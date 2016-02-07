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

#ifndef OGRE_EE
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

//
// HUD screen co-ords
//

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

static screen
	*hud_texture_screen = NULL,
	*outside_hud_texture_screen;

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

#define HUD_UNIT_RATIO 12.05    // ratio of HUD size with distance to HUD

static void (*draw_line_func)(float, float, float, float, const rgb_colour) = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * unfinshed code, it doesn't quite work satisfactory yet
static void transform_position_to_hud_coordinate(vec3d* position, float* x, float* y)
{
	float one_over_range;
	float x_factor = 7.9, y_factor = 7.9;
	char s[80];

	float head_offset_z = get_global_wide_cockpit() ? wide_cockpit_position[WIDEVIEW_HOKUM_PILOT].c.z : 0.0;

	if (command_line_TIR_6DOF && query_TIR_active())
		head_offset_z = getViewpointOffsetZ(1);

	if (position->z > 0.0)
		one_over_range = 1.0 / position->z;
	else
		one_over_range = 1.0;

	*x = position->x * one_over_range * x_factor;
	*y = position->y * one_over_range * y_factor;

	// compensate for distance of head to HUD
	*x *= (head_offset_z + 1.1);
	*y *= (head_offset_z + 1.1);

	// compensate for straight ahead not being in the middle of the HUD
	*y += 0.36;

	sprintf (s, "%6.4f %6.4f %6.4f", *x, *y, one_over_range);
	set_2d_mono_font_position (-0.9, -0.5);
	set_mono_font_rel_position (0.0, 0.0);
	print_mono_font_string (s);
}
*/

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

	mod_pitch_step_10 = fmod (pitch, 10.0f);

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

	mod_heading_step_10 = fmod (heading, 10.0f);

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

	if (!hokum_damage.navigation_computer)
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

static void draw_velocity_scale(float airspeed)
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

		if (!hokum_damage.navigation_computer)
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

static void draw_basic_hud(void)
{
	display_altitude();
	display_vertical_velocity();
	display_true_airspeed();
	draw_pitch_scale();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

void initialise_hokum_hud (void)
{
#ifndef OGRE_EE
	hud_env = create_2d_environment ();

	outside_hud_texture_screen = create_system_texture_screen (HUD_VIEWPORT_LARGE_SIZE, HUD_VIEWPORT_LARGE_SIZE, TEXTURE_INDEX_AVCKPT_DISPLAY_LHS_MFD, TEXTURE_TYPE_SINGLEALPHA);

	if (command_line_high_res_hud)
		hud_texture_screen = create_system_texture_screen (HUD_VIEWPORT_LARGE_SIZE, HUD_VIEWPORT_LARGE_SIZE, TEXTURE_INDEX_HOKUM_COCKPIT_HUD, TEXTURE_TYPE_SINGLEALPHA);
	else
		hud_texture_screen = create_system_texture_screen (HUD_VIEWPORT_SMALL_SIZE, HUD_VIEWPORT_SMALL_SIZE, TEXTURE_INDEX_HOKUM_COCKPIT_HUD, TEXTURE_TYPE_SINGLEALPHA);

	set_rgb_colour (clear_hud_colour, 255, 255, 255, 0);

	initialise_hms_gun_pipper ();
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_hokum_hud (void)
{
#ifndef OGRE_EE
	destroy_2d_environment (hud_env);

	destroy_screen (outside_hud_texture_screen);

	destroy_screen (hud_texture_screen);
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_hokum_hud (void)
{
#ifndef OGRE_EE
	int
		draw_hud_on_glass;

	////////////////////////////////////////
	//
	// if viewing from the pilot's head then draw a 'projected'
	// HUD else draw the HUD actually on the glass for effect
	//
	////////////////////////////////////////

	{
		object_3d_sub_object_search_data
			search;

		draw_hud_on_glass = TRUE;

		if (get_crew_role () == CREW_ROLE_PILOT)
		{
			if
			(
				(get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT) ||
				(get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_PADLOCK) ||
				(get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_TRACK_TARGET) ||
				(get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_HUD)
			)
			{
				draw_hud_on_glass = FALSE;
			}
		}

		search.search_depth = 0;
		search.search_object = virtual_cockpit_inst3d;
		search.sub_object_index = OBJECT_3D_SUB_OBJECT_HAVOC_COCKPIT_HUD_DISPLAY;

		if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			search.result_sub_object->visible_object = !draw_hud_on_glass;
		}

		search.search_depth = 0;
		search.search_object = virtual_cockpit_inst3d;
		search.sub_object_index = OBJECT_3D_SUB_OBJECT_HAVOC_COCKPIT_HUD_EFFECT;

		if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			search.result_sub_object->visible_object = draw_hud_on_glass;
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
	draw_large_hud = FALSE;

	if (!draw_hud_on_glass)
	{
		// move HUD coordinate system with head movements to simulate the collimation effect (focus on infinity)
		float y_offset, x_offset;
		float head_offset_x = 0.0, head_offset_y = 0.0;

		head_offset_x = getViewpointOffsetX(head_offset_x);
		head_offset_y = getViewpointOffsetY(head_offset_y);

		if (get_global_wide_cockpit())
		{
			head_offset_x += wide_cockpit_position[WIDEVIEW_HOKUM_PILOT].c.x;
			head_offset_y += wide_cockpit_position[WIDEVIEW_HOKUM_PILOT].c.y - 0.04;
		}

		x_offset = head_offset_x * -HUD_UNIT_RATIO;
		y_offset = head_offset_y * -HUD_UNIT_RATIO;

		set_2d_view_offset(hud_env, x_offset, y_offset);
	}
	else
		reset_2d_view_offset(hud_env);

	ASSERT(hud_texture_screen);
	if (command_line_high_res_hud)
	{
		hud_viewport_size = HUD_VIEWPORT_LARGE_SIZE;
		draw_large_hud = TRUE;
		draw_line_func = draw_2d_half_thick_line;
	}
	else
	{
		hud_viewport_size = HUD_VIEWPORT_SMALL_SIZE;
		draw_large_hud = FALSE;
		draw_line_func = draw_2d_line;
	}

	hud_viewport_x_org = hud_viewport_size * 0.5;

	hud_viewport_y_org = hud_viewport_size * 0.5;

	hud_viewport_x_min = 0.0;

	hud_viewport_y_min = 0.0;

	hud_viewport_x_max = hud_viewport_size;

	hud_viewport_y_max = hud_viewport_size;

	set_2d_viewport (hud_env, hud_viewport_x_min, hud_viewport_y_min, hud_viewport_x_max, hud_viewport_y_max);

	//
	// get screen co-ords (this HUD texture is in the virtual cockpit and will scale itself)
	//

	hud_screen_x_min = 0.0;
	hud_screen_y_min = 0.0;

	hud_screen_x_max = hud_viewport_size;
	hud_screen_y_max = hud_viewport_size;

	hud_screen_x_scale = 1.0;
	hud_screen_y_scale = 1.0;

	////////////////////////////////////////
	//
	// draw HUD on texture
	//
	////////////////////////////////////////

	set_active_screen (hud_texture_screen);

	if (lock_screen (hud_texture_screen))
	{
		rgb_colour
			clear_hud_colour;

		set_rgb_colour (clear_hud_colour, hud_colour.r, hud_colour.g, hud_colour.b, 0);

		set_block (0, 0, hud_viewport_size - 1, hud_viewport_size - 1, clear_hud_colour);

		if (!draw_hud_on_glass && !hokum_damage.head_up_display && electrical_system_active())
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

					break;
				}
				case HUD_MODE_WEAPON:
				{
					display_weapon_information();
					display_target_information();

//					draw_target_marker();
//					draw_navigation_mode_hud ();
//					draw_weapon_mode_hud ();

					break;
				}
			}
		}

		unlock_screen (hud_texture_screen);
	}

	reset_2d_view_offset(hud_env);

	set_active_screen (video_screen);
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_external_hokum_hud (void)
{
#ifndef OGRE_EE
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

	if (hokum_damage.head_up_display)
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
	draw_line_func = draw_2d_half_thick_line;

	hud_viewport_size = HUD_VIEWPORT_LARGE_SIZE;

	hud_viewport_x_org = HUD_VIEWPORT_LARGE_SIZE * 0.5;

	hud_viewport_y_org = HUD_VIEWPORT_LARGE_SIZE * 0.5;

	hud_viewport_x_min = 0.0;

	hud_viewport_y_min = 0.0;

	hud_viewport_x_max = HUD_VIEWPORT_LARGE_SIZE;

	hud_viewport_y_max = HUD_VIEWPORT_LARGE_SIZE;

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

		hud_screen_x_max = full_screen_x_mid + ((256.0 / (640.0 * 2.0)) * full_screen_width);
		hud_screen_y_max = full_screen_y_mid + ((256.0 / (480.0 * 2.0)) * full_screen_height);

		hud_screen_x_scale = 640.0 / full_screen_width;
		hud_screen_y_scale = 480.0 / full_screen_height;
	}

	////////////////////////////////////////
	//
	// draw HUD on texture
	//
	////////////////////////////////////////

	set_active_screen (outside_hud_texture_screen);

	if (lock_screen (outside_hud_texture_screen))
	{
	 	store_hud_colour = hud_colour;

		set_rgb_colour (hud_colour, 255, 255, 255, 255);

		set_mono_font_colour (hud_colour);

		set_block (0, 0, HUD_VIEWPORT_LARGE_SIZE - 1, HUD_VIEWPORT_LARGE_SIZE - 1, clear_hud_colour);

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

		unlock_screen (outside_hud_texture_screen);
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

		set_d3d_flat_shaded_textured_renderstate (get_system_texture_ptr (TEXTURE_INDEX_AVCKPT_DISPLAY_LHS_MFD));

		////////////////////////////////////////
		//

		colour.red				= hud_colour_table[get_global_hud_colour ()].r;
		colour.green			= hud_colour_table[get_global_hud_colour ()].g;
		colour.blue				= hud_colour_table[get_global_hud_colour ()].b;
		colour.alpha			= 255;

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

		quad[0].next_vertex 	= &quad[1];
		quad[1].next_vertex 	= &quad[2];
		quad[2].next_vertex 	= &quad[3];
		quad[3].next_vertex 	= NULL;

		//
		////////////////////////////////////////

		draw_wbuffered_flat_shaded_textured_polygon (quad, colour, specular);

		set_d3d_transparency_off ();

		set_d3d_zbuffer_comparison (TRUE);

		set_d3d_culling (TRUE);

		end_3d_scene ();
	}
#endif
}

#ifndef OGRE_EE
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
/*	vec3d
		*source_position,
		position;

	object_3d_visibility
		visibility;

	int
		angle;

	float
		i,
		j,
		x,
		y;

	float pitch = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_PITCH);

	source_position = get_local_entity_vec3d_ptr (get_gunship_entity(), VEC3D_TYPE_POSITION);
	for (angle = -5; angle <= 5; angle++)
	{
		float dist = 1000.0;
		float heading = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_HEADING);
		rgb_colour c;

		if (angle == 0)
			c = sys_col_red;
		else
		{
			c.r = 255;
			c.g = 255;
			c.b = 0;
			c.a = 255;
		}

		position.x = source_position->x + dist * sin(heading);
		position.y = source_position->y + dist * atan(rad(angle) + pitch);
		position.z = source_position->z + dist * cos(heading);

		visibility = get_position_3d_screen_coordinates (&position, &i, &j);
		if ((visibility == OBJECT_3D_COMPLETELY_VISIBLE) || (visibility == OBJECT_3D_PARTIALLY_VISIBLE))
		{
			transform_hud_screen_co_ords_to_hud_texture_co_ords (&i, &j);
			get_2d_world_position (i, j, &x, &y);
//			clip_2d_point_to_hud_extent (&x, &y);

			draw_2d_line(-1.0, y, 1.0, y, c);
		}
	}
	draw_2d_line(x, 1.0, x, -1.0, sys_col_red);
	*/
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
		theta,
		max_range;

	if (weapon_max_range > 5000)
		max_range = 10000;
	else if (weapon_max_range > 2500)
		max_range = 5000;
	else
		max_range = 2500;

	if (get_range_finder() != RANGEFINDER_TRIANGULATION)
	{
		int i, i_max;
		float normalised_range = range / max_range;

		i_max = (int) (normalised_range * NUM_GUN_PIPPER_POINTS);

		i_max = bound (i_max, 0, NUM_GUN_PIPPER_POINTS - 1);

		for (i = 0; i <= i_max; i++)
		{
			set_2d_pixel (x + gun_pipper_points[i][0], y + gun_pipper_points[i][1], hud_colour);
		}
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
		airborne_target = FALSE;

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
		vec3d* tracking_point = get_eo_tracking_point();
		target = get_local_entity_parent (source, LIST_TYPE_TARGET);

		if (target || tracking_point)
		{
			if (tracking_point)
				target_position = *tracking_point;
			else
			{
				get_local_entity_target_point (target, &target_position);
				airborne_target = get_local_entity_int_value (target, INT_TYPE_AIRBORNE_AIRCRAFT);
			}

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
		if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND
			|| weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND)
		{
			float head_offset_z = get_global_wide_cockpit() ? wide_cockpit_position[WIDEVIEW_HOKUM_PILOT].c.z : 0.0;
			float left_limit, right_limit, upper_limit;

			if (command_line_TIR_6DOF && query_TIR_active())
				head_offset_z = getViewpointOffsetZ(1);

			// adjust box for head position
			left_limit = atan(rad(-1.0)) * (head_offset_z + 1.1) * HUD_UNIT_RATIO;
			right_limit = atan(rad(6.0)) * (head_offset_z + 1.1) * HUD_UNIT_RATIO;
			upper_limit = atan(rad(3.0)) * (head_offset_z + 1.1) * HUD_UNIT_RATIO;

			draw_2d_line(left_limit, -1.0, left_limit, upper_limit, hud_colour);
			draw_2d_line(right_limit, -1.0, right_limit, upper_limit, hud_colour);
			draw_2d_line(left_limit, upper_limit, right_limit, upper_limit, hud_colour);

			set_mono_font_type (MONO_FONT_TYPE_6X10);
			set_2d_mono_font_position (-0.9, -0.7);
			set_mono_font_rel_position (0.0, 0.0);
			if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND)
				weapon_type = "HE";
			else
				weapon_type = "AP";
		}
		else if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_9K121_VIKHR)
		{
			float flight_time = get_missile_flight_time ();
//			debug_log("ft: %.1f", flight_time);

			if (flight_time > 0.01)
			{
				flight_time = bound (flight_time, 0.0, 99.9);
				sprintf (s, "%02.0f", flight_time);
				set_2d_mono_font_position (-0.5, -0.65);
				set_mono_font_rel_position (1.0, 0.0);
				print_mono_font_string (s);
			}
			weapon_type = "MSL";
		}
		else if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_9M39_IGLA_V)
			weapon_type = "ATA";
		else
		{
			float x,y;
			float angle_of_drop = 0.0;
			float head_offset_z = get_global_wide_cockpit() ? wide_cockpit_position[WIDEVIEW_HOKUM_PILOT].c.z : 0.0;
			float drop_hud_distance;
			float roll = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_ROLL);

			if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND)
				weapon_type = "GUN";
			else
				weapon_type = "RKT";

			angle_of_drop = get_weapon_drop(weapon_sub_type);

			// move eo to hit point
			if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_OFF)
				slew_eo_to_direction(-angle_of_drop, 0.0);

			x = 0.0;
			y = get_global_wide_cockpit() ? 0.38 : 0.80;

			// this magic formula translates the angle to a HUD distance
			// the magic values are just arrived at by measuring in game
			drop_hud_distance = atan(angle_of_drop) * ((head_offset_z * 0.84) + 0.66) * HUD_UNIT_RATIO;
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
		print_mono_font_string (weapon_type);
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

	int has_range = get_range_finder() != RANGEFINDER_TRIANGULATION;

	if (draw_large_hud)
		set_mono_font_type (MONO_FONT_TYPE_7X12);
	else
		set_mono_font_type (MONO_FONT_TYPE_5X7);

	// Range
	source = get_gunship_entity ();
	ASSERT(source);
	target = get_local_entity_parent (source, LIST_TYPE_TARGET);
	if (target || eo_is_tracking_point())
	{
		float min_weapon_range, max_weapon_range, target_range;
		entity_sub_types selected_weapon_type;

		if (has_range)
		{
			vec3d *target_position, *source_position;

			source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);
			target_position = get_eo_tracking_point();
			if (!target_position)
				target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

			target_range = get_3d_range (source_position, target_position);
		}

		if (has_range)
		{
			sprintf (buffer, "%2.1f", target_range * 0.001);
			set_2d_mono_font_position (0.0, -0.65);
			width = get_mono_font_string_width (buffer);
			set_mono_font_rel_position (-width * 0.5, 0.0);
			print_mono_font_string (buffer);
		}

		// min and max range
		selected_weapon_type = get_local_entity_int_value (source, INT_TYPE_SELECTED_WEAPON);

		min_weapon_range = weapon_database[selected_weapon_type].min_range;
		max_weapon_range = weapon_database[selected_weapon_type].max_range;

		// flashing X when within minimum range
		if (has_range && target_range < min_weapon_range && (get_system_time() % 800) < 400)
		{
			draw_line_func(-0.5, -0.5, 0.5, 0.5, hud_colour);
			draw_line_func(-0.5, 0.5, 0.5, -0.5, hud_colour);
		}
	}

	//
	// weapon lock
	//

	if (draw_large_hud)
		set_mono_font_type (MONO_FONT_TYPE_6X10);
	else
		set_mono_font_type (MONO_FONT_TYPE_3X6);

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
			if (has_range)
			{
				s = "MIN RNG";
				break;
			}
		case WEAPON_LOCK_MAX_RANGE:
			if (has_range)
			{
				s = "MAX RNG";
				break;
			}
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

	// laser and radar indicators
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
	// target name
	//

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
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_hokum_hms (void)
{
#ifndef OGRE_EE
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

	if (hokum_damage.helmet_mounted_sight || !electrical_system_active())
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
			{
				heading_offset = HOKUM_INSTRUMENT_VIEW_HEADING - pilot_head_heading;

				if (heading_offset < 0.0)
				{
					heading_offset = -heading_offset;
				}

				pitch_offset = HOKUM_INSTRUMENT_VIEW_PITCH - pilot_head_pitch;

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

	hud_viewport_x_max = HUD_VIEWPORT_LARGE_SIZE;

	hud_viewport_y_max = HUD_VIEWPORT_LARGE_SIZE;

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

		hud_screen_x_max = full_screen_x_mid + ((256.0 / (640.0 * 2.0)) * full_screen_width);
		hud_screen_y_max = full_screen_y_mid + ((256.0 / (480.0 * 2.0)) * full_screen_height);

		hud_screen_x_scale = 640.0 / full_screen_width;
		hud_screen_y_scale = 480.0 / full_screen_height;
	}

	////////////////////////////////////////
	//
	// draw HUD on texture
	//
	////////////////////////////////////////

	set_active_screen (outside_hud_texture_screen);

	if (lock_screen (outside_hud_texture_screen))
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

		unlock_screen (outside_hud_texture_screen);
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

		set_d3d_flat_shaded_textured_renderstate (get_system_texture_ptr (TEXTURE_INDEX_AVCKPT_DISPLAY_LHS_MFD));

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
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
