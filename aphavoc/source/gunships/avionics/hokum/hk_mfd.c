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

#ifdef DEBUG

static char
	*hokum_mfd_mode_names[NUM_HOKUM_MFD_MODES] =
	{
		"HOKUM_MFD_MODE_OFF",
		"HOKUM_MFD_MODE_DAMAGED",
		"HOKUM_MFD_MODE_GROUND_RADAR",
		"HOKUM_MFD_MODE_AIR_RADAR",
		"HOKUM_MFD_MODE_FLIR",
		"HOKUM_MFD_MODE_LLLTV",
		"HOKUM_MFD_MODE_PERISCOPE",
		"HOKUM_MFD_MODE_TSD",
		"HOKUM_MFD_MODE_ASE",
		"HOKUM_MFD_MODE_WEAPON",
		"HOKUM_MFD_MODE_SYSTEM",
		"HOKUM_MFD_MODE_ENGINE",
		"HOKUM_MFD_MODE_FLIGHT",
		"HOKUM_MFD_MODE_MISSION",
	};

static char
	*hokum_mfd_location_names[NUM_HOKUM_MFD_LOCATIONS] =
	{
		"HOKUM_MFD_LOCATION_PILOT_LHS",
		"HOKUM_MFD_LOCATION_PILOT_RHS",
		"HOKUM_MFD_LOCATION_CO_PILOT_LHS",
		"HOKUM_MFD_LOCATION_CO_PILOT_RHS",
	};

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static hokum_mfd_modes
	pilot_lhs_mfd_mode			= HOKUM_MFD_MODE_OFF,
	pilot_rhs_mfd_mode			= HOKUM_MFD_MODE_OFF,
	co_pilot_lhs_mfd_mode		= HOKUM_MFD_MODE_OFF,
	co_pilot_rhs_mfd_mode		= HOKUM_MFD_MODE_OFF;

static hokum_mfd_modes
	*mfd_mode_ptrs[NUM_HOKUM_MFD_LOCATIONS] =
	{
		&pilot_lhs_mfd_mode,						// HOKUM_MFD_LOCATION_PILOT_LHS
		&pilot_rhs_mfd_mode,						// HOKUM_MFD_LOCATION_PILOT_RHS
		&co_pilot_lhs_mfd_mode,					// HOKUM_MFD_LOCATION_CO_PILOT_LHS
		&co_pilot_rhs_mfd_mode,					// HOKUM_MFD_LOCATION_CO_PILOT_RHS
	};

static hokum_mfd_modes
	*opposite_mfd_mode_ptrs[NUM_HOKUM_MFD_LOCATIONS] =
	{
		&pilot_rhs_mfd_mode,						// HOKUM_MFD_LOCATION_PILOT_LHS
		&pilot_lhs_mfd_mode,						// HOKUM_MFD_LOCATION_PILOT_RHS
		&co_pilot_rhs_mfd_mode,					// HOKUM_MFD_LOCATION_CO_PILOT_LHS
		&co_pilot_lhs_mfd_mode,					// HOKUM_MFD_LOCATION_CO_PILOT_RHS
	};

static hokum_mfd_locations
	opposite_mfd_locations[NUM_HOKUM_MFD_LOCATIONS] =
	{
		HOKUM_MFD_LOCATION_PILOT_RHS,			// HOKUM_MFD_LOCATION_PILOT_LHS
		HOKUM_MFD_LOCATION_PILOT_LHS,			// HOKUM_MFD_LOCATION_PILOT_RHS
		HOKUM_MFD_LOCATION_CO_PILOT_RHS,		// HOKUM_MFD_LOCATION_CO_PILOT_LHS
		HOKUM_MFD_LOCATION_CO_PILOT_LHS,		// HOKUM_MFD_LOCATION_CO_PILOT_RHS
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static rgb_colour
	mfd_colours[13];

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
#define MFD_CLEAR_COLOUR		(mfd_colours[10])
#define MFD_COLOUR7				(mfd_colours[11])
#define MFD_COLOUR8				(mfd_colours[12])

static rgb_colour
   clear_mfd_colour;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static rgb_colour
	text_display_colours[2];

#define TEXT_COLOUR1					(text_display_colours[0])
#define TEXT_BACKGROUND_COLOUR	(text_display_colours[1])

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define PILOT_LHS_MFD		(1 << 0)
#define PILOT_RHS_MFD		(1 << 1)
#define CO_PILOT_LHS_MFD	(1 << 2)
#define CO_PILOT_RHS_MFD	(1 << 3)
#define EKRAN_DISPLAY		(1 << 4)

static int
	display_mask;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
	*pilot_lhs_mfd_texture_screen,
	*pilot_rhs_mfd_texture_screen,
	*co_pilot_lhs_mfd_texture_screen,
	*co_pilot_rhs_mfd_texture_screen,
	*ekran_display_texture_screen,
	*large_pilot_lhs_mfd_texture_screen,
	*large_pilot_rhs_mfd_texture_screen,
	*large_co_pilot_lhs_mfd_texture_screen,
	*large_co_pilot_rhs_mfd_texture_screen,
	*large_ekran_display_texture_screen,
	*small_pilot_lhs_mfd_texture_screen,
	*small_pilot_rhs_mfd_texture_screen,
	*small_co_pilot_lhs_mfd_texture_screen,
	*small_co_pilot_rhs_mfd_texture_screen,
	*small_ekran_display_texture_screen,
	*eo_3d_texture_screen,
	*full_mfd_texture_screen;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define TEXT_DISPLAY_MAX_STRING_LENGTH	(10)

static char
	text_display_line1[TEXT_DISPLAY_MAX_STRING_LENGTH + 1],
	text_display_line2[TEXT_DISPLAY_MAX_STRING_LENGTH + 1],
	text_display_line3[TEXT_DISPLAY_MAX_STRING_LENGTH + 1];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//
// HEADING SCALE
//
////////////////////////////////////////

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

static char large_command_heading_carat[] =
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
	pilot_tsd_ase_range,
	co_pilot_tsd_ase_range;

enum TSD_DECLUTTER_LEVELS
{
	TSD_DECLUTTER_LEVEL_ALL,
	TSD_DECLUTTER_LEVEL_TARGET,
	TSD_DECLUTTER_LEVEL_NAVIGATION,
	NUM_TSD_DECLUTTER_LEVELS
};

typedef enum TSD_DECLUTTER_LEVELS tsd_declutter_levels;

static tsd_declutter_levels
	pilot_tsd_declutter_level,
	co_pilot_tsd_declutter_level;

#define TSD_THREAT_LINE_FLASH_RATE	(0.1)

static float
	pilot_tsd_threat_line_flash_timer,
	co_pilot_tsd_threat_line_flash_timer;

static int
	pilot_tsd_draw_threat_line_status,
	co_pilot_tsd_draw_threat_line_status;

#define ASE_THREAT_LINE_FLASH_RATE	(0.1)

static float
	pilot_ase_threat_line_flash_timer,
	co_pilot_ase_threat_line_flash_timer;

static int
	pilot_ase_draw_threat_line_status,
	co_pilot_ase_draw_threat_line_status;

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

static hokum_mfd_modes get_mfd_mode_for_eo_sensor (void);

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

	set_2d_window (mfd_env, MFD_WINDOW_X_MIN * 0.5, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX * 0.5, MFD_WINDOW_Y_MAX);

	mfd_vp_x_min = mfd_viewport_x_org - (mfd_viewport_size * (0.5 * 0.5));

	mfd_vp_x_max = mfd_viewport_x_org + (mfd_viewport_size * (0.5 * 0.5)) - 0.001;

	set_2d_viewport (mfd_env, mfd_vp_x_min, mfd_viewport_y_min, mfd_vp_x_max, mfd_viewport_y_max);

	//
	// large and small MFD position
	//

	if (draw_large_mfd)
	{
		y_position = 0.85;
	}
	else
	{
		y_position = 0.8375;
	}

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

		draw_mono_sprite (large_heading_scale_datum, i, j + 1.0, MFD_COLOUR1);
	}
	else
	{
		set_mono_font_type (MONO_FONT_TYPE_5X7);

		draw_mono_sprite (small_heading_scale_datum, i, j + 1.0, MFD_COLOUR1);
	}

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

				command_heading = bound (command_heading, rad (-90.0), rad (90.0));

				if (draw_large_mfd)
				{
					get_2d_float_screen_coordinates (command_heading * ((0.5 - 0.04) / rad (90.0)), y_position, &i, &j);

					draw_mono_sprite (large_command_heading_carat, i, j + 1.0, MFD_COLOUR1);
				}
				else
				{
					get_2d_float_screen_coordinates (command_heading * ((0.5 - 0.05) / rad (90.0)), y_position, &i, &j);

					draw_mono_sprite (small_command_heading_carat, i, j + 1.0, MFD_COLOUR1);
				}
			}
		}
	}

	//
	// sort first major tick position (draw 2 major ticks either side of centre)
	//

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
//
// FIELD OF REGARD AND VIEW BOXES
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_field_of_regard_and_view_boxes (void)
{
	float
		x,
		y;

	if (draw_large_mfd)
	{
		draw_2d_line (-0.3000, -0.6500,  0.3000, -0.6500, MFD_COLOUR1);
		draw_2d_line (-0.3000, -0.8682,  0.3000, -0.8682, MFD_COLOUR1);
		draw_2d_line (-0.3000, -0.6500, -0.3000, -0.8682, MFD_COLOUR1);
		draw_2d_line ( 0.3000, -0.6500,  0.3000, -0.8682, MFD_COLOUR1);

		draw_2d_line ( 0.0000, -0.6500,  0.0000, -0.6700, MFD_COLOUR1);
		draw_2d_line (-0.2454, -0.6500, -0.2454, -0.6700, MFD_COLOUR1);
		draw_2d_line ( 0.2454, -0.6500,  0.2454, -0.6700, MFD_COLOUR1);

		draw_2d_line ( 0.0000, -0.8482,  0.0000, -0.8682, MFD_COLOUR1);
		draw_2d_line (-0.2454, -0.8482, -0.2454, -0.8682, MFD_COLOUR1);
		draw_2d_line ( 0.2454, -0.8482,  0.2454, -0.8682, MFD_COLOUR1);

		draw_2d_line (-0.3000, -0.7046, -0.2800, -0.7046, MFD_COLOUR1);
		draw_2d_line ( 0.3000, -0.7046,  0.2800, -0.7046, MFD_COLOUR1);

		x = eo_azimuth / eo_max_azimuth * 0.3;
		y = (eo_elevation / eo_min_elevation * -0.1636) - 0.7046;

		draw_2d_circle (x, y, 0.04, MFD_COLOUR1);
	}
	else
	{
		draw_2d_line (-0.2000, -0.7250,  0.2000, -0.7250, MFD_COLOUR1);
		draw_2d_line (-0.2000, -0.8705,  0.2000, -0.8705, MFD_COLOUR1);
		draw_2d_line (-0.2000, -0.7250, -0.2000, -0.8705, MFD_COLOUR1);
		draw_2d_line ( 0.2000, -0.7250,  0.2000, -0.8705, MFD_COLOUR1);

		draw_2d_line ( 0.0000, -0.7250,  0.0000, -0.7475, MFD_COLOUR1);
		draw_2d_line (-0.1636, -0.7250, -0.1636, -0.7475, MFD_COLOUR1);
		draw_2d_line ( 0.1636, -0.7250,  0.1636, -0.7475, MFD_COLOUR1);

		draw_2d_line ( 0.0000, -0.8480,  0.0000, -0.8705, MFD_COLOUR1);
		draw_2d_line (-0.1636, -0.8480, -0.1636, -0.8705, MFD_COLOUR1);
		draw_2d_line ( 0.1636, -0.8480,  0.1636, -0.8705, MFD_COLOUR1);

		draw_2d_line (-0.2000, -0.7614, -0.1775, -0.7614, MFD_COLOUR1);
		draw_2d_line ( 0.2000, -0.7614,  0.1775, -0.7614, MFD_COLOUR1);

		x = eo_azimuth / eo_max_azimuth * 0.2;
		y = (eo_elevation / eo_min_elevation * -0.1091) - 0.7614;

		draw_2d_circle (x, y, 0.04, MFD_COLOUR1);
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
		width,
		y_adjust;

	if (scan_range == HOKUM_RADAR_SCAN_RANGE_1000)
	{
//		s = "1Km";
		sprintf(s,"%.0fKm",HOKUM_RADAR_SCAN_RANGE_1000/1000);
	}
	else if (scan_range == HOKUM_RADAR_SCAN_RANGE_2000)
	{
//		s = "2Km";
		sprintf(s,"%.0fKm",HOKUM_RADAR_SCAN_RANGE_2000/1000);
	}
	else if (scan_range == HOKUM_RADAR_SCAN_RANGE_4000)
	{
//		s = "4Km";
		sprintf(s,"%.0fKm",HOKUM_RADAR_SCAN_RANGE_4000/1000);
	}
	else if (scan_range == HOKUM_RADAR_SCAN_RANGE_6000)
	{
//		s = "6Km";
		sprintf(s,"%.0fKm",HOKUM_RADAR_SCAN_RANGE_6000/1000);
	}
	else if (scan_range == HOKUM_RADAR_SCAN_RANGE_10000)
	{
//		s = "10Km";
		sprintf(s,"%.0fKm",HOKUM_RADAR_SCAN_RANGE_10000/1000);
	}
	else
	{
//		s = "XXX";
		sprintf(s,"XXX");
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

	if (hokum_damage.radar)
	{
		return;
	}

	if (draw_large_mfd)
	{
		y_adjust = -12.0;
	}
	else
	{
		y_adjust = -5.0;
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

		if ((target_range < 1000.0) && (!hokum_damage.laser_designator))
		{
			sprintf (buffer, "%dm", (int) target_range);
		}
		else
		{
			sprintf (buffer, "%.1fKm", target_range * (1.0 / 1000.0));
		}

		width = get_mono_font_string_width (buffer);

		if (draw_large_mfd)
		{
			width += 2.0;
		}
		else
		{
			width += 1.0;
		}

		set_2d_mono_font_position (1.0, -1.0);

		set_mono_font_rel_position (-width, y_adjust);

		print_mono_font_string (buffer);

		//
		// no line of sight
		//

		if (!get_local_entity_int_value (target, INT_TYPE_GUNSHIP_RADAR_LOS_CLEAR))
		{
			width = get_mono_font_string_width ("NO LOS");

			if (draw_large_mfd)
			{
				width += 2.0;

				y_adjust = -25.0;
			}
			else
			{
				width += 1.0;

				y_adjust = -12.0;
			}

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
			y_adjust = 18.0;
		}
		else
		{
			y_adjust = 9.0;
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

	num_segments = (int) (arc_size * (1.0 / HOKUM_RADAR_SCAN_ARC_SEGMENT_SIZE));

	if (num_segments > 0)
	{
		theta = arc_size * 0.5;

		sine_cosine (theta, &sin_theta, &cos_theta);

		x1 = -radius * sin_theta;
		y1 = radius * cos_theta;

		while (num_segments--)
		{
			theta -= HOKUM_RADAR_SCAN_ARC_SEGMENT_SIZE;

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
	source_side = get_local_entity_int_value (source, INT_TYPE_SIDE);
	
	target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

	dx = (target_position->x - source_position->x) * scale;
	dy = (target_position->z - source_position->z) * scale;

	target_symbol_type = get_local_entity_int_value (target, INT_TYPE_TARGET_SYMBOL_TYPE);

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
					target_symbol_colour = MFD_COLOUR1;
				else
					target_symbol_colour = MFD_COLOUR3;
			}
			else
			{
					target_symbol_colour = MFD_COLOUR8;
			}
		}		
		else
			target_symbol_colour = MFD_COLOUR2;
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
					target_symbol_colour = MFD_COLOUR2;
				else
					target_symbol_colour = MFD_COLOUR4;
			}
			else
			{
					target_symbol_colour = MFD_COLOUR7;
			}
		}		
		else
			target_symbol_colour = MFD_COLOUR1;
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
/*
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

	target_symbol_type = get_local_entity_int_value (target, INT_TYPE_TARGET_SYMBOL_TYPE);

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
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GROUND RADAR
//
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
		radius = max (50.0, radius);

		draw_2d_hatched_circle (dx, dy, radius * scale, MFD_COLOUR5);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define RADIUS	(ROOT2 - 0.05)

static void draw_ground_radar_mfd (void)
{
	float
		y_adjust,
		u,
		v,
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

	source_heading = get_local_entity_float_value (source, FLOAT_TYPE_HEADING);

	scale = RADIUS / ground_radar.scan_range;

	if (draw_large_mfd)
	{
		get_2d_float_screen_coordinates (0.0, -0.6, &u, &v);
	}
	else
	{
		get_2d_float_screen_coordinates (0.0, -0.675, &u, &v);
	}

	u -= mfd_viewport_x_min;
	v -= mfd_viewport_y_min;

	////////////////////////////////////////
	//
	// draw radar clutter
	//
	////////////////////////////////////////

	if (!hokum_damage.radar)
	{
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
	}

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

	if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_GROUND_RADAR)
	{
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
	}

	////////////////////////////////////////
	//
	// draw heading scale
	//
	////////////////////////////////////////

	draw_heading_scale (get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_HEADING), FALSE);

	////////////////////////////////////////
	//
	// draw field of regard and view boxes
	//
	////////////////////////////////////////

	draw_field_of_regard_and_view_boxes ();

	////////////////////////////////////////
	//
	// line graphics
	//
	////////////////////////////////////////

	set_2d_viewport_origin (mfd_env, u, v);

	//
	// max scan limits
	//

	draw_2d_line (0.0, 0.0, -0.965, 0.965, MFD_COLOUR4);

	draw_2d_line (0.0, 0.0, 0.965, 0.965, MFD_COLOUR4);

	draw_radar_arc (HOKUM_RADAR_SCAN_ARC_SIZE_90, RADIUS, MFD_COLOUR4);

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

	if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_GROUND_RADAR)
	{
		set_2d_window_rotation (mfd_env, -(ground_radar.scan_datum + ground_radar.sweep_offset));

		draw_2d_line (0.0, 0.0, 0.0, RADIUS, MFD_COLOUR1);
	}

	set_2d_window_rotation (mfd_env, 0.0);

	////////////////////////////////////////
	//
	// targets
	//
	////////////////////////////////////////

	if (!hokum_damage.radar)
	{
		set_2d_window_rotation (mfd_env, source_heading);

		target = get_local_entity_first_child (source, LIST_TYPE_GUNSHIP_TARGET);

		while (target)
		{
			if (get_gunship_target_valid_for_ground_radar (target))
			{
				if (get_target_matches_ground_radar_declutter_criteria (target))
				{
//VJ 030423 TSD render mod
					draw_radar_target_symbol (target, source_position, scale, FALSE, FALSE);
				}
			}

			target = get_local_entity_child_succ (target, LIST_TYPE_GUNSHIP_TARGET);
		}

		//
		// draw selected target last
		//

		if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_GROUND_RADAR)
		{
			target = get_local_entity_parent (source, LIST_TYPE_TARGET);

			if (target)
			{
//VJ 030423 TSD render mod
				draw_radar_target_symbol (target, source_position, scale, TRUE, FALSE);
			}
		}

		set_2d_window_rotation (mfd_env, 0.0);
	}

	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

	////////////////////////////////////////
	//
	// damaged
	//
	////////////////////////////////////////

	if (hokum_damage.radar)
	{
		draw_2d_line (-0.5, -0.5,  0.5, 0.5, MFD_COLOUR1);
		draw_2d_line ( 0.5, -0.5, -0.5, 0.5, MFD_COLOUR1);
	}
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
		target_range,
		y_adjust;

	entity
		*source,
		*target;

	vec3d
		*source_position,
		*target_position;

	source = get_gunship_entity ();

	source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

	source_side = get_local_entity_int_value (source, INT_TYPE_SIDE);

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

	if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_AIR_RADAR)
	{
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
	}

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

	if (air_radar.scan_arc_size == HOKUM_RADAR_SCAN_ARC_SIZE_360)
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

	if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_AIR_RADAR)
	{
		set_2d_window_rotation (mfd_env, -(air_radar.scan_datum + air_radar.sweep_offset));

		draw_2d_line (0.0, 0.0, 0.0, RADIUS, MFD_COLOUR1);
	}

	set_2d_window_rotation (mfd_env, 0.0);

	////////////////////////////////////////
	//
	// draw targets
	//
	////////////////////////////////////////

	if (!hokum_damage.radar)
	{
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
//VJ 030423 TSD render mod
					draw_radar_target_symbol (target, source_position, scale, FALSE, FALSE);
				}
			}

			target = get_local_entity_child_succ (target, LIST_TYPE_GUNSHIP_TARGET);
		}

		//
		// draw selected target last
		//

		if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_AIR_RADAR)
		{
			target = get_local_entity_parent (source, LIST_TYPE_TARGET);

			if (target)
			{
//VJ 030423 TSD render mod				
				draw_radar_target_symbol (target, source_position, scale, TRUE, FALSE);
			}
		}

		set_2d_window_rotation (mfd_env, 0.0);
	}

	////////////////////////////////////////
	//
	// damaged
	//
	////////////////////////////////////////

	if (hokum_damage.radar)
	{
		draw_2d_line (-0.5, -0.5,  0.5, 0.5, MFD_COLOUR1);
		draw_2d_line ( 0.5, -0.5, -0.5, 0.5, MFD_COLOUR1);
	}
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

#define FULL_SCREEN_EO_RATIO	((float) (0.9))

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

////////////////////////////////////////
//
// PERISCOPE
//
////////////////////////////////////////

static display_3d_light_levels
	periscope_light_levels[WEATHERMODE_LAST][NUM_DAY_SEGMENT_TYPES] =
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
			DISPLAY_3D_LIGHT_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_LIGHT_LEVEL_HIGH,	 	// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_LIGHT_LEVEL_LOW, 		// DAY_SEGMENT_TYPE_DUSK
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
	periscope_noise_levels[WEATHERMODE_LAST][NUM_DAY_SEGMENT_TYPES] =
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

#if 0

static int get_eo_display_mode (hokum_mfd_modes mode)
{
	if
	(
		(mode == HOKUM_MFD_MODE_FLIR) ||
		(mode == HOKUM_MFD_MODE_LLLTV) ||
		(mode == HOKUM_MFD_MODE_PERISCOPE)
	)
	{
		return (TRUE);
	}

	return (FALSE);
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_undamaged_eo_display_mode (hokum_mfd_modes mode)
{
	if ((mode == HOKUM_MFD_MODE_FLIR) && (!hokum_damage.flir))
	{
		return (TRUE);
	}

	if ((mode == HOKUM_MFD_MODE_LLLTV) && (!hokum_damage.llltv))
	{
		return (TRUE);
	}

	if ((mode == HOKUM_MFD_MODE_PERISCOPE) && (!hokum_damage.periscope))
	{
		return (TRUE);
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_3d_eo_display (eo_params_dynamic_move *eo, target_acquisition_systems system)
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

	ASSERT (eo_3d_texture_screen);

#ifdef OLD_EO
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
#else
	zoom = convert_linear_view_value (eo);
#endif

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

			break;
		}
		case TARGET_ACQUISITION_SYSTEM_LLLTV:
		{
			light_level = llltv_light_levels[weather_mode][day_segment_type];

			noise_level = llltv_noise_levels[weather_mode][day_segment_type];

			break;
		}
		case TARGET_ACQUISITION_SYSTEM_PERISCOPE:
		{
			light_level = periscope_light_levels[weather_mode][day_segment_type];

			noise_level = periscope_noise_levels[weather_mode][day_segment_type];

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

	set_main_3d_params (DISPLAY_3D_TINT_ORANGE, light_level, noise_level, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_size, mfd_viewport_size, rad (59.99) * zoom, rad (59.99) * zoom);

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

		get_hokum_eo_relative_centred_viewpoint (&centered_eo_vp);

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

	finalise_3d_render_target_texture (eo_3d_texture_screen);

	set_3d_render_target (video_screen);

	set_active_screen (video_screen);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_full_screen_3d_eo_display (eo_params_dynamic_move *eo, target_acquisition_systems system, display_3d_tints tint)
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
#else
	zoom = convert_linear_view_value (eo);
#endif

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

			break;
		}
		case TARGET_ACQUISITION_SYSTEM_LLLTV:
		{
			light_level = llltv_light_levels[weather_mode][day_segment_type];

			noise_level = llltv_noise_levels[weather_mode][day_segment_type];

			break;
		}
		case TARGET_ACQUISITION_SYSTEM_PERISCOPE:
		{
			light_level = periscope_light_levels[weather_mode][day_segment_type];

			noise_level = periscope_noise_levels[weather_mode][day_segment_type];

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
		rad (59.99) * zoom
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

		get_hokum_eo_relative_centred_viewpoint (&centered_eo_vp);

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

static void draw_2d_eo_display (eo_params_dynamic_move *eo, target_acquisition_systems system, int damaged, int valid_3d)
{
	const char
		*s;
	char
		buffer[200];

	int
		heading_readout;

	float
		width,
		heading,
		marker_position,
		target_range,
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

	if (target)
	{
		target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

		target_range = get_3d_range (source_position, target_position);
	}

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

#ifdef OLD_EO
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
#else
	{
		float level = 1.0 / convert_linear_view_value (eo);

		if (level < 10)
		{
			sprintf (buffer, "%.1f", level);
		}
		else
		{
			sprintf (buffer, "%d", (int)level);
		}

		s = buffer;
	}
#endif

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

	if (target)
	{
		if ((target_range < 1000.0) && (!hokum_damage.laser_designator))
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

	if (eo_target_locked)
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

	if (target)
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
					transform_mfd_screen_co_ords_to_mfd_texture_co_ords (&i, &j);

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

static void draw_3d_flir_mfd (int full_screen)
{
	if (!hokum_damage.flir)
	{
		if (full_screen)
		{
			draw_full_screen_3d_eo_display (&hokum_flir, TARGET_ACQUISITION_SYSTEM_FLIR, DISPLAY_3D_TINT_ORANGE);
		}
		else
		{
			draw_3d_eo_display (&hokum_flir, TARGET_ACQUISITION_SYSTEM_FLIR);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_2d_flir_mfd (int valid_3d)
{
	draw_2d_eo_display (&hokum_flir, TARGET_ACQUISITION_SYSTEM_FLIR, hokum_damage.flir, valid_3d);
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
	if (!hokum_damage.llltv)
	{
		if (full_screen)
		{
			draw_full_screen_3d_eo_display (&hokum_llltv, TARGET_ACQUISITION_SYSTEM_LLLTV, DISPLAY_3D_TINT_ORANGE);
		}
		else
		{
			draw_3d_eo_display (&hokum_llltv, TARGET_ACQUISITION_SYSTEM_LLLTV);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_2d_llltv_mfd (int valid_3d)
{
	draw_2d_eo_display (&hokum_llltv, TARGET_ACQUISITION_SYSTEM_LLLTV, hokum_damage.llltv, valid_3d);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PERISCOPE
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_3d_periscope_mfd (int full_screen)
{
	if (!hokum_damage.periscope)
	{
		if (full_screen)
		{
			draw_full_screen_3d_eo_display (&hokum_periscope, TARGET_ACQUISITION_SYSTEM_PERISCOPE, DISPLAY_3D_TINT_ORANGE);
		}
		else
		{
			draw_3d_eo_display (&hokum_periscope, TARGET_ACQUISITION_SYSTEM_PERISCOPE);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_2d_periscope_mfd (int valid_3d)
{
	draw_2d_eo_display (&hokum_periscope, TARGET_ACQUISITION_SYSTEM_PERISCOPE, hokum_damage.periscope, valid_3d);
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
//VJ 030423 TSD render mod, code moved to co_tsd.c in ../common
/* 
static int
	contour_spacing,
	contour_samples;

#define OPTIMISE_CONTOURS	0

#define OPTIMISE_PATHS		0

#if OPTIMISE_CONTOURS

static int
	num_contour_loops,
	num_contour_lines;

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_contour_lines (vec3d *p1, vec3d *p2, vec3d *p3)
{
	int
		y,
		y1,
		y2,
		y3,
		dy,
		y_tmp,
		contour_samples_minus_one;

	float
		x1,
		z1,
		x2,
		z2,
		x3,
		z3,
		dx1,
		dz1,
		dx2,
		dz2,
		x_tmp,
		z_tmp,
		one_over_dy;

	x1 = p1->x;
	convert_float_to_int (p1->y, &y1);
	z1 = p1->z;

	x2 = p2->x;
	convert_float_to_int (p2->y, &y2);
	z2 = p2->z;

	x3 = p3->x;
	convert_float_to_int (p3->y, &y3);
	z3 = p3->z;

	//
	// ensure above sea level
	//

	y1 = max (y1, 0);

	y2 = max (y2, 0);

	y3 = max (y3, 0);

	//
	// scale height values for contour line spacing
	//

	y1 /= contour_spacing;
	y2 /= contour_spacing;
	y3 /= contour_spacing;

	contour_samples_minus_one = contour_samples - 1;

	//
	// check if flat
	//

	if ((y1 == y2) && (y2 == y3))
	{
		return;
	}

	//
	// sort height values (y1 = lowest, y3 = highest)
	//

	if (y1 > y3)
	{
		x_tmp = x1;
		y_tmp = y1;
		z_tmp = z1;

		x1 = x3;
		y1 = y3;
		z1 = z3;

		x3 = x_tmp;
		y3 = y_tmp;
		z3 = z_tmp;
	}

	if (y2 > y3)
	{
		x_tmp = x2;
		y_tmp = y2;
		z_tmp = z2;

		x2 = x3;
		y2 = y3;
		z2 = z3;

		x3 = x_tmp;
		y3 = y_tmp;
		z3 = z_tmp;
	}

	if (y1 > y2)
	{
		x_tmp = x1;
		y_tmp = y1;
		z_tmp = z1;

		x1 = x2;
		y1 = y2;
		z1 = z2;

		x2 = x_tmp;
		y2 = y_tmp;
		z2 = z_tmp;
	}

	//
	// draw contour lines
	//

	if (y1 == y2)
	{
		dy = y3 - y1;

		one_over_dy = 1.0 / (float) dy;

		dx1 = (x3 - x1) * one_over_dy;
		dz1 = (z3 - z1) * one_over_dy;
		dx2 = (x3 - x2) * one_over_dy;
		dz2 = (z3 - z2) * one_over_dy;

		y = contour_samples_minus_one - ((y1 - 1) % contour_samples);

		while (dy--)
		{
			#if OPTIMISE_CONTOURS

			num_contour_loops++;

			#endif

			if (y == 0)
			{
				#if OPTIMISE_CONTOURS

				num_contour_lines++;

				#endif

				y = contour_samples;

				draw_2d_line (x1, z1, x2, z2, MFD_CONTOUR_COLOUR);
			}

			y--;

			x1 += dx1;
			z1 += dz1;
			x2 += dx2;
			z2 += dz2;
		}
	}
	else if (y2 == y3)
	{
		dy = y2 - y1;

		one_over_dy = 1.0 / (float) dy;

		dx1 = (x2 - x1) * one_over_dy;
		dz1 = (z2 - z1) * one_over_dy;
		dx2 = (x3 - x1) * one_over_dy;
		dz2 = (z3 - z1) * one_over_dy;

		y = contour_samples_minus_one - ((y1 - 1) % contour_samples);

		x2 = x1;
		z2 = z1;

		while (dy--)
		{
			#if OPTIMISE_CONTOURS

			num_contour_loops++;

			#endif

			if (y == 0)
			{
				#if OPTIMISE_CONTOURS

				num_contour_lines++;

				#endif

				y = contour_samples;

				draw_2d_line (x1, z1, x2, z2, MFD_CONTOUR_COLOUR);
			}

			y--;

			x1 += dx1;
			z1 += dz1;
			x2 += dx2;
			z2 += dz2;
		}
	}
	else
	{
		dy = y3 - y1;

		one_over_dy = 1.0 / (float) dy;

		dx1 = (x3 - x1) * one_over_dy;
		dz1 = (z3 - z1) * one_over_dy;

		dy = y2 - y1;

		one_over_dy = 1.0 / (float) dy;

		dx2 = (x2 - x1) * one_over_dy;
		dz2 = (z2 - z1) * one_over_dy;

		y = contour_samples_minus_one - ((y1 - 1) % contour_samples);

		x2 = x1;
		z2 = z1;

		while (dy--)
		{
			#if OPTIMISE_CONTOURS

			num_contour_loops++;

			#endif

			if (y == 0)
			{
				#if OPTIMISE_CONTOURS

				num_contour_lines++;

				#endif

				y = contour_samples;

				draw_2d_line (x1, z1, x2, z2, MFD_CONTOUR_COLOUR);
			}

			y--;

			x1 += dx1;
			z1 += dz1;
			x2 += dx2;
			z2 += dz2;
		}

		dy = y3 - y2;

		one_over_dy = 1.0 / (float) dy;

		dx2 = (x3 - x2) * one_over_dy;
		dz2 = (z3 - z2) * one_over_dy;

		y = contour_samples_minus_one - ((y2 - 1) % contour_samples);

		while (dy--)
		{
			#if OPTIMISE_CONTOURS

			num_contour_loops++;

			#endif

			if (y == 0)
			{
				#if OPTIMISE_CONTOURS

				num_contour_lines++;

				#endif

				y = contour_samples;

				draw_2d_line (x1, z1, x2, z2, MFD_CONTOUR_COLOUR);
			}

			y--;

			x1 += dx1;
			z1 += dz1;
			x2 += dx2;
			z2 += dz2;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_path_lines
(
	int number_of_paths,
	contour_path *paths,
	vec3d *nodes,
	rgb_colour colour,
	int detail_level,
	float x_world_min,
	float z_world_min,
	float x_world_mid,
	float z_world_mid,
	float x_world_max,
	float z_world_max,
	float scale,
	int draw_thick_lines
)
{
	int
		this_path,
		outcode1,
		outcode2,
		index,
		step_size;

	#if OPTIMISE_PATHS

	int
		num_paths_traversed,
		num_lines_drawn;

	#endif

	float
		x1,
		z1,
		x2,
		z2;

	vec3d
		*sub_positions;

	ASSERT (number_of_paths > 0);

	ASSERT (paths);

	ASSERT (nodes);

	#if OPTIMISE_PATHS

	num_paths_traversed = 0;

	num_lines_drawn = 0;

	#endif

	step_size = max (detail_level << 3, 1);

	for (this_path = 0; this_path < number_of_paths; this_path++)
	{
		if
		(
			(paths[this_path].type != TEMP_TERRAIN_TYPE_COASTAL_RIVER) &&
			(paths[this_path].type != TEMP_TERRAIN_TYPE_LAKE) &&
			(paths[this_path].type != TEMP_TERRAIN_TYPE_OFFROAD)
		)
		{
			//
			// trivially reject path
			//

			outcode1 = 0;

			if (paths[this_path].xmin < x_world_min) outcode1 |= CLIP_LEFT;
			if (paths[this_path].xmin > x_world_max) outcode1 |= CLIP_RIGHT;
			if (paths[this_path].zmin < z_world_min) outcode1 |= CLIP_TOP;
			if (paths[this_path].zmin > z_world_max) outcode1 |= CLIP_BOTTOM;

			outcode2 = 0;

			if (paths[this_path].xmax < x_world_min) outcode2 |= CLIP_LEFT;
			if (paths[this_path].xmax > x_world_max) outcode2 |= CLIP_RIGHT;
			if (paths[this_path].zmax < z_world_min) outcode2 |= CLIP_TOP;
			if (paths[this_path].zmax > z_world_max) outcode2 |= CLIP_BOTTOM;

			if (!(outcode1 & outcode2))
			{
				#if OPTIMISE_PATHS

				num_paths_traversed++;

				#endif

				//
				// this also catches conditions where (count == 0)
				//

				if (paths[this_path].count <= step_size)
				{
					////////////////////////////////////////
					//
					// draw path as a single line
					//
					////////////////////////////////////////

					x1 = (nodes[paths[this_path].from].x - x_world_mid) * scale;
					z1 = (nodes[paths[this_path].from].z - z_world_mid) * scale;

					x2 = (nodes[paths[this_path].to].x - x_world_mid) * scale;
					z2 = (nodes[paths[this_path].to].z - z_world_mid) * scale;

					if (draw_thick_lines && draw_large_mfd)
					{
						draw_2d_half_thick_line (x1, z1, x2, z2, colour);
					}
					else
					{
						draw_2d_line (x1, z1, x2, z2, colour);
					}

					#if OPTIMISE_PATHS

					num_lines_drawn++;

					#endif
				}
				else
				{
					////////////////////////////////////////
					//
					// draw path with variable detail level
					//
					////////////////////////////////////////

					sub_positions = paths[this_path].points;

					index = step_size - 1;;

					//
					// draw line from start node to first sub-position
					//

					x1 = (nodes[paths[this_path].from].x - x_world_mid) * scale;
					z1 = (nodes[paths[this_path].from].z - z_world_mid) * scale;

					x2 = (sub_positions[index].x - x_world_mid) * scale;
					z2 = (sub_positions[index].z - z_world_mid) * scale;

					if (draw_thick_lines && draw_large_mfd)
					{
						draw_2d_half_thick_line (x1, z1, x2, z2, colour);
					}
					else
					{
						draw_2d_line (x1, z1, x2, z2, colour);
					}

					#if OPTIMISE_PATHS

					num_lines_drawn++;

					#endif

					//
					// draw sub-position lines
					//

					index += step_size;

					while (index < paths[this_path].count)
					{
						x1 = x2;
						z1 = z2;

						x2 = (sub_positions[index].x - x_world_mid) * scale;
						z2 = (sub_positions[index].z - z_world_mid) * scale;

						if (draw_thick_lines && draw_large_mfd)
						{
							draw_2d_half_thick_line (x1, z1, x2, z2, colour);
						}
						else
						{
							draw_2d_line (x1, z1, x2, z2, colour);
						}

						#if OPTIMISE_PATHS

						num_lines_drawn++;

						#endif

						index += step_size;
					}

					//
					// draw line from last sub-position to end node
					//

					x1 = x2;
					z1 = z2;

					x2 = (nodes[paths[this_path].to].x - x_world_mid) * scale;
					z2 = (nodes[paths[this_path].to].z - z_world_mid) * scale;

					if (draw_thick_lines && draw_large_mfd)
					{
						draw_2d_half_thick_line (x1, z1, x2, z2, colour);
					}
					else
					{
						draw_2d_line (x1, z1, x2, z2, colour);
					}

					#if OPTIMISE_PATHS

					num_lines_drawn++;

					#endif
				}
			}
		}
	}

	#if OPTIMISE_PATHS

	debug_filtered_log ("paths=%d, paths drawn=%d, lines drawn=%d", number_of_paths, num_paths_traversed, num_lines_drawn);

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_tsd_contour_map (float y_translate, float range, float scale, vec3d *position, float heading)
{
	int
		x_index,
		z_index,
		row_add_on,
		x_min_index,
		z_min_index,
		x_max_index,
		z_max_index,
		path_detail_level,
		contour_granularity,
		contour_granularity_mask;

	float
		x_min,
		z_min,
		x_mid,
		z_mid,
		x_max,
		z_max,
		radius,
		distance,
		dx0,
		dz0,
		dx1,
		dz1,
		dx_grid,
		dz_grid,
		dx_start,
		dz_start,
		*this_row_ptr,
		*next_row_ptr,
		*this_row_start_ptr,
		*next_row_start_ptr;

	vec3d
		p1,
		p2,
		p3;

	ASSERT (position);

	#if OPTIMISE_CONTOURS

	num_contour_loops = 0;

	num_contour_lines = 0;

	#endif

	//
	// rotate map
	//

	set_2d_window_rotation (mfd_env, heading);

	//
	// get map centre position
	//

	distance = y_translate / scale;

	x_mid = position->x + (distance * sin (heading));
	z_mid = position->z + (distance * cos (heading));

	//
	// get map area (increased by one grid, where hypotenuse is approx (x + z))
	//

	radius = range + terrain_3d_simple_elevation_x_grid_size + terrain_3d_simple_elevation_z_grid_size;

	x_min = x_mid - radius;
	z_min = z_mid - radius;

	x_max = x_mid + radius;
	z_max = z_mid + radius;

	//
	// clip map area
	//

	x_min = max (x_min, MIN_MAP_X);
	z_min = max (z_min, MIN_MAP_Z);

	x_max = min (x_max, MAX_MAP_X);
	z_max = min (z_max, MAX_MAP_Z);

	////////////////////////////////////////
	//
	// DRAW CONTOURS
	//
	////////////////////////////////////////

	//
	// get simple terrain map indices
	//

	convert_float_to_int ((x_min * terrain_3d_simple_elevation_x_grid_size_reciprocal), &x_min_index);
	convert_float_to_int ((z_min * terrain_3d_simple_elevation_z_grid_size_reciprocal), &z_min_index);

	convert_float_to_int ((x_max * terrain_3d_simple_elevation_x_grid_size_reciprocal), &x_max_index);
	convert_float_to_int ((z_max * terrain_3d_simple_elevation_z_grid_size_reciprocal), &z_max_index);

	////////////////////////////////////////
	//
	// contour_granularity: chunks the terrain grid
	// contour_samples    : culls the number of contour line samples
	// contour_spacing    : height between contour lines (meters)
	// path_detail_level  : 0 = highest detail (ie draw all sub-lines)
	//
	////////////////////////////////////////

	////////////////////////////////////////
	if (range == TSD_ASE_RANGE_2000)
	////////////////////////////////////////
	{
		contour_granularity = 1;

		contour_samples = 5;

		contour_spacing = 100;

		if (draw_large_mfd)
		{
			path_detail_level = 0;
		}
		else
		{
			path_detail_level = 2;
		}
	}
	////////////////////////////////////////
	else if (range == TSD_ASE_RANGE_5000)
	////////////////////////////////////////
	{
		if (draw_large_mfd)
		{
			contour_granularity = 1;

			contour_samples = 10;

			path_detail_level = 0;
		}
		else
		{
			contour_granularity = 2;

			contour_samples = 10;

			path_detail_level = 2;
		}

		contour_spacing = 100;
	}
	////////////////////////////////////////
	else if (range == TSD_ASE_RANGE_10000)
	////////////////////////////////////////
	{
		if (draw_large_mfd)
		{
			contour_granularity = 2;

			contour_samples = 10;

			path_detail_level = 1;
		}
		else
		{
			contour_granularity = 4;

			contour_samples = 20;

			path_detail_level = 3;
		}

		contour_spacing = 100;
	}
	////////////////////////////////////////
	else if (range == TSD_ASE_RANGE_25000)
	////////////////////////////////////////
	{
		if (draw_large_mfd)
		{
			contour_granularity = 4;

			contour_samples = 10;

			path_detail_level = 2;
		}
		else
		{
			contour_granularity = 8;

			contour_samples = 15;

			path_detail_level = 4;
		}

		contour_spacing = 250;
	}
	////////////////////////////////////////
	else
	////////////////////////////////////////
	{
		debug_fatal ("Unknown TSD/ASE range %.2f", range);
	}

	contour_spacing /= contour_samples;

	contour_granularity_mask = ~(contour_granularity - 1);

	//
	// scan map
	//

	x_min_index &= contour_granularity_mask;
	z_min_index &= contour_granularity_mask;

	x_max_index += contour_granularity - 1;
	z_max_index += contour_granularity - 1;

	x_max_index &= contour_granularity_mask;
	z_max_index &= contour_granularity_mask;

	if (x_max_index >= terrain_3d_simple_elevation_width)
	{
		x_max_index = terrain_3d_simple_elevation_width & contour_granularity_mask;
	}

	if (z_max_index >= terrain_3d_simple_elevation_height)
	{
		z_max_index = terrain_3d_simple_elevation_height & contour_granularity_mask;
	}

	if ((x_min_index < x_max_index) && (z_min_index < z_max_index))
	{
		this_row_start_ptr = &terrain_3d_simple_elevation_grid[(z_min_index * terrain_3d_simple_elevation_width) + x_min_index];

		row_add_on = terrain_3d_simple_elevation_width * contour_granularity;

		next_row_start_ptr = this_row_start_ptr + row_add_on;

		dx_start = ((((float) x_min_index) * terrain_3d_simple_elevation_x_grid_size) - x_mid) * scale;
		dz_start = ((((float) z_min_index) * terrain_3d_simple_elevation_z_grid_size) - z_mid) * scale;

		dx_grid = terrain_3d_simple_elevation_x_grid_size * (float) contour_granularity * scale;
		dz_grid = terrain_3d_simple_elevation_z_grid_size * (float) contour_granularity * scale;

		dz0 = dz_start;
		dz1 = dz_start + dz_grid;

		for (z_index = z_min_index; z_index < z_max_index; z_index += contour_granularity)
		{
			dx0 = dx_start;
			dx1 = dx_start + dx_grid;

			this_row_ptr = this_row_start_ptr;
			next_row_ptr = next_row_start_ptr;

			for (x_index = x_min_index; x_index < x_max_index; x_index += contour_granularity)
			{
				//
				// offset [z=0][x=0]
				//

				p1.x = dx0;
				p1.y = this_row_ptr[0];
				p1.z = dz0;

				//
				// offset [z=0][x=1]
				//

				p2.x = dx1;
				p2.y = this_row_ptr[contour_granularity];
				p2.z = dz0;

				//
				// offset [z=1][x=0]
				//

				p3.x = dx0;
				p3.y = next_row_ptr[0];
				p3.z = dz1;

				draw_contour_lines (&p1, &p2, &p3);

				//
				// offset [z=1][x=1]
				//

				p1.x = dx1;
				p1.y = next_row_ptr[contour_granularity];
				p1.z = dz1;

				draw_contour_lines (&p1, &p2, &p3);

				//
				// next column
				//

				dx0 += dx_grid;
				dx1 += dx_grid;

				this_row_ptr += contour_granularity;
				next_row_ptr += contour_granularity;
			}

			//
			// next row
			//

			dz0 += dz_grid;
			dz1 += dz_grid;

			this_row_start_ptr += row_add_on;
			next_row_start_ptr += row_add_on;
		}
	}

	#if OPTIMISE_CONTOURS

	debug_filtered_log ("num_contour_loops = %d, num_contour_lines = %d", num_contour_loops, num_contour_lines);

	#endif

	////////////////////////////////////////
	//
	// DRAW RIVERS
	//
	////////////////////////////////////////

	draw_path_lines
	(
		contour_map_number_of_river_paths,
		contour_map_river_paths,
		contour_map_river_nodes,
		MFD_RIVER_COLOUR,
		path_detail_level,
		x_min,
		z_min,
		x_mid,
		z_mid,
		x_max,
		z_max,
		scale,
		TRUE
	);

	////////////////////////////////////////
	//
	// DRAW ROADS
	//
	////////////////////////////////////////

	draw_path_lines
	(
		contour_map_number_of_road_paths,
		contour_map_road_paths,
		contour_map_road_nodes,
		MFD_ROAD_COLOUR,
		path_detail_level,
		x_min,
		z_min,
		x_mid,
		z_mid,
		x_max,
		z_max,
		scale,
		FALSE
	);

	//
	// reset window rotation
	//

	set_2d_window_rotation (mfd_env, 0.0);
}
*/ //VJ 030423 TSD render mod, code moved to co_tsd.c in ../common
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

static void draw_tactical_situation_display_mfd (hokum_mfd_locations mfd_location)
{
	char
		*s,
		buffer[200];

	int
		*tsd_draw_threat_line_status;

	entity_sides
		source_side;

	tsd_declutter_levels
		tsd_declutter_level;

	float
		u,
		v,
		scale,
		x_origin,
		y_origin,
		width,
		y_adjust,
		source_heading,
		tsd_ase_range,
		*tsd_threat_line_flash_timer;

	entity
		*source,
		*source_target;

	vec3d
		*source_position;

	ASSERT (hokum_mfd_location_valid (mfd_location));

	switch (mfd_location)
	{
		////////////////////////////////////////
		case HOKUM_MFD_LOCATION_PILOT_LHS:
		case HOKUM_MFD_LOCATION_PILOT_RHS:
		////////////////////////////////////////
		{
			tsd_ase_range						= pilot_tsd_ase_range;
			tsd_declutter_level				= pilot_tsd_declutter_level;
			tsd_threat_line_flash_timer	= &pilot_tsd_threat_line_flash_timer;
			tsd_draw_threat_line_status	= &pilot_tsd_draw_threat_line_status;

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_LOCATION_CO_PILOT_LHS:
		case HOKUM_MFD_LOCATION_CO_PILOT_RHS:
		////////////////////////////////////////
		{
			tsd_ase_range						= co_pilot_tsd_ase_range;
			tsd_declutter_level				= co_pilot_tsd_declutter_level;
			tsd_threat_line_flash_timer	= &co_pilot_tsd_threat_line_flash_timer;
			tsd_draw_threat_line_status	= &co_pilot_tsd_draw_threat_line_status;

			break;
		}
	}

	source = get_gunship_entity ();

	source_side = get_local_entity_int_value (source, INT_TYPE_SIDE);

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

	if (tsd_render_mode != TSD_RENDER_CONTOUR_MODE)
	{
		//VJ 030423 TSD render mod
		set_rgb_colour (MFD_COLOUR1,   0, 0,  96, 255);  //dark blue
	   set_rgb_colour (MFD_COLOUR2,	32, 32,  164, 255); //light blue
		set_rgb_colour (MFD_COLOUR3, 220, 48,   0, 255); //bright red
		set_rgb_colour (MFD_COLOUR4, 148, 32,   0, 255);//dark red
				
		if (tsd_render_palette == 0)
		{
			set_rgb_colour (MFD_COLOUR5,   32, 56,   20, 255);
		}	
		else
			if (tsd_render_palette == 1)
			{
				set_rgb_colour (MFD_COLOUR5,   0, 132,   156, 255);
			}	
			else
			{
				set_rgb_colour (MFD_COLOUR5,   64, 132,   0, 255);
			}	

		set_rgb_colour (MFD_COLOUR6,  255, 255,  0, 255);
		//VJ 030511 colours 7 and 8 are grays when enemy colour option is off in eech.ini
		//VJ 030530 colour tweaks: black and dark gray are best
		set_rgb_colour (MFD_COLOUR7,    64, 64, 64, 255);
		set_rgb_colour (MFD_COLOUR8,    0,   0,  0, 255);
	
	   draw_tsd_terrain_map (mfd_env, -y_origin, tsd_ase_range, scale, source_position, source_heading);
	}
	
	////////////////////////////////////////
	//
	// contour map
	//
	////////////////////////////////////////
	
//VJ 030423 TSD render mod, added mfd_env
	draw_tsd_contour_map (mfd_env, -y_origin, tsd_ase_range, scale, source_position, source_heading, draw_large_mfd);

	////////////////////////////////////////
	//
	// radar scan
	//
	////////////////////////////////////////

	if (tsd_declutter_level != TSD_DECLUTTER_LEVEL_NAVIGATION)
	{
		float
			radius;

		if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_GROUND_RADAR)
		{
			set_2d_viewport_origin (mfd_env, u, v);

			radius = ground_radar.scan_range * scale;

			set_2d_window_rotation (mfd_env, -ground_radar.scan_datum);

			draw_radar_arc (ground_radar.scan_arc_size, radius, MFD_COLOUR4);

			set_2d_window_rotation (mfd_env, -(ground_radar.scan_datum - (ground_radar.scan_arc_size * 0.5)));

			draw_2d_line (0.0, 0.0, 0.0, radius, MFD_COLOUR4);

			set_2d_window_rotation (mfd_env, -(ground_radar.scan_datum + (ground_radar.scan_arc_size * 0.5)));

			draw_2d_line (0.0, 0.0, 0.0, radius, MFD_COLOUR4);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_2d_window_rotation (mfd_env, 0.0);
		}
		else if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_AIR_RADAR)
		{
			set_2d_viewport_origin (mfd_env, u, v);

			radius = air_radar.scan_range * scale;

			if (air_radar.scan_arc_size == HOKUM_RADAR_SCAN_ARC_SIZE_360)
			{
				draw_2d_circle (0.0, 0.0, radius, MFD_COLOUR4);
			}
			else
			{
				set_2d_window_rotation (mfd_env, -air_radar.scan_datum);

				draw_radar_arc (air_radar.scan_arc_size, radius, MFD_COLOUR4);

				draw_2d_line (0.0, 0.0, 0.0, radius, MFD_COLOUR4);

				set_2d_window_rotation (mfd_env, -(air_radar.scan_datum - (air_radar.scan_arc_size * 0.5)));

				draw_2d_line (0.0, 0.0, 0.0, radius, MFD_COLOUR4);

				set_2d_window_rotation (mfd_env, -(air_radar.scan_datum + (air_radar.scan_arc_size * 0.5)));

				draw_2d_line (0.0, 0.0, 0.0, radius, MFD_COLOUR4);

				set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

				set_2d_window_rotation (mfd_env, 0.0);
			}
		}
	}

	////////////////////////////////////////
	//
	// waypoint route
	//
	////////////////////////////////////////

	if (tsd_declutter_level != TSD_DECLUTTER_LEVEL_TARGET)
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
					draw_2d_half_thick_line (wp1_rel_position.x, wp1_rel_position.z, wp2_rel_position.x, wp2_rel_position.z, MFD_COLOUR2);
				}
				else
				{
					draw_2d_line (wp1_rel_position.x, wp1_rel_position.z, wp2_rel_position.x, wp2_rel_position.z, MFD_COLOUR2);
				}

				wp1 = wp2;

				wp1_rel_position = wp2_rel_position;

				wp2 = get_local_entity_child_succ (wp1, LIST_TYPE_WAYPOINT);
			}

			//
			// waypoint markers
			//

			set_mono_font_colour (MFD_COLOUR6);

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
					draw_2d_mono_sprite (large_tsd_waypoint_marker, wp1_rel_position.x, wp1_rel_position.z, MFD_COLOUR2);

					set_2d_mono_font_position (wp1_rel_position.x, wp1_rel_position.z);

					set_mono_font_rel_position (-2.0, -4.0);
				}
				else
				{
					draw_2d_mono_sprite (small_tsd_waypoint_marker, wp1_rel_position.x, wp1_rel_position.z, MFD_COLOUR2);

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
			*tsd_threat_line_flash_timer -= get_delta_time ();

			if (*tsd_threat_line_flash_timer < 0.0)
			{
				*tsd_threat_line_flash_timer = TSD_THREAT_LINE_FLASH_RATE;

				*tsd_draw_threat_line_status ^= 1;
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
						threat_type = get_local_entity_int_value (target, INT_TYPE_THREAT_TYPE);

						if ((threat_type == THREAT_TYPE_SAM) || (threat_type == THREAT_TYPE_AAA))
						{
							target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

							dx = (target_position->x - source_position->x) * scale;
							dy = (target_position->z - source_position->z) * scale;

							air_scan_range = get_local_entity_float_value (target, FLOAT_TYPE_AIR_SCAN_RANGE) * scale;

//VJ 030423 TSD render mod, enemy of comanche so blue
//VJ 030511 TSD render mod, enemy optional in eech.ini
							if (command_line_tsd_enemy_colours)
								draw_2d_circle (dx, dy, air_scan_range, MFD_COLOUR2);
							else				
								draw_2d_circle (dx, dy, air_scan_range, MFD_COLOUR8);
							
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
							threat_type = get_local_entity_int_value (target, INT_TYPE_THREAT_TYPE);

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
												draw_threat_line = *tsd_draw_threat_line_status;

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

	////////////////////////////////////////
	//
	// aircraft datum symbol
	//
	////////////////////////////////////////

	if (draw_large_mfd)
	{
		draw_2d_mono_sprite (large_tsd_ase_aircraft_datum_mask, x_origin, y_origin, MFD_COLOUR6);

		draw_2d_mono_sprite (large_tsd_ase_aircraft_datum, x_origin, y_origin, MFD_COLOUR1);
	}
	else
	{
		draw_2d_mono_sprite (small_tsd_ase_aircraft_datum_mask, x_origin, y_origin, MFD_COLOUR6);

		draw_2d_mono_sprite (small_tsd_ase_aircraft_datum, x_origin, y_origin, MFD_COLOUR1);
	}

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
	// sensor type
	//

	if (tsd_declutter_level != TSD_DECLUTTER_LEVEL_NAVIGATION)
	{
		switch (target_acquisition_system)
		{
			case TARGET_ACQUISITION_SYSTEM_OFF:
			{
				s = "NO ACQ";

				break;
			}
			case TARGET_ACQUISITION_SYSTEM_GROUND_RADAR:
			case TARGET_ACQUISITION_SYSTEM_AIR_RADAR:
			{
				s = "FCR";

				break;
			}
			case TARGET_ACQUISITION_SYSTEM_FLIR:
			case TARGET_ACQUISITION_SYSTEM_LLLTV:
			case TARGET_ACQUISITION_SYSTEM_PERISCOPE:
			{
				s = "EOS";

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

		set_2d_mono_font_position (-1.0, 1.0);

		set_mono_font_rel_position (1.0, y_adjust);

		print_mono_font_string (s);

		switch (target_acquisition_system)
		{
			case TARGET_ACQUISITION_SYSTEM_OFF:
			{
				s = "";

				break;
			}
			case TARGET_ACQUISITION_SYSTEM_GROUND_RADAR:
			{
				s = "GND";

				break;
			}
			case TARGET_ACQUISITION_SYSTEM_AIR_RADAR:
			{
				s = "AIR";

				break;
			}
			case TARGET_ACQUISITION_SYSTEM_FLIR:
			{
				s = "FLIR";

				break;
			}
			case TARGET_ACQUISITION_SYSTEM_LLLTV:
			{
				s = "LLLTV";

				break;
			}
			case TARGET_ACQUISITION_SYSTEM_PERISCOPE:
			{
				s = "SCOPE";

				break;
			}
			case TARGET_ACQUISITION_SYSTEM_HMS:
			{
				s = "";

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
			y_adjust = 18.0;
		}
		else
		{
			y_adjust = 9.0;
		}

		set_2d_mono_font_position (-1.0, 1.0);

		set_mono_font_rel_position (1.0, y_adjust);

		print_mono_font_string (s);
	}

	//
	// TSD range
	//

	if (tsd_ase_range == TSD_ASE_RANGE_2000)
	{
		s = "2Km";
	}
	else if (tsd_ase_range == TSD_ASE_RANGE_5000)
	{
		s = "5Km";
	}
	else if (tsd_ase_range == TSD_ASE_RANGE_10000)
	{
		s = "10Km";
	}
	else if (tsd_ase_range == TSD_ASE_RANGE_25000)
	{
		s = "25Km";
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
		s = "ALL";
	}
	else if (tsd_declutter_level == TSD_DECLUTTER_LEVEL_TARGET)
	{
		s = "TGT";
	}
	else if (tsd_declutter_level == TSD_DECLUTTER_LEVEL_NAVIGATION)
	{
		s = "NAV";
	}
	else
	{
		s = "XXX";
	}

	width = get_mono_font_string_width (s);

	if (draw_large_mfd)
	{
		width += 2.0;

		y_adjust = 18.0;
	}
	else
	{
		width += 1.0;

		y_adjust = 9.0;
	}

	set_2d_mono_font_position (1.0, 1.0);

	set_mono_font_rel_position (-width, y_adjust);

	print_mono_font_string (s);

	//
	// target range
	//

	if (tsd_declutter_level != TSD_DECLUTTER_LEVEL_NAVIGATION)
	{
		if (source_target)
		{
			vec3d
				*target_position;

			float
				target_range;

			target_position = get_local_entity_vec3d_ptr (source_target, VEC3D_TYPE_POSITION);

			target_range = get_3d_range (source_position, target_position);

			if ((target_range < 1000.0) && (!hokum_damage.laser_designator))
			{
				sprintf (buffer, "%dm", (int) target_range);
			}
			else
			{
				sprintf (buffer, "%.1fKm", target_range * (1.0 / 1000.0));
			}

			width = get_mono_font_string_width (buffer);

			if (draw_large_mfd)
			{
				width += 2.0;

				y_adjust = -12.0;
			}
			else
			{
				width += 1.0;

				y_adjust = -5.0;
			}

			set_2d_mono_font_position (1.0, -1.0);

			set_mono_font_rel_position (-width, y_adjust);

			print_mono_font_string (buffer);
		}
	}

	//
	// waypoint information
	//

	if (tsd_declutter_level != TSD_DECLUTTER_LEVEL_TARGET)
	{
		entity
			*wp;

		vec3d
			waypoint_position;

		float
			waypoint_range;

		wp = get_local_entity_current_waypoint (source);

		if (wp)
		{
			get_waypoint_display_position (source, wp, &waypoint_position);

			//
			// waypoint id & range
			//

			waypoint_range = get_2d_range (source_position, &waypoint_position);

			if (!hokum_damage.navigation_computer)
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

			if (draw_large_mfd)
			{
				y_adjust = -12.0;
			}
			else
			{
				y_adjust = -5.0;
			}

			set_2d_mono_font_position (-1.0, -1.0);

			set_mono_font_rel_position (1.0, y_adjust);

			print_mono_font_string (buffer);
		}
	}
//VJ 030423 TSD render mod
	set_rgb_colour (MFD_COLOUR1,            255, 135,   0, 255);
	set_rgb_colour (MFD_COLOUR2,            255,  90,   0, 255);
	set_rgb_colour (MFD_COLOUR3,            200,  65,   0, 255);
	set_rgb_colour (MFD_COLOUR4,            130,  50,   0, 255);
	set_rgb_colour (MFD_COLOUR5,            100,  50,   0, 255);
	set_rgb_colour (MFD_COLOUR6,             50,  25,   0, 255);	
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

			time_to_impact = threat_range / max (threat_velocity, 1.0);

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

static void draw_aircraft_survivability_equipment_display_mfd (hokum_mfd_locations mfd_location)
{
	char
		*s,
		buffer[200];

	entity_sides
		source_side;

	int
		*ase_draw_threat_line_status;

	float
		scale,
		width,
		y_adjust,
		source_heading,
		tsd_ase_range,
		*ase_threat_line_flash_timer;

	entity
		*source,
		*source_target;

	vec3d
		*source_position;

	ASSERT (hokum_mfd_location_valid (mfd_location));

	switch (mfd_location)
	{
		////////////////////////////////////////
		case HOKUM_MFD_LOCATION_PILOT_LHS:
		case HOKUM_MFD_LOCATION_PILOT_RHS:
		////////////////////////////////////////
		{
			tsd_ase_range						= pilot_tsd_ase_range;
			ase_threat_line_flash_timer	= &pilot_ase_threat_line_flash_timer;
			ase_draw_threat_line_status	= &pilot_ase_draw_threat_line_status;

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_LOCATION_CO_PILOT_LHS:
		case HOKUM_MFD_LOCATION_CO_PILOT_RHS:
		////////////////////////////////////////
		{
			tsd_ase_range						= co_pilot_tsd_ase_range;
			ase_threat_line_flash_timer	= &co_pilot_ase_threat_line_flash_timer;
			ase_draw_threat_line_status	= &co_pilot_ase_draw_threat_line_status;

			break;
		}
	}

	source = get_gunship_entity ();

	source_side = get_local_entity_int_value (source, INT_TYPE_SIDE);

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

		*ase_threat_line_flash_timer -= get_delta_time ();

		if (*ase_threat_line_flash_timer < 0.0)
		{
			*ase_threat_line_flash_timer = ASE_THREAT_LINE_FLASH_RATE;

			*ase_draw_threat_line_status ^= 1;
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
					threat_type = get_local_entity_int_value (threat, INT_TYPE_THREAT_TYPE);

					if ((threat_type == THREAT_TYPE_SAM) || (threat_type == THREAT_TYPE_AAA))
					{
						threat_position = get_local_entity_vec3d_ptr (threat, VEC3D_TYPE_POSITION);

						dx = (threat_position->x - source_position->x) * scale;
						dy = (threat_position->z - source_position->z) * scale;

						air_scan_range = get_local_entity_float_value (threat, FLOAT_TYPE_AIR_SCAN_RANGE) * scale;

						draw_2d_circle (dx, dy, air_scan_range, MFD_COLOUR2);
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
					threat_type = get_local_entity_int_value (threat, INT_TYPE_THREAT_TYPE);

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
						threat_type = get_local_entity_int_value (threat, INT_TYPE_THREAT_TYPE);

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
											draw_threat_line = *ase_draw_threat_line_status;

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

									draw_2d_line (0.0, 0.0, dx, dy, MFD_COLOUR1);
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
			threat_type = get_local_entity_int_value (threat, INT_TYPE_THREAT_TYPE);

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

	set_mono_font_colour (MFD_COLOUR1);

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
		s = "2Km";
	}
	else if (tsd_ase_range == TSD_ASE_RANGE_5000)
	{
		s = "5Km";
	}
	else if (tsd_ase_range == TSD_ASE_RANGE_10000)
	{
		s = "10Km";
	}
	else if (tsd_ase_range == TSD_ASE_RANGE_25000)
	{
		s = "25Km";
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
		if (hokum_damage.infra_red_jammer)
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
		if (hokum_damage.infra_red_jammer)
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
		if (hokum_damage.radar_jammer)
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
		if (hokum_damage.radar_jammer)
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
		if ((hokum_damage.lh_chaff_dispensers) && (hokum_damage.rh_chaff_dispensers))
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
		if ((hokum_damage.lh_chaff_dispensers) && (hokum_damage.rh_chaff_dispensers))
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
		if ((hokum_damage.lh_flare_dispensers) && (hokum_damage.rh_flare_dispensers))
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
		if ((hokum_damage.lh_flare_dispensers) && (hokum_damage.rh_flare_dispensers))
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

	if (draw_large_mfd)
	{
		i = 0;

		while (i < num_weapon_line_points)
		{
			draw_2d_half_thick_line
			(
				weapon_line_points[i].x,
				weapon_line_points[i].y,
				weapon_line_points[i + 1].x,
				weapon_line_points[i + 1].y,
				MFD_COLOUR4
			);

			i += 2;
		}
	}
	else
	{
		i = 0;

		while (i < num_weapon_line_points)
		{
			draw_2d_line
			(
				weapon_line_points[i].x,
				weapon_line_points[i].y,
				weapon_line_points[i + 1].x,
				weapon_line_points[i + 1].y,
				MFD_COLOUR4
			);

			i += 2;
		}
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

	result = get_local_entity_weapon_hardpoint_info (en, HOKUM_LHS_CHAFF_DISPENSER, ENTITY_SUB_TYPE_WEAPON_CHAFF, &weapon_sub_type, &number, &damaged);

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

	result = get_local_entity_weapon_hardpoint_info (en, HOKUM_LHS_FLARE_DISPENSER, ENTITY_SUB_TYPE_WEAPON_FLARE, &weapon_sub_type, &number, &damaged);

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

	result = get_local_entity_weapon_hardpoint_info (en, HOKUM_RHS_CHAFF_DISPENSER, ENTITY_SUB_TYPE_WEAPON_CHAFF, &weapon_sub_type, &number, &damaged);

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

	result = get_local_entity_weapon_hardpoint_info (en, HOKUM_RHS_FLARE_DISPENSER, ENTITY_SUB_TYPE_WEAPON_FLARE, &weapon_sub_type, &number, &damaged);

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

	result = get_local_entity_weapon_hardpoint_info (en, HOKUM_CANNON_TURRET, ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND, &weapon_sub_type, &number, &damaged);

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

	result = get_local_entity_weapon_hardpoint_info (en, HOKUM_CANNON_TURRET, ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND, &weapon_sub_type, &number, &damaged);

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
			draw_2d_half_thick_line (0.2375, -0.26, 0.2375, -0.425, MFD_COLOUR4);

			draw_2d_half_thick_line (0.1875, -0.425, 0.2375, -0.425, MFD_COLOUR4);

			if (hokum_damage.gun_jammed)
			{
				draw_2d_half_thick_line (0.2375 - 0.05, -0.215 - 0.05, 0.2375 + 0.05, -0.215 + 0.05, MFD_COLOUR1);

				draw_2d_half_thick_line (0.2375 + 0.05, -0.215 - 0.05, 0.2375 - 0.05, -0.215 + 0.05, MFD_COLOUR1);
			}
		}
		else
		{
			draw_2d_line (0.233, -0.27, 0.233, -0.42, MFD_COLOUR4);

			draw_2d_line (0.2, -0.42, 0.233, -0.42, MFD_COLOUR4);

			if (hokum_damage.gun_jammed)
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

	result = get_local_entity_weapon_hardpoint_info (en, HOKUM_LHS_INNER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, &weapon_sub_type, &number, &damaged);

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
			draw_2d_half_thick_line (-0.52, -0.14, -0.52, -0.63, MFD_COLOUR4);

			draw_2d_half_thick_line (-0.47, -0.63, -0.52, -0.63, MFD_COLOUR4);

			if (damaged)
			{
				draw_2d_half_thick_line (-0.52 - 0.05, -0.07 - 0.05, -0.52 + 0.05, -0.07 + 0.05, MFD_COLOUR1);

				draw_2d_half_thick_line (-0.52 + 0.05, -0.07 - 0.05, -0.52 - 0.05, -0.07 + 0.05, MFD_COLOUR1);
			}
		}
		else
		{
			draw_2d_line (-0.52, -0.16, -0.52, -0.63, MFD_COLOUR4);

			draw_2d_line (-0.47, -0.63, -0.52, -0.63, MFD_COLOUR4);

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

	result = get_local_entity_weapon_hardpoint_info (en, HOKUM_RHS_INNER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, &weapon_sub_type, &number, &damaged);

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
			draw_2d_half_thick_line (0.52, -0.14, 0.52, -0.63, MFD_COLOUR4);

			draw_2d_half_thick_line (0.47, -0.63, 0.52, -0.63, MFD_COLOUR4);

			if (damaged)
			{
				draw_2d_half_thick_line (0.52 - 0.05, -0.07 - 0.05, 0.52 + 0.05, -0.07 + 0.05, MFD_COLOUR1);

				draw_2d_half_thick_line (0.52 + 0.05, -0.07 - 0.05, 0.52 - 0.05, -0.07 + 0.05, MFD_COLOUR1);
			}
		}
		else
		{
			draw_2d_line (0.52, -0.16, 0.52, -0.63, MFD_COLOUR4);

			draw_2d_line (0.47, -0.63, 0.52, -0.63, MFD_COLOUR4);

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

	result = get_local_entity_weapon_hardpoint_info (en, HOKUM_LHS_OUTER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, &weapon_sub_type, &number, &damaged);

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
			draw_2d_half_thick_line (-0.695, -0.14, -0.695, -0.785, MFD_COLOUR4);

			draw_2d_half_thick_line (-0.47, -0.785, -0.695, -0.785, MFD_COLOUR4);

			if (damaged)
			{
				draw_2d_half_thick_line (-0.695 - 0.05, -0.07 - 0.05, -0.695 + 0.05, -0.07 + 0.05, MFD_COLOUR1);

				draw_2d_half_thick_line (-0.695 + 0.05, -0.07 - 0.05, -0.695 - 0.05, -0.07 + 0.05, MFD_COLOUR1);
			}
		}
		else
		{
			draw_2d_line (-0.695, -0.16, -0.695, -0.785, MFD_COLOUR4);

			draw_2d_line (-0.47, -0.785, -0.695, -0.785, MFD_COLOUR4);

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

	result = get_local_entity_weapon_hardpoint_info (en, HOKUM_RHS_OUTER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, &weapon_sub_type, &number, &damaged);

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
			draw_2d_half_thick_line (0.695, -0.14, 0.695, -0.785, MFD_COLOUR4);

			draw_2d_half_thick_line (0.47, -0.785, 0.695, -0.785, MFD_COLOUR4);

			if (damaged)
			{
				draw_2d_half_thick_line (0.695 - 0.05, -0.07 - 0.05, 0.695 + 0.05, -0.07 + 0.05, MFD_COLOUR1);

				draw_2d_half_thick_line (0.695 + 0.05, -0.07 - 0.05, 0.695 - 0.05, -0.07 + 0.05, MFD_COLOUR1);
			}
		}
		else
		{
			draw_2d_line (0.695, -0.16, 0.695, -0.785, MFD_COLOUR4);

			draw_2d_line (0.47, -0.785, 0.695, -0.785, MFD_COLOUR4);

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

	y_adjust = print_mfd_system_message ("RADAR", "FAIL", hokum_damage.radar, y_adjust, width_adjust);

	y_adjust = print_mfd_system_message ("FLIR", "FAIL", hokum_damage.flir, y_adjust, width_adjust);

	y_adjust = print_mfd_system_message ("LLLTV", "FAIL", hokum_damage.llltv, y_adjust, width_adjust);

	y_adjust = print_mfd_system_message ("PERISCOPE", "FAIL", hokum_damage.periscope, y_adjust, width_adjust);

	y_adjust = print_mfd_system_message ("LASER DESIGNATOR", "FAIL", hokum_damage.laser_designator, y_adjust, width_adjust);

	y_adjust = print_mfd_system_message ("RADAR JAMMER", "FAIL", hokum_damage.radar_jammer, y_adjust, width_adjust);

	y_adjust = print_mfd_system_message ("IR JAMMER", "FAIL", hokum_damage.infra_red_jammer, y_adjust, width_adjust);

	y_adjust = print_mfd_system_message ("NAVIGATION COMPUTER", "FAIL", hokum_damage.navigation_computer, y_adjust, width_adjust);

	y_adjust = print_mfd_system_message ("COMMUNICATIONS", "FAIL", hokum_damage.communications, y_adjust, width_adjust);

	y_adjust = print_mfd_system_message ("RADAR WARNING SYSTEM", "FAIL", hokum_damage.radar_warning_system, y_adjust, width_adjust);

	y_adjust = print_mfd_system_message ("HUD", "FAIL", hokum_damage.head_up_display, y_adjust, width_adjust);

	y_adjust = print_mfd_system_message ("HMS", "FAIL", hokum_damage.helmet_mounted_sight, y_adjust, width_adjust);

	y_adjust = print_mfd_system_message ("NVG", "FAIL", hokum_damage.night_vision_goggles, y_adjust, width_adjust);

	y_adjust = print_mfd_system_message ("STABILISER", "FAIL", get_dynamics_damage_type (DYNAMICS_DAMAGE_STABILISER), y_adjust, width_adjust);

	y_adjust = print_mfd_system_message ("MAIN ROTOR", "DAMAGED", get_dynamics_damage_type (DYNAMICS_DAMAGE_MAIN_ROTOR), y_adjust, width_adjust);

	y_adjust = print_mfd_system_message ("L ENGINE", "DAMAGED", get_dynamics_damage_type (DYNAMICS_DAMAGE_LEFT_ENGINE), y_adjust, width_adjust);

	y_adjust = print_mfd_system_message ("APU", "DAMAGED", FALSE, y_adjust, width_adjust);

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

static float get_rpm_scale_value (float rpm_value)
{
	float
		scale_value,
		a,
		b,
		c,
		d;

	ASSERT ((rpm_value >= 0.0) && (rpm_value <= 120.0));

	if (rpm_value <= 50.0)
	{
		a = 0.0;
		b = 50.0;
		c = 0.0;
		d = 0.1333;
	}
	else if (rpm_value <= 90.0)
	{
		a = 50.0;
		b = 90.0;
		c = 0.1333;
		d = 0.4;
	}
	else
	{
		a = 90.0;
		b = 120.0;
		c = 0.4;
		d = 1.0;
	}

	scale_value = ((rpm_value - a) * ((d - c) / (b - a))) + c;

	return (scale_value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define BAR_WIDTH		((float) (0.1))
#define BAR_HEIGHT	((float) (1.5))

static void draw_rpm_bar (char *title, float xv_org, float yv_org, float rpm_value, int numeric_scale)
{
	char
		s[80];

	int
		ix1,
		iy1,
		ix2,
		iy2,
		digital_readout;

	float
		x_adjust,
		y_adjust,
		bar_xvmin,
		bar_yvmin,
		bar_xvmax,
		bar_yvmax,
		tick_length,
		tick_xw1,
		tick_xw2,
		tick_xw3,
		tick_xw4,
		tick_yw,
		text_xw1,
		text_xw2;

	ASSERT (title);

	////////////////////////////////////////

	bar_xvmin = xv_org - (BAR_WIDTH * 0.5);
	bar_yvmin = yv_org - BAR_HEIGHT;
	bar_xvmax = xv_org + (BAR_WIDTH * 0.5);
	bar_yvmax = yv_org;

	////////////////////////////////////////

	set_2d_mono_font_position (xv_org, yv_org + 0.1);

	x_adjust = get_mono_font_string_width (title) * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string (title);

	////////////////////////////////////////

	rpm_value = bound (rpm_value, 0.0, 120.0);

	convert_float_to_int (rpm_value, &digital_readout);

	sprintf (s, "%03d", digital_readout);

	set_2d_mono_font_position (xv_org, bar_yvmin - 0.1);

	x_adjust = get_mono_font_string_width (s) * -0.5;

	y_adjust = draw_large_mfd ? -6.0 : -3.0;

	set_mono_font_rel_position (x_adjust, y_adjust);

	print_mono_font_string (s);

	////////////////////////////////////////

	if (numeric_scale)
	{
		if (draw_large_mfd)
		{
			set_mono_font_type (MONO_FONT_TYPE_5X9);

			y_adjust = -3.0;
		}
		else
		{
			set_mono_font_type (MONO_FONT_TYPE_3X6);

			y_adjust = -2.0;
		}

		get_2d_float_screen_x_coordinate (bar_xvmin - 0.1, &text_xw1);
		get_2d_float_screen_x_coordinate (bar_xvmax + 0.1, &text_xw2);
	}

	////////////////////////////////////////

	draw_2d_line (bar_xvmin, bar_yvmax, bar_xvmin, bar_yvmin, MFD_COLOUR1);
	draw_2d_line (bar_xvmax, bar_yvmax, bar_xvmax, bar_yvmin, MFD_COLOUR1);
	draw_2d_line (bar_xvmin, bar_yvmax, bar_xvmax, bar_yvmax, MFD_COLOUR1);
	draw_2d_line (bar_xvmin, bar_yvmin, bar_xvmax, bar_yvmin, MFD_COLOUR1);

	////////////////////////////////////////

	tick_length = draw_large_mfd ? 2.0 : 1.0;

	get_2d_float_screen_x_coordinate (bar_xvmin, &tick_xw1);
	tick_xw2 = tick_xw1 - tick_length;

	get_2d_float_screen_x_coordinate (bar_xvmax, &tick_xw3);
	tick_xw4 = tick_xw3 + tick_length;

	////////////////////////////////////////

	get_2d_float_screen_y_coordinate (bar_yvmin + (get_rpm_scale_value (120.0) * BAR_HEIGHT), &tick_yw);
	draw_line (tick_xw1, tick_yw, tick_xw2, tick_yw, MFD_COLOUR1);
	draw_line (tick_xw3, tick_yw, tick_xw4, tick_yw, MFD_COLOUR1);

	if (numeric_scale)
	{
		x_adjust = get_mono_font_string_width ("120") * -0.5;

		set_mono_font_position (text_xw1, tick_yw);

		set_mono_font_rel_position (x_adjust, y_adjust);

		print_mono_font_string ("120");

		set_mono_font_position (text_xw2, tick_yw);

		set_mono_font_rel_position (x_adjust, y_adjust);

		print_mono_font_string ("120");
	}

	get_2d_float_screen_y_coordinate (bar_yvmin + (get_rpm_scale_value (110.0) * BAR_HEIGHT), &tick_yw);
	draw_line (tick_xw1, tick_yw, tick_xw2, tick_yw, MFD_COLOUR1);
	draw_line (tick_xw3, tick_yw, tick_xw4, tick_yw, MFD_COLOUR1);

	if (numeric_scale)
	{
		x_adjust = get_mono_font_string_width ("110") * -0.5;

		set_mono_font_position (text_xw1, tick_yw);

		set_mono_font_rel_position (x_adjust, y_adjust);

		print_mono_font_string ("110");

		set_mono_font_position (text_xw2, tick_yw);

		set_mono_font_rel_position (x_adjust, y_adjust);

		print_mono_font_string ("110");
	}

	get_2d_float_screen_y_coordinate (bar_yvmin + (get_rpm_scale_value (108.0) * BAR_HEIGHT), &tick_yw);
	draw_line (tick_xw1, tick_yw, tick_xw2, tick_yw, MFD_COLOUR1);
	draw_line (tick_xw3, tick_yw, tick_xw4, tick_yw, MFD_COLOUR1);

	get_2d_float_screen_y_coordinate (bar_yvmin + (get_rpm_scale_value (106.0) * BAR_HEIGHT), &tick_yw);
	draw_line (tick_xw1, tick_yw, tick_xw2, tick_yw, MFD_COLOUR1);
	draw_line (tick_xw3, tick_yw, tick_xw4, tick_yw, MFD_COLOUR1);

	get_2d_float_screen_y_coordinate (bar_yvmin + (get_rpm_scale_value (104.0) * BAR_HEIGHT), &tick_yw);
	draw_line (tick_xw1, tick_yw, tick_xw2, tick_yw, MFD_COLOUR1);
	draw_line (tick_xw3, tick_yw, tick_xw4, tick_yw, MFD_COLOUR1);

	get_2d_float_screen_y_coordinate (bar_yvmin + (get_rpm_scale_value (102.0) * BAR_HEIGHT), &tick_yw);
	draw_line (tick_xw1, tick_yw, tick_xw2, tick_yw, MFD_COLOUR1);
	draw_line (tick_xw3, tick_yw, tick_xw4, tick_yw, MFD_COLOUR1);

	get_2d_float_screen_y_coordinate (bar_yvmin + (get_rpm_scale_value (100.0) * BAR_HEIGHT), &tick_yw);
	draw_line (tick_xw1, tick_yw, tick_xw2, tick_yw, MFD_COLOUR1);
	draw_line (tick_xw3, tick_yw, tick_xw4, tick_yw, MFD_COLOUR1);

	if (numeric_scale)
	{
		x_adjust = get_mono_font_string_width ("100") * -0.5;

		set_mono_font_position (text_xw1, tick_yw);

		set_mono_font_rel_position (x_adjust, y_adjust);

		print_mono_font_string ("100");

		set_mono_font_position (text_xw2, tick_yw);

		set_mono_font_rel_position (x_adjust, y_adjust);

		print_mono_font_string ("100");
	}

	get_2d_float_screen_y_coordinate (bar_yvmin + (get_rpm_scale_value (98.0) * BAR_HEIGHT), &tick_yw);
	draw_line (tick_xw1, tick_yw, tick_xw2, tick_yw, MFD_COLOUR1);
	draw_line (tick_xw3, tick_yw, tick_xw4, tick_yw, MFD_COLOUR1);

	get_2d_float_screen_y_coordinate (bar_yvmin + (get_rpm_scale_value (96.0) * BAR_HEIGHT), &tick_yw);
	draw_line (tick_xw1, tick_yw, tick_xw2, tick_yw, MFD_COLOUR1);
	draw_line (tick_xw3, tick_yw, tick_xw4, tick_yw, MFD_COLOUR1);

	get_2d_float_screen_y_coordinate (bar_yvmin + (get_rpm_scale_value (94.0) * BAR_HEIGHT), &tick_yw);
	draw_line (tick_xw1, tick_yw, tick_xw2, tick_yw, MFD_COLOUR1);
	draw_line (tick_xw3, tick_yw, tick_xw4, tick_yw, MFD_COLOUR1);

	get_2d_float_screen_y_coordinate (bar_yvmin + (get_rpm_scale_value (92.0) * BAR_HEIGHT), &tick_yw);
	draw_line (tick_xw1, tick_yw, tick_xw2, tick_yw, MFD_COLOUR1);
	draw_line (tick_xw3, tick_yw, tick_xw4, tick_yw, MFD_COLOUR1);

	get_2d_float_screen_y_coordinate (bar_yvmin + (get_rpm_scale_value (90.0) * BAR_HEIGHT), &tick_yw);
	draw_line (tick_xw1, tick_yw, tick_xw2, tick_yw, MFD_COLOUR1);
	draw_line (tick_xw3, tick_yw, tick_xw4, tick_yw, MFD_COLOUR1);

	if (numeric_scale)
	{
		x_adjust = get_mono_font_string_width ("90") * -0.5;

		set_mono_font_position (text_xw1, tick_yw);

		set_mono_font_rel_position (x_adjust, y_adjust);

		print_mono_font_string ("90");

		set_mono_font_position (text_xw2, tick_yw);

		set_mono_font_rel_position (x_adjust, y_adjust);

		print_mono_font_string ("90");
	}

	get_2d_float_screen_y_coordinate (bar_yvmin + (get_rpm_scale_value (70.0) * BAR_HEIGHT), &tick_yw);
	draw_line (tick_xw1, tick_yw, tick_xw2, tick_yw, MFD_COLOUR1);
	draw_line (tick_xw3, tick_yw, tick_xw4, tick_yw, MFD_COLOUR1);

	if (numeric_scale)
	{
		x_adjust = get_mono_font_string_width ("70") * -0.5;

		set_mono_font_position (text_xw1, tick_yw);

		set_mono_font_rel_position (x_adjust, y_adjust);

		print_mono_font_string ("70");

		set_mono_font_position (text_xw2, tick_yw);

		set_mono_font_rel_position (x_adjust, y_adjust);

		print_mono_font_string ("70");
	}

	get_2d_float_screen_y_coordinate (bar_yvmin + (get_rpm_scale_value (50.0) * BAR_HEIGHT), &tick_yw);
	draw_line (tick_xw1, tick_yw, tick_xw2, tick_yw, MFD_COLOUR1);
	draw_line (tick_xw3, tick_yw, tick_xw4, tick_yw, MFD_COLOUR1);

	if (numeric_scale)
	{
		x_adjust = get_mono_font_string_width ("50") * -0.5;

		set_mono_font_position (text_xw1, tick_yw);

		set_mono_font_rel_position (x_adjust, y_adjust);

		print_mono_font_string ("50");

		set_mono_font_position (text_xw2, tick_yw);

		set_mono_font_rel_position (x_adjust, y_adjust);

		print_mono_font_string ("50");
	}

	get_2d_float_screen_y_coordinate (bar_yvmin + (get_rpm_scale_value (0.0) * BAR_HEIGHT), &tick_yw);
	draw_line (tick_xw1, tick_yw, tick_xw2, tick_yw, MFD_COLOUR1);
	draw_line (tick_xw3, tick_yw, tick_xw4, tick_yw, MFD_COLOUR1);

	////////////////////////////////////////

	get_2d_int_screen_coordinates (bar_xvmin, bar_yvmin + (get_rpm_scale_value (rpm_value) * BAR_HEIGHT), &ix1, &iy1);
	get_2d_int_screen_coordinates (bar_xvmax, bar_yvmin, &ix2, &iy2);
	set_block (ix1, iy1, ix2, iy2, MFD_COLOUR1);

	////////////////////////////////////////

	if (numeric_scale)
	{
		if (draw_large_mfd)
		{
			set_mono_font_type (MONO_FONT_TYPE_6X10);
		}
		else
		{
			set_mono_font_type (MONO_FONT_TYPE_3X6);
		}
	}
}

#undef BAR_WIDTH
#undef BAR_HEIGHT

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float get_torque_scale_value (float torque_value)
{
	ASSERT ((torque_value >= 0.0) && (torque_value <= 120.0));

	return (torque_value * ((float) (1.0 / 120.0)));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define BAR_WIDTH		((float) (0.1))
#define BAR_HEIGHT	((float) (1.5))

static void draw_torque_bar (char *title, float xv_org, float yv_org, float torque_value, int numeric_scale)
{
	char
		s[80];

	int
		ix1,
		iy1,
		ix2,
		iy2,
		digital_readout;

	float
		x_adjust,
		y_adjust,
		bar_xvmin,
		bar_yvmin,
		bar_xvmax,
		bar_yvmax,
		tick_length,
		tick_xw1,
		tick_xw2,
		tick_xw3,
		tick_xw4,
		tick_yw,
		text_xw1;

	ASSERT (title);

	////////////////////////////////////////

	bar_xvmin = xv_org - (BAR_WIDTH * 0.5);
	bar_yvmin = yv_org - BAR_HEIGHT;
	bar_xvmax = xv_org + (BAR_WIDTH * 0.5);
	bar_yvmax = yv_org;

	////////////////////////////////////////

	set_2d_mono_font_position (xv_org, yv_org + 0.1);

	x_adjust = get_mono_font_string_width (title) * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string (title);

	////////////////////////////////////////

	torque_value = bound (torque_value, 0.0, 120.0);

	convert_float_to_int (torque_value, &digital_readout);

	sprintf (s, "%03d", digital_readout);

	set_2d_mono_font_position (xv_org, bar_yvmin - 0.1);

	x_adjust = get_mono_font_string_width (s) * -0.5;

	y_adjust = draw_large_mfd ? -6.0 : -3.0;

	set_mono_font_rel_position (x_adjust, y_adjust);

	print_mono_font_string (s);

	////////////////////////////////////////

	if (numeric_scale)
	{
		if (draw_large_mfd)
		{
			set_mono_font_type (MONO_FONT_TYPE_5X9);

			y_adjust = -3.0;
		}
		else
		{
			set_mono_font_type (MONO_FONT_TYPE_3X6);

			y_adjust = -2.0;
		}

		get_2d_float_screen_x_coordinate (bar_xvmax + 0.1, &text_xw1);
	}

	////////////////////////////////////////

	draw_2d_line (bar_xvmin, bar_yvmax, bar_xvmin, bar_yvmin, MFD_COLOUR1);
	draw_2d_line (bar_xvmax, bar_yvmax, bar_xvmax, bar_yvmin, MFD_COLOUR1);
	draw_2d_line (bar_xvmin, bar_yvmax, bar_xvmax, bar_yvmax, MFD_COLOUR1);
	draw_2d_line (bar_xvmin, bar_yvmin, bar_xvmax, bar_yvmin, MFD_COLOUR1);

	////////////////////////////////////////

	tick_length = draw_large_mfd ? 2.0 : 1.0;

	get_2d_float_screen_x_coordinate (bar_xvmin, &tick_xw1);
	tick_xw2 = tick_xw1 - tick_length;

	get_2d_float_screen_x_coordinate (bar_xvmax, &tick_xw3);
	tick_xw4 = tick_xw3 + tick_length;

	////////////////////////////////////////

	get_2d_float_screen_y_coordinate (bar_yvmin + (get_torque_scale_value (120.0) * BAR_HEIGHT), &tick_yw);
	draw_line (tick_xw1, tick_yw, tick_xw2, tick_yw, MFD_COLOUR1);
	draw_line (tick_xw3, tick_yw, tick_xw4, tick_yw, MFD_COLOUR1);

	if (numeric_scale)
	{
		x_adjust = get_mono_font_string_width ("120") * -0.5;

		set_mono_font_position (text_xw1, tick_yw);

		set_mono_font_rel_position (x_adjust, y_adjust);

		print_mono_font_string ("120");
	}

	get_2d_float_screen_y_coordinate (bar_yvmin + (get_torque_scale_value (110.0) * BAR_HEIGHT), &tick_yw);
	draw_line (tick_xw1, tick_yw, tick_xw2, tick_yw, MFD_COLOUR1);
	draw_line (tick_xw3, tick_yw, tick_xw4, tick_yw, MFD_COLOUR1);

	get_2d_float_screen_y_coordinate (bar_yvmin + (get_torque_scale_value (100.0) * BAR_HEIGHT), &tick_yw);
	draw_line (tick_xw1, tick_yw, tick_xw2, tick_yw, MFD_COLOUR1);
	draw_line (tick_xw3, tick_yw, tick_xw4, tick_yw, MFD_COLOUR1);

	if (numeric_scale)
	{
		x_adjust = get_mono_font_string_width ("100") * -0.5;

		set_mono_font_position (text_xw1, tick_yw);

		set_mono_font_rel_position (x_adjust, y_adjust);

		print_mono_font_string ("100");
	}

	get_2d_float_screen_y_coordinate (bar_yvmin + (get_torque_scale_value (70.0) * BAR_HEIGHT), &tick_yw);
	draw_line (tick_xw1, tick_yw, tick_xw2, tick_yw, MFD_COLOUR1);
	draw_line (tick_xw3, tick_yw, tick_xw4, tick_yw, MFD_COLOUR1);

	if (numeric_scale)
	{
		x_adjust = get_mono_font_string_width ("70") * -0.5;

		set_mono_font_position (text_xw1, tick_yw);

		set_mono_font_rel_position (x_adjust, y_adjust);

		print_mono_font_string ("70");
	}

	get_2d_float_screen_y_coordinate (bar_yvmin + (get_torque_scale_value (50.0) * BAR_HEIGHT), &tick_yw);
	draw_line (tick_xw1, tick_yw, tick_xw2, tick_yw, MFD_COLOUR1);
	draw_line (tick_xw3, tick_yw, tick_xw4, tick_yw, MFD_COLOUR1);

	if (numeric_scale)
	{
		x_adjust = get_mono_font_string_width ("50") * -0.5;

		set_mono_font_position (text_xw1, tick_yw);

		set_mono_font_rel_position (x_adjust, y_adjust);

		print_mono_font_string ("50");
	}

	get_2d_float_screen_y_coordinate (bar_yvmin + (get_torque_scale_value (0.0) * BAR_HEIGHT), &tick_yw);
	draw_line (tick_xw1, tick_yw, tick_xw2, tick_yw, MFD_COLOUR1);
	draw_line (tick_xw3, tick_yw, tick_xw4, tick_yw, MFD_COLOUR1);

	////////////////////////////////////////

	get_2d_int_screen_coordinates (bar_xvmin, bar_yvmin + (get_torque_scale_value (torque_value) * BAR_HEIGHT), &ix1, &iy1);
	get_2d_int_screen_coordinates (bar_xvmax, bar_yvmin, &ix2, &iy2);
	set_block (ix1, iy1, ix2, iy2, MFD_COLOUR1);

	////////////////////////////////////////

	if (numeric_scale)
	{
		if (draw_large_mfd)
		{
			set_mono_font_type (MONO_FONT_TYPE_6X10);
		}
		else
		{
			set_mono_font_type (MONO_FONT_TYPE_3X6);
		}
	}
}

#undef BAR_WIDTH
#undef BAR_HEIGHT

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float get_temp_scale_value (float temp_value)
{
	ASSERT ((temp_value >= 0.0) && (temp_value <= 999.0));

	return (temp_value * ((float) (1.0 / 999.0)));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define BAR_WIDTH		((float) (0.1))
#define BAR_HEIGHT	((float) (0.5))

static void draw_temp_bar (char *title, float xv_org, float yv_org, float temp_value)
{
	char
		s[80];

	int
		ix1,
		iy1,
		ix2,
		iy2,
		digital_readout;

	float
		x_adjust,
		y_adjust,
		bar_xvmin,
		bar_yvmin,
		bar_xvmax,
		bar_yvmax,
		tick_length,
		tick_xw1,
		tick_xw2,
		tick_xw3,
		tick_xw4,
		tick_yw;

	ASSERT (title);

	////////////////////////////////////////

	bar_xvmin = xv_org - (BAR_WIDTH * 0.5);
	bar_yvmin = yv_org - BAR_HEIGHT;
	bar_xvmax = xv_org + (BAR_WIDTH * 0.5);
	bar_yvmax = yv_org;

	////////////////////////////////////////

	set_2d_mono_font_position (xv_org, yv_org + 0.1);

	x_adjust = get_mono_font_string_width (title) * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string (title);

	////////////////////////////////////////

	temp_value = bound (temp_value, 0.0, 999.0);

	convert_float_to_int (temp_value, &digital_readout);

	sprintf (s, "%03d", digital_readout);

	set_2d_mono_font_position (xv_org, bar_yvmin - 0.1);

	x_adjust = get_mono_font_string_width (s) * -0.5;

	y_adjust = draw_large_mfd ? -6.0 : -3.0;

	set_mono_font_rel_position (x_adjust, y_adjust);

	print_mono_font_string (s);

	////////////////////////////////////////

	draw_2d_line (bar_xvmin, bar_yvmax, bar_xvmin, bar_yvmin, MFD_COLOUR1);
	draw_2d_line (bar_xvmax, bar_yvmax, bar_xvmax, bar_yvmin, MFD_COLOUR1);
	draw_2d_line (bar_xvmin, bar_yvmax, bar_xvmax, bar_yvmax, MFD_COLOUR1);
	draw_2d_line (bar_xvmin, bar_yvmin, bar_xvmax, bar_yvmin, MFD_COLOUR1);

	////////////////////////////////////////

	tick_length = draw_large_mfd ? 2.0 : 1.0;

	get_2d_float_screen_x_coordinate (bar_xvmin, &tick_xw1);
	tick_xw2 = tick_xw1 - tick_length;

	get_2d_float_screen_x_coordinate (bar_xvmax, &tick_xw3);
	tick_xw4 = tick_xw3 + tick_length;

	////////////////////////////////////////

	get_2d_float_screen_y_coordinate (bar_yvmin + (get_temp_scale_value (900.0) * BAR_HEIGHT), &tick_yw);
	draw_line (tick_xw1, tick_yw, tick_xw2, tick_yw, MFD_COLOUR1);
	draw_line (tick_xw3, tick_yw, tick_xw4, tick_yw, MFD_COLOUR1);

	get_2d_float_screen_y_coordinate (bar_yvmin + (get_temp_scale_value (800.0) * BAR_HEIGHT), &tick_yw);
	draw_line (tick_xw1, tick_yw, tick_xw2, tick_yw, MFD_COLOUR1);
	draw_line (tick_xw3, tick_yw, tick_xw4, tick_yw, MFD_COLOUR1);

	get_2d_float_screen_y_coordinate (bar_yvmin + (get_temp_scale_value (0.0) * BAR_HEIGHT), &tick_yw);
	draw_line (tick_xw1, tick_yw, tick_xw2, tick_yw, MFD_COLOUR1);
	draw_line (tick_xw3, tick_yw, tick_xw4, tick_yw, MFD_COLOUR1);

	get_2d_int_screen_coordinates (bar_xvmin, bar_yvmin + (get_temp_scale_value (temp_value) * BAR_HEIGHT), &ix1, &iy1);
	get_2d_int_screen_coordinates (bar_xvmax, bar_yvmin, &ix2, &iy2);
	set_block (ix1, iy1, ix2, iy2, MFD_COLOUR1);
}

#undef BAR_WIDTH
#undef BAR_HEIGHT

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_engine_display_mfd (void)
{
	char
		s[80];

	int
		ix1,
		iy1,
		ix2,
		iy2,
		ivalue;

	float
		fvalue,
		fuel_ratio,
		x_adjust,
		y_adjust;

	set_mono_font_colour (MFD_COLOUR1);

	if (draw_large_mfd)
	{
		set_mono_font_type (MONO_FONT_TYPE_6X10);
	}
	else
	{
		set_mono_font_type (MONO_FONT_TYPE_3X6);
	}

	////////////////////////////////////////
	//
	// engine and rotor rpm
	//
	////////////////////////////////////////

	set_2d_mono_font_position (-0.600, 0.900);

	x_adjust = get_mono_font_string_width ("Np/Nr") * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string ("Np/Nr");

	draw_rpm_bar ("Np1", -0.900, 0.700, current_flight_dynamics->left_engine_rpm.value, FALSE);

	draw_rpm_bar ("Nr", -0.600, 0.700, current_flight_dynamics->main_rotor_rpm.value, TRUE);

	draw_rpm_bar ("Np2", -0.300, 0.700, current_flight_dynamics->right_engine_rpm.value, FALSE);

	////////////////////////////////////////
	//
	// engine torque
	//
	////////////////////////////////////////

	set_2d_mono_font_position (0.200, 0.900);

	x_adjust = get_mono_font_string_width ("Torque") * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string ("Torque");

	draw_torque_bar ("Eng1", 0.050, 0.700, current_flight_dynamics->left_engine_torque.value, TRUE);

	draw_torque_bar ("Eng2", 0.350, 0.700, current_flight_dynamics->right_engine_torque.value, FALSE);

	////////////////////////////////////////
	//
	// fuel
	//
	////////////////////////////////////////

	fuel_ratio = current_flight_dynamics->fuel_weight.value / current_flight_dynamics->fuel_weight.max;

	fuel_ratio = bound (fuel_ratio, 0.0, 1.0);

	//
	// Fuel
	//

	set_2d_mono_font_position (0.800, 0.550);

	x_adjust = get_mono_font_string_width ("Fuel") * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string ("Fuel");

	fvalue = bound (current_flight_dynamics->fuel_weight.value, 0.0, 9999.0);

	convert_float_to_int (fvalue, &ivalue);

	sprintf (s, "%04d", ivalue);

	set_2d_mono_font_position (0.800, 0.450);

	x_adjust = get_mono_font_string_width (s) * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string (s);

	//
	// Fwd
	//

	set_2d_mono_font_position (0.650, 0.225);

	x_adjust = -get_mono_font_string_width ("Fwd");

	if (draw_large_mfd)
	{
		x_adjust -= 2.0;

		y_adjust = -3.0;
	}
	else
	{
		x_adjust -= 1.0;

		y_adjust = -2.0;
	}

	set_mono_font_rel_position (x_adjust, y_adjust);

	print_mono_font_string ("Fwd");

	draw_2d_line ( 0.650,  0.300,  0.650,  0.150, MFD_COLOUR1);
	draw_2d_line ( 0.950,  0.300,  0.950,  0.150, MFD_COLOUR1);
	draw_2d_line ( 0.650,  0.300,  0.950,  0.300, MFD_COLOUR1);
	draw_2d_line ( 0.650,  0.150,  0.950,  0.150, MFD_COLOUR1);

	draw_2d_line ( 0.710,  0.300,  0.710,  0.325, MFD_COLOUR1);
	draw_2d_line ( 0.710,  0.150,  0.710,  0.125, MFD_COLOUR1);

	get_2d_int_screen_coordinates (0.650, 0.300, &ix1, &iy1);
	get_2d_int_screen_coordinates (0.650 + (0.3 * fuel_ratio), 0.150, &ix2, &iy2);
	set_block (ix1, iy1, ix2, iy2, MFD_COLOUR1);

	//
	// Aft
	//

	set_2d_mono_font_position (0.650, 0.025);

	x_adjust = -get_mono_font_string_width ("Aft");

	if (draw_large_mfd)
	{
		x_adjust -= 2.0;

		y_adjust = -3.0;
	}
	else
	{
		x_adjust -= 1.0;

		y_adjust = -2.0;
	}

	set_mono_font_rel_position (x_adjust, y_adjust);

	print_mono_font_string ("Aft");

	draw_2d_line ( 0.650,  0.100,  0.650, -0.050, MFD_COLOUR1);
	draw_2d_line ( 0.950,  0.100,  0.950, -0.050, MFD_COLOUR1);
	draw_2d_line ( 0.650,  0.100,  0.950,  0.100, MFD_COLOUR1);
	draw_2d_line ( 0.650, -0.050,  0.950, -0.050, MFD_COLOUR1);

	draw_2d_line ( 0.710,  0.100,  0.710,  0.125, MFD_COLOUR1);
	draw_2d_line ( 0.710, -0.050,  0.710, -0.075, MFD_COLOUR1);

	get_2d_int_screen_coordinates (0.650, 0.100, &ix1, &iy1);
	get_2d_int_screen_coordinates (0.650 + (0.3 * fuel_ratio), -0.050, &ix2, &iy2);
	set_block (ix1, iy1, ix2, iy2, MFD_COLOUR1);

	////////////////////////////////////////
	//
	// engine temperature
	//
	////////////////////////////////////////

	draw_temp_bar ("TGT1", 0.600, -0.300, current_flight_dynamics->left_engine_temp.value);

	draw_temp_bar ("TGT2", 0.850, -0.300, current_flight_dynamics->right_engine_temp.value);
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
		x1,
		y1,
		x2,
		y2,
		int_pitch,
		step_direction,
		loop;

	float
		y_adjust_above_line,
		y_adjust_below_line,
		vp_size,
		pitch,
		mod_pitch,
		tan_mod_pitch,
		roll,
		u,
		v,
		x,
		y,
		fx1,
		fy1,
		fx2,
		fy2,
		x_scale,
		y_scale,
		x_horizon,
		y_horizon,
		x_10_deg_step,
		y_10_deg_step,
		x_adjust;

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

	//
	// draw frame
	//

	draw_2d_circle (PITCH_DATUM_X, PITCH_DATUM_Y, 0.6, MFD_COLOUR1);

	get_2d_int_screen_coordinates (PITCH_DATUM_X - 0.6, PITCH_DATUM_Y + 0.6, &x1, &y1);
	get_2d_int_screen_coordinates (PITCH_DATUM_X - 0.4, PITCH_DATUM_Y - 0.6, &x2, &y2);

	set_block (x1, y1, x2 - 1, y2, MFD_BACKGROUND_COLOUR);

	get_2d_int_screen_coordinates (PITCH_DATUM_X + 0.4, PITCH_DATUM_Y + 0.6, &x1, &y1);
	get_2d_int_screen_coordinates (PITCH_DATUM_X + 0.6, PITCH_DATUM_Y - 0.6, &x2, &y2);

	set_block (x1 + 1, y1, x2, y2, MFD_BACKGROUND_COLOUR);

	get_2d_float_screen_coordinates (PITCH_DATUM_X - 0.4, PITCH_DATUM_Y + 0.4, &fx1, &fy1);
	get_2d_float_screen_coordinates (PITCH_DATUM_X - 0.4, PITCH_DATUM_Y - 0.4, &fx2, &fy2);

	if (draw_large_mfd)
	{
		fy1 -= 4.0;
		fy2 += 3.0;
	}
	else
	{
		fy1 -= 2.0;
		fy2 += 1.0;
	}

	draw_line (fx1, fy1, fx2, fy2, MFD_COLOUR1);

	get_2d_float_screen_coordinates (PITCH_DATUM_X + 0.4, PITCH_DATUM_Y + 0.4, &fx1, &fy1);
	get_2d_float_screen_coordinates (PITCH_DATUM_X + 0.4, PITCH_DATUM_Y - 0.4, &fx2, &fy2);

	if (draw_large_mfd)
	{
		fy1 -= 5.0;
		fy2 += 4.0;
	}
	else
	{
		fy1 -= 3.0;
		fy2 += 1.0;
	}

	draw_line (fx1, fy1, fx2, fy2, MFD_COLOUR1);

	//
	// datum
	//

	get_2d_float_screen_coordinates (PITCH_DATUM_X, PITCH_DATUM_Y, &u, &v);

	if (draw_large_mfd)
	{
		draw_line (u, v, u + 6.0, v + 6.0, MFD_COLOUR1);
		draw_line (u + 6.0, v + 6.0, u + 12.0, v, MFD_COLOUR1);

		draw_line (u, v, u - 6.0, v + 6.0, MFD_COLOUR1);
		draw_line (u - 6.0, v + 6.0, u - 12.0, v, MFD_COLOUR1);
	}
	else
	{
		draw_line (u, v, u + 3.0, v + 3.0, MFD_COLOUR1);
		draw_line (u + 3.0, v + 3.0, u + 6.0, v, MFD_COLOUR1);

		draw_line (u, v, u - 3.0, v + 3.0, MFD_COLOUR1);
		draw_line (u - 3.0, v + 3.0, u - 6.0, v, MFD_COLOUR1);
	}

	draw_2d_line (PITCH_DATUM_X + 0.10, PITCH_DATUM_Y + 0.00, PITCH_DATUM_X + 0.30, PITCH_DATUM_Y + 0.00, MFD_COLOUR1);
	draw_2d_line (PITCH_DATUM_X - 0.10, PITCH_DATUM_Y + 0.00, PITCH_DATUM_X - 0.30, PITCH_DATUM_Y + 0.00, MFD_COLOUR1);

	//
	// roll
	//

	roll = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_ROLL);

	set_2d_instance_position (mfd_env, PITCH_DATUM_X, PITCH_DATUM_Y);

	set_2d_instance_rotation (mfd_env, rad (0.0));
	draw_2d_line (0.0, -0.59, 0.0, -0.59 + 0.05, MFD_COLOUR1);

	set_2d_instance_rotation (mfd_env, rad (10.0));
	draw_2d_line (0.0, -0.59, 0.0, -0.59 + 0.025, MFD_COLOUR1);
	set_2d_instance_rotation (mfd_env, rad (-10.0));
	draw_2d_line (0.0, -0.59, 0.0, -0.59 + 0.025, MFD_COLOUR1);

	set_2d_instance_rotation (mfd_env, rad (20.0));
	draw_2d_line (0.0, -0.59, 0.0, -0.59 + 0.025, MFD_COLOUR1);
	set_2d_instance_rotation (mfd_env, rad (-20.0));
	draw_2d_line (0.0, -0.59, 0.0, -0.59 + 0.025, MFD_COLOUR1);

	set_2d_instance_rotation (mfd_env, rad (30.0));
	draw_2d_line (0.0, -0.59, 0.0, -0.59 + 0.05, MFD_COLOUR1);
	set_2d_instance_rotation (mfd_env, rad (-30.0));
	draw_2d_line (0.0, -0.59, 0.0, -0.59 + 0.05, MFD_COLOUR1);

	set_2d_instance_rotation (mfd_env, bound (roll, rad (-30.0), rad (30.0)));
	draw_2d_line ( 0.0, -0.6,  0.025, -0.6 - 0.05, MFD_COLOUR1);
	draw_2d_line ( 0.0, -0.6, -0.025, -0.6 - 0.05, MFD_COLOUR1);
	draw_2d_line (-0.025, -0.6 - 0.05,  0.025, -0.6 - 0.05, MFD_COLOUR1);

	//
	// set 2D environment
	//

	set_2d_window (mfd_env, MFD_WINDOW_X_MIN * 0.4, MFD_WINDOW_Y_MIN * 0.4, MFD_WINDOW_X_MAX * 0.4, MFD_WINDOW_Y_MAX * 0.4);

	vp_size = mfd_viewport_size * 0.4 * 0.5;

	set_2d_viewport (mfd_env, u - vp_size, v - vp_size, u + vp_size - 0.001, v + vp_size - 0.001);

	//
	// pitch
	//

	pitch = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_PITCH);

	mod_pitch = fmod (pitch, rad (10.0));

	tan_mod_pitch = -tan (mod_pitch);

	int_pitch = (int) (pitch * (1.0 / rad (10.0)));

	//
	// get x and y scale factors
	//

	x_scale = -sin (roll) * 1.5;

	y_scale = cos (roll) * 1.5;

	x_horizon = tan_mod_pitch * x_scale;
	y_horizon = tan_mod_pitch * y_scale;

	x_10_deg_step = tan (rad (10.0)) * x_scale;
	y_10_deg_step = tan (rad (10.0)) * y_scale;

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
				draw_2d_line (-PITCH_BAR_X7, +PITCH_BAR_Y7, +PITCH_BAR_X7, +PITCH_BAR_Y7, MFD_COLOUR1);

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
					draw_2d_line (+PITCH_BAR_X1, +PITCH_BAR_Y1, +PITCH_BAR_X6, +PITCH_BAR_Y6, MFD_COLOUR1);
					draw_2d_line (-PITCH_BAR_X1, +PITCH_BAR_Y1, -PITCH_BAR_X6, +PITCH_BAR_Y6, MFD_COLOUR1);

					draw_2d_line (+PITCH_BAR_X6, +PITCH_BAR_Y6, +PITCH_BAR_X8, +PITCH_BAR_Y8, MFD_COLOUR1);
					draw_2d_line (-PITCH_BAR_X6, +PITCH_BAR_Y6, -PITCH_BAR_X8, +PITCH_BAR_Y8, MFD_COLOUR1);
				}
				else
				{
					draw_2d_line (-PITCH_BAR_X1, -PITCH_BAR_Y1, -PITCH_BAR_X6, -PITCH_BAR_Y6, MFD_COLOUR1);
					draw_2d_line (+PITCH_BAR_X1, -PITCH_BAR_Y1, +PITCH_BAR_X6, -PITCH_BAR_Y6, MFD_COLOUR1);

					draw_2d_line (-PITCH_BAR_X6, -PITCH_BAR_Y6, -PITCH_BAR_X8, -PITCH_BAR_Y8, MFD_COLOUR1);
					draw_2d_line (+PITCH_BAR_X6, -PITCH_BAR_Y6, +PITCH_BAR_X8, -PITCH_BAR_Y8, MFD_COLOUR1);
				}

				sprintf (s, "%d0", int_pitch);

				x_adjust = get_mono_font_string_width (s) * -0.5;

				set_2d_mono_font_position (-PITCH_BAR_X10, +PITCH_BAR_Y10);

				set_mono_font_rel_position (x_adjust, y_adjust_above_line);

				print_mono_font_string (s);

				break;
			}
			////////////////////////////////////////
			case 9:
			////////////////////////////////////////
			{
				draw_2d_line (+PITCH_BAR_X1, +PITCH_BAR_Y1, +PITCH_BAR_X6, +PITCH_BAR_Y6, MFD_COLOUR1);
				draw_2d_line (-PITCH_BAR_X1, +PITCH_BAR_Y1, -PITCH_BAR_X6, +PITCH_BAR_Y6, MFD_COLOUR1);

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
					draw_2d_line (+PITCH_BAR_X1, +PITCH_BAR_Y1, +PITCH_BAR_X6, +PITCH_BAR_Y6, MFD_COLOUR1);
					draw_2d_line (-PITCH_BAR_X1, +PITCH_BAR_Y1, -PITCH_BAR_X6, +PITCH_BAR_Y6, MFD_COLOUR1);

					draw_2d_line (+PITCH_BAR_X6, +PITCH_BAR_Y6, +PITCH_BAR_X9, +PITCH_BAR_Y9, MFD_COLOUR1);
					draw_2d_line (-PITCH_BAR_X6, +PITCH_BAR_Y6, -PITCH_BAR_X9, +PITCH_BAR_Y9, MFD_COLOUR1);
				}
				else
				{
					draw_2d_line (-PITCH_BAR_X1, -PITCH_BAR_Y1, -PITCH_BAR_X6, -PITCH_BAR_Y6, MFD_COLOUR1);
					draw_2d_line (+PITCH_BAR_X1, -PITCH_BAR_Y1, +PITCH_BAR_X6, -PITCH_BAR_Y6, MFD_COLOUR1);

					draw_2d_line (-PITCH_BAR_X6, -PITCH_BAR_Y6, -PITCH_BAR_X9, -PITCH_BAR_Y9, MFD_COLOUR1);
					draw_2d_line (+PITCH_BAR_X6, -PITCH_BAR_Y6, +PITCH_BAR_X9, -PITCH_BAR_Y9, MFD_COLOUR1);
				}

				sprintf (s, "%d0", int_pitch);

				x_adjust = get_mono_font_string_width (s) * -0.5;

				set_2d_mono_font_position (-PITCH_BAR_X11, +PITCH_BAR_Y11);

				set_mono_font_rel_position (x_adjust, y_adjust_below_line);

				print_mono_font_string (s);

				break;
			}
			////////////////////////////////////////
			case -9:
			////////////////////////////////////////
			{
				draw_2d_line (+PITCH_BAR_X1, +PITCH_BAR_Y1, +PITCH_BAR_X2, +PITCH_BAR_Y2, MFD_COLOUR1);
				draw_2d_line (-PITCH_BAR_X1, +PITCH_BAR_Y1, -PITCH_BAR_X2, +PITCH_BAR_Y2, MFD_COLOUR1);

				draw_2d_line (+PITCH_BAR_X3, +PITCH_BAR_Y3, +PITCH_BAR_X4, +PITCH_BAR_Y4, MFD_COLOUR1);
				draw_2d_line (-PITCH_BAR_X3, +PITCH_BAR_Y3, -PITCH_BAR_X4, +PITCH_BAR_Y4, MFD_COLOUR1);

				draw_2d_line (+PITCH_BAR_X5, +PITCH_BAR_Y5, +PITCH_BAR_X6, +PITCH_BAR_Y6, MFD_COLOUR1);
				draw_2d_line (-PITCH_BAR_X5, +PITCH_BAR_Y5, -PITCH_BAR_X6, +PITCH_BAR_Y6, MFD_COLOUR1);

				break;
			}
		}

		int_pitch = limit_pitch (int_pitch + step_direction, &step_direction);

		x -= x_10_deg_step;
		y -= y_10_deg_step;
	}

	//
	// restore 2D environment
	//

	reset_2d_instance (mfd_env);

	set_2d_window (mfd_env, MFD_WINDOW_X_MIN, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX, MFD_WINDOW_Y_MAX);

	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);
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

	true_airspeed = kilometres_per_hour (true_airspeed);

	sprintf (s, "%d", (int) true_airspeed);

	set_2d_mono_font_position (-1.0, 0.0);

	if (draw_large_mfd)
	{
		set_mono_font_type (MONO_FONT_TYPE_7X12);

		set_mono_font_rel_position (1.0, -4.0);
	}
	else
	{
		set_mono_font_type (MONO_FONT_TYPE_5X9);

		set_mono_font_rel_position (1.0, -3.0);
	}

	print_mono_font_string (s);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_altitude (void)
{
	float
		radar_altitude,
		barometric_altitude,
		width;

	char
		s[20];

	radar_altitude = current_flight_dynamics->radar_altitude.value;

	if (radar_altitude < 500.0)
	{
		sprintf (s, "R%d", (int) radar_altitude);
	}
	else
	{
		barometric_altitude = current_flight_dynamics->barometric_altitude.value;

		sprintf (s, "%d", (int) barometric_altitude);
	}

	width = get_mono_font_string_width (s);

	set_2d_mono_font_position (1.0, 0.8);

	if (draw_large_mfd)
	{
		set_mono_font_type (MONO_FONT_TYPE_7X12);

		set_mono_font_rel_position (-width - 2.0, 0.0);
	}
	else
	{
		set_mono_font_type (MONO_FONT_TYPE_5X9);

		set_mono_font_rel_position (-width - 1.0, 0.0);
	}

	print_mono_font_string (s);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//
// rate of climb scale
//
////////////////////////////////////////

static char large_mfd_rate_of_climb_scale_pointer[] =
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

static char small_mfd_rate_of_climb_scale_pointer[] =
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

	draw_2d_line (+0.800, +0.500, +0.800, -0.500, MFD_COLOUR1);

	draw_2d_line (+0.800, +0.500, +0.850, +0.500, MFD_COLOUR1);
	draw_2d_line (+0.800, +0.400, +0.825, +0.400, MFD_COLOUR1);
	draw_2d_line (+0.800, +0.300, +0.825, +0.300, MFD_COLOUR1);
	draw_2d_line (+0.800, +0.200, +0.825, +0.200, MFD_COLOUR1);
	draw_2d_line (+0.800, +0.100, +0.825, +0.100, MFD_COLOUR1);
	draw_2d_line (+0.800, +0.000, +0.850, +0.000, MFD_COLOUR1);
	draw_2d_line (+0.800, -0.100, +0.825, -0.100, MFD_COLOUR1);
	draw_2d_line (+0.800, -0.200, +0.825, -0.200, MFD_COLOUR1);
	draw_2d_line (+0.800, -0.300, +0.825, -0.300, MFD_COLOUR1);
	draw_2d_line (+0.800, -0.400, +0.825, -0.400, MFD_COLOUR1);
	draw_2d_line (+0.800, -0.500, +0.850, -0.500, MFD_COLOUR1);

	//
	// get indicator position (fsd +/- 10m/s)
	//

	y = current_flight_dynamics->world_velocity_y.value;

	y = bound (y, -10.0, 10.0);

	y *= 0.05;

	//
	// draw indicator and fsd values
	//

	draw_2d_line (0.8, y, 0.85, y, MFD_COLOUR1);

	get_2d_float_screen_coordinates (0.85, y, &i, &j);

	if (draw_large_mfd)
	{
		draw_mono_sprite (large_mfd_rate_of_climb_scale_pointer, i + 1.0, j, MFD_COLOUR1);

		set_mono_font_type (MONO_FONT_TYPE_6X10);

		set_2d_mono_font_position (1.0, 0.5);

		width = get_mono_font_string_width ("10");

		set_mono_font_rel_position (-width - 2.0, -12.0);

		print_mono_font_string ("10");

		set_2d_mono_font_position (1.0, -0.5);

		width = get_mono_font_string_width ("-10");

		set_mono_font_rel_position (-width - 2.0, 6.0);

		print_mono_font_string ("-10");
	}
	else
	{
		draw_mono_sprite (small_mfd_rate_of_climb_scale_pointer, i + 1.0, j, MFD_COLOUR1);

		set_mono_font_type (MONO_FONT_TYPE_6X7);

		set_2d_mono_font_position (1.0, 0.5);

		width = get_mono_font_string_width ("10");

		set_mono_font_rel_position (-width - 1.0, -8.0);

		print_mono_font_string ("10");

		set_2d_mono_font_position (1.0, -0.5);

		width = get_mono_font_string_width ("-10");

		set_mono_font_rel_position (-width - 1.0, 4.0);

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

	sprintf (s, "%d%%", (int) current_flight_dynamics->combined_engine_torque.value);

	set_2d_mono_font_position (-1.0, 0.8);

	if (draw_large_mfd)
	{
		set_mono_font_type (MONO_FONT_TYPE_7X12);

		set_mono_font_rel_position (1.0, 0.0);
	}
	else
	{
		set_mono_font_type (MONO_FONT_TYPE_5X9);

		set_mono_font_rel_position (1.0, 0.0);
	}

	print_mono_font_string (s);
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
			set_mono_font_type (MONO_FONT_TYPE_6X10);
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

		set_2d_mono_font_position (-1.0, -0.7);

		set_mono_font_rel_position (1.0, 0.0);

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

		set_2d_mono_font_position (-1.0, -0.8);

		set_mono_font_rel_position (1.0, 0.0);

		print_mono_font_string (buffer);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_flight_display_mfd (void)
{
	set_mono_font_colour (MFD_COLOUR1);

	draw_pitch_ladder ();

	draw_heading_scale (get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_HEADING), TRUE);

	display_true_airspeed ();

	display_altitude ();

	draw_rate_of_climb_scale ();

	display_engine_torque ();

	display_waypoint_information ();
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

		set_mono_font_colour (MFD_COLOUR1);

		draw_line (x_min, y_adjust, x_max, y_adjust, MFD_COLOUR1);

		y_adjust += 2.0;

		x_adjust = get_mono_font_string_width ("FLIGHT GROUP") * 0.5;

		set_mono_font_position (x_mid - x_adjust, y_adjust);

		print_mono_font_string ("FLIGHT GROUP");

		y_adjust += char_height;

		if (draw_large_mfd)
		{
			y_adjust -= 1.0;
		}

		draw_line (x_min, y_adjust, x_max, y_adjust, MFD_COLOUR1);

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

		set_mono_font_colour (MFD_COLOUR1);

		draw_line (x_min, y_adjust, x_max, y_adjust, MFD_COLOUR1);

		y_adjust += 2.0;

		x_adjust = get_mono_font_string_width ("MISSION") * 0.5;

		set_mono_font_position (x_mid - x_adjust, y_adjust);

		print_mono_font_string ("MISSION");

		y_adjust += char_height;

		if (draw_large_mfd)
		{
			y_adjust -= 1.0;
		}

		draw_line (x_min, y_adjust, x_max, y_adjust, MFD_COLOUR1);

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

		keysite = get_local_entity_ptr_value (task, PTR_TYPE_RETURN_KEYSITE);

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

	set_mono_font_colour (MFD_COLOUR1);

	get_2d_float_screen_y_coordinate (-0.9, &y_adjust);

	y_adjust -= 2.0;

	draw_line (x_min, y_adjust, x_max, y_adjust, MFD_COLOUR1);

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

static void draw_mfd (screen *mfd_screen, hokum_mfd_modes mode, hokum_mfd_locations location)
{
	ASSERT (mfd_screen);

	ASSERT (hokum_mfd_mode_valid (mode));

	ASSERT (hokum_mfd_location_valid (location));

	if ((get_undamaged_eo_display_mode (mode) && d3d_can_render_to_texture))
	{
		return;
	}

	set_active_screen (mfd_screen);

	if (lock_screen (mfd_screen))
	{
		set_block (0, 0, int_mfd_viewport_size - 1, int_mfd_viewport_size - 1, MFD_BACKGROUND_COLOUR);

		draw_layout_grid ();

		switch (mode)
		{
			////////////////////////////////////////
			case HOKUM_MFD_MODE_OFF:
			////////////////////////////////////////
			{
				break;
			}
			////////////////////////////////////////
			case HOKUM_MFD_MODE_DAMAGED:
			////////////////////////////////////////
			{
				draw_damaged_mfd ();

				break;
			}
			////////////////////////////////////////
			case HOKUM_MFD_MODE_GROUND_RADAR:
			////////////////////////////////////////
			{
				draw_ground_radar_mfd ();

				break;
			}
			////////////////////////////////////////
			case HOKUM_MFD_MODE_AIR_RADAR:
			////////////////////////////////////////
			{
				draw_air_radar_mfd ();

				break;
			}
			////////////////////////////////////////
			case HOKUM_MFD_MODE_FLIR:
			////////////////////////////////////////
			{
				draw_2d_flir_mfd (FALSE);

				break;
			}
			////////////////////////////////////////
			case HOKUM_MFD_MODE_LLLTV:
			////////////////////////////////////////
			{
				draw_2d_llltv_mfd (FALSE);

				break;
			}
			////////////////////////////////////////
			case HOKUM_MFD_MODE_PERISCOPE:
			////////////////////////////////////////
			{
				draw_2d_periscope_mfd (FALSE);

				break;
			}
			////////////////////////////////////////
			case HOKUM_MFD_MODE_TSD:
			////////////////////////////////////////
			{
				draw_tactical_situation_display_mfd (location);

				break;
			}
			////////////////////////////////////////
			case HOKUM_MFD_MODE_ASE:
			////////////////////////////////////////
			{
				draw_aircraft_survivability_equipment_display_mfd (location);

				break;
			}
			////////////////////////////////////////
			case HOKUM_MFD_MODE_WEAPON:
			////////////////////////////////////////
			{
				draw_weapon_display_mfd ();

				break;
			}
			////////////////////////////////////////
			case HOKUM_MFD_MODE_SYSTEM:
			////////////////////////////////////////
			{
				draw_system_display_mfd ();

				break;
			}
			////////////////////////////////////////
			case HOKUM_MFD_MODE_ENGINE:
			////////////////////////////////////////
			{
				draw_engine_display_mfd ();

				break;
			}
			////////////////////////////////////////
			case HOKUM_MFD_MODE_FLIGHT:
			////////////////////////////////////////
			{
				draw_flight_display_mfd ();

				break;
			}
			////////////////////////////////////////
			case HOKUM_MFD_MODE_MISSION:
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

		flush_screen_texture_graphics (mfd_screen);

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

		draw_layout_grid ();

		set_mono_font_colour (TEXT_COLOUR1);

		if (draw_large_mfd)
		{
			set_mono_font_type (MONO_FONT_TYPE_7X12);

			set_2d_mono_font_position (-1.0, 1.0);

			set_mono_font_rel_position (1.0, 11.0);

			print_mono_font_string (text_display_line1);

			set_2d_mono_font_position (-1.0, 1.0);

			set_mono_font_rel_position (1.0, 25.0);

			print_mono_font_string (text_display_line2);

			set_2d_mono_font_position (-1.0, 1.0);

			set_mono_font_rel_position (1.0, 39.0);

			print_mono_font_string (text_display_line3);
		}
		else
		{
			set_mono_font_type (MONO_FONT_TYPE_3X6);

			set_2d_mono_font_position (-1.0, 1.0);

			set_mono_font_rel_position (1.0, 5.0);

			print_mono_font_string (text_display_line1);

			set_2d_mono_font_position (-1.0, 1.0);

			set_mono_font_rel_position (1.0, 12.0);

			print_mono_font_string (text_display_line2);

			set_2d_mono_font_position (-1.0, 1.0);

			set_mono_font_rel_position (1.0, 19.0);

			print_mono_font_string (text_display_line3);
		}

		flush_screen_texture_graphics (text_screen);

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

void initialise_hokum_mfd (void)
{
	select_hokum_mfd_mode (HOKUM_MFD_MODE_ENGINE, HOKUM_MFD_LOCATION_PILOT_LHS);
	select_hokum_mfd_mode (HOKUM_MFD_MODE_TSD, HOKUM_MFD_LOCATION_PILOT_RHS);

	select_hokum_mfd_mode (HOKUM_MFD_MODE_MISSION, HOKUM_MFD_LOCATION_CO_PILOT_LHS);
	select_hokum_mfd_mode (HOKUM_MFD_MODE_TSD, HOKUM_MFD_LOCATION_CO_PILOT_RHS);

	////////////////////////////////////////

	set_hokum_text_display_text ("", "", "");

	////////////////////////////////////////

	pilot_tsd_ase_range							= TSD_ASE_RANGE_5000;
	pilot_tsd_declutter_level					= TSD_DECLUTTER_LEVEL_NAVIGATION;
	pilot_tsd_threat_line_flash_timer		= TSD_THREAT_LINE_FLASH_RATE;
	pilot_tsd_draw_threat_line_status		= 0;
	pilot_ase_threat_line_flash_timer		= ASE_THREAT_LINE_FLASH_RATE;
	pilot_ase_draw_threat_line_status		= 0;

	co_pilot_tsd_ase_range						= TSD_ASE_RANGE_5000;
	co_pilot_tsd_declutter_level				= TSD_DECLUTTER_LEVEL_TARGET;
	co_pilot_tsd_threat_line_flash_timer	= TSD_THREAT_LINE_FLASH_RATE;
	co_pilot_tsd_draw_threat_line_status	= 0;
	co_pilot_ase_threat_line_flash_timer	= ASE_THREAT_LINE_FLASH_RATE;
	co_pilot_ase_draw_threat_line_status	= 0;

	////////////////////////////////////////

	mfd_env = create_2d_environment ();

	////////////////////////////////////////

	large_pilot_lhs_mfd_texture_screen = create_user_texture_screen (LARGE_MFD_VIEWPORT_SIZE, LARGE_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 0);
	large_pilot_rhs_mfd_texture_screen = create_user_texture_screen (LARGE_MFD_VIEWPORT_SIZE, LARGE_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 0);
	large_co_pilot_lhs_mfd_texture_screen = create_user_texture_screen (LARGE_MFD_VIEWPORT_SIZE, LARGE_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 0);
	large_co_pilot_rhs_mfd_texture_screen = create_user_texture_screen (LARGE_MFD_VIEWPORT_SIZE, LARGE_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 0);
	large_ekran_display_texture_screen = create_user_texture_screen (LARGE_MFD_VIEWPORT_SIZE, LARGE_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 0);

	small_pilot_lhs_mfd_texture_screen = create_user_texture_screen (SMALL_MFD_VIEWPORT_SIZE, SMALL_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 0);
	small_pilot_rhs_mfd_texture_screen = create_user_texture_screen (SMALL_MFD_VIEWPORT_SIZE, SMALL_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 0);
	small_co_pilot_lhs_mfd_texture_screen = create_user_texture_screen (SMALL_MFD_VIEWPORT_SIZE, SMALL_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 0);
	small_co_pilot_rhs_mfd_texture_screen = create_user_texture_screen (SMALL_MFD_VIEWPORT_SIZE, SMALL_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 0);
	small_ekran_display_texture_screen = create_user_texture_screen (SMALL_MFD_VIEWPORT_SIZE, SMALL_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 0);

	full_mfd_texture_screen = create_system_texture_screen (LARGE_MFD_VIEWPORT_SIZE, LARGE_MFD_VIEWPORT_SIZE, TEXTURE_INDEX_AVCKPT_DISPLAY_RHS_MFD, TEXTURE_TYPE_SINGLEALPHA);

	set_rgb_colour (MFD_COLOUR1,            255, 135,   0, 255);
	set_rgb_colour (MFD_COLOUR2,            255,  90,   0, 255);
	set_rgb_colour (MFD_COLOUR3,            200,  65,   0, 255);
	set_rgb_colour (MFD_COLOUR4,            130,  50,   0, 255);
	set_rgb_colour (MFD_COLOUR5,            100,  50,   0, 255);
	set_rgb_colour (MFD_COLOUR6,             50,  25,   0, 255);
	set_rgb_colour (MFD_CONTOUR_COLOUR,     200,  35,   0, 255);
	set_rgb_colour (MFD_RIVER_COLOUR,        50,  75, 225, 255);
	set_rgb_colour (MFD_ROAD_COLOUR,        255, 225,   0, 255);
	set_rgb_colour (MFD_BACKGROUND_COLOUR,   35,  10,   0, 255);
	set_rgb_colour (MFD_CLEAR_COLOUR,         0,   0,   0,   0);

	set_rgb_colour (TEXT_COLOUR1,             0, 243,  97, 255);
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

	weapon_line_points = safe_malloc (sizeof (vec3d) * num_weapon_line_points);

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
	
//VJ 030423 TSd render mod

   Initialise_TSD_render_terrain();
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_hokum_mfd (void)
{
	destroy_2d_environment (mfd_env);

	////////////////////////////////////////

	destroy_screen (large_pilot_lhs_mfd_texture_screen);
	destroy_screen (large_pilot_rhs_mfd_texture_screen);
	destroy_screen (large_co_pilot_lhs_mfd_texture_screen);
	destroy_screen (large_co_pilot_rhs_mfd_texture_screen);
	destroy_screen (large_ekran_display_texture_screen);

	destroy_screen (small_pilot_lhs_mfd_texture_screen);
	destroy_screen (small_pilot_rhs_mfd_texture_screen);
	destroy_screen (small_co_pilot_lhs_mfd_texture_screen);
	destroy_screen (small_co_pilot_rhs_mfd_texture_screen);
	destroy_screen (small_ekran_display_texture_screen);

	destroy_screen (full_mfd_texture_screen);

	////////////////////////////////////////
	//
	// weapon display lines
	//
	////////////////////////////////////////

	safe_free (weapon_line_points);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_hokum_mfd (void)
{
	////////////////////////////////////////
	//
	// SELECT LARGE OR SMALL MFD TEXTURES
	//
	////////////////////////////////////////

	// loke 030420
	// support for high resolution mfd's
	int
		large_mfd;

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

		pilot_lhs_mfd_texture_screen = large_pilot_lhs_mfd_texture_screen;
		pilot_rhs_mfd_texture_screen = large_pilot_rhs_mfd_texture_screen;
		co_pilot_lhs_mfd_texture_screen = large_co_pilot_lhs_mfd_texture_screen;
		co_pilot_rhs_mfd_texture_screen = large_co_pilot_rhs_mfd_texture_screen;
		ekran_display_texture_screen = large_ekran_display_texture_screen;

		eo_3d_texture_screen = large_eo_3d_texture_screen;
	}
	else
	{
		draw_large_mfd = FALSE;

		pilot_lhs_mfd_texture_screen = small_pilot_lhs_mfd_texture_screen;
		pilot_rhs_mfd_texture_screen = small_pilot_rhs_mfd_texture_screen;
		co_pilot_lhs_mfd_texture_screen = small_co_pilot_lhs_mfd_texture_screen;
		co_pilot_rhs_mfd_texture_screen = small_co_pilot_rhs_mfd_texture_screen;
		ekran_display_texture_screen = small_ekran_display_texture_screen;

		eo_3d_texture_screen = small_eo_3d_texture_screen;
	}

	set_system_texture_screen (pilot_lhs_mfd_texture_screen, TEXTURE_INDEX_HOKUM_COCKPIT_MFD_LHS_2);
	set_system_texture_screen (pilot_rhs_mfd_texture_screen, TEXTURE_INDEX_HOKUM_COCKPIT_MFD_LHS_1);
	set_system_texture_screen (co_pilot_lhs_mfd_texture_screen, TEXTURE_INDEX_HOKUM_COCKPIT_MFD_RHS_1);
	set_system_texture_screen (co_pilot_rhs_mfd_texture_screen, TEXTURE_INDEX_HOKUM_COCKPIT_MFD_RHS_2);
	set_system_texture_screen (ekran_display_texture_screen, TEXTURE_INDEX_HOKUM_COCKPIT_EKRAN);

	////////////////////////////////////////
	//
	// SELECT VISIBLE DISPLAYS
	//
	////////////////////////////////////////

	switch (get_view_mode ())
	{
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY:
		////////////////////////////////////////
		{
			display_mask =
				PILOT_LHS_MFD |
				PILOT_RHS_MFD;

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY:
		////////////////////////////////////////
		{
			display_mask =
				PILOT_LHS_MFD |
				PILOT_RHS_MFD;

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY:
		////////////////////////////////////////
		{
			display_mask =
				CO_PILOT_LHS_MFD |
				CO_PILOT_RHS_MFD |
				EKRAN_DISPLAY;

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY:
		////////////////////////////////////////
		{
			display_mask =
				CO_PILOT_LHS_MFD |
				CO_PILOT_RHS_MFD;

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			display_mask =
				PILOT_LHS_MFD |
				PILOT_RHS_MFD |
				CO_PILOT_LHS_MFD |
				CO_PILOT_RHS_MFD |
				EKRAN_DISPLAY;

			break;
		}
	}

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

	mfd_viewport_x_max = mfd_viewport_size - 0.001;

	mfd_viewport_y_max = mfd_viewport_size - 0.001;

	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

	mfd_screen_x_min = 0.0;
	mfd_screen_y_min = 0.0;

	mfd_screen_x_max = mfd_viewport_size - 0.001;
	mfd_screen_y_max = mfd_viewport_size - 0.001;

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

		if (d3d_can_render_to_texture)
		{
			ASSERT (eo_3d_texture_screen);

			draw_eo_display = FALSE;

			if (get_undamaged_eo_display_mode (pilot_lhs_mfd_mode) && (display_mask & PILOT_LHS_MFD))
			{
				set_system_texture_screen (eo_3d_texture_screen, TEXTURE_INDEX_HOKUM_COCKPIT_MFD_LHS_2);

				draw_eo_display = TRUE;
			}

			if (get_undamaged_eo_display_mode (pilot_rhs_mfd_mode) && (display_mask & PILOT_RHS_MFD))
			{
				set_system_texture_screen (eo_3d_texture_screen, TEXTURE_INDEX_HOKUM_COCKPIT_MFD_LHS_1);

				draw_eo_display = TRUE;
			}

			if (get_undamaged_eo_display_mode (co_pilot_lhs_mfd_mode) && (display_mask & CO_PILOT_LHS_MFD))
			{
				set_system_texture_screen (eo_3d_texture_screen, TEXTURE_INDEX_HOKUM_COCKPIT_MFD_RHS_1);

				draw_eo_display = TRUE;
			}

			if (get_undamaged_eo_display_mode (co_pilot_rhs_mfd_mode) && (display_mask & CO_PILOT_RHS_MFD))
			{
				set_system_texture_screen (eo_3d_texture_screen, TEXTURE_INDEX_HOKUM_COCKPIT_MFD_RHS_2);

				draw_eo_display = TRUE;
			}

			if (draw_eo_display)
			{
				switch (get_mfd_mode_for_eo_sensor ())
				{
					case HOKUM_MFD_MODE_FLIR:
					{
						draw_3d_flir_mfd (FALSE);

						break;
					}
					case HOKUM_MFD_MODE_LLLTV:
					{
						draw_3d_llltv_mfd (FALSE);

						break;
					}
					case HOKUM_MFD_MODE_PERISCOPE:
					{
						draw_3d_periscope_mfd (FALSE);

						break;
					}
				}

				set_active_screen (eo_3d_texture_screen);

				if (lock_screen (eo_3d_texture_screen))
				{
					draw_layout_grid ();

					switch (get_mfd_mode_for_eo_sensor ())
					{
						case HOKUM_MFD_MODE_FLIR:
						{
							draw_2d_flir_mfd (TRUE);

							break;
						}
						case HOKUM_MFD_MODE_LLLTV:
						{
							draw_2d_llltv_mfd (TRUE);

							break;
						}
						case HOKUM_MFD_MODE_PERISCOPE:
						{
							draw_2d_periscope_mfd (TRUE);

							break;
						}
					}

					flush_screen_texture_graphics (eo_3d_texture_screen);

					unlock_screen (eo_3d_texture_screen);
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

	if (display_mask & PILOT_LHS_MFD)
	{
		draw_mfd (pilot_lhs_mfd_texture_screen, pilot_lhs_mfd_mode, HOKUM_MFD_LOCATION_PILOT_LHS);
	}

	if (display_mask & PILOT_RHS_MFD)
	{
		draw_mfd (pilot_rhs_mfd_texture_screen, pilot_rhs_mfd_mode, HOKUM_MFD_LOCATION_PILOT_RHS);
	}

	if (display_mask & CO_PILOT_LHS_MFD)
	{
		draw_mfd (co_pilot_lhs_mfd_texture_screen, co_pilot_lhs_mfd_mode, HOKUM_MFD_LOCATION_CO_PILOT_LHS);
	}

	if (display_mask & CO_PILOT_RHS_MFD)
	{
		draw_mfd (co_pilot_rhs_mfd_texture_screen, co_pilot_rhs_mfd_mode, HOKUM_MFD_LOCATION_CO_PILOT_RHS);
	}

	if (display_mask & EKRAN_DISPLAY)
	{
		draw_text_display (ekran_display_texture_screen);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_hokum_text_display_text (char *s1, char *s2, char *s3)
{
	ASSERT (s1);

	ASSERT (s2);

	ASSERT (s3);

	strncpy (text_display_line1, s1, TEXT_DISPLAY_MAX_STRING_LENGTH);

	strncpy (text_display_line2, s2, TEXT_DISPLAY_MAX_STRING_LENGTH);

	strncpy (text_display_line3, s3, TEXT_DISPLAY_MAX_STRING_LENGTH);

	text_display_line1[TEXT_DISPLAY_MAX_STRING_LENGTH] = '\0';

	text_display_line2[TEXT_DISPLAY_MAX_STRING_LENGTH] = '\0';

	text_display_line3[TEXT_DISPLAY_MAX_STRING_LENGTH] = '\0';
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_hokum_full_screen_display (void)
{
	hokum_mfd_modes
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
			mode = pilot_lhs_mfd_mode;

			break;
		}
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY:
		{
			mode = pilot_rhs_mfd_mode;

			break;
		}
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY:
		{
			mode = co_pilot_lhs_mfd_mode;

			break;
		}
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY:
		{
			mode = co_pilot_rhs_mfd_mode;

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

	mfd_screen_x_max -= 0.001;
	mfd_screen_y_max -= 0.001;

	mfd_screen_x_scale = 256.0 / mfd_screen_width;
	mfd_screen_y_scale = 256.0 / mfd_screen_height;

	switch (mode)
	{
		case HOKUM_MFD_MODE_FLIR:
		{
			draw_3d_flir_mfd (TRUE);

			break;
		}
		case HOKUM_MFD_MODE_LLLTV:
		{
			draw_3d_llltv_mfd (TRUE);

			break;
		}
		case HOKUM_MFD_MODE_PERISCOPE:
		{
			draw_3d_periscope_mfd (TRUE);

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

	mfd_viewport_x_max = LARGE_MFD_VIEWPORT_SIZE - 0.001;

	mfd_viewport_y_max = LARGE_MFD_VIEWPORT_SIZE - 0.001;

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

		draw_layout_grid ();

		switch (mode)
		{
			case HOKUM_MFD_MODE_FLIR:
			{
				draw_2d_flir_mfd (TRUE);

				break;
			}
			case HOKUM_MFD_MODE_LLLTV:
			{
				draw_2d_llltv_mfd (TRUE);

				break;
			}
			case HOKUM_MFD_MODE_PERISCOPE:
			{
				draw_2d_periscope_mfd (TRUE);

				break;
			}
		}

		MFD_COLOUR1 = store_mfd_colour;

		flush_screen_texture_graphics (full_mfd_texture_screen);

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_hokum_virtual_cockpit_periscope_view (void)
{
	float
		zoom;

#ifdef OLD_EO
	switch (hokum_periscope.field_of_view)
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
			debug_fatal ("Invalid field of view = %d", hokum_periscope.field_of_view);

			break;
		}
	}
#else
	zoom = convert_linear_view_value (&hokum_periscope);
#endif

	set_main_3d_params
	(
		DISPLAY_3D_TINT_CLEAR,
		DISPLAY_3D_LIGHT_LEVEL_HIGH,
		DISPLAY_3D_NOISE_LEVEL_NONE,
		full_screen_x_min,
		full_screen_y_min,
		full_screen_width,
		full_screen_height,
		full_screen_width_view_angle * zoom,
		full_screen_height_view_angle * zoom
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

		get_hokum_eo_relative_centred_viewpoint (&centered_eo_vp);

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

void draw_hokum_virtual_cockpit_periscope_symbology (void)
{
	vertex
		quad[4];

	real_colour
		colour,
		specular;

	//
	// set active 3D environment now else 2D clipping will be affected
	//

	set_3d_active_environment (main_3d_env);

	//
	// set up MFD 2D environment
	//

	set_2d_active_environment (mfd_env);

	set_2d_window (mfd_env, MFD_WINDOW_X_MIN, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX, MFD_WINDOW_Y_MAX);

	draw_large_mfd = TRUE;

	mfd_viewport_size = LARGE_MFD_VIEWPORT_SIZE;

	int_mfd_viewport_size = LARGE_MFD_VIEWPORT_SIZE;

	mfd_viewport_x_org = LARGE_MFD_VIEWPORT_SIZE * 0.5;

	mfd_viewport_y_org = LARGE_MFD_VIEWPORT_SIZE * 0.5;

	mfd_viewport_x_min = 0.0;

	mfd_viewport_y_min = 0.0;

	mfd_viewport_x_max = LARGE_MFD_VIEWPORT_SIZE - 0.001;

	mfd_viewport_y_max = LARGE_MFD_VIEWPORT_SIZE - 0.001;

	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

	//
	// get screen co-ords (scaled to keep MFD size constant)
	//

	if (get_global_unscaled_displays ())
	{
		mfd_screen_x_min = full_screen_x_mid - 128.0;
		mfd_screen_y_min = full_screen_y_mid - 128.0;

		mfd_screen_x_max = full_screen_x_mid + 127.999;
		mfd_screen_y_max = full_screen_y_mid + 127.999;

		mfd_screen_x_scale = 1.0;
		mfd_screen_y_scale = 1.0;
	}
	else
	{
		mfd_screen_x_min = full_screen_x_mid - ((256.0 / (640.0 * 2.0)) * full_screen_width);
		mfd_screen_y_min = full_screen_y_mid - ((256.0 / (480.0 * 2.0)) * full_screen_height);

		mfd_screen_x_max = full_screen_x_mid + ((256.0 / (640.0 * 2.0)) * full_screen_width) - 0.001;
		mfd_screen_y_max = full_screen_y_mid + ((256.0 / (480.0 * 2.0)) * full_screen_height) - 0.001;

		mfd_screen_x_scale = 640.0 / full_screen_width;
		mfd_screen_y_scale = 480.0 / full_screen_height;
	}

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

		draw_layout_grid ();

		draw_2d_periscope_mfd (TRUE);

		MFD_COLOUR1 = store_mfd_colour;

		flush_screen_texture_graphics (full_mfd_texture_screen);

		unlock_screen (full_mfd_texture_screen);
	}

	set_active_screen (video_screen);

	//
	// render MFD to screen
	//

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

		set_d3d_flat_shaded_textured_renderstate (get_system_texture_ptr (TEXTURE_INDEX_AVCKPT_DISPLAY_RHS_MFD));

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

static void draw_overlaid_mfd (screen *mfd_screen, hokum_mfd_modes mode, hokum_mfd_locations location)
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

	ASSERT (hokum_mfd_mode_valid (mode));

	ASSERT (hokum_mfd_location_valid (location));

	if (mode == HOKUM_MFD_MODE_OFF)
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
		case HOKUM_MFD_LOCATION_PILOT_LHS:
		case HOKUM_MFD_LOCATION_CO_PILOT_LHS:
		////////////////////////////////////////
		{
			mfd_screen_x_min = border_size;
			mfd_screen_y_min = full_screen_height - border_size - mfd_screen_height;

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_LOCATION_PILOT_RHS:
		case HOKUM_MFD_LOCATION_CO_PILOT_RHS:
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
		case HOKUM_MFD_MODE_OFF:
		////////////////////////////////////////
		{
			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_screen);

			if (lock_screen (mfd_screen))
			{
				set_block (0, 0, int_mfd_viewport_size - 1, int_mfd_viewport_size - 1, clear_mfd_colour);

				draw_layout_grid ();

				flush_screen_texture_graphics (mfd_screen);

				unlock_screen (mfd_screen);
			}

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_DAMAGED:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_screen);

			if (lock_screen (mfd_screen))
			{
				set_block (0, 0, int_mfd_viewport_size - 1, int_mfd_viewport_size - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_overlaid_damaged_mfd ();

				flush_screen_texture_graphics (mfd_screen);

				unlock_screen (mfd_screen);
			}

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_GROUND_RADAR:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_screen);

			if (lock_screen (mfd_screen))
			{
				set_block (0, 0, int_mfd_viewport_size - 1, int_mfd_viewport_size - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_ground_radar_mfd ();

				flush_screen_texture_graphics (mfd_screen);

				unlock_screen (mfd_screen);
			}

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_AIR_RADAR:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_screen);

			if (lock_screen (mfd_screen))
			{
				set_block (0, 0, int_mfd_viewport_size - 1, int_mfd_viewport_size - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_air_radar_mfd ();

				flush_screen_texture_graphics (mfd_screen);

				unlock_screen (mfd_screen);
			}

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_FLIR:
		////////////////////////////////////////
		{
			if (!hokum_damage.flir)
			{
				draw_full_screen_3d_eo_display (&hokum_flir, TARGET_ACQUISITION_SYSTEM_FLIR, DISPLAY_3D_TINT_AMBER);
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

				draw_layout_grid ();

				draw_2d_flir_mfd (TRUE);

				flush_screen_texture_graphics (mfd_screen);

				unlock_screen (mfd_screen);
			}

			set_pilots_full_screen_params (FALSE);

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_LLLTV:
		////////////////////////////////////////
		{
			if (!hokum_damage.llltv)
			{
				draw_full_screen_3d_eo_display (&hokum_llltv, TARGET_ACQUISITION_SYSTEM_LLLTV, DISPLAY_3D_TINT_AMBER);
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

				draw_layout_grid ();

				draw_2d_llltv_mfd (TRUE);

				flush_screen_texture_graphics (mfd_screen);

				unlock_screen (mfd_screen);
			}

			set_pilots_full_screen_params (FALSE);

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_PERISCOPE:
		////////////////////////////////////////
		{
			if (!hokum_damage.periscope)
			{
				draw_full_screen_3d_eo_display (&hokum_periscope, TARGET_ACQUISITION_SYSTEM_PERISCOPE, DISPLAY_3D_TINT_AMBER);
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

				draw_layout_grid ();

				draw_2d_periscope_mfd (TRUE);

				flush_screen_texture_graphics (mfd_screen);

				unlock_screen (mfd_screen);
			}

			set_pilots_full_screen_params (FALSE);

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_TSD:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_screen);

			if (lock_screen (mfd_screen))
			{
				set_block (0, 0, int_mfd_viewport_size - 1, int_mfd_viewport_size - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_tactical_situation_display_mfd (location);

				flush_screen_texture_graphics (mfd_screen);

				unlock_screen (mfd_screen);
			}

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_ASE:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_screen);

			if (lock_screen (mfd_screen))
			{
				set_block (0, 0, int_mfd_viewport_size - 1, int_mfd_viewport_size - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_aircraft_survivability_equipment_display_mfd (location);

				flush_screen_texture_graphics (mfd_screen);

				unlock_screen (mfd_screen);
			}

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_WEAPON:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_screen);

			if (lock_screen (mfd_screen))
			{
				set_block (0, 0, int_mfd_viewport_size - 1, int_mfd_viewport_size - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_weapon_display_mfd ();

				flush_screen_texture_graphics (mfd_screen);

				unlock_screen (mfd_screen);
			}

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_SYSTEM:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_screen);

			if (lock_screen (mfd_screen))
			{
				set_block (0, 0, int_mfd_viewport_size - 1, int_mfd_viewport_size - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_system_display_mfd ();

				flush_screen_texture_graphics (mfd_screen);

				unlock_screen (mfd_screen);
			}

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_ENGINE:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_screen);

			if (lock_screen (mfd_screen))
			{
				set_block (0, 0, int_mfd_viewport_size - 1, int_mfd_viewport_size - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_engine_display_mfd ();

				flush_screen_texture_graphics (mfd_screen);

				unlock_screen (mfd_screen);
			}

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_FLIGHT:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_screen);

			if (lock_screen (mfd_screen))
			{
				set_block (0, 0, int_mfd_viewport_size - 1, int_mfd_viewport_size - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_flight_display_mfd ();

				flush_screen_texture_graphics (mfd_screen);

				unlock_screen (mfd_screen);
			}

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_MISSION:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_screen);

			if (lock_screen (mfd_screen))
			{
				set_block (0, 0, int_mfd_viewport_size - 1, int_mfd_viewport_size - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_mission_display_mfd ();

				flush_screen_texture_graphics (mfd_screen);

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

void draw_overlaid_hokum_mfd (void)
{
	////////////////////////////////////////
	//
	// SELECT LARGE OR SMALL MFD TEXTURES
	//
	////////////////////////////////////////

   if (application_video_width >= 1280)
   {
		draw_large_mfd = TRUE;

		pilot_lhs_mfd_texture_screen = large_pilot_lhs_mfd_texture_screen;
		pilot_rhs_mfd_texture_screen = large_pilot_rhs_mfd_texture_screen;
		co_pilot_lhs_mfd_texture_screen = large_co_pilot_lhs_mfd_texture_screen;
		co_pilot_rhs_mfd_texture_screen = large_co_pilot_rhs_mfd_texture_screen;
		ekran_display_texture_screen = large_ekran_display_texture_screen;

		eo_3d_texture_screen = large_eo_3d_texture_screen;
   }
   else
   {
		draw_large_mfd = FALSE;

		pilot_lhs_mfd_texture_screen = small_pilot_lhs_mfd_texture_screen;
		pilot_rhs_mfd_texture_screen = small_pilot_rhs_mfd_texture_screen;
		co_pilot_lhs_mfd_texture_screen = small_co_pilot_lhs_mfd_texture_screen;
		co_pilot_rhs_mfd_texture_screen = small_co_pilot_rhs_mfd_texture_screen;
		ekran_display_texture_screen = small_ekran_display_texture_screen;

		eo_3d_texture_screen = small_eo_3d_texture_screen;
   }

	set_system_texture_screen (pilot_lhs_mfd_texture_screen, TEXTURE_INDEX_HOKUM_COCKPIT_MFD_LHS_2);
	set_system_texture_screen (pilot_rhs_mfd_texture_screen, TEXTURE_INDEX_HOKUM_COCKPIT_MFD_LHS_1);
	set_system_texture_screen (co_pilot_lhs_mfd_texture_screen, TEXTURE_INDEX_HOKUM_COCKPIT_MFD_RHS_1);
	set_system_texture_screen (co_pilot_rhs_mfd_texture_screen, TEXTURE_INDEX_HOKUM_COCKPIT_MFD_RHS_2);
	set_system_texture_screen (ekran_display_texture_screen, TEXTURE_INDEX_HOKUM_COCKPIT_EKRAN);

	////////////////////////////////////////
	//
	// SELECT VISIBLE DISPLAYS
	//
	////////////////////////////////////////

   if (get_crew_role () == CREW_ROLE_PILOT)
   {
      display_mask = PILOT_LHS_MFD | PILOT_RHS_MFD;
   }
   else
   {
      display_mask = CO_PILOT_LHS_MFD | CO_PILOT_RHS_MFD;
   }

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

	mfd_viewport_x_max = mfd_viewport_size - 0.001;

	mfd_viewport_y_max = mfd_viewport_size - 0.001;

	////////////////////////////////////////
	//
	// DRAW DISPLAYS
	//
	////////////////////////////////////////

	if (display_mask & PILOT_LHS_MFD)
	{
		draw_overlaid_mfd (pilot_lhs_mfd_texture_screen, pilot_lhs_mfd_mode, HOKUM_MFD_LOCATION_PILOT_LHS);
	}

	if (display_mask & PILOT_RHS_MFD)
	{
		draw_overlaid_mfd (pilot_rhs_mfd_texture_screen, pilot_rhs_mfd_mode, HOKUM_MFD_LOCATION_PILOT_RHS);
	}

	if (display_mask & CO_PILOT_LHS_MFD)
	{
		draw_overlaid_mfd (co_pilot_lhs_mfd_texture_screen, co_pilot_lhs_mfd_mode, HOKUM_MFD_LOCATION_CO_PILOT_LHS);
	}

	if (display_mask & CO_PILOT_RHS_MFD)
	{
		draw_overlaid_mfd (co_pilot_rhs_mfd_texture_screen, co_pilot_rhs_mfd_mode, HOKUM_MFD_LOCATION_CO_PILOT_RHS);
	}
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

int get_hokum_mfd_has_focus (hokum_mfd_locations mfd_location)
{
	int
		result;

	hokum_mfd_modes
		mfd_mode;

	ASSERT (hokum_mfd_location_valid (mfd_location));

	mfd_mode = *mfd_mode_ptrs[mfd_location];

	switch (target_acquisition_system)
	{
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_GROUND_RADAR:
		////////////////////////////////////////
		{
			result = (mfd_mode == HOKUM_MFD_MODE_GROUND_RADAR);

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_AIR_RADAR:
		////////////////////////////////////////
		{
			result = (mfd_mode == HOKUM_MFD_MODE_AIR_RADAR);

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_FLIR:
		////////////////////////////////////////
		{
			result = (mfd_mode == HOKUM_MFD_MODE_FLIR);

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_LLLTV:
		////////////////////////////////////////
		{
			result = (mfd_mode == HOKUM_MFD_MODE_LLLTV);

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_PERISCOPE:
		////////////////////////////////////////
		{
			result = (mfd_mode == HOKUM_MFD_MODE_PERISCOPE);

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			result = FALSE;

			break;
		}
	}

	return (result);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static hokum_mfd_modes get_mfd_mode_for_eo_sensor (void)
{
	hokum_mfd_modes
		mfd_mode;

	if (eo_sensor == TARGET_ACQUISITION_SYSTEM_FLIR)
	{
		mfd_mode = HOKUM_MFD_MODE_FLIR;
	}
	else if (eo_sensor == TARGET_ACQUISITION_SYSTEM_LLLTV)
	{
		mfd_mode = HOKUM_MFD_MODE_LLLTV;
	}
	else if (eo_sensor == TARGET_ACQUISITION_SYSTEM_PERISCOPE)
	{
		mfd_mode = HOKUM_MFD_MODE_PERISCOPE;
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

static hokum_mfd_modes get_default_mfd_mode (hokum_mfd_locations mfd_location)
{
	hokum_mfd_modes
		mfd_mode;

	ASSERT (hokum_mfd_location_valid (mfd_location));

	switch (mfd_location)
	{
		////////////////////////////////////////
		case HOKUM_MFD_LOCATION_PILOT_LHS:
		////////////////////////////////////////
		{
			mfd_mode = HOKUM_MFD_MODE_ASE;

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_LOCATION_PILOT_RHS:
		////////////////////////////////////////
		{
			mfd_mode = HOKUM_MFD_MODE_TSD;

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_LOCATION_CO_PILOT_LHS:
		////////////////////////////////////////
		{
			mfd_mode = HOKUM_MFD_MODE_ASE;

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_LOCATION_CO_PILOT_RHS:
		////////////////////////////////////////
		{
			mfd_mode = HOKUM_MFD_MODE_TSD;

			break;
		}
	}

	return (mfd_mode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_mfd_damage (hokum_mfd_locations mfd_location)
{
	int
		damage;

	ASSERT (hokum_mfd_location_valid (mfd_location));

	switch (mfd_location)
	{
		////////////////////////////////////////
		case HOKUM_MFD_LOCATION_PILOT_LHS:
		////////////////////////////////////////
		{
			damage = hokum_damage.pilot_lh_mfd;

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_LOCATION_PILOT_RHS:
		////////////////////////////////////////
		{
			damage = hokum_damage.pilot_rh_mfd;

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_LOCATION_CO_PILOT_LHS:
		////////////////////////////////////////
		{
			damage = hokum_damage.co_pilot_lh_mfd;

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_LOCATION_CO_PILOT_RHS:
		////////////////////////////////////////
		{
			damage = hokum_damage.co_pilot_rh_mfd;

			break;
		}
	}

	return (damage);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_hokum_mfd_mode (hokum_mfd_modes mfd_mode, hokum_mfd_locations mfd_location)
{
	hokum_mfd_modes
		*mfd_mode_ptr1,
		*mfd_mode_ptr2,
		default_mfd_mode;

	ASSERT (hokum_mfd_mode_valid (mfd_mode));

	ASSERT (hokum_mfd_location_valid (mfd_location));

	debug_colour_log (DEBUG_COLOUR_AMBER, "%s = %s", hokum_mfd_location_names[mfd_location], hokum_mfd_mode_names[mfd_mode]);

	mfd_mode_ptr1 = mfd_mode_ptrs[mfd_location];

	mfd_mode_ptr2 = opposite_mfd_mode_ptrs[mfd_location];

	if ((mfd_mode == HOKUM_MFD_MODE_DAMAGED) && (*mfd_mode_ptr1 == HOKUM_MFD_MODE_OFF))
	{
		mfd_mode = HOKUM_MFD_MODE_OFF;
	}

	if (get_mfd_damage (mfd_location))
	{
		if (mfd_mode != HOKUM_MFD_MODE_OFF)
		{
			mfd_mode = HOKUM_MFD_MODE_DAMAGED;
		}
	}

	if ((mfd_mode != HOKUM_MFD_MODE_OFF) && (mfd_mode != HOKUM_MFD_MODE_DAMAGED) && (mfd_mode == *mfd_mode_ptr2))
	{
		default_mfd_mode = get_default_mfd_mode (opposite_mfd_locations[mfd_location]);

		if (default_mfd_mode == mfd_mode)
		{
			default_mfd_mode = get_default_mfd_mode (mfd_location);

			ASSERT (default_mfd_mode != mfd_mode);
		}

		*mfd_mode_ptr2 = default_mfd_mode;
	}

	*mfd_mode_ptr1 = mfd_mode;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static hokum_mfd_modes get_next_mfd_mode (hokum_mfd_modes mfd_mode, hokum_mfd_locations mfd_location)
{
	hokum_mfd_modes
		next_mfd_mode;

	ASSERT (hokum_mfd_mode_valid (mfd_mode));

	ASSERT (hokum_mfd_location_valid (mfd_location));

	switch (mfd_mode)
	{
		////////////////////////////////////////
		case HOKUM_MFD_MODE_OFF:
		////////////////////////////////////////
		{
			next_mfd_mode = get_default_mfd_mode (mfd_location);

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_DAMAGED:
		////////////////////////////////////////
		{
			next_mfd_mode = HOKUM_MFD_MODE_DAMAGED;

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_GROUND_RADAR:
		////////////////////////////////////////
		{
			next_mfd_mode = HOKUM_MFD_MODE_AIR_RADAR;

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_AIR_RADAR:
		////////////////////////////////////////
		{
			next_mfd_mode = get_mfd_mode_for_eo_sensor ();

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_FLIR:
		////////////////////////////////////////
		{
			next_mfd_mode = HOKUM_MFD_MODE_TSD;

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_LLLTV:
		////////////////////////////////////////
		{
			next_mfd_mode = HOKUM_MFD_MODE_TSD;

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_PERISCOPE:
		////////////////////////////////////////
		{
			next_mfd_mode = HOKUM_MFD_MODE_TSD;

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_TSD:
		////////////////////////////////////////
		{
			next_mfd_mode = HOKUM_MFD_MODE_ASE;

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_ASE:
		////////////////////////////////////////
		{
			next_mfd_mode = HOKUM_MFD_MODE_WEAPON;

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_WEAPON:
		////////////////////////////////////////
		{
			next_mfd_mode = HOKUM_MFD_MODE_SYSTEM;

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_SYSTEM:
		////////////////////////////////////////
		{
			next_mfd_mode = HOKUM_MFD_MODE_ENGINE;

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_ENGINE:
		////////////////////////////////////////
		{
			next_mfd_mode = HOKUM_MFD_MODE_FLIGHT;

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_FLIGHT:
		////////////////////////////////////////
		{
			next_mfd_mode = HOKUM_MFD_MODE_MISSION;

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_MISSION:
		////////////////////////////////////////
		{
			next_mfd_mode = HOKUM_MFD_MODE_GROUND_RADAR;

			break;
		}
	}

	return (next_mfd_mode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static hokum_mfd_modes get_previous_mfd_mode (hokum_mfd_modes mfd_mode, hokum_mfd_locations mfd_location)
{
	hokum_mfd_modes
		previous_mfd_mode;

	ASSERT (hokum_mfd_mode_valid (mfd_mode));

	ASSERT (hokum_mfd_location_valid (mfd_location));

	switch (mfd_mode)
	{
		////////////////////////////////////////
		case HOKUM_MFD_MODE_OFF:
		////////////////////////////////////////
		{
			previous_mfd_mode = get_default_mfd_mode (mfd_location);

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_DAMAGED:
		////////////////////////////////////////
		{
			previous_mfd_mode = HOKUM_MFD_MODE_DAMAGED;

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_GROUND_RADAR:
		////////////////////////////////////////
		{
			previous_mfd_mode = HOKUM_MFD_MODE_MISSION;

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_AIR_RADAR:
		////////////////////////////////////////
		{
			previous_mfd_mode = HOKUM_MFD_MODE_GROUND_RADAR;

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_FLIR:
		////////////////////////////////////////
		{
			previous_mfd_mode = HOKUM_MFD_MODE_AIR_RADAR;

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_LLLTV:
		////////////////////////////////////////
		{
			previous_mfd_mode = HOKUM_MFD_MODE_AIR_RADAR;

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_PERISCOPE:
		////////////////////////////////////////
		{
			previous_mfd_mode = HOKUM_MFD_MODE_AIR_RADAR;

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_TSD:
		////////////////////////////////////////
		{
			previous_mfd_mode = get_mfd_mode_for_eo_sensor ();

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_ASE:
		////////////////////////////////////////
		{
			previous_mfd_mode = HOKUM_MFD_MODE_TSD;

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_WEAPON:
		////////////////////////////////////////
		{
			previous_mfd_mode = HOKUM_MFD_MODE_ASE;

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_SYSTEM:
		////////////////////////////////////////
		{
			previous_mfd_mode = HOKUM_MFD_MODE_WEAPON;

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_ENGINE:
		////////////////////////////////////////
		{
			previous_mfd_mode = HOKUM_MFD_MODE_SYSTEM;

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_FLIGHT:
		////////////////////////////////////////
		{
			previous_mfd_mode = HOKUM_MFD_MODE_ENGINE;

			break;
		}
		////////////////////////////////////////
		case HOKUM_MFD_MODE_MISSION:
		////////////////////////////////////////
		{
			previous_mfd_mode = HOKUM_MFD_MODE_FLIGHT;

			break;
		}
	}

	return (previous_mfd_mode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_next_hokum_mfd (hokum_mfd_locations mfd_location)
{
	hokum_mfd_modes
		*mfd_mode_ptr1,
		*mfd_mode_ptr2,
		next_mfd_mode;

	ASSERT (hokum_mfd_location_valid (mfd_location));

	mfd_mode_ptr1 = mfd_mode_ptrs[mfd_location];

	mfd_mode_ptr2 = opposite_mfd_mode_ptrs[mfd_location];

	next_mfd_mode = get_next_mfd_mode (*mfd_mode_ptr1, mfd_location);

	if (next_mfd_mode != HOKUM_MFD_MODE_DAMAGED)
	{
		if (next_mfd_mode == *mfd_mode_ptr2)
		{
			next_mfd_mode = get_next_mfd_mode (next_mfd_mode, mfd_location);
		}

		ASSERT (next_mfd_mode != *mfd_mode_ptr2);
	}

	select_hokum_mfd_mode (next_mfd_mode, mfd_location);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_previous_hokum_mfd (hokum_mfd_locations mfd_location)
{
	hokum_mfd_modes
		*mfd_mode_ptr1,
		*mfd_mode_ptr2,
		previous_mfd_mode;

	ASSERT (hokum_mfd_location_valid (mfd_location));

	mfd_mode_ptr1 = mfd_mode_ptrs[mfd_location];

	mfd_mode_ptr2 = opposite_mfd_mode_ptrs[mfd_location];

	previous_mfd_mode = get_previous_mfd_mode (*mfd_mode_ptr1, mfd_location);

	if (previous_mfd_mode != HOKUM_MFD_MODE_DAMAGED)
	{
		if (previous_mfd_mode == *mfd_mode_ptr2)
		{
			previous_mfd_mode = get_previous_mfd_mode (previous_mfd_mode, mfd_location);
		}

		ASSERT (previous_mfd_mode != *mfd_mode_ptr2);
	}

	select_hokum_mfd_mode (previous_mfd_mode, mfd_location);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void toggle_hokum_mfd_on_off (hokum_mfd_locations mfd_location)
{
	ASSERT (hokum_mfd_location_valid (mfd_location));

	if (*mfd_mode_ptrs[mfd_location] != HOKUM_MFD_MODE_OFF)
	{
		select_hokum_mfd_mode (HOKUM_MFD_MODE_OFF, mfd_location);
	}
	else
	{
		select_next_hokum_mfd (mfd_location);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_next_hokum_pilot_tsd_ase_range (void)
{
	if (pilot_tsd_ase_range == TSD_ASE_RANGE_2000)
	{
		pilot_tsd_ase_range = TSD_ASE_RANGE_5000;
	}
	else if (pilot_tsd_ase_range == TSD_ASE_RANGE_5000)
	{
		pilot_tsd_ase_range = TSD_ASE_RANGE_10000;
	}
	else if (pilot_tsd_ase_range == TSD_ASE_RANGE_10000)
	{
		pilot_tsd_ase_range = TSD_ASE_RANGE_25000;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_next_hokum_co_pilot_tsd_ase_range (void)
{
	if (co_pilot_tsd_ase_range == TSD_ASE_RANGE_2000)
	{
		co_pilot_tsd_ase_range = TSD_ASE_RANGE_5000;
	}
	else if (co_pilot_tsd_ase_range == TSD_ASE_RANGE_5000)
	{
		co_pilot_tsd_ase_range = TSD_ASE_RANGE_10000;
	}
	else if (co_pilot_tsd_ase_range == TSD_ASE_RANGE_10000)
	{
		co_pilot_tsd_ase_range = TSD_ASE_RANGE_25000;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_previous_hokum_pilot_tsd_ase_range (void)
{
	if (pilot_tsd_ase_range == TSD_ASE_RANGE_25000)
	{
		pilot_tsd_ase_range = TSD_ASE_RANGE_10000;
	}
	else if (pilot_tsd_ase_range == TSD_ASE_RANGE_10000)
	{
		pilot_tsd_ase_range = TSD_ASE_RANGE_5000;
	}
	else if (pilot_tsd_ase_range == TSD_ASE_RANGE_5000)
	{
		pilot_tsd_ase_range = TSD_ASE_RANGE_2000;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_previous_hokum_co_pilot_tsd_ase_range (void)
{
	if (co_pilot_tsd_ase_range == TSD_ASE_RANGE_25000)
	{
		co_pilot_tsd_ase_range = TSD_ASE_RANGE_10000;
	}
	else if (co_pilot_tsd_ase_range == TSD_ASE_RANGE_10000)
	{
		co_pilot_tsd_ase_range = TSD_ASE_RANGE_5000;
	}
	else if (co_pilot_tsd_ase_range == TSD_ASE_RANGE_5000)
	{
		co_pilot_tsd_ase_range = TSD_ASE_RANGE_2000;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_next_hokum_pilot_tsd_declutter_level (void)
{
	if (pilot_tsd_declutter_level == TSD_DECLUTTER_LEVEL_ALL)
	{
		pilot_tsd_declutter_level = TSD_DECLUTTER_LEVEL_TARGET;
	}
	else if (pilot_tsd_declutter_level == TSD_DECLUTTER_LEVEL_TARGET)
	{
		pilot_tsd_declutter_level = TSD_DECLUTTER_LEVEL_NAVIGATION;
	}
	else
	{
		pilot_tsd_declutter_level = TSD_DECLUTTER_LEVEL_ALL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_next_hokum_co_pilot_tsd_declutter_level (void)
{
	if (co_pilot_tsd_declutter_level == TSD_DECLUTTER_LEVEL_ALL)
	{
		co_pilot_tsd_declutter_level = TSD_DECLUTTER_LEVEL_TARGET;
	}
	else if (co_pilot_tsd_declutter_level == TSD_DECLUTTER_LEVEL_TARGET)
	{
		co_pilot_tsd_declutter_level = TSD_DECLUTTER_LEVEL_NAVIGATION;
	}
	else
	{
		co_pilot_tsd_declutter_level = TSD_DECLUTTER_LEVEL_ALL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_previous_hokum_pilot_tsd_declutter_level (void)
{
	if (pilot_tsd_declutter_level == TSD_DECLUTTER_LEVEL_NAVIGATION)
	{
		pilot_tsd_declutter_level = TSD_DECLUTTER_LEVEL_TARGET;
	}
	else if (pilot_tsd_declutter_level == TSD_DECLUTTER_LEVEL_TARGET)
	{
		pilot_tsd_declutter_level = TSD_DECLUTTER_LEVEL_ALL;
	}
	else
	{
		pilot_tsd_declutter_level = TSD_DECLUTTER_LEVEL_NAVIGATION;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_previous_hokum_co_pilot_tsd_declutter_level (void)
{
	if (co_pilot_tsd_declutter_level == TSD_DECLUTTER_LEVEL_NAVIGATION)
	{
		co_pilot_tsd_declutter_level = TSD_DECLUTTER_LEVEL_TARGET;
	}
	else if (co_pilot_tsd_declutter_level == TSD_DECLUTTER_LEVEL_TARGET)
	{
		co_pilot_tsd_declutter_level = TSD_DECLUTTER_LEVEL_ALL;
	}
	else
	{
		co_pilot_tsd_declutter_level = TSD_DECLUTTER_LEVEL_NAVIGATION;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void toggle_hokum_ase_auto_page (void)
{
	set_global_ase_auto_page (get_global_ase_auto_page () ^ 1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void auto_page_hokum_ase_mfd (void)
{
	if (!get_global_ase_auto_page ())
	{
		return;
	}

	if (get_crew_role () == CREW_ROLE_PILOT)
	{
		////////////////////////////////////////
		//
		// PILOT
		//
		////////////////////////////////////////

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY) && (!hokum_damage.pilot_lh_mfd))
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_ASE, HOKUM_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY) && (!hokum_damage.pilot_rh_mfd))
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_ASE, HOKUM_MFD_LOCATION_PILOT_RHS);

			return;
		}

		if (pilot_lhs_mfd_mode == HOKUM_MFD_MODE_ASE)
		{
			return;
		}

		if (pilot_rhs_mfd_mode == HOKUM_MFD_MODE_ASE)
		{
			return;
		}

		if ((pilot_lhs_mfd_mode == HOKUM_MFD_MODE_OFF) && (!hokum_damage.pilot_lh_mfd))
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_ASE, HOKUM_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if ((pilot_rhs_mfd_mode == HOKUM_MFD_MODE_OFF) && (!hokum_damage.pilot_rh_mfd))
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_ASE, HOKUM_MFD_LOCATION_PILOT_RHS);

			return;
		}

		if ((!get_hokum_mfd_has_focus (HOKUM_MFD_LOCATION_PILOT_LHS)) && (!hokum_damage.pilot_lh_mfd))
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_ASE, HOKUM_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if ((!get_hokum_mfd_has_focus (HOKUM_MFD_LOCATION_PILOT_RHS)) && (!hokum_damage.pilot_rh_mfd))
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_ASE, HOKUM_MFD_LOCATION_PILOT_RHS);

			return;
		}

		if (!hokum_damage.pilot_lh_mfd)
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_ASE, HOKUM_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if (!hokum_damage.pilot_rh_mfd)
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_ASE, HOKUM_MFD_LOCATION_PILOT_RHS);

			return;
		}
	}
	else
	{
		////////////////////////////////////////
		//
		// CO-PILOT
		//
		////////////////////////////////////////

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY) && (!hokum_damage.co_pilot_lh_mfd))
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_ASE, HOKUM_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY) && (!hokum_damage.co_pilot_rh_mfd))
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_ASE, HOKUM_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}

		if (co_pilot_lhs_mfd_mode == HOKUM_MFD_MODE_ASE)
		{
			return;
		}

		if (co_pilot_rhs_mfd_mode == HOKUM_MFD_MODE_ASE)
		{
			return;
		}

		if ((co_pilot_lhs_mfd_mode == HOKUM_MFD_MODE_OFF) && (!hokum_damage.co_pilot_lh_mfd))
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_ASE, HOKUM_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if ((co_pilot_rhs_mfd_mode == HOKUM_MFD_MODE_OFF) && (!hokum_damage.co_pilot_rh_mfd))
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_ASE, HOKUM_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}

		if ((!get_hokum_mfd_has_focus (HOKUM_MFD_LOCATION_CO_PILOT_LHS)) && (!hokum_damage.co_pilot_lh_mfd))
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_ASE, HOKUM_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if ((!get_hokum_mfd_has_focus (HOKUM_MFD_LOCATION_CO_PILOT_RHS)) && (!hokum_damage.co_pilot_rh_mfd))
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_ASE, HOKUM_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}

		if (!hokum_damage.co_pilot_lh_mfd)
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_ASE, HOKUM_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if (!hokum_damage.co_pilot_rh_mfd)
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_ASE, HOKUM_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_hokum_ground_radar_mfd (void)
{
	if (get_crew_role () == CREW_ROLE_PILOT)
	{
		////////////////////////////////////////
		//
		// PILOT
		//
		////////////////////////////////////////

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY) && (!hokum_damage.pilot_lh_mfd))
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_GROUND_RADAR, HOKUM_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY) && (!hokum_damage.pilot_rh_mfd))
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_GROUND_RADAR, HOKUM_MFD_LOCATION_PILOT_RHS);

			return;
		}

		if (pilot_lhs_mfd_mode == HOKUM_MFD_MODE_GROUND_RADAR)
		{
			return;
		}

		if (pilot_rhs_mfd_mode == HOKUM_MFD_MODE_GROUND_RADAR)
		{
			return;
		}

		if (pilot_lhs_mfd_mode == HOKUM_MFD_MODE_AIR_RADAR)
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_GROUND_RADAR, HOKUM_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if (pilot_rhs_mfd_mode == HOKUM_MFD_MODE_AIR_RADAR)
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_GROUND_RADAR, HOKUM_MFD_LOCATION_PILOT_RHS);

			return;
		}

		if ((pilot_lhs_mfd_mode == HOKUM_MFD_MODE_OFF) && (!hokum_damage.pilot_lh_mfd))
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_GROUND_RADAR, HOKUM_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if ((pilot_rhs_mfd_mode == HOKUM_MFD_MODE_OFF) && (!hokum_damage.pilot_rh_mfd))
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_GROUND_RADAR, HOKUM_MFD_LOCATION_PILOT_RHS);

			return;
		}

		if (!hokum_damage.pilot_lh_mfd)
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_GROUND_RADAR, HOKUM_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if (!hokum_damage.pilot_rh_mfd)
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_GROUND_RADAR, HOKUM_MFD_LOCATION_PILOT_RHS);

			return;
		}
	}
	else
	{
		////////////////////////////////////////
		//
		// CO-PILOT
		//
		////////////////////////////////////////

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY) && (!hokum_damage.co_pilot_lh_mfd))
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_GROUND_RADAR, HOKUM_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY) && (!hokum_damage.co_pilot_rh_mfd))
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_GROUND_RADAR, HOKUM_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}

		if (co_pilot_lhs_mfd_mode == HOKUM_MFD_MODE_GROUND_RADAR)
		{
			return;
		}

		if (co_pilot_rhs_mfd_mode == HOKUM_MFD_MODE_GROUND_RADAR)
		{
			return;
		}

		if (co_pilot_lhs_mfd_mode == HOKUM_MFD_MODE_AIR_RADAR)
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_GROUND_RADAR, HOKUM_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if (co_pilot_rhs_mfd_mode == HOKUM_MFD_MODE_AIR_RADAR)
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_GROUND_RADAR, HOKUM_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}

		if ((co_pilot_lhs_mfd_mode == HOKUM_MFD_MODE_OFF) && (!hokum_damage.co_pilot_lh_mfd))
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_GROUND_RADAR, HOKUM_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if ((co_pilot_rhs_mfd_mode == HOKUM_MFD_MODE_OFF) && (!hokum_damage.co_pilot_rh_mfd))
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_GROUND_RADAR, HOKUM_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}

		if (!hokum_damage.co_pilot_lh_mfd)
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_GROUND_RADAR, HOKUM_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if (!hokum_damage.co_pilot_rh_mfd)
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_GROUND_RADAR, HOKUM_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_hokum_air_radar_mfd (void)
{
	if (get_crew_role () == CREW_ROLE_PILOT)
	{
		////////////////////////////////////////
		//
		// PILOT
		//
		////////////////////////////////////////

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY) && (!hokum_damage.pilot_lh_mfd))
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_AIR_RADAR, HOKUM_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY) && (!hokum_damage.pilot_rh_mfd))
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_AIR_RADAR, HOKUM_MFD_LOCATION_PILOT_RHS);

			return;
		}

		if (pilot_lhs_mfd_mode == HOKUM_MFD_MODE_AIR_RADAR)
		{
			return;
		}

		if (pilot_rhs_mfd_mode == HOKUM_MFD_MODE_AIR_RADAR)
		{
			return;
		}

		if (pilot_lhs_mfd_mode == HOKUM_MFD_MODE_GROUND_RADAR)
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_AIR_RADAR, HOKUM_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if (pilot_rhs_mfd_mode == HOKUM_MFD_MODE_GROUND_RADAR)
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_AIR_RADAR, HOKUM_MFD_LOCATION_PILOT_RHS);

			return;
		}

		if ((pilot_lhs_mfd_mode == HOKUM_MFD_MODE_OFF) && (!hokum_damage.pilot_lh_mfd))
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_AIR_RADAR, HOKUM_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if ((pilot_rhs_mfd_mode == HOKUM_MFD_MODE_OFF) && (!hokum_damage.pilot_rh_mfd))
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_AIR_RADAR, HOKUM_MFD_LOCATION_PILOT_RHS);

			return;
		}

		if (!hokum_damage.pilot_lh_mfd)
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_AIR_RADAR, HOKUM_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if (!hokum_damage.pilot_rh_mfd)
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_AIR_RADAR, HOKUM_MFD_LOCATION_PILOT_RHS);

			return;
		}
	}
	else
	{
		////////////////////////////////////////
		//
		// CO-PILOT
		//
		////////////////////////////////////////

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY) && (!hokum_damage.co_pilot_lh_mfd))
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_AIR_RADAR, HOKUM_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY) && (!hokum_damage.co_pilot_rh_mfd))
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_AIR_RADAR, HOKUM_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}

		if (co_pilot_lhs_mfd_mode == HOKUM_MFD_MODE_AIR_RADAR)
		{
			return;
		}

		if (co_pilot_rhs_mfd_mode == HOKUM_MFD_MODE_AIR_RADAR)
		{
			return;
		}

		if (co_pilot_lhs_mfd_mode == HOKUM_MFD_MODE_GROUND_RADAR)
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_AIR_RADAR, HOKUM_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if (co_pilot_rhs_mfd_mode == HOKUM_MFD_MODE_GROUND_RADAR)
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_AIR_RADAR, HOKUM_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}

		if ((co_pilot_lhs_mfd_mode == HOKUM_MFD_MODE_OFF) && (!hokum_damage.co_pilot_lh_mfd))
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_AIR_RADAR, HOKUM_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if ((co_pilot_rhs_mfd_mode == HOKUM_MFD_MODE_OFF) && (!hokum_damage.co_pilot_rh_mfd))
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_AIR_RADAR, HOKUM_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}

		if (!hokum_damage.co_pilot_lh_mfd)
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_AIR_RADAR, HOKUM_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if (!hokum_damage.co_pilot_rh_mfd)
		{
			select_hokum_mfd_mode (HOKUM_MFD_MODE_AIR_RADAR, HOKUM_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_hokum_eo_mfd (void)
{
	if (get_crew_role () == CREW_ROLE_PILOT)
	{
		////////////////////////////////////////
		//
		// PILOT
		//
		////////////////////////////////////////

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY) && (!hokum_damage.pilot_lh_mfd))
		{
			select_hokum_mfd_mode (get_mfd_mode_for_eo_sensor (), HOKUM_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY) && (!hokum_damage.pilot_rh_mfd))
		{
			select_hokum_mfd_mode (get_mfd_mode_for_eo_sensor (), HOKUM_MFD_LOCATION_PILOT_RHS);

			return;
		}

		if
		(
			(pilot_lhs_mfd_mode == HOKUM_MFD_MODE_FLIR) ||
			(pilot_lhs_mfd_mode == HOKUM_MFD_MODE_LLLTV) ||
			(pilot_lhs_mfd_mode == HOKUM_MFD_MODE_PERISCOPE)
		)
		{
			select_hokum_mfd_mode (get_mfd_mode_for_eo_sensor (), HOKUM_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if
		(
			(pilot_rhs_mfd_mode == HOKUM_MFD_MODE_FLIR) ||
			(pilot_rhs_mfd_mode == HOKUM_MFD_MODE_LLLTV) ||
			(pilot_rhs_mfd_mode == HOKUM_MFD_MODE_PERISCOPE)
		)
		{
			select_hokum_mfd_mode (get_mfd_mode_for_eo_sensor (), HOKUM_MFD_LOCATION_PILOT_RHS);

			return;
		}

		if ((pilot_lhs_mfd_mode == HOKUM_MFD_MODE_OFF) && (!hokum_damage.pilot_lh_mfd))
		{
			select_hokum_mfd_mode (get_mfd_mode_for_eo_sensor (), HOKUM_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if ((pilot_rhs_mfd_mode == HOKUM_MFD_MODE_OFF) && (!hokum_damage.pilot_rh_mfd))
		{
			select_hokum_mfd_mode (get_mfd_mode_for_eo_sensor (), HOKUM_MFD_LOCATION_PILOT_RHS);

			return;
		}

		if (!hokum_damage.pilot_lh_mfd)
		{
			select_hokum_mfd_mode (get_mfd_mode_for_eo_sensor (), HOKUM_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if (!hokum_damage.pilot_rh_mfd)
		{
			select_hokum_mfd_mode (get_mfd_mode_for_eo_sensor (), HOKUM_MFD_LOCATION_PILOT_RHS);

			return;
		}
	}
	else
	{
		////////////////////////////////////////
		//
		// CO-PILOT
		//
		////////////////////////////////////////

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY) && (!hokum_damage.co_pilot_lh_mfd))
		{
			select_hokum_mfd_mode (get_mfd_mode_for_eo_sensor (), HOKUM_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY) && (!hokum_damage.co_pilot_rh_mfd))
		{
			select_hokum_mfd_mode (get_mfd_mode_for_eo_sensor (), HOKUM_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}

		if
		(
			(co_pilot_lhs_mfd_mode == HOKUM_MFD_MODE_FLIR) ||
			(co_pilot_lhs_mfd_mode == HOKUM_MFD_MODE_LLLTV) ||
			(co_pilot_lhs_mfd_mode == HOKUM_MFD_MODE_PERISCOPE)
		)
		{
			select_hokum_mfd_mode (get_mfd_mode_for_eo_sensor (), HOKUM_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if
		(
			(co_pilot_rhs_mfd_mode == HOKUM_MFD_MODE_FLIR) ||
			(co_pilot_rhs_mfd_mode == HOKUM_MFD_MODE_LLLTV) ||
			(co_pilot_rhs_mfd_mode == HOKUM_MFD_MODE_PERISCOPE)
		)
		{
			select_hokum_mfd_mode (get_mfd_mode_for_eo_sensor (), HOKUM_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}

		if ((co_pilot_lhs_mfd_mode == HOKUM_MFD_MODE_OFF) && (!hokum_damage.co_pilot_lh_mfd))
		{
			select_hokum_mfd_mode (get_mfd_mode_for_eo_sensor (), HOKUM_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if ((co_pilot_rhs_mfd_mode == HOKUM_MFD_MODE_OFF) && (!hokum_damage.co_pilot_rh_mfd))
		{
			select_hokum_mfd_mode (get_mfd_mode_for_eo_sensor (), HOKUM_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}

		if (!hokum_damage.co_pilot_lh_mfd)
		{
			select_hokum_mfd_mode (get_mfd_mode_for_eo_sensor (), HOKUM_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if (!hokum_damage.co_pilot_rh_mfd)
		{
			select_hokum_mfd_mode (get_mfd_mode_for_eo_sensor (), HOKUM_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
