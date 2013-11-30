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

static float
	seeker_head_theta1,
	seeker_head_theta2;

float
	default_stinger_seeker_head_x_position,
	default_stinger_seeker_head_y_position;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_default_weapon_systems (void)
{
	seeker_head_theta1 = 0.0;

	seeker_head_theta2 = 0.0;

	default_stinger_seeker_head_x_position = 0.0;

	default_stinger_seeker_head_y_position = 0.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_default_weapon_systems (void)
{
	int
		inhibit_launch;

	entity
		*en,
		*target;

	entity_sub_types
		weapon_sub_type;

	en = get_gunship_entity ();

	weapon_sub_type = get_local_entity_int_value (en, INT_TYPE_SELECTED_WEAPON);

	////////////////////////////////////////
	//
	// Stinger/Igla lock tone
	//
	////////////////////////////////////////

	switch (weapon_sub_type)
	{
	case ENTITY_SUB_TYPE_WEAPON_AIM92_STINGER:
	case ENTITY_SUB_TYPE_WEAPON_IGLA_V:
	case ENTITY_SUB_TYPE_WEAPON_AIM9M_SIDEWINDER:
	 if (weapon_lock_type == WEAPON_LOCK_VALID)
	{
		resume_local_entity_sound_type (en, ENTITY_SUB_TYPE_EFFECT_SOUND_LOCK_ON_TONE);

		update_good_tone ();
		break;
	}
	default:
	{
		pause_local_entity_sound_type (en, ENTITY_SUB_TYPE_EFFECT_SOUND_LOCK_ON_TONE, 0.5);

		reset_good_tone ();
	}
	}

	
	////////////////////////////////////////
	//
	// Stinger seeker head position
	//
	////////////////////////////////////////

	default_stinger_seeker_head_x_position = 0.25 * sin (seeker_head_theta1);
	default_stinger_seeker_head_y_position = 0.25 * cos (seeker_head_theta1);

	default_stinger_seeker_head_x_position += 0.125 * sin (seeker_head_theta2);
	default_stinger_seeker_head_y_position += 0.125 * cos (seeker_head_theta2);

	seeker_head_theta1 += rad (120.0) * get_delta_time ();
	seeker_head_theta2 -= rad (180.0) * get_delta_time ();

	////////////////////////////////////////
	//
	// weapon launch interlocks
	//
	////////////////////////////////////////

	inhibit_launch = FALSE;

	switch (weapon_sub_type)
	{
		////////////////////////////////////////
		case ENTITY_SUB_TYPE_WEAPON_M230_30MM_ROUND:
		case ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255:
		case ENTITY_SUB_TYPE_WEAPON_HYDRA70_M261:
		case ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND:
		case ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND:
		case ENTITY_SUB_TYPE_WEAPON_M2_12P7MM_ROUND:
		case ENTITY_SUB_TYPE_WEAPON_S5:
		case ENTITY_SUB_TYPE_WEAPON_S8:
		case ENTITY_SUB_TYPE_WEAPON_S13:
		case ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND:
		////////////////////////////////////////
		{
			if
			(
				//WEAPON_LOCK_NO_ACQUIRE
				(weapon_lock_type == WEAPON_LOCK_NO_WEAPON)
				//WEAPON_LOCK_NO_TARGET
				//WEAPON_LOCK_INVALID_TARGET
				//WEAPON_LOCK_SEEKER_LIMIT
				//WEAPON_LOCK_NO_LOS
				//WEAPON_LOCK_NO_BORESIGHT
				//WEAPON_LOCK_MIN_RANGE
				//WEAPON_LOCK_MAX_RANGE
				//WEAPON_LOCK_VALID
			)
			{
				inhibit_launch = TRUE;
			}

			break;
		}
		////////////////////////////////////////
		case ENTITY_SUB_TYPE_WEAPON_AIM92_STINGER:
		case ENTITY_SUB_TYPE_WEAPON_IGLA_V:
		case ENTITY_SUB_TYPE_WEAPON_AT6_SPIRAL:
		case ENTITY_SUB_TYPE_WEAPON_AIM9M_SIDEWINDER:
		////////////////////////////////////////
		{
			if
			(
				(weapon_lock_type == WEAPON_LOCK_NO_ACQUIRE) ||
				(weapon_lock_type == WEAPON_LOCK_NO_WEAPON) ||
				(weapon_lock_type == WEAPON_LOCK_NO_TARGET) ||
				(weapon_lock_type == WEAPON_LOCK_INVALID_TARGET) ||
				(weapon_lock_type == WEAPON_LOCK_SEEKER_LIMIT) ||
				(weapon_lock_type == WEAPON_LOCK_NO_LOS) ||
				//WEAPON_LOCK_NO_BORESIGHT
				//WEAPON_LOCK_MIN_RANGE
				(weapon_lock_type == WEAPON_LOCK_MAX_RANGE)
				//WEAPON_LOCK_VALID
			)
			{
				inhibit_launch = TRUE;
			}

			break;
		}
		////////////////////////////////////////
		case ENTITY_SUB_TYPE_WEAPON_ATAKA:
		case ENTITY_SUB_TYPE_WEAPON_VIKHR:
		////////////////////////////////////////
		{
			if
			(
				(weapon_lock_type == WEAPON_LOCK_NO_ACQUIRE) ||
				(weapon_lock_type == WEAPON_LOCK_NO_WEAPON) ||
				(weapon_lock_type == WEAPON_LOCK_NO_TARGET) ||
				(weapon_lock_type == WEAPON_LOCK_INVALID_TARGET) ||
				(weapon_lock_type == WEAPON_LOCK_SEEKER_LIMIT) ||
				//WEAPON_LOCK_NO_LOS
				//WEAPON_LOCK_NO_BORESIGHT
				//WEAPON_LOCK_MIN_RANGE
				(weapon_lock_type == WEAPON_LOCK_MAX_RANGE)
				//WEAPON_LOCK_VALID
			)
			{
				inhibit_launch = TRUE;
			}

			break;
		}
		////////////////////////////////////////
		case ENTITY_SUB_TYPE_WEAPON_AGM114L_LONGBOW_HELLFIRE:
		case ENTITY_SUB_TYPE_WEAPON_AGM114K_HELLFIRE_II:
		////////////////////////////////////////
		{
			if (!get_local_entity_int_value (en, INT_TYPE_LOCK_ON_AFTER_LAUNCH))
			{
				if
				(
					(weapon_lock_type == WEAPON_LOCK_NO_ACQUIRE) ||
					(weapon_lock_type == WEAPON_LOCK_NO_WEAPON) ||
					(weapon_lock_type == WEAPON_LOCK_NO_TARGET) ||
					(weapon_lock_type == WEAPON_LOCK_INVALID_TARGET) ||
					(weapon_lock_type == WEAPON_LOCK_SEEKER_LIMIT) ||
					//WEAPON_LOCK_NO_LOS
					//WEAPON_LOCK_NO_BORESIGHT
					//WEAPON_LOCK_MIN_RANGE
					(weapon_lock_type == WEAPON_LOCK_MAX_RANGE)
					//WEAPON_LOCK_VALID
				)
				{
					inhibit_launch = TRUE;
				}
			}
			else
			{
				if
				(
					//WEAPON_LOCK_NO_ACQUIRE
					(weapon_lock_type == WEAPON_LOCK_NO_WEAPON)
					//WEAPON_LOCK_NO_TARGET
					//WEAPON_LOCK_INVALID_TARGET
					//WEAPON_LOCK_SEEKER_LIMIT
					//WEAPON_LOCK_NO_LOS
					//WEAPON_LOCK_NO_BORESIGHT
					//WEAPON_LOCK_MIN_RANGE
					//WEAPON_LOCK_MAX_RANGE
					//WEAPON_LOCK_VALID
				)
				{
					inhibit_launch = TRUE;
				}
			}

			break;
		}

	}

	if (inhibit_launch)
	{
		if (fire_single_weapon)
		{
			play_common_cpg_failed_launch_speech (weapon_lock_type);
		}

		rocket_salvo_count = 0;

		fire_single_weapon = 0;

		return;
	}

	//
	// ensure that there is a selected weapon
	//

	if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
	{
		if (fire_single_weapon)
		{
			play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_NO_WEAPON);
		}

		rocket_salvo_count = 0;

		fire_single_weapon = 0;

		return;
	}

	////////////////////////////////////////
	//
	// rocket salvo
	//
	////////////////////////////////////////

	if ((weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255) || (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_HYDRA70_M261) ||
					 weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_S5 ||
					 weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_S8 ||
					 weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_S13)
	{
		if (fire_single_weapon)
		{
			rocket_salvo_count += rocket_salvo_size;
		}

		if (rocket_salvo_count)
		{
			fire_single_weapon = min (rocket_salvo_count, 2);

			rocket_salvo_count -= fire_single_weapon;

			rocket_salvo_count = max (rocket_salvo_count, 0);
		}
	}
	else
	{
		rocket_salvo_count = 0;
	}

	////////////////////////////////////////
	//
	// launch weapon(s)
	//
	////////////////////////////////////////

	target = get_local_entity_parent (en, LIST_TYPE_TARGET);

	if (fire_continuous_weapon || fire_single_weapon)
	{
		if (weapon_database[weapon_sub_type].rate_of_fire == FIRE_SINGLE_WEAPON)
		{
			//
			// fire a maximum of two weapons per frame (one off of each stub wing)
			//

			if (fire_single_weapon >= 2)
			{
				apply_weapon_recoil_effect (en, weapon_sub_type);

				launch_client_server_weapon (en, weapon_sub_type);
			}

			if (fire_single_weapon >= 1)
			{
				apply_weapon_recoil_effect (en, weapon_sub_type);

				launch_client_server_weapon (en, weapon_sub_type);
			}
			
			// when firing radar hellfires in PFZ mode automaticly select next target
			// after each launch
			if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_AGM114L_LONGBOW_HELLFIRE
				&& target_acquisition_system == TARGET_ACQUISITION_SYSTEM_GROUND_RADAR
				&& get_local_entity_int_value (get_gunship_entity (), INT_TYPE_LOCK_ON_AFTER_LAUNCH)  // TODO: remove this once radar hellfires get their target upon launch, not 3 seconds later
				&& pfz_active())
			{
				get_next_ground_radar_target();	
			}
		}
		else
		{
			if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND)
			{
				apply_weapon_recoil_effect (en, weapon_sub_type);

				launch_client_server_weapon (en, weapon_sub_type);

				apply_weapon_recoil_effect (en, weapon_sub_type);

				launch_client_server_weapon (en, weapon_sub_type);
			}
			else
			{
				apply_weapon_recoil_effect (en, weapon_sub_type);

				launch_client_server_weapon (en, weapon_sub_type);
			}
		}
	}
	else
		((helicopter*)get_local_entity_data(en))->ac.weapon_salvo_timer = 0.0;

	fire_single_weapon = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_default_missile_flight_time (void)
{
	entity_sub_types
		weapon_sub_type;

	entity
		*en,
		*weapon,
		*target;

	vec3d
		*weapon_position,
		*target_position;

	float
		flight_time,
		weapon_velocity,
		target_range;

	flight_time = 0.0;

	en = get_gunship_entity ();

	//
	// find most recently launched Hellfire with a target (first found on list)
	//

	weapon = get_local_entity_first_child (en, LIST_TYPE_LAUNCHED_WEAPON);

	while (weapon)
	{
		weapon_sub_type = get_local_entity_int_value (weapon, INT_TYPE_ENTITY_SUB_TYPE);

		if ((weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_AGM114L_LONGBOW_HELLFIRE) || (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_AGM114K_HELLFIRE_II) ||
			(weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_AT6_SPIRAL) || (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_ATAKA) || (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_VIKHR)
		)
		{
			target = get_local_entity_parent (weapon, LIST_TYPE_TARGET);

			if (target)
			{
				weapon_position = get_local_entity_vec3d_ptr (weapon, VEC3D_TYPE_POSITION);

				target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

				target_range = get_3d_range (weapon_position, target_position);

				weapon_velocity = get_local_entity_float_value (weapon, FLOAT_TYPE_VELOCITY);

				if (weapon_velocity > 0.0)
				{
					flight_time = target_range / weapon_velocity;

					break;
				}
			}
		}

		weapon = get_local_entity_child_succ (weapon, LIST_TYPE_LAUNCHED_WEAPON);
	}

	return (flight_time);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void toggle_default_radar_jammer_manual (void)
{
	if (!default_damage.radar_jammer)
	{
		if (!get_global_auto_counter_measures ())
		{
			if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_RADAR_JAMMER_ON))
			{
				set_client_server_entity_int_value (get_gunship_entity (), INT_TYPE_RADAR_JAMMER_ON, FALSE);
			}
			else
			{
				set_client_server_entity_int_value (get_gunship_entity (), INT_TYPE_RADAR_JAMMER_ON, TRUE);
			}
		}
	}

	play_common_cpg_radar_jammer_speech (default_damage.radar_jammer);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_default_radar_jammer_manual (int state)
{
	if (!default_damage.radar_jammer)
	{
		if (!get_global_auto_counter_measures ())
		{
			if (state != get_local_entity_int_value (get_gunship_entity (), INT_TYPE_RADAR_JAMMER_ON))
			{
				set_client_server_entity_int_value (get_gunship_entity (), INT_TYPE_RADAR_JAMMER_ON, state);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_default_radar_jammer_auto (int state)
{
	if (!default_damage.radar_jammer)
	{
		if (get_global_auto_counter_measures ())
		{
			if (state != get_local_entity_int_value (get_gunship_entity (), INT_TYPE_RADAR_JAMMER_ON))
			{
				set_client_server_entity_int_value (get_gunship_entity (), INT_TYPE_RADAR_JAMMER_ON, state);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void toggle_default_infra_red_jammer_manual (void)
{
	if (!default_damage.infra_red_jammer)
	{
		if (!get_global_auto_counter_measures ())
		{
			if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_INFRA_RED_JAMMER_ON))
			{
				set_client_server_entity_int_value (get_gunship_entity (), INT_TYPE_INFRA_RED_JAMMER_ON, FALSE);
			}
			else
			{
				set_client_server_entity_int_value (get_gunship_entity (), INT_TYPE_INFRA_RED_JAMMER_ON, TRUE);
			}
		}
	}

	play_common_cpg_infra_red_jammer_speech (default_damage.infra_red_jammer);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_default_infra_red_jammer_manual (int state)
{
	if (!default_damage.infra_red_jammer)
	{
		if (!get_global_auto_counter_measures ())
		{
			if (state != get_local_entity_int_value (get_gunship_entity (), INT_TYPE_INFRA_RED_JAMMER_ON))
			{
				set_client_server_entity_int_value (get_gunship_entity (), INT_TYPE_INFRA_RED_JAMMER_ON, state);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_default_infra_red_jammer_auto (int state)
{
	if (!default_damage.infra_red_jammer)
	{
		if (get_global_auto_counter_measures ())
		{
			if (state != get_local_entity_int_value (get_gunship_entity (), INT_TYPE_INFRA_RED_JAMMER_ON))
			{
				set_client_server_entity_int_value (get_gunship_entity (), INT_TYPE_INFRA_RED_JAMMER_ON, state);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
