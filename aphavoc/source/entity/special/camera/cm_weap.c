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

int weapon_loading_camera_valid (camera *raw)
{
	object_3d_instance
		*inst3d = nullptr;

	ASSERT (raw);

	if (get_gunship_entity ())
	{
		if (raw->external_view_entity == get_gunship_entity ())
		{
			inst3d = get_local_entity_ptr_value (raw->external_view_entity, PTR_TYPE_INSTANCE_3D_OBJECT);

			if (inst3d)
			{
				if (get_number_of_3d_object_cameras (inst3d, OBJECT_3D_CAMERA_PAYLOAD_MOVING) > 0)
				{
					return (TRUE);
				}
				else
				{
					debug_colour_log (DEBUG_COLOUR_RED, "Weapon loading camera requires OBJECT_3D_CAMERA_PAYLOAD_MOVING");
				}
			}
		}
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_weapon_loading_camera (camera *raw)
{
	object_3d_instance
		*inst3d = nullptr;

	//
	// pre-amble
	//

	ASSERT (raw);

	ASSERT (raw->external_view_entity);

	//
	// initialise weapon loading camera
	//

	inst3d = get_local_entity_ptr_value (raw->external_view_entity, PTR_TYPE_INSTANCE_3D_OBJECT);

	ASSERT (inst3d);

	ASSERT (get_number_of_3d_object_cameras (inst3d, OBJECT_3D_CAMERA_PAYLOAD_MOVING) > 0);

	raw->weapon_loading_camera_lifetime = get_object_3d_camera_lifetime (inst3d, OBJECT_3D_CAMERA_PAYLOAD_MOVING, 0);

	ASSERT (raw->weapon_loading_camera_lifetime > 0.0);

	raw->weapon_loading_camera_timer = 0.0;

	//
	// motion vector
	//

	get_local_entity_vec3d (raw->external_view_entity, VEC3D_TYPE_MOTION_VECTOR, &raw->motion_vector);

	//
	// initialise data for weapon loading
	//

	initialise_weapon_loading_mode ();

	//
	// Setup flight dynamics
	//

	set_current_flight_dynamics_wheel_brake (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_weapon_loading_camera (camera *raw)
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
	// get position and attitude of camera
	//

	inst3d = get_local_entity_ptr_value (en, PTR_TYPE_INSTANCE_3D_OBJECT);

	get_local_entity_vec3d (en, VEC3D_TYPE_POSITION, &inst3d->vp.position);

	get_local_entity_attitude_matrix (en, inst3d->vp.attitude);

	raw->weapon_loading_camera_timer += get_delta_time ();

	if (raw->weapon_loading_camera_timer > raw->weapon_loading_camera_lifetime)
	{
		raw->weapon_loading_camera_timer = raw->weapon_loading_camera_lifetime;
	}

	normalised_timer = raw->weapon_loading_camera_timer / raw->weapon_loading_camera_lifetime;

	get_object_3d_camera_position (inst3d, OBJECT_3D_CAMERA_PAYLOAD_MOVING, 0, normalised_timer, &vp);

	raw->position = vp.position;

	memcpy (raw->attitude, vp.attitude, sizeof (matrix3x3));

	//
	// keep point above ground (unless point off map)
	//

	if (point_inside_map_area (&raw->position))
	{
		raw->position.y = max (raw->position.y, get_3d_terrain_point_data (raw->position.x, raw->position.z, &raw->terrain_info) + 0.5);
	}

	//
	// motion vector
	//

	get_local_entity_vec3d (en, VEC3D_TYPE_MOTION_VECTOR, &raw->motion_vector);

	//
	// animate keyframed payload markers
	//

	set_weapon_loading_payload_marker_state (normalised_timer);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void leave_weapon_loading_camera (void)
{
	set_weapon_loading_payload_marker_state (0.0);

	deinitialise_weapon_loading_mode ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
