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
	yellow_needle_colour,
	orange_needle_colour,
	red_needle_colour,
	white_digit_colour,
	yellow_digit_colour;

static rgb_colour
	white_needle_colour_level1,
	yellow_needle_colour_level1,
	orange_needle_colour_level1,
	red_needle_colour_level1,
	white_digit_colour_level1,
	yellow_digit_colour_level1,
	white_needle_colour_level2,
	yellow_needle_colour_level2,
	orange_needle_colour_level2,
	red_needle_colour_level2,
	white_digit_colour_level2,
	yellow_digit_colour_level2,
	white_needle_colour_level3,
	yellow_needle_colour_level3,
	orange_needle_colour_level3,
	red_needle_colour_level3,
	white_digit_colour_level3,
	yellow_digit_colour_level3;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static char
	*instrument_error = "Cannot draw instrument on panel";

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ha_aspd.h"

#include "ha_balt.h"

#include "ha_clock.h"

#include "ha_erpm.h"

#include "ha_etmp.h"

#include "ha_etrq.h"

#include "ha_fuel.h"

#include "ha_gmtr.h"

#include "ha_ralt.h"

#include "ha_rrpm.h"

#include "ha_vsi.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_havoc_instrument_colours (void)
{
	set_rgb_colour (white_needle_colour_level1,  200, 200, 200, 0);
	set_rgb_colour (yellow_needle_colour_level1, 205, 183,  13, 0);
	set_rgb_colour (orange_needle_colour_level1, 255, 147,   0, 0);
	set_rgb_colour (red_needle_colour_level1,    188,  58,  26, 0);
	set_rgb_colour (white_digit_colour_level1,   200, 200, 200, 0);
	set_rgb_colour (yellow_digit_colour_level1,  205, 183,  13, 0);
	set_rgb_colour (white_needle_colour_level2,  255, 147,   0, 0);
	set_rgb_colour (yellow_needle_colour_level2, 255, 147,   0, 0);
	set_rgb_colour (orange_needle_colour_level2, 255, 147,   0, 0);
	set_rgb_colour (red_needle_colour_level2,    255, 147,   0, 0);
	set_rgb_colour (white_digit_colour_level2,   255, 147,   0, 0);
	set_rgb_colour (yellow_digit_colour_level2,  205, 183,  13, 0);
	set_rgb_colour (white_needle_colour_level3,  255, 147,   0, 0);
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
//
// FIXED COCKPIT
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data *find_scale_value (scale_data *scale, float value)
{
	while (value >= (scale+1)->value)
	{
		scale++;
	}

	return (scale);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_scale_value (scale_data *scale, float value, rgb_colour colour)
{
	while (value >= scale->value)
	{
		set_pixel (ix_640_480 + scale->x, iy_640_480 + scale->y, colour);

		scale++;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void test_scale (scale_data *scale, float first, float last, float step)
{
	float
		value;

	for (value = first; value <= last; value += step)
	{
		scale = find_scale_value (scale, value);

		set_pixel (ix_640_480 + scale->x, iy_640_480 + scale->y, sys_col_red);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_havoc_barometric_altimeter (cockpit_panels panel)
{
	float
		large_needle_value,
		small_needle_value,
		x_centre,
		y_centre;

	scale_data
		*large_needle_scale,
		*small_needle_scale,
		*p;

	if (test_cockpit_instruments)
	{
		static float
			value = 0.0;

		value += 10.0;

		if (value > 10000.0)
		{
			value = 0.0;
		}

		large_needle_value = fmod (value, 1000.0);

		small_needle_value = fmod (value, 10000.0);
	}
	else
	{
		large_needle_value = fmod (current_flight_dynamics->barometric_altitude.value, 1000.0);

		small_needle_value = fmod (current_flight_dynamics->barometric_altitude.value, 10000.0);
	}

	switch (panel)
	{
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_AHEAD:
		////////////////////////////////////////
		{
			x_centre = 75.0;

			y_centre = 394.0;

			large_needle_scale = barometric_altimeter_large_needle_scale_down_20_ahead;

			small_needle_scale = barometric_altimeter_small_needle_scale_down_20_ahead;

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_LEFT30:
		////////////////////////////////////////
		{
			x_centre = 340.0;

			y_centre = 361.0;

			large_needle_scale = barometric_altimeter_large_needle_scale_down_20_left_30;

			small_needle_scale = barometric_altimeter_small_needle_scale_down_20_left_30;

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_LEFT60:
		////////////////////////////////////////
		{
			x_centre = 614.0;

			y_centre = 407.0;

			large_needle_scale = barometric_altimeter_large_needle_scale_down_20_left_60;

			small_needle_scale = barometric_altimeter_small_needle_scale_down_20_left_60;

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal (instrument_error);

			break;
		}
	}

	p = find_scale_value (large_needle_scale, large_needle_value);

	draw_line (fx_640_480 + x_centre, fy_640_480 + y_centre, fx_640_480 + p->x, fy_640_480 + p->y, white_needle_colour);

	p = find_scale_value (small_needle_scale, small_needle_value);

	draw_line (fx_640_480 + x_centre, fy_640_480 + y_centre, fx_640_480 + p->x, fy_640_480 + p->y, white_needle_colour);

	if (test_cockpit_instruments && DEBUG_MODULE)
	{
		test_scale (large_needle_scale, 0.0, 900.0, 100.0);

		test_scale (small_needle_scale, 0.0, 9000.0, 1000.0);

		set_pixel (ix_640_480 + x_centre, iy_640_480 + y_centre, sys_col_red);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_havoc_airspeed_indicator (cockpit_panels panel)
{
	float
		airspeed_needle_value,
		slip_needle_value,
		x_centre,
		y_centre;

	scale_data
		*airspeed_needle_scale,
		*slip_needle_scale,
		*p;

	if (test_cockpit_instruments)
	{
		static float
			value = -100.0;

		value += 5.0;

		if (value > 500.0)
		{
			value = -100.0;
		}

		airspeed_needle_value = value;
	}
	else
	{
		airspeed_needle_value = kilometres_per_hour (current_flight_dynamics->indicated_airspeed.value);
	}

	airspeed_needle_value = bound (airspeed_needle_value, -50.0, 450.0);

	if (test_cockpit_instruments)
	{
		static float
			value = -120.0;

		value += 2.0;

		if (value > 120.0)
		{
			value = -120.0;
		}

		slip_needle_value = value;
	}
	else
	{
		slip_needle_value = kilometres_per_hour (current_flight_dynamics->indicated_slip.value);
	}

	slip_needle_value = bound (slip_needle_value, -100.0, 100.0);

	switch (panel)
	{
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_AHEAD:
		////////////////////////////////////////
		{
			x_centre = 150.0;

			y_centre = 329.0;

			airspeed_needle_scale = airspeed_indicator_airspeed_needle_scale_down_20_ahead;

			slip_needle_scale = airspeed_indicator_slip_needle_scale_down_20_ahead;

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_LEFT30:
		////////////////////////////////////////
		{
			x_centre = 415.0;

			y_centre = 320.0;

			airspeed_needle_scale = airspeed_indicator_airspeed_needle_scale_down_20_left_30;

			slip_needle_scale = airspeed_indicator_slip_needle_scale_down_20_left_30;

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal (instrument_error);

			break;
		}
	}

	//
	// draw white needle over yellow needle
	//

	p = find_scale_value (slip_needle_scale, slip_needle_value);

	draw_line (fx_640_480 + x_centre, fy_640_480 + y_centre, fx_640_480 + p->x, fy_640_480 + p->y, yellow_needle_colour);

	p = find_scale_value (airspeed_needle_scale, airspeed_needle_value);

	draw_line (fx_640_480 + x_centre, fy_640_480 + y_centre, fx_640_480 + p->x, fy_640_480 + p->y, white_needle_colour);

	if (test_cockpit_instruments && DEBUG_MODULE)
	{
		test_scale (airspeed_needle_scale, -50.0, 450.0, 50.0);

		test_scale (slip_needle_scale, -100.0, 100.0, 50.0);

		set_pixel (ix_640_480 + x_centre, iy_640_480 + y_centre, sys_col_red);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_havoc_main_rotor_rpm_indicator (cockpit_panels panel)
{
	float
		main_rotor_rpm_needle_value,
		x_centre,
		y_centre;

	scale_data
		*main_rotor_rpm_needle_scale,
		*p;

	if (test_cockpit_instruments)
	{
		static float
			value = -10.0;

		value += 1.0;

		if (value > 110.0)
		{
			value = -10.0;
		}

		main_rotor_rpm_needle_value = value;
	}
	else
	{
		main_rotor_rpm_needle_value = current_flight_dynamics->main_rotor_rpm.value;
	}

	main_rotor_rpm_needle_value = bound (main_rotor_rpm_needle_value, 0.0, 100.0);

	switch (panel)
	{
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_AHEAD:
		////////////////////////////////////////
		{
			x_centre = 88.0;

			y_centre = 329.0;

			main_rotor_rpm_needle_scale = main_rotor_rpm_indicator_needle_scale_down_20_ahead;

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_LEFT30:
		////////////////////////////////////////
		{
			x_centre = 361.0;

			y_centre = 307.0;

			main_rotor_rpm_needle_scale = main_rotor_rpm_indicator_needle_scale_down_20_left_30;

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal (instrument_error);

			break;
		}
	}

	p = find_scale_value (main_rotor_rpm_needle_scale, main_rotor_rpm_needle_value);

	draw_line (fx_640_480 + x_centre, fy_640_480 + y_centre, fx_640_480 + p->x, fy_640_480 + p->y, white_needle_colour);

	if (test_cockpit_instruments && DEBUG_MODULE)
	{
		test_scale (main_rotor_rpm_needle_scale, 0.0, 100.0, 10.0);

		set_pixel (ix_640_480 + x_centre, iy_640_480 + y_centre, sys_col_red);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_havoc_g_meter (cockpit_panels panel)
{
	float
		g_meter_needle_value,
		x_centre,
		y_centre;

	scale_data
		*g_meter_needle_scale,
		*p;

	if (test_cockpit_instruments)
	{
		static float
			value = -2.5;

		value += 0.05;

		if (value > 4.5)
		{
			value = -2.5;
		}

		g_meter_needle_value = value;
	}
	else
	{
		g_meter_needle_value = current_flight_dynamics->g_force.value;
	}

	g_meter_needle_value = bound (g_meter_needle_value, -2.0, 4.0);

	switch (panel)
	{
		////////////////////////////////////////
		case COCKPIT_PANEL_LEVEL_AHEAD:
		////////////////////////////////////////
		{
			x_centre = 117.0;

			y_centre = 374.0;

			g_meter_needle_scale = g_meter_needle_scale_level_ahead;

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_AHEAD:
		////////////////////////////////////////
		{
			x_centre = 122.0;

			y_centre = 177.0;

			g_meter_needle_scale = g_meter_needle_scale_down_20_ahead;

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_LEVEL_LEFT30:
		////////////////////////////////////////
		{
			x_centre = 418.0;

			y_centre = 368.0;

			g_meter_needle_scale = g_meter_needle_scale_level_left_30;

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_LEFT30:
		////////////////////////////////////////
		{
			x_centre = 416.0;

			y_centre = 171.0;

			g_meter_needle_scale = g_meter_needle_scale_down_20_left_30;

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal (instrument_error);

			break;
		}
	}

	p = find_scale_value (g_meter_needle_scale, g_meter_needle_value);

	draw_line (fx_640_480 + x_centre, fy_640_480 + y_centre, fx_640_480 + p->x, fy_640_480 + p->y, white_needle_colour);

	if (test_cockpit_instruments && DEBUG_MODULE)
	{
		test_scale (g_meter_needle_scale, -2.0, 4.0, 1.0);

		set_pixel (ix_640_480 + x_centre, iy_640_480 + y_centre, sys_col_red);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_havoc_engine_torque_indicator (cockpit_panels panel)
{
	float
		lh_engine_torque_indicator_value,
		rh_engine_torque_indicator_value;

	scale_data
		*lh_engine_torque_indicator_scale1,
		*lh_engine_torque_indicator_scale2,
		*rh_engine_torque_indicator_scale1,
		*rh_engine_torque_indicator_scale2;

	if (test_cockpit_instruments)
	{
		static float
			value = -10.0;

		value += 2.0;

		if (value > 120.0)
		{
			value = -10.0;
		}

		lh_engine_torque_indicator_value = value;

		rh_engine_torque_indicator_value = value;
	}
	else
	{
		lh_engine_torque_indicator_value = current_flight_dynamics->left_engine_torque.value;

		rh_engine_torque_indicator_value = current_flight_dynamics->right_engine_torque.value;
	}

	lh_engine_torque_indicator_value = bound (lh_engine_torque_indicator_value, 0.0, 110.0);

	rh_engine_torque_indicator_value = bound (rh_engine_torque_indicator_value, 0.0, 110.0);

	switch (panel)
	{
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_AHEAD:
		////////////////////////////////////////
		{
			lh_engine_torque_indicator_scale1 = lh_engine_torque_indicator_line1_down_20_ahead;

			lh_engine_torque_indicator_scale2 = lh_engine_torque_indicator_line2_down_20_ahead;

			rh_engine_torque_indicator_scale1 = rh_engine_torque_indicator_line1_down_20_ahead;

			rh_engine_torque_indicator_scale2 = rh_engine_torque_indicator_line2_down_20_ahead;

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_RIGHT30:
		////////////////////////////////////////
		{
			lh_engine_torque_indicator_scale1 = lh_engine_torque_indicator_line1_down_20_right_30;

			lh_engine_torque_indicator_scale2 = lh_engine_torque_indicator_line2_down_20_right_30;

			rh_engine_torque_indicator_scale1 = rh_engine_torque_indicator_line1_down_20_right_30;

			rh_engine_torque_indicator_scale2 = rh_engine_torque_indicator_line2_down_20_right_30;

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal (instrument_error);

			break;
		}
	}

	draw_scale_value (lh_engine_torque_indicator_scale1, lh_engine_torque_indicator_value, white_needle_colour);

	draw_scale_value (lh_engine_torque_indicator_scale2, lh_engine_torque_indicator_value, white_needle_colour);

	draw_scale_value (rh_engine_torque_indicator_scale1, rh_engine_torque_indicator_value, white_needle_colour);

	draw_scale_value (rh_engine_torque_indicator_scale2, rh_engine_torque_indicator_value, white_needle_colour);

	if (test_cockpit_instruments && DEBUG_MODULE)
	{
		test_scale (lh_engine_torque_indicator_scale1, 0.0, 110.0, 10.0);

		test_scale (lh_engine_torque_indicator_scale2, 0.0, 110.0, 10.0);

		test_scale (rh_engine_torque_indicator_scale1, 0.0, 110.0, 10.0);

		test_scale (rh_engine_torque_indicator_scale2, 0.0, 110.0, 10.0);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_havoc_engine_temperature_indicator (cockpit_panels panel)
{
	float
		lh_engine_temperature_indicator_value,
		rh_engine_temperature_indicator_value;

	scale_data
		*lh_engine_temperature_indicator_scale,
		*rh_engine_temperature_indicator_scale;

	if (test_cockpit_instruments)
	{
		static float
			value = -100.0;

		value += 20.0;

		if (value > 1100.0)
		{
			value = -100.0;
		}

		lh_engine_temperature_indicator_value = value;

		rh_engine_temperature_indicator_value = value;
	}
	else
	{
		lh_engine_temperature_indicator_value = current_flight_dynamics->left_engine_temp.value;

		rh_engine_temperature_indicator_value = current_flight_dynamics->right_engine_temp.value;
	}

	lh_engine_temperature_indicator_value = bound (lh_engine_temperature_indicator_value, 0.0, 1000.0);

	rh_engine_temperature_indicator_value = bound (rh_engine_temperature_indicator_value, 0.0, 1000.0);

	switch (panel)
	{
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_AHEAD:
		////////////////////////////////////////
		{
			lh_engine_temperature_indicator_scale = lh_engine_temperature_indicator_line_down_20_ahead;

			rh_engine_temperature_indicator_scale = rh_engine_temperature_indicator_line_down_20_ahead;

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_RIGHT30:
		////////////////////////////////////////
		{
			lh_engine_temperature_indicator_scale = lh_engine_temperature_indicator_line_down_20_right_30;

			rh_engine_temperature_indicator_scale = rh_engine_temperature_indicator_line_down_20_right_30;

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal (instrument_error);

			break;
		}
	}

	draw_scale_value (lh_engine_temperature_indicator_scale, lh_engine_temperature_indicator_value, orange_needle_colour);

	draw_scale_value (rh_engine_temperature_indicator_scale, rh_engine_temperature_indicator_value, orange_needle_colour);

	if (test_cockpit_instruments && DEBUG_MODULE)
	{
		test_scale (lh_engine_temperature_indicator_scale, 0.0, 1000.0, 100.0);

		test_scale (rh_engine_temperature_indicator_scale, 0.0, 1000.0, 100.0);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_havoc_engine_rpm_indicator (cockpit_panels panel)
{
	float
		lh_engine_rpm_indicator_value,
		rh_engine_rpm_indicator_value;

	scale_data
		*lh_engine_rpm_indicator_scale1,
		*lh_engine_rpm_indicator_scale2,
		*lh_engine_rpm_indicator_scale3,
		*rh_engine_rpm_indicator_scale1,
		*rh_engine_rpm_indicator_scale2,
		*rh_engine_rpm_indicator_scale3;

	if (test_cockpit_instruments)
	{
		static float
			value = -10.0;

		value += 2.0;

		if (value > 120.0)
		{
			value = -10.0;
		}

		lh_engine_rpm_indicator_value = value;

		rh_engine_rpm_indicator_value = value;
	}
	else
	{
		lh_engine_rpm_indicator_value = current_flight_dynamics->left_engine_rpm.value;

		rh_engine_rpm_indicator_value = current_flight_dynamics->right_engine_rpm.value;
	}

	lh_engine_rpm_indicator_value = bound (lh_engine_rpm_indicator_value, 0.0, 110.0);

	rh_engine_rpm_indicator_value = bound (rh_engine_rpm_indicator_value, 0.0, 110.0);

	switch (panel)
	{
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_AHEAD:
		////////////////////////////////////////
		{
			lh_engine_rpm_indicator_scale1 = lh_engine_rpm_indicator_line1_down_20_ahead;

			lh_engine_rpm_indicator_scale2 = lh_engine_rpm_indicator_line2_down_20_ahead;

			lh_engine_rpm_indicator_scale3 = lh_engine_rpm_indicator_line3_down_20_ahead;

			rh_engine_rpm_indicator_scale1 = rh_engine_rpm_indicator_line1_down_20_ahead;

			rh_engine_rpm_indicator_scale2 = rh_engine_rpm_indicator_line2_down_20_ahead;

			rh_engine_rpm_indicator_scale3 = rh_engine_rpm_indicator_line3_down_20_ahead;

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_RIGHT30:
		////////////////////////////////////////
		{
			lh_engine_rpm_indicator_scale1 = lh_engine_rpm_indicator_line1_down_20_right_30;

			lh_engine_rpm_indicator_scale2 = lh_engine_rpm_indicator_line2_down_20_right_30;

			lh_engine_rpm_indicator_scale3 = lh_engine_rpm_indicator_line3_down_20_right_30;

			rh_engine_rpm_indicator_scale1 = rh_engine_rpm_indicator_line1_down_20_right_30;

			rh_engine_rpm_indicator_scale2 = rh_engine_rpm_indicator_line2_down_20_right_30;

			rh_engine_rpm_indicator_scale3 = rh_engine_rpm_indicator_line3_down_20_right_30;

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal (instrument_error);

			break;
		}
	}

	draw_scale_value (lh_engine_rpm_indicator_scale1, lh_engine_rpm_indicator_value, white_needle_colour);

	draw_scale_value (lh_engine_rpm_indicator_scale2, lh_engine_rpm_indicator_value, white_needle_colour);

	draw_scale_value (lh_engine_rpm_indicator_scale3, lh_engine_rpm_indicator_value, white_needle_colour);

	draw_scale_value (rh_engine_rpm_indicator_scale1, rh_engine_rpm_indicator_value, white_needle_colour);

	draw_scale_value (rh_engine_rpm_indicator_scale2, rh_engine_rpm_indicator_value, white_needle_colour);

	draw_scale_value (rh_engine_rpm_indicator_scale3, rh_engine_rpm_indicator_value, white_needle_colour);

	if (test_cockpit_instruments && DEBUG_MODULE)
	{
		test_scale (lh_engine_rpm_indicator_scale1, 0.0, 110.0, 10.0);

		test_scale (lh_engine_rpm_indicator_scale2, 0.0, 110.0, 10.0);

		test_scale (lh_engine_rpm_indicator_scale3, 0.0, 110.0, 10.0);

		test_scale (rh_engine_rpm_indicator_scale1, 0.0, 110.0, 10.0);

		test_scale (rh_engine_rpm_indicator_scale2, 0.0, 110.0, 10.0);

		test_scale (rh_engine_rpm_indicator_scale3, 0.0, 110.0, 10.0);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_havoc_engine_temperature_and_rpm_indicator_ticks (cockpit_panels panel)
{
	rgb_alpha_masked_sprite_data
		lh_engine_temperature_tick_sprite,
		rh_engine_temperature_tick_sprite,
		lh_engine_rpm_tick_sprite,
		rh_engine_rpm_tick_sprite;

	switch (panel)
	{
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_AHEAD:
		////////////////////////////////////////
		{
			static rgb_alpha_masked_sprite_data
				lh_temperature_sprite = {493, 409, 137, 213, 7, 4, 237},
				rh_temperature_sprite = {517, 409, 161, 213, 7, 4, 237},
				lh_rpm_sprite = {498, 388, 142, 192, 7, 3, 237},
				rh_rpm_sprite = {512, 388, 156, 192, 7, 3, 237};

			memcpy (&lh_engine_temperature_tick_sprite, &lh_temperature_sprite, sizeof (rgb_alpha_masked_sprite_data));

			memcpy (&rh_engine_temperature_tick_sprite, &rh_temperature_sprite, sizeof (rgb_alpha_masked_sprite_data));

			memcpy (&lh_engine_rpm_tick_sprite, &lh_rpm_sprite, sizeof (rgb_alpha_masked_sprite_data));

			memcpy (&rh_engine_rpm_tick_sprite, &rh_rpm_sprite, sizeof (rgb_alpha_masked_sprite_data));

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_RIGHT30:
		////////////////////////////////////////
		{
			static rgb_alpha_masked_sprite_data
				lh_temperature_sprite = {241, 393, 177, 217, 7, 5, 237},
				rh_temperature_sprite = {262, 386, 198, 210, 7, 5, 237},
				lh_rpm_sprite = {242, 372, 178, 196, 7, 3, 237},
				rh_rpm_sprite = {255, 368, 191, 192, 6, 3, 237};

			memcpy (&lh_engine_temperature_tick_sprite, &lh_temperature_sprite, sizeof (rgb_alpha_masked_sprite_data));

			memcpy (&rh_engine_temperature_tick_sprite, &rh_temperature_sprite, sizeof (rgb_alpha_masked_sprite_data));

			memcpy (&lh_engine_rpm_tick_sprite, &lh_rpm_sprite, sizeof (rgb_alpha_masked_sprite_data));

			memcpy (&rh_engine_rpm_tick_sprite, &rh_rpm_sprite, sizeof (rgb_alpha_masked_sprite_data));

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal (instrument_error);

			break;
		}
	}

	lh_engine_temperature_tick_sprite.x += ix_640_480;
	lh_engine_temperature_tick_sprite.y += iy_640_480;

	blit_rgb_alpha_masked_sprite
	(
		get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_SPRITES),
		get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_SPRITES_MASK),
		&lh_engine_temperature_tick_sprite
	);

	rh_engine_temperature_tick_sprite.x += ix_640_480;
	rh_engine_temperature_tick_sprite.y += iy_640_480;

	blit_rgb_alpha_masked_sprite
	(
		get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_SPRITES),
		get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_SPRITES_MASK),
		&rh_engine_temperature_tick_sprite
	);

	lh_engine_rpm_tick_sprite.x += ix_640_480;
	lh_engine_rpm_tick_sprite.y += iy_640_480;

	blit_rgb_alpha_masked_sprite
	(
		get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_SPRITES),
		get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_SPRITES_MASK),
		&lh_engine_rpm_tick_sprite
	);

	rh_engine_rpm_tick_sprite.x += ix_640_480;
	rh_engine_rpm_tick_sprite.y += iy_640_480;

	blit_rgb_alpha_masked_sprite
	(
		get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_SPRITES),
		get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_SPRITES_MASK),
		&rh_engine_rpm_tick_sprite
	);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_havoc_vertical_speed_indicator (cockpit_panels panel)
{
	float
		vertical_speed_needle_value,
		x_centre,
		y_centre;

	scale_data
		*vertical_speed_needle_scale,
		*p;

	if (test_cockpit_instruments)
	{
		static float
			value = -350.0;

		value += 5.0;

		if (value > 350.0)
		{
			value = -350.0;
		}

		vertical_speed_needle_value = value;
	}
	else
	{
		vertical_speed_needle_value = metres_per_minute (current_flight_dynamics->world_velocity_y.value);
	}

	vertical_speed_needle_value = bound (vertical_speed_needle_value, -300.0, 300.0);

	switch (panel)
	{
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_AHEAD:
		////////////////////////////////////////
		{
			x_centre = 135.0;

			y_centre = 394.0;

			vertical_speed_needle_scale = vertical_speed_indicator_needle_scale_down_20_ahead;

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_LEFT30:
		////////////////////////////////////////
		{
			x_centre = 391.0;

			y_centre = 377.0;

			vertical_speed_needle_scale = vertical_speed_indicator_needle_scale_down_20_left_30;

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal (instrument_error);

			break;
		}
	}

	p = find_scale_value (vertical_speed_needle_scale, vertical_speed_needle_value);

	draw_line (fx_640_480 + x_centre, fy_640_480 + y_centre, fx_640_480 + p->x, fy_640_480 + p->y, white_needle_colour);

	if (test_cockpit_instruments && DEBUG_MODULE)
	{
		test_scale (vertical_speed_needle_scale, -300.0, 300.0, 50.0);

		set_pixel (ix_640_480 + x_centre, iy_640_480 + y_centre, sys_col_red);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_havoc_clock (cockpit_panels panel)
{
	float
		time_of_day,
		hour_hand_value,
		minute_hand_value,
		second_hand_value,
		x_centre,
		y_centre;

	scale_data
		*hour_hand_scale,
		*minute_hand_scale,
		*second_hand_scale,
		*p;

	if (test_cockpit_instruments)
	{
		static float
			hour_value = 0.0,
			minute_value = 30.0,
			second_value = 0.0;

		hour_value += 0.1;

		if (hour_value >= 12.0)
		{
			hour_value = 0.0;
		}

		minute_value += 0.5;

		if (minute_value >= 60.0)
		{
			minute_value = 0.0;
		}

		second_value += 1.0;

		if (second_value >= 60.0)
		{
			second_value = 0.0;
		}

		hour_hand_value = hour_value;

		minute_hand_value = minute_value;

		second_hand_value = second_value;
	}
	else
	{
		time_of_day = get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_TIME_OF_DAY);

		get_analogue_clock_values (time_of_day, &hour_hand_value, &minute_hand_value, &second_hand_value);
	}

	switch (panel)
	{
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_AHEAD:
		////////////////////////////////////////
		{
			x_centre = 290.0;

			y_centre = 436.0;

			hour_hand_scale = clock_small_hand_scale_down_20_ahead;

			minute_hand_scale = clock_large_hand_scale_down_20_ahead;

			second_hand_scale = clock_large_hand_scale_down_20_ahead;

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_LEFT30:
		////////////////////////////////////////
		{
			x_centre = 539.0;

			y_centre = 469.0;

			hour_hand_scale = clock_small_hand_scale_down_20_left_30;

			minute_hand_scale = clock_large_hand_scale_down_20_left_30;

			second_hand_scale = clock_large_hand_scale_down_20_left_30;

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal (instrument_error);

			break;
		}
	}

	//
	// draw second hand over minute hand over hour hand
	//

	p = find_scale_value (hour_hand_scale, hour_hand_value);

	draw_line (fx_640_480 + x_centre, fy_640_480 + y_centre, fx_640_480 + p->x, fy_640_480 + p->y, white_needle_colour);

	p = find_scale_value (minute_hand_scale, minute_hand_value);

	draw_line (fx_640_480 + x_centre, fy_640_480 + y_centre, fx_640_480 + p->x, fy_640_480 + p->y, white_needle_colour);

	p = find_scale_value (second_hand_scale, second_hand_value);

	draw_line (fx_640_480 + x_centre, fy_640_480 + y_centre, fx_640_480 + p->x, fy_640_480 + p->y, red_needle_colour);

	if (test_cockpit_instruments && DEBUG_MODULE)
	{
		test_scale (minute_hand_scale, 0.0, 55.0, 5.0);

		test_scale (hour_hand_scale, 0.0, 11.0, 1.0);

		set_pixel (ix_640_480 + x_centre, iy_640_480 + y_centre, sys_col_red);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_havoc_radar_altimeter (cockpit_panels panel)
{
	float
		radar_altimeter_needle_value,
		x_centre,
		y_centre;

	scale_data
		*radar_altimeter_needle_scale,
		*p;

	if (test_cockpit_instruments)
	{
		static float
			value = -20.0;

		if (value < 100.0)
		{
			value += 2.0;
		}
		else
		{
			value += 10.0;
		}

		if (value > 400.0)
		{
			value = -20.0;
		}

		radar_altimeter_needle_value = value;
	}
	else
	{
		radar_altimeter_needle_value = current_flight_dynamics->radar_altitude.value;
	}

	radar_altimeter_needle_value = bound (radar_altimeter_needle_value, 0.0, 300.0);

	switch (panel)
	{
		////////////////////////////////////////
		case COCKPIT_PANEL_LEVEL_AHEAD:
		////////////////////////////////////////
		{
			x_centre = 102.0;

			y_centre = 430.0;

			radar_altimeter_needle_scale = radar_altimeter_needle_scale_level_ahead;

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_AHEAD:
		////////////////////////////////////////
		{
			x_centre = 114.0;

			y_centre = 229.0;

			radar_altimeter_needle_scale = radar_altimeter_needle_scale_down_20_ahead;

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_LEVEL_LEFT30:
		////////////////////////////////////////
		{
			x_centre = 404.0;

			y_centre = 419.0;

			radar_altimeter_needle_scale = radar_altimeter_needle_scale_level_left_30;

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_LEFT30:
		////////////////////////////////////////
		{
			x_centre = 400.0;

			y_centre = 219.0;

			radar_altimeter_needle_scale = radar_altimeter_needle_scale_down_20_left_30;

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal (instrument_error);

			break;
		}
	}

	p = find_scale_value (radar_altimeter_needle_scale, radar_altimeter_needle_value);

	draw_line (fx_640_480 + x_centre, fy_640_480 + y_centre, fx_640_480 + p->x, fy_640_480 + p->y, white_needle_colour);

	if (test_cockpit_instruments && DEBUG_MODULE)
	{
		test_scale (radar_altimeter_needle_scale, 0.0, 80.0, 20.0);

		test_scale (radar_altimeter_needle_scale, 100.0, 300.0, 100.0);

		set_pixel (ix_640_480 + x_centre, iy_640_480 + y_centre, sys_col_red);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_havoc_fuel_gauge (cockpit_panels panel)
{
	float
		fuel_gauge_needle_value,
		x_centre,
		y_centre;

	scale_data
		*fuel_gauge_needle_scale,
		*p;

	rgb_alpha_masked_sprite_data
		yellow_dot_sprite;

	if (test_cockpit_instruments)
	{
		static float
			value = -500.0;

		value += 50.0;

		if (value > 2000.0)
		{
			value = -500.0;
		}

		fuel_gauge_needle_value = value;
	}
	else
	{
		fuel_gauge_needle_value = current_flight_dynamics->fuel_weight.value;
	}

	fuel_gauge_needle_value = bound (fuel_gauge_needle_value, 0.0, 1600.0);

	switch (panel)
	{
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_AHEAD:
		////////////////////////////////////////
		{
			static rgb_alpha_masked_sprite_data
				sprite = {414, 431, 135, 230, 12, 12, 235};

			x_centre = 419.0;

			y_centre = 436.0;

			fuel_gauge_needle_scale = fuel_gauge_needle_scale_down_20_ahead;

			memcpy (&yellow_dot_sprite, &sprite, sizeof (rgb_alpha_masked_sprite_data));

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_RIGHT30:
		////////////////////////////////////////
		{
			static rgb_alpha_masked_sprite_data
				sprite = {171, 439, 157, 230, 11, 11, 235};

			x_centre = 176.0;

			y_centre = 443.0;

			fuel_gauge_needle_scale = fuel_gauge_needle_scale_down_20_right_30;

			memcpy (&yellow_dot_sprite, &sprite, sizeof (rgb_alpha_masked_sprite_data));

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal (instrument_error);

			break;
		}
	}

	p = find_scale_value (fuel_gauge_needle_scale, fuel_gauge_needle_value);

	draw_line (fx_640_480 + x_centre, fy_640_480 + y_centre, fx_640_480 + p->x, fy_640_480 + p->y, white_needle_colour);

	if (test_cockpit_instruments && DEBUG_MODULE)
	{
		test_scale (fuel_gauge_needle_scale, 0.0, 2000.0, 500.0);

		set_pixel (ix_640_480 + x_centre, iy_640_480 + y_centre, sys_col_red);
	}

	yellow_dot_sprite.x += ix_640_480;
	yellow_dot_sprite.y += iy_640_480;

	blit_rgb_alpha_masked_sprite
	(
		get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_SPRITES),
		get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_SPRITES_MASK),
		&yellow_dot_sprite
	);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_havoc_fixed_cockpit_hsi_waypoint_distance_digits (cockpit_panels panel)
{
	float
		distance_digital_value,
		x,
		y,
		whole_digit,
		fractional_digit;

	entity
		*en,
		*wp;

	vec3d
		*en_position,
		wp_position;

	en = get_gunship_entity ();

	wp = get_local_entity_current_waypoint (en);

	distance_digital_value = 0.0;

	if ((wp) && (!havoc_damage.navigation_computer))
	{
		en_position = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

		get_waypoint_display_position (en, wp, &wp_position);

		distance_digital_value = get_2d_range (en_position, &wp_position) * 0.001;
	}

	switch (panel)
	{
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_AHEAD:
		////////////////////////////////////////
		{
			set_mono_font_type (MONO_FONT_TYPE_3X6);

			set_viewport (fx_640_480 + 179.0, fy_640_480 + 384.0, fx_640_480 + 189.999, fy_640_480 + 388.999);

			////////////////////////////////////////
			//
			// tenths digit
			//
			////////////////////////////////////////

			#define ONE_REV		  				(1.0)
			#define ONE_TENTH_REV				((ONE_REV) / 10.0)
			#define ONE_OVER_ONE_TENTH_REV	(1.0 / (ONE_TENTH_REV))
			#define DIGIT_CHANGE_THRESHOLD	(0.01)

			set_mono_font_colour (yellow_digit_colour);

			x = fx_640_480 + 187.0;
			y = fy_640_480 + 384.0 + 6.0;

			whole_digit = fmod (distance_digital_value, ONE_REV);

			fractional_digit = fmod (distance_digital_value, ONE_TENTH_REV);

			y += (float) ((int) (whole_digit * ONE_OVER_ONE_TENTH_REV)) * 6.0;

			//
			// rotate digits near change-over point (except at bottom zero)
			//

			if (distance_digital_value >= DIGIT_CHANGE_THRESHOLD)
			{
				if (fractional_digit <= DIGIT_CHANGE_THRESHOLD)
				{
					y += (fractional_digit - DIGIT_CHANGE_THRESHOLD) * (3.0 / DIGIT_CHANGE_THRESHOLD);
				}
				else if (fractional_digit >= (ONE_TENTH_REV - DIGIT_CHANGE_THRESHOLD))
				{
					y += (fractional_digit - (ONE_TENTH_REV - DIGIT_CHANGE_THRESHOLD)) * (3.0 / DIGIT_CHANGE_THRESHOLD);
				}
			}

			set_mono_font_position (x, y); print_mono_font_char ('9'); y -= 6.0;
			set_mono_font_position (x, y); print_mono_font_char ('0'); y -= 6.0;
			set_mono_font_position (x, y); print_mono_font_char ('1'); y -= 6.0;
			set_mono_font_position (x, y); print_mono_font_char ('2'); y -= 6.0;
			set_mono_font_position (x, y); print_mono_font_char ('3'); y -= 6.0;
			set_mono_font_position (x, y); print_mono_font_char ('4'); y -= 6.0;
			set_mono_font_position (x, y); print_mono_font_char ('5'); y -= 6.0;
			set_mono_font_position (x, y); print_mono_font_char ('6'); y -= 6.0;
			set_mono_font_position (x, y); print_mono_font_char ('7'); y -= 6.0;
			set_mono_font_position (x, y); print_mono_font_char ('8'); y -= 6.0;
			set_mono_font_position (x, y); print_mono_font_char ('9'); y -= 6.0;
			set_mono_font_position (x, y); print_mono_font_char ('0');

			#undef ONE_REV
			#undef ONE_TENTH_REV
			#undef ONE_OVER_ONE_TENTH_REV
			#undef DIGIT_CHANGE_THRESHOLD

			////////////////////////////////////////
			//
			// units digit
			//
			////////////////////////////////////////

			#define ONE_REV		  				(10.0)
			#define ONE_TENTH_REV				((ONE_REV) / 10.0)
			#define ONE_OVER_ONE_TENTH_REV	(1.0 / (ONE_TENTH_REV))
			#define DIGIT_CHANGE_THRESHOLD	(0.01)

			set_mono_font_colour (white_digit_colour);

			x = fx_640_480 + 183.0;
			y = fy_640_480 + 384.0 + 6.0;

			whole_digit = fmod (distance_digital_value, ONE_REV);

			fractional_digit = fmod (distance_digital_value, ONE_TENTH_REV);

			y += (float) ((int) (whole_digit * ONE_OVER_ONE_TENTH_REV)) * 6.0;

			//
			// rotate digits near change-over point (except at bottom zero)
			//

			if (distance_digital_value >= DIGIT_CHANGE_THRESHOLD)
			{
				if (fractional_digit <= DIGIT_CHANGE_THRESHOLD)
				{
					y += (fractional_digit - DIGIT_CHANGE_THRESHOLD) * (3.0 / DIGIT_CHANGE_THRESHOLD);
				}
				else if (fractional_digit >= (ONE_TENTH_REV - DIGIT_CHANGE_THRESHOLD))
				{
					y += (fractional_digit - (ONE_TENTH_REV - DIGIT_CHANGE_THRESHOLD)) * (3.0 / DIGIT_CHANGE_THRESHOLD);
				}
			}

			set_mono_font_position (x, y); print_mono_font_char ('9'); y -= 6.0;
			set_mono_font_position (x, y); print_mono_font_char ('0'); y -= 6.0;
			set_mono_font_position (x, y); print_mono_font_char ('1'); y -= 6.0;
			set_mono_font_position (x, y); print_mono_font_char ('2'); y -= 6.0;
			set_mono_font_position (x, y); print_mono_font_char ('3'); y -= 6.0;
			set_mono_font_position (x, y); print_mono_font_char ('4'); y -= 6.0;
			set_mono_font_position (x, y); print_mono_font_char ('5'); y -= 6.0;
			set_mono_font_position (x, y); print_mono_font_char ('6'); y -= 6.0;
			set_mono_font_position (x, y); print_mono_font_char ('7'); y -= 6.0;
			set_mono_font_position (x, y); print_mono_font_char ('8'); y -= 6.0;
			set_mono_font_position (x, y); print_mono_font_char ('9'); y -= 6.0;
			set_mono_font_position (x, y); print_mono_font_char ('0');

			#undef ONE_REV
			#undef ONE_TENTH_REV
			#undef ONE_OVER_ONE_TENTH_REV
			#undef DIGIT_CHANGE_THRESHOLD

			////////////////////////////////////////
			//
			// tens digit
			//
			////////////////////////////////////////

			#define ONE_REV		  				(100.0)
			#define ONE_TENTH_REV				((ONE_REV) / 10.0)
			#define ONE_OVER_ONE_TENTH_REV	(1.0 / (ONE_TENTH_REV))
			#define DIGIT_CHANGE_THRESHOLD	(0.01)

			set_mono_font_colour (white_digit_colour);

			x = fx_640_480 + 179.0;
			y = fy_640_480 + 384.0 + 6.0;

			whole_digit = fmod (distance_digital_value, ONE_REV);

			fractional_digit = fmod (distance_digital_value, ONE_TENTH_REV);

			y += (float) ((int) (whole_digit * ONE_OVER_ONE_TENTH_REV)) * 6.0;

			//
			// rotate digits near change-over point (except at bottom zero)
			//

			if (distance_digital_value >= DIGIT_CHANGE_THRESHOLD)
			{
				if (fractional_digit <= DIGIT_CHANGE_THRESHOLD)
				{
					y += (fractional_digit - DIGIT_CHANGE_THRESHOLD) * (3.0 / DIGIT_CHANGE_THRESHOLD);
				}
				else if (fractional_digit >= (ONE_TENTH_REV - DIGIT_CHANGE_THRESHOLD))
				{
					y += (fractional_digit - (ONE_TENTH_REV - DIGIT_CHANGE_THRESHOLD)) * (3.0 / DIGIT_CHANGE_THRESHOLD);
				}
			}

			set_mono_font_position (x, y); print_mono_font_char ('9'); y -= 6.0;
			set_mono_font_position (x, y); print_mono_font_char ('0'); y -= 6.0;
			set_mono_font_position (x, y); print_mono_font_char ('1'); y -= 6.0;
			set_mono_font_position (x, y); print_mono_font_char ('2'); y -= 6.0;
			set_mono_font_position (x, y); print_mono_font_char ('3'); y -= 6.0;
			set_mono_font_position (x, y); print_mono_font_char ('4'); y -= 6.0;
			set_mono_font_position (x, y); print_mono_font_char ('5'); y -= 6.0;
			set_mono_font_position (x, y); print_mono_font_char ('6'); y -= 6.0;
			set_mono_font_position (x, y); print_mono_font_char ('7'); y -= 6.0;
			set_mono_font_position (x, y); print_mono_font_char ('8'); y -= 6.0;
			set_mono_font_position (x, y); print_mono_font_char ('9'); y -= 6.0;
			set_mono_font_position (x, y); print_mono_font_char ('0');

			#undef ONE_REV
			#undef ONE_TENTH_REV
			#undef ONE_OVER_ONE_TENTH_REV
			#undef DIGIT_CHANGE_THRESHOLD

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal (instrument_error);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_havoc_fixed_cockpit_hsi_waypoint_identifier (cockpit_panels panel)
{
	entity
		*wp;

	wp = get_local_entity_current_waypoint (get_gunship_entity ());

	if (wp)
	{
		switch (panel)
		{
			////////////////////////////////////////
			case COCKPIT_PANEL_DOWN20_AHEAD:
			////////////////////////////////////////
			{
				set_mono_font_type (MONO_FONT_TYPE_3X6);

				set_viewport (fx_640_480 + 238.0, fy_640_480 + 384.0, fx_640_480 + 240.999, fy_640_480 + 388.999);

				set_mono_font_colour (white_digit_colour);

				set_mono_font_position (fx_640_480 + 238.0, fy_640_480 + 384.0);

				if (!havoc_damage.navigation_computer)
				{
					print_mono_font_char (get_local_entity_char_value (wp, CHAR_TYPE_TAG));
				}
				else
				{
					print_mono_font_char ('A');
				}

				break;
			}
			////////////////////////////////////////
			default:
			////////////////////////////////////////
			{
				debug_fatal (instrument_error);

				break;
			}
		}
	}
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
	// get inverse attitude (attiude * inverse attitude = identity) which aligns the ADI with the world axis
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
