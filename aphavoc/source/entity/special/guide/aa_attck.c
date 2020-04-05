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
		ASSERT(get_local_entity_ptr_value (en, PTR_TYPE_TASK_LEADER));
		set_attack_guide_fire_intercept_position (en);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void attack_guide_move_six_reached (entity *en)
{
	entity
		*task = nullptr,
		*aggressor = nullptr,
		*target = nullptr;

	ASSERT(en);
	
	aggressor = (entity *) get_local_entity_ptr_value (en, PTR_TYPE_TASK_LEADER);
	ASSERT(aggressor);
	task = get_local_entity_parent (en, LIST_TYPE_GUIDE);
	ASSERT(task);
	target = get_local_entity_parent (task, LIST_TYPE_TASK_DEPENDENT);
	ASSERT(target);

	#if DEBUG_MODULE
		if (aggressor == get_external_view_entity ())
		{
			debug_log("AA_ATTCK: attack_guide_move_six_reached");
		}
	#endif

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
		ASSERT(get_local_entity_ptr_value (en, PTR_TYPE_TASK_LEADER));
		set_attack_guide_fire_intercept_position (en);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void attack_guide_move_circle_reached (entity *en)
{
	entity
		*task = nullptr,
		*aggressor = nullptr,
		*target = nullptr;

	ASSERT(en);
	
	aggressor = (entity *) get_local_entity_ptr_value (en, PTR_TYPE_TASK_LEADER);
	ASSERT(aggressor);
	task = get_local_entity_parent (en, LIST_TYPE_GUIDE);
	ASSERT(task);
	target = get_local_entity_parent (task, LIST_TYPE_TASK_DEPENDENT);
	ASSERT(target);

	#if DEBUG_MODULE
		if (aggressor == get_external_view_entity ())
		{
			debug_log("AA_ATTCK: attack_guide_move_circle_reached");
		}
	#endif

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
		ASSERT(get_local_entity_ptr_value (en, PTR_TYPE_TASK_LEADER));
		set_attack_guide_fire_intercept_position (en);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void attack_guide_fire_intercept_reached (entity *en)
{
	entity
		*task = nullptr,
		*aggressor = nullptr,
		*target = nullptr;

	vec3d
		*target_pos = nullptr,
		*aggressor_pos = nullptr;
		
	ASSERT(en);
	
	aggressor = (entity *) get_local_entity_ptr_value (en, PTR_TYPE_TASK_LEADER);
	ASSERT(aggressor);
	task = get_local_entity_parent (en, LIST_TYPE_GUIDE);
	ASSERT(task);
	target = get_local_entity_parent (task, LIST_TYPE_TASK_DEPENDENT);
	ASSERT(target);

	if (get_local_entity_float_value (aggressor, FLOAT_TYPE_WEAPON_BURST_TIMER) && get_local_entity_float_value (aggressor, FLOAT_TYPE_WEAPON_BURST_TIMER) < 0.2 && 
			attack_guide_find_best_weapon (en))
	{
		if (get_local_entity_type (aggressor) == ENTITY_TYPE_FIXED_WING)
			set_attack_guide_move_six_position (en);
		else
			set_attack_guide_move_circle_position (en);

		return;
	}	
	
	if (get_local_entity_int_value (aggressor, INT_TYPE_WEAPONS_HOLD))
	{
		#if DEBUG_MODULE
			if (aggressor == get_external_view_entity ())
			{
				debug_log ("AA_ATTCK: Aborting attack - weapons hold (fire intercept)");
			}
		#endif

		delete_group_member_from_engage_guide (aggressor, en, FALSE);

		return;
	}

	#if DEBUG_MODULE
		if (aggressor == get_external_view_entity ())
		{
			debug_log("AA_ATTCK: attack_guide_fire_intercept_reached");
		}
	#endif

	if (check_guided_missile_type_alive(aggressor))
	{
		#if DEBUG_MODULE
			if (aggressor == get_external_view_entity ())
			{
				debug_log("AA_ATTCK: abort attack_guide_fire_intercept, another missile is still alive");

			}
		#endif

		if (get_local_entity_type (aggressor) == ENTITY_TYPE_FIXED_WING)
			set_attack_guide_move_six_position (en);
		else
			set_attack_guide_move_circle_position (en);
		return;
	}

	aggressor_pos = get_local_entity_vec3d_ptr (aggressor, VEC3D_TYPE_POSITION);
	target_pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

	if (get_2d_range (aggressor_pos, target_pos) < (0.5 + 0.5 * frand1()) * (get_local_entity_type (aggressor) == ENTITY_TYPE_FIXED_WING ? 300 : 200)) // too close, move back
	{
		#if DEBUG_MODULE
			if (aggressor == get_external_view_entity ())
			{
				debug_log("AA_ATTCK: abort attack_guide_fire_intercept, too close to target");

			}
		#endif

		if (get_local_entity_type (aggressor) == ENTITY_TYPE_FIXED_WING)
			set_attack_guide_move_six_position (en);
		else
			set_attack_guide_move_circle_position (en);
		
		return;
	}

	// Fire Weapon

	if (!get_local_entity_float_value (aggressor, FLOAT_TYPE_WEAPON_BURST_TIMER))
	{
		if (aircraft_fire_weapon (aggressor, AIRCRAFT_FIRE_CHECK_ALL, TRUE) == AIRCRAFT_FIRE_OK)
		{
			if (!get_local_entity_float_value (aggressor, FLOAT_TYPE_WEAPON_BURST_TIMER) && attack_guide_find_best_weapon (en))
			{
				set_local_entity_float_value(aggressor, FLOAT_TYPE_WEAPON_LAUNCH_DELAY, 5.0);

				if (get_local_entity_type (aggressor) == ENTITY_TYPE_FIXED_WING)
					set_attack_guide_move_six_position (en);
				else
					set_attack_guide_move_circle_position (en);
			}
		}
		else if (get_local_entity_ptr_value (en, PTR_TYPE_TASK_LEADER)) // update intercept point if it's possible
			set_attack_guide_fire_intercept_position(en);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_attack_guide_move_six_position (entity *en)
{
	float
		weapon_effective_range,
		rand_value;

	vec3d
		*target_pos = nullptr,
		*aggressor_position = nullptr,
		*target_zv = nullptr,
		position;

	entity
		*wp = nullptr,
		*task = nullptr,
		*aggressor = nullptr,
		*target = nullptr;

	entity_sub_types
		selected_weapon;

	ASSERT(en);
	
	set_client_server_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_GUIDE_ATTACK_AA_MOVE_SIX);

	aggressor = (entity *) get_local_entity_ptr_value (en, PTR_TYPE_TASK_LEADER);
	ASSERT(aggressor);
	task = get_local_entity_parent (en, LIST_TYPE_GUIDE);
	ASSERT(task);
	target = get_local_entity_parent (task, LIST_TYPE_TASK_DEPENDENT);
	ASSERT(target);
	wp = get_local_entity_parent (en, LIST_TYPE_CURRENT_WAYPOINT);
	ASSERT (wp);

	ASSERT (get_local_entity_type (aggressor) == ENTITY_TYPE_FIXED_WING);

	//
	// find aggressors selected weapon, and it's effective range
	//
	
	selected_weapon = get_local_entity_int_value (aggressor, INT_TYPE_SELECTED_WEAPON);

	if (selected_weapon == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
	{
		delete_group_member_from_engage_guide (aggressor, en, FALSE);

		return;
	}
	
	weapon_effective_range = bound(weapon_database [selected_weapon].effective_range, 1000.0, 2000.0);

	//
	// calculate position of targets "six"
	//

	target_pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);
	aggressor_position = get_local_entity_vec3d_ptr (aggressor, VEC3D_TYPE_POSITION);
	
	target_zv = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_ZV);

	ASSERT (target_zv);

	position = *target_pos;
	
	do
	{
		rand_value = 0.5 + 0.5 * frand1();
			
		position.x -= rand_value * (target_zv->x * weapon_effective_range);
		position.z -= rand_value * (target_zv->z * weapon_effective_range);
	}
	while(get_2d_range(&position, aggressor_position) < weapon_effective_range);

	bound_position_to_adjusted_map_volume (&position);

	position.y = max(aggressor_position->y + 20.0 * sfrand1(), get_3d_terrain_elevation (position.x, position.z) + 0.25 * get_local_entity_float_value (aggressor, FLOAT_TYPE_ATTACK_ALTITUDE));

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
		*target_pos = nullptr,
		*aggressor_pos = nullptr,
		*target_mv = nullptr,
		position;

	vec2d		
		direction;

	entity
		*task = nullptr,
		*aggressor = nullptr,
		*target = nullptr;

	ASSERT(en);
	
	set_client_server_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_GUIDE_ATTACK_AA_MOVE_CIRCLE);

	aggressor = (entity *) get_local_entity_ptr_value (en, PTR_TYPE_TASK_LEADER);
	ASSERT(aggressor);
	task = get_local_entity_parent (en, LIST_TYPE_GUIDE);
	ASSERT(task);
	target = get_local_entity_parent (task, LIST_TYPE_TASK_DEPENDENT);
	ASSERT(target);

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

	if (distance >= 500)
		rotate_2d_vector (&direction, rad (10.0));
	else
		rotate_2d_vector (&direction, frand1() * rad (90.0));

	distance = max((0.5 + 0.4 * frand1()) * distance, 500.0);

	position.x = target_pos->x + (direction.x * distance);
	position.z = target_pos->z + (direction.y * distance);

	//
	// account for target movement
	//

	target_mv = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_MOTION_VECTOR);

	ASSERT (target_mv);

	position.x += (target_mv->x);
	position.z += (target_mv->z);

	bound_position_to_adjusted_map_volume (&position);

	position.y = max(get_3d_terrain_elevation (position.x, position.z) + get_local_entity_float_value (aggressor, FLOAT_TYPE_ATTACK_ALTITUDE), target_pos->y);
	
	#if DEBUG_MODULE
		if (aggressor == get_external_view_entity ())
		{
			debug_log("AA_ATTCK: set circle position");
		}
	#endif

	set_client_server_guide_entity_new_position (en, &position, NULL);

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_RADIUS, TRUE, 25.0);

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
		radius;

	vec3d
		position,
		*target_pos = nullptr,
		*aggressor_pos = nullptr;
		
	entity
		*task = nullptr,
		*aggressor = nullptr,
		*target = nullptr;

	ASSERT(en);
	
	set_client_server_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_GUIDE_ATTACK_AA_FIRE_INTERCEPT);

	aggressor = (entity *) get_local_entity_ptr_value (en, PTR_TYPE_TASK_LEADER);
	ASSERT(aggressor);
	task = get_local_entity_parent (en, LIST_TYPE_GUIDE);
	ASSERT(task);
	target = get_local_entity_parent (task, LIST_TYPE_TASK_DEPENDENT);
	ASSERT(target);

	//
	// find aggressors selected weapon, and it's effective range
	//
	
	selected_weapon = get_local_entity_int_value (aggressor, INT_TYPE_SELECTED_WEAPON);

	if (selected_weapon == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
	{
		delete_group_member_from_engage_guide (aggressor, en, FALSE);

		return;
	}
	
	weapon_effective_range = weapon_database [selected_weapon].effective_range;

	//
	// calculate required distance of guide from target 
	//

	radius = weapon_effective_range;

	aggressor_pos = get_local_entity_vec3d_ptr (aggressor, VEC3D_TYPE_POSITION);

	target_pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

	// calculate guide position (absolute)

	position = *target_pos;

	if (get_local_entity_int_value (aggressor, INT_TYPE_WEAPON_AND_TARGET_VECTORS_VALID))
		position = get_global_position_from_unit_vector(get_local_entity_vec3d_ptr (aggressor, VEC3D_TYPE_POSITION),
				get_local_entity_vec3d_ptr (aggressor, VEC3D_TYPE_WEAPON_TO_INTERCEPT_POINT_VECTOR),
				get_local_entity_float_value (aggressor, FLOAT_TYPE_WEAPON_TO_INTERCEPT_POINT_RANGE));

	if (weapon_database[selected_weapon].burst_duration)
		position.y -= 0.5 * (position.y - target_pos->y); // compensate aircraft inertness and velocity

	set_client_server_guide_entity_new_position (en, &position, NULL);

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_RADIUS, TRUE, radius);

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_HEADING, FALSE, 0.0);

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_WEAPON_VECTOR, FALSE, 0.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

