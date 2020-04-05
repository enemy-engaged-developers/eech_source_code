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

void basic_vehicle_movement (entity *en)
{
	vehicle
		*raw = nullptr;

	entity
		*wp = nullptr;

	vec3d
		*wp_pos = nullptr,
		wp_vec,
		new_pos,
		face_normal;

	float
		sqr_range,
		current_heading,
		required_heading,
		delta_heading,
		new_heading,
		current_velocity,
		new_velocity;

	raw = get_local_entity_data (en);

	///////////////////////////////////////
	//
	// Only update if entity has 2 waypoints
	//
	///////////////////////////////////////

	wp = get_local_entity_first_waypoint (en);

	if (!get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT))
	{

		#if DEBUG_MODULE

		debug_log ("AIRCRAFT MOVE: Entity with only 1 waypoint");

		#endif

		return;
	}

	////////////////////////////////////////
	//
	// current waypoint vector
	//
	////////////////////////////////////////

	wp = raw->mob.current_waypoint_link.parent;

	wp_pos = get_local_entity_vec3d_ptr (wp, VEC3D_TYPE_POSITION);

	wp_vec.x = wp_pos->x - raw->mob.position.x;
	wp_vec.y = wp_pos->y - raw->mob.position.y;
	wp_vec.z = wp_pos->z - raw->mob.position.z;

	sqr_range = (wp_vec.x * wp_vec.x) + (wp_vec.z * wp_vec.z);

	current_velocity = raw->mob.velocity;

	if ((sqr_range < ((current_velocity * current_velocity) / 2.0)) || (sqr_range < 1 * CENTIMETRE))
	{

		wp = get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT);

		if (!wp)
		{

			return;
		}

		delete_local_entity_from_parents_child_list (en, LIST_TYPE_CURRENT_WAYPOINT);

		insert_local_entity_into_parents_child_list (en, LIST_TYPE_CURRENT_WAYPOINT, wp, NULL);

		wp_pos = get_local_entity_vec3d_ptr (wp, VEC3D_TYPE_POSITION);

		wp_vec.x = wp_pos->x - raw->mob.position.x;
		wp_vec.y = wp_pos->y - raw->mob.position.y;
		wp_vec.z = wp_pos->z - raw->mob.position.z;

		//
		// safe guard against many waypoints exactly on top of each other
		//

		sqr_range = (wp_vec.x * wp_vec.x) + (wp_vec.z * wp_vec.z);

		if (fabs (sqr_range) < 1 * CENTIMETRE)
		{
			wp_vec.z = 0;
			wp_vec.y = 0;
			wp_vec.z = 1;
		}

		//
		// End of Safe Guard
		//
	}

	normalise_3d_vector (&wp_vec);

	////////////////////////////////////////
	//
	// heading
	//
	////////////////////////////////////////

	current_heading = get_heading_from_attitude_matrix (raw->mob.attitude);

	required_heading = atan2 (wp_vec.x, wp_vec.z);

	delta_heading = required_heading - current_heading;

	//
	// turn shortest way
	//

	if (delta_heading > PI)
	{
		delta_heading -= 2.0 * PI;
  	}
	else if (delta_heading < -PI)
	{
		delta_heading += 2.0 * PI;
	}

  	new_heading = current_heading + delta_heading * get_delta_time ();

	////////////////////////////////////////
	//
	// attitude
	//
	////////////////////////////////////////

	get_3d_terrain_face_normal (&face_normal, raw->mob.position.x, raw->mob.position.z);

	get_3d_transformation_matrix_from_face_normal_and_heading (&raw->mob.attitude, &face_normal, new_heading);

	////////////////////////////////////////
	//
	// velocity
	//
	////////////////////////////////////////

	new_velocity = get_local_entity_float_value (wp, FLOAT_TYPE_VELOCITY);

	raw->mob.velocity = new_velocity;

	////////////////////////////////////////
	//
	// position
	//
	////////////////////////////////////////

	new_pos.x = raw->mob.position.x + (new_velocity * raw->mob.zv.x * get_delta_time ());
	new_pos.y = raw->mob.position.y + (new_velocity * raw->mob.zv.y * get_delta_time ());
	new_pos.z = raw->mob.position.z + (new_velocity * raw->mob.zv.z * get_delta_time ());

	ASSERT(point_inside_map_area(&new_pos));
	
	new_pos.y = get_3d_terrain_elevation (new_pos.x, new_pos.z);

	set_local_entity_vec3d (en, VEC3D_TYPE_POSITION, &new_pos);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
