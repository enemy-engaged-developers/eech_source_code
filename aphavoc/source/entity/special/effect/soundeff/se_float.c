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

static void set_local_float_value (entity *en, float_types type, float value)
{
	sound_effect
		*raw;

	#if DEBUG_MODULE

	debug_log_entity_args (ENTITY_DEBUG_LOCAL, ENTITY_DEBUG_FLOAT_VALUE, en, type, value);

	#endif

	raw = (sound_effect *) get_local_entity_data (en);

	switch (type)
	{
		////////////////////////////////////////
		case FLOAT_TYPE_AMPLIFICATION:
		////////////////////////////////////////
		{
			raw->amplification = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_SOUNDPITCH:
		////////////////////////////////////////
		{
			raw->pitch = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_EFFECT_LIFETIME:
		////////////////////////////////////////
		{
			raw->effect_lifetime = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_VALID_EFFECT_LIFETIME:
		////////////////////////////////////////
		{
			raw->valid_effect_lifetime = value;

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
	sound_effect
		*raw;

	float
		value;

	raw = (sound_effect *) get_local_entity_data (en);

	switch (type)
	{
		////////////////////////////////////////
		case FLOAT_TYPE_AMPLIFICATION:
		////////////////////////////////////////
		{
			value = raw->amplification;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_SOUNDPITCH:
		////////////////////////////////////////
		{
			value = raw->pitch;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_EFFECT_LIFETIME:
		////////////////////////////////////////
		{
			value = raw->effect_lifetime;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_VALID_EFFECT_LIFETIME:
		////////////////////////////////////////
		{
			value = raw->valid_effect_lifetime;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_MINIMUM_SOUND_RANGE:
		////////////////////////////////////////
		{
			// possibly store in the entity ??

			ASSERT (raw->effect_index);

			value = application_sound_effects [raw->effect_index [0]].minimum_sound_range;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_REFERENCE_SOUND_RANGE:
		////////////////////////////////////////
		{
			// possibly store in the entity ??

			ASSERT (raw->effect_index);

			value = application_sound_effects [raw->effect_index [0]].reference_sound_range;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_MAXIMUM_SOUND_RANGE:
		////////////////////////////////////////
		{
			// possibly store in the entity ??

			ASSERT (raw->effect_index);

			value = application_sound_effects [raw->effect_index [0]].maximum_sound_range;

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

void overload_sound_effect_float_value_functions (void)
{
	fn_set_local_entity_raw_float_value			[ENTITY_TYPE_SOUND_EFFECT][FLOAT_TYPE_AMPLIFICATION]								= set_local_float_value;
	fn_set_local_entity_float_value				[ENTITY_TYPE_SOUND_EFFECT][FLOAT_TYPE_AMPLIFICATION]								= set_local_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SOUND_EFFECT][FLOAT_TYPE_AMPLIFICATION][COMMS_MODEL_SERVER]	= set_server_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SOUND_EFFECT][FLOAT_TYPE_AMPLIFICATION][COMMS_MODEL_CLIENT]	= set_client_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_SOUND_EFFECT][FLOAT_TYPE_AMPLIFICATION]								= get_local_float_value;

	fn_set_local_entity_raw_float_value			[ENTITY_TYPE_SOUND_EFFECT][FLOAT_TYPE_SOUNDPITCH]								= set_local_float_value;
	fn_set_local_entity_float_value				[ENTITY_TYPE_SOUND_EFFECT][FLOAT_TYPE_SOUNDPITCH]								= set_local_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SOUND_EFFECT][FLOAT_TYPE_SOUNDPITCH][COMMS_MODEL_SERVER]	= set_server_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SOUND_EFFECT][FLOAT_TYPE_SOUNDPITCH][COMMS_MODEL_CLIENT]	= set_client_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_SOUND_EFFECT][FLOAT_TYPE_SOUNDPITCH]								= get_local_float_value;

	fn_set_local_entity_raw_float_value			[ENTITY_TYPE_SOUND_EFFECT][FLOAT_TYPE_EFFECT_LIFETIME]							= set_local_float_value;
	fn_set_local_entity_float_value				[ENTITY_TYPE_SOUND_EFFECT][FLOAT_TYPE_EFFECT_LIFETIME]							= set_local_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SOUND_EFFECT][FLOAT_TYPE_EFFECT_LIFETIME][COMMS_MODEL_SERVER]	= set_server_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SOUND_EFFECT][FLOAT_TYPE_EFFECT_LIFETIME][COMMS_MODEL_CLIENT]	= set_client_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_SOUND_EFFECT][FLOAT_TYPE_EFFECT_LIFETIME]							= get_local_float_value;

	fn_set_local_entity_raw_float_value			[ENTITY_TYPE_SOUND_EFFECT][FLOAT_TYPE_VALID_EFFECT_LIFETIME]							= set_local_float_value;
	fn_set_local_entity_float_value				[ENTITY_TYPE_SOUND_EFFECT][FLOAT_TYPE_VALID_EFFECT_LIFETIME]							= set_local_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SOUND_EFFECT][FLOAT_TYPE_VALID_EFFECT_LIFETIME][COMMS_MODEL_SERVER]	= set_server_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_SOUND_EFFECT][FLOAT_TYPE_VALID_EFFECT_LIFETIME][COMMS_MODEL_CLIENT]	= set_client_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_SOUND_EFFECT][FLOAT_TYPE_VALID_EFFECT_LIFETIME]							= get_local_float_value;

	fn_get_local_entity_float_value				[ENTITY_TYPE_SOUND_EFFECT][FLOAT_TYPE_MINIMUM_SOUND_RANGE]							= get_local_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_SOUND_EFFECT][FLOAT_TYPE_REFERENCE_SOUND_RANGE]							= get_local_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_SOUND_EFFECT][FLOAT_TYPE_MAXIMUM_SOUND_RANGE]							= get_local_float_value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
