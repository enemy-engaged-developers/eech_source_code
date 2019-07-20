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
void copy_export_mfd(screen* export_left, screen* export_right);

static mfd_modes
	mfd_mode;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static rgb_colour
	mfd_colours[15],					//  Javelin  6/19
	clear_hud_colour;					//  Javelin  7/19


#define MFD_COLOUR1 (mfd_colours[0])
#define MFD_COLOUR2 (mfd_colours[1])
#define MFD_COLOUR3 (mfd_colours[2])
#define MFD_COLOUR4 (mfd_colours[3])
#define MFD_COLOUR5 (mfd_colours[4])
#define MFD_COLOUR6 (mfd_colours[5])
#define MFD_COLOUR_RED (mfd_colours[6])
#define MFD_COLOUR_GREEN (mfd_colours[7])
#define MFD_COLOUR_BLUE (mfd_colours[8])
#define MFD_COLOUR_LGREY (mfd_colours[9])
#define MFD_COLOUR_DGREY (mfd_colours[10])
#define MFD_COLOUR_LIGHT_BLUE	(mfd_colours[11])		//  Javelin  6/19
#define MFD_COLOUR_YELLOW    	(mfd_colours[12])		//  Javelin  6/19
#define MFD_COLOUR_BLACK    	(mfd_colours[13])		//  Javelin  6/19
#define MFD_COLOUR_ORANGE	  	(mfd_colours[14])		//  Javelin  7/19



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//
// main 2D environment
//
////////////////////////////////////////

#define MFD_WINDOW_X_MIN				(-1.0)
#define MFD_WINDOW_Y_MIN				(-1.0)
#define MFD_WINDOW_X_MAX				(0.999)
#define MFD_WINDOW_Y_MAX				(0.999)

#define MFD_VIEWPORT_SMALL_SIZE			(114)
#define MFD_VIEWPORT_LARGE_SIZE			(256)

#define MFD_SMALL_TEXTURE_SIZE				(128)
#define MFD_LARGE_TEXTURE_SIZE				(256)

#ifndef OGRE_EE
static env_2d
	*mfd_env;
#endif

static float
	mfd_viewport_size,
	mfd_viewport_x_org,
	mfd_viewport_y_org,
	mfd_viewport_x_min,
	mfd_viewport_y_min,
	mfd_viewport_x_max,
	mfd_viewport_y_max;

static int
	mfd_texture_size,
	mfd_viewport_texture_x_org,
	mfd_viewport_texture_y_org,
	draw_large_mfd;

static char
	*main_horizon_mask = NULL;			//  Javelin  6/19

#ifndef OGRE_EE
static float
	i_translate_3d,
	j_translate_3d,
	i_scale_3d,
	j_scale_3d;

static entity
	*last_target = NULL;
#endif



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define OVERLAID_MFD_TEXTURE_INDEX (TEXTURE_INDEX_COMANCHE_MFD2)	//  Javelin  7/19  

static screen
	*mfd_texture_screen,
	*eo_3d_texture_screen,
	*eo_3d_texture_screen_over,
	*overlaid_mfd_texture_screen,
	*export_screen,						//  Javelin  6/19
	*flight_mfd_texture_screen,   		//  Javelin  6/19
	*mfd_engine_screen;					//  Javelin  7/19

static rgb_colour
	clear_mfd_colour;

////////////////////////////////////////
//
// HEADING SCALE						Javelin  6/19
//
////////////////////////////////////////
static char large_command_heading_carat[] =
{
	11,
	6,
	-5,
	0,
	0,0,0,0,0,1,0,0,0,0,0,
	0,0,0,0,1,1,1,0,0,0,0,
	0,0,0,1,1,1,1,1,0,0,0,
	0,0,1,1,1,1,1,1,1,0,0,
	0,1,1,1,1,0,1,1,1,1,0,
	1,1,1,1,0,0,0,1,1,1,1,
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void initalize_horizon_mask(int width, char** mask)   //  Javelin  6/19
{
	int i,j;
	char *row;
	char* horizon_mask;
	int height = width;
	int circle_width = height * 0.8;
	int cutoff_width = (height - circle_width) / 2;
	int radius = (height / 2) - 2;
	int centre_y = height / 2;

	if (*mask)
		safe_free(*mask);
	horizon_mask = (char *) safe_malloc((width * height) + 4);
	*mask = horizon_mask;

	horizon_mask[0] = width;
	horizon_mask[1] = height;
	horizon_mask[2] = -(width / 2);
	horizon_mask[3] = -(height / 2);

	for (i = 0; i < height; i++)
	{
		row = &horizon_mask[4 + (i*width)];
		for (j = 0; j < width; j++)
		{
			{
				float height_val = fabs(((float)i - centre_y));
				float x_limit = radius - sqrt((radius * radius) - (height_val * height_val));

				x_limit = max((float) cutoff_width, x_limit);

				if (j < x_limit || j >= (width - x_limit))
					row[j] = 1;
				else
					row[j] = 0;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_havoc_mfd (void)
{
	mfd_mode = MFD_MODE_OFF;

#ifndef OGRE_EE
	mfd_env = create_2d_environment ();
#endif

	if (command_line_high_res_mfd)
	{
		draw_large_mfd = TRUE;

		mfd_viewport_size = MFD_VIEWPORT_LARGE_SIZE;
		mfd_texture_size = MFD_LARGE_TEXTURE_SIZE;
		eo_3d_texture_screen = large_eo_3d_texture_screen;
		eo_3d_texture_screen_over = large_eo_3d_texture_screen_over;
	}
	else
	{
		draw_large_mfd = FALSE;

		mfd_viewport_size = MFD_VIEWPORT_SMALL_SIZE;
		mfd_texture_size = MFD_SMALL_TEXTURE_SIZE;
		eo_3d_texture_screen = small_eo_3d_texture_screen;
		eo_3d_texture_screen_over = small_eo_3d_texture_screen_over;
	}

	mfd_viewport_texture_x_org = mfd_texture_size / 2;
	mfd_viewport_texture_y_org = mfd_texture_size / 2;

	mfd_viewport_x_min = mfd_viewport_x_org - (mfd_viewport_size * 0.5);
	mfd_viewport_y_min = mfd_viewport_y_org - (mfd_viewport_size * 0.5);
	mfd_viewport_x_max = mfd_viewport_x_org + (mfd_viewport_size * 0.5);
	mfd_viewport_y_max = mfd_viewport_y_org + (mfd_viewport_size * 0.5);

	mfd_texture_screen = create_system_texture_screen (mfd_texture_size, mfd_texture_size, TEXTURE_INDEX_HVCKPT_DISPLAY_CRT, TEXTURE_TYPE_SINGLEALPHA);
	overlaid_mfd_texture_screen = create_system_texture_screen (mfd_texture_size, mfd_texture_size, OVERLAID_MFD_TEXTURE_INDEX, TEXTURE_TYPE_SINGLEALPHA);
	flight_mfd_texture_screen = create_system_texture_screen (MFD_VIEWPORT_LARGE_SIZE, MFD_VIEWPORT_LARGE_SIZE, TEXTURE_INDEX_AVCKPT_DISPLAY_LHS_MFD, TEXTURE_TYPE_SINGLEALPHA);		//  Javelin  6/19
	mfd_engine_screen = create_system_texture_screen (mfd_texture_size, mfd_texture_size, TEXTURE_INDEX_COMANCHE_MFD2, TEXTURE_TYPE_SINGLEALPHA);

	set_rgb_colour (MFD_COLOUR1, 255, 160,   0, 255);
	set_rgb_colour (MFD_COLOUR2, 200, 130,   0, 255);
	set_rgb_colour (MFD_COLOUR3, 176, 126,   0, 255);
	set_rgb_colour (MFD_COLOUR4, 151, 100,   0, 255);
	set_rgb_colour (MFD_COLOUR5, 140,  90,   0, 255);
	set_rgb_colour (MFD_COLOUR6,  80,  62,   8, 255);
	set_rgb_colour (MFD_COLOUR_GREEN,		65, 165, 92, 255);
	set_rgb_colour (MFD_COLOUR_BLUE,		14, 22, 59, 255);
	set_rgb_colour (MFD_COLOUR_RED,			128, 44, 49, 255);
	set_rgb_colour (MFD_COLOUR_LGREY,		200, 200, 200, 255);
	set_rgb_colour (MFD_COLOUR_DGREY,		20, 20, 20, 255);
	set_rgb_colour (MFD_COLOUR_LIGHT_BLUE,  192, 192, 255, 255);		//  Javelin  6/19
	set_rgb_colour (MFD_COLOUR_YELLOW,      220, 220,  20, 255);		//  Javelin  6/19
	set_rgb_colour (MFD_COLOUR_BLACK ,      0,   0,   0, 255);			//  Javelin  6/19
	set_rgb_colour (clear_hud_colour,		255, 255, 255, 0);			//  Javelin  7/19
	set_rgb_colour (MFD_COLOUR_ORANGE,      255, 123,  20, 255);		//  Javelin  7/19


	if(command_line_export_mfd)
	{
		set_rgb_colour (clear_mfd_colour,  80,  62,   8, 0);
	}
	else
	{
		set_rgb_colour (clear_mfd_colour, 255, 255, 0, 0);
	}

	initalize_horizon_mask(MFD_VIEWPORT_LARGE_SIZE * 0.55, &main_horizon_mask);   //  Javelin  6/19
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_havoc_mfd (void)
{
#ifndef OGRE_EE
	destroy_2d_environment (mfd_env);
#endif

	destroy_screen (mfd_texture_screen);
	destroy_screen (overlaid_mfd_texture_screen);
	destroy_screen (export_screen);					//  Javelin  6/19
	destroy_screen (flight_mfd_texture_screen);		//  Javelin  6/19
	destroy_screen (mfd_engine_screen);				//  Javelin  7/19
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

mfd_modes get_havoc_mfd_mode (void)
{
	return mfd_mode;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_next_havoc_mfd_mode (void)
{
	switch (mfd_mode)
	{
	case MFD_MODE_OFF:
		if (!havoc_damage.tv_display)
			mfd_mode = MFD_MODE_LLLTV;
		else
			mfd_mode = MFD_MODE_DAMAGED;
		break;

	case MFD_MODE_DAMAGED:
		// do nothing
		break;

	case MFD_MODE_GROUND_RADAR:
	case MFD_MODE_AIR_RADAR:
		mfd_mode = MFD_MODE_LLLTV;
		break;

	case MFD_MODE_FLIR:
		if (air_radar_is_active() || (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_AIR_RADAR))
			mfd_mode = MFD_MODE_AIR_RADAR;
		else
			mfd_mode = MFD_MODE_GROUND_RADAR;
		break;

	case MFD_MODE_LLLTV:
		mfd_mode = MFD_MODE_FLIR;
		break;

	default:
		debug_fatal ("Invalid mfd mode = %d", mfd_mode);
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_havoc_mfd_mode (mfd_modes mode)
{
	switch (mode)
	{
		////////////////////////////////////////
		case MFD_MODE_OFF:
		////////////////////////////////////////
		{
			mfd_mode = mode;

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_DAMAGED:
		////////////////////////////////////////
		{
			mfd_mode = mode;

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_GROUND_RADAR:
		////////////////////////////////////////
		{
			mfd_mode = mode;

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_AIR_RADAR:
		////////////////////////////////////////
		{
			mfd_mode = mode;

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_FLIR:
		////////////////////////////////////////
		{
			mfd_mode = mode;

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_LLLTV:
		////////////////////////////////////////
		{
			mfd_mode = mode;

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal ("Invalid mfd mode = %d", mode);

			break;
		}
	}
}

#ifndef OGRE_EE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DAMAGED
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_damaged_mfd (void)
{
	int
		count,
		max_lines,
		i;

	rgb_colour
		col;

	float
		x_centre,
		x_delta,
		x_left,
		x_right,
		y;

	col.r = 0;
	col.g = 0;
	col.b = 0;
	col.a = 255;

	if (draw_large_mfd)
	{
		max_lines = 150;
	}
	else
	{
		max_lines = 75;
	}

	for (count = 0; count < max_lines; count++)
	{
		convert_float_to_int (frand1 () * 127.0, &i);

		col.r = i + 128;
		col.g = i + 128;

		x_centre = sfrand1 ();

		x_delta = (frand1 () * 0.5) + 0.25;

		x_left = x_centre - x_delta;

		x_right = x_centre + x_delta;

		y = sfrand1 ();

		draw_2d_line (x_left, y, x_right, y, col);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GROUND AND AIR RADAR
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_radar_scan_range (float scan_range)
{
//VJ 030807 radar range adjustable
	char
		s[8];
//		*s;

	float
		width;

	if (scan_range == HAVOC_RADAR_SCAN_RANGE_1000)
	{
//		s = "1Km";
		sprintf(s,"%.0fKm",HAVOC_RADAR_SCAN_RANGE_1000/1000);
	}
	else if (scan_range == HAVOC_RADAR_SCAN_RANGE_2000)
	{
//		s = "2Km";
		sprintf(s,"%.0fKm",HAVOC_RADAR_SCAN_RANGE_2000/1000);
	}
	else if (scan_range == HAVOC_RADAR_SCAN_RANGE_4000)
	{
//		s = "4Km";
		sprintf(s,"%.0fKm",HAVOC_RADAR_SCAN_RANGE_4000/1000);
	}
	else if (scan_range == HAVOC_RADAR_SCAN_RANGE_6000)
	{
//		s = "6Km";
		sprintf(s,"%.0fKm",HAVOC_RADAR_SCAN_RANGE_6000/1000);
	}
	else
	{
//		s = "XXX";
		sprintf(s,"XXX");
	}

	width = get_mono_font_string_width (s);

	set_2d_mono_font_position (1.0, 1.0);

	set_mono_font_rel_position (-width, 1.0);

	print_mono_font_string (s);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_radar_target_details (entity *target, float target_range, radar_params *radar)
{
	const char
		*s;
	char
		buffer[200];

	float
		y_adjust,
		width;

	ASSERT (radar);

	if (draw_large_mfd)
	{
		y_adjust = -8.0;
	}
	else
	{
		y_adjust = -4.0;
	}

	//
	// name
	//

	s = get_target_display_name (target, buffer, draw_large_mfd);

	if (s)
	{
		set_2d_mono_font_position (-1.0, -1.0);

		set_mono_font_rel_position (1.0, y_adjust);

		print_mono_font_string (s);
	}

	if (target)
	{
		//
		// range
		//

		if ((target_range < 1000.0) && (!havoc_damage.laser_range_finder))
		{
			sprintf (buffer, "%dm", (int) target_range);
		}
		else
		{
			sprintf (buffer, "%.1fKm", target_range * (1.0 / 1000.0));
		}

		width = get_mono_font_string_width (buffer);

		set_2d_mono_font_position (1.0, -1.0);

		set_mono_font_rel_position (-width, y_adjust);

		print_mono_font_string (buffer);

		//
		// no line of sight
		//

		if (!get_local_entity_int_value (target, INT_TYPE_GUNSHIP_RADAR_LOS_CLEAR))
		{
			if (draw_large_mfd)
			{
				y_adjust = -21.0;
			}
			else
			{
				y_adjust = -11.0;
			}

			width = get_mono_font_string_width ("NO LOS");

			set_2d_mono_font_position (1.0, -1.0);

			set_mono_font_rel_position (-width, y_adjust);

			print_mono_font_string ("NO LOS");
		}
	}

	//
	// auto
	//

	if (radar->auto_target)
	{
		if (draw_large_mfd)
		{
			y_adjust = 14.0;
		}
		else
		{
			y_adjust = 8.0;
		}

		set_2d_mono_font_position (-1.0, 1.0);

		set_mono_font_rel_position (1.0, y_adjust);

		print_mono_font_string ("AUTO");
	}

	//
	// locked
	//

	if (radar->target_locked)
	{
		if (draw_large_mfd)
		{
			y_adjust = -21.0;
		}
		else
		{
			y_adjust = -11.0;
		}

		set_2d_mono_font_position (-1.0, -1.0);

		set_mono_font_rel_position (1.0, y_adjust);

		print_mono_font_string ("LOCKED");
	}
// Jabberwock 031107 Designated targets

	target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

	if (target && get_local_entity_parent (target, LIST_TYPE_DESIGNATED_TARGET))
	{
		if (draw_large_mfd)
		{
			y_adjust = -25.0;
		}
		else
		{
			y_adjust = -12.0;
		}

		width = get_mono_font_string_width ("MARKED");

		set_2d_mono_font_position (1.0, -1.0);

		set_mono_font_rel_position (-width -1.0, y_adjust);

		print_mono_font_string ("MARKED");
	}
// Jabberwock 031107 ends
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_radar_arc (float arc_size, float radius, rgb_colour colour)
{
	int
		num_segments;

	float
		theta,
		sin_theta,
		cos_theta,
		x1,
		y1,
		x2,
		y2;

	num_segments = (int) (arc_size * (1.0 / HAVOC_RADAR_SCAN_ARC_SEGMENT_SIZE));

	if (num_segments > 0)
	{
		theta = arc_size * 0.5;

		sine_cosine (theta, &sin_theta, &cos_theta);

		x1 = -radius * sin_theta;
		y1 = radius * cos_theta;

		while (num_segments--)
		{
			theta -= HAVOC_RADAR_SCAN_ARC_SEGMENT_SIZE;

			sine_cosine (theta, &sin_theta, &cos_theta);

			x2 = -radius * sin_theta;
			y2 = radius * cos_theta;

			draw_2d_line (x1, y1, x2, y2, colour);

			x1 = x2;
			y1 = y2;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_radar_target_symbol (entity *target, vec3d *source_position, float scale, int selected_target)
{
	target_symbol_types
		target_symbol_type;

	rgb_colour
		target_symbol_colour;

	float
		dx,
		dy;

	vec3d
		*target_position;

	ASSERT (target);

	ASSERT (source_position);

	ASSERT (!get_local_entity_int_value (target, INT_TYPE_GROUND_RADAR_CLUTTER));

	target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

	dx = (target_position->x - source_position->x) * scale;
	dy = (target_position->z - source_position->z) * scale;

	target_symbol_type = (target_symbol_types) get_local_entity_int_value (target, INT_TYPE_TARGET_SYMBOL_TYPE);

	ASSERT ((target_symbol_type >= 0) && (target_symbol_type < NUM_TARGET_SYMBOL_TYPES));

	if (get_local_entity_index (target) & 1)
	{
		target_symbol_colour = MFD_COLOUR2;
	}
	else
	{
		target_symbol_colour = MFD_COLOUR1;
	}

	if (draw_large_mfd)
	{
		if (get_local_entity_int_value (target, INT_TYPE_GUNSHIP_RADAR_LOS_CLEAR))
		{
			if (selected_target)
			{
				draw_2d_mono_sprite (large_display_target_symbols_los_mask[target_symbol_type], dx, dy, MFD_COLOUR6);
			}

			draw_2d_mono_sprite (large_display_target_symbols_los[target_symbol_type], dx, dy, target_symbol_colour);
		}
		else
		{
			if (selected_target)
			{
				draw_2d_mono_sprite (large_display_target_symbols_no_los_mask[target_symbol_type], dx, dy, MFD_COLOUR6);
			}

			draw_2d_mono_sprite (large_display_target_symbols_no_los[target_symbol_type], dx, dy, target_symbol_colour);
		}

		if (selected_target)
		{
			draw_2d_mono_sprite (large_display_target_symbol_selected_target_mask, dx, dy, MFD_COLOUR6);

			draw_2d_mono_sprite (large_display_target_symbol_selected_target, dx, dy, target_symbol_colour);
		}
	}
	else
	{
		if (get_local_entity_int_value (target, INT_TYPE_GUNSHIP_RADAR_LOS_CLEAR))
		{
			if (selected_target)
			{
				draw_2d_mono_sprite (small_display_target_symbols_los_mask[target_symbol_type], dx, dy, MFD_COLOUR6);
			}

			draw_2d_mono_sprite (small_display_target_symbols_los[target_symbol_type], dx, dy, target_symbol_colour);
		}
		else
		{
			if (selected_target)
			{
				draw_2d_mono_sprite (small_display_target_symbols_no_los_mask[target_symbol_type], dx, dy, MFD_COLOUR6);
			}

			draw_2d_mono_sprite (small_display_target_symbols_no_los[target_symbol_type], dx, dy, target_symbol_colour);
		}

		if (selected_target)
		{
			draw_2d_mono_sprite (small_display_target_symbol_selected_target_mask, dx, dy, MFD_COLOUR6);

			draw_2d_mono_sprite (small_display_target_symbol_selected_target, dx, dy, target_symbol_colour);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GROUND RADAR
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static char large_ground_radar_heading_scale_datum[] =
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

static char small_ground_radar_heading_scale_datum[] =
{
	5,
	3,
	-2,
	0,
	0,0,1,0,0,
	0,1,1,1,0,
	1,1,1,1,1,
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_ground_radar_heading_scale (void)
{
	float
		y_position,
		mfd_vp_x_min,
		mfd_vp_x_max,
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

	set_2d_window (mfd_env, MFD_WINDOW_X_MIN * 0.5, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX * 0.5, MFD_WINDOW_Y_MAX);

	mfd_vp_x_min = mfd_viewport_x_org - (mfd_viewport_size * (0.5 * 0.5));

	mfd_vp_x_max = mfd_viewport_x_org + (mfd_viewport_size * (0.5 * 0.5));

	set_2d_viewport (mfd_env, mfd_vp_x_min, mfd_viewport_y_min, mfd_vp_x_max, mfd_viewport_y_max);

	//
	// sort first major tick position (draw 2 major ticks either side of centre)
	//

	heading = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_HEADING);

	heading = deg (heading);

	mod_heading_step_10 = fmod (heading, 10.0f);

	int_heading_step_10 = ((int) (heading * 0.1) * 10);

	int_heading_step_10 -= 20;

	if (int_heading_step_10 < 0)
	{
		int_heading_step_10 += 360;
	}

	x = - (20.0 + mod_heading_step_10) * 0.05;

	//
	// large and small MFD position
	//

	y_position = 0.8375;

	//
	// draw heading scale line
	//

	draw_2d_line (-0.5, y_position, 0.5, y_position, MFD_COLOUR1);

	//
	// large and small MFD differences
	//

	get_2d_float_screen_coordinates (0.0, y_position, &i, &j);

	if (draw_large_mfd)
	{
		set_mono_font_type (MONO_FONT_TYPE_6X10);

		draw_mono_sprite (large_ground_radar_heading_scale_datum, i, j + 1.0, MFD_COLOUR1);
	}
	else
	{
		set_mono_font_type (MONO_FONT_TYPE_5X7);

		draw_mono_sprite (small_ground_radar_heading_scale_datum, i, j + 1.0, MFD_COLOUR1);
	}

	//
	// draw heading scale ticks and heading value
	//

	for (loop = 0; loop < 5; loop++)
	{
		//
		// major tick every 10 degrees
		//

		draw_2d_line (x, y_position, x, y_position + 0.05, MFD_COLOUR1);

		//
		// minor tick every 5 degrees
		//

		draw_2d_line (x + 0.25, y_position, x + 0.25, y_position + 0.025, MFD_COLOUR1);

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

		set_2d_mono_font_position (x, y_position + 0.05);

		width = get_mono_font_string_width (s);

		if (draw_large_mfd)
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
	// restore 2D environment
	//

	set_2d_window (mfd_env, MFD_WINDOW_X_MIN, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX, MFD_WINDOW_Y_MAX);

	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_ground_radar_clutter (entity *target, vec3d *source_position, float scale)
{
	float
		dx,
		dy,
		radius;

	vec3d
		*target_position,
		*bounding_box_min,
		*bounding_box_max;

	ASSERT (target);

	ASSERT (source_position);

	ASSERT (get_local_entity_type (target) == ENTITY_TYPE_CITY);

	target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

	dx = (target_position->x - source_position->x) * scale;
	dy = (target_position->z - source_position->z) * scale;

	bounding_box_min = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_BOUNDING_BOX_MIN);
	bounding_box_max = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_BOUNDING_BOX_MAX);

	radius = get_approx_2d_range (bounding_box_min, bounding_box_max);

	//
	// radius check to ignore oil pipelines and overly large city blocks
	//

	if (radius < 2000.0)
	{
		radius = max (50.0f, radius);

		draw_2d_hatched_circle (dx, dy, radius * scale, MFD_COLOUR5);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define RADIUS	(ROOT2)

static void draw_ground_radar_mfd (void)
{
	float
		u,
		v,
		source_heading,
		scale,
		target_range,
		x,
		y;

	entity
		*source,
		*target;

	vec3d
		*source_position,
		*target_position;

	source = get_gunship_entity ();

	source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

	source_heading = get_local_entity_float_value (source, FLOAT_TYPE_HEADING);

	scale = RADIUS / ground_radar.scan_range;

	if (draw_large_mfd)
	{
		get_2d_float_screen_coordinates (0.0, -0.65, &u, &v);
	}
	else
	{
		get_2d_float_screen_coordinates (0.0, -0.7, &u, &v);
	}

	u -= mfd_viewport_x_min;
	v -= mfd_viewport_y_min;

	////////////////////////////////////////
	//
	// draw radar clutter
	//
	////////////////////////////////////////

	set_hatched_pattern (radar_clutter_hatch_pattern);

	set_2d_viewport_origin (mfd_env, u, v);

	set_2d_window_rotation (mfd_env, source_heading);

	target = get_local_entity_first_child (source, LIST_TYPE_GUNSHIP_TARGET);

	while (target)
	{
		if (get_local_entity_int_value (target, INT_TYPE_GROUND_RADAR_CLUTTER))
		{
			draw_ground_radar_clutter (target, source_position, scale);
		}

		target = get_local_entity_child_succ (target, LIST_TYPE_GUNSHIP_TARGET);
	}

	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

	set_2d_window_rotation (mfd_env, 0.0);

	////////////////////////////////////////
	//
	// text
	//
	////////////////////////////////////////

	set_mono_font_colour (MFD_COLOUR1);

	if (draw_large_mfd)
	{
		set_mono_font_type (MONO_FONT_TYPE_7X12);
	}
	else
	{
		set_mono_font_type (MONO_FONT_TYPE_5X7);
	}

	//
	// declutter status
	//

	set_2d_mono_font_position (-1.0, 1.0);

	set_mono_font_rel_position (1.0, 1.0);

	switch (ground_radar.target_priority_type)
	{
		case TARGET_PRIORITY_UNKNOWN:
		{
			print_mono_font_string ("ALL");

			break;
		}
		case TARGET_PRIORITY_LOW:
		{
			print_mono_font_string ("LOW");

			break;
		}
		case TARGET_PRIORITY_MEDIUM:
		{
			if (draw_large_mfd)
			{
				print_mono_font_string ("MEDIUM");
			}
			else
			{
				print_mono_font_string ("MED");
			}

			break;
		}
		case TARGET_PRIORITY_HIGH:
		{
			print_mono_font_string ("HIGH");

			break;
		}
		// Jabberwock 031107 Designated targets
		case TARGET_PRIORITY_DESIGNATED:
		{
			print_mono_font_string ("MARK");

			break;
		}
		// Jabberwock 031107 ends
	}
	//
	// scan range
	//

	display_radar_scan_range (ground_radar.scan_range);

	//
	// target details
	//

	target = get_local_entity_parent (source, LIST_TYPE_TARGET);

	if (target)
	{
		target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

		target_range = get_3d_range (source_position, target_position);
	}
	else
	{
		target_range = 0.0;
	}

	display_radar_target_details (target, target_range, &ground_radar);

	////////////////////////////////////////
	//
	// draw heading scale
	//
	////////////////////////////////////////

	draw_ground_radar_heading_scale ();

	////////////////////////////////////////
	//
	// draw field of regard and view
	//
	////////////////////////////////////////

	if (draw_large_mfd)
	{
		draw_2d_line (-0.3000, -0.7000,  0.3000, -0.7000, MFD_COLOUR1);
		draw_2d_line (-0.3000, -0.8445,  0.3000, -0.8445, MFD_COLOUR1);
		draw_2d_line (-0.3000, -0.7000, -0.3000, -0.8445, MFD_COLOUR1);
		draw_2d_line ( 0.3000, -0.7000,  0.3000, -0.8445, MFD_COLOUR1);

		draw_2d_line ( 0.0000, -0.7000,  0.0000, -0.7225, MFD_COLOUR1);
		draw_2d_line (-0.2455, -0.7000, -0.2455, -0.7225, MFD_COLOUR1);
		draw_2d_line ( 0.2455, -0.7000,  0.2455, -0.7225, MFD_COLOUR1);

		draw_2d_line ( 0.0000, -0.8275,  0.0000, -0.8445, MFD_COLOUR1);
		draw_2d_line (-0.2455, -0.8275, -0.2455, -0.8445, MFD_COLOUR1);
		draw_2d_line ( 0.2455, -0.8275,  0.2455, -0.8445, MFD_COLOUR1);

		draw_2d_line (-0.3000, -0.7354, -0.2800, -0.7354, MFD_COLOUR1);
		draw_2d_line ( 0.3000, -0.7354,  0.2800, -0.7354, MFD_COLOUR1);

		x = eo_azimuth / eo_max_azimuth * 0.3;
		y = (eo_elevation / eo_min_elevation * -0.1091) - 0.7354;

		draw_2d_circle (x, y, 0.04, MFD_COLOUR1);
	}
	else
	{
		draw_2d_line (-0.2000, -0.7500,  0.2000, -0.7500, MFD_COLOUR1);
		draw_2d_line (-0.2000, -0.8464,  0.2000, -0.8464, MFD_COLOUR1);
		draw_2d_line (-0.2000, -0.7500, -0.2000, -0.8464, MFD_COLOUR1);
		draw_2d_line ( 0.2000, -0.7500,  0.2000, -0.8464, MFD_COLOUR1);

		draw_2d_line ( 0.0000, -0.7500,  0.0000, -0.7700, MFD_COLOUR1);
		draw_2d_line (-0.1636, -0.7500, -0.1636, -0.7700, MFD_COLOUR1);
		draw_2d_line ( 0.1636, -0.7500,  0.1636, -0.7700, MFD_COLOUR1);

		draw_2d_line ( 0.0000, -0.8264,  0.0000, -0.8464, MFD_COLOUR1);
		draw_2d_line (-0.1636, -0.8264, -0.1636, -0.8464, MFD_COLOUR1);
		draw_2d_line ( 0.1636, -0.8264,  0.1636, -0.8464, MFD_COLOUR1);

		draw_2d_line (-0.2000, -0.7736, -0.1775, -0.7736, MFD_COLOUR1);
		draw_2d_line ( 0.2000, -0.7736,  0.1775, -0.7736, MFD_COLOUR1);

		x = eo_azimuth / eo_max_azimuth * 0.2;
		y = (eo_elevation / eo_min_elevation * -0.0727) - 0.7736;

		draw_2d_circle (x, y, 0.04, MFD_COLOUR1);
	}

	////////////////////////////////////////
	//
	// line graphics
	//
	////////////////////////////////////////

	set_2d_viewport_origin (mfd_env, u, v);

	//
	// max scan limits
	//

	draw_2d_line (0.0, 0.0, -1.0, 1.0, MFD_COLOUR4);

	draw_2d_line (0.0, 0.0, 1.0, 1.0, MFD_COLOUR4);

	draw_radar_arc (HAVOC_RADAR_SCAN_ARC_SIZE_90, RADIUS, MFD_COLOUR4);

	//
	// scan limits and range markers
	//

	set_2d_window_rotation (mfd_env, -ground_radar.scan_datum);

	draw_radar_arc (ground_radar.scan_arc_size, RADIUS, MFD_COLOUR1);

	draw_radar_arc (ground_radar.scan_arc_size, RADIUS * 0.25, MFD_COLOUR4);
	draw_radar_arc (ground_radar.scan_arc_size, RADIUS * 0.50, MFD_COLOUR4);
	draw_radar_arc (ground_radar.scan_arc_size, RADIUS * 0.75, MFD_COLOUR4);

	set_2d_window_rotation (mfd_env, -(ground_radar.scan_datum - (ground_radar.scan_arc_size * 0.5)));

	draw_2d_line (0.0, 0.0, 0.0, RADIUS, MFD_COLOUR1);

	set_2d_window_rotation (mfd_env, -(ground_radar.scan_datum + (ground_radar.scan_arc_size * 0.5)));

	draw_2d_line (0.0, 0.0, 0.0, RADIUS, MFD_COLOUR1);

	//
	// sweep
	//

	if (ground_radar_is_active())
	{
		set_2d_window_rotation (mfd_env, -(ground_radar.scan_datum + ground_radar.sweep_offset));

		draw_2d_line (0.0, 0.0, 0.0, RADIUS, MFD_COLOUR1);

		set_2d_window_rotation (mfd_env, 0.0);
	}

	////////////////////////////////////////
	//
	// targets
	//
	////////////////////////////////////////

	set_2d_window_rotation (mfd_env, source_heading);

	target = get_local_entity_first_child (source, LIST_TYPE_GUNSHIP_TARGET);

	while (target)
	{
		if (get_gunship_target_valid_for_ground_radar (target))
		{
			if (get_target_matches_ground_radar_declutter_criteria (target))
			{
				draw_radar_target_symbol (target, source_position, scale, FALSE);
			}
		}

		target = get_local_entity_child_succ (target, LIST_TYPE_GUNSHIP_TARGET);
	}

	//
	// draw selected target last
	//

	target = get_local_entity_parent (source, LIST_TYPE_TARGET);

	if (target)
	{
		draw_radar_target_symbol (target, source_position, scale, TRUE);
	}

	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

	set_2d_window_rotation (mfd_env, 0.0);
}

#undef RADIUS

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// AIR RADAR
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define RADIUS	(0.85)
#define TICK1	(RADIUS * 0.8125)
#define TICK2	(RADIUS * 0.9375)

static void draw_air_radar_mfd (void)
{
	entity_sides
		source_side;

	float
		source_heading,
		scale,
		target_range;

	entity
		*source,
		*target;

	vec3d
		*source_position,
		*target_position;

	source = get_gunship_entity ();

	source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

	source_side = (entity_sides) get_local_entity_int_value (source, INT_TYPE_SIDE);

	////////////////////////////////////////
	//
	// text
	//
	////////////////////////////////////////

	set_mono_font_colour (MFD_COLOUR1);

	if (draw_large_mfd)
	{
		set_mono_font_type (MONO_FONT_TYPE_7X12);
	}
	else
	{
		set_mono_font_type (MONO_FONT_TYPE_5X7);
	}

	//
	// declutter status
	//

	set_2d_mono_font_position (-1.0, 1.0);

	set_mono_font_rel_position (1.0, 1.0);

	if (air_radar.show_allied_targets)
	{
		print_mono_font_string ("ALL");
	}
	else
	{
		print_mono_font_string ("ENEMY");
	}

	//
	// scan range
	//

	display_radar_scan_range (air_radar.scan_range);

	//
	// target details
	//

	target = get_local_entity_parent (source, LIST_TYPE_TARGET);

	if (target)
	{
		target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

		target_range = get_3d_range (source_position, target_position);
	}
	else
	{
		target_range = 0.0;
	}

	display_radar_target_details (target, target_range, &air_radar);

	////////////////////////////////////////
	//
	// line graphics
	//
	////////////////////////////////////////

	//
	// datum markers
	//

	draw_2d_line ( 0.00,  TICK1,  0.00,  TICK2, MFD_COLOUR4);
	draw_2d_line ( TICK1,  0.00,  TICK2,  0.00, MFD_COLOUR4);
	draw_2d_line ( 0.00, -TICK1,  0.00, -TICK2, MFD_COLOUR4);
	draw_2d_line (-TICK1,  0.00, -TICK2,  0.00, MFD_COLOUR4);

	//
	// range markers
	//

	draw_2d_circle (0.0, 0.0, RADIUS * 0.25, MFD_COLOUR4);
	draw_2d_circle (0.0, 0.0, RADIUS * 0.50, MFD_COLOUR4);
	draw_2d_circle (0.0, 0.0, RADIUS * 0.75, MFD_COLOUR4);

	//
	// scan limits
	//

	if (air_radar.scan_arc_size == HAVOC_RADAR_SCAN_ARC_SIZE_360)
	{
		draw_2d_circle (0.0, 0.0, RADIUS, MFD_COLOUR1);
	}
	else
	{
		draw_2d_circle (0.0, 0.0, RADIUS, MFD_COLOUR4);

		set_2d_window_rotation (mfd_env, -air_radar.scan_datum);

		draw_radar_arc (air_radar.scan_arc_size, RADIUS, MFD_COLOUR1);

		draw_2d_line (0.0, 0.0, 0.0, RADIUS, MFD_COLOUR1);

		set_2d_window_rotation (mfd_env, -(air_radar.scan_datum - (air_radar.scan_arc_size * 0.5)));

		draw_2d_line (0.0, 0.0, 0.0, RADIUS, MFD_COLOUR1);

		set_2d_window_rotation (mfd_env, -(air_radar.scan_datum + (air_radar.scan_arc_size * 0.5)));

		draw_2d_line (0.0, 0.0, 0.0, RADIUS, MFD_COLOUR1);
	}

	//
	// sweep
	//

	if (air_radar_is_active())
	{
		set_2d_window_rotation (mfd_env, -(air_radar.scan_datum + air_radar.sweep_offset));

		draw_2d_line (0.0, 0.0, 0.0, RADIUS, MFD_COLOUR1);

		set_2d_window_rotation (mfd_env, 0.0);
	}

	////////////////////////////////////////
	//
	// draw targets
	//
	////////////////////////////////////////

	source_heading = get_local_entity_float_value (source, FLOAT_TYPE_HEADING);

	set_2d_window_rotation (mfd_env, source_heading);

	scale = RADIUS / air_radar.scan_range;

	target = get_local_entity_first_child (source, LIST_TYPE_GUNSHIP_TARGET);

	while (target)
	{
		if (get_gunship_target_valid_for_air_radar (target))
		{
			if (get_target_matches_air_radar_declutter_criteria (target, source_side))
			{
				draw_radar_target_symbol (target, source_position, scale, FALSE);
			}
		}

		target = get_local_entity_child_succ (target, LIST_TYPE_GUNSHIP_TARGET);
	}

	//
	// draw selected target last
	//

	target = get_local_entity_parent (source, LIST_TYPE_TARGET);

	if (target)
	{
		draw_radar_target_symbol (target, source_position, scale, TRUE);
	}

	set_2d_window_rotation (mfd_env, 0.0);
}

#undef RADIUS
#undef TICK1
#undef TICK2

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// EO
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//
// FLIR
//
////////////////////////////////////////

static display_3d_light_levels
	flir_light_levels[WEATHERMODE_LAST][NUM_DAY_SEGMENT_TYPES] =
	{
		// WEATHERMODE_INVALID
		{
			DISPLAY_3D_LIGHT_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_LIGHT_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_LIGHT_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_LIGHT_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_DRY
		{
			DISPLAY_3D_LIGHT_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_LIGHT_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_LIGHT_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_LIGHT_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_LIGHT_RAIN
		{
			DISPLAY_3D_LIGHT_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_LIGHT_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_LIGHT_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_LIGHT_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_HEAVY_RAIN
		{
			DISPLAY_3D_LIGHT_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_LIGHT_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_LIGHT_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_LIGHT_LEVEL_LOW,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_SNOW
		{
			DISPLAY_3D_LIGHT_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_LIGHT_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_LIGHT_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_LIGHT_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_NIGHT
		},
	};

static display_3d_noise_levels
	flir_noise_levels[WEATHERMODE_LAST][NUM_DAY_SEGMENT_TYPES] =
	{
		// WEATHERMODE_INVALID
		{
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_DRY
		{
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_LIGHT_RAIN
		{
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_HEAVY_RAIN
		{
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_SNOW
		{
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_NIGHT
		},
	};

////////////////////////////////////////
//
// LLLTV
//
////////////////////////////////////////

static display_3d_light_levels
	llltv_light_levels[WEATHERMODE_LAST][NUM_DAY_SEGMENT_TYPES] =
	{
		// WEATHERMODE_INVALID
		{
			DISPLAY_3D_LIGHT_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_LIGHT_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_LIGHT_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_LIGHT_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_DRY
		{
			DISPLAY_3D_LIGHT_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_LIGHT_LEVEL_HIGH,	 	// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_LIGHT_LEVEL_MEDIUM, 	// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_LIGHT_LEVEL_LOW,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_LIGHT_RAIN
		{
			DISPLAY_3D_LIGHT_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_LIGHT_LEVEL_MEDIUM, 	// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_LIGHT_LEVEL_LOW, 		// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_LIGHT_LEVEL_LOW,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_HEAVY_RAIN
		{
			DISPLAY_3D_LIGHT_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_LIGHT_LEVEL_LOW, 		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_LIGHT_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_LIGHT_LEVEL_LOW,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_SNOW
		{
			DISPLAY_3D_LIGHT_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_LIGHT_LEVEL_MEDIUM, 	// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_LIGHT_LEVEL_LOW, 		// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_LIGHT_LEVEL_LOW,		// DAY_SEGMENT_TYPE_NIGHT
		},
	};

static display_3d_noise_levels
	llltv_noise_levels[WEATHERMODE_LAST][NUM_DAY_SEGMENT_TYPES] =
	{
		// WEATHERMODE_INVALID
		{
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,		// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_DRY
		{
			DISPLAY_3D_NOISE_LEVEL_LOW,	// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_LIGHT_RAIN
		{
			DISPLAY_3D_NOISE_LEVEL_LOW,	// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_HEAVY_RAIN
		{
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_HIGH,	// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_SNOW
		{
			DISPLAY_3D_NOISE_LEVEL_LOW,	// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_NIGHT
		},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_3d_eo_display (eo_params *eo, target_acquisition_systems system)
{
	float
		zoom;

	display_3d_light_levels
		light_level;

	display_3d_noise_levels
		noise_level;

	vec3d
		*position;

	weathermodes
		weather_mode;

	day_segment_types
		day_segment_type;

	ASSERT (eo);

	switch (eo->field_of_view)
	{
		case EO_FOV_NARROW:
		{
			zoom = 0.0165;

			break;
		}
		case EO_FOV_MEDIUM:
		{
			zoom = 0.066;

			break;
		}
		case EO_FOV_WIDE:
		{
			zoom = 0.3;

			break;
		}
		default:
		{
			debug_fatal ("Invalid field of view = %d", eo->field_of_view);

			break;
		}
	}

	position = get_local_entity_vec3d_ptr (get_gunship_entity (), VEC3D_TYPE_POSITION);

	weather_mode = get_simple_session_weather_at_point (position);

	ASSERT ((weather_mode > WEATHERMODE_INVALID) && (weather_mode < WEATHERMODE_LAST));

	day_segment_type = (day_segment_types) get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE);

	ASSERT ((day_segment_type >= 0) && (day_segment_type < NUM_DAY_SEGMENT_TYPES));

	switch (system)
	{
		case TARGET_ACQUISITION_SYSTEM_FLIR:
		{
			light_level = flir_light_levels[weather_mode][day_segment_type];

			noise_level = flir_noise_levels[weather_mode][day_segment_type];

			break;
		}
		case TARGET_ACQUISITION_SYSTEM_LLLTV:
		{
			light_level = llltv_light_levels[weather_mode][day_segment_type];

			noise_level = llltv_noise_levels[weather_mode][day_segment_type];

			break;
		}
		default:
		{
			debug_fatal ("Invalid target acquisition system = %d", system);

			break;
		}
	}

	if (draw_large_mfd)
	{
		set_main_3d_params (DISPLAY_3D_TINT_FLIR, light_level, noise_level, mfd_viewport_x_min - 78.0, mfd_viewport_y_min - 17.0, 488.0, 366.0, rad (59.99) * zoom, rad (59.99) * zoom);
	}
	else
	{
		set_main_3d_params (DISPLAY_3D_TINT_FLIR, light_level, noise_level, mfd_viewport_x_min - 31.0, mfd_viewport_y_min - 10.0, 176.0, 132.0, rad (59.99) * zoom, rad (59.99) * zoom);
	}

	draw_eo_3d_scene = TRUE;

	draw_main_3d_scene (&eo_vp);

	draw_eo_3d_scene = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_3d_eo_display_on_texture (eo_params *eo, target_acquisition_systems system)
{
	float
		zoom;

	display_3d_light_levels
		light_level;

	display_3d_noise_levels
		noise_level;

	vec3d
		*position;

	weathermodes
		weather_mode;

	day_segment_types
		day_segment_type;

	display_3d_tints
		tint;

	ASSERT (eo);

	ASSERT (eo_3d_texture_screen);

	switch (eo->field_of_view)
	{
		case EO_FOV_NARROW:
		{
			zoom = 0.0165;

			break;
		}
		case EO_FOV_MEDIUM:
		{
			zoom = 0.066;

			break;
		}
		case EO_FOV_WIDE:
		{
			zoom = 0.3;

			break;
		}
		default:
		{
			debug_fatal ("Invalid field of view = %d", eo->field_of_view);

			break;
		}
	}

	position = get_local_entity_vec3d_ptr (get_gunship_entity (), VEC3D_TYPE_POSITION);

	weather_mode = get_simple_session_weather_at_point (position);

	ASSERT ((weather_mode > WEATHERMODE_INVALID) && (weather_mode < WEATHERMODE_LAST));

	day_segment_type = (day_segment_types) get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE);

	ASSERT ((day_segment_type >= 0) && (day_segment_type < NUM_DAY_SEGMENT_TYPES));

	switch (system)
	{
		case TARGET_ACQUISITION_SYSTEM_FLIR:
		{
			light_level = flir_light_levels[weather_mode][day_segment_type];

			noise_level = flir_noise_levels[weather_mode][day_segment_type];

			tint = DISPLAY_3D_TINT_FLIR;

			break;
		}
		case TARGET_ACQUISITION_SYSTEM_LLLTV:
		{
			light_level = llltv_light_levels[weather_mode][day_segment_type];

			noise_level = llltv_noise_levels[weather_mode][day_segment_type];

			tint = DISPLAY_3D_TINT_LLLTV;

			break;
		}
		default:
		{
			debug_fatal ("Invalid target acquisition system = %d", system);

			break;
		}
	}

	set_3d_render_target (eo_3d_texture_screen);

	set_active_screen (eo_3d_texture_screen);

	set_main_3d_params (tint, light_level, noise_level, 0.0, 0.0, mfd_texture_size, mfd_texture_size, rad (59.99) * zoom, rad (59.99) * zoom);

	draw_eo_3d_scene = TRUE;

	draw_main_3d_scene (&eo_vp);

	draw_eo_3d_scene = FALSE;

	finalise_3d_render_target_texture (eo_3d_texture_screen);

	set_3d_render_target (video_screen);

	set_active_screen (video_screen);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_overlaid_3d_eo_display (eo_params *eo, target_acquisition_systems system, float x, float y, float size)
{
	float
		zoom;

	display_3d_light_levels
		light_level;

	display_3d_noise_levels
		noise_level;

	vec3d
		*position;

	weathermodes
		weather_mode;

	day_segment_types
		day_segment_type;

	ASSERT (eo);

	switch (eo->field_of_view)
	{
		case EO_FOV_NARROW:
		{
			zoom = 0.0165;

			break;
		}
		case EO_FOV_MEDIUM:
		{
			zoom = 0.066;

			break;
		}
		case EO_FOV_WIDE:
		{
			zoom = 0.3;

			break;
		}
		default:
		{
			debug_fatal ("Invalid field of view = %d", eo->field_of_view);

			break;
		}
	}

	position = get_local_entity_vec3d_ptr (get_gunship_entity (), VEC3D_TYPE_POSITION);

	weather_mode = get_simple_session_weather_at_point (position);

	ASSERT ((weather_mode > WEATHERMODE_INVALID) && (weather_mode < WEATHERMODE_LAST));

	day_segment_type = (day_segment_types) get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE);

	ASSERT ((day_segment_type >= 0) && (day_segment_type < NUM_DAY_SEGMENT_TYPES));

	switch (system)
	{
		case TARGET_ACQUISITION_SYSTEM_FLIR:
		{
			light_level = flir_light_levels[weather_mode][day_segment_type];

			noise_level = flir_noise_levels[weather_mode][day_segment_type];

			break;
		}
		case TARGET_ACQUISITION_SYSTEM_LLLTV:
		{
			light_level = llltv_light_levels[weather_mode][day_segment_type];

			noise_level = llltv_noise_levels[weather_mode][day_segment_type];

			break;
		}
		default:
		{
			debug_fatal ("Invalid target acquisition system = %d", system);

			break;
		}
	}

	set_main_3d_params (DISPLAY_3D_TINT_FLIR, light_level, noise_level, x, y, size, size, rad (59.99) * zoom, rad (59.99) * zoom);

	draw_eo_3d_scene = TRUE;

	draw_main_3d_scene (&eo_vp);

	draw_eo_3d_scene = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static char large_azimuth_marker[] =
{
	11,
	6,
	-5,
	1,
	0,0,0,0,0,1,0,0,0,0,0,
	0,0,0,0,1,0,1,0,0,0,0,
	0,0,0,1,0,0,0,1,0,0,0,
	0,0,1,0,0,0,0,0,1,0,0,
	0,1,0,0,0,0,0,0,0,1,0,
	1,1,1,1,1,1,1,1,1,1,1,
};

static char small_azimuth_marker[] =
{
	3,
	8,
	-1,
	0,
	0,1,0,
	0,1,0,
	0,1,0,
	1,0,1,
	1,0,1,
	1,0,1,
	1,0,1,
	1,1,1,
};

static char large_elevation_marker[] =
{
	12,
	5,
	1,
	-2,
	0,0,0,0,0,1,1,1,1,1,1,1,
	0,0,0,0,1,0,0,0,0,0,0,1,
	1,1,1,1,0,0,0,0,0,0,0,1,
	0,0,0,0,1,0,0,0,0,0,0,1,
	0,0,0,0,0,1,1,1,1,1,1,1,
};

static char adv_elevation_marker[] =
{
	6,
	11,
	- 6,
	- 5,
	1,0,0,0,0,0,
	1,1,0,0,0,0,
	1,0,1,0,0,0,
	1,0,0,1,0,0,
	1,0,0,0,1,0,
	1,0,0,0,0,1,
	1,0,0,0,1,0,
	1,0,0,1,0,0,
	1,0,1,0,0,0,
	1,1,0,0,0,0,
	1,0,0,0,0,0,
};

static char cross[] =
{
	7,
	7,
	-3,
	-3,
	0,0,0,1,0,0,0,
	0,0,0,1,0,0,0,
	0,0,0,1,0,0,0,
	1,1,1,1,1,1,1,
	0,0,0,1,0,0,0,
	0,0,0,1,0,0,0,
	0,0,0,1,0,0,0,
};

static char dot[] =
{
	3,
	3,
	-1,
	-1,
	0,1,0,
	1,1,1,
	0,1,0,
};

static char small_elevation_marker[] =
{
	8,
	3,
	1,
	-1,
	0,0,0,1,1,1,1,1,
	1,1,1,0,0,0,0,1,
	0,0,0,1,1,1,1,1,
};

static char large_range_marker[] =
{
	12,
	5,
	-12,
	-2,
	1,1,1,1,1,1,1,0,0,0,0,0,
	1,0,0,0,0,0,0,1,0,0,0,0,
	1,0,0,0,0,0,0,0,1,1,1,1,
	1,0,0,0,0,0,0,1,0,0,0,0,
	1,1,1,1,1,1,1,0,0,0,0,0,
};

static char small_range_marker[] =
{
	8,
	3,
	-8,
	-1,
	1,1,1,1,1,0,0,0,
	1,0,0,0,0,1,1,1,
	1,1,1,1,1,0,0,0,
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_2d_eo_display (eo_params *eo, target_acquisition_systems system, int valid_3d, int scaled_3d)
{
	const char
		*s;
	char
		buffer[200];

	int
		heading_readout,
		has_range;

	float
		width,
		heading,
		marker_position,
		target_range = get_range_to_target(),
		y_adjust,
		i,
		j,
		x,
		y;

	entity
		*source,
		*target;

	vec3d
		*source_position,
		*target_position,
		target_point;

	viewpoint
		tmp;

	object_3d_visibility
		visibility;

	ASSERT (eo);

	source = get_gunship_entity ();

	source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

	target = get_local_entity_parent (source, LIST_TYPE_TARGET);

	has_range = get_range_finder() != RANGEFINDER_TRIANGULATION;

	if (target && has_range)
		target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

	////////////////////////////////////////
	//
	// text
	//
	////////////////////////////////////////

	set_mono_font_colour (MFD_COLOUR1);

	if (draw_large_mfd)
	{
		set_mono_font_type (MONO_FONT_TYPE_7X12);
	}
	else
	{
		set_mono_font_type (MONO_FONT_TYPE_5X7);
	}

	//
	// heading
	//

	heading = get_heading_from_attitude_matrix (eo_vp.attitude);

	if (heading < 0.0)
	{
		heading += rad (360.0);
	}

	heading_readout = (int) deg (heading);

	if (heading_readout == 0)
	{
		heading_readout = 360;
	}

	sprintf (buffer, "%d", heading_readout);

	width = get_mono_font_string_width (buffer);

	set_2d_mono_font_position (0.0, 1.0);

	set_mono_font_rel_position ((-width * 0.5) + 1.0, 1.0);

	print_mono_font_string (buffer);

	//
	// sensor type
	//

	set_2d_mono_font_position (-1.0, 1.0);

	set_mono_font_rel_position (1.0, 1.0);

	switch (system)
	{
		case TARGET_ACQUISITION_SYSTEM_FLIR:
		{
			print_mono_font_string ("FLIR");

			break;
		}
		case TARGET_ACQUISITION_SYSTEM_LLLTV:
		{
			print_mono_font_string ("LLLTV");

			break;
		}
		default:
		{
			print_mono_font_string ("XXX");

			break;
		}
	}

	if (eo_low_light)
	{
		set_2d_mono_font_position (-1.0, 0.9);

		if (draw_large_mfd)
		{
			set_mono_font_rel_position (1.0, -3.0);

			print_mono_font_string ("LOW LIGHT");
		}
		else
		{
			set_mono_font_rel_position (1.0, 2.0);

			print_mono_font_string ("LOW");
		}
	}

	//
	// field of view
	//

	switch (eo->field_of_view)
	{
		case EO_FOV_NARROW:
		{
			if (draw_large_mfd)
			{
				s = "NARROW";
			}
			else
			{
				s = "NAR";
			}

			break;
		}
		case EO_FOV_MEDIUM:
		{
			if (draw_large_mfd)
			{
				s = "MEDIUM";
			}
			else
			{
				s = "MED";
			}

			break;
		}
		case EO_FOV_WIDE:
		{
			s = "WIDE";

			break;
		}
		default:
		{
			s = "XXX";

			break;
		}
	}

	width = get_mono_font_string_width (s);

	set_2d_mono_font_position (1.0, 1.0);

	set_mono_font_rel_position (-width, 1.0);

	print_mono_font_string (s);

	//
	// target name
	//

	if (draw_large_mfd)
	{
		y_adjust = -8.0;
	}
	else
	{
		y_adjust = -4.0;
	}

	s = get_target_display_name (target, buffer, draw_large_mfd);

	if (s)
	{
		set_2d_mono_font_position (-1.0, -1.0);

		set_mono_font_rel_position (1.0, y_adjust);

		print_mono_font_string (s);
	}

	//
	// target range
	//

	if (target_range > 0.0)
	{
		if ((target_range < 1000.0) && (!havoc_damage.laser_range_finder))
		{
			sprintf (buffer, "%dm", (int) target_range);
		}
		else
		{
			sprintf (buffer, "%.1fKm", target_range * (1.0 / 1000.0));
		}

		width = get_mono_font_string_width (buffer);

		set_2d_mono_font_position (1.0, -1.0);

		set_mono_font_rel_position (-width, y_adjust);

		print_mono_font_string (buffer);
	}

	//
	// locked
	//

	if (eo_is_locked())
	{
		if (draw_large_mfd)
		{
			y_adjust = -21.0;
		}
		else
		{
			y_adjust = -11.0;
		}

		set_2d_mono_font_position (-1.0, -1.0);

		set_mono_font_rel_position (1.0, y_adjust);

		print_mono_font_string ("LOCKED");
	}
// Jabberwock 031107 Designated targets

	if (target && get_local_entity_parent (target, LIST_TYPE_DESIGNATED_TARGET))
	{
		if (draw_large_mfd)
		{
			y_adjust = -25.0;
		}
		else
		{
			y_adjust = -12.0;
		}

		width = get_mono_font_string_width ("MARKED");

		set_2d_mono_font_position (1.0, -1.0);

		set_mono_font_rel_position (-width - 1.0, y_adjust);

		print_mono_font_string ("MARKED");
	}
// Jabberwock 031107 ends

// added ground stabi by GCsDriver 08-12-2007
	//
	// 030418 loke
	// draw an indication if ground stablisation is enabled
	//

	if (eo_ground_stabilised)
	{
		if (draw_large_mfd) // Jabberwock 031107 Designated targets - moved the stab indicator one line up, sorry!
		{
			y_adjust = -38.0;
		}
		else
		{
			y_adjust = -19.0;
		}

		width = get_mono_font_string_width ("S");

		set_2d_mono_font_position (1.0, -1.0);

		set_mono_font_rel_position (-width, y_adjust);

		print_mono_font_string ("S");
	}

	////////////////////////////////////////
	//
	// line graphics
	//
	////////////////////////////////////////

	//
	// datum
	//

	if (draw_large_mfd)
	{
		draw_2d_line (-0.075, 0.0, -0.025, 0.0, MFD_COLOUR1);

		draw_2d_line (0.035, 0.0, 0.08, 0.0, MFD_COLOUR1);

		draw_2d_line (0.0, -0.075, 0.0, -0.025, MFD_COLOUR1);

		draw_2d_line (0.0, 0.035, 0.0, 0.08, MFD_COLOUR1);
	}
	else
	{
		draw_2d_line (-0.075, 0.0, -0.025, 0.0, MFD_COLOUR1);

		draw_2d_line (0.035, 0.0, 0.09, 0.0, MFD_COLOUR1);

		draw_2d_line (0.0, -0.075, 0.0, -0.025, MFD_COLOUR1);

		draw_2d_line (0.0, 0.035, 0.0, 0.09, MFD_COLOUR1);
	}

	//
	// azimuth
	//

	draw_2d_line (-0.5, 0.8, 0.5, 0.8, MFD_COLOUR1);

	marker_position = (eo_azimuth / eo_max_azimuth) * 0.5;

	if (draw_large_mfd)
	{
		draw_2d_line (-0.5, 0.8 - 0.02, -0.5, 0.8 + 0.02, MFD_COLOUR1);

		draw_2d_line (0.5, 0.8 - 0.02, 0.5, 0.8 + 0.02, MFD_COLOUR1);

		draw_2d_line (0.0, 0.8 - 0.01, 0.0, 0.8 + 0.01, MFD_COLOUR1);

		draw_2d_mono_sprite (large_azimuth_marker, marker_position, 0.8, MFD_COLOUR1);
	}
	else
	{
		draw_2d_line (-0.5, 0.8 - 0.03, -0.5, 0.8 + 0.03, MFD_COLOUR1);

		draw_2d_line (0.5, 0.8 - 0.03, 0.5, 0.8 + 0.03, MFD_COLOUR1);

		draw_2d_line (0.0, 0.8 - 0.02, 0.0, 0.8 + 0.02, MFD_COLOUR1);

		draw_2d_mono_sprite (small_azimuth_marker, marker_position, 0.8, MFD_COLOUR1);
	}

	//
	// elevation
	//

	draw_2d_line (-0.9, 0.2, -0.9, -0.6, MFD_COLOUR1);

	if (eo_elevation < 0.0)
	{
		marker_position = (eo_elevation / eo_min_elevation) * -0.6;
	}
	else
	{
		marker_position = (eo_elevation / eo_max_elevation) * 0.2;
	}

	if (draw_large_mfd)
	{
		draw_2d_line (-0.9 - 0.02, 0.2, -0.9 + 0.02, 0.2, MFD_COLOUR1);

		draw_2d_line (-0.9 - 0.02, -0.6, -0.9 + 0.02, -0.6, MFD_COLOUR1);

		draw_2d_line (-0.9 - 0.01, 0.0, -0.9 + 0.01, 0.0, MFD_COLOUR1);

		draw_2d_mono_sprite (large_elevation_marker, -0.9, marker_position, MFD_COLOUR1);
	}
	else
	{
		draw_2d_line (-0.9 - 0.03, 0.2, -0.9 + 0.03, 0.2, MFD_COLOUR1);

		draw_2d_line (-0.9 - 0.03, -0.6, -0.9 + 0.03, -0.6, MFD_COLOUR1);

		draw_2d_line (-0.9 - 0.02, 0.0, -0.9 + 0.02, 0.0, MFD_COLOUR1);

		draw_2d_mono_sprite (small_elevation_marker, -0.9, marker_position, MFD_COLOUR1);
	}

	//
	// range
	//

	draw_2d_line (0.9, 0.0, 0.9, -0.5, MFD_COLOUR1);

	if (draw_large_mfd)
	{
		draw_2d_line (0.9,  0.000, 0.9 + 0.02,  0.000, MFD_COLOUR1);
		draw_2d_line (0.9, -0.025, 0.9 + 0.01, -0.025, MFD_COLOUR1);
		draw_2d_line (0.9, -0.050, 0.9 + 0.01, -0.050, MFD_COLOUR1);
		draw_2d_line (0.9, -0.075, 0.9 + 0.01, -0.075, MFD_COLOUR1);

		draw_2d_line (0.9, -0.100, 0.9 + 0.02, -0.100, MFD_COLOUR1);
		draw_2d_line (0.9, -0.125, 0.9 + 0.01, -0.125, MFD_COLOUR1);
		draw_2d_line (0.9, -0.150, 0.9 + 0.01, -0.150, MFD_COLOUR1);
		draw_2d_line (0.9, -0.175, 0.9 + 0.01, -0.175, MFD_COLOUR1);

		draw_2d_line (0.9, -0.200, 0.9 + 0.02, -0.200, MFD_COLOUR1);
		draw_2d_line (0.9, -0.225, 0.9 + 0.01, -0.225, MFD_COLOUR1);
		draw_2d_line (0.9, -0.250, 0.9 + 0.01, -0.250, MFD_COLOUR1);
		draw_2d_line (0.9, -0.275, 0.9 + 0.01, -0.275, MFD_COLOUR1);

		draw_2d_line (0.9, -0.300, 0.9 + 0.02, -0.300, MFD_COLOUR1);

		draw_2d_line (0.9, -0.400, 0.9 + 0.02, -0.400, MFD_COLOUR1);

		draw_2d_line (0.9, -0.500, 0.9 + 0.02, -0.500, MFD_COLOUR1);
	}
	else
	{
		draw_2d_line (0.9,  0.000, 0.9 + 0.03,  0.000, MFD_COLOUR1);

		draw_2d_line (0.9, -0.100, 0.9 + 0.03, -0.100, MFD_COLOUR1);

		draw_2d_line (0.9, -0.200, 0.9 + 0.03, -0.200, MFD_COLOUR1);

		draw_2d_line (0.9, -0.300, 0.9 + 0.03, -0.300, MFD_COLOUR1);

		draw_2d_line (0.9, -0.400, 0.9 + 0.03, -0.400, MFD_COLOUR1);

		draw_2d_line (0.9, -0.500, 0.9 + 0.03, -0.500, MFD_COLOUR1);
	}

	if (target_range > 0.0)
	{
		marker_position = (min (target_range, eo_max_visual_range) / eo_max_visual_range) * -0.5;

		if (draw_large_mfd)
		{
			draw_2d_mono_sprite (large_range_marker, 0.9, marker_position, MFD_COLOUR1);
		}
		else
		{
			draw_2d_mono_sprite (small_range_marker, 0.9, marker_position, MFD_COLOUR1);
		}
	}

	//
	// target gates
	//

	if (target)
	{
		if (valid_3d)
		{
			tmp = main_vp;

			main_vp = eo_vp;

			get_local_entity_target_point (target, &target_point);

			visibility = get_position_3d_screen_coordinates (&target_point, &i, &j);

			if ((visibility == OBJECT_3D_COMPLETELY_VISIBLE) || (visibility == OBJECT_3D_PARTIALLY_VISIBLE))
			{
				if (scaled_3d)
				{
					i -= i_translate_3d;
					j -= j_translate_3d;

					i *= i_scale_3d;
					j *= j_scale_3d;
				}

				get_2d_world_position (i, j, &x, &y);

				draw_2d_line (x - 0.20, y + 0.20, x - 0.15, y + 0.20, MFD_COLOUR1);
				draw_2d_line (x + 0.20, y + 0.20, x + 0.15, y + 0.20, MFD_COLOUR1);
				draw_2d_line (x - 0.20, y - 0.20, x - 0.15, y - 0.20, MFD_COLOUR1);
				draw_2d_line (x + 0.20, y - 0.20, x + 0.15, y - 0.20, MFD_COLOUR1);
				draw_2d_line (x - 0.20, y + 0.20, x - 0.20, y + 0.15, MFD_COLOUR1);
				draw_2d_line (x - 0.20, y - 0.20, x - 0.20, y - 0.15, MFD_COLOUR1);
				draw_2d_line (x + 0.20, y + 0.20, x + 0.20, y + 0.15, MFD_COLOUR1);
				draw_2d_line (x + 0.20, y - 0.20, x + 0.20, y - 0.15, MFD_COLOUR1);
			}

			main_vp = tmp;
		}
	}
}

static void draw_adv_2d_eo_display (eo_params *eo, target_acquisition_systems system, int valid_3d, int scaled_3d)
{
	int
		has_range,
		k;

	float
		width,
		marker_position,
		target_range = get_range_to_target();

	entity
		*source,
		*target;

	vec3d
		*source_position;

	ASSERT (eo);

	source = get_gunship_entity ();

	source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

	target = get_local_entity_parent (source, LIST_TYPE_TARGET);

	if (target && last_target != target)
		last_target = target;

	has_range = get_range_finder() != RANGEFINDER_TRIANGULATION;

	////////////////////////////////////////
	//
	// text
	//
	////////////////////////////////////////

	set_mono_font_colour (MFD_COLOUR_DGREY);
	set_mono_font_type (MONO_FONT_TYPE_6X7);

	// sensor type

	set_2d_mono_font_position (-0.88, -0.84);
	set_mono_font_rel_position (0.0, 0.0);
	draw_2d_box(-0.9, -0.83, -0.55, -0.89, TRUE, FALSE, MFD_COLOUR_LGREY);

	switch (system)
	{
		case TARGET_ACQUISITION_SYSTEM_FLIR:
		{
			print_mono_font_string ("FLIR");

			break;
		}
		case TARGET_ACQUISITION_SYSTEM_LLLTV:
		{
			print_mono_font_string ("LLLTV");

			break;
		}
		default:
		{
			print_mono_font_string ("XXX");

			break;
		}
	}

// Jabberwock 031107 Designated targets

	if (target && get_local_entity_parent (target, LIST_TYPE_DESIGNATED_TARGET))
	{
		width = get_mono_font_string_width ("MARKED");

		set_2d_mono_font_position (1.0, -1.0);

		set_mono_font_rel_position (-width - 1.0, -25.0);

		print_mono_font_string ("MARKED");
	}
// Jabberwock 031107 ends

	// gyro stabilization

	if (eo_ground_stabilised)
	{
		set_2d_mono_font_position (0.78, -0.84);
		set_mono_font_rel_position (0.0, 0.0);
		draw_2d_box(0.96, -0.83, 0.76, -0.89, TRUE, FALSE, MFD_COLOUR_LGREY);

		print_mono_font_string ("GS");
	}

	// azimuth

	{
		char string[10];

		set_mono_font_colour (MFD_COLOUR_GREEN);
		set_mono_font_type (MONO_FONT_TYPE_3X6);

		draw_2d_line (-0.73, 0.72, 0.73, 0.72, MFD_COLOUR_GREEN);

		for (k = 0; k < 12; k++)
		{
			draw_2d_line(k * 0.0664, 0.72, k * 0.0664, 0.72 + 0.04 * (1 + !((k + (k == 11)) % 3)), MFD_COLOUR_GREEN);

			if (!((k + (k == 11)) % 3))
			{
				set_2d_mono_font_position (k * 0.0664, 0.8);
				sprintf(string, "%i", k * 10);
				width = get_mono_font_string_width (string);
				set_mono_font_rel_position (- 0.5 * width, - 7.0);
				print_mono_font_string (string);
			}
		}
		for (k = 1; k < 12; k++)
		{
			draw_2d_line(- k * 0.0664, 0.72, - k * 0.0664, 0.72 + 0.04 * (1 + !((k + (k == 11)) % 3)), MFD_COLOUR_GREEN);

			if (!((k + (k == 11)) % 3))
			{
				set_2d_mono_font_position (- k * 0.0664, 0.8);
				sprintf(string, "%i", - k * 10);
				width = get_mono_font_string_width (string);
				set_mono_font_rel_position (- 0.5 * width, - 7.0);
				print_mono_font_string (string);
			}
		}

		marker_position = (eo_azimuth / eo_max_azimuth) * 0.73;
		draw_2d_mono_sprite (large_azimuth_marker, marker_position, 0.72, MFD_COLOUR_GREEN);
	}

	// elevation

	set_mono_font_colour (MFD_COLOUR_GREEN);
	set_mono_font_type (MONO_FONT_TYPE_3X6);

	draw_2d_line (0.78, 0.28, 0.78, - 0.41, MFD_COLOUR_GREEN);
	for (k = 0; k < 16; k++)
	{
		char string[10];

		draw_2d_line(0.78, 0.28 - 0.046 * k, 0.78 + 0.02 * (1 + !((k + 3 * (k > 13)) % 2) + !((k + 3 * (k > 13)) % 6)), 0.28 - 0.046 * k, MFD_COLOUR_GREEN);

		if (!((k + 3 * (k > 13)) % 2))
		{
			set_2d_mono_font_position (0.83 + 0.02 * !((k + 3 * (k > 13)) % 6), 0.28 - 0.046 * k);
			set_mono_font_rel_position (1.0, - 2.0);
			sprintf(string, "%i", 30 - k * 5);
			print_mono_font_string (string);
		}
	}

	marker_position = - 0.41 + (eo_elevation - eo_min_elevation) / (eo_max_elevation - eo_min_elevation) * 0.69;
	draw_2d_mono_sprite (adv_elevation_marker, 0.78, marker_position, MFD_COLOUR_GREEN);


	// velocity

	{
		char buffer[10];

		set_mono_font_colour (MFD_COLOUR_GREEN);
		set_mono_font_type (MONO_FONT_TYPE_10X16);

		sprintf(buffer, "%1.0f", 3.6 * current_flight_dynamics->velocity_z.value);
		width = get_mono_font_string_width (buffer);
		set_2d_mono_font_position (-0.42, 0.72);
		set_mono_font_rel_position (- width, 16.0);
		print_mono_font_string (buffer);

		set_mono_font_type (MONO_FONT_TYPE_3X6);
		set_mono_font_rel_position (1.0, 7.0);
		print_mono_font_string ("km/h");
	}

	// altitude

	{
		char buffer[10];
		int radar = current_flight_dynamics->radar_altitude.value < 1500;

		set_mono_font_colour (MFD_COLOUR_GREEN);
		set_mono_font_type (MONO_FONT_TYPE_10X16);

		if (radar)
			sprintf(buffer, "%1.0f", current_flight_dynamics->radar_altitude.value);
		else
			sprintf(buffer, "%1.0f", current_flight_dynamics->position.y);

		width = get_mono_font_string_width (buffer);
		set_2d_mono_font_position (0.5, 0.72);
		set_mono_font_rel_position (- width, 16.0);
		print_mono_font_string (buffer);

		set_mono_font_type (MONO_FONT_TYPE_3X6);
		set_mono_font_rel_position (1.0, 7.0);

		if (radar)
			print_mono_font_string ("r");
		else
			print_mono_font_string ("b");
	}

	// target range

	if (target)
	{
		char buffer[10];

		set_mono_font_colour (MFD_COLOUR_GREEN);
		set_mono_font_type (MONO_FONT_TYPE_10X16);
		sprintf(buffer, "%.1f", target_range / 1000);
		set_2d_mono_font_position (-0.1, -0.66);
		set_mono_font_rel_position (1.0, 1.0);
		print_mono_font_string (buffer);
	}

	// target gates

	if (valid_3d)
	{
		float scale = 8 / (2 * (float)eo->field_of_view + 1), x, y;

		if (eo_is_locked())
		{
			move_targeting_gates(&x, &y);
			set_2d_instance_position(mfd_env, x, y);

			draw_2d_dash_line(- 0.13 * scale, 0.0, - 0.07 * scale, 0, MFD_COLOUR_LGREY, MFD_COLOUR_DGREY, 0.02, FALSE);
			draw_2d_dash_line(0.13 * scale, 0.0, 0.07 * scale, 0, MFD_COLOUR_LGREY, MFD_COLOUR_DGREY, 0.02, FALSE);
			draw_2d_line(0.0, 0.13 * scale, 0.0, 0.07 * scale, MFD_COLOUR_LGREY);
			draw_2d_line(0.0, - 0.13 * scale, 0.0, - 0.07 * scale, MFD_COLOUR_LGREY);

			draw_2d_dash_line(- 0.1 * scale, 0.1 * scale, - 0.05 * scale, 0.1 * scale, MFD_COLOUR_LGREY, MFD_COLOUR_DGREY, 0.02, FALSE);
			draw_2d_dash_line(0.1 * scale, 0.1 * scale, 0.05 * scale, 0.1 * scale, MFD_COLOUR_LGREY, MFD_COLOUR_DGREY, 0.02, FALSE);
			draw_2d_dash_line(- 0.1 * scale, - 0.1 * scale, - 0.05 * scale, - 0.1 * scale, MFD_COLOUR_LGREY, MFD_COLOUR_DGREY, 0.02, FALSE);
			draw_2d_dash_line(0.1 * scale, - 0.1 * scale, 0.05 * scale, - 0.1 * scale, MFD_COLOUR_LGREY, MFD_COLOUR_DGREY, 0.02, FALSE);

			draw_2d_line(- 0.1 * scale, 0.1 * scale, - 0.1 * scale, 0.05 * scale, MFD_COLOUR_LGREY);
			draw_2d_line(- 0.1 * scale, - 0.1 * scale, - 0.1 * scale, - 0.05 * scale, MFD_COLOUR_LGREY);
			draw_2d_line(0.1 * scale, 0.1 * scale, 0.1 * scale, 0.05 * scale, MFD_COLOUR_LGREY);
			draw_2d_line(0.1 * scale, - 0.1 * scale, 0.1 * scale, - 0.05 * scale, MFD_COLOUR_LGREY);

			set_2d_pixel(0.0, 0.0, MFD_COLOUR_LGREY);
		}
		else
		{
			draw_2d_dash_line(- 0.1 * scale, 0.0, - 0.04 * scale, 0, MFD_COLOUR_LGREY, MFD_COLOUR_DGREY, 0.02, FALSE);
			draw_2d_dash_line(0.1 * scale, 0.0, 0.04 * scale, 0, MFD_COLOUR_LGREY, MFD_COLOUR_DGREY, 0.02, FALSE);
			draw_2d_line(0.0, 0.1 * scale, 0.0, 0.04 * scale, MFD_COLOUR_LGREY);
			draw_2d_line(0.0, - 0.1 * scale, 0.0, - 0.04 * scale, MFD_COLOUR_LGREY);

			draw_2d_dash_line(- 0.1 * scale, 0.1 * scale, 0.1 * scale, 0.1 * scale, MFD_COLOUR_LGREY, MFD_COLOUR_DGREY, 0.04, TRUE);
			draw_2d_dash_line(- 0.1 * scale, - 0.1 * scale, 0.1 * scale, - 0.1 * scale, MFD_COLOUR_LGREY, MFD_COLOUR_DGREY, 0.04, TRUE);

			draw_2d_line(- 0.1 * scale, 0.1 * scale, - 0.1 * scale, - 0.1 * scale, MFD_COLOUR_LGREY);
			draw_2d_line(0.1 * scale, 0.1 * scale, 0.1 * scale, - 0.1 * scale, MFD_COLOUR_LGREY);

			set_2d_pixel(0.0, 0.0, MFD_COLOUR_LGREY);
		}

		reset_2d_instance(mfd_env);
	}
	// weapon info

	{
		entity_sub_types weapon_sub_type;
		char s[80], *weapon_type;

		weapon_sub_type = get_local_entity_int_value (get_gunship_entity (), INT_TYPE_SELECTED_WEAPON);

		if (weapon_sub_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
		{
			float flight_time = get_missile_flight_time ();

			switch (weapon_sub_type)
			{
				case ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND:
				case ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND:
				{
					if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND)
						weapon_type = "HE";
					else
						weapon_type = "AP";
					break;
				}
				case ENTITY_SUB_TYPE_WEAPON_9M120_ATAKA_V:
				{
					weapon_type = "MSL";
					break;
				}
				case ENTITY_SUB_TYPE_WEAPON_9M39_IGLA_V:
				{
					weapon_type = "ATA";
					break;
				}
				default:
				{
					if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND)
						weapon_type = "GUN";
					else
						weapon_type = "RKT";
				}
			}

			set_mono_font_colour (MFD_COLOUR_GREEN);
			set_mono_font_type (MONO_FONT_TYPE_5X9);
			set_2d_mono_font_position (0.7, - 0.8);
			set_mono_font_rel_position (0.0, 0.0);
			print_mono_font_string (weapon_type);

			if (flight_time > 0.01)
			{
				set_mono_font_colour (MFD_COLOUR_GREEN);
				set_mono_font_type (MONO_FONT_TYPE_6X7);
				flight_time = bound (flight_time, 0.0, 99.9);
				sprintf (s, "%1.0f s", flight_time + 0.5);
				set_2d_mono_font_position (0, -0.51);
				set_mono_font_rel_position (1.0, 1.0);
				print_mono_font_string (s);
			}
			else if (!get_local_entity_weapon_available (get_gunship_entity(), weapon_sub_type))
			{
				draw_2d_line(-1.0, -1.0, 1.0, 1.0, MFD_COLOUR_GREEN);
				draw_2d_line(1.0, - 1.0, - 1.0, 1.0, MFD_COLOUR_GREEN);
			}


		}
	}

	// view sector

	{
		float angle[] = {0, rad(-110), rad(110), 0};

		angle[3] = eo_azimuth;

		for(k = 0; k < 4; k++)
		{
			float length = k < 3 ? 0.22 : 0.18;

			draw_2d_line(-0.73, -0.64, -0.73 + length * sin(angle[k]), -0.64 + length * cos(angle[k]), k < 3 ? MFD_COLOUR_BLUE : MFD_COLOUR_GREEN);

			if (k == 3)
				draw_2d_mono_sprite (dot, -0.73 + length * sin(angle[k]), -0.64 + length * cos(angle[k]), MFD_COLOUR_GREEN);
		}

		if (last_target)
		{
			vec3d *target_position;
			float source_heading, target_azimuth, pitch, target_range;
			vec3d heading;

			target_position = get_local_entity_vec3d_ptr(last_target, VEC3D_TYPE_POSITION);
			target_range = get_2d_range(target_position, source_position) / 1000;

			if (target_range < 10)
			{
				source_heading = get_local_entity_float_value (source, FLOAT_TYPE_HEADING);

				heading.x = target_position->x - source_position->x;
				heading.z = target_position->z - source_position->z;
				normalise_3d_vector(&heading);
				get_heading_and_pitch_from_3d_unit_vector(&heading, &target_azimuth, &pitch);

				draw_2d_mono_sprite (cross, -0.73 + 0.024 * target_range * sin(target_azimuth - source_heading), -0.64 + 0.024 * target_range * cos(target_azimuth - source_heading), MFD_COLOUR_RED);
			}
		}

		draw_2d_circle (-0.73, -0.64, 0.24, MFD_COLOUR_GREEN);

		set_mono_font_colour (MFD_COLOUR_GREEN);
		set_mono_font_type (MONO_FONT_TYPE_6X10);
		set_2d_mono_font_position (-0.79, -0.33);
		set_mono_font_rel_position (1.0, 1.0);
		print_mono_font_string ("10");


	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// FLIR
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_3d_flir_mfd (void)
{
	draw_3d_eo_display (&havoc_flir, TARGET_ACQUISITION_SYSTEM_FLIR);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_2d_flir_mfd (int valid_3d, int scaled_3d)
{
	if (command_line_advanced_mfd && command_line_colour_mfd && draw_large_mfd)
		draw_adv_2d_eo_display (&havoc_flir, TARGET_ACQUISITION_SYSTEM_FLIR, valid_3d, scaled_3d);
	else
		draw_2d_eo_display (&havoc_flir, TARGET_ACQUISITION_SYSTEM_FLIR, valid_3d, scaled_3d);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// LLLTV
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_3d_llltv_mfd (void)
{
	draw_3d_eo_display (&havoc_llltv, TARGET_ACQUISITION_SYSTEM_LLLTV);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_2d_llltv_mfd (int valid_3d, int scaled_3d)
{
	if (command_line_advanced_mfd && command_line_colour_mfd && draw_large_mfd)
		draw_adv_2d_eo_display (&havoc_llltv, TARGET_ACQUISITION_SYSTEM_LLLTV, valid_3d, scaled_3d);
	else
		draw_2d_eo_display (&havoc_llltv, TARGET_ACQUISITION_SYSTEM_LLLTV, valid_3d, scaled_3d);
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DRAW MFD ON COCKPIT
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_havoc_mfd_on_cockpit (float x_org, float y_org, int large_mfd, int draw_translucent_background)
{
#ifndef OGRE_EE
	if (havoc_damage.tv_display)
	{
		if (mfd_mode != MFD_MODE_OFF)
		{
			mfd_mode = MFD_MODE_DAMAGED;
		}
	}
	else
	{
		if (mfd_mode == MFD_MODE_DAMAGED)
		{
			mfd_mode = MFD_MODE_OFF;
		}
	}

	////////////////////////////////////////
	//
	// set up MFD 2D environment
	//
	////////////////////////////////////////

	set_2d_active_environment (mfd_env);

	//
	// window
	//

	set_2d_window (mfd_env, MFD_WINDOW_X_MIN, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX, MFD_WINDOW_Y_MAX);

	//
	// viewport
	//

	draw_large_mfd = large_mfd;

	if (draw_large_mfd)
	{
		mfd_viewport_size = MFD_VIEWPORT_LARGE_SIZE;
	}
	else
	{
		mfd_viewport_size = MFD_VIEWPORT_SMALL_SIZE;
	}

	mfd_viewport_x_org = x_org;

	mfd_viewport_y_org = y_org;

	mfd_viewport_x_min = mfd_viewport_x_org - (mfd_viewport_size * 0.5);

	mfd_viewport_y_min = mfd_viewport_y_org - (mfd_viewport_size * 0.5);

	mfd_viewport_x_max = mfd_viewport_x_org + (mfd_viewport_size * 0.5);

	mfd_viewport_y_max = mfd_viewport_y_org + (mfd_viewport_size * 0.5);

	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

	////////////////////////////////////////
	//
	// draw translucent background
	//
	////////////////////////////////////////

	if (draw_translucent_background)
	{
		if (!draw_large_mfd)
		{
			if
			(
				(mfd_mode == MFD_MODE_DAMAGED) ||
				(mfd_mode == MFD_MODE_GROUND_RADAR) ||
				(mfd_mode == MFD_MODE_AIR_RADAR)
			)
			{
				vertex
					quad[4];

				real_colour
					colour,
					specular;

				float
					x_min,
					y_min,
					x_max,
					y_max;

				if (begin_3d_scene ())
				{
					colour.red = 0;
					colour.green = 0;
					colour.blue = 0;
					colour.alpha = 64;

					specular.red = 0;
					specular.green = 0;
					specular.blue = 0;
					specular.alpha = 255;

					set_d3d_transparency_on ();

					set_d3d_zbuffer_comparison (FALSE);

					set_d3d_plain_renderstate ();

					set_d3d_culling (FALSE);

					//
					// match co-ordinates with small EO 3D display
					//

					x_min = mfd_viewport_x_min - 31.0;
					y_min = mfd_viewport_y_min - 10.0;
					x_max = x_min + 176.0;
					y_max = y_min + 132.0;

					quad[0].i = x_min;
					quad[0].j = y_min;
					quad[0].z = 0.5;
					quad[0].q = 0.5;
					quad[0].next_vertex = &quad[1];

					quad[1].i = x_max;
					quad[1].j = y_min;
					quad[1].z = 0.5;
					quad[1].q = 0.5;
					quad[1].next_vertex = &quad[2];

					quad[2].i = x_max;
					quad[2].j = y_max;
					quad[2].z = 0.5;
					quad[2].q = 0.5;
					quad[2].next_vertex = &quad[3];

					quad[3].i = x_min;
					quad[3].j = y_max;
					quad[3].z = 0.5;
					quad[3].q = 0.5;
					quad[3].next_vertex = NULL;

					draw_wbuffered_plain_polygon (quad, colour, specular);

					set_d3d_transparency_off ();

					set_d3d_zbuffer_comparison (TRUE);

					end_3d_scene ();
				}
			}
		}
	}

	////////////////////////////////////////
	//
	// draw MFD
	//
	////////////////////////////////////////

	switch (mfd_mode)
	{
		////////////////////////////////////////
		case MFD_MODE_OFF:
		////////////////////////////////////////
		{
			if (lock_screen (active_screen))
			{
				draw_mfd_layout_grid ();

				unlock_screen (active_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_DAMAGED:
		////////////////////////////////////////
		{
			if (lock_screen (active_screen))
			{
				draw_mfd_layout_grid ();

				draw_damaged_mfd ();

				unlock_screen (active_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_GROUND_RADAR:
		////////////////////////////////////////
		{
			if (lock_screen (active_screen))
			{
				draw_mfd_layout_grid ();

				draw_ground_radar_mfd ();

				unlock_screen (active_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_AIR_RADAR:
		////////////////////////////////////////
		{
			if (lock_screen (active_screen))
			{
				draw_mfd_layout_grid ();

				draw_air_radar_mfd ();

				unlock_screen (active_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_FLIR:
		////////////////////////////////////////
		{
			draw_3d_flir_mfd ();

			if (lock_screen (active_screen))
			{
				draw_mfd_layout_grid ();

				draw_2d_flir_mfd (TRUE, FALSE);

				unlock_screen (active_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_LLLTV:
		////////////////////////////////////////
		{
			draw_3d_llltv_mfd ();

			if (lock_screen (active_screen))
			{
				draw_mfd_layout_grid ();

				draw_2d_llltv_mfd (TRUE, FALSE);

				unlock_screen (active_screen);
			}

			break;
		}
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// FLIGHT				Javelin  6/19	A lot of what follows is for the Exported FLIGHT MFD
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//
// HEADING SCALE			
//
////////////////////////////////////////

static void draw_heading_scale (float heading, int draw_command_heading)
{
	float
		y_position,
		mfd_vp_x_min,
		mfd_vp_x_max,
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

	if (draw_large_mfd)
	{
		y_position = -0.85;
	}
	else
	{
		y_position = -0.8375;
	}

	draw_2d_box(-0.5, y_position - 0.1, 0.5, y_position + 0.1, TRUE, FALSE, MFD_COLOUR_BLUE);
	draw_2d_box(-0.5, y_position - 0.1, 0.5, y_position + 0.1, FALSE, FALSE, MFD_COLOUR_LIGHT_BLUE);

	set_2d_window (mfd_env, MFD_WINDOW_X_MIN * 0.5, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX * 0.5, MFD_WINDOW_Y_MAX);

	mfd_vp_x_min = mfd_viewport_x_org - (mfd_viewport_size * (0.5 * 0.5));

	mfd_vp_x_max = mfd_viewport_x_org + (mfd_viewport_size * (0.5 * 0.5));

	set_2d_viewport (mfd_env, mfd_vp_x_min, mfd_viewport_y_min, mfd_vp_x_max, mfd_viewport_y_max);

	//
	// large and small MFD position
	//


	//
	// draw heading scale line
	//

//	draw_2d_line (-0.5, y_position, 0.5, y_position, MFD_COLOUR1);

	//
	// large and small MFD differences
	//

	get_2d_float_screen_coordinates (0.0, y_position, &i, &j);

	set_mono_font_type (MONO_FONT_TYPE_5X9);

	//
	// draw command heading carat
	//

	if (draw_command_heading)
	{
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

				command_heading = bearing - heading;

				if (command_heading > rad (180.0))
				{
					command_heading -= rad (360.0);
				}
				else if (command_heading < rad (-180.0))
				{
					command_heading += rad (360.0);
				}

				command_heading = bound (command_heading, rad (-20.0), rad (20.0));

				get_2d_float_screen_coordinates (deg(command_heading) * (0.025), y_position + 0.05, &i, &j);

				draw_mono_sprite (large_command_heading_carat, i, j + 1.0, MFD_COLOUR_LIGHT_BLUE);
			}
		}
	}

	//
	// sort first major tick position (draw 2 major ticks either side of centre)
	//

	heading = deg (heading);

	mod_heading_step_10 = fmod (heading, 10.0f);

	int_heading_step_10 = ((int) (heading * 0.1) * 10);

	int_heading_step_10 -= 40;

	if (int_heading_step_10 < 0)
	{
		int_heading_step_10 += 360;
	}

	x = - (40.0 + mod_heading_step_10) * 0.025;

	//
	// draw heading scale ticks and heading value
	//

	for (loop = 0; loop < 20; loop++)
	{
		//
		// major tick every 10 degrees
		//

		draw_2d_line (x, y_position + 0.1, x, y_position + 0.05, MFD_COLOUR_LIGHT_BLUE);

		//
		// minor tick every 5 degrees
		//

		draw_2d_line (x + 0.125, y_position + 0.1, x + 0.125, y_position + 0.075, MFD_COLOUR_LIGHT_BLUE);

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

		set_2d_mono_font_position (x, y_position - 0.1);

		width = get_mono_font_string_width (s);

		set_mono_font_rel_position ((-width * 0.5) + 1.0, -10.0);

		print_mono_font_string (s);

		//
		// next heading value
		//

		int_heading_step_10 += 10;

		if (int_heading_step_10 == 360)
		{
			int_heading_step_10 = 0;
		}

		x += 0.25;
	}

	//
	// restore 2D environment
	//

	set_2d_window (mfd_env, MFD_WINDOW_X_MIN, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX, MFD_WINDOW_Y_MAX);

	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);
}


static void draw_sideslip_scale (void)
{
	float
		sideslip = kilometres_per_hour(current_flight_dynamics->velocity_x.value),
		y_position,
		mfd_vp_x_min,
		mfd_vp_x_max,
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

	y_position = -0.65;

	set_2d_window (mfd_env, MFD_WINDOW_X_MIN * 0.5, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX * 0.5, MFD_WINDOW_Y_MAX);

	mfd_vp_x_min = mfd_viewport_x_org - (mfd_viewport_size * (0.5 * 0.5));

	mfd_vp_x_max = mfd_viewport_x_org + (mfd_viewport_size * (0.5 * 0.5));

	set_2d_viewport (mfd_env, mfd_vp_x_min, mfd_viewport_y_min, mfd_vp_x_max, mfd_viewport_y_max);


	get_2d_float_screen_coordinates (0.0, y_position, &i, &j);

	set_mono_font_type (MONO_FONT_TYPE_5X7);


	//
	// sort first major tick position (draw 2 major ticks either side of centre)
	//

	mod_heading_step_10 = fmod (sideslip, 10.0f);
	int_heading_step_10 = ((int) (sideslip * 0.1) * 10);
	int_heading_step_10 -= 40;

	x = - (40.0 + mod_heading_step_10) * 0.025;

	//
	// draw heading scale ticks and heading value
	//

	for (loop = 0; loop < 20; loop++)
	{
		//
		// minor tick every 5 kph
		//

		draw_2d_line (x + 0.125, y_position + 0.025, x + 0.125, y_position - 0.025, MFD_COLOUR_LIGHT_BLUE);

		sprintf (s, "%d", abs(int_heading_step_10));

		set_2d_mono_font_position (x, y_position);
		width = get_mono_font_string_width (s);
		set_mono_font_rel_position ((-width * 0.5) + 1.0, -3.0);

		print_mono_font_string (s);

		//
		// next heading value
		//

		int_heading_step_10 += 10;

		if (int_heading_step_10 == 360)
		{
			int_heading_step_10 = 0;
		}

		x += 0.25;
	}

	//
	// restore 2D environment
	//

	set_2d_window (mfd_env, MFD_WINDOW_X_MIN, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX, MFD_WINDOW_Y_MAX);

	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);
}

////////////////////////////////////////
//
// pitch ladder
//
////////////////////////////////////////

#define PITCH_DATUM_X	((float) 0.0)
#define PITCH_DATUM_Y	((float) 0.0)

//                   P10 O (+ve)  O  P9
//                                |
//                                |
// P1    P2    P3    P4    P5    P6    P7
//  O-----O-----O-----O-----O-----O-----O
//                                |
//                                |
//                                |
//                   P11 O (-ve)  O  P8

#define PITCH_BAR_X1		((float) +0.1000)
#define PITCH_BAR_Y1		((float) +0.0000)
#define PITCH_BAR_X2		((float) +0.1375)
#define PITCH_BAR_Y2		((float) +0.0000)
#define PITCH_BAR_X3		((float) +0.1750)
#define PITCH_BAR_Y3		((float) +0.0000)
#define PITCH_BAR_X4		((float) +0.2125)
#define PITCH_BAR_Y4		((float) +0.0000)
#define PITCH_BAR_X5		((float) +0.2500)
#define PITCH_BAR_Y5		((float) +0.0000)
#define PITCH_BAR_X6		((float) +0.2875)
#define PITCH_BAR_Y6		((float) +0.0000)
#define PITCH_BAR_X7		((float) +0.3250)
#define PITCH_BAR_Y7		((float) +0.0000)
#define PITCH_BAR_X8		((float) +0.2875)
#define PITCH_BAR_Y8		((float) -0.0250)
#define PITCH_BAR_X9		((float) +0.2875)
#define PITCH_BAR_Y9		((float) +0.0250)
#define PITCH_BAR_X10	((float) +0.265)
#define PITCH_BAR_Y10	((float) +0.050)
#define PITCH_BAR_X11	((float) +0.265)
#define PITCH_BAR_Y11	((float) -0.050)

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
static void draw_pitch_ladder (void)
{
	char
		s[20];

	int
		int_pitch,
		step_direction,
		loop;

	float
		y_adjust_above_line,
		y_adjust_below_line,
		x_centre,
		y_centre = 0.0,
		size,
		vp_size,
		pitch,
		mod_pitch,
		tan_mod_pitch,
		pitch_bar_scale,
		roll,
		u,
		v,
		x,
		y,
		left_edge,
		right_edge,
		upper_edge,
		lower_edge,
		x_scale,
		y_scale,
		x_horizon,
		y_horizon,
		x_10_deg_step,
		y_10_deg_step,
		x_adjust;

	rgb_colour
		sky_colour,
		ground_colour;

	if (command_line_colour_mfd)
	{
		sky_colour.red = 0;
		sky_colour.green = 120;
		sky_colour.blue = 192;
		sky_colour.alpha = 255;

		ground_colour.red =   0;
		ground_colour.green =  90;
		ground_colour.blue =  10;
		ground_colour.alpha = 255;
	}
	else
	{
		sky_colour = MFD_COLOUR2;
		ground_colour = MFD_COLOUR5;
	}

	if (draw_large_mfd)
	{
		set_mono_font_type (MONO_FONT_TYPE_5X9);

		y_adjust_above_line = -3.0;
		y_adjust_below_line = -3.0;
	}
	else
	{
		set_mono_font_type (MONO_FONT_TYPE_3X6);

		y_adjust_above_line = -3.0;
		y_adjust_below_line = -1.0;
	}

	x_centre = 0.0;

	size = 0.53;			//  0.59
	pitch_bar_scale = 0.8;

	//
	//

	get_2d_float_screen_coordinates (PITCH_DATUM_X, PITCH_DATUM_Y, &u, &v);
	roll = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_ROLL);

	//
	// set 2D environment
	//

	set_2d_window (mfd_env, MFD_WINDOW_X_MIN * size, MFD_WINDOW_Y_MIN * size, MFD_WINDOW_X_MAX * size, MFD_WINDOW_Y_MAX * size);

	vp_size = mfd_viewport_size * size * 0.5;
	set_2d_viewport (mfd_env, u - (vp_size), v - vp_size, u + (vp_size), v + vp_size);

	upper_edge = 0.5 * size;
	left_edge = -(size * 0.5);
	right_edge = (size * 0.5);
	lower_edge = -0.5 * size;

//	set_2d_viewport (mfd_env, u + left_edge, v + upper_edge, u + right_edge, v + lower_edge);


	//
	// pitch
	//

	{
		float
			x_horizon_abs,
			y_horizon_abs,
			tan_pitch;

		int inverted = (roll < -rad(90)) || (roll > rad(90));

		pitch = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_PITCH);
		tan_pitch = -tan(pitch);
		mod_pitch = fmod (pitch, rad (10.0f));
		tan_mod_pitch = -tan (mod_pitch);
		int_pitch = (int) (pitch * (1.0 / rad (10.0)));

		//
		// get x and y scale factors
		//

		x_scale = -sin (roll) * 1.5 * pitch_bar_scale;
		y_scale = cos (roll) * 1.5 * pitch_bar_scale;

		x_horizon = tan_mod_pitch * x_scale;
		y_horizon = tan_mod_pitch * y_scale;

		x_10_deg_step = tan (rad (10.0)) * x_scale;
		y_10_deg_step = tan (rad (10.0)) * y_scale;

		x_horizon_abs = tan_pitch * x_scale;
		y_horizon_abs = tan_pitch * y_scale;

		// draw horizon
		set_2d_pixel(x_horizon_abs, y_horizon_abs, MFD_COLOUR1);
		if (roll != -rad(90) && roll != rad(90))
		{
			float incline = tan(roll);
			float left_y, right_y;
			float start_x = -1.0, end_x = 1.0;

			left_y = (x_horizon_abs - left_edge) * -incline;
			right_y = (right_edge - x_horizon_abs) * incline;

			if (incline < 0.0)
			{
				// find where horizon intersects top and bottom
				start_x = x_horizon_abs + ((1 - y_horizon_abs) / incline);
				end_x = x_horizon_abs + ((-2 - y_horizon_abs) / incline);
			}

			draw_2d_line(left_edge, left_y, right_edge, right_y, sys_col_red);

			left_y = y_horizon_abs + (1.0 + x_horizon_abs) * -incline;
			right_y = y_horizon_abs + (1.0 - x_horizon_abs) * incline;

			if (inverted)
			{
				rgb_colour tmp = sky_colour;
				sky_colour = ground_colour;
				ground_colour = tmp;
			}

			draw_2d_filled_triangle(-1.0, left_y, -1.0, 1.0, 1.0, right_y, sky_colour);
			draw_2d_filled_triangle(start_x, 1.0, 1.0, 1.0, 1.0, right_y, sky_colour);

			draw_2d_filled_triangle(-1.0, left_y, end_x, -2.0, -1.0, -2.0, ground_colour);
			draw_2d_filled_triangle(-1.0, left_y, 1.0, right_y, 1.0, -2.0, ground_colour);
		}
		else  // 90 degree bank
		{
			rgb_colour
				*left_colour,
				*right_colour;

			if (roll == rad(90))
			{
				left_colour = &ground_colour;
				right_colour = &sky_colour;
			}
			else
			{
				left_colour = &sky_colour;
				right_colour = &ground_colour;
			}

			draw_2d_filled_triangle(x_horizon_abs, 1.0, 1.0, 1.0, 1.0, -1.0, *right_colour);
			draw_2d_filled_triangle(1.0, -1.0, x_horizon_abs, -1.0, x_horizon_abs, 1.0, *right_colour);

			draw_2d_filled_triangle(-1.0, 1.0, x_horizon_abs, 1.0, x_horizon_abs, -1.0, *left_colour);
			draw_2d_filled_triangle(x_horizon_abs, -1.0, -1.0, -1.0, -1.0, 1.0, *left_colour);
		}

		////////////////////////////////////////
		//
		// draw pitch ladder
		//
		////////////////////////////////////////

		step_direction = -1;

		int_pitch = limit_pitch (int_pitch + 3, &step_direction);

		x = x_horizon + x_10_deg_step * 3.0;
		y = y_horizon + y_10_deg_step * 3.0;

		set_2d_instance_rotation (mfd_env, roll);

		for (loop = 0; loop < 7; loop++)
		{
			set_2d_instance_position (mfd_env, x, y);

			switch (int_pitch)
			{
				////////////////////////////////////////
				case 0:
				////////////////////////////////////////
				{
					break;
				}
				////////////////////////////////////////
				default:
				////////////////////////////////////////
				{
					draw_2d_line (-PITCH_BAR_X2, PITCH_BAR_Y2, PITCH_BAR_X2, -PITCH_BAR_Y2, MFD_COLOUR_LIGHT_BLUE);

					sprintf (s, "%d0", abs(int_pitch));
					x_adjust = get_mono_font_string_width (s) * -0.5;

					set_2d_mono_font_position (+PITCH_BAR_X4, +PITCH_BAR_Y4);
					set_mono_font_rel_position (x_adjust, y_adjust_above_line);
					print_mono_font_string (s);

					set_2d_mono_font_position (-PITCH_BAR_X4, +PITCH_BAR_Y4);
					set_mono_font_rel_position (x_adjust, y_adjust_above_line);
					print_mono_font_string (s);

					break;
				}
				////////////////////////////////////////
				case 9:
				////////////////////////////////////////
				{
					draw_2d_line (+PITCH_BAR_X1, +PITCH_BAR_Y1, +PITCH_BAR_X6, +PITCH_BAR_Y6, MFD_COLOUR_LIGHT_BLUE);
					draw_2d_line (-PITCH_BAR_X1, +PITCH_BAR_Y1, -PITCH_BAR_X6, +PITCH_BAR_Y6, MFD_COLOUR_LIGHT_BLUE);

					break;
				}
				////////////////////////////////////////
				case -9:
				////////////////////////////////////////
				{
					draw_2d_line (+PITCH_BAR_X1, +PITCH_BAR_Y1, +PITCH_BAR_X2, +PITCH_BAR_Y2, MFD_COLOUR_LIGHT_BLUE);
					draw_2d_line (-PITCH_BAR_X1, +PITCH_BAR_Y1, -PITCH_BAR_X2, +PITCH_BAR_Y2, MFD_COLOUR_LIGHT_BLUE);

					draw_2d_line (+PITCH_BAR_X3, +PITCH_BAR_Y3, +PITCH_BAR_X4, +PITCH_BAR_Y4, MFD_COLOUR_LIGHT_BLUE);
					draw_2d_line (-PITCH_BAR_X3, +PITCH_BAR_Y3, -PITCH_BAR_X4, +PITCH_BAR_Y4, MFD_COLOUR_LIGHT_BLUE);

					draw_2d_line (+PITCH_BAR_X5, +PITCH_BAR_Y5, +PITCH_BAR_X6, +PITCH_BAR_Y6, MFD_COLOUR_LIGHT_BLUE);
					draw_2d_line (-PITCH_BAR_X5, +PITCH_BAR_Y5, -PITCH_BAR_X6, +PITCH_BAR_Y6, MFD_COLOUR_LIGHT_BLUE);

					break;
				}
			}

			int_pitch = limit_pitch (int_pitch + step_direction, &step_direction);

			x -= x_10_deg_step;
			y -= y_10_deg_step;
		}
	}

	//
	// restore 2D environment
	//

	reset_2d_instance (mfd_env);

	set_2d_window (mfd_env, MFD_WINDOW_X_MIN, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX, MFD_WINDOW_Y_MAX);

	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

	draw_2d_mono_sprite (main_horizon_mask, x_centre, y_centre, MFD_COLOUR_BLACK);

	//
	// restore 2D environment
	//

	reset_2d_instance (mfd_env);
	set_2d_window (mfd_env, MFD_WINDOW_X_MIN, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX, MFD_WINDOW_Y_MAX);
	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);
}

static void draw_aircraft_datum(void)
{
	float y_centre = 0.0;

	draw_2d_half_thick_line(0.15, y_centre, 0.4, y_centre, MFD_COLOUR_YELLOW);
	draw_2d_half_thick_line(-0.15, y_centre, -0.4, y_centre, MFD_COLOUR_YELLOW);

	draw_2d_half_thick_line(0.15, y_centre, 0.15, y_centre - 0.05, MFD_COLOUR_YELLOW);
	draw_2d_half_thick_line(-0.15, y_centre, -0.15, y_centre - 0.05, MFD_COLOUR_YELLOW);

	draw_2d_half_thick_line(0.5, y_centre, 0.7, y_centre, MFD_COLOUR_YELLOW);
	draw_2d_half_thick_line(-0.5, y_centre, -0.7, y_centre, MFD_COLOUR_YELLOW);

	draw_2d_half_thick_line(0.0, y_centre - 0.6, 0.0, y_centre - 0.75, MFD_COLOUR_YELLOW);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_altitude_scale (void)
{
	const float
		y_centre = 0.0,
		box_start = 0.7,
		box_end = box_start + 0.25,
		box_top = y_centre + 0.04,
		box_bottom = y_centre - 0.04,
		x1 = box_start,
		x2 = x1 + 0.03,
//		x3 = x1 + 0.125,
		x5 = box_end,
//		x4 = x5 - 0.03,
		scale_top = y_centre + 0.6,
		scale_bottom = y_centre - 0.6,
		scale_step = 1.0 / 9.0;

	float
		v,
		mfd_vp_y_min,
		mfd_vp_y_max,
		x_adjust,
		y_adjust = y_centre,
		radar_altitude = current_flight_dynamics->radar_altitude.value,
		barometric_altitude = current_flight_dynamics->barometric_altitude.value,
		altitude;


	char
		*format,
		buffer[8];

	int
		u1, u2, v1, v2,
		displayed_altitude = (int)((barometric_altitude + 5) / 10);


	draw_2d_box(x1, scale_top, x5, scale_bottom, TRUE, FALSE, MFD_COLOUR_BLUE);
	draw_2d_box(x1, scale_top, x5, scale_bottom, FALSE, FALSE, MFD_COLOUR_LIGHT_BLUE);

	// draw scale
	get_2d_float_screen_x_coordinate (-y_centre, &v);

	mfd_vp_y_min = v - (0.5 * mfd_viewport_size * (scale_top - scale_bottom) * 0.5);
	mfd_vp_y_max = v + (0.5 * mfd_viewport_size * (scale_top - scale_bottom) * 0.5);

	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_vp_y_min, mfd_viewport_x_max, mfd_vp_y_max);

	if (radar_altitude < 250.0)
	{
		format = "R%3d";
		altitude = radar_altitude;
		displayed_altitude = altitude;
	}
	else
	{
		format = "%04d";
		altitude = barometric_altitude;
		displayed_altitude = (int)((barometric_altitude + 5) / 10) * 10;
	}

	//
	// draw scale
	//

	{
		float scale_step_5 = altitude * 0.4;
		int int_scale_step_5 = (int) scale_step_5;
		float mod_scale_step_5 = scale_step_5 - (float) int_scale_step_5;

//		int tick_type = (int_scale_step_5 % 4) == 0;
		float y = -(8.0 + mod_scale_step_5) * scale_step;
		int loop;

		int_scale_step_5 -= 8;

		set_mono_font_type (MONO_FONT_TYPE_5X9);
		y_adjust = -2.0;

		for (loop = 0; loop <= 25; loop++)
		{
			if (int_scale_step_5 >= 0)
			{
				draw_2d_line (x1, y, x2, y, MFD_COLOUR_LIGHT_BLUE);

				if ((int_scale_step_5 % 4) == 0)
				{
					float x_adjust;
					char buffer[8];

					sprintf(buffer, "%4d", (int_scale_step_5 * 5 / 2));
					x_adjust = 2.0; //get_mono_font_string_width(buffer) + 2;

					set_2d_mono_font_position (x2, y);
					set_mono_font_rel_position (x_adjust, y_adjust);
					print_mono_font_string(buffer);
				}
			}

			int_scale_step_5++;
			y += scale_step;
		}
	}

	//
	// restore 2D environment
	//

	set_2d_window (mfd_env, MFD_WINDOW_X_MIN, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX, MFD_WINDOW_Y_MAX);
	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

	// clear background area
	get_2d_int_screen_coordinates (box_start, box_top, &u1, &v1);
	get_2d_int_screen_coordinates (box_end, box_bottom, &u2, &v2);
	set_block(u1, v1, u2, v2, MFD_COLOUR_BLUE);

	// draw surrounding box
	draw_2d_line(box_start, box_top, box_end, box_top, MFD_COLOUR_LIGHT_BLUE);
	draw_2d_line(box_start, box_bottom, box_end, box_bottom, MFD_COLOUR_LIGHT_BLUE);
	draw_2d_line(box_start, box_top, box_start, box_bottom, MFD_COLOUR_LIGHT_BLUE);
	draw_2d_line(box_end, box_top, box_end, box_bottom, MFD_COLOUR_LIGHT_BLUE);

	// print digital readout

	set_mono_font_type (MONO_FONT_TYPE_6X10);
	y_adjust = -2.0;

	sprintf(buffer, format, displayed_altitude);
	x_adjust = -get_mono_font_string_width(buffer) - 1;

	set_2d_mono_font_position (box_end, y_centre);
	set_mono_font_rel_position (x_adjust, y_adjust);
	print_mono_font_string(buffer);
}

static void draw_airspeed_scale (void)
{
	const float
		y_centre = 0.0,
		box_start = -0.95,
		box_end = box_start + 0.25,
		box_top = y_centre + 0.04,
		box_bottom = y_centre - 0.04,
		x1 = box_start,
//		x2 = x1 + 0.03,
//		x3 = x1 + 0.125,
		x5 = box_end,
		x4 = x5 - 0.03,
		scale_top = y_centre + 0.6,
		scale_bottom = y_centre - 0.6,
		scale_step = 1.0 / 9.0;

	float
		v,
		mfd_vp_y_min,
		mfd_vp_y_max,
		x_adjust,
		y_adjust = y_centre,
		airspeed = kilometres_per_hour(current_flight_dynamics->velocity_z.value);


	char
		buffer[8];

	int
		u1, u2, v1, v2;


	draw_2d_box(x1, scale_top, x5, scale_bottom, TRUE, FALSE, MFD_COLOUR_BLUE);
	draw_2d_box(x1, scale_top, x5, scale_bottom, FALSE, FALSE, MFD_COLOUR_LIGHT_BLUE);

	// draw scale
	get_2d_float_screen_x_coordinate (-y_centre, &v);

	mfd_vp_y_min = v - (0.5 * mfd_viewport_size * (scale_top - scale_bottom) * 0.5);
	mfd_vp_y_max = v + (0.5 * mfd_viewport_size * (scale_top - scale_bottom) * 0.5);

	debug_log("min: %.02f, max: %.02f", mfd_vp_y_min, mfd_vp_y_max);

	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_vp_y_min, mfd_viewport_x_max, mfd_vp_y_max);

	//
	// draw scale
	//

	{
		float scale_step_5 = airspeed * 0.4;
		int int_scale_step_5 = (int) scale_step_5;
		float mod_scale_step_5 = scale_step_5 - (float) int_scale_step_5;

//		int tick_type = (int_scale_step_5 % 4) == 0;
		float y = -(8.0 + mod_scale_step_5) * scale_step;
		int loop;

		int_scale_step_5 -= 8;

		set_mono_font_type (MONO_FONT_TYPE_5X9);
		y_adjust = -2.0;

		for (loop = 0; loop <= 25; loop++)
		{
//			if (int_scale_step_5 > 0)
			{
				draw_2d_line (x4, y, x5, y, MFD_COLOUR_LIGHT_BLUE);

				if ((int_scale_step_5 % 4) == 0)
				{
					float x_adjust;
					char buffer[8];

					sprintf(buffer, "%4d", (int_scale_step_5 * 5 / 2));
					x_adjust = get_mono_font_string_width(buffer) + 2;

					set_2d_mono_font_position (x4, y);
					set_mono_font_rel_position (-x_adjust, y_adjust);
					print_mono_font_string(buffer);
				}
			}

			int_scale_step_5++;
			y += scale_step;
		}
	}

	//
	// restore 2D environment
	//

	set_2d_window (mfd_env, MFD_WINDOW_X_MIN, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX, MFD_WINDOW_Y_MAX);
	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

	// clear background area
	get_2d_int_screen_coordinates (box_start, box_top, &u1, &v1);
	get_2d_int_screen_coordinates (box_end, box_bottom, &u2, &v2);
	set_block(u1, v1, u2, v2, MFD_COLOUR_BLUE);

	// draw surrounding box
	draw_2d_line(box_start, box_top, box_end, box_top, MFD_COLOUR_LIGHT_BLUE);
	draw_2d_line(box_start, box_bottom, box_end, box_bottom, MFD_COLOUR_LIGHT_BLUE);
	draw_2d_line(box_start, box_top, box_start, box_bottom, MFD_COLOUR_LIGHT_BLUE);
	draw_2d_line(box_end, box_top, box_end, box_bottom, MFD_COLOUR_LIGHT_BLUE);

	// print digital readout

	set_mono_font_type (MONO_FONT_TYPE_6X10);
	y_adjust = -2.0;

	sprintf(buffer, "%.0f", airspeed);
	x_adjust = -get_mono_font_string_width(buffer) - 1;

	set_2d_mono_font_position (box_end, y_centre);
	set_mono_font_rel_position (x_adjust, y_adjust);
	print_mono_font_string(buffer);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//
// rate of climb scale
//
////////////////////////////////////////

static char large_rate_of_climb_scale_pointer[] =
{
	5,
	9,
	-5,
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_rate_of_climb_scale (void)
{
	float
		xpos = 0.47,
		y;

	//
	// draw scale
	//

	draw_2d_line (+xpos, +0.500, xpos + 0.050, +0.500, MFD_COLOUR_LIGHT_BLUE);
	draw_2d_line (+xpos, +0.400, xpos + 0.025, +0.400, MFD_COLOUR_LIGHT_BLUE);
	draw_2d_line (+xpos, +0.300, xpos + 0.025, +0.300, MFD_COLOUR_LIGHT_BLUE);
	draw_2d_line (+xpos, +0.200, xpos + 0.025, +0.200, MFD_COLOUR_LIGHT_BLUE);
	draw_2d_line (+xpos, +0.100, xpos + 0.025, +0.100, MFD_COLOUR_LIGHT_BLUE);
	draw_2d_line (+xpos, +0.000, xpos + 0.050, +0.000, MFD_COLOUR_LIGHT_BLUE);
	draw_2d_line (+xpos, -0.100, xpos + 0.025, -0.100, MFD_COLOUR_LIGHT_BLUE);
	draw_2d_line (+xpos, -0.200, xpos + 0.025, -0.200, MFD_COLOUR_LIGHT_BLUE);
	draw_2d_line (+xpos, -0.300, xpos + 0.025, -0.300, MFD_COLOUR_LIGHT_BLUE);
	draw_2d_line (+xpos, -0.400, xpos + 0.025, -0.400, MFD_COLOUR_LIGHT_BLUE);
	draw_2d_line (+xpos, -0.500, xpos + 0.050, -0.500, MFD_COLOUR_LIGHT_BLUE);

	//
	// get indicator position (fsd +/- 10m/s)
	//

	y = current_flight_dynamics->world_velocity_y.value;

	y = bound (y, -10.0, 10.0);

	y *= 0.05;

	draw_2d_mono_sprite(large_rate_of_climb_scale_pointer, xpos + 0.05, y, MFD_COLOUR_LIGHT_BLUE);
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
		if (draw_large_mfd)
		{
			set_mono_font_type (MONO_FONT_TYPE_5X9);
		}
		else
		{
			set_mono_font_type (MONO_FONT_TYPE_5X7);
		}

		gunship_position = get_local_entity_vec3d_ptr (get_gunship_entity (), VEC3D_TYPE_POSITION);

		get_waypoint_display_position (get_gunship_entity (), wp, &waypoint_position);

		//
		// waypoint id & range
		//

		waypoint_range = get_2d_range (gunship_position, &waypoint_position);

		if (!hokum_damage.navigation_computer)
		{
			if (waypoint_range < 1000.0)
			{
				sprintf (buffer, "%c: %d M", get_local_entity_char_value (wp, CHAR_TYPE_TAG), (int) waypoint_range);
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

				sprintf (buffer, "%c: %.1f KM", get_local_entity_char_value (wp, CHAR_TYPE_TAG), f);
			}
			else
			{
				sprintf (buffer, "%c: %d KM", get_local_entity_char_value (wp, CHAR_TYPE_TAG), (int) (waypoint_range * (1.0 / 1000.0)));
			}
		}
		else
		{
			sprintf (buffer, "-:--.-");
		}

		set_2d_mono_font_position (1.0, -0.7);

		set_mono_font_rel_position (-get_mono_font_string_width(buffer) - 4, 0.0);

		print_mono_font_string (buffer);

		//
		// time to go
		//

		if ((current_flight_dynamics->velocity_z.value > 0.1) && (!hokum_damage.navigation_computer))
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

		set_2d_mono_font_position (1.0, -0.8);

		set_mono_font_rel_position (-get_mono_font_string_width(buffer) - 4, 0.0);

		print_mono_font_string (buffer);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_flight_display_mfd (void)
{
	set_mono_font_colour (MFD_COLOUR_LIGHT_BLUE);

	draw_pitch_ladder ();

	draw_heading_scale (get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_HEADING), TRUE);

	draw_airspeed_scale();

	draw_sideslip_scale();

	draw_altitude_scale();

	draw_rate_of_climb_scale ();

	display_waypoint_information ();

	draw_aircraft_datum();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DRAW MFD ON TEXTURE
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void draw_flight_mfd (void)			// Javelin 6/19  exported MFD
{
#ifndef OGRE_EE
	set_system_texture_screen (flight_mfd_texture_screen, TEXTURE_INDEX_AVCKPT_DISPLAY_LHS_MFD);

	//
	// draw MFD on texture
	//

	set_active_screen (flight_mfd_texture_screen);

	if (lock_screen (flight_mfd_texture_screen))
	{
      		set_block (0, 0, MFD_VIEWPORT_LARGE_SIZE - 1, MFD_VIEWPORT_LARGE_SIZE - 1, clear_mfd_colour);

			draw_mfd_layout_grid ();

		    draw_flight_display_mfd ();

		unlock_screen (flight_mfd_texture_screen);
	}

	set_active_screen (video_screen);

	export_screen = get_screen_of_system_texture (TEXTURE_INDEX_AVCKPT_DISPLAY_LHS_MFD);
	copy_export_mfd(export_screen, NULL);

#endif
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void draw_havoc_mfd_on_texture (void)
{
#ifndef OGRE_EE
	screen* export_screen;
	if (havoc_damage.tv_display)
	{
		if (mfd_mode != MFD_MODE_OFF)
		{
			mfd_mode = MFD_MODE_DAMAGED;
		}
	}
	else
	{
		if (mfd_mode == MFD_MODE_DAMAGED)
		{
			mfd_mode = MFD_MODE_OFF;
		}
	}

	set_system_texture_screen (mfd_texture_screen, TEXTURE_INDEX_HVCKPT_DISPLAY_CRT);

	////////////////////////////////////////
	//
	// set up MFD 2D environment
	//
	////////////////////////////////////////

	set_2d_active_environment (mfd_env);

	//
	// window
	//

	set_2d_window (mfd_env, MFD_WINDOW_X_MIN, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX, MFD_WINDOW_Y_MAX);

	//
	// viewport
	//

	if (draw_large_mfd)
		mfd_viewport_size = MFD_VIEWPORT_LARGE_SIZE;
	else
		mfd_viewport_size = MFD_VIEWPORT_SMALL_SIZE;

	ASSERT (mfd_viewport_size <= mfd_texture_size);


	mfd_viewport_x_org = mfd_viewport_texture_x_org;
	mfd_viewport_y_org = mfd_viewport_texture_y_org;

	mfd_viewport_x_min = mfd_viewport_x_org - (mfd_viewport_size * 0.5);
	mfd_viewport_y_min = mfd_viewport_y_org - (mfd_viewport_size * 0.5);
	mfd_viewport_x_max = mfd_viewport_x_org + (mfd_viewport_size * 0.5);
	mfd_viewport_y_max = mfd_viewport_y_org + (mfd_viewport_size * 0.5);

	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

	////////////////////////////////////////
	//
	// draw MFD display
	//
	////////////////////////////////////////

	switch (mfd_mode)
	{
		////////////////////////////////////////
		case MFD_MODE_OFF:
		////////////////////////////////////////
		{
			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

				draw_mfd_layout_grid ();

				unlock_screen (mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_DAMAGED:
		////////////////////////////////////////
		{
			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

				draw_mfd_layout_grid ();

				draw_damaged_mfd ();

				unlock_screen (mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_GROUND_RADAR:
		case MFD_MODE_AIR_RADAR:
		////////////////////////////////////////
		{
			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

				draw_mfd_layout_grid ();

				if (mfd_mode == MFD_MODE_GROUND_RADAR)
				 	draw_ground_radar_mfd ();
				else
				 	draw_air_radar_mfd ();

				unlock_screen (mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_FLIR:
		case MFD_MODE_LLLTV:
		////////////////////////////////////////
		{
			if
			(
				(!havoc_damage.flir) &&
				(get_view_mode () != VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT30) &&
				(get_view_mode () != VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT30)
			)
			{
				ASSERT (eo_3d_texture_screen);

				set_system_texture_screen (eo_3d_texture_screen, TEXTURE_INDEX_HVCKPT_DISPLAY_CRT);

				if (eo_sensor == TARGET_ACQUISITION_SYSTEM_FLIR)
					mfd_mode = MFD_MODE_FLIR;
				else
					mfd_mode = MFD_MODE_LLLTV;

				if (mfd_mode == MFD_MODE_FLIR)
					draw_3d_eo_display_on_texture (&havoc_flir, TARGET_ACQUISITION_SYSTEM_FLIR);
				else
					draw_3d_eo_display_on_texture (&havoc_llltv, TARGET_ACQUISITION_SYSTEM_LLLTV);

				set_active_screen (eo_3d_texture_screen_over);

				if (lock_screen (eo_3d_texture_screen_over))
				{
					draw_mfd_layout_grid ();

					if (mfd_mode == MFD_MODE_FLIR)
						draw_2d_flir_mfd (TRUE, FALSE);
					else
						draw_2d_llltv_mfd (TRUE, FALSE);

					unlock_screen (eo_3d_texture_screen_over);

					eo_3d_texture_merge (eo_3d_texture_screen, eo_3d_texture_screen_over);
				}

				set_pilots_full_screen_params (FALSE);
			}
			else
			{
				set_active_screen (mfd_texture_screen);

				if (lock_screen (mfd_texture_screen))
				{
					set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

					draw_mfd_layout_grid ();

					if (mfd_mode == MFD_MODE_FLIR)
						draw_2d_flir_mfd (FALSE, FALSE);
					else
						draw_2d_llltv_mfd (FALSE, FALSE);

					unlock_screen (mfd_texture_screen);
				}
			}

			break;
		}

	}

	set_active_screen (video_screen);

	if(command_line_export_mfd)
	{
		export_screen = get_screen_of_system_texture (TEXTURE_INDEX_HVCKPT_DISPLAY_CRT);
		copy_export_mfd(NULL, export_screen);				//  Javelin  6/19

		draw_flight_mfd ();		//  Javelin  6/19
	}

#endif
}

#ifndef OGRE_EE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DRAW OVERLAID MFD
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_translucent_mfd_background (float x_min, float y_min, float x_max, float y_max)
{
	vertex
		quad[4];

	real_colour
		colour,
		specular;

	set_3d_active_environment (main_3d_env);

	if (begin_3d_scene ())
	{
		colour.red = 0;
		colour.green = 0;
		colour.blue = 0;
		colour.alpha = 64;

		specular.red = 0;
		specular.green = 0;
		specular.blue = 0;
		specular.alpha = 255;

		set_d3d_transparency_on ();

		set_d3d_zbuffer_comparison (FALSE);

		set_d3d_plain_renderstate ();

		set_d3d_culling (FALSE);

		quad[0].i = x_min;
		quad[0].j = y_min;
		quad[0].z = 0.5;
		quad[0].q = 0.5;
		quad[0].next_vertex = &quad[1];

		quad[1].i = x_max;
		quad[1].j = y_min;
		quad[1].z = 0.5;
		quad[1].q = 0.5;
		quad[1].next_vertex = &quad[2];

		quad[2].i = x_max;
		quad[2].j = y_max;
		quad[2].z = 0.5;
		quad[2].q = 0.5;
		quad[2].next_vertex = &quad[3];

		quad[3].i = x_min;
		quad[3].j = y_max;
		quad[3].z = 0.5;
		quad[3].q = 0.5;
		quad[3].next_vertex = NULL;

		draw_wbuffered_plain_polygon (quad, colour, specular);

		set_d3d_transparency_off ();

		set_d3d_zbuffer_comparison (TRUE);

		end_3d_scene ();
	}
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_overlaid_havoc_mfd (float x_org, float y_org, float size)
{
#ifndef OGRE_EE
	float
		mfd_screen_size,
		mfd_screen_half_size,
		mfd_screen_x_org,
		mfd_screen_y_org,
		mfd_screen_x_min,
		mfd_screen_y_min,
		mfd_screen_x_max,
		mfd_screen_y_max;

	if (havoc_damage.tv_display)
	{
		if (mfd_mode != MFD_MODE_OFF)
		{
			mfd_mode = MFD_MODE_DAMAGED;
		}
	}
	else
	{
		if (mfd_mode == MFD_MODE_DAMAGED)
		{
			mfd_mode = MFD_MODE_OFF;
		}
	}

	if (mfd_mode == MFD_MODE_OFF)
	{
		return;
	}

	////////////////////////////////////////
	//
	// scale position and size wrt screen resolution
	//
	////////////////////////////////////////

/*	if (get_global_unscaled_displays ())
	{
		float
			org_offset;

		mfd_screen_size = size;

		mfd_screen_half_size = mfd_screen_size * 0.5;

		mfd_screen_x_org = x_org * full_screen_width * (1.0 / 640.0);
		mfd_screen_y_org = y_org * full_screen_height * (1.0 / 480.0);

		org_offset = ((size * full_screen_width * (1.0 / 640.0)) - size) * 0.5;

		mfd_screen_x_org -= org_offset;
		mfd_screen_y_org += org_offset;

		mfd_screen_x_min = mfd_screen_x_org - mfd_screen_half_size;
		mfd_screen_y_min = mfd_screen_y_org - mfd_screen_half_size;
		mfd_screen_x_max = mfd_screen_x_org + mfd_screen_half_size;
		mfd_screen_y_max = mfd_screen_y_org + mfd_screen_half_size;
	}
	else */
	{
		float
			scalex,
			scaley;

		scalex = full_screen_width * (1.0 / 640.0);
		scaley = full_screen_height * (1.0 / 480.0);

		mfd_screen_size = size * global_mfd_size * scalex;
		mfd_screen_half_size = mfd_screen_size * 0.5;

		mfd_screen_x_org = x_org * scalex;
		mfd_screen_y_org = y_org * scaley;

		mfd_screen_x_org -= size * scalex * 0.5 - mfd_screen_half_size;
		mfd_screen_y_org += size * scaley * 0.5 - mfd_screen_half_size;

		mfd_screen_x_min = mfd_screen_x_org - mfd_screen_half_size;
		mfd_screen_y_min = mfd_screen_y_org - mfd_screen_half_size;
		mfd_screen_x_max = mfd_screen_x_org + mfd_screen_half_size;
		mfd_screen_y_max = mfd_screen_y_org + mfd_screen_half_size;
	}

	////////////////////////////////////////
	//
	// set up MFD 2D environment
	//
	////////////////////////////////////////

	set_2d_active_environment (mfd_env);

	//
	// window
	//

	set_2d_window (mfd_env, MFD_WINDOW_X_MIN, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX, MFD_WINDOW_Y_MAX);

	//
	// viewport
	//

	mfd_viewport_x_org = mfd_viewport_texture_x_org;

	mfd_viewport_y_org = mfd_viewport_texture_y_org;

	mfd_viewport_x_min = mfd_viewport_x_org - (mfd_viewport_size * 0.5);

	mfd_viewport_y_min = mfd_viewport_y_org - (mfd_viewport_size * 0.5);

	mfd_viewport_x_max = mfd_viewport_x_org + (mfd_viewport_size * 0.5);

	mfd_viewport_y_max = mfd_viewport_y_org + (mfd_viewport_size * 0.5);

	//
	// translate & scale values (EO 3D display does not match texture)
	//

	i_translate_3d = mfd_screen_x_min;
	j_translate_3d = mfd_screen_y_min;

	i_scale_3d = mfd_texture_size / mfd_screen_size;
	j_scale_3d = mfd_texture_size / mfd_screen_size;

	////////////////////////////////////////
	//
	// draw MFD display
	//
	////////////////////////////////////////

	switch (mfd_mode)
	{
		////////////////////////////////////////
		case MFD_MODE_OFF:
		////////////////////////////////////////
		{
			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (overlaid_mfd_texture_screen);

			if (lock_screen (overlaid_mfd_texture_screen))
			{
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

				draw_mfd_layout_grid ();

				unlock_screen (overlaid_mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_DAMAGED:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (overlaid_mfd_texture_screen);

			if (lock_screen (overlaid_mfd_texture_screen))
			{
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

				draw_mfd_layout_grid ();

				draw_damaged_mfd ();

				unlock_screen (overlaid_mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_GROUND_RADAR:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (overlaid_mfd_texture_screen);

			if (lock_screen (overlaid_mfd_texture_screen))
			{
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

				draw_mfd_layout_grid ();

			 	draw_ground_radar_mfd ();

				unlock_screen (overlaid_mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_AIR_RADAR:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (overlaid_mfd_texture_screen);

			if (lock_screen (overlaid_mfd_texture_screen))
			{
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

				draw_mfd_layout_grid ();

				draw_air_radar_mfd ();

				unlock_screen (overlaid_mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_FLIR:
		////////////////////////////////////////
		{
			if (!havoc_damage.flir)
			{
				draw_overlaid_3d_eo_display (&havoc_flir, TARGET_ACQUISITION_SYSTEM_FLIR, mfd_screen_x_min, mfd_screen_y_min, mfd_screen_size);
			}
			else
			{
				draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);
			}

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (overlaid_mfd_texture_screen);

			if (lock_screen (overlaid_mfd_texture_screen))
			{
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

				draw_mfd_layout_grid ();

				draw_2d_flir_mfd (TRUE, TRUE);

				unlock_screen (overlaid_mfd_texture_screen);
			}

			set_pilots_full_screen_params (FALSE);

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_LLLTV:
		////////////////////////////////////////
		{
			if (!havoc_damage.llltv)
			{
				draw_overlaid_3d_eo_display (&havoc_llltv, TARGET_ACQUISITION_SYSTEM_LLLTV, mfd_screen_x_min, mfd_screen_y_min, mfd_screen_size);
			}
			else
			{
				draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);
			}

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (overlaid_mfd_texture_screen);

			if (lock_screen (overlaid_mfd_texture_screen))
			{
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

				draw_mfd_layout_grid ();

				draw_2d_llltv_mfd (TRUE, TRUE);

				unlock_screen (overlaid_mfd_texture_screen);
			}

			set_pilots_full_screen_params (FALSE);

			break;
		}
	}

	set_active_screen (video_screen);

	////////////////////////////////////////
	//
	// render MFD to screen
	//
	////////////////////////////////////////
	{
		vertex
			quad[4];

		real_colour
			colour,
			specular;

		set_3d_active_environment (main_3d_env);

		if (begin_3d_scene ())
		{
			set_d3d_transparency_on ();

			set_d3d_zbuffer_comparison (FALSE);

			set_d3d_culling (FALSE);

			set_d3d_texture_wrapping (0, FALSE);

/*
			if ((application_video_width == 640) || (get_global_unscaled_displays ()))
			{
				set_d3d_texture_mag_filtering (FALSE);
				set_d3d_texture_min_filtering (FALSE);
				set_d3d_texture_mip_filtering (FALSE);
			}
			else */
			{
				set_d3d_texture_mag_filtering (TRUE);
				set_d3d_texture_min_filtering (TRUE);
				set_d3d_texture_mip_filtering (FALSE);
			}

			set_d3d_flat_shaded_textured_renderstate (get_system_texture_ptr (OVERLAID_MFD_TEXTURE_INDEX));

			////////////////////////////////////////
			//

			colour.red	 			= 255;
			colour.green			= 255;
			colour.blue	 			= 255;
			colour.alpha  			= 255;

			specular.red 			= 0;
			specular.green	 		= 0;
			specular.blue 			= 0;
			specular.alpha	  		= 255;

			quad[0].i 				= mfd_screen_x_min;
			quad[0].j  				= mfd_screen_y_min;
			quad[0].z  				= 0.5;
			quad[0].q  				= 0.5;
			quad[0].u  				= 0.0;
			quad[0].v				= 0.0;

			quad[1].i  				= mfd_screen_x_max;
			quad[1].j  				= mfd_screen_y_min;
			quad[1].z  				= 0.5;
			quad[1].q  				= 0.5;
			quad[1].u  				= 1.0;
			quad[1].v  				= 0.0;

			quad[2].i				= mfd_screen_x_max;
			quad[2].j  				= mfd_screen_y_max;
			quad[2].z  				= 0.5;
			quad[2].q  				= 0.5;
			quad[2].u  				= 1.0;
			quad[2].v  				= 1.0;

			quad[3].i  				= mfd_screen_x_min;
			quad[3].j  				= mfd_screen_y_max;
			quad[3].z  				= 0.5;
			quad[3].q  				= 0.5;
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
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_havoc_eo_display_visible (void)
{
	return
	(
		(mfd_mode == MFD_MODE_FLIR) ||
		(mfd_mode == MFD_MODE_LLLTV)
	);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_engine_display(void)		//  Javelin 7/19
{
	float
		fvalue;

	fvalue = bound (current_flight_dynamics->left_engine_torque.value, 0.0, 120.0);  //  TQ  L
	draw_2d_box (-0.96, -0.81, -0.92, -0.81 +fvalue*1.6/120.0, TRUE, FALSE, MFD_COLOUR_YELLOW);

	fvalue = bound (current_flight_dynamics->right_engine_torque.value, 0.0, 120.0);  //  TQ  R
	draw_2d_box (-0.65, -0.81, -0.61, -0.81 +fvalue*1.6/120.0, TRUE, FALSE, MFD_COLOUR_YELLOW);

	fvalue = bound (current_flight_dynamics->left_engine_temp.value, 0.0, 1000.0);  //  TG  L
	if (fvalue<600)
		draw_2d_box (-0.05, -0.89, -0.01, -0.89 +fvalue*0.92/1000.0, TRUE, FALSE, MFD_COLOUR_ORANGE);
	else
		draw_2d_box (-0.05, -0.89, -0.01, -0.89+0.552 +(fvalue-600)*2.75/1000.0, TRUE, FALSE, MFD_COLOUR_ORANGE);

	fvalue = bound (current_flight_dynamics->right_engine_temp.value, 0.0, 1000.0);  //  TG  R
	if (fvalue<600)
		draw_2d_box ( 0.49, -0.89,  0.52, -0.89 +fvalue*0.92/1000.0, TRUE, FALSE, MFD_COLOUR_ORANGE);
	else
		draw_2d_box ( 0.49, -0.89,  0.52, -0.89+0.552 +(fvalue-600)*2.75/1000.0, TRUE, FALSE, MFD_COLOUR_ORANGE);

	fvalue = bound (current_flight_dynamics->left_engine_n1_rpm.value, 0.0, 120.0);  //  NG  L
	if (fvalue<60)
		draw_2d_box ( 0.04, -0.89,  0.07, -0.89 +fvalue*1.25/110.0, TRUE, FALSE, MFD_COLOUR_YELLOW);
	else
		draw_2d_box ( 0.04, -0.89,  0.07, -0.89+0.375 +(fvalue-60)*3.0/110.0, TRUE, FALSE, MFD_COLOUR_YELLOW);

	fvalue = bound (current_flight_dynamics->right_engine_n1_rpm.value, 0.0, 120.0);  //  NG  L
	if (fvalue<60)
		draw_2d_box ( 0.38, -0.89,  0.41, -0.89 +fvalue*1.25/110.0, TRUE, FALSE, MFD_COLOUR_YELLOW);
	else
		draw_2d_box ( 0.38, -0.89,  0.41, -0.89+0.375 +(fvalue-60)*3.0/110.0, TRUE, FALSE, MFD_COLOUR_YELLOW);

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_engine_mfd_on_texture (void)		//  Javelin  7/19
{
	set_system_texture_screen (mfd_engine_screen, TEXTURE_INDEX_COMANCHE_MFD1);

		set_active_screen (mfd_engine_screen);

		if (lock_screen (mfd_engine_screen))
		{
			set_block (0, 0, mfd_viewport_size - 1, mfd_viewport_size - 1, clear_hud_colour);	//////  Blank out the MFD background, transparent

				draw_engine_display ();

			unlock_screen (mfd_engine_screen);
		}

		set_active_screen (video_screen);

	//export_screen = get_screen_of_system_texture (TEXTURE_INDEX_COMANCHE_MFD1);  //  for testing only.
	//copy_export_mfd(export_screen, NULL);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

