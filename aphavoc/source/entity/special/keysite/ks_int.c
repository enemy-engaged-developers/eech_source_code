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

#define DEBUG_MODULE 				0

#define KEYSITE_ICON_FLASH_RATE 	1.0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	keysite_icon_timer_flag;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_local_int_value (entity *en, int_types type, int value)
{
	keysite
		*raw;

	#if DEBUG_MODULE

	debug_log_entity_args (ENTITY_DEBUG_LOCAL, ENTITY_DEBUG_INT_VALUE, en, type, value);

	#endif

	raw = (keysite *) get_local_entity_data (en);

	switch (type)
	{
		////////////////////////////////////////
		case INT_TYPE_ALIVE:
		////////////////////////////////////////
		{
			raw->alive = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_ENTITY_SUB_TYPE:
		////////////////////////////////////////
		{
			raw->sub_type = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_IN_USE:
		////////////////////////////////////////
		{
			raw->in_use = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_KEYSITE_ID:
		////////////////////////////////////////
		{
			raw->keysite_id = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_KEYSITE_USABLE_STATE:
		////////////////////////////////////////
		{
			raw->keysite_usable_state = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_LANDING_TYPES:
		////////////////////////////////////////
		{
			raw->landing_types = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_NDB_FREQUENCY:
		////////////////////////////////////////
		{
			raw->ndb_frequency = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_OBJECT_INDEX:
		////////////////////////////////////////
		{
			raw->object_index = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_SIDE:
		////////////////////////////////////////
		{
			raw->side = value;

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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
	keysite
		*raw;

	int
		value;

	raw = (keysite *) get_local_entity_data (en);

	switch (type)
	{
		////////////////////////////////////////
		case INT_TYPE_ALIGN_WITH_TERRAIN:
		////////////////////////////////////////
		{
			value = keysite_database [raw->sub_type].align_with_terrain;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_ALIVE:
		////////////////////////////////////////
		{
			value = raw->alive;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_ENTITY_SUB_TYPE:
		////////////////////////////////////////
		{
			value = raw->sub_type;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_HIDDEN_BY_FOG_OF_WAR:
		////////////////////////////////////////
		{
			value = keysite_database [raw->sub_type].hidden_by_fog_of_war;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_IN_USE:
		////////////////////////////////////////
		{
			value = raw->in_use;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_KEYSITE_ID:
		////////////////////////////////////////
		{
			value = raw->keysite_id;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_KEYSITE_USABLE_STATE:
		////////////////////////////////////////
		{
			value = raw->keysite_usable_state;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_LANDING_TYPES:
		////////////////////////////////////////
		{
			value = raw->landing_types;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_MAP_ICON:
		////////////////////////////////////////
		{
			value = keysite_database [raw->sub_type].map_icon;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_NDB_FREQUENCY:
		////////////////////////////////////////
		{
			value = raw->ndb_frequency;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_OBJECT_INDEX:
		////////////////////////////////////////
		{
			value = raw->object_index;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_POTENTIAL_CAMPAIGN_OBJECTIVE:
		////////////////////////////////////////
		{
			value = keysite_database [raw->sub_type].campaign_objective;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_SIDE:
		////////////////////////////////////////
		{
			value = raw->side;

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

void overload_keysite_int_value_functions (void)
{
	fn_get_local_entity_int_value				[ENTITY_TYPE_KEYSITE][INT_TYPE_ALIGN_WITH_TERRAIN]							= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_KEYSITE][INT_TYPE_ALIVE]											= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_KEYSITE][INT_TYPE_ALIVE]											= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_KEYSITE][INT_TYPE_ALIVE][COMMS_MODEL_SERVER]				= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_KEYSITE][INT_TYPE_ALIVE][COMMS_MODEL_CLIENT]				= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_KEYSITE][INT_TYPE_ALIVE]											= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_KEYSITE][INT_TYPE_ENTITY_SUB_TYPE]								= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_KEYSITE][INT_TYPE_ENTITY_SUB_TYPE]								= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_KEYSITE][INT_TYPE_ENTITY_SUB_TYPE][COMMS_MODEL_SERVER]	= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_KEYSITE][INT_TYPE_ENTITY_SUB_TYPE][COMMS_MODEL_CLIENT]	= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_KEYSITE][INT_TYPE_ENTITY_SUB_TYPE]								= get_local_int_value;

	fn_get_local_entity_int_value				[ENTITY_TYPE_KEYSITE][INT_TYPE_HIDDEN_BY_FOG_OF_WAR]						= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_KEYSITE][INT_TYPE_IN_USE]											= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_KEYSITE][INT_TYPE_IN_USE]											= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_KEYSITE][INT_TYPE_IN_USE][COMMS_MODEL_SERVER]				= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_KEYSITE][INT_TYPE_IN_USE][COMMS_MODEL_CLIENT]				= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_KEYSITE][INT_TYPE_IN_USE]											= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_KEYSITE][INT_TYPE_KEYSITE_ID]									= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_KEYSITE][INT_TYPE_KEYSITE_ID]									= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_KEYSITE][INT_TYPE_KEYSITE_ID][COMMS_MODEL_SERVER]			= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_KEYSITE][INT_TYPE_KEYSITE_ID][COMMS_MODEL_CLIENT]			= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_KEYSITE][INT_TYPE_KEYSITE_ID]									= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_KEYSITE][INT_TYPE_KEYSITE_USABLE_STATE]								= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_KEYSITE][INT_TYPE_KEYSITE_USABLE_STATE]								= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_KEYSITE][INT_TYPE_KEYSITE_USABLE_STATE][COMMS_MODEL_SERVER]	= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_KEYSITE][INT_TYPE_KEYSITE_USABLE_STATE][COMMS_MODEL_CLIENT]	= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_KEYSITE][INT_TYPE_KEYSITE_USABLE_STATE]								= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_KEYSITE][INT_TYPE_LANDING_TYPES]								= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_KEYSITE][INT_TYPE_LANDING_TYPES]								= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_KEYSITE][INT_TYPE_LANDING_TYPES][COMMS_MODEL_SERVER]		= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_KEYSITE][INT_TYPE_LANDING_TYPES][COMMS_MODEL_CLIENT]		= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_KEYSITE][INT_TYPE_LANDING_TYPES]								= get_local_int_value;

	fn_get_local_entity_int_value				[ENTITY_TYPE_KEYSITE][INT_TYPE_MAP_ICON]										= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_KEYSITE][INT_TYPE_NDB_FREQUENCY]								= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_KEYSITE][INT_TYPE_NDB_FREQUENCY]								= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_KEYSITE][INT_TYPE_NDB_FREQUENCY][COMMS_MODEL_SERVER]	= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_KEYSITE][INT_TYPE_NDB_FREQUENCY][COMMS_MODEL_CLIENT]	= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_KEYSITE][INT_TYPE_NDB_FREQUENCY]								= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_KEYSITE][INT_TYPE_OBJECT_INDEX]									= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_KEYSITE][INT_TYPE_OBJECT_INDEX]									= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_KEYSITE][INT_TYPE_OBJECT_INDEX][COMMS_MODEL_SERVER]		= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_KEYSITE][INT_TYPE_OBJECT_INDEX][COMMS_MODEL_CLIENT]		= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_KEYSITE][INT_TYPE_OBJECT_INDEX]									= get_local_int_value;
	
	fn_get_local_entity_int_value				[ENTITY_TYPE_KEYSITE][INT_TYPE_POTENTIAL_CAMPAIGN_OBJECTIVE]								= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_KEYSITE][INT_TYPE_SIDE]											= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_KEYSITE][INT_TYPE_SIDE]											= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_KEYSITE][INT_TYPE_SIDE][COMMS_MODEL_SERVER]					= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_KEYSITE][INT_TYPE_SIDE][COMMS_MODEL_CLIENT]					= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_KEYSITE][INT_TYPE_SIDE]											= get_local_int_value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
