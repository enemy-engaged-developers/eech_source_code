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



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	fixed_collision_count,
	moving_collision_count;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_fixed_ground_collision_dynamics (void);

static void update_moving_ground_collision_dynamics (void);

static void update_object_collision_dynamics (void);

static void dynamics_service_fixed_collision_violations (void);

static void dynamics_service_moving_collision_violations (void);

static void dynamics_setup_fixed_collision_points (void);

static void dynamics_setup_moving_collision_points (void);

static int get_radius_collision_tree (vec3d *position, float model_radius, int ignore_forest_edge_trees, vec3d *collision_vector, vec3d *face_normal);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

dynamics_collision_point_type
	dynamics_collision_point_info [] =
	{
  		{
			"DYNAMICS_COLLISION_POINT_MAIN_ROTOR",
			OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_COLLISION_POINT,
			TRUE,
			DYNAMICS_DAMAGE_MAIN_ROTOR | 
			DYNAMICS_DAMAGE_MAIN_ROTOR_BLADE,
		},
		{
			"DYNAMICS_COLLISION_POINT_TAIL_ROTOR",
			OBJECT_3D_SUB_OBJECT_TAIL_ROTOR_COLLISION_POINT,
			TRUE,
			DYNAMICS_DAMAGE_TAIL_ROTOR | DYNAMICS_DAMAGE_STABILISER,
		},
		{
			"DYNAMICS_COLLISION_POINT_FUSELAGE",
			OBJECT_3D_SUB_OBJECT_FUSELAGE_COLLISION_POINT,
			FALSE,
			DYNAMICS_DAMAGE_LEFT_ENGINE | DYNAMICS_DAMAGE_RIGHT_ENGINE | DYNAMICS_DAMAGE_LOW_HYDRAULICS | DYNAMICS_DAMAGE_STABILISER |
			DYNAMICS_DAMAGE_LEFT_ENGINE_FIRE | DYNAMICS_DAMAGE_RIGHT_ENGINE_FIRE | DYNAMICS_DAMAGE_LOW_OIL_PRESSURE | DYNAMICS_DAMAGE_HIGH_OIL_PRESSURE,
		},
		{
			"DYNAMICS_COLLISION_POINT_NOSE_GUN",
			OBJECT_3D_SUB_OBJECT_NOSE_GUN_COLLISION_POINT,
			FALSE,
			DYNAMICS_DAMAGE_NONE,
		},
		{
			"DYNAMICS_COLLISION_POINT_WHEEL",
			OBJECT_3D_SUB_OBJECT_WHEEL_COLLISION_POINT,
			FALSE,
			DYNAMICS_DAMAGE_NONE,
		},
		{
			"DYNAMICS_COLLISION_POINT_WING_TIP",
			OBJECT_3D_SUB_OBJECT_WING_TIP_COLLISION_POINT,
			FALSE,
			DYNAMICS_DAMAGE_NONE,
		},
		{
			"NUM_DYNAMICS_COLLISION_POINT_TYPES",
			OBJECT_3D_SUB_OBJECT_COLLISION_POINT_FIXED,
			FALSE,
			DYNAMICS_DAMAGE_NONE,
		},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_dynamic_forces (void)
{

   current_flight_dynamics->max_number_of_dynamic_forces = NUMBER_OF_DYNAMIC_FORCES;

	current_flight_dynamics->dynamic_forces = (dynamic_force_type *) malloc_heap_mem (sizeof (dynamic_force_type) * current_flight_dynamics->max_number_of_dynamic_forces);

	memset (current_flight_dynamics->dynamic_forces, 0, sizeof (dynamic_force_type) * current_flight_dynamics->max_number_of_dynamic_forces);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_dynamic_forces (void)
{

	if (current_flight_dynamics->dynamic_forces)
	{

		free_mem (current_flight_dynamics->dynamic_forces);

		current_flight_dynamics->dynamic_forces = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_dynamic_force (char *name, float force, float duration, vec3d *position, vec3d *direction, int debug)
{

	int
		index;

	if (force == 0.0)
	{

		return;
	}

	if (current_flight_dynamics->number_of_dynamic_forces >= current_flight_dynamics->max_number_of_dynamic_forces)
	{

		dynamic_force_type
			*new_dynamic_forces;

		#if DEBUG_MODULE

		debug_log ("DYNAMICS: remallocing dynamic forces array to %d", current_flight_dynamics->max_number_of_dynamic_forces * 2);

		#endif

		new_dynamic_forces = (dynamic_force_type *) malloc_heap_mem (sizeof (dynamic_force_type) * current_flight_dynamics->max_number_of_dynamic_forces * 2);

		memset (new_dynamic_forces, 0, sizeof (dynamic_force_type) * current_flight_dynamics->max_number_of_dynamic_forces * 2);

		memcpy (new_dynamic_forces, current_flight_dynamics->dynamic_forces, sizeof (dynamic_force_type) * current_flight_dynamics->max_number_of_dynamic_forces);

		current_flight_dynamics->max_number_of_dynamic_forces *= 2;

		free_mem (current_flight_dynamics->dynamic_forces);

		current_flight_dynamics->dynamic_forces = new_dynamic_forces;
	}

	for (index = 0; index < current_flight_dynamics->max_number_of_dynamic_forces; index ++)
	{
	
		if (!current_flight_dynamics->dynamic_forces [index].valid)
		{
		
			current_flight_dynamics->dynamic_forces [index].valid = TRUE;
		
			current_flight_dynamics->dynamic_forces [index].position = *position;
		
			current_flight_dynamics->dynamic_forces [index].direction = *direction;
			
			current_flight_dynamics->dynamic_forces [index].linear_force = force;
		
			current_flight_dynamics->dynamic_forces [index].duration = duration;
		
			current_flight_dynamics->number_of_dynamic_forces ++;

			current_flight_dynamics->dynamic_forces [index].name = NULL;

			//#if DEBUG_MODULE

			//if ((get_current_dynamics_options (DYNAMICS_OPTIONS_DRAW_FLIGHT_PATH)) && (debug))
			if (debug)
			{
	
				current_flight_dynamics->dynamic_forces [index].name = (char *) malloc_heap_mem (sizeof (char) * (strlen (name) + 1));
	
				sprintf (current_flight_dynamics->dynamic_forces [index].name, "%s", name);

				debug_log ("DYNAMICS: adding dynamic force %s (index %d, count %d, max %d) %f at %f, %f, %f (dir %f, %f, %f)",
								current_flight_dynamics->dynamic_forces [index].name,
								index,
								current_flight_dynamics->number_of_dynamic_forces,
								current_flight_dynamics->max_number_of_dynamic_forces,
								force,
								position->x, position->y, position->z,
								direction->x, direction->y, direction->z);
			}

/*
			//debug_log ("CO_FORCE: adding force to joystick");
			set_joystick_force_feedback_forces (current_flight_dynamics->input_data.cyclic_joystick_device_index,
															direction->x * force * 500,
															direction->z * force * 500);
*/
			//#endif

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_dynamic_forces (void)
{
	int
		index;

	if (!get_gunship_entity ())
	{
		return;
	}

	//
	// destroy expired forces
	//

	for (index = 0; index < current_flight_dynamics->max_number_of_dynamic_forces; index ++)
	{

		if (current_flight_dynamics->dynamic_forces [index].valid)
		{
	
			current_flight_dynamics->dynamic_forces [index].duration -= get_model_delta_time ();
	
			if (current_flight_dynamics->dynamic_forces [index].duration <= 0.0)
			{
	
				current_flight_dynamics->dynamic_forces [index].valid = FALSE;

				current_flight_dynamics->number_of_dynamic_forces --;
	
				#if DEBUG_MODULE

				if (current_flight_dynamics->dynamic_forces [index].name)
				{

					debug_log ("DYNAMICS: destroying dynamic force %s (index %d, count %d, max %d) %f at %f, %f, %f",
								current_flight_dynamics->dynamic_forces [index].name,
								index,
								current_flight_dynamics->number_of_dynamic_forces,
								current_flight_dynamics->max_number_of_dynamic_forces,
								current_flight_dynamics->dynamic_forces [index].linear_force,
								current_flight_dynamics->dynamic_forces [index].position.x,
								current_flight_dynamics->dynamic_forces [index].position.y,
								current_flight_dynamics->dynamic_forces [index].position.z);

					free_mem (current_flight_dynamics->dynamic_forces [index].name);
				}
				else
				{
	
					debug_log ("DYNAMICS: destroying dynamic force (index %d, count %d, max %d) %f at %f, %f, %f",
									index,
									current_flight_dynamics->number_of_dynamic_forces,
									current_flight_dynamics->max_number_of_dynamic_forces,
									current_flight_dynamics->dynamic_forces [index].linear_force,
									current_flight_dynamics->dynamic_forces [index].position.x,
									current_flight_dynamics->dynamic_forces [index].position.y,
									current_flight_dynamics->dynamic_forces [index].position.z);
	
				}
				#endif
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void resolve_dynamic_forces (void)
{

	int
		index;

   matrix3x3
      delta_attitude,
      attitude;

   float
      force,
		moment_x,
		moment_y,
		moment_z,
      resultant_laterally,
      resultant_horizontally,
      resultant_vertically,
      resultant_x_axis,
      resultant_y_axis,
      resultant_z_axis;

   vec3d
		test_point,
		result;

   float
      roll,
      heading,
      pitch;

   ASSERT(get_gunship_entity());
   get_local_entity_attitude_matrix (get_gunship_entity (), attitude);

   // get heading, pitch, and roll

   heading = atan2 (attitude [2][0], attitude [2][2]);

   pitch = asin (attitude [2][1]);

   roll = atan2 (-attitude [0][1], attitude [1][1]);

   current_flight_dynamics->heading.value = heading;
   current_flight_dynamics->heading.delta = 0.0;;

   current_flight_dynamics->pitch.value = pitch;
   current_flight_dynamics->pitch.delta = 0.0;;

   current_flight_dynamics->roll.value = roll;
   current_flight_dynamics->roll.delta = 0.0;;

   ///////////////////////////////////////////////////////////////
   // Calculate zero moment position
   ///////////////////////////////////////////////////////////////

	force = 0;
	moment_x = 0;
	moment_y = 0;
	moment_z = 0;

	for (index = 0; index < current_flight_dynamics->max_number_of_dynamic_forces; index ++)
	{

		if (current_flight_dynamics->dynamic_forces [index].valid)
		{

			moment_x += (current_flight_dynamics->dynamic_forces [index].linear_force * current_flight_dynamics->dynamic_forces [index].position.z * current_flight_dynamics->dynamic_forces [index].direction.y) -
							(current_flight_dynamics->dynamic_forces [index].linear_force * current_flight_dynamics->dynamic_forces [index].position.y * current_flight_dynamics->dynamic_forces [index].direction.z);

			moment_y += (current_flight_dynamics->dynamic_forces [index].linear_force * current_flight_dynamics->dynamic_forces [index].position.z * current_flight_dynamics->dynamic_forces [index].direction.x) -
							(current_flight_dynamics->dynamic_forces [index].linear_force * current_flight_dynamics->dynamic_forces [index].position.x * current_flight_dynamics->dynamic_forces [index].direction.z);

			moment_z += (current_flight_dynamics->dynamic_forces [index].linear_force * current_flight_dynamics->dynamic_forces [index].position.x * current_flight_dynamics->dynamic_forces [index].direction.y) -
							(current_flight_dynamics->dynamic_forces [index].linear_force * current_flight_dynamics->dynamic_forces [index].position.y * current_flight_dynamics->dynamic_forces [index].direction.x);
		}
	}

	if (force)
	{
	
		current_flight_dynamics->rotation_origin.x = moment_x / force;
		current_flight_dynamics->rotation_origin.y = moment_y / force;
		current_flight_dynamics->rotation_origin.z = moment_z / force;
	}
	else
	{

		current_flight_dynamics->rotation_origin.x = 0.0;
		current_flight_dynamics->rotation_origin.y = 0.0;
		current_flight_dynamics->rotation_origin.z = 0.0;
	}

   ////////////////////////////////////////////////////////////////////////
	
	resolve_moments (current_flight_dynamics->rotation_origin.x, current_flight_dynamics->rotation_origin.y, current_flight_dynamics->rotation_origin.z, &resultant_x_axis, &resultant_y_axis, &resultant_z_axis);

   ////////////////////////////////////////////////////////////////////////

   //
   // Pitch: Resolve X Axis (clockwise)
   //

   current_flight_dynamics->angular_pitch_acceleration.value = resultant_x_axis;

   current_flight_dynamics->angular_pitch_velocity.value += current_flight_dynamics->angular_pitch_acceleration.value * get_model_delta_time ();

   current_flight_dynamics->pitch.delta = current_flight_dynamics->angular_pitch_velocity.value * get_model_delta_time ();

   ////////////////////////////////////////////////////////////////////////

   //
   // Roll: Resolve Z Axis (clockwise)
   //

   current_flight_dynamics->angular_roll_acceleration.value = resultant_z_axis;

   current_flight_dynamics->angular_roll_velocity.value -= current_flight_dynamics->angular_roll_acceleration.value * get_model_delta_time ();

   current_flight_dynamics->roll.delta = current_flight_dynamics->angular_roll_velocity.value * get_model_delta_time ();

   ////////////////////////////////////////////////////////////////////////

   //
   // Heading: Resolve Y Axis (clockwise)
   //

	//if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AIRBORNE_AIRCRAFT))
	{
	
		current_flight_dynamics->angular_heading_acceleration.value = resultant_y_axis;
	
		current_flight_dynamics->angular_heading_velocity.value -= current_flight_dynamics->angular_heading_acceleration.value * get_model_delta_time ();
	
		current_flight_dynamics->heading.delta = current_flight_dynamics->angular_heading_velocity.value * get_model_delta_time ();
	}

   ////////////////////////////////////////////////////////////////////////

  	get_3d_transformation_matrix (delta_attitude, -current_flight_dynamics->heading.delta, current_flight_dynamics->pitch.delta, current_flight_dynamics->roll.delta);

	multiply_matrix3x3_vec3d (&test_point, current_flight_dynamics->attitude, &current_flight_dynamics->rotation_origin);

	multiply_matrix3x3_matrix3x3 (current_flight_dynamics->attitude, delta_attitude, attitude);

	multiply_matrix3x3_vec3d (&result, current_flight_dynamics->attitude, &current_flight_dynamics->rotation_origin);

	result.x -= test_point.x;
	result.y -= test_point.y;
	result.z -= test_point.z;

	current_flight_dynamics->position.x -= result.x;
	current_flight_dynamics->position.y -= result.y;
	current_flight_dynamics->position.z -= result.z;

   ///////////////////////////////////////////////////////////////
   // Linear forces
   ///////////////////////////////////////////////////////////////

   //
   // Resolve acceleration Horizontally, Verically and Laterally
   //

   resultant_vertically = 0.0;
   resultant_horizontally = 0.0;
   resultant_laterally = 0.0;

	for (index = 0; index < current_flight_dynamics->max_number_of_dynamic_forces; index ++)
	{

		if (current_flight_dynamics->dynamic_forces [index].valid)
		{
	
			resultant_vertically += (current_flight_dynamics->dynamic_forces [index].linear_force * current_flight_dynamics->dynamic_forces [index].direction.y);
	
			resultant_horizontally += (current_flight_dynamics->dynamic_forces [index].linear_force * current_flight_dynamics->dynamic_forces [index].direction.z);
	
			resultant_laterally += (current_flight_dynamics->dynamic_forces [index].linear_force * current_flight_dynamics->dynamic_forces [index].direction.x);
		}
   }

   ///////////////////////////////////////////////////////////////
	// Auto hover calculations
   ///////////////////////////////////////////////////////////////
	{
	
		switch (current_flight_dynamics->auto_hover)
		{
	
			case HOVER_HOLD_NORMAL:
			case HOVER_HOLD_STABLE:
			{
	
				float
					i = 4.0;
	
				//
				// adjust collective accordingly
				//
		
				if ((current_flight_dynamics->velocity_y.value < 0.0) && (resultant_vertically < 1.0))
				{
		
					current_flight_dynamics->input_data.collective.value += i * get_delta_time ();
				}
				else if ((current_flight_dynamics->velocity_y.value > 0.0) && (resultant_vertically > -1.0))
				{
		
					current_flight_dynamics->input_data.collective.value -= i * get_delta_time ();
				}

				//
				// wash velocity out to zero
				//

				current_flight_dynamics->model_acceleration_vector.x = -(10.0 * get_model_delta_time ()) * current_flight_dynamics->model_motion_vector.x;
				current_flight_dynamics->model_acceleration_vector.y = resultant_vertically;
				current_flight_dynamics->model_acceleration_vector.z = -(10.0 * get_model_delta_time ()) * current_flight_dynamics->model_motion_vector.z;

				break;
			}
			case HOVER_HOLD_ALTITUDE_LOCK:
			{
		
				//
				// adjust collective accordingly
				//
	
				float
					i = 4.0,
					look_ahead_distance,
					delta_altitude;

				vec3d
					look_ahead_position;

				look_ahead_distance = HELICOPTER_TERRAIN_FOLLOW_LOOKAHEAD_TIME * current_flight_dynamics->velocity_z.value;

				look_ahead_position.x = current_flight_dynamics->position.x;
				look_ahead_position.y = current_flight_dynamics->position.y;
				look_ahead_position.z = current_flight_dynamics->position.z;

				look_ahead_position.x += current_flight_dynamics->attitude [2][0] * look_ahead_distance;
				look_ahead_position.z += current_flight_dynamics->attitude [2][2] * look_ahead_distance;

				look_ahead_position.y = get_3d_terrain_elevation (look_ahead_position.x, look_ahead_position.z);

				// take the highest point (either current_pos or look ahead point)
				look_ahead_position.y = max (look_ahead_position.y, current_flight_dynamics->altitude.min);

				// predicted altitude in 1 second
				delta_altitude = (current_flight_dynamics->altitude.value +
										(current_flight_dynamics->world_motion_vector.y + current_flight_dynamics->world_acceleration_vector.y)) -
										look_ahead_position.y;

				// subtract altitude lock
				delta_altitude -= current_flight_dynamics->altitude.max;
	  
				if (delta_altitude < 0.0)
				{

					i = min (i, -delta_altitude);
		
					current_flight_dynamics->input_data.collective.value += i * get_delta_time ();
				}
				else if (delta_altitude > 0.0)
				{

					i = min (i, delta_altitude);
		
					current_flight_dynamics->input_data.collective.value -= i * get_delta_time ();
				}
		
	  			// intentional follow through...
			}
	
			case HOVER_HOLD_NONE:
			default:
			{
		
				current_flight_dynamics->model_acceleration_vector.x = resultant_laterally;
				current_flight_dynamics->model_acceleration_vector.y = resultant_vertically;
				current_flight_dynamics->model_acceleration_vector.z = resultant_horizontally;
	
				break;
			}
		}
	}

	//debug_log ("current_flight_dynamics->model_acceleration_vector.y %f", current_flight_dynamics->model_acceleration_vector.y);

	if (!get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AIRBORNE_AIRCRAFT))
	{

		//current_flight_dynamics->model_acceleration_vector.y = max (0.0, resultant_vertically);
	}

   ///////////////////////////////////////////////////////////////

	//debug_log ("CO_FORCE: adding force to joystick");
	//set_joystick_force_feedback_forces (current_flight_dynamics->input_data.cyclic_joystick_device_index,
													//resultant_laterally * 1000.0, -resultant_horizontally * 1000.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_dynamic_forces (void)
{

	float
		size;

	vec3d
		pos,
		direction;

	matrix3x3
		attitude;

	vec3d
		old_position;

	int
		index;

	if (!get_gunship_entity ())
	{
		return;
	}

	if (get_in_flight_game_mode () != IN_FLIGHT_GAME_MODE_SIMULATOR)
	{
		return;
	}

	old_position.x = current_flight_dynamics->position.x - (current_flight_dynamics->world_motion_vector.x * get_delta_time ());
	old_position.y = current_flight_dynamics->position.y - (current_flight_dynamics->world_motion_vector.y * get_delta_time ());
	old_position.z = current_flight_dynamics->position.z - (current_flight_dynamics->world_motion_vector.z * get_delta_time ());

	get_local_entity_attitude_matrix (get_gunship_entity (), attitude);

	for (index = 0; index < current_flight_dynamics->max_number_of_dynamic_forces; index ++)
	{

		if (current_flight_dynamics->dynamic_forces [index].valid)
		{
	
			multiply_matrix3x3_vec3d (&pos, attitude, &current_flight_dynamics->dynamic_forces [index].position);
	
			direction = current_flight_dynamics->dynamic_forces [index].direction;
	
			multiply_matrix3x3_vec3d (&direction, attitude, &direction);
	
			pos.x += current_flight_dynamics->position.x;
			pos.y += current_flight_dynamics->position.y + 0.25;
			pos.z += current_flight_dynamics->position.z;
	
			current_flight_dynamics->dynamic_forces [index].linear_force *= 10;
	
			size = bound (current_flight_dynamics->dynamic_forces [index].linear_force * 0.25, -4.0, 4.0);
	
			pos.y += 2.0;
	
			create_vectored_debug_3d_object (&pos, &direction, OBJECT_3D_ARROW_FORCES, 0, size);
		}
	}

	// acceleration vector

	direction = current_flight_dynamics->model_acceleration_vector;

	if (!check_zero_3d_vector (&direction))
	{

		normalise_any_3d_vector (&direction);

		multiply_matrix3x3_vec3d (&direction, current_flight_dynamics->attitude, &direction);

		size = get_3d_vector_magnitude (&current_flight_dynamics->model_acceleration_vector);

		size = bound (size, -4.0, 4.0);

		pos.x = current_flight_dynamics->position.x;
		pos.y = current_flight_dynamics->position.y;
		pos.z = current_flight_dynamics->position.z;

		pos.y += 2.0;

//		create_vectored_debug_3d_object (&pos, &direction, OBJECT_3D_ARROW_FORCES, 0, size);
	}

	// motion vector

	direction = current_flight_dynamics->world_motion_vector;

	if (!check_zero_3d_vector (&direction))
	{

		normalise_any_3d_vector (&direction);

		size = get_3d_vector_magnitude (&current_flight_dynamics->world_motion_vector);

		size = bound (size, -4.0, 4.0);

		pos.x = current_flight_dynamics->position.x;
		pos.y = current_flight_dynamics->position.y;
		pos.z = current_flight_dynamics->position.z;

		pos.y += 2.0;

//		create_vectored_debug_3d_object (&pos, &direction, OBJECT_3D_ARROW_MOVEMENT, 0, size);
	}

	// motion line

	old_position.y += 2.0;

//	create_debug_3d_line (&old_position, &pos, sys_col_yellow, 20.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_dynamic_explosion_force (vec3d *explosion_position, float force)
{
/*
	vec3d
		position,
		direction;

	position.x = explosion_position->x - current_flight_dynamics->position.x;
	position.y = explosion_position->y - current_flight_dynamics->position.y;
	position.z = explosion_position->z - current_flight_dynamics->position.z;

	direction = position;

	direction.y = 0.0;

	invert_3d_vector (&direction);

	normalise_any_3d_vector (&direction);

	if (!check_zero_3d_vector (&direction))
	{
	
//		multiply_matrix3x3_vec3d (&direction, current_flight_dynamics->attitude, &direction);
		//multiply_transpose_matrix3x3_vec3d (&direction, current_flight_dynamics->attitude, &direction);

		force = bound (force, 0.0, 40.0);
	
		multiply_transpose_matrix3x3_vec3d (&position, current_flight_dynamics->attitude, &position);
	
		//add_dynamic_force ("Explosion force", force, 0.0, &position, &direction, FALSE);
	
		#if DEBUG_MODULE
	
		debug_log ("DYNAMICS: explosion force %f (strength %f, range %f), position %f, %f, %f, direction %f, %f, %f",
						force, force, get_3d_vector_magnitude (&position), position.x, position.y, position.z, direction.x, direction.y, direction.z);

		position.x += current_flight_dynamics->position.x;
		position.y += current_flight_dynamics->position.y;
		position.z += current_flight_dynamics->position.z;
	
		create_vectored_debug_3d_object (&position, &direction, OBJECT_3D_ARROW_FORCES, 1.0, 15.0);
	
		#endif
	}
	*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_dynamic_weapon_launch_force (vec3d *launch_position, vec3d *launch_direction, float force, float duration)
{

	vec3d
		position,
		direction;

	position.x = launch_position->x - current_flight_dynamics->position.x;
	position.y = 0.0;
	position.z = launch_position->z - current_flight_dynamics->position.z;

	multiply_transpose_matrix3x3_vec3d (&direction, current_flight_dynamics->attitude, launch_direction);

	invert_3d_vector (&direction);

	multiply_transpose_matrix3x3_vec3d (&position, current_flight_dynamics->attitude, &position);

	force /= (duration * MODEL_FRAME_RATE);

	//add_dynamic_force (force, duration, &position, &direction, FALSE);

	#if DEBUG_MODULE

	create_vectored_debug_3d_object (launch_position, &direction, OBJECT_3D_ARROW_FORCES, duration, 15.0);

	debug_log ("DYNAMICS: launch force %f (range %f), position %f, %f, %f, direction %f, %f, %f",
					force, get_3d_vector_magnitude (&position), position.x, position.y, position.z, direction.x, direction.y, direction.z);

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void resolve_moments (float x, float y, float z, float *x_axis_moment, float *y_axis_moment, float *z_axis_moment)
{

	int
		index;

	vec3d
		position;

   *x_axis_moment = 0.0;
   *y_axis_moment = 0.0;
   *z_axis_moment = 0.0;

	for (index = 0; index < current_flight_dynamics->max_number_of_dynamic_forces; index ++)
   {

		if (current_flight_dynamics->dynamic_forces [index].valid)
		{
	
			position.x = current_flight_dynamics->dynamic_forces [index].position.x + x;
			position.y = current_flight_dynamics->dynamic_forces [index].position.y + y;
			position.z = current_flight_dynamics->dynamic_forces [index].position.z + z;
	
			#if 0
	
			debug_log ("DYNAMICS:     %s F = %f, P = (%f, %f, %f), D = (%f, %f, %f), R = (%f, %f, %f)",
							current_flight_dynamics->dynamic_forces [index].name,
							current_flight_dynamics->dynamic_forces [index].linear_force,
							current_flight_dynamics->dynamic_forces [index].position.x, current_flight_dynamics->dynamic_forces [index].position.y, current_flight_dynamics->dynamic_forces [index].position.z,
							current_flight_dynamics->dynamic_forces [index].direction.x, current_flight_dynamics->dynamic_forces [index].direction.y, current_flight_dynamics->dynamic_forces [index].direction.z,
							(current_flight_dynamics->dynamic_forces [index].linear_force * position.z * current_flight_dynamics->dynamic_forces [index].direction.y) - (current_flight_dynamics->dynamic_forces [index].linear_force * position.y * current_flight_dynamics->dynamic_forces [index].direction.z),
							(current_flight_dynamics->dynamic_forces [index].linear_force * position.z * current_flight_dynamics->dynamic_forces [index].direction.x) - (current_flight_dynamics->dynamic_forces [index].linear_force * position.x * current_flight_dynamics->dynamic_forces [index].direction.z),
							(current_flight_dynamics->dynamic_forces [index].linear_force * position.x * current_flight_dynamics->dynamic_forces [index].direction.y) - (current_flight_dynamics->dynamic_forces [index].linear_force * position.y * current_flight_dynamics->dynamic_forces [index].direction.x));
	
			#endif
	
			*x_axis_moment += (current_flight_dynamics->dynamic_forces [index].linear_force * position.z * current_flight_dynamics->dynamic_forces [index].direction.y) - (current_flight_dynamics->dynamic_forces [index].linear_force * position.y * current_flight_dynamics->dynamic_forces [index].direction.z);
			*y_axis_moment += (current_flight_dynamics->dynamic_forces [index].linear_force * position.z * current_flight_dynamics->dynamic_forces [index].direction.x) - (current_flight_dynamics->dynamic_forces [index].linear_force * position.x * current_flight_dynamics->dynamic_forces [index].direction.z);
			*z_axis_moment += (current_flight_dynamics->dynamic_forces [index].linear_force * position.x * current_flight_dynamics->dynamic_forces [index].direction.y) - (current_flight_dynamics->dynamic_forces [index].linear_force * position.y * current_flight_dynamics->dynamic_forces [index].direction.x);
		}
   }
/*
			//debug_log ("CO_FORCE: adding force to joystick");
	set_joystick_force_feedback_forces (current_flight_dynamics->input_data.cyclic_joystick_device_index,
													*z_axis_moment * -3000, *x_axis_moment * 3000);
*/
	//debug_log ("%f, %f", *x_axis_moment * 5000, *z_axis_moment * 5000);

	#if 0

	debug_log ("DYNAMICS: origin %f, %f, %f, resultant x = %f, y = %f, z = %f",
		x,
		y,
		z,
		*x_axis_moment, *y_axis_moment, *z_axis_moment);

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_object_collision_dynamics (void)
{

	int
		loop;

	entity
		*collision_en;

	vec3d
		position,
		vec;

	helicopter
		*raw;

	if (!get_gunship_entity ())
	{

		return;
	}

	raw = get_local_entity_data (get_gunship_entity ());

	if ((current_flight_dynamics->valid_last_frame_fixed_collision_points) || (current_flight_dynamics->valid_last_frame_moving_collision_points))
	{

		entity
			*object,
			*sector;

		int
			x,
			z,
			loop_x,
			loop_z,
			start_loop_x,
			start_loop_z,
			detailed_test;

		float
			sqr_range,
			user_radius,
			object_radius;

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//
		// Quick radius check once for the whole object
		//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		detailed_test = FALSE;

		user_radius = get_object_3d_radius (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_OBJECT_3D_SHAPE));

		get_x_sector (x, current_flight_dynamics->position.x);
		get_z_sector (z, current_flight_dynamics->position.z);

		start_loop_x = max (x - 1, 0);
	
		start_loop_z = max (z - 1, 0);
	
		for (loop_x = start_loop_x; ((loop_x <= x + 1) && (loop_x < NUM_MAP_X_SECTORS)); loop_x ++)
		{
	
			for (loop_z = start_loop_z; ((loop_z <= z + 1) && (loop_z < NUM_MAP_Z_SECTORS)); loop_z ++)
			{
	
				sector = get_local_raw_sector_entity (loop_x, loop_z);

				object = get_local_entity_first_child (sector, LIST_TYPE_SECTOR);

				while (object)
				{
	
					if ((object != get_gunship_entity ()) &&
						(get_local_entity_int_value (object, INT_TYPE_COLLISION_TEST_FIXED) ||
						(get_local_entity_int_value (object, INT_TYPE_COLLISION_TEST_MOBILE))))
					{

						if ((get_local_entity_int_value (object, INT_TYPE_OBJECT_3D_SHAPE) != OBJECT_3D_FARP_MAT) &&
							(get_local_entity_int_value (object, INT_TYPE_OBJECT_3D_SHAPE) != OBJECT_3D_FARP_MAT_GREY))
						{
	
							object_radius = get_object_3d_radius (get_local_entity_int_value (object, INT_TYPE_OBJECT_3D_SHAPE));
	
							position.x = current_flight_dynamics->position.x;
							position.y = current_flight_dynamics->position.y;
							position.z = current_flight_dynamics->position.z;
	
							sqr_range = get_sqr_3d_range (get_local_entity_vec3d_ptr (object, VEC3D_TYPE_POSITION), &position);
	
							if (sqr_range < ((user_radius + object_radius) * (user_radius + object_radius)))
							{
	
								detailed_test = TRUE;
	
								break;
							}
						}
					}
	
					object = get_local_entity_child_succ (object, LIST_TYPE_SECTOR);
				}
			}
		}

		if (!detailed_test)
		{

			return;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//
		// detailed test
		//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//
		// Fixed
		//

		if (current_flight_dynamics->valid_last_frame_fixed_collision_points)
		{
		
			for (loop = 0; loop < current_flight_dynamics->number_of_fixed_collision_points; loop ++)
			{
	
				collision_en = get_line_of_sight_collision_entity (get_gunship_entity (),
																					NULL,
																					&current_flight_dynamics->fixed_collision_points [loop].world_point,
																					&current_flight_dynamics->last_frame_fixed_collision_points [loop].world_point,
																					&current_flight_dynamics->fixed_collision_points [loop].collision_point,
																					&current_flight_dynamics->fixed_collision_points [loop].face_normal);
	
				if (collision_en)
				{

					if (get_3d_vector_dot_product (&current_flight_dynamics->fixed_collision_points [loop].face_normal, &current_flight_dynamics->world_acceleration_vector) > 0.0)
					{

						//debug_log ("CO_FORCE: objects moving apart");
					}
					else
					{
			
						fixed_collision_count ++;
			
						current_flight_dynamics->fixed_collision_points [loop].violated = TRUE;
			
						current_flight_dynamics->world_motion_vector.x = 0.0;
						current_flight_dynamics->world_motion_vector.y = 0.0;
						current_flight_dynamics->world_motion_vector.z = 0.0;
			
						current_flight_dynamics->model_acceleration_vector.x = 0.0;
						current_flight_dynamics->model_acceleration_vector.y = 0.0;
						current_flight_dynamics->model_acceleration_vector.z = 0.0;
			
						vec.x = current_flight_dynamics->fixed_collision_points [loop].world_point.x - current_flight_dynamics->fixed_collision_points [loop].collision_point.x;
						vec.y = current_flight_dynamics->fixed_collision_points [loop].world_point.y - current_flight_dynamics->fixed_collision_points [loop].collision_point.y;
						vec.z = current_flight_dynamics->fixed_collision_points [loop].world_point.z - current_flight_dynamics->fixed_collision_points [loop].collision_point.z;
		
						current_flight_dynamics->fixed_collision_points [loop].violation_distance = get_3d_vector_magnitude (&vec) + 0.02;
			
						#if 0

						debug_log ("DYNAMICS: violation dist %f, start %f, %f, %f, stop %f, %f, %f, collision %f, %f, %f, normal %f, %f, %f",
										current_flight_dynamics->fixed_collision_points [loop].violation_distance,
										current_flight_dynamics->fixed_collision_points [loop].world_point.x,
										current_flight_dynamics->fixed_collision_points [loop].world_point.y,
										current_flight_dynamics->fixed_collision_points [loop].world_point.z,
										current_flight_dynamics->last_frame_fixed_collision_points [loop].world_point.x,
										current_flight_dynamics->last_frame_fixed_collision_points [loop].world_point.y,
										current_flight_dynamics->last_frame_fixed_collision_points [loop].world_point.z,
										current_flight_dynamics->fixed_collision_points [loop].collision_point.x,
										current_flight_dynamics->fixed_collision_points [loop].collision_point.y,
										current_flight_dynamics->fixed_collision_points [loop].collision_point.z,
										current_flight_dynamics->fixed_collision_points [loop].face_normal.x,
										current_flight_dynamics->fixed_collision_points [loop].face_normal.y,
										current_flight_dynamics->fixed_collision_points [loop].face_normal.z);
				
						debug_log ("DYNAMICS: possible object %s collision", get_local_entity_type_name (collision_en));
			
						create_vectored_debug_3d_object (&current_flight_dynamics->fixed_collision_points [loop].world_point, &current_flight_dynamics->fixed_collision_points [loop].face_normal, OBJECT_3D_ARROW_FORCES, 10, 5.0);
		
						#endif
					}
				}
			}
		}

		//
		// Moving
		//

		if (current_flight_dynamics->valid_last_frame_moving_collision_points)
		{
		
			for (loop = 0; loop < current_flight_dynamics->number_of_moving_collision_points; loop ++)
			{
	
				collision_en = get_line_of_sight_collision_entity (get_gunship_entity (),
																					NULL,
																					&current_flight_dynamics->moving_collision_points [loop].world_point,
																					&current_flight_dynamics->last_frame_moving_collision_points [loop].world_point,
																					&current_flight_dynamics->moving_collision_points [loop].collision_point,
																					&current_flight_dynamics->moving_collision_points [loop].face_normal);
	
				if (collision_en)
				{
		
					moving_collision_count ++;
		
					current_flight_dynamics->moving_collision_points [loop].violated = TRUE;
		
					current_flight_dynamics->world_motion_vector.x = 0.0;
					current_flight_dynamics->world_motion_vector.y = 0.0;
					current_flight_dynamics->world_motion_vector.z = 0.0;
		
					current_flight_dynamics->model_acceleration_vector.x = 0.0;
					current_flight_dynamics->model_acceleration_vector.y = 0.0;
					current_flight_dynamics->model_acceleration_vector.z = 0.0;
		
					vec.x = current_flight_dynamics->moving_collision_points [loop].world_point.x - current_flight_dynamics->moving_collision_points [loop].collision_point.x;
					vec.y = current_flight_dynamics->moving_collision_points [loop].world_point.y - current_flight_dynamics->moving_collision_points [loop].collision_point.y;
					vec.z = current_flight_dynamics->moving_collision_points [loop].world_point.z - current_flight_dynamics->moving_collision_points [loop].collision_point.z;
	
					current_flight_dynamics->moving_collision_points [loop].violation_distance = get_3d_vector_magnitude (&vec) + 0.02;

					#if 0
			
					debug_log ("DYNAMICS: possible object %s collision", get_local_entity_type_name (collision_en));
	
					debug_log ("DYNAMICS: violation dist %f, start %f, %f, %f, stop %f, %f, %f, collision %f, %f, %f, normal %f, %f, %f",
									current_flight_dynamics->moving_collision_points [loop].violation_distance,
									current_flight_dynamics->moving_collision_points [loop].world_point.x,
									current_flight_dynamics->moving_collision_points [loop].world_point.y,
									current_flight_dynamics->moving_collision_points [loop].world_point.z,
									current_flight_dynamics->last_frame_moving_collision_points [loop].world_point.x,
									current_flight_dynamics->moving_frame_fixed_collision_points [loop].world_point.y,
									current_flight_dynamics->moving_frame_fixed_collision_points [loop].world_point.z,
									current_flight_dynamics->moving_collision_points [loop].collision_point.x,
									current_flight_dynamics->moving_collision_points [loop].collision_point.y,
									current_flight_dynamics->moving_collision_points [loop].collision_point.z,
									current_flight_dynamics->moving_collision_points [loop].face_normal.x,
									current_flight_dynamics->moving_collision_points [loop].face_normal.y,
									current_flight_dynamics->moving_collision_points [loop].face_normal.z);
		
					create_vectored_debug_3d_object (&current_flight_dynamics->moving_collision_points [loop].world_point, &current_flight_dynamics->moving_collision_points [loop].face_normal, OBJECT_3D_ARROW_FORCES, 10, 5.0);
	
					#endif
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_tree_collision_dynamics (void)
{

	int
		collision,
		loop;

	vec3d
		collision_vector,
		vec;

	helicopter
		*raw;

	if (!get_gunship_entity ())
	{

		return;
	}

	raw = get_local_entity_data (get_gunship_entity ());

	collision = FALSE;

	if ((current_flight_dynamics->valid_last_frame_fixed_collision_points) || (current_flight_dynamics->valid_last_frame_moving_collision_points))
	{

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//
		// detailed test
		//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		loop = 0;

		//
		// Fixed
		//

		//if (current_flight_dynamics->valid_last_frame_fixed_collision_points)
		{
		
			for (loop = 0; loop < current_flight_dynamics->number_of_fixed_collision_points; loop ++)
			{

				collision = get_radius_collision_tree (&current_flight_dynamics->fixed_collision_points [loop].world_point, 0.5, TRUE, &collision_vector, &current_flight_dynamics->fixed_collision_points [loop].face_normal);

				if (collision)
				{
		
					fixed_collision_count ++;
		
					current_flight_dynamics->fixed_collision_points [loop].violated = TRUE;
		
					current_flight_dynamics->world_motion_vector.x = 0.0;
					current_flight_dynamics->world_motion_vector.y = 0.0;
					current_flight_dynamics->world_motion_vector.z = 0.0;
		
					current_flight_dynamics->model_acceleration_vector.x = 0.0;
					current_flight_dynamics->model_acceleration_vector.y = 0.0;
					current_flight_dynamics->model_acceleration_vector.z = 0.0;
		
					vec.x = current_flight_dynamics->fixed_collision_points [loop].world_point.x - current_flight_dynamics->fixed_collision_points [loop].collision_point.x;
					vec.y = current_flight_dynamics->fixed_collision_points [loop].world_point.y - current_flight_dynamics->fixed_collision_points [loop].collision_point.y;
					vec.z = current_flight_dynamics->fixed_collision_points [loop].world_point.z - current_flight_dynamics->fixed_collision_points [loop].collision_point.z;

					current_flight_dynamics->fixed_collision_points [loop].collision_point.x = current_flight_dynamics->fixed_collision_points [loop].world_point.x;
					current_flight_dynamics->fixed_collision_points [loop].collision_point.y = current_flight_dynamics->fixed_collision_points [loop].world_point.y;
					current_flight_dynamics->fixed_collision_points [loop].collision_point.z = current_flight_dynamics->fixed_collision_points [loop].world_point.z;

					current_flight_dynamics->fixed_collision_points [loop].violation_distance = get_3d_vector_magnitude (&collision_vector);
		
					#if 0
	
					debug_log ("DYNAMICS: violation dist %f, start %f, %f, %f, stop %f, %f, %f, collision %f, %f, %f, normal %f, %f, %f",
									current_flight_dynamics->fixed_collision_points [loop].violation_distance,
									current_flight_dynamics->fixed_collision_points [loop].world_point.x,
									current_flight_dynamics->fixed_collision_points [loop].world_point.y,
									current_flight_dynamics->fixed_collision_points [loop].world_point.z,
									current_flight_dynamics->last_frame_fixed_collision_points [loop].world_point.x,
									current_flight_dynamics->last_frame_fixed_collision_points [loop].world_point.y,
									current_flight_dynamics->last_frame_fixed_collision_points [loop].world_point.z,
									current_flight_dynamics->fixed_collision_points [loop].collision_point.x,
									current_flight_dynamics->fixed_collision_points [loop].collision_point.y,
									current_flight_dynamics->fixed_collision_points [loop].collision_point.z,
									current_flight_dynamics->fixed_collision_points [loop].face_normal.x,
									current_flight_dynamics->fixed_collision_points [loop].face_normal.y,
									current_flight_dynamics->fixed_collision_points [loop].face_normal.z);
			
					debug_filtered_log ("DYNAMICS: possible fixed point object collision");
		
					//create_vectored_debug_3d_object (&current_flight_dynamics->fixed_collision_points [loop].world_point, &current_flight_dynamics->fixed_collision_points [loop].face_normal, OBJECT_3D_ARROW_FORCES, 10, 5.0);
	
					#endif
				}
			}
		}

		//
		// Moving
		//

		if (current_flight_dynamics->valid_last_frame_moving_collision_points)
		{
		
			for (loop = 0; loop < current_flight_dynamics->number_of_moving_collision_points; loop ++)
			{
	
				collision = get_radius_collision_tree (&current_flight_dynamics->moving_collision_points [loop].world_point, 0.5, TRUE, &collision_vector, &current_flight_dynamics->moving_collision_points [loop].face_normal);
	
				if (collision)
				{
		
					moving_collision_count ++;
		
					current_flight_dynamics->moving_collision_points [loop].violated = TRUE;
		
					current_flight_dynamics->world_motion_vector.x = 0.0;
					current_flight_dynamics->world_motion_vector.y = 0.0;
					current_flight_dynamics->world_motion_vector.z = 0.0;
		
					current_flight_dynamics->model_acceleration_vector.x = 0.0;
					current_flight_dynamics->model_acceleration_vector.y = 0.0;
					current_flight_dynamics->model_acceleration_vector.z = 0.0;
		
					vec.x = current_flight_dynamics->moving_collision_points [loop].world_point.x - current_flight_dynamics->moving_collision_points [loop].collision_point.x;
					vec.y = current_flight_dynamics->moving_collision_points [loop].world_point.y - current_flight_dynamics->moving_collision_points [loop].collision_point.y;
					vec.z = current_flight_dynamics->moving_collision_points [loop].world_point.z - current_flight_dynamics->moving_collision_points [loop].collision_point.z;

					current_flight_dynamics->moving_collision_points [loop].collision_point.x = current_flight_dynamics->moving_collision_points [loop].world_point.x;
					current_flight_dynamics->moving_collision_points [loop].collision_point.y = current_flight_dynamics->moving_collision_points [loop].world_point.y;
					current_flight_dynamics->moving_collision_points [loop].collision_point.z = current_flight_dynamics->moving_collision_points [loop].world_point.z;
	
					current_flight_dynamics->moving_collision_points [loop].violation_distance = get_3d_vector_magnitude (&collision_vector);

					#if 0
	
					debug_log ("DYNAMICS: violation dist %f, start %f, %f, %f, stop %f, %f, %f, collision %f, %f, %f, normal %f, %f, %f",
									current_flight_dynamics->moving_collision_points [loop].violation_distance,
									current_flight_dynamics->moving_collision_points [loop].world_point.x,
									current_flight_dynamics->moving_collision_points [loop].world_point.y,
									current_flight_dynamics->moving_collision_points [loop].world_point.z,
									current_flight_dynamics->last_frame_moving_collision_points [loop].world_point.x,
									current_flight_dynamics->last_frame_moving_collision_points [loop].world_point.y,
									current_flight_dynamics->last_frame_moving_collision_points [loop].world_point.z,
									current_flight_dynamics->moving_collision_points [loop].collision_point.x,
									current_flight_dynamics->moving_collision_points [loop].collision_point.y,
									current_flight_dynamics->moving_collision_points [loop].collision_point.z,
									current_flight_dynamics->moving_collision_points [loop].face_normal.x,
									current_flight_dynamics->moving_collision_points [loop].face_normal.y,
									current_flight_dynamics->moving_collision_points [loop].face_normal.z);
			
					debug_filtered_log ("DYNAMICS: possible moving point tree collision");
		
					//create_vectored_debug_3d_object (&current_flight_dynamics->moving_collision_points [loop].world_point, &current_flight_dynamics->moving_collision_points [loop].face_normal, OBJECT_3D_ARROW_FORCES, 10, 5.0);
	
					#endif
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_fixed_ground_collision_dynamics (void)
{

	helicopter
		*raw;

	float
		temp_water_offset;

	int
		loop;

	if (!get_gunship_entity ())
	{

		return;
	}

	raw = get_local_entity_data (get_gunship_entity ());

	//
	// Check FIXED collision points with GROUND
	//

	for (loop = 0; loop < current_flight_dynamics->number_of_fixed_collision_points; loop ++)
	{

		get_3d_terrain_point_data (current_flight_dynamics->fixed_collision_points [loop].world_point.x, current_flight_dynamics->fixed_collision_points [loop].world_point.z, &raw->ac.terrain_info);

		current_flight_dynamics->fixed_collision_points [loop].terrain_elevation = get_3d_terrain_point_data_elevation (&raw->ac.terrain_info);

		temp_water_offset = 0.0;

		if (get_terrain_type_class (get_3d_terrain_point_data_type (&raw->ac.terrain_info)) != TERRAIN_CLASS_LAND)
		{

			temp_water_offset = water_offset;
		}

		if (current_flight_dynamics->fixed_collision_points [loop].terrain_elevation + temp_water_offset > current_flight_dynamics->fixed_collision_points [loop].world_point.y)
		{

			fixed_collision_count ++;

			current_flight_dynamics->fixed_collision_points [loop].violation_distance = fabs (current_flight_dynamics->fixed_collision_points [loop].terrain_elevation - current_flight_dynamics->fixed_collision_points [loop].world_point.y) + temp_water_offset;

			current_flight_dynamics->fixed_collision_points [loop].violated = TRUE;

			memcpy (&current_flight_dynamics->fixed_collision_points [loop].face_normal, get_3d_terrain_point_data_normal (&raw->ac.terrain_info), sizeof (vec3d));

			current_flight_dynamics->fixed_collision_points [loop].collision_point = current_flight_dynamics->fixed_collision_points [loop].world_point;
			current_flight_dynamics->fixed_collision_points [loop].collision_point.y = current_flight_dynamics->fixed_collision_points [loop].terrain_elevation + temp_water_offset;

			// if under water kill, something like water_offset - 0.5m
			if (temp_water_offset != 0.0)
			{

				if (current_flight_dynamics->fixed_collision_points [loop].terrain_elevation + temp_water_offset + 0.5 > current_flight_dynamics->fixed_collision_points [loop].world_point.y)
				{

					dynamics_kill_model (DYNAMICS_DESTROY_WATER_CRASH, NULL);

					break;
				}
			}
			//
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_moving_ground_collision_dynamics (void)
{

	int
		loop;

	helicopter
		*raw;

	if (!get_gunship_entity ())
	{

		return;
	}

	raw = get_local_entity_data (get_gunship_entity ());

	//
	// Check MOVING collision points with GROUND
	//

	for (loop = 0; loop < current_flight_dynamics->number_of_moving_collision_points; loop ++)
	{

		get_3d_terrain_point_data (current_flight_dynamics->moving_collision_points [loop].world_point.x, current_flight_dynamics->moving_collision_points [loop].world_point.z, &raw->ac.terrain_info);

		current_flight_dynamics->moving_collision_points [loop].terrain_elevation = get_3d_terrain_point_data_elevation (&raw->ac.terrain_info);

		if ((current_flight_dynamics->moving_collision_points [loop].terrain_elevation) > current_flight_dynamics->moving_collision_points [loop].world_point.y)
		{

			moving_collision_count ++;

			current_flight_dynamics->moving_collision_points [loop].violation_distance = fabs (current_flight_dynamics->moving_collision_points [loop].terrain_elevation - current_flight_dynamics->moving_collision_points [loop].world_point.y);

			current_flight_dynamics->moving_collision_points [loop].violated = TRUE;

			memcpy (&current_flight_dynamics->moving_collision_points [loop].face_normal, get_3d_terrain_point_data_normal (&raw->ac.terrain_info), sizeof (vec3d));

			current_flight_dynamics->moving_collision_points [loop].collision_point = current_flight_dynamics->moving_collision_points [loop].world_point;

			current_flight_dynamics->moving_collision_points [loop].collision_point.y = current_flight_dynamics->moving_collision_points [loop].terrain_elevation;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_collision_dynamics (void)
{

	int
		fatal,
		loop;

	helicopter
		*raw;

	if (!get_gunship_entity ())
	{

		return;
	}
		
	raw = get_local_entity_data (get_gunship_entity ());

	fixed_collision_count = 0;

	moving_collision_count = 0;

	///////////////////////////////////////////////////////////////////
	//
	// check for collision
	//
	///////////////////////////////////////////////////////////////////

	dynamics_setup_fixed_collision_points ();
	update_fixed_ground_collision_dynamics ();
	dynamics_service_fixed_collision_violations ();
	
	/////////////////////////////////

	dynamics_setup_moving_collision_points ();
	update_moving_ground_collision_dynamics ();
	dynamics_service_moving_collision_violations ();

	/////////////////////////////////

	dynamics_setup_fixed_collision_points ();
	dynamics_setup_moving_collision_points ();

	update_object_collision_dynamics ();

	dynamics_service_fixed_collision_violations ();
	dynamics_service_moving_collision_violations ();

	/////////////////////////////////

	dynamics_setup_fixed_collision_points ();
	dynamics_setup_moving_collision_points ();

	update_tree_collision_dynamics ();

	dynamics_service_fixed_collision_violations ();
	dynamics_service_moving_collision_violations ();

	///////////////////////////////////////////////////////////////////
	//
	// store this frames collision points with new position
	//
	///////////////////////////////////////////////////////////////////

	if (!get_gunship_entity ())
	{

		return;
	}

	memcpy (current_flight_dynamics->last_frame_fixed_collision_points, current_flight_dynamics->fixed_collision_points, sizeof (dynamics_collision_type) * current_flight_dynamics->number_of_fixed_collision_points);

	for (loop = 0; loop < current_flight_dynamics->number_of_fixed_collision_points; loop ++)
	{

		multiply_matrix3x3_vec3d (&current_flight_dynamics->last_frame_fixed_collision_points [loop].world_point,
											raw->ac.inst3d->vp.attitude,
											&current_flight_dynamics->last_frame_fixed_collision_points [loop].model_point);

		current_flight_dynamics->last_frame_fixed_collision_points [loop].world_point.x += current_flight_dynamics->position.x;
		current_flight_dynamics->last_frame_fixed_collision_points [loop].world_point.y += current_flight_dynamics->position.y;
		current_flight_dynamics->last_frame_fixed_collision_points [loop].world_point.z += current_flight_dynamics->position.z;

		bound_position_to_map_area (&current_flight_dynamics->last_frame_fixed_collision_points [loop].world_point);
	}

	current_flight_dynamics->valid_last_frame_fixed_collision_points = TRUE;

	//

	memcpy (current_flight_dynamics->last_frame_moving_collision_points, current_flight_dynamics->moving_collision_points, sizeof (dynamics_collision_type) * current_flight_dynamics->number_of_moving_collision_points);

	for (loop = 0; loop < current_flight_dynamics->number_of_moving_collision_points; loop ++)
	{

		multiply_matrix3x3_vec3d (&current_flight_dynamics->last_frame_moving_collision_points [loop].world_point,
											raw->ac.inst3d->vp.attitude,
											&current_flight_dynamics->last_frame_moving_collision_points [loop].model_point);

		current_flight_dynamics->last_frame_moving_collision_points [loop].world_point.x += current_flight_dynamics->position.x;
		current_flight_dynamics->last_frame_moving_collision_points [loop].world_point.y += current_flight_dynamics->position.y;
		current_flight_dynamics->last_frame_moving_collision_points [loop].world_point.z += current_flight_dynamics->position.z;

		bound_position_to_map_area (&current_flight_dynamics->last_frame_moving_collision_points [loop].world_point);
	}

	current_flight_dynamics->valid_last_frame_moving_collision_points = TRUE;

	///////////////////////////////////////////////////////////////////
	//
	// landing stuff
	//
	///////////////////////////////////////////////////////////////////

	if (fixed_collision_count == 0)
	{

		if (!get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AIRBORNE_AIRCRAFT))
		{

			if (current_flight_dynamics->world_motion_vector.y > 0.0)
			{
		
				dynamics_takeoff ();
			}
		}
	}
	else
	{

		if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AIRBORNE_AIRCRAFT))
		{

			float
				landing_assessment;
	
			//
			// Assess quality of landing
			//

			fatal = FALSE;

			landing_assessment = current_flight_dynamics->world_motion_vector.y - fabs (current_flight_dynamics->model_motion_vector.z / 10.0);

			// landed with undercarriage up
			if (current_flight_dynamics->undercarriage_state.value != 1.0)
			{

				dynamics_damage_model ( DYNAMICS_DAMAGE_LOW_HYDRAULICS |
												DYNAMICS_DAMAGE_STABILISER |
												DYNAMICS_DAMAGE_FUEL_LEAK |
												DYNAMICS_DAMAGE_LOW_OIL_PRESSURE |
												DYNAMICS_DAMAGE_HIGH_OIL_PRESSURE,
												TRUE);

				fatal = get_current_dynamics_fatal_damage ();
	
				//#if DEBUG_DYNAMICS >= 2
	
				debug_log ("CO_FORCE: landed with undercarriage up");
	
				//#endif
			}
			//

			debug_log ("CO_FORCE: landing force %f", landing_assessment);
	
			if (landing_assessment < current_flight_dynamics->landing_quality.max)
			{
	
				dynamics_damage_model (DYNAMICS_DAMAGE_MAIN_ROTOR, FALSE);
				dynamics_damage_model (DYNAMICS_DAMAGE_TAIL_ROTOR, FALSE);
				dynamics_damage_model (DYNAMICS_DAMAGE_LEFT_ENGINE, FALSE);
				dynamics_damage_model (DYNAMICS_DAMAGE_RIGHT_ENGINE, FALSE);
				dynamics_damage_model (DYNAMICS_DAMAGE_FUEL_LEAK, FALSE);
				dynamics_damage_model (DYNAMICS_DAMAGE_STABILISER, FALSE);
				dynamics_damage_model (DYNAMICS_DAMAGE_HIGH_OIL_PRESSURE, FALSE);

				fatal = get_current_dynamics_fatal_damage ();
	
				//#if DEBUG_DYNAMICS >= 2
	
				debug_log ("CO_FORCE: crash landing");
	
				//#endif
			}
			else if (landing_assessment < current_flight_dynamics->landing_quality.value)
			{
	
				dynamics_damage_model ( DYNAMICS_DAMAGE_MAIN_ROTOR |
										DYNAMICS_DAMAGE_MAIN_ROTOR_BLADE |
												DYNAMICS_DAMAGE_TAIL_ROTOR |
												DYNAMICS_DAMAGE_LEFT_ENGINE |
												DYNAMICS_DAMAGE_RIGHT_ENGINE |
												DYNAMICS_DAMAGE_LEFT_ENGINE_FIRE |
												DYNAMICS_DAMAGE_RIGHT_ENGINE_FIRE |
												DYNAMICS_DAMAGE_LOW_HYDRAULICS |
												DYNAMICS_DAMAGE_STABILISER |
												DYNAMICS_DAMAGE_FUEL_LEAK |
												DYNAMICS_DAMAGE_LOW_OIL_PRESSURE |
												DYNAMICS_DAMAGE_HIGH_OIL_PRESSURE,
												TRUE);

				fatal = get_current_dynamics_fatal_damage ();
	
				//#if DEBUG_DYNAMICS >= 2
	
				debug_log ("CO_FORCE: heavy landing");
	
				//#endif
			}
			else if (landing_assessment < current_flight_dynamics->landing_quality.delta)
			{

				//#if DEBUG_DYNAMICS >= 2
	
				debug_log ("CO_FORCE: ok landing");
	
				//#endif
			}
			else if (landing_assessment < current_flight_dynamics->landing_quality.min)
			{

				//#if DEBUG_DYNAMICS >= 2
	
				debug_log ("CO_FORCE: good landing");
	
				//#endif
			}
			else
			{
	
				//#if DEBUG_DYNAMICS >= 2

				debug_log ("CO_FORCE: very good landing");
	
				//#endif
			}
	
			//
			//
			//
	
			if ((get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE)) && (fatal))
			{
	
				entity
					*force,
					*enemy_force;
	
				//
				// Enter demo mode
				//
	
				force = get_local_force_entity (get_global_gunship_side ());
	
				enemy_force = get_local_force_entity (get_enemy_side (get_global_gunship_side ()));
	
				notify_local_entity (ENTITY_MESSAGE_FORCE_DESTROYED, force, get_gunship_entity (), NULL); 
	
				notify_local_entity (ENTITY_MESSAGE_FORCE_DESTROYED, enemy_force, get_gunship_entity (), NULL);
	
				dynamics_kill_model (DYNAMICS_DESTROY_CRASH_LANDED, NULL);
			}
			else
			{
	
				dynamics_land ();
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
				enum TERRAIN_TYPES
					collision_terrain_type;

				vec3d
					result,
					*normal;

				float
					force,
					n_n,
					a_n;

				collision_terrain_type = get_3d_terrain_point_data_type (&raw->ac.terrain_info);
	
				if ((collision_terrain_type == TERRAIN_TYPE_FOREST_TOP1))
				{
	
					//
					// possibly hit forest side.....
					//
				}

				normal = get_3d_terrain_point_data_normal (&raw->ac.terrain_info);
	
				a_n = (-current_flight_dynamics->model_motion_vector.x) * normal->x +
						(-current_flight_dynamics->model_motion_vector.y) * normal->y +
						(-current_flight_dynamics->model_motion_vector.z) * normal->z;
	
				n_n = (normal->x * normal->x) + (normal->y * normal->y) + (normal->z * normal->z);
	
				if (n_n != 0.0)
				{
	
					result.x = (-current_flight_dynamics->model_motion_vector.x) - (a_n / n_n) * normal->x;
					result.y = (-current_flight_dynamics->model_motion_vector.y) - (a_n / n_n) * normal->y;
					result.z = (-current_flight_dynamics->model_motion_vector.z) - (a_n / n_n) * normal->z;
	
					force = get_3d_vector_magnitude (&result);
	
					if (force != 0.0)
					{
	
						vec3d
							position;
	
						multiply_transpose_matrix3x3_vec3d (&result, current_flight_dynamics->attitude, &result);
	
						normalise_3d_vector (&result);
	
						position = current_flight_dynamics->fixed_collision_points [loop].model_point;
	
						position.y = current_flight_dynamics->rotation_origin.y;
	
						add_dynamic_force (force / 20.0, 0.0, &position, &result, FALSE);

						//
						multiply_transpose_matrix3x3_vec3d (&position, raw->ac.mob.attitude, &position);

						position.x += current_flight_dynamics->position.x;
						position.y += current_flight_dynamics->position.y;
						position.z += current_flight_dynamics->position.z;

						create_vectored_debug_3d_object (&position, &result, OBJECT_3D_ARROW_FORCES, 0, 10);
						//
					}
				}
			}
			*/

void dynamics_service_fixed_collision_violations (void)
{
	vec3d
		collision_movement;

	int
		greatest_x_violation_index,
		greatest_y_violation_index,
		greatest_z_violation_index,
		loop;

	float
		greatest_x_violation_distance,
		greatest_y_violation_distance,
		greatest_z_violation_distance;

	if (!get_gunship_entity ())
	{

		return;
	}

	greatest_x_violation_index = -1;
	greatest_y_violation_index = -1;
	greatest_z_violation_index = -1;

	greatest_x_violation_distance = 0.0;
	greatest_y_violation_distance = 0.0;
	greatest_z_violation_distance = 0.0;

	if (fixed_collision_count)
	{

		for (loop = 0; loop < current_flight_dynamics->number_of_fixed_collision_points; loop ++)
		{

			if (current_flight_dynamics->fixed_collision_points [loop].violated)
			{

				//
				// X violation distance
				//

				if (fabs (current_flight_dynamics->fixed_collision_points [loop].violation_distance * current_flight_dynamics->fixed_collision_points [loop].face_normal.x) > fabs (greatest_x_violation_distance))
				{

					greatest_x_violation_distance = current_flight_dynamics->fixed_collision_points [loop].violation_distance * current_flight_dynamics->fixed_collision_points [loop].face_normal.x;
					greatest_x_violation_index = loop;
				}

				//
				// Y violation distance
				//

				if (fabs (current_flight_dynamics->fixed_collision_points [loop].violation_distance * current_flight_dynamics->fixed_collision_points [loop].face_normal.y) > fabs (greatest_y_violation_distance))
				{

					greatest_y_violation_distance = current_flight_dynamics->fixed_collision_points [loop].violation_distance * current_flight_dynamics->fixed_collision_points [loop].face_normal.y;
					greatest_y_violation_index = loop;
				}

				//
				// Z violation distance
				//

				if (fabs (current_flight_dynamics->fixed_collision_points [loop].violation_distance * current_flight_dynamics->fixed_collision_points [loop].face_normal.z) > fabs (greatest_z_violation_distance))
				{

					greatest_z_violation_distance = current_flight_dynamics->fixed_collision_points [loop].violation_distance * current_flight_dynamics->fixed_collision_points [loop].face_normal.z;
					greatest_z_violation_index = loop;
				}
			}
		}

		//
		// move model by greatest violation distance 
		//
	
		collision_movement.x = 0.0;
		collision_movement.y = 0.0;
		collision_movement.z = 0.0;
	
		if (greatest_x_violation_index != -1)
		{
	
			collision_movement.x = greatest_x_violation_distance;
		}
	
		if (greatest_y_violation_index != -1)
		{
	
			collision_movement.y = greatest_y_violation_distance;
		}
	
		if (greatest_z_violation_index != -1)
		{
	
			collision_movement.z = greatest_z_violation_distance;
		}
	
		bound_position_to_map_volume (&collision_movement);
	
		current_flight_dynamics->position.x += collision_movement.x;
		current_flight_dynamics->position.y += collision_movement.y;
		current_flight_dynamics->position.z += collision_movement.z;
	
		//debug_log ("DYNAMICS: fixed collision movement %f, %f, %f", collision_movement.x, collision_movement.y, collision_movement.z);

		if ((get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE)) && (get_current_dynamics_fatal_damage ()))
		{

			entity
				*force,
				*enemy_force;

			//
			// Enter demo mode
			//

			force = get_local_force_entity (get_global_gunship_side ());

			enemy_force = get_local_force_entity (get_enemy_side (get_global_gunship_side ()));

			notify_local_entity (ENTITY_MESSAGE_FORCE_DESTROYED, force, get_gunship_entity (), NULL); 

			notify_local_entity (ENTITY_MESSAGE_FORCE_DESTROYED, enemy_force, get_gunship_entity (), NULL);

			dynamics_kill_model (DYNAMICS_DESTROY_CRASH_LANDED, NULL);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void dynamics_service_moving_collision_violations (void)
{

	vec3d
		collision_movement;

	int
		greatest_x_violation_index,
		greatest_y_violation_index,
		greatest_z_violation_index,
		loop;

	float
		greatest_x_violation_distance,
		greatest_y_violation_distance,
		greatest_z_violation_distance;

	if (!get_gunship_entity ())
	{

		return;
	}

	greatest_x_violation_index = -1;
	greatest_y_violation_index = -1;
	greatest_z_violation_index = -1;

	greatest_x_violation_distance = 0.0;
	greatest_y_violation_distance = 0.0;
	greatest_z_violation_distance = 0.0;

	if (moving_collision_count)
	{

		for (loop = 0; loop < current_flight_dynamics->number_of_moving_collision_points; loop ++)
		{

			if (current_flight_dynamics->moving_collision_points [loop].violated)
			{

				//
				// X violation distance
				//

				if (fabs (current_flight_dynamics->moving_collision_points [loop].violation_distance * current_flight_dynamics->moving_collision_points [loop].face_normal.x) > fabs (greatest_x_violation_distance))
				{

					greatest_x_violation_distance = current_flight_dynamics->moving_collision_points [loop].violation_distance * current_flight_dynamics->moving_collision_points [loop].face_normal.x;
					greatest_x_violation_index = loop;
				}

				//
				// Y violation distance
				//

				if (fabs (current_flight_dynamics->moving_collision_points [loop].violation_distance * current_flight_dynamics->moving_collision_points [loop].face_normal.y) > fabs (greatest_y_violation_distance))
				{

					greatest_y_violation_distance = current_flight_dynamics->moving_collision_points [loop].violation_distance * current_flight_dynamics->moving_collision_points [loop].face_normal.y;
					greatest_y_violation_index = loop;
				}

				//
				// Z violation distance
				//

				if (fabs (current_flight_dynamics->moving_collision_points [loop].violation_distance * current_flight_dynamics->moving_collision_points [loop].face_normal.z) > fabs (greatest_z_violation_distance))
				{

					greatest_z_violation_distance = current_flight_dynamics->moving_collision_points [loop].violation_distance * current_flight_dynamics->moving_collision_points [loop].face_normal.z;
					greatest_z_violation_index = loop;
				}
			}
		}
	}

	//
	// move model by greatest violation distance 
	//

	collision_movement.x = 0.0;
	collision_movement.y = 0.0;
	collision_movement.z = 0.0;

	if (greatest_x_violation_index != -1)
	{

		collision_movement.x = greatest_x_violation_distance;
	}

	if (greatest_y_violation_index != -1)
	{

		collision_movement.y = greatest_y_violation_distance;
	}

	if (greatest_z_violation_index != -1)
	{

		collision_movement.z = greatest_z_violation_distance;
	}

	bound_position_to_map_volume (&collision_movement);

	current_flight_dynamics->position.x += collision_movement.x;
	current_flight_dynamics->position.y += collision_movement.y;
	current_flight_dynamics->position.z += collision_movement.z;

	if (moving_collision_count)
	{

		for (loop = 0; loop < current_flight_dynamics->number_of_moving_collision_points; loop ++)
		{

			if (current_flight_dynamics->moving_collision_points [loop].violated)
			{

				debug_log ("DYNAMICS: moving collision %s", dynamics_collision_point_info [current_flight_dynamics->moving_collision_points [loop].collision_point_type].name);

				// DEBUG-------------------------------------
				// ignore tail hitting carrier if landed....
				if (current_flight_dynamics->moving_collision_points [loop].collision_point_type == DYNAMICS_COLLISION_POINT_TAIL_ROTOR)
				{

					if (!get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AIRBORNE_AIRCRAFT))
					{

						continue;
					}
				}
				//
				// DEBUG-------------------------------------

				dynamics_damage_model (dynamics_collision_point_info [current_flight_dynamics->moving_collision_points [loop].collision_point_type].damage_type, TRUE);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void dynamics_setup_fixed_collision_points (void)
{

	int
		loop;

	if (!get_gunship_entity ())
	{

		return;
	}

	//
	// clear collisions
	//

	for (loop = 0; loop < current_flight_dynamics->number_of_fixed_collision_points; loop ++)
	{

		multiply_matrix3x3_vec3d (&current_flight_dynamics->fixed_collision_points [loop].world_point,
											current_flight_dynamics->attitude,
											&current_flight_dynamics->fixed_collision_points [loop].model_point);

		current_flight_dynamics->fixed_collision_points [loop].world_point.x += current_flight_dynamics->position.x;
		current_flight_dynamics->fixed_collision_points [loop].world_point.y += current_flight_dynamics->position.y;
		current_flight_dynamics->fixed_collision_points [loop].world_point.z += current_flight_dynamics->position.z;

		// temp for undercarriage... lower collision points
		switch (get_global_gunship_type ())
		{
			
			case GUNSHIP_TYPE_COMANCHE:
			{

				current_flight_dynamics->fixed_collision_points [loop].world_point.y -= 0.48 * get_current_flight_dynamics_undercarriage_state ();

				break;
			}
			case GUNSHIP_TYPE_HOKUM:
			{

				current_flight_dynamics->fixed_collision_points [loop].world_point.y -= 0.69 * get_current_flight_dynamics_undercarriage_state ();

				break;
			}
			case GUNSHIP_TYPE_APACHE:
			{

				//current_flight_dynamics->fixed_collision_points [loop].world_point.y -= 0.48 * get_current_flight_dynamics_undercarriage_state ();

				break;
			}
			case GUNSHIP_TYPE_HAVOC:
			{

				//current_flight_dynamics->fixed_collision_points [loop].world_point.y -= 0.20 * get_current_flight_dynamics_undercarriage_state ();

				break;
			}
			default:
			{

				break;
			}
		}
		//

		bound_position_to_map_area (&current_flight_dynamics->fixed_collision_points [loop].world_point);

		current_flight_dynamics->fixed_collision_points [loop].violated = FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void dynamics_setup_moving_collision_points (void)
{

	int
		loop;

	if (!get_gunship_entity ())
	{

		return;
	}

	//
	// setup moving collision points (after fixed have been done so thay are rotated into correct position)
	//

	for (loop = 0; loop < current_flight_dynamics->number_of_moving_collision_points; loop ++)
	{

		multiply_matrix3x3_vec3d (&current_flight_dynamics->moving_collision_points [loop].world_point,
											current_flight_dynamics->attitude,
											&current_flight_dynamics->moving_collision_points [loop].model_point);

		current_flight_dynamics->moving_collision_points [loop].world_point.x += current_flight_dynamics->position.x;
		current_flight_dynamics->moving_collision_points [loop].world_point.y += current_flight_dynamics->position.y;
		current_flight_dynamics->moving_collision_points [loop].world_point.z += current_flight_dynamics->position.z;

		bound_position_to_map_area (&current_flight_dynamics->moving_collision_points [loop].world_point);

		current_flight_dynamics->moving_collision_points [loop].violated = FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_radius_collision_tree (vec3d *position, float model_radius, int ignore_forest_edge_trees, vec3d *collision_vector, vec3d *face_normal)
{

	int
		num_trees,
		x_sector,
		z_sector;

	float
		tree_radius,
		sqr_range,
		height,
		x_sector_mid_point,
		z_sector_mid_point;

	terrain_3d_tree_data
		*tree;

	vec3d
		vector,
		tree_position;

	tree_radius = 5.0,

	get_terrain_3d_sector (position->x, position->z, &x_sector, &z_sector);

	num_trees = get_terrain_3d_tree_sector_data (x_sector, z_sector, &tree);

	x_sector_mid_point = (x_sector * TERRAIN_3D_SECTOR_SIDE_LENGTH) + (TERRAIN_3D_SECTOR_SIDE_LENGTH * 0.5);
	z_sector_mid_point = (z_sector * TERRAIN_3D_SECTOR_SIDE_LENGTH) + (TERRAIN_3D_SECTOR_SIDE_LENGTH * 0.5);

	while (num_trees)
	{

		height = get_terrain_3d_tree_scale (tree) * 0.75;

		if (current_flight_dynamics->radar_altitude.value < height)
		{

			if (!(ignore_forest_edge_trees && (tree->type == 0)))
			{
	
				tree_position.x = x_sector_mid_point + (tree->x * TERRAIN_3D_XZ_SCALE * 0.5);
				tree_position.y = (tree->y * terrain_3d_map_scaled_height_difference * 0.5) + terrain_3d_map_minimum_height;
				tree_position.z = z_sector_mid_point + (tree->z * TERRAIN_3D_XZ_SCALE * 0.5);
	
				sqr_range = get_sqr_2d_range (position, &tree_position);

				if (sqr_range < ((tree_radius + model_radius) * (tree_radius + model_radius)))
				{

					vector.x = tree_position.x - position->x;
					vector.y = tree_position.y - position->y;
					vector.z = tree_position.z - position->z;

					normalise_any_3d_vector (&vector);

					face_normal->x = vector.x;
					face_normal->y = vector.y;
					face_normal->z = vector.z;

					vector.x *= tree_radius;
					vector.y *= tree_radius;
					vector.z *= tree_radius;

					collision_vector->x = (tree_position.x - position->x) - vector.x;
					collision_vector->y = (tree_position.y - position->y) - vector.y;
					collision_vector->z = (tree_position.z - position->z) - vector.z;

					debug_log ("DYNAMICS: possible tree collision %f, %f, %f", collision_vector->x, collision_vector->y, collision_vector->z);

					return TRUE;
				}
			}
		}

		tree ++;

		num_trees --;
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
