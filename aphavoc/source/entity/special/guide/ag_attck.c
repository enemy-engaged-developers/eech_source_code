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

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define FIXED_WING_APPROACH_TIME		10.0

#define FIXED_WING_CLIMB_TIME			10.0

#define FIXED_WING_DIVE_TIME			5.0

#define FIXED_WING_EGRESS_TIME		10.0

#define INITIAL_BOB_UP_DISTANCE		10.0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_attack_guide_approach_position (entity *en);

static void set_attack_guide_seek_cover_position (entity *en);

static void set_attack_guide_take_cover_position (entity *en);

static void set_attack_guide_climb_position (entity *en);

static void set_attack_guide_fire_position (entity *en);

static void set_attack_guide_disengage_position (entity *en);

static void set_attack_guide_egress_position (entity *en);

static void set_attack_guide_hasty_fire_position (entity *en);

static void set_attack_guide_hasty_take_cover_position (entity *en);

void set_attack_guide_dive_position (entity *en);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_air_to_ground_attack_guide (entity *en, entity *aggressor, entity *target)
{
	entity_sub_types
		best_weapon;

	if (get_local_entity_type (aggressor) == ENTITY_TYPE_HELICOPTER)
	{
//		if (get_local_entity_first_child (aggressor, LIST_TYPE_TARGET))
		{
			//
			// if the aggressor is a helicopter, and is being targeted - attempt to fire back rapidly and then look for cover
			//

			best_weapon = get_best_weapon_for_target (aggressor, target, BEST_WEAPON_RANGE_CHECK);

			if (best_weapon != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
			{
				set_client_server_entity_int_value (aggressor, INT_TYPE_SELECTED_WEAPON, best_weapon);

				set_attack_guide_hasty_fire_position (en);

				return;
			}
		}
	}

	//
	// find best weapon for target (approach ranges will be based on this)
	//

	best_weapon = get_best_weapon_for_target (aggressor, target, BEST_WEAPON_CRITERIA_MINIMAL);

	set_client_server_entity_int_value (aggressor, INT_TYPE_SELECTED_WEAPON, best_weapon);

	if (best_weapon == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
	{
		//
		// Entity is not capable of destroying the target
		//

		#ifdef DEBUG

		debug_fatal ("Entity %s incapable of destroying %s", get_local_entity_string (aggressor, STRING_TYPE_FULL_NAME), get_local_entity_string (target, STRING_TYPE_FULL_NAME));

		#endif

		return;
	}

	//
	// calculate APPROACH position
	//

	set_attack_guide_approach_position (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void attack_guide_approach_reached (entity *en)
{
	entity
		*aggressor;

	//
	// change guide type to SEEK_COVER (Helicopter) or CLIMB (Jet) and calculate new position
	//

	aggressor = get_local_entity_ptr_value (en, PTR_TYPE_TASK_LEADER);

	ASSERT (aggressor);

	switch (get_local_entity_type (aggressor))
	{
		case ENTITY_TYPE_HELICOPTER:
		{
			set_attack_guide_seek_cover_position (en);

			break;
		}
		case ENTITY_TYPE_FIXED_WING:
		{
			set_attack_guide_climb_position (en);

			break;
		}
		default:
		{
			debug_fatal ("GD_ATTCK: Invalid Entity Type %d", get_local_entity_type (aggressor));
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void attack_guide_seek_cover_reached (entity *en)
{
	//
	// search for cover
	//

	update_guide_seek_cover_results (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void attack_guide_fly_to_cover_reached (entity *en)
{

	//
	// change guide type to TAKE_COVER and calculate new position
	//

	set_attack_guide_take_cover_position (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void attack_guide_take_cover_reached (entity *en)
{
	entity
		*last_weapon,
		*group,
		*leader,
		*task,
		*wp,
		*target,
		*aggressor;

	entity_sub_types
		best_weapon,
		selected_weapon;

	get_local_guide_entity_pointers (en, &aggressor, &wp, &task, &target);

	group = get_local_entity_parent (en, LIST_TYPE_GUIDE_STACK);

	ASSERT (group);

	//
	// Wait if mobile is still firing
	//

	if (get_local_entity_float_value (aggressor, FLOAT_TYPE_WEAPON_BURST_TIMER) > 0.0)
	{
		return;
	}

	//
	// check weapon
	//

	best_weapon = get_best_weapon_for_target (aggressor, target, BEST_WEAPON_RANGE_CHECK);

	selected_weapon = get_local_entity_int_value (aggressor, INT_TYPE_SELECTED_WEAPON);

	if ((selected_weapon == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON) || (best_weapon != selected_weapon))
	{
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
			}
			else
			{
				//
				// Entity is capable of destroying the target, but must move to a different position
				//

				set_client_server_entity_int_value (aggressor, INT_TYPE_SELECTED_WEAPON, best_weapon);

				set_attack_guide_approach_position (en);
			}

			return;
		}
		else
		{
			//
			// found new suitable weapon at current range
			//

			set_client_server_entity_int_value (aggressor, INT_TYPE_SELECTED_WEAPON, best_weapon);
		}
	}

	//
	// wait if it still has guided AG missiles fired at the same target
	//

	last_weapon = get_local_entity_first_child (aggressor, LIST_TYPE_LAUNCHED_WEAPON);
	if (last_weapon
		&& (weapon_database[best_weapon].weapon_class == WEAPON_CLASS_AIR_TO_SURFACE
			|| weapon_database[best_weapon].weapon_class == WEAPON_CLASS_SURFACE_TO_SURFACE)
		&& weapon_database[best_weapon].guidance_type != WEAPON_GUIDANCE_TYPE_NONE
		&& get_local_entity_parent(last_weapon, LIST_TYPE_TARGET) == target)
	{
		return;
	}


	//
	// notify the group leader that the cover position has been reached
	//

	leader = get_local_entity_ptr_value (group, PTR_TYPE_GROUP_LEADER);

	ASSERT (leader);

	notify_local_entity (ENTITY_MESSAGE_GUIDE_COVER_POSITION_REACHED, leader, en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void attack_guide_proceed_to_fire_positon (entity *en)
{
	//
	// change guide type to FIRE and calculate new position
	//

	ASSERT (get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_TAKE_COVER);

	set_attack_guide_fire_position (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void attack_guide_climb_reached (entity *en)
{
	//
	// change guide type to DIVE and calculate new position
	//

	set_attack_guide_dive_position (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void attack_guide_dive_reached (entity *en)
{
	//
	// change guide type to FIRE and calculate new position
	//

	set_attack_guide_fire_position (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void attack_guide_fire_reached (entity *en)
{
	entity
		*aggressor;

	//
	// Fire Weapon
	// Jet - Change guide type to DISENGAGE
	// Helicopter - Move back to TAKE_COVER
	//

	aggressor = get_local_entity_ptr_value (en, PTR_TYPE_TASK_LEADER);

	ASSERT (aggressor);

	switch (get_local_entity_type (aggressor))
	{
		/////////////////////////////
		//
		case ENTITY_TYPE_HELICOPTER:
		//
		/////////////////////////////
		{
			switch (aircraft_fire_weapon (aggressor, AIRCRAFT_FIRE_CHECK_ALL))
			{
				case AIRCRAFT_FIRE_OK:
				{
					//
					// Aircraft fired weapon - move back to cover position
					//

					set_attack_guide_take_cover_position (en);

					break;
				}

				case AIRCRAFT_FIRE_WEAPON_SYSTEM_NOT_READY:
				{
					//
					// weapon system not ready - wait
					//

					break;
				}

				case AIRCRAFT_FIRE_NO_WEAPON:
				case AIRCRAFT_FIRE_NO_TARGET:
				{
					//
					// Aircraft has no suitable weapon / target - abort task
					//

					// (should never happen ?)

					break;
				}

				case AIRCRAFT_FIRE_NO_LOS:
				{
					//
					// no LOS - increase altitude of guide
					//

					vec3d
						position;

					float
						altitude,
						terrain_elevation;

					get_local_entity_vec3d (en, VEC3D_TYPE_GUIDE_POSITION, &position);

					position.y += 10.0;

					//
					// check position isn't too high
					//

					terrain_elevation = get_3d_terrain_elevation (position.x, position.z);

					altitude = position.y - terrain_elevation;

					if (altitude >= 100.0)
					{
						//
						// something wrong - e.g. target has moved - find another cover position
						//

						set_attack_guide_seek_cover_position (en);
					}
					else
					{
						set_client_server_guide_entity_new_position (en, &position, NULL);
					}

					break;
				}

				case AIRCRAFT_FIRE_SUPPRESSED:
				{
					//
					// suppress AI fire option selected - should never engage !
					//

					break;
				}
			}

			break;
		}

		/////////////////////////////
		//
		case ENTITY_TYPE_FIXED_WING:
		//
		/////////////////////////////
		{
			//
			// Must set the disengage position BEFORE firing the weapon, as firing may set selected weapon to NONE
			//

			set_attack_guide_disengage_position (en);

			aircraft_fire_weapon (aggressor, AIRCRAFT_FIRE_CHECK_ALL);

			break;
		}
		default:
		{
			debug_fatal ("GD_ATTCK: Invalid Entity Type %d", get_local_entity_type (aggressor));
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void attack_guide_disengage_reached (entity *en)
{
	//
	// Jet - Change guide type to EGRESS
	//

	set_attack_guide_egress_position (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void attack_guide_egress_reached (entity *en)
{
	entity_sub_types
		best_weapon;

	entity
		*task,
		*wp,
		*target,
		*aggressor;

	get_local_guide_entity_pointers (en, &aggressor, &wp, &task, &target);

	//
	// find best weapon for target (approach ranges will be based on this)
	//

	best_weapon = get_best_weapon_for_target (aggressor, target, BEST_WEAPON_CRITERIA_MINIMAL);

	set_client_server_entity_int_value (aggressor, INT_TYPE_SELECTED_WEAPON, best_weapon);

	if (best_weapon == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
	{
		//
		// Entity is not capable of destroying the target - abort the attack
		//

		delete_group_member_from_engage_guide (aggressor, en, TRUE);

		return;
	}

	//
	// Change guide type back to APPROACH
	//

	set_attack_guide_approach_position (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void attack_guide_hasty_fire_reached (entity *en)
{
	entity
		*aggressor,
		*target;

	aggressor = get_local_entity_ptr_value (en, PTR_TYPE_TASK_LEADER);

	ASSERT (aggressor);

	ASSERT (get_local_entity_type (aggressor) == ENTITY_TYPE_HELICOPTER);

	target = get_local_entity_parent (aggressor, LIST_TYPE_TARGET);

	ASSERT (target);

	//
	// Take a pot-shot
	//

	if (get_local_entity_int_value (aggressor, INT_TYPE_SELECTED_WEAPON) != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
	{
		if (!get_local_entity_int_value (aggressor, INT_TYPE_WEAPONS_HOLD))
		{
			if (check_entity_line_of_sight (aggressor, target, MOBILE_LOS_CHECK_ALL))
			{
				//
				// (as long as it is in "weapons free" mode)
				//

				aircraft_fire_weapon (aggressor, AIRCRAFT_FIRE_CHECK_ALL);
			}
		}
	}

	//
	// and duck down low
	//

	set_attack_guide_hasty_take_cover_position (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void attack_guide_hasty_take_cover_reached (entity *en)
{
	entity
		*task,
		*wp,
		*target,
		*aggressor;

	entity_sub_types
		best_weapon;

	get_local_guide_entity_pointers (en, &aggressor, &wp, &task, &target);

	//
	// check weapon
	//

	if (get_local_entity_int_value (aggressor, INT_TYPE_SELECTED_WEAPON) == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
	{
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

				return;
			}
		}

		set_client_server_entity_int_value (aggressor, INT_TYPE_SELECTED_WEAPON, best_weapon);
	}

	//
	// change guide type to SEEK_COVER
	//

	set_attack_guide_seek_cover_position (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_attack_guide_approach_position (entity *en)
{
	entity_sub_types
		selected_weapon;

	float
		weapon_max_range,
		weapon_min_range,
		weapon_effective_range,
		target_range,
		distance;

	vec3d
		*target_pos,
		*aggressor_pos,
		*cover_pos,
		direction,
		position;

	entity
		*wp,
		*task,
		*aggressor,
		*target;

	int
		force_new_position;

	set_client_server_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_APPROACH);

	get_local_guide_entity_pointers (en, &aggressor, &wp, &task, &target);

	//
	// find aggressors selected weapon, and it's max range
	//

	selected_weapon = get_local_entity_int_value (aggressor, INT_TYPE_SELECTED_WEAPON);

	ASSERT (selected_weapon != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON);

	weapon_max_range = weapon_database [selected_weapon].max_range * 0.9;

	weapon_min_range = weapon_database [selected_weapon].min_range;

	weapon_effective_range = weapon_database [selected_weapon].effective_range;

	//
	// calculate vector of aggressor to target
	//

	target_pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

	aggressor_pos = get_local_entity_vec3d_ptr (aggressor, VEC3D_TYPE_POSITION);

	direction.x = aggressor_pos->x - target_pos->x;
	direction.y = 0.0;
	direction.z = aggressor_pos->z - target_pos->z;

	target_range = normalise_any_3d_vector (&direction);

	if (target_range == 0.0)
	{
		//
		// safety check for case when aggressor is directly above target
		//

		direction.x = 0.0;
		direction.y = 0.0;
		direction.z = -1.0;
	}

	//
	// calculate required distance of guide from target
	//

	force_new_position = FALSE;

	switch (get_local_entity_type (aggressor))
	{
		case ENTITY_TYPE_HELICOPTER:
		{
			distance = bound (target_range, weapon_min_range, weapon_max_range);

			if (distance != target_range)
			{
				force_new_position = TRUE;
			}

			break;
		}
		case ENTITY_TYPE_FIXED_WING:
		{
			float
				time,
				velocity;

			velocity = get_local_entity_float_value (aggressor, FLOAT_TYPE_CRUISE_VELOCITY);

			ASSERT (velocity > 0.0);

			time = weapon_effective_range / velocity;

			time = time + FIXED_WING_APPROACH_TIME + FIXED_WING_CLIMB_TIME + FIXED_WING_DIVE_TIME;

			distance = velocity * time;

			break;
		}
		default:
		{
			debug_fatal ("GD_ATTCK: Invalid Entity Type %d", get_local_entity_type (aggressor));
		}
	}

	//
	// calculate guide position
	//

	position.x = target_pos->x + (direction.x * distance);
	position.y = 0.0;
	position.z = target_pos->z + (direction.z * distance);

	bound_position_to_adjusted_map_volume (&position);

	//
	// Check existing cover position to see if it is within range - if so then use it instead
	//

	cover_pos = get_local_entity_vec3d_ptr (aggressor, VEC3D_TYPE_COVER_POSITION);

	if ((!force_new_position) && (cover_pos) && (!check_zero_3d_vector (cover_pos)) && (get_2d_range (cover_pos, &position) < 20.0))
	{
		ASSERT (get_local_entity_type (aggressor) == ENTITY_TYPE_HELICOPTER);

		set_client_server_guide_entity_new_position (en, cover_pos, NULL);
	}
	else
	{
		position.y = get_3d_terrain_elevation (position.x, position.z) + get_local_entity_float_value (aggressor, FLOAT_TYPE_ATTACK_ALTITUDE);

		set_client_server_guide_entity_new_position (en, &position, NULL);
	}

	set_client_server_entity_float_value (en, FLOAT_TYPE_VELOCITY, get_local_entity_float_value (aggressor, FLOAT_TYPE_CRUISE_VELOCITY));

	//
	// set guide reached criteria
	//

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_ALTITUDE, FALSE, 0.0);

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_HEADING, FALSE, 0.0);

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_WEAPON_VECTOR, FALSE, 0.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_attack_guide_seek_cover_position (entity *en)
{
	entity
		*wp,
		*task,
		*aggressor,
		*target;

	vec3d
		position;

	float
		alt;

	set_client_server_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_SEEK_COVER);

	get_local_guide_entity_pointers (en, &aggressor, &wp, &task, &target);

	ASSERT (get_local_entity_type (aggressor) == ENTITY_TYPE_HELICOPTER);

	//
	// Helicopter remains at current location - just set heading criteria (so it's not spinning while it does the searching)
	//

	get_local_entity_vec3d (aggressor, VEC3D_TYPE_POSITION, &position);

	alt = get_3d_terrain_elevation (position.x, position.z) + get_local_entity_float_value (aggressor, FLOAT_TYPE_ATTACK_ALTITUDE);

	if (position.y > alt)
	{
		position.y = alt;

		set_client_server_guide_entity_new_position (en, &position, NULL);
	}

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_ALTITUDE, FALSE, 0.0);

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_HEADING, TRUE, rad (5.0));

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_WEAPON_VECTOR, FALSE, 0.0);

	//
	// reset seek data
	//

	reset_guide_seek_cover_results (en);

	//
	// Play Speech
	//

	play_client_server_wingman_message
	(
		aggressor,
		0.6,
		4.0,
		SPEECH_CATEGORY_ATTACKING_TARGETS,
		8.0,
		SPEECH_INTRODUCTION_ALWAYS,
		SPEECH_ARRAY_WINGMAN_MESSAGES,
		SPEECH_WINGMAN_SEEKING_COVER
	);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void attack_guide_no_cover_found (entity *en)
{
	entity
		*wp,
		*task,
		*aggressor,
		*target;

	vec3d
		*aggressor_pos,
		*target_pos,
		position;

	vec2d
		direction;

	float
		distance;

	get_local_guide_entity_pointers (en, &aggressor, &wp, &task, &target);

	target_pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

	aggressor_pos = get_local_entity_vec3d_ptr (aggressor, VEC3D_TYPE_POSITION);

	//
	// No cover found - Check Line Of Sight
	//

	if (check_position_line_of_sight (aggressor, target, aggressor_pos, target_pos, MOBILE_LOS_CHECK_ALL))
	{
		//
		// Full Line Of Sight - forget cover just fire from here
		//

		set_local_entity_vec3d (aggressor, VEC3D_TYPE_COVER_POSITION, aggressor_pos);

		set_attack_guide_fly_to_cover_position (en);

		return;
	}

	//
	// Set guide to seek cover, but rotate around the target
	//

	set_client_server_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_SEEK_COVER);

	ASSERT (get_local_entity_type (aggressor) == ENTITY_TYPE_HELICOPTER);

	//
	// calculate vector of aggressor to target
	//

	direction.x = aggressor_pos->x - target_pos->x;
	direction.y = aggressor_pos->z - target_pos->z;

	distance = normalise_any_2d_vector (&direction);

	//
	// Reduce distance (spiral around target)
	//

	distance *= 0.8;

	//
	// calculate guide position
	//

	rotate_2d_vector (&direction, rad (25.0));

	position.x = target_pos->x + (direction.x * distance);
	position.z = target_pos->z + (direction.y * distance);

	bound_position_to_adjusted_map_volume (&position);

	position.y = get_3d_terrain_elevation (position.x, position.z) + get_local_entity_float_value (aggressor, FLOAT_TYPE_ATTACK_ALTITUDE);

	set_client_server_guide_entity_new_position (en, &position, NULL);

	//
	// Set criteria
	//

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_ALTITUDE, FALSE, 0.0);

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_HEADING, TRUE, rad (5.0));

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_WEAPON_VECTOR, FALSE, 0.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_attack_guide_fly_to_cover_position (entity *en)
{
	entity
		*wp,
		*task,
		*aggressor,
		*target;

	vec3d
		*position;

	set_client_server_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_FLY_TO_COVER);

	get_local_guide_entity_pointers (en, &aggressor, &wp, &task, &target);

	set_client_server_entity_float_value (en, FLOAT_TYPE_VELOCITY, get_local_entity_float_value (aggressor, FLOAT_TYPE_CRUISE_VELOCITY));

	position = get_local_entity_vec3d_ptr (aggressor, VEC3D_TYPE_COVER_POSITION);

	set_client_server_guide_entity_new_position (en, position, NULL);

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_ALTITUDE, FALSE, 0.0);

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_HEADING, TRUE, rad (5.0));

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_WEAPON_VECTOR, FALSE, 0.0);

	//
	// Play Speech
	//

	play_client_server_wingman_message
	(
		aggressor,
		0.3,
		3.0,
		SPEECH_CATEGORY_ATTACKING_TARGETS,
		5.0,
		SPEECH_INTRODUCTION_ALWAYS,
		SPEECH_ARRAY_WINGMAN_MESSAGES,
		SPEECH_WINGMAN_FLYING_TO_COVER
	);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_attack_guide_take_cover_position (entity *en)
{
	vec3d
		*position;

	entity
		*wp,
		*task,
		*aggressor,
		*target;

	set_client_server_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_TAKE_COVER);

	get_local_guide_entity_pointers (en, &aggressor, &wp, &task, &target);

	ASSERT (get_local_entity_type (aggressor) == ENTITY_TYPE_HELICOPTER);

	position = get_local_entity_vec3d_ptr (aggressor, VEC3D_TYPE_COVER_POSITION);

	ASSERT (position);

	ASSERT (!check_zero_3d_vector (position));

	// Just to be sure....

	if (check_zero_3d_vector (position))
	{
		position = get_local_entity_vec3d_ptr (aggressor, VEC3D_TYPE_POSITION);
	}

	set_client_server_guide_entity_new_position (en, position, NULL);

	set_client_server_entity_float_value (en, FLOAT_TYPE_VELOCITY, get_local_entity_float_value (aggressor, FLOAT_TYPE_CRUISE_VELOCITY));

	//
	// change guide reached criteria
	//

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_ALTITUDE, TRUE, 1.0);

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_HEADING, TRUE, rad (5.0));

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_WEAPON_VECTOR, FALSE, 0.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_attack_guide_climb_position (entity *en)
{
	entity_sub_types
		selected_weapon;

	float
		weapon_effective_range,
		target_range,
		distance,
		time,
		velocity;

	vec3d
		*target_pos,
		*aggressor_pos,
		direction,
		position;

	entity
		*wp,
		*task,
		*aggressor,
		*target;

	set_client_server_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_CLIMB);

	get_local_guide_entity_pointers (en, &aggressor, &wp, &task, &target);

	//
	// find aggressors selected weapon, and it's max range
	//

	selected_weapon = get_local_entity_int_value (aggressor, INT_TYPE_SELECTED_WEAPON);

	ASSERT (selected_weapon != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON);

	weapon_effective_range = weapon_database [selected_weapon].effective_range;

	//
	// calculate vector of aggressor to target
	//

	target_pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

	aggressor_pos = get_local_entity_vec3d_ptr (aggressor, VEC3D_TYPE_POSITION);

	direction.x = aggressor_pos->x - target_pos->x;
	direction.y = 0.0;
	direction.z = aggressor_pos->z - target_pos->z;

	target_range = normalise_any_3d_vector (&direction);

	ASSERT (target_range != 0.0);

	//
	// calculate required distance of guide from target
	//

	velocity = get_local_entity_float_value (aggressor, FLOAT_TYPE_CRUISE_VELOCITY);

	ASSERT (velocity > 0.0);

	time = weapon_effective_range / velocity;

	time = time + FIXED_WING_CLIMB_TIME + FIXED_WING_DIVE_TIME;

	distance = velocity * time;

	//
	// calculate guide position
	//

	position.x = target_pos->x + (direction.x * distance);
	position.y = 0.0;
	position.z = target_pos->z + (direction.z * distance);

	bound_position_to_adjusted_map_volume (&position);

	position.y = get_3d_terrain_elevation (position.x, position.z) + get_local_entity_float_value (aggressor, FLOAT_TYPE_ATTACK_ALTITUDE);

	set_client_server_entity_float_value (en, FLOAT_TYPE_VELOCITY, get_local_entity_float_value (aggressor, FLOAT_TYPE_VELOCITY));

	set_client_server_guide_entity_new_position (en, &position, NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_attack_guide_dive_position (entity *en)
{
	entity_sub_types
		selected_weapon;

	float
		weapon_effective_range,
		target_range,
		distance,
		time,
		velocity;

	vec3d
		*target_pos,
		*aggressor_pos,
		direction,
		position;

	entity
		*wp,
		*task,
		*aggressor,
		*target;

	set_client_server_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_DIVE);

	get_local_guide_entity_pointers (en, &aggressor, &wp, &task, &target);

	//
	// find aggressors selected weapon, and it's effective range
	//

	selected_weapon = get_local_entity_int_value (aggressor, INT_TYPE_SELECTED_WEAPON);

	ASSERT (selected_weapon != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON);

	weapon_effective_range = weapon_database [selected_weapon].effective_range;

	//
	// calculate vector of aggressor to target
	//

	target_pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

	aggressor_pos = get_local_entity_vec3d_ptr (aggressor, VEC3D_TYPE_POSITION);

	direction.x = aggressor_pos->x - target_pos->x;
	direction.y = 0.0;
	direction.z = aggressor_pos->z - target_pos->z;

	target_range = normalise_any_3d_vector (&direction);

	ASSERT (target_range != 0.0);

	//
	// calculate required distance of guide from target
	//

	velocity = get_local_entity_float_value (aggressor, FLOAT_TYPE_CRUISE_VELOCITY);

	ASSERT (velocity > 0.0);

	time = weapon_effective_range / velocity;

	time = time + FIXED_WING_DIVE_TIME;

	distance = velocity * time;

	//
	// calculate guide position
	//

	position.x = target_pos->x + (direction.x * distance);
	position.y = 0.0;
	position.z = target_pos->z + (direction.z * distance);

	bound_position_to_map_volume (&position);

	position.y = get_3d_terrain_elevation (position.x, position.z) + get_local_entity_float_value (aggressor, FLOAT_TYPE_CRUISE_ALTITUDE);

	set_client_server_entity_float_value (en, FLOAT_TYPE_VELOCITY, get_local_entity_float_value (aggressor, FLOAT_TYPE_VELOCITY));

	set_client_server_guide_entity_new_position (en, &position, NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_attack_guide_fire_position (entity *en)
{
	vec3d
		position;

	entity
		*wp,
		*task,
		*aggressor,
		*target;

	get_local_guide_entity_pointers (en, &aggressor, &wp, &task, &target);

	switch (get_local_entity_type (aggressor))
	{
		case ENTITY_TYPE_HELICOPTER:
		{
			set_client_server_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_FIRE);

			get_local_entity_vec3d (aggressor, VEC3D_TYPE_POSITION, &position);

//			position.y += INITIAL_BOB_UP_DISTANCE;

			set_client_server_guide_entity_new_position (en, &position, NULL);

			set_client_server_entity_float_value (en, FLOAT_TYPE_VELOCITY, get_local_entity_float_value (aggressor, FLOAT_TYPE_CRUISE_VELOCITY));

			//
			// change guide reached criteria
			//

			set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_ALTITUDE, TRUE, 2.0);

			set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_HEADING, FALSE, 0.0);

			set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_WEAPON_VECTOR, TRUE, 0.0);

			break;
		}

		case ENTITY_TYPE_FIXED_WING:
		{
			entity_sub_types
				selected_weapon;

			float
				weapon_effective_range;

			vec3d
				*target_pos;

			//
			// find aggressors selected weapon, and it's max range
			//

			selected_weapon = get_local_entity_int_value (aggressor, INT_TYPE_SELECTED_WEAPON);

			ASSERT (selected_weapon != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON);

			weapon_effective_range = weapon_database [selected_weapon].effective_range;

			//
			// calculate vector of aggressor to target
			//

			target_pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

			if (weapon_database [selected_weapon].guidance_type != WEAPON_GUIDANCE_TYPE_NONE)
			{
				//
				// Make Jet Fly level and high for guided AG missiles
				//

				set_client_server_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_FIRE);

				position.x = target_pos->x;
				position.z = target_pos->z;

				position.y = get_3d_terrain_elevation (position.x, position.z) + get_local_entity_float_value (aggressor, FLOAT_TYPE_CRUISE_ALTITUDE);

				set_client_server_guide_entity_new_position (en, &position, NULL);
			}
			else
			{
				//
				// Head for intercept point (virtual)
				//

				set_client_server_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_FIRE_VIRTUAL);

				calculate_attack_guide_intercept_point (aggressor, target, selected_weapon, &position);

				set_client_server_guide_entity_new_position (en, &position, target);
			}

			set_client_server_entity_float_value (en, FLOAT_TYPE_VELOCITY, get_local_entity_float_value (aggressor, FLOAT_TYPE_VELOCITY));

			//
			// change guide reached criteria
			//

			set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_RADIUS, TRUE, weapon_effective_range);

			break;
		}

		default:
		{
			debug_fatal ("GD_ATTCK: Invalid Entity Type %d", get_local_entity_type (aggressor));
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_attack_guide_disengage_position (entity *en)
{
	entity
		*wp,
		*task,
		*aggressor,
		*target;

	entity_sub_types
		selected_weapon;

	float
		distance,
		velocity,
		time,
		weapon_effective_range;

	int
		virtual;

	vec3d
		position;

	virtual = FALSE;

	switch (get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE))
	{
		case ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_FIRE:
		{
			set_client_server_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_DISENGAGE);

			break;
		}

		case ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_FIRE_VIRTUAL:
		{
			set_client_server_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_DISENGAGE_VIRTUAL);

			virtual = TRUE;

			break;
		}

		default:
		{
			debug_fatal ("AG_ATTCK: Invalid Guide Type %d", get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE));

			break;
		}
	}

	get_local_guide_entity_pointers (en, &aggressor, &wp, &task, &target);

	ASSERT (get_local_entity_type (aggressor) == ENTITY_TYPE_FIXED_WING);

	//
	// find aggressors selected weapon, and it's effective range
	//

	selected_weapon = get_local_entity_int_value (aggressor, INT_TYPE_SELECTED_WEAPON);

	ASSERT (selected_weapon != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON);

	weapon_effective_range = weapon_database [selected_weapon].effective_range;

	//
	// calculate required distance of guide from target
	//

	velocity = get_local_entity_float_value (aggressor, FLOAT_TYPE_CRUISE_VELOCITY);

	ASSERT (velocity > 0.0);

	time = weapon_database [selected_weapon].burst_duration;

	time = max (time, 1.5);

	distance = weapon_effective_range - (velocity * time);

	distance = max (distance, 250.0);

	//
	// Set position
	//

	if (virtual)
	{
		//
		// Use same lead distance as fire position
		//

		get_local_entity_vec3d (en, VEC3D_TYPE_RELATIVE_POSITION, &position);

		set_client_server_guide_entity_new_position (en, &position, target);
	}
	else
	{
		//
		// calculate vector of aggressor to target
		//

		get_local_entity_vec3d (target, VEC3D_TYPE_POSITION, &position);

		position.y = get_3d_terrain_elevation (position.x, position.z) + get_local_entity_float_value (aggressor, FLOAT_TYPE_CRUISE_ALTITUDE);

		set_client_server_guide_entity_new_position (en, &position, NULL);
	}

	set_client_server_entity_float_value (en, FLOAT_TYPE_VELOCITY, get_local_entity_float_value (aggressor, FLOAT_TYPE_VELOCITY));

	//
	// change guide reached criteria
	//

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_RADIUS, TRUE, distance);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_attack_guide_egress_position (entity *en)
{
	entity
		*wp,
		*task,
		*group,
		*base,
		*aggressor,
		*target;

	float
		angle,
		distance,
		velocity,
		time;

	vec3d
		position,
		direction,
		*base_pos,
		*target_pos;

	int
		member_number;

	set_client_server_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_EGRESS);

	get_local_guide_entity_pointers (en, &aggressor, &wp, &task, &target);

	ASSERT (get_local_entity_type (aggressor) == ENTITY_TYPE_FIXED_WING);

	target_pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

	member_number = get_local_entity_int_value (aggressor, INT_TYPE_GROUP_MEMBER_NUMBER);

	//
	// break off at an angle
	//

	if (member_number > 3)
	{
		//
		// Should never happen, but just in case...
		//

		get_local_entity_vec3d (aggressor, VEC3D_TYPE_XV, &direction);

		direction.y = 0.0;

		normalise_any_3d_vector (&direction);
	}
	else
	{
		//
		// Use groups base as reference point so that egress route usually goes into friendly territory
		//

		group = get_local_entity_parent (aggressor, LIST_TYPE_MEMBER);

		ASSERT (group);

		base = get_local_entity_parent (group, LIST_TYPE_KEYSITE_GROUP);

		ASSERT (base);

		base_pos = get_local_entity_vec3d_ptr (base, VEC3D_TYPE_POSITION);

		ASSERT (base_pos);

		direction.x = base_pos->x - target_pos->x;
		direction.y = 0.0;
		direction.z = base_pos->z - target_pos->z;

		normalise_any_3d_vector (&direction);

		angle = 0.0;

		switch (member_number)
		{
			case 0:
			{
				angle = rad (-20.0);

				break;
			}
			case 1:
			{
				angle = rad (45.0);

				break;
			}
			case 2:
			{
				angle = rad (20.0);

				break;
			}
			case 3:
			{
				angle = rad (-45.0);

				break;
			}
		}

		rotate_3d_vector (&direction, angle);
	}

	//
	// calculate required distance of guide from target
	//

	velocity = get_local_entity_float_value (aggressor, FLOAT_TYPE_VELOCITY);

	ASSERT (velocity > 0.0);

	time = FIXED_WING_EGRESS_TIME;

	distance = velocity * time;

	//
	// calculate guide position
	//

	position.x = target_pos->x + (direction.x * distance);
	position.y = 0.0;
	position.z = target_pos->z + (direction.z * distance);

	bound_position_to_adjusted_map_volume (&position);

	position.y = get_3d_terrain_elevation (position.x, position.z) + get_local_entity_float_value (aggressor, FLOAT_TYPE_ATTACK_ALTITUDE);

	set_client_server_guide_entity_new_position (en, &position, NULL);

	set_client_server_entity_float_value (en, FLOAT_TYPE_VELOCITY, get_local_entity_float_value (aggressor, FLOAT_TYPE_VELOCITY));

	//
	// change guide reached criteria
	//

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_RADIUS, TRUE, get_local_entity_waypoint_database_reached_radius_value (wp, aggressor));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_attack_guide_hasty_fire_position (entity *en)
{
	entity
		*wp,
		*task,
		*aggressor,
		*target;

	vec3d
		position;

	set_client_server_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_HASTY_FIRE);

	get_local_guide_entity_pointers (en, &aggressor, &wp, &task, &target);

	ASSERT (get_local_entity_type (aggressor) == ENTITY_TYPE_HELICOPTER);

	//
	// Helicopter remains at current location
	//

	set_client_server_entity_float_value (en, FLOAT_TYPE_VELOCITY, get_local_entity_float_value (aggressor, FLOAT_TYPE_CRUISE_VELOCITY));

	get_local_entity_vec3d (aggressor, VEC3D_TYPE_POSITION, &position);

	set_client_server_guide_entity_new_position (en, &position, NULL);

	//
	// change guide reached criteria
	//

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_ALTITUDE, FALSE, 0.0);

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_HEADING, FALSE, 0.0);

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_WEAPON_VECTOR, TRUE, 0.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_attack_guide_hasty_take_cover_position (entity *en)
{
	vec3d
		position;

	entity
		*wp,
		*task,
		*aggressor,
		*target;

	set_client_server_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_HASTY_TAKE_COVER);

	get_local_guide_entity_pointers (en, &aggressor, &wp, &task, &target);

	ASSERT (get_local_entity_type (aggressor) == ENTITY_TYPE_HELICOPTER);

	get_local_entity_vec3d (en, VEC3D_TYPE_GUIDE_POSITION, &position);

	//
	// Helicopter remains at current location - just change altitude
	//

	position.y = get_3d_terrain_elevation (position.x, position.z) + 5.0;

	set_client_server_guide_entity_new_position (en, &position, NULL);

	set_client_server_entity_float_value (en, FLOAT_TYPE_VELOCITY, get_local_entity_float_value (aggressor, FLOAT_TYPE_CRUISE_VELOCITY));

	//
	// Need to set COVER_POSITION also
	//

	set_local_entity_vec3d (aggressor, VEC3D_TYPE_COVER_POSITION, &position);

	//
	// change guide reached criteria
	//

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_ALTITUDE, TRUE, 1.0);

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_HEADING, TRUE, rad (5.0));

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_WEAPON_VECTOR, FALSE, 0.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
