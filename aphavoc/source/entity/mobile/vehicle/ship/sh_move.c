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

static int clear_ship_fires (entity *ship_en, entity_sub_types type);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void ship_movement_get_waypoint_position (entity *en, vec3d *wp_pos)
{
	entity
		*wp,
		*group,
		*guide;

	float
		distance;

	vec3d
		*pos;

	ASSERT (en);

	ASSERT (wp_pos);

	group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

	ASSERT (group);

	guide = get_local_entity_parent (en, LIST_TYPE_FOLLOWER);

	ASSERT (guide);

	wp = get_local_entity_parent (guide, LIST_TYPE_CURRENT_WAYPOINT);

	ASSERT (wp);

	//
	// Should vehicle follow leader, or follow guide in set waypoint formation?
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
			// set wp pos to offset from task leader
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
			// find task leader
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
			
			wp_pos->x = leader_pos->x - ((xv->x * formation->sites [leader_formation_index].x) + (xv->z * formation->sites [leader_formation_index].z));
			wp_pos->y = 0;
			wp_pos->z = leader_pos->z - ((xv->z * formation->sites [leader_formation_index].x) + (xv->x * formation->sites [leader_formation_index].z));
	
			//
			// then ADD members formation position
			//
	
			wp_pos->x += ((xv->x * formation->sites [formation_index].x) + (xv->z * formation->sites [formation_index].z));
			wp_pos->z += ((xv->z * formation->sites [formation_index].x) + (xv->x * formation->sites [formation_index].z));
		}
	}

	//
	// calculate distance of entity to desired position
	//

	pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

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

void ship_vehicle_movement (entity *en)
{
	ship_vehicle
		*raw;

	entity
		*guide,
		*current_waypoint;

	vec3d
		wp_pos,
		wp_vec,
		new_pos;

	float
		roll,
		pitch,
		heading,
		sqr_range,
		turn_rate,
		required_heading,
		delta_heading,
		current_velocity,
		new_velocity;

	raw = get_local_entity_data (en);

	//
	// abort if mobile is not moving (i.e. landed, or dead)
	//

	if (!get_local_entity_int_value (en, INT_TYPE_MOBILE_MOVING))
	{

		return;
	}

	//
	// abort if the mobile has no PRIMARY guide (also stops ships from moving if just engaging)
	//

	guide = get_local_entity_primary_guide (en);

	if (!guide)
	{
		return;
	}

	current_waypoint = get_local_entity_parent (guide, LIST_TYPE_CURRENT_WAYPOINT);

	ASSERT (current_waypoint);

	current_velocity = raw->vh.mob.velocity;

	//
	// GET WAYPOINT POSITION
	//

	ship_movement_get_waypoint_position (en, &wp_pos);

	wp_vec.x = wp_pos.x - raw->vh.mob.position.x;
	wp_vec.y = 0;
	wp_vec.z = wp_pos.z - raw->vh.mob.position.z;

	sqr_range = ((wp_vec.x * wp_vec.x) + (wp_vec.z * wp_vec.z));

	#if DEBUG_MODULE

	create_vectored_debug_3d_object (&wp_pos, (vec3d *) &raw->vh.mob.attitude [1], OBJECT_3D_RED_ARROW, 0, 0.20);

	#endif
	
	// ????
	if (fabs (sqr_range) < 1 * CENTIMETRE)
	{
		wp_vec.z = 0;
		wp_vec.y = 0;
		wp_vec.z = 1;
	}

	////////////////////////////////////////
	//
	// angles
	//
	////////////////////////////////////////

	// heading

	normalise_3d_vector (&wp_vec);

	heading = get_heading_from_attitude_matrix (raw->vh.mob.attitude);

	required_heading = atan2 (wp_vec.x, wp_vec.z);

	{

		float
			angle,
			range,
			v;

		range = sqrt (sqr_range);
	
		v = sqrt (0.5 * range * vehicle_database [raw->vh.mob.sub_type].g_max);

		angle = ((raw->vh.mob.attitude [2][0] * wp_vec.x) + (raw->vh.mob.attitude [2][2] * wp_vec.z));

		if (angle < 0.707) // 45 degs.
		{

			// wp behind ship
	
			#if DEBUG_MODULE
		
			debug_log ("SH_MOVE: ship cannot reach wp at vel %f m/s (max v %f), range %f, g %f", raw->vh.mob.velocity, v, range, vehicle_database [raw->vh.mob.sub_type].g_max);

			#endif

			new_velocity = bound (v, 0.0, get_local_entity_float_value (guide, FLOAT_TYPE_VELOCITY));
		}
		else
		{
	
			#if DEBUG_MODULE
		
			debug_log ("SH_MOVE: ship can reach wp at vel %f m/s (max v %f), range %f, g %f", raw->vh.mob.velocity, v, range, vehicle_database [raw->vh.mob.sub_type].g_max);

			#endif

			new_velocity = get_local_entity_float_value (guide, FLOAT_TYPE_VELOCITY);
		}
	}

	turn_rate = 0.0;

	if (raw->vh.mob.velocity != 0.0)
	{

		turn_rate = fabs (vehicle_database [raw->vh.mob.sub_type].g_max / raw->vh.mob.velocity);
	}

	delta_heading = required_heading - heading;

	if (delta_heading <= -PI)
	{

		delta_heading += PI2;
	}

	if (delta_heading >= PI)
	{

		delta_heading -= PI2;
	}

	delta_heading = bound (delta_heading, -turn_rate, turn_rate);

	heading += delta_heading * get_entity_movement_delta_time ();

	pitch = 0.0;

	roll = 0.0;

	////////////////////////////////////////
	//
	// attitude
	//
	////////////////////////////////////////

	get_3d_transformation_matrix (raw->vh.mob.attitude, heading, rad (pitch), rad (roll));

	////////////////////////////////////////
	//
	// velocity
	//
	////////////////////////////////////////

	{
		float
			maximum_acceleration,
			required_acceleration;

		required_acceleration = (new_velocity - raw->vh.mob.velocity);

		maximum_acceleration = get_local_entity_float_value (en, FLOAT_TYPE_MAX_ACCELERATION);
		
		raw->vh.mob.velocity += min (required_acceleration, maximum_acceleration) * get_entity_movement_delta_time ();
	}

	////////////////////////////////////////
	//
	// position
	//
	////////////////////////////////////////

	new_pos.x = raw->vh.mob.position.x + (raw->vh.mob.velocity * raw->vh.mob.zv.x * get_entity_movement_delta_time ());
	new_pos.y = 0.0;
	new_pos.z = raw->vh.mob.position.z + (raw->vh.mob.velocity * raw->vh.mob.zv.z * get_entity_movement_delta_time ());

	bound_position_to_map_volume (&new_pos);

	//
	// Calculate motion vector for view system
	//

	raw->vh.mob.motion_vector.x = (new_pos.x - raw->vh.mob.position.x) * get_one_over_delta_time ();
	raw->vh.mob.motion_vector.y = 0.0;
	raw->vh.mob.motion_vector.z = (new_pos.z - raw->vh.mob.position.z) * get_one_over_delta_time ();

	new_pos.y = 0.0;

	set_local_entity_vec3d (en, VEC3D_TYPE_POSITION, &new_pos);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define SHIP_SINK_RATE	0.06

#define SHIP_SINK_DELTA_PITCH_RATE	rad(0.1)
#define SHIP_SINK_DELTA_ROLL_RATE	rad(0.5)

void ship_vehicle_death_movement (entity *en)
{

	ship_vehicle
		*raw;

	float
		speed,
		heading,
		pitch,
		roll;

	vec3d
		*pos,
		*velocity,
		new_pos;

	raw = get_local_entity_data (en);

	//
	// work out new position 
	//

	velocity = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_MOTION_VECTOR);

	pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	new_pos.x = pos->x + (velocity->x * get_entity_movement_delta_time());
	new_pos.y = pos->y + (velocity->y * get_entity_movement_delta_time());
	new_pos.z = pos->z + (velocity->z * get_entity_movement_delta_time());
	
	//
	// update velocity
	//

	velocity->x -= (velocity->x * 0.2 * get_entity_movement_delta_time ());
	velocity->z -= (velocity->z * 0.2 * get_entity_movement_delta_time ());
	velocity->y -= (SHIP_SINK_RATE * get_entity_movement_delta_time ());

	speed = get_3d_vector_magnitude (velocity);

	set_local_entity_float_value (en, FLOAT_TYPE_VELOCITY, speed);

	//
	// update attitude
	//
		
	heading = get_heading_from_attitude_matrix (raw->vh.mob.attitude);

	pitch = get_pitch_from_attitude_matrix (raw->vh.mob.attitude);

	pitch += (SHIP_SINK_DELTA_PITCH_RATE * get_entity_movement_delta_time());

	roll = get_roll_from_attitude_matrix (raw->vh.mob.attitude);
	
	roll += (SHIP_SINK_DELTA_ROLL_RATE * get_entity_movement_delta_time());

	get_3d_transformation_matrix (raw->vh.mob.attitude, heading, pitch, roll);

	//
	// set new position
	//

	set_local_entity_vec3d (en, VEC3D_TYPE_POSITION, &new_pos);

	clear_ship_fires (en, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_FIRE);
	clear_ship_fires (en, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_EXPLOSION_TRAIL);

	//
	// remove ship if totally obscured (i.e. sunk)
	//

	if (get_comms_model () == COMMS_MODEL_SERVER)
	{

		struct OBJECT_3D_BOUNDS
			*bounding_box;

		vec3d
			d;

		float
			obscured_altitude;

		bounding_box = get_object_3d_bounding_box (get_local_entity_int_value (en, INT_TYPE_OBJECT_3D_SHAPE));

		d.x = bounding_box->xmax - bounding_box->xmin;
		d.y = bounding_box->ymax - bounding_box->ymin;
		d.z = bounding_box->zmax - bounding_box->zmin;

		obscured_altitude = -(0.5 * get_3d_vector_magnitude (&d));

		if (new_pos.y < obscured_altitude)
		{
			//
			// ship is no longer visible
			//

			destroy_client_server_entity_family (en);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int clear_ship_fires (entity *ship_en, entity_sub_types type)
{
	entity
		*en;

	vec3d
		*pos;

	en = get_local_entity_first_child (ship_en, LIST_TYPE_SPECIAL_EFFECT);

	while (en)
	{
		if (en->type == ENTITY_TYPE_SMOKE_LIST)
		{
			if (get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE) == type)
			{
				pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

				if (pos->y < 0.0)
				{
					set_local_entity_float_value (en, FLOAT_TYPE_GENERATOR_LIFETIME, 0.0);
				}
			}
      }

		en = get_local_entity_child_succ (en, LIST_TYPE_SPECIAL_EFFECT);
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



