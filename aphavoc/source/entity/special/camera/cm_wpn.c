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

entity *get_external_view_entity_viewable_weapon (void)
{
	camera
		*raw;

	entity
		*en;

	ASSERT (get_camera_entity ());

	raw = get_local_entity_data (get_camera_entity ());

	ASSERT (raw->external_view_entity);

	en = get_local_entity_first_child (raw->external_view_entity, LIST_TYPE_LAUNCHED_WEAPON);

	while (en)
	{
		if (get_local_entity_int_value (en, INT_TYPE_VIEWABLE_WEAPON))
		{
			break;
		}

		en = get_local_entity_child_succ (en, LIST_TYPE_LAUNCHED_WEAPON);
	}

	return (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *get_local_entity_viewable_weapon (entity *this_entity)
{
	entity
		*en;

	ASSERT (this_entity);

	en = get_local_entity_first_child (this_entity, LIST_TYPE_LAUNCHED_WEAPON);

	while (en)
	{
		if (get_local_entity_int_value (en, INT_TYPE_VIEWABLE_WEAPON))
		{
			break;
		}

		en = get_local_entity_child_succ (en, LIST_TYPE_LAUNCHED_WEAPON);
	}

	return (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int weapon_camera_valid (camera *raw)
{
	ASSERT (raw);

	if (raw->view_weapon_root.first_child)
	{
		return (TRUE);
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_weapon_camera (camera *raw)
{
	ASSERT (raw);

	ASSERT (raw->external_view_entity);

	ASSERT (raw->view_weapon_root.first_child);

	raw->weapon_camera_direction.x = 0.0;
	raw->weapon_camera_direction.y = 0.0;
	raw->weapon_camera_direction.z = 0.0;

	reset_offset(raw);
	raw->chase_camera_zoom = 0.1;

	//
	// motion vector
	//

	get_local_entity_vec3d (raw->view_weapon_root.first_child, VEC3D_TYPE_MOTION_VECTOR, &raw->motion_vector);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_weapon_camera (camera *raw)
{
	entity
		*weapon,
		*target;

	vec3d
		*weapon_position,
		target_position,
		direction;

	float
		length;

	int
		spoofed;

	ASSERT (raw);

	ASSERT (raw->view_weapon_root.first_child);

	weapon = raw->view_weapon_root.first_child;

	target = get_local_entity_parent (weapon, LIST_TYPE_TARGET);

	////////////////////////////////////////
	//
	// update weapon camera
	//
	////////////////////////////////////////

	adjust_camera_zoom(raw);
	
	//
	// camera position and attitude
	//

	weapon_position = get_local_entity_vec3d_ptr (weapon, VEC3D_TYPE_POSITION);

	if (target)
	{
		get_local_entity_target_point (target, &target_position);

		direction.x = target_position.x - weapon_position->x;
		direction.y = target_position.y - weapon_position->y;
		direction.z = target_position.z - weapon_position->z;

		length = get_3d_vector_magnitude (&direction);

		if (length > 0.001)
		{
			normalise_3d_vector_given_magnitude (&direction, length);
		}
		else
		{
			get_local_entity_vec3d (weapon, VEC3D_TYPE_ZV, &direction);
		}
	}
	else
	{
		get_local_entity_vec3d (weapon, VEC3D_TYPE_ZV, &direction);
	}

	get_matrix3x3_from_unit_vec3d (raw->attitude, &direction);

	raw->position.x = weapon_position->x - (raw->attitude[2][0] * (5.0 + 100.0 * raw->chase_camera_zoom)) + (raw->attitude[1][0] * 1.0);
	raw->position.y = weapon_position->y - (raw->attitude[2][1] * (5.0 + 100.0 * raw->chase_camera_zoom)) + (raw->attitude[1][1] * 1.0);
	raw->position.z = weapon_position->z - (raw->attitude[2][2] * (5.0 + 100.0 * raw->chase_camera_zoom)) + (raw->attitude[1][2] * 1.0);

	add_turbulence(raw, &raw->position);

	if (point_inside_map_area (&raw->position))
	{
		raw->position.y = max (raw->position.y, get_3d_terrain_point_data (raw->position.x, raw->position.z, &raw->terrain_info) + CAMERA_MIN_HEIGHT_ABOVE_GROUND);
	}

	//
	// motion vector
	//

	get_local_entity_vec3d (weapon, VEC3D_TYPE_MOTION_VECTOR, &raw->motion_vector);

	////////////////////////////////////////
	//
	// setup the explosion camera direction
	//
	////////////////////////////////////////

	//
	// default to the weapon's direction
	//

	get_local_entity_vec3d (weapon, VEC3D_TYPE_ZV, &raw->weapon_camera_direction);

	//
	// if the target is a decoy then get the decoy's launcher (actual target)
	//

	spoofed = FALSE;

	if (target)
	{
		if (get_local_entity_int_value (target, INT_TYPE_IDENTIFY_WEAPON))
		{
			target = get_local_entity_parent (target, LIST_TYPE_LAUNCHED_WEAPON);

			spoofed = TRUE;
		}
	}

	if (target)
	{
		if (get_local_entity_int_value (target, INT_TYPE_AIRBORNE_AIRCRAFT))
		{
			//
			// air target
			//

			get_local_entity_target_point (target, &target_position);

			if ((!spoofed) && (get_3d_range (weapon_position, &target_position) < 250.0))
			{
				get_local_entity_vec3d (target, VEC3D_TYPE_MOTION_VECTOR, &raw->weapon_camera_direction);
			}
			else
			{
  				raw->weapon_camera_direction.x = target_position.x - weapon_position->x;
				raw->weapon_camera_direction.y = target_position.y - weapon_position->y;
				raw->weapon_camera_direction.z = target_position.z - weapon_position->z;
			}
		}
		else
		{
			//
			// ground target
			//

			raw->weapon_camera_direction.x = target_position.x - weapon_position->x;
			raw->weapon_camera_direction.y = target_position.y - weapon_position->y;
			raw->weapon_camera_direction.z = target_position.z - weapon_position->z;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
