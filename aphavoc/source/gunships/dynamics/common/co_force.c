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

#include "co_undercarriage.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	fixed_collision_count,
	moving_collision_count,
	collision_detected;
static int
	water_damage = 0;
float
	max_fixed_damage[32];

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

static void update_tree_collision_dynamics (void);

static int get_radius_collision_tree (vec3d *position, float model_radius, int ignore_forest_edge_trees, vec3d *collision_vector, vec3d *face_normal);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

dynamics_collision_point_type
	dynamics_collision_point_info [] =
	{
  		{
			"DYNAMICS_COLLISION_POINT_MAIN_ROTOR", // always first!
			OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_COLLISION_POINT,
			TRUE,
			(dynamics_damage_types) (DYNAMICS_DAMAGE_MAIN_ROTOR_BLADE),
		},
		{
			"DYNAMICS_COLLISION_POINT_TAIL_ROTOR",
			OBJECT_3D_SUB_OBJECT_TAIL_ROTOR_COLLISION_POINT,
			TRUE,
			(dynamics_damage_types) (DYNAMICS_DAMAGE_TAIL_ROTOR),
		},
		{
			"DYNAMICS_COLLISION_POINT_STABILISER",
			OBJECT_3D_SUB_OBJECT_STABILISER_COLLISION_POINT,
			FALSE,
			(dynamics_damage_types) (DYNAMICS_DAMAGE_STABILISER),
		},
		{
			"DYNAMICS_COLLISION_POINT_FUSELAGE",
			OBJECT_3D_SUB_OBJECT_FUSELAGE_COLLISION_POINT,
			FALSE,
			(dynamics_damage_types) (DYNAMICS_DAMAGE_FUEL_LEAK | DYNAMICS_DAMAGE_LOW_HYDRAULICS | DYNAMICS_DAMAGE_LEFT_ENGINE_FIRE | DYNAMICS_DAMAGE_LEFT_ENGINE | DYNAMICS_DAMAGE_APU |
					DYNAMICS_DAMAGE_SECONDARY_HYDRAULICS | DYNAMICS_DAMAGE_RIGHT_ENGINE_FIRE | DYNAMICS_DAMAGE_RIGHT_ENGINE | DYNAMICS_DAMAGE_LOW_OIL_PRESSURE | DYNAMICS_DAMAGE_HIGH_OIL_PRESSURE |
						DYNAMICS_DAMAGE_AVIONICS | DYNAMICS_DAMAGE_UNDERCARRIAGE),
		},
		{
			"DYNAMICS_COLLISION_POINT_ENGINE",
			OBJECT_3D_SUB_OBJECT_ENGINE_COLLISION_POINT,
			FALSE,
			(dynamics_damage_types) (DYNAMICS_DAMAGE_LEFT_ENGINE | DYNAMICS_DAMAGE_LEFT_ENGINE_FIRE | DYNAMICS_DAMAGE_RIGHT_ENGINE | DYNAMICS_DAMAGE_RIGHT_ENGINE_FIRE |
					DYNAMICS_DAMAGE_HIGH_OIL_PRESSURE | DYNAMICS_DAMAGE_LOW_OIL_PRESSURE | DYNAMICS_DAMAGE_APU),
		},
		{
			"DYNAMICS_COLLISION_POINT_NOSE_GUN",
			OBJECT_3D_SUB_OBJECT_NOSE_GUN_COLLISION_POINT,
			FALSE,
			DYNAMICS_DAMAGE_NONE,
		},
		{
			"DYNAMICS_COLLISION_POINT_AVIONICS",
			OBJECT_3D_SUB_OBJECT_AVIONICS_COLLISION_POINT,
			FALSE,
			(dynamics_damage_types) (DYNAMICS_DAMAGE_AVIONICS),
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
			(dynamics_damage_types) (DYNAMICS_DAMAGE_LOW_HYDRAULICS | DYNAMICS_DAMAGE_LEFT_ENGINE_FIRE | DYNAMICS_DAMAGE_RIGHT_ENGINE_FIRE | DYNAMICS_DAMAGE_LOW_OIL_PRESSURE),
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

void add_dynamic_force (const char *name, float force, float duration, vec3d *position, vec3d *direction, int debug)
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

			#if DEBUG_MODULE

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
			#endif

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

				#if DEBUG_MODULE > 1

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

	if(!get_gunship_entity() || !current_flight_dynamics)
		return;

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
	//{

		current_flight_dynamics->angular_heading_acceleration.value = resultant_y_axis;

		current_flight_dynamics->angular_heading_velocity.value -= current_flight_dynamics->angular_heading_acceleration.value * get_model_delta_time ();

		current_flight_dynamics->heading.delta = current_flight_dynamics->angular_heading_velocity.value * get_model_delta_time ();
	//}

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
	
		switch (current_flight_dynamics->auto_hover)
		{
			case HOVER_HOLD_NORMAL:
			case HOVER_HOLD_STABLE:
			{

				float			//  PID hover control loop added by Javelin 5/18
					alt_error_1,
					der_error,
					PID_output,
					Bias= 90,	//  Bias the center of the PID output
					Kp = 3.0,	//  PID loop Proportional constant  
					Kd = 7.0;	//  PID loop Derivative constant,  (handles up to about a 100m height correction smoothly)
								//  the Ki Integral term is not being used
				static float
					alt_error_0 = 0.0;

				const float
					output_min = 55,	//  Limit the throttle adjustment range to 85% +- 30
					output_max = 120;	//  Extra lift is needed for moving upwards because of gravity

							//                                                altitude.max = target net altitude
			alt_error_1 = (current_flight_dynamics->radar_altitude.value) - current_flight_dynamics->altitude.max;

			der_error = (alt_error_1 - alt_error_0)/get_model_delta_time();

			PID_output = Bias -(Kp * alt_error_1) -(Kd * der_error);

//debug_log ("HOVER:  Altitude: %f Setting: %f PID_out: %f", current_flight_dynamics->altitude.value - current_flight_dynamics->altitude.min, current_flight_dynamics->altitude.max, PID_output);

			PID_output = bound (PID_output, output_min, output_max);

		current_flight_dynamics->input_data.collective.value = PID_output;	//  set the collective-throttle

			alt_error_0 = alt_error_1;  //  save the current altitude error for the next round


				// wash velocity out to zero
				// level out helicopter
				// level out pitch/yaw

				current_flight_dynamics->input_data.cyclic_x.value = bound(-current_flight_dynamics->roll.value / rad(10.0) * 100.0, current_flight_dynamics->input_data.cyclic_x.min, current_flight_dynamics->input_data.cyclic_x.max);
				current_flight_dynamics->input_data.cyclic_y.value = bound((current_flight_dynamics->pitch.value - rad(5.0))/ rad(10.0) * 100.0, current_flight_dynamics->input_data.cyclic_y.min, current_flight_dynamics->input_data.cyclic_y.max);

				current_flight_dynamics->model_acceleration_vector.x = -(10.0 * get_model_delta_time ()) * current_flight_dynamics->model_motion_vector.x;
				current_flight_dynamics->model_acceleration_vector.y = resultant_vertically;
				current_flight_dynamics->model_acceleration_vector.z = -(10.0 * get_model_delta_time ()) * current_flight_dynamics->model_motion_vector.z;

				break;
			}

			case HOVER_HOLD_ALTITUDE_LOCK:
			{

				float			   //  PID hover control loop added by Javelin 5/18
					alt_error_1,
					der_error,
					PID_output,
					Bias= 90,	   //  Bias the center of the PID output
					ABias = -3.0,  //  Angle Bias (in % joystick throw) Nose-Up
					Kp = 6.0,	   //  PID loop Proportional constant  
					Kd = 10.0,	   //  PID loop Derivative constant,  (handles up to about a 100m height correction smoothly)
								   //  the Ki Integral term is not being used
					Angl_output,
					Ka = 1.2,      //  Nose Angle adjustment constant
					AAA,
					look_ahead_distance;

				vec3d
					look_ahead_position;

				static float
					alt_error_0 = 0.0;

				const float
					output_min = 55,	//  Limit the throttle adjustment range to 85% +- 30
					output_max = 120;	//  Extra lift is needed for moving upwards to counter gravity

				
			alt_error_1 = (current_flight_dynamics->radar_altitude.value) - current_flight_dynamics->altitude.max;

			der_error = (alt_error_1 - alt_error_0)/get_model_delta_time();

			PID_output = Bias -(Kp * alt_error_1) -(Kd * der_error);

			PID_output = bound (PID_output, output_min, output_max);

		current_flight_dynamics->input_data.collective.value = PID_output;	//  set the collective-throttle

			alt_error_0 = alt_error_1;  //  save the current altitude error for the next round

			//  Speed control & Nose Angle Control only if below 100 meters
			if (current_flight_dynamics->altitude.value - current_flight_dynamics->altitude.min < 100)
			{
				AAA = knots(current_flight_dynamics->velocity_z.value);
				if (AAA > 100) 
				{	AAA = (AAA - 100)/125.0 *60.0;  //  Kick up the nose if over 100 knots to slow the helo down (speed control)
					ABias = -3 -AAA;
				}
				else if (AAA<55)
				{   AAA = (55-AAA)/125.0 *35.0;		//   Push the nose down if under 55 knots to speed it up
					ABias = -3 +AAA;
				}
				else
					ABias = -3;  //  Approximately Level Flight 
			
			////////////////////////////////  Original Razorworks Code  ////////////////////////////////////////////////////////

				look_ahead_distance = 5.0 * current_flight_dynamics->velocity_z.value;  //  5 seconds straight ahead

				look_ahead_position.x = current_flight_dynamics->position.x;
				look_ahead_position.y = current_flight_dynamics->position.y;
				look_ahead_position.z = current_flight_dynamics->position.z;

				look_ahead_position.x += current_flight_dynamics->attitude [2][0] * look_ahead_distance;
				look_ahead_position.z += current_flight_dynamics->attitude [2][2] * look_ahead_distance;

				ASSERT(point_inside_map_area(&look_ahead_position));
	
				look_ahead_position.y = get_3d_terrain_elevation (look_ahead_position.x, look_ahead_position.z);

//debug_log ("HOVER: Ground Altitude: %f   1-sec-ahead: %f", current_flight_dynamics->altitude.min, look_ahead_position.y);  
		
			////////////////////////////////  End Original Razorworks Code  ////////////////////////////////////////////////////

				//  Next, Kick the nose up or down to follow the slope of the ground, looking ahead

				alt_error_1 = (current_flight_dynamics->altitude.value - look_ahead_position.y) - current_flight_dynamics->altitude.max;  
			
				Angl_output = (Ka * alt_error_1)/5.0 + ABias;   //  Must be balanced against the # of seconds look ahead
				
				Angl_output = bound (Angl_output, -55, 15);  //   limit the cyclic correction angle: Allow more nose up(-) than down

		current_flight_dynamics->input_data.cyclic_y_trim.value = Angl_output;   //  Set the Collective pitch angle
				//  Trim is being used so the pilot can still over-ride the automated controls
			}

				current_flight_dynamics->model_acceleration_vector.x = resultant_laterally;
				current_flight_dynamics->model_acceleration_vector.y = resultant_vertically;
				current_flight_dynamics->model_acceleration_vector.z = resultant_horizontally;

//debug_log ("HOVER: Altitude: %f Setting: %f PID_out: %f Angl_out: %f", current_flight_dynamics->altitude.value - current_flight_dynamics->altitude.min, current_flight_dynamics->altitude.max, PID_output, Angl_output);
				break;
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

	if(!get_gunship_entity() || !current_flight_dynamics)
		return;

	if (get_in_flight_game_mode () != IN_FLIGHT_GAME_MODE_SIMULATOR)
	{
		return;
	}

	old_position.x = current_flight_dynamics->position.x - (current_flight_dynamics->world_motion_vector.x * get_model_delta_time ());
	old_position.y = current_flight_dynamics->position.y - (current_flight_dynamics->world_motion_vector.y * get_model_delta_time ());
	old_position.z = current_flight_dynamics->position.z - (current_flight_dynamics->world_motion_vector.z * get_model_delta_time ());

	get_local_entity_attitude_matrix (get_gunship_entity (), attitude);

	for (index = 0; index < current_flight_dynamics->max_number_of_dynamic_forces; index ++)
	{

		if (current_flight_dynamics->dynamic_forces [index].valid)
		{

			multiply_matrix3x3_vec3d (&pos, attitude, &current_flight_dynamics->dynamic_forces [index].position);

			multiply_matrix3x3_vec3d (&direction, attitude, &current_flight_dynamics->dynamic_forces [index].direction);

			pos.x += current_flight_dynamics->position.x;
			pos.y += current_flight_dynamics->position.y;
			pos.z += current_flight_dynamics->position.z;

			size = bound ((current_flight_dynamics->dynamic_forces [index].duration ? 1000 : 1) * current_flight_dynamics->dynamic_forces [index].linear_force, -4.0, 4.0);

			create_vectored_debug_3d_object (&pos, &direction, OBJECT_3D_ARROW_FORCES, current_flight_dynamics->dynamic_forces [index].duration, size);
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
#if DEBUG_MODULE
	debug_log ("DYNAMICS: weapon launch force %f (range %f), duration %f, position %f, %f, %f, direction %f, %f, %f",
			force, get_3d_vector_magnitude (launch_position), duration, launch_position->x, launch_position->y, launch_position->z, launch_direction->x, launch_direction->y, launch_direction->z);
#endif

	add_dynamic_force ("Weapon launch force", force * get_model_delta_time(), duration, launch_position, launch_direction, TRUE);
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

void update_collision_dynamics (void)
{

	int
		loop,
		emergency_landing = FALSE;

	helicopter
		*raw;

	if(!get_gunship_entity() || !current_flight_dynamics)
		return;
	raw = (helicopter *) get_local_entity_data (get_gunship_entity ());

	fixed_collision_count = 0;

	moving_collision_count = 0;
	
	collision_detected = 0;

	///////////////////////////////////////////////////////////////////
	//
	// check for collision
	//
	///////////////////////////////////////////////////////////////////

	initialise_flight_dynamics_collision_points(TRUE);

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

	if(!get_gunship_entity() || !current_flight_dynamics)
		return;

	if ((get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE)) && (get_current_dynamics_fatal_damage ()))
	{

		entity
			*force,
			*enemy_force;

		//
		// Enter demo mode
		//

		debug_log("fatal damage");

		force = get_local_force_entity (get_global_gunship_side ());

		enemy_force = get_local_force_entity (get_enemy_side (get_global_gunship_side ()));

		notify_local_entity (ENTITY_MESSAGE_FORCE_DESTROYED, force, get_gunship_entity (), NULL);

		notify_local_entity (ENTITY_MESSAGE_FORCE_DESTROYED, enemy_force, get_gunship_entity (), NULL);

		if (!water_damage)
			dynamics_kill_model (DYNAMICS_DESTROY_CRASH_LANDED, NULL);
		else
			dynamics_kill_model (DYNAMICS_DESTROY_WATER_CRASH, NULL);
		
		return;
	}	

	///////////////////////////////////////////////////////////////////
	//
	// store this frames collision points with new position
	//
	///////////////////////////////////////////////////////////////////

	if (collision_detected)
	{
		current_flight_dynamics->world_motion_vector.x = current_flight_dynamics->world_motion_vector.y = current_flight_dynamics->world_motion_vector.z = 0.0;
		current_flight_dynamics->model_acceleration_vector.x = current_flight_dynamics->model_acceleration_vector.y = current_flight_dynamics->model_acceleration_vector.z = 0.0;
	}

	memcpy (current_flight_dynamics->last_frame_fixed_collision_points, current_flight_dynamics->fixed_collision_points, sizeof (dynamics_collision_type) * current_flight_dynamics->number_of_fixed_collision_points);
	current_flight_dynamics->valid_last_frame_fixed_collision_points = TRUE;

	memcpy (current_flight_dynamics->last_frame_moving_collision_points, current_flight_dynamics->moving_collision_points, sizeof (dynamics_collision_type) * current_flight_dynamics->number_of_moving_collision_points);

	for (loop = 0; loop < current_flight_dynamics->number_of_moving_collision_points; loop ++)
		if(current_flight_dynamics->moving_collision_points [loop].collision_point_type == DYNAMICS_COLLISION_POINT_MAIN_ROTOR)
		{
			current_flight_dynamics->last_frame_moving_collision_points [loop].world_point.x = current_flight_dynamics->position.x;
			current_flight_dynamics->last_frame_moving_collision_points [loop].world_point.y = current_flight_dynamics->position.y;
			current_flight_dynamics->last_frame_moving_collision_points [loop].world_point.z = current_flight_dynamics->position.z;
		}

	current_flight_dynamics->valid_last_frame_moving_collision_points = TRUE;

	///////////////////////////////////////////////////////////////////
	//
	// landing stuff
	//
	///////////////////////////////////////////////////////////////////

	if (current_flight_dynamics->main_rotor_rpm.value <= 50)
		for (loop = 0; loop < current_flight_dynamics->number_of_fixed_collision_points; loop ++)
			if(current_flight_dynamics->fixed_collision_points [loop].terrain_elevation < 0.1)
				emergency_landing = TRUE;

	if (!get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AIRBORNE_AIRCRAFT) && !(weight_on_wheels() || emergency_landing))
		dynamics_takeoff ();
	else if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AIRBORNE_AIRCRAFT) && (weight_on_wheels() || emergency_landing)) // TO DO - make fixed_collision_count works stable
		dynamics_land ();

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

	if(!get_gunship_entity() || !current_flight_dynamics)
		return;

	raw = (helicopter *) get_local_entity_data (get_gunship_entity ());

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

//						if ((get_local_entity_int_value (object, INT_TYPE_OBJECT_3D_SHAPE) != OBJECT_3D_FARP_MAT) &&
//							(get_local_entity_int_value (object, INT_TYPE_OBJECT_3D_SHAPE) != OBJECT_3D_FARP_MAT_GREY))
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
						
						collision_detected = TRUE;

						vec.x = current_flight_dynamics->fixed_collision_points [loop].world_point.x - current_flight_dynamics->fixed_collision_points [loop].collision_point.x;
						vec.y = current_flight_dynamics->fixed_collision_points [loop].world_point.y - current_flight_dynamics->fixed_collision_points [loop].collision_point.y;
						vec.z = current_flight_dynamics->fixed_collision_points [loop].world_point.z - current_flight_dynamics->fixed_collision_points [loop].collision_point.z;

						current_flight_dynamics->fixed_collision_points [loop].violation_distance = get_3d_vector_magnitude (&vec) + 0.02;
						current_flight_dynamics->fixed_collision_points [loop].surface_type = DYNAMICS_COLLISION_SURFACE_OBJECT;

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

					vec.x = current_flight_dynamics->moving_collision_points [loop].world_point.x - current_flight_dynamics->moving_collision_points [loop].collision_point.x;
					vec.y = current_flight_dynamics->moving_collision_points [loop].world_point.y - current_flight_dynamics->moving_collision_points [loop].collision_point.y;
					vec.z = current_flight_dynamics->moving_collision_points [loop].world_point.z - current_flight_dynamics->moving_collision_points [loop].collision_point.z;

					current_flight_dynamics->moving_collision_points [loop].violation_distance = get_3d_vector_magnitude (&vec) + 0.02;
					current_flight_dynamics->moving_collision_points [loop].surface_type = DYNAMICS_COLLISION_SURFACE_OBJECT;

					#if 0

					debug_log ("DYNAMICS: possible object %s collision", get_local_entity_type_name (collision_en));

					debug_log ("DYNAMICS: violation dist %f, start %f, %f, %f, stop %f, %f, %f, collision %f, %f, %f, normal %f, %f, %f",
									current_flight_dynamics->moving_collision_points [loop].violation_distance,
									current_flight_dynamics->moving_collision_points [loop].world_point.x,
									current_flight_dynamics->moving_collision_points [loop].world_point.y,
									current_flight_dynamics->moving_collision_points [loop].world_point.z,
									current_flight_dynamics->last_frame_moving_collision_points [loop].world_point.x,
									current_flight_dynamics->last_frame_fixed_collision_points [loop].world_point.y,
									current_flight_dynamics->last_frame_fixed_collision_points [loop].world_point.z,
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

	if(!get_gunship_entity() || !current_flight_dynamics)
		return;

	raw = (helicopter *) get_local_entity_data (get_gunship_entity ());

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
					
					collision_detected = TRUE;

					vec.x = current_flight_dynamics->fixed_collision_points [loop].world_point.x - current_flight_dynamics->fixed_collision_points [loop].collision_point.x;
					vec.y = current_flight_dynamics->fixed_collision_points [loop].world_point.y - current_flight_dynamics->fixed_collision_points [loop].collision_point.y;
					vec.z = current_flight_dynamics->fixed_collision_points [loop].world_point.z - current_flight_dynamics->fixed_collision_points [loop].collision_point.z;

					current_flight_dynamics->fixed_collision_points [loop].collision_point.x = current_flight_dynamics->fixed_collision_points [loop].world_point.x;
					current_flight_dynamics->fixed_collision_points [loop].collision_point.y = current_flight_dynamics->fixed_collision_points [loop].world_point.y;
					current_flight_dynamics->fixed_collision_points [loop].collision_point.z = current_flight_dynamics->fixed_collision_points [loop].world_point.z;

					current_flight_dynamics->fixed_collision_points [loop].violation_distance = get_3d_vector_magnitude (&collision_vector);
					current_flight_dynamics->fixed_collision_points [loop].surface_type = DYNAMICS_COLLISION_SURFACE_TREE;

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

					vec.x = current_flight_dynamics->moving_collision_points [loop].world_point.x - current_flight_dynamics->moving_collision_points [loop].collision_point.x;
					vec.y = current_flight_dynamics->moving_collision_points [loop].world_point.y - current_flight_dynamics->moving_collision_points [loop].collision_point.y;
					vec.z = current_flight_dynamics->moving_collision_points [loop].world_point.z - current_flight_dynamics->moving_collision_points [loop].collision_point.z;

					current_flight_dynamics->moving_collision_points [loop].collision_point.x = current_flight_dynamics->moving_collision_points [loop].world_point.x;
					current_flight_dynamics->moving_collision_points [loop].collision_point.y = current_flight_dynamics->moving_collision_points [loop].world_point.y;
					current_flight_dynamics->moving_collision_points [loop].collision_point.z = current_flight_dynamics->moving_collision_points [loop].world_point.z;

					current_flight_dynamics->moving_collision_points [loop].violation_distance = get_3d_vector_magnitude (&collision_vector);
					current_flight_dynamics->moving_collision_points [loop].surface_type = DYNAMICS_COLLISION_SURFACE_TREE;

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
	int
		loop;

	if(!get_gunship_entity() || !current_flight_dynamics)
		return;

	raw = (helicopter *) get_local_entity_data (get_gunship_entity ());

	//
	// Check FIXED collision points with GROUND
	//

	for (loop = 0; loop < current_flight_dynamics->number_of_fixed_collision_points; loop ++)
		if (current_flight_dynamics->fixed_collision_points [loop].collision_point_type != DYNAMICS_COLLISION_POINT_WHEEL) // we have suspension dynamics for this
		{
			get_3d_terrain_point_data (current_flight_dynamics->fixed_collision_points [loop].world_point.x, current_flight_dynamics->fixed_collision_points [loop].world_point.z, &raw->ac.terrain_info);

			current_flight_dynamics->fixed_collision_points [loop].terrain_elevation = get_3d_terrain_point_data_elevation (&raw->ac.terrain_info);

			if (current_flight_dynamics->fixed_collision_points [loop].terrain_elevation > current_flight_dynamics->fixed_collision_points [loop].world_point.y)
			{
				int soil = get_terrain_type_class (get_3d_terrain_point_data_type (&raw->ac.terrain_info)) == TERRAIN_CLASS_LAND || get_terrain_type_class (get_3d_terrain_point_data_type (&raw->ac.terrain_info)) == TERRAIN_CLASS_FOREST;
				
				fixed_collision_count ++;

				if (soil)
				{
					current_flight_dynamics->fixed_collision_points [loop].violation_distance = fabs (current_flight_dynamics->fixed_collision_points [loop].terrain_elevation - current_flight_dynamics->fixed_collision_points [loop].world_point.y);
					current_flight_dynamics->fixed_collision_points [loop].surface_type = DYNAMICS_COLLISION_SURFACE_GROUND;
				}
				else
				{
					current_flight_dynamics->fixed_collision_points [loop].violation_distance = 0;
					current_flight_dynamics->fixed_collision_points [loop].surface_type = DYNAMICS_COLLISION_SURFACE_WATER;
				}

				current_flight_dynamics->fixed_collision_points [loop].violated = TRUE;

				collision_detected = current_flight_dynamics->fixed_collision_points [loop].violation_distance != 0;

				memcpy (&current_flight_dynamics->fixed_collision_points [loop].face_normal, get_3d_terrain_point_data_normal (&raw->ac.terrain_info), sizeof (vec3d));

				current_flight_dynamics->fixed_collision_points [loop].collision_point = current_flight_dynamics->fixed_collision_points [loop].world_point;
				current_flight_dynamics->fixed_collision_points [loop].collision_point.y = current_flight_dynamics->fixed_collision_points [loop].terrain_elevation;
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

	if(!get_gunship_entity() || !current_flight_dynamics)
		return;

	raw = (helicopter *) get_local_entity_data (get_gunship_entity ());

	//
	// Check MOVING collision points with GROUND
	//

	for (loop = 0; loop < current_flight_dynamics->number_of_moving_collision_points; loop ++)
	{

		get_3d_terrain_point_data (current_flight_dynamics->moving_collision_points [loop].world_point.x, current_flight_dynamics->moving_collision_points [loop].world_point.z, &raw->ac.terrain_info);

		current_flight_dynamics->moving_collision_points [loop].terrain_elevation = get_3d_terrain_point_data_elevation (&raw->ac.terrain_info);

		if ((current_flight_dynamics->moving_collision_points [loop].terrain_elevation) > current_flight_dynamics->moving_collision_points [loop].world_point.y)
		{
			int soil = get_terrain_type_class (get_3d_terrain_point_data_type (&raw->ac.terrain_info)) == TERRAIN_CLASS_LAND || get_terrain_type_class (get_3d_terrain_point_data_type (&raw->ac.terrain_info)) == TERRAIN_CLASS_FOREST;

			moving_collision_count ++;

			current_flight_dynamics->moving_collision_points [loop].violation_distance = fabs (current_flight_dynamics->moving_collision_points [loop].terrain_elevation - current_flight_dynamics->moving_collision_points [loop].world_point.y);

			if (soil)
				current_flight_dynamics->moving_collision_points [loop].surface_type = DYNAMICS_COLLISION_SURFACE_GROUND;
			else
				current_flight_dynamics->moving_collision_points [loop].surface_type = DYNAMICS_COLLISION_SURFACE_WATER;

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

void dynamics_service_fixed_collision_violations (void)
{
	vec3d
		collision_movement;

	int
		greatest_x_violation_index,
		greatest_y_violation_index,
		greatest_z_violation_index,
		loop,
		i;

	float
		greatest_x_violation_distance,
		greatest_y_violation_distance,
		greatest_z_violation_distance,
		f,
		violation_min_level = (float) get_local_entity_int_value (get_local_entity_first_child (get_gunship_entity (), LIST_TYPE_AIRCREW), INT_TYPE_DIFFICULTY_LEVEL) * 2 * get_model_delta_time();

	if(!get_gunship_entity() || !current_flight_dynamics)
		return;

	greatest_x_violation_index = -1;
	greatest_y_violation_index = -1;
	greatest_z_violation_index = -1;

	greatest_x_violation_distance = 0.0;
	greatest_y_violation_distance = 0.0;
	greatest_z_violation_distance = 0.0;

	for (i = 0; i < NUM_DYNAMICS_COLLISION_POINT_TYPES; i++)
		max_fixed_damage[i] = max (violation_min_level, max_fixed_damage[i] - get_model_delta_time() / 30);

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
				
				//
				// Fixed collisions damage
				//
				
				current_flight_dynamics->fixed_collision_points [loop].violation_distance *= get_3d_vector_magnitude (&current_flight_dynamics->world_motion_vector) / 10;
				
				if (current_flight_dynamics->fixed_collision_points [loop].collision_point_type == DYNAMICS_COLLISION_POINT_ENGINE && !current_flight_dynamics->fixed_collision_points [loop].violation_distance) // water damage
				{
					dynamics_damage_model (dynamics_collision_point_info [DYNAMICS_COLLISION_POINT_ENGINE].damage_type, TRUE);
					water_damage = TRUE;
					debug_log ("DYNAMICS: water damage %s", dynamics_collision_point_info [current_flight_dynamics->fixed_collision_points [loop].collision_point_type].name);
				}
				else if (!current_flight_dynamics->fixed_collision_points [loop].violation_distance) // water damage
				{
					if (frand1() < (get_model_delta_time() / ((get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_AIRCRAFT_CH47D_CHINOOK || 
							get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_AIRCRAFT_CH53E_SUPER_STALLION) ? 1000 : 10)))
					{
						dynamics_damage_model (dynamics_collision_point_info [current_flight_dynamics->fixed_collision_points [loop].collision_point_type].damage_type, TRUE);
						water_damage = TRUE;
						debug_log ("DYNAMICS: water damage %s", dynamics_collision_point_info [current_flight_dynamics->fixed_collision_points [loop].collision_point_type].name);
					}
				}
				else if (current_flight_dynamics->fixed_collision_points [loop].violation_distance >= max_fixed_damage[current_flight_dynamics->fixed_collision_points [loop].collision_point_type])
				{
					int power;
					
					if (current_flight_dynamics->fixed_collision_points [loop].collision_point_type == DYNAMICS_COLLISION_POINT_STABILISER ||
							current_flight_dynamics->fixed_collision_points [loop].collision_point_type == DYNAMICS_COLLISION_POINT_AVIONICS)
						dynamics_damage_model (dynamics_collision_point_info [current_flight_dynamics->fixed_collision_points [loop].collision_point_type].damage_type, FALSE);
					else
						dynamics_damage_model (dynamics_collision_point_info [current_flight_dynamics->fixed_collision_points [loop].collision_point_type].damage_type, TRUE);

					f = current_flight_dynamics->fixed_collision_points [loop].violation_distance;

					while (f >= violation_min_level + max_fixed_damage[current_flight_dynamics->fixed_collision_points [loop].collision_point_type]) // additional damage if collision too hard
					{
						dynamics_damage_model (dynamics_collision_point_info [DYNAMICS_COLLISION_POINT_FUSELAGE].damage_type, TRUE);
						f -= violation_min_level;
					}
					
					water_damage = FALSE;
					max_fixed_damage[current_flight_dynamics->fixed_collision_points [loop].collision_point_type] = current_flight_dynamics->fixed_collision_points [loop].violation_distance;
					
					// effects 
					
					if (get_comms_model () == COMMS_MODEL_SERVER)
					{
						power = (int) (bound(current_flight_dynamics->fixed_collision_points [loop].violation_distance / 0.1, 0, 2));
						create_client_server_collision_effect (&current_flight_dynamics->fixed_collision_points [loop].world_point, current_flight_dynamics->fixed_collision_points [loop].surface_type, power);
					}
					
					debug_log ("DYNAMICS: fixed collision %s violation distance %f, min level %f", dynamics_collision_point_info [current_flight_dynamics->fixed_collision_points [loop].collision_point_type].name, current_flight_dynamics->fixed_collision_points [loop].violation_distance, violation_min_level + max_fixed_damage[current_flight_dynamics->fixed_collision_points [loop].collision_point_type]);
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
		
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void dynamics_service_moving_collision_violations (void)
{
	int
		loop;

	if(!get_gunship_entity() || !current_flight_dynamics)
		return;

	if (moving_collision_count)
		for (loop = 0; loop < current_flight_dynamics->number_of_moving_collision_points; loop ++)
			if (current_flight_dynamics->moving_collision_points [loop].violated)
			{
				float point_velocity;
				vec3d dummy;
				
				moving_collision_points_counter (loop);	
				dynamics_damage_model (dynamics_collision_point_info [current_flight_dynamics->moving_collision_points [loop].collision_point_type].damage_type, FALSE);
			
				// effects 

				point_velocity = get_point_to_point_distance(&dummy, &current_flight_dynamics->moving_collision_points [loop].world_point, &current_flight_dynamics->last_frame_moving_collision_points [loop].world_point) / get_delta_time();

				if (get_comms_model () == COMMS_MODEL_SERVER && !current_flight_dynamics->last_frame_moving_collision_points [loop].violated && point_velocity > 150.0)
					create_client_server_collision_effect (&current_flight_dynamics->moving_collision_points [loop].world_point, current_flight_dynamics->moving_collision_points [loop].surface_type, 1);
			}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void dynamics_setup_fixed_collision_points (void)
{

	int
		loop;

	if(!get_gunship_entity() || !current_flight_dynamics)
		return;

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

	if(!get_gunship_entity() || !current_flight_dynamics)
		return;

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
