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

static entity *create_local (entity_types type, int index, char *pargs)
{
	entity
		*en;

	smoke_list
		*raw;

	int
		loop,
		number_of_slots;

	#if DEBUG_MODULE

	debug_log ("SMOKE_LIST: create");

	#endif

	////////////////////////////////////////
  	//
  	// VALIDATE
  	//
	////////////////////////////////////////

	validate_local_create_entity_index (index);

	#if DEBUG_MODULE

	debug_log_entity_args (ENTITY_DEBUG_LOCAL, ENTITY_DEBUG_CREATE, NULL, type, index);

	#endif

	en = get_free_entity (index);

	if (en)
	{
		////////////////////////////////////////
   	//
   	// MALLOC ENTITY DATA
   	//
		////////////////////////////////////////

		set_local_entity_type (en, type);

		raw = malloc_fast_mem (sizeof (smoke_list));

		set_local_entity_data (en, raw);

		////////////////////////////////////////
   	//
   	// INITIALISE ALL ENTITY DATA TO 'WORKING' DEFAULT VALUES
		//
		// DO NOT USE ACCESS FUNCTIONS
		//
		// DO NOT USE RANDOM VALUES
		//
		////////////////////////////////////////

		memset (raw, 0, sizeof (smoke_list));

		//
		// fixed
		//

		raw->eff.position.x = MID_MAP_X;
		raw->eff.position.y = MID_MAP_Y;
		raw->eff.position.z = MID_MAP_Z;

		//
		// smoke list
		//

		raw->relative_position.x = 0.0;
		raw->relative_position.y = 0.0;
		raw->relative_position.z = 0.0;

		raw->width_adjustment = 0.0;

		////////////////////////////////////////
		//
		// OVERWRITE DEFAULT VALUES WITH GIVEN ATTRIBUTES
		//
		////////////////////////////////////////

		set_local_entity_attributes (en, pargs);

		////////////////////////////////////////
		//
		// CHECK MANDATORY ATTRIBUTES HAVE BEEN GIVEN
		//
		////////////////////////////////////////

		ASSERT (entity_sub_type_effect_valid (raw->eff.sub_type));

		ASSERT (raw->frequency);

		ASSERT (raw->smoke_lifetime);

		////////////////////////////////////////
		//
		// RESOLVE DEFAULT VALUES
		//
		////////////////////////////////////////

		////////////////////////////////////////
		//
		// BUILD COMPONENTS
		//
		////////////////////////////////////////

		number_of_slots = raw->smoke_lifetime / raw->frequency;

		ASSERT (number_of_slots > 0);

		ASSERT (number_of_slots < 65536);

		//
		// Build array of smoke positions, and set all to ( -1, -1, -1 ), and mark invalid
		//

		raw->position = malloc_fast_mem (sizeof (vec3d) * number_of_slots);

		raw->valid = malloc_fast_mem (sizeof (unsigned char) * number_of_slots);

		for ( loop = number_of_slots - 1 ; loop >= 0 ; loop -- )
		{
			raw->valid[ loop ] = FALSE;

			raw->position[ loop ].x = -1.0;
			raw->position[ loop ].y = -1.0;
			raw->position[ loop ].z = -1.0;
		}

		raw->motion_vector = malloc_fast_mem (sizeof (vec3d) * number_of_slots);

		memset( raw->motion_vector, 0, sizeof( vec3d ) * number_of_slots );

		raw->start_rotation = malloc_fast_mem (sizeof (float) * number_of_slots);

		raw->head = 0;

		raw->tail = 0;

		////////////////////////////////////////
		//
		// LINK INTO SYSTEM
		//
		////////////////////////////////////////

		if (raw->eff.special_effect_link.parent)
		{
			insert_local_entity_into_parents_child_list (en, LIST_TYPE_SPECIAL_EFFECT, raw->eff.special_effect_link.parent, NULL);
		}

		if (raw->generator_lifetime > 0.0)
		{
			insert_local_entity_into_parents_child_list (en, LIST_TYPE_UPDATE, get_update_entity(), raw->eff.update_link.child_pred);
		}

		insert_local_entity_into_parents_child_list (en, LIST_TYPE_SECTOR, get_local_sector_entity (&raw->eff.position), NULL);
	}

	return (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *create_remote (entity_types type, int index, char *pargs)
{
	validate_remote_create_entity_index (index);

	#if DEBUG_MODULE

	debug_log_entity_args (ENTITY_DEBUG_REMOTE, ENTITY_DEBUG_CREATE, NULL, type, index);

	#endif

	transmit_entity_comms_message (ENTITY_COMMS_CREATE, NULL, type, index, pargs);

	return (NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *create_server (entity_types type, int index, char *pargs)
{
	entity
		*en;

	validate_client_server_local_fn ();

	en = create_local (type, index, pargs);

	if (en)
	{
		validate_client_server_remote_fn ();

		create_remote (type, get_local_entity_index (en), pargs);
	}

	return (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *create_client (entity_types type, int index, char *pargs)
{
	entity
		*en;

	if (get_comms_data_flow () == COMMS_DATA_FLOW_TX)
	{
		validate_client_server_remote_fn ();

		en = create_remote (type, index, pargs);
	}
	else
	{
		validate_client_server_local_fn ();

		en = create_local (type, index, pargs);
	}

	return (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_smoke_list_create_functions (void)
{
	fn_create_local_entity[ENTITY_TYPE_SMOKE_LIST]		  								= create_local;

	fn_create_client_server_entity[ENTITY_TYPE_SMOKE_LIST][COMMS_MODEL_SERVER]	= create_server;

	fn_create_client_server_entity[ENTITY_TYPE_SMOKE_LIST][COMMS_MODEL_CLIENT]	= create_client;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
