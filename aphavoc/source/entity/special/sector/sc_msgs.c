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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_link_child (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	entity
		*enemy_force = nullptr,
		*allied_force = nullptr;

	sector
		*raw = nullptr;

	entity_sides
		side;

	list_types
		list_type;

	session_list_types
		session_type;

	#if DEBUG_MODULE

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	raw = (sector *) get_local_entity_data (receiver);

	list_type = va_arg (pargs, list_types);

	////////////////////////////////////////

	if (list_type == LIST_TYPE_SECTOR)
	{
		float
			height;

		vec3d
			*position = nullptr;

		object_3d_index_numbers
			object_3d_index;

		object_3d_bounds
			*bounding_box = nullptr;

		//
		// check for tallest fixed structure
		//

		if (get_local_entity_int_value (sender, INT_TYPE_IDENTIFY_FIXED))
		{
			object_3d_index = get_local_entity_int_value (sender, INT_TYPE_OBJECT_3D_SHAPE);

			if (object_3d_index != OBJECT_3D_INVALID_OBJECT_INDEX)
			{
				bounding_box = get_object_3d_bounding_box (object_3d_index);

	 			position = get_local_entity_vec3d_ptr (sender, VEC3D_TYPE_POSITION);

				height = position->y + bounding_box->ymax;

				if (height > raw->tallest_structure_height)
				{
					raw->tallest_structure_height = height;
				}
			}
		}

		//
		// set defence levels / activity array
		//

		add_mobile_values_to_sector (receiver, sender);

		//
		// set side awareness + notify force
		//

		if
		(
			(get_local_entity_int_value (sender, INT_TYPE_IDENTIFY_AIRCRAFT)) ||
			(get_local_entity_int_value (sender, INT_TYPE_IDENTIFY_VEHICLE))
		)
		{
			side = (entity_sides) get_local_entity_int_value (sender, INT_TYPE_SIDE);

			////////////////////////////////////////
			//
			// SIDE NOT NEUTRAL.......
			//
			////////////////////////////////////////

			if (side == ENTITY_SIDE_NEUTRAL)
			{
				return TRUE;
			}

			ASSERT (get_valid_current_game_session ());

			set_sector_fog_of_war_value (sender, receiver);

			////////////////////////////////////////
			//
			// ONLY IF GAME INITIALISED......
			//
			////////////////////////////////////////

			if (get_game_status () != GAME_STATUS_INITIALISED)
			{
				return TRUE;
			}

			////////////////////////////////////////
			//
			// SERVER ONLY...... 
			//
			////////////////////////////////////////

			if (get_comms_model () == COMMS_MODEL_CLIENT)
			{
				return TRUE;
			}

			session_type = get_current_game_session_type ();

			// sector occupation timer

			//
			// notify force
			//

			allied_force = get_local_force_entity (side);

			if (allied_force)
			{

				notify_local_entity (ENTITY_MESSAGE_FORCE_ENTERED_SECTOR, allied_force, sender, receiver);
			}

			enemy_force = get_local_force_entity (get_enemy_side (side));

			if (enemy_force)
			{

				notify_local_entity (ENTITY_MESSAGE_FORCE_ENTERED_SECTOR, enemy_force, sender, receiver);
			}
		}
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_unlink_child (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	list_types
		list_type;

	#if DEBUG_MODULE

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	list_type = va_arg( pargs, list_types );

	if ( list_type == LIST_TYPE_SECTOR )
	{
		remove_mobile_values_from_sector (receiver, sender);
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MODULE

static int response_to_link_parent (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	debug_log_entity_message (message, receiver, sender, pargs);

	return (TRUE);
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MODULE

static int response_to_unlink_parent (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	debug_log_entity_message (message, receiver, sender, pargs);

	return (TRUE);
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_sector_message_responses (void)
{
	message_responses[ENTITY_TYPE_SECTOR][ENTITY_MESSAGE_LINK_CHILD]		= response_to_link_child;

	message_responses[ENTITY_TYPE_SECTOR][ENTITY_MESSAGE_UNLINK_CHILD]	= response_to_unlink_child;

	#if DEBUG_MODULE

	message_responses[ENTITY_TYPE_SECTOR][ENTITY_MESSAGE_LINK_PARENT]		= response_to_link_parent;

	message_responses[ENTITY_TYPE_SECTOR][ENTITY_MESSAGE_UNLINK_PARENT]	= response_to_unlink_parent;

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
