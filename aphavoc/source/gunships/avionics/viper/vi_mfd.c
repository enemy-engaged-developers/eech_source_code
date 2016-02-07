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

//mue 070223
void copy_export_mfd(screen* export_left, screen* export_right);

#ifdef DEBUG

static char
	*viper_mfd_mode_names[NUM_VIPER_MFD_MODES] =
	{
		"VIPER_MFD_MODE_OFF",
		"VIPER_MFD_MODE_DAMAGED",
		"VIPER_MFD_MODE_FLIR",
		"VIPER_MFD_MODE_DTV",
		"VIPER_MFD_MODE_TSD",
		"VIPER_MFD_MODE_ASE",
		"VIPER_MFD_MODE_WEAPON",
		"VIPER_MFD_MODE_SYSTEM",
		"VIPER_MFD_MODE_ENGINE",
		"VIPER_MFD_MODE_FLIGHT",
		"VIPER_MFD_MODE_MISSION",
	};

static char
	*viper_mfd_location_names[NUM_VIPER_MFD_LOCATIONS] =
	{
		"VIPER_MFD_LOCATION_PILOT_LHS",
		"VIPER_MFD_LOCATION_PILOT_RHS",
		"VIPER_MFD_LOCATION_CO_PILOT_LHS",
		"VIPER_MFD_LOCATION_CO_PILOT_RHS",
	};

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static viper_mfd_modes
	pilot_lhs_mfd_mode			= VIPER_MFD_MODE_OFF,
	pilot_rhs_mfd_mode			= VIPER_MFD_MODE_OFF,
	co_pilot_lhs_mfd_mode		= VIPER_MFD_MODE_OFF,
	co_pilot_rhs_mfd_mode		= VIPER_MFD_MODE_OFF,
	pilot_dfd_mode		= VIPER_MFD_MODE_OFF,
	co_pilot_dfd_mode		= VIPER_MFD_MODE_OFF;

static viper_mfd_modes
	*mfd_mode_ptrs[NUM_VIPER_MFD_LOCATIONS] =
	{
		&pilot_lhs_mfd_mode,						// VIPER_MFD_LOCATION_PILOT_LHS
		&pilot_rhs_mfd_mode,     				// VIPER_MFD_LOCATION_PILOT_RHS
		&co_pilot_lhs_mfd_mode,  				// VIPER_MFD_LOCATION_CO_PILOT_LHS
		&co_pilot_rhs_mfd_mode,  				// VIPER_MFD_LOCATION_CO_PILOT_RHS
		&pilot_dfd_mode,     				// VIPER_MFD_LOCATION_PILOT_DFD
		&co_pilot_dfd_mode,  				// VIPER_MFD_LOCATION_CO_PILOT_DFD
	};

static viper_mfd_modes
	*opposite_mfd_mode_ptrs[NUM_VIPER_MFD_LOCATIONS] =
	{
		&pilot_rhs_mfd_mode,						// VIPER_MFD_LOCATION_PILOT_LHS
		&pilot_lhs_mfd_mode,     				// VIPER_MFD_LOCATION_PILOT_RHS
		&co_pilot_rhs_mfd_mode,  				// VIPER_MFD_LOCATION_CO_PILOT_LHS
		&co_pilot_lhs_mfd_mode,  				// VIPER_MFD_LOCATION_CO_PILOT_RHS
		&pilot_dfd_mode,  				// VIPER_MFD_LOCATION_PILOT_DFD
		&co_pilot_dfd_mode,  				// VIPER_MFD_LOCATION_CO_PILOT_DFD
	};

static viper_mfd_locations
	opposite_mfd_locations[NUM_VIPER_MFD_LOCATIONS] =
	{
		VIPER_MFD_LOCATION_PILOT_RHS,		// VIPER_MFD_LOCATION_PILOT_LHS
		VIPER_MFD_LOCATION_PILOT_LHS,		// VIPER_MFD_LOCATION_PILOT_RHS
		VIPER_MFD_LOCATION_CO_PILOT_RHS,	// VIPER_MFD_LOCATION_CO_PILOT_LHS
		VIPER_MFD_LOCATION_CO_PILOT_LHS,	// VIPER_MFD_LOCATION_CO_PILOT_RHS
		VIPER_MFD_LOCATION_PILOT_DFD,		// VIPER_MFD_LOCATION_PILOT_DFD
		VIPER_MFD_LOCATION_CO_PILOT_DFD,	// VIPER_MFD_LOCATION_CO_PILOT_DFD
	};

#ifndef OGRE_EE
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
#define MFD_CLEAR_COLOUR		(mfd_colours[10])
#define MFD_COLOUR7				(mfd_colours[11])
#define MFD_COLOUR8				(mfd_colours[12])
#define MFD_COLOUR_BLUE			(mfd_colours[12])
#define MFD_COLOUR_YELLOW		(mfd_colours[13])
#define MFD_COLOUR_DARK_YELLOW	(mfd_colours[14])
#define MFD_COLOUR_RED			(mfd_colours[15])
#define MFD_COLOUR_CYAN			(mfd_colours[16])
#define MFD_COLOUR_DARK_BLUE	(mfd_colours[17])
#define MFD_COLOUR_DARK_RED		(mfd_colours[18])
#define MFD_COLOUR_WHITE    	(mfd_colours[19])
static rgb_colour
   clear_mfd_colour;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define PILOT_LHS_MFD		(1 << 0)
#define PILOT_RHS_MFD		(1 << 1)
#define PILOT_DFD		(1 << 4)
#define CO_PILOT_LHS_MFD	(1 << 5)
#define CO_PILOT_RHS_MFD	(1 << 6)
#define CO_PILOT_DFD	(1 << 9)

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
	*pilot_dfd_texture_screen,
	*co_pilot_lhs_mfd_texture_screen,
	*co_pilot_rhs_mfd_texture_screen,
	*co_pilot_dfd_texture_screen,
	*large_pilot_lhs_mfd_texture_screen,
	*large_pilot_rhs_mfd_texture_screen,
	*large_pilot_dfd_texture_screen,
	*large_co_pilot_lhs_mfd_texture_screen,
	*large_co_pilot_rhs_mfd_texture_screen,
	*large_co_pilot_dfd_texture_screen,
	*small_pilot_lhs_mfd_texture_screen,
	*small_pilot_rhs_mfd_texture_screen,
	*small_pilot_dfd_texture_screen,
	*small_co_pilot_lhs_mfd_texture_screen,
	*small_co_pilot_rhs_mfd_texture_screen,
	*small_co_pilot_dfd_texture_screen,
	*eo_3d_texture_screen,
	*eo_3d_texture_screen_over,
	*full_mfd_texture_screen;

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

#ifndef OGRE_EE
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
	*main_horizon_mask = NULL;

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

static char large_open_right_carat[] =
{
	5,
	9,
	-4,
	0,
	1,0,0,0,0,
	1,1,0,0,0,
	0,1,1,0,0,
	0,0,1,1,0,
	0,0,0,1,1,
	0,0,1,1,0,
	0,1,1,0,0,
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

static char large_open_left_carat[] =
{
	5,
	9,
	0,
	0,
	0,0,0,0,1,
	0,0,0,1,1,
	0,0,1,1,0,
	0,1,1,0,0,
	1,1,0,0,0,
	0,1,1,0,0,
	0,0,1,1,0,
	0,0,0,1,1,
	0,0,0,0,1,
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static viper_mfd_modes get_mfd_mode_for_eo_sensor (void);

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

static void draw_airspeed_scale (void)
{
	float
		v,
		y_centre = 0.1,
		scale_height_ratio = 0.35,
		tick_y_spacing = 0.27,
		airspeed = current_flight_dynamics->velocity_z.value,
		y_adjust,
		mfd_vp_y_min,
		mfd_vp_y_max;

	float x1, x2, x3, x4, x5, x6, x7;

	x1 = 0.41;

	x2 = x1 + 0.04;
	x4 = x1 + 0.13;
	x3 = x4 - 0.02;
	x5 = x4 + 0.02;
	x7 = x1 + 0.26;
	x6 = x7 - 0.04;

	get_2d_float_screen_x_coordinate (-y_centre, &v);

	// draw box around
	draw_2d_line (x1, y_centre + scale_height_ratio, x7, y_centre + scale_height_ratio, MFD_COLOUR1);
	draw_2d_line (x1, y_centre - scale_height_ratio, x7, y_centre - scale_height_ratio, MFD_COLOUR1);
	draw_2d_line (x7, y_centre + scale_height_ratio, x7, y_centre - scale_height_ratio, MFD_COLOUR1);

	mfd_vp_y_min = v - (0.5 * mfd_viewport_size * (scale_height_ratio));
	mfd_vp_y_max = v + (0.5 * mfd_viewport_size * (scale_height_ratio));
	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_vp_y_min, mfd_viewport_x_max, mfd_vp_y_max);

	//
	// draw speed scale
	//

	{
		float scale_step_5 = knots(airspeed * 0.2);
		int int_scale_step_5 = (int) scale_step_5;
		float mod_scale_step_5 = scale_step_5 - (float) int_scale_step_5;

		int tick_type = (int_scale_step_5 % 2) == 0;
		float y = -(5.0 + mod_scale_step_5) * tick_y_spacing;
		int loop;

		int_scale_step_5 -= 5;

		set_mono_font_type (MONO_FONT_TYPE_5X7);
		y_adjust = -2.0;

		for (loop = 0; loop <= 10; loop++)
		{
			if (int_scale_step_5 >= 0)
			{
				if (tick_type == 0)
				{
					float x_adjust;
					char buffer[8];

					draw_2d_line (x1, y, x2, y, MFD_COLOUR1);
					draw_2d_line (x6, y, x7, y, MFD_COLOUR1);

					sprintf(buffer, "%d", int_scale_step_5 * 5);
					x_adjust = get_mono_font_string_width(buffer) / 2;

					set_2d_mono_font_position (x4, y);
					set_mono_font_rel_position (-x_adjust, y_adjust);
					print_mono_font_string(buffer);
				}
				else
					draw_2d_line (x3, y, x5, y, MFD_COLOUR1);
			}

			int_scale_step_5++;
			tick_type = !tick_type;
			y += tick_y_spacing;
		}
	}

	//
	// restore 2D environment
	//

	set_2d_window (mfd_env, MFD_WINDOW_X_MIN, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX, MFD_WINDOW_Y_MAX);
	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

	// draw centre box with digital airspeed

	{
		float
			x_start = x1 + 0.04,
			x_end = x7 + 0.02,
			top = y_centre + 0.05,
			bottom = y_centre - 0.05;

		int u1, u2, v1, v2;

		float x_adjust;
		char buffer[8];

		get_2d_int_screen_coordinates (x_start, top, &u1, &v1);
		get_2d_int_screen_coordinates (x_end, bottom, &u2, &v2);

		// clear background area

		set_block(u1, v1, u2, v2, MFD_BACKGROUND_COLOUR);
		draw_2d_filled_triangle(x1, y_centre, x_start, top, x_start, bottom, MFD_BACKGROUND_COLOUR);

		// draw surrounding box

		draw_2d_line(x_start, top, x_end, top, MFD_COLOUR1);
		draw_2d_line(x_start, bottom, x_end, bottom, MFD_COLOUR1);
		draw_2d_line(x_end, top, x_end, bottom, MFD_COLOUR1);
		draw_2d_line(x1, y_centre, x_start, top, MFD_COLOUR1);
		draw_2d_line(x1, y_centre, x_start, bottom, MFD_COLOUR1);

		// print digital readout

		set_mono_font_type (MONO_FONT_TYPE_7X12);
		y_adjust = -4.0;

		sprintf(buffer, "%3d", (int)knots(airspeed));
		x_adjust = -get_mono_font_string_width(buffer);

		set_2d_mono_font_position (x7, y_centre);
		set_mono_font_rel_position (x_adjust, y_adjust);
		print_mono_font_string(buffer);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_radar_altitude_scale (void)
{
	const float
		y_centre = 0.1,
		box_top = y_centre + 0.05,
		box_bottom = y_centre - 0.05;

	float
		x_start,
		x_end,
		tick_end,
		box_start,
		box_end,
		x_adjust,
		y_adjust = y_centre,
		radar_altitude = bound(feet(current_flight_dynamics->radar_altitude.value), 0.0, 500.0);

	char
		buffer[8];

	x_start = -0.76;

	x_end = x_start + 0.04;
	tick_end = x_end + 0.02;
	box_start = x_start + 0.07;
	box_end = box_start + 0.18;

	// draw box with digital radar altitude readout
	draw_2d_line(box_start, box_top, box_end, box_top, MFD_COLOUR1);
	draw_2d_line(box_start, box_bottom, box_end, box_bottom, MFD_COLOUR1);
	draw_2d_line(box_start, box_top, box_start, box_bottom, MFD_COLOUR1);
	draw_2d_line(box_end, box_top, box_end, box_bottom, MFD_COLOUR1);

	draw_2d_line(x_start, y_centre, box_start, y_centre, MFD_COLOUR1);

	// rate_of_climb
	{
		float roc = bound(current_flight_dynamics->world_velocity_y.value * 0.05, -0.2, 0.2);
		draw_2d_mono_sprite (large_left_carat, x_end, y_centre + roc, MFD_COLOUR1);
	}

	// print digital readout

	set_mono_font_type (MONO_FONT_TYPE_6X10);
	y_adjust = -4.0;

	sprintf(buffer, "%3d", (int)radar_altitude);
	x_adjust = -get_mono_font_string_width(buffer) - 1;

	set_2d_mono_font_position (box_end, y_centre);
	set_mono_font_rel_position (x_adjust, y_adjust);
	print_mono_font_string(buffer);

	// draw altitude scale
	{
		const float
			scale_height = 0.6,
			low_height = scale_height * 0.75,
			high_height = scale_height - low_height,
			low_step = low_height / 3,
			high_step = high_height / 2;

		float
			current_y;

		int i;

		// adjust start of altitude scale
		current_y = y_centre;
		current_y -= bound(radar_altitude, 0.0, 300.0) * low_step * 0.01;
		if (radar_altitude > 300)
			current_y -= bound(radar_altitude - 300.0, 0.0, 200.0) * high_step * 0.01;

		// draw main box
		draw_2d_line(x_start, current_y, tick_end, current_y, MFD_COLOUR1);
		draw_2d_line(x_start, current_y + scale_height, tick_end, current_y + scale_height, MFD_COLOUR1);
		draw_2d_line(x_start, current_y, x_start, current_y + scale_height, MFD_COLOUR1);
		draw_2d_line(x_end, current_y, x_end, current_y + scale_height, MFD_COLOUR1);

		// draw tick marks
		for (i = 0; i < 3; i++)
		{
			current_y += low_step;
			draw_2d_line(x_end, current_y, tick_end, current_y, MFD_COLOUR1);
		}

		current_y += high_step;
		draw_2d_line(x_end, current_y, tick_end, current_y, MFD_COLOUR1);
	}
}

static void draw_barometric_altitude_scale (void)
{
	const float
		y_centre = 0.1,
		box_start = -0.98,
		box_end = box_start + 0.20,
		box_top = y_centre + 0.04,
		box_bottom = y_centre - 0.04,
		x1 = -0.95,
		x2 = x1 + 0.02,
		x3 = x1 + 0.08,
		x5 = x1 + 0.16,
		x4 = x5 - 0.02,
		scale_top = y_centre + 0.35,
		scale_bottom = y_centre - 0.35,
		scale_step = 0.35 / 4.5;

	float
		v,
		mfd_vp_y_min,
		mfd_vp_y_max,
		x_adjust,
		y_adjust = y_centre,
		radar_altitude = feet(current_flight_dynamics->radar_altitude.value),
		barometric_altitude = feet (current_flight_dynamics->barometric_altitude.value),
		ground_level = barometric_altitude - radar_altitude;


	char
		buffer[8];

	int
		u1, u2, v1, v2,
		displayed_altitude = (int)((barometric_altitude + 5) / 10);

	// draw scale
	get_2d_float_screen_x_coordinate (-y_centre, &v);

	mfd_vp_y_min = v - (0.5 * mfd_viewport_size * (scale_top - scale_bottom));
	mfd_vp_y_max = v + (0.5 * mfd_viewport_size * (scale_top - scale_bottom));

	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_vp_y_min, mfd_viewport_x_max, mfd_vp_y_max);

	//
	// draw scale
	//

	{
		float scale_step_5 = barometric_altitude * 0.2;
		int int_scale_step_5 = (int) scale_step_5;
		float mod_scale_step_5 = scale_step_5 - (float) int_scale_step_5;

		int tick_type = (int_scale_step_5 % 2) == 0;
		float y = -(5.0 + mod_scale_step_5) * scale_step;
		int loop;
		float ground_y = -1.0;

		int_scale_step_5 -= 5;

		set_mono_font_type (MONO_FONT_TYPE_5X7);
		y_adjust = -2.0;

		for (loop = 0; loop <= 10; loop++)
		{
			if (int_scale_step_5 * 5 > (ground_level + 5))
			{
				if (tick_type == 0)
				{
					float x_adjust;
					char buffer[8];

					draw_2d_line (x1, y, x2, y, MFD_COLOUR1);
					draw_2d_line (x4, y, x5, y, MFD_COLOUR1);

					sprintf(buffer, "%02d", (int_scale_step_5 * 5) % 100);
					x_adjust = get_mono_font_string_width(buffer) / 2;

					set_2d_mono_font_position (x3, y);
					set_mono_font_rel_position (-x_adjust, y_adjust);
					print_mono_font_string(buffer);
				}
				else
					draw_2d_line (x3 - 0.02, y, x3 + 0.02, y, MFD_COLOUR1);
			}
			else
				ground_y = max(y, ground_y);

			int_scale_step_5++;
			tick_type = !tick_type;
			y += scale_step;
		}

		if (ground_y != -1.0)
			draw_2d_hatched_area(x1, -0.5, x5, ground_y, MFD_COLOUR_RED);
	}

	//
	// restore 2D environment
	//

	set_2d_window (mfd_env, MFD_WINDOW_X_MIN, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX, MFD_WINDOW_Y_MAX);
	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

	// draw box around
	draw_2d_line (x1, scale_top, x5, scale_top, MFD_COLOUR1);
	draw_2d_line (x1, scale_bottom, x5, scale_bottom, MFD_COLOUR1);
	draw_2d_line (x1, scale_top, x1, scale_bottom, MFD_COLOUR1);
	draw_2d_line (x5, scale_top, x5, scale_bottom, MFD_COLOUR1);

	// draw box with digital altitude readout

	// clear background area
	get_2d_int_screen_coordinates (box_start, box_top, &u1, &v1);
	get_2d_int_screen_coordinates (box_end, box_bottom, &u2, &v2);
	set_block(u1, v1, u2, v2, MFD_BACKGROUND_COLOUR);

	// draw surrounding box
	draw_2d_line(box_start, box_top, box_end, box_top, MFD_COLOUR1);
	draw_2d_line(box_start, box_bottom, box_end, box_bottom, MFD_COLOUR1);
	draw_2d_line(box_start, box_top, box_start, box_bottom, MFD_COLOUR1);
	draw_2d_line(box_end, box_top, box_end, box_bottom, MFD_COLOUR1);

	// print digital readout

	set_mono_font_type (MONO_FONT_TYPE_5X7);
	y_adjust = -2.0;

	sprintf(buffer, "%3do", displayed_altitude);
	x_adjust = -get_mono_font_string_width(buffer) - 1;

	set_2d_mono_font_position (box_end, y_centre);
	set_mono_font_rel_position (x_adjust, y_adjust);
	print_mono_font_string(buffer);
}

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
		tick_top,
		tick_bottom,
		tick_datum_top,
		tick_datum_bottom,
		mfd_vp_x_min,
		mfd_vp_x_max,
		x,
		u,
		heading_step_5,
		mod_heading_step_5;

	int
		loop,
		int_heading_step_5,
		tick_type;

	//
	// sort large and small mfd differences
	//

	set_mono_font_type (MONO_FONT_TYPE_5X9);

	x_adjust_single  			= -2.0;
	x_adjust_double  			= -5.0;
	y_adjust			  		= -12.0;

	tick_top                   = 0.85;
	tick_bottom                = 0.85 - 0.075;
	tick_datum_top		  		= tick_top + 0.020;
	tick_datum_bottom	  		= tick_bottom - 0.020;

	//
	// adjust 2D environment for heading scale clipping
	//

	heading_width_ratio		= 0.65;
	heading_tick_x_spacing = heading_width_ratio / 5;
	get_2d_float_screen_x_coordinate (0.0, &u);

	set_2d_window (mfd_env, MFD_WINDOW_X_MIN * heading_width_ratio, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX * heading_width_ratio, MFD_WINDOW_Y_MAX);
	mfd_vp_x_min = u - (mfd_viewport_size * (heading_width_ratio * 0.5));
	mfd_vp_x_max = u + (mfd_viewport_size * (heading_width_ratio * 0.5));
	set_2d_viewport (mfd_env, mfd_vp_x_min, mfd_viewport_y_min, mfd_vp_x_max, mfd_viewport_y_max);

	//
	// draw heading datum tick
	//

	draw_2d_line (0.0, tick_datum_top, 0.0, tick_datum_bottom, MFD_COLOUR1);
	draw_2d_line (-0.025, tick_datum_top, 0.025, tick_datum_top, MFD_COLOUR1);
	draw_2d_line (-0.025, tick_datum_bottom, 0.025, tick_datum_bottom, MFD_COLOUR1);

	draw_2d_line (-1.0, 0.8125, 1.0, 0.8125, MFD_COLOUR1);

	//
	// draw command heading carat
	//

	if (draw_command_heading)
	{
		if (!viper_damage.navigation_computer)
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
					command_heading -= rad (360.0);
				else if (command_heading < rad (-180.0))
					command_heading += rad (360.0);

				if (command_heading < rad(-22.0))
					draw_2d_mono_sprite (large_open_left_carat, -heading_width_ratio, tick_datum_bottom, MFD_COLOUR1);
				else if (command_heading > rad(22.0))
					draw_2d_mono_sprite (large_open_right_carat, heading_width_ratio, tick_datum_bottom, MFD_COLOUR1);
				else
					draw_2d_mono_sprite (large_command_heading_carat, 0.0 + (command_heading * ((heading_width_ratio) / rad (25.0))), tick_datum_bottom, MFD_COLOUR1);
			}
		}
	}

	//
	// draw heading scale
	//

	heading_step_5 = deg (heading * 0.2);
	int_heading_step_5 = (int) heading_step_5;
	mod_heading_step_5 = heading_step_5 - (float) int_heading_step_5;
	int_heading_step_5 -= 5;

	if (int_heading_step_5 < 0)
	{
		int_heading_step_5 += 72;
	}

	tick_type = int_heading_step_5 % 2;
	x = - (5.0 + mod_heading_step_5) * heading_tick_x_spacing;

	for (loop = 0; loop <= 20; loop++)
	{
		draw_2d_line (x, tick_top, x, tick_bottom, MFD_COLOUR1);

		if (tick_type == 0)
		{
			float x_adjust;
			char buffer[8];

			sprintf(buffer, "%03d", int_heading_step_5 * 5);
			x_adjust = get_mono_font_string_width(buffer) / 2;

			set_2d_mono_font_position (x, tick_top);
			set_mono_font_rel_position (-x_adjust, y_adjust);
			print_mono_font_string(buffer);
		}

		int_heading_step_5 = (++int_heading_step_5 == 72) ? 0 : int_heading_step_5;

		tick_type = !tick_type;

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

static void draw_torque_scale(void)
{
	const float
		box_start = -0.94,
		box_end = box_start + 0.2,
		box_top = -0.88,
		box_bottom = box_top - 0.1,
		scale_height = 0.5,
		scale_100_torque = box_top + scale_height * 100.0/120.0,
		scale_50_torque = box_top + scale_height * 50.0 / 120.0,
		scale_top = box_top + scale_height,
		scale_centre = (box_end + box_start) / 2,
		scale_left = box_start + 0.085,
		scale_right = box_end - 0.085,
		tick_left = box_start + 0.07,
		tick_right = box_end - 0.07;

	float
		torque = current_flight_dynamics->combined_engine_torque.value,
		y_torque = box_top + (torque / 120.0) * scale_height,
		x_adjust,
		y_adjust;

	char
		buffer[8];

	int
		u1, u2, v1, v2;

	// draw torque scale
	get_2d_int_screen_coordinates (scale_left, box_top, &u1, &v1);
	if (torque > 100.0)
	{
		get_2d_int_screen_coordinates (scale_right, scale_100_torque, &u2, &v2);
		draw_2d_hatched_area(scale_left, box_top, scale_right+ 0.02, y_torque, MFD_COLOUR_RED);
	}
	else
		get_2d_int_screen_coordinates (scale_right, y_torque, &u2, &v2);

	set_block(u1, v2, u2, v1, MFD_COLOUR1);

	draw_2d_line(scale_centre, y_torque, scale_centre, scale_top, MFD_COLOUR1);

	draw_2d_line(tick_left, scale_50_torque, tick_right, scale_50_torque, MFD_COLOUR1);
	draw_2d_line(tick_left, scale_100_torque, tick_right, scale_100_torque, MFD_COLOUR1);

	// draw surrounding box
	draw_2d_line(box_start, box_top, box_end, box_top, MFD_COLOUR1);
	draw_2d_line(box_start, box_bottom, box_end, box_bottom, MFD_COLOUR1);
	draw_2d_line(box_start, box_top, box_start, box_bottom, MFD_COLOUR1);
	draw_2d_line(box_end, box_top, box_end, box_bottom, MFD_COLOUR1);

	// print digital readout
	set_mono_font_type (MONO_FONT_TYPE_6X10);
	y_adjust = 3.0;

	sprintf(buffer, "%3d", (int)(torque + 0.5));
	x_adjust = -get_mono_font_string_width(buffer) - 1;

	set_2d_mono_font_position (box_end, box_top);
	set_mono_font_rel_position (x_adjust, y_adjust);
	print_mono_font_string(buffer);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_navigation_info(void)
{
	const float
		left_edge = -0.6,
		right_edge = 0.6,
		upper_right = -0.2,
		upper_left = 0.2,
		bottom = -0.98,
		top = -0.78,
		mid_y = -0.88;

	entity
		*wp;

	vec3d
		*gunship_position = get_local_entity_vec3d_ptr (get_gunship_entity (), VEC3D_TYPE_POSITION);

	char
		buffer[80];


	// draw surrounding box
	draw_2d_line(left_edge, mid_y, right_edge, mid_y, MFD_COLOUR1);
	draw_2d_line(left_edge, bottom, right_edge, bottom, MFD_COLOUR1);
	draw_2d_line(left_edge, mid_y, left_edge, bottom, MFD_COLOUR1);
	draw_2d_line(right_edge, mid_y, right_edge, bottom, MFD_COLOUR1);

	draw_2d_line(left_edge, top, upper_right, top, MFD_COLOUR1);
	draw_2d_line(left_edge, top, left_edge, mid_y, MFD_COLOUR1);
	draw_2d_line(upper_right, top, upper_right, mid_y, MFD_COLOUR1);

	draw_2d_line(right_edge, top, upper_left, top, MFD_COLOUR1);
	draw_2d_line(right_edge, top, right_edge, mid_y, MFD_COLOUR1);
	draw_2d_line(upper_left, top, upper_left, mid_y, MFD_COLOUR1);

	set_mono_font_type (MONO_FONT_TYPE_6X10);

	wp = get_local_entity_current_waypoint (get_gunship_entity ());
	if (wp)
	{
		vec3d
			waypoint_position;

		float
			x_adjust,
			waypoint_range;

		get_waypoint_display_position (get_gunship_entity (), wp, &waypoint_position);

		//
		// waypoint id & range
		//

		waypoint_range = get_2d_range (gunship_position, &waypoint_position);
		if (!viper_damage.navigation_computer)
		{
			if (waypoint_range < 1000.0)
				sprintf (buffer, "%c:%dm", get_local_entity_char_value (wp, CHAR_TYPE_TAG), (int) waypoint_range);
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
				sprintf (buffer, "%c:%dKm", get_local_entity_char_value (wp, CHAR_TYPE_TAG), (int) (waypoint_range * (1.0 / 1000.0)));
		}
		else
			sprintf (buffer, "-:--.-");

		set_2d_mono_font_position (left_edge + 0.1, mid_y);
		set_mono_font_rel_position (1.0, 3.0);
		print_mono_font_string (buffer);

		//
		// time to go
		//

		if ((current_flight_dynamics->velocity_z.value > 0.1) && (!viper_damage.navigation_computer))
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
			strcpy (buffer, "--:--:--");

		x_adjust = -get_mono_font_string_width(buffer);
		set_2d_mono_font_position (right_edge - 0.1, mid_y);
		set_mono_font_rel_position (x_adjust, 3.0);
		print_mono_font_string (buffer);
	}

	// sector:
	{
		int sz, sx;
		entity* sec = get_local_sector_entity(gunship_position);

		sx = get_local_entity_int_value(sec, INT_TYPE_X_SECTOR);
		sz = get_local_entity_int_value(sec, INT_TYPE_Z_SECTOR);

		sprintf(buffer, "%d,%d", sx, sz);
		set_2d_mono_font_position (left_edge, top);
		set_mono_font_rel_position (4.0, 3.0);
		print_mono_font_string (buffer);
	}

	// fuel
	{
		float x_adjust;
		float fvalue = bound (kilograms_to_pounds (current_flight_dynamics->fuel_weight.value), 0.0, 9999.0);

		sprintf(buffer, "%d lb", (int)fvalue);
		x_adjust = -get_mono_font_string_width(buffer) - 2.0;

		set_2d_mono_font_position (right_edge, top);
		set_mono_font_rel_position (x_adjust, 3.0);
		print_mono_font_string (buffer);
	}
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

	draw_2d_line (-0.4800, -0.7650,  0.4800, -0.7650, MFD_COLOUR1);
	draw_2d_line (-0.4800, -0.7650, -0.4800, -1.0000, MFD_COLOUR1);
	draw_2d_line ( 0.4800, -0.7650,  0.4800, -1.0000, MFD_COLOUR1);

	x = eo_azimuth / eo_max_azimuth * 0.48;
	y = (eo_elevation / eo_min_elevation * -0.15) - 0.850;

	draw_2d_line (x - 0.0400, y - 0.0300, x + 0.0400, y - 0.0300, MFD_COLOUR1);
	draw_2d_line (x - 0.0400, y + 0.0300, x + 0.0400, y + 0.0300, MFD_COLOUR1);
	draw_2d_line (x - 0.0400, y - 0.0300, x - 0.0400, y + 0.0300, MFD_COLOUR1);
	draw_2d_line (x + 0.0400, y - 0.0300, x + 0.0400, y + 0.0300, MFD_COLOUR1);
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

static int get_undamaged_eo_display_mode (viper_mfd_modes mode)
{
	if ((mode == VIPER_MFD_MODE_FLIR) && (!viper_damage.flir))
	{
		return (TRUE);
	}

	if ((mode == VIPER_MFD_MODE_DTV) && (!viper_damage.dtv))
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

	display_3d_tints
		tint;

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
		case TARGET_ACQUISITION_SYSTEM_DTV:
		{
			light_level = dtv_light_levels[weather_mode][day_segment_type];

			noise_level = dtv_noise_levels[weather_mode][day_segment_type];

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

	set_main_3d_params (tint, light_level, noise_level, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_size, mfd_viewport_size, rad (59.99) * zoom, rad (59.99) * zoom);

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

		get_viper_eo_relative_centred_viewpoint (&centered_eo_vp);

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

	display_3d_tints
		tint;

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
		case TARGET_ACQUISITION_SYSTEM_DTV:
		{
			light_level = dtv_light_levels[weather_mode][day_segment_type];

			noise_level = dtv_noise_levels[weather_mode][day_segment_type];

			tint = DISPLAY_3D_TINT_LLLTV;

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

		get_viper_eo_relative_centred_viewpoint (&centered_eo_vp);

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

	float
		width,
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

	rangefinding_system
		range_finder = get_range_finder();

	ASSERT (eo);

	source = get_gunship_entity ();

	source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

	target = get_local_entity_parent (source, LIST_TYPE_TARGET);

	if (target)
		target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);
	else
		target_position = get_eo_tracking_point();

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

		set_mono_font_rel_position (-width-1.0, y_adjust);

		print_mono_font_string ("MARKED");
	}
// Jabberwock 031107 ends

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
	// draw heading scale
	//
	////////////////////////////////////////

	draw_heading_scale (get_heading_from_attitude_matrix (eo_vp.attitude), FALSE);

	// draw speed and altitude

	{
		float
			speed = knots(current_flight_dynamics->velocity_z.value),
			altitude = min(feet(current_flight_dynamics->radar_altitude.value), 500.0f);

		y_adjust = 0.0;

		sprintf(buffer, "%3d FT", (int)altitude);

		set_2d_mono_font_position (-0.4, -0.7);
		set_mono_font_rel_position (0.0, y_adjust);
		print_mono_font_string (buffer);


		sprintf(buffer, "%3d KTS", (int)speed);
		width = get_mono_font_string_width (buffer);

		set_2d_mono_font_position (0.4, -0.7);
		set_mono_font_rel_position (-width, y_adjust);
		print_mono_font_string (buffer);
	}

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
		vec3d* tracking_point = get_eo_tracking_point();

		if (target || tracking_point)
		{
			{
				if (target)
					get_local_entity_target_point (target, &target_point);
				else
					target_point = *tracking_point;

				tmp = main_vp;

				main_vp = eo_vp;

				visibility = get_position_3d_screen_coordinates (&target_point, &i, &j);

				if ((visibility == OBJECT_3D_COMPLETELY_VISIBLE) || (visibility == OBJECT_3D_PARTIALLY_VISIBLE))
				{
					float x_adjust;
					transform_mfd_screen_co_ords_to_mfd_texture_co_ords (&i, &j);

					get_2d_world_position (i, j, &x, &y);


					//
					// target name
					//

					if (target)
					{
						s = get_target_display_name (target, buffer, FALSE);

						if (s)
						{
							y_adjust = -12.0;
							x_adjust = -get_mono_font_string_width (s) / 2.0;

							if (strcmp(s, "LOW LIGHT") == 0
								|| strcmp(s, "CP/G ID...") == 0)
							{
								set_mono_font_colour (MFD_COLOUR_YELLOW);
							}
							else if (get_local_entity_int_value(get_gunship_entity(), INT_TYPE_SIDE) !=
								get_local_entity_int_value(target, INT_TYPE_SIDE))
							{
								set_mono_font_colour (MFD_COLOUR_RED);
							}
							else
								set_mono_font_colour (MFD_COLOUR1);

							set_2d_mono_font_position (x, y - 0.33);
							set_mono_font_rel_position (x_adjust, y_adjust);

							print_mono_font_string (s);
						}
					}

					set_mono_font_colour (MFD_COLOUR1);

					// target range, speed and bearing
					{
						char
							range_char = 'R';

						float
							target_velocity = 0.0;

						if (range_finder == RANGEFINDER_TRIANGULATION)
							range_char = 'A';
						else
						{
							if (target)
								target_velocity = kilometres_per_hour(get_local_entity_vec3d_magnitude (target, VEC3D_TYPE_MOTION_VECTOR));
							range_char = (range_finder == RANGEFINDER_FCR) ? 'R' : 'L';
						}

						sprintf (buffer, "%c%04d M   %3d KPH", range_char, (int)target_range, (int)target_velocity);

						width = get_mono_font_string_width (buffer) / 2;
						set_2d_mono_font_position (0.0, 0.75);
						set_mono_font_rel_position (-width, 0.0);

						print_mono_font_string (buffer);
					}

					draw_2d_line (x - 0.30, y + 0.20, x - 0.15, y + 0.20, MFD_COLOUR1);
					draw_2d_line (x + 0.30, y + 0.20, x + 0.15, y + 0.20, MFD_COLOUR1);
					draw_2d_line (x - 0.30, y - 0.20, x - 0.15, y - 0.20, MFD_COLOUR1);
					draw_2d_line (x + 0.30, y - 0.20, x + 0.15, y - 0.20, MFD_COLOUR1);
					draw_2d_line (x - 0.30, y + 0.20, x - 0.30, y + 0.15, MFD_COLOUR1);
					draw_2d_line (x - 0.30, y - 0.20, x - 0.30, y - 0.15, MFD_COLOUR1);
					draw_2d_line (x + 0.30, y + 0.20, x + 0.30, y + 0.15, MFD_COLOUR1);
					draw_2d_line (x + 0.30, y - 0.20, x + 0.30, y - 0.15, MFD_COLOUR1);

					if (eo_is_locked())
					{
						draw_2d_line (x - 0.35, y + 0.35, x - 0.6, y + 0.6, MFD_COLOUR1);
						draw_2d_line (x - 0.35, y - 0.35, x - 0.6, y - 0.6, MFD_COLOUR1);
						draw_2d_line (x + 0.35, y + 0.35, x + 0.6, y + 0.6, MFD_COLOUR1);
						draw_2d_line (x + 0.35, y - 0.35, x + 0.6, y - 0.6, MFD_COLOUR1);
					}
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
	if (!viper_damage.flir)
	{
		if (full_screen)
		{
			draw_full_screen_3d_eo_display (&viper_flir, TARGET_ACQUISITION_SYSTEM_FLIR);
		}
		else
		{
			draw_3d_eo_display (&viper_flir, TARGET_ACQUISITION_SYSTEM_FLIR);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_2d_flir_mfd (int valid_3d)
{
	draw_2d_eo_display (&viper_flir, TARGET_ACQUISITION_SYSTEM_FLIR, viper_damage.flir, valid_3d);
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
	if (!viper_damage.dtv)
	{
		if (full_screen)
		{
			draw_full_screen_3d_eo_display (&viper_dtv, TARGET_ACQUISITION_SYSTEM_DTV);
		}
		else
		{
			draw_3d_eo_display (&viper_dtv, TARGET_ACQUISITION_SYSTEM_DTV);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_2d_dtv_mfd (int valid_3d)
{
	draw_2d_eo_display (&viper_dtv, TARGET_ACQUISITION_SYSTEM_DTV, viper_damage.dtv, valid_3d);
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ATARIBABY HEADING SCALE TSD
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_heading_scale_tsd (float heading, int draw_command_heading)
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

	get_2d_float_screen_x_coordinate (0.0, &u);

	set_2d_window (mfd_env, MFD_WINDOW_X_MIN * heading_width_ratio, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX * heading_width_ratio, MFD_WINDOW_Y_MAX);

	mfd_vp_x_min = u - (mfd_viewport_size * (heading_width_ratio * 0.5));

	mfd_vp_x_max = u + (mfd_viewport_size * (heading_width_ratio * 0.5));

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
		if (!viper_damage.navigation_computer)
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


//
// match ground radar radius
//

#define RADIUS	(ROOT2 - 0.05)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_tactical_situation_display_mfd (viper_mfd_locations mfd_location)
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

	ASSERT (viper_mfd_location_valid (mfd_location));

	switch (mfd_location)
	{
		////////////////////////////////////////
		case VIPER_MFD_LOCATION_PILOT_LHS:
		case VIPER_MFD_LOCATION_PILOT_RHS:
		////////////////////////////////////////
		{
			tsd_ase_range						= pilot_tsd_ase_range;
			tsd_declutter_level				= pilot_tsd_declutter_level;
			tsd_threat_line_flash_timer	= &pilot_tsd_threat_line_flash_timer;
			tsd_draw_threat_line_status	= &pilot_tsd_draw_threat_line_status;

			break;
		}
		////////////////////////////////////////
		case VIPER_MFD_LOCATION_CO_PILOT_LHS:
		case VIPER_MFD_LOCATION_CO_PILOT_RHS:
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

	if (tsd_render_mode != TSD_RENDER_CONTOUR_MODE && !viper_damage.navigation_computer)
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
		set_rgb_colour (MFD_COLOUR8,    0,0,0, 255);

	   draw_tsd_terrain_map (mfd_env, -y_origin, tsd_ase_range, scale, source_position, source_heading, FALSE);
	}

	////////////////////////////////////////
	//
	// contour map
	//
	////////////////////////////////////////

//VJ 030423 TSD render mod, added mfd_env
	if (!viper_damage.navigation_computer)
		draw_tsd_contour_map (mfd_env, -y_origin, tsd_ase_range, scale, source_position, source_heading, draw_large_mfd, FALSE);

	////////////////////////////////////////
	//
	// waypoint route
	//
	////////////////////////////////////////

	if (tsd_declutter_level != TSD_DECLUTTER_LEVEL_TARGET && !viper_damage.navigation_computer)
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
						threat_type = (threat_types) get_local_entity_int_value (target, INT_TYPE_THREAT_TYPE);

						if ((threat_type == THREAT_TYPE_SAM) || (threat_type == THREAT_TYPE_AAA))
						{
							target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

							dx = (target_position->x - source_position->x) * scale;
							dy = (target_position->z - source_position->z) * scale;

							air_scan_range = get_local_entity_float_value (target, FLOAT_TYPE_AIR_SCAN_RANGE) * scale;

//VJ 030423 TSD render mod, enemy of viper so red
//VJ 030511 TSD render mod, enemy optional in eech.ini
//VJ 030530 TSD render mod, corrected colour vor original view MFD_COLOUR2
							if (tsd_render_mode == TSD_RENDER_CONTOUR_MODE)
								draw_2d_circle (dx, dy, air_scan_range, MFD_COLOUR2);
							else
								if (command_line_tsd_enemy_colours)
									draw_2d_circle (dx, dy, air_scan_range, MFD_COLOUR4);
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

	// ATARIBABY added heading tape to TSD NAV display
	if (tsd_declutter_level == TSD_DECLUTTER_LEVEL_NAVIGATION || tsd_declutter_level == TSD_DECLUTTER_LEVEL_ALL)
	{
		set_mono_font_colour (MFD_COLOUR1);
		draw_heading_scale_tsd (get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_HEADING), TRUE);
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
			case TARGET_ACQUISITION_SYSTEM_FLIR:
			case TARGET_ACQUISITION_SYSTEM_DTV:
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

			if ((target_range < 1000.0) && (!viper_damage.laser_designator))
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

	if (tsd_declutter_level != TSD_DECLUTTER_LEVEL_TARGET && !viper_damage.navigation_computer)
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

			if (!viper_damage.navigation_computer)
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

			if ((current_flight_dynamics->velocity_z.value > 0.1) && (!viper_damage.navigation_computer))
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

static void draw_aircraft_survivability_equipment_display_mfd (viper_mfd_locations mfd_location)
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

	ASSERT (viper_mfd_location_valid (mfd_location));

	switch (mfd_location)
	{
		////////////////////////////////////////
		case VIPER_MFD_LOCATION_PILOT_LHS:
		case VIPER_MFD_LOCATION_PILOT_RHS:
		////////////////////////////////////////
		{
			tsd_ase_range						= pilot_tsd_ase_range;
			ase_threat_line_flash_timer	= &pilot_ase_threat_line_flash_timer;
			ase_draw_threat_line_status	= &pilot_ase_draw_threat_line_status;

			break;
		}
		////////////////////////////////////////
		case VIPER_MFD_LOCATION_CO_PILOT_LHS:
		case VIPER_MFD_LOCATION_CO_PILOT_RHS:
		////////////////////////////////////////
		{
			tsd_ase_range						= co_pilot_tsd_ase_range;
			ase_threat_line_flash_timer	= &co_pilot_ase_threat_line_flash_timer;
			ase_draw_threat_line_status	= &co_pilot_ase_draw_threat_line_status;

			break;
		}
	}

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
					threat_type = (threat_types) get_local_entity_int_value (threat, INT_TYPE_THREAT_TYPE);

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
		if (viper_damage.infra_red_jammer)
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
		if (viper_damage.infra_red_jammer)
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
		if (viper_damage.radar_jammer)
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
		if (viper_damage.radar_jammer)
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
		if (viper_damage.chaff_dispenser)
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
		if (viper_damage.chaff_dispenser)
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
		if (viper_damage.flare_dispenser)
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
		if (viper_damage.flare_dispenser)
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

static char
	hellfire_missile_data[] =
	{
		15,
		39,
		-7,
		-19,
		0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,
		0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,
		0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,
		0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,
		0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,
		1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,
		1,0,0,1,0,0,0,0,0,0,0,1,0,0,1,
		1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,
		1,0,0,0,0,1,0,0,0,1,0,0,0,0,1,
		1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,
		1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	};

static char
	inverted_hellfire_missile_data[] =
	{
		15,
		39,
		-7,
		-19,
		0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,
		0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,
		0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,
		1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,
		1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,
		1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,
		1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,
		1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,
		1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	};

static char
	sidewinder_missile_data[] =
	{
		15,
		31,
		-7,
		-15,
		0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,
		0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,
		0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,
		0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,
		0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,
		0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,
		0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,
		0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,
		1,0,0,1,0,0,0,0,0,0,0,1,0,0,1,
		1,0,0,1,0,0,0,0,0,0,0,1,0,0,1,
		1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,
		0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,
		0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,
	};

static char
	inverted_sidewinder_missile_data[] =
	{
		15,
		31,
		-7,
		-15,
		0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,
		0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,
		0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,
		0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,
		0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,
		0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,
		0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,
		0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,
		0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,
		0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,
		0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,
		0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,
		0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,
		0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,
		0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,
		0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,
		0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,
		0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,
		0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,
		0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,
		0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,
		0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,
		0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,
		0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,
		0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,
		0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_box(float x1_c, float y1_c, float x2_c, float y2_c, int filled, rgb_colour colour)
{
	float x1, x2, y1, y2;

	get_2d_float_screen_coordinates (x1_c, y1_c, &x1, &y1);
	get_2d_float_screen_coordinates (x2_c, y2_c, &x2, &y2);

	if (filled)
	{
		float x_min = min(x1, x2), x_max = max(x1, x2);
		float y_min = min(y1, y2), y_max = max(y1, y2);

		// set block likes to have its smallest arguments first
		set_block(x_min, y_min, x_max, y_max, colour);
	}
	else
	{
		draw_line(x1, y1, x2, y1, colour);
		draw_line(x1, y1, x1, y2, colour);
		draw_line(x1, y2, x2, y2, colour);
		draw_line(x2, y1, x2, y2, colour);
	}
}

static void draw_weapon_display_mfd (void)
{
	float
		x1, x2, x3, x4, y1, y2, y3;
	float
		forward_wing, rear_wing, wing_tip_left, wing_tip_right;
	char
		s[80];
	const char
		*s_ptr;
	float
		x_adjust;
	int
		number, damaged, selected_weapon, pylon;
	entity_sub_types
		weapon_sub_type;
	int
		selected;

	selected_weapon = get_local_entity_int_value(get_gunship_entity (), INT_TYPE_SELECTED_WEAPON);

	set_mono_font_type (draw_large_mfd ? MONO_FONT_TYPE_7X12 : MONO_FONT_TYPE_5X7);

	get_2d_float_screen_coordinates (-0.25, 0.5, &x1, &y1);
	get_2d_float_screen_coordinates (-0.1, 0.525, &x2, &y2);
	get_2d_float_screen_coordinates (-0.075, 0.6, &x3, &y3);
	get_2d_float_screen_x_coordinate (0.075, &x4);

	draw_line (x1, y1, x2, y2, MFD_COLOUR1);
	draw_line (x2, y2, x3, y3, MFD_COLOUR1);
	draw_line (x3, y3, x4, y3, MFD_COLOUR1);

	get_2d_float_screen_x_coordinate (0.1, &x3);
	get_2d_float_screen_x_coordinate (0.25, &x2);

	draw_line (x4, y3, x3, y2, MFD_COLOUR1);
	draw_line (x3, y2, x2, y1, MFD_COLOUR1);

	// body

	get_2d_float_screen_y_coordinate (-0.1, &forward_wing);
	get_2d_float_screen_y_coordinate (-0.5, &rear_wing);
	get_2d_float_screen_x_coordinate (-0.97, &wing_tip_left);
	get_2d_float_screen_x_coordinate (0.97, &wing_tip_right);

	draw_line (x1, y1, x1, forward_wing, MFD_COLOUR1);
	draw_line (x2, y1, x2, forward_wing, MFD_COLOUR1);
	draw_line (x1, forward_wing, wing_tip_left, forward_wing, MFD_COLOUR1);
	draw_line (x2, forward_wing, wing_tip_right, forward_wing, MFD_COLOUR1);

	draw_line (wing_tip_left, forward_wing, wing_tip_left, rear_wing, MFD_COLOUR1);
	draw_line (wing_tip_right, forward_wing, wing_tip_right, rear_wing, MFD_COLOUR1);
	draw_line (x1, rear_wing, wing_tip_left, rear_wing, MFD_COLOUR1);
	draw_line (x2, rear_wing, wing_tip_right, rear_wing, MFD_COLOUR1);

	get_2d_float_screen_y_coordinate (-0.8, &y2);

	draw_line (x1, rear_wing, x1, y2, MFD_COLOUR1);
	draw_line (x2, rear_wing, x2, y2, MFD_COLOUR1);
	draw_line (x1, y2, x2, y2, MFD_COLOUR1);


	get_local_entity_weapon_hardpoint_info (get_gunship_entity (),
		COBRA_CANNON_TURRET, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON,
		&weapon_sub_type, &number, &damaged);

	selected = (weapon_sub_type == selected_weapon) && !damaged;

	// cannon
	{
		get_2d_float_screen_coordinates (-0.01, 0.575, &x1, &y1);
		get_2d_float_screen_x_coordinate (0.01, &x2);
		get_2d_float_screen_y_coordinate (0.35, &y2);
		get_2d_float_screen_x_coordinate (-0.08, &x3);
		get_2d_float_screen_x_coordinate (0.08, &x4);
		get_2d_float_screen_y_coordinate (0.2, &y3);

		if (selected)
		{
			set_block (x1, y1, x2, y2, MFD_COLOUR1);
			set_block (x3, y2, x4, y3, MFD_COLOUR1);
		}
		else
		{
			draw_line (x1, y1, x2, y1, MFD_COLOUR1);
			draw_line (x1, y1, x1, y2, MFD_COLOUR1);
			draw_line (x2, y1, x2, y2, MFD_COLOUR1);
			draw_line (x1, y2, x3, y2, MFD_COLOUR1);
			draw_line (x2, y2, x4, y2, MFD_COLOUR1);
			draw_line (x3, y2, x3, y3, MFD_COLOUR1);
			draw_line (x4, y2, x4, y3, MFD_COLOUR1);
		}

		get_2d_float_screen_coordinates (-0.2, 0.2, &x1, &y1);
		get_2d_float_screen_coordinates (0.2, 0.05, &x2, &y2);

		set_mono_font_colour (MFD_COLOUR1);
		draw_line (x1, y1, x2, y1, MFD_COLOUR1);
		draw_line (x1, y1, x1, y2, MFD_COLOUR1);
		draw_line (x1, y2, x2, y2, MFD_COLOUR1);
		draw_line (x2, y1, x2, y2, MFD_COLOUR1);

		set_2d_mono_font_position (0.0, 0.15);

		if (!damaged)
			sprintf (s, "%4d", number);
		else
			sprintf (s, "XXXX");

		x_adjust = get_mono_font_string_width (s) * -0.5;
		set_mono_font_rel_position (x_adjust, 0.0);
		print_mono_font_string (s);
	}

	// Chaff
	set_2d_mono_font_position (0.0, -0.2);

	s_ptr = draw_large_mfd ? "CHAFF" : "C";

	x_adjust = get_mono_font_string_width (s_ptr) * -0.5;
	set_mono_font_rel_position (x_adjust, 0.0);
	print_mono_font_string (s_ptr);

	set_2d_mono_font_position (0.0, -0.3);

	get_local_entity_weapon_hardpoint_info (get_gunship_entity (),
		VIPER_LBHS_CHAFF_DISPENSER, ENTITY_SUB_TYPE_WEAPON_CHAFF,
		&weapon_sub_type, &number, &damaged);

	if (!damaged)
		sprintf (s, "%2d", number);
	else
		sprintf (s, "XX");

	x_adjust = get_mono_font_string_width (s) * -0.5;
	set_mono_font_rel_position (x_adjust, 0.0);
	print_mono_font_string (s);


	// Flares
	set_2d_mono_font_position (0.0, -0.45);

	s_ptr = draw_large_mfd ? "FLARE" : "F";

	x_adjust = get_mono_font_string_width (s_ptr) * -0.5;
	set_mono_font_rel_position (x_adjust, 0.0);
	print_mono_font_string (s_ptr);

	set_2d_mono_font_position (0.0, -0.55);


	get_local_entity_weapon_hardpoint_info (get_gunship_entity (),
		VIPER_LBHS_FLARE_DISPENSER, ENTITY_SUB_TYPE_WEAPON_FLARE,
		&weapon_sub_type, &number, &damaged);

	if (!damaged)
		sprintf (s, "%2d", number);
	else
		sprintf (s, "XX");

	x_adjust = get_mono_font_string_width (s) * -0.5;
	set_mono_font_rel_position (x_adjust, 0.0);
	print_mono_font_string (s);

	// auto CM
	set_2d_mono_font_position (0.0, -0.7);

	if (get_global_auto_counter_measures ())
		s_ptr = draw_large_mfd ? "AUTO" : "A";
	else
		s_ptr = draw_large_mfd ? "MAN" : "M";

	x_adjust = get_mono_font_string_width (s_ptr) * -0.5;
	set_mono_font_rel_position (x_adjust, 0.0);
	print_mono_font_string (s_ptr);

	// master arm box

	set_2d_mono_font_position (0.0, 0.89);

	if (selected_weapon != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
	{
		draw_box(-0.25, 0.7, 0.25, 1.0, TRUE, MFD_COLOUR1);

		set_mono_font_colour (MFD_CLEAR_COLOUR);
		s_ptr = draw_large_mfd ? "ARM" : "A";

		draw_box(-0.14, 0.93,-0.09, 1.00, TRUE, MFD_CLEAR_COLOUR);
		draw_box(-0.03, 0.93, 0.03, 1.00, TRUE, MFD_CLEAR_COLOUR);
		draw_box( 0.10, 0.93, 0.15, 1.00, TRUE, MFD_CLEAR_COLOUR);
		draw_box(-0.25, 0.93,-0.19, 0.88, TRUE, MFD_CLEAR_COLOUR);
		draw_box(-0.25, 0.77,-0.19, 0.82, TRUE, MFD_CLEAR_COLOUR);
		draw_box( 0.25, 0.93, 0.19, 0.88, TRUE, MFD_CLEAR_COLOUR);
		draw_box( 0.25, 0.77, 0.19, 0.82, TRUE, MFD_CLEAR_COLOUR);
		draw_box(-0.14, 0.77,-0.09, 0.70, TRUE, MFD_CLEAR_COLOUR);
		draw_box(-0.03, 0.77, 0.03, 0.70, TRUE, MFD_CLEAR_COLOUR);
		draw_box( 0.10, 0.77, 0.15, 0.70, TRUE, MFD_CLEAR_COLOUR);

		draw_box(-0.25, 0.7, 0.25, 1.0, FALSE, MFD_COLOUR1);
	}
	else
	{
		draw_box(-0.25, 0.7, 0.25, 1.0, FALSE, MFD_COLOUR1);
		s_ptr = draw_large_mfd ? "SAFE" : "S";
	}

	x_adjust = get_mono_font_string_width (s_ptr) * -0.5;
	set_mono_font_rel_position (x_adjust, 0.0);
	print_mono_font_string (s_ptr);

	// targeting system
	draw_box(-0.85, 0.8, -0.4, 0.55, FALSE, MFD_COLOUR1);

	set_2d_mono_font_position (-0.63, 0.7);
	set_mono_font_colour (MFD_COLOUR1);

	switch (target_acquisition_system)
	{
	case TARGET_ACQUISITION_SYSTEM_FLIR:
	case TARGET_ACQUISITION_SYSTEM_DTV:
		s_ptr = "TADS";
		break;
	case TARGET_ACQUISITION_SYSTEM_HIDSS:
		s_ptr = "HIDSS";
		break;
	case TARGET_ACQUISITION_SYSTEM_OFF:
	default:
		s_ptr = "NONE";
		break;
	}

	x_adjust = get_mono_font_string_width (s_ptr) * -0.5;
	set_mono_font_rel_position (x_adjust, 0.0);
	print_mono_font_string (s_ptr);

	// range finding system
	draw_box(0.85, 0.8, 0.4, 0.55, FALSE, MFD_COLOUR1);

	set_2d_mono_font_position (0.64, 0.7);

	switch (get_range_finder())
	{
	case RANGEFINDER_FCR:
		s_ptr = "FCR";
		break;
	case RANGEFINDER_LASER:
		s_ptr = "LRF";
		break;
	case RANGEFINDER_TRIANGULATION:
	default:
		s_ptr = "TRNGL";
		break;
	}

	x_adjust = get_mono_font_string_width (s_ptr) * -0.5;
	set_mono_font_rel_position (x_adjust, 0.0);
	print_mono_font_string (s_ptr);

	// launch mode
	draw_box(-0.9, 0.45, -0.45, 0.2, FALSE, MFD_COLOUR1);

	set_2d_mono_font_position (-0.65, 0.35);

	if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_LOCK_ON_AFTER_LAUNCH))
		s_ptr = "LOAL";
	else
		s_ptr = "LOBL";

	x_adjust = get_mono_font_string_width (s_ptr) * -0.5;
	set_mono_font_rel_position (x_adjust, 0.0);
	print_mono_font_string (s_ptr);

	// rocket salve
	draw_box(0.9, 0.45, 0.45, 0.2, FALSE, MFD_COLOUR1);

	set_2d_mono_font_position (0.67, 0.42);
	s_ptr = draw_large_mfd ? "SALVO" : "S";

	x_adjust = get_mono_font_string_width (s_ptr) * -0.5;
	set_mono_font_rel_position (x_adjust, 0.0);
	print_mono_font_string (s_ptr);

	set_2d_mono_font_position (0.67, 0.31);
	if (rocket_salvo_size == ROCKET_SALVO_SIZE_ALL)
		sprintf(s, "ALL");
	else
		sprintf(s, "%2d", rocket_salvo_size);

	x_adjust = get_mono_font_string_width (s) * -0.6;
	set_mono_font_rel_position (x_adjust, 0.0);
	print_mono_font_string (s);

	// weapon pylons
	for (pylon = VIPER_LHS_INNER_PYLON; pylon <= VIPER_RHS_WING_TIP_MOUNT; pylon++)
	{
		float pylon_x, pylon_y;

		pylon_y = -0.35;

		switch (pylon)
		{
		case VIPER_LHS_INNER_PYLON:
			pylon_x = -0.42;
			break;
		case VIPER_RHS_INNER_PYLON:
			pylon_x = 0.42;
			break;
		case VIPER_LHS_OUTER_PYLON:
			pylon_x = -0.74;
			break;
		case VIPER_RHS_OUTER_PYLON:
			pylon_x = 0.74;
			break;
		case VIPER_LHS_WING_TIP_MOUNT:
			pylon_x = -0.97;
			break;
		case VIPER_RHS_WING_TIP_MOUNT:
			pylon_x = 0.97;
			break;
		}

		if (get_local_entity_weapon_hardpoint_info (get_gunship_entity (),
			pylon, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON,
			&weapon_sub_type, &number, &damaged))
		{
			switch (weapon_sub_type)
			{
			case ENTITY_SUB_TYPE_WEAPON_AGM114L_LONGBOW_HELLFIRE:
			case ENTITY_SUB_TYPE_WEAPON_AGM114K_HELLFIRE_II:
			case ENTITY_SUB_TYPE_WEAPON_AGM114R_HELLFIRE_II:
			{
				int i;
				float last_offset;  // is last missile on the left or right side of pylon

				if (pylon == VIPER_LHS_INNER_PYLON || pylon == VIPER_LHS_OUTER_PYLON)
					last_offset = 0.07;
				else
					last_offset = -0.07;

				for (i = 1; i <= number; i++)
				{
					float missile_x, missile_y;

					switch (i)
					{
						case 1:
							missile_x = pylon_x + last_offset;
							missile_y = pylon_y - 0.18;
							break;
						case 2:
							missile_x = pylon_x - last_offset;
							missile_y = pylon_y - 0.18;
							break;
						case 3:
							missile_x = pylon_x + last_offset;
							missile_y = pylon_y + 0.22;
							break;
						case 4:
							missile_x = pylon_x - last_offset;
							missile_y = pylon_y + 0.22;
							break;
						default:
							ASSERT(!"more than 4 hellfires on Viper pylon");
					}

					// remove wing
					get_2d_float_screen_x_coordinate(missile_x + 0.06, &x1);
					get_2d_float_screen_x_coordinate(missile_x - 0.06, &x2);

					if (missile_y > pylon_y)
						draw_line(x1, forward_wing, x2, forward_wing, MFD_CLEAR_COLOUR);
					else
						draw_line(x1, rear_wing, x2, rear_wing, MFD_CLEAR_COLOUR);

					// draw missile
					if ((weapon_sub_type == selected_weapon) && !damaged)
					{
						draw_2d_mono_sprite(inverted_hellfire_missile_data, missile_x, missile_y, MFD_COLOUR1);
						set_mono_font_colour (MFD_CLEAR_COLOUR);
					}
					else
					{
						draw_2d_mono_sprite(hellfire_missile_data, missile_x, missile_y, MFD_COLOUR1);
						set_mono_font_colour (MFD_COLOUR1);
					}
					set_mono_font_type (MONO_FONT_TYPE_7X12);
					set_2d_mono_font_position (missile_x, missile_y-0.05);

					if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_AGM114L_LONGBOW_HELLFIRE)
						sprintf(s, "R");
					else
						sprintf(s, "L");

					x_adjust = get_mono_font_string_width (s) * -0.4;
					set_mono_font_rel_position (x_adjust, 0.0);
					print_mono_font_string (s);
				}
				break;
			}
			case ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255:
			{
				int selected = (weapon_sub_type == selected_weapon) && !damaged;
				rgb_colour text_colour = selected ? MFD_CLEAR_COLOUR : MFD_COLOUR1;

				set_mono_font_colour (text_colour);

				// remove wing under pod
				get_2d_float_screen_x_coordinate(pylon_x + 0.11, &x1);
				get_2d_float_screen_x_coordinate(pylon_x - 0.11, &x2);

				draw_line(x1, forward_wing, x2, forward_wing, MFD_CLEAR_COLOUR);
				draw_line(x1, rear_wing, x2, rear_wing, MFD_CLEAR_COLOUR);

				// draw rocket pod
				get_2d_float_screen_coordinates (pylon_x - 0.11, pylon_y + 0.3, &x1, &y1);
				get_2d_float_screen_coordinates (pylon_x + 0.11, pylon_y - 0.3, &x2, &y2);

				if (selected)
					set_block (x1, y1, x2, y2, MFD_COLOUR1);
				else
				{
					draw_line (x1, y1, x2, y1, MFD_COLOUR1);
					draw_line (x1, y1, x1, y2, MFD_COLOUR1);
					draw_line (x1, y2, x2, y2, MFD_COLOUR1);
					draw_line (x2, y1, x2, y2, MFD_COLOUR1);
				}

				set_mono_font_type (MONO_FONT_TYPE_7X12);
				set_2d_mono_font_position (pylon_x, pylon_y);

				sprintf(s, "MP");

				x_adjust = get_mono_font_string_width (s) * -0.4;
				set_mono_font_rel_position (x_adjust, 0.0);
				print_mono_font_string (s);

				set_2d_mono_font_position (pylon_x, pylon_y - 0.1);
				sprintf(s, "%2d", number);
				x_adjust = get_mono_font_string_width (s) * -0.4;
				set_mono_font_rel_position (x_adjust, 0.0);
				print_mono_font_string (s);

				break;
			}
			case ENTITY_SUB_TYPE_WEAPON_AIM9M_SIDEWINDER:
			{
				int selected = (weapon_sub_type == selected_weapon) && !damaged;
				// Left or right wingtip
				int left_tip = pylon == VIPER_LHS_WING_TIP_MOUNT;
				float tip;

				if (number == 2)
				{
					// remove wing drawing
					if (left_tip)
					{
						tip = wing_tip_left;
						get_2d_float_screen_x_coordinate(-0.93, &x1);
						get_2d_float_screen_y_coordinate(-0.22, &y1);
					}
					else
					{
						tip = wing_tip_right;
						get_2d_float_screen_x_coordinate(0.93, &x1);
						get_2d_float_screen_y_coordinate(-0.22, &y1);
					}
					draw_line(x1, forward_wing, tip, forward_wing, MFD_CLEAR_COLOUR);
					draw_line(tip, forward_wing, tip, y1, MFD_CLEAR_COLOUR);

					// draw missile
					if (selected)
						draw_2d_mono_sprite(inverted_sidewinder_missile_data, pylon_x, pylon_y + 0.25, MFD_COLOUR1);
					else
						draw_2d_mono_sprite(sidewinder_missile_data, pylon_x, pylon_y + 0.25, MFD_COLOUR1);
				}

				if (number >= 1)
				{
					// remove wing drawing
					if (left_tip)
					{
						tip = wing_tip_left;
						get_2d_float_screen_x_coordinate(-0.91, &x1);
						get_2d_float_screen_y_coordinate(-0.27, &y1);
					}
					else
					{
						tip = wing_tip_right;
						get_2d_float_screen_x_coordinate(0.91, &x1);
						get_2d_float_screen_y_coordinate(-0.27, &y1);
					}
					draw_line(x1, rear_wing, tip, rear_wing, MFD_CLEAR_COLOUR);
					draw_line(tip, rear_wing, tip, y1, MFD_CLEAR_COLOUR);

					// draw missile
					if (selected)
						draw_2d_mono_sprite(inverted_sidewinder_missile_data, pylon_x, pylon_y - 0.05, MFD_COLOUR1);
					else
						draw_2d_mono_sprite(sidewinder_missile_data, pylon_x, pylon_y - 0.05, MFD_COLOUR1);
				}
			}
			}

			// if damaged, draw X across pylon
			if (damaged)
			{
				float width, height = 0.7, x1, y1, x2, y2, y_offset = 0.0;

				if (pylon == VIPER_LHS_WING_TIP_MOUNT || pylon == VIPER_RHS_WING_TIP_MOUNT)
				{
					// sidewinders are narrower and drawn more forward than other pylons
					y_offset = 0.1;
					width = 0.125;
				}
				else
					width = 0.25;
				get_2d_float_screen_coordinates(pylon_x - 0.5 * width, pylon_y - 0.5 * height, &x1, &y1);
				get_2d_float_screen_coordinates(pylon_x + 0.5 * width, pylon_y + y_offset + 0.5 * height, &x2, &y2);

				draw_half_thick_line(x1, y1, x2, y2, MFD_COLOUR1);
				draw_half_thick_line(x1, y2, x2, y1, MFD_COLOUR1);
			}
		}
	}
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

static float print_mfd_system_message (char *equipment, char *warning, int fail, float y_adjust)
{
	char
		*status;

	float
		width;

	ASSERT (equipment);

	ASSERT (warning);

	if (fail)
	{
		set_mono_font_colour (MFD_COLOUR_RED);

		status = warning;
	}
	else
	{
		set_mono_font_colour (MFD_COLOUR_WHITE);

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

	y_adjust = print_mfd_system_message ("FLIR", "FAIL", viper_damage.flir, y_adjust);

	y_adjust = print_mfd_system_message ("DTV", "FAIL", viper_damage.dtv, y_adjust);

	y_adjust = print_mfd_system_message ("LASER DESIGNATOR", "FAIL", viper_damage.laser_designator, y_adjust);

	y_adjust = print_mfd_system_message ("RADAR JAMMER", "FAIL", viper_damage.radar_jammer, y_adjust);

	y_adjust = print_mfd_system_message ("IR JAMMER", "FAIL", viper_damage.infra_red_jammer, y_adjust);

	y_adjust = print_mfd_system_message ("NAVIGATION COMPUTER", "FAIL", viper_damage.navigation_computer, y_adjust);

	y_adjust = print_mfd_system_message ("COMMUNICATIONS", "FAIL", viper_damage.communications, y_adjust);

	y_adjust = print_mfd_system_message ("RADAR WARNING SYSTEM", "FAIL", viper_damage.radar_warning_system, y_adjust);

	y_adjust = print_mfd_system_message ("HIDSS", "FAIL", viper_damage.hidss, y_adjust);

	y_adjust = print_mfd_system_message ("PNVS", "FAIL", viper_damage.pnvs, y_adjust);

	y_adjust = print_mfd_system_message ("STABILISER", "FAIL", get_dynamics_damage_type (DYNAMICS_DAMAGE_STABILISER), y_adjust);

	y_adjust = print_mfd_system_message ("MAIN ROTOR", "FAIL", get_dynamics_damage_type (DYNAMICS_DAMAGE_MAIN_ROTOR), y_adjust);

	y_adjust = print_mfd_system_message ("TAIL ROTOR", "DAMAGED", get_dynamics_damage_type (DYNAMICS_DAMAGE_TAIL_ROTOR), y_adjust);

	y_adjust = print_mfd_system_message ("L ENGINE", "DAMAGED", get_dynamics_damage_type (DYNAMICS_DAMAGE_LEFT_ENGINE), y_adjust);

	y_adjust = print_mfd_system_message ("SPU", "DAMAGED", get_dynamics_damage_type (DYNAMICS_DAMAGE_APU), y_adjust);

	y_adjust = print_mfd_system_message ("R ENGINE", "DAMAGED", get_dynamics_damage_type (DYNAMICS_DAMAGE_RIGHT_ENGINE), y_adjust);

	y_adjust = print_mfd_system_message ("HYDRAULIC PRESSURE", "LOW", get_dynamics_damage_type (DYNAMICS_DAMAGE_LOW_HYDRAULICS), y_adjust);

	if (get_dynamics_damage_type (DYNAMICS_DAMAGE_LOW_OIL_PRESSURE))
	{
		y_adjust = print_mfd_system_message ("OIL PRESSURE", "LOW", get_dynamics_damage_type (DYNAMICS_DAMAGE_LOW_OIL_PRESSURE), y_adjust);
	}
	else
	{
		y_adjust = print_mfd_system_message ("OIL PRESSURE", "HIGH", get_dynamics_damage_type (DYNAMICS_DAMAGE_HIGH_OIL_PRESSURE), y_adjust);
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

static void draw_engine_bar(float f_x1, float f_y1, float f_x2, float f_y2, float fvalue)
{
	int x1, x2, y1, y2;

	draw_2d_box(f_x1, f_y1, f_x2, f_y2, FALSE, FALSE, MFD_COLOUR1);

	get_2d_int_screen_coordinates (f_x1, f_y2 + (fvalue * (f_y1 - f_y2)), &x1, &y1);
	get_2d_int_screen_coordinates (f_x2, f_y2, &x2, &y2);
	set_block (x1, y1, x2, y2, MFD_COLOUR1);
}

static void draw_engine_display_mfd (void)
{
	char
		s[80], s2[10];

	int
		ivalue;

	float
		bottom_edge,
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

	set_2d_mono_font_position (-0.7, -0.6);

	x_adjust = get_mono_font_string_width ("FUEL QTY") * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string ("FUEL QTY");

	set_2d_mono_font_position (-0.7, -0.7);

/*	x_adjust = get_mono_font_string_width ("LB") * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string ("LB"); */

	set_2d_mono_font_position (-0.7, -0.7);

	fvalue = bound (kilograms_to_pounds (current_flight_dynamics->fuel_weight.value), 0.0, 9999.0);

	convert_float_to_int (fvalue, &ivalue);

	sprintf (s, "%04d lb", ivalue);

	x_adjust = get_mono_font_string_width (s) * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string (s);

	////////////////////////////////////////

	set_2d_mono_font_position (0.0, -0.6);

	x_adjust = get_mono_font_string_width ("THROTTLE") * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string ("THROTTLE");

//	set_2d_mono_font_position (0.0, -0.7);

	fvalue = bound (current_flight_dynamics->left_engine_n1_rpm.max, 0.0, 110.0);
	convert_float_to_int (fvalue, &ivalue);

	if (ivalue < 60)
		sprintf(s2, "OFF ");
	else if (ivalue == 60)
		sprintf(s2, "IDLE");
	else if (ivalue == 110.0)
		sprintf(s2, "FLY ");
	else
		sprintf(s2, "%03d%%", (ivalue-60) * 2);

	/*
	x_adjust = get_mono_font_string_width (s) * -0.5;
	set_mono_font_rel_position (x_adjust, 0.0);
	print_mono_font_string (s);
	*/

	set_2d_mono_font_position (0.0, -0.7);

	fvalue = bound (current_flight_dynamics->right_engine_n1_rpm.max, 0.0, 110.0);
	convert_float_to_int (fvalue, &ivalue);

	if (ivalue < 60)
		sprintf(s, " %s  OFF ", s2);
	else if (ivalue == 60)
		sprintf(s, " %s  IDLE", s2);
	else if (ivalue == 110.0)
		sprintf(s, " %s  FLY ", s2);
	else
		sprintf(s, " %s  %03d%%", s2, (ivalue-60) * 2);

	x_adjust = get_mono_font_string_width (s) * -0.5;
	set_mono_font_rel_position (x_adjust, 0.0);
	print_mono_font_string (s);

	////////////////////////////////////////

	set_2d_mono_font_position (0.5, -0.6);

	fvalue = bound (current_flight_dynamics->apu_rpm.value + 0.5, 0.0, 100.0);
	convert_float_to_int (fvalue, &ivalue);

	sprintf(s, "SPU %03d%%", ivalue);

	print_mono_font_string (s);

	////////////////////////////////////////

	draw_2d_line (-0.7500 - 0.02, 0.3333, -0.6500 + 0.02, 0.3333, MFD_COLOUR1);
	draw_2d_line (-0.5500 - 0.02, 0.3333, -0.4500 + 0.02, 0.3333, MFD_COLOUR1);
	draw_2d_line (-0.3500 - 0.02, 0.3333, -0.2500 + 0.02, 0.3333, MFD_COLOUR1);
	draw_2d_line (-0.1500 - 0.02, 0.3333, -0.0500 + 0.02, 0.3333, MFD_COLOUR1);

	draw_2d_line ( 0.7500 + 0.00, 0.3333,  0.6500 - 0.02, 0.3333, MFD_COLOUR1);
	draw_2d_line ( 0.5500 + 0.02, 0.3333,  0.4500 - 0.02, 0.3333, MFD_COLOUR1);
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

	// seems to be a compiler bug, have to use a float variable for this value, sending it
	// as a constant as a function parameter will use a double (even though
	// definition is available and says float), which causes later parameters
	// to be wrong
	bottom_edge = (Y_ORG - HEIGHT);

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

	draw_engine_bar(X_ORG - (WIDTH * 0.5), Y_ORG, X_ORG + (WIDTH * 0.5), bottom_edge, fvalue / 120.0);

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

	// seems to be a compiler bug, have to use a float variable for this value, sending it
	// as a constant as a function parameter will use a double (even though
	// definition is available and says const float), which causes later parameters
	// to be wrong
	bottom_edge = (Y_ORG - HEIGHT);

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

	draw_engine_bar(X_ORG - (WIDTH * 0.5), Y_ORG, X_ORG + (WIDTH * 0.5), bottom_edge, fvalue / 120.0);

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

	// seems to be a compiler bug, have to use a float variable for this value, sending it
	// as a constant as a function parameter will use a double (even though
	// definition is available and says const float), which causes later parameters
	// to be wrong
	bottom_edge = (Y_ORG - HEIGHT);

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

	draw_engine_bar(X_ORG - (WIDTH * 0.5), Y_ORG, X_ORG + (WIDTH * 0.5), bottom_edge, fvalue / 120.0);

	#undef X_ORG
	#undef Y_ORG
	#undef WIDTH
	#undef HEIGHT

	//
	// NG1
	//

	#define X_ORG	((float) (-0.4))
	#define Y_ORG	((float) (0.5))
	#define WIDTH	((float) (0.06))
	#define HEIGHT	((float) (1.0))

	// seems to be a compiler bug, have to use a float variable for this value, sending it
	// as a constant as a function parameter will use a double (even though
	// definition is available and says const float), which causes later parameters
	// to be wrong
	bottom_edge = (Y_ORG - HEIGHT);

	set_2d_mono_font_position (X_ORG, Y_ORG + 0.2);

	x_adjust = get_mono_font_string_width ("NG") * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string ("NG");

	////////////////////////////////////////

	fvalue = bound (current_flight_dynamics->left_engine_n1_rpm.value, 0.0, 120.0);

	convert_float_to_int (fvalue, &ivalue);

	sprintf (s, "%03d", ivalue);

	set_2d_mono_font_position (X_ORG, Y_ORG + 0.1);

	x_adjust = get_mono_font_string_width (s) * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string (s);

	////////////////////////////////////////

	draw_engine_bar(X_ORG - (WIDTH * 0.5), Y_ORG, X_ORG + (WIDTH * 0.5), bottom_edge, fvalue / 120.0);

	#undef X_ORG
	#undef Y_ORG
	#undef WIDTH
	#undef HEIGHT

	//
	// NG2
	//

	#define X_ORG	((float) (0.4))
	#define Y_ORG	((float) (0.5))
	#define WIDTH	((float) (0.06))
	#define HEIGHT	((float) (1.0))

	// seems to be a compiler bug, have to use a float variable for this value, sending it
	// as a constant as a function parameter will use a double (even though
	// definition is available and says const float), which causes later parameters
	// to be wrong
	bottom_edge = (Y_ORG - HEIGHT);

	set_2d_mono_font_position (X_ORG, Y_ORG + 0.2);

	x_adjust = get_mono_font_string_width ("NG") * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string ("NG");

	////////////////////////////////////////

	fvalue = bound (current_flight_dynamics->right_engine_n1_rpm.value, 0.0, 120.0);

	convert_float_to_int (fvalue, &ivalue);

	sprintf (s, "%03d", ivalue);

	set_2d_mono_font_position (X_ORG, Y_ORG + 0.1);

	x_adjust = get_mono_font_string_width (s) * -0.5;

	set_mono_font_rel_position (x_adjust, 0.0);

	print_mono_font_string (s);

	////////////////////////////////////////

	draw_engine_bar(X_ORG - (WIDTH * 0.5), Y_ORG, X_ORG + (WIDTH * 0.5), bottom_edge, fvalue / 120.0);

	#undef X_ORG
	#undef Y_ORG
	#undef WIDTH
	#undef HEIGHT

	//
	// TQ1
	//

	#define X_ORG	((float) (-0.6))
	#define Y_ORG	((float) (0.5))
	#define WIDTH	((float) (0.06))
	#define HEIGHT	((float) (1.0))

	// seems to be a compiler bug, have to use a float variable for this value, sending it
	// as a constant as a function parameter will use a double (even though
	// definition is available and says const float), which causes later parameters
	// to be wrong
	bottom_edge = (Y_ORG - HEIGHT);

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

	draw_engine_bar(X_ORG - (WIDTH * 0.5), Y_ORG, X_ORG + (WIDTH * 0.5), bottom_edge, fvalue / 120.0);

	#undef X_ORG
	#undef Y_ORG
	#undef WIDTH
	#undef HEIGHT

	//
	// TQ2
	//

	#define X_ORG	((float) (0.6))
	#define Y_ORG	((float) (0.5))
	#define WIDTH	((float) (0.06))
	#define HEIGHT	((float) (1.0))

	// seems to be a compiler bug, have to use a float variable for this value, sending it
	// as a constant as a function parameter will use a double (even though
	// definition is available and says const float), which causes later parameters
	// to be wrong
	bottom_edge = (Y_ORG - HEIGHT);

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

	draw_engine_bar(X_ORG - (WIDTH * 0.5), Y_ORG, X_ORG + (WIDTH * 0.5), bottom_edge, fvalue / 120.0);

	#undef X_ORG
	#undef Y_ORG
	#undef WIDTH
	#undef HEIGHT

	//
	// TGT1
	//

	#define X_ORG	((float) (-0.8))
	#define Y_ORG	((float) (0.5))
	#define WIDTH	((float) (0.06))
	#define HEIGHT	((float) (0.8333))

	// seems to be a compiler bug, have to use a float variable for this value, sending it
	// as a constant as a function parameter will use a double (even though
	// definition is available and says const float), which causes later parameters
	// to be wrong
	bottom_edge = (Y_ORG - HEIGHT);

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

	draw_engine_bar(X_ORG - (WIDTH * 0.5), Y_ORG, X_ORG + (WIDTH * 0.5), bottom_edge, fvalue / 1000.0);

	#undef X_ORG
	#undef Y_ORG
	#undef WIDTH
	#undef HEIGHT

	//
	// TGT2
	//

	#define X_ORG	((float) (0.8))
	#define Y_ORG	((float) (0.5))
	#define WIDTH	((float) (0.06))
	#define HEIGHT	((float) (0.8333))

	// seems to be a compiler bug, have to use a float variable for this value, sending it
	// as a constant as a function parameter will use a double (even though
	// definition is available and says const float), which causes later parameters
	// to be wrong
	bottom_edge = (Y_ORG - HEIGHT);

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

	draw_engine_bar(X_ORG - (WIDTH * 0.5), Y_ORG, X_ORG + (WIDTH * 0.5), bottom_edge, fvalue / 1000.0);

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
#define PITCH_BAR_X3		((float) (+0.100) * pitch_bar_scale)
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
		int_pitch,
		step_direction,
		loop;

	float
		y_adjust_above_line,
		y_adjust_below_line,
		x_centre,
		y_centre = 0.1,
		size,
		vsize,
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
		sky_colour.red = 44;
		sky_colour.green = 13;
		sky_colour.blue = 116;
		sky_colour.alpha = 255;

		ground_colour.red = 155;
		ground_colour.green = 131;
		ground_colour.blue = 107;
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

	size = 0.4;
	pitch_bar_scale = 0.6;

	vsize = size * 1.5;

	//
	//

	get_2d_float_screen_coordinates (PITCH_DATUM_X, PITCH_DATUM_Y, &u, &v);
	roll = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_ROLL);

//	set_2d_instance_position (mfd_env, PITCH_DATUM_X, PITCH_DATUM_Y - size);

	//
	// set 2D environment
	//

	set_2d_window (mfd_env, MFD_WINDOW_X_MIN * size, MFD_WINDOW_Y_MIN * size, MFD_WINDOW_X_MAX * size, MFD_WINDOW_Y_MAX * size);

	vp_size = mfd_viewport_size * size * 0.5;
	set_2d_viewport (mfd_env, u - (vp_size * 1.5), v - vp_size, u + (vp_size * 1.5), v + (2.0 * vp_size));

	upper_edge = 0.5 * size;
	left_edge = -(size * 0.75);
	right_edge = (size * 0.75);
	lower_edge = -size;

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
					draw_2d_line (-PITCH_BAR_X3, PITCH_BAR_Y3, PITCH_BAR_X3, -PITCH_BAR_Y3, MFD_COLOUR1);

					break;
				}
				////////////////////////////////////////
				default:
				////////////////////////////////////////
				{
					draw_2d_line (-PITCH_BAR_X3, PITCH_BAR_Y3, PITCH_BAR_X3, -PITCH_BAR_Y3, MFD_COLOUR1);

					sprintf (s, "%d0", int_pitch);
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
					draw_2d_line (+PITCH_BAR_X1, +PITCH_BAR_Y1, +PITCH_BAR_X6, +PITCH_BAR_Y6, MFD_COLOUR1);
					draw_2d_line (-PITCH_BAR_X1, +PITCH_BAR_Y1, -PITCH_BAR_X6, +PITCH_BAR_Y6, MFD_COLOUR1);

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
	}

	//
	// restore 2D environment
	//

	reset_2d_instance (mfd_env);

	set_2d_window (mfd_env, MFD_WINDOW_X_MIN, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX, MFD_WINDOW_Y_MAX);

	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

	draw_2d_mono_sprite (main_horizon_mask, x_centre, 0.41 + PITCH_DATUM_Y, MFD_BACKGROUND_COLOUR);

	// pitch scale
	{
		float
			current_y,
			y_fine_height = 0.24,    // -10 to 10 degrees
			y_coarse_height = 0.12,  // above 10 and below 10
			y_fine_step = y_fine_height / 4,
			y_coarse_step = y_coarse_height / 2,
			x_end = -0.41,
			x_half_tick = x_end - 0.02,
			x_tick = x_end - 0.04;

		int i;

		float x_adjust, y_adjust;
		char buffer[8];

		set_mono_font_type (MONO_FONT_TYPE_5X7);
		y_adjust = -2.0;

		current_y = y_centre + y_coarse_height + y_fine_height + y_coarse_step;
		for (i = 3; i >= 1; i--)
		{
			current_y -= y_coarse_step;
			draw_2d_line(x_tick, current_y, x_end, current_y, MFD_COLOUR1);

			sprintf(buffer, "%d", i);
			x_adjust = get_mono_font_string_width(buffer) + 1;

			set_2d_mono_font_position (x_tick, current_y);
			set_mono_font_rel_position (-x_adjust, y_adjust);
			print_mono_font_string(buffer);
		}

		for (i = 0; i < 7; i++)
		{
			current_y -= y_fine_step;
			if ((i % 2) != 0)
				draw_2d_line(x_tick, current_y, x_end, current_y, MFD_COLOUR1);
			else
				draw_2d_line(x_half_tick, current_y, x_end, current_y, MFD_COLOUR1);
		}

		sprintf(buffer, "%d", 0);
		x_adjust = get_mono_font_string_width(buffer) + 1;

		set_2d_mono_font_position (x_tick, y_centre);
		set_mono_font_rel_position (-x_adjust, y_adjust);
		print_mono_font_string(buffer);

		current_y -= y_fine_step;
		for (i = -1; i >= -3; i--)
		{
			draw_2d_line(x_tick, current_y, x_end, current_y, MFD_COLOUR1);

			sprintf(buffer, "%d", i);
			x_adjust = get_mono_font_string_width(buffer) + 1;

			set_2d_mono_font_position (x_tick, current_y);
			set_mono_font_rel_position (-x_adjust, y_adjust);
			print_mono_font_string(buffer);
			current_y -= y_coarse_step;
		}

		// draw marker

		{
			float
				pitch_y;

			pitch_y = bound(deg(pitch), -10.0, 10.0) * y_fine_height * 0.1;
			if (pitch < rad(-10))
				pitch_y += bound(deg(pitch) + 10.0, -20.0, 0.0) * y_coarse_height * 0.05;
			else if (pitch > rad(10))
				pitch_y += bound(deg(pitch) - 10.0, 0.0, 20.0) * y_coarse_height * 0.05;

			pitch_y += y_centre;

			draw_2d_mono_sprite(large_right_carat, x_end, pitch_y, MFD_COLOUR1);
		}
	}


	//
	// roll
	//

	{
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

		set_2d_instance_rotation (mfd_env, rad (45.0));
		draw_2d_line (0.0, -size, 0.0, -size - 0.05, MFD_COLOUR1);
		set_2d_instance_rotation (mfd_env, rad (-45.0));
		draw_2d_line (0.0, -size, 0.0, -size - 0.05, MFD_COLOUR1);

		set_2d_instance_rotation (mfd_env, rad (60.0));
		draw_2d_line (0.0, -size, 0.0, -size - 0.05, MFD_COLOUR1);
		set_2d_instance_rotation (mfd_env, rad (-60.0));
		draw_2d_line (0.0, -size, 0.0, -size - 0.05, MFD_COLOUR1);

		set_2d_instance_rotation (mfd_env, bound (roll, rad(-60.0), rad(60.0)));
		draw_2d_filled_triangle(0.0, -size, -0.035, -size + 0.075, 0.035, -size + 0.075, MFD_COLOUR4);
	}

	//
	// restore 2D environment
	//

	reset_2d_instance (mfd_env);
	set_2d_window (mfd_env, MFD_WINDOW_X_MIN, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX, MFD_WINDOW_Y_MAX);
	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

	// datum
	draw_2d_line(x_centre, 0.0, x_centre + 0.05, -0.05, MFD_COLOUR6);
	draw_2d_line(x_centre, 0.0, x_centre - 0.05, -0.05, MFD_COLOUR6);

	draw_2d_line(x_centre + 0.05, -0.05, x_centre + 0.10, 0.0, MFD_COLOUR6);
	draw_2d_line(x_centre - 0.05, -0.05, x_centre - 0.10, 0.0, MFD_COLOUR6);

	draw_2d_line(x_centre + 0.10, 0.0, x_centre + 0.20, 0.0, MFD_COLOUR6);
	draw_2d_line(x_centre - 0.10, 0.0, x_centre - 0.20, 0.0, MFD_COLOUR6);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_flight_display_mfd (void)
{
	set_mono_font_colour (MFD_COLOUR1);

	draw_pitch_ladder ();
	draw_heading_scale (get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_HEADING), TRUE);

	draw_airspeed_scale();
	draw_radar_altitude_scale();
	draw_barometric_altitude_scale();

	draw_torque_scale();
	display_navigation_info();
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

		set_mono_font_colour (MFD_COLOUR_WHITE);

		draw_line (x_min, y_adjust, x_max, y_adjust, MFD_COLOUR_WHITE);

		y_adjust += 2.0;

		x_adjust = get_mono_font_string_width ("FLIGHT GROUP") * 0.5;

		set_mono_font_position (x_mid - x_adjust, y_adjust);

		print_mono_font_string ("FLIGHT GROUP");

		y_adjust += char_height;

		if (draw_large_mfd)
		{
			y_adjust -= 1.0;
		}

		draw_line (x_min, y_adjust, x_max, y_adjust, MFD_COLOUR_WHITE);

		if (draw_large_mfd)
		{
			y_adjust += 3.0;
		}
		else
		{
			y_adjust += 2.0;
		}

		set_mono_font_colour (MFD_COLOUR_RED);

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

		set_mono_font_colour (MFD_COLOUR_WHITE);

		draw_line (x_min, y_adjust, x_max, y_adjust, MFD_COLOUR_WHITE);

		y_adjust += 2.0;

		x_adjust = get_mono_font_string_width ("MISSION") * 0.5;

		set_mono_font_position (x_mid - x_adjust, y_adjust);

		print_mono_font_string ("MISSION");

		y_adjust += char_height;

		if (draw_large_mfd)
		{
			y_adjust -= 1.0;
		}

		draw_line (x_min, y_adjust, x_max, y_adjust, MFD_COLOUR_WHITE);

		if (draw_large_mfd)
		{
			y_adjust += 3.0;
		}
		else
		{
			y_adjust += 2.0;
		}

		set_mono_font_colour (MFD_COLOUR_RED);

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

	set_mono_font_colour (MFD_COLOUR_WHITE);

	get_2d_float_screen_y_coordinate (-0.9, &y_adjust);

	y_adjust -= 2.0;

	draw_line (x_min, y_adjust, x_max, y_adjust, MFD_COLOUR_WHITE);

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

static void draw_mfd (screen *mfd_screen, viper_mfd_modes* mode, viper_mfd_locations location)
{
	ASSERT (mfd_screen);

	ASSERT (viper_mfd_mode_valid (*mode));

	ASSERT (viper_mfd_location_valid (location));

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
			case VIPER_MFD_MODE_OFF:
			////////////////////////////////////////
			{
				break;
			}
			////////////////////////////////////////
			case VIPER_MFD_MODE_DAMAGED:
			////////////////////////////////////////
			{
				draw_damaged_mfd ();

				break;
			}
			////////////////////////////////////////
			case VIPER_MFD_MODE_FLIR:
			////////////////////////////////////////
			{
				draw_2d_flir_mfd (FALSE);

				break;
			}
			////////////////////////////////////////
			case VIPER_MFD_MODE_DTV:
			////////////////////////////////////////
			{
				draw_2d_dtv_mfd (FALSE);

				break;
			}
			////////////////////////////////////////
			case VIPER_MFD_MODE_TSD:
			////////////////////////////////////////
			{
				draw_tactical_situation_display_mfd (location);

				break;
			}
			////////////////////////////////////////
			case VIPER_MFD_MODE_ASE:
			////////////////////////////////////////
			{
				draw_aircraft_survivability_equipment_display_mfd (location);

				break;
			}
			////////////////////////////////////////
			case VIPER_MFD_MODE_WEAPON:
			////////////////////////////////////////
			{
				draw_weapon_display_mfd ();

				break;
			}
			////////////////////////////////////////
			case VIPER_MFD_MODE_SYSTEM:
			////////////////////////////////////////
			{
				draw_system_display_mfd ();

				break;
			}
			////////////////////////////////////////
			case VIPER_MFD_MODE_ENGINE:
			////////////////////////////////////////
			{
				draw_engine_display_mfd ();

				break;
			}
			////////////////////////////////////////
			case VIPER_MFD_MODE_FLIGHT:
			////////////////////////////////////////
			{
				draw_flight_display_mfd ();

				break;
			}
			////////////////////////////////////////
			case VIPER_MFD_MODE_MISSION:
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

static void initalize_horizon_mask(int width, char** mask)
{
	int i,j;
	char *row;
	char* horizon_mask;
	int height = LARGE_MFD_VIEWPORT_SIZE * 0.62;
	int side_border_width = LARGE_MFD_VIEWPORT_SIZE * 0.175;
	int semi_radius = ((width - 2*side_border_width) / 2);
	int semi_begin = height - 2 - semi_radius;

	if (*mask)
		safe_free(*mask);
	horizon_mask = (char *) safe_malloc((width * height) + 4);
	*mask = horizon_mask;

	horizon_mask[0] = width;
	horizon_mask[1] = height;
	horizon_mask[2] = -(width / 2);
	horizon_mask[3] = 0;

	for (i = 0; i < height; i++)
	{
		row = &horizon_mask[4 + (i*width)];
		for (j = 0; j < width; j++)
		{
			if (i < 2 || i >= semi_begin + semi_radius)
			{
				row[j] = 1;
				continue;
			}

			if (i < semi_begin)
			{
				if (j < side_border_width || j >= (width - side_border_width))
					row[j] = 1;
				else
					row[j] = 0;
			}
			else
			{
				float height_val = ((float)i - semi_begin);
				float x_limit = side_border_width + semi_radius - sqrt((semi_radius * semi_radius) - (height_val * height_val));

				if (j < x_limit || j >= (width - x_limit))
					row[j] = 1;
				else
					row[j] = 0;
			}
		}
	}
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
#endif

void initialise_viper_mfd (void)
{
#ifndef OGRE_EE
	if (command_line_dynamics_engine_startup)
	{
		select_viper_mfd_mode (VIPER_MFD_MODE_OFF, VIPER_MFD_LOCATION_PILOT_LHS);
		select_viper_mfd_mode (VIPER_MFD_MODE_OFF, VIPER_MFD_LOCATION_PILOT_RHS);
	}
	else
	{
		select_viper_mfd_mode (VIPER_MFD_MODE_ASE, VIPER_MFD_LOCATION_PILOT_LHS);
		select_viper_mfd_mode (VIPER_MFD_MODE_TSD, VIPER_MFD_LOCATION_PILOT_RHS);
	}

	select_viper_mfd_mode (VIPER_MFD_MODE_MISSION, VIPER_MFD_LOCATION_CO_PILOT_LHS);
	select_viper_mfd_mode (VIPER_MFD_MODE_TSD, VIPER_MFD_LOCATION_CO_PILOT_RHS);

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
	large_pilot_lhs_mfd_texture_screen = create_user_texture_screen (LARGE_MFD_VIEWPORT_SIZE, LARGE_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 1);
	large_pilot_rhs_mfd_texture_screen = create_user_texture_screen (LARGE_MFD_VIEWPORT_SIZE, LARGE_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 1);
	large_co_pilot_lhs_mfd_texture_screen = create_user_texture_screen (LARGE_MFD_VIEWPORT_SIZE, LARGE_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 1);
	large_co_pilot_rhs_mfd_texture_screen = create_user_texture_screen (LARGE_MFD_VIEWPORT_SIZE, LARGE_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 1);
	large_pilot_dfd_texture_screen = create_user_texture_screen (LARGE_MFD_VIEWPORT_SIZE, LARGE_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 1);

	large_co_pilot_dfd_texture_screen = create_user_texture_screen (LARGE_MFD_VIEWPORT_SIZE, LARGE_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 1);

	small_pilot_lhs_mfd_texture_screen = create_user_texture_screen (SMALL_MFD_VIEWPORT_SIZE, SMALL_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 1);
	small_pilot_rhs_mfd_texture_screen = create_user_texture_screen (SMALL_MFD_VIEWPORT_SIZE, SMALL_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 1);
	small_pilot_dfd_texture_screen = create_user_texture_screen (SMALL_MFD_VIEWPORT_SIZE, SMALL_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 1);

	small_co_pilot_lhs_mfd_texture_screen = create_user_texture_screen (SMALL_MFD_VIEWPORT_SIZE, SMALL_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 1);
	small_co_pilot_rhs_mfd_texture_screen = create_user_texture_screen (SMALL_MFD_VIEWPORT_SIZE, SMALL_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 1);
	small_co_pilot_dfd_texture_screen = create_user_texture_screen (SMALL_MFD_VIEWPORT_SIZE, SMALL_MFD_VIEWPORT_SIZE, TEXTURE_TYPE_SINGLEALPHA, 1);

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

	if (command_line_colour_mfd)
	{
		set_rgb_colour (MFD_COLOUR_BLUE,          60, 160, 255,  255);
		set_rgb_colour (MFD_COLOUR_DARK_BLUE,	   0,   0,  96,  255);
		set_rgb_colour (MFD_COLOUR_YELLOW,       230, 230,  40,  255);
		set_rgb_colour (MFD_COLOUR_DARK_YELLOW,  165, 165,  30,  255);
		set_rgb_colour (MFD_COLOUR_RED,          255,  40,  40,  255);
		set_rgb_colour (MFD_COLOUR_DARK_RED,	 148,   8,   8,  255);
		set_rgb_colour (MFD_COLOUR_CYAN,          60, 255, 230,  255);
		set_rgb_colour (MFD_COLOUR_WHITE,        200, 200, 240,  255);
	}
	else
	{
		set_rgb_colour (MFD_COLOUR_BLUE,           0, 200,   0, 255);
		set_rgb_colour (MFD_COLOUR_DARK_BLUE,      0, 128,   0, 255);
		set_rgb_colour (MFD_COLOUR_YELLOW,         0, 255,   0, 255);
		set_rgb_colour (MFD_COLOUR_DARK_YELLOW,    0, 200,   0, 255);
		set_rgb_colour (MFD_COLOUR_RED,            0, 200,   0, 255);
		set_rgb_colour (MFD_COLOUR_DARK_RED,       0, 128,   0, 255);
		set_rgb_colour (MFD_COLOUR_CYAN,           0, 255,   0, 255);
		set_rgb_colour (MFD_COLOUR_WHITE,          0, 255,   0, 255);
	}

   set_rgb_colour (clear_mfd_colour, 255, 255, 255, 0);

	////////////////////////////////////////
	//
	// weapon display lines
	//
	////////////////////////////////////////

	initalize_horizon_mask(LARGE_MFD_VIEWPORT_SIZE * 3 / 4, &main_horizon_mask);

//VJ 030423 TSd render mod

   Initialise_TSD_render_terrain();

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_viper_mfd (void)
{
#ifndef OGRE_EE
	destroy_2d_environment (mfd_env);

	////////////////////////////////////////

	destroy_screen (large_pilot_lhs_mfd_texture_screen);
	destroy_screen (large_pilot_rhs_mfd_texture_screen);
	destroy_screen (large_pilot_dfd_texture_screen);

	destroy_screen (large_co_pilot_lhs_mfd_texture_screen);
	destroy_screen (large_co_pilot_rhs_mfd_texture_screen);
	destroy_screen (large_co_pilot_dfd_texture_screen);

	destroy_screen (small_pilot_lhs_mfd_texture_screen);
	destroy_screen (small_pilot_rhs_mfd_texture_screen);
	destroy_screen (small_pilot_dfd_texture_screen);

	destroy_screen (small_co_pilot_lhs_mfd_texture_screen);
	destroy_screen (small_co_pilot_rhs_mfd_texture_screen);
	destroy_screen (small_co_pilot_dfd_texture_screen);

	destroy_screen (full_mfd_texture_screen);
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_viper_mfd (void)
{
#ifndef OGRE_EE
	screen *export_left, *export_right;

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
		pilot_dfd_texture_screen = large_pilot_dfd_texture_screen;

		co_pilot_lhs_mfd_texture_screen = large_co_pilot_lhs_mfd_texture_screen;
		co_pilot_rhs_mfd_texture_screen = large_co_pilot_rhs_mfd_texture_screen;
		co_pilot_dfd_texture_screen = large_co_pilot_dfd_texture_screen;

		eo_3d_texture_screen = large_eo_3d_texture_screen;
		eo_3d_texture_screen_over = large_eo_3d_texture_screen_over;
	}
	else
	{
		draw_large_mfd = FALSE;

		pilot_lhs_mfd_texture_screen = small_pilot_lhs_mfd_texture_screen;
		pilot_rhs_mfd_texture_screen = small_pilot_rhs_mfd_texture_screen;
		pilot_dfd_texture_screen = small_pilot_dfd_texture_screen;

		co_pilot_lhs_mfd_texture_screen = small_co_pilot_lhs_mfd_texture_screen;
		co_pilot_rhs_mfd_texture_screen = small_co_pilot_rhs_mfd_texture_screen;
		co_pilot_dfd_texture_screen = small_co_pilot_dfd_texture_screen;

		eo_3d_texture_screen = small_eo_3d_texture_screen;
		eo_3d_texture_screen_over = small_eo_3d_texture_screen_over;
	}

	if (get_crew_role () == CREW_ROLE_PILOT)
	{
		export_left=pilot_lhs_mfd_texture_screen;
		export_right=pilot_rhs_mfd_texture_screen;
	}
	else
	{
		export_left=co_pilot_lhs_mfd_texture_screen;
		export_right=co_pilot_rhs_mfd_texture_screen;
	}

	set_system_texture_screen (pilot_lhs_mfd_texture_screen, TEXTURE_INDEX_COMANCHE_MFD2);
	set_system_texture_screen (pilot_rhs_mfd_texture_screen, TEXTURE_INDEX_COMANCHE_MFD3);
	set_system_texture_screen (pilot_dfd_texture_screen, TEXTURE_INDEX_COMANCHE_TEXT);

	set_system_texture_screen (co_pilot_lhs_mfd_texture_screen, TEXTURE_INDEX_COMANCHE_MFD6);
	set_system_texture_screen (co_pilot_rhs_mfd_texture_screen, TEXTURE_INDEX_COMANCHE_MFD7);
	set_system_texture_screen (co_pilot_dfd_texture_screen, TEXTURE_INDEX_COMANCHE_TEXT2);

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
					PILOT_LHS_MFD |
					PILOT_RHS_MFD |
					PILOT_DFD;
			}
			else
			{
				display_mask =
					CO_PILOT_LHS_MFD |
					CO_PILOT_RHS_MFD |
					CO_PILOT_DFD;
			}

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY:
		////////////////////////////////////////
		{
			display_mask =
				PILOT_LHS_MFD |
				PILOT_RHS_MFD |
				PILOT_DFD;

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY:
		////////////////////////////////////////
		{
			display_mask =
				PILOT_LHS_MFD |
				PILOT_RHS_MFD |
				PILOT_DFD;

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY:
		////////////////////////////////////////
		{
			display_mask =
				CO_PILOT_LHS_MFD |
				CO_PILOT_RHS_MFD |
				CO_PILOT_DFD;

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY:
		////////////////////////////////////////
		{
			display_mask =
				CO_PILOT_LHS_MFD |
				CO_PILOT_RHS_MFD |
				CO_PILOT_DFD;

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			display_mask =
				PILOT_LHS_MFD |
				PILOT_RHS_MFD |
				PILOT_DFD |
				CO_PILOT_LHS_MFD |
				CO_PILOT_RHS_MFD |
				CO_PILOT_DFD;

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

			if (get_undamaged_eo_display_mode (pilot_lhs_mfd_mode) && (display_mask & PILOT_LHS_MFD))
			{
				set_system_texture_screen (eo_3d_texture_screen, TEXTURE_INDEX_COMANCHE_MFD2);
				export_left=eo_3d_texture_screen;

				draw_eo_display = TRUE;
			}

			if (get_undamaged_eo_display_mode (pilot_rhs_mfd_mode) && (display_mask & PILOT_RHS_MFD))
			{
				set_system_texture_screen (eo_3d_texture_screen, TEXTURE_INDEX_COMANCHE_MFD3);
				export_right=eo_3d_texture_screen;

				draw_eo_display = TRUE;
			}

			if (get_undamaged_eo_display_mode (co_pilot_lhs_mfd_mode) && (display_mask & CO_PILOT_LHS_MFD))
			{
				set_system_texture_screen (eo_3d_texture_screen, TEXTURE_INDEX_COMANCHE_MFD6);
				export_left=eo_3d_texture_screen;

				draw_eo_display = TRUE;
			}

			if (get_undamaged_eo_display_mode (co_pilot_rhs_mfd_mode) && (display_mask & CO_PILOT_RHS_MFD))
			{
				set_system_texture_screen (eo_3d_texture_screen, TEXTURE_INDEX_COMANCHE_MFD7);
				export_right=eo_3d_texture_screen;

				draw_eo_display = TRUE;
			}

			if (draw_eo_display)
			{
				switch (get_mfd_mode_for_eo_sensor ())
				{
					case VIPER_MFD_MODE_FLIR:
					{
						draw_3d_flir_mfd (FALSE);

						break;
					}
					case VIPER_MFD_MODE_DTV:
					{
						draw_3d_dtv_mfd (FALSE);

						break;
					}
				}

				set_active_screen (eo_3d_texture_screen_over);

				if (lock_screen (eo_3d_texture_screen_over))
				{
					draw_mfd_layout_grid ();

					switch (get_mfd_mode_for_eo_sensor ())
					{
						case VIPER_MFD_MODE_FLIR:
						{
							draw_2d_flir_mfd (TRUE);

							break;
						}
						case VIPER_MFD_MODE_DTV:
						{
							draw_2d_dtv_mfd (TRUE);

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

	if (display_mask & PILOT_LHS_MFD)
	{
		draw_mfd (pilot_lhs_mfd_texture_screen, &pilot_lhs_mfd_mode, VIPER_MFD_LOCATION_PILOT_LHS);
	}

	if (display_mask & PILOT_RHS_MFD)
	{
		draw_mfd (pilot_rhs_mfd_texture_screen, &pilot_rhs_mfd_mode, VIPER_MFD_LOCATION_PILOT_RHS);
	}

	if (display_mask & PILOT_DFD)
	{
		draw_mfd (pilot_dfd_texture_screen, &pilot_dfd_mode, VIPER_MFD_LOCATION_PILOT_DFD);
	}

	if (display_mask & CO_PILOT_LHS_MFD)
	{
		draw_mfd (co_pilot_lhs_mfd_texture_screen, &co_pilot_lhs_mfd_mode, VIPER_MFD_LOCATION_CO_PILOT_LHS);
	}

	if (display_mask & CO_PILOT_RHS_MFD)
	{
		draw_mfd (co_pilot_rhs_mfd_texture_screen, &co_pilot_rhs_mfd_mode, VIPER_MFD_LOCATION_CO_PILOT_RHS);
	}

	if (display_mask & CO_PILOT_DFD)
	{
		draw_mfd (co_pilot_dfd_texture_screen, &co_pilot_dfd_mode, VIPER_MFD_LOCATION_CO_PILOT_DFD);
	}

	if(command_line_export_mfd)
		copy_export_mfd(export_left,export_right);
#endif
}

#ifndef OGRE_EE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
void draw_viper_full_screen_display (void)
{
	viper_mfd_modes
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

	mfd_screen_x_scale = 256.0 / mfd_screen_width;
	mfd_screen_y_scale = 256.0 / mfd_screen_height;

	switch (mode)
	{
		case VIPER_MFD_MODE_FLIR:
		{
			draw_3d_flir_mfd (TRUE);

			break;
		}
		case VIPER_MFD_MODE_DTV:
		{
			draw_3d_dtv_mfd (TRUE);

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
			case VIPER_MFD_MODE_FLIR:
			{
				draw_2d_flir_mfd (TRUE);

				break;
			}
			case VIPER_MFD_MODE_DTV:
			{
				draw_2d_dtv_mfd (TRUE);

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

static void draw_overlaid_mfd (screen *mfd_screen, viper_mfd_modes mode, viper_mfd_locations location)
{
	float
		border_size;

	ASSERT (mfd_screen);

	ASSERT (viper_mfd_mode_valid (mode));

	ASSERT (viper_mfd_location_valid (location));

	if (mode == VIPER_MFD_MODE_OFF)
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
		case VIPER_MFD_LOCATION_PILOT_LHS:
		case VIPER_MFD_LOCATION_CO_PILOT_LHS:
		////////////////////////////////////////
		{
			mfd_screen_x_min = border_size;
			mfd_screen_y_min = full_screen_height - border_size - mfd_screen_height;

			break;
		}
		////////////////////////////////////////
		case VIPER_MFD_LOCATION_PILOT_RHS:
		case VIPER_MFD_LOCATION_CO_PILOT_RHS:
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
	// draw MFD display
	//
	////////////////////////////////////////

	switch (mode)
	{
		////////////////////////////////////////
		case VIPER_MFD_MODE_OFF:
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
		case VIPER_MFD_MODE_DAMAGED:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_screen);

			if (lock_screen (mfd_screen))
			{
				set_block (0, 0, int_mfd_viewport_size - 1, int_mfd_viewport_size - 1, clear_mfd_colour);

				draw_mfd_layout_grid ();

				draw_damaged_mfd ();

				unlock_screen (mfd_screen);
			}

			break;
		}
		////////////////////////////////////////
		case VIPER_MFD_MODE_FLIR:
		////////////////////////////////////////
		{
			if (!viper_damage.flir)
			{
				draw_full_screen_3d_eo_display (&viper_flir, TARGET_ACQUISITION_SYSTEM_FLIR);
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
		case VIPER_MFD_MODE_DTV:
		////////////////////////////////////////
		{
			if (!viper_damage.dtv)
			{
				draw_full_screen_3d_eo_display (&viper_dtv, TARGET_ACQUISITION_SYSTEM_DTV);
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

				draw_2d_dtv_mfd (TRUE);

				unlock_screen (mfd_screen);
			}

			set_pilots_full_screen_params (FALSE);

			break;
		}
		////////////////////////////////////////
		case VIPER_MFD_MODE_TSD:
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

				draw_mfd_layout_grid ();

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

				unlock_screen (mfd_screen);
			}

			break;
		}
		////////////////////////////////////////
		case VIPER_MFD_MODE_ASE:
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
		case VIPER_MFD_MODE_WEAPON:
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
		case VIPER_MFD_MODE_SYSTEM:
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
		case VIPER_MFD_MODE_ENGINE:
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
		case VIPER_MFD_MODE_FLIGHT:
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

				draw_mfd_layout_grid ();

				store_background_colour = MFD_BACKGROUND_COLOUR;

				set_rgb_colour (MFD_BACKGROUND_COLOUR, 255, 255, 255, 0);

				draw_flight_display_mfd ();

				MFD_BACKGROUND_COLOUR = store_background_colour;

				unlock_screen (mfd_screen);
			}

			break;
		}
		////////////////////////////////////////
		case VIPER_MFD_MODE_MISSION:
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
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

void draw_overlaid_viper_mfd (void)
{
#ifndef OGRE_EE
	////////////////////////////////////////
	//
	// SELECT LARGE OR SMALL MFD TEXTURES
	//
	////////////////////////////////////////

//   if (application_video_width >= 1280)
   {
      draw_large_mfd = TRUE;

      pilot_lhs_mfd_texture_screen = large_pilot_lhs_mfd_texture_screen;
      pilot_rhs_mfd_texture_screen = large_pilot_rhs_mfd_texture_screen;
      pilot_dfd_texture_screen = large_pilot_dfd_texture_screen;

      co_pilot_lhs_mfd_texture_screen = large_co_pilot_lhs_mfd_texture_screen;
      co_pilot_rhs_mfd_texture_screen = large_co_pilot_rhs_mfd_texture_screen;
      co_pilot_dfd_texture_screen = large_co_pilot_dfd_texture_screen;

      eo_3d_texture_screen = large_eo_3d_texture_screen;
      eo_3d_texture_screen_over = large_eo_3d_texture_screen_over;
   }
/*   else
   {
      draw_large_mfd = FALSE;

      pilot_lhs_mfd_texture_screen = small_pilot_lhs_mfd_texture_screen;
      pilot_rhs_mfd_texture_screen = small_pilot_rhs_mfd_texture_screen;
      pilot_dfd_texture_screen = small_pilot_dfd_texture_screen;

      co_pilot_lhs_mfd_texture_screen = small_co_pilot_lhs_mfd_texture_screen;
      co_pilot_rhs_mfd_texture_screen = small_co_pilot_rhs_mfd_texture_screen;
      co_pilot_dfd_texture_screen = small_co_pilot_dfd_texture_screen;

      eo_3d_texture_screen = small_eo_3d_texture_screen;
      eo_3d_texture_screen_over = small_eo_3d_texture_screen_over;
   }
*/
	set_system_texture_screen (pilot_lhs_mfd_texture_screen, TEXTURE_INDEX_COMANCHE_MFD2);
	set_system_texture_screen (pilot_rhs_mfd_texture_screen, TEXTURE_INDEX_COMANCHE_MFD3);
	set_system_texture_screen (pilot_dfd_texture_screen, TEXTURE_INDEX_COMANCHE_TEXT);

	set_system_texture_screen (co_pilot_lhs_mfd_texture_screen, TEXTURE_INDEX_COMANCHE_MFD6);
	set_system_texture_screen (co_pilot_rhs_mfd_texture_screen, TEXTURE_INDEX_COMANCHE_MFD7);
	set_system_texture_screen (co_pilot_dfd_texture_screen, TEXTURE_INDEX_COMANCHE_TEXT2);

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

	mfd_viewport_x_max = mfd_viewport_size;

	mfd_viewport_y_max = mfd_viewport_size;

	////////////////////////////////////////
	//
	// DRAW DISPLAYS
	//
	////////////////////////////////////////

	if (display_mask & PILOT_LHS_MFD)
	{
      draw_overlaid_mfd (pilot_lhs_mfd_texture_screen, pilot_lhs_mfd_mode, VIPER_MFD_LOCATION_PILOT_LHS);
	}

	if (display_mask & PILOT_RHS_MFD)
	{
      draw_overlaid_mfd (pilot_rhs_mfd_texture_screen, pilot_rhs_mfd_mode, VIPER_MFD_LOCATION_PILOT_RHS);
	}

	if (display_mask & CO_PILOT_LHS_MFD)
	{
      draw_overlaid_mfd (co_pilot_lhs_mfd_texture_screen, co_pilot_lhs_mfd_mode, VIPER_MFD_LOCATION_CO_PILOT_LHS);
	}

	if (display_mask & CO_PILOT_RHS_MFD)
	{
      draw_overlaid_mfd (co_pilot_rhs_mfd_texture_screen, co_pilot_rhs_mfd_mode, VIPER_MFD_LOCATION_CO_PILOT_RHS);
	}
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

int get_viper_mfd_has_focus (viper_mfd_locations mfd_location)
{
	int
		result;

	viper_mfd_modes
		mfd_mode;

	ASSERT (viper_mfd_location_valid (mfd_location));

	mfd_mode = *mfd_mode_ptrs[mfd_location];

	switch (target_acquisition_system)
	{
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_FLIR:
		////////////////////////////////////////
		{
			result = (mfd_mode == VIPER_MFD_MODE_FLIR);

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_DTV:
		////////////////////////////////////////
		{
			result = (mfd_mode == VIPER_MFD_MODE_DTV);

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

static viper_mfd_modes get_mfd_mode_for_eo_sensor (void)
{
	viper_mfd_modes
		mfd_mode;

	if (eo_sensor == TARGET_ACQUISITION_SYSTEM_FLIR)
	{
		mfd_mode = VIPER_MFD_MODE_FLIR;
	}
	else if (eo_sensor == TARGET_ACQUISITION_SYSTEM_DTV)
	{
		mfd_mode = VIPER_MFD_MODE_DTV;
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

static viper_mfd_modes get_default_mfd_mode (viper_mfd_locations mfd_location)
{
	viper_mfd_modes
		mfd_mode;

	ASSERT (viper_mfd_location_valid (mfd_location));

	switch (mfd_location)
	{
		////////////////////////////////////////
		case VIPER_MFD_LOCATION_PILOT_LHS:
		////////////////////////////////////////
		{
			mfd_mode = VIPER_MFD_MODE_ENGINE;

			break;
		}
		////////////////////////////////////////
		case VIPER_MFD_LOCATION_PILOT_RHS:
		////////////////////////////////////////
		{
			mfd_mode = VIPER_MFD_MODE_TSD;

			break;
		}
		////////////////////////////////////////
		case VIPER_MFD_LOCATION_CO_PILOT_LHS:
		////////////////////////////////////////
		{
			mfd_mode = VIPER_MFD_MODE_ENGINE;

			break;
		}
		////////////////////////////////////////
		case VIPER_MFD_LOCATION_CO_PILOT_RHS:
		////////////////////////////////////////
		{
			mfd_mode = VIPER_MFD_MODE_TSD;

			break;
		}
		////////////////////////////////////////
		case VIPER_MFD_LOCATION_PILOT_DFD:
		////////////////////////////////////////
		{
			mfd_mode = VIPER_MFD_MODE_FLIGHT;

			break;
		}
		////////////////////////////////////////
		case VIPER_MFD_LOCATION_CO_PILOT_DFD:
		////////////////////////////////////////
		{
			mfd_mode = VIPER_MFD_MODE_MISSION;

			break;
		}
	}

	return (mfd_mode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_mfd_damage (viper_mfd_locations mfd_location)
{
	int
		damage;

	ASSERT (viper_mfd_location_valid (mfd_location));

	switch (mfd_location)
	{
		////////////////////////////////////////
		case VIPER_MFD_LOCATION_PILOT_LHS:
		////////////////////////////////////////
		{
			damage = viper_damage.pilot_lh_mfd;

			break;
		}
		////////////////////////////////////////
		case VIPER_MFD_LOCATION_PILOT_RHS:
		////////////////////////////////////////
		{
			damage = viper_damage.pilot_rh_mfd;

			break;
		}
		////////////////////////////////////////
		case VIPER_MFD_LOCATION_CO_PILOT_LHS:
		////////////////////////////////////////
		{
			damage = viper_damage.co_pilot_lh_mfd;

			break;
		}
		////////////////////////////////////////
		case VIPER_MFD_LOCATION_CO_PILOT_RHS:
		////////////////////////////////////////
		{
			damage = viper_damage.co_pilot_rh_mfd;

			break;
		}
		////////////////////////////////////////
		case VIPER_MFD_LOCATION_PILOT_DFD:
		////////////////////////////////////////
		{
			damage = viper_damage.pilot_dfd;

			break;
		}
		////////////////////////////////////////
		case VIPER_MFD_LOCATION_CO_PILOT_DFD:
		////////////////////////////////////////
		{
			damage = viper_damage.co_pilot_dfd;

			break;
		}
	}

	return (damage);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_viper_mfd_mode (viper_mfd_modes mfd_mode, viper_mfd_locations mfd_location)
{
	viper_mfd_modes
		*mfd_mode_ptr1,
		*mfd_mode_ptr2,
		default_mfd_mode;

	ASSERT (viper_mfd_mode_valid (mfd_mode));

	ASSERT (viper_mfd_location_valid (mfd_location));

	debug_colour_log (DEBUG_COLOUR_AMBER, "%s = %s", viper_mfd_location_names[mfd_location], viper_mfd_mode_names[mfd_mode]);

	mfd_mode_ptr1 = mfd_mode_ptrs[mfd_location];

	mfd_mode_ptr2 = opposite_mfd_mode_ptrs[mfd_location];

	if ((mfd_mode == VIPER_MFD_MODE_DAMAGED) && (*mfd_mode_ptr1 == VIPER_MFD_MODE_OFF))
	{
		mfd_mode = VIPER_MFD_MODE_OFF;
	}

	if (get_mfd_damage (mfd_location))
	{
		if (mfd_mode != VIPER_MFD_MODE_OFF)
		{
			mfd_mode = VIPER_MFD_MODE_DAMAGED;
		}
	}

	if ((mfd_mode != VIPER_MFD_MODE_OFF) && (mfd_mode != VIPER_MFD_MODE_DAMAGED) && (mfd_mode == *mfd_mode_ptr2))
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

static viper_mfd_modes get_next_mfd_mode (viper_mfd_modes mfd_mode, viper_mfd_locations mfd_location)
{
	viper_mfd_modes
		next_mfd_mode;

	ASSERT (viper_mfd_mode_valid (mfd_mode));

	ASSERT (viper_mfd_location_valid (mfd_location));

	switch (mfd_mode)
	{
		////////////////////////////////////////
		case VIPER_MFD_MODE_OFF:
		////////////////////////////////////////
		{
			next_mfd_mode = get_default_mfd_mode (mfd_location);

			break;
		}
		////////////////////////////////////////
		case VIPER_MFD_MODE_DAMAGED:
		////////////////////////////////////////
		{
			next_mfd_mode = VIPER_MFD_MODE_DAMAGED;

			break;
		}
		////////////////////////////////////////
		case VIPER_MFD_MODE_FLIR:
		////////////////////////////////////////
		{
			next_mfd_mode = VIPER_MFD_MODE_TSD;

			break;
		}
		////////////////////////////////////////
		case VIPER_MFD_MODE_DTV:
		////////////////////////////////////////
		{
			next_mfd_mode = VIPER_MFD_MODE_TSD;

			break;
		}
		////////////////////////////////////////
		case VIPER_MFD_MODE_TSD:
		////////////////////////////////////////
		{
			next_mfd_mode = VIPER_MFD_MODE_ASE;

			break;
		}
		////////////////////////////////////////
		case VIPER_MFD_MODE_ASE:
		////////////////////////////////////////
		{
			next_mfd_mode = VIPER_MFD_MODE_WEAPON;

			break;
		}
		////////////////////////////////////////
		case VIPER_MFD_MODE_WEAPON:
		////////////////////////////////////////
		{
			next_mfd_mode = VIPER_MFD_MODE_SYSTEM;

			break;
		}
		////////////////////////////////////////
		case VIPER_MFD_MODE_SYSTEM:
		////////////////////////////////////////
		{
			next_mfd_mode = VIPER_MFD_MODE_ENGINE;

			break;
		}
		////////////////////////////////////////
		case VIPER_MFD_MODE_ENGINE:
		////////////////////////////////////////
		{
			next_mfd_mode = VIPER_MFD_MODE_FLIGHT;

			break;
		}
		////////////////////////////////////////
		case VIPER_MFD_MODE_FLIGHT:
		////////////////////////////////////////
		{
			next_mfd_mode = VIPER_MFD_MODE_MISSION;

			break;
		}
		////////////////////////////////////////
		case VIPER_MFD_MODE_MISSION:
		////////////////////////////////////////
		{
			next_mfd_mode = mfd_location < VIPER_MFD_LOCATION_PILOT_DFD ? get_mfd_mode_for_eo_sensor () : VIPER_MFD_MODE_FLIGHT;

			break;
		}
	}

	return (next_mfd_mode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static viper_mfd_modes get_previous_mfd_mode (viper_mfd_modes mfd_mode, viper_mfd_locations mfd_location)
{
	viper_mfd_modes
		previous_mfd_mode;

	ASSERT (viper_mfd_mode_valid (mfd_mode));

	ASSERT (viper_mfd_location_valid (mfd_location));

	switch (mfd_mode)
	{
		////////////////////////////////////////
		case VIPER_MFD_MODE_OFF:
		////////////////////////////////////////
		{
			previous_mfd_mode = get_default_mfd_mode (mfd_location);

			break;
		}
		////////////////////////////////////////
		case VIPER_MFD_MODE_DAMAGED:
		////////////////////////////////////////
		{
			previous_mfd_mode = VIPER_MFD_MODE_DAMAGED;

			break;
		}
		////////////////////////////////////////
		case VIPER_MFD_MODE_FLIR:
		case VIPER_MFD_MODE_DTV:
		////////////////////////////////////////
		{
			previous_mfd_mode = VIPER_MFD_MODE_MISSION;

			break;
		}
		////////////////////////////////////////
		case VIPER_MFD_MODE_TSD:
		////////////////////////////////////////
		{
			previous_mfd_mode = get_mfd_mode_for_eo_sensor ();

			break;
		}
		////////////////////////////////////////
		case VIPER_MFD_MODE_ASE:
		////////////////////////////////////////
		{
			previous_mfd_mode = VIPER_MFD_MODE_TSD;

			break;
		}
		////////////////////////////////////////
		case VIPER_MFD_MODE_WEAPON:
		////////////////////////////////////////
		{
			previous_mfd_mode = VIPER_MFD_MODE_ASE;

			break;
		}
		////////////////////////////////////////
		case VIPER_MFD_MODE_SYSTEM:
		////////////////////////////////////////
		{
			previous_mfd_mode = VIPER_MFD_MODE_WEAPON;

			break;
		}
		////////////////////////////////////////
		case VIPER_MFD_MODE_ENGINE:
		////////////////////////////////////////
		{
			previous_mfd_mode = VIPER_MFD_MODE_SYSTEM;

			break;
		}
		////////////////////////////////////////
		case VIPER_MFD_MODE_FLIGHT:
		////////////////////////////////////////
		{
			previous_mfd_mode = mfd_location < VIPER_MFD_LOCATION_PILOT_DFD ? VIPER_MFD_MODE_ENGINE : VIPER_MFD_MODE_MISSION;

			break;
		}
		////////////////////////////////////////
		case VIPER_MFD_MODE_MISSION:
		////////////////////////////////////////
		{
			previous_mfd_mode = VIPER_MFD_MODE_FLIGHT;

			break;
		}
	}

	return (previous_mfd_mode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_next_viper_mfd (viper_mfd_locations mfd_location)
{
	viper_mfd_modes
		*mfd_mode_ptr1,
		*mfd_mode_ptr2,
		next_mfd_mode;

	ASSERT (viper_mfd_location_valid (mfd_location));

	mfd_mode_ptr1 = mfd_mode_ptrs[mfd_location];

	mfd_mode_ptr2 = opposite_mfd_mode_ptrs[mfd_location];

	next_mfd_mode = get_next_mfd_mode (*mfd_mode_ptr1, mfd_location);

	if (next_mfd_mode != VIPER_MFD_MODE_DAMAGED)
	{
		if (next_mfd_mode == *mfd_mode_ptr2)
		{
			next_mfd_mode = get_next_mfd_mode (next_mfd_mode, mfd_location);
		}

		ASSERT (next_mfd_mode != *mfd_mode_ptr2);
	}

	select_viper_mfd_mode (next_mfd_mode, mfd_location);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_previous_viper_mfd (viper_mfd_locations mfd_location)
{
	viper_mfd_modes
		*mfd_mode_ptr1,
		*mfd_mode_ptr2,
		previous_mfd_mode;

	ASSERT (viper_mfd_location_valid (mfd_location));

	mfd_mode_ptr1 = mfd_mode_ptrs[mfd_location];

	mfd_mode_ptr2 = opposite_mfd_mode_ptrs[mfd_location];

	previous_mfd_mode = get_previous_mfd_mode (*mfd_mode_ptr1, mfd_location);

	if (previous_mfd_mode != VIPER_MFD_MODE_DAMAGED)
	{
		if (previous_mfd_mode == *mfd_mode_ptr2)
		{
			previous_mfd_mode = get_previous_mfd_mode (previous_mfd_mode, mfd_location);
		}

		ASSERT (previous_mfd_mode != *mfd_mode_ptr2);
	}

	select_viper_mfd_mode (previous_mfd_mode, mfd_location);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void toggle_viper_mfd_on_off (viper_mfd_locations mfd_location)
{
	ASSERT (viper_mfd_location_valid (mfd_location));

	if (*mfd_mode_ptrs[mfd_location] != VIPER_MFD_MODE_OFF)
	{
		select_viper_mfd_mode (VIPER_MFD_MODE_OFF, mfd_location);
	}
	else
	{
		select_next_viper_mfd (mfd_location);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_next_viper_pilot_tsd_ase_range (void)
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

void select_next_viper_co_pilot_tsd_ase_range (void)
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

void select_previous_viper_pilot_tsd_ase_range (void)
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

void select_previous_viper_co_pilot_tsd_ase_range (void)
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

void select_next_viper_pilot_tsd_declutter_level (void)
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

void select_next_viper_co_pilot_tsd_declutter_level (void)
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

void select_previous_viper_pilot_tsd_declutter_level (void)
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

void select_previous_viper_co_pilot_tsd_declutter_level (void)
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

void toggle_viper_ase_auto_page (void)
{
	set_global_ase_auto_page (get_global_ase_auto_page () ^ 1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void auto_page_viper_ase_mfd (void)
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

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY) && (!viper_damage.pilot_lh_mfd))
		{
			select_viper_mfd_mode (VIPER_MFD_MODE_ASE, VIPER_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY) && (!viper_damage.pilot_rh_mfd))
		{
			select_viper_mfd_mode (VIPER_MFD_MODE_ASE, VIPER_MFD_LOCATION_PILOT_RHS);

			return;
		}

		if (pilot_lhs_mfd_mode == VIPER_MFD_MODE_ASE)
		{
			return;
		}

		if (pilot_rhs_mfd_mode == VIPER_MFD_MODE_ASE)
		{
			return;
		}

		if ((pilot_lhs_mfd_mode == VIPER_MFD_MODE_OFF) && (!viper_damage.pilot_lh_mfd))
		{
			select_viper_mfd_mode (VIPER_MFD_MODE_ASE, VIPER_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if ((pilot_rhs_mfd_mode == VIPER_MFD_MODE_OFF) && (!viper_damage.pilot_rh_mfd))
		{
			select_viper_mfd_mode (VIPER_MFD_MODE_ASE, VIPER_MFD_LOCATION_PILOT_RHS);

			return;
		}

		if ((!get_viper_mfd_has_focus (VIPER_MFD_LOCATION_PILOT_LHS)) && (!viper_damage.pilot_lh_mfd))
		{
			select_viper_mfd_mode (VIPER_MFD_MODE_ASE, VIPER_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if ((!get_viper_mfd_has_focus (VIPER_MFD_LOCATION_PILOT_RHS)) && (!viper_damage.pilot_rh_mfd))
		{
			select_viper_mfd_mode (VIPER_MFD_MODE_ASE, VIPER_MFD_LOCATION_PILOT_RHS);

			return;
		}

		if (!viper_damage.pilot_lh_mfd)
		{
			select_viper_mfd_mode (VIPER_MFD_MODE_ASE, VIPER_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if (!viper_damage.pilot_rh_mfd)
		{
			select_viper_mfd_mode (VIPER_MFD_MODE_ASE, VIPER_MFD_LOCATION_PILOT_RHS);

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

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY) && (!viper_damage.co_pilot_lh_mfd))
		{
			select_viper_mfd_mode (VIPER_MFD_MODE_ASE, VIPER_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY) && (!viper_damage.co_pilot_rh_mfd))
		{
			select_viper_mfd_mode (VIPER_MFD_MODE_ASE, VIPER_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}

		if (co_pilot_lhs_mfd_mode == VIPER_MFD_MODE_ASE)
		{
			return;
		}

		if (co_pilot_rhs_mfd_mode == VIPER_MFD_MODE_ASE)
		{
			return;
		}

		if ((co_pilot_lhs_mfd_mode == VIPER_MFD_MODE_OFF) && (!viper_damage.co_pilot_lh_mfd))
		{
			select_viper_mfd_mode (VIPER_MFD_MODE_ASE, VIPER_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if ((co_pilot_rhs_mfd_mode == VIPER_MFD_MODE_OFF) && (!viper_damage.co_pilot_rh_mfd))
		{
			select_viper_mfd_mode (VIPER_MFD_MODE_ASE, VIPER_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}

		if ((!get_viper_mfd_has_focus (VIPER_MFD_LOCATION_CO_PILOT_LHS)) && (!viper_damage.co_pilot_lh_mfd))
		{
			select_viper_mfd_mode (VIPER_MFD_MODE_ASE, VIPER_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if ((!get_viper_mfd_has_focus (VIPER_MFD_LOCATION_CO_PILOT_RHS)) && (!viper_damage.co_pilot_rh_mfd))
		{
			select_viper_mfd_mode (VIPER_MFD_MODE_ASE, VIPER_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}

		if (!viper_damage.co_pilot_lh_mfd)
		{
			select_viper_mfd_mode (VIPER_MFD_MODE_ASE, VIPER_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if (!viper_damage.co_pilot_rh_mfd)
		{
			select_viper_mfd_mode (VIPER_MFD_MODE_ASE, VIPER_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_viper_tads_mfd (void)
{
	if (get_crew_role () == CREW_ROLE_PILOT)
	{
		////////////////////////////////////////
		//
		// PILOT
		//
		////////////////////////////////////////

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY) && (!viper_damage.pilot_lh_mfd))
		{
			select_viper_mfd_mode (get_mfd_mode_for_eo_sensor (), VIPER_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY) && (!viper_damage.pilot_rh_mfd))
		{
			select_viper_mfd_mode (get_mfd_mode_for_eo_sensor (), VIPER_MFD_LOCATION_PILOT_RHS);

			return;
		}

		if
		(
			(pilot_lhs_mfd_mode == VIPER_MFD_MODE_FLIR) ||
			(pilot_lhs_mfd_mode == VIPER_MFD_MODE_DTV)
		)
		{
			select_viper_mfd_mode (get_mfd_mode_for_eo_sensor (), VIPER_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if
		(
			(pilot_rhs_mfd_mode == VIPER_MFD_MODE_FLIR) ||
			(pilot_rhs_mfd_mode == VIPER_MFD_MODE_DTV)
		)
		{
			select_viper_mfd_mode (get_mfd_mode_for_eo_sensor (), VIPER_MFD_LOCATION_PILOT_RHS);

			return;
		}

		if ((pilot_lhs_mfd_mode == VIPER_MFD_MODE_OFF) && (!viper_damage.pilot_lh_mfd))
		{
			select_viper_mfd_mode (get_mfd_mode_for_eo_sensor (), VIPER_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if ((pilot_rhs_mfd_mode == VIPER_MFD_MODE_OFF) && (!viper_damage.pilot_rh_mfd))
		{
			select_viper_mfd_mode (get_mfd_mode_for_eo_sensor (), VIPER_MFD_LOCATION_PILOT_RHS);

			return;
		}

		if (!viper_damage.pilot_lh_mfd)
		{
			select_viper_mfd_mode (get_mfd_mode_for_eo_sensor (), VIPER_MFD_LOCATION_PILOT_LHS);

			return;
		}

		if (!viper_damage.pilot_rh_mfd)
		{
			select_viper_mfd_mode (get_mfd_mode_for_eo_sensor (), VIPER_MFD_LOCATION_PILOT_RHS);

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

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY) && (!viper_damage.co_pilot_lh_mfd))
		{
			select_viper_mfd_mode (get_mfd_mode_for_eo_sensor (), VIPER_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY) && (!viper_damage.co_pilot_rh_mfd))
		{
			select_viper_mfd_mode (get_mfd_mode_for_eo_sensor (), VIPER_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}

		if
		(
			(co_pilot_lhs_mfd_mode == VIPER_MFD_MODE_FLIR) ||
			(co_pilot_lhs_mfd_mode == VIPER_MFD_MODE_DTV)
		)
		{
			select_viper_mfd_mode (get_mfd_mode_for_eo_sensor (), VIPER_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if
		(
			(co_pilot_rhs_mfd_mode == VIPER_MFD_MODE_FLIR) ||
			(co_pilot_rhs_mfd_mode == VIPER_MFD_MODE_DTV)
		)
		{
			select_viper_mfd_mode (get_mfd_mode_for_eo_sensor (), VIPER_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}

		if ((co_pilot_lhs_mfd_mode == VIPER_MFD_MODE_OFF) && (!viper_damage.co_pilot_lh_mfd))
		{
			select_viper_mfd_mode (get_mfd_mode_for_eo_sensor (), VIPER_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if ((co_pilot_rhs_mfd_mode == VIPER_MFD_MODE_OFF) && (!viper_damage.co_pilot_rh_mfd))
		{
			select_viper_mfd_mode (get_mfd_mode_for_eo_sensor (), VIPER_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}

		if (!viper_damage.co_pilot_lh_mfd)
		{
			select_viper_mfd_mode (get_mfd_mode_for_eo_sensor (), VIPER_MFD_LOCATION_CO_PILOT_LHS);

			return;
		}

		if (!viper_damage.co_pilot_rh_mfd)
		{
			select_viper_mfd_mode (get_mfd_mode_for_eo_sensor (), VIPER_MFD_LOCATION_CO_PILOT_RHS);

			return;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
