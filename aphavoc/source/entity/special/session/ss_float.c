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

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_local_float_value (entity *en, float_types type, float value)
{
	session
		*raw;

	#if DEBUG_MODULE

	debug_log_entity_args (ENTITY_DEBUG_LOCAL, ENTITY_DEBUG_FLOAT_VALUE, en, type, value);

	#endif

	raw = get_local_entity_data (en);

	switch (type)
	{
		////////////////////////////////////////
		case FLOAT_TYPE_ELAPSED_TIME:
		////////////////////////////////////////
		{
			raw->elapsed_time = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_FOG_OF_WAR_MAXIMUM_VALUE:
		////////////////////////////////////////
		{
			raw->fog_of_war_maximum_value = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_LIGHTNING_TIMER:
		////////////////////////////////////////
		{
			raw->lightning_timer = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_POPULATION_X_MIN:
		////////////////////////////////////////
		{
			raw->population_x_min = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_POPULATION_X_MAX:
		////////////////////////////////////////
		{
			raw->population_x_max = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_POPULATION_Z_MIN:
		////////////////////////////////////////
		{
			raw->population_z_min = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_POPULATION_Z_MAX:
		////////////////////////////////////////
		{
			raw->population_z_max = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_START_TIME:
		////////////////////////////////////////
		{
			raw->start_time = value;

			raw->day_segment_type = get_day_segment_type (value);

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_TIME_OF_DAY_ACCELERATION:
		////////////////////////////////////////
		{
			raw->time_of_day_acceleration = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_WEATHER_MODE_TRANSITIONAL_PERIOD:
		////////////////////////////////////////
		{
			raw->weather_mode_transitional_period = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_WEATHER_MODE_TRANSITIONAL_STATUS:
		////////////////////////////////////////
		{
			raw->weather_mode_transitional_status = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_WEATHER_RADIUS:
		////////////////////////////////////////
		{
			raw->weather_radius = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_WIND_EFFECT_RADIUS:
		////////////////////////////////////////
		{
			raw->wind_effect_radius = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_WIND_GUSTING_VALUE:
		////////////////////////////////////////
		{
			raw->wind_gusting_value = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_WIND_MAXIMUM_SPEED:
		////////////////////////////////////////
		{
			raw->wind_maximum_speed = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_WIND_MINIMUM_SPEED:
		////////////////////////////////////////
		{
			raw->wind_minimum_speed = value;

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal_invalid_float_type (en, type);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_remote_float_value (entity *en, float_types type, float value)
{
	#if DEBUG_MODULE

	debug_log_entity_args (ENTITY_DEBUG_REMOTE, ENTITY_DEBUG_FLOAT_VALUE, en, type, value);

	#endif

	transmit_entity_comms_message (ENTITY_COMMS_FLOAT_VALUE, en, type, value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_server_float_value (entity *en, float_types type, float value)
{
	validate_client_server_local_fn ();

	set_local_float_value (en, type, value);

	validate_client_server_remote_fn ();

	set_remote_float_value (en, type, value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_client_float_value (entity *en, float_types type, float value)
{
	if (get_comms_data_flow () == COMMS_DATA_FLOW_TX)
	{
		validate_client_server_remote_fn ();

		set_remote_float_value (en, type, value);
	}
	else
	{
		validate_client_server_local_fn ();

		set_local_float_value (en, type, value);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float get_local_float_value (entity *en, float_types type)
{
	session
		*raw;

	float
		value;

	raw = get_local_entity_data (en);

	switch (type)
	{
		////////////////////////////////////////
		case FLOAT_TYPE_ELAPSED_TIME:
		////////////////////////////////////////
		{
			value = raw->elapsed_time;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_FOG_OF_WAR_MAXIMUM_VALUE:
		////////////////////////////////////////
		{
			value = raw->fog_of_war_maximum_value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_LIGHTNING_TIMER:
		////////////////////////////////////////
		{
			value = raw->lightning_timer;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_POPULATION_X_MIN:
		////////////////////////////////////////
		{
			value = raw->population_x_min;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_POPULATION_X_MAX:
		////////////////////////////////////////
		{
			value = raw->population_x_max;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_POPULATION_Z_MIN:
		////////////////////////////////////////
		{
			value = raw->population_z_min;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_POPULATION_Z_MAX:
		////////////////////////////////////////
		{
			value = raw->population_z_max;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_START_TIME:
		////////////////////////////////////////
		{
			value = raw->start_time;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_TIME_OF_DAY:
		////////////////////////////////////////
		{
			value = calculate_session_time_of_day (en, NULL);

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_TIME_OF_DAY_ACCELERATION:
		////////////////////////////////////////
		{
			value = raw->time_of_day_acceleration;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_WEATHER_MODE_TRANSITIONAL_PERIOD:
		////////////////////////////////////////
		{
			value = raw->weather_mode_transitional_period;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_WEATHER_MODE_TRANSITIONAL_STATUS:
		////////////////////////////////////////
		{
			value = raw->weather_mode_transitional_status;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_WEATHER_RADIUS:
		////////////////////////////////////////
		{
			value = raw->weather_radius;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_WIND_EFFECT_RADIUS:
		////////////////////////////////////////
		{
			value = raw->wind_effect_radius;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_WIND_GUSTING_VALUE:
		////////////////////////////////////////
		{
			value = raw->wind_gusting_value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_WIND_MAXIMUM_SPEED:
		////////////////////////////////////////
		{
			value = raw->wind_maximum_speed;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_WIND_MINIMUM_SPEED:
		////////////////////////////////////////
		{
			value = raw->wind_minimum_speed;

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal_invalid_float_type (en, type);

			break;
		}
	}

	return (value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_session_float_value_functions (void)
{
	fn_set_local_entity_raw_float_value			[ENTITY_TYPE_SESSION][FLOAT_TYPE_ELAPSED_TIME]							= set_local_float_value;
	fn_set_local_entity_float_value				[ENTITY_TYPE_SESSION][FLOAT_TYPE_ELAPSED_TIME]						  	= set_local_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SESSION][FLOAT_TYPE_ELAPSED_TIME][COMMS_MODEL_SERVER]	= set_server_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SESSION][FLOAT_TYPE_ELAPSED_TIME][COMMS_MODEL_CLIENT]	= set_client_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_SESSION][FLOAT_TYPE_ELAPSED_TIME]							= get_local_float_value;

	fn_set_local_entity_raw_float_value			[ENTITY_TYPE_SESSION][FLOAT_TYPE_FOG_OF_WAR_MAXIMUM_VALUE]							= set_local_float_value;
	fn_set_local_entity_float_value				[ENTITY_TYPE_SESSION][FLOAT_TYPE_FOG_OF_WAR_MAXIMUM_VALUE]						  	= set_local_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SESSION][FLOAT_TYPE_FOG_OF_WAR_MAXIMUM_VALUE][COMMS_MODEL_SERVER]	= set_server_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SESSION][FLOAT_TYPE_FOG_OF_WAR_MAXIMUM_VALUE][COMMS_MODEL_CLIENT]	= set_client_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_SESSION][FLOAT_TYPE_FOG_OF_WAR_MAXIMUM_VALUE]							= get_local_float_value;

	fn_set_local_entity_raw_float_value			[ENTITY_TYPE_SESSION][FLOAT_TYPE_LIGHTNING_TIMER]								= set_local_float_value;
	fn_set_local_entity_float_value				[ENTITY_TYPE_SESSION][FLOAT_TYPE_LIGHTNING_TIMER]							  	= set_local_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SESSION][FLOAT_TYPE_LIGHTNING_TIMER][COMMS_MODEL_SERVER]	= set_server_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SESSION][FLOAT_TYPE_LIGHTNING_TIMER][COMMS_MODEL_CLIENT]	= set_client_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_SESSION][FLOAT_TYPE_LIGHTNING_TIMER]								= get_local_float_value;

	fn_set_local_entity_raw_float_value			[ENTITY_TYPE_SESSION][FLOAT_TYPE_POPULATION_X_MIN]								= set_local_float_value;
	fn_set_local_entity_float_value				[ENTITY_TYPE_SESSION][FLOAT_TYPE_POPULATION_X_MIN]							  	= set_local_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SESSION][FLOAT_TYPE_POPULATION_X_MIN][COMMS_MODEL_SERVER]	= set_server_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SESSION][FLOAT_TYPE_POPULATION_X_MIN][COMMS_MODEL_CLIENT]	= set_client_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_SESSION][FLOAT_TYPE_POPULATION_X_MIN]								= get_local_float_value;

	fn_set_local_entity_raw_float_value			[ENTITY_TYPE_SESSION][FLOAT_TYPE_POPULATION_X_MAX]								= set_local_float_value;
	fn_set_local_entity_float_value				[ENTITY_TYPE_SESSION][FLOAT_TYPE_POPULATION_X_MAX]							  	= set_local_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SESSION][FLOAT_TYPE_POPULATION_X_MAX][COMMS_MODEL_SERVER]	= set_server_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SESSION][FLOAT_TYPE_POPULATION_X_MAX][COMMS_MODEL_CLIENT]	= set_client_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_SESSION][FLOAT_TYPE_POPULATION_X_MAX]								= get_local_float_value;

	fn_set_local_entity_raw_float_value			[ENTITY_TYPE_SESSION][FLOAT_TYPE_POPULATION_Z_MIN]								= set_local_float_value;
	fn_set_local_entity_float_value				[ENTITY_TYPE_SESSION][FLOAT_TYPE_POPULATION_Z_MIN]							  	= set_local_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SESSION][FLOAT_TYPE_POPULATION_Z_MIN][COMMS_MODEL_SERVER]	= set_server_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SESSION][FLOAT_TYPE_POPULATION_Z_MIN][COMMS_MODEL_CLIENT]	= set_client_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_SESSION][FLOAT_TYPE_POPULATION_Z_MIN]								= get_local_float_value;

	fn_set_local_entity_raw_float_value			[ENTITY_TYPE_SESSION][FLOAT_TYPE_POPULATION_Z_MAX]								= set_local_float_value;
	fn_set_local_entity_float_value				[ENTITY_TYPE_SESSION][FLOAT_TYPE_POPULATION_Z_MAX]							  	= set_local_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SESSION][FLOAT_TYPE_POPULATION_Z_MAX][COMMS_MODEL_SERVER]	= set_server_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SESSION][FLOAT_TYPE_POPULATION_Z_MAX][COMMS_MODEL_CLIENT]	= set_client_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_SESSION][FLOAT_TYPE_POPULATION_Z_MAX]								= get_local_float_value;

	fn_set_local_entity_raw_float_value			[ENTITY_TYPE_SESSION][FLOAT_TYPE_START_TIME]								= set_local_float_value;
	fn_set_local_entity_float_value				[ENTITY_TYPE_SESSION][FLOAT_TYPE_START_TIME]							  	= set_local_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SESSION][FLOAT_TYPE_START_TIME][COMMS_MODEL_SERVER]	= set_server_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SESSION][FLOAT_TYPE_START_TIME][COMMS_MODEL_CLIENT]	= set_client_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_SESSION][FLOAT_TYPE_START_TIME]								= get_local_float_value;

	fn_get_local_entity_float_value				[ENTITY_TYPE_SESSION][FLOAT_TYPE_TIME_OF_DAY]							= get_local_float_value;

	fn_set_local_entity_raw_float_value			[ENTITY_TYPE_SESSION][FLOAT_TYPE_TIME_OF_DAY_ACCELERATION]						  		= set_local_float_value;
	fn_set_local_entity_float_value				[ENTITY_TYPE_SESSION][FLOAT_TYPE_TIME_OF_DAY_ACCELERATION]						 	 	= set_local_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SESSION][FLOAT_TYPE_TIME_OF_DAY_ACCELERATION][COMMS_MODEL_SERVER]	= set_server_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SESSION][FLOAT_TYPE_TIME_OF_DAY_ACCELERATION][COMMS_MODEL_CLIENT]	= set_client_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_SESSION][FLOAT_TYPE_TIME_OF_DAY_ACCELERATION]								= get_local_float_value;

	fn_set_local_entity_raw_float_value			[ENTITY_TYPE_SESSION][FLOAT_TYPE_WEATHER_MODE_TRANSITIONAL_PERIOD]							= set_local_float_value;
	fn_set_local_entity_float_value				[ENTITY_TYPE_SESSION][FLOAT_TYPE_WEATHER_MODE_TRANSITIONAL_PERIOD]							= set_local_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SESSION][FLOAT_TYPE_WEATHER_MODE_TRANSITIONAL_PERIOD][COMMS_MODEL_SERVER]	= set_server_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SESSION][FLOAT_TYPE_WEATHER_MODE_TRANSITIONAL_PERIOD][COMMS_MODEL_CLIENT]	= set_client_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_SESSION][FLOAT_TYPE_WEATHER_MODE_TRANSITIONAL_PERIOD]							= get_local_float_value;

	fn_set_local_entity_raw_float_value			[ENTITY_TYPE_SESSION][FLOAT_TYPE_WEATHER_MODE_TRANSITIONAL_STATUS]							= set_local_float_value;
	fn_set_local_entity_float_value				[ENTITY_TYPE_SESSION][FLOAT_TYPE_WEATHER_MODE_TRANSITIONAL_STATUS]							= set_local_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SESSION][FLOAT_TYPE_WEATHER_MODE_TRANSITIONAL_STATUS][COMMS_MODEL_SERVER]	= set_server_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SESSION][FLOAT_TYPE_WEATHER_MODE_TRANSITIONAL_STATUS][COMMS_MODEL_CLIENT]	= set_client_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_SESSION][FLOAT_TYPE_WEATHER_MODE_TRANSITIONAL_STATUS]							= get_local_float_value;

	fn_set_local_entity_raw_float_value			[ENTITY_TYPE_SESSION][FLOAT_TYPE_WEATHER_RADIUS]							= set_local_float_value;
	fn_set_local_entity_float_value				[ENTITY_TYPE_SESSION][FLOAT_TYPE_WEATHER_RADIUS]							= set_local_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SESSION][FLOAT_TYPE_WEATHER_RADIUS][COMMS_MODEL_SERVER]	= set_server_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SESSION][FLOAT_TYPE_WEATHER_RADIUS][COMMS_MODEL_CLIENT]	= set_client_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_SESSION][FLOAT_TYPE_WEATHER_RADIUS]							= get_local_float_value;

	fn_set_local_entity_raw_float_value			[ENTITY_TYPE_SESSION][FLOAT_TYPE_WIND_EFFECT_RADIUS]								= set_local_float_value;
	fn_set_local_entity_float_value				[ENTITY_TYPE_SESSION][FLOAT_TYPE_WIND_EFFECT_RADIUS]								= set_local_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SESSION][FLOAT_TYPE_WIND_EFFECT_RADIUS][COMMS_MODEL_SERVER]	= set_server_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SESSION][FLOAT_TYPE_WIND_EFFECT_RADIUS][COMMS_MODEL_CLIENT]	= set_client_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_SESSION][FLOAT_TYPE_WIND_EFFECT_RADIUS]								= get_local_float_value;

	fn_set_local_entity_raw_float_value			[ENTITY_TYPE_SESSION][FLOAT_TYPE_WIND_GUSTING_VALUE]								= set_local_float_value;
	fn_set_local_entity_float_value				[ENTITY_TYPE_SESSION][FLOAT_TYPE_WIND_GUSTING_VALUE]								= set_local_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SESSION][FLOAT_TYPE_WIND_GUSTING_VALUE][COMMS_MODEL_SERVER]	= set_server_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SESSION][FLOAT_TYPE_WIND_GUSTING_VALUE][COMMS_MODEL_CLIENT]	= set_client_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_SESSION][FLOAT_TYPE_WIND_GUSTING_VALUE]								= get_local_float_value;

	fn_set_local_entity_raw_float_value			[ENTITY_TYPE_SESSION][FLOAT_TYPE_WIND_MAXIMUM_SPEED]								= set_local_float_value;
	fn_set_local_entity_float_value				[ENTITY_TYPE_SESSION][FLOAT_TYPE_WIND_MAXIMUM_SPEED]								= set_local_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SESSION][FLOAT_TYPE_WIND_MAXIMUM_SPEED][COMMS_MODEL_SERVER]	= set_server_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SESSION][FLOAT_TYPE_WIND_MAXIMUM_SPEED][COMMS_MODEL_CLIENT]	= set_client_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_SESSION][FLOAT_TYPE_WIND_MAXIMUM_SPEED]								= get_local_float_value;

	fn_set_local_entity_raw_float_value			[ENTITY_TYPE_SESSION][FLOAT_TYPE_WIND_MINIMUM_SPEED]								= set_local_float_value;
	fn_set_local_entity_float_value				[ENTITY_TYPE_SESSION][FLOAT_TYPE_WIND_MINIMUM_SPEED]								= set_local_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SESSION][FLOAT_TYPE_WIND_MINIMUM_SPEED][COMMS_MODEL_SERVER]	= set_server_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SESSION][FLOAT_TYPE_WIND_MINIMUM_SPEED][COMMS_MODEL_CLIENT]	= set_client_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_SESSION][FLOAT_TYPE_WIND_MINIMUM_SPEED]								= get_local_float_value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
