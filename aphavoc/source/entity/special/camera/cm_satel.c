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

// Jabberwock 031009 Satellite view

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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


void reset_satellite_camera (camera *raw)
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
		z_max,
		length;

	ASSERT (raw);

	ASSERT (raw->external_view_entity);

	en = raw->external_view_entity;

	z_min = get_local_entity_float_value (en, FLOAT_TYPE_CHASE_VIEW_MIN_DISTANCE);
	z_max = get_local_entity_float_value (en, FLOAT_TYPE_CHASE_VIEW_MAX_DISTANCE);

	//ASSERT (z_min < z_max);

	heading = get_local_entity_float_value (en, FLOAT_TYPE_HEADING);

	get_3d_transformation_matrix (m, heading, CHASE_CAMERA_RESET_PITCH, 0.0);

	v.x = 0.0;
	v.y = 0.0;
	v.z = 0.0;

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

	
	raw->motion_vector.y = raw->position.y;
	
	raw->position.y += 5000;
		
	//
	// attitude
	//

	v.x = pos.x - raw->position.x;
	v.y = pos.y - raw->position.y;
	v.z = pos.z - raw->position.z;

	length = (v.x * v.x) + (v.y * v.y) + (v.z * v.z);

	if (length > 1.0)
	{
		length = sqrt (length);

		normalise_3d_vector_given_magnitude (&v, length);

		get_matrix3x3_from_unit_vec3d (raw->attitude, &v);
	}
	else
	{
		get_identity_matrix3x3 (raw->attitude);
	}

	//
	// motion vector
	//

	raw->motion_vector.x = 0.0;
	raw->motion_vector.z = 0.0;
	
	raw->fly_by_camera_timer = frand1() * 150 + 80; // parasiting on the struct, can't get my own data...

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_satellite_camera (camera *raw)
{
	float
		heading,
		pitch;
	
	vec3d
		pos,
		v;

	entity
		*en;
	
	ASSERT (raw);
	
	en = raw->external_view_entity;

	if (adjust_view_left_key || joystick_pov_left)
	{
		raw->position.x -= 1;
	}
	else if (adjust_view_right_key || joystick_pov_right)
	{
		raw->position.x += 1;
	}

	if (adjust_view_up_key || joystick_pov_up)
	{
		raw->position.z += 1;

	}
	else if (adjust_view_down_key || joystick_pov_down)
	{
		raw->position.z -= 1;
	}
	
	if (adjust_view_zoom_out_key)
	{
		raw->position.y += 1000;

		raw->position.y = min (5000 + raw->motion_vector.y, raw->position.y);
		
		adjust_view_zoom_out_key = FALSE;
	}
	else if (adjust_view_zoom_in_key)
	{
		raw->position.y -= 1000;

		raw->position.y = max (1000 + raw->motion_vector.y, raw->position.y);
		
		adjust_view_zoom_in_key = FALSE;
	}

	heading = 0.1;
	
	pitch = -1.5;
	
	switch (get_local_entity_type (en))
	{
		case ENTITY_TYPE_HELICOPTER:
		case ENTITY_TYPE_FIXED_WING:
		case ENTITY_TYPE_ROUTED_VEHICLE:
		case ENTITY_TYPE_SHIP_VEHICLE:
		case ENTITY_TYPE_ANTI_AIRCRAFT:
		case ENTITY_TYPE_GROUP:
		{
			get_local_entity_target_point (en, &pos);
	
			raw->position.x = pos.x + v.x;
			raw->position.z = pos.z + v.z;		

			break;
		}
	}

	get_3d_transformation_matrix (raw->attitude, heading, pitch, 0.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Jabberwock 031009 ends
