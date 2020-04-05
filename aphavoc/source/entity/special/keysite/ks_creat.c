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
#include "ai/highlevl/imaps.h"

#include "entity/tacview/tacview.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *create_local (entity_types type, int index, char *pargs)
{

	char
		 name [STRING_TYPE_KEYSITE_NAME_MAX_LENGTH];

	entity
		*group = nullptr,
		*force = nullptr,
		*sector = nullptr,
		*en = nullptr;

	keysite
		*raw = nullptr;

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

		raw = (keysite *) malloc_fast_mem (sizeof (keysite));

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

		memset (raw, 0, sizeof (keysite));

		sprintf (name, "KEYSITE %d", (int) en % 100);

		strncpy (raw->keysite_name, name, STRING_TYPE_KEYSITE_NAME_MAX_LENGTH);

		//
		// fixed
		//

		raw->position.x = MID_MAP_X;
		raw->position.y = MID_MAP_Y;
		raw->position.z = MID_MAP_Z;

		raw->alive = TRUE;

		raw->keysite_usable_state = KEYSITE_STATE_USABLE;

		raw->ndb_frequency = 0;

		raw->in_use = FALSE;
		raw->object_index = OBJECT_3D_INVALID_OBJECT_INDEX;

		raw->side = ENTITY_SIDE_NEUTRAL;

		raw->supplies.ammo_supply_level = 0.0;

		raw->supplies.fuel_supply_level = 0.0;

		raw->assign_timer = frand1 () * KEYSITE_TASK_ASSIGN_TIMER;		// SERVER ONLY - OK TO USE RANDOM

		raw->sleep = frand1 () * KEYSITE_UPDATE_SLEEP_TIMER;				// SERVER ONLY - OK TO USE RANDOM

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

		ASSERT (raw->side != ENTITY_SIDE_NEUTRAL);

		ASSERT (entity_sub_type_keysite_valid (raw->sub_type));

		ASSERT (keysite_database [raw->sub_type].minimum_efficiency < 1.0);

		// the following is currently required for the campaign to progress properly...
		ASSERT (keysite_database [raw->sub_type].repairable == keysite_database [raw->sub_type].troop_insertion_target);

		////////////////////////////////////////
		//
		// RESOLVE DEFAULT VALUES
		//
		////////////////////////////////////////

		update_keysite_cargo (en, raw->supplies.ammo_supply_level, ENTITY_SUB_TYPE_CARGO_AMMO, CARGO_AMMO_SIZE);

		update_keysite_cargo (en, raw->supplies.fuel_supply_level, ENTITY_SUB_TYPE_CARGO_FUEL, CARGO_FUEL_SIZE);

		if (raw->sub_type == ENTITY_SUB_TYPE_KEYSITE_AIRBASE || raw->sub_type == ENTITY_SUB_TYPE_KEYSITE_ANCHORAGE || 
				raw->sub_type == ENTITY_SUB_TYPE_KEYSITE_FARP || raw->sub_type == ENTITY_SUB_TYPE_KEYSITE_RADIO_TRANSMITTER)
			raw->ndb_frequency = 100 + rand16() % 1900;

		////////////////////////////////////////
		//
		// BUILD COMPONENTS
		//
		////////////////////////////////////////

		////////////////////////////////////////
		//
		// LINK INTO SYSTEM
		//
		////////////////////////////////////////

		force = get_local_entity_parent (en, LIST_TYPE_KEYSITE_FORCE);

		debug_assert (get_local_entity_type (force) == ENTITY_TYPE_FORCE);

		ASSERT (force);

		sector = get_local_sector_entity (&raw->position);

		ASSERT (sector);

		insert_local_entity_into_parents_child_list (en, LIST_TYPE_KEYSITE_FORCE, force, NULL);

		insert_local_entity_into_parents_child_list (en, LIST_TYPE_SECTOR, sector, NULL);

		insert_local_entity_into_parents_child_list (en, LIST_TYPE_UPDATE, get_update_entity (), NULL);

		set_local_entity_int_value (sector, INT_TYPE_KEYSITE_COUNT, get_local_entity_int_value (sector, INT_TYPE_KEYSITE_COUNT) + 1);

		if (raw->in_use)
		{
			update_imap_sector_side (en, TRUE);

			update_imap_importance_level (en, TRUE);

			update_keysite_distance_to_friendly_base (en, (entity_sides) raw->side);
		}

		////////////////////////////////////////
		//
		//	CREATE SUB ENTITIES
		//
		////////////////////////////////////////

		// for site buildings

		group = create_local_entity
		(
			ENTITY_TYPE_GROUP,
			ENTITY_INDEX_DONT_CARE,
			ENTITY_ATTR_PARENT (LIST_TYPE_BUILDING_GROUP, en),
			ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, raw->position.x, raw->position.y, raw->position.z),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_GROUP_BUILDINGS),
			ENTITY_ATTR_END
		);

		#if DEBUG_MODULE
		{
			int
				sx,
				sz;

			get_x_sector (sx, raw->position.x);
			get_z_sector (sz, raw->position.z);

			debug_log ("KS_CREAT: Side %s creating keysite %s (type %d) index %d at %f, %f (%d, %d)", entity_side_short_names [raw->side], raw->keysite_name, raw->sub_type, get_local_entity_index (en), raw->position.x, raw->position.z, sx, sz);
		}
		#endif
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
		*en = nullptr;

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
		*en = nullptr;

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

void overload_keysite_create_functions (void)
{
	fn_create_local_entity[ENTITY_TYPE_KEYSITE]		  								= create_local;

	fn_create_client_server_entity[ENTITY_TYPE_KEYSITE][COMMS_MODEL_SERVER]	= create_server;

	fn_create_client_server_entity[ENTITY_TYPE_KEYSITE][COMMS_MODEL_CLIENT]	= create_client;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
