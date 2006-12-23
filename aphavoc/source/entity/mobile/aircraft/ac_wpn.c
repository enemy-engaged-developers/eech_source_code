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

static void play_aircraft_weapon_launched_speech (entity *en, int weapon_type)
{
	weapon_launch_wingman_speech_types
		weapon_class;

	int
		speech_index;
	
	ASSERT (en);
	
	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	speech_index = -1;

	if (get_local_entity_int_value (en, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI)
	{
		weapon_class = weapon_database [weapon_type].weapon_launched_wingman_speech;

		switch (weapon_class)
		{
			case WEAPON_LAUNCH_WINGMAN_SPEECH_CANNON:
			{
				if (rand16 () & 0x01)
				{
					speech_index = SPEECH_WINGMAN_FIRING_CANNON;
				}
				else
				{
					speech_index = SPEECH_WINGMAN_ENGAGING_WITH_CANNON;
				}

				break;
			}
			case WEAPON_LAUNCH_WINGMAN_SPEECH_ROCKET:
			{
				if (rand16 () & 0x01)
				{
					speech_index = SPEECH_WINGMAN_FIRING_ROCKETS;
				}
				else
				{
					speech_index = SPEECH_WINGMAN_ROCKETS_AWAY;
				}

				break;
			}
			case WEAPON_LAUNCH_WINGMAN_SPEECH_MISSILE:
			{
				if (rand16 () & 0x01)
				{
					speech_index = SPEECH_WINGMAN_LAUNCHING_MISSILE;
				}
				else
				{
					speech_index = SPEECH_WINGMAN_MISSILE_AWAY;
				}

				break;
			}
			default:
			{
				return;
			}
		}

		ASSERT (speech_index != -1);

		play_client_server_wingman_message
		(
			en,
			1.0,
			1.5,
			SPEECH_CATEGORY_FIRING,
			4.0,
			SPEECH_INTRODUCTION_SOMETIMES,
			SPEECH_ARRAY_WINGMAN_MESSAGES,
			speech_index
		);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

aircraft_fire_result aircraft_fire_weapon (entity *en, unsigned int check_flags)
{
	entity
		*target;
	
	aircraft
		*raw;

	vec3d
		*target_pos,
		en_pos;

	int loal_mode = FALSE;

	ASSERT (en);

	raw = get_local_entity_data (en);

	//
	// Fire suppressed
	//

	if (check_flags & AIRCRAFT_FIRE_SUPPRESSED)
	{
		if (get_local_entity_int_value (get_session_entity (), INT_TYPE_SUPPRESS_AI_FIRE))
		{
			return AIRCRAFT_FIRE_SUPPRESSED;
		}
	}

	//
	// check weapon
	//

	if (check_flags & AIRCRAFT_FIRE_NO_WEAPON)
	{
		if (get_local_entity_int_value (en, INT_TYPE_SELECTED_WEAPON) == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
		{
			debug_log ("AC_WPN: Fire Weapon Error - NO WEAPON");
	
			return AIRCRAFT_FIRE_NO_WEAPON;
		}
	}

	//
	// weapon system_ready
	//

	if (check_flags & AIRCRAFT_FIRE_WEAPON_SYSTEM_NOT_READY)
	{
		if (!get_local_entity_int_value (en, INT_TYPE_SELECTED_WEAPON_SYSTEM_READY))
		{
			debug_log ("AC_WPN: Fire Weapon Error - WEAPON SYSTEM NOT READY");
	
			return AIRCRAFT_FIRE_WEAPON_SYSTEM_NOT_READY;
		}
	}

	//
	// find target
	//

	if (check_flags & AIRCRAFT_FIRE_NO_TARGET)
	{
		target = get_local_entity_parent (en, LIST_TYPE_TARGET);
	
		if (!target)
		{
			debug_log ("AC_WPN: Fire Weapon Error - NO TARGET");
	
			return AIRCRAFT_FIRE_NO_TARGET;
		}
	}

	//
	// line of sight checks
	//

	if (check_flags & AIRCRAFT_FIRE_NO_LOS)
	{
		int
			criteria;

		if (get_local_entity_int_value (target, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
		{
			criteria = MOBILE_LOS_CHECK_ALL;
		}
		else
		{
			criteria = MOBILE_LOS_CHECK_COURSE_TERRAIN;
		}

		get_local_entity_vec3d (en, VEC3D_TYPE_POSITION, &en_pos);

		target_pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

		en_pos.y -= (get_local_entity_float_value (en, FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE) + 2.0);

		if (!check_position_line_of_sight (en, target, &en_pos, target_pos, criteria))
		{
			if (get_local_entity_int_value (en, INT_TYPE_SELECTED_WEAPON) == ENTITY_SUB_TYPE_WEAPON_AGM114L_LONGBOW_HELLFIRE)
			{
				debug_log("AC_WPN: Switching to LOAL mode to fire at target without LOS ((Aircraft %s (%d), Target %s (%d))",
									get_local_entity_string (en, STRING_TYPE_FULL_NAME), get_local_entity_index (en),
									get_local_entity_string (target, STRING_TYPE_FULL_NAME), get_local_entity_index (target));

				loal_mode = TRUE;
			}
			else
			{
				debug_log ("AC_WPN: Fire Weapon Error - NO LOS (Aircraft %s (%d), Target %s (%d))",
									get_local_entity_string (en, STRING_TYPE_FULL_NAME), get_local_entity_index (en),
									get_local_entity_string (target, STRING_TYPE_FULL_NAME), get_local_entity_index (target));
		
				return AIRCRAFT_FIRE_NO_LOS;
			}
		}
	}

	//
	// Play Speech
	//

	play_aircraft_weapon_launched_speech (en, raw->selected_weapon);

	//
	// Fire weapon
	//

	set_local_entity_int_value(en, INT_TYPE_LOCK_ON_AFTER_LAUNCH, loal_mode);

	launch_client_server_weapon (en, raw->selected_weapon);

	return AIRCRAFT_FIRE_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_aircraft_weapon_fire (entity *en)
{
   aircraft
      *raw;

	ASSERT (en);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

   raw = get_local_entity_data (en);

	if (raw->weapon_burst_timer > 0.0)
	{
		//
		// check valid selected weapon
		//

		if (raw->selected_weapon == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
		{
			pause_client_server_continuous_weapon_sound_effect (en, raw->selected_weapon);

			raw->weapon_burst_timer = 0.0;

			return;
		}

		//
		// check selected weapon is ready
		//

		if (!raw->selected_weapon_system_ready)
		{
			pause_client_server_continuous_weapon_sound_effect (en, raw->selected_weapon);

			raw->weapon_burst_timer = 0.0;

			return;
		}

		//
		// check valid target
		//

		if (!raw->mob.target_link.parent)
		{
			pause_client_server_continuous_weapon_sound_effect (en, raw->selected_weapon);

			raw->weapon_burst_timer = 0.0;

			return;
		}
	
		//
		// fire weapon
		//

		launch_client_server_weapon (en, raw->selected_weapon);

		//
		// update burst timer
		//
		
		raw->weapon_burst_timer -= get_delta_time ();

		if (raw->weapon_burst_timer <= 0.0)
		{
			pause_client_server_continuous_weapon_sound_effect (en, raw->selected_weapon);

			raw->weapon_burst_timer = 0.0;

			return;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_aircraft_decoy_release (entity *en)
{
	aircraft
		*raw;

	int
		chaff_available,
		flare_available,
		chaff_released,
		flare_released;

	float
		range,
		velocity,
		time_to_impact;

	entity_sub_types
		weapon_sub_type;

	entity
		*persuer;

	vec3d
		*target_position,
		*weapon_position;

	ASSERT (en);

	#ifdef DEBUG

	if (get_comms_model () == COMMS_MODEL_CLIENT)
	{
		ASSERT (en == get_gunship_entity ());
	}

	#endif

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

	if (en == get_gunship_entity ())
	{
		if (!get_global_auto_counter_measures ())
		{
			return;
		}
	}
	else if (get_local_entity_int_value (en, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
	{
		return;
	}

	if (!get_local_entity_int_value (en, INT_TYPE_AIRBORNE_AIRCRAFT))
	{
		return;
	}

	persuer = get_local_entity_first_child (en, LIST_TYPE_TARGET);

	if (!persuer)
	{
		return;
	}

	chaff_available = get_local_entity_weapon_available (en, ENTITY_SUB_TYPE_WEAPON_CHAFF);

	flare_available = get_local_entity_weapon_available (en, ENTITY_SUB_TYPE_WEAPON_FLARE);

	if (!(chaff_available || flare_available))
	{
		return;
	}

	////////////////////////////////////////
	//
	// check all persuers
	//
	////////////////////////////////////////

	target_position = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	chaff_released = FALSE;
	flare_released = FALSE;

	while (persuer)
	{
		if (get_local_entity_type (persuer) == ENTITY_TYPE_WEAPON)
		{
			if (get_local_entity_int_value (persuer, INT_TYPE_WEAPON_GUIDANCE_TYPE) != WEAPON_GUIDANCE_TYPE_NONE)
			{
				weapon_sub_type = get_decoy_type_for_weapon (persuer);

				if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_CHAFF)
				{
					if (chaff_available)
					{
						if (!chaff_released)
						{
							weapon_position = get_local_entity_vec3d_ptr (persuer, VEC3D_TYPE_POSITION);

							range = get_approx_3d_range (weapon_position, target_position);

							velocity = get_local_entity_float_value (persuer, FLOAT_TYPE_VELOCITY);

							time_to_impact = range / max (velocity, 1.0);

							if (time_to_impact < 10.0)
							{
								launch_client_server_weapon (en, ENTITY_SUB_TYPE_WEAPON_CHAFF);

								chaff_released = TRUE;

								if (flare_released)
								{
									break;
								}
							}
						}
					}
				}
				else if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_FLARE)
				{
					if (flare_available)
					{
						if (!flare_released)
						{
							weapon_position = get_local_entity_vec3d_ptr (persuer, VEC3D_TYPE_POSITION);

							range = get_approx_3d_range (weapon_position, target_position);

							velocity = get_local_entity_float_value (persuer, FLOAT_TYPE_VELOCITY);

							time_to_impact = range / max (velocity, 1.0);

							if (time_to_impact < 10.0)
							{
								launch_client_server_weapon (en, ENTITY_SUB_TYPE_WEAPON_FLARE);

								flare_released = TRUE;

								if (chaff_released)
								{
									break;
								}
							}
						}
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
