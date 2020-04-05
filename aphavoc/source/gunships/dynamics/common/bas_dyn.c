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
	basic_flight_dynamics;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_basic_main_rotor_dynamics (void);

static void update_basic_tail_rotor_dynamics (void);

static void update_basic_main_rotor_rpm_dynamics (void);

static void update_basic_tail_rotor_rpm_dynamics (void);

static void update_basic_main_rotor_coning_angle (void);

static void update_basic_main_rotor_thrust_dynamics (void);

static void update_basic_tail_rotor_thrust_dynamics (void);

static void update_basic_attitude_dynamics (void);

static void update_basic_power_dynamics (void);

static void update_basic_air_density_dynamics (void);

static void update_basic_acceleration_dynamics (void);

static void update_basic_altitude_dynamics (void);

void set_basic_dynamics_defaults (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_basic_dynamics (void)
{

	FILE
		*file_ptr = nullptr;

	current_flight_dynamics = &basic_flight_dynamics;

	memset (current_flight_dynamics, 0, sizeof (dynamics_type));

	if (!file_exist ("basic.dyn"))
	{

		set_basic_dynamics_defaults ();

		#if !DEBUG_DYNAMICS

		file_ptr = fopen ("basic.dyn", "wb");

		if (file_ptr)
		{

			save_dynamics_model (file_ptr);
		}

		fclose (file_ptr);

		#endif
	}
	else
	{

		file_ptr = fopen ("basic.dyn", "rb");

		if (file_ptr)
		{

			if (file_size ("basic.dyn") != sizeof (dynamics_type))
			{

				debug_fatal ("DYNAMICS: BASIC: basic.dyn file incorrect size");
			}

			load_dynamics_model (file_ptr);
		}

		fclose (file_ptr);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_basic_dynamics_defaults (void)
{

	vec3d
		position;

	get_local_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &position);

	current_flight_dynamics->position.x = position.x;
	current_flight_dynamics->position.y = position.y;
	current_flight_dynamics->position.z = position.z;

	current_flight_dynamics->input_data.collective.value = 75.0;
	current_flight_dynamics->input_data.collective.min = 0;
	current_flight_dynamics->input_data.collective.max = 100;

	current_flight_dynamics->roll.min = rad (-180.0);
	current_flight_dynamics->roll.max = rad (180.0);

	current_flight_dynamics->pitch.min = rad (-90.0);
	current_flight_dynamics->pitch.max = rad (90.0);

	current_flight_dynamics->air_density.value = 2.3;
	current_flight_dynamics->air_density.max = 2.3;
	current_flight_dynamics->air_density.min = 1.5;

	current_flight_dynamics->altitude.min = 0.0;
	current_flight_dynamics->altitude.max = 4990.0;

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

	current_flight_dynamics->heading_inertia.value = 6000;
	current_flight_dynamics->pitch_inertia.value = 3200;
	current_flight_dynamics->roll_inertia.value = 3200;

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

void update_basic_dynamics (void)
{

	update_basic_main_rotor_dynamics ();

	update_basic_tail_rotor_dynamics ();

	update_basic_main_rotor_rpm_dynamics ();

	update_basic_tail_rotor_rpm_dynamics ();

	update_basic_main_rotor_coning_angle ();

	update_basic_main_rotor_thrust_dynamics ();

	update_basic_tail_rotor_thrust_dynamics ();

	update_basic_power_dynamics ();

	update_basic_air_density_dynamics ();

	update_basic_acceleration_dynamics ();

	update_basic_altitude_dynamics ();

	update_basic_attitude_dynamics ();

	update_dynamics_external_values ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_basic_main_rotor_dynamics (void)
{

	float
		rotor_roll,
		rotor_pitch,
		cyclic_x,
		cyclic_y,
		collective,
		blade_pitch;

	// calculate blade pitch 0->5 Degs. collective = blade_pitch^3

	collective = basic_flight_dynamics.input_data.collective.value;

	blade_pitch = pow (fabs (collective), (float) (1.0 / 3.0)) * (basic_flight_dynamics.main_blade_pitch.max / 4.64);

	basic_flight_dynamics.main_blade_pitch.value = blade_pitch;

	basic_flight_dynamics.main_blade_pitch.value = bound (
																basic_flight_dynamics.main_blade_pitch.value,
																basic_flight_dynamics.main_blade_pitch.min,
																basic_flight_dynamics.main_blade_pitch.max);

	// calculate 'Tip Plane Path' roll and pitch

	// roll

	cyclic_x = basic_flight_dynamics.input_data.cyclic_x.value;

	rotor_roll = rad (cyclic_x / (basic_flight_dynamics.input_data.cyclic_x.max / deg (basic_flight_dynamics.main_rotor_roll_angle.max)));

	basic_flight_dynamics.main_rotor_roll_angle.value = rotor_roll;

	basic_flight_dynamics.main_rotor_roll_angle.value = bound (
																basic_flight_dynamics.main_rotor_roll_angle.value,
																basic_flight_dynamics.main_rotor_roll_angle.min,
																basic_flight_dynamics.main_rotor_roll_angle.max);

	// pitch

	cyclic_y = basic_flight_dynamics.input_data.cyclic_y.value;

	rotor_pitch = -rad (cyclic_y / (basic_flight_dynamics.input_data.cyclic_y.max / deg (basic_flight_dynamics.main_rotor_pitch_angle.max)));

	basic_flight_dynamics.main_rotor_pitch_angle.value = rotor_pitch;

	basic_flight_dynamics.main_rotor_pitch_angle.value = bound (
																basic_flight_dynamics.main_rotor_pitch_angle.value,
																basic_flight_dynamics.main_rotor_pitch_angle.min,
																basic_flight_dynamics.main_rotor_pitch_angle.max);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_basic_tail_rotor_dynamics (void)
{

	float
		pedal,
		blade_pitch;

	// calculate blade pitch 0->5 Degs, linearly

	pedal = basic_flight_dynamics.input_data.pedal.value;

	blade_pitch = rad (pedal / (basic_flight_dynamics.input_data.pedal.max / deg (basic_flight_dynamics.main_blade_pitch.max)));

	basic_flight_dynamics.tail_blade_pitch.value = blade_pitch;

	basic_flight_dynamics.tail_blade_pitch.value = bound (
																basic_flight_dynamics.tail_blade_pitch.value,
																basic_flight_dynamics.tail_blade_pitch.min,
																basic_flight_dynamics.tail_blade_pitch.max);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_basic_main_rotor_rpm_dynamics (void)
{

	float
		rpm_min,
		rpm_max,
		rpm;

	// simple, just follow collective setting between min and max

	rpm_min = current_flight_dynamics->main_rotor_rpm.min;

	rpm_max = current_flight_dynamics->main_rotor_rpm.max;

	rpm = (((rpm_max - rpm_min) / current_flight_dynamics->input_data.collective.max) * current_flight_dynamics->input_data.collective.value) + rpm_min;

	current_flight_dynamics->main_rotor_rpm.value += (rpm - current_flight_dynamics->main_rotor_rpm.value);// * get_delta_time ();

	current_flight_dynamics->main_rotor_rpm.value = bound (current_flight_dynamics->main_rotor_rpm.value,
																current_flight_dynamics->main_rotor_rpm.min,
																current_flight_dynamics->main_rotor_rpm.max);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_basic_tail_rotor_rpm_dynamics (void)
{

	float
		rpm_min,
		rpm_max,
		rpm;

	// simple, just follow collective setting between min and max

	rpm_min = current_flight_dynamics->tail_rotor_rpm.min;

	rpm_max = current_flight_dynamics->tail_rotor_rpm.max;

	rpm = (((rpm_max - rpm_min) / current_flight_dynamics->input_data.collective.max) * current_flight_dynamics->input_data.collective.value) + rpm_min;

	current_flight_dynamics->tail_rotor_rpm.value += (rpm - current_flight_dynamics->tail_rotor_rpm.value) * get_delta_time ();

	current_flight_dynamics->tail_rotor_rpm.value = bound (current_flight_dynamics->tail_rotor_rpm.value,
																current_flight_dynamics->tail_rotor_rpm.min,
																current_flight_dynamics->tail_rotor_rpm.max);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_basic_main_rotor_coning_angle (void)
{

	float
		coning_angle,
		rpm,
		rx,
		cx,
		cm;

	// simple, linear coning from Cmin to Cmax over Rx wrt rpm.

	rx = current_flight_dynamics->main_rotor_rpm.max;
	cx = current_flight_dynamics->main_rotor_coning_angle.max;
	cm = current_flight_dynamics->main_rotor_coning_angle.min;
	rpm = current_flight_dynamics->main_rotor_rpm.value;

	coning_angle = ((cx - cm) / rx) * rpm + cm;

	current_flight_dynamics->main_rotor_coning_angle.value += (coning_angle - current_flight_dynamics->main_rotor_coning_angle.value) * get_delta_time ();

	current_flight_dynamics->main_rotor_coning_angle.value = bound (current_flight_dynamics->main_rotor_coning_angle.value,
																current_flight_dynamics->main_rotor_coning_angle.min,
																current_flight_dynamics->main_rotor_coning_angle.max);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_basic_main_rotor_thrust_dynamics (void)
{

	float
		thrust_at_0_blade_pitch_percentage = 25.0,
		blade_pitch_induced_thrust_percentage,
		rotor_rpm_induced_thrust;

	// combination of blade pitch (linear from 0->Bx) and Rpm (linear)

	blade_pitch_induced_thrust_percentage = (((100.0 - thrust_at_0_blade_pitch_percentage) /
															current_flight_dynamics->main_blade_pitch.max) *
															current_flight_dynamics->main_blade_pitch.value +
															thrust_at_0_blade_pitch_percentage) / 100.0;

	rotor_rpm_induced_thrust = (current_flight_dynamics->main_rotor_thrust.max / current_flight_dynamics->main_rotor_rpm.max) *
											current_flight_dynamics->main_rotor_rpm.value;

	current_flight_dynamics->main_rotor_thrust.value = rotor_rpm_induced_thrust * blade_pitch_induced_thrust_percentage;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_basic_tail_rotor_thrust_dynamics (void)
{

	// the thrust_at_0.. will cause a constant yaw input = correct.

	float
		thrust_at_0_blade_pitch_percentage = 25.0,
		blade_pitch_induced_thrust_percentage,
		rotor_rpm_induced_thrust;

	blade_pitch_induced_thrust_percentage = (((100.0 - thrust_at_0_blade_pitch_percentage) /
															current_flight_dynamics->tail_blade_pitch.max) *
															current_flight_dynamics->tail_blade_pitch.value +
															thrust_at_0_blade_pitch_percentage) / 100.0;

	rotor_rpm_induced_thrust = (current_flight_dynamics->tail_rotor_thrust.max / current_flight_dynamics->tail_rotor_rpm.max) *
											current_flight_dynamics->tail_rotor_rpm.value;

	current_flight_dynamics->tail_rotor_thrust.value = rotor_rpm_induced_thrust * blade_pitch_induced_thrust_percentage;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_basic_attitude_dynamics (void)
{

	matrix3x3
		attitude;

	float
		restore,
		cross_coupling_effect,
		heading_max,
		heading_angle,
		roll_angle,
		pitch_angle,
		pitch_delta,
		roll_delta;

	float
		heading,
		pitch,
		roll;

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

	roll_delta = current_flight_dynamics->main_rotor_roll_angle.value;

	current_flight_dynamics->roll.delta = (roll_delta * (1 - (fabs (current_flight_dynamics->roll.value) / current_flight_dynamics->roll.max))) * 2; // const just to spice things up a little

	// restore

	// calculate restoring force

	restore = (1.0 - 1.0 * (fabs (current_flight_dynamics->roll.value) / current_flight_dynamics->roll.max));

	// reduce restore with velocity

	restore -= 0.75 * restore * current_flight_dynamics->velocity_z.value / current_flight_dynamics->velocity_z.max;

	current_flight_dynamics->roll.delta -= restore * current_flight_dynamics->roll.value * get_delta_time (); // const feels about right

	// actually roll

	current_flight_dynamics->roll.value += current_flight_dynamics->roll.delta;

	//
	// pitch
	//

	pitch_delta = current_flight_dynamics->main_rotor_pitch_angle.value * get_delta_time ();

	current_flight_dynamics->pitch.delta = (pitch_delta * (1 - (fabs (current_flight_dynamics->pitch.value) / current_flight_dynamics->pitch.max))) * 4; // const just to spice things up a little

	// restore

	restore = (1.0 - 1.0 * (fabs (current_flight_dynamics->pitch.value) / current_flight_dynamics->pitch.max));

	// reduce restore with velocity

	restore -= 1.0 * restore * current_flight_dynamics->velocity_z.value / current_flight_dynamics->velocity_z.max;

	current_flight_dynamics->pitch.delta -= restore * (current_flight_dynamics->pitch.value * get_delta_time ()); // const that feels about right

	// actually pitch

	current_flight_dynamics->pitch.value += (current_flight_dynamics->pitch.delta * cos (current_flight_dynamics->roll.value)) +
										(current_flight_dynamics->heading.delta * sin (current_flight_dynamics->roll.value));

	//
	// heading
	//

	current_flight_dynamics->heading.delta = (((current_flight_dynamics->main_rotor_thrust.value * current_flight_dynamics->main_rotor_diameter.value) -
												(current_flight_dynamics->tail_rotor_thrust.value * current_flight_dynamics->tail_boom_length.value * current_flight_dynamics->tail_rotor_diameter.value) * 2) * get_delta_time ()) /
												current_flight_dynamics->mass.value;

	cross_coupling_effect = (((current_flight_dynamics->main_rotor_thrust.value * current_flight_dynamics->main_rotor_diameter.value) -
												(.250 * current_flight_dynamics->tail_rotor_rpm.value * current_flight_dynamics->tail_boom_length.value * current_flight_dynamics->tail_rotor_diameter.value) * 2) * get_delta_time ()) /
												current_flight_dynamics->mass.value;

	current_flight_dynamics->cross_coupling_effect.value += (cross_coupling_effect - current_flight_dynamics->cross_coupling_effect.value) * get_delta_time ();

	current_flight_dynamics->heading.delta -= current_flight_dynamics->cross_coupling_effect.value;

	// decrease yaw input with velocity

	heading_max = current_flight_dynamics->heading.delta - (current_flight_dynamics->heading.delta * (current_flight_dynamics->velocity_z.value / current_flight_dynamics->velocity_z.max));

	current_flight_dynamics->heading.delta = bound (current_flight_dynamics->heading.delta, -fabs (heading_max), fabs (heading_max));

	// add delta_heading for roll value

	current_flight_dynamics->heading.value += ((((current_flight_dynamics->roll.value * current_flight_dynamics->velocity_z.value) / current_flight_dynamics->velocity_z.max) * get_delta_time ()) / 3); // const to calm it down a litte

	// add it all up

	current_flight_dynamics->heading.value += (current_flight_dynamics->pitch.delta * sin (current_flight_dynamics->roll.value)) -
										(current_flight_dynamics->heading.delta * cos (current_flight_dynamics->roll.value));

	//
	// keep everything happy
	//

	if (current_flight_dynamics->roll.value > PI)
	{

		current_flight_dynamics->roll.value -= 2 * PI;
	}
	else if (current_flight_dynamics->roll.value < -PI)
	{

		current_flight_dynamics->roll.value += 2 * PI;
	}

	if (current_flight_dynamics->pitch.value > PI)
	{

		current_flight_dynamics->pitch.value -= 2 * PI;
	}
	else if (current_flight_dynamics->pitch.value < -PI)
	{

		current_flight_dynamics->pitch.value += 2 * PI;
	}

	if (current_flight_dynamics->heading.value > 2 * PI)
	{

		current_flight_dynamics->heading.value -= 2 * PI;
	}
	else if (current_flight_dynamics->heading.value < 0)
	{

		current_flight_dynamics->heading.value += 2 * PI;
	}

	roll_angle = current_flight_dynamics->roll.value;

	pitch_angle = current_flight_dynamics->pitch.value;

	heading_angle = current_flight_dynamics->heading.value;

  	get_3d_transformation_matrix (attitude, heading_angle, pitch_angle, roll_angle);

	set_local_entity_attitude_matrix (get_gunship_entity (), attitude);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_basic_power_dynamics (void)
{

	float
		profile_min = 40.0,
		profile_max = 50.0,
		induced_min = 60.0,
		induced_max = 50.0,
		blade_pitch,
		Vmax,
		Bmax,
		total_velocity;

	current_flight_dynamics->power_avaliable.value = current_flight_dynamics->power_avaliable.max * (current_flight_dynamics->main_rotor_rpm.value / current_flight_dynamics->main_rotor_rpm.max);

	total_velocity = (current_flight_dynamics->velocity_x.value + current_flight_dynamics->velocity_y.value + current_flight_dynamics->velocity_z.value);

	blade_pitch = current_flight_dynamics->main_blade_pitch.value;

	Bmax = current_flight_dynamics->main_blade_pitch.max;

	Vmax = (current_flight_dynamics->velocity_x.max + current_flight_dynamics->velocity_y.max + current_flight_dynamics->velocity_z.max);

	// parasitic drag = square of velocity

	if (total_velocity)
	{

		current_flight_dynamics->power_parasite.value = current_flight_dynamics->power_avaliable.value * pow (total_velocity, 2) / pow (Vmax, 2);

		// rotor profile drag = linear from min to max across V

		current_flight_dynamics->power_profile.value = ((profile_max - profile_min) / Vmax) * total_velocity + profile_min;
	}
	else
	{
		current_flight_dynamics->power_parasite.value = 0;

		current_flight_dynamics->power_profile.value = 0;
	}

	// rotor induced power = linear wrt blade angle

	current_flight_dynamics->power_induced.value = ((induced_max - induced_min) / Bmax) * blade_pitch + induced_min;

	current_flight_dynamics->power_required.value = current_flight_dynamics->power_induced.value + current_flight_dynamics->power_profile.value + current_flight_dynamics->power_parasite.value;

	current_flight_dynamics->power_required.value /= 100;

	current_flight_dynamics->power_required.value *= current_flight_dynamics->power_avaliable.max;

	current_flight_dynamics->power_surplus.value = current_flight_dynamics->power_avaliable.value - current_flight_dynamics->power_required.value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_basic_air_density_dynamics (void)
{

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

void update_basic_acceleration_dynamics (void)
{

	float
		v_lift,
		velocity_x_max,
		velocity_y_in_hover = 7.9,
		optimal_velocity = 30.8, // ~60 kts
		h_lift_forward,
		h_lift_sideways;

	vec3d
		position;

	// calculate total lift provided by main rotor

	current_flight_dynamics->lift.value = (current_flight_dynamics->power_avaliable.max * (current_flight_dynamics->main_rotor_thrust.value / current_flight_dynamics->main_rotor_thrust.max)) *
					current_flight_dynamics->air_density.value *
					current_flight_dynamics->main_rotor_diameter.value;

	current_flight_dynamics->lift.value -= current_flight_dynamics->mass.value * G;

	// transitional lift

	if (current_flight_dynamics->velocity_z.value < optimal_velocity)
	{

		current_flight_dynamics->lift.value += current_flight_dynamics->lift.value * (current_flight_dynamics->velocity_z.value / optimal_velocity);
	}
	else
	{

		current_flight_dynamics->lift.value += (current_flight_dynamics->lift.max - current_flight_dynamics->lift.value) / (current_flight_dynamics->lift.max - optimal_velocity);
	}

	// produce cubic charateristics for lift.. ie less sensitive around zero
	// therefore need to cube and then divide to scale down but different for
	// positive and negative.

	current_flight_dynamics->lift.value = pow (current_flight_dynamics->lift.value, 3);

	if (current_flight_dynamics->lift.value < 0)
	{

		current_flight_dynamics->lift.value /= 3135964286.0;
	}
	else
	{

		current_flight_dynamics->lift.value /= 121000000.0;
	}

	// vertically

	if (current_flight_dynamics->lift.value > 0)
	{

		// if it's going up its a component of the rotor disc angles

		v_lift = current_flight_dynamics->lift.value * cos (current_flight_dynamics->roll.value) * cos (current_flight_dynamics->pitch.value);
	}
	else
	{

		// if going down it's going straight down

		v_lift = current_flight_dynamics->lift.value;
	}

	current_flight_dynamics->velocity_y.delta = (v_lift / current_flight_dynamics->mass.value);

	current_flight_dynamics->drag_y.value = (current_flight_dynamics->velocity_y.delta * (current_flight_dynamics->velocity_y.value / current_flight_dynamics->velocity_y.max)) + current_flight_dynamics->drag_x.min;

	current_flight_dynamics->drag_y.value = min (current_flight_dynamics->velocity_y.value, current_flight_dynamics->drag_y.value);

	current_flight_dynamics->velocity_y.value += current_flight_dynamics->velocity_y.delta * get_delta_time () ;

	// if accelerating in different direction retard

	if (current_flight_dynamics->velocity_y.value * current_flight_dynamics->velocity_y.delta < 0)
	{

		current_flight_dynamics->velocity_y.value -= (current_flight_dynamics->velocity_y.value * 0.5) * get_delta_time ();
	}

	// dynamics lift constraints

	if (current_flight_dynamics->velocity_z.value < optimal_velocity)
	{

		current_flight_dynamics->velocity_y.value = bound (current_flight_dynamics->velocity_y.value,
							current_flight_dynamics->velocity_y.min,
							((current_flight_dynamics->velocity_y.max - velocity_y_in_hover) *
							(current_flight_dynamics->velocity_z.value) / optimal_velocity)
							+ velocity_y_in_hover);
	}
	else if (current_flight_dynamics->velocity_z.value > optimal_velocity)
	{

		current_flight_dynamics->velocity_y.value = bound (current_flight_dynamics->velocity_y.value,
							current_flight_dynamics->velocity_y.min,
							current_flight_dynamics->velocity_y.max - (current_flight_dynamics->velocity_y.max * (current_flight_dynamics->velocity_z.value - optimal_velocity) /
							(current_flight_dynamics->velocity_z.max - optimal_velocity)));
	}

	// horizontally forward

	h_lift_forward = fabs (current_flight_dynamics->lift.value) * sin (current_flight_dynamics->pitch.value) * 10;

	current_flight_dynamics->velocity_z.delta = (-h_lift_forward / current_flight_dynamics->mass.value) - (G * sin (current_flight_dynamics->pitch.value));

	current_flight_dynamics->velocity_z.delta = bound (current_flight_dynamics->velocity_z.delta, current_flight_dynamics->acceleration_z.min - current_flight_dynamics->acceleration_z.min * (current_flight_dynamics->velocity_z.value / current_flight_dynamics->velocity_z.min),
				current_flight_dynamics->acceleration_z.max -
				(current_flight_dynamics->acceleration_z.max * current_flight_dynamics->velocity_z.value) /
				current_flight_dynamics->velocity_z.max);

	current_flight_dynamics->drag_z.value = (current_flight_dynamics->drag_x.max * (current_flight_dynamics->velocity_z.value / current_flight_dynamics->velocity_z.max)) + current_flight_dynamics->drag_x.min;

	current_flight_dynamics->drag_z.value = min (current_flight_dynamics->velocity_z.value, current_flight_dynamics->drag_z.value);

	current_flight_dynamics->velocity_z.value += current_flight_dynamics->velocity_z.delta * get_delta_time ();

	current_flight_dynamics->velocity_z.value -= (current_flight_dynamics->drag_z.value * get_delta_time ());

	// horizontally sideways

	h_lift_sideways = fabs (current_flight_dynamics->lift.value) * sin (-current_flight_dynamics->roll.value) * 10;

	current_flight_dynamics->velocity_x.delta = (h_lift_forward / current_flight_dynamics->mass.value) - (G * sin (-current_flight_dynamics->roll.value));

	current_flight_dynamics->drag_x.value = ((current_flight_dynamics->drag_x.max * (current_flight_dynamics->velocity_x.value / current_flight_dynamics->velocity_x.max)) + current_flight_dynamics->drag_x.min);

	current_flight_dynamics->drag_x.value *= 5;

	current_flight_dynamics->drag_x.value = min (current_flight_dynamics->velocity_x.value, current_flight_dynamics->drag_x.value);

	current_flight_dynamics->velocity_x.value += current_flight_dynamics->velocity_x.delta * get_delta_time ();

	current_flight_dynamics->velocity_x.value -= (current_flight_dynamics->drag_x.value * get_delta_time ());

	// fade out sidespeed at optimal velocity (~60 kts)

	if (current_flight_dynamics->velocity_z.value < optimal_velocity)
	{

		velocity_x_max = current_flight_dynamics->velocity_x.max -
					(current_flight_dynamics->velocity_x.max * current_flight_dynamics->velocity_z.value) /
					optimal_velocity;
	}
	else
	{

		velocity_x_max = 0.0;
	}

	current_flight_dynamics->velocity_x.value = bound (current_flight_dynamics->velocity_x.value,
										-velocity_x_max,
										velocity_x_max);

	// convert to world axis and
	// move the object
/*
	debug_log ("x =  x %f, z %f,,,, z =  x %f, z %f",
								(current_flight_dynamics->velocity_x.value * cos (current_flight_dynamics->heading.value)),
								(current_flight_dynamics->velocity_z.value * sin (current_flight_dynamics->heading.value)),
								(current_flight_dynamics->velocity_z.value * cos (current_flight_dynamics->heading.value)),
								(current_flight_dynamics->velocity_x.value * sin (current_flight_dynamics->heading.value)));
*/

	current_flight_dynamics->world_velocity_x.value =
						(current_flight_dynamics->velocity_x.value * cos (current_flight_dynamics->heading.value)) +
						(current_flight_dynamics->velocity_z.value * sin (current_flight_dynamics->heading.value)) +
						(current_flight_dynamics->velocity_y.value * sin (current_flight_dynamics->roll.value));

	//(current_flight_dynamics->input_data.collective.value - 50) / 2;

	current_flight_dynamics->world_velocity_y.value =
						(current_flight_dynamics->velocity_y.value * cos (current_flight_dynamics->pitch.value)) +
						(current_flight_dynamics->velocity_z.value * sin (current_flight_dynamics->pitch.value)) +
						(-current_flight_dynamics->velocity_x.value * sin (current_flight_dynamics->roll.value));

	current_flight_dynamics->world_velocity_z.value =
						(current_flight_dynamics->velocity_z.value * cos (current_flight_dynamics->heading.value)) +
						(-current_flight_dynamics->velocity_x.value * sin (current_flight_dynamics->heading.value)) +
						(current_flight_dynamics->velocity_y.value * sin (current_flight_dynamics->pitch.value));

	current_flight_dynamics->position.x += current_flight_dynamics->world_velocity_x.value * get_delta_time ();
	current_flight_dynamics->position.y += current_flight_dynamics->world_velocity_y.value * get_delta_time ();
	current_flight_dynamics->position.z += current_flight_dynamics->world_velocity_z.value * get_delta_time ();

	position.x = current_flight_dynamics->position.x;
	position.y = current_flight_dynamics->position.y;
	position.z = current_flight_dynamics->position.z;

	set_local_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &position);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_basic_altitude_dynamics (void)
{

	matrix3x3
		attitude;

	float
		ground_height,
		centre_of_gravity_to_ground_distance;

	vec3d
		position,
		*old_z = nullptr,
		*face_normal = nullptr;

	centre_of_gravity_to_ground_distance = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE);

	get_local_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &position);

	get_local_entity_attitude_matrix (get_gunship_entity (), attitude);

	ground_height = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_TERRAIN_ELEVATION);

	current_flight_dynamics->altitude.value = position.y;

	current_flight_dynamics->altitude.min = ground_height;

	if (current_flight_dynamics->altitude.value < current_flight_dynamics->altitude.min + centre_of_gravity_to_ground_distance)
	{

		memset (&current_flight_dynamics->world_motion_vector, 0, sizeof (vec3d));

		current_flight_dynamics->velocity_x.value /= 2;
		current_flight_dynamics->velocity_y.value = 0;
		current_flight_dynamics->velocity_z.value /= 2;

		position.y = ground_height + centre_of_gravity_to_ground_distance;

		current_flight_dynamics->altitude.value = current_flight_dynamics->altitude.min + centre_of_gravity_to_ground_distance;

		face_normal = get_local_entity_ptr_value (get_gunship_entity (), PTR_TYPE_TERRAIN_FACE_NORMAL);

		// cross n with z giving x

		old_z = (vec3d *) attitude [2];

		attitude [1][0] = face_normal->x;

		attitude [1][1] = face_normal->y;

		attitude [1][2] = face_normal->z;

		attitude [0][0] = (face_normal->y * old_z->z) - (face_normal->z * old_z->y);

		attitude [0][1] = (face_normal->z * old_z->x) - (face_normal->x * old_z->z);

		attitude [0][2] = (face_normal->x * old_z->y) - (face_normal->y * old_z->x);

		// cross n with x giving z

		attitude [2][0] = - (face_normal->y * attitude [0][2]) + (face_normal->z * attitude [0][1]);

		attitude [2][1] = - (face_normal->z * attitude [0][0]) + (face_normal->x * attitude [0][2]);

		attitude [2][2] = - (face_normal->x * attitude [0][1]) + (face_normal->y * attitude [0][0]);

		normalise_3d_vector ((vec3d *) &attitude [0]);

		normalise_3d_vector ((vec3d *) &attitude [2]);

		set_local_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &position);

		set_local_entity_attitude_matrix (get_gunship_entity (), attitude);
	}

	current_flight_dynamics->altitude.value = bound (
														current_flight_dynamics->altitude.value,
														current_flight_dynamics->altitude.min,
														current_flight_dynamics->altitude.max);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
