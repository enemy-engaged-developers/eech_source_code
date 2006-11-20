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

////////////////////////////////////////
//
// main 2D environment
//
////////////////////////////////////////

#define HUD_WINDOW_X_MIN	(-1.0)
#define HUD_WINDOW_Y_MIN	(-1.0)
#define HUD_WINDOW_X_MAX	(0.999)
#define HUD_WINDOW_Y_MAX	(0.999)

#define HUD_VIEWPORT_SIZE	(256)

static env_2d
	*hud_env;

static float
//VJ 050126 hud mod start
	hud_viewport_size,
//VJ 050126 hud mod end
	hud_viewport_x_org,
	hud_viewport_y_org,
	hud_viewport_x_min,
	hud_viewport_y_min,
	hud_viewport_x_max,
	hud_viewport_y_max,
	hdg_viewport_x_min,
	hdg_viewport_y_min,
	hdg_viewport_x_max,
	hdg_viewport_y_max,
	bank_scale_viewport_x_min,
	bank_scale_viewport_y_min,
	bank_scale_viewport_x_max,
	bank_scale_viewport_y_max;

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

#define HUD_TEXTURE_INDEX (TEXTURE_INDEX_COMANCHE_MFD2)

static screen
	*hud_texture_screen;

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

//
// adjust 2D environment for heading scale clipping
//

#define HDG_WIDTH_RATIO			(0.6)

#define HDG_WINDOW_X_MIN		(HUD_WINDOW_X_MIN * HDG_WIDTH_RATIO)
#define HDG_WINDOW_Y_MIN		(HUD_WINDOW_Y_MIN)
#define HDG_WINDOW_X_MAX		(HUD_WINDOW_X_MAX * HDG_WIDTH_RATIO)
#define HDG_WINDOW_Y_MAX		(HUD_WINDOW_Y_MAX)

#define HDG_WINDOW_X_ORG		(0.0)
#define HDG_WINDOW_Y_ORG		(0.9)  //VJ 050126 hud mod size, was (0.93)

//
// draw heading tape ticks +/-90 degs of centre (plus an extra bit to keep three cardinal points visible (N,S,E,W))
//

#define HDG_TICK_X_SPACING			(HDG_WIDTH_RATIO / 9.5)

#define HDG_TICK_10_DEG_TOP		(HDG_WINDOW_Y_ORG - 0.015)
#define HDG_TICK_10_DEG_BOTTOM	(HDG_TICK_10_DEG_TOP - 0.045)

#define HDG_TICK_30_DEG_TOP		(HDG_WINDOW_Y_ORG)
#define HDG_TICK_30_DEG_BOTTOM	(HDG_TICK_30_DEG_TOP - 0.075)

#define HDG_TICK_DATUM_TOP			(HDG_TICK_30_DEG_BOTTOM - 0.010)
#define HDG_TICK_DATUM_BOTTOM		(HDG_TICK_DATUM_TOP - 0.045)

//
// character position adjust
//

#define HDG_CHAR_ADJUST_SINGLE	(-2.0)
#define HDG_CHAR_ADJUST_DOUBLE	(-5.0)
#define HDG_CHAR_Y_ADJUST			(-8.0)

//
// command heading carat
//

#define HDG_CARAT_FSD	(HDG_WIDTH_RATIO - 0.05)

static char command_heading_carat[] =
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

//
// radar sweep indicator
//

#define RADAR_SWEEP_INDICATOR_FSD	(HDG_WIDTH_RATIO - 0.04)

static char radar_sweep_indicator[] =
{
	11,
	7,
	-5,
	0,
	0,0,1,1,0,0,0,1,1,0,0,
	0,1,1,1,0,0,0,1,1,1,0,
	1,1,1,1,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,1,1,1,1,
	0,1,1,1,0,0,0,1,1,1,0,
	0,0,1,1,0,0,0,1,1,0,0,
};

//
// bob-up command heading carat
//

#define BOB_UP_HDG_CARAT_FSD	(HDG_WIDTH_RATIO - 0.05)

static char bob_up_command_heading_carat[] =
{
	7,
	9,
	-3,
	0,
	0,0,0,1,0,0,0,
	0,0,1,1,1,0,0,
	0,1,1,1,1,1,0,
	1,1,1,1,1,1,1,
	0,0,1,1,1,0,0,
	0,0,1,1,1,0,0,
	0,0,1,1,1,0,0,
	0,0,1,1,1,0,0,
	0,0,1,1,1,0,0,
};


//
// flight path marker
//

static char flight_path_marker[] =
{
	// first two is size
	25,
	15,
	// next two is center position
	-12,
	-9,
	// the sprite itself
	0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,
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

////////////////////////////////////////
//
// pitch ladder
//
////////////////////////////////////////

//													P11 O (+ve)
//
//
//    P1    P2    P3    P4    P5    P6    P7    P8    P9    P13   P14   P15
//     O-----O-----O-----O-----O-----O-----O-----O-----O-----O-----O-----O
//     |
//     |
//     |
// P10 O					 						P12 O (-ve)

#define PITCH_BAR_X1			(+0.125)
#define PITCH_BAR_Y1			(+0.000)
#define PITCH_BAR_X2			(+0.160)
#define PITCH_BAR_Y2			(+0.000)
#define PITCH_BAR_X3			(+0.195)
#define PITCH_BAR_Y3			(+0.000)
#define PITCH_BAR_X4			(+0.230)
#define PITCH_BAR_Y4			(+0.000)
#define PITCH_BAR_X5			(+0.265)
#define PITCH_BAR_Y5			(+0.000)
#define PITCH_BAR_X6			(+0.300)
#define PITCH_BAR_Y6			(+0.000)
#define PITCH_BAR_X7			(+0.335)
#define PITCH_BAR_Y7			(+0.000)
#define PITCH_BAR_X8			(+0.370)
#define PITCH_BAR_Y8			(+0.000)
#define PITCH_BAR_X9			(+0.405)
#define PITCH_BAR_Y9			(+0.000)
#define PITCH_BAR_X10		(+0.125)
#define PITCH_BAR_Y10		(-0.050)
#define PITCH_BAR_X11		(+0.335)
#define PITCH_BAR_Y11		(+0.050)
#define PITCH_BAR_X12		(+0.335)
#define PITCH_BAR_Y12		(-0.050)
#define PITCH_BAR_X13		(+0.440)
#define PITCH_BAR_Y13		(-0.000)
#define PITCH_BAR_X14		(+0.475)
#define PITCH_BAR_Y14		(-0.000)
#define PITCH_BAR_X15		(+0.510)
#define PITCH_BAR_Y15		(-0.000)

//
// character position adjust
//

#define PITCH_CHAR_Y_ADJUST	(-3.0)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//
// bank scale
//
////////////////////////////////////////

//
// adjust 2D environment for bank scale clipping
//

#define BANK_SCALE_WINDOW_X_MIN		(HUD_WINDOW_X_MIN)
#define BANK_SCALE_WINDOW_Y_MIN		(HUD_WINDOW_Y_MAX * 0.5)
#define BANK_SCALE_WINDOW_X_MAX		(HUD_WINDOW_X_MAX)
#define BANK_SCALE_WINDOW_Y_MAX		(HUD_WINDOW_Y_MAX * 0.8)

//
// bank scale ticks
//

#define BANK_SCALE_MAJOR_TICK_Y1		(0.69)
#define BANK_SCALE_MAJOR_TICK_Y2		(0.79)
#define BANK_SCALE_MINOR_TICK_Y1		(BANK_SCALE_MAJOR_TICK_Y1 + 0.025)
#define BANK_SCALE_MINOR_TICK_Y2		(BANK_SCALE_MAJOR_TICK_Y2 - 0.025)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define CLIMB_SCALE_FSD					(0.8)

#define CLIMB_SCALE_MAJOR_TICK_X1	(0.850)
#define CLIMB_SCALE_MAJOR_TICK_X2	(0.895)
#define CLIMB_SCALE_MAJOR_TICK_X3	(0.950)
#define CLIMB_SCALE_MAJOR_TICK_X4	(0.995)

#define CLIMB_SCALE_MINOR_TICK_X1	(0.857)
#define CLIMB_SCALE_MINOR_TICK_X2	(0.885)
#define CLIMB_SCALE_MINOR_TICK_X3	(0.957)
#define CLIMB_SCALE_MINOR_TICK_X4	(0.985)

static char rate_of_climb_scale_pointer[] =
{
	5,
	9,
	-5,
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
		x,
		heading,
		heading_step_10,
		mod_heading_step_10;

	int
		loop,
		int_heading_step_10,
		tick_type;

	heading = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_HEADING);

	//
	// adjust 2D environment for heading scale clipping
	//

	set_2d_window (hud_env, HDG_WINDOW_X_MIN, HDG_WINDOW_Y_MIN, HDG_WINDOW_X_MAX, HDG_WINDOW_Y_MAX);

/*	VJ 050126 hud mod start
	hdg_viewport_x_min = (hud_viewport_x_org - (hud_viewport_size * HDG_WIDTH_RATIO * 0.5));

	hdg_viewport_y_min = (hud_viewport_y_org - (hud_viewport_size * 0.5));

	hdg_viewport_x_max = (hud_viewport_x_org + (hud_viewport_size * HDG_WIDTH_RATIO * 0.5) - 0.001);

	hdg_viewport_y_max = (hud_viewport_y_org + (hud_viewport_size * 0.5) - 0.001);
*/
	hdg_viewport_x_min = hud_viewport_x_min + (hud_viewport_size * (1-HDG_WIDTH_RATIO) * 0.5);

	hdg_viewport_y_min = hud_viewport_y_min;

	hdg_viewport_x_max = hud_viewport_x_max - (hud_viewport_size * (1-HDG_WIDTH_RATIO) * 0.5) - 0.001;

	hdg_viewport_y_max = hud_viewport_y_max;
//VJ 050126 hud mod end

	set_2d_viewport (hud_env, hdg_viewport_x_min, hdg_viewport_y_min, hdg_viewport_x_max, hdg_viewport_y_max);

	//
	// draw heading datum tick
	//

	draw_2d_line (HDG_WINDOW_X_ORG, HDG_TICK_DATUM_TOP, HDG_WINDOW_X_ORG, HDG_TICK_DATUM_BOTTOM, hud_colour);

	//
	// draw command heading carat
	//

	if (!apache_damage.navigation_computer)
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

			command_heading = bearing - heading;

			if (command_heading > rad (180.0))
			{
				command_heading -= rad (360.0);
			}
			else if (command_heading < rad (-180.0))
			{
				command_heading += rad (360.0);
			}

			command_heading = bound (command_heading, rad (-90.0), rad (90.0));

			draw_2d_mono_sprite (command_heading_carat, HDG_WINDOW_X_ORG + (command_heading * (HDG_CARAT_FSD / rad (90.0))), HDG_TICK_DATUM_TOP, hud_colour);
		}
	}

	//
	// draw radar sweep indicator
	//

	{
		radar_params
			*radar;

		float
			sweep_position;

		if (!apache_damage.radar)
		{
			radar = NULL;

			if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_GROUND_RADAR)
			{
				radar = &ground_radar;
			}
			else if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_AIR_RADAR)
			{
				radar = &air_radar;
			}

			if (radar)
			{
				sweep_position = radar->scan_datum + radar->sweep_offset;

				if (sweep_position > rad (180.0))
				{
					sweep_position -= rad (360.0);
				}
				else if (sweep_position < rad (-180.0))
				{
					sweep_position += rad (360.0);
				}

				sweep_position = bound (sweep_position, rad (-90.0), rad (90.0));

				draw_2d_mono_sprite (radar_sweep_indicator, HDG_WINDOW_X_ORG + (sweep_position * (RADAR_SWEEP_INDICATOR_FSD / rad (90.0))), HDG_TICK_DATUM_TOP, hud_colour);
			}
		}
	}

	//
	// draw bob-up command heading carat
	//

	{
		float
			command_heading;

		if (hud_bob_up_overlay)
		{
			command_heading = hud_bob_up_heading - heading;

			if (command_heading > rad (180.0))
			{
				command_heading -= rad (360.0);
			}
			else if (command_heading < rad (-180.0))
			{
				command_heading += rad (360.0);
			}

			command_heading = bound (command_heading, rad (-90.0), rad (90.0));

			draw_2d_mono_sprite (bob_up_command_heading_carat, HDG_WINDOW_X_ORG + (command_heading * (BOB_UP_HDG_CARAT_FSD / rad (90.0))), HDG_TICK_DATUM_TOP, hud_colour);
		}
	}

	////////////////////////////////////////
	//
	// draw heading scale
	//
	////////////////////////////////////////

	set_mono_font_type (MONO_FONT_TYPE_5X9);

	heading_step_10 = deg (heading * 0.1);

	int_heading_step_10 = (int) heading_step_10;

	mod_heading_step_10 = heading_step_10 - (float) int_heading_step_10;

	int_heading_step_10 -= 10;

	if (int_heading_step_10 < 0)
	{
		int_heading_step_10 += 36;
	}

	// tick type:-
	//
	//		0 = long tick (30 degs)
	//		1 = short tick (10 degs)
	//		2 = short tick (20 degs)

	tick_type = int_heading_step_10 % 3;

	x = - (10.0 + mod_heading_step_10) * HDG_TICK_X_SPACING;

	for (loop = 0; loop <= 20; loop++)
	{
		if (tick_type == 0)
		{
			draw_2d_line (x, HDG_TICK_30_DEG_TOP, x, HDG_TICK_30_DEG_BOTTOM, hud_colour);

			set_2d_mono_font_position (x, HDG_TICK_30_DEG_TOP);

			switch (int_heading_step_10)
			{
				////////////////////////////////////////
				case 0:
				////////////////////////////////////////
				{
					set_mono_font_rel_position (HDG_CHAR_ADJUST_SINGLE, HDG_CHAR_Y_ADJUST);

					print_mono_font_char ('N');

					break;
				}
				////////////////////////////////////////
				case 9:
				////////////////////////////////////////
				{
					set_mono_font_rel_position (HDG_CHAR_ADJUST_SINGLE, HDG_CHAR_Y_ADJUST);

					print_mono_font_char ('E');

					break;
				}
				////////////////////////////////////////
				case 18:
				////////////////////////////////////////
				{
					set_mono_font_rel_position (HDG_CHAR_ADJUST_SINGLE, HDG_CHAR_Y_ADJUST);

					print_mono_font_char ('S');

					break;
				}
				////////////////////////////////////////
				case 27:
				////////////////////////////////////////
				{
					set_mono_font_rel_position (HDG_CHAR_ADJUST_SINGLE, HDG_CHAR_Y_ADJUST);

					print_mono_font_char ('W');

					break;
				}
				////////////////////////////////////////
				default:
				////////////////////////////////////////
				{
					if (int_heading_step_10 < 10)
					{
						set_mono_font_rel_position (HDG_CHAR_ADJUST_SINGLE, HDG_CHAR_Y_ADJUST);

						print_mono_font_char ('0' + int_heading_step_10);
					}
					else
					{
						set_mono_font_rel_position (HDG_CHAR_ADJUST_DOUBLE, HDG_CHAR_Y_ADJUST);

						print_mono_font_char ('0' + int_heading_step_10 / 10);

						print_mono_font_char ('0' + int_heading_step_10 % 10);
					}

					break;
				}
			}
		}
		else
		{
			draw_2d_line (x, HDG_TICK_10_DEG_TOP, x, HDG_TICK_10_DEG_BOTTOM, hud_colour);
		}

		int_heading_step_10 = (++int_heading_step_10 == 36) ? 0 : int_heading_step_10;

		tick_type = (++tick_type == 3) ? 0 : tick_type;

		x += HDG_TICK_X_SPACING;
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

static int limit_pitch (int pitch, int *step_direction)
{
	if (pitch > 9)
	{
		pitch -= 18;

		pitch = -pitch;

		*step_direction = -(*step_direction);
	}
	else if (pitch < -9)
	{
		pitch += 18;

		pitch = -pitch;

		*step_direction = -(*step_direction);
	}

	return (pitch);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// returns true if some part of the line lies inside the clip box
static short clip_2d_line(float* x1, float* y1, float* x2, float* y2, float xmin, float ymin, float xmax, float ymax)
{
	float ratio;
	float dx, dy;

	dy = *y2 - *y1;
	if (fabs(dy) < 0.001)  // (close to) horizontal line
	{
		if (*y1 > ymax || *y1 < ymin)  // line outside clip box
			return FALSE;

		*y2 = *y1;
		*x1 = bound(*x1, xmin, xmax);
		*x2 = bound(*x2, xmin, xmax);

		return *x1 != *x2;
	}
	dx = *x2 - *x1;
	if (fabs(dx) < 0.001)  // (close to) vertical line
	{
		if (*x1 < xmin || *x1 > xmax) // line outside clip box
			return FALSE;
		
		*x1 = *x2;
		*y1 = bound(*y1, ymin, ymax);
		*y2 = bound(*y2, ymin, ymax);
		
		return *y1 != *y2;
	}

	ratio = dy / dx;

	if (*x1 < xmin)
	{
		*y1 += (xmin - *x1) * ratio;
		*x1 = xmin;
	}
	else if (*x1 > xmax)
	{
		*y1 -= (*x1 - xmax) * ratio;
		*x1 = xmax;
	}

	if (*x2 < xmin)
	{
		*y2 += (xmin - *x2) * ratio;
		*x2 = xmin;	
	}
	else if (*x2 > xmax)
	{
		*y2 -= (*x2 - xmax) * ratio;
		*x2 = xmax;
	}

	if ((*y1 < ymin && *y2 < ymin) || (*y1 > ymax && *y2 > ymax))
		return FALSE;

	if (*y1 < ymin)
	{
		ASSERT(ratio > 0);
		*x1 += (ymin - *y1) / ratio;
		*y1 = ymin;
		ASSERT(*x1 < xmax);
	}
	else if (*y1 > ymax)
	{
		ASSERT(ratio < 0);
		*x1 -= (*y1 - ymax) / ratio;
		*y1 = ymax;
		ASSERT(*x1 < xmax);
	}

	if (*y2 < ymin)
	{
		ASSERT(ratio < 0);
		*x2 += (ymin - *y2) / ratio;
		*y2 = ymin;
		ASSERT(*x2 < xmax);
	}
	else if (*y2 > ymax)
	{
		ASSERT(ratio > 0);
		*x2 -= (*y2 - ymax) / ratio;
		*y2 = ymax;
		ASSERT(*x2 < xmax);
	}

	ASSERT(*x1 >= xmin && *x1 <= xmax && *x2 >= xmin && *x2 <= xmax &&
		   *y1 >= ymin && *y1 <= ymax && *y2 >= ymin && *y2 <= ymax);
	
	return *x1 != *x2 && *y1 != *y2;
}

// arneh, june 2006 - added as part of transition mode hud
static void draw_flight_path_marker (void)
{
	float forward_airspeed, sideways_airspeed, vertical_airspeed, flight_vector_x, flight_vector_y;
	float pitch, roll, pixels_per_rad, focal_length;
	float fpm_x_pixel_offset, fpm_y_pixel_offset, hud_pixel_ratio, fpm_hud_x_offset, fpm_hud_y_offset;
	float cos_roll, sin_roll, fpm_x_offset, fpm_y_offset;
	float horizon_angle, line_climb_ratio, horizon_pt_x, horizon_pt_y, horizon_deg;
	float horizon_hud_x, horizon_hud_y, left_hud_x, left_hud_y, right_hud_x, right_hud_y;
	
	forward_airspeed = current_flight_dynamics->velocity_z.value;
	sideways_airspeed = current_flight_dynamics->velocity_x.value;
	vertical_airspeed = current_flight_dynamics->world_velocity_y.value;

	// figure out which direction we're going (relative to nose)
	if (forward_airspeed < 0.01)   // don't bother drawing flight path marker if going backwards
		return;
	else
	{
		flight_vector_y = atan(vertical_airspeed / forward_airspeed);
		flight_vector_x = atan(sideways_airspeed / forward_airspeed);
	}

	pitch = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_PITCH);
	roll = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_ROLL);
	cos_roll = cos(roll);
	sin_roll = sin(roll);

	ASSERT (main_3d_env);
	
	// figure out on which screen pixel the flight path marker should be drawn
	focal_length = tan (main_3d_env->width_view_angle * 0.5);               // view angle (20, 60, 80 deg etc.)
	pixels_per_rad = (main_3d_env->clip_xmax - main_3d_env->clip_xmin) * 0.5;  // resolution
	pixels_per_rad /= focal_length;

	fpm_x_offset = pilot_head_heading + cos_roll * flight_vector_x + sin_roll * (pitch - flight_vector_y);
	fpm_y_offset = pilot_head_pitch + cos_roll * (pitch - flight_vector_y) - sin_roll * flight_vector_x;
	fpm_x_pixel_offset = pixels_per_rad * tan(fpm_x_offset);
	fpm_y_pixel_offset = pixels_per_rad * tan(fpm_y_offset);


	// figure out which hud texture pixel lies on top the screen pixel
	hud_pixel_ratio = 1.0 /((active_2d_environment->vp.x_max - active_2d_environment->vp.x_min) * 0.5 / hud_screen_x_scale);
	fpm_hud_x_offset = fpm_x_pixel_offset * hud_pixel_ratio;
	fpm_hud_y_offset = fpm_y_pixel_offset * hud_pixel_ratio;

	// draw the flight path marker on the hud
	if (fpm_hud_x_offset > HUD_WINDOW_X_MIN + 0.05 && fpm_hud_x_offset < HUD_WINDOW_X_MAX - 0.05 && fpm_hud_y_offset > HUD_WINDOW_Y_MIN + 0.05 && fpm_hud_y_offset < HUD_WINDOW_Y_MAX - 0.05)
		draw_2d_mono_sprite (flight_path_marker, fpm_hud_x_offset, -fpm_hud_y_offset, hud_colour);


	// draw horizon line
	horizon_pt_x = fpm_x_offset + sin_roll * flight_vector_y;
	horizon_pt_y = -(fpm_y_offset + cos_roll * flight_vector_y);
	horizon_hud_x = hud_pixel_ratio * pixels_per_rad * tan(horizon_pt_x);
	horizon_hud_y = hud_pixel_ratio * pixels_per_rad * tan(horizon_pt_y);
	
	horizon_angle = cos(pilot_head_heading) * roll + sin(pilot_head_heading) * -pitch;
	horizon_deg = fmod(fabs(deg(horizon_angle)), 180);

	if (horizon_deg < 89)  // my primitive horizon drawing algoritm assumes less than 90 degrees bank angle
	{
		line_climb_ratio = tan(horizon_angle);
	
		left_hud_x = horizon_hud_x - 1.5;
		left_hud_y = horizon_hud_y + 1.5 * -line_climb_ratio;
		right_hud_x = horizon_hud_x + 1.5;
		right_hud_y = horizon_hud_y + 1.5 * line_climb_ratio;
	
		if (clip_2d_line(&left_hud_x, &left_hud_y, &right_hud_x, &right_hud_y, -0.75, -0.75, 0.8, 0.8))
		{
			float step = 0.05;
			float x, y;
			float xstep = step * cos_roll;
			float ystep = xstep * line_climb_ratio;
			ASSERT(left_hud_x != right_hud_x);
			ASSERT(xstep != 0);

			// draw left side of horizon line
			x = horizon_hud_x - 3*xstep;
			y = horizon_hud_y - 3*ystep;
			while (x > left_hud_x)
			{
				float x2, y2;
				x2 = x - xstep;
				y2 = y - ystep;

				if (x <= right_hud_x)
					draw_2d_line(x, y, x2, y2, hud_colour);

				x -= 2*xstep;
				y -= 2*ystep;
			}

			// draw right side of horizon line
			x = horizon_hud_x + 3*xstep;
			y = horizon_hud_y + 3*ystep;
			while (x < right_hud_x)
			{
				float x2, y2;
				x2 = x + xstep;
				y2 = y + ystep;
	
				if (x >= left_hud_x)
					draw_2d_line(x, y, x2, y2, hud_colour);

				x += 2*xstep;
				y += 2*ystep;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_pitch_ladder (int draw_horizon_line_only)
{
	float
		//VJ 050204 bug fix scale not correct
		scalefactor,
		pitch,
		mod_pitch,
		tan_mod_pitch,
		roll,
		x,
		y,
		x_scale,
		y_scale,
		x_horizon,
		y_horizon,
		x_10_deg_step,
		y_10_deg_step,
		x_adjust;

	int
		int_pitch,
		step_direction,
		loop;

	char
		s[20];

	ASSERT (main_3d_env);

	//VJ 050213 bug fix scale not correct
	scalefactor = global_hud_size2;

	pitch = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_PITCH);

	roll = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_ROLL);

	mod_pitch = fmod (pitch, rad (10.0));

	tan_mod_pitch = -tan (mod_pitch);

	int_pitch = (int) (pitch * (1.0 / rad (10.0)));

	//
	// get x and y scale factors
	//

	x_scale = (main_3d_env->clip_xmax - main_3d_env->clip_xmin) * 0.5;
	x_scale /= tan (main_3d_env->width_view_angle * 0.5);
	x_scale /= (active_2d_environment->vp.x_max - active_2d_environment->vp.x_min) * 0.5;
	x_scale *= -sin (roll);
//VJ 050204 bug fix scale not correct
	x_scale *= hud_screen_x_scale * scalefactor;

	y_scale = (main_3d_env->clip_ymax - main_3d_env->clip_ymin) * 0.5;
	y_scale /= tan (main_3d_env->height_view_angle * 0.5);
	y_scale /= (active_2d_environment->vp.y_max - active_2d_environment->vp.y_min) * 0.5;
	y_scale *= cos (roll);
//VJ 050204 bug fix scale not correct
	y_scale *= hud_screen_y_scale * scalefactor;
	
	x_horizon = tan_mod_pitch * x_scale;
	y_horizon = tan_mod_pitch * y_scale;

	x_10_deg_step = tan (rad (10.0)) * x_scale;
	y_10_deg_step = tan (rad (10.0)) * y_scale;

	////////////////////////////////////////
	//
	// draw pitch ladder
	//
	////////////////////////////////////////

	set_mono_font_type (MONO_FONT_TYPE_6X10);

	step_direction = -1;

	int_pitch = limit_pitch (int_pitch + 2, &step_direction);

	x = x_horizon + x_10_deg_step * 2.0;
	y = y_horizon + y_10_deg_step * 2.0;

	set_2d_instance_rotation (hud_env, roll);

	for (loop = 0; loop < 5; loop++)
	{
		set_2d_instance_position (hud_env, x, y);

		if (draw_horizon_line_only)
		{
			if (int_pitch == 0)
			{
				draw_2d_line (+PITCH_BAR_X1, +PITCH_BAR_Y1, +PITCH_BAR_X2, +PITCH_BAR_Y2, hud_colour);
				draw_2d_line (-PITCH_BAR_X1, +PITCH_BAR_Y1, -PITCH_BAR_X2, +PITCH_BAR_Y2, hud_colour);

				draw_2d_line (+PITCH_BAR_X3, +PITCH_BAR_Y3, +PITCH_BAR_X4, +PITCH_BAR_Y4, hud_colour);
				draw_2d_line (-PITCH_BAR_X3, +PITCH_BAR_Y3, -PITCH_BAR_X4, +PITCH_BAR_Y4, hud_colour);

				draw_2d_line (+PITCH_BAR_X5, +PITCH_BAR_Y5, +PITCH_BAR_X6, +PITCH_BAR_Y6, hud_colour);
				draw_2d_line (-PITCH_BAR_X5, +PITCH_BAR_Y5, -PITCH_BAR_X6, +PITCH_BAR_Y6, hud_colour);

				draw_2d_line (+PITCH_BAR_X7, +PITCH_BAR_Y7, +PITCH_BAR_X8, +PITCH_BAR_Y8, hud_colour);
				draw_2d_line (-PITCH_BAR_X7, +PITCH_BAR_Y7, -PITCH_BAR_X8, +PITCH_BAR_Y8, hud_colour);

				draw_2d_line (+PITCH_BAR_X9, +PITCH_BAR_Y9, +PITCH_BAR_X13, +PITCH_BAR_Y13, hud_colour);
				draw_2d_line (-PITCH_BAR_X9, +PITCH_BAR_Y9, -PITCH_BAR_X13, +PITCH_BAR_Y13, hud_colour);

				draw_2d_line (+PITCH_BAR_X14, +PITCH_BAR_Y14, +PITCH_BAR_X15, +PITCH_BAR_Y15, hud_colour);
				draw_2d_line (-PITCH_BAR_X14, +PITCH_BAR_Y14, -PITCH_BAR_X15, +PITCH_BAR_Y15, hud_colour);
			}
		}
		else
		{
			switch (int_pitch)
			{
				////////////////////////////////////////
				case 0:
				////////////////////////////////////////
				{
					draw_2d_line (+PITCH_BAR_X1, +PITCH_BAR_Y1, +PITCH_BAR_X9, +PITCH_BAR_Y9, hud_colour);
					draw_2d_line (-PITCH_BAR_X1, +PITCH_BAR_Y1, -PITCH_BAR_X9, +PITCH_BAR_Y9, hud_colour);

					break;
				}
				////////////////////////////////////////
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
				////////////////////////////////////////
				{
					if (step_direction == -1)
					{
						draw_2d_line (+PITCH_BAR_X1, +PITCH_BAR_Y1, +PITCH_BAR_X8, +PITCH_BAR_Y8, hud_colour);
						draw_2d_line (-PITCH_BAR_X1, +PITCH_BAR_Y1, -PITCH_BAR_X8, +PITCH_BAR_Y8, hud_colour);

						draw_2d_line (+PITCH_BAR_X1, +PITCH_BAR_Y1, +PITCH_BAR_X10, +PITCH_BAR_Y10, hud_colour);
						draw_2d_line (-PITCH_BAR_X1, +PITCH_BAR_Y1, -PITCH_BAR_X10, +PITCH_BAR_Y10, hud_colour);
					}
					else
					{
						draw_2d_line (-PITCH_BAR_X1, -PITCH_BAR_Y1, -PITCH_BAR_X8, -PITCH_BAR_Y8, hud_colour);
						draw_2d_line (+PITCH_BAR_X1, -PITCH_BAR_Y1, +PITCH_BAR_X8, -PITCH_BAR_Y8, hud_colour);

						draw_2d_line (-PITCH_BAR_X1, -PITCH_BAR_Y1, -PITCH_BAR_X10, -PITCH_BAR_Y10, hud_colour);
						draw_2d_line (+PITCH_BAR_X1, -PITCH_BAR_Y1, +PITCH_BAR_X10, -PITCH_BAR_Y10, hud_colour);
					}

					sprintf (s, "%d0", int_pitch);

					x_adjust = get_mono_font_string_width (s) * -0.5 - 1.0;

					set_2d_mono_font_position (+PITCH_BAR_X11, +PITCH_BAR_Y11);

					set_mono_font_rel_position (x_adjust, PITCH_CHAR_Y_ADJUST);

					print_mono_font_string (s);

					set_2d_mono_font_position (-PITCH_BAR_X11, +PITCH_BAR_Y11);

					set_mono_font_rel_position (x_adjust, PITCH_CHAR_Y_ADJUST);

					print_mono_font_string (s);

					break;
				}

				////////////////////////////////////////
				case 9:
				////////////////////////////////////////
				{
					draw_2d_line (+PITCH_BAR_X1, +PITCH_BAR_Y1, +PITCH_BAR_X8, +PITCH_BAR_Y8, hud_colour);
					draw_2d_line (-PITCH_BAR_X1, +PITCH_BAR_Y1, -PITCH_BAR_X8, +PITCH_BAR_Y8, hud_colour);

					break;
				}

				////////////////////////////////////////
				case -1:
				case -2:
				case -3:
				case -4:
				case -5:
				case -6:
				case -7:
				case -8:
				////////////////////////////////////////
				{
					if (step_direction == -1)
					{
						draw_2d_line (+PITCH_BAR_X1, +PITCH_BAR_Y1, +PITCH_BAR_X2, +PITCH_BAR_Y2, hud_colour);
						draw_2d_line (-PITCH_BAR_X1, +PITCH_BAR_Y1, -PITCH_BAR_X2, +PITCH_BAR_Y2, hud_colour);

						draw_2d_line (+PITCH_BAR_X3, +PITCH_BAR_Y3, +PITCH_BAR_X4, +PITCH_BAR_Y4, hud_colour);
						draw_2d_line (-PITCH_BAR_X3, +PITCH_BAR_Y3, -PITCH_BAR_X4, +PITCH_BAR_Y4, hud_colour);

						draw_2d_line (+PITCH_BAR_X5, +PITCH_BAR_Y5, +PITCH_BAR_X6, +PITCH_BAR_Y6, hud_colour);
						draw_2d_line (-PITCH_BAR_X5, +PITCH_BAR_Y5, -PITCH_BAR_X6, +PITCH_BAR_Y6, hud_colour);

						draw_2d_line (+PITCH_BAR_X7, +PITCH_BAR_Y7, +PITCH_BAR_X8, +PITCH_BAR_Y8, hud_colour);
						draw_2d_line (-PITCH_BAR_X7, +PITCH_BAR_Y7, -PITCH_BAR_X8, +PITCH_BAR_Y8, hud_colour);

						draw_2d_line (+PITCH_BAR_X1, +PITCH_BAR_Y1, +PITCH_BAR_X10, +PITCH_BAR_Y10, hud_colour);
						draw_2d_line (-PITCH_BAR_X1, +PITCH_BAR_Y1, -PITCH_BAR_X10, +PITCH_BAR_Y10, hud_colour);
					}
					else
					{
						draw_2d_line (-PITCH_BAR_X1, -PITCH_BAR_Y1, -PITCH_BAR_X2, -PITCH_BAR_Y2, hud_colour);
						draw_2d_line (+PITCH_BAR_X1, -PITCH_BAR_Y1, +PITCH_BAR_X2, -PITCH_BAR_Y2, hud_colour);

						draw_2d_line (-PITCH_BAR_X3, -PITCH_BAR_Y3, -PITCH_BAR_X4, -PITCH_BAR_Y4, hud_colour);
						draw_2d_line (+PITCH_BAR_X3, -PITCH_BAR_Y3, +PITCH_BAR_X4, -PITCH_BAR_Y4, hud_colour);

						draw_2d_line (-PITCH_BAR_X5, -PITCH_BAR_Y5, -PITCH_BAR_X6, -PITCH_BAR_Y6, hud_colour);
						draw_2d_line (+PITCH_BAR_X5, -PITCH_BAR_Y5, +PITCH_BAR_X6, -PITCH_BAR_Y6, hud_colour);

						draw_2d_line (-PITCH_BAR_X7, -PITCH_BAR_Y7, -PITCH_BAR_X8, -PITCH_BAR_Y8, hud_colour);
						draw_2d_line (+PITCH_BAR_X7, -PITCH_BAR_Y7, +PITCH_BAR_X8, -PITCH_BAR_Y8, hud_colour);

						draw_2d_line (-PITCH_BAR_X1, -PITCH_BAR_Y1, -PITCH_BAR_X10, -PITCH_BAR_Y10, hud_colour);
						draw_2d_line (+PITCH_BAR_X1, -PITCH_BAR_Y1, +PITCH_BAR_X10, -PITCH_BAR_Y10, hud_colour);
					}

					sprintf (s, "%d0", int_pitch);

					x_adjust = get_mono_font_string_width (s) * -0.5 - 1.0;

					set_2d_mono_font_position (+PITCH_BAR_X12, +PITCH_BAR_Y12);

					set_mono_font_rel_position (x_adjust, PITCH_CHAR_Y_ADJUST);

					print_mono_font_string (s);

					set_2d_mono_font_position (-PITCH_BAR_X12, +PITCH_BAR_Y12);

					set_mono_font_rel_position (x_adjust, PITCH_CHAR_Y_ADJUST);

					print_mono_font_string (s);

					break;
				}

				////////////////////////////////////////
				case -9:
				////////////////////////////////////////
				{
					draw_2d_line (+PITCH_BAR_X1, +PITCH_BAR_Y1, +PITCH_BAR_X2, +PITCH_BAR_Y2, hud_colour);
					draw_2d_line (-PITCH_BAR_X1, +PITCH_BAR_Y1, -PITCH_BAR_X2, +PITCH_BAR_Y2, hud_colour);

					draw_2d_line (+PITCH_BAR_X3, +PITCH_BAR_Y3, +PITCH_BAR_X4, +PITCH_BAR_Y4, hud_colour);
					draw_2d_line (-PITCH_BAR_X3, +PITCH_BAR_Y3, -PITCH_BAR_X4, +PITCH_BAR_Y4, hud_colour);

					draw_2d_line (+PITCH_BAR_X5, +PITCH_BAR_Y5, +PITCH_BAR_X6, +PITCH_BAR_Y6, hud_colour);
					draw_2d_line (-PITCH_BAR_X5, +PITCH_BAR_Y5, -PITCH_BAR_X6, +PITCH_BAR_Y6, hud_colour);

					draw_2d_line (+PITCH_BAR_X7, +PITCH_BAR_Y7, +PITCH_BAR_X8, +PITCH_BAR_Y8, hud_colour);
					draw_2d_line (-PITCH_BAR_X7, +PITCH_BAR_Y7, -PITCH_BAR_X8, +PITCH_BAR_Y8, hud_colour);

					break;
				}
			}
		}

		int_pitch = limit_pitch (int_pitch + step_direction, &step_direction);

		x -= x_10_deg_step;
		y -= y_10_deg_step;
	}

	reset_2d_instance (hud_env);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_bank_scale (void)
{
	float
		roll;

	//
	// adjust 2D environment for bank scale clipping
	//

	set_2d_window (hud_env, BANK_SCALE_WINDOW_X_MIN, BANK_SCALE_WINDOW_Y_MIN, BANK_SCALE_WINDOW_X_MAX, BANK_SCALE_WINDOW_Y_MAX);
/*
	bank_scale_viewport_x_min = (hud_viewport_x_org - (HUD_VIEWPORT_SIZE * 0.5));

	bank_scale_viewport_y_min = (hud_viewport_y_org - (HUD_VIEWPORT_SIZE * 0.5 * 0.8));

	bank_scale_viewport_x_max = (hud_viewport_x_org + (HUD_VIEWPORT_SIZE * 0.5) - 0.001);

	bank_scale_viewport_y_max = (hud_viewport_y_org - (HUD_VIEWPORT_SIZE * 0.5 * 0.5) - 0.001);
*/
//VJ 050126 hud mod start
	bank_scale_viewport_x_min = hud_viewport_x_min;
                                                 
	bank_scale_viewport_y_min = hud_viewport_y_min + (hud_viewport_size * 0.1);
                                                 
	bank_scale_viewport_x_max = hud_viewport_x_max;
                                                 
	bank_scale_viewport_y_max = hud_viewport_y_min + (hud_viewport_size * 0.25) - 0.001;

	set_2d_viewport (hud_env, bank_scale_viewport_x_min, bank_scale_viewport_y_min, bank_scale_viewport_x_max, bank_scale_viewport_y_max);
//VJ 050126 hud mod end

	set_2d_viewport (hud_env, bank_scale_viewport_x_min, bank_scale_viewport_y_min, bank_scale_viewport_x_max, bank_scale_viewport_y_max);

	//
	// draw bank scale
	//

	set_2d_instance_position (hud_env, 0.0, 0.0);

	roll = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_ROLL);

	set_2d_instance_rotation (hud_env, roll);
	draw_2d_line (0.0, BANK_SCALE_MAJOR_TICK_Y1, 0.0, BANK_SCALE_MAJOR_TICK_Y2, hud_colour);

	set_2d_instance_rotation (hud_env, roll + rad (5.0));
	draw_2d_line (0.0, BANK_SCALE_MINOR_TICK_Y1, 0.0, BANK_SCALE_MINOR_TICK_Y2, hud_colour);
	set_2d_instance_rotation (hud_env, roll - rad (5.0));
	draw_2d_line (0.0, BANK_SCALE_MINOR_TICK_Y1, 0.0, BANK_SCALE_MINOR_TICK_Y2, hud_colour);

	set_2d_instance_rotation (hud_env, roll + rad (10.0));
	draw_2d_line (0.0, BANK_SCALE_MAJOR_TICK_Y1, 0.0, BANK_SCALE_MAJOR_TICK_Y2, hud_colour);
	set_2d_instance_rotation (hud_env, roll - rad (10.0));
	draw_2d_line (0.0, BANK_SCALE_MAJOR_TICK_Y1, 0.0, BANK_SCALE_MAJOR_TICK_Y2, hud_colour);

	set_2d_instance_rotation (hud_env, roll + rad (15.0));
	draw_2d_line (0.0, BANK_SCALE_MINOR_TICK_Y1, 0.0, BANK_SCALE_MINOR_TICK_Y2, hud_colour);
	set_2d_instance_rotation (hud_env, roll - rad (15.0));
	draw_2d_line (0.0, BANK_SCALE_MINOR_TICK_Y1, 0.0, BANK_SCALE_MINOR_TICK_Y2, hud_colour);

	set_2d_instance_rotation (hud_env, roll + rad (20.0));
	draw_2d_line (0.0, BANK_SCALE_MAJOR_TICK_Y1, 0.0, BANK_SCALE_MAJOR_TICK_Y2, hud_colour);
	set_2d_instance_rotation (hud_env, roll - rad (20.0));
	draw_2d_line (0.0, BANK_SCALE_MAJOR_TICK_Y1, 0.0, BANK_SCALE_MAJOR_TICK_Y2, hud_colour);

	set_2d_instance_rotation (hud_env, roll + rad (25.0));
	draw_2d_line (0.0, BANK_SCALE_MINOR_TICK_Y1, 0.0, BANK_SCALE_MINOR_TICK_Y2, hud_colour);
	set_2d_instance_rotation (hud_env, roll - rad (25.0));
	draw_2d_line (0.0, BANK_SCALE_MINOR_TICK_Y1, 0.0, BANK_SCALE_MINOR_TICK_Y2, hud_colour);

	set_2d_instance_rotation (hud_env, roll + rad (30.0));
	draw_2d_line (0.0, BANK_SCALE_MAJOR_TICK_Y1, 0.0, BANK_SCALE_MAJOR_TICK_Y2, hud_colour);
	set_2d_instance_rotation (hud_env, roll - rad (30.0));
	draw_2d_line (0.0, BANK_SCALE_MAJOR_TICK_Y1, 0.0, BANK_SCALE_MAJOR_TICK_Y2, hud_colour);

	reset_2d_instance (hud_env);

	//
	// restore 2D environment
	//

	set_2d_window (hud_env, HUD_WINDOW_X_MIN, HUD_WINDOW_Y_MIN, HUD_WINDOW_X_MAX, HUD_WINDOW_Y_MAX);

	set_2d_viewport (hud_env, hud_viewport_x_min, hud_viewport_y_min, hud_viewport_x_max, hud_viewport_y_max);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_true_airspeed (void)
{
	float
		true_airspeed;

	char
		s[20];

	true_airspeed = current_flight_dynamics->velocity_z.value;

	true_airspeed = knots (true_airspeed);

	sprintf (s, "%d", (int) true_airspeed);

	set_mono_font_type (MONO_FONT_TYPE_7X12);

	set_2d_mono_font_position (-1.0, 0.0);

	set_mono_font_rel_position (1.0, -4.0);

	print_mono_font_string (s);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_barometric_altitude (void)
{
	float
		barometric_altitude,
		width;

	char
		s[20];

	barometric_altitude = feet (current_flight_dynamics->barometric_altitude.value);

	set_mono_font_type (MONO_FONT_TYPE_6X10);

	sprintf (s, "%d", (int) barometric_altitude);

	width = get_mono_font_string_width (s);

	set_2d_mono_font_position (0.8, 0.8);

	set_mono_font_rel_position (-width, -3.0);

	print_mono_font_string (s);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_rate_of_climb_scale (void)
{
	float
		radar_altitude,
		rate_of_climb,
		x,
		y,
		y1,
		y2,
		width;

	char
		s[20];

	//
	// draw scale
	//

	draw_2d_line (CLIMB_SCALE_MAJOR_TICK_X1, CLIMB_SCALE_FSD * +1.0, CLIMB_SCALE_MAJOR_TICK_X2, CLIMB_SCALE_FSD * +1.0, hud_colour);
	draw_2d_line (CLIMB_SCALE_MAJOR_TICK_X3, CLIMB_SCALE_FSD * +1.0, CLIMB_SCALE_MAJOR_TICK_X4, CLIMB_SCALE_FSD * +1.0, hud_colour);

	draw_2d_line (CLIMB_SCALE_MAJOR_TICK_X1, CLIMB_SCALE_FSD * +0.5, CLIMB_SCALE_MAJOR_TICK_X2, CLIMB_SCALE_FSD * +0.5, hud_colour);
	draw_2d_line (CLIMB_SCALE_MAJOR_TICK_X3, CLIMB_SCALE_FSD * +0.5, CLIMB_SCALE_MAJOR_TICK_X4, CLIMB_SCALE_FSD * +0.5, hud_colour);

	draw_2d_line (CLIMB_SCALE_MINOR_TICK_X1, CLIMB_SCALE_FSD * +0.4, CLIMB_SCALE_MINOR_TICK_X2, CLIMB_SCALE_FSD * +0.4, hud_colour);

	draw_2d_line (CLIMB_SCALE_MINOR_TICK_X1, CLIMB_SCALE_FSD * +0.3, CLIMB_SCALE_MINOR_TICK_X2, CLIMB_SCALE_FSD * +0.3, hud_colour);

	draw_2d_line (CLIMB_SCALE_MINOR_TICK_X1, CLIMB_SCALE_FSD * +0.2, CLIMB_SCALE_MINOR_TICK_X2, CLIMB_SCALE_FSD * +0.2, hud_colour);

	draw_2d_line (CLIMB_SCALE_MINOR_TICK_X1, CLIMB_SCALE_FSD * +0.1, CLIMB_SCALE_MINOR_TICK_X2, CLIMB_SCALE_FSD * +0.1, hud_colour);

	draw_2d_line (CLIMB_SCALE_MAJOR_TICK_X1, CLIMB_SCALE_FSD * +0.0, CLIMB_SCALE_MAJOR_TICK_X2, CLIMB_SCALE_FSD * +0.0, hud_colour);
	draw_2d_line (CLIMB_SCALE_MAJOR_TICK_X3, CLIMB_SCALE_FSD * +0.0, CLIMB_SCALE_MAJOR_TICK_X4, CLIMB_SCALE_FSD * +0.0, hud_colour);

	draw_2d_line (CLIMB_SCALE_MINOR_TICK_X1, CLIMB_SCALE_FSD * -0.1, CLIMB_SCALE_MINOR_TICK_X2, CLIMB_SCALE_FSD * -0.1, hud_colour);

	draw_2d_line (CLIMB_SCALE_MINOR_TICK_X1, CLIMB_SCALE_FSD * -0.2, CLIMB_SCALE_MINOR_TICK_X2, CLIMB_SCALE_FSD * -0.2, hud_colour);

	draw_2d_line (CLIMB_SCALE_MINOR_TICK_X1, CLIMB_SCALE_FSD * -0.3, CLIMB_SCALE_MINOR_TICK_X2, CLIMB_SCALE_FSD * -0.3, hud_colour);

	draw_2d_line (CLIMB_SCALE_MINOR_TICK_X1, CLIMB_SCALE_FSD * -0.4, CLIMB_SCALE_MINOR_TICK_X2, CLIMB_SCALE_FSD * -0.4, hud_colour);

	draw_2d_line (CLIMB_SCALE_MAJOR_TICK_X1, CLIMB_SCALE_FSD * -0.5, CLIMB_SCALE_MAJOR_TICK_X2, CLIMB_SCALE_FSD * -0.5, hud_colour);
	draw_2d_line (CLIMB_SCALE_MAJOR_TICK_X3, CLIMB_SCALE_FSD * -0.5, CLIMB_SCALE_MAJOR_TICK_X4, CLIMB_SCALE_FSD * -0.5, hud_colour);

	draw_2d_line (CLIMB_SCALE_MINOR_TICK_X3, CLIMB_SCALE_FSD * -0.6, CLIMB_SCALE_MINOR_TICK_X4, CLIMB_SCALE_FSD * -0.6, hud_colour);

	draw_2d_line (CLIMB_SCALE_MINOR_TICK_X3, CLIMB_SCALE_FSD * -0.7, CLIMB_SCALE_MINOR_TICK_X4, CLIMB_SCALE_FSD * -0.7, hud_colour);

	draw_2d_line (CLIMB_SCALE_MINOR_TICK_X3, CLIMB_SCALE_FSD * -0.8, CLIMB_SCALE_MINOR_TICK_X4, CLIMB_SCALE_FSD * -0.8, hud_colour);

	draw_2d_line (CLIMB_SCALE_MINOR_TICK_X3, CLIMB_SCALE_FSD * -0.9, CLIMB_SCALE_MINOR_TICK_X4, CLIMB_SCALE_FSD * -0.9, hud_colour);

	draw_2d_line (CLIMB_SCALE_MAJOR_TICK_X1, CLIMB_SCALE_FSD * -1.0, CLIMB_SCALE_MAJOR_TICK_X2, CLIMB_SCALE_FSD * -1.0, hud_colour);
	draw_2d_line (CLIMB_SCALE_MAJOR_TICK_X3, CLIMB_SCALE_FSD * -1.0, CLIMB_SCALE_MAJOR_TICK_X4, CLIMB_SCALE_FSD * -1.0, hud_colour);

	//
	// display analogue radar altitude
	//

	radar_altitude = feet (current_flight_dynamics->radar_altitude.value);

	if (radar_altitude <= 200.0)
	{
		y1 = -CLIMB_SCALE_FSD;

		y2 = -CLIMB_SCALE_FSD + radar_altitude * ((CLIMB_SCALE_FSD * 2.0) / 200.0);

		get_2d_float_screen_coordinates (CLIMB_SCALE_MAJOR_TICK_X2, y1, &x, &y1);

		get_2d_float_screen_coordinates (CLIMB_SCALE_MAJOR_TICK_X2, y2, &x, &y2);

		draw_line (x + 1.0, y1, x + 1.0, y2, hud_colour);
		draw_line (x + 2.0, y1, x + 2.0, y2, hud_colour);
		draw_line (x + 3.0, y1, x + 3.0, y2, hud_colour);
		draw_line (x + 4.0, y1, x + 4.0, y2, hud_colour);
		draw_line (x + 5.0, y1, x + 5.0, y2, hud_colour);
		draw_line (x + 6.0, y1, x + 6.0, y2, hud_colour);
	}

	//
	// display digital radar altitude
	//

	if (radar_altitude <= 1500.0)
	{
		set_mono_font_type (MONO_FONT_TYPE_7X12);

		sprintf (s, "%d", (int) radar_altitude);

		width = get_mono_font_string_width (s);

		set_2d_mono_font_position (CLIMB_SCALE_MAJOR_TICK_X1, 0.0);

		set_mono_font_rel_position (-width - 5.0, -4.0);

		print_mono_font_string (s);
	}

	//
	// draw rate of climb scale pointer
	//

	rate_of_climb = current_flight_dynamics->world_velocity_y.value;

	rate_of_climb = feet_per_minute (rate_of_climb);

	rate_of_climb = bound (rate_of_climb, -1000.0, 1000.0);

	x = CLIMB_SCALE_MAJOR_TICK_X1;

	y = rate_of_climb * (CLIMB_SCALE_FSD / 1000.0);

	draw_2d_mono_sprite (rate_of_climb_scale_pointer, x, y, hud_colour);
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

	set_mono_font_type (MONO_FONT_TYPE_7X12);

	set_2d_mono_font_position (-1.0, 0.7);

	if (torque < 98)
	{
		set_mono_font_rel_position (1.0, -4.0);

		print_mono_font_string (s);
	}
	else
	{
		set_mono_font_rel_position (2.0, -4.0);

		get_mono_font_position (&x_min, &y_min);

		print_mono_font_string (s);

		width = get_mono_font_string_width (s);

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_waypoint_information (void)
{
	char
		buffer[80];

	entity
		*wp;

	vec3d
		*gunship_position,
		waypoint_position;

	float
		waypoint_range;

	wp = get_local_entity_current_waypoint (get_gunship_entity ());

	if (wp)
	{
		set_mono_font_type (MONO_FONT_TYPE_6X10);

		gunship_position = get_local_entity_vec3d_ptr (get_gunship_entity (), VEC3D_TYPE_POSITION);

		get_waypoint_display_position (get_gunship_entity (), wp, &waypoint_position);

		//
		// waypoint id & range
		//

		waypoint_range = get_2d_range (gunship_position, &waypoint_position);

		if (!apache_damage.navigation_computer)
		{
			if (waypoint_range < 1000.0)
			{
				sprintf (buffer, "%c:%dm", get_local_entity_char_value (wp, CHAR_TYPE_TAG), (int) waypoint_range);
			}
			else if (waypoint_range < 100000.0)
			{
				int
					i;

				float
					f;

				//
				// this is required to prevent rounding errors around the 100Km mark
				//

				i = (int) waypoint_range * (1.0 / 100.0);

				f = (float) i * (1.0 / 10.0);

				sprintf (buffer, "%c:%.1fKm", get_local_entity_char_value (wp, CHAR_TYPE_TAG), f);
			}
			else
			{
				sprintf (buffer, "%c:%dKm", get_local_entity_char_value (wp, CHAR_TYPE_TAG), (int) (waypoint_range * (1.0 / 1000.0)));
			}
		}
		else
		{
			sprintf (buffer, "-:--.-");
		}

		set_2d_mono_font_position (-1.0, -0.4);

		set_mono_font_rel_position (1.0, 0.0);

		print_mono_font_string (buffer);

		//
		// time to go
		//

		if ((current_flight_dynamics->velocity_z.value > 0.1) && (!apache_damage.navigation_computer))
		{
			float
				time_to_go,
				hours,
				minutes,
				seconds;

			time_to_go = waypoint_range / current_flight_dynamics->velocity_z.value;

			get_digital_clock_values (time_to_go, &hours, &minutes, &seconds);

			sprintf (buffer, "%02d:%02d:%02d", (int) hours, (int) minutes, (int) seconds);
		}
		else
		{
			strcpy (buffer, "--:--:--");
		}

		set_2d_mono_font_position (-1.0, -0.5);

		set_mono_font_rel_position (1.0, 0.0);

		print_mono_font_string (buffer);
	}
}

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
		set_mono_font_type (MONO_FONT_TYPE_6X7);

		//
		// selected weapon
		//

		count = get_local_entity_weapon_count (get_gunship_entity (), weapon_sub_type);

		sprintf (s, "%s %d", weapon_database[weapon_sub_type].hud_name, count);

		set_2d_mono_font_position (0.35, -0.7);

		set_mono_font_rel_position (1.0, 0.0);

		print_mono_font_string (s);

		//
		// weapon specific
		//

		if ((weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_AGM114L_LONGBOW_HELLFIRE) || (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_AGM114K_HELLFIRE_II))
		{
			set_2d_mono_font_position (0.35, -0.8);

			set_mono_font_rel_position (1.0, 0.0);

			if (!get_local_entity_int_value (get_gunship_entity (), INT_TYPE_LOCK_ON_AFTER_LAUNCH))
			{
				print_mono_font_string ("LOBL");
			}
			else
			{
				print_mono_font_string ("LOAL-HI");
			}

			flight_time = get_apache_missile_flight_time ();

			if (flight_time > 0.01)
			{
				flight_time = bound (flight_time, 0.0, 99.9);

				sprintf (s, "%.1f", flight_time);

				set_2d_mono_font_position (0.9, -0.8);

				set_mono_font_rel_position (0.8, 0.0);

				print_mono_font_string (s);
			}
		}
		else if ((weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255) || (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_HYDRA70_M261))
		{
			if (rocket_salvo_size == ROCKET_SALVO_SIZE_ALL)
			{
				sprintf (s, "Salvo:ALL");
			}
			else
			{
				sprintf (s, "Salvo:%d", rocket_salvo_size);
			}

			set_2d_mono_font_position (0.35, -0.8);

			set_mono_font_rel_position (1.0, 0.0);

			print_mono_font_string (s);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_target_marker (float x, float y)
{
	set_2d_pixel (x - 0.100, y, hud_colour);
	set_2d_pixel (x - 0.075, y, hud_colour);
	set_2d_pixel (x - 0.050, y, hud_colour);
	set_2d_pixel (x - 0.025, y, hud_colour);

	set_2d_pixel (x + 0.025, y, hud_colour);
	set_2d_pixel (x + 0.050, y, hud_colour);
	set_2d_pixel (x + 0.075, y, hud_colour);
	set_2d_pixel (x + 0.100, y, hud_colour);

	set_2d_pixel (x, y - 0.100, hud_colour);
	set_2d_pixel (x, y - 0.075, hud_colour);
	set_2d_pixel (x, y - 0.050, hud_colour);
	set_2d_pixel (x, y - 0.025, hud_colour);

	set_2d_pixel (x, y + 0.025, hud_colour);
	set_2d_pixel (x, y + 0.050, hud_colour);
	set_2d_pixel (x, y + 0.075, hud_colour);
	set_2d_pixel (x, y + 0.100, hud_colour);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_dashed_i_beam (float x, float y)
{
	draw_2d_line (x - 0.1000 + 0.0125, y + 0.2, x - 0.0500 - 0.0125, y + 0.2, hud_colour);
	draw_2d_line (x - 0.0500 + 0.0125, y + 0.2, x - 0.0000 - 0.0125, y + 0.2, hud_colour);

	draw_2d_line (x + 0.1000 - 0.0125, y + 0.2, x + 0.0500 + 0.0125, y + 0.2, hud_colour);
	draw_2d_line (x + 0.0500 - 0.0125, y + 0.2, x + 0.0000 + 0.0125, y + 0.2, hud_colour);

	draw_2d_line (x, y + 0.2000 - 0.0125, x, y + 0.1500 + 0.0125, hud_colour);
	draw_2d_line (x, y + 0.1500 - 0.0125, x, y + 0.1000 + 0.0125, hud_colour);
	draw_2d_line (x, y + 0.1000 - 0.0125, x, y + 0.0500 + 0.0125, hud_colour);
	draw_2d_line (x, y + 0.0500 - 0.0125, x, y + 0.0000 + 0.0125, hud_colour);

	draw_2d_line (x, y - 0.2000 + 0.0125, x, y - 0.1500 - 0.0125, hud_colour);
	draw_2d_line (x, y - 0.1500 + 0.0125, x, y - 0.1000 - 0.0125, hud_colour);
	draw_2d_line (x, y - 0.1000 + 0.0125, x, y - 0.0500 - 0.0125, hud_colour);
	draw_2d_line (x, y - 0.0500 + 0.0125, x, y - 0.0000 - 0.0125, hud_colour);

	draw_2d_line (x - 0.1000 + 0.0125, y - 0.2, x - 0.0500 - 0.0125, y - 0.2, hud_colour);
	draw_2d_line (x - 0.0500 + 0.0125, y - 0.2, x - 0.0000 - 0.0125, y - 0.2, hud_colour);

	draw_2d_line (x + 0.1000 - 0.0125, y - 0.2, x + 0.0500 + 0.0125, y - 0.2, hud_colour);
	draw_2d_line (x + 0.0500 - 0.0125, y - 0.2, x + 0.0000 + 0.0125, y - 0.2, hud_colour);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_solid_i_beam (float x, float y)
{
	draw_2d_line (x - 0.1000 + 0.0125, y + 0.2, x - 0.0000 - 0.0125, y + 0.2, hud_colour);

	draw_2d_line (x + 0.1000 - 0.0125, y + 0.2, x + 0.0000 + 0.0125, y + 0.2, hud_colour);

	draw_2d_line (x, y + 0.2000 - 0.0125, x, y + 0.1000 + 0.0125, hud_colour);

	draw_2d_line (x, y - 0.2000 + 0.0125, x, y - 0.1000 - 0.0125, hud_colour);

	draw_2d_line (x - 0.1000 + 0.0125, y - 0.2, x - 0.0000 - 0.0125, y - 0.2, hud_colour);

	draw_2d_line (x + 0.1000 - 0.0125, y - 0.2, x + 0.0000 + 0.0125, y - 0.2, hud_colour);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_dashed_stinger_target_marker (float x, float y)
{
	float
		theta,
		x1,
		y1,
		x2,
		y2,
		x3,
		y3;

	theta = rad (0.0);

	while (theta < rad (360.0))
	{
		x1 = x + (0.2 * sin (theta));
		y1 = y + (0.2 * cos (theta));

		theta += rad (7.5);

		x2 = x + (0.2 * sin (theta));
		y2 = y + (0.2 * cos (theta));

		theta += rad (7.5);

		x3 = x + (0.2 * sin (theta));
		y3 = y + (0.2 * cos (theta));

		theta += rad (15.0);

		draw_2d_line (x1, y1, x2, y2, hud_colour);

		draw_2d_line (x2, y2, x3, y3, hud_colour);
	}

	theta = rad (15.0);

	while (theta < rad (360.0))
	{
		x1 = x + (0.1 * sin (theta));
		y1 = y + (0.1 * cos (theta));

		theta += rad (15.0);

		x2 = x + (0.1 * sin (theta));
		y2 = y + (0.1 * cos (theta));

		theta += rad (15.0);

		draw_2d_line (x1, y1, x2, y2, hud_colour);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_solid_stinger_target_marker (float x, float y)
{
	draw_2d_circle (x, y, 0.2, hud_colour);

	draw_2d_circle (x, y, 0.1, hud_colour);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_dashed_gun_target_marker (float x, float y)
{
	draw_2d_line (x - 0.1000, y + 0.1, x - 0.0788, y + 0.1, hud_colour);
	draw_2d_line (x - 0.0556, y + 0.1, x - 0.0334, y + 0.1, hud_colour);
	draw_2d_line (x - 0.0112, y + 0.1, x + 0.0110, y + 0.1, hud_colour);
	draw_2d_line (x + 0.0332, y + 0.1, x + 0.0554, y + 0.1, hud_colour);
	draw_2d_line (x + 0.0776, y + 0.1, x + 0.1000, y + 0.1, hud_colour);

	draw_2d_line (x - 0.1000, y - 0.1, x - 0.0788, y - 0.1, hud_colour);
	draw_2d_line (x - 0.0556, y - 0.1, x - 0.0334, y - 0.1, hud_colour);
	draw_2d_line (x - 0.0112, y - 0.1, x + 0.0110, y - 0.1, hud_colour);
	draw_2d_line (x + 0.0332, y - 0.1, x + 0.0554, y - 0.1, hud_colour);
	draw_2d_line (x + 0.0776, y - 0.1, x + 0.1000, y - 0.1, hud_colour);

	draw_2d_line (x + 0.1, y - 0.1000, x + 0.1, y - 0.0788, hud_colour);
	draw_2d_line (x + 0.1, y - 0.0556, x + 0.1, y - 0.0334, hud_colour);
	draw_2d_line (x + 0.1, y - 0.0112, x + 0.1, y + 0.0110, hud_colour);
	draw_2d_line (x + 0.1, y + 0.0332, x + 0.1, y + 0.0554, hud_colour);
	draw_2d_line (x + 0.1, y + 0.0776, x + 0.1, y + 0.1000, hud_colour);

	draw_2d_line (x - 0.1, y - 0.1000, x - 0.1, y - 0.0788, hud_colour);
	draw_2d_line (x - 0.1, y - 0.0556, x - 0.1, y - 0.0334, hud_colour);
	draw_2d_line (x - 0.1, y - 0.0112, x - 0.1, y + 0.0110, hud_colour);
	draw_2d_line (x - 0.1, y + 0.0332, x - 0.1, y + 0.0554, hud_colour);
	draw_2d_line (x - 0.1, y + 0.0776, x - 0.1, y + 0.1000, hud_colour);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_solid_gun_target_marker (float x, float y)
{
	draw_2d_line (x - 0.1, y + 0.1, x + 0.1, y + 0.1, hud_colour);
	draw_2d_line (x + 0.1, y + 0.1, x + 0.1, y - 0.1, hud_colour);
	draw_2d_line (x + 0.1, y - 0.1, x - 0.1, y - 0.1, hud_colour);
	draw_2d_line (x - 0.1, y - 0.1, x - 0.1, y + 0.1, hud_colour);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_hellfire_lobl_dashed_target_marker (float x, float y)
{
	draw_2d_line (x - 0.15000, y + 0.15000, x - 0.13125, y + 0.15000, hud_colour);
	draw_2d_line (x - 0.09375, y + 0.15000, x - 0.05626, y + 0.15000, hud_colour);
	draw_2d_line (x - 0.01875, y + 0.15000, x + 0.01875, y + 0.15000, hud_colour);
	draw_2d_line (x + 0.05625, y + 0.15000, x + 0.09375, y + 0.15000, hud_colour);
	draw_2d_line (x + 0.13125, y + 0.15000, x + 0.15000, y + 0.15000, hud_colour);

	draw_2d_line (x - 0.15000, y - 0.15000, x - 0.13125, y - 0.15000, hud_colour);
	draw_2d_line (x - 0.09375, y - 0.15000, x - 0.05626, y - 0.15000, hud_colour);
	draw_2d_line (x - 0.01875, y - 0.15000, x + 0.01875, y - 0.15000, hud_colour);
	draw_2d_line (x + 0.05625, y - 0.15000, x + 0.09375, y - 0.15000, hud_colour);
	draw_2d_line (x + 0.13125, y - 0.15000, x + 0.15000, y - 0.15000, hud_colour);

	draw_2d_line (x + 0.15000, y - 0.15000, x + 0.15000, y - 0.13125, hud_colour);
	draw_2d_line (x + 0.15000, y - 0.09375, x + 0.15000, y - 0.05626, hud_colour);
	draw_2d_line (x + 0.15000, y - 0.01875, x + 0.15000, y + 0.01875, hud_colour);
	draw_2d_line (x + 0.15000, y + 0.05625, x + 0.15000, y + 0.09375, hud_colour);
	draw_2d_line (x + 0.15000, y + 0.13125, x + 0.15000, y + 0.15000, hud_colour);

	draw_2d_line (x - 0.15000, y - 0.15000, x - 0.15000, y - 0.13125, hud_colour);
	draw_2d_line (x - 0.15000, y - 0.09375, x - 0.15000, y - 0.05626, hud_colour);
	draw_2d_line (x - 0.15000, y - 0.01875, x - 0.15000, y + 0.01875, hud_colour);
	draw_2d_line (x - 0.15000, y + 0.05625, x - 0.15000, y + 0.09375, hud_colour);
	draw_2d_line (x - 0.15000, y + 0.13125, x - 0.15000, y + 0.15000, hud_colour);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_hellfire_lobl_solid_target_marker (float x, float y)
{
	draw_2d_line (x - 0.15, y + 0.15, x + 0.15, y + 0.15, hud_colour);
	draw_2d_line (x + 0.15, y + 0.15, x + 0.15, y - 0.15, hud_colour);
	draw_2d_line (x + 0.15, y - 0.15, x - 0.15, y - 0.15, hud_colour);
	draw_2d_line (x - 0.15, y - 0.15, x - 0.15, y + 0.15, hud_colour);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_hellfire_loal_dashed_target_marker (float x, float y)
{
	x = bound (x, -0.295, 0.295);
	y = bound (y, -0.295, 0.295);

	draw_2d_line (x - 0.70, y + 0.70, x - 0.65, y + 0.70, hud_colour);
	draw_2d_line (x - 0.55, y + 0.70, x - 0.45, y + 0.70, hud_colour);
	draw_2d_line (x - 0.35, y + 0.70, x - 0.25, y + 0.70, hud_colour);
	draw_2d_line (x - 0.15, y + 0.70, x - 0.05, y + 0.70, hud_colour);
	draw_2d_line (x + 0.05, y + 0.70, x + 0.15, y + 0.70, hud_colour);
	draw_2d_line (x + 0.25, y + 0.70, x + 0.35, y + 0.70, hud_colour);
	draw_2d_line (x + 0.45, y + 0.70, x + 0.55, y + 0.70, hud_colour);
	draw_2d_line (x + 0.65, y + 0.70, x + 0.70, y + 0.70, hud_colour);

	draw_2d_line (x - 0.70, y - 0.70, x - 0.65, y - 0.70, hud_colour);
	draw_2d_line (x - 0.55, y - 0.70, x - 0.45, y - 0.70, hud_colour);
	draw_2d_line (x - 0.35, y - 0.70, x - 0.25, y - 0.70, hud_colour);
	draw_2d_line (x - 0.15, y - 0.70, x - 0.05, y - 0.70, hud_colour);
	draw_2d_line (x + 0.05, y - 0.70, x + 0.15, y - 0.70, hud_colour);
	draw_2d_line (x + 0.25, y - 0.70, x + 0.35, y - 0.70, hud_colour);
	draw_2d_line (x + 0.45, y - 0.70, x + 0.55, y - 0.70, hud_colour);
	draw_2d_line (x + 0.65, y - 0.70, x + 0.70, y - 0.70, hud_colour);

	draw_2d_line (x + 0.70, y - 0.70, x + 0.70, y - 0.65, hud_colour);
	draw_2d_line (x + 0.70, y - 0.55, x + 0.70, y - 0.45, hud_colour);
	draw_2d_line (x + 0.70, y - 0.35, x + 0.70, y - 0.25, hud_colour);
	draw_2d_line (x + 0.70, y - 0.15, x + 0.70, y - 0.05, hud_colour);
	draw_2d_line (x + 0.70, y + 0.05, x + 0.70, y + 0.15, hud_colour);
	draw_2d_line (x + 0.70, y + 0.25, x + 0.70, y + 0.35, hud_colour);
	draw_2d_line (x + 0.70, y + 0.45, x + 0.70, y + 0.55, hud_colour);
	draw_2d_line (x + 0.70, y + 0.65, x + 0.70, y + 0.70, hud_colour);

	draw_2d_line (x - 0.70, y - 0.70, x - 0.70, y - 0.65, hud_colour);
	draw_2d_line (x - 0.70, y - 0.55, x - 0.70, y - 0.45, hud_colour);
	draw_2d_line (x - 0.70, y - 0.35, x - 0.70, y - 0.25, hud_colour);
	draw_2d_line (x - 0.70, y - 0.15, x - 0.70, y - 0.05, hud_colour);
	draw_2d_line (x - 0.70, y + 0.05, x - 0.70, y + 0.15, hud_colour);
	draw_2d_line (x - 0.70, y + 0.25, x - 0.70, y + 0.35, hud_colour);
	draw_2d_line (x - 0.70, y + 0.45, x - 0.70, y + 0.55, hud_colour);
	draw_2d_line (x - 0.70, y + 0.65, x - 0.70, y + 0.70, hud_colour);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_hellfire_loal_solid_target_marker (float x, float y)
{
	x = bound (x, -0.295, 0.295);
	y = bound (y, -0.295, 0.295);

	draw_2d_line (x - 0.7, y + 0.7, x + 0.7, y + 0.7, hud_colour);
	draw_2d_line (x + 0.7, y + 0.7, x + 0.7, y - 0.7, hud_colour);
	draw_2d_line (x + 0.7, y - 0.7, x - 0.7, y - 0.7, hud_colour);
	draw_2d_line (x - 0.7, y - 0.7, x - 0.7, y + 0.7, hud_colour);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_airborne_target_computed_intercept_point (float x, float y)
{
	draw_2d_line (x - 0.05, y, x + 0.05, y, hud_colour);
	draw_2d_line (x, y - 0.05, x, y + 0.05, hud_colour);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_target_symbology (void)
{
	int
		target_visible;

	entity_sub_types
		selected_weapon_type;

	object_3d_visibility
		visibility;

	float
		i,
		j,
		target_x,
		target_y,
		intercept_point_x,
		intercept_point_y,
		heading_offset,
		pitch_offset;

	entity
		*source,
		*target;

	vec3d
		target_position,
		intercept_point;

	source = get_gunship_entity ();

	selected_weapon_type = get_local_entity_int_value (source, INT_TYPE_SELECTED_WEAPON);

	if (selected_weapon_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
	{
		target = get_local_entity_parent (source, LIST_TYPE_TARGET);

		target_visible = FALSE;

		if (target)
		{
			//
			// draw target marker
			//

			get_local_entity_target_point (target, &target_position);

			visibility = get_position_3d_screen_coordinates (&target_position, &i, &j);

			if ((visibility == OBJECT_3D_COMPLETELY_VISIBLE) || (visibility == OBJECT_3D_PARTIALLY_VISIBLE))
			{
				target_visible = TRUE;

				transform_hud_screen_co_ords_to_hud_texture_co_ords (&i, &j);

				get_2d_world_position (i, j, &target_x, &target_y);

				clip_2d_point_to_hud_extent (&target_x, &target_y);

				draw_target_marker (target_x, target_y);
			}
		}

		switch (selected_weapon_type)
		{
			////////////////////////////////////////
			case ENTITY_SUB_TYPE_WEAPON_M230_30MM_ROUND:
			////////////////////////////////////////
			{
				if (target_visible)
				{
					if (weapon_lock_type == WEAPON_LOCK_VALID)
					{
						draw_solid_gun_target_marker (target_x, target_y);
					}
					else
					{
						draw_dashed_gun_target_marker (target_x, target_y);
					}
				}

				break;
			}
			////////////////////////////////////////
			case ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255:
			case ENTITY_SUB_TYPE_WEAPON_HYDRA70_M261:
			////////////////////////////////////////
			{
				if (target_visible)
				{
					if (get_local_entity_int_value (target, INT_TYPE_AIRBORNE_AIRCRAFT))
					{
						get_target_intercept_point (source, target, selected_weapon_type, &intercept_point);

						visibility = get_position_3d_screen_coordinates (&intercept_point, &i, &j);

						if ((visibility == OBJECT_3D_COMPLETELY_VISIBLE) || (visibility == OBJECT_3D_PARTIALLY_VISIBLE))
						{
							transform_hud_screen_co_ords_to_hud_texture_co_ords (&i, &j);

							get_2d_world_position (i, j, &intercept_point_x, &intercept_point_y);

							clip_2d_point_to_hud_extent (&intercept_point_x, &intercept_point_y);

							draw_airborne_target_computed_intercept_point (intercept_point_x, intercept_point_y);
						}
					}

					if (get_local_entity_selected_weapon_to_target_offsets (source, &heading_offset, &pitch_offset))
					{
						heading_offset = bound (heading_offset, rad (-10.0), rad (10.0));

						heading_offset *= 0.7 / 0.17453293;	// rad (10.0)

						pitch_offset = bound (pitch_offset, rad (-5.0), rad (5.0));

						pitch_offset *= 0.35 / 0.08726646;	// rad (5.0)

						if (weapon_lock_type == WEAPON_LOCK_VALID)
						{
							draw_solid_i_beam (heading_offset, pitch_offset);
						}
						else
						{
							draw_dashed_i_beam (heading_offset, pitch_offset);
						}
					}
					else
					{
						//
						// this should never happen
						//

						debug_colour_log (DEBUG_COLOUR_RED, "WARNING! get_local_entity_selected_weapon_to_target_offsets failed");
					}
				}

				break;
			}
			////////////////////////////////////////
			case ENTITY_SUB_TYPE_WEAPON_AGM114L_LONGBOW_HELLFIRE:
			case ENTITY_SUB_TYPE_WEAPON_AGM114K_HELLFIRE_II:
			////////////////////////////////////////
			{
				if (!get_local_entity_int_value (source, INT_TYPE_LOCK_ON_AFTER_LAUNCH))
				{
					if (target_visible)
					{
						if (weapon_lock_type == WEAPON_LOCK_VALID)
						{
							draw_hellfire_lobl_solid_target_marker (target_x, target_y);
						}
						else
						{
							draw_hellfire_lobl_dashed_target_marker (target_x, target_y);
						}
					}
				}
				else
				{
					if (target_visible)
					{
						if (weapon_lock_type == WEAPON_LOCK_VALID)
						{
							draw_hellfire_loal_solid_target_marker (target_x, target_y);
						}
						else
						{
							draw_hellfire_loal_dashed_target_marker (target_x, target_y);
						}
					}
					else
					{
						draw_hellfire_loal_dashed_target_marker (0.0, 0.0);
					}
				}

				break;
			}
			////////////////////////////////////////
			case ENTITY_SUB_TYPE_WEAPON_AIM92_STINGER:
			////////////////////////////////////////
			{
				if ((weapon_lock_type == WEAPON_LOCK_VALID) && target_visible)
				{
					draw_solid_stinger_target_marker (target_x, target_y);
				}
				else
				{
					draw_dashed_stinger_target_marker (apache_stinger_seeker_head_x_position, apache_stinger_seeker_head_y_position);
				}

				break;
			}
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
		width,
		target_range;

	entity
		*target;

	vec3d
		*gunship_position,
		*target_position;

	int
		has_range = get_range_finder() != RANGEFINDER_TRIANGULATION;

	set_mono_font_type (MONO_FONT_TYPE_6X7);

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
		if (has_range)
		{
			s = "MIN RANGE";

			break;
		}
		// fallthrough
		////////////////////////////////////////
		case WEAPON_LOCK_MAX_RANGE:
		////////////////////////////////////////
		if (has_range)
		{
			s = "MAX RANGE";

			break;
		}
		// fallthrough
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

	set_2d_mono_font_position (0.0, -0.6);

	set_mono_font_rel_position (-width * 0.5, -9.0);

	print_mono_font_string (s);

	//
	// target name and range
	//

	target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

	if (target && s)
	{
		s = get_target_display_name (target, buffer, TRUE);
		if (s)
		{
			width = get_mono_font_string_width (s);
	
			set_2d_mono_font_position (0.0, -0.8);
	
			set_mono_font_rel_position (-width * 0.5, 8.0);
	
			print_mono_font_string (s);
		}

		gunship_position = get_local_entity_vec3d_ptr (get_gunship_entity (), VEC3D_TYPE_POSITION);
		target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);
	
		target_range = get_3d_range (gunship_position, target_position);
	}
	
	switch (target_acquisition_system)
	{
	case TARGET_ACQUISITION_SYSTEM_GROUND_RADAR:
	case TARGET_ACQUISITION_SYSTEM_AIR_RADAR:
		s = "FCR";
		if (target)
			sprintf(buffer, "R%.1f", target_range * 0.001);
		else
			sprintf(buffer, "AX.X");
		break;
	case TARGET_ACQUISITION_SYSTEM_FLIR:
	case TARGET_ACQUISITION_SYSTEM_DTV:
	case TARGET_ACQUISITION_SYSTEM_DVO:
	case TARGET_ACQUISITION_SYSTEM_IHADSS:
		s = "TADS";
		if (target)
		{
			if (laser_is_active())
				sprintf(buffer, "L%04.0f", target_range);
			else
			{
				float range = get_triangulated_range(target);
				if (range > 0)
					sprintf(buffer, "A%.1f", range * 0.001);
				else
					sprintf(buffer, "AX.X");
			}
		}
		else
			sprintf(buffer, "AX.X");
		break;
	case TARGET_ACQUISITION_SYSTEM_OFF:
	default:
		s = "NONE";
		sprintf(buffer, "AX.X");
		break;
	}

	set_2d_mono_font_position (-0.95, -0.7);
	width = 0; //get_mono_font_string_width (s) * -0.5;
	set_mono_font_rel_position (width, 0);
	print_mono_font_string (s);

	set_2d_mono_font_position (-0.35, -0.7);
	width = -get_mono_font_string_width (buffer); // * 0.5;
	set_mono_font_rel_position (width, 0);
	print_mono_font_string (buffer);

	// target system emmision
	set_2d_mono_font_position (-0.35, -0.8);

	switch (target_acquisition_system)
	{
		case TARGET_ACQUISITION_SYSTEM_GROUND_RADAR:
		case TARGET_ACQUISITION_SYSTEM_AIR_RADAR:
			if ((air_radar_is_active() && air_radar.sweep_mode != RADAR_SWEEP_MODE_SINGLE_INACTIVE)
				|| (ground_radar_is_active() && ground_radar.sweep_mode != RADAR_SWEEP_MODE_SINGLE_INACTIVE))
			{
				if (laser_is_active())
					s = "LASE/FCR";
				else
					s = "FCR XMIT";
				
				width = -get_mono_font_string_width (s);
				set_mono_font_rel_position (width, 0);
				print_mono_font_string(s);

				break;
			}
			
			// fall through
		case TARGET_ACQUISITION_SYSTEM_FLIR:
		case TARGET_ACQUISITION_SYSTEM_DTV:
		case TARGET_ACQUISITION_SYSTEM_DVO:
		case TARGET_ACQUISITION_SYSTEM_IHADSS:
			if (laser_is_active())
			{
				s = "TGT LASE";
				width = -get_mono_font_string_width (s);
				set_mono_font_rel_position (width, 0);
				print_mono_font_string(s);
			}
			break;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_field_of_view_and_regard_boxes (void)
{
	float x, y, slip;

	slip = bound(current_flight_dynamics->velocity_x.value, -10.0, 10.0);
	slip *= 0.01;

	// slip indicator
	draw_2d_circle(slip, -0.6400, 0.0350, hud_colour);
	draw_2d_line (0.0350, -0.6750,  0.0350, -0.6050, hud_colour);
	draw_2d_line (-0.0350, -0.6750, -0.0350, -0.6050, hud_colour);

	// box
	draw_2d_line (-0.3000, -0.6750,  0.3000, -0.6750, hud_colour);
	draw_2d_line (-0.3000, -0.8250,  0.3000, -0.8250, hud_colour);
	draw_2d_line (-0.3000, -0.6750, -0.3000, -0.8250, hud_colour);
	draw_2d_line ( 0.3000, -0.6750,  0.3000, -0.8250, hud_colour);

	// horizontal center tick marks
	draw_2d_line ( 0.0000, -0.6750,  0.0000, -0.6900, hud_colour);
	draw_2d_line ( 0.0000, -0.8250,  0.0000, -0.8100, hud_colour);

	// 90 deg right tick marks
	draw_2d_line ( 0.2250, -0.6750,  0.2250, -0.6900, hud_colour);
	draw_2d_line ( 0.2250, -0.8250,  0.2250, -0.8100, hud_colour);

	// 90 deg left tick marks
	draw_2d_line (-0.2250, -0.6750, -0.2250, -0.6900, hud_colour);
	draw_2d_line (-0.2250, -0.8250, -0.2250, -0.8100, hud_colour);

	// vertical center tick marks
	draw_2d_line (-0.3000, -0.7250, -0.2775, -0.7250, hud_colour);
	draw_2d_line ( 0.3000, -0.7250,  0.2775, -0.7250, hud_colour);

	x = eo_azimuth / eo_max_azimuth * 0.3;

	y = (eo_elevation / eo_min_elevation * -0.10) - 0.7250;

	draw_2d_line (x - 0.0400, y - 0.0250, x + 0.0400, y - 0.0250, hud_colour);
	draw_2d_line (x - 0.0400, y + 0.0250, x + 0.0400, y + 0.0250, hud_colour);
	draw_2d_line (x - 0.0400, y - 0.0250, x - 0.0400, y + 0.0250, hud_colour);
	draw_2d_line (x + 0.0400, y - 0.0250, x + 0.0400, y + 0.0250, hud_colour);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// arneh, june 2006. Improved to include acceleration cue
static void draw_velocity_vector()
{
#define VV_CUTOFF_VELOCITY 10.0
	float scale, x, z, dx, dz;
	
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

	// from center use 70% of the hud area
	scale = (0.7 / VV_CUTOFF_VELOCITY);

	x *= scale;
	z *= scale;

	draw_2d_line(0.0, 0.0, x, z, hud_colour);
	// draw a little plus at the end
	draw_2d_line(x, z - 0.01, x, z + 0.01, hud_colour);
	draw_2d_line(x - 0.01, z, x + 0.01, z, hud_colour);

	// draw acceleration cue
	if (current_flight_dynamics->radar_altitude.value > 0.1)
	{
		dx = current_flight_dynamics->model_acceleration_vector.x / 40.0;
		dz = current_flight_dynamics->model_acceleration_vector.z / 20.0;
	}
	else  // the acceleration vector doesn't work on the ground (it apparently 
	      // assumes no ground interfers with the acceleration :)
		dx = dz = 0.0;
	
	draw_2d_circle(bound(x+dx, -0.8, 0.8), bound(z+dz, -0.8, 0.8), 0.04, hud_colour);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_bob_up_overlay (void)
{
	float
		heading,
		dx,
		dz,
		dxt,
		dzt;

	vec3d *position;

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
			if (hud_bob_up_overlay)
			{
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
			}
			
			draw_velocity_vector();
		}
		else
		{
			clear_hud_bob_up_overlay ();
		}
	}
}

/*
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

			if ((length < knots_to_metres_per_second (-0.1)) || (length > knots_to_metres_per_second (0.1)))
			{
				length = min (length, knots_to_metres_per_second (10.0));

				length *= 0.5 / knots_to_metres_per_second (10.0);

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

			length = max (length - 0.0075, 0.0);

			draw_2d_line (-0.0075, length, 0.0075, length, hud_colour);

			set_2d_window_rotation (hud_env, 0.0);
		}
		else
		{
			clear_hud_bob_up_overlay ();
		}
	}
}
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_cockpit_look_ahead (void)
{
	int
		look_ahead;

	look_ahead = FALSE;

	if (in_cockpit)
	{
		switch (get_view_mode ())
		{
			case VIEW_MODE_COCKPIT_PANEL_LEVEL_AHEAD:
			case VIEW_MODE_COCKPIT_PANEL_DOWN20_AHEAD:
			{
				look_ahead = TRUE;

				break;
			}
			case VIEW_MODE_VIRTUAL_COCKPIT:
			case VIEW_MODE_VIRTUAL_COCKPIT_PADLOCK:
			case VIEW_MODE_VIRTUAL_COCKPIT_TRACK_TARGET:
			{
				if
				(
					(pilot_head_heading >= rad (-26.57)) &&
					(pilot_head_heading <= rad (26.57)) &&
					(pilot_head_pitch >= rad (-26.57)) &&
					(pilot_head_pitch <= rad (26.57))
				)
				{
					look_ahead = TRUE;
				}

				break;
			}
		}
	}
	else
	{
		look_ahead = TRUE;
	}

	return (look_ahead);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_navigation_mode_hud (void)
{
	draw_hud_centre_datum ();

	draw_heading_scale ();

	if (get_cockpit_look_ahead ())
	{
		draw_pitch_ladder (FALSE);

		draw_bank_scale ();
	}

	display_true_airspeed ();

	display_barometric_altitude ();

	draw_rate_of_climb_scale ();

	display_engine_torque ();

	display_waypoint_information ();

	display_target_information ();

	draw_field_of_view_and_regard_boxes ();

	draw_bob_up_overlay ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// arneh, june 2006 - added transition mode hud
static void draw_transition_mode_hud (void)
{
	draw_hud_centre_datum ();

	draw_flight_path_marker ();
	
	if (!hud_bob_up_overlay)
		draw_velocity_vector();
	
	draw_heading_scale ();

	display_true_airspeed ();

	draw_rate_of_climb_scale ();

	display_engine_torque ();

	display_waypoint_information ();

	display_target_information ();

	draw_field_of_view_and_regard_boxes ();

	draw_bob_up_overlay ();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_weapon_mode_hud (void)
{
	draw_hud_centre_datum ();

	draw_heading_scale ();

	if (get_cockpit_look_ahead ())
	{
		if (previous_hud_mode == HUD_MODE_NAVIGATION)
			draw_pitch_ladder (TRUE);
		else
			draw_flight_path_marker();
	}

	display_true_airspeed ();

	draw_rate_of_climb_scale ();

	display_engine_torque ();

	draw_target_symbology ();

	display_weapon_information ();

	display_target_information ();

	draw_field_of_view_and_regard_boxes ();

	draw_bob_up_overlay ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_apache_hud (void)
{
	hud_env = create_2d_environment ();

	hud_texture_screen = create_system_texture_screen (HUD_VIEWPORT_SIZE, HUD_VIEWPORT_SIZE, HUD_TEXTURE_INDEX, TEXTURE_TYPE_SINGLEALPHA);

	clear_hud_colour.r = 255;
	clear_hud_colour.g = 255;
	clear_hud_colour.b = 255;
	clear_hud_colour.a = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_apache_hud (void)
{
	destroy_2d_environment (hud_env);

	destroy_screen (hud_texture_screen);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_apache_hud (void)
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
	// do not draw damaged HUD
	//
	////////////////////////////////////////

	if (apache_damage.ihadss)
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
				heading_offset = APACHE_INSTRUMENT_VIEW_HEADING - pilot_head_heading;

				if (heading_offset < 0.0)
				{
					heading_offset = -heading_offset;
				}

				pitch_offset = APACHE_INSTRUMENT_VIEW_PITCH - pilot_head_pitch;

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
				if ((pilot_head_heading == APACHE_INSTRUMENT_VIEW_HEADING) && (pilot_head_pitch == APACHE_INSTRUMENT_VIEW_PITCH))
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

//VJ 050126 hud mod start
/*
	hud_viewport_x_org = HUD_VIEWPORT_SIZE * 0.5;

	hud_viewport_y_org = HUD_VIEWPORT_SIZE * 0.5;

	hud_viewport_x_min = 0.0;

	hud_viewport_y_min = 0.0;

	hud_viewport_x_max = HUD_VIEWPORT_SIZE - 0.001;

	hud_viewport_y_max = HUD_VIEWPORT_SIZE - 0.001;
*/
	hud_viewport_size = HUD_VIEWPORT_SIZE * min( 1.0, global_hud_size2); //VJ
   
	hud_viewport_x_org = hud_viewport_size * 0.5;
   
	hud_viewport_y_org = hud_viewport_size * 0.5;

	hud_viewport_x_min = (HUD_VIEWPORT_SIZE - hud_viewport_size)*0.5;

	hud_viewport_y_min = (HUD_VIEWPORT_SIZE - hud_viewport_size)*0.5;

	hud_viewport_x_max = HUD_VIEWPORT_SIZE - hud_viewport_x_min-0.001;
   
	hud_viewport_y_max = HUD_VIEWPORT_SIZE - hud_viewport_y_min-0.001;

//VJ 050126 hud mod end

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
		//VJ 050210, 060913 scaling factor for hud > 1.0
		float scale = 4.35 - 2.5*global_hud_size2;			 
		hud_screen_x_min = full_screen_x_mid - ((256.0 / (scale*640.0 * 2.0)) * full_screen_width);
		hud_screen_y_min = full_screen_y_mid - ((256.0 / (scale*480.0 * 2.0)) * full_screen_height);

		hud_screen_x_max = full_screen_x_mid + ((256.0 / (scale*640.0 * 2.0)) * full_screen_width) - 0.001;
		hud_screen_y_max = full_screen_y_mid + ((256.0 / (scale*480.0 * 2.0)) * full_screen_height) - 0.001;

		hud_screen_x_scale = scale*640.0 / full_screen_width;
		hud_screen_y_scale = scale*480.0 / full_screen_height;

	}

//VJ 050126 hud mod start 
	hsd.hud_viewport_x_min = hud_viewport_x_min; 
	hsd.hud_viewport_y_min = hud_viewport_y_min; 
	hsd.hud_viewport_x_max = hud_viewport_x_max; 
	hsd.hud_viewport_y_max = hud_viewport_y_max; 
	hsd.hud_screen_x_min = hud_screen_x_min;   
	hsd.hud_screen_y_min = hud_screen_y_min;   
	hsd.hud_screen_x_max = hud_screen_x_max;   
	hsd.hud_screen_y_max = hud_screen_y_max;   
	hsd.hud_texture_screen = hud_texture_screen;
	
   draw_hud_background (&hsd, alpha );
//VJ 050126 hud mod end

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

		set_block (0, 0, HUD_VIEWPORT_SIZE - 1, HUD_VIEWPORT_SIZE - 1, clear_hud_colour);

		draw_layout_grid ();

		switch (hud_mode)
		{
			case HUD_MODE_TRANSITION:
			{
				draw_transition_mode_hud();

				break;
			}
			case HUD_MODE_NAVIGATION:
			{
				draw_navigation_mode_hud ();

				break;
			}
			case HUD_MODE_WEAPON:
			{
				draw_weapon_mode_hud ();

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

		set_d3d_flat_shaded_textured_renderstate (get_system_texture_ptr (HUD_TEXTURE_INDEX));

		////////////////////////////////////////
		//

		colour.red	  			= hud_colour_table[get_global_hud_colour ()].r;
		colour.green 			= hud_colour_table[get_global_hud_colour ()].g;
		colour.blue	 			= hud_colour_table[get_global_hud_colour ()].b;
		colour.alpha			= alpha;

		specular.red  			= 0;
		specular.green			= 0;
		specular.blue			= 0;
		specular.alpha			= 255;

		quad[0].i				= hud_screen_x_min;
		quad[0].j	  			= hud_screen_y_min;
		quad[0].z	  			= 0.5;
		quad[0].q	  			= 0.5;
		quad[0].u	  			= 0.0;
		quad[0].v	  			= 0.0;

		quad[1].i  				= hud_screen_x_max;
		quad[1].j  				= hud_screen_y_min;
		quad[1].z  				= 0.5;
		quad[1].q  				= 0.5;
		quad[1].u  				= 1.0;
		quad[1].v  				= 0.0;

		quad[2].i				= hud_screen_x_max;
		quad[2].j  				= hud_screen_y_max;
		quad[2].z  				= 0.5;
		quad[2].q  				= 0.5;
		quad[2].u  				= 1.0;
		quad[2].v  				= 1.0;

		quad[3].i				= hud_screen_x_min;
		quad[3].j				= hud_screen_y_max;
		quad[3].z				= 0.5;
		quad[3].q				= 0.5;
		quad[3].u				= 0.0;
		quad[3].v				= 1.0;

		quad[0].next_vertex 	= &quad[1];
		quad[1].next_vertex 	= &quad[2];
		quad[2].next_vertex 	= &quad[3];
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
