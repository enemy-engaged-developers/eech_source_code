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

#define OLD_EO

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//mue 070223
void copy_export_mfd(screen* export_left, screen* export_right);

#ifdef DEBUG

static char
	*ka50_mfd_mode_names[NUM_KA50_MFD_MODES] =
	{
		"KA50_MFD_MODE_OFF",
		"KA50_MFD_MODE_DAMAGED",
		"KA50_MFD_MODE_FLIR",		//  Javelin 7/19
		"KA50_MFD_MODE_LLLTV",
		"KA50_MFD_MODE_TSD",
		"KA50_MFD_MODE_ASE",
		"KA50_MFD_MODE_WEAPON",
		"KA50_MFD_MODE_SYSTEM",
		"KA50_MFD_MODE_ENGINE",
		"KA50_MFD_MODE_FLIGHT",
		"KA50_MFD_MODE_MISSION",
	};

static char
	*ka50_mfd_location_names[NUM_KA50_MFD_LOCATIONS] =
	{
		"KA50_MFD_LOCATION_SHKVAL",
		"KA50_MFD_LOCATION_ABRIS",
	};

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static ka50_mfd_modes
	shkval_mfd_mode			= KA50_MFD_MODE_OFF,
	abris_mfd_mode			= KA50_MFD_MODE_OFF;

static ka50_mfd_modes
	*mfd_mode_ptrs[NUM_KA50_MFD_LOCATIONS] =
	{
		&shkval_mfd_mode,						// KA50_MFD_LOCATION_SHKVAL
		&abris_mfd_mode,						// KA50_MFD_LOCATION_ABRIS
	};

#ifndef OGRE_EE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static rgb_colour
	mfd_colours[20];

#define MFD_COLOUR1 		  	(mfd_colours[0])
#define MFD_COLOUR2 		  	(mfd_colours[1])
#define MFD_COLOUR3 		  	(mfd_colours[2])
#define MFD_COLOUR4	  	  		(mfd_colours[3])
#define MFD_COLOUR5				(mfd_colours[4])
#define MFD_COLOUR6				(mfd_colours[5])
#define MFD_CONTOUR_COLOUR		(mfd_colours[6])
#define MFD_RIVER_COLOUR		(mfd_colours[7])
#define MFD_ROAD_COLOUR			(mfd_colours[8])
#define MFD_BACKGROUND_COLOUR	(mfd_colours[9])
#define MFD_CLEAR_COLOUR		(mfd_colours[10])
#define MFD_COLOUR7				(mfd_colours[11])
#define MFD_COLOUR8				(mfd_colours[12])
#define MFD_COLOUR_GREEN		(mfd_colours[13])
#define MFD_COLOUR_DARK_GREEN	(mfd_colours[14])
#define MFD_COLOUR_YELLOW    	(mfd_colours[15])
#define MFD_COLOUR_LIGHT_BLUE	(mfd_colours[16])
#define MFD_COLOUR_BLUE      	(mfd_colours[17])
#define MFD_COLOUR_RED 			(mfd_colours[18])

static rgb_colour
   clear_mfd_colour;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static rgb_colour
	text_display_colours[2];

#define TEXT_COLOUR1			(text_display_colours[0])
#define TEXT_BACKGROUND_COLOUR	(text_display_colours[1])

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_GUN_SHAKE_DEFLECTION  rad(0.1)

#define MFD_WINDOW_X_MIN				(-1.0)
#define MFD_WINDOW_Y_MIN				(-1.0)
#define MFD_WINDOW_X_MAX				(0.999)
#define MFD_WINDOW_Y_MAX				(0.999)

#define LARGE_MFD_VIEWPORT_SIZE		(256)
#define SMALL_MFD_VIEWPORT_SIZE		(128)

static env_2d
	*mfd_env;

static int
	int_mfd_viewport_size;

static float
	mfd_viewport_size,
	mfd_viewport_x_org,
	mfd_viewport_y_org,
	mfd_viewport_x_min,
	mfd_viewport_y_min,
	mfd_viewport_x_max,
	mfd_viewport_y_max,
	mfd_screen_x_min,
	mfd_screen_y_min,
	mfd_screen_x_max,
	mfd_screen_y_max,
	mfd_screen_width,
	mfd_screen_height,
	mfd_screen_x_scale,
	mfd_screen_y_scale;

static int
	draw_large_mfd;

static screen
	*shkval_mfd_texture_screen,
	*abris_mfd_texture_screen,
	*ekran_display_texture_screen,
	*cannon_rounds_display_screen,
	*large_shkval_mfd_texture_screen,
	*large_abris_mfd_texture_screen,
	*large_ekran_display_texture_screen,
	*small_shkval_mfd_texture_screen,
	*small_abris_mfd_texture_screen,
	*small_ekran_display_texture_screen,
	*cannon_rounds_display_texture_screen,
	*eo_3d_texture_screen,
	*eo_3d_texture_screen_over,
	*full_mfd_texture_screen;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define TEXT_DISPLAY_MAX_STRING_LENGTH	 (10)
#define CANNON_DISPLAY_MAX_STRING_LENGTH (3)

static char
	text_display_line1[TEXT_DISPLAY_MAX_STRING_LENGTH + 1],
	text_display_line2[TEXT_DISPLAY_MAX_STRING_LENGTH + 1],
	text_display_line3[TEXT_DISPLAY_MAX_STRING_LENGTH + 1],
	text_display_line4[TEXT_DISPLAY_MAX_STRING_LENGTH + 1], //  Javelin  7/19
	text_display_line5[TEXT_DISPLAY_MAX_STRING_LENGTH + 1];

static char
	cannon_rounds[CANNON_DISPLAY_MAX_STRING_LENGTH +1];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//
// HEADING SCALE
//
////////////////////////////////////////

static char small_command_heading_carat[] =
{
	7,
	4,
	-3,
	0,
	0,0,0,1,0,0,0,
	0,0,1,0,1,0,0,
	0,1,0,0,0,1,0,
	1,0,0,0,0,0,1,
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ 030423 TSD render mod, added display_on_tsd
static void draw_radar_target_symbol (entity *target, vec3d *source_position, float scale, int selected_target, int display_on_tsd)
{
	target_symbol_types
		target_symbol_type;

	rgb_colour
		target_symbol_colour;

//VJ 030423 TSD render mod
	entity_sides
		source_side;
	entity
		*source;

	float
		dx,
		dy;

	vec3d
		*target_position;

	ASSERT (target);

	ASSERT (source_position);

	ASSERT (!get_local_entity_int_value (target, INT_TYPE_GROUND_RADAR_CLUTTER));

//VJ 030423 TSD render mod
	source = get_gunship_entity ();
	source_side = (entity_sides) get_local_entity_int_value (source, INT_TYPE_SIDE);

	target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

	dx = (target_position->x - source_position->x) * scale;
	dy = (target_position->z - source_position->z) * scale;

	target_symbol_type = (target_symbol_types) get_local_entity_int_value (target, INT_TYPE_TARGET_SYMBOL_TYPE);

	ASSERT ((target_symbol_type >= 0) && (target_symbol_type < NUM_TARGET_SYMBOL_TYPES));

	if (get_local_entity_index (target) & 1)
	{
//VJ 030423 TSD render mod
		if (display_on_tsd)
		{
			//VJ 030511 TSD render mod, treat enemy colours as cheat
			if (command_line_tsd_enemy_colours)
			{
				if (source_side == get_local_entity_int_value (target, INT_TYPE_SIDE))
					target_symbol_colour = MFD_COLOUR_YELLOW;
				else
					target_symbol_colour = MFD_COLOUR_RED;
			}
			else
			{
					target_symbol_colour = MFD_COLOUR_RED;
			}
		}
		else
			target_symbol_colour = MFD_COLOUR_RED;
	}
	else
	{
//VJ 030423 TSD render mod
		if (display_on_tsd)
		{
			//VJ 030511 TSD render mod, treat enemy colours as cheat
			if (command_line_tsd_enemy_colours)
			{
				if (source_side == get_local_entity_int_value (target, INT_TYPE_SIDE))
					target_symbol_colour = MFD_COLOUR_YELLOW;
				else
					target_symbol_colour = MFD_COLOUR_RED;
			}
			else
			{
					target_symbol_colour = MFD_COLOUR_RED;
			}
		}
		else
			target_symbol_colour = MFD_COLOUR_RED;
	}

	if (draw_large_mfd)
	{
		if (get_local_entity_int_value (target, INT_TYPE_GUNSHIP_RADAR_LOS_CLEAR))
		{
			if (selected_target)
			{
//VJ 030423 TSD render mod
				if (display_on_tsd)
					draw_2d_mono_sprite (large_display_target_symbols_los_mask[target_symbol_type], dx, dy, clear_mfd_colour);
				else
					draw_2d_mono_sprite (large_display_target_symbols_los_mask[target_symbol_type], dx, dy, MFD_COLOUR6);
			}

			draw_2d_mono_sprite (large_display_target_symbols_los[target_symbol_type], dx, dy, target_symbol_colour);
		}
		else
		{
			if (selected_target)
			{
//VJ 030423 TSD render mod
				if (display_on_tsd)
					draw_2d_mono_sprite (large_display_target_symbols_no_los_mask[target_symbol_type], dx, dy, clear_mfd_colour);
				else
					draw_2d_mono_sprite (large_display_target_symbols_no_los_mask[target_symbol_type], dx, dy, MFD_COLOUR6);
			}

			draw_2d_mono_sprite (large_display_target_symbols_no_los[target_symbol_type], dx, dy, target_symbol_colour);
		}

		if (selected_target)
		{
//VJ 030423 TSD render mod
			if (display_on_tsd)
				draw_2d_mono_sprite (large_display_target_symbol_selected_target_mask, dx, dy, clear_mfd_colour);
			else
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
//VJ 030423 TSD render mod
				if (display_on_tsd)
					draw_2d_mono_sprite (small_display_target_symbols_los_mask[target_symbol_type], dx, dy, clear_mfd_colour);
				else
					draw_2d_mono_sprite (small_display_target_symbols_los_mask[target_symbol_type], dx, dy, MFD_COLOUR6);
			}

			draw_2d_mono_sprite (small_display_target_symbols_los[target_symbol_type], dx, dy, target_symbol_colour);
		}
		else
		{
			if (selected_target)
			{
//VJ 030423 TSD render mod
				if (display_on_tsd)
					draw_2d_mono_sprite (small_display_target_symbols_no_los_mask[target_symbol_type], dx, dy, clear_mfd_colour);
				else
					draw_2d_mono_sprite (small_display_target_symbols_no_los_mask[target_symbol_type], dx, dy, MFD_COLOUR6);
			}

			draw_2d_mono_sprite (small_display_target_symbols_no_los[target_symbol_type], dx, dy, target_symbol_colour);
		}

		if (selected_target)
		{
//VJ 030423 TSD render mod
			if (display_on_tsd)
				draw_2d_mono_sprite (small_display_target_symbol_selected_target_mask, dx, dy, clear_mfd_colour);
			else
				draw_2d_mono_sprite (small_display_target_symbol_selected_target_mask, dx, dy, MFD_COLOUR6);

			draw_2d_mono_sprite (small_display_target_symbol_selected_target, dx, dy, target_symbol_colour);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//
// EO
//
////////////////////////////////////////

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

static char adv_azimuth_marker[] =
{
	7,
	8,
	-3,
	1,
	0,0,0,1,0,0,0,
	0,0,1,1,1,0,0,
	0,1,0,0,0,1,0,
	1,0,0,0,0,0,1,
	1,0,0,0,0,0,1,
	1,0,0,0,0,0,1,
	1,0,0,0,0,0,1,
	1,1,1,1,1,1,1,
};

static char adv_elevation_marker[] =
{
	8,
	7,
	1,
	-3,
	0,0,0,1,1,1,1,1,
	0,0,1,0,0,0,0,1,
	0,1,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	0,1,0,0,0,0,0,1,
	0,0,1,0,0,0,0,1,
	0,0,0,1,1,1,1,1,
};

static char adv_altitude_marker[] =
{
	8,
	7,
	-8,
	-3,
	1,1,1,1,1,0,0,0,
	1,0,0,0,0,1,0,0,
	1,0,0,0,0,0,1,0,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,1,0,
	1,0,0,0,0,1,0,0,
	1,1,1,1,1,0,0,0,
};

static char tg_symbol[]=
{
	19,
	8,
	-9,
	-8,
	1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,
	0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,
	0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,
	0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,
	0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,
	0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,
	0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,
	0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,
};

static char ta_symbol[]=
{
	19,
	8,
	-9,
	-8,
	1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,
	0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
	0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,
	0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,
	0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,
	0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,
	0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,
	0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

////////////////////////////////////////
//
// TSD and ASE
//
////////////////////////////////////////

#define TSD_ASE_RANGE_2000		((float) 2000.0)
#define TSD_ASE_RANGE_5000		((float) 5000.0)
#define TSD_ASE_RANGE_10000	((float) 10000.0)
#define TSD_ASE_RANGE_25000	((float) 25000.0)

static float
	tsd_ase_range;

enum TSD_DECLUTTER_LEVELS
{
	TSD_DECLUTTER_LEVEL_ALL,
	TSD_DECLUTTER_LEVEL_TARGET,
	TSD_DECLUTTER_LEVEL_NAVIGATION,
	NUM_TSD_DECLUTTER_LEVELS
};

typedef enum TSD_DECLUTTER_LEVELS tsd_declutter_levels;

static tsd_declutter_levels
	tsd_declutter_level;

#ifndef OGRE_EE
#define TSD_THREAT_LINE_FLASH_RATE	(0.1)

static float
	tsd_threat_line_flash_timer;

static int
	tsd_draw_threat_line_status;

#define ASE_THREAT_LINE_FLASH_RATE	(0.1)

static float
	ase_threat_line_flash_timer;

static int
	ase_draw_threat_line_status;

static char
	*main_horizon_mask = NULL;

static char
	large_tsd_ase_aircraft_datum[] =
	{
		17,
		37,
		-8,
		-18,
		0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,
		0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,
		0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,
		0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,
		0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,
		0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,
		0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,
		0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,
		0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,
		0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
		0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,
		0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,
		0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,
		0,0,0,0,1,0,0,1,0,1,0,0,1,0,0,0,0,
		0,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,
		0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,
	};

static char
	large_tsd_ase_aircraft_datum_mask[] =
	{
		19,
		39,
		-9,
		-19,
		0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,
		0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,
		0,0,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,
		0,0,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,
		0,0,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,0,0,
		0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,
		0,0,0,1,0,1,0,0,0,1,0,0,0,1,0,1,0,0,0,
		0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,
		0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,0,
		0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,0,
		0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,
		0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,
		1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
		1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,
		0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,
		0,0,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,0,0,
		0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,1,0,1,1,1,0,1,0,0,0,0,0,0,
		0,0,0,0,0,1,0,1,1,0,1,1,0,1,0,0,0,0,0,
		0,0,0,0,1,0,1,1,0,1,0,1,1,0,1,0,0,0,0,
		0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,
		0,0,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,
		0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,
	};

static char
	small_tsd_ase_aircraft_datum[] =
	{
		7,
		15,
		-3,
		-7,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,1,0,1,0,0,
		0,0,1,0,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		1,0,0,0,0,0,1,
		1,1,1,1,1,1,1,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,1,0,1,0,0,
		0,1,0,0,0,1,0,
	};

static char
	small_tsd_ase_aircraft_datum_mask[] =
	{
		9,
		17,
		-4,
		-8,
		0,0,0,0,1,0,0,0,0,
		0,0,0,1,0,1,0,0,0,
		0,0,0,1,0,1,0,0,0,
		0,0,0,1,0,1,0,0,0,
		0,0,0,1,0,1,0,0,0,
		0,0,0,1,0,1,0,0,0,
		0,0,1,0,1,0,1,0,0,
		0,0,1,0,1,0,1,0,0,
		0,1,0,1,0,1,0,1,0,
		0,1,0,1,0,1,0,1,0,
		1,0,1,1,1,1,1,0,1,
		1,0,0,0,0,0,0,0,1,
		1,1,1,1,0,1,1,1,1,
		0,0,0,1,0,1,0,0,0,
		0,0,1,0,1,0,1,0,0,
		0,1,0,1,0,1,0,1,0,
		0,0,1,0,0,0,1,0,0,
	};

static char
	large_tsd_waypoint_marker[] =
	{
		12,
		13,
		-5,
		-6,
		0,0,0,1,1,1,1,1,1,0,0,0,
		0,0,1,1,1,1,1,1,1,1,0,0,
		0,1,1,1,1,1,1,1,1,1,1,0,
		1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,
		0,1,1,1,1,1,1,1,1,1,1,0,
		0,0,1,1,1,1,1,1,1,1,0,0,
		0,0,0,1,1,1,1,1,1,0,0,0,
	};

static char
	small_tsd_waypoint_marker[] =
	{
		9,
		9,
		-4,
		-4,
		0,0,1,1,1,1,1,0,0,
		0,1,1,1,1,1,1,1,0,
		1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,
		0,1,1,1,1,1,1,1,0,
		0,0,1,1,1,1,1,0,0,
	};

static char
	large_ase_missile[] =
	{
		11,
		9,
		-5,
		-4,
		1,1,0,0,0,0,0,0,0,1,1,
		0,1,1,0,0,0,0,0,1,1,0,
		0,0,1,1,0,0,0,1,1,0,0,
		0,0,0,1,1,0,1,1,0,0,0,
		0,0,0,0,1,1,1,0,0,0,0,
		0,0,0,1,1,0,1,1,0,0,0,
		0,0,1,1,0,0,0,1,1,0,0,
		0,1,1,0,0,0,0,0,1,1,0,
		1,1,0,0,0,0,0,0,0,1,1,
	};

static char
	large_ase_missile_mask[] =
	{
		13,
		11,
		-6,
		-5,
		1,1,1,0,0,0,0,0,0,0,1,1,1,
		1,0,0,1,0,0,0,0,0,1,0,0,1,
		0,1,0,0,1,0,0,0,1,0,0,1,0,
		0,0,1,0,0,1,0,1,0,0,1,0,0,
		0,0,0,1,0,0,1,0,0,1,0,0,0,
		0,0,0,0,1,0,0,0,1,0,0,0,0,
		0,0,0,1,0,0,1,0,0,1,0,0,0,
		0,0,1,0,0,1,0,1,0,0,1,0,0,
		0,1,0,0,1,0,0,0,1,0,0,1,0,
		1,0,0,1,0,0,0,0,0,1,0,0,1,
		1,1,1,0,0,0,0,0,0,0,1,1,1,
	};

static char
	small_ase_missile[] =
	{
		7,
		5,
		-3,
		-2,
		1,1,0,0,0,1,1,
		0,1,1,0,1,1,0,
		0,0,1,1,1,0,0,
		0,1,1,0,1,1,0,
		1,1,0,0,0,1,1,
	};

static char
	small_ase_missile_mask[] =
	{
		9,
		7,
		-4,
		-3,
		1,1,1,0,0,0,1,1,1,
		1,0,0,1,0,1,0,0,1,
		0,1,0,0,1,0,0,1,0,
		0,0,1,0,0,0,1,0,0,
		0,1,0,0,1,0,0,1,0,
		1,0,0,1,0,1,0,0,1,
		1,1,1,0,0,0,1,1,1,
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static ka50_mfd_modes get_mfd_mode_for_eo_sensor (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void transform_mfd_screen_co_ords_to_mfd_texture_co_ords (float *i, float *j)
{
	ASSERT (i);
	ASSERT (j);

	*i -= mfd_screen_x_min;
	*j -= mfd_screen_y_min;

	*i *= mfd_screen_x_scale;
	*j *= mfd_screen_y_scale;
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
		col.g = (i >> 1) + 64;

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

static void draw_overlaid_damaged_mfd (void)
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
// HEADING SCALE
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
		if (!ka50_damage.navigation_computer)
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

				draw_mono_sprite (small_command_heading_carat, i, j + 1.0, MFD_COLOUR1);
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// EO
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define FULL_SCREEN_EO_RATIO	((float) (0.9))

////////////////////////////////////////
//
// FLIR									//  Javelin  7/19
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

static int get_undamaged_eo_display_mode (ka50_mfd_modes mode)
{
	if ((mode == KA50_MFD_MODE_FLIR) && (!ka50_damage.flir))		//  Javelin  7/19
	{
		return (TRUE);
	}

	if ((mode == KA50_MFD_MODE_LLLTV) && (!ka50_damage.llltv))
	{
		return (TRUE);
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef OLD_EO
static void draw_3d_eo_display (eo_params *eo, target_acquisition_systems system)
#else
static void draw_3d_eo_display (eo_params_dynamic_move *eo, target_acquisition_systems system)
#endif
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

#ifdef OLD_EO
	switch (eo->field_of_view)			//  Javelin  7/19
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
			//debug_fatal ("Invalid 3D field of view = %d", eo->field_of_view);
			eo->field_of_view = EO_FOV_WIDE;
			zoom = 0.3;

			break;
		}
	}
#else
	zoom = convert_linear_view_value (eo);
#endif

	position = get_local_entity_vec3d_ptr (get_gunship_entity (), VEC3D_TYPE_POSITION);

	weather_mode = get_simple_session_weather_at_point (position);

	ASSERT ((weather_mode > WEATHERMODE_INVALID) && (weather_mode < WEATHERMODE_LAST));

	day_segment_type = (day_segment_types) get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE);

	ASSERT ((day_segment_type >= 0) && (day_segment_type < NUM_DAY_SEGMENT_TYPES));

	switch (system)
	{
		case TARGET_ACQUISITION_SYSTEM_FLIR:		//  Javelin  7/19
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

	set_main_3d_params (tint, light_level, noise_level, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_size, mfd_viewport_size, rad (59.99) * zoom, rad (44.99) * zoom);

	//
	// draw 3D scene (temporarily adjust the virtual cockpit position relative to EO sensor position)
	//

	{
		vec3d
			position;

		viewpoint
			centered_eo_vp,
			rotated_eo_vp,
			tmp_vp;

		matrix3x3
			m;

		tmp_vp = virtual_cockpit_inst3d->vp;

		get_ka50_eo_relative_centred_viewpoint (&centered_eo_vp);

		rotated_eo_vp.position = centered_eo_vp.position;

		if (gun_is_firing)
			get_3d_transformation_matrix (m, eo_azimuth + sfrand1norm() * MAX_GUN_SHAKE_DEFLECTION, eo_elevation + sfrand1norm() * MAX_GUN_SHAKE_DEFLECTION, 0.0);
		else
			get_3d_transformation_matrix (m, eo_azimuth, eo_elevation, 0.0);

		multiply_matrix3x3_matrix3x3 (rotated_eo_vp.attitude, m, centered_eo_vp.attitude);

		position.x = -rotated_eo_vp.x;
		position.y = -rotated_eo_vp.y;
		position.z = -rotated_eo_vp.z;

		multiply_transpose_matrix3x3_vec3d (&virtual_cockpit_inst3d->vp.position, rotated_eo_vp.attitude, &position);

		get_local_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &position);

		rotated_eo_vp.x += position.x;
		rotated_eo_vp.y += position.y;
		rotated_eo_vp.z += position.z;

		draw_eo_3d_scene = TRUE;

		draw_main_3d_scene (&rotated_eo_vp);

		draw_eo_3d_scene = FALSE;

		virtual_cockpit_inst3d->vp = tmp_vp;
	}

//	if ( active_3d_environment->render_filter == RENDER_INFRARED )
//	{
//		DWORD
//			dwTFactor;
//
//		dwTFactor = ( 0xFF << 24 ) | (80 << 16) | (80 << 8) | 80;
//		f3d_set_texture_state(0, D3DTSS_COLOROP,D3DTOP_DOTPRODUCT3);
//		f3d_set_texture_state(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
//		f3d_set_texture_state(0, D3DTSS_COLORARG2, D3DTA_TFACTOR );
//		f3d_render_state ( D3DRENDERSTATE_TEXTUREFACTOR, dwTFactor );
//	}

	finalise_3d_render_target_texture (eo_3d_texture_screen);

	set_3d_render_target (video_screen);

	set_active_screen (video_screen);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef OLD_EO
static void draw_full_screen_3d_eo_display (eo_params *eo, target_acquisition_systems system, display_3d_tints tint)
#else
static void draw_full_screen_3d_eo_display (eo_params_dynamic_move *eo, target_acquisition_systems system, display_3d_tints tint)
#endif
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

#ifdef OLD_EO
	switch (eo->field_of_view)			//  Javelin  7/19
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
			debug_fatal ("Invalid full-3D field of view = %d", eo->field_of_view);

			break;
		}
	}
#else
	zoom = convert_linear_view_value (eo);
#endif

	position = get_local_entity_vec3d_ptr (get_gunship_entity (), VEC3D_TYPE_POSITION);

	weather_mode = get_simple_session_weather_at_point (position);

	ASSERT ((weather_mode > WEATHERMODE_INVALID) && (weather_mode < WEATHERMODE_LAST));

	day_segment_type = (day_segment_types) get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE);

	ASSERT ((day_segment_type >= 0) && (day_segment_type < NUM_DAY_SEGMENT_TYPES));

	switch (system)
	{
		case TARGET_ACQUISITION_SYSTEM_FLIR:		//  Javelin  7/19
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

	set_main_3d_params
	(
		tint,
		light_level,
		noise_level,
		mfd_screen_x_min,
		mfd_screen_y_min,
		mfd_screen_width,
		mfd_screen_height,
		rad (59.99) * zoom,
		rad (44.99) * zoom
	);

	//
	// draw 3D scene (temporarily adjust the virtual cockpit position relative to EO sensor position)
	//

	{
		vec3d
			position;

		viewpoint
			centered_eo_vp,
			rotated_eo_vp,
			tmp_vp;

		matrix3x3
			m;

		tmp_vp = virtual_cockpit_inst3d->vp;

		get_ka50_eo_relative_centred_viewpoint (&centered_eo_vp);

		rotated_eo_vp.position = centered_eo_vp.position;

		get_3d_transformation_matrix (m, eo_azimuth, eo_elevation, 0.0);

		multiply_matrix3x3_matrix3x3 (rotated_eo_vp.attitude, m, centered_eo_vp.attitude);

		position.x = -rotated_eo_vp.x;
		position.y = -rotated_eo_vp.y;
		position.z = -rotated_eo_vp.z;

		multiply_transpose_matrix3x3_vec3d (&virtual_cockpit_inst3d->vp.position, rotated_eo_vp.attitude, &position);

		get_local_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &position);

		rotated_eo_vp.x += position.x;
		rotated_eo_vp.y += position.y;
		rotated_eo_vp.z += position.z;

		draw_eo_3d_scene = TRUE;

		draw_main_3d_scene (&rotated_eo_vp);

		draw_eo_3d_scene = FALSE;

		virtual_cockpit_inst3d->vp = tmp_vp;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef OLD_EO
static void draw_2d_eo_display (eo_params *eo, target_acquisition_systems system, int damaged, int valid_3d)
#else
static void draw_2d_eo_display (eo_params_dynamic_move *eo, target_acquisition_systems system, int damaged, int valid_3d)
#endif
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

	has_range = get_range_finder() != RANGEFINDER_TRIANGULATION;

	if (has_range)
		target_range = get_range_to_target();

	////////////////////////////////////////
	//
	// text
	//
	////////////////////////////////////////

	set_mono_font_colour (MFD_COLOUR_GREEN);

	if (draw_large_mfd)
	{
		set_mono_font_type (MONO_FONT_TYPE_7X12);
	}
	else
	{
		set_mono_font_type (MONO_FONT_TYPE_5X7);
	}

	//
	// sensor type
	//

	if (draw_large_mfd)
	{
		y_adjust = 5.0;
	}
	else
	{
		y_adjust = 2.0;
	}

	set_2d_mono_font_position (-1.0, 1.0);

	set_mono_font_rel_position (1.0, y_adjust);

	switch (system)
	{
		case TARGET_ACQUISITION_SYSTEM_FLIR:		//  Javelin  7/19
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
		if (draw_large_mfd)
		{
			y_adjust = 18.0;
		}
		else
		{
			y_adjust = 9.0;
		}

		set_2d_mono_font_position (-1.0, 1.0);

		set_mono_font_rel_position (1.0, y_adjust);

		if (draw_large_mfd)
		{
			print_mono_font_string ("LO LIGHT");
		}
		else
		{
			print_mono_font_string ("LO");
		}
	}

	//
	// field of view
	//

	{
		float level;

#ifdef OLD_EO
		switch (eo->field_of_view)			//  Javelin  7/19
		{
			case EO_FOV_NARROW:
			{
				level = 21;

				break;
			}
			case EO_FOV_MEDIUM:
			{
				level = 7;

				break;
			}
			case EO_FOV_WIDE:
			{
				level = 3;

				break;
			}
			default:
			{
				debug_fatal ("Invalid LEVEL field of view = %d", eo->field_of_view);

				break;
			}
		}
#else
		level = 1.0 / convert_linear_view_value (eo);
#endif

		sprintf (buffer, "%d", (int)level);

		s = buffer;
	}

	width = get_mono_font_string_width (s);

	if (draw_large_mfd)
	{
		width += 2.0;

		y_adjust = 5.0;
	}
	else
	{
		width += 1.0;

		y_adjust = 2.0;
	}

	set_2d_mono_font_position (1.0, 1.0);

	set_mono_font_rel_position (-width, y_adjust);

	print_mono_font_string (s);

	//
	// target name
	//

	if (draw_large_mfd)
	{
		y_adjust = -12.0;
	}
	else
	{
		y_adjust = -5.0;
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
		if ((target_range < 1000.0) && (!ka50_damage.laser_designator))
		{
			sprintf (buffer, "%dm", (int) target_range);
		}
		else
		{
			sprintf (buffer, "%.1fKm", target_range * (1.0 / 1000.0));
		}

		width = get_mono_font_string_width (buffer);

		set_2d_mono_font_position (1.0, -1.0);

		if (draw_large_mfd)
		{
			width += 2.0;
		}
		else
		{
			width += 1.0;
		}

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
			y_adjust = -25.0;
		}
		else
		{
			y_adjust = -12.0;
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
		draw_2d_line (-0.075, 0.0, -0.025, 0.0, MFD_COLOUR_GREEN);

		draw_2d_line (0.035, 0.0, 0.08, 0.0, MFD_COLOUR_GREEN);

		draw_2d_line (0.0, -0.075, 0.0, -0.025, MFD_COLOUR_GREEN);

		draw_2d_line (0.0, 0.035, 0.0, 0.08, MFD_COLOUR_GREEN);
	}
	else
	{
		draw_2d_line (-0.075, 0.0, -0.025, 0.0, MFD_COLOUR_GREEN);

		draw_2d_line (0.035, 0.0, 0.09, 0.0, MFD_COLOUR_GREEN);

		draw_2d_line (0.0, -0.075, 0.0, -0.025, MFD_COLOUR_GREEN);

		draw_2d_line (0.0, 0.035, 0.0, 0.09, MFD_COLOUR_GREEN);
	}

	//
	// azimuth
	//

	draw_2d_line (-0.5, 0.8, 0.5, 0.8, MFD_COLOUR_GREEN);

	marker_position = (eo_azimuth / eo_max_azimuth) * 0.5;

	if (draw_large_mfd)
	{
		draw_2d_line (-0.5, 0.8 - 0.02, -0.5, 0.8 + 0.02, MFD_COLOUR_GREEN);

		draw_2d_line (0.5, 0.8 - 0.02, 0.5, 0.8 + 0.02, MFD_COLOUR_GREEN);

		draw_2d_line (0.0, 0.8 - 0.01, 0.0, 0.8 + 0.01, MFD_COLOUR_GREEN);

		draw_2d_mono_sprite (large_azimuth_marker, marker_position, 0.8, MFD_COLOUR_GREEN);
	}
	else
	{
		draw_2d_line (-0.5, 0.8 - 0.03, -0.5, 0.8 + 0.03, MFD_COLOUR_GREEN);

		draw_2d_line (0.5, 0.8 - 0.03, 0.5, 0.8 + 0.03, MFD_COLOUR_GREEN);

		draw_2d_line (0.0, 0.8 - 0.02, 0.0, 0.8 + 0.02, MFD_COLOUR_GREEN);

		draw_2d_mono_sprite (small_azimuth_marker, marker_position, 0.8, MFD_COLOUR_GREEN);
	}

	//
	// elevation
	//

	draw_2d_line (-0.9, 0.4, -0.9, -0.3, MFD_COLOUR_GREEN);

	if (eo_elevation < 0.0)
	{
		marker_position = (eo_elevation / eo_min_elevation) * -0.3;
	}
	else
	{
		marker_position = (eo_elevation / eo_max_elevation) * 0.4;
	}

	if (draw_large_mfd)
	{
		draw_2d_line (-0.9 - 0.02, 0.4, -0.9 + 0.02, 0.4, MFD_COLOUR_GREEN);

		draw_2d_line (-0.9 - 0.02, -0.3, -0.9 + 0.02, -0.3, MFD_COLOUR_GREEN);

		draw_2d_line (-0.9 - 0.01, 0.0, -0.9 + 0.01, 0.0, MFD_COLOUR_GREEN);

		draw_2d_mono_sprite (large_elevation_marker, -0.9, marker_position, MFD_COLOUR_GREEN);
	}
	else
	{
		draw_2d_line (-0.9 - 0.03, 0.2, -0.9 + 0.03, 0.2, MFD_COLOUR_GREEN);

		draw_2d_line (-0.9 - 0.03, -0.6, -0.9 + 0.03, -0.6, MFD_COLOUR_GREEN);

		draw_2d_line (-0.9 - 0.02, 0.0, -0.9 + 0.02, 0.0, MFD_COLOUR_GREEN);

		draw_2d_mono_sprite (small_elevation_marker, -0.9, marker_position, MFD_COLOUR_GREEN);
	}

	//
	// range
	//

	draw_2d_line (0.9, 0.0, 0.9, -0.5, MFD_COLOUR_GREEN);

	if (draw_large_mfd)
	{
		draw_2d_line (0.9,  0.000, 0.9 + 0.02,  0.000, MFD_COLOUR_GREEN);
		draw_2d_line (0.9, -0.025, 0.9 + 0.01, -0.025, MFD_COLOUR_GREEN);
		draw_2d_line (0.9, -0.050, 0.9 + 0.01, -0.050, MFD_COLOUR_GREEN);
		draw_2d_line (0.9, -0.075, 0.9 + 0.01, -0.075, MFD_COLOUR_GREEN);

		draw_2d_line (0.9, -0.100, 0.9 + 0.02, -0.100, MFD_COLOUR_GREEN);
		draw_2d_line (0.9, -0.125, 0.9 + 0.01, -0.125, MFD_COLOUR_GREEN);
		draw_2d_line (0.9, -0.150, 0.9 + 0.01, -0.150, MFD_COLOUR_GREEN);
		draw_2d_line (0.9, -0.175, 0.9 + 0.01, -0.175, MFD_COLOUR_GREEN);

		draw_2d_line (0.9, -0.200, 0.9 + 0.02, -0.200, MFD_COLOUR_GREEN);
		draw_2d_line (0.9, -0.225, 0.9 + 0.01, -0.225, MFD_COLOUR_GREEN);
		draw_2d_line (0.9, -0.250, 0.9 + 0.01, -0.250, MFD_COLOUR_GREEN);
		draw_2d_line (0.9, -0.275, 0.9 + 0.01, -0.275, MFD_COLOUR_GREEN);

		draw_2d_line (0.9, -0.300, 0.9 + 0.02, -0.300, MFD_COLOUR_GREEN);

		draw_2d_line (0.9, -0.400, 0.9 + 0.02, -0.400, MFD_COLOUR_GREEN);

		draw_2d_line (0.9, -0.500, 0.9 + 0.02, -0.500, MFD_COLOUR_GREEN);
	}
	else
	{
		draw_2d_line (0.9,  0.000, 0.9 + 0.03,  0.000, MFD_COLOUR_GREEN);

		draw_2d_line (0.9, -0.100, 0.9 + 0.03, -0.100, MFD_COLOUR_GREEN);

		draw_2d_line (0.9, -0.200, 0.9 + 0.03, -0.200, MFD_COLOUR_GREEN);

		draw_2d_line (0.9, -0.300, 0.9 + 0.03, -0.300, MFD_COLOUR_GREEN);

		draw_2d_line (0.9, -0.400, 0.9 + 0.03, -0.400, MFD_COLOUR_GREEN);

		draw_2d_line (0.9, -0.500, 0.9 + 0.03, -0.500, MFD_COLOUR_GREEN);
	}

	if (target_range > 0.0)
	{
		marker_position = (min (target_range, eo_max_visual_range) / eo_max_visual_range) * -0.5;

		if (draw_large_mfd)
		{
			draw_2d_mono_sprite (large_range_marker, 0.9, marker_position, MFD_COLOUR_GREEN);
		}
		else
		{
			draw_2d_mono_sprite (small_range_marker, 0.9, marker_position, MFD_COLOUR_GREEN);
		}
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
					transform_mfd_screen_co_ords_to_mfd_texture_co_ords (&i, &j);

					get_2d_world_position (i, j, &x, &y);

					draw_2d_line (x - 0.20, y + 0.20, x - 0.15, y + 0.20, MFD_COLOUR_GREEN);
					draw_2d_line (x + 0.20, y + 0.20, x + 0.15, y + 0.20, MFD_COLOUR_GREEN);
					draw_2d_line (x - 0.20, y - 0.20, x - 0.15, y - 0.20, MFD_COLOUR_GREEN);
					draw_2d_line (x + 0.20, y - 0.20, x + 0.15, y - 0.20, MFD_COLOUR_GREEN);
					draw_2d_line (x - 0.20, y + 0.20, x - 0.20, y + 0.15, MFD_COLOUR_GREEN);
					draw_2d_line (x - 0.20, y - 0.20, x - 0.20, y - 0.15, MFD_COLOUR_GREEN);
					draw_2d_line (x + 0.20, y + 0.20, x + 0.20, y + 0.15, MFD_COLOUR_GREEN);
					draw_2d_line (x + 0.20, y - 0.20, x + 0.20, y - 0.15, MFD_COLOUR_GREEN);
				}

				main_vp = tmp;
			}
		}
	}
}


#ifdef OLD_EO
static void draw_adv_2d_eo_display (eo_params *eo, target_acquisition_systems system, int damaged, int valid_3d)
#else
static void draw_adv_2d_eo_display (eo_params_dynamic_move *eo, target_acquisition_systems system, int damaged, int valid_3d)
#endif
{
	int
		has_range,
		k;

	float
		width,
		marker_position,
		target_range = 0.0,
		y_adjust;

	entity
		*source,
		*target;

	vec3d
		*source_position;

	ASSERT (eo);

	//
	// damaged
	//

	if (damaged)
	{
		draw_2d_line (-0.5, -0.5,  0.5, 0.5, MFD_COLOUR1);
		draw_2d_line ( 0.5, -0.5, -0.5, 0.5, MFD_COLOUR1);

		return;
	}

	source = get_gunship_entity ();

	source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

	target = get_local_entity_parent (source, LIST_TYPE_TARGET);

	has_range = get_range_finder() != RANGEFINDER_TRIANGULATION;

	if (has_range)
		target_range = get_range_to_target();

	set_mono_font_colour (MFD_COLOUR2);
	set_mono_font_type (MONO_FONT_TYPE_7X12);

//	// damaged
//
//	if (damaged)
//	{
//		draw_2d_line (-0.5, -0.5,  0.5, 0.5, MFD_COLOUR1);
//		draw_2d_line ( 0.5, -0.5, -0.5, 0.5, MFD_COLOUR1);
//
//		return;
//	}

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

		set_mono_font_rel_position (-width - 1.0, y_adjust);

		print_mono_font_string ("MARKED");
	}
// Jabberwock 031107 ends

	// targeting mode

	if (eo_is_locked())
	{
		draw_2d_mono_sprite (ta_symbol, -0.25, 0.27, MFD_COLOUR2);
	}
	else if (eo_ground_stabilised)
	{
		draw_2d_mono_sprite (tg_symbol, 0.25, 0.27, MFD_COLOUR2);
	}

	// warnings

	if (current_flight_dynamics->radar_altitude.value < 10)
	{
		set_mono_font_type (MONO_FONT_TYPE_10X16);
		set_2d_mono_font_position (- 0.7, - 0.85);
		print_mono_font_string ("H");
	}

	if (current_flight_dynamics->velocity_z.value * current_flight_dynamics->velocity_z.modifier > 0.85 * current_flight_dynamics->velocity_z.max)
	{
		set_mono_font_type (MONO_FONT_TYPE_10X16);
		set_2d_mono_font_position (- 0.5, - 0.85);
		print_mono_font_string ("V");
	}

	// static markers

	draw_2d_line (-0.4, 0.3, -0.3, 0.3, MFD_COLOUR2); // top left
	draw_2d_line (-0.4, 0.3, -0.4, 0.2, MFD_COLOUR2); // top left
	draw_2d_line (-0.4, -0.3, -0.3, -0.3, MFD_COLOUR2); // bottom left
	draw_2d_line (-0.4, -0.3, -0.4, -0.2, MFD_COLOUR2); // bottom left
	draw_2d_line (0.4, 0.3, 0.3, 0.3, MFD_COLOUR2); // top right
	draw_2d_line (0.4, 0.3, 0.4, 0.2, MFD_COLOUR2); // top right
	draw_2d_line (0.4, -0.3, 0.3, -0.3, MFD_COLOUR2); // bottom right
	draw_2d_line (0.4, -0.3, 0.4, -0.2, MFD_COLOUR2); // bottom right

	draw_2d_line (-0.8, 0, -0.6, 0, MFD_COLOUR2); // center left
	draw_2d_line (0.6, 0, 0.8, 0, MFD_COLOUR2); // center right

	// target gates

	{
#ifdef OLD_EO
		float scale = 4 / ((float) pow(eo->field_of_view, 2.0f) + 1), x, y;
#else
		float scale = 4 * (int) (1 / eo->zoom / 64) + 1, x, y;
#endif

		if (eo_is_locked())
		{
			move_targeting_gates(&x, &y);
			set_2d_instance_position(mfd_env, x, y);
		}

		draw_2d_dash_line(- 0.1 * scale, 0.08 * scale, 0.1 * scale, 0.08 * scale, MFD_COLOUR2, MFD_COLOUR6, 0.02, TRUE);
		draw_2d_dash_line(- 0.1 * scale, - 0.08 * scale, 0.1 * scale, - 0.08 * scale, MFD_COLOUR2, MFD_COLOUR6, 0.02, TRUE);
		draw_2d_dash_line(- 0.1 * scale, 0.08 * scale, - 0.1 * scale, - 0.08 * scale, MFD_COLOUR2, MFD_COLOUR6, 0.02, TRUE);
		draw_2d_dash_line(0.1 * scale, 0.08 * scale, 0.1 * scale, - 0.08 * scale, MFD_COLOUR2, MFD_COLOUR6, 0.02, TRUE);
		draw_2d_dash_line(0.0, 0.0, 0.0, - 0.08 * scale, MFD_COLOUR2, MFD_COLOUR6, 0.02, TRUE);

		reset_2d_instance(mfd_env);
	}

	// azimuth

	marker_position = (eo_azimuth / eo_max_azimuth) * 0.48;

	draw_2d_line (-0.48, 0.8, 0.48, 0.8, MFD_COLOUR2);
	draw_2d_line (-0.48, 0.8 - 0.02, -0.48, 0.8 + 0.02, MFD_COLOUR2);
	draw_2d_line (0.48, 0.8 - 0.02, 0.48, 0.8 + 0.02, MFD_COLOUR2);
	draw_2d_line (0.0, 0.8 - 0.01, 0.0, 0.8 + 0.01, MFD_COLOUR2);

	draw_2d_mono_sprite (adv_azimuth_marker, marker_position, 0.8, MFD_COLOUR2);

	// elevation

	marker_position = 2 * 0.75 * (eo_elevation - eo_min_elevation) / (eo_max_elevation - eo_min_elevation);

	draw_2d_line (-0.93, 0.75, -0.93, -0.75, MFD_COLOUR2);
	draw_2d_line (-0.95, 0.75, -0.91, 0.75, MFD_COLOUR2);
	draw_2d_line (-0.95, -0.75, -0.91, -0.75, MFD_COLOUR2);
	draw_2d_line (-0.95, 0.51, -0.91, 0.51, MFD_COLOUR2);

	draw_2d_mono_sprite (adv_elevation_marker, -0.93, marker_position - 0.75, MFD_COLOUR2);

	// altitude

	draw_2d_line (0.92, -0.86, 0.92, -0.16, MFD_COLOUR2);
	draw_2d_line (0.89, -0.86, 0.95, -0.86, MFD_COLOUR2); // 0

	for (k = 0; k < 5; k++)
		draw_2d_line (0.92, -0.72 + 0.14 * k, 0.94, -0.72 + 0.14 * k, MFD_COLOUR2);

	marker_position = 0.7 * bound(current_flight_dynamics->radar_altitude.value, 0 , 50) / 50;
	draw_2d_mono_sprite (adv_altitude_marker, 0.92, -0.86 + marker_position, MFD_COLOUR2);

	// horizon

	set_2d_instance_rotation (mfd_env, current_flight_dynamics->roll.value);

	draw_2d_line (-0.6, 0, -0.45, 0, MFD_COLOUR2); // left
	draw_2d_line (-0.45, 0, -0.45, -0.02, MFD_COLOUR2); // left
	draw_2d_line (0.45, 0, 0.6, 0, MFD_COLOUR2); // right
	draw_2d_line (0.45, 0, 0.45, -0.02, MFD_COLOUR2); // right

	reset_2d_instance (mfd_env);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// FLIR													//  Javelin  7/19
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_3d_flir_mfd (int full_screen)			//  Javelin  7/19
{
	if (!ka50_damage.flir)
	{
		if (full_screen)
		{
			draw_full_screen_3d_eo_display (&ka50_flir, TARGET_ACQUISITION_SYSTEM_FLIR, DISPLAY_3D_TINT_FLIR);
		}
		else
		{
			draw_3d_eo_display (&ka50_flir, TARGET_ACQUISITION_SYSTEM_FLIR);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_2d_flir_mfd (int valid_3d)			//  Javelin  7/19
{
	if (command_line_advanced_mfd && command_line_colour_mfd && draw_large_mfd)
		draw_adv_2d_eo_display (&ka50_flir, TARGET_ACQUISITION_SYSTEM_FLIR, ka50_damage.flir, valid_3d);
	else
		draw_2d_eo_display (&ka50_flir, TARGET_ACQUISITION_SYSTEM_FLIR, ka50_damage.flir, valid_3d);
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

static void draw_3d_llltv_mfd (int full_screen)
{
	if (!ka50_damage.llltv)
	{
		if (full_screen)
		{
			draw_full_screen_3d_eo_display (&ka50_llltv, TARGET_ACQUISITION_SYSTEM_LLLTV, DISPLAY_3D_TINT_LLLTV);
		}
		else
		{
			draw_3d_eo_display (&ka50_llltv, TARGET_ACQUISITION_SYSTEM_LLLTV);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_2d_llltv_mfd (int valid_3d)
{
	if (command_line_advanced_mfd && command_line_colour_mfd && draw_large_mfd)
		draw_adv_2d_eo_display (&ka50_llltv, TARGET_ACQUISITION_SYSTEM_LLLTV, ka50_damage.llltv, valid_3d);
	else
		draw_2d_eo_display (&ka50_llltv, TARGET_ACQUISITION_SYSTEM_LLLTV, ka50_damage.llltv, valid_3d);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TSD
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// match ground radar radius
//

#define RADIUS	(ROOT2 - 0.05)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_tactical_situation_display_mfd (ka50_mfd_locations mfd_location)
{
	char
		*s,
		buffer[200];

	entity_sides
		source_side;

	float
		u,
		v,
		scale,
		x_origin,
		y_origin,
		width,
		y_adjust,
		source_heading;

	entity
		*source,
		*source_target;

	vec3d
		*source_position;

	ASSERT (ka50_mfd_location_valid (mfd_location));

	source = get_gunship_entity ();

	source_side = (entity_sides) get_local_entity_int_value (source, INT_TYPE_SIDE);

	source_heading = get_local_entity_float_value (source, FLOAT_TYPE_HEADING);

	source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

	source_target = get_local_entity_parent (source, LIST_TYPE_TARGET);

	scale = RADIUS / tsd_ase_range;

	//
	// match ground radar origin
	//

	if (draw_large_mfd)
	{
		x_origin = 0.0;
		y_origin = -0.6;
	}
	else
	{
		x_origin = 0.0;
		y_origin = -0.675;
	}

	get_2d_float_screen_coordinates (x_origin, y_origin, &u, &v);

	u -= mfd_viewport_x_min;
	v -= mfd_viewport_y_min;

	////////////////////////////////////////
	//
	//VJ 030423 TSD RENDER MOD
	//
	////////////////////////////////////////

	if (tsd_render_mode != TSD_RENDER_CONTOUR_MODE && !ka50_damage.navigation_computer)
	{
		//VJ 030423 TSD render mod
		set_rgb_colour (MFD_COLOUR1,   0, 0,  96, 255);  //dark blue
	   set_rgb_colour (MFD_COLOUR2,	32, 32,  164, 255); //light blue
		set_rgb_colour (MFD_COLOUR3, 220, 48,   0, 255); //bright red
		set_rgb_colour (MFD_COLOUR4, 148, 32,   0, 255);//dark red

		set_rgb_colour (MFD_COLOUR6,  255, 255,  0, 255);
		//VJ 030511 colours 7 and 8 are grays when enemy colour option is off in eech.ini
		//VJ 030530 colour tweaks: black and dark gray are best
		set_rgb_colour (MFD_COLOUR7,    64, 64, 64, 255);
		set_rgb_colour (MFD_COLOUR8,    0,   0,  0, 255);

	   draw_tsd_terrain_map (mfd_env, -y_origin, tsd_ase_range, scale, source_position, source_heading, FALSE);

		if (command_line_colour_mfd)
		{
		   	set_rgb_colour (MFD_COLOUR1,            255, 255, 255, 255);
			set_rgb_colour (MFD_COLOUR2,            200, 200, 200, 255);
			set_rgb_colour (MFD_COLOUR3,            176, 176, 176, 255);
			set_rgb_colour (MFD_COLOUR4,            151, 151, 151, 255);
			set_rgb_colour (MFD_COLOUR5,            128, 128, 128, 255);
			set_rgb_colour (MFD_COLOUR6,             40,  40,  40, 255);
		}
		else
		{
			set_rgb_colour (MFD_COLOUR1,            255, 135,   0, 255);
			set_rgb_colour (MFD_COLOUR2,            255,  90,   0, 255);
			set_rgb_colour (MFD_COLOUR3,            200,  65,   0, 255);
			set_rgb_colour (MFD_COLOUR4,            130,  50,   0, 255);
			set_rgb_colour (MFD_COLOUR5,            100,  50,   0, 255);
			set_rgb_colour (MFD_COLOUR6,             50,  25,   0, 255);
		}
	}

	////////////////////////////////////////
	//
	// contour map
	//
	////////////////////////////////////////

//VJ 030423 TSD render mod, added mfd_env
	if (!ka50_damage.navigation_computer)
		draw_tsd_contour_map (mfd_env, -y_origin, tsd_ase_range, scale, source_position, source_heading, draw_large_mfd, FALSE);

	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

	////////////////////////////////////////
	//
	// waypoint route
	//
	////////////////////////////////////////

	if (tsd_declutter_level != TSD_DECLUTTER_LEVEL_TARGET && !ka50_damage.navigation_computer)
	{
		entity
			*wp1,
			*wp2;

		vec3d
			wp1_rel_position,
			wp2_rel_position;

		wp1 = get_local_entity_first_waypoint (source);

		if (wp1)
		{
			set_2d_viewport_origin (mfd_env, u, v);

			set_2d_window_rotation (mfd_env, source_heading);

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
				{
					draw_2d_half_thick_line (wp1_rel_position.x, wp1_rel_position.z, wp2_rel_position.x, wp2_rel_position.z, MFD_COLOUR_BLUE);
				}
				else
				{
					draw_2d_line (wp1_rel_position.x, wp1_rel_position.z, wp2_rel_position.x, wp2_rel_position.z, MFD_COLOUR_BLUE);
				}

				wp1 = wp2;

				wp1_rel_position = wp2_rel_position;

				wp2 = get_local_entity_child_succ (wp1, LIST_TYPE_WAYPOINT);
			}

			//
			// waypoint markers
			//

			set_mono_font_colour (MFD_COLOUR2);

			if (draw_large_mfd)
			{
				set_mono_font_type (MONO_FONT_TYPE_7X12);
			}
			else
			{
				set_mono_font_type (MONO_FONT_TYPE_5X7);
			}

			wp1 = get_local_entity_first_waypoint (source);

			while (wp1)
			{
				get_waypoint_display_position (source, wp1, &wp1_rel_position);

				wp1_rel_position.x = (wp1_rel_position.x - source_position->x) * scale;
				wp1_rel_position.z = (wp1_rel_position.z - source_position->z) * scale;

				if (draw_large_mfd)
				{
					draw_2d_mono_sprite (large_tsd_waypoint_marker, wp1_rel_position.x, wp1_rel_position.z, MFD_COLOUR_BLUE);

					set_2d_mono_font_position (wp1_rel_position.x, wp1_rel_position.z);

					set_mono_font_rel_position (-2.0, -4.0);
				}
				else
				{
					draw_2d_mono_sprite (small_tsd_waypoint_marker, wp1_rel_position.x, wp1_rel_position.z, MFD_COLOUR_BLUE);

					set_2d_mono_font_position (wp1_rel_position.x, wp1_rel_position.z);

					set_mono_font_rel_position (-2.0, -2.0);
				}

				print_mono_font_char (get_local_entity_char_value (wp1, CHAR_TYPE_TAG));

				wp1 = get_local_entity_child_succ (wp1, LIST_TYPE_WAYPOINT);
			}

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_2d_window_rotation (mfd_env, 0.0);
		}
	}

	////////////////////////////////////////
	//
	// targets
	//
	////////////////////////////////////////

	{
		entity
			*target,
			*launched_weapon;

		vec3d
			*target_position;

		threat_types
			threat_type;

		int
			draw_threat_line;

		float
			air_scan_range,
			dx,
			dy;

		if (tsd_declutter_level != TSD_DECLUTTER_LEVEL_NAVIGATION)
		{
			tsd_threat_line_flash_timer -= get_delta_time ();

			if (tsd_threat_line_flash_timer < 0.0)
			{
				tsd_threat_line_flash_timer = TSD_THREAT_LINE_FLASH_RATE;

				tsd_draw_threat_line_status ^= 1;
			}

			set_2d_viewport_origin (mfd_env, u, v);

			set_2d_window_rotation (mfd_env, source_heading);

			//
			// display enemy SAM and AAA threat range circles
			//

			target = get_local_entity_first_child (source, LIST_TYPE_GUNSHIP_TARGET);

			while (target)
			{
				if (!get_local_entity_int_value (target, INT_TYPE_GROUND_RADAR_CLUTTER))
				{
					if (source_side != get_local_entity_int_value (target, INT_TYPE_SIDE))
					{
						threat_type = (threat_types) get_local_entity_int_value (target, INT_TYPE_THREAT_TYPE);

						if ((threat_type == THREAT_TYPE_SAM) || (threat_type == THREAT_TYPE_AAA))
						{
							target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

							dx = (target_position->x - source_position->x) * scale;
							dy = (target_position->z - source_position->z) * scale;

							air_scan_range = get_local_entity_float_value (target, FLOAT_TYPE_AIR_SCAN_RANGE) * scale;

							draw_2d_circle (dx, dy, air_scan_range, MFD_COLOUR_RED);

						}
					}
				}

				target = get_local_entity_child_succ (target, LIST_TYPE_GUNSHIP_TARGET);
			}

			//
			// display all gunship targets (do not show ground radar clutter)
			//

			target = get_local_entity_first_child (source, LIST_TYPE_GUNSHIP_TARGET);

			while (target)
			{
				if (!get_local_entity_int_value (target, INT_TYPE_GROUND_RADAR_CLUTTER))
				{
					//VJ 030423 TSD render mod
					if (tsd_render_mode == TSD_RENDER_CONTOUR_MODE)
						draw_radar_target_symbol (target, source_position, scale, FALSE, FALSE);
					else
						draw_radar_target_symbol (target, source_position, scale, FALSE, TRUE);
				}

				target = get_local_entity_child_succ (target, LIST_TYPE_GUNSHIP_TARGET);
			}

			//
			// draw selected target last
			//

			if (source_target)
			{
				//VJ 030423 TSD render mod
				if (tsd_render_mode == TSD_RENDER_CONTOUR_MODE)
					draw_radar_target_symbol (source_target, source_position, scale, TRUE, FALSE);
				else
					draw_radar_target_symbol (source_target, source_position, scale, TRUE, TRUE);
			}

			//
			// draw threat line if gunship is targetted (flash if missile fired)
			//

			target = get_local_entity_first_child (source, LIST_TYPE_GUNSHIP_TARGET);

			while (target)
			{
				if (!get_local_entity_int_value (target, INT_TYPE_GROUND_RADAR_CLUTTER))
				{
					if (source_side != get_local_entity_int_value (target, INT_TYPE_SIDE))
					{
						if (get_local_entity_int_value (target, INT_TYPE_RADAR_ON))
						{
							threat_type = (threat_types) get_local_entity_int_value (target, INT_TYPE_THREAT_TYPE);

							if ((threat_type == THREAT_TYPE_SAM) || (threat_type == THREAT_TYPE_AAA) || (threat_type == THREAT_TYPE_AIRBORNE_RADAR))
							{
								if (get_local_entity_parent (target, LIST_TYPE_TARGET) == source)
								{
									draw_threat_line = TRUE;

									launched_weapon = get_local_entity_first_child (target, LIST_TYPE_LAUNCHED_WEAPON);

									while (launched_weapon)
									{
										if (get_local_entity_int_value (launched_weapon, INT_TYPE_WEAPON_GUIDANCE_TYPE) != WEAPON_GUIDANCE_TYPE_NONE)
										{
											if (get_local_entity_parent (launched_weapon, LIST_TYPE_TARGET) == source)
											{
												draw_threat_line = tsd_draw_threat_line_status;

												break;
											}
										}

										launched_weapon = get_local_entity_child_succ (launched_weapon, LIST_TYPE_LAUNCHED_WEAPON);
									}

									if (draw_threat_line)
									{
										target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

										dx = (target_position->x - source_position->x) * scale;
										dy = (target_position->z - source_position->z) * scale;

										draw_2d_line (0.0, 0.0, dx, dy, MFD_COLOUR1);
									}
								}
							}
						}
					}
				}

				target = get_local_entity_child_succ (target, LIST_TYPE_GUNSHIP_TARGET);
			}

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_2d_window_rotation (mfd_env, 0.0);
		}
	}

	draw_2d_box(-1.0, 1.0, 1.0, 0.87, TRUE, FALSE, MFD_BACKGROUND_COLOUR);
	draw_2d_box(-1.0, -1.0, 1.0, y_origin, TRUE, FALSE, MFD_BACKGROUND_COLOUR);

	////////////////////////////////////////
	//
	// text
	//
	////////////////////////////////////////

	set_mono_font_colour (MFD_COLOUR_GREEN);

	if (draw_large_mfd)
	{
		set_mono_font_type (MONO_FONT_TYPE_7X12);
	}
	else
	{
		set_mono_font_type (MONO_FONT_TYPE_5X7);
	}


	//
	// TSD range
	//

	if (tsd_ase_range == TSD_ASE_RANGE_2000)
	{
		s = "2.5KM";
	}
	else if (tsd_ase_range == TSD_ASE_RANGE_5000)
	{
		s = "5KM";
	}
	else if (tsd_ase_range == TSD_ASE_RANGE_10000)
	{
		s = "10KM";
	}
	else if (tsd_ase_range == TSD_ASE_RANGE_25000)
	{
		s = "25KM";
	}
	else
	{
		s = "XXX";
	}

	width = get_mono_font_string_width (s);

	if (draw_large_mfd)
	{
		width += 2.0;

		y_adjust = 5.0;
	}
	else
	{
		width += 1.0;

		y_adjust = 2.0;
	}

	set_2d_mono_font_position (1.0, 1.0);

	set_mono_font_rel_position (-width, y_adjust);

	print_mono_font_string (s);

	//
	// TSD declutter level
	//

	if (tsd_declutter_level == TSD_DECLUTTER_LEVEL_ALL)
	{
		s = "COMBINED";
	}
	else if (tsd_declutter_level == TSD_DECLUTTER_LEVEL_TARGET)
	{
		s = "TARGETING";
	}
	else if (tsd_declutter_level == TSD_DECLUTTER_LEVEL_NAVIGATION)
	{
		s = "NAVIGATION";
	}
	else
	{
		s = "XXX";
	}

	if (draw_large_mfd)
	{
		width += 2.0;

		y_adjust = 5.0;
	}
	else
	{
		width += 1.0;

		y_adjust = 5.0;
	}

	set_2d_mono_font_position (-0.95, 1.0);

	set_mono_font_rel_position (2.0, y_adjust);

	print_mono_font_string (s);
	//
	// sensor type
	//

	set_mono_font_colour (MFD_COLOUR3);
	set_mono_font_type(MONO_FONT_TYPE_5X9);

//	if (tsd_declutter_level != TSD_DECLUTTER_LEVEL_NAVIGATION)
	{
		switch (target_acquisition_system)
		{
			case TARGET_ACQUISITION_SYSTEM_OFF:
			{
				s = "NO ACQ";

				break;
			}
			case TARGET_ACQUISITION_SYSTEM_FLIR:		//  Javelin  7/19
			{
				s = "EOS FLIR";

				break;
			}
			case TARGET_ACQUISITION_SYSTEM_LLLTV:
			{
				s = "EOS LLLTV";

				break;
			}
			case TARGET_ACQUISITION_SYSTEM_HMS:
			{
				s = "HMS";

				break;
			}
			default:
			{
				s = "XXX";

				break;
			}
		}

		if (draw_large_mfd)
		{
			y_adjust = 5.0;
		}
		else
		{
			y_adjust = 2.0;
		}

		set_2d_mono_font_position (0.5, -0.65);

		set_mono_font_rel_position (1.0, y_adjust);

		print_mono_font_string (s);
	}


	//
	// target range
	//

	{
		float
			target_range = get_range_to_target();

		if (target_range > 0.0)
		{
			sprintf (buffer, "%   4d M", (int) target_range);

			if (draw_large_mfd)
			{
				width += 2.0;

				y_adjust = 5.0;
			}
			else
			{
				width += 1.0;

				y_adjust = 2.0;
			}

			set_2d_mono_font_position (0.5, -0.75);

			set_mono_font_rel_position (1.0, y_adjust);

			print_mono_font_string (buffer);
		}
	}

	//
	// waypoint information
	//

//	if (tsd_declutter_level != TSD_DECLUTTER_LEVEL_TARGET)
	if (!ka50_damage.navigation_computer)
	{
		entity
			*wp;

		vec3d
			waypoint_position;

		float
			waypoint_range;

		// sector:
		{
			int sz, sx;
			entity* sec = get_local_sector_entity(source_position);

			sx = get_local_entity_int_value(sec, INT_TYPE_X_SECTOR);
			sz = get_local_entity_int_value(sec, INT_TYPE_Z_SECTOR);

			sprintf(buffer, "SECTOR: %d,%d", sx, sz);
			set_2d_mono_font_position (-1.0, -0.65);
			set_mono_font_rel_position (5.0, 5.0);
			print_mono_font_string (buffer);
		}

		wp = get_local_entity_current_waypoint (source);

		if (wp)
		{
			get_waypoint_display_position (source, wp, &waypoint_position);

			//
			// waypoint id & range
			//

			waypoint_range = get_2d_range (source_position, &waypoint_position);

			if (!ka50_damage.navigation_computer)
			{
				if (waypoint_range < 100000.0)
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

			if (draw_large_mfd)
			{
				y_adjust = 5.0;
			}
			else
			{
				y_adjust = 2.0;
			}

			set_2d_mono_font_position (-1.0, -0.75);

			set_mono_font_rel_position (5.0, y_adjust);

			print_mono_font_string (buffer);

			//
			// time to go
			//

			if ((current_flight_dynamics->velocity_z.value > 0.1) && (!ka50_damage.navigation_computer))
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

			if (draw_large_mfd)
			{
				y_adjust = 5.0;
			}
			else
			{
				y_adjust = 2.0;
			}

			set_2d_mono_font_position (-1.0, -0.85);

			set_mono_font_rel_position (5.0, y_adjust);

			print_mono_font_string (buffer);
		}
	}
}

#undef RADIUS

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ASE
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *get_closest_missile (entity *source, vec3d *source_position, threat_types threat_type, float *closest_missile_time_to_impact)
{
	entity
		*threat,
		*closest_missile;

	int
		overshot;

	float
		threat_range,
		threat_velocity,
		time_to_impact,
		length,
		cos_error;

	vec3d
		*threat_position,
		uvec_threat_to_target;

	matrix3x3
		*attitude;

	ASSERT (source);

	ASSERT (source_position);

	ASSERT ((threat_type == THREAT_TYPE_RF_MISSILE) || (threat_type == THREAT_TYPE_IR_MISSILE) || (threat_type == THREAT_TYPE_LASER_MISSILE));

	closest_missile = NULL;

	*closest_missile_time_to_impact = 1000000.0;

	threat = get_local_entity_first_child (get_gunship_entity (), LIST_TYPE_TARGET);

	while (threat)
	{
		if (get_local_entity_int_value (threat, INT_TYPE_THREAT_TYPE) == threat_type)
		{
			threat_position = get_local_entity_vec3d_ptr (threat, VEC3D_TYPE_POSITION);

			threat_range = get_3d_range (source_position, threat_position);

			threat_velocity = get_local_entity_float_value (threat, FLOAT_TYPE_VELOCITY);

			time_to_impact = threat_range / max (threat_velocity, 1.0f);

			//
			// guard against 'overshot target' to prevent spurious indications
			//

			overshot = FALSE;

			if (time_to_impact < 1.0)
			{
				uvec_threat_to_target.x = source_position->x - threat_position->x;
				uvec_threat_to_target.y = source_position->y - threat_position->y;
				uvec_threat_to_target.z = source_position->z - threat_position->z;

				length = get_3d_vector_magnitude (&uvec_threat_to_target);

				if (length > 1.0)
				{
					normalise_3d_vector_given_magnitude (&uvec_threat_to_target, length);

					attitude = get_local_entity_attitude_matrix_ptr (threat);

					cos_error = get_3d_unit_vector_dot_product ((vec3d *) &((*attitude) [2][0]), &uvec_threat_to_target);

					if (cos_error < 0.0)
					{
						overshot = TRUE;
					}
				}
				else
				{
					overshot = TRUE;
				}
			}

			if (!overshot)
			{
				if (time_to_impact < *closest_missile_time_to_impact)
				{
					closest_missile = threat;

					*closest_missile_time_to_impact = time_to_impact;
				}
			}
		}

		threat = get_local_entity_child_succ (threat, LIST_TYPE_TARGET);
	}

	return (closest_missile);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define RADIUS	(1.0)

static void draw_aircraft_survivability_equipment_display_mfd (ka50_mfd_locations mfd_location)
{
	char
		*s,
		buffer[200];

	entity_sides
		source_side;

	float
		scale,
		width,
		y_adjust,
		source_heading;

	entity
		*source,
		*source_target;

	vec3d
		*source_position;

	ASSERT (ka50_mfd_location_valid (mfd_location));

	source = get_gunship_entity ();

	source_side = (entity_sides) get_local_entity_int_value (source, INT_TYPE_SIDE);

	source_heading = get_local_entity_float_value (source, FLOAT_TYPE_HEADING);

	source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

	source_target = get_local_entity_parent (source, LIST_TYPE_TARGET);

	scale = RADIUS / tsd_ase_range;

	////////////////////////////////////////
	//
	// threats
	//
	////////////////////////////////////////

	{
		entity
			*threat,
			*launched_weapon;

		vec3d
			*threat_position;

		threat_types
			threat_type;

		int
			draw_threat_line;

		float
			air_scan_range,
			dx,
			dy;

		ase_threat_line_flash_timer -= get_delta_time ();

		if (ase_threat_line_flash_timer < 0.0)
		{
			ase_threat_line_flash_timer = ASE_THREAT_LINE_FLASH_RATE;

			ase_draw_threat_line_status ^= 1;
		}

		set_2d_window_rotation (mfd_env, source_heading);

		//
		// display enemy SAM and AAA threat range circles
		//
		// (use the gunship target list so that threats which are not targetting the player are still visible)
		//

		threat = get_local_entity_first_child (source, LIST_TYPE_GUNSHIP_TARGET);

		while (threat)
		{
			if (!get_local_entity_int_value (threat, INT_TYPE_GROUND_RADAR_CLUTTER))
			{
				if (source_side != get_local_entity_int_value (threat, INT_TYPE_SIDE))
				{
					threat_type = (threat_types) get_local_entity_int_value (threat, INT_TYPE_THREAT_TYPE);

					if ((threat_type == THREAT_TYPE_SAM) || (threat_type == THREAT_TYPE_AAA))
					{
						threat_position = get_local_entity_vec3d_ptr (threat, VEC3D_TYPE_POSITION);

						dx = (threat_position->x - source_position->x) * scale;
						dy = (threat_position->z - source_position->z) * scale;

						air_scan_range = get_local_entity_float_value (threat, FLOAT_TYPE_AIR_SCAN_RANGE) * scale;

						draw_2d_circle (dx, dy, air_scan_range, MFD_COLOUR_RED);
					}
				}
			}

			threat = get_local_entity_child_succ (threat, LIST_TYPE_GUNSHIP_TARGET);
		}

		//
		// display enemy SAM, AAA and AIRBORNE_RADAR threats
		//

		threat = get_local_entity_first_child (source, LIST_TYPE_GUNSHIP_TARGET);

		while (threat)
		{
			if (!get_local_entity_int_value (threat, INT_TYPE_GROUND_RADAR_CLUTTER))
			{
				if (source_side != get_local_entity_int_value (threat, INT_TYPE_SIDE))
				{
					threat_type = (threat_types) get_local_entity_int_value (threat, INT_TYPE_THREAT_TYPE);

					if ((threat_type == THREAT_TYPE_SAM) || (threat_type == THREAT_TYPE_AAA) || (threat_type == THREAT_TYPE_AIRBORNE_RADAR))
					{
//VJ 030423 TSD render mod
						draw_radar_target_symbol (threat, source_position, scale, FALSE, FALSE);
					}
				}
			}

			threat = get_local_entity_child_succ (threat, LIST_TYPE_GUNSHIP_TARGET);
		}

		//
		// draw threat line if gunship is targetted (flash if missile fired)
		//

		threat = get_local_entity_first_child (source, LIST_TYPE_GUNSHIP_TARGET);

		while (threat)
		{
			if (!get_local_entity_int_value (threat, INT_TYPE_GROUND_RADAR_CLUTTER))
			{
				if (source_side != get_local_entity_int_value (threat, INT_TYPE_SIDE))
				{
					if (get_local_entity_int_value (threat, INT_TYPE_RADAR_ON))
					{
						threat_type = (threat_types) get_local_entity_int_value (threat, INT_TYPE_THREAT_TYPE);

						if ((threat_type == THREAT_TYPE_SAM) || (threat_type == THREAT_TYPE_AAA) || (threat_type == THREAT_TYPE_AIRBORNE_RADAR))
						{
							if (get_local_entity_parent (threat, LIST_TYPE_TARGET) == source)
							{
								draw_threat_line = TRUE;

								launched_weapon = get_local_entity_first_child (threat, LIST_TYPE_LAUNCHED_WEAPON);

								while (launched_weapon)
								{
									if (get_local_entity_int_value (launched_weapon, INT_TYPE_WEAPON_GUIDANCE_TYPE) != WEAPON_GUIDANCE_TYPE_NONE)
									{
										if (get_local_entity_parent (launched_weapon, LIST_TYPE_TARGET) == source)
										{
											draw_threat_line = ase_draw_threat_line_status;

											break;
										}
									}

									launched_weapon = get_local_entity_child_succ (launched_weapon, LIST_TYPE_LAUNCHED_WEAPON);
								}

								if (draw_threat_line)
								{
									threat_position = get_local_entity_vec3d_ptr (threat, VEC3D_TYPE_POSITION);

									dx = (threat_position->x - source_position->x) * scale;
									dy = (threat_position->z - source_position->z) * scale;

									draw_2d_line (0.0, 0.0, dx, dy, MFD_COLOUR_RED);
								}
							}
						}
					}
				}
			}

			threat = get_local_entity_child_succ (threat, LIST_TYPE_GUNSHIP_TARGET);
		}

		//
		// draw incoming missiles
		//

		threat = get_local_entity_first_child (source, LIST_TYPE_TARGET);

		while (threat)
		{
			threat_type = (threat_types) get_local_entity_int_value (threat, INT_TYPE_THREAT_TYPE);

			if ((threat_type == THREAT_TYPE_RF_MISSILE) || (threat_type == THREAT_TYPE_IR_MISSILE) || (threat_type == THREAT_TYPE_LASER_MISSILE))
			{
				threat_position = get_local_entity_vec3d_ptr (threat, VEC3D_TYPE_POSITION);

				dx = (threat_position->x - source_position->x) * scale;
				dy = (threat_position->z - source_position->z) * scale;

				if (draw_large_mfd)
				{
					draw_2d_mono_sprite (large_ase_missile_mask, dx, dy, MFD_COLOUR6);

					draw_2d_mono_sprite (large_ase_missile, dx, dy, MFD_COLOUR1);
				}
				else
				{
					draw_2d_mono_sprite (small_ase_missile_mask, dx, dy, MFD_COLOUR6);

					draw_2d_mono_sprite (small_ase_missile, dx, dy, MFD_COLOUR1);
				}
			}

			threat = get_local_entity_child_succ (threat, LIST_TYPE_TARGET);
		}

		set_2d_window_rotation (mfd_env, 0.0);
	}

	////////////////////////////////////////
	//
	// aircraft datum symbol
	//
	////////////////////////////////////////

	if (draw_large_mfd)
	{
		draw_2d_mono_sprite (large_tsd_ase_aircraft_datum_mask, 0.0, 0.0, MFD_COLOUR6);

		draw_2d_mono_sprite (large_tsd_ase_aircraft_datum, 0.0, 0.0, MFD_COLOUR1);
	}
	else
	{
		draw_2d_mono_sprite (small_tsd_ase_aircraft_datum_mask, 0.0, 0.0, MFD_COLOUR6);

		draw_2d_mono_sprite (small_tsd_ase_aircraft_datum, 0.0, 0.0, MFD_COLOUR1);
	}

	set_mono_font_colour (MFD_COLOUR_GREEN);

	if (draw_large_mfd)
	{
		set_mono_font_type (MONO_FONT_TYPE_7X12);
	}
	else
	{
		set_mono_font_type (MONO_FONT_TYPE_5X7);
	}

	////////////////////////////////////////
	//
	// text
	//
	////////////////////////////////////////

	//
	// closest incoming missile
	//

	{
		entity
			*closest_missile;

		float
			time_to_impact;

		if (draw_large_mfd)
		{
			y_adjust = 5.0;
		}
		else
		{
			y_adjust = 2.0;
		}

		closest_missile = get_closest_missile (source, source_position, THREAT_TYPE_IR_MISSILE, &time_to_impact);

		if (closest_missile)
		{
			set_2d_mono_font_position (-1.0, 1.0);

			set_mono_font_rel_position (1.0, y_adjust);

			sprintf (buffer, "IR MSL:%.1f", time_to_impact);

			print_mono_font_string (buffer);

			if (draw_large_mfd)
			{
				y_adjust += 13.0;
			}
			else
			{
				y_adjust += 7.0;
			}
		}

		closest_missile = get_closest_missile (source, source_position, THREAT_TYPE_RF_MISSILE, &time_to_impact);

		if (closest_missile)
		{
			set_2d_mono_font_position (-1.0, 1.0);

			set_mono_font_rel_position (1.0, y_adjust);

			sprintf (buffer, "RF MSL:%.1f", time_to_impact);

			print_mono_font_string (buffer);

			if (draw_large_mfd)
			{
				y_adjust += 13.0;
			}
			else
			{
				y_adjust += 7.0;
			}
		}

		closest_missile = get_closest_missile (source, source_position, THREAT_TYPE_LASER_MISSILE, &time_to_impact);

		if (closest_missile)
		{
			set_2d_mono_font_position (-1.0, 1.0);

			set_mono_font_rel_position (1.0, y_adjust);

			sprintf (buffer, "LS MSL:%.1f", time_to_impact);

			print_mono_font_string (buffer);
		}
	}

	//
	// ASE range
	//

	if (tsd_ase_range == TSD_ASE_RANGE_2000)
	{
		s = "2.5KM";
	}
	else if (tsd_ase_range == TSD_ASE_RANGE_5000)
	{
		s = "5KM";
	}
	else if (tsd_ase_range == TSD_ASE_RANGE_10000)
	{
		s = "10KM";
	}
	else if (tsd_ase_range == TSD_ASE_RANGE_25000)
	{
		s = "25KM";
	}
	else
	{
		s = "XXX";
	}

	width = get_mono_font_string_width (s);

	if (draw_large_mfd)
	{
		width += 2.0;

		y_adjust = 5.0;
	}
	else
	{
		width += 1.0;

		y_adjust = 2.0;
	}

	set_2d_mono_font_position (1.0, 1.0);

	set_mono_font_rel_position (-width, y_adjust);

	print_mono_font_string (s);

	//
	// jammers
	//

	if (draw_large_mfd)
	{
		if (ka50_damage.infra_red_jammer)
		{
			s = "IR JAM XXX";
		}
		else
		{
			if (get_local_entity_int_value (source, INT_TYPE_INFRA_RED_JAMMER_ON))
			{
				s = "IR JAM ON";
			}
			else
			{
				s = "IR JAM OFF";
			}
		}

		y_adjust = -25.0;
	}
	else
	{
		if (ka50_damage.infra_red_jammer)
		{
			s = "IR XXX";
		}
		else
		{
			if (get_local_entity_int_value (source, INT_TYPE_INFRA_RED_JAMMER_ON))
			{
				s = "IR ON";
			}
			else
			{
				s = "IR OFF";
			}
		}

		y_adjust = -12.0;
	}

	set_2d_mono_font_position (-1.0, -1.0);

	set_mono_font_rel_position (1.0, y_adjust);

	print_mono_font_string (s);

	if (draw_large_mfd)
	{
		if (ka50_damage.radar_jammer)
		{
			s = "RD JAM XXX";
		}
		else
		{
			if (get_local_entity_int_value (source, INT_TYPE_RADAR_JAMMER_ON))
			{
				s = "RD JAM ON";
			}
			else
			{
				s = "RD JAM OFF";
			}
		}

		y_adjust = -12.0;
	}
	else
	{
		if (ka50_damage.radar_jammer)
		{
			s = "RD XXX";
		}
		else
		{
			if (get_local_entity_int_value (source, INT_TYPE_RADAR_JAMMER_ON))
			{
				s = "RD ON";
			}
			else
			{
				s = "RD OFF";
			}
		}

		y_adjust = -5.0;
	}

	set_2d_mono_font_position (-1.0, -1.0);

	set_mono_font_rel_position (1.0, y_adjust);

	print_mono_font_string (s);

	//
	// auto-countermeasures
	//

	if (get_global_auto_counter_measures ())
	{
		s = "AUTO";

		width = get_mono_font_string_width (s);

		if (draw_large_mfd)
		{
			width += 2.0;

			y_adjust = -38.0;
		}
		else
		{
			width += 1.0;

			y_adjust = -19.0;
		}

		set_2d_mono_font_position (-1.0, -1.0);

		set_mono_font_rel_position (1.0, y_adjust);

		print_mono_font_string (s);

		set_2d_mono_font_position (1.0, -1.0);

		set_mono_font_rel_position (-width, y_adjust);

		print_mono_font_string (s);
	}

	//
	// chaff
	//

	if (draw_large_mfd)
	{
		if ((ka50_damage.lh_chaff_dispensers) && (ka50_damage.rh_chaff_dispensers))
		{
			sprintf (buffer, "CHAFF:XX");
		}
		else
		{
			sprintf (buffer, "CHAFF:%02d", get_local_entity_weapon_count (source, ENTITY_SUB_TYPE_WEAPON_CHAFF));
		}

		width = get_mono_font_string_width (buffer);

		width += 2.0;

		y_adjust = -25.0;
	}
	else
	{
		if ((ka50_damage.lh_chaff_dispensers) && (ka50_damage.rh_chaff_dispensers))
		{
			sprintf (buffer, "C:XX");
		}
		else
		{
			sprintf (buffer, "C:%02d", get_local_entity_weapon_count (source, ENTITY_SUB_TYPE_WEAPON_CHAFF));
		}

		width = get_mono_font_string_width (buffer);

		width += 1.0;

		y_adjust = -12.0;
	}

	set_2d_mono_font_position (1.0, -1.0);

	set_mono_font_rel_position (-width, y_adjust);

	print_mono_font_string (buffer);

	//
	// flares
	//

	if (draw_large_mfd)
	{
		if ((ka50_damage.lh_flare_dispensers) && (ka50_damage.rh_flare_dispensers))
		{
			sprintf (buffer, "FLARE:XX");
		}
		else
		{
			sprintf (buffer, "FLARE:%02d", get_local_entity_weapon_count (source, ENTITY_SUB_TYPE_WEAPON_FLARE));
		}

		width = get_mono_font_string_width (buffer);

		width += 2.0;

		y_adjust = -12.0;
	}
	else
	{
		if ((ka50_damage.lh_flare_dispensers) && (ka50_damage.rh_flare_dispensers))
		{
			sprintf (buffer, "F:XX");
		}
		else
		{
			sprintf (buffer, "F:%02d", get_local_entity_weapon_count (source, ENTITY_SUB_TYPE_WEAPON_FLARE));
		}

		width = get_mono_font_string_width (buffer);

		width += 1.0;

		y_adjust = -5.0;
	}

	set_2d_mono_font_position (1.0, -1.0);

	set_mono_font_rel_position (-width, y_adjust);

	print_mono_font_string (buffer);
}

#undef RADIUS

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// WEAPON
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define WEAPON_LINE_POINT_SCALE			((float) (0.25))

#define WEAPON_LINE_POINT_X_TRANSLATE	((float) (0.0))
#define WEAPON_LINE_POINT_Y_TRANSLATE	((float) (0.575))

static int
	num_weapon_line_points;

static vec3d
	*weapon_line_points;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_weapon_display_mfd (void)
{
	char
		s[80];

	int
		i,
		result,
		number,
		damaged;

	float
		x_adjust,
		y_adjust;

	entity
		*en;

	entity_sub_types
		weapon_sub_type,
		selected_weapon;

	en = get_gunship_entity ();

	selected_weapon = get_local_entity_int_value (en, INT_TYPE_SELECTED_WEAPON);

	////////////////////////////////////////
	//
	// draw outline
	//
	////////////////////////////////////////

	i = 0;

	while (i < num_weapon_line_points)
	{
		draw_2d_line
		(
			weapon_line_points[i].x,
			weapon_line_points[i].y,
			weapon_line_points[i + 1].x,
			weapon_line_points[i + 1].y,
			MFD_COLOUR_YELLOW
		);

		i += 2;
	}

	////////////////////////////////////////
	//
	// arm
	//
	////////////////////////////////////////

	if (selected_weapon != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
	{
		set_mono_font_colour (MFD_COLOUR1);
	}
	else
	{
		set_mono_font_colour (MFD_COLOUR4);
	}

	if (draw_large_mfd)
	{
		set_mono_font_type (MONO_FONT_TYPE_7X12);

		set_2d_mono_font_position (0.0, 0.2);

		x_adjust = get_mono_font_string_width ("ARM") * -0.5;

		set_mono_font_rel_position (x_adjust, 0.0);

		print_mono_font_string ("ARM");
	}
	else
	{
		set_mono_font_type (MONO_FONT_TYPE_5X7);

		set_2d_mono_font_position (0.0, 0.2);

		x_adjust = get_mono_font_string_width ("ARM") * -0.5;

		set_mono_font_rel_position (x_adjust, 0.0);

		print_mono_font_string ("ARM");
	}

	////////////////////////////////////////
	//
	// auto-counter measures
	//
	////////////////////////////////////////

	if (get_global_auto_counter_measures ())
	{
		set_mono_font_colour (MFD_COLOUR1);
	}
	else
	{
		set_mono_font_colour (MFD_COLOUR4);
	}

	if (draw_large_mfd)
	{
		set_mono_font_type (MONO_FONT_TYPE_6X10);

		set_2d_mono_font_position (0.0, 0.0);

		x_adjust = get_mono_font_string_width ("AUTO") * -0.5;

		set_mono_font_rel_position (x_adjust, 0.0);

		print_mono_font_string ("AUTO");

		set_2d_mono_font_position (0.0, 0.0);

		x_adjust = get_mono_font_string_width ("C/M") * -0.5;

		set_mono_font_rel_position (x_adjust, get_mono_font_char_height ('X'));

		print_mono_font_string ("C/M");
	}
	else
	{
		set_mono_font_type (MONO_FONT_TYPE_5X7);

		set_2d_mono_font_position (0.0, 0.0);

		x_adjust = get_mono_font_string_width ("AUTO") * -0.5;

		set_mono_font_rel_position (x_adjust, 0.0);

		print_mono_font_string ("AUTO");

		set_2d_mono_font_position (0.0, 0.0);

		x_adjust = get_mono_font_string_width ("C/M") * -0.5;

		set_mono_font_rel_position (x_adjust, get_mono_font_char_height ('X'));

		print_mono_font_string ("C/M");
	}

	////////////////////////////////////////
	//
	// chaff and flares
	//
	////////////////////////////////////////

	if (draw_large_mfd)
	{
		set_mono_font_type (MONO_FONT_TYPE_6X10);

		y_adjust = -6.0;
	}
	else
	{
		set_mono_font_type (MONO_FONT_TYPE_3X6);

		y_adjust = -4.0;
	}

	//
	// lh chaff
	//

	result = get_local_entity_weapon_hardpoint_info (en, KA50_LHS_CHAFF_DISPENSER, ENTITY_SUB_TYPE_WEAPON_CHAFF, &weapon_sub_type, &number, &damaged);

	if (result)
	{
		set_2d_mono_font_position (-0.95, 0.3);

		if (!damaged)
		{
			if (number > 0)
			{
				set_mono_font_colour (MFD_COLOUR1);
			}
			else
			{
				set_mono_font_colour (MFD_COLOUR4);
			}

			if (draw_large_mfd)
			{
				sprintf (s, "CHAFFx%02d", number);
			}
			else
			{
				sprintf (s, "Cx%02d", number);
			}

			print_mono_font_string (s);
		}
		else
		{
			set_mono_font_colour (MFD_COLOUR4);

			if (draw_large_mfd)
			{
				print_mono_font_string ("CHAFFxXX");
			}
			else
			{
				print_mono_font_string ("CxXX");
			}
		}
	}

	//
	// lh flare
	//

	result = get_local_entity_weapon_hardpoint_info (en, KA50_LHS_FLARE_DISPENSER, ENTITY_SUB_TYPE_WEAPON_FLARE, &weapon_sub_type, &number, &damaged);

	if (result)
	{
		set_2d_mono_font_position (-0.95, 0.2);

		if (!damaged)
		{
			if (number > 0)
			{
				set_mono_font_colour (MFD_COLOUR1);
			}
			else
			{
				set_mono_font_colour (MFD_COLOUR4);
			}

			if (draw_large_mfd)
			{
				sprintf (s, "FLAREx%02d", number);
			}
			else
			{
				sprintf (s, "Fx%02d", number);
			}

			print_mono_font_string (s);
		}
		else
		{
			set_mono_font_colour (MFD_COLOUR4);

			if (draw_large_mfd)
			{
				print_mono_font_string ("FLARExXX");
			}
			else
			{
				print_mono_font_string ("FxXX");
			}
		}
	}

	//
	// rh chaff
	//

	result = get_local_entity_weapon_hardpoint_info (en, KA50_RHS_CHAFF_DISPENSER, ENTITY_SUB_TYPE_WEAPON_CHAFF, &weapon_sub_type, &number, &damaged);

	if (result)
	{
		set_2d_mono_font_position (0.95, 0.3);

		if (!damaged)
		{
			if (number > 0)
			{
				set_mono_font_colour (MFD_COLOUR1);
			}
			else
			{
				set_mono_font_colour (MFD_COLOUR4);
			}

			if (draw_large_mfd)
			{
				sprintf (s, "CHAFFx%02d", number);
			}
			else
			{
				sprintf (s, "Cx%02d", number);
			}

			x_adjust = -get_mono_font_string_width (s);

			set_mono_font_rel_position (x_adjust, 0.0);

			print_mono_font_string (s);
		}
		else
		{
			set_mono_font_colour (MFD_COLOUR4);

			if (draw_large_mfd)
			{
				x_adjust = -get_mono_font_string_width ("CHAFFxXX");

				set_mono_font_rel_position (x_adjust, 0.0);

				print_mono_font_string ("CHAFFxXX");
			}
			else
			{
				x_adjust = -get_mono_font_string_width ("CxXX");

				set_mono_font_rel_position (x_adjust, 0.0);

				print_mono_font_string ("CxXX");
			}
		}
	}

	//
	// rh flare
	//

	result = get_local_entity_weapon_hardpoint_info (en, KA50_RHS_FLARE_DISPENSER, ENTITY_SUB_TYPE_WEAPON_FLARE, &weapon_sub_type, &number, &damaged);

	if (result)
	{
		set_2d_mono_font_position (0.95, 0.2);

		if (!damaged)
		{
			if (number > 0)
			{
				set_mono_font_colour (MFD_COLOUR1);
			}
			else
			{
				set_mono_font_colour (MFD_COLOUR4);
			}

			if (draw_large_mfd)
			{
				sprintf (s, "FLAREx%02d", number);
			}
			else
			{
				sprintf (s, "Fx%02d", number);
			}

			x_adjust = -get_mono_font_string_width (s);

			set_mono_font_rel_position (x_adjust, 0.0);

			print_mono_font_string (s);
		}
		else
		{
			set_mono_font_colour (MFD_COLOUR4);

			if (draw_large_mfd)
			{
				x_adjust = -get_mono_font_string_width ("FLARExXX");

				set_mono_font_rel_position (x_adjust, 0.0);

				print_mono_font_string ("FLARExXX");
			}
			else
			{
				x_adjust = -get_mono_font_string_width ("FxXX");

				set_mono_font_rel_position (x_adjust, 0.0);

				print_mono_font_string ("FxXX");
			}
		}
	}

	////////////////////////////////////////
	//
	// cannon
	//
	////////////////////////////////////////

	result = get_local_entity_weapon_hardpoint_info (en, KA50_CANNON_TURRET, ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND, &weapon_sub_type, &number, &damaged);

	if (result)
	{
		//
		// selected weapon
		//

		if (weapon_sub_type == selected_weapon)
		{
			set_mono_font_colour (MFD_COLOUR1);
		}
		else
		{
			set_mono_font_colour (MFD_COLOUR4);
		}

		//
		// weapon name and number
		//

		sprintf (s, "HEx%03d", number);

		set_2d_mono_font_position (0.0, -0.4);

		x_adjust = get_mono_font_string_width (s) * -0.5;

		set_mono_font_rel_position (x_adjust, y_adjust);

		print_mono_font_string (s);
	}

	result = get_local_entity_weapon_hardpoint_info (en, KA50_CANNON_TURRET, ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND, &weapon_sub_type, &number, &damaged);

	if (result)
	{
		//
		// selected weapon
		//

		if (weapon_sub_type == selected_weapon)
		{
			set_mono_font_colour (MFD_COLOUR1);
		}
		else
		{
			set_mono_font_colour (MFD_COLOUR4);
		}

		//
		// weapon name and number
		//

		sprintf (s, "APx%03d", number);

		set_2d_mono_font_position (0.0, -0.5);

		x_adjust = get_mono_font_string_width (s) * -0.5;

		set_mono_font_rel_position (x_adjust, y_adjust);

		print_mono_font_string (s);

		//
		// lines
		//

		if (draw_large_mfd)
		{
			draw_2d_half_thick_line (0.2375, -0.26, 0.2375, -0.425, MFD_COLOUR_YELLOW);

			draw_2d_half_thick_line (0.1875, -0.425, 0.2375, -0.425, MFD_COLOUR_YELLOW);

			if (ka50_damage.gun_jammed)
			{
				draw_2d_half_thick_line (0.2375 - 0.05, -0.215 - 0.05, 0.2375 + 0.05, -0.215 + 0.05, MFD_COLOUR1);

				draw_2d_half_thick_line (0.2375 + 0.05, -0.215 - 0.05, 0.2375 - 0.05, -0.215 + 0.05, MFD_COLOUR1);
			}
		}
		else
		{
			draw_2d_line (0.233, -0.27, 0.233, -0.42, MFD_COLOUR_YELLOW);

			draw_2d_line (0.2, -0.42, 0.233, -0.42, MFD_COLOUR_YELLOW);

			if (ka50_damage.gun_jammed)
			{
				draw_2d_line (0.235 - 0.05, -0.22 - 0.05, 0.235 + 0.05, -0.22 + 0.05, MFD_COLOUR1);

				draw_2d_line (0.235 + 0.05, -0.22 - 0.05, 0.235 - 0.05, -0.22 + 0.05, MFD_COLOUR1);
			}
		}
	}

	////////////////////////////////////////
	//
	// lh inner pylon
	//
	////////////////////////////////////////

	result = get_local_entity_weapon_hardpoint_info (en, KA50_LHS_INNER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, &weapon_sub_type, &number, &damaged);

	if (result)
	{
		//
		// selected weapon
		//

		if (weapon_sub_type == selected_weapon)
		{
			set_mono_font_colour (MFD_COLOUR1);
		}
		else
		{
			set_mono_font_colour (MFD_COLOUR4);
		}

		//
		// number
		//

		sprintf (s, "x%02d", number);

		set_2d_mono_font_position (-0.45, -0.6);

		print_mono_font_string (s);

		//
		// lines
		//

		if (draw_large_mfd)
		{
			draw_2d_half_thick_line (-0.52, -0.14, -0.52, -0.63, MFD_COLOUR_YELLOW);

			draw_2d_half_thick_line (-0.47, -0.63, -0.52, -0.63, MFD_COLOUR_YELLOW);

			if (damaged)
			{
				draw_2d_half_thick_line (-0.52 - 0.05, -0.07 - 0.05, -0.52 + 0.05, -0.07 + 0.05, MFD_COLOUR1);

				draw_2d_half_thick_line (-0.52 + 0.05, -0.07 - 0.05, -0.52 - 0.05, -0.07 + 0.05, MFD_COLOUR1);
			}
		}
		else
		{
			draw_2d_line (-0.52, -0.16, -0.52, -0.63, MFD_COLOUR_YELLOW);

			draw_2d_line (-0.47, -0.63, -0.52, -0.63, MFD_COLOUR_YELLOW);

			if (damaged)
			{
				draw_2d_line (-0.52 - 0.05, -0.07 - 0.05, -0.52 + 0.05, -0.07 + 0.05, MFD_COLOUR1);

				draw_2d_line (-0.52 + 0.05, -0.07 - 0.05, -0.52 - 0.05, -0.07 + 0.05, MFD_COLOUR1);
			}
		}
	}

	////////////////////////////////////////
	//
	// rh inner pylon
	//
	////////////////////////////////////////

	result = get_local_entity_weapon_hardpoint_info (en, KA50_RHS_INNER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, &weapon_sub_type, &number, &damaged);

	if (result)
	{
		//
		// selected weapon
		//

		if (weapon_sub_type == selected_weapon)
		{
			set_mono_font_colour (MFD_COLOUR1);
		}
		else
		{
			set_mono_font_colour (MFD_COLOUR4);
		}

		//
		// number
		//

		sprintf (s, "x%02d", number);

		set_2d_mono_font_position (0.45, -0.6);

		x_adjust = -get_mono_font_string_width (s);

		set_mono_font_rel_position (x_adjust, 0.0);

		print_mono_font_string (s);

		//
		// weapon name
		//

		set_2d_mono_font_position (0.0, -0.6);

		x_adjust = get_mono_font_string_width (weapon_database[weapon_sub_type].mfd_name) * -0.5;

		set_mono_font_rel_position (x_adjust, 0.0);

		print_mono_font_string (weapon_database[weapon_sub_type].mfd_name);

		//
		// lines
		//

		if (draw_large_mfd)
		{
			draw_2d_half_thick_line (0.52, -0.14, 0.52, -0.63, MFD_COLOUR_YELLOW);

			draw_2d_half_thick_line (0.47, -0.63, 0.52, -0.63, MFD_COLOUR_YELLOW);

			if (damaged)
			{
				draw_2d_half_thick_line (0.52 - 0.05, -0.07 - 0.05, 0.52 + 0.05, -0.07 + 0.05, MFD_COLOUR1);

				draw_2d_half_thick_line (0.52 + 0.05, -0.07 - 0.05, 0.52 - 0.05, -0.07 + 0.05, MFD_COLOUR1);
			}
		}
		else
		{
			draw_2d_line (0.52, -0.16, 0.52, -0.63, MFD_COLOUR_YELLOW);

			draw_2d_line (0.47, -0.63, 0.52, -0.63, MFD_COLOUR_YELLOW);

			if (damaged)
			{
				draw_2d_line (0.52 - 0.05, -0.07 - 0.05, 0.52 + 0.05, -0.07 + 0.05, MFD_COLOUR1);

				draw_2d_line (0.52 + 0.05, -0.07 - 0.05, 0.52 - 0.05, -0.07 + 0.05, MFD_COLOUR1);
			}
		}
	}

	////////////////////////////////////////
	//
	// lh outer pylons
	//
	////////////////////////////////////////

	result = get_local_entity_weapon_hardpoint_info (en, KA50_LHS_OUTER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, &weapon_sub_type, &number, &damaged);

	if (result)
	{
		//
		// selected weapon
		//

		if (weapon_sub_type == selected_weapon)
		{
			set_mono_font_colour (MFD_COLOUR1);
		}
		else
		{
			set_mono_font_colour (MFD_COLOUR4);
		}

		//
		// number
		//

		sprintf (s, "x%02d", number);

		set_2d_mono_font_position (-0.45, -0.8);

		set_mono_font_rel_position (0.0, y_adjust);

		print_mono_font_string (s);

		//
		// lines
		//

		if (draw_large_mfd)
		{
			draw_2d_half_thick_line (-0.695, -0.14, -0.695, -0.785, MFD_COLOUR_YELLOW);

			draw_2d_half_thick_line (-0.47, -0.785, -0.695, -0.785, MFD_COLOUR_YELLOW);

			if (damaged)
			{
				draw_2d_half_thick_line (-0.695 - 0.05, -0.07 - 0.05, -0.695 + 0.05, -0.07 + 0.05, MFD_COLOUR1);

				draw_2d_half_thick_line (-0.695 + 0.05, -0.07 - 0.05, -0.695 - 0.05, -0.07 + 0.05, MFD_COLOUR1);
			}
		}
		else
		{
			draw_2d_line (-0.695, -0.16, -0.695, -0.785, MFD_COLOUR_YELLOW);

			draw_2d_line (-0.47, -0.785, -0.695, -0.785, MFD_COLOUR_YELLOW);

			if (damaged)
			{
				draw_2d_line (-0.695 - 0.05, -0.07 - 0.05, -0.695 + 0.05, -0.07 + 0.05, MFD_COLOUR1);

				draw_2d_line (-0.695 + 0.05, -0.07 - 0.05, -0.695 - 0.05, -0.07 + 0.05, MFD_COLOUR1);
			}
		}
	}

	////////////////////////////////////////
	//
	// rh outer pylon
	//
	////////////////////////////////////////

	result = get_local_entity_weapon_hardpoint_info (en, KA50_RHS_OUTER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, &weapon_sub_type, &number, &damaged);

	if (result)
	{
		//
		// selected weapon
		//

		if (weapon_sub_type == selected_weapon)
		{
			set_mono_font_colour (MFD_COLOUR1);
		}
		else
		{
			set_mono_font_colour (MFD_COLOUR4);
		}

		//
		// number
		//

		sprintf (s, "x%02d", number);

		set_2d_mono_font_position (0.45, -0.8);

		x_adjust = -get_mono_font_string_width (s);

		set_mono_font_rel_position (x_adjust, y_adjust);

		print_mono_font_string (s);

		//
		// weapon name
		//

		set_2d_mono_font_position (0.0, -0.8);

		x_adjust = get_mono_font_string_width (weapon_database[weapon_sub_type].mfd_name) * -0.5;

		set_mono_font_rel_position (x_adjust, y_adjust);

		print_mono_font_string (weapon_database[weapon_sub_type].mfd_name);

		//
		// lines
		//

		if (draw_large_mfd)
		{
			draw_2d_half_thick_line (0.695, -0.14, 0.695, -0.785, MFD_COLOUR_YELLOW);

			draw_2d_half_thick_line (0.47, -0.785, 0.695, -0.785, MFD_COLOUR_YELLOW);

			if (damaged)
			{
				draw_2d_half_thick_line (0.695 - 0.05, -0.07 - 0.05, 0.695 + 0.05, -0.07 + 0.05, MFD_COLOUR1);

				draw_2d_half_thick_line (0.695 + 0.05, -0.07 - 0.05, 0.695 - 0.05, -0.07 + 0.05, MFD_COLOUR1);
			}
		}
		else
		{
			draw_2d_line (0.695, -0.16, 0.695, -0.785, MFD_COLOUR_YELLOW);

			draw_2d_line (0.47, -0.785, 0.695, -0.785, MFD_COLOUR_YELLOW);

			if (damaged)
			{
				draw_2d_line (0.695 - 0.05, -0.07 - 0.05, 0.695 + 0.05, -0.07 + 0.05, MFD_COLOUR1);

				draw_2d_line (0.695 + 0.05, -0.07 - 0.05, 0.695 - 0.05, -0.07 + 0.05, MFD_COLOUR1);
			}
		}
	}

	////////////////////////////////////////
	//
	// rocket salvo
	//
	////////////////////////////////////////

	if ((selected_weapon == ENTITY_SUB_TYPE_WEAPON_S8) || (selected_weapon == ENTITY_SUB_TYPE_WEAPON_S13))
	{
		set_mono_font_colour (MFD_COLOUR1);
	}
	else
	{
		set_mono_font_colour (MFD_COLOUR4);
	}

	set_2d_mono_font_position (0.0, -0.9);

	if (rocket_salvo_size == ROCKET_SALVO_SIZE_ALL)
	{
		sprintf (s, "ROCKET SALVOxALL");
	}
	else
	{
		sprintf (s, "ROCKET SALVOx%02d", rocket_salvo_size);
	}

	x_adjust = get_mono_font_string_width (s) * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string (s);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SYSTEM
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float print_mfd_system_message (char *equipment, char *warning, int fail, float y_adjust, float width_adjust)
{
	char
		*status;

	float
		width;

	ASSERT (equipment);

	ASSERT (warning);

	if (fail)
	{
		set_mono_font_colour (MFD_COLOUR1);

		status = warning;
	}
	else
	{
		set_mono_font_colour (MFD_COLOUR4);

		status = "OK";
	}

	set_2d_mono_font_position (-0.9, 0.975);

	set_mono_font_rel_position (1.0, y_adjust);

	print_mono_font_string (equipment);

	width = get_mono_font_string_width (status);

	width += width_adjust;

	set_2d_mono_font_position (0.9, 0.975);

	set_mono_font_rel_position (-width, y_adjust);

	print_mono_font_string (status);

	y_adjust += get_mono_font_char_height ('X');

	return (y_adjust);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_system_display_mfd (void)
{
	float
		y_adjust,
		width_adjust;

	if (draw_large_mfd)
	{
		set_mono_font_type (MONO_FONT_TYPE_7X12);

		y_adjust = 0.0;

		width_adjust = 2.0;
	}
	else
	{
		set_mono_font_type (MONO_FONT_TYPE_3X6);

		y_adjust = 0.0;

		width_adjust = 1.0;
	}

	y_adjust = print_mfd_system_message ("FLIR", "FAIL", ka50_damage.flir, y_adjust, width_adjust);  //  Javelin  7/19

	y_adjust = print_mfd_system_message ("LLLTV", "FAIL", ka50_damage.llltv, y_adjust, width_adjust);

	y_adjust = print_mfd_system_message ("LASER DESIGNATOR", "FAIL", ka50_damage.laser_designator, y_adjust, width_adjust);

	y_adjust = print_mfd_system_message ("RADAR JAMMER", "FAIL", ka50_damage.radar_jammer, y_adjust, width_adjust);

	y_adjust = print_mfd_system_message ("IR JAMMER", "FAIL", ka50_damage.infra_red_jammer, y_adjust, width_adjust);

	y_adjust = print_mfd_system_message ("NAVIGATION COMPUTER", "FAIL", ka50_damage.navigation_computer, y_adjust, width_adjust);

	y_adjust = print_mfd_system_message ("COMMUNICATIONS", "FAIL", ka50_damage.communications, y_adjust, width_adjust);

	y_adjust = print_mfd_system_message ("RADAR WARNING SYSTEM", "FAIL", ka50_damage.radar_warning_system, y_adjust, width_adjust);

	y_adjust = print_mfd_system_message ("HUD", "FAIL", ka50_damage.head_up_display, y_adjust, width_adjust);

	y_adjust = print_mfd_system_message ("HMS", "FAIL", ka50_damage.helmet_mounted_sight, y_adjust, width_adjust);

	y_adjust = print_mfd_system_message ("NVG", "FAIL", ka50_damage.night_vision_goggles, y_adjust, width_adjust);

	y_adjust = print_mfd_system_message ("STABILISER", "FAIL", get_dynamics_damage_type (DYNAMICS_DAMAGE_STABILISER), y_adjust, width_adjust);

	y_adjust = print_mfd_system_message ("MAIN ROTOR", "FAIL", get_dynamics_damage_type (DYNAMICS_DAMAGE_MAIN_ROTOR), y_adjust, width_adjust);

	y_adjust = print_mfd_system_message ("L ENGINE", "DAMAGED", get_dynamics_damage_type (DYNAMICS_DAMAGE_LEFT_ENGINE), y_adjust, width_adjust);

	y_adjust = print_mfd_system_message ("APU", "DAMAGED", get_dynamics_damage_type (DYNAMICS_DAMAGE_APU), y_adjust, width_adjust);

	y_adjust = print_mfd_system_message ("R ENGINE", "DAMAGED", get_dynamics_damage_type (DYNAMICS_DAMAGE_RIGHT_ENGINE), y_adjust, width_adjust);

	y_adjust = print_mfd_system_message ("HYDRAULIC PRESSURE", "LOW", get_dynamics_damage_type (DYNAMICS_DAMAGE_LOW_HYDRAULICS), y_adjust, width_adjust);

	if (get_dynamics_damage_type (DYNAMICS_DAMAGE_LOW_OIL_PRESSURE))
	{
		y_adjust = print_mfd_system_message ("OIL PRESSURE", "LOW", get_dynamics_damage_type (DYNAMICS_DAMAGE_LOW_OIL_PRESSURE), y_adjust, width_adjust);
	}
	else
	{
		y_adjust = print_mfd_system_message ("OIL PRESSURE", "HIGH", get_dynamics_damage_type (DYNAMICS_DAMAGE_HIGH_OIL_PRESSURE), y_adjust, width_adjust);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ENGINE
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_engine_dial(char* name, float x_pos, float y_pos, float size, float value, float top_value, unsigned green_zone, unsigned yellow_zone, unsigned red_zone)
{
	float x_adjust, y_adjust;
	char s[20];

	draw_2d_arc(x_pos, y_pos, size, green_zone, MFD_COLOUR_GREEN);
	if (yellow_zone)
		draw_2d_arc(x_pos, y_pos, size, yellow_zone, MFD_COLOUR_YELLOW);
	if (red_zone)
		draw_2d_arc(x_pos, y_pos, size, red_zone, MFD_COLOUR_RED);

	// print value
	sprintf (s, "%d", (int)(value + 0.5));
	set_2d_mono_font_position (x_pos + size, y_pos - 0.1);

	x_adjust = -get_mono_font_string_width (s);
	y_adjust = -6.0;

	set_mono_font_rel_position (x_adjust, y_adjust);
	print_mono_font_string (s);

	// print name
	set_2d_mono_font_position (x_pos + 0.05, y_pos - 0.2);

	x_adjust = 1.0;
	y_adjust = -6.0;

	set_mono_font_rel_position (x_adjust, y_adjust);
	print_mono_font_string (name);

	// draw dial
	{
		float dial_angle = rad(180.0) + (PI * (value / top_value));
		float dial_x, dial_y;

		dial_angle = bound(dial_angle, rad(180.0), rad(405.0));
		dial_x = x_pos + sin(dial_angle) * size;
		dial_y = y_pos + cos(dial_angle) * size;

		draw_2d_half_thick_line(x_pos, y_pos, dial_x, dial_y, MFD_COLOUR1);
	}
}

static void draw_engine_display_mfd (void)
{
	char
		s[80];

	set_mono_font_colour (MFD_COLOUR1);

	draw_2d_box(-0.9, 0.9, -0.4, -0.9, FALSE, FALSE, MFD_COLOUR1);
	draw_2d_box( 0.9, 0.9,  0.4, -0.9, FALSE, FALSE, MFD_COLOUR1);

	set_mono_font_type(MONO_FONT_TYPE_6X10);

	// engine NG RPM
	{
		float rpm;

		rpm = bound (current_flight_dynamics->left_engine_n1_rpm.value, 0.0, 120.0);
		draw_engine_dial("NG", -0.65, 0.65, 0.2, rpm, 100.0, ARC_LEFT_UP | ARC_LEFT_DOWN | ARC_BOTTOM_LEFT, ARC_TOP_LEFT, ARC_TOP_RIGHT);

		rpm = bound (current_flight_dynamics->right_engine_n1_rpm.value, 0.0, 120.0);
		draw_engine_dial("NG", 0.65, 0.65, 0.2, rpm, 100.0, ARC_LEFT_UP | ARC_LEFT_DOWN | ARC_BOTTOM_LEFT, ARC_TOP_LEFT, ARC_TOP_RIGHT);
	}

	// engine NP RPM
	{
		float rpm;

		rpm = bound (current_flight_dynamics->left_engine_rpm.value, 0.0, 120.0);
		draw_engine_dial("NP", -0.65, 0.22, 0.2, rpm, 100.0, ARC_LEFT_UP | ARC_LEFT_DOWN | ARC_BOTTOM_LEFT | ARC_TOP_LEFT, ARC_TOP_RIGHT, 0);

		rpm = bound (current_flight_dynamics->right_engine_rpm.value, 0.0, 120.0);
		draw_engine_dial("NP", 0.65, 0.22, 0.2, rpm, 100.0, ARC_LEFT_UP | ARC_LEFT_DOWN | ARC_BOTTOM_LEFT | ARC_TOP_LEFT, ARC_TOP_RIGHT, 0);
	}

	// engine torque
	{
		float torque;

		torque = bound (current_flight_dynamics->left_engine_torque.value, 0.0, 120.0);
		draw_engine_dial("TRQ", -0.65, -0.22, 0.2, torque, 100.0, ARC_LEFT_UP | ARC_LEFT_DOWN | ARC_BOTTOM_LEFT, ARC_TOP_LEFT, ARC_TOP_RIGHT);

		torque = bound (current_flight_dynamics->right_engine_torque.value, 0.0, 120.0);
		draw_engine_dial("TRQ", 0.65, -0.22, 0.2, torque, 100.0, ARC_LEFT_UP | ARC_LEFT_DOWN | ARC_BOTTOM_LEFT, ARC_TOP_LEFT, ARC_TOP_RIGHT);
	}

	// engine temp
	{
		float temp;

		temp = bound (current_flight_dynamics->left_engine_temp.value, 0.0, 1000.0);
		draw_engine_dial("TGT", -0.65, -0.65, 0.2, temp, 800.0, ARC_LEFT_UP | ARC_LEFT_DOWN | ARC_BOTTOM_LEFT, ARC_TOP_LEFT, ARC_TOP_RIGHT);

		temp = bound (current_flight_dynamics->right_engine_temp.value, 0.0, 1000.0);
		draw_engine_dial("TGT", 0.65, -0.65, 0.2, temp, 800.0, ARC_LEFT_UP | ARC_LEFT_DOWN | ARC_BOTTOM_LEFT, ARC_TOP_LEFT, ARC_TOP_RIGHT);
	}

	// rotor RPM
	{
		float rpm;

		rpm = bound (current_flight_dynamics->main_rotor_rpm.value, 0.0, 125.0);
		draw_engine_dial("NR", 0.0, 0.55, 0.25, rpm, 100.0, ARC_TOP_LEFT, ARC_LEFT_UP | ARC_TOP_RIGHT, ARC_LEFT_DOWN | ARC_BOTTOM_LEFT);
	}

	// combined torque
	{
		float torque;

		torque = bound (current_flight_dynamics->combined_engine_torque.value, 0.0, 120.0);
		draw_engine_dial("TRQ", 0.0, 0.0, 0.25, torque, 100.0, ARC_LEFT_UP | ARC_LEFT_DOWN | ARC_BOTTOM_LEFT, ARC_TOP_LEFT, ARC_TOP_RIGHT);
	}

	set_mono_font_type(MONO_FONT_TYPE_5X9);

	// fuel
	{
		int i;
		float digital_readout;

		set_2d_mono_font_position (-0.4, -0.4);
		set_mono_font_rel_position (8.0, -8.0);

		digital_readout = bound (current_flight_dynamics->fuel_weight.value, 0.0, 9999.0);
		convert_float_to_int (digital_readout, &i);
		sprintf (s, "FUEL      %4d", i);

		print_mono_font_string(s);
	}

	// oil pressure
	{
		set_2d_mono_font_position (-0.4, -0.5);
		set_mono_font_rel_position (8.0, -8.0);

		if (get_dynamics_damage_type (DYNAMICS_DAMAGE_LOW_OIL_PRESSURE))
			print_mono_font_string("OIL PRES. LOW");
		else
			print_mono_font_string("OIL PRES. NORM");
	}

	// APU
	{
		float digital_readout;

		set_2d_mono_font_position (-0.4, -0.6);
		set_mono_font_rel_position (8.0, -8.0);

		digital_readout = bound (current_flight_dynamics->apu_rpm.value, 0.0, 100.0);
		sprintf (s, "APU       %3.0f%%", digital_readout);

		print_mono_font_string(s);
	}

	// Throttle
	{
		int i;
		float x_adjust;
		float digital_readout;
		char buffer2[64];

		set_2d_mono_font_position (-0.4, -0.8);
		set_mono_font_rel_position (28.0, -8.0);

		print_mono_font_string("THROTTLE");

		digital_readout = bound (current_flight_dynamics->left_engine_n1_rpm.max, 0.0, 110.0);
		convert_float_to_int (digital_readout, &i);

		if (i < 60)
			sprintf(buffer2, "OFF ");
		else if (i == 60)
			sprintf(buffer2, "IDLE");
		else if (i == 110.0)
			sprintf(buffer2, "FLY ");
		else
			sprintf(buffer2, "%03d%%", (i-60) * 2);

		digital_readout = bound (current_flight_dynamics->right_engine_n1_rpm.max, 0.0, 110.0);
		convert_float_to_int (digital_readout, &i);

		if (i< 60)
			sprintf(s, " %s OFF ", buffer2);
		else if (i == 60)
			sprintf(s, " %s IDLE", buffer2);
		else if (i == 110.0)
			sprintf(s, " %s FLY ", buffer2);
		else
			sprintf(s, " %s %03d%%", buffer2, (i-60) * 2);

		x_adjust = get_mono_font_string_width (s) * -0.5;

		set_2d_mono_font_position (0.0, -0.9);
		set_mono_font_rel_position (x_adjust, -8.0);
		print_mono_font_string (s);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// FLIGHT
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

	size = 0.59;
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

	draw_2d_mono_sprite (main_horizon_mask, x_centre, y_centre, MFD_BACKGROUND_COLOUR);

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

		if (!ka50_damage.navigation_computer)
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

		if ((current_flight_dynamics->velocity_z.value > 0.1) && (!ka50_damage.navigation_computer))
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
// MISSION
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void print_mono_font_max_length_string (char *s)
{
	char
		buffer[200];

	ASSERT (s);

	sprintf (buffer, "%.31s", s);

	print_mono_font_string (buffer);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static char *get_player_rank_and_name (entity *en, char *buffer)
{
	const char
		*rank,
		*name;

	entity
		*aircrew;

	ASSERT (en);

	ASSERT (buffer);

	if (get_local_entity_int_value (en, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
	{
		aircrew = get_local_entity_first_child (en, LIST_TYPE_AIRCREW);

		while (aircrew)
		{
			if (get_local_entity_int_value (aircrew, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_PILOT_PILOT)
			{
				break;
			}

			aircrew = get_local_entity_child_succ (aircrew, LIST_TYPE_AIRCREW);
		}

		if (aircrew)
		{
			rank = get_untranslated_pilot_rank_short_name (get_local_entity_int_value (aircrew, INT_TYPE_PILOT_RANK));

			name = get_local_entity_string (aircrew, STRING_TYPE_PILOTS_NAME);

			if ((rank && strlen (rank)) && (name && strlen (name)))
			{
				sprintf (buffer, "%s %s", rank, name);

				return (buffer);
			}
		}
	}

	return (NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void print_target_position (entity *source, entity *target)
{
	char
		s[80];

	int
		x_sector,
		z_sector,
		bearing;

	float
		range;

	vec3d
		*position;

	ASSERT (source);

	ASSERT (target);

	position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

	ASSERT (position);

	get_x_sector (x_sector, position->x);
	get_z_sector (z_sector, position->z);

	bearing = (int) (deg (get_local_entity_target_bearing (source, target, &range)));

	if (bearing == 0)
	{
		bearing = 360;
	}

	range *= (float) (1.0 / 1000.0);

	sprintf (s, "       <%03d,%03d> %6.1fKm %3d\x7f", x_sector, z_sector, range, bearing);

	print_mono_font_max_length_string (s);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_mission_display_mfd (void)
{
	char
		c,
		s1[200],
		s2[200];

	int
		formation,
		status_name,
		hours,
		minutes,
		seconds,
		mission_hours,
		mission_minutes,
		mission_seconds,
		estimated_hours,
		estimated_minutes,
		estimated_seconds;

	float
		char_height,
		x_adjust,
		y_adjust,
		x_min,
		x_mid,
		x_max,
		time,
		mission_time,
		estimated_time;

	entity
		*en,
		*group,
		*company,
		*member,
		*task,
		*keysite,
		*objective;

	en = get_gunship_entity ();

	get_2d_float_screen_y_coordinate (1.0, &y_adjust);

	get_2d_float_screen_x_coordinate (-1.0, &x_min);

	get_2d_float_screen_x_coordinate (0.0, &x_mid);

	get_2d_float_screen_x_coordinate (1.0, &x_max);

	if (draw_large_mfd)
	{
		set_mono_font_type (MONO_FONT_TYPE_7X12);

		y_adjust += 3.0;

		x_min += 3.0;

		x_max -= 3.0;
	}
	else
	{
		set_mono_font_type (MONO_FONT_TYPE_3X6);

		y_adjust += 2.0;

		x_min += 2.0;

		x_max -= 2.0;
	}

	char_height = get_mono_font_char_height ('X');

	////////////////////////////////////////
	//
	// flight group
	//
	////////////////////////////////////////

	group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

	if (group)
	{
		//
		// title
		//

		set_mono_font_colour (MFD_COLOUR_GREEN);

		draw_line (x_min, y_adjust, x_max, y_adjust, MFD_COLOUR_GREEN);

		y_adjust += 2.0;

		x_adjust = get_mono_font_string_width ("FLIGHT GROUP") * 0.5;

		set_mono_font_position (x_mid - x_adjust, y_adjust);

		print_mono_font_string ("FLIGHT GROUP");

		y_adjust += char_height;

		if (draw_large_mfd)
		{
			y_adjust -= 1.0;
		}

		draw_line (x_min, y_adjust, x_max, y_adjust, MFD_COLOUR_GREEN);

		if (draw_large_mfd)
		{
			y_adjust += 3.0;
		}
		else
		{
			y_adjust += 2.0;
		}

		set_mono_font_colour (MFD_COLOUR3);

		//
		// division name
		//

		if (get_global_current_language () != LANGUAGE_RUSSIAN)
		{
			company = get_local_entity_parent (group, LIST_TYPE_DIVISION);

			ASSERT (company);

			sprintf (s1, "%s:", get_local_entity_string (company, STRING_TYPE_DIVISION_NAME));

			set_mono_font_position (x_min, y_adjust);

			print_mono_font_max_length_string (s1);

			y_adjust += char_height;
		}

		//
		// members (callsign, players' rank and name, group leader)
		//

		member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

		while (member)
		{
			if (get_local_entity_int_value (member, INT_TYPE_GROUP_LEADER))
			{
				c = '>';
			}
			else
			{
				c = ' ';
			}

			if (get_player_rank_and_name (member, s2))
			{
				if (get_global_current_language () != LANGUAGE_RUSSIAN)
				{
					sprintf
					(
						s1,
						"%c%s 1-%d %s",
						c,
						get_local_entity_string (group, STRING_TYPE_GROUP_CALLSIGN),
						get_local_entity_int_value (member, INT_TYPE_GROUP_MEMBER_ID),
						s2
					);
				}
				else
				{
					sprintf
					(
						s1,
						"%c1-%d %s",
						c,
						get_local_entity_int_value (member, INT_TYPE_GROUP_MEMBER_ID),
						s2
					);
				}
			}
			else
			{
				if (get_global_current_language () != LANGUAGE_RUSSIAN)
				{
					sprintf
					(
						s1,
						"%c%s 1-%d",
						c,
						get_local_entity_string (group, STRING_TYPE_GROUP_CALLSIGN),
						get_local_entity_int_value (member, INT_TYPE_GROUP_MEMBER_ID)
					);
				}
				else
				{
					sprintf
					(
						s1,
						"%c1-%d",
						c,
						get_local_entity_int_value (member, INT_TYPE_GROUP_MEMBER_ID)
					);
				}
			}

			set_mono_font_position (x_min, y_adjust);

			print_mono_font_max_length_string (s1);

			y_adjust += char_height;

			member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
		}

		//
		// formation
		//

		formation = get_local_entity_int_value (group, INT_TYPE_GROUP_FORMATION);

		sprintf (s1, "FORMATION:%s", formation_display_names[formation]);

		set_mono_font_position (x_min, y_adjust);

		print_mono_font_max_length_string (s1);

		y_adjust += char_height + 2.0;
	}

	////////////////////////////////////////
	//
	// mission
	//
	////////////////////////////////////////

	task = get_player_task (NULL);

	if (task)
	{
		ASSERT (get_local_entity_int_value (task, INT_TYPE_VISIBLE_TASK));

		//
		// title
		//

		set_mono_font_colour (MFD_COLOUR_GREEN);

		draw_line (x_min, y_adjust, x_max, y_adjust, MFD_COLOUR_GREEN);

		y_adjust += 2.0;

		x_adjust = get_mono_font_string_width ("MISSION") * 0.5;

		set_mono_font_position (x_mid - x_adjust, y_adjust);

		print_mono_font_string ("MISSION");

		y_adjust += char_height;

		if (draw_large_mfd)
		{
			y_adjust -= 1.0;
		}

		draw_line (x_min, y_adjust, x_max, y_adjust, MFD_COLOUR_GREEN);

		if (draw_large_mfd)
		{
			y_adjust += 3.0;
		}
		else
		{
			y_adjust += 2.0;
		}

		set_mono_font_colour (MFD_COLOUR3);

		//
		// type
		//

		sprintf (s1, "TYPE  :%s", get_local_entity_string (task, STRING_TYPE_SHORT_DISPLAY_NAME));

		set_mono_font_position (x_min, y_adjust);

		print_mono_font_max_length_string (s1);

		y_adjust += char_height;

		if (draw_large_mfd)
		{
			y_adjust += 2.0;
		}

		//
		// objective
		//

		objective = get_local_entity_parent (task, LIST_TYPE_TASK_DEPENDENT);

		if (objective)
		{
			char
				buffer[1024];

			get_task_objective_mfd_display_string (task, buffer);

			sprintf (s1, "OBJECT:%s", buffer);

			set_mono_font_position (x_min, y_adjust);

			print_mono_font_max_length_string (s1);

			y_adjust += char_height;

			set_mono_font_position (x_min, y_adjust);

			print_target_position (en, objective);

			y_adjust += char_height;

			if (draw_large_mfd)
			{
				y_adjust += 2.0;
			}
		}

		//
		// status
		//

		status_name = get_local_entity_int_value (task, INT_TYPE_TASK_COMPLETED);

		sprintf (s1, "STATUS:%s", task_status_names[status_name]);

		set_mono_font_position (x_min, y_adjust);

		print_mono_font_max_length_string (s1);

		y_adjust += char_height;

		if (draw_large_mfd)
		{
			y_adjust += 2.0;
		}

		//
		// start base
		//

		keysite = get_local_entity_parent (task, LIST_TYPE_ASSIGNED_TASK);

		if (keysite)
		{
			char
				buffer[1024];

			get_keysite_entity_mfd_display_name (keysite, buffer);

			sprintf (s1, "START :%s", buffer);

			set_mono_font_position (x_min, y_adjust);

			print_mono_font_max_length_string (s1);

			y_adjust += char_height;

			set_mono_font_position (x_min, y_adjust);

			print_target_position (en, keysite);

			y_adjust += char_height;

			if (draw_large_mfd)
			{
				y_adjust += 2.0;
			}
		}

		//
		// end base
		//

		keysite = (entity *) get_local_entity_ptr_value (task, PTR_TYPE_RETURN_KEYSITE);

		if (keysite)
		{
			char
				buffer[1024];

			get_keysite_entity_mfd_display_name (keysite, buffer);

			sprintf (s1, "END   :%s", buffer);

			set_mono_font_position (x_min, y_adjust);

			print_mono_font_max_length_string (s1);

			y_adjust += char_height;

			set_mono_font_position (x_min, y_adjust);

			print_target_position (en, keysite);

			y_adjust += char_height;

			if (draw_large_mfd)
			{
				y_adjust += 2.0;
			}
		}

		//
		// count (kills and losses)
		//

		sprintf
		(
			s1,
			"COUNT :Kills=%d Losses=%d",
			get_local_entity_int_value (task, INT_TYPE_KILLS),
			get_local_entity_int_value (task, INT_TYPE_LOSSES)
		);

		set_mono_font_position (x_min, y_adjust);

		print_mono_font_max_length_string (s1);

		y_adjust += char_height;

		if (draw_large_mfd)
		{
			y_adjust += 2.0;
		}

		//
		// time
		//

		mission_time = get_local_entity_float_value (task, FLOAT_TYPE_ELAPSED_MISSION_TIME);

		get_digital_clock_int_values (mission_time, &mission_hours, &mission_minutes, &mission_seconds);

		estimated_time = get_task_estimated_route_duration (task);

		get_digital_clock_int_values (estimated_time, &estimated_hours, &estimated_minutes, &estimated_seconds);

		sprintf
		(
			s1,
			"TIME  :MT=%02d:%02d:%02d MD=%02d:%02d:%02d",
			mission_hours,
			mission_minutes,
			mission_seconds,
			estimated_hours,
			estimated_minutes,
			estimated_seconds
		);

		set_mono_font_position (x_min, y_adjust);

		print_mono_font_max_length_string (s1);
	}

	////////////////////////////////////////
	//
	// time of day
	//
	////////////////////////////////////////

	set_mono_font_colour (MFD_COLOUR_GREEN);

	get_2d_float_screen_y_coordinate (-0.9, &y_adjust);

	y_adjust -= 2.0;

	draw_line (x_min, y_adjust, x_max, y_adjust, MFD_COLOUR_GREEN);

	y_adjust += 2.0;

	time = get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_TIME_OF_DAY);

	get_digital_clock_int_values (time, &hours, &minutes, &seconds);

	sprintf (s1, "%02d:%02d:%02d", hours, minutes, seconds);

	x_adjust = get_mono_font_string_width (s1) * 0.5;

	set_mono_font_position (x_mid - x_adjust, y_adjust);

	print_mono_font_string (s1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DRAW DISPLAYS
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_mfd (screen *mfd_screen, ka50_mfd_modes* mode, ka50_mfd_locations location)
{
	ASSERT (mfd_screen);

	ASSERT (ka50_mfd_mode_valid (*mode));

	ASSERT (ka50_mfd_location_valid (location));

	if (get_undamaged_eo_display_mode (*mode))
	{
		return;
	}

	set_active_screen (mfd_screen);

	if (lock_screen (mfd_screen))
	{
		set_block (0, 0, int_mfd_viewport_size - 1, int_mfd_viewport_size - 1, MFD_BACKGROUND_COLOUR);

		draw_mfd_layout_grid ();

		switch (*mode)
		{
			////////////////////////////////////////
			case KA50_MFD_MODE_OFF:
			////////////////////////////////////////
			{
				break;
			}
			////////////////////////////////////////
			case KA50_MFD_MODE_DAMAGED:
			////////////////////////////////////////
			{
				draw_damaged_mfd ();

				break;
			}
			////////////////////////////////////////
			case KA50_MFD_MODE_FLIR:				//  Javelin  7/19
			////////////////////////////////////////
			{
				draw_2d_flir_mfd (FALSE);

				break;
			}
			////////////////////////////////////////
			case KA50_MFD_MODE_LLLTV:
			////////////////////////////////////////
			{
				draw_2d_llltv_mfd (FALSE);

				break;
			}
			////////////////////////////////////////
			case KA50_MFD_MODE_TSD:
			////////////////////////////////////////
			{
				draw_tactical_situation_display_mfd (location);

				break;
			}
			////////////////////////////////////////
			case KA50_MFD_MODE_ASE:
			////////////////////////////////////////
			{
				draw_aircraft_survivability_equipment_display_mfd (location);

				break;
			}
			////////////////////////////////////////
			case KA50_MFD_MODE_WEAPON:
			////////////////////////////////////////
			{
				draw_weapon_display_mfd ();

				break;
			}
			////////////////////////////////////////
			case KA50_MFD_MODE_SYSTEM:
			////////////////////////////////////////
			{
				draw_system_display_mfd ();

				break;
			}
			////////////////////////////////////////
			case KA50_MFD_MODE_ENGINE:
			////////////////////////////////////////
			{
				draw_engine_display_mfd ();

				break;
			}
			////////////////////////////////////////
			case KA50_MFD_MODE_FLIGHT:
			////////////////////////////////////////
			{
				draw_flight_display_mfd ();

				break;
			}
			////////////////////////////////////////
			case KA50_MFD_MODE_MISSION:
			////////////////////////////////////////
			{
				draw_mission_display_mfd ();

				break;
			}
			////////////////////////////////////////
			default:
			////////////////////////////////////////
			{
				debug_fatal ("Invalid main MFD mode = %d", mode);

				break;
			}
		}

		unlock_screen (mfd_screen);
	}

	set_active_screen (video_screen);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_text_display (screen *text_screen)
{
	ASSERT (text_screen);

	set_active_screen (text_screen);

	if (lock_screen (text_screen))
	{
		set_block (0, 0, int_mfd_viewport_size - 1, int_mfd_viewport_size - 1, TEXT_BACKGROUND_COLOUR);

		draw_mfd_layout_grid ();

		set_mono_font_colour (TEXT_COLOUR1);

		if (draw_large_mfd)
		{
			set_mono_font_type (MONO_FONT_TYPE_12X20); //MONO_FONT_TYPE_7X12

			set_2d_mono_font_position (-1.0, 1.0);

			set_mono_font_rel_position (2.0, 11.0);

			print_mono_font_string (text_display_line1);

			set_2d_mono_font_position (-1.0, 1.0);

			set_mono_font_rel_position (2.0, 29.0);

			print_mono_font_string (text_display_line2);

			set_2d_mono_font_position (-1.0, 1.0);

			set_mono_font_rel_position (2.0, 47.0);

			print_mono_font_string (text_display_line3);

			set_2d_mono_font_position (-1.0, 1.0);

			set_mono_font_rel_position (2.0, 65.0);

			print_mono_font_string (text_display_line4);

			set_2d_mono_font_position (-1.0, 1.0);

			set_mono_font_rel_position (2.0, 83.0);

			print_mono_font_string (text_display_line5);
		}
		else
		{
			set_mono_font_type (MONO_FONT_TYPE_7X12);

			set_2d_mono_font_position (-1.0, 1.0);

			set_mono_font_rel_position (2.0, 11.0);

			print_mono_font_string (text_display_line1);

			set_2d_mono_font_position (-1.0, 1.0);

			set_mono_font_rel_position (2.0, 25.0);

			print_mono_font_string (text_display_line2);

			set_2d_mono_font_position (-1.0, 1.0);

			set_mono_font_rel_position (2.0, 39.0);

			print_mono_font_string (text_display_line3);

			set_2d_mono_font_position (-1.0, 1.0);

			set_mono_font_rel_position (2.0, 53.0);

			print_mono_font_string (text_display_line4);

			set_2d_mono_font_position (-1.0, 1.0);

			set_mono_font_rel_position (2.0, 67.0);

			print_mono_font_string (text_display_line5);
		}

		if (command_line_shared_mem_export != 0)		//  Javelin  7/19
			update_ka50_ekran_shared_mem(text_display_line1, text_display_line2, text_display_line3, text_display_line4, text_display_line5);

		unlock_screen (text_screen);
	}

	set_active_screen (video_screen);
}


void draw_cannon_rounds_display(screen *text_screen)
{
	ASSERT (text_screen);

	set_active_screen (text_screen);

	if (lock_screen (text_screen))
	{
		set_block (0, 0, 128 - 1, 128 - 1, TEXT_BACKGROUND_COLOUR);

		draw_mfd_layout_grid ();

		set_mono_font_colour (MFD_COLOUR_GREEN);

		set_mono_font_type (MONO_FONT_TYPE_17X26);

		set_2d_mono_font_position (-1.0, 1.0);

		set_mono_font_rel_position (2.0, 11.0);

		print_mono_font_string (cannon_rounds);

		unlock_screen (text_screen);
	}

	set_active_screen (video_screen);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MAIN FUNCTIONS
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


static void initalize_horizon_mask(int width, char** mask)
{
	int i,j;
	char *row;
	char* horizon_mask;
	int height = LARGE_MFD_VIEWPORT_SIZE * 0.62;
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

void initialise_ka50_mfd (void)
{
#ifndef OGRE_EE
	if (command_line_dynamics_engine_startup)
	{
		select_ka50_mfd_mode (KA50_MFD_MODE_OFF, KA50_MFD_LOCATION_SHKVAL);
		select_ka50_mfd_mode (KA50_MFD_MODE_OFF, KA50_MFD_LOCATION_ABRIS);
	}
	else
	{
		select_ka50_mfd_mode (KA50_MFD_MODE_OFF, KA50_MFD_LOCATION_SHKVAL);
		select_ka50_mfd_mode (KA50_MFD_MODE_TSD, KA50_MFD_LOCATION_ABRIS);
	}

	////////////////////////////////////////

	set_ka50_text_display_text ("", "", "", "", "");

	////////////////////////////////////////

	tsd_ase_range					= TSD_ASE_RANGE_5000;
	tsd_declutter_level				= TSD_DECLUTTER_LEVEL_NAVIGATION;
	tsd_threat_line_flash_timer		= TSD_THREAT_LINE_FLASH_RATE;
	tsd_draw_threat_line_status		= 0;
	ase_threat_line_flash_timer		= ASE_THREAT_LINE_FLASH_RATE;
	ase_draw_threat_line_status		= 0;

	////////////////////////////////////////

	mfd_env = create_2d_environment ();

	////////////////////////////////////////

	large_shkval_mfd_texture_screen = create_user_texture_screen (LARGE_MFD_VIEWPORT_SIZE, LARGE_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 1);
	large_abris_mfd_texture_screen = create_user_texture_screen (LARGE_MFD_VIEWPORT_SIZE, LARGE_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 1);
	large_ekran_display_texture_screen = create_user_texture_screen (LARGE_MFD_VIEWPORT_SIZE, LARGE_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 1);
	cannon_rounds_display_screen = create_user_texture_screen (128, 128, TEXTURE_TYPE_SINGLEALPHA, 1);

	small_shkval_mfd_texture_screen = create_user_texture_screen (SMALL_MFD_VIEWPORT_SIZE, SMALL_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 1);
	small_abris_mfd_texture_screen = create_user_texture_screen (SMALL_MFD_VIEWPORT_SIZE, SMALL_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 1);
	small_ekran_display_texture_screen = create_user_texture_screen (SMALL_MFD_VIEWPORT_SIZE, SMALL_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 1);

	full_mfd_texture_screen = create_system_texture_screen (LARGE_MFD_VIEWPORT_SIZE, LARGE_MFD_VIEWPORT_SIZE, TEXTURE_INDEX_AVCKPT_DISPLAY_RHS_MFD, TEXTURE_TYPE_SINGLEALPHA);

	if (command_line_colour_mfd)
	{
		set_rgb_colour (MFD_COLOUR1,            255, 255, 255, 255);
		set_rgb_colour (MFD_COLOUR2,            200, 200, 200, 255);
		set_rgb_colour (MFD_COLOUR3,            176, 176, 176, 255);
		set_rgb_colour (MFD_COLOUR4,            151, 151, 151, 255);
		set_rgb_colour (MFD_COLOUR5,            128, 128, 128, 255);
		set_rgb_colour (MFD_COLOUR6,             40,  40,  40, 255);

		set_rgb_colour (MFD_COLOUR_GREEN,        40, 220,  40, 255);
		set_rgb_colour (MFD_COLOUR_DARK_GREEN,    0, 120,   0, 255);
		set_rgb_colour (MFD_COLOUR_YELLOW,      220, 220,  20, 255);
		set_rgb_colour (MFD_COLOUR_LIGHT_BLUE,  192, 192, 255, 255);
		set_rgb_colour (MFD_COLOUR_BLUE,         20,  20, 180, 255);
		set_rgb_colour (MFD_COLOUR_RED,         200,  50,  50, 255);
	}
	else
	{
		set_rgb_colour (MFD_COLOUR1,            255, 135,   0, 255);
		set_rgb_colour (MFD_COLOUR2,            255,  90,   0, 255);
		set_rgb_colour (MFD_COLOUR3,            200,  65,   0, 255);
		set_rgb_colour (MFD_COLOUR4,            130,  50,   0, 255);
		set_rgb_colour (MFD_COLOUR5,            100,  50,   0, 255);
		set_rgb_colour (MFD_COLOUR6,             50,  25,   0, 255);

		set_rgb_colour (MFD_COLOUR_GREEN,       200,  65,   0, 255);
		set_rgb_colour (MFD_COLOUR_DARK_GREEN,  100,  50,   0, 255);
		set_rgb_colour (MFD_COLOUR_YELLOW,      255, 135,   0, 255);
		set_rgb_colour (MFD_COLOUR_LIGHT_BLUE,  255, 135,   0, 255);
		set_rgb_colour (MFD_COLOUR_BLUE,        200,  65,   0, 255);
		set_rgb_colour (MFD_COLOUR_RED,         200,  65,   0, 255);
	}

	set_rgb_colour (MFD_CONTOUR_COLOUR,     200,  35,   0, 255);
	set_rgb_colour (MFD_RIVER_COLOUR,        50,  75, 225, 255);
	set_rgb_colour (MFD_ROAD_COLOUR,        255, 225,   0, 255);
	set_rgb_colour (MFD_BACKGROUND_COLOUR,   20,  20,  30, 255);
	set_rgb_colour (MFD_CLEAR_COLOUR,         0,   0,   0, 255);

	set_rgb_colour (TEXT_COLOUR1,             255, 147, 0, 255);
	set_rgb_colour (TEXT_BACKGROUND_COLOUR,   0,  60,  34, 255);

    set_rgb_colour (clear_mfd_colour, 255, 255, 255, 0);

	////////////////////////////////////////
	//
	// weapon display lines
	//
	////////////////////////////////////////

	num_weapon_line_points = get_object_3d_number_of_poly_lines (OBJECT_3D_HOKUM_COCKPIT_WEAPONS_DISPLAY);

	ASSERT (num_weapon_line_points > 0);

	ASSERT ((num_weapon_line_points & 1) == 0);

	weapon_line_points = (vec3d *) safe_malloc (sizeof (vec3d) * num_weapon_line_points);

	get_object_3d_poly_line_data (OBJECT_3D_HOKUM_COCKPIT_WEAPONS_DISPLAY, weapon_line_points);

	{
		int
			i;

		for (i = 0; i < num_weapon_line_points; i++)
		{
			weapon_line_points[i].x *= WEAPON_LINE_POINT_SCALE;
			weapon_line_points[i].y *= WEAPON_LINE_POINT_SCALE;

			weapon_line_points[i].x += WEAPON_LINE_POINT_X_TRANSLATE;
			weapon_line_points[i].y += WEAPON_LINE_POINT_Y_TRANSLATE;
		}
	}

	initalize_horizon_mask(LARGE_MFD_VIEWPORT_SIZE * 0.6, &main_horizon_mask);

//VJ 030423 TSd render mod

   Initialise_TSD_render_terrain();

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_ka50_mfd (void)
{
#ifndef OGRE_EE
	destroy_2d_environment (mfd_env);

	////////////////////////////////////////

	destroy_screen (large_shkval_mfd_texture_screen);
	destroy_screen (large_abris_mfd_texture_screen);
	destroy_screen (large_ekran_display_texture_screen);
	destroy_screen (cannon_rounds_display_texture_screen);

	destroy_screen (small_shkval_mfd_texture_screen);
	destroy_screen (small_abris_mfd_texture_screen);
	destroy_screen (small_ekran_display_texture_screen);

	destroy_screen (full_mfd_texture_screen);

	////////////////////////////////////////
	//
	// weapon display lines
	//
	////////////////////////////////////////

	safe_free (weapon_line_points);
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_ka50_mfd (void)
{
#ifndef OGRE_EE
	////////////////////////////////////////
	//
	// SELECT LARGE OR SMALL MFD TEXTURES
	//
	////////////////////////////////////////

	// loke 030420
	// support for high resolution mfd's
	int
		large_mfd;
	screen *export_screen;						//  Javelin  6/19

	if (!command_line_high_res_mfd)
	{
		switch (get_view_mode ())
		{
			////////////////////////////////////////
			case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY:
			case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY:
			case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY:
			case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY:
			////////////////////////////////////////
			{

				large_mfd = 1;

				break;
			}
			////////////////////////////////////////
			default:
			////////////////////////////////////////
			{

				large_mfd = 0;

				break;
			}
		}
	}
	else
	{
		large_mfd = 1;
	}

	if (large_mfd)
	{
		draw_large_mfd = TRUE;

		shkval_mfd_texture_screen = large_shkval_mfd_texture_screen;
		abris_mfd_texture_screen = large_abris_mfd_texture_screen;
		ekran_display_texture_screen = large_ekran_display_texture_screen;
		cannon_rounds_display_texture_screen = cannon_rounds_display_screen;

		eo_3d_texture_screen = large_eo_3d_texture_screen;
		eo_3d_texture_screen_over = large_eo_3d_texture_screen_over;
	}
	else
	{
		draw_large_mfd = FALSE;

		shkval_mfd_texture_screen = small_shkval_mfd_texture_screen;
		abris_mfd_texture_screen = small_abris_mfd_texture_screen;
		ekran_display_texture_screen = small_ekran_display_texture_screen;
		cannon_rounds_display_texture_screen = cannon_rounds_display_screen;

		eo_3d_texture_screen = small_eo_3d_texture_screen;
		eo_3d_texture_screen_over = small_eo_3d_texture_screen_over;
	}

	set_system_texture_screen (shkval_mfd_texture_screen, TEXTURE_INDEX_HOKUM_COCKPIT_MFD_LHS_2);
	set_system_texture_screen (abris_mfd_texture_screen, TEXTURE_INDEX_HOKUM_COCKPIT_MFD_LHS_1);
	set_system_texture_screen (ekran_display_texture_screen, TEXTURE_INDEX_HOKUM_COCKPIT_EKRAN);
	set_system_texture_screen (cannon_rounds_display_texture_screen, TEXTURE_INDEX_COMANCHE_MFD1);

	////////////////////////////////////////
	//
	// SET UP MFD 2D ENVIRONMENT
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
	{
		mfd_viewport_size = LARGE_MFD_VIEWPORT_SIZE;

		int_mfd_viewport_size = LARGE_MFD_VIEWPORT_SIZE;
	}
	else
	{
		mfd_viewport_size = SMALL_MFD_VIEWPORT_SIZE;

		int_mfd_viewport_size = SMALL_MFD_VIEWPORT_SIZE;
	}

	mfd_viewport_x_org = mfd_viewport_size * 0.5;

	mfd_viewport_y_org = mfd_viewport_size * 0.5;

	mfd_viewport_x_min = 0.0;

	mfd_viewport_y_min = 0.0;

	mfd_viewport_x_max = mfd_viewport_size;

	mfd_viewport_y_max = mfd_viewport_size;

	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

	mfd_screen_x_min = 0.0;
	mfd_screen_y_min = 0.0;

	mfd_screen_x_max = mfd_viewport_size;
	mfd_screen_y_max = mfd_viewport_size;

	mfd_screen_width = mfd_viewport_size;
	mfd_screen_height = mfd_viewport_size;

	mfd_screen_x_scale = 1.0;
	mfd_screen_y_scale = 1.0;

	////////////////////////////////////////
	//
	// render EO 3D display (if required)
	//
	////////////////////////////////////////

	{
		int
			draw_eo_display;

		{
			ASSERT (eo_3d_texture_screen);

			draw_eo_display = FALSE;

			if (get_undamaged_eo_display_mode (shkval_mfd_mode))
			{
				set_system_texture_screen (eo_3d_texture_screen, TEXTURE_INDEX_HOKUM_COCKPIT_MFD_LHS_2);

				draw_eo_display = TRUE;
			}

			if (draw_eo_display)
			{
				switch (get_mfd_mode_for_eo_sensor ())
				{
					case KA50_MFD_MODE_FLIR:			//  Javelin  7/19
					{
						draw_3d_flir_mfd (FALSE);

						break;
					}
					case KA50_MFD_MODE_LLLTV:
					{
						draw_3d_llltv_mfd (FALSE);

						break;
					}
				}

				set_active_screen (eo_3d_texture_screen_over);

				if (lock_screen (eo_3d_texture_screen_over))
				{
					draw_mfd_layout_grid ();

					switch (get_mfd_mode_for_eo_sensor ())
					{
						case KA50_MFD_MODE_FLIR:			//  Javelin  7/19
						{
							draw_2d_flir_mfd (TRUE);

							break;
						}
						case KA50_MFD_MODE_LLLTV:
						{
							draw_2d_llltv_mfd (TRUE);

							break;
						}
					}

					unlock_screen (eo_3d_texture_screen_over);

					eo_3d_texture_merge (eo_3d_texture_screen, eo_3d_texture_screen_over);
				}

				set_active_screen (video_screen);
			}
		}
	}

	////////////////////////////////////////
	//
	// DRAW DISPLAYS
	//
	////////////////////////////////////////

	draw_mfd (shkval_mfd_texture_screen, &shkval_mfd_mode, KA50_MFD_LOCATION_SHKVAL);

	draw_mfd (abris_mfd_texture_screen, &abris_mfd_mode, KA50_MFD_LOCATION_ABRIS);

	draw_text_display (ekran_display_texture_screen);

	draw_cannon_rounds_display (cannon_rounds_display_texture_screen);

	if (command_line_export_mfd)
	{
		export_screen = get_screen_of_system_texture (TEXTURE_INDEX_HOKUM_COCKPIT_MFD_LHS_2);
		copy_export_mfd(export_screen, NULL);  //  shkval

		export_screen = get_screen_of_system_texture (TEXTURE_INDEX_HOKUM_COCKPIT_MFD_LHS_1);
		copy_export_mfd(NULL, export_screen);  //  abris
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_ka50_ekran_display (void)
{
	char
		s1[80],
		s2[80],
		s3[80];

	int
		lh_chaff,
		rh_chaff,
		lh_flare,
		rh_flare,
		lh_chaff_number,
		rh_chaff_number,
		lh_flare_number,
		rh_flare_number,
		damaged;

	entity
		*en;

	entity_sub_types
		weapon_sub_type;

	en = get_gunship_entity ();

	lh_chaff = get_local_entity_weapon_hardpoint_info (en, KA50_LHS_CHAFF_DISPENSER, ENTITY_SUB_TYPE_WEAPON_CHAFF, &weapon_sub_type, &lh_chaff_number, &damaged);
	rh_chaff = get_local_entity_weapon_hardpoint_info (en, KA50_RHS_CHAFF_DISPENSER, ENTITY_SUB_TYPE_WEAPON_CHAFF, &weapon_sub_type, &rh_chaff_number, &damaged);

	if (lh_chaff || rh_chaff)
	{
		if (!damaged)
		{
			sprintf	(s1, "C: L%02d R%02d", lh_chaff_number, rh_chaff_number);
		}
		else if (damaged)
			{
				if (ka50_damage.lh_chaff_dispensers)
				{
					sprintf (s1, "C: LXX R%02d", rh_chaff_number);
				}

				if (ka50_damage.rh_chaff_dispensers)
				{
					sprintf	(s1, "C: L%02d RXX", lh_chaff_number);
				}
			}
	}

	lh_flare = get_local_entity_weapon_hardpoint_info (en, KA50_LHS_FLARE_DISPENSER, ENTITY_SUB_TYPE_WEAPON_FLARE, &weapon_sub_type, &lh_flare_number, &damaged);
	rh_flare = get_local_entity_weapon_hardpoint_info (en, KA50_RHS_FLARE_DISPENSER, ENTITY_SUB_TYPE_WEAPON_FLARE, &weapon_sub_type, &rh_flare_number, &damaged);

	if (lh_flare || rh_flare)
	{
		if (!damaged)
		{
			sprintf	(s2, "F: L%02d R%02d", lh_flare_number, rh_flare_number);
		}
		else if (damaged)
			{
				if (ka50_damage.lh_flare_dispensers)
				{
					sprintf	(s2, "F: LXX R%02d", rh_flare_number);
				}

				if (ka50_damage.rh_flare_dispensers)
				{
					sprintf	(s2, "F: L%02d RXX", lh_flare_number);
				}
			}
	}

	sprintf (s3, "FUEL %04d", (int) (bound (current_flight_dynamics->fuel_weight.value, 0.0, 9999.0)));

	set_ka50_text_display_text ("", "", s1, s2, s3);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_ka50_text_display_text (char *s1, char *s2, char *s3, char *s4, char *s5)
{
#ifndef OGRE_EE

	if(s1 != "") {
		strncpy (text_display_line1, s1, TEXT_DISPLAY_MAX_STRING_LENGTH);
		text_display_line1[TEXT_DISPLAY_MAX_STRING_LENGTH] = '\0';
	}

	if(s2 != "") {
		strncpy (text_display_line2, s2, TEXT_DISPLAY_MAX_STRING_LENGTH);
		text_display_line2[TEXT_DISPLAY_MAX_STRING_LENGTH] = '\0';
	}

	if(s3 != "") {
		strncpy (text_display_line3, s3, TEXT_DISPLAY_MAX_STRING_LENGTH);
		text_display_line3[TEXT_DISPLAY_MAX_STRING_LENGTH] = '\0';
	}

	if(s4 != "") {
		strncpy (text_display_line4, s4, TEXT_DISPLAY_MAX_STRING_LENGTH);
		text_display_line4[TEXT_DISPLAY_MAX_STRING_LENGTH] = '\0';
	}

	if(s5 != "") {
		strncpy (text_display_line5, s5, TEXT_DISPLAY_MAX_STRING_LENGTH);
		text_display_line5[TEXT_DISPLAY_MAX_STRING_LENGTH] = '\0';
	}

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_ka50_cannon_rounds_display (void)
{
	char
		c1[80];

	int
		ap_rounds_number,
		he_rounds_number,
		damaged;

	entity
		*en;

	entity_sub_types
		selected_weapon,
		weapon_sub_type;

	en = get_gunship_entity ();

	selected_weapon = get_local_entity_int_value (en, INT_TYPE_SELECTED_WEAPON);

	if (get_local_entity_weapon_hardpoint_info (en, KA50_CANNON_TURRET, ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND, &weapon_sub_type, &ap_rounds_number, &damaged))
	{
		if (!damaged) {
			if (weapon_sub_type == selected_weapon) {
				sprintf	(c1, "%02d", (ap_rounds_number/10));
			}
		}
	}

	if (get_local_entity_weapon_hardpoint_info (en, KA50_CANNON_TURRET, ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND, &weapon_sub_type, &he_rounds_number, &damaged))
	{
		if (!damaged) {
			if (weapon_sub_type == selected_weapon) {
				sprintf	(c1, "%02d", (he_rounds_number/10));
			}
		}
	}

	set_ka50_cannon_rounds_display_text (c1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_ka50_cannon_rounds_display_text (char *c1)
{
#ifndef OGRE_EE

	if(c1 != "") {
		strncpy (cannon_rounds, c1, CANNON_DISPLAY_MAX_STRING_LENGTH);
	}

#endif
}

#ifndef OGRE_EE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
void draw_ka50_full_screen_display (void)
{
	ka50_mfd_modes
		mode;

	vertex
		quad[4];

	real_colour
		colour,
		specular;

	////////////////////////////////////////
	//
	// determine if full screen display is required
	//
	////////////////////////////////////////

	if (d3d_can_render_to_texture)
	{
		return;
	}

	switch (get_view_mode ())
	{
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY:
		{
			mode = shkval_mfd_mode;

			break;
		}
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY:
		{
			mode = abris_mfd_mode;

			break;
		}
		default:
		{
			debug_fatal ("Invalid view mode = %d", get_view_mode ());

			break;
		}
	}

	if (!get_undamaged_eo_display_mode (mode))
	{
		return;
	}

	////////////////////////////////////////
	//
	// render 3D display
	//
	////////////////////////////////////////

	mfd_screen_x_min = floor ((149.0 * full_screen_width) / 640.0);
	mfd_screen_y_min = floor ((69.0 * full_screen_height) / 480.0);

	mfd_screen_x_max = ceil ((492.0 * full_screen_width) / 640.0);
	mfd_screen_y_max = ceil ((412.0 * full_screen_height) / 480.0);

	//
	// widen by 1 pixel either side to ensure the MFD is covered at all resolutions
	//

	mfd_screen_x_min -= 1.0;
	mfd_screen_y_min -= 1.0;

	mfd_screen_x_max += 1.0;
	mfd_screen_y_max += 1.0;

	mfd_screen_width = mfd_screen_x_max - mfd_screen_x_min;
	mfd_screen_height = mfd_screen_y_max - mfd_screen_y_min;

	mfd_screen_x_scale = 256.0 / mfd_screen_width;
	mfd_screen_y_scale = 256.0 / mfd_screen_height;

	switch (mode)
	{
		case KA50_MFD_MODE_FLIR:		//  Javelin  7/19
		{
			draw_3d_flir_mfd (TRUE);

			break;
		}
		case KA50_MFD_MODE_LLLTV:
		{
			draw_3d_llltv_mfd (TRUE);

			break;
		}
	}

	////////////////////////////////////////
	//
	// render 2D display
	//
	////////////////////////////////////////

	set_2d_active_environment (mfd_env);

	set_2d_window (mfd_env, MFD_WINDOW_X_MIN, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX, MFD_WINDOW_Y_MAX);

	draw_large_mfd = TRUE;

	mfd_viewport_size = LARGE_MFD_VIEWPORT_SIZE;

	int_mfd_viewport_size = LARGE_MFD_VIEWPORT_SIZE;

	mfd_viewport_x_org = LARGE_MFD_VIEWPORT_SIZE * 0.5;

	mfd_viewport_y_org = LARGE_MFD_VIEWPORT_SIZE * 0.5;

	mfd_viewport_x_min = 0.0;

	mfd_viewport_y_min = 0.0;

	mfd_viewport_x_max = LARGE_MFD_VIEWPORT_SIZE;

	mfd_viewport_y_max = LARGE_MFD_VIEWPORT_SIZE;

	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

	//
	// draw MFD on texture
	//

	set_active_screen (full_mfd_texture_screen);

	if (lock_screen (full_mfd_texture_screen))
	{
      rgb_colour
         store_mfd_colour;

      store_mfd_colour = MFD_COLOUR1;

      set_rgb_colour (MFD_COLOUR1, 255, 255, 255, 255);

      set_block (0, 0, LARGE_MFD_VIEWPORT_SIZE - 1, LARGE_MFD_VIEWPORT_SIZE - 1, clear_mfd_colour);

		draw_mfd_layout_grid ();

		switch (mode)
		{
			case KA50_MFD_MODE_FLIR:		//  Javelin  7/19
			{
				draw_2d_flir_mfd (TRUE);

				break;
			}
			case KA50_MFD_MODE_LLLTV:
			{
				draw_2d_llltv_mfd (TRUE);

				break;
			}
		}

		MFD_COLOUR1 = store_mfd_colour;

		unlock_screen (full_mfd_texture_screen);
	}

	set_active_screen (video_screen);

	////////////////////////////////////////
	//
	// render MFD to screen
	//
	////////////////////////////////////////

	set_3d_active_environment (main_3d_env);

	if (begin_3d_scene ())
	{
		set_d3d_transparency_on ();

		set_d3d_zbuffer_comparison (FALSE);

		set_d3d_culling (FALSE);

		set_d3d_texture_wrapping (0, FALSE);

      set_d3d_texture_mag_filtering (TRUE);
      set_d3d_texture_min_filtering (TRUE);
      set_d3d_texture_mip_filtering (FALSE);

		set_d3d_flat_shaded_textured_renderstate (get_system_texture_ptr (TEXTURE_INDEX_AVCKPT_DISPLAY_RHS_MFD));

      ////////////////////////////////////////
      //

		colour.red				= MFD_COLOUR1.r;
		colour.green			= MFD_COLOUR1.g;
		colour.blue				= MFD_COLOUR1.b;
		colour.alpha			= MFD_COLOUR1.a;

		specular.red			= 0;
		specular.green			= 0;
		specular.blue			= 0;
		specular.alpha			= 255;

		quad[0].i				= mfd_screen_x_min;
		quad[0].j	  			= mfd_screen_y_min;
		quad[0].z	  			= 0.5;
		quad[0].q	  			= 0.5;
		quad[0].u	  			= 0.0;
		quad[0].v	  			= 0.0;

		quad[1].i				= mfd_screen_x_max;
		quad[1].j  				= mfd_screen_y_min;
		quad[1].z  				= 0.5;
		quad[1].q  				= 0.5;
		quad[1].u  				= 1.0;
		quad[1].v  				= 0.0;

		quad[2].i				= mfd_screen_x_max;
		quad[2].j 				= mfd_screen_y_max;
		quad[2].z  				= 0.5;
		quad[2].q  				= 0.5;
		quad[2].u  				= 1.0;
		quad[2].v  				= 1.0;

		quad[3].i				= mfd_screen_x_min;
		quad[3].j				= mfd_screen_y_max;
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
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// OVERLAID MFD
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

static void draw_overlaid_mfd (screen *mfd_screen, ka50_mfd_modes mode, ka50_mfd_locations location)
{
	float
		border_size;

	rgb_colour
		store_colour1,
		store_colour2,
		store_colour3,
		store_colour4,
		store_colour5,
		store_colour6,
		store_contour_colour,
		store_river_colour,
		store_road_colour,
		store_background_colour;

	ASSERT (mfd_screen);

	ASSERT (ka50_mfd_mode_valid (mode));

	ASSERT (ka50_mfd_location_valid (location));

	if (mode == KA50_MFD_MODE_OFF)
	{
		return;
	}

	////////////////////////////////////////
	//
	// scale position and size wrt screen resolution
	//
	////////////////////////////////////////

	border_size = 4.0 * full_screen_width * (1.0 / 640.0);

	if (get_global_unscaled_displays ())
	{
		mfd_screen_width = mfd_viewport_size;
	}
	else
	{
		mfd_screen_width = full_screen_width * (128.0 / 640.0);
	}

	mfd_screen_height = mfd_screen_width;

	switch (location)
	{
		////////////////////////////////////////
		case KA50_MFD_LOCATION_SHKVAL:
		////////////////////////////////////////
		{
			mfd_screen_x_min = border_size;
			mfd_screen_y_min = full_screen_height - border_size - mfd_screen_height;

			break;
		}
		////////////////////////////////////////
		case KA50_MFD_LOCATION_ABRIS:
		////////////////////////////////////////
		{
			mfd_screen_x_min = full_screen_width - border_size - mfd_screen_width;
			mfd_screen_y_min = full_screen_height - border_size - mfd_screen_height;

			break;
		}
	}

	mfd_screen_x_max = mfd_screen_x_min + mfd_screen_width - 0.0001;
	mfd_screen_y_max = mfd_screen_y_min + mfd_screen_height - 0.0001;

	mfd_screen_x_scale = mfd_viewport_size / mfd_screen_width;
	mfd_screen_y_scale = mfd_viewport_size / mfd_screen_height;

	////////////////////////////////////////
	//
	// store colours
	//
	////////////////////////////////////////

	store_colour1				= MFD_COLOUR1;
	store_colour2				= MFD_COLOUR2;
	store_colour3				= MFD_COLOUR3;
	store_colour4				= MFD_COLOUR4;
	store_colour5				= MFD_COLOUR5;
	store_colour6				= MFD_COLOUR6;
	store_contour_colour		= MFD_CONTOUR_COLOUR;
	store_river_colour		= MFD_RIVER_COLOUR;
	store_road_colour			= MFD_ROAD_COLOUR;
	store_background_colour	= MFD_BACKGROUND_COLOUR;

	set_rgb_colour (MFD_COLOUR1,            255, 255,   0, 255);
	set_rgb_colour (MFD_COLOUR2,            200, 200,   0, 255);
	set_rgb_colour (MFD_COLOUR3,            176, 176,   0, 255);
	set_rgb_colour (MFD_COLOUR4,            151, 151,   0, 255);
	set_rgb_colour (MFD_COLOUR5,            140, 140,   0, 255);
	set_rgb_colour (MFD_COLOUR6,             80,  52,   8, 255);
	set_rgb_colour (MFD_CONTOUR_COLOUR,     151, 151,   0, 255);
	set_rgb_colour (MFD_RIVER_COLOUR,       176, 176,   0, 255);
	set_rgb_colour (MFD_ROAD_COLOUR,        200, 200,   0, 255);
	set_rgb_colour (MFD_BACKGROUND_COLOUR,  255, 255, 255,   0);

	////////////////////////////////////////
	//
	// draw MFD display
	//
	////////////////////////////////////////

	switch (mode)
	{
		////////////////////////////////////////
		case KA50_MFD_MODE_OFF:
		////////////////////////////////////////
		{
			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_screen);

			if (lock_screen (mfd_screen))
			{
				set_block (0, 0, int_mfd_viewport_size - 1, int_mfd_viewport_size - 1, clear_mfd_colour);

				draw_mfd_layout_grid ();

				unlock_screen (mfd_screen);
			}

			break;
		}
		////////////////////////////////////////
		case KA50_MFD_MODE_DAMAGED:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_screen);

			if (lock_screen (mfd_screen))
			{
				set_block (0, 0, int_mfd_viewport_size - 1, int_mfd_viewport_size - 1, clear_mfd_colour);

				draw_mfd_layout_grid ();

				draw_overlaid_damaged_mfd ();

				unlock_screen (mfd_screen);
			}

			break;
		}
		////////////////////////////////////////
		case KA50_MFD_MODE_FLIR:					//  Javelin  7/19
		////////////////////////////////////////
		{
			if (!ka50_damage.flir)
			{
				draw_full_screen_3d_eo_display (&ka50_flir, TARGET_ACQUISITION_SYSTEM_FLIR, DISPLAY_3D_TINT_FLIR);
			}
			else
			{
				draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);
			}

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_screen);

			if (lock_screen (mfd_screen))
			{
				set_block (0, 0, int_mfd_viewport_size - 1, int_mfd_viewport_size - 1, clear_mfd_colour);

				draw_mfd_layout_grid ();

				draw_2d_flir_mfd (TRUE);

				unlock_screen (mfd_screen);
			}

			set_pilots_full_screen_params (FALSE);

			break;
		}
		////////////////////////////////////////
		case KA50_MFD_MODE_LLLTV:
		////////////////////////////////////////
		{
			if (!ka50_damage.llltv)
			{
				draw_full_screen_3d_eo_display (&ka50_llltv, TARGET_ACQUISITION_SYSTEM_LLLTV, DISPLAY_3D_TINT_LLLTV);
			}
			else
			{
				draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);
			}

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_screen);

			if (lock_screen (mfd_screen))
			{
				set_block (0, 0, int_mfd_viewport_size - 1, int_mfd_viewport_size - 1, clear_mfd_colour);

				draw_mfd_layout_grid ();

				draw_2d_llltv_mfd (TRUE);

				unlock_screen (mfd_screen);
			}

			set_pilots_full_screen_params (FALSE);

			break;
		}
		////////////////////////////////////////
		case KA50_MFD_MODE_TSD:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_screen);

			if (lock_screen (mfd_screen))
			{
				set_block (0, 0, int_mfd_viewport_size - 1, int_mfd_viewport_size - 1, clear_mfd_colour);

				draw_mfd_layout_grid ();

				draw_tactical_situation_display_mfd (location);

				unlock_screen (mfd_screen);
			}

			break;
		}
		////////////////////////////////////////
		case KA50_MFD_MODE_ASE:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_screen);

			if (lock_screen (mfd_screen))
			{
				set_block (0, 0, int_mfd_viewport_size - 1, int_mfd_viewport_size - 1, clear_mfd_colour);

				draw_mfd_layout_grid ();

				draw_aircraft_survivability_equipment_display_mfd (location);

				unlock_screen (mfd_screen);
			}

			break;
		}
		////////////////////////////////////////
		case KA50_MFD_MODE_WEAPON:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_screen);

			if (lock_screen (mfd_screen))
			{
				set_block (0, 0, int_mfd_viewport_size - 1, int_mfd_viewport_size - 1, clear_mfd_colour);

				draw_mfd_layout_grid ();

				draw_weapon_display_mfd ();

				unlock_screen (mfd_screen);
			}

			break;
		}
		////////////////////////////////////////
		case KA50_MFD_MODE_SYSTEM:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_screen);

			if (lock_screen (mfd_screen))
			{
				set_block (0, 0, int_mfd_viewport_size - 1, int_mfd_viewport_size - 1, clear_mfd_colour);

				draw_mfd_layout_grid ();

				draw_system_display_mfd ();

				unlock_screen (mfd_screen);
			}

			break;
		}
		////////////////////////////////////////
		case KA50_MFD_MODE_ENGINE:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_screen);

			if (lock_screen (mfd_screen))
			{
				set_block (0, 0, int_mfd_viewport_size - 1, int_mfd_viewport_size - 1, clear_mfd_colour);

				draw_mfd_layout_grid ();

				draw_engine_display_mfd ();

				unlock_screen (mfd_screen);
			}

			break;
		}
		////////////////////////////////////////
		case KA50_MFD_MODE_FLIGHT:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_screen);

			if (lock_screen (mfd_screen))
			{
				set_block (0, 0, int_mfd_viewport_size - 1, int_mfd_viewport_size - 1, clear_mfd_colour);

				draw_mfd_layout_grid ();

				draw_flight_display_mfd ();

				unlock_screen (mfd_screen);
			}

			break;
		}
		////////////////////////////////////////
		case KA50_MFD_MODE_MISSION:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_screen);

			if (lock_screen (mfd_screen))
			{
				set_block (0, 0, int_mfd_viewport_size - 1, int_mfd_viewport_size - 1, clear_mfd_colour);

				draw_mfd_layout_grid ();

				draw_mission_display_mfd ();

				unlock_screen (mfd_screen);
			}

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal ("Invalid main MFD mode = %d", mode);

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

			{
				int
					width;

   			if (application_video_width >= 1280)
				{
					width = 1280;
				}
				else
				{
					width = 640;
				}

				if ((application_video_width == width) || (get_global_unscaled_displays ()))
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
			}

			set_d3d_flat_shaded_textured_renderstate (mfd_screen);

      	////////////////////////////////////////
      	//

			colour.red				= MFD_COLOUR1.r;
			colour.green			= MFD_COLOUR1.g;
			colour.blue				= MFD_COLOUR1.b;
			colour.alpha			= MFD_COLOUR1.a;

			specular.red			= 0;
			specular.green			= 0;
			specular.blue			= 0;
			specular.alpha			= 255;

			quad[0].i				= mfd_screen_x_min;
			quad[0].j	  			= mfd_screen_y_min;
			quad[0].z	  			= 0.5;
			quad[0].q	  			= 0.5;
			quad[0].u	  			= 0.0;
			quad[0].v	  			= 0.0;

			quad[1].i				= mfd_screen_x_max;
			quad[1].j  				= mfd_screen_y_min;
			quad[1].z  				= 0.5;
			quad[1].q  				= 0.5;
			quad[1].u  				= 1.0;
			quad[1].v  				= 0.0;

			quad[2].i				= mfd_screen_x_max;
			quad[2].j 				= mfd_screen_y_max;
			quad[2].z  				= 0.5;
			quad[2].q  				= 0.5;
			quad[2].u  				= 1.0;
			quad[2].v  				= 1.0;

			quad[3].i				= mfd_screen_x_min;
			quad[3].j				= mfd_screen_y_max;
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

	////////////////////////////////////////
	//
	// restore colours
	//
	////////////////////////////////////////

	MFD_COLOUR1					= store_colour1;
	MFD_COLOUR2					= store_colour2;
	MFD_COLOUR3					= store_colour3;
	MFD_COLOUR4					= store_colour4;
	MFD_COLOUR5					= store_colour5;
	MFD_COLOUR6					= store_colour6;
	MFD_CONTOUR_COLOUR      = store_contour_colour;
	MFD_RIVER_COLOUR			= store_river_colour;
	MFD_ROAD_COLOUR			= store_road_colour;
   MFD_BACKGROUND_COLOUR	= store_background_colour;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

void draw_overlaid_ka50_mfd (void)
{
#ifndef OGRE_EE
	////////////////////////////////////////
	//
	// SELECT LARGE OR SMALL MFD TEXTURES
	//
	////////////////////////////////////////

   if (application_video_width >= 1280)
   {
		draw_large_mfd = TRUE;

		shkval_mfd_texture_screen = large_shkval_mfd_texture_screen;
		abris_mfd_texture_screen = large_abris_mfd_texture_screen;
		ekran_display_texture_screen = large_ekran_display_texture_screen;
		cannon_rounds_display_texture_screen = cannon_rounds_display_screen;

		eo_3d_texture_screen = large_eo_3d_texture_screen;
		eo_3d_texture_screen_over = large_eo_3d_texture_screen_over;
   }
   else
   {
		draw_large_mfd = FALSE;

		shkval_mfd_texture_screen = small_shkval_mfd_texture_screen;
		abris_mfd_texture_screen = small_abris_mfd_texture_screen;
		ekran_display_texture_screen = small_ekran_display_texture_screen;
		cannon_rounds_display_texture_screen = cannon_rounds_display_screen;

		eo_3d_texture_screen = small_eo_3d_texture_screen;
		eo_3d_texture_screen_over = small_eo_3d_texture_screen_over;
   }

	set_system_texture_screen (shkval_mfd_texture_screen, TEXTURE_INDEX_HOKUM_COCKPIT_MFD_LHS_2);
	set_system_texture_screen (abris_mfd_texture_screen, TEXTURE_INDEX_HOKUM_COCKPIT_MFD_LHS_1);
	set_system_texture_screen (ekran_display_texture_screen, TEXTURE_INDEX_HOKUM_COCKPIT_EKRAN);
	set_system_texture_screen (cannon_rounds_display_texture_screen, TEXTURE_INDEX_COMANCHE_MFD1);

	////////////////////////////////////////
	//
	// SET UP MFD 2D ENVIRONMENT
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
	{
		mfd_viewport_size = LARGE_MFD_VIEWPORT_SIZE;

		int_mfd_viewport_size = LARGE_MFD_VIEWPORT_SIZE;
	}
	else
	{
		mfd_viewport_size = SMALL_MFD_VIEWPORT_SIZE;

		int_mfd_viewport_size = SMALL_MFD_VIEWPORT_SIZE;
	}

	mfd_viewport_x_org = mfd_viewport_size * 0.5;

	mfd_viewport_y_org = mfd_viewport_size * 0.5;

	mfd_viewport_x_min = 0.0;

	mfd_viewport_y_min = 0.0;

	mfd_viewport_x_max = mfd_viewport_size;

	mfd_viewport_y_max = mfd_viewport_size;

	////////////////////////////////////////
	//
	// DRAW DISPLAYS
	//
	////////////////////////////////////////

	draw_overlaid_mfd (shkval_mfd_texture_screen, shkval_mfd_mode, KA50_MFD_LOCATION_SHKVAL);

	draw_overlaid_mfd (abris_mfd_texture_screen, abris_mfd_mode, KA50_MFD_LOCATION_ABRIS);
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// EVENTS & MFD SWITCHING
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static ka50_mfd_modes get_mfd_mode_for_eo_sensor (void)
{
	ka50_mfd_modes
		mfd_mode;

	if (eo_sensor == TARGET_ACQUISITION_SYSTEM_FLIR)		//  Javelin  7/19
	{
		mfd_mode = KA50_MFD_MODE_FLIR;
	}
	else if (eo_sensor == TARGET_ACQUISITION_SYSTEM_LLLTV)
	{
		mfd_mode = KA50_MFD_MODE_LLLTV;
	}
	else
	{
		debug_fatal ("Invalid EO sensor = %d", eo_sensor);
	}

	return (mfd_mode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static ka50_mfd_modes get_default_mfd_mode (ka50_mfd_locations mfd_location)
{
	ka50_mfd_modes
		mfd_mode;

	ASSERT (ka50_mfd_location_valid (mfd_location));

	switch (mfd_location)
	{
		////////////////////////////////////////
		case KA50_MFD_LOCATION_SHKVAL:
		////////////////////////////////////////
		{
			mfd_mode = KA50_MFD_MODE_LLLTV;

			break;
		}
		////////////////////////////////////////
		case KA50_MFD_LOCATION_ABRIS:
		////////////////////////////////////////
		{
			mfd_mode = KA50_MFD_MODE_TSD;

			break;
		}
		////////////////////////////////////////
	}

	return (mfd_mode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_mfd_damage (ka50_mfd_locations mfd_location)
{
	int
		damage;

	ASSERT (ka50_mfd_location_valid (mfd_location));

	switch (mfd_location)
	{
		////////////////////////////////////////
		case KA50_MFD_LOCATION_SHKVAL:
		////////////////////////////////////////
		{
			damage = ka50_damage.shkval_mfd;

			break;
		}
		////////////////////////////////////////
		case KA50_MFD_LOCATION_ABRIS:
		////////////////////////////////////////
		{
			damage = ka50_damage.abris_mfd;

			break;
		}
		////////////////////////////////////////
	}

	return (damage);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_ka50_mfd_mode (ka50_mfd_modes mfd_mode, ka50_mfd_locations mfd_location)
{
	ka50_mfd_modes
		*mfd_mode_ptr1;

	ASSERT (ka50_mfd_mode_valid (mfd_mode));

	ASSERT (ka50_mfd_location_valid (mfd_location));

	debug_colour_log (DEBUG_COLOUR_AMBER, "%s = %s", ka50_mfd_location_names[mfd_location], ka50_mfd_mode_names[mfd_mode]);

	mfd_mode_ptr1 = mfd_mode_ptrs[mfd_location];

	if ((mfd_mode == KA50_MFD_MODE_DAMAGED) && (*mfd_mode_ptr1 == KA50_MFD_MODE_OFF))
	{
		mfd_mode = KA50_MFD_MODE_OFF;
	}

	if (get_mfd_damage (mfd_location))
	{
		if (mfd_mode != KA50_MFD_MODE_OFF)
		{
			mfd_mode = KA50_MFD_MODE_DAMAGED;
		}
	}

	*mfd_mode_ptr1 = mfd_mode;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static ka50_mfd_modes get_next_mfd_mode (ka50_mfd_modes mfd_mode, ka50_mfd_locations mfd_location)
{
	ka50_mfd_modes
		next_mfd_mode;

	ASSERT (ka50_mfd_mode_valid (mfd_mode));

	ASSERT (ka50_mfd_location_valid (mfd_location));

	switch (mfd_mode)
	{
		////////////////////////////////////////
		case KA50_MFD_MODE_OFF:
		////////////////////////////////////////
		{
			next_mfd_mode = get_default_mfd_mode (mfd_location);

			break;
		}
		////////////////////////////////////////
		case KA50_MFD_MODE_DAMAGED:
		////////////////////////////////////////
		{
			next_mfd_mode = KA50_MFD_MODE_DAMAGED;

			break;
		}
		////////////////////////////////////////
		case KA50_MFD_MODE_FLIR:					//  Javelin  7/19
		////////////////////////////////////////
		{
			next_mfd_mode = KA50_MFD_MODE_LLLTV;

			break;
		}
		////////////////////////////////////////
		case KA50_MFD_MODE_LLLTV:					//  Javelin  7/19
		////////////////////////////////////////
		{
			next_mfd_mode = KA50_MFD_MODE_FLIR;

			break;
		}
		////////////////////////////////////////
		case KA50_MFD_MODE_TSD:
		////////////////////////////////////////
		{
			next_mfd_mode = KA50_MFD_MODE_ASE;

			break;
		}
		////////////////////////////////////////
		case KA50_MFD_MODE_ASE:
		////////////////////////////////////////
		{
			next_mfd_mode = KA50_MFD_MODE_WEAPON;

			break;
		}
		////////////////////////////////////////
		case KA50_MFD_MODE_WEAPON:
		////////////////////////////////////////
		{
			next_mfd_mode = KA50_MFD_MODE_SYSTEM;

			break;
		}
		////////////////////////////////////////
		case KA50_MFD_MODE_SYSTEM:
		////////////////////////////////////////
		{
			next_mfd_mode = KA50_MFD_MODE_ENGINE;

			break;
		}
		////////////////////////////////////////
		case KA50_MFD_MODE_ENGINE:
		////////////////////////////////////////
		{
			next_mfd_mode = KA50_MFD_MODE_FLIGHT;

			break;
		}
		////////////////////////////////////////
		case KA50_MFD_MODE_FLIGHT:
		////////////////////////////////////////
		{
			next_mfd_mode = KA50_MFD_MODE_MISSION;

			break;
		}
		////////////////////////////////////////
		case KA50_MFD_MODE_MISSION:
		////////////////////////////////////////
		{
			next_mfd_mode = KA50_MFD_MODE_TSD;

			break;
		}
		default:
		{
			debug_fatal ( "Next Ka-50 MFD mode for %i", mfd_mode );

			next_mfd_mode = mfd_mode;

			break;
		}
	}

	return (next_mfd_mode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static ka50_mfd_modes get_previous_mfd_mode (ka50_mfd_modes mfd_mode, ka50_mfd_locations mfd_location)
{
	ka50_mfd_modes
		previous_mfd_mode;

	ASSERT (ka50_mfd_mode_valid (mfd_mode));

	ASSERT (ka50_mfd_location_valid (mfd_location));

	switch (mfd_mode)
	{
		////////////////////////////////////////
		case KA50_MFD_MODE_OFF:
		////////////////////////////////////////
		{
			previous_mfd_mode = get_default_mfd_mode (mfd_location);

			break;
		}
		////////////////////////////////////////
		case KA50_MFD_MODE_DAMAGED:
		////////////////////////////////////////
		{
			previous_mfd_mode = KA50_MFD_MODE_DAMAGED;

			break;
		}
		////////////////////////////////////////
		case KA50_MFD_MODE_FLIR:					//  Javelin  7/19
		////////////////////////////////////////
		{
			previous_mfd_mode = KA50_MFD_MODE_LLLTV;

			break;
		}
		////////////////////////////////////////
		case KA50_MFD_MODE_LLLTV:					//  Javelin  7/19
		////////////////////////////////////////
		{
			previous_mfd_mode = KA50_MFD_MODE_FLIR;

			break;
		}
		////////////////////////////////////////
		case KA50_MFD_MODE_TSD:
		////////////////////////////////////////
		{
			previous_mfd_mode = KA50_MFD_MODE_MISSION;

			break;
		}
		////////////////////////////////////////
		case KA50_MFD_MODE_ASE:
		////////////////////////////////////////
		{
			previous_mfd_mode = KA50_MFD_MODE_TSD;

			break;
		}
		////////////////////////////////////////
		case KA50_MFD_MODE_WEAPON:
		////////////////////////////////////////
		{
			previous_mfd_mode = KA50_MFD_MODE_ASE;

			break;
		}
		////////////////////////////////////////
		case KA50_MFD_MODE_SYSTEM:
		////////////////////////////////////////
		{
			previous_mfd_mode = KA50_MFD_MODE_WEAPON;

			break;
		}
		////////////////////////////////////////
		case KA50_MFD_MODE_ENGINE:
		////////////////////////////////////////
		{
			previous_mfd_mode = KA50_MFD_MODE_SYSTEM;

			break;
		}
		////////////////////////////////////////
		case KA50_MFD_MODE_FLIGHT:
		////////////////////////////////////////
		{
			previous_mfd_mode = KA50_MFD_MODE_ENGINE;

			break;
		}
		////////////////////////////////////////
		case KA50_MFD_MODE_MISSION:
		////////////////////////////////////////
		{
			previous_mfd_mode = KA50_MFD_MODE_FLIGHT;

			break;
		}
		default:
		{
			debug_fatal ( "Previous Ka-50 MFD mode for %i", mfd_mode );

			previous_mfd_mode = mfd_mode;

			break;
		}
	}

	return (previous_mfd_mode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_next_ka50_mfd (ka50_mfd_locations mfd_location)
{
	ka50_mfd_modes
		*mfd_mode_ptr1,
		next_mfd_mode;

	ASSERT (ka50_mfd_location_valid (mfd_location));

	mfd_mode_ptr1 = mfd_mode_ptrs[mfd_location];

	next_mfd_mode = get_next_mfd_mode (*mfd_mode_ptr1, mfd_location);

	select_ka50_mfd_mode (next_mfd_mode, mfd_location);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_previous_ka50_mfd (ka50_mfd_locations mfd_location)
{
	ka50_mfd_modes
		*mfd_mode_ptr1,
		previous_mfd_mode;

	ASSERT (ka50_mfd_location_valid (mfd_location));

	mfd_mode_ptr1 = mfd_mode_ptrs[mfd_location];

	previous_mfd_mode = get_previous_mfd_mode (*mfd_mode_ptr1, mfd_location);

	select_ka50_mfd_mode (previous_mfd_mode, mfd_location);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void toggle_ka50_mfd_on_off (ka50_mfd_locations mfd_location)
{
	ASSERT (ka50_mfd_location_valid (mfd_location));

	if (*mfd_mode_ptrs[mfd_location] != KA50_MFD_MODE_OFF)
	{
		select_ka50_mfd_mode (KA50_MFD_MODE_OFF, mfd_location);
	}
	else
	{
		select_next_ka50_mfd (mfd_location);
	}
}

ka50_mfd_modes get_ka50_mfd_mode (ka50_mfd_locations mfd_location)
{
	ASSERT (ka50_mfd_location_valid (mfd_location));

	return *mfd_mode_ptrs[mfd_location];
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_next_ka50_tsd_ase_range (void)
{
	if (tsd_ase_range == TSD_ASE_RANGE_2000)
	{
		tsd_ase_range = TSD_ASE_RANGE_5000;
	}
	else if (tsd_ase_range == TSD_ASE_RANGE_5000)
	{
		tsd_ase_range = TSD_ASE_RANGE_10000;
	}
	else if (tsd_ase_range == TSD_ASE_RANGE_10000)
	{
		tsd_ase_range = TSD_ASE_RANGE_25000;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_previous_ka50_tsd_ase_range (void)
{
	if (tsd_ase_range == TSD_ASE_RANGE_25000)
	{
		tsd_ase_range = TSD_ASE_RANGE_10000;
	}
	else if (tsd_ase_range == TSD_ASE_RANGE_10000)
	{
		tsd_ase_range = TSD_ASE_RANGE_5000;
	}
	else if (tsd_ase_range == TSD_ASE_RANGE_5000)
	{
		tsd_ase_range = TSD_ASE_RANGE_2000;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_next_ka50_tsd_declutter_level (void)
{
	if (tsd_declutter_level == TSD_DECLUTTER_LEVEL_ALL)
	{
		tsd_declutter_level = TSD_DECLUTTER_LEVEL_TARGET;
	}
	else if (tsd_declutter_level == TSD_DECLUTTER_LEVEL_TARGET)
	{
		tsd_declutter_level = TSD_DECLUTTER_LEVEL_NAVIGATION;
	}
	else
	{
		tsd_declutter_level = TSD_DECLUTTER_LEVEL_ALL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_previous_ka50_tsd_declutter_level (void)
{
	if (tsd_declutter_level == TSD_DECLUTTER_LEVEL_NAVIGATION)
	{
		tsd_declutter_level = TSD_DECLUTTER_LEVEL_TARGET;
	}
	else if (tsd_declutter_level == TSD_DECLUTTER_LEVEL_TARGET)
	{
		tsd_declutter_level = TSD_DECLUTTER_LEVEL_ALL;
	}
	else
	{
		tsd_declutter_level = TSD_DECLUTTER_LEVEL_NAVIGATION;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void toggle_ka50_ase_auto_page (void)
{
	set_global_ase_auto_page (get_global_ase_auto_page () ^ 1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void auto_page_ka50_ase_mfd (void)
{
	if (!get_global_ase_auto_page ())
	{
		return;
	}

	if (abris_mfd_mode == KA50_MFD_MODE_ASE)
	{
		return;
	}

	if (!ka50_damage.abris_mfd)
	{
		select_ka50_mfd_mode (KA50_MFD_MODE_ASE, KA50_MFD_LOCATION_ABRIS);

		return;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_ka50_eo_mfd (target_acquisition_systems system)		//  Javelin  7/19
{
	switch (system)
	{
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_OFF:
		////////////////////////////////////////
		{
			select_ka50_mfd_mode (KA50_MFD_MODE_OFF, KA50_MFD_LOCATION_SHKVAL);
			return;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_FLIR:		
		////////////////////////////////////////
		{
			select_ka50_mfd_mode (KA50_MFD_MODE_FLIR, KA50_MFD_LOCATION_SHKVAL);
			return;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_LLLTV:
		////////////////////////////////////////
		{
			select_ka50_mfd_mode (KA50_MFD_MODE_LLLTV, KA50_MFD_LOCATION_SHKVAL);
			return;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_HMS:
		////////////////////////////////////////
		{
			return;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal ("Invalid shkval targeting system = %d", system);
			return;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#undef OLD_EO
