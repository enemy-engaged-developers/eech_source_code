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

#define NEW_FIXED_WING_FLIGHT_MODEL	1

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_NEW_FLIGHT_MODULE 	0

#define DEBUG_MODULE 					0

#define DEBUG_INFINITY_SLIDE			0

#define GROUND_ACCELERATION 			3.0

#define AIR_ACCELERATION 				30.0

#define PITCH_MIN 						-30.0

#define PITCH_MAX 						30.0

#define AIRCRAFT_MAX_FLARE_ANGLE					rad (15.0)

#define AIRCRAFT_MAX_LANDING_FLARE_ANGLE		rad (4.0)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void fixed_wing_collision_avoidance (entity *en, vec3d *des_acc);

void fixed_wing_attain_waypoint (entity *en, vec3d *wp_vec, vec3d *vel);

void fixed_wing_aim_correction (entity *en, vec3d *wp_vec, vec3d *vel);

void fixed_wing_follow_waypoint (entity *en, vec3d *vel, vec3d *des_acc);

void fixed_wing_pursue_guide (entity *en, vec3d *vel, vec3d *des_acc);

void fixed_wing_navigator (entity *en, vec3d *acc, vec3d *vel);

void fixed_wing_calc_attitude (entity *en, vec3d *acc, vec3d *vel);

void fixed_wing_bound_vector_scale (vec3d *vector, float min, float max);

float fixed_wing_accum (entity *en, vec3d *accumulator, vec3d *new_acc);

void fixed_wing_set_velocity (entity *en, vec3d *acc, vec3d *vel);

void fixed_wing_land_jet (entity *en, vec3d *new_pos);

void fixed_wing_flight (entity *en, vec3d *new_pos);


void fixed_wing_taxi(entity *en, vec3d *current_pos, vec3d *dist, vec3d *new_pos, float ter_elev);

void fixed_wing_crash_movement (entity *en);

void draw_aircraft_turn_radius (entity *en);

void draw_debug_circle_line (vec3d *centre, float radius);

void clear_fixed_wing_velocity (entity *en);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void fixed_wing_collision_avoidance (entity *en, vec3d *des_acc)
{
	entity
		*group,
		*member,
		*nearest;

	fixed_wing
		*raw,
		*jet_raw;

	matrix3x3
		wp_attitude;
		
	vec3d
		*curr_pos,
		*jet_pos,
		jet_to_jet,
		nearest_jet_to_jet,
		local_jet_to_jet,
		wp_pos,
		wp_vec;

	float
		test_distance,
		shortest_distance,
		jet_to_jet_2d_distance,
		avoid_distance,
		max_speed,
		wp_distance;

	nearest = NULL;

	raw = get_local_entity_data (en);

	// if entity is not the leader, test for potential collision
	if (!get_local_entity_int_value(en, INT_TYPE_GROUP_LEADER))
	{

		curr_pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

		shortest_distance = get_local_entity_float_value (en, FLOAT_TYPE_VELOCITY);

		fixed_wing_movement_get_waypoint_position (en, &wp_pos);

		wp_vec.x = wp_pos.x - curr_pos->x;
		wp_vec.y = wp_pos.y - curr_pos->y;
		wp_vec.z = wp_pos.z - curr_pos->z;

		wp_distance = get_3d_vector_magnitude (&wp_vec);
		
		normalise_any_3d_vector (&wp_vec);

		get_matrix3x3_from_unit_vec3d (wp_attitude, &wp_vec);

		group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

		ASSERT (group);
		
		member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

		// find nearest jet to ours that is in the way of our objective
		while (member)
		{
			if (member != en)
			{
				jet_raw = get_local_entity_data (member);
				
				jet_pos = get_local_entity_vec3d_ptr (member, VEC3D_TYPE_POSITION);
		
				jet_to_jet.x = (jet_pos->x + jet_raw->ac.mob.motion_vector.x * get_entity_movement_delta_time()) - (curr_pos->x + raw->ac.mob.motion_vector.x * get_entity_movement_delta_time());
				jet_to_jet.y = (jet_pos->y + jet_raw->ac.mob.motion_vector.y * get_entity_movement_delta_time()) - (curr_pos->y + raw->ac.mob.motion_vector.y * get_entity_movement_delta_time());
				jet_to_jet.z = (jet_pos->z + jet_raw->ac.mob.motion_vector.z * get_entity_movement_delta_time()) - (curr_pos->z + raw->ac.mob.motion_vector.z * get_entity_movement_delta_time());
		
				multiply_transpose_matrix3x3_vec3d(&local_jet_to_jet, wp_attitude, &jet_to_jet);

				test_distance = get_3d_vector_magnitude (&jet_to_jet);

				//is the jet between us and our waypoint?
				if ( (local_jet_to_jet.z > 0.0) && (test_distance < wp_distance) )
				{

					// get 2d distance & collision avoidance radius
					jet_to_jet_2d_distance = (local_jet_to_jet.x * local_jet_to_jet.x + local_jet_to_jet.y * local_jet_to_jet.y);

					avoid_distance = aircraft_database[raw->ac.mob.sub_type].avoidance_radius +
											aircraft_database[jet_raw->ac.mob.sub_type].avoidance_radius;

					//does the jet get in our way?
					if (jet_to_jet_2d_distance < (avoid_distance * avoid_distance))
					{
						//is it the nearest jet in our way?	
						if (test_distance < shortest_distance)
						{
							nearest = member;
		
							nearest_jet_to_jet = local_jet_to_jet;
								
							shortest_distance = test_distance;
						}
					}
				}
			}

			member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
		}
		
	}

	// if a jet is in the way, modify our direction

	if (nearest != NULL)
	{
		max_speed = get_local_entity_float_value (en, FLOAT_TYPE_CRUISE_VELOCITY) * 2.0;

		//get local acc. request
		nearest_jet_to_jet.x = -nearest_jet_to_jet.x;
		nearest_jet_to_jet.y = -nearest_jet_to_jet.y;
		nearest_jet_to_jet.z = 0.0;

		normalise_any_3d_vector (&nearest_jet_to_jet);

		//rotate back into world coord sys

		multiply_matrix3x3_vec3d(des_acc, wp_attitude, &nearest_jet_to_jet);

		des_acc->x *= max_speed;
		des_acc->y *= max_speed;
		des_acc->z *= max_speed;

	}
	
	// otherwise no jet is in the way
	else
	{
		// set desired acceleration to nothing
		des_acc->z = des_acc->y = des_acc->x = 0.0;
	}
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void fixed_wing_attain_waypoint (entity *en, vec3d *wp_vec, vec3d *vel)
{
	fixed_wing
		*raw;

	float
		distance_to_wp,
		max_turn_radius;

	raw = get_local_entity_data (en);

	distance_to_wp = get_3d_vector_magnitude (wp_vec);

	max_turn_radius = (raw->ac.mob.velocity * raw->ac.mob.velocity) / aircraft_database [raw->ac.mob.sub_type].g_max;

	//test to see if waypoint is attainable
	if (distance_to_wp < max_turn_radius)
	{
		
		//continue along current motion vector until waypoint can be reached
		*wp_vec = *vel;

		#if DEBUG_MODULE

		if (en == get_external_view_entity ())
		{
			debug_filtered_log ("UTAW: %s %d", entity_sub_type_aircraft_names[raw->ac.mob.sub_type], get_local_entity_index(en));
		}

		#endif

	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void fixed_wing_aim_correction (entity *en, vec3d *wp_vec, vec3d *vel)
{
	fixed_wing
		*raw;

	vec3d
		dir_vec;

	raw = get_local_entity_data (en);

	if (!check_zero_3d_vector (vel))
	{
		if ((get_3d_vector_dot_product (wp_vec, vel) < 0.0))
		{
			multiply_transpose_matrix3x3_vec3d (&dir_vec, raw->ac.mob.attitude, wp_vec);
	
	//		dir_vec.y = fabs (dir_vec.z * get_local_entity_float_value(en, FLOAT_TYPE_MAX_VERTICAL_TURN_ALLOWANCE));
	
			if (fabs (dir_vec.y) > fabs(dir_vec.z))
			{
				dir_vec.y = fabs (dir_vec.y);
			}
			else
			{
				dir_vec.y =fabs (dir_vec.z);
			}
	
			dir_vec.y *= get_local_entity_float_value(en, FLOAT_TYPE_MAX_VERTICAL_TURN_ALLOWANCE);
			
			dir_vec.z = 0.0;
	
			normalise_any_3d_vector (&dir_vec);
	
			multiply_matrix3x3_vec3d (wp_vec, raw->ac.mob.attitude, &dir_vec);
	
	//old methods
	/*
			//max_roll or equivalent should be in ac_dbase
			max_roll = aircraft_database[raw->ac.mob.sub_type].max_turn_rate;
	
			if (max_roll >= (rad (90.0)))
			{
				//this is wrong if the plane is inverted - will it ever be the case
				aim_vec.x = raw->ac.mob.yv.x;
				aim_vec.y = raw->ac.mob.yv.y;
				aim_vec.z = raw->ac.mob.yv.z;
			}
			else
			{
				//cheap horizontal vector to aim for - potentially problematic?
				*aim_vec = raw->ac.mob.xv;
	
				aim_vec->y = 0.0;
	
				normalise_any_3d_vector (aim_vec);
			}
	*/
		}
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void fixed_wing_follow_waypoint (entity *en, vec3d *vel, vec3d *des_acc)
{
	fixed_wing
		*raw;
		
	entity
		*guide;
		
	vec3d
		*curr_pos,
		wp_pos,
		wp_vec;

	float
		wp_vel;

	raw = get_local_entity_data (en);

	fixed_wing_movement_get_waypoint_position (en, &wp_pos);

	curr_pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	guide = get_local_entity_parent (en, LIST_TYPE_FOLLOWER);

	ASSERT (guide);

	wp_vel = get_local_entity_float_value (guide, FLOAT_TYPE_VELOCITY);

	if(wp_vel == 0)
	{
		wp_vel = get_local_entity_float_value(en, FLOAT_TYPE_CRUISE_VELOCITY);
	}

	// get waypoint vector - no lookahead
	wp_vec.x = wp_pos.x - curr_pos->x;
	wp_vec.y = wp_pos.y - curr_pos->y;
	wp_vec.z = wp_pos.z - curr_pos->z;

	fixed_wing_attain_waypoint (en, &wp_vec, vel);

	// scale to correct length - that of waypoint velocity
	normalise_any_3d_vector (&wp_vec);

	fixed_wing_aim_correction (en, &wp_vec, vel);

	wp_vec.x *= wp_vel;
	wp_vec.y *= wp_vel;
	wp_vec.z *= wp_vel;
		
	// calculate desired change in velocity
	des_acc->x = wp_vec.x - vel->x;
	des_acc->y = wp_vec.y - vel->y;
	des_acc->z = wp_vec.z - vel->z;
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void fixed_wing_pursue_guide (entity *en, vec3d *vel, vec3d *des_acc)
{
	entity
		*guide,
		*leader;

	fixed_wing
		*leader_raw,
		*raw;

	vec3d
		*curr_pos,
		wp_pos,
		wp_vec,
		vel_shift;

	float
		slowdown_distance,
		distance,
		wp_speed,
		max_speed,
		sd_shift,
		ramped_speed,
		curr_speed;

	raw = get_local_entity_data (en);

	guide = get_local_entity_parent (en, LIST_TYPE_FOLLOWER);
	
	ASSERT (guide);
		
	leader = get_local_entity_ptr_value(guide, PTR_TYPE_TASK_LEADER);

	ASSERT (leader);

	leader_raw = get_local_entity_data(leader);

	wp_speed = get_local_entity_float_value (guide, FLOAT_TYPE_VELOCITY);

	if(wp_speed == 0)
	{
		wp_speed = get_local_entity_float_value(en, FLOAT_TYPE_CRUISE_VELOCITY);
	}
	
	fixed_wing_movement_get_waypoint_position (en, &wp_pos);

	curr_pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	curr_speed = raw->ac.mob.velocity;

	max_speed = get_local_entity_float_value (en, FLOAT_TYPE_CRUISE_VELOCITY) * 2.0;

	slowdown_distance = max_speed * 1.5;

	// shift slowdown radius forwards so point of velocity equilibrium is coincident with formation position required

	sd_shift = (wp_speed * 1.5);

	vel_shift = leader_raw->ac.mob.motion_vector;

	normalise_any_3d_vector (&vel_shift);

	// get vector to the offset waypoint
	wp_vec.x = (wp_pos.x + vel_shift.x * sd_shift) - (curr_pos->x + vel->x * get_entity_movement_delta_time ());
	wp_vec.y = (wp_pos.y + vel_shift.y * sd_shift) - (curr_pos->y + vel->y * get_entity_movement_delta_time ());
	wp_vec.z = (wp_pos.z + vel_shift.z * sd_shift) - (curr_pos->z + vel->z * get_entity_movement_delta_time ());

	distance = get_3d_vector_magnitude (&wp_vec);

	if (distance > 0.0)
	{
		// ramp the speed linearly to zero from slowdown distance to formation point
		ramped_speed = max_speed * (distance / slowdown_distance);
	
		ramped_speed = bound (ramped_speed, -max_speed, max_speed);
	
		normalise_3d_vector_given_magnitude (&wp_vec, distance);
	
		fixed_wing_aim_correction (en, &wp_vec, vel);
		
		wp_vec.x *= ramped_speed;
		wp_vec.y *= ramped_speed;
		wp_vec.z *= ramped_speed;
	
		// calculate desired change in velocity
		des_acc->x = wp_vec.x - vel->x;
		des_acc->y = wp_vec.y - vel->y;
		des_acc->z = wp_vec.z - vel->z;
	}
	else
	{
		des_acc->x = -vel->x;
		des_acc->y = -vel->y;
		des_acc->z = -vel->z;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void fixed_wing_bound_vector_scale (vec3d *vector, float min, float max)
{
	float
		distance;

	distance = get_3d_vector_magnitude (vector);

	if (distance > max)
	{
		normalise_3d_vector_given_magnitude (vector, distance);

		vector->x *= max;
		vector->y *= max;
		vector->z *= max;
	}
	else if (distance < min)
	{
		normalise_3d_vector_given_magnitude (vector, distance);

		vector->x *= min;
		vector->y *= min;
		vector->z *= min;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void fixed_wing_set_velocity (entity *en, vec3d *acc, vec3d *velocity)
{
	fixed_wing
		*raw;

	float
		d,
		acc_avail,
		curr_speed,
		min_speed,
		max_speed;

	raw = get_local_entity_data (en);

	curr_speed = raw->ac.mob.velocity;

	min_speed = max_speed = get_local_entity_float_value(en, FLOAT_TYPE_CRUISE_VELOCITY);

	// arbitrary values - seem to work tho'. p'haps should be in a dbase somewhere?
	min_speed *= 0.7;

	max_speed *= 2.0;
	
	// debug - possibly unneccesary control?
	acc_avail = 1.0;
	// debug

	d = get_3d_vector_magnitude (acc);

	// limit acceleration
	if (d > aircraft_database[raw->ac.mob.sub_type].g_max)
	{

		//used to get inverse attitude matrix, multiply acc vec by it, normalise, scale by g_max & rotate back
		//inverse multiply totally unneccesary?

		normalise_3d_vector_given_magnitude (acc, d);

		// perform limiting
		acc->x *= aircraft_database[raw->ac.mob.sub_type].g_max;
		acc->y *= aircraft_database[raw->ac.mob.sub_type].g_max;
		acc->z *= aircraft_database[raw->ac.mob.sub_type].g_max;
	}

	velocity->x += acc->x * acc_avail * get_entity_movement_delta_time ();
	velocity->y += acc->y * acc_avail * get_entity_movement_delta_time ();
	velocity->z += acc->z * acc_avail * get_entity_movement_delta_time ();
	
	//ASSERT (!check_zero_3d_vector (velocity));

	fixed_wing_bound_vector_scale (velocity, min_speed, max_speed);

	//ASSERT (!check_zero_3d_vector (velocity));

	raw->ac.mob.velocity = get_3d_vector_magnitude (velocity);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// accumulates all acceleration vectors, works on a first come first served basis
float fixed_wing_accum(entity *en, vec3d *accumulator, vec3d *new_acc)
{

	float
		acc_avail,
		vm,
		new_mag,
		max_acc;


	max_acc = get_local_entity_float_value (en, FLOAT_TYPE_CRUISE_VELOCITY) * 2.0;
	
  	acc_avail = max_acc - get_3d_vector_magnitude(accumulator);

	vm = get_3d_vector_magnitude(new_acc);

  	new_mag = vm < acc_avail ? vm : acc_avail;

	// scale newacc by new_mag
	normalise_any_3d_vector(new_acc);

  	accumulator->x += new_acc->x * new_mag;
  	accumulator->y += new_acc->y * new_mag;
  	accumulator->z += new_acc->z * new_mag;

  	return new_mag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void fixed_wing_navigator(entity *en, vec3d *acc, vec3d *vel)
{
	vec3d
		acc_req;
		
	acc_req.x = acc_req.y = acc_req.z = 0.0;

	acc->x = acc->y = acc->z = 0.0;

	if( !get_local_entity_int_value (en, INT_TYPE_TASK_LEADER) )
	{
		fixed_wing_collision_avoidance (en, &acc_req);

		fixed_wing_accum(en, acc, &acc_req);

		fixed_wing_pursue_guide (en, vel, &acc_req);

		fixed_wing_accum(en, acc, &acc_req);

	}
	else
	{
		fixed_wing_collision_avoidance (en, &acc_req);

		fixed_wing_accum(en, acc, &acc_req);

		fixed_wing_follow_waypoint (en, vel, acc);

		fixed_wing_accum(en, acc, &acc_req);
	}
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void fixed_wing_calc_attitude(entity *en, vec3d *acc, vec3d *vel)
{
	fixed_wing
		*raw;

	vec3d
		norm_mv;
			
	float
		pitch,
		old_heading,
		heading,
		change_in_heading,
		roll,
		max_roll,
		factor;

	raw = get_local_entity_data (en);

	old_heading = get_heading_from_attitude_matrix (raw->ac.mob.attitude);

	roll = get_roll_from_attitude_matrix (raw->ac.mob.attitude);

	norm_mv = raw->ac.mob.motion_vector;

	normalise_any_3d_vector (&norm_mv);

	heading = atan2 (norm_mv.x, norm_mv.z);

	pitch = asin (norm_mv.y);

	//cih not best value to use, as inversion infers 180deg roll. need change in local x.
	
	change_in_heading = heading - old_heading;

	//wrap cih to get correct change in roll
	if (change_in_heading > PI)
	{
		change_in_heading -= PI2;
	}
	else if (change_in_heading < (-PI))
	{
		change_in_heading += PI2;
	}


	max_roll = get_local_entity_float_value (en, FLOAT_TYPE_MAX_ROLL);

	factor = max_roll * 0.01;

	if (fabs (change_in_heading) >= factor)
	{
		roll += change_in_heading;

	}
	else
	{
		factor = (factor - fabs (change_in_heading)) / factor;

		roll -= (roll * factor * get_entity_movement_delta_time ());

		roll += (change_in_heading * (1.0 - factor));

	}

	//wrap roll
	if (max_roll >= PI)
	{
		if (roll > PI)
		{
			roll -= PI2;
		}
		else if (roll < (-PI))
		{
			roll += PI2;
		}
	}
	else
	{
		
		roll = bound (roll, -max_roll, max_roll);
	}

	get_3d_transformation_matrix (raw->ac.mob.attitude, heading, pitch, roll);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void fixed_wing_land_jet (entity *en, vec3d *new_pos)
{
	entity
		*guide;
		
	fixed_wing
		*raw;

	vec3d
		wp_vec,
		wp_pos,
		*curr_pos;

	float
		factor,
		range,
		wp_vel,
		delta_vel,
		heading,
		pitch,
		roll,
		desired_heading,
		desired_pitch,
		delta_heading,
		delta_pitch,
		delta_roll;

	raw = get_local_entity_data (en);
		
	fixed_wing_movement_get_waypoint_position (en, &wp_pos);

	curr_pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	guide = get_local_entity_parent (en, LIST_TYPE_FOLLOWER);

	ASSERT (guide);

	wp_vel = get_local_entity_float_value (guide, FLOAT_TYPE_VELOCITY);

	if(wp_vel == 0)
	{
		wp_vel = get_local_entity_float_value(en, FLOAT_TYPE_CRUISE_VELOCITY);
	}

	desired_pitch = 0.0;
	
	// get waypoint vector - no lookahead
	wp_vec.x = wp_pos.x - curr_pos->x;
	wp_vec.y = wp_pos.y - curr_pos->y;
	wp_vec.z = wp_pos.z - curr_pos->z;

	range = get_3d_vector_magnitude (&wp_vec);
	
	// scale to correct length - that of waypoint velocity
	normalise_any_3d_vector (&wp_vec);

	//attitude
	heading = get_heading_from_attitude_matrix (raw->ac.mob.attitude);

	pitch = get_pitch_from_attitude_matrix (raw->ac.mob.attitude);

	roll = get_roll_from_attitude_matrix (raw->ac.mob.attitude);
	
	//heading
	desired_heading = atan2 (wp_vec.x, wp_vec.z);

	//pitch
	if (range < 100.0)
	{
		desired_pitch = AIRCRAFT_MAX_LANDING_FLARE_ANGLE;
	}		
	else if (range < 1000.0)
	{
		factor = (1000.0 - range) * 0.001;

		desired_pitch = AIRCRAFT_MAX_FLARE_ANGLE * factor;
	}
	else
	{
		desired_pitch = asin (wp_vec.y);
	}
	
	delta_heading = (desired_heading - heading) * get_entity_movement_delta_time ();

	delta_pitch = (desired_pitch - pitch) * get_entity_movement_delta_time ();

	delta_roll = -roll * get_entity_movement_delta_time ();

	heading += delta_heading;

	pitch += delta_pitch;

	roll += delta_roll;

	get_3d_transformation_matrix (raw->ac.mob.attitude, heading, pitch, roll);


	//velocity
	delta_vel = (wp_vel - raw->ac.mob.velocity);

	//make braking less immediate
	if (fabs (delta_vel) > 10.0)
	{
		delta_vel = sign (delta_vel) * 5.0;
	}

	raw->ac.mob.velocity += delta_vel;
	
	//position
	wp_vec.x *= raw->ac.mob.velocity;
	wp_vec.y *= raw->ac.mob.velocity;
	wp_vec.z *= raw->ac.mob.velocity;
		
	new_pos->x = curr_pos->x + wp_vec.x * get_entity_movement_delta_time ();
	new_pos->y = curr_pos->y + wp_vec.y * get_entity_movement_delta_time ();
	new_pos->z = curr_pos->z + wp_vec.z * get_entity_movement_delta_time ();

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void fixed_wing_flight (entity *en, vec3d *new_pos)
{
	entity
		*wp;
		
	fixed_wing
		*raw;

	vec3d
		*current_pos,
		acc,
		vel;

	int
		curr_wp;

	raw = get_local_entity_data(en);

	current_pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	vel = raw->ac.mob.motion_vector;

	//ASSERT (!check_zero_3d_vector (&vel));

	wp = get_local_entity_current_waypoint (en);

	curr_wp = get_local_entity_int_value (wp, INT_TYPE_ENTITY_SUB_TYPE);

	if (curr_wp != ENTITY_SUB_TYPE_WAYPOINT_TOUCH_DOWN)
	{
		// get acceleration vector
		fixed_wing_navigator(en, &acc, &vel);
	
		// set new velocity
		fixed_wing_set_velocity (en, &acc, &vel);
		
		//ASSERT (!check_zero_3d_vector (&vel));

		// set new position
		new_pos->x = current_pos->x + vel.x * get_entity_movement_delta_time();
		new_pos->y = current_pos->y + vel.y * get_entity_movement_delta_time();
		new_pos->z = current_pos->z + vel.z * get_entity_movement_delta_time();
	
		// calculate attiude
		fixed_wing_calc_attitude (en, &acc, &vel);
	}
	else
	{
		fixed_wing_land_jet (en, new_pos);
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void fixed_wing_taxi(entity *en, vec3d *current_pos, vec3d *dist, vec3d *new_pos, float ter_elev)
{
	entity
		*guide;

	fixed_wing
		*raw;

	vec3d
		wp_pos,
		wp_vec;
		
	float
		wp_vel,
		delta_heading,
		current_heading,
		current_pitch,
		desired_heading,
		new_heading,
		new_pitch,
		desired_velocity;


	raw = get_local_entity_data (en);

	//
	// aircraft on the ground
	//

	//
	// GET WAYPOINT VELOCITY
	//
	
	guide = get_local_entity_parent (en, LIST_TYPE_FOLLOWER);

	ASSERT (guide);

	wp_vel = get_local_entity_float_value (guide, FLOAT_TYPE_VELOCITY);

	if (wp_vel == 0.0)
	{
		wp_vel = get_local_entity_float_value (en, FLOAT_TYPE_CRUISE_VELOCITY);
	}

	//
	// GET VECTOR TO WAYPOINT
	//
	
	fixed_wing_movement_get_waypoint_position (en, &wp_pos);

	wp_vec.x = wp_pos.x - current_pos->x;
	wp_vec.y = wp_pos.y - (current_pos->y - get_local_entity_float_value (en, FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE));
	wp_vec.z = wp_pos.z - current_pos->z;
		
	desired_velocity = wp_vel;

	raw->ac.mob.velocity += min ((desired_velocity - raw->ac.mob.velocity), GROUND_ACCELERATION) * get_entity_movement_delta_time ();

	// heading

		current_heading = get_heading_from_attitude_matrix (raw->ac.mob.attitude);

		desired_heading = atan2 (wp_vec.x, wp_vec.z);

		delta_heading = desired_heading - current_heading;

		if (delta_heading <= -PI)
		{
		
			delta_heading += PI2;
		}
		
		if (delta_heading >= PI)
		{
		
			delta_heading -= PI2;
		}
			
		// calculate new attitude

		delta_heading = bound (delta_heading, rad (-30.0), rad (30.0));// taxiing turn rate

		new_heading = current_heading + (delta_heading * get_entity_movement_delta_time ());

		#if DEBUG_MODULE

		debug_log ("current heading %f, desired heading %f, delta_heading %f",
					current_heading, desired_heading, delta_heading);

		#endif

	current_pitch = get_pitch_from_attitude_matrix (raw->ac.mob.attitude);

	if (current_pitch > aircraft_database [raw->ac.mob.sub_type].fuselage_angle)
	{
		new_pitch = current_pitch + ((aircraft_database [raw->ac.mob.sub_type].fuselage_angle - current_pitch) * get_entity_movement_delta_time ());
	}
	else
	{
		new_pitch = aircraft_database [raw->ac.mob.sub_type].fuselage_angle;
	}

	get_3d_transformation_matrix (raw->ac.mob.attitude, new_heading, new_pitch, 0.0);
	
	dist->x = min (raw->ac.mob.velocity * raw->ac.mob.zv.x * get_entity_movement_delta_time (), fabs (wp_vec.x));
	dist->y = 0.0;
	dist->z = min (raw->ac.mob.velocity * raw->ac.mob.zv.z * get_entity_movement_delta_time (), fabs (wp_vec.z));

	#if DEBUG_MODULE

	debug_log ("current heading %d, desired heading %d, delta_heading %f, dist %f, %f, %f, sqr_range %f, vel %f",
						current_heading, desired_heading, delta_heading, dist->x, dist->y, dist->z, sqr_range, raw->ac.mob.velocity);

	#endif
	
	new_pos->x = current_pos->x + dist->x;
	new_pos->y = current_pos->y + dist->y;
	new_pos->z = current_pos->z + dist->z;
	
	bound_position_to_map_volume (new_pos);
	
	new_pos->y = ter_elev + get_local_entity_float_value (en, FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE);

	raw->ac.mob.motion_vector.x = raw->ac.mob.velocity * raw->ac.mob.zv.x;
	raw->ac.mob.motion_vector.y = 0.0;
	raw->ac.mob.motion_vector.z = raw->ac.mob.velocity * raw->ac.mob.zv.z;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void fixed_wing_movement_get_waypoint_position (entity *en, vec3d *wp_pos)
{
	entity
		*wp,
		*group,
		*guide;

	float
		distance,
		min_height,
		terrain_elevation;

	vec3d
		*pos;

	guide_terrain_follow_modes
		terrain_follow;

/*
	if (get_external_view_entity () == en)
	{

		draw_debug_takeoff_landing_routes ();
	}
	*/

	ASSERT (en);

	ASSERT (wp_pos);

	group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

	ASSERT (group);

	guide = get_local_entity_parent (en, LIST_TYPE_FOLLOWER);

	ASSERT (guide);

	pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	ASSERT (pos);

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
		
				//
				// terrain check
				//
	
				terrain_follow = get_local_entity_int_value (guide, INT_TYPE_TERRAIN_FOLLOW_MODE);
		
				if (terrain_follow != GUIDE_TERRAIN_FOLLOW_NONE)
				{
					entity
						*sector;
		
					fixed_wing
						*raw;
		
					raw = get_local_entity_data (en);
		
					sector = get_local_entity_parent (en, LIST_TYPE_SECTOR);
		
					terrain_elevation = get_3d_terrain_point_data_elevation (&raw->ac.terrain_info);
		
					if (terrain_follow == GUIDE_TERRAIN_FOLLOW_ATTACK_ALTITUDE)
					{
						min_height = get_local_entity_float_value (en, FLOAT_TYPE_ATTACK_ALTITUDE);
					}
					else 
					{
						min_height = get_local_entity_float_value (en, FLOAT_TYPE_CRUISE_ALTITUDE);
					}
	
					min_height = max (min_height, get_local_entity_float_value (sector, FLOAT_TYPE_TALLEST_STRUCTURE_HEIGHT) - terrain_elevation);
		
					min_height = max (get_local_entity_float_value (wp, FLOAT_TYPE_ALTITUDE), min_height);
		
					mobile_terrain_adjust_waypoint_height (en, wp_pos, min_height);
				}

				if (!get_local_entity_int_value (en, INT_TYPE_GROUP_LEADER))
				{
					//
					// Need to offset Task leader, so that it doesn't overlap with any other task leaders in the group
					//
					
					vec3d
						zv,
						xv;

					entity
						*group_leader;

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
	
					group_leader = get_local_entity_ptr_value (group, PTR_TYPE_GROUP_LEADER);
	
					ASSERT (group_leader);
		
					//
					// get formation
					//
		
					type = get_local_entity_int_value (group, INT_TYPE_GROUP_FORMATION);
		
					formation = get_formation (type);
		
					formation_count = formation->number_in_formation;
		
					formation_index = get_local_entity_int_value (en, INT_TYPE_GROUP_MEMBER_NUMBER);
		
					leader_formation_index = get_local_entity_int_value (group_leader, INT_TYPE_GROUP_MEMBER_NUMBER);
		
					ASSERT (formation_index < formation_count);
					ASSERT (leader_formation_index < formation_count);
		
					//
					// calculate position
					//
		
					zv.x = wp_pos->x - pos->x;
					zv.y = 0.0; 
					zv.z = wp_pos->z - pos->z;

					if (normalise_any_3d_vector (&zv) == 0.0)
					{
						xv.x = 0.0;
						xv.y = 0.0;
						xv.z = 1.0;
					}
					else
					{
						xv.x = zv.z;
						xv.y = 0.0;
						xv.z = -zv.x;
					}

					//
					// take waypoint position and SUBTRACT leaders formation position 
					//
				
					wp_pos->x -= ((xv.x * formation->sites [leader_formation_index].x) - (xv.z * formation->sites [leader_formation_index].z));
					wp_pos->z -= ((xv.x * formation->sites [leader_formation_index].z) + (xv.z * formation->sites [leader_formation_index].x));

					//
					// then ADD members formation position
					//
		
					wp_pos->x += ((xv.x * formation->sites [formation_index].x) - (xv.z * formation->sites [formation_index].z));
					wp_pos->y += formation->sites [formation_index].y;
					wp_pos->z += ((xv.x * formation->sites [formation_index].z) + (xv.z * formation->sites [formation_index].x));
				}
			}
			else
			{
				//
				// set wp pos to offset from flight leader
				//
		
				entity
					*task_leader;
		
				vec3d
					*xv,
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
		
				xv = get_local_entity_vec3d_ptr (task_leader, VEC3D_TYPE_XV);

				//
				// take leader position and SUBTRACT leaders formation position (coz leader is not necessarily formation pos 0)
				//
				
				wp_pos->x = leader_pos->x - ((xv->x * formation->sites [leader_formation_index].x) - (xv->z * formation->sites [leader_formation_index].z));
				wp_pos->y = leader_pos->y - formation->sites [leader_formation_index].y;
				wp_pos->z = leader_pos->z - ((xv->x * formation->sites [leader_formation_index].z) + (xv->z * formation->sites [leader_formation_index].x));

				//
				// then ADD members formation position
				//
		
				wp_pos->x += ((xv->x * formation->sites [formation_index].x) - (xv->z * formation->sites [formation_index].z));
				wp_pos->y += formation->sites [formation_index].y;
				wp_pos->z += ((xv->x * formation->sites [formation_index].z) + (xv->z * formation->sites [formation_index].x));

				wp_pos->y -= get_local_entity_float_value (task_leader, FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE);
			}
		}
	
		//
		// align waypoint altitude with the lowest point on the aircraft
		//
	
		wp_pos->y += get_local_entity_float_value (en, FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE);
	}
	
	//
	// calculate distance of entity to desire position
	//

	distance = get_2d_range (pos, wp_pos);

	set_local_entity_float_value (en, FLOAT_TYPE_DISTANCE, distance);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void fixed_wing_movement_avoid_enemy_fire (entity *en, vec3d *wp_pos)
{
#if 0
	entity
		*guide,
		*persuer,
		*aggressor;

	float
		d,
		velocity,
		guide_distance,
		aggressor_distance,
		evasion_distance;

	vec3d
		*xv,
		*yv,
		*pos,
		*aggressor_pos;

	ASSERT (en);

	ASSERT (wp_pos);

	if (!get_local_entity_int_value (en, INT_TYPE_AIRBORNE_AIRCRAFT))
	{
		return;
	}

	debug_filtered_log ("I am here!");


	guide = get_local_entity_parent (en, LIST_TYPE_FOLLOWER);

	ASSERT (guide);

	if (!get_local_entity_int_value (guide, INT_TYPE_EVADE_FIRE))
	{
		return;
	}

	//
	// see if something is shooting at the aircraft
	//

	persuer = get_local_entity_first_child (en, LIST_TYPE_TARGET);

	while (persuer)
	{
		if (get_local_entity_type (persuer) == ENTITY_TYPE_WEAPON)
		{
			break;
		}

		persuer = get_local_entity_child_succ (persuer, LIST_TYPE_TARGET);
	}

	if (!persuer)
	{
		return;
	}

	aggressor = get_local_entity_parent (persuer, LIST_TYPE_LAUNCHED_WEAPON);

	if (!aggressor)
	{
		return;
	}

	//
	// find distances
	//

	pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	aggressor_pos = get_local_entity_vec3d_ptr (aggressor, VEC3D_TYPE_POSITION);

	aggressor_distance = get_3d_range (pos, aggressor_pos);

	velocity = get_local_entity_float_value (en, FLOAT_TYPE_VELOCITY);

	ASSERT (velocity > 0.0);

	guide_distance = get_local_entity_float_value (en, FLOAT_TYPE_DISTANCE);

	d = frac (aggressor_distance / velocity) * 2.0 * PI;

	//
	// find evasion distance = (sin (d) * guide_distance * C) / velocity;
	//
	// if we make the maximum deflection, C, equal to half the aircraft's velocity, the divide cancels...
	//
	
	evasion_distance = (sin (d) * guide_distance * 0.5);
	
	xv = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_XV);

	wp_pos->x += (xv->x * evasion_distance);
	wp_pos->z += (xv->z * evasion_distance);

	//
	// vertical (barrel roll)
	//

	evasion_distance = (cos (d) * guide_distance * 0.5);
	
	yv = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_YV);

	wp_pos->y += (yv->y * evasion_distance);
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if NEW_FIXED_WING_FLIGHT_MODEL

void basic_fixed_wing_movement (entity *en)
{
	fixed_wing
		*raw;

	entity
		*guide;

	float
		terrain_elevation;

	vec3d
		dist,
		wp_pos,
		new_pos,
		*current_pos;

	raw = get_local_entity_data (en);

	//
	// abort if mobile is not moving (i.e. landed, or dead)
	//

	if (!get_local_entity_int_value (en, INT_TYPE_MOBILE_MOVING))
	{

		return;
	}

	//
	// abort if the mobile has no current guide (in which case it should never get past the first check ??)
	//

	guide = get_local_entity_parent (en, LIST_TYPE_FOLLOWER);

	if (!guide)
	{
		#if DEBUG
		
		debug_fatal ("FW_MOVE: Entity %s (%d) has no current guide", get_local_entity_string (en, STRING_TYPE_FULL_NAME), get_local_entity_index (en));

		#endif

		return;
	}

	//
	// GET CURRENT POSITION 
	//

	current_pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	terrain_elevation = get_3d_terrain_point_data_elevation (&raw->ac.terrain_info);

	//
	// GET WAYPOINT POSITION
	//

	fixed_wing_movement_get_waypoint_position (en, &wp_pos);

	//
	// avoid incoming fire
	//

	fixed_wing_movement_avoid_enemy_fire (en, &wp_pos);

	// taxi or fly depending upon airborne state

	if (!get_local_entity_int_value (en, INT_TYPE_AIRBORNE_AIRCRAFT))
	{
		fixed_wing_taxi (en, current_pos, &dist, &new_pos, terrain_elevation);
	}
	else
	{
		fixed_wing_flight (en, &new_pos);

		//
		// do motion vector calculation BEFORE bound, otherwise it may be zeroed
		//

		raw->ac.mob.motion_vector.x = (new_pos.x - current_pos->x) * get_one_over_delta_time ();
		raw->ac.mob.motion_vector.y = (new_pos.y - current_pos->y) * get_one_over_delta_time ();
		raw->ac.mob.motion_vector.z = (new_pos.z - current_pos->z) * get_one_over_delta_time ();

		//ASSERT (!check_zero_3d_vector (&raw->ac.mob.motion_vector));
	}

	bound_position_to_map_volume (&new_pos);

	if (raw->ac.operational_state == OPERATIONAL_STATE_NAVIGATING)
	{
		if (new_pos.y < (terrain_elevation + 100.0))
		{
			new_pos.y = terrain_elevation + 100.0;
		}
	}
	else
	{
		if (new_pos.y < terrain_elevation)
		{
			new_pos.y = terrain_elevation;
		}
	}

	set_local_entity_vec3d (en, VEC3D_TYPE_POSITION, &new_pos);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#else

void basic_fixed_wing_movement (entity *en)
{
	fixed_wing
		*raw;

	entity
		*guide;

	float
		wp_vel,
		sqr_range,
		terrain_elevation;

	vec3d
		dist,
		wp_vec,
		wp_pos,
		new_pos,
		*current_pos;

	raw = get_local_entity_data (en);

	//
	// abort if mobile is not moving (i.e. landed, or dead)
	//

	if (!get_local_entity_int_value (en, INT_TYPE_MOBILE_MOVING))
	{

		return;
	}

	//
	// abort if the mobile has no current guide (in which case it should never get past the first check ??)
	//

	guide = get_local_entity_parent (en, LIST_TYPE_FOLLOWER);

	if (!guide)
	{
		#if DEBUG
		
		debug_fatal ("FW_MOVE: Entity %s (%d) has no current guide", get_local_entity_string (en, STRING_TYPE_FULL_NAME), get_local_entity_index (en));

		#endif

		return;
	}

	//
	// GET CURRENT POSITION 
	//

	current_pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	terrain_elevation = get_3d_terrain_point_data_elevation (&raw->ac.terrain_info);

	//
	// GET WAYPOINT POSITION
	//

	fixed_wing_movement_get_waypoint_position (en, &wp_pos);

	//
	// avoid incoming fire
	//

	fixed_wing_movement_avoid_enemy_fire (en, &wp_pos);

	//
	// GET WAYPOINT VELOCITY
	//
	
	// temp
	wp_vel = get_local_entity_float_value (guide, FLOAT_TYPE_VELOCITY);

	if (wp_vel == 0.0)
	{
		wp_vel = get_local_entity_float_value (en, FLOAT_TYPE_CRUISE_VELOCITY);
	}

	//
	// GET VECTOR TO WAYPOINT
	//
	
	wp_vec.x = wp_pos.x - current_pos->x;
	wp_vec.y = wp_pos.y - (current_pos->y - get_local_entity_float_value (en, FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE));
	wp_vec.z = wp_pos.z - current_pos->z;
		
	sqr_range = (wp_vec.x * wp_vec.x) + (wp_vec.z * wp_vec.z);

	if (!get_local_entity_int_value (en, INT_TYPE_AIRBORNE_AIRCRAFT))
	{

		float
			delta_heading,
			current_heading,
			desired_heading,
			new_heading,
			new_pitch,
			new_roll,
			desired_velocity;

		new_roll = 0.0;

		//
		// aircraft on the ground
		//

		desired_velocity = wp_vel;

		raw->ac.mob.velocity += min ((desired_velocity - raw->ac.mob.velocity), GROUND_ACCELERATION) * get_entity_movement_delta_time ();

		// heading
		{
			current_heading = get_heading_from_attitude_matrix (raw->ac.mob.attitude);

			desired_heading = atan2 (wp_vec.x, wp_vec.z);

			delta_heading = desired_heading - current_heading;

			if (delta_heading <= -PI)
			{
		
				delta_heading += PI2;
			}
		
			if (delta_heading >= PI)
			{
		
				delta_heading -= PI2;
			}
			
			// calculate new attitude

			delta_heading = bound (delta_heading, rad (-30.0), rad (30.0));// taxiing turn rate

			new_heading = current_heading + (delta_heading * get_entity_movement_delta_time ());

			#if DEBUG_MODULE

			debug_log ("current heading %f, desired heading %f, delta_heading %f",
						current_heading, desired_heading, delta_heading);

			#endif
		}

		new_pitch = aircraft_database [raw->ac.mob.sub_type].fuselage_angle;

		get_3d_transformation_matrix (raw->ac.mob.attitude, new_heading, new_pitch, new_roll);
	
		dist.x = min (raw->ac.mob.velocity * raw->ac.mob.zv.x * get_entity_movement_delta_time (), fabs (wp_vec.x));
		dist.y = 0.0;
		dist.z = min (raw->ac.mob.velocity * raw->ac.mob.zv.z * get_entity_movement_delta_time (), fabs (wp_vec.z));

		#if DEBUG_MODULE

		debug_log ("current heading %d, desired heading %d, delta_heading %f, dist %f, %f, %f, sqr_range %f, vel %f",
						current_heading, desired_heading, delta_heading, dist.x, dist.y, dist.z, sqr_range, raw->ac.mob.velocity);

		#endif
	
		new_pos.x = current_pos->x + dist.x;
		new_pos.y = current_pos->y + dist.y;
		new_pos.z = current_pos->z + dist.z;
	
		bound_position_to_map_volume (&new_pos);
	
		new_pos.y = terrain_elevation + get_local_entity_float_value (en, FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE);
	}
	else
	{
		vec3d
			rel_pos,
			normalised_wp_vec;

		float
			max_turn_radius,
			required_heading,
			required_pitch,
			required_roll,
			delta_heading,
			delta_pitch,
			heading,
			pitch,
			roll,
			max_turn_rate;

		matrix3x3
			m,
			inv;

		//
		// in the air
		//

		raw->ac.mob.velocity += min ((wp_vel - raw->ac.mob.velocity), AIR_ACCELERATION) * get_entity_movement_delta_time ();

		#if USE_VELOCITY_MATCHING
			fixed_wing_match_velocity(en);
		#endif
		
		normalised_wp_vec = wp_vec;

		normalise_any_3d_vector (&normalised_wp_vec);
		
		get_heading_and_pitch_from_3d_unit_vector (&normalised_wp_vec, &required_heading, &required_pitch);

		heading = get_heading_from_attitude_matrix (raw->ac.mob.attitude);

		pitch = get_pitch_from_attitude_matrix (raw->ac.mob.attitude);

		roll = get_roll_from_attitude_matrix (raw->ac.mob.attitude);
	
		// heading

		if (raw->ac.mob.velocity)
		{

			max_turn_rate = aircraft_database [raw->ac.mob.sub_type].g_max / raw->ac.mob.velocity;

			ASSERT (max_turn_rate < aircraft_database [raw->ac.mob.sub_type].g_max);
		}
		else
		{

			max_turn_rate = aircraft_database [raw->ac.mob.sub_type].g_max;
		}

		delta_heading = (required_heading - heading);

		if (delta_heading <= -PI)
		{
	
			delta_heading += PI2;
		}
	
		if (delta_heading >= PI)
		{
	
			delta_heading -= PI2;
		}

		//
		// can aircraft reach waypoint
		//
	
		max_turn_radius = (raw->ac.mob.velocity * raw->ac.mob.velocity) / aircraft_database [raw->ac.mob.sub_type].g_max;

		memcpy (m, get_local_entity_attitude_matrix_ptr (en), sizeof (matrix3x3));

		get_inverse_matrix (inv, m);

		multiply_matrix3x3_vec3d (&rel_pos, inv, &wp_vec);

		delta_heading = bound (delta_heading, -max_turn_rate, max_turn_rate);

		#if DEBUG_MODULE

		draw_aircraft_turn_radius (en);

		#endif

		//
		// update position
		//

		dist.x = raw->ac.mob.velocity * raw->ac.mob.zv.x * get_entity_movement_delta_time ();
		dist.y = raw->ac.mob.velocity * raw->ac.mob.zv.y * get_entity_movement_delta_time ();
		dist.z = raw->ac.mob.velocity * raw->ac.mob.zv.z * get_entity_movement_delta_time ();

		new_pos.x = current_pos->x + dist.x;
		new_pos.y = current_pos->y + dist.y;
		new_pos.z = current_pos->z + dist.z;

		//
		// attitude
		//

		heading += delta_heading * get_entity_movement_delta_time ();

		// pitch

		delta_pitch = (required_pitch - pitch);

		delta_pitch = bound (delta_pitch, PITCH_MIN, PITCH_MAX);

		pitch += delta_pitch * get_entity_movement_delta_time ();

		// roll

		required_roll = (delta_heading / max_turn_rate) * rad (70);

		roll += (required_roll - roll) * get_entity_movement_delta_time ();

		get_3d_transformation_matrix (raw->ac.mob.attitude, heading, pitch, roll);
	}

	//
	// do motion vector calculation BEFORE bound, otherwise it may be zeroed
	//

	raw->ac.mob.motion_vector.x = (new_pos.x - current_pos->x) * get_one_over_delta_time ();
	raw->ac.mob.motion_vector.y = (new_pos.y - current_pos->y) * get_one_over_delta_time ();
	raw->ac.mob.motion_vector.z = (new_pos.z - current_pos->z) * get_one_over_delta_time ();

	bound_position_to_map_volume (&new_pos);

	if (raw->ac.operational_state == OPERATIONAL_STATE_NAVIGATING)
	{
		if (new_pos.y < (terrain_elevation + 100.0))
		{
			new_pos.y = terrain_elevation + 100.0;
		}
	}
	else
	{
		if (new_pos.y < terrain_elevation)
		{
			new_pos.y = terrain_elevation;
		}
	}

	set_local_entity_vec3d (en, VEC3D_TYPE_POSITION, &new_pos);
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define RIVER_DEPTH 3.0

void basic_fixed_wing_death_movement (entity *en)
{

	fixed_wing
		*raw;

	float
		speed,
		altitude,
		terrain_elevation,
		old_terrain_elevation;

	vec3d
		*pos,
		*velocity,
		direction_vector,
		new_pos;

	terrain_classes
		terrain_class;

	raw = get_local_entity_data (en);

	//
	// get current position, speed, and velocity
	//

	velocity = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_MOTION_VECTOR);

	speed = get_3d_vector_magnitude (velocity);

	pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	//
	// check terrain elevation is valid
	//

	if (raw->ac.terrain_info.terrain_face == NULL)
	{
		get_3d_terrain_point_data (pos->x, pos->z, &raw->ac.terrain_info);
	}

	//
	// ground test
	//

	old_terrain_elevation = get_3d_terrain_point_data_elevation (&raw->ac.terrain_info);

	altitude = pos->y - (old_terrain_elevation + get_local_entity_float_value (en, FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE));

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

			//
			// stop any engine noise
			//

			kill_client_server_entity_sound_type (en, ENTITY_SUB_TYPE_EFFECT_SOUND_ENGINE_LOOPING2);

			kill_client_server_entity_sound_type (en, ENTITY_SUB_TYPE_EFFECT_SOUND_ENGINE_LOOPING1);
		}

		//
		// stop any black smoke TRAILS generating ( marked as type VEHICLE_DAMAGE )
		//

		if (speed < FIXED_WING_DAMAGE_TRAIL_CUT_OFF_SPEED)
		{
			clear_smoke_list_generator_lifetime (en, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_LIGHT_DAMAGE);
			clear_smoke_list_generator_lifetime (en, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_MEDIUM_DAMAGE);
			clear_smoke_list_generator_lifetime (en, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_HEAVY_DAMAGE);
		}

		//
		// if aircraft is already on the ground, but not on water, call different movement function
		//

		if (get_terrain_type_class (get_3d_terrain_point_data_type (&raw->ac.terrain_info)) == TERRAIN_CLASS_LAND)
		{
			fixed_wing_crash_movement (en);

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
			// stop any black smoke TRAILS generating ( marked as type VEHICLE_DAMAGE )
			//

			clear_smoke_list_generator_lifetime (en, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_LIGHT_DAMAGE);
			clear_smoke_list_generator_lifetime (en, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_MEDIUM_DAMAGE);
			clear_smoke_list_generator_lifetime (en, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_HEAVY_DAMAGE);

			//
			// also if it lands in water kill any fires that may be burning
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
	
						clear_fixed_wing_velocity (en);

	//					delete_local_entity_from_parents_child_list (en, LIST_TYPE_VIEW);
		
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
	
						clear_fixed_wing_velocity (en);

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
					// stop any black smoke TRAILS generating ( marked as type VEHICLE_DAMAGE )
					//
		
					clear_smoke_list_generator_lifetime (en, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_LIGHT_DAMAGE);
					clear_smoke_list_generator_lifetime (en, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_MEDIUM_DAMAGE);
					clear_smoke_list_generator_lifetime (en, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_HEAVY_DAMAGE);

					//
					// aircraft is no longer visible
					//
	
					clear_fixed_wing_velocity (en);

//					delete_local_entity_from_parents_child_list (en, LIST_TYPE_VIEW);
		
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

				sound_sample_index = SOUND_SAMPLE_INDEX_AIRCRAFT_CRASH;

				create_client_server_sound_effect_entity
				(
					en,
					ENTITY_SIDE_NEUTRAL,
					ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,
					SOUND_CHANNEL_SOUND_EFFECT,
					SOUND_LOCALITY_ALL,
					NULL,												// position
					1.0,												// amplification
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
		
	if ((velocity->x != 0.0) || (velocity->z != 0.0))
	{
		float		
			heading,
			pitch,
			roll,
			required_heading,
			required_pitch,
			dh,
			dp;

		heading = get_heading_from_attitude_matrix (raw->ac.mob.attitude);
		pitch = get_pitch_from_attitude_matrix (raw->ac.mob.attitude);
		roll = get_roll_from_attitude_matrix (raw->ac.mob.attitude);

		memcpy (&direction_vector, velocity, sizeof (vec3d));
		
		normalise_3d_vector_given_magnitude (&direction_vector, speed);
		
		get_heading_and_pitch_from_3d_unit_vector (&direction_vector, &required_heading, &required_pitch);
		
		dh = bound (required_heading - heading, -(PI * 0.25), (PI *0.25));

		heading += (dh * get_entity_movement_delta_time());

		if (altitude > 12.0)
		{
			//
			// stop planes rolling on the floor
			//

			roll += (PI * 0.5 * get_entity_movement_delta_time());

			dp = bound (required_pitch - pitch, -(PI * 0.25), (PI *0.25));

			pitch += (dp * get_entity_movement_delta_time());
		}
	
		get_3d_transformation_matrix (raw->ac.mob.attitude, heading, pitch, roll);
	}

	//
	// set new position
	//

	set_local_entity_vec3d (en, VEC3D_TYPE_POSITION, &new_pos);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void fixed_wing_crash_movement (entity *en)
{

	fixed_wing
		*raw;

	float
		heading,
		pitch,
		roll,
		required_angle,
		max_angle,
		delta_pitch,
		delta_roll,
		speed,
		horizontal_speed,
		terrain_elevation;

	vec3d
		*pos,
		*velocity,
		new_pos,
		*face_normal;

	matrix3x3
		m;

	raw = get_local_entity_data (en);

	pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	velocity = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_MOTION_VECTOR);

	speed = get_3d_vector_magnitude (velocity);

	//
	// work out new position 
	//

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
	// update attitude
	//
		
	heading = get_heading_from_attitude_matrix (raw->ac.mob.attitude);

	pitch = get_pitch_from_attitude_matrix (raw->ac.mob.attitude);

	roll = get_roll_from_attitude_matrix (raw->ac.mob.attitude);
	
	face_normal = get_3d_terrain_point_data_normal (&raw->ac.terrain_info);

	get_3d_transformation_matrix_from_face_normal_and_heading (m, face_normal, heading);

	//
	// update velocity
	//

	horizontal_speed = sqrt ((velocity->x * velocity->x) + (velocity->z * velocity->z));

	if (speed > 0.0)
	{
		normalise_3d_vector_given_magnitude (velocity, speed);

		horizontal_speed -= (horizontal_speed * get_entity_movement_delta_time());

		velocity->x *= horizontal_speed;
		velocity->y = 0.0;
		velocity->z *= horizontal_speed;
	}
	else
	{
		velocity->x = 0.0;
		velocity->y = 0.0;
		velocity->z = 0.0;
	}

	if (face_normal->y < 0.3)
	{
		velocity->x += (G * face_normal->x * get_entity_movement_delta_time());
		velocity->z += (G * face_normal->z * get_entity_movement_delta_time());
	}

	speed = get_3d_vector_magnitude (velocity);

	if (speed < 1.0)
	{
		clear_fixed_wing_velocity (en);
	}
	else
	{
		set_local_entity_float_value (en, FLOAT_TYPE_VELOCITY, speed);
	}

	//
	// pitch
	//

	required_angle = get_pitch_from_attitude_matrix (m) + aircraft_database [raw->ac.mob.sub_type].destroyed_pitch_offset;

	max_angle = PI * get_entity_movement_delta_time ();

	delta_pitch = bound (required_angle - pitch, -max_angle, max_angle);
	
	pitch += delta_pitch;

	//
	// roll
	//

	required_angle = get_roll_from_attitude_matrix (m) + aircraft_database [raw->ac.mob.sub_type].destroyed_bank_offset;

	max_angle = PI * 0.75 * get_entity_movement_delta_time ();

	delta_roll = bound (required_angle - roll, -max_angle, max_angle);
	
	roll += delta_roll;

	//

	get_3d_transformation_matrix (raw->ac.mob.attitude, heading, pitch, roll);

	//
	// set new position
	//

	set_local_entity_vec3d (en, VEC3D_TYPE_POSITION, &new_pos);

	//
	// if aircraft has come to a stop, remove from update list
	//

	if ((speed == 0.0) && (delta_pitch <= 0.01) && (delta_roll <= 0.01) && (!raw->ac.mob.alive))
	{
		set_local_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_DEAD);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void fixed_wing_impact_movement (entity *en)
{

	fixed_wing
		*raw;

	float
		speed;

	vec3d
		*velocity;

	int
		seed;

	raw = get_local_entity_data (en);

	seed = get_client_server_entity_random_number_seed(en);

	speed = 4.0 + (3.0 * frand1x (&seed));

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

void clear_fixed_wing_velocity (entity *en)
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

void draw_aircraft_turn_radius (entity *en)
{
#if 0
	float
		heading,
		max_turn_radius,
		wp_radius;

	vec3d
		test_point,
		*wp_pos;

	aircraft
		*raw;

	raw = get_local_entity_data (en);

	heading = get_heading_from_attitude_matrix (raw->mob.attitude);
		
	wp_pos = get_local_entity_vec3d_ptr (raw->waypoint_root.first_child, VEC3D_TYPE_POSITION);

	create_vectored_debug_3d_object (wp_pos, (vec3d *) raw->mob.attitude [1], OBJECT_3D_RED_ARROW, 0, 2.0);
	
	max_turn_radius = (raw->mob.velocity * raw->mob.velocity) / aircraft_database [raw->mob.sub_type].g_max;
	
	wp_radius = get_local_entity_float_value (raw->waypoint_root.first_child, FLOAT_TYPE_RADIUS);

	// draw RHS
	
	test_point = raw->mob.position;
	
	test_point.x += (max_turn_radius + wp_radius) * cos (heading);
	test_point.z -= (max_turn_radius + wp_radius) * sin (heading);

	draw_debug_circle_line (&test_point, max_turn_radius);

	// draw LHS
	
	test_point = raw->mob.position;
	
	test_point.x -= (max_turn_radius + wp_radius) * cos (heading);
	test_point.z += (max_turn_radius + wp_radius) * sin (heading);

	draw_debug_circle_line (&test_point, max_turn_radius);
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_debug_circle_line (vec3d *centre, float radius)
{

	vec3d
		old_pos,
		new_pos;

	int
		loop,
		inc;

	inc = 10;

	old_pos = *centre;

	old_pos.z += radius;

	for (loop = 0; loop < 360; loop += inc)
	{

		new_pos.x = centre->x + (radius * sin (rad (loop)));
		new_pos.y = centre->y;
		new_pos.z = centre->z + (radius * cos (rad (loop)));

		create_debug_3d_line (&old_pos, &new_pos, sys_col_yellow, 0);

		old_pos = new_pos;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_debug_takeoff_landing_routes (entity *en)
{

	entity
		*landing,
		*group,
		*keysite,
		*wp;

	vec3d
		wp_pos,
		offset;

	fixed_wing
		*raw;

	raw = get_local_entity_data (en);
	
	group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

	keysite = get_local_entity_parent (group, LIST_TYPE_KEYSITE_GROUP);

	landing = get_local_entity_landing_entity (keysite, ENTITY_SUB_TYPE_LANDING_FIXED_WING);

	wp = get_local_landing_entity_route (landing, ENTITY_SUB_TYPE_TASK_TAKEOFF);

	while (wp)
	{

		get_local_entity_vec3d (wp, VEC3D_TYPE_POSITION, &wp_pos);

		get_local_entity_formation_position_offset (en, wp, &offset);

		wp_pos.x += offset.x;
		wp_pos.y += offset.y;
		wp_pos.z += offset.z;

		create_vectored_debug_3d_object (&wp_pos, (vec3d *) raw->ac.mob.attitude [1], OBJECT_3D_RED_ARROW, 0, 2.0);

		wp = get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT);
	}

	wp = get_local_landing_entity_route (landing, ENTITY_SUB_TYPE_TASK_LANDING);

	while (wp)
	{

		get_local_entity_vec3d (wp, VEC3D_TYPE_POSITION, &wp_pos);

		get_local_entity_formation_position_offset (en, wp, &offset);

		wp_pos.x += offset.x;
		wp_pos.y += offset.y;
		wp_pos.z += offset.z;

		create_vectored_debug_3d_object (&wp_pos, (vec3d *) raw->ac.mob.attitude [1], OBJECT_3D_RED_ARROW, 0, 2.0);

		wp = get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
