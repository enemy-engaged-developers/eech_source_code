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

void store_reverse_tactical_camera_values (void)
{
	camera
		*raw = nullptr;

	ASSERT (get_camera_entity ());

	raw = (camera *) get_local_entity_data (get_camera_entity ());

	raw->stored_reverse_tactical_position = raw->position;

	raw->stored_reverse_tactical_motion_vector = raw->motion_vector;

	memcpy (raw->stored_reverse_tactical_attitude, raw->attitude, sizeof (matrix3x3));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void restore_reverse_tactical_camera_values (void)
{
	camera
		*raw = nullptr;

	ASSERT (get_camera_entity ());

	raw = (camera *) get_local_entity_data (get_camera_entity ());

	raw->position = raw->stored_reverse_tactical_position;

	raw->motion_vector = raw->stored_reverse_tactical_motion_vector;

	memcpy (raw->attitude, raw->stored_reverse_tactical_attitude, sizeof (matrix3x3));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_reverse_tactical_camera_values (entity *source, entity *target)
{
	camera
		*raw = nullptr;

	int
		airborne;

	object_3d_index_numbers
		object_3d_index;

	object_3d_bounds
		*bounding_box = nullptr;

	float
		length,
		radius,
		z_min,
		z_max,
		rad_alt,
		dx,
		dy,
		dz;

	vec3d
		source_position,
		target_position,
		direction;

	ASSERT (source);

	ASSERT (target);

	ASSERT (get_camera_entity ());

	raw = (camera *) get_local_entity_data (get_camera_entity ());
	
	//
	// get camera position
	//

	if (get_local_entity_int_value (target, INT_TYPE_IDENTIFY_FIXED))
	{
		object_3d_index = get_local_entity_int_value (target, INT_TYPE_OBJECT_3D_SHAPE);

		bounding_box = get_object_3d_bounding_box (object_3d_index);

		dx = bounding_box->xmax - bounding_box->xmin;
		dy = bounding_box->ymax;
		dz = bounding_box->zmax - bounding_box->zmin;

		radius = sqrt ((dx * dx) + (dy * dy) + (dz * dz)) * 2.0;
	}
	else
	{
		z_min = get_local_entity_float_value (target, FLOAT_TYPE_CHASE_VIEW_MIN_DISTANCE);
		z_max = get_local_entity_float_value (target, FLOAT_TYPE_CHASE_VIEW_MAX_DISTANCE);

		ASSERT (z_min < z_max);

		radius = ((z_max - z_min) * 0.05) + z_min;
	}

	get_local_entity_target_point (source, &source_position);

	get_local_entity_target_point (target, &target_position);

	airborne = FALSE;

	if (get_local_entity_int_value (target, INT_TYPE_AIRBORNE_AIRCRAFT))
	{
		if (point_inside_map_area (&target_position))
		{
			rad_alt = max (target_position.y - get_3d_terrain_elevation (target_position.x, target_position.z), 0.0f);

			if (rad_alt > z_min)
			{
				airborne = TRUE;
			}
		}
	}

	if (airborne)
	{
		direction.x = target_position.x - source_position.x;
		direction.y = target_position.y - source_position.y;
		direction.z = target_position.z - source_position.z;

		length = (direction.x * direction.x) + (direction.y * direction.y) + (direction.z * direction.z);

		if (length > 1.0)
		{
			length = sqrt (length);

			normalise_3d_vector_given_magnitude (&direction, length);
		}
		else
		{
			direction.x = 0.0;
			direction.y = 0.0;
			direction.z = -1.0;
		}
	}
	else
	{
		direction.x = target_position.x - source_position.x;
		direction.y = 0.0;
		direction.z = target_position.z - source_position.z;

		length = (direction.x * direction.x) + (direction.z * direction.z);

		if (length > 1.0)
		{
			length = sqrt (length);

			normalise_3d_vector_given_magnitude (&direction, length);
		}
		else
		{
			direction.x = 0.0;
			direction.z = -1.0;
		}

		direction.y = 0.5;

		normalise_3d_vector (&direction);
	}

	raw->position.x = target_position.x + (direction.x * radius);
	raw->position.y = target_position.y + (direction.y * radius);
	raw->position.z = target_position.z + (direction.z * radius);

	//
	// keep point above ground (unless point off map)
	//

	if (point_inside_map_area (&raw->position))
	{
		raw->position.y = max (raw->position.y, get_3d_terrain_point_data (raw->position.x, raw->position.z, &raw->terrain_info) + CAMERA_MIN_HEIGHT_ABOVE_GROUND);
	}

	//
	// get camera attitude
	//

	direction.x = target_position.x - raw->position.x;
	direction.y = target_position.y - raw->position.y;
	direction.z = target_position.z - raw->position.z;

	length = (direction.x * direction.x) + (direction.y * direction.y) + (direction.z * direction.z);
	
	if (source == target)
	{
		length = 200; // Jabberwock 031016
	
	}

	if (length > 1.0)
	{
		length = sqrt (length);

		normalise_3d_vector_given_magnitude (&direction, length);

		get_matrix3x3_from_unit_vec3d (raw->attitude, &direction);
	}
	else
	{
		get_identity_matrix3x3 (raw->attitude);
	}

	//
	// motion vector
	//

	get_local_entity_vec3d (target, VEC3D_TYPE_MOTION_VECTOR, &raw->motion_vector);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
