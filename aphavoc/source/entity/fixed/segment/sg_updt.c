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

static void update_server (entity *en)
{
	entity
		*parent,
		*next_segment,
		*prev_segment;

	entity_sub_types
		sub_type;

	vec3d
		*pos;

	float
		terrain_height;

	terrain_3d_point_data
		terrain_info;

	//
	// notify the segments neighbours as applicable
	//

	parent = get_local_entity_parent (en, LIST_TYPE_SEGMENT);

	ASSERT (parent);

	next_segment = get_local_entity_child_succ (en, LIST_TYPE_SEGMENT);

	if (next_segment)
	{
		notify_local_entity (ENTITY_MESSAGE_COLLISION, parent, next_segment);
	}

	prev_segment = get_local_entity_child_pred (en, LIST_TYPE_SEGMENT);

	if (prev_segment)
	{
		notify_local_entity (ENTITY_MESSAGE_COLLISION, parent, prev_segment);
	}

	sub_type = get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);

	if (sub_type == ENTITY_SUB_TYPE_FIXED_BRIDGE_UNSUPPORTED_MID_SECTION)
	{
		//
		// make the segment drop to the floor ( removing it from the update list when it hits )
		//
	
		pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);
	
		pos->y -= ( 10.0 * get_delta_time() );
	
		memset (&terrain_info, 0, sizeof (terrain_3d_point_data));
	
		terrain_height = get_3d_terrain_point_data (pos->x, pos->z, &terrain_info);

		if (get_terrain_type_class (terrain_info.terrain_type) == TERRAIN_CLASS_WATER)
		{
			terrain_height -= 1.0;
		}
	
		if ( pos->y <= terrain_height )
		{
			pos->y = terrain_height;
	
			delete_local_entity_from_parents_child_list (en, LIST_TYPE_UPDATE);
	
			if (get_comms_model () == COMMS_MODEL_SERVER)
			{
				create_client_server_object_hit_ground_explosion_effect (en, terrain_info.terrain_type);
			}
		}
	}
	else
	{
		//
		// segment is supported, and so should be instantly removed from the update list
		// ( only put there in the first place so that neighbours would be notified )
		//

		delete_local_entity_from_parents_child_list (en, LIST_TYPE_UPDATE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_segment_update_functions (void)
{
	fn_update_client_server_entity[ENTITY_TYPE_SEGMENT][COMMS_MODEL_SERVER]	= update_server;

	fn_update_client_server_entity[ENTITY_TYPE_SEGMENT][COMMS_MODEL_CLIENT]	= update_server;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
