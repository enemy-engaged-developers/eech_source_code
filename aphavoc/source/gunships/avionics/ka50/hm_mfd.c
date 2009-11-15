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
	mfd_colours[6];

#define MFD_COLOUR1 (mfd_colours[0])
#define MFD_COLOUR2 (mfd_colours[1])
#define MFD_COLOUR3 (mfd_colours[2])
#define MFD_COLOUR4 (mfd_colours[3])
#define MFD_COLOUR5 (mfd_colours[4])
#define MFD_COLOUR6 (mfd_colours[5])

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

#define MFD_VIEWPORT_SMALL_SIZE		(114)
//#define MFD_VIEWPORT_LARGE_SIZE		(332)
#define MFD_VIEWPORT_LARGE_SIZE		(210)

#define MFD_TEXTURE_SMALL_SIZE			(128)
#define MFD_TEXTURE_LARGE_SIZE			(256)

static env_2d
	*mfd_env;

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

static float
	i_translate_3d,
	j_translate_3d,
	i_scale_3d,
	j_scale_3d;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define OVERLAID_MFD_TEXTURE_INDEX (TEXTURE_INDEX_COMANCHE_MFD1)

static screen
	*mfd_texture_screen,
	*eo_3d_texture_screen,
	*overlaid_mfd_texture_screen;

static rgb_colour
	clear_mfd_colour;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_ka50_mfd (void)
{
	mfd_mode = MFD_MODE_OFF;

	mfd_env = create_2d_environment ();


	if (command_line_high_res_mfd)
	{
		draw_large_mfd = TRUE;
		
		mfd_viewport_size = MFD_VIEWPORT_LARGE_SIZE;
		mfd_texture_size = MFD_TEXTURE_LARGE_SIZE;
		eo_3d_texture_screen = large_eo_3d_texture_screen;
	}
	else
	{
		draw_large_mfd = FALSE;

		mfd_viewport_size = MFD_VIEWPORT_SMALL_SIZE;
		mfd_texture_size = MFD_TEXTURE_SMALL_SIZE;
		eo_3d_texture_screen = small_eo_3d_texture_screen;
	}
	
	mfd_viewport_texture_x_org = mfd_texture_size / 2;
	mfd_viewport_texture_y_org = mfd_texture_size / 2;

	mfd_viewport_x_min = mfd_viewport_x_org - (mfd_viewport_size * 0.5);
	mfd_viewport_y_min = mfd_viewport_y_org - (mfd_viewport_size * 0.5);
	mfd_viewport_x_max = mfd_viewport_x_org + (mfd_viewport_size * 0.5) - 0.001;
	mfd_viewport_y_max = mfd_viewport_y_org + (mfd_viewport_size * 0.5) - 0.001;

	mfd_texture_screen = create_system_texture_screen (mfd_texture_size, mfd_texture_size, TEXTURE_INDEX_HVCKPT_DISPLAY_CRT, TEXTURE_TYPE_SINGLEALPHA);
	overlaid_mfd_texture_screen = create_system_texture_screen (mfd_texture_size, mfd_texture_size, OVERLAID_MFD_TEXTURE_INDEX, TEXTURE_TYPE_SINGLEALPHA);

	set_rgb_colour (MFD_COLOUR1, 255, 160,   0, 255);
	set_rgb_colour (MFD_COLOUR2, 200, 130,   0, 255);
	set_rgb_colour (MFD_COLOUR3, 176, 126,   0, 255);
	set_rgb_colour (MFD_COLOUR4, 151, 100,   0, 255);
	set_rgb_colour (MFD_COLOUR5, 140,  90,   0, 255);
	set_rgb_colour (MFD_COLOUR6,  80,  62,   8, 255);

	if(command_line_export_mfd)
	{
		set_rgb_colour (clear_mfd_colour, 80,  62,   8, 0);
	}
	else
	{
		set_rgb_colour (clear_mfd_colour, 255, 255, 0, 0);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_ka50_mfd (void)
{
	destroy_2d_environment (mfd_env);

	destroy_screen (mfd_texture_screen);

	destroy_screen (overlaid_mfd_texture_screen);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_ka50_mfd_mode (mfd_modes mode)
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// LAYOUT GRID
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_layout_grid (void)
{
	float
		x,
		y;

	if (display_mfd_layout_grid)
	{
		for (x = -1.0; x <= 1.0; x += 0.1)
		{
			draw_2d_line (x, -1.0, x, 1.0, sys_col_red);
		}

		for (y = -1.0; y <= 1.0; y += 0.1)
		{
			draw_2d_line (-1.0, y, 1.0, y, sys_col_red);
		}
	}
}

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

	if (scan_range == HIND_RADAR_SCAN_RANGE_1000)
	{
//		s = "1Km";
		sprintf(s,"%.0fKm",HIND_RADAR_SCAN_RANGE_1000/1000);	
	}
	else if (scan_range == HIND_RADAR_SCAN_RANGE_2000)
	{
//		s = "2Km";
		sprintf(s,"%.0fKm",HIND_RADAR_SCAN_RANGE_2000/1000);	
	}
	else if (scan_range == HIND_RADAR_SCAN_RANGE_4000)
	{
//		s = "4Km";
		sprintf(s,"%.0fKm",HIND_RADAR_SCAN_RANGE_4000/1000);	
	}
	else if (scan_range == HIND_RADAR_SCAN_RANGE_6000)
	{
//		s = "6Km";
		sprintf(s,"%.0fKm",HIND_RADAR_SCAN_RANGE_6000/1000);	
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

		if ((target_range < 1000.0) && (!ka50_damage.laser_range_finder))
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

	mfd_vp_x_max = mfd_viewport_x_org + (mfd_viewport_size * (0.5 * 0.5)) - 0.001;

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

	set_2d_window_rotation (mfd_env, -(ground_radar.scan_datum + ground_radar.sweep_offset));

	draw_2d_line (0.0, 0.0, 0.0, RADIUS, MFD_COLOUR1);

	set_2d_window_rotation (mfd_env, 0.0);

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

	set_2d_window_rotation (mfd_env, -(air_radar.scan_datum + air_radar.sweep_offset));

	draw_2d_line (0.0, 0.0, 0.0, RADIUS, MFD_COLOUR1);

	set_2d_window_rotation (mfd_env, 0.0);

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
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_HEAVY_RAIN
		{
			DISPLAY_3D_NOISE_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_SNOW
		{
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_NIGHT
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
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_DRY
		{
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_LIGHT_RAIN
		{
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_HEAVY_RAIN
		{
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_SNOW
		{
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_NIGHT
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

	display_3d_tints
		tint;
		
	ASSERT (eo);

	switch (eo->field_of_view)
	{
		case EO_FOV_NARROW:
		{
			zoom = 1.0 / 128.0;

			break;
		}
		case EO_FOV_MEDIUM:
		{
			zoom = 1.0 / 8.0;

			break;
		}
		case EO_FOV_WIDE:
		{
			zoom = 1.0;

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

			tint = DISPLAY_3D_TINT_AMBER;
			
			break;
		}
		case TARGET_ACQUISITION_SYSTEM_LLLTV:
		{
			light_level = llltv_light_levels[weather_mode][day_segment_type];

			noise_level = llltv_noise_levels[weather_mode][day_segment_type];

			tint = DISPLAY_3D_TINT_AMBER_VISUAL;
			
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
//		set_main_3d_params (DISPLAY_3D_TINT_AMBER, light_level, noise_level, mfd_viewport_x_min - 78.0, mfd_viewport_y_min - 17.0, 488.0, 366.0, rad (59.99) * zoom, rad (46.82) * zoom);
		set_main_3d_params (tint, light_level, noise_level, mfd_viewport_x_min - 78.0, mfd_viewport_y_min - 17.0, 488.0, 366.0, rad (59.99) * zoom, rad (46.82) * zoom);
	}
	else
	{
//		set_main_3d_params (DISPLAY_3D_TINT_AMBER, light_level, noise_level, mfd_viewport_x_min - 31.0, mfd_viewport_y_min - 10.0, 176.0, 132.0, rad (59.99) * zoom, rad (46.82) * zoom);
		set_main_3d_params (tint, light_level, noise_level, mfd_viewport_x_min - 31.0, mfd_viewport_y_min - 10.0, 176.0, 132.0, rad (59.99) * zoom, rad (46.82) * zoom);
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

	ASSERT (d3d_can_render_to_texture);

	switch (eo->field_of_view)
	{
		case EO_FOV_NARROW:
		{
			zoom = 1.0 / 128.0;

			break;
		}
		case EO_FOV_MEDIUM:
		{
			zoom = 1.0 / 8.0;

			break;
		}
		case EO_FOV_WIDE:
		{
			zoom = 1.0;

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

			tint = DISPLAY_3D_TINT_AMBER;

			break;
		}
		case TARGET_ACQUISITION_SYSTEM_LLLTV:
		{
			light_level = llltv_light_levels[weather_mode][day_segment_type];

			noise_level = llltv_noise_levels[weather_mode][day_segment_type];

			tint = DISPLAY_3D_TINT_AMBER_VISUAL;

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

//	set_main_3d_params (DISPLAY_3D_TINT_AMBER, light_level, noise_level, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_size, mfd_viewport_size, rad (59.99) * zoom, rad (59.99) * zoom);
	set_main_3d_params (tint, light_level, noise_level, 0.0, 0.0, mfd_texture_size - 0.001, mfd_texture_size - 0.001, rad (59.99) * zoom, rad (59.99) * zoom);

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

	display_3d_tints
		tint;
		
	ASSERT (eo);

	switch (eo->field_of_view)
	{
		case EO_FOV_NARROW:
		{
			zoom = 1.0 / 128.0;

			break;
		}
		case EO_FOV_MEDIUM:
		{
			zoom = 1.0 / 8.0;

			break;
		}
		case EO_FOV_WIDE:
		{
			zoom = 1.0;

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

			tint = DISPLAY_3D_TINT_AMBER;
			
			break;
		}
		case TARGET_ACQUISITION_SYSTEM_LLLTV:
		{
			light_level = llltv_light_levels[weather_mode][day_segment_type];

			noise_level = llltv_noise_levels[weather_mode][day_segment_type];

			tint = DISPLAY_3D_TINT_AMBER_VISUAL;

			break;
		}
		default:
		{
			debug_fatal ("Invalid target acquisition system = %d", system);

			break;
		}
	}

//	set_main_3d_params (DISPLAY_3D_TINT_AMBER, light_level, noise_level, x, y, size, size, rad (59.99) * zoom, rad (59.99) * zoom);
	set_main_3d_params (tint, light_level, noise_level, x, y, size, size, rad (59.99) * zoom, rad (59.99) * zoom);

	draw_eo_3d_scene = TRUE;

	draw_main_3d_scene (&eo_vp);

	draw_eo_3d_scene = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static char large_azimuth_marker[] =
{
	5,
	12,
	-2,
	0,
	0,0,1,0,0,
	0,0,1,0,0,
	0,0,1,0,0,
	0,0,1,0,0,
	0,1,0,1,0,
	1,0,0,0,1,
	1,0,0,0,1,
	1,0,0,0,1,
	1,0,0,0,1,
	1,0,0,0,1,
	1,0,0,0,1,
	1,1,1,1,1,
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
		has_range;		// from havoc

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
		if ((target_range < 1000.0) && (!ka50_damage.laser_range_finder))
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
	draw_3d_eo_display (&ka50_flir, TARGET_ACQUISITION_SYSTEM_FLIR);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_2d_flir_mfd (int valid_3d, int scaled_3d)
{
	draw_2d_eo_display (&ka50_flir, TARGET_ACQUISITION_SYSTEM_FLIR, valid_3d, scaled_3d);
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
	draw_3d_eo_display (&ka50_llltv, TARGET_ACQUISITION_SYSTEM_LLLTV);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_2d_llltv_mfd (int valid_3d, int scaled_3d)
{
	draw_2d_eo_display (&ka50_llltv, TARGET_ACQUISITION_SYSTEM_LLLTV, valid_3d, scaled_3d);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DRAW MFD ON COCKPIT
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_ka50_mfd_on_cockpit (float x_org, float y_org, int large_mfd, int draw_translucent_background)
{
	if (ka50_damage.tv_display)
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

	mfd_viewport_x_max = mfd_viewport_x_org + (mfd_viewport_size * 0.5) - 0.001;

	mfd_viewport_y_max = mfd_viewport_y_org + (mfd_viewport_size * 0.5) - 0.001;

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
				draw_layout_grid ();

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
				draw_layout_grid ();

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
				draw_layout_grid ();

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
				draw_layout_grid ();

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
				draw_layout_grid ();

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
				draw_layout_grid ();

				draw_2d_llltv_mfd (TRUE, FALSE);

				unlock_screen (active_screen);
			}

			break;
		}
	}
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

void draw_ka50_mfd_on_texture (void)
{
	screen* export_screen;
	if (ka50_damage.tv_display)
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
	mfd_viewport_x_max = mfd_viewport_x_org + (mfd_viewport_size * 0.5) - 0.001;
	mfd_viewport_y_max = mfd_viewport_y_org + (mfd_viewport_size * 0.5) - 0.001;

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

				draw_layout_grid ();

				flush_screen_texture_graphics (mfd_texture_screen);

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

				draw_layout_grid ();

				draw_damaged_mfd ();

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_GROUND_RADAR:
		////////////////////////////////////////
		{
			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

				draw_layout_grid ();

			 	draw_ground_radar_mfd ();

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_AIR_RADAR:
		////////////////////////////////////////
		{
			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_air_radar_mfd ();

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_FLIR:
		////////////////////////////////////////
		{
			if
			(
				(d3d_can_render_to_texture) &&
				(!ka50_damage.flir) &&
				(get_view_mode () != VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT30) &&
				(get_view_mode () != VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT30)
			)
			{
				ASSERT (eo_3d_texture_screen);

				set_system_texture_screen (eo_3d_texture_screen, TEXTURE_INDEX_HVCKPT_DISPLAY_CRT);

				draw_3d_eo_display_on_texture (&ka50_flir, TARGET_ACQUISITION_SYSTEM_FLIR);

				set_active_screen (eo_3d_texture_screen);

				if (lock_screen (eo_3d_texture_screen))
				{
					draw_layout_grid ();

					draw_2d_flir_mfd (TRUE, FALSE);

					flush_screen_texture_graphics (eo_3d_texture_screen);

					unlock_screen (eo_3d_texture_screen);
				}

				set_pilots_full_screen_params (FALSE);
			}
			else
			{
				set_active_screen (mfd_texture_screen);

				if (lock_screen (mfd_texture_screen))
				{
					set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

					draw_layout_grid ();

					draw_2d_flir_mfd (FALSE, FALSE);

					flush_screen_texture_graphics (mfd_texture_screen);

					unlock_screen (mfd_texture_screen);
				}
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_LLLTV:
		////////////////////////////////////////
		{
			if
			(
				(d3d_can_render_to_texture) &&
				(!ka50_damage.llltv) &&
				(get_view_mode () != VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT30) &&
				(get_view_mode () != VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT30)
			)
			{
				ASSERT (eo_3d_texture_screen);

				set_system_texture_screen (eo_3d_texture_screen, TEXTURE_INDEX_HVCKPT_DISPLAY_CRT);

				draw_3d_eo_display_on_texture (&ka50_llltv, TARGET_ACQUISITION_SYSTEM_LLLTV);

				set_active_screen (eo_3d_texture_screen);

				if (lock_screen (eo_3d_texture_screen))
				{
					draw_layout_grid ();

					draw_2d_llltv_mfd (TRUE, FALSE);

					flush_screen_texture_graphics (eo_3d_texture_screen);

					unlock_screen (eo_3d_texture_screen);
				}

				set_pilots_full_screen_params (FALSE);
			}
			else
			{
				set_active_screen (mfd_texture_screen);

				if (lock_screen (mfd_texture_screen))
				{
					set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

					draw_layout_grid ();

					draw_2d_llltv_mfd (FALSE, FALSE);

					flush_screen_texture_graphics (mfd_texture_screen);

					unlock_screen (mfd_texture_screen);
				}
			}

			break;
		}

	}

	set_active_screen (video_screen);
	if(command_line_export_mfd)
	{
		export_screen=create_screen_for_system_texture (TEXTURE_INDEX_HVCKPT_DISPLAY_CRT);
		copy_export_mfd(export_screen,NULL);
	}
}

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_overlaid_ka50_mfd (float x_org, float y_org, float size)
{
	float
		mfd_screen_size,
		mfd_screen_half_size,
		mfd_screen_x_org,
		mfd_screen_y_org,
		mfd_screen_x_min,
		mfd_screen_y_min,
		mfd_screen_x_max,
		mfd_screen_y_max;

	if (ka50_damage.tv_display)
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
		mfd_screen_x_max = mfd_screen_x_org + mfd_screen_half_size - 0.001;
		mfd_screen_y_max = mfd_screen_y_org + mfd_screen_half_size - 0.001;
	}
	else*/
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
		mfd_screen_x_max = mfd_screen_x_org + mfd_screen_half_size - 0.001;
		mfd_screen_y_max = mfd_screen_y_org + mfd_screen_half_size - 0.001;
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

//	ASSERT (mfd_viewport_size <= mfd_texture_size);

	mfd_viewport_x_org = mfd_viewport_texture_x_org;

	mfd_viewport_y_org = mfd_viewport_texture_y_org;

	mfd_viewport_x_min = mfd_viewport_x_org - (mfd_viewport_size * 0.5);

	mfd_viewport_y_min = mfd_viewport_y_org - (mfd_viewport_size * 0.5);

	mfd_viewport_x_max = mfd_viewport_x_org + (mfd_viewport_size * 0.5) - 0.001;

	mfd_viewport_y_max = mfd_viewport_y_org + (mfd_viewport_size * 0.5) - 0.001;
	
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

				draw_layout_grid ();

				flush_screen_texture_graphics (overlaid_mfd_texture_screen);

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

				draw_layout_grid ();

				draw_damaged_mfd ();

				flush_screen_texture_graphics (overlaid_mfd_texture_screen);

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

				draw_layout_grid ();

			 	draw_ground_radar_mfd ();

				flush_screen_texture_graphics (overlaid_mfd_texture_screen);

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

				draw_layout_grid ();

				draw_air_radar_mfd ();

				flush_screen_texture_graphics (overlaid_mfd_texture_screen);

				unlock_screen (overlaid_mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_FLIR:
		////////////////////////////////////////
		{
			if (!ka50_damage.flir)
			{
				draw_overlaid_3d_eo_display (&ka50_flir, TARGET_ACQUISITION_SYSTEM_FLIR, mfd_screen_x_min, mfd_screen_y_min, mfd_screen_size);
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

				draw_layout_grid ();

				draw_2d_flir_mfd (TRUE, TRUE);

				flush_screen_texture_graphics (overlaid_mfd_texture_screen);

				unlock_screen (overlaid_mfd_texture_screen);
			}

			set_pilots_full_screen_params (FALSE);

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_LLLTV:
		////////////////////////////////////////
		{
			if (!ka50_damage.llltv)
			{
				draw_overlaid_3d_eo_display (&ka50_llltv, TARGET_ACQUISITION_SYSTEM_LLLTV, mfd_screen_x_min, mfd_screen_y_min, mfd_screen_size);
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

				draw_layout_grid ();

				draw_2d_llltv_mfd (TRUE, TRUE);

				flush_screen_texture_graphics (overlaid_mfd_texture_screen);

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
			else*/
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
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_ka50_eo_display_visible (void)
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
