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

void reset_fly_by_camera (camera *raw)
{
	entity
		*en;

	entity_forces
		force;

	vec3d
		pos,
		mvec,
		v;

	matrix3x3
		m1,
		m2,
		m3;

	float
		min_dist,
		rad_alt,
		velocity,
		heading,
		theta,
		duration;

	int
		near_to_ground;

	//
	// pre-amble
	//

	ASSERT (raw);

	ASSERT (raw->external_view_entity);

	en = raw->external_view_entity;

	get_local_entity_target_point (en, &pos);

	get_local_entity_vec3d (en, VEC3D_TYPE_MOTION_VECTOR, &mvec);

	min_dist = get_local_entity_float_value (en, FLOAT_TYPE_CHASE_VIEW_MIN_DISTANCE);

	//
	// get rotation limits and fly-by duration wrt force
	//

	force = (entity_forces) get_local_entity_int_value (en, INT_TYPE_FORCE);

	switch (force)
	{
		////////////////////////////////////////
		case ENTITY_FORCE_AIR:
		////////////////////////////////////////
		{
			if (point_inside_map_area (&pos))
			{
				if (get_local_entity_int_value (en, INT_TYPE_AIRBORNE_AIRCRAFT))
				{
					rad_alt = max (pos.y - get_3d_terrain_elevation (pos.x, pos.z), 0.0f);

					if (rad_alt < min_dist)
					{
						near_to_ground = TRUE;
					}
					else
					{
						near_to_ground = FALSE;
					}
				}
				else
				{
					near_to_ground = TRUE;
				}
			}
			else
			{
				near_to_ground = TRUE;
			}

			//
			// prevent underside view if near to ground
			//

			if (near_to_ground)
			{
				theta = rad (5.0f) + (frand1 () * rad (75.0f));
			}
			else
			{
				theta = rad (5.0f) + (frand1 () * rad (170.0));
			}

			duration = 2.0 + (frand1 () * 6.0);

			break;
		}
		////////////////////////////////////////
		case ENTITY_FORCE_GROUND:
		////////////////////////////////////////
		{
			theta = rad (30.0f) + (frand1 () * rad (50.0f));

			duration = 4.0 + (frand1 () * 4.0);

			break;
		}
		////////////////////////////////////////
		case ENTITY_FORCE_SEA:
		////////////////////////////////////////
		{
			theta = rad (60.0f) + (frand1 () * rad (20.0f));

			duration = 6.0 + (frand1 () * 4.0);

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal ("Invalid force = %d", force);

			break;
		}
	}

	if (sfrand1 () < 0.0)
	{
		theta = -theta;
	}

	raw->fly_by_camera_timer = duration;

	//
	// if velocity is small then use a random heading
	//

	velocity = get_3d_vector_magnitude (&mvec);

	if (velocity < 1.0)
	{
		heading = sfrand1 () * rad (180.0f);

		mvec.x = sin (heading);
		mvec.y = 0.0;
		mvec.z = cos (heading);
	}

	//
	// get offset vector perpendicular to motion vector (offset vector = y vector of attitude matrix)
	//

	v = mvec;

	normalise_3d_vector (&v);

	get_matrix3x3_from_unit_vec3d (m1, &v);

	//
	// rotate offset vector about motion vector
	//

	get_3d_transformation_matrix (m2, 0.0, 0.0, theta);

	multiply_matrix3x3_matrix3x3 (m3, m2, m1);

	//
	// scale offset vector
	//

	m3[1][0] *= min_dist;
	m3[1][1] *= min_dist;
	m3[1][2] *= min_dist;

	//
	// scale motion vector
	//

	duration *= 0.5;

	mvec.x *= duration;
	mvec.y *= duration;
	mvec.z *= duration;

	//
	// camera position = entity position + motion vector + offset vector
	//

	raw->position.x = pos.x + mvec.x + m3[1][0];
	raw->position.y = pos.y + mvec.y + m3[1][1];
	raw->position.z = pos.z + mvec.z + m3[1][2];

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

void update_fly_by_camera (camera *raw)
{
	//
	// pre-amble
	//

	ASSERT (raw);

	ASSERT (raw->external_view_entity);

	//
	// update timer
	//

	raw->fly_by_camera_timer -= get_delta_time ();

	if (raw->fly_by_camera_timer < 0.0)
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

		reset_fly_by_camera (raw);
	}

	//
	// continue update
	//

	update_fly_by_camera_continued (raw);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_fly_by_camera_continued (camera *raw)
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
	// reset camera position if entity is too close
	//

	if (get_3d_vector_magnitude (&v) < (get_local_entity_float_value (en, FLOAT_TYPE_CHASE_VIEW_MIN_DISTANCE) * 0.5))
	{
		reset_fly_by_camera (raw);

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
