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
static void display_weapon_information (void);
static void display_target_information (void);

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
	*large_hms_texture_screen;

static rgb_colour
	clear_hud_colour;

#define HUD_UNIT_RATIO 14.6    // ratio of HUD size with distance to HUD

static void (*draw_line_func)(float, float, float, float, const rgb_colour) = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//
// heading scale
//
////////////////////////////////////////


////////////////////////////////////////
//
// heading scale
//
////////////////////////////////////////

static char large_hud_command_heading_carat[] =
{
	11,
	6,
	-5,
	0,
	0,0,0,0,0,1,0,0,0,0,0,
	0,0,0,0,1,1,1,0,0,0,0,
	0,0,0,1,1,0,1,1,0,0,0,
	0,0,1,1,0,0,0,1,1,0,0,
	0,1,1,0,0,0,0,0,1,1,0,
	1,1,0,0,0,0,0,0,0,1,1,
};

static char large_hud_heading_carat[] =
{
	11,
	6,
	-5,
	0,
	0,0,0,0,0,1,0,0,0,0,0,
	0,0,0,0,1,1,1,0,0,0,0,
	0,0,0,1,1,1,1,1,0,0,0,
	0,0,1,1,1,1,1,1,1,0,0,
	0,1,1,1,1,1,1,1,1,1,0,
	1,1,1,1,1,1,1,1,1,1,1,
};

static char large_right_carat[] =
{
	5,
	9,
	-4,
	-4,
	1,0,0,0,0,
	1,1,0,0,0,
	1,1,1,0,0,
	1,1,1,1,0,
	1,1,1,1,1,
	1,1,1,1,0,
	1,1,1,0,0,
	1,1,0,0,0,
	1,0,0,0,0,
};

static char large_left_carat[] =
{
	5,
	9,
	0,
	-4,
	0,0,0,0,1,
	0,0,0,1,1,
	0,0,1,1,1,
	0,1,1,1,1,
	1,1,1,1,1,
	0,1,1,1,1,
	0,0,1,1,1,
	0,0,0,1,1,
	0,0,0,0,1,
};

static char small_right_carat[] =
{
	3,
	5,
	-2,
	-2,
	1,0,0,
	1,1,0,
	1,1,1,
	1,1,0,
	1,0,0,
};

static char small_left_carat[] =
{
	3,
	5,
	0,
	-2,
	0,0,1,
	0,1,1,
	1,1,1,
	0,1,1,
	0,0,1,
};

static char small_hud_heading_carat[] =
{
	5,
	3,
	-2,
	0,
	0,0,1,0,0,
	0,1,1,1,0,
	1,1,1,1,1,
};

static char small_hud_command_heading_carat[] =
{
	5,
	3,
	-2,
	0,
	0,0,1,0,0,
	0,1,0,1,0,
	1,0,0,0,1,
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
	// sort first major tick position (draw 2 major ticks either side of centre)
	//

	heading = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_HEADING);

	heading = deg (heading);

	mod_heading_step_10 = fmod (heading, 10.0);

	int_heading_step_10 = ((int) (heading * 0.1));

	int_heading_step_10 -= 2;

	if (int_heading_step_10 < 0)
	{
		int_heading_step_10 += 36;
	}

	x = - (20.0 + mod_heading_step_10) * 0.025;

	//
	// draw heading scale line
	//

	draw_2d_line (-0.25, 0.85, 0.25, 0.85, hud_colour);

	//
	// large and small HUD differences
	//

	get_2d_float_screen_coordinates (0.0, 0.85, &i, &j);

	if (draw_large_hud)
	{
		set_mono_font_type (MONO_FONT_TYPE_7X12);

		draw_2d_mono_sprite(large_hud_heading_carat, 0.0, 0.85, hud_colour);
	}
	else
	{
		set_mono_font_type (MONO_FONT_TYPE_5X7);

		draw_2d_mono_sprite(small_hud_heading_carat, 0.0, 0.85, hud_colour);
	}

	//
	// draw heading scale ticks and heading value
	//

	for (loop = 0; loop < 5; loop++)
	{
		//
		// major tick every 10 degrees
		//

		if (x >= -0.25)
			draw_2d_line (x, 0.9, x, 0.85, hud_colour);

		//
		// minor tick every 5 degrees
		//

		if (x + 0.125 >= -0.25 && x + 0.125 < 0.25)
			draw_2d_line (x + 0.125, 0.85, x + 0.125, 0.875, hud_colour);

		//
		// heading value ('0' displayed as '36')
		//

		if (int_heading_step_10 != 0)
		{
			sprintf (s, "%02d", int_heading_step_10);
		}
		else
		{
			sprintf (s, "36");
		}

		set_2d_mono_font_position (x, 0.9);

		width = get_mono_font_string_width (s);

		if (draw_large_hud)
		{
			set_mono_font_rel_position ((-width * 0.5) + 1.0, -8.0);
		}
		else
		{
			set_mono_font_rel_position ((-width * 0.5) + 1.0, -6.0);
		}

		if (x >= -0.25)
			print_mono_font_string (s);

		//
		// next heading value
		//

		int_heading_step_10++;

		if (int_heading_step_10 == 36)
		{
			int_heading_step_10 = 0;
		}

		x += 0.25;
		if (x > 0.25)
			break;
	}

	//
	// draw command heading carat
	//

	if (!havoc_damage.navigation_computer)
	{
		entity
			*wp;

		wp = get_local_entity_current_waypoint (get_gunship_entity ());

		if (wp)
		{
			vec3d
				*gunship_position,
				waypoint_position;

			float
				dx,
				dz,
				bearing,
				command_heading;

			gunship_position = get_local_entity_vec3d_ptr (get_gunship_entity (), VEC3D_TYPE_POSITION);

			get_waypoint_display_position (get_gunship_entity (), wp, &waypoint_position);

			dx = waypoint_position.x - gunship_position->x;
			dz = waypoint_position.z - gunship_position->z;

			bearing = atan2 (dx, dz);

			heading = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_HEADING);

			command_heading = bearing - heading;

			if (command_heading > rad (180.0))
				command_heading -= rad (360.0);
			else if (command_heading < rad (-180.0))
				command_heading += rad (360.0);

			command_heading = bound (command_heading, rad (-90.0), rad (90.0));

			if (draw_large_hud)
				draw_2d_mono_sprite (large_hud_command_heading_carat, command_heading * ((0.25 - 0.04) / rad (90.0)), 0.85, hud_colour);
			else
				draw_2d_mono_sprite (small_hud_command_heading_carat, command_heading * ((0.25 - 0.04) / rad (90.0)), 0.85, hud_colour);
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

static void draw_velocity_vector(void)
{
#define VV_CUTOFF_VELOCITY kilometres_per_hour_to_metres_per_second(50.0)
	float scale, x, z;
	
	z = current_flight_dynamics->velocity_z.value;
	x = current_flight_dynamics->velocity_x.value;

	// cutoff the velocity marker if it gets too far from center
	if (fabs(z) > VV_CUTOFF_VELOCITY)
	{
		x *= VV_CUTOFF_VELOCITY / fabs(z);
		z = bound(z, -VV_CUTOFF_VELOCITY, VV_CUTOFF_VELOCITY);
	}
	if (fabs(x) > VV_CUTOFF_VELOCITY)
	{
		z *= VV_CUTOFF_VELOCITY / fabs(x);
		x = bound(x, -VV_CUTOFF_VELOCITY, VV_CUTOFF_VELOCITY);
	}

	// from center use 50% of the hud area
	scale = (0.5 / VV_CUTOFF_VELOCITY);

	x *= scale;
	z *= scale;

	draw_line_func(0.0, 0.0, x, z, hud_colour);
}

static void draw_velocity_scale(airspeed)
{
	float y_offset = bound(airspeed, 0.0, 500.0) * 0.0014;
	
	draw_2d_line(-0.55, 0.1, -0.55, 0.8, hud_colour);
	
	draw_2d_line(-0.55, 0.1, -0.575, 0.1, hud_colour);
	draw_2d_line(-0.55, 0.24, -0.575, 0.24, hud_colour);
	draw_2d_line(-0.55, 0.38, -0.575, 0.38, hud_colour);
	draw_2d_line(-0.55, 0.52, -0.575, 0.52, hud_colour);
	draw_2d_line(-0.55, 0.66, -0.575, 0.66, hud_colour);
	draw_2d_line(-0.55, 0.80, -0.575, 0.80, hud_colour);

	draw_2d_line(-0.55, 0.54, -0.525, 0.54, hud_colour);

	if (draw_large_hud)
	{
		set_mono_font_type(MONO_FONT_TYPE_6X10);
		set_mono_font_rel_position (0.0, -1.0);
	}
	else
	{
		set_mono_font_type(MONO_FONT_TYPE_3X6);
		set_mono_font_rel_position (-5.0, -1.0);
	}

	set_2d_mono_font_position(-0.75, 0.8);

	print_mono_font_string("500");
	
	if (draw_large_hud)
		draw_2d_mono_sprite(large_left_carat, -0.55, 0.1 + y_offset, hud_colour);
	else
		draw_2d_mono_sprite(small_left_carat, -0.55, 0.1 + y_offset, hud_colour);
}

static void display_true_airspeed (void)
{
	float
		true_airspeed;

	char
		s[20];

	true_airspeed = current_flight_dynamics->velocity_z.value;

	true_airspeed = kilometres_per_hour (true_airspeed);

	sprintf (s, "%03d", abs((int) true_airspeed));

	if (true_airspeed <= 50.0 || hud_mode != HUD_MODE_WEAPON)
	{
		if (draw_large_hud)
		{
			set_mono_font_type (MONO_FONT_TYPE_8X14);
			set_2d_mono_font_position (-0.9, 0.95);
			set_mono_font_rel_position (5.0, -4.0);
	
			if (true_airspeed >= 0.0)
				print_mono_font_string("+");
			else
				print_mono_font_string("-");
	
			set_mono_font_type (MONO_FONT_TYPE_10X16);
			set_2d_mono_font_position (-0.8, 0.95);
			set_mono_font_rel_position (0.0, -4.0);
			print_mono_font_string (s);
		}
		else
		{
			set_mono_font_type (MONO_FONT_TYPE_5X7);
			set_2d_mono_font_position (-0.9, 0.9);
			set_mono_font_rel_position (3.0, -4.0);
	
			if (true_airspeed >= 0.0)
				print_mono_font_string("+");
			else
				print_mono_font_string("-");
	
			set_mono_font_type (MONO_FONT_TYPE_6X10);
			set_2d_mono_font_position (-0.75, 0.9);
			set_mono_font_rel_position (0.0, -5.0);
			print_mono_font_string (s);
		}
	}

	if (true_airspeed <= 50.0)
		draw_velocity_vector();
	else
		draw_velocity_scale(true_airspeed);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_pitch_scale (void)
{
	float
		pitch,
		roll,
		mod_pitch_step_10,
		y,
		width;

	int
		loop,
		int_pitch_step_10;

	char
		s[20];

	roll = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_ROLL);
	pitch = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_PITCH);
	pitch = deg(pitch);

	mod_pitch_step_10 = fmod (pitch, 10.0);

	int_pitch_step_10 = ((int)(pitch * 0.1)) * 10;
	int_pitch_step_10 -= 30;

	y = - (30.0 + mod_pitch_step_10) * 0.04;


	//
	// draw pitch scale ticks and pitch value
	//

	for (loop = 0; loop < 6; loop++)
	{
		//
		// major tick every 10 degrees
		//

		if (y >= -0.6)
		{
			if (int_pitch_step_10 != 0)
			{
				int pnum;
				
				draw_line_func (-0.22, y, -0.07, y, hud_colour);
				draw_line_func (0.07, y, 0.22, y, hud_colour);
				
				if (draw_large_hud)
					set_mono_font_type (MONO_FONT_TYPE_6X10);
				else
					set_mono_font_type (MONO_FONT_TYPE_3X6);
				set_2d_mono_font_position (0.0, y);
		
				pnum = abs(int_pitch_step_10);
				if (pnum > 90)
					pnum = 180 - pnum;
				sprintf(s, "%2d", pnum);
				width = get_mono_font_string_width(s);
		
				if (draw_large_hud)
					set_mono_font_rel_position ((-width * 0.5), -4.0);
				else
					set_mono_font_rel_position ((-width * 0.5), -2.0);
		
				print_mono_font_string (s);
			}
			else
				draw_line_func(0.005, y, 0.005, y, hud_colour);
		}

		//
		// minor tick every 5 degrees
		//

		if (y + 0.2 < 0.6 && y + 0.2 >= -0.6)
			draw_line_func(-0.05, y + 0.2, 0.05, y + 0.2, hud_colour);


		//
		// next pitch value
		//

		int_pitch_step_10 += 10;
		y += 0.4;
		
		if (y > 0.6)
			break;
	}
	
	// draw datum
	set_2d_instance_rotation (hud_env, -roll);
	
	draw_line_func(-0.2, 0.0, -0.08, 0.0, hud_colour);
	draw_line_func(-0.08, 0.0, -0.08, -0.04, hud_colour);
	draw_line_func(-0.08, -0.04, -0.04, -0.08, hud_colour);
	draw_line_func(-0.04, -0.08, 0.04, -0.08, hud_colour);
	draw_line_func(0.08, -0.04, 0.04, -0.08, hud_colour);
	draw_line_func(0.08, 0.0, 0.08, -0.04, hud_colour);
	draw_line_func(0.2, 0.0, 0.08, 0.0, hud_colour);
	
	reset_2d_instance (hud_env);
	
	// draw bank angle marks
	draw_2d_line(0.35, 0.0, 0.45, 0.0, hud_colour);
	draw_2d_line(-0.35, 0.0, -0.45, 0.0, hud_colour);
	
	draw_2d_line(0.303, -0.175, 0.390, -0.225, hud_colour);
	draw_2d_line(-0.303, -0.175, -0.390, -0.225, hud_colour);
	draw_2d_line(0.175, -0.303, 0.225, -0.390, hud_colour);
	draw_2d_line(-0.175, -0.303, -0.225, -0.390, hud_colour);

	// reset view
	reset_2d_instance (hud_env);
	set_2d_window (hud_env, HUD_WINDOW_X_MIN, HUD_WINDOW_Y_MIN, HUD_WINDOW_X_MAX, HUD_WINDOW_Y_MAX);
	set_2d_viewport (hud_env, hud_viewport_x_min, hud_viewport_y_min, hud_viewport_x_max, hud_viewport_y_max);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_altitude_scale(float altitude)
{
	float y_offset = altitude * 0.016;
	
	draw_2d_line(0.55, 0.0, 0.55, 0.8, hud_colour);
	
	// the vertical tick marks
	draw_2d_line(0.525, 0.0, 0.575, 0.0, hud_colour);
	draw_2d_line(0.55, 0.16, 0.575, 0.16, hud_colour);
	draw_2d_line(0.55, 0.32, 0.575, 0.32, hud_colour);
	draw_2d_line(0.55, 0.48, 0.575, 0.48, hud_colour);
	draw_2d_line(0.55, 0.64, 0.575, 0.64, hud_colour);
	draw_2d_line(0.55, 0.80, 0.575, 0.80, hud_colour);
	
	if (draw_large_hud)
		set_mono_font_type(MONO_FONT_TYPE_6X10);
	else
		set_mono_font_type(MONO_FONT_TYPE_5X7);

	set_2d_mono_font_position(0.6, 0.8);
	set_mono_font_rel_position (0.0, -2.0);

	print_mono_font_string("50");
	
	if (draw_large_hud)
		draw_2d_mono_sprite(large_right_carat, 0.55, y_offset, hud_colour);
	else
		draw_2d_mono_sprite(small_right_carat, 0.55, y_offset, hud_colour);
}

static void display_altitude (void)
{
	float altitude = current_flight_dynamics->radar_altitude.value;
	char
		s[20];

	if (altitude < 300.0)
	{
		if (altitude <= 50.0)
			draw_altitude_scale(altitude);
		
		sprintf (s, "%03d", (int) current_flight_dynamics->radar_altitude.value);
		
		if (draw_large_hud)
		{
			set_mono_font_type (MONO_FONT_TYPE_7X12);
			set_2d_mono_font_position (0.87, 0.95);			
		}
		else
		{
			set_mono_font_type (MONO_FONT_TYPE_5X7);
			set_2d_mono_font_position (0.9, 0.95);
		}

		print_mono_font_string("R");
	}
	else
	{
		sprintf (s, "%04d", 10 * (((int)(current_flight_dynamics->barometric_altitude.value + 5.0)) / 10));
	}

	if (draw_large_hud)
	{
		set_mono_font_type (MONO_FONT_TYPE_10X16);
		set_2d_mono_font_position (0.8, 0.95);
		set_mono_font_rel_position (-25.0, -4.0);
	}
	else
	{
		set_mono_font_type (MONO_FONT_TYPE_6X10);
		set_2d_mono_font_position (0.8, 0.9);
		set_mono_font_rel_position (-15.0, -5.0);
	}

	print_mono_font_string (s);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_g_scale(void)
{
	float y_offset = bound(current_flight_dynamics->g_force.value * 0.1, -0.1, 0.35);
	
	draw_2d_line(-0.7, -0.2, -0.7, -0.65, hud_colour);

	draw_2d_line(-0.7, -0.25, -0.725, -0.25, hud_colour);
	draw_2d_line(-0.7, -0.55, -0.725, -0.55, hud_colour);
	draw_2d_line(-0.7, -0.65, -0.725, -0.65, hud_colour);
	
	if (draw_large_hud)
		set_mono_font_type(MONO_FONT_TYPE_6X10);
	else
		set_mono_font_type(MONO_FONT_TYPE_3X6);

	set_2d_mono_font_position(-0.78, -0.25);
	set_mono_font_rel_position (0.0, -3.0);
	print_mono_font_string("3");
	
	set_2d_mono_font_position(-0.78, -0.55);
	set_mono_font_rel_position (0.0, -3.0);
	print_mono_font_string("0");

	set_2d_mono_font_position(-0.78, -0.65);
	set_mono_font_rel_position (0.0, -3.0);
	print_mono_font_string("1");

	if (draw_large_hud)
		draw_2d_mono_sprite(large_left_carat, -0.7, -0.55 + y_offset, hud_colour);
	else
		draw_2d_mono_sprite(small_left_carat, -0.7, -0.55 + y_offset, hud_colour);
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_vertical_velocity(void)
{
	char s[20];
	float vv = kilometres_per_hour(current_flight_dynamics->world_velocity_y.value);
	
	sprintf (s, "%02d", abs((int)vv));;

	set_2d_mono_font_position (0.6, -0.07);
	if (draw_large_hud)
	{
		set_mono_font_type (MONO_FONT_TYPE_8X14);
		set_mono_font_rel_position (5.0, -4.0);
	}
	else
	{
		set_mono_font_type (MONO_FONT_TYPE_5X7);
		set_mono_font_rel_position (0.0, -3.0);
	}

	if (vv >= 0.0)
		print_mono_font_string("+");
	else
		print_mono_font_string("-");

	set_2d_mono_font_position (0.7, -0.07);
	if (draw_large_hud)
	{
		set_mono_font_type (MONO_FONT_TYPE_10X16);
		set_mono_font_rel_position (0.0, -4.0);
	}
	else
	{
		set_mono_font_type (MONO_FONT_TYPE_6X10);
		set_mono_font_rel_position (0.0, -4.0);
	}
	
	print_mono_font_string (s);

	// draw the scale
	if (hud_mode != HUD_MODE_WEAPON)
	{
		float y_offset = vv * 0.01;
		
		draw_2d_line(0.7, -0.2, 0.7, -0.8, hud_colour);

		// the vertical tick marks
		draw_2d_line(0.7, -0.2, 0.725, -0.2, hud_colour);
		draw_2d_line(0.7, -0.3, 0.725, -0.3, hud_colour);
		draw_2d_line(0.7, -0.4, 0.725, -0.4, hud_colour);
		draw_2d_line(0.7, -0.5, 0.75, -0.5, hud_colour);
		draw_2d_line(0.7, -0.6, 0.725, -0.6, hud_colour);
		draw_2d_line(0.7, -0.7, 0.725, -0.7, hud_colour);
		draw_2d_line(0.7, -0.8, 0.725, -0.8, hud_colour);
		
		if (draw_large_hud)
			set_mono_font_type(MONO_FONT_TYPE_6X10);
		else
			set_mono_font_type(MONO_FONT_TYPE_3X6);
			
		set_2d_mono_font_position(0.75, -0.2);
		set_mono_font_rel_position (0.0, -3.0);
		print_mono_font_string("30");
		
		set_2d_mono_font_position(0.75, -0.5);
		set_mono_font_rel_position (0.0, -3.0);
		print_mono_font_string("0");

		set_2d_mono_font_position(0.75, -0.8);
		set_mono_font_rel_position (0.0, -3.0);
		print_mono_font_string("30");

		if (draw_large_hud)
			draw_2d_mono_sprite(large_right_carat, 0.7, -0.5 + bound(y_offset, -0.3, 0.3), hud_colour);
		else
			draw_2d_mono_sprite(small_right_carat, 0.7, -0.5 + bound(y_offset, -0.3, 0.3), hud_colour);
	}
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
			if (!havoc_damage.navigation_computer)
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

		if (!havoc_damage.navigation_computer)
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

static void display_waypoint_information (void)
{
	char
		s[100],
		tag;

	float
		flat_range,
		width;

	entity
		*en,
		*wp;

	vec3d
		*en_position,
		wp_position;

	en = get_gunship_entity ();

	wp = get_local_entity_current_waypoint (en);

	if (wp)
	{
		en_position = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

		get_waypoint_display_position (en, wp, &wp_position);

		if (!havoc_damage.navigation_computer)
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
static void draw_basic_hud(void)
{
	display_altitude();
	display_vertical_velocity();
	display_true_airspeed();
	draw_pitch_scale();
}

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

	draw_rate_of_climb_scale ();

	display_engine_torque ();

	draw_bob_up_overlay ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_havoc_hud (void)
{
	hud_env = create_2d_environment ();

	if (command_line_high_res_hud)
	{
		hud_texture_screen = create_system_texture_screen (HUD_VIEWPORT_LARGE_SIZE, HUD_VIEWPORT_LARGE_SIZE, TEXTURE_INDEX_HVCKPT_HUD_DISPLAY, TEXTURE_TYPE_SINGLEALPHA);
		draw_large_hud = TRUE;
		hud_viewport_size = HUD_VIEWPORT_LARGE_SIZE;
		draw_line_func = draw_2d_half_thick_line;
	}
	else
	{
		hud_texture_screen = create_system_texture_screen (HUD_VIEWPORT_SMALL_SIZE, HUD_VIEWPORT_SMALL_SIZE, TEXTURE_INDEX_HVCKPT_HUD_DISPLAY, TEXTURE_TYPE_SINGLEALPHA);
		draw_large_hud = FALSE;
		hud_viewport_size = HUD_VIEWPORT_SMALL_SIZE;
		draw_line_func = draw_2d_line;
	}

	hud_viewport_x_org = hud_viewport_size / 2;
	hud_viewport_y_org = hud_viewport_size / 2;

	large_hms_texture_screen = create_system_texture_screen (HUD_VIEWPORT_LARGE_SIZE, HUD_VIEWPORT_LARGE_SIZE, LARGE_HMS_TEXTURE_INDEX, TEXTURE_TYPE_SINGLEALPHA);

	set_rgb_colour (clear_hud_colour, 255, 255, 255, 0);

	initialise_hms_gun_pipper ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_havoc_hud (void)
{
	destroy_2d_environment (hud_env);

	destroy_screen (hud_texture_screen);
	destroy_screen (large_hms_texture_screen);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_havoc_hud_on_cockpit (int hud_enlarge)
{
	if (havoc_damage.head_up_display || !electrical_system_active())
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

void draw_havoc_hud_on_texture (void)
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

	{
		// move HUD coordinate system with head movements to simulate the collimation effect (focus on infinity)
		float y_offset, x_offset;
		float head_offset_x = 0.0, head_offset_y = 0.0;

		head_offset_x = getViewpointOffsetX(head_offset_x);
		head_offset_y = getViewpointOffsetY(head_offset_y);
		
		if (get_global_wide_cockpit())
		{
			head_offset_x += wide_cockpit_position[WIDEVIEW_HAVOC_PILOT].x;
			head_offset_y += wide_cockpit_position[WIDEVIEW_HAVOC_PILOT].y + 0.02;
		}

		x_offset = head_offset_x * -HUD_UNIT_RATIO;
		y_offset = head_offset_y * -HUD_UNIT_RATIO;

		set_2d_view_offset(hud_env, x_offset, y_offset);
	}

	//
	// viewport
	//

	hud_viewport_x_min = hud_viewport_x_org - (hud_viewport_size * 0.5);
	hud_viewport_y_min = hud_viewport_y_org - (hud_viewport_size * 0.5);
	hud_viewport_x_max = hud_viewport_x_org + (hud_viewport_size * 0.5) - 0.001;
	hud_viewport_y_max = hud_viewport_y_org + (hud_viewport_size * 0.5) - 0.001;

	set_2d_viewport (hud_env, hud_viewport_x_min, hud_viewport_y_min, hud_viewport_x_max, hud_viewport_y_max);

	//
	// get screen co-ords (vitural cockpit texture - scaling only works near screen centre)
	//

	hud_screen_x_min = full_screen_x_mid - ((hud_viewport_size / (640.0 * 2.0)) * full_screen_width);
	hud_screen_y_min = full_screen_y_mid - ((hud_viewport_size / (480.0 * 2.0)) * full_screen_height);

	hud_screen_x_max = full_screen_x_mid + ((hud_viewport_size / (640.0 * 2.0)) * full_screen_width) - 0.001;
	hud_screen_y_max = full_screen_y_mid + ((hud_viewport_size / (480.0 * 2.0)) * full_screen_height) - 0.001;

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

		set_block (0, 0, hud_viewport_size - 1, hud_viewport_size - 1, clear_hud_colour);

		if (!havoc_damage.head_up_display && electrical_system_active())
		{
			set_mono_font_colour (hud_colour);

			draw_layout_grid ();

			draw_basic_hud();

			switch (hud_mode)
			{
				case HUD_MODE_TRANSITION:				
				case HUD_MODE_NAVIGATION:
				{
					draw_heading_scale();
					display_waypoint_information();
					display_g_scale();
//					draw_navigation_mode_hud (TRUE);

					break;
				}
				case HUD_MODE_WEAPON:
				{
					display_weapon_information();
					display_target_information();
//					draw_weapon_mode_hud (TRUE);

					break;
				}
			}
		}

		flush_screen_texture_graphics (hud_texture_screen);

		unlock_screen (hud_texture_screen);
	}

	set_active_screen (video_screen);

	reset_2d_view_offset(hud_env);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_external_havoc_hud (void)
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

	if (havoc_damage.head_up_display)
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

	hud_viewport_x_org = hud_viewport_size * 0.5;
	hud_viewport_y_org = hud_viewport_size * 0.5;

	hud_viewport_x_min = 0.0;
	hud_viewport_y_min = 0.0;

	hud_viewport_x_max = hud_viewport_size - 0.001;
	hud_viewport_y_max = hud_viewport_size - 0.001;

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

	set_active_screen (hud_texture_screen);

	if (lock_screen (hud_texture_screen))
	{
	 	store_hud_colour = hud_colour;

		set_rgb_colour (hud_colour, 255, 255, 255, 255);

		set_mono_font_colour (hud_colour);

		set_block (0, 0, hud_viewport_size - 1, hud_viewport_size - 1, clear_hud_colour);

		draw_layout_grid ();

		draw_basic_hud();

		switch (hud_mode)
		{
			case HUD_MODE_TRANSITION:				
			case HUD_MODE_NAVIGATION:
			{
				draw_heading_scale();
				display_waypoint_information();
				display_g_scale();

				break;
			}
			case HUD_MODE_WEAPON:
			{
				display_weapon_information();
				display_target_information();

				break;
			}
		}

		hud_colour = store_hud_colour;

		flush_screen_texture_graphics (hud_texture_screen);

		unlock_screen (hud_texture_screen);
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

		set_d3d_flat_shaded_textured_renderstate (get_system_texture_ptr (TEXTURE_INDEX_HVCKPT_HUD_DISPLAY));

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
	if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_HMS)
	{
		draw_2d_circle(0.0, 0.0, 0.3, hud_colour);
		
		if (weapon_lock_type != WEAPON_LOCK_NO_TARGET)
			draw_2d_circle(0.0, 0.0, 0.35, hud_colour);
		if (weapon_lock_type == WEAPON_LOCK_VALID)
		{
			draw_2d_line(0.3, 0.0, 0.4, 0.0, hud_colour);	
			draw_2d_line(0.0, 0.3, 0.0, 0.4, hud_colour);	
			draw_2d_line(-0.3, 0.0, -0.4, 0.0, hud_colour);	
			draw_2d_line(0.0, -0.3, 0.0, -0.4, hud_colour);	
		}
	}
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

static void draw_gun_pipper (float x, float y, float range, float weapon_min_range, float weapon_max_range)
{
	float
		normalised_range,
		theta,
		max_range;

	int
		i,
		i_max;

	if (weapon_max_range > 5000)
		max_range = 10000;
	else if (weapon_max_range > 2500)
		max_range = 5000;
	else
		max_range = 2500;

	normalised_range = range / max_range;

	if (get_range_finder() != RANGEFINDER_TRIANGULATION)
	{
		i_max = (int) (normalised_range * NUM_GUN_PIPPER_POINTS);
	
		i_max = bound (i_max, 0, NUM_GUN_PIPPER_POINTS - 1);
	
		for (i = 0; i <= i_max; i++)
			set_2d_pixel (x + gun_pipper_points[i][0], y + gun_pipper_points[i][1], hud_colour);
	}

	set_2d_instance_position (hud_env, x, y);

	draw_2d_line (0.0, 0.15, 0.0, 0.12, hud_colour);

	theta = weapon_max_range / max_range * -PI2;
	set_2d_instance_rotation (hud_env, theta);
	draw_2d_line (0.0, 0.15, 0.0, 0.12, hud_colour);

	theta = weapon_min_range / max_range * -PI2;
	set_2d_instance_rotation (hud_env, theta);
	draw_2d_line (0.0, 0.15, 0.0, 0.12, hud_colour);

	draw_2d_circle(0.0, 0.0, 0.12, hud_colour);

	reset_2d_instance (hud_env);
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

				source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);
				target_range = get_3d_range (source_position, &target_position);

				draw_gun_pipper (x, y, target_range, weapon_database[selected_weapon_type].min_range, weapon_database[selected_weapon_type].max_range);

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

static void display_weapon_information (void)
{
	entity_sub_types weapon_sub_type;
	char s[80], *weapon_type;

	weapon_sub_type = get_local_entity_int_value (get_gunship_entity (), INT_TYPE_SELECTED_WEAPON);

	if (weapon_sub_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
	{
		int count = get_local_entity_weapon_count (get_gunship_entity (), weapon_sub_type);
		
		if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND
			|| weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND)
		{
			set_mono_font_type (MONO_FONT_TYPE_6X10);
			set_2d_mono_font_position (-0.9, -0.7);
			set_mono_font_rel_position (0.0, 0.0);
			if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND)
				weapon_type = "HE %03d";
			else
				weapon_type = "AP %03d";
		}
		else if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_ATAKA)
		{
			float flight_time = get_hokum_missile_flight_time ();

			if (flight_time > 0.01)
			{
				flight_time = bound (flight_time, 0.0, 99.9);
				sprintf (s, "%02.0f", flight_time);
				set_2d_mono_font_position (-0.5, -0.65);
				set_mono_font_rel_position (1.0, 0.0);
				print_mono_font_string (s);
			}
			weapon_type = "MSL %02d";
		}
		else if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_IGLA_V)
			weapon_type = "ATA %02d";
		else
		{
			float x,y;
			float angle_of_drop = 0.0;
			float head_offset_z = get_global_wide_cockpit() ? wide_cockpit_position[WIDEVIEW_HAVOC_PILOT].z : 0.0;
			float drop_hud_distance;
			float roll = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_ROLL);

			if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND)
				weapon_type = "GUN %03d";
			else
				weapon_type = "RKT %03d";

			angle_of_drop = get_weapon_drop(weapon_sub_type);

			// move eo to hit point
			if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_OFF)
				slew_eo_to_direction(-angle_of_drop, 0.0);

			x = 0.0;
			y = get_global_wide_cockpit() ? 0.26 : 0.0;

			// this magic formula translates the angle to a HUD distance
			// the magic values are just arrived at by measuring in game
			drop_hud_distance = atan(angle_of_drop) * ((head_offset_z * 0.82) + 0.56) * HUD_UNIT_RATIO;
			y -= cos(roll) * drop_hud_distance;
			x += sin(roll) * drop_hud_distance;

			draw_2d_circle(x, y, 0.1, hud_colour);
			set_2d_pixel(x, y, hud_colour); 
		}

		if (draw_large_hud)
			set_mono_font_type (MONO_FONT_TYPE_6X10);
		else
			set_mono_font_type (MONO_FONT_TYPE_3X6);

		set_2d_mono_font_position (-0.85, -0.1);
		set_mono_font_rel_position (0.0, 0.0);
		sprintf(s, weapon_type, count);
		print_mono_font_string (s);
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
		*target,
		*source;

	rangefinding_system
		range_finder = get_range_finder();

	// Range
	source = get_gunship_entity ();
	ASSERT(source);
	target = get_local_entity_parent (source, LIST_TYPE_TARGET);
	if (target && range_finder != RANGEFINDER_TRIANGULATION)
	{
		vec3d *target_position, *source_position;
		float min_weapon_range, max_weapon_range, target_range;
		entity_sub_types selected_weapon_type;


		source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);
		target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);
		target_range = get_3d_range (source_position, target_position);

		if (draw_large_hud)
			set_mono_font_type (MONO_FONT_TYPE_7X12);
		else
			set_mono_font_type (MONO_FONT_TYPE_5X7);

		sprintf (buffer, "%2.1f", target_range * 0.001);
		set_2d_mono_font_position (0.0, -0.65);
		width = get_mono_font_string_width (buffer);
		set_mono_font_rel_position (-width * 0.5, 0.0);
		print_mono_font_string (buffer);

		// min and max range
		selected_weapon_type = get_local_entity_int_value (source, INT_TYPE_SELECTED_WEAPON);

		min_weapon_range = weapon_database[selected_weapon_type].min_range;
		max_weapon_range = weapon_database[selected_weapon_type].max_range;
		
		// flashing X when within minimum range
		if (target_range < min_weapon_range && (get_system_time() % 800) < 400)
		{
			draw_line_func(-0.5, -0.5, 0.5, 0.5, hud_colour);
			draw_line_func(-0.5, 0.5, 0.5, -0.5, hud_colour);
		}
	}

	if (draw_large_hud)
		set_mono_font_type (MONO_FONT_TYPE_6X10);
	else
		set_mono_font_type (MONO_FONT_TYPE_3X6);

	// laser active
	if (laser_is_active())
	{
		set_2d_mono_font_position (-0.8, 0.2);
		set_mono_font_rel_position (0.0, 0.0);
		print_mono_font_string("L");
	}

	if (get_local_entity_int_value(source, INT_TYPE_RADAR_ON))
	{
		set_2d_mono_font_position (-0.8, 0.1);
		set_mono_font_rel_position (0.0, 0.0);
		print_mono_font_string("R");
	}
	

	//
	// weapon lock
	//

	switch (weapon_lock_type)
	{
		case WEAPON_LOCK_NO_ACQUIRE:
			s = "NO ACQ";
			break;
		case WEAPON_LOCK_NO_WEAPON:
			s = "NO WPN";
			break;
		case WEAPON_LOCK_NO_TARGET:
			s = "NO TGT";
			break;
		case WEAPON_LOCK_INVALID_TARGET:
			s = "INV TGT";
			break;
		case WEAPON_LOCK_SEEKER_LIMIT:
			s = "SKR LMT";
			break;
		case WEAPON_LOCK_NO_LOS:
			s = "NO LOS";
			break;
		case WEAPON_LOCK_NO_BORESIGHT:
			s = "NO SGT";
			break;
		case WEAPON_LOCK_MIN_RANGE:
			if (range_finder != RANGEFINDER_TRIANGULATION)
			{
				s = "MIN RNG";
				break;
			}
			// fallthrough
		case WEAPON_LOCK_MAX_RANGE:
			if (range_finder != RANGEFINDER_TRIANGULATION)
			{
				s = "MAX RNG";
				break;
			}
			// fallthrough
		case WEAPON_LOCK_VALID:
			s = "LOCK";
			break;
		default:
			debug_fatal ("Invalid weapon lock type = %d", weapon_lock_type);
			break;
	}

	width = get_mono_font_string_width (s);
	set_2d_mono_font_position (-0.9, -0.2);
	set_mono_font_rel_position (0.0, 0.0);
	print_mono_font_string (s);

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
			set_2d_mono_font_position (0.0, -0.75);
			set_mono_font_rel_position (-width * 0.5, 0.0);
			print_mono_font_string (s);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_havoc_hms (void)
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

	if (havoc_damage.helmet_mounted_sight || !electrical_system_active())
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
				heading_offset = HAVOC_INSTRUMENT_VIEW_HEADING - pilot_head_heading;

				if (heading_offset < 0.0)
				{
					heading_offset = -heading_offset;
				}

				pitch_offset = HAVOC_INSTRUMENT_VIEW_PITCH - pilot_head_pitch;

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
				if ((pilot_head_heading == HAVOC_INSTRUMENT_VIEW_HEADING) && (pilot_head_pitch == HAVOC_INSTRUMENT_VIEW_PITCH))
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

//		draw_target_range_indicator ();

//		display_weapon_information ();

//		display_target_information ();

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
