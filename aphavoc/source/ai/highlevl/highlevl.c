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

#include "highlevl.h"

#include "../ai_misc/ai_route.h"
#include "../parser/parsgen.h"
#include "../taskgen/taskgen.h"
//#include "../faction/parser.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE   0

#define MAX_HIGHLEVEL_TARGET_CHECKS					160

#define MIN_TASK_CREATION_RATIO						0.75

#define CREATE_CAS_TASK_COUNT							2
#define MAX_SECTOR_CAS_TASK_COUNT					1

#define CREATE_BAI_TASK_COUNT							2
#define MAX_SECTOR_BAI_TASK_COUNT					1

#define CREATE_KEYSITE_STRIKE_TASK_COUNT			3
#define CREATE_OCA_STRIKE_TASK_COUNT				1
#define CREATE_OCA_SWEEP_TASK_COUNT					2
#define CREATE_TROOP_INSERTION_TASK_COUNT			2
#define CREATE_SEAD_TASK_COUNT						2

#define MAX_SECTOR_SEAD_TASK_COUNT					1

#define CREATE_TRANSFER_TASK_COUNT					3

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity
	*target_list [MAX_HIGHLEVEL_TARGET_CHECKS];

static float
	target_rating [MAX_HIGHLEVEL_TARGET_CHECKS];

#ifdef DEBUG

#define AI_LOG_FILENAME "AI.LOG"

static FILE
	*ai_log_file = NULL;

#endif

static float
	importance_rating,
	air_defence_rating,
	surface_defence_rating,
	base_distance_rating;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int add_high_level_ai_function (void ((*function) (void)), float frequency, float start_time);

static void create_advance_and_retreat_tasks (void);

static void create_bai_tasks (void);

static void create_cas_tasks (void);

static void create_keysite_strike_tasks (void);

static void create_oca_strike_tasks (void);

static void create_oca_sweep_tasks (void);

static void create_troop_insertion_tasks (void);

static void create_sead_tasks (void);

static void create_fixed_wing_transfer_tasks (void);

static void create_helicopter_transfer_tasks (void);

static void create_troop_patrol_tasks (void);

static void create_artillery_strike_tasks (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_high_level_ai (void)
{
	initialise_group_task_array ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_high_level_ai (void)
{
	deinitialise_group_task_array ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void start_high_level_ai ()
{
	//
	// SERVER ONLY
	//
	
	if (get_comms_model () == COMMS_MODEL_SERVER)
	{
		#ifdef DEBUG

		ai_log_file = safe_fopen (AI_LOG_FILENAME, "w");

		fclose (ai_log_file);

		#endif

		//
		// initialise influence maps
		//

		initialise_imaps ();

		normalise_importance_imaps ();
		
		normalise_base_distance_imaps ();
		
		normalise_air_defence_imaps ();
		
		normalise_surface_defence_imaps ();
		
		update_client_server_sector_side_count ();

		//
		// add update functions
		//

		// Task creation
		if (get_game_type () == GAME_TYPE_SKIRMISH)
		{
			add_high_level_ai_function (create_cas_tasks, 6.0 * ONE_MINUTE, 0.0);
	
			add_high_level_ai_function (create_sead_tasks, 10.0 * ONE_MINUTE, 2.0);
	
			add_high_level_ai_function (create_advance_and_retreat_tasks, 15.0 * ONE_MINUTE, 12.0);
	
			add_high_level_ai_function (create_artillery_strike_tasks, 12.0 * ONE_MINUTE, 8.0);
	
			add_high_level_ai_function (create_keysite_strike_tasks, 10.0 * ONE_MINUTE, 15.0);
	
			add_high_level_ai_function (create_troop_patrol_tasks, 5.0 * ONE_MINUTE, 30.0);
	
			add_high_level_ai_function (create_fixed_wing_transfer_tasks, 15.0 * ONE_MINUTE, 34.0);
	
			add_high_level_ai_function (create_troop_insertion_tasks, 6.0 * ONE_MINUTE, 60.0);
	
			add_high_level_ai_function (create_bai_tasks, 10.0 * ONE_MINUTE, 90.0);

			add_high_level_ai_function (create_helicopter_transfer_tasks, 10.0 * ONE_MINUTE, 3.0 * ONE_MINUTE);

			add_high_level_ai_function (create_oca_sweep_tasks, 20.0 * ONE_MINUTE, 4.0 * ONE_MINUTE);
	
			add_high_level_ai_function (create_oca_strike_tasks, 30.0 * ONE_MINUTE, 5.0 * ONE_MINUTE);
		}
		else
		{
			add_high_level_ai_function (create_cas_tasks, 15.0 * ONE_MINUTE, 0.0);
	
			add_high_level_ai_function (create_troop_patrol_tasks, 5.0 * ONE_MINUTE, 10.0);
	
			add_high_level_ai_function (create_advance_and_retreat_tasks, 12.0 * ONE_MINUTE, 12.0);
	
			add_high_level_ai_function (create_keysite_strike_tasks, 7.5 * ONE_MINUTE, 15.0);
	
			add_high_level_ai_function (create_artillery_strike_tasks, 15.0 * ONE_MINUTE, 45.0);
	
			add_high_level_ai_function (create_troop_insertion_tasks, 20.0 * ONE_MINUTE, 1.0 * ONE_MINUTE);

			add_high_level_ai_function (create_oca_sweep_tasks, 30.0 * ONE_MINUTE, 1.5 * ONE_MINUTE);
	
			add_high_level_ai_function (create_helicopter_transfer_tasks, 7.5 * ONE_MINUTE, 2.0 * ONE_MINUTE);
	
			add_high_level_ai_function (create_fixed_wing_transfer_tasks, 15.0 * ONE_MINUTE, 2.5 * ONE_MINUTE);
	
			add_high_level_ai_function (create_sead_tasks, 12.0 * ONE_MINUTE, 3.0 * ONE_MINUTE);
	
			add_high_level_ai_function (create_bai_tasks, 20.0 * ONE_MINUTE, 5.0 * ONE_MINUTE);

			add_high_level_ai_function (create_oca_strike_tasks, 30.0 * ONE_MINUTE, 6.5 * ONE_MINUTE);
		}
		
		// Normalise influence maps (takes values from sector entities and creates "bitmap" overview)
		add_high_level_ai_function (normalise_importance_imaps, 2.0 * ONE_MINUTE, 20.0);

		add_high_level_ai_function (normalise_base_distance_imaps, 2.0 * ONE_MINUTE, 40.0);

		add_high_level_ai_function (normalise_air_defence_imaps, 2.0 * ONE_MINUTE, 60.0);

		add_high_level_ai_function (normalise_surface_defence_imaps, 2.0 * ONE_MINUTE, 80.0);

		add_high_level_ai_function (update_client_server_sector_fog_of_war, FOG_OF_WAR_DECAY_RATE, 8.0);

		add_high_level_ai_function (update_client_server_sector_side_count, 1.0 * ONE_MINUTE, 15.0);

		// Campaign triggers
		add_high_level_ai_function (update_campaign_triggers, 1.0 * ONE_SECOND, 0.0);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stop_high_level_ai ()
{
	if (get_comms_model () == COMMS_MODEL_SERVER)
	{
		// Task creation
		remove_update_function (create_cas_tasks);

		remove_update_function (create_advance_and_retreat_tasks);

		remove_update_function (create_sead_tasks);

		remove_update_function (create_keysite_strike_tasks);

		remove_update_function (create_troop_patrol_tasks);

		remove_update_function (create_helicopter_transfer_tasks);

		remove_update_function (create_fixed_wing_transfer_tasks);

		remove_update_function (create_artillery_strike_tasks);

		remove_update_function (create_troop_insertion_tasks);

		remove_update_function (create_bai_tasks);

		remove_update_function (create_oca_strike_tasks);

		remove_update_function (create_oca_sweep_tasks);

		// Normalise influence maps (takes values from sector entities and creates "bitmap" overview)
		remove_update_function (normalise_importance_imaps);

		remove_update_function (normalise_base_distance_imaps);

		remove_update_function (normalise_air_defence_imaps);

		remove_update_function (normalise_surface_defence_imaps);

		remove_update_function (update_client_server_sector_fog_of_war);

		remove_update_function (update_client_server_sector_side_count);

		deinitialise_imaps ();

		// Campaign triggers
		remove_update_function (update_campaign_triggers);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int add_high_level_ai_function (void ((*function) (void)), float frequency, float start_time)
{
	float
		offset;

	//
	// expects frequency in seconds, and start time in elapsed seconds
	//

	ASSERT ((start_time >= 0.0) && (start_time < (24.0 * ONE_HOUR)));

	ASSERT ((frequency > 0.0) && (frequency <= (24.0 * ONE_HOUR)));

	ASSERT (fmod ((24.0f * ONE_HOUR), frequency) == 0.0);

	offset = fmod ((start_time - get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_ELAPSED_TIME)), frequency);

	while (offset < 0.0)
	{
		offset += frequency;
	}

	return add_update_function (function, frequency, offset);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_advance_and_retreat_tasks (void)
{

	unsigned int
		node;

	int
		original_node,
		count,
		side,
		loop,
		x,
		z,
		to_node,
		from_node,
		best_node;

	float
		best_rating,
		rating;

	vec3d
		*pos,
		*node_pos;

	group
		*group_raw;

	entity
		*force,
		*group;

	ai_log ("================================");
	ai_log ("CREATE ADVANCE AND RETREAT TASKS");
	ai_log ("--------------------------------");

	force = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

	while (force)
	{
		//
		// for each force spin through the list of frontline groups and select best group
		//
	
		memset (target_list, 0, sizeof (entity *) * MAX_HIGHLEVEL_TARGET_CHECKS);

		memset (target_rating, 0, sizeof (float) * MAX_HIGHLEVEL_TARGET_CHECKS);

		count = 0;

		side = (entity_sides) get_local_entity_int_value (force, INT_TYPE_SIDE);
	
		group = get_local_entity_first_child (force, LIST_TYPE_GROUND_REGISTRY);

		while ((group) && (count < MAX_HIGHLEVEL_TARGET_CHECKS))
		{
			group_raw = (struct GROUP *)get_local_entity_data (group);
	
			if (group_database [group_raw->sub_type].frontline_flag)
			{
				if (get_local_entity_int_value (group, INT_TYPE_ALIVE))
				{
					if ((get_local_entity_int_value (group, INT_TYPE_GROUP_MODE) != GROUP_MODE_BUSY) && (check_group_members_awake (group)))
					{
						ASSERT (count < MAX_HIGHLEVEL_TARGET_CHECKS);

						//
						// get sector
						//

						pos = get_local_entity_vec3d_ptr (group, VEC3D_TYPE_POSITION);
								
						get_x_sector (x, pos->x);
						get_z_sector (z, pos->z);

						//
						// Calculate group rating
						//

						rating = 0.0;
	
						// far from enemy base
						rating += (1.0 * (1.0 - get_imap_value (IMAP_BASE_DISTANCE, get_enemy_side (side), x, z)));

						// near to friendly base
						rating += (1.0 * (get_imap_value (IMAP_BASE_DISTANCE, (entity_sides)side, x, z)));

						//
						// Store
						//
	
						target_list [count] = group;

						target_rating [count] = rating;

						count ++;
					}
				}
			}

			group = get_local_entity_child_succ (group, LIST_TYPE_GROUND_REGISTRY);
		}
	
		//
		// Advance best group
		//

		if (count > 0)
		{
			debug_log ("HIGHLEVL: %s %d candidates for Advance/Retreat", entity_side_short_names [side], count);

			quicksort_entity_list (target_list, count, target_rating);

			for (loop = 0; loop < count; loop ++)
			{
				group = target_list [loop];
				
				group_raw = (struct GROUP *)get_local_entity_data (group);

				best_node = group_raw->route_node;
				from_node = group_raw->route_node;
	
				original_node = best_node;
		
				//
				// find warmest node to move to
				//
	
				best_rating = target_rating [loop];
		
				for (node = 0; node < road_nodes [group_raw->route_node].number_of_links; node ++)
				{
		
					to_node = road_nodes [group_raw->route_node].links [node].node;
	
					//
					// not occupied by allied group
					//
	
					if (road_nodes [to_node].side_occupying != group_raw->side)
					{
						if (get_road_link_breaks (from_node, to_node) == 0)
						{
							node_pos = &road_node_positions [to_node];

							if (point_inside_adjusted_map_area (node_pos))
							{
								get_x_sector (x, node_pos->x);
								get_z_sector (z, node_pos->z);
		
								//
								// Calculate group rating
								//
		
								rating = 0.0;
			
								// close to enemy base
								rating += (2.0f * get_imap_value (IMAP_BASE_DISTANCE, get_enemy_side (side), x, z));
		
								if (rating > best_rating)
								{
									best_rating = rating;
				
									best_node = to_node;
								}
							}
						}
					}
				}
	
				if (best_node != original_node)
				{
					if (notify_local_entity (ENTITY_MESSAGE_GROUND_FORCE_ADVANCE, group, NULL, best_node))
					{
						#if DEBUG_MODULE
	
						debug_filtered_log ("HIGHLEVL: Created Advance for %s (Rating %f -> %f)", get_local_entity_string (group, STRING_TYPE_FULL_NAME), target_rating [loop], best_rating);

						#endif

						ai_log ("(TASK) Side %s : Created Advance for %s (Rating %f -> %f)", entity_side_short_names [side], get_local_entity_string (group, STRING_TYPE_FULL_NAME), target_rating [loop], best_rating);

						//
						// Move one group at a time
						//

						break;
					}
				}
			}
		}

		force = get_local_entity_child_succ (force, LIST_TYPE_FORCE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_bai_tasks (void)
{
	entity_sides
		side,
		this_side;

	entity
		*group,
		*force,
		*sector,
		*new_task,
		*target_force;

	vec3d
		*pos;

	int
		x,
		z,
		loop,
		count;

	float
		priority,
		rating,
		ratio,
		max_rating;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ai_log ("================");
	ai_log ("CREATE BAI TASKS");
	ai_log ("----------------");

	force = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

	while (force)
	{
		//
		// for each force ( excluding our own ) spin through the list of frontline groups and select viable targets
		//
	
		memset (target_list, 0, sizeof (entity *) * MAX_HIGHLEVEL_TARGET_CHECKS);

		memset (target_rating, 0, sizeof (float) * MAX_HIGHLEVEL_TARGET_CHECKS);

		count = 0;

		this_side = (entity_sides) get_local_entity_int_value (force, INT_TYPE_SIDE);
	
		target_force = get_local_entity_first_child (get_session_entity(), LIST_TYPE_FORCE);
	
		while ((target_force) && (count < MAX_HIGHLEVEL_TARGET_CHECKS))
		{
			side = (entity_sides) get_local_entity_int_value (target_force, INT_TYPE_SIDE);
	
			if (side != this_side)
			{
				group = get_local_entity_first_child (target_force, LIST_TYPE_GROUND_REGISTRY);

				while ((group) && (count < MAX_HIGHLEVEL_TARGET_CHECKS))
				{
					if (get_local_entity_int_value (group, INT_TYPE_FRONTLINE) > 1)
					{
						if (get_local_entity_int_value (group, INT_TYPE_ALIVE))
						{
							if (get_local_entity_int_value (group, INT_TYPE_GROUP_LIST_TYPE) != LIST_TYPE_KEYSITE_GROUP)
							{
								ASSERT (count < MAX_HIGHLEVEL_TARGET_CHECKS);
	
								//
								// get sector
								//
	
								pos = get_local_entity_vec3d_ptr (group, VEC3D_TYPE_POSITION);
									
								get_x_sector (x, pos->x);
								get_z_sector (z, pos->z);
	
								//
								// Calculate group rating
								//
	
								importance_rating = get_imap_value (IMAP_IMPORTANCE, side, x, z);
	
								air_defence_rating = get_imap_value (IMAP_AIR_DEFENCE, side, x, z);
	
								surface_defence_rating = get_imap_value (IMAP_SURFACE_DEFENCE, side, x, z);
	
								base_distance_rating = get_imap_value (IMAP_BASE_DISTANCE, this_side, x, z);
	
								rating = 0.0;
	
								// low enemy importance
	//							rating += (2.0 - importance_rating);
								
								// low enemy S-A threat 
								rating += 2.0 * (1.0 - air_defence_rating);
	
								// high enemy S-S threat
	//							rating += (surface_defence_rating);
	
								// close to friendly base
								rating += 3.0 * (base_distance_rating);
	
								// friendly territory
								rating += 2.0f * get_local_sector_side_ratio (x, z, this_side);
	
								max_rating = 7.0;
	
								#if DEBUG_MODULE
	
								ai_log ("(TASK) %s BAI (%d) Group %s : IMP %.4f - AIR %.4f - SUR %.4f - DIST %.4f (Total %.3f / %.3f)",
												entity_side_short_names [this_side],
												count,
												get_local_entity_string (group, STRING_TYPE_FULL_NAME),
												importance_rating,
												air_defence_rating,
												surface_defence_rating,
												base_distance_rating,
												rating,
												max_rating);
	
								#endif
	
								//
								// Store
								//
	
								if (rating > 0.0)
								{
									target_list [count] = group;
		
									target_rating [count] = rating;
		
									count ++;
								}
							}
						}
					}

					group = get_local_entity_child_succ (group, LIST_TYPE_GROUND_REGISTRY);
				}
			}

			target_force = get_local_entity_child_succ (target_force, LIST_TYPE_FORCE);
		}

		//
		// Create BAI tasks
		//

		if (count > 0)
		{
			debug_log ("HIGHLEVL: %s %d candidates for BAI", entity_side_short_names [this_side], count);

			quicksort_entity_list (target_list, count, target_rating);

			count = min (count, CREATE_BAI_TASK_COUNT);

			ASSERT (target_rating [0] > 0.0);

			for (loop = 0; loop < count; loop ++)
			{
				ratio = target_rating [loop] / target_rating [0];

				if (ratio >= MIN_TASK_CREATION_RATIO)
				{
					group = target_list [loop];
					
					if (!entity_is_object_of_task (group, ENTITY_SUB_TYPE_TASK_BAI, this_side))
					{
						pos = get_local_entity_vec3d_ptr (group, VEC3D_TYPE_POSITION);
									
						sector = get_local_sector_entity (pos);
	
						ASSERT (sector);
					
						// sector task count
						if (get_sector_task_type_count (sector, ENTITY_SUB_TYPE_TASK_BAI, this_side) < MAX_SECTOR_BAI_TASK_COUNT)
						{
							// fog of war 
							if (get_sector_fog_of_war_value (sector, this_side) > (0.5 * get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_FOG_OF_WAR_MAXIMUM_VALUE)))
							{
								//
								// Create BAI
								//
								
								priority = (target_rating [loop] / max_rating) * task_database [ENTITY_SUB_TYPE_TASK_BAI].task_priority;
		
								new_task = create_bai_task (this_side, group, NULL, FALSE, priority, NULL, NULL);
	
								if (new_task)
								{
									ai_log ("(TASK) %s BAI #%d (%d) - Target Group %s : Rating %f - CREATED (Priority %f)",
											entity_side_short_names [this_side],
											get_local_entity_int_value (new_task, INT_TYPE_TASK_ID),
											get_local_entity_safe_index (new_task),
											get_local_entity_string (group, STRING_TYPE_FULL_NAME),
											target_rating [loop], priority);
								}
							}
							else
							{
								//
								// Create RECON
								//
								
								priority = (target_rating [loop] / max_rating) * task_database [ENTITY_SUB_TYPE_TASK_BAI].task_priority;
		
								new_task = create_recon_task (this_side, group, NULL, TRUE, priority, NULL, NULL);
	
								if (new_task)
								{
									ai_log ("(TASK) %s BAI RECON #%d (%d) - Target Group %s : Rating %f - CREATED (Priority %f)",
											entity_side_short_names [this_side],
											get_local_entity_int_value (new_task, INT_TYPE_TASK_ID),
											get_local_entity_safe_index (new_task),
											get_local_entity_string (group, STRING_TYPE_FULL_NAME),
											target_rating [loop], priority);
								}
							}
						}
					}
				}
			}
		}

		//
		// Next force
		//
	
		force = get_local_entity_child_succ (force, LIST_TYPE_FORCE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_cas_tasks (void)
{
	entity_sides
		side,
		this_side;

	entity
		*group,
		*force,
		*sector,
		*new_task,
		*target_force;

	vec3d
		*pos;

	int
		x,
		z,
		loop,
		count;

	float
		priority,
		rating,
		ratio,
		max_rating;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ai_log ("================");
	ai_log ("CREATE CAS TASKS");
	ai_log ("----------------");

	force = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

	while (force)
	{
		//
		// for each force ( excluding our own ) spin through the list of frontline groups and select viable targets
		//
	
		memset (target_list, 0, sizeof (entity *) * MAX_HIGHLEVEL_TARGET_CHECKS);

		memset (target_rating, 0, sizeof (float) * MAX_HIGHLEVEL_TARGET_CHECKS);

		count = 0;

		this_side = (entity_sides) get_local_entity_int_value (force, INT_TYPE_SIDE);
	
		target_force = get_local_entity_first_child (get_session_entity(), LIST_TYPE_FORCE);
	
		while ((target_force) && (count < MAX_HIGHLEVEL_TARGET_CHECKS))
		{
			side = (entity_sides) get_local_entity_int_value (target_force, INT_TYPE_SIDE);
	
			if (side != this_side)
			{
				group = get_local_entity_first_child (target_force, LIST_TYPE_GROUND_REGISTRY);

				while ((group) && (count < MAX_HIGHLEVEL_TARGET_CHECKS))
				{
					if (get_local_entity_int_value (group, INT_TYPE_FRONTLINE) == 1)
					{
						if (get_local_entity_int_value (group, INT_TYPE_ALIVE))
						{
							if (get_local_entity_int_value (group, INT_TYPE_GROUP_LIST_TYPE) != LIST_TYPE_KEYSITE_GROUP)
							{
								ASSERT (count < MAX_HIGHLEVEL_TARGET_CHECKS);
	
								//
								// get sector
								//
	
								pos = get_local_entity_vec3d_ptr (group, VEC3D_TYPE_POSITION);
									
								get_x_sector (x, pos->x);
								get_z_sector (z, pos->z);
	
								//
								// Calculate group rating
								//
	
								importance_rating = get_imap_value (IMAP_IMPORTANCE, side, x, z);
	
								air_defence_rating = get_imap_value (IMAP_AIR_DEFENCE, side, x, z);
	
								surface_defence_rating = get_imap_value (IMAP_SURFACE_DEFENCE, side, x, z);
	
								base_distance_rating = get_imap_value (IMAP_BASE_DISTANCE, this_side, x, z);
	
								rating = 0.0;
	
								// low enemy importance
	//							rating += (2.0 - importance_rating);
	
								// low enemy S-A threat 
								rating += (1.0 - air_defence_rating);
	
								// low enemy S-S threat
	//							rating += 2.0 * (1.0 - surface_defence_rating);
	
								// close to friendly base
								rating += 3.0 * (base_distance_rating);
	
								// friendly territory
								rating += 2.0f * get_local_sector_side_ratio (x, z, this_side);
	
								max_rating = 6.0;
	
								#if DEBUG_MODULE
	
								ai_log ("(TASK) %s CAS (%d) Group %s : IMP %.4f - AIR %.4f - SUR %.4f - DIST %.4f (Total %.3f / %.3f)",
												entity_side_short_names [this_side],
												count,
												get_local_entity_string (group, STRING_TYPE_FULL_NAME),
												importance_rating,
												air_defence_rating,
												surface_defence_rating,
												base_distance_rating,
												rating,
												max_rating);
	
								#endif
	
								//
								// Store
								//
	
								if (rating > 0.0)
								{
									target_list [count] = group;
		
									target_rating [count] = rating;
		
									count ++;
								}
							}
						}
					}

					group = get_local_entity_child_succ (group, LIST_TYPE_GROUND_REGISTRY);
				}
			}

			target_force = get_local_entity_child_succ (target_force, LIST_TYPE_FORCE);
		}

		//
		// Create CAS tasks
		//

		if (count > 0)
		{
			debug_log ("HIGHLEVL: %s %d candidates for CAS", entity_side_short_names [this_side], count);

			quicksort_entity_list (target_list, count, target_rating);

			count = min (count, CREATE_CAS_TASK_COUNT);

			ASSERT (target_rating [0] > 0.0);

			for (loop = 0; loop < count; loop ++)
			{
				ratio = target_rating [loop] / target_rating [0];

				if (ratio >= MIN_TASK_CREATION_RATIO)
				{
					group = target_list [loop];
					
					if (!entity_is_object_of_task (group, ENTITY_SUB_TYPE_TASK_CLOSE_AIR_SUPPORT, this_side))
					{
						pos = get_local_entity_vec3d_ptr (group, VEC3D_TYPE_POSITION);
									
						sector = get_local_sector_entity (pos);
	
						ASSERT (sector);
					
						if (get_sector_task_type_count (sector, ENTITY_SUB_TYPE_TASK_CLOSE_AIR_SUPPORT, this_side) < MAX_SECTOR_CAS_TASK_COUNT)
						{
							priority = (target_rating [loop] / max_rating) * task_database [ENTITY_SUB_TYPE_TASK_CLOSE_AIR_SUPPORT].task_priority;
	
							new_task = create_close_air_support_task (this_side, group, NULL, FALSE, priority, NULL, NULL);
	
							if (new_task)
							{
								ai_log ("(TASK) %s CAS #%d (%d) - Target Group %s : Rating %f - CREATED (Priority %f)",
										entity_side_short_names [this_side],
										get_local_entity_int_value (new_task, INT_TYPE_TASK_ID),
										get_local_entity_safe_index (new_task),
										get_local_entity_string (group, STRING_TYPE_FULL_NAME),
										target_rating [loop], priority);
							}
						}
					}
				}
			}
		}

		//
		// Next force
		//
	
		force = get_local_entity_child_succ (force, LIST_TYPE_FORCE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_keysite_strike_tasks (void)
{
	entity_sides
		side,
		this_side;

	entity
		*force,
		*sector,
		*target_force,
		*new_task,
		*keysite;

	vec3d
		*pos;

	int
		x,
		z,
		loop,
		count,
		keysite_type;

	float
		priority,
		rating,
		ratio,
		max_rating;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ai_log ("==========================");
	ai_log ("CREATE KEYSITE STRIKE TASKS");
	ai_log ("--------------------------");

	force = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

	while (force)
	{
		//
		// for each force ( excluding our own ) spin through the list of keysites and select viable targets
		//
	
		memset (target_list, 0, sizeof (entity *) * MAX_HIGHLEVEL_TARGET_CHECKS);

		memset (target_rating, 0, sizeof (float) * MAX_HIGHLEVEL_TARGET_CHECKS);

		count = 0;

		this_side = (entity_sides) get_local_entity_int_value (force, INT_TYPE_SIDE);
	
		target_force = get_local_entity_first_child (get_session_entity(), LIST_TYPE_FORCE);
	
		while ((target_force) && (count < MAX_HIGHLEVEL_TARGET_CHECKS))
		{
			side = (entity_sides) get_local_entity_int_value (target_force, INT_TYPE_SIDE);
	
			if (side != this_side)
			{
				keysite = get_local_entity_first_child (target_force, LIST_TYPE_KEYSITE_FORCE);
	
				while ((keysite) && (count < MAX_HIGHLEVEL_TARGET_CHECKS))
				{
					if ((get_local_entity_int_value (keysite, INT_TYPE_IN_USE)) && (get_local_entity_int_value (keysite, INT_TYPE_ALIVE)))
					{
						keysite_type = get_local_entity_int_value (keysite, INT_TYPE_ENTITY_SUB_TYPE);

						if ((keysite_database [keysite_type].ground_strike_target) || (keysite_database [keysite_type].ship_strike_target))
						{
							ASSERT (count < MAX_HIGHLEVEL_TARGET_CHECKS);
	
							//
							// get sector
							//
	
							pos = get_local_entity_vec3d_ptr (keysite, VEC3D_TYPE_POSITION);
								
							get_x_sector (x, pos->x);
							get_z_sector (z, pos->z);
	
							//
							// Calculate keysite rating
							//
	
							rating = 0.0;
	
							// low enemy importance
//							rating += (1.0 * (1.0 - get_imap_value (IMAP_IMPORTANCE, side, x, z)));
	
							// low enemy S-A threat 
							rating += (1.0 * (1.0 - get_imap_value (IMAP_AIR_DEFENCE, side, x, z)));
	
							// close to friendly base
							rating += (4.0f * get_imap_value (IMAP_BASE_DISTANCE, this_side, x, z));

							// low efficiency 
							rating += (2.0 * (1.0 - get_local_entity_float_value (keysite, FLOAT_TYPE_EFFICIENCY)));

							// friendly territory
							rating += 2.0f * get_local_sector_side_ratio (x, z, this_side);

							max_rating = 9.0;

							//
							// Store
							//
	
							if (rating > 0.0)
							{
								target_list [count] = keysite;
		
								target_rating [count] = rating;
		
								count ++;
							}
						}
					}
	
					keysite = get_local_entity_child_succ (keysite, LIST_TYPE_KEYSITE_FORCE);
				}
			}

			target_force = get_local_entity_child_succ (target_force, LIST_TYPE_FORCE);
		}

		//
		// Create tasks
		//

		if (count > 0)
		{
			debug_log ("HIGHLEVL: %s %d candidates for STRIKE", entity_side_short_names [this_side], count);

			quicksort_entity_list (target_list, count, target_rating);

			count = min (count, CREATE_KEYSITE_STRIKE_TASK_COUNT);

			ASSERT (target_rating [0] > 0.0);

			for (loop = 0; loop < count; loop ++)
			{
				ratio = target_rating [loop] / target_rating [0];

				if (ratio >= MIN_TASK_CREATION_RATIO)
				{
					keysite = target_list [loop];
	
					sector = get_local_entity_parent (keysite, LIST_TYPE_SECTOR);
	
					ASSERT (sector);
					
					keysite_type = get_local_entity_int_value (keysite, INT_TYPE_ENTITY_SUB_TYPE);
	
					if ((keysite_database [keysite_type].recon_target) || (get_sector_fog_of_war_value (sector, this_side) < (0.25 * get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_FOG_OF_WAR_MAXIMUM_VALUE))))
					{
						//
						// KEYSITE REQUIRES RECON (Strike Created Upon Reaction
						//
	
						if (
								(!entity_is_object_of_task (keysite, ENTITY_SUB_TYPE_TASK_RECON, this_side)) &&
								(!entity_is_object_of_task (keysite, ENTITY_SUB_TYPE_TASK_BDA, this_side)) &&
								(!entity_is_object_of_task (keysite, ENTITY_SUB_TYPE_TASK_GROUND_STRIKE, this_side)) &&
								(!entity_is_object_of_task (keysite, ENTITY_SUB_TYPE_TASK_ANTI_SHIP_STRIKE, this_side)) &&
								(!entity_is_object_of_task (keysite, ENTITY_SUB_TYPE_TASK_TROOP_INSERTION, this_side))
							)
						{
							if (keysite_database [keysite_type].ground_strike_target)
							{
								priority = (target_rating [loop] / max_rating) * task_database [ENTITY_SUB_TYPE_TASK_GROUND_STRIKE].task_priority;
							}
							else
							{
								ASSERT (keysite_database [keysite_type].ship_strike_target);
									
								priority = (target_rating [loop] / max_rating) * task_database [ENTITY_SUB_TYPE_TASK_ANTI_SHIP_STRIKE].task_priority;
							}

							new_task = create_recon_task (this_side, keysite, NULL, FALSE, priority, NULL, NULL);
	
							if (new_task)
							{
								ai_log ("(TASK) %s KEYSITE RECON #%d (%d) - Target %s : Rating %f - CREATED (Priority %f)",
											entity_side_short_names [this_side],
											get_local_entity_int_value (new_task, INT_TYPE_TASK_ID),
											get_local_entity_safe_index (new_task),
											get_local_entity_string (keysite, STRING_TYPE_KEYSITE_NAME),
											target_rating [loop], priority);
							}
						}
					}
					else
					{
						//
						// KEYSITE REQUIRES NO RECON - Create Strike 
						//
	
						if (get_local_entity_float_value (keysite, FLOAT_TYPE_EFFICIENCY) >= keysite_database [keysite_type].minimum_efficiency)
						{
							if (
									(!entity_is_object_of_task (keysite, ENTITY_SUB_TYPE_TASK_GROUND_STRIKE, this_side)) &&
									(!entity_is_object_of_task (keysite, ENTITY_SUB_TYPE_TASK_ANTI_SHIP_STRIKE, this_side)) &&
									(!entity_is_object_of_task (keysite, ENTITY_SUB_TYPE_TASK_TROOP_INSERTION, this_side))
								)
							{
								if (keysite_database [keysite_type].ground_strike_target)
								{
									priority = (target_rating [loop] / max_rating) * task_database [ENTITY_SUB_TYPE_TASK_GROUND_STRIKE].task_priority;
		
									new_task = create_ground_strike_task (this_side, keysite, NULL, FALSE, priority, NULL, NULL);
		
									if (new_task)
									{
										ai_log ("(TASK) %s KEYSITE GROUND STRIKE #%d (%d) - Target %s : Rating %f - CREATED (Priority %f)",
													entity_side_short_names [this_side],
													get_local_entity_int_value (new_task, INT_TYPE_TASK_ID),
													get_local_entity_safe_index (new_task),
													get_local_entity_string (keysite, STRING_TYPE_KEYSITE_NAME),
													target_rating [loop], priority);
									}
								}
								else
								{
									ASSERT (keysite_database [keysite_type].ship_strike_target);
									
									priority = (target_rating [loop] / max_rating) * task_database [ENTITY_SUB_TYPE_TASK_ANTI_SHIP_STRIKE].task_priority;
		
									new_task = create_anti_ship_strike_task (this_side, keysite, NULL, FALSE, priority, NULL, NULL);
		
									if (new_task)
									{
										ai_log ("(TASK) %s KEYSITE SHIP STRIKE #%d (%d) - Target %s : Rating %f - CREATED (Priority %f)",
													entity_side_short_names [this_side],
													get_local_entity_int_value (new_task, INT_TYPE_TASK_ID),
													get_local_entity_safe_index (new_task),
													get_local_entity_string (keysite, STRING_TYPE_KEYSITE_NAME),
													target_rating [loop], priority);
									}
								}
							}
						}
					}
				}
			}
		}

		//
		// Next force
		//
	
		force = get_local_entity_child_succ (force, LIST_TYPE_FORCE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_oca_strike_tasks (void)
{
	entity_sides
		side,
		this_side;

	entity
		*force,
		*sector,
		*target_force,
		*new_task,
		*keysite;

	vec3d
		*pos;

	int
		x,
		z,
		loop,
		count,
		keysite_type;

	float
		priority,
		rating,
		ratio,
		max_rating;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ai_log ("==========================");
	ai_log ("CREATE OCA STRIKE TASKS");
	ai_log ("--------------------------");

	force = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

	while (force)
	{
		//
		// for each force ( excluding our own ) spin through the list of keysites and select viable targets
		//
	
		memset (target_list, 0, sizeof (entity *) * MAX_HIGHLEVEL_TARGET_CHECKS);

		memset (target_rating, 0, sizeof (float) * MAX_HIGHLEVEL_TARGET_CHECKS);

		count = 0;

		this_side = (entity_sides) get_local_entity_int_value (force, INT_TYPE_SIDE);
	
		target_force = get_local_entity_first_child (get_session_entity(), LIST_TYPE_FORCE);
	
		while ((target_force) && (count < MAX_HIGHLEVEL_TARGET_CHECKS))
		{
			side = (entity_sides) get_local_entity_int_value (target_force, INT_TYPE_SIDE);
	
			if (side != this_side)
			{
				keysite = get_local_entity_first_child (target_force, LIST_TYPE_KEYSITE_FORCE);
	
				while ((keysite) && (count < MAX_HIGHLEVEL_TARGET_CHECKS))
				{
					if ((get_local_entity_int_value (keysite, INT_TYPE_IN_USE)) && (get_local_entity_int_value (keysite, INT_TYPE_ALIVE)))
					{
						keysite_type = get_local_entity_int_value (keysite, INT_TYPE_ENTITY_SUB_TYPE);

						if (keysite_database [keysite_type].oca_target) 
						{
							ASSERT (count < MAX_HIGHLEVEL_TARGET_CHECKS);
	
							//
							// get sector
							//
	
							pos = get_local_entity_vec3d_ptr (keysite, VEC3D_TYPE_POSITION);
								
							get_x_sector (x, pos->x);
							get_z_sector (z, pos->z);
	
							//
							// Calculate keysite rating
							//
	
							rating = 0.0;
	
							// low enemy S-A threat 
							rating += (1.0 * (1.0 - get_imap_value (IMAP_AIR_DEFENCE, side, x, z)));
	
							// close to friendly base
							rating += (4.0f * get_imap_value (IMAP_BASE_DISTANCE, this_side, x, z));

							// friendly territory
							rating += (2.0f * get_local_sector_side_ratio (x, z, this_side));

							max_rating = 7.0;

							//
							// Store
							//
	
							if (rating > 0.0)
							{
								target_list [count] = keysite;
		
								target_rating [count] = rating;
		
								count ++;
							}
						}
					}
	
					keysite = get_local_entity_child_succ (keysite, LIST_TYPE_KEYSITE_FORCE);
				}
			}

			target_force = get_local_entity_child_succ (target_force, LIST_TYPE_FORCE);
		}

		//
		// Create tasks
		//

		if (count > 0)
		{
			debug_log ("HIGHLEVL: %s %d candidates for OCA STRIKE", entity_side_short_names [this_side], count);

			quicksort_entity_list (target_list, count, target_rating);

			count = min (count, CREATE_OCA_STRIKE_TASK_COUNT);

			ASSERT (target_rating [0] > 0.0);

			for (loop = 0; loop < count; loop ++)
			{
				ratio = target_rating [loop] / target_rating [0];

				if (ratio >= MIN_TASK_CREATION_RATIO)
				{
					keysite = target_list [loop];
	
					sector = get_local_entity_parent (keysite, LIST_TYPE_SECTOR);
	
					ASSERT (sector);
					
					keysite_type = get_local_entity_int_value (keysite, INT_TYPE_ENTITY_SUB_TYPE);
	
					if (get_sector_fog_of_war_value (sector, this_side) >= (0.25 * get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_FOG_OF_WAR_MAXIMUM_VALUE)))
					{
                  if (
                        (!entity_is_object_of_task (keysite, ENTITY_SUB_TYPE_TASK_OCA_STRIKE, this_side)) &&
                        (!entity_is_object_of_task (keysite, ENTITY_SUB_TYPE_TASK_BDA, this_side)) &&
                        (!entity_is_object_of_task (keysite, ENTITY_SUB_TYPE_TASK_TROOP_INSERTION, this_side))
                     )
						{
							priority = (target_rating [loop] / max_rating) * task_database [ENTITY_SUB_TYPE_TASK_OCA_STRIKE].task_priority;
		
							new_task = create_oca_strike_task (this_side, keysite, NULL, TRUE, priority, NULL, NULL);
		
							if (new_task)
							{
								ai_log ("(TASK) %s OCA STRIKE #%d (%d) - Target %s : Rating %f - CREATED (Priority %f)",
													entity_side_short_names [this_side],
													get_local_entity_int_value (new_task, INT_TYPE_TASK_ID),
													get_local_entity_safe_index (new_task),
													get_local_entity_string (keysite, STRING_TYPE_KEYSITE_NAME),
													target_rating [loop], priority);
							}
						}
					}
				}
			}
		}

		//
		// Next force
		//
	
		force = get_local_entity_child_succ (force, LIST_TYPE_FORCE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_oca_sweep_tasks (void)
{
	entity_sides
		side,
		this_side;

	entity
		*force,
		*sector,
		*target_force,
		*new_task,
		*keysite;

	vec3d
		*pos;

	int
		x,
		z,
		loop,
		count,
		keysite_type;

	float
		priority,
		rating,
		ratio,
		max_rating;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ai_log ("==========================");
	ai_log ("CREATE OCA SWEEP TASKS");
	ai_log ("--------------------------");

	force = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

	while (force)
	{
		//
		// for each force ( excluding our own ) spin through the list of keysites and select viable targets
		//
	
		memset (target_list, 0, sizeof (entity *) * MAX_HIGHLEVEL_TARGET_CHECKS);

		memset (target_rating, 0, sizeof (float) * MAX_HIGHLEVEL_TARGET_CHECKS);

		count = 0;

		this_side = (entity_sides) get_local_entity_int_value (force, INT_TYPE_SIDE);
	
		target_force = get_local_entity_first_child (get_session_entity(), LIST_TYPE_FORCE);
	
		while ((target_force) && (count < MAX_HIGHLEVEL_TARGET_CHECKS))
		{
			side = (entity_sides) get_local_entity_int_value (target_force, INT_TYPE_SIDE);
	
			if (side != this_side)
			{
				keysite = get_local_entity_first_child (target_force, LIST_TYPE_KEYSITE_FORCE);
	
				while ((keysite) && (count < MAX_HIGHLEVEL_TARGET_CHECKS))
				{
					if ((get_local_entity_int_value (keysite, INT_TYPE_IN_USE)) && (get_local_entity_int_value (keysite, INT_TYPE_ALIVE)))
					{
						keysite_type = get_local_entity_int_value (keysite, INT_TYPE_ENTITY_SUB_TYPE);

						if (keysite_database [keysite_type].oca_target) 
						{
							ASSERT (count < MAX_HIGHLEVEL_TARGET_CHECKS);
	
							//
							// get sector
							//
	
							pos = get_local_entity_vec3d_ptr (keysite, VEC3D_TYPE_POSITION);
								
							get_x_sector (x, pos->x);
							get_z_sector (z, pos->z);
	
							//
							// Calculate keysite rating
							//
	
							rating = 0.0;
	
							// low enemy S-A threat 
							rating += (1.0 * (1.0 - get_imap_value (IMAP_AIR_DEFENCE, side, x, z)));
	
							// close to friendly base
							rating += (4.0f * get_imap_value (IMAP_BASE_DISTANCE, this_side, x, z));

							// friendly territory
							rating += (2.0f * get_local_sector_side_ratio (x, z, this_side));

							max_rating = 7.0;

							//
							// Store
							//
	
							if (rating > 0.0)
							{
								target_list [count] = keysite;
		
								target_rating [count] = rating;
		
								count ++;
							}
						}
					}
	
					keysite = get_local_entity_child_succ (keysite, LIST_TYPE_KEYSITE_FORCE);
				}
			}

			target_force = get_local_entity_child_succ (target_force, LIST_TYPE_FORCE);
		}

		//
		// Create tasks
		//

		if (count > 0)
		{
			debug_log ("HIGHLEVL: %s %d candidates for OCA SWEEP", entity_side_short_names [this_side], count);

			quicksort_entity_list (target_list, count, target_rating);

			count = min (count, CREATE_OCA_SWEEP_TASK_COUNT);

			ASSERT (target_rating [0] > 0.0);

			for (loop = 0; loop < count; loop ++)
			{
				ratio = target_rating [loop] / target_rating [0];

				if (ratio >= MIN_TASK_CREATION_RATIO)
				{
					keysite = target_list [loop];
	
					sector = get_local_entity_parent (keysite, LIST_TYPE_SECTOR);
	
					ASSERT (sector);
					
					keysite_type = get_local_entity_int_value (keysite, INT_TYPE_ENTITY_SUB_TYPE);
	
					if (get_sector_fog_of_war_value (sector, this_side) >= (0.25 * get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_FOG_OF_WAR_MAXIMUM_VALUE)))
					{
                  if (
                        (!entity_is_object_of_task (keysite, ENTITY_SUB_TYPE_TASK_OCA_SWEEP, this_side)) &&
                        (!entity_is_object_of_task (keysite, ENTITY_SUB_TYPE_TASK_BDA, this_side)) &&
                        (!entity_is_object_of_task (keysite, ENTITY_SUB_TYPE_TASK_TROOP_INSERTION, this_side))
                     )
                  {
							priority = (target_rating [loop] / max_rating) * task_database [ENTITY_SUB_TYPE_TASK_OCA_SWEEP].task_priority;
		
							new_task = create_oca_sweep_task (this_side, keysite, NULL, TRUE, priority, NULL, NULL);
		
							if (new_task)
							{
								ai_log ("(TASK) %s OCA SWEEP #%d (%d) - Target %s : Rating %f - CREATED (Priority %f)",
													entity_side_short_names [this_side],
													get_local_entity_int_value (new_task, INT_TYPE_TASK_ID),
													get_local_entity_safe_index (new_task),
													get_local_entity_string (keysite, STRING_TYPE_KEYSITE_NAME),
													target_rating [loop], priority);
							}
						}
					}
				}
			}
		}

		//
		// Next force
		//
	
		force = get_local_entity_child_succ (force, LIST_TYPE_FORCE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_troop_insertion_tasks (void)
{
	entity_sides
		side,
		this_side;

	entity
		*force,
		*sector,
		*target_force,
		*new_task,
		*keysite;

	vec3d
		*pos;

	int
		x,
		z,
		loop,
		count,
		keysite_type;

	float
		efficiency,
		priority,
		rating,
		ratio,
		max_rating;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ai_log ("============================");
	ai_log ("CREATE TROOP INSERTION TASKS");
	ai_log ("----------------------------");

	force = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

	while (force)
	{
		//
		// for each force ( excluding our own ) spin through the list of keysites and select viable targets
		//
	
		memset (target_list, 0, sizeof (entity *) * MAX_HIGHLEVEL_TARGET_CHECKS);

		memset (target_rating, 0, sizeof (float) * MAX_HIGHLEVEL_TARGET_CHECKS);

		count = 0;

		this_side = (entity_sides) get_local_entity_int_value (force, INT_TYPE_SIDE);
	
		target_force = get_local_entity_first_child (get_session_entity(), LIST_TYPE_FORCE);
	
		while ((target_force) && (count < MAX_HIGHLEVEL_TARGET_CHECKS))
		{
			side = (entity_sides) get_local_entity_int_value (target_force, INT_TYPE_SIDE);
	
			if (side != this_side)
			{
				keysite = get_local_entity_first_child (target_force, LIST_TYPE_KEYSITE_FORCE);
	
				while ((keysite) && (count < MAX_HIGHLEVEL_TARGET_CHECKS))
				{
					if ((get_local_entity_int_value (keysite, INT_TYPE_IN_USE)) && (get_local_entity_int_value (keysite, INT_TYPE_ALIVE)))
					{
						keysite_type = get_local_entity_int_value (keysite, INT_TYPE_ENTITY_SUB_TYPE);

						if (keysite_database [keysite_type].troop_insertion_target)
						{
							efficiency = get_local_entity_float_value (keysite, FLOAT_TYPE_EFFICIENCY);

							if (efficiency < keysite_database [keysite_type].minimum_efficiency)
							{
								ASSERT (count < MAX_HIGHLEVEL_TARGET_CHECKS);
		
								//
								// get sector
								//
		
								pos = get_local_entity_vec3d_ptr (keysite, VEC3D_TYPE_POSITION);
									
								get_x_sector (x, pos->x);
								get_z_sector (z, pos->z);
		
								//
								// Calculate keysite rating
								//
		
								rating = 0.0;
		
								// low enemy importance
//								rating += (1.0 * (1.0 - get_imap_value (IMAP_IMPORTANCE, side, x, z)));
		
								// low enemy S-A threat 
								rating += (1.0 * (1.0 - get_imap_value (IMAP_AIR_DEFENCE, side, x, z)));
		
								// close to friendly base
								rating += (3.0f * get_imap_value (IMAP_BASE_DISTANCE, this_side, x, z));
		
								// low efficiency 
								rating += (3.0 * (1.0 - get_local_entity_float_value (keysite, FLOAT_TYPE_EFFICIENCY)));

								// friendly territory
								rating += 2.0f * get_local_sector_side_ratio (x, z, this_side);

								max_rating = 9.0;
	
								//
								// Store
								//
		
								if (rating > 0.0)
								{
									target_list [count] = keysite;
			
									target_rating [count] = rating;
			
									count ++;
								}
							}
						}
					}
	
					keysite = get_local_entity_child_succ (keysite, LIST_TYPE_KEYSITE_FORCE);
				}
			}

			target_force = get_local_entity_child_succ (target_force, LIST_TYPE_FORCE);
		}

		//
		// Create tasks
		//

		if (count > 0)
		{
			debug_log ("HIGHLEVL: %s %d candidates for T.I", entity_side_short_names [this_side], count);

			quicksort_entity_list (target_list, count, target_rating);

			count = min (count, CREATE_TROOP_INSERTION_TASK_COUNT);

			ASSERT (target_rating [0] > 0.0);

			for (loop = 0; loop < count; loop ++)
			{
				ratio = target_rating [loop] / target_rating [0];

				if (ratio >= MIN_TASK_CREATION_RATIO)
				{
					keysite = target_list [loop];
	
					sector = get_local_entity_parent (keysite, LIST_TYPE_SECTOR);
	
					ASSERT (sector);
					
					keysite_type = get_local_entity_int_value (keysite, INT_TYPE_ENTITY_SUB_TYPE);
	
					if ((keysite_database [keysite_type].recon_target) || (get_sector_fog_of_war_value (sector, this_side) < (0.2 * get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_FOG_OF_WAR_MAXIMUM_VALUE))))
					{
						//
						// KEYSITE REQUIRES RECON (T.I. Created Upon Reaction)
						//
	
						if (
								(!entity_is_object_of_task (keysite, ENTITY_SUB_TYPE_TASK_RECON, this_side)) &&
								(!entity_is_object_of_task (keysite, ENTITY_SUB_TYPE_TASK_BDA, this_side)) &&
								(!entity_is_object_of_task (keysite, ENTITY_SUB_TYPE_TASK_TROOP_INSERTION, this_side))
							)
						{
							priority = (target_rating [loop] / max_rating) * task_database [ENTITY_SUB_TYPE_TASK_TROOP_INSERTION].task_priority;
	
							new_task = create_recon_task (this_side, keysite, NULL, FALSE, priority, NULL, NULL);
	
							if (new_task)
							{
								ai_log ("(TASK) %s KEYSITE T.I. RECON #%d (%d) - Target %s : Rating %f - CREATED (Priority %f)",
											entity_side_short_names [this_side],
											get_local_entity_int_value (new_task, INT_TYPE_TASK_ID),
											get_local_entity_safe_index (new_task),
											get_local_entity_string (keysite, STRING_TYPE_KEYSITE_NAME),
											target_rating [loop], priority);
							}
						}
					}
					else
					{
						//
						// KEYSITE REQUIRES NO RECON - Create T.I.
						//
	
						if (get_local_entity_int_value (keysite, INT_TYPE_KEYSITE_USABLE_STATE) != KEYSITE_STATE_USABLE)
						{
							if (
									(!entity_is_object_of_task (keysite, ENTITY_SUB_TYPE_TASK_TROOP_INSERTION, this_side))
								)
							{
								priority = (target_rating [loop] / max_rating) * task_database [ENTITY_SUB_TYPE_TASK_TROOP_INSERTION].task_priority;
		
								new_task = create_troop_insertion_task (this_side, keysite, NULL, TRUE, priority, NULL, NULL);
		
								if (new_task)
								{
									ai_log ("(TASK) %s TROOP INSERTION #%d (%d) - Target %s : Rating %f - CREATED (Priority %f)",
												entity_side_short_names [this_side],
												get_local_entity_int_value (new_task, INT_TYPE_TASK_ID),
												get_local_entity_safe_index (new_task),
												get_local_entity_string (keysite, STRING_TYPE_KEYSITE_NAME),
												target_rating [loop], priority);
								}
							}
						}
					}
				}
			}
		}

		//
		// Next force
		//
	
		force = get_local_entity_child_succ (force, LIST_TYPE_FORCE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_sead_tasks (void)
{
	entity_sides
		side,
		this_side;

	entity
		*group,
		*force,
		*sector,
		*new_task,
		*target_force;

	vec3d
		*pos;

	int
		x,
		z,
		loop,
		count,
		group_type;

	float
		priority,
		rating,
		ratio,
		max_rating;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	force = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

	while (force)
	{
		//
		// for each force ( excluding our own ) spin through the list of air defences and select viable targets
		//
	
		memset (target_list, 0, sizeof (entity *) * MAX_HIGHLEVEL_TARGET_CHECKS);

		memset (target_rating, 0, sizeof (float) * MAX_HIGHLEVEL_TARGET_CHECKS);

		count = 0;

		this_side = (entity_sides) get_local_entity_int_value (force, INT_TYPE_SIDE);
	
		target_force = get_local_entity_first_child (get_session_entity(), LIST_TYPE_FORCE);
	
		while ((target_force) && (count < MAX_HIGHLEVEL_TARGET_CHECKS))
		{
			side = (entity_sides) get_local_entity_int_value (target_force, INT_TYPE_SIDE);
	
			if (side != this_side)
			{
				group = get_local_entity_first_child (target_force, LIST_TYPE_GROUND_REGISTRY);

				while ((group) && (count < MAX_HIGHLEVEL_TARGET_CHECKS))
				{
					if (get_local_entity_int_value (group, INT_TYPE_ALIVE))
					{
						group_type = get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE); 

						if ((!group_database [group_type].frontline_flag) && (group_database [group_type].ai_stats.air_attack_strength == 10))
						{
							ASSERT (count < MAX_HIGHLEVEL_TARGET_CHECKS);

							//
							// get sector
							//

							pos = get_local_entity_vec3d_ptr (group, VEC3D_TYPE_POSITION);
								
							get_x_sector (x, pos->x);
							get_z_sector (z, pos->z);

							//
							// Calculate group rating
							//

							rating = 0.0;

							// low enemy importance
//							rating += (2.0 * (1.0 - get_imap_value (IMAP_IMPORTANCE, side, x, z)));

							// low enemy S-A threat
//							rating += (1.0 * (1.0 - get_imap_value (IMAP_AIR_DEFENCE, side, x, z)));

							// close to friendly base
							rating += (4.0f * get_imap_value (IMAP_BASE_DISTANCE, this_side, x, z));

							// friendly territory
							rating += (3.0f * get_local_sector_side_ratio (x, z, this_side));

//							max_rating = 10.0;
							max_rating = 7.0;

							//
							// Store
							//

							if (rating > 0.0)
							{
								target_list [count] = group;
	
								target_rating [count] = rating;
								
								count ++;
							}
						}
					}

					group = get_local_entity_child_succ (group, LIST_TYPE_GROUND_REGISTRY);
				}
			}

			target_force = get_local_entity_child_succ (target_force, LIST_TYPE_FORCE);
		}

		//
		// Create SEAD tasks
		//

		if (count > 0)
		{
			debug_log ("HIGHLEVL: %s %d candidates for SEAD", entity_side_short_names [this_side], count);

			quicksort_entity_list (target_list, count, target_rating);

			count = min (count, CREATE_SEAD_TASK_COUNT);

			ASSERT (target_rating [0] > 0.0);

			for (loop = 0; loop < count; loop ++)
			{
				ratio = target_rating [loop] / target_rating [0];

				if (ratio >= MIN_TASK_CREATION_RATIO)
				{
					group = target_list [loop];
					
					if (
							(!entity_is_object_of_task (group, ENTITY_SUB_TYPE_TASK_RECON, this_side)) &&
							(!entity_is_object_of_task (group, ENTITY_SUB_TYPE_TASK_SEAD, this_side))
						)
					{
						pos = get_local_entity_vec3d_ptr (group, VEC3D_TYPE_POSITION);
									
						sector = get_local_sector_entity (pos);
	
						ASSERT (sector);
					
						if (get_sector_task_type_count (sector, ENTITY_SUB_TYPE_TASK_SEAD, this_side) < MAX_SECTOR_SEAD_TASK_COUNT)
						{
							if (get_sector_fog_of_war_value (sector, this_side) >= (0.25 * get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_FOG_OF_WAR_MAXIMUM_VALUE)))
							{
								//
								// Create SEAD
								//
								
								priority = (target_rating [loop] / max_rating) * task_database [ENTITY_SUB_TYPE_TASK_SEAD].task_priority;
		
								new_task = create_sead_task (this_side, group, NULL, FALSE, priority, NULL, NULL);
	
								if (new_task)
								{
									ai_log ("(TASK) %s SEAD #%d (%d) - Target Sector %d, %d : Rating %f - CREATED (Priority %f)",
											entity_side_short_names [this_side],
											get_local_entity_int_value (new_task, INT_TYPE_TASK_ID),
											get_local_entity_safe_index (new_task),
											get_local_entity_int_value (sector, INT_TYPE_X_SECTOR),
											get_local_entity_int_value (sector, INT_TYPE_Z_SECTOR),
											target_rating [loop], priority);
								}
							}
							else
							{
								//
								// Create RECON
								//
								
								priority = (target_rating [loop] / max_rating) * task_database [ENTITY_SUB_TYPE_TASK_SEAD].task_priority;
	
								new_task = create_recon_task (this_side, group, NULL, TRUE, priority, NULL, NULL);
	
								if (new_task)
								{
									ai_log ("(TASK) %s SEAD RECON #%d (%d) - Target Sector %d, %d : Rating %f - CREATED (Priority %f)",
											entity_side_short_names [this_side],
											get_local_entity_int_value (new_task, INT_TYPE_TASK_ID),
											get_local_entity_safe_index (new_task),
											get_local_entity_int_value (sector, INT_TYPE_X_SECTOR),
											get_local_entity_int_value (sector, INT_TYPE_Z_SECTOR),
											target_rating [loop], priority);
								}
							}
						}
					}
				}
			}
		}

		//
		// Next force
		//
	
		force = get_local_entity_child_succ (force, LIST_TYPE_FORCE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_fixed_wing_transfer_tasks (void)
{
	entity_sides
		side,
		this_side;

	entity
		*force,
		*group,
		*keysite,
		*donar,
		*landing_en;

	landing
		*landing_raw;

	vec3d
		*pos;

	int
		x,
		z,
		loop,
		loop2,
		count,
		group_type,
		keysite_count;

	float
		priority,
		rating,
		idle_group_count,
		max_rating;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ai_log ("==========================");
	ai_log ("CREATE TRANSFER (FW) TASKS");
	ai_log ("--------------------------");

	force = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

	while (force)
	{
		//
		// for each force spin through the list of keysites and select ones in most need of transfer
		//
	
		memset (target_list, 0, sizeof (entity *) * MAX_HIGHLEVEL_TARGET_CHECKS);

		memset (target_rating, 0, sizeof (float) * MAX_HIGHLEVEL_TARGET_CHECKS);

		count = 0;

		this_side = (entity_sides) get_local_entity_int_value (force, INT_TYPE_SIDE);

		side = get_enemy_side (this_side);
	
		keysite = get_local_entity_first_child (force, LIST_TYPE_KEYSITE_FORCE);
	
		while ((keysite) && (count < MAX_HIGHLEVEL_TARGET_CHECKS))
		{
			if (get_local_entity_int_value (keysite, INT_TYPE_IN_USE))
			{
				if (get_local_entity_int_value (keysite, INT_TYPE_KEYSITE_USABLE_STATE) == KEYSITE_STATE_USABLE)
				{
					if (get_local_entity_landing_entity (keysite, ENTITY_SUB_TYPE_LANDING_FIXED_WING))
					{
						ASSERT (count < MAX_HIGHLEVEL_TARGET_CHECKS);
	
						//
						// Check group count
						//
	
						idle_group_count = 0.0;
	
						group = get_local_entity_first_child (keysite, LIST_TYPE_KEYSITE_GROUP);
	
						while (group)
						{
							group_type = get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE);
	
							if (group_database [group_type].default_landing_type == ENTITY_SUB_TYPE_LANDING_FIXED_WING)
							{
								if (get_local_entity_int_value (group, INT_TYPE_GROUP_MODE) == GROUP_MODE_IDLE)
								{
									idle_group_count += 1.0;
								}
							}
	
							group = get_local_entity_child_succ (group, LIST_TYPE_KEYSITE_GROUP);
						}	
		
						//
						// get sector
						//
		
						pos = get_local_entity_vec3d_ptr (keysite, VEC3D_TYPE_POSITION);
									
						get_x_sector (x, pos->x);
						get_z_sector (z, pos->z);
		
						//
						// Calculate keysite rating
						//
	
						importance_rating = get_imap_value (IMAP_IMPORTANCE, side, x, z);
	
						air_defence_rating = get_imap_value (IMAP_AIR_DEFENCE, side, x, z);
	
						surface_defence_rating = get_imap_value (IMAP_SURFACE_DEFENCE, side, x, z);
	
						base_distance_rating = get_imap_value (IMAP_BASE_DISTANCE, side, x, z);
	
						rating = 0.0;
		
						// high enemy importance
//						rating += (importance_rating);
	
						// high enemy S-A threat 
//						rating += (air_defence_rating);
	
						// high enemy S-S threat
//						rating += (surface_defence_rating);
	
						// close to enemy base
						rating += 4.0 * base_distance_rating;
	
						// low idle group count
						idle_group_count = min (idle_group_count, 4.0f) * 0.25;
	
						rating += 4.0 * (1.0 - idle_group_count);
	
						max_rating = 8.0;
	
						//
						// Store
						//
		
						if (rating > 0.0)
						{
							target_list [count] = keysite;
		
							target_rating [count] = rating;
		
							count ++;
						}
					}
				}
			}	

			keysite = get_local_entity_child_succ (keysite, LIST_TYPE_KEYSITE_FORCE);
		}

		//
		// Create TRANSFER tasks
		//

		if (count > 0)
		{
			quicksort_entity_list (target_list, count, target_rating);

			keysite_count = min (count / 2, CREATE_TRANSFER_TASK_COUNT);

			loop2 = count - 1;

			for (loop = 0; loop < keysite_count; loop ++)
			{
//				if ((target_rating [loop] > (max_rating * 0.5)) && (target_rating [loop2] < (max_rating * 0.5)))
				{
					keysite = target_list [loop];
	
					if (!entity_is_object_of_task (keysite, ENTITY_SUB_TYPE_TASK_TRANSFER_FIXED_WING, this_side))
					{
						//
						// Check landing sites free
						//
	
						landing_en = get_local_entity_landing_entity (keysite, ENTITY_SUB_TYPE_LANDING_FIXED_WING);
	
						ASSERT (landing_en);
						
						landing_raw = (landing*) get_local_entity_data (landing_en);
	
						//if (landing_raw->free_landing_sites >= 4)
						if (get_keysite_landing_sites_available (keysite, ENTITY_SUB_TYPE_LANDING_FIXED_WING))
						{
							donar = target_list [loop2];	
						
							priority = ((target_rating [loop] - target_rating [loop2]) / max_rating) * task_database [ENTITY_SUB_TYPE_TASK_TRANSFER_FIXED_WING].task_priority;
	
							create_transfer_task (this_side, ENTITY_SUB_TYPE_TASK_TRANSFER_FIXED_WING, priority, donar, keysite);
	
							ai_log ("(TASK) %s TRANSFER - From %s (%.3f) To %s (%.3f) - CREATED (Priority %f)",
										entity_side_short_names [this_side],
										get_local_entity_string (donar, STRING_TYPE_KEYSITE_NAME),
										target_rating [loop2],
										get_local_entity_string (keysite, STRING_TYPE_KEYSITE_NAME),
										target_rating [loop],
										priority);

							loop2 --;
						}
					}
				}
			}
		}

		//
		// Next force
		//
	
		force = get_local_entity_child_succ (force, LIST_TYPE_FORCE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_helicopter_transfer_tasks (void)
{
	entity_sides
		side,
		this_side;

	entity
		*force,
		*group,
		*keysite,
		*donar,
		*landing_en;

	landing
		*landing_raw;

	vec3d
		*pos;

	int
		x,
		z,
		loop,
		loop2,
		count,
		group_type,
		keysite_count;

	float
		priority,
		rating,
		idle_group_count,
		max_rating;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ai_log ("==========================");
	ai_log ("CREATE TRANSFER (HC) TASKS");
	ai_log ("--------------------------");

	force = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

	while (force)
	{
		//
		// for each force spin through the list of keysites and select ones in most need of transfer
		//
	
		memset (target_list, 0, sizeof (entity *) * MAX_HIGHLEVEL_TARGET_CHECKS);

		memset (target_rating, 0, sizeof (float) * MAX_HIGHLEVEL_TARGET_CHECKS);

		count = 0;

		this_side = (entity_sides) get_local_entity_int_value (force, INT_TYPE_SIDE);

		side = get_enemy_side (this_side);
	
		keysite = get_local_entity_first_child (force, LIST_TYPE_KEYSITE_FORCE);
	
		while ((keysite) && (count < MAX_HIGHLEVEL_TARGET_CHECKS))
		{
			if (get_local_entity_int_value (keysite, INT_TYPE_IN_USE))
			{
				if (get_local_entity_int_value (keysite, INT_TYPE_KEYSITE_USABLE_STATE) == KEYSITE_STATE_USABLE)
				{
					if (get_local_entity_landing_entity (keysite, ENTITY_SUB_TYPE_LANDING_HELICOPTER))
					{
						ASSERT (count < MAX_HIGHLEVEL_TARGET_CHECKS);
	
						//
						// Check group count
						//
	
						idle_group_count = 0.0;
	
						group = get_local_entity_first_child (keysite, LIST_TYPE_KEYSITE_GROUP);
	
						while (group)
						{
							group_type = get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE);
	
							if (group_database [group_type].default_landing_type == ENTITY_SUB_TYPE_LANDING_HELICOPTER)
							{
								if (get_local_entity_int_value (group, INT_TYPE_GROUP_MODE) == GROUP_MODE_IDLE)
								{
									idle_group_count += 1.0;
								}
							}
	
							group = get_local_entity_child_succ (group, LIST_TYPE_KEYSITE_GROUP);
						}	
		
						//
						// get sector
						//
		
						pos = get_local_entity_vec3d_ptr (keysite, VEC3D_TYPE_POSITION);
									
						get_x_sector (x, pos->x);
						get_z_sector (z, pos->z);
		
						//
						// Calculate keysite rating
						//
	
						importance_rating = get_imap_value (IMAP_IMPORTANCE, side, x, z);
	
						air_defence_rating = get_imap_value (IMAP_AIR_DEFENCE, side, x, z);
	
						surface_defence_rating = get_imap_value (IMAP_SURFACE_DEFENCE, side, x, z);
	
						base_distance_rating = get_imap_value (IMAP_BASE_DISTANCE, side, x, z);
	
						rating = 0.0;
		
						// high enemy importance
//						rating += (importance_rating);
	
						// high enemy S-A threat 
//						rating += (air_defence_rating);
	
						// high enemy S-S threat
//						rating += (surface_defence_rating);
	
						// close to enemy base
						rating += 4.0 * base_distance_rating;
	
						// low idle group count
						idle_group_count = min (idle_group_count, 4.0f) * 0.25;
	
						rating += 4.0 * (1.0 - idle_group_count);
	
						max_rating = 8.0;
	
						//
						// Store
						//
		
						if (rating > 0.0)
						{
							target_list [count] = keysite;
		
							target_rating [count] = rating;
		
							count ++;
						}
					}
				}
			}	

			keysite = get_local_entity_child_succ (keysite, LIST_TYPE_KEYSITE_FORCE);
		}

		//
		// Create TRANSFER tasks
		//

		if (count > 0)
		{
			quicksort_entity_list (target_list, count, target_rating);

			keysite_count = min (count / 2, CREATE_TRANSFER_TASK_COUNT);

			loop2 = count - 1;

			for (loop = 0; loop < keysite_count; loop ++)
			{
//				if ((target_rating [loop] > (max_rating * 0.5)) && (target_rating [loop2] < (max_rating * 0.5)))
				{
					keysite = target_list [loop];
	
					if (!entity_is_object_of_task (keysite, ENTITY_SUB_TYPE_TASK_TRANSFER_HELICOPTER, this_side))
					{
						//
						// Check landing sites free
						//
	
						landing_en = get_local_entity_landing_entity (keysite, ENTITY_SUB_TYPE_LANDING_HELICOPTER);
	
						ASSERT (landing_en);
						
						landing_raw = (landing*) get_local_entity_data (landing_en);
	
						//if (landing_raw->free_landing_sites >= 4)
						if (get_keysite_landing_sites_available (keysite, ENTITY_SUB_TYPE_LANDING_HELICOPTER))
						{
							donar = target_list [loop2];	
						
							priority = ((target_rating [loop] - target_rating [loop2]) / max_rating) * task_database [ENTITY_SUB_TYPE_TASK_TRANSFER_HELICOPTER].task_priority;
	
							create_transfer_task (this_side, ENTITY_SUB_TYPE_TASK_TRANSFER_HELICOPTER, priority, donar, keysite);
	
							ai_log ("(TASK) %s TRANSFER - From %s (%.3f) To %s (%.3f) - CREATED (Priority %f)",
										entity_side_short_names [this_side],
										get_local_entity_string (donar, STRING_TYPE_KEYSITE_NAME),
										target_rating [loop2],
										get_local_entity_string (keysite, STRING_TYPE_KEYSITE_NAME),
										target_rating [loop],
										priority);

							loop2 --;
						}
					}
				}
			}
		}

		//
		// Next force
		//
	
		force = get_local_entity_child_succ (force, LIST_TYPE_FORCE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_KEYSITE_SEAD_RANGE	(4.0 * KILOMETRE)

#define MAX_KEYSITE_SEAD_COUNT	3

int create_sead_tasks_around_keysite (entity *original_task, entity *keysite, entity_sides this_side)
{
	entity
		*force,
		*group,
		*new_task,
		*sector;
		
	entity_sides
		enemy_side;

	int
		count,
		group_type;

	vec3d
		*group_pos,
		*keysite_pos;

	float
		priority;

	ASSERT (keysite);

	enemy_side = (entity_sides) get_local_entity_int_value (keysite, INT_TYPE_SIDE);

	force = get_local_force_entity (enemy_side);

	ASSERT (force);

	count = 0;

	keysite_pos = get_local_entity_vec3d_ptr (keysite, VEC3D_TYPE_POSITION);

	priority = get_local_entity_float_value (original_task, FLOAT_TYPE_TASK_PRIORITY);
	
	group = get_local_entity_first_child (force, LIST_TYPE_INDEPENDENT_GROUP);

	while (group)
	{
		group_type = get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE);
		
		//
		// check group is AA
		//

		if (group_database [group_type].default_entity_type == ENTITY_TYPE_ANTI_AIRCRAFT)
		{
			//
			// check group is alive
			//

			if (get_local_entity_int_value (group, INT_TYPE_ALIVE))
			{
				//
				// check group is not already subject of task
				//

				if ((!entity_is_object_of_task (group, ENTITY_SUB_TYPE_TASK_SEAD, this_side)) &&
						(!entity_is_object_of_task (group, ENTITY_SUB_TYPE_TASK_RECON, this_side)))
				{
					//
					// check range from keysite
					//

					group_pos = get_local_entity_vec3d_ptr (group, VEC3D_TYPE_POSITION);

					if (get_sqr_2d_range (group_pos, keysite_pos) < (MAX_KEYSITE_SEAD_RANGE * MAX_KEYSITE_SEAD_RANGE))
					{
						//
						// check fog of war
						//		

						sector = get_local_sector_entity (group_pos);

						ASSERT (sector);
			
						if (get_sector_fog_of_war_value (sector, this_side) > (0.25 * get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_FOG_OF_WAR_MAXIMUM_VALUE)))
						{
							//
							// create task
							//

							new_task = create_sead_task (this_side, group, original_task, TRUE, priority, NULL, NULL);

							if (new_task)
							{
								ai_log ("(TASK) Side %s : Created SEAD #%d (%d) at %s in reaction to %s",
												entity_side_short_names [this_side],
												get_local_entity_int_value (new_task, INT_TYPE_TASK_ID),
												get_local_entity_safe_index (new_task),
												get_local_entity_string (keysite, STRING_TYPE_KEYSITE_NAME),
												get_local_entity_string (original_task, STRING_TYPE_FULL_NAME));
							}

							count ++;

							if (count == MAX_KEYSITE_SEAD_COUNT)
							{
								return count;
							}
						}
					}
				}
			}
		}

		group = get_local_entity_child_succ (group, LIST_TYPE_INDEPENDENT_GROUP);
	}

	return count;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_troop_patrol_tasks (void)
{
	entity
		*task,
		*group,
		*keysite,
		*force;

	entity_sides
		side;
		
	force = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

	while (force)
	{
		side = (entity_sides) get_local_entity_int_value (force, INT_TYPE_SIDE);
			
		keysite = get_local_entity_first_child (force, LIST_TYPE_KEYSITE_FORCE);
	
		while (keysite)
		{
			#if DEBUG_MODULE

			debug_log ("HIGHLEVL: Trying to create patrol task");

			#endif
			
			if (get_local_entity_int_value (keysite, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_KEYSITE_AIRBASE)
			{
				if (!entity_is_object_of_task (keysite, ENTITY_SUB_TYPE_TASK_TROOP_MOVEMENT_PATROL, side))
				{
					group = get_local_entity_first_child (keysite, LIST_TYPE_KEYSITE_GROUP);
					
					while (group)
					{
						if (get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_GROUP_INFANTRY_PATROL)
						{
							if (get_local_entity_int_value (group, INT_TYPE_GROUP_MODE) == GROUP_MODE_IDLE)
							{
								if (get_local_entity_int_value (group, INT_TYPE_ALIVE))
								{
									task = create_troop_movement_patrol_task (side, keysite);

									#if DEBUG_MODULE

									debug_log ("HIGHLEVL: created patrol task");

									#endif
									
									if (!assign_task_to_group (group, task, TASK_ASSIGN_ALL_MEMBERS))
									{
										destroy_client_server_entity (task);
									}
									else
									{
										break;
									}
								}
							}
						}
	
						group = get_local_entity_child_succ (group, LIST_TYPE_KEYSITE_GROUP);
					}
				}
			}

			keysite = get_local_entity_child_succ (keysite, LIST_TYPE_KEYSITE_FORCE);
		}
	
		force = get_local_entity_child_succ (force, LIST_TYPE_FORCE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_ARTILLERY_STRIKE_COUNT 5

void create_artillery_strike_tasks (void)
{
	entity_sides
		side,
		enemy_side;

	entity
		*group,
		*target,
		**group_list,
		**target_list,
		*sector,
		*force,
		*target_force;

	vec3d
		*pos,
		*target_pos;

	int
		result,
		assigned_count,
		group_count,
		target_sub_type,
		target_count,
		target_group_count,
		target_keysite_count,
		group_index,
		target_index;

	float
		range,
		max_range;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ai_log ("=============================");
	ai_log ("CREATE ARTILLERY STRIKE TASKS");
	ai_log ("-----------------------------");

	force = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

	while (force)
	{
		side = (entity_sides) get_local_entity_int_value (force, INT_TYPE_SIDE);

		enemy_side = get_enemy_side (side);

		target_force = get_local_force_entity (enemy_side);

		//
		// Store list of artillery groups
		//

		group_count = 0;

		group = get_local_entity_first_child (force, LIST_TYPE_GROUND_REGISTRY);

		while (group)
		{
			if (get_local_entity_int_value (group, INT_TYPE_FRONTLINE) == GROUP_FRONTLINE_FLAG_ARTILLERY)
			{
				group_count ++;
			}

			group = get_local_entity_child_succ (group, LIST_TYPE_GROUND_REGISTRY);
		}

		if (group_count > 0)
		{
			group_list = (entity**)malloc_fast_mem (sizeof (entity *) * group_count);

			group_count = 0;
	
			group = get_local_entity_first_child (force, LIST_TYPE_GROUND_REGISTRY);
	
			while (group)
			{
				if (get_local_entity_int_value (group, INT_TYPE_FRONTLINE) == GROUP_FRONTLINE_FLAG_ARTILLERY)
				{
					group_list [group_count] = group;

					group_count ++;
				}
	
				group = get_local_entity_child_succ (group, LIST_TYPE_GROUND_REGISTRY);
			}

			//
			// Count up possible targets (enemy frontline forces, keysites)
			//

			target_count = 0;

			// groups...
			target_group_count = 0;

			target = get_local_entity_first_child (target_force, LIST_TYPE_GROUND_REGISTRY);
	
			while (target)
			{
				if (get_local_entity_int_value (target, INT_TYPE_FRONTLINE) != GROUP_FRONTLINE_FLAG_NONE)
				{
					target_count ++;

					target_group_count ++;
				}
	
				target = get_local_entity_child_succ (target, LIST_TYPE_GROUND_REGISTRY);
			}

			// keysites...
			target_keysite_count = 0;

			target = get_local_entity_first_child (target_force, LIST_TYPE_KEYSITE_FORCE);
	
			while (target)
			{
				target_sub_type = get_local_entity_int_value (target, INT_TYPE_ENTITY_SUB_TYPE);

				if (keysite_database [target_sub_type].ground_strike_target)
				{
					if ((get_local_entity_int_value (target, INT_TYPE_IN_USE)) && (get_local_entity_int_value (target, INT_TYPE_ALIVE)))
					{
						target_count ++;
	
						target_keysite_count ++;
					}
				}

				target = get_local_entity_child_succ (target, LIST_TYPE_KEYSITE_FORCE);
			}

			//
			// Store targets in list
			//
	
			if (target_count > 0)
			{
				target_list = (entity**)malloc_fast_mem (sizeof (entity *) * target_count);
	
				target_count = 0;
		
				if (target_group_count > 0)
				{
					target = get_local_entity_first_child (target_force, LIST_TYPE_GROUND_REGISTRY);
		
					while (target)
					{
						if (get_local_entity_int_value (target, INT_TYPE_FRONTLINE) != GROUP_FRONTLINE_FLAG_NONE)
						{
							target_list [target_count] = target;
	
							target_count ++;
						}
		
						target = get_local_entity_child_succ (target, LIST_TYPE_GROUND_REGISTRY);
					}
				}

				if (target_keysite_count > 0)
				{
					target = get_local_entity_first_child (target_force, LIST_TYPE_KEYSITE_FORCE);
			
					while (target)
					{
						target_sub_type = get_local_entity_int_value (target, INT_TYPE_ENTITY_SUB_TYPE);
		
						if (keysite_database [target_sub_type].ground_strike_target)
						{
							if ((get_local_entity_int_value (target, INT_TYPE_IN_USE)) && (get_local_entity_int_value (target, INT_TYPE_ALIVE)))
							{
								if (get_local_entity_float_value (target, FLOAT_TYPE_EFFICIENCY) >= get_local_entity_float_value (target, FLOAT_TYPE_MINIMUM_EFFICIENCY))
								{
									if (
											(!entity_is_object_of_task (target, ENTITY_SUB_TYPE_TASK_GROUND_STRIKE, side)) &&
											(!entity_is_object_of_task (target, ENTITY_SUB_TYPE_TASK_TROOP_INSERTION, side))
										)
									{
										target_list [target_count] = target;
	
										target_count ++;
									}
								}
							}
						}
		
						target = get_local_entity_child_succ (target, LIST_TYPE_KEYSITE_FORCE);
					}
				}

				//
				// Assign targets to groups
				// 

				assigned_count = 0;
				
				for (group_index = 0; group_index < group_count; group_index ++)
				{
					group = group_list [group_index];
					
					max_range = get_local_group_max_weapon_range (group);
	
					if (max_range > 0.0)
					{
						max_range *= max_range;

						pos = get_local_entity_vec3d_ptr (group, VEC3D_TYPE_POSITION);

						for (target_index = 0; target_index < target_count; target_index ++)
						{
							target = target_list [target_index];

							if (target)
							{
								target_pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);
			
								range = get_sqr_2d_range (pos, target_pos);

								if (range < max_range)
								{
									sector = get_local_sector_entity (target_pos);

									if (get_sector_fog_of_war_value (sector, side) > (0.25 * get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_FOG_OF_WAR_MAXIMUM_VALUE)))
									{
										if (get_local_entity_type (target) == ENTITY_TYPE_GROUP)
										{
											result = engage_targets_in_group (group, target, TRUE);
										}
										else
										{
											ASSERT (get_local_entity_type (target) == ENTITY_TYPE_KEYSITE);
											
											result = engage_targets_in_area (group, target_pos, 1.0 * KILOMETRE, TASK_TARGET_TYPE_BUILDING, TRUE);
										}

										if (result)
										{
											assigned_count ++;
	
											target_list [target_index] = NULL;
	
											ai_log ("(ARTILLERY) Group %d Attacking Target %d (%s) - sqr range %f",
															get_local_entity_index (group),
															get_local_entity_index (target),
															get_local_entity_string (target, STRING_TYPE_FULL_NAME),
															range);

											//
											// Create Reaction
											//
	
											create_reaction_to_artillery_fire (group, target);

											break;
										}
									}
								}
							}
						}
					}

					if ((assigned_count >= MAX_ARTILLERY_STRIKE_COUNT) || (assigned_count >= target_count))
					{
						break;
					}
				}
			
				free_mem (target_list);
			}

			free_mem (group_list);
		}

		//
		// Next force
		//
	
		force = get_local_entity_child_succ (force, LIST_TYPE_FORCE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef DEBUG

void ai_log (const char *string, ...)
{
	static char
		buffer[1000];

	char
		time_info[100];

	float
		elapsed_time;

	int
		elapsed_days,
		hours,
		minutes,
		seconds;

	va_list
		args;

	if (!ai_log_file)
	{
		return;
	}

	ASSERT (get_session_entity ());

	va_start (args, string);

	vsprintf (buffer, string, args);

	va_end (args);

	elapsed_time = get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_ELAPSED_TIME);

	convert_float_to_int (elapsed_time / ONE_DAY, &elapsed_days);

	elapsed_time = fmod (elapsed_time, ONE_DAY);

	get_digital_clock_int_values (elapsed_time, &hours, &minutes, &seconds);

	sprintf (time_info, "Day %d %02d:%02d:%02d :- ", elapsed_days, hours, minutes, seconds);

	// JB 030311 Enable running out of separate directories
	ai_log_file = safe_fopen (AI_LOG_FILENAME, "a");

	if (ai_log_file)
	{
		fprintf (ai_log_file, time_info);
		fprintf (ai_log_file, buffer);
		fprintf (ai_log_file, "\n");
	
		fclose (ai_log_file);
	}
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
