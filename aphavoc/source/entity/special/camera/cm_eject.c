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

float
	eject_fader;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_eject_camera (camera *raw)
{
	entity
		*en = nullptr;

	vec3d
		pos,
		v;

	matrix3x3
		m;

	float
		heading,
		z_min,
		z_max;

	//
	// pre-amble
	//

	ASSERT (raw);

	ASSERT (raw->external_view_entity);

	en = raw->external_view_entity;

	//
	// place camera behind object to prevent going inside object (especially when the object is stationary)
	//

	heading = get_local_entity_float_value (en, FLOAT_TYPE_HEADING);

	get_3d_transformation_matrix (m, heading, CHASE_CAMERA_RESET_PITCH, 0.0);

	z_min = get_local_entity_float_value (en, FLOAT_TYPE_CHASE_VIEW_MIN_DISTANCE);
	z_max = get_local_entity_float_value (en, FLOAT_TYPE_CHASE_VIEW_MAX_DISTANCE);

	ASSERT (z_min < z_max);

	v.x = 0.0;
	v.y = 0.0;
	v.z = -(((z_max - z_min) * CHASE_CAMERA_RESET_ZOOM * CHASE_CAMERA_RESET_ZOOM) + z_min);

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

	//
	// motion vector
	//

	raw->motion_vector.x = 0.0;
	raw->motion_vector.y = 0.0;
	raw->motion_vector.z = 0.0;

	//
	// fader
	//

	eject_fader = 0.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_eject_camera (camera *raw)
{
	entity
		*players_gunship = nullptr,
		*launched_weapon = nullptr,
		*ejected_pilot = nullptr,
		*track_target = nullptr;

	//
	// pre-amble (assume the external view entity is the player's gunship)
	//

	ASSERT (raw);

	ASSERT (raw->external_view_entity);

	players_gunship = raw->external_view_entity;

	eject_fader = 0.0;

	//
	// find the ejected pilot
	//

	launched_weapon = get_local_entity_first_child (players_gunship, LIST_TYPE_LAUNCHED_WEAPON);

	ejected_pilot = NULL;

	while (launched_weapon)
	{
		if (get_crew_role () == CREW_ROLE_PILOT)
		{
			if (get_local_entity_int_value (launched_weapon, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_WEAPON_HOKUM_PILOT)
			{
				ejected_pilot = launched_weapon;

				break;
			}
		}
		else
		{
			if (get_local_entity_int_value (launched_weapon, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_WEAPON_HOKUM_CO_PILOT)
			{
				ejected_pilot = launched_weapon;

				break;
			}
		}

		launched_weapon = get_local_entity_child_succ (launched_weapon, LIST_TYPE_LAUNCHED_WEAPON);
	}

	//
	// sort out what to watch
	//

	track_target = NULL;

	if (ejected_pilot)
	{
		if (!get_local_weapon_entity_parachute_open (ejected_pilot))
		{
			track_target = ejected_pilot;
		}
	}
	else
	{
		track_target = players_gunship;

		//
		// if either pilot or co-pilot fired then quit mission
		//

		if
		(!
			(
				get_local_entity_weapon_available (players_gunship, ENTITY_SUB_TYPE_WEAPON_HOKUM_PILOT) &&
				get_local_entity_weapon_available (players_gunship, ENTITY_SUB_TYPE_WEAPON_HOKUM_CO_PILOT)
			)
		)
		{
			exit_game_function (NULL);
		}
	}

	if (track_target)
	{
		////////////////////////////////////////
		//
		// TRACK GUNSHIP OR EJECTED PILOT
		//
		////////////////////////////////////////

		vec3d
			pos,
			v;

		//
		// get camera to entity vector
		//

		get_local_entity_target_point (track_target, &pos);

		v.x = pos.x - raw->position.x;
		v.y = pos.y - raw->position.y;
		v.z = pos.z - raw->position.z;

		//
		// prevent divide by zero
		//

		if (get_3d_vector_magnitude (&v) < 0.001)
		{
			v.x = 0.0;
			v.y = 0.0;
			v.z = 1.0;
		}

		//
		// get camera attitude
		//

		normalise_3d_vector (&v);

		get_matrix3x3_from_unit_vec3d (raw->attitude, &v);

		//
		// motion vector
		//

		raw->motion_vector.x = 0.0;
		raw->motion_vector.y = 0.0;
		raw->motion_vector.z = 0.0;
	}
	else
	{
		////////////////////////////////////////
		//
		// WATCH EJECTED PILOT
		//
		////////////////////////////////////////

		vec3d
			rel_camera_position;

		float
			heading,
			terrain_y;

		//
		// get camera attitude
		//

		heading = get_local_entity_float_value (ejected_pilot, FLOAT_TYPE_HEADING);

		heading += rad (180);

		get_3d_transformation_matrix (raw->attitude, heading, rad (-14.036), 0.0);

		//
		// get camera position
		//

		rel_camera_position.x = 0.0;
		rel_camera_position.y = 0.0;
		rel_camera_position.z = -4.123;

		multiply_matrix3x3_vec3d (&rel_camera_position, raw->attitude, &rel_camera_position);

		get_local_entity_vec3d (ejected_pilot, VEC3D_TYPE_POSITION, &raw->position);

		raw->position.x += rel_camera_position.x;
		raw->position.y += rel_camera_position.y;
		raw->position.z += rel_camera_position.z;

		//
		// make camera level
		//

		get_3d_transformation_matrix (raw->attitude, heading, 0.0, 0.0);

		//
		// keep point above ground (unless point off map)
		//

		if (point_inside_map_area (&raw->position))
		{
			terrain_y = get_3d_terrain_point_data (raw->position.x, raw->position.z, &raw->terrain_info);

			raw->position.y = max (raw->position.y, terrain_y + CAMERA_MIN_HEIGHT_ABOVE_GROUND);

			if (raw->position.y < (terrain_y + 10.0))
			{
				exit_game_function (NULL);

				eject_fader = 1.0;
			}
			else if (raw->position.y < (terrain_y + 30.0))
			{
				eject_fader = ((terrain_y + 30.0) - raw->position.y) * (1.0 / 20.0);

				eject_fader = bound (eject_fader, 0.0, 1.0);
			}
		}
		else
		{
			exit_game_function (NULL);

			eject_fader = 1.0;
		}

		//
		// motion vector
		//

		get_local_entity_vec3d (ejected_pilot, VEC3D_TYPE_MOTION_VECTOR, &raw->motion_vector);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
