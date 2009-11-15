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

static void apply_weapon_recoil_effect (entity *en, entity_sub_types selected_weapon)
{
	float
		duration,
		strength;

	viewpoint
		vp;

	ASSERT (en);

	if (get_local_entity_selected_weapon_viewpoint (en, &vp))
	{
		switch (selected_weapon)
		{
			////////////////////////////////////////
			case ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND:
			case ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND:
			////////////////////////////////////////
			{
				duration = 0.3;

				strength = 2.0;

				break;
			}
			////////////////////////////////////////
			case ENTITY_SUB_TYPE_WEAPON_IGLA_V:
			////////////////////////////////////////
			{
				duration = 0.6;

				strength = 7.5;

				break;
			}
			////////////////////////////////////////
			case ENTITY_SUB_TYPE_WEAPON_ATAKA:
			////////////////////////////////////////
			{
				duration = 0.7;

				strength = 9.0;

				break;
			}
			////////////////////////////////////////
			case ENTITY_SUB_TYPE_WEAPON_S8:
			////////////////////////////////////////
			{
				duration = 0.4;

				strength = 10.0;

				break;
			}
			////////////////////////////////////////
			case ENTITY_SUB_TYPE_WEAPON_S13:
			////////////////////////////////////////
			{
				duration = 0.5;

				strength = 7.5;

				break;
			}
			////////////////////////////////////////
			case ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND:
			////////////////////////////////////////
			{
				duration = 0.1;

				strength = 2.5;

				break;
			}
			////////////////////////////////////////
			default:
			////////////////////////////////////////
			{
				duration = 0.0;

				strength = 0.0;

				break;
			}
		}

		add_dynamic_weapon_launch_force (&vp.position, &vp.zv, strength, duration);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_havoc_weapon_systems (void)
{
	int
		inhibit_launch;

	entity
		*en;

	entity_sub_types
		weapon_sub_type;

	gun_is_firing = FALSE;

	en = get_gunship_entity ();

	weapon_sub_type = get_local_entity_int_value (en, INT_TYPE_SELECTED_WEAPON);

	////////////////////////////////////////
	//
	// Igla lock tone
	//
	////////////////////////////////////////

	if ((weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_IGLA_V) && (weapon_lock_type == WEAPON_LOCK_VALID))
	{
		resume_local_entity_sound_type (en, ENTITY_SUB_TYPE_EFFECT_SOUND_LOCK_ON_TONE);

		update_good_tone ();
	}
	else
	{
		pause_local_entity_sound_type (en, ENTITY_SUB_TYPE_EFFECT_SOUND_LOCK_ON_TONE, 0.5);

		reset_good_tone ();
	}

	////////////////////////////////////////
	//
	// weapon launch interlocks
	//
	////////////////////////////////////////

	inhibit_launch = FALSE;

	switch (weapon_sub_type)
	{
		////////////////////////////////////////
		case ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND:
		case ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND:
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
		case ENTITY_SUB_TYPE_WEAPON_IGLA_V:
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
		case ENTITY_SUB_TYPE_WEAPON_S8:
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
		case ENTITY_SUB_TYPE_WEAPON_S13:
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

	if ((weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_S8) || (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_S13))
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
		}
		else
		{
			gun_is_firing = get_local_entity_weapon_count (en, weapon_sub_type) > 0;

			if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND)
			{
				helicopter* raw = (helicopter *) get_local_entity_data(en);
				unsigned number_of_pods = get_number_of_pods_firing(en, weapon_sub_type);
				unsigned pre_fire_timer = raw->ac.weapon_salvo_timer;

				while (number_of_pods--)
				{
					raw->ac.weapon_salvo_timer = pre_fire_timer;  // should only set once per frame, not once per gun, so revert before each gun */
					apply_weapon_recoil_effect (en, weapon_sub_type);
					launch_client_server_weapon (en, weapon_sub_type);
				}
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

float get_havoc_missile_flight_time (void)
{
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
	// find most recently launched Ataka with a target (first found on list)
	//

	weapon = get_local_entity_first_child (en, LIST_TYPE_LAUNCHED_WEAPON);

	while (weapon)
	{
		if (get_local_entity_int_value (weapon, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_WEAPON_ATAKA)
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

void toggle_havoc_radar_jammer_manual (void)
{
	if (!havoc_damage.radar_jammer)
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

	play_common_cpg_radar_jammer_speech (havoc_damage.radar_jammer);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_havoc_radar_jammer_manual (int state)
{
	if (!havoc_damage.radar_jammer)
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

void set_havoc_radar_jammer_auto (int state)
{
	if (!havoc_damage.radar_jammer)
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

void toggle_havoc_infra_red_jammer_manual (void)
{
	if (!havoc_damage.infra_red_jammer)
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

	play_common_cpg_infra_red_jammer_speech (havoc_damage.infra_red_jammer);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_havoc_infra_red_jammer_manual (int state)
{
	if (!havoc_damage.infra_red_jammer)
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

void set_havoc_infra_red_jammer_auto (int state)
{
	if (!havoc_damage.infra_red_jammer)
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
