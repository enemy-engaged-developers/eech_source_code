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



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

#include "assign.h"
#include "taskgen.h"

#include "../highlevl/highlevl.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

#define DEBUG_ESCORT_TASK_CREATION 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef DEBUG

static void dump_guide_stack (entity *group);

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void assign_keysite_tasks (entity *keysite, task_category_types category)
{
	entity
		*task,
		*group,
		*force,
		**task_list;

	float
		*sort_order;

	int
		loop,
		task_type,
		task_count,
		assign_count,
		group_type,
		keysite_type,
		non_critical_task_count;

	static int
		idle_group_count [NUM_ENTITY_SUB_TYPE_GROUPS];

	ASSERT (keysite);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	task = get_local_entity_first_child (keysite, LIST_TYPE_UNASSIGNED_TASK);

	if (!task)
	{
		return;
	}

	keysite_type = get_local_entity_int_value (keysite, INT_TYPE_ENTITY_SUB_TYPE);

	force = get_local_entity_parent (keysite, LIST_TYPE_KEYSITE_FORCE);

	ASSERT (force);

	//
	// Count tasks at keysite
	//

	task_count = 0;
	
	task = get_local_entity_first_child (keysite, LIST_TYPE_UNASSIGNED_TASK);

	while (task)
	{
		if (get_local_entity_int_value (task, INT_TYPE_TASK_CATEGORY) == category)
		{
			task_count ++;
		}

		task = get_local_entity_child_succ (task, LIST_TYPE_UNASSIGNED_TASK);
	}

	if (task_count == 0)
	{
		return;
	}

	//
	// Count up number of idle groups across the map (air registry only)
	//

	memset (idle_group_count, 0, sizeof (int) * NUM_ENTITY_SUB_TYPE_GROUPS);

	group = get_local_entity_first_child (force, LIST_TYPE_AIR_REGISTRY);

	while (group)
	{
		if (get_local_entity_int_value (group, INT_TYPE_GROUP_MODE) == GROUP_MODE_IDLE)
		{
			group_type = get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE);

			idle_group_count [group_type] ++;
		}

		group = get_local_entity_child_succ (group, LIST_TYPE_AIR_REGISTRY);
	}

	//
	// Sort tasks
	//

	ASSERT (task_count > 0);
	
	task_list = ( entity * * ) malloc_fast_mem (sizeof (entity *) * task_count);

	sort_order = ( float * ) malloc_fast_mem (sizeof (float) * task_count);

	task_count = 0;

	task = get_local_entity_first_child (keysite, LIST_TYPE_UNASSIGNED_TASK);

	while (task)
	{
		if (get_local_entity_int_value (task, INT_TYPE_TASK_CATEGORY) == category)
		{
			task_list [task_count] = task;
	
			sort_order [task_count] = get_local_entity_float_value (task, FLOAT_TYPE_TASK_PRIORITY);
	
			if (get_local_entity_int_value (task, INT_TYPE_CRITICAL_TASK))
			{
				sort_order [task_count] *= 2.0;
			}
	
			task_count ++;
		}
			
		task = get_local_entity_child_succ (task, LIST_TYPE_UNASSIGNED_TASK);
	}

	quicksort_entity_list (task_list, task_count, sort_order);

	//
	// Assign tasks
	//

	assign_count = max (keysite_database [keysite_type].assign_task_count, 1u);

	non_critical_task_count = keysite_database [keysite_type].reserve_task_count;

	for (loop = 0; loop < task_count; loop ++)
	{
		if (assign_count == 0)
		{				
			break;
		}

		task = task_list [loop]; 

		//
		// Check for player lock
		//

		if (get_local_entity_parent (task, LIST_TYPE_PILOT_LOCK))
		{
			continue;
		}

		//
		// Reserve non-critical tasks for player
		//

		if (!get_local_entity_int_value (task, INT_TYPE_CRITICAL_TASK))
		{
			if (get_local_entity_float_value (task, FLOAT_TYPE_EXPIRE_TIMER) > KEYSITE_TASK_ASSIGN_TIMER)
			{
				if (non_critical_task_count > 0)
				{
					non_critical_task_count --;
	
					continue;
				}
			}
		}

		task_type = get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE);

		group = get_suitable_registered_group (task, idle_group_count);
	
		if (group)
		{
			if (assign_primary_task_to_group (group, task))
			{
	
				ai_log ("ASSIGN: (%d/%d) Assigned group %s (%d) to task %s (%d) from keysite %s (%s)",
								assign_count, keysite_database [keysite_type].assign_task_count,
								entity_sub_type_group_names [get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE)],
								get_local_entity_index (group),
								entity_sub_type_task_names [task_type],
								get_local_entity_index (task),
								get_local_entity_string (keysite, STRING_TYPE_KEYSITE_NAME),
								entity_side_short_names [get_local_entity_int_value (keysite, INT_TYPE_SIDE)]);
	
				//
				// Only Assign n tasks per keysite
				//

				assign_count --;
			}
			else
			{
				#if DEBUG_MODULE
	
				debug_log ("ASSIGN: not assigning group %s (%d) to task %s (%d) from keysite %s",
								entity_sub_type_group_names [get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE)],
								get_local_entity_index (group),
								entity_sub_type_task_names [task_type],
								get_local_entity_index (task),
								get_local_entity_string (keysite, STRING_TYPE_KEYSITE_NAME));
	
				#endif
			}
		}
	}

	free_mem (task_list);

	free_mem (sort_order);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int suitable_group_task_specific_checks (entity *task, entity *group)
{
	int
		task_type,
		group_type;

	task_type = get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE);

	group_type = get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE);

	switch (task_type)
	{
		case ENTITY_SUB_TYPE_TASK_ESCORT:
		{
			//
			// Special check for ESCORT task :- Jets escort Jets, Helis escort anything but jets
			//

			entity
				*objective;
	
			int
				objective_group_type;
	
			objective = get_local_entity_parent (task, LIST_TYPE_TASK_DEPENDENT);
	
			ASSERT (objective);
	
			ASSERT (get_local_entity_type (objective) == ENTITY_TYPE_GROUP);
	
			objective_group_type = get_local_entity_int_value (objective, INT_TYPE_ENTITY_SUB_TYPE);
	
			if (group_database [objective_group_type].ai_stats.movement_speed >= 5)
			{
				// Fast objective group
				if (group_database [group_type].ai_stats.movement_speed < 5)
				{
					// Slow escort group
					return FALSE;
				}
			}
			else
			{
				// Slow objective group
				if (group_database [group_type].ai_stats.movement_speed >= 5)
				{
					// Fast escort group
					return FALSE;
				}
				
				// magitek: avoid picking slower units than objective group
				if (group_database [objective_group_type].ai_stats.movement_speed > group_database [group_type].ai_stats.movement_speed)
				{
					return FALSE;
				}
			}

			break;
		}

		case ENTITY_SUB_TYPE_TASK_TROOP_INSERTION:
		{
			//
			// Special check for T.I. task :- Assaults against airbases require large assault groups
			//

			entity
				*objective;
	
			int
				objective_type;
	
			objective = get_local_entity_parent (task, LIST_TYPE_TASK_DEPENDENT);
	
			ASSERT (objective);
	
			ASSERT (get_local_entity_type (objective) == ENTITY_TYPE_KEYSITE);
	
			objective_type = get_local_entity_int_value (objective, INT_TYPE_ENTITY_SUB_TYPE);
	
			if (objective_type == ENTITY_SUB_TYPE_KEYSITE_AIRBASE && get_local_entity_int_value (group, INT_TYPE_MEMBER_COUNT) < 2 &&
					get_local_entity_int_value (objective, INT_TYPE_SIDE) != get_local_entity_int_value (group, INT_TYPE_SIDE))
				return FALSE;

			break;
		}
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *get_suitable_registered_group (entity *task, int *idle_group_count)
{

	float
		result,
		distance,
		best_result;

	group
		*group_raw;

	entity
		*keysite,
		*best_group,
		*current_group;

	unsigned int
		idle_count;

	entity_sub_types
		task_type;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ASSERT (task);

	task_type = get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE);

	keysite = get_local_entity_parent (task, LIST_TYPE_UNASSIGNED_TASK);

	ASSERT (keysite);

	best_group = NULL;

	best_result = FLT_MAX;

	current_group = get_local_entity_first_child (keysite, LIST_TYPE_KEYSITE_GROUP);

	while (current_group)
	{
		//
		// Check for player lock
		//

		if (!get_local_entity_parent (current_group, LIST_TYPE_PILOT_LOCK))
		{
			group_raw = ( group * ) get_local_entity_data (current_group);
	
			//////////////////////////////////////////////////////////////////
			// stop carriers being assigned
			if (group_raw->sub_type == ENTITY_SUB_TYPE_GROUP_ASSAULT_SHIP)
			{
				current_group = get_local_entity_child_succ (current_group, LIST_TYPE_KEYSITE_GROUP);
	
				continue;
			}
			//////////////////////////////////////////////////////////////////
	
			if (get_local_entity_int_value (current_group, INT_TYPE_GROUP_MODE) == GROUP_MODE_IDLE)
			{
				if (group_raw->sleep == 0.0)
				{	
					if (group_raw->side == get_local_entity_int_value (task, INT_TYPE_SIDE))
					{
						if (idle_group_count)
						{
							idle_count = idle_group_count [group_raw->sub_type];
						}
						else
						{
							idle_count = INT_MAX;
						}

						if (idle_count > group_database [group_raw->sub_type].minimum_idle_count)
						{
							if (get_local_entity_int_value (current_group, INT_TYPE_MEMBER_COUNT) >= get_local_entity_int_value (task, INT_TYPE_MINIMUM_MEMBER_COUNT))
							{
								if (check_group_members_awake (current_group))
								{
									result = get_group_to_task_suitability (group_raw->sub_type, task_type);
									
									if (result > 0.0)
									{
										if (suitable_group_task_specific_checks (task, current_group))
										{
											//
											// locality
											// assess if group could get to end position quick enough, using first members cruise speed.
											//
					
											if (assess_group_task_locality_factor (current_group, task, &distance))
											{
												//
												// best group
												//
							
												if (result < best_result)
												{
													best_result = result;
							
													best_group = current_group;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}

		current_group = get_local_entity_child_succ (current_group, LIST_TYPE_KEYSITE_GROUP);
	}

	return best_group;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int assign_primary_task_to_group (entity *group_en, entity *task_en)
{
	entity_sub_types
		task_type,
		group_type;

	entity
		*force,
		*keysite;

	int
		side,
		formation,
		air_threat,
		enemy_sectors;

	unsigned int
		threat;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);
		
	task_type = get_local_entity_int_value (task_en, INT_TYPE_ENTITY_SUB_TYPE);

	ASSERT (task_database [task_type].primary_task);

	group_type = get_local_entity_int_value (group_en, INT_TYPE_ENTITY_SUB_TYPE);

	ASSERT (!get_local_group_primary_task (group_en));

	if (assign_task_to_group (group_en, task_en, TASK_ASSIGN_ALL_MEMBERS))
	{
		//
		// set default group formation
		//

		formation = get_local_entity_int_value (group_en, INT_TYPE_GROUP_DEFAULT_FORMATION);

		if (formation != get_local_entity_int_value (group_en, INT_TYPE_GROUP_FORMATION))
		{
			set_client_server_entity_int_value (group_en, INT_TYPE_GROUP_FORMATION, formation);
		}

		//
		// Link to new keysite
		// 

		if (get_local_entity_int_value (group_en, INT_TYPE_GROUP_LIST_TYPE) == LIST_TYPE_KEYSITE_GROUP)
		{
			keysite = ( entity * ) get_local_entity_ptr_value (task_en, PTR_TYPE_RETURN_KEYSITE);

			if (keysite)
			{
				ASSERT(get_local_entity_type (keysite) == ENTITY_TYPE_KEYSITE);

				set_client_server_entity_parent (group_en, LIST_TYPE_KEYSITE_GROUP, keysite);
			}	
		}

		//
		// Notify Force
		//

		side = get_local_entity_int_value (group_en, INT_TYPE_SIDE);

		force = get_local_force_entity ( ( entity_sides ) side );

		ASSERT (force);

		notify_local_entity (ENTITY_MESSAGE_TASK_ASSIGNED, force, task_en);

		//
		// Assess for Escort task
		//

		if (task_database [task_type].escort_required_threshold != ESCORT_NEVER)
		{
			threat = assess_task_difficulty (task_en, &air_threat, &enemy_sectors);

			#if DEBUG_ESCORT_TASK_CREATION

			debug_filtered_log ("(ASSIGN) Side %s: Assigned %s to %s, objective %s",
											entity_side_short_names [side],
											get_local_entity_string (group_en, STRING_TYPE_FULL_NAME),
											get_local_entity_string (task_en, STRING_TYPE_FULL_NAME),
											get_task_objective_string (task_en)
									);

			debug_filtered_log ("Threat: %d (air_threat: %d, enemy_sectors: %d) - Threshold %d",
											threat, air_threat, enemy_sectors,
											task_database [task_type].escort_required_threshold);

			#endif

			if (threat >= task_database [task_type].escort_required_threshold)
			{
				create_escort_task (group_en, (threat >= ESCORT_CRITICAL), task_database [ENTITY_SUB_TYPE_TASK_ESCORT].task_priority, NULL, NULL);

				ai_log ("(ASSIGN) Created Escort Task for %s :- Threat %d / Threshold %d",
											get_local_entity_string (task_en, STRING_TYPE_FULL_NAME),
											threat,
											task_database [task_type].escort_required_threshold
											);
			}
		}

		//
		// Store Start Time
		//

		set_client_server_entity_float_value (task_en, FLOAT_TYPE_START_TIME, get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_ELAPSED_TIME));

		//
		// Clear Expire Timer (now also used for destroying completed tasks)
		//

		set_local_entity_float_value (task_en, FLOAT_TYPE_EXPIRE_TIMER, 0.0);

		ai_log ("(ASSIGN) Side %s: Assigned %s (%d) to %s (%d) - Priority %f",
					entity_side_short_names [side],
					get_local_entity_string (group_en, STRING_TYPE_FULL_NAME),
					get_local_entity_safe_index (group_en),
					get_local_entity_string (task_en, STRING_TYPE_FULL_NAME),
					get_local_entity_safe_index (task_en),
					get_local_entity_float_value (task_en, FLOAT_TYPE_TASK_PRIORITY));

		return TRUE;
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *push_task_onto_group_task_stack (entity *group, entity *task, unsigned int valid_members)
{
	entity
		*task_parent,
		*guide;

	list_types
		list_type;

	#ifdef DEBUG
	
	unsigned int
		total_members,
		member_number;

	#endif

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ASSERT (group);

	#ifdef DEBUG

	total_members = 0;

	//
	// Check not already on stack
	//

	guide = get_local_entity_first_child (task, LIST_TYPE_GUIDE);

	while (guide)
	{
		if (get_local_entity_parent (guide, LIST_TYPE_GUIDE_STACK) == group)
		{
			member_number = get_local_entity_int_value (guide, INT_TYPE_VALID_GUIDE_MEMBERS);

			total_members |= member_number;
		}

		guide = get_local_entity_child_succ (guide, LIST_TYPE_GUIDE);
	}

	//
	// A TASK may be on the stack many times, but any one member should not have the same task duplicated
	// e.g. ENGAGE tasks may be duplicated many times, but their guide "valid_members" should all be exclusive
	//

	if (valid_members & total_members)
	{
		debug_filtered_log ("Trying to assign task %s (%d) to group %s - members %d",
										get_local_entity_string (task, STRING_TYPE_FULL_NAME),
										get_local_entity_index (task),
										get_local_entity_string (group, STRING_TYPE_FULL_NAME),
										valid_members);

		debug_filtered_log ("");

		dump_guide_stack (group);

		debug_fatal ("ASSIGN: Task %s already on Group %s guide stack",
								get_local_entity_string (task, STRING_TYPE_FULL_NAME),
								get_local_entity_string (group, STRING_TYPE_FULL_NAME));
	}

	#endif

	//
	// create guide entity for task
	//

	guide = create_client_server_guide_entity (task, NULL, valid_members);

	attach_group_to_guide_entity (group, guide);

	//
	// remove task and group from lists (must be done AFTER guide is created and attached)
	//

	list_type = get_local_task_list_type (task);

	if (list_type == LIST_TYPE_UNASSIGNED_TASK)
	{
		task_parent = get_local_entity_parent (task, list_type);

		if (task_parent)
		{
			delete_local_entity_from_parents_child_list (task, list_type);

			//
			// add task to assigned task list, if not already on it.
			//

			insert_local_entity_into_parents_child_list (task, LIST_TYPE_ASSIGNED_TASK, task_parent, NULL);

			transmit_entity_comms_message (ENTITY_COMMS_SWITCH_LIST, task, LIST_TYPE_UNASSIGNED_TASK, task_parent, LIST_TYPE_ASSIGNED_TASK);
		}
	}

	return guide;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int assign_task_to_group (entity *group, entity *task_en, unsigned int valid_members)
{

	int
		sites_required;

	entity_sub_types
		sub_type,
		group_type;

	entity
		*force,
		*landing,
		*end_keysite,
		*start_keysite,
		*guide,
		*member;

	vec3d
		*pos;

	task
		*task_raw;

   debug_assert (get_comms_model () == COMMS_MODEL_SERVER);

	ASSERT (task_en);

	ASSERT (group);

	ASSERT (!(get_local_group_primary_task (group) && (get_local_entity_int_value (task_en, INT_TYPE_PRIMARY_TASK))));

	task_raw = ( task * ) get_local_entity_data (task_en);

	group_type = get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE);

	member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

	// don't if no members or if the group is a CARRIER
	if (!member)
	{
		return FALSE;
	}

	if (get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_GROUP_ASSAULT_SHIP)
	{
		if (task_raw->sub_type != ENTITY_SUB_TYPE_TASK_ENGAGE)
		{
			return FALSE;
		}
	}

	//
	// check for invalid tasks
	//
	
	switch (task_raw->sub_type)
	{
		case ENTITY_SUB_TYPE_TASK_LANDING:
		case ENTITY_SUB_TYPE_TASK_LANDING_HOLDING:
		case ENTITY_SUB_TYPE_TASK_TAKEOFF:
		case ENTITY_SUB_TYPE_TASK_TAKEOFF_HOLDING:
		{
			#ifdef DEBUG

			debug_fatal ("ASSIGN: Invalid task type (%s) for assign_task_to_group", get_local_entity_string (task_en, STRING_TYPE_FULL_NAME));

			#endif

			return FALSE;
		}
	}

	//
	// Create route
	//

	if (get_local_entity_int_value (group, INT_TYPE_GROUP_LIST_TYPE) == LIST_TYPE_KEYSITE_GROUP)
	{
		start_keysite = get_local_entity_parent (group, LIST_TYPE_KEYSITE_GROUP);
	}
	else
	{
		start_keysite = NULL;
	}

	pos = get_local_entity_vec3d_ptr (task_en, VEC3D_TYPE_STOP_POSITION);

	force = get_local_force_entity ( ( entity_sides ) get_local_entity_int_value (task_en, INT_TYPE_SIDE) );

	sub_type = group_database [group_type].default_landing_type;

	landing = NULL;

	end_keysite = NULL;

	if (get_local_entity_int_value (task_en, INT_TYPE_ASSESS_LANDING))
	{
		end_keysite = ( entity * ) get_local_entity_ptr_value (task_en, PTR_TYPE_RETURN_KEYSITE);

		if (end_keysite)
		{
			//
			// check end keysite has suitble free landing sites
			//

			if (start_keysite != end_keysite)
			{
				//
				// if end keysite == start keysite then keysite MUST have enough sites because the aircraft are already there
				//
				
				sites_required = get_local_group_member_count (group);
	
				if (get_keysite_landing_sites_available (end_keysite, sub_type) < sites_required)
				{
					//
					// END keysite was specified - but no free landing sites for this group
					//
					
					return FALSE;
				}
			}
		}
		else
		{
			if (!start_keysite)
			{
				entity *leader = get_local_entity_first_child (group, LIST_TYPE_MEMBER);
				
				ASSERT(leader);
				
				debug_log ("ASSIGN: start keysite not present, looking for new one");

				start_keysite = get_closest_keysite (NUM_ENTITY_SUB_TYPE_KEYSITES, (entity_sides) task_raw->side, get_local_entity_vec3d_ptr (leader, VEC3D_TYPE_POSITION), 1.0 * KILOMETRE, NULL, TRUE, NULL);
				
				if (!start_keysite)
					return FALSE;

				sites_required = get_local_group_member_count (group);
				
				if (get_keysite_landing_sites_available (start_keysite, sub_type) < sites_required)
					return FALSE;

				debug_log ("ASSIGN: new start keysite is %s", get_local_entity_string (start_keysite, STRING_TYPE_KEYSITE_NAME));
			}
			

			//
			// No END keysite specified so return to start keysite
			//

			end_keysite = start_keysite;

			set_local_entity_ptr_value (task_en, PTR_TYPE_RETURN_KEYSITE, end_keysite);
		}

		ASSERT (end_keysite);

		landing = get_local_entity_landing_entity (end_keysite, group_database [get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE)].default_landing_type);
	}

	if (create_generic_waypoint_route (group, task_en, end_keysite, NULL, NULL, NULL, 0))
	{
		#if DEBUG_MODULE

		debug_log ("ASSIGN: group %s (%d) assigned to task %s (%d)",
							get_local_entity_string (group, STRING_TYPE_FULL_NAME),
							get_local_entity_index (group),
							get_local_entity_string (task_en, STRING_TYPE_FULL_NAME),
							get_local_entity_index (task_en));

		#endif

		//
		// Assign task
		//

		guide = push_task_onto_group_task_stack (group, task_en, valid_members);

		assign_task_to_group_members (group, guide, valid_members);

		return TRUE;
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int assign_task_to_group_members (entity *group, entity *guide, unsigned int valid_members)
{
	entity
		*task,
		*member;

	ASSERT (group);

	ASSERT (guide);

	task = get_local_entity_parent (guide, LIST_TYPE_GUIDE);

	ASSERT (task);

	member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

	while (member)
	{
		if (valid_members & (1 << get_local_entity_int_value (member, INT_TYPE_GROUP_MEMBER_NUMBER)))
		{
			attach_group_member_to_guide_entity (member, guide);

			notify_local_entity (ENTITY_MESSAGE_TASK_ASSIGNED, member, task);

			if (get_local_entity_type (member) == ENTITY_TYPE_HELICOPTER) {
				prepare_helicopter_for_task(member, task, group);
				set_helicopter_fuel_level(member, task);
			}
		}
		
		member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int reassign_group_members_to_valid_tasks (entity *group, entity *last_task, unsigned int members_to_reassign, int engage_enemy)
{
	entity
		*guide,
		*member,
		*new_task;

	unsigned int
		member_number,
		valid_members;

	ASSERT (members_to_reassign != 0);

	//
	// first see if any engage tasks can be done
	//

	if (engage_enemy)
	{
		members_to_reassign = assign_engage_tasks_to_group (group, members_to_reassign);
	}

	if (!members_to_reassign)
	{
		//
		// all members have successfully been allocated engage tasks - so no need to worry about rest of the task stack
		//
		
		return TRUE;
	}

	//
	// take each member in the group that requires a new task
	//

	member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

	while (member)
	{
		member_number = (1 << get_local_entity_int_value (member, INT_TYPE_GROUP_MEMBER_NUMBER));

		if (members_to_reassign & member_number)
		{
			//
			// If the member gets here, then it can't be doing an engage task, hence it shouldn't have a target... (unless its a player)
			//

			if (get_local_entity_int_value (member, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI)
			{
				if (get_local_entity_parent (member, LIST_TYPE_TARGET))
				{
					set_client_server_entity_parent (member, LIST_TYPE_TARGET, NULL);
				}
			}

			//
			// Look at each task on the stack
			//

			new_task = NULL;
	
			guide = get_local_entity_first_child (group, LIST_TYPE_GUIDE_STACK);

			while (guide)
			{
				//
				// is task meant for this member ?
				//

				valid_members = get_local_entity_int_value (guide, INT_TYPE_VALID_GUIDE_MEMBERS);

				if (valid_members & member_number)
				{
					new_task = get_local_entity_parent (guide, LIST_TYPE_GUIDE);

					if (get_local_entity_int_value (new_task, INT_TYPE_TASK_TERMINATED) == TASK_TERMINATED_IN_PROGRESS)
					{
						assign_new_task_to_group_member (group, member, new_task, guide);

						//
						// clear member flag, and skip to next group member
						//
							
						members_to_reassign &= (~member_number);
							
						break;
					}
				}
			
				new_task = NULL;

				guide = get_local_entity_child_succ (guide, LIST_TYPE_GUIDE_STACK);
			}
		}
		
		member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int assign_new_task_to_group_member (entity *group, entity *member, entity *task, entity *guide)
{
	entity
		*current_guide,
		*current_task;

	unsigned int
		member_number;

	ASSERT (group);

	ASSERT (member);

	ASSERT (task);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	if (get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_TASK_ENGAGE)
	{
		ASSERT (!guide);
	}
	else
	{
		ASSERT (guide);
	}

	member_number = (1 << get_local_entity_int_value (member, INT_TYPE_GROUP_MEMBER_NUMBER));

	//
	// check what task the member is currently doing
	//

	current_guide = get_local_entity_parent (member, LIST_TYPE_FOLLOWER);

	if (current_guide)
	{
		current_task = get_local_entity_parent (current_guide, LIST_TYPE_GUIDE);

		ASSERT (current_task);

		if (current_task == task)
		{
			//
			// member is already doing the task
			//
			
			return TRUE;
		}

		if (get_local_entity_int_value (current_task, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_TASK_ENGAGE)
		{
			//
			// member is doing an ENGAGE task - destroy the guide clone....
			//

			ASSERT (get_local_entity_int_value (current_guide, INT_TYPE_VALID_GUIDE_MEMBERS) == member_number);

			//
			// ...UNLESS the task has been terminated, in which case the guide will be destroyed elsewhere
			//

			if (get_local_entity_int_value (current_task, INT_TYPE_TASK_TERMINATED) == TASK_TERMINATED_IN_PROGRESS)
			{
				destroy_client_server_entity (current_guide);
			}
		}
	}

	//
	// assign member to new task
	//

	if (guide)
	{
		assign_task_to_group_members (group, guide, member_number);
	}
	else
	{
		assign_task_to_group (group, task, member_number);
	}

	//
	// ensure member was actually assigned to a new task (not always the desired task - e.g. in the case of when aircraft need to takeoff first)
	//

	#ifdef DEBUG

	current_guide = get_local_entity_parent (member, LIST_TYPE_FOLLOWER);

	ASSERT (current_guide);

	current_task = get_local_entity_parent (current_guide, LIST_TYPE_GUIDE);

	ASSERT (current_task);

	#endif

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void respond_to_player_task_assign_request (entity *pilot, entity *task, entity *mobile)
{
	entity
		*group;
		
	ASSERT (pilot);

	ASSERT (mobile);

	ASSERT (task);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	group = get_local_entity_parent (mobile, LIST_TYPE_MEMBER);

	if ((!get_local_entity_first_child (task, LIST_TYPE_GUIDE)) && (!get_local_group_primary_task (group)))
	{
		if (assign_primary_task_to_group (group, task))
		{
			transmit_entity_comms_message (ENTITY_COMMS_TASK_ASSIGN_RESULT, pilot, task, mobile);

			return;
		}
	}
	else
	{
		if (get_local_group_primary_task (group))
		{
			transmit_entity_comms_message (ENTITY_COMMS_TASK_ASSIGN_RESULT, pilot, task, mobile);

			return;
		}
	}

	transmit_entity_comms_message (ENTITY_COMMS_TASK_ASSIGN_RESULT, pilot, NULL, NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef DEBUG

void dump_guide_stack (entity *group)
{
	entity
		*guide,
		*task;

	debug_filtered_log ("GUIDE STACK:-");
	debug_filtered_log ("-------------");

	guide = get_local_entity_first_child (group, LIST_TYPE_GUIDE_STACK);

	while (guide)
	{
		task = get_local_entity_parent (guide, LIST_TYPE_GUIDE);

		ASSERT (task);

		debug_filtered_log ("Task %s (%d) - Guide (%d) - Valid Members %d",
									get_local_entity_string (task, STRING_TYPE_FULL_NAME),
									get_local_entity_index (task),
									get_local_entity_index (guide),
									get_local_entity_int_value (guide, INT_TYPE_VALID_GUIDE_MEMBERS));

		guide = get_local_entity_child_succ (guide, LIST_TYPE_GUIDE_STACK);
	}
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int check_group_members_awake (entity *group)
{

	entity
		*mb;

	mb = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

	while (mb)
	{

		if (get_local_entity_float_value (mb, FLOAT_TYPE_SLEEP) > 0.0)
		{

			return FALSE;
		}

		mb = get_local_entity_child_succ (mb, LIST_TYPE_MEMBER);
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// PLACE TROOPS INSIDE HELICOPTER
void prepare_helicopter_for_task(entity *en, entity *task, entity *group) {
	#if DEBUG_MODULE || DEBUG_SUPPLY
	debug_log ("task assigned to helicopter: %s", get_local_entity_string (task, STRING_TYPE_FULL_NAME));
	#endif

	if (get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_TASK_TROOP_INSERTION)
	{
		int troops = group_database[get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE)].ai_stats.troop_space;

		ASSERT (troops > 0 && troops <= 12);

		set_client_server_entity_int_value (en, INT_TYPE_TROOPS_ONBOARD, troops);
	}
}

// CALCULATE AMOUNT OF REQUIRED FUEL
void set_helicopter_fuel_level(entity *en, entity *task) {
	float
		time = 0,
		fuel_amount,
		fuel_level,
		fuel_supply;
		
	if (get_local_entity_int_value (en, INT_TYPE_LANDED)) {
		time = get_task_estimated_route_duration(task) / 60.0; // IN MINUTES

		if (time > 0.0 && time < 500.0) {
			time = 1.25 * time + 20.0; // ADD SOME EXTRA
			fuel_amount = time * get_local_entity_float_value (en, FLOAT_TYPE_FUEL_ECONOMY);
			fuel_level = fuel_amount / get_local_entity_float_value (en, FLOAT_TYPE_FUEL_DEFAULT_WEIGHT);
			fuel_level = bound(ceil(fuel_level * 4.0) / 4.0, 0.5, 1.0);
			fuel_supply = fuel_level * get_local_entity_float_value (en, FLOAT_TYPE_FUEL_DEFAULT_WEIGHT);
			
			ASSERT(fuel_supply > 1.0);
			
			#if DEBUG_SUPPLY || DEBUG_MODULE
			debug_log ("Required amount of fuel for %s: %fkg (%fmin %feco), fuel level: %f / %f", get_local_entity_string (en, STRING_TYPE_FULL_NAME),
					fuel_amount, time, get_local_entity_float_value (en, FLOAT_TYPE_FUEL_ECONOMY), fuel_supply, get_local_entity_float_value (en, FLOAT_TYPE_FUEL_DEFAULT_WEIGHT));
			#endif

			set_client_server_entity_float_value (en, FLOAT_TYPE_FUEL_SUPPLY_LEVEL, fuel_supply);
		}
	}
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

