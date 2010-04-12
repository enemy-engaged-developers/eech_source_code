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

static void update_time_of_day (entity *en)
{
	session
		*raw;

	float
		time_of_day;

	ASSERT (en);

	raw = (session *) get_local_entity_data (en);

	//
	// Time of day
	//

	raw->elapsed_time += (get_delta_time () * raw->time_of_day_acceleration);

	time_of_day = calculate_session_time_of_day (en, NULL);

	//
	// skip night-time for demos
	//

	if (raw->skip_night_time)
	{
		if (time_of_day > get_segment_time_of_day (DAY_SEGMENT_TYPE_NIGHT))
		{
			raw->elapsed_time += (ONE_DAY - time_of_day) + get_segment_time_of_day (DAY_SEGMENT_TYPE_DAWN);

			time_of_day = calculate_session_time_of_day (en, NULL);
		}
		else if (time_of_day < get_segment_time_of_day (DAY_SEGMENT_TYPE_DAWN))
		{
			raw->elapsed_time += get_segment_time_of_day (DAY_SEGMENT_TYPE_DAWN) - time_of_day;

			time_of_day = calculate_session_time_of_day (en, NULL);
		}
	}

	raw->day_segment_type = get_day_segment_type (time_of_day);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_time_of_day_resync (entity *en)
{
	session
		*raw;
		
	ASSERT (en);

	raw = (session *) get_local_entity_data (en);

	raw->time_of_day_resync += get_delta_time ();

	if (raw->time_of_day_resync > SESSION_RESYNC_FREQUENCY)
	{

		transmit_entity_comms_message (ENTITY_COMMS_UPDATE, en);

		raw->time_of_day_resync = 0.0;

		#if DEBUG_MODULE

		debug_log ("SS_UPDT : Weather at %f, %f - radius %f", raw->weather_position.x, raw->weather_position.z, raw->weather_radius);

		#endif
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define LIGHTNING_EFFECT_MINIMUM_TIMER		20.0 * ONE_SECOND
#define LIGHTNING_EFFECT_MAXIMUM_TIMER		4.0 * ONE_MINUTE

void update_lightning_effect (entity *en)
{
	session
		*raw;

	int
		lightning_flag = FALSE;

	float
		new_time;

	ASSERT (en);

	raw = (session *) get_local_entity_data (en);

	if (get_comms_model () == COMMS_MODEL_SERVER)
	{
		//
		// SERVER : decrease timer, if timer reaches zero create a strike, and reset timer (c/s)
		//

		raw->lightning_timer -= get_delta_time ();

		if (raw->lightning_timer <= 0.0)
		{
			lightning_flag = TRUE;

			new_time = LIGHTNING_EFFECT_MINIMUM_TIMER + ((LIGHTNING_EFFECT_MAXIMUM_TIMER - LIGHTNING_EFFECT_MINIMUM_TIMER) * frand1 ());

			#if DEBUG_MODULES

			debug_log ("SS_UPDT : Set lightning timer %.2f", new_time);

			#endif

			set_client_server_entity_float_value (en, FLOAT_TYPE_LIGHTNING_TIMER, new_time);
		}
	}
	else
	{
		//
		// CLIENT : decrease timer only if non-zero and create strike if zero reached ( new timer will be set by server )
		//

		if (raw->lightning_timer > 0.0)
		{
			raw->lightning_timer -= get_delta_time ();

			if (raw->lightning_timer <= 0.0)
			{
				lightning_flag = TRUE;

				raw->lightning_timer = 0.0;
			}
		}
	}

	if (lightning_flag)
	{
		//
		// create lightning
		//

		env_3d
			*current_3d_env;

		current_3d_env = get_3d_active_environment ();

		if (current_3d_env == main_3d_env)
		{
			current_3d_env = NULL;
		}
		else
		{
			set_3d_active_environment (main_3d_env);
		}
		
		add_3d_lightning_strike (LIGHTNING_TYPE_CLOUD_BURST, 0.3f, raw->weather_position.x, raw->weather_position.z);

		add_3d_lightning_strike (LIGHTNING_TYPE_FORKED_1, 0.3f, raw->weather_position.x, raw->weather_position.z);

		if (current_3d_env)
		{
			set_3d_active_environment (current_3d_env);
		}

		if (get_comms_model () == COMMS_MODEL_SERVER)
		{
			sound_sample_indices
				sound_effect_index;

			//
			// lightning sound effect
			//

			sound_effect_index = SOUND_SAMPLE_INDEX_AMBIENT_LIGHTNING;

			create_client_server_sound_effect_entity
			(
				get_local_sector_entity (&(raw->weather_position)),
				ENTITY_SIDE_NEUTRAL,
				ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,
				SOUND_CHANNEL_SOUND_EFFECT,
				SOUND_LOCALITY_ALL,
				&raw->weather_position,						// position
				1.0,												// amplification
				0.85+(0.3* frand1 ()), //pitch
				TRUE,												// valid sound effect
				FALSE,											// looping
				1,													// sample count
				&sound_effect_index							// sample index list
			);

			//
			// thunder sound effect
			//

			sound_effect_index = SOUND_SAMPLE_INDEX_AMBIENT_THUNDER;

			create_client_server_sound_effect_entity
			(
				get_local_sector_entity (&(raw->weather_position)),
				ENTITY_SIDE_NEUTRAL,
				ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,
				SOUND_CHANNEL_SOUND_EFFECT,
				SOUND_LOCALITY_ALL,
				&raw->weather_position,						// position
				1.0,												// amplification
				0.85+(0.3* frand1 ()), //pitch
				TRUE,												// valid sound effect
				FALSE,											// looping
				1,													// sample count
				&sound_effect_index							// sample index list
			);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_transitional_weather (entity *en)
{
	vec3d
		*camera_pos;

	session
		*raw;

	ASSERT (en);

	raw = (session *) get_local_entity_data (en);

	if (raw->local_weather_model)
	{
		//
		// local weather model
		//

		if (raw->weather_radius == 0.0)
		{
			//
			// weather is fine all across the map
			//
	
			raw->weather_mode = WEATHERMODE_DRY;
			raw->target_weather_mode = WEATHERMODE_DRY;
	
			raw->weather_mode_transitional_status = 1.0;
		}
		else
		{
			//
			// there is some bad weather somewhere on the map
			//

			if (in_cockpit)
			{
				camera_pos = get_local_entity_vec3d_ptr (get_gunship_entity (), VEC3D_TYPE_POSITION);
			}
			else
			{
				camera_pos = get_local_entity_vec3d_ptr (get_camera_entity (), VEC3D_TYPE_POSITION);
			}

			get_session_weather_at_point (camera_pos, &(raw->weather_mode), &(raw->target_weather_mode), &(raw->weather_mode_transitional_status));

			//
			// lightning effect
			//

			update_lightning_effect (en);
		}
		
		//
		// move weather
		//
	
		raw->weather_position.x += (raw->weather_velocity.x * get_delta_time ());
		raw->weather_position.z += (raw->weather_velocity.z * get_delta_time ());
	
		//
		// "bounce" weather of sides of map
		//
	
		if (raw->weather_position.x < MIN_MAP_X)
		{
			raw->weather_position.x = MIN_MAP_X;
	
			raw->weather_velocity.x = -raw->weather_velocity.x;
		}
		else if (raw->weather_position.x >= MAX_MAP_X)
		{
			raw->weather_position.x = MAX_MAP_X - 1.0;
	
			raw->weather_velocity.x = -raw->weather_velocity.x;
		}
	
		if (raw->weather_position.z < MIN_MAP_Z)
		{
			raw->weather_position.z = MIN_MAP_Z;
	
			raw->weather_velocity.z = -raw->weather_velocity.z;
		}
		else if (raw->weather_position.z >= MAX_MAP_Z)
		{
			raw->weather_position.z = MAX_MAP_Z - 1.0;
	
			raw->weather_velocity.z = -raw->weather_velocity.z;
		}

		//
		// expand / contract weather radius
		//

		if (raw->weather_increasing)
		{
			raw->weather_radius += (WEATHER_EXPANSION_RATE * get_delta_time ());

			if (raw->weather_radius > MAX_WEATHER_RADIUS)
			{
				raw->weather_increasing = FALSE;

				raw->weather_radius = MAX_WEATHER_RADIUS;
			}
		}
		else
		{
			raw->weather_radius -= (WEATHER_EXPANSION_RATE * get_delta_time ());

			if (raw->weather_radius < MIN_WEATHER_RADIUS)
			{
				raw->weather_increasing = TRUE;

				raw->weather_radius = MIN_WEATHER_RADIUS;
			}
		}
	}
	else
	{
		//
		// global weather model
		//
			
		if (raw->weather_mode != raw->target_weather_mode)
		{
			raw->weather_mode_transitional_status += get_delta_time () / raw->weather_mode_transitional_period;
	
			if (raw->weather_mode_transitional_status >= 1.0)
			{
				raw->weather_mode = raw->target_weather_mode;
	
				raw->weather_mode_transitional_status = 0.0;
			}
		}
		else
		{
			raw->weather_mode_transitional_status = 0.0;
		}
	}

	//
	// move wind
	//
	
	raw->wind_effect_position.x += (raw->wind_effect_velocity.x * get_delta_time ());
	raw->wind_effect_position.z += (raw->wind_effect_velocity.z * get_delta_time ());

	//
	// "bounce" wind_effect of sides of map
	//

	if (raw->wind_effect_position.x < MIN_MAP_X)
	{
		raw->wind_effect_position.x = MIN_MAP_X;

		raw->wind_effect_velocity.x = -raw->wind_effect_velocity.x;
	}
	else if (raw->wind_effect_position.x >= MAX_MAP_X)
	{
		raw->wind_effect_position.x = MAX_MAP_X - 1.0;

		raw->wind_effect_velocity.x = -raw->wind_effect_velocity.x;
	}

	if (raw->wind_effect_position.z < MIN_MAP_Z)
	{
		raw->wind_effect_position.z = MIN_MAP_Z;

		raw->wind_effect_velocity.z = -raw->wind_effect_velocity.z;
	}
	else if (raw->wind_effect_position.z >= MAX_MAP_Z)
	{
		raw->wind_effect_position.z = MAX_MAP_Z - 1.0;

		raw->wind_effect_velocity.z = -raw->wind_effect_velocity.z;
	}

	//
	// increase gusting value
	//

	raw->wind_gusting_value += (get_delta_time () * WIND_GUST_FREQUENCY);

	while (raw->wind_gusting_value >= 1.0)
	{
		raw->wind_gusting_value -= 1.0;
	}

	//
	// expand / contract wind_effect radius
	//

	if (raw->wind_increasing)
	{
		raw->wind_effect_radius += (WIND_EXPANSION_RATE * get_delta_time ());

		if (raw->wind_effect_radius > MAX_WIND_RADIUS)
		{
			raw->wind_increasing = FALSE;

			raw->wind_effect_radius = MAX_WIND_RADIUS;
		}
	}
	else
	{
		raw->wind_effect_radius -= (WIND_EXPANSION_RATE * get_delta_time ());

		if (raw->wind_effect_radius < MIN_WIND_RADIUS)
		{
			raw->wind_increasing = TRUE;

			raw->wind_effect_radius = MIN_WIND_RADIUS;
		}
	}

	//
	// set wind direction
	//

	raw->wind_direction_vector.x = raw->wind_effect_position.x - MID_MAP_X;
	raw->wind_direction_vector.y = 0.0;
	raw->wind_direction_vector.z = raw->wind_effect_position.z - MID_MAP_Z;

	normalise_any_3d_vector (&raw->wind_direction_vector);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define SESSION_RAIN_SOUND_EFFECT_ZERO_VOLUME_ALTITUDE		180.0
#define SESSION_TERRAIN_SOUND_EFFECT_ZERO_VOLUME_ALTITUDE	280.0

void update_session_sound_effects (entity *en)
{
	session
		*raw;

	entity
		*spec;

	vec3d
		*camera_pos;

	weathermodes
		current_weather_mode,
		target_weather_mode;

	float
		alt,
		trans,
		value,
		light_wind_sound_level,
		heavy_wind_sound_level,
		rain_sound_levels [WEATHERMODE_LAST];

	ASSERT (en);

	raw = (session *) get_local_entity_data (en);

	if (in_cockpit)
	{
		camera_pos = get_local_entity_vec3d_ptr (get_gunship_entity (), VEC3D_TYPE_POSITION);

		alt = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_RADAR_ALTITUDE);
	}
	else
	{
		camera_pos = get_local_entity_vec3d_ptr (get_camera_entity (), VEC3D_TYPE_POSITION);

		alt = get_local_entity_float_value (get_camera_entity (), FLOAT_TYPE_RADAR_ALTITUDE);
	}

	//
	// rain
	//

	memset (rain_sound_levels, 0, sizeof (float) * WEATHERMODE_LAST);

	if (camera_pos->y < get_cloud_3d_base_height ())
	{
		if ((!in_cockpit) && (alt >= SESSION_RAIN_SOUND_EFFECT_ZERO_VOLUME_ALTITUDE))
		{
			//
			// rain should only make a sound when it hits either the cockpit, or the ground
			//
		}
		else
		{
			get_session_weather_at_point (camera_pos, &current_weather_mode, &target_weather_mode, &trans);

			if (target_weather_mode == current_weather_mode)
			{
				rain_sound_levels [target_weather_mode] = 1.0;
				rain_sound_levels [current_weather_mode] = 1.0;
			}
			else
			{
				rain_sound_levels [target_weather_mode] = trans;
				rain_sound_levels [current_weather_mode] = (1.0 - trans);
			}

			if (!in_cockpit)
			{
				rain_sound_levels [target_weather_mode] *= (1.0 - (alt / SESSION_RAIN_SOUND_EFFECT_ZERO_VOLUME_ALTITUDE));
				rain_sound_levels [current_weather_mode] *= (1.0 - (alt / SESSION_RAIN_SOUND_EFFECT_ZERO_VOLUME_ALTITUDE));
			}
		}
	}
	
	//
	// wind
	//
	{
		float
			r,
			wind_speed;
	
		wind_speed = get_session_wind_velocity_at_point (camera_pos, NULL);

		if (wind_speed <= raw->wind_minimum_speed)
		{
			r = 0.0;
		}
		else if (wind_speed >= raw->wind_maximum_speed)
		{
			r = 1.0;
		}
		else
		{
			r = (wind_speed - raw->wind_minimum_speed) / (raw->wind_maximum_speed - raw->wind_minimum_speed);
		}
		
		ASSERT ((r >= 0.0) && (r <= 1.0));

		if (r == 0.0)
		{
			light_wind_sound_level = 0.0;

			heavy_wind_sound_level = 0.0;
		}
		else if (r < 0.5)
		{
			light_wind_sound_level = r * 2.0;

			heavy_wind_sound_level = 0.0;
		}
		else
		{
			light_wind_sound_level = 1.0 - ((r - 0.5) * 2.0);

			heavy_wind_sound_level = (r - 0.5) * 2.0;
		}
	}

	//
	// terrain
	//
	{
		float
			xpos,
			zpos;

		xpos = bound (camera_pos->x, MIN_MAP_X, MAX_MAP_X);
		zpos = bound (camera_pos->z, MIN_MAP_Z, MAX_MAP_Z);
		
		get_terrain_3d_types_in_sector (xpos, zpos);
	}

	//
	// set new values
	//

	spec = get_local_entity_first_child (en, LIST_TYPE_SPECIAL_EFFECT);

	while (spec)
	{
		switch (get_local_entity_int_value (spec, INT_TYPE_ENTITY_SUB_TYPE))
		{
			case ENTITY_SUB_TYPE_EFFECT_SOUND_AMBIENT_LIGHT_RAIN:
			{
				set_local_entity_float_value (spec, FLOAT_TYPE_AMPLIFICATION, rain_sound_levels [WEATHERMODE_LIGHT_RAIN]);

				break;
			}
			case ENTITY_SUB_TYPE_EFFECT_SOUND_AMBIENT_HEAVY_RAIN:
			{
				set_local_entity_float_value (spec, FLOAT_TYPE_AMPLIFICATION, rain_sound_levels [WEATHERMODE_HEAVY_RAIN]);

				break;
			}
			case ENTITY_SUB_TYPE_EFFECT_SOUND_AMBIENT_LIGHT_WIND:
			{
				set_local_entity_float_value (spec, FLOAT_TYPE_AMPLIFICATION, light_wind_sound_level);

				break;
			}
			case ENTITY_SUB_TYPE_EFFECT_SOUND_AMBIENT_HEAVY_WIND:
			{
				set_local_entity_float_value (spec, FLOAT_TYPE_AMPLIFICATION, heavy_wind_sound_level);

				break;
			}
			case ENTITY_SUB_TYPE_EFFECT_SOUND_AMBIENT_SEA:
			{
				if (alt >= SESSION_TERRAIN_SOUND_EFFECT_ZERO_VOLUME_ALTITUDE)
				{
					value = 0.0;
				}
				else
				{
					value = get_local_entity_float_value (spec, FLOAT_TYPE_AMPLIFICATION);
	

					if (terrain_types_in_sector [TERRAIN_TYPE_SEA])
					{
						value += (0.5 * get_delta_time ());
					}
					else
					{
						value -= (0.5 * get_delta_time ());
					}

					value = bound (value, 0.0, 0.3f);

					value *= bound(1.0 - (alt / SESSION_TERRAIN_SOUND_EFFECT_ZERO_VOLUME_ALTITUDE), 0.0, 1.0);

					if (in_cockpit)
					{
						value *= 0.75;
					}
				}

				set_local_entity_float_value (spec, FLOAT_TYPE_AMPLIFICATION, value);

				break;
			}
			case ENTITY_SUB_TYPE_EFFECT_SOUND_AMBIENT_JUNGLE:
			{
				if (alt >= SESSION_TERRAIN_SOUND_EFFECT_ZERO_VOLUME_ALTITUDE)
				{
					value = 0.0;
				}
				else
				{
					value = get_local_entity_float_value (spec, FLOAT_TYPE_AMPLIFICATION);


					if (terrain_types_in_sector [TERRAIN_TYPE_FOREST_TOP])
					{
						value += (0.5 * get_delta_time ());
					}
					else
					{
						value -= (0.5 * get_delta_time ());
					}

					value = bound (value, 0.0, 0.3f);
					value *= bound(1.0 - (alt / SESSION_TERRAIN_SOUND_EFFECT_ZERO_VOLUME_ALTITUDE), 0.0, 1.0);

					if (in_cockpit)
					{
						value *= 0.75;
					}
				}

				set_local_entity_float_value (spec, FLOAT_TYPE_AMPLIFICATION, value);

				break;
	        }
			case ENTITY_SUB_TYPE_EFFECT_SOUND_AMB1:
			{
				if (alt >= SESSION_TERRAIN_SOUND_EFFECT_ZERO_VOLUME_ALTITUDE)
				{
					value = 0.0;
				}
				else
				{
					value = get_local_entity_float_value (spec, FLOAT_TYPE_AMPLIFICATION);
	
					if (terrain_types_in_sector [TERRAIN_TYPE_RIVER])
					{
						value += (0.5 * get_delta_time ());
					}
					else
					{
						value -= (0.5 * get_delta_time ());
					}
	
					value = bound (value, 0.0, 0.3f);

					value *= bound(1.0 - (alt / SESSION_TERRAIN_SOUND_EFFECT_ZERO_VOLUME_ALTITUDE), 0.0, 1.0);

					if (in_cockpit)
					{
						value *= 0.75;
					}
				}

				set_local_entity_float_value (spec, FLOAT_TYPE_AMPLIFICATION, value);

				break;
            }
			case ENTITY_SUB_TYPE_EFFECT_SOUND_AMB2:
			{
				if (alt >= SESSION_TERRAIN_SOUND_EFFECT_ZERO_VOLUME_ALTITUDE)
				{
					value = 0.0;
				}
				else
				{
					value = get_local_entity_float_value (spec, FLOAT_TYPE_AMPLIFICATION);
	
					if (terrain_types_in_sector [TERRAIN_TYPE_RESERVOIR])
					{
						value += (0.5 * get_delta_time ());
					}
					else
					{
						value -= (0.5 * get_delta_time ());
					}
	
					value = bound (value, 0.0, 0.3f);

					value *= bound(1.0 - (alt / SESSION_TERRAIN_SOUND_EFFECT_ZERO_VOLUME_ALTITUDE), 0.0, 1.0);

					if (in_cockpit)
					{
						value *= 0.75;
					}
				}

				set_local_entity_float_value (spec, FLOAT_TYPE_AMPLIFICATION, value);

				break;
            }
			case ENTITY_SUB_TYPE_EFFECT_SOUND_AMB3:
			{
				if (alt >= SESSION_TERRAIN_SOUND_EFFECT_ZERO_VOLUME_ALTITUDE)
				{
					value = 0.0;
				}
				else
				{
					value = get_local_entity_float_value (spec, FLOAT_TYPE_AMPLIFICATION);
	
					if (terrain_types_in_sector [TERRAIN_TYPE_ALTERED_LAND1])
					{
						value += (0.5 * get_delta_time ());
					}
					else
					{
						value -= (0.5 * get_delta_time ());
					}
	
					value = bound (value, 0.0, 0.3f);

					value *= bound(1.0 - (alt / SESSION_TERRAIN_SOUND_EFFECT_ZERO_VOLUME_ALTITUDE), 0.0, 1.0);

					if (in_cockpit)
					{
						value *= 0.75;
					}
				}

				set_local_entity_float_value (spec, FLOAT_TYPE_AMPLIFICATION, value);

				break;
            }
			case ENTITY_SUB_TYPE_EFFECT_SOUND_AMB4:
			{
				if (alt >= SESSION_TERRAIN_SOUND_EFFECT_ZERO_VOLUME_ALTITUDE)
				{
					value = 0.0;
				}
				else
				{
					value = get_local_entity_float_value (spec, FLOAT_TYPE_AMPLIFICATION);
	
					if (terrain_types_in_sector [TERRAIN_TYPE_ALTERED_LAND2])
					{
						value += (0.5 * get_delta_time ());
					}
					else
					{
						value -= (0.5 * get_delta_time ());
					}
	
					value = bound (value, 0.0, 0.3f);

					value *= bound(1.0 - (alt / SESSION_TERRAIN_SOUND_EFFECT_ZERO_VOLUME_ALTITUDE), 0.0, 1.0);

					if (in_cockpit)
					{
						value *= 0.75;
					}
				}

				set_local_entity_float_value (spec, FLOAT_TYPE_AMPLIFICATION, value);

				break;
			}
		}

		spec = get_local_entity_child_succ (spec, LIST_TYPE_SPECIAL_EFFECT);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_server (entity *en)
{
	update_time_of_day (en);

	update_time_of_day_resync (en);

	update_transitional_weather (en);

	update_session_sound_effects (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_client (entity *en)
{
	update_time_of_day (en);

	update_transitional_weather (en);

	update_session_sound_effects (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_session_update_functions (void)
{
	fn_update_client_server_entity[ENTITY_TYPE_SESSION][COMMS_MODEL_SERVER]	= update_server;

	fn_update_client_server_entity[ENTITY_TYPE_SESSION][COMMS_MODEL_CLIENT]	= update_client;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
