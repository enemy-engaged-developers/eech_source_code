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
	red_needle_colour,
	white_digit_colour;

static rgb_colour
	white_needle_colour_level1,
	red_needle_colour_level1,
	white_digit_colour_level1,
	white_needle_colour_level2,
	red_needle_colour_level2,
	white_digit_colour_level2,
	white_needle_colour_level3,
	red_needle_colour_level3,
	white_digit_colour_level3;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static char
	*instrument_error = "Cannot draw instrument on panel";

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ah_aspd.h"

#include "ah_balt.h"

#include "ah_clock.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_ah64a_instrument_colours (void)
{
	set_rgb_colour (white_needle_colour_level1, 200, 200, 200, 0);
	set_rgb_colour (red_needle_colour_level1,   188,  58,  26, 0);
	set_rgb_colour (white_digit_colour_level1,  200, 200, 200, 0);
	set_rgb_colour (white_needle_colour_level2, 192,   0,   0, 0);
	set_rgb_colour (red_needle_colour_level2,   192,   0,   0, 0);
	set_rgb_colour (white_digit_colour_level2,  192,   0,   0, 0);
	set_rgb_colour (white_needle_colour_level3, 192,   0,   0, 0);
	set_rgb_colour (red_needle_colour_level3,   192,   0,   0, 0);
	set_rgb_colour (white_digit_colour_level3,  192,   0,   0, 0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_ah64a_instrument_colours (void)
{
	switch (get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE))
	{
		case DAY_SEGMENT_TYPE_DAWN:
		{
			white_needle_colour	= white_needle_colour_level2;
			red_needle_colour		= red_needle_colour_level2;
			white_digit_colour	= white_digit_colour_level2;

			break;
		}
		case DAY_SEGMENT_TYPE_DAY:
		{
			white_needle_colour	= white_needle_colour_level1;
			red_needle_colour		= red_needle_colour_level1;
			white_digit_colour	= white_digit_colour_level1;

			break;
		}
		case DAY_SEGMENT_TYPE_DUSK:
		{
			white_needle_colour	= white_needle_colour_level2;
			red_needle_colour		= red_needle_colour_level2;
			white_digit_colour	= white_digit_colour_level2;

			break;
		}
		case DAY_SEGMENT_TYPE_NIGHT:
		{
			white_needle_colour	= white_needle_colour_level3;
			red_needle_colour		= red_needle_colour_level3;
			white_digit_colour	= white_digit_colour_level3;

			break;
		}
	}

	#if DEMO_VERSION

	white_needle_colour	= white_needle_colour_level1;
	red_needle_colour		= red_needle_colour_level1;
	white_digit_colour	= white_digit_colour_level1;

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

static float get_adi_slip_indicator_needle_value (void)
{
	float
		slip_needle_value;

	if (test_cockpit_instruments)
	{
		static float
			value = -40.0;

		value += 1.0;

		if (value > 40.0)
		{
			value = -40.0;
		}

		slip_needle_value = value;
	}
	else
	{
		slip_needle_value = knots (current_flight_dynamics->indicated_slip.value);
	}

	slip_needle_value = bound (slip_needle_value, -30.0, 30.0);

	return (slip_needle_value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float get_airspeed_indicator_needle_value (void)
{
	float
		airspeed_needle_value;

	if (test_cockpit_instruments)
	{
		static float
			value = -50.0;

		value += 2.0;

		if (value > 300.0)
		{
			value = -50.0;
		}

		airspeed_needle_value = value;
	}
	else
	{
		airspeed_needle_value = knots (current_flight_dynamics->indicated_airspeed.value);
	}

	airspeed_needle_value = bound (airspeed_needle_value, 0.0, 250.0);

	return (airspeed_needle_value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float get_barometric_altimeter_needle_value (void)
{
	float
		altimeter_needle_value;

	if (test_cockpit_instruments)
	{
		static float
			value = 0.0;

		value += 10.0;

		if (value > 1000.0)
		{
			value = 0.0;
		}

		altimeter_needle_value = value;
	}
	else
	{
		altimeter_needle_value = fmod (feet (current_flight_dynamics->barometric_altitude.value), 1000.0);
	}

	return (altimeter_needle_value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float get_barometric_altimeter_digital_value (void)
{
	float
		altimeter_digital_value;

	if (test_cockpit_instruments)
	{
		static float
			value = 0.0;

		value += 10.0;

		if (value > 100000.0)
		{
			value = 0.0;
		}

		altimeter_digital_value = value;
	}
	else
	{
		altimeter_digital_value = feet (current_flight_dynamics->barometric_altitude.value);
	}

	return (altimeter_digital_value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void get_clock_hand_values (float *hours, float *minutes, float *seconds)
{
	float
		time_of_day,
		hour_hand_value,
		minute_hand_value,
		second_hand_value;

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

	*hours = hour_hand_value;

	*minutes = minute_hand_value;

	*seconds = second_hand_value;
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

void draw_ah64a_fixed_cockpit_airspeed_indicator_needle (cockpit_panels panel)
{
	float
		airspeed_needle_value,
		x_centre,
		y_centre;

	scale_data
		*airspeed_needle_scale,
		*p;

	if (draw_virtual_cockpit_needles_on_fixed_cockpits)
	{
		return;
	}

	airspeed_needle_value = get_airspeed_indicator_needle_value ();

	switch (panel)
	{
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_AHEAD:
		////////////////////////////////////////
		{
			x_centre = 533.0;

			y_centre = 440.0;

			airspeed_needle_scale = airspeed_indicator_needle_scale_down_20_ahead;

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_RIGHT30:
		////////////////////////////////////////
		{
			x_centre = 281.0;

			y_centre = 411.0;

			airspeed_needle_scale = airspeed_indicator_needle_scale_down_20_right_30;

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_RIGHT60:
		////////////////////////////////////////
		{
			x_centre = 12.0;

			y_centre = 471.0;

			airspeed_needle_scale = airspeed_indicator_needle_scale_down_20_right_60;

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

	p = find_scale_value (airspeed_needle_scale, airspeed_needle_value);

	draw_line (fx_640_480 + x_centre, fy_640_480 + y_centre, fx_640_480 + p->x, fy_640_480 + p->y, white_needle_colour);

	if (test_cockpit_instruments && DEBUG_MODULE)
	{
		test_scale (airspeed_needle_scale, 0.0, 250.0, 50.0);

		set_pixel (ix_640_480 + x_centre, iy_640_480 + y_centre, sys_col_red);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_ah64a_fixed_cockpit_barometric_altimeter_needle (cockpit_panels panel)
{
	float
		altimeter_needle_value,
		x_centre,
		y_centre;

	scale_data
		*altimeter_needle_scale,
		*p;

	if (draw_virtual_cockpit_needles_on_fixed_cockpits)
	{
		return;
	}

	altimeter_needle_value = get_barometric_altimeter_needle_value ();

	switch (panel)
	{
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_AHEAD:
		////////////////////////////////////////
		{
			x_centre = 599.0;

			y_centre = 440.0;

			altimeter_needle_scale = barometric_altimeter_needle_scale_down_20_ahead;

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_RIGHT30:
		////////////////////////////////////////
		{
			x_centre = 333.0;

			y_centre = 393.0;

			altimeter_needle_scale = barometric_altimeter_needle_scale_down_20_right_30;

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_RIGHT60:
		////////////////////////////////////////
		{
			x_centre = 73.0;

			y_centre = 430.0;

			altimeter_needle_scale = barometric_altimeter_needle_scale_down_20_right_60;

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

	p = find_scale_value (altimeter_needle_scale, altimeter_needle_value);

	draw_line (fx_640_480 + x_centre, fy_640_480 + y_centre, fx_640_480 + p->x, fy_640_480 + p->y, white_needle_colour);

	if (test_cockpit_instruments && DEBUG_MODULE)
	{
		test_scale (altimeter_needle_scale, 0.0, 900.0, 100.0);

		set_pixel (ix_640_480 + x_centre, iy_640_480 + y_centre, sys_col_red);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_ah64a_fixed_cockpit_barometric_altimeter_digits (cockpit_panels panel)
{
	float
		altimeter_digital_value,
		x,
		y,
		whole_digit,
		fractional_digit;

	altimeter_digital_value = get_barometric_altimeter_digital_value ();

	switch (panel)
	{
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_AHEAD:
		////////////////////////////////////////
		{
			set_mono_font_type (MONO_FONT_TYPE_3X6);

			set_mono_font_colour (white_digit_colour);

			set_viewport (fx_640_480 + 579.0, fy_640_480 + 438.0, fx_640_480 + 587.999, fy_640_480 + 442.999);

			////////////////////////////////////////
			//
			// 1,000's digit
			//
			////////////////////////////////////////

			#define ONE_REV		  				(10000.0)
			#define ONE_TENTH_REV				((ONE_REV) / 10.0)
			#define ONE_OVER_ONE_TENTH_REV	(1.0 / (ONE_TENTH_REV))
			#define DIGIT_CHANGE_THRESHOLD	(20.0)

			x = fx_640_480 + 583.0;
			y = fy_640_480 + 438.0 + 6.0;

			whole_digit = fmod (altimeter_digital_value, ONE_REV);

			fractional_digit = fmod (altimeter_digital_value, ONE_TENTH_REV);

			y += (float) ((int) (whole_digit * ONE_OVER_ONE_TENTH_REV)) * 6.0;

			//
			// rotate digits near change-over point (except at bottom zero)
			//

			if (altimeter_digital_value >= DIGIT_CHANGE_THRESHOLD)
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
			// 10,000's digit
			//
			////////////////////////////////////////

			#define ONE_REV		  				(100000.0)
			#define ONE_TENTH_REV				((ONE_REV) / 10.0)
			#define ONE_OVER_ONE_TENTH_REV	(1.0 / (ONE_TENTH_REV))
			#define DIGIT_CHANGE_THRESHOLD	(20.0)

			x = fx_640_480 + 579.0;
			y = fy_640_480 + 438.0 + 6.0;

			whole_digit = fmod (altimeter_digital_value, ONE_REV);

			fractional_digit = fmod (altimeter_digital_value, ONE_TENTH_REV);

			y += (float) ((int) (whole_digit * ONE_OVER_ONE_TENTH_REV)) * 6.0;

			//
			// rotate digits near change-over point (except at bottom zero)
			//

			if (altimeter_digital_value >= DIGIT_CHANGE_THRESHOLD)
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

void draw_ah64a_fixed_cockpit_clock_hands (cockpit_panels panel)
{
	float
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

	if (draw_virtual_cockpit_needles_on_fixed_cockpits)
	{
		return;
	}

	get_clock_hand_values (&hour_hand_value, &minute_hand_value, &second_hand_value);

	switch (panel)
	{
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_AHEAD:
		////////////////////////////////////////
		{
			x_centre = 45.0;

			y_centre = 388.0;

			hour_hand_scale = clock_small_hand_scale_down_20_ahead;

			minute_hand_scale = clock_large_hand_scale_down_20_ahead;

			second_hand_scale = clock_large_hand_scale_down_20_ahead;

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_LEFT30:
		////////////////////////////////////////
		{
			x_centre = 317.0;

			y_centre = 349.0;

			hour_hand_scale = clock_small_hand_scale_down_20_left_30;

			minute_hand_scale = clock_large_hand_scale_down_20_left_30;

			second_hand_scale = clock_large_hand_scale_down_20_left_30;

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_LEFT60:
		////////////////////////////////////////
		{
			x_centre = 589.0;

			y_centre = 386.0;

			hour_hand_scale = clock_small_hand_scale_down_20_left_60;

			minute_hand_scale = clock_large_hand_scale_down_20_left_60;

			second_hand_scale = clock_large_hand_scale_down_20_left_60;

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
//
// VIRTUAL COCKPIT
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_ah64a_virtual_cockpit_adi_angles (matrix3x3 attitude, float *heading, float *pitch, float *roll)
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

float get_ah64a_virtual_cockpit_adi_slip_indicator_needle_value (void)
{
	float
		slip_needle_value;

	slip_needle_value = get_adi_slip_indicator_needle_value ();

	slip_needle_value *= rad (30.0) / 30.0;

	return (slip_needle_value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_ah64a_virtual_cockpit_airspeed_indicator_needle_value (void)
{
	float
		airspeed_needle_value,
		fraction,
		roll;

	airspeed_needle_value = get_airspeed_indicator_needle_value ();

	//
	// non-linear scale
	//

	if (airspeed_needle_value <= 50.0)
	{
		fraction = airspeed_needle_value * (1.0 / 50.0);

		roll = fraction * rad (60.0);
	}
	else if (airspeed_needle_value <= 100.0)
	{
		fraction = (airspeed_needle_value - 50.0) * (1.0 / 50.0);

		roll = (fraction * (rad (150.0) - rad (60.0))) + rad (60.0);
	}
	else if (airspeed_needle_value <= 150.0)
	{
		fraction = (airspeed_needle_value - 100.0) * (1.0 / 50.0);

		roll = (fraction * (rad (210.0) - rad (150.0))) + rad (150.0);
	}
	else if (airspeed_needle_value <= 200.0)
	{
		fraction = (airspeed_needle_value - 150.0) * (1.0 / 50.0);

		roll = (fraction * (rad (270.0) - rad (210.0))) + rad (210.0);
	}
	else
	{
		fraction = (airspeed_needle_value - 200.0) * (1.0 / 50.0);

		roll = (fraction * (rad (330.0) - rad (270.0))) + rad (270.0);
	}

	return (-roll);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_ah64a_virtual_cockpit_barometric_altimeter_needle_value (void)
{
	float
		altimeter_needle_value;

	altimeter_needle_value = get_barometric_altimeter_needle_value ();

	altimeter_needle_value *= -PI2 / 1000.0;

	return (altimeter_needle_value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_ah64a_virtual_cockpit_clock_hand_values (float *hours, float *minutes, float *seconds)
{
	float
		hour_hand_value,
		minute_hand_value,
		second_hand_value;

	get_clock_hand_values (&hour_hand_value, &minute_hand_value, &second_hand_value);

	hour_hand_value *= -PI2 / 12.0;

	minute_hand_value *= -PI2 / 60.0;

	second_hand_value *= -PI2 / 60.0;

	*hours = hour_hand_value;

	*minutes = minute_hand_value;

	*seconds = second_hand_value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
