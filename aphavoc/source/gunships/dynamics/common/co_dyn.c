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

#include "co_undercarriage.h"

int
	trim_button_held = FALSE;

static float
	right_g_e_force = 0.0,
	left_g_e_force = 0.0,
	back_g_e_force = 0.0,
	front_g_e_force = 0.0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_trim_control (event *ev)
{
	if (ev->state == KEY_STATE_DOWN)
	{
		current_flight_dynamics->input_data.cyclic_x_trim.value = current_flight_dynamics->input_data.cyclic_x.value;
		current_flight_dynamics->input_data.cyclic_y_trim.value = current_flight_dynamics->input_data.cyclic_y.value;

		current_flight_dynamics->input_data.pedal_trim.value = current_flight_dynamics->input_data.pedal.value;

		trim_button_held = TRUE;
		debug_log ("CO_DYN: setting trim %f, %f, %f", current_flight_dynamics->input_data.cyclic_x.value, current_flight_dynamics->input_data.cyclic_y.value, current_flight_dynamics->input_data.pedal.value);
	}
	else
		trim_button_held = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void clear_trim_control (event *ev)
{
	float centre_trim = 0.0, centre_pedal_trim = 0.0;

	if (!ev || ev->state == KEY_STATE_DOWN)
	{
		// arneh 20060817 - trim for hover
		switch (get_global_gunship_type ())
		{
		case GUNSHIP_TYPE_COMANCHE:
			centre_trim = 2.0;
			if (!get_current_dynamics_options(DYNAMICS_OPTIONS_CROSS_COUPLING))
				centre_pedal_trim = -56.0;
			break;
		case GUNSHIP_TYPE_APACHE:
			centre_trim = 3.5;
			if (!get_current_dynamics_options(DYNAMICS_OPTIONS_CROSS_COUPLING))
				centre_pedal_trim = -56.0;
			break;
		case GUNSHIP_TYPE_AH64A:
			centre_trim = 3.2;
			if (!get_current_dynamics_options(DYNAMICS_OPTIONS_CROSS_COUPLING))
				centre_pedal_trim = -53.0;
			break;
		case GUNSHIP_TYPE_BLACKHAWK:
			centre_trim = 3.0;
			if (!get_current_dynamics_options(DYNAMICS_OPTIONS_CROSS_COUPLING))
				centre_pedal_trim = -61.0;
			break;
		case GUNSHIP_TYPE_HOKUM:
			centre_trim = 0.0;
			break;
		case GUNSHIP_TYPE_KA50:
			centre_trim = 5.0;
			break;
		case GUNSHIP_TYPE_HIND:
			centre_trim = 0.0;
			if (!get_current_dynamics_options(DYNAMICS_OPTIONS_CROSS_COUPLING))
				centre_pedal_trim = 41.0;
			break;
		case GUNSHIP_TYPE_HAVOC:
			centre_trim = 6.0;
			if (!get_current_dynamics_options(DYNAMICS_OPTIONS_CROSS_COUPLING))
				centre_pedal_trim = 49.5;
			break;
		case GUNSHIP_TYPE_VIPER:
			centre_trim = 2.0;
			if (!get_current_dynamics_options(DYNAMICS_OPTIONS_CROSS_COUPLING))
				centre_pedal_trim = -56.0;
			break;
		case GUNSHIP_TYPE_KIOWA:
			centre_trim = 2.0;
			if (!get_current_dynamics_options(DYNAMICS_OPTIONS_CROSS_COUPLING))
				centre_pedal_trim = -56.0;
			break;
		default:
			centre_trim = 6.0;
			if (!get_current_dynamics_options(DYNAMICS_OPTIONS_CROSS_COUPLING))
				centre_pedal_trim = -50.0;
			break;
		}


		current_flight_dynamics->input_data.cyclic_x_trim.value = 0.0;
		current_flight_dynamics->input_data.cyclic_y_trim.value = centre_trim;
		if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AIRBORNE_AIRCRAFT) || command_line_dynamics_flight_model == 2)
			current_flight_dynamics->input_data.pedal_trim.value = 0.0;
		else
			current_flight_dynamics->input_data.pedal_trim.value = centre_pedal_trim;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void adjust_pitch_trim(event *ev)
{
	int adjustment = (ev->key == DIK_UP) ? +1 : -1;

	current_flight_dynamics->input_data.cyclic_y_trim.value += adjustment;

	debug_log ("CO_DYN: pitch trim adjusted to %f", current_flight_dynamics->input_data.cyclic_y_trim.value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void adjust_roll_trim(event *ev)
{
	int adjustment = (ev->key == DIK_RIGHT) ? +1 : -1;

	current_flight_dynamics->input_data.cyclic_x_trim.value += adjustment;

	debug_log ("CO_DYN: roll trim adjusted to %f", current_flight_dynamics->input_data.cyclic_x_trim.value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void adjust_pedal_trim(event *ev)
{
	float adjustment = (ev->key == DIK_X) ? +0.5 : -0.5;

	current_flight_dynamics->input_data.pedal_trim.value += adjustment;

	debug_log ("CO_DYN: pedal trim adjusted to %f", current_flight_dynamics->input_data.pedal_trim.value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_common_dynamics(void)
{
	right_g_e_force = 0.0,
	left_g_e_force = 0.0,
	back_g_e_force = 0.0,
	front_g_e_force = 0.0,
	trim_button_held = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_common_attitude_dynamics (void)
{

	int
		model_landed,
		coaxial = 0;

	matrix3x3
		rotor_attitude,
		attitude;

	float
		rotor_radius = current_flight_dynamics->main_rotor_diameter.value * 0.5,
		angle,
		rotor_edge_value,
		motion_vector_magnitude,
		rotor_split,
		edge_rotor_split,
		force,
		rotor_force,
		front_rotor_force,
		back_rotor_force,
		left_rotor_force,
		right_rotor_force,
		reaction_force,
		main_angular_force = 0,
		tail_angular_force = 0,
		mass_percentage;

	float
		main_rotor_induced_air_value,
		main_rotor_pitch_angle_value,
		main_rotor_rpm_value,
		main_rotor_roll_angle_value,
		tail_rotor_induced_air_value,
		heading_inertia_modifier,
		pitch_inertia_modifier,
		roll_inertia_modifier,
		heading_moment_modifier,
		pitch_moment_modifier,
		roll_moment_modifier,
		pitch_value,
		main_blade_x_pitch_value,
		main_blade_y_pitch_value,
		velocity_z_value,
		horizontal_velocity,
		main_blade_pitch_value,
		sqr_main_rotor_rpm;

	vec3d
		wind,
		model_wind,
		position,
		rotor_direction,
		direction,
		world_motion_vector,
		model_motion_vector;

	model_landed = !get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AIRBORNE_AIRCRAFT);

	switch (current_flight_dynamics->sub_type)
	{
		case ENTITY_SUB_TYPE_AIRCRAFT_CH46E_SEA_KNIGHT:
		case ENTITY_SUB_TYPE_AIRCRAFT_CH47D_CHINOOK:
		case ENTITY_SUB_TYPE_AIRCRAFT_MV22_OSPREY:
		case ENTITY_SUB_TYPE_AIRCRAFT_KA52_HOKUM_B:
		case ENTITY_SUB_TYPE_AIRCRAFT_KA50_HOKUM:
		case ENTITY_SUB_TYPE_AIRCRAFT_KA29_HELIX_B:
			coaxial = 1;
	}
	
	get_local_entity_attitude_matrix (get_gunship_entity (), attitude);

	world_motion_vector = current_flight_dynamics->world_motion_vector;
	model_motion_vector = current_flight_dynamics->model_motion_vector;

	//
	// allow for wind
	//

	position.x = current_flight_dynamics->position.x;
	position.y = current_flight_dynamics->position.y;
	position.z = current_flight_dynamics->position.z;

	if (get_current_dynamics_options (DYNAMICS_OPTIONS_WIND))
	{

		get_session_wind_velocity_at_point (&position, &wind);

		multiply_matrix3x3_vec3d (&model_wind, current_flight_dynamics->attitude, &wind);

		world_motion_vector.x -= wind.x;
		world_motion_vector.y -= wind.y;
		world_motion_vector.z -= wind.z;

		model_motion_vector.x -= model_wind.x;
		model_motion_vector.y -= model_wind.y;
		model_motion_vector.z -= model_wind.z;
	}

	motion_vector_magnitude = get_3d_vector_magnitude (&current_flight_dynamics->model_motion_vector);

	//////////////////////////////////////////////////////////
	// safey check
	//////////////////////////////////////////////////////////
	if (motion_vector_magnitude > 1000 || current_flight_dynamics->angular_pitch_velocity.value > 50 || current_flight_dynamics->angular_roll_velocity.value > 50 || current_flight_dynamics->angular_heading_velocity.value > 50)
	{

		debug_log ("DYNAMICS: UNSTABLE motion magnitude %f", motion_vector_magnitude);

		if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE))
		{

			current_flight_dynamics->model_motion_vector.x = 0.0;
			current_flight_dynamics->model_motion_vector.y = 0.0;
			current_flight_dynamics->model_motion_vector.z = 0.0;

			current_flight_dynamics->model_acceleration_vector.x = 0.0;
			current_flight_dynamics->model_acceleration_vector.y = 0.0;
			current_flight_dynamics->model_acceleration_vector.z = 0.0;

			current_flight_dynamics->world_motion_vector.x = 0.0;
			current_flight_dynamics->world_motion_vector.y = 0.0;
			current_flight_dynamics->world_motion_vector.z = 0.0;

			current_flight_dynamics->world_acceleration_vector.x = 0.0;
			current_flight_dynamics->world_acceleration_vector.y = 0.0;
			current_flight_dynamics->world_acceleration_vector.z = 0.0;

			set_client_server_entity_float_value (get_gunship_entity (), FLOAT_TYPE_VELOCITY, 0.0);

			set_client_server_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_MOTION_VECTOR, &current_flight_dynamics->model_motion_vector);

			kill_client_server_entity (get_gunship_entity ());

//			start_game_exit (GAME_EXIT_CRASH, FALSE);
		}

		return;
	}
	//////////////////////////////////////////////////////////

	//
	// Set up variables
	//

	main_rotor_rpm_value = current_flight_dynamics->main_rotor_rpm.value * current_flight_dynamics->main_rotor_rpm.modifier;
	sqr_main_rotor_rpm = pow(main_rotor_rpm_value / current_flight_dynamics->main_rotor_rpm.max, 2);
	main_rotor_induced_air_value = sqr_main_rotor_rpm * current_flight_dynamics->main_rotor_induced_air.value * current_flight_dynamics->main_rotor_induced_air.modifier;
	main_rotor_pitch_angle_value = current_flight_dynamics->main_rotor_pitch_angle.value * current_flight_dynamics->main_rotor_pitch_angle.modifier;
	main_rotor_roll_angle_value = current_flight_dynamics->main_rotor_roll_angle.value * current_flight_dynamics->main_rotor_roll_angle.modifier;
	tail_rotor_induced_air_value = sqr_main_rotor_rpm * current_flight_dynamics->tail_rotor_induced_air.value * current_flight_dynamics->tail_rotor_induced_air.modifier;
	heading_inertia_modifier = current_flight_dynamics->heading_inertia.modifier;
	pitch_inertia_modifier = current_flight_dynamics->pitch_inertia.modifier;
	roll_inertia_modifier = current_flight_dynamics->roll_inertia.modifier;
	heading_moment_modifier = current_flight_dynamics->heading_moment.modifier;
	pitch_moment_modifier = current_flight_dynamics->pitch_moment.modifier;
	roll_moment_modifier = current_flight_dynamics->roll_moment.modifier;
	pitch_value = current_flight_dynamics->pitch.value * current_flight_dynamics->pitch.modifier; // + debug_var_y * rad(1.0);
	main_blade_x_pitch_value = current_flight_dynamics->main_blade_x_pitch.value * current_flight_dynamics->main_blade_x_pitch.modifier;
	main_blade_y_pitch_value = current_flight_dynamics->main_blade_y_pitch.value * current_flight_dynamics->main_blade_y_pitch.modifier;
	velocity_z_value = current_flight_dynamics->velocity_z.value * current_flight_dynamics->velocity_z.modifier;
	main_blade_pitch_value = current_flight_dynamics->main_blade_pitch.value * current_flight_dynamics->main_blade_pitch.modifier;

	rotor_direction.x = 0.0;
	rotor_direction.y = 1.0;
	rotor_direction.z = 0.0;

	get_3d_transformation_heading_pitch_matrix(rotor_attitude, main_rotor_roll_angle_value, rad(5.0) - main_rotor_pitch_angle_value);
	multiply_transpose_matrix3x3_vec3d(&rotor_direction, rotor_attitude, &rotor_direction);

	////////////////////////////////////////////
	// gravity
	////////////////////////////////////////////
	{
		set_flight_dynamics_mass ();

		mass_percentage = current_flight_dynamics->mass.value;
		mass_percentage /= (current_flight_dynamics->mass.min + current_flight_dynamics->fuel_weight.max);

		force = G * mass_percentage;

		position.x = current_flight_dynamics->centre_of_gravity.x;
		position.y = current_flight_dynamics->centre_of_gravity.y;
		position.z = current_flight_dynamics->centre_of_gravity.z;

		direction.x = 0.0;
		direction.y = -1.0;
		direction.z = 0.0;

		multiply_transpose_matrix3x3_vec3d (&direction, attitude, &direction);

		//debug_log("force: %.2f", force);

		add_dynamic_force ("Gravity", force, 0.0, &position, &direction, FALSE);
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Rotor Force Analysis
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	angle = 1.0;
	rotor_split = 0.90;

	edge_rotor_split = 1.0 - rotor_split;
	edge_rotor_split /= 8.0;

	rotor_edge_value = 0.401681;

	////////////////////////////////////////////
	// Transitional Lift generated by 'Wing' effect
	////////////////////////////////////////////

	if (current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_MAIN_ROTOR || current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_MAIN_ROTOR_BLADE)
		current_flight_dynamics->translational_lift.value = 0.5;
	else if (get_current_dynamics_options (DYNAMICS_OPTIONS_TRANSITIONAL_LIFT))
	{

		vec3d
			wind,
			position,
			normalised_model_motion_vector;

		float
			vel;
		
		dynamics_float_variable
			*tl = &current_flight_dynamics->translational_lift;

		normalised_model_motion_vector = model_motion_vector;

		position.x = current_flight_dynamics->position.x;
		position.y = current_flight_dynamics->position.y;
		position.z = current_flight_dynamics->position.z;

		if (get_current_dynamics_options (DYNAMICS_OPTIONS_WIND))
		{

			get_session_wind_velocity_at_point (&position, &wind);

			multiply_transpose_matrix3x3_vec3d (&wind, current_flight_dynamics->attitude, &wind);

			normalised_model_motion_vector.x -= wind.x;
			normalised_model_motion_vector.y -= wind.y;
			normalised_model_motion_vector.z -= wind.z;
		}

		normalised_model_motion_vector.y = 0.0;

		vel = min(get_3d_vector_magnitude(&normalised_model_motion_vector) / current_flight_dynamics->velocity_z.max, 1.0f);

		if (vel <= tl->modifier)
			tl->value = tl->min + (tl->max - tl->min) * pow(vel / tl->modifier, 0.4f);
		else
			tl->value = tl->min + (tl->max - tl->min) * pow((1 - vel) / (1 - tl->modifier), 0.4f);

//		debug_log("TRANSITIONAL %f", current_flight_dynamics->translational_lift.value);
	}
	else
		current_flight_dynamics->translational_lift.value = 1.0;

	////////////////////////////////////////////
	// middle of rotor disc
	////////////////////////////////////////////
	{
		rotor_force = rotor_split * main_rotor_induced_air_value * current_flight_dynamics->translational_lift.value;

		position.x = 0.0;
		position.y = 0.0;
		position.z = 0.0;

		add_dynamic_force ("Middle rotor force", command_line_dynamics_main_rotor_lift * rotor_force, 0.0, &position, &rotor_direction, FALSE);
	}

	////////////////////////////////////////////
	// front of rotor disc
	////////////////////////////////////////////
	{

		angle = main_rotor_pitch_angle_value;

		front_rotor_force = rotor_edge_value +
				(0.6 * angle) / (current_flight_dynamics->main_rotor_pitch_angle.max - current_flight_dynamics->main_rotor_pitch_angle.min) +
				 pitch_moment_modifier / mass_percentage * (0.2 * current_flight_dynamics->input_data.collective.value) / (current_flight_dynamics->input_data.collective.max - current_flight_dynamics->input_data.collective.min);

		front_rotor_force *= sqr_main_rotor_rpm;

		position.x = 0.0;
		position.y = 0.0;
		position.z = rotor_radius;

		add_dynamic_force ("Front rotor force", command_line_dynamics_main_rotor_lift * front_rotor_force, 0.0, &position, &rotor_direction, FALSE);
	}
	////////////////////////////////////////////
	// back of rotor disc
	////////////////////////////////////////////
	{

		angle = main_rotor_pitch_angle_value;

		back_rotor_force = rotor_edge_value -
				(0.6 * angle) / (current_flight_dynamics->main_rotor_pitch_angle.max - current_flight_dynamics->main_rotor_pitch_angle.min) +
				pitch_moment_modifier / mass_percentage * (0.2 * current_flight_dynamics->input_data.collective.value) / (current_flight_dynamics->input_data.collective.max - current_flight_dynamics->input_data.collective.min);

		back_rotor_force *= sqr_main_rotor_rpm;

		position.x = 0.0;
		position.y = 0.0;
		position.z = -rotor_radius;

		add_dynamic_force ("Back rotor force", command_line_dynamics_main_rotor_lift * back_rotor_force, 0.0, &position, &rotor_direction, FALSE);
	}
	////////////////////////////////////////////
	// left of rotor disc
	////////////////////////////////////////////
	{

		angle = main_rotor_roll_angle_value;

		left_rotor_force = rotor_edge_value - 
				(0.6 * angle) / (current_flight_dynamics->main_rotor_roll_angle.max - current_flight_dynamics->main_rotor_roll_angle.min) +
				roll_moment_modifier / mass_percentage * (0.2 * current_flight_dynamics->input_data.collective.value) / (current_flight_dynamics->input_data.collective.max - current_flight_dynamics->input_data.collective.min);

		left_rotor_force *= sqr_main_rotor_rpm;

		position.x = rotor_radius;
		position.y = 0.0;
		position.z = 0.0;

		add_dynamic_force ("Left rotor force", command_line_dynamics_main_rotor_lift * left_rotor_force, 0.0, &position, &rotor_direction, FALSE);
	}
	////////////////////////////////////////////
	// right of rotor disc
	////////////////////////////////////////////
	{

		angle = main_rotor_roll_angle_value;

		right_rotor_force = rotor_edge_value + 
				(0.6 * angle) / (current_flight_dynamics->main_rotor_roll_angle.max - current_flight_dynamics->main_rotor_roll_angle.min) +
				roll_moment_modifier / mass_percentage * (0.2 * current_flight_dynamics->input_data.collective.value) / (current_flight_dynamics->input_data.collective.max - current_flight_dynamics->input_data.collective.min);

		right_rotor_force *= sqr_main_rotor_rpm;

		position.x = -rotor_radius;
		position.y = 0.0;
		position.z = 0.0;

		add_dynamic_force ("Right rotor force", command_line_dynamics_main_rotor_lift * right_rotor_force, 0.0, &position, &rotor_direction, FALSE);
	}
	////////////////////////////////////////////
	// tail rotor disc
	////////////////////////////////////////////
	if (!coaxial)
	{

		tail_angular_force = tail_rotor_induced_air_value * current_flight_dynamics->tail_boom_length.value;
		tail_angular_force *= heading_moment_modifier;
		
		position.x = 0.0;
		position.y = 0.0; // -0.08022;
		position.z = -current_flight_dynamics->tail_boom_length.value;

		direction.x = - 1.0;
		direction.y = 0.0;
		direction.z = 0.0;

		add_dynamic_force ("Angular tail rotor force", tail_angular_force, 0.0, &position, &direction, FALSE);
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Rotor Aerodynamic Analysis
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		vec3d
			temp_model_motion_vector;

		temp_model_motion_vector = current_flight_dynamics->model_motion_vector;
		temp_model_motion_vector.y = 0.0;
		horizontal_velocity = (get_3d_vector_magnitude (&temp_model_motion_vector));
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Secondary effects
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////
	// Retreating blade lift loss
	////////////////////////////////////////////
	if (get_current_dynamics_options (DYNAMICS_OPTIONS_RETREATING_BLADE_STALL) && !coaxial)
	{

		if (!(get_current_dynamics_options (DYNAMICS_OPTIONS_KEYBOARD_ASSISTANCE) && (get_global_cyclic_input () == KEYBOARD_INPUT)))
		{

			if (!(current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_MAIN_ROTOR))
			{

				left_rotor_force = 0.1 * ((edge_rotor_split * main_rotor_induced_air_value) -
							((edge_rotor_split * main_rotor_induced_air_value * main_rotor_roll_angle_value) /
							(current_flight_dynamics->main_rotor_roll_angle.max - current_flight_dynamics->main_rotor_roll_angle.min)));

				left_rotor_force *= (motion_vector_magnitude *
											motion_vector_magnitude *
											motion_vector_magnitude) /
											(current_flight_dynamics->velocity_z.max *
											current_flight_dynamics->velocity_z.max *
											current_flight_dynamics->velocity_z.max);

				left_rotor_force *= command_line_dynamics_retreating_blade_stall_effect;

				position.x = rotor_radius;
				position.y = 0.0;
				position.z = 0.0;

				direction.x = 0.0;
				direction.y = -current_flight_dynamics->rotor_rotation_direction;
				direction.z = 0.0;

				add_dynamic_force ("Retreating blade stall", left_rotor_force, 0.0, &position, &direction, FALSE);
			}
		}
	}
	////////////////////////////////////////////
	// Advancing Blade lift gain
	////////////////////////////////////////////
	if (get_current_dynamics_options (DYNAMICS_OPTIONS_RETREATING_BLADE_STALL) && !coaxial)
	{

		if (!(get_current_dynamics_options (DYNAMICS_OPTIONS_KEYBOARD_ASSISTANCE) && (get_global_cyclic_input () == KEYBOARD_INPUT)))
		{

			if (!(current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_MAIN_ROTOR))
			{

				right_rotor_force = 0.1 * ((edge_rotor_split * main_rotor_induced_air_value) +
							((edge_rotor_split * main_rotor_induced_air_value * main_rotor_roll_angle_value) /
							(current_flight_dynamics->main_rotor_roll_angle.max - current_flight_dynamics->main_rotor_roll_angle.min)));

				right_rotor_force *= (motion_vector_magnitude *
											motion_vector_magnitude *
											motion_vector_magnitude) /
											(current_flight_dynamics->velocity_z.max *
											current_flight_dynamics->velocity_z.max *
											current_flight_dynamics->velocity_z.max);

				right_rotor_force *= command_line_dynamics_retreating_blade_stall_effect;

				position.x = -rotor_radius;
				position.y = 0.0;
				position.z = 0.0;

				direction.x = 0.0;
				direction.y = current_flight_dynamics->rotor_rotation_direction;
				direction.z = 0.0;

				add_dynamic_force ("Advancing blade stall", right_rotor_force, 0.0, &position, &direction, FALSE);
			}
		}
	}
	////////////////////////////////////////////
	// Advancing Blade Sonic Buildup effect
	////////////////////////////////////////////
	if (!(current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_MAIN_ROTOR))
	{
		if (velocity_z_value - current_flight_dynamics->velocity_z.max > 0)
		{
			static float
				time = 0.0;

			// Approaching VNE speech

			time -= get_model_delta_time ();

			if (time <= 0.0)
			{

				play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_HOVER_HOLD_TOO_FAST1);

				time = DYNAMICS_EXCEEDING_VNE_SPEECH_TIME;
			}

			// 1.1 is smooth coefficient
			force = sfrand1 () * (exp (100 * (velocity_z_value - 1.1 * current_flight_dynamics->velocity_z.max) / current_flight_dynamics->velocity_z.max) - 1);

			// scale on blade pitch.
			force *= 0.25 + 0.75 * ((current_flight_dynamics->main_blade_pitch.value - current_flight_dynamics->main_blade_pitch.min) / (current_flight_dynamics->main_blade_pitch.max - current_flight_dynamics->main_blade_pitch.min));

			if (!get_current_dynamics_options (DYNAMICS_OPTIONS_RETREATING_BLADE_STALL))
				force = bound(force, -0.5, 0.5);
			else
				force = bound(force, -10.0, 10.0);

			position.x = -rotor_radius;
			position.y = 0.0;
			position.z = sfrand1() * rotor_radius;

			direction.x = sfrand1() * current_flight_dynamics->rotor_rotation_direction;
			direction.y = current_flight_dynamics->rotor_rotation_direction;
			direction.z = sfrand1() * current_flight_dynamics->rotor_rotation_direction;

			add_dynamic_force ("Sonic buildup", force, 0.0, &position, &direction, FALSE);
		}
	}
	////////////////////////////////////////////
	// main rotor disc torque effect
	////////////////////////////////////////////

	{
		// arneh - main rotor produces no torque when disengaged from
		// engine or if running with cross coupling enabled
		if (!coaxial && !current_flight_dynamics->cross_coupling_effect.damaged &&
			get_current_dynamics_options (DYNAMICS_OPTIONS_CROSS_COUPLING) && !(current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_MAIN_ROTOR_BLADE))
		{
			main_angular_force = 0.0;
		}
		else
		{

			static float
				v = 0.0,
				relative_air_flow_angle = 0,
				res = 6,
				mass = 40.0,
				torque = 0.0;

			float
				f = 0.0,
				p = 0.0025,
				i = 0.00125,
				blade_pitch,
				a,
				u,
				rotor_friction,
				rotor_parasitic,
				rotor_induced,
				rotor_drag;

			u = main_rotor_rpm_value;

			if (!u)
				torque = 0.0; // reset value if we jumped in another aircraft

			blade_pitch = bound (main_blade_pitch_value, current_flight_dynamics->main_blade_pitch.min, current_flight_dynamics->main_blade_pitch.max);

			blade_pitch = main_blade_pitch_value - current_flight_dynamics->main_blade_pitch.min;

			////////////////////////////////////////////////////////////

			relative_air_flow_angle = 0.0;

			rotor_friction = u * f;
			rotor_parasitic = (u * u) * p;
			rotor_induced = (u * u) * i * deg (fabs (blade_pitch + relative_air_flow_angle));

			if (!coaxial)
				rotor_drag = rotor_induced * current_flight_dynamics->cross_coupling_effect.modifier;
			else
				rotor_drag = rotor_friction + rotor_parasitic + rotor_induced;
//			debug_log("blade_pitch %f, rotor_drag %f", deg (fabs (blade_pitch + relative_air_flow_angle)), rotor_drag);
			a = (torque - rotor_drag) / mass;

			v = (a * get_model_delta_time ());

			// engine management

			torque -= 2 * (v + (a * res)) * get_model_delta_time ();
			torque = bound (torque, 0.0, 120.0);

			if (!coaxial)
				main_angular_force = 0.01 * current_flight_dynamics->cross_coupling_effect.modifier * torque;// * 2.0 * PI * (current_flight_dynamics->main_rotor_diameter.value / 2.0) / 1649.0;
			else
				main_angular_force = heading_moment_modifier / mass_percentage * torque * fabs(current_flight_dynamics->tail_blade_pitch.value / current_flight_dynamics->tail_blade_pitch.max) / 100;				

			position.x = 0.0;
			position.y = 0.0; // -0.08022;
			position.z = - rotor_radius;

			if (!coaxial)
				direction.x = current_flight_dynamics->rotor_rotation_direction;
			else
				direction.x = current_flight_dynamics->rotor_rotation_direction * sign(current_flight_dynamics->tail_blade_pitch.value);
			
			direction.y = 0.0;
			direction.z = 0.0;

//			main_angular_force += pow(current_flight_dynamics->tail_rotor_diameter.value, 2) * sqr_main_rotor_rpm;

			add_dynamic_force ("Main rotor angular torque", main_angular_force, 0.0, &position, &direction, FALSE);
		}
	}
	////////////////////////////////////////////
	// Rotor Resistance to movement (Pitch) raw delta pitch
	////////////////////////////////////////////
	{

		reaction_force = pitch_inertia_modifier * (current_flight_dynamics->pitch.delta + current_flight_dynamics->main_rotor_pitch_angle.delta);

		position.x = 0.0;
		position.y = 0.0;
		position.z = rotor_radius;

		direction.x = 0.0;
		direction.y = -1.0;
		direction.z = 0.0;

		add_dynamic_force ("Pitch resistance", reaction_force, 0.0, &position, &direction, FALSE);
	}
	////////////////////////////////////////////
	// Rotor Resistance to movement (Roll)
	////////////////////////////////////////////
	{

		reaction_force = roll_inertia_modifier * (current_flight_dynamics->roll.delta + current_flight_dynamics->main_rotor_roll_angle.delta);

		position.x = rotor_radius;
		position.y = 0.0;
		position.z = 0.0;

		add_dynamic_force ("Roll resistance", reaction_force, 0.0, &position, &rotor_direction, FALSE);
	}
	////////////////////////////////////////////
	// Tail Rotor Resistance to movement. raw delta heading resistance
	////////////////////////////////////////////

	{

		float
			a,
			scaling,
			delta = fabs(current_flight_dynamics->heading.delta) >= 0.005 ? current_flight_dynamics->heading.delta : (sign(current_flight_dynamics->heading.delta) * 200 * pow(current_flight_dynamics->heading.delta, 2));

		reaction_force = - heading_inertia_modifier * delta * current_flight_dynamics->tail_boom_length.value;

		a = exp (velocity_z_value / 90.0);

		if (a != 0.0)
		{

			scaling = 1.0 - (1.0 / a);
		}

		scaling = min (fabs (scaling), 1.0f);

//		if (!coaxial)
//			reaction_force += (tail_angular_force - main_angular_force) * scaling;

		position.x = 0.0;
		position.y = 0.0; //-0.08022;
		position.z = -current_flight_dynamics->tail_boom_length.value;

		direction.x = 1.0;
		direction.y = 0.0;
		direction.z = 0.0;

		add_dynamic_force ("Yaw resistance", reaction_force, 0.0, &position, &direction, FALSE);
	}
	////////////////////////////////////////////
	// Fuselage aerodynamics motion_vector -> attitude realignment force in the y axis
	////////////////////////////////////////////
	if (!(current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_MAIN_ROTOR))
	{

		if (!check_zero_3d_vector (&model_motion_vector))
		{

			vec3d
				normalised_vector;

			normalised_vector = model_motion_vector;

			normalise_any_3d_vector (&normalised_vector);

			// arneh, 20060813 - reduce banking effect on heading change at slow speed
			force = heading_inertia_modifier * normalised_vector.x * 0.00001 * pow(horizontal_velocity, 2.0) * 
					(0.25 * current_flight_dynamics->tail_boom_length.value + pow(current_flight_dynamics->tail_rotor_diameter.value, 2.0));

			direction.x *= - sign(force);
			direction.y = 0.0;
			direction.z = 0.0;

			position.x = 0.0;
			position.y = 0.0;
			position.z = -current_flight_dynamics->tail_boom_length.value;

			add_dynamic_force ("Realign force (Y axis)", fabs(force), 0.0, &position, &direction, FALSE);
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Aerodynamics
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////
	// Fuselage aerodynamics motion_vector -> attitude realignment force in the x axis
	////////////////////////////////////////////
	if (!(current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_MAIN_ROTOR))
	{

		reaction_force = 30.0 * (current_flight_dynamics->pitch.delta + current_flight_dynamics->main_rotor_pitch_angle.delta);

		if (current_flight_dynamics->velocity_z.max != 0.0)
			reaction_force *= motion_vector_magnitude / current_flight_dynamics->velocity_z.max;
		else
			reaction_force = 0.0;

		position.x = 0.0;
		position.y = 0.0;
		position.z = rotor_radius;

		direction.x = 0.0;
		direction.y = -1.0;
		direction.z = 0.0;

		add_dynamic_force ("Realign force (X axis)", reaction_force, 0.0, &position, &direction, FALSE);
	}

	////////////////////////////////////////////
	// Resistance to forward movement
	////////////////////////////////////////////
	{

		vec3d
			motion_vector = current_flight_dynamics->model_motion_vector;
		float
			drag,
			heading,
			pitch;

		if (normalise_any_3d_vector(&motion_vector))
		{
			get_heading_and_pitch_from_3d_unit_vector(&motion_vector, &heading, &pitch);
			
			drag = 0.0003 * (current_flight_dynamics->drag_z.modifier + 
					current_flight_dynamics->drag_x.modifier * fabs(sin(heading)) + 
					current_flight_dynamics->drag_y.modifier * fabs(sin(pitch)));

			reaction_force = drag * motion_vector_magnitude * motion_vector_magnitude;

			position.x = motion_vector.x * rotor_radius;
			position.y = motion_vector.y * rotor_radius - 0.1 * aircraft_database[current_flight_dynamics->sub_type].centre_of_gravity_to_ground_distance;
			position.z = motion_vector.z * rotor_radius;

			direction.x = - motion_vector.x;
			direction.y = - motion_vector.y;
			direction.z = - motion_vector.z;

			add_dynamic_force ("Forward motion drag", reaction_force, 0.0, &position, &direction, FALSE);
		}
	}
	////////////////////////////////////////////
	// Resistance to vertical movement
	////////////////////////////////////////////

	// if we're in contact with something then the helicopter may not move afterall
	// and what we thought were downward movement isn't actually, and when we then
	// apply "drag" we're actually creating a force which moves the helicopter in the
	// opposite direction.  So disable the drag if we're in contact with something else
	// (most commonly the ground)
	if (!fixed_collision_count)
	{

		float
			drag,
			sideways_drag,
			Fmax;

		// ball park figures
		drag = 0.4;

		Fmax = 0.0;
		// arneh 20060813 - reduce drag in sideway flight - compensated by reduced lift.
		// makes it impossible to keep flying sideways at insane bank angles without losing altitude
		sideways_drag = 5.0 * (model_motion_vector.x * model_motion_vector.x) / pow (current_flight_dynamics->velocity_x.max, 2.0f);


		if (current_flight_dynamics->main_rotor_rpm.max != 0.0)
		{

			Fmax = drag + sideways_drag + 4.5 * (main_rotor_rpm_value / current_flight_dynamics->main_rotor_rpm.max);
		}

		reaction_force = 0.0;

		if (current_flight_dynamics->velocity_y.max != 0.0)
		{

			reaction_force = current_flight_dynamics->drag_y.modifier * Fmax * (fabs (model_motion_vector.y) * model_motion_vector.y) / pow (current_flight_dynamics->velocity_y.max, 2.0f);
		}

		//
		// Only add resistane lift
		//

//		if (reaction_force > 0.0)
		{

			position.x = 0.0;
			position.y = 1.0;
			position.z = 0.0;

			direction.x = 0.0;
			direction.y = (reaction_force > 0.0) ? -1.0 : 1.0;
			direction.z = 0.0;

			add_dynamic_force ("Vertical motion drag", fabs(reaction_force), 0.0, &position, &direction, FALSE);
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// External forces
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////
	// In Ground Effect
	////////////////////////////////////////////
	if ((get_current_dynamics_options (DYNAMICS_OPTIONS_GROUND_EFFECT)) &&
		(!(current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_MAIN_ROTOR)))
	{

		float
			altitude;

		terrain_3d_point_data
			terrain_info;

		vec3d
			world_position;

		memset (&terrain_info, 0, sizeof (terrain_3d_point_data));

		get_3d_terrain_point_data (current_flight_dynamics->position.x, current_flight_dynamics->position.z, &terrain_info);

		altitude = current_flight_dynamics->position.y - get_3d_terrain_point_data_elevation (&terrain_info);

		////////////////////////////////////////////
		// In Ground Effect on middle side of rotor disc
		////////////////////////////////////////////
		{

			float
				over_all_g_e_force;

			over_all_g_e_force = (1.0 - ((altitude * altitude) / (current_flight_dynamics->main_rotor_diameter.value * current_flight_dynamics->main_rotor_diameter.value)));

			over_all_g_e_force = bound (over_all_g_e_force, 0.0, 1.0);

			over_all_g_e_force *= 0.1 * main_rotor_induced_air_value;

			if (current_flight_dynamics->velocity_z.max != 0.0)
			{

				over_all_g_e_force *= (current_flight_dynamics->velocity_z.max - fabs (velocity_z_value)) / current_flight_dynamics->velocity_z.max;
			}

			position.x = 0.0;
			position.y = 0.0;
			position.z = 0.0;

			over_all_g_e_force *= current_flight_dynamics->ground_effect.modifier;

			add_dynamic_force ("Middle rotor Ground effect", over_all_g_e_force, 0.0, &position, &rotor_direction, FALSE);
		}
		////////////////////////////////////////////
		// In Ground Effect on front side of rotor disc
		////////////////////////////////////////////
		{

			float
				tuning_value;

			tuning_value = 0.1;

			position.x = 0.0;
			position.y = 0.0;
			position.z = rotor_radius;

			multiply_matrix3x3_vec3d (&world_position, current_flight_dynamics->attitude, &position);

			world_position.x += current_flight_dynamics->position.x;
			world_position.y += current_flight_dynamics->position.y;
			world_position.z += current_flight_dynamics->position.z;

			bound_position_to_adjusted_map_volume (&world_position);

			get_3d_terrain_point_data (world_position.x, world_position.z, &terrain_info);

			altitude = world_position.y - get_3d_terrain_point_data_elevation (&terrain_info);

			altitude = max (altitude, 0.0f);

			front_g_e_force += ((0.05 - ((altitude * altitude) / (20.0 * current_flight_dynamics->main_rotor_diameter.value * current_flight_dynamics->main_rotor_diameter.value))) - front_g_e_force) * get_model_delta_time ();

			front_g_e_force = bound (front_g_e_force, 0.0, 0.05);

			if (front_g_e_force > 0.0)
			{

				front_g_e_force *= tuning_value * main_rotor_induced_air_value;

				if (current_flight_dynamics->velocity_z.max != 0.0)
				{

					front_g_e_force *= (current_flight_dynamics->velocity_z.max - fabs (velocity_z_value)) / current_flight_dynamics->velocity_z.max;
				}

				#if DEBUG_MODULE

				debug_log ("DYNAMICS: IGE front force %f, alt %f, y %f, el %f, x %f, z %f, tuning %f induced %f",
								front_g_e_force, altitude, current_flight_dynamics->position.y,
								get_3d_terrain_point_data_elevation (&terrain_info), world_position.x, world_position.z,
								tuning_value, main_rotor_induced_air_value);

				create_vectored_debug_3d_object (&world_position, &direction, OBJECT_3D_ARROW_FORCES, 0, 20.0 * front_g_e_force);

				#endif

				front_g_e_force *= current_flight_dynamics->ground_effect.modifier;

				add_dynamic_force ("Front rotor Ground effect", front_g_e_force, 0.0, &position, &rotor_direction, FALSE);
			}
		}
		////////////////////////////////////////////
		// In Ground Effect on back side of rotor disc
		////////////////////////////////////////////
		{

			float
				tuning_value = 0.1;

			position.x = 0.0;
			position.y = 0.0;
			position.z = -rotor_radius;

			multiply_matrix3x3_vec3d (&world_position, current_flight_dynamics->attitude, &position);

			world_position.x += current_flight_dynamics->position.x;
			world_position.y += current_flight_dynamics->position.y;
			world_position.z += current_flight_dynamics->position.z;

			bound_position_to_adjusted_map_volume (&world_position);

			get_3d_terrain_point_data (world_position.x, world_position.z, &terrain_info);

			altitude = world_position.y - get_3d_terrain_point_data_elevation (&terrain_info);

			altitude = max (altitude, 0.0f);

			back_g_e_force += ((0.05 - ((altitude * altitude) / (20.0 * current_flight_dynamics->main_rotor_diameter.value * current_flight_dynamics->main_rotor_diameter.value))) - back_g_e_force) * get_model_delta_time ();

			back_g_e_force = bound (back_g_e_force, 0.0, 0.05);

			if (back_g_e_force > 0.0)
			{

				back_g_e_force *= tuning_value * main_rotor_induced_air_value;

				if (current_flight_dynamics->velocity_z.max != 0.0)
				{

					back_g_e_force *= (current_flight_dynamics->velocity_z.max - fabs (velocity_z_value)) / current_flight_dynamics->velocity_z.max;
				}

				#if DEBUG_MODULE

				debug_log ("DYNAMICS: IGE back force %f, alt %f, y %f, el %f, x %f, z %f",
								back_g_e_force, altitude, current_flight_dynamics->position.y,
								get_3d_terrain_point_data_elevation (&terrain_info), world_position.x, world_position.z);

				create_vectored_debug_3d_object (&world_position, &direction, OBJECT_3D_ARROW_FORCES, 0, 20.0 * back_g_e_force);

				#endif

				back_g_e_force *= current_flight_dynamics->ground_effect.modifier;

				add_dynamic_force ("Back rotor Ground effect", back_g_e_force, 0.0, &position, &rotor_direction, FALSE);
			}
		}
		////////////////////////////////////////////
		// In Ground Effect on left side of rotor disc
		////////////////////////////////////////////
		{

			float
				tuning_value = 0.1;

			position.x = rotor_radius;
			position.y = 0.0;
			position.z = 0.0;

			multiply_matrix3x3_vec3d (&world_position, current_flight_dynamics->attitude, &position);

			world_position.x += current_flight_dynamics->position.x;
			world_position.y += current_flight_dynamics->position.y;
			world_position.z += current_flight_dynamics->position.z;

			bound_position_to_adjusted_map_volume (&world_position);

			get_3d_terrain_point_data (world_position.x, world_position.z, &terrain_info);

			altitude = world_position.y - get_3d_terrain_point_data_elevation (&terrain_info);

			altitude = max (altitude, 0.0f);

			left_g_e_force += ((0.05 - ((altitude * altitude) / (20.0 * current_flight_dynamics->main_rotor_diameter.value * current_flight_dynamics->main_rotor_diameter.value))) - left_g_e_force) * get_model_delta_time ();

			left_g_e_force = bound (left_g_e_force, 0.0, 0.05);

			if (left_g_e_force > 0.0)
			{

				left_g_e_force *= tuning_value * main_rotor_induced_air_value;

				if (current_flight_dynamics->velocity_z.max != 0.0)
				{

					left_g_e_force *= (current_flight_dynamics->velocity_z.max - fabs (velocity_z_value)) / current_flight_dynamics->velocity_z.max;
				}

				#if DEBUG_MODULE

				debug_log ("DYNAMICS: IGE left force %f, alt %f, y %f, el %f, x %f, z %f",
								left_g_e_force, altitude, current_flight_dynamics->position.y,
								get_3d_terrain_point_data_elevation (&terrain_info), world_position.x, world_position.z);

				create_vectored_debug_3d_object (&world_position, &direction, OBJECT_3D_ARROW_FORCES, 0, 20.0 * left_g_e_force);

				#endif

				left_g_e_force *= current_flight_dynamics->ground_effect.modifier;

				add_dynamic_force ("Left rotor Ground effect", left_g_e_force, 0.0, &position, &rotor_direction, FALSE);
			}
		}
		////////////////////////////////////////////
		// In Ground Effect on right side of rotor disc
		////////////////////////////////////////////
		{

			float
				tuning_value = 0.1;

			position.x = -rotor_radius;
			position.y = 0.0;
			position.z = 0.0;

			multiply_matrix3x3_vec3d (&world_position, current_flight_dynamics->attitude, &position);

			world_position.x += current_flight_dynamics->position.x;
			world_position.y += current_flight_dynamics->position.y;
			world_position.z += current_flight_dynamics->position.z;

			bound_position_to_adjusted_map_volume (&world_position);

			get_3d_terrain_point_data (world_position.x, world_position.z, &terrain_info);

			altitude = world_position.y - get_3d_terrain_point_data_elevation (&terrain_info);

			altitude = max (altitude, 0.0f);

			right_g_e_force += ((0.05 - ((altitude * altitude) / (20.0 * current_flight_dynamics->main_rotor_diameter.value * current_flight_dynamics->main_rotor_diameter.value))) - right_g_e_force) * get_model_delta_time ();

			right_g_e_force = bound (right_g_e_force, 0.0, 0.05);

			if (right_g_e_force > 0.0)
			{

				right_g_e_force *= tuning_value * main_rotor_induced_air_value;

				if (current_flight_dynamics->velocity_z.max != 0.0)
				{

					right_g_e_force *= (current_flight_dynamics->velocity_z.max - fabs (velocity_z_value)) / current_flight_dynamics->velocity_z.max;
				}

				#if DEBUG_MODULE

				debug_log ("DYNAMICS: IGE right force %f, alt %f, y %f, el %f, x %f, z %f",
								right_g_e_force, altitude, current_flight_dynamics->position.y,
								get_3d_terrain_point_data_elevation (&terrain_info), world_position.x, world_position.z);

				create_vectored_debug_3d_object (&world_position, &direction, OBJECT_3D_ARROW_FORCES, 0, 20.0 * right_g_e_force);

				#endif

				right_g_e_force *= current_flight_dynamics->ground_effect.modifier;

				add_dynamic_force ("Right rotor Ground effect", right_g_e_force, 0.0, &position, &rotor_direction, FALSE);
			}
		}
	}
	////////////////////////////////////////////
	// Vortex ring
	////////////////////////////////////////////
	if ((!model_landed) &&
		(get_current_dynamics_options (DYNAMICS_OPTIONS_VORTEX_RING)) &&
		(!(current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_MAIN_ROTOR)))
	{
		float air_over_rotor = -fabs(main_rotor_induced_air_value) * mass_percentage - model_motion_vector.y;
		float vibration_limit = -fabs(main_rotor_induced_air_value) - model_motion_vector.y * 0.6;
		float velocity_factor = max (((current_flight_dynamics->main_rotor_induced_vortex_air_flow.min -
					   fabs (model_motion_vector.z)) / current_flight_dynamics->main_rotor_induced_vortex_air_flow.min), 0.0f);

		// arneh - create vibration when close to vortex ring state
		if (vibration_limit > 0.0 &&  velocity_factor > 0.0)
			create_rotor_vibration(bound(vibration_limit * 0.3 * velocity_factor, 0.0, 1.0));

		if (air_over_rotor > 0.0)     //model_motion_vector.y < -fabs (main_rotor_induced_air_value))
		{

			force = current_flight_dynamics->main_rotor_induced_vortex_air_flow.modifier * fabs (main_rotor_induced_air_value) * velocity_factor;

			force *= deg (current_flight_dynamics->main_blade_pitch.value);

			position.x = 0.0;
			position.y = 0.0;
			position.z = 0.0;

			direction.x = 0.0;
			direction.y = -1.0;
			direction.z = 0.0;

			add_dynamic_force ("Vortex ring force", force, 0.0, &position, &direction, FALSE);
		}
	}

	////////////////////////////////////////////
	// Wind
	////////////////////////////////////////////
	if ((!model_landed) &&
		(get_current_dynamics_options (DYNAMICS_OPTIONS_WIND)) &&
		(!(current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_MAIN_ROTOR)))
	{

		static float
			force = 0.0,
			desired_force = 0.0;

		position.x = current_flight_dynamics->position.x;
		position.y = current_flight_dynamics->position.y;
		position.z = current_flight_dynamics->position.z;

		get_session_wind_velocity_at_point (&position, &direction);

		position.x = current_flight_dynamics->rotation_origin.x;
		position.y = current_flight_dynamics->rotation_origin.y;
		position.z = current_flight_dynamics->rotation_origin.z;

		multiply_transpose_matrix3x3_vec3d (&direction, attitude, &direction);

		normalise_any_3d_vector (&direction);

		force += (desired_force - force) * get_model_delta_time ();

		if ((fabs (force - desired_force) < 0.001))
		{

			desired_force = frand1 () * get_model_delta_time ();
		}

		add_dynamic_force ("Wind", force, 0.0, &position, &direction, FALSE);
	}
	////////////////////////////////////////////

	// If colliding with something, then the collision will move the helicopter. Combined with gravity
	// and no drag this can make the helicopter fall down hillsides very rapidly.  So add some "friction"
	// so it won't move as fast.
	if (fixed_collision_count)
	{

		float
			force;

		vec3d
			direction,
			position;

		direction = current_flight_dynamics->model_motion_vector;

		direction.x += current_flight_dynamics->model_acceleration_vector.x * get_model_delta_time ();
		direction.y += current_flight_dynamics->model_acceleration_vector.y * get_model_delta_time ();
		direction.z += current_flight_dynamics->model_acceleration_vector.z * get_model_delta_time ();

		force = 3.0 * get_3d_vector_magnitude(&direction);// / get_model_delta_time ();

		invert_3d_vector (&direction);

		normalise_any_3d_vector (&direction);

		position.x = 0.0;
		position.y = 0.0;
		position.z = 0.0;

		add_dynamic_force ("Ground Friction force", force, 0.0, &position, &direction, TRUE);

		#if DEBUG_MODULE

		multiply_matrix3x3_vec3d (&direction, current_flight_dynamics->attitude, &direction);

		position.x += current_flight_dynamics->position.x;
		position.y += current_flight_dynamics->position.y;
		position.z += current_flight_dynamics->position.z;

		create_vectored_debug_3d_object (&position, &direction, OBJECT_3D_ARROW_FORCES, 0, 5 * force);

		#endif
	}
		// arneh - add vibration if rotor damaged
	if (current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_MAIN_ROTOR_BLADE || current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_MAIN_ROTOR)
		create_advanced_rotor_vibration(2, TRUE);
}
