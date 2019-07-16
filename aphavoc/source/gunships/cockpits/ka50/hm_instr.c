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

void get_ka50_temperature_needle_values(float temp, float* big_needle, float* small_needle)
{
	temp = bound(temp, 0.0, 1000.0);

	*big_needle = rad(131) - rad(0.2183) * temp;
	*small_needle = rad(180) - 0.02 * PI * temp;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void get_ka50_hsi_needle_values (float *direction_finder, float *flight_path, float *drift)
{
	float
		direction_finder_needle_value,
		flight_path_needle_value,
		drift_needle_value,
		dx,
		dz,
		heading,
		bearing,
		length1,
		length2,
		dot_product,
		cross_product;

	entity
		*en,
		*wp,
		*prev_wp;

	vec3d
		*motion_vector,
		wind_vector,
		*en_position,
		wp_position,
		prev_wp_position;

	vec2d
		v1,
		v2;

	ASSERT (direction_finder);

	ASSERT (flight_path);

	ASSERT (drift);

	direction_finder_needle_value = 0.0;

	flight_path_needle_value = 0.0;

	drift_needle_value = 0.0;

	if (test_cockpit_instruments)
	{
		static float
			direction_finder_value = rad (0.0),
			flight_path_value = rad (90.0),
			drift_value = rad (-20.0);

		//
		// automatic direction finder
		//

		direction_finder_value += rad (5.0);

		if (direction_finder_value > rad (360.0))
		{
			direction_finder_value -= rad (360.0);
		}

		direction_finder_needle_value = direction_finder_value;

		//
		// flight path
		//

		flight_path_value += rad (3.0);

		if (flight_path_value > rad (360.0))
		{
			flight_path_value -= rad (360.0);
		}

		flight_path_needle_value = flight_path_value;

		//
		// drift
		//

		drift_value += rad (1.0);

		if (drift_value > rad (35.0))
		{
			drift_value = rad (-35.0);
		}

		drift_needle_value = drift_value;
	}
	else
	{
		if (!havoc_damage.navigation_computer)
		{
			en = get_gunship_entity ();

			wp = get_local_entity_current_waypoint (en);

			if (wp)
			{
				//
				// automatic direction finder
				//

				heading = get_local_entity_float_value (en, FLOAT_TYPE_HEADING);

				en_position = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

				get_waypoint_display_position (en, wp, &wp_position);

				dx = wp_position.x - en_position->x;
				dz = wp_position.z - en_position->z;

				bearing = atan2 (dx, dz);

				direction_finder_needle_value = bearing - heading;

				//
				// flight path
				//

				prev_wp = get_local_entity_prev_waypoint (en);

				if ((prev_wp) && (prev_wp != wp))
				{
					get_waypoint_display_position (en, prev_wp, &prev_wp_position);

					dx = wp_position.x - prev_wp_position.x;
					dz = wp_position.z - prev_wp_position.z;

					bearing = atan2 (dx, dz);

					flight_path_needle_value = bearing - heading;
				}
				else
				{
					flight_path_needle_value = direction_finder_needle_value;
				}

				//
				// drift
				//

				drift_needle_value = 0.0;

				motion_vector = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_MOTION_VECTOR);

				v1.x = motion_vector->x;
				v1.y = motion_vector->z;

				length1 = (v1.x * v1.x) + (v1.y * v1.y);

				if (length1 > 0.001)
				{
					length1 = sqrt (length1);

					v1.x /= length1;
					v1.y /= length1;

					get_session_wind_velocity_at_point (en_position, &wind_vector);

					v2.x = motion_vector->x + wind_vector.x;
					v2.y = motion_vector->z + wind_vector.z;

					length2 = (v2.x * v2.x) + (v2.y * v2.y);

					if (length2 > 0.001)
					{
						length2 = sqrt (length2);

						v2.x /= length2;
						v2.y /= length2;

						dot_product = get_2d_unit_vector_dot_product (&v1, &v2);

						drift_needle_value = acos (dot_product);

						cross_product = (v1.x * v2.y) - (v2.x * v1.y);

						if (cross_product > 0.0)
						{
							drift_needle_value = -drift_needle_value;
						}
					}
				}
			}
		}
	}

	drift_needle_value = bound (drift_needle_value, rad (-30.0), rad (30.0));

	*direction_finder = direction_finder_needle_value;

	*flight_path = flight_path_needle_value;

	*drift = drift_needle_value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_ka50_virtual_cockpit_hsi_needle_values (float *direction_finder, float *flight_path, float *drift)
{
	float
		direction_finder_needle_value,
		flight_path_needle_value,
		drift_needle_value;

	ASSERT  (direction_finder);

	ASSERT (flight_path);

	ASSERT (drift);

	get_ka50_hsi_needle_values (&direction_finder_needle_value, &flight_path_needle_value, &drift_needle_value);

	*direction_finder = direction_finder_needle_value * -1.0;

	*flight_path = flight_path_needle_value * -1.0;

	*drift = drift_needle_value * -1.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_ka50_virtual_cockpit_instruments (void)
{
	matrix3x3
		*attitude;

	object_3d_sub_object_search_data
		search;

	ASSERT (get_gunship_entity ());

	ASSERT (current_flight_dynamics);

	ASSERT (virtual_cockpit_inst3d);

	attitude = get_local_entity_attitude_matrix_ptr (get_gunship_entity ());

	////////////////////////////////////////
	//
	// Main ADI
	//
	////////////////////////////////////////

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_COCKPIT_MAIN_ADI;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		float
			heading,
			pitch,
			roll;

		matrix3x3
			inverse_attitude,
			heading_rotation,
			result;

		//
		// get inverse attitude (attitude * inverse attitude = identity) which aligns the ADI with the world axis
		//

		inverse_attitude[0][0] = (*attitude)[0][0];
		inverse_attitude[1][0] = (*attitude)[0][1];
		inverse_attitude[2][0] = (*attitude)[0][2];
		inverse_attitude[0][1] = (*attitude)[1][0];
		inverse_attitude[1][1] = (*attitude)[1][1];
		inverse_attitude[2][1] = (*attitude)[1][2];
		inverse_attitude[0][2] = (*attitude)[2][0];
		inverse_attitude[1][2] = (*attitude)[2][1];
		inverse_attitude[2][2] = (*attitude)[2][2];

		//
		// rotate heading so that the ADI pitch markings face the pilot
		//

		get_3d_transformation_matrix (heading_rotation, get_heading_from_attitude_matrix (*attitude), 0.0, 0.0);

		multiply_matrix3x3_matrix3x3 (result, heading_rotation, inverse_attitude);

		heading = get_heading_from_attitude_matrix (result);

		pitch = get_pitch_from_attitude_matrix (result);

		roll = get_roll_from_attitude_matrix (result);

		search.result_sub_object->relative_heading = -heading;

		search.result_sub_object->relative_pitch = pitch;

		search.result_sub_object->relative_roll = -roll;
	}

	////////////////////////////////////////
	//
	// Backup ADI
	//
	////////////////////////////////////////

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_COCKPIT_ADI;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		float
			heading,
			pitch,
			roll;

		matrix3x3
			inverse_attitude,
			heading_rotation,
			result;

		//
		// get inverse attitude (attitude * inverse attitude = identity) which aligns the ADI with the world axis
		//

		inverse_attitude[0][0] = (*attitude)[0][0];
		inverse_attitude[1][0] = (*attitude)[0][1];
		inverse_attitude[2][0] = (*attitude)[0][2];
		inverse_attitude[0][1] = (*attitude)[1][0];
		inverse_attitude[1][1] = (*attitude)[1][1];
		inverse_attitude[2][1] = (*attitude)[1][2];
		inverse_attitude[0][2] = (*attitude)[2][0];
		inverse_attitude[1][2] = (*attitude)[2][1];
		inverse_attitude[2][2] = (*attitude)[2][2];

		//
		// rotate heading so that the ADI pitch markings face the pilot
		//

		get_3d_transformation_matrix (heading_rotation, get_heading_from_attitude_matrix (*attitude), 0.0, 0.0);

		multiply_matrix3x3_matrix3x3 (result, heading_rotation, inverse_attitude);

		heading = get_heading_from_attitude_matrix (result);

		pitch = get_pitch_from_attitude_matrix (result);

		roll = get_roll_from_attitude_matrix (result);

		search.result_sub_object->relative_heading = -heading;

		search.result_sub_object->relative_pitch = pitch;

		search.result_sub_object->relative_roll = -roll;
	}

	////////////////////////////////////////
	//
	// HSI
	//
	////////////////////////////////////////
	{
		float
			direction_finder,
			flight_path,
			drift;

		get_ka50_virtual_cockpit_hsi_needle_values (&direction_finder, &flight_path, &drift);

		search.search_depth = 0;
		search.search_object = virtual_cockpit_inst3d;
		search.sub_object_index = OBJECT_3D_SUB_OBJECT_BLACKSHARK_VIRTUAL_COCKPIT_HSI;

		if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			search.result_sub_object->relative_roll = current_flight_dynamics->heading.value;
		}

		//
		// flight path
		//

		search.search_depth = 0;
		search.search_object = virtual_cockpit_inst3d;
		search.sub_object_index = OBJECT_3D_SUB_OBJECT_BLACKSHARK_VIRTUAL_COCKPIT_HSI_ARROW_DOUBLE;

		if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			search.result_sub_object->relative_roll = flight_path;
		}

		//
		// direction finder
		//

		search.search_depth = 0;
		search.search_object = virtual_cockpit_inst3d;
		search.sub_object_index = OBJECT_3D_SUB_OBJECT_BLACKSHARK_VIRTUAL_COCKPIT_HSI_ARROW_LONG;

		if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			search.result_sub_object->relative_roll = direction_finder;
		}

		//
		// drift
		//

		search.search_depth = 0;
		search.search_object = virtual_cockpit_inst3d;
		search.sub_object_index = OBJECT_3D_SUB_OBJECT_BLACKSHARK_VIRTUAL_COCKPIT_HSI_ARROW_SHORT;

		if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			search.result_sub_object->relative_roll = drift;
		}
	}

	////////////////////////////////////////
	//
	// compass
	//
	////////////////////////////////////////

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_COCKPIT_COMPASS;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search.result_sub_object->relative_heading = -current_flight_dynamics->heading.value;
	}

	////////////////////////////////////////
	//
	// airspeed
	//
	////////////////////////////////////////

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_HOKUM_COCKPIT_AIRSPEED;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		float airspeed = bound(kilometres_per_hour(current_flight_dynamics->indicated_airspeed.value), 0.0, 350.0);
		float angle;

		//
		// non-linear scale
		//

//		0 - 20 no movement
//
//		20 - 50 = 95 deg
//		for every 10 kmh, move 30 deg
//
//		50 - 100 = 53 deg
//		for every 50 kmh, move 53deg
//
//		100 - 200 = 90 deg
//		for every 50 kmh, move 45 deg
//
//		200 - 350 = 105 deg
//		for every 50 kmh, move 35 deg

		if (airspeed < 20.0)
			angle = 0.0;
		else if (airspeed < 50.0)
			angle = rad(((airspeed - 20.0)/30.0) * 95.0);
		else if (airspeed < 100.0)
			angle = rad(95.0 + (airspeed - 50.0) * 53.0/50.0);
		else if (airspeed < 200.0)
			angle = rad(148.0 + (airspeed - 100.0) * 90.0/100.0);
		else
			angle = rad(238.0 + (airspeed - 200.0) * 105.0/150.0);

		search.result_sub_object->relative_roll = -angle;
	}


	////////////////////////////////////////
	//
	// Barometric altimeter
	//
	////////////////////////////////////////

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_HOKUM_COCKPIT_ALITIMETER_LARGE;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		float
			altitude;

		altitude = fmod (current_flight_dynamics->barometric_altitude.value, 1000.0f);

		altitude *= rad (-360.0) / 1000.0;

		search.result_sub_object->relative_roll = altitude;
	}

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_HOKUM_COCKPIT_ALITIMETER_SMALL;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		float
			altitude;

		altitude = fmod (current_flight_dynamics->barometric_altitude.value, 10000.0f);

		altitude *= rad (-360.0) / 10000.0;

		search.result_sub_object->relative_roll = altitude;
	}

	////////////////////////////////////////
	//
	// Radar altimeter
	//
	////////////////////////////////////////

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_BLACKSHARK_RDR_ALTIMETER;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		float
			altitude,
			angle;

		altitude = bound((current_flight_dynamics->radar_altitude.value), 0.0, 300.00);

		//
		// non-linear scale
		//

//		up to 50m, move 30 deg for each 10m = 150 deg
//
//		50 - 150m, move 50 deg for each 50m = 100 deg
//
//		150 - 200m, move 25 deg for each 50m = 30 deg
//
//		200 - 300m, move 30 deg for each 100m = 30 deg

		if (altitude < 50.0)
			angle = rad((altitude/50.0) * 150.0);
		else if (altitude < 150.0)
			angle = rad(150.0 + (altitude - 50.0) * 100.0/100.0);
		else if (altitude < 200.0)
			angle = rad(250.0 + (altitude - 150.0) * 30.0/50.0);
		else
			angle = rad(280.0 + (altitude - 200.0) * 30.0/100.0);

		search.result_sub_object->relative_roll = -angle;
	}


	////////////////////////////////////////
	//
	// vertical speed indicator
	//
	////////////////////////////////////////

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_HOKUM_COCKPIT_VERTICAL_SPEED;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		float vertical_speed = bound((metres_per_minute (current_flight_dynamics->world_velocity_y.value) / 60), -30.0, 30.0); //convert to metres per second
		int negative = vertical_speed < 0.0;
		float angle = 0.0;

		vertical_speed = fabs(vertical_speed);

		//
		// non-linear scale
		//

//		up to 10 m/s, move 80 deg
//
//		10 - 20 m/s, move 60 deg
//
//		20 - 30 m/s, move 40 deg

		if (vertical_speed < 10.0)
			angle = rad((vertical_speed / 10.0) * 80.0);
		else if (vertical_speed < 20.0)
			angle = rad(80.0 + (vertical_speed - 10.0) * 60.0/10.0);
		else
			angle = rad(140.0 + (vertical_speed - 20.0) * 40.0/10.0);

		if (negative)
			search.result_sub_object->relative_roll = angle;
		else
			search.result_sub_object->relative_roll = -angle;
	}

	////////////////////////////////////////
	//
	// G METER
	//
	////////////////////////////////////////

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_BLACKSHARK_GMETER_NEEDLE;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		float
			gforce;

		gforce = bound((current_flight_dynamics->g_force.value), -2.0, 4.0);

		gforce *= rad (360.0) / 7.0;

		search.result_sub_object->relative_roll = -gforce;
	}

	// Max G

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_BLACKSHARK_GMAX_NEEDLE;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		float
			gforce;

		static float
			gforce_max;

		gforce = bound((current_flight_dynamics->g_force.value), -2.0, 4.0);

		if (gforce > gforce_max) {
			gforce_max = gforce;

			search.result_sub_object->relative_roll = -gforce_max;
		}
	}

	// Min G

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_BLACKSHARK_GMIN_NEEDLE;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		float
			gforce;

		static float
			gforce_min = 0.0;

		gforce = bound((current_flight_dynamics->g_force.value), -2.0, 4.0);

		if (gforce < gforce_min) {
			gforce_min = gforce;

			search.result_sub_object->relative_roll = -gforce_min;
		}
	}

	////////////////////////////////////////
	//
	// Rotor RPM
	//
	////////////////////////////////////////

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_BLACKSHARK_RTR_RPM;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		float
			rotor_rpm;

		rotor_rpm = bound((current_flight_dynamics->main_rotor_rpm.value), 0.0, 110.0);

		rotor_rpm *= rad (305.0) / 100.0;

		search.result_sub_object->relative_roll = -rotor_rpm;
	}

	////////////////////////////////////////
	//
	// Rotor Blade Pitch
	//
	////////////////////////////////////////

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_BLACKSHARK_BLADE_PITCH;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search.result_sub_object->relative_roll = rad(98) - rad(185.0) *
		(current_flight_dynamics->main_blade_pitch.value - current_flight_dynamics->main_blade_pitch.min)
			/ (current_flight_dynamics->main_blade_pitch.max - current_flight_dynamics->main_blade_pitch.min);
	}

	////////////////////////////////////////
	//
	// LEFT ENGINE NP
	//
	////////////////////////////////////////

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_BLACKSHARK_ENG1_RPM;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		float
			leng_rpm;

		leng_rpm = bound((current_flight_dynamics->left_engine_rpm.value), 0.0, 110.0);

		leng_rpm *= rad (305.0) / 100.0;

		search.result_sub_object->relative_roll = -leng_rpm;
	}

	////////////////////////////////////////
	//
	// RIGHT ENGINE NP
	//
	////////////////////////////////////////

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_BLACKSHARK_ENG2_RPM;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		float
			reng_rpm;

		reng_rpm = bound((current_flight_dynamics->right_engine_rpm.value), 0.0, 110.0);

		reng_rpm *= rad (305.0) / 100.0;

		search.result_sub_object->relative_roll = -reng_rpm;
	}

	////////////////////////////////////////
	//
	// FUEL GAUGE
	//
	////////////////////////////////////////

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_BLACKSHARK_FUEL_GUAGE;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		float
			fuel_value;

		fuel_value = bound((current_flight_dynamics->fuel_weight.value), 0.0, 100.0);
		fuel_value *= rad (320.0) / 100.0;

		search.result_sub_object->relative_roll = -fuel_value;
	}

	////////////////////////////////////////
	//
	// CLOCK
	//
	////////////////////////////////////////

	{
		float
			tod,
			hour_hand_value,
			minute_hand_value,
			second_hand_value;

		tod = get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_TIME_OF_DAY);
		get_analogue_clock_values (tod, &hour_hand_value, &minute_hand_value, &second_hand_value);

		// Hour Hand

		search.search_depth = 0;
		search.search_object = virtual_cockpit_inst3d;
		search.sub_object_index = OBJECT_3D_SUB_OBJECT_BLACKSHARK_CLOCK_HOUR_NEEDLE;

		if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			float
				hour;

			hour = hour_hand_value * rad (360.0) / 12.0;

			search.result_sub_object->relative_roll = -hour;
		}

		// Minute Hand

		search.search_depth = 0;
		search.search_object = virtual_cockpit_inst3d;
		search.sub_object_index = OBJECT_3D_SUB_OBJECT_BLACKSHARK_CLOCK_MINUTE_NEEDLE;

		if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			float
				minute;

			minute = minute_hand_value * rad (360.0) / 60.0;

			search.result_sub_object->relative_roll = -minute;
		}

		// Second Hand

		search.search_depth = 0;
		search.search_object = virtual_cockpit_inst3d;
		search.sub_object_index = OBJECT_3D_SUB_OBJECT_BLACKSHARK_CLOCK_SECOND_NEEDLE;

		if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			float
				second;

			second = second_hand_value * rad (360.0) / 60.0;

			search.result_sub_object->relative_roll = -second;
		}
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
