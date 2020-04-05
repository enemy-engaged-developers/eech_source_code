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

static void set_local_int_value (entity *en, int_types type, int value)
{
	session
		*raw = nullptr;

	#if DEBUG_MODULE

	debug_log_entity_args (ENTITY_DEBUG_LOCAL, ENTITY_DEBUG_INT_VALUE, en, type, value);

	#endif

	raw = (session *) get_local_entity_data (en);

	switch (type)
	{
		////////////////////////////////////////
		case INT_TYPE_AUTO_ASSIGN_GUNSHIP:
		////////////////////////////////////////
		{
			raw->auto_assign_gunship = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_CAMPAIGN_MEDAL:
		////////////////////////////////////////
		{
			raw->campaign_medal = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_CAMPAIGN_REQUIRES_APACHE_HAVOC:
		////////////////////////////////////////
		{
			raw->campaign_requires_apache_havoc = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_CHEATS_ENABLED:
		////////////////////////////////////////
		{
			raw->cheats_enabled = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_INFINITE_FUEL:
		////////////////////////////////////////
		{
			raw->infinite_fuel = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_INFINITE_WEAPONS:
		////////////////////////////////////////
		{
			raw->infinite_weapons = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_INVULNERABLE_FROM_COLLISIONS:
		////////////////////////////////////////
		{
			raw->invulnerable_from_collisions = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_INVULNERABLE_FROM_WEAPONS:
		////////////////////////////////////////
		{
			raw->invulnerable_from_weapons = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_LOCAL_WEATHER_MODEL:
		////////////////////////////////////////
		{
			raw->local_weather_model = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_SESSION_COMPLETE:
		////////////////////////////////////////
		{
			raw->session_complete = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_SKIP_NIGHT_TIME:
		////////////////////////////////////////
		{
			raw->skip_night_time = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_SUPPRESS_AI_FIRE:
		////////////////////////////////////////
		{
			raw->suppress_ai_fire = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_TARGET_WEATHER_MODE:
		////////////////////////////////////////
		{
			raw->target_weather_mode = (weathermodes) value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_VERSION_NUMBER:
		////////////////////////////////////////
		{
			raw->version_number = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_WEATHER_INCREASING:
		////////////////////////////////////////
		{
			raw->weather_increasing = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_WEATHER_MODE:
		////////////////////////////////////////
		{
			raw->weather_mode = (weathermodes) value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_WIND_INCREASING:
		////////////////////////////////////////
		{
			raw->wind_increasing = value;

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal_invalid_int_type (en, type);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_remote_int_value (entity *en, int_types type, int value)
{
	#if DEBUG_MODULE

	debug_log_entity_args (ENTITY_DEBUG_REMOTE, ENTITY_DEBUG_INT_VALUE, en, type, value);

	#endif

	transmit_entity_comms_message (ENTITY_COMMS_INT_VALUE, en, type, value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_server_int_value (entity *en, int_types type, int value)
{
	validate_client_server_local_fn ();

	set_local_int_value (en, type, value);

	validate_client_server_remote_fn ();

	set_remote_int_value (en, type, value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_client_int_value (entity *en, int_types type, int value)
{
	if (get_comms_data_flow () == COMMS_DATA_FLOW_TX)
	{
		validate_client_server_remote_fn ();

		set_remote_int_value (en, type, value);
	}
	else
	{
		validate_client_server_local_fn ();

		set_local_int_value (en, type, value);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_local_int_value (entity *en, int_types type)
{
	session
		*raw = nullptr;

	int
		value;

	raw = (session *) get_local_entity_data (en);

	switch (type)
	{
		////////////////////////////////////////
		case INT_TYPE_AUTO_ASSIGN_GUNSHIP:
		////////////////////////////////////////
		{
			value = raw->auto_assign_gunship;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_CAMPAIGN_MEDAL:
		////////////////////////////////////////
		{
			value = raw->campaign_medal;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_CAMPAIGN_REQUIRES_APACHE_HAVOC:
		////////////////////////////////////////
		{
			value = raw->campaign_requires_apache_havoc;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_CHEATS_ENABLED:
		////////////////////////////////////////
		{
			if (get_connection_list_head ())
			{
				value = FALSE;
			}
			else if (command_line_cheats_on)
			{
				value = TRUE;
			}
			else
			{
				value = raw->cheats_enabled;
			}

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_DAY:
		////////////////////////////////////////
		{
			calculate_session_time_of_day (en, &value);

			value += 1;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_DAY_SEGMENT_TYPE:
		////////////////////////////////////////
		{
			value = raw->day_segment_type;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_INFINITE_FUEL:
		////////////////////////////////////////
		{
			value = (raw->infinite_fuel /*&& get_local_entity_int_value (en, INT_TYPE_CHEATS_ENABLED)*/);

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_INFINITE_WEAPONS:
		////////////////////////////////////////
		{
			value = (raw->infinite_weapons /*&& get_local_entity_int_value (en, INT_TYPE_CHEATS_ENABLED)*/);

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_INVULNERABLE_FROM_COLLISIONS:
		////////////////////////////////////////
		{
			value = (raw->invulnerable_from_collisions /*&& get_local_entity_int_value (en, INT_TYPE_CHEATS_ENABLED)*/);

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_INVULNERABLE_FROM_WEAPONS:
		////////////////////////////////////////
		{
			value = (raw->invulnerable_from_weapons /*&& get_local_entity_int_value (en, INT_TYPE_CHEATS_ENABLED)*/);

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_LOCAL_WEATHER_MODEL:
		////////////////////////////////////////
		{
			value = raw->local_weather_model;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_SESSION_COMPLETE:
		////////////////////////////////////////
		{
			value = raw->session_complete;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_SKIP_NIGHT_TIME:
		////////////////////////////////////////
		{
			value = raw->skip_night_time;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_SUPPRESS_AI_FIRE:
		////////////////////////////////////////
		{
			value = raw->suppress_ai_fire;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_TARGET_WEATHER_MODE:
		////////////////////////////////////////
		{
			value = raw->target_weather_mode;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_VERSION_NUMBER:
		////////////////////////////////////////
		{
			value = raw->version_number;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_WEATHER_INCREASING:
		////////////////////////////////////////
		{
			value = raw->weather_increasing;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_WEATHER_MODE:
		////////////////////////////////////////
		{
			value = raw->weather_mode;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_WIND_INCREASING:
		////////////////////////////////////////
		{
			value = raw->wind_increasing;

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal_invalid_int_type (en, type);

			break;
		}
	}

	return (value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_session_int_value_functions (void)
{
	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_SESSION][INT_TYPE_AUTO_ASSIGN_GUNSHIP]													= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_SESSION][INT_TYPE_AUTO_ASSIGN_GUNSHIP]													= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_SESSION][INT_TYPE_AUTO_ASSIGN_GUNSHIP][COMMS_MODEL_SERVER]						= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_SESSION][INT_TYPE_AUTO_ASSIGN_GUNSHIP][COMMS_MODEL_CLIENT]						= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_SESSION][INT_TYPE_AUTO_ASSIGN_GUNSHIP]													= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_SESSION][INT_TYPE_CAMPAIGN_MEDAL]													= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_SESSION][INT_TYPE_CAMPAIGN_MEDAL]													= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_SESSION][INT_TYPE_CAMPAIGN_MEDAL][COMMS_MODEL_SERVER]						= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_SESSION][INT_TYPE_CAMPAIGN_MEDAL][COMMS_MODEL_CLIENT]						= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_SESSION][INT_TYPE_CAMPAIGN_MEDAL]													= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_SESSION][INT_TYPE_CAMPAIGN_REQUIRES_APACHE_HAVOC]													= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_SESSION][INT_TYPE_CAMPAIGN_REQUIRES_APACHE_HAVOC]													= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_SESSION][INT_TYPE_CAMPAIGN_REQUIRES_APACHE_HAVOC][COMMS_MODEL_SERVER]						= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_SESSION][INT_TYPE_CAMPAIGN_REQUIRES_APACHE_HAVOC][COMMS_MODEL_CLIENT]						= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_SESSION][INT_TYPE_CAMPAIGN_REQUIRES_APACHE_HAVOC]													= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_SESSION][INT_TYPE_CHEATS_ENABLED]									= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_SESSION][INT_TYPE_CHEATS_ENABLED]									= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_SESSION][INT_TYPE_CHEATS_ENABLED][COMMS_MODEL_SERVER]		= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_SESSION][INT_TYPE_CHEATS_ENABLED][COMMS_MODEL_CLIENT]		= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_SESSION][INT_TYPE_CHEATS_ENABLED]									= get_local_int_value;

	fn_get_local_entity_int_value				[ENTITY_TYPE_SESSION][INT_TYPE_DAY]													= get_local_int_value;

	fn_get_local_entity_int_value				[ENTITY_TYPE_SESSION][INT_TYPE_DAY_SEGMENT_TYPE]								= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_SESSION][INT_TYPE_INFINITE_FUEL]				 					= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_SESSION][INT_TYPE_INFINITE_FUEL]					  				= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_SESSION][INT_TYPE_INFINITE_FUEL][COMMS_MODEL_SERVER]			= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_SESSION][INT_TYPE_INFINITE_FUEL][COMMS_MODEL_CLIENT]			= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_SESSION][INT_TYPE_INFINITE_FUEL]							  		= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_SESSION][INT_TYPE_INFINITE_WEAPONS]								= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_SESSION][INT_TYPE_INFINITE_WEAPONS]								= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_SESSION][INT_TYPE_INFINITE_WEAPONS][COMMS_MODEL_SERVER]		= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_SESSION][INT_TYPE_INFINITE_WEAPONS][COMMS_MODEL_CLIENT]		= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_SESSION][INT_TYPE_INFINITE_WEAPONS]								= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_SESSION][INT_TYPE_INVULNERABLE_FROM_COLLISIONS]										= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_SESSION][INT_TYPE_INVULNERABLE_FROM_COLLISIONS]										= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_SESSION][INT_TYPE_INVULNERABLE_FROM_COLLISIONS][COMMS_MODEL_SERVER]			= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_SESSION][INT_TYPE_INVULNERABLE_FROM_COLLISIONS][COMMS_MODEL_CLIENT]			= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_SESSION][INT_TYPE_INVULNERABLE_FROM_COLLISIONS]										= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_SESSION][INT_TYPE_INVULNERABLE_FROM_WEAPONS]										= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_SESSION][INT_TYPE_INVULNERABLE_FROM_WEAPONS]										= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_SESSION][INT_TYPE_INVULNERABLE_FROM_WEAPONS][COMMS_MODEL_SERVER]			= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_SESSION][INT_TYPE_INVULNERABLE_FROM_WEAPONS][COMMS_MODEL_CLIENT]			= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_SESSION][INT_TYPE_INVULNERABLE_FROM_WEAPONS]										= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_SESSION][INT_TYPE_LOCAL_WEATHER_MODEL]							= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_SESSION][INT_TYPE_LOCAL_WEATHER_MODEL]							= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_SESSION][INT_TYPE_LOCAL_WEATHER_MODEL][COMMS_MODEL_SERVER]	= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_SESSION][INT_TYPE_LOCAL_WEATHER_MODEL][COMMS_MODEL_CLIENT]	= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_SESSION][INT_TYPE_LOCAL_WEATHER_MODEL]							= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_SESSION][INT_TYPE_SESSION_COMPLETE]								= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_SESSION][INT_TYPE_SESSION_COMPLETE]								= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_SESSION][INT_TYPE_SESSION_COMPLETE][COMMS_MODEL_SERVER]		= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_SESSION][INT_TYPE_SESSION_COMPLETE][COMMS_MODEL_CLIENT]		= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_SESSION][INT_TYPE_SESSION_COMPLETE]								= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_SESSION][INT_TYPE_SKIP_NIGHT_TIME]									= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_SESSION][INT_TYPE_SKIP_NIGHT_TIME]									= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_SESSION][INT_TYPE_SKIP_NIGHT_TIME][COMMS_MODEL_SERVER]		= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_SESSION][INT_TYPE_SKIP_NIGHT_TIME][COMMS_MODEL_CLIENT]		= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_SESSION][INT_TYPE_SKIP_NIGHT_TIME]									= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_SESSION][INT_TYPE_SUPPRESS_AI_FIRE]								= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_SESSION][INT_TYPE_SUPPRESS_AI_FIRE]								= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_SESSION][INT_TYPE_SUPPRESS_AI_FIRE][COMMS_MODEL_SERVER]		= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_SESSION][INT_TYPE_SUPPRESS_AI_FIRE][COMMS_MODEL_CLIENT]		= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_SESSION][INT_TYPE_SUPPRESS_AI_FIRE]								= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_SESSION][INT_TYPE_TARGET_WEATHER_MODE]							= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_SESSION][INT_TYPE_TARGET_WEATHER_MODE]							= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_SESSION][INT_TYPE_TARGET_WEATHER_MODE][COMMS_MODEL_SERVER]	= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_SESSION][INT_TYPE_TARGET_WEATHER_MODE][COMMS_MODEL_CLIENT]	= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_SESSION][INT_TYPE_TARGET_WEATHER_MODE]							= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_SESSION][INT_TYPE_VERSION_NUMBER]									= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_SESSION][INT_TYPE_VERSION_NUMBER]									= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_SESSION][INT_TYPE_VERSION_NUMBER][COMMS_MODEL_SERVER]		= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_SESSION][INT_TYPE_VERSION_NUMBER][COMMS_MODEL_CLIENT]		= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_SESSION][INT_TYPE_VERSION_NUMBER]									= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_SESSION][INT_TYPE_WEATHER_INCREASING]								= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_SESSION][INT_TYPE_WEATHER_INCREASING]								= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_SESSION][INT_TYPE_WEATHER_INCREASING][COMMS_MODEL_SERVER]	= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_SESSION][INT_TYPE_WEATHER_INCREASING][COMMS_MODEL_CLIENT]	= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_SESSION][INT_TYPE_WEATHER_INCREASING]								= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_SESSION][INT_TYPE_WEATHER_MODE]										= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_SESSION][INT_TYPE_WEATHER_MODE]										= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_SESSION][INT_TYPE_WEATHER_MODE][COMMS_MODEL_SERVER]			= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_SESSION][INT_TYPE_WEATHER_MODE][COMMS_MODEL_CLIENT]			= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_SESSION][INT_TYPE_WEATHER_MODE]										= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_SESSION][INT_TYPE_WIND_INCREASING]									= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_SESSION][INT_TYPE_WIND_INCREASING]									= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_SESSION][INT_TYPE_WIND_INCREASING][COMMS_MODEL_SERVER]		= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_SESSION][INT_TYPE_WIND_INCREASING][COMMS_MODEL_CLIENT]		= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_SESSION][INT_TYPE_WIND_INCREASING]									= get_local_int_value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
