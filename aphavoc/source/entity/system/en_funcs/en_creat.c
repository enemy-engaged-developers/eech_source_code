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
//
// Create Entity Calling Conventions
// =================================
//
// There are two ways of invoking the create entity functions, depending on the comms data flow.
//
// If transmitting then the variable argument list is on the stack, as normal.
//
// If receiving then the variable argument list is in a char buffer, passed as the first and only variable argument.
//
// The create entity functions convert both types into a char buffer for the overloaded create functions.
//
// Entity Index Rules
// ==================
//
// Logic table for local entity index:
//
// 	SERVER/TX: index == ENTITY_INDEX_DONT_CARE
// 	SERVER/RX: index == ENTITY_INDEX_DONT_CARE
// 	CLIENT/TX: ILLEGAL
// 	CLIENT/RX: index != ENTITY_INDEX_DONT_CARE
//
// Logic table for remote entity index:
//
// 	SERVER/TX: index != ENTITY_INDEX_DONT_CARE
// 	SERVER/RX: index != ENTITY_INDEX_DONT_CARE
// 	CLIENT/TX: index == ENTITY_INDEX_DONT_CARE
// 	CLIENT/RX: ILLEGAL
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *(*fn_create_local_entity[NUM_ENTITY_TYPES]) (entity_types type, int index, char *pargs);

entity *(*fn_create_client_server_entity[NUM_ENTITY_TYPES][NUM_COMMS_MODEL_TYPES]) (entity_types type, int index, char *pargs);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// force local create function to accept stack based attributes during receive - use with caution!!!
//

int
	force_local_entity_create_stack_attributes = FALSE;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *default_create_entity (entity_types type, int index, char *pargs)
{
	debug_fatal ("default_create_entity invoked: %s (index = %d)", get_entity_type_name (type), index);

	return (NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_entity_create_default_functions (void)
{
	int
		i;

	for (i = 0; i < NUM_ENTITY_TYPES; i++)
	{
		fn_create_local_entity[i]										= default_create_entity;

		fn_create_client_server_entity[i][COMMS_MODEL_SERVER]	= default_create_entity;

		fn_create_client_server_entity[i][COMMS_MODEL_CLIENT]	= default_create_entity;
	}

	force_local_entity_create_stack_attributes = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_local_entity (entity_types type, int index, ...)
{
	va_list
		pargs;

	char
		*pargs_buffer;

	entity
		*en;

	ASSERT ((type > ENTITY_TYPE_UNKNOWN) && (type < NUM_ENTITY_TYPES));

	//
	// safe guard - should never need to force stack attributes during transmit
	//

	ASSERT (!((get_comms_data_flow () == COMMS_DATA_FLOW_TX) && force_local_entity_create_stack_attributes));

	//
	// update statistics
	//

	update_create_entity_statistics (type);

	//
	// sort argument list
	//

	va_start (pargs, index);

	if ((get_comms_data_flow () == COMMS_DATA_FLOW_TX) || force_local_entity_create_stack_attributes)
	{
		#ifdef __WATCOMC__

		pargs_buffer = (char *) *pargs;

		#else

		pargs_buffer = (char *) pargs;

		#endif
	}
	else
	{
		pargs_buffer = va_arg (pargs, char *);
	}

	va_end (pargs);

	//
	// create
	//

	en = NULL;

	en = fn_create_local_entity[type] (type, index, pargs_buffer);

	if (!en)
	{

		debug_fatal ("EN_CREATE: CREATE_LOCAL_ENTITY : unable to create entity %s. Limit of %d reached", get_entity_type_name (type), number_of_entities);
	}

	#if DEBUG_MODULE
	{

		static int
			reported_segment = FALSE,
			reported_city_building = FALSE,
			reported_sector = FALSE;
	
		switch (get_local_entity_type (en))
		{

			case ENTITY_TYPE_SEGMENT:
			case ENTITY_TYPE_SECTOR:
			case ENTITY_TYPE_CITY_BUILDING:
			{
	
				if (get_local_entity_type (en) == ENTITY_TYPE_SEGMENT)
				{
		
					if (reported_segment)
					{
		
						break;
					}
		
					reported_segment = TRUE;
				}
	
				if (get_local_entity_type (en) == ENTITY_TYPE_SECTOR)
				{
		
					if (reported_sector)
					{
		
						break;
					}
		
					reported_sector = TRUE;
				}
	
				if (get_local_entity_type (en) == ENTITY_TYPE_CITY_BUILDING)
				{
		
					if (reported_city_building)
					{
		
						break;
					}
		
					reported_city_building = TRUE;
				}
			}

			default:
			{
	
				debug_log ("EN_CREAT : Created %s (index %d), sub_type %d", entity_type_names [type], get_local_entity_index (en), get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE));
	
				break;
			} 
		}
	
	}
	#endif

	return (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_client_server_entity (entity_types type, int index, ...)
{
	va_list
		pargs;

	char
		*pargs_buffer;

	entity
		*en;

	ASSERT ((type > ENTITY_TYPE_UNKNOWN) && (type < NUM_ENTITY_TYPES));

	//
	// safe guard - should never need to force stack attributes during transmit
	//

	ASSERT (!((get_comms_data_flow () == COMMS_DATA_FLOW_TX) && force_local_entity_create_stack_attributes));

	//
	// update statistics
	//

	update_create_entity_statistics (type);

	//
	// sort argument list
	//

	va_start (pargs, index);

	if ((get_comms_data_flow () == COMMS_DATA_FLOW_TX) || force_local_entity_create_stack_attributes)
	{
		#ifdef __WATCOMC__

		pargs_buffer = (char *) *pargs;

		#else

		pargs_buffer = (char *) pargs;

		#endif
	}
	else
	{
		pargs_buffer = va_arg (pargs, char *);
	}

	va_end (pargs);

	//
	// create
	//

	en = NULL;

	en = fn_create_client_server_entity[type][get_comms_model ()] (type, index, pargs_buffer);

	if ((get_comms_model () == COMMS_MODEL_SERVER) && (!en))
	{

		debug_fatal ("EN_CREATE: CREATE_CLIENT_SERVER_ENTITY : unable to create entity %s. Limit of %d reached", get_entity_type_name (type), number_of_entities);
	}

	#if DEBUG_MODULE

	switch (get_local_entity_type (en))
	{

		case ENTITY_TYPE_SEGMENT:
		case ENTITY_TYPE_SECTOR:
		case ENTITY_TYPE_CITY_BUILDING:
		{

			break;
		}
		default:
		{

			debug_log ("EN_CREAT : CS Created %s (index %d), sub_type %d", entity_type_names [type], get_local_entity_index (en), get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE));

			break;
		} 
	}

	#endif

	return (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_local_only_entities (pack_modes pack_mode)
{
	comms_model_types
		temp_comms_model;

	comms_data_flow_types
		temp_comms_data_flow;

	//
	// store comms model and data flow
	//

	temp_comms_model = get_comms_model ();

	temp_comms_data_flow = get_comms_data_flow ();

	//
	// set comms model and data flow to SERVER/TX
	//

	set_comms_model (COMMS_MODEL_SERVER);

	set_comms_data_flow (COMMS_DATA_FLOW_TX);

	disable_entity_comms_messages ();

	//
	// create local only entities
	//

	create_local_sector_entities ();

	create_local_pylon_entities (pack_mode);

	create_local_bridge_entities (pack_mode);

	create_local_update_entity ();

	// create camera entity now so that it is forced to the end of the update list (updated last)

	create_local_camera_entity ();

	//
	// restore comms model and data flow
	//

	set_comms_model (temp_comms_model);

	set_comms_data_flow (temp_comms_data_flow);

	enable_entity_comms_messages ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
