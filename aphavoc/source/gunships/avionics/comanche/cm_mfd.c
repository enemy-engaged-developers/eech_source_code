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



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef DEBUG

static char
	*comanche_main_mfd_mode_names[NUM_COMANCHE_MAIN_MFD_MODES] =
	{
		"COMANCHE_MAIN_MFD_MODE_OFF",
		"COMANCHE_MAIN_MFD_MODE_DAMAGED",
		"COMANCHE_MAIN_MFD_MODE_GROUND_RADAR",
		"COMANCHE_MAIN_MFD_MODE_AIR_RADAR",
		"COMANCHE_MAIN_MFD_MODE_FLIR",
		"COMANCHE_MAIN_MFD_MODE_DTV",
		"COMANCHE_MAIN_MFD_MODE_DVO",
		"COMANCHE_MAIN_MFD_MODE_TSD",
		"COMANCHE_MAIN_MFD_MODE_ASE",
		"COMANCHE_MAIN_MFD_MODE_WEAPON",
		"COMANCHE_MAIN_MFD_MODE_SYSTEM",
		"COMANCHE_MAIN_MFD_MODE_ENGINE",
		"COMANCHE_MAIN_MFD_MODE_FLIGHT",
		"COMANCHE_MAIN_MFD_MODE_MISSION",
	};

static char
	*comanche_main_mfd_location_names[NUM_COMANCHE_MAIN_MFD_LOCATIONS] =
	{
		"COMANCHE_MAIN_MFD_LOCATION_PILOT_LHS",
		"COMANCHE_MAIN_MFD_LOCATION_PILOT_RHS",
		"COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_LHS",
		"COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_RHS",
	};

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef DEBUG

static char
	*comanche_side_mfd_mode_names[NUM_COMANCHE_SIDE_MFD_MODES] =
	{
		"COMANCHE_SIDE_MFD_MODE_OFF",
		"COMANCHE_SIDE_MFD_MODE_DAMAGED",
		"COMANCHE_SIDE_MFD_MODE_WEAPON",
		"COMANCHE_SIDE_MFD_MODE_SYSTEM",
		"COMANCHE_SIDE_MFD_MODE_ENGINE",
		"COMANCHE_SIDE_MFD_MODE_FLIGHT",
	};

static char
	*comanche_side_mfd_location_names[NUM_COMANCHE_SIDE_MFD_LOCATIONS] =
	{
		"COMANCHE_SIDE_MFD_LOCATION_PILOT_LHS",
		"COMANCHE_SIDE_MFD_LOCATION_PILOT_RHS",
		"COMANCHE_SIDE_MFD_LOCATION_CO_PILOT_LHS",
		"COMANCHE_SIDE_MFD_LOCATION_CO_PILOT_RHS",
	};

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static comanche_main_mfd_modes
	pilot_lhs_main_mfd_mode			= COMANCHE_MAIN_MFD_MODE_OFF,
	pilot_rhs_main_mfd_mode			= COMANCHE_MAIN_MFD_MODE_OFF,
	co_pilot_lhs_main_mfd_mode		= COMANCHE_MAIN_MFD_MODE_OFF,
	co_pilot_rhs_main_mfd_mode		= COMANCHE_MAIN_MFD_MODE_OFF;

static comanche_main_mfd_modes
	*main_mfd_mode_ptrs[NUM_COMANCHE_MAIN_MFD_LOCATIONS] =
	{
		&pilot_lhs_main_mfd_mode,						// COMANCHE_MAIN_MFD_LOCATION_PILOT_LHS
		&pilot_rhs_main_mfd_mode,     				// COMANCHE_MAIN_MFD_LOCATION_PILOT_RHS
		&co_pilot_lhs_main_mfd_mode,  				// COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_LHS
		&co_pilot_rhs_main_mfd_mode,  				// COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_RHS
	};

static comanche_main_mfd_modes
	*opposite_main_mfd_mode_ptrs[NUM_COMANCHE_MAIN_MFD_LOCATIONS] =
	{
		&pilot_rhs_main_mfd_mode,						// COMANCHE_MAIN_MFD_LOCATION_PILOT_LHS
		&pilot_lhs_main_mfd_mode,     				// COMANCHE_MAIN_MFD_LOCATION_PILOT_RHS
		&co_pilot_rhs_main_mfd_mode,  				// COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_LHS
		&co_pilot_lhs_main_mfd_mode,  				// COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_RHS
	};

static comanche_main_mfd_locations
	opposite_main_mfd_locations[NUM_COMANCHE_MAIN_MFD_LOCATIONS] =
	{
		COMANCHE_MAIN_MFD_LOCATION_PILOT_RHS,		// COMANCHE_MAIN_MFD_LOCATION_PILOT_LHS
		COMANCHE_MAIN_MFD_LOCATION_PILOT_LHS,		// COMANCHE_MAIN_MFD_LOCATION_PILOT_RHS
		COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_RHS,	// COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_LHS
		COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_LHS,	// COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_RHS
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static comanche_side_mfd_modes
	pilot_lhs_side_mfd_mode			= COMANCHE_SIDE_MFD_MODE_OFF,
	pilot_rhs_side_mfd_mode			= COMANCHE_SIDE_MFD_MODE_OFF,
	co_pilot_lhs_side_mfd_mode		= COMANCHE_SIDE_MFD_MODE_OFF,
	co_pilot_rhs_side_mfd_mode		= COMANCHE_SIDE_MFD_MODE_OFF;

static comanche_side_mfd_modes
	*side_mfd_mode_ptrs[NUM_COMANCHE_SIDE_MFD_LOCATIONS] =
	{
		&pilot_lhs_side_mfd_mode,						// COMANCHE_SIDE_MFD_LOCATION_PILOT_LHS
		&pilot_rhs_side_mfd_mode,     				// COMANCHE_SIDE_MFD_LOCATION_PILOT_RHS
		&co_pilot_lhs_side_mfd_mode,  				// COMANCHE_SIDE_MFD_LOCATION_CO_PILOT_LHS
		&co_pilot_rhs_side_mfd_mode,  				// COMANCHE_SIDE_MFD_LOCATION_CO_PILOT_RHS
	};

static comanche_side_mfd_modes
	*opposite_side_mfd_mode_ptrs[NUM_COMANCHE_SIDE_MFD_LOCATIONS] =
	{
		&pilot_rhs_side_mfd_mode,						// COMANCHE_SIDE_MFD_LOCATION_PILOT_LHS
		&pilot_lhs_side_mfd_mode,     				// COMANCHE_SIDE_MFD_LOCATION_PILOT_RHS
		&co_pilot_rhs_side_mfd_mode,  				// COMANCHE_SIDE_MFD_LOCATION_CO_PILOT_LHS
		&co_pilot_lhs_side_mfd_mode,  				// COMANCHE_SIDE_MFD_LOCATION_CO_PILOT_RHS
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static rgb_colour
	mfd_colours[11];

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

#define PILOT_LHS_MAIN_MFD		(1 << 0)
#define PILOT_RHS_MAIN_MFD		(1 << 1)
#define PILOT_LHS_SIDE_MFD		(1 << 2)
#define PILOT_RHS_SIDE_MFD		(1 << 3)
#define PILOT_TEXT_DISPLAY		(1 << 4)
#define CO_PILOT_LHS_MAIN_MFD	(1 << 5)
#define CO_PILOT_RHS_MAIN_MFD	(1 << 6)
#define CO_PILOT_LHS_SIDE_MFD	(1 << 7)
#define CO_PILOT_RHS_SIDE_MFD	(1 << 8)
#define CO_PILOT_TEXT_DISPLAY	(1 << 9)

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
	draw_large_mfd,
	draw_main_display;

static screen
	*pilot_lhs_main_mfd_texture_screen,
	*pilot_rhs_main_mfd_texture_screen,
	*pilot_lhs_side_mfd_texture_screen,
	*pilot_rhs_side_mfd_texture_screen,
	*pilot_text_display_texture_screen,
	*co_pilot_lhs_main_mfd_texture_screen,
	*co_pilot_rhs_main_mfd_texture_screen,
	*co_pilot_lhs_side_mfd_texture_screen,
	*co_pilot_rhs_side_mfd_texture_screen,
	*co_pilot_text_display_texture_screen,
	*large_pilot_lhs_main_mfd_texture_screen,
	*large_pilot_rhs_main_mfd_texture_screen,
	*large_pilot_lhs_side_mfd_texture_screen,
	*large_pilot_rhs_side_mfd_texture_screen,
	*large_pilot_text_display_texture_screen,
	*large_co_pilot_lhs_main_mfd_texture_screen,
	*large_co_pilot_rhs_main_mfd_texture_screen,
	*large_co_pilot_lhs_side_mfd_texture_screen,
	*large_co_pilot_rhs_side_mfd_texture_screen,
	*large_co_pilot_text_display_texture_screen,
	*small_pilot_lhs_main_mfd_texture_screen,
	*small_pilot_rhs_main_mfd_texture_screen,
	*small_pilot_lhs_side_mfd_texture_screen,
	*small_pilot_rhs_side_mfd_texture_screen,
	*small_pilot_text_display_texture_screen,
	*small_co_pilot_lhs_main_mfd_texture_screen,
	*small_co_pilot_rhs_main_mfd_texture_screen,
	*small_co_pilot_lhs_side_mfd_texture_screen,
	*small_co_pilot_rhs_side_mfd_texture_screen,
	*small_co_pilot_text_display_texture_screen,
	*eo_3d_texture_screen,
	*full_mfd_texture_screen;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define TEXT_DISPLAY_MAX_STRING_LENGTH	(17)

static char
	text_display_line1[TEXT_DISPLAY_MAX_STRING_LENGTH + 1],
	text_display_line2[TEXT_DISPLAY_MAX_STRING_LENGTH + 1];

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
		-8,
		0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,
		0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,
		0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,
		0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,
		0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
		0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
		0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
		0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,
		0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,
		0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,
		0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
	};

static char
	large_tsd_ase_aircraft_datum_mask[] =
	{
		19,
		39,
		-9,
		-9,
		0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,
		0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,
		0,0,0,0,1,0,0,1,1,1,1,1,0,0,1,0,0,0,0,
		0,0,0,1,0,1,1,0,0,0,0,0,1,1,0,1,0,0,0,
		0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,0,
		0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,
		0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,
		1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
		1,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1,
		1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,
		1,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1,
		1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
		0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,
		0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,
		0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,0,
		0,0,0,1,0,1,1,0,0,0,0,0,1,1,0,1,0,0,0,
		0,0,0,0,1,0,0,1,1,1,1,1,0,0,1,0,0,0,0,
		0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,
		0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,1,1,1,0,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,
	};

static char
	small_tsd_ase_aircraft_datum[] =
	{
		7,
		15,
		-3,
		-3,
		0,0,1,1,1,0,0,
		0,1,0,0,0,1,0,
		1,0,0,0,0,0,1,
		1,0,0,1,0,0,1,
		1,0,0,0,0,0,1,
		0,1,0,0,0,1,0,
		0,0,1,1,1,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,1,1,0,0,0,
		0,0,1,1,0,0,0,
		0,0,1,0,0,0,0,
	};

static char
	small_tsd_ase_aircraft_datum_mask[] =
	{
		9,
		17,
		-4,
		-4,
		0,0,0,1,1,1,0,0,0,
		0,0,1,0,0,0,1,0,0,
		0,1,0,1,1,1,0,1,0,
		1,0,1,0,1,0,1,0,1,
		1,0,1,1,0,1,1,0,1,
		1,0,1,0,1,0,1,0,1,
		0,1,0,1,1,1,0,1,0,
		0,0,1,0,0,0,1,0,0,
		0,0,0,1,0,1,0,0,0,
		0,0,0,1,0,1,0,0,0,
		0,0,0,1,0,1,0,0,0,
		0,0,0,1,0,1,0,0,0,
		0,0,1,1,0,1,0,0,0,
		0,0,1,0,0,1,0,0,0,
		0,0,1,0,0,1,0,0,0,
		0,0,1,0,1,1,0,0,0,
		0,0,1,1,1,0,0,0,0,
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

static void draw_damaged_side_mfd (void)
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

static void draw_heading_scale (float heading, int draw_command_heading)
{
	float
		heading_width_ratio,
		heading_tick_x_spacing,
		x_adjust_single,
		x_adjust_double,
		y_adjust,
		tick_10_deg_top,
		tick_10_deg_bottom,
		tick_30_deg_top,
		tick_30_deg_bottom,
		tick_datum_top,
		tick_datum_bottom,
		mfd_vp_x_min,
		mfd_vp_x_max,
		x,
		u,
		heading_step_10,
		mod_heading_step_10;

	int
		loop,
		int_heading_step_10,
		tick_type;

	//
	// sort large and small mfd differences
	//

	if (draw_large_mfd)
	{
		set_mono_font_type (MONO_FONT_TYPE_5X9);

		heading_width_ratio		= 0.4;

		heading_tick_x_spacing	= 0.4 / 6.5;

		x_adjust_single  			= -2.0;
		x_adjust_double  			= -5.0;
		y_adjust			  			= -8.0;

		tick_10_deg_top			= 0.925 - 0.015;
		tick_10_deg_bottom  		= 0.925 - 0.015 - 0.045;
		tick_30_deg_top	  		= 0.925;
		tick_30_deg_bottom  		= 0.925 - 0.075;
		tick_datum_top		  		= 0.925 - 0.075 - 0.010;
		tick_datum_bottom	  		= 0.925 - 0.075 - 0.010 - 0.045;
	}
	else
	{
		set_mono_font_type (MONO_FONT_TYPE_3X6);

		heading_width_ratio		= 0.3;

		heading_tick_x_spacing	= 0.4 / 5.0;

		x_adjust_single			= -1.0;
		x_adjust_double  			= -3.0;
		y_adjust			  			= -6.0;

		tick_10_deg_top  			= 0.875 - 0.015;
		tick_10_deg_bottom 		= 0.875 - 0.015 - 0.045;
		tick_30_deg_top	  		= 0.875;
		tick_30_deg_bottom  		= 0.875 - 0.075;
		tick_datum_top		  		= 0.875 - 0.075 - 0.010;
		tick_datum_bottom	  		= 0.875 - 0.075 - 0.010 - 0.045;
	}

	//
	// adjust 2D environment for heading scale clipping
	//

	if (draw_main_display)
	{
		get_2d_float_screen_x_coordinate (0.0, &u);
	}
	else
	{
		get_2d_float_screen_x_coordinate (-0.4, &u);
	}

	set_2d_window (mfd_env, MFD_WINDOW_X_MIN * heading_width_ratio, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX * heading_width_ratio, MFD_WINDOW_Y_MAX);

	mfd_vp_x_min = u - (mfd_viewport_size * (heading_width_ratio * 0.5));

	mfd_vp_x_max = u + (mfd_viewport_size * (heading_width_ratio * 0.5)) - 0.001;

	set_2d_viewport (mfd_env, mfd_vp_x_min, mfd_viewport_y_min, mfd_vp_x_max, mfd_viewport_y_max);

	//
	// draw heading datum tick
	//

	draw_2d_line (0.0, tick_datum_top, 0.0, tick_datum_bottom, MFD_COLOUR1);

	//
	// draw command heading carat
	//

	if (draw_command_heading)
	{
		if (!comanche_damage.navigation_computer)
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
					draw_2d_mono_sprite (large_command_heading_carat, 0.0 + (command_heading * ((heading_width_ratio - 0.035) / rad (90.0))), tick_datum_top, MFD_COLOUR1);
				}
				else
				{
					draw_2d_mono_sprite (small_command_heading_carat, 0.0 + (command_heading * ((heading_width_ratio - 0.050) / rad (90.0))), tick_datum_top, MFD_COLOUR1);
				}
			}
		}
	}

	//
	// draw heading scale
	//

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

	x = - (10.0 + mod_heading_step_10) * heading_tick_x_spacing;

	for (loop = 0; loop <= 20; loop++)
	{
		if (tick_type == 0)
		{
			draw_2d_line (x, tick_30_deg_top, x, tick_30_deg_bottom, MFD_COLOUR1);

			set_2d_mono_font_position (x, tick_30_deg_top);

			switch (int_heading_step_10)
			{
				////////////////////////////////////////
				case 0:
				////////////////////////////////////////
				{
					set_mono_font_rel_position (x_adjust_single, y_adjust);

					print_mono_font_char ('N');

					break;
				}
				////////////////////////////////////////
				case 9:
				////////////////////////////////////////
				{
					set_mono_font_rel_position (x_adjust_single, y_adjust);

					print_mono_font_char ('E');

					break;
				}
				////////////////////////////////////////
				case 18:
				////////////////////////////////////////
				{
					set_mono_font_rel_position (x_adjust_single, y_adjust);

					print_mono_font_char ('S');

					break;
				}
				////////////////////////////////////////
				case 27:
				////////////////////////////////////////
				{
					set_mono_font_rel_position (x_adjust_single, y_adjust);

					print_mono_font_char ('W');

					break;
				}
				////////////////////////////////////////
				default:
				////////////////////////////////////////
				{
					if (int_heading_step_10 < 10)
					{
						set_mono_font_rel_position (x_adjust_single, y_adjust);

						print_mono_font_char ('0' + int_heading_step_10);
					}
					else
					{
						set_mono_font_rel_position (x_adjust_double, y_adjust);

						print_mono_font_char ('0' + int_heading_step_10 / 10);

						print_mono_font_char ('0' + int_heading_step_10 % 10);
					}

					break;
				}
			}
		}
		else
		{
			draw_2d_line (x, tick_10_deg_top, x, tick_10_deg_bottom, MFD_COLOUR1);
		}

		int_heading_step_10 = (++int_heading_step_10 == 36) ? 0 : int_heading_step_10;

		tick_type = (++tick_type == 3) ? 0 : tick_type;

		x += heading_tick_x_spacing;
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
		draw_2d_line (-0.3000, -0.8750,  0.3000, -0.8750, MFD_COLOUR1);
		draw_2d_line (-0.3000, -0.6500, -0.3000, -0.8750, MFD_COLOUR1);
		draw_2d_line ( 0.3000, -0.6500,  0.3000, -0.8750, MFD_COLOUR1);

		draw_2d_line ( 0.0000, -0.6500,  0.0000, -0.6700, MFD_COLOUR1);
		draw_2d_line (-0.2250, -0.6500, -0.2250, -0.6700, MFD_COLOUR1);
		draw_2d_line ( 0.2250, -0.6500,  0.2250, -0.6700, MFD_COLOUR1);

		draw_2d_line ( 0.0000, -0.8550,  0.0000, -0.8750, MFD_COLOUR1);
		draw_2d_line (-0.2250, -0.8550, -0.2250, -0.8750, MFD_COLOUR1);
		draw_2d_line ( 0.2250, -0.8550,  0.2250, -0.8750, MFD_COLOUR1);

		draw_2d_line (-0.3000, -0.7250, -0.2800, -0.7250, MFD_COLOUR1);
		draw_2d_line ( 0.3000, -0.7250,  0.2800, -0.7250, MFD_COLOUR1);

		x = eo_azimuth / eo_max_azimuth * 0.3;
		y = (eo_elevation / eo_min_elevation * -0.15) - 0.725;

		draw_2d_line (x - 0.0400, y - 0.0300, x + 0.0400, y - 0.0300, MFD_COLOUR1);
		draw_2d_line (x - 0.0400, y + 0.0300, x + 0.0400, y + 0.0300, MFD_COLOUR1);
		draw_2d_line (x - 0.0400, y - 0.0300, x - 0.0400, y + 0.0300, MFD_COLOUR1);
		draw_2d_line (x + 0.0400, y - 0.0300, x + 0.0400, y + 0.0300, MFD_COLOUR1);
	}
	else
	{
		draw_2d_line (-0.2000, -0.7250,  0.2000, -0.7250, MFD_COLOUR1);
		draw_2d_line (-0.2000, -0.8750,  0.2000, -0.8750, MFD_COLOUR1);
		draw_2d_line (-0.2000, -0.7250, -0.2000, -0.8750, MFD_COLOUR1);
		draw_2d_line ( 0.2000, -0.7250,  0.2000, -0.8750, MFD_COLOUR1);

		draw_2d_line ( 0.0000, -0.7250,  0.0000, -0.7475, MFD_COLOUR1);
		draw_2d_line (-0.1500, -0.7250, -0.1500, -0.7475, MFD_COLOUR1);
		draw_2d_line ( 0.1500, -0.7250,  0.1500, -0.7475, MFD_COLOUR1);

		draw_2d_line ( 0.0000, -0.8525,  0.0000, -0.8750, MFD_COLOUR1);
		draw_2d_line (-0.1500, -0.8525, -0.1500, -0.8750, MFD_COLOUR1);
		draw_2d_line ( 0.1500, -0.8525,  0.1500, -0.8750, MFD_COLOUR1);

		draw_2d_line (-0.2000, -0.7750, -0.1775, -0.7750, MFD_COLOUR1);
		draw_2d_line ( 0.2000, -0.7750,  0.1775, -0.7750, MFD_COLOUR1);

		x = eo_azimuth / eo_max_azimuth * 0.2;
		y = (eo_elevation / eo_min_elevation * -0.1) - 0.775;

		draw_2d_line (x - 0.0267, y - 0.0200, x + 0.0267, y - 0.0200, MFD_COLOUR1);
		draw_2d_line (x - 0.0267, y + 0.0200, x + 0.0267, y + 0.0200, MFD_COLOUR1);
		draw_2d_line (x - 0.0267, y - 0.0200, x - 0.0267, y + 0.0200, MFD_COLOUR1);
		draw_2d_line (x + 0.0267, y - 0.0200, x + 0.0267, y + 0.0200, MFD_COLOUR1);
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
	char
		*s;

	float
		width,
		y_adjust;

	if (scan_range == COMANCHE_RADAR_SCAN_RANGE_500)
	{
		s = "500m";
	}
	else if (scan_range == COMANCHE_RADAR_SCAN_RANGE_1000)
	{
		s = "1Km";
	}
	else if (scan_range == COMANCHE_RADAR_SCAN_RANGE_2000)
	{
		s = "2Km";
	}
	else if (scan_range == COMANCHE_RADAR_SCAN_RANGE_4000)
	{
		s = "4Km";
	}
	else if (scan_range == COMANCHE_RADAR_SCAN_RANGE_8000)
	{
		s = "8Km";
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
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_radar_target_details (entity *target, float target_range, radar_params *radar)
{
	char
		*s,
		buffer[200];

	float
		y_adjust,
		width;

	ASSERT (radar);

	if (comanche_damage.radar)
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

		if ((target_range < 1000.0) && (!comanche_damage.laser_designator))
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

	num_segments = (int) (arc_size * (1.0 / COMANCHE_RADAR_SCAN_ARC_SEGMENT_SIZE));

	if (num_segments > 0)
	{
		theta = arc_size * 0.5;

		sine_cosine (theta, &sin_theta, &cos_theta);

		x1 = -radius * sin_theta;
		y1 = radius * cos_theta;

		while (num_segments--)
		{
			theta -= COMANCHE_RADAR_SCAN_ARC_SEGMENT_SIZE;

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
			if (source_side == get_local_entity_int_value (target, INT_TYPE_SIDE))
				target_symbol_colour = MFD_COLOUR1;
			else
				target_symbol_colour = MFD_COLOUR3;			
		}		
		else
			target_symbol_colour = MFD_COLOUR2;
	}
	else
	{
//VJ 030423 TSD render mod
		if (display_on_tsd)
		{
			if (source_side == get_local_entity_int_value (target, INT_TYPE_SIDE))
				target_symbol_colour = MFD_COLOUR2;
			else
				target_symbol_colour = MFD_COLOUR4;			
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

	if (!comanche_damage.radar)
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

	draw_radar_arc (COMANCHE_RADAR_SCAN_ARC_SIZE_90, RADIUS, MFD_COLOUR4);

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

	if (!comanche_damage.radar)
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

	if (comanche_damage.radar)
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
#define TICK1	(RADIUS * 0.90)
#define TICK2	(RADIUS * 0.99)

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

	if (air_radar.scan_arc_size == COMANCHE_RADAR_SCAN_ARC_SIZE_360)
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

	if (!comanche_damage.radar)
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

	if (comanche_damage.radar)
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
// DTV
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
// DVO
//
////////////////////////////////////////

static display_3d_light_levels
	dvo_light_levels[WEATHERMODE_LAST][NUM_DAY_SEGMENT_TYPES] =
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
	dvo_noise_levels[WEATHERMODE_LAST][NUM_DAY_SEGMENT_TYPES] =
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

static int get_eo_display_mode (comanche_main_mfd_modes mode)
{
	if
	(
		(mode == COMANCHE_MAIN_MFD_MODE_FLIR) ||
		(mode == COMANCHE_MAIN_MFD_MODE_DTV) ||
		(mode == COMANCHE_MAIN_MFD_MODE_DVO)
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

static int get_undamaged_eo_display_mode (comanche_main_mfd_modes mode)
{
	if ((mode == COMANCHE_MAIN_MFD_MODE_FLIR) && (!comanche_damage.flir))
	{
		return (TRUE);
	}

	if ((mode == COMANCHE_MAIN_MFD_MODE_DTV) && (!comanche_damage.dtv))
	{
		return (TRUE);
	}

	if ((mode == COMANCHE_MAIN_MFD_MODE_DVO) && (!comanche_damage.dvo))
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
		case TARGET_ACQUISITION_SYSTEM_DTV:
		{
			light_level = dtv_light_levels[weather_mode][day_segment_type];

			noise_level = dtv_noise_levels[weather_mode][day_segment_type];

			break;
		}
		case TARGET_ACQUISITION_SYSTEM_DVO:
		{
			light_level = dvo_light_levels[weather_mode][day_segment_type];

			noise_level = dvo_noise_levels[weather_mode][day_segment_type];

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

	set_main_3d_params (DISPLAY_3D_TINT_GREEN, light_level, noise_level, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_size, mfd_viewport_size, rad (59.99) * zoom, rad (59.99) * zoom);

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

		get_comanche_eo_relative_centred_viewpoint (&centered_eo_vp);

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

static void draw_full_screen_3d_eo_display (eo_params_dynamic_move *eo, target_acquisition_systems system)
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
		case TARGET_ACQUISITION_SYSTEM_DTV:
		{
			light_level = dtv_light_levels[weather_mode][day_segment_type];

			noise_level = dtv_noise_levels[weather_mode][day_segment_type];

			break;
		}
		case TARGET_ACQUISITION_SYSTEM_DVO:
		{
			light_level = dvo_light_levels[weather_mode][day_segment_type];

			noise_level = dvo_noise_levels[weather_mode][day_segment_type];

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
		DISPLAY_3D_TINT_GREEN,
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

		get_comanche_eo_relative_centred_viewpoint (&centered_eo_vp);

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
	char
		*s,
		buffer[200];

	float
		width,
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
		case TARGET_ACQUISITION_SYSTEM_DTV:
		{
			print_mono_font_string ("DTV");

			break;
		}
		case TARGET_ACQUISITION_SYSTEM_DVO:
		{
			print_mono_font_string ("DVO");

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
		if ((target_range < 1000.0) && (!comanche_damage.laser_designator))
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

	//
	// 030418 loke
	// draw an indication if ground stablisation is enabled
	//

	if (eo_ground_stabilised)
	{
		if (draw_large_mfd)
		{
			y_adjust = -25.0;
		}
		else
		{
			y_adjust = -12.0;
		}

		width = get_mono_font_string_width ("S");

		set_2d_mono_font_position (1.0, -1.0);

		set_mono_font_rel_position (-width, y_adjust);

		print_mono_font_string ("S");
	}

	////////////////////////////////////////
	//
	// draw heading scale
	//
	////////////////////////////////////////

	draw_heading_scale (get_heading_from_attitude_matrix (eo_vp.attitude), FALSE);

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
	if (!comanche_damage.flir)
	{
		if (full_screen)
		{
			draw_full_screen_3d_eo_display (&comanche_flir, TARGET_ACQUISITION_SYSTEM_FLIR);
		}
		else
		{
			draw_3d_eo_display (&comanche_flir, TARGET_ACQUISITION_SYSTEM_FLIR);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_2d_flir_mfd (int valid_3d)
{
	draw_2d_eo_display (&comanche_flir, TARGET_ACQUISITION_SYSTEM_FLIR, comanche_damage.flir, valid_3d);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DTV
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_3d_dtv_mfd (int full_screen)
{
	if (!comanche_damage.dtv)
	{
		if (full_screen)
		{
			draw_full_screen_3d_eo_display (&comanche_dtv, TARGET_ACQUISITION_SYSTEM_DTV);
		}
		else
		{
			draw_3d_eo_display (&comanche_dtv, TARGET_ACQUISITION_SYSTEM_DTV);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_2d_dtv_mfd (int valid_3d)
{
	draw_2d_eo_display (&comanche_dtv, TARGET_ACQUISITION_SYSTEM_DTV, comanche_damage.dtv, valid_3d);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DVO
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_3d_dvo_mfd (int full_screen)
{
	if (!comanche_damage.dvo)
	{
		if (full_screen)
		{
			draw_full_screen_3d_eo_display (&comanche_dvo, TARGET_ACQUISITION_SYSTEM_DVO);
		}
		else
		{
			draw_3d_eo_display (&comanche_dvo, TARGET_ACQUISITION_SYSTEM_DVO);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_2d_dvo_mfd (int valid_3d)
{
	draw_2d_eo_display (&comanche_dvo, TARGET_ACQUISITION_SYSTEM_DVO, comanche_damage.dvo, valid_3d);
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
*/

/*
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
*/


/*
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
*/

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

static void draw_tactical_situation_display_mfd (comanche_main_mfd_locations mfd_location)
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

	ASSERT (comanche_main_mfd_location_valid (mfd_location));

	switch (mfd_location)
	{
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_LOCATION_PILOT_LHS:
		case COMANCHE_MAIN_MFD_LOCATION_PILOT_RHS:
		////////////////////////////////////////
		{
			tsd_ase_range						= pilot_tsd_ase_range;
			tsd_declutter_level				= pilot_tsd_declutter_level;
			tsd_threat_line_flash_timer	= &pilot_tsd_threat_line_flash_timer;
			tsd_draw_threat_line_status	= &pilot_tsd_draw_threat_line_status;

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_LHS:
		case COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_RHS:
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

			if (air_radar.scan_arc_size == COMANCHE_RADAR_SCAN_ARC_SIZE_360)
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
//VJ 030423 TSD render mod
				if (draw_large_mfd)
				{
					if (tsd_render_mode == TSD_RENDER_CONTOUR_MODE)
						draw_2d_half_thick_line (wp1_rel_position.x, wp1_rel_position.z, wp2_rel_position.x, wp2_rel_position.z, MFD_COLOUR2);
					else
						draw_2d_half_thick_line (wp1_rel_position.x, wp1_rel_position.z, wp2_rel_position.x, wp2_rel_position.z, MFD_COLOUR5);
				}
				else
				{
					if (tsd_render_mode == TSD_RENDER_CONTOUR_MODE)
						draw_2d_line (wp1_rel_position.x, wp1_rel_position.z, wp2_rel_position.x, wp2_rel_position.z, MFD_COLOUR2);
					else
						draw_2d_line (wp1_rel_position.x, wp1_rel_position.z, wp2_rel_position.x, wp2_rel_position.z, MFD_COLOUR5);
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
//VJ 030423 TSD render mod
					if (tsd_render_mode == TSD_RENDER_CONTOUR_MODE)
						draw_2d_mono_sprite (large_tsd_waypoint_marker, wp1_rel_position.x, wp1_rel_position.z, MFD_COLOUR2);
					else
						draw_2d_mono_sprite (large_tsd_waypoint_marker, wp1_rel_position.x, wp1_rel_position.z, MFD_COLOUR5);

					set_2d_mono_font_position (wp1_rel_position.x, wp1_rel_position.z);

					set_mono_font_rel_position (-2.0, -4.0);
				}
				else
				{
//VJ 030423 TSD render mod
					if (tsd_render_mode == TSD_RENDER_CONTOUR_MODE)
						draw_2d_mono_sprite (small_tsd_waypoint_marker, wp1_rel_position.x, wp1_rel_position.z, MFD_COLOUR2);
					else
						draw_2d_mono_sprite (small_tsd_waypoint_marker, wp1_rel_position.x, wp1_rel_position.z, MFD_COLOUR5);

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

//VJ 030423 TSD render mod, enemy of comanche so red
							draw_2d_circle (dx, dy, air_scan_range, MFD_COLOUR4);
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
			case TARGET_ACQUISITION_SYSTEM_DTV:
			case TARGET_ACQUISITION_SYSTEM_DVO:
			{
				s = "TADS";

				break;
			}
			case TARGET_ACQUISITION_SYSTEM_HIDSS:
			{
				s = "HIDSS";

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
			case TARGET_ACQUISITION_SYSTEM_DTV:
			{
				s = "DTV";

				break;
			}
			case TARGET_ACQUISITION_SYSTEM_DVO:
			{
				s = "DVO";

				break;
			}
			case TARGET_ACQUISITION_SYSTEM_HIDSS:
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

			if ((target_range < 1000.0) && (!comanche_damage.laser_designator))
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

			if (!comanche_damage.navigation_computer)
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

			if ((current_flight_dynamics->velocity_z.value > 0.1) && (!comanche_damage.navigation_computer))
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
	set_rgb_colour (MFD_COLOUR1,              0, 255,   0, 255);
	set_rgb_colour (MFD_COLOUR2,              0, 200,   0, 255);
	set_rgb_colour (MFD_COLOUR3,              0, 176,   0, 255);
	set_rgb_colour (MFD_COLOUR4,              0, 151,   0, 255);
	set_rgb_colour (MFD_COLOUR5,              0, 128,   0, 255);
	set_rgb_colour (MFD_COLOUR6,             40,  68,  56, 255);
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

static void draw_aircraft_survivability_equipment_display_mfd (comanche_main_mfd_locations mfd_location)
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

	ASSERT (comanche_main_mfd_location_valid (mfd_location));

	switch (mfd_location)
	{
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_LOCATION_PILOT_LHS:
		case COMANCHE_MAIN_MFD_LOCATION_PILOT_RHS:
		////////////////////////////////////////
		{
			tsd_ase_range						= pilot_tsd_ase_range;
			ase_threat_line_flash_timer	= &pilot_ase_threat_line_flash_timer;
			ase_draw_threat_line_status	= &pilot_ase_draw_threat_line_status;

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_LHS:
		case COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_RHS:
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
		if (comanche_damage.infra_red_jammer)
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
		if (comanche_damage.infra_red_jammer)
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
		if (comanche_damage.radar_jammer)
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
		if (comanche_damage.radar_jammer)
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
		if (comanche_damage.chaff_dispensers)
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
		if (comanche_damage.chaff_dispensers)
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
		if (comanche_damage.flare_dispensers)
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
		if (comanche_damage.flare_dispensers)
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

#define MAIN_WEAPON_LINE_POINT_SCALE			((float) (0.25))

#define MAIN_WEAPON_LINE_POINT_X_TRANSLATE	((float) (0.0))
#define MAIN_WEAPON_LINE_POINT_Y_TRANSLATE	((float) (0.8))

#define SIDE_WEAPON_LINE_POINT_SCALE			((float) (0.25))

#define SIDE_WEAPON_LINE_POINT_X_TRANSLATE	((float) (-0.4))
#define SIDE_WEAPON_LINE_POINT_Y_TRANSLATE	((float) (0.8))

static int
	num_main_weapon_line_points_with_stub_wings,
	num_side_weapon_line_points_with_stub_wings,
	num_main_weapon_line_points_without_stub_wings,
	num_side_weapon_line_points_without_stub_wings;

static vec3d
	*main_weapon_line_points_with_stub_wings,
	*side_weapon_line_points_with_stub_wings,
	*main_weapon_line_points_without_stub_wings,
	*side_weapon_line_points_without_stub_wings;

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
		damaged,
		stub_wings_attached;

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

	stub_wings_attached = get_comanche_stub_wings_attached (get_gunship_entity ());

	if (stub_wings_attached)
	{
		if (draw_large_mfd)
		{
			i = 0;

			while (i < num_main_weapon_line_points_with_stub_wings)
			{
				draw_2d_half_thick_line
				(
					main_weapon_line_points_with_stub_wings[i].x,
					main_weapon_line_points_with_stub_wings[i].y,
					main_weapon_line_points_with_stub_wings[i + 1].x,
					main_weapon_line_points_with_stub_wings[i + 1].y,
					MFD_COLOUR5
				);

				i += 2;
			}
		}
		else
		{
			i = 0;

			while (i < num_main_weapon_line_points_with_stub_wings)
			{
				draw_2d_line
				(
					main_weapon_line_points_with_stub_wings[i].x,
					main_weapon_line_points_with_stub_wings[i].y,
					main_weapon_line_points_with_stub_wings[i + 1].x,
					main_weapon_line_points_with_stub_wings[i + 1].y,
					MFD_COLOUR5
				);

				i += 2;
			}
		}
	}
	else
	{
		if (draw_large_mfd)
		{
			i = 0;

			while (i < num_main_weapon_line_points_without_stub_wings)
			{
				draw_2d_half_thick_line
				(
					main_weapon_line_points_without_stub_wings[i].x,
					main_weapon_line_points_without_stub_wings[i].y,
					main_weapon_line_points_without_stub_wings[i + 1].x,
					main_weapon_line_points_without_stub_wings[i + 1].y,
					MFD_COLOUR5
				);

				i += 2;
			}
		}
		else
		{
			i = 0;

			while (i < num_main_weapon_line_points_without_stub_wings)
			{
				draw_2d_line
				(
					main_weapon_line_points_without_stub_wings[i].x,
					main_weapon_line_points_without_stub_wings[i].y,
					main_weapon_line_points_without_stub_wings[i + 1].x,
					main_weapon_line_points_without_stub_wings[i + 1].y,
					MFD_COLOUR5
				);

				i += 2;
			}
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
		set_mono_font_colour (MFD_COLOUR5);
	}

	if (draw_large_mfd)
	{
		set_mono_font_type (MONO_FONT_TYPE_7X12);

		set_2d_mono_font_position (0.0, 0.5);

		x_adjust = get_mono_font_string_width ("ARM") * -0.5;

		set_mono_font_rel_position (x_adjust, 0.0);

		print_mono_font_string ("ARM");
	}
	else
	{
		set_mono_font_type (MONO_FONT_TYPE_5X7);

		set_2d_mono_font_position (0.0, 0.5);

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
		set_mono_font_colour (MFD_COLOUR5);
	}

	if (draw_large_mfd)
	{
		set_mono_font_type (MONO_FONT_TYPE_6X10);

		set_2d_mono_font_position (0.0, 0.3);

		x_adjust = get_mono_font_string_width ("AUTO") * -0.5;

		set_mono_font_rel_position (x_adjust, 0.0);

		print_mono_font_string ("AUTO");

		set_2d_mono_font_position (0.0, 0.3);

		x_adjust = get_mono_font_string_width ("C/M") * -0.5;

		set_mono_font_rel_position (x_adjust, get_mono_font_char_height ('X'));

		print_mono_font_string ("C/M");
	}
	else
	{
		set_mono_font_type (MONO_FONT_TYPE_5X7);

		set_2d_mono_font_position (0.0, 0.3);

		x_adjust = get_mono_font_string_width ("AUTO") * -0.5;

		set_mono_font_rel_position (x_adjust, 0.0);

		print_mono_font_string ("AUTO");

		set_2d_mono_font_position (0.0, 0.3);

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

	result = get_local_entity_weapon_hardpoint_info (en, COMANCHE_LHS_CHAFF_DISPENSER, ENTITY_SUB_TYPE_WEAPON_CHAFF, &weapon_sub_type, &number, &damaged);

	if (result)
	{
		set_2d_mono_font_position (-0.675, 0.7);

		if (!damaged)
		{
			if (number > 0)
			{
				set_mono_font_colour (MFD_COLOUR1);
			}
			else
			{
				set_mono_font_colour (MFD_COLOUR5);
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
			set_mono_font_colour (MFD_COLOUR5);

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

	result = get_local_entity_weapon_hardpoint_info (en, COMANCHE_LHS_FLARE_DISPENSER, ENTITY_SUB_TYPE_WEAPON_FLARE, &weapon_sub_type, &number, &damaged);

	if (result)
	{
		set_2d_mono_font_position (-0.675, 0.6);

		if (!damaged)
		{
			if (number > 0)
			{
				set_mono_font_colour (MFD_COLOUR1);
			}
			else
			{
				set_mono_font_colour (MFD_COLOUR5);
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
			set_mono_font_colour (MFD_COLOUR5);

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

	result = get_local_entity_weapon_hardpoint_info (en, COMANCHE_RHS_CHAFF_DISPENSER, ENTITY_SUB_TYPE_WEAPON_CHAFF, &weapon_sub_type, &number, &damaged);

	if (result)
	{
		set_2d_mono_font_position (0.675, 0.7);

		if (!damaged)
		{
			if (number > 0)
			{
				set_mono_font_colour (MFD_COLOUR1);
			}
			else
			{
				set_mono_font_colour (MFD_COLOUR5);
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
			set_mono_font_colour (MFD_COLOUR5);

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

	result = get_local_entity_weapon_hardpoint_info (en, COMANCHE_RHS_FLARE_DISPENSER, ENTITY_SUB_TYPE_WEAPON_FLARE, &weapon_sub_type, &number, &damaged);

	if (result)
	{
		set_2d_mono_font_position (0.675, 0.6);

		if (!damaged)
		{
			if (number > 0)
			{
				set_mono_font_colour (MFD_COLOUR1);
			}
			else
			{
				set_mono_font_colour (MFD_COLOUR5);
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
			set_mono_font_colour (MFD_COLOUR5);

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

	result = get_local_entity_weapon_hardpoint_info (en, COMANCHE_CANNON_TURRET, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, &weapon_sub_type, &number, &damaged);

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
			set_mono_font_colour (MFD_COLOUR5);
		}

		//
		// weapon name and number
		//

		sprintf (s, "%sx%03d", weapon_database[weapon_sub_type].mfd_name, number);

		set_2d_mono_font_position (0.0, -0.0);

		x_adjust = get_mono_font_string_width (s) * -0.5;

		set_mono_font_rel_position (x_adjust, 0.0);

		print_mono_font_string (s);

		//
		// lines
		//

		if (draw_large_mfd)
		{
			if (damaged)
			{
				draw_2d_half_thick_line (0.0 - 0.05, 0.07 - 0.03, 0.0 + 0.05, 0.07 + 0.03, MFD_COLOUR1);

				draw_2d_half_thick_line (0.0 + 0.05, 0.07 - 0.03, 0.0 - 0.05, 0.07 + 0.03, MFD_COLOUR1);
			}
		}
		else
		{
			if (damaged)
			{
				draw_2d_line (0.0 - 0.05, 0.07 - 0.03, 0.0 + 0.05, 0.07 + 0.03, MFD_COLOUR1);

				draw_2d_line (0.0 + 0.05, 0.07 - 0.03, 0.0 - 0.05, 0.07 + 0.03, MFD_COLOUR1);
			}
		}
	}

	////////////////////////////////////////
	//
	// lh bay door inner pylon
	//
	////////////////////////////////////////

	result = get_local_entity_weapon_hardpoint_info (en, COMANCHE_LHS_BAY_DOOR_INNER, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, &weapon_sub_type, &number, &damaged);

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
			set_mono_font_colour (MFD_COLOUR5);
		}

		//
		// number
		//

		sprintf (s, "x%02d", number);

		set_2d_mono_font_position (-0.24, -0.1);

		set_mono_font_rel_position (0.0, get_mono_font_char_height ('X'));

		print_mono_font_string (s);

		//
		// lines
		//

		if (draw_large_mfd)
		{
			draw_2d_half_thick_line (-0.29, 0.19, -0.29, -0.16, MFD_COLOUR5);

			draw_2d_half_thick_line (-0.26, -0.16, -0.29, -0.16, MFD_COLOUR5);

			if (damaged)
			{
				draw_2d_half_thick_line (-0.29 - 0.03, 0.225 - 0.05, -0.29 + 0.03, 0.225 + 0.05, MFD_COLOUR1);

				draw_2d_half_thick_line (-0.29 + 0.03, 0.225 - 0.05, -0.29 - 0.03, 0.225 + 0.05, MFD_COLOUR1);
			}
		}
		else
		{
			draw_2d_line (-0.29, 0.19, -0.29, -0.16, MFD_COLOUR5);

			draw_2d_line (-0.26, -0.16, -0.29, -0.16, MFD_COLOUR5);

			if (damaged)
			{
				draw_2d_line (-0.29 - 0.03, 0.225 - 0.05, -0.29 + 0.03, 0.225 + 0.05, MFD_COLOUR1);

				draw_2d_line (-0.29 + 0.03, 0.225 - 0.05, -0.29 - 0.03, 0.225 + 0.05, MFD_COLOUR1);
			}
		}
	}

	////////////////////////////////////////
	//
	// rh bay door inner pylon
	//
	////////////////////////////////////////

	result = get_local_entity_weapon_hardpoint_info (en, COMANCHE_RHS_BAY_DOOR_INNER, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, &weapon_sub_type, &number, &damaged);

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
			set_mono_font_colour (MFD_COLOUR5);
		}

		//
		// number
		//

		sprintf (s, "x%02d", number);

		set_2d_mono_font_position (0.24, -0.1);

		x_adjust = -get_mono_font_string_width (s) + 1.0;

		set_mono_font_rel_position (x_adjust, get_mono_font_char_height ('X'));

		print_mono_font_string (s);

		//
		// weapon name
		//

		set_2d_mono_font_position (0.0, -0.1);

		x_adjust = get_mono_font_string_width (weapon_database[weapon_sub_type].mfd_name) * -0.5;

		set_mono_font_rel_position (x_adjust, 0.0);

		print_mono_font_string (weapon_database[weapon_sub_type].mfd_name);

		//
		// lines
		//

		if (draw_large_mfd)
		{
			draw_2d_half_thick_line (0.29, 0.19, 0.29, -0.16, MFD_COLOUR5);

			draw_2d_half_thick_line (0.26, -0.16, 0.29, -0.16, MFD_COLOUR5);

			if (damaged)
			{
				draw_2d_half_thick_line (0.29 - 0.03, 0.225 - 0.05, 0.29 + 0.03, 0.225 + 0.05, MFD_COLOUR1);

				draw_2d_half_thick_line (0.29 + 0.03, 0.225 - 0.05, 0.29 - 0.03, 0.225 + 0.05, MFD_COLOUR1);
			}
		}
		else
		{
			draw_2d_line (0.29, 0.19, 0.29, -0.16, MFD_COLOUR5);

			draw_2d_line (0.26, -0.16, 0.29, -0.16, MFD_COLOUR5);

			if (damaged)
			{
				draw_2d_line (0.29 - 0.03, 0.225 - 0.05, 0.29 + 0.03, 0.225 + 0.05, MFD_COLOUR1);

				draw_2d_line (0.29 + 0.03, 0.225 - 0.05, 0.29 - 0.03, 0.225 + 0.05, MFD_COLOUR1);
			}
		}
	}

	////////////////////////////////////////
	//
	// lh bay door middle pylon
	//
	////////////////////////////////////////

	result = get_local_entity_weapon_hardpoint_info (en, COMANCHE_LHS_BAY_DOOR_MIDDLE, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, &weapon_sub_type, &number, &damaged);

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
			set_mono_font_colour (MFD_COLOUR5);
		}

		//
		// number
		//

		sprintf (s, "x%02d", number);

		set_2d_mono_font_position (-0.24, -0.3);

		set_mono_font_rel_position (0.0, get_mono_font_char_height ('X'));

		print_mono_font_string (s);

		//
		// lines
		//

		if (draw_large_mfd)
		{
			draw_2d_half_thick_line (-0.38, 0.17, -0.38, -0.36, MFD_COLOUR5);

			draw_2d_half_thick_line (-0.26, -0.36, -0.38, -0.36, MFD_COLOUR5);

			if (damaged)
			{
				draw_2d_half_thick_line (-0.38 - 0.03, 0.2 - 0.05, -0.38 + 0.03, 0.2 + 0.05, MFD_COLOUR1);

				draw_2d_half_thick_line (-0.38 + 0.03, 0.2 - 0.05, -0.38 - 0.03, 0.2 + 0.05, MFD_COLOUR1);
			}
		}
		else
		{
			draw_2d_line (-0.38, 0.17, -0.38, -0.36, MFD_COLOUR5);

			draw_2d_line (-0.26, -0.36, -0.38, -0.36, MFD_COLOUR5);

			if (damaged)
			{
				draw_2d_line (-0.38 - 0.03, 0.2 - 0.05, -0.38 + 0.03, 0.2 + 0.05, MFD_COLOUR1);

				draw_2d_line (-0.38 + 0.03, 0.2 - 0.05, -0.38 - 0.03, 0.2 + 0.05, MFD_COLOUR1);
			}
		}
	}

	////////////////////////////////////////
	//
	// rh bay door middle pylon
	//
	////////////////////////////////////////

	result = get_local_entity_weapon_hardpoint_info (en, COMANCHE_RHS_BAY_DOOR_MIDDLE, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, &weapon_sub_type, &number, &damaged);

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
			set_mono_font_colour (MFD_COLOUR5);
		}

		//
		// number
		//

		sprintf (s, "x%02d", number);

		set_2d_mono_font_position (0.24, -0.3);

		x_adjust = -get_mono_font_string_width (s) + 1.0;

		set_mono_font_rel_position (x_adjust, get_mono_font_char_height ('X'));

		print_mono_font_string (s);

		//
		// weapon name
		//

		set_2d_mono_font_position (0.0, -0.3);

		x_adjust = get_mono_font_string_width (weapon_database[weapon_sub_type].mfd_name) * -0.5;

		set_mono_font_rel_position (x_adjust, 0.0);

		print_mono_font_string (weapon_database[weapon_sub_type].mfd_name);

		//
		// lines
		//

		if (draw_large_mfd)
		{
			draw_2d_half_thick_line (0.38, 0.17, 0.38, -0.36, MFD_COLOUR5);

			draw_2d_half_thick_line (0.26, -0.36, 0.38, -0.36, MFD_COLOUR5);

			if (damaged)
			{
				draw_2d_half_thick_line (0.38 - 0.03, 0.2 - 0.05, 0.38 + 0.03, 0.2 + 0.05, MFD_COLOUR1);

				draw_2d_half_thick_line (0.38 + 0.03, 0.2 - 0.05, 0.38 - 0.03, 0.2 + 0.05, MFD_COLOUR1);
			}
		}
		else
		{
			draw_2d_line (0.38, 0.17, 0.38, -0.36, MFD_COLOUR5);

			draw_2d_line (0.26, -0.36, 0.38, -0.36, MFD_COLOUR5);

			if (damaged)
			{
				draw_2d_line (0.38 - 0.03, 0.2 - 0.05, 0.38 + 0.03, 0.2 + 0.05, MFD_COLOUR1);

				draw_2d_line (0.38 + 0.03, 0.2 - 0.05, 0.38 - 0.03, 0.2 + 0.05, MFD_COLOUR1);
			}
		}
	}

	////////////////////////////////////////
	//
	// lh bay door outer pylon
	//
	////////////////////////////////////////

	result = get_local_entity_weapon_hardpoint_info (en, COMANCHE_LHS_BAY_DOOR_OUTER, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, &weapon_sub_type, &number, &damaged);

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
			set_mono_font_colour (MFD_COLOUR5);
		}

		//
		// number
		//

		sprintf (s, "x%02d", number);

		set_2d_mono_font_position (-0.24, -0.5);

		set_mono_font_rel_position (0.0, get_mono_font_char_height ('X'));

		print_mono_font_string (s);

		//
		// lines
		//

		if (draw_large_mfd)
		{
			draw_2d_half_thick_line (-0.46, 0.14, -0.46, -0.56, MFD_COLOUR5);

			draw_2d_half_thick_line (-0.26, -0.56, -0.46, -0.56, MFD_COLOUR5);

			if (damaged)
			{
				draw_2d_half_thick_line (-0.46 - 0.03, 0.17 - 0.05, -0.46 + 0.03, 0.17 + 0.05, MFD_COLOUR1);

				draw_2d_half_thick_line (-0.46 + 0.03, 0.17 - 0.05, -0.46 - 0.03, 0.17 + 0.05, MFD_COLOUR1);
			}
		}
		else
		{
			draw_2d_line (-0.46, 0.14, -0.46, -0.56, MFD_COLOUR5);

			draw_2d_line (-0.26, -0.56, -0.46, -0.56, MFD_COLOUR5);

			if (damaged)
			{
				draw_2d_line (-0.46 - 0.03, 0.17 - 0.05, -0.46 + 0.03, 0.17 + 0.05, MFD_COLOUR1);

				draw_2d_line (-0.46 + 0.03, 0.17 - 0.05, -0.46 - 0.03, 0.17 + 0.05, MFD_COLOUR1);
			}
		}
	}

	////////////////////////////////////////
	//
	// rh bay door outer pylon
	//
	////////////////////////////////////////

	result = get_local_entity_weapon_hardpoint_info (en, COMANCHE_RHS_BAY_DOOR_OUTER, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, &weapon_sub_type, &number, &damaged);

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
			set_mono_font_colour (MFD_COLOUR5);
		}

		//
		// number
		//

		sprintf (s, "x%02d", number);

		set_2d_mono_font_position (0.24, -0.5);

		x_adjust = -get_mono_font_string_width (s) + 1.0;

		set_mono_font_rel_position (x_adjust, get_mono_font_char_height ('X'));

		print_mono_font_string (s);

		//
		// weapon name
		//

		set_2d_mono_font_position (0.0, -0.5);

		x_adjust = get_mono_font_string_width (weapon_database[weapon_sub_type].mfd_name) * -0.5;

		set_mono_font_rel_position (x_adjust, 0.0);

		print_mono_font_string (weapon_database[weapon_sub_type].mfd_name);

		//
		// lines
		//

		if (draw_large_mfd)
		{
			draw_2d_half_thick_line (0.46, 0.14, 0.46, -0.56, MFD_COLOUR5);

			draw_2d_half_thick_line (0.26, -0.56, 0.46, -0.56, MFD_COLOUR5);

			if (damaged)
			{
				draw_2d_half_thick_line (0.46 - 0.03, 0.17 - 0.05, 0.46 + 0.03, 0.17 + 0.05, MFD_COLOUR1);

				draw_2d_half_thick_line (0.46 + 0.03, 0.17 - 0.05, 0.46 - 0.03, 0.17 + 0.05, MFD_COLOUR1);
			}
		}
		else
		{
			draw_2d_line (0.46, 0.14, 0.46, -0.56, MFD_COLOUR5);

			draw_2d_line (0.26, -0.56, 0.46, -0.56, MFD_COLOUR5);

			if (damaged)
			{
				draw_2d_line (0.46 - 0.03, 0.17 - 0.05, 0.46 + 0.03, 0.17 + 0.05, MFD_COLOUR1);

				draw_2d_line (0.46 + 0.03, 0.17 - 0.05, 0.46 - 0.03, 0.17 + 0.05, MFD_COLOUR1);
			}
		}
	}

	////////////////////////////////////////
	//
	// lh stub wing pylon
	//
	////////////////////////////////////////

	if (stub_wings_attached)
	{
		result = get_local_entity_weapon_hardpoint_info (en, COMANCHE_LHS_STUB_WING, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, &weapon_sub_type, &number, &damaged);

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
				set_mono_font_colour (MFD_COLOUR5);
			}

			//
			// number
			//

			sprintf (s, "x%02d", number);

			set_2d_mono_font_position (-0.24, -0.7);

			set_mono_font_rel_position (0.0, get_mono_font_char_height ('X'));

			print_mono_font_string (s);

			//
			// lines
			//

			if (draw_large_mfd)
			{
				draw_2d_half_thick_line (-0.55, 0.29, -0.55, -0.76, MFD_COLOUR5);

				draw_2d_half_thick_line (-0.26, -0.76, -0.55, -0.76, MFD_COLOUR5);

				if (damaged)
				{
					draw_2d_half_thick_line (-0.55 - 0.03, 0.33 - 0.05, -0.55 + 0.03, 0.33 + 0.05, MFD_COLOUR1);

					draw_2d_half_thick_line (-0.55 + 0.03, 0.33 - 0.05, -0.55 - 0.03, 0.33 + 0.05, MFD_COLOUR1);
				}
			}
			else
			{
				draw_2d_line (-0.55, 0.29, -0.55, -0.76, MFD_COLOUR5);

				draw_2d_line (-0.26, -0.76, -0.55, -0.76, MFD_COLOUR5);

				if (damaged)
				{
					draw_2d_line (-0.55 - 0.03, 0.33 - 0.05, -0.55 + 0.03, 0.33 + 0.05, MFD_COLOUR1);

					draw_2d_line (-0.55 + 0.03, 0.33 - 0.05, -0.55 - 0.03, 0.33 + 0.05, MFD_COLOUR1);
				}
			}
		}
	}

	////////////////////////////////////////
	//
	// rh stub wing pylon
	//
	////////////////////////////////////////

	if (stub_wings_attached)
	{
		result = get_local_entity_weapon_hardpoint_info (en, COMANCHE_RHS_STUB_WING, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, &weapon_sub_type, &number, &damaged);

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
				set_mono_font_colour (MFD_COLOUR5);
			}

			//
			// number
			//

			sprintf (s, "x%02d", number);

			set_2d_mono_font_position (0.24, -0.7);

			x_adjust = -get_mono_font_string_width (s) + 1.0;

			set_mono_font_rel_position (x_adjust, get_mono_font_char_height ('X'));

			print_mono_font_string (s);

			//
			// weapon name
			//

			set_2d_mono_font_position (0.0, -0.7);

			x_adjust = get_mono_font_string_width (weapon_database[weapon_sub_type].mfd_name) * -0.5;

			set_mono_font_rel_position (x_adjust, 0.0);

			print_mono_font_string (weapon_database[weapon_sub_type].mfd_name);

			//
			// lines
			//

			if (draw_large_mfd)
			{
				draw_2d_half_thick_line (0.55, 0.29, 0.55, -0.76, MFD_COLOUR5);

				draw_2d_half_thick_line (0.26, -0.76, 0.55, -0.76, MFD_COLOUR5);

				if (damaged)
				{
					draw_2d_half_thick_line (0.55 - 0.03, 0.33 - 0.05, 0.55 + 0.03, 0.33 + 0.05, MFD_COLOUR1);

					draw_2d_half_thick_line (0.55 + 0.03, 0.33 - 0.05, 0.55 - 0.03, 0.33 + 0.05, MFD_COLOUR1);
				}
			}
			else
			{
				draw_2d_line (0.55, 0.29, 0.55, -0.76, MFD_COLOUR5);

				draw_2d_line (0.26, -0.76, 0.55, -0.76, MFD_COLOUR5);

				if (damaged)
				{
					draw_2d_line (0.55 - 0.03, 0.33 - 0.05, 0.55 + 0.03, 0.33 + 0.05, MFD_COLOUR1);

					draw_2d_line (0.55 + 0.03, 0.33 - 0.05, 0.55 - 0.03, 0.33 + 0.05, MFD_COLOUR1);
				}
			}
		}
	}

	////////////////////////////////////////
	//
	// rocket salvo
	//
	////////////////////////////////////////

	if ((selected_weapon == ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255) || (selected_weapon == ENTITY_SUB_TYPE_WEAPON_HYDRA70_M261))
	{
		set_mono_font_colour (MFD_COLOUR1);
	}
	else
	{
		set_mono_font_colour (MFD_COLOUR5);
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

static void draw_weapon_display_side_mfd (void)
{
	char
		s[80];

	int
		i,
		result,
		number,
		damaged,
		stub_wings_attached;

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

	stub_wings_attached = get_comanche_stub_wings_attached (get_gunship_entity ());

	if (stub_wings_attached)
	{
		if (draw_large_mfd)
		{
			i = 0;

			while (i < num_side_weapon_line_points_with_stub_wings)
			{
				draw_2d_half_thick_line
				(
					side_weapon_line_points_with_stub_wings[i].x,
					side_weapon_line_points_with_stub_wings[i].y,
					side_weapon_line_points_with_stub_wings[i + 1].x,
					side_weapon_line_points_with_stub_wings[i + 1].y,
					MFD_COLOUR4
				);

				i += 2;
			}
		}
		else
		{
			i = 0;

			while (i < num_side_weapon_line_points_with_stub_wings)
			{
				draw_2d_line
				(
					side_weapon_line_points_with_stub_wings[i].x,
					side_weapon_line_points_with_stub_wings[i].y,
					side_weapon_line_points_with_stub_wings[i + 1].x,
					side_weapon_line_points_with_stub_wings[i + 1].y,
					MFD_COLOUR4
				);

				i += 2;
			}
		}
	}
	else
	{
		if (draw_large_mfd)
		{
			i = 0;

			while (i < num_side_weapon_line_points_without_stub_wings)
			{
				draw_2d_half_thick_line
				(
					side_weapon_line_points_without_stub_wings[i].x,
					side_weapon_line_points_without_stub_wings[i].y,
					side_weapon_line_points_without_stub_wings[i + 1].x,
					side_weapon_line_points_without_stub_wings[i + 1].y,
					MFD_COLOUR4
				);

				i += 2;
			}
		}
		else
		{
			i = 0;

			while (i < num_side_weapon_line_points_without_stub_wings)
			{
				draw_2d_line
				(
					side_weapon_line_points_without_stub_wings[i].x,
					side_weapon_line_points_without_stub_wings[i].y,
					side_weapon_line_points_without_stub_wings[i + 1].x,
					side_weapon_line_points_without_stub_wings[i + 1].y,
					MFD_COLOUR4
				);

				i += 2;
			}
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
		set_mono_font_colour (MFD_COLOUR5);
	}

	if (draw_large_mfd)
	{
		set_mono_font_type (MONO_FONT_TYPE_7X12);

		set_2d_mono_font_position (-0.4, 0.5);

		x_adjust = get_mono_font_string_width ("ARM") * -0.5;

		set_mono_font_rel_position (x_adjust, 0.0);

		print_mono_font_string ("ARM");
	}
	else
	{
		set_mono_font_type (MONO_FONT_TYPE_5X7);

		set_2d_mono_font_position (-0.4, 0.5);

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
		set_mono_font_colour (MFD_COLOUR5);
	}

	if (draw_large_mfd)
	{
		set_mono_font_type (MONO_FONT_TYPE_6X10);

		set_2d_mono_font_position (-0.4, 0.3);

		x_adjust = get_mono_font_string_width ("AUTO") * -0.5;

		set_mono_font_rel_position (x_adjust, 0.0);

		print_mono_font_string ("AUTO");

		set_2d_mono_font_position (-0.4, 0.3);

		x_adjust = get_mono_font_string_width ("C/M") * -0.5;

		set_mono_font_rel_position (x_adjust, get_mono_font_char_height ('X'));

		print_mono_font_string ("C/M");
	}
	else
	{
		set_mono_font_type (MONO_FONT_TYPE_5X7);

		set_2d_mono_font_position (-0.4, 0.3);

		x_adjust = get_mono_font_string_width ("AUTO") * -0.5;

		set_mono_font_rel_position (x_adjust, 0.0);

		print_mono_font_string ("AUTO");

		set_2d_mono_font_position (-0.4, 0.3);

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

	result = get_local_entity_weapon_hardpoint_info (en, COMANCHE_LHS_CHAFF_DISPENSER, ENTITY_SUB_TYPE_WEAPON_CHAFF, &weapon_sub_type, &number, &damaged);

	if (result)
	{
		set_2d_mono_font_position (-0.55 - 0.4, 0.7);

		if (!damaged)
		{
			if (number > 0)
			{
				set_mono_font_colour (MFD_COLOUR1);
			}
			else
			{
				set_mono_font_colour (MFD_COLOUR5);
			}

			if (draw_large_mfd)
			{
				sprintf (s, "CHFx%02d", number);
			}
			else
			{
				sprintf (s, "Cx%02d", number);
			}

			print_mono_font_string (s);
		}
		else
		{
			set_mono_font_colour (MFD_COLOUR5);

			if (draw_large_mfd)
			{
				print_mono_font_string ("CHFxXX");
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

	result = get_local_entity_weapon_hardpoint_info (en, COMANCHE_LHS_FLARE_DISPENSER, ENTITY_SUB_TYPE_WEAPON_FLARE, &weapon_sub_type, &number, &damaged);

	if (result)
	{
		set_2d_mono_font_position (-0.55 - 0.4, 0.6);

		if (!damaged)
		{
			if (number > 0)
			{
				set_mono_font_colour (MFD_COLOUR1);
			}
			else
			{
				set_mono_font_colour (MFD_COLOUR5);
			}

			if (draw_large_mfd)
			{
				sprintf (s, "FLRx%02d", number);
			}
			else
			{
				sprintf (s, "Fx%02d", number);
			}

			print_mono_font_string (s);
		}
		else
		{
			set_mono_font_colour (MFD_COLOUR5);

			if (draw_large_mfd)
			{
				print_mono_font_string ("FLRxXX");
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

	result = get_local_entity_weapon_hardpoint_info (en, COMANCHE_RHS_CHAFF_DISPENSER, ENTITY_SUB_TYPE_WEAPON_CHAFF, &weapon_sub_type, &number, &damaged);

	if (result)
	{
		set_2d_mono_font_position (0.55 - 0.4, 0.7);

		if (!damaged)
		{
			if (number > 0)
			{
				set_mono_font_colour (MFD_COLOUR1);
			}
			else
			{
				set_mono_font_colour (MFD_COLOUR5);
			}

			if (draw_large_mfd)
			{
				sprintf (s, "CHFx%02d", number);
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
			set_mono_font_colour (MFD_COLOUR5);

			if (draw_large_mfd)
			{
				x_adjust = -get_mono_font_string_width ("CHFxXX");

				set_mono_font_rel_position (x_adjust, 0.0);

				print_mono_font_string ("CHFxXX");
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

	result = get_local_entity_weapon_hardpoint_info (en, COMANCHE_RHS_FLARE_DISPENSER, ENTITY_SUB_TYPE_WEAPON_FLARE, &weapon_sub_type, &number, &damaged);

	if (result)
	{
		set_2d_mono_font_position (0.55 - 0.4, 0.6);

		if (!damaged)
		{
			if (number > 0)
			{
				set_mono_font_colour (MFD_COLOUR1);
			}
			else
			{
				set_mono_font_colour (MFD_COLOUR5);
			}

			if (draw_large_mfd)
			{
				sprintf (s, "FLRx%02d", number);
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
			set_mono_font_colour (MFD_COLOUR5);

			if (draw_large_mfd)
			{
				x_adjust = -get_mono_font_string_width ("FLRxXX");

				set_mono_font_rel_position (x_adjust, 0.0);

				print_mono_font_string ("FLRxXX");
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

	result = get_local_entity_weapon_hardpoint_info (en, COMANCHE_CANNON_TURRET, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, &weapon_sub_type, &number, &damaged);

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
			set_mono_font_colour (MFD_COLOUR5);
		}

		//
		// weapon name and number
		//

		sprintf (s, "%sx%03d", weapon_database[weapon_sub_type].mfd_name, number);

		set_2d_mono_font_position (-0.4, -0.0);

		x_adjust = get_mono_font_string_width (s) * -0.5;

		set_mono_font_rel_position (x_adjust, 0.0);

		print_mono_font_string (s);

		//
		// lines
		//

		if (draw_large_mfd)
		{
			if (damaged)
			{
				draw_2d_half_thick_line (0.0 - 0.05 - 0.4, 0.07 - 0.03, 0.0 + 0.05 - 0.4, 0.07 + 0.03, MFD_COLOUR1);

				draw_2d_half_thick_line (0.0 + 0.05 - 0.4, 0.07 - 0.03, 0.0 - 0.05 - 0.4, 0.07 + 0.03, MFD_COLOUR1);
			}
		}
		else
		{
			if (damaged)
			{
				draw_2d_line (0.0 - 0.05 - 0.4, 0.07 - 0.03, 0.0 + 0.05 - 0.4, 0.07 + 0.03, MFD_COLOUR1);

				draw_2d_line (0.0 + 0.05 - 0.4, 0.07 - 0.03, 0.0 - 0.05 - 0.4, 0.07 + 0.03, MFD_COLOUR1);
			}
		}
	}

	////////////////////////////////////////
	//
	// lh bay door inner pylon
	//
	////////////////////////////////////////

	result = get_local_entity_weapon_hardpoint_info (en, COMANCHE_LHS_BAY_DOOR_INNER, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, &weapon_sub_type, &number, &damaged);

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
			set_mono_font_colour (MFD_COLOUR5);
		}

		//
		// number
		//

		sprintf (s, "x%02d", number);

		set_2d_mono_font_position (-0.24 - 0.4, -0.1);

		set_mono_font_rel_position (0.0, get_mono_font_char_height ('X'));

		print_mono_font_string (s);

		//
		// lines
		//

		if (draw_large_mfd)
		{
			draw_2d_half_thick_line (-0.29 - 0.4, 0.19, -0.29 - 0.4, -0.16, MFD_COLOUR5);

			draw_2d_half_thick_line (-0.26 - 0.4, -0.16, -0.29 - 0.4, -0.16, MFD_COLOUR5);

			if (damaged)
			{
				draw_2d_half_thick_line (-0.29 - 0.03 - 0.4, 0.225 - 0.05, -0.29 + 0.03 - 0.4, 0.225 + 0.05, MFD_COLOUR1);

				draw_2d_half_thick_line (-0.29 + 0.03 - 0.4, 0.225 - 0.05, -0.29 - 0.03 - 0.4, 0.225 + 0.05, MFD_COLOUR1);
			}
		}
		else
		{
			draw_2d_line (-0.29 - 0.4, 0.19, -0.29 - 0.4, -0.16, MFD_COLOUR5);

			draw_2d_line (-0.26 - 0.4, -0.16, -0.29 - 0.4, -0.16, MFD_COLOUR5);

			if (damaged)
			{
				draw_2d_line (-0.29 - 0.03 - 0.4, 0.225 - 0.05, -0.29 + 0.03 - 0.4, 0.225 + 0.05, MFD_COLOUR1);

				draw_2d_line (-0.29 + 0.03 - 0.4, 0.225 - 0.05, -0.29 - 0.03 - 0.4, 0.225 + 0.05, MFD_COLOUR1);
			}
		}
	}

	////////////////////////////////////////
	//
	// rh bay door inner pylon
	//
	////////////////////////////////////////

	result = get_local_entity_weapon_hardpoint_info (en, COMANCHE_RHS_BAY_DOOR_INNER, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, &weapon_sub_type, &number, &damaged);

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
			set_mono_font_colour (MFD_COLOUR5);
		}

		//
		// number
		//

		sprintf (s, "x%02d", number);

		set_2d_mono_font_position (0.24 - 0.4, -0.1);

		x_adjust = -get_mono_font_string_width (s) + 1.0;

		set_mono_font_rel_position (x_adjust, get_mono_font_char_height ('X'));

		print_mono_font_string (s);

		//
		// weapon name
		//

		set_2d_mono_font_position (-0.4, -0.1);

		x_adjust = get_mono_font_string_width (weapon_database[weapon_sub_type].mfd_name) * -0.5;

		set_mono_font_rel_position (x_adjust, 0.0);

		print_mono_font_string (weapon_database[weapon_sub_type].mfd_name);

		//
		// lines
		//

		if (draw_large_mfd)
		{
			draw_2d_half_thick_line (0.29 - 0.4, 0.19, 0.29 - 0.4, -0.16, MFD_COLOUR5);

			draw_2d_half_thick_line (0.26 - 0.4, -0.16, 0.29 - 0.4, -0.16, MFD_COLOUR5);

			if (damaged)
			{
				draw_2d_half_thick_line (0.29 - 0.03 - 0.4, 0.225 - 0.05, 0.29 + 0.03 - 0.4, 0.225 + 0.05, MFD_COLOUR1);

				draw_2d_half_thick_line (0.29 + 0.03 - 0.4, 0.225 - 0.05, 0.29 - 0.03 - 0.4, 0.225 + 0.05, MFD_COLOUR1);
			}
		}
		else
		{
			draw_2d_line (0.29 - 0.4, 0.19, 0.29 - 0.4, -0.16, MFD_COLOUR5);

			draw_2d_line (0.26 - 0.4, -0.16, 0.29 - 0.4, -0.16, MFD_COLOUR5);

			if (damaged)
			{
				draw_2d_line (0.29 - 0.03 - 0.4, 0.225 - 0.05, 0.29 + 0.03 - 0.4, 0.225 + 0.05, MFD_COLOUR1);

				draw_2d_line (0.29 + 0.03 - 0.4, 0.225 - 0.05, 0.29 - 0.03 - 0.4, 0.225 + 0.05, MFD_COLOUR1);
			}
		}
	}

	////////////////////////////////////////
	//
	// lh bay door middle pylon
	//
	////////////////////////////////////////

	result = get_local_entity_weapon_hardpoint_info (en, COMANCHE_LHS_BAY_DOOR_MIDDLE, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, &weapon_sub_type, &number, &damaged);

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
			set_mono_font_colour (MFD_COLOUR5);
		}

		//
		// number
		//

		sprintf (s, "x%02d", number);

		set_2d_mono_font_position (-0.24 - 0.4, -0.3);

		set_mono_font_rel_position (0.0, get_mono_font_char_height ('X'));

		print_mono_font_string (s);

		//
		// lines
		//

		if (draw_large_mfd)
		{
			draw_2d_half_thick_line (-0.38 - 0.4, 0.17, -0.38 - 0.4, -0.36, MFD_COLOUR5);

			draw_2d_half_thick_line (-0.26 - 0.4, -0.36, -0.38 - 0.4, -0.36, MFD_COLOUR5);

			if (damaged)
			{
				draw_2d_half_thick_line (-0.38 - 0.03 - 0.4, 0.2 - 0.05, -0.38 + 0.03 - 0.4, 0.2 + 0.05, MFD_COLOUR1);

				draw_2d_half_thick_line (-0.38 + 0.03 - 0.4, 0.2 - 0.05, -0.38 - 0.03 - 0.4, 0.2 + 0.05, MFD_COLOUR1);
			}
		}
		else
		{
			draw_2d_line (-0.38 - 0.4, 0.17, -0.38 - 0.4, -0.36, MFD_COLOUR5);

			draw_2d_line (-0.26 - 0.4, -0.36, -0.38 - 0.4, -0.36, MFD_COLOUR5);

			if (damaged)
			{
				draw_2d_line (-0.38 - 0.03 - 0.4, 0.2 - 0.05, -0.38 + 0.03 - 0.4, 0.2 + 0.05, MFD_COLOUR1);

				draw_2d_line (-0.38 + 0.03 - 0.4, 0.2 - 0.05, -0.38 - 0.03 - 0.4, 0.2 + 0.05, MFD_COLOUR1);
			}
		}
	}

	////////////////////////////////////////
	//
	// rh bay door middle pylon
	//
	////////////////////////////////////////

	result = get_local_entity_weapon_hardpoint_info (en, COMANCHE_RHS_BAY_DOOR_MIDDLE, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, &weapon_sub_type, &number, &damaged);

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
			set_mono_font_colour (MFD_COLOUR5);
		}

		//
		// number
		//

		sprintf (s, "x%02d", number);

		set_2d_mono_font_position (0.24 - 0.4, -0.3);

		x_adjust = -get_mono_font_string_width (s) + 1.0;

		set_mono_font_rel_position (x_adjust, get_mono_font_char_height ('X'));

		print_mono_font_string (s);

		//
		// weapon name
		//

		set_2d_mono_font_position (-0.4, -0.3);

		x_adjust = get_mono_font_string_width (weapon_database[weapon_sub_type].mfd_name) * -0.5;

		set_mono_font_rel_position (x_adjust, 0.0);

		print_mono_font_string (weapon_database[weapon_sub_type].mfd_name);

		//
		// lines
		//

		if (draw_large_mfd)
		{
			draw_2d_half_thick_line (0.38 - 0.4, 0.17, 0.38 - 0.4, -0.36, MFD_COLOUR5);

			draw_2d_half_thick_line (0.26 - 0.4, -0.36, 0.38 - 0.4, -0.36, MFD_COLOUR5);

			if (damaged)
			{
				draw_2d_half_thick_line (0.38 - 0.03 - 0.4, 0.2 - 0.05, 0.38 + 0.03 - 0.4, 0.2 + 0.05, MFD_COLOUR1);

				draw_2d_half_thick_line (0.38 + 0.03 - 0.4, 0.2 - 0.05, 0.38 - 0.03 - 0.4, 0.2 + 0.05, MFD_COLOUR1);
			}
		}
		else
		{
			draw_2d_line (0.38 - 0.4, 0.17, 0.38 - 0.4, -0.36, MFD_COLOUR5);

			draw_2d_line (0.26 - 0.4, -0.36, 0.38 - 0.4, -0.36, MFD_COLOUR5);

			if (damaged)
			{
				draw_2d_line (0.38 - 0.03 - 0.4, 0.2 - 0.05, 0.38 + 0.03 - 0.4, 0.2 + 0.05, MFD_COLOUR1);

				draw_2d_line (0.38 + 0.03 - 0.4, 0.2 - 0.05, 0.38 - 0.03 - 0.4, 0.2 + 0.05, MFD_COLOUR1);
			}
		}
	}

	////////////////////////////////////////
	//
	// lh bay door outer pylon
	//
	////////////////////////////////////////

	result = get_local_entity_weapon_hardpoint_info (en, COMANCHE_LHS_BAY_DOOR_OUTER, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, &weapon_sub_type, &number, &damaged);

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
			set_mono_font_colour (MFD_COLOUR5);
		}

		//
		// number
		//

		sprintf (s, "x%02d", number);

		set_2d_mono_font_position (-0.24 - 0.4, -0.5);

		set_mono_font_rel_position (0.0, get_mono_font_char_height ('X'));

		print_mono_font_string (s);

		//
		// lines
		//

		if (draw_large_mfd)
		{
			draw_2d_half_thick_line (-0.46 - 0.4, 0.14, -0.46 - 0.4, -0.56, MFD_COLOUR5);

			draw_2d_half_thick_line (-0.26 - 0.4, -0.56, -0.46 - 0.4, -0.56, MFD_COLOUR5);

			if (damaged)
			{
				draw_2d_half_thick_line (-0.46 - 0.03 - 0.4, 0.17 - 0.05, -0.46 + 0.03 - 0.4, 0.17 + 0.05, MFD_COLOUR1);

				draw_2d_half_thick_line (-0.46 + 0.03 - 0.4, 0.17 - 0.05, -0.46 - 0.03 - 0.4, 0.17 + 0.05, MFD_COLOUR1);
			}
		}
		else
		{
			draw_2d_line (-0.46 - 0.4, 0.14, -0.46 - 0.4, -0.56, MFD_COLOUR5);

			draw_2d_line (-0.26 - 0.4, -0.56, -0.46 - 0.4, -0.56, MFD_COLOUR5);

			if (damaged)
			{
				draw_2d_line (-0.46 - 0.03 - 0.4, 0.17 - 0.05, -0.46 + 0.03 - 0.4, 0.17 + 0.05, MFD_COLOUR1);

				draw_2d_line (-0.46 + 0.03 - 0.4, 0.17 - 0.05, -0.46 - 0.03 - 0.4, 0.17 + 0.05, MFD_COLOUR1);
			}
		}
	}

	////////////////////////////////////////
	//
	// rh bay door outer pylon
	//
	////////////////////////////////////////

	result = get_local_entity_weapon_hardpoint_info (en, COMANCHE_RHS_BAY_DOOR_OUTER, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, &weapon_sub_type, &number, &damaged);

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
			set_mono_font_colour (MFD_COLOUR5);
		}

		//
		// number
		//

		sprintf (s, "x%02d", number);

		set_2d_mono_font_position (0.24 - 0.4, -0.5);

		x_adjust = -get_mono_font_string_width (s) + 1.0;

		set_mono_font_rel_position (x_adjust, get_mono_font_char_height ('X'));

		print_mono_font_string (s);

		//
		// weapon name
		//

		set_2d_mono_font_position (-0.4, -0.5);

		x_adjust = get_mono_font_string_width (weapon_database[weapon_sub_type].mfd_name) * -0.5;

		set_mono_font_rel_position (x_adjust, 0.0);

		print_mono_font_string (weapon_database[weapon_sub_type].mfd_name);

		//
		// lines
		//

		if (draw_large_mfd)
		{
			draw_2d_half_thick_line (0.46 - 0.4, 0.14, 0.46 - 0.4, -0.56, MFD_COLOUR5);

			draw_2d_half_thick_line (0.26 - 0.4, -0.56, 0.46 - 0.4, -0.56, MFD_COLOUR5);

			if (damaged)
			{
				draw_2d_half_thick_line (0.46 - 0.03 - 0.4, 0.17 - 0.05, 0.46 + 0.03 - 0.4, 0.17 + 0.05, MFD_COLOUR1);

				draw_2d_half_thick_line (0.46 + 0.03 - 0.4, 0.17 - 0.05, 0.46 - 0.03 - 0.4, 0.17 + 0.05, MFD_COLOUR1);
			}
		}
		else
		{
			draw_2d_line (0.46 - 0.4, 0.14, 0.46 - 0.4, -0.56, MFD_COLOUR5);

			draw_2d_line (0.26 - 0.4, -0.56, 0.46 - 0.4, -0.56, MFD_COLOUR5);

			if (damaged)
			{
				draw_2d_line (0.46 - 0.03 - 0.4, 0.17 - 0.05, 0.46 + 0.03 - 0.4, 0.17 + 0.05, MFD_COLOUR1);

				draw_2d_line (0.46 + 0.03 - 0.4, 0.17 - 0.05, 0.46 - 0.03 - 0.4, 0.17 + 0.05, MFD_COLOUR1);
			}
		}
	}

	////////////////////////////////////////
	//
	// lh stub wing pylon
	//
	////////////////////////////////////////

	if (stub_wings_attached)
	{
		result = get_local_entity_weapon_hardpoint_info (en, COMANCHE_LHS_STUB_WING, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, &weapon_sub_type, &number, &damaged);

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
				set_mono_font_colour (MFD_COLOUR5);
			}

			//
			// number
			//

			sprintf (s, "x%02d", number);

			set_2d_mono_font_position (-0.24 - 0.4, -0.7);

			set_mono_font_rel_position (0.0, get_mono_font_char_height ('X'));

			print_mono_font_string (s);

			//
			// lines
			//

			if (draw_large_mfd)
			{
				draw_2d_half_thick_line (-0.55 - 0.4, 0.29, -0.55 - 0.4, -0.76, MFD_COLOUR5);

				draw_2d_half_thick_line (-0.26 - 0.4, -0.76, -0.55 - 0.4, -0.76, MFD_COLOUR5);

				if (damaged)
				{
					draw_2d_half_thick_line (-0.55 - 0.03 - 0.4, 0.33 - 0.05, -0.55 + 0.03 - 0.4, 0.33 + 0.05, MFD_COLOUR1);

					draw_2d_half_thick_line (-0.55 + 0.03 - 0.4, 0.33 - 0.05, -0.55 - 0.03 - 0.4, 0.33 + 0.05, MFD_COLOUR1);
				}
			}
			else
			{
				draw_2d_line (-0.55 - 0.4, 0.29, -0.55 - 0.4, -0.76, MFD_COLOUR5);

				draw_2d_line (-0.26 - 0.4, -0.76, -0.55 - 0.4, -0.76, MFD_COLOUR5);

				if (damaged)
				{
					draw_2d_line (-0.55 - 0.03 - 0.4, 0.33 - 0.05, -0.55 + 0.03 - 0.4, 0.33 + 0.05, MFD_COLOUR1);

					draw_2d_line (-0.55 + 0.03 - 0.4, 0.33 - 0.05, -0.55 - 0.03 - 0.4, 0.33 + 0.05, MFD_COLOUR1);
				}
			}
		}
	}

	////////////////////////////////////////
	//
	// rh stub wing pylon
	//
	////////////////////////////////////////

	if (stub_wings_attached)
	{
		result = get_local_entity_weapon_hardpoint_info (en, COMANCHE_RHS_STUB_WING, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, &weapon_sub_type, &number, &damaged);

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
				set_mono_font_colour (MFD_COLOUR5);
			}

			//
			// number
			//

			sprintf (s, "x%02d", number);

			set_2d_mono_font_position (0.24 - 0.4, -0.7);

			x_adjust = -get_mono_font_string_width (s) + 1.0;

			set_mono_font_rel_position (x_adjust, get_mono_font_char_height ('X'));

			print_mono_font_string (s);

			//
			// weapon name
			//

			set_2d_mono_font_position (-0.4, -0.7);

			x_adjust = get_mono_font_string_width (weapon_database[weapon_sub_type].mfd_name) * -0.5;

			set_mono_font_rel_position (x_adjust, 0.0);

			print_mono_font_string (weapon_database[weapon_sub_type].mfd_name);

			//
			// lines
			//

			if (draw_large_mfd)
			{
				draw_2d_half_thick_line (0.55 - 0.4, 0.29, 0.55 - 0.4, -0.76, MFD_COLOUR5);

				draw_2d_half_thick_line (0.26 - 0.4, -0.76, 0.55 - 0.4, -0.76, MFD_COLOUR5);

				if (damaged)
				{
					draw_2d_half_thick_line (0.55 - 0.03 - 0.4, 0.33 - 0.05, 0.55 + 0.03 - 0.4, 0.33 + 0.05, MFD_COLOUR1);

					draw_2d_half_thick_line (0.55 + 0.03 - 0.4, 0.33 - 0.05, 0.55 - 0.03 - 0.4, 0.33 + 0.05, MFD_COLOUR1);
				}
			}
			else
			{
				draw_2d_line (0.55 - 0.4, 0.29, 0.55 - 0.4, -0.76, MFD_COLOUR5);

				draw_2d_line (0.26 - 0.4, -0.76, 0.55 - 0.4, -0.76, MFD_COLOUR5);

				if (damaged)
				{
					draw_2d_line (0.55 - 0.03 - 0.4, 0.33 - 0.05, 0.55 + 0.03 - 0.4, 0.33 + 0.05, MFD_COLOUR1);

					draw_2d_line (0.55 + 0.03 - 0.4, 0.33 - 0.05, 0.55 - 0.03 - 0.4, 0.33 + 0.05, MFD_COLOUR1);
				}
			}
		}
	}

	////////////////////////////////////////
	//
	// rocket salvo
	//
	////////////////////////////////////////

	if ((selected_weapon == ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255) || (selected_weapon == ENTITY_SUB_TYPE_WEAPON_HYDRA70_M261))
	{
		set_mono_font_colour (MFD_COLOUR1);
	}
	else
	{
		set_mono_font_colour (MFD_COLOUR5);
	}

	set_2d_mono_font_position (-0.4, -0.9);

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

static float print_main_mfd_system_message (char *equipment, char *warning, int fail, float y_adjust)
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

	set_2d_mono_font_position (-0.9, 0.92125);

	set_mono_font_rel_position (1.0, y_adjust);

	print_mono_font_string (equipment);

	width = get_mono_font_string_width (status);

	set_2d_mono_font_position (0.9, 0.92125);

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
		y_adjust;

	if (draw_large_mfd)
	{
		set_mono_font_type (MONO_FONT_TYPE_7X12);

		y_adjust = 0.0;
	}
	else
	{
		set_mono_font_type (MONO_FONT_TYPE_3X6);

		y_adjust = 0.0;
	}

	y_adjust = print_main_mfd_system_message ("RADAR", "FAIL", comanche_damage.radar, y_adjust);

	y_adjust = print_main_mfd_system_message ("FLIR", "FAIL", comanche_damage.flir, y_adjust);

	y_adjust = print_main_mfd_system_message ("DTV", "FAIL", comanche_damage.dtv, y_adjust);

	//DVO REMOVED//
	/*
	y_adjust = print_main_mfd_system_message ("DVO", "FAIL", comanche_damage.dvo, y_adjust);
	*/
	//DVO REMOVED//

	y_adjust = print_main_mfd_system_message ("LASER DESIGNATOR", "FAIL", comanche_damage.laser_designator, y_adjust);

	y_adjust = print_main_mfd_system_message ("RADAR JAMMER", "FAIL", comanche_damage.radar_jammer, y_adjust);

	y_adjust = print_main_mfd_system_message ("IR JAMMER", "FAIL", comanche_damage.infra_red_jammer, y_adjust);

	y_adjust = print_main_mfd_system_message ("NAVIGATION COMPUTER", "FAIL", comanche_damage.navigation_computer, y_adjust);

	y_adjust = print_main_mfd_system_message ("COMMUNICATIONS", "FAIL", comanche_damage.communications, y_adjust);

	y_adjust = print_main_mfd_system_message ("RADAR WARNING SYSTEM", "FAIL", comanche_damage.radar_warning_system, y_adjust);

	y_adjust = print_main_mfd_system_message ("HIDSS", "FAIL", comanche_damage.hidss, y_adjust);

	y_adjust = print_main_mfd_system_message ("PNVS", "FAIL", comanche_damage.pnvs, y_adjust);

	y_adjust = print_main_mfd_system_message ("STABILISER", "FAIL", get_dynamics_damage_type (DYNAMICS_DAMAGE_STABILISER), y_adjust);

	y_adjust = print_main_mfd_system_message ("MAIN ROTOR", "DAMAGED", get_dynamics_damage_type (DYNAMICS_DAMAGE_MAIN_ROTOR), y_adjust);

	y_adjust = print_main_mfd_system_message ("TAIL ROTOR", "DAMAGED", get_dynamics_damage_type (DYNAMICS_DAMAGE_TAIL_ROTOR), y_adjust);

	y_adjust = print_main_mfd_system_message ("L ENGINE", "DAMAGED", get_dynamics_damage_type (DYNAMICS_DAMAGE_LEFT_ENGINE), y_adjust);

	y_adjust = print_main_mfd_system_message ("APU", "DAMAGED", FALSE, y_adjust);

	y_adjust = print_main_mfd_system_message ("R ENGINE", "DAMAGED", get_dynamics_damage_type (DYNAMICS_DAMAGE_RIGHT_ENGINE), y_adjust);

	y_adjust = print_main_mfd_system_message ("HYDRAULIC PRESSURE", "LOW", get_dynamics_damage_type (DYNAMICS_DAMAGE_LOW_HYDRAULICS), y_adjust);

	if (get_dynamics_damage_type (DYNAMICS_DAMAGE_LOW_OIL_PRESSURE))
	{
		y_adjust = print_main_mfd_system_message ("OIL PRESSURE", "LOW", get_dynamics_damage_type (DYNAMICS_DAMAGE_LOW_OIL_PRESSURE), y_adjust);
	}
	else
	{
		y_adjust = print_main_mfd_system_message ("OIL PRESSURE", "HIGH", get_dynamics_damage_type (DYNAMICS_DAMAGE_HIGH_OIL_PRESSURE), y_adjust);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float print_side_mfd_system_message (char *equipment, char *warning, int fail, float y_adjust)
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

	set_2d_mono_font_position (-0.9, 0.9);

	set_mono_font_rel_position (1.0, y_adjust);

	print_mono_font_string (equipment);

	width = get_mono_font_string_width (status);

	set_2d_mono_font_position (0.1, 0.9);

	set_mono_font_rel_position (-width, y_adjust);

	print_mono_font_string (status);

	y_adjust += get_mono_font_char_height ('X');

	return (y_adjust);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_system_display_side_mfd (void)
{
	float
		y_adjust;

	if (draw_large_mfd)
	{
		set_mono_font_type (MONO_FONT_TYPE_7X12);

		y_adjust = 0.0;
	}
	else
	{
		set_mono_font_type (MONO_FONT_TYPE_3X6);

		y_adjust = 0.0;
	}

	y_adjust = print_side_mfd_system_message ("RADAR", "FAIL", comanche_damage.radar, y_adjust);

	y_adjust = print_side_mfd_system_message ("FLIR", "FAIL", comanche_damage.flir, y_adjust);

	y_adjust = print_side_mfd_system_message ("DTV", "FAIL", comanche_damage.dtv, y_adjust);

	//DVO REMOVED//
	/*
	y_adjust = print_side_mfd_system_message ("DVO", "FAIL", comanche_damage.dvo, y_adjust);
	*/
	//DVO REMOVED//

	y_adjust = print_side_mfd_system_message ("LASER DES", "FAIL", comanche_damage.laser_designator, y_adjust);

	y_adjust = print_side_mfd_system_message ("RADAR JAM", "FAIL", comanche_damage.radar_jammer, y_adjust);

	y_adjust = print_side_mfd_system_message ("IR JAMMER", "FAIL", comanche_damage.infra_red_jammer, y_adjust);

	y_adjust = print_side_mfd_system_message ("NAV COMP", "FAIL", comanche_damage.navigation_computer, y_adjust);

	y_adjust = print_side_mfd_system_message ("COMMS", "FAIL", comanche_damage.communications, y_adjust);

	y_adjust = print_side_mfd_system_message ("RADAR WARN", "FAIL", comanche_damage.radar_warning_system, y_adjust);

	y_adjust = print_side_mfd_system_message ("HIDSS", "FAIL", comanche_damage.hidss, y_adjust);

	y_adjust = print_side_mfd_system_message ("PNVS", "FAIL", comanche_damage.pnvs, y_adjust);

	y_adjust = print_side_mfd_system_message ("STABILISER", "FAIL", get_dynamics_damage_type (DYNAMICS_DAMAGE_STABILISER), y_adjust);

	y_adjust = print_side_mfd_system_message ("MAIN ROTOR", "DMGD", get_dynamics_damage_type (DYNAMICS_DAMAGE_MAIN_ROTOR), y_adjust);

	y_adjust = print_side_mfd_system_message ("TAIL ROTOR", "DMGD", get_dynamics_damage_type (DYNAMICS_DAMAGE_TAIL_ROTOR), y_adjust);

	y_adjust = print_side_mfd_system_message ("L ENGINE", "DMGD", get_dynamics_damage_type (DYNAMICS_DAMAGE_LEFT_ENGINE), y_adjust);

	y_adjust = print_side_mfd_system_message ("APU", "DMGD", FALSE, y_adjust);

	y_adjust = print_side_mfd_system_message ("R ENGINE", "DMGD", get_dynamics_damage_type (DYNAMICS_DAMAGE_RIGHT_ENGINE), y_adjust);

	y_adjust = print_side_mfd_system_message ("HYD PRESS", "LOW", get_dynamics_damage_type (DYNAMICS_DAMAGE_LOW_HYDRAULICS), y_adjust);

	if (get_dynamics_damage_type (DYNAMICS_DAMAGE_LOW_OIL_PRESSURE))
	{
		y_adjust = print_side_mfd_system_message ("OIL PRESS", "LOW", get_dynamics_damage_type (DYNAMICS_DAMAGE_LOW_OIL_PRESSURE), y_adjust);
	}
	else
	{
		y_adjust = print_side_mfd_system_message ("OIL PRESS", "HIGH", get_dynamics_damage_type (DYNAMICS_DAMAGE_HIGH_OIL_PRESSURE), y_adjust);
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

static void draw_engine_display_mfd (void)
{
	char
		s[80];

	int
		x1,
		y1,
		x2,
		y2,
		ivalue;

	float
		x_adjust,
		fvalue;

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

	set_2d_mono_font_position (-0.8, 0.9);

	set_mono_font_rel_position (1.0, 0.0);

	print_mono_font_string ("L ENGINE");

	set_2d_mono_font_position (0.8, 0.9);

	x_adjust = -get_mono_font_string_width ("R ENGINE");

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string ("R ENGINE");

	////////////////////////////////////////

	set_2d_mono_font_position (0.0, -0.6);

	x_adjust = get_mono_font_string_width ("FUEL QTY") * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string ("FUEL QTY");

	set_2d_mono_font_position (0.0, -0.7);

	x_adjust = get_mono_font_string_width ("LB") * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string ("LB");

	set_2d_mono_font_position (0.0, -0.8);

	fvalue = bound (kilograms_to_pounds (current_flight_dynamics->fuel_weight.value), 0.0, 9999.0);

	convert_float_to_int (fvalue, &ivalue);

	sprintf (s, "%04d", ivalue);

	x_adjust = get_mono_font_string_width (s) * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string (s);

	////////////////////////////////////////

	draw_2d_line (-0.8000 - 0.00, 0.3333, -0.7500 + 0.02, 0.3333, MFD_COLOUR1);
	draw_2d_line (-0.6500 - 0.02, 0.3333, -0.4500 + 0.02, 0.3333, MFD_COLOUR1);
	draw_2d_line (-0.3500 - 0.02, 0.3333, -0.2500 + 0.02, 0.3333, MFD_COLOUR1);
	draw_2d_line (-0.1500 - 0.02, 0.3333, -0.0500 + 0.02, 0.3333, MFD_COLOUR1);

	draw_2d_line ( 0.8000 + 0.00, 0.3333,  0.7500 - 0.02, 0.3333, MFD_COLOUR1);
	draw_2d_line ( 0.6500 + 0.02, 0.3333,  0.4500 - 0.02, 0.3333, MFD_COLOUR1);
	draw_2d_line ( 0.3500 + 0.02, 0.3333,  0.2500 - 0.02, 0.3333, MFD_COLOUR1);
	draw_2d_line ( 0.1500 + 0.02, 0.3333,  0.0500 - 0.02, 0.3333, MFD_COLOUR1);

	////////////////////////////////////////

	//
	// Nr
	//

	#define X_ORG	((float) (0.0))
	#define Y_ORG	((float) (0.5))
	#define WIDTH	((float) (0.06))
	#define HEIGHT	((float) (1.0))

	set_2d_mono_font_position (X_ORG, Y_ORG + 0.2);

	x_adjust = get_mono_font_string_width ("NR") * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string ("NR");

	////////////////////////////////////////

	fvalue = bound (current_flight_dynamics->main_rotor_rpm.value, 0.0, 120.0);

	convert_float_to_int (fvalue, &ivalue);

	sprintf (s, "%03d", ivalue);

	set_2d_mono_font_position (X_ORG, Y_ORG + 0.1);

	x_adjust = get_mono_font_string_width (s) * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string (s);

	////////////////////////////////////////

	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG, X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);
	draw_2d_line (X_ORG + (WIDTH * 0.5), Y_ORG, X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);
	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG, X_ORG + (WIDTH * 0.5), Y_ORG, MFD_COLOUR1);
	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT, X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);

	get_2d_int_screen_coordinates (X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT + (fvalue * (HEIGHT / 120.0)), &x1, &y1);
	get_2d_int_screen_coordinates (X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, &x2, &y2);
	set_block (x1, y1, x2, y2, MFD_COLOUR1);

	#undef X_ORG
	#undef Y_ORG
	#undef WIDTH
	#undef HEIGHT

	//
	// Np1
	//

	#define X_ORG	((float) (-0.2))
	#define Y_ORG	((float) (0.5))
	#define WIDTH	((float)	(0.06))
	#define HEIGHT	((float) (1.0))

	set_2d_mono_font_position (X_ORG, Y_ORG + 0.2);

	x_adjust = get_mono_font_string_width ("NP") * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string ("NP");

	////////////////////////////////////////

	fvalue = bound (current_flight_dynamics->left_engine_rpm.value, 0.0, 120.0);

	convert_float_to_int (fvalue, &ivalue);

	sprintf (s, "%03d", ivalue);

	set_2d_mono_font_position (X_ORG, Y_ORG + 0.1);

	x_adjust = get_mono_font_string_width (s) * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string (s);

	////////////////////////////////////////

	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG, X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);
	draw_2d_line (X_ORG + (WIDTH * 0.5), Y_ORG, X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);
	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG, X_ORG + (WIDTH * 0.5), Y_ORG, MFD_COLOUR1);
	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT, X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);

	get_2d_int_screen_coordinates (X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT + (fvalue * (HEIGHT / 120.0)), &x1, &y1);
	get_2d_int_screen_coordinates (X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, &x2, &y2);
	set_block (x1, y1, x2, y2, MFD_COLOUR1);

	#undef X_ORG
	#undef Y_ORG
	#undef WIDTH
	#undef HEIGHT

	//
	// Np2
	//

	#define X_ORG	((float) (0.2))
	#define Y_ORG	((float) (0.5))
	#define WIDTH	((float) (0.06))
	#define HEIGHT	((float) (1.0))

	set_2d_mono_font_position (X_ORG, Y_ORG + 0.2);

	x_adjust = get_mono_font_string_width ("NP") * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string ("NP");

	////////////////////////////////////////

	fvalue = bound (current_flight_dynamics->right_engine_rpm.value, 0.0, 120.0);

	convert_float_to_int (fvalue, &ivalue);

	sprintf (s, "%03d", ivalue);

	set_2d_mono_font_position (X_ORG, Y_ORG + 0.1);

	x_adjust = get_mono_font_string_width (s) * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string (s);

	////////////////////////////////////////

	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG, X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);
	draw_2d_line (X_ORG + (WIDTH * 0.5), Y_ORG, X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);
	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG, X_ORG + (WIDTH * 0.5), Y_ORG, MFD_COLOUR1);
	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT, X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);

	get_2d_int_screen_coordinates (X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT + (fvalue * (HEIGHT / 120.0)), &x1, &y1);
	get_2d_int_screen_coordinates (X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, &x2, &y2);
	set_block (x1, y1, x2, y2, MFD_COLOUR1);

	#undef X_ORG
	#undef Y_ORG
	#undef WIDTH
	#undef HEIGHT

	//
	// TQ1
	//

	#define X_ORG	((float) (-0.4))
	#define Y_ORG	((float) (0.5))
	#define WIDTH	((float) (0.06))
	#define HEIGHT	((float) (1.0))

	set_2d_mono_font_position (X_ORG, Y_ORG + 0.2);

	x_adjust = get_mono_font_string_width ("TQ") * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string ("TQ");

	////////////////////////////////////////

	fvalue = bound (current_flight_dynamics->left_engine_torque.value, 0.0, 120.0);

	convert_float_to_int (fvalue, &ivalue);

	sprintf (s, "%03d", ivalue);

	set_2d_mono_font_position (X_ORG, Y_ORG + 0.1);

	x_adjust = get_mono_font_string_width (s) * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string (s);

	////////////////////////////////////////

	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG, X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);
	draw_2d_line (X_ORG + (WIDTH * 0.5), Y_ORG, X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);
	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG, X_ORG + (WIDTH * 0.5), Y_ORG, MFD_COLOUR1);
	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT, X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);

	get_2d_int_screen_coordinates (X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT + (fvalue * (HEIGHT / 120.0)), &x1, &y1);
	get_2d_int_screen_coordinates (X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, &x2, &y2);
	set_block (x1, y1, x2, y2, MFD_COLOUR1);

	#undef X_ORG
	#undef Y_ORG
	#undef WIDTH
	#undef HEIGHT

	//
	// TQ2
	//

	#define X_ORG	((float) (0.4))
	#define Y_ORG	((float) (0.5))
	#define WIDTH	((float) (0.06))
	#define HEIGHT	((float) (1.0))

	set_2d_mono_font_position (X_ORG, Y_ORG + 0.2);

	x_adjust = get_mono_font_string_width ("TQ") * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string ("TQ");

	////////////////////////////////////////

	fvalue = bound (current_flight_dynamics->right_engine_torque.value, 0.0, 120.0);

	convert_float_to_int (fvalue, &ivalue);

	sprintf (s, "%03d", ivalue);

	set_2d_mono_font_position (X_ORG, Y_ORG + 0.1);

	x_adjust = get_mono_font_string_width (s) * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string (s);

	////////////////////////////////////////

	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG, X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);
	draw_2d_line (X_ORG + (WIDTH * 0.5), Y_ORG, X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);
	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG, X_ORG + (WIDTH * 0.5), Y_ORG, MFD_COLOUR1);
	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT, X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);

	get_2d_int_screen_coordinates (X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT + (fvalue * (HEIGHT / 120.0)), &x1, &y1);
	get_2d_int_screen_coordinates (X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, &x2, &y2);
	set_block (x1, y1, x2, y2, MFD_COLOUR1);

	#undef X_ORG
	#undef Y_ORG
	#undef WIDTH
	#undef HEIGHT

	//
	// TGT1
	//

	#define X_ORG	((float) (-0.7))
	#define Y_ORG	((float) (0.5))
	#define WIDTH	((float) (0.06))
	#define HEIGHT	((float) (0.8333))

	set_2d_mono_font_position (X_ORG, Y_ORG + 0.2);

	x_adjust = get_mono_font_string_width ("TG") * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string ("TG");

	////////////////////////////////////////

	fvalue = bound (current_flight_dynamics->left_engine_temp.value, 0.0, 999.0);

	convert_float_to_int (fvalue, &ivalue);

	sprintf (s, "%03d", ivalue);

	set_2d_mono_font_position (X_ORG, Y_ORG + 0.1);

	x_adjust = get_mono_font_string_width (s) * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string (s);

	////////////////////////////////////////

	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG, X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);
	draw_2d_line (X_ORG + (WIDTH * 0.5), Y_ORG, X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);
	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG, X_ORG + (WIDTH * 0.5), Y_ORG, MFD_COLOUR1);
	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT, X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);

	get_2d_int_screen_coordinates (X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT + (fvalue * (HEIGHT / 999.0)), &x1, &y1);
	get_2d_int_screen_coordinates (X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, &x2, &y2);
	set_block (x1, y1, x2, y2, MFD_COLOUR1);

	#undef X_ORG
	#undef Y_ORG
	#undef WIDTH
	#undef HEIGHT

	//
	// TGT2
	//

	#define X_ORG	((float) (0.7))
	#define Y_ORG	((float) (0.5))
	#define WIDTH	((float) (0.06))
	#define HEIGHT	((float) (0.8333))

	set_2d_mono_font_position (X_ORG, Y_ORG + 0.2);

	x_adjust = get_mono_font_string_width ("TG") * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string ("TG");

	////////////////////////////////////////

	fvalue = bound (current_flight_dynamics->right_engine_temp.value, 0.0, 999.0);

	convert_float_to_int (fvalue, &ivalue);

	sprintf (s, "%03d", ivalue);

	set_2d_mono_font_position (X_ORG, Y_ORG + 0.1);

	x_adjust = get_mono_font_string_width (s) * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string (s);

	////////////////////////////////////////

	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG, X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);
	draw_2d_line (X_ORG + (WIDTH * 0.5), Y_ORG, X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);
	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG, X_ORG + (WIDTH * 0.5), Y_ORG, MFD_COLOUR1);
	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT, X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);

	get_2d_int_screen_coordinates (X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT + (fvalue * (HEIGHT / 999.0)), &x1, &y1);
	get_2d_int_screen_coordinates (X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, &x2, &y2);
	set_block (x1, y1, x2, y2, MFD_COLOUR1);

	#undef X_ORG
	#undef Y_ORG
	#undef WIDTH
	#undef HEIGHT
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_engine_display_side_mfd (void)
{
	char
		s[80];

	int
		x1,
		y1,
		x2,
		y2,
		ivalue;

	float
		x_adjust,
		fvalue;

	set_mono_font_colour (MFD_COLOUR1);

	if (draw_large_mfd)
	{
		set_mono_font_type (MONO_FONT_TYPE_5X9);
	}
	else
	{
		set_mono_font_type (MONO_FONT_TYPE_3X6);
	}

	////////////////////////////////////////

	set_2d_mono_font_position (-0.6 - 0.4, 0.9);

	set_mono_font_rel_position (1.0, 0.0);

	print_mono_font_string ("L ENGINE");

	set_2d_mono_font_position (0.6 - 0.4, 0.9);

	x_adjust = -get_mono_font_string_width ("R ENGINE");

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string ("R ENGINE");

	////////////////////////////////////////

	set_2d_mono_font_position (0.0 - 0.4, -0.6);

	x_adjust = get_mono_font_string_width ("FUEL QTY") * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string ("FUEL QTY");

	set_2d_mono_font_position (0.0 - 0.4, -0.7);

	x_adjust = get_mono_font_string_width ("LB") * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string ("LB");

	set_2d_mono_font_position (0.0 - 0.4, -0.8);

	fvalue = bound (kilograms_to_pounds (current_flight_dynamics->fuel_weight.value), 0.0, 9999.0);

	convert_float_to_int (fvalue, &ivalue);

	sprintf (s, "%04d", ivalue);

	x_adjust = get_mono_font_string_width (s) * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string (s);

	////////////////////////////////////////

	draw_2d_line (-0.6000 - 0.000 - 0.4, 0.3333, -0.5500 + 0.015 - 0.4, 0.3333, MFD_COLOUR1);
	draw_2d_line (-0.4750 - 0.015 - 0.4, 0.3333, -0.3792 + 0.015 - 0.4, 0.3333, MFD_COLOUR1);
	draw_2d_line (-0.3042 - 0.015 - 0.4, 0.3333, -0.2083 + 0.015 - 0.4, 0.3333, MFD_COLOUR1);
	draw_2d_line (-0.1333 - 0.015 - 0.4, 0.3333, -0.0375 + 0.015 - 0.4, 0.3333, MFD_COLOUR1);

	draw_2d_line ( 0.6000 + 0.000 - 0.4, 0.3333,  0.5500 - 0.015 - 0.4, 0.3333, MFD_COLOUR1);
	draw_2d_line ( 0.4750 + 0.015 - 0.4, 0.3333,  0.3792 - 0.015 - 0.4, 0.3333, MFD_COLOUR1);
	draw_2d_line ( 0.3042 + 0.015 - 0.4, 0.3333,  0.2083 - 0.015 - 0.4, 0.3333, MFD_COLOUR1);
	draw_2d_line ( 0.1333 + 0.015 - 0.4, 0.3333,  0.0375 - 0.015 - 0.4, 0.3333, MFD_COLOUR1);

	////////////////////////////////////////

	//
	// Nr
	//

	#define X_ORG	((float) (0.0 - 0.4))
	#define Y_ORG	((float) (0.5))
	#define WIDTH	((float) (0.045))
	#define HEIGHT	((float) (1.0))

	set_2d_mono_font_position (X_ORG, Y_ORG + 0.2);

	x_adjust = get_mono_font_string_width ("NR") * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string ("NR");

	////////////////////////////////////////

	fvalue = bound (current_flight_dynamics->main_rotor_rpm.value, 0.0, 120.0);

	convert_float_to_int (fvalue, &ivalue);

	sprintf (s, "%03d", ivalue);

	set_2d_mono_font_position (X_ORG, Y_ORG + 0.1);

	x_adjust = get_mono_font_string_width (s) * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string (s);

	////////////////////////////////////////

	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG, X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);
	draw_2d_line (X_ORG + (WIDTH * 0.5), Y_ORG, X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);
	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG, X_ORG + (WIDTH * 0.5), Y_ORG, MFD_COLOUR1);
	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT, X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);

	get_2d_int_screen_coordinates (X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT + (fvalue * (HEIGHT / 120.0)), &x1, &y1);
	get_2d_int_screen_coordinates (X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, &x2, &y2);
	set_block (x1, y1, x2, y2, MFD_COLOUR1);

	#undef X_ORG
	#undef Y_ORG
	#undef WIDTH
	#undef HEIGHT

	//
	// Np1
	//

	#define X_ORG	((float) (-0.1708 - 0.4))
	#define Y_ORG	((float) (0.5))
	#define WIDTH	((float) (0.045))
	#define HEIGHT	((float) (1.0))

	set_2d_mono_font_position (X_ORG, Y_ORG + 0.2);

	x_adjust = get_mono_font_string_width ("NP") * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string ("NP");

	////////////////////////////////////////

	fvalue = bound (current_flight_dynamics->left_engine_rpm.value, 0.0, 120.0);

	convert_float_to_int (fvalue, &ivalue);

	sprintf (s, "%03d", ivalue);

	set_2d_mono_font_position (X_ORG, Y_ORG + 0.1);

	x_adjust = get_mono_font_string_width (s) * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string (s);

	////////////////////////////////////////

	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG, X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);
	draw_2d_line (X_ORG + (WIDTH * 0.5), Y_ORG, X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);
	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG, X_ORG + (WIDTH * 0.5), Y_ORG, MFD_COLOUR1);
	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT, X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);

	get_2d_int_screen_coordinates (X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT + (fvalue * (HEIGHT / 120.0)), &x1, &y1);
	get_2d_int_screen_coordinates (X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, &x2, &y2);
	set_block (x1, y1, x2, y2, MFD_COLOUR1);

	#undef X_ORG
	#undef Y_ORG
	#undef WIDTH
	#undef HEIGHT

	//
	// Np2
	//

	#define X_ORG	((float) (0.1708 - 0.4))
	#define Y_ORG	((float) (0.5))
	#define WIDTH	((float) (0.045))
	#define HEIGHT	((float) (1.0))

	set_2d_mono_font_position (X_ORG, Y_ORG + 0.2);

	x_adjust = get_mono_font_string_width ("NP") * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string ("NP");

	////////////////////////////////////////

	fvalue = bound (current_flight_dynamics->right_engine_rpm.value, 0.0, 120.0);

	convert_float_to_int (fvalue, &ivalue);

	sprintf (s, "%03d", ivalue);

	set_2d_mono_font_position (X_ORG, Y_ORG + 0.1);

	x_adjust = get_mono_font_string_width (s) * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string (s);

	////////////////////////////////////////

	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG, X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);
	draw_2d_line (X_ORG + (WIDTH * 0.5), Y_ORG, X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);
	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG, X_ORG + (WIDTH * 0.5), Y_ORG, MFD_COLOUR1);
	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT, X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);

	get_2d_int_screen_coordinates (X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT + (fvalue * (HEIGHT / 120.0)), &x1, &y1);
	get_2d_int_screen_coordinates (X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, &x2, &y2);
	set_block (x1, y1, x2, y2, MFD_COLOUR1);

	#undef X_ORG
	#undef Y_ORG
	#undef WIDTH
	#undef HEIGHT

	//
	// TQ1
	//

	#define X_ORG	((float) (-0.3417 - 0.4))
	#define Y_ORG	((float) (0.5))
	#define WIDTH	((float) (0.045))
	#define HEIGHT	((float) (1.0))

	set_2d_mono_font_position (X_ORG, Y_ORG + 0.2);

	x_adjust = get_mono_font_string_width ("TQ") * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string ("TQ");

	////////////////////////////////////////

	fvalue = bound (current_flight_dynamics->left_engine_torque.value, 0.0, 120.0);

	convert_float_to_int (fvalue, &ivalue);

	sprintf (s, "%03d", ivalue);

	set_2d_mono_font_position (X_ORG, Y_ORG + 0.1);

	x_adjust = get_mono_font_string_width (s) * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string (s);

	////////////////////////////////////////

	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG, X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);
	draw_2d_line (X_ORG + (WIDTH * 0.5), Y_ORG, X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);
	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG, X_ORG + (WIDTH * 0.5), Y_ORG, MFD_COLOUR1);
	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT, X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);

	get_2d_int_screen_coordinates (X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT + (fvalue * (HEIGHT / 120.0)), &x1, &y1);
	get_2d_int_screen_coordinates (X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, &x2, &y2);
	set_block (x1, y1, x2, y2, MFD_COLOUR1);

	#undef X_ORG
	#undef Y_ORG
	#undef WIDTH
	#undef HEIGHT

	//
	// TQ2
	//

	#define X_ORG	((float) (0.3417 - 0.4))
	#define Y_ORG	((float) (0.5))
	#define WIDTH	((float) (0.045))
	#define HEIGHT	((float) (1.0))

	set_2d_mono_font_position (X_ORG, Y_ORG + 0.2);

	x_adjust = get_mono_font_string_width ("TQ") * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string ("TQ");

	////////////////////////////////////////

	fvalue = bound (current_flight_dynamics->right_engine_torque.value, 0.0, 120.0);

	convert_float_to_int (fvalue, &ivalue);

	sprintf (s, "%03d", ivalue);

	set_2d_mono_font_position (X_ORG, Y_ORG + 0.1);

	x_adjust = get_mono_font_string_width (s) * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string (s);

	////////////////////////////////////////

	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG, X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);
	draw_2d_line (X_ORG + (WIDTH * 0.5), Y_ORG, X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);
	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG, X_ORG + (WIDTH * 0.5), Y_ORG, MFD_COLOUR1);
	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT, X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);

	get_2d_int_screen_coordinates (X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT + (fvalue * (HEIGHT / 120.0)), &x1, &y1);
	get_2d_int_screen_coordinates (X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, &x2, &y2);
	set_block (x1, y1, x2, y2, MFD_COLOUR1);

	#undef X_ORG
	#undef Y_ORG
	#undef WIDTH
	#undef HEIGHT

	//
	// TGT1
	//

	#define X_ORG	((float) (-0.5125 - 0.4))
	#define Y_ORG	((float) (0.5))
	#define WIDTH	((float) (0.045))
	#define HEIGHT	((float) (0.8333))

	set_2d_mono_font_position (X_ORG, Y_ORG + 0.2);

	x_adjust = get_mono_font_string_width ("TG") * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string ("TG");

	////////////////////////////////////////

	fvalue = bound (current_flight_dynamics->left_engine_temp.value, 0.0, 999.0);

	convert_float_to_int (fvalue, &ivalue);

	sprintf (s, "%03d", ivalue);

	set_2d_mono_font_position (X_ORG, Y_ORG + 0.1);

	x_adjust = get_mono_font_string_width (s) * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string (s);

	////////////////////////////////////////

	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG, X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);
	draw_2d_line (X_ORG + (WIDTH * 0.5), Y_ORG, X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);
	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG, X_ORG + (WIDTH * 0.5), Y_ORG, MFD_COLOUR1);
	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT, X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);

	get_2d_int_screen_coordinates (X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT + (fvalue * (HEIGHT / 999.0)), &x1, &y1);
	get_2d_int_screen_coordinates (X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, &x2, &y2);
	set_block (x1, y1, x2, y2, MFD_COLOUR1);

	#undef X_ORG
	#undef Y_ORG
	#undef WIDTH
	#undef HEIGHT

	//
	// TGT2
	//

	#define X_ORG	((float) (0.5125 - 0.4))
	#define Y_ORG	((float) (0.5))
	#define WIDTH	((float) (0.045))
	#define HEIGHT	((float) (0.8333))

	set_2d_mono_font_position (X_ORG, Y_ORG + 0.2);

	x_adjust = get_mono_font_string_width ("TG") * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string ("TG");

	////////////////////////////////////////

	fvalue = bound (current_flight_dynamics->right_engine_temp.value, 0.0, 999.0);

	convert_float_to_int (fvalue, &ivalue);

	sprintf (s, "%03d", ivalue);

	set_2d_mono_font_position (X_ORG, Y_ORG + 0.1);

	x_adjust = get_mono_font_string_width (s) * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string (s);

	////////////////////////////////////////

	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG, X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);
	draw_2d_line (X_ORG + (WIDTH * 0.5), Y_ORG, X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);
	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG, X_ORG + (WIDTH * 0.5), Y_ORG, MFD_COLOUR1);
	draw_2d_line (X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT, X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, MFD_COLOUR1);

	get_2d_int_screen_coordinates (X_ORG - (WIDTH * 0.5), Y_ORG - HEIGHT + (fvalue * (HEIGHT / 999.0)), &x1, &y1);
	get_2d_int_screen_coordinates (X_ORG + (WIDTH * 0.5), Y_ORG - HEIGHT, &x2, &y2);
	set_block (x1, y1, x2, y2, MFD_COLOUR1);

	#undef X_ORG
	#undef Y_ORG
	#undef WIDTH
	#undef HEIGHT
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

#define PITCH_DATUM_X	(x_centre)
#define PITCH_DATUM_Y	((float) 0.2)

//									P9 O (+ve)
//
//
//    P1    P2    P3    P4    P5    P6    P7
//     O-----O-----O-----O-----O-----O-----O
//     |
//     |
//     |
// P8  O					 	   P10 O (-ve)

#define PITCH_BAR_X1		((float) (+0.125) * pitch_bar_scale)
#define PITCH_BAR_Y1		((float) (+0.000) * pitch_bar_scale)
#define PITCH_BAR_X2		((float) (+0.160) * pitch_bar_scale)
#define PITCH_BAR_Y2		((float) (+0.000) * pitch_bar_scale)
#define PITCH_BAR_X3		((float) (+0.195) * pitch_bar_scale)
#define PITCH_BAR_Y3		((float) (+0.000) * pitch_bar_scale)
#define PITCH_BAR_X4		((float) (+0.230) * pitch_bar_scale)
#define PITCH_BAR_Y4		((float) (+0.000) * pitch_bar_scale)
#define PITCH_BAR_X5		((float) (+0.265) * pitch_bar_scale)
#define PITCH_BAR_Y5		((float) (+0.000) * pitch_bar_scale)
#define PITCH_BAR_X6		((float) (+0.300) * pitch_bar_scale)
#define PITCH_BAR_Y6		((float) (+0.000) * pitch_bar_scale)
#define PITCH_BAR_X7		((float) (+0.335) * pitch_bar_scale)
#define PITCH_BAR_Y7		((float) (+0.000) * pitch_bar_scale)
#define PITCH_BAR_X8		((float) (+0.125) * pitch_bar_scale)
#define PITCH_BAR_Y8		((float) (-0.050) * pitch_bar_scale)
#define PITCH_BAR_X9		((float) (+0.265) * pitch_bar_scale)
#define PITCH_BAR_Y9		((float) (+0.050) * pitch_bar_scale)
#define PITCH_BAR_X10	((float) (+0.265) * pitch_bar_scale)
#define PITCH_BAR_Y10	((float) (-0.050) * pitch_bar_scale)

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
		x_centre,
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

	if (draw_main_display)
	{
		x_centre = 0.0;

		size = 0.4;

		pitch_bar_scale = 1.0;
	}
	else
	{
		x_centre = -0.4;

		size = 0.3;

		pitch_bar_scale = 0.3 / 0.4;
	}

	//
	// draw semi-circle (circle with top half cleared)
	//

	draw_2d_circle (PITCH_DATUM_X + 0.0, PITCH_DATUM_Y - size, size, MFD_COLOUR1);

	get_2d_int_screen_coordinates (PITCH_DATUM_X - size, PITCH_DATUM_Y + size, &x1, &y1);
	get_2d_int_screen_coordinates (PITCH_DATUM_X + size, PITCH_DATUM_Y - size, &x2, &y2);

	set_block (x1, y1, x2, y2, MFD_BACKGROUND_COLOUR);

	//
	// box
	//

	draw_2d_line (PITCH_DATUM_X - size, PITCH_DATUM_Y + size, PITCH_DATUM_X + size, PITCH_DATUM_Y + size, MFD_COLOUR1);
	draw_2d_line (PITCH_DATUM_X - size, PITCH_DATUM_Y + size, PITCH_DATUM_X - size, PITCH_DATUM_Y - size, MFD_COLOUR1);
	draw_2d_line (PITCH_DATUM_X + size, PITCH_DATUM_Y + size, PITCH_DATUM_X + size, PITCH_DATUM_Y - size, MFD_COLOUR1);

	//
	// datum
	//

	get_2d_float_screen_coordinates (PITCH_DATUM_X, PITCH_DATUM_Y, &u, &v);

	if (draw_large_mfd)
	{
		draw_line (u, v + 2.0, u, v + 5.0, MFD_COLOUR1);
		draw_line (u, v - 2.0, u, v - 5.0, MFD_COLOUR1);
		draw_line (u + 2.0, v, u + 5.0, v, MFD_COLOUR1);
		draw_line (u - 2.0, v, u - 5.0, v, MFD_COLOUR1);
	}
	else
	{
		draw_line (u, v + 1.0, u, v + 2.0, MFD_COLOUR1);
		draw_line (u, v - 1.0, u, v - 2.0, MFD_COLOUR1);
		draw_line (u + 1.0, v, u + 2.0, v, MFD_COLOUR1);
		draw_line (u - 1.0, v, u - 2.0, v, MFD_COLOUR1);
	}

	//
	// roll
	//

	roll = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_ROLL);

	set_2d_instance_position (mfd_env, PITCH_DATUM_X, PITCH_DATUM_Y - size);

	set_2d_instance_rotation (mfd_env, rad (0.0));
	draw_2d_line (0.0, -size, 0.0, -size - 0.05, MFD_COLOUR1);

	set_2d_instance_rotation (mfd_env, rad (10.0));
	draw_2d_line (0.0, -size, 0.0, -size - 0.025, MFD_COLOUR1);
	set_2d_instance_rotation (mfd_env, rad (-10.0));
	draw_2d_line (0.0, -size, 0.0, -size - 0.025, MFD_COLOUR1);

	set_2d_instance_rotation (mfd_env, rad (20.0));
	draw_2d_line (0.0, -size, 0.0, -size - 0.025, MFD_COLOUR1);
	set_2d_instance_rotation (mfd_env, rad (-20.0));
	draw_2d_line (0.0, -size, 0.0, -size - 0.025, MFD_COLOUR1);

	set_2d_instance_rotation (mfd_env, rad (30.0));
	draw_2d_line (0.0, -size, 0.0, -size - 0.05, MFD_COLOUR1);
	set_2d_instance_rotation (mfd_env, rad (-30.0));
	draw_2d_line (0.0, -size, 0.0, -size - 0.05, MFD_COLOUR1);

	set_2d_instance_rotation (mfd_env, bound (roll, rad (-30.0), rad (30.0)));
	draw_2d_line (0.0, -size + 0.075, 0.0, -size, MFD_COLOUR1);

	//
	// set 2D environment
	//

	set_2d_window (mfd_env, MFD_WINDOW_X_MIN * size, MFD_WINDOW_Y_MIN * size, MFD_WINDOW_X_MAX * size, MFD_WINDOW_Y_MAX * size);

	vp_size = mfd_viewport_size * size * 0.5;

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

	x_scale = -sin (roll) * 1.5 * pitch_bar_scale;

	y_scale = cos (roll) * 1.5 * pitch_bar_scale;

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
				draw_2d_line (+PITCH_BAR_X1, +PITCH_BAR_Y1, +PITCH_BAR_X7, +PITCH_BAR_Y7, MFD_COLOUR1);
				draw_2d_line (-PITCH_BAR_X1, +PITCH_BAR_Y1, -PITCH_BAR_X7, +PITCH_BAR_Y7, MFD_COLOUR1);

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

					draw_2d_line (+PITCH_BAR_X1, +PITCH_BAR_Y1, +PITCH_BAR_X8, +PITCH_BAR_Y8, MFD_COLOUR1);
					draw_2d_line (-PITCH_BAR_X1, +PITCH_BAR_Y1, -PITCH_BAR_X8, +PITCH_BAR_Y8, MFD_COLOUR1);
				}
				else
				{
					draw_2d_line (-PITCH_BAR_X1, -PITCH_BAR_Y1, -PITCH_BAR_X6, -PITCH_BAR_Y6, MFD_COLOUR1);
					draw_2d_line (+PITCH_BAR_X1, -PITCH_BAR_Y1, +PITCH_BAR_X6, -PITCH_BAR_Y6, MFD_COLOUR1);

					draw_2d_line (-PITCH_BAR_X1, -PITCH_BAR_Y1, -PITCH_BAR_X8, -PITCH_BAR_Y8, MFD_COLOUR1);
					draw_2d_line (+PITCH_BAR_X1, -PITCH_BAR_Y1, +PITCH_BAR_X8, -PITCH_BAR_Y8, MFD_COLOUR1);
				}

				sprintf (s, "%d0", int_pitch);

				x_adjust = get_mono_font_string_width (s) * -0.5;

				set_2d_mono_font_position (+PITCH_BAR_X9, +PITCH_BAR_Y9);

				set_mono_font_rel_position (x_adjust, y_adjust_above_line);

				print_mono_font_string (s);

				set_2d_mono_font_position (-PITCH_BAR_X9, +PITCH_BAR_Y9);

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
					draw_2d_line (+PITCH_BAR_X1, +PITCH_BAR_Y1, +PITCH_BAR_X2, +PITCH_BAR_Y2, MFD_COLOUR1);
					draw_2d_line (-PITCH_BAR_X1, +PITCH_BAR_Y1, -PITCH_BAR_X2, +PITCH_BAR_Y2, MFD_COLOUR1);

					draw_2d_line (+PITCH_BAR_X3, +PITCH_BAR_Y3, +PITCH_BAR_X4, +PITCH_BAR_Y4, MFD_COLOUR1);
					draw_2d_line (-PITCH_BAR_X3, +PITCH_BAR_Y3, -PITCH_BAR_X4, +PITCH_BAR_Y4, MFD_COLOUR1);

					draw_2d_line (+PITCH_BAR_X5, +PITCH_BAR_Y5, +PITCH_BAR_X6, +PITCH_BAR_Y6, MFD_COLOUR1);
					draw_2d_line (-PITCH_BAR_X5, +PITCH_BAR_Y5, -PITCH_BAR_X6, +PITCH_BAR_Y6, MFD_COLOUR1);

					draw_2d_line (+PITCH_BAR_X1, +PITCH_BAR_Y1, +PITCH_BAR_X8, +PITCH_BAR_Y8, MFD_COLOUR1);
					draw_2d_line (-PITCH_BAR_X1, +PITCH_BAR_Y1, -PITCH_BAR_X8, +PITCH_BAR_Y8, MFD_COLOUR1);
				}
				else
				{
					draw_2d_line (-PITCH_BAR_X1, -PITCH_BAR_Y1, -PITCH_BAR_X2, -PITCH_BAR_Y2, MFD_COLOUR1);
					draw_2d_line (+PITCH_BAR_X1, -PITCH_BAR_Y1, +PITCH_BAR_X2, -PITCH_BAR_Y2, MFD_COLOUR1);

					draw_2d_line (-PITCH_BAR_X3, -PITCH_BAR_Y3, -PITCH_BAR_X4, -PITCH_BAR_Y4, MFD_COLOUR1);
					draw_2d_line (+PITCH_BAR_X3, -PITCH_BAR_Y3, +PITCH_BAR_X4, -PITCH_BAR_Y4, MFD_COLOUR1);

					draw_2d_line (-PITCH_BAR_X5, -PITCH_BAR_Y5, -PITCH_BAR_X6, -PITCH_BAR_Y6, MFD_COLOUR1);
					draw_2d_line (+PITCH_BAR_X5, -PITCH_BAR_Y5, +PITCH_BAR_X6, -PITCH_BAR_Y6, MFD_COLOUR1);

					draw_2d_line (-PITCH_BAR_X1, -PITCH_BAR_Y1, -PITCH_BAR_X8, -PITCH_BAR_Y8, MFD_COLOUR1);
					draw_2d_line (+PITCH_BAR_X1, -PITCH_BAR_Y1, +PITCH_BAR_X8, -PITCH_BAR_Y8, MFD_COLOUR1);
				}

				sprintf (s, "%d0", int_pitch);

				x_adjust = get_mono_font_string_width (s) * -0.5;

				set_2d_mono_font_position (+PITCH_BAR_X10, +PITCH_BAR_Y10);

				set_mono_font_rel_position (x_adjust, y_adjust_below_line);

				print_mono_font_string (s);

				set_2d_mono_font_position (-PITCH_BAR_X10, +PITCH_BAR_Y10);

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

	true_airspeed = knots (true_airspeed);

	sprintf (s, "%d", (int) true_airspeed);

	set_2d_mono_font_position (-1.0, -0.1);

	if (draw_main_display)
	{
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
	}
	else
	{
		if (draw_large_mfd)
		{
			set_mono_font_type (MONO_FONT_TYPE_7X12);

			set_mono_font_rel_position (1.0, -4.0);
		}
		else
		{
			set_mono_font_type (MONO_FONT_TYPE_5X7);

			set_mono_font_rel_position (1.0, -2.0);
		}
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

	radar_altitude = feet (current_flight_dynamics->radar_altitude.value);

	if (radar_altitude <= 1500.0)
	{
		sprintf (s, "R%d", (int) radar_altitude);
	}
	else
	{
		barometric_altitude = feet (current_flight_dynamics->barometric_altitude.value);

		sprintf (s, "%d", (int) barometric_altitude);
	}

	width = get_mono_font_string_width (s);

	if (draw_main_display)
	{
		set_2d_mono_font_position (1.0, 0.6);

		if (draw_large_mfd)
		{
			set_mono_font_type (MONO_FONT_TYPE_7X12);

			set_mono_font_rel_position (-width - 2.0, -4.0);
		}
		else
		{
			set_mono_font_type (MONO_FONT_TYPE_5X9);

			set_mono_font_rel_position (-width - 1.0, -4.0);
		}
	}
	else
	{
		set_2d_mono_font_position (0.2, 0.6);

		if (draw_large_mfd)
		{
			set_mono_font_type (MONO_FONT_TYPE_7X12);

			set_mono_font_rel_position (-width - 2.0, -4.0);
		}
		else
		{
			set_mono_font_type (MONO_FONT_TYPE_5X7);

			set_mono_font_rel_position (-width - 1.0, -2.0);
		}
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

#define CLIMB_SCALE_FSD					((float) 0.6)

#define CLIMB_SCALE_MAJOR_TICK_X1	((float) (0.850) + x_adjust)
#define CLIMB_SCALE_MAJOR_TICK_X2	((float) (0.895) + x_adjust)
#define CLIMB_SCALE_MAJOR_TICK_X3	((float) (0.950) + x_adjust)
#define CLIMB_SCALE_MAJOR_TICK_X4	((float) (0.995) + x_adjust)

#define CLIMB_SCALE_MINOR_TICK_X1	((float) (0.857) + x_adjust)
#define CLIMB_SCALE_MINOR_TICK_X2	((float) (0.885) + x_adjust)
#define CLIMB_SCALE_MINOR_TICK_X3	((float) (0.957) + x_adjust)
#define CLIMB_SCALE_MINOR_TICK_X4	((float) (0.985) + x_adjust)

static char large_rate_of_climb_scale_pointer[] =
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

static char small_rate_of_climb_scale_pointer[] =
{
	3,
	5,
	-3,
	-2,
	1,0,0,
	1,1,0,
	1,1,1,
	1,1,0,
	1,0,0,
};

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
		x_adjust;

	if (draw_main_display)
	{
		x_adjust = -0.05;
	}
	else
	{
		x_adjust = -0.85;
	}

	//
	// draw scale
	//

	draw_2d_line (CLIMB_SCALE_MAJOR_TICK_X1, (CLIMB_SCALE_FSD * +1.0) - 0.1, CLIMB_SCALE_MAJOR_TICK_X2, (CLIMB_SCALE_FSD * +1.0) - 0.1, MFD_COLOUR1);
	draw_2d_line (CLIMB_SCALE_MAJOR_TICK_X3, (CLIMB_SCALE_FSD * +1.0) - 0.1, CLIMB_SCALE_MAJOR_TICK_X4, (CLIMB_SCALE_FSD * +1.0) - 0.1, MFD_COLOUR1);

	draw_2d_line (CLIMB_SCALE_MAJOR_TICK_X1, (CLIMB_SCALE_FSD * +0.5) - 0.1, CLIMB_SCALE_MAJOR_TICK_X2, (CLIMB_SCALE_FSD * +0.5) - 0.1, MFD_COLOUR1);
	draw_2d_line (CLIMB_SCALE_MAJOR_TICK_X3, (CLIMB_SCALE_FSD * +0.5) - 0.1, CLIMB_SCALE_MAJOR_TICK_X4, (CLIMB_SCALE_FSD * +0.5) - 0.1, MFD_COLOUR1);

	draw_2d_line (CLIMB_SCALE_MINOR_TICK_X1, (CLIMB_SCALE_FSD * +0.4) - 0.1, CLIMB_SCALE_MINOR_TICK_X2, (CLIMB_SCALE_FSD * +0.4) - 0.1, MFD_COLOUR1);

	draw_2d_line (CLIMB_SCALE_MINOR_TICK_X1, (CLIMB_SCALE_FSD * +0.3) - 0.1, CLIMB_SCALE_MINOR_TICK_X2, (CLIMB_SCALE_FSD * +0.3) - 0.1, MFD_COLOUR1);

	draw_2d_line (CLIMB_SCALE_MINOR_TICK_X1, (CLIMB_SCALE_FSD * +0.2) - 0.1, CLIMB_SCALE_MINOR_TICK_X2, (CLIMB_SCALE_FSD * +0.2) - 0.1, MFD_COLOUR1);

	draw_2d_line (CLIMB_SCALE_MINOR_TICK_X1, (CLIMB_SCALE_FSD * +0.1) - 0.1, CLIMB_SCALE_MINOR_TICK_X2, (CLIMB_SCALE_FSD * +0.1) - 0.1, MFD_COLOUR1);

	draw_2d_line (CLIMB_SCALE_MAJOR_TICK_X1, (CLIMB_SCALE_FSD * +0.0) - 0.1, CLIMB_SCALE_MAJOR_TICK_X2, (CLIMB_SCALE_FSD * +0.0) - 0.1, MFD_COLOUR1);
	draw_2d_line (CLIMB_SCALE_MAJOR_TICK_X3, (CLIMB_SCALE_FSD * +0.0) - 0.1, CLIMB_SCALE_MAJOR_TICK_X4, (CLIMB_SCALE_FSD * +0.0) - 0.1, MFD_COLOUR1);

	draw_2d_line (CLIMB_SCALE_MINOR_TICK_X1, (CLIMB_SCALE_FSD * -0.1) - 0.1, CLIMB_SCALE_MINOR_TICK_X2, (CLIMB_SCALE_FSD * -0.1) - 0.1, MFD_COLOUR1);

	draw_2d_line (CLIMB_SCALE_MINOR_TICK_X1, (CLIMB_SCALE_FSD * -0.2) - 0.1, CLIMB_SCALE_MINOR_TICK_X2, (CLIMB_SCALE_FSD * -0.2) - 0.1, MFD_COLOUR1);

	draw_2d_line (CLIMB_SCALE_MINOR_TICK_X1, (CLIMB_SCALE_FSD * -0.3) - 0.1, CLIMB_SCALE_MINOR_TICK_X2, (CLIMB_SCALE_FSD * -0.3) - 0.1, MFD_COLOUR1);

	draw_2d_line (CLIMB_SCALE_MINOR_TICK_X1, (CLIMB_SCALE_FSD * -0.4) - 0.1, CLIMB_SCALE_MINOR_TICK_X2, (CLIMB_SCALE_FSD * -0.4) - 0.1, MFD_COLOUR1);

	draw_2d_line (CLIMB_SCALE_MAJOR_TICK_X1, (CLIMB_SCALE_FSD * -0.5) - 0.1, CLIMB_SCALE_MAJOR_TICK_X2, (CLIMB_SCALE_FSD * -0.5) - 0.1, MFD_COLOUR1);
	draw_2d_line (CLIMB_SCALE_MAJOR_TICK_X3, (CLIMB_SCALE_FSD * -0.5) - 0.1, CLIMB_SCALE_MAJOR_TICK_X4, (CLIMB_SCALE_FSD * -0.5) - 0.1, MFD_COLOUR1);

	draw_2d_line (CLIMB_SCALE_MINOR_TICK_X3, (CLIMB_SCALE_FSD * -0.6) - 0.1, CLIMB_SCALE_MINOR_TICK_X4, (CLIMB_SCALE_FSD * -0.6) - 0.1, MFD_COLOUR1);

	draw_2d_line (CLIMB_SCALE_MINOR_TICK_X3, (CLIMB_SCALE_FSD * -0.7) - 0.1, CLIMB_SCALE_MINOR_TICK_X4, (CLIMB_SCALE_FSD * -0.7) - 0.1, MFD_COLOUR1);

	draw_2d_line (CLIMB_SCALE_MINOR_TICK_X3, (CLIMB_SCALE_FSD * -0.8) - 0.1, CLIMB_SCALE_MINOR_TICK_X4, (CLIMB_SCALE_FSD * -0.8) - 0.1, MFD_COLOUR1);

	draw_2d_line (CLIMB_SCALE_MINOR_TICK_X3, (CLIMB_SCALE_FSD * -0.9) - 0.1, CLIMB_SCALE_MINOR_TICK_X4, (CLIMB_SCALE_FSD * -0.9) - 0.1, MFD_COLOUR1);

	draw_2d_line (CLIMB_SCALE_MAJOR_TICK_X1, (CLIMB_SCALE_FSD * -1.0) - 0.1, CLIMB_SCALE_MAJOR_TICK_X2, (CLIMB_SCALE_FSD * -1.0) - 0.1, MFD_COLOUR1);
	draw_2d_line (CLIMB_SCALE_MAJOR_TICK_X3, (CLIMB_SCALE_FSD * -1.0) - 0.1, CLIMB_SCALE_MAJOR_TICK_X4, (CLIMB_SCALE_FSD * -1.0) - 0.1, MFD_COLOUR1);

	//
	// display analogue radar altitude
	//

	radar_altitude = feet (current_flight_dynamics->radar_altitude.value);

	if (radar_altitude <= 200.0)
	{
		y1 = -CLIMB_SCALE_FSD - 0.1;

		y2 = -CLIMB_SCALE_FSD - 0.1 + radar_altitude * ((CLIMB_SCALE_FSD * 2.0) / 200.0);

		get_2d_float_screen_coordinates (CLIMB_SCALE_MAJOR_TICK_X2, y1, &x, &y1);

		get_2d_float_screen_coordinates (CLIMB_SCALE_MAJOR_TICK_X2, y2, &x, &y2);

		if (draw_large_mfd)
		{
			draw_line (x + 1.0, y1, x + 1.0, y2, MFD_COLOUR1);
			draw_line (x + 2.0, y1, x + 2.0, y2, MFD_COLOUR1);
			draw_line (x + 3.0, y1, x + 3.0, y2, MFD_COLOUR1);
			draw_line (x + 4.0, y1, x + 4.0, y2, MFD_COLOUR1);
			draw_line (x + 5.0, y1, x + 5.0, y2, MFD_COLOUR1);
			draw_line (x + 6.0, y1, x + 6.0, y2, MFD_COLOUR1);
		}
		else
		{
			draw_line (x + 1.0, y1, x + 1.0, y2, MFD_COLOUR1);
			draw_line (x + 2.0, y1, x + 2.0, y2, MFD_COLOUR1);
			draw_line (x + 3.0, y1, x + 3.0, y2, MFD_COLOUR1);
		}
	}

	//
	// draw rate of climb scale pointer
	//

	rate_of_climb = current_flight_dynamics->world_velocity_y.value;

	rate_of_climb = feet_per_minute (rate_of_climb);

	rate_of_climb = bound (rate_of_climb, -1000.0, 1000.0);

	x = CLIMB_SCALE_MAJOR_TICK_X1;

	y = rate_of_climb * (CLIMB_SCALE_FSD / 1000.0) - 0.1;

	if (draw_large_mfd)
	{
		draw_2d_mono_sprite (large_rate_of_climb_scale_pointer, x, y, MFD_COLOUR1);
	}
	else
	{
		draw_2d_mono_sprite (small_rate_of_climb_scale_pointer, x, y, MFD_COLOUR1);
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

	set_2d_mono_font_position (-1.0, 0.6);

	if (draw_main_display)
	{
		if (draw_large_mfd)
		{
			set_mono_font_type (MONO_FONT_TYPE_7X12);

			set_mono_font_rel_position (1.0, -4.0);
		}
		else
		{
			set_mono_font_type (MONO_FONT_TYPE_5X9);

			set_mono_font_rel_position (1.0, -4.0);
		}
	}
	else
	{
		if (draw_large_mfd)
		{
			set_mono_font_type (MONO_FONT_TYPE_7X12);

			set_mono_font_rel_position (1.0, -4.0);
		}
		else
		{
			set_mono_font_type (MONO_FONT_TYPE_5X7);

			set_mono_font_rel_position (1.0, -2.0);
		}
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
		if (draw_main_display)
		{
			if (draw_large_mfd)
			{
				set_mono_font_type (MONO_FONT_TYPE_6X10);
			}
			else
			{
				set_mono_font_type (MONO_FONT_TYPE_5X7);
			}
		}
		else
		{
			if (draw_large_mfd)
			{
				set_mono_font_type (MONO_FONT_TYPE_6X10);
			}
			else
			{
				set_mono_font_type (MONO_FONT_TYPE_5X7);
			}
		}

		gunship_position = get_local_entity_vec3d_ptr (get_gunship_entity (), VEC3D_TYPE_POSITION);

		get_waypoint_display_position (get_gunship_entity (), wp, &waypoint_position);

		//
		// waypoint id & range
		//

		waypoint_range = get_2d_range (gunship_position, &waypoint_position);

		if (!comanche_damage.navigation_computer)
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

		if ((current_flight_dynamics->velocity_z.value > 0.1) && (!comanche_damage.navigation_computer))
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

static void draw_flight_display_side_mfd (void)
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
	char
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

static void draw_main_mfd (screen *mfd_screen, comanche_main_mfd_modes mode, comanche_main_mfd_locations location)
{
	ASSERT (mfd_screen);

	ASSERT (comanche_main_mfd_mode_valid (mode));

	ASSERT (comanche_main_mfd_location_valid (location));

	if ((get_undamaged_eo_display_mode (mode) && d3d_can_render_to_texture))
	{
		return;
	}

	draw_main_display = TRUE;

	set_active_screen (mfd_screen);

	if (lock_screen (mfd_screen))
	{
		set_block (0, 0, int_mfd_viewport_size - 1, int_mfd_viewport_size - 1, MFD_BACKGROUND_COLOUR);

		draw_layout_grid ();

		switch (mode)
		{
			////////////////////////////////////////
			case COMANCHE_MAIN_MFD_MODE_OFF:
			////////////////////////////////////////
			{
				break;
			}
			////////////////////////////////////////
			case COMANCHE_MAIN_MFD_MODE_DAMAGED:
			////////////////////////////////////////
			{
				draw_damaged_mfd ();

				break;
			}
			////////////////////////////////////////
			case COMANCHE_MAIN_MFD_MODE_GROUND_RADAR:
			////////////////////////////////////////
			{
				draw_ground_radar_mfd ();

				break;
			}
			////////////////////////////////////////
			case COMANCHE_MAIN_MFD_MODE_AIR_RADAR:
			////////////////////////////////////////
			{
				draw_air_radar_mfd ();

				break;
			}
			////////////////////////////////////////
			case COMANCHE_MAIN_MFD_MODE_FLIR:
			////////////////////////////////////////
			{
				draw_2d_flir_mfd (FALSE);

				break;
			}
			////////////////////////////////////////
			case COMANCHE_MAIN_MFD_MODE_DTV:
			////////////////////////////////////////
			{
				draw_2d_dtv_mfd (FALSE);

				break;
			}
			////////////////////////////////////////
			case COMANCHE_MAIN_MFD_MODE_DVO:
			////////////////////////////////////////
			{
				draw_2d_dvo_mfd (FALSE);

				break;
			}
			////////////////////////////////////////
			case COMANCHE_MAIN_MFD_MODE_TSD:
			////////////////////////////////////////
			{
				draw_tactical_situation_display_mfd (location);

				break;
			}
			////////////////////////////////////////
			case COMANCHE_MAIN_MFD_MODE_ASE:
			////////////////////////////////////////
			{
				draw_aircraft_survivability_equipment_display_mfd (location);

				break;
			}
			////////////////////////////////////////
			case COMANCHE_MAIN_MFD_MODE_WEAPON:
			////////////////////////////////////////
			{
				draw_weapon_display_mfd ();

				break;
			}
			////////////////////////////////////////
			case COMANCHE_MAIN_MFD_MODE_SYSTEM:
			////////////////////////////////////////
			{
				draw_system_display_mfd ();

				break;
			}
			////////////////////////////////////////
			case COMANCHE_MAIN_MFD_MODE_ENGINE:
			////////////////////////////////////////
			{
				draw_engine_display_mfd ();

				break;
			}
			////////////////////////////////////////
			case COMANCHE_MAIN_MFD_MODE_FLIGHT:
			////////////////////////////////////////
			{
				draw_flight_display_mfd ();

				break;
			}
			////////////////////////////////////////
			case COMANCHE_MAIN_MFD_MODE_MISSION:
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

static void draw_side_mfd (screen *mfd_screen, comanche_side_mfd_modes mode, comanche_side_mfd_locations location)
{
	ASSERT (mfd_screen);

	ASSERT (comanche_side_mfd_mode_valid (mode));

	ASSERT (comanche_side_mfd_location_valid (location));

	draw_main_display = FALSE;

	set_active_screen (mfd_screen);

	if (lock_screen (mfd_screen))
	{
		set_block (0, 0, int_mfd_viewport_size - 1, int_mfd_viewport_size - 1, MFD_BACKGROUND_COLOUR);

		draw_layout_grid ();

		switch (mode)
		{
			////////////////////////////////////////
			case COMANCHE_SIDE_MFD_MODE_OFF:
			////////////////////////////////////////
			{
				break;
			}
			////////////////////////////////////////
			case COMANCHE_SIDE_MFD_MODE_DAMAGED:
			////////////////////////////////////////
			{
				draw_damaged_side_mfd ();

				break;
			}
			////////////////////////////////////////
			case COMANCHE_SIDE_MFD_MODE_WEAPON:
			////////////////////////////////////////
			{
				draw_weapon_display_side_mfd ();

				break;
			}
			////////////////////////////////////////
			case COMANCHE_SIDE_MFD_MODE_SYSTEM:
			////////////////////////////////////////
			{
				draw_system_display_side_mfd ();

				break;
			}
			////////////////////////////////////////
			case COMANCHE_SIDE_MFD_MODE_ENGINE:
			////////////////////////////////////////
			{
				draw_engine_display_side_mfd ();

				break;
			}
			////////////////////////////////////////
			case COMANCHE_SIDE_MFD_MODE_FLIGHT:
			////////////////////////////////////////
			{
				draw_flight_display_side_mfd ();

				break;
			}
			////////////////////////////////////////
			default:
			////////////////////////////////////////
			{
				debug_fatal ("Invalid side MFD mode = %d", mode);

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

			set_mono_font_rel_position (3.0, 5.0);

			print_mono_font_string (text_display_line1);

			set_2d_mono_font_position (-1.0, 1.0);

			set_mono_font_rel_position (3.0, 19.0);

			print_mono_font_string (text_display_line2);
		}
		else
		{
			set_mono_font_type (MONO_FONT_TYPE_3X6);

			set_2d_mono_font_position (-1.0, 1.0);

			set_mono_font_rel_position (2.0, 3.0);

			print_mono_font_string (text_display_line1);

			set_2d_mono_font_position (-1.0, 1.0);

			set_mono_font_rel_position (2.0, 10.0);

			print_mono_font_string (text_display_line2);
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

void initialise_comanche_mfd (void)
{
	select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_ASE, COMANCHE_MAIN_MFD_LOCATION_PILOT_LHS);
	select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_TSD, COMANCHE_MAIN_MFD_LOCATION_PILOT_RHS);
	select_comanche_side_mfd_mode (COMANCHE_SIDE_MFD_MODE_ENGINE, COMANCHE_SIDE_MFD_LOCATION_PILOT_LHS);
	select_comanche_side_mfd_mode (COMANCHE_SIDE_MFD_MODE_FLIGHT, COMANCHE_SIDE_MFD_LOCATION_PILOT_RHS);

	select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_MISSION, COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_LHS);
	select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_TSD, COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_RHS);
	select_comanche_side_mfd_mode (COMANCHE_SIDE_MFD_MODE_SYSTEM, COMANCHE_SIDE_MFD_LOCATION_CO_PILOT_LHS);
	select_comanche_side_mfd_mode (COMANCHE_SIDE_MFD_MODE_WEAPON, COMANCHE_SIDE_MFD_LOCATION_CO_PILOT_RHS);

	////////////////////////////////////////

	set_comanche_text_display_text ("", "");

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

	large_pilot_lhs_main_mfd_texture_screen = create_user_texture_screen (LARGE_MFD_VIEWPORT_SIZE, LARGE_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 0);
	large_pilot_rhs_main_mfd_texture_screen = create_user_texture_screen (LARGE_MFD_VIEWPORT_SIZE, LARGE_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 0);
	large_pilot_lhs_side_mfd_texture_screen = create_user_texture_screen (LARGE_MFD_VIEWPORT_SIZE, LARGE_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 0);
	large_pilot_rhs_side_mfd_texture_screen = create_user_texture_screen (LARGE_MFD_VIEWPORT_SIZE, LARGE_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 0);
	large_pilot_text_display_texture_screen = create_user_texture_screen (LARGE_MFD_VIEWPORT_SIZE, LARGE_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 0);

	large_co_pilot_lhs_main_mfd_texture_screen = create_user_texture_screen (LARGE_MFD_VIEWPORT_SIZE, LARGE_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 0);
	large_co_pilot_rhs_main_mfd_texture_screen = create_user_texture_screen (LARGE_MFD_VIEWPORT_SIZE, LARGE_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 0);
	large_co_pilot_lhs_side_mfd_texture_screen = create_user_texture_screen (LARGE_MFD_VIEWPORT_SIZE, LARGE_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 0);
	large_co_pilot_rhs_side_mfd_texture_screen = create_user_texture_screen (LARGE_MFD_VIEWPORT_SIZE, LARGE_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 0);
	large_co_pilot_text_display_texture_screen = create_user_texture_screen (LARGE_MFD_VIEWPORT_SIZE, LARGE_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 0);

	small_pilot_lhs_main_mfd_texture_screen = create_user_texture_screen (SMALL_MFD_VIEWPORT_SIZE, SMALL_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 0);
	small_pilot_rhs_main_mfd_texture_screen = create_user_texture_screen (SMALL_MFD_VIEWPORT_SIZE, SMALL_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 0);
	small_pilot_lhs_side_mfd_texture_screen = create_user_texture_screen (SMALL_MFD_VIEWPORT_SIZE, SMALL_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 0);
	small_pilot_rhs_side_mfd_texture_screen = create_user_texture_screen (SMALL_MFD_VIEWPORT_SIZE, SMALL_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 0);
	small_pilot_text_display_texture_screen = create_user_texture_screen (SMALL_MFD_VIEWPORT_SIZE, SMALL_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 0);

	small_co_pilot_lhs_main_mfd_texture_screen = create_user_texture_screen (SMALL_MFD_VIEWPORT_SIZE, SMALL_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 0);
	small_co_pilot_rhs_main_mfd_texture_screen = create_user_texture_screen (SMALL_MFD_VIEWPORT_SIZE, SMALL_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 0);
	small_co_pilot_lhs_side_mfd_texture_screen = create_user_texture_screen (SMALL_MFD_VIEWPORT_SIZE, SMALL_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 0);
	small_co_pilot_rhs_side_mfd_texture_screen = create_user_texture_screen (SMALL_MFD_VIEWPORT_SIZE, SMALL_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 0);
	small_co_pilot_text_display_texture_screen = create_user_texture_screen (SMALL_MFD_VIEWPORT_SIZE, SMALL_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 0);

	full_mfd_texture_screen = create_system_texture_screen (LARGE_MFD_VIEWPORT_SIZE, LARGE_MFD_VIEWPORT_SIZE, TEXTURE_INDEX_AVCKPT_DISPLAY_RHS_MFD, TEXTURE_TYPE_SINGLEALPHA);

	set_rgb_colour (MFD_COLOUR1,              0, 255,   0, 255);
	set_rgb_colour (MFD_COLOUR2,              0, 200,   0, 255);
	set_rgb_colour (MFD_COLOUR3,              0, 176,   0, 255);
	set_rgb_colour (MFD_COLOUR4,              0, 151,   0, 255);
	set_rgb_colour (MFD_COLOUR5,              0, 128,   0, 255);
	set_rgb_colour (MFD_COLOUR6,             40,  68,  56, 255);
	set_rgb_colour (MFD_CONTOUR_COLOUR,     255, 100,   0, 255);
	set_rgb_colour (MFD_RIVER_COLOUR,        50,  75, 225, 255);
	set_rgb_colour (MFD_ROAD_COLOUR,        255, 200,   0, 255);
	set_rgb_colour (MFD_BACKGROUND_COLOUR,   15,  24,  16, 255);
	set_rgb_colour (MFD_CLEAR_COLOUR,         0,   0,   0,   0);

	set_rgb_colour (TEXT_COLOUR1,           254, 204,   1, 255);
	set_rgb_colour (TEXT_BACKGROUND_COLOUR,  66,  35,  11, 255);

   set_rgb_colour (clear_mfd_colour, 255, 255, 255, 0);

	////////////////////////////////////////
	//
	// weapon display lines
	//
	////////////////////////////////////////

	//
	// main display - with stub wings
	//

	num_main_weapon_line_points_with_stub_wings = get_object_3d_number_of_poly_lines (OBJECT_3D_COMANCHE_COCKPIT_WEAPONS_DISPLAY_ALL);

	ASSERT (num_main_weapon_line_points_with_stub_wings > 0);

	ASSERT ((num_main_weapon_line_points_with_stub_wings & 1) == 0);

	main_weapon_line_points_with_stub_wings = safe_malloc (sizeof (vec3d) * num_main_weapon_line_points_with_stub_wings);

	get_object_3d_poly_line_data (OBJECT_3D_COMANCHE_COCKPIT_WEAPONS_DISPLAY_ALL, main_weapon_line_points_with_stub_wings);

	{
		int
			i;

		for (i = 0; i < num_main_weapon_line_points_with_stub_wings; i++)
		{
			main_weapon_line_points_with_stub_wings[i].x *= MAIN_WEAPON_LINE_POINT_SCALE;
			main_weapon_line_points_with_stub_wings[i].y *= MAIN_WEAPON_LINE_POINT_SCALE;

			main_weapon_line_points_with_stub_wings[i].x += MAIN_WEAPON_LINE_POINT_X_TRANSLATE;
			main_weapon_line_points_with_stub_wings[i].y += MAIN_WEAPON_LINE_POINT_Y_TRANSLATE;
		}
	}

	//
	// main display - without stub wings
	//

	num_main_weapon_line_points_without_stub_wings = get_object_3d_number_of_poly_lines (OBJECT_3D_COMANCHE_COCKPIT_WEAPONS_DISPLAY);

	ASSERT (num_main_weapon_line_points_without_stub_wings > 0);

	ASSERT ((num_main_weapon_line_points_without_stub_wings & 1) == 0);

	main_weapon_line_points_without_stub_wings = safe_malloc (sizeof (vec3d) * num_main_weapon_line_points_without_stub_wings);

	get_object_3d_poly_line_data (OBJECT_3D_COMANCHE_COCKPIT_WEAPONS_DISPLAY, main_weapon_line_points_without_stub_wings);

	{
		int
			i;

		for (i = 0; i < num_main_weapon_line_points_without_stub_wings; i++)
		{
			main_weapon_line_points_without_stub_wings[i].x *= MAIN_WEAPON_LINE_POINT_SCALE;
			main_weapon_line_points_without_stub_wings[i].y *= MAIN_WEAPON_LINE_POINT_SCALE;

			main_weapon_line_points_without_stub_wings[i].x += MAIN_WEAPON_LINE_POINT_X_TRANSLATE;
			main_weapon_line_points_without_stub_wings[i].y += MAIN_WEAPON_LINE_POINT_Y_TRANSLATE;
		}
	}

	//
	// side display - with stub wings
	//

	num_side_weapon_line_points_with_stub_wings = get_object_3d_number_of_poly_lines (OBJECT_3D_COMANCHE_COCKPIT_WEAPONS_DISPLAY_ALL);

	ASSERT (num_side_weapon_line_points_with_stub_wings > 0);

	ASSERT ((num_side_weapon_line_points_with_stub_wings & 1) == 0);

	side_weapon_line_points_with_stub_wings = safe_malloc (sizeof (vec3d) * num_side_weapon_line_points_with_stub_wings);

	get_object_3d_poly_line_data (OBJECT_3D_COMANCHE_COCKPIT_WEAPONS_DISPLAY_ALL, side_weapon_line_points_with_stub_wings);

	{
		int
			i;

		for (i = 0; i < num_side_weapon_line_points_with_stub_wings; i++)
		{
			side_weapon_line_points_with_stub_wings[i].x *= SIDE_WEAPON_LINE_POINT_SCALE;
			side_weapon_line_points_with_stub_wings[i].y *= SIDE_WEAPON_LINE_POINT_SCALE;

			side_weapon_line_points_with_stub_wings[i].x += SIDE_WEAPON_LINE_POINT_X_TRANSLATE;
			side_weapon_line_points_with_stub_wings[i].y += SIDE_WEAPON_LINE_POINT_Y_TRANSLATE;
		}
	}

	//
	// side display - without stub wings
	//

	num_side_weapon_line_points_without_stub_wings = get_object_3d_number_of_poly_lines (OBJECT_3D_COMANCHE_COCKPIT_WEAPONS_DISPLAY);

	ASSERT (num_side_weapon_line_points_without_stub_wings > 0);

	ASSERT ((num_side_weapon_line_points_without_stub_wings & 1) == 0);

	side_weapon_line_points_without_stub_wings = safe_malloc (sizeof (vec3d) * num_side_weapon_line_points_without_stub_wings);

	get_object_3d_poly_line_data (OBJECT_3D_COMANCHE_COCKPIT_WEAPONS_DISPLAY, side_weapon_line_points_without_stub_wings);

	{
		int
			i;

		for (i = 0; i < num_side_weapon_line_points_without_stub_wings; i++)
		{
			side_weapon_line_points_without_stub_wings[i].x *= SIDE_WEAPON_LINE_POINT_SCALE;
			side_weapon_line_points_without_stub_wings[i].y *= SIDE_WEAPON_LINE_POINT_SCALE;

			side_weapon_line_points_without_stub_wings[i].x += SIDE_WEAPON_LINE_POINT_X_TRANSLATE;
			side_weapon_line_points_without_stub_wings[i].y += SIDE_WEAPON_LINE_POINT_Y_TRANSLATE;
		}
	}

//VJ 030423 TSd render mod

   Initialise_TSD_render_terrain();
   
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_comanche_mfd (void)
{
	destroy_2d_environment (mfd_env);

	////////////////////////////////////////

	destroy_screen (large_pilot_lhs_main_mfd_texture_screen);
	destroy_screen (large_pilot_rhs_main_mfd_texture_screen);
	destroy_screen (large_pilot_lhs_side_mfd_texture_screen);
	destroy_screen (large_pilot_rhs_side_mfd_texture_screen);
	destroy_screen (large_pilot_text_display_texture_screen);

	destroy_screen (large_co_pilot_lhs_main_mfd_texture_screen);
	destroy_screen (large_co_pilot_rhs_main_mfd_texture_screen);
	destroy_screen (large_co_pilot_lhs_side_mfd_texture_screen);
	destroy_screen (large_co_pilot_rhs_side_mfd_texture_screen);
	destroy_screen (large_co_pilot_text_display_texture_screen);

	destroy_screen (small_pilot_lhs_main_mfd_texture_screen);
	destroy_screen (small_pilot_rhs_main_mfd_texture_screen);
	destroy_screen (small_pilot_lhs_side_mfd_texture_screen);
	destroy_screen (small_pilot_rhs_side_mfd_texture_screen);
	destroy_screen (small_pilot_text_display_texture_screen);

	destroy_screen (small_co_pilot_lhs_main_mfd_texture_screen);
	destroy_screen (small_co_pilot_rhs_main_mfd_texture_screen);
	destroy_screen (small_co_pilot_lhs_side_mfd_texture_screen);
	destroy_screen (small_co_pilot_rhs_side_mfd_texture_screen);
	destroy_screen (small_co_pilot_text_display_texture_screen);

	destroy_screen (full_mfd_texture_screen);

	////////////////////////////////////////
	//
	// weapon display lines
	//
	////////////////////////////////////////

	safe_free (main_weapon_line_points_with_stub_wings);

	safe_free (main_weapon_line_points_without_stub_wings);

	safe_free (side_weapon_line_points_with_stub_wings);

	safe_free (side_weapon_line_points_without_stub_wings);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_comanche_mfd (void)
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

		pilot_lhs_main_mfd_texture_screen = large_pilot_lhs_main_mfd_texture_screen;
		pilot_rhs_main_mfd_texture_screen = large_pilot_rhs_main_mfd_texture_screen;
		pilot_lhs_side_mfd_texture_screen = large_pilot_lhs_side_mfd_texture_screen;
		pilot_rhs_side_mfd_texture_screen = large_pilot_rhs_side_mfd_texture_screen;
		pilot_text_display_texture_screen = large_pilot_text_display_texture_screen;

		co_pilot_lhs_main_mfd_texture_screen = large_co_pilot_lhs_main_mfd_texture_screen;
		co_pilot_rhs_main_mfd_texture_screen = large_co_pilot_rhs_main_mfd_texture_screen;
		co_pilot_lhs_side_mfd_texture_screen = large_co_pilot_lhs_side_mfd_texture_screen;
		co_pilot_rhs_side_mfd_texture_screen = large_co_pilot_rhs_side_mfd_texture_screen;
		co_pilot_text_display_texture_screen = large_co_pilot_text_display_texture_screen;

		eo_3d_texture_screen = large_eo_3d_texture_screen;
	}
	else
	{
		draw_large_mfd = FALSE;

		pilot_lhs_main_mfd_texture_screen = small_pilot_lhs_main_mfd_texture_screen;
		pilot_rhs_main_mfd_texture_screen = small_pilot_rhs_main_mfd_texture_screen;
		pilot_lhs_side_mfd_texture_screen = small_pilot_lhs_side_mfd_texture_screen;
		pilot_rhs_side_mfd_texture_screen = small_pilot_rhs_side_mfd_texture_screen;
		pilot_text_display_texture_screen = small_pilot_text_display_texture_screen;

		co_pilot_lhs_main_mfd_texture_screen = small_co_pilot_lhs_main_mfd_texture_screen;
		co_pilot_rhs_main_mfd_texture_screen = small_co_pilot_rhs_main_mfd_texture_screen;
		co_pilot_lhs_side_mfd_texture_screen = small_co_pilot_lhs_side_mfd_texture_screen;
		co_pilot_rhs_side_mfd_texture_screen = small_co_pilot_rhs_side_mfd_texture_screen;
		co_pilot_text_display_texture_screen = small_co_pilot_text_display_texture_screen;

		eo_3d_texture_screen = small_eo_3d_texture_screen;
	}

	set_system_texture_screen (pilot_lhs_main_mfd_texture_screen, TEXTURE_INDEX_COMANCHE_MFD2);
	set_system_texture_screen (pilot_rhs_main_mfd_texture_screen, TEXTURE_INDEX_COMANCHE_MFD3);
	set_system_texture_screen (pilot_lhs_side_mfd_texture_screen, TEXTURE_INDEX_COMANCHE_MFD1);
	set_system_texture_screen (pilot_rhs_side_mfd_texture_screen, TEXTURE_INDEX_COMANCHE_MFD4);
	set_system_texture_screen (pilot_text_display_texture_screen, TEXTURE_INDEX_COMANCHE_TEXT);

	set_system_texture_screen (co_pilot_lhs_main_mfd_texture_screen, TEXTURE_INDEX_COMANCHE_MFD6);
	set_system_texture_screen (co_pilot_rhs_main_mfd_texture_screen, TEXTURE_INDEX_COMANCHE_MFD7);
	set_system_texture_screen (co_pilot_lhs_side_mfd_texture_screen, TEXTURE_INDEX_COMANCHE_MFD5);
	set_system_texture_screen (co_pilot_rhs_side_mfd_texture_screen, TEXTURE_INDEX_COMANCHE_MFD8);
	set_system_texture_screen (co_pilot_text_display_texture_screen, TEXTURE_INDEX_COMANCHE_TEXT2);

	////////////////////////////////////////
	//
	// SELECT VISIBLE DISPLAYS
	//
	////////////////////////////////////////

	switch (get_view_mode ())
	{
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT:
		case VIEW_MODE_VIRTUAL_COCKPIT_PADLOCK:
		case VIEW_MODE_VIRTUAL_COCKPIT_TRACK_TARGET:
		////////////////////////////////////////
		{
			if (get_crew_role () == CREW_ROLE_PILOT)
			{
				display_mask =
					PILOT_LHS_MAIN_MFD |
					PILOT_RHS_MAIN_MFD |
					PILOT_LHS_SIDE_MFD |
					PILOT_RHS_SIDE_MFD |
					PILOT_TEXT_DISPLAY;
			}
			else
			{
				display_mask =
					CO_PILOT_LHS_MAIN_MFD |
					CO_PILOT_RHS_MAIN_MFD |
					CO_PILOT_LHS_SIDE_MFD |
					CO_PILOT_RHS_SIDE_MFD |
					CO_PILOT_TEXT_DISPLAY;
			}

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY:
		////////////////////////////////////////
		{
			display_mask =
				PILOT_LHS_MAIN_MFD |
				PILOT_RHS_MAIN_MFD |
				PILOT_LHS_SIDE_MFD |
				PILOT_TEXT_DISPLAY;

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY:
		////////////////////////////////////////
		{
			display_mask =
				PILOT_LHS_MAIN_MFD |
				PILOT_RHS_MAIN_MFD |
				PILOT_RHS_SIDE_MFD |
				PILOT_TEXT_DISPLAY;

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY:
		////////////////////////////////////////
		{
			display_mask =
				CO_PILOT_LHS_MAIN_MFD |
				CO_PILOT_RHS_MAIN_MFD |
				CO_PILOT_LHS_SIDE_MFD |
				CO_PILOT_TEXT_DISPLAY;

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY:
		////////////////////////////////////////
		{
			display_mask =
				CO_PILOT_LHS_MAIN_MFD |
				CO_PILOT_RHS_MAIN_MFD |
				CO_PILOT_RHS_SIDE_MFD |
				CO_PILOT_TEXT_DISPLAY;

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			display_mask =
				PILOT_LHS_MAIN_MFD |
				PILOT_RHS_MAIN_MFD |
				PILOT_LHS_SIDE_MFD |
				PILOT_RHS_SIDE_MFD |
				PILOT_TEXT_DISPLAY |
				CO_PILOT_LHS_MAIN_MFD |
				CO_PILOT_RHS_MAIN_MFD |
				CO_PILOT_LHS_SIDE_MFD |
				CO_PILOT_RHS_SIDE_MFD |
				CO_PILOT_TEXT_DISPLAY;

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

			if (get_undamaged_eo_display_mode (pilot_lhs_main_mfd_mode) && (display_mask & PILOT_LHS_MAIN_MFD))
			{
				set_system_texture_screen (eo_3d_texture_screen, TEXTURE_INDEX_COMANCHE_MFD2);

				draw_eo_display = TRUE;
			}

			if (get_undamaged_eo_display_mode (pilot_rhs_main_mfd_mode) && (display_mask & PILOT_RHS_MAIN_MFD))
			{
				set_system_texture_screen (eo_3d_texture_screen, TEXTURE_INDEX_COMANCHE_MFD3);

				draw_eo_display = TRUE;
			}

			if (get_undamaged_eo_display_mode (co_pilot_lhs_main_mfd_mode) && (display_mask & CO_PILOT_LHS_MAIN_MFD))
			{
				set_system_texture_screen (eo_3d_texture_screen, TEXTURE_INDEX_COMANCHE_MFD6);

				draw_eo_display = TRUE;
			}

			if (get_undamaged_eo_display_mode (co_pilot_rhs_main_mfd_mode) && (display_mask & CO_PILOT_RHS_MAIN_MFD))
			{
				set_system_texture_screen (eo_3d_texture_screen, TEXTURE_INDEX_COMANCHE_MFD7);

				draw_eo_display = TRUE;
			}

			if (draw_eo_display)
			{
				switch (get_main_mfd_mode_for_eo_sensor ())
				{
					case COMANCHE_MAIN_MFD_MODE_FLIR:
					{
						draw_3d_flir_mfd (FALSE);

						break;
					}
					case COMANCHE_MAIN_MFD_MODE_DTV:
					{
						draw_3d_dtv_mfd (FALSE);

						break;
					}
					case COMANCHE_MAIN_MFD_MODE_DVO:
					{
						draw_3d_dvo_mfd (FALSE);

						break;
					}
				}

				draw_main_display = TRUE;

				set_active_screen (eo_3d_texture_screen);

				if (lock_screen (eo_3d_texture_screen))
				{
					draw_layout_grid ();

					switch (get_main_mfd_mode_for_eo_sensor ())
					{
						case COMANCHE_MAIN_MFD_MODE_FLIR:
						{
							draw_2d_flir_mfd (TRUE);

							break;
						}
						case COMANCHE_MAIN_MFD_MODE_DTV:
						{
							draw_2d_dtv_mfd (TRUE);

							break;
						}
						case COMANCHE_MAIN_MFD_MODE_DVO:
						{
							draw_2d_dvo_mfd (TRUE);

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

	if (display_mask & PILOT_LHS_MAIN_MFD)
	{
		draw_main_mfd (pilot_lhs_main_mfd_texture_screen, pilot_lhs_main_mfd_mode, COMANCHE_MAIN_MFD_LOCATION_PILOT_LHS);
	}

	if (display_mask & PILOT_RHS_MAIN_MFD)
	{
		draw_main_mfd (pilot_rhs_main_mfd_texture_screen, pilot_rhs_main_mfd_mode, COMANCHE_MAIN_MFD_LOCATION_PILOT_RHS);
	}

	if (display_mask & PILOT_LHS_SIDE_MFD)
	{
		draw_side_mfd (pilot_lhs_side_mfd_texture_screen, pilot_lhs_side_mfd_mode, COMANCHE_SIDE_MFD_LOCATION_PILOT_LHS);
	}

	if (display_mask & PILOT_RHS_SIDE_MFD)
	{
		draw_side_mfd (pilot_rhs_side_mfd_texture_screen, pilot_rhs_side_mfd_mode, COMANCHE_SIDE_MFD_LOCATION_PILOT_RHS);
	}

	if (display_mask & PILOT_TEXT_DISPLAY)
	{
		draw_text_display (pilot_text_display_texture_screen);
	}

	if (display_mask & CO_PILOT_LHS_MAIN_MFD)
	{
		draw_main_mfd (co_pilot_lhs_main_mfd_texture_screen, co_pilot_lhs_main_mfd_mode, COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_LHS);
	}

	if (display_mask & CO_PILOT_RHS_MAIN_MFD)
	{
		draw_main_mfd (co_pilot_rhs_main_mfd_texture_screen, co_pilot_rhs_main_mfd_mode, COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_RHS);
	}

	if (display_mask & CO_PILOT_LHS_SIDE_MFD)
	{
		draw_side_mfd (co_pilot_lhs_side_mfd_texture_screen, co_pilot_lhs_side_mfd_mode, COMANCHE_SIDE_MFD_LOCATION_CO_PILOT_LHS);
	}

	if (display_mask & CO_PILOT_RHS_SIDE_MFD)
	{
		draw_side_mfd (co_pilot_rhs_side_mfd_texture_screen, co_pilot_rhs_side_mfd_mode, COMANCHE_SIDE_MFD_LOCATION_CO_PILOT_RHS);
	}

	if (display_mask & CO_PILOT_TEXT_DISPLAY)
	{
		draw_text_display (co_pilot_text_display_texture_screen);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_comanche_text_display_text (char *s1, char *s2)
{
	ASSERT (s1);

	ASSERT (s2);

	strncpy (text_display_line1, s1, TEXT_DISPLAY_MAX_STRING_LENGTH);

	strncpy (text_display_line2, s2, TEXT_DISPLAY_MAX_STRING_LENGTH);

	text_display_line1[TEXT_DISPLAY_MAX_STRING_LENGTH] = '\0';

	text_display_line2[TEXT_DISPLAY_MAX_STRING_LENGTH] = '\0';
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_comanche_full_screen_display (void)
{
	comanche_main_mfd_modes
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
			mode = pilot_lhs_main_mfd_mode;

			break;
		}
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY:
		{
			mode = pilot_rhs_main_mfd_mode;

			break;
		}
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY:
		{
			mode = co_pilot_lhs_main_mfd_mode;

			break;
		}
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY:
		{
			mode = co_pilot_rhs_main_mfd_mode;

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

	switch (get_view_mode ())
	{
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY:
		{
			mfd_screen_x_min = floor ((243.0 * full_screen_width) / 640.0);
			mfd_screen_y_min = floor ((40.0 * full_screen_height) / 480.0);

			mfd_screen_x_max = ceil ((499.0 * full_screen_width) / 640.0);
			mfd_screen_y_max = ceil ((296.0 * full_screen_height) / 480.0);

			break;
		}
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY:
		{
			mfd_screen_x_min = floor ((141.0 * full_screen_width) / 640.0);
			mfd_screen_y_min = floor ((40.0 * full_screen_height) / 480.0);

			mfd_screen_x_max = ceil ((397.0 * full_screen_width) / 640.0);
			mfd_screen_y_max = ceil ((296.0 * full_screen_height) / 480.0);

			break;
		}
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY:
		{
			mfd_screen_x_min = floor ((243.0 * full_screen_width) / 640.0);
			mfd_screen_y_min = floor ((40.0 * full_screen_height) / 480.0);

			mfd_screen_x_max = ceil ((499.0 * full_screen_width) / 640.0);
			mfd_screen_y_max = ceil ((296.0 * full_screen_height) / 480.0);

			break;
		}
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY:
		{
			mfd_screen_x_min = floor ((141.0 * full_screen_width) / 640.0);
			mfd_screen_y_min = floor ((40.0 * full_screen_height) / 480.0);

			mfd_screen_x_max = ceil ((397.0 * full_screen_width) / 640.0);
			mfd_screen_y_max = ceil ((296.0 * full_screen_height) / 480.0);

			break;
		}
	}

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
		case COMANCHE_MAIN_MFD_MODE_FLIR:
		{
			draw_3d_flir_mfd (TRUE);

			break;
		}
		case COMANCHE_MAIN_MFD_MODE_DTV:
		{
			draw_3d_dtv_mfd (TRUE);

			break;
		}
		case COMANCHE_MAIN_MFD_MODE_DVO:
		{
			draw_3d_dvo_mfd (TRUE);

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

	draw_main_display = TRUE;

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
			case COMANCHE_MAIN_MFD_MODE_FLIR:
			{
				draw_2d_flir_mfd (TRUE);

				break;
			}
			case COMANCHE_MAIN_MFD_MODE_DTV:
			{
				draw_2d_dtv_mfd (TRUE);

				break;
			}
			case COMANCHE_MAIN_MFD_MODE_DVO:
			{
				draw_2d_dvo_mfd (TRUE);

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

static void draw_overlaid_main_mfd (screen *mfd_screen, comanche_main_mfd_modes mode, comanche_main_mfd_locations location)
{
	float
		border_size;

	ASSERT (mfd_screen);

	ASSERT (comanche_main_mfd_mode_valid (mode));

	ASSERT (comanche_main_mfd_location_valid (location));

	if (mode == COMANCHE_MAIN_MFD_MODE_OFF)
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
		case COMANCHE_MAIN_MFD_LOCATION_PILOT_LHS:
		case COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_LHS:
		////////////////////////////////////////
		{
			mfd_screen_x_min = border_size;
			mfd_screen_y_min = full_screen_height - border_size - mfd_screen_height;

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_LOCATION_PILOT_RHS:
		case COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_RHS:
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

	draw_main_display = TRUE;

	////////////////////////////////////////
	//
	// draw MFD display
	//
	////////////////////////////////////////

	switch (mode)
	{
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_MODE_OFF:
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
		case COMANCHE_MAIN_MFD_MODE_DAMAGED:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_screen);

			if (lock_screen (mfd_screen))
			{
				set_block (0, 0, int_mfd_viewport_size - 1, int_mfd_viewport_size - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_damaged_mfd ();

				flush_screen_texture_graphics (mfd_screen);

				unlock_screen (mfd_screen);
			}

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_MODE_GROUND_RADAR:
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
		case COMANCHE_MAIN_MFD_MODE_AIR_RADAR:
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
		case COMANCHE_MAIN_MFD_MODE_FLIR:
		////////////////////////////////////////
		{
			if (!comanche_damage.flir)
			{
				draw_full_screen_3d_eo_display (&comanche_flir, TARGET_ACQUISITION_SYSTEM_FLIR);
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
		case COMANCHE_MAIN_MFD_MODE_DTV:
		////////////////////////////////////////
		{
			if (!comanche_damage.dtv)
			{
				draw_full_screen_3d_eo_display (&comanche_dtv, TARGET_ACQUISITION_SYSTEM_DTV);
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

				draw_2d_dtv_mfd (TRUE);

				flush_screen_texture_graphics (mfd_screen);

				unlock_screen (mfd_screen);
			}

			set_pilots_full_screen_params (FALSE);

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_MODE_DVO:
		////////////////////////////////////////
		{
			if (!comanche_damage.dvo)
			{
				draw_full_screen_3d_eo_display (&comanche_dvo, TARGET_ACQUISITION_SYSTEM_DVO);
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

				draw_2d_dvo_mfd (TRUE);

				flush_screen_texture_graphics (mfd_screen);

				unlock_screen (mfd_screen);
			}

			set_pilots_full_screen_params (FALSE);

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_MODE_TSD:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_screen);

			if (lock_screen (mfd_screen))
			{
				rgb_colour
					store_contour_colour,
					store_river_colour,
					store_road_colour;

				set_block (0, 0, int_mfd_viewport_size - 1, int_mfd_viewport_size - 1, clear_mfd_colour);

				draw_layout_grid ();

				store_contour_colour	= MFD_CONTOUR_COLOUR;
				store_river_colour	= MFD_RIVER_COLOUR;
				store_road_colour		= MFD_ROAD_COLOUR;

				set_rgb_colour (MFD_CONTOUR_COLOUR,   0, 151,   0, 255);
				set_rgb_colour (MFD_RIVER_COLOUR,     0, 176,   0, 255);
				set_rgb_colour (MFD_ROAD_COLOUR,      0, 200,   0, 255);

				draw_tactical_situation_display_mfd (location);

				MFD_CONTOUR_COLOUR	= store_contour_colour;
				MFD_RIVER_COLOUR		= store_river_colour;
				MFD_ROAD_COLOUR		= store_road_colour;

				flush_screen_texture_graphics (mfd_screen);

				unlock_screen (mfd_screen);
			}

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_MODE_ASE:
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
		case COMANCHE_MAIN_MFD_MODE_WEAPON:
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
		case COMANCHE_MAIN_MFD_MODE_SYSTEM:
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
		case COMANCHE_MAIN_MFD_MODE_ENGINE:
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
		case COMANCHE_MAIN_MFD_MODE_FLIGHT:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_screen);

			if (lock_screen (mfd_screen))
			{
				rgb_colour
					store_background_colour;

				set_block (0, 0, int_mfd_viewport_size - 1, int_mfd_viewport_size - 1, clear_mfd_colour);

				draw_layout_grid ();

				store_background_colour = MFD_BACKGROUND_COLOUR;

				set_rgb_colour (MFD_BACKGROUND_COLOUR, 255, 255, 255, 0);

				draw_flight_display_mfd ();

				MFD_BACKGROUND_COLOUR = store_background_colour;

				flush_screen_texture_graphics (mfd_screen);

				unlock_screen (mfd_screen);
			}

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_MODE_MISSION:
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
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_overlaid_comanche_mfd (void)
{
	////////////////////////////////////////
	//
	// SELECT LARGE OR SMALL MFD TEXTURES
	//
	////////////////////////////////////////

   if (application_video_width >= 1280)
   {
      draw_large_mfd = TRUE;

      pilot_lhs_main_mfd_texture_screen = large_pilot_lhs_main_mfd_texture_screen;
      pilot_rhs_main_mfd_texture_screen = large_pilot_rhs_main_mfd_texture_screen;
      pilot_lhs_side_mfd_texture_screen = large_pilot_lhs_side_mfd_texture_screen;
      pilot_rhs_side_mfd_texture_screen = large_pilot_rhs_side_mfd_texture_screen;
      pilot_text_display_texture_screen = large_pilot_text_display_texture_screen;

      co_pilot_lhs_main_mfd_texture_screen = large_co_pilot_lhs_main_mfd_texture_screen;
      co_pilot_rhs_main_mfd_texture_screen = large_co_pilot_rhs_main_mfd_texture_screen;
      co_pilot_lhs_side_mfd_texture_screen = large_co_pilot_lhs_side_mfd_texture_screen;
      co_pilot_rhs_side_mfd_texture_screen = large_co_pilot_rhs_side_mfd_texture_screen;
      co_pilot_text_display_texture_screen = large_co_pilot_text_display_texture_screen;

      eo_3d_texture_screen = large_eo_3d_texture_screen;
   }
   else
   {
      draw_large_mfd = FALSE;

      pilot_lhs_main_mfd_texture_screen = small_pilot_lhs_main_mfd_texture_screen;
      pilot_rhs_main_mfd_texture_screen = small_pilot_rhs_main_mfd_texture_screen;
      pilot_lhs_side_mfd_texture_screen = small_pilot_lhs_side_mfd_texture_screen;
      pilot_rhs_side_mfd_texture_screen = small_pilot_rhs_side_mfd_texture_screen;
      pilot_text_display_texture_screen = small_pilot_text_display_texture_screen;

      co_pilot_lhs_main_mfd_texture_screen = small_co_pilot_lhs_main_mfd_texture_screen;
      co_pilot_rhs_main_mfd_texture_screen = small_co_pilot_rhs_main_mfd_texture_screen;
      co_pilot_lhs_side_mfd_texture_screen = small_co_pilot_lhs_side_mfd_texture_screen;
      co_pilot_rhs_side_mfd_texture_screen = small_co_pilot_rhs_side_mfd_texture_screen;
      co_pilot_text_display_texture_screen = small_co_pilot_text_display_texture_screen;

      eo_3d_texture_screen = small_eo_3d_texture_screen;
   }

	set_system_texture_screen (pilot_lhs_main_mfd_texture_screen, TEXTURE_INDEX_COMANCHE_MFD2);
	set_system_texture_screen (pilot_rhs_main_mfd_texture_screen, TEXTURE_INDEX_COMANCHE_MFD3);
	set_system_texture_screen (pilot_lhs_side_mfd_texture_screen, TEXTURE_INDEX_COMANCHE_MFD1);
	set_system_texture_screen (pilot_rhs_side_mfd_texture_screen, TEXTURE_INDEX_COMANCHE_MFD4);
	set_system_texture_screen (pilot_text_display_texture_screen, TEXTURE_INDEX_COMANCHE_TEXT);

	set_system_texture_screen (co_pilot_lhs_main_mfd_texture_screen, TEXTURE_INDEX_COMANCHE_MFD6);
	set_system_texture_screen (co_pilot_rhs_main_mfd_texture_screen, TEXTURE_INDEX_COMANCHE_MFD7);
	set_system_texture_screen (co_pilot_lhs_side_mfd_texture_screen, TEXTURE_INDEX_COMANCHE_MFD5);
	set_system_texture_screen (co_pilot_rhs_side_mfd_texture_screen, TEXTURE_INDEX_COMANCHE_MFD8);
	set_system_texture_screen (co_pilot_text_display_texture_screen, TEXTURE_INDEX_COMANCHE_TEXT2);

	////////////////////////////////////////
	//
	// SELECT VISIBLE DISPLAYS
	//
	////////////////////////////////////////

   if (get_crew_role () == CREW_ROLE_PILOT)
   {
      display_mask = PILOT_LHS_MAIN_MFD | PILOT_RHS_MAIN_MFD;
   }
   else
   {
      display_mask = CO_PILOT_LHS_MAIN_MFD | CO_PILOT_RHS_MAIN_MFD;
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

	if (display_mask & PILOT_LHS_MAIN_MFD)
	{
      draw_overlaid_main_mfd (pilot_lhs_main_mfd_texture_screen, pilot_lhs_main_mfd_mode, COMANCHE_MAIN_MFD_LOCATION_PILOT_LHS);
	}

	if (display_mask & PILOT_RHS_MAIN_MFD)
	{
      draw_overlaid_main_mfd (pilot_rhs_main_mfd_texture_screen, pilot_rhs_main_mfd_mode, COMANCHE_MAIN_MFD_LOCATION_PILOT_RHS);
	}

	if (display_mask & CO_PILOT_LHS_MAIN_MFD)
	{
      draw_overlaid_main_mfd (co_pilot_lhs_main_mfd_texture_screen, co_pilot_lhs_main_mfd_mode, COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_LHS);
	}

	if (display_mask & CO_PILOT_RHS_MAIN_MFD)
	{
      draw_overlaid_main_mfd (co_pilot_rhs_main_mfd_texture_screen, co_pilot_rhs_main_mfd_mode, COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_RHS);
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

int get_comanche_main_mfd_has_focus (comanche_main_mfd_locations mfd_location)
{
	int
		result;

	comanche_main_mfd_modes
		mfd_mode;

	ASSERT (comanche_main_mfd_location_valid (mfd_location));

	mfd_mode = *main_mfd_mode_ptrs[mfd_location];

	switch (target_acquisition_system)
	{
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_GROUND_RADAR:
		////////////////////////////////////////
		{
			result = (mfd_mode == COMANCHE_MAIN_MFD_MODE_GROUND_RADAR);

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_AIR_RADAR:
		////////////////////////////////////////
		{
			result = (mfd_mode == COMANCHE_MAIN_MFD_MODE_AIR_RADAR);

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_FLIR:
		////////////////////////////////////////
		{
			result = (mfd_mode == COMANCHE_MAIN_MFD_MODE_FLIR);

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_DTV:
		////////////////////////////////////////
		{
			result = (mfd_mode == COMANCHE_MAIN_MFD_MODE_DTV);

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_DVO:
		////////////////////////////////////////
		{
			result = (mfd_mode == COMANCHE_MAIN_MFD_MODE_DVO);

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

static comanche_main_mfd_modes get_main_mfd_mode_for_eo_sensor (void)
{
	comanche_main_mfd_modes
		mfd_mode;

	if (eo_sensor == TARGET_ACQUISITION_SYSTEM_FLIR)
	{
		mfd_mode = COMANCHE_MAIN_MFD_MODE_FLIR;
	}
	else if (eo_sensor == TARGET_ACQUISITION_SYSTEM_DTV)
	{
		mfd_mode = COMANCHE_MAIN_MFD_MODE_DTV;
	}
	else if (eo_sensor == TARGET_ACQUISITION_SYSTEM_DVO)
	{
		mfd_mode = COMANCHE_MAIN_MFD_MODE_DVO;
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

static comanche_main_mfd_modes get_default_main_mfd_mode (comanche_main_mfd_locations mfd_location)
{
	comanche_main_mfd_modes
		mfd_mode;

	ASSERT (comanche_main_mfd_location_valid (mfd_location));

	switch (mfd_location)
	{
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_LOCATION_PILOT_LHS:
		////////////////////////////////////////
		{
			mfd_mode = COMANCHE_MAIN_MFD_MODE_ASE;

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_LOCATION_PILOT_RHS:
		////////////////////////////////////////
		{
			mfd_mode = COMANCHE_MAIN_MFD_MODE_TSD;

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_LHS:
		////////////////////////////////////////
		{
			mfd_mode = COMANCHE_MAIN_MFD_MODE_ASE;

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_RHS:
		////////////////////////////////////////
		{
			mfd_mode = COMANCHE_MAIN_MFD_MODE_TSD;

			break;
		}
	}

	return (mfd_mode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static comanche_side_mfd_modes get_default_side_mfd_mode (comanche_side_mfd_locations mfd_location)
{
	comanche_side_mfd_modes
		mfd_mode;

	ASSERT (comanche_side_mfd_location_valid (mfd_location));

	switch (mfd_location)
	{
		////////////////////////////////////////
		case COMANCHE_SIDE_MFD_LOCATION_PILOT_LHS:
		////////////////////////////////////////
		{
			mfd_mode = COMANCHE_SIDE_MFD_MODE_ENGINE;

			break;
		}
		////////////////////////////////////////
		case COMANCHE_SIDE_MFD_LOCATION_PILOT_RHS:
		////////////////////////////////////////
		{
			mfd_mode = COMANCHE_SIDE_MFD_MODE_FLIGHT;

			break;
		}
		////////////////////////////////////////
		case COMANCHE_SIDE_MFD_LOCATION_CO_PILOT_LHS:
		////////////////////////////////////////
		{
			mfd_mode = COMANCHE_SIDE_MFD_MODE_SYSTEM;

			break;
		}
		////////////////////////////////////////
		case COMANCHE_SIDE_MFD_LOCATION_CO_PILOT_RHS:
		////////////////////////////////////////
		{
			mfd_mode = COMANCHE_SIDE_MFD_MODE_WEAPON;

			break;
		}
	}

	return (mfd_mode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_main_mfd_damage (comanche_main_mfd_locations mfd_location)
{
	int
		damage;

	ASSERT (comanche_main_mfd_location_valid (mfd_location));

	switch (mfd_location)
	{
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_LOCATION_PILOT_LHS:
		////////////////////////////////////////
		{
			damage = comanche_damage.pilot_lh_main_mfd;

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_LOCATION_PILOT_RHS:
		////////////////////////////////////////
		{
			damage = comanche_damage.pilot_rh_main_mfd;

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_LHS:
		////////////////////////////////////////
		{
			damage = comanche_damage.co_pilot_lh_main_mfd;

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_RHS:
		////////////////////////////////////////
		{
			damage = comanche_damage.co_pilot_rh_main_mfd;

			break;
		}
	}

	return (damage);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_side_mfd_damage (comanche_side_mfd_locations mfd_location)
{
	int
		damage;

	ASSERT (comanche_side_mfd_location_valid (mfd_location));

	switch (mfd_location)
	{
		////////////////////////////////////////
		case COMANCHE_SIDE_MFD_LOCATION_PILOT_LHS:
		////////////////////////////////////////
		{
			damage = comanche_damage.pilot_lh_side_mfd;

			break;
		}
		////////////////////////////////////////
		case COMANCHE_SIDE_MFD_LOCATION_PILOT_RHS:
		////////////////////////////////////////
		{
			damage = comanche_damage.pilot_rh_side_mfd;

			break;
		}
		////////////////////////////////////////
		case COMANCHE_SIDE_MFD_LOCATION_CO_PILOT_LHS:
		////////////////////////////////////////
		{
			damage = comanche_damage.co_pilot_lh_side_mfd;

			break;
		}
		////////////////////////////////////////
		case COMANCHE_SIDE_MFD_LOCATION_CO_PILOT_RHS:
		////////////////////////////////////////
		{
			damage = comanche_damage.co_pilot_rh_side_mfd;

			break;
		}
	}

	return (damage);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_comanche_main_mfd_mode (comanche_main_mfd_modes mfd_mode, comanche_main_mfd_locations mfd_location)
{
	comanche_main_mfd_modes
		*mfd_mode_ptr1,
		*mfd_mode_ptr2,
		default_mfd_mode;

	ASSERT (comanche_main_mfd_mode_valid (mfd_mode));

	ASSERT (comanche_main_mfd_location_valid (mfd_location));

	debug_colour_log (DEBUG_COLOUR_AMBER, "%s = %s", comanche_main_mfd_location_names[mfd_location], comanche_main_mfd_mode_names[mfd_mode]);

	mfd_mode_ptr1 = main_mfd_mode_ptrs[mfd_location];

	mfd_mode_ptr2 = opposite_main_mfd_mode_ptrs[mfd_location];

	if ((mfd_mode == COMANCHE_MAIN_MFD_MODE_DAMAGED) && (*mfd_mode_ptr1 == COMANCHE_MAIN_MFD_MODE_OFF))
	{
		mfd_mode = COMANCHE_MAIN_MFD_MODE_OFF;
	}

	if (get_main_mfd_damage (mfd_location))
	{
		if (mfd_mode != COMANCHE_MAIN_MFD_MODE_OFF)
		{
			mfd_mode = COMANCHE_MAIN_MFD_MODE_DAMAGED;
		}
	}

	if ((mfd_mode != COMANCHE_MAIN_MFD_MODE_OFF) && (mfd_mode != COMANCHE_MAIN_MFD_MODE_DAMAGED) && (mfd_mode == *mfd_mode_ptr2))
	{
		default_mfd_mode = get_default_main_mfd_mode (opposite_main_mfd_locations[mfd_location]);

		if (default_mfd_mode == mfd_mode)
		{
			default_mfd_mode = get_default_main_mfd_mode (mfd_location);

			ASSERT (default_mfd_mode != mfd_mode);
		}

		*mfd_mode_ptr2 = default_mfd_mode;
	}

	*mfd_mode_ptr1 = mfd_mode;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_comanche_side_mfd_mode (comanche_side_mfd_modes mfd_mode, comanche_side_mfd_locations mfd_location)
{
	comanche_side_mfd_modes
		*mfd_mode_ptr1,
		*mfd_mode_ptr2;

	ASSERT (comanche_side_mfd_mode_valid (mfd_mode));

	ASSERT (comanche_side_mfd_location_valid (mfd_location));

	debug_colour_log (DEBUG_COLOUR_AMBER, "%s = %s", comanche_side_mfd_location_names[mfd_location], comanche_side_mfd_mode_names[mfd_mode]);

	mfd_mode_ptr1 = side_mfd_mode_ptrs[mfd_location];

	mfd_mode_ptr2 = opposite_side_mfd_mode_ptrs[mfd_location];

	if ((mfd_mode == COMANCHE_SIDE_MFD_MODE_DAMAGED) && (*mfd_mode_ptr1 == COMANCHE_SIDE_MFD_MODE_OFF))
	{
		mfd_mode = COMANCHE_SIDE_MFD_MODE_OFF;
	}

	if (get_side_mfd_damage (mfd_location))
	{
		if (mfd_mode != COMANCHE_SIDE_MFD_MODE_OFF)
		{
			mfd_mode = COMANCHE_SIDE_MFD_MODE_DAMAGED;
		}
	}

	if ((mfd_mode != COMANCHE_SIDE_MFD_MODE_OFF) && (mfd_mode != COMANCHE_SIDE_MFD_MODE_DAMAGED) && (mfd_mode == *mfd_mode_ptr2))
	{
		*mfd_mode_ptr2 = COMANCHE_SIDE_MFD_MODE_OFF;
	}

	*mfd_mode_ptr1 = mfd_mode;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static comanche_main_mfd_modes get_next_main_mfd_mode (comanche_main_mfd_modes mfd_mode, comanche_main_mfd_locations mfd_location)
{
	comanche_main_mfd_modes
		next_mfd_mode;

	ASSERT (comanche_main_mfd_mode_valid (mfd_mode));

	ASSERT (comanche_main_mfd_location_valid (mfd_location));

	switch (mfd_mode)
	{
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_MODE_OFF:
		////////////////////////////////////////
		{
			next_mfd_mode = get_default_main_mfd_mode (mfd_location);

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_MODE_DAMAGED:
		////////////////////////////////////////
		{
			next_mfd_mode = COMANCHE_MAIN_MFD_MODE_DAMAGED;

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_MODE_GROUND_RADAR:
		////////////////////////////////////////
		{
			next_mfd_mode = COMANCHE_MAIN_MFD_MODE_AIR_RADAR;

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_MODE_AIR_RADAR:
		////////////////////////////////////////
		{
			next_mfd_mode = get_main_mfd_mode_for_eo_sensor ();

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_MODE_FLIR:
		////////////////////////////////////////
		{
			next_mfd_mode = COMANCHE_MAIN_MFD_MODE_TSD;

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_MODE_DTV:
		////////////////////////////////////////
		{
			next_mfd_mode = COMANCHE_MAIN_MFD_MODE_TSD;

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_MODE_DVO:
		////////////////////////////////////////
		{
			next_mfd_mode = COMANCHE_MAIN_MFD_MODE_TSD;

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_MODE_TSD:
		////////////////////////////////////////
		{
			next_mfd_mode = COMANCHE_MAIN_MFD_MODE_ASE;

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_MODE_ASE:
		////////////////////////////////////////
		{
			next_mfd_mode = COMANCHE_MAIN_MFD_MODE_WEAPON;

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_MODE_WEAPON:
		////////////////////////////////////////
		{
			next_mfd_mode = COMANCHE_MAIN_MFD_MODE_SYSTEM;

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_MODE_SYSTEM:
		////////////////////////////////////////
		{
			next_mfd_mode = COMANCHE_MAIN_MFD_MODE_ENGINE;

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_MODE_ENGINE:
		////////////////////////////////////////
		{
			next_mfd_mode = COMANCHE_MAIN_MFD_MODE_FLIGHT;

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_MODE_FLIGHT:
		////////////////////////////////////////
		{
			next_mfd_mode = COMANCHE_MAIN_MFD_MODE_MISSION;

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_MODE_MISSION:
		////////////////////////////////////////
		{
			next_mfd_mode = COMANCHE_MAIN_MFD_MODE_GROUND_RADAR;

			break;
		}
	}

	return (next_mfd_mode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static comanche_main_mfd_modes get_previous_main_mfd_mode (comanche_main_mfd_modes mfd_mode, comanche_main_mfd_locations mfd_location)
{
	comanche_main_mfd_modes
		previous_mfd_mode;

	ASSERT (comanche_main_mfd_mode_valid (mfd_mode));

	ASSERT (comanche_main_mfd_location_valid (mfd_location));

	switch (mfd_mode)
	{
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_MODE_OFF:
		////////////////////////////////////////
		{
			previous_mfd_mode = get_default_main_mfd_mode (mfd_location);

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_MODE_DAMAGED:
		////////////////////////////////////////
		{
			previous_mfd_mode = COMANCHE_MAIN_MFD_MODE_DAMAGED;

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_MODE_GROUND_RADAR:
		////////////////////////////////////////
		{
			previous_mfd_mode = COMANCHE_MAIN_MFD_MODE_MISSION;

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_MODE_AIR_RADAR:
		////////////////////////////////////////
		{
			previous_mfd_mode = COMANCHE_MAIN_MFD_MODE_GROUND_RADAR;

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_MODE_FLIR:
		////////////////////////////////////////
		{
			previous_mfd_mode = COMANCHE_MAIN_MFD_MODE_AIR_RADAR;

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_MODE_DTV:
		////////////////////////////////////////
		{
			previous_mfd_mode = COMANCHE_MAIN_MFD_MODE_AIR_RADAR;

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_MODE_DVO:
		////////////////////////////////////////
		{
			previous_mfd_mode = COMANCHE_MAIN_MFD_MODE_AIR_RADAR;

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_MODE_TSD:
		////////////////////////////////////////
		{
			previous_mfd_mode = get_main_mfd_mode_for_eo_sensor ();

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_MODE_ASE:
		////////////////////////////////////////
		{
			previous_mfd_mode = COMANCHE_MAIN_MFD_MODE_TSD;

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_MODE_WEAPON:
		////////////////////////////////////////
		{
			previous_mfd_mode = COMANCHE_MAIN_MFD_MODE_ASE;

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_MODE_SYSTEM:
		////////////////////////////////////////
		{
			previous_mfd_mode = COMANCHE_MAIN_MFD_MODE_WEAPON;

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_MODE_ENGINE:
		////////////////////////////////////////
		{
			previous_mfd_mode = COMANCHE_MAIN_MFD_MODE_SYSTEM;

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_MODE_FLIGHT:
		////////////////////////////////////////
		{
			previous_mfd_mode = COMANCHE_MAIN_MFD_MODE_ENGINE;

			break;
		}
		////////////////////////////////////////
		case COMANCHE_MAIN_MFD_MODE_MISSION:
		////////////////////////////////////////
		{
			previous_mfd_mode = COMANCHE_MAIN_MFD_MODE_FLIGHT;

			break;
		}
	}

	return (previous_mfd_mode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_next_comanche_main_mfd (comanche_main_mfd_locations mfd_location)
{
	comanche_main_mfd_modes
		*mfd_mode_ptr1,
		*mfd_mode_ptr2,
		next_mfd_mode;

	ASSERT (comanche_main_mfd_location_valid (mfd_location));

	mfd_mode_ptr1 = main_mfd_mode_ptrs[mfd_location];

	mfd_mode_ptr2 = opposite_main_mfd_mode_ptrs[mfd_location];

	next_mfd_mode = get_next_main_mfd_mode (*mfd_mode_ptr1, mfd_location);

	if (next_mfd_mode != COMANCHE_MAIN_MFD_MODE_DAMAGED)
	{
		if (next_mfd_mode == *mfd_mode_ptr2)
		{
			next_mfd_mode = get_next_main_mfd_mode (next_mfd_mode, mfd_location);
		}

		ASSERT (next_mfd_mode != *mfd_mode_ptr2);
	}

	select_comanche_main_mfd_mode (next_mfd_mode, mfd_location);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_previous_comanche_main_mfd (comanche_main_mfd_locations mfd_location)
{
	comanche_main_mfd_modes
		*mfd_mode_ptr1,
		*mfd_mode_ptr2,
		previous_mfd_mode;

	ASSERT (comanche_main_mfd_location_valid (mfd_location));

	mfd_mode_ptr1 = main_mfd_mode_ptrs[mfd_location];

	mfd_mode_ptr2 = opposite_main_mfd_mode_ptrs[mfd_location];

	previous_mfd_mode = get_previous_main_mfd_mode (*mfd_mode_ptr1, mfd_location);

	if (previous_mfd_mode != COMANCHE_MAIN_MFD_MODE_DAMAGED)
	{
		if (previous_mfd_mode == *mfd_mode_ptr2)
		{
			previous_mfd_mode = get_previous_main_mfd_mode (previous_mfd_mode, mfd_location);
		}

		ASSERT (previous_mfd_mode != *mfd_mode_ptr2);
	}

	select_comanche_main_mfd_mode (previous_mfd_mode, mfd_location);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void toggle_comanche_main_mfd_on_off (comanche_main_mfd_locations mfd_location)
{
	ASSERT (comanche_main_mfd_location_valid (mfd_location));

	if (*main_mfd_mode_ptrs[mfd_location] != COMANCHE_MAIN_MFD_MODE_OFF)
	{
		select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_OFF, mfd_location);
	}
	else
	{
		select_next_comanche_main_mfd (mfd_location);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void toggle_comanche_side_mfd_on_off (comanche_side_mfd_locations mfd_location)
{
	ASSERT (comanche_side_mfd_location_valid (mfd_location));

	if (*side_mfd_mode_ptrs[mfd_location] != COMANCHE_SIDE_MFD_MODE_OFF)
	{
		select_comanche_side_mfd_mode (COMANCHE_SIDE_MFD_MODE_OFF, mfd_location);
	}
	else
	{
		select_comanche_side_mfd_mode (get_default_side_mfd_mode (mfd_location), mfd_location);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_next_comanche_pilot_tsd_ase_range (void)
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

void select_next_comanche_co_pilot_tsd_ase_range (void)
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

void select_previous_comanche_pilot_tsd_ase_range (void)
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

void select_previous_comanche_co_pilot_tsd_ase_range (void)
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

void select_next_comanche_pilot_tsd_declutter_level (void)
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

void select_next_comanche_co_pilot_tsd_declutter_level (void)
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

void select_previous_comanche_pilot_tsd_declutter_level (void)
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

void select_previous_comanche_co_pilot_tsd_declutter_level (void)
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

void toggle_comanche_ase_auto_page (void)
{
	set_global_ase_auto_page (get_global_ase_auto_page () ^ 1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void auto_page_comanche_ase_main_mfd (void)
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

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY) && (!comanche_damage.pilot_lh_main_mfd))
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_ASE, COMANCHE_MAIN_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY) && (!comanche_damage.pilot_rh_main_mfd))
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_ASE, COMANCHE_MAIN_MFD_LOCATION_PILOT_RHS);

			return;
		}

		if (pilot_lhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_ASE)
		{
			return;
		}

		if (pilot_rhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_ASE)
		{
			return;
		}

		if ((pilot_lhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_OFF) && (!comanche_damage.pilot_lh_main_mfd))
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_ASE, COMANCHE_MAIN_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if ((pilot_rhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_OFF) && (!comanche_damage.pilot_rh_main_mfd))
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_ASE, COMANCHE_MAIN_MFD_LOCATION_PILOT_RHS);

			return;
		}

		if ((!get_comanche_main_mfd_has_focus (COMANCHE_MAIN_MFD_LOCATION_PILOT_LHS)) && (!comanche_damage.pilot_lh_main_mfd))
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_ASE, COMANCHE_MAIN_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if ((!get_comanche_main_mfd_has_focus (COMANCHE_MAIN_MFD_LOCATION_PILOT_RHS)) && (!comanche_damage.pilot_rh_main_mfd))
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_ASE, COMANCHE_MAIN_MFD_LOCATION_PILOT_RHS);

			return;
		}

		if (!comanche_damage.pilot_lh_main_mfd)
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_ASE, COMANCHE_MAIN_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if (!comanche_damage.pilot_rh_main_mfd)
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_ASE, COMANCHE_MAIN_MFD_LOCATION_PILOT_RHS);

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

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY) && (!comanche_damage.co_pilot_lh_main_mfd))
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_ASE, COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY) && (!comanche_damage.co_pilot_rh_main_mfd))
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_ASE, COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}

		if (co_pilot_lhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_ASE)
		{
			return;
		}

		if (co_pilot_rhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_ASE)
		{
			return;
		}

		if ((co_pilot_lhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_OFF) && (!comanche_damage.co_pilot_lh_main_mfd))
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_ASE, COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if ((co_pilot_rhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_OFF) && (!comanche_damage.co_pilot_rh_main_mfd))
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_ASE, COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}

		if ((!get_comanche_main_mfd_has_focus (COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_LHS)) && (!comanche_damage.co_pilot_lh_main_mfd))
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_ASE, COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if ((!get_comanche_main_mfd_has_focus (COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_RHS)) && (!comanche_damage.co_pilot_rh_main_mfd))
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_ASE, COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}

		if (!comanche_damage.co_pilot_lh_main_mfd)
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_ASE, COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if (!comanche_damage.co_pilot_rh_main_mfd)
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_ASE, COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_comanche_ground_radar_main_mfd (void)
{
	if (get_crew_role () == CREW_ROLE_PILOT)
	{
		////////////////////////////////////////
		//
		// PILOT
		//
		////////////////////////////////////////

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY) && (!comanche_damage.pilot_lh_main_mfd))
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_GROUND_RADAR, COMANCHE_MAIN_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY) && (!comanche_damage.pilot_rh_main_mfd))
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_GROUND_RADAR, COMANCHE_MAIN_MFD_LOCATION_PILOT_RHS);

			return;
		}

		if (pilot_lhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_GROUND_RADAR)
		{
			return;
		}

		if (pilot_rhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_GROUND_RADAR)
		{
			return;
		}

		if (pilot_lhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_AIR_RADAR)
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_GROUND_RADAR, COMANCHE_MAIN_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if (pilot_rhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_AIR_RADAR)
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_GROUND_RADAR, COMANCHE_MAIN_MFD_LOCATION_PILOT_RHS);

			return;
		}

		if ((pilot_lhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_OFF) && (!comanche_damage.pilot_lh_main_mfd))
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_GROUND_RADAR, COMANCHE_MAIN_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if ((pilot_rhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_OFF) && (!comanche_damage.pilot_rh_main_mfd))
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_GROUND_RADAR, COMANCHE_MAIN_MFD_LOCATION_PILOT_RHS);

			return;
		}

		if (!comanche_damage.pilot_lh_main_mfd)
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_GROUND_RADAR, COMANCHE_MAIN_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if (!comanche_damage.pilot_rh_main_mfd)
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_GROUND_RADAR, COMANCHE_MAIN_MFD_LOCATION_PILOT_RHS);

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

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY) && (!comanche_damage.co_pilot_lh_main_mfd))
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_GROUND_RADAR, COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY) && (!comanche_damage.co_pilot_rh_main_mfd))
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_GROUND_RADAR, COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}

		if (co_pilot_lhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_GROUND_RADAR)
		{
			return;
		}

		if (co_pilot_rhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_GROUND_RADAR)
		{
			return;
		}

		if (co_pilot_lhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_AIR_RADAR)
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_GROUND_RADAR, COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if (co_pilot_rhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_AIR_RADAR)
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_GROUND_RADAR, COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}

		if ((co_pilot_lhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_OFF) && (!comanche_damage.co_pilot_lh_main_mfd))
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_GROUND_RADAR, COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if ((co_pilot_rhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_OFF) && (!comanche_damage.co_pilot_rh_main_mfd))
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_GROUND_RADAR, COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}

		if (!comanche_damage.co_pilot_lh_main_mfd)
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_GROUND_RADAR, COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if (!comanche_damage.co_pilot_rh_main_mfd)
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_GROUND_RADAR, COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_comanche_air_radar_main_mfd (void)
{
	if (get_crew_role () == CREW_ROLE_PILOT)
	{
		////////////////////////////////////////
		//
		// PILOT
		//
		////////////////////////////////////////

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY) && (!comanche_damage.pilot_lh_main_mfd))
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_AIR_RADAR, COMANCHE_MAIN_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY) && (!comanche_damage.pilot_rh_main_mfd))
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_AIR_RADAR, COMANCHE_MAIN_MFD_LOCATION_PILOT_RHS);

			return;
		}

		if (pilot_lhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_AIR_RADAR)
		{
			return;
		}

		if (pilot_rhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_AIR_RADAR)
		{
			return;
		}

		if (pilot_lhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_GROUND_RADAR)
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_AIR_RADAR, COMANCHE_MAIN_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if (pilot_rhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_GROUND_RADAR)
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_AIR_RADAR, COMANCHE_MAIN_MFD_LOCATION_PILOT_RHS);

			return;
		}

		if ((pilot_lhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_OFF) && (!comanche_damage.pilot_lh_main_mfd))
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_AIR_RADAR, COMANCHE_MAIN_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if ((pilot_rhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_OFF) && (!comanche_damage.pilot_rh_main_mfd))
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_AIR_RADAR, COMANCHE_MAIN_MFD_LOCATION_PILOT_RHS);

			return;
		}

		if (!comanche_damage.pilot_lh_main_mfd)
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_AIR_RADAR, COMANCHE_MAIN_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if (!comanche_damage.pilot_rh_main_mfd)
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_AIR_RADAR, COMANCHE_MAIN_MFD_LOCATION_PILOT_RHS);

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

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY) && (!comanche_damage.co_pilot_lh_main_mfd))
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_AIR_RADAR, COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY) && (!comanche_damage.co_pilot_rh_main_mfd))
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_AIR_RADAR, COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}

		if (co_pilot_lhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_AIR_RADAR)
		{
			return;
		}

		if (co_pilot_rhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_AIR_RADAR)
		{
			return;
		}

		if (co_pilot_lhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_GROUND_RADAR)
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_AIR_RADAR, COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if (co_pilot_rhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_GROUND_RADAR)
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_AIR_RADAR, COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}

		if ((co_pilot_lhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_OFF) && (!comanche_damage.co_pilot_lh_main_mfd))
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_AIR_RADAR, COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if ((co_pilot_rhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_OFF) && (!comanche_damage.co_pilot_rh_main_mfd))
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_AIR_RADAR, COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}

		if (!comanche_damage.co_pilot_lh_main_mfd)
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_AIR_RADAR, COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if (!comanche_damage.co_pilot_rh_main_mfd)
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_AIR_RADAR, COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_comanche_tads_main_mfd (void)
{
	if (get_crew_role () == CREW_ROLE_PILOT)
	{
		////////////////////////////////////////
		//
		// PILOT
		//
		////////////////////////////////////////

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY) && (!comanche_damage.pilot_lh_main_mfd))
		{
			select_comanche_main_mfd_mode (get_main_mfd_mode_for_eo_sensor (), COMANCHE_MAIN_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY) && (!comanche_damage.pilot_rh_main_mfd))
		{
			select_comanche_main_mfd_mode (get_main_mfd_mode_for_eo_sensor (), COMANCHE_MAIN_MFD_LOCATION_PILOT_RHS);

			return;
		}

		if
		(
			(pilot_lhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_FLIR) ||
			(pilot_lhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_DTV) ||
			(pilot_lhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_DVO)
		)
		{
			select_comanche_main_mfd_mode (get_main_mfd_mode_for_eo_sensor (), COMANCHE_MAIN_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if
		(
			(pilot_rhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_FLIR) ||
			(pilot_rhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_DTV) ||
			(pilot_rhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_DVO)
		)
		{
			select_comanche_main_mfd_mode (get_main_mfd_mode_for_eo_sensor (), COMANCHE_MAIN_MFD_LOCATION_PILOT_RHS);

			return;
		}

		if ((pilot_lhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_OFF) && (!comanche_damage.pilot_lh_main_mfd))
		{
			select_comanche_main_mfd_mode (get_main_mfd_mode_for_eo_sensor (), COMANCHE_MAIN_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if ((pilot_rhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_OFF) && (!comanche_damage.pilot_rh_main_mfd))
		{
			select_comanche_main_mfd_mode (get_main_mfd_mode_for_eo_sensor (), COMANCHE_MAIN_MFD_LOCATION_PILOT_RHS);

			return;
		}

		if (!comanche_damage.pilot_lh_main_mfd)
		{
			select_comanche_main_mfd_mode (get_main_mfd_mode_for_eo_sensor (), COMANCHE_MAIN_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if (!comanche_damage.pilot_rh_main_mfd)
		{
			select_comanche_main_mfd_mode (get_main_mfd_mode_for_eo_sensor (), COMANCHE_MAIN_MFD_LOCATION_PILOT_RHS);

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

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY) && (!comanche_damage.co_pilot_lh_main_mfd))
		{
			select_comanche_main_mfd_mode (get_main_mfd_mode_for_eo_sensor (), COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY) && (!comanche_damage.co_pilot_rh_main_mfd))
		{
			select_comanche_main_mfd_mode (get_main_mfd_mode_for_eo_sensor (), COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}

		if
		(
			(co_pilot_lhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_FLIR) ||
			(co_pilot_lhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_DTV) ||
			(co_pilot_lhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_DVO)
		)
		{
			select_comanche_main_mfd_mode (get_main_mfd_mode_for_eo_sensor (), COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if
		(
			(co_pilot_rhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_FLIR) ||
			(co_pilot_rhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_DTV) ||
			(co_pilot_rhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_DVO)
		)
		{
			select_comanche_main_mfd_mode (get_main_mfd_mode_for_eo_sensor (), COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}

		if ((co_pilot_lhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_OFF) && (!comanche_damage.co_pilot_lh_main_mfd))
		{
			select_comanche_main_mfd_mode (get_main_mfd_mode_for_eo_sensor (), COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if ((co_pilot_rhs_main_mfd_mode == COMANCHE_MAIN_MFD_MODE_OFF) && (!comanche_damage.co_pilot_rh_main_mfd))
		{
			select_comanche_main_mfd_mode (get_main_mfd_mode_for_eo_sensor (), COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}

		if (!comanche_damage.co_pilot_lh_main_mfd)
		{
			select_comanche_main_mfd_mode (get_main_mfd_mode_for_eo_sensor (), COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if (!comanche_damage.co_pilot_rh_main_mfd)
		{
			select_comanche_main_mfd_mode (get_main_mfd_mode_for_eo_sensor (), COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
