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

#define HELLFIRE_LOBL_CLIMB_RATIO	(0.14)
#define HELLFIRE_LOBL_DIVE_RATIO	(0.31)
#define HELLFIRE_LOAL_CLIMB1_RATIO	(0.084)
#define HELLFIRE_LOAL_CLIMB2_RATIO	(0.22)
#define HELLFIRE_LOAL_DIVE_RATIO	(0.5)
#define HELLFIRE_LOAL_CLIMB1_TIME	(0.0)
#define HELLFIRE_LOAL_CLIMB2_TIME	(-10.0)
#define HELLFIRE_LOAL_XZ	(1000.0)
#define HELLFIRE_LOAL_CLIMB1_Y		(300.0)
#define HELLFIRE_LOAL_CLIMB2_Y		(40.0)
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
#define VELOCITY_TESTS 1 + 4
#define VELOCITY_TEST_STEP 50.0
#define NUM_SINGLE_DEGREE_VALUES 61
#define NUM_NEGATIVE_PITCH_VALUES (((90 - (NUM_SINGLE_DEGREE_VALUES - 1) / 2) / PITCH_STEP))
#define TOTAL_PITCH_INDICES (2*NUM_NEGATIVE_PITCH_VALUES + NUM_SINGLE_DEGREE_VALUES)
#define LAST_WEAPON (NUM_ENTITY_SUB_TYPE_WEAPONS - 1)

typedef struct
{
	float drop_angle;
	float flight_time;
} ballistics_data;

static ballistics_data*
	ballistics_table[VELOCITY_TESTS][LAST_WEAPON+1][TOTAL_PITCH_INDICES + 2];

static void update_guided_weapon (	weapon* raw, vec3d* new_position, float delta_time, float turn_rate, float range, int wind);
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

	if ((weapon_velocity > 0.001) && (target_true_velocity > 0.001))
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

static void move_guided_weapon (entity *en, vec3d *new_position, vec3d *intercept_point, int loal)
{
	weapon
		*raw;

	float
		length,
		cos_turn_demand,
		turn_demand,
		max_turn_rate,
		turn_rate,
		inhibit_damp_factor = 1,
		time_elapsed,
		current_life_time;
	int
		engine_mode = 0,
		target_lost = FALSE;
	vec3d
		uvec_intercept_point;

	matrix3x3
		m1,
		m2;

	ASSERT (en);

	ASSERT (new_position);

	ASSERT (intercept_point);

	raw = (weapon *) get_local_entity_data (en);

	if (raw->weapon_lifetime - weapon_database[raw->mob.sub_type].sustain_time > 0)
		engine_mode = 2; // boost
	else if (raw->weapon_lifetime > 0)
		engine_mode = 1; // sustain
	
	current_life_time = weapon_database[raw->mob.sub_type].boost_time + weapon_database[raw->mob.sub_type].sustain_time - raw->weapon_lifetime;

	////////////////////////////////////////
	//
	// move guided powered/guided unpowered weapon (ignore gravity)
	//
	////////////////////////////////////////

	#if DEBUG_MODULE

	create_rotated_debug_3d_object (intercept_point, rad (0.0), rad (0.0), rad (0.0), OBJECT_3D_INTERCEPT_POINT_RED, 0.0, DEBUG_3D_OBJECT_SCALE);

	#endif

	// adjust for high trajectory

	if (weapon_database[raw->mob.sub_type].flight_profile_or_self_destr == 1 && raw->missile_phase != MISSILE_FINAL_PHASE)
	{
		float range, dive_ratio;
		vec3d
			*weapon_position;

		weapon_position = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

		range = get_2d_range (weapon_position, intercept_point);

		dive_ratio = (weapon_position->y - intercept_point->y) / range;
//		debug_log("DIVE_RATIO %f, loal mode %i, phase %i", dive_ratio, raw->loal_mode, raw->missile_phase);

		if (raw->loal_mode && !loal)
		{
				switch (raw->missile_phase)
				{
				case MISSILE_PHASE1:
					if (dive_ratio > HELLFIRE_LOAL_DIVE_RATIO || range < 1800)
					{
						raw->missile_phase = MISSILE_FINAL_PHASE;
						break;
					}
					
					if (dive_ratio < HELLFIRE_LOAL_CLIMB1_RATIO && range > 3000)
					{
					// initial climb of 30%
						float new_aim_y = weapon_position->y + range * 0.3;
						intercept_point->y = max(new_aim_y, intercept_point->y);
						break;
					}

					raw->missile_phase = MISSILE_PHASE2;
					// fall through

				case MISSILE_PHASE2:
					if (dive_ratio > HELLFIRE_LOAL_DIVE_RATIO || range < 1500)
					{
						raw->missile_phase = MISSILE_FINAL_PHASE;
						break;
					}

					if (dive_ratio < HELLFIRE_LOAL_CLIMB2_RATIO && range > 2500)
					{
						// seconds phase climb at 4%
						float new_aim_y = weapon_position->y + range * 0.04;
						intercept_point->y = max(new_aim_y, intercept_point->y);

						break;
					}

					raw->missile_phase = MISSILE_PHASE3;
					// fall through

				case MISSILE_PHASE3:
					if (dive_ratio > HELLFIRE_LOAL_DIVE_RATIO || range < 1000)
					{
						raw->missile_phase = MISSILE_FINAL_PHASE;
						break;
					}
					else
					{
						// third phase dive at 20%
						float new_aim_y = weapon_position->y - range * 0.2;
						intercept_point->y = max(new_aim_y, intercept_point->y);

						break;
					}
				default:
					ASSERT(FALSE);
				}
		}
		else if (!raw->loal_mode)  // lobl mode
		{
				switch (raw->missile_phase)
				{
				case MISSILE_PHASE1:
					if (dive_ratio > HELLFIRE_LOBL_DIVE_RATIO || range < 2000)
					{
						raw->missile_phase = MISSILE_FINAL_PHASE;
						break;
					}

					if (dive_ratio < HELLFIRE_LOBL_CLIMB_RATIO && range > 2500)
					{
						// intial phase climb at 7%
						float new_aim_y = weapon_position->y + range * 0.07;
						intercept_point->y = max(new_aim_y, intercept_point->y);

						break;
					}

					raw->missile_phase = MISSILE_PHASE2;
				case MISSILE_PHASE2:
					if (dive_ratio > HELLFIRE_LOBL_DIVE_RATIO || range < 1500)
					{
						raw->missile_phase = MISSILE_FINAL_PHASE;
						break;
					}
					else
					{
						// second phase dive at 3%
						float new_aim_y = weapon_position->y - range * 0.03;
						intercept_point->y = max(new_aim_y, intercept_point->y);

						break;
					}

//					raw->missile_phase = MISSILE_FINAL_PHASE;

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

	// make higher trajectory /thealx/
	
	if (weapon_database[raw->mob.sub_type].flight_profile_or_self_destr != 1)
	{
		time_elapsed = min (2, 0.5 * (max(length - 500, 0) / raw->mob.velocity)); // back to normal trajectory if < 4 sec elapsed
		uvec_intercept_point.y += 5 * time_elapsed * time_elapsed / 2; // flightpath rised 10m
	}

	//
	// guard against divide by zero (weapon must be very close to the intercept point)
	//

	if (length < max(weapon_database[raw->mob.sub_type].detonation_radius, 1))
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
		if (current_life_time > weapon_database[raw->mob.sub_type].inhibit_time && weapon_database[raw->mob.sub_type].detonation_radius >= length)  // weapon armed after 1 second
		{

			#if DEBUG_MODULE
				debug_log("%s overshot target (%0.1f degrees, limit %.2f, range %.2f, detonation radius %.2f", weapon_database[raw->mob.sub_type].full_name, deg(acos(cos_turn_demand), length, weapon_database[raw->mob.sub_type].detonation_radius),
					deg(acos(weapon_database[raw->mob.sub_type].max_seeker_limit)));
			#endif

			raw->kill_code = WEAPON_KILL_CODE_OVERSHOT_TARGET;

			return;
		}
		else
			target_lost = TRUE;
	}

	if (!target_lost)
	{

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

		//
		// damp turn rate during inhibit period
		//

		if (current_life_time < weapon_database[raw->mob.sub_type].inhibit_time)
		{
			//
			// damp using y = x * x curve
			//

			ASSERT (weapon_database[raw->mob.sub_type].inhibit_time > 0.0);

			inhibit_damp_factor = current_life_time / weapon_database[raw->mob.sub_type].inhibit_time;

			inhibit_damp_factor *= inhibit_damp_factor;

		}
		else if (weapon_database[raw->mob.sub_type].flight_profile_or_self_destr == 1 && raw->missile_phase != MISSILE_FINAL_PHASE)
		{
			// arneh - limit turn rate in first phases of hellfire trajectory to get a smoother arc
			
			inhibit_damp_factor = 0.5;
		}

		max_turn_rate = G * weapon_database[raw->mob.sub_type].g_max / raw->mob.velocity * inhibit_damp_factor;
		turn_rate = bound (turn_demand, - max_turn_rate, max_turn_rate);
		get_3d_transformation_matrix (m1, turn_rate * get_delta_time (), 0.0, 0.0);
		multiply_matrix3x3_matrix3x3 (m2, m1, raw->mob.attitude);

		//
		// set roll to zero to remove jitter on weapon view
		//

		get_3d_transformation_matrix (raw->mob.attitude, get_heading_from_attitude_matrix (m2), get_pitch_from_attitude_matrix (m2), 0.0);
	}
	else
		turn_rate = 0;

	update_guided_weapon (raw, new_position, get_delta_time (), turn_rate, length, TRUE);
	
//	debug_log("weapon velocity %f, turn rate %f, limit %f, range %f, time passed %f", raw->mob.velocity, deg(turn_demand), deg(max_turn_rate), length, weapon_database[raw->mob.sub_type].boost_time - raw->weapon_lifetime);

}

static void update_guided_weapon (weapon* raw, vec3d* new_position, float delta_time, float turn_rate, float range, int wind)
{
	float
		acceleration = 0,
		displacement_modifier,
		current_life_time,
		weapon_weight = get_weapon_current_weight(raw->weapon_lifetime, raw->mob.sub_type);
	int 
		engine_mode = 0;
	vec3d
		wind_velocity;

	if (raw->weapon_lifetime - weapon_database[raw->mob.sub_type].sustain_time > 0)
		engine_mode = 2; // boost
	else if (raw->weapon_lifetime > 0)
		engine_mode = 1; // sustain
	
	current_life_time = weapon_database[raw->mob.sub_type].boost_time + weapon_database[raw->mob.sub_type].sustain_time - raw->weapon_lifetime;
	displacement_modifier = 25 * delta_time * bound ((range - 500) / 1000, 0, 1) * bound(min(current_life_time, raw->weapon_lifetime) / weapon_database[raw->mob.sub_type].inhibit_time, 0, 1);

	//
	// acceleration
	//

	if (engine_mode == 2)
		acceleration = weapon_database[raw->mob.sub_type].boost_power / weapon_weight;
	else if (engine_mode == 1)
		acceleration = weapon_database[raw->mob.sub_type].sustain_power / weapon_weight;
	acceleration -= get_weapon_drag(raw->mob.velocity, raw->mob.position.y, weapon_database[raw->mob.sub_type].diameter, weapon_database[raw->mob.sub_type].drag_coefficient) / weapon_weight;
	acceleration -= fabs(turn_rate) * get_delta_time () * raw->mob.velocity;
	if (!weapon_database[raw->mob.sub_type].ignore_gravity)
		acceleration -= sin(get_pitch_from_attitude_matrix(raw->mob.attitude)) * G;

	if (acceleration > 9999 || acceleration < -9999)
		acceleration = 0;

	// udate velocity

	raw->mob.velocity = bound (raw->mob.velocity + acceleration * delta_time, 0, 1.5 * weapon_database[raw->mob.sub_type].cruise_velocity);

	// wind

	if (wind)
	{
		get_session_wind_velocity_at_point (&raw->mob.position, &wind_velocity);

		wind_velocity.x = delta_time * get_weapon_drag(wind_velocity.x, raw->mob.position.y, weapon_database[raw->mob.sub_type].diameter, weapon_database[raw->mob.sub_type].drag_coefficient * 1.5) / weapon_weight;	
		wind_velocity.y = delta_time * get_weapon_drag(wind_velocity.y, raw->mob.position.y, weapon_database[raw->mob.sub_type].diameter, weapon_database[raw->mob.sub_type].drag_coefficient * 1.5) / weapon_weight;	
		wind_velocity.z = delta_time * get_weapon_drag(wind_velocity.z, raw->mob.position.y, weapon_database[raw->mob.sub_type].diameter, weapon_database[raw->mob.sub_type].drag_coefficient * 1.5) / weapon_weight;	
	}
	else
		wind_velocity.x = wind_velocity.y = wind_velocity.z = 0;
		
	// motion vector

	raw->mob.motion_vector.x = raw->mob.zv.x * raw->mob.velocity + wind_velocity.x;
	raw->mob.motion_vector.y = raw->mob.zv.y * raw->mob.velocity + wind_velocity.y;
	raw->mob.motion_vector.z = raw->mob.zv.z * raw->mob.velocity + wind_velocity.z;

	// position

	new_position->x += raw->mob.motion_vector.x * delta_time;
	new_position->y += raw->mob.motion_vector.y * delta_time;
	new_position->z += raw->mob.motion_vector.z * delta_time;
	
	// flightpath adjustments

	if (raw->weapon_lifetime > 0.0 && displacement_modifier)
	{
		vec3d displacement;
		float spiral = (weapon_database[raw->mob.sub_type].flight_profile_or_self_destr == 2),
				deviation = weapon_database[raw->mob.sub_type].flightpath_deviation;

		displacement.x = displacement.y = displacement.z = 0;

		if (spiral)
		{
			float timer = wrap_angle(0.75 * PI2 * raw->weapon_lifetime);

			displacement.x -= displacement_modifier * (sin(timer) > 0 ? 1 : - 1) * sqrt(sin(timer));
			displacement.y += displacement_modifier * (cos(timer) > 0 ? 1 : - 1) * cos(timer) * cos(timer);
		}

		if (deviation)
		{
			float
				angle_x = sin((wrap_angle(get_3d_vector_magnitude(new_position) / 222) + wrap_angle(get_system_time() / 1000)) / 2),
				angle_y = sin((wrap_angle(get_3d_vector_magnitude(new_position) / 111) + wrap_angle(get_system_time() / 2000)) / 2);

			displacement.x += deviation * displacement_modifier * sign(angle_x) * sin(angle_x) * sin(angle_x);
			displacement.y += deviation * displacement_modifier * sign(angle_y) * sin(angle_y) * sin(angle_y);
//			debug_log("angle x %f y %f", angle_x, angle_y);
		}
	
		multiply_matrix3x3_vec3d(&displacement, raw->mob.attitude, &displacement);

		new_position->x += bound(displacement.x, - delta_time * (10 * spiral + deviation), delta_time * (10 * spiral + deviation));
		new_position->y += bound(displacement.y, - delta_time * (10 * spiral + deviation), delta_time * (10 * spiral + deviation));
		new_position->z += bound(displacement.z, - delta_time * (10 * spiral + deviation), delta_time * (10 * spiral + deviation));
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void move_unguided_weapon (weapon* raw, vec3d *new_position, float delta_time, int wind)
{
	float
		acceleration = 0,
		heading,
		pitch,
		h_vel,
		v_vel,
		parachute_modifier = 1,
		weapon_weight;
	vec3d
		wind_velocity;
	
	ASSERT (raw);
	ASSERT (new_position);
	
	weapon_weight = get_weapon_current_weight(raw->weapon_lifetime, raw->mob.sub_type);

	// acceleration

	if (raw->weapon_lifetime - weapon_database[raw->mob.sub_type].sustain_time > 0) // boost
		acceleration += weapon_database[raw->mob.sub_type].boost_power / weapon_weight;
	else if (raw->weapon_lifetime > 0) // sustain
		acceleration += weapon_database[raw->mob.sub_type].sustain_power / weapon_weight;

	switch(raw->mob.sub_type) // speed up eject seat if parachute is closed
		case ENTITY_SUB_TYPE_WEAPON_HOKUM_PILOT:
		case ENTITY_SUB_TYPE_WEAPON_HOKUM_CO_PILOT:
		case ENTITY_SUB_TYPE_WEAPON_CRATE:
		{
			if (raw->parachute_status != PARACHUTE_STATUS_OPEN3)
				parachute_modifier = 0.05;
			break;
		}
			
	acceleration -= get_weapon_drag(raw->mob.velocity, raw->mob.position.y, weapon_database[raw->mob.sub_type].diameter * parachute_modifier, weapon_database[raw->mob.sub_type].drag_coefficient) / weapon_weight;

	if (acceleration > 9999 || acceleration < -9999)
		acceleration = 0;

	// update velocity

	raw->mob.velocity = bound (raw->mob.velocity + acceleration * delta_time, 0.0, 1.5 * weapon_database[raw->mob.sub_type].cruise_velocity);

	// wind

	if (wind)
	{
		get_session_wind_velocity_at_point (&raw->mob.position, &wind_velocity);
	
		wind_velocity.x = delta_time * get_weapon_drag(wind_velocity.x, raw->mob.position.y, weapon_database[raw->mob.sub_type].diameter * parachute_modifier, weapon_database[raw->mob.sub_type].drag_coefficient * 1.5) / weapon_weight;	
		wind_velocity.y = delta_time * get_weapon_drag(wind_velocity.y, raw->mob.position.y, weapon_database[raw->mob.sub_type].diameter * parachute_modifier, weapon_database[raw->mob.sub_type].drag_coefficient * 1.5) / weapon_weight;	
		wind_velocity.z = delta_time * get_weapon_drag(wind_velocity.z, raw->mob.position.y, weapon_database[raw->mob.sub_type].diameter * parachute_modifier, weapon_database[raw->mob.sub_type].drag_coefficient * 1.5) / weapon_weight;	
	}
	else
		wind_velocity.x = wind_velocity.y = wind_velocity.z = 0;
	
	// motion vector

	raw->mob.motion_vector.x = raw->mob.zv.x * raw->mob.velocity + wind_velocity.x;
	raw->mob.motion_vector.y = raw->mob.zv.y * raw->mob.velocity + wind_velocity.y;
	raw->mob.motion_vector.z = raw->mob.zv.z * raw->mob.velocity + wind_velocity.z;

	// position

	new_position->x += raw->mob.motion_vector.x * delta_time;
	new_position->y += raw->mob.motion_vector.y * delta_time;
	new_position->z += raw->mob.motion_vector.z * delta_time;

	ASSERT(new_position->y >= -1000000000000.0);  // mostly just tests for -nan and -inf which happens with buggy floating point calculations

	// apply gravity (after moving weapon)

	if (!weapon_database[raw->mob.sub_type].ignore_gravity)
	{
		heading = get_heading_from_attitude_matrix (raw->mob.attitude);

		pitch = get_pitch_from_attitude_matrix (raw->mob.attitude);

		h_vel = cos (pitch) * raw->mob.velocity;

		v_vel = (sin (pitch) * raw->mob.velocity) - (G * delta_time);

		raw->mob.velocity = bound (sqrt ((h_vel * h_vel) + (v_vel * v_vel)), 0.0, 1.5 * weapon_database[raw->mob.sub_type].cruise_velocity);

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
				#if DEBUG_MODULE
//				debug_log("Finding parent's target (parent: %p, parent type %s", raw->launched_weapon_link.parent, entity_type_names[raw->launched_weapon_link.parent->type]);
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

	raw->mob.velocity = bound (raw->mob.velocity, 0.0, 1.5 * weapon_database[raw->mob.sub_type].cruise_velocity);

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

	cruise_time_error = 0.5 * frand1x (&seed) * weapon_database[raw->mob.sub_type].cruise_time_max_error;

	if (raw->weapon_lifetime <= - weapon_database[raw->mob.sub_type].cruise_time - cruise_time_error) // this is the end of the journey..
	{
		if (weapon_database[raw->mob.sub_type].flight_profile_or_self_destr == 3)
			raw->kill_code = WEAPON_KILL_CODE_SELF_DESTRUCT;
		else
			raw->kill_code = WEAPON_KILL_CODE_EXHAUSTED;
		
		#if DEBUG_MODULE
			debug_log("Weapon destroyed due to time exceeded");
		#endif

		return;
	}

	if (raw->decoy_timer && !weapon_database[raw->mob.sub_type].decoy_type && raw->weapon_lifetime <= - raw->decoy_timer) // time for fireworks!
	{
		if (weapon_database[raw->mob.sub_type].warhead_type == WEAPON_WARHEAD_TYPE_CONVENTIONAL_MUNITIONS) // create submunitions if it's needed
		{
			viewpoint vp;
			int count = (int) weapon_database[raw->mob.sub_type + 1].burst_duration;
		
			memcpy ( vp.attitude, raw->mob.attitude, sizeof ( matrix3x3 ) );
			vp.position = raw->mob.position;

			while (count--)
				create_client_server_entity_submunition_weapon(raw->launched_weapon_link.parent, raw->mob.target_link.parent, raw->mob.sub_type + 1, ENTITY_INDEX_DONT_CARE, &vp, raw->mob.velocity * weapon_database[raw->mob.sub_type + 1].acquire_parent_forward_velocity);
		}

		if (weapon_database[raw->mob.sub_type].flight_profile_or_self_destr == 3)
			raw->kill_code = WEAPON_KILL_CODE_SELF_DESTRUCT;
		
		raw->decoy_timer = 0;
	
		#if DEBUG_MODULE > 1
			debug_log("Weapon timer is reached");
		#endif

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
					if (weapon_database[raw->mob.sub_type].flight_profile_or_self_destr != 1)
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
					if (weapon_database[raw->mob.sub_type].flight_profile_or_self_destr == 1)
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
				&& (!get_local_entity_int_value(raw->launched_weapon_link.parent, INT_TYPE_LASER_ON) || !get_local_entity_int_value (raw->launched_weapon_link.parent, INT_TYPE_LOS_TO_TARGET)))
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
				&& (!get_local_entity_int_value(raw->launched_weapon_link.parent, INT_TYPE_LASER_ON) || !get_local_entity_int_value (raw->launched_weapon_link.parent, INT_TYPE_LOS_TO_TARGET)))
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
		case WEAPON_GUIDANCE_TYPE_WIRE_GUIDED:
		////////////////////////////////////////
		{
			check_guidance_source (raw, en, FALSE);

			if (get_local_entity_int_value (raw->launched_weapon_link.parent, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI
				&& !get_local_entity_int_value (raw->launched_weapon_link.parent, INT_TYPE_LOS_TO_TARGET))
			{
				intercept_point_valid = FALSE;
			}
			else
				intercept_point_valid = get_target_position (en, &intercept_point, TRUE);

			break;
		}
	}

	////////////////////////////////////////
	//
	// movement
	//
	////////////////////////////////////////

	if (intercept_point_valid && (raw->weapon_lifetime > 0 || raw->mob.velocity > 200))
	{
		move_guided_weapon (en, &new_position, &intercept_point, FALSE);
	}
	else
	{
		// unless missile is a LOAL hellfire in phase 1 or 2, move as an unguided weapon when no target
		if (!raw->loal_mode || raw->missile_phase > MISSILE_PHASE2 || (raw->weapon_lifetime <= 0 && raw->mob.velocity <= 200))
		{
			weapon* weapon = (struct WEAPON *) get_local_entity_data (en);
			
			move_unguided_weapon (weapon, &new_position, get_delta_time(), weapon_database[raw->mob.sub_type].aiming_type != 2);
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
				intercept_point.x += HELLFIRE_LOAL_XZ * raw->mob.zv.x;
				intercept_point.y += HELLFIRE_LOAL_CLIMB1_Y;
				intercept_point.z += HELLFIRE_LOAL_XZ * raw->mob.zv.z;
			}
			else if (raw->weapon_lifetime > HELLFIRE_LOAL_CLIMB2_TIME)
			{
				intercept_point.x += HELLFIRE_LOAL_XZ * raw->mob.zv.x;
				intercept_point.y += HELLFIRE_LOAL_CLIMB2_Y;
				intercept_point.z += HELLFIRE_LOAL_XZ * raw->mob.zv.z;
			}
			else
			{
				intercept_point.x += HELLFIRE_LOAL_XZ * raw->mob.zv.x;
				intercept_point.y += HELLFIRE_LOAL_DIVE_Y;
				intercept_point.z += HELLFIRE_LOAL_XZ * raw->mob.zv.z;
			}

			move_guided_weapon (en, &new_position, &intercept_point, TRUE);

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
				int target_hit = collision_test_weapon_with_given_target (en, raw->mob.target_link.parent, &old_position, &new_position); // 1 - target, 2 - something else
				if (target_hit == 1)
					raw->kill_code = WEAPON_KILL_CODE_HIT_TARGET;
				else if (target_hit == 2)
					raw->kill_code = WEAPON_KILL_CODE_SELF_DESTRUCT;
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
			dx = (new_position.x - old_position.x) * 0.1;
			dy = (new_position.y - old_position.y) * 0.1;
			dz = (new_position.z - old_position.z) * 0.1;

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
		int_pitch,
		i_elevation = (NUM_SINGLE_DEGREE_VALUES - 1) / 2;
	float
		f_elevation = (NUM_SINGLE_DEGREE_VALUES - 1) / 2;
	

	ASSERT(closeness);

	if (deg_pitch < - f_elevation)
	{
		int_pitch = (int)(floor(deg_pitch / PITCH_STEP));

		*closeness = 1.0 - ((deg_pitch - (int_pitch * PITCH_STEP)) / PITCH_STEP);

		return int_pitch + (i_elevation / PITCH_STEP) + NUM_NEGATIVE_PITCH_VALUES;
	}
	else if (deg_pitch < (f_elevation + PITCH_STEP))
	{
		int_pitch = (int)(floor(deg_pitch));

		*closeness = 1.0 - (deg_pitch - int_pitch);

		return int_pitch + NUM_NEGATIVE_PITCH_VALUES + i_elevation;
	}
	else
	{
		int_pitch = (int)(floor(deg_pitch / PITCH_STEP));

		*closeness = 1.0 - ((deg_pitch - (int_pitch * PITCH_STEP)) / PITCH_STEP);

		return int_pitch - (i_elevation / PITCH_STEP) + NUM_NEGATIVE_PITCH_VALUES + NUM_SINGLE_DEGREE_VALUES - 1;
	}
}


/** calculates a ballistics table for the specified weapon
 *  if output is non-NULL part of the table will also be written
 *  to that file
 */
void calculate_projectory(weapon* wpn, FILE* output, int velocity_test)
{
	int
		i,
		pitch_index = 0,
		num_range_values;

	float
		pitch,
		test_velocity[256],
		test_time[256],
		test_drop[256],
		test_range[256],
		test_drop_angle[256],
		test_drag[256],
		max_speed = 0;
	
	ballistics_data** data = ballistics_table[velocity_test][wpn->mob.sub_type];

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
	
	for (i=0; i < 256; i++)
	{
		test_velocity[i] = test_time[i] = test_drop[i] = test_drop_angle[i] = test_drag[i] = 0.0;
		test_range[i] = weapon_database[wpn->mob.sub_type].max_range;
	}	

	// initialize all the other pitches
	pitch_index = 1;
	pitch = rad(-90.0 + PITCH_STEP);
	while (pitch_index < (TOTAL_PITCH_INDICES - 1))
	{
		float
			dummy,
			time = 0.0,
			pitch_ratio,
			max_range,
			delta_time = 0.02;

		int
			range_mark = 0,
			write_step = 0,
			write_range = WRITE_STEP;
		
		data[pitch_index] = (ballistics_data *) safe_malloc(sizeof(ballistics_data) * num_range_values);

		if (velocity_test && (weapon_database[wpn->mob.sub_type].weapon_class & WEAPON_CLASS_SURFACE_TO_AIR || weapon_database[wpn->mob.sub_type].weapon_class & WEAPON_CLASS_SURFACE_TO_SURFACE))
		{
			ballistics_data
					*source_ptr = ballistics_table[velocity_test - 1][wpn->mob.sub_type][pitch_index],
					*dest_ptr = ballistics_table[velocity_test][wpn->mob.sub_type][pitch_index];
		
			memcpy(dest_ptr, source_ptr, sizeof(ballistics_data) * num_range_values);
			pitch_index++;
			continue;
		}
		
		ASSERT(get_floor_pitch_index(pitch + rad(0.1), &dummy) == pitch_index);

		// initialize weapon for new firing
		wpn->weapon_lifetime = weapon_database[wpn->mob.sub_type].boost_time + weapon_database[wpn->mob.sub_type].sustain_time;
		wpn->mob.velocity = weapon_database[wpn->mob.sub_type].muzzle_velocity + velocity_test * VELOCITY_TEST_STEP;

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

		while (TRUE)
		{
			float
				fake_y,
				fake_z,
				expected_height;
			vec2d magnitude[2];

			time += delta_time;
			wpn->weapon_lifetime -= delta_time;
			move_unguided_weapon(wpn, &wpn->mob.position, delta_time, FALSE);

			if (wpn->weapon_lifetime < - weapon_database[wpn->mob.sub_type].cruise_time ||
					wpn->mob.position.y < max(- weapon_database[wpn->mob.sub_type].max_range, - 4000) ||
					wpn->mob.velocity < 20.0 && wpn->weapon_lifetime < 0)
				break;
			
			// increase delta_time when projectile slows down a lot so as to ease amount of calculations a little

			if (wpn->mob.velocity < 75.0)
				delta_time = 0.1;
			else if (wpn->mob.velocity < 150.0)
				delta_time = 0.04;
			else
				delta_time = 0.02;

			if (pitch >= 0 && pitch <= PI / 4 && !velocity_test) // collect data for statistics, only for first velocity test
			{
				if (wpn->mob.velocity > max_speed)
					max_speed = wpn->mob.velocity;

				if (wpn->mob.position.z >= write_range - 1)
				{
					magnitude[0].x = test_range[write_step] - range_mark * RANGE_STEP;
					magnitude[0].y = test_drop[write_step];
					magnitude[1].x = wpn->mob.position.z - range_mark * RANGE_STEP;
					magnitude[1].y = wpn->mob.position.y;

					if(get_2d_vector_magnitude(&magnitude[1]) < get_2d_vector_magnitude(&magnitude[0]))
					{
						test_velocity[write_step] = wpn->mob.velocity;
						test_time[write_step] = time;
						test_drop[write_step] = wpn->mob.position.y;
						test_range[write_step] = wpn->mob.position.z;
						test_drop_angle[write_step] = pitch - atan(test_drop[write_step]/test_range[write_step]);
						test_drag[write_step] = get_weapon_drag(wpn->mob.velocity, wpn->mob.position.y, weapon_database[wpn->mob.sub_type].diameter, weapon_database[wpn->mob.sub_type].drag_coefficient) / get_weapon_current_weight(wpn->weapon_lifetime, wpn->mob.sub_type);
					}
					
					if (wpn->mob.position.z >= 10000)
						write_range += WRITE_STEP * 4;
					else if (wpn->mob.position.z >= 5000)
						write_range +=  WRITE_STEP * 2;
					else
						write_range += WRITE_STEP;
					
					write_step++;
				}
			}

			expected_height = pitch_ratio * wpn->mob.position.z;
			fake_y = wpn->mob.position.y + cos(pitch) * (expected_height - wpn->mob.position.y);
			fake_z = wpn->mob.position.z - sin(pitch) * (expected_height - wpn->mob.position.y);
			
			if (fake_z > ((range_mark * RANGE_STEP) - 1.0)) // this is a range we want to sample
			{
				int
					stop_index = (int)((fake_z + 1) / RANGE_STEP);
				float
					drop_angle;

				// adjust for expected height if there was no drop, so as to calculate real drop

				drop_angle = pitch - atan(wpn->mob.position.y / wpn->mob.position.z);

				ASSERT(stop_index >= range_mark);

				// if the projectile is really fast we might actually have passed several sample values, so set the value for all of them
				for (; range_mark <= stop_index; range_mark++)
				{
					data[pitch_index][range_mark].drop_angle = drop_angle;
					data[pitch_index][range_mark].flight_time = time;
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
	
	// write collected ballistics data
	if (output && !velocity_test)
	{
		fputs("range     velocity    time     drop  drop angle   drag force\n", output);

		i = 0;
		
		if (output)
			while (test_time[i])
			{
				fprintf(output, "%5.2f m  %6.2f m/s %5.2f s %6.1f m %2.2f degrees %4.1f\n",
					test_range[i], test_velocity[i], test_time[i], - test_drop[i], deg(test_drop_angle[i]), test_drag[i]);
				i++;
			}
		fprintf(output, "top velocity %6.1f m/s \n", max_speed);
	}
}

void calculate_range(weapon* wpn, FILE* output, int zero_pitch)
{
	float
		pitch = 0,
		range_step = 100,
		write_step = 100;

	if (output)
	{

		float
			time = 0.0,
			delta_time = 0.1;

		int
			last_write_range = 0;

		fputs(" range    altitude    velocity    time     drag   weight\n", output);
	
		wpn->weapon_lifetime = weapon_database[wpn->mob.sub_type].boost_time + weapon_database[wpn->mob.sub_type].sustain_time;
		wpn->mob.velocity = weapon_database[wpn->mob.sub_type].muzzle_velocity;
		wpn->mob.position.x = wpn->mob.position.y = wpn->mob.position.z = 0.0;

		if (!zero_pitch)
		{
			if (weapon_database[wpn->mob.sub_type].weapon_class & WEAPON_CLASS_AIR_TO_AIR || weapon_database[wpn->mob.sub_type].weapon_class & WEAPON_CLASS_AIR_TO_SURFACE)
			{
				wpn->mob.position.y = weapon_database[wpn->mob.sub_type].max_altitude;
				pitch = - atan(weapon_database[wpn->mob.sub_type].max_altitude / weapon_database[wpn->mob.sub_type].max_range);
			}
			else if (weapon_database[wpn->mob.sub_type].weapon_class & WEAPON_CLASS_SURFACE_TO_AIR)
				pitch = atan(weapon_database[wpn->mob.sub_type].max_altitude / weapon_database[wpn->mob.sub_type].max_range);
			else
				return;
		}

		get_identity_matrix3x3(wpn->mob.attitude);
		get_3d_transformation_matrix(wpn->mob.attitude, 0.0, pitch, 0.0);

		while (wpn->mob.position.z < weapon_database[wpn->mob.sub_type].max_range)
		{
			time += delta_time;
			wpn->weapon_lifetime -= delta_time;

			update_guided_weapon(wpn, &wpn->mob.position, delta_time, FALSE, FALSE, FALSE);
			
			// increase delta_time when projectile slows down a lot so as to ease amount of calculations a little

			if (wpn->mob.velocity < 150.0)
			{
				delta_time = 0.04;
				if (wpn->mob.velocity < 75.0)
					delta_time = 0.1;

				if (wpn->mob.velocity < 20.0 && wpn->weapon_lifetime < 0)
					break;
			}
			
			if (wpn->mob.position.z > 300000 || wpn->mob.position.y > 1.1 * weapon_database[wpn->mob.sub_type].max_altitude || wpn->mob.position.y < - weapon_database[wpn->mob.sub_type].max_altitude)
				break;

			if (output && wpn->mob.position.z > (last_write_range + write_step - 1))
			{
				last_write_range += write_step;
				fprintf(output, "%5d m %f m  %6.1f m/s %5.1f s, %.2f, %.2f \n",
					last_write_range, wpn->mob.position.y, wpn->mob.velocity, time, get_weapon_drag(wpn->mob.velocity, wpn->mob.position.y, weapon_database[wpn->mob.sub_type].diameter, weapon_database[wpn->mob.sub_type].drag_coefficient), get_weapon_current_weight(wpn->weapon_lifetime, wpn->mob.sub_type));
			}

			if (last_write_range >= 20000)
			{
				write_step = 5000;
				range_step = 2500;
			}
			else if (last_write_range >= 10000)
			{
				write_step = 2000;
				range_step = 1000;
			}
			else if (last_write_range >= 5000)
			{
				write_step = 1000;
				range_step = 500;
			}
			else if (last_write_range >= 500)
			{
				write_step = 500;
				range_step = 250;
			}
		}

		fprintf(output, "%5.0f m %f m  %6.1f m/s %5.1f s, %.2f, pitch %.2f \n",
			wpn->mob.position.z, wpn->mob.position.y, wpn->mob.velocity, time, get_weapon_drag(wpn->mob.velocity, wpn->mob.position.y, weapon_database[wpn->mob.sub_type].diameter, weapon_database[wpn->mob.sub_type].drag_coefficient), deg(pitch));
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
		if (weapon_database[wpn_type].aiming_type && !weapon_database[wpn_type].guidance_type)
		{
			unsigned i;
			
			if (write_file)
			{
				fprintf(write_file, "\n%s   max_range: %.0f m, muzzle velocity: %.0f m/s, cruise velocity: %.0f m/s, drag: %.2f\n",
					weapon_database[wpn_type].full_name,
					weapon_database[wpn_type].max_range,
					weapon_database[wpn_type].muzzle_velocity,
					weapon_database[wpn_type].cruise_velocity,
					weapon_database[wpn_type].drag_coefficient);
			}

			wpn.mob.sub_type = wpn_type;

			for(i = 0; i < VELOCITY_TESTS; i++)
				calculate_projectory(&wpn, write_file, i);
		}

		if (write_file)
			fflush(write_file);
	}

	if (write_file)
		fclose(write_file);
}

void generate_guided_missiles_tables(void)
{
	weapon
		wpn;

	entity_sub_types
		wpn_type;

	FILE*
		write_file = NULL;

	write_file = fopen("guided-missiles-data.txt", "w");

	fputs("Note: this file only lists ballistics data generated from the currently used GWUT File\n"
		  "Changing the values will have no effect, change the GWUT file to see change\n"
		  "This file can be used to help getting good values for the GWUT file\n\n", write_file);

	for (wpn_type = 1; wpn_type <= LAST_WEAPON; wpn_type++)
	{
		if (weapon_database[wpn_type].guidance_type)
		{
			int i;
			
			if (write_file)
			{
				fprintf(write_file, "\n%s \n"
						"max_range: %.0f m, max_altitude %.0f m, muzzle velocity: %.0f m/s, cruise velocity: %.0f m/s, cruise_time %.1f s\n"
						"sustain_time %.1f s, sustain_power %.1f, g_max %.1f, drag: %.2f \n"
						"boost_time %.1f s, boost_power %.1f, start_weight %.1f, final_weight %.1f \n",
					weapon_database[wpn_type].full_name,
					weapon_database[wpn_type].max_range,
					weapon_database[wpn_type].max_altitude,
					weapon_database[wpn_type].muzzle_velocity,
					weapon_database[wpn_type].cruise_velocity,
					weapon_database[wpn_type].cruise_time,
					weapon_database[wpn_type].sustain_time,
					weapon_database[wpn_type].sustain_power,
					weapon_database[wpn_type].g_max,
					weapon_database[wpn_type].drag_coefficient,
					weapon_database[wpn_type].boost_time,
					weapon_database[wpn_type].boost_power,
					weapon_database[wpn_type].start_weight,
					weapon_database[wpn_type].final_weight);
			}

			wpn.mob.sub_type = wpn_type;
			for(i = 0; i < 2; i++)
				calculate_range(&wpn, write_file, i);
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
	unsigned pitch_index, i;

	for(i = 0; i < VELOCITY_TESTS; i++)
		for (wpn_type = 1; wpn_type <= LAST_WEAPON; wpn_type++)
			if (weapon_database[wpn_type].aiming_type && !weapon_database[wpn_type].guidance_type)
			{
				for(pitch_index = 0; pitch_index < TOTAL_PITCH_INDICES; pitch_index++)
				{
					if (ballistics_table[i][wpn_type][pitch_index])
						safe_free(ballistics_table[i][wpn_type][pitch_index]);
					ballistics_table[i][wpn_type][pitch_index] = NULL;
				}
			}
}

/**
 * Looks up om the ballistics tables how much drop and time of flight a projectile
 * of wpn_type will have at the given range.
 * As we probably don't have the value for the exact range/pitch requested it
 * will make a weighted average of the closeset values we have.
 */
int get_ballistic_pitch_deflection(entity_sub_types wpn_type, float range, float height_diff_or_pitch, float* aiming_pitch, float* time_of_flight, int simplified, int fixed_pitch, float parent_velocity)
{
	float
		pitch_delta,
		range_error,
		range_delta,
		drop_compensation[2] = {0, 0},
		time[2] = {0, 0},
		straight_pitch,
		velocity_multiplier = 1;

	int
		iterations,
		i,
		k,
		l = 0,
		pitch_index,
		range_index,
		velocity_test = 0;

	ASSERT(time_of_flight);
	ASSERT(aiming_pitch);

	if (wpn_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON || wpn_type >= NUM_ENTITY_SUB_TYPE_WEAPONS) // some bug should be fixed..
	{
		debug_log("weapon type %i is illegal!", wpn_type);
		return FALSE;
	}
	
	if (!ballistics_table[0][wpn_type][0])
		return FALSE;

		// we need 2d range

	if (!fixed_pitch)
	{
		straight_pitch = - asin(height_diff_or_pitch / range);
		range = sqrt(range * range - height_diff_or_pitch * height_diff_or_pitch);
	}
	else
	{
		straight_pitch = height_diff_or_pitch;
		range = range * cos(height_diff_or_pitch);
	}
	
	if (fixed_pitch)
		iterations = 2;
	else
		iterations = 3;

	// prepare velocity test
	
	parent_velocity = bound(parent_velocity, 0, ((float)VELOCITY_TESTS - 1) * VELOCITY_TEST_STEP - 1);

	if (parent_velocity > 1)
	{
		velocity_test = (int) (parent_velocity / VELOCITY_TEST_STEP);
		velocity_multiplier = 1 - (parent_velocity / VELOCITY_TEST_STEP - velocity_test);
	}
	
	ASSERT(range >= 0.0);

	if (range <= 0.1)
	{
		if (!fixed_pitch)
			*aiming_pitch = straight_pitch;
		else
			*aiming_pitch = 0;
		*time_of_flight = 0.0;
		return TRUE;
	}

	range = bound(range, 0.01, weapon_database[wpn_type].max_range);
	range_index = (int)(range / RANGE_STEP);
	range_error = range - (range_index * RANGE_STEP);
	range_delta = 1.0 - (range_error / RANGE_STEP);   // normalize to [0..1]

	#if DEBUG_MODULE > 1
	debug_log("WN_MOVE: simple range: %.0f (%.0f) closeness: %.02f, height_difference: %.0f", range, range_index*RANGE_STEP, range_delta, height_diff_or_pitch);
	#endif

	// refine drop_compensation - do it several times because as we adjust
	// cannon pitch we have to use a different ballistics table.  Do it a few
	// times so that it stabalizes somewhat

	for (k = velocity_test; k <= velocity_test + (parent_velocity > 1); k++)
	{
		for (i = 0; i < iterations; i++)
		{
			float use_pitch = min(straight_pitch + drop_compensation[l], rad(90.0f));

			pitch_index = get_floor_pitch_index(use_pitch, &pitch_delta);
			ASSERT(pitch_index >= 0 && pitch_index < TOTAL_PITCH_INDICES);
			drop_compensation[l] = ballistics_table[k][wpn_type][pitch_index][range_index].drop_angle;

			if (drop_compensation[l] > rad(45.0))
				return FALSE;

			time[l] = ballistics_table[k][wpn_type][pitch_index][range_index].flight_time;
		}

		// average between next pitch and range:
		if (!simplified)
		{
			ballistics_data
				pitch_compensation[2],
				compensation_grid[2][2];

			int next_pitch_index = min(pitch_index + 1, TOTAL_PITCH_INDICES-1);

			// first average the next ranges
			compensation_grid[0][0].drop_angle = drop_compensation[l];
			compensation_grid[0][0].flight_time = time[l];

			compensation_grid[0][1].drop_angle = ballistics_table[k][wpn_type][pitch_index][range_index+1].drop_angle;
			compensation_grid[0][1].flight_time = ballistics_table[k][wpn_type][pitch_index][range_index+1].flight_time;

			compensation_grid[1][0].drop_angle = ballistics_table[k][wpn_type][next_pitch_index][range_index].drop_angle;
			compensation_grid[1][0].flight_time = ballistics_table[k][wpn_type][next_pitch_index][range_index].flight_time;

			compensation_grid[1][1].drop_angle = ballistics_table[k][wpn_type][next_pitch_index][range_index+1].drop_angle;
			compensation_grid[1][1].flight_time = ballistics_table[k][wpn_type][next_pitch_index][range_index+1].flight_time;

			// then average oover next pitch
			pitch_compensation[0].drop_angle = (pitch_delta * compensation_grid[0][0].drop_angle) + ((1 - pitch_delta) * compensation_grid[1][0].drop_angle);
			pitch_compensation[0].flight_time = (pitch_delta * compensation_grid[0][0].flight_time) + ((1 - pitch_delta) * compensation_grid[1][0].flight_time);

			pitch_compensation[1].drop_angle = (pitch_delta * compensation_grid[0][1].drop_angle) + ((1 - pitch_delta) * compensation_grid[1][1].drop_angle);
			pitch_compensation[1].flight_time = (pitch_delta * compensation_grid[0][1].flight_time) + ((1 - pitch_delta) * compensation_grid[1][1].flight_time);

			// and finally get a total
			drop_compensation[l] = (range_delta * pitch_compensation[0].drop_angle) + ((1 - range_delta) * pitch_compensation[1].drop_angle);
			time[l] = (range_delta * pitch_compensation[0].flight_time) + ((1 - range_delta) * pitch_compensation[1].flight_time);

			#if DEBUG_MODULE > 1
				debug_log("velocity_test: %f, velocity_multiplier %.2f, range: %.0f, pitch %.3f, drop: %.3f, time %.2f", (float)k * VELOCITY_TEST_STEP, velocity_multiplier, range, deg(straight_pitch), deg(drop_compensation[l]), time[l]);
			#endif
		}
		
		l++;
	}

	*aiming_pitch = drop_compensation[0] * velocity_multiplier + drop_compensation[1] * (1 - velocity_multiplier);
	*time_of_flight = time[0] * velocity_multiplier + time[1] * (1 - velocity_multiplier);

	#if DEBUG_MODULE > 1
		debug_log("result pitch %.3f, time %.2f", *aiming_pitch, *time_of_flight);
	#endif

	if (!fixed_pitch)
		*aiming_pitch += straight_pitch; // get absolute angle only if straight_pitch wasn't given
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

