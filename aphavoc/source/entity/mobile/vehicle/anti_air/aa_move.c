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

//
// 3 levels of debug
//

#define DEBUG_MODULE 									0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void anti_aircraft_falling_movement (entity *en);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void anti_aircraft_death_movement (entity *en)
{

	anti_aircraft
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

	raw = (anti_aircraft *) get_local_entity_data (en);

	//
	// first check to see if vehicle is on the ground or not
	//

	pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	terrain_elevation = get_3d_terrain_point_data_elevation (&raw->vh.terrain_info);

	if ((get_terrain_type_class (get_3d_terrain_point_data_type (&raw->vh.terrain_info)) == TERRAIN_CLASS_WATER) ||
			(pos->y > (terrain_elevation + get_local_entity_float_value (en, FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE) + 0.2)))
	{

		anti_aircraft_falling_movement (en);

		return;
	}

	//
	// if vehicle has come to a stop, remove from update list
	//

	velocity = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_MOTION_VECTOR);

	speed = get_3d_vector_magnitude (velocity);

	if (speed == 0.0)
	{

		delete_local_entity_from_parents_child_list (en, LIST_TYPE_UPDATE);

		return;
	}

	//
	// work out new position 
	//

	new_pos.x = pos->x + (velocity->x * get_entity_movement_delta_time());
	new_pos.z = pos->z + (velocity->z * get_entity_movement_delta_time());
	
	get_3d_terrain_point_data (new_pos.x, new_pos.z, &raw->vh.terrain_info);

	terrain_elevation = get_3d_terrain_point_data_elevation (&raw->vh.terrain_info);

	new_pos.y = terrain_elevation + get_local_entity_float_value (en, FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE);

	//
	// update velocity
	//

	normalise_3d_vector_given_magnitude (velocity, speed);

	speed -= (4.0 * get_entity_movement_delta_time());

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

void anti_aircraft_falling_movement (entity *en)
{

	anti_aircraft
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

	raw = (anti_aircraft *) get_local_entity_data (en);

	//
	// get current position and velocity
	//

	pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	old_terrain_elevation = get_3d_terrain_point_data_elevation (&raw->vh.terrain_info);

	velocity = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_MOTION_VECTOR);

	new_pos.x = pos->x + (velocity->x * get_entity_movement_delta_time());
	new_pos.y = pos->y + (velocity->y * get_entity_movement_delta_time());
	new_pos.z = pos->z + (velocity->z * get_entity_movement_delta_time());
	
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

					create_client_server_object_hit_ground_explosion_effect (en, get_3d_terrain_point_data_type (&raw->vh.terrain_info));
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
	
					delete_local_entity_from_parents_child_list (en, LIST_TYPE_UPDATE);
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

				create_client_server_object_hit_ground_explosion_effect (en, get_3d_terrain_point_data_type (&raw->vh.terrain_info));
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

void anti_aircraft_impact_movement (entity *en)
{

	anti_aircraft
		*raw;

	float
		speed;

	vec3d
		*velocity;

	int
		seed;

	//
	// when a vehicle is killed it needs to be "moved out the way", so give it an instantaneous sideways velocity
	//

	raw = (anti_aircraft *) get_local_entity_data (en);

	seed = get_client_server_entity_random_number_seed(en);

	speed = 7.0 + (4.0 * frand1x (&seed));

	velocity = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_MOTION_VECTOR);

	velocity->x += (speed * raw->vh.mob.xv.x);

	velocity->z += (speed * raw->vh.mob.xv.z);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
