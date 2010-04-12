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

#include "entity/tacview/tacview.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 								0

#define DEBUG_MODULE_DISABLE_ARTILLERY_ERROR	0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_3D_OBJECT_SCALE (0.5)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//HELLFIRE//

#define HELLFIRE_MINIMUM_CLIMB_TIME (3.0)  // 1 seconds of burm, 3 remaining
#define HELLFIRE_LOAL_CLIMB1_TIME	(0.0)
#define HELLFIRE_LOAL_CLIMB2_TIME	(-12.0)
#define HELLFIRE_LOAL_CLIMB1_XZ	(1000.0)
#define HELLFIRE_LOAL_CLIMB1_Y		(300.0)
#define HELLFIRE_LOAL_CLIMB2_XZ	(6000.0)
#define HELLFIRE_LOAL_CLIMB2_Y		(450.0)
#define HELLFIRE_LOAL_DIVE_XZ		(7500.0)
#define HELLFIRE_LOAL_DIVE_Y		(-400.0)

//HELLFIRE//

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	draw_weapon_terrain_los_markers = FALSE;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define RANGE_STEP 20.0
#define WRITE_STEP 250.0
#define PITCH_STEP 5
#define NUM_SINGLE_DEGREE_VALUES 21
#define NUM_NEGATIVE_PITCH_VALUES (((90 - 10) / PITCH_STEP))
#define TOTAL_PITCH_INDICES (2*NUM_NEGATIVE_PITCH_VALUES + NUM_SINGLE_DEGREE_VALUES)
#define LAST_WEAPON ENTITY_SUB_TYPE_WEAPON_S13

typedef struct
{
	float drop_angle;
	float flight_time;
} ballistics_data;

static ballistics_data*
	ballistics_table[LAST_WEAPON+1][TOTAL_PITCH_INDICES + 2];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//
// NOTE: KEEP THIS FUNCTION IN SYNC WITH THE SIMILAR FUNCTION IN WEAPON.C
//
////////////////////////////////////////

// The get_intercept_point function predicts where the weapon will intercept the target (assuming the velocities and
// motion vector remain constant).
//
// The function computes how long it will take the weapon to reach where the target is now and then projects the target
// position along its motion vector to get the intercept point.
//
// This is a very approximate method but it works well when the weapon's velocity is much greater than the target's velocity.
//
// The result can be improved by iterating the process a few times.

static void get_intercept_point (entity *weapon_entity, entity *target, vec3d *intercept_point)
{
	int
		number_of_iterations;

	float
		weapon_velocity,
		target_true_velocity,
		velocity_ratio,
		target_move_distance;

	vec3d
		*weapon_position,
		target_position,
		target_motion_vector;

	ASSERT (weapon_entity);

	ASSERT (target);

	ASSERT (intercept_point);

	//
	// set intercept point to the targets current position
	//

	get_local_entity_target_point (target, intercept_point);

	target_position = *intercept_point;
	weapon_position = get_local_entity_vec3d_ptr (weapon_entity, VEC3D_TYPE_POSITION);


	//
	// use the weapon's forward velocity not true velocity as it is assumed that the weapon will
	// change course to intercept the target and the current motion vector may not be valid
	//

	weapon_velocity = get_local_entity_float_value (weapon_entity, FLOAT_TYPE_VELOCITY);

	target_true_velocity = get_local_entity_vec3d_magnitude (target, VEC3D_TYPE_MOTION_VECTOR);

	//
	// catch possible divide by zero (slow weapon or target)
	//

	if ((weapon_velocity > 0.001f) && (target_true_velocity > 0.001f))
	{
		if (target_true_velocity < weapon_velocity)
		{
			velocity_ratio = target_true_velocity / weapon_velocity;

			get_local_entity_vec3d (target, VEC3D_TYPE_MOTION_VECTOR, &target_motion_vector);

			normalise_3d_vector (&target_motion_vector);

			number_of_iterations = 3;

			while (number_of_iterations--)
			{
				target_move_distance = get_3d_range (weapon_position, intercept_point) * velocity_ratio;

				intercept_point->x = target_position.x + (target_motion_vector.x * target_move_distance);
				intercept_point->y = target_position.y + (target_motion_vector.y * target_move_distance);
				intercept_point->z = target_position.z + (target_motion_vector.z * target_move_distance);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_target_position (entity *en, vec3d *position, int can_guide_on_ground_lock)
{
	weapon
		*raw;

	entity
		*target;

	int
		target_position_valid = FALSE;

	weapon_decoy_types
		weapon_decoy_type;

	ASSERT (en);

	ASSERT (position);

	raw = (weapon *) get_local_entity_data (en);

	target = raw->mob.target_link.parent;

	if (can_guide_on_ground_lock)
	{
		// track the locked ground point
		get_local_entity_vec3d(raw->launched_weapon_link.parent, VEC3D_TYPE_EO_TRACKING_POINT, position);

		target_position_valid = eo_tracking_point_valid(position);
	}

	if (!target_position_valid && target)
	{
		if (get_local_entity_int_value (target, INT_TYPE_IDENTIFY_MOBILE))
		{
			weapon_decoy_type = (weapon_decoy_types) get_local_entity_int_value (target, INT_TYPE_WEAPON_DECOY_TYPE);

			if (weapon_decoy_type == WEAPON_DECOY_TYPE_NONE)
			{
				get_intercept_point (en, target, position);

				//
				// not a decoy, test for jammers
				//

				if ((get_local_entity_int_value (target, INT_TYPE_RADAR_JAMMER_ON)) && (get_decoy_type_for_weapon (en) == ENTITY_SUB_TYPE_WEAPON_CHAFF))
				{
					get_jammer_distract_position (en, position);
				}
				else if ((get_local_entity_int_value (target, INT_TYPE_INFRA_RED_JAMMER_ON)) && (get_decoy_type_for_weapon (en) == ENTITY_SUB_TYPE_WEAPON_FLARE))
				{
					get_jammer_distract_position (en, position);
				}
			}
			else if (weapon_decoy_type == WEAPON_DECOY_TYPE_SMOKE_GRENADE)
			{
				get_smoke_grenade_distract_position (en, target, position);
			}
			else
			{
				get_intercept_point (en, target, position);
			}
		}
		else
			get_local_entity_target_point (target, position);

		target_position_valid = TRUE;
	}

	return (target_position_valid);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void move_guided_weapon (entity *en, vec3d *new_position, vec3d *intercept_point)
{
	weapon
		*raw;

	float
		length,
		cos_turn_demand,
		turn_demand,
		max_turn_rate,
		turn_rate,
		max_frame_turn_rate,
		frame_turn_rate,
		inhibit_damp_factor,
		acceleration;

	vec3d
		uvec_intercept_point;

	matrix3x3
		m1,
		m2;

	ASSERT (en);

	ASSERT (new_position);

	ASSERT (intercept_point);

	raw = (weapon *) get_local_entity_data (en);

	////////////////////////////////////////
	//
	// move guided powered/guided unpowered weapon (ignore gravity)
	//
	////////////////////////////////////////

	#if DEBUG_MODULE

	create_rotated_debug_3d_object (intercept_point, rad (0.0), rad (0.0), rad (0.0), OBJECT_3D_INTERCEPT_POINT_RED, 0.0, DEBUG_3D_OBJECT_SCALE);

	#endif

	// adjust for high trajectory
	if (weapon_database[raw->mob.sub_type].hellfire_flight_profile && raw->missile_phase != MISSILE_FINAL_PHASE)
	{
		float range, dive_ratio;
		vec3d
			horizontal_range_point = *intercept_point,
			*weapon_position;

		weapon_position = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

		horizontal_range_point.y = weapon_position->y;
		range = get_2d_range (weapon_position, &horizontal_range_point);

		dive_ratio = (intercept_point->y - weapon_position->y) / range;

		if (raw->loal_mode)
		{
				switch (raw->missile_phase)
				{
				case MISSILE_PHASE1:
					if (raw->weapon_lifetime > HELLFIRE_LOAL_CLIMB1_TIME)
					{
						if (range < 10.0)
							raw->missile_phase = MISSILE_FINAL_PHASE;
						else
						{
						// initial climb of 30%
							float new_aim_y = weapon_position->y + range * 0.3f;
							intercept_point->y = max(new_aim_y, intercept_point->y);
						}
						break;
					}

					raw->missile_phase = MISSILE_PHASE2;
					// fall through

				case MISSILE_PHASE2:
					if (range < 800.0)
					{
						raw->missile_phase = MISSILE_FINAL_PHASE;
						break;
					}
					else if (dive_ratio > -0.25)
					{
						// seconds phase climb at 4%
						float new_aim_y = weapon_position->y + range * 0.04;
						intercept_point->y = max(new_aim_y, intercept_point->y);

						break;
					}

					raw->missile_phase = MISSILE_PHASE3;
					// fall through

				case MISSILE_PHASE3:
					if (range < 500.0)
					{
						raw->missile_phase = MISSILE_FINAL_PHASE;
						break;
					}
					else if (dive_ratio > -0.55f)
					{
						// third phase dive at 20%
						float new_aim_y = weapon_position->y + range * -0.2f;
						intercept_point->y = max(new_aim_y, intercept_point->y);

						break;
					}

					// final phase goes straigt for target (in approximate 60% dive)
					raw->missile_phase = MISSILE_FINAL_PHASE;
					break;
				default:
					ASSERT(FALSE);
				}
		}
		else  // lobl mode
		{
				switch (raw->missile_phase)
				{
				case MISSILE_PHASE1:
					if (raw->weapon_lifetime < HELLFIRE_MINIMUM_CLIMB_TIME && range < 900.0)
					{
						raw->missile_phase = MISSILE_FINAL_PHASE;
						break;
					}

					if (dive_ratio > -0.15)
					{
						// intial phase climb at 7%
						float new_aim_y = weapon_position->y + range * 0.07f;
						intercept_point->y = max(new_aim_y, intercept_point->y);

						break;
					}

					raw->missile_phase = MISSILE_PHASE2;
				case MISSILE_PHASE2:
					if (raw->weapon_lifetime < HELLFIRE_MINIMUM_CLIMB_TIME && range < 750.0)
					{
						raw->missile_phase = MISSILE_FINAL_PHASE;
						break;
					}

					if (dive_ratio > -0.3f)
					{
						// second phase dive at 3%
						float new_aim_y = weapon_position->y + range * -0.03;
						intercept_point->y = max(new_aim_y, intercept_point->y);

						break;
					}

					raw->missile_phase = MISSILE_FINAL_PHASE;

					break;
				default:
					ASSERT(FALSE);
				}
		}
	}


	//
	// get unit vector to intercept point
	//

	uvec_intercept_point.x = intercept_point->x - raw->mob.position.x;
	uvec_intercept_point.y = intercept_point->y - raw->mob.position.y;
	uvec_intercept_point.z = intercept_point->z - raw->mob.position.z;

	length = get_3d_vector_magnitude (&uvec_intercept_point);

	//
	// guard against divide by zero (weapon must be very close to the intercept point)
	//

	if (length < 1.0)
	{
		raw->kill_code = WEAPON_KILL_CODE_HIT_TARGET;

		return;
	}

	normalise_3d_vector_given_magnitude (&uvec_intercept_point, length);

	//
	// get turn demand
	//

	cos_turn_demand = get_3d_unit_vector_dot_product (&raw->mob.zv, &uvec_intercept_point);

	//
	// check for overshot target (but only when speed is high enough, otherwise intercept point might be
	// unusually much offset
	//

	if (raw->mob.velocity > 20.0 && cos_turn_demand < weapon_database[raw->mob.sub_type].max_seeker_limit)   // lost guidance
	{
		if (raw->weapon_lifetime - weapon_database[raw->mob.sub_type].burn_time < -1.0)  // weapon armed after 1 second
		{
			debug_log("%s self destructed due to turn demand too high (%0.1f degrees). limit: %.2f", weapon_database[raw->mob.sub_type].full_name, deg(acos(cos_turn_demand)),
				deg(acos(weapon_database[raw->mob.sub_type].max_seeker_limit)));

			raw->kill_code = WEAPON_KILL_CODE_OVERSHOT_TARGET;

			return;
		}
//		else
//			set_client_server_entity_parent (en, LIST_TYPE_TARGET, NULL);
	}

	//
	// get attitude matrix (where y-axis is perpendicular to turn demand plane)
	//

	get_3d_vector_cross_product (&raw->mob.yv, &raw->mob.zv, &uvec_intercept_point);

	normalise_3d_vector (&raw->mob.yv);

	get_3d_vector_cross_product (&raw->mob.xv, &raw->mob.yv, &raw->mob.zv);

	normalise_3d_vector (&raw->mob.xv);

	//
	// close angle (rotate about y-axis)
	//

	turn_demand = acos (cos_turn_demand);

	max_turn_rate = weapon_database[raw->mob.sub_type].g_max / max (raw->mob.velocity, 1.0f);

	turn_rate = bound (turn_demand, -max_turn_rate, max_turn_rate);

	max_frame_turn_rate = max_turn_rate * get_delta_time ();

	//
	// damp turn rate during inhibit period
	//

	if (raw->weapon_lifetime > (weapon_database[raw->mob.sub_type].burn_time - weapon_database[raw->mob.sub_type].inhibit_time))
	{
		//
		// damp using y = x * x curve
		//

		ASSERT (weapon_database[raw->mob.sub_type].inhibit_time > 0.0);

		inhibit_damp_factor = (weapon_database[raw->mob.sub_type].burn_time - raw->weapon_lifetime) / weapon_database[raw->mob.sub_type].inhibit_time;

		inhibit_damp_factor *= inhibit_damp_factor;

		turn_rate *= inhibit_damp_factor;

		frame_turn_rate = inhibit_damp_factor * bound (turn_demand, -max_frame_turn_rate, max_frame_turn_rate);
	}
	else
	{
		// arneh - limit turn rate in first phases of hellfire trajectory to get a smoother arc
		if (weapon_database[raw->mob.sub_type].hellfire_flight_profile && raw->missile_phase != MISSILE_FINAL_PHASE)
			max_frame_turn_rate = max_frame_turn_rate * 0.5;

		frame_turn_rate = bound (turn_demand, -max_frame_turn_rate, max_frame_turn_rate);
	}

	get_3d_transformation_matrix (m1, frame_turn_rate, 0.0, 0.0);

	// arneh - make vikhrs spiral
	if (weapon_database[raw->mob.sub_type].spiral_flightpath && raw->weapon_lifetime > 0.0
		&& (raw->weapon_lifetime - weapon_database[raw->mob.sub_type].burn_time) < -0.2f)
	{
		matrix3x3 spiral_matrix, tmp;

		float heading = rad(cos(raw->weapon_lifetime * 8.0)) * raw->weapon_lifetime * 0.4f;
		float pitch = -rad(sin(raw->weapon_lifetime * 8.0)) * raw->weapon_lifetime * 0.4f;

		get_3d_transformation_matrix (spiral_matrix, heading, pitch, 0.0);

		multiply_matrix3x3_matrix3x3 (tmp, m1, raw->mob.attitude);
		multiply_matrix3x3_matrix3x3 (m2, tmp, spiral_matrix);
	}
	else
		multiply_matrix3x3_matrix3x3 (m2, m1, raw->mob.attitude);

	//
	// set roll to zero to remove jitter on weapon view
	//

	get_3d_transformation_matrix (raw->mob.attitude, get_heading_from_attitude_matrix (m2), get_pitch_from_attitude_matrix (m2), 0.0);

	//
	// acceleration
	//

	if (raw->weapon_lifetime > 0.0)
	{
		acceleration = weapon_database[raw->mob.sub_type].g_max - (fabs (turn_rate) * raw->mob.velocity);
	}
	else
	{
		acceleration = -(fabs (turn_rate) * raw->mob.velocity);
	}

	//
	// velocity
	//

	raw->mob.velocity += acceleration * get_delta_time ();

	raw->mob.velocity = max (raw->mob.velocity, 0.0f);

	if (raw->weapon_lifetime < 0.0 && raw->mob.velocity < 20.0)  // self destruct if speed drops too low (after motor has burned out)
	{
		debug_log("%s self destructed due to speed dropping too low (%0.1f m/s)", weapon_database[raw->mob.sub_type].full_name, raw->mob.velocity);

		raw->kill_code = WEAPON_KILL_CODE_SELF_DESTRUCT;

		return;
	}

	//
	// motion vector
	//

	raw->mob.motion_vector.x = raw->mob.zv.x * raw->mob.velocity;
	raw->mob.motion_vector.y = raw->mob.zv.y * raw->mob.velocity;
	raw->mob.motion_vector.z = raw->mob.zv.z * raw->mob.velocity;

	//
	// position
	//

	new_position->x += raw->mob.motion_vector.x * get_delta_time ();
	new_position->y += raw->mob.motion_vector.y * get_delta_time ();
	new_position->z += raw->mob.motion_vector.z * get_delta_time ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void move_unguided_weapon (weapon* raw, vec3d *new_position, float delta_time, int disperse)
{
	float
		acceleration,
		heading,
		pitch,
		h_vel,
		v_vel;

	ASSERT (raw);
	ASSERT (new_position);

	if (raw->weapon_lifetime > 0.0)
	{
		////////////////////////////////////////
		//
		// move unguided powered weapon (ignore gravity)
		//
		////////////////////////////////////////

		//
		// acceleration
		//

		acceleration = weapon_database[raw->mob.sub_type].g_max;

		//
		// velocity
		//

		raw->mob.velocity += acceleration * delta_time;
		raw->mob.velocity = bound (raw->mob.velocity, 0.0, weapon_database[raw->mob.sub_type].cruise_velocity);
	}
	else if (weapon_database[raw->mob.sub_type].drag_factor > 0.0 &&
		weapon_database[raw->mob.sub_type].aiming_type == WEAPON_AIMING_TYPE_CALC_LEAD_AND_BALLISTIC)
	{
		// arneh - simulate drag as decelleration
		float
			 // adjust velocity in steps to avoid difference because of different delta times (i.e. different behaviour drag depending on frame rate)
			adjusted_velocity = (int)(raw->mob.velocity * 0.1f) * 10;

		acceleration = -0.001 * weapon_database[raw->mob.sub_type].drag_factor * adjusted_velocity * adjusted_velocity;

		// velocity

		raw->mob.velocity += acceleration * delta_time;
		raw->mob.velocity = max (raw->mob.velocity, 0.0f);
	}


	if (weapon_database[raw->mob.sub_type].ignore_gravity)
	{
		////////////////////////////////////////
		//
		// move unguided unpowered weapon (ignore gravity)
		//
		////////////////////////////////////////

		//
		// motion vector
		//

		raw->mob.motion_vector.x = raw->mob.zv.x * raw->mob.velocity;
		raw->mob.motion_vector.y = raw->mob.zv.y * raw->mob.velocity;
		raw->mob.motion_vector.z = raw->mob.zv.z * raw->mob.velocity;

		//
		// position
		//

		new_position->x += raw->mob.motion_vector.x * delta_time;
		new_position->y += raw->mob.motion_vector.y * delta_time;
		new_position->z += raw->mob.motion_vector.z * delta_time;
	}
	else
	{
		////////////////////////////////////////
		//
		// move unguided unpowered weapon (with gravity)
		//
		////////////////////////////////////////

		// Workaround for buggy floating point calculations in open watcom 1.7
		// Assign to variable instead of using expression directly in calculation
		float gravity_fall = (0.5 * G * delta_time * delta_time);

		//
		// motion vector
		//

		raw->mob.motion_vector.x = raw->mob.zv.x * raw->mob.velocity;
		raw->mob.motion_vector.y = raw->mob.zv.y * raw->mob.velocity;
		raw->mob.motion_vector.z = raw->mob.zv.z * raw->mob.velocity;

		//
		// position
		//

		new_position->x += raw->mob.motion_vector.x * delta_time;
		new_position->y += raw->mob.motion_vector.y * delta_time - gravity_fall;
		new_position->z += raw->mob.motion_vector.z * delta_time;

		ASSERT(new_position->y >= -1000000000000.0);  // mostly just tests for -nan and -inf which happens with buggy floating point calculations

		//
		// apply gravity (after moving weapon)
		//

		heading = get_heading_from_attitude_matrix (raw->mob.attitude);

		pitch = get_pitch_from_attitude_matrix (raw->mob.attitude);

		h_vel = cos (pitch) * raw->mob.velocity;

		v_vel = (sin (pitch) * raw->mob.velocity) - (G * delta_time);

		////////////////////////////////////////
		//
		// fudge for ejector seat and crates
		//

		switch (raw->mob.sub_type)
		{
			case ENTITY_SUB_TYPE_WEAPON_HOKUM_PILOT:
			case ENTITY_SUB_TYPE_WEAPON_HOKUM_CO_PILOT:
			{
				if (raw->parachute_status == PARACHUTE_STATUS_OPEN1)
				{
					h_vel = bound (h_vel, -7.5, 7.5);

					v_vel = max (v_vel, -15.0f);
				}
				else if (raw->parachute_status == PARACHUTE_STATUS_OPEN2)
				{
					h_vel = bound (h_vel, -5.0, 5.0);

					v_vel = max (v_vel, -10.0f);
				}
				else if (raw->parachute_status == PARACHUTE_STATUS_OPEN3)
				{
					h_vel = bound (h_vel, -2.5, 2.5);

					v_vel = max (v_vel, -5.0f);
				}

				break;
			}
			case ENTITY_SUB_TYPE_WEAPON_CRATE:
			{
				h_vel = bound (h_vel, -10.0, 10.0);

				v_vel = max (v_vel, -20.0f);

				break;
			}
		}

		//
		////////////////////////////////////////

		raw->mob.velocity = sqrt ((h_vel * h_vel) + (v_vel * v_vel));

		pitch = atan2 (v_vel, h_vel);

		get_3d_transformation_matrix (raw->mob.attitude, heading, pitch, 0.0);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void check_guidance_source (weapon *raw, entity *en, int laser_guided)
{
	entity
		*new_target;

	float
		target_range,
		theta;

	vec3d
		*target_position,
		weapon_to_target;

	ASSERT (raw);

	ASSERT (en);

	if (get_comms_model () == COMMS_MODEL_SERVER)
	{
		new_target = raw->mob.target_link.parent;

		//
		// check guidance source exists for all weapons
		//

		if (raw->launched_weapon_link.parent)
		{
			//
			// check guidance source has changed target for weapons launched by human pilots only
			//

			if (get_local_entity_int_value (raw->launched_weapon_link.parent, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
			{
				#ifdef DEBUG_MODULE
				debug_log("Finding parent's target (parent: %p, parent type %s", raw->launched_weapon_link.parent, entity_type_names[raw->launched_weapon_link.parent->type]);
				#endif

				// no target if no laser designation
				if (laser_guided && !get_local_entity_int_value(raw->launched_weapon_link.parent, INT_TYPE_LASER_ON))
				{
					new_target = NULL;
				}
				else
					new_target = get_local_entity_parent (raw->launched_weapon_link.parent, LIST_TYPE_TARGET);

				//
				// check target is in weapon lock cone
				//

				if (new_target)
				{
					if (new_target != raw->mob.target_link.parent)
					{
						target_position = get_local_entity_vec3d_ptr (new_target, VEC3D_TYPE_POSITION);

						weapon_to_target.x = target_position->x - raw->mob.position.x;
						weapon_to_target.y = target_position->y - raw->mob.position.y;
						weapon_to_target.z = target_position->z - raw->mob.position.z;

						target_range = (weapon_to_target.x * weapon_to_target.x) +
											(weapon_to_target.y * weapon_to_target.y) +
											(weapon_to_target.z * weapon_to_target.z);

						if (target_range > 1.0)
						{
							target_range = sqrt (target_range);

							normalise_3d_vector_given_magnitude (&weapon_to_target, target_range);

							theta = acos (get_3d_unit_vector_dot_product (&raw->mob.zv, &weapon_to_target));

							if (theta > weapon_database[raw->mob.sub_type].max_launch_angle_error)
							{
								new_target = NULL;
							}
						}
 					}
				}
			}
		}
		else
		{
			new_target = NULL;
		}

		if (new_target != raw->mob.target_link.parent)
		{
			set_client_server_entity_parent (en, LIST_TYPE_TARGET, new_target);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void weapon_movement (entity *en)
{
	weapon
		*raw;

	int
		i,
		seed,
		intercept_point_valid,
		high_precision_collision,
		hit_ground;

	terrain_classes
		terrain_class;

	float
		dx,
		dy,
		dz,
		cruise_time_error,
		total_cruise_time,
		heading;

	vec3d
		old_position,
		new_position,
		intercept_point,
		face_normal,
		test_point;

	entity
		*hit_target;

	////////////////////////////////////////
	//
	// pre-amble
	//
	////////////////////////////////////////

	ASSERT (en);

	raw = (weapon *) get_local_entity_data (en);

	ASSERT (entity_sub_type_weapon_valid (raw->mob.sub_type));

	////////////////////////////////////////
	//
	// ensure velocity >= 0.0
	//
	////////////////////////////////////////

	raw->mob.velocity = max (raw->mob.velocity, 0.0f);

	////////////////////////////////////////
	//
	// ensure valid positions
	//
	////////////////////////////////////////

	old_position = raw->mob.position;

	new_position = raw->mob.position;

	////////////////////////////////////////
	//
	// update lifetime
	//
	////////////////////////////////////////

	raw->weapon_lifetime -= get_delta_time ();

	seed = get_client_server_entity_random_number_seed (en);

	cruise_time_error = frand1x (&seed) * weapon_database[raw->mob.sub_type].cruise_time_max_error;

	total_cruise_time = weapon_database[raw->mob.sub_type].cruise_time + cruise_time_error;

	if (raw->weapon_lifetime < -total_cruise_time)
	{
		raw->kill_code = WEAPON_KILL_CODE_EXHAUSTED;

		return;
	}

	////////////////////////////////////////
	//
	// do not move weapon on ground
	//
	////////////////////////////////////////

	if (raw->weapon_on_ground)
	{
		raw->mob.velocity = 0.0;

		raw->mob.motion_vector.x = 0.0;
		raw->mob.motion_vector.y = 0.0;
		raw->mob.motion_vector.z = 0.0;

		#if DEBUG_MODULE

		create_vectored_debug_3d_object (&new_position, &raw->mob.zv, OBJECT_3D_VECTOR_GREEN, 0.0, DEBUG_3D_OBJECT_SCALE);

		#endif

		return;
	}

	////////////////////////////////////////
	//
	// guidance
	//
	////////////////////////////////////////

	switch (weapon_database[raw->mob.sub_type].guidance_type)
	{
		////////////////////////////////////////
		case WEAPON_GUIDANCE_TYPE_NONE:
		////////////////////////////////////////
		{
			intercept_point_valid = FALSE;

			break;
		}
		////////////////////////////////////////
		case WEAPON_GUIDANCE_TYPE_PASSIVE_INFRA_RED:
		////////////////////////////////////////
		{
			intercept_point_valid = get_target_position (en, &intercept_point, FALSE);

			break;
		}
		////////////////////////////////////////
		case WEAPON_GUIDANCE_TYPE_SEMI_ACTIVE_RADAR:
		////////////////////////////////////////
		{
			check_guidance_source (raw, en, FALSE);

			intercept_point_valid = get_target_position (en, &intercept_point, FALSE);

			break;
		}
		////////////////////////////////////////
		case WEAPON_GUIDANCE_TYPE_ACTIVE_RADAR:
		////////////////////////////////////////
		{
			//
			// active radar lock on after launch (switch from NULL target to valid target)
			//

			if (get_comms_model () == COMMS_MODEL_SERVER)
			{
				if (!raw->mob.target_link.parent)  // has no target
				{
					if (!weapon_database[raw->mob.sub_type].hellfire_flight_profile)
					{
						check_guidance_source (raw, en, FALSE);
					}
					else
					{
						//HELLFIRE//

						//
						// Hellfire flight profile only look for a new target after climb
						//

						if (raw->weapon_lifetime < HELLFIRE_LOAL_CLIMB1_TIME)
						{
							check_guidance_source (raw, en, FALSE);
						}

						//HELLFIRE//
					}
				}
			}

			intercept_point_valid = get_target_position (en, &intercept_point, FALSE);

			break;
		}
		////////////////////////////////////////
		case WEAPON_GUIDANCE_TYPE_SEMI_ACTIVE_LASER:
		////////////////////////////////////////
		{
			int
				do_guidance_source_check;

			do_guidance_source_check = TRUE;

			//HELLFIRE// LOAL for weapons launched by human pilots only

			if (get_comms_model () == COMMS_MODEL_SERVER)
			{
				if (!raw->mob.target_link.parent)
				{
					if (weapon_database[raw->mob.sub_type].hellfire_flight_profile)
					{
						if (raw->launched_weapon_link.parent)
						{
							if (get_local_entity_int_value (raw->launched_weapon_link.parent, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
							{
								//
								// Hellfire flight profile only look for a new target after climb
								//

								do_guidance_source_check = FALSE;

								if (raw->weapon_lifetime < HELLFIRE_LOAL_CLIMB1_TIME)
									if (get_local_entity_int_value (raw->launched_weapon_link.parent, INT_TYPE_LASER_ON))
										if (get_local_entity_int_value (raw->launched_weapon_link.parent, INT_TYPE_LOS_TO_TARGET))
											do_guidance_source_check = TRUE;
							}
						}
					}
				}
			}

			//HELLFIRE//

			if (do_guidance_source_check)
			{
				check_guidance_source (raw, en, TRUE);
			}

			if (get_local_entity_int_value (raw->launched_weapon_link.parent, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI
				&& !get_local_entity_int_value(raw->launched_weapon_link.parent, INT_TYPE_LASER_ON))
			{
				intercept_point_valid = FALSE;
			}
			else
				intercept_point_valid = get_target_position (en, &intercept_point, TRUE);

			break;
		}
		////////////////////////////////////////
		case WEAPON_GUIDANCE_TYPE_SEMI_ACTIVE_LASER_BEAM_RIDING:
		////////////////////////////////////////
		{
			check_guidance_source (raw, en, TRUE);

			if (get_local_entity_int_value (raw->launched_weapon_link.parent, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI
				&& !get_local_entity_int_value(raw->launched_weapon_link.parent, INT_TYPE_LASER_ON))
			{
				intercept_point_valid = FALSE;
			}
			else
				intercept_point_valid = get_target_position (en, &intercept_point, TRUE);

			break;
		}
		////////////////////////////////////////
		case WEAPON_GUIDANCE_TYPE_ACTIVE_LASER:
		////////////////////////////////////////
		{
			intercept_point_valid = get_target_position (en, &intercept_point, FALSE);

			break;
		}
		////////////////////////////////////////
		case WEAPON_GUIDANCE_TYPE_RADIO_COMMAND:
		////////////////////////////////////////
		{
			check_guidance_source (raw, en, FALSE);

			intercept_point_valid = get_target_position (en, &intercept_point, TRUE);

			break;
		}
		////////////////////////////////////////
		case WEAPON_GUIDANCE_TYPE_WIRE_GUIDED:
		////////////////////////////////////////
		{
			check_guidance_source (raw, en, FALSE);

			intercept_point_valid = get_target_position (en, &intercept_point, TRUE);

			break;
		}
	}

	////////////////////////////////////////
	//
	// movement
	//
	////////////////////////////////////////

	if (intercept_point_valid)
	{
		move_guided_weapon (en, &new_position, &intercept_point);
	}
	else
	{
		// unless missile is a LOAL hellfire in phase 1 or 2, move as an unguided weapon when no target
		if (!raw->loal_mode || raw->missile_phase > MISSILE_PHASE2)
		{
			weapon* weapon = (struct WEAPON *) get_local_entity_data (en);
			move_unguided_weapon (weapon, &new_position, get_delta_time(), TRUE);
		}
		else
		{
			//HELLFIRE//

			//
			// Hellfire flight profile
			//

			intercept_point = raw->mob.position;

			//
			// climb or dive
			//

			if (raw->weapon_lifetime > HELLFIRE_LOAL_CLIMB1_TIME)
			{
				intercept_point.x += HELLFIRE_LOAL_CLIMB1_XZ * raw->mob.zv.x;
				intercept_point.y += HELLFIRE_LOAL_CLIMB1_Y;
				intercept_point.z += HELLFIRE_LOAL_CLIMB1_XZ * raw->mob.zv.z;
			}
			else if (raw->weapon_lifetime > HELLFIRE_LOAL_CLIMB2_TIME)
			{
				intercept_point.x += HELLFIRE_LOAL_CLIMB2_XZ * raw->mob.zv.x;
				intercept_point.y += HELLFIRE_LOAL_CLIMB2_Y;
				intercept_point.z += HELLFIRE_LOAL_CLIMB2_XZ * raw->mob.zv.z;
			}
			else
			{
				intercept_point.x += HELLFIRE_LOAL_DIVE_XZ * raw->mob.zv.x;
				intercept_point.y += HELLFIRE_LOAL_DIVE_Y;
				intercept_point.z += HELLFIRE_LOAL_DIVE_XZ * raw->mob.zv.z;
			}

			move_guided_weapon (en, &new_position, &intercept_point);

			//HELLFIRE//
		}
	}

	// TODO check rotation
	if (tacview_is_logging())
		write_tacview_unit_update(en, TRUE, TRUE, FALSE);

	if (raw->kill_code != WEAPON_KILL_CODE_OK)
	{
		return;
	}

	////////////////////////////////////////
	//
	// collision detection precision
	//
	////////////////////////////////////////

	high_precision_collision = FALSE;

	if (raw->mob.target_link.parent)
	{
		if (get_local_entity_int_value (raw->mob.target_link.parent, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
		{
			high_precision_collision = TRUE;
		}
	}

	if (raw->launched_weapon_link.parent)
	{
		if (get_local_entity_int_value (raw->launched_weapon_link.parent, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
		{
			high_precision_collision = TRUE;
		}
	}

	if (en == get_local_entity_first_child (get_camera_entity (), LIST_TYPE_VIEW_WEAPON))
	{
		high_precision_collision = TRUE;
	}

	////////////////////////////////////////
	//
	// target collision detection
	//
	////////////////////////////////////////

	if (get_comms_model () == COMMS_MODEL_SERVER)
	{
		if (weapon_database[raw->mob.sub_type].in_flight_collision_check)
		{
			if (high_precision_collision || (!raw->mob.target_link.parent))
			{
				if (hit_target = collision_test_weapon_with_any_target (en, &old_position, &new_position))
				{
					if (hit_target != raw->mob.target_link.parent)
					{
						//
						// switch target parent to new_target (on server only)
						//

						delete_local_entity_from_parents_child_list (en, LIST_TYPE_TARGET);

						insert_local_entity_into_parents_child_list (en, LIST_TYPE_TARGET, hit_target, NULL);
					}

					raw->kill_code = WEAPON_KILL_CODE_HIT_TARGET;
				}
				else if (high_precision_collision)
				{
					if (collision_test_weapon_with_trees (&old_position, &new_position))
					{
						raw->kill_code = WEAPON_KILL_CODE_SELF_DESTRUCT;
					}
				}
			}
			else
			{
				if (collision_test_weapon_with_given_target (en, raw->mob.target_link.parent, &old_position, &new_position))
				{
					raw->kill_code = WEAPON_KILL_CODE_HIT_TARGET;
				}
			}
		}
	}

	////////////////////////////////////////
	//
	// terrain collision detection
	//
	////////////////////////////////////////

	//
	// UP TO THIS POINT THE WEAPON HAS NOT BEEN MOVED SO IT IS OK TO RETURN WITHOUT BOUNDS CHECKING THE POSITION
	//

	//
	// from now on only overwrite kill_code if kill_code == WEAPON_KILL_CODE_OK
	//

	//
	// inside map area
	//

	if (!point_inside_map_area (&new_position))
	{
		bound_position_to_map_volume (&new_position);

		ASSERT(point_inside_map_volume(&new_position));

		set_local_entity_vec3d (en, VEC3D_TYPE_POSITION, &new_position);

		if (raw->kill_code == WEAPON_KILL_CODE_OK)
		{
			raw->kill_code = WEAPON_KILL_CODE_OUT_OF_BOUNDS;
		}

		return;
	}

	//
	// below map ceiling
	//

	if (!point_below_ceiling (&new_position))
	{
		bound_position_to_map_volume (&new_position);

		set_local_entity_vec3d (en, VEC3D_TYPE_POSITION, &new_position);

		if (raw->kill_code == WEAPON_KILL_CODE_OK)
		{
			raw->kill_code = WEAPON_KILL_CODE_OUT_OF_BOUNDS;
		}

		return;
	}

	ASSERT(point_inside_map_volume(&new_position));

	//
	// set weapon position (set again if new_position changes)
	//

	set_local_entity_vec3d (en, VEC3D_TYPE_POSITION, &new_position);

	//
	// terrain collision
	//

	hit_ground = FALSE;

	if (point_below_ground (&new_position))
	{
		hit_ground = TRUE;
	}
	else
	{
		if (high_precision_collision)
		{
			dx = (new_position.x - old_position.x) * 0.1f;
			dy = (new_position.y - old_position.y) * 0.1f;
			dz = (new_position.z - old_position.z) * 0.1f;

			test_point = old_position;

			//
			// new_position has already been tested so there is no need to test again (also the interpolated new_position
			// would be inaccurate and may be tested as above ground when it is below)
			//

			for (i = 0; i < 9; i++)
			{
				test_point.x += dx;
				test_point.y += dy;
				test_point.z += dz;

				if (point_inside_map_area (&test_point))
				{
					if (point_below_ground (&test_point))
					{
						hit_ground = TRUE;

						new_position = test_point;

						break;
					}
					else
					{
						if (draw_weapon_terrain_los_markers && (get_view_mode () == VIEW_MODE_EXTERNAL))
						{
							create_rotated_debug_3d_object (&test_point, 0.0, 0.0, 0.0, OBJECT_3D_INTERCEPT_POINT_WHITE, 0.0, 0.25);
						}
					}
				}
			}
		}
	}

	if (hit_ground)
	{
		terrain_class = get_ground_impact_point (&old_position, &new_position, &new_position);

		if (draw_weapon_terrain_los_markers && (get_view_mode () == VIEW_MODE_EXTERNAL))
		{
			create_rotated_debug_3d_object (&new_position, 0.0, 0.0, 0.0, OBJECT_3D_INTERCEPT_POINT_RED, 3.0, 0.25);
		}

		set_local_entity_vec3d (en, VEC3D_TYPE_POSITION, &new_position);

		if (terrain_class == TERRAIN_CLASS_WATER)
		{
			if (raw->kill_code == WEAPON_KILL_CODE_OK)
			{
				raw->kill_code = WEAPON_KILL_CODE_HIT_WATER;
			}
		}
		else
		{
			if (weapon_database[raw->mob.sub_type].survive_ground_impact)
			{
				//
				// align weapon with terrain
				//

				heading = get_heading_from_attitude_matrix (raw->mob.attitude);

				get_3d_terrain_face_normal (&face_normal, new_position.x, new_position.z);

				get_3d_transformation_matrix_from_face_normal_and_heading (raw->mob.attitude, &face_normal, heading);

				//
				// smoke grenade effect
				//

				if (raw->mob.sub_type == ENTITY_SUB_TYPE_WEAPON_SMOKE_GRENADE)
				{
					if (get_comms_model () == COMMS_MODEL_SERVER)
					{
						raw->kill_code = WEAPON_KILL_CODE_HIT_LAND;

						create_client_server_weapon_killed_explosion_effect (en);

						raw->kill_code = WEAPON_KILL_CODE_OK;
					}
				}

				raw->weapon_on_ground = TRUE;
			}
			else
			{
				if (raw->kill_code == WEAPON_KILL_CODE_OK)
				{
					raw->kill_code = WEAPON_KILL_CODE_HIT_LAND;
				}
			}
		}
	}

	////////////////////////////////////////
	//
	// draw debug trail
	//
	////////////////////////////////////////

	#if DEBUG_MODULE

	if (raw->weapon_lifetime > 0.0)
	{
		create_debug_3d_line (&old_position, &new_position, sys_col_red, 30.0);
	}
	else
	{
		create_debug_3d_line (&old_position, &new_position, sys_col_yellow, 30.0);
	}

	create_vectored_debug_3d_object (&new_position, &raw->mob.zv, OBJECT_3D_VECTOR_GREEN, 0.0, DEBUG_3D_OBJECT_SCALE);

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** calculates the index for the pitch value in the ballistics table.  Rounded down.
 *
 *  Closeness will be set to a value from 0.0 to 1.0 describing how
 *  close the index is to the returned index (compared to the next
 *  higher index.  1.0 means it is the exact index,  0.5 means
 *  halfway between return value and return value + 1, etc.
 *  Used for making a weighted average of value.
 */
static int get_floor_pitch_index(float pitch, float* closeness)
{
	float deg_pitch = deg(pitch);

	int
		int_pitch;

	ASSERT(closeness);

	if (deg_pitch < -10.0)
	{
		int_pitch = (int)(floor(deg_pitch / PITCH_STEP));

		*closeness = 1.0 - ((deg_pitch - (int_pitch * PITCH_STEP)) / PITCH_STEP);

		return int_pitch + (10 / PITCH_STEP) + NUM_NEGATIVE_PITCH_VALUES;
	}
	else if (deg_pitch < (10.0 + PITCH_STEP))
	{
		int_pitch = (int)(floor(deg_pitch));

		*closeness = 1.0 - (deg_pitch - int_pitch);

		return int_pitch + NUM_NEGATIVE_PITCH_VALUES + 10;
	}
	else
	{
		int_pitch = (int)(floor(deg_pitch / PITCH_STEP));

		*closeness = 1.0 - ((deg_pitch - (int_pitch * PITCH_STEP)) / PITCH_STEP);

		return int_pitch - (10 / PITCH_STEP) + NUM_NEGATIVE_PITCH_VALUES + NUM_SINGLE_DEGREE_VALUES - 1;
	}
}


/** calculates a ballistics table for the specified weapon
 *  if output is non-NULL part of the table will also be written
 *  to that file
 */
void calculate_projectory(weapon* wpn, FILE* output)
{
	float
		dummy;

	int
		i,
		pitch_index = 0,
		zero_pitch = get_floor_pitch_index(0, &dummy),
		num_range_values;

	float
		pitch;

	ballistics_data** data = ballistics_table[wpn->mob.sub_type];

	num_range_values = (int)(weapon_database[wpn->mob.sub_type].max_range / RANGE_STEP) + 2;

	// initialize -90 and +90
	data[0] = (ballistics_data *) safe_malloc(sizeof(ballistics_data) * num_range_values);
	data[TOTAL_PITCH_INDICES - 1] = (ballistics_data *) safe_malloc(sizeof(ballistics_data) * num_range_values);

	for (i=0; i < num_range_values; i++)
	{
		data[0][i].drop_angle = 0.0;
		data[0][i].flight_time = 0.0;
		data[TOTAL_PITCH_INDICES-1][i].drop_angle = 0.0;
		data[TOTAL_PITCH_INDICES-1][i].flight_time = 0.0;
	}

	// write header for ballistics data:
	if (output)
		fputs("range     velocity    time   drop\n", output);

	// initialize all the other pitches
	pitch_index = 1;
	pitch = rad(-90.0f + PITCH_STEP);
	while (pitch_index < (TOTAL_PITCH_INDICES - 1))
	{
		float
			#ifdef DEBUG
			dummy,
			#endif
			time = 0.0,
			pitch_ratio,
			max_range,
			delta_time = 0.02f;

		int
			last_write_range = 0,
			range_mark = 0;


		ASSERT(get_floor_pitch_index(pitch + rad(0.1f), &dummy) == pitch_index);

		data[pitch_index] = (ballistics_data *) safe_malloc(sizeof(ballistics_data) * num_range_values);

		// initialize weapon for new firing
		wpn->weapon_lifetime = weapon_database[wpn->mob.sub_type].burn_time;
		wpn->mob.velocity = weapon_database[wpn->mob.sub_type].muzzle_velocity;

		wpn->mob.position.x = 0.0;
		wpn->mob.position.y = 0.0;
		wpn->mob.position.z = 0.0;

		get_identity_matrix3x3(wpn->mob.attitude);
		get_3d_transformation_matrix(wpn->mob.attitude, 0.0, pitch, 0.0);

		// initialize 0-range:
		data[pitch_index][range_mark].drop_angle = 0.0;
		data[pitch_index][range_mark].flight_time = 0.0;
		range_mark++;

		pitch_ratio = tan(pitch);

		// don't calculate out to entire range for very high or low pitch values (takes too long)
		max_range = min(weapon_database[wpn->mob.sub_type].max_range,
			weapon_database[wpn->mob.sub_type].max_range * cos(pitch) * 1.25f);

		while (wpn->mob.position.z < max_range)
		{
			float drop;

			time += delta_time;
			wpn->weapon_lifetime -= delta_time;
			move_unguided_weapon(wpn, &wpn->mob.position, delta_time, FALSE);

			// increase delta_time when projectile slows down a lot so as to ease amount of calculations a little
			if (wpn->mob.velocity < 150.0)
			{
				delta_time = 0.04f;
				if (wpn->mob.velocity < 75.0)
					delta_time = 0.1f;

				if (wpn->mob.velocity < 20.0)
					break;
			}

			if (wpn->mob.position.z > ((range_mark * RANGE_STEP) - 1.0)) // this is a range we want to sample
			{
				int
					stop_index = (int)((wpn->mob.position.z + 1) / RANGE_STEP);
				float
					drop_angle,
					expected_height;

				// adjust for expected height if there was no drop, so as to calculate real drop
				expected_height = pitch_ratio * wpn->mob.position.z;
				drop = (expected_height - wpn->mob.position.y) / wpn->mob.position.z;
				drop_angle = atan(drop);

				ASSERT(stop_index >= range_mark);

				// if the projectile is really fast we might actually have passed several sample values, so set the value for all of them
				for (; range_mark <= stop_index; range_mark++)
				{
					data[pitch_index][range_mark].drop_angle = drop_angle;
					data[pitch_index][range_mark].flight_time = time;
				}

				// output to file every WRITE_STEP steps
				if (output && wpn->mob.position.z > (last_write_range + WRITE_STEP - 1) && pitch_index == zero_pitch)
				{
					last_write_range += WRITE_STEP;
					fprintf(output, "%5d m  %6.1f m/s %5.1f s %6.1f m (%.1f degrees)\n",
						last_write_range, wpn->mob.velocity, time, -wpn->mob.position.y, deg(drop_angle));
				}

				if (range_mark == num_range_values)
					break;
			}
		}

		// if there's any spots left just copy the last to those (it will be wrong, but better than arbitrary values)
		for (; range_mark < num_range_values; range_mark++)
		{
			data[pitch_index][range_mark] = data[pitch_index][range_mark-1];
		}

		// we have smaller steps around 0 pitch to get a little better accuracy there
		pitch_index++;
		if (pitch_index <= NUM_NEGATIVE_PITCH_VALUES)
			pitch += rad(PITCH_STEP);
		else if (pitch_index < (NUM_NEGATIVE_PITCH_VALUES + NUM_SINGLE_DEGREE_VALUES))
			pitch += rad(1.0);
		else
			pitch += rad(PITCH_STEP);
	}
}

/** precalculates ballistics tables for all weapons with ballistic aiming.
 *  for certain range and angle intervals
 *
 *  The tables are calculated by simulating a firing and measuring drop at
 *  at various distances
 */
void generate_ballistics_tables(void)
{
	weapon
		wpn;

	entity_sub_types
		wpn_type;

	FILE*
		write_file = NULL;

	write_file = fopen("ballistics-data.txt", "w");

	fputs("Note: this file only lists ballistics data generated from the currently used GWUT File\n"
		  "Changing the values will have no effect, change the GWUT file to see change\n"
		  "This file can be used to help getting good values for the GWUT file\n\n", write_file);

	for (wpn_type = 1; wpn_type <= LAST_WEAPON; wpn_type++)
	{
		if (weapon_database[wpn_type].aiming_type == WEAPON_AIMING_TYPE_CALC_LEAD_AND_BALLISTIC)
		{
			if (write_file)
			{
				fprintf(write_file, "\n%s   max_range: %.0f m, muzzle velocity: %.0f m/s, drag: %.2f\n",
					weapon_database[wpn_type].full_name,
					weapon_database[wpn_type].max_range,
					weapon_database[wpn_type].muzzle_velocity,
					weapon_database[wpn_type].drag_factor);
			}

			wpn.mob.sub_type = wpn_type;
			calculate_projectory(&wpn, write_file);
		}

		if (write_file)
			fflush(write_file);
	}

	if (write_file)
		fclose(write_file);
}

void delete_ballistics_tables(void)
{
	entity_sub_types wpn_type;
	unsigned pitch_index;

	for (wpn_type = 1; wpn_type <= LAST_WEAPON; wpn_type++)
		if (weapon_database[wpn_type].aiming_type == WEAPON_AIMING_TYPE_CALC_LEAD_AND_BALLISTIC)
		{
			for(pitch_index = 0; pitch_index < TOTAL_PITCH_INDICES; pitch_index++)
			{
				if (ballistics_table[wpn_type][pitch_index])
					safe_free(ballistics_table[wpn_type][pitch_index]);
				ballistics_table[wpn_type][pitch_index] = NULL;
			}
		}
}

/**
 * Looks up om the ballistics tables how much drop and time of flight a projectile
 * of wpn_type will have at the given range.
 * As we probably don't have the value for the exact range/pitch requested it
 * will make a weighted average of the closeset values we have.
 */
int get_ballistic_pitch_deflection(entity_sub_types wpn_type, float range, float height_diff_or_pitch, float* aiming_pitch, float* time_of_flight, int simplified, int fixed_pitch)
{
	float
		pitch_delta,
		range_error,
		range_delta,
		drop_compensation = 0.0,
		straight_pitch = fixed_pitch ? height_diff_or_pitch : -atan(height_diff_or_pitch / range);

	int
		iterations,
		i,
		pitch_index,
		range_index;

	ASSERT(time_of_flight);
	ASSERT(aiming_pitch);

	if (fixed_pitch)
		iterations = 1;
	else if (simplified)
		iterations = 3;
	else
		iterations = 5;

	if (!ballistics_table[wpn_type][0])
	{
		ASSERT(FALSE);
		return FALSE;
	}

	ASSERT(range >= 0.0);

	if (range <= 0.1f)
	{
		*aiming_pitch = straight_pitch;
		*time_of_flight = 0.0;
		return TRUE;
	}

	range = bound(range, 0.01f, weapon_database[wpn_type].max_range);
	range_index = (int)(range / RANGE_STEP);
	range_error = range - (range_index * RANGE_STEP);
	range_delta = 1.0 - (range_error / RANGE_STEP);   // normalize to [0..1]

	#if DEBUG_MODULE
	debug_log("range: %.0f (%.0f) closeness: %.02f, height_difference: %.0f", range, range_index*RANGE_STEP, range_delta, height_diff_or_pitch);
	#endif

	// refine drop_compensation - do it several times because as we adjust
	// cannon pitch we have to use a different ballistics table.  Do it a few
	// times so that it stabalizes somewhat
	for (i = 0; i < iterations; i++)
	{
		float use_pitch = min(straight_pitch + drop_compensation, rad(90.0f));

		pitch_index = get_floor_pitch_index(use_pitch, &pitch_delta);
		ASSERT(pitch_index >= 0 && pitch_index < TOTAL_PITCH_INDICES);
		drop_compensation = ballistics_table[wpn_type][pitch_index][range_index].drop_angle;

		if (drop_compensation > rad(45.0))
			return FALSE;

		*time_of_flight = ballistics_table[wpn_type][pitch_index][range_index].flight_time;
	}

	// average between next pitch and range:
	if (!simplified)
	{
		ballistics_data
			pitch_compensation[2],
			compensation_grid[2][2];

		int next_pitch_index = min(pitch_index + 1, TOTAL_PITCH_INDICES-1);

		// first average the next ranges
		compensation_grid[0][0].drop_angle = drop_compensation;
		compensation_grid[0][0].flight_time = *time_of_flight;

		compensation_grid[0][1].drop_angle = ballistics_table[wpn_type][pitch_index][range_index+1].drop_angle;
		compensation_grid[0][1].flight_time = ballistics_table[wpn_type][pitch_index][range_index+1].flight_time;

		compensation_grid[1][0].drop_angle = ballistics_table[wpn_type][next_pitch_index][range_index].drop_angle;
		compensation_grid[1][0].flight_time = ballistics_table[wpn_type][next_pitch_index][range_index].flight_time;

		compensation_grid[1][1].drop_angle = ballistics_table[wpn_type][next_pitch_index][range_index+1].drop_angle;
		compensation_grid[1][1].flight_time = ballistics_table[wpn_type][next_pitch_index][range_index+1].flight_time;

		// then average oover next pitch
		pitch_compensation[0].drop_angle = (pitch_delta * compensation_grid[0][0].drop_angle) + ((1 - pitch_delta) * compensation_grid[1][0].drop_angle);
		pitch_compensation[0].flight_time = (pitch_delta * compensation_grid[0][0].flight_time) + ((1 - pitch_delta) * compensation_grid[1][0].flight_time);

		pitch_compensation[1].drop_angle = (pitch_delta * compensation_grid[0][1].drop_angle) + ((1 - pitch_delta) * compensation_grid[1][1].drop_angle);
		pitch_compensation[1].flight_time = (pitch_delta * compensation_grid[0][1].flight_time) + ((1 - pitch_delta) * compensation_grid[1][1].flight_time);

		// and finally get a total
		drop_compensation = (range_delta * pitch_compensation[0].drop_angle) + ((1 - range_delta) * pitch_compensation[1].drop_angle);
		*time_of_flight = (range_delta * pitch_compensation[0].flight_time) + ((1 - range_delta) * pitch_compensation[1].flight_time);

		#if DEBUG_MODULE
		debug_log("average over drop: (%.3f, %.3f, %.3f, %.3f) result: %.3f",
			deg(compensation_grid[0][0].drop_angle), deg(compensation_grid[0][1].drop_angle),
			deg(compensation_grid[1][0].drop_angle), deg(compensation_grid[1][1].drop_angle),
			deg(drop_compensation));
		#endif
	}

	*aiming_pitch = straight_pitch + drop_compensation;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

