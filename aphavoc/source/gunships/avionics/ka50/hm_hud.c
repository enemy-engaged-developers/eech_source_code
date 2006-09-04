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

static void initialise_hms_gun_pipper (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//
// main 2D environment
//
////////////////////////////////////////

#define HUD_WINDOW_X_MIN  				(-1.0)
#define HUD_WINDOW_Y_MIN				(-1.0)
#define HUD_WINDOW_X_MAX  				(0.999)
#define HUD_WINDOW_Y_MAX 				(0.999)

#define HUD_VIEWPORT_LARGE_SIZE		(256)
#define HUD_VIEWPORT_SMALL_SIZE		(128)

#define HUD_VIEWPORT_TEXTURE_X_ORG	(HUD_VIEWPORT_SMALL_SIZE / 2)
#define HUD_VIEWPORT_TEXTURE_Y_ORG	(HUD_VIEWPORT_SMALL_SIZE / 2)

static env_2d
	*hud_env;

static float
	hud_viewport_size,
	hud_viewport_x_org,
	hud_viewport_y_org,
	hud_viewport_x_min,
	hud_viewport_y_min,
	hud_viewport_x_max,
	hud_viewport_y_max;

static int
	draw_large_hud;

static float
	hud_screen_x_min,
	hud_screen_y_min,
	hud_screen_x_max,
	hud_screen_y_max,
	hud_screen_x_scale,
	hud_screen_y_scale;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define LARGE_HUD_TEXTURE_INDEX (TEXTURE_INDEX_AVCKPT_DISPLAY_LHS_MFD)
#define LARGE_HMS_TEXTURE_INDEX (TEXTURE_INDEX_AVCKPT_DISPLAY_RHS_MFD)

static screen
	*hud_texture_screen,
	*large_hud_texture_screen,
	*large_hms_texture_screen;

static rgb_colour
	clear_hud_colour;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//
// heading scale
//
////////////////////////////////////////

static char large_hud_heading_scale_datum[] =
{
	5,
	6,
	-2,
	0,
	0,0,1,0,0,
	0,0,1,0,0,
	0,1,1,1,0,
	0,1,1,1,0,
	1,1,1,1,1,
	1,1,1,1,1,
};

static char small_hud_heading_scale_datum[] =
{
	5,
	3,
	-2,
	0,
	0,0,1,0,0,
	0,1,1,1,0,
	1,1,1,1,1,
};

static char large_hud_bob_up_command_heading_carat[] =
{
	5,
	11,
	-2,
	0,
	0,0,1,0,0,
	0,0,1,0,0,
	0,1,1,1,0,
	0,1,1,1,0,
	1,1,1,1,1,
	1,1,1,1,1,
	0,0,1,0,0,
	0,0,1,0,0,
	0,0,1,0,0,
	0,0,1,0,0,
	0,0,1,0,0,
};

static char small_hud_bob_up_command_heading_carat[] =
{
	5,
	5,
	-2,
	0,
	0,0,1,0,0,
	0,1,1,1,0,
	1,1,1,1,1,
	0,0,1,0,0,
	0,0,1,0,0,
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//
// bank scale
//
////////////////////////////////////////

#define BANK_SCALE_TICK_START	(0.4)
#define BANK_SCALE_MAJOR_TICK	(BANK_SCALE_TICK_START + 0.150)
#define BANK_SCALE_MINOR_TICK	(BANK_SCALE_TICK_START + 0.075)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//
// rate of climb scale
//
////////////////////////////////////////

static char large_hud_rate_of_climb_scale_pointer[] =
{
	15,
	9,
	0,
	-4,
	0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
	0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,
	0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,
	0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,
	0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,
	0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
};

static char small_hud_rate_of_climb_scale_pointer[] =
{
	8,
	5,
	0,
	-2,
	0,0,1,0,0,0,0,0,
	0,1,0,1,1,1,1,1,
	1,0,0,0,0,0,0,1,
	0,1,0,1,1,1,1,1,
	0,0,1,0,0,0,0,0,
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void clip_2d_point_to_hud_extent (float *x, float *y)
{
	ASSERT (x);

	ASSERT (y);

	//
	// clipping assumes that the HUD origin is at (0.0, 0.0)
	//

	if (*x > HUD_WINDOW_X_MAX)
	{
		*y = (*y * HUD_WINDOW_X_MAX) / *x;

		*x = HUD_WINDOW_X_MAX;
	}
	else if (*x < HUD_WINDOW_X_MIN)
	{
		*y = (*y * HUD_WINDOW_X_MIN) / *x;

		*x = HUD_WINDOW_X_MIN;
	}

	if (*y > HUD_WINDOW_Y_MAX)
	{
		*x = (*x * HUD_WINDOW_Y_MAX) / *y;

		*y = HUD_WINDOW_Y_MAX;
	}
	else if (*y < HUD_WINDOW_Y_MIN)
	{
		*x = (*x * HUD_WINDOW_Y_MIN) / *y;

		*y = HUD_WINDOW_Y_MIN;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void transform_hud_screen_co_ords_to_hud_texture_co_ords (float *i, float *j)
{
	ASSERT (i);
	ASSERT (j);

	*i -= hud_screen_x_min;
	*j -= hud_screen_y_min;

	*i *= hud_screen_x_scale;
	*j *= hud_screen_y_scale;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_layout_grid (void)
{
	float
		x,
		y;

	if (display_hud_layout_grid)
	{
		for (x = HUD_WINDOW_X_MIN; x <= HUD_WINDOW_X_MAX; x += 0.1)
		{
			draw_2d_line (x, HUD_WINDOW_Y_MIN, x, HUD_WINDOW_Y_MAX, sys_col_red);
		}

		for (y = HUD_WINDOW_Y_MIN; y <= HUD_WINDOW_Y_MAX; y += 0.1)
		{
			draw_2d_line (HUD_WINDOW_X_MIN, y, HUD_WINDOW_X_MAX, y, sys_col_red);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_hud_centre_datum (void)
{
	draw_2d_line (-0.10, +0.00, -0.05, +0.00, hud_colour);
	draw_2d_line (+0.10, +0.00, +0.05, +0.00, hud_colour);
	draw_2d_line (+0.00, -0.10, +0.00, -0.05, hud_colour);
	draw_2d_line (+0.00, +0.10, +0.00, +0.05, hud_colour);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_heading_scale (void)
{
	float
		hud_vp_x_min,
		hud_vp_x_max,
		heading,
		mod_heading_step_10,
		x,
		width,
		i,
		j;

	int
		loop,
		int_heading_step_10;

	char
		s[20];

	//
	// adjust 2D environment for heading scale clipping
	//

	set_2d_window (hud_env, HUD_WINDOW_X_MIN * 0.5, HUD_WINDOW_Y_MIN, HUD_WINDOW_X_MAX * 0.5, HUD_WINDOW_Y_MAX);

	hud_vp_x_min = hud_viewport_x_org - (hud_viewport_size * (0.5 * 0.5));

	hud_vp_x_max = hud_viewport_x_org + (hud_viewport_size * (0.5 * 0.5)) - 0.001;

	set_2d_viewport (hud_env, hud_vp_x_min, hud_viewport_y_min, hud_vp_x_max, hud_viewport_y_max);

	//
	// sort first major tick position (draw 2 major ticks either side of centre)
	//

	heading = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_HEADING);

	heading = deg (heading);

	mod_heading_step_10 = fmod (heading, 10.0);

	int_heading_step_10 = ((int) (heading * 0.1) * 10);

	int_heading_step_10 -= 20;

	if (int_heading_step_10 < 0)
	{
		int_heading_step_10 += 360;
	}

	x = - (20.0 + mod_heading_step_10) * 0.05;

	//
	// draw heading scale line
	//

	draw_2d_line (-0.5, 0.8, 0.5, 0.8, hud_colour);

	//
	// large and small HUD differences
	//

	get_2d_float_screen_coordinates (0.0, 0.8, &i, &j);

	if (draw_large_hud)
	{
		set_mono_font_type (MONO_FONT_TYPE_6X10);

		draw_mono_sprite (large_hud_heading_scale_datum, i, j + 1.0, hud_colour);
	}
	else
	{
		set_mono_font_type (MONO_FONT_TYPE_6X7);

		draw_mono_sprite (small_hud_heading_scale_datum, i, j + 1.0, hud_colour);
	}

	//
	// draw heading scale ticks and heading value
	//

	for (loop = 0; loop < 5; loop++)
	{
		//
		// major tick every 10 degrees
		//

		draw_2d_line (x, 0.8, x, 0.85, hud_colour);

		//
		// minor tick every 5 degrees
		//

		draw_2d_line (x + 0.25, 0.8, x + 0.25, 0.825, hud_colour);

		//
		// heading value ('0' displayed as '360')
		//

		if (int_heading_step_10 != 0)
		{
			sprintf (s, "%d", int_heading_step_10);
		}
		else
		{
			sprintf (s, "360");
		}

		set_2d_mono_font_position (x, 0.85);

		width = get_mono_font_string_width (s);

		if (draw_large_hud)
		{
			set_mono_font_rel_position ((-width * 0.5) + 1.0, -8.0);
		}
		else
		{
			set_mono_font_rel_position ((-width * 0.5) + 1.0, -6.0);
		}

		print_mono_font_string (s);

		//
		// next heading value
		//

		int_heading_step_10 += 10;

		if (int_heading_step_10 == 360)
		{
			int_heading_step_10 = 0;
		}

		x += 0.5;
	}

	//
	// draw bob-up command heading carat
	//

	{
		float
			command_heading;

		if (hud_bob_up_overlay)
		{
			heading = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_HEADING);

			command_heading = hud_bob_up_heading - heading;

			if (command_heading > rad (180.0))
			{
				command_heading -= rad (360.0);
			}
			else if (command_heading < rad (-180.0))
			{
				command_heading += rad (360.0);
			}

			command_heading = bound (command_heading, rad (-10.0), rad (10.0));

			if (draw_large_hud)
			{
				get_2d_float_screen_coordinates (command_heading * ((0.5 - 0.02) / rad (10.0)), 0.8, &i, &j);

				draw_mono_sprite (large_hud_bob_up_command_heading_carat, i, j + 1.0, hud_colour);
			}
			else
			{
				get_2d_float_screen_coordinates (command_heading * ((0.5 - 0.04) / rad (10.0)), 0.8, &i, &j);

				draw_mono_sprite (small_hud_bob_up_command_heading_carat, i, j + 1.0, hud_colour);
			}
		}
	}

	//
	// restore 2D environment
	//

	set_2d_window (hud_env, HUD_WINDOW_X_MIN, HUD_WINDOW_Y_MIN, HUD_WINDOW_X_MAX, HUD_WINDOW_Y_MAX);

	set_2d_viewport (hud_env, hud_viewport_x_min, hud_viewport_y_min, hud_viewport_x_max, hud_viewport_y_max);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_pitch_indicator (void)
{
	float
		pitch,
		y,
		width;

	char
		s[20];

	pitch = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_PITCH);

	y = pitch * (-0.7 / (PI / 2.0));

	draw_2d_line (-0.5, y, 0.7, y, hud_colour);

	sprintf (s, "%d", abs ((int) (deg (pitch))));

	if (draw_large_hud)
	{
		set_mono_font_type (MONO_FONT_TYPE_6X10);

		set_2d_mono_font_position (0.7, y);

		width = get_mono_font_string_width (s);

		set_mono_font_rel_position (-width + 1.0, -8.0);
	}
	else
	{
		set_mono_font_type (MONO_FONT_TYPE_6X7);

		set_2d_mono_font_position (0.7, y);

		width = get_mono_font_string_width (s);

		set_mono_font_rel_position (-width + 1.0, -6.0);
	}

	print_mono_font_string (s);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_bank_scale (void)
{
	draw_2d_line (-BANK_SCALE_TICK_START, 0.0, -BANK_SCALE_MAJOR_TICK, 0.0, hud_colour);
	draw_2d_line (+BANK_SCALE_TICK_START, 0.0, +BANK_SCALE_MAJOR_TICK, 0.0, hud_colour);

	set_2d_window_rotation (hud_env, rad (+5.0));
	draw_2d_line (-BANK_SCALE_TICK_START, 0.0, -BANK_SCALE_MINOR_TICK, 0.0, hud_colour);
	set_2d_window_rotation (hud_env, rad (-5.0));
	draw_2d_line (+BANK_SCALE_TICK_START, 0.0, +BANK_SCALE_MINOR_TICK, 0.0, hud_colour);

	set_2d_window_rotation (hud_env, rad (+10.0));
	draw_2d_line (-BANK_SCALE_TICK_START, 0.0, -BANK_SCALE_MINOR_TICK, 0.0, hud_colour);
	set_2d_window_rotation (hud_env, rad (-10.0));
	draw_2d_line (+BANK_SCALE_TICK_START, 0.0, +BANK_SCALE_MINOR_TICK, 0.0, hud_colour);

	set_2d_window_rotation (hud_env, rad (+15.0));
	draw_2d_line (-BANK_SCALE_TICK_START, 0.0, -BANK_SCALE_MAJOR_TICK, 0.0, hud_colour);
	set_2d_window_rotation (hud_env, rad (-15.0));
	draw_2d_line (+BANK_SCALE_TICK_START, 0.0, +BANK_SCALE_MAJOR_TICK, 0.0, hud_colour);

	set_2d_window_rotation (hud_env, rad (+30.0));
	draw_2d_line (-BANK_SCALE_TICK_START, 0.0, -BANK_SCALE_MAJOR_TICK, 0.0, hud_colour);
	set_2d_window_rotation (hud_env, rad (-30.0));
	draw_2d_line (+BANK_SCALE_TICK_START, 0.0, +BANK_SCALE_MAJOR_TICK, 0.0, hud_colour);

	set_2d_window_rotation (hud_env, rad (+60.0));
	draw_2d_line (-BANK_SCALE_TICK_START, 0.0, -BANK_SCALE_MAJOR_TICK, 0.0, hud_colour);
	set_2d_window_rotation (hud_env, rad (-60.0));
	draw_2d_line (+BANK_SCALE_TICK_START, 0.0, +BANK_SCALE_MAJOR_TICK, 0.0, hud_colour);

	set_2d_window_rotation (hud_env, 0.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_aircraft_datum (void)
{
	float
		roll;

	roll = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_ROLL);

	set_2d_window_rotation (hud_env, -roll);

	draw_2d_line (-0.35, +0.00, -0.15, +0.00, hud_colour);
	draw_2d_line (+0.35, +0.00, +0.15, +0.00, hud_colour);
	draw_2d_line (+0.00, +0.15, +0.00, +0.25, hud_colour);
	draw_2d_line (-0.20, +0.00, -0.20, -0.04, hud_colour);
	draw_2d_line (+0.20, +0.00, +0.20, -0.04, hud_colour);

	set_2d_window_rotation (hud_env, 0.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_true_airspeed (void)
{
	float
		true_airspeed,
		width;

	char
		s[20];

	true_airspeed = current_flight_dynamics->velocity_z.value;

	true_airspeed = kilometres_per_hour (true_airspeed);

	sprintf (s, "%d", (int) true_airspeed);

	if (draw_large_hud)
	{
		set_mono_font_type (MONO_FONT_TYPE_7X12);

		set_2d_mono_font_position (-0.55, 0.8);

		width = get_mono_font_string_width (s);

		set_mono_font_rel_position (-width + 1.0, -4.0);
	}
	else
	{
		set_mono_font_type (MONO_FONT_TYPE_6X10);

		set_2d_mono_font_position (-0.55, 0.8);

		width = get_mono_font_string_width (s);

		set_mono_font_rel_position (-width + 1.0, -3.0);
	}

	print_mono_font_string (s);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_altitude (void)
{
	char
		s[20];

	if (current_flight_dynamics->radar_altitude.value < 500.0)
	{
		sprintf (s, "R%d", (int) current_flight_dynamics->radar_altitude.value);
	}
	else
	{
		sprintf (s, "%d", (int) current_flight_dynamics->barometric_altitude.value);
	}

	if (draw_large_hud)
	{
		set_mono_font_type (MONO_FONT_TYPE_7X12);

		set_2d_mono_font_position (0.55, 0.8);

		set_mono_font_rel_position (0.0, -4.0);
	}
	else
	{
		set_mono_font_type (MONO_FONT_TYPE_6X10);

		set_2d_mono_font_position (0.55, 0.8);

		set_mono_font_rel_position (0.0, -3.0);
	}

	print_mono_font_string (s);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_rate_of_climb_scale (void)
{
	float
		y,
		i,
		j,
		width;

	//
	// draw scale
	//

	draw_2d_line (+0.800, +0.500, +0.800, -0.500, hud_colour);

	draw_2d_line (+0.800, +0.500, +0.850, +0.500, hud_colour);
	draw_2d_line (+0.800, +0.400, +0.825, +0.400, hud_colour);
	draw_2d_line (+0.800, +0.300, +0.825, +0.300, hud_colour);
	draw_2d_line (+0.800, +0.200, +0.825, +0.200, hud_colour);
	draw_2d_line (+0.800, +0.100, +0.825, +0.100, hud_colour);
	draw_2d_line (+0.800, +0.000, +0.850, +0.000, hud_colour);
	draw_2d_line (+0.800, -0.100, +0.825, -0.100, hud_colour);
	draw_2d_line (+0.800, -0.200, +0.825, -0.200, hud_colour);
	draw_2d_line (+0.800, -0.300, +0.825, -0.300, hud_colour);
	draw_2d_line (+0.800, -0.400, +0.825, -0.400, hud_colour);
	draw_2d_line (+0.800, -0.500, +0.850, -0.500, hud_colour);

	//
	// get indicator position (fsd +/- 10m/s)
	//

	y = current_flight_dynamics->world_velocity_y.value;

	y = bound (y, -10.0, 10.0);

	y *= 0.05;

	//
	// draw indicator and fsd values
	//

	draw_2d_line (0.8, y, 0.85, y, hud_colour);

	get_2d_float_screen_coordinates (0.85, y, &i, &j);

	if (draw_large_hud)
	{
		draw_mono_sprite (large_hud_rate_of_climb_scale_pointer, i + 1.0, j, hud_colour);

		set_mono_font_type (MONO_FONT_TYPE_6X10);

		set_2d_mono_font_position (1.0, 0.5);

		width = get_mono_font_string_width ("10");

		set_mono_font_rel_position (-width, -12.0);

		print_mono_font_string ("10");

		set_2d_mono_font_position (1.0, -0.5);

		width = get_mono_font_string_width ("-10");

		set_mono_font_rel_position (-width, 6.0);

		print_mono_font_string ("-10");
	}
	else
	{
		draw_mono_sprite (small_hud_rate_of_climb_scale_pointer, i + 1.0, j, hud_colour);

		set_mono_font_type (MONO_FONT_TYPE_6X7);

		set_2d_mono_font_position (1.0, 0.5);

		width = get_mono_font_string_width ("10");

		set_mono_font_rel_position (-width, -8.0);

		print_mono_font_string ("10");

		set_2d_mono_font_position (1.0, -0.5);

		width = get_mono_font_string_width ("-10");

		set_mono_font_rel_position (-width, 4.0);

		print_mono_font_string ("-10");
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_engine_torque (void)
{
	char
		s[20];

	int
		torque;

	float
		x_min,
		y_min,
		x_max,
		y_max,
		width;

	torque = (int) current_flight_dynamics->combined_engine_torque.value;

	sprintf (s, "%d%%", torque);

	if (draw_large_hud)
	{
		set_mono_font_type (MONO_FONT_TYPE_7X12);

		set_2d_mono_font_position (0.0, 0.7);

		width = get_mono_font_string_width (s);

		set_mono_font_rel_position ((-width * 0.5) + 1.0, 0.0);

		get_mono_font_position (&x_min, &y_min);

		print_mono_font_string (s);

		if (torque >= 98)
		{
			x_min -= 2.0;
			y_min -= 2.0;

			x_max = x_min + width + 3.0;
			y_max = y_min + 12.0;

			draw_line (x_min, y_min, x_max, y_min, hud_colour);
			draw_line (x_max, y_min, x_max, y_max, hud_colour);
			draw_line (x_max, y_max, x_min, y_max, hud_colour);
			draw_line (x_min, y_max, x_min, y_min, hud_colour);
		}
	}
	else
	{
		set_mono_font_type (MONO_FONT_TYPE_6X10);

		set_2d_mono_font_position (0.0, 0.7);

		width = get_mono_font_string_width (s);

		set_mono_font_rel_position ((-width * 0.5) + 1.0, 0.0);

		get_mono_font_position (&x_min, &y_min);

		print_mono_font_string (s);

		if (torque >= 98)
		{
			x_min -= 2.0;
			y_min -= 2.0;

			x_max = x_min + width + 3.0;
			y_max = y_min + 10.0;

			draw_line (x_min, y_min, x_max, y_min, hud_colour);
			draw_line (x_max, y_min, x_max, y_max, hud_colour);
			draw_line (x_max, y_max, x_min, y_max, hud_colour);
			draw_line (x_min, y_max, x_min, y_min, hud_colour);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_flight_path_marker_and_waypoint_information (int draw_on_virtual_cockpit_texture)
{
	char
		s[100],
		tag;

	int
		draw_flight_path_marker;

	float
		i,
		j,
		x,
		y,
		flat_range,
		width,
		dx,
		dz,
		bearing,
		heading,
		relative_heading;

	entity
		*en,
		*wp;

	vec3d
		*en_position,
		wp_position;

	object_3d_visibility
		visibility;

	en = get_gunship_entity ();

	wp = get_local_entity_current_waypoint (en);

	if (wp)
	{
		en_position = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

		get_waypoint_display_position (en, wp, &wp_position);

		//
		// flight path marker
		//

		draw_flight_path_marker = FALSE;

		if (draw_on_virtual_cockpit_texture)
		{
			if
			(
				(pilot_head_heading >= rad (-5.0)) &&
				(pilot_head_heading <= rad (5.0)) &&
				(pilot_head_pitch >= rad (-5.0)) &&
				(pilot_head_pitch <= rad (5.0))
			)
			{
				draw_flight_path_marker = TRUE;
			}
		}
		else
		{
			draw_flight_path_marker = TRUE;
		}

		if (draw_flight_path_marker)
		{
			if (!ka50_damage.navigation_computer)
			{
				visibility = get_position_3d_screen_coordinates (&wp_position, &i, &j);

				if ((visibility == OBJECT_3D_COMPLETELY_VISIBLE) || (visibility == OBJECT_3D_PARTIALLY_VISIBLE))
				{
					transform_hud_screen_co_ords_to_hud_texture_co_ords (&i, &j);

					get_2d_world_position (i, j, &x, &y);

					clip_2d_point_to_hud_extent (&x, &y);

					draw_2d_circle (x, y, 0.125, hud_colour);
				}
				else
				{
					dx = wp_position.x - en_position->x;
					dz = wp_position.z - en_position->z;

					bearing = atan2 (dx, dz);

					heading = get_local_entity_float_value (en, FLOAT_TYPE_HEADING);

					relative_heading = bearing - heading;

					if (relative_heading < rad (-180.0))
					{
						relative_heading += rad (360.0);
					}
					else if (relative_heading > rad (180.0))
					{
						relative_heading -= rad (360.0);
					}

					if (relative_heading < 0.0)
					{
						draw_2d_circle (-1.0, 0.0, 0.125, hud_colour);
					}
					else
					{
						draw_2d_circle (1.0, 0.0, 0.125, hud_colour);
					}
				}
			}
		}

		//
		// waypoint information
		//

		if (!ka50_damage.navigation_computer)
		{
			tag = get_local_entity_char_value (wp, CHAR_TYPE_TAG);

			flat_range = get_2d_range (en_position, &wp_position);

			sprintf (s, "%c:%.1f", tag, flat_range * (1.0 / 1000.0));
		}
		else
		{
			sprintf (s, "-:--.-");
		}

		if (draw_large_hud)
		{
			set_mono_font_type (MONO_FONT_TYPE_6X10);
		}
		else
		{
			set_mono_font_type (MONO_FONT_TYPE_6X7);
		}

		set_2d_mono_font_position (0.0, -0.8);

		width = get_mono_font_string_width (s);

		set_mono_font_rel_position ((-width * 0.5) + 1.0, 0.0);

		print_mono_font_string (s);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_bob_up_overlay (void)
{
	float
		heading,
		bearing,
		theta,
		length,
		dx,
		dz,
		dxt,
		dzt;

	vec3d
		*position,
		*motion_vector;

	if (hud_bob_up_overlay)
	{
		position = get_local_entity_vec3d_ptr (get_gunship_entity (), VEC3D_TYPE_POSITION);

		dx = hud_bob_up_position.x - position->x;
		dz = hud_bob_up_position.z - position->z;

		if (((dx * dx) + (dz * dz)) < (500.0 * 500.0))
		{
			heading = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_HEADING);

			//
			// hover box
			//

			dxt = (dx * cos (heading)) - (dz * sin (heading));
			dzt = (dx * sin (heading)) + (dz * cos (heading));

			dxt *= 1.0 / 100.0;
			dzt *= 1.0 / 100.0;

			clip_2d_point_to_hud_extent (&dxt, &dzt);

			draw_2d_line (dxt - 0.083, dzt + 0.200, dxt + 0.083, dzt + 0.200, hud_colour);
			draw_2d_line (dxt + 0.083, dzt + 0.200, dxt + 0.200, dzt + 0.083, hud_colour);
			draw_2d_line (dxt + 0.200, dzt + 0.083, dxt + 0.200, dzt - 0.083, hud_colour);
			draw_2d_line (dxt + 0.200, dzt - 0.083, dxt + 0.083, dzt - 0.200, hud_colour);
			draw_2d_line (dxt + 0.083, dzt - 0.200, dxt - 0.083, dzt - 0.200, hud_colour);
			draw_2d_line (dxt - 0.083, dzt - 0.200, dxt - 0.200, dzt - 0.083, hud_colour);
			draw_2d_line (dxt - 0.200, dzt - 0.083, dxt - 0.200, dzt + 0.083, hud_colour);
			draw_2d_line (dxt - 0.200, dzt + 0.083, dxt - 0.083, dzt + 0.200, hud_colour);

			//
			// velocity vector
			//

			motion_vector = get_local_entity_vec3d_ptr (get_gunship_entity (), VEC3D_TYPE_MOTION_VECTOR);

			dx = motion_vector->x;
			dz = motion_vector->z;

			length = sqrt ((dx * dx) + (dz * dz));

			if ((length < kilometres_per_hour_to_metres_per_second (-0.1)) || (length > kilometres_per_hour_to_metres_per_second (0.1)))
			{
				length = min (length, kilometres_per_hour_to_metres_per_second (20.0));

				length *= 0.5 / kilometres_per_hour_to_metres_per_second (20.0);

				bearing = atan2 (dx, dz);

				theta = bearing - heading;

				if (theta > rad (180.0))
				{
					theta -= rad (360.0);
				}
				else if (theta < rad (-180.0))
				{
					theta += rad (360.0);
				}
			}
			else
			{
				length = 0.0;

				theta = 0.0;
			}

			set_2d_window_rotation (hud_env, -theta);

			draw_2d_line (0.0, 0.0, 0.0, length, hud_colour);

			if (draw_large_hud)
			{
				length = max (length - 0.008, 0.0);

				draw_2d_line (-0.008, length, 0.008, length, hud_colour);
			}

			set_2d_window_rotation (hud_env, 0.0);
		}
		else
		{
			clear_hud_bob_up_overlay ();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_navigation_mode_hud (int draw_on_virtual_cockpit_texture)
{
	draw_hud_centre_datum ();

	draw_heading_scale ();

	draw_pitch_indicator ();

	draw_bank_scale ();

	draw_aircraft_datum ();

	display_true_airspeed ();

	display_altitude ();

	draw_rate_of_climb_scale ();

	display_engine_torque ();

	display_flight_path_marker_and_waypoint_information (draw_on_virtual_cockpit_texture);

	draw_bob_up_overlay ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_weapon_mode_hud (int draw_on_virtual_cockpit_texture)
{
	if (get_view_mode () != VIEW_MODE_COCKPIT_PANEL_LEVEL_AHEAD)
	{
		draw_hud_centre_datum ();
	}

	draw_heading_scale ();

	display_true_airspeed ();

	display_altitude ();

	display_engine_torque ();

	draw_bob_up_overlay ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_ka50_hud (void)
{
	hud_env = create_2d_environment ();

	hud_texture_screen = create_system_texture_screen (HUD_VIEWPORT_SMALL_SIZE, HUD_VIEWPORT_SMALL_SIZE, TEXTURE_INDEX_HVCKPT_HUD_DISPLAY, TEXTURE_TYPE_SINGLEALPHA);

	large_hud_texture_screen = create_system_texture_screen (HUD_VIEWPORT_LARGE_SIZE, HUD_VIEWPORT_LARGE_SIZE, LARGE_HUD_TEXTURE_INDEX, TEXTURE_TYPE_SINGLEALPHA);

	large_hms_texture_screen = create_system_texture_screen (HUD_VIEWPORT_LARGE_SIZE, HUD_VIEWPORT_LARGE_SIZE, LARGE_HMS_TEXTURE_INDEX, TEXTURE_TYPE_SINGLEALPHA);

	set_rgb_colour (clear_hud_colour, 255, 255, 255, 0);

	initialise_hms_gun_pipper ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_ka50_hud (void)
{
	destroy_2d_environment (hud_env);

	destroy_screen (hud_texture_screen);

	destroy_screen (large_hud_texture_screen);

	destroy_screen (large_hms_texture_screen);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_ka50_hud_on_cockpit (int hud_enlarge)
{
	if (ka50_damage.head_up_display)
	{
		return;
	}

	//
	// set active 3D environment now else 2D clipping will be affected
	//

	set_main_3d_full_screen_params (DISPLAY_3D_TINT_CLEAR, DISPLAY_3D_LIGHT_LEVEL_HIGH, DISPLAY_3D_NOISE_LEVEL_NONE);

	set_3d_active_environment (main_3d_env);

	////////////////////////////////////////
	//
	// set up HUD 2D environment
	//
	////////////////////////////////////////

	set_2d_active_environment (hud_env);

	//
	// window
	//

	set_2d_window (hud_env, HUD_WINDOW_X_MIN, HUD_WINDOW_Y_MIN, HUD_WINDOW_X_MAX, HUD_WINDOW_Y_MAX);

	//
	// viewport
	//

	draw_large_hud = hud_enlarge;

	if (draw_large_hud)
	{
		hud_viewport_size = HUD_VIEWPORT_LARGE_SIZE;
	}
	else
	{
		hud_viewport_size = HUD_VIEWPORT_SMALL_SIZE;
	}

	hud_viewport_x_org = full_screen_x_mid;

	hud_viewport_y_org = full_screen_y_mid;

	hud_viewport_x_min = hud_viewport_x_org - (hud_viewport_size * 0.5);

	hud_viewport_y_min = hud_viewport_y_org - (hud_viewport_size * 0.5);

	hud_viewport_x_max = hud_viewport_x_org + (hud_viewport_size * 0.5) - 0.001;

	hud_viewport_y_max = hud_viewport_y_org + (hud_viewport_size * 0.5) - 0.001;

	set_2d_viewport (hud_env, hud_viewport_x_min, hud_viewport_y_min, hud_viewport_x_max, hud_viewport_y_max);

	//
	// get screen co-ords (constant size - does not require scaling)
	//

	hud_screen_x_min = 0.0;
	hud_screen_y_min = 0.0;

	hud_screen_x_max = hud_viewport_size - 0.001;
	hud_screen_y_max = hud_viewport_size - 0.001;

	hud_screen_x_scale = 1.0;
	hud_screen_y_scale = 1.0;

	////////////////////////////////////////
	//
	// draw HUD
	//
	////////////////////////////////////////

	if (lock_screen (active_screen))
	{
		set_mono_font_colour (hud_colour);

		draw_layout_grid ();

		switch (hud_mode)
		{
			case HUD_MODE_NAVIGATION:
			case HUD_MODE_TRANSITION:
			{
				draw_navigation_mode_hud (FALSE);

				break;
			}
			case HUD_MODE_WEAPON:
			{
				draw_weapon_mode_hud (FALSE);

				break;
			}
		}

		unlock_screen (active_screen);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_ka50_hud_on_texture (void)
{
	//
	// set active 3D environment now else 2D clipping will be affected
	//

	set_main_3d_full_screen_params (DISPLAY_3D_TINT_CLEAR, DISPLAY_3D_LIGHT_LEVEL_HIGH, DISPLAY_3D_NOISE_LEVEL_NONE);

	set_3d_active_environment (main_3d_env);

	////////////////////////////////////////
	//
	// set up HUD 2D environment
	//
	////////////////////////////////////////

	set_2d_active_environment (hud_env);

	//
	// window
	//

	set_2d_window (hud_env, HUD_WINDOW_X_MIN, HUD_WINDOW_Y_MIN, HUD_WINDOW_X_MAX, HUD_WINDOW_Y_MAX);

	//
	// viewport
	//

	draw_large_hud = FALSE;

	hud_viewport_size = HUD_VIEWPORT_SMALL_SIZE;

	hud_viewport_x_org = HUD_VIEWPORT_TEXTURE_X_ORG;

	hud_viewport_y_org = HUD_VIEWPORT_TEXTURE_Y_ORG;

	hud_viewport_x_min = hud_viewport_x_org - (hud_viewport_size * 0.5);

	hud_viewport_y_min = hud_viewport_y_org - (hud_viewport_size * 0.5);

	hud_viewport_x_max = hud_viewport_x_org + (hud_viewport_size * 0.5) - 0.001;

	hud_viewport_y_max = hud_viewport_y_org + (hud_viewport_size * 0.5) - 0.001;

	set_2d_viewport (hud_env, hud_viewport_x_min, hud_viewport_y_min, hud_viewport_x_max, hud_viewport_y_max);

	//
	// get screen co-ords (vitural cockpit texture - scaling only works near screen centre)
	//

	hud_screen_x_min = full_screen_x_mid - ((HUD_VIEWPORT_SMALL_SIZE / (640.0 * 2.0)) * full_screen_width);
	hud_screen_y_min = full_screen_y_mid - ((HUD_VIEWPORT_SMALL_SIZE / (480.0 * 2.0)) * full_screen_height);

	hud_screen_x_max = full_screen_x_mid + ((HUD_VIEWPORT_SMALL_SIZE / (640.0 * 2.0)) * full_screen_width) - 0.001;
	hud_screen_y_max = full_screen_y_mid + ((HUD_VIEWPORT_SMALL_SIZE / (480.0 * 2.0)) * full_screen_height) - 0.001;

	hud_screen_x_scale = 640.0 / full_screen_width;
	hud_screen_y_scale = 480.0 / full_screen_height;

	////////////////////////////////////////
	//
	// draw HUD
	//
	////////////////////////////////////////

	set_active_screen (hud_texture_screen);

	if (lock_screen (hud_texture_screen))
	{
		rgb_colour
			clear_hud_colour;

		set_rgb_colour (clear_hud_colour, hud_colour.r, hud_colour.g, hud_colour.b, 0);

		set_block (0, 0, HUD_VIEWPORT_SMALL_SIZE - 1, HUD_VIEWPORT_SMALL_SIZE - 1, clear_hud_colour);

		if (!ka50_damage.head_up_display)
		{
			set_mono_font_colour (hud_colour);

			draw_layout_grid ();

			switch (hud_mode)
			{
				case HUD_MODE_NAVIGATION:
				case HUD_MODE_TRANSITION:
				{
					draw_navigation_mode_hud (TRUE);

					break;
				}
				case HUD_MODE_WEAPON:
				{
					draw_weapon_mode_hud (TRUE);

					break;
				}
			}
		}

		flush_screen_texture_graphics (hud_texture_screen);

		unlock_screen (hud_texture_screen);
	}

	set_active_screen (video_screen);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_external_ka50_hud (void)
{
	rgb_colour
		store_hud_colour;

	vertex
		quad[4];

	real_colour
		colour,
		specular;

	////////////////////////////////////////
	//
	// do not draw damaged HUD
	//
	////////////////////////////////////////

	if (ka50_damage.head_up_display)
	{
		return;
	}

	////////////////////////////////////////
	//
	// set active 3D environment now else 2D clipping will be affected
	//
	////////////////////////////////////////

	set_main_3d_full_screen_params (DISPLAY_3D_TINT_CLEAR, DISPLAY_3D_LIGHT_LEVEL_HIGH, DISPLAY_3D_NOISE_LEVEL_NONE);

	set_3d_active_environment (main_3d_env);

	////////////////////////////////////////
	//
	// set up HUD 2D environment
	//
	////////////////////////////////////////

	set_2d_active_environment (hud_env);

	set_2d_window (hud_env, HUD_WINDOW_X_MIN, HUD_WINDOW_Y_MIN, HUD_WINDOW_X_MAX, HUD_WINDOW_Y_MAX);

	draw_large_hud = TRUE;

	hud_viewport_size = HUD_VIEWPORT_LARGE_SIZE;

	hud_viewport_x_org = HUD_VIEWPORT_LARGE_SIZE * 0.5;

	hud_viewport_y_org = HUD_VIEWPORT_LARGE_SIZE * 0.5;

	hud_viewport_x_min = 0.0;

	hud_viewport_y_min = 0.0;

	hud_viewport_x_max = HUD_VIEWPORT_LARGE_SIZE - 0.001;

	hud_viewport_y_max = HUD_VIEWPORT_LARGE_SIZE - 0.001;

	set_2d_viewport (hud_env, hud_viewport_x_min, hud_viewport_y_min, hud_viewport_x_max, hud_viewport_y_max);

	//
	// get screen co-ords (scaled to keep HUD size constant)
	//

	if (get_global_unscaled_displays ())
	{
		hud_screen_x_min = full_screen_x_mid - 128.0;
		hud_screen_y_min = full_screen_y_mid - 128.0;

		hud_screen_x_max = full_screen_x_mid + 127.999;
		hud_screen_y_max = full_screen_y_mid + 127.999;

		hud_screen_x_scale = 1.0;
		hud_screen_y_scale = 1.0;
	}
	else
	{
		hud_screen_x_min = full_screen_x_mid - ((256.0 / (640.0 * 2.0)) * full_screen_width);
		hud_screen_y_min = full_screen_y_mid - ((256.0 / (480.0 * 2.0)) * full_screen_height);

		hud_screen_x_max = full_screen_x_mid + ((256.0 / (640.0 * 2.0)) * full_screen_width) - 0.001;
		hud_screen_y_max = full_screen_y_mid + ((256.0 / (480.0 * 2.0)) * full_screen_height) - 0.001;

		hud_screen_x_scale = 640.0 / full_screen_width;
		hud_screen_y_scale = 480.0 / full_screen_height;
	}

	////////////////////////////////////////
	//
	// draw HUD on texture
	//
	////////////////////////////////////////

	set_active_screen (large_hud_texture_screen);

	if (lock_screen (large_hud_texture_screen))
	{
	 	store_hud_colour = hud_colour;

		set_rgb_colour (hud_colour, 255, 255, 255, 255);

		set_mono_font_colour (hud_colour);

		set_block (0, 0, HUD_VIEWPORT_LARGE_SIZE - 1, HUD_VIEWPORT_LARGE_SIZE - 1, clear_hud_colour);

		draw_layout_grid ();

		switch (hud_mode)
		{
			case HUD_MODE_NAVIGATION:
			{
				draw_navigation_mode_hud (FALSE);

				break;
			}
			case HUD_MODE_WEAPON:
			{
				draw_weapon_mode_hud (FALSE);

				break;
			}
		}

		hud_colour = store_hud_colour;

		flush_screen_texture_graphics (large_hud_texture_screen);

		unlock_screen (large_hud_texture_screen);
	}

	set_active_screen (video_screen);

	////////////////////////////////////////
	//
	// render HUD to screen
	//
	////////////////////////////////////////

	set_3d_active_environment (main_3d_env);

	if (begin_3d_scene ())
	{
		set_d3d_transparency_on ();

		set_d3d_zbuffer_comparison (FALSE);

		set_d3d_culling (FALSE);

		set_d3d_texture_wrapping (0, FALSE);

		if ((application_video_width == 640) || (get_global_unscaled_displays ()))
		{
			set_d3d_texture_mag_filtering (FALSE);
			set_d3d_texture_min_filtering (FALSE);
			set_d3d_texture_mip_filtering (FALSE);
		}
		else
		{
			set_d3d_texture_mag_filtering (TRUE);
			set_d3d_texture_min_filtering (TRUE);
			set_d3d_texture_mip_filtering (FALSE);
		}

		set_d3d_flat_shaded_textured_renderstate (get_system_texture_ptr (LARGE_HUD_TEXTURE_INDEX));

		////////////////////////////////////////
		//

		colour.red 				= hud_colour_table[get_global_hud_colour ()].r;
		colour.green 			= hud_colour_table[get_global_hud_colour ()].g;
		colour.blue	  			= hud_colour_table[get_global_hud_colour ()].b;
		colour.alpha 			= 255;

		specular.red 			= 0;
		specular.green			= 0;
		specular.blue			= 0;
		specular.alpha			= 255;

		quad[0].i				= hud_screen_x_min;
		quad[0].j				= hud_screen_y_min;
		quad[0].z				= 0.5;
		quad[0].q				= 0.5;
		quad[0].u				= 0.0;
		quad[0].v				= 0.0;

		quad[1].i				= hud_screen_x_max;
		quad[1].j				= hud_screen_y_min;
		quad[1].z				= 0.5;
		quad[1].q				= 0.5;
		quad[1].u				= 1.0;
		quad[1].v				= 0.0;

		quad[2].i				= hud_screen_x_max;
		quad[2].j				= hud_screen_y_max;
		quad[2].z				= 0.5;
		quad[2].q				= 0.5;
		quad[2].u				= 1.0;
		quad[2].v				= 1.0;

		quad[3].i				= hud_screen_x_min;
		quad[3].j				= hud_screen_y_max;
		quad[3].z				= 0.5;
		quad[3].q				= 0.5;
		quad[3].u				= 0.0;
		quad[3].v				= 1.0;

		quad[0].next_vertex	= &quad[1];
		quad[1].next_vertex	= &quad[2];
		quad[2].next_vertex	= &quad[3];
		quad[3].next_vertex	= NULL;

		//
		////////////////////////////////////////

		draw_wbuffered_flat_shaded_textured_polygon (quad, colour, specular);

		set_d3d_transparency_off ();

		set_d3d_zbuffer_comparison (TRUE);

		set_d3d_culling (TRUE);

		end_3d_scene ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HELMET MOUNTED SIGHT
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_hms_centre_datum (void)
{
	draw_2d_line (-0.10, +0.00, -0.05, +0.00, hud_colour);
	draw_2d_line (+0.10, +0.00, +0.05, +0.00, hud_colour);
	draw_2d_line (+0.00, -0.10, +0.00, -0.05, hud_colour);
	draw_2d_line (+0.00, +0.10, +0.00, +0.05, hud_colour);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define GUN_PIPPER_SIZE						(0.15)
#define NUM_GUN_PIPPER_POINTS				(130)
#define GUN_PIPPER_ANGULAR_STEP_SIZE	(PI2 / NUM_GUN_PIPPER_POINTS)

static float
	gun_pipper_points[NUM_GUN_PIPPER_POINTS][2];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void initialise_hms_gun_pipper (void)
{
	int
		i;

	float
		theta,
		sin_theta,
		cos_theta;

	theta = 0.0;

	for (i = 0; i < NUM_GUN_PIPPER_POINTS; i++)
	{
		sin_theta = sin (theta);
		cos_theta = cos (theta);

		gun_pipper_points[i][0] = sin_theta * GUN_PIPPER_SIZE;
		gun_pipper_points[i][1] = cos_theta * GUN_PIPPER_SIZE;

		theta += GUN_PIPPER_ANGULAR_STEP_SIZE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_gun_pipper (float x, float y, float range, float max_range)
{
	float
		normalised_range,
		theta;

	int
		i,
		i_max;

	normalised_range = range / max_range;

	i_max = (int) (normalised_range * NUM_GUN_PIPPER_POINTS);

	i_max = bound (i_max, 0, NUM_GUN_PIPPER_POINTS - 1);

	for (i = 0; i <= i_max; i++)
	{
		set_2d_pixel (x + gun_pipper_points[i][0], y + gun_pipper_points[i][1], hud_colour);
	}

	set_2d_instance_position (hud_env, x, y);

	draw_2d_line (0.0, 0.15, 0.0, 0.18, hud_colour);

	theta = normalised_range * -PI2;

	set_2d_instance_rotation (hud_env, theta);

	draw_2d_line (0.0, 0.15, 0.0, 0.18, hud_colour);

	reset_2d_instance (hud_env);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_target_marker_valid_lock (float x, float y)
{
	draw_2d_circle (x, y, 0.2, hud_colour);

	draw_2d_line (x - 0.20, y, x - 0.25, y, hud_colour);
	draw_2d_line (x + 0.20, y, x + 0.25, y, hud_colour);
	draw_2d_line (x, y - 0.20, x, y - 0.25, hud_colour);
	draw_2d_line (x, y + 0.20, x, y + 0.25, hud_colour);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_target_marker_invalid_lock (float x, float y)
{
	draw_2d_circle (x, y, 0.2, hud_colour);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_target_marker (void)
{
	int
		airborne_target;

	entity_sub_types
		selected_weapon_type;

	object_3d_visibility
		visibility;

	float
		i,
		j,
		x,
		y,
		target_range;

	entity
		*source,
		*target;

	vec3d
		*source_position,
		target_position,
		intercept_point;

	source = get_gunship_entity ();

	selected_weapon_type = get_local_entity_int_value (source, INT_TYPE_SELECTED_WEAPON);

	if (selected_weapon_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
	{
		target = get_local_entity_parent (source, LIST_TYPE_TARGET);

		if (target)
		{
			airborne_target = get_local_entity_int_value (target, INT_TYPE_AIRBORNE_AIRCRAFT);

			get_local_entity_target_point (target, &target_position);

			visibility = get_position_3d_screen_coordinates (&target_position, &i, &j);

			if ((visibility == OBJECT_3D_COMPLETELY_VISIBLE) || (visibility == OBJECT_3D_PARTIALLY_VISIBLE))
			{
				transform_hud_screen_co_ords_to_hud_texture_co_ords (&i, &j);

				get_2d_world_position (i, j, &x, &y);

				clip_2d_point_to_hud_extent (&x, &y);

				if (weapon_lock_type == WEAPON_LOCK_VALID)
				{
					if
					(
						(selected_weapon_type == ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND) ||
						(selected_weapon_type == ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND) ||
						(selected_weapon_type == ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND)
					)
					{
						source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

						target_range = get_3d_range (source_position, &target_position);

						if (target_range < weapon_database[selected_weapon_type].max_range)
						{
							draw_gun_pipper (x, y, target_range, weapon_database[selected_weapon_type].max_range);
						}
						else
						{
							draw_target_marker_valid_lock (x, y);
						}
					}
					else
					{
						draw_target_marker_valid_lock (x, y);
					}
				}
				else
				{
					draw_target_marker_invalid_lock (x, y);
				}

				//
				// if unguided weapon then draw a dot in the target marker centre (except for airborne targets)
				//

				if (!airborne_target)
				{
					if (weapon_database[selected_weapon_type].guidance_type == WEAPON_GUIDANCE_TYPE_NONE)
					{
						set_2d_pixel (x, y, hud_colour);
					}
				}
			}

			//
			// if airborne target then draw the intercept point
			//

			if (airborne_target)
			{
				get_target_intercept_point (source, target, selected_weapon_type, &intercept_point);

				visibility = get_position_3d_screen_coordinates (&intercept_point, &i, &j);

				if ((visibility == OBJECT_3D_COMPLETELY_VISIBLE) || (visibility == OBJECT_3D_PARTIALLY_VISIBLE))
				{
					transform_hud_screen_co_ords_to_hud_texture_co_ords (&i, &j);

					get_2d_world_position (i, j, &x, &y);

					clip_2d_point_to_hud_extent (&x, &y);

					draw_2d_line (x - 0.05, y, x + 0.05, y, hud_colour);
					draw_2d_line (x, y - 0.05, x, y + 0.05, hud_colour);
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static char target_range_scale_pointer[] =
{
	15,
	9,
	0,
	-4,
	0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
	0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,
	0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,
	0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,
	0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,
	0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define NEAR_RANGE_SCALE				((float) 5000.0)
#define FAR_RANGE_SCALE					((float) 10000.0)
#define ONE_OVER_NEAR_RANGE_SCALE	((float) (1.0 / 5000.0))
#define ONE_OVER_FAR_RANGE_SCALE		((float) (1.0 / 10000.0))

static void draw_target_range_indicator (void)
{
	char
		*s;

	entity
		*source,
		*target;

	entity_sub_types
		selected_weapon_type;

	float
		i,
		j,
		y,
		width,
		target_range,
		range_scale,
		one_over_range_scale,
		min_weapon_range,
		max_weapon_range;

	vec3d
		*source_position,
		*target_position;

	source = get_gunship_entity ();

	target = get_local_entity_parent (source, LIST_TYPE_TARGET);

	//
	// draw range scale (regardless of having a target)
	//

	draw_2d_line (-0.8, 0.5, -0.8, -0.5, hud_colour);

	draw_2d_line (-0.8,  0.5, -0.85,  0.5, hud_colour);
	draw_2d_line (-0.8,  0.3, -0.85,  0.3, hud_colour);
	draw_2d_line (-0.8,  0.1, -0.85,  0.1, hud_colour);
	draw_2d_line (-0.8, -0.1, -0.85, -0.1, hud_colour);
	draw_2d_line (-0.8, -0.3, -0.85, -0.3, hud_colour);
	draw_2d_line (-0.8, -0.5, -0.85, -0.5, hud_colour);

	selected_weapon_type = get_local_entity_int_value (source, INT_TYPE_SELECTED_WEAPON);

	range_scale = FAR_RANGE_SCALE;

	one_over_range_scale = ONE_OVER_FAR_RANGE_SCALE;

	if (selected_weapon_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
	{
		min_weapon_range = weapon_database[selected_weapon_type].min_range;
		max_weapon_range = weapon_database[selected_weapon_type].max_range;

		if (max_weapon_range <= NEAR_RANGE_SCALE)
		{
			range_scale = NEAR_RANGE_SCALE;

			one_over_range_scale = ONE_OVER_NEAR_RANGE_SCALE;
		}

		y = 1.0 - (min_weapon_range * one_over_range_scale);

		draw_2d_line (-0.8, 0.5 - y, -0.75, 0.5 - y, hud_colour);

		y = 1.0 - (max_weapon_range * one_over_range_scale);

		draw_2d_line (-0.8, 0.5 - y, -0.75, 0.5 - y, hud_colour);
	}

	if (range_scale == NEAR_RANGE_SCALE)
	{
		s = "5";
	}
	else
	{
		s = "10";
	}

	set_mono_font_type (MONO_FONT_TYPE_7X12);

	set_2d_mono_font_position (-0.85, 0.5);

	width = get_mono_font_string_width (s);

	set_mono_font_rel_position (-width - 1.0, -4.0);

	print_mono_font_string (s);

	//
	// draw target range pointer
	//

	if (target)
	{
		source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

		target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

		target_range = get_3d_range (source_position, target_position);

		if (target_range < range_scale)
		{
			y = 1.0 - (target_range * one_over_range_scale);
		}
		else
		{
			y = 0.0;
		}

		draw_2d_line (-0.8, 0.5 - y, -0.75, 0.5 - y, hud_colour);

		get_2d_float_screen_coordinates (-0.75, 0.5 - y, &i, &j);

		draw_mono_sprite (target_range_scale_pointer, i, j, hud_colour);
	}
}

#undef NEAR_RANGE_SCALE
#undef FAR_RANGE_SCALE
#undef ONE_OVER_NEAR_RANGE_SCALE
#undef ONE_OVER_FAR_RANGE_SCALE

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_weapon_information (void)
{
	char
		s[100];

	int
		count;

	float
		flight_time;

	entity_sub_types
		weapon_sub_type;

	weapon_sub_type = get_local_entity_int_value (get_gunship_entity (), INT_TYPE_SELECTED_WEAPON);

	if (weapon_sub_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
	{
		set_mono_font_type (MONO_FONT_TYPE_6X10);

		//
		// selected weapon
		//

		count = get_local_entity_weapon_count (get_gunship_entity (), weapon_sub_type);

		sprintf (s, "%s:%d", weapon_database[weapon_sub_type].hud_name, count);

		set_2d_mono_font_position (-1.0, -0.7);

		set_mono_font_rel_position (1.0, 0.0);

		print_mono_font_string (s);

		//
		// weapon specific
		//

		if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_ATAKA)
		{
			flight_time = get_ka50_missile_flight_time ();

			if (flight_time > 0.01)
			{
				flight_time = bound (flight_time, 0.0, 99.9);

				sprintf (s, "%.1f", flight_time);

				set_2d_mono_font_position (-1.0, -0.9);

				set_mono_font_rel_position (1.0, 0.0);

				print_mono_font_string (s);
			}
		}
		else if ((weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_S8) || (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_S13))
		{
			if (rocket_salvo_size == ROCKET_SALVO_SIZE_ALL)
			{
				sprintf (s, "Salvo:ALL");
			}
			else
			{
				sprintf (s, "Salvo:%d", rocket_salvo_size);
			}

			set_2d_mono_font_position (-1.0, -0.8);

			set_mono_font_rel_position (1.0, 0.0);

			print_mono_font_string (s);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_target_information (void)
{
	const char
		*s;
	char
		buffer[200];

	float
		width;

	entity
		*target;

	set_mono_font_type (MONO_FONT_TYPE_6X10);

	//
	// target system
	//

	switch (target_acquisition_system)
	{
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_OFF:
		////////////////////////////////////////
		{
			s = NULL;

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_GROUND_RADAR:
		////////////////////////////////////////
		{
			s = "GND RDR";

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_AIR_RADAR:
		////////////////////////////////////////
		{
			s = "AIR RDR";

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_FLIR:
		////////////////////////////////////////
		{
			s = "FLIR";

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_LLLTV:
		////////////////////////////////////////
		{
			s = "LLLTV";

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_HMS:
		////////////////////////////////////////
		{
			s = "HMS";

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal ("Invalid target acquisition system = %d", target_acquisition_system);

			break;
		}
	}

	if (s)
	{
		width = get_mono_font_string_width (s);

		set_2d_mono_font_position (1.0, -0.6);

		set_mono_font_rel_position (-width, 0.0);

		print_mono_font_string (s);
	}

	//
	// weapon lock
	//

	switch (weapon_lock_type)
	{
		////////////////////////////////////////
		case WEAPON_LOCK_NO_ACQUIRE:
		////////////////////////////////////////
		{
			s = "NO ACQUIRE";

			break;
		}
		////////////////////////////////////////
		case WEAPON_LOCK_NO_WEAPON:
		////////////////////////////////////////
		{
			s = "NO WEAPON";

			break;
		}
		////////////////////////////////////////
		case WEAPON_LOCK_NO_TARGET:
		////////////////////////////////////////
		{
			s = "NO TARGET";

			break;
		}
		////////////////////////////////////////
		case WEAPON_LOCK_INVALID_TARGET:
		////////////////////////////////////////
		{
			s = "INVALID TARGET";

			break;
		}
		////////////////////////////////////////
		case WEAPON_LOCK_SEEKER_LIMIT:
		////////////////////////////////////////
		{
			s = "SEEKER LIMIT";

			break;
		}
		////////////////////////////////////////
		case WEAPON_LOCK_NO_LOS:
		////////////////////////////////////////
		{
			s = "NO LOS";

			break;
		}
		////////////////////////////////////////
		case WEAPON_LOCK_NO_BORESIGHT:
		////////////////////////////////////////
		{
			s = "NO BORESIGHT";

			break;
		}
		////////////////////////////////////////
		case WEAPON_LOCK_MIN_RANGE:
		////////////////////////////////////////
		{
			s = "MIN RANGE";

			break;
		}
		////////////////////////////////////////
		case WEAPON_LOCK_MAX_RANGE:
		////////////////////////////////////////
		{
			s = "MAX RANGE";

			break;
		}
		////////////////////////////////////////
		case WEAPON_LOCK_VALID:
		////////////////////////////////////////
		{
			s = "VALID LOCK";

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal ("Invalid weapon lock type = %d", weapon_lock_type);

			break;
		}
	}

	width = get_mono_font_string_width (s);

	set_2d_mono_font_position (1.0, -0.7);

	set_mono_font_rel_position (-width, 0.0);

	print_mono_font_string (s);

	//
	// locked
	//

	if (target_locked)
	{
		s = "LOCKED";

		width = get_mono_font_string_width (s);

		set_2d_mono_font_position (1.0, -0.8);

		set_mono_font_rel_position (-width, 0.0);

		print_mono_font_string (s);
	}
// Jabberwock 031107 Designated targets
	
	target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);
	
	if (target && get_local_entity_parent (target, LIST_TYPE_DESIGNATED_TARGET))
	{
		s = "MARKED";

		width = get_mono_font_string_width (s);

		set_2d_mono_font_position (-1.0, -0.8);

		set_mono_font_rel_position (1.0, 0.0);

		print_mono_font_string (s);
	}
// Jabberwock 031107 ends


	//
	// target name
	//

	target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

	if (target)
	{
		s = get_target_display_name (target, buffer, TRUE);

		if (s)
		{
			width = get_mono_font_string_width (s);

			set_2d_mono_font_position (1.0, -0.9);

			set_mono_font_rel_position (-width, 0.0);

			print_mono_font_string (s);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_ka50_hms (void)
{
	rgb_colour
		store_hud_colour;

	int
		alpha;

	float
		heading_offset,
		pitch_offset,
		max_offset;

	vertex
		quad[4];

	real_colour
		colour,
		specular;

	////////////////////////////////////////
	//
	// do not draw damaged or inactive HMS
	//
	////////////////////////////////////////

	if (ka50_damage.helmet_mounted_sight)
	{
		return;
	}

	if (hud_mode != HUD_MODE_WEAPON)
	{
		return;
	}

	////////////////////////////////////////
	//
	// reduce alpha as the HUD interferes with the instrument view (some cards cannot do this)
	//
	////////////////////////////////////////

	alpha = 255;

	if (in_cockpit)
	{
		if (get_global_draw_cockpit_graphics ())
		{
			if (d3d_modulate_alpha)
			{
				heading_offset = KA50_INSTRUMENT_VIEW_HEADING - pilot_head_heading;

				if (heading_offset < 0.0)
				{
					heading_offset = -heading_offset;
				}

				pitch_offset = KA50_INSTRUMENT_VIEW_PITCH - pilot_head_pitch;

				if (pitch_offset < 0.0)
				{
					pitch_offset = -pitch_offset;
				}

				if ((heading_offset < rad (25.0)) && (pitch_offset < rad (25.0)))
				{
					max_offset = max (heading_offset, pitch_offset);

					alpha = (int) (max_offset * (200.0 / rad (25.0))) + 55;

					alpha = bound (alpha, 0, 255);
				}
			}
			else
			{
				if ((pilot_head_heading == KA50_INSTRUMENT_VIEW_HEADING) && (pilot_head_pitch == KA50_INSTRUMENT_VIEW_PITCH))
				{
					return;
				}
			}
		}
	}

	////////////////////////////////////////
	//
	// set active 3D environment now else 2D clipping will be affected
	//
	////////////////////////////////////////

	set_main_3d_full_screen_params (DISPLAY_3D_TINT_CLEAR, DISPLAY_3D_LIGHT_LEVEL_HIGH, DISPLAY_3D_NOISE_LEVEL_NONE);

	set_3d_active_environment (main_3d_env);

	////////////////////////////////////////
	//
	// set up HUD 2D environment
	//
	////////////////////////////////////////

	set_2d_active_environment (hud_env);

	set_2d_window (hud_env, HUD_WINDOW_X_MIN, HUD_WINDOW_Y_MIN, HUD_WINDOW_X_MAX, HUD_WINDOW_Y_MAX);

	hud_viewport_x_org = HUD_VIEWPORT_LARGE_SIZE * 0.5;

	hud_viewport_y_org = HUD_VIEWPORT_LARGE_SIZE * 0.5;

	hud_viewport_x_min = 0.0;

	hud_viewport_y_min = 0.0;

	hud_viewport_x_max = HUD_VIEWPORT_LARGE_SIZE - 0.001;

	hud_viewport_y_max = HUD_VIEWPORT_LARGE_SIZE - 0.001;

	set_2d_viewport (hud_env, hud_viewport_x_min, hud_viewport_y_min, hud_viewport_x_max, hud_viewport_y_max);

	//
	// get screen co-ords (scaled to keep HUD size constant)
	//

	if (get_global_unscaled_displays ())
	{
		hud_screen_x_min = full_screen_x_mid - 128.0;
		hud_screen_y_min = full_screen_y_mid - 128.0;

		hud_screen_x_max = full_screen_x_mid + 127.999;
		hud_screen_y_max = full_screen_y_mid + 127.999;

		hud_screen_x_scale = 1.0;
		hud_screen_y_scale = 1.0;
	}
	else
	{
		hud_screen_x_min = full_screen_x_mid - ((256.0 / (640.0 * 2.0)) * full_screen_width);
		hud_screen_y_min = full_screen_y_mid - ((256.0 / (480.0 * 2.0)) * full_screen_height);

		hud_screen_x_max = full_screen_x_mid + ((256.0 / (640.0 * 2.0)) * full_screen_width) - 0.001;
		hud_screen_y_max = full_screen_y_mid + ((256.0 / (480.0 * 2.0)) * full_screen_height) - 0.001;

		hud_screen_x_scale = 640.0 / full_screen_width;
		hud_screen_y_scale = 480.0 / full_screen_height;
	}

	////////////////////////////////////////
	//
	// draw HUD on texture
	//
	////////////////////////////////////////

	set_active_screen (large_hms_texture_screen);

	if (lock_screen (large_hms_texture_screen))
	{
	 	store_hud_colour = hud_colour;

		set_rgb_colour (hud_colour, 255, 255, 255, 255);

		set_mono_font_colour (hud_colour);

		set_block (0, 0, HUD_VIEWPORT_LARGE_SIZE - 1, HUD_VIEWPORT_LARGE_SIZE - 1, clear_hud_colour);

		draw_layout_grid ();

		draw_hms_centre_datum ();

		draw_target_marker ();

		draw_target_range_indicator ();

		display_weapon_information ();

		display_target_information ();

		hud_colour = store_hud_colour;

		flush_screen_texture_graphics (large_hms_texture_screen);

		unlock_screen (large_hms_texture_screen);
	}

	set_active_screen (video_screen);

	////////////////////////////////////////
	//
	// render HUD to screen
	//
	////////////////////////////////////////

	set_3d_active_environment (main_3d_env);

	if (begin_3d_scene ())
	{
		set_d3d_transparency_on ();

		set_d3d_zbuffer_comparison (FALSE);

		set_d3d_culling (FALSE);

		set_d3d_texture_wrapping (0, FALSE);

		if ((application_video_width == 640) || (get_global_unscaled_displays ()))
		{
			set_d3d_texture_mag_filtering (FALSE);
			set_d3d_texture_min_filtering (FALSE);
			set_d3d_texture_mip_filtering (FALSE);
		}
		else
		{
			set_d3d_texture_mag_filtering (TRUE);
			set_d3d_texture_min_filtering (TRUE);
			set_d3d_texture_mip_filtering (FALSE);
		}

		set_d3d_flat_shaded_textured_renderstate (get_system_texture_ptr (LARGE_HMS_TEXTURE_INDEX));

		////////////////////////////////////////
		//

		colour.red				= hud_colour_table[get_global_hud_colour ()].r;
		colour.green			= hud_colour_table[get_global_hud_colour ()].g;
		colour.blue				= hud_colour_table[get_global_hud_colour ()].b;
		colour.alpha			= alpha;

		specular.red			= 0;
		specular.green			= 0;
		specular.blue			= 0;
		specular.alpha			= 255;

		quad[0].i				= hud_screen_x_min;
		quad[0].j				= hud_screen_y_min;
		quad[0].z				= 0.5;
		quad[0].q				= 0.5;
		quad[0].u				= 0.0;
		quad[0].v				= 0.0;

		quad[1].i				= hud_screen_x_max;
		quad[1].j				= hud_screen_y_min;
		quad[1].z				= 0.5;
		quad[1].q				= 0.5;
		quad[1].u				= 1.0;
		quad[1].v				= 0.0;

		quad[2].i				= hud_screen_x_max;
		quad[2].j				= hud_screen_y_max;
		quad[2].z				= 0.5;
		quad[2].q				= 0.5;
		quad[2].u				= 1.0;
		quad[2].v				= 1.0;

		quad[3].i				= hud_screen_x_min;
		quad[3].j				= hud_screen_y_max;
		quad[3].z				= 0.5;
		quad[3].q				= 0.5;
		quad[3].u				= 0.0;
		quad[3].v				= 1.0;

		quad[0].next_vertex	= &quad[1];
		quad[1].next_vertex	= &quad[2];
		quad[2].next_vertex	= &quad[3];
		quad[3].next_vertex	= NULL;

		//
		////////////////////////////////////////

		draw_wbuffered_flat_shaded_textured_polygon (quad, colour, specular);

		set_d3d_transparency_off ();

		set_d3d_zbuffer_comparison (TRUE);

		set_d3d_culling (TRUE);

		end_3d_scene ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
