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

////////////////////////////////////////
//
// main 2D environment
//
////////////////////////////////////////

#define MFD_WINDOW_X_MIN				(-1.0)
#define MFD_WINDOW_Y_MIN				(-1.0)
#define MFD_WINDOW_X_MAX				(0.999)
#define MFD_WINDOW_Y_MAX				(0.999)

#define MFD_TEXTURE_SIZE			(1024)
#define MFD_VIEWPORT_SIZE           (1024)

// for the old cockpit:
#define MFD_HAVOC_TEXTURE_SIZE			(256)
#define MFD_HAVOC_VIEWPORT_SIZE           (256)

#define MAP_DISPLAY_WIDTH  0.5
#define MAP_DISPLAY_HEIGHT 0.35

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

static float
	map_range,
	map_scale;

static int
	mfd_texture_size,
	mfd_viewport_texture_x_org,
	mfd_viewport_texture_y_org,
	map_up_to_date = FALSE,
	draw_large_mfd = TRUE;

rgb_colour
	clear_mfd_colour;

static object_3d*
	map_display_model;

static object_3d_short_textured_point
	*upper_left_texture_uv = NULL,
	*upper_right_texture_uv = NULL,
	*lower_left_texture_uv = NULL,
	*lower_right_texture_uv = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define OVERLAID_MFD_TEXTURE_INDEX (TEXTURE_INDEX_COMANCHE_MFD1)

static screen
	*mfd_texture_screen;

static vec3d
	map_centre_position;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static rgb_colour
	mfd_colours[20];

#define MFD_COLOUR1 		  		(mfd_colours[0])
#define MFD_COLOUR2 		  		(mfd_colours[1])
#define MFD_COLOUR3 		  		(mfd_colours[2])
#define MFD_COLOUR4	  	  		(mfd_colours[3])
#define MFD_COLOUR5				(mfd_colours[4])
#define MFD_COLOUR6				(mfd_colours[5])
#define MFD_CONTOUR_COLOUR		(mfd_colours[6])
#define MFD_RIVER_COLOUR		(mfd_colours[7])
#define MFD_ROAD_COLOUR			(mfd_colours[8])
#define MFD_BACKGROUND_COLOUR	(mfd_colours[9])
#define MFD_COLOUR7				(mfd_colours[10])
#define MFD_COLOUR8				(mfd_colours[11])
#define MFD_COLOUR_BLUE			(mfd_colours[12])
#define MFD_COLOUR_YELLOW		(mfd_colours[13])
#define MFD_COLOUR_DARK_YELLOW	(mfd_colours[14])
#define MFD_COLOUR_RED			(mfd_colours[15])
#define MFD_COLOUR_CYAN			(mfd_colours[16])
#define MFD_COLOUR_DARK_BLUE	(mfd_colours[17])
#define MFD_COLOUR_DARK_RED		(mfd_colours[18])
#define MFD_CLEAR_COLOUR		(mfd_colours[19])

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void initialize_colours(void)
{
	//VJ 030423 TSd render mod
	set_rgb_colour (MFD_COLOUR1,              40, 40,  40, 255);
	set_rgb_colour (MFD_COLOUR2,              0, 200,   0, 255);
	set_rgb_colour (MFD_COLOUR3,              0, 176,   0, 255);
	set_rgb_colour (MFD_COLOUR4,              0, 151,   0, 255);
	set_rgb_colour (MFD_COLOUR5,              0, 128,   0, 255);
	set_rgb_colour (MFD_COLOUR6,             40,  68,  56, 255);
	set_rgb_colour (MFD_CONTOUR_COLOUR,     110,  80,  60, 255);
	set_rgb_colour (MFD_RIVER_COLOUR,       150, 160, 225, 255);
	set_rgb_colour (MFD_ROAD_COLOUR,         50,  35,  25, 255);
	set_rgb_colour (MFD_BACKGROUND_COLOUR,  220, 220, 200, 255);
	set_rgb_colour (MFD_CLEAR_COLOUR,         0,   0,   0,   0);

	set_rgb_colour (MFD_COLOUR_BLUE,          60, 160, 255,  255);
	set_rgb_colour (MFD_COLOUR_DARK_BLUE,	   0,   0,  96,  255);
	set_rgb_colour (MFD_COLOUR_YELLOW,       230, 230,  40,  255);
	set_rgb_colour (MFD_COLOUR_DARK_YELLOW,  165, 165,  30,  255);
	set_rgb_colour (MFD_COLOUR_RED,          230,  50,  20,  255);	
	set_rgb_colour (MFD_COLOUR_DARK_RED,	 148,  32,   0,  255);
	set_rgb_colour (MFD_COLOUR_CYAN,          60, 255, 230,  255);	

	set_rgb_colour (clear_mfd_colour, 220, 220, 200, 255);

	Initialise_TSD_render_terrain();
	set_tsd_map_contour_colour(MFD_CONTOUR_COLOUR);
	set_tsd_map_river_colour(MFD_RIVER_COLOUR);
	set_tsd_map_road_colour(MFD_ROAD_COLOUR);
}

void initialise_hind_mfd (void)
{
	mfd_env = create_2d_environment ();

	map_up_to_date = FALSE;

	if (custom_3d_models.arneh_mi24v_cockpit)
	{
		mfd_viewport_size = MFD_VIEWPORT_SIZE;
		mfd_texture_size = MFD_TEXTURE_SIZE;
		map_range = 50000.0,
		map_scale = 1.0 / (50000.0 * ROOT2);
	}
	else
	{
		mfd_viewport_size = MFD_HAVOC_VIEWPORT_SIZE;
		mfd_texture_size = MFD_HAVOC_TEXTURE_SIZE;
		map_range = 25000.0,
		map_scale = 1.0 / (25000.0 * ROOT2);
	}
	
	mfd_viewport_texture_x_org = mfd_texture_size / 2;
	mfd_viewport_texture_y_org = mfd_texture_size / 2;

	mfd_viewport_x_min = mfd_viewport_x_org - (mfd_viewport_size * 0.5);
	mfd_viewport_y_min = mfd_viewport_y_org - (mfd_viewport_size * 0.5);
	mfd_viewport_x_max = mfd_viewport_x_org + (mfd_viewport_size * 0.5) - 0.001;
	mfd_viewport_y_max = mfd_viewport_y_org + (mfd_viewport_size * 0.5) - 0.001;

	if (custom_3d_models.arneh_mi24v_cockpit)
		mfd_texture_screen = create_system_texture_screen (mfd_texture_size, mfd_texture_size, TEXTURE_INDEX_HIND_MAP_DISPLAY, TEXTURE_TYPE_SINGLEALPHA);
	else
		mfd_texture_screen = create_system_texture_screen (mfd_texture_size, mfd_texture_size, TEXTURE_INDEX_HVCKPT_DISPLAY_CRT, TEXTURE_TYPE_SINGLEALPHA);

	initialize_colours();

	if (objects_3d_scene_database[OBJECT_3D_MI24V_MAP_DISPLAY].index)
	{
		map_display_model = &objects_3d_data[objects_3d_scene_database[OBJECT_3D_MI24V_MAP_DISPLAY].index];

		if (map_display_model->surfaces[0].texture_index)
		{
			unsigned i;
			
			if (map_display_model->surfaces[0].number_of_faces != 1)
				debug_fatal("map with more than one face!");

			if (map_display_model->faces[0].number_of_points != 4)
				debug_fatal("map polygon with more than four points!");

			for (i=0; i < map_display_model->faces[0].number_of_points; i++)
			{
				object_3d_short_textured_point* uv = &map_display_model->surface_texture_points[i];
				
				if (uv->u < 0.5)  // left
					if (uv->v < 0.5)
						upper_left_texture_uv = uv;
					else
						lower_left_texture_uv = uv;
				else // right
					if (uv->v < 0.5)
						upper_right_texture_uv = uv;
					else
						lower_right_texture_uv = uv;
			}
			if (!upper_left_texture_uv || !lower_left_texture_uv || !upper_right_texture_uv || !lower_right_texture_uv)
				debug_fatal("could not find all corners of map display");
		}
		else
			debug_fatal("Untextured HUD display");
	}
	else
		map_display_model = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_hind_mfd (void)
{
	destroy_2d_environment (mfd_env);

	destroy_screen (mfd_texture_screen);

//	destroy_screen (overlaid_mfd_texture_screen);
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

static int scroll_map_to_uv(float u, float v)
{
	upper_left_texture_uv->u = u - 0.5 * MAP_DISPLAY_WIDTH;
	upper_left_texture_uv->v = v - 0.5 * MAP_DISPLAY_HEIGHT;
	upper_right_texture_uv->u = u + 0.5 * MAP_DISPLAY_WIDTH;
	upper_right_texture_uv->v = v - 0.5 * MAP_DISPLAY_HEIGHT;

	lower_left_texture_uv->u = u - 0.5 * MAP_DISPLAY_WIDTH;
	lower_left_texture_uv->v = v + 0.5 * MAP_DISPLAY_HEIGHT;
	lower_right_texture_uv->u = u + 0.5 * MAP_DISPLAY_WIDTH;
	lower_right_texture_uv->v = v + 0.5 * MAP_DISPLAY_HEIGHT;

	if (upper_left_texture_uv->u < 0.0 || upper_left_texture_uv->v < 0.0)
		return FALSE;
	
	if (lower_right_texture_uv->u > 1.0 || lower_right_texture_uv->v > 1.0)
		return FALSE;
	
	return TRUE;
}

static void recentre_map_texture(vec3d* position)
{
	map_centre_position = *position;

	scroll_map_to_uv(0.5, 0.5);
}

static int scroll_map(vec3d* position)
{
	float
		u = 0.5 + ((position->x - map_centre_position.x) * map_scale),
		v = 0.5 - ((position->z - map_centre_position.z) * map_scale);
	
	return scroll_map_to_uv(u, v);
}

#define RADIUS	(ROOT2 - 0.05)

static void draw_map_display(void)
{
	entity_sides
		source_side;

	float
		u,
		v,
		scale,
		x_origin,
		y_origin,
		source_heading;

	entity
		*source,
		*source_target;

	vec3d
		*source_position;

	source = get_gunship_entity ();
	source_side = get_local_entity_int_value (source, INT_TYPE_SIDE);
	source_heading = 0.0;  // hind map doesn't rotate
	source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);
	source_target = get_local_entity_parent (source, LIST_TYPE_TARGET);

	recentre_map_texture(source_position);

	scale = RADIUS / map_range;

	//
	// match ground radar origin
	//

	x_origin = 0.0;
	y_origin = 0.0;

	get_2d_float_screen_coordinates (x_origin, y_origin, &u, &v);

	u -= mfd_viewport_x_min;
	v -= mfd_viewport_y_min;

	////////////////////////////////////////
	//
	//VJ 030423 TSD RENDER MOD
	//
	////////////////////////////////////////

	{
		draw_tsd_terrain_map (mfd_env, -y_origin, map_range, scale, source_position, source_heading, TRUE);
		draw_tsd_contour_map (mfd_env, -y_origin, map_range, scale, source_position, source_heading, TRUE, TRUE);
	}

	// grid and towns
	{
		rgb_colour grid_colour;
		
		set_rgb_colour(grid_colour, 96, 64, 0, 255);
		draw_tsd_map_grid(source_position, scale, grid_colour);
		
		set_mono_font_colour (MFD_COLOUR1);
		set_mono_font_type (MONO_FONT_TYPE_6X10);

		draw_tsd_map_towns(source_position, scale);
	}
	
	////////////////////////////////////////
	//
	// waypoint route
	//
	////////////////////////////////////////

	{
		entity
			*wp1,
			*wp2;

		vec3d
			wp1_rel_position,
			wp2_rel_position;

		rgb_colour waypoint_colour = MFD_COLOUR_RED;

		wp1 = get_local_entity_first_waypoint (source);

		if (wp1)
		{
			set_2d_viewport_origin (mfd_env, u, v);

			//
			// waypoint route
			//

			get_waypoint_display_position (source, wp1, &wp1_rel_position);

			wp1_rel_position.x = (wp1_rel_position.x - source_position->x) * scale;
			wp1_rel_position.z = (wp1_rel_position.z - source_position->z) * scale;

			wp2 = get_local_entity_child_succ (wp1, LIST_TYPE_WAYPOINT);

			while (wp2)
			{
				get_waypoint_display_position (source, wp2, &wp2_rel_position);

				wp2_rel_position.x = (wp2_rel_position.x - source_position->x) * scale;
				wp2_rel_position.z = (wp2_rel_position.z - source_position->z) * scale;

				if (draw_large_mfd)
					draw_2d_half_thick_line (wp1_rel_position.x, wp1_rel_position.z, wp2_rel_position.x, wp2_rel_position.z, waypoint_colour);  // 2

				wp1 = wp2;

				wp1_rel_position = wp2_rel_position;

				wp2 = get_local_entity_child_succ (wp1, LIST_TYPE_WAYPOINT);
			}

			//
			// waypoint markers
			//

			set_mono_font_colour (MFD_COLOUR_RED);

			set_mono_font_type (MONO_FONT_TYPE_10X16);

			wp1 = get_local_entity_first_waypoint (source);

			while (wp1)
			{
				get_waypoint_display_position (source, wp1, &wp1_rel_position);

				wp1_rel_position.x = (wp1_rel_position.x - source_position->x) * scale;
				wp1_rel_position.z = (wp1_rel_position.z - source_position->z) * scale;

				if (draw_large_mfd)
				{
					set_2d_mono_font_position (wp1_rel_position.x, wp1_rel_position.z);
					set_mono_font_rel_position (-4.0, 10.0);
				}

				print_mono_font_char (get_local_entity_char_value (wp1, CHAR_TYPE_TAG));

				wp1 = get_local_entity_child_succ (wp1, LIST_TYPE_WAYPOINT);
			}

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);
		}
	}

	////////////////////////////////////////
	//
	// aircraft datum symbol
	//
	////////////////////////////////////////

	// last pixel must be transparent because it's repeated when texture doesn't fill entire polygon
	draw_line(0, 0, 0, mfd_viewport_size - 1, clear_mfd_colour);
	draw_line(0, 0, mfd_viewport_size - 1, 0, clear_mfd_colour);
	draw_line(0, mfd_viewport_size - 1, mfd_viewport_size - 1, mfd_viewport_size - 1, clear_mfd_colour);
	draw_line(mfd_viewport_size - 1, 0, mfd_viewport_size - 1, mfd_viewport_size - 1, clear_mfd_colour);
	
	map_up_to_date = TRUE;
}

void draw_hind_mfd_on_cockpit (float x_org, float y_org, int large_mfd, int draw_translucent_background)
{
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

void draw_hind_mfd_on_texture (void)
{	
	set_system_texture_screen (mfd_texture_screen, TEXTURE_INDEX_HIND_MAP_DISPLAY);

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

	if (!map_up_to_date || !scroll_map(get_local_entity_vec3d_ptr (get_gunship_entity(), VEC3D_TYPE_POSITION)))
	{
		set_active_screen (mfd_texture_screen);
	
		if (lock_screen (mfd_texture_screen))
		{
			set_block (0, 0, mfd_viewport_size - 1, mfd_viewport_size - 1, clear_mfd_colour);
	
			draw_layout_grid ();
	
			draw_map_display();
			
			flush_screen_texture_graphics (mfd_texture_screen);
	
			unlock_screen (mfd_texture_screen);
		}
	
		set_active_screen (video_screen);
	}
/*
	if(command_line_export_mfd)
	{
		export_screen=create_screen_for_system_texture (TEXTURE_INDEX_HIND_MAP_DISPLAY);
		copy_export_mfd(export_screen,NULL);
	}
*/
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

void draw_overlaid_hind_mfd (float x_org, float y_org, float size)
{
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_hind_eo_display_visible (void)
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
