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
	mobile
		*raw;

	#if DEBUG_MODULE

	debug_log_entity_args (ENTITY_DEBUG_LOCAL, ENTITY_DEBUG_INT_VALUE, en, type, value);

	#endif

	raw = (mobile *) get_local_entity_data (en);

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
		case INT_TYPE_KILL_NEXT_UPDATE:
		////////////////////////////////////////
		{
			raw->kill_next_update = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_OBJECT_DRAWN_ONCE_THIS_FRAME:
		////////////////////////////////////////
		{
			raw->object_drawn_once_this_frame = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_SIDE:
		////////////////////////////////////////
		{
			raw->side = value;

			break;
		}
		/*
		////////////////////////////////////////
		case INT_TYPE_TIMER:
		////////////////////////////////////////
		{
			raw->timer = value;

			break;
		}
		*/
		////////////////////////////////////////
		case INT_TYPE_TACVIEW_LOGGING:
		////////////////////////////////////////
		{
			raw->tacview_logging = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_UPDATED:
		case INT_TYPE_MOVED:
		case INT_TYPE_ROTATED:
		////////////////////////////////////////
		{
			int
				mask,
				index,
				offset;

			//
			// Coded around the entity system to avoid spinning through the update list twice
			// (which Vtune shows up as very slow). Update_entities is declared in update.c
			// You may only set the value to TRUE. It is set to FALSE by the memset in update.c
			//

			ASSERT (value == TRUE);

			index = get_local_entity_index (en) >> 5;

			offset = get_local_entity_index (en) & 0x1f;

			mask = 1 << offset;

			if (type == INT_TYPE_UPDATED)
				updated_entities [index] |= mask;
			else if (type == INT_TYPE_MOVED)
				moved_entities [index] |= mask;
			else
				rotated_entities [index] |= mask;

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
	mobile
		*raw;

	int
		value;

	raw = (mobile *) get_local_entity_data (en);

	switch (type)
	{
		////////////////////////////////////////
		case INT_TYPE_ALIVE:
		////////////////////////////////////////
		{
			value = raw->alive;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_IDENTIFY_MOBILE:
		////////////////////////////////////////
		{
			value = TRUE;

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
		case INT_TYPE_INSIDE_HANGAR:
		////////////////////////////////////////
		{
			value = FALSE;

			if (get_local_entity_int_value (en, INT_TYPE_LANDED))
			{
				entity
					*landing;

				int
					formation_position;

				landing = get_local_group_member_landing_entity_from_keysite (en);

				if (landing)
				{
					formation_position = get_local_entity_int_value (en, INT_TYPE_FORMATION_POSITION);

					if (get_local_entity_int_value (landing, INT_TYPE_INSIDE_HANGAR) & (1 << formation_position))
					{
						value = TRUE;
					}
				}
			}

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_KILL_NEXT_UPDATE:
		////////////////////////////////////////
		{
			value = raw->kill_next_update;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_OBJECT_DRAWN_ONCE_THIS_FRAME:
		////////////////////////////////////////
		{
			value = raw->object_drawn_once_this_frame;

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
		case INT_TYPE_SOUND_LIST_VALID:
		////////////////////////////////////////
		{
			value = TRUE;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_TASK_TARGET_TYPE:
		////////////////////////////////////////
		{
			value = (TASK_TARGET_TYPE_ANY | TASK_TARGET_TYPE_MOBILE);

			break;
		}
		/*
		////////////////////////////////////////
		case INT_TYPE_TIMER:
		////////////////////////////////////////
		{
			value = raw->timer;

			break;
		}
		*/
		case INT_TYPE_TACVIEW_LOGGING:
		{
			value = raw->tacview_logging;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_UPDATED:
		case INT_TYPE_MOVED:
		case INT_TYPE_ROTATED:
		////////////////////////////////////////
		{
			int
				mask,
				index,
				offset;

			index = get_local_entity_index (en) >> 5;

			offset = get_local_entity_index (en) & 0x1f;

			mask = 1 << offset;

			if (type == INT_TYPE_UPDATED)
				value = updated_entities [index] &= mask;
			else if (type == INT_TYPE_MOVED)
				value = moved_entities [index] &= mask;
			else
				value = rotated_entities [index] &= mask;

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

void overload_mobile_int_value_functions (entity_types type)
{
	fn_set_local_entity_raw_int_value		[type][INT_TYPE_ALIVE]												= set_local_int_value;
	fn_set_local_entity_int_value				[type][INT_TYPE_ALIVE]												= set_local_int_value;
	fn_set_client_server_entity_int_value	[type][INT_TYPE_ALIVE][COMMS_MODEL_SERVER]					= set_server_int_value;
	fn_set_client_server_entity_int_value	[type][INT_TYPE_ALIVE][COMMS_MODEL_CLIENT]					= set_client_int_value;
	fn_get_local_entity_int_value				[type][INT_TYPE_ALIVE]												= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_IDENTIFY_MOBILE]									= get_local_int_value;

	fn_set_local_entity_raw_int_value		[type][INT_TYPE_ENTITY_SUB_TYPE]									= set_local_int_value;
	fn_set_local_entity_int_value				[type][INT_TYPE_ENTITY_SUB_TYPE]									= set_local_int_value;
	fn_set_client_server_entity_int_value	[type][INT_TYPE_ENTITY_SUB_TYPE][COMMS_MODEL_SERVER]		= set_server_int_value;
	fn_set_client_server_entity_int_value	[type][INT_TYPE_ENTITY_SUB_TYPE][COMMS_MODEL_CLIENT]		= set_client_int_value;
	fn_get_local_entity_int_value				[type][INT_TYPE_ENTITY_SUB_TYPE]									= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_INSIDE_HANGAR]									= get_local_int_value;

	fn_set_local_entity_raw_int_value  		[type][INT_TYPE_KILL_NEXT_UPDATE]								= set_local_int_value;
	fn_set_local_entity_int_value				[type][INT_TYPE_KILL_NEXT_UPDATE]								= set_local_int_value;
	fn_set_client_server_entity_int_value	[type][INT_TYPE_KILL_NEXT_UPDATE][COMMS_MODEL_SERVER]		= set_server_int_value;
	fn_set_client_server_entity_int_value	[type][INT_TYPE_KILL_NEXT_UPDATE][COMMS_MODEL_CLIENT]		= set_client_int_value;
	fn_get_local_entity_int_value				[type][INT_TYPE_KILL_NEXT_UPDATE]								= get_local_int_value;

	fn_set_local_entity_raw_int_value  		[type][INT_TYPE_OBJECT_DRAWN_ONCE_THIS_FRAME]				= set_local_int_value;
	fn_set_local_entity_int_value				[type][INT_TYPE_OBJECT_DRAWN_ONCE_THIS_FRAME]				= set_local_int_value;
	fn_get_local_entity_int_value				[type][INT_TYPE_OBJECT_DRAWN_ONCE_THIS_FRAME]				= get_local_int_value;

	fn_set_local_entity_raw_int_value  		[type][INT_TYPE_SIDE]												= set_local_int_value;
	fn_set_local_entity_int_value				[type][INT_TYPE_SIDE]												= set_local_int_value;
	fn_set_client_server_entity_int_value	[type][INT_TYPE_SIDE][COMMS_MODEL_SERVER]						= set_server_int_value;
	fn_set_client_server_entity_int_value	[type][INT_TYPE_SIDE][COMMS_MODEL_CLIENT]						= set_client_int_value;
	fn_get_local_entity_int_value				[type][INT_TYPE_SIDE]												= get_local_int_value;

	fn_set_local_entity_raw_int_value  		[type][INT_TYPE_MOVED]												= set_local_int_value;
	fn_set_local_entity_int_value				[type][INT_TYPE_MOVED]												= set_local_int_value;
	fn_get_local_entity_int_value				[type][INT_TYPE_MOVED]												= get_local_int_value;

	fn_set_local_entity_raw_int_value  		[type][INT_TYPE_ROTATED]												= set_local_int_value;
	fn_set_local_entity_int_value				[type][INT_TYPE_ROTATED]												= set_local_int_value;
	fn_get_local_entity_int_value				[type][INT_TYPE_ROTATED]												= get_local_int_value;

	fn_set_local_entity_raw_int_value  		[type][INT_TYPE_TACVIEW_LOGGING]												= set_local_int_value;
	fn_set_local_entity_int_value				[type][INT_TYPE_TACVIEW_LOGGING]												= set_local_int_value;
	fn_get_local_entity_int_value				[type][INT_TYPE_TACVIEW_LOGGING]												= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_SOUND_LIST_VALID]								= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_TASK_TARGET_TYPE]								= get_local_int_value;
/*
	fn_set_local_entity_raw_int_value  		[type][INT_TYPE_TIMER]												= set_local_int_value;
	fn_set_local_entity_int_value				[type][INT_TYPE_TIMER]												= set_local_int_value;
	fn_set_client_server_entity_int_value	[type][INT_TYPE_TIMER][COMMS_MODEL_SERVER]					= set_server_int_value;
	fn_set_client_server_entity_int_value	[type][INT_TYPE_TIMER][COMMS_MODEL_CLIENT]					= set_client_int_value;
	fn_get_local_entity_int_value				[type][INT_TYPE_TIMER]												= get_local_int_value;
*/
	fn_set_local_entity_raw_int_value  		[type][INT_TYPE_UPDATED]											= set_local_int_value;
	fn_set_local_entity_int_value				[type][INT_TYPE_UPDATED]											= set_local_int_value;
	fn_get_local_entity_int_value				[type][INT_TYPE_UPDATED]											= get_local_int_value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
