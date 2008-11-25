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

#define EO_VIEWPORT_SIZE   			(256)

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
	i_translate_3d,
	j_translate_3d,
	i_scale_3d,
	j_scale_3d,
	map_range,
	map_scale;

static int
	map_active = TRUE,
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
	*eo_texture_screen,
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
#define MFD_EO_TEXT_COLOUR		(mfd_colours[5])
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void toggle_mi24_map(void)
{
	map_active = !map_active;
}

int mi24_map_active(void)
{
	return map_active;
}

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
	set_rgb_colour (MFD_EO_TEXT_COLOUR,      220,200,  56, 255);
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
	map_active = TRUE;

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

	eo_texture_screen = create_system_texture_screen (EO_VIEWPORT_SIZE, EO_VIEWPORT_SIZE, TEXTURE_INDEX_AVCKPT_DISPLAY_RHS_MFD, TEXTURE_TYPE_SINGLEALPHA);

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
	destroy_screen (eo_texture_screen);

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
	if (!map_display_model)
		return FALSE;

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

	if (hind_damage.navigation_computer)
		return TRUE;
	else
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

				draw_2d_circle(wp1_rel_position.x, wp1_rel_position.z, 0.008 + debug_var_x * 0.01, waypoint_colour);

				set_2d_mono_font_position (wp1_rel_position.x, wp1_rel_position.z);
				set_mono_font_rel_position (-4.0, 8.0);

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
	if (!map_active)
		return;

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

#define ONE_OVER_SQRT2 0.707106

static float get_eo_sensor_fov(eo_params *eo, target_acquisition_systems system)
{
	// TODO: change fov numbers
	float fov = 10.0;

	switch (eo->field_of_view)
	{
		case EO_FOV_MEDIUM:
		{
			if (system == TARGET_ACQUISITION_SYSTEM_FLIR)
				fov = 4.0 * ONE_OVER_SQRT2;
			else  // DTV or DVO
				fov = 3.0 * ONE_OVER_SQRT2;

			break;
		}
		case EO_FOV_WIDE:
		{
			if (system == TARGET_ACQUISITION_SYSTEM_FLIR)
				fov = 15.0 * ONE_OVER_SQRT2;
			else  // DVO
				fov = 12.0 * ONE_OVER_SQRT2;

			break;
		}
		default:
		{
			debug_fatal ("Invalid field of view = %d", eo->field_of_view);

			break;
		}
	}

	return fov;
}

static void set_eo_view_params(target_acquisition_systems system, int x_min, int y_min, int x_max, int y_max, float xfov, float yfov)
{
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

	int
		tint;

	position = get_local_entity_vec3d_ptr (get_gunship_entity (), VEC3D_TYPE_POSITION);

	weather_mode = get_simple_session_weather_at_point (position);
	ASSERT ((weather_mode > WEATHERMODE_INVALID) && (weather_mode < WEATHERMODE_LAST));

	day_segment_type = get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE);
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

	set_main_3d_params (tint, light_level, noise_level, x_min, y_min, x_max, y_max, xfov, yfov);
}



static void draw_2d_eo_display (eo_params *eo, target_acquisition_systems system, int damaged, int valid_3d)
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
		target_range = 0.0,
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
	target_range = get_range_to_target();

	////////////////////////////////////////
	//
	// text
	//
	////////////////////////////////////////

	set_mono_font_colour (MFD_EO_TEXT_COLOUR);

	set_mono_font_type (MONO_FONT_TYPE_7X12);

	//
	// sensor type
	//

	y_adjust = 5.0;
	set_2d_mono_font_position (-1.0, 1.0);
	set_mono_font_rel_position (1.0, y_adjust);

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
		case TARGET_ACQUISITION_SYSTEM_PERISCOPE:
		{
			print_mono_font_string ("SCOPE");

			break;
		}
		default:
		{
			print_mono_font_string ("XXX");

			break;
		}
	}

	//
	// damaged
	//

	if (damaged)
	{
		draw_2d_line (-0.5, -0.5,  0.5, 0.5, MFD_COLOUR1);
		draw_2d_line ( 0.5, -0.5, -0.5, 0.5, MFD_COLOUR1);

		return;
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

	set_mono_font_rel_position ((-width * 0.5) + 1.0, y_adjust);

	print_mono_font_string (buffer);

	//
	// low light
	//

	if (eo_low_light)
	{
		y_adjust = 18.0;

		set_2d_mono_font_position (-1.0, 1.0);

		set_mono_font_rel_position (1.0, y_adjust);

		print_mono_font_string ("LO LIGHT");
	}

	//
	// field of view
	//

	switch (eo->field_of_view)
	{
		case EO_FOV_NARROW:
		case EO_FOV_MEDIUM:
		{
			s = "NARROW";
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

	width += 2.0;
	y_adjust = 5.0;

	set_2d_mono_font_position (1.0, 1.0);

	set_mono_font_rel_position (-width, y_adjust);

	print_mono_font_string (s);

	//
	// target name
	//

	y_adjust = -12.0;

	s = get_target_display_name (target, buffer, TRUE);

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
		sprintf (buffer, "%.1fKm", target_range * (1.0 / 1000.0));

		width = get_mono_font_string_width (buffer);

		set_2d_mono_font_position (1.0, -1.0);

		width += 2.0;

		set_mono_font_rel_position (-width, y_adjust);

		print_mono_font_string (buffer);
	}

	//
	// locked
	//

	if (eo_is_locked())
	{
		y_adjust = -25.0;

		set_2d_mono_font_position (-1.0, -1.0);

		set_mono_font_rel_position (1.0, y_adjust);

		print_mono_font_string ("LOCKED");
	}

// Jabberwock 031107 Designated targets

	target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

	if (target && get_local_entity_parent (target, LIST_TYPE_DESIGNATED_TARGET))
	{
		y_adjust = -25.0;

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
		y_adjust = -38.0;

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

	draw_2d_line (-0.075, 0.0, -0.025, 0.0, MFD_EO_TEXT_COLOUR);
	draw_2d_line (0.035, 0.0, 0.08, 0.0, MFD_EO_TEXT_COLOUR);
	draw_2d_line (0.0, -0.075, 0.0, -0.025, MFD_EO_TEXT_COLOUR);
	draw_2d_line (0.0, 0.035, 0.0, 0.08, MFD_EO_TEXT_COLOUR);

	//
	// azimuth
	//

	draw_2d_line (-0.5, 0.8, 0.5, 0.8, MFD_EO_TEXT_COLOUR);

	marker_position = (eo_azimuth / eo_max_azimuth) * 0.5;

	draw_2d_line (-0.5, 0.8 - 0.02, -0.5, 0.8 + 0.02, MFD_EO_TEXT_COLOUR);
	draw_2d_line (0.5, 0.8 - 0.02, 0.5, 0.8 + 0.02, MFD_EO_TEXT_COLOUR);
	draw_2d_line (0.0, 0.8 - 0.01, 0.0, 0.8 + 0.01, MFD_EO_TEXT_COLOUR);
	draw_2d_mono_sprite (large_azimuth_marker, marker_position, 0.8, MFD_EO_TEXT_COLOUR);

	//
	// elevation
	//

	draw_2d_line (-0.9, 0.1, -0.9, -0.3, MFD_EO_TEXT_COLOUR);

	if (eo_elevation < 0.0)
	{
		marker_position = (eo_elevation / eo_min_elevation) * -0.3;
	}
	else
	{
		marker_position = (eo_elevation / eo_max_elevation) * 0.1;
	}

	draw_2d_line (-0.9 - 0.02, 0.1, -0.9 + 0.02, 0.1, MFD_EO_TEXT_COLOUR);
	draw_2d_line (-0.9 - 0.02, -0.3, -0.9 + 0.02, -0.3, MFD_EO_TEXT_COLOUR);
	draw_2d_line (-0.9 - 0.01, 0.0, -0.9 + 0.01, 0.0, MFD_EO_TEXT_COLOUR);
	draw_2d_mono_sprite (large_elevation_marker, -0.9, marker_position, MFD_EO_TEXT_COLOUR);

	//
	// range
	//

	draw_2d_line (0.9, 0.0, 0.9, -0.5, MFD_EO_TEXT_COLOUR);

	draw_2d_line (0.9,  0.000, 0.9 + 0.02,  0.000, MFD_EO_TEXT_COLOUR);
	draw_2d_line (0.9, -0.025, 0.9 + 0.01, -0.025, MFD_EO_TEXT_COLOUR);
	draw_2d_line (0.9, -0.050, 0.9 + 0.01, -0.050, MFD_EO_TEXT_COLOUR);
	draw_2d_line (0.9, -0.075, 0.9 + 0.01, -0.075, MFD_EO_TEXT_COLOUR);

	draw_2d_line (0.9, -0.100, 0.9 + 0.02, -0.100, MFD_EO_TEXT_COLOUR);
	draw_2d_line (0.9, -0.125, 0.9 + 0.01, -0.125, MFD_EO_TEXT_COLOUR);
	draw_2d_line (0.9, -0.150, 0.9 + 0.01, -0.150, MFD_EO_TEXT_COLOUR);
	draw_2d_line (0.9, -0.175, 0.9 + 0.01, -0.175, MFD_EO_TEXT_COLOUR);

	draw_2d_line (0.9, -0.200, 0.9 + 0.02, -0.200, MFD_EO_TEXT_COLOUR);
	draw_2d_line (0.9, -0.225, 0.9 + 0.01, -0.225, MFD_EO_TEXT_COLOUR);
	draw_2d_line (0.9, -0.250, 0.9 + 0.01, -0.250, MFD_EO_TEXT_COLOUR);
	draw_2d_line (0.9, -0.275, 0.9 + 0.01, -0.275, MFD_EO_TEXT_COLOUR);

	draw_2d_line (0.9, -0.300, 0.9 + 0.02, -0.300, MFD_EO_TEXT_COLOUR);

	draw_2d_line (0.9, -0.400, 0.9 + 0.02, -0.400, MFD_EO_TEXT_COLOUR);

	draw_2d_line (0.9, -0.500, 0.9 + 0.02, -0.500, MFD_EO_TEXT_COLOUR);

	if (target_range > 0.0)
	{
		marker_position = (min (target_range, eo_max_visual_range) / eo_max_visual_range) * -0.5;
		draw_2d_mono_sprite (large_range_marker, 0.9, marker_position, MFD_EO_TEXT_COLOUR);
	}

	//
	// target gates
	//

	if (valid_3d)
	{
		if (target)
		{
			if (!((!d3d_can_render_to_texture) && (!draw_large_mfd)))
			{
				tmp = main_vp;

				main_vp = eo_vp;

				get_local_entity_target_point (target, &target_point);

				visibility = get_position_3d_screen_coordinates (&target_point, &i, &j);

				if ((visibility == OBJECT_3D_COMPLETELY_VISIBLE) || (visibility == OBJECT_3D_PARTIALLY_VISIBLE))
				{
					i -= i_translate_3d;
					j -= j_translate_3d;

					i *= i_scale_3d;
					j *= j_scale_3d;

					get_2d_world_position (i, j, &x, &y);

					draw_2d_line (x - 0.20, y + 0.20, x - 0.15, y + 0.20, MFD_EO_TEXT_COLOUR);
					draw_2d_line (x + 0.20, y + 0.20, x + 0.15, y + 0.20, MFD_EO_TEXT_COLOUR);
					draw_2d_line (x - 0.20, y - 0.20, x - 0.15, y - 0.20, MFD_EO_TEXT_COLOUR);
					draw_2d_line (x + 0.20, y - 0.20, x + 0.15, y - 0.20, MFD_EO_TEXT_COLOUR);
					draw_2d_line (x - 0.20, y + 0.20, x - 0.20, y + 0.15, MFD_EO_TEXT_COLOUR);
					draw_2d_line (x - 0.20, y - 0.20, x - 0.20, y - 0.15, MFD_EO_TEXT_COLOUR);
					draw_2d_line (x + 0.20, y + 0.20, x + 0.20, y + 0.15, MFD_EO_TEXT_COLOUR);
					draw_2d_line (x + 0.20, y - 0.20, x + 0.20, y - 0.15, MFD_EO_TEXT_COLOUR);
				}

				main_vp = tmp;
			}
		}
	}
}

static void draw_hind_ort_symbology(int dummy)
{
	if (eo_sensor == TARGET_ACQUISITION_SYSTEM_FLIR)
		draw_2d_eo_display (&hind_flir, TARGET_ACQUISITION_SYSTEM_FLIR, hind_damage.flir, TRUE);
	else
		draw_2d_eo_display (&hind_llltv, TARGET_ACQUISITION_SYSTEM_LLLTV, hind_damage.llltv, TRUE);
}

void draw_hind_virtual_cockpit_ort_view (int x_min, int x_max)
{
	float
		fov;

	eo_params*
		eo;

	target_acquisition_systems
		system;

	rgb_colour
		black;

	int
		damaged = FALSE;

	if (eo_sensor == TARGET_ACQUISITION_SYSTEM_FLIR)
	{
		eo = &hind_flir;
		system = TARGET_ACQUISITION_SYSTEM_FLIR;
		damaged = hind_damage.flir;
	}
	else
	{
		eo = &hind_llltv;
		system = TARGET_ACQUISITION_SYSTEM_LLLTV;
		damaged = hind_damage.llltv;
	}

	black.r = 0;
	black.g = 0;
	black.b = 0;
	black.a = 255;

	// clear background, since we won't be drawing the 3D view over the entire screen
	set_block(0, 0, full_screen_x_max, full_screen_y_max, black);

	if (!damaged)
	{
		fov = rad(get_eo_sensor_fov(eo, system));

		set_eo_view_params(system, x_min, full_screen_y_min, x_max, full_screen_y_max, fov, fov);

		draw_eo_3d_scene = TRUE;
		draw_main_3d_scene (&eo_vp);
		draw_eo_3d_scene = FALSE;
	}
}

void draw_hind_virtual_cockpit_ort_symbology(void)
{
	int
		mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max;

	rgb_colour
		background_colour,
		symbology_colour;

	set_3d_active_environment (main_3d_env);

	//
	// set up MFD 2D environment
	//

	set_2d_active_environment (mfd_env);
	set_2d_window (mfd_env, MFD_WINDOW_X_MIN, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX, MFD_WINDOW_Y_MAX);

	mfd_viewport_size = EO_VIEWPORT_SIZE;

	mfd_viewport_x_org = EO_VIEWPORT_SIZE * 0.5;
	mfd_viewport_y_org = EO_VIEWPORT_SIZE * 0.5;

	mfd_viewport_x_min = 0.0;
	mfd_viewport_y_min = 0.0;

	mfd_viewport_x_max = EO_VIEWPORT_SIZE - 0.001;
	mfd_viewport_y_max = EO_VIEWPORT_SIZE - 0.001;

	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

	mfd_screen_x_min = full_screen_x_mid - ((256.0 / (640.0 * 2.0)) * full_screen_width);
	mfd_screen_y_min = full_screen_y_mid - ((256.0 / (480.0 * 2.0)) * full_screen_height);

	mfd_screen_x_max = full_screen_x_mid + ((256.0 / (640.0 * 2.0)) * full_screen_width) - 0.001;
	mfd_screen_y_max = full_screen_y_mid + ((256.0 / (480.0 * 2.0)) * full_screen_height) - 0.001;

	i_translate_3d = mfd_screen_x_min;
	j_translate_3d = mfd_screen_y_min;

	i_scale_3d = 640.0 / full_screen_width;
	j_scale_3d = 480.0 / full_screen_height;

	symbology_colour = MFD_EO_TEXT_COLOUR;
	set_rgb_colour(background_colour, 255, 255, 255, 0);

	set_system_texture_screen (eo_texture_screen, TEXTURE_INDEX_AVCKPT_DISPLAY_RHS_MFD);

	draw_symbology_to_texture(
		eo_texture_screen,
		TEXTURE_INDEX_AVCKPT_DISPLAY_RHS_MFD,
		mfd_viewport_size,
		mfd_viewport_size,
		mfd_screen_x_min,
		mfd_screen_y_min,
		mfd_screen_x_max,
		mfd_screen_y_max,
		symbology_colour,
		background_colour,
		draw_hind_ort_symbology);
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
