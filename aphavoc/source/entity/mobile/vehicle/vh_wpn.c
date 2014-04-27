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
#include "../../../ai/taskgen/engage.h" // for CIWS

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int vehicle_select_best_weapon (entity *en, entity *target);

static float get_fire_timer_difficulty_factor (entity *en);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_vehicle_weapon_fire (entity *en)
{
 	vehicle
      *raw;

	entity
		*target;

	int
		debug_flag = FALSE;

	float
		range,
		launch_angle_error;

	vec3d
		*pos,
		*target_pos,
		*weapon_vector,
		*weapon_to_target_vector;

	ASSERT (en);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

   raw = (vehicle *) get_local_entity_data (en);

	target = raw->mob.target_link.parent;

	#if DEBUG_MODULE

	if (en == get_external_view_entity ())
		debug_flag = DEBUG_MODULE;
	if (get_gunship_entity())
		if (en == (get_local_entity_parent (get_gunship_entity(), LIST_TYPE_TARGET)))
			debug_flag = DEBUG_MODULE;

	#endif

	// check vehicle not sleeping

	if (raw->sleep > 0.0)
	{
		if (debug_flag && (raw->target_fire_timer > 0.02 || raw->weapon_burst_timer))
		{
			debug_log ("VH_WPN: Not Firing - Sleeping (%.1f seconds left", raw->sleep);
		}

		pause_client_server_continuous_weapon_sound_effect (en, raw->selected_weapon);
		raw->weapon_salvo_timer = 0;
		raw->target_fire_timer = 0.01;		
		
		return;
	}

	// check valid target

	if (!target)
	{
		if (debug_flag && (raw->target_fire_timer > 0.02 || raw->weapon_burst_timer))
		{
			debug_log ("VH_WPN: Not Firing - No Target");
		}

		pause_client_server_continuous_weapon_sound_effect (en, raw->selected_weapon);
		raw->weapon_salvo_timer = 0;
		raw->target_fire_timer = 0.01;		
		
		return;
	}

	// Check Suppress AI fire

	if (get_local_entity_int_value (get_session_entity (), INT_TYPE_SUPPRESS_AI_FIRE))
	{
		if (debug_flag && (raw->target_fire_timer > 0.02 || raw->weapon_burst_timer))
		{
			debug_log ("VH_WPN: Not Firing - AI fire suppressed");
		}

		pause_client_server_continuous_weapon_sound_effect (en, raw->selected_weapon);
		raw->weapon_salvo_timer = 0.0;
		raw->target_fire_timer = 0.01;		

		return;
	}

	// check valid selected weapon

	if (!vehicle_select_best_weapon (en, target) && !raw->weapon_burst_timer)
	{
		if (debug_flag && (raw->target_fire_timer > 0.02))
		{
			debug_log ("VH_WPN: Not Firing - No weapon");
		}

		pause_client_server_continuous_weapon_sound_effect (en, raw->selected_weapon);
		raw->weapon_salvo_timer = 0.0;
		raw->target_fire_timer = 0.01;		

		return;
	}

	// check selected weapon is ready

	if (!raw->selected_weapon_system_ready)
	{
		if (debug_flag && (raw->target_fire_timer > 0.02 || raw->weapon_burst_timer))
		{
			debug_log ("VH_WPN: Not Firing - Weapon system not ready");
		}

		pause_client_server_continuous_weapon_sound_effect (en, raw->selected_weapon);
		raw->weapon_salvo_timer = 0.0;
		raw->target_fire_timer = 0.01;		

		return;
	}

	// Check range

	if (!raw->weapon_burst_timer)
	{
		pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

		target_pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

		range = get_3d_range (pos, target_pos);

		if ((range < weapon_database [raw->selected_weapon].min_range) || (range > weapon_database [raw->selected_weapon].max_range))
		{
			if (debug_flag && (raw->target_fire_timer > 0.02 || raw->weapon_burst_timer))
			{
				debug_log ("VH_WPN: Not Firing - out of range");
			}

			pause_client_server_continuous_weapon_sound_effect (en, raw->selected_weapon);
			raw->weapon_salvo_timer = 0.0;
			raw->target_fire_timer = 0.01;		

			return;
		}
	}

	// Check altitude for radar guided missiles

	if (get_local_entity_int_value (target, INT_TYPE_AIRBORNE_AIRCRAFT) && 
			(weapon_database [raw->selected_weapon].guidance_type == WEAPON_GUIDANCE_TYPE_SEMI_ACTIVE_RADAR || weapon_database [raw->selected_weapon].guidance_type == WEAPON_GUIDANCE_TYPE_ACTIVE_RADAR))
	{
		float
			min_alt,
			max_alt,
			altitude;

		int
			seed;

		altitude = get_local_entity_float_value (target, FLOAT_TYPE_RADAR_ALTITUDE);

		min_alt = get_local_entity_float_value (en, FLOAT_TYPE_AIR_SCAN_FLOOR);

		max_alt = get_local_entity_float_value (en, FLOAT_TYPE_AIR_SCAN_CEILING);

		seed = get_client_server_entity_random_number_seed (en);

		min_alt *= (1.0 + (0.5 * frand1x (&seed)));

		if ((altitude < min_alt) || (altitude > max_alt))
		{
			if (debug_flag && (raw->target_fire_timer > 0.02 || raw->weapon_burst_timer))
			{
				debug_log ("VH_WPN: Not Firing - altitude");
			}

			pause_client_server_continuous_weapon_sound_effect (en, raw->selected_weapon);
			raw->weapon_salvo_timer = 0.0;
			raw->target_fire_timer = 0.01;		

				return;
		}
	}

	// check within max launch angle error

	if (!get_local_entity_int_value (en, INT_TYPE_WEAPON_AND_TARGET_VECTORS_VALID))
	{
		if (debug_flag && (raw->target_fire_timer > 0.02 || raw->weapon_burst_timer))
		{
			debug_log ("VH_WPN: Not Firing - outside launch angle (1)");
		}

		pause_client_server_continuous_weapon_sound_effect (en, raw->selected_weapon);
		raw->weapon_salvo_timer = 0.0;
		raw->target_fire_timer = 0.01;		

		if (debug_flag && (raw->target_fire_timer > 0.02 || raw->weapon_burst_timer))
		{
			debug_log ("VH_WPN: Not Firing - outside launch angle (1)");
		}

		return;
	}

	weapon_vector = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_WEAPON_VECTOR);

	ASSERT (weapon_vector);

	weapon_to_target_vector = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_WEAPON_TO_TARGET_VECTOR);

	ASSERT (weapon_to_target_vector);

	launch_angle_error = acos (get_3d_unit_vector_dot_product (weapon_vector, weapon_to_target_vector));

	if (fabs (launch_angle_error) > weapon_database[raw->selected_weapon].max_launch_angle_error)
	{
		if (debug_flag && (raw->target_fire_timer > 0.02 || raw->weapon_burst_timer))
		{
			debug_log ("VH_WPN: Not Firing - outside launch angle (%f > %f)", deg(fabs (launch_angle_error)), deg(weapon_database[raw->selected_weapon].max_launch_angle_error));
		}

		pause_client_server_continuous_weapon_sound_effect (en, raw->selected_weapon);
		raw->weapon_salvo_timer = 0.0;
		raw->target_fire_timer = 0.01;		

		return;
	}

	// Check Line Of Sight (Non-projectile weapons only)

	if (!raw->weapon_burst_timer)
	{
		if (weapon_database[raw->selected_weapon].aiming_type != WEAPON_AIMING_TYPE_CALC_ANGLE_OF_PROJECTION)
		{
			if (!check_entity_line_of_sight (en, target, (mobile_los_check_criteria) MOBILE_LOS_CHECK_ALL))
			{
				if (debug_flag && (raw->target_fire_timer > 0.02 || raw->weapon_burst_timer))
				{
					debug_log ("VH_WPN: Not Firing - No Line Of Sight");
				}

				pause_client_server_continuous_weapon_sound_effect (en, raw->selected_weapon);
				raw->weapon_salvo_timer = 0.0;
				raw->target_fire_timer = 0.01;		

				return;
			}
		}
	}
		
	// Update fire timer (unless continuing burst)

	if (raw->weapon_burst_timer <= 0.0)
	{
		pause_client_server_continuous_weapon_sound_effect (en, raw->selected_weapon);

		if (raw->target_fire_timer > 0.0)
		{
			raw->target_fire_timer = max(0, raw->target_fire_timer - get_delta_time ());
			
			if (raw->target_fire_timer > 0.0)
				return;
		}
		else
		{
			int
				seed;

			raw->target_fire_timer = weapon_database [raw->selected_weapon].reload_time;

			seed = get_client_server_entity_random_number_seed (en);

			raw->target_fire_timer *= (1.0 + (0.333 * sfrand1x (&seed)));

			if ((target) && (get_local_entity_int_value (target, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI))
			{
				// then modify timer based on difficulty level

				raw->target_fire_timer *= get_fire_timer_difficulty_factor (target);
			}

			if (debug_flag)
			{
				debug_log("VH_WPN: Firing interval %f seconds", raw->target_fire_timer);
			}

			return;
		}
	}
	
	if (raw->weapon_burst_timer > 0)
	{
		raw->weapon_burst_timer = max(0, raw->weapon_burst_timer - get_delta_time ());

		if (raw->weapon_burst_timer > 0.0)
		{
			if (debug_flag >= 2)
			{
				debug_log ("VH_WPN: Continuing Burst");
			}
		}
		else
		{
			if (debug_flag)
			{
				debug_log ("VH_WPN: Stop Burst this frame");
			}

			pause_client_server_continuous_weapon_sound_effect (en, raw->selected_weapon);
			raw->weapon_salvo_timer = 0.0;
			
			return;
		}
	}

	// fire weapon

	if (debug_flag > 1)
	{
		debug_log ("VH_WPN: Firing weapon");
	}

	launch_client_server_weapon (en, raw->selected_weapon, FALSE);
	
	/////////////////////////////////////////////////////////////////
	//
	// SPECIAL_EFFECT_HOOK FOR LAUNCHING WEAPON
	//
	/////////////////////////////////////////////////////////////////

	//
	// If current weapon is WEAPON_NO_WEAPON it means the last one was just fired - set vehicle to re-arming
	//

	if (raw->selected_weapon == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
	{
		pause_client_server_continuous_weapon_sound_effect (en, raw->selected_weapon);
	}

//	if (raw->selected_weapon == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
//	{
//		entity
//			*group;
//
//		float
//			ammo,
//			sleep_time;
//
//		weapon_config_types
//			config_type;
//
//		pause_client_server_continuous_weapon_sound_effect (en, raw->selected_weapon);
//		raw->target_fire_timer = raw->weapon_salvo_timer = 0.0;
//
//		//
//		// set vehicle to rearming and decrease groups ammo
//		//
//
//		group = get_local_entity_parent (en, LIST_TYPE_MEMBER);
//
//		ASSERT (group);
//
////		sleep_time = get_local_entity_rearming_sleep_time (group);
//		sleep_time = 10;
//
//		set_local_entity_float_value (en, FLOAT_TYPE_SLEEP, sleep_time);
//
//		ammo = get_local_entity_float_value (group, FLOAT_TYPE_AMMO_SUPPLY_LEVEL);
//
//		ammo -= get_local_entity_float_value (en, FLOAT_TYPE_AMMO_ECONOMY) * AMMO_USAGE_ACCELERATOR;
//
//		ammo = bound (ammo, 0.0, 100.0);
//
//		set_local_entity_float_value (group, FLOAT_TYPE_AMMO_SUPPLY_LEVEL, ammo);
//
//		//
//		// set vehicle to rearmed
//		//
//
//		config_type = (weapon_config_types) get_local_entity_int_value (en, INT_TYPE_WEAPON_CONFIG_TYPE);
//
//		if (config_type == WEAPON_CONFIG_TYPE_UNARMED)
//		{
//			config_type = (weapon_config_types) get_local_entity_int_value (en, INT_TYPE_DEFAULT_WEAPON_CONFIG_TYPE);
//		}
//
//		set_client_server_entity_int_value (en, INT_TYPE_WEAPON_CONFIG_TYPE, config_type);
//
//		#if DEBUG_MODULE || DEBUG_SUPPLY
//
//		debug_log ("VH_WPN: SUPPLY_INFO: member %s (%d) rearmed, sleeping for %0.2f seconds (group ammo = %0.2f%%, fuel %0.2f%%)",
//						get_local_entity_string (en, STRING_TYPE_FULL_NAME),
//						get_local_entity_index (en),
//						sleep_time,
//						get_local_entity_float_value (group, FLOAT_TYPE_AMMO_SUPPLY_LEVEL),
//						get_local_entity_float_value (group, FLOAT_TYPE_FUEL_SUPPLY_LEVEL));
//
//		#endif
//	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int vehicle_select_best_weapon (entity *en, entity *target)
{
	entity
		*guide,
		*task;

	int
		weapon_type;

	ASSERT(target);
	ASSERT(en);
	
	//
	// Find best weapon
	//

	weapon_type = get_best_weapon_for_target (en, target, BEST_WEAPON_CRITERIA_ALL);

	//
	// abort engage task and re-arm if no suitable weapon
	//

	if (weapon_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
	{
		weapon_type = get_best_weapon_for_target (en, target, BEST_WEAPON_CRITERIA_MINIMAL);

		if (weapon_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
		{
			#if DEBUG_MODULE

			debug_log ("VH_WPN: %s (%d) Aborting engage task - no suitable weapon for %s (%d)",
										get_local_entity_string (en, STRING_TYPE_FULL_NAME),
										get_local_entity_index (en),
										get_local_entity_string (target, STRING_TYPE_FULL_NAME),
										get_local_entity_index (target));

			#endif

			guide = get_local_entity_parent (en, LIST_TYPE_FOLLOWER);

			if (guide)
			{
				task = get_local_entity_parent (guide, LIST_TYPE_GUIDE);

				ASSERT (task);

				notify_local_entity (ENTITY_MESSAGE_TASK_TERMINATED, task, en, TASK_TERMINATED_ABORTED);
			}
		}

		if (weapon_type != get_local_entity_int_value (en, INT_TYPE_SELECTED_WEAPON))
		{
			set_client_server_entity_int_value (en, INT_TYPE_SELECTED_WEAPON, weapon_type);
		}

		return FALSE;
	}
	else
	{
		if (weapon_type != get_local_entity_int_value (en, INT_TYPE_SELECTED_WEAPON))
		{
			set_client_server_entity_int_value (en, INT_TYPE_SELECTED_WEAPON, weapon_type);
		}

		return TRUE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_vehicle_decoy_release (entity *en)
{
	vehicle
		*raw;

	float
		range,
		velocity,
		time_to_impact;

	entity
		*persuer,
		*launched_weapon;

	vec3d
		*target_position,
		*weapon_position;

	ASSERT (en);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	raw = (vehicle *) get_local_entity_data (en);

	////////////////////////////////////////
	//
	// update timer
	//
	////////////////////////////////////////

	raw->decoy_release_timer -= get_delta_time ();

	if (raw->decoy_release_timer >= 0.0)
	{
		return;
	}

	raw->decoy_release_timer = 2.0 + frand1 ();

	////////////////////////////////////////
	//
	// validate
	//
	////////////////////////////////////////

	if (get_local_entity_float_value (en, FLOAT_TYPE_VELOCITY) > 0.1)
	{
		return;
	}

	persuer = get_local_entity_first_child (en, LIST_TYPE_TARGET);

	if (!persuer)
	{
		return;
	}

	if (!vehicle_database[raw->mob.sub_type].carries_smoke_grenades)
	{
		return;
	}

	launched_weapon = get_local_entity_first_child (en, LIST_TYPE_LAUNCHED_WEAPON);

	while (launched_weapon)
	{
		if (get_local_entity_int_value (launched_weapon, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_WEAPON_SMOKE_GRENADE)
		{
			return;
		}

		launched_weapon = get_local_entity_child_succ (launched_weapon, LIST_TYPE_LAUNCHED_WEAPON);
	}

	////////////////////////////////////////
	//
	// check all persuers
	//
	////////////////////////////////////////

	target_position = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	while (persuer)
	{
		if (get_local_entity_type (persuer) == ENTITY_TYPE_WEAPON)
		{
			if (get_local_entity_int_value (persuer, INT_TYPE_WEAPON_GUIDANCE_TYPE) != WEAPON_GUIDANCE_TYPE_NONE)
			{
				if (get_decoy_type_for_weapon (persuer) == ENTITY_SUB_TYPE_WEAPON_SMOKE_GRENADE)
				{
					weapon_position = get_local_entity_vec3d_ptr (persuer, VEC3D_TYPE_POSITION);

					range = get_approx_3d_range (weapon_position, target_position);

					velocity = get_local_entity_float_value (persuer, FLOAT_TYPE_VELOCITY);

					time_to_impact = range / max (velocity, 1.0f);

					if (time_to_impact < 10.0)
					{
						launch_client_server_weapon (en, ENTITY_SUB_TYPE_WEAPON_SMOKE_GRENADE, FALSE);

						break;
					}
				}
			}
		}

		persuer = get_local_entity_child_succ (persuer, LIST_TYPE_TARGET);
	}
}

void update_vehicle_missile_defence (entity *en)
{
	entity
		*group;
	vehicle
		*raw;
	entity
		*persuer,
		*rocket = NULL;

	ASSERT (en);
	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	raw = (vehicle *) get_local_entity_data (en);
	
	group = get_local_entity_parent (en, LIST_TYPE_MEMBER);
	ASSERT (group);

	persuer = get_local_entity_first_child (en, LIST_TYPE_TARGET);

	if (!persuer)
		return;
	
	while (persuer) // stick to the first launched rocket
	{
		if (get_local_entity_type (persuer) == ENTITY_TYPE_WEAPON)
			rocket = persuer;
		persuer = get_local_entity_child_succ (persuer, LIST_TYPE_TARGET);
	}

	if (rocket)
		if (rocket != raw->mob.target_link.parent) // target already engaged
		{
			entity_sub_types type = get_local_entity_int_value (rocket, INT_TYPE_ENTITY_SUB_TYPE);

			if (weapon_database[type].boost_time > 0) // missiles and rockets only
				if (vehicle_select_best_weapon (en, rocket))
				{
					engage_specific_target (group, rocket, 1, TRUE);

					return;
				}
		}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static struct FIRE_TIMER_DIFFICULTY_TABLE
{
	game_difficulty_settings
		difficulty;

	float
		timer_scale;

} fire_timer_difficulty_table [] =
	{
		GAME_DIFFICULTY_HARD,		0.66,
		GAME_DIFFICULTY_MEDIUM,		1.0,
		GAME_DIFFICULTY_EASY,		1.33,
		(game_difficulty_settings) -1
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_fire_timer_difficulty_factor (entity *en)
{
	int
		loop;

	entity
		*pilot_en;

	game_difficulty_settings
		difficulty;

	ASSERT (en);

	pilot_en = get_local_entity_first_child (en, LIST_TYPE_AIRCREW);

	if (pilot_en)
	{
		difficulty = (game_difficulty_settings) get_local_entity_int_value (pilot_en, INT_TYPE_DIFFICULTY_LEVEL);

		loop = 0;

		while (fire_timer_difficulty_table [loop].difficulty >= 0)
		{
			if (fire_timer_difficulty_table [loop].difficulty == difficulty)
			{
				return fire_timer_difficulty_table [loop].timer_scale;
			}

			loop ++;
		}

		debug_fatal ("VH_WPN: No fire timer modifier for difficulty level %d", difficulty);
	}

	return 1.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rearm_vehicle_weapons(entity *en)
{
		entity
			*group;
		float
			ammo;
		weapon_config_types
			config_type;
		weapon_package_status
			*package_status;
		int
			package;

		group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

		ASSERT (group);

		package_status = (weapon_package_status *) get_local_entity_ptr_value (en, PTR_TYPE_WEAPON_PACKAGE_STATUS_ARRAY);
		config_type = (weapon_config_types) get_local_entity_int_value (en, INT_TYPE_WEAPON_CONFIG_TYPE);

		ASSERT (weapon_config_type_valid (config_type));

		if (package_status)
			for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
			{
				if (!package_status[package].number && weapon_config_database[config_type][package].sub_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
				{
					if (!package_status[package].rearming_timer)
					{
						package_status[package].rearming_timer = get_local_entity_rearming_sleep_time (group, weapon_config_database[config_type][package].sub_type);

						#if DEBUG_MODULE || DEBUG_SUPPLY
							debug_log("VH_WPN: %s / %s will be rearmed for %.1f seconds", 
									get_local_entity_string (en, STRING_TYPE_FULL_NAME), weapon_database[weapon_config_database[config_type][package].sub_type].full_name, package_status[package].rearming_timer);
						#endif
					}
					else
						package_status[package].rearming_timer = max(0, package_status[package].rearming_timer - get_delta_time());
					
					if (!package_status[package].rearming_timer)
					{
						ammo = get_local_entity_float_value (group, FLOAT_TYPE_AMMO_SUPPLY_LEVEL);
						ammo -= get_local_entity_float_value (en, FLOAT_TYPE_AMMO_ECONOMY) * AMMO_USAGE_ACCELERATOR;
						ammo = bound (ammo, 0.0, 100.0);
						set_local_entity_float_value (group, FLOAT_TYPE_AMMO_SUPPLY_LEVEL, ammo);
						
						package_status[package].number = weapon_config_database[config_type][package].number;

						#if DEBUG_MODULE || DEBUG_SUPPLY
							debug_log("VH_WPN: %s / %s is rearmed, group ammo level %f percents", get_local_entity_string (en, STRING_TYPE_FULL_NAME), weapon_database[weapon_config_database[config_type][package].sub_type].full_name, ammo);
						#endif
					}
				}
			}
	}
