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

#define CHASE_CAMERA_ROTATE_RATE			(rad (90.0))
#define CHASE_CAMERA_ROTATE_UP_LIMIT	(rad (90.0))
#define CHASE_CAMERA_ROTATE_DOWN_LIMIT	(rad (-90.0))

#define CHASE_CAMERA_ZOOM_RATE			(0.5)
#define CHASE_CAMERA_ZOOM_IN_LIMIT		(0.0)
#define CHASE_CAMERA_ZOOM_OUT_LIMIT		(1.0)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_chase_camera (camera *raw)
{
	ASSERT (raw);

	ASSERT (raw->external_view_entity);

	//
	// motion vector
	//

	get_local_entity_vec3d (raw->external_view_entity, VEC3D_TYPE_MOTION_VECTOR, &raw->motion_vector);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_chase_camera_position (camera *raw)
{
	ASSERT (raw);

	raw->chase_camera_heading = rad (0.0);

	if (!raw->chase_camera_lock_rotate)
	{
		if (raw->external_view_entity)
		{
			raw->chase_camera_heading = get_local_entity_float_value (raw->external_view_entity, FLOAT_TYPE_HEADING);
		}
	}

	raw->chase_camera_pitch = CHASE_CAMERA_RESET_PITCH;

	raw->chase_camera_zoom = CHASE_CAMERA_RESET_ZOOM;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_chase_camera (camera *raw)
{
	entity
		*en;

	float
		combined_heading,
		z_min,
		z_max;

	vec3d
		rel_camera_position;

	//
	// pre-amble
	//

	ASSERT (raw);

	ASSERT (raw->external_view_entity);

	en = raw->external_view_entity;

	if ((command_line_mouse_look == MOUSELOOK_OFF)||	// Retro 31Oct2004.. if keyboard/POV panning.. (by me, stuff inside is (C) RW)
		(command_line_mouse_look == MOUSELOOK_INTERNAL))
	{

		//
		// adjust camera heading
		//

		if (adjust_view_left_key || joystick_pov_left)
		{
			raw->chase_camera_heading += CHASE_CAMERA_ROTATE_RATE * get_delta_time ();
		}
		else if (adjust_view_right_key || joystick_pov_right)
		{
			raw->chase_camera_heading -= CHASE_CAMERA_ROTATE_RATE * get_delta_time ();
		}

		raw->chase_camera_heading = wrap_angle (raw->chase_camera_heading);

		//
		// adjust camera pitch
		//

		if (adjust_view_up_key || joystick_pov_up)
		{
			raw->chase_camera_pitch -= CHASE_CAMERA_ROTATE_RATE * get_delta_time ();

			raw->chase_camera_pitch = max (CHASE_CAMERA_ROTATE_DOWN_LIMIT, raw->chase_camera_pitch);
		}
		else if (adjust_view_down_key || joystick_pov_down)
		{
			raw->chase_camera_pitch += CHASE_CAMERA_ROTATE_RATE * get_delta_time ();

			raw->chase_camera_pitch = min (CHASE_CAMERA_ROTATE_UP_LIMIT, raw->chase_camera_pitch);
		}
	}
	else // Retro 31Oct2004 - mouse or TrackIR control
	{
		float
			temp_p,
			temp_h;

		// No TIR window, use mouse;
		// OR trackir active, but user doesn't want this in outside view

		if ((query_TIR_active() == FALSE)||
			(!command_line_external_trackir))
		{
			temp_h = get_absolute_mouse_x ();
			temp_p = get_absolute_mouse_y ();

			temp_h = -180*temp_h/16383;
			temp_p = -90*temp_p/16383;
			
			raw->chase_camera_pitch = rad(temp_p);
			raw->chase_camera_heading = rad(temp_h);

			// wrap horizontal pan.. vertical is limited to +- 180 degree
			// it is 179 because of rounding.. it never gets 180 but 179.999...
			if (temp_h <= -179)
			{
				set_absolute_mouse_x(-16383);
			}
			else if (temp_h >= 179)
			{
				set_absolute_mouse_x(16383);
			}
		}
		else	// TrackIR - TIR is am absolute device and hence can not wrap. Vertical pan is limited as above
		{
			temp_h = (float) GetYaw();
			temp_p = (float) GetPitch();

			temp_h = 180*temp_h/16383;
			temp_p = -90*temp_p/16383;

			raw->chase_camera_pitch = rad(temp_p);
			raw->chase_camera_heading = rad(temp_h);
		}

		raw->chase_camera_pitch = max (CHASE_CAMERA_ROTATE_DOWN_LIMIT, raw->chase_camera_pitch);
		raw->chase_camera_pitch = min (CHASE_CAMERA_ROTATE_UP_LIMIT, raw->chase_camera_pitch);
	} // Retro 31Oct2004 end

	if (adjust_view_zoom_in_key)
	{
		raw->chase_camera_zoom -= CHASE_CAMERA_ZOOM_RATE * get_delta_time ();

		raw->chase_camera_zoom = max (CHASE_CAMERA_ZOOM_IN_LIMIT, raw->chase_camera_zoom);
	}
	else if (adjust_view_zoom_out_key)
	{
		raw->chase_camera_zoom += CHASE_CAMERA_ZOOM_RATE * get_delta_time ();

		raw->chase_camera_zoom = min (CHASE_CAMERA_ZOOM_OUT_LIMIT, raw->chase_camera_zoom);
	}

	//
	// get camera attitude
	//

	if (get_local_entity_int_value (en, INT_TYPE_ALIVE) && raw->chase_camera_lock_rotate)
	{
		combined_heading = get_local_entity_float_value (en, FLOAT_TYPE_HEADING);
	}
	else
	{
		combined_heading = 0.0;
	}

	combined_heading += raw->chase_camera_heading;

	get_3d_transformation_matrix (raw->attitude, combined_heading, raw->chase_camera_pitch, 0.0);

	//
	// get camera position
	//

	if (in_flight_zoom_test)
	{
		z_min = get_local_entity_float_value (en, FLOAT_TYPE_CHASE_VIEW_MIN_DISTANCE_TEST);
		z_max = get_local_entity_float_value (en, FLOAT_TYPE_CHASE_VIEW_MAX_DISTANCE_TEST);
	}
	else
	{
		z_min = get_local_entity_float_value (en, FLOAT_TYPE_CHASE_VIEW_MIN_DISTANCE);
		z_max = get_local_entity_float_value (en, FLOAT_TYPE_CHASE_VIEW_MAX_DISTANCE);
	}

	ASSERT (z_min < z_max);

	rel_camera_position.x = 0.0;
	rel_camera_position.y = 0.0;
	rel_camera_position.z = -(((z_max - z_min) * raw->chase_camera_zoom * raw->chase_camera_zoom) + z_min);

	multiply_matrix3x3_vec3d (&rel_camera_position, raw->attitude, &rel_camera_position);

	get_local_entity_target_point (en, &raw->position);

	raw->position.x += rel_camera_position.x;
	raw->position.y += rel_camera_position.y;
	raw->position.z += rel_camera_position.z;

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

	get_local_entity_vec3d (en, VEC3D_TYPE_MOTION_VECTOR, &raw->motion_vector);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_chase_camera_view_target_to_source (entity *source, entity *target)
{
	camera
		*raw;

	float
		length;

	vec3d
		*source_position,
		*target_position,
		direction;

	ASSERT (source);

	ASSERT (target);

	ASSERT (get_camera_entity ());

	raw = get_local_entity_data (get_camera_entity ());

	source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

	target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

	direction.x = source_position->x - target_position->x;
	direction.y = source_position->y - target_position->y;
	direction.z = source_position->z - target_position->z;

	length = (direction.x * direction.x) + (direction.y * direction.y) + (direction.z * direction.z);

	if (length > 1.0)
	{
		length = sqrt (length);

		normalise_3d_vector_given_magnitude (&direction, length);

		raw->chase_camera_heading = atan2 (direction.x, direction.z);

		if (raw->chase_camera_lock_rotate)
		{
			raw->chase_camera_heading -= get_local_entity_float_value (target, FLOAT_TYPE_HEADING);

			raw->chase_camera_heading = wrap_angle (raw->chase_camera_heading);
		}

		raw->chase_camera_pitch = asin (direction.y);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
