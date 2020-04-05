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

void reset_cinematic_camera (camera *raw)
{
	entity
		*en = nullptr;

	object_3d_instance
		*inst3d = nullptr;

	int
		num_moving_cameras,
		num_static_cameras,
		attempts;

	//
	// pre-amble
	//

	ASSERT (raw);

	ASSERT (raw->external_view_entity);

	en = raw->external_view_entity;

	inst3d = (object_3d_instance *) get_local_entity_ptr_value (en, PTR_TYPE_INSTANCE_3D_OBJECT);

	//
	// select 3D camera
	//

	raw->cinematic_camera_index = OBJECT_3D_INVALID_CAMERA_INDEX;

	if (inst3d)
	{
		num_moving_cameras = get_number_of_3d_object_cameras (inst3d, OBJECT_3D_CAMERA_SCENIC_MOVING);

		num_static_cameras = get_number_of_3d_object_cameras (inst3d, OBJECT_3D_CAMERA_SCENIC_STATIC);

		if ((num_moving_cameras > 0) && (num_static_cameras > 0))
		{
			if (frand1 () < 0.333)
			{
				raw->cinematic_camera_index = OBJECT_3D_CAMERA_SCENIC_MOVING;
			}
			else
			{
				raw->cinematic_camera_index = OBJECT_3D_CAMERA_SCENIC_STATIC;
			}
		}
		else if (num_moving_cameras > 0)
		{
			raw->cinematic_camera_index = OBJECT_3D_CAMERA_SCENIC_MOVING;
		}
		else if (num_static_cameras > 0)
		{
			raw->cinematic_camera_index = OBJECT_3D_CAMERA_SCENIC_STATIC;
		}
	}

	switch (raw->cinematic_camera_index)
	{
		////////////////////////////////////////
		case OBJECT_3D_INVALID_CAMERA_INDEX:
		////////////////////////////////////////
		{
			raw->cinematic_camera_depth = 0;

			raw->cinematic_camera_lifetime = (frand1 () * 2.0) + 2.0;

			raw->cinematic_camera_heading = rad (45.0) * ((float) (rand16 () % 8));

			raw->cinematic_camera_pitch = rad (-45.0) * ((float) (rand16 () % 2));

			#if DEBUG_MODULE

			debug_log
			(
				"CINEMATIC CAMERA is INVALID (object = %s, moving cameras = %d, static cameras = %d, depth = %d, lifetime = %.2f, heading = %.2f, pitch = %.2f)",
				get_local_entity_string (en, STRING_TYPE_FULL_NAME),
				num_moving_cameras,
				num_static_cameras,
		  		raw->cinematic_camera_depth,
				raw->cinematic_camera_lifetime,
				deg (raw->cinematic_camera_heading),
				deg (raw->cinematic_camera_pitch)
			);

			#endif

			break;
		}
		////////////////////////////////////////
		case OBJECT_3D_CAMERA_SCENIC_MOVING:
		////////////////////////////////////////
		{
			//
			// try and prevent using the same moving camera twice in succession
			//

			if (num_moving_cameras > 1)
			{
				attempts = 10;

				while (attempts--)
				{
					raw->cinematic_camera_depth = rand16 () % num_moving_cameras;

					if (raw->cinematic_camera_depth != raw->cinematic_camera_previous_moving_depth)
					{
						break;
					}
				}
			}
			else
			{
				raw->cinematic_camera_depth = 0;
			}

			raw->cinematic_camera_previous_moving_depth = raw->cinematic_camera_depth;

			raw->cinematic_camera_lifetime = get_object_3d_camera_lifetime (inst3d, raw->cinematic_camera_index, raw->cinematic_camera_depth);

			#if DEBUG_MODULE

			debug_log
			(
				"CINEMATIC CAMERA is MOVING (object = %s, moving cameras = %d, static cameras = %d, depth = %d, lifetime = %.2f)",
				get_local_entity_string (en, STRING_TYPE_FULL_NAME),
				num_moving_cameras,
				num_static_cameras,
		  		raw->cinematic_camera_depth,
				raw->cinematic_camera_lifetime
			);

			#endif

			ASSERT (raw->cinematic_camera_lifetime > 0.0);

			break;
		}
		////////////////////////////////////////
		case OBJECT_3D_CAMERA_SCENIC_STATIC:
		////////////////////////////////////////
		{
			//
			// try and prevent using the same static camera twice in succession
			//

			if (num_static_cameras > 1)
			{
				attempts = 10;

				while (attempts--)
				{
					raw->cinematic_camera_depth = rand16 () % num_static_cameras;

					if (raw->cinematic_camera_depth != raw->cinematic_camera_previous_static_depth)
					{
						break;
					}
				}
			}
			else
			{
				raw->cinematic_camera_depth = 0;
			}

			raw->cinematic_camera_previous_static_depth = raw->cinematic_camera_depth;

			raw->cinematic_camera_lifetime = (frand1 () * 2.0) + 2.0;

			#if DEBUG_MODULE

			debug_log
			(
				"CINEMATIC CAMERA is STATIC (object = %s, moving cameras = %d, static cameras = %d, depth = %d, lifetime = %.2f)",
				get_local_entity_string (en, STRING_TYPE_FULL_NAME),
				num_moving_cameras,
				num_static_cameras,
		  		raw->cinematic_camera_depth,
				raw->cinematic_camera_lifetime
			);

			#endif
		}
	}

	raw->cinematic_camera_timer = 0.0;

	//
	// motion vector
	//

	get_local_entity_vec3d (en, VEC3D_TYPE_MOTION_VECTOR, &raw->motion_vector);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_cinematic_camera_for_new_view_entity (camera *raw)
{
	ASSERT (raw);

	raw->cinematic_camera_previous_moving_depth = -1;

	raw->cinematic_camera_previous_static_depth = -1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_cinematic_camera (camera *raw)
{
	//
	// pre-amble
	//

	ASSERT (raw);

	ASSERT (raw->external_view_entity);

	////////////////////////////////////////
	//
	// This code has been added to protect against cases where an object
	// and its destroyed version have a different number of cameras.
	//

	switch (raw->cinematic_camera_index)
	{
		case OBJECT_3D_CAMERA_SCENIC_MOVING:
		case OBJECT_3D_CAMERA_SCENIC_STATIC:
		{
			object_3d_instance
				*inst3d = nullptr;

			inst3d = (object_3d_instance *) get_local_entity_ptr_value (raw->external_view_entity, PTR_TYPE_INSTANCE_3D_OBJECT);

			if (raw->cinematic_camera_depth >= get_number_of_3d_object_cameras (inst3d, raw->cinematic_camera_index))
			{
				#if DEBUG_MODULE

				debug_colour_log (DEBUG_COLOUR_RED, "CINEMATIC CAMERA ERROR - forced reset!!!");

				#endif

				reset_cinematic_camera (raw);
			}

			break;
		}
	}

	//
	////////////////////////////////////////

	//
	// update timer
	//

	raw->cinematic_camera_timer += get_delta_time ();

	if (raw->cinematic_camera_timer > raw->cinematic_camera_lifetime)
	{
		if (raw->auto_edit)
		{
			switch_auto_edit_entity (raw);

			if (switch_auto_edit_camera_mode (raw))
			{
				//
				// switched to a different camera
				//

				return;
			}
		}

		reset_cinematic_camera (raw);
	}

	//
	// continue update
	//

	update_cinematic_camera_continued (raw);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_cinematic_camera_continued (camera *raw)
{
	entity
		*en = nullptr;

	object_3d_instance
		*inst3d = nullptr;

	viewpoint
		vp;

	float
		normalised_timer;

	//
	// pre-amble
	//

	ASSERT (raw);

	ASSERT (raw->external_view_entity);

	en = raw->external_view_entity;

	//
	// get camera position and attitude
	//

	switch (raw->cinematic_camera_index)
	{
		////////////////////////////////////////
		case OBJECT_3D_INVALID_CAMERA_INDEX:
		////////////////////////////////////////
		{
			float
				combined_heading,
				z_min,
				z_max;

			vec3d
				rel_camera_position;

			combined_heading = get_local_entity_float_value (en, FLOAT_TYPE_HEADING);

			combined_heading += raw->cinematic_camera_heading;

			get_3d_transformation_matrix (raw->attitude, combined_heading, raw->cinematic_camera_pitch, 0.0);

			z_min = get_local_entity_float_value (en, FLOAT_TYPE_CHASE_VIEW_MIN_DISTANCE);
			z_max = get_local_entity_float_value (en, FLOAT_TYPE_CHASE_VIEW_MAX_DISTANCE);

			ASSERT (z_min < z_max);

			rel_camera_position.x = 0.0;
			rel_camera_position.y = 0.0;
			rel_camera_position.z = -(((z_max - z_min) * 0.1) + z_min);

			multiply_matrix3x3_vec3d (&rel_camera_position, raw->attitude, &rel_camera_position);

			get_local_entity_target_point (en, &raw->position);

			raw->position.x += rel_camera_position.x;
			raw->position.y += rel_camera_position.y;
			raw->position.z += rel_camera_position.z;

			break;
		}
		////////////////////////////////////////
		case OBJECT_3D_CAMERA_SCENIC_MOVING:
		////////////////////////////////////////
		{
			normalised_timer = raw->cinematic_camera_timer / raw->cinematic_camera_lifetime;

			inst3d = (object_3d_instance *) get_local_entity_ptr_value (en, PTR_TYPE_INSTANCE_3D_OBJECT);

			get_local_entity_vec3d (en, VEC3D_TYPE_POSITION, (vec3d *) &inst3d->vp.position);

			get_local_entity_attitude_matrix (en, inst3d->vp.attitude);

			get_object_3d_camera_position (inst3d, raw->cinematic_camera_index, raw->cinematic_camera_depth, normalised_timer, &vp);

			raw->position = vp.position;

			memcpy (raw->attitude, vp.attitude, sizeof (matrix3x3));

			break;
		}
		////////////////////////////////////////
		case OBJECT_3D_CAMERA_SCENIC_STATIC:
		////////////////////////////////////////
		{
			normalised_timer = 0.0;

			inst3d = (object_3d_instance *) get_local_entity_ptr_value (en, PTR_TYPE_INSTANCE_3D_OBJECT);

			get_local_entity_vec3d (en, VEC3D_TYPE_POSITION, (vec3d *) &inst3d->vp.position);

			get_local_entity_attitude_matrix (en, inst3d->vp.attitude);

			get_object_3d_camera_position (inst3d, raw->cinematic_camera_index, raw->cinematic_camera_depth, normalised_timer, &vp);

			raw->position = vp.position;

			memcpy (raw->attitude, vp.attitude, sizeof (matrix3x3));

			break;
		}
	}

	//
	// keep point above ground (unless point off map)
	//

	if (point_inside_map_area (&raw->position))
	{
		raw->position.y = max (raw->position.y, get_3d_terrain_point_data (raw->position.x, raw->position.z, &raw->terrain_info) + 0.5f);
	}

	//
	// motion vector
	//

	get_local_entity_vec3d (en, VEC3D_TYPE_MOTION_VECTOR, &raw->motion_vector);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
