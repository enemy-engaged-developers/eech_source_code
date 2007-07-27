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

#define FREE_CAMERA_ROTATE_UP_LIMIT	(rad (90.0))
#define FREE_CAMERA_ROTATE_DOWN_LIMIT	(rad (-90.0))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_free_camera (camera *raw)
{
	// get heading and velocity from previous camera
	raw->chase_camera_heading = get_heading_from_attitude_matrix(raw->attitude);
	multiply_transpose_matrix3x3_vec3d(&raw->velocity, raw->attitude, &raw->motion_vector);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_free_camera (camera *raw)
{
	float
		acceleration,
		combined_heading;

	float
		max_velocity = 100.0;

	float dh, dp;

	// adjust direction (pan)

	if (camera_previous_mouse_update_flag != get_mouse_update_flag())
	{
		dh = get_mouse_move_delta_x() * -180 / 8000.0;
		dp = get_mouse_move_delta_y() * -90 / 8000.0;

		camera_previous_mouse_update_flag = get_mouse_update_flag();
	
		raw->chase_camera_pitch += rad(dp);
		raw->chase_camera_heading -= rad(dh);
	}

	raw->chase_camera_pitch = bound(raw->chase_camera_pitch, FREE_CAMERA_ROTATE_DOWN_LIMIT, FREE_CAMERA_ROTATE_UP_LIMIT);

	combined_heading = raw->chase_camera_heading;

	get_3d_transformation_matrix (raw->attitude, combined_heading, raw->chase_camera_pitch, 0.0);


	// adjustposition (move camera)

	// forward/backwards
	if (move_view_forward_key)
	{
		if (raw->velocity.z < -12.5)
			acceleration = -4.0 * raw->velocity.z;
		else
			acceleration = 50.0;

		acceleration *= move_view_forward_key;
		max_velocity *= move_view_forward_key;
	}
	else if (move_view_backward_key)
	{
		if (raw->velocity.z > 12.5)
			acceleration = -4.0 * raw->velocity.z;
		else
			acceleration = -50.0;

		acceleration *= move_view_backward_key;
		max_velocity *= move_view_backward_key;
	}
	else
		acceleration = -2.0 * raw->velocity.z;

	raw->velocity.z = bound(raw->velocity.z + acceleration * get_delta_time(), -max_velocity, max_velocity);

	// sideways
	max_velocity = 100.0;
	if (move_view_right_key)
	{
		if (raw->velocity.x < -12.5)
			acceleration = -4.0 * raw->velocity.x;
		else
			acceleration = 50.0;

		acceleration *= move_view_right_key;
		max_velocity *= move_view_right_key;
	}
	else if (move_view_left_key)
	{
		if (raw->velocity.x > 12.5)
			acceleration = -4.0 * raw->velocity.x;
		else
			acceleration = -50.0;

		acceleration *= move_view_left_key;
		max_velocity *= move_view_left_key;
	}
	else
		acceleration = -2.0 * raw->velocity.x;

	raw->velocity.x = bound(raw->velocity.x + acceleration * get_delta_time(), -max_velocity, max_velocity);

	acceleration = -2.0 * raw->velocity.y;
	raw->velocity.y += acceleration * get_delta_time();

	// rotate velocity in view diretion:
	multiply_matrix3x3_vec3d(&raw->motion_vector, raw->attitude, &raw->velocity);

	// move in direction of velocity
	raw->position.x += raw->motion_vector.x * get_delta_time();
	raw->position.y += raw->motion_vector.y * get_delta_time();
	raw->position.z += raw->motion_vector.z * get_delta_time();

	// keep point above ground (unless point off map)
	if (point_inside_map_area (&raw->position))
	{
		raw->position.y = max (raw->position.y, get_3d_terrain_point_data (raw->position.x, raw->position.z, &raw->terrain_info) + CAMERA_MIN_HEIGHT_ABOVE_GROUND);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
