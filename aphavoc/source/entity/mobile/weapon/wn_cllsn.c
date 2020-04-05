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

#define DEBUG_MODULE	0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define COLLISION_THRESHOLD	(5.0)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int collision_test_weapon_with_given_target (entity *weapon, entity *target, vec3d *weapon_old_position, vec3d *weapon_new_position)
{
	float
		range,
		weapon_velocity,
		time_to_impact,
		sqr_velocity;

	vec3d
		*target_position = nullptr,
		*target_motion_vector = nullptr,
		target_old_position,
		target_new_position,
		weapon_intercept_point,
		target_intercept_point;

	ASSERT (weapon);

	ASSERT (target);

	ASSERT (weapon_old_position);

	ASSERT (weapon_new_position);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	//
	// approximate time to impact (uses the target position rather than the intercept point)
	//

	target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

	range = get_approx_3d_range (target_position, weapon_new_position);

	weapon_velocity = get_local_entity_float_value (weapon, FLOAT_TYPE_VELOCITY);

	time_to_impact = range / max (weapon_velocity, 1.0f);

	//
	// only proceed if close to impact
	//

	if (time_to_impact > 0.5)
	{
		return (FALSE);
	}

	if (get_local_entity_int_value (target, INT_TYPE_COLLISION_TEST_MOBILE))
	{
		////////////////////////////////////////
		//
		// MOBILE TARGET
		//
		////////////////////////////////////////

		target_motion_vector = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_MOTION_VECTOR);

		sqr_velocity =
		(
			target_motion_vector->x * target_motion_vector->x +
			target_motion_vector->y * target_motion_vector->y +
			target_motion_vector->z * target_motion_vector->z
		);

		if (sqr_velocity > 1.0)
		{
			//
			// moving mobile
			//

			if (get_local_entity_int_value (target, INT_TYPE_UPDATED))
			{
				get_local_entity_target_point (target, &target_new_position);

				target_old_position.x = target_new_position.x - target_motion_vector->x * get_delta_time ();
				target_old_position.y = target_new_position.y - target_motion_vector->y * get_delta_time ();
				target_old_position.z = target_new_position.z - target_motion_vector->z * get_delta_time ();
			}
			else
			{
				get_local_entity_target_point (target, &target_old_position);

				target_new_position.x = target_old_position.x + target_motion_vector->x * get_delta_time ();
				target_new_position.y = target_old_position.y + target_motion_vector->y * get_delta_time ();
				target_new_position.z = target_old_position.z + target_motion_vector->z * get_delta_time ();
			}

			if (get_3d_vector_cube_cube_intersect (weapon_old_position, weapon_new_position, &target_old_position, &target_new_position))
			{
				line_line_3d_intercept
				(
					weapon_old_position,
					weapon_new_position,
					&target_old_position,
					&target_new_position,
					&weapon_intercept_point,
					&target_intercept_point
				);
				
				range = get_3d_range (&weapon_intercept_point, &target_intercept_point);

				if (range < COLLISION_THRESHOLD)
				{
					*weapon_new_position = weapon_intercept_point;

					return (TRUE);
				}
			}
		}
		else
		{
			//
			// stationary mobile
			//

			get_local_entity_target_point (target, &target_new_position);

			range = get_3d_perp_dist_of_point_from_line (weapon_old_position, weapon_new_position, &target_new_position, &weapon_intercept_point);

			if (range < COLLISION_THRESHOLD)
			{
				*weapon_new_position = weapon_intercept_point;

				return (TRUE);
			}
		}
	}
	else if (get_local_entity_int_value (target, INT_TYPE_COLLISION_TEST_FIXED))
	{
		////////////////////////////////////////
		//
		// FIXED TARGET
		//
		////////////////////////////////////////

		get_local_entity_target_point (target, &target_new_position);

		range = get_3d_perp_dist_of_point_from_line (weapon_old_position, weapon_new_position, &target_new_position, &weapon_intercept_point);

		if (range < COLLISION_THRESHOLD)
		{
			*weapon_new_position = weapon_intercept_point;

			return (TRUE);
		}
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *collision_test_weapon_with_any_target (entity *weapon, vec3d *weapon_old_position, vec3d *weapon_new_position)
{
	entity
		*launcher = nullptr,
		*collision_entity = nullptr;

	vec3d
		weapon_intercept_point,
		face_normal;

	ASSERT (weapon);

	ASSERT (weapon_old_position);

	ASSERT (weapon_new_position);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	launcher = get_local_entity_parent (weapon, LIST_TYPE_LAUNCHED_WEAPON);

	collision_entity = get_line_of_sight_collision_entity (launcher, NULL, weapon_old_position, weapon_new_position, &weapon_intercept_point, &face_normal);

	if (collision_entity)
	{
		*weapon_new_position = weapon_intercept_point;
	}

	return (collision_entity);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int collision_test_weapon_with_trees (vec3d *weapon_old_position, vec3d *weapon_new_position)
{
	int
		hit_tree;

	vec3d
		intercept_point,
		face_normal;

	ASSERT (weapon_old_position);

	ASSERT (weapon_new_position);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	hit_tree = get_line_of_sight_collision_tree (weapon_old_position, weapon_new_position, &intercept_point, &face_normal, FALSE, TRUE);

	if (hit_tree)
	{
		*weapon_new_position = intercept_point;
	}

	return (hit_tree);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_local_entity_armour_thickness (entity *target, entity *weapon)
{
	float
		armor_thickness,
		result = 0;

	entity_sub_types
		sub_type;

	ASSERT (target);

	ASSERT (weapon);

	ASSERT (get_local_entity_int_value (weapon, INT_TYPE_IDENTIFY_WEAPON));

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	// get game difficulty level (use player's own level)

	{
		game_difficulty_settings
			difficulty;

		entity
			*launcher = nullptr,
			*pilot = nullptr;

		launcher = get_local_entity_parent (weapon, LIST_TYPE_LAUNCHED_WEAPON);

		if (launcher)
		{
			if (get_local_entity_int_value (launcher, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
			{
				pilot = get_local_entity_first_child (launcher, LIST_TYPE_AIRCREW);

				if (pilot)
				{
					difficulty = (game_difficulty_settings) get_local_entity_int_value (pilot, INT_TYPE_DIFFICULTY_LEVEL);

					if (difficulty == GAME_DIFFICULTY_EASY)
					{
						return (0.1);
					}
				}
			}
		}
	}

	// get armour thickness

	armor_thickness = (float) get_local_entity_int_value (target, INT_TYPE_ARMOR_LEVEL);

	ASSERT(armor_thickness);
	
	if (get_local_entity_int_value (target, INT_TYPE_IDENTIFY_VEHICLE) ||
			get_local_entity_int_value (target, INT_TYPE_IDENTIFY_AIRCRAFT))
	{
		float
			front_armor,
			rear_armor,
			side_armor,
			top_armor,
			norm;
		vec3d
			impact_vector,
			*target_position = nullptr,
			*weapon_position = nullptr;
		matrix3x3
			*target_attitude = nullptr;

		
		if (get_local_entity_int_value (target, INT_TYPE_IDENTIFY_VEHICLE))
		{
			sub_type = get_local_entity_int_value (target, INT_TYPE_ENTITY_SUB_TYPE);

			front_armor = vehicle_database[sub_type].armour_front;
			rear_armor = vehicle_database[sub_type].armour_rear;
			side_armor = vehicle_database[sub_type].armour_side;
			top_armor = (rear_armor + side_armor) / 3.0;
		}
		else
		{
			front_armor = 1;
			rear_armor = 0.25;
			side_armor = 0.75;
			top_armor = 0.33;
		}
		
		target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);
		weapon_position = get_local_entity_vec3d_ptr (weapon, VEC3D_TYPE_POSITION);
		target_attitude = get_local_entity_attitude_matrix_ptr (target);
		
		impact_vector.x = weapon_position->x - target_position->x;
		impact_vector.y = weapon_position->y - target_position->y;
		impact_vector.z = weapon_position->z - target_position->z;
		
		multiply_matrix3x3_vec3d(&impact_vector, *target_attitude, &impact_vector);
		
		norm = fabs(impact_vector.x) + fabs(impact_vector.y) + fabs(impact_vector.z);
		
		impact_vector.x /= norm;
		impact_vector.y /= norm;
		impact_vector.z /= norm;

		if (impact_vector.x >= 0)
			result += side_armor * impact_vector.x;
		else
			result -= side_armor * impact_vector.x;
		
		if (impact_vector.y >= 0)
			result += top_armor * impact_vector.y;
		else
			result -= top_armor * impact_vector.y;
		
		if (impact_vector.z >= 0)
			result += front_armor * impact_vector.z;
		else
			result -= rear_armor * impact_vector.z;
		
		ASSERT(result);
		
		armor_thickness *= result;
		
		#if DEBUG_MODULE
		debug_log("WN_COLLSN: armor: side %f, top %f, front %f, result %f, armour_thickness %f", impact_vector.x, impact_vector.y, impact_vector.z, result, armor_thickness);
		#endif
	}
	
//	{
//		float
//			target_zvx,
//			target_zvz,
//			weapon_zvx,
//			weapon_zvz,
//			cos_theta,
//			theta;
//
//		matrix3x3
//			*target_attitude,
//			*weapon_attitude;
//
//		target_attitude = get_local_entity_attitude_matrix_ptr (target);
//		weapon_attitude = get_local_entity_attitude_matrix_ptr (weapon);
//
//		target_zvx = (*target_attitude)[2][0];
//		target_zvz = (*target_attitude)[2][2];
//		weapon_zvx = -(*weapon_attitude)[2][0];
//		weapon_zvz = -(*weapon_attitude)[2][2];
//
//		cos_theta = (target_zvx * weapon_zvx) + (target_zvz * weapon_zvz);
//
//		cos_theta = bound (cos_theta, -1.0, 1.0);
//
//		theta = acos (cos_theta);
//
//		if (theta <= rad (45.0))
//		{
//			armour_thickness *= vehicle_database[sub_type].armour_front;
//		}
//		else if (theta <= rad (135.0))
//		{
//			armour_thickness *= vehicle_database[sub_type].armour_side;
//		}
//		else
//		{
//			armour_thickness *= vehicle_database[sub_type].armour_rear;
//		}
//	}

	return (armor_thickness);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
