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

static void set_attack_guide_move_six_position (entity *en);

static void set_attack_guide_move_circle_position (entity *en);

static void set_attack_guide_fire_intercept_position (entity *en);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_air_to_air_attack_guide (entity *en, entity *aggressor, entity *target)
{
	//
	// calculate FIRE position
	//
	
	if (get_local_entity_int_value (aggressor, INT_TYPE_WEAPONS_HOLD))
	{
		debug_log ("AA_ATTCK: Aborting attack - weapons hold (initialise)");

		delete_group_member_from_engage_guide (aggressor, en, FALSE);

		return;
	}
	
	if (attack_guide_find_best_weapon (en))
	{
		set_attack_guide_fire_intercept_position (en);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void attack_guide_move_six_reached (entity *en)
{
	entity
		*wp,
		*task,
		*aggressor,
		*target;

	get_local_guide_entity_pointers (en, &aggressor, &wp, &task, &target);

	if (get_local_entity_int_value (aggressor, INT_TYPE_WEAPONS_HOLD))
	{
		debug_log ("AA_ATTCK: Aborting attack - weapons hold (move six)");

		delete_group_member_from_engage_guide (aggressor, en, FALSE);

		return;
	}
	
	//
	// check weapon
	//

	if (attack_guide_find_best_weapon (en))
	{
		set_attack_guide_fire_intercept_position (en);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void attack_guide_move_circle_reached (entity *en)
{
	entity
		*wp,
		*task,
		*aggressor,
		*target;

	get_local_guide_entity_pointers (en, &aggressor, &wp, &task, &target);

	if (get_local_entity_int_value (aggressor, INT_TYPE_WEAPONS_HOLD))
	{
		debug_log ("AA_ATTCK: Aborting attack - weapons hold (move circle)");

		delete_group_member_from_engage_guide (aggressor, en, FALSE);

		return;
	}
	
	//
	// check weapon
	//

	if (attack_guide_find_best_weapon (en))
	{
		set_attack_guide_fire_intercept_position (en);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void attack_guide_fire_intercept_reached (entity *en)
{
	entity
		*wp,
		*task,
		*aggressor,
		*target;

	entity_sub_types
		selected_weapon;

	vec3d
		position,
		*weapon_vector,
		*weapon_to_target_vector;

	float
		distance,
		terrain_elevation,
		launch_angle_error;
		
	get_local_guide_entity_pointers (en, &aggressor, &wp, &task, &target);

	if (get_local_entity_int_value (aggressor, INT_TYPE_WEAPONS_HOLD))
	{
		debug_log ("AA_ATTCK: Aborting attack - weapons hold (fire intercept)");

		delete_group_member_from_engage_guide (aggressor, en, FALSE);

		return;
	}
	
	//
	// Check if too close
	//

	if (get_local_entity_type (aggressor) == ENTITY_TYPE_FIXED_WING)
	{
		if (get_local_entity_float_value (aggressor, FLOAT_TYPE_DISTANCE) < 400.0)
		{
			//
			// set MOVE SIX position
			//

			set_attack_guide_move_six_position (en);

			return;
		}
	}
	else
	{
		if (get_local_entity_float_value (aggressor, FLOAT_TYPE_DISTANCE) < 200.0)
		{
			//
			// set MOVE CIRCLE position
			//

			set_attack_guide_move_circle_position (en);

			return;
		}
	}

	//
	// check weapon vector
	//

	selected_weapon = get_local_entity_int_value (aggressor, INT_TYPE_SELECTED_WEAPON);

	ASSERT (selected_weapon != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON);

	if (get_local_entity_int_value (aggressor, INT_TYPE_WEAPON_AND_TARGET_VECTORS_VALID))
	{
		weapon_vector = get_local_entity_vec3d_ptr (aggressor, VEC3D_TYPE_WEAPON_VECTOR);

		ASSERT (weapon_vector);

		//
		// Check launch angle error
		//
		
		weapon_to_target_vector = get_local_entity_vec3d_ptr (aggressor, VEC3D_TYPE_WEAPON_TO_TARGET_VECTOR);

		ASSERT (weapon_to_target_vector);

		launch_angle_error = acos (get_3d_unit_vector_dot_product (weapon_vector, weapon_to_target_vector));

		if (fabs (launch_angle_error) > weapon_database[selected_weapon].max_launch_angle_error)
		{
			return;
		}

		//
		// Check firing into ground
		//

		if (get_local_entity_int_value (aggressor, INT_TYPE_IDENTIFY_HELICOPTER))
		{
			get_local_entity_vec3d (aggressor, VEC3D_TYPE_POSITION, &position);
	
			distance = 120.0;
	
			position.x += (distance * weapon_vector->x);
			position.y += (distance * weapon_vector->y);
			position.z += (distance * weapon_vector->z);
	
			terrain_elevation = get_3d_terrain_elevation (position.x, position.z);
	
			if (position.y < terrain_elevation)
			{
				return;
			}
		}
	}
	else
	{
		return;
	}

	//
	// Check target altitude
	//
	{
		float
			min_alt,
			altitude;

		int
			seed;

		altitude = get_local_entity_float_value (target, FLOAT_TYPE_RADAR_ALTITUDE);

		min_alt = 10.0;

		seed = get_client_server_entity_random_number_seed (aggressor);

		min_alt *= (1.0 + (0.5 * frand1x (&seed)));

		if (altitude < min_alt) 
		{
			return;
		}
	}

	//
	// Fire Weapon
	//

	aircraft_fire_weapon (aggressor, AIRCRAFT_FIRE_CHECK_ALL);

	//
	// check weapon
	//

	if (attack_guide_find_best_weapon (en))
	{
		if (get_local_entity_type (aggressor) == ENTITY_TYPE_FIXED_WING)
		{
			//
			// set MOVE SIX position
			//

			set_attack_guide_move_six_position (en);
		}
		else
		{
			//
			// set MOVE CIRCLE position
			//

			set_attack_guide_move_circle_position (en);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_attack_guide_move_six_position (entity *en)
{
	float
		weapon_effective_range;

	vec3d
		*target_pos,
		*target_zv,
		position;

	entity
		*wp,
		*task,
		*aggressor,
		*target;

	entity_sub_types
		selected_weapon;

	set_client_server_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_GUIDE_ATTACK_AA_MOVE_SIX);

	get_local_guide_entity_pointers (en, &aggressor, &wp, &task, &target);

	ASSERT (get_local_entity_type (aggressor) == ENTITY_TYPE_FIXED_WING);

	//
	// find aggressors selected weapon, and it's effective range
	//
	
	selected_weapon = get_local_entity_int_value (aggressor, INT_TYPE_SELECTED_WEAPON);

	ASSERT (selected_weapon != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON);
	
	weapon_effective_range = weapon_database [selected_weapon].effective_range;

	//
	// calculate position of targets "six"
	//

	target_pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

	target_zv = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_ZV);

	ASSERT (target_zv);

	position.x = target_pos->x - (target_zv->x * weapon_effective_range);
	position.z = target_pos->z - (target_zv->z * weapon_effective_range);

	bound_position_to_adjusted_map_volume (&position);

	position.y = get_3d_terrain_elevation (position.x, position.z) + get_local_entity_float_value (aggressor, FLOAT_TYPE_CRUISE_ALTITUDE);

	set_client_server_guide_entity_new_position (en, &position, NULL);

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_RADIUS, TRUE, get_local_entity_waypoint_database_reached_radius_value (wp, aggressor));

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_HEADING, FALSE, 0.0);

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_WEAPON_VECTOR, FALSE, 0.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_attack_guide_move_circle_position (entity *en)
{
	float
		distance;

	vec3d
		*target_pos,
		*aggressor_pos,
		*target_mv,
		position;

	vec2d		
		direction;

	entity
		*wp,
		*task,
		*aggressor,
		*target;

	set_client_server_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_GUIDE_ATTACK_AA_MOVE_CIRCLE);

	get_local_guide_entity_pointers (en, &aggressor, &wp, &task, &target);

	ASSERT (get_local_entity_type (aggressor) == ENTITY_TYPE_HELICOPTER);

	//
	// calculate vector of aggressor to target
	//

	target_pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

	aggressor_pos = get_local_entity_vec3d_ptr (aggressor, VEC3D_TYPE_POSITION);

	direction.x = aggressor_pos->x - target_pos->x;
	direction.y = aggressor_pos->z - target_pos->z;

	distance = normalise_any_2d_vector (&direction);
	
	//
	// calculate guide position 
	//

	rotate_2d_vector (&direction, rad (10.0f));

	position.x = target_pos->x + (direction.x * distance);
	position.z = target_pos->z + (direction.y * distance);

	//
	// account for target movement
	//

	target_mv = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_MOTION_VECTOR);

	ASSERT (target_mv);

	position.x += (target_mv->x * 5.0);
	position.z += (target_mv->z * 5.0);

	bound_position_to_adjusted_map_volume (&position);

	position.y = get_3d_terrain_elevation (position.x, position.z) + get_local_entity_float_value (aggressor, FLOAT_TYPE_ATTACK_ALTITUDE);

	set_client_server_guide_entity_new_position (en, &position, NULL);

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_RADIUS, TRUE, 50.0);

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_HEADING, FALSE, 0.0);

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_WEAPON_VECTOR, FALSE, 0.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_attack_guide_fire_intercept_position (entity *en)
{
	entity_sub_types
		selected_weapon;

	float
		weapon_effective_range,
		target_range,
		lead_distance,
		time,
		radius;

	vec3d
		position,
		*target_pos,
		*aggressor_pos;
		
	entity
		*wp,
		*task,
		*aggressor,
		*target;

	set_client_server_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_GUIDE_ATTACK_AA_FIRE_INTERCEPT);

	get_local_guide_entity_pointers (en, &aggressor, &wp, &task, &target);

	//
	// find aggressors selected weapon, and it's effective range
	//
	
	selected_weapon = get_local_entity_int_value (aggressor, INT_TYPE_SELECTED_WEAPON);

	ASSERT (selected_weapon != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON);
	
	weapon_effective_range = weapon_database [selected_weapon].effective_range;

	//
	// calculate required distance of guide from target 
	//

	radius = weapon_effective_range;

	aggressor_pos = get_local_entity_vec3d_ptr (aggressor, VEC3D_TYPE_POSITION);

	target_pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

	target_range = get_3d_range (aggressor_pos, target_pos);

	time = target_range / weapon_database [selected_weapon].cruise_velocity;

	lead_distance = time * get_local_entity_float_value (aggressor, FLOAT_TYPE_VELOCITY);

	lead_distance = max (lead_distance, 0.5f * KILOMETRE);

	//
	// calculate guide position (relative to target)
	//

	position.x = 0.0;
	position.y = 0.0;
	position.z = lead_distance;

	set_client_server_guide_entity_new_position (en, &position, target);

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_RADIUS, TRUE, radius);

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_HEADING, FALSE, 0.0);

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_WEAPON_VECTOR, FALSE, 0.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

