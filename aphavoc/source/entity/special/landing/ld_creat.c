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
		*task,
		*en;

	landing
		*raw;

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

		raw = malloc_fast_mem (sizeof (landing));

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

		memset (raw, 0, sizeof (landing));

		raw->position.x = MID_MAP_X;
		raw->position.y = MID_MAP_Y;
		raw->position.z = MID_MAP_Z;

		raw->free_landing_sites = 0;

		raw->total_landing_sites = 0;

		raw->reserved_landing_sites = 0;

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

		////////////////////////////////////////
		//
		// RESOLVE DEFAULT VALUES
		//
		////////////////////////////////////////
		
		raw->free_landing_sites = raw->total_landing_sites;

		switch (raw->sub_type)
		{

			case ENTITY_SUB_TYPE_LANDING_FIXED_WING:
			case ENTITY_SUB_TYPE_LANDING_FIXED_WING_TRANSPORT:
			case ENTITY_SUB_TYPE_LANDING_HELICOPTER:
			{

				//raw->route_node = get_closest_air_node (&raw->position, 10.0);

				break;
			}

			case ENTITY_SUB_TYPE_LANDING_GROUND:
			{

				raw->route_node = get_closest_road_node (&raw->position, 10.0);

				break;
			}
			case ENTITY_SUB_TYPE_LANDING_SEA:
			{

				//raw->route_node = get_closest_sea_node (&raw->position, 10.0);

				break;
			}
		}

		////////////////////////////////////////
		//
		// LINK INTO SYSTEM
		//
		////////////////////////////////////////

		if (raw->landing_site_link.parent)
		{

			insert_local_entity_into_parents_child_list (en, LIST_TYPE_LANDING_SITE, raw->landing_site_link.parent, NULL);
		}

		#if LANDING_ROUTE_CHECK

		insert_local_entity_into_parents_child_list (en, LIST_TYPE_UPDATE, get_update_entity (), NULL);

		#endif

		#if LANDING_KEYSITE_DEBUG_OUTPUT

		if (get_local_entity_int_value (raw->landing_site_link.parent, INT_TYPE_ENTITY_SUB_TYPE) != ENTITY_SUB_TYPE_KEYSITE_FARP)
		{
			debug_filtered_log ("%d x %s", raw->total_landing_sites, entity_sub_type_landing_names [raw->sub_type]);
		}

		#endif

		////////////////////////////////////////
		//
		// CREATE SUB ENTITIES
		//
		////////////////////////////////////////

		task = create_local_entity
		(
			ENTITY_TYPE_TASK,
			ENTITY_INDEX_DONT_CARE,
			ENTITY_ATTR_PARENT (LIST_TYPE_ASSIGNED_TASK, en),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_TASK_TAKEOFF_HOLDING),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_TASK_STATE, TASK_STATE_ASSIGNED),
			ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, raw->position.x, raw->position.y, raw->position.z),
			ENTITY_ATTR_END
		);

		task = create_local_entity
		(
			ENTITY_TYPE_TASK,
			ENTITY_INDEX_DONT_CARE,
			ENTITY_ATTR_PARENT (LIST_TYPE_ASSIGNED_TASK, en),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_TASK_LANDING_HOLDING),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_TASK_STATE, TASK_STATE_ASSIGNED),
			ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, raw->position.x, raw->position.y, raw->position.z),
			ENTITY_ATTR_END
		);

		task = create_local_entity
		(
			ENTITY_TYPE_TASK,
			ENTITY_INDEX_DONT_CARE,
			ENTITY_ATTR_PARENT (LIST_TYPE_ASSIGNED_TASK, en),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_TASK_TAKEOFF),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_TASK_STATE, TASK_STATE_ASSIGNED),
			ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, raw->position.x, raw->position.y, raw->position.z),
			ENTITY_ATTR_END
		);

		task = create_local_entity
		(
			ENTITY_TYPE_TASK,
			ENTITY_INDEX_DONT_CARE,
			ENTITY_ATTR_PARENT (LIST_TYPE_ASSIGNED_TASK, en),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_TASK_LANDING),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_TASK_STATE, TASK_STATE_ASSIGNED),
			ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, raw->position.x, raw->position.y, raw->position.z),
			ENTITY_ATTR_END
		);
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

void overload_landing_create_functions (void)
{
	fn_create_local_entity[ENTITY_TYPE_LANDING]										= create_local;

	fn_create_client_server_entity[ENTITY_TYPE_LANDING][COMMS_MODEL_SERVER]	= create_server;

	fn_create_client_server_entity[ENTITY_TYPE_LANDING][COMMS_MODEL_CLIENT]	= create_client;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
