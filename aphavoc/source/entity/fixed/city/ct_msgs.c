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

static void update_city_bounding_box (entity *this_city, entity *this_building)
{
	city
		*raw;

	object_3d_index_numbers
		object_3d_index;

	object_3d_bounds
		*bounding_box;

	vec3d
		*building_position,
		position_offset,
		p1,
		p2;

	matrix3x3
		attitude;

	float
		heading;

	ASSERT (this_city);

	ASSERT (this_building);

	raw = get_local_entity_data (this_city);

	//
	// get building bounding box minmax points (assume on flat ground)
	//

	object_3d_index = get_local_entity_int_value (this_building, INT_TYPE_OBJECT_3D_SHAPE);

	ASSERT (object_3d_index != OBJECT_3D_INVALID_OBJECT_INDEX);

	bounding_box = get_object_3d_bounding_box_without_lines (object_3d_index);

	ASSERT (bounding_box);

	p1.x = bounding_box->xmin;
	p1.y = bounding_box->ymin;
	p1.z = bounding_box->zmin;

	p2.x = bounding_box->xmax;
	p2.y = bounding_box->ymax;
	p2.z = bounding_box->zmax;

	//
	// rotate minmax points (no longer minmax after rotate)
	//

	heading = get_local_entity_float_value (this_building, FLOAT_TYPE_HEADING);

	get_3d_transformation_matrix (attitude, heading, 0.0, 0.0);

	multiply_matrix3x3_vec3d (&p1, attitude, &p1);
	multiply_matrix3x3_vec3d (&p2, attitude, &p2);

	//
	// get building position offset from city centre
	//

	building_position = get_local_entity_vec3d_ptr (this_building, VEC3D_TYPE_POSITION);

	position_offset.x = building_position->x - raw->fix.position.x;
	position_offset.y = building_position->y - raw->fix.position.y;
	position_offset.z = building_position->z - raw->fix.position.z;

	//
	// offset p1 and p2
	//

	p1.x += position_offset.x;
	p1.y += position_offset.y;
	p1.z += position_offset.z;

	p2.x += position_offset.x;
	p2.y += position_offset.y;
	p2.z += position_offset.z;

	//
	// adjust city bounding box
	//

	if (p1.x < raw->bounding_box_min.x) raw->bounding_box_min.x = p1.x;
	if (p1.y < raw->bounding_box_min.y) raw->bounding_box_min.y = p1.y;
	if (p1.z < raw->bounding_box_min.z) raw->bounding_box_min.z = p1.z;
	if (p1.x > raw->bounding_box_max.x) raw->bounding_box_max.x = p1.x;
	if (p1.y > raw->bounding_box_max.y) raw->bounding_box_max.y = p1.y;
	if (p1.z > raw->bounding_box_max.z) raw->bounding_box_max.z = p1.z;

	if (p2.x < raw->bounding_box_min.x) raw->bounding_box_min.x = p2.x;
	if (p2.y < raw->bounding_box_min.y) raw->bounding_box_min.y = p2.y;
	if (p2.z < raw->bounding_box_min.z) raw->bounding_box_min.z = p2.z;
	if (p2.x > raw->bounding_box_max.x) raw->bounding_box_max.x = p2.x;
	if (p2.y > raw->bounding_box_max.y) raw->bounding_box_max.y = p2.y;
	if (p2.z > raw->bounding_box_max.z) raw->bounding_box_max.z = p2.z;

	ASSERT (raw->bounding_box_min.x <= raw->bounding_box_max.x);
	ASSERT (raw->bounding_box_min.y <= raw->bounding_box_max.y);
	ASSERT (raw->bounding_box_min.z <= raw->bounding_box_max.z);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_link_child (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	list_types
		list_type;

	#if DEBUG_MODULE

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	list_type = va_arg (pargs, list_types);

	switch (list_type)
	{
		////////////////////////////////////////
		case LIST_TYPE_CITY_BUILDING:
		////////////////////////////////////////
		{
			update_city_bounding_box (receiver, sender);

			break;
		}
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MODULE

static int response_to_unlink_child (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	debug_log_entity_message (message, receiver, sender, pargs);

	return (TRUE);
}

#endif

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

void overload_city_message_responses (void)
{
	overload_fixed_message_responses (ENTITY_TYPE_CITY);

	message_responses[ENTITY_TYPE_CITY][ENTITY_MESSAGE_LINK_CHILD]		= response_to_link_child;

	#if DEBUG_MODULE

	message_responses[ENTITY_TYPE_CITY][ENTITY_MESSAGE_UNLINK_CHILD]	= response_to_unlink_child;

	message_responses[ENTITY_TYPE_CITY][ENTITY_MESSAGE_LINK_PARENT]	= response_to_link_parent;

	message_responses[ENTITY_TYPE_CITY][ENTITY_MESSAGE_UNLINK_PARENT]	= response_to_unlink_parent;

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
