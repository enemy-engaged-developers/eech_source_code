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

void reset_drop_camera (camera *raw)
{
	entity
		*en;

	vec3d
		pos,
		v;

	matrix3x3
		m;

	float
		heading,
		z_min,
		z_max;

	//
	// pre-amble
	//

	ASSERT (raw);

	ASSERT (raw->external_view_entity);

	en = raw->external_view_entity;

	//
	// place camera behind object to prevent going inside object (especially when the object is stationary)
	//

	heading = get_local_entity_float_value (en, FLOAT_TYPE_HEADING);

	get_3d_transformation_matrix (m, heading, CHASE_CAMERA_RESET_PITCH, 0.0);

	z_min = get_local_entity_float_value (en, FLOAT_TYPE_CHASE_VIEW_MIN_DISTANCE);
	z_max = get_local_entity_float_value (en, FLOAT_TYPE_CHASE_VIEW_MAX_DISTANCE);

	ASSERT (z_min < z_max);

	v.x = 0.0;
	v.y = 0.0;
	v.z = -(((z_max - z_min) * CHASE_CAMERA_RESET_ZOOM * CHASE_CAMERA_RESET_ZOOM) + z_min);

	multiply_matrix3x3_vec3d (&v, m, &v);

	get_local_entity_target_point (en, &pos);

	raw->position.x = pos.x + v.x;
	raw->position.y = pos.y + v.y;
	raw->position.z = pos.z + v.z;

	//
	// keep point above ground (unless point off map)
	//

	if (point_inside_map_area (&raw->position))
	{
		raw->position.y = max (raw->position.y, get_3d_terrain_point_data (raw->position.x, raw->position.z, &raw->terrain_info) + CAMERA_MIN_HEIGHT_ABOVE_GROUND);
	}

	//
	// motion vector
	//

	raw->motion_vector.x = 0.0;
	raw->motion_vector.y = 0.0;
	raw->motion_vector.z = 0.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_drop_camera (camera *raw)
{
	entity
		*en;

	vec3d
		pos,
		v;

	//
	// pre-amble
	//

	ASSERT (raw);

	ASSERT (raw->external_view_entity);

	en = raw->external_view_entity;

	//
	// get camera to entity vector
	//

	get_local_entity_target_point (en, &pos);

	v.x = pos.x - raw->position.x;
	v.y = pos.y - raw->position.y;
	v.z = pos.z - raw->position.z;

	//
	// prevent divide by zero
	//

	if (get_3d_vector_magnitude (&v) < 0.001f)
	{
		v.x = 0.0;
		v.y = 0.0;
		v.z = 1.0;
	}

	//
	// get camera attitude
	//

	normalise_3d_vector (&v);

	get_matrix3x3_from_unit_vec3d (raw->attitude, &v);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
