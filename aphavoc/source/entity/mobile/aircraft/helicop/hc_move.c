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



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 														0

#define DEBUG_WAYPOINT_VECTOR												0

#define HELICOPTER_VELOCITY_RAMP_DISTANCE								(500.0 * METRE)

#define HELICOPTER_MAX_PITCH 												(rad (20.0))

#define HELICOPTER_MAX_ROLL 												(rad (30.0))

#define HELICOPTER_LATERAL_TO_FORWARD_VELOCITY_SCALING			5.0

#define HELICOPTER_AVOIDANCE_DISTANCE									20.0

#define HELICOPTER_STRUCTURE_AVOIDANCE_LOOKAHEAD_TIME				1.0

#define HELICOPTER_TERRAIN_AVOIDANCE_LOOKAHEAD_TIME				2.0

#define HELICOPTER_TERRAIN_AVOIDANCE_LOOKAHEAD_SAMPLE_NUMBER	1

#define RIVER_DEPTH 															3.0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float
	min_coning_angle = -1.0,
	max_coning_angle = 5.0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void helicopter_movement_get_waypoint_position_and_velocity (entity *en, vec3d *wp_pos, vec3d *wp_vel);

static float helicopter_movement_get_desired_heading (entity *en, vec3d *fly_to_pos, float current_heading);

static float helicopter_movement_get_desired_pitch (entity *en, vec3d *model_motion_vector, vec3d *model_acceleratoin_vector, int *return_flag);

static float helicopter_movement_get_desired_roll (entity *en, float lateral_velocity, float lateral_acceleration, int *return_flag);

static void helicopter_movement_calculate_rotor_rpm (entity *en, float lift);

static float helicopter_movement_structure_avoidance (entity *en);

static float helicopter_movement_altitude_follow (entity *en, entity *guide, vec3d *wp_pos);

static void helicopter_movement_calculate_new_position (entity *en, entity *guide, vec3d *wp_pos);

static int helicopter_crash_movement (entity *en);

static void clear_helicopter_velocity (entity *en);

static void helicopter_adjust_waypoint_position_with_los (entity *en, vec3d *wp_pos);

/*static*/ void debug_visuals (entity *en, vec3d *wp_pos);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void helicopter_movement (entity *en)
{
	entity
		*guide,
		*group,
		*member;

	float
		maxx,
		lift,
		speed,
		current_pitch,
		current_roll,
		current_heading,
		new_heading,
		new_pitch,
		new_roll,
		delta_heading,
		desired_heading;

	float
		max_x_vel,
		max_y_vel,
		max_z_vel,
		height,
		range,
		max_vel,
		range_scaler,
		desired_roll,
		desired_pitch;

	vec3d
		wp_vec,
		wp_pos,
		wp_vel,
		*hc_pos,
		normalised_wp_vec,
		model_motion_vector,
		model_acceleration_vector,
		world_acceleration_vector;

	helicopter
		*raw;

	#ifdef DEBUG

	if (en == get_external_view_entity ())
	{

		// Put breakpoint here to debug external-view-entity
		raw = NULL;
	}

	#endif

	raw = get_local_entity_data (en);

	//
	// abort if the mobile has no current guide
	//

	guide = get_local_entity_parent (en, LIST_TYPE_FOLLOWER);

	if (!guide)
	{
		return;
	}

	//
	//
	//

	hc_pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	helicopter_movement_get_waypoint_position_and_velocity (en, &wp_pos, &wp_vel);

	wp_pos.y = max (wp_pos.y, get_3d_terrain_point_data_elevation (&raw->ac.terrain_info));

	helicopter_adjust_waypoint_position_with_los (en, &wp_pos);

	range = get_local_entity_float_value (en, FLOAT_TYPE_DISTANCE);

	height = helicopter_movement_altitude_follow (en, guide, &wp_pos);

	// ramp vel from 0 to cruise_vel between 0m -> HELICOPTER_VELOCITY_RAMP_DISTANCE
	range_scaler = min ((range / HELICOPTER_VELOCITY_RAMP_DISTANCE), 1.0);

	wp_vec.x = wp_pos.x - hc_pos->x;
	wp_vec.y = wp_pos.y - hc_pos->y;
	wp_vec.z = wp_pos.z - hc_pos->z;

	// calcualte max_vel
	max_vel = aircraft_database [raw->ac.mob.sub_type].cruise_velocity * ((2.0 * range_scaler) - (range_scaler * range_scaler));

	// bound speeds to something realistic
	max_x_vel = 0.2 * aircraft_database [raw->ac.mob.sub_type].cruise_velocity;
	max_y_vel = 0.1 * aircraft_database [raw->ac.mob.sub_type].cruise_velocity;
	max_z_vel = 1.0 * aircraft_database [raw->ac.mob.sub_type].cruise_velocity;

	normalise_any_3d_vector (&wp_vec);

	// rotate into model space for speed bounding
	multiply_transpose_matrix3x3_vec3d (&wp_vec, raw->ac.mob.attitude, &wp_vec);

	normalised_wp_vec = wp_vec;

	// get velocity vector to wp
	wp_vec.x *= max_vel;
	wp_vec.y *= max_vel;
	wp_vec.z *= max_vel;

	// limit max_velocity depending on required climb rate
	max_z_vel -= (max_z_vel * min ((max (height - hc_pos->y, 0.0) / max_y_vel), 1.0));
	max_x_vel -= (max_x_vel * min ((max (height - hc_pos->y, 0.0) / max_y_vel), 1.0));

	// limit forward acceleration depending on climb demand

	wp_vec.x = bound (wp_vec.x, -max_x_vel, max_x_vel);
	wp_vec.y = bound (wp_vec.y, -max_y_vel, max_y_vel);
	wp_vec.z = bound (wp_vec.z, -max_z_vel, max_z_vel);

	// rotate back into world space
	multiply_matrix3x3_vec3d (&wp_vec, raw->ac.mob.attitude, &wp_vec);

	// add on required height for terrain avoidance
	wp_vec.y = (height - hc_pos->y);
	wp_vec.y = bound (wp_vec.y, -max_y_vel, max_y_vel);

	// add on the velocity of the wp (i.e. the speed it is moving)
	// don't add in Y-component as it causes the wingmen to crash into the floor if the player decends quickly
	wp_vec.x += wp_vel.x;
	wp_vec.z += wp_vel.z;

	#if DEBUG_MODULE

	wp_pos.y = height;

	debug_visuals (en, &wp_pos);

	#endif

	//
	//
	//

	world_acceleration_vector.x = (wp_vec.x - raw->ac.mob.motion_vector.x) * 0.3;
	world_acceleration_vector.y = (wp_vec.y - raw->ac.mob.motion_vector.y) * 0.3;
	world_acceleration_vector.z = (wp_vec.z - raw->ac.mob.motion_vector.z) * 0.3;

	//
	// Don't allow movement before rotors have spun up.
	//

	// bodge for rotor rpm
	lift = (0.7 * aircraft_database [raw->ac.mob.sub_type].power_output) + (fabs (world_acceleration_vector.y) + fabs (world_acceleration_vector.z));

	helicopter_movement_calculate_rotor_rpm (en, lift);

	if ((raw->main_rotor_spin_up_timer > 0.0) &&
		((get_local_entity_int_value (en, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI) ||
		 (get_local_entity_int_value (en, INT_TYPE_AUTO_PILOT))))
	{

		raw->main_rotor_spin_up_timer -= get_entity_movement_delta_time ();

		raw->main_rotor_spin_up_timer = max (raw->main_rotor_spin_up_timer, 0.0);

		return;
	}

	//
	// Make AI helicopters wait until all human helicopters in the group have taken off
	//

	if (get_comms_model () == COMMS_MODEL_SERVER)
	{
		if (get_local_entity_int_value (en, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI)
		{
			if (get_local_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE) == OPERATIONAL_STATE_LANDED)
			{
				group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

				ASSERT (group);

				member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

				while (member)
				{
					if (get_local_entity_int_value (member, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
					{
						if (!get_local_entity_int_value (member, INT_TYPE_AIRBORNE_AIRCRAFT))
						{
							return;
						}
					}

					member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
				}

				set_client_server_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_TAKEOFF);
			}
		}
	}

	if (get_local_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE) == OPERATIONAL_STATE_LANDED)
	{
		return;
	}

	//
	// calculate the motion vector, in world coords
	//

	raw->ac.mob.motion_vector.x += world_acceleration_vector.x * get_entity_movement_delta_time ();
	raw->ac.mob.motion_vector.y = wp_vec.y;
	raw->ac.mob.motion_vector.z += world_acceleration_vector.z * get_entity_movement_delta_time ();

	// set velocity
	speed = get_3d_vector_magnitude (&raw->ac.mob.motion_vector);
	set_local_entity_float_value (en, FLOAT_TYPE_VELOCITY, speed);

	current_heading = get_heading_from_attitude_matrix (raw->ac.mob.attitude);
	current_pitch = get_pitch_from_attitude_matrix (raw->ac.mob.attitude);
	current_roll = get_roll_from_attitude_matrix (raw->ac.mob.attitude);

	// attitude
	desired_heading = helicopter_movement_get_desired_heading (en, &wp_vec, current_heading);

	delta_heading = (desired_heading - current_heading);

	if (delta_heading < -PI)
	{

		delta_heading += PI2;
	}
	else if (delta_heading > PI)
	{

		delta_heading -= PI2;
	}

	maxx = get_local_entity_float_value (en, FLOAT_TYPE_MAX_TURN_RATE);

	delta_heading = bound (delta_heading, -maxx, maxx);

	new_heading = current_heading + (delta_heading * get_entity_movement_delta_time ());

	multiply_transpose_matrix3x3_vec3d (&model_motion_vector, raw->ac.mob.attitude, &raw->ac.mob.motion_vector);
	multiply_transpose_matrix3x3_vec3d (&model_acceleration_vector, raw->ac.mob.attitude, &world_acceleration_vector);

	desired_pitch = helicopter_movement_get_desired_pitch (en, &model_motion_vector, &model_acceleration_vector, NULL);
	desired_roll = helicopter_movement_get_desired_roll (en, model_motion_vector.x, model_acceleration_vector.x, NULL);

	new_pitch = current_pitch + (desired_pitch - current_pitch) * 0.5 * get_entity_movement_delta_time ();
	new_roll = current_roll + (desired_roll - current_roll) * 0.5 * get_entity_movement_delta_time ();

	get_3d_transformation_matrix (raw->ac.mob.attitude, new_heading, new_pitch, new_roll);

	helicopter_movement_calculate_new_position (en, guide, &wp_pos);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void helicopter_death_movement (entity *en)
{

	helicopter
		*raw;

	float
		heading,
		pitch,
		roll,
		speed,
		altitude,
		delta_rpm,
		spin_up_amount,
		terrain_elevation,
		old_terrain_elevation;

	vec3d
		*pos,
		*velocity,
		new_pos;

	terrain_classes
		terrain_class;

	raw = get_local_entity_data (en);

	//
	// wind down rotors
	//

	delta_rpm = -raw->main_rotor_rpm;

	spin_up_amount = ((1.0 / 3600) * raw->main_rotor_rpm * raw->main_rotor_rpm);

	spin_up_amount = bound (spin_up_amount, 0.3, 1.0);

	delta_rpm *= spin_up_amount;

	raw->main_rotor_rpm += delta_rpm * get_entity_movement_delta_time ();

	if (raw->main_rotor_rpm < 2.0)
	{
		raw->main_rotor_rpm = 0.0;
	}

	raw->tail_rotor_rpm = raw->main_rotor_rpm;

	//
	// get current position and velocity
	//

	pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	old_terrain_elevation = get_3d_terrain_point_data_elevation (&raw->ac.terrain_info);

	velocity = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_MOTION_VECTOR);

	if (get_terrain_type_class (get_3d_terrain_point_data_type (&raw->ac.terrain_info)) == TERRAIN_CLASS_LAND)
	{
		altitude = pos->y - (old_terrain_elevation + get_local_entity_float_value (en, FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE));

		if (altitude <= 0.0)
		{
			//
			// stop any engine noise
			//

			if (get_comms_model() == COMMS_MODEL_SERVER)
			{
				kill_helicopter_rotor_sound_effects (en);
			}

			//
			// if aircraft is already on the ground, but not on water, call different movement function
			//

			if (helicopter_crash_movement (en))
			{
				if (raw->main_rotor_rpm == 0.0)
				{
					if (!raw->ac.mob.alive)
					{
						set_local_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_DEAD);
					}
				}
			}

			return;
		}
	}

	new_pos.x = pos->x + (velocity->x * get_entity_movement_delta_time());
	new_pos.y = pos->y + (velocity->y * get_entity_movement_delta_time());
	new_pos.z = pos->z + (velocity->z * get_entity_movement_delta_time());

	bound_position_to_map_volume (&new_pos);

	get_3d_terrain_point_data (new_pos.x, new_pos.z, &raw->ac.terrain_info);

	//
	// update velocity
	//

	velocity->y -= (G * get_entity_movement_delta_time());		// ignore lift for simplicity

	speed = get_3d_vector_magnitude (velocity);

	set_local_entity_float_value (en, FLOAT_TYPE_VELOCITY, speed);

	//
	// check if aircraft has hit the floor
	//

	terrain_elevation = get_3d_terrain_point_data_elevation (&raw->ac.terrain_info);

	terrain_class = get_terrain_type_class (get_3d_terrain_point_data_type (&raw->ac.terrain_info));

	altitude = new_pos.y - (terrain_elevation + get_local_entity_float_value (en, FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE));

	if (altitude <= 0.0)
	{
		if (get_comms_model() == COMMS_MODEL_SERVER)
		{
			//
			// ensure that the aircraft is actually dead
			//

			if (get_local_entity_int_value (en, INT_TYPE_ALIVE))
			{
				kill_client_server_entity (en);
			}

			if (pos->y > old_terrain_elevation)
			{
				//
				// aircraft has hit the terrain this frame - create a "splash"
				//

				vec3d
					temp_pos;

				temp_pos.x = new_pos.x;
				temp_pos.y = terrain_elevation;
				temp_pos.z = new_pos.z;

				set_local_entity_vec3d (en, VEC3D_TYPE_POSITION, &temp_pos);

				create_client_server_object_hit_ground_explosion_effect (en, get_3d_terrain_point_data_type (&raw->ac.terrain_info));

				//
				// stop any engine noise
				//

				if (get_comms_model() == COMMS_MODEL_SERVER)
				{
					kill_helicopter_rotor_sound_effects (en);
				}
			}
		}

		if (terrain_class == TERRAIN_CLASS_WATER)
		{
			//////////////////////////////////////////
			//
			// AIRCRAFT IS BELOW GROUND AND IN WATER
			//
			//////////////////////////////////////////

			//
			// kill any fires that may be burning
			//

			clear_smoke_list_generator_lifetime (en, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_FIRE);
			clear_smoke_list_generator_lifetime (en, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_EXPLOSION_TRAIL);

			//
			// no lateral movement below ground
			//

			new_pos.x = pos->x;
			new_pos.z = pos->z;

			switch (get_3d_terrain_point_data_type (&raw->ac.terrain_info))
			{
				case TERRAIN_TYPE_SEA:
				{
					//
					// aircraft has landed in the sea
					//

					struct OBJECT_3D_BOUNDS
						*bounding_box;

					vec3d
						d;

					bounding_box = get_object_3d_bounding_box (get_local_entity_int_value (en, INT_TYPE_OBJECT_3D_SHAPE));

					d.x = bounding_box->xmax - bounding_box->xmin;
					d.y = bounding_box->ymax - bounding_box->ymin;
					d.z = bounding_box->zmax - bounding_box->zmin;

					if (altitude < -(get_3d_vector_magnitude (&d) * 0.5))
					{
						//
						// aircraft is no longer visible
						//

						raw->main_rotor_rpm = 0.0;

						raw->tail_rotor_rpm = 0.0;

						clear_helicopter_velocity (en);

						set_local_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_DEAD);
					}

					break;
				}
				default:
				{
					//
					// aircraft has landed in a river / lake
					//

					if (altitude < -RIVER_DEPTH)
					{
						new_pos.y = terrain_elevation + get_local_entity_float_value (en, FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE);

						new_pos.y -= RIVER_DEPTH;

						raw->main_rotor_rpm = 0.0;

						raw->tail_rotor_rpm = 0.0;

						clear_helicopter_velocity (en);

						set_local_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_DEAD);
					}
				}
			}
		}
		else if (terrain_class == TERRAIN_CLASS_FOREST)
		{
			//////////////////////////////////////////
			//
			// AIRCRAFT HAS HIT FOREST
			//
			//////////////////////////////////////////

			//
			// keep moving until the aircraft is obscured
			//

			{
				struct OBJECT_3D_BOUNDS
					*bounding_box;

				vec3d
					d;

				bounding_box = get_object_3d_bounding_box (get_local_entity_int_value (en, INT_TYPE_OBJECT_3D_SHAPE));

				d.x = bounding_box->xmax - bounding_box->xmin;
				d.y = bounding_box->ymax - bounding_box->ymin;
				d.z = bounding_box->zmax - bounding_box->zmin;

				if (altitude < -(get_3d_vector_magnitude (&d) * 0.5))
				{
					//
					// aircraft is no longer visible
					//

					raw->main_rotor_rpm = 0.0;

					raw->tail_rotor_rpm = 0.0;

					clear_helicopter_velocity (en);

					set_local_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_DEAD);
				}
			}
		}
		else
		{
			//////////////////////////////////////////
			//
			// AIRCRAFT HAS HIT SOLID GROUND
			//
			//////////////////////////////////////////

			new_pos.y = terrain_elevation + get_local_entity_float_value (en, FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE);

			//
			// crash sound effect
			//

			if (get_comms_model () == COMMS_MODEL_SERVER)
			{
				sound_sample_indices
					sound_sample_index;

				sound_sample_index = SOUND_SAMPLE_INDEX_HELICOPTER_CRASH;

				create_client_server_sound_effect_entity
				(
					en,
					ENTITY_SIDE_NEUTRAL,
					ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,
					SOUND_CHANNEL_SOUND_EFFECT,
					SOUND_LOCALITY_ALL,
					NULL,												// position
					1.0,												// amplification
					1.0,												// Werewolf pitch
					TRUE,												// valid sound effect
					FALSE,											// looping
					1,													// sample count
					&sound_sample_index							// sample index list
				);
			}
		}
	}

	//
	// update attitude
	//

	heading = get_heading_from_attitude_matrix (raw->ac.mob.attitude);

	pitch = get_pitch_from_attitude_matrix (raw->ac.mob.attitude);

	roll = get_roll_from_attitude_matrix (raw->ac.mob.attitude);

	heading += (PI * 0.4 * get_entity_movement_delta_time());

	pitch -= (pitch * 0.25 * get_entity_movement_delta_time());

	roll -= (roll * 0.25 * get_entity_movement_delta_time());

	get_3d_transformation_matrix (raw->ac.mob.attitude, heading, pitch, roll);

	//
	// set new position
	//

	set_local_entity_vec3d (en, VEC3D_TYPE_POSITION, &new_pos);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int helicopter_crash_movement (entity *en)
{

	helicopter
		*raw;

	float
		heading,
		pitch,
		roll,
		required_angle,
		delta_angle,
		max_angle,
		speed,
		acc,
		dx,
		dy,
		dz,
		terrain_elevation;

	vec3d
		*pos,
		*velocity,
		new_pos,
		*face_normal;

	matrix3x3
		m;

	raw = get_local_entity_data (en);

	//
	// update attitude
	//

	heading = get_heading_from_attitude_matrix (raw->ac.mob.attitude);

	pitch = get_pitch_from_attitude_matrix (raw->ac.mob.attitude);

	roll = get_roll_from_attitude_matrix (raw->ac.mob.attitude);

	face_normal = get_3d_terrain_point_data_normal (&raw->ac.terrain_info);

	get_3d_transformation_matrix_from_face_normal_and_heading (m, face_normal, heading);

	//
	// pitch
	//

	required_angle = get_pitch_from_attitude_matrix (m) + aircraft_database [raw->ac.mob.sub_type].destroyed_pitch_offset;

	max_angle = PI * get_entity_movement_delta_time ();

	delta_angle = bound (required_angle - pitch, -max_angle, max_angle);

	pitch += delta_angle;

	//
	// roll
	//

	required_angle = get_roll_from_attitude_matrix (m) + aircraft_database [raw->ac.mob.sub_type].destroyed_bank_offset;

	max_angle = PI * 0.25 * get_entity_movement_delta_time ();

	delta_angle = bound (required_angle - roll, -max_angle, max_angle);

	roll += delta_angle;

	//

	get_3d_transformation_matrix (raw->ac.mob.attitude, heading, pitch, roll);

	//
	// work out new position
	//

	velocity = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_MOTION_VECTOR);

	pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	new_pos.x = pos->x + (velocity->x * get_entity_movement_delta_time());
	new_pos.z = pos->z + (velocity->z * get_entity_movement_delta_time());

	bound_position_to_map_area (&new_pos);

	get_3d_terrain_point_data (new_pos.x, new_pos.z, &raw->ac.terrain_info);

	terrain_elevation = get_3d_terrain_point_data_elevation (&raw->ac.terrain_info);

	if (get_terrain_type_class (get_3d_terrain_point_data_type (&raw->ac.terrain_info)) == TERRAIN_CLASS_FOREST)
	{
		//
		// use last frame's altitude to stop aircraft from magically pinging to the top of the forest
		//

		new_pos.y = pos->y;
	}
	else
	{
		new_pos.y = terrain_elevation + get_local_entity_float_value (en, FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE);
	}

	//
	// update velocity
	//

	speed = normalise_any_3d_vector (velocity);

	acc = max (speed * 0.65, 4.0);

	speed -= (acc * get_entity_movement_delta_time ());

	speed = max (speed, 0.0);

	velocity->x *= speed;
	velocity->y *= speed;
	velocity->z *= speed;

	dx = (G * face_normal->x * get_entity_movement_delta_time());
	dz = (G * face_normal->z * get_entity_movement_delta_time());

	dy = (new_pos.y - pos->y) / get_entity_movement_delta_time();

	velocity->x += dx;
	velocity->z += dz;

	velocity->y = dy;

	//
	// set new position
	//

	set_local_entity_vec3d (en, VEC3D_TYPE_POSITION, &new_pos);

	//
	// Stop Aircraft ?
	//

	#if DEBUG_MODULE

	if (en == get_external_view_entity ())
	{
		float
			slope;

		slope = acos (face_normal->y);

		debug_log ("SLOPE %f - SPEED %f (dx %f, dy %f, dz %f)", deg (slope), speed, dx, dy, dz);
	}

	#endif

	if (speed < 1.0)
	{
		clear_helicopter_velocity (en);

		return TRUE;
	}
	else
	{
		set_local_entity_float_value (en, FLOAT_TYPE_VELOCITY, speed);

		return FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void helicopter_impact_movement (entity *en)
{

	helicopter
		*raw;

	float
		speed;

	vec3d
		*velocity;

	int
		seed;

	raw = get_local_entity_data (en);

	seed = get_client_server_entity_random_number_seed(en);

	speed = 10.0 + (2.0 * frand1x (&seed));

	if (seed & 1)
	{
		speed = -speed;
	}

	velocity = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_MOTION_VECTOR);

	velocity->x += (speed * raw->ac.mob.xv.x);

	velocity->z += (speed * raw->ac.mob.xv.z);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void helicopter_movement_get_waypoint_position_and_velocity (entity *en, vec3d *wp_pos, vec3d *wp_vel)
{
	entity
		*wp,
		*group,
		*guide;

	float
		distance;

	vec3d
		*pos;

	int
		hold_position;

	ASSERT (en);

	pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	ASSERT (wp_pos);

	group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

	ASSERT (group);

	guide = get_local_entity_parent (en, LIST_TYPE_FOLLOWER);

	//ASSERT (guide);

	wp_vel->x = 0.0;
	wp_vel->y = 0.0;
	wp_vel->z = 0.0;

	if (!guide)
	{
		return;
	}

	//
	// Check for position hold
	//

	hold_position = FALSE;

	if ((get_local_entity_int_value (en, INT_TYPE_POSITION_HOLD)) && (!get_local_entity_int_value (en, INT_TYPE_TASK_LEADER)))
	{
		//
		// Hold position if flag is set, and entity is not the task leader (to stop group leader, or entities taking off / landing / attacking from holding)
		//

		hold_position = TRUE;

		if ((get_local_entity_parent (en, LIST_TYPE_TARGET)) && (!get_local_entity_int_value (en, INT_TYPE_WEAPONS_HOLD)))
		{
			//
			// ...Unless entity has a target and is in 'weapons free' mode...
			//

			hold_position = FALSE;
		}
	}

	if (hold_position)
	{
		//
		// Hold Position
		//

		get_local_entity_vec3d (en, VEC3D_TYPE_WAIT_POSITION, wp_pos);

		ASSERT (point_inside_map_volume (wp_pos));
	}
	else
	{
		//
		// Normal Operation
		//

		if (!get_local_entity_int_value (guide, INT_TYPE_FOLLOW_FORMATION))
		{
			//
			// Head directly for the guide position
			//

			get_local_entity_vec3d (guide, VEC3D_TYPE_GUIDE_POSITION, wp_pos);
		}
		else
		{
			//
			// Fly in formation
			//

			wp = get_local_entity_parent (guide, LIST_TYPE_CURRENT_WAYPOINT);

			ASSERT (wp);

			//
			// Should aircraft follow leader, or follow guide in set waypoint formation?
			//

			if (get_local_entity_int_value (wp, INT_TYPE_MOBILE_FOLLOW_WAYPOINT_OFFSET))
			{
				vec3d
					offset;

				get_local_entity_vec3d (guide, VEC3D_TYPE_GUIDE_POSITION, wp_pos);

				get_local_entity_formation_position_offset (en, wp, &offset);

				wp_pos->x += offset.x;
				wp_pos->y += offset.y;
				wp_pos->z += offset.z;
			}
			else
			{
				//
				// Task leader follows guide,.... other members follow task leader
				//

				if (get_local_entity_int_value (en, INT_TYPE_TASK_LEADER))
				{
					get_local_entity_vec3d (guide, VEC3D_TYPE_GUIDE_POSITION, wp_pos);
				}
				else
				{
					//
					// set wp pos to offset from flight leader
					//

					entity
						*task_leader;

					vec3d
						xv,
						*leader_pos;

					formation_type
						*formation;

					int
						type,
						formation_count,
						formation_index,
						leader_formation_index;

					//
					// find flight leader
					//

					task_leader = get_local_entity_ptr_value (guide, PTR_TYPE_TASK_LEADER);

					ASSERT (task_leader);

					//
					// get formation
					//

					type = get_local_entity_int_value (group, INT_TYPE_GROUP_FORMATION);

					formation = get_formation (type);

					formation_count = formation->number_in_formation;

					formation_index = get_local_entity_int_value (en, INT_TYPE_GROUP_MEMBER_NUMBER);

					leader_formation_index = get_local_entity_int_value (task_leader, INT_TYPE_GROUP_MEMBER_NUMBER);

					ASSERT (formation_index < formation_count);
					ASSERT (leader_formation_index < formation_count);

					//
					// calculate position
					//

					leader_pos = get_local_entity_vec3d_ptr (task_leader, VEC3D_TYPE_POSITION);

					get_local_entity_vec3d (task_leader, VEC3D_TYPE_XV, &xv);

					xv.x *= 1.75;
					xv.z *= 1.75;

					//
					// take leader position and SUBTRACT leaders formation position (coz leader is not necessarily formation pos 0)
					//

					wp_pos->x = leader_pos->x - ((xv.x * formation->sites [leader_formation_index].x) - (xv.z * formation->sites [leader_formation_index].z));
					wp_pos->y = leader_pos->y - formation->sites [leader_formation_index].y;
					wp_pos->z = leader_pos->z - ((xv.x * formation->sites [leader_formation_index].z) + (xv.z * formation->sites [leader_formation_index].x));

					//
					// then ADD members formation position
					//

					wp_pos->x += ((xv.x * formation->sites [formation_index].x) - (xv.z * formation->sites [formation_index].z));
					wp_pos->y += formation->sites [formation_index].y;
					wp_pos->z += ((xv.x * formation->sites [formation_index].z) + (xv.z * formation->sites [formation_index].x));

					wp_pos->y -= get_local_entity_float_value (task_leader, FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE);

					get_local_entity_vec3d (task_leader, VEC3D_TYPE_MOTION_VECTOR, wp_vel);
				}
			}
		}
	}

	//
	// align waypoint altitude with the lowest point on the aircraft
	//

	wp_pos->y += get_local_entity_float_value (en, FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE);

	//
	// calculate distance of entity to desire position
	//

	distance = get_2d_range (pos, wp_pos);

	#if DEBUG_WAYPOINT_VECTOR

	if (distance > 0.0)
	{
		create_debug_3d_line (pos, wp_pos, sys_col_black, 0.0);
	}

	#endif

	set_local_entity_float_value (en, FLOAT_TYPE_DISTANCE, distance);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_waypoint_display_position (entity *en, entity *wp, vec3d *wp_pos)
{
	vec3d
		offset;

	ASSERT (en);

	ASSERT (wp);

	ASSERT (wp_pos);

	get_local_entity_vec3d (wp, VEC3D_TYPE_POSITION, wp_pos);

	if (get_local_entity_int_value (wp, INT_TYPE_MOBILE_FOLLOW_WAYPOINT_OFFSET))
	{
		get_local_entity_formation_position_offset (en, wp, &offset);

		wp_pos->x += offset.x;
		wp_pos->y += offset.y;
		wp_pos->z += offset.z;
	}

	if (point_inside_map_area (wp_pos))
	{
		wp_pos->y = get_3d_terrain_elevation (wp_pos->x, wp_pos->z);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float helicopter_movement_get_desired_heading (entity *en, vec3d *fly_to_pos, float current_heading)
{
	entity
		*guide,
		*leader;

	vec3d
		*mv;

	float
		heading;

	ASSERT (en);

	ASSERT (fly_to_pos);

	guide = get_local_entity_parent (en, LIST_TYPE_FOLLOWER);

	ASSERT (guide);

	if (get_guide_criteria_valid (guide, GUIDE_CRITERIA_RADIUS))
	{
		if (get_local_entity_float_value (en, FLOAT_TYPE_DISTANCE) < (get_guide_criteria_value (guide, GUIDE_CRITERIA_RADIUS)))
		{
			mv = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_MOTION_VECTOR);

			if (((mv->x * mv->x) + (mv->z * mv->z)) < (5.0 * 5.0))
			{
				if (get_guide_required_heading (guide, en, &heading))
				{
					return heading;
				}
				else
				{
					leader = get_local_entity_ptr_value (guide, PTR_TYPE_TASK_LEADER);

					if (leader != en)
					{
						return (get_local_entity_float_value (leader, FLOAT_TYPE_HEADING));
					}
				}
			}
		}
	}

	//
	// Default case :- face the direction the helicopter is flying if more than 5m away,
	// otherwise just face the way its facing already. Stops the jiggling when landing at wp's
	//

	if (((fly_to_pos->x * fly_to_pos->x) + (fly_to_pos->z * fly_to_pos->z)) < (5.0 * 5.0))
	{

		heading = current_heading;
	}
	else
	{

		heading = atan2 (fly_to_pos->x, fly_to_pos->z);
	}

	return heading;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float helicopter_movement_get_desired_pitch (entity *en, vec3d *model_motion_vector, vec3d *model_acceleration_vector, int *return_flag)
{
	entity
		*guide;

	float
		pitch,
		range;

	vec3d
		guide_pos;

	ASSERT (en);

	if (return_flag) *return_flag = FALSE;

	guide = get_local_entity_parent (en, LIST_TYPE_FOLLOWER);

	ASSERT (guide);

	if (get_guide_criteria_valid (guide, GUIDE_CRITERIA_WEAPON_VECTOR))
	{
		//
		// check radius
		//

		if ((!get_guide_criteria_valid (guide, GUIDE_CRITERIA_RADIUS)) || (get_local_entity_float_value (en, FLOAT_TYPE_DISTANCE) < get_guide_criteria_value (guide, GUIDE_CRITERIA_RADIUS)))
		{
			//
			// check velocity
			//

			if (get_local_entity_float_value (en, FLOAT_TYPE_VELOCITY) < 5.0)
			{
				//
				// check altitude
				//

				if (get_guide_criteria_valid (guide, GUIDE_CRITERIA_ALTITUDE))
				{
					get_local_entity_vec3d (guide, VEC3D_TYPE_POSITION, &guide_pos);

					range = get_local_entity_float_value (en, FLOAT_TYPE_ALTITUDE);

					range -= get_local_entity_float_value (en, FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE);

					range -= guide_pos.y;

					if (fabs (range) < get_guide_criteria_value (guide, GUIDE_CRITERIA_ALTITUDE))
					{
						if (get_guide_required_pitch (guide, en, &pitch))
						{
							if (return_flag) *return_flag = TRUE;

							return pitch;
						}
					}
				}
				else
				{
					if (get_guide_required_pitch (guide, en, &pitch))
					{
						if (return_flag) *return_flag = TRUE;

						return pitch;
					}
				}
			}
		}
	}

	//
	// Default case :-
	//

	{

		//
		// calculate pitch for helicopter at given velocity
		//

		pitch = -(HELICOPTER_MAX_PITCH * min ((model_motion_vector->z / get_local_entity_float_value (en, FLOAT_TYPE_CRUISE_VELOCITY)), 1.0));
    
    pitch *= 1.3; //ataribaby 4/1/2009 add more forward flight pitch to AI controled helis to look more real
    
		// reduce pitch if climbing, upto 0 pitch
		pitch = min (pitch + HELICOPTER_MAX_PITCH * bound (((fabs (model_motion_vector->y) * G) / aircraft_database [get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)].g_max), -1.0, 1.0), 0.0);

		//
		// calculate pitch for helicopter at given acceleration
		//

		pitch -= HELICOPTER_MAX_PITCH * bound (((model_acceleration_vector->z * G) / aircraft_database [get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)].g_max), -1.0, 1.0);

		//
		// add in rotor angle
		//

		pitch += get_local_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_SHAFT_ANGLE);
	}
  
	return pitch;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float helicopter_movement_get_desired_roll (entity *en, float lateral_velocity, float lateral_acceleration, int *return_flag)
{

	float
		roll;

	//
	// calculate roll for helicopter at given velocity
	//

	roll = (HELICOPTER_MAX_ROLL * min (((lateral_velocity * HELICOPTER_LATERAL_TO_FORWARD_VELOCITY_SCALING) / get_local_entity_float_value (en, FLOAT_TYPE_CRUISE_VELOCITY)), 1.0));

	//
	// calculate roll for helicopter at given acceleration
	//

	roll = HELICOPTER_MAX_ROLL * min (((lateral_acceleration * G) / aircraft_database [get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)].g_max), 1.0);

	return roll;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void helicopter_movement_calculate_rotor_rpm (entity *en, float lift)
{
	helicopter
		*raw;

	float
		delta_rpm,
		spin_up_amount,
		desired_rpm;

	ASSERT (en);

	raw = get_local_entity_data (en);

	ASSERT (aircraft_database [raw->ac.mob.sub_type].power_output != 0.0);

	desired_rpm = (lift / aircraft_database [raw->ac.mob.sub_type].power_output) * 100.0;

	desired_rpm = min (desired_rpm, 100.0);

	delta_rpm = desired_rpm - raw->main_rotor_rpm;

	spin_up_amount = ((1.0 / 3600) * raw->main_rotor_rpm * raw->main_rotor_rpm);

	spin_up_amount = bound (spin_up_amount, 0.01, 1.0);

	delta_rpm *= spin_up_amount;

	raw->main_rotor_rpm += delta_rpm * get_entity_movement_delta_time ();

	raw->main_rotor_rpm = bound (raw->main_rotor_rpm, 0.0, 100.0);

	raw->tail_rotor_rpm = raw->main_rotor_rpm;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float helicopter_movement_structure_avoidance (entity *en)
{
	helicopter
		*raw;

	entity
		*guide,
		*sector,
		*structure;

	vec3d
		pos,
		*test_pos;

	matrix3x3
		*attitude;

	float
		d,
		radius,
		max_height;

	ASSERT (en);

	raw = get_local_entity_data (en);

	if (get_local_entity_int_value (en, INT_TYPE_TASK_LEADER))
	{
		guide = get_local_entity_parent (en, LIST_TYPE_FOLLOWER);

		ASSERT (guide);

		if (get_guide_criteria_valid (guide, GUIDE_CRITERIA_RADIUS))
		{
			if (get_guide_criteria_valid (guide, GUIDE_CRITERIA_ALTITUDE))
			{
				if (get_local_entity_float_value (en, FLOAT_TYPE_DISTANCE) < (get_guide_criteria_value (guide, GUIDE_CRITERIA_RADIUS)))
				{
					return 0.0;
				}
			}
		}
	}

	get_local_entity_vec3d (en, VEC3D_TYPE_POSITION, &pos);

	attitude = get_local_entity_attitude_matrix_ptr (en);

	sector = get_local_entity_parent (en, LIST_TYPE_SECTOR);

	//
	// Look Ahead
	//

	pos.x += ((*attitude) [2][0] * aircraft_database [raw->ac.mob.sub_type].cruise_velocity * HELICOPTER_STRUCTURE_AVOIDANCE_LOOKAHEAD_TIME);
	pos.y = 0.0;
	pos.z += ((*attitude) [2][2] * aircraft_database [raw->ac.mob.sub_type].cruise_velocity * HELICOPTER_STRUCTURE_AVOIDANCE_LOOKAHEAD_TIME);

	//
	// scan the sector
	//

	max_height = 0;

	structure = get_local_entity_first_child (sector, LIST_TYPE_SECTOR);

	while (structure)
	{
		radius = get_local_entity_float_value (structure, FLOAT_TYPE_AVOIDANCE_RADIUS);

		if (radius > 0.0)
		{
			radius *= radius;

			test_pos = get_local_entity_vec3d_ptr (structure, VEC3D_TYPE_POSITION);

			d = get_sqr_2d_range (&pos, test_pos);

			if (d < radius)
			{
				max_height = max (max_height, get_local_entity_float_value (structure, FLOAT_TYPE_FIXED_STRUCTURE_HEIGHT));

				#if DEBUG_MODULE

				if (en == get_external_view_entity ())
				{
					debug_log ("%s - Max height %f", object_3d_enumeration_names [get_local_entity_int_value (structure, INT_TYPE_OBJECT_3D_SHAPE)], max_height);
				}

				#endif
			}
		}

		structure = get_local_entity_child_succ (structure, LIST_TYPE_SECTOR);
	}

	return max_height;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float helicopter_movement_altitude_follow (entity *en, entity *guide, vec3d *wp_pos)
{
	helicopter
		*raw;

	float
		min_height,
		current_height,
		required_height,
		terrain_elevation;

	entity
		*leader;

	vec3d
		test_pos,
		*pos;

	matrix3x3
		*attitude;

	guide_terrain_follow_modes
		terrain_follow;

	int
		loop;

	ASSERT (en);

	ASSERT (guide);

	ASSERT (wp_pos);

	raw = get_local_entity_data (en);

	pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	current_height = pos->y;

	attitude = get_local_entity_attitude_matrix_ptr (en);

	//
	// Calculate required height (above sea level)
	//

	terrain_follow = get_local_entity_int_value (guide, INT_TYPE_TERRAIN_FOLLOW_MODE);

	if (terrain_follow != GUIDE_TERRAIN_FOLLOW_NONE)
	{
		//
		// Find Required Altitude
		//

		if ((terrain_follow == GUIDE_TERRAIN_FOLLOW_ATTACK_ALTITUDE) || (get_local_entity_int_value (en, INT_TYPE_POSITION_HOLD)))
		{
			min_height = get_local_entity_float_value (en, FLOAT_TYPE_ATTACK_ALTITUDE) + helicopter_movement_structure_avoidance (en);
		}
		else
		{
			leader = get_local_entity_ptr_value (guide, PTR_TYPE_TASK_LEADER);

			if (en == leader)
			{
				min_height = get_local_entity_float_value (en, FLOAT_TYPE_CRUISE_ALTITUDE) + helicopter_movement_structure_avoidance (en);
			}
			else
			{
				min_height = max (get_local_entity_float_value (leader, FLOAT_TYPE_RADAR_ALTITUDE), (get_local_entity_float_value (en, FLOAT_TYPE_CRUISE_ALTITUDE) + helicopter_movement_structure_avoidance (en)));
			}
		}

		//
		// Get samples from "Look Ahead" back to "Current position" so that the terrain_info has current position stored.
		//

		terrain_elevation = 0.0;

		for (loop = HELICOPTER_TERRAIN_AVOIDANCE_LOOKAHEAD_SAMPLE_NUMBER; loop >= 0; loop --)
		{

			test_pos.x = pos->x + ((*attitude) [2][0] * loop * aircraft_database [raw->ac.mob.sub_type].cruise_velocity * HELICOPTER_TERRAIN_AVOIDANCE_LOOKAHEAD_TIME);
			test_pos.y = pos->y + 0.0;
			test_pos.z = pos->z + ((*attitude) [2][2] * loop * aircraft_database [raw->ac.mob.sub_type].cruise_velocity * HELICOPTER_TERRAIN_AVOIDANCE_LOOKAHEAD_TIME);

			bound_position_to_map_area (&test_pos);

			terrain_elevation = max (terrain_elevation, get_3d_terrain_point_data (test_pos.x, test_pos.z, &raw->ac.terrain_info));
		}

		//
		// find required height (above sea level)
		//

		required_height = min_height + terrain_elevation;
	}
	else
	{

		// was here to make helicopters avoid buildings when doing troop insertion, but it messed up the carrier landing.
		//terrain_elevation = get_3d_terrain_point_data (pos->x, pos->z, &raw->ac.terrain_info);
		//required_height = max (wp_pos->y, terrain_elevation + helicopter_movement_structure_avoidance (en));
		required_height = wp_pos->y;
	}

	return required_height;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void helicopter_movement_calculate_new_position (entity *en, entity *guide, vec3d *wp_pos)
{
	vec3d
		*position,
		*mv;

	helicopter
		*raw;

	float
		min_height;

	ASSERT (en);

	ASSERT (guide);

	raw = get_local_entity_data (en);

	position = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	mv = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_MOTION_VECTOR);

	position->x += (mv->x * get_entity_movement_delta_time ());
	position->y += (mv->y * get_entity_movement_delta_time ());
	position->z += (mv->z * get_entity_movement_delta_time ());

	bound_position_to_map_volume (position);

	min_height = get_3d_terrain_point_data_elevation (&raw->ac.terrain_info) + get_local_entity_float_value (en, FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE);

	if (get_local_entity_int_value (guide, INT_TYPE_TERRAIN_FOLLOW_MODE != GUIDE_TERRAIN_FOLLOW_NONE))
	{

		min_height += 2.0;
	}

	// bound to floor. Allow for pitch of aircraft... assume 5m to nose. Stop motion vector.

	if (position->y <= min_height)
	{

		float
			pitch;

		pitch = get_pitch_from_attitude_matrix (raw->ac.mob.attitude);

		min_height += 5.0 * sin (fabs (pitch));

		raw->ac.mob.motion_vector.y = max (raw->ac.mob.motion_vector.y, 0.0);

		position->y = max (position->y, min_height);
	}

	set_local_entity_vec3d (en, VEC3D_TYPE_POSITION, position);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void clear_helicopter_velocity (entity *en)
{
	vec3d
		velocity;

	velocity.x = 0.0;
	velocity.y = 0.0;
	velocity.z = 0.0;

	set_local_entity_vec3d (en, VEC3D_TYPE_MOTION_VECTOR, &velocity);

	set_local_entity_float_value (en, FLOAT_TYPE_VELOCITY, 0.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_player_helicopter_waypoint_distance (entity *en)
{
	vec3d
		wp_vel,
		wp_pos;

	ASSERT (en);

	//
	// abort if mobile is not moving (i.e. landed, or dead)
	//

	if ((!get_local_entity_int_value (en, INT_TYPE_MOBILE_MOVING)) && (get_local_entity_int_value (en, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI))
	{

		return;
	}

	//
	// abort if mobile is not alive (operational state dying is not caught by INT_TYPE_MOBILE_MOVING))
	//

	if (!get_local_entity_int_value (en, INT_TYPE_ALIVE))
	{

		return;
	}

	//
	// calculate helicopter fly-to position, and store distance from it
	//

	helicopter_movement_get_waypoint_position_and_velocity (en, &wp_pos, &wp_vel);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void helicopter_adjust_waypoint_position_with_los (entity *en, vec3d *wp_pos)
{

	float
		closest_range,
		range,
		distance;

	vec3d
		closest_collision_point,
		collision_point,
		*en_pos,
		*hc_pos;

	entity
		*closest_hc,
		*group,
		*hc;

	if (get_local_entity_int_value (en, INT_TYPE_GROUP_LEADER))
	{

		// leader doesn't avoid wingmen

		return;
	}

	// check los to wp_pos

	en_pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

	hc = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

	#if 0
	{
		rgb_colour
			los_colour;

		los_colour.r = 0.0;
		los_colour.g = 0.0;
		los_colour.b = 255.0;
		los_colour.a = 255.0;

		// vertical line to wp
		create_debug_3d_line (en_pos, wp_pos, los_colour, 0.001);
	}
	#endif

	closest_range = ((500.0 * METRE) * (500.0 * METRE));

	closest_hc = NULL;

	while (hc)
	{

		if (hc != en)
		{

			hc_pos = get_local_entity_vec3d_ptr (hc, VEC3D_TYPE_POSITION);

			range = get_sqr_3d_range (hc_pos, en_pos);

			if (range < closest_range)
			{

				distance = get_3d_perp_dist_of_point_from_line (en_pos, wp_pos, hc_pos, &collision_point);

				if (distance <= HELICOPTER_AVOIDANCE_DISTANCE)
				{

					closest_range = range;

					closest_hc = hc;

					closest_collision_point = collision_point;
				}
			}
		}

		hc = get_local_entity_child_succ (hc, LIST_TYPE_MEMBER);
	}

	if (closest_hc)
	{

		vec3d
			new_pos;

		hc_pos = get_local_entity_vec3d_ptr (closest_hc, VEC3D_TYPE_POSITION);

		new_pos.x = closest_collision_point.x - hc_pos->x;
		new_pos.y = closest_collision_point.y - hc_pos->y;
		new_pos.z = closest_collision_point.z - hc_pos->z;

		normalise_any_3d_vector (&new_pos);

		new_pos.x = hc_pos->x + (2.0 * HELICOPTER_AVOIDANCE_DISTANCE * new_pos.x);
		new_pos.y = hc_pos->y + (2.0 * HELICOPTER_AVOIDANCE_DISTANCE * new_pos.y);
		new_pos.z = hc_pos->z + (2.0 * HELICOPTER_AVOIDANCE_DISTANCE * new_pos.z);

		wp_pos->x = new_pos.x;
		wp_pos->y = new_pos.y;
		wp_pos->z = new_pos.z;

		#if 0
		{
			rgb_colour
				los_colour;

			los_colour.r = 255.0;
			los_colour.g = 0.0;
			los_colour.b = 0.0;
			los_colour.a = 255.0;

			// vertical line to wp
			create_debug_3d_line (en_pos, wp_pos, los_colour, 0.001);
		}
		#endif
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void debug_visuals (entity *en, vec3d *wp_pos)
{

	helicopter
		*raw;

	vec3d
		flat_wp_pos,
		*hc_pos;

	rgb_colour
		los_colour;

	ASSERT (en);

	raw = get_local_entity_data (en);

	hc_pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	// create first line from helicopter to waypoint position

	los_colour.r = 0.0;
	los_colour.g = 255.0;
	los_colour.b = 0.0;
	los_colour.a = 255.0;

	flat_wp_pos = *wp_pos;

	flat_wp_pos.y = hc_pos->y;

	// line to flat wp_pos
	create_debug_3d_line (hc_pos, &flat_wp_pos, los_colour, 0.001);

	los_colour.r = 0.0;
	los_colour.g = 0.0;
	los_colour.b = 255.0;
	los_colour.a = 255.0;

	// vertical line to wp
	create_debug_3d_line (&flat_wp_pos, wp_pos, los_colour, 0.001);

	// create arrow at wp_pos
	{

		vec3d
			temp_position,
			temp_direction;

			viewpoint
				vp;

		temp_position = *wp_pos;

		temp_direction.x = 0.0;
		temp_direction.y = 1.0;
		temp_direction.z = 0.0;

		memcpy (&vp.position, wp_pos, sizeof (vec3d));

		get_matrix3x3_from_unit_vec3d_and_roll (vp.attitude, &temp_direction, 0.0);

		create_debug_3d_object (&vp, OBJECT_3D_SPHERICAL_TEST, 0.001, 1.0);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
