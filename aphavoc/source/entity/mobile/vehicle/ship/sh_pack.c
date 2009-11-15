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

static void pack_local_data (entity *en, pack_modes mode)
{
	ASSERT ((mode >= 0) && (mode < NUM_PACK_MODES));

	switch (mode)
	{
		////////////////////////////////////////
		case PACK_MODE_SERVER_SESSION:
		case PACK_MODE_CLIENT_SESSION:
		////////////////////////////////////////
		{
			ship_vehicle
				*raw;

			raw = (ship_vehicle *) get_local_entity_data (en);

			pack_entity_type (get_local_entity_type (en));

			pack_entity_safe_ptr (en);

			//
			// pack vehicle data
			//

			pack_vehicle_data (en, &raw->vh, mode);

			if (raw->vh.mob.velocity == 0.0)
			{

				pack_int_value (en, INT_TYPE_VALID, TRUE);
			}
			else
			{

				pack_int_value (en, INT_TYPE_VALID, FALSE);

				pack_float_value (en, FLOAT_TYPE_LOW_VELOCITY, raw->vh.mob.velocity);
			}

			//
			// pack ship data
			//

			pack_ship_meta_smoke_lists (en, mode);

			pack_mobile_local_sound_effects (en, mode);

			break;
		}
		////////////////////////////////////////
		case PACK_MODE_BROWSE_SESSION:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case PACK_MODE_UPDATE_ENTITY:
		////////////////////////////////////////
		{
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void unpack_local_data (entity *en, entity_types type, pack_modes mode)
{
	ASSERT ((mode >= 0) && (mode < NUM_PACK_MODES));

	switch (mode)
	{
		////////////////////////////////////////
		case PACK_MODE_SERVER_SESSION:
		case PACK_MODE_CLIENT_SESSION:
		////////////////////////////////////////
		{
			int
				index;

			ship_vehicle
				*raw;

			//
			// create entity
			//

			index = unpack_entity_safe_index ();

			en = get_free_entity (index);

			set_local_entity_type (en, type);

			raw = (ship_vehicle *) malloc_fast_mem (sizeof (ship_vehicle));

			set_local_entity_data (en, raw);

			memset (raw, 0, sizeof (ship_vehicle));

			//
			// unpack vehicle data (in exactly the same order as the data was packed)
			//

			unpack_vehicle_data (en, &raw->vh, mode);

			if (unpack_int_value (en, INT_TYPE_VALID))
			{

				raw->vh.mob.velocity = 0.0;
			}
			else
			{

				raw->vh.mob.velocity = unpack_float_value (en, FLOAT_TYPE_LOW_VELOCITY);
			}

			//
			// unpack ship data
			//

			//
			// radar dish rotation (ok to use a random number as this is for visual effect only)
			//

			raw->vh.radar_rotation_state = frand1 ();

			//
			// Turn off any waypoint route lines
			//
			{
				object_3d_sub_object_search_data
					search;

				search.search_object = raw->vh.inst3d;
				search.search_depth = 0;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_WAYPOINT_ROUTES;

				if ( find_object_3d_sub_object ( &search ) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND )
				{
					search.result_sub_object->visible_object = FALSE;
				}
			}

			//
			// id number
			//

			set_ship_vehicle_id_number (en);

			//
			// link into system
			//

			insert_local_entity_into_parents_child_list (en, LIST_TYPE_VIEW, get_camera_entity (), NULL);

			insert_local_entity_into_parents_child_list (en, LIST_TYPE_SECTOR, get_local_sector_entity (&raw->vh.mob.position), NULL);

			insert_local_entity_into_parents_child_list (en, LIST_TYPE_UPDATE, get_update_entity (), NULL);

			add_to_force_info (get_local_force_entity ((entity_sides) raw->vh.mob.side), en);

			//
			// attached smoke lists must be unpacked after the entity is linked into the world
			//

			unpack_ship_meta_smoke_lists (en, mode);

			unpack_mobile_local_sound_effects (en, mode);

			break;
		}
		////////////////////////////////////////
		case PACK_MODE_BROWSE_SESSION:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case PACK_MODE_UPDATE_ENTITY:
		////////////////////////////////////////
		{
			//
			// always use access functions to set the data
			//

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_ship_vehicle_pack_functions (void)
{
	fn_pack_local_entity_data[ENTITY_TYPE_SHIP_VEHICLE]	= pack_local_data;

	fn_unpack_local_entity_data[ENTITY_TYPE_SHIP_VEHICLE]	= unpack_local_data;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
