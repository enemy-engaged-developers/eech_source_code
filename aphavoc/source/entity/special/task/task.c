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



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

#include "ai/highlevl/highlevl.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float
	completed_task_expire_time = (20.0 * ONE_MINUTE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void assess_task_sector_difficulty (entity *task_en, int x, int z, int *air_threats, int *enemy_sectors);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

task_completed_types assess_task_completeness (entity *en, task_terminated_types task_terminated)
{
	entity_sub_types
		sub_type;

	entity
		*objective;

	float
		partial,
		success,
		rating;

	entity_sides
		side;

	int
		colour;

	task_completed_types
		result;

	//
	// calculates and stores the overall success of a task as a float between 0.0 and 1.0,
	//
	// and returns whether the task is deemed complete or not
	//

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ASSERT (!get_local_entity_int_value (en, INT_TYPE_TASK_COMPLETED));

	sub_type = get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);

	ASSERT (sub_type < NUM_ENTITY_SUB_TYPE_TASKS);

	ASSERT (task_database [sub_type].primary_task);

	side = (entity_sides) get_local_entity_int_value (en, INT_TYPE_SIDE);

	colour = (side == ENTITY_SIDE_BLUE_FORCE) ? DEBUG_COLOUR_BLUE : DEBUG_COLOUR_RED;

	objective = get_local_entity_parent (en, LIST_TYPE_TASK_DEPENDENT);

	partial = task_database [sub_type].task_pass_percentage_partial / 100.0;

	success = task_database [sub_type].task_pass_percentage_success / 100.0;

	//
	// give rating for task completeness
	//

	rating = 0.0;

	result = TASK_INCOMPLETE;

	switch (sub_type)
	{

		case ENTITY_SUB_TYPE_TASK_ADVANCE:
		case ENTITY_SUB_TYPE_TASK_COASTAL_PATROL:
		case ENTITY_SUB_TYPE_TASK_FREE_FLIGHT:
		case ENTITY_SUB_TYPE_TASK_RETREAT:
		case ENTITY_SUB_TYPE_TASK_TRANSFER_FIXED_WING:
		case ENTITY_SUB_TYPE_TASK_TRANSFER_HELICOPTER:
		{
			//
			// SUCCESS if waypoint route complete
			// INCOMPLETE if in progress
			// FAILURE any other
			//
			
			if (task_terminated == TASK_TERMINATED_WAYPOINT_ROUTE_COMPLETE)
			{
				rating = 1.0;

				result = TASK_COMPLETED_SUCCESS;
			}
			else if (task_terminated == TASK_TERMINATED_IN_PROGRESS)
			{
			}
			else
			{
				result = TASK_COMPLETED_FAILURE;
			}

			break;
		}

		case ENTITY_SUB_TYPE_TASK_BARCAP:
		case ENTITY_SUB_TYPE_TASK_COMBAT_AIR_PATROL:
		{
			//
			// SUCCESS if stop time reached 
			// INCOMPLETE if in progress
			// FAILURE any other
			//
			
			if (task_terminated == TASK_TERMINATED_STOP_TIME_REACHED)
			{
				result = TASK_COMPLETED_SUCCESS;
			}
			else if (task_terminated == TASK_TERMINATED_IN_PROGRESS)
			{
			}
			else
			{
				result = TASK_COMPLETED_FAILURE;
			}

			break;
		}

		case ENTITY_SUB_TYPE_TASK_ESCORT:
		{
			//
			// SUCCESS if objective message and escorted group alive
			// ILLEGAL for waypoint route complete
			// INCOMPLETE if in progress
			// FAILURE any other
			//
			
			float
				old_member_count,
				new_member_count;

			if (task_terminated == TASK_TERMINATED_OBJECTIVE_MESSAGE)
			{
				ASSERT (objective);

				old_member_count = get_local_entity_float_value (en, FLOAT_TYPE_TASK_USER_DATA);

				new_member_count = get_local_entity_int_value (objective, INT_TYPE_MEMBER_COUNT);
				
				ASSERT (old_member_count > 0.0);

				rating = (old_member_count - new_member_count) / old_member_count;
	
				rating = bound (rating, 0.0, 1.0);

				rating = 1.0 - rating;

				if (rating >= partial)
				{
					result = TASK_COMPLETED_SUCCESS;
				}
				else
				{
					result = TASK_COMPLETED_FAILURE;
				}

				ai_log ("ESCORT RESULT: Old Count = %.0f, New Count = %.0f, Rating = %f%%", old_member_count, new_member_count, (rating * 100.0));
			}
			else if (task_terminated == TASK_TERMINATED_IN_PROGRESS)
			{
			}
			else
			{
				result = TASK_COMPLETED_FAILURE;
			}

			break;
		}

		case ENTITY_SUB_TYPE_TASK_BAI:
		case ENTITY_SUB_TYPE_TASK_CLOSE_AIR_SUPPORT:
		case ENTITY_SUB_TYPE_TASK_SEAD:
		{
			float
				old_member_count,
				new_member_count;

			//
			// check the old sector defence level against new defence level (0.0 -> 1.0)
			//

			old_member_count = get_local_entity_float_value (en, FLOAT_TYPE_TASK_USER_DATA);

			new_member_count = get_local_entity_int_value (objective, INT_TYPE_MEMBER_COUNT);

			ASSERT (old_member_count > 0.0);

			if (new_member_count > 0.0)
			{
				if (old_member_count <= 4)
				{
					//
					// If group had 4 or less members in it to start with, then only pass mission if all destroyed
					//
					
					rating = 0.0;
				}
				else
				{
					rating = (old_member_count - new_member_count) / old_member_count;
	
					rating = bound (rating, 0.0, 1.0);
				}
				
				if (rating >= success)
				{
					//
					// enough members killed for success
					//
					
					result = TASK_COMPLETED_SUCCESS;
				}
				else if (rating >= partial)
				{
					//
					// enough members killed for partial success
					//
					
					result = TASK_COMPLETED_PARTIAL;
				}
				else
				{
					//
					// Not enough members killed for success.......
					//
					
					if (task_terminated == TASK_TERMINATED_IN_PROGRESS)
					{
						//
						// ..... O.K. If the task is still in progress ....
						//
						
						result = TASK_INCOMPLETE;
					}
					else
					{
						//
						// .... But failure if the task has been terminated for whatever reason
						//
						
						result = TASK_COMPLETED_FAILURE;
					}
				}
			}
			else
			{
				//
				// No members left in group - so must be a success
				//
				
				rating = 1.0;
				
				result = TASK_COMPLETED_SUCCESS;
			}

			break;
		}

		case ENTITY_SUB_TYPE_TASK_GROUND_STRIKE:
		case ENTITY_SUB_TYPE_TASK_ANTI_SHIP_STRIKE:
		{
			float
				min_eff;

			ASSERT (objective);

			ASSERT (get_local_entity_type (objective) == ENTITY_TYPE_KEYSITE);

			min_eff = get_local_entity_float_value (objective, FLOAT_TYPE_MINIMUM_EFFICIENCY);

			//
			// By reducing the minimum efficiency required for success, it will stop the victim keysite from being
			// safe by simply repairing one structure...
			//
			
			min_eff *= 0.8;

			if ((!get_local_entity_int_value (objective, INT_TYPE_IN_USE)) ||
				(get_local_entity_float_value (objective, FLOAT_TYPE_EFFICIENCY) < min_eff))
			{
				//
				// Assuming that strike tasks are only created for keysites with above minimum efficiency and in-use,
				// If the efficiency is now below minimum, or not in use then the task was a success...
				//
					
				rating = 1.0;

				result = TASK_COMPLETED_SUCCESS;
			}
			else
			{
				//
				// otherwise, give rating based on how much the efficiency has decreased 
				//

				rating = get_local_entity_float_value (en, FLOAT_TYPE_TASK_USER_DATA) - get_local_entity_float_value (objective, FLOAT_TYPE_EFFICIENCY);

				rating = bound (rating, 0.0, 1.0);

				if (rating >= success)
				{
					result = TASK_COMPLETED_SUCCESS;
				}
				else if (rating >= partial)
				{
					result = TASK_COMPLETED_PARTIAL;
				}
				else
				{
					//
					// Rating not good enough for success.......
					//
					
					if (task_terminated == TASK_TERMINATED_IN_PROGRESS)
					{
						//
						// ..... O.K. If the task is still in progress ....
						//
						
						result = TASK_INCOMPLETE;
					}
					else if (task_terminated == TASK_TERMINATED_WAYPOINT_ROUTE_COMPLETE)
					{
						//
						// ..... partial if group returned to base ....
						//
						
						result = TASK_COMPLETED_PARTIAL;
					}
					else
					{
						//
						// .... But failure if the task has been terminated for whatever reason
						//
						
						result = TASK_COMPLETED_FAILURE;
					}
				}
			}

			break;
		}

		case ENTITY_SUB_TYPE_TASK_BDA:
		case ENTITY_SUB_TYPE_TASK_RECON:
		case ENTITY_SUB_TYPE_TASK_REPAIR:
		case ENTITY_SUB_TYPE_TASK_SUPPLY:
		case ENTITY_SUB_TYPE_TASK_TROOP_INSERTION:
		{
			//
			// SUCCESS if objective message 
			// INCOMPLETE if in progress
			// FAILURE any other
			//
			
			if (task_terminated == TASK_TERMINATED_OBJECTIVE_MESSAGE)
			{
				rating = 1.0;

				result = TASK_COMPLETED_SUCCESS;
			}
			else if (task_terminated == TASK_TERMINATED_IN_PROGRESS)
			{
			}
			else
			{
				result = TASK_COMPLETED_FAILURE;
			}

			break;
		}
		
		case ENTITY_SUB_TYPE_TASK_OCA_STRIKE:
		case ENTITY_SUB_TYPE_TASK_OCA_SWEEP:
		case ENTITY_SUB_TYPE_TASK_TROOP_MOVEMENT_PATROL:
		{
			if ((task_terminated == TASK_TERMINATED_WAYPOINT_ROUTE_COMPLETE) || (task_terminated == TASK_TERMINATED_OBJECTIVE_MESSAGE))
			{
				rating = 1.0;

				result = TASK_COMPLETED_SUCCESS;
			}
			else if (task_terminated == TASK_TERMINATED_IN_PROGRESS)
			{
			}
			else
			{
				result = TASK_COMPLETED_FAILURE;
			}
				
			break;
		}

		default:
		{
			debug_fatal ("TASK: Unknown Task Type %d", sub_type);

			break;
		}
	}

	//
	// determine overall task success rating
	//

	if (rating != get_local_entity_float_value (en, FLOAT_TYPE_RATING))
	{
		set_client_server_entity_float_value (en, FLOAT_TYPE_RATING, rating);
	}

	return result;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int award_points_for_task_completion (entity *en)
{
	int
		points,
		total,
		task_completed;

	ASSERT (en);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	task_completed = get_local_entity_int_value (en, INT_TYPE_TASK_COMPLETED);

	ASSERT (task_completed != TASK_INCOMPLETE);

	points = get_local_entity_int_value (en, INT_TYPE_POINTS_VALUE);

	switch (task_completed)
	{
		case TASK_COMPLETED_FAILURE:
		{
			points = 0;

			break;
		}
		case TASK_COMPLETED_PARTIAL:
		{
			points = (points >> 2);

			break;
		}
		case TASK_COMPLETED_SUCCESS:
		{
			break;
		}
	}

	if (points > 0)
	{
		total = get_local_entity_int_value (en, INT_TYPE_TASK_SCORE);
	
		total += points;
	
		set_client_server_entity_int_value (en, INT_TYPE_TASK_SCORE, total);
	}

	return points;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

list_types get_local_task_list_type (entity *task_en)
{
	task
		*raw;

	raw = (task *) get_local_entity_data (task_en);

	switch (raw->task_state)
	{
		case TASK_STATE_UNASSIGNED:
		{
			return LIST_TYPE_UNASSIGNED_TASK;
		}
		case TASK_STATE_ASSIGNED:
		{
			return LIST_TYPE_ASSIGNED_TASK;
		}
		case TASK_STATE_COMPLETED:
		{
			return LIST_TYPE_COMPLETED_TASK;
		}
		default:
		{
			debug_fatal ("TASK: Invalid Task State %d", raw->task_state);
		}
	}

	return LIST_TYPE_INVALID;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *get_local_entity_current_task (entity *member)
{
	entity
		*guide;

	ASSERT (member);

	guide = get_local_entity_parent (member, LIST_TYPE_FOLLOWER);

	if (guide)
	{
		return get_local_entity_parent (guide, LIST_TYPE_GUIDE);
	}
	else
	{
		return NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int entity_is_object_of_task (entity *en, entity_sub_types task_type, entity_sides side)
{

	entity
		*this_task;

	int
		count;

	ASSERT (en);

	count = 0;

	this_task = get_local_entity_first_child (en, LIST_TYPE_TASK_DEPENDENT);

	while (this_task)
	{

		if (get_local_entity_type (this_task) == ENTITY_TYPE_TASK)
		{

			if (get_local_entity_int_value (this_task, INT_TYPE_ENTITY_SUB_TYPE) == task_type)
			{

				if (get_local_entity_int_value (this_task, INT_TYPE_SIDE) == side)
				{

					if (get_local_entity_int_value (this_task, INT_TYPE_TASK_STATE) != TASK_STATE_COMPLETED)
					{

						count ++;
					}
				}
			}
		}

		this_task = get_local_entity_child_succ (this_task, LIST_TYPE_TASK_DEPENDENT);
	}

	return count;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int assess_task_locality_factor (entity *task_en, vec3d *pos1, float cruise_speed, float *return_distance)
{
	vec3d
		*pos2;

	float
		distance;

	//
	// locality
	// assess if entity could get to end position quick enough
	//

	if (return_distance)
	{
		*return_distance = 0.0;
	}

	//
	// only approximate - get straight line distance from current pos to task start pos
	//

	pos2 = get_local_entity_vec3d_ptr (task_en, VEC3D_TYPE_START_POSITION);

	distance = get_approx_2d_range (pos1, pos2);

	if ((cruise_speed * get_local_entity_float_value (task_en, FLOAT_TYPE_EXPIRE_TIMER)) < distance)
	{

		return FALSE;
	}

	if (return_distance)
	{
		*return_distance = distance;
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int assess_task_difficulty (entity *task_en, int *route_air_threat, int *route_enemy_sectors)
{

	//
	// rate task difficulty on :
	//
	//	-	distance travelled in enemy sectors					(0..10)
	//	-	enemy air threats en route								(0..10)
	// -	task type													(0..10)
	//	-	time of day													(0..10)
	//	-	number of wingmen											(0..10)
	//	-	available weapons / fuel								(0..10)
	// -	BASE distance from frontline							(0..10)
	//	-	Number of enemy tasks in destination sector 		(0..10)
	//	-	Number of allied tasks in destination sector 	(0..10)
	//	-	Balance of power											(0..10)
	//
	// total																(0..100)

	unsigned int
		node;

	int
		x,
		z,
		air_threats,
		enemy_sectors,
		task_level,
		difficulty_level;

	task
		*raw;

	vec3d
		*last_pos,
		*this_pos;

	entity
		*start_keysite;

	ASSERT (task_en);

	raw = (task *) get_local_entity_data (task_en);

	//
	// task type
	//

	task_level = task_database [raw->sub_type].difficulty_rating;

	//
	// enemy sectors
	//

	air_threats = 0;

	enemy_sectors = 0;

	start_keysite = raw->task_link.parent; 

	if ((start_keysite) && (get_local_entity_type (start_keysite) == ENTITY_TYPE_KEYSITE))
	{
		//
		// start at the assigned keysite
		//
		
		node = 0;

		last_pos = get_local_entity_vec3d_ptr (start_keysite, VEC3D_TYPE_POSITION);
	}
	else
	{
		//
		// start at the first point on the route
		//
		
		node = 1;

		last_pos = &raw->route_nodes [0];
	}

	for (; node < raw->route_length; node ++)
	{
		this_pos = &raw->route_nodes [node];

		{
			int
				d, ax, az, sx, sz, dx, dz, x1, z1, x2, z2;
		
			//
			// convert coordinates into sector coordinates
			//
		
			get_x_sector (x1, last_pos->x);
			get_z_sector (z1, last_pos->z);
		
			get_x_sector (x2, this_pos->x);
			get_z_sector (z2, this_pos->z);

			//
			// traverse sectors using bresenham's algorithm
			//
		
			dx = x2 - x1;
			dz = z2 - z1;
		
			ax = abs( dx ) * 2;
			az = abs( dz ) * 2;
		
			sx = ( dx > 0 ) ? 1 : -1;
			sz = ( dz > 0 ) ? 1 : -1;
		
			x = x1;
			z = z1;
		
			if ( ax > az )
			{
				d = az - ( ax / 2 );
		
				while ( TRUE )
				{
					assess_task_sector_difficulty (task_en, x, z, &air_threats, &enemy_sectors);

					if ( x == x2 ) break;
		
					if ( d >= 0 )
					{
						z += sz;
						d -= ax;
					}
		
					x += sx;
					d += az;
				}
			}
			else
			{
				d = ax - ( az / 2 );
		
				while ( TRUE )
				{
					assess_task_sector_difficulty (task_en, x, z, &air_threats, &enemy_sectors);

					if ( z == z2 ) break;
		
					if ( d >= 0 )
					{
						x += sx;
						d -= az;
					}
		
					z += sz;
					d += ax;
				}
			}
		}

		last_pos = this_pos;
	}

	//
	// do last point on the route
	//

	last_pos = &raw->route_nodes [raw->route_length - 1];

	get_x_sector (x, last_pos->x);
	get_z_sector (z, last_pos->z);
		
	assess_task_sector_difficulty (task_en, x, z, &air_threats, &enemy_sectors);

	//
	// +1 difficulty point for every sector with enemy air defences ( maximum of 5 )
	//

	if (route_air_threat)
	{
		*route_air_threat = air_threats;
	}

	air_threats = min ((air_threats >> 1), 5);

	//
	// +1 difficulty point for every 2 enemy sectors passing through ( maximum of 5 )
	//

	if (route_enemy_sectors)
	{
		*route_enemy_sectors = enemy_sectors;
	}

	enemy_sectors = min ((enemy_sectors >> 1), 5);

	//
	// total
	//

	difficulty_level = air_threats + enemy_sectors;

	return difficulty_level;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void assess_task_sector_difficulty (entity *task_en, int x, int z, int *air_threats, int *enemy_sectors)
{
	entity
		*sector_en;

	entity_sides
		side;

	sector_en = get_local_raw_sector_entity(x, z);

	side = (entity_sides) get_local_entity_int_value (task_en, INT_TYPE_SIDE);

	ASSERT (sector_en);

	if (
			(get_local_sector_entity_enemy_surface_to_air_defence_level (sector_en, side) > 0.0)
		)
	{
		(*air_threats) ++;
	}

	if (get_local_entity_int_value (sector_en, INT_TYPE_SECTOR_SIDE) != side)
	{
		(*enemy_sectors) ++;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *get_local_group_primary_task (entity *en)
{
	entity
		*guide,
		*task,
		*primary_task;

	entity_sub_types
		sub_type;

	int
		count;

	ASSERT (en);

	count = 0;

	primary_task = NULL;

	guide = get_local_entity_first_child (en, LIST_TYPE_GUIDE_STACK);

	while (guide)
	{
		task = get_local_entity_parent (guide, LIST_TYPE_GUIDE);

		sub_type = get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE);

		if (task_database [sub_type].primary_task)
		{
			count ++;

			primary_task = task;

			//
			// could break out / return here, but keep going to check that there is only one primary task
			//								
		}

		guide = get_local_entity_child_succ (guide, LIST_TYPE_GUIDE_STACK);
	}

	ASSERT (count <= 1);

	return primary_task;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *get_local_entity_primary_task (entity *en)
{
	entity
		*group;

	ASSERT (en);

	group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

	if (group)
	{
		return get_local_group_primary_task (group);
	}
	else
	{
		return NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define KEYSITE_TASK_IDLE_GROUP_COUNT_BIAS	5.0f

#define KEYSITE_TASK_BUSY_GROUP_COUNT_BIAS	0.5f

#define KEYSITE_TASK_MAX_GROUP_COUNT_BIAS		12.0f

#define KEYSITE_TASK_MAX_RANGE_BIAS				(100.0f * KILOMETRE)

#define KEYSITE_TASK_COUNT_BIAS					0.2f

entity *find_most_suitable_keysite_for_task (entity_sub_types task_type, entity_sides side, vec3d *pos, int check_capacity)
{

	int
		task_landing_types;

	float
		x,
		best_score,
		score,
		task_count,
		max_range,
		range;

	entity
		*force,
		*best_keysite,
		*ts,
		*group,
		*keysite;

	entity_sub_types
		group_type,
		keysite_type;

	vec3d
		*keysite_pos;

	ASSERT (pos);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	//
	// Find Entity types suitable for task
	//

	task_landing_types = task_database [task_type].landing_types;

	ASSERT (task_landing_types > 0);

	#if DEBUG_MODULE

	debug_log ("-------------------------------------");
	debug_log ("Task: %s", task_database [task_type].full_name);

	#endif

	//
	// Find closest keysite with lowest task count and most suitable groups
	//

	max_range = KEYSITE_TASK_MAX_RANGE_BIAS;

	force = get_local_force_entity (side);

	ASSERT (force);

	best_keysite = NULL;

	best_score = 0.0;

	keysite = get_local_entity_first_child (force, LIST_TYPE_KEYSITE_FORCE);

	while (keysite)
	{
		if (get_local_entity_int_value (keysite, INT_TYPE_IN_USE))
		{
			if (get_local_entity_first_child (keysite, LIST_TYPE_KEYSITE_GROUP))
			{
				if ((task_landing_types & (1 << ENTITY_SUB_TYPE_LANDING_GROUND)) || (get_local_entity_int_value (keysite, INT_TYPE_LANDING_TYPES) & task_landing_types))
				{
					keysite_type = get_local_entity_int_value (keysite, INT_TYPE_ENTITY_SUB_TYPE);

					if ((!check_capacity) || (keysite_database [keysite_type].air_force_capacity >= task_database [task_type].keysite_air_force_capacity))
					{
						score = 0.0;

						#if DEBUG_MODULE

						debug_log ("Keysite: %s", get_local_entity_string (keysite, STRING_TYPE_KEYSITE_NAME));

						#endif

						//
						// bias keysites with more groups suitable for this type
						//

						if (check_capacity)
						{
		
							group = get_local_entity_first_child (keysite, LIST_TYPE_KEYSITE_GROUP);
		
							while (group)
							{
								group_type = get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE); 
	
								if (get_group_to_task_suitability (group_type, task_type) > 0.0)
								{
									if (get_local_entity_int_value (group, INT_TYPE_ALIVE))
									{
										if (get_local_entity_int_value (group, INT_TYPE_GROUP_MODE) == GROUP_MODE_IDLE)
										{
											score += KEYSITE_TASK_IDLE_GROUP_COUNT_BIAS;
										}
										else
										{
											score += KEYSITE_TASK_BUSY_GROUP_COUNT_BIAS;
										}
									}
								}
		
								group = get_local_entity_child_succ (group, LIST_TYPE_KEYSITE_GROUP);
							}
		
							#if DEBUG_MODULE
	
							debug_log ("Group Score: %f", score);
	
							#endif
						}
						else
						{

							score = KEYSITE_TASK_MAX_GROUP_COUNT_BIAS;
						}

						if (score == 0.0)
						{
							keysite = get_local_entity_child_succ (keysite, LIST_TYPE_KEYSITE_FORCE);

							continue;
						}
						
						score = min (score, KEYSITE_TASK_MAX_GROUP_COUNT_BIAS);

						//
						// find distance between keysite and task origin
						//
							
						keysite_pos = get_local_entity_vec3d_ptr (keysite, VEC3D_TYPE_POSITION);
			
						range = get_approx_2d_range (keysite_pos, pos);

						#if DEBUG_MODULE

						debug_log ("Actual Range: %f", range);

						#endif

						if (range >= max_range)
						{
							keysite = get_local_entity_child_succ (keysite, LIST_TYPE_KEYSITE_FORCE);

							continue;
						}

						x = ((range / max_range) - 1);

						score *= 2.0 * (x * x * x * x);

						#if DEBUG_MODULE

						debug_log ("Range: %f (new score %f)", range, score);

						#endif

						//
						// bias keysites with less tasks of this type
						//
		
						task_count = 0.0;
		
						ts = get_local_entity_first_child (keysite, LIST_TYPE_UNASSIGNED_TASK);
		
						while (ts)
						{
							if (get_local_entity_int_value (ts, INT_TYPE_ENTITY_SUB_TYPE) == task_type)
							{
								task_count += 1.0;
							}
		
							ts = get_local_entity_child_succ (ts, LIST_TYPE_UNASSIGNED_TASK);
						}

						#if DEBUG_MODULE

						debug_log ("Actual Task count: %f", task_count);

						#endif

						task_count = 1.0 - (task_count * KEYSITE_TASK_COUNT_BIAS);

						task_count = max (task_count, KEYSITE_TASK_COUNT_BIAS);

						score *= task_count;

						#if DEBUG_MODULE

						debug_log ("Task bias: %f (new score %f)", task_count, score);

						#endif

						//
						// Less suitable if out-of-action / repairing
						//
							
						if (get_local_entity_int_value (keysite, INT_TYPE_KEYSITE_USABLE_STATE) != KEYSITE_STATE_USABLE)
						{
							score *= 0.5;
						}
							
						//
						// Check if best keysite
						//
		
						#if DEBUG_MODULE

						debug_log ("Final Score %f", score);

						#endif

						if (score > best_score)
						{
							best_keysite = keysite;
		
							best_score = score;

							#if DEBUG_MODULE

							debug_log ("!!** BEST SO FAR**!!");

							#endif
						}
					}

					#if DEBUG_MODULE

					debug_log ("                         ");

					#endif
				}
			}
		}

		keysite = get_local_entity_child_succ (keysite, LIST_TYPE_KEYSITE_FORCE);
	}

	return (best_keysite);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef DEBUG

void validate_task_entity (entity *en)
{
	entity_sub_types
		task_type;
	task
		*raw;
	
	ASSERT (en);

	raw = (task *) get_local_entity_data (en);

	task_type = get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);

	//
	// Check certain tasks have objective
	//

	switch (task_type)
	{
		case ENTITY_SUB_TYPE_TASK_ENGAGE:
		{
			if(!get_local_entity_parent (en, LIST_TYPE_TASK_DEPENDENT)) // target destroyed already, terminate task
				switch (raw->task_state)
				{
					case TASK_STATE_COMPLETED:
					case TASK_STATE_UNASSIGNED:
					{
						raw->expire_timer = 0.0001;

						break;
					}

					case TASK_STATE_ASSIGNED:
					{
						raw->stop_timer = 0.0001;

						break;
					}

				}

			break;
		}
		case ENTITY_SUB_TYPE_TASK_ESCORT:
		{
			if (!get_local_entity_int_value (en, INT_TYPE_TASK_COMPLETED))
			{
				ASSERT (get_local_entity_parent (en, LIST_TYPE_TASK_DEPENDENT));
			}

			break;
		}
	}
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_kill_to_task (entity *task_en, entity *victim, entity *aggressor)
{

	task
		*task_raw;

	task_kill_loss_data
		*new_kill;

	task_raw = (task *) get_local_entity_data (task_en);

	new_kill = (task_kill_loss_data *) malloc_heap_mem (sizeof (task_kill_loss_data));

	memset (new_kill, 0, sizeof (task_kill_loss_data));

	new_kill->victim_type = get_local_entity_type (victim);
	new_kill->aggressor_type = get_local_entity_type (aggressor);

	new_kill->victim_side = (entity_sides) get_local_entity_int_value (victim, INT_TYPE_SIDE);
	new_kill->aggressor_side = (entity_sides) get_local_entity_int_value (aggressor, INT_TYPE_SIDE);

	new_kill->victim_sub_type = get_local_entity_int_value (victim, INT_TYPE_ENTITY_SUB_TYPE);
	new_kill->aggressor_sub_type = get_local_entity_int_value (aggressor, INT_TYPE_ENTITY_SUB_TYPE);

	new_kill->victim_id = get_local_entity_int_value (victim, INT_TYPE_GROUP_MEMBER_ID);
	new_kill->aggressor_id = get_local_entity_int_value (aggressor, INT_TYPE_GROUP_MEMBER_ID);

	new_kill->time = get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_TIME_OF_DAY);

	new_kill->day = get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY);

	new_kill->next = task_raw->task_kills;
	task_raw->task_kills = new_kill;

	debug_log ("TASK: added kill to task %s (%d)", get_local_entity_string (task_en, STRING_TYPE_FULL_NAME), get_local_entity_index (task_en));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_loss_to_task (entity *task_en, entity *victim, entity *aggressor)
{

	task
		*task_raw;

	task_kill_loss_data
		*new_loss;

	task_raw = (task *) get_local_entity_data (task_en);

	new_loss = (task_kill_loss_data *) malloc_heap_mem (sizeof (task_kill_loss_data));

	memset (new_loss, 0, sizeof (task_kill_loss_data));

	new_loss->victim_type = get_local_entity_type (victim);
	new_loss->aggressor_type = get_local_entity_type (aggressor);

	new_loss->victim_side = (entity_sides) get_local_entity_int_value (victim, INT_TYPE_SIDE);
	new_loss->aggressor_side = (entity_sides) get_local_entity_int_value (aggressor, INT_TYPE_SIDE);

	new_loss->victim_sub_type = get_local_entity_int_value (victim, INT_TYPE_ENTITY_SUB_TYPE);
	new_loss->aggressor_sub_type = get_local_entity_int_value (aggressor, INT_TYPE_ENTITY_SUB_TYPE);

	new_loss->victim_id = get_local_entity_int_value (victim, INT_TYPE_GROUP_MEMBER_ID);
	new_loss->aggressor_id = get_local_entity_int_value (aggressor, INT_TYPE_GROUP_MEMBER_ID);

	new_loss->time = get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_TIME_OF_DAY);

	new_loss->day = get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY);

	new_loss->next = task_raw->task_losses;
	task_raw->task_losses = new_loss;

	debug_log ("TASK: added loss to task %s (%d)", get_local_entity_string (task_en, STRING_TYPE_FULL_NAME), get_local_entity_index (task_en));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_task_estimated_route_duration (entity *task)
{

	entity
		*waypoint;

	float
		flight_time;

	waypoint = get_local_entity_first_child (task, LIST_TYPE_WAYPOINT);

	flight_time = 0.0;

	while (waypoint)
	{

		flight_time += get_local_entity_float_value (waypoint, FLOAT_TYPE_FLIGHT_TIME);

		waypoint = get_local_entity_child_succ (waypoint, LIST_TYPE_WAYPOINT);
	}

	return flight_time;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_completed_task_expire_time (float value)
{
	completed_task_expire_time = value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_completed_task_expire_time (void)
{
	return completed_task_expire_time;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char *get_task_objective_string (entity *en)
{
	entity
		*objective,
		*sector;

	entity_sub_types
		task_type;

	entity_sides
		side;

	task_objective_info_types
		info;

	vec3d
		*pos;

	ASSERT (en);

	objective = get_local_entity_parent (en, LIST_TYPE_TASK_DEPENDENT);

	task_type = get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);

	info = (task_objective_info_types) task_database [task_type].task_objective_info;

	//
	// If No Objective, Or Task specified NONE, Return NULL...
	//

	if (!objective)
	{
		return NULL;
	}

	if (info == TASK_OBJECTIVE_INFO_NONE)
	{
		return NULL;
	}

	side = (entity_sides) get_local_entity_int_value (en, INT_TYPE_SIDE);

	pos = get_local_entity_vec3d_ptr (objective, VEC3D_TYPE_POSITION);

	ASSERT (pos);

	sector = get_local_sector_entity (pos);

	ASSERT (sector);

	//
	// If Objective (obj) NOT Hidden By Fog, OR obj ALWAYS KNOWN, OR (obj FOG-OF-WAR KNOWN AND sector fog level > threshold)
	// Return Objective Name.....
	//
	
	if ((info == TASK_OBJECTIVE_INFO_ALWAYS_KNOWN)
										||
		(!get_local_entity_int_value (objective, INT_TYPE_HIDDEN_BY_FOG_OF_WAR))
										||
		((info == TASK_OBJECTIVE_INFO_FOG_OF_WAR_KNOWN) && (get_sector_fog_of_war_value (sector, side) > 0.1)))
	{
		if (get_local_entity_type (objective) == ENTITY_TYPE_KEYSITE)
		{
			return get_local_entity_string (objective, STRING_TYPE_KEYSITE_NAME);
		}
		else
		{
			return get_local_entity_string (objective, STRING_TYPE_FULL_NAME);
		}
	}

	//
	// Return 'Unknown'...
	//

	return "Unknown";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_task_objective_mfd_display_string (entity *en, char *s)
{
	entity
		*objective,
		*sector;

	entity_sub_types
		task_type;

	entity_sides
		side;

	task_objective_info_types
		info;

	vec3d
		*pos;

	ASSERT (s);

	ASSERT (en);

	objective = get_local_entity_parent (en, LIST_TYPE_TASK_DEPENDENT);

	task_type = get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);

	info = (task_objective_info_types) task_database [task_type].task_objective_info;

	sprintf (s, "Unknown");

	//
	// If No Objective, Or Task specified NONE, Return NULL...
	//

	if (!objective)
	{
		return;
	}

	if (info == TASK_OBJECTIVE_INFO_NONE)
	{
		return;
	}

	side = (entity_sides) get_local_entity_int_value (en, INT_TYPE_SIDE);

	pos = get_local_entity_vec3d_ptr (objective, VEC3D_TYPE_POSITION);

	ASSERT (pos);

	sector = get_local_sector_entity (pos);

	ASSERT (sector);

	//
	// If Objective (obj) NOT Hidden By Fog, OR obj ALWAYS KNOWN, OR (obj FOG-OF-WAR KNOWN AND sector fog level > threshold)
	// Return Objective Name.....
	//
	
	if ((info == TASK_OBJECTIVE_INFO_ALWAYS_KNOWN)
										||
		(!get_local_entity_int_value (objective, INT_TYPE_HIDDEN_BY_FOG_OF_WAR))
										||
		((info == TASK_OBJECTIVE_INFO_FOG_OF_WAR_KNOWN) && (get_sector_fog_of_war_value (sector, side) > 0.1)))
	{
		if (get_local_entity_type (objective) == ENTITY_TYPE_KEYSITE)
		{
			get_keysite_entity_mfd_display_name (objective, s);
		}
		else
		{
			sprintf (s, "%s", get_local_entity_string (objective, STRING_TYPE_FULL_NAME));
		}
	}

	//
	// Return 'Unknown'...
	//
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_task_friendly_fire_incidents (entity *task_en)
{

	task
		*task_raw;

	task_kill_loss_data
		*item;

	task_raw = (task *) get_local_entity_data (task_en);

	// check kill list

	item = task_raw->task_kills;

	if (item)
	{

		while (item)
		{

			if (item->victim_side == get_local_entity_int_value (task_en, INT_TYPE_SIDE))
			{

				return TRUE;
			}

			item = item->next;
		}
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
