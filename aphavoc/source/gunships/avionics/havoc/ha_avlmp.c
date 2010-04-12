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

void activate_havoc_master_caution_lamp (void)
{
	havoc_lamps.master_caution = 1;

	master_caution_alert = TRUE;

	master_caution_flash_timer = MASTER_CAUTION_FLASH_RATE;

	master_caution_sound_timer = 3.0;

	resume_local_entity_sound_type (get_gunship_entity (), ENTITY_SUB_TYPE_EFFECT_SOUND_MCA);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deactivate_havoc_master_caution_lamp (void)
{
	havoc_lamps.master_caution = 0;

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

		activate_havoc_master_caution_lamp ();
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

			havoc_lamps.master_caution ^= 1;
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
	havoc_lamps.threat_warning_radar_type_1						= 0;
	havoc_lamps.threat_warning_radar_type_2						= 0;
	havoc_lamps.threat_warning_radar_type_3						= 0;
	havoc_lamps.threat_warning_radar_type_4						= 0;
	havoc_lamps.threat_warning_radar_type_5						= 0;
	havoc_lamps.threat_warning_radar_type_6						= 0;
	havoc_lamps.threat_warning_bearing_lh_rear					= 0;
	havoc_lamps.threat_warning_bearing_rh_rear					= 0;
	havoc_lamps.threat_warning_close_range_1						= 0;
	havoc_lamps.threat_warning_close_range_2						= 0;
	havoc_lamps.threat_warning_close_range_3						= 0;
	havoc_lamps.threat_warning_close_range_4						= 0;
	havoc_lamps.threat_warning_close_range_5						= 0;
	havoc_lamps.threat_warning_close_range_6						= 0;
	havoc_lamps.threat_warning_close_range_7						= 0;
	havoc_lamps.threat_warning_close_range_8						= 0;
	havoc_lamps.threat_warning_close_range_9						= 0;
	havoc_lamps.threat_warning_close_range_10						= 0;
	havoc_lamps.threat_warning_close_range_11						= 0;
	havoc_lamps.threat_warning_close_range_12						= 0;
	havoc_lamps.threat_warning_close_range_13						= 0;
	havoc_lamps.threat_warning_close_range_14						= 0;
	havoc_lamps.threat_warning_close_range_15						= 0;
	havoc_lamps.threat_warning_bearing_lh_90_close_range		= 0;
	havoc_lamps.threat_warning_bearing_lh_67_close_range		= 0;
	havoc_lamps.threat_warning_bearing_lh_45_close_range		= 0;
	havoc_lamps.threat_warning_bearing_lh_22_close_range		= 0;
	havoc_lamps.threat_warning_bearing_rh_22_close_range		= 0;
	havoc_lamps.threat_warning_bearing_rh_45_close_range		= 0;
	havoc_lamps.threat_warning_bearing_rh_67_close_range		= 0;
	havoc_lamps.threat_warning_bearing_rh_90_close_range		= 0;
	havoc_lamps.threat_warning_bearing_lh_90						= 0;
	havoc_lamps.threat_warning_bearing_lh_67						= 0;
	havoc_lamps.threat_warning_bearing_lh_45						= 0;
	havoc_lamps.threat_warning_bearing_lh_22						= 0;
	havoc_lamps.threat_warning_bearing_rh_22						= 0;
	havoc_lamps.threat_warning_bearing_rh_45						= 0;
	havoc_lamps.threat_warning_bearing_rh_67						= 0;
	havoc_lamps.threat_warning_bearing_rh_90						= 0;
	havoc_lamps.threat_warning_missile_below						= 0;
	havoc_lamps.threat_warning_missile_above						= 0;
	havoc_lamps.threat_warning_missile_lh_lock					= 0;
	havoc_lamps.threat_warning_missile_rh_lock					= 0;
	havoc_lamps.threat_warning_bearing_lh_rear_close_range	= 0;
	havoc_lamps.threat_warning_bearing_rh_rear_close_range	= 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void light_threat_bearing_lamp (float theta)
{
	if (theta >= 0.0)
	{
		if (theta <= rad (22.75 + 11.25))
		{
			havoc_lamps.threat_warning_bearing_rh_22 = 1;
		}
		else if (theta <= rad (45.0 + 11.25))
		{
			havoc_lamps.threat_warning_bearing_rh_45 = 1;
		}
		else if (theta <= rad (67.5 + 11.25))
		{
			havoc_lamps.threat_warning_bearing_rh_67 = 1;
		}
		else if (theta <= rad (90.0 + 11.25))
		{
			havoc_lamps.threat_warning_bearing_rh_90 = 1;
		}
		else
		{
			havoc_lamps.threat_warning_bearing_rh_rear = 1;
		}
	}
	else
	{
		if (theta >= rad (-22.75 + -11.25))
		{
			havoc_lamps.threat_warning_bearing_lh_22 = 1;
		}
		else if (theta >= rad (-45.0 + -11.25))
		{
			havoc_lamps.threat_warning_bearing_lh_45 = 1;
		}
		else if (theta >= rad (-67.5 + -11.25))
		{
			havoc_lamps.threat_warning_bearing_lh_67 = 1;
		}
		else if (theta >= rad (-90.0 + -11.25))
		{
			havoc_lamps.threat_warning_bearing_lh_90 = 1;
		}
		else
		{
			havoc_lamps.threat_warning_bearing_lh_rear = 1;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void light_close_range_threat_bearing_lamp (float theta, int state)
{
	if (theta >= 0.0)
	{
		if (theta <= rad (22.75 + 11.25))
		{
			havoc_lamps.threat_warning_bearing_rh_22_close_range = state;
		}
		else if (theta <= rad (45.0 + 11.25))
		{
			havoc_lamps.threat_warning_bearing_rh_45_close_range = state;
		}
		else if (theta <= rad (67.5 + 11.25))
		{
			havoc_lamps.threat_warning_bearing_rh_67_close_range = state;
		}
		else if (theta <= rad (90.0 + 11.25))
		{
			havoc_lamps.threat_warning_bearing_rh_90_close_range = state;
		}
		else
		{
			havoc_lamps.threat_warning_bearing_rh_rear_close_range = state;
		}
	}
	else
	{
		if (theta >= rad (-22.75 + -11.25))
		{
			havoc_lamps.threat_warning_bearing_lh_22_close_range = state;
		}
		else if (theta >= rad (-45.0 + -11.25))
		{
			havoc_lamps.threat_warning_bearing_lh_45_close_range = state;
		}
		else if (theta >= rad (-67.5 + -11.25))
		{
			havoc_lamps.threat_warning_bearing_lh_67_close_range = state;
		}
		else if (theta >= rad (-90.0 + -11.25))
		{
			havoc_lamps.threat_warning_bearing_lh_90_close_range = state;
		}
		else
		{
			havoc_lamps.threat_warning_bearing_lh_rear_close_range = state;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
			case 14: havoc_lamps.threat_warning_close_range_15 = 1;
			case 13: havoc_lamps.threat_warning_close_range_14 = 1;
			case 12: havoc_lamps.threat_warning_close_range_13 = 1;
			case 11: havoc_lamps.threat_warning_close_range_12 = 1;
			case 10: havoc_lamps.threat_warning_close_range_11 = 1;
			case  9: havoc_lamps.threat_warning_close_range_10 = 1;
			case  8: havoc_lamps.threat_warning_close_range_9 = 1;
			case  7: havoc_lamps.threat_warning_close_range_8 = 1;
			case  6: havoc_lamps.threat_warning_close_range_7 = 1;
			case  5: havoc_lamps.threat_warning_close_range_6 = 1;
			case  4: havoc_lamps.threat_warning_close_range_5 = 1;
			case  3: havoc_lamps.threat_warning_close_range_4 = 1;
			case  2: havoc_lamps.threat_warning_close_range_3 = 1;
			case  1: havoc_lamps.threat_warning_close_range_2 = 1;
			case  0: havoc_lamps.threat_warning_close_range_1 = 1;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_threat_warning_display (void)
{
	entity
		*source,
		*threat,
		*closest_missile;

	int
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
		closest_missile_time_to_impact,
		closest_missile_theta,
		closest_missile_altitude,
		source_heading,
		length,
		cos_error;

	threat_types
		threat_type,
		closest_missile_threat_type;

	vec3d
		*source_position,
		*threat_position,
		uvec_threat_to_target;

	matrix3x3
		*attitude;

	clear_threat_warning_display_lamps ();

	if (havoc_damage.threat_warning_display)
	{
		return;
	}

	threat = get_local_entity_first_child (get_gunship_entity (), LIST_TYPE_TARGET);

	if (threat)
	{
		closest_missile = NULL;

		closest_missile_time_to_impact = 1000000.0;

		source = get_gunship_entity ();

		source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

		source_heading = get_local_entity_float_value (source, FLOAT_TYPE_HEADING);

		while (threat)
		{
			threat_type = (threat_types) get_local_entity_int_value (threat, INT_TYPE_THREAT_TYPE);

			//
			// check threat is active
			//

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
					if (!havoc_damage.radar_warning_system)
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
					threat_active = TRUE;

					break;
				}
				////////////////////////////////////////
				case THREAT_TYPE_LASER_MISSILE:
				////////////////////////////////////////
				{
					threat_active = TRUE;

					break;
				}
				////////////////////////////////////////
				case THREAT_TYPE_AIRBORNE_RADAR:
				////////////////////////////////////////
				{
					if (!havoc_damage.radar_warning_system)
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
					if (!havoc_damage.radar_warning_system)
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
					if (!havoc_damage.radar_warning_system)
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
					if (!havoc_damage.radar_warning_system)
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

			if (threat_active)
			{
				//
				// light threat type lamp
				//

				switch (threat_type)
				{
					////////////////////////////////////////
					case THREAT_TYPE_RF_MISSILE:
					////////////////////////////////////////
					{
						havoc_lamps.threat_warning_radar_type_1 = 1;

						break;
					}
					////////////////////////////////////////
					case THREAT_TYPE_IR_MISSILE:
					////////////////////////////////////////
					{
						havoc_lamps.threat_warning_radar_type_2 = 1;

						break;
					}
					////////////////////////////////////////
					case THREAT_TYPE_LASER_MISSILE:
					////////////////////////////////////////
					{
						//
						// this used to be the EWR lamp
						//

						havoc_lamps.threat_warning_radar_type_6 = 1;

						break;
					}
					////////////////////////////////////////
					case THREAT_TYPE_AIRBORNE_RADAR:
					////////////////////////////////////////
					{
						havoc_lamps.threat_warning_radar_type_3 = 1;

						break;
					}
					////////////////////////////////////////
					case THREAT_TYPE_SAM:
					////////////////////////////////////////
					{
						havoc_lamps.threat_warning_radar_type_4 = 1;

						break;
					}
					////////////////////////////////////////
					case THREAT_TYPE_AAA:
					////////////////////////////////////////
					{
						havoc_lamps.threat_warning_radar_type_5 = 1;

						break;
					}
					////////////////////////////////////////
					case THREAT_TYPE_EARLY_WARNING_RADAR:
					////////////////////////////////////////
					{
						//
						// this lamp is now used for laser missiles
						//

						break;
					}
				}

				//
				// get threat direction wrt aircraft datum
				//

				threat_position = get_local_entity_vec3d_ptr (threat, VEC3D_TYPE_POSITION);

				dx = threat_position->x - source_position->x;
				dz = threat_position->z - source_position->z;

				threat_bearing = atan2 (dx, dz);

				theta = threat_bearing - source_heading;

				if (theta > rad (180.0f))
				{
					theta -= rad (360.0f);
				}
				else if (theta < rad (-180.0f))
				{
					theta += rad (360.0f);
				}

				//
				// if missile threat then guard against 'overshot target' to prevent spurious indications
				//

				if ((threat_type == THREAT_TYPE_RF_MISSILE) || (threat_type == THREAT_TYPE_IR_MISSILE) || (threat_type == THREAT_TYPE_LASER_MISSILE))
				{
					dy = threat_position->y - source_position->y;

					threat_range = sqrt ((dx * dx) + (dy * dy) + (dz * dz));

					threat_velocity = get_local_entity_float_value (threat, FLOAT_TYPE_VELOCITY);

					time_to_impact = threat_range / max (threat_velocity, 1.0f);

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

						light_close_range_threat_bearing_lamp (theta, 1);

						if (time_to_impact < closest_missile_time_to_impact)
						{
							closest_missile = threat;

							closest_missile_threat_type = threat_type;

							closest_missile_time_to_impact = time_to_impact;

							closest_missile_theta = theta;

							closest_missile_altitude = threat_position->z;
						}
					}
				}
				else
				{
					light_threat_bearing_lamp (theta);
				}
			}

			threat = get_local_entity_child_succ (threat, LIST_TYPE_TARGET);
		}

		if (closest_missile)
		{
			closest_missile_flash_timer -= get_delta_time ();

			if (closest_missile_flash_timer <= 0.0)
			{
				closest_missile_flash_timer = CLOSEST_MISSILE_FLASH_RATE;

				closest_missile_flash_state ^= 1;
			}

			//
			// make lamps flash (overriding previous setting)
			//

			light_close_range_threat_bearing_lamp (closest_missile_theta, closest_missile_flash_state);

			switch (closest_missile_threat_type)
			{
				case THREAT_TYPE_RF_MISSILE:
				{
					havoc_lamps.threat_warning_radar_type_1 = closest_missile_flash_state;

					break;
				}
				case THREAT_TYPE_IR_MISSILE:
				{
					havoc_lamps.threat_warning_radar_type_2 = closest_missile_flash_state;

					break;
				}
				case THREAT_TYPE_LASER_MISSILE:
				{
					havoc_lamps.threat_warning_radar_type_6 = closest_missile_flash_state;

					break;
				}
			}

			light_missile_approaching_lamps (closest_missile_time_to_impact);

			havoc_lamps.threat_warning_missile_lh_lock = 1;
			havoc_lamps.threat_warning_missile_rh_lock = 1;

			if (closest_missile_altitude < source_position->z)
			{
				havoc_lamps.threat_warning_missile_below = 1;
			}
			else
			{
				havoc_lamps.threat_warning_missile_above = 1;
			}
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

	havoc_lamps.warning_1 = get_dynamics_damage_type (DYNAMICS_DAMAGE_LEFT_ENGINE_FIRE);

	havoc_lamps.warning_2 = get_dynamics_damage_type (DYNAMICS_DAMAGE_RIGHT_ENGINE_FIRE);

	havoc_lamps.warning_3 = get_current_flight_dynamics_overtorque ();

	havoc_lamps.warning_4 = get_local_entity_int_value (en, INT_TYPE_RADAR_ON);

	havoc_lamps.warning_5 = get_current_flight_dynamics_auto_pilot ();

	havoc_lamps.warning_6 = get_current_flight_dynamics_auto_hover ();

	havoc_lamps.warning_7 = get_local_entity_int_value (en, INT_TYPE_RADAR_JAMMER_ON);

	havoc_lamps.warning_8 = get_local_entity_int_value (en, INT_TYPE_INFRA_RED_JAMMER_ON);
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
	havoc_lamps.status_1 = havoc_damage.radar;

	havoc_lamps.status_2 = havoc_damage.flir;

	havoc_lamps.status_3 = havoc_damage.llltv;

	havoc_lamps.status_4 = havoc_damage.laser_range_finder;

	havoc_lamps.status_5 = havoc_damage.radar_jammer;

	havoc_lamps.status_6 = havoc_damage.infra_red_jammer;

	havoc_lamps.status_7 = havoc_damage.navigation_computer;

	havoc_lamps.status_8 = havoc_damage.communications;

	havoc_lamps.status_9 = havoc_damage.radar_warning_system;

	havoc_lamps.status_10 = havoc_damage.head_up_display;

	havoc_lamps.status_11 = havoc_damage.helmet_mounted_sight;

	havoc_lamps.status_12 = havoc_damage.tv_display;

	havoc_lamps.status_13 = havoc_damage.threat_warning_display;

	havoc_lamps.status_14 = havoc_damage.night_vision_goggles;

	havoc_lamps.status_15 = fire_extinguisher_used;

	havoc_lamps.status_16 = get_current_flight_dynamics_rotor_brake ();

	havoc_lamps.status_17 = get_current_flight_dynamics_wheel_brake ();

	havoc_lamps.status_18 = get_global_auto_counter_measures ();
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

	havoc_lamps.weapons_management_lh_outer_pylon_green			= 0;
	havoc_lamps.weapons_management_lh_inner_pylon_green			= 0;
	havoc_lamps.weapons_management_rh_inner_pylon_green			= 0;
	havoc_lamps.weapons_management_rh_outer_pylon_green			= 0;
	havoc_lamps.weapons_management_armour_piercing_cannon_green	= 0;
	havoc_lamps.weapons_management_high_explosive_cannon_green	= 0;
	havoc_lamps.weapons_management_lh_outer_pylon_red				= 0;
	havoc_lamps.weapons_management_lh_inner_pylon_red				= 0;
	havoc_lamps.weapons_management_rh_inner_pylon_red				= 0;
	havoc_lamps.weapons_management_rh_outer_pylon_red				= 0;
	havoc_lamps.weapons_management_armour_piercing_cannon_red	= 0;
	havoc_lamps.weapons_management_high_explosive_cannon_red		= 0;
	havoc_lamps.weapons_management_chaff_green						= 0;
	havoc_lamps.weapons_management_flare_green						= 0;
	havoc_lamps.weapons_management_chaff_red							= 0;
	havoc_lamps.weapons_management_flare_red							= 0;

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

	if (get_local_entity_weapon_hardpoint_info (en, HAVOC_LHS_OUTER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, &weapon_sub_type, &number, &damaged))
	{
		if (damaged)
		{
			havoc_lamps.weapons_management_lh_outer_pylon_red = 1;
		}
		else
		{
			if (number > 0)
			{
				if (weapon_sub_type == selected_weapon)
				{
					havoc_lamps.weapons_management_lh_outer_pylon_green = weapon_armed_flash_state;
				}
				else
				{
					havoc_lamps.weapons_management_lh_outer_pylon_green = 1;
				}
			}
		}
	}

	////////////////////////////////////////

	if (get_local_entity_weapon_hardpoint_info (en, HAVOC_LHS_INNER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, &weapon_sub_type, &number, &damaged))
	{
		if (damaged)
		{
			havoc_lamps.weapons_management_lh_inner_pylon_red = 1;
		}
		else
		{
			if (number > 0)
			{
				if (weapon_sub_type == selected_weapon)
				{
					havoc_lamps.weapons_management_lh_inner_pylon_green = weapon_armed_flash_state;
				}
				else
				{
					havoc_lamps.weapons_management_lh_inner_pylon_green = 1;
				}
			}
		}
	}

	////////////////////////////////////////

	if (get_local_entity_weapon_hardpoint_info (en, HAVOC_RHS_INNER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, &weapon_sub_type, &number, &damaged))
	{
		if (damaged)
		{
			havoc_lamps.weapons_management_rh_inner_pylon_red = 1;
		}
		else
		{
			if (number > 0)
			{
				if (weapon_sub_type == selected_weapon)
				{
					havoc_lamps.weapons_management_rh_inner_pylon_green = weapon_armed_flash_state;
				}
				else
				{
					havoc_lamps.weapons_management_rh_inner_pylon_green = 1;
				}
			}
		}
	}

	////////////////////////////////////////

	if (get_local_entity_weapon_hardpoint_info (en, HAVOC_RHS_OUTER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, &weapon_sub_type, &number, &damaged))
	{
		if (damaged)
		{
			havoc_lamps.weapons_management_rh_outer_pylon_red = 1;
		}
		else
		{
			if (number > 0)
			{
				if (weapon_sub_type == selected_weapon)
				{
					havoc_lamps.weapons_management_rh_outer_pylon_green = weapon_armed_flash_state;
				}
				else
				{
					havoc_lamps.weapons_management_rh_outer_pylon_green = 1;
				}
			}
		}
	}

	////////////////////////////////////////

	if (get_local_entity_weapon_hardpoint_info (en, HAVOC_CANNON_TURRET, ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND, &weapon_sub_type, &number, &damaged))
	{
		if (damaged)
		{
			havoc_lamps.weapons_management_armour_piercing_cannon_red = 1;
		}
		else
		{
			if (number > 0)
			{
				if (weapon_sub_type == selected_weapon)
				{
					havoc_lamps.weapons_management_armour_piercing_cannon_green = weapon_armed_flash_state;
				}
				else
				{
					havoc_lamps.weapons_management_armour_piercing_cannon_green = 1;
				}
			}
		}
	}

	////////////////////////////////////////

	if (get_local_entity_weapon_hardpoint_info (en, HAVOC_CANNON_TURRET, ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND, &weapon_sub_type, &number, &damaged))
	{
		if (damaged)
		{
			havoc_lamps.weapons_management_high_explosive_cannon_red = 1;
		}
		else
		{
			if (number > 0)
			{
				if (weapon_sub_type == selected_weapon)
				{
					havoc_lamps.weapons_management_high_explosive_cannon_green = weapon_armed_flash_state;
				}
				else
				{
					havoc_lamps.weapons_management_high_explosive_cannon_green = 1;
				}
			}
		}
	}

	////////////////////////////////////////

	if (get_local_entity_weapon_hardpoint_info (en, HAVOC_CHAFF_DISPENSER, ENTITY_SUB_TYPE_WEAPON_CHAFF, &weapon_sub_type, &number, &damaged))
	{
		if (damaged)
		{
			havoc_lamps.weapons_management_chaff_red = 1;
		}
		else
		{
			if (number > 0)
			{
				havoc_lamps.weapons_management_chaff_green = 1;
			}
		}
	}

	////////////////////////////////////////

	if (get_local_entity_weapon_hardpoint_info (en, HAVOC_FLARE_DISPENSER, ENTITY_SUB_TYPE_WEAPON_FLARE, &weapon_sub_type, &number, &damaged))
	{
		if (damaged)
		{
			havoc_lamps.weapons_management_flare_red = 1;
		}
		else
		{
			if (number > 0)
			{
				havoc_lamps.weapons_management_flare_green = 1;
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
		havoc_lamps.lh_engine_oil_pressure_normal = 0;
		havoc_lamps.rh_engine_oil_pressure_normal = 0;
		havoc_lamps.lh_engine_oil_pressure_low = 1;
		havoc_lamps.rh_engine_oil_pressure_low = 1;
	}
	else
	{
		havoc_lamps.lh_engine_oil_pressure_normal = 1;
		havoc_lamps.rh_engine_oil_pressure_normal = 1;
		havoc_lamps.lh_engine_oil_pressure_low = 0;
		havoc_lamps.rh_engine_oil_pressure_low = 0;
	}

	//
	// temperature
	//

	havoc_lamps.lh_engine_oil_temperature_normal = 1;
	havoc_lamps.rh_engine_oil_temperature_normal = 1;
	havoc_lamps.lh_engine_oil_temperature_high = 0;
	havoc_lamps.rh_engine_oil_temperature_high = 0;
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
// Note that all lamps are extinguished in initialise_havoc_lamps ().
//

void initialise_havoc_lamp_avionics (void)
{
	initialise_master_caution_lamp ();

	initialise_threat_warning_display ();

	initialise_weapon_status_lamps ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_havoc_lamp_avionics (void)
{
	deinitialise_master_caution_lamp ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_havoc_lamp_avionics (void)
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
