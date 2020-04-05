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

#define DEBUG_MODULE 0
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void copy_export_mfd(screen* export_left, screen* export_right);

static mfd_modes
	mfd_mode;

#ifndef OGRE_EE
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

#define MFD_TEXTURE_SIZE			(512)   // (1024)  Javelin  6/19
#define MFD_VIEWPORT_SIZE           (512)   // (1024)  Javelin  6/19

#define EO_VIEWPORT_SIZE   			(256)

static env_2d
	*mfd_env = nullptr;

static float
	mfd_viewport_size,
	mfd_viewport_x_org,
	mfd_viewport_y_org,
	mfd_viewport_x_min,
	mfd_viewport_y_min,
	mfd_viewport_x_max,
	mfd_viewport_y_max;
#endif

static float
#ifndef OGRE_EE
	i_translate_3d,
	j_translate_3d,
	i_scale_3d,
	j_scale_3d,
	map_range,
#endif
	map_scale;

static int
	map_active = TRUE,
#ifndef OGRE_EE
	mfd_texture_size,
	mfd_viewport_texture_x_org,
	mfd_viewport_texture_y_org,
#endif
	map_up_to_date = FALSE;

#ifndef OGRE_EE
rgb_colour
	clear_mfd_colour;

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
	*eo_texture_screen = nullptr,
	*mfd_texture_screen = nullptr,
	*flight_mfd_texture_screen = nullptr;   				//  Javelin  6/19
#endif

static vec3d
	map_centre_position;

#ifndef OGRE_EE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static rgb_colour
	mfd_colours[22];					//  Javelin 6/19

#define MFD_COLOUR1 		  	(mfd_colours[0])
#define MFD_COLOUR2 		  	(mfd_colours[1])
#define MFD_COLOUR3 		  	(mfd_colours[2])
#define MFD_COLOUR4	  	  	(mfd_colours[3])
#define MFD_COLOUR5			(mfd_colours[4])
#define MFD_EO_TEXT_COLOUR		(mfd_colours[5])
#define MFD_CONTOUR_COLOUR		(mfd_colours[6])
#define MFD_RIVER_COLOUR		(mfd_colours[7])
#define MFD_ROAD_COLOUR			(mfd_colours[8])
#define MFD_BACKGROUND_COLOUR		(mfd_colours[9])
#define MFD_COLOUR7			(mfd_colours[10])
#define MFD_COLOUR8			(mfd_colours[11])
#define MFD_COLOUR_BLUE			(mfd_colours[12])
#define MFD_COLOUR_YELLOW		(mfd_colours[13])
#define MFD_COLOUR_DARK_YELLOW		(mfd_colours[14])
#define MFD_COLOUR_RED			(mfd_colours[15])
#define MFD_COLOUR_CYAN			(mfd_colours[16])
#define MFD_COLOUR_DARK_BLUE		(mfd_colours[17])
#define MFD_COLOUR_DARK_RED		(mfd_colours[18])
#define MFD_CLEAR_COLOUR		(mfd_colours[19])
#define MFD_COLOUR_LIGHT_BLUE		(mfd_colours[20])	//  Javelin 6/19
#define MFD_COLOUR_DARK_GREEN	(mfd_colours[21])


////////////////////////////////////////
//
// DTV
//
////////////////////////////////////////

static display_3d_light_levels
	llltv_light_levels[WEATHERMODE_LAST][NUM_DAY_SEGMENT_TYPES] =
	{
		// WEATHERMODE_INVALID
		{
			DISPLAY_3D_LIGHT_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_LIGHT_LEVEL_HIGH,	 	// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_LIGHT_LEVEL_HIGH, 	// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_LIGHT_LEVEL_MEDIUM,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_DRY
		{
			DISPLAY_3D_LIGHT_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_LIGHT_LEVEL_HIGH,	 	// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_LIGHT_LEVEL_HIGH, 	// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_LIGHT_LEVEL_MEDIUM,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_LIGHT_RAIN
		{
			DISPLAY_3D_LIGHT_LEVEL_MEDIUM,		// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_LIGHT_LEVEL_MEDIUM, 	// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_LIGHT_LEVEL_MEDIUM, 		// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_LIGHT_LEVEL_MEDIUM,		// DAY_SEGMENT_TYPE_NIGHT
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
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_DRY
		{
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_LIGHT_RAIN
		{
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_HEAVY_RAIN
		{
			DISPLAY_3D_NOISE_LEVEL_HIGH,	// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_HIGH,	// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_SNOW
		{
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,		// DAY_SEGMENT_TYPE_NIGHT
		},
	};

////////////////////////////////////////
//
// LLLTV
//
////////////////////////////////////////

static display_3d_light_levels
	dtv_light_levels[WEATHERMODE_LAST][NUM_DAY_SEGMENT_TYPES] =
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
			DISPLAY_3D_LIGHT_LEVEL_MEDIUM, 		// DAY_SEGMENT_TYPE_DUSK
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
			DISPLAY_3D_LIGHT_LEVEL_MEDIUM, 		// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_LIGHT_LEVEL_LOW,		// DAY_SEGMENT_TYPE_NIGHT
		},
	};

static display_3d_noise_levels
	dtv_noise_levels[WEATHERMODE_LAST][NUM_DAY_SEGMENT_TYPES] =
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
			DISPLAY_3D_NOISE_LEVEL_LOW,	// DAY_SEGMENT_TYPE_DUSK
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
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_SNOW
		{
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,		// DAY_SEGMENT_TYPE_DAY
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

////////////////////////////////////////
//
// HEADING SCALE						//  Javelin  6/19
//
////////////////////////////////////////

#if 0
static char large_heading_scale_datum[] =
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

static char small_heading_scale_datum[] =
{
	5,
	3,
	-2,
	0,
	0,0,1,0,0,
	0,1,1,1,0,
	1,1,1,1,1,
};
#endif

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

static char
	*main_horizon_mask = NULL;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void initalize_horizon_mask(int width, char** mask)			//  Javelin  6/19
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
#endif


void toggle_mi24_map(void)
{
	map_active = !map_active;
}

#ifndef OGRE_EE
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
	set_rgb_colour (MFD_COLOUR_LIGHT_BLUE,   192, 192, 255,  255);		//  Javelin 6/19
	set_rgb_colour (MFD_COLOUR_DARK_GREEN,    60, 160, 60,   255);	    //  Javelin 6/19

	set_rgb_colour (clear_mfd_colour, 	 220, 220, 200, 255);

	Initialise_TSD_render_terrain();
	set_tsd_map_contour_colour(MFD_CONTOUR_COLOUR);
	set_tsd_map_river_colour(MFD_RIVER_COLOUR);
	set_tsd_map_road_colour(MFD_ROAD_COLOUR);
}
#endif

void initialise_hind_mfd (void)
{
#ifndef OGRE_EE
	mfd_env = create_2d_environment ();

	map_up_to_date = FALSE;
	map_active = TRUE;

	mfd_viewport_size = MFD_VIEWPORT_SIZE;
	mfd_texture_size = MFD_TEXTURE_SIZE;
	map_range = 25000.0;
	map_scale = ROOT2 / 25000.0;

	mfd_viewport_texture_x_org = mfd_texture_size / 2;
	mfd_viewport_texture_y_org = mfd_texture_size / 2;

	mfd_viewport_x_min = mfd_viewport_x_org - (mfd_viewport_size * 0.5);
	mfd_viewport_y_min = mfd_viewport_y_org - (mfd_viewport_size * 0.5);
	mfd_viewport_x_max = mfd_viewport_x_org + (mfd_viewport_size * 0.5);
	mfd_viewport_y_max = mfd_viewport_y_org + (mfd_viewport_size * 0.5);

	mfd_texture_screen = create_system_texture_screen (mfd_texture_size, mfd_texture_size, TEXTURE_INDEX_HIND_MAP_DISPLAY, TEXTURE_TYPE_SINGLEALPHA);

	eo_texture_screen = create_system_texture_screen (EO_VIEWPORT_SIZE, EO_VIEWPORT_SIZE, TEXTURE_INDEX_AVCKPT_DISPLAY_RHS_MFD, TEXTURE_TYPE_SINGLEALPHA);

	flight_mfd_texture_screen = create_system_texture_screen (MFD_VIEWPORT_SIZE, MFD_VIEWPORT_SIZE, TEXTURE_INDEX_AVCKPT_DISPLAY_LHS_MFD, TEXTURE_TYPE_SINGLEALPHA);		//  Javelin  6/19

	initialize_colours();

	initalize_horizon_mask(255, &main_horizon_mask);		//  Javelin  6/19

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_hind_mfd (void)
{
#ifndef OGRE_EE
	// reset texture coordinates
	if (upper_left_texture_uv)
	{
		upper_left_texture_uv->u = 0.0;
		upper_left_texture_uv->v = 0.0;
	}
	if (upper_right_texture_uv)
	{
		upper_right_texture_uv->u = 1.0;
		upper_right_texture_uv->v = 0.0;
	}
	if (lower_left_texture_uv)
	{
		lower_left_texture_uv->u = 0.0;
		lower_left_texture_uv->v = 1.0;
	}
	if (lower_right_texture_uv)
	{
		lower_right_texture_uv->u = 1.0;
		lower_right_texture_uv->v = 1.0;
	}

	destroy_2d_environment (mfd_env);

	destroy_screen (mfd_texture_screen);
	destroy_screen (eo_texture_screen);
	destroy_screen (flight_mfd_texture_screen);		//  Javelin  6/19

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void hind_map_waypoints_changed(void)
{
	map_up_to_date = FALSE;
}

#ifndef OGRE_EE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define RADIUS	(ROOT2 - 0.05)

static void draw_map_display(void)
{
	float
		u,
		v,
		scale;

	entity
		*source = nullptr;

	vec3d
		*source_position = nullptr,
		*position = nullptr;				//  Javelin  6/19

	source = get_gunship_entity ();
	source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

	map_centre_position = *source_position;

	scale = RADIUS / map_range;

	//
	// match ground radar origin
	//

	get_2d_float_screen_coordinates (0.0f, 0.0f, &u, &v);

	u -= mfd_viewport_x_min;
	v -= mfd_viewport_y_min;

	////////////////////////////////////////
	//
	//VJ 030423 TSD RENDER MOD
	//
	////////////////////////////////////////

	{
		draw_tsd_terrain_map (mfd_env, 0.0f, map_range, scale, source_position, 0.0f, TRUE);
		draw_tsd_contour_map (mfd_env, 0.0f, map_range, scale, source_position, 0.0f, TRUE, TRUE);
	}

	// grid and towns
	{
		rgb_colour grid_colour;

		set_rgb_colour(grid_colour, 96, 64, 0, 255);
		draw_tsd_map_grid(source_position, scale, grid_colour);

		set_mono_font_colour (MFD_COLOUR1);
		set_mono_font_type (MONO_FONT_TYPE_12X20);

		draw_tsd_map_towns(source_position, scale);
	}

	////////////////////////////////////////
	//
	// waypoint route
	//
	////////////////////////////////////////

	{
		entity
			*wp1 = nullptr,
			*wp2 = nullptr;

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

				draw_2d_circle(wp1_rel_position.x, wp1_rel_position.z, 0.008, waypoint_colour);

				set_2d_mono_font_position (wp1_rel_position.x, wp1_rel_position.z);
				set_mono_font_rel_position (-4.0, 8.0);

				print_mono_font_char (get_local_entity_char_value (wp1, CHAR_TYPE_TAG));

				wp1 = get_local_entity_child_succ (wp1, LIST_TYPE_WAYPOINT);
			}

	////////////////////////////////
	//   Aircraft Position Marker			  added by Javelin 6/19
	////////////////////////////////

		position = get_local_entity_vec3d_ptr (get_gunship_entity(), VEC3D_TYPE_POSITION);

		u = (position->x - map_centre_position.x) * map_scale * 0.125,
		v = (position->z - map_centre_position.z) * map_scale * 0.115;

		draw_2d_circle (u, v, 0.05,  MFD_COLOUR_DARK_GREEN);
		draw_2d_circle (u, v, 0.053, MFD_COLOUR_DARK_GREEN);
		draw_2d_circle (u, v, 0.056, MFD_COLOUR_DARK_GREEN);


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

	map_up_to_date = FALSE;   //  changed by Javelin 6/19 to FALSE so the map pointer would move.
}

void draw_hind_mfd_on_cockpit (float x_org, float y_org, int large_mfd, int draw_translucent_background)
{
	//  Empty, no Routine at all.
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
	//  Empty, no Routine at all.
}

#ifndef OGRE_EE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define ONE_OVER_SQRT2 0.707106

static float get_eo_sensor_fov(eo_params *eo, target_acquisition_systems system)
{
	// TODO: change fov numbers
	float fov = 9.0;

	switch (eo->field_of_view)
	{
		case EO_FOV_MEDIUM:
		{
			if (system == TARGET_ACQUISITION_SYSTEM_DTV)
				fov = 4.0 * ONE_OVER_SQRT2;
			else  // DTV or DVO
				fov = 2.0 * ONE_OVER_SQRT2;

			break;
		}
		case EO_FOV_WIDE:
		{
			if (system == TARGET_ACQUISITION_SYSTEM_DTV)
				fov = 15.0 * ONE_OVER_SQRT2;
			else  // DVO
				fov = 9.0 * ONE_OVER_SQRT2;

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
		*position = nullptr;

	weathermodes
		weather_mode;

	day_segment_types
		day_segment_type;

	display_3d_tints
		tint;

	position = get_local_entity_vec3d_ptr (get_gunship_entity (), VEC3D_TYPE_POSITION);

	weather_mode = get_simple_session_weather_at_point (position);
	ASSERT ((weather_mode > WEATHERMODE_INVALID) && (weather_mode < WEATHERMODE_LAST));

	day_segment_type = (day_segment_types) get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE);
	ASSERT ((day_segment_type >= 0) && (day_segment_type < NUM_DAY_SEGMENT_TYPES));

	switch (system)
	{
		case TARGET_ACQUISITION_SYSTEM_DTV:
		{
			light_level = dtv_light_levels[weather_mode][day_segment_type];
			noise_level = dtv_noise_levels[weather_mode][day_segment_type];
			tint = DISPLAY_3D_TINT_AMBER_VISUAL;

			break;
		}
		case TARGET_ACQUISITION_SYSTEM_LLLTV:
		{
			light_level = llltv_light_levels[weather_mode][day_segment_type];
			noise_level = llltv_noise_levels[weather_mode][day_segment_type];
			tint = DISPLAY_3D_TINT_GREEN_VISUAL;

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
		*s = nullptr;
	char
		buffer[200];

	int
		heading_readout;

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
		*source = nullptr,
		*target = nullptr;

	vec3d
		*source_position = nullptr,
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
		case TARGET_ACQUISITION_SYSTEM_DTV:
		{
			print_mono_font_string ("DAY FILTER");

			break;
		}
		case TARGET_ACQUISITION_SYSTEM_LLLTV:
		{
			print_mono_font_string ("NIGHT FILTER");

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

	// airspeed

	sprintf(buffer, "%+04.0f", current_flight_dynamics->indicated_airspeed.value);
	set_2d_mono_font_position (-1.0, 1.0);
	set_mono_font_rel_position(1.0, 18.0);
	print_mono_font_string(buffer);

	// altitude

	if (current_flight_dynamics->radar_altitude.value < 300.0)
	{
		sprintf(buffer, "R%03.0f", current_flight_dynamics->radar_altitude.value);
		set_2d_mono_font_position (1.0, 1.0);
		set_mono_font_rel_position(-get_mono_font_string_width(buffer) - 2.0, 18.0);
		print_mono_font_string(buffer);
	}

	//
	// low light
	//

	if (eo_low_light)
	{
		y_adjust = 32.0;

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

	// horizon
	{
		float roll = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_ROLL);
		float pitch = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_PITCH);
		float pitch_adjustment = -pitch / rad(90) * 0.5;

		draw_2d_half_thick_line(-0.35, 0.0, -0.3, 0.0, MFD_EO_TEXT_COLOUR);
		draw_2d_half_thick_line( 0.35, 0.0,  0.3, 0.0, MFD_EO_TEXT_COLOUR);

		// draw datum
		set_2d_instance_rotation (mfd_env, roll);

		draw_2d_half_thick_line(-0.75, pitch_adjustment, -0.4, pitch_adjustment, MFD_EO_TEXT_COLOUR);
		draw_2d_half_thick_line( 0.75, pitch_adjustment,  0.4, pitch_adjustment, MFD_EO_TEXT_COLOUR);

		reset_2d_instance (mfd_env);
	}

	//
	// target gates
	//

	if (valid_3d)
	{
		if (target)
		{
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
	if (eo_sensor == TARGET_ACQUISITION_SYSTEM_DTV)
		draw_2d_eo_display (&hind_dtv, TARGET_ACQUISITION_SYSTEM_DTV, hind_damage.dtv, TRUE);
	else
		draw_2d_eo_display (&hind_llltv, TARGET_ACQUISITION_SYSTEM_LLLTV, hind_damage.llltv, TRUE);
}
#endif

void draw_hind_virtual_cockpit_ort_view (int x_min, int x_max)
{
#ifndef OGRE_EE
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

	if (eo_sensor == TARGET_ACQUISITION_SYSTEM_DTV)
	{
		eo = &hind_dtv;
		system = TARGET_ACQUISITION_SYSTEM_DTV;
		damaged = hind_damage.dtv;
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
	f3d_clear_screen ( black.colour );

	if (!damaged)
	{
		fov = rad(get_eo_sensor_fov(eo, system));

		set_eo_view_params(system, x_min, full_screen_y_min, x_max, full_screen_y_max, fov, fov);

		draw_eo_3d_scene = TRUE;
		draw_main_3d_scene (&eo_vp);
		draw_eo_3d_scene = FALSE;
	}
#endif
}

void draw_hind_virtual_cockpit_ort_symbology(void)
{
#ifndef OGRE_EE
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

	mfd_viewport_x_max = EO_VIEWPORT_SIZE;
	mfd_viewport_y_max = EO_VIEWPORT_SIZE;

	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

	mfd_screen_x_min = full_screen_x_mid - ((256.0 / (640.0 * 2.0)) * full_screen_width);
	mfd_screen_y_min = full_screen_y_mid - ((256.0 / (480.0 * 2.0)) * full_screen_height);

	mfd_screen_x_max = full_screen_x_mid + ((256.0 / (640.0 * 2.0)) * full_screen_width);
	mfd_screen_y_max = full_screen_y_mid + ((256.0 / (480.0 * 2.0)) * full_screen_height);

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
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_hind_eo_display_visible (void)
{
	return
	(
		(mfd_mode == MFD_MODE_DTV) ||
		(mfd_mode == MFD_MODE_LLLTV)
	);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_mi24_map_caret_position(float *x, float *z)
{
	if (!hind_damage.navigation_computer)
	{
		vec3d
			*position = nullptr;
		float
			nx,
			nz;

		position = get_local_entity_vec3d_ptr (get_gunship_entity(), VEC3D_TYPE_POSITION);

		nx = (position->x - map_centre_position.x) * map_scale * 0.125,
		nz = (position->z - map_centre_position.z) * map_scale * 0.115;

		*x = bound(nx, -0.12, 0.12);
		*z = bound(nz, -0.075, 0.065);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////   Everything from here down is added to install a Flight MFD for Export to an external monitor.  Javelin  6/19
////
////   FLIGHT
////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 	HEADING SCALE
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

	y_position = -0.8375;

	draw_2d_box(-0.5, y_position - 0.1, 0.5, y_position + 0.1, TRUE, FALSE, MFD_COLOUR_DARK_BLUE);
	draw_2d_box(-0.5, y_position - 0.085, 0.5, y_position + 0.1, FALSE, FALSE, MFD_COLOUR_LIGHT_BLUE);  //  - 0.1

	set_2d_window (mfd_env, MFD_WINDOW_X_MIN * 0.5, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX * 0.5, MFD_WINDOW_Y_MAX);

	mfd_vp_x_min = mfd_viewport_x_org - (mfd_viewport_size * (0.5 * 0.5));

	mfd_vp_x_max = mfd_viewport_x_org + (mfd_viewport_size * (0.5 * 0.5));

	set_2d_viewport (mfd_env, mfd_vp_x_min, mfd_viewport_y_min, mfd_vp_x_max, mfd_viewport_y_max);

	//
	// large and small MFD position
	//

	get_2d_float_screen_coordinates (0.0, y_position, &i, &j);

	set_mono_font_type (MONO_FONT_TYPE_10X16);

	//
	// draw command heading carat
	//

	if (draw_command_heading)
	{
		if (!hind_damage.navigation_computer)
		{
			entity
				*wp = nullptr;

			wp = get_local_entity_current_waypoint (get_gunship_entity ());

			if (wp)
			{
				vec3d
					*gunship_position = nullptr,
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

		draw_2d_half_thick_line (x, y_position + 0.1, x, y_position + 0.05, MFD_COLOUR_LIGHT_BLUE);

		//
		// minor tick every 5 degrees
		//

		draw_2d_half_thick_line (x + 0.125, y_position + 0.1, x + 0.125, y_position + 0.075, MFD_COLOUR_LIGHT_BLUE);

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

		set_2d_mono_font_position (x, y_position - 0.05);  //  - 0.1

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

	set_mono_font_type (MONO_FONT_TYPE_10X16);


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
		set_mono_font_rel_position ((-width * 0.5) + 1.0, -3.0);  //  -3.0

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
#define PITCH_BAR_X10		((float) +0.265)
#define PITCH_BAR_Y10		((float) +0.050)
#define PITCH_BAR_X11		((float) +0.265)
#define PITCH_BAR_Y11		((float) -0.050)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

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

		set_mono_font_type (MONO_FONT_TYPE_10X16);

		y_adjust_above_line = -6.0;		// -3.0
		y_adjust_below_line = -6.0;		// -3.0

	x_centre = 0.0;

	size = 0.495;			//  = 0.59 
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

			draw_2d_half_thick_line(left_edge, left_y, right_edge, right_y, sys_col_red);

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
				*left_colour = nullptr,
				*right_colour = nullptr;

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
					draw_2d_half_thick_line (-PITCH_BAR_X2, PITCH_BAR_Y2, PITCH_BAR_X2, -PITCH_BAR_Y2, MFD_COLOUR_LIGHT_BLUE);

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
					draw_2d_half_thick_line (+PITCH_BAR_X1, +PITCH_BAR_Y1, +PITCH_BAR_X6, +PITCH_BAR_Y6, MFD_COLOUR_LIGHT_BLUE);
					draw_2d_half_thick_line (-PITCH_BAR_X1, +PITCH_BAR_Y1, -PITCH_BAR_X6, +PITCH_BAR_Y6, MFD_COLOUR_LIGHT_BLUE);

					break;
				}
				////////////////////////////////////////
				case -9:
				////////////////////////////////////////
				{
					draw_2d_half_thick_line (+PITCH_BAR_X1, +PITCH_BAR_Y1, +PITCH_BAR_X2, +PITCH_BAR_Y2, MFD_COLOUR_LIGHT_BLUE);
					draw_2d_half_thick_line (-PITCH_BAR_X1, +PITCH_BAR_Y1, -PITCH_BAR_X2, +PITCH_BAR_Y2, MFD_COLOUR_LIGHT_BLUE);

					draw_2d_half_thick_line (+PITCH_BAR_X3, +PITCH_BAR_Y3, +PITCH_BAR_X4, +PITCH_BAR_Y4, MFD_COLOUR_LIGHT_BLUE);
					draw_2d_half_thick_line (-PITCH_BAR_X3, +PITCH_BAR_Y3, -PITCH_BAR_X4, +PITCH_BAR_Y4, MFD_COLOUR_LIGHT_BLUE);

					draw_2d_half_thick_line (+PITCH_BAR_X5, +PITCH_BAR_Y5, +PITCH_BAR_X6, +PITCH_BAR_Y6, MFD_COLOUR_LIGHT_BLUE);
					draw_2d_half_thick_line (-PITCH_BAR_X5, +PITCH_BAR_Y5, -PITCH_BAR_X6, +PITCH_BAR_Y6, MFD_COLOUR_LIGHT_BLUE);

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
	// size = 1.2;

	reset_2d_instance (mfd_env);
	set_2d_window (mfd_env, MFD_WINDOW_X_MIN, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX, MFD_WINDOW_Y_MAX);
	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			draw_2d_mono_sprite (main_horizon_mask, x_centre , y_centre, MFD_CLEAR_COLOUR);

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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_altitude_scale (void)
{
	const float
		y_centre = 0.0,
		box_start = 0.7,
		box_end = box_start + 0.25,
		box_top = y_centre + 0.045,		// 0.04
		box_bottom = y_centre - 0.045,	// 0.04
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
		*format = nullptr,
		buffer[8];

	int
		u1, u2, v1, v2,
		displayed_altitude = (int)((barometric_altitude + 5) / 10);


	draw_2d_box(x1, scale_top, x5, scale_bottom, TRUE, FALSE, MFD_COLOUR_DARK_BLUE);
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

		set_mono_font_type (MONO_FONT_TYPE_10X16);
		y_adjust = -4.0;   //  -2.0

		for (loop = 0; loop <= 25; loop++)
		{
			if (int_scale_step_5 >= 0)
			{
				draw_2d_half_thick_line (x1, y, x2, y, MFD_COLOUR_LIGHT_BLUE);

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
	set_block(u1, v1, u2, v2, MFD_COLOUR_DARK_BLUE);

	// draw surrounding box
	draw_2d_half_thick_line(box_start, box_top, box_end, box_top, MFD_COLOUR_LIGHT_BLUE);
	draw_2d_half_thick_line(box_start, box_bottom, box_end, box_bottom, MFD_COLOUR_LIGHT_BLUE);
	draw_2d_half_thick_line(box_start, box_top, box_start, box_bottom, MFD_COLOUR_LIGHT_BLUE);
	draw_2d_half_thick_line(box_end, box_top, box_end, box_bottom, MFD_COLOUR_LIGHT_BLUE);

	// print digital readout

	set_mono_font_type (MONO_FONT_TYPE_12X20);
	y_adjust = -7.0;	//  -2.0

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
		box_top = y_centre + 0.045,		//  0.04
		box_bottom = y_centre - 0.045,	//  0.04
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


	draw_2d_box(x1, scale_top, x5, scale_bottom, TRUE, FALSE, MFD_COLOUR_DARK_BLUE);
	draw_2d_box(x1, scale_top, x5, scale_bottom, FALSE, FALSE, MFD_COLOUR_LIGHT_BLUE);

	// draw scale
	get_2d_float_screen_x_coordinate (-y_centre, &v);

	mfd_vp_y_min = v - (0.5 * mfd_viewport_size * (scale_top - scale_bottom) * 0.5);
	mfd_vp_y_max = v + (0.5 * mfd_viewport_size * (scale_top - scale_bottom) * 0.5);

	#if DEBUG_MODULE
		debug_log("min: %.02f, max: %.02f", mfd_vp_y_min, mfd_vp_y_max);
	#endif

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

		set_mono_font_type (MONO_FONT_TYPE_10X16);
		y_adjust = -4.0;  //  -2.0

		for (loop = 0; loop <= 25; loop++)
		{
//			if (int_scale_step_5 > 0)
			{
				draw_2d_half_thick_line (x4, y, x5, y, MFD_COLOUR_LIGHT_BLUE);

				if ((int_scale_step_5 % 4) == 0)
				{
					float x_adjust;
					char buffer[8];

					sprintf(buffer, "%4d", (int_scale_step_5 * 5 / 2));
					x_adjust = get_mono_font_string_width(buffer) + 4;   // +2

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
	set_block(u1, v1, u2, v2, MFD_COLOUR_DARK_BLUE);

	// draw surrounding box
	draw_2d_half_thick_line(box_start, box_top, box_end, box_top, MFD_COLOUR_LIGHT_BLUE);
	draw_2d_half_thick_line(box_start, box_bottom, box_end, box_bottom, MFD_COLOUR_LIGHT_BLUE);
	draw_2d_half_thick_line(box_start, box_top, box_start, box_bottom, MFD_COLOUR_LIGHT_BLUE);
	draw_2d_half_thick_line(box_end, box_top, box_end, box_bottom, MFD_COLOUR_LIGHT_BLUE);

	// print digital readout

	set_mono_font_type (MONO_FONT_TYPE_12X20);
	y_adjust = -7.0;

	sprintf(buffer, "%.0f", airspeed);
	x_adjust = -get_mono_font_string_width(buffer) - 1;

	set_2d_mono_font_position (box_end, y_centre);
	set_mono_font_rel_position (x_adjust, y_adjust);
	print_mono_font_string(buffer);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_rate_of_climb_scale (void)
{
	float
		xpos = 0.47,
		y;

	//
	// draw scale
	//

	draw_2d_half_thick_line (+xpos, +0.500, xpos + 0.050, +0.500, MFD_COLOUR_LIGHT_BLUE);
	draw_2d_half_thick_line (+xpos, +0.400, xpos + 0.025, +0.400, MFD_COLOUR_LIGHT_BLUE);
	draw_2d_half_thick_line (+xpos, +0.300, xpos + 0.025, +0.300, MFD_COLOUR_LIGHT_BLUE);
	draw_2d_half_thick_line (+xpos, +0.200, xpos + 0.025, +0.200, MFD_COLOUR_LIGHT_BLUE);
	draw_2d_half_thick_line (+xpos, +0.100, xpos + 0.025, +0.100, MFD_COLOUR_LIGHT_BLUE);
	draw_2d_half_thick_line (+xpos, +0.000, xpos + 0.050, +0.000, MFD_COLOUR_LIGHT_BLUE);
	draw_2d_half_thick_line (+xpos, -0.100, xpos + 0.025, -0.100, MFD_COLOUR_LIGHT_BLUE);
	draw_2d_half_thick_line (+xpos, -0.200, xpos + 0.025, -0.200, MFD_COLOUR_LIGHT_BLUE);
	draw_2d_half_thick_line (+xpos, -0.300, xpos + 0.025, -0.300, MFD_COLOUR_LIGHT_BLUE);
	draw_2d_half_thick_line (+xpos, -0.400, xpos + 0.025, -0.400, MFD_COLOUR_LIGHT_BLUE);
	draw_2d_half_thick_line (+xpos, -0.500, xpos + 0.050, -0.500, MFD_COLOUR_LIGHT_BLUE);

	//
	// get indicator position (fsd +/- 10m/s)
	//

	y = current_flight_dynamics->world_velocity_y.value;

	y = bound (y, -10.0, 10.0);

	y *= 0.05;

	draw_2d_mono_sprite(large_rate_of_climb_scale_pointer, xpos + 0.05, y, MFD_COLOUR_LIGHT_BLUE);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_waypoint_information (void)
{
	char
		buffer[80];

	entity
		*wp = nullptr;

	vec3d
		*gunship_position = nullptr,
		waypoint_position;

	float
		waypoint_range;

	wp = get_local_entity_current_waypoint (get_gunship_entity ());

	if (wp)
	{
		set_mono_font_type (MONO_FONT_TYPE_10X16);

		gunship_position = get_local_entity_vec3d_ptr (get_gunship_entity (), VEC3D_TYPE_POSITION);

		get_waypoint_display_position (get_gunship_entity (), wp, &waypoint_position);

		//
		// waypoint id & range
		//

		waypoint_range = get_2d_range (gunship_position, &waypoint_position);

		if (!hind_damage.navigation_computer)
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

		if ((current_flight_dynamics->velocity_z.value > 0.1) && (!hind_damage.navigation_computer))
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


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////
/////   FLIGHT MFD
/////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_hind_flight_mfd (void)
{
#ifndef OGRE_EE
	screen *export_screen;						//  Javelin  6/19
	set_system_texture_screen (flight_mfd_texture_screen, TEXTURE_INDEX_AVCKPT_DISPLAY_LHS_MFD);

	//
	// draw MFD on texture
	//

	set_active_screen (flight_mfd_texture_screen);

	if (lock_screen (flight_mfd_texture_screen))
	{
      		set_block (0, 0, MFD_VIEWPORT_SIZE - 1, MFD_VIEWPORT_SIZE - 1, clear_mfd_colour);

		draw_mfd_layout_grid ();

		    draw_flight_display_mfd ();

		unlock_screen (flight_mfd_texture_screen);
	}

	set_active_screen (video_screen);

	if(command_line_export_mfd)	//  restored  Javelin 6/19
	{
		export_screen = get_screen_of_system_texture (TEXTURE_INDEX_AVCKPT_DISPLAY_LHS_MFD);
		copy_export_mfd(export_screen, NULL);
	}

#endif
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
#endif

void draw_hind_mfd_on_texture (void)
{
#ifndef OGRE_EE
	screen *export_screen;						//  Javelin  6/19
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

	mfd_viewport_size = MFD_VIEWPORT_SIZE;
	mfd_texture_size = MFD_TEXTURE_SIZE;

	mfd_viewport_texture_x_org = mfd_texture_size / 2;
	mfd_viewport_texture_y_org = mfd_texture_size / 2;

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
	// draw MFD Map display
	//
	////////////////////////////////////////

	if (!hind_damage.navigation_computer && !map_up_to_date)
	{
		set_active_screen (mfd_texture_screen);

		if (lock_screen (mfd_texture_screen))
		{
			set_block (0, 0, mfd_viewport_size - 1, mfd_viewport_size - 1, clear_mfd_colour);

			draw_mfd_layout_grid ();

			draw_map_display ();

			unlock_screen (mfd_texture_screen);
		}

		set_active_screen (video_screen);
	}

	if(command_line_export_mfd)		//  Javelin  6/19
	{
		export_screen = get_screen_of_system_texture (TEXTURE_INDEX_HIND_MAP_DISPLAY);
		copy_export_mfd(NULL, export_screen);
	}

		draw_hind_flight_mfd ();	//  Javelin  6/19   Add in a Flight MFD for Export

#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
