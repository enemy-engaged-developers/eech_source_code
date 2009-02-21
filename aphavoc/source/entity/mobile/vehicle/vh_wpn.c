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
		debug_flag,
		continue_burst_fire;

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

   raw = get_local_entity_data (en);

	target = raw->mob.target_link.parent;

	debug_flag = FALSE;

	#if DEBUG_MODULE

	if (en == get_external_view_entity ())
	{
		debug_flag = DEBUG_MODULE;
	}

	#endif

	//
	// update burst
	//

	continue_burst_fire = FALSE;

	if (raw->weapon_burst_timer > 0.0)
	{
		raw->weapon_burst_timer -= get_delta_time ();

		if (raw->weapon_burst_timer > 0.0)
		{
			if (debug_flag)
			{
				debug_log ("VH_WPN: Continuing Burst");
			}

			continue_burst_fire = TRUE;
		}
		else
		{
			if (debug_flag)
			{
				debug_log ("VH_WPN: Stop Burst this frame");
			}

			raw->weapon_salvo_timer = 0.0;

			pause_client_server_continuous_weapon_sound_effect (en, raw->selected_weapon);
		}
	}
	else
		raw->weapon_salvo_timer = 0.0;

	//
	// Check Suppress AI fire
	//

	if (get_local_entity_int_value (get_session_entity (), INT_TYPE_SUPPRESS_AI_FIRE))
	{
		if (raw->weapon_burst_timer > 0.0)
		{
			pause_client_server_continuous_weapon_sound_effect (en, raw->selected_weapon);
		}

		if (debug_flag)
		{
			debug_log ("VH_WPN: Not Firing - AI fire suppressed");
		}

		return;
	}

	//
	// Update fire timer (unless continuing burst)
	//

	if (!continue_burst_fire)
	{
		raw->target_fire_timer -= get_delta_time ();

		if (raw->target_fire_timer > 0.0)
		{
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
				//
				// each radar / jamming device active decreases fire timer by 15%, meaning more "heat" for the player
				//

				if (get_local_entity_int_value (target, INT_TYPE_RADAR_ON))
				{
					raw->target_fire_timer *= 0.85;
				}
				if (get_local_entity_int_value (target, INT_TYPE_RADAR_JAMMER_ON))
				{
					raw->target_fire_timer *= 0.85;
				}
				if (get_local_entity_int_value (target, INT_TYPE_INFRA_RED_JAMMER_ON))
				{
					raw->target_fire_timer *= 0.85;
				}

				//
				// then modify timer based on difficulty level
				//

				raw->target_fire_timer *= get_fire_timer_difficulty_factor (target);
			}
		}
	}

	//
	// check vehicle not sleeping
	//

	if (raw->sleep > 0.0)
	{
		if (raw->weapon_burst_timer > 0.0)
		{
			pause_client_server_continuous_weapon_sound_effect (en, raw->selected_weapon);
		}

		if (debug_flag)
		{
			debug_log ("VH_WPN: Not Firing - Sleeping");
		}

		return;
	}

	//
	// check valid target
	//

	if (!target)
	{
		if (raw->weapon_burst_timer > 0.0)
		{
			pause_client_server_continuous_weapon_sound_effect (en, raw->selected_weapon);
		}

		if (debug_flag >= 2)
		{
			debug_log ("VH_WPN: Not Firing - No Target");
		}

		return;
	}

	//
	// check valid selected weapon
	//

	if (!vehicle_select_best_weapon (en, target))
	{
		if (raw->weapon_burst_timer > 0.0)
		{
			pause_client_server_continuous_weapon_sound_effect (en, raw->selected_weapon);
		}

		if (debug_flag)
		{
			debug_log ("VH_WPN: Not Firing - No weapon");
		}

		return;
	}

	//
	// check selected weapon is ready
	//

	if (!raw->selected_weapon_system_ready)
	{
		if (raw->weapon_burst_timer > 0.0)
		{
			pause_client_server_continuous_weapon_sound_effect (en, raw->selected_weapon);
		}

		if (debug_flag)
		{
			debug_log ("VH_WPN: Not Firing - Weapon system not ready");
		}

		return;
	}

	//
	// Check range
	//

	pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	target_pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

	range = get_3d_range (pos, target_pos);

	if ((range < weapon_database [raw->selected_weapon].min_range) || (range > weapon_database [raw->selected_weapon].max_range))
	{
		if (raw->weapon_burst_timer > 0.0)
		{
			pause_client_server_continuous_weapon_sound_effect (en, raw->selected_weapon);
		}

		if (debug_flag)
		{
			debug_log ("VH_WPN: Not Firing - out of range");
		}

		return;
	}

	//
	// Check altitude
	//

	if (get_local_entity_int_value (target, INT_TYPE_AIRBORNE_AIRCRAFT))
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
			if (raw->weapon_burst_timer > 0.0)
			{
				pause_client_server_continuous_weapon_sound_effect (en, raw->selected_weapon);
			}

			if (debug_flag)
			{
				debug_log ("VH_WPN: Not Firing - altitude");
			}

			return;
		}
	}

	//
	// check within max launch angle error
	//

	if (!get_local_entity_int_value (en, INT_TYPE_WEAPON_AND_TARGET_VECTORS_VALID))
	{
		if (raw->weapon_burst_timer > 0.0)
		{
			pause_client_server_continuous_weapon_sound_effect (en, raw->selected_weapon);
		}

		if (debug_flag)
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
		if (raw->weapon_burst_timer > 0.0)
		{
			pause_client_server_continuous_weapon_sound_effect (en, raw->selected_weapon);
		}

		if (debug_flag)
		{
			debug_log ("VH_WPN: Not Firing - outside launch angle (2)");
		}

		return;
	}

	//
	// Check Line Of Sight (Non-projectile weapons only)
	//

	if (!continue_burst_fire)
	{
		if (weapon_database[raw->selected_weapon].aiming_type != WEAPON_AIMING_TYPE_CALC_ANGLE_OF_PROJECTION)
		{
			if (!check_entity_line_of_sight (en, target, MOBILE_LOS_CHECK_ALL))
			{
				if (raw->weapon_burst_timer > 0.0)
				{
					pause_client_server_continuous_weapon_sound_effect (en, raw->selected_weapon);
				}

				if (debug_flag)
				{
					debug_log ("VH_WPN: Not Firing - No Line Of Sight");
				}

				return;
			}
		}
	}

	//
	// fire weapon
	//

	if (debug_flag)
	{
		debug_log ("VH_WPN: Firing weapon");
	}

	launch_client_server_weapon (en, raw->selected_weapon);

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
		entity
			*group;

		float
			ammo,
			sleep_time;

		weapon_config_types
			config_type;

		//
		// set vehicle to rearming and decrease groups ammo
		//

		group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

		ASSERT (group);

		sleep_time = get_local_entity_rearming_sleep_time (group);

		set_local_entity_float_value (en, FLOAT_TYPE_SLEEP, sleep_time);

		ammo = get_local_entity_float_value (group, FLOAT_TYPE_AMMO_SUPPLY_LEVEL);

		ammo -= get_local_entity_float_value (en, FLOAT_TYPE_AMMO_ECONOMY) * AMMO_USAGE_ACCELERATOR;

		ammo = bound (ammo, 0.0, 100.0);

		set_local_entity_float_value (group, FLOAT_TYPE_AMMO_SUPPLY_LEVEL, ammo);

		//
		// set vehicle to rearmed
		//

		config_type = get_local_entity_int_value (en, INT_TYPE_WEAPON_CONFIG_TYPE);

		if (config_type == WEAPON_CONFIG_TYPE_UNARMED)
		{
			config_type = get_local_entity_int_value (en, INT_TYPE_DEFAULT_WEAPON_CONFIG_TYPE);
		}

		set_client_server_entity_int_value (en, INT_TYPE_WEAPON_CONFIG_TYPE, config_type);

		#if DEBUG_MODULE || DEBUG_SUPPLY

		debug_log ("VH_WPN: SUPPLY_INFO: member %s (%d) rearmed, sleeping for %0.2f seconds (group ammo = %0.2f%%, fuel %0.2f%%)",
						get_local_entity_string (en, STRING_TYPE_FULL_NAME),
						get_local_entity_index (en),
						sleep_time,
						get_local_entity_float_value (group, FLOAT_TYPE_AMMO_SUPPLY_LEVEL),
						get_local_entity_float_value (group, FLOAT_TYPE_FUEL_SUPPLY_LEVEL));

		#endif
	}
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

	raw = get_local_entity_data (en);

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

					time_to_impact = range / max (velocity, 1.0);

					if (time_to_impact < 10.0)
					{
						launch_client_server_weapon (en, ENTITY_SUB_TYPE_WEAPON_SMOKE_GRENADE);

						break;
					}
				}
			}
		}

		persuer = get_local_entity_child_succ (persuer, LIST_TYPE_TARGET);
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
		-1
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
		difficulty = get_local_entity_int_value (pilot_en, INT_TYPE_DIFFICULTY_LEVEL);

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
