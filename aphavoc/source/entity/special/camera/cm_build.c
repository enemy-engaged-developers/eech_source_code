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

#define BUILDING_CAMERA_ROTATE_RATE			(rad (90.0))
#define BUILDING_CAMERA_ROTATE_UP_LIMIT	(rad (90.0))
#define BUILDING_CAMERA_ROTATE_DOWN_LIMIT	(rad (-90.0))

#define BUILDING_CAMERA_ZOOM_RATE			(0.5)
#define BUILDING_CAMERA_ZOOM_IN_LIMIT		(0.0)
#define BUILDING_CAMERA_ZOOM_OUT_LIMIT		(1.0)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_building_camera (camera *raw)
{
	ASSERT (raw);

	raw->motion_vector.x = 0.0;
	raw->motion_vector.y = 0.0;
	raw->motion_vector.z = 0.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_building_camera_values (entity *en)
{
	camera
		*raw;

	float
		dx,
		dy,
		dz;

	object_3d_index_numbers
		object_3d_index;

	object_3d_bounds
		*bounding_box;

	ASSERT (en);

	ASSERT (get_camera_entity ());

	raw = get_local_entity_data (get_camera_entity ());

	//
	// position
	//

	get_local_entity_target_point (en, &raw->building_camera_position);

	//
	// radius
	//

	object_3d_index = get_local_entity_int_value (en, INT_TYPE_OBJECT_3D_SHAPE);

	bounding_box = get_object_3d_bounding_box (object_3d_index);

	dx = bounding_box->xmax - bounding_box->xmin;
	dy = bounding_box->ymax;
	dz = bounding_box->zmax - bounding_box->zmin;

	raw->building_camera_radius = sqrt ((dx * dx) + (dy * dy) + (dz * dz)) * 4.0;

	//
	// heading
	//

	raw->building_camera_heading = get_local_entity_float_value (en, FLOAT_TYPE_HEADING);

	raw->building_camera_heading += rad (180.0);

	raw->building_camera_heading = wrap_angle (raw->building_camera_heading);

	//
	// pitch
	//

	raw->building_camera_pitch = rad (-15.0);

	//
	// zoom
	//

	raw->building_camera_zoom = 0.333;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_building_camera (camera *raw)
{
	float
		z_min,
		z_max;

	vec3d
		rel_camera_position;

	//
	// pre-amble
	//

	ASSERT (raw);

	raw->position = raw->building_camera_position;

	//
	// adjust camera heading
	//

	if (adjust_view_left_key || joystick_pov_left)
	{
		raw->building_camera_heading += BUILDING_CAMERA_ROTATE_RATE * get_delta_time ();
	}
	else if (adjust_view_right_key || joystick_pov_right)
	{
		raw->building_camera_heading -= BUILDING_CAMERA_ROTATE_RATE * get_delta_time ();
	}

	raw->building_camera_heading = wrap_angle (raw->building_camera_heading);

	//
	// adjust camera pitch
	//

	if (adjust_view_up_key || joystick_pov_up)
	{
		raw->building_camera_pitch -= BUILDING_CAMERA_ROTATE_RATE * get_delta_time ();

		raw->building_camera_pitch = max (BUILDING_CAMERA_ROTATE_DOWN_LIMIT, raw->building_camera_pitch);
	}
	else if (adjust_view_down_key || joystick_pov_down)
	{
		raw->building_camera_pitch += BUILDING_CAMERA_ROTATE_RATE * get_delta_time ();

		raw->building_camera_pitch = min (BUILDING_CAMERA_ROTATE_UP_LIMIT, raw->building_camera_pitch);
	}

	//
	// adjust camera zoom
	//

	if (adjust_view_zoom_in_key)
	{
		raw->building_camera_zoom -= BUILDING_CAMERA_ZOOM_RATE * get_delta_time ();

		raw->building_camera_zoom = max (BUILDING_CAMERA_ZOOM_IN_LIMIT, raw->building_camera_zoom);
	}
	else if (adjust_view_zoom_out_key)
	{
		raw->building_camera_zoom += BUILDING_CAMERA_ZOOM_RATE * get_delta_time ();

		raw->building_camera_zoom = min (BUILDING_CAMERA_ZOOM_OUT_LIMIT, raw->building_camera_zoom);
	}

	//
	// get camera attitude
	//

	get_3d_transformation_matrix (raw->attitude, raw->building_camera_heading, raw->building_camera_pitch, 0.0);

	//
	// get camera position
	//

	z_min = raw->building_camera_radius * 0.25;

	z_max = raw->building_camera_radius;

	rel_camera_position.x = 0.0;
	rel_camera_position.y = 0.0;
	rel_camera_position.z = -(((z_max - z_min) * raw->building_camera_zoom * raw->building_camera_zoom) + z_min);

	multiply_matrix3x3_vec3d (&rel_camera_position, raw->attitude, &rel_camera_position);

	raw->position.x = raw->building_camera_position.x + rel_camera_position.x;
	raw->position.y = raw->building_camera_position.y + rel_camera_position.y;
	raw->position.z = raw->building_camera_position.z + rel_camera_position.z;

	//
	// keep point above ground (unless point off map)
	//

	if (point_inside_map_area (&raw->position))
	{
		raw->position.y = max (raw->position.y, get_3d_terrain_point_data (raw->position.x, raw->position.z, &raw->terrain_info) + CAMERA_MIN_HEIGHT_ABOVE_GROUND);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
