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

static dynamics_type
	vector_flight_dynamics;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_vector_main_rotor_dynamics (void);

static void update_vector_tail_rotor_dynamics (void);

static void update_vector_main_rotor_rpm_dynamics (void);

static void update_vector_tail_rotor_rpm_dynamics (void);

static void update_vector_main_rotor_coning_angle (void);

static void update_vector_main_rotor_thrust_dynamics (void);

static void update_vector_tail_rotor_thrust_dynamics (void);

static void update_vector_attitude_dynamics (void);

static void update_vector_power_dynamics (void);

static void update_vector_air_density_dynamics (void);

static void update_vector_acceleration_dynamics (void);

static void update_vector_altitude_dynamics (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_vector_dynamics (void)
{

	FILE
		*file_ptr;

	current_flight_dynamics = &vector_flight_dynamics;

	memset (current_flight_dynamics, 0, sizeof (dynamics_type));

	if (!file_exist ("vector.dyn"))
	{

		set_vector_dynamics_defaults ();

		#if !DEBUG_DYNAMICS

		file_ptr = fopen ("vector.dyn", "wb");

		if (file_ptr)
		{

			save_dynamics_model (file_ptr);
		}

		fclose (file_ptr);

		#endif
	}
	else
	{

		file_ptr = fopen ("vector.dyn", "rb");

		if (file_ptr)
		{

			if (file_size ("vector.dyn") != sizeof (dynamics_type))
			{

				debug_fatal ("DYNAMICS: VECTOR: apache.dyn file incorrect size");
			}

			load_dynamics_model (file_ptr);
		}

		fclose (file_ptr);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_vector_dynamics_defaults (void)
{

	vec3d
		position;

	get_local_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &position);

	current_flight_dynamics->position.x = position.x;
	current_flight_dynamics->position.y = position.y;
	current_flight_dynamics->position.z = position.z;

	get_identity_matrix3x3 (current_flight_dynamics->attitude);

	current_flight_dynamics->air_density.value = 2.3;
	current_flight_dynamics->air_density.max = 2.3;
	current_flight_dynamics->air_density.min = 1.5;

	current_flight_dynamics->altitude.min = 0.0;
	current_flight_dynamics->altitude.max = MAX_MAP_Y;

	current_flight_dynamics->input_data.cyclic_x.min = -100.0;
	current_flight_dynamics->input_data.cyclic_x.max = 100.0;

	current_flight_dynamics->input_data.cyclic_y.min = -100.0;
	current_flight_dynamics->input_data.cyclic_y.max = 100.0;

	current_flight_dynamics->input_data.cyclic_horizontal_pressure.min = -100.0;
	current_flight_dynamics->input_data.cyclic_horizontal_pressure.max = 100.0;

	current_flight_dynamics->input_data.cyclic_vertical_pressure.min = -100.0;
	current_flight_dynamics->input_data.cyclic_vertical_pressure.max = 100.0;

	current_flight_dynamics->input_data.collective_pressure.min = -10.0;
	current_flight_dynamics->input_data.collective_pressure.max = 10.0;

	current_flight_dynamics->input_data.pedal.min = -100.0;
	current_flight_dynamics->input_data.pedal.max = 100.0;

	current_flight_dynamics->input_data.pedal_pressure.min = -10.0;
	current_flight_dynamics->input_data.pedal_pressure.max = 10.0;

	// main rotor characteristics

	current_flight_dynamics->main_rotor_diameter.value = 14.63;
	current_flight_dynamics->main_rotor_area.value = PI * pow ((current_flight_dynamics->main_rotor_diameter.value / 2.0), 2);

	current_flight_dynamics->main_rotor_induced_air.value = 4.63;
	current_flight_dynamics->main_rotor_induced_air.min = 2.5;
	current_flight_dynamics->main_rotor_induced_air.max = 6.5;

	current_flight_dynamics->main_rotor_roll_angle.min = rad (-5.0);
	current_flight_dynamics->main_rotor_roll_angle.max = rad (5.0);

	current_flight_dynamics->main_rotor_pitch_angle.min = rad (-5.0);
	current_flight_dynamics->main_rotor_pitch_angle.max = rad (5.0);

	current_flight_dynamics->main_rotor_thrust.min = 0.0;
	current_flight_dynamics->main_rotor_thrust.max = 100.0;

	current_flight_dynamics->main_rotor_rpm.value = 80.0;
	current_flight_dynamics->main_rotor_rpm.min = 80.0;
	current_flight_dynamics->main_rotor_rpm.max = 100.0;

	current_flight_dynamics->main_rotor_coning_angle.min = rad (-3.0);
	current_flight_dynamics->main_rotor_coning_angle.max = rad (10.0);

	current_flight_dynamics->main_blade_pitch.value = 2.5;
	current_flight_dynamics->main_blade_pitch.min = rad (2.5);
	current_flight_dynamics->main_blade_pitch.max = rad (6.0);

	// tail rotor characteristics

	current_flight_dynamics->tail_rotor_diameter.value = 2.79;

	current_flight_dynamics->tail_rotor_rpm.value = 80.0;
	current_flight_dynamics->tail_rotor_rpm.min = 80.0;
	current_flight_dynamics->tail_rotor_rpm.max = 100.0;

	current_flight_dynamics->tail_rotor_thrust.min = 0.0;
	current_flight_dynamics->tail_rotor_thrust.max = 100.0;

	current_flight_dynamics->tail_blade_pitch.value = 0.0;
	current_flight_dynamics->tail_blade_pitch.min = rad (-5.0);
	current_flight_dynamics->tail_blade_pitch.max = rad (5.0);

	current_flight_dynamics->tail_boom_length.value = 10.59; // actually the wheelbase (but close enough)

	current_flight_dynamics->cross_coupling_effect.value = 0.0;

	// other

	current_flight_dynamics->velocity_x.min = -11.1;
	current_flight_dynamics->velocity_x.max = 11.1;

	current_flight_dynamics->acceleration_x.min = -10.0;
	current_flight_dynamics->acceleration_x.max = 10.0;

	current_flight_dynamics->velocity_y.value = 0.0;
	current_flight_dynamics->velocity_y.min = -1000.0;
	current_flight_dynamics->velocity_y.max = 15.7;

	current_flight_dynamics->acceleration_y.min = -1000.0;
	current_flight_dynamics->acceleration_y.max = 15.7;

	current_flight_dynamics->velocity_z.min = -8.33;
	current_flight_dynamics->velocity_z.max = knots_to_metres_per_second (250); //(197); // never exceed

	current_flight_dynamics->acceleration_z.value = 0.0;
	current_flight_dynamics->acceleration_z.min = -10.0;
	current_flight_dynamics->acceleration_z.max = 10.0;

	current_flight_dynamics->power_avaliable.min = 0.0;
	current_flight_dynamics->power_avaliable.max = 2530.0;

	current_flight_dynamics->lift.min = -10.0;
	current_flight_dynamics->lift.max = 40.0;


	current_flight_dynamics->drag_x.min = 0.90;
	current_flight_dynamics->drag_x.max = 0.98;

	current_flight_dynamics->drag_y.min = 0.80;
	current_flight_dynamics->drag_y.max = 0.97;

	current_flight_dynamics->drag_z.min = 0.9999;
	current_flight_dynamics->drag_z.max = 1.0;

	current_flight_dynamics->heading_inertia.value = 2000;
	current_flight_dynamics->pitch_inertia.value = 1200;
	current_flight_dynamics->roll_inertia.value = 1200;

	current_flight_dynamics->mass.value = 7480.0;
	current_flight_dynamics->mass.min = 5000.0;
	current_flight_dynamics->mass.max = 10000.0;

	current_flight_dynamics->centre_of_gravity.x = 0.00;
	current_flight_dynamics->centre_of_gravity.y = 2.475;
	current_flight_dynamics->centre_of_gravity.z = 0.00;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_vector_dynamics (void)
{

	update_vector_main_rotor_dynamics ();

	update_vector_tail_rotor_dynamics ();

	update_vector_main_rotor_rpm_dynamics ();

	update_vector_tail_rotor_rpm_dynamics ();

	update_vector_main_rotor_coning_angle ();

	update_vector_main_rotor_thrust_dynamics ();

	update_vector_tail_rotor_thrust_dynamics ();

	update_vector_power_dynamics ();

	update_vector_air_density_dynamics ();

	update_vector_acceleration_dynamics ();

	update_vector_altitude_dynamics ();

	update_vector_attitude_dynamics ();

	current_flight_dynamics->position.x += current_flight_dynamics->world_motion_vector.x * get_delta_time ();
	current_flight_dynamics->position.y += current_flight_dynamics->world_motion_vector.y * get_delta_time ();
	current_flight_dynamics->position.z += current_flight_dynamics->world_motion_vector.z * get_delta_time ();

	update_dynamics_external_values ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_vector_main_rotor_dynamics (void)
{

	float
		rotor_roll,
		rotor_pitch,
		cyclic_x,
		cyclic_y,
		collective,
		blade_pitch;

	// calculate blade pitch 0->5 Degs. collective = blade_pitch^3

	collective = current_flight_dynamics->input_data.collective.value;

	blade_pitch = pow (fabs (collective), (float) (1.0 / 3.0)) * (current_flight_dynamics->main_blade_pitch.max / 4.64);

	current_flight_dynamics->main_blade_pitch.value = blade_pitch;

	current_flight_dynamics->main_blade_pitch.value = bound (
																current_flight_dynamics->main_blade_pitch.value,
																current_flight_dynamics->main_blade_pitch.min,
																current_flight_dynamics->main_blade_pitch.max);

	// calculate 'Tip Plane Path' roll and pitch

	// roll

	cyclic_x = current_flight_dynamics->input_data.cyclic_x.value;

	rotor_roll = rad (cyclic_x / (current_flight_dynamics->input_data.cyclic_x.max / deg (current_flight_dynamics->main_rotor_roll_angle.max)));

	current_flight_dynamics->main_rotor_roll_angle.value = rotor_roll;

	current_flight_dynamics->main_rotor_roll_angle.value = bound (
																current_flight_dynamics->main_rotor_roll_angle.value,
																current_flight_dynamics->main_rotor_roll_angle.min,
																current_flight_dynamics->main_rotor_roll_angle.max);

	// pitch

	cyclic_y = current_flight_dynamics->input_data.cyclic_y.value;

	rotor_pitch = -rad (cyclic_y / (current_flight_dynamics->input_data.cyclic_y.max / deg (current_flight_dynamics->main_rotor_pitch_angle.max)));

	current_flight_dynamics->main_rotor_pitch_angle.value = rotor_pitch;

	current_flight_dynamics->main_rotor_pitch_angle.value = bound (
																current_flight_dynamics->main_rotor_pitch_angle.value,
																current_flight_dynamics->main_rotor_pitch_angle.min,
																current_flight_dynamics->main_rotor_pitch_angle.max);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_vector_tail_rotor_dynamics (void)
{

	float
		pedal,
		blade_pitch;

	// calculate blade pitch 0->5 Degs, linearly

	pedal = current_flight_dynamics->input_data.pedal.value;

	blade_pitch = rad (pedal / (current_flight_dynamics->input_data.pedal.max / deg (current_flight_dynamics->main_blade_pitch.max)));

	current_flight_dynamics->tail_blade_pitch.value = blade_pitch;

	current_flight_dynamics->tail_blade_pitch.value = bound (
																current_flight_dynamics->tail_blade_pitch.value,
																current_flight_dynamics->tail_blade_pitch.min,
																current_flight_dynamics->tail_blade_pitch.max);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_vector_main_rotor_rpm_dynamics (void)
{

	current_flight_dynamics->main_rotor_rpm.value = 100;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_vector_tail_rotor_rpm_dynamics (void)
{

	current_flight_dynamics->tail_rotor_rpm.value = 100;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_vector_main_rotor_coning_angle (void)
{

	current_flight_dynamics->main_rotor_coning_angle.value = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_vector_main_rotor_thrust_dynamics (void)
{

	current_flight_dynamics->main_rotor_thrust.value = 100;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_vector_tail_rotor_thrust_dynamics (void)
{

	current_flight_dynamics->tail_rotor_thrust.value = current_flight_dynamics->input_data.pedal.value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_vector_attitude_dynamics (void)
{

	matrix3x3
		delta_attitude,
		attitude;

	float
		heading,
		pitch,
		roll;

	vec3d
		result,
		test_point;

	get_local_entity_attitude_matrix (get_gunship_entity (), attitude);

	// get heading, pitch, and roll

	heading = atan2 (attitude [2][0], attitude [2][2]);

	pitch = asin (attitude [2][1]);

	roll = atan2 (-attitude [0][1], attitude [1][1]);

	current_flight_dynamics->heading.value = heading;

	current_flight_dynamics->pitch.value = pitch;

	current_flight_dynamics->roll.value = roll;

	//
	// roll
	//

	current_flight_dynamics->roll.delta = 30 * current_flight_dynamics->main_rotor_roll_angle.value * get_delta_time ();

	//
	// pitch
	//

	current_flight_dynamics->pitch.delta = 30 * current_flight_dynamics->main_rotor_pitch_angle.value * get_delta_time ();

	//
	// heading
	//

	current_flight_dynamics->heading.delta = 15 * (-(current_flight_dynamics->tail_rotor_thrust.value * current_flight_dynamics->tail_boom_length.value * current_flight_dynamics->tail_rotor_diameter.value) * get_delta_time () /
												current_flight_dynamics->mass.value);

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
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_vector_power_dynamics (void)
{

	current_flight_dynamics->power_avaliable.value = 100;

	current_flight_dynamics->power_parasite.value = 40;

	current_flight_dynamics->power_profile.value = 60;

	current_flight_dynamics->power_induced.value = 40;

	current_flight_dynamics->power_required.value = 100;

	current_flight_dynamics->power_surplus.value = 50;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_vector_air_density_dynamics (void)
{

//	current_flight_dynamics->air_density.value = 2;

	float
		Amax,
		Amin;

	Amax = current_flight_dynamics->air_density.max;

	Amin = current_flight_dynamics->air_density.min;

	current_flight_dynamics->air_density.value = Amax - (((Amax - Amin) / current_flight_dynamics->altitude.max) * current_flight_dynamics->altitude.value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_vector_acceleration_dynamics (void)
{

	vec3d
		position;

	get_local_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &position);

	current_flight_dynamics->position.x = position.x;
	current_flight_dynamics->position.y = position.y;
	current_flight_dynamics->position.z = position.z;

	// convert to world axis and
	// move the object

	current_flight_dynamics->world_velocity_x.value =
						(current_flight_dynamics->velocity_x.value * cos (current_flight_dynamics->heading.value)) +
						(current_flight_dynamics->velocity_z.value * sin (current_flight_dynamics->heading.value)) +
						(current_flight_dynamics->velocity_y.value * sin (current_flight_dynamics->pitch.value) * sin (current_flight_dynamics->heading.value));

	current_flight_dynamics->world_velocity_y.value =
						(current_flight_dynamics->velocity_y.value) +
						(current_flight_dynamics->velocity_z.value * sin (current_flight_dynamics->pitch.value)) +
						(current_flight_dynamics->velocity_x.value * sin (current_flight_dynamics->roll.value));

	current_flight_dynamics->world_velocity_z.value =
						(current_flight_dynamics->velocity_z.value * cos (current_flight_dynamics->heading.value)) +
						(current_flight_dynamics->velocity_x.value * sin (current_flight_dynamics->heading.value)) +
						(current_flight_dynamics->velocity_y.value * sin (current_flight_dynamics->pitch.value) * cos (current_flight_dynamics->heading.value));

	current_flight_dynamics->position.x += current_flight_dynamics->world_velocity_x.value * get_delta_time ();
	current_flight_dynamics->position.y += current_flight_dynamics->world_velocity_y.value * get_delta_time ();
	current_flight_dynamics->position.z += current_flight_dynamics->world_velocity_z.value * get_delta_time ();

	// maintain motion vector for outputed variables.

	current_flight_dynamics->model_motion_vector.x = current_flight_dynamics->velocity_x.value;
	current_flight_dynamics->model_motion_vector.y = current_flight_dynamics->velocity_y.value;
	current_flight_dynamics->model_motion_vector.z = current_flight_dynamics->velocity_z.value;

	current_flight_dynamics->world_motion_vector.x = current_flight_dynamics->world_velocity_x.value;
	current_flight_dynamics->world_motion_vector.y = current_flight_dynamics->world_velocity_y.value;
	current_flight_dynamics->world_motion_vector.z = current_flight_dynamics->world_velocity_z.value;

	position.x = current_flight_dynamics->position.x;
	position.y = current_flight_dynamics->position.y;
	position.z = current_flight_dynamics->position.z;

	set_local_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &position);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_vector_altitude_dynamics (void)
{

	static float
		last_ground_height = 0;

	matrix3x3
		attitude;

	float
		heading,
		pitch,
		roll,
		ground_height,
		centre_of_gravity_to_ground_distance;

	vec3d
		position,
		*face_normal;

	centre_of_gravity_to_ground_distance = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE);

	get_local_entity_attitude_matrix (get_gunship_entity (), attitude);

	ground_height = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_TERRAIN_ELEVATION);

	//
	// debug
	//

	if ((ground_height < -1000) || (ground_height > 32000))
	{

		debug_log ("!!!!!!!!!!!!!! GROUND HEIGHT %f", ground_height);

		ground_height = last_ground_height;
	}

	//
	// end
	//

	last_ground_height = ground_height;

	current_flight_dynamics->altitude.value = current_flight_dynamics->position.y;

	current_flight_dynamics->altitude.min = ground_height;

	switch (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_OPERATIONAL_STATE))
	{

		case OPERATIONAL_STATE_LANDED:
		{

			if (current_flight_dynamics->world_velocity_y.value > 0.0)
			{
		
				#if DEBUG_DYNAMICS
		
				debug_log ("VECTOR DYN: takeoff !");
		
				#endif
		
				set_local_entity_int_value (get_gunship_entity (), INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_NAVIGATING);
		
				delete_local_entity_from_parents_child_list (get_gunship_entity (), LIST_TYPE_CURRENT_WAYPOINT);
		
				transmit_entity_comms_message (ENTITY_COMMS_MOBILE_TAKEOFF, get_gunship_entity ());
			}
			else
			{

				entity
					*wp;

				vec3d
					wp_pos;

				wp = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_CURRENT_WAYPOINT);

				if (wp)
				{

					get_local_waypoint_formation_position (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_FORMATION_POSITION), wp, &wp_pos);

					ground_height = wp_pos.y;
				}
	
				current_flight_dynamics->world_velocity_y.value = max (current_flight_dynamics->world_velocity_y.value, 0.0);

				current_flight_dynamics->velocity_y.value = max (current_flight_dynamics->velocity_y.value, 0.0);
				
				memset (&current_flight_dynamics->world_motion_vector, 0, sizeof (vec3d));
			
				current_flight_dynamics->velocity_x.value = bound (current_flight_dynamics->velocity_x.value, knots_to_metres_per_second (-10), knots_to_metres_per_second (50));
				current_flight_dynamics->velocity_y.value = 0;
				current_flight_dynamics->velocity_z.value = bound (current_flight_dynamics->velocity_z.value, knots_to_metres_per_second (-10), knots_to_metres_per_second (50));
			
				current_flight_dynamics->position.y = ground_height + centre_of_gravity_to_ground_distance;
			
				current_flight_dynamics->altitude.value = ground_height + centre_of_gravity_to_ground_distance;
				
				heading = get_heading_from_attitude_matrix (attitude);
			
				//get_3d_terrain_face_normal (&n, current_flight_dynamics->position.x, current_flight_dynamics->position.z);
				face_normal = get_local_entity_ptr_value (get_gunship_entity (), PTR_TYPE_TERRAIN_FACE_NORMAL);
			
				get_3d_transformation_matrix_from_face_normal_and_heading (attitude, face_normal, heading);
				
				pitch = get_pitch_from_attitude_matrix (attitude);
			
				pitch += rad (aircraft_database [ENTITY_SUB_TYPE_AIRCRAFT_AH64D_APACHE_LONGBOW].fuselage_angle);
			
				roll = get_roll_from_attitude_matrix (attitude);
			
				get_3d_transformation_matrix (attitude, heading, pitch, roll);

				position.x = current_flight_dynamics->position.x;
				position.y = current_flight_dynamics->position.y;
				position.z = current_flight_dynamics->position.z;
			
				set_local_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &position);
			
				set_local_entity_attitude_matrix (get_gunship_entity (), attitude);
			}

			break;
		}

		default:
		{
	
			if (current_flight_dynamics->world_velocity_y.value < 0.0)
			{
	
				if (current_flight_dynamics->altitude.value < current_flight_dynamics->altitude.min + centre_of_gravity_to_ground_distance)
				{
			
					if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_OPERATIONAL_STATE) != OPERATIONAL_STATE_LANDED)
					{
			
						//
						// need to find what wp the user is trying to land on ....
						//
			
						//entity
							//*wp;
				
						#if DEBUG_DYNAMICS
				
						debug_log ("VECTOR DYN: landed !");
				
						#endif
				
						set_local_entity_int_value (get_gunship_entity (), INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_LANDED);
			
						//transmit_entity_comms_message (ENTITY_COMMS_MOBILE_LAND, get_gunship_entity (), wp);
					}
				}
			}
		
			break;
		}
	}

	current_flight_dynamics->altitude.value = bound (
														current_flight_dynamics->altitude.value,
														current_flight_dynamics->altitude.min,
														current_flight_dynamics->altitude.max);
}
/*
{

	matrix3x3
		attitude;

	float
		ground_height,
		centre_of_gravity_to_ground_distance;

	vec3d
		position,
		*old_z,
		n;

	centre_of_gravity_to_ground_distance = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE);

	get_local_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &position);

	get_local_entity_attitude_matrix (get_gunship_entity (), &attitude);

	ground_height = get_3d_terrain_elevation (position.x, position.z);

	current_flight_dynamics->altitude.value = position.y;

	current_flight_dynamics->altitude.min = ground_height;

	if (current_flight_dynamics->altitude.value < current_flight_dynamics->altitude.min + centre_of_gravity_to_ground_distance)
	{

		//
		// debug landing state
		//

		if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_OPERATIONAL_STATE) != OPERATIONAL_STATE_LANDED)
		{

			//
			// need to find what wp the user is trying to land on ....
			//

			//entity
				//*wp;
	
			#if DEBUG_DYNAMICS
	
			debug_log ("VECTOR DYN: landed !");
	
			#endif
	
			set_local_entity_int_value (get_gunship_entity (), INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_LANDED);

			//transmit_entity_comms_message (ENTITY_COMMS_MOBILE_LAND, get_gunship_entity (), wp);
		}

		//
		// end
		//

		memset (&current_flight_dynamics->world_motion_vector, 0, sizeof (vec3d));

		current_flight_dynamics->velocity_y.value = 0;

		position.y = ground_height + centre_of_gravity_to_ground_distance;

		current_flight_dynamics->altitude.value = current_flight_dynamics->altitude.min + centre_of_gravity_to_ground_distance;

		get_3d_terrain_face_normal (&n, position.x, position.z);

		// cross n with z giving x

		old_z = (vec3d *) attitude [2];

		attitude [1][0] = n.x;

		attitude [1][1] = n.y;

		attitude [1][2] = n.z;

		attitude [0][0] = (n.y * old_z->z) - (n.z * old_z->y);

		attitude [0][1] = (n.z * old_z->x) - (n.x * old_z->z);

		attitude [0][2] = (n.x * old_z->y) - (n.y * old_z->x);

		// cross n with x giving z

		attitude [2][0] = - (n.y * attitude [0][2]) + (n.z * attitude [0][1]);

		attitude [2][1] = - (n.z * attitude [0][0]) + (n.x * attitude [0][2]);

		attitude [2][2] = - (n.x * attitude [0][1]) + (n.y * attitude [0][0]);

		normalise_3d_vector ((vec3d *) &attitude [0]);

		normalise_3d_vector ((vec3d *) &attitude [2]);

		set_local_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &position);

		set_local_entity_attitude_matrix (get_gunship_entity (), attitude);
	}
	else if ((get_local_entity_int_value (get_gunship_entity (), INT_TYPE_OPERATIONAL_STATE) == OPERATIONAL_STATE_LANDED) &&
				(current_flight_dynamics->world_velocity_y.value >= 0.0))
	{

		#if DEBUG_DYNAMICS

		debug_log ("VECTOR DYN: takeoff !");

		#endif

		set_local_entity_int_value (get_gunship_entity (), INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_NAVIGATING);

		delete_local_entity_from_parents_child_list (get_gunship_entity (), LIST_TYPE_CURRENT_WAYPOINT);

		transmit_entity_comms_message (ENTITY_COMMS_MOBILE_TAKEOFF, get_gunship_entity ());
	}

	current_flight_dynamics->altitude.value = bound (
														current_flight_dynamics->altitude.value,
														current_flight_dynamics->altitude.min,
														current_flight_dynamics->altitude.max);

}
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void vector_dynamics_velocity (event *ev)
{

	if (ev->modifier == MODIFIER_RIGHT_SHIFT)
	{

		switch (ev->key)
		{

			case DIK_Q:
			{

				current_flight_dynamics->velocity_z.value = 1000;

				break;
			}

			case DIK_A:
			{

				current_flight_dynamics->velocity_z.value = 0.0;

				break;
			}
		}
	}
	else if (ev->modifier == MODIFIER_RIGHT_ALT)
	{

		switch (ev->key)
		{

			case DIK_Q:
			{

				vec3d
					pos;

				get_local_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &pos);

				pos.y += 10;

				set_client_server_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &pos);

				break;
			}

			case DIK_A:
			{

				vec3d
					pos;

				get_local_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &pos);

				pos.y -= 10;

				set_client_server_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &pos);

				break;
			}
		}
	}
	else 
	{

		switch (ev->key)
		{

			case DIK_Q:
			{

				current_flight_dynamics->velocity_z.value += 20;

				break;
			}

			case DIK_A:
			{

				current_flight_dynamics->velocity_z.value -= 20;

				break;
			}
		}
	}

	current_flight_dynamics->velocity_z.value = bound (current_flight_dynamics->velocity_z.value, -1000, 1000);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
