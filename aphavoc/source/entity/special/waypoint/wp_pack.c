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

static void pack_local_data (entity *en, pack_modes mode)
{
	
	ASSERT ((mode >= 0) && (mode < NUM_PACK_MODES));
	
	switch (mode)
	{
		////////////////////////////////////////
		case PACK_MODE_SERVER_SESSION:
		////////////////////////////////////////
		{
			
			vec3d
				position;
			
			waypoint
				*raw;
			
			raw = get_local_entity_data (en);
			
			ASSERT (raw->waypoint_link.parent);
				
			ASSERT (get_local_entity_type (raw->waypoint_link.parent) == ENTITY_TYPE_TASK);
				
			//
			// do send task's waypoint list (not landing ones)
			//
					
			switch (get_local_entity_int_value (raw->waypoint_link.parent, INT_TYPE_ENTITY_SUB_TYPE))
			{
						
				case ENTITY_SUB_TYPE_TASK_LANDING:
				case ENTITY_SUB_TYPE_TASK_LANDING_HOLDING:
				case ENTITY_SUB_TYPE_TASK_TAKEOFF:
				case ENTITY_SUB_TYPE_TASK_TAKEOFF_HOLDING:
				{
							
					return;
				}
			}
			
			pack_entity_type (get_local_entity_type (en));
			
			pack_entity_safe_ptr (en);
			
			//
			// pack data (in exactly the same order as the data is unpacked)
			//
			
			pack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, raw->sub_type);
			
			/////////////////////////////////////////////////////////////////

			pack_list_link (en, LIST_TYPE_WAYPOINT, &raw->waypoint_link);

			/////////////////////////////////////////////////////////////////
			
			/////////////////////////////////////////////////////////////////
			if (raw->current_waypoint_root.first_child)
			{
				
				pack_int_value (en, INT_TYPE_VALID, TRUE);
				
				pack_list_root (en, LIST_TYPE_CURRENT_WAYPOINT, &raw->current_waypoint_root);
			}
			else
			{
				
				pack_int_value (en, INT_TYPE_VALID, FALSE);
			}
			/////////////////////////////////////////////////////////////////
			
			/////////////////////////////////////////////////////////////////
			if (raw->task_dependent_link.parent)
			{
				
				pack_int_value (en, INT_TYPE_VALID, TRUE);
				
				pack_list_link (en, LIST_TYPE_TASK_DEPENDENT, &raw->task_dependent_link);
			}
			else
			{
				
				pack_int_value (en, INT_TYPE_VALID, FALSE);
			}
			/////////////////////////////////////////////////////////////////
			
			pack_float_value (en, FLOAT_TYPE_ALTITUDE, raw->altitude);
			
			pack_float_value (en, FLOAT_TYPE_HEADING, raw->heading);
			
			pack_int_value (en, INT_TYPE_POSITION_TYPE, raw->position_type);
			
			pack_int_value (en, INT_TYPE_ROUTE_NODE, raw->route_node);
			
			pack_char_value (en, CHAR_TYPE_TAG, (char) raw->tag);
			
			pack_int_value (en, INT_TYPE_WAYPOINT_FORMATION, raw->waypoint_formation);
			
			switch (raw->position_type)
			{
				
				case POSITION_TYPE_RELATIVE:
				{
					
					debug_fatal ("WP_PACK: internal waypoint with relative position");
					
					break;
				}
				
				case POSITION_TYPE_ABSOLUTE:
				case POSITION_TYPE_VIRTUAL:
				{
					
					position = raw->position;
					
					pack_vec3d (en, VEC3D_TYPE_POSITION, &position);
					
					pack_entity_safe_ptr (raw->position_entity);
					
					break;
				}
			}
			
			break;
		}
		////////////////////////////////////////
		case PACK_MODE_CLIENT_SESSION:
		////////////////////////////////////////
		{
			
			vec3d
				position;
			
			waypoint
				*raw;
			
			raw = get_local_entity_data (en);
			
			ASSERT (raw->waypoint_link.parent);
				
			ASSERT (get_local_entity_type (raw->waypoint_link.parent) == ENTITY_TYPE_TASK);
				
			//
			// do send task's waypoint list (not landing ones)
			//
					
			switch (get_local_entity_int_value (raw->waypoint_link.parent, INT_TYPE_ENTITY_SUB_TYPE))
			{
						
				case ENTITY_SUB_TYPE_TASK_LANDING:
				case ENTITY_SUB_TYPE_TASK_LANDING_HOLDING:
				case ENTITY_SUB_TYPE_TASK_TAKEOFF:
				case ENTITY_SUB_TYPE_TASK_TAKEOFF_HOLDING:
				{
							
					return;
				}
			}
			
			pack_entity_type (get_local_entity_type (en));
			
			pack_entity_safe_ptr (en);
			
			//
			// pack data (in exactly the same order as the data is unpacked)
			//
			
			pack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, raw->sub_type);

			/////////////////////////////////////////////////////////////////
			
			pack_list_link (en, LIST_TYPE_WAYPOINT, &raw->waypoint_link);
			
			pack_float_value (en, FLOAT_TYPE_ALTITUDE, raw->altitude);
			
			pack_int_value (en, INT_TYPE_POSITION_TYPE, raw->position_type);
			
			pack_int_value (en, INT_TYPE_ROUTE_NODE, raw->route_node);
			
			pack_char_value (en, CHAR_TYPE_TAG, (char) raw->tag);
			
			pack_int_value (en, INT_TYPE_WAYPOINT_FORMATION, raw->waypoint_formation);
			
			switch (raw->position_type)
			{
				
				case POSITION_TYPE_RELATIVE:
				{
					
					debug_fatal ("WP_PACK: internal waypoint with relative position");
					
					break;
				}
				
				case POSITION_TYPE_ABSOLUTE:
				case POSITION_TYPE_VIRTUAL:
				{
					
					position = raw->position;
					
					pack_vec3d (en, VEC3D_TYPE_POSITION, &position);
					
					pack_entity_safe_ptr (raw->position_entity);
					
					break;
				}
			}
			
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
		////////////////////////////////////////
		{
			int
			index;
			
			waypoint
			*raw;
			
			//
			// create entity
			//
			
			index = unpack_entity_safe_index ();
			
			en = get_free_entity (index);
			
			set_local_entity_type (en, type);
			
			raw = malloc_fast_mem (sizeof (waypoint));
			
			set_local_entity_data (en, raw);
			
			memset (raw, 0, sizeof (waypoint));
			
			//
			// unpack data (in exactly the same order as the data was packed)
			//
			
			raw->sub_type = unpack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);

			unpack_list_link (en, LIST_TYPE_WAYPOINT, &raw->waypoint_link);
			
			/////////////////////////////////////////////////////////////////
			if (unpack_int_value (en, INT_TYPE_VALID))
			{
				
				unpack_list_root (en, LIST_TYPE_CURRENT_WAYPOINT, &raw->current_waypoint_root);
			}
			/////////////////////////////////////////////////////////////////
			
			/////////////////////////////////////////////////////////////////
			if (unpack_int_value (en, INT_TYPE_VALID))
			{
				
				unpack_list_link (en, LIST_TYPE_TASK_DEPENDENT, &raw->task_dependent_link);
			}
			/////////////////////////////////////////////////////////////////
			
			raw->altitude = unpack_float_value (en, FLOAT_TYPE_ALTITUDE);
			
			raw->heading = unpack_float_value (en, FLOAT_TYPE_HEADING);
			
			raw->position_type = unpack_int_value (en, INT_TYPE_POSITION_TYPE);
			
			raw->route_node = unpack_int_value (en, INT_TYPE_ROUTE_NODE);
			
			raw->tag = unpack_char_value (en, CHAR_TYPE_TAG);
			
			raw->waypoint_formation = unpack_int_value (en, INT_TYPE_WAYPOINT_FORMATION);
			
			//
			//
			//
			
			switch (raw->position_type)
			{
				
				case POSITION_TYPE_RELATIVE:
				{
					
					debug_fatal ("WP_PACK: internal waypoint with relative position");
					
					break;
				}
				
				case POSITION_TYPE_ABSOLUTE:
				case POSITION_TYPE_VIRTUAL:
				{
					
					unpack_vec3d (en, VEC3D_TYPE_POSITION, &raw->position);
					
					index = unpack_entity_safe_index ();
					
					raw->position_entity = get_local_entity_safe_ptr (index);
					
					break;
				}
			}
			
			break;
		}
		////////////////////////////////////////
		case PACK_MODE_CLIENT_SESSION:
		////////////////////////////////////////
		{
			int
				index;
			
			waypoint
				*raw;
			
			//
			// create entity
			//
			
			index = unpack_entity_safe_index ();
			
			en = get_free_entity (index);
			
			set_local_entity_type (en, type);
			
			raw = malloc_fast_mem (sizeof (waypoint));
			
			set_local_entity_data (en, raw);
			
			memset (raw, 0, sizeof (waypoint));
			
			//
			// unpack data (in exactly the same order as the data was packed)
			//
			
			raw->sub_type = unpack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);

			unpack_list_link (en, LIST_TYPE_WAYPOINT, &raw->waypoint_link);
			
			raw->altitude = unpack_float_value (en, FLOAT_TYPE_ALTITUDE);
			
			raw->position_type = unpack_int_value (en, INT_TYPE_POSITION_TYPE);
			
			raw->route_node = unpack_int_value (en, INT_TYPE_ROUTE_NODE);
			
			raw->tag = unpack_char_value (en, CHAR_TYPE_TAG);
			
			raw->waypoint_formation = unpack_int_value (en, INT_TYPE_WAYPOINT_FORMATION);
			
			//
			//
			//
			
			switch (raw->position_type)
			{
				
				case POSITION_TYPE_RELATIVE:
				{
					
					debug_fatal ("WP_PACK: internal waypoint with relative position");
					
					break;
				}
				
				case POSITION_TYPE_ABSOLUTE:
				case POSITION_TYPE_VIRTUAL:
				{
					
					unpack_vec3d (en, VEC3D_TYPE_POSITION, &raw->position);
					
					index = unpack_entity_safe_index ();
					
					raw->position_entity = get_local_entity_safe_ptr (index);
					
					break;
				}
			}
			
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

void overload_waypoint_pack_functions (void)
{
	fn_pack_local_entity_data[ENTITY_TYPE_WAYPOINT]         = pack_local_data;
	
	fn_unpack_local_entity_data[ENTITY_TYPE_WAYPOINT]       = unpack_local_data;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
