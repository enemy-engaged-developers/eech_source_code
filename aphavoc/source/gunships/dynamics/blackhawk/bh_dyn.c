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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

#include "ai/parser/parsgen.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static dynamics_type
	advanced_flight_dynamics;

static float
	right_g_e_force = 0.0,
	left_g_e_force = 0.0,
	back_g_e_force = 0.0,
	front_g_e_force = 0.0,
	this_reaction_force = 0.0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_dynamics_defaults (entity *en);

static void update_main_rotor_dynamics (void);

static void update_tail_rotor_dynamics (void);

static void update_main_rotor_rpm_dynamics (void);

static void update_tail_rotor_rpm_dynamics (void);

static void update_main_rotor_coning_angle (void);

static void update_main_rotor_thrust_dynamics (void);

static void update_tail_rotor_thrust_dynamics (void);

static void update_attitude_dynamics (void);

static void update_power_dynamics (void);

static void update_air_density_dynamics (void);

static void update_acceleration_dynamics (void);

static void update_power_dynamics (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_blackhawk_advanced_dynamics (entity *en)
{

	current_flight_dynamics = &advanced_flight_dynamics;

	memset (current_flight_dynamics, 0, sizeof (dynamics_type));

	set_dynamics_defaults (en);

	current_flight_dynamics->sub_type = ENTITY_SUB_TYPE_AIRCRAFT_UH60_BLACK_HAWK;

	sprintf (current_flight_dynamics->filename, "..\\common\\data\\blckhwk.dyn");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_dynamics_defaults (entity *en)
{

	vec3d
		position;

	memset (current_flight_dynamics, 0, sizeof (dynamics_type));

	if (parser_flight_dynamics_options == 0)
	{

		set_current_dynamics_options (DYNAMICS_OPTIONS_CROSS_COUPLING, get_global_dynamics_options_cross_coupling());
		set_current_dynamics_options (DYNAMICS_OPTIONS_DAMAGE, get_global_dynamics_options_damage());
		set_current_dynamics_options (DYNAMICS_OPTIONS_DRAW_FLIGHT_PATH, get_global_dynamics_options_draw_flight_path());
		set_current_dynamics_options (DYNAMICS_OPTIONS_GROUND_COLLISIONS, get_global_dynamics_options_ground_collisions());
		set_current_dynamics_options (DYNAMICS_OPTIONS_GROUND_EFFECT, get_global_dynamics_options_ground_effect());
		set_current_dynamics_options (DYNAMICS_OPTIONS_KEYBOARD_ASSISTANCE, get_global_dynamics_options_keyboard_assistance());
		set_current_dynamics_options (DYNAMICS_OPTIONS_OBJECT_COLLISIONS, get_global_dynamics_options_object_collisions());
		set_current_dynamics_options (DYNAMICS_OPTIONS_OVER_TORQUE, get_global_dynamics_options_over_torque());
		set_current_dynamics_options (DYNAMICS_OPTIONS_RETREATING_BLADE_STALL, get_global_dynamics_options_retreating_blade_stall());
		set_current_dynamics_options (DYNAMICS_OPTIONS_REVERSE_THROTTLE_INPUT, get_global_dynamics_options_reverse_throttle_input());
		set_current_dynamics_options (DYNAMICS_OPTIONS_TRANSITIONAL_LIFT, get_global_dynamics_options_transitional_lift());
		set_current_dynamics_options (DYNAMICS_OPTIONS_VORTEX_RING, get_global_dynamics_options_vortex_ring());
		set_current_dynamics_options (DYNAMICS_OPTIONS_WIND, get_global_dynamics_options_wind());
	}
	else
	{

		unsigned int
			flag;

		dynamics_options_types
			option;

		flag = parser_flight_dynamics_options;

		option = DYNAMICS_OPTIONS_CROSS_COUPLING;

		while (option < NUM_DYNAMICS_OPTIONS_TYPES)
		{

			if (flag & (1 << option))
			{

				set_current_dynamics_options (option, TRUE);

				#if DEBUG_MODULE

				debug_log ("DYNAMICS: flight dynamics %s = %d", dynamics_options_type_names [option], TRUE);

				#endif
			}

			option ++;
		}
	}

	// set default modifier values

	current_flight_dynamics->undercarriage_state.modifier = 1.0;
	current_flight_dynamics->apu_rpm.modifier = 1.0;
	current_flight_dynamics->left_engine_rpm.modifier = 1.0;
	current_flight_dynamics->left_engine_torque.modifier = 1.0;
	current_flight_dynamics->left_engine_temp.modifier = 1.0;
	current_flight_dynamics->right_engine_rpm.modifier = 1.0;
	current_flight_dynamics->right_engine_torque.modifier = 1.0;
	current_flight_dynamics->right_engine_temp.modifier = 1.0;
	current_flight_dynamics->main_rotor_number_of_blades.modifier = 1.0;
	current_flight_dynamics->main_rotor_induced_air.modifier = 0.5;
	current_flight_dynamics->main_rotor_induced_vortex_air_flow.modifier = 0.3;
	current_flight_dynamics->main_rotor_diameter.modifier = 1.0;
	current_flight_dynamics->main_rotor_area.modifier = 1.0;
	current_flight_dynamics->main_rotor_thrust.modifier = 1.0;
	current_flight_dynamics->main_rotor_roll_angle.modifier = 1.0;
	current_flight_dynamics->main_rotor_pitch_angle.modifier = 1.0;
	current_flight_dynamics->main_rotor_rpm.modifier = 1.0;
	current_flight_dynamics->main_rotor_rps.modifier = 1.0;
	current_flight_dynamics->main_rotor_coning_angle.modifier = 1.0;
	current_flight_dynamics->main_rotor_angular_position.modifier = 1.0;
	current_flight_dynamics->main_rotor_angular_increment.modifier = 1.0;
	current_flight_dynamics->main_blade_pitch.modifier = 1.0;
	current_flight_dynamics->main_blade_x_pitch.modifier = 1.0;
	current_flight_dynamics->main_blade_y_pitch.modifier = 1.0;
	current_flight_dynamics->main_rotor_swash_plate_pitch.modifier = 1.0;
	current_flight_dynamics->main_rotor_swash_plate_roll.modifier = 1.0;
	current_flight_dynamics->tail_rotor_induced_air.modifier = 1.0;
	current_flight_dynamics->tail_rotor_diameter.modifier = 1.0;
	current_flight_dynamics->tail_rotor_thrust.modifier = 1.0;
	current_flight_dynamics->tail_rotor_rpm.modifier = 1.0;
	current_flight_dynamics->tail_rotor_rps.modifier = 1.0;
	current_flight_dynamics->tail_rotor_angular_position.modifier = 1.0;
	current_flight_dynamics->tail_blade_pitch.modifier = 1.0;
	current_flight_dynamics->tail_boom_length.modifier = 1.0;
	current_flight_dynamics->cross_coupling_effect.modifier = 1.0;
	current_flight_dynamics->power_avaliable.modifier = 1.0;
	current_flight_dynamics->power_required.modifier = 1.0;
	current_flight_dynamics->power_induced.modifier = 1.0;
	current_flight_dynamics->power_profile.modifier = 1.0;
	current_flight_dynamics->power_parasite.modifier = 1.0;
	current_flight_dynamics->power_surplus.modifier = 1.0;
	current_flight_dynamics->velocity_x.modifier = 1.0;
	current_flight_dynamics->velocity_y.modifier = 1.0;
	current_flight_dynamics->velocity_z.modifier = 1.0;
	current_flight_dynamics->acceleration_x.modifier = 1.0;
	current_flight_dynamics->acceleration_y.modifier = 1.0;
	current_flight_dynamics->acceleration_z.modifier = 1.0;
	current_flight_dynamics->world_velocity_x.modifier = 1.0;
	current_flight_dynamics->world_velocity_y.modifier = 1.0;
	current_flight_dynamics->world_velocity_z.modifier = 1.0;
	current_flight_dynamics->air_density.modifier = 1.0;
	current_flight_dynamics->pitch.modifier = 1.0;
	current_flight_dynamics->roll.modifier = 1.0;
	current_flight_dynamics->heading.modifier = 1.0;
	current_flight_dynamics->lift.modifier = 1.0;
	current_flight_dynamics->translational_lift.modifier = 0.01;
	current_flight_dynamics->altitude.modifier = 1.0;
	current_flight_dynamics->drag_x.modifier = 1.0;
	current_flight_dynamics->drag_y.modifier = 1.0;
	current_flight_dynamics->drag_z.modifier = 1.0;
	current_flight_dynamics->heading_inertia.modifier = 1.0;
	current_flight_dynamics->pitch_inertia.modifier = 1.0;
	current_flight_dynamics->roll_inertia.modifier = 1.0;
	current_flight_dynamics->heading_moment.modifier = 1.0;
	current_flight_dynamics->pitch_moment.modifier = 1.0;
	current_flight_dynamics->roll_moment.modifier = 1.0;
	current_flight_dynamics->heading_moment_reaction.modifier = 1.0;
	current_flight_dynamics->pitch_moment_reaction.modifier = 1.0;
	current_flight_dynamics->roll_moment_reaction.modifier = 1.0;
	current_flight_dynamics->angular_heading_acceleration.modifier = 1.0;
	current_flight_dynamics->angular_pitch_acceleration.modifier = 1.0;
	current_flight_dynamics->angular_roll_acceleration.modifier = 1.0;
	current_flight_dynamics->angular_heading_velocity.modifier = 1.0;
	current_flight_dynamics->angular_pitch_velocity.modifier = 1.0;
	current_flight_dynamics->angular_roll_velocity.modifier = 1.0;
	current_flight_dynamics->landing_quality.modifier = 1.0;
	current_flight_dynamics->mass.modifier = 1.0;
	current_flight_dynamics->weapon_mass.modifier = 1.0;
	current_flight_dynamics->ground_effect.modifier = 1.5;
	current_flight_dynamics->indicated_airspeed.modifier = 1.0;
	current_flight_dynamics->indicated_slip.modifier = 1.0;
	current_flight_dynamics->barometric_altitude.modifier = 1.0;
	current_flight_dynamics->radar_altitude.modifier = 1.0;
	current_flight_dynamics->g_force.modifier = 1.0;
	current_flight_dynamics->combined_engine_rpm.modifier = 1.0;
	current_flight_dynamics->combined_engine_torque.modifier = 1.0;
	current_flight_dynamics->fuel_weight.modifier = 1.0;

	//

	get_local_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &position);

	current_flight_dynamics->dynamics_damage = DYNAMICS_DAMAGE_NONE;
	current_flight_dynamics->repairing_damage = DYNAMICS_DAMAGE_NONE;

	// input values

	current_flight_dynamics->input_data.collective.value = 0.0;
	current_flight_dynamics->input_data.collective.min = 0.0;
	current_flight_dynamics->input_data.collective.max = 120;

	current_flight_dynamics->input_data.cyclic_x_trim.value = 0.0;
	current_flight_dynamics->input_data.cyclic_y_trim.value = 6.0;

	current_flight_dynamics->input_data.cyclic_x.min = -100.0;
	current_flight_dynamics->input_data.cyclic_x.max = 100.0;

	current_flight_dynamics->input_data.cyclic_y.min = -100.0;
	current_flight_dynamics->input_data.cyclic_y.max = 100.0;

	current_flight_dynamics->input_data.cyclic_horizontal_pressure.min = -100.0;
	current_flight_dynamics->input_data.cyclic_horizontal_pressure.max = 100.0;

	current_flight_dynamics->input_data.cyclic_vertical_pressure.min = -100.0;
	current_flight_dynamics->input_data.cyclic_vertical_pressure.max = 100.0;

	current_flight_dynamics->input_data.collective_pressure.min = -5.0;
	current_flight_dynamics->input_data.collective_pressure.max = 5.0;

	current_flight_dynamics->input_data.pedal.min = -100.0;
	current_flight_dynamics->input_data.pedal.max = 100.0;

	current_flight_dynamics->input_data.pedal_pressure.min = -10.0;
	current_flight_dynamics->input_data.pedal_pressure.max = 10.0;

	// general

	current_flight_dynamics->undercarriage_state.damaged = FALSE;
	current_flight_dynamics->undercarriage_state.value = 1.0;
	current_flight_dynamics->undercarriage_state.min = 1.0;
	current_flight_dynamics->undercarriage_state.max = 1.0;

	current_flight_dynamics->repairing = TRUE;
	current_flight_dynamics->refuelling = TRUE;

	current_flight_dynamics->position.x = position.x;
	current_flight_dynamics->position.y = position.y;
	current_flight_dynamics->position.z = position.z;

	// attitutde

	get_identity_matrix3x3 (current_flight_dynamics->attitude);

	current_flight_dynamics->roll.min = rad (-360.0);
	current_flight_dynamics->roll.max = rad (360.0);

	current_flight_dynamics->pitch.min = rad (-360.0);
	current_flight_dynamics->pitch.max = rad (360.0);

	current_flight_dynamics->air_density.value = 1.0;
	current_flight_dynamics->air_density.max = 1.0;
	current_flight_dynamics->air_density.min = 0.0;

	current_flight_dynamics->altitude.min = 0.0;
	current_flight_dynamics->altitude.max = 20000.0;

	// engine characteristics
	current_flight_dynamics->apu_rpm.value = 0.0;
	current_flight_dynamics->apu_rpm.min = 0.0;
	current_flight_dynamics->apu_rpm.max = 0.0;
	current_flight_dynamics->apu_rpm.damaged = FALSE;

	current_flight_dynamics->left_engine_rpm.value = 0.0;
	current_flight_dynamics->left_engine_rpm.max = 100.0;  // engine is always trying for 100% N2 RPM
	current_flight_dynamics->left_engine_n1_rpm.value = 0.0;
	current_flight_dynamics->left_engine_n1_rpm.max = 100.0;
	current_flight_dynamics->left_engine_torque.value = 0.0;
	current_flight_dynamics->left_engine_torque.max = 120.0;

	current_flight_dynamics->left_engine_temp.value = 800.0;
	current_flight_dynamics->left_engine_temp.max = 1000.0;

	current_flight_dynamics->right_engine_rpm.value = 0.0;
	current_flight_dynamics->right_engine_rpm.max = 100.0;
	current_flight_dynamics->right_engine_n1_rpm.value = 0.0;
	current_flight_dynamics->right_engine_n1_rpm.max = 100.0;
	current_flight_dynamics->right_engine_torque.value = 0.0;
	current_flight_dynamics->right_engine_torque.max = 120.0;

	current_flight_dynamics->right_engine_temp.value = 800.0;
	current_flight_dynamics->right_engine_temp.max = 1000.0;

	// main rotor characteristics

	current_flight_dynamics->main_rotor_diameter.value = 14.63;
	current_flight_dynamics->main_rotor_area.value = PI * pow ((current_flight_dynamics->main_rotor_diameter.value / 2.0), 2);

	current_flight_dynamics->main_rotor_induced_air.value = 0.0;
	current_flight_dynamics->main_rotor_induced_air.min = 0.0;
	current_flight_dynamics->main_rotor_induced_air.max = 26.0;

	current_flight_dynamics->main_rotor_induced_vortex_air_flow.min = knots_to_metres_per_second (10.0); // actually used for the max velocity for vortex ring to occur

	current_flight_dynamics->main_rotor_roll_angle.min = rad (-5.5);
	current_flight_dynamics->main_rotor_roll_angle.max = rad (5.5);

	current_flight_dynamics->main_rotor_pitch_angle.min = rad (-5.5);
	current_flight_dynamics->main_rotor_pitch_angle.max = rad (5.5);

	current_flight_dynamics->main_rotor_thrust.value = 0.0;
	current_flight_dynamics->main_rotor_thrust.min = 0.0;
	current_flight_dynamics->main_rotor_thrust.max = 100.0;

	current_flight_dynamics->main_rotor_rpm.value = 0.0;
	current_flight_dynamics->main_rotor_rpm.min = 0.0;
	current_flight_dynamics->main_rotor_rpm.max = 100.0;

	current_flight_dynamics->main_rotor_rps.value = 0.0;
	current_flight_dynamics->main_rotor_rps.min = 0.0;
	current_flight_dynamics->main_rotor_rps.max = 4.5;

	current_flight_dynamics->main_rotor_angular_position.value = 0;
	current_flight_dynamics->main_rotor_angular_position.min = 0;
	current_flight_dynamics->main_rotor_angular_position.max = PI2;

	current_flight_dynamics->main_rotor_coning_angle.min = rad (-3.0);
	current_flight_dynamics->main_rotor_coning_angle.max = rad (4.0);

	current_flight_dynamics->main_blade_pitch.value = 2.0;
	current_flight_dynamics->main_blade_pitch.min = rad (1.0);
	current_flight_dynamics->main_blade_pitch.max = rad (7.5);

	// tail rotor characteristics

	current_flight_dynamics->tail_rotor_diameter.value = 2.79;

	current_flight_dynamics->tail_rotor_rpm.value = 0.0;
	current_flight_dynamics->tail_rotor_rpm.min = 0.0;
	current_flight_dynamics->tail_rotor_rpm.max = 100.0;

	current_flight_dynamics->tail_rotor_rps.value = 0.0;
	current_flight_dynamics->tail_rotor_rps.min = 0.0;
	current_flight_dynamics->tail_rotor_rps.max = 10;

	current_flight_dynamics->tail_rotor_angular_position.value = 0;
	current_flight_dynamics->tail_rotor_angular_position.min = 0;
	current_flight_dynamics->tail_rotor_angular_position.max = PI2;

	current_flight_dynamics->tail_rotor_thrust.value = 0.0;
	current_flight_dynamics->tail_rotor_thrust.min = 0.0;
	current_flight_dynamics->tail_rotor_thrust.max = 100.0;

	current_flight_dynamics->tail_blade_pitch.value = 0.0;
	current_flight_dynamics->tail_blade_pitch.min = rad (-2.0);
	current_flight_dynamics->tail_blade_pitch.max = rad (2.0);

	current_flight_dynamics->tail_rotor_induced_air.value = 0.0;
	current_flight_dynamics->tail_rotor_induced_air.min = -1.0;
	current_flight_dynamics->tail_rotor_induced_air.max = 1.0;

	current_flight_dynamics->tail_boom_length.value = 10.59; // actually the wheelbase (but close enough)

	current_flight_dynamics->cross_coupling_effect.value = 0.0;

	// other

	current_flight_dynamics->velocity_x.min = -11.1;
	current_flight_dynamics->velocity_x.max = 11.1;

	current_flight_dynamics->model_acceleration_vector.x = 0.0;
	current_flight_dynamics->model_acceleration_vector.y = 0.0;
	current_flight_dynamics->model_acceleration_vector.z = 0.0;

	current_flight_dynamics->world_acceleration_vector.x = 0.0;
	current_flight_dynamics->world_acceleration_vector.y = 0.0;
	current_flight_dynamics->world_acceleration_vector.z = 0.0;

	current_flight_dynamics->velocity_y.value = 0.0;
	current_flight_dynamics->velocity_y.min = -1000.0;
	current_flight_dynamics->velocity_y.max = 15.7;

	current_flight_dynamics->velocity_z.min = -8.33;
	current_flight_dynamics->velocity_z.max = knots_to_metres_per_second (190);

	current_flight_dynamics->power_avaliable.min = 0.0;
	current_flight_dynamics->power_avaliable.max = 1890.0;

	current_flight_dynamics->lift.min = -10.0;
	current_flight_dynamics->lift.max = 20.0;

	current_flight_dynamics->translational_lift.value = 3.0;
	current_flight_dynamics->translational_lift.min = 8.0;
	current_flight_dynamics->translational_lift.max = 15.0;

	current_flight_dynamics->heading_moment.value = 0.0;
	current_flight_dynamics->heading_moment_reaction.value = 0.0;

	current_flight_dynamics->pitch_moment.value = 0.0;
	current_flight_dynamics->pitch_moment_reaction.value = 0.0;

	current_flight_dynamics->roll_moment.value = 0.0;
	current_flight_dynamics->roll_moment_reaction.value = 0.0;

	// drag

	current_flight_dynamics->drag_x.min = 0.01;
	current_flight_dynamics->drag_x.max = 0.1;

	current_flight_dynamics->drag_y.min = 0.01;
	current_flight_dynamics->drag_y.max = 0.1;

	current_flight_dynamics->drag_z.min = 0.01;
	current_flight_dynamics->drag_z.max = 0.1;

	// inertia

	current_flight_dynamics->heading_inertia.value = 5.0;
	current_flight_dynamics->pitch_inertia.value = 40.0;
	current_flight_dynamics->roll_inertia.value = 30.0;

	// mass

	current_flight_dynamics->mass.value = 0.0;
	current_flight_dynamics->mass.min = 5480.0;
	current_flight_dynamics->mass.max = 0.0;

	current_flight_dynamics->fuel_weight.value = 1136.36;
	current_flight_dynamics->fuel_weight.min = 0.0;
	current_flight_dynamics->fuel_weight.max = 1136.36;
	current_flight_dynamics->fuel_weight.delta = 0.1450; // kg/s

	// cog
	// havoc at 	0.0, -0.2, -0.022
	// apache at 	0.0, -0.2, -0.012

	current_flight_dynamics->centre_of_gravity.x = 0.00;
	current_flight_dynamics->centre_of_gravity.y = -0.2;
	current_flight_dynamics->centre_of_gravity.z = -0.012;

	// landing
	// havoc at 	1.0, 3.0, 7.0, 10.0
	// apache at 	0.75, 2.5, 6.0, 9.0 - good, ok, heavy, crash

	current_flight_dynamics->landing_quality.min = -0.75;
	current_flight_dynamics->landing_quality.delta = -2.5;
	current_flight_dynamics->landing_quality.value = -6.0;
	current_flight_dynamics->landing_quality.max = -9.0;

	// g force

	current_flight_dynamics->g_force.value = 1.0;

	//
	// debug to start with engine on.
	//

	// havoc 1
	// apache -1

	current_flight_dynamics->rotor_rotation_direction = -1.0;

	current_flight_dynamics->rotor_brake = TRUE;

	current_flight_dynamics->auto_hover = HOVER_HOLD_NONE;

	current_flight_dynamics->wheel_brake = TRUE;

	//if (get_local_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE) != OPERATIONAL_STATE_LANDED)
	{

		float
			Mrpm,
			Md,
			Pmax,
			Tl;

		current_flight_dynamics->rotor_brake = FALSE;

		current_flight_dynamics->auto_hover = HOVER_HOLD_NONE;

		current_flight_dynamics->wheel_brake = FALSE;

		// cross coupling to match main rotor rpm

		Mrpm = current_flight_dynamics->main_rotor_rpm.value;

		Md = current_flight_dynamics->main_rotor_diameter.value;

		Pmax = current_flight_dynamics->tail_blade_pitch.max;

		Tl = current_flight_dynamics->tail_boom_length.value;

		current_flight_dynamics->cross_coupling_effect.value = (((200 * PI * Mrpm * Md * Pmax) / (1649 * Tl))) / (Pmax);
	}

	right_g_e_force = 0.0;
	left_g_e_force = 0.0;
	back_g_e_force = 0.0;
	front_g_e_force = 0.0;
	this_reaction_force = 0.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_blackhawk_advanced_dynamics (void)
{
	float
		rpm, workload=0.0, total_rpm, left_power_ratio;

	update_power_dynamics ();

	update_apu_rpm_dynamics();
	update_engine_rpm_dynamics(1);
	update_engine_rpm_dynamics(2);

	update_engine_temperature_dynamics (1);
	update_engine_temperature_dynamics (2);

	update_main_rotor_dynamics ();

	update_tail_rotor_dynamics ();

	update_main_rotor_rpm_dynamics ();

	update_tail_rotor_rpm_dynamics ();

	update_main_rotor_coning_angle ();

	update_main_rotor_thrust_dynamics ();

	update_tail_rotor_thrust_dynamics ();

	update_power_dynamics ();

	update_air_density_dynamics ();

	update_acceleration_dynamics ();

	update_attitude_dynamics ();

	resolve_dynamic_forces ();

	update_dynamics_external_values ();

	// Leave the last iteration of forces to allow the draw function to work.
	if (get_current_dynamics_options (DYNAMICS_OPTIONS_DRAW_FLIGHT_PATH))
	{

		if (current_flight_dynamics->model_iterations > 0)
		{

			update_dynamic_forces ();
		}
	}
	else
	{

		update_dynamic_forces ();
	}

	//debug

	//Werewolf engine torque management
	//Rotor RPM is reduced by workload, so we have to have twice as much workload on the engine to circumvent the whacky way EECH mixes RPM into the engine torque
	if (command_line_dynamics_advanced_engine_model == TRUE)
	{
	  workload = ((float) fabs (current_flight_dynamics->main_rotor_pitch_angle.value) + (float) fabs (current_flight_dynamics->main_rotor_roll_angle.value))
		  * 100.0;
	  workload = bound (workload, 0.0, 100.0);
	}

	// arneh - distribute torque among engines depending on the N1 RPM of each engine
	total_rpm = bound(current_flight_dynamics->left_engine_n1_rpm.value - 55.0, 0.0, 100.0) +
		bound(current_flight_dynamics->right_engine_n1_rpm.value - 55.0, 0.0, 100.0);
	if (total_rpm > 0.0)
		left_power_ratio = bound(current_flight_dynamics->left_engine_n1_rpm.value -55.0, 0.0, 100.0) / total_rpm;
	else
		left_power_ratio = 0.5;

	if (!current_flight_dynamics->left_engine_torque.damaged)
	{
		rpm = 0.0;

		if (current_flight_dynamics->main_rotor_rpm.max != 0.0)
		{
			float rotor_rpm_diff = current_flight_dynamics->main_rotor_rpm.value - current_flight_dynamics->left_engine_rpm.value;

			rpm = current_flight_dynamics->main_rotor_rpm.value / current_flight_dynamics->main_rotor_rpm.max;
			rpm *= 0.5 + left_power_ratio;
			if (rotor_rpm_diff > 0.0)
				rpm *= 1.0 - bound(rotor_rpm_diff * 0.75, 0.0, 1.0);
		}

//Werewolf: engine torque should INCREASE when the aircraft works harder
//Rotor RPM drops under workload, so we use twice as much workload here to make the torque sum increase under workload
		current_flight_dynamics->left_engine_torque.value += ((current_flight_dynamics->input_data.collective.value * rpm) - current_flight_dynamics->left_engine_torque.value) * (4.0 * get_model_delta_time ());
		if (command_line_dynamics_advanced_engine_model == TRUE)
		  current_flight_dynamics->left_engine_torque.value += (workload) * (4.0 * get_model_delta_time ());
	}
	else
	{

		current_flight_dynamics->left_engine_torque.value -= current_flight_dynamics->left_engine_torque.value * get_model_delta_time ();
	}

	if (!current_flight_dynamics->right_engine_torque.damaged)
	{
		rpm = 0.0;

		if (current_flight_dynamics->main_rotor_rpm.max != 0.0)
		{
			float rotor_rpm_diff = current_flight_dynamics->main_rotor_rpm.value - current_flight_dynamics->right_engine_rpm.value;

			rpm = current_flight_dynamics->main_rotor_rpm.value / current_flight_dynamics->main_rotor_rpm.max;
			rpm *= 0.5 + (1.0 - left_power_ratio);
			if (rotor_rpm_diff > 0.0)
				rpm *= 1.0 - bound(rotor_rpm_diff * 0.75, 0.0, 1.0);
		}

//Werewolf
		current_flight_dynamics->right_engine_torque.value += ((current_flight_dynamics->input_data.collective.value * rpm) - current_flight_dynamics->right_engine_torque.value) * (4.0 * get_model_delta_time ());
		if (command_line_dynamics_advanced_engine_model == TRUE)
			current_flight_dynamics->right_engine_torque.value += (workload) * (4.0 * get_model_delta_time ());
	}
	else
	{

		current_flight_dynamics->right_engine_torque.value -= current_flight_dynamics->right_engine_torque.value * get_model_delta_time ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_main_rotor_dynamics (void)
{

	float
		coll,
		average_blade_input,
		rotor_roll,
		rotor_pitch,
		blade_pitch;

	// main rotor angular position

	if (current_flight_dynamics->main_rotor_rpm.max != 0.0)
	{

		current_flight_dynamics->main_rotor_rps.value = 4.5 * (current_flight_dynamics->main_rotor_rpm.value / current_flight_dynamics->main_rotor_rpm.max);

		current_flight_dynamics->main_rotor_angular_position.value += current_flight_dynamics->main_rotor_rps.value * PI2 * get_model_delta_time ();
	}

	if (current_flight_dynamics->main_rotor_angular_position.value >= PI2)
	{

		current_flight_dynamics->main_rotor_angular_position.value -= PI2;
	}
	else if (current_flight_dynamics->main_rotor_angular_position.value < 0)
	{

		current_flight_dynamics->main_rotor_angular_position.value += PI2;
	}

	// calculate blade pitch 0->5 Degs. collective = blade_pitch^3

	current_flight_dynamics->main_blade_x_pitch.value = (current_flight_dynamics->main_blade_pitch.max - current_flight_dynamics->main_blade_pitch.min) *
						(current_flight_dynamics->input_data.cyclic_x.value / 100.0) + current_flight_dynamics->main_blade_pitch.min;

	current_flight_dynamics->main_blade_y_pitch.value = (current_flight_dynamics->main_blade_pitch.max - current_flight_dynamics->main_blade_pitch.min) *
						(current_flight_dynamics->input_data.cyclic_y.value / 100.0) + current_flight_dynamics->main_blade_pitch.min;

	coll = current_flight_dynamics->input_data.collective.value / 100.0;

	coll *= coll;

	coll *= 100.0;

	average_blade_input = coll;

	average_blade_input = bound (average_blade_input, 0.0, 100.0);

	blade_pitch = (current_flight_dynamics->main_blade_pitch.max - current_flight_dynamics->main_blade_pitch.min) *
						(average_blade_input / 100.0) + current_flight_dynamics->main_blade_pitch.min;

	if (!current_flight_dynamics->main_blade_pitch.damaged)
	{

		current_flight_dynamics->main_blade_pitch.value = blade_pitch;
	}
	else
	{

		current_flight_dynamics->main_blade_pitch.value = 0.0;
	}

	current_flight_dynamics->main_blade_pitch.value = bound (
																current_flight_dynamics->main_blade_pitch.value,
																current_flight_dynamics->main_blade_pitch.min,
																current_flight_dynamics->main_blade_pitch.max);

	// calculate 'Tip Plane Path' roll and pitch

	// roll

	rotor_roll = (current_flight_dynamics->input_data.cyclic_x.value / (current_flight_dynamics->input_data.cyclic_x.max - current_flight_dynamics->input_data.cyclic_x.min)) *
					(current_flight_dynamics->main_rotor_roll_angle.max - current_flight_dynamics->main_rotor_roll_angle.min);

	if (!current_flight_dynamics->main_rotor_roll_angle.damaged)
	{

		current_flight_dynamics->main_rotor_roll_angle.value = rotor_roll;
	}
	else
	{

		current_flight_dynamics->main_rotor_roll_angle.value = 0.0;
	}

	current_flight_dynamics->main_rotor_roll_angle.value = bound (
																current_flight_dynamics->main_rotor_roll_angle.value,
																current_flight_dynamics->main_rotor_roll_angle.min,
																current_flight_dynamics->main_rotor_roll_angle.max);

	// pitch

	rotor_pitch = -(current_flight_dynamics->input_data.cyclic_y.value / (current_flight_dynamics->input_data.cyclic_y.max - current_flight_dynamics->input_data.cyclic_y.min)) *
					(current_flight_dynamics->main_rotor_pitch_angle.max - current_flight_dynamics->main_rotor_pitch_angle.min);

	if (!current_flight_dynamics->main_rotor_pitch_angle.damaged)
	{

		current_flight_dynamics->main_rotor_pitch_angle.value = rotor_pitch;
	}
	else
	{

		current_flight_dynamics->main_rotor_pitch_angle.value = 0.0;
	}

	current_flight_dynamics->main_rotor_pitch_angle.value = bound (
																current_flight_dynamics->main_rotor_pitch_angle.value,
																current_flight_dynamics->main_rotor_pitch_angle.min,
																current_flight_dynamics->main_rotor_pitch_angle.max);

	// debug

	current_flight_dynamics->main_rotor_swash_plate_pitch.value = current_flight_dynamics->main_rotor_pitch_angle.value;

	current_flight_dynamics->main_rotor_swash_plate_roll.value = current_flight_dynamics->main_rotor_roll_angle.value;

	// end
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_tail_rotor_dynamics (void)
{

	float
		pedal,
		blade_pitch;

	// tail rotor angular position

	current_flight_dynamics->tail_rotor_angular_position.value += current_flight_dynamics->tail_rotor_rps.value * PI2 * get_model_delta_time ();

	if (current_flight_dynamics->tail_rotor_angular_position.value >= PI2)
	{

		current_flight_dynamics->tail_rotor_angular_position.value -= PI2;
	}
	else if (current_flight_dynamics->tail_rotor_angular_position.value < 0)
	{

		current_flight_dynamics->tail_rotor_angular_position.value += PI2;
	}

	// calculate blade pitch 0->5 Degs, linearly

	pedal = current_flight_dynamics->input_data.pedal.value;

	blade_pitch = rad (pedal / (current_flight_dynamics->input_data.pedal.max / deg (current_flight_dynamics->tail_blade_pitch.max)));

	current_flight_dynamics->tail_blade_pitch.delta = 2.0 * (blade_pitch - current_flight_dynamics->tail_blade_pitch.value);

	if (!current_flight_dynamics->tail_blade_pitch.damaged)
	{

		current_flight_dynamics->tail_blade_pitch.value += current_flight_dynamics->tail_blade_pitch.delta * get_model_delta_time ();
	}
	else
	{

		current_flight_dynamics->tail_blade_pitch.value = 0.0;
	}

	current_flight_dynamics->tail_blade_pitch.value = bound (
																current_flight_dynamics->tail_blade_pitch.value,
																current_flight_dynamics->tail_blade_pitch.min,
																current_flight_dynamics->tail_blade_pitch.max);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_main_rotor_rpm_dynamics (void)
{

	int
		number_of_engines;

	float
		max_delta,
		auto_min_delta,
		blade_pitch,
		rotor_rpm,
		rpm_min,
		rpm_max,
		rotor_workload = 0.0;

	rpm_min = current_flight_dynamics->main_rotor_rpm.min;

	rpm_max = current_flight_dynamics->main_rotor_rpm.max;
	max_delta = 100.0 / 20.0;
	auto_min_delta = -100.0 / 4.0;

	blade_pitch = ((current_flight_dynamics->main_blade_pitch.value - current_flight_dynamics->main_blade_pitch.min) /
						(current_flight_dynamics->main_blade_pitch.max - current_flight_dynamics->main_blade_pitch.min));

	if ((!current_flight_dynamics->rotor_brake) && (!current_flight_dynamics->main_rotor_rpm.damaged))
	{

		// brake off

		rotor_rpm = 0.0;

		number_of_engines = 2 - current_flight_dynamics->left_engine_rpm.damaged - current_flight_dynamics->right_engine_rpm.damaged;

		//Werewolf - Rotor RPM depending on workload
		if (command_line_dynamics_advanced_engine_model == TRUE)
		{
		  rotor_workload = ((float) fabs (current_flight_dynamics->main_rotor_pitch_angle.value) + (float) fabs (current_flight_dynamics->main_rotor_roll_angle.value))
				  * 30.0;
		  rotor_workload = bound (rotor_workload, 0.0, 100.0);
		  //debug_log ( "Rotor Workload=%.2f ", rotor_workload);
		}

		if (number_of_engines)
		{
			// arneh - rotor spins at the speed of the fastest engine
			rotor_rpm = max(current_flight_dynamics->left_engine_rpm.value, current_flight_dynamics->right_engine_rpm.value);
			if (command_line_dynamics_advanced_engine_model == TRUE)
			  rotor_rpm -= rotor_workload; //Werewolf
		}

		current_flight_dynamics->main_rotor_rpm.delta = rotor_rpm - current_flight_dynamics->main_rotor_rpm.value;
		current_flight_dynamics->main_rotor_rpm.delta = bound (current_flight_dynamics->main_rotor_rpm.delta, -max_delta, max_delta);
	}
	else
	{
		// arneh - rotor brake on (rotor disengaged)
		// modelling of how autorotation affects rotor RPM

		float
			induced_drag, profile_drag,
			autorotational_acceleration,
			rpm_ratio, air_flow,
			autorotation_factor = 1.6,
			induced_drag_factor = 8.0,
			profile_drag_factor = 2.0;

		// when not engaged to engine, rpm may exceed max
		// (but rotor will fail before reaching the new limit)
		rpm_max *= 1.5;
		rpm_ratio = current_flight_dynamics->main_rotor_rpm.value / rpm_max;

		if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AIRBORNE_AIRCRAFT))
		{
			air_flow = get_3d_vector_magnitude (&current_flight_dynamics->model_motion_vector);

			// function of vertical speed through air, but adjusted for blade pitch, which reduces the autorotational part of the rotor
			// at about 10 m/s drag and autorotational acceleration should cancel each other out (all other things being ideal)
			autorotational_acceleration = current_flight_dynamics->g_force.value *
				-(current_flight_dynamics->velocity_y.value / 10.0) *
				max(0.6 - blade_pitch, 0.0);

			// induced drag on rotor.  drops sharpy up to 60kts, slowly after that
			// clean air produces less drag, hence a hover (where lots of vortexes
			// creates dirty air) has the most induced drag
			induced_drag = blade_pitch * (1.0 - rpm_ratio);
			if (air_flow < knots_to_metres_per_second(60))
				induced_drag *= 1.0 - (air_flow / knots_to_metres_per_second(60) * 0.6);
			else
				induced_drag *= 0.6 - (air_flow / knots_to_metres_per_second(200) * 0.3);

			// profile drag increases with speed and rotor rpm
			profile_drag = rpm_ratio * (0.5 + 0.5 * blade_pitch) *
				(0.5 + 0.4 * fabs(current_flight_dynamics->velocity_z.value / current_flight_dynamics->velocity_z.max) +
				fabs(current_flight_dynamics->velocity_x.value / current_flight_dynamics->velocity_z.max));

			// calulate change in rotor RPM.  The factors for autorotational_acceleration,
			// profile_drag and induced_drag have been arrived at by experimentation.
			// Feel free to change the factors if you feel they are wrong.
			current_flight_dynamics->main_rotor_rpm.delta = max_delta *
				(autorotation_factor * autorotational_acceleration -
				 profile_drag_factor * profile_drag -
				 induced_drag_factor * induced_drag);

			bound (current_flight_dynamics->main_rotor_rpm.delta, auto_min_delta, max_delta);
		}
		else
		{

			current_flight_dynamics->main_rotor_rpm.delta = -5.0;
		}

		//debug_log ("DYNAMICS: rotor rpm %f delta %f, velocity y %f, accelaration y %f", current_flight_dynamics->main_rotor_rpm.value, current_flight_dynamics->main_rotor_rpm.delta, current_flight_dynamics->velocity_y.value, current_flight_dynamics->velocity_y.delta);
	}

	current_flight_dynamics->main_rotor_rpm.value += current_flight_dynamics->main_rotor_rpm.delta * get_model_delta_time ();
	current_flight_dynamics->main_rotor_rpm.value = bound (current_flight_dynamics->main_rotor_rpm.value, rpm_min, rpm_max);

	// arneh - damage rotor if rpm too high (can only happen when rotor is disengaged)
	if (current_flight_dynamics->main_rotor_rpm.value > 125.0)
		dynamics_damage_model(DYNAMICS_DAMAGE_MAIN_ROTOR, FALSE);

	// low rotor speech
	if ((current_flight_dynamics->main_rotor_rpm.value < 60.0) && (current_flight_dynamics->main_rotor_rpm.delta < 0.0) && (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AIRBORNE_AIRCRAFT)))
	{

		static float
			time = 0.0;

		time -= get_model_delta_time ();

		if (time <= 0.0)
		{

			play_client_server_warning_message (get_gunship_entity (), SPEECH_SYSTEM_LOW_ROTOR_RPM);

			time = DYNAMICS_LOW_ROTOR_RPM_SPEECH_TIME;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_tail_rotor_rpm_dynamics (void)
{

	int
		number_of_engines;

	float
		engine_rpm,
		rpm_min,
		rpm_max,
		rpm;

	rpm_min = current_flight_dynamics->tail_rotor_rpm.min;

	rpm_max = current_flight_dynamics->tail_rotor_rpm.max;

	number_of_engines = 2 - current_flight_dynamics->left_engine_rpm.damaged - current_flight_dynamics->right_engine_rpm.damaged;

	engine_rpm = 0.0;

	if (number_of_engines)
	{

		engine_rpm = (current_flight_dynamics->left_engine_rpm.value + current_flight_dynamics->right_engine_rpm.value) / number_of_engines;
	}

	rpm = 0.0;
	if (!current_flight_dynamics->tail_rotor_rpm.damaged)
	{
		if (!current_flight_dynamics->rotor_brake)
			rpm = engine_rpm;
		// arneh, june 2006 - when rotor is disengaged from engines, main rotor drives tail rotor
		else
			rpm = current_flight_dynamics->main_rotor_rpm.value;
	}

	current_flight_dynamics->tail_rotor_rpm.delta = rpm - current_flight_dynamics->tail_rotor_rpm.value;

	current_flight_dynamics->tail_rotor_rpm.delta = bound (current_flight_dynamics->tail_rotor_rpm.delta, -10.0, 10.0);

	current_flight_dynamics->tail_rotor_rpm.value += current_flight_dynamics->tail_rotor_rpm.delta * get_model_delta_time ();

	current_flight_dynamics->tail_rotor_rpm.value = bound (current_flight_dynamics->tail_rotor_rpm.value, rpm_min, rpm_max);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_main_rotor_coning_angle (void)
{

	float
		coning_angle,
		lift,
		rx,
		cx,
		cm;

	// simple, linear coning from Cmin to Cmax over Rx wrt lift.

	rx = current_flight_dynamics->lift.max;
	cx = current_flight_dynamics->main_rotor_coning_angle.max;
	cm = current_flight_dynamics->main_rotor_coning_angle.min;
	lift = current_flight_dynamics->lift.value;

	// arneh - multiply with inverse rotor rpm, as high rotor rpm creates centrifugal force to counteract the lift
	coning_angle = (((cx - cm) / rx) * lift + cm) * 100.0 / current_flight_dynamics->main_rotor_rpm.value;

	current_flight_dynamics->main_rotor_coning_angle.value += (coning_angle - current_flight_dynamics->main_rotor_coning_angle.value) * get_model_delta_time ();

	current_flight_dynamics->main_rotor_coning_angle.value = bound (current_flight_dynamics->main_rotor_coning_angle.value,
																current_flight_dynamics->main_rotor_coning_angle.min,
																current_flight_dynamics->main_rotor_coning_angle.max);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_main_rotor_thrust_dynamics (void)
{

	float
		rpm_ratio,
		x_max,
		x_min,
		x;

	x_max = current_flight_dynamics->main_blade_pitch.max;

	x_min = current_flight_dynamics->main_blade_pitch.min;

	x = current_flight_dynamics->main_blade_pitch.value;

	//  arneh - let rotor have thrust even when rotor is disengaged from engine
	// if (!current_flight_dynamics->rotor_brake)
	{

		rpm_ratio = 0.0;

		if (current_flight_dynamics->main_rotor_rpm.max)
		{

			rpm_ratio = current_flight_dynamics->main_rotor_rpm.value / current_flight_dynamics->main_rotor_rpm.max;
		}

		// loss of lift due to rotating the helicopter about the y axis.

		if (fabs (current_flight_dynamics->main_rotor_rps.value) > 1.0)
		{

			if (current_flight_dynamics->main_rotor_rps.value != 0.0)
			{

				rpm_ratio -= command_line_dynamics_yaw_altitude_loss * (current_flight_dynamics->heading.delta / (2 * PI * current_flight_dynamics->main_rotor_rps.value * get_model_delta_time ()));
			}
		}

		current_flight_dynamics->main_rotor_induced_air.value =
			rpm_ratio * (current_flight_dynamics->main_rotor_induced_air.min +
			(current_flight_dynamics->main_rotor_induced_air.max - current_flight_dynamics->main_rotor_induced_air.min) *
			(x - x_min) / (x_max - x_min));

		current_flight_dynamics->main_rotor_induced_air.value *=
			(current_flight_dynamics->air_density.value / current_flight_dynamics->air_density.max);
	}

	current_flight_dynamics->main_rotor_thrust.value =
		2.0 * current_flight_dynamics->air_density.value * current_flight_dynamics->main_rotor_area.value *
		((current_flight_dynamics->main_rotor_induced_air.value - (current_flight_dynamics->velocity_y.value / 10.0)) *
		current_flight_dynamics->main_rotor_induced_air.value);

	// debug everything seems to powerful..
	current_flight_dynamics->main_rotor_thrust.value /= 16.0;
	// end debug

	//debug_log ("main induced %f, cross %f, main pitch value %f", current_flight_dynamics->main_rotor_induced_air.value, current_flight_dynamics->cross_coupling_effect.value, current_flight_dynamics->main_blade_pitch.value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_tail_rotor_thrust_dynamics (void)
{

	// the thrust_at_0.. will cause a constant yaw input = correct.

	float
		desired,
		Mrpm,
		Md,
		Pmax,
		Tl,
		blade_pitch_induced_thrust_percentage;

	Mrpm = current_flight_dynamics->main_rotor_rpm.value;

	Md = current_flight_dynamics->main_rotor_diameter.value;

	Pmax = current_flight_dynamics->tail_blade_pitch.max;

	Tl = current_flight_dynamics->tail_boom_length.value;

	// arneh - when rotor is disengaged it produces no torque, so 0 tail rotor adjustment is desired
	if (current_flight_dynamics->rotor_brake ||
		(!current_flight_dynamics->cross_coupling_effect.damaged) &&
		(get_current_dynamics_options (DYNAMICS_OPTIONS_CROSS_COUPLING)))
		desired = 0.0;
	else
		desired = (((200 * PI * Mrpm * Md * Pmax) / (1649 * Tl))) / (Pmax);

	current_flight_dynamics->cross_coupling_effect.value += (desired - current_flight_dynamics->cross_coupling_effect.value) * get_model_delta_time ();

	blade_pitch_induced_thrust_percentage = (((100.0 - current_flight_dynamics->cross_coupling_effect.value) /
															current_flight_dynamics->tail_blade_pitch.max) *
															current_flight_dynamics->tail_blade_pitch.value +
															current_flight_dynamics->cross_coupling_effect.value) / 100.0;

	current_flight_dynamics->tail_rotor_induced_air.value = 0.0;

	if (current_flight_dynamics->tail_rotor_rpm.max != 0.0)
	{

		current_flight_dynamics->tail_rotor_induced_air.value = (current_flight_dynamics->tail_rotor_rpm.value / current_flight_dynamics->tail_rotor_rpm.max) *
																					(blade_pitch_induced_thrust_percentage / 2.0);
	}

	//debug_log ("tail induced %f, cross %f, tail pitch value %f", current_flight_dynamics->tail_rotor_induced_air.value, current_flight_dynamics->cross_coupling_effect.value, current_flight_dynamics->tail_blade_pitch.value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_attitude_dynamics (void)
{

	int
		model_landed;

	matrix3x3
		attitude;

	float
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
		main_angular_force,
		tail_angular_force;

	float
		main_rotor_induced_air_value,
		main_rotor_pitch_angle_value,
		main_rotor_rpm_value,
		main_rotor_roll_angle_value,
		tail_rotor_induced_air_value,
		heading_inertia_value,
		pitch_inertia_value,
		roll_inertia_value,
		pitch_value,
		main_blade_x_pitch_value,
		main_blade_y_pitch_value,
		velocity_z_value,
		horizontal_velocity,
		main_blade_pitch_value;

	vec3d
		wind,
		model_wind,
		position,
		direction,
		world_motion_vector,
		model_motion_vector;

	model_landed = !get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AIRBORNE_AIRCRAFT);

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
	if (motion_vector_magnitude > 1000)
	{

		debug_log ("DYNAMICS: UNSTABLE");

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

	main_rotor_induced_air_value = current_flight_dynamics->main_rotor_induced_air.value * current_flight_dynamics->main_rotor_induced_air.modifier;
	main_rotor_pitch_angle_value = current_flight_dynamics->main_rotor_pitch_angle.value * current_flight_dynamics->main_rotor_pitch_angle.modifier;
	main_rotor_rpm_value = current_flight_dynamics->main_rotor_rpm.value * current_flight_dynamics->main_rotor_rpm.modifier;
	main_rotor_roll_angle_value = current_flight_dynamics->main_rotor_roll_angle.value * current_flight_dynamics->main_rotor_roll_angle.modifier;
	tail_rotor_induced_air_value = current_flight_dynamics->tail_rotor_induced_air.value * current_flight_dynamics->tail_rotor_induced_air.modifier;
	heading_inertia_value = current_flight_dynamics->heading_inertia.value * current_flight_dynamics->heading_inertia.modifier;
	pitch_inertia_value = current_flight_dynamics->pitch_inertia.value * current_flight_dynamics->pitch_inertia.modifier;
	roll_inertia_value = current_flight_dynamics->roll_inertia.value * current_flight_dynamics->roll_inertia.modifier;
	pitch_value = current_flight_dynamics->pitch.value * current_flight_dynamics->pitch.modifier;
	main_blade_x_pitch_value = current_flight_dynamics->main_blade_x_pitch.value * current_flight_dynamics->main_blade_x_pitch.modifier;
	main_blade_y_pitch_value = current_flight_dynamics->main_blade_y_pitch.value * current_flight_dynamics->main_blade_y_pitch.modifier;
	velocity_z_value = current_flight_dynamics->velocity_z.value * current_flight_dynamics->velocity_z.modifier;
	main_blade_pitch_value = current_flight_dynamics->main_blade_pitch.value * current_flight_dynamics->main_blade_pitch.modifier;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Rotor Force Analysis
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	angle = 1.0;

	rotor_split = 0.90;

	edge_rotor_split = 1.0 - rotor_split;

	edge_rotor_split /= 8.0;

	rotor_edge_value = 0.401681;

	////////////////////////////////////////////
	// Taxiing
	////////////////////////////////////////////
	if (!get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AIRBORNE_AIRCRAFT))
	{

		// rotor

		rotor_force = main_rotor_induced_air_value * 35.0;// ball park number to give about 50kts at 60%

		direction.x = 0.0;
		direction.y = 0.0;
		direction.z = bound (-main_rotor_pitch_angle_value, -1.0, 1.0);

		position.x = 0.0;
		position.y = 0.0;
		position.z = 0.0;

		add_dynamic_force ("Taxiing force", rotor_force, 0.0, &position, &direction, FALSE);
	}

	////////////////////////////////////////////
	// middle of rotor disc
	////////////////////////////////////////////
	{

		rotor_force = rotor_split * main_rotor_induced_air_value;

		if ((current_flight_dynamics->rotor_brake) && (current_flight_dynamics->main_rotor_rpm.max != 0.0))
		{

			rotor_force *= main_rotor_rpm_value / current_flight_dynamics->main_rotor_rpm.max;
		}

		position.x = 0.0;
		position.y = 0.0;
		position.z = 0.0;

		direction.x = 0.0;
		direction.y = 1.0;
		direction.z = 0.0;

		add_dynamic_force ("Middle rotor force", command_line_dynamics_main_rotor_lift * rotor_force, 0.0, &position, &direction, FALSE);
	}

	////////////////////////////////////////////
	// front of rotor disc
	////////////////////////////////////////////
	{

		angle = main_rotor_pitch_angle_value;

		front_rotor_force = rotor_edge_value +
				(0.6 * angle) / (current_flight_dynamics->main_rotor_pitch_angle.max - current_flight_dynamics->main_rotor_pitch_angle.min) +
				(0.2 * current_flight_dynamics->input_data.collective.value) / (current_flight_dynamics->input_data.collective.max - current_flight_dynamics->input_data.collective.min);

		if ((current_flight_dynamics->rotor_brake) && (current_flight_dynamics->main_rotor_rpm.max != 0.0))
		{

			front_rotor_force *= main_rotor_rpm_value / current_flight_dynamics->main_rotor_rpm.max;
		}

		if (model_landed)
		{

			position.x = 0.0;
			position.y = 0.0;
			position.z = 0.0;
		}
		else
		{

			position.x = 0.0;
			position.y = 0.0;
			position.z = 7.299;
		}

		direction.x = 0.0;
		direction.y = 1.0;
		direction.z = 0.0;

		add_dynamic_force ("Front rotor force", command_line_dynamics_main_rotor_lift * front_rotor_force, 0.0, &position, &direction, FALSE);
	}
	////////////////////////////////////////////
	// back of rotor disc
	////////////////////////////////////////////
	{

		angle = main_rotor_pitch_angle_value;

		back_rotor_force = rotor_edge_value -
				(0.6 * angle) / (current_flight_dynamics->main_rotor_pitch_angle.max - current_flight_dynamics->main_rotor_pitch_angle.min) +
				(0.2 * current_flight_dynamics->input_data.collective.value) / (current_flight_dynamics->input_data.collective.max - current_flight_dynamics->input_data.collective.min);

		if ((current_flight_dynamics->rotor_brake) && (current_flight_dynamics->main_rotor_rpm.max != 0.0))
		{

			back_rotor_force *= main_rotor_rpm_value / current_flight_dynamics->main_rotor_rpm.max;
		}

		if (model_landed)
		{

			position.x = 0.0;
			position.y = 0.0;
			position.z = 0.0;
		}
		else
		{

			position.x = 0.0;
			position.y = 0.0;
			position.z = -7.299;
		}

		direction.x = 0.0;
		direction.y = 1.0;
		direction.z = 0.0;

		add_dynamic_force ("Back rotor force", command_line_dynamics_main_rotor_lift * back_rotor_force, 0.0, &position, &direction, FALSE);
	}
	////////////////////////////////////////////
	// left of rotor disc
	////////////////////////////////////////////
	{

		angle = main_rotor_roll_angle_value;

		left_rotor_force = rotor_edge_value -
				(0.6 * angle) / (current_flight_dynamics->main_rotor_roll_angle.max - current_flight_dynamics->main_rotor_roll_angle.min) +
				(0.2 * current_flight_dynamics->input_data.collective.value) / (current_flight_dynamics->input_data.collective.max - current_flight_dynamics->input_data.collective.min);

		if ((current_flight_dynamics->rotor_brake) && (current_flight_dynamics->main_rotor_rpm.max != 0.0))
		{

			left_rotor_force *= main_rotor_rpm_value / current_flight_dynamics->main_rotor_rpm.max;
		}

		if (model_landed)
		{

			position.x = 0.0;
			position.y = 0.0;
			position.z = 0.0;
		}
		else
		{

			position.x = 7.299;
			position.y = 0.0;
			position.z = 0.0;
		}

		direction.x = 0.0;
		direction.y = 1.0;
		direction.z = 0.0;

		add_dynamic_force ("Left rotor force", command_line_dynamics_main_rotor_lift * left_rotor_force, 0.0, &position, &direction, FALSE);
	}
	////////////////////////////////////////////
	// right of rotor disc
	////////////////////////////////////////////
	{

		angle = main_rotor_roll_angle_value;

		right_rotor_force = rotor_edge_value +
				(0.6 * angle) / (current_flight_dynamics->main_rotor_roll_angle.max - current_flight_dynamics->main_rotor_roll_angle.min) +
				(0.2 * current_flight_dynamics->input_data.collective.value) / (current_flight_dynamics->input_data.collective.max - current_flight_dynamics->input_data.collective.min);

		if ((current_flight_dynamics->rotor_brake) && (current_flight_dynamics->main_rotor_rpm.max != 0.0))
		{

			right_rotor_force *= main_rotor_rpm_value / current_flight_dynamics->main_rotor_rpm.max;
		}

		if (model_landed)
		{

			position.x = 0.0;
			position.y = 0.0;
			position.z = 0.0;
		}
		else
		{

			position.x = -7.299;
			position.y = 0.0;
			position.z = 0.0;
		}

		direction.x = 0.0;
		direction.y = 1.0;
		direction.z = 0.0;

		add_dynamic_force ("Right rotor force", command_line_dynamics_main_rotor_lift * right_rotor_force, 0.0, &position, &direction, FALSE);
	}
	////////////////////////////////////////////
	// tail rotor disc
	////////////////////////////////////////////
	{

		tail_angular_force = tail_rotor_induced_air_value * current_flight_dynamics->tail_boom_length.value;
		tail_angular_force *= heading_inertia_value;

		position.x = 0.0;
		position.y = -0.08022;
		position.z = -current_flight_dynamics->tail_boom_length.value;

		direction.x = current_flight_dynamics->rotor_rotation_direction;
		direction.y = 0.0;
		direction.z = 0.0;

		if (model_landed)
		{

			position.y = 0.0;

			if ((current_flight_dynamics->input_data.pedal_input_pressure != PEDAL_PRESSURE_LEFT) &&
				(current_flight_dynamics->input_data.pedal_input_pressure != PEDAL_PRESSURE_RIGHT))
			{

				tail_angular_force = 0.0;
			}
			else
			{

				tail_angular_force *= min (fabs (velocity_z_value) / 15.0, 1.0);
			}
		}

		add_dynamic_force ("Angular tail rotor force", tail_angular_force, 0.0, &position, &direction, FALSE);
	}

	////////////////////////////////////////////
	// gravity
	////////////////////////////////////////////
	{

		float
			mass_percentage;

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

		add_dynamic_force ("Gravity", force, 0.0, &position, &direction, FALSE);
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

	////////////////////////////////////////////
	// Transitional Lift generated by 'Wing' effect
	////////////////////////////////////////////
	//if ((!model_landed) &&
	if ((get_current_dynamics_options (DYNAMICS_OPTIONS_TRANSITIONAL_LIFT)) &&
		(!(current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_MAIN_ROTOR)))
	{

		vec3d
			wind,
			position,
			normalised_model_motion_vector;

		float
			force,
			vel;

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

		vel = normalise_any_3d_vector (&normalised_model_motion_vector);

		// * 3 because induced air at normal is 9 and max is about 26... needs to scale 0.0 -> 1.0
		vel *= min (fabs ((3.0 * current_flight_dynamics->main_rotor_induced_air.value) / (current_flight_dynamics->main_rotor_induced_air.max - current_flight_dynamics->main_rotor_induced_air.min)), 1.0);

		if (vel >= current_flight_dynamics->translational_lift.min)
		{

			if (vel <= current_flight_dynamics->translational_lift.max)
			{

				force = (current_flight_dynamics->translational_lift.value * (vel - current_flight_dynamics->translational_lift.min)) / (current_flight_dynamics->translational_lift.max - current_flight_dynamics->translational_lift.min);
			}
			else
			{

				force = current_flight_dynamics->translational_lift.value;
			}

			position.x = (current_flight_dynamics->translational_lift.modifier * current_flight_dynamics->main_rotor_diameter.value / 2.0) * normalised_model_motion_vector.x;
			position.y = 0.0;
			position.z = (current_flight_dynamics->translational_lift.modifier * current_flight_dynamics->main_rotor_diameter.value / 2.0) * normalised_model_motion_vector.z;

			direction.x = 0.0;
			direction.y = 1.0;
			direction.z = 0.0;

			add_dynamic_force ("Transitional lift", force, 0.0, &position, &direction, FALSE);
/*
			// debug
			{
				multiply_matrix3x3_vec3d (&position, current_flight_dynamics->attitude, &position);

				multiply_matrix3x3_vec3d (&direction, current_flight_dynamics->attitude, &direction);

				position.x += current_flight_dynamics->position.x;
				position.y += current_flight_dynamics->position.y;
				position.z += current_flight_dynamics->position.z;

				create_vectored_debug_3d_object (&position, &direction, OBJECT_3D_ARROW_FORCES, 0, 10.0);
			}
			// debug
*/
		}
		{
			float
				motion_vector_pitch;

			vec3d
				normalised_world_motion_vector;

			normalised_world_motion_vector = world_motion_vector;
			normalise_any_3d_vector (&normalised_world_motion_vector);
			motion_vector_pitch = asin (normalised_world_motion_vector.y) - aircraft_database [current_flight_dynamics->sub_type].main_rotor_shaft_angle;

			if (current_flight_dynamics->model_motion_vector.z < 0.0)
			{

				pitch_value *= -1.0;
			}

			force = horizontal_velocity *
						((pitch_value +
						main_rotor_pitch_angle_value) -
						motion_vector_pitch);

			force = max (force, 0.0);

			position.x = -0.4 * sin (main_blade_x_pitch_value);
			position.y = 0.0;
			position.z = 0.4 * sin (main_blade_y_pitch_value);

			direction.x = 0.0;
			direction.y = 1.0;
			direction.z = 0.0;

			// arneh - this force seems too strong, impossible to decend faster than
			// about 7-8 m/s by default with forward speed. So reduce it a little
			force *= 0.9;
			add_dynamic_force ("Transitional lift", force, 0.0, &position, &direction, FALSE);
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Secondary effects
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////
	// Retreating blade lift loss
	////////////////////////////////////////////
	if (get_current_dynamics_options (DYNAMICS_OPTIONS_RETREATING_BLADE_STALL))
	{

		if (!(get_current_dynamics_options (DYNAMICS_OPTIONS_KEYBOARD_ASSISTANCE) && (get_global_cyclic_input () == KEYBOARD_INPUT)))
		{

			if (!(current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_MAIN_ROTOR))
			{

				left_rotor_force = 0.25 * ((edge_rotor_split * main_rotor_induced_air_value) -
							((edge_rotor_split * main_rotor_induced_air_value * main_rotor_roll_angle_value) /
							(current_flight_dynamics->main_rotor_roll_angle.max - current_flight_dynamics->main_rotor_roll_angle.min)));

				left_rotor_force *= (motion_vector_magnitude *
											motion_vector_magnitude *
											motion_vector_magnitude) /
											(current_flight_dynamics->velocity_z.max *
											current_flight_dynamics->velocity_z.max *
											current_flight_dynamics->velocity_z.max);

				left_rotor_force *= command_line_dynamics_retreating_blade_stall_effect;

				position.x = 7.299;
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
	if (get_current_dynamics_options (DYNAMICS_OPTIONS_RETREATING_BLADE_STALL))
	{

		if (!(get_current_dynamics_options (DYNAMICS_OPTIONS_KEYBOARD_ASSISTANCE) && (get_global_cyclic_input () == KEYBOARD_INPUT)))
		{

			if (!(current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_MAIN_ROTOR))
			{

				right_rotor_force = 0.25 * ((edge_rotor_split * main_rotor_induced_air_value) +
							((edge_rotor_split * main_rotor_induced_air_value * main_rotor_roll_angle_value) /
							(current_flight_dynamics->main_rotor_roll_angle.max - current_flight_dynamics->main_rotor_roll_angle.min)));

				right_rotor_force *= (motion_vector_magnitude *
											motion_vector_magnitude *
											motion_vector_magnitude) /
											(current_flight_dynamics->velocity_z.max *
											current_flight_dynamics->velocity_z.max *
											current_flight_dynamics->velocity_z.max);

				right_rotor_force *= command_line_dynamics_retreating_blade_stall_effect;

				position.x = -7.299;
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

		// 0.2 defines the buildup
		force = sfrand1 () * exp (0.2 * (velocity_z_value - current_flight_dynamics->velocity_z.max));

		// scale on blade pitch.
		force *= ((current_flight_dynamics->main_blade_pitch.value - current_flight_dynamics->main_blade_pitch.min) / (current_flight_dynamics->main_blade_pitch.max - current_flight_dynamics->main_blade_pitch.min));

		if (fabs (force) > 2.0)
		{

			dynamics_damage_model (DYNAMICS_DAMAGE_MAIN_ROTOR, FALSE);

			force = bound (force, -2.0, 2.0);
		}
		else if (fabs (force) > 1.0)
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
		}

		position.x = -7.299;
		position.y = 0.0;
		position.z = 0.0;

		direction.x = 0.0;
		direction.y = current_flight_dynamics->rotor_rotation_direction;
		direction.z = 0.0;

		add_dynamic_force ("Sonic buildup", force, 0.0, &position, &direction, FALSE);
	}
	////////////////////////////////////////////
	// main rotor disc torque effect
	////////////////////////////////////////////
	//if (!model_landed)
	{
		// arneh - main rotor produces no torque when disengaged from
		// engine or if running with cross coupling enabled
		if (current_flight_dynamics->rotor_brake ||
			(!current_flight_dynamics->cross_coupling_effect.damaged) &&
			(get_current_dynamics_options (DYNAMICS_OPTIONS_CROSS_COUPLING)))
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
				engine_response = 8.0,
				blade_pitch,
				a,
				u,
				rotor_friction,
				rotor_parasitic,
				rotor_induced,
				rotor_drag;

			u = main_rotor_rpm_value;

			blade_pitch = bound (main_blade_pitch_value, current_flight_dynamics->main_blade_pitch.min, current_flight_dynamics->main_blade_pitch.max);

			blade_pitch = main_blade_pitch_value - current_flight_dynamics->main_blade_pitch.min;

			////////////////////////////////////////////////////////////

			relative_air_flow_angle = 0.0;

			rotor_friction = u * f;
			rotor_parasitic = (u * u) * p;
			rotor_induced = (u * u) * i * deg (fabs (blade_pitch + relative_air_flow_angle));
			rotor_drag = rotor_friction + rotor_parasitic + rotor_induced;

			if (current_flight_dynamics->rotor_brake)
			{

				a = rotor_drag / mass;
			}
			else
			{

				a = (torque - rotor_drag) / mass;
			}

			v = u + (a * get_model_delta_time ());

			// engine management

			torque += engine_response * (100.0 - (v + (a * res))) * get_model_delta_time ();
			torque = bound (torque, 0.0, 120.0);

			main_angular_force = heading_inertia_value * (torque * 2.0 * PI * (current_flight_dynamics->main_rotor_diameter.value / 2.0)) / 1649.0;

			position.x = 0.0;
			position.y = -0.08022;
			position.z = -current_flight_dynamics->tail_boom_length.value;

			direction.x = -current_flight_dynamics->rotor_rotation_direction;
			direction.y = 0.0;
			direction.z = 0.0;

			main_angular_force = (2 * 9) - main_angular_force;

			if (model_landed)
			{

				position.y = 0.0;

				if ((current_flight_dynamics->input_data.pedal_input_pressure != PEDAL_PRESSURE_LEFT) &&
					(current_flight_dynamics->input_data.pedal_input_pressure != PEDAL_PRESSURE_RIGHT))
				{

					main_angular_force = 0.0;
				}
				else
				{

					main_angular_force *= min (fabs (current_flight_dynamics->velocity_z.value) / 15.0, 1.0);
				}
			}

			add_dynamic_force ("Main rotor angular torque", main_angular_force, 0.0, &position, &direction, FALSE);
		}
	}
	////////////////////////////////////////////
	// Rotor Resistance to movement (Pitch) raw delta pitch
	////////////////////////////////////////////
	{

		reaction_force = pitch_inertia_value *
							(current_flight_dynamics->pitch.delta + current_flight_dynamics->main_rotor_pitch_angle.delta);

		position.x = 0.0;
		position.y = 0.0;
		position.z = 7.299;

		direction.x = 0.0;
		direction.y = -1.0;
		direction.z = 0.0;

		add_dynamic_force ("Pitch resistance", reaction_force, 0.0, &position, &direction, FALSE);
	}
	////////////////////////////////////////////
	// Rotor Resistance to movement (Roll)
	////////////////////////////////////////////
	{

		reaction_force = roll_inertia_value *
							(current_flight_dynamics->roll.delta + current_flight_dynamics->main_rotor_roll_angle.delta);

		position.x = 7.299;
		position.y = 0.0;
		position.z = 0.0;

		direction.x = 0.0;
		direction.y = 1.0;
		direction.z = 0.0;

		add_dynamic_force ("Roll resistance", reaction_force, 0.0, &position, &direction, FALSE);
	}
	////////////////////////////////////////////
	// Tail Rotor Resistance to movement. raw delta heading resistance
	////////////////////////////////////////////
	//if (!model_landed)
	{

		float
			a,
			scaling,
			drag;

		drag = -40.0;

		reaction_force = drag * current_flight_dynamics->heading.delta * current_flight_dynamics->tail_boom_length.value;

		a = exp (velocity_z_value / 45.0);

		if (a != 0.0)
		{

			scaling = 1.0 - (1.0 / a);
		}

		scaling = min (fabs (scaling), 1.0);

		reaction_force += (tail_angular_force - main_angular_force) * scaling;

		position.x = 0.0;
		position.y = -0.08022;
		position.z = -current_flight_dynamics->tail_boom_length.value;

		if (model_landed)
		{

			position.y = 0.0;
		}

		direction.x = 1.0;
		direction.y = 0.0;
		direction.z = 0.0;

		if (current_flight_dynamics->tail_rotor_rpm.damaged)
		{

			reaction_force *= 0.25 + 0.65 * (velocity_z_value / current_flight_dynamics->velocity_z.max);
		}

		add_dynamic_force ("Yaw resistance", reaction_force, 0.0, &position, &direction, FALSE);
	}
	////////////////////////////////////////////
	// Fuselage aerodynamics motion_vector -> attitude realignment force in the y axis
	////////////////////////////////////////////
	if ((!model_landed) &&
		(!(current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_MAIN_ROTOR)))
	{

		if (!check_zero_3d_vector (&model_motion_vector))
		{

			vec3d
				unnormalised_direction;

			direction = model_motion_vector;

			invert_3d_vector (&direction);

			unnormalised_direction = direction;

			// arneh, 20060813 - reduce banking effect on heading change at slow speed
			force = 0.0030 * (horizontal_velocity * horizontal_velocity) * current_flight_dynamics->tail_boom_length.value;
//			force = (motion_vector_magnitude * motion_vector_magnitude) / (3.5 * current_flight_dynamics->tail_boom_length.value);

			this_reaction_force += (force - this_reaction_force) * get_model_delta_time ();

			this_reaction_force = bound (this_reaction_force, -100.0, 100.0);

			normalise_any_3d_vector (&direction);

			direction.y = 0.0;
			direction.z = 0.0;

			position.x = 0.0;
			position.y = 0.0;
			position.z = -current_flight_dynamics->tail_boom_length.value;

			//Werewolf 3 Jan 04
			if (command_line_dynamics_flight_model == 1)
				this_reaction_force *= 0.5;

			add_dynamic_force ("Realign force (Y axis)", this_reaction_force, 0.0, &position, &direction, FALSE);
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Aerodynamics
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////
	// Fuselage aerodynamics motion_vector -> attitude realignment force in the x axis
	////////////////////////////////////////////
	if ((!model_landed) &&
		(!(current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_MAIN_ROTOR)))
	{

		reaction_force = 30.0 * (current_flight_dynamics->pitch.delta + current_flight_dynamics->main_rotor_pitch_angle.delta);

		if (current_flight_dynamics->velocity_z.max != 0.0)
			reaction_force *= motion_vector_magnitude / current_flight_dynamics->velocity_z.max;
		else
			reaction_force = 0.0;

		position.x = 0.0;
		position.y = 0.0;
		position.z = 7.299;

		direction.x = 0.0;
		direction.y = -1.0;
		direction.z = 0.0;

		//Werewolf 3 Jan 04
		if (command_line_dynamics_flight_model == 1)
			reaction_force *= 0.5;

		add_dynamic_force ("Realign force (X axis)", reaction_force, 0.0, &position, &direction, FALSE);
	}
	////////////////////////////////////////////
	// forward drag caused by yaw input
	////////////////////////////////////////////
	{

		float
			a;

		float
			drag;

		a = 0.0823;

		drag = a * command_line_dynamics_tail_rotor_drag * fabs (current_flight_dynamics->tail_blade_pitch.value);

		reaction_force = drag * motion_vector_magnitude * motion_vector_magnitude;

		position.x = 0.0;
		position.y = 0.0;
		position.z = 7.299;

		direction.x = 0.0;
		direction.y = 0.0;
		direction.z = -1.0;

		add_dynamic_force ("Forward motion Yaw input drag", reaction_force, 0.0, &position, &direction, FALSE);
	}
	////////////////////////////////////////////
	// Resistance to forward movement
	////////////////////////////////////////////
	if (!model_landed)
	{

		float
			sign,
			drag;

		drag = 0.00034 + (0.034 * command_line_dynamics_main_rotor_drag * max (current_flight_dynamics->pitch.value, 0.0));

		reaction_force = drag * motion_vector_magnitude * motion_vector_magnitude;

		sign = 0.0;

		if (velocity_z_value != 0.0)
		{

			sign = fabs (velocity_z_value) / velocity_z_value;
		}

		position.x = 0.0;
		position.y = 0.0;
		position.z = 7.299;

		direction.x = 0.0;
		direction.y = 0.0;
		direction.z = -1.0 * sign;

		//Werewolf 3 Jan 04
		if (command_line_dynamics_flight_model == 1)
			reaction_force *= 1.0;

		add_dynamic_force ("Forward motion drag", reaction_force, 0.0, &position, &direction, FALSE);
	}
	////////////////////////////////////////////
	// Resistance to lateral movement
	////////////////////////////////////////////
	if (!model_landed)
	{

		float
			Fmax;

		Fmax = 0.5;

		if (current_flight_dynamics->velocity_x.max != 0.0)
		{

			reaction_force = Fmax * (fabs (model_motion_vector.x) * model_motion_vector.x) / pow (current_flight_dynamics->velocity_x.max, 2.0);
		}

		position.x = 7.299;
		position.y = 0.0;
		position.z = 0.0;

		direction.x = -1.0;
		direction.y = 0.0;
		direction.z = 0.0;

		//Werewolf 3 Jan 04
		if (command_line_dynamics_flight_model == 1)
			reaction_force *= 1.0;

		add_dynamic_force ("Lateral motion drag", reaction_force, 0.0, &position, &direction, FALSE);
	}
	////////////////////////////////////////////
	// Resistance to vertical movement
	////////////////////////////////////////////
	{

		float
			drag,
			sideways_drag,
			Fmax;

		// ball park figures
		if (world_motion_vector.y < 0.0)
		{

			// y = mx + c, drag 0.4 at 0m/s ->0.0001 at -30m/s

			drag = 0.4 - (((0.4 - 0.0001) / 30.0) * -world_motion_vector.y);

			drag = bound (drag, 0.0001, 0.4);
		}
		else
		{

			drag = 0.4;
		}

		Fmax = 0.0;
		// arneh 20060813 - reduce drag in sideway flight - compensated by reduced lift.
		// makes it impossible to keep flying sideways at insane bank angles without losing altitude
		sideways_drag = 5.0 * (model_motion_vector.x * model_motion_vector.x) / pow (current_flight_dynamics->velocity_x.max, 2.0);

		if (current_flight_dynamics->main_rotor_rpm.max != 0.0)
		{

			Fmax = drag + sideways_drag + 4.5 * (main_rotor_rpm_value / current_flight_dynamics->main_rotor_rpm.max);
		}

		reaction_force = 0.0;

		if (current_flight_dynamics->velocity_y.max != 0.0)
		{

			reaction_force = Fmax * (fabs (model_motion_vector.y) * model_motion_vector.y) / pow (current_flight_dynamics->velocity_y.max, 2.0);
		}

		//
		// Only add resistane lift
		//

		if (reaction_force > 0.0)
		{

			position.x = 0.0;
			position.y = 1.0;
			position.z = 0.0;

			direction.x = 0.0;
			direction.y = -1.0;
			direction.z = 0.0;

			add_dynamic_force ("Vertical motion drag", reaction_force, 0.0, &position, &direction, FALSE);
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

			direction.x = 0.0;
			direction.y = 1.0;
			direction.z = 0.0;

			over_all_g_e_force *= current_flight_dynamics->ground_effect.modifier;

			add_dynamic_force ("Middle rotor Ground effect", over_all_g_e_force, 0.0, &position, &direction, FALSE);
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
			position.z = 7.299;

			direction.x = 0.0;
			direction.y = 1.0;
			direction.z = 0.0;

			multiply_matrix3x3_vec3d (&world_position, current_flight_dynamics->attitude, &position);

			world_position.x += current_flight_dynamics->position.x;
			world_position.y += current_flight_dynamics->position.y;
			world_position.z += current_flight_dynamics->position.z;

			bound_position_to_adjusted_map_volume (&world_position);

			get_3d_terrain_point_data (world_position.x, world_position.z, &terrain_info);

			altitude = world_position.y - get_3d_terrain_point_data_elevation (&terrain_info);

			altitude = max (altitude, 0.0);

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

				add_dynamic_force ("Front rotor Ground effect", front_g_e_force, 0.0, &position, &direction, FALSE);
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
			position.z = -7.299;

			direction.x = 0.0;
			direction.y = 1.0;
			direction.z = 0.0;

			multiply_matrix3x3_vec3d (&world_position, current_flight_dynamics->attitude, &position);

			world_position.x += current_flight_dynamics->position.x;
			world_position.y += current_flight_dynamics->position.y;
			world_position.z += current_flight_dynamics->position.z;

			bound_position_to_adjusted_map_volume (&world_position);

			get_3d_terrain_point_data (world_position.x, world_position.z, &terrain_info);

			altitude = world_position.y - get_3d_terrain_point_data_elevation (&terrain_info);

			altitude = max (altitude, 0.0);

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

				add_dynamic_force ("Back rotor Ground effect", back_g_e_force, 0.0, &position, &direction, FALSE);
			}
		}
		////////////////////////////////////////////
		// In Ground Effect on left side of rotor disc
		////////////////////////////////////////////
		{

			float
				tuning_value = 0.1;

			position.x = 7.299;
			position.y = 0.0;
			position.z = 0.0;

			direction.x = 0.0;
			direction.y = 1.0;
			direction.z = 0.0;

			multiply_matrix3x3_vec3d (&world_position, current_flight_dynamics->attitude, &position);

			world_position.x += current_flight_dynamics->position.x;
			world_position.y += current_flight_dynamics->position.y;
			world_position.z += current_flight_dynamics->position.z;

			bound_position_to_adjusted_map_volume (&world_position);

			get_3d_terrain_point_data (world_position.x, world_position.z, &terrain_info);

			altitude = world_position.y - get_3d_terrain_point_data_elevation (&terrain_info);

			altitude = max (altitude, 0.0);

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

				add_dynamic_force ("Left rotor Ground effect", left_g_e_force, 0.0, &position, &direction, FALSE);
			}
		}
		////////////////////////////////////////////
		// In Ground Effect on right side of rotor disc
		////////////////////////////////////////////
		{

			float
				tuning_value = 0.1;

			position.x = -7.299;
			position.y = 0.0;
			position.z = 0.0;

			direction.x = 0.0;
			direction.y = 1.0;
			direction.z = 0.0;

			multiply_matrix3x3_vec3d (&world_position, current_flight_dynamics->attitude, &position);

			world_position.x += current_flight_dynamics->position.x;
			world_position.y += current_flight_dynamics->position.y;
			world_position.z += current_flight_dynamics->position.z;

			bound_position_to_adjusted_map_volume (&world_position);

			get_3d_terrain_point_data (world_position.x, world_position.z, &terrain_info);

			altitude = world_position.y - get_3d_terrain_point_data_elevation (&terrain_info);

			altitude = max (altitude, 0.0);

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

				add_dynamic_force ("Right rotor Ground effect", right_g_e_force, 0.0, &position, &direction, FALSE);
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
		float air_over_rotor = -fabs(main_rotor_induced_air_value) - model_motion_vector.y;
		float vibration_limit = -fabs(main_rotor_induced_air_value) - model_motion_vector.y * 0.6;
		float velocity_factor = max (((current_flight_dynamics->main_rotor_induced_vortex_air_flow.min -
					   fabs (model_motion_vector.z)) / current_flight_dynamics->main_rotor_induced_vortex_air_flow.min), 0.0);

		// arneh - create vibration when close to vortex ring state
		if (vibration_limit > 0.0 && !(current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_MAIN_ROTOR_BLADE) && velocity_factor > 0.0)
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

		force += (desired_force - force) * get_model_delta_time ();

		if ((fabs (force - desired_force) < 0.001))
		{

			desired_force = frand1 () * get_model_delta_time ();
		}

		add_dynamic_force ("Wind", force, 0.0, &position, &direction, FALSE);
	}
	////////////////////////////////////////////

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

		force = get_3d_vector_magnitude (&direction);// / get_model_delta_time ();

		invert_3d_vector (&direction);

		normalise_any_3d_vector (&direction);

		position.x = 0.0; //direction.x * 5.0;
		position.y = 0.0; //direction.y * 5.0;
		position.z = 0.0; //direction.z * 5.0;

		add_dynamic_force ("Ground Friction force", force, 0.0, &position, &direction, FALSE);

		#if DEBUG_MODULE

		multiply_matrix3x3_vec3d (&direction, raw->ac.mob.attitude, &direction);

		position.x += current_flight_dynamics->position.x;
		position.y += current_flight_dynamics->position.y;
		position.z += current_flight_dynamics->position.z;

		create_vectored_debug_3d_object (&position, &direction, OBJECT_3D_ARROW_FORCES, 0, 5 * force);

		#endif
	}


	// arneh - add vibration if rotor damaged
	if (!model_landed && current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_MAIN_ROTOR_BLADE)
		create_rotor_vibration(1.2);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_power_dynamics (void)
{

	float
		profile_min = 20.0,
		profile_max = 40.0,
		induced_min = 50.0,
		induced_max = 30.0,
		blade_pitch,
		Vmax,
		Bmax,
		total_velocity;

	current_flight_dynamics->power_avaliable.value = current_flight_dynamics->main_rotor_thrust.value * ((current_flight_dynamics->main_rotor_induced_air.value) - (current_flight_dynamics->velocity_y.value / 10.0));

	total_velocity = (fabs (current_flight_dynamics->velocity_x.value) + fabs (current_flight_dynamics->velocity_z.value));

	blade_pitch = current_flight_dynamics->main_blade_pitch.value;

	Bmax = current_flight_dynamics->main_blade_pitch.max;

	Vmax = (current_flight_dynamics->velocity_x.max + current_flight_dynamics->velocity_z.max);

	// parasitic drag = square of velocity

	if (total_velocity)
	{

		current_flight_dynamics->power_parasite.value = (current_flight_dynamics->power_avaliable.value * pow (total_velocity, 2) / pow (Vmax, 2)) / 10;

		// rotor profile drag = linear from min to max across V

		current_flight_dynamics->power_profile.value = ((profile_max - profile_min) / Vmax) * total_velocity + profile_min;
	}
	else
	{
		current_flight_dynamics->power_parasite.value = 0;

		current_flight_dynamics->power_profile.value = profile_min;
	}

	// rotor induced power = linear wrt blade angle

	current_flight_dynamics->power_induced.value = ((induced_max - induced_min) / Bmax) * blade_pitch + induced_min;

//tg
	// induced power decreases upto 60kts and then increases. 100% @ 0kts -> 50% @ 60 kts-> 100% @ max kts

	if (current_flight_dynamics->velocity_z.value < knots_to_metres_per_second (60.0))
	{

		current_flight_dynamics->power_induced.value -= (current_flight_dynamics->power_induced.value / 2.0) * (current_flight_dynamics->velocity_z.value / knots_to_metres_per_second (60.0));
	}
	else
	{

		current_flight_dynamics->power_induced.value -= (current_flight_dynamics->power_induced.value / 2.0) * ((current_flight_dynamics->velocity_z.max - current_flight_dynamics->velocity_z.value) + knots_to_metres_per_second (60.0)) / (current_flight_dynamics->velocity_z.max);
	}

	current_flight_dynamics->power_required.value = current_flight_dynamics->power_induced.value + current_flight_dynamics->power_profile.value + current_flight_dynamics->power_parasite.value;

	current_flight_dynamics->power_required.value /= 100;

	current_flight_dynamics->power_required.value *= current_flight_dynamics->power_avaliable.max;

	current_flight_dynamics->power_surplus.value = current_flight_dynamics->power_avaliable.value - current_flight_dynamics->power_required.value;

	current_flight_dynamics->power_surplus.value = max (current_flight_dynamics->power_surplus.value, 0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_air_density_dynamics (void)
{

	float
		Amax,
		Amin;

	Amax = current_flight_dynamics->air_density.max;

	Amin = current_flight_dynamics->air_density.min;

	current_flight_dynamics->air_density.value = Amax - (((Amax - Amin) / 10000) * current_flight_dynamics->position.y);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_acceleration_dynamics (void)
{

	helicopter
		*raw;

	raw = get_local_entity_data (get_gunship_entity ());

	// calculate total lift provided by main rotor

	current_flight_dynamics->lift.value = current_flight_dynamics->power_surplus.value * 50;

	current_flight_dynamics->lift.value /= current_flight_dynamics->mass.value;

	// transform model acceleration into world acceleration

	multiply_matrix3x3_vec3d (&current_flight_dynamics->world_acceleration_vector, current_flight_dynamics->attitude, &current_flight_dynamics->model_acceleration_vector);

	// calculate the motion vector, in world coords

	current_flight_dynamics->world_motion_vector.x += current_flight_dynamics->world_acceleration_vector.x * get_model_delta_time ();
	current_flight_dynamics->world_motion_vector.y += current_flight_dynamics->world_acceleration_vector.y * get_model_delta_time ();
	current_flight_dynamics->world_motion_vector.z += current_flight_dynamics->world_acceleration_vector.z * get_model_delta_time ();

	current_flight_dynamics->world_velocity_x.value = current_flight_dynamics->world_motion_vector.x;
	current_flight_dynamics->world_velocity_y.value = current_flight_dynamics->world_motion_vector.y;
	current_flight_dynamics->world_velocity_z.value = current_flight_dynamics->world_motion_vector.z;

	// transform the motion vector back into model coords ready for read-out and bounding

	multiply_transpose_matrix3x3_vec3d (&current_flight_dynamics->model_motion_vector, current_flight_dynamics->attitude, &current_flight_dynamics->world_motion_vector);

	// output values for HUD etc..

	current_flight_dynamics->velocity_x.delta = current_flight_dynamics->world_acceleration_vector.x * get_model_delta_time ();
	current_flight_dynamics->velocity_y.delta = current_flight_dynamics->world_acceleration_vector.y * get_model_delta_time ();
	current_flight_dynamics->velocity_z.delta = current_flight_dynamics->world_acceleration_vector.z * get_model_delta_time ();

	current_flight_dynamics->velocity_x.value = current_flight_dynamics->model_motion_vector.x;
	current_flight_dynamics->velocity_y.value = current_flight_dynamics->model_motion_vector.y;
	current_flight_dynamics->velocity_z.value = current_flight_dynamics->model_motion_vector.z;

	// move position

	current_flight_dynamics->position.x += current_flight_dynamics->world_motion_vector.x * get_model_delta_time ();
	current_flight_dynamics->position.y += current_flight_dynamics->world_motion_vector.y * get_model_delta_time ();
	current_flight_dynamics->position.z += current_flight_dynamics->world_motion_vector.z * get_model_delta_time ();

	// bound to the world

	bound_double_position_to_adjusted_map_volume (&current_flight_dynamics->position);
	//current_flight_dynamics->position.x = bound (current_flight_dynamics->position.x, MIN_MAP_X, MAX_MAP_X);
	//current_flight_dynamics->position.z = bound (current_flight_dynamics->position.z, MIN_MAP_Z, MAX_MAP_Z);

	if (get_terrain_type_class (get_3d_terrain_point_data_type (&raw->ac.terrain_info)) == TERRAIN_CLASS_LAND)
	{

		current_flight_dynamics->position.y = bound (current_flight_dynamics->position.y, 0.0, MAX_MAP_Y);
	}
	else
	{

		//
		// allow model to go 1m into water/forest and then blow up
		//

		current_flight_dynamics->position.y = bound (current_flight_dynamics->position.y, -1.0, MAX_MAP_Y);
	}

	// debug - for ships, VSI = 0 when landed.

	if (!get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AIRBORNE_AIRCRAFT))
	{

		current_flight_dynamics->world_velocity_y.value = max (current_flight_dynamics->world_velocity_y.value, 0.0);
		current_flight_dynamics->velocity_y.value = max (current_flight_dynamics->velocity_y.value, 0.0);
		current_flight_dynamics->model_motion_vector.y = max (current_flight_dynamics->model_motion_vector.y, 0.0);
		current_flight_dynamics->world_motion_vector.y = max (current_flight_dynamics->world_motion_vector.y, 0.0);

		if (current_flight_dynamics->wheel_brake)
		{
			// arneh, june 2006 - reduces effectivness of wheel brakes
			if (current_flight_dynamics->world_motion_vector.x > 0)
				current_flight_dynamics->world_motion_vector.x -= min(20.0 * get_model_delta_time (), current_flight_dynamics->world_motion_vector.x );
			else
				current_flight_dynamics->world_motion_vector.x -= max(-20.0 * get_model_delta_time (), current_flight_dynamics->world_motion_vector.x );

			if (current_flight_dynamics->world_motion_vector.z > 0)
				current_flight_dynamics->world_motion_vector.z -= min(5.0 * get_model_delta_time (), current_flight_dynamics->world_motion_vector.z);
			else
				current_flight_dynamics->world_motion_vector.z -= max(-5.0 * get_model_delta_time (), current_flight_dynamics->world_motion_vector.z);
		}
	}
	{

		entity
			*keysite;

		keysite = get_local_entity_parent (get_local_entity_parent (get_gunship_entity (), LIST_TYPE_MEMBER), LIST_TYPE_KEYSITE_GROUP);

		if (keysite)
		{

			if (get_local_entity_int_value (keysite, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_KEYSITE_ANCHORAGE)
			{

				if (helicopter_within_keysite_area (get_gunship_entity ()))
				{


					if (current_flight_dynamics->position.y < 19.90 + get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE))
					{

						if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AIRBORNE_AIRCRAFT))
						{

							set_client_server_entity_int_value (get_gunship_entity (), INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_TAXIING);
						}

						current_flight_dynamics->position.y = bound (current_flight_dynamics->position.y, 19.90 + get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE), MAX_MAP_Y);
					}
				}
			}
		}
	}

	current_flight_dynamics->altitude.value = current_flight_dynamics->position.y;

	current_flight_dynamics->altitude.min = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_TERRAIN_ELEVATION);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void blackhawk_restore_damage_values (void)
{

	current_flight_dynamics->centre_of_gravity.x = 0.00;
	current_flight_dynamics->centre_of_gravity.y = -0.2;
	current_flight_dynamics->centre_of_gravity.z = -0.012;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
