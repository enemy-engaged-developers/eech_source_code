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

#define DEBUG_MODULE	0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MASTER CAUTION LAMP
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MASTER_CAUTION_FLASH_RATE	(0.5)

static int
	master_caution_alert,
	engine_damage_imminent_status,
	previous_engine_damage_imminent_status;

static float
	master_caution_flash_timer;

static float
	master_caution_sound_timer;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void initialise_master_caution_lamp (void)
{
	master_caution_alert = FALSE;

	master_caution_flash_timer = 0.0;

	master_caution_sound_timer = 0.0;

	engine_damage_imminent_status = FALSE;

	previous_engine_damage_imminent_status = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void deinitialise_master_caution_lamp (void)
{
	if (get_gunship_entity ())
	{
		pause_local_entity_sound_type (get_gunship_entity (), ENTITY_SUB_TYPE_EFFECT_SOUND_MCA, 0.5);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void activate_hind_master_caution_lamp (void)
{
	hind_lamps.master_caution = 1;

	master_caution_alert = TRUE;

	master_caution_flash_timer = MASTER_CAUTION_FLASH_RATE;

	master_caution_sound_timer = 3.0;

	resume_local_entity_sound_type (get_gunship_entity (), ENTITY_SUB_TYPE_EFFECT_SOUND_MCA);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deactivate_hind_master_caution_lamp (void)
{
	hind_lamps.master_caution = 0;

	master_caution_alert = FALSE;

	master_caution_flash_timer = 0.0;

	master_caution_sound_timer = 0.0;

	pause_local_entity_sound_type (get_gunship_entity (), ENTITY_SUB_TYPE_EFFECT_SOUND_MCA, 0.5);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_master_caution_lamp (void)
{
	//
	// monitor engine damage
	//

	engine_damage_imminent_status = get_current_flight_dynamics_engine_damage_imminent ();

	if ((!previous_engine_damage_imminent_status) && engine_damage_imminent_status)
	{
		play_client_server_warning_message (get_gunship_entity (), SPEECH_SYSTEM_ENGINE_OVERTORQUE);

		activate_hind_master_caution_lamp ();
	}

	previous_engine_damage_imminent_status = engine_damage_imminent_status;

	//
	// update master caution lamp
	//

	if (master_caution_alert)
	{
		master_caution_flash_timer -= get_delta_time ();

		if (master_caution_flash_timer <= 0.0)
		{
			master_caution_flash_timer = MASTER_CAUTION_FLASH_RATE;

			hind_lamps.master_caution ^= 1;
		}

		master_caution_sound_timer -= get_delta_time ();

		if (master_caution_sound_timer <= 0.0)
		{
			master_caution_sound_timer = 0.0;

			pause_local_entity_sound_type (get_gunship_entity (), ENTITY_SUB_TYPE_EFFECT_SOUND_MCA, 0.5);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// THREAT WARNING DISPLAY
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define CLOSEST_MISSILE_FLASH_RATE	(0.333)

static int
	closest_missile_flash_state;

static float
	closest_missile_flash_timer;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void initialise_threat_warning_display (void)
{
	closest_missile_flash_state = 0;

	closest_missile_flash_timer = 0.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void clear_threat_warning_display_lamps (void)
{
	hind_lamps.threat_warning_radar_type_1						= 0;
	hind_lamps.threat_warning_radar_type_2						= 0;
	hind_lamps.threat_warning_radar_type_3						= 0;
	hind_lamps.threat_warning_radar_type_4						= 0;
	hind_lamps.threat_warning_radar_type_5						= 0;
	hind_lamps.threat_warning_radar_type_6						= 0;
	hind_lamps.threat_warning_bearing_lh_rear					= 0;
	hind_lamps.threat_warning_bearing_rh_rear					= 0;
	hind_lamps.threat_warning_close_range_1						= 0;
	hind_lamps.threat_warning_close_range_2						= 0;
	hind_lamps.threat_warning_close_range_3						= 0;
	hind_lamps.threat_warning_close_range_4						= 0;
	hind_lamps.threat_warning_close_range_5						= 0;
	hind_lamps.threat_warning_close_range_6						= 0;
	hind_lamps.threat_warning_close_range_7						= 0;
	hind_lamps.threat_warning_close_range_8						= 0;
	hind_lamps.threat_warning_close_range_9						= 0;
	hind_lamps.threat_warning_close_range_10						= 0;
	hind_lamps.threat_warning_close_range_11						= 0;
	hind_lamps.threat_warning_close_range_12						= 0;
	hind_lamps.threat_warning_close_range_13						= 0;
	hind_lamps.threat_warning_close_range_14						= 0;
	hind_lamps.threat_warning_close_range_15						= 0;
	hind_lamps.threat_warning_bearing_lh_90_close_range		= 0;
	hind_lamps.threat_warning_bearing_lh_50_close_range		= 0;
	hind_lamps.threat_warning_bearing_lh_30_close_range		= 0;
	hind_lamps.threat_warning_bearing_lh_10_close_range		= 0;
	hind_lamps.threat_warning_bearing_rh_10_close_range		= 0;
	hind_lamps.threat_warning_bearing_rh_30_close_range		= 0;
	hind_lamps.threat_warning_bearing_rh_50_close_range		= 0;
	hind_lamps.threat_warning_bearing_rh_90_close_range		= 0;
	hind_lamps.threat_warning_bearing_lh_90						= 0;
	hind_lamps.threat_warning_bearing_lh_50						= 0;
	hind_lamps.threat_warning_bearing_lh_30						= 0;
	hind_lamps.threat_warning_bearing_lh_10						= 0;
	hind_lamps.threat_warning_bearing_rh_10						= 0;
	hind_lamps.threat_warning_bearing_rh_30						= 0;
	hind_lamps.threat_warning_bearing_rh_50						= 0;
	hind_lamps.threat_warning_bearing_rh_90						= 0;
	hind_lamps.threat_warning_missile_below						= 0;
	hind_lamps.threat_warning_missile_above						= 0;
	hind_lamps.threat_warning_missile_lh_lock					= 0;
	hind_lamps.threat_warning_missile_rh_lock					= 0;
	hind_lamps.threat_warning_bearing_lh_rear_close_range	= 0;
	hind_lamps.threat_warning_bearing_rh_rear_close_range	= 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void light_threat_bearing_lamp (float theta)
{
	if (theta >= 0.0)
	{
		if (theta <= rad (10.0 + 10.0))
		{
			hind_lamps.threat_warning_bearing_rh_10 = 1;
		}
		else if (theta <= rad (30.0 + 10.0))
		{
			hind_lamps.threat_warning_bearing_rh_30 = 1;
		}
		else if (theta <= rad (50.0 + 20.0))
		{
			hind_lamps.threat_warning_bearing_rh_50 = 1;
		}
		else if (theta <= rad (90.0 + 30.0))
		{
			hind_lamps.threat_warning_bearing_rh_90 = 1;
		}
		else
		{
			hind_lamps.threat_warning_bearing_rh_rear = 1;
		}
	}
	else
	{
		if (theta >= rad (-10.0 + -10.0))
		{
			hind_lamps.threat_warning_bearing_lh_10 = 1;
		}
		else if (theta >= rad (-30.0 + -10.0))
		{
			hind_lamps.threat_warning_bearing_lh_30 = 1;
		}
		else if (theta >= rad (-50.0 + -20.0))
		{
			hind_lamps.threat_warning_bearing_lh_50 = 1;
		}
		else if (theta >= rad (-90.0 + -30.0))
		{
			hind_lamps.threat_warning_bearing_lh_90 = 1;
		}
		else
		{
			hind_lamps.threat_warning_bearing_lh_rear = 1;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
static void light_close_range_threat_bearing_lamp (float theta, int state)
{
	if (theta >= 0.0)
	{
		if (theta <= rad (10.0 + 10.0))
		{
			hind_lamps.threat_warning_bearing_rh_10_close_range = state;
		}
		else if (theta <= rad (30.0 + 10.0))
		{
			hind_lamps.threat_warning_bearing_rh_30_close_range = state;
		}
		else if (theta <= rad (50.0 + 20.0))
		{
			hind_lamps.threat_warning_bearing_rh_50_close_range = state;
		}
		else if (theta <= rad (90.0 + 30.0))
		{
			hind_lamps.threat_warning_bearing_rh_90_close_range = state;
		}
		else
		{
			hind_lamps.threat_warning_bearing_rh_rear_close_range = state;
		}
	}
	else
	{
		if (theta >= rad (-10.0 + -10.0))
		{
			hind_lamps.threat_warning_bearing_lh_10_close_range = state;
		}
		else if (theta >= rad (-30.0 + -10.0))
		{
			hind_lamps.threat_warning_bearing_lh_30_close_range = state;
		}
		else if (theta >= rad (-50.0 + -20.0))
		{
			hind_lamps.threat_warning_bearing_lh_50_close_range = state;
		}
		else if (theta >= rad (-90.0 + -30.0))
		{
			hind_lamps.threat_warning_bearing_lh_90_close_range = state;
		}
		else
		{
			hind_lamps.threat_warning_bearing_lh_rear_close_range = state;
		}
	}
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if 0
static void light_missile_approaching_lamps (float time_to_impact)
{
	int
		segment;

	if (time_to_impact < 15.0)
	{
		convert_float_to_int (15.0 - time_to_impact, &segment);

		ASSERT ((segment >= 0) && (segment <= 14));

		switch (segment)
		{
			case 14: hind_lamps.threat_warning_close_range_15 = 1;
			case 13: hind_lamps.threat_warning_close_range_14 = 1;
			case 12: hind_lamps.threat_warning_close_range_13 = 1;
			case 11: hind_lamps.threat_warning_close_range_12 = 1;
			case 10: hind_lamps.threat_warning_close_range_11 = 1;
			case  9: hind_lamps.threat_warning_close_range_10 = 1;
			case  8: hind_lamps.threat_warning_close_range_9 = 1;
			case  7: hind_lamps.threat_warning_close_range_8 = 1;
			case  6: hind_lamps.threat_warning_close_range_7 = 1;
			case  5: hind_lamps.threat_warning_close_range_6 = 1;
			case  4: hind_lamps.threat_warning_close_range_5 = 1;
			case  3: hind_lamps.threat_warning_close_range_4 = 1;
			case  2: hind_lamps.threat_warning_close_range_3 = 1;
			case  1: hind_lamps.threat_warning_close_range_2 = 1;
			case  0: hind_lamps.threat_warning_close_range_1 = 1;
		}
	}
}
#endif

static void light_signal_strength_lamps(float range, float max_range)
{
	float range_ratio;
	int segment;

	ASSERT(max_range > 0.0);
	if (max_range > 0.0)
	{
		range_ratio = 0.99 - bound(range/(max_range * 1.5), 0.0, 0.99);
		segment = (int)(range_ratio * 15);
	}
	else
		segment = 14;

	switch (segment)
	{
		case 14: hind_lamps.threat_warning_close_range_15 = 1;
		case 13: hind_lamps.threat_warning_close_range_14 = 1;
		case 12: hind_lamps.threat_warning_close_range_13 = 1;
		case 11: hind_lamps.threat_warning_close_range_12 = 1;
		case 10: hind_lamps.threat_warning_close_range_11 = 1;
		case  9: hind_lamps.threat_warning_close_range_10 = 1;
		case  8: hind_lamps.threat_warning_close_range_9 = 1;
		case  7: hind_lamps.threat_warning_close_range_8 = 1;
		case  6: hind_lamps.threat_warning_close_range_7 = 1;
		case  5: hind_lamps.threat_warning_close_range_6 = 1;
		case  4: hind_lamps.threat_warning_close_range_5 = 1;
		case  3: hind_lamps.threat_warning_close_range_4 = 1;
		case  2: hind_lamps.threat_warning_close_range_3 = 1;
		case  1: hind_lamps.threat_warning_close_range_2 = 1;
		case  0: hind_lamps.threat_warning_close_range_1 = 1;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_threat_warning_display (void)
{
	entity
		*source,
		*threat;

	int
		above = FALSE,
		overshot,
		threat_active;

	float
		dx,
		dy,
		dz,
		theta,
		threat_bearing,
		threat_range,
		threat_velocity,
		time_to_impact,
		source_heading,
		length,
		cos_error;

	threat_types
		threat_type;

	vec3d
		*source_position,
		*threat_position,
		uvec_threat_to_target;

	matrix3x3
		*attitude;

	clear_threat_warning_display_lamps ();

	if (hind_damage.threat_warning_display || hind_damage.radar_warning_system)
	{
		return;
	}

	threat = get_local_entity_first_child (get_gunship_entity (), LIST_TYPE_TARGET);

	if (threat)
	{
		source = get_gunship_entity ();

		source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

		source_heading = get_local_entity_float_value (source, FLOAT_TYPE_HEADING);

		while (threat)
		{
			entity_sub_types sub_type = get_local_entity_int_value(threat, INT_TYPE_ENTITY_SUB_TYPE);
			float max_range = 10.0;

			threat_type = get_local_entity_int_value (threat, INT_TYPE_THREAT_TYPE);

			//
			// check threat is active
			//

			if (get_local_entity_int_value (threat, INT_TYPE_IDENTIFY_VEHICLE))
			{
				max_range = vehicle_database[sub_type].air_scan_range;
				threat_active = get_local_entity_int_value (threat, INT_TYPE_RADAR_ON);
			}
			else if (get_local_entity_int_value (threat, INT_TYPE_IDENTIFY_AIRCRAFT))
			{
				max_range = aircraft_database[sub_type].air_scan_range;
				threat_active = get_local_entity_int_value (threat, INT_TYPE_RADAR_ON);
			}
			else if (get_local_entity_int_value (threat, INT_TYPE_IDENTIFY_WEAPON))
			{
				weapon_guidance_types guidance = weapon_database[sub_type].guidance_type;

				threat_active = guidance == WEAPON_GUIDANCE_TYPE_ACTIVE_RADAR;
				if (guidance == WEAPON_GUIDANCE_TYPE_ACTIVE_RADAR || guidance == WEAPON_GUIDANCE_TYPE_SEMI_ACTIVE_RADAR)
				{
					hind_lamps.threat_warning_missile_lh_lock = 1;
					hind_lamps.threat_warning_missile_rh_lock = 1;
				}

				max_range = weapon_database[sub_type].max_range;
			}

#if 0
			switch (threat_type)
			{
				////////////////////////////////////////
				case THREAT_TYPE_INVALID:
				////////////////////////////////////////
				{
					threat_active = FALSE;

					break;
				}
				////////////////////////////////////////
				case THREAT_TYPE_RF_MISSILE:
				////////////////////////////////////////
				{
					ASSERT(get_local_entity_int_value (threat, INT_TYPE_IDENTIFY_WEAPON));

					if (!hind_damage.radar_warning_system)
					{
						threat_active = TRUE;
					}
					else
					{
						threat_active = FALSE;
					}

					break;
				}
				////////////////////////////////////////
				case THREAT_TYPE_IR_MISSILE:
				////////////////////////////////////////
				{
					threat_active = FALSE;

					break;
				}
				////////////////////////////////////////
				case THREAT_TYPE_LASER_MISSILE:
				////////////////////////////////////////
				{
					threat_active = FALSE;

					break;
				}
				////////////////////////////////////////
				case THREAT_TYPE_AIRBORNE_RADAR:
				////////////////////////////////////////
				{
					if (!hind_damage.radar_warning_system)
					{
						threat_active = get_local_entity_int_value (threat, INT_TYPE_RADAR_ON);
					}
					else
					{
						threat_active = FALSE;
					}

					break;
				}
				////////////////////////////////////////
				case THREAT_TYPE_SAM:
				////////////////////////////////////////
				{
					if (!hind_damage.radar_warning_system)
					{
						threat_active = get_local_entity_int_value (threat, INT_TYPE_RADAR_ON);
					}
					else
					{
						threat_active = FALSE;
					}

					break;
				}
				////////////////////////////////////////
				case THREAT_TYPE_AAA:
				////////////////////////////////////////
				{
					if (!hind_damage.radar_warning_system)
					{
						threat_active = get_local_entity_int_value (threat, INT_TYPE_RADAR_ON);
					}
					else
					{
						threat_active = FALSE;
					}

					break;
				}
				////////////////////////////////////////
				case THREAT_TYPE_EARLY_WARNING_RADAR:
				////////////////////////////////////////
				{
					if (!hind_damage.radar_warning_system)
					{
						threat_active = get_local_entity_int_value (threat, INT_TYPE_RADAR_ON);
					}
					else
					{
						threat_active = FALSE;
					}

					break;
				}
				////////////////////////////////////////
				default:
				////////////////////////////////////////
				{
					debug_fatal ("Invalid threat type = %d", threat_type);

					break;
				}
			}
#endif

			if (threat_active)
			{
				//
				// get threat direction wrt aircraft datum
				//

				threat_position = get_local_entity_vec3d_ptr (threat, VEC3D_TYPE_POSITION);

				dx = threat_position->x - source_position->x;
				dy = threat_position->y - source_position->y;
				dz = threat_position->z - source_position->z;

				threat_range = sqrt ((dx * dx) + (dy * dy) + (dz * dz));
				above = dy > 0.0;
				threat_bearing = atan2 (dx, dz);
				theta = threat_bearing - source_heading;

				if (theta > rad (180.0))
				{
					theta -= rad (360.0);
				}
				else if (theta < rad (-180.0))
				{
					theta += rad (360.0);
				}

				//
				// if missile threat then guard against 'overshot target' to prevent spurious indications
				//

				if ((threat_type == THREAT_TYPE_RF_MISSILE) || (threat_type == THREAT_TYPE_IR_MISSILE) || (threat_type == THREAT_TYPE_LASER_MISSILE))
				{
					threat_velocity = get_local_entity_float_value (threat, FLOAT_TYPE_VELOCITY);

					time_to_impact = threat_range / max (threat_velocity, 1.0);

					overshot = FALSE;

					if (time_to_impact < 1.0)
					{
						uvec_threat_to_target.x = source_position->x - threat_position->x;
						uvec_threat_to_target.y = source_position->y - threat_position->y;
						uvec_threat_to_target.z = source_position->z - threat_position->z;

						length = get_3d_vector_magnitude (&uvec_threat_to_target);

						if (length > 1.0)
						{
							normalise_3d_vector_given_magnitude (&uvec_threat_to_target, length);

							attitude = get_local_entity_attitude_matrix_ptr (threat);

							cos_error = get_3d_unit_vector_dot_product ((vec3d *) &((*attitude) [2][0]), &uvec_threat_to_target);

							if (cos_error < 0.0)
							{
								overshot = TRUE;
							}
						}
						else
						{
							overshot = TRUE;
						}
					}

					if (!overshot)
					{
						light_threat_bearing_lamp (theta);
						light_signal_strength_lamps(threat_range, max_range);

						hind_lamps.threat_warning_radar_type_1 = 1;

						if (above)
							hind_lamps.threat_warning_missile_above = 1;
						else
							hind_lamps.threat_warning_missile_below = 1;
					}
				}
				else
				{
					light_threat_bearing_lamp (theta);
					light_signal_strength_lamps(threat_range, max_range);

					if (above)
						hind_lamps.threat_warning_missile_above = 1;
					else
						hind_lamps.threat_warning_missile_below = 1;

					if (threat_type == THREAT_TYPE_AIRBORNE_RADAR)
						hind_lamps.threat_warning_radar_type_1 = 1;
					else
					{
						if (max_range <= 4000.0)  // short range
							hind_lamps.threat_warning_radar_type_4 = 1;
						else if (max_range <= 10000.0)   // medium range
							hind_lamps.threat_warning_radar_type_3 = 1;
						else  // long range
							hind_lamps.threat_warning_radar_type_2 = 1;
					}

				}
			}

			threat = get_local_entity_child_succ (threat, LIST_TYPE_TARGET);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// WARNING PANEL LAMPS
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_warning_panel_lamps (void)
{
	entity
		*en;

	en = get_gunship_entity ();

	hind_lamps.warning_1 = get_dynamics_damage_type (DYNAMICS_DAMAGE_LEFT_ENGINE_FIRE);

	hind_lamps.warning_2 = get_dynamics_damage_type (DYNAMICS_DAMAGE_RIGHT_ENGINE_FIRE);

	hind_lamps.warning_3 = get_current_flight_dynamics_overtorque ();

	hind_lamps.warning_4 = get_local_entity_int_value (en, INT_TYPE_RADAR_ON);

	hind_lamps.warning_5 = get_current_flight_dynamics_auto_pilot ();

	hind_lamps.warning_6 = get_current_flight_dynamics_auto_hover ();

	hind_lamps.warning_7 = get_local_entity_int_value (en, INT_TYPE_RADAR_JAMMER_ON);

	hind_lamps.warning_8 = get_local_entity_int_value (en, INT_TYPE_INFRA_RED_JAMMER_ON);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// STATUS PANEL LAMPS
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_status_panel_lamps (void)
{
	hind_lamps.status_1 = hind_damage.radar;

	hind_lamps.status_2 = hind_damage.flir;

	hind_lamps.status_3 = hind_damage.llltv;

	hind_lamps.status_4 = hind_damage.laser_range_finder;

	hind_lamps.status_5 = hind_damage.radar_jammer;

	hind_lamps.status_6 = hind_damage.infra_red_jammer;

	hind_lamps.status_7 = hind_damage.navigation_computer;

	hind_lamps.status_8 = hind_damage.communications;

	hind_lamps.status_9 = hind_damage.radar_warning_system;

	hind_lamps.status_10 = hind_damage.head_up_display;

	hind_lamps.status_11 = hind_damage.helmet_mounted_sight;

	hind_lamps.status_12 = hind_damage.tv_display;

	hind_lamps.status_13 = hind_damage.threat_warning_display;

	hind_lamps.status_14 = hind_damage.night_vision_goggles;

	hind_lamps.status_15 = fire_extinguisher_used;

	hind_lamps.status_16 = get_current_flight_dynamics_rotor_brake ();

	hind_lamps.status_17 = get_current_flight_dynamics_wheel_brake ();

	hind_lamps.status_18 = get_global_auto_counter_measures ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// WEAPON STATUS LAMPS
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define WEAPON_ARMED_FLASH_RATE	(0.75)

static int
	weapon_armed_flash_state;

static float
	weapon_armed_flash_timer;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void initialise_weapon_status_lamps (void)
{
	weapon_armed_flash_state = 0;

	weapon_armed_flash_timer = 0.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_weapon_status_lamps (void)
{
	entity
		*en;

	entity_sub_types
		selected_weapon,
		weapon_sub_type;

	int
		number,
		damaged;

	hind_lamps.weapons_management_lh_outer_pylon_green			= 0;
	hind_lamps.weapons_management_lh_inner_pylon_green			= 0;
	hind_lamps.weapons_management_rh_inner_pylon_green			= 0;
	hind_lamps.weapons_management_rh_outer_pylon_green			= 0;
	hind_lamps.weapons_management_armour_piercing_cannon_green	= 0;
	hind_lamps.weapons_management_high_explosive_cannon_green	= 0;
	hind_lamps.weapons_management_lh_outer_pylon_red				= 0;
	hind_lamps.weapons_management_lh_inner_pylon_red				= 0;
	hind_lamps.weapons_management_rh_inner_pylon_red				= 0;
	hind_lamps.weapons_management_rh_outer_pylon_red				= 0;
	hind_lamps.weapons_management_armour_piercing_cannon_red	= 0;
	hind_lamps.weapons_management_high_explosive_cannon_red		= 0;
	hind_lamps.weapons_management_chaff_green						= 0;
	hind_lamps.weapons_management_flare_green						= 0;
	hind_lamps.weapons_management_chaff_red							= 0;
	hind_lamps.weapons_management_flare_red							= 0;

	////////////////////////////////////////

	en = get_gunship_entity ();

	selected_weapon = get_local_entity_int_value (en, INT_TYPE_SELECTED_WEAPON);

	////////////////////////////////////////

	weapon_armed_flash_timer -= get_delta_time ();

	if (weapon_armed_flash_timer <= 0.0)
	{
		weapon_armed_flash_timer = WEAPON_ARMED_FLASH_RATE;

		weapon_armed_flash_state ^= 1;
	}

	////////////////////////////////////////

	if (get_local_entity_weapon_hardpoint_info (en, HIND_LHS_OUTER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, &weapon_sub_type, &number, &damaged))
	{
		if (damaged)
		{
			hind_lamps.weapons_management_lh_outer_pylon_red = 1;
		}
		else
		{
			if (number > 0)
			{
				if (weapon_sub_type == selected_weapon)
				{
					hind_lamps.weapons_management_lh_outer_pylon_green = weapon_armed_flash_state;
				}
				else
				{
					hind_lamps.weapons_management_lh_outer_pylon_green = 1;
				}
			}
		}
	}

	////////////////////////////////////////

	if (get_local_entity_weapon_hardpoint_info (en, HIND_LHS_INNER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, &weapon_sub_type, &number, &damaged))
	{
		if (damaged)
		{
			hind_lamps.weapons_management_lh_inner_pylon_red = 1;
		}
		else
		{
			if (number > 0)
			{
				if (weapon_sub_type == selected_weapon)
				{
					hind_lamps.weapons_management_lh_inner_pylon_green = weapon_armed_flash_state;
				}
				else
				{
					hind_lamps.weapons_management_lh_inner_pylon_green = 1;
				}
			}
		}
	}

	////////////////////////////////////////

	if (get_local_entity_weapon_hardpoint_info (en, HIND_RHS_INNER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, &weapon_sub_type, &number, &damaged))
	{
		if (damaged)
		{
			hind_lamps.weapons_management_rh_inner_pylon_red = 1;
		}
		else
		{
			if (number > 0)
			{
				if (weapon_sub_type == selected_weapon)
				{
					hind_lamps.weapons_management_rh_inner_pylon_green = weapon_armed_flash_state;
				}
				else
				{
					hind_lamps.weapons_management_rh_inner_pylon_green = 1;
				}
			}
		}
	}

	////////////////////////////////////////

	if (get_local_entity_weapon_hardpoint_info (en, HIND_RHS_OUTER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, &weapon_sub_type, &number, &damaged))
	{
		if (damaged)
		{
			hind_lamps.weapons_management_rh_outer_pylon_red = 1;
		}
		else
		{
			if (number > 0)
			{
				if (weapon_sub_type == selected_weapon)
				{
					hind_lamps.weapons_management_rh_outer_pylon_green = weapon_armed_flash_state;
				}
				else
				{
					hind_lamps.weapons_management_rh_outer_pylon_green = 1;
				}
			}
		}
	}

	////////////////////////////////////////

	if (get_local_entity_weapon_hardpoint_info (en, HIND_CANNON_TURRET, ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND, &weapon_sub_type, &number, &damaged))
	{
		if (damaged)
		{
			hind_lamps.weapons_management_armour_piercing_cannon_red = 1;
		}
		else
		{
			if (number > 0)
			{
				if (weapon_sub_type == selected_weapon)
				{
					hind_lamps.weapons_management_armour_piercing_cannon_green = weapon_armed_flash_state;
				}
				else
				{
					hind_lamps.weapons_management_armour_piercing_cannon_green = 1;
				}
			}
		}
	}

	////////////////////////////////////////

	if (get_local_entity_weapon_hardpoint_info (en, HIND_CANNON_TURRET, ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND, &weapon_sub_type, &number, &damaged))
	{
		if (damaged)
		{
			hind_lamps.weapons_management_high_explosive_cannon_red = 1;
		}
		else
		{
			if (number > 0)
			{
				if (weapon_sub_type == selected_weapon)
				{
					hind_lamps.weapons_management_high_explosive_cannon_green = weapon_armed_flash_state;
				}
				else
				{
					hind_lamps.weapons_management_high_explosive_cannon_green = 1;
				}
			}
		}
	}

	////////////////////////////////////////

	if (get_local_entity_weapon_hardpoint_info (en, HIND_LHS_CHAFF_DISPENSER, ENTITY_SUB_TYPE_WEAPON_CHAFF, &weapon_sub_type, &number, &damaged))
	{
		if (damaged)
		{
			hind_lamps.weapons_management_chaff_red = 1;
		}
		else
		{
			if (number > 0)
			{
				hind_lamps.weapons_management_chaff_green = 1;
			}
		}
	}

	////////////////////////////////////////

	if (get_local_entity_weapon_hardpoint_info (en, HIND_LHS_FLARE_DISPENSER, ENTITY_SUB_TYPE_WEAPON_FLARE, &weapon_sub_type, &number, &damaged))
	{
		if (damaged)
		{
			hind_lamps.weapons_management_flare_red = 1;
		}
		else
		{
			if (number > 0)
			{
				hind_lamps.weapons_management_flare_green = 1;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// OIL GAUGES
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_oil_gauges (void)
{
	//
	// pressure
	//

	if (get_dynamics_damage_type (DYNAMICS_DAMAGE_LOW_OIL_PRESSURE))
	{
		hind_lamps.lh_engine_oil_pressure_normal = 0;
		hind_lamps.rh_engine_oil_pressure_normal = 0;
		hind_lamps.lh_engine_oil_pressure_low = 1;
		hind_lamps.rh_engine_oil_pressure_low = 1;
	}
	else
	{
		hind_lamps.lh_engine_oil_pressure_normal = 1;
		hind_lamps.rh_engine_oil_pressure_normal = 1;
		hind_lamps.lh_engine_oil_pressure_low = 0;
		hind_lamps.rh_engine_oil_pressure_low = 0;
	}

	//
	// temperature
	//

	hind_lamps.lh_engine_oil_temperature_normal = 1;
	hind_lamps.rh_engine_oil_temperature_normal = 1;
	hind_lamps.lh_engine_oil_temperature_high = 0;
	hind_lamps.rh_engine_oil_temperature_high = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GENERAL
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// Note that all lamps are extinguished in initialise_hind_lamps ().
//

void initialise_hind_lamp_avionics (void)
{
	initialise_master_caution_lamp ();

	initialise_threat_warning_display ();

	initialise_weapon_status_lamps ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_hind_lamp_avionics (void)
{
	deinitialise_master_caution_lamp ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_hind_lamp_avionics (void)
{
	update_master_caution_lamp ();

	update_threat_warning_display ();

	update_warning_panel_lamps ();

	update_status_panel_lamps ();

	update_weapon_status_lamps ();

	update_oil_gauges ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
