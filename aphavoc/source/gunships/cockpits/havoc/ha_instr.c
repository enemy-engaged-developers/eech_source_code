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

static const char
	*instrument_error = "Cannot draw instrument on panel";

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Casm Gauges Arrows mod

enum TEXTURE_GAUGES
{
	TG_LLHS,
	TG_ULHS,
	TG_LRHS,
	TG_URHS,
	TG_CEN,
	TG_LAST
};

static texture_index_numbers
	textures[TG_LAST][3] =
		{
			{ TEXTURE_INDEX_DAY_INSTR_LLHS, TEXTURE_INDEX_NGT_INSTR_LLHS, TEXTURE_INDEX_TWI_INSTR_LLHS },
			{ TEXTURE_INDEX_DAY_INSTR_ULHS, TEXTURE_INDEX_NGT_INSTR_ULHS, TEXTURE_INDEX_TWI_INSTR_ULHS },
			{ TEXTURE_INDEX_DAY_INSTR_LRHS, TEXTURE_INDEX_NGT_INSTR_LRHS, TEXTURE_INDEX_TWI_INSTR_LRHS },
			{ TEXTURE_INDEX_DAY_INSTR_URHS, TEXTURE_INDEX_NGT_INSTR_URHS, TEXTURE_INDEX_TWI_INSTR_URHS },
			{ TEXTURE_INDEX_DAY_INSTR_CEN,  TEXTURE_INDEX_NGT_INSTR_CEN,  TEXTURE_INDEX_TWI_INSTR_CEN  }
		};

static screen
	*old_texture_screen[TG_LAST][3],
	*texture_screen[TG_LAST][3];

static float
	texture_width[TG_LAST][3],
	texture_height[TG_LAST][3];

//VJ 051209 added check aphavoc installed else there are no sprites
#define draw_sprite(scale_x, scale_y, flag, t_x, t_y, t_dx, t_dy, s_x, s_y, s_dx, s_dy, mask) \
	if (flag && get_global_apache_havoc_installed()) \
		blit_rgb_alpha_masked_sprite_zero_mask_value_scaled (sprite_data, mask_data, t_x * scale_x, t_y * scale_y, t_dx * scale_x, t_dy * scale_y, s_x, s_y, s_dx, s_dy, mask);

// Casm end

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
	set_rgb_colour (white_needle_colour_level1,  255, 255, 255, 0);
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

// Casm 10SEP05 begin Havoc Instruments

void initialise_havoc_instruments (void)
{
	enum TEXTURE_GAUGES
		tg;
	int
		texture;

	for (tg = 0; tg < TG_LAST; tg++)
	{
		for (texture = 0; texture < 3; texture++)
		{
			old_texture_screen[tg][texture] = create_screen_for_system_texture (textures[tg][texture]);
			texture_width[tg][texture] = get_screen_width (old_texture_screen[tg][texture]);
			texture_height[tg][texture] = get_screen_height (old_texture_screen[tg][texture]);

			texture_screen[tg][texture] = create_system_texture_screen (texture_width[tg][texture], texture_height[tg][texture], textures[tg][texture], TEXTURE_TYPE_NOALPHA_NOPALETTE);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_havoc_instruments (void)
{
	enum TEXTURE_GAUGES
		tg;
	int
		texture;

	for (tg = 0; tg < TG_LAST; tg++)
	{
		for (texture = 0; texture < 3; texture++)
		{
			set_system_texture_screen (old_texture_screen[tg][texture], textures[tg][texture]);
			destroy_screen (texture_screen[tg][texture]);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_havoc_virtual_cockpit_instruments_on_texture (void)
{
	int
		texture;
	enum TEXTURE_GAUGES
		tg;
	float
		width,
		height,
		value,
		hour_hand_value,
		minute_hand_value,
		second_hand_value,
		centre_x,
		centre_y,
		dot_x,
		dot_y;
	graphics_file_specifiers
		base_cockpit_graphics_file;
	unsigned char
		*sprite_data,
		*mask_data;
	extern havoc_lamp_flags
		havoc_lamps;


	set_havoc_instrument_colours ();

	switch (get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE))
	{
		case DAY_SEGMENT_TYPE_DAWN:
		{
			texture = 2;
			base_cockpit_graphics_file = GRAPHICS_COCKPITS_HAVOC_LEVEL2_BASE;
			break;
		}
		case DAY_SEGMENT_TYPE_DAY:
		{
			texture = 0;
			base_cockpit_graphics_file = GRAPHICS_COCKPITS_HAVOC_LEVEL1_BASE;
			break;
		}
		case DAY_SEGMENT_TYPE_DUSK:
		{
			texture = 2;
			base_cockpit_graphics_file = GRAPHICS_COCKPITS_HAVOC_LEVEL2_BASE;
			break;
		}
		case DAY_SEGMENT_TYPE_NIGHT:
		{
			texture = 1;
			base_cockpit_graphics_file = GRAPHICS_COCKPITS_HAVOC_LEVEL3_BASE;
			break;
		}
	}

	#if DEMO_VERSION

	texture = 0;
	base_cockpit_graphics_file = GRAPHICS_COCKPITS_HAVOC_LEVEL1_BASE;

	#endif

	/* Copy original panels */
	for (tg = 0; tg < TG_LAST; tg++)
	{
		register int
			width = texture_width[tg][texture],
			height = texture_height[tg][texture];
		blit_screens (old_texture_screen[tg][texture], texture_screen[tg][texture], 0, 0, width - 1, height - 1, 0, 0, width - 1, height - 1);
	}

	/* Find sprites */

	sprite_data = get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_SPRITES);

	mask_data = get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_SPRITES_MASK);

	/* Draw indicators */

	/* Lower Left Panel */
	width = texture_width[TG_LLHS][texture];
	height = texture_height[TG_LLHS][texture];

	if (lock_screen (texture_screen[TG_LLHS][texture]))
	{
		set_active_screen (texture_screen[TG_LLHS][texture]);

		/* Vertical speed indicator */
		value = metres_per_minute (current_flight_dynamics->world_velocity_y.value);
		value = bound (value, -300.0, 300.0);
		value *= rad (180.0) / 300.0;
	    centre_x = 251 * width / 512;
    	centre_y = 315 * height / 512;
		dot_x = centre_x - cos (value) * 40 * width / 512;
		dot_y = centre_y - sin (value) * 50 * height / 512;
		draw_arrow (centre_x, centre_y, dot_x, dot_y, width / 128, height / 128, white_needle_colour);

		/* Barometric altimeter long arrow */
		value = fmod (current_flight_dynamics->barometric_altitude.value, 1000.0);
		value *= rad (360.0) / 1000.0;
	    centre_x = 126 * width / 512;
    	centre_y = 318 * height / 512;
		dot_x = centre_x + sin (value) * 40 * width / 512;
		dot_y = centre_y - cos (value) * 50 * height / 512;
		draw_arrow (centre_x, centre_y, dot_x, dot_y, width / 128, height / 128, white_needle_colour);

		/* Barometric altimeter short arrow */
		value = fmod (current_flight_dynamics->barometric_altitude.value, 10000.0);
		value *= rad (360.0) / 10000.0;
	    centre_x = 126 * width / 512;
    	centre_y = 318 * height / 512;
		dot_x = centre_x + sin (value) * 20 * width / 512;
		dot_y = centre_y - cos (value) * 25 * height / 512;
		draw_arrow (centre_x, centre_y, dot_x, dot_y, width / 128, height / 128, white_needle_colour);

		/* Airspeed */
		value = kilometres_per_hour (current_flight_dynamics->indicated_airspeed.value);
		value = bound (value, -50.0, 450.0);
		value *= rad (180.0) / 400.0;
	    centre_x = 282 * width / 512;
    	centre_y = 146 * height / 512;
		dot_x = centre_x - cos (value) * 40 * width / 512;
		dot_y = centre_y - sin (value) * 50 * height / 512;
		draw_arrow (centre_x, centre_y, dot_x, dot_y, width / 128, height / 128, white_needle_colour);

		/* Slip */
		value = kilometres_per_hour (current_flight_dynamics->indicated_slip.value);
		value = bound (value, -100.0, 100.0);
		value *= rad (45.0) / 100.0;
	    centre_x = 282 * width / 512;
    	centre_y = 146 * height / 512;
		dot_x = centre_x + sin (value) * 20 * width / 512;
		dot_y = centre_y + cos (value) * 25 * height / 512;
		draw_arrow (centre_x, centre_y, dot_x, dot_y, width / 128, height / 128, white_needle_colour);

		/* RPM */
		value = current_flight_dynamics->main_rotor_rpm.value;
		value = bound (value, 0.0, 100.0);
		value += 20.0;
		value *= rad (360.0) / 120.0;
	    centre_x = 157 * width / 512;
    	centre_y = 146 * height / 512;
		dot_x = centre_x + sin (value) * 40 * width / 512;
		dot_y = centre_y - cos (value) * 50 * height / 512;
		draw_arrow (centre_x, centre_y, dot_x, dot_y, width / 128, height / 128, white_needle_colour);

		/* Draw chaff & flare lamps */
		draw_sprite(width / 512, height / 512, havoc_lamps.weapons_management_chaff_green, 172, 26, 40, 22, 481,  79,  22,  11,  51);
		draw_sprite(width / 512, height / 512, havoc_lamps.weapons_management_flare_green, 218, 26, 40, 22, 503,  79,  22,  11,  48);
		draw_sprite(width / 512, height / 512, havoc_lamps.weapons_management_chaff_red, 172, 26, 40, 22, 436,  54,  22,  11,  51);
		draw_sprite(width / 512, height / 512, havoc_lamps.weapons_management_flare_red, 218, 26, 40, 22, 458,  54,  22,  11,  48);

		unlock_screen (texture_screen[TG_LLHS][texture]);
	}

	/* Upper Left Panel */
	width = texture_width[TG_ULHS][texture];
	height = texture_height[TG_ULHS][texture];

	if (lock_screen (texture_screen[TG_ULHS][texture]))
	{
		set_active_screen (texture_screen[TG_ULHS][texture]);

		/* G meter */
		value = current_flight_dynamics->g_force.value;
		value = bound (value, -2.0, 4.0);
		value *= rad (360.0) / 7.0;
	    centre_x = 209 * width / 512;
    	centre_y = 194 * height / 512;
		dot_x = centre_x + sin (value) * 35 * width / 512;
		dot_y = centre_y - cos (value) * 35 * height / 512;
		draw_arrow (centre_x, centre_y, dot_x, dot_y, width / 128, height / 128, white_needle_colour);

		/* Radar altimeter */
		value = current_flight_dynamics->radar_altitude.value;
		value = bound (value, 0.0, 300.0);
		if (value < 100.0)
			value *= rad (360.0) / 160.0;
		else
			value = value * rad (180.0) / 400.0 + rad (180.0);
	    centre_x = 182 * width / 512;
    	centre_y = 366 * height / 512;
		dot_x = centre_x + sin (value) * 50 * width / 512;
		dot_y = centre_y - cos (value) * 50 * height / 512;
		draw_arrow (centre_x, centre_y, dot_x, dot_y, width / 128, height / 128, white_needle_colour);

		/* Draw master caution lamp */
		draw_sprite(width / 512, height / 512, havoc_lamps.master_caution, 315, 51, 124, 76, 213, 150,  42,  29, 232);

		unlock_screen (texture_screen[TG_ULHS][texture]);
	}

	/* Lower Right Panel */
	width = texture_width[TG_LRHS][texture];
	height = texture_height[TG_LRHS][texture];

	if (lock_screen (texture_screen[TG_LRHS][texture]))
	{
		set_active_screen (texture_screen[TG_LRHS][texture]);

		/* Left engine torque */
		value = current_flight_dynamics->left_engine_torque.value;
		value = bound (value, 0.0, 110.0);
		value *= 170.0 / 100.0;
	    centre_x = 22 * width / 512;
    	centre_y = 466 * height / 512;
	    dot_x = centre_x;
    	dot_y = centre_y - value * height / 512;
		draw_arrow (centre_x, centre_y, dot_x, dot_y, width / 128, height / 128, yellow_needle_colour);

		/* Right engine torque */
		value = current_flight_dynamics->right_engine_torque.value;
		value = bound (value, 0.0, 110.0);
		value *= 170.0 / 100.0;
	    centre_x = 66 * width / 512;
    	centre_y = 466 * height / 512;
	    dot_x = centre_x;
    	dot_y = centre_y - value * height / 512;
		draw_arrow (centre_x, centre_y, dot_x, dot_y, width / 128, height / 128, yellow_needle_colour);

		/* Left engine temperature */
		/* Right engine temperature */

		/* Draw status lamps */
		draw_sprite (width / 512, height / 512, havoc_lamps.status_1 , 167,  48, 58, 26, 332,   2,  22,  11, 120);
		draw_sprite (width / 512, height / 512, havoc_lamps.status_2 , 227,  48, 58, 26, 354,   2,  22,  11, 117);
		draw_sprite (width / 512, height / 512, havoc_lamps.status_3 , 288,  48, 58, 26, 376,   2,  22,  11, 115);
		draw_sprite (width / 512, height / 512, havoc_lamps.status_4 , 167,  76, 58, 26, 332,  13,  22,  11, 112);
		draw_sprite (width / 512, height / 512, havoc_lamps.status_5 , 227,  76, 58, 26, 354,  13,  22,  11, 110);
		draw_sprite (width / 512, height / 512, havoc_lamps.status_6 , 288,  76, 58, 26, 376,  13,  22,  11, 107);
		draw_sprite (width / 512, height / 512, havoc_lamps.status_7 , 167, 104, 58, 26, 332,  24,  22,  11, 105);
		draw_sprite (width / 512, height / 512, havoc_lamps.status_8 , 227, 104, 58, 26, 354,  24,  22,  11, 102);
		draw_sprite (width / 512, height / 512, havoc_lamps.status_9 , 288, 104, 58, 26, 376,  24,  22,  11,  99);
		draw_sprite (width / 512, height / 512, havoc_lamps.status_10, 167, 133, 58, 26, 332,  35,  22,  11,  97);
		draw_sprite (width / 512, height / 512, havoc_lamps.status_11, 227, 133, 58, 26, 354,  35,  22,  11,  94);
		draw_sprite (width / 512, height / 512, havoc_lamps.status_12, 288, 133, 58, 26, 376,  35,  22,  11,  92);
		draw_sprite (width / 512, height / 512, havoc_lamps.status_13, 167, 161, 58, 26, 332,  46,  22,  11,  89);
		draw_sprite (width / 512, height / 512, havoc_lamps.status_14, 227, 161, 58, 26, 354,  46,  22,  11,  87);
		draw_sprite (width / 512, height / 512, havoc_lamps.status_15, 288, 161, 58, 26, 376,  46,  22,  11,  84);
		draw_sprite (width / 512, height / 512, havoc_lamps.status_16, 167, 189, 58, 26, 332,  57,  22,  11,  82);
		draw_sprite (width / 512, height / 512, havoc_lamps.status_17, 227, 189, 58, 26, 354,  57,  22,  11,  79);
		draw_sprite (width / 512, height / 512, havoc_lamps.status_18, 288, 189, 58, 26, 376,  57,  22,  11,  76);

		/* Draw radio lamp */
		draw_sprite(width / 512, height / 512, havoc_lamps.radio, 374, 271, 86, 44, 401,  50,  29,  17,  74);

		/* Draw oil & temperature lamps */
		draw_sprite(width / 512, height / 512, havoc_lamps.lh_engine_oil_pressure_normal, 274, 392, 8, 30, 580,  55,   3,  13,  46);
		draw_sprite(width / 512, height / 512, havoc_lamps.rh_engine_oil_pressure_normal, 306, 392, 8, 30, 591,  55,   4,  13,  43);
		draw_sprite(width / 512, height / 512, havoc_lamps.lh_engine_oil_pressure_low, 274, 412, 8, 10, 579,  90,   4,   5,  46);
		draw_sprite(width / 512, height / 512, havoc_lamps.rh_engine_oil_pressure_low, 306, 412, 8, 10, 591,  90,   4,   5,  43);
		draw_sprite(width / 512, height / 512, havoc_lamps.lh_engine_oil_temperature_normal, 274, 292, 8, 34, 579,  72,   5,  15,  46);
		draw_sprite(width / 512, height / 512, havoc_lamps.rh_engine_oil_temperature_normal, 306, 292, 8, 34, 591,  72,   5,  15,  43);
		draw_sprite(width / 512, height / 512, havoc_lamps.lh_engine_oil_temperature_high, 274, 268, 8, 58, 576,  99,   4,  25,  46);
		draw_sprite(width / 512, height / 512, havoc_lamps.rh_engine_oil_temperature_high, 306, 268, 8, 58, 588,  99,   4,  25,  43);

		unlock_screen (texture_screen[TG_LRHS][texture]);
	}

	/* Upper Right Panel */
	width = texture_width[TG_URHS][texture];
	height = texture_height[TG_URHS][texture];

	if (lock_screen (texture_screen[TG_URHS][texture]))
	{
		set_active_screen (texture_screen[TG_URHS][texture]);

		/* Draw warning lamps */
		draw_sprite (width / 512, height / 512, havoc_lamps.warning_1, 118,  40, 68, 34, 539,   2,  22,  12,  71);
		draw_sprite (width / 512, height / 512, havoc_lamps.warning_2, 193,  40, 68, 34, 561,   2,  23,  12,  69);
		draw_sprite (width / 512, height / 512, havoc_lamps.warning_3, 118,  78, 68, 34, 539,  14,  22,  11,  66);
		draw_sprite (width / 512, height / 512, havoc_lamps.warning_4, 193,  78, 68, 34, 561,  14,  23,  11,  64);
		draw_sprite (width / 512, height / 512, havoc_lamps.warning_5, 118, 116, 68, 34, 539,  25,  22,  11,  61);
		draw_sprite (width / 512, height / 512, havoc_lamps.warning_6, 193, 116, 68, 34, 561,  25,  23,  11,  59);
		draw_sprite (width / 512, height / 512, havoc_lamps.warning_7, 118, 154, 68, 34, 539,  36,  22,  12,  56);
		draw_sprite (width / 512, height / 512, havoc_lamps.warning_8, 193, 154, 68, 34, 561,  36,  23,  12,  54);

		/* Draw threat warning lamps */
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_radar_type_1, 120, 377, 18, 10, 274, 230,   8,   6, 229);
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_radar_type_2, 143, 377, 18, 10, 282, 230,   8,   6, 227);
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_radar_type_3, 170, 377, 18, 10, 290, 230,   8,   6, 224);
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_radar_type_4, 195, 377, 18, 10, 298, 230,   7,   6, 222);
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_radar_type_5, 219, 377, 18, 10, 305, 230,   8,   6, 219);
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_radar_type_6, 244, 377, 18, 10, 313, 230,   8,   6, 217);
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_close_range_1, 151, 322, 11, 12, 289, 221,   5,   3, 209);
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_close_range_2, 145, 309,  9, 13, 284, 217,   5,   5, 207);	// (19% alpha)
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_close_range_3, 144, 295,  6, 11, 281, 211,   4,   6, 204);	// (20% alpha)
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_close_range_4, 145, 279,  8, 15, 281, 205,   3,   6, 201);	// (21% alpha)
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_close_range_5, 149, 266, 10, 13, 282, 200,   3,   5, 199);	// (22% alpha)
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_close_range_6, 158, 257, 12,  8, 285, 195,   4,   5, 196);	// (23% alpha)
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_close_range_7, 167, 250, 14, 10, 289, 192,   6,   4, 194);	// (24% alpha)
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_close_range_8, 187, 249,  8,  6, 295, 192,   5,   2, 191);	// (25% alpha)
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_close_range_9, 200, 250, 12,  9, 300, 192,   6,   4, 189);	// (26% alpha)
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_close_range_10, 211, 256, 12, 12, 306, 195,   4,   5, 186);	// (27% alpha)
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_close_range_11, 221, 267, 11, 14, 310, 200,   3,   6, 184);	// (28% alpha)
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_close_range_12, 228, 281,  9, 17, 311, 206,   3,   5, 181);	// (29% alpha)
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_close_range_13, 230, 300, 10, 16, 309, 211,   5,   6, 178);	// (30% alpha)
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_close_range_14, 220, 316, 12, 13, 306, 217,   5,   4, 176);	// (31% alpha)
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_close_range_15, 206, 329, 14, 15, 300, 220,   6,   4, 173);	// (32% alpha)
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_bearing_lh_rear_close_range, 152, 345, 8, 6, 285, 222,   4,   4, 120);
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_bearing_rh_rear_close_range, 218, 345, 8, 6, 305, 222,   5,   4, 117);
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_bearing_lh_90_close_range, 132, 279, 8, 6, 278, 203,   4,   4, 171);
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_bearing_lh_67_close_range, 141, 261, 8, 6, 281, 196,   4,   4, 168);
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_bearing_lh_45_close_range, 154, 246, 8, 6, 285, 191,   4,   4, 166);
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_bearing_lh_22_close_range, 171, 237, 8, 6, 292, 188,   4,   4, 163);
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_bearing_rh_22_close_range, 200, 237, 8, 6, 299, 188,   4,   4, 161);
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_bearing_rh_45_close_range, 218, 246, 8, 6, 305, 191,   4,   4, 158);
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_bearing_rh_67_close_range, 232, 261, 8, 6, 310, 196,   4,   4, 156);
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_bearing_rh_90_close_range, 240, 279, 8, 6, 313, 203,   4,   4, 153);
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_bearing_lh_rear, 140, 351, 18, 20, 281, 224,   7,   6, 214);
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_bearing_rh_rear, 224, 351, 18, 20, 307, 224,   6,   6, 212);
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_bearing_lh_90, 108, 273, 18, 20, 272, 200,   6,   7, 150);
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_bearing_lh_67, 118, 249, 18, 20, 275, 192,   7,   7, 148);
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_bearing_lh_45, 137, 227, 18, 20, 281, 186,   7,   6, 145);
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_bearing_lh_22, 162, 218, 18, 20, 290, 183,   6,   6, 143);
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_bearing_rh_22, 200, 218, 18, 20, 299, 183,   6,   6, 140);
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_bearing_rh_45, 222, 227, 18, 20, 307, 186,   6,   6, 138);
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_bearing_rh_67, 242, 249, 18, 20, 313, 192,   7,   7, 135);
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_bearing_rh_90, 254, 273, 18, 20, 317, 201,   6,   6, 133);
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_missile_below, 177, 290, 26, 12, 292, 206,  11,   5, 130);
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_missile_above, 177, 274, 26, 12, 292, 202,  11,   4, 127);
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_missile_lh_lock, 161, 266, 24, 66, 286, 197,  11,  23, 125);
		draw_sprite (width / 512, height / 512, havoc_lamps.threat_warning_missile_rh_lock, 197, 266, 24, 66, 298, 197,  11,  23, 122);

		unlock_screen (texture_screen[TG_URHS][texture]);
	}

	/* Centre Panel */
	width = texture_width[TG_CEN][texture];
	height = texture_height[TG_CEN][texture];

	if (lock_screen (texture_screen[TG_CEN][texture]))
	{
		set_active_screen (texture_screen[TG_CEN][texture]);

		/* Clock */
		value = get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_TIME_OF_DAY);
		get_analogue_clock_values (value, &hour_hand_value, &minute_hand_value, &second_hand_value);
		/* Hour */
		value = hour_hand_value * rad (360.0) / 12.0;
	    centre_x = 77 * width / 512;
    	centre_y = 119 * height / 256;
		dot_x = centre_x + sin (value) * 20 * width / 512;
		dot_y = centre_y - cos (value) * 30 * height / 256;
		draw_arrow (centre_x, centre_y, dot_x, dot_y, width / 128, height / 64, white_needle_colour);
		/* Minute */
		value = minute_hand_value * rad (360.0) / 60.0;
	    centre_x = 77 * width / 512;
    	centre_y = 119 * height / 256;
		dot_x = centre_x + sin (value) * 40 * width / 512;
		dot_y = centre_y - cos (value) * 60 * height / 256;
		draw_arrow (centre_x, centre_y, dot_x, dot_y, width / 256, height / 128, white_needle_colour);
		/* Second */
		value = second_hand_value * rad (360.0) / 60.0;
	    centre_x = 77 * width / 512;
    	centre_y = 119 * height / 256;
		dot_x = centre_x + sin (value) * 40 * width / 512;
		dot_y = centre_y - cos (value) * 60 * height / 256;
		draw_arrow (centre_x, centre_y, dot_x, dot_y, width / 256, height / 128, red_needle_colour);

		/* Fuel */
		value = current_flight_dynamics->fuel_weight.value;
		value = bound (value, 0.0, 1600.0);
		value = (value - 750.0) * rad (360.0) / 2000.0;
	    centre_x = 432 * width / 512;
    	centre_y = 118 * height / 256;
		dot_x = centre_x + sin (value) * 40 * width / 512;
		dot_y = centre_y - cos (value) * 60 * height / 256;
		centre_x = centre_x + sin (value) * 10 * width / 512;
		centre_y = centre_y - cos (value) * 15 * height / 256;
		draw_arrow (centre_x, centre_y, dot_x, dot_y, width / 128, height / 64, yellow_needle_colour);

		unlock_screen (texture_screen[TG_CEN][texture]);
	}

	/* Restore */
	set_active_screen (video_screen);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Casm 10SEP05 end

