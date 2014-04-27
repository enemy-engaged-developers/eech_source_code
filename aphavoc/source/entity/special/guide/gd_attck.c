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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_attack_guide (entity *en)
{
	entity
		*task,
		*aggressor,
		*target;

	ASSERT (en);

	task = get_local_entity_parent (en, LIST_TYPE_GUIDE);

	ASSERT (task);

	ASSERT (get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_TASK_ENGAGE);

	aggressor = (entity *) get_local_entity_ptr_value (en, PTR_TYPE_TASK_LEADER);

	ASSERT (aggressor);

	if (get_local_entity_float_value (aggressor, FLOAT_TYPE_WEAPON_BURST_TIMER) > 0.0)
	{
		return;
	}

	target = get_local_entity_parent (task, LIST_TYPE_TASK_DEPENDENT);

	ASSERT (target);

	if (!get_local_entity_int_value (aggressor, INT_TYPE_IDENTIFY_AIRCRAFT))
	{
		//
		// Surface-Air & Surface-Surface
		//

		entity_sub_types
			best_weapon;

		//
		// find best weapon for target
		//

		best_weapon = get_best_weapon_for_target (aggressor, target, BEST_WEAPON_CRITERIA_ALL);

		set_client_server_entity_int_value (aggressor, INT_TYPE_SELECTED_WEAPON, best_weapon);

		return;
	}
	else
	{
		//
		// Air-Air & Air-Surface
		//

		if (get_local_entity_int_value (target, INT_TYPE_AIRBORNE_AIRCRAFT))
		{
			initialise_air_to_air_attack_guide (en, aggressor, target);
		}
		else
		{
			initialise_air_to_ground_attack_guide (en, aggressor, target);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void calculate_attack_guide_intercept_point (entity *aggressor, entity *target, int selected_weapon, vec3d *ip)
{
	float
		time,
		distance,
		target_speed,
		weapon_speed;

	int
		object_index;

	ASSERT (aggressor);

	ASSERT (target);

	ASSERT (ip);

	//
	// Also uses target point NULL on the object to define offset
	//

	object_index = get_local_entity_int_value (target, INT_TYPE_OBJECT_3D_SHAPE);

	if (object_index != OBJECT_3D_INVALID_OBJECT_INDEX)
	{
		ip->x = target_point_offsets [object_index].x;
		ip->y = target_point_offsets [object_index].y;
		ip->z = target_point_offsets [object_index].z;
	}
	else
	{
		ip->x = 0.0;
		ip->y = 0.0;
		ip->z = 0.0;
	}

	//
	// check for simple case if target not moving
	//

	target_speed = get_local_entity_float_value (target, FLOAT_TYPE_VELOCITY);

	//
	// Assume distance between target and aggressor at fire position will be the weapons effective range
	//

	distance = weapon_database [selected_weapon].effective_range;

	// adjust for weapon drop
	if (weapon_database [selected_weapon].guidance_type == WEAPON_GUIDANCE_TYPE_NONE)
	{
		vec3d*
			aggressor_pos = get_local_entity_vec3d_ptr (aggressor, VEC3D_TYPE_POSITION);

		float
			velocity = get_local_entity_float_value (aggressor, FLOAT_TYPE_CRUISE_VELOCITY),
			burst_length = weapon_database[selected_weapon].burst_duration,
			// use distance in the middle of the salve. First rounds will hit short, last long, but should bracket target nicely
			mid_salvo_distance = distance - max(250.0, (0.5 * velocity * burst_length)),
			aiming_pitch,
			height_diff = aggressor_pos->y - ip->y,
			// current pitch from aggressor to target, it won't be the same at firing point, but close enough
			pitch = -atan(height_diff / get_2d_range(aggressor_pos, get_local_entity_vec3d_ptr(target, VEC3D_TYPE_POSITION))),
			tof;

		if (get_ballistic_pitch_deflection(selected_weapon, mid_salvo_distance, pitch, &aiming_pitch, &tof, FALSE, TRUE, get_local_entity_float_value (aggressor, FLOAT_TYPE_VELOCITY)))
		{
			float
				projectile_drop_angle = aiming_pitch - pitch,  // aiming pitch is absolute, but we need to figure out how much higher we need to aim
				projectile_drop = tan(projectile_drop_angle) * mid_salvo_distance * cos(pitch);  // distance projectile will drop, so aim this much above target

			ip->y += projectile_drop;
		}
	}

	if (target_speed == 0.0)
	{
		return;
	}

	//
	// Find time taken for weapon to travel this distance
	//

	weapon_speed = weapon_database [selected_weapon].cruise_velocity;

	ASSERT (weapon_speed > 0.0);

	time = distance / weapon_speed;

	//
	// calculate lead distance
	//

	ip->z += target_speed * time;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int attack_guide_find_best_weapon (entity *en)
{
	entity
		*target,
		*aggressor;

	entity_sub_types
		best_weapon;

	//
	// check weapon
	//

	aggressor = (entity *) get_local_entity_ptr_value (en, PTR_TYPE_TASK_LEADER);

	ASSERT (aggressor);

	if (get_local_entity_float_value (aggressor, FLOAT_TYPE_WEAPON_BURST_TIMER) > 0.0)
	{
		return FALSE;
	}

	target = get_local_entity_parent (aggressor, LIST_TYPE_TARGET);

	ASSERT (target);

	best_weapon = get_best_weapon_for_target (aggressor, target, BEST_WEAPON_RANGE_CHECK);

	if (best_weapon == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
	{
		//
		// No suitable weapon at current range
		//

		best_weapon = get_best_weapon_for_target (aggressor, target, BEST_WEAPON_CRITERIA_MINIMAL);

		if (best_weapon == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
		{
			//
			// Entity is not capable of destroying the target - abort the attack
			//

			delete_group_member_from_engage_guide (aggressor, en, TRUE);

			return FALSE;
		}
	}

	set_client_server_entity_int_value (aggressor, INT_TYPE_SELECTED_WEAPON, best_weapon);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

