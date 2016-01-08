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

#include "ai/ai_misc/ai_route.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// 3 levels of debug
//

#define DEBUG_JUMP_TO_WAYPOINT						0

#define DEBUG_MODULE 									0

#define SUB_ROUTE_WAYPOINT_RESYNC_FREQUENCY		0x01

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void routed_vehicle_falling_movement (entity *en);

static void routed_vehicle_movement_get_waypoint_position (entity *en, vec3d *wp_pos);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void routed_vehicle_movement (entity *en)
{

	routed_vehicle
      *raw;

   entity
      *wp,
		*group,
		*guide;

   vec3d
      *face_normal,
      wp_vec,
      wp_pos,
      new_pos;

   float
		distance,
		roll,
		pitch,
		heading;

    raw = (routed_vehicle *) get_local_entity_data (en);

	guide = get_local_entity_parent (en, LIST_TYPE_FOLLOWER);

	if (!guide)
	{

		if (raw->vh.mob.velocity != 0.0)
		{

			set_local_entity_float_value (en, FLOAT_TYPE_VELOCITY, 0.0);
		}

		group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

		if (group)
		{

			switch (get_local_entity_int_value (group, INT_TYPE_GROUP_LIST_TYPE))
			{

				case LIST_TYPE_KEYSITE_GROUP:
				{

					if (get_local_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE) != OPERATIONAL_STATE_LANDED)
					{

						debug_log ("RV_MOVE: RV %s (%d) at keysite in incorrect state, setting to LANDED", get_local_entity_string (en, STRING_TYPE_FULL_NAME), get_local_entity_index (en));

						set_local_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_LANDED);
					}

					break;
				}

				case LIST_TYPE_INDEPENDENT_GROUP:
				{

					if (get_local_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE) != OPERATIONAL_STATE_STOPPED)
					{

						debug_log ("RV_MOVE: RV %s (%d) at road node in incorrect state (%d), setting to STOPPED", get_local_entity_string (en, STRING_TYPE_FULL_NAME), get_local_entity_index (en), get_local_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE));

						set_local_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_STOPPED);
					}

					break;
				}

				default:
				{

					debug_fatal ("RV_MOVE: RV %s (%d) not on keysite or independent list", get_local_entity_string (en, STRING_TYPE_FULL_NAME), get_local_entity_index (en));
				}
			}
		}

		return;
	}

	wp = get_local_entity_parent (guide, LIST_TYPE_CURRENT_WAYPOINT);

	if ((!wp) || (!(get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT) || (get_local_entity_child_pred (wp, LIST_TYPE_WAYPOINT)))))
	{

		if (raw->vh.mob.velocity != 0.0)
		{

			if (get_comms_model () == COMMS_MODEL_SERVER)
			{

				set_client_server_entity_float_value (en, FLOAT_TYPE_VELOCITY, 0.0);
			}
			else
			{

				//set_local_entity_float_value (en, FLOAT_TYPE_VELOCITY, 0.0);
			}
		}

		raw->vh.mob.motion_vector.x = raw->vh.mob.attitude [2][0] * raw->vh.mob.velocity;
		raw->vh.mob.motion_vector.y = raw->vh.mob.attitude [2][1] * raw->vh.mob.velocity;
		raw->vh.mob.motion_vector.z = raw->vh.mob.attitude [2][2] * raw->vh.mob.velocity;

		return;
	}

   ////////////////////////////////////////
	//
	// not correct state to move (or group is engaging targets)
	//
   ////////////////////////////////////////

	group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

	if (((!get_local_entity_int_value (en, INT_TYPE_MOBILE_MOVING)) && (raw->vh.operational_state != OPERATIONAL_STATE_WAITING)) ||
		(check_group_task_type_valid_members (group, ENTITY_SUB_TYPE_TASK_ENGAGE)))
	{

		if (raw->vh.mob.velocity != 0.0)
		{

			if (get_comms_model () == COMMS_MODEL_SERVER)
			{

				set_client_server_entity_float_value (en, FLOAT_TYPE_VELOCITY, 0.0);
			}
			else
			{

				//set_local_entity_float_value (en, FLOAT_TYPE_VELOCITY, 0.0);
			}
		}

		if (raw->desired_velocity != 0.0)
		{

			set_local_entity_float_value (en, FLOAT_TYPE_DESIRED_VELOCITY, 0.0);
		}

		raw->vh.mob.motion_vector.x = raw->vh.mob.attitude [2][0] * raw->vh.mob.velocity;
		raw->vh.mob.motion_vector.y = raw->vh.mob.attitude [2][1] * raw->vh.mob.velocity;
		raw->vh.mob.motion_vector.z = raw->vh.mob.attitude [2][2] * raw->vh.mob.velocity;

		return;
	}

   ////////////////////////////////////////
   //
   // current waypoint vector
   //
   ////////////////////////////////////////

	routed_vehicle_movement_get_waypoint_position (en, &wp_pos);

	// find better place for this...
	if (raw->vh.sleep > 0.0)
	{

		return;
	}
	//

   wp_vec.x = wp_pos.x - raw->vh.mob.position.x;
   wp_vec.y = wp_pos.y - raw->vh.mob.position.y;
   wp_vec.z = wp_pos.z - raw->vh.mob.position.z;

   ////////////////////////////////////////
   //
	// Movement
   //
   ////////////////////////////////////////

	new_pos.x = raw->vh.mob.position.x;
	new_pos.y = raw->vh.mob.position.y;
	new_pos.z = raw->vh.mob.position.z;

	// not on top of waypoint (sqr check within 0.1m)
	if (((wp_vec.x * wp_vec.x) + (wp_vec.z * wp_vec.z)) > 1.0)
	{

		float
			old_heading = 0,
			old_roll = 0,
			old_pitch = 0,
			movement_distance,
			delta_velocity,
			max_accel;

		////////////////////////////////////////
		//
		// velocity
		//
		////////////////////////////////////////

		max_accel = get_local_entity_float_value (en, FLOAT_TYPE_MAX_ACCELERATION);

		raw->desired_velocity = get_local_entity_float_value (guide, FLOAT_TYPE_VELOCITY);

		delta_velocity = (raw->desired_velocity - raw->vh.mob.velocity);

		delta_velocity = bound (delta_velocity, -(10.0 * max_accel), max_accel);

		raw->vh.mob.velocity += delta_velocity * get_entity_movement_delta_time ();

		////////////////////////////////////////
		//
		// Calculate attitude angles
		//
		////////////////////////////////////////

		//
		// Heading
		//

		heading = atan2 (wp_vec.x, wp_vec.z);

		//
		// Roll
		//

		roll = 0;

		distance = normalise_any_3d_vector (&wp_vec);

		////////////////////////////////////////
		//
		// attitude
		//
		////////////////////////////////////////

		if (raw->vh.mob.tacview_logging)
		{
			old_roll = get_roll_from_attitude_matrix(raw->vh.mob.attitude);
			old_pitch = get_pitch_from_attitude_matrix(raw->vh.mob.attitude);
			old_heading = get_heading_from_attitude_matrix(raw->vh.mob.attitude);
		}

		if (get_local_entity_int_value (guide, INT_TYPE_TERRAIN_FOLLOW_MODE) != GUIDE_TERRAIN_FOLLOW_NONE)
		{

			//
			// Get roll for terrain
			//

			ASSERT(point_inside_map_area(&new_pos));

			get_3d_terrain_point_data (new_pos.x, new_pos.z, &raw->vh.terrain_info);

			new_pos.y = get_3d_terrain_point_data_elevation (&raw->vh.terrain_info);

			if (get_terrain_type_class (get_3d_terrain_point_data_type (&raw->vh.terrain_info)) == TERRAIN_CLASS_FOREST)
			{
				new_pos.y -= 20.0;
			}

			face_normal = get_3d_terrain_point_data_normal (&raw->vh.terrain_info);

			get_3d_transformation_matrix_from_face_normal_and_heading (raw->vh.mob.attitude, face_normal, heading);
		}
		else
		{

			pitch = asin (wp_vec.y);

			get_3d_transformation_heading_pitch_matrix (raw->vh.mob.attitude, heading, pitch);
		}

		////////////////////////////////////////
		//
		// Set Position
		//
		////////////////////////////////////////

		if (raw->vh.mob.tacview_logging)
		{
			if (fabs(get_roll_from_attitude_matrix(raw->vh.mob.attitude) - old_roll) > rad(0.001)
				|| fabs(get_pitch_from_attitude_matrix(raw->vh.mob.attitude) - old_pitch) > rad(0.001)
				|| fabs(heading - old_heading) > rad(0.001))
			{
				set_local_entity_int_value(en, INT_TYPE_ROTATED, TRUE);
			}
		}

		movement_distance = min (distance, raw->vh.mob.velocity * get_entity_movement_delta_time ());

		//new_pos.x += raw->vh.mob.attitude [2][0] * movement_distance;
		//new_pos.y += raw->vh.mob.attitude [2][1] * movement_distance;
		//new_pos.z += raw->vh.mob.attitude [2][2] * movement_distance;
		new_pos.x += wp_vec.x * movement_distance;
		new_pos.y += wp_vec.y * movement_distance;
		new_pos.z += wp_vec.z * movement_distance;
	}

	//
	// Set vehicle positon
	//

	bound_position_to_map_volume (&new_pos);

	set_local_entity_vec3d (en, VEC3D_TYPE_POSITION, &new_pos);

	//
	// Calculate motion vector for view system
	//

	raw->vh.mob.motion_vector.x = raw->vh.mob.attitude [2][0] * raw->vh.mob.velocity;
	raw->vh.mob.motion_vector.y = raw->vh.mob.attitude [2][1] * raw->vh.mob.velocity;
	raw->vh.mob.motion_vector.z = raw->vh.mob.attitude [2][2] * raw->vh.mob.velocity;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void routed_vehicle_death_movement (entity *en)
{

	routed_vehicle
		*raw;

	float
		heading,
		pitch,
		roll,
		speed,
		terrain_elevation;

	vec3d
		*pos,
		*velocity,
		new_pos;

	raw = (routed_vehicle *) get_local_entity_data (en);

	//
	// first check to see if vehicle is on the ground or not
	//

	pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	terrain_elevation = get_3d_terrain_point_data_elevation (&raw->vh.terrain_info);

	if ((get_terrain_type_class (get_3d_terrain_point_data_type (&raw->vh.terrain_info)) == TERRAIN_CLASS_WATER) ||
			(pos->y > (terrain_elevation + get_local_entity_float_value (en, FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE) + 0.2)))
	{

		routed_vehicle_falling_movement (en);

		return;
	}

	//
	// if vehicle has come to a stop, remove from update list
	//

	velocity = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_MOTION_VECTOR);

	speed = get_3d_vector_magnitude (velocity);

	if (speed == 0.0)
	{
		if (get_local_entity_int_value (en, INT_TYPE_DAMAGE_LEVEL) <= 0)
			set_local_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_DEAD);

		return;
	}

	//
	// work out new position
	//

	new_pos.x = pos->x + (velocity->x * get_entity_movement_delta_time());
	new_pos.z = pos->z + (velocity->z * get_entity_movement_delta_time());

	ASSERT(point_inside_map_area(&new_pos));

	get_3d_terrain_point_data (new_pos.x, new_pos.z, &raw->vh.terrain_info);

	terrain_elevation = get_3d_terrain_point_data_elevation (&raw->vh.terrain_info);

	new_pos.y = terrain_elevation + get_local_entity_float_value (en, FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE);

	//
	// update velocity
	//

	normalise_3d_vector_given_magnitude (velocity, speed);

	speed -= (4.0f * get_entity_movement_delta_time());

	speed = max (0.0f, speed);

	set_local_entity_float_value (en, FLOAT_TYPE_VELOCITY, speed);

	velocity->x *= speed;
	velocity->y *= speed;
	velocity->z *= speed;

	//
	// update attitude
	//

	heading = get_heading_from_attitude_matrix (raw->vh.mob.attitude);

	pitch = get_pitch_from_attitude_matrix (raw->vh.mob.attitude);

	roll = get_roll_from_attitude_matrix (raw->vh.mob.attitude);

	heading -= (PI * 0.1 * get_entity_movement_delta_time());

	get_3d_transformation_matrix (raw->vh.mob.attitude, heading, pitch, roll);

	//
	// set new position
	//

	set_local_entity_vec3d (en, VEC3D_TYPE_POSITION, &new_pos);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void routed_vehicle_falling_movement (entity *en)
{

	routed_vehicle
		*raw;

	float
		speed,
		altitude,
		terrain_elevation,
		old_terrain_elevation;

	vec3d
		*pos,
		*velocity,
		new_pos;

	raw = (routed_vehicle *) get_local_entity_data (en);

	//
	// get current position and velocity
	//

	pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	old_terrain_elevation = get_3d_terrain_point_data_elevation (&raw->vh.terrain_info);

	velocity = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_MOTION_VECTOR);

	new_pos.x = pos->x + (velocity->x * get_entity_movement_delta_time());
	new_pos.y = pos->y + (velocity->y * get_entity_movement_delta_time());
	new_pos.z = pos->z + (velocity->z * get_entity_movement_delta_time());

	ASSERT(point_inside_map_area(&new_pos));

	get_3d_terrain_point_data (new_pos.x, new_pos.z, &raw->vh.terrain_info);

	//
	// update velocity
	//

	velocity->y -= (G * get_entity_movement_delta_time());

	//
	// check if vehicle has hit the floor
	//

	terrain_elevation = get_3d_terrain_point_data_elevation (&raw->vh.terrain_info);

	altitude = new_pos.y - (terrain_elevation + get_local_entity_float_value (en, FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE));

	if (altitude <= 0.0)
	{
		//
		// no lateral movement below ground
		//

		new_pos.x = pos->x;
		new_pos.z = pos->z;

		if (get_terrain_type_class (get_3d_terrain_point_data_type (&raw->vh.terrain_info)) == TERRAIN_CLASS_WATER)
		{
			//////////////////////////////////////////
			//
			// VEHICLE IS BELOW GROUND AND IN WATER
			//
			//////////////////////////////////////////

			if (pos->y > old_terrain_elevation)
			{
				//
				// vehicle has hit the water this frame - create a "splash"
				//

				if (get_comms_model() == COMMS_MODEL_SERVER)
				{
					vec3d
						temp_pos;

					temp_pos.x = new_pos.x;
					temp_pos.y = terrain_elevation;
					temp_pos.z = new_pos.z;

					set_local_entity_vec3d (en, VEC3D_TYPE_POSITION, &temp_pos);

					create_client_server_collision_effect (&temp_pos, DYNAMICS_COLLISION_SURFACE_WATER, 1);
				}

				//
				// also kill any fires that may be burning
				//

				clear_smoke_list_generator_lifetime (en, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_FIRE);
			}

			{
				//
				// make vehicle sink until it is no longer visible
				//

				struct OBJECT_3D_BOUNDS
					*bounding_box;

				vec3d
					d;

				bounding_box = get_object_3d_bounding_box (get_local_entity_int_value (en, INT_TYPE_OBJECT_3D_SHAPE));

				d.x = bounding_box->xmax - bounding_box->xmin;
				d.y = bounding_box->ymax - bounding_box->ymin;
				d.z = bounding_box->zmax - bounding_box->zmin;

				if (altitude < -get_3d_vector_magnitude (&d))
				{
					//
					// vehicle is no longer visible
					//

					velocity->x = 0.0;
					velocity->y = 0.0;
					velocity->z = 0.0;

//					delete_local_entity_from_parents_child_list (en, LIST_TYPE_VIEW);

					set_local_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_DEAD);
				}
			}
		}
		else
		{
			//////////////////////////////////////////
			//
			// VEHICLE HAS HIT SOLID GROUND
			//
			//////////////////////////////////////////

			new_pos.y = terrain_elevation + get_local_entity_float_value (en, FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE);

			if (get_comms_model() == COMMS_MODEL_SERVER)
			{
				vec3d
					temp_pos;

				temp_pos.x = new_pos.x;
				temp_pos.y = terrain_elevation;
				temp_pos.z = new_pos.z;

				set_local_entity_vec3d (en, VEC3D_TYPE_POSITION, &temp_pos);

				create_client_server_collision_effect (&temp_pos, DYNAMICS_COLLISION_SURFACE_GROUND, 2);
			}

			velocity->y = 0.0;
		}
	}

	//
	// update speed
	//

	speed = get_3d_vector_magnitude (velocity);

	set_local_entity_float_value (en, FLOAT_TYPE_VELOCITY, speed);

	//
	// set new position
	//

	set_local_entity_vec3d (en, VEC3D_TYPE_POSITION, &new_pos);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void routed_vehicle_impact_movement (entity *en)
{

	routed_vehicle
		*raw;

	float
		speed;

	vec3d
		*velocity;

	int
		seed;

	//
	// when a routed vehicle is killed it needs to be "moved out the way", so give it an instantaneous sideways velocity
	//

	raw = (routed_vehicle *) get_local_entity_data (en);

	seed = get_client_server_entity_random_number_seed(en);

	speed = 4.0 * frand1x (&seed);

	velocity = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_MOTION_VECTOR);

	velocity->x += (speed * raw->vh.mob.xv.x);

	velocity->z += (speed * raw->vh.mob.xv.z);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void routed_vehicle_movement_get_waypoint_position (entity *en, vec3d *wp_pos)
{

	entity
		*wp,
		*guide;

	float
		distance;

	vec3d
		offset,
		temp_pos,
		*pos;

	routed_vehicle
		*raw;

	ASSERT (en);

	ASSERT (wp_pos);

	guide = get_local_entity_parent (en, LIST_TYPE_FOLLOWER);

	ASSERT (guide);

	wp = get_local_entity_parent (guide, LIST_TYPE_CURRENT_WAYPOINT);

	ASSERT (wp);

	//
	// Should vehicle follow waypoint or sub_route ?
	//

	if (get_local_entity_int_value (wp, INT_TYPE_MOBILE_FOLLOW_WAYPOINT_OFFSET))
	{

		get_local_entity_vec3d (guide, VEC3D_TYPE_GUIDE_POSITION, wp_pos);

		get_local_entity_formation_position_offset (en, wp, &offset);

		wp_pos->x += offset.x;
		wp_pos->y += offset.y;
		wp_pos->z += offset.z;
	}
	else
	{

		//
		// following sub_route
		//

		raw = (routed_vehicle *) get_local_entity_data (en);

		if ((raw->sub_route) && (raw->sub_waypoint_count > 0))
		{

			float
				sqr_range;

			if (raw->waypoint_next_index > raw->waypoint_this_index)
			{

				*wp_pos = raw->sub_route->link_positions [raw->sub_route->number_of_links - raw->sub_waypoint_count];
			}
			else
			{

				*wp_pos = raw->sub_route->link_positions [raw->sub_waypoint_count - 1];
			}

			sqr_range = ((wp_pos->x - raw->vh.mob.position.x) * (wp_pos->x - raw->vh.mob.position.x)) +
							((wp_pos->z - raw->vh.mob.position.z) * (wp_pos->z - raw->vh.mob.position.z));

			#if DEBUG_MODULE

			if (get_external_view_entity () == en)
			{

				debug_log ("RV_MOVE: %s, %d at [%f, %f, %f] following sub_route %d, at [%f, %f, %f] sqr_range %f",
								get_local_entity_string (en, STRING_TYPE_FULL_NAME),
								get_local_entity_index (en),
								raw->vh.mob.position.x,
								raw->vh.mob.position.y,
								raw->vh.mob.position.z,
								raw->waypoint_next_index,
								wp_pos->x, wp_pos->y, wp_pos->z,
								sqr_range);
			}

			#endif

			if (sqr_range < 6.0)
			{

				raw->sub_waypoint_count --;

				#if DEBUG_MODULE

				if (get_external_view_entity () == en)
				{

					debug_log ("RV_MOVE: reached sub_route waypoint");
				}

				#endif

				if ((get_comms_model () == COMMS_MODEL_SERVER) && (raw->sub_waypoint_count & SUB_ROUTE_WAYPOINT_RESYNC_FREQUENCY))
				{

					transmit_entity_comms_message (ENTITY_COMMS_UPDATE, en);

					#if DEBUG_MODULE

					debug_log ("RV_MOVE: client server update position for en %s %d", get_local_entity_string (en, STRING_TYPE_FULL_NAME), get_local_entity_index (en));

					#endif
				}

				if (raw->sub_waypoint_count > 0)
				{

					if (raw->waypoint_next_index > raw->waypoint_this_index)
					{

						*wp_pos = raw->sub_route->link_positions [raw->sub_route->number_of_links - raw->sub_waypoint_count];
					}
					else
					{

						*wp_pos = raw->sub_route->link_positions [raw->sub_waypoint_count - 1];
					}
				}
				else
				{

					raw->sub_route = NULL;

					raw->sub_waypoint_count = 0;
				}
			}
		}
		else
		{

			vec3d
				offset;

			#if DEBUG_MODULE

			debug_log ("RV_MOVE: warning... routed vehicle %s (%d) is moving between %d and %d and has no sub_route setup",
							get_local_entity_string (en, STRING_TYPE_FULL_NAME),
							get_local_entity_index (en),
							get_local_entity_int_value (en, INT_TYPE_WAYPOINT_THIS_INDEX),
							get_local_entity_int_value (en, INT_TYPE_WAYPOINT_NEXT_INDEX));

			#endif

			get_local_entity_vec3d (guide, VEC3D_TYPE_GUIDE_POSITION, wp_pos);

			get_local_entity_formation_position_offset (en, wp, &offset);

			wp_pos->x += offset.x;
			wp_pos->y += offset.y;
			wp_pos->z += offset.z;
		}
	}

	//
	// calculate distance of entity to next waypoint position
	//

	pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	get_local_entity_vec3d (wp, VEC3D_TYPE_POSITION, &temp_pos);

	get_local_entity_formation_position_offset (en, wp, &offset);

	temp_pos.x += offset.x;
	temp_pos.y += offset.y;
	temp_pos.z += offset.z;

	distance = get_2d_range (pos, &temp_pos);

	set_local_entity_float_value (en, FLOAT_TYPE_DISTANCE, distance);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
