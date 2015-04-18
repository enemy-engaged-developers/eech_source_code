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
#include "ai/taskgen/engage.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 	0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define TARGET_RANGE_WEIGHTING	 			(5.0)
#define TARGET_POTENTIAL_THREAT_WEIGHTING	(1.0)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void vehicle_target_scan (entity *en);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int check_vehicle_target_scan_valid (entity *en)
{
	entity
		*group;

	//
	// Is entity allowed to scan for targets
	//

	if (!get_local_entity_int_value (en, INT_TYPE_OFFENSIVE_CAPABILITY))
	{
		return FALSE;
	}

	if (get_local_entity_float_value (en, FLOAT_TYPE_TARGET_SCAN_DELAY) == 0.0)
	{
		return FALSE;
	}

	//
	// Is group allowed to engage (by default or overridden by force)
	//

	group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

	if (!group)
	{
		return FALSE;
	}

	if (!get_local_entity_int_value (group, INT_TYPE_ENGAGE_ENEMY))
	{
		#if DEBUG_MODULE

		debug_log ("VH_TGT: group %s not allowed to engage enemy", entity_sub_type_group_names [get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE)]);

		#endif

		return FALSE;
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_vehicle_target_scan (entity *en)
{
	if (check_vehicle_target_scan_valid (en))
	{
		vehicle_target_scan (en);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void vehicle_target_scan (entity *en)
{
	vehicle
		*raw;

	entity
		*task,
		*guide,
		*group,
		*target_group,
		*current_target;

	int
		target_count,
		debug = FALSE;

	task_target_source_types
		target_source;

	vec3d
		*pos;

#ifdef DEBUG
	debug = DEBUG_MODULE && en == get_external_view_entity ();
#endif

	guide = get_local_entity_parent (en, LIST_TYPE_FOLLOWER);

	if (guide)
	{
		entity *wp = get_local_entity_parent (guide, LIST_TYPE_CURRENT_WAYPOINT);
		
		if (wp)
			if (get_local_entity_int_value (wp, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_WAYPOINT_TROOP_PUTDOWN_POINT)
			{
				if (debug)
				{
					debug_log("VH_TGT: TROOP_PUTDOWN_POINT");
				}

				return;
			}
	}
	
	raw = (vehicle *) get_local_entity_data (en);

	raw->target_scan_timer -= get_delta_time (); 
		
	if (raw->target_scan_timer > 0.0)
	{
		return;
	}

	if (debug)
	{
		debug_log("VH_TGT: targets scan");
	}
	
	//
	// reset target_scan_timer (okay to use a random number as this is a server only variable)
	//
		
	raw->target_scan_timer = vehicle_database[raw->mob.sub_type].target_scan_delay * (1.0 + (sfrand1 () * 0.5));
		
	group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

	current_target = get_local_entity_parent (en, LIST_TYPE_TARGET);

	//
	// What type of target does task allow 
	//

	target_source = TASK_TARGET_SOURCE_SCAN_ALL;

	if (guide)
	{
		task = get_local_entity_parent (guide, LIST_TYPE_GUIDE);

		ASSERT (task);
		
		target_source = (task_target_source_types) get_local_entity_int_value (task, INT_TYPE_TASK_TARGET_SOURCE);
	}

	//
	//
	//

	switch (target_source)
	{
		case TASK_TARGET_SOURCE_TASK_OBJECTIVE:
		{
			if (debug)
			{
				debug_log("VH_TGT: TASK_TARGET_SOURCE_TASK_OBJECTIVE");
			}

			return;
		}

		case TASK_TARGET_SOURCE_NONE:
		case TASK_TARGET_SOURCE_SCAN_ALL:
		case TASK_TARGET_SOURCE_SCAN_AIR:
		{
			//
			// Only first member in a group to do targetting
			//

			if (get_local_entity_child_pred (en, LIST_TYPE_MEMBER))
			{
				if (debug)
				{
					debug_log("VH_TGT: Only first member in a group to do targetting");
				}

				return;
			}

			//
			// Just notify force entity of targets
			//

			target_group = get_vehicle_surface_to_air_scan_group_targets (en, &target_count);

			if ((target_group) && (target_count > 0))
			{
				if (debug)
				{
					debug_log ("VH_TGT: %s(%d) Scanned %d air group targets", get_local_entity_string (en, STRING_TYPE_SHORT_DISPLAY_NAME), get_local_entity_index (en), target_count);
				}

				/////////////////////////////////////////////////////////////////
				//
				// SPECIAL_EFFECT_HOOK FOR AIR TARGETS SIGHTED
				//
				/////////////////////////////////////////////////////////////////
				
				if (!current_target)
				{
					// PLAY_SPEECH (GC)
					//
					// [GC Introduction],
					// We have incoming enemy aircraft
	
					pos = get_local_entity_vec3d_ptr (target_group, VEC3D_TYPE_POSITION); 

					ASSERT (pos);

					get_speech_sector_coordinates (pos);

					play_client_server_speech
					(
						get_session_entity (),
						en,
						(entity_sides) raw->mob.side,
						ENTITY_SUB_TYPE_EFFECT_SOUND_RADIO_MESSAGE,
						SOUND_LOCALITY_RADIO,
						0.0,
						1.0,
						20.0,
						SPEECH_ORIGINATOR_GROUND_CONTROLLER,
						SPEECH_CATEGORY_SIGHTED_TARGETS,
						60.0,
						SPEECH_ARRAY_GC_MESSAGES, SPEECH_GC_INTRODUCTION,
						SPEECH_ARRAY_GC_MESSAGES, SPEECH_GC_INCOMING_ENEMY_AIRCRAFT_HEADING,
						SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [0],
						SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [1],
						SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [2],
						SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [3],
						SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [4],
						SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [5],
						-1
					);
				}
				else if (debug)
				{
					debug_log("VH_TGT: already has target");
				}

				/////////////////////////////////////////////////////////////////
				//
				//
				/////////////////////////////////////////////////////////////////

				engage_targets_in_group (group, target_group, TRUE);
			}

			if (target_source == TASK_TARGET_SOURCE_SCAN_AIR)
			{

				break;
			}
		}

		case TASK_TARGET_SOURCE_SCAN_GROUND:
		{
			//
			// Only first member in a group to do targetting
			//

			if (get_local_entity_child_pred (en, LIST_TYPE_MEMBER))
			{
				if (debug)
				{
					debug_log("VH_TGT: Only first member in a group to do targeting");
				}

				return;
			}

			//
			// Just notify force entity of targets
			//

			target_group = get_vehicle_surface_to_surface_scan_group_targets (en, &target_count);

			if ((target_group) && (target_count > 0))
			{
				if (debug)
				{
					debug_log ("VH_TGT: %s(%d) Scanned %d ground group targets", get_local_entity_string (en, STRING_TYPE_SHORT_DISPLAY_NAME), get_local_entity_index (en), target_count);
				}

				/////////////////////////////////////////////////////////////////
				//
				// SPECIAL_EFFECT_HOOK FOR GROUND TARGETS SIGHTED
				//
				/////////////////////////////////////////////////////////////////
				
				// PLAY_SPEECH (GC)
				//
				// [GC Introduction],
				// We have incoming enemy ground units

				if (!current_target)
				{
					pos = get_local_entity_vec3d_ptr (target_group, VEC3D_TYPE_POSITION); 

					ASSERT (pos);

					get_speech_sector_coordinates (pos);

					play_client_server_speech
					(
						get_session_entity (),
						en,
						(entity_sides) raw->mob.side,
						ENTITY_SUB_TYPE_EFFECT_SOUND_RADIO_MESSAGE,
						SOUND_LOCALITY_RADIO,
						0.0,
						0.8,
						40.0,
						SPEECH_ORIGINATOR_GROUND_CONTROLLER,
						SPEECH_CATEGORY_SIGHTED_TARGETS,
						90.0,
						SPEECH_ARRAY_GC_MESSAGES, SPEECH_GC_INTRODUCTION,
						SPEECH_ARRAY_GC_MESSAGES, SPEECH_GC_INCOMING_ENEMY_GROUND_UNITS_AT,
						SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [0],
						SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [1],
						SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [2],
						SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [3],
						SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [4],
						SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [5],
						-1
					);
				}
				else if (debug)
				{
					debug_log("VH_TGT: already has target");
				}

				/////////////////////////////////////////////////////////////////
				//
				//
				/////////////////////////////////////////////////////////////////

				engage_targets_in_group (group, target_group, TRUE);
			}

			break;
		}
	}

	return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *get_vehicle_surface_to_air_scan_group_targets (entity *source, int *target_count)
{
	int
		x_sec_org,
		z_sec_org,
		x_sec_min,
		z_sec_min,
		x_sec_max,
		z_sec_max,
		x_sec,
		z_sec,
		seed;

	int
		debug = FALSE;

	entity
		*group,
		*target,
		*member,
		*sec,
		*best_group,
		*best_target;

	entity_sides
		source_side;

	vec3d
		*source_position,
		*target_position;

	float
		source_air_scan_range,
		source_air_scan_floor,
		source_air_scan_ceiling,
		target_range,
		target_radar_altitude,
		target_select_criteria,
		best_target_select_criteria,
		weighting;

	ASSERT (source);

	(*target_count) = 0;

	//
	// find best scan range
	//

	group = get_local_entity_parent (source, LIST_TYPE_MEMBER);

	if (!group)
	{
		return NULL;
	}

	source_air_scan_range = 0.0;
	source_air_scan_ceiling = 0.0;
	source_air_scan_floor = 0.0;
	
	member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

	while (member)
	{
		source_air_scan_range = max (source_air_scan_range, get_local_entity_float_value (member, FLOAT_TYPE_AIR_SCAN_RANGE));
		source_air_scan_ceiling = max (source_air_scan_ceiling, get_local_entity_float_value (member, FLOAT_TYPE_AIR_SCAN_CEILING));
		source_air_scan_floor = max (source_air_scan_floor, get_local_entity_float_value (member, FLOAT_TYPE_AIR_SCAN_FLOOR));

		member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);

#ifdef DEBUG
		debug = DEBUG_MODULE && member == get_external_view_entity ();
#endif
	}

	group = NULL;

	best_target = NULL;

	best_group = NULL;

	if ((source_air_scan_range > 0.0) && ((source_air_scan_ceiling - source_air_scan_floor) > 0.0))
	{
		if (debug)
		{
			debug_log ("SURFACE TO AIR SCAN ->SOURCE: %s (index = %d) RANGE %.1f", get_local_entity_string (source, STRING_TYPE_FULL_NAME), get_local_entity_index (source), source_air_scan_range);
		}

		source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

		source_air_scan_ceiling += source_position->y;

		source_side = (entity_sides) get_local_entity_int_value (source, INT_TYPE_SIDE);

		////////////////////////////////////////
		//
		// get sector scan area
		//
		////////////////////////////////////////

		//DEBUG// cull down given field of view?

		get_x_sector (x_sec_org, source_position->x);
		get_z_sector (z_sec_org, source_position->z);

		ASSERT (sector_inside_map_area (x_sec_org, z_sec_org));

		get_x_sector (x_sec_min, source_position->x - source_air_scan_range);
		get_z_sector (z_sec_min, source_position->z - source_air_scan_range);

		get_x_sector (x_sec_max, source_position->x + source_air_scan_range);
		get_z_sector (z_sec_max, source_position->z + source_air_scan_range);

		x_sec_min = max (x_sec_min, MIN_MAP_X_SECTOR);
		z_sec_min = max (z_sec_min, MIN_MAP_Z_SECTOR);

		x_sec_max = min (x_sec_max, MAX_MAP_X_SECTOR);
		z_sec_max = min (z_sec_max, MAX_MAP_Z_SECTOR);

		////////////////////////////////////////
		//
		// sector scan
		//
		////////////////////////////////////////

		best_target_select_criteria = 0.0;

		for (z_sec = z_sec_min; z_sec <= z_sec_max; z_sec++)
		{
			for (x_sec = x_sec_min; x_sec <= x_sec_max; x_sec++)
			{
				sec = get_local_raw_sector_entity (x_sec, z_sec);

				target = get_local_entity_first_child (sec, LIST_TYPE_SECTOR);

				if (target)
				{
					do
					{
						////////////////////////////////////////
						//
						// simple target select criteria
						//
						////////////////////////////////////////

						if (target == source)
						{
							continue;
						}

						if (!get_local_entity_int_value (target, INT_TYPE_AIRBORNE_AIRCRAFT))
						{
							continue;
						}

						if (get_local_entity_int_value (target, INT_TYPE_TARGET_TYPE) == TARGET_TYPE_INVALID)
						{
							continue;
						}

						if (!get_local_entity_int_value (target, INT_TYPE_ALIVE))
						{
							continue;
						}

						if (get_local_entity_int_value (target, INT_TYPE_SIDE) == source_side)
						{
							continue;
						}

						group = get_local_entity_parent (target, LIST_TYPE_MEMBER);

						if (!group)
						{
							continue;
						}

						if ((group == best_group) && (get_local_entity_int_value (target, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI))
						{
							continue;
						}

						////////////////////////////////////////
						//
						// Source specific target selection
						//
						////////////////////////////////////////

						//
						// Check target altitude
						//

						target_radar_altitude = get_local_entity_float_value (target, FLOAT_TYPE_RADAR_ALTITUDE);

						if ((target_radar_altitude < source_air_scan_floor) || (target_radar_altitude > source_air_scan_ceiling))
						{
							continue;
						}

						//
						// allow for random tolerance
						//

						seed = get_client_server_entity_random_number_seed (source);

						if (target_radar_altitude < (source_air_scan_floor * (1.0 + (0.5 * frand1x (&seed)))))
						{
							continue;
						}

						//
						// Target range
						//
						
						target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

						target_range = get_approx_3d_range (source_position, target_position);

						//
						// adjust range if target is player - each jammer / radar turned off allows player to fly 10% closer
						//
						{
							float
								adj_range;

							adj_range = target_range;

							if (get_local_entity_int_value (target, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
							{
								if (!get_local_entity_int_value (target, INT_TYPE_RADAR_ON))
								{
									adj_range *= 1.1;
								}
								if (!get_local_entity_int_value (target, INT_TYPE_RADAR_JAMMER_ON))
								{
									adj_range *= 1.1;
								}
								if (!get_local_entity_int_value (target, INT_TYPE_INFRA_RED_JAMMER_ON))
								{
									adj_range *= 1.1;
								}
							}

							if (adj_range > (source_air_scan_range * get_local_entity_float_value (target, FLOAT_TYPE_RADAR_STEALTH_FACTOR)))
							{
								continue;
							}
						}

						(*target_count) ++;

						////////////////////////////////////////////////////////////////
						// Line of sight check
						////////////////////////////////////////////////////////////////

						if (get_local_entity_int_value (target, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
						{
							if (!check_entity_line_of_sight (source, target, (mobile_los_check_criteria) MOBILE_LOS_CHECK_ALL))
							{
								continue;
							}
						}
						else
						{
							if (!check_entity_line_of_sight (source, target, MOBILE_LOS_CHECK_COURSE_TERRAIN))
							{
								continue;
							}
						}

						////////////////////////////////////////
						//
						// weighted target select criteria
						//
						////////////////////////////////////////

						if (debug)
						{
							debug_log ("--->TARGET: %s (index = %d)", get_local_entity_type_name (target), get_local_entity_index (target));
						}

						////////////////////////////////////////

						target_select_criteria = 0.0;

						////////////////////////////////////////

						weighting = ((source_air_scan_range - target_range) / source_air_scan_range) * TARGET_RANGE_WEIGHTING;

						if (debug)
						{
							debug_log ("----->target range weighting = %.2f", weighting);
						}

						target_select_criteria += weighting;

						////////////////////////////////////////

						weighting = get_local_entity_float_value (target, FLOAT_TYPE_POTENTIAL_AIR_TO_SURFACE_THREAT) * TARGET_POTENTIAL_THREAT_WEIGHTING;

						if (debug)
						{
							debug_log ("----->target potential threat weighting = %.2f", weighting);
						}

						target_select_criteria += weighting;

						////////////////////////////////////////

						//DEBUG// target/source aspect (target looking at source)

						//DEBUG// target is targeting source

						//DEBUG// target already target (persuers - possibly check if persuer ok to fire, check incoming weapons)

						//DEBUG// weapon/target suitablity

						//DEBUG// weapon lock ok (min range, max range, etc.)

						//DEBUG// frand1 () * (1.0 - SOURCE force_morale?) * FORCE_MORALE_WEIGHTING?

						////////////////////////////////////////

						if (debug)
						{
							debug_log ("----->target select criteria = %.2f", target_select_criteria);
						}

						////////////////////////////////////////

						if (target_select_criteria > best_target_select_criteria)
						{
							best_target_select_criteria = target_select_criteria;

							best_target = target;

							best_group = group;
						}
					}
					while (target = get_local_entity_child_succ (target, LIST_TYPE_SECTOR));
				}
			}
		}
	}
	else if (debug)
	{
		debug_log (" NO SCAN - SURFACE TO AIR ->SOURCE: %s (index = %d)", get_local_entity_string (source, STRING_TYPE_FULL_NAME), get_local_entity_index (source));
	}

	return (best_group);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *get_vehicle_surface_to_surface_scan_group_targets (entity *source, int *target_count)
{
	int
		x_sec_org,
		z_sec_org,
		x_sec_min,
		z_sec_min,
		x_sec_max,
		z_sec_max,
		x_sec,
		z_sec;

	int
		debug = FALSE;

	entity
		*group,
		*target,
		*member,
		*sec,
		*best_group,
		*best_target;

	entity_sides
		source_side;

	vec3d
		*source_position,
		*target_position;

	float
		source_surface_scan_range,
		target_range,
		target_select_criteria,
		best_target_select_criteria,
		weighting;

	ASSERT (source);

	*target_count = 0;

#ifdef DEBUG
	debug = DEBUG_MODULE && source == get_external_view_entity ();
#endif

	//
	// find best scan range
	//

	group = get_local_entity_parent (source, LIST_TYPE_MEMBER);

	if (!group)
	{
		return NULL;
	}

	source_surface_scan_range = 0.0;
	
	member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

	while (member)
	{
		source_surface_scan_range = max (source_surface_scan_range, get_local_entity_float_value (member, FLOAT_TYPE_SURFACE_SCAN_RANGE));

		member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
	}

	best_target = NULL;

	best_group = NULL;

	group = NULL;

	if (source_surface_scan_range > 0.0)
	{
		if (debug)
		{
			debug_log ("SURFACE TO SURFACE ->SOURCE: %s (index = %d), RANGE %.1f", get_local_entity_string (source, STRING_TYPE_FULL_NAME), get_local_entity_index (source), source_surface_scan_range);
		}

		source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

		source_side = (entity_sides) get_local_entity_int_value (source, INT_TYPE_SIDE);

		////////////////////////////////////////
		//
		// get sector scan area
		//
		////////////////////////////////////////

		//DEBUG// cull down given field of view?

		get_x_sector (x_sec_org, source_position->x);
		get_z_sector (z_sec_org, source_position->z);

		ASSERT (sector_inside_map_area (x_sec_org, z_sec_org));

		get_x_sector (x_sec_min, source_position->x - source_surface_scan_range);
		get_z_sector (z_sec_min, source_position->z - source_surface_scan_range);

		get_x_sector (x_sec_max, source_position->x + source_surface_scan_range);
		get_z_sector (z_sec_max, source_position->z + source_surface_scan_range);

		x_sec_min = max (x_sec_min, MIN_MAP_X_SECTOR);
		z_sec_min = max (z_sec_min, MIN_MAP_Z_SECTOR);

		x_sec_max = min (x_sec_max, MAX_MAP_X_SECTOR);
		z_sec_max = min (z_sec_max, MAX_MAP_Z_SECTOR);

		////////////////////////////////////////
		//
		// sector scan
		//
		////////////////////////////////////////

		best_target_select_criteria = 0.0;

		for (z_sec = z_sec_min; z_sec <= z_sec_max; z_sec++)
		{
			for (x_sec = x_sec_min; x_sec <= x_sec_max; x_sec++)
			{
				sec = get_local_raw_sector_entity (x_sec, z_sec);

				target = get_local_entity_first_child (sec, LIST_TYPE_SECTOR);

				if (target)
				{
					do
					{
						////////////////////////////////////////
						//
						// simple target select criteria
						//
						////////////////////////////////////////

						if (target == source)
						{
							continue;
						}

						//
						// Allow vehicles and aircraft....
						//
						
						if ((!get_local_entity_int_value (target, INT_TYPE_IDENTIFY_AIRCRAFT)) && 
								(!get_local_entity_int_value (target, INT_TYPE_IDENTIFY_VEHICLE)))
						{
							continue;
						}

						//
						// ... But only aircraft that are on the ground
						//

						if (get_local_entity_int_value (target, INT_TYPE_AIRBORNE_AIRCRAFT))
						{
							continue;
						}

						if (get_local_entity_int_value (target, INT_TYPE_TARGET_TYPE) == TARGET_TYPE_INVALID)
						{
							continue;
						}

						group = get_local_entity_parent (target, LIST_TYPE_MEMBER);

						if (!group)
						{
							continue;
						}

						if (group == best_group)
						{
							continue;
						}

						if (!get_local_entity_int_value (target, INT_TYPE_ALIVE))
						{
							continue;
						}

						if (get_local_entity_int_value (target, INT_TYPE_SIDE) == source_side)
						{
							continue;
						}

						(*target_count) ++;

						////////////////////////////////////////
						//
						// Source specific target selection
						//
						////////////////////////////////////////

						//DEBUG// use squared range (faster and more accurate, weapons need to store squared min/max ranges)

						target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

						target_range = get_approx_3d_range (source_position, target_position);

						if (target_range > source_surface_scan_range)
						{
							continue;
						}

						////////////////////////////////////////
						//
						// weighted target select criteria
						//
						////////////////////////////////////////

						if (debug)
						{
							debug_log ("--->TARGET: %s (index = %d)", get_local_entity_type_name (target), get_local_entity_index (target));
						}

						////////////////////////////////////////

						target_select_criteria = 0.0;

						////////////////////////////////////////

						weighting = ((source_surface_scan_range - target_range) / source_surface_scan_range) * TARGET_RANGE_WEIGHTING;

						if (debug)
						{
							debug_log ("----->target range weighting = %.2f", weighting);
						}

						target_select_criteria += weighting;

						////////////////////////////////////////

						weighting = get_local_entity_float_value (target, FLOAT_TYPE_POTENTIAL_SURFACE_TO_SURFACE_THREAT) * TARGET_POTENTIAL_THREAT_WEIGHTING;

						if (debug)
						{
							debug_log ("----->target potential threat weighting = %.2f", weighting);
						}

						target_select_criteria += weighting;

						////////////////////////////////////////

						//DEBUG// target/source aspect (target looking at source)

						//DEBUG// target is targeting source

						//DEBUG// target already target (persuers - possibly check if persuer ok to fire, check incoming weapons)

						//DEBUG// weapon/target suitablity

						//DEBUG// weapon lock ok (min range, max range, etc.)

						//DEBUG// frand1 () * (1.0 - SOURCE force_morale?) * FORCE_MORALE_WEIGHTING?

						////////////////////////////////////////

						if (debug)
						{
							debug_log ("----->target select criteria = %.2f", target_select_criteria);
						}

						////////////////////////////////////////

						if (target_select_criteria > best_target_select_criteria)
						{
							best_target_select_criteria = target_select_criteria;

							best_target = target;

							best_group = group;
						}
					}
					while (target = get_local_entity_child_succ (target, LIST_TYPE_SECTOR));
				}
			}
		}
	}
	else if (debug)
	{
		debug_log (" NO SCAN - SURFACE TO SURFACE ->SOURCE: %s (index = %d)", get_local_entity_string (source, STRING_TYPE_FULL_NAME), get_local_entity_index (source));
	}

	return (best_group);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
