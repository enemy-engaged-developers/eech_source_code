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

struct SCALE_DATA
{
	short int
		x,
		y;

	float
		value;
};

typedef struct SCALE_DATA scale_data;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static rgb_colour
	white_needle_colour,
	grey_needle_colour,
	yellow_needle_colour,
	orange_needle_colour,
	red_needle_colour,
	white_digit_colour,
	yellow_digit_colour;

static rgb_colour
	white_needle_colour_level1,
	grey_needle_colour_level1,
	yellow_needle_colour_level1,
	orange_needle_colour_level1,
	red_needle_colour_level1,
	white_digit_colour_level1,
	yellow_digit_colour_level1,
	white_needle_colour_level2,
	grey_needle_colour_level2,
	yellow_needle_colour_level2,
	orange_needle_colour_level2,
	red_needle_colour_level2,
	white_digit_colour_level2,
	yellow_digit_colour_level2,
	white_needle_colour_level3,
	grey_needle_colour_level3,
	yellow_needle_colour_level3,
	orange_needle_colour_level3,
	red_needle_colour_level3,
	white_digit_colour_level3,
	yellow_digit_colour_level3;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_havoc_instrument_colours (void)
{
	set_rgb_colour (white_needle_colour_level1,  255, 255, 255, 0);
	set_rgb_colour (grey_needle_colour_level1,  128, 128, 128, 0);
	set_rgb_colour (yellow_needle_colour_level1, 205, 183,  13, 0);
	set_rgb_colour (orange_needle_colour_level1, 255, 147,   0, 0);
	set_rgb_colour (red_needle_colour_level1,    188,  58,  26, 0);
	set_rgb_colour (white_digit_colour_level1,   200, 200, 200, 0);
	set_rgb_colour (yellow_digit_colour_level1,  205, 183,  13, 0);
	set_rgb_colour (white_needle_colour_level2,  255, 147,   0, 0);
	set_rgb_colour (grey_needle_colour_level2,   128,  74,   0, 0);
	set_rgb_colour (yellow_needle_colour_level2, 255, 147,   0, 0);
	set_rgb_colour (orange_needle_colour_level2, 255, 147,   0, 0);
	set_rgb_colour (red_needle_colour_level2,    255, 147,   0, 0);
	set_rgb_colour (white_digit_colour_level2,   255, 147,   0, 0);
	set_rgb_colour (yellow_digit_colour_level2,  205, 183,  13, 0);
	set_rgb_colour (white_needle_colour_level3,  255, 147,   0, 0);
	set_rgb_colour (grey_needle_colour_level3,   128,  74,   0, 0);
	set_rgb_colour (yellow_needle_colour_level3, 255, 147,   0, 0);
	set_rgb_colour (orange_needle_colour_level3, 255, 147,   0, 0);
	set_rgb_colour (red_needle_colour_level3,    255, 147,   0, 0);
	set_rgb_colour (white_digit_colour_level3,   255, 147,   0, 0);
	set_rgb_colour (yellow_digit_colour_level3,  205, 183,  13, 0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_havoc_instrument_colours (void)
{
	switch (get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE))
	{
		case DAY_SEGMENT_TYPE_DAWN:
		{
			white_needle_colour	= white_needle_colour_level2;
			grey_needle_colour = grey_needle_colour_level2;
			yellow_needle_colour	= yellow_needle_colour_level2;
			orange_needle_colour	= orange_needle_colour_level2;
			red_needle_colour		= red_needle_colour_level2;
			white_digit_colour	= white_digit_colour_level2;
			yellow_digit_colour	= yellow_digit_colour_level2;

			break;
		}
		case DAY_SEGMENT_TYPE_DAY:
		{
			white_needle_colour	= white_needle_colour_level1;
			grey_needle_colour = grey_needle_colour_level1;
			yellow_needle_colour	= yellow_needle_colour_level1;
			orange_needle_colour	= orange_needle_colour_level1;
			red_needle_colour		= red_needle_colour_level1;
			white_digit_colour	= white_digit_colour_level1;
			yellow_digit_colour	= yellow_digit_colour_level1;

			break;
		}
		case DAY_SEGMENT_TYPE_DUSK:
		{
			white_needle_colour	= white_needle_colour_level2;
			grey_needle_colour = grey_needle_colour_level2;
			yellow_needle_colour	= yellow_needle_colour_level2;
			orange_needle_colour	= orange_needle_colour_level2;
			red_needle_colour		= red_needle_colour_level2;
			white_digit_colour	= white_digit_colour_level2;
			yellow_digit_colour	= yellow_digit_colour_level2;

			break;
		}
		case DAY_SEGMENT_TYPE_NIGHT:
		{
			white_needle_colour	= white_needle_colour_level3;
			grey_needle_colour = grey_needle_colour_level3;
			yellow_needle_colour	= yellow_needle_colour_level3;
			orange_needle_colour	= orange_needle_colour_level3;
			red_needle_colour		= red_needle_colour_level3;
			white_digit_colour	= white_digit_colour_level3;
			yellow_digit_colour	= yellow_digit_colour_level3;

			break;
		}
	}

	#if DEMO_VERSION

	white_needle_colour	= white_needle_colour_level1;
	yellow_needle_colour	= yellow_needle_colour_level1;
	orange_needle_colour	= orange_needle_colour_level1;
	red_needle_colour		= red_needle_colour_level1;
	white_digit_colour	= white_digit_colour_level1;
	yellow_digit_colour	= yellow_digit_colour_level1;

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// INSTRUMENT VALUES
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void get_hsi_needle_values (float *direction_finder, float *flight_path, float *drift)
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

float get_airspeed_indicator_needle_value (void)
{
	float ias;

	ias = bound(kilometres_per_hour(current_flight_dynamics->indicated_airspeed.value), -50.0, 450.0);

	ias *= rad (-180.0) / 300.0;

	return (ias);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_havoc_g_meter_needle_value (void)
{
	float
		g_meter_value;

	g_meter_value = bound((current_flight_dynamics->g_force.value), -2.0, 4.0);

	return (g_meter_value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_havoc_rad_alt_needle_value (void)
{
	float
	radar_altitude;

	radar_altitude = bound((current_flight_dynamics->radar_altitude.value), 0.00, 500.00);

	return (radar_altitude);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// VIRTUAL COCKPIT
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_havoc_virtual_cockpit_adi_angles (matrix3x3 attitude, float *heading, float *pitch, float *roll)
{
	matrix3x3
		inverse_attitude,
		heading_rotation,
		result;

	//
	// get inverse attitude (attitude * inverse attitude = identity) which aligns the ADI with the world axis
	//

	inverse_attitude[0][0] = attitude[0][0];
	inverse_attitude[1][0] = attitude[0][1];
	inverse_attitude[2][0] = attitude[0][2];
	inverse_attitude[0][1] = attitude[1][0];
	inverse_attitude[1][1] = attitude[1][1];
	inverse_attitude[2][1] = attitude[1][2];
	inverse_attitude[0][2] = attitude[2][0];
	inverse_attitude[1][2] = attitude[2][1];
	inverse_attitude[2][2] = attitude[2][2];

	//
	// rotate heading so that the ADI pitch markings face the pilot
	//

	get_3d_transformation_matrix (heading_rotation, get_heading_from_attitude_matrix (attitude), 0.0, 0.0);

	multiply_matrix3x3_matrix3x3 (result, heading_rotation, inverse_attitude);

	*heading = get_heading_from_attitude_matrix (result);

	*pitch = get_pitch_from_attitude_matrix (result);

	*roll = get_roll_from_attitude_matrix (result);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_havoc_virtual_cockpit_hsi_needle_values (float *direction_finder, float *flight_path, float *drift)
{
	float
		direction_finder_needle_value,
		flight_path_needle_value,
		drift_needle_value;

	ASSERT  (direction_finder);

	ASSERT (flight_path);

	ASSERT (drift);

	get_hsi_needle_values (&direction_finder_needle_value, &flight_path_needle_value, &drift_needle_value);

	*direction_finder = direction_finder_needle_value * -1.0;

	*flight_path = flight_path_needle_value * -1.0;

	*drift = drift_needle_value * -1.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_havoc_virtual_cockpit_vsi_needle_value (void)
{
	float vvi = bound(kilometres_per_hour(current_flight_dynamics->world_velocity_y.value), -30.0, 30.0);
	int negative = vvi < 0.0;
	float roll = 0.0;

	vvi = fabs(vvi);

	if (vvi < 5.0)
		roll = vvi / 5.0 * rad(42.0);
	else if (vvi < 10.0)
		roll = rad(42.0) + (vvi - 5.0) / 5.0 * rad(38.5);
	else if (vvi < 20.0)
		roll = rad(80.5) + (vvi - 10.0) / 10.0 * rad(60.0);
	else
		roll = rad(140.5) + (vvi - 20.0) / 10.0 * rad(39.5);

	if (negative)
		return roll;
	else
		return - roll;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_havoc_virtual_cockpit_gmeter_needle_value (void)
{
	float
	g_meter_value;

	g_meter_value = get_havoc_g_meter_needle_value();

	return -g_meter_value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_havoc_virtual_cockpit_rad_alt_needle_value (void)
{
	float
	radar_alt_value,
	roll = 0.0;

	radar_alt_value = get_havoc_rad_alt_needle_value();

	if (radar_alt_value < 20.0)
		roll = radar_alt_value / 20.0 * rad(29.0);
	else if (radar_alt_value < 60.0)
		roll = rad(29.0) + (radar_alt_value - 20.0) / 40.0 * rad(64.0);
	else if (radar_alt_value < 100.0)
		roll = rad(93.0) + (radar_alt_value - 60.0) / 40.0 * rad(62.0);
	else if (radar_alt_value < 500.0)
		roll = rad(155.0) + (radar_alt_value - 100.0) / 400.0 * rad(105.0);
	else
		roll = rad(260.0) + (radar_alt_value - 500.0) / 200.0 * rad(49.0);

	return -roll;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_havoc_barometric_alt_long_needle_value()
{
	float lng;

	float alt = current_flight_dynamics->barometric_altitude.value;

	lng = -(alt / 1000.0) * 2 * PI;

	return lng;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_havoc_barometric_alt_shrt_needle_value()
{
	float shrt;

	float alt = current_flight_dynamics->barometric_altitude.value;

	shrt = -(alt / 10000.0) * 2 * PI;

	return shrt;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_havoc_fuel_quantity_needle_value(void)
{
	float angle = rad(149.0);

	angle += rad(-0.1196) * current_flight_dynamics->fuel_weight.value * 1.39;  // gauge uses liters, 1.39 liters per kilo

	return angle;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_havoc_clock_hand_values(float* hour_hand, float* minute_hand, float* second_hand)
{
	float
		time_of_day,
		hour_hand_value,
		minute_hand_value,
		second_hand_value;

	time_of_day = get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_TIME_OF_DAY);
	get_analogue_clock_values (time_of_day, &hour_hand_value, &minute_hand_value, &second_hand_value);

	*hour_hand = hour_hand_value * rad(-30.0);
	*minute_hand = minute_hand_value * rad(-6.0);
	*second_hand = floor(second_hand_value) * rad(-6.0);
}


float get_havoc_slip_needle_value(void)
{
	float
		slip;

	slip = kilometres_per_hour (current_flight_dynamics->indicated_slip.value);

	slip = bound (slip, -100.0, 100.0);

	slip *= rad (45.0) / 100.0;

	return slip;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
