// 
// 	 Enemy Engaged RAH-66 Comanche Versus KA-52 Hokum
// 	 Copyright (C) 2000 Empire Interactive (Europe) Ltd,
// 	 677 High Road, North Finchley, London N12 0DA
// 
// 	 Please see the document LICENSE.TXT for the full licence agreement
// 
// 2. LICENCE
//  2.1 	
//  	Subject to the provisions of this Agreement we now grant to you the 
//  	following rights in respect of the Source Code:
//   2.1.1 
//   	the non-exclusive right to Exploit  the Source Code and Executable 
//   	Code on any medium; and 
//   2.1.2 
//   	the non-exclusive right to create and distribute Derivative Works.
//  2.2 	
//  	Subject to the provisions of this Agreement we now grant you the
// 	following rights in respect of the Object Code:
//   2.2.1 
// 	the non-exclusive right to Exploit the Object Code on the same
// 	terms and conditions set out in clause 3, provided that any
// 	distribution is done so on the terms of this Agreement and is
// 	accompanied by the Source Code and Executable Code (as
// 	applicable).
// 
// 3. GENERAL OBLIGATIONS
//  3.1 
//  	In consideration of the licence granted in clause 2.1 you now agree:
//   3.1.1 
// 	that when you distribute the Source Code or Executable Code or
// 	any Derivative Works to Recipients you will also include the
// 	terms of this Agreement;
//   3.1.2 
// 	that when you make the Source Code, Executable Code or any
// 	Derivative Works ("Materials") available to download, you will
// 	ensure that Recipients must accept the terms of this Agreement
// 	before being allowed to download such Materials;
//   3.1.3 
// 	that by Exploiting the Source Code or Executable Code you may
// 	not impose any further restrictions on a Recipient's subsequent
// 	Exploitation of the Source Code or Executable Code other than
// 	those contained in the terms and conditions of this Agreement;
//   3.1.4 
// 	not (and not to allow any third party) to profit or make any
// 	charge for the Source Code, or Executable Code, any
// 	Exploitation of the Source Code or Executable Code, or for any
// 	Derivative Works;
//   3.1.5 
// 	not to place any restrictions on the operability of the Source 
// 	Code;
//   3.1.6 
// 	to attach prominent notices to any Derivative Works stating
// 	that you have changed the Source Code or Executable Code and to
// 	include the details anddate of such change; and
//   3.1.7 
//   	not to Exploit the Source Code or Executable Code otherwise than
// 	as expressly permitted by  this Agreement.
// 



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

#include "engage.h"
#include "taskgen.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static unsigned int assign_specific_engage_task_to_group (entity *group, entity *task, unsigned int valid_members);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_engage_task (entity *group, entity *objective, entity *originator, int expire)
{
	entity
		*force_en,
		*new_task;

	force
		*force_raw;

	vec3d
		*pos;

	entity_sides
		side;

	float
		expire_time;

	formation_types
		original_formation;

	ASSERT (group);

	if (!get_local_entity_int_value (group, INT_TYPE_ENGAGE_ENEMY))
		return NULL;

	ASSERT (objective);

	#if DEBUG_MODULE
	
	debug_log ("ENGAGE: Trying to engage against %s (%d)",
									get_local_entity_string (objective, STRING_TYPE_FULL_NAME),
									get_local_entity_index (objective));

	#endif

	ASSERT ((get_local_entity_int_value (objective, INT_TYPE_IDENTIFY_AIRCRAFT)) ||
				(get_local_entity_int_value (objective, INT_TYPE_IDENTIFY_VEHICLE)) ||
				(get_local_entity_int_value (objective, INT_TYPE_IDENTIFY_FIXED)) ||
				(get_local_entity_int_value (objective, INT_TYPE_IDENTIFY_WEAPON)));

	if (get_local_entity_int_value (get_session_entity (), INT_TYPE_SUPPRESS_AI_FIRE))
	{
		return NULL;
	}

	force_en = get_local_force_entity ((entity_sides)get_local_entity_int_value (group, INT_TYPE_SIDE));

	force_raw = (force*) get_local_entity_data (force_en);

	if (expire)
	{
		expire_time = (2.0 * ONE_MINUTE) + (frand1 () * ONE_MINUTE);
	}
	else
	{
		//
		// Max time for ENGAGE - stops attackers hanging around target area for too long (especially if they can NEVER get to their target)
		//
		
		expire_time = (10.0 * ONE_MINUTE) + (frand1 () * 2.5 * ONE_MINUTE);
	}

	new_task = NULL;

	//
	// Create engage task to expire in task_time seconds - debug
	//

	side = (entity_sides) get_local_entity_int_value (group, INT_TYPE_SIDE);

	pos = get_local_entity_vec3d_ptr (objective, VEC3D_TYPE_POSITION);

	ASSERT (get_local_entity_first_child (group, LIST_TYPE_MEMBER));

	original_formation = FORMATION_ROW_LEFT;

	new_task = create_task (ENTITY_SUB_TYPE_TASK_ENGAGE,
									side,
									(movement_types) get_local_entity_int_value (group, INT_TYPE_MOVEMENT_TYPE),
									NULL,
									NULL,
									originator,
									TRUE,
									expire_time,
									0.0,
									objective,
									task_database [ENTITY_SUB_TYPE_TASK_ENGAGE].task_priority,
									pos, objective, ENTITY_SUB_TYPE_WAYPOINT_TARGET, original_formation,
									&terminator_point, NULL, NUM_ENTITY_SUB_TYPE_WAYPOINTS, FORMATION_NONE);

	#if DEBUG_MODULE
	
	debug_log ("ENGAGE: Created Engage task against %s (%d)",
									get_local_entity_string (objective, STRING_TYPE_FULL_NAME),
									get_local_entity_index (objective));

	#endif

	return new_task;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int engage_targets_in_sector (entity *group, int sx, int sz, unsigned int task_target_type, int expire)
{

	unsigned int
		objective_target_type;

	entity
		*new_task,
		*objective,
		*target_sector;

	entity_sides
		side;

	sector
		*raw;

	new_task = NULL;

	target_sector = get_local_raw_sector_entity (sx, sz);

	raw = (sector *) get_local_entity_data (target_sector);

	//
	// search for viable targets
	//

	side = (entity_sides) get_local_entity_int_value (group, INT_TYPE_SIDE);

	objective = raw->sector_root.first_child;

	while (objective) 
	{
		//
		// criteria for target is that it is a valid target, and not on your side
		//

		if ((get_local_entity_int_value (objective, INT_TYPE_SIDE) != side) &&
			((get_local_entity_int_value (objective, INT_TYPE_TARGET_TYPE) != TARGET_TYPE_INVALID)))
		{

			objective_target_type = get_local_entity_int_value (objective, INT_TYPE_TASK_TARGET_TYPE);

			if (task_target_type & objective_target_type)
			{

				if (get_local_entity_int_value (objective, INT_TYPE_ALIVE))
				{

					new_task = create_engage_task (group, objective, group, expire);

					if (new_task)
					{
						assign_task_to_group (group, new_task, TASK_ASSIGN_NO_MEMBERS);
					}
				}
			}
		}

		objective = get_local_entity_child_succ (objective, LIST_TYPE_SECTOR);
	}

	if (assign_engage_tasks_to_group (group, TASK_ASSIGN_ALL_MEMBERS) != TASK_ASSIGN_ALL_MEMBERS)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int engage_targets_in_area (entity *group, vec3d *target_point, float radius, unsigned int task_target_type, int expire)
{

	int
		sx,
		sz,
		min_sector_x,
		max_sector_x,
		min_sector_z,
		max_sector_z;

	entity
		*new_task,
		*objective,
		*target_sector;

	entity_sides
		side;

	sector
		*raw;

	float
		range,
		temp_x,
		temp_z;

	vec3d
		*pos;

	unsigned int
		objective_target_type;

	new_task = NULL;

	temp_x = target_point->x - radius;
	temp_z = target_point->z - radius;

	get_x_sector (min_sector_x, temp_x);
	get_z_sector (min_sector_z, temp_z);

	temp_x = target_point->x + radius;
	temp_z = target_point->z + radius;

	get_x_sector (max_sector_x, temp_x);
	get_z_sector (max_sector_z, temp_z);

	min_sector_x = bound (min_sector_x, MIN_MAP_X_SECTOR, MAX_MAP_X_SECTOR);
	max_sector_x = bound (max_sector_x, MIN_MAP_X_SECTOR, MAX_MAP_X_SECTOR);

	min_sector_z = bound (min_sector_z, MIN_MAP_Z_SECTOR, MAX_MAP_Z_SECTOR);
	max_sector_z = bound (max_sector_z, MIN_MAP_Z_SECTOR, MAX_MAP_Z_SECTOR);

	side = (entity_sides) get_local_entity_int_value (group, INT_TYPE_SIDE);

	for (sz = min_sector_z; sz <= max_sector_z; sz ++)
	{
		for (sx = min_sector_x; sx <= max_sector_x; sx ++)
		{

			target_sector = get_local_raw_sector_entity (sx, sz);

			raw = (sector *) get_local_entity_data (target_sector);

			//
			// search for viable targets
			//

			objective = raw->sector_root.first_child;

			while (objective)
			{
				//
				// criteria for target is that it is a valid target, and not on your side
				//

				if ((get_local_entity_int_value (objective, INT_TYPE_SIDE) != side) &&
					((get_local_entity_int_value (objective, INT_TYPE_TARGET_TYPE) != TARGET_TYPE_INVALID)))
				{

					objective_target_type = get_local_entity_int_value (objective, INT_TYPE_TASK_TARGET_TYPE);

					if (task_target_type & objective_target_type)
					{

						//debug_log ("TASKGEN: found target %d for task %d", objective_target_type, task_target_type);

						if (get_local_entity_int_value (objective, INT_TYPE_ALIVE))
						{

							pos = get_local_entity_vec3d_ptr (objective, VEC3D_TYPE_POSITION);

							range = get_approx_2d_range (target_point, pos);

							if (range <= radius)
							{

								new_task = create_engage_task (group, objective, group, expire);

								if (new_task)
								{
									assign_task_to_group (group, new_task, TASK_ASSIGN_NO_MEMBERS);
								}
							}
						}
					}
				}

				objective = get_local_entity_child_succ (objective, LIST_TYPE_SECTOR);
			}
		}
	}

	if (assign_engage_tasks_to_group (group, TASK_ASSIGN_ALL_MEMBERS) != TASK_ASSIGN_ALL_MEMBERS)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int debug_engage_targets_in_area (entity *group, vec3d *target_point, float radius, unsigned int target_type)
{
	//
	// Engages all targets in area, regardless of side 
	//

	int
		sx,
		sz,
		min_sector_x,
		max_sector_x,
		min_sector_z,
		max_sector_z;

	entity
		*new_task,
		*objective,
		*target_sector;

	entity_sides
		side;

	sector
		*raw;

	float
		range,
		temp_x,
		temp_z;

	vec3d
		*pos;

	new_task = NULL;

	temp_x = target_point->x - radius;
	temp_z = target_point->z - radius;

	get_x_sector (min_sector_x, temp_x);
	get_z_sector (min_sector_z, temp_z);

	temp_x = target_point->x + radius;
	temp_z = target_point->z + radius;

	get_x_sector (max_sector_x, temp_x);
	get_z_sector (max_sector_z, temp_z);

	min_sector_x = bound (min_sector_x, MIN_MAP_X_SECTOR, MAX_MAP_X_SECTOR);
	max_sector_x = bound (max_sector_x, MIN_MAP_X_SECTOR, MAX_MAP_X_SECTOR);

	min_sector_z = bound (min_sector_z, MIN_MAP_Z_SECTOR, MAX_MAP_Z_SECTOR);
	max_sector_z = bound (max_sector_z, MIN_MAP_Z_SECTOR, MAX_MAP_Z_SECTOR);

	side = (entity_sides) get_local_entity_int_value (group, INT_TYPE_SIDE);

	for (sz = min_sector_z; sz <= max_sector_z; sz ++)
	{
		for (sx = min_sector_x; sx <= max_sector_x; sx ++)
		{
			target_sector = get_local_raw_sector_entity (sx, sz);

			raw = (sector *) get_local_entity_data (target_sector);

			//
			// search for viable targets
			//

			objective = raw->sector_root.first_child;

			while (objective)
			{
				//
				// criteria for target is that it is a valid target, and not in your group
				//

				if (get_local_entity_int_value (objective, INT_TYPE_TARGET_TYPE) == target_type)
				{
					if (get_local_entity_int_value (objective, INT_TYPE_ALIVE))
					{
						if ((!get_local_entity_int_value (objective, INT_TYPE_IDENTIFY_MOBILE)) || (get_local_entity_parent (objective, LIST_TYPE_MEMBER) != group))
						{
							pos = get_local_entity_vec3d_ptr (objective, VEC3D_TYPE_POSITION);
	
							range = get_approx_2d_range (target_point, pos);
	
							if (range <= radius)
							{
	
								new_task = create_engage_task (group, objective, group, FALSE);
	
								if (new_task)
								{
									assign_task_to_group (group, new_task, TASK_ASSIGN_NO_MEMBERS);
								}
							}
						}
					}
				}

				objective = get_local_entity_child_succ (objective, LIST_TYPE_SECTOR);
			}
		}
	}

	if (assign_engage_tasks_to_group (group, TASK_ASSIGN_ALL_MEMBERS) != TASK_ASSIGN_ALL_MEMBERS)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int engage_targets_in_group (entity *group, entity *target_group, int expire)
{
	entity
		*task,
		*guide,
		*member,
		*new_task;

	ASSERT (group);

	ASSERT (target_group);

	ASSERT (target_group->type == ENTITY_TYPE_GROUP);

	//
	// Abort if engage task already exists
	//

	guide = get_local_entity_first_child (group, LIST_TYPE_GUIDE_STACK);

	while (guide)
	{
		task = get_local_entity_parent (guide, LIST_TYPE_GUIDE);

		ASSERT (task);

		if (get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_TASK_ENGAGE)
		{

			entity
				*member,
				*objective;

			objective = get_local_entity_parent (task, LIST_TYPE_TASK_DEPENDENT);

			member = get_local_entity_first_child (target_group, LIST_TYPE_MEMBER);

			while (member)
			{
				if (member == objective)
				{
					#if DEBUG_MODULE

					debug_log ("ENGAGE.C: engage task already exists");

					#endif

					if (!get_local_entity_int_value (member, INT_TYPE_IDENTIFY_VEHICLE))
						return FALSE;
				}

				member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
			}
		}

		guide = get_local_entity_child_succ (guide, LIST_TYPE_GUIDE_STACK);
	}

	//
	// Create N engage tasks
	//

	member = get_local_entity_first_child (target_group, LIST_TYPE_MEMBER);

	while (member) 
	{

		if (get_local_entity_int_value (member, INT_TYPE_ALIVE))
		{
			new_task = create_engage_task (group, member, group, expire);

			if (new_task)
			{
				assign_task_to_group (group, new_task, TASK_ASSIGN_NO_MEMBERS);

				#if DEBUG_MODULE

				debug_log ("ENGAGE.C: engage task assigned to member");

				#endif
			}
		}

		member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
	}

	//
	// Assign tasks to group members
	//

	if (assign_engage_tasks_to_group (group, TASK_ASSIGN_ALL_MEMBERS) != TASK_ASSIGN_ALL_MEMBERS)
	{
		#if DEBUG_MODULE

		debug_log ("ENGAGE.C: engage task created");

		#endif

		return TRUE;
	}
	else
	{
		#if DEBUG_MODULE

		debug_log ("ENGAGE.C: engage task create fail");

		#endif

		return FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int engage_specific_target (entity *group, entity *target, unsigned int valid_members, int expire)
{
	entity
		*task,
		*guide,
		*new_task,
		*objective;

	ASSERT (group);

	ASSERT (target);

	if (!get_local_entity_int_value (target, INT_TYPE_ALIVE))
	{
		return FALSE;
	}

	//
	// Check if engage task already exists
	//

	new_task = NULL;

	guide = get_local_entity_first_child (group, LIST_TYPE_GUIDE_STACK);

	while (guide)
	{
		task = get_local_entity_parent (guide, LIST_TYPE_GUIDE);

		ASSERT (task);

		if (get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_TASK_ENGAGE)
		{
			objective = get_local_entity_parent (task, LIST_TYPE_TASK_DEPENDENT);

			if (target == objective)
			{
				new_task = task;

				break;
			}
		}

		guide = get_local_entity_child_succ (guide, LIST_TYPE_GUIDE_STACK);
	}

	if (new_task)
	{
		//
		// Use existing engage tasks
		//

		assign_specific_engage_task_to_group (group, new_task, valid_members);

		return TRUE;
	}
	else
	{
		//
		// Create engage task
		//

		new_task = create_engage_task (group, target, group, expire);

		if (new_task)
		{
			assign_task_to_group (group, new_task, TASK_ASSIGN_NO_MEMBERS);

			if (assign_engage_tasks_to_group (group, valid_members) != valid_members)
			{
				return TRUE;
			}
		}
	}
	
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void engage_specific_targets(entity *wingman, entity *targets[])
{
	entity
		*group;

	unsigned int valid_members = 0, member_number, i;

	ASSERT(get_local_entity_int_value (wingman, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI);

	group = get_local_entity_parent(wingman, LIST_TYPE_MEMBER);
	
	if (!get_local_entity_int_value (group, INT_TYPE_ENGAGE_ENEMY))
		return;

	member_number = get_local_entity_int_value(wingman, INT_TYPE_GROUP_MEMBER_NUMBER);
	valid_members = (1 << member_number);
	
	for (i = 0; i < 16; i++)
	{
		entity* target = targets[i];
		if (!target)
			break;

		engage_specific_target(group, target, valid_members, FALSE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int assign_specific_engage_task_to_group (entity *group, entity *task, unsigned int valid_members)
{
	entity
		*member;

	unsigned int
		member_number;

	ASSERT (group);

	ASSERT (task);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);
		
	member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

	while ((member) && (valid_members))
	{
		//
		// Only assign AI entities to ENGAGE tasks
		//
		
		if (get_local_entity_int_value (member, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI)
		{
			if (get_local_entity_int_value (member, INT_TYPE_ENGAGE_ENEMY))
			{
				member_number = (1 << get_local_entity_int_value (member, INT_TYPE_GROUP_MEMBER_NUMBER));
		
				if (member_number & valid_members)
				{
					if (assign_new_task_to_group_member (group, member, task, NULL))
					{
						valid_members &= (~member_number);
					}
				}
			}
		}
		
		member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
	}

	return valid_members;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_ENGAGE_RANGE	((16.0f * KILOMETRE) * (16.0f * KILOMETRE))			// aircraft only

unsigned int assign_engage_tasks_to_group (entity *group, unsigned int valid_members)
{
	entity
		*task,
		*guide,
		*target,
		*member,
		*single_member,
		*persuer,
		**guide_list;

	unsigned int
		member_number;

	int
		best_count,
		best_guide,
		loop,
		criteria,
		task_count,
		*assigned_count;

	float
		range,
		*priority;

	vec3d
		*member_pos,
		*target_pos;

	ASSERT (group);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	if (!valid_members)
	{
		return valid_members;
	}	

	//
	// count up engage tasks
	//

	task_count = 0;

	guide = get_local_entity_first_child (group, LIST_TYPE_GUIDE_STACK);

	while (guide)
	{
		if (get_local_entity_int_value (guide, INT_TYPE_VALID_GUIDE_MEMBERS) == TASK_ASSIGN_NO_MEMBERS)
		{
			task = get_local_entity_parent (guide, LIST_TYPE_GUIDE);

			ASSERT (task);

			ASSERT (get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_TASK_ENGAGE);

			if (get_local_entity_int_value (task, INT_TYPE_TASK_TERMINATED) == TASK_TERMINATED_IN_PROGRESS)
			{
				task_count ++;
			}
		}

		guide = get_local_entity_child_succ (guide, LIST_TYPE_GUIDE_STACK);
	}

	#if DEBUG_MODULE

	debug_log ("ENGAGE: ==========================");
	
	debug_log ("ENGAGE: %d suitable tasks", task_count);

	#endif

	if (task_count == 0)
	{
		return valid_members;
	}

	//////////////////////////////////////////////////////////////////
	//
	// prioritize engage tasks
	//
	//////////////////////////////////////////////////////////////////

	//
	// get target priority
	//

	guide_list = (entity * *) malloc_fast_mem (sizeof (entity *) * task_count);
	priority = (float *) malloc_fast_mem (sizeof (float) * task_count);
	assigned_count = (int *) malloc_fast_mem (sizeof (int) * task_count);

	#if DEBUG_MODULE

	debug_log ("ENGAGE: ======RAW LIST======");

	#endif

	single_member = NULL;
	// check if we have a single member, if so assign that member to single_member
	for (member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);
		 member;
		 member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER))
	{
		member_number = (1 << get_local_entity_int_value (member, INT_TYPE_GROUP_MEMBER_NUMBER));

		if (member_number & valid_members)
		{
			if (single_member)  // we already have a valid member, so there is more than one
			{
				single_member = NULL;
				break;
			}
			else
				single_member = member;
		}
	}

	loop = 0;
	guide = get_local_entity_first_child (group, LIST_TYPE_GUIDE_STACK);

	while (guide)
	{
		if (get_local_entity_int_value (guide, INT_TYPE_VALID_GUIDE_MEMBERS) == TASK_ASSIGN_NO_MEMBERS)
		{
			task = get_local_entity_parent (guide, LIST_TYPE_GUIDE);

			ASSERT (task);

			ASSERT (get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_TASK_ENGAGE);

			if (get_local_entity_int_value (task, INT_TYPE_TASK_TERMINATED) == TASK_TERMINATED_IN_PROGRESS)
			{
				target = get_local_entity_parent (task, LIST_TYPE_TASK_DEPENDENT);

//				ASSERT (target);

				if (!target)
				{
					notify_local_entity (ENTITY_MESSAGE_TASK_TERMINATED, task, group, TASK_TERMINATED_ABORTED);

					free_mem (guide_list);
				
					free_mem (priority);
				
					free_mem (assigned_count);
				
					return valid_members;
				}
				
				guide_list [loop] = guide;

				if (get_local_entity_int_value (group, INT_TYPE_AIRCRAFT_GROUP))
				{
					priority [loop] = get_local_entity_float_value (target, FLOAT_TYPE_TARGET_PRIORITY_AIR_ATTACK);
				}
				else
				{
					priority [loop] = get_local_entity_float_value (target, FLOAT_TYPE_TARGET_PRIORITY_GROUND_ATTACK);
				}

				priority [loop] += max(0.0f, 0.1f - 0.1f * get_sqr_2d_range(get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION), get_local_entity_vec3d_ptr (group, VEC3D_TYPE_POSITION)) / MAX_ENGAGE_RANGE); // close targets a more important
				
				if (get_local_entity_int_value (target, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI) // adjust players priority value for different difficulty levels
				{
					entity *pilot;
					
					pilot = get_local_entity_first_child (target, LIST_TYPE_AIRCREW);

					ASSERT (pilot);

					if (get_local_entity_int_value (pilot, INT_TYPE_DIFFICULTY_LEVEL) == GAME_DIFFICULTY_HARD)
						priority [loop] += 0.1;
					else if (get_local_entity_int_value (pilot, INT_TYPE_DIFFICULTY_LEVEL) == GAME_DIFFICULTY_EASY)
						priority [loop] = max(0.0, priority [loop] - 0.1);
				}
				
				#if DEBUG_MODULE

				debug_log ("ENGAGE: (%d) Target : %s, Priority %f", loop, get_local_entity_string (target, STRING_TYPE_FULL_NAME), priority [loop]);

				#endif

				loop ++;
			}
		}

		guide = get_local_entity_child_succ (guide, LIST_TYPE_GUIDE_STACK);
	}

	ASSERT (loop == task_count);

	//
	// sort the tasks according to their priority
	//

	quicksort_entity_list (guide_list, task_count, priority);

	#if DEBUG_MODULE

	debug_log ("ENGAGE: ======SORTED======");

	for (loop = 0; loop < task_count; loop ++)
	{
		task = get_local_entity_parent (guide_list [loop], LIST_TYPE_GUIDE);

		target = get_local_entity_parent (task, LIST_TYPE_TASK_DEPENDENT);

		debug_log ("ENGAGE: (%d) Target : %s (%d), Priority %f", loop, get_local_entity_string (target, STRING_TYPE_FULL_NAME), get_local_entity_index (target), priority [loop]);
	}

	#endif

	//
	// consider other entities attacking the same targets
	//

	memset (assigned_count, 0, sizeof (int) * task_count);

	for (loop = 0; loop < task_count; loop ++)
	{
		task = get_local_entity_parent (guide_list [loop], LIST_TYPE_GUIDE);

		target = get_local_entity_parent (task, LIST_TYPE_TASK_DEPENDENT);

		persuer = get_local_entity_first_child (target, LIST_TYPE_TARGET);

		while (persuer)
		{
			assigned_count [loop] ++;

			persuer = get_local_entity_child_succ (persuer, LIST_TYPE_TARGET);
		}
	}

	//////////////////////////////////////////////////////////////////
	//
	// assign new engage tasks
	//
	// for each member, run through the task list (most important first)
	// try to assign one member per task, but as tasks run out group members can "team-up"
	//
	//////////////////////////////////////////////////////////////////

	member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

	while ((member) && (valid_members))
	{
		//
		// Only assign AI entities to ENGAGE tasks
		//
		
		if (get_local_entity_int_value (member, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI)
		{
			if (get_local_entity_int_value (member, INT_TYPE_ENGAGE_ENEMY))
			{
				member_number = (1 << get_local_entity_int_value (member, INT_TYPE_GROUP_MEMBER_NUMBER));

				if (member_number & valid_members)
				{
					member_pos = get_local_entity_vec3d_ptr (member, VEC3D_TYPE_POSITION);

					if (get_local_entity_int_value (member, INT_TYPE_IDENTIFY_AIRCRAFT))
					{
						criteria = BEST_WEAPON_CRITERIA_MINIMAL;
					}
					else
					{
						criteria = BEST_WEAPON_RANGE_CHECK | BEST_WEAPON_LOS_CHECK;
					}
		
					best_guide = -1;
			
					best_count = INT_MAX;
			
					for (loop = 0; loop < task_count; loop ++)
					{
						if (assigned_count [loop] < best_count)
						{
							guide = guide_list [loop];					
			
							task = get_local_entity_parent (guide, LIST_TYPE_GUIDE);
			
							target = get_local_entity_parent (task, LIST_TYPE_TASK_DEPENDENT);

							ASSERT(target);

							if (target == member)
							{
								//
								// Don't try to attack yourself !
								//
								
								continue;
							}

							//
							// Range Check
							//

							if (criteria & BEST_WEAPON_RANGE_CHECK)
							{
								// range handled by weapon selection
								range = 0.0;
							}
							else
							{
								target_pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

								range = get_sqr_2d_range (target_pos, member_pos);
							}
							
							if (range < MAX_ENGAGE_RANGE)
							{
								//
								// Weapon Check
								//
				
								if (get_best_weapon_for_target (member, target, criteria) != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
								{
									best_count = assigned_count [loop];
				
									best_guide = loop;
								}
							}
						}
					}
			
					if (best_guide != -1)
					{
						guide = guide_list [best_guide];
						
						task = get_local_entity_parent (guide, LIST_TYPE_GUIDE);
			
						if (assign_new_task_to_group_member (group, member, task, NULL))
						{
							valid_members &= (~member_number);
				
							assigned_count [best_guide] ++;
			
							#if DEBUG_MODULE
						
							debug_log ("ENGAGE: Assigning %s (%d) to target %s (%d)",
											get_local_entity_string (member, STRING_TYPE_FULL_NAME), get_local_entity_index (member),
											get_local_entity_string (target, STRING_TYPE_FULL_NAME), get_local_entity_index (target));
		
							#endif
						}
					}
					else
					{
						#if DEBUG_MODULE
						
						debug_log ("ENGAGE: Couldn't assign %s (%d) to engage task",
										get_local_entity_string (member, STRING_TYPE_FULL_NAME), get_local_entity_index (member));
		
						#endif
					}
				}
			}
		}
		
		member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
	}

	free_mem (guide_list);

	free_mem (priority);

	free_mem (assigned_count);

	return valid_members;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void terminate_all_engage_tasks (entity *group)
{
	entity
		*guide,
		*task;

	ASSERT (group);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	do
	{
		guide = get_local_entity_first_child (group, LIST_TYPE_GUIDE_STACK);

		while (guide)
		{
			if (get_local_entity_int_value (guide, INT_TYPE_VALID_GUIDE_MEMBERS) == 0)
			{
				task = get_local_entity_parent (guide, LIST_TYPE_GUIDE);

				ASSERT (get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_TASK_ENGAGE);

				if (get_local_entity_int_value (task, INT_TYPE_TASK_TERMINATED) == TASK_TERMINATED_IN_PROGRESS)
				{
					notify_local_entity (ENTITY_MESSAGE_TASK_TERMINATED, task, group, TASK_TERMINATED_ABORTED);

					break;
				}
			}

			guide = get_local_entity_child_succ (guide, LIST_TYPE_GUIDE_STACK);
		}
	}
	while (guide);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void terminate_entity_current_engage_task (entity *en)
{
	entity
		*guide,
		*task;

	ASSERT (en);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	guide = get_local_entity_parent (en, LIST_TYPE_FOLLOWER);

	if (guide)
	{
		task = get_local_entity_parent (guide, LIST_TYPE_GUIDE);

		if (get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_TASK_ENGAGE)
		{
			delete_group_member_from_engage_guide (en, guide, FALSE);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
