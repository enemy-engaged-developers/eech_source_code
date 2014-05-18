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
		*task,
		*aggressor,
		*target;

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
		*task,
		*aggressor,
		*target;

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
		*task,
		*aggressor,
		*target,
		*weapon;

	vec3d
		*target_pos,
		*aggressor_pos;
		
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

	weapon = get_local_entity_first_child (aggressor, LIST_TYPE_LAUNCHED_WEAPON);

	if (weapon)
	{
		weapon = get_local_entity_child_pred_circular(weapon, LIST_TYPE_LAUNCHED_WEAPON);

		while (weapon)
		{
			if(weapon_database[get_local_entity_int_value (weapon, INT_TYPE_ENTITY_SUB_TYPE)].guidance_type)
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

			weapon = get_local_entity_child_pred (weapon, LIST_TYPE_LAUNCHED_WEAPON);
		}
	}

	aggressor_pos = get_local_entity_vec3d_ptr (aggressor, VEC3D_TYPE_POSITION);
	target_pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

	if (get_3d_range (aggressor_pos, target_pos) < frand1() * (get_local_entity_type (aggressor) == ENTITY_TYPE_FIXED_WING ? 300 : 100)) // too close, move back
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
		set_client_server_entity_float_value(aggressor, FLOAT_TYPE_WEAPON_LAUNCH_DELAY, 5);

		if (aircraft_fire_weapon (aggressor, AIRCRAFT_FIRE_CHECK_ALL, TRUE) == AIRCRAFT_FIRE_OK)
		{
			if (!get_local_entity_float_value (aggressor, FLOAT_TYPE_WEAPON_BURST_TIMER) && attack_guide_find_best_weapon (en))
			{
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
		weapon_effective_range;

	vec3d
		*target_pos,
		*aggressor_position,
		*target_zv,
		position;

	entity
		*wp,
		*task,
		*aggressor,
		*target;

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

	ASSERT (selected_weapon != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON);
	
	weapon_effective_range = max(1000, weapon_database [selected_weapon].effective_range);

	//
	// calculate position of targets "six"
	//

	target_pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);
	aggressor_position = get_local_entity_vec3d_ptr (aggressor, VEC3D_TYPE_POSITION);
	
	target_zv = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_ZV);

	ASSERT (target_zv);

	position.x = target_pos->x - frand1() * (target_zv->x * weapon_effective_range);
	position.z = target_pos->z - frand1() * (target_zv->z * weapon_effective_range);

	bound_position_to_adjusted_map_volume (&position);

	position.y = get_3d_terrain_elevation (position.x, position.z) + min(aggressor_position->y, get_local_entity_float_value (aggressor, FLOAT_TYPE_CRUISE_ALTITUDE));

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
		*task,
		*aggressor,
		*target;

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

	if (distance >= 200)
		rotate_2d_vector (&direction, rad (10.0));
	else
		rotate_2d_vector (&direction, frand1() * rad (90.0));

	distance = max(frand1() * distance, 200);

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
		target_range,
		lead_distance,
		time,
		radius,
		aiming_pitch;

	vec3d
		position,
		*target_pos,
		*aggressor_pos;
		
	entity
		*task,
		*aggressor,
		*target;

	matrix3x3
		attitude;

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

	ASSERT (selected_weapon != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON);
	
	weapon_effective_range = weapon_database [selected_weapon].effective_range;

	//
	// calculate required distance of guide from target 
	//

	radius = weapon_effective_range;

	aggressor_pos = get_local_entity_vec3d_ptr (aggressor, VEC3D_TYPE_POSITION);

	target_pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

	target_range = get_3d_range (aggressor_pos, target_pos);

	//
	// calculate guide position (relative to target)
	//

	if (weapon_database [selected_weapon].guidance_type)
	{
		time = target_range / (0.75 * weapon_database[selected_weapon].cruise_velocity);
		lead_distance = min (time * get_local_entity_float_value (target, FLOAT_TYPE_VELOCITY), 500);

		position.x = 0.0;
		position.y = 0.0;
		position.z = lead_distance;
	}
	else
	{
//		get_ballistic_pitch_deflection(selected_weapon, target_range, - asin((aggressor_pos->y - target_pos->y) / target_range), &aiming_pitch, &time, FALSE, TRUE, weapon_database [selected_weapon].acquire_parent_forward_velocity * get_local_entity_float_value (aggressor, FLOAT_TYPE_VELOCITY));
		get_lead_and_ballistic_intercept_point_and_angle_of_projection (target_pos, selected_weapon, weapon_database[selected_weapon].acquire_parent_forward_velocity * get_local_entity_float_value (aggressor, FLOAT_TYPE_VELOCITY), aggressor, target, &position, &aiming_pitch, &time);

		position.x -= target_pos->x;
		position.y -= target_pos->y;
		position.z -= target_pos->z;
		
		get_local_entity_attitude_matrix (target, attitude);
		multiply_matrix3x3_vec3d (&position, attitude, &position);
	}

	set_client_server_guide_entity_new_position (en, &position, target);

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_RADIUS, TRUE, radius);

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_HEADING, FALSE, 0.0);

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_WEAPON_VECTOR, FALSE, 0.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

