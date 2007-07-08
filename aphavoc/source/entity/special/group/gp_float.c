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
	group
		*raw;

	#if DEBUG_MODULE

	debug_log_entity_args (ENTITY_DEBUG_LOCAL, ENTITY_DEBUG_FLOAT_VALUE, en, type, value);

	#endif

	raw = get_local_entity_data (en);

	switch (type)
	{
		////////////////////////////////////////
		case FLOAT_TYPE_AMMO_SUPPLY_LEVEL:
		////////////////////////////////////////
		{
			raw->supplies.ammo_supply_level = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_ASSIST_TIMER:
		////////////////////////////////////////
		{
			raw->assist_timer = value;

			if ((value != 0.0) && (!raw->update_link.parent))
			{

				insert_local_entity_into_parents_child_list (en, LIST_TYPE_UPDATE, get_update_entity (), NULL);
			}

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_FUEL_SUPPLY_LEVEL:
		////////////////////////////////////////
		{
			raw->supplies.fuel_supply_level = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_SLEEP:
		////////////////////////////////////////
		{
			raw->sleep = value;

			if ((value != 0.0) && (!raw->update_link.parent))
			{

				insert_local_entity_into_parents_child_list (en, LIST_TYPE_UPDATE, get_update_entity (), NULL);
			}

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_LAST_SEEN_TIME:
		////////////////////////////////////////
		{
			raw->last_seen_time = value;

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
	group
		*raw;

	float
		value;

	raw = get_local_entity_data (en);

	switch (type)
	{
		////////////////////////////////////////
		case FLOAT_TYPE_AMMO_SUPPLY_LEVEL:
		////////////////////////////////////////
		{
			value = raw->supplies.ammo_supply_level;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_ASSIST_TIMER:
		////////////////////////////////////////
		{
			value = raw->assist_timer;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_FUEL_SUPPLY_LEVEL:
		////////////////////////////////////////
		{
			value = raw->supplies.fuel_supply_level;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_REARMING_TIME:
		////////////////////////////////////////
		{
			value = group_database [raw->sub_type].rearming_time;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_RECON_DISTANCE:
		////////////////////////////////////////
		{
			value = 100.0;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_SLEEP:
		////////////////////////////////////////
		{
			value = raw->sleep;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_LAST_SEEN_TIME:
		////////////////////////////////////////
		{
			value = raw->last_seen_time;

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

void overload_group_float_value_functions (void)
{
	fn_set_local_entity_raw_float_value			[ENTITY_TYPE_GROUP][FLOAT_TYPE_AMMO_SUPPLY_LEVEL]								= set_local_float_value;
	fn_set_local_entity_float_value				[ENTITY_TYPE_GROUP][FLOAT_TYPE_AMMO_SUPPLY_LEVEL]								= set_local_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_GROUP][FLOAT_TYPE_AMMO_SUPPLY_LEVEL][COMMS_MODEL_SERVER]	= set_server_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_GROUP][FLOAT_TYPE_AMMO_SUPPLY_LEVEL][COMMS_MODEL_CLIENT]	= set_client_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_GROUP][FLOAT_TYPE_AMMO_SUPPLY_LEVEL]								= get_local_float_value;

	fn_set_local_entity_raw_float_value			[ENTITY_TYPE_GROUP][FLOAT_TYPE_ASSIST_TIMER]										= set_local_float_value;
	fn_set_local_entity_float_value				[ENTITY_TYPE_GROUP][FLOAT_TYPE_ASSIST_TIMER]										= set_local_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_GROUP][FLOAT_TYPE_ASSIST_TIMER][COMMS_MODEL_SERVER]			= set_server_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_GROUP][FLOAT_TYPE_ASSIST_TIMER][COMMS_MODEL_CLIENT]			= set_client_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_GROUP][FLOAT_TYPE_ASSIST_TIMER]										= get_local_float_value;

	fn_set_local_entity_raw_float_value			[ENTITY_TYPE_GROUP][FLOAT_TYPE_FUEL_SUPPLY_LEVEL]								= set_local_float_value;
	fn_set_local_entity_float_value				[ENTITY_TYPE_GROUP][FLOAT_TYPE_FUEL_SUPPLY_LEVEL]								= set_local_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_GROUP][FLOAT_TYPE_FUEL_SUPPLY_LEVEL][COMMS_MODEL_SERVER]	= set_server_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_GROUP][FLOAT_TYPE_FUEL_SUPPLY_LEVEL][COMMS_MODEL_CLIENT]	= set_client_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_GROUP][FLOAT_TYPE_FUEL_SUPPLY_LEVEL]								= get_local_float_value;

	fn_get_local_entity_float_value				[ENTITY_TYPE_GROUP][FLOAT_TYPE_REARMING_TIME]						= get_local_float_value;

	fn_get_local_entity_float_value				[ENTITY_TYPE_GROUP][FLOAT_TYPE_RECON_DISTANCE]						= get_local_float_value;

	fn_set_local_entity_raw_float_value			[ENTITY_TYPE_GROUP][FLOAT_TYPE_SLEEP]									= set_local_float_value;
	fn_set_local_entity_float_value				[ENTITY_TYPE_GROUP][FLOAT_TYPE_SLEEP]									= set_local_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_GROUP][FLOAT_TYPE_SLEEP][COMMS_MODEL_SERVER]		= set_server_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_GROUP][FLOAT_TYPE_SLEEP][COMMS_MODEL_CLIENT]		= set_client_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_GROUP][FLOAT_TYPE_SLEEP]									= get_local_float_value;

	fn_set_local_entity_raw_float_value			[ENTITY_TYPE_GROUP][FLOAT_TYPE_LAST_SEEN_TIME]								= set_local_float_value;
	fn_set_local_entity_float_value				[ENTITY_TYPE_GROUP][FLOAT_TYPE_LAST_SEEN_TIME]								= set_local_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_GROUP][FLOAT_TYPE_LAST_SEEN_TIME][COMMS_MODEL_SERVER]	= set_server_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_GROUP][FLOAT_TYPE_LAST_SEEN_TIME][COMMS_MODEL_CLIENT]	= set_client_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_GROUP][FLOAT_TYPE_LAST_SEEN_TIME]								= get_local_float_value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
