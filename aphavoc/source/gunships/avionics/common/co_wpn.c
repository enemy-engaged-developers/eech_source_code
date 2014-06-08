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

weapon_lock_types
	weapon_lock_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	fire_continuous_weapon,
	fire_single_weapon,
	rocket_salvo_size,
	rocket_salvo_count,
	gun_is_firing = FALSE;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	good_tone;

float
	ballistics_sight_calibrated_drop = 0.0,
	good_tone_delay;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_common_weapon_systems (void)
{
	fire_continuous_weapon = FALSE;

	fire_single_weapon = 0;

	if (get_global_gunship_type() == GUNSHIP_TYPE_HIND)
		rocket_salvo_size = 2;
	else
		rocket_salvo_size = 1;

	rocket_salvo_count = 0;

	good_tone = FALSE;

	good_tone_delay = 0.0;

	set_client_server_entity_int_value (get_gunship_entity (), INT_TYPE_LOCK_ON_AFTER_LAUNCH, FALSE);

	set_gunship_weapon (ENTITY_SUB_TYPE_WEAPON_NO_WEAPON);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_common_weapon_systems (void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void apply_weapon_recoil_effect (entity *en, entity_sub_types selected_weapon)
{
	float
		duration,
		strength;
	vec3d
		direction;

	viewpoint
		vp;

	ASSERT (en);

	if (get_local_entity_selected_weapon_viewpoint (en, &vp))
	{
		switch (selected_weapon)
		{
			////////////////////////////////////////
			case ENTITY_SUB_TYPE_WEAPON_AIM92A_STINGER:
			case ENTITY_SUB_TYPE_WEAPON_AIM9M_SIDEWINDER:
			case ENTITY_SUB_TYPE_WEAPON_9M39_IGLA_V:
			case ENTITY_SUB_TYPE_WEAPON_9M114_SHTURM:
			case ENTITY_SUB_TYPE_WEAPON_9M120_ATAKA_V:
			case ENTITY_SUB_TYPE_WEAPON_9K121_VIKHR:
			case ENTITY_SUB_TYPE_WEAPON_AGM114L_LONGBOW_HELLFIRE:
			case ENTITY_SUB_TYPE_WEAPON_AGM114K_HELLFIRE_II:
			case ENTITY_SUB_TYPE_WEAPON_AGM114R_HELLFIRE_II:
			////////////////////////////////////////
			{
				duration = 2.0;
				strength = 1.0;
				break;
			}
			////////////////////////////////////////
			case ENTITY_SUB_TYPE_WEAPON_S5:
			case ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255:
			case ENTITY_SUB_TYPE_WEAPON_HYDRA70_M261:
			////////////////////////////////////////
			{
				duration = 0.1;
				strength = 0.5;
				break;
			}
			////////////////////////////////////////
			case ENTITY_SUB_TYPE_WEAPON_S8:
			////////////////////////////////////////
			{
				duration = 0.2;
				strength = 0.8;
				break;
			}
			////////////////////////////////////////
			case ENTITY_SUB_TYPE_WEAPON_S13:
			////////////////////////////////////////
			{
				duration = 0.3;
				strength = 1.3;
				break;
			}
			////////////////////////////////////////
			case ENTITY_SUB_TYPE_WEAPON_M2HB_12P7MM_ROUND:
			case ENTITY_SUB_TYPE_WEAPON_YAK_B_12P7MM_ROUND:
			////////////////////////////////////////
			{
				duration = 0.2;
				strength = 0.1;
				break;
			}
			////////////////////////////////////////
			case ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND:
			case ENTITY_SUB_TYPE_WEAPON_M197_20MM_ROUND:
			////////////////////////////////////////
			{
				duration = 0.2;
				strength = 0.4;
				break;
			}
			////////////////////////////////////////
			case ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND:
			case ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND:
			case ENTITY_SUB_TYPE_WEAPON_M230_30MM_ROUND:
			////////////////////////////////////////
			{
				duration = 0.3;
				strength = 0.7;
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
		
		direction.x = 0;
		direction.y = 0;
		direction.z = - 1;
		multiply_matrix3x3_vec3d(&direction, vp.attitude, &direction);
		add_dynamic_weapon_launch_force (&vp.position, &direction, strength, duration);
		
		play_ffb_weapon_effect((char*)weapon_database[selected_weapon].full_name, weapon_database[selected_weapon].rate_of_fire);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_weapon_lock_type (target_acquisition_systems system)
{
	entity
		*source,
		*target;

	entity_sub_types
		selected_weapon_type;

	float
		target_range,
		theta,
		weapon_min_range,
		weapon_max_range;

	vec3d
		*source_position,
		*target_position,
		*weapon_vector,
		*weapon_to_target_vector;

	////////////////////////////////////////
	//
	// WEAPON_LOCK_NO_ACQUIRE
	//
	////////////////////////////////////////

	if (system == TARGET_ACQUISITION_SYSTEM_OFF)
	{
		weapon_lock_type = WEAPON_LOCK_NO_ACQUIRE;

		return;
	}

	source = get_gunship_entity ();
	selected_weapon_type = get_local_entity_int_value (source, INT_TYPE_SELECTED_WEAPON);

	// trying to fire a laser guided without laser active
	if (weapon_database[selected_weapon_type].guidance_type == WEAPON_GUIDANCE_TYPE_SEMI_ACTIVE_LASER
		&& !laser_is_active())
	{
		weapon_lock_type = WEAPON_LOCK_NO_ACQUIRE;

		return;
	}


	////////////////////////////////////////
	//
	// WEAPON_LOCK_NO_WEAPON
	//
	////////////////////////////////////////

	if (selected_weapon_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
	{
		weapon_lock_type = WEAPON_LOCK_NO_WEAPON;

		return;
	}

	////////////////////////////////////////
	//
	// WEAPON_LOCK_NO_TARGET
	//
	////////////////////////////////////////

	target = get_local_entity_parent (source, LIST_TYPE_TARGET);

	if (!target)
	{
		if (!guidance_type_can_use_point_lock(weapon_database[selected_weapon_type].guidance_type))
		{
			weapon_lock_type = WEAPON_LOCK_NO_TARGET;
			return;
		}

		target_position = get_eo_tracking_point();  // get_local_entity_vec3d_ptr(source, VEC3D_TYPE_EO_TRACKING_POINT);

		if (!target_position)
		{
			weapon_lock_type = WEAPON_LOCK_NO_TARGET;
			return;
		}
	}

	////////////////////////////////////////
	//
	// WEAPON_LOCK_INVALID_TARGET
	//
	////////////////////////////////////////

	//
	// infra-red air-to-air weapons require an airborne target
	//

	if (weapon_database[selected_weapon_type].guidance_type == WEAPON_GUIDANCE_TYPE_PASSIVE_INFRA_RED)
	{
		if (weapon_database[selected_weapon_type].weapon_class & WEAPON_CLASS_AIR_TO_AIR)
		{
			if (!target || !get_local_entity_int_value (target, INT_TYPE_AIRBORNE_AIRCRAFT))
			{
				weapon_lock_type = WEAPON_LOCK_INVALID_TARGET;

				return;
			}
		}
	}

	////////////////////////////////////////
	//
	// WEAPON_LOCK_SEEKER_LIMIT
	//
	////////////////////////////////////////

	//
	// if guided weapon check target is inside the seeker limit
	//


	if (weapon_database[selected_weapon_type].guidance_type != WEAPON_GUIDANCE_TYPE_NONE)
	{
		update_entity_weapon_system_weapon_and_target_vectors (source);

		if (get_local_entity_int_value (source, INT_TYPE_WEAPON_AND_TARGET_VECTORS_VALID))
		{
			weapon_vector = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_WEAPON_VECTOR);

			weapon_to_target_vector = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_WEAPON_TO_TARGET_VECTOR);

			theta = get_3d_unit_vector_dot_product (weapon_vector, weapon_to_target_vector);

			theta = fabs (acos (theta));

			if (theta > weapon_database[selected_weapon_type].max_launch_angle_error)
			{
				weapon_lock_type = WEAPON_LOCK_SEEKER_LIMIT;

				return;
			}
		}
		else
		{
			//
			// this should never happen
			//

			#if DEBUG_MODULE
			debug_colour_log (DEBUG_COLOUR_RED, "WARNING! Target and weapon vectors are not valid");
			#endif
		}
	}

	////////////////////////////////////////
	//
	// WEAPON_LOCK_NO_LOS
	//
	////////////////////////////////////////

	//
	// if air or ground radar then check line of sight
	//

	if ((system == TARGET_ACQUISITION_SYSTEM_GROUND_RADAR) || (system == TARGET_ACQUISITION_SYSTEM_AIR_RADAR))
	{
		if (!get_local_entity_int_value (target, INT_TYPE_GUNSHIP_RADAR_LOS_CLEAR))
		{
			weapon_lock_type = WEAPON_LOCK_NO_LOS;

			return;
		}
	}

	////////////////////////////////////////
	//
	// WEAPON_LOCK_NO_BORESIGHT
	//
	////////////////////////////////////////

	//
	// a boresight_weapon will be an unguided weapon so the seeker limit test is not being repeated here
	//

	if (weapon_database[selected_weapon_type].boresight_weapon)
	{
		update_entity_weapon_system_weapon_and_target_vectors (source);

		if (get_local_entity_int_value (source, INT_TYPE_WEAPON_AND_TARGET_VECTORS_VALID))
		{
			weapon_vector = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_WEAPON_VECTOR);

			weapon_to_target_vector = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_WEAPON_TO_TARGET_VECTOR);

			theta = get_3d_unit_vector_dot_product (weapon_vector, weapon_to_target_vector);

			theta = fabs (acos (theta));

			if (theta > rad (1.0))
			{
				weapon_lock_type = WEAPON_LOCK_NO_BORESIGHT;

				return;
			}
		}
		else
		{
			//
			// this should never happen
			//

			#if DEBUG_MODULE
			debug_colour_log (DEBUG_COLOUR_RED, "WARNING! Target and weapon vectors are not valid");
			#endif
		}
	}

	////////////////////////////////////////
	//
	// WEAPON_LOCK_MIN_RANGE
	// WEAPON_LOCK_MAX_RANGE
	//
	////////////////////////////////////////

	source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);
	if (target)
		target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

	target_range = get_3d_range (source_position, target_position);

	weapon_min_range = weapon_database[selected_weapon_type].min_range;

	if (weapon_database[selected_weapon_type].flight_profile_or_self_destr == 1)
	{
		if (get_local_entity_int_value (source, INT_TYPE_LOCK_ON_AFTER_LAUNCH))
		{
			weapon_min_range = 0.5 * weapon_database[selected_weapon_type].max_range;
		}
	}

	if (target_range < weapon_min_range)
	{
		weapon_lock_type = WEAPON_LOCK_MIN_RANGE;

		return;
	}

	weapon_max_range = weapon_database[selected_weapon_type].max_range;

	if (weapon_database[selected_weapon_type].flight_profile_or_self_destr == 1)
	{
		if (get_local_entity_int_value (source, INT_TYPE_LOCK_ON_AFTER_LAUNCH))
		{
			weapon_max_range *= 1.1;
		}
	}

	if (target_range > weapon_max_range)
	{
		weapon_lock_type = WEAPON_LOCK_MAX_RANGE;

		return;
	}

	////////////////////////////////////////
	//
	// WEAPON_LOCK_VALID
	//
	////////////////////////////////////////

	weapon_lock_type = WEAPON_LOCK_VALID;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void increase_rocket_salvo_size (void)
{
	switch (rocket_salvo_size)
	{
		////////////////////////////////////////
		case 1:
		////////////////////////////////////////
		{
			rocket_salvo_size = 2;

			break;
		}
		////////////////////////////////////////
		case 2:
		////////////////////////////////////////
		{
			rocket_salvo_size = 4;

			break;
		}
		////////////////////////////////////////
		case 4:
		////////////////////////////////////////
		{
			if (get_global_gunship_type() == GUNSHIP_TYPE_HIND)
				rocket_salvo_size = 10;
			else
				rocket_salvo_size = 8;

			break;
		}
		////////////////////////////////////////
		case 8:
		////////////////////////////////////////
		{
			rocket_salvo_size = 16;

			break;
		}
		////////////////////////////////////////
		case 10:
		////////////////////////////////////////
		{
			rocket_salvo_size = 2;

			break;
		}
		////////////////////////////////////////
		case 16:
		////////////////////////////////////////
		{
			rocket_salvo_size = ROCKET_SALVO_SIZE_ALL;

			break;
		}
		////////////////////////////////////////
		case ROCKET_SALVO_SIZE_ALL:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal ("Invalid rocket salvo size = %d", rocket_salvo_size);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void decrease_rocket_salvo_size (void)
{
	switch (rocket_salvo_size)
	{
		////////////////////////////////////////
		case 1:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case 2:
		////////////////////////////////////////
		{
			if (get_global_gunship_type() == GUNSHIP_TYPE_HIND)
				rocket_salvo_size = 10;
			else
				rocket_salvo_size = 1;

			break;
		}
		////////////////////////////////////////
		case 4:
		////////////////////////////////////////
		{
			rocket_salvo_size = 2;

			break;
		}
		////////////////////////////////////////
		case 8:
		////////////////////////////////////////
		{
			rocket_salvo_size = 4;

			break;
		}
		////////////////////////////////////////
		case 10:
		////////////////////////////////////////
		{
			rocket_salvo_size = 4;

			break;
		}
		////////////////////////////////////////
		case 16:
		////////////////////////////////////////
		{
			rocket_salvo_size = 8;

			break;
		}
		////////////////////////////////////////
		case ROCKET_SALVO_SIZE_ALL:
		////////////////////////////////////////
		{
			rocket_salvo_size = 16;

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal ("Invalid rocket salvo size = %d", rocket_salvo_size);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_gunship_weapon (entity_sub_types weapon_sub_type)
{
	entity
		*en;

	ASSERT (entity_sub_type_weapon_valid (weapon_sub_type));

	en = get_gunship_entity ();

	if (weapon_sub_type != get_local_entity_int_value (en, INT_TYPE_SELECTED_WEAPON))
	{
		set_client_server_entity_int_value (en, INT_TYPE_SELECTED_WEAPON, weapon_sub_type);
	}

	//
	// ensure navigation HUD mode is set
	//

	if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
	{
		hud_mode = previous_hud_mode;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void play_common_cpg_radar_jammer_speech (int damaged)
{
	if (!get_global_auto_counter_measures ())
	{
		if (!damaged)
		{
			if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_RADAR_JAMMER_ON))
			{
				play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_RADAR_JAMMER_ON);
			}
			else
			{
				play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_RADAR_JAMMER_OFF);
			}
		}
		else
		{
			play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_RADAR_JAMMER_DAMAGED);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void play_common_cpg_infra_red_jammer_speech (int damaged)
{
	if (!get_global_auto_counter_measures ())
	{
		if (!damaged)
		{
			if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_INFRA_RED_JAMMER_ON))
			{
				play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_IR_JAMMER_ON);
			}
			else
			{
				play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_IR_JAMMER_OFF);
			}
		}
		else
		{
			play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_IR_JAMMER_DAMAGED);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void play_common_cpg_failed_launch_speech (weapon_lock_types type)
{
	switch (type)
	{
		////////////////////////////////////////
		case WEAPON_LOCK_NO_ACQUIRE:
		////////////////////////////////////////
		{
			play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_NO_TARGETING_SYSTEM);

			break;
		}
		////////////////////////////////////////
		case WEAPON_LOCK_NO_WEAPON:
		////////////////////////////////////////
		{
			play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_NO_WEAPON);

			break;
		}
		////////////////////////////////////////
		case WEAPON_LOCK_NO_TARGET:
		////////////////////////////////////////
		{
			play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_NO_TARGET);

			break;
		}
		////////////////////////////////////////
		case WEAPON_LOCK_INVALID_TARGET:
		////////////////////////////////////////
		{
			play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_INVALID_TARGET);

			break;
		}
		////////////////////////////////////////
		case WEAPON_LOCK_SEEKER_LIMIT:
		////////////////////////////////////////
		{
			play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_TARGET_OUTSIDE_SEEKER_LIMIT);

			break;
		}
		////////////////////////////////////////
		case WEAPON_LOCK_NO_LOS:
		////////////////////////////////////////
		{
			play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_NO_LOS);

			break;
		}
		////////////////////////////////////////
		case WEAPON_LOCK_MAX_RANGE:
		////////////////////////////////////////
		{
			play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_TARGET_OUT_OF_RANGE);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_good_tone (void)
{
	if (good_tone_delay > 0.0)
	{
		good_tone_delay -= get_delta_time ();

		if (good_tone_delay <= 0.0)
		{
			good_tone_delay = 0.0;

			play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_GOOD_TONE);
		}
	}

	if (!good_tone)
	{
		if (frand1 () < 0.5)
		{
			good_tone_delay = 0.5 + (frand1 () * 0.5);
		}
	}

	good_tone = TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_good_tone (void)
{
	good_tone = FALSE;

	good_tone_delay = 0.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void lase_range_for_ballistics_sight(void)
{
	vec3d target_position;
	float range = get_eo_los_intercept_point(&target_position);
	float angle_of_drop;
	float time_of_flight;
	entity_sub_types wpn_type = get_local_entity_int_value (get_gunship_entity (), INT_TYPE_SELECTED_WEAPON);

	angle_of_drop = 0.0;

	if (weapon_database[wpn_type].aiming_type == WEAPON_AIMING_TYPE_CALC_LEAD_AND_BALLISTIC)
		get_ballistic_pitch_deflection(wpn_type, range, current_flight_dynamics->pitch.value, &angle_of_drop, &time_of_flight, FALSE, TRUE, weapon_database [wpn_type].acquire_parent_forward_velocity * get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_VELOCITY));

	ballistics_sight_calibrated_drop = angle_of_drop;
}

float get_weapon_drop(entity_sub_types wpn_type) // boresight weapon
{
	entity* target = get_local_entity_parent (get_gunship_entity(), LIST_TYPE_TARGET);

	if (target)
	{
		float range = 1000.0;
		vec3d *source_position, target_position;
		float angle_of_projection;
		float time_of_flight;
		source_position = get_local_entity_vec3d_ptr (get_gunship_entity(), VEC3D_TYPE_POSITION);

		get_local_entity_target_point (target, &target_position);
		if (get_range_finder() == RANGEFINDER_TRIANGULATION)
		{
			range = get_triangulated_by_position_range(source_position, &target_position);
			if (range == -1.0)
				range = 1000.0;  // use 1000 meters if unable to triangulate range
		}
		else
			range = get_3d_range (source_position, &target_position);

		if (weapon_database[wpn_type].aiming_type == WEAPON_AIMING_TYPE_CALC_LEAD_AND_BALLISTIC || weapon_database[wpn_type].aiming_type == WEAPON_AIMING_TYPE_CALC_ANGLE_OF_PROJECTION)
		{
			angle_of_projection = 0.0;
			get_ballistic_pitch_deflection(wpn_type, range, source_position->y - target_position.y, &angle_of_projection, &time_of_flight, FALSE, FALSE, weapon_database [wpn_type].acquire_parent_forward_velocity * get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_VELOCITY));
			angle_of_projection += asin((source_position->y - target_position.y) / range);
		}
		else
		{
			float weapon_velocity = weapon_database[wpn_type].cruise_velocity;
			if (!get_angle_of_projection_with_range(source_position, &target_position, weapon_velocity, &angle_of_projection, range))
				angle_of_projection = 0.0;
		}

		ballistics_sight_calibrated_drop = angle_of_projection;
	}

	return ballistics_sight_calibrated_drop;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_missile_flight_time (void)
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
	// find first launched Hellfire with a target (first found on list)
	//

	weapon = get_local_entity_first_child (en, LIST_TYPE_LAUNCHED_WEAPON);
	if (weapon)
		weapon = get_local_entity_child_pred_circular(weapon, LIST_TYPE_LAUNCHED_WEAPON);

	while (weapon)
	{
		int show_flight_time = FALSE;
		weapon_sub_type = get_local_entity_int_value (weapon, INT_TYPE_ENTITY_SUB_TYPE);

		switch (weapon_sub_type)
		{
		case ENTITY_SUB_TYPE_WEAPON_AGM114L_LONGBOW_HELLFIRE:
		case ENTITY_SUB_TYPE_WEAPON_AGM114K_HELLFIRE_II:
		case ENTITY_SUB_TYPE_WEAPON_AGM114R_HELLFIRE_II:
		case ENTITY_SUB_TYPE_WEAPON_9M120_ATAKA_V:
		case ENTITY_SUB_TYPE_WEAPON_9K121_VIKHR:
		case ENTITY_SUB_TYPE_WEAPON_9M114_SHTURM:
		case ENTITY_SUB_TYPE_WEAPON_KH_25MT:
		case ENTITY_SUB_TYPE_WEAPON_KH_29L:
			show_flight_time = TRUE;
			break;
		default:
			show_flight_time = FALSE;
			break;
		}

		if (show_flight_time)
		{
			target = get_local_entity_parent (weapon, LIST_TYPE_TARGET);

			target_position = get_eo_tracking_point();
			if (!target_position && target)
				target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

			if (target_position)
			{
				float cruise_velocity = weapon_database[weapon_sub_type].cruise_velocity * 0.75;

				weapon_position = get_local_entity_vec3d_ptr (weapon, VEC3D_TYPE_POSITION);
				target_range = get_3d_range (weapon_position, target_position);

				// if rocket still burning and accelerating, use cruise velocity
				if (get_local_entity_float_value(weapon, FLOAT_TYPE_WEAPON_LIFETIME) > 0.0)
					weapon_velocity = cruise_velocity;
				else
					weapon_velocity = bound(get_local_entity_float_value (weapon, FLOAT_TYPE_VELOCITY), 0.0, cruise_velocity);

				if (weapon_velocity > 0.0)
				{
					flight_time = target_range / weapon_velocity;

					break;
				}
			}
		}

		weapon = get_local_entity_child_pred (weapon, LIST_TYPE_LAUNCHED_WEAPON);
	}

	return (flight_time);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_ballistic_weapon_drop(entity_sub_types weapon_sub_type, float* hud_aim_range)
{
#define MAX_RANGE weapon_database[weapon_sub_type].max_range
	static float
		angle_of_drop = 0.0;

	float
		time_of_flight,
		triangulated_range,
		range_diff,
		height = current_flight_dynamics->radar_altitude.value,
		pitch = current_flight_dynamics->pitch.value;

	if (get_time_acceleration() != TIME_ACCELERATION_PAUSE)
	{
		if (pitch > (angle_of_drop + rad(0.05)) || height < 2.0)
			triangulated_range = MAX_RANGE;
		else
			triangulated_range = bound(height / tan(-pitch + angle_of_drop), 0.0, MAX_RANGE);

		range_diff = triangulated_range - *hud_aim_range;
		// move the aiming range in gradual steps, so as not to come into a oscilating
		// state where it continousely overcorrects in alternating directions
		*hud_aim_range += 0.25 * range_diff;

		if (!get_ballistic_pitch_deflection(weapon_sub_type, *hud_aim_range, pitch, &angle_of_drop, &time_of_flight, FALSE, TRUE, weapon_database [weapon_sub_type].acquire_parent_forward_velocity * get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_VELOCITY)))
			angle_of_drop = 0.0;
	}

	return angle_of_drop;
}
