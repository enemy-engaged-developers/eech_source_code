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

#define STATIC_CAMERA_ROTATE_RATE			(rad (45.0))
#define STATIC_CAMERA_ROTATE_UP_LIMIT		(rad (90.0))
#define STATIC_CAMERA_ROTATE_DOWN_LIMIT	(rad (-90.0))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_static_camera (camera *raw)
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
		radius,
		length;

	int
		fast_airborne;

	ASSERT (raw);

	ASSERT (raw->external_view_entity);

	en = raw->external_view_entity;

	z_min = get_local_entity_float_value (en, FLOAT_TYPE_CHASE_VIEW_MIN_DISTANCE);
	z_max = get_local_entity_float_value (en, FLOAT_TYPE_CHASE_VIEW_MAX_DISTANCE);

	ASSERT (z_min < z_max);

	radius = -(((z_max - z_min) * CHASE_CAMERA_RESET_ZOOM * CHASE_CAMERA_RESET_ZOOM) + z_min);

	fast_airborne = FALSE;

	if (get_local_entity_int_value (en, INT_TYPE_AIRBORNE_AIRCRAFT))
	{
		if (get_local_entity_vec3d_magnitude (en, VEC3D_TYPE_MOTION_VECTOR) >= knots_to_metres_per_second (10.0))
		{
			fast_airborne = TRUE;
		}
	}

	if (fast_airborne)
	{
		get_local_entity_vec3d (en, VEC3D_TYPE_MOTION_VECTOR, &v);

		normalise_3d_vector (&v);

		v.x *= radius;
		v.y *= radius;
		v.z *= radius;
	}
	else
	{
		heading = get_local_entity_float_value (en, FLOAT_TYPE_HEADING);

		get_3d_transformation_matrix (m, heading, CHASE_CAMERA_RESET_PITCH, 0.0);

		v.x = 0.0;
		v.y = 0.0;
		v.z = radius;

		multiply_matrix3x3_vec3d (&v, m, &v);
	}

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
	raw->motion_vector.y = 0.0;
	raw->motion_vector.z = 0.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_static_camera (camera *raw)
{
	float
		heading,
		pitch;

	ASSERT (raw);

	heading = get_heading_from_attitude_matrix (raw->attitude);

	pitch = get_pitch_from_attitude_matrix (raw->attitude);

	//
	// adjust camera heading
	//

	if (adjust_view_left_key || joystick_pov_left)
	{
		heading -= STATIC_CAMERA_ROTATE_RATE * get_delta_time ();
	}
	else if (adjust_view_right_key || joystick_pov_right)
	{
		heading += STATIC_CAMERA_ROTATE_RATE * get_delta_time ();
	}

	heading = wrap_angle (heading);

	//
	// adjust camera pitch
	//

	if (adjust_view_up_key || joystick_pov_up)
	{
		pitch += STATIC_CAMERA_ROTATE_RATE * get_delta_time ();

		pitch = min (STATIC_CAMERA_ROTATE_UP_LIMIT, pitch);
	}
	else if (adjust_view_down_key || joystick_pov_down)
	{
		pitch -= STATIC_CAMERA_ROTATE_RATE * get_delta_time ();

		pitch = max (STATIC_CAMERA_ROTATE_DOWN_LIMIT, pitch);
	}

	get_3d_transformation_matrix (raw->attitude, heading, pitch, 0.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
