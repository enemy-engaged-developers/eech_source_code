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

static mfd_modes
	lhs_mfd_mode = MFD_MODE_OFF,
	rhs_mfd_mode = MFD_MODE_OFF;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//VJ 030423 TSD render mod
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
	text_display_colours[2];

#define TEXT_COLOUR1					(text_display_colours[0])
#define TEXT_BACKGROUND_COLOUR	(text_display_colours[1])


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//
// main 2D environment
//
////////////////////////////////////////
//Maverick fix the apache MFD font

#define MFD_WINDOW_X_MIN				(-1.1)
#define MFD_WINDOW_Y_MIN				(-1.1)
#define MFD_WINDOW_X_MAX				(1.100)
#define MFD_WINDOW_Y_MAX				(1.100)

#define MFD_VIEWPORT_SMALL_SIZE		(128)
#define MFD_VIEWPORT_LARGE_SIZE		(331)

#define MFD_TEXTURE_SIZE				(128)

#define MFD_VIEWPORT_TEXTURE_X_ORG	(MFD_TEXTURE_SIZE / 2)
#define MFD_VIEWPORT_TEXTURE_Y_ORG	(MFD_TEXTURE_SIZE / 2)

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
	draw_large_mfd;

static float
	i_translate_3d,
	j_translate_3d,
	i_scale_3d,
	j_scale_3d;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define LHS_OVERLAID_MFD_TEXTURE_INDEX (TEXTURE_INDEX_COMANCHE_MFD1)
#define RHS_OVERLAID_MFD_TEXTURE_INDEX (TEXTURE_INDEX_COMANCHE_MFD4)

static screen
	*lhs_mfd_texture_screen,
	*rhs_mfd_texture_screen,
	*lhs_overlaid_mfd_texture_screen,
	*rhs_overlaid_mfd_texture_screen;

static rgb_colour
	clear_mfd_colour;

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

////////////////////////////////////////
//
// ENGINE
//
////////////////////////////////////////

static char
	large_engine_bar_marker[] =
	{
		7,
		7,
		0,
		0,
		0,0,1,1,1,0,0,
		0,1,1,1,1,1,0,
		1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,
		0,1,1,1,1,1,0,
		0,0,1,1,1,0,0,
	};

static char
	small_engine_bar_marker[] =
	{
		4,
		4,
		0,
		0,
		0,1,1,0,
		1,1,1,1,
		1,1,1,1,
		0,1,1,0,
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_apache_mfd (void)
{
	select_apache_mfd_mode (MFD_MODE_ENGINE, MFD_LOCATION_LHS);

	select_apache_mfd_mode (MFD_MODE_TSD, MFD_LOCATION_RHS);

	tsd_ase_range = TSD_ASE_RANGE_5000;

	tsd_declutter_level = TSD_DECLUTTER_LEVEL_ALL;

	tsd_threat_line_flash_timer = TSD_THREAT_LINE_FLASH_RATE;

	tsd_draw_threat_line_status = 0;

	ase_threat_line_flash_timer = ASE_THREAT_LINE_FLASH_RATE;

	ase_draw_threat_line_status = 0;

	mfd_env = create_2d_environment ();

	lhs_mfd_texture_screen = create_system_texture_screen (MFD_TEXTURE_SIZE, MFD_TEXTURE_SIZE, TEXTURE_INDEX_AVCKPT_DISPLAY_LHS_MFD, TEXTURE_TYPE_SINGLEALPHA);
	rhs_mfd_texture_screen = create_system_texture_screen (MFD_TEXTURE_SIZE, MFD_TEXTURE_SIZE, TEXTURE_INDEX_AVCKPT_DISPLAY_RHS_MFD, TEXTURE_TYPE_SINGLEALPHA);

	lhs_overlaid_mfd_texture_screen = create_system_texture_screen (MFD_TEXTURE_SIZE, MFD_TEXTURE_SIZE, LHS_OVERLAID_MFD_TEXTURE_INDEX, TEXTURE_TYPE_SINGLEALPHA);
	rhs_overlaid_mfd_texture_screen = create_system_texture_screen (MFD_TEXTURE_SIZE, MFD_TEXTURE_SIZE, RHS_OVERLAID_MFD_TEXTURE_INDEX, TEXTURE_TYPE_SINGLEALPHA);

	set_rgb_colour (MFD_COLOUR1,   0, 255,   0, 255);
	set_rgb_colour (MFD_COLOUR2,   0, 200,   0, 255);
	set_rgb_colour (MFD_COLOUR3,   0, 176,   0, 255);
	set_rgb_colour (MFD_COLOUR4,   0, 151,   0, 255);
	set_rgb_colour (MFD_COLOUR5,   0, 149,   0, 255);
	set_rgb_colour (MFD_COLOUR6,  40,  68,  56, 255);

	set_rgb_colour (clear_mfd_colour, 0, 255, 0, 0);
	
	//VJ 030423 TSd render mod
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

   Initialise_TSD_render_terrain();

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_apache_mfd (void)
{
	destroy_2d_environment (mfd_env);

	destroy_screen (lhs_mfd_texture_screen);
	destroy_screen (rhs_mfd_texture_screen);

	destroy_screen (lhs_overlaid_mfd_texture_screen);
	destroy_screen (rhs_overlaid_mfd_texture_screen);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_apache_mfd_mode (mfd_modes mfd_mode, mfd_locations location)
{
	ASSERT ((mfd_mode >= MFD_MODE_OFF) && (mfd_mode < NUM_MFD_MODES));

	ASSERT (mfd_mode != MFD_MODE_LLLTV);

	ASSERT ((location == MFD_LOCATION_LHS) || (location == MFD_LOCATION_RHS));

	if (location == MFD_LOCATION_LHS)
	{
		if ((mfd_mode == MFD_MODE_DAMAGED) && (lhs_mfd_mode == MFD_MODE_OFF))
		{
			mfd_mode = MFD_MODE_OFF;
		}

		if (apache_damage.lh_mfd)
		{
			if (mfd_mode != MFD_MODE_OFF)
			{
				mfd_mode = MFD_MODE_DAMAGED;
			}
		}

		if ((mfd_mode != MFD_MODE_OFF) && (mfd_mode != MFD_MODE_DAMAGED) && (mfd_mode == rhs_mfd_mode))
		{
			rhs_mfd_mode = MFD_MODE_OFF;
		}

		lhs_mfd_mode = mfd_mode;

		debug_log ("LHS MFD: %s", mfd_mode_names[lhs_mfd_mode]);
	}
	else
	{
		if ((mfd_mode == MFD_MODE_DAMAGED) && (rhs_mfd_mode == MFD_MODE_OFF))
		{
			mfd_mode = MFD_MODE_OFF;
		}

		if (apache_damage.rh_mfd)
		{
			if (mfd_mode != MFD_MODE_OFF)
			{
				mfd_mode = MFD_MODE_DAMAGED;
			}
		}

		if ((mfd_mode != MFD_MODE_OFF) && (mfd_mode != MFD_MODE_DAMAGED) && (mfd_mode == lhs_mfd_mode))
		{
			lhs_mfd_mode = MFD_MODE_OFF;
		}

		rhs_mfd_mode = mfd_mode;

		debug_log ("RHS MFD: %s", mfd_mode_names[rhs_mfd_mode]);
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

static void draw_heading_scale (float heading)
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

		tick_10_deg_top			= 0.9375 - 0.015;
		tick_10_deg_bottom  		= 0.9375 - 0.015 - 0.045;
		tick_30_deg_top	  		= 0.9375;
		tick_30_deg_bottom  		= 0.9375 - 0.075;
		tick_datum_top		  		= 0.9375 - 0.075 - 0.010;
		tick_datum_bottom	  		= 0.9375 - 0.075 - 0.010 - 0.045;
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
heading_width_ratio = 0.1;
	set_2d_window (mfd_env, MFD_WINDOW_X_MIN * heading_width_ratio, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX * heading_width_ratio, MFD_WINDOW_Y_MAX);

	mfd_vp_x_min = mfd_viewport_x_org - (mfd_viewport_size * (heading_width_ratio * 0.5));

	mfd_vp_x_max = mfd_viewport_x_org + (mfd_viewport_size * (heading_width_ratio * 0.5)) - 0.001;

	set_2d_viewport (mfd_env, mfd_vp_x_min, mfd_viewport_y_min, mfd_vp_x_max, mfd_viewport_y_max);

	//
	// draw heading datum tick
	//

	draw_2d_line (0.0, tick_datum_top, 0.0, tick_datum_bottom, MFD_COLOUR1);

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
		draw_2d_line (-0.3000, -0.6750,  0.3000, -0.6750, MFD_COLOUR1);
		draw_2d_line (-0.3000, -0.9000,  0.3000, -0.9000, MFD_COLOUR1);
		draw_2d_line (-0.3000, -0.6750, -0.3000, -0.9000, MFD_COLOUR1);
		draw_2d_line ( 0.3000, -0.6750,  0.3000, -0.9000, MFD_COLOUR1);

		draw_2d_line ( 0.0000, -0.6750,  0.0000, -0.6950, MFD_COLOUR1);
		draw_2d_line (-0.2250, -0.6750, -0.2250, -0.6950, MFD_COLOUR1);
		draw_2d_line ( 0.2250, -0.6750,  0.2250, -0.6950, MFD_COLOUR1);

		draw_2d_line ( 0.0000, -0.8800,  0.0000, -0.9000, MFD_COLOUR1);
		draw_2d_line (-0.2250, -0.8800, -0.2250, -0.9000, MFD_COLOUR1);
		draw_2d_line ( 0.2250, -0.8800,  0.2250, -0.9000, MFD_COLOUR1);

		draw_2d_line (-0.3000, -0.7500, -0.2800, -0.7500, MFD_COLOUR1);
		draw_2d_line ( 0.3000, -0.7500,  0.2800, -0.7500, MFD_COLOUR1);

		x = eo_azimuth / eo_max_azimuth * 0.3;
		y = (eo_elevation / eo_min_elevation * -0.15) - 0.75;

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
//VJ 030807 radar range adjustable
	char
		s[8];
//		*s;

	float
		width,
		y_adjust;

	if (scan_range == APACHE_RADAR_SCAN_RANGE_500)
	{
//		s = "500m";
		sprintf(s,"%.0fm",APACHE_RADAR_SCAN_RANGE_500);
	}
	else if (scan_range == APACHE_RADAR_SCAN_RANGE_1000)
	{
		sprintf(s,"%.0fKm",APACHE_RADAR_SCAN_RANGE_1000/1000);
//		s = "1Km";
	}
	else if (scan_range == APACHE_RADAR_SCAN_RANGE_2000)
	{
		sprintf(s,"%.0fKm",APACHE_RADAR_SCAN_RANGE_2000/1000);
//		s = "2Km";
	}
	else if (scan_range == APACHE_RADAR_SCAN_RANGE_4000)
	{
		sprintf(s,"%.0fKm",APACHE_RADAR_SCAN_RANGE_4000/1000);
//		s = "4Km";
	}
	else if (scan_range == APACHE_RADAR_SCAN_RANGE_8000)
	{
		sprintf(s,"%.0fKm",APACHE_RADAR_SCAN_RANGE_8000/1000);
//		s = "8Km";
	}
	else
	{
		sprintf(s,"XXX");
//		s = "XXX";
	}

	width = get_mono_font_string_width (s);

	if (draw_large_mfd)
	{
		y_adjust = 5.0;
	}
	else
	{
		y_adjust = 2.0;
	}

	set_2d_mono_font_position (0.8, 1.0);

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

	if (apache_damage.radar)
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
		set_2d_mono_font_position (-0.8, -1.0);

		set_mono_font_rel_position (1.0, y_adjust);

		print_mono_font_string (s);
	}

	if (target)
	{
		//
		// range
		//

		if ((target_range < 1000.0) && (!apache_damage.laser_designator))
		{
			sprintf (buffer, "%dm", (int) target_range);
		}
		else
		{
			sprintf (buffer, "%.1fKm", target_range * (1.0 / 1000.0));
		}

		width = get_mono_font_string_width (buffer);

		set_2d_mono_font_position (0.8, -1.0);

		set_mono_font_rel_position (-width, y_adjust);

		print_mono_font_string (buffer);

		//
		// no line of sight
		//

		if (!get_local_entity_int_value (target, INT_TYPE_GUNSHIP_RADAR_LOS_CLEAR))
		{
			if (draw_large_mfd)
			{
				y_adjust = -25.0;
			}
			else
			{
				y_adjust = -12.0;
			}

			width = get_mono_font_string_width ("NO LOS");

			set_2d_mono_font_position (0.8, -1.0);

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

		set_2d_mono_font_position (-0.8, 1.0);

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

		set_2d_mono_font_position (-0.8, -1.0);

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

	num_segments = (int) (arc_size * (1.0 / APACHE_RADAR_SCAN_ARC_SEGMENT_SIZE));

	if (num_segments > 0)
	{
		theta = arc_size * 0.5;

		sine_cosine (theta, &sin_theta, &cos_theta);

		x1 = -radius * sin_theta;
		y1 = radius * cos_theta;

		while (num_segments--)
		{
			theta -= APACHE_RADAR_SCAN_ARC_SEGMENT_SIZE;

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
	else
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

	if (!apache_damage.radar)
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

	set_2d_mono_font_position (-0.8, 1.0);

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

	draw_heading_scale (get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_HEADING));

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

	draw_radar_arc (APACHE_RADAR_SCAN_ARC_SIZE_90, RADIUS, MFD_COLOUR4);

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

	if (!apache_damage.radar)
	{
		set_2d_window_rotation (mfd_env, source_heading);

		target = get_local_entity_first_child (source, LIST_TYPE_GUNSHIP_TARGET);

		while (target)
		{
			if (get_gunship_target_valid_for_ground_radar (target))
			{
				if (get_target_matches_ground_radar_declutter_criteria (target))
				{
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

	if (apache_damage.radar)
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

#define RADIUS	(0.8)
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

	set_2d_mono_font_position (-0.8, 1.0);

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

	if (air_radar.scan_arc_size == APACHE_RADAR_SCAN_ARC_SIZE_360)
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

	if (!apache_damage.radar)
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

	if (apache_damage.radar)
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

static void draw_3d_eo_display (eo_params *eo, target_acquisition_systems system, mfd_locations location)
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

	int
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

	if (command_line_green_mfd)
	{
		tint = DISPLAY_3D_TINT_GREEN;
	}
	else
	{
		tint = DISPLAY_3D_TINT_GREY;
	}

	if (draw_large_mfd)
	{
		if (location == MFD_LOCATION_LHS)
		{
			set_main_3d_params (tint, light_level, noise_level, mfd_viewport_x_min - 1.5, mfd_viewport_y_min - 1.5, 334.0, 333.0, rad (59.99) * zoom, rad (59.99) * zoom);
		}
		else
		{
			set_main_3d_params (tint, light_level, noise_level, mfd_viewport_x_min - 1.5, mfd_viewport_y_min - 1.5, 334.0, 333.0, rad (59.99) * zoom, rad (59.99) * zoom);
		}
	}
	else
	{
		if (location == MFD_LOCATION_LHS)
		{
			set_main_3d_params (tint, light_level, noise_level, mfd_viewport_x_min, mfd_viewport_y_min, 128.0, 128.0, rad (59.99) * zoom, rad (59.99) * zoom);
		}
		else
		{
			set_main_3d_params (tint, light_level, noise_level, mfd_viewport_x_min, mfd_viewport_y_min, 128.0, 128.0, rad (59.99) * zoom, rad (59.99) * zoom);
		}
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

	int
		tint;

	ASSERT (eo);

	ASSERT (small_eo_3d_texture_screen);

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

	set_3d_render_target (small_eo_3d_texture_screen);

	set_active_screen (small_eo_3d_texture_screen);

	if (command_line_green_mfd)
	{
		tint = DISPLAY_3D_TINT_GREEN;
	}
	else
	{
		tint = DISPLAY_3D_TINT_GREY;
	}

	set_main_3d_params (tint, light_level, noise_level, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_size, mfd_viewport_size, rad (59.99) * zoom, rad (59.99) * zoom);

	draw_eo_3d_scene = TRUE;

	draw_main_3d_scene (&eo_vp);

	draw_eo_3d_scene = FALSE;

	finalise_3d_render_target_texture (small_eo_3d_texture_screen);

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

	set_main_3d_params (DISPLAY_3D_TINT_GREEN, light_level, noise_level, x, y, size, size, rad (59.99) * zoom, rad (59.99) * zoom);

	draw_eo_3d_scene = TRUE;

	draw_main_3d_scene (&eo_vp);

	draw_eo_3d_scene = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_2d_eo_display (eo_params *eo, target_acquisition_systems system, int damaged, int valid_3d, int scaled_3d)
{
	const char
		*s;
	char
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

	set_2d_mono_font_position (-0.8, 1.0);

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
		set_2d_mono_font_position (-0.8, 0.9);

		if (draw_large_mfd)
		{
			set_mono_font_rel_position (1.0, 2.0);

			print_mono_font_string ("LO LIGHT");
		}
		else
		{
			set_mono_font_rel_position (1.0, 2.0);

			print_mono_font_string ("LO");
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

	if (draw_large_mfd)
	{
		y_adjust = 5.0;
	}
	else
	{
		y_adjust = 2.0;
	}

	set_2d_mono_font_position (0.8, 1.0);

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
		set_2d_mono_font_position (-0.8, -1.0);

		set_mono_font_rel_position (1.0, y_adjust);

		print_mono_font_string (s);
	}

	//
	// target range
	//

	if (target)
	{
		if ((target_range < 1000.0) && (!apache_damage.laser_designator))
		{
			sprintf (buffer, "%dm", (int) target_range);
		}
		else
		{
			sprintf (buffer, "%.1fKm", target_range * (1.0 / 1000.0));
		}

		width = get_mono_font_string_width (buffer);

		set_2d_mono_font_position (0.8, -1.0);

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

		set_2d_mono_font_position (-0.8, -1.0);

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
	// draw heading scale
	//
	////////////////////////////////////////

	draw_heading_scale (get_heading_from_attitude_matrix (eo_vp.attitude));

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

static void draw_3d_flir_mfd (mfd_locations location)
{
	if (!apache_damage.flir)
	{
		draw_3d_eo_display (&apache_flir, TARGET_ACQUISITION_SYSTEM_FLIR, location);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_2d_flir_mfd (int valid_3d, int scaled_3d)
{
	draw_2d_eo_display (&apache_flir, TARGET_ACQUISITION_SYSTEM_FLIR, apache_damage.flir, valid_3d, scaled_3d);
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

static void draw_3d_dtv_mfd (mfd_locations location)
{
	if (!apache_damage.dtv)
	{
		draw_3d_eo_display (&apache_dtv, TARGET_ACQUISITION_SYSTEM_DTV, location);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_2d_dtv_mfd (int valid_3d, int scaled_3d)
{
	draw_2d_eo_display (&apache_dtv, TARGET_ACQUISITION_SYSTEM_DTV, apache_damage.dtv, valid_3d, scaled_3d);
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

static void draw_3d_dvo_mfd (mfd_locations location)
{
	if (!apache_damage.dvo)
	{
		draw_3d_eo_display (&apache_dvo, TARGET_ACQUISITION_SYSTEM_DVO, location);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_2d_dvo_mfd (int valid_3d, int scaled_3d)
{
	draw_2d_eo_display (&apache_dvo, TARGET_ACQUISITION_SYSTEM_DVO, apache_damage.dvo, valid_3d, scaled_3d);
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

static void draw_tactical_situation_display_mfd (void)
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
		y_origin = -0.65;
	}
	else
	{
		x_origin = 0.0;
		y_origin = -0.70;
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
		set_rgb_colour (MFD_COLOUR1,	0, 0,  96, 255);  //dark blue
	   set_rgb_colour (MFD_COLOUR2,	32, 32,  164, 255); //light blue
		set_rgb_colour (MFD_COLOUR3,	240, 64,   0, 255); //bright red
		set_rgb_colour (MFD_COLOUR4,	148, 32,   0, 255);//dark red

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
		
		set_rgb_colour (MFD_COLOUR6,	255, 255,  0, 255);
		//VJ 030511 colours 7 and 8 are grays when enemy colour option is off in eech.ini		
		//VJ 030530 colour tweaks: black and dark gray are best
		set_rgb_colour (MFD_COLOUR7,    64, 64, 64, 255);
		set_rgb_colour (MFD_COLOUR8,   0, 0, 0, 255);
		
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

			if (air_radar.scan_arc_size == APACHE_RADAR_SCAN_ARC_SIZE_360)
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
						threat_type = get_local_entity_int_value (target, INT_TYPE_THREAT_TYPE);

						if ((threat_type == THREAT_TYPE_SAM) || (threat_type == THREAT_TYPE_AAA))
						{
							target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

							dx = (target_position->x - source_position->x) * scale;
							dy = (target_position->z - source_position->z) * scale;

							air_scan_range = get_local_entity_float_value (target, FLOAT_TYPE_AIR_SCAN_RANGE) * scale;

//VJ 030423 TSD render mod, enemy of comanche so red
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
			case TARGET_ACQUISITION_SYSTEM_IHADSS:
			{
				s = "IHADSS";

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

		set_2d_mono_font_position (-0.8, 1.0);

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
			case TARGET_ACQUISITION_SYSTEM_IHADSS:
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
			y_adjust = 2.0;
		}
		else
		{
			y_adjust = 2.0;
		}

		set_2d_mono_font_position (-0.8, 0.9);

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
		y_adjust = 5.0;
	}
	else
	{
		y_adjust = 2.0;
	}

	set_2d_mono_font_position (0.8, 1.0);

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
		y_adjust = 2.0;
	}
	else
	{
		y_adjust = 2.0;
	}

	set_2d_mono_font_position (0.8, 0.9);

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

			if ((target_range < 1000.0) && (!apache_damage.laser_designator))
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
				y_adjust = -12.0;
			}
			else
			{
				y_adjust = -5.0;
			}

			set_2d_mono_font_position (0.8, -1.0);

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

			if (draw_large_mfd)
			{
				y_adjust = -25.0;
			}
			else
			{
				y_adjust = -12.0;
			}

			set_2d_mono_font_position (-0.8, -1.0);

			set_mono_font_rel_position (1.0, y_adjust);

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

			if (draw_large_mfd)
			{
				y_adjust = -12.0;
			}
			else
			{
				y_adjust = -5.0;
			}

			set_2d_mono_font_position (-0.8, -1.0);

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

#define RADIUS	(0.8)

static void draw_aircraft_survivability_equipment_display_mfd (void)
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

		set_2d_mono_font_position (-0.8, 1.0);

		set_mono_font_rel_position (1.0, y_adjust);

		closest_missile = get_closest_missile (source, source_position, THREAT_TYPE_IR_MISSILE, &time_to_impact);

		if (closest_missile)
		{
			sprintf (buffer, "IR MSL:%.1f", time_to_impact);

			print_mono_font_string (buffer);

			if (draw_large_mfd)
			{
				y_adjust = 2.0;
			}
			else
			{
				y_adjust = 2.0;
			}

			set_2d_mono_font_position (-0.8, 0.9);

			set_mono_font_rel_position (1.0, y_adjust);
		}

		closest_missile = get_closest_missile (source, source_position, THREAT_TYPE_RF_MISSILE, &time_to_impact);

		if (closest_missile)
		{
			sprintf (buffer, "RF MSL:%.1f", time_to_impact);

			print_mono_font_string (buffer);

			if (draw_large_mfd)
			{
				y_adjust = -2.0;
			}
			else
			{
				y_adjust = 3.0;
			}

			set_2d_mono_font_position (-0.8, 0.8);

			set_mono_font_rel_position (1.0, y_adjust);
		}

		closest_missile = get_closest_missile (source, source_position, THREAT_TYPE_LASER_MISSILE, &time_to_impact);

		if (closest_missile)
		{
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
		y_adjust = 5.0;
	}
	else
	{
		y_adjust = 2.0;
	}

	set_2d_mono_font_position (0.8, 1.0);

	set_mono_font_rel_position (-width, y_adjust);

	print_mono_font_string (s);

	//
	// jammers
	//

	if (draw_large_mfd)
	{
		if (apache_damage.infra_red_jammer)
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
		if (apache_damage.infra_red_jammer)
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

	set_2d_mono_font_position (-0.8, -1.0);

	set_mono_font_rel_position (1.0, y_adjust);

	print_mono_font_string (s);

	if (draw_large_mfd)
	{
		if (apache_damage.radar_jammer)
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
		if (apache_damage.radar_jammer)
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

	set_2d_mono_font_position (-0.8, -1.0);

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
			y_adjust = -38.0;
		}
		else
		{
			y_adjust = -19.0;
		}

		set_2d_mono_font_position (-0.8, -1.0);

		set_mono_font_rel_position (1.0, y_adjust);

		print_mono_font_string (s);

		set_2d_mono_font_position (0.8, -1.0);

		set_mono_font_rel_position (-width, y_adjust);

		print_mono_font_string (s);
	}

	//
	// chaff
	//

	if (draw_large_mfd)
	{
		if (apache_damage.chaff_dispenser)
		{
			sprintf (buffer, "CHAFF:XX");
		}
		else
		{
			sprintf (buffer, "CHAFF:%02d", get_local_entity_weapon_count (source, ENTITY_SUB_TYPE_WEAPON_CHAFF));
		}

		y_adjust = -25.0;
	}
	else
	{
		if (apache_damage.chaff_dispenser)
		{
			sprintf (buffer, "C:XX");
		}
		else
		{
			sprintf (buffer, "C:%02d", get_local_entity_weapon_count (source, ENTITY_SUB_TYPE_WEAPON_CHAFF));
		}

		y_adjust = -12.0;
	}

	width = get_mono_font_string_width (buffer);

	set_2d_mono_font_position (0.8, -1.0);

	set_mono_font_rel_position (-width, y_adjust);

	print_mono_font_string (buffer);

	//
	// flares
	//

	if (draw_large_mfd)
	{
		if (apache_damage.flare_dispenser)
		{
			sprintf (buffer, "FLARE:XX");
		}
		else
		{
			sprintf (buffer, "FLARE:%02d", get_local_entity_weapon_count (source, ENTITY_SUB_TYPE_WEAPON_FLARE));
		}

		y_adjust = -12.0;
	}
	else
	{
		if (apache_damage.flare_dispenser)
		{
			sprintf (buffer, "F:XX");
		}
		else
		{
			sprintf (buffer, "F:%02d", get_local_entity_weapon_count (source, ENTITY_SUB_TYPE_WEAPON_FLARE));
		}

		y_adjust = -5.0;
	}

	width = get_mono_font_string_width (buffer);

	set_2d_mono_font_position (0.8, -1.0);

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

static rgb_alpha_masked_sprite_data
	weapon_sprite;

static unsigned char
	*weapon_sprite_data,
	*weapon_mask_data;

static int
	weapon_x_offset,
	weapon_y_offset,
	weapon_draw_on_texture;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_sprite (int x, int y, int u, int v, int width, int height)
{
	ASSERT (x >= 0);
	ASSERT (y >= 0);

	weapon_sprite.x = weapon_x_offset + x;

	weapon_sprite.y = weapon_y_offset + y;

	weapon_sprite.u = u;

	weapon_sprite.v = v;

	weapon_sprite.width = width;

	weapon_sprite.height = height;

	// JB 030311 Disable EEAH check
	if (!weapon_sprite_data)
		return;

	if (weapon_draw_on_texture)
	{
		blit_rgb_alpha_masked_sprite_zero_mask_value_onto_texture (weapon_sprite_data, weapon_mask_data, &weapon_sprite, video_screen);
	}
	else
	{
		blit_rgb_alpha_masked_sprite_zero_mask_value (weapon_sprite_data, weapon_mask_data, &weapon_sprite);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_weapon_hardpoint_info (int heading_depth, entity_sub_types given_weapon, entity_sub_types selected_weapon)
{
	char
		buffer[80];

	int
		number,
		damaged,
		hardpoint_x,
		hardpoint_y,
		u,
		v;

	entity_sub_types
		weapon_sub_type;

	if (!get_local_entity_weapon_hardpoint_info (get_gunship_entity (), heading_depth, given_weapon, &weapon_sub_type, &number, &damaged))
	{
		return;
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	// Chain Gun
	//
	////////////////////////////////////////////////////////////////////////////////

	if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_M230_30MM_ROUND)
	{
		if (draw_large_mfd)
		{
			////////////////////////////////////////
			//
			// LARGE
			//
			////////////////////////////////////////

			//
			// chain gun
			//

			if (number == 0)
			{
				if ((weapon_sub_type == selected_weapon) && (!damaged))
				{
					draw_sprite (118, 200, 262, 134, 28, 27);
				}
			}
			else
			{
				if ((weapon_sub_type == selected_weapon) && (!damaged))
				{
					draw_sprite (118, 200, 292, 134, 28, 27);
				}
				else
				{
					draw_sprite (118, 200, 322, 134, 27, 27);
				}
			}

			//
			// digits
			//

			hardpoint_x = 115;
			hardpoint_y = 234;

			sprintf (buffer, "%04d", number);

			if ((weapon_sub_type == selected_weapon) && (!damaged))
			{
				v = 32;
			}
			else
			{
				v = 47;
			}

			if (buffer[0] == '0')
			{
				u = 364 + (9 * 10);
			}
			else
			{
				u = 364 + ((buffer[0] - '1') * 10);
			}

			draw_sprite (hardpoint_x, hardpoint_y, u, v, 8, 12);

			if (buffer[1] == '0')
			{
				u = 364 + (9 * 10);
			}
			else
			{
				u = 364 + ((buffer[1] - '1') * 10);
			}

			draw_sprite (hardpoint_x + 9, hardpoint_y, u, v, 8, 12);

			if (buffer[2] == '0')
			{
				u = 364 + (9 * 10);
			}
			else
			{
				u = 364 + ((buffer[2] - '1') * 10);
			}

			draw_sprite (hardpoint_x + 18, hardpoint_y, u, v, 8, 12);

			if (buffer[3] == '0')
			{
				u = 364 + (9 * 10);
			}
			else
			{
				u = 364 + ((buffer[3] - '1') * 10);
			}

			draw_sprite (hardpoint_x + 27, hardpoint_y, u, v, 8, 12);

			//
			// damage cross
			//

			if (damaged)
			{
				draw_sprite (116, 203, 334, 61, 32, 32);
			}
		}
		else
		{
			////////////////////////////////////////
			//
			// SMALL
			//
			////////////////////////////////////////

			//
			// chain gun
			//

			if (number == 0)
			{
				if ((weapon_sub_type == selected_weapon) && (!damaged))
				{
					draw_sprite (61, 360, 133, 327, 14, 13);
				}
			}
			else
			{
				if ((weapon_sub_type == selected_weapon) && (!damaged))
				{
					draw_sprite (61, 360, 148, 327, 14, 13);
				}
				else
				{
					draw_sprite (61, 360, 163, 327, 13, 13);
				}
			}

			//
			// digits
			//

			hardpoint_x = 60;
			hardpoint_y = 377;

			sprintf (buffer, "%04d", number);

			if ((weapon_sub_type == selected_weapon) && (!damaged))
			{
				v = 276;
			}
			else
			{
				v = 283;
			}

			if (buffer[0] == '0')
			{
				u = 184 + (9 * 5);
			}
			else
			{
				u = 184 + ((buffer[0] - '1') * 5);
			}

			draw_sprite (hardpoint_x, hardpoint_y, u, v, 4, 6);

			if (buffer[1] == '0')
			{
				u = 184 + (9 * 5);
			}
			else
			{
				u = 184 + ((buffer[1] - '1') * 5);
			}

			draw_sprite (hardpoint_x + 4, hardpoint_y, u, v, 4, 6);

			if (buffer[2] == '0')
			{
				u = 184 + (9 * 5);
			}
			else
			{
				u = 184 + ((buffer[2] - '1') * 5);
			}

			draw_sprite (hardpoint_x + 8, hardpoint_y, u, v, 4, 6);

			if (buffer[3] == '0')
			{
				u = 184 + (9 * 5);
			}
			else
			{
				u = 184 + ((buffer[3] - '1') * 5);
			}

			draw_sprite (hardpoint_x + 12, hardpoint_y, u, v, 4, 6);

			//
			// damage cross
			//

			if (damaged)
			{
				draw_sprite (60, 361, 169, 290, 16, 16);
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	// Hydras
	//
	////////////////////////////////////////////////////////////////////////////////

	if ((weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255) || (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_HYDRA70_M261))
	{
		if (draw_large_mfd)
		{
			////////////////////////////////////////
			//
			// LARGE
			//
			////////////////////////////////////////

			//
			// rocket pod
			//

			switch (heading_depth)
			{
				case APACHE_LHS_INNER_PYLON:
				{
					hardpoint_x = 50;
					hardpoint_y = 177;

					break;
				}
				case APACHE_RHS_INNER_PYLON:
				{
					hardpoint_x = 188;
					hardpoint_y = 177;

					break;
				}
				case APACHE_LHS_OUTER_PYLON:
				{
					hardpoint_x = 18;
					hardpoint_y = 177;

					break;
				}
				case APACHE_RHS_OUTER_PYLON:
				{
					hardpoint_x = 220;
					hardpoint_y = 177;

					break;
				}
			}

			if (number == 0)
			{
				if ((weapon_sub_type == selected_weapon) && (!damaged))
				{
					draw_sprite (hardpoint_x, hardpoint_y, 262, 99, 26, 33);
				}
				else
				{
					draw_sprite (hardpoint_x, hardpoint_y, 319, 99, 26, 33);
				}
			}
			else
			{
				if ((weapon_sub_type == selected_weapon) && (!damaged))
				{
					draw_sprite (hardpoint_x, hardpoint_y, 291, 99, 26, 33);
				}
				else
				{
					draw_sprite (hardpoint_x, hardpoint_y, 347, 99, 26, 33);
				}

				//
				// digits
				//

				hardpoint_x += 4;
				hardpoint_y += 14;

				sprintf (buffer, "%02d", number);

				if ((weapon_sub_type == selected_weapon) && (!damaged))
				{
					v = 32;
				}
				else
				{
					v = 47;
				}

				if (buffer[0] == '0')
				{
					u = 263 + (9 * 10);
				}
				else
				{
					u = 263 + ((buffer[0] - '1') * 10);
				}

				draw_sprite (hardpoint_x, hardpoint_y, u, v, 8, 12);

				if (buffer[1] == '0')
				{
					u = 263 + (9 * 10);
				}
				else
				{
					u = 263 + ((buffer[1] - '1') * 10);
				}

				draw_sprite (hardpoint_x + 8, hardpoint_y, u, v, 8, 12);
			}

			//
			// damage cross
			//

			if (damaged)
			{
				switch (heading_depth)
				{
					case APACHE_LHS_INNER_PYLON:
					{
						draw_sprite (47, 181, 334, 61, 32, 32);

						break;
					}
					case APACHE_RHS_INNER_PYLON:
					{
						draw_sprite (185, 181, 334, 61, 32, 32);

						break;
					}
					case APACHE_LHS_OUTER_PYLON:
					{
						draw_sprite (15, 181, 334, 61, 32, 32);

						break;
					}
					case APACHE_RHS_OUTER_PYLON:
					{
						draw_sprite (217, 181, 334, 61, 32, 32);

						break;
					}
				}
			}

			//
			// type
			//

			switch (heading_depth)
			{
				case APACHE_LHS_INNER_PYLON:
				{
					hardpoint_x = 47;
					hardpoint_y = 234;

					break;
				}
				case APACHE_RHS_INNER_PYLON:
				{
					hardpoint_x = 185;
					hardpoint_y = 234;

					break;
				}
				case APACHE_LHS_OUTER_PYLON:
				{
					hardpoint_x = 15;
					hardpoint_y = 234;

					break;
				}
				case APACHE_RHS_OUTER_PYLON:
				{
					hardpoint_x = 217;
					hardpoint_y = 234;

					break;
				}
			}

			if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255)
			{
				if ((weapon_sub_type == selected_weapon) && (!damaged))
				{
					draw_sprite (hardpoint_x, hardpoint_y, 262, 17, 31, 12);
				}
				else
				{
					draw_sprite (hardpoint_x, hardpoint_y, 342, 17, 31, 12);
				}
			}
			else
			{
				if ((weapon_sub_type == selected_weapon) && (!damaged))
				{
					draw_sprite (hardpoint_x, hardpoint_y, 295, 17, 31, 12);
				}
				else
				{
					draw_sprite (hardpoint_x, hardpoint_y, 375, 17, 31, 12);
				}
			}
		}
		else
		{
			////////////////////////////////////////
			//
			// SMALL
			//
			////////////////////////////////////////

			//
			// rocket pod
			//

			switch (heading_depth)
			{
				case APACHE_LHS_INNER_PYLON:
				{
					hardpoint_x = 27;
					hardpoint_y = 348;

					break;
				}
				case APACHE_RHS_INNER_PYLON:
				{
					hardpoint_x = 96;
					hardpoint_y = 348;

					break;
				}
				case APACHE_LHS_OUTER_PYLON:
				{
					hardpoint_x = 11;
					hardpoint_y = 348;

					break;
				}
				case APACHE_RHS_OUTER_PYLON:
				{
					hardpoint_x = 112;
					hardpoint_y = 348;

					break;
				}
			}

			if (number == 0)
			{
				if ((weapon_sub_type == selected_weapon) && (!damaged))
				{
					draw_sprite (hardpoint_x, hardpoint_y, 133, 309, 13, 17);
				}
				else
				{
					draw_sprite (hardpoint_x, hardpoint_y, 161, 309, 13, 17);
				}
			}
			else
			{
				if ((weapon_sub_type == selected_weapon) && (!damaged))
				{
					draw_sprite (hardpoint_x, hardpoint_y, 147, 309, 13, 17);
				}
				else
				{
					draw_sprite (hardpoint_x, hardpoint_y, 175, 309, 13, 17);
				}

				//
				// digits
				//

				hardpoint_x += 2;
				hardpoint_y += 7;

				sprintf (buffer, "%02d", number);

				if ((weapon_sub_type == selected_weapon) && (!damaged))
				{
					v = 276;
				}
				else
				{
					v = 283;
				}

				if (buffer[0] == '0')
				{
					u = 133 + (9 * 5);
				}
				else
				{
					u = 133 + ((buffer[0] - '1') * 5);
				}

				draw_sprite (hardpoint_x, hardpoint_y, u, v, 4, 6);

				if (buffer[1] == '0')
				{
					u = 133 + (9 * 5);
				}
				else
				{
					u = 133 + ((buffer[1] - '1') * 5);
				}

				draw_sprite (hardpoint_x + 4, hardpoint_y, u, v, 4, 6);
			}

			//
			// damage cross
			//

			if (damaged)
			{
				switch (heading_depth)
				{
					case APACHE_LHS_INNER_PYLON:
					{
						draw_sprite (26, 350, 169, 290, 16, 16);

						break;
					}
					case APACHE_RHS_INNER_PYLON:
					{
						draw_sprite (95, 350, 169, 290, 16, 16);

						break;
					}
					case APACHE_LHS_OUTER_PYLON:
					{
						draw_sprite (10, 350, 169, 290, 16, 16);

						break;
					}
					case APACHE_RHS_OUTER_PYLON:
					{
						draw_sprite (111, 350, 169, 290, 16, 16);

						break;
					}
				}
			}

			//
			// type
			//

			switch (heading_depth)
			{
				case APACHE_LHS_INNER_PYLON:
				{
					hardpoint_x = 26;
					hardpoint_y = 377;

					break;
				}
				case APACHE_RHS_INNER_PYLON:
				{
					hardpoint_x = 95;
					hardpoint_y = 377;

					break;
				}
				case APACHE_LHS_OUTER_PYLON:
				{
					hardpoint_x = 10;
					hardpoint_y = 377;

					break;
				}
				case APACHE_RHS_OUTER_PYLON:
				{
					hardpoint_x = 111;
					hardpoint_y = 377;

					break;
				}
			}

			if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255)
			{
				if ((weapon_sub_type == selected_weapon) && (!damaged))
				{
					draw_sprite (hardpoint_x, hardpoint_y, 133, 268, 15, 6);
				}
				else
				{
					draw_sprite (hardpoint_x, hardpoint_y, 173, 268, 15, 6);
				}
			}
			else
			{
				if ((weapon_sub_type == selected_weapon) && (!damaged))
				{
					draw_sprite (hardpoint_x, hardpoint_y, 149, 268, 15, 6);
				}
				else
				{
					draw_sprite (hardpoint_x, hardpoint_y, 189, 268, 15, 6);
				}
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	// Hellfires
	//
	////////////////////////////////////////////////////////////////////////////////

	if ((weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_AGM114L_LONGBOW_HELLFIRE) || (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_AGM114K_HELLFIRE_II))
	{
		if (draw_large_mfd)
		{
			////////////////////////////////////////
			//
			// LARGE
			//
			////////////////////////////////////////

			//
			// pylon
			//

			switch (heading_depth)
			{
				case APACHE_LHS_INNER_PYLON:
				{
					hardpoint_x = 53;
					hardpoint_y = 177;

					break;
				}
				case APACHE_RHS_INNER_PYLON:
				{
					hardpoint_x = 191;
					hardpoint_y = 177;

					break;
				}
				case APACHE_LHS_OUTER_PYLON:
				{
					hardpoint_x = 21;
					hardpoint_y = 177;

					break;
				}
				case APACHE_RHS_OUTER_PYLON:
				{
					hardpoint_x = 223;
					hardpoint_y = 177;

					break;
				}
			}

			if ((weapon_sub_type == selected_weapon) && (!damaged))
			{
				draw_sprite (hardpoint_x, hardpoint_y, 262, 79, 20, 18);
			}
			else
			{
				draw_sprite (hardpoint_x, hardpoint_y, 284, 79, 20, 18);
			}

			//
			// missiles
			//

			switch (heading_depth)
			{
				case APACHE_LHS_INNER_PYLON:
				case APACHE_LHS_OUTER_PYLON:
				{
					if (number > 3)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x - 6, hardpoint_y + 19, 280, 61, 16, 16);
						}
						else
						{
							draw_sprite (hardpoint_x - 6, hardpoint_y + 19, 316, 61, 16, 16);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x - 6, hardpoint_y + 19, 262, 61, 16, 16);
						}
						else
						{
							draw_sprite (hardpoint_x - 6, hardpoint_y + 19, 298, 61, 16, 16);
						}
					}

					if (number > 2)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x + 10, hardpoint_y + 19, 280, 61, 16, 16);
						}
						else
						{
							draw_sprite (hardpoint_x + 10, hardpoint_y + 19, 316, 61, 16, 16);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x + 10, hardpoint_y + 19, 262, 61, 16, 16);
						}
						else
						{
							draw_sprite (hardpoint_x + 10, hardpoint_y + 19, 298, 61, 16, 16);
						}
					}

					if (number > 1)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x - 6, hardpoint_y + 35, 280, 61, 16, 16);
						}
						else
						{
							draw_sprite (hardpoint_x - 6, hardpoint_y + 35, 316, 61, 16, 16);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x - 6, hardpoint_y + 35, 262, 61, 16, 16);
						}
						else
						{
							draw_sprite (hardpoint_x - 6, hardpoint_y + 35, 298, 61, 16, 16);
						}
					}

					if (number > 0)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x + 10, hardpoint_y + 35, 280, 61, 16, 16);
						}
						else
						{
							draw_sprite (hardpoint_x + 10, hardpoint_y + 35, 316, 61, 16, 16);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x + 10, hardpoint_y + 35, 262, 61, 16, 16);
						}
						else
						{
							draw_sprite (hardpoint_x + 10, hardpoint_y + 35, 298, 61, 16, 16);
						}
					}

					break;
				}
				case APACHE_RHS_INNER_PYLON:
				case APACHE_RHS_OUTER_PYLON:
				{
					if (number > 3)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x + 10, hardpoint_y + 19, 280, 61, 16, 16);
						}
						else
						{
							draw_sprite (hardpoint_x + 10, hardpoint_y + 19, 316, 61, 16, 16);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x + 10, hardpoint_y + 19, 262, 61, 16, 16);
						}
						else
						{
							draw_sprite (hardpoint_x + 10, hardpoint_y + 19, 298, 61, 16, 16);
						}
					}

					if (number > 2)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x - 6, hardpoint_y + 19, 280, 61, 16, 16);
						}
						else
						{
							draw_sprite (hardpoint_x - 6, hardpoint_y + 19, 316, 61, 16, 16);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x - 6, hardpoint_y + 19, 262, 61, 16, 16);
						}
						else
						{
							draw_sprite (hardpoint_x - 6, hardpoint_y + 19, 298, 61, 16, 16);
						}
					}

					if (number > 1)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x + 10, hardpoint_y + 35, 280, 61, 16, 16);
						}
						else
						{
							draw_sprite (hardpoint_x + 10, hardpoint_y + 35, 316, 61, 16, 16);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x + 10, hardpoint_y + 35, 262, 61, 16, 16);
						}
						else
						{
							draw_sprite (hardpoint_x + 10, hardpoint_y + 35, 298, 61, 16, 16);
						}
					}

					if (number > 0)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x - 6, hardpoint_y + 35, 280, 61, 16, 16);
						}
						else
						{
							draw_sprite (hardpoint_x - 6, hardpoint_y + 35, 316, 61, 16, 16);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x - 6, hardpoint_y + 35, 262, 61, 16, 16);
						}
						else
						{
							draw_sprite (hardpoint_x - 6, hardpoint_y + 35, 298, 61, 16, 16);
						}
					}

					break;
				}
			}

			//
			// damage cross
			//

			if (damaged)
			{
				switch (heading_depth)
				{
					case APACHE_LHS_INNER_PYLON:
					{
						draw_sprite (47, 196, 334, 61, 32, 32);

						break;
					}
					case APACHE_RHS_INNER_PYLON:
					{
						draw_sprite (185, 196, 334, 61, 32, 32);

						break;
					}
					case APACHE_LHS_OUTER_PYLON:
					{
						draw_sprite (15, 196, 334, 61, 32, 32);

						break;
					}
					case APACHE_RHS_OUTER_PYLON:
					{
						draw_sprite (217, 196, 334, 61, 32, 32);

						break;
					}
				}
			}

			//
			// type
			//

			switch (heading_depth)
			{
				case APACHE_LHS_INNER_PYLON:
				{
					hardpoint_x = 47;
					hardpoint_y = 234;

					break;
				}
				case APACHE_RHS_INNER_PYLON:
				{
					hardpoint_x = 185;
					hardpoint_y = 234;

					break;
				}
				case APACHE_LHS_OUTER_PYLON:
				{
					hardpoint_x = 15;
					hardpoint_y = 234;

					break;
				}
				case APACHE_RHS_OUTER_PYLON:
				{
					hardpoint_x = 217;
					hardpoint_y = 234;

					break;
				}
			}

			if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_AGM114K_HELLFIRE_II)
			{
				if ((weapon_sub_type == selected_weapon) && (!damaged))
				{
					draw_sprite (hardpoint_x, hardpoint_y, 262, 3, 31, 12);
				}
				else
				{
					draw_sprite (hardpoint_x, hardpoint_y, 342, 3, 31, 12);
				}
			}
			else
			{
				if ((weapon_sub_type == selected_weapon) && (!damaged))
				{
					draw_sprite (hardpoint_x, hardpoint_y, 295, 3, 31, 12);
				}
				else
				{
					draw_sprite (hardpoint_x, hardpoint_y, 375, 3, 31, 12);
				}
			}
		}
		else
		{
			////////////////////////////////////////
			//
			// SMALL
			//
			////////////////////////////////////////

			//
			// pylon
			//

			switch (heading_depth)
			{
				case APACHE_LHS_INNER_PYLON:
				{
					hardpoint_x = 29;
					hardpoint_y = 348;

					break;
				}
				case APACHE_RHS_INNER_PYLON:
				{
					hardpoint_x = 98;
					hardpoint_y = 348;

					break;
				}
				case APACHE_LHS_OUTER_PYLON:
				{
					hardpoint_x = 13;
					hardpoint_y = 348;

					break;
				}
				case APACHE_RHS_OUTER_PYLON:
				{
					hardpoint_x = 114;
					hardpoint_y = 348;

					break;
				}
			}

			if ((weapon_sub_type == selected_weapon) && (!damaged))
			{
				draw_sprite (hardpoint_x, hardpoint_y, 133, 299, 10, 9);
			}
			else
			{
				draw_sprite (hardpoint_x, hardpoint_y, 144, 299, 10, 9);
			}

			//
			// missiles
			//

			switch (heading_depth)
			{
				case APACHE_LHS_INNER_PYLON:
				case APACHE_LHS_OUTER_PYLON:
				{
					if (number > 3)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x - 3, hardpoint_y + 10, 142, 290, 8, 8);
						}
						else
						{
							draw_sprite (hardpoint_x - 3, hardpoint_y + 10, 160, 290, 8, 8);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x - 3, hardpoint_y + 10, 133, 290, 8, 8);
						}
						else
						{
							draw_sprite (hardpoint_x - 3, hardpoint_y + 10, 151, 290, 8, 8);
						}
					}

					if (number > 2)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x + 5, hardpoint_y + 10, 142, 290, 8, 8);
						}
						else
						{
							draw_sprite (hardpoint_x + 5, hardpoint_y + 10, 160, 290, 8, 8);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x + 5, hardpoint_y + 10, 133, 290, 8, 8);
						}
						else
						{
							draw_sprite (hardpoint_x + 5, hardpoint_y + 10, 151, 290, 8, 8);
						}
					}

					if (number > 1)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x - 3, hardpoint_y + 18, 142, 290, 8, 8);
						}
						else
						{
							draw_sprite (hardpoint_x - 3, hardpoint_y + 18, 160, 290, 8, 8);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x - 3, hardpoint_y + 18, 133, 290, 8, 8);
						}
						else
						{
							draw_sprite (hardpoint_x - 3, hardpoint_y + 18, 151, 290, 8, 8);
						}
					}

					if (number > 0)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x + 5, hardpoint_y + 18, 142, 290, 8, 8);
						}
						else
						{
							draw_sprite (hardpoint_x + 5, hardpoint_y + 18, 160, 290, 8, 8);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x + 5, hardpoint_y + 18, 133, 290, 8, 8);
						}
						else
						{
							draw_sprite (hardpoint_x + 5, hardpoint_y + 18, 151, 290, 8, 8);
						}
					}

					break;
				}
				case APACHE_RHS_INNER_PYLON:
				case APACHE_RHS_OUTER_PYLON:
				{
					if (number > 3)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x + 5, hardpoint_y + 10, 142, 290, 8, 8);
						}
						else
						{
							draw_sprite (hardpoint_x + 5, hardpoint_y + 10, 160, 290, 8, 8);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x + 5, hardpoint_y + 10, 133, 290, 8, 8);
						}
						else
						{
							draw_sprite (hardpoint_x + 5, hardpoint_y + 10, 151, 290, 8, 8);
						}
					}

					if (number > 2)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x - 3, hardpoint_y + 10, 142, 290, 8, 8);
						}
						else
						{
							draw_sprite (hardpoint_x - 3, hardpoint_y + 10, 160, 290, 8, 8);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x - 3, hardpoint_y + 10, 133, 290, 8, 8);
						}
						else
						{
							draw_sprite (hardpoint_x - 3, hardpoint_y + 10, 151, 290, 8, 8);
						}
					}

					if (number > 1)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x + 5, hardpoint_y + 18, 142, 290, 8, 8);
						}
						else
						{
							draw_sprite (hardpoint_x + 5, hardpoint_y + 18, 160, 290, 8, 8);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x + 5, hardpoint_y + 18, 133, 290, 8, 8);
						}
						else
						{
							draw_sprite (hardpoint_x + 5, hardpoint_y + 18, 151, 290, 8, 8);
						}
					}

					if (number > 0)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x - 3, hardpoint_y + 18, 142, 290, 8, 8);
						}
						else
						{
							draw_sprite (hardpoint_x - 3, hardpoint_y + 18, 160, 290, 8, 8);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x - 3, hardpoint_y + 18, 133, 290, 8, 8);
						}
						else
						{
							draw_sprite (hardpoint_x - 3, hardpoint_y + 18, 151, 290, 8, 8);
						}
					}

					break;
				}
			}

			//
			// damage cross
			//

			if (damaged)
			{
				switch (heading_depth)
				{
					case APACHE_LHS_INNER_PYLON:
					{
						draw_sprite (26, 358, 169, 290, 16, 16);

						break;
					}
					case APACHE_RHS_INNER_PYLON:
					{
						draw_sprite (95, 358, 169, 290, 16, 16);

						break;
					}
					case APACHE_LHS_OUTER_PYLON:
					{
						draw_sprite (10, 358, 169, 290, 16, 16);

						break;
					}
					case APACHE_RHS_OUTER_PYLON:
					{
						draw_sprite (111, 358, 169, 290, 16, 16);

						break;
					}
				}
			}

			//
			// type
			//

			switch (heading_depth)
			{
				case APACHE_LHS_INNER_PYLON:
				{
					hardpoint_x = 26;
					hardpoint_y = 377;

					break;
				}
				case APACHE_RHS_INNER_PYLON:
				{
					hardpoint_x = 95;
					hardpoint_y = 377;

					break;
				}
				case APACHE_LHS_OUTER_PYLON:
				{
					hardpoint_x = 10;
					hardpoint_y = 377;

					break;
				}
				case APACHE_RHS_OUTER_PYLON:
				{
					hardpoint_x = 111;
					hardpoint_y = 377;

					break;
				}
			}

			if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_AGM114K_HELLFIRE_II)
			{
				if ((weapon_sub_type == selected_weapon) && (!damaged))
				{
					draw_sprite (hardpoint_x, hardpoint_y, 133, 261, 15, 6);
				}
				else
				{
					draw_sprite (hardpoint_x, hardpoint_y, 173, 261, 15, 6);
				}
			}
			else
			{
				if ((weapon_sub_type == selected_weapon) && (!damaged))
				{
					draw_sprite (hardpoint_x, hardpoint_y, 149, 261, 15, 6);
				}
				else
				{
					draw_sprite (hardpoint_x, hardpoint_y, 189, 261, 15, 6);
				}
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	// Stingers
	//
	////////////////////////////////////////////////////////////////////////////////

	if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_AIM92_STINGER)
	{
		if (draw_large_mfd)
		{
			////////////////////////////////////////
			//
			// LARGE
			//
			////////////////////////////////////////

			//
			// missiles
			//

			switch (heading_depth)
			{
				case APACHE_LHS_WING_TIP_MOUNT:
				{
					if (number > 1)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (6, 144, 280, 61, 16, 16);
						}
						else
						{
							draw_sprite (6, 144, 316, 61, 16, 16);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (6, 144, 262, 61, 16, 16);
						}
						else
						{
							draw_sprite (6, 144, 298, 61, 16, 16);
						}
					}

					if (number > 0)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (6, 161, 280, 61, 16, 16);
						}
						else
						{
							draw_sprite (6, 161, 316, 61, 16, 16);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (6, 161, 262, 61, 16, 16);
						}
						else
						{
							draw_sprite (6, 161, 298, 61, 16, 16);
						}
					}

					break;
				}
				case APACHE_RHS_WING_TIP_MOUNT:
				{
					if (number > 1)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (242, 144, 280, 61, 16, 16);
						}
						else
						{
							draw_sprite (242, 144, 316, 61, 16, 16);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (242, 144, 262, 61, 16, 16);
						}
						else
						{
							draw_sprite (242, 144, 298, 61, 16, 16);
						}
					}

					if (number > 0)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (242, 161, 280, 61, 16, 16);
						}
						else
						{
							draw_sprite (242, 161, 316, 61, 16, 16);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (242, 161, 262, 61, 16, 16);
						}
						else
						{
							draw_sprite (242, 161, 298, 61, 16, 16);
						}
					}

					break;
				}
			}

			//
			// damage cross
			//

			if (damaged)
			{
				switch (heading_depth)
				{
					case APACHE_LHS_WING_TIP_MOUNT:
					{
						draw_sprite (6, 144, 368, 61, 17, 33);

						break;
					}
					case APACHE_RHS_WING_TIP_MOUNT:
					{
						draw_sprite (241, 144, 368, 61, 17, 33);

						break;
					}
				}
			}
		}
		else
		{
			////////////////////////////////////////
			//
			// SMALL
			//
			////////////////////////////////////////

			//
			// missiles
			//

			switch (heading_depth)
			{
				case APACHE_LHS_WING_TIP_MOUNT:
				{
					if (number > 1)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (5, 332, 142, 290, 8, 8);
						}
						else
						{
							draw_sprite (5, 332, 160, 290, 8, 8);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (5, 332, 133, 290, 8, 8);
						}
						else
						{
							draw_sprite (5, 332, 151, 290, 8, 8);
						}
					}

					if (number > 0)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (5, 340, 142, 290, 8, 8);
						}
						else
						{
							draw_sprite (5, 340, 160, 290, 8, 8);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (5, 340, 133, 290, 8, 8);
						}
						else
						{
							draw_sprite (5, 340, 151, 290, 8, 8);
						}
					}

					break;
				}
				case APACHE_RHS_WING_TIP_MOUNT:
				{
					if (number > 1)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (123, 332, 142, 290, 8, 8);
						}
						else
						{
							draw_sprite (123, 332, 160, 290, 8, 8);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (123, 332, 133, 290, 8, 8);
						}
						else
						{
							draw_sprite (123, 332, 151, 290, 8, 8);
						}
					}

					if (number > 0)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (123, 340, 142, 290, 8, 8);
						}
						else
						{
							draw_sprite (123, 340, 160, 290, 8, 8);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (123, 340, 133, 290, 8, 8);
						}
						else
						{
							draw_sprite (123, 340, 151, 290, 8, 8);
						}
					}

					break;
				}
			}

			//
			// damage cross
			//

			if (damaged)
			{
				switch (heading_depth)
				{
					case APACHE_LHS_WING_TIP_MOUNT:
					{
						draw_sprite (5, 332, 186, 290, 8, 17);

						break;
					}
					case APACHE_RHS_WING_TIP_MOUNT:
					{
						draw_sprite (122, 332, 186, 290, 8, 17);

						break;
					}
				}
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	// Chaff
	//
	////////////////////////////////////////////////////////////////////////////////

	if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_CHAFF)
	{
		if (draw_large_mfd)
		{
			////////////////////////////////////////
			//
			// LARGE
			//
			////////////////////////////////////////

			//
			// digits
			//

			if ((number > 0) && (!damaged))
			{
				draw_sprite (94, 160, 483, 3, 18, 14);

				v = 32;
			}
			else
			{
				v = 47;
			}

			sprintf (buffer, "%02d", number);

			if (buffer[0] == '0')
			{
				u = 364 + (9 * 10);
			}
			else
			{
				u = 364 + ((buffer[0] - '1') * 10);
			}

			draw_sprite (112, 161, u, v, 8, 12);

			if (buffer[1] == '0')
			{
				u = 364 + (9 * 10);
			}
			else
			{
				u = 364 + ((buffer[1] - '1') * 10);
			}

			draw_sprite (121, 161, u, v, 8, 12);

			//
			// damage cross
			//

			if (damaged)
			{
				draw_sprite (96, 159, 387, 61, 33, 17);
			}
		}
		else
		{
			////////////////////////////////////////
			//
			// SMALL
			//
			////////////////////////////////////////

			//
			// digits
			//

			if ((number > 0) && (!damaged))
			{
				draw_sprite (49, 340, 243, 261, 9, 7);

				v = 276;
			}
			else
			{
				v = 283;
			}

			sprintf (buffer, "%02d", number);

			if (buffer[0] == '0')
			{
				u = 184 + (9 * 5);
			}
			else
			{
				u = 184 + ((buffer[0] - '1') * 5);
			}

			draw_sprite (58, 341, u, v, 4, 6);

			if (buffer[1] == '0')
			{
				u = 184 + (9 * 5);
			}
			else
			{
				u = 184 + ((buffer[1] - '1') * 5);
			}

			draw_sprite (62, 341, u, v, 4, 6);

			//
			// damage cross
			//

			if (damaged)
			{
				draw_sprite (49, 339, 196, 290, 17, 9);
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	// Flare
	//
	////////////////////////////////////////////////////////////////////////////////

	if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_FLARE)
	{
		if (draw_large_mfd)
		{
			////////////////////////////////////////
			//
			// LARGE
			//
			////////////////////////////////////////

			//
			// digits
			//

			if ((number > 0) && (!damaged))
			{
				draw_sprite (134, 160, 503, 3, 15, 14);

				v = 32;
			}
			else
			{
				v = 47;
			}

			sprintf (buffer, "%02d", number);

			if (buffer[0] == '0')
			{
				u = 364 + (9 * 10);
			}
			else
			{
				u = 364 + ((buffer[0] - '1') * 10);
			}

			draw_sprite (149, 161, u, v, 8, 12);

			if (buffer[1] == '0')
			{
				u = 364 + (9 * 10);
			}
			else
			{
				u = 364 + ((buffer[1] - '1') * 10);
			}

			draw_sprite (158, 161, u, v, 8, 12);

			//
			// damage cross
			//

			if (damaged)
			{
				draw_sprite (135, 159, 387, 61, 33, 17);
			}
		}
		else
		{
			////////////////////////////////////////
			//
			// SMALL
			//
			////////////////////////////////////////

			//
			// digits
			//

			if ((number > 0) && (!damaged))
			{
				draw_sprite (69, 340, 253, 261, 8, 7);

				v = 276;
			}
			else
			{
				v = 283;
			}

			sprintf (buffer, "%02d", number);

			if (buffer[0] == '0')
			{
				u = 184 + (9 * 5);
			}
			else
			{
				u = 184 + ((buffer[0] - '1') * 5);
			}

			draw_sprite (77, 341, u, v, 4, 6);

			if (buffer[1] == '0')
			{
				u = 184 + (9 * 5);
			}
			else
			{
				u = 184 + ((buffer[1] - '1') * 5);
			}

			draw_sprite (81, 341, u, v, 4, 6);

			//
			// damage cross
			//

			if (damaged)
			{
				draw_sprite (69, 339, 196, 290, 17, 9);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_weapon_display_mfd (mfd_locations location, int draw_on_texture)
{
	char
		buffer[80];

	entity
		*en;

	entity_sub_types
		selected_weapon;

	float
		u;

	////////////////////////////////////////
	//
	// select cockpit graphics wrt time of day - required here for hi-res virtual cockpits
	//

	switch (get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE))
	{
		case DAY_SEGMENT_TYPE_DAWN:
		{
			base_cockpit_graphics_file = GRAPHICS_COCKPITS_APACHE_LEVEL2_BASE;

			break;
		}
		case DAY_SEGMENT_TYPE_DAY:
		{
			base_cockpit_graphics_file = GRAPHICS_COCKPITS_APACHE_LEVEL1_BASE;

			break;
		}
		case DAY_SEGMENT_TYPE_DUSK:
		{
			base_cockpit_graphics_file = GRAPHICS_COCKPITS_APACHE_LEVEL2_BASE;

			break;
		}
		case DAY_SEGMENT_TYPE_NIGHT:
		{
			base_cockpit_graphics_file = GRAPHICS_COCKPITS_APACHE_LEVEL3_BASE;

			break;
		}
	}

	#if DEMO_VERSION

	base_cockpit_graphics_file = GRAPHICS_COCKPITS_APACHE_LEVEL1_BASE;

	#endif

	//
	////////////////////////////////////////

	weapon_draw_on_texture = draw_on_texture;

	weapon_sprite_data = get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_WEAPONS_MFD_SPRITES);

	weapon_mask_data = get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_WEAPONS_MFD_SPRITES_MASK);

	weapon_sprite.mask_value = 0;

	en = get_gunship_entity ();

	selected_weapon = get_local_entity_int_value (en, INT_TYPE_SELECTED_WEAPON);

	if (draw_large_mfd)
	{
		if (location == MFD_LOCATION_LHS)
		{
			weapon_x_offset = (int) mfd_viewport_x_min + 38 - 4;
			weapon_y_offset = (int) mfd_viewport_y_min + 32 - 4;
		}
		else
		{
			weapon_x_offset = (int) mfd_viewport_x_min + 38 - 4;
			weapon_y_offset = (int) mfd_viewport_y_min + 32 - 4;
		}

		//
		// helicopter
		//

		draw_sprite (4, 4, 4, 4, 256, 256);

		//
		// arm
		//

		if (selected_weapon != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
		{
			draw_sprite (102, 116, 422, 3, 59, 22);
		}

		//
		// hardpoints
		//

		draw_weapon_hardpoint_info (APACHE_CHAIN_GUN_TURRET, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, selected_weapon);

		draw_weapon_hardpoint_info (APACHE_LHS_WING_TIP_MOUNT, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, selected_weapon);

		draw_weapon_hardpoint_info (APACHE_RHS_WING_TIP_MOUNT, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, selected_weapon);

		draw_weapon_hardpoint_info (APACHE_LHS_INNER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, selected_weapon);

		draw_weapon_hardpoint_info (APACHE_RHS_INNER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, selected_weapon);

		draw_weapon_hardpoint_info (APACHE_LHS_OUTER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, selected_weapon);

		draw_weapon_hardpoint_info (APACHE_RHS_OUTER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, selected_weapon);

		draw_weapon_hardpoint_info (APACHE_CHAFF_DISPENSER, ENTITY_SUB_TYPE_WEAPON_CHAFF, selected_weapon);

		draw_weapon_hardpoint_info (APACHE_FLARE_DISPENSER, ENTITY_SUB_TYPE_WEAPON_FLARE, selected_weapon);

		//
		// auto-countermeasures
		//

		if (get_global_auto_counter_measures ())
		{
			draw_sprite (108, 176, 520, 3, 47, 14);
		}

		//
		// rocket salvo
		//

		if
		(
			get_local_entity_weapon_available (en, ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255) ||
			get_local_entity_weapon_available (en, ENTITY_SUB_TYPE_WEAPON_HYDRA70_M261)
		)
		{
			draw_sprite (66, 268, 264, 165, 98, 16);

			if (rocket_salvo_size == ROCKET_SALVO_SIZE_ALL)
			{
				draw_sprite (167, 268, 365, 165, 34, 16);
			}
			else
			{
				sprintf (buffer, "%02d", rocket_salvo_size);

				if (buffer[0] == '0')
				{
					u = 364 + (9 * 10);
				}
				else
				{
					u = 364 + ((buffer[0] - '1') * 10);
				}

				draw_sprite (167, 270, u, 32, 8, 12);

				if (buffer[1] == '0')
				{
					u = 364 + (9 * 10);
				}
				else
				{
					u = 364 + ((buffer[1] - '1') * 10);
				}

				draw_sprite (175, 270, u, 32, 8, 12);
			}
		}
	}
	else
	{
		if (draw_on_texture)
		{
			weapon_x_offset = 0 - 4;
			weapon_y_offset = 0 - 262 - 3;
		}
		else
		{
			if (location == MFD_LOCATION_LHS)
			{
				weapon_x_offset = (int) mfd_viewport_x_min - 4;
				weapon_y_offset = (int) mfd_viewport_y_min - 262 - 3;
			}
			else
			{
				weapon_x_offset = (int) mfd_viewport_x_min - 4;
				weapon_y_offset = (int) mfd_viewport_y_min - 262 - 3;
			}
		}

		//
		// helicopter
		//

		draw_sprite (4, 262 + 3, 4, 262, 128, 128);

		//
		// arm
		//

		if (selected_weapon != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
		{
			draw_sprite (53, 318, 213, 261, 29, 11);
		}

		//
		// hardpoints
		//

		draw_weapon_hardpoint_info (APACHE_CHAIN_GUN_TURRET, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, selected_weapon);

		draw_weapon_hardpoint_info (APACHE_LHS_WING_TIP_MOUNT, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, selected_weapon);

		draw_weapon_hardpoint_info (APACHE_RHS_WING_TIP_MOUNT, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, selected_weapon);

		draw_weapon_hardpoint_info (APACHE_LHS_INNER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, selected_weapon);

		draw_weapon_hardpoint_info (APACHE_RHS_INNER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, selected_weapon);

		draw_weapon_hardpoint_info (APACHE_LHS_OUTER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, selected_weapon);

		draw_weapon_hardpoint_info (APACHE_RHS_OUTER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, selected_weapon);

		draw_weapon_hardpoint_info (APACHE_CHAFF_DISPENSER, ENTITY_SUB_TYPE_WEAPON_CHAFF, selected_weapon);

		draw_weapon_hardpoint_info (APACHE_FLARE_DISPENSER, ENTITY_SUB_TYPE_WEAPON_FLARE, selected_weapon);

		//
		// auto-countermeasures
		//

		if (get_global_auto_counter_measures ())
		{
			draw_sprite (56, 347, 262, 261, 23, 7);
		}

		//
		// rocket salvo
		//

		if
		(
			get_local_entity_weapon_available (en, ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255) ||
			get_local_entity_weapon_available (en, ENTITY_SUB_TYPE_WEAPON_HYDRA70_M261)
		)
		{
			draw_sprite (34, 382 + 3, 133, 342, 49, 8);

			if (rocket_salvo_size == ROCKET_SALVO_SIZE_ALL)
			{
				draw_sprite (84, 382 + 3, 183, 342, 18, 8);
			}
			else
			{
				sprintf (buffer, "%02d", rocket_salvo_size);

				if (buffer[0] == '0')
				{
					u = 184 + (9 * 5);
				}
				else
				{
					u = 184 + ((buffer[0] - '1') * 5);
				}

				draw_sprite (86, 383 + 3, u, 276, 4, 6);

				if (buffer[1] == '0')
				{
					u = 184 + (9 * 5);
				}
				else
				{
					u = 184 + ((buffer[1] - '1') * 5);
				}

				draw_sprite (90, 383 + 3, u, 276, 4, 6);
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

static float print_system_message (char *equipment, char *warning, int fail, float y_adjust)
{
	char
		*status;

	float
		width;

	ASSERT (equipment);

	ASSERT (warning);

	set_2d_mono_font_position (-0.8, 0.90);

	set_mono_font_rel_position (1.0, y_adjust);

	print_mono_font_string (equipment);

	if (fail)
	{
		status = warning;
	}
	else
	{
		status = "OK";
	}

	width = get_mono_font_string_width (status);

	set_2d_mono_font_position (0.8, 0.90);

	set_mono_font_rel_position (-width, y_adjust);

	print_mono_font_string (status);

	y_adjust += get_mono_font_char_height ('X');

	if (draw_large_mfd)
	{
		y_adjust += 2;
	}

	return (y_adjust);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_system_display_mfd (void)
{
	float
		y_adjust;

	set_mono_font_colour (MFD_COLOUR1);

	if (draw_large_mfd)
	{
		set_mono_font_type (MONO_FONT_TYPE_7X12);

		y_adjust = 5.0;
	}
	else
	{
		set_mono_font_type (MONO_FONT_TYPE_3X6);

		y_adjust = -2.0;
	}

	y_adjust = print_system_message ("RADAR", "FAIL", apache_damage.radar, y_adjust);

	y_adjust = print_system_message ("FLIR", "FAIL", apache_damage.flir, y_adjust);

	y_adjust = print_system_message ("DTV", "FAIL", apache_damage.dtv, y_adjust);

	y_adjust = print_system_message ("DVO", "FAIL", apache_damage.dvo, y_adjust);

	y_adjust = print_system_message ("LASER DESIGNATOR", "FAIL", apache_damage.laser_designator, y_adjust);

	y_adjust = print_system_message ("RADAR JAMMER", "FAIL", apache_damage.radar_jammer, y_adjust);

	y_adjust = print_system_message ("IR JAMMER", "FAIL", apache_damage.infra_red_jammer, y_adjust);

	y_adjust = print_system_message ("NAVIGATION COMPUTER", "FAIL", apache_damage.navigation_computer, y_adjust);

	y_adjust = print_system_message ("COMMUNICATIONS", "FAIL", apache_damage.communications, y_adjust);

	y_adjust = print_system_message ("RADAR WARNING SYSTEM", "FAIL", apache_damage.radar_warning_system, y_adjust);

	y_adjust = print_system_message ("IHADSS", "FAIL", apache_damage.ihadss, y_adjust);

	y_adjust = print_system_message ("PNVS", "FAIL", apache_damage.pnvs, y_adjust);

	y_adjust = print_system_message ("STABILISER", "FAIL", get_dynamics_damage_type (DYNAMICS_DAMAGE_STABILISER), y_adjust);

	y_adjust = print_system_message ("MAIN ROTOR", "FAIL", get_dynamics_damage_type (DYNAMICS_DAMAGE_MAIN_ROTOR), y_adjust);

	y_adjust = print_system_message ("TAIL ROTOR", "DAMAGED", get_dynamics_damage_type (DYNAMICS_DAMAGE_TAIL_ROTOR), y_adjust);

	y_adjust = print_system_message ("ENGINE 1", "DAMAGED", get_dynamics_damage_type (DYNAMICS_DAMAGE_LEFT_ENGINE), y_adjust);

	y_adjust = print_system_message ("ENGINE 2", "DAMAGED", get_dynamics_damage_type (DYNAMICS_DAMAGE_RIGHT_ENGINE), y_adjust);

	y_adjust = print_system_message ("HYDRAULIC PRESSURE", "LOW", get_dynamics_damage_type (DYNAMICS_DAMAGE_LOW_HYDRAULICS), y_adjust);

	if (get_dynamics_damage_type (DYNAMICS_DAMAGE_LOW_OIL_PRESSURE))
	{
		y_adjust = print_system_message ("OIL PRESSURE", "LOW", get_dynamics_damage_type (DYNAMICS_DAMAGE_LOW_OIL_PRESSURE), y_adjust);
	}
	else
	{
		y_adjust = print_system_message ("OIL PRESSURE", "HIGH", get_dynamics_damage_type (DYNAMICS_DAMAGE_HIGH_OIL_PRESSURE), y_adjust);
	}

	//
	// fire extinguisher
	//

	if (draw_large_mfd)
	{
		y_adjust += 14;
	}
	else
	{
		y_adjust += 3;
	}

	y_adjust = print_system_message ("FIRE EXTINGUISHER", "USED", fire_extinguisher_used, y_adjust);
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
		buffer[80], buffer2[10];

	int
		i;

	float
		x1,
		y1,
		y2,
		y3,
		bar_value,
		x_adjust,
		digital_readout;

	set_mono_font_colour (MFD_COLOUR1);

	if (draw_large_mfd)
	{
		set_mono_font_type (MONO_FONT_TYPE_7X12);
	}
	else
	{
		set_mono_font_type (MONO_FONT_TYPE_3X6);
	}

	////////////////////////////////////////
	//
	// engine torque
	//
	////////////////////////////////////////

	set_2d_mono_font_position (-0.85, 0.85);

	if (draw_large_mfd)
	{
		set_mono_font_rel_position (-6.0, -16.0);
	}
	else
	{
		set_mono_font_rel_position (-4.0, -7.0);
	}

	print_mono_font_string ("TORQUE");

	//
	// engine 1 torque
	//

	digital_readout = bound (current_flight_dynamics->left_engine_torque.value, 0.0, 120.0);

	convert_float_to_int (digital_readout, &i);

	sprintf (buffer, "%03d", i);

	set_2d_mono_font_position (-0.85, -0.35);

	if (draw_large_mfd)
	{
		set_mono_font_rel_position (-13.0, 8.0);
	}
	else
	{
		set_mono_font_rel_position (-6.0, 3.0);
	}

	print_mono_font_string (buffer);

	bar_value = digital_readout * 0.01;

	get_2d_float_screen_coordinates (-0.85, 0.85, &x1, &y1);
	get_2d_float_screen_y_coordinate (-0.35, &y2);
	get_2d_float_screen_y_coordinate (-0.35 + bar_value, &y3);

	if (draw_large_mfd)
	{
		draw_line (x1, y1, x1, y2, MFD_COLOUR1);
		draw_line (x1 + 4.0, y1, x1 + 4.0, y2, MFD_COLOUR1);
		draw_line (x1, y1, x1 + 4.0, y1, MFD_COLOUR1);
		draw_line (x1, y2, x1 + 4.0, y2, MFD_COLOUR1);

		draw_line (x1 + 1.0, y2, x1 + 1.0, y3, MFD_COLOUR1);
		draw_line (x1 + 2.0, y2, x1 + 2.0, y3, MFD_COLOUR1);
		draw_line (x1 + 3.0, y2, x1 + 3.0, y3, MFD_COLOUR1);

		draw_mono_sprite (large_engine_bar_marker, x1 + 5.0, y1 + 30.0, MFD_COLOUR1);
	}
	else
	{
		draw_line (x1, y1, x1, y2, MFD_COLOUR1);
		draw_line (x1 + 2.0, y1, x1 + 2.0, y2, MFD_COLOUR1);
		draw_line (x1, y1, x1 + 2.0, y1, MFD_COLOUR1);
		draw_line (x1, y2, x1 + 2.0, y2, MFD_COLOUR1);

		draw_line (x1 + 1.0, y2, x1 + 1.0, y3, MFD_COLOUR1);

		draw_mono_sprite (small_engine_bar_marker, x1 + 3.0, y1 + 11.0, MFD_COLOUR1);
	}

	//
	// engine 2 torque
	//

	digital_readout = bound (current_flight_dynamics->right_engine_torque.value, 0.0, 120.0);

	convert_float_to_int (digital_readout, &i);

	sprintf (buffer, "%03d", i);

	set_2d_mono_font_position (-0.65 - 0.025, -0.35);

	if (draw_large_mfd)
	{
		set_mono_font_rel_position (-4.0, 8.0);
	}
	else
	{
		set_mono_font_rel_position (-2.0, 3.0);
	}

	print_mono_font_string (buffer);

	bar_value = digital_readout * 0.01;

	get_2d_float_screen_coordinates (-0.65 - 0.025, 0.85, &x1, &y1);
	get_2d_float_screen_y_coordinate (-0.35, &y2);
	get_2d_float_screen_y_coordinate (-0.35 + bar_value, &y3);

	if (draw_large_mfd)
	{
		draw_line (x1, y1, x1, y2, MFD_COLOUR1);
		draw_line (x1 + 4.0, y1, x1 + 4.0, y2, MFD_COLOUR1);
		draw_line (x1, y1, x1 + 4.0, y1, MFD_COLOUR1);
		draw_line (x1, y2, x1 + 4.0, y2, MFD_COLOUR1);

		draw_line (x1 + 1.0, y2, x1 + 1.0, y3, MFD_COLOUR1);
		draw_line (x1 + 2.0, y2, x1 + 2.0, y3, MFD_COLOUR1);
		draw_line (x1 + 3.0, y2, x1 + 3.0, y3, MFD_COLOUR1);

		draw_mono_sprite (large_engine_bar_marker, x1 - 7.0, y1 + 30.0, MFD_COLOUR1);
	}
	else
	{
		draw_line (x1, y1, x1, y2, MFD_COLOUR1);
		draw_line (x1 + 2.0, y1, x1 + 2.0, y2, MFD_COLOUR1);
		draw_line (x1, y1, x1 + 2.0, y1, MFD_COLOUR1);
		draw_line (x1, y2, x1 + 2.0, y2, MFD_COLOUR1);

		draw_line (x1 + 1.0, y2, x1 + 1.0, y3, MFD_COLOUR1);

		draw_mono_sprite (small_engine_bar_marker, x1 - 4.0, y1 + 11.0, MFD_COLOUR1);
	}

	////////////////////////////////////////
	//
	// engine temperature
	//
	////////////////////////////////////////

	set_2d_mono_font_position (-0.35, 0.85);

	if (draw_large_mfd)
	{
		set_mono_font_rel_position (2.0, -16.0);
	}
	else
	{
		set_mono_font_rel_position (0.0, -7.0);
	}

	print_mono_font_string ("TGT");

	//
	// engine 1 temperature
	//

	digital_readout = bound (current_flight_dynamics->left_engine_temp.value, 0.0, 1000.0);
	convert_float_to_int (digital_readout * 0.1, &i);
	sprintf (buffer, "%03d", i);

	set_2d_mono_font_position (-0.35, -0.35);

	if (draw_large_mfd)
	{
		set_mono_font_rel_position (-13.0, 8.0);
	}
	else
	{
		set_mono_font_rel_position (-6.0, 3.0);
	}

	print_mono_font_string (buffer);

	digital_readout = bound (current_flight_dynamics->left_engine_temp.value * 0.125, 0.0, 125.0);
	bar_value = digital_readout * 0.0096;

	get_2d_float_screen_coordinates (-0.35, 0.85, &x1, &y1);
	get_2d_float_screen_y_coordinate (-0.35, &y2);
	get_2d_float_screen_y_coordinate (-0.35 + bar_value, &y3);

	if (draw_large_mfd)
	{
		draw_line (x1, y1, x1, y2, MFD_COLOUR1);
		draw_line (x1 + 4.0, y1, x1 + 4.0, y2, MFD_COLOUR1);
		draw_line (x1, y1, x1 + 4.0, y1, MFD_COLOUR1);
		draw_line (x1, y2, x1 + 4.0, y2, MFD_COLOUR1);

		draw_line (x1 + 1.0, y2, x1 + 1.0, y3, MFD_COLOUR1);
		draw_line (x1 + 2.0, y2, x1 + 2.0, y3, MFD_COLOUR1);
		draw_line (x1 + 3.0, y2, x1 + 3.0, y3, MFD_COLOUR1);

		draw_mono_sprite (large_engine_bar_marker, x1 + 5.0, y1 + 37.0, MFD_COLOUR1);
	}
	else
	{
		draw_line (x1, y1, x1, y2, MFD_COLOUR1);
		draw_line (x1 + 2.0, y1, x1 + 2.0, y2, MFD_COLOUR1);
		draw_line (x1, y1, x1 + 2.0, y1, MFD_COLOUR1);
		draw_line (x1, y2, x1 + 2.0, y2, MFD_COLOUR1);

		draw_line (x1 + 1.0, y2, x1 + 1.0, y3, MFD_COLOUR1);

		draw_mono_sprite (small_engine_bar_marker, x1 + 3.0, y1 + 13.0, MFD_COLOUR1);
	}

	//
	// engine 2 temperature
	//

	digital_readout = bound (current_flight_dynamics->right_engine_temp.value, 0.0, 1000.0);
	convert_float_to_int (digital_readout * 0.1, &i);
	sprintf (buffer, "%03d", i);

	set_2d_mono_font_position (-0.15 - 0.025, -0.35);

	if (draw_large_mfd)
	{
		set_mono_font_rel_position (-4.0, 8.0);
	}
	else
	{
		set_mono_font_rel_position (-2.0, 3.0);
	}

	print_mono_font_string (buffer);

	digital_readout = bound (current_flight_dynamics->right_engine_temp.value * 0.125, 0.0, 125.0);
	bar_value = digital_readout * 0.0096;

	get_2d_float_screen_coordinates (-0.15 - 0.025, 0.85, &x1, &y1);
	get_2d_float_screen_y_coordinate (-0.35, &y2);
	get_2d_float_screen_y_coordinate (-0.35 + bar_value, &y3);

	if (draw_large_mfd)
	{
		draw_line (x1, y1, x1, y2, MFD_COLOUR1);
		draw_line (x1 + 4.0, y1, x1 + 4.0, y2, MFD_COLOUR1);
		draw_line (x1, y1, x1 + 4.0, y1, MFD_COLOUR1);
		draw_line (x1, y2, x1 + 4.0, y2, MFD_COLOUR1);

		draw_line (x1 + 1.0, y2, x1 + 1.0, y3, MFD_COLOUR1);
		draw_line (x1 + 2.0, y2, x1 + 2.0, y3, MFD_COLOUR1);
		draw_line (x1 + 3.0, y2, x1 + 3.0, y3, MFD_COLOUR1);

		draw_mono_sprite (large_engine_bar_marker, x1 - 7.0, y1 + 37.0, MFD_COLOUR1);
	}
	else
	{
		draw_line (x1, y1, x1, y2, MFD_COLOUR1);
		draw_line (x1 + 2.0, y1, x1 + 2.0, y2, MFD_COLOUR1);
		draw_line (x1, y1, x1 + 2.0, y1, MFD_COLOUR1);
		draw_line (x1, y2, x1 + 2.0, y2, MFD_COLOUR1);

		draw_line (x1 + 1.0, y2, x1 + 1.0, y3, MFD_COLOUR1);

		draw_mono_sprite (small_engine_bar_marker, x1 - 4.0, y1 + 13.0, MFD_COLOUR1);
	}

	////////////////////////////////////////
	//
	// engine and rotor rpm
	//
	////////////////////////////////////////

	//
	// engine 1 rpm
	//

	set_2d_mono_font_position (0.1, 0.85);

	if (draw_large_mfd)
	{
		set_mono_font_rel_position (-6.0, -16.0);

		print_mono_font_char ('N');

		set_mono_font_rel_position (0.0, 2.0);

		print_mono_font_char ('P');
	}
	else
	{
		set_mono_font_rel_position (-2.0, -7.0);

		print_mono_font_char ('N');

		set_mono_font_rel_position (0.0, 1.0);

		print_mono_font_char ('P');
	}

	digital_readout = bound (current_flight_dynamics->left_engine_rpm.value, 0.0, 120.0);

	convert_float_to_int (digital_readout, &i);

	sprintf (buffer, "%03d", i);

	set_2d_mono_font_position (0.1 + 0.05, -0.35);

	if (draw_large_mfd)
	{
		set_mono_font_rel_position (-13.0, 8.0);
	}
	else
	{
		set_mono_font_rel_position (-6.0, 3.0);
	}

	print_mono_font_string (buffer);

	bar_value = digital_readout * 0.01;

	get_2d_float_screen_coordinates (0.1, 0.85, &x1, &y1);
	get_2d_float_screen_y_coordinate (-0.35, &y2);
	get_2d_float_screen_y_coordinate (-0.35 + bar_value, &y3);

	if (draw_large_mfd)
	{
		draw_line (x1, y1, x1, y2, MFD_COLOUR1);
		draw_line (x1 + 4.0, y1, x1 + 4.0, y2, MFD_COLOUR1);
		draw_line (x1, y1, x1 + 4.0, y1, MFD_COLOUR1);
		draw_line (x1, y2, x1 + 4.0, y2, MFD_COLOUR1);

		draw_line (x1 + 1.0, y2, x1 + 1.0, y3, MFD_COLOUR1);
		draw_line (x1 + 2.0, y2, x1 + 2.0, y3, MFD_COLOUR1);
		draw_line (x1 + 3.0, y2, x1 + 3.0, y3, MFD_COLOUR1);

		draw_mono_sprite (large_engine_bar_marker, x1 - 7.0, y1 + 30.0, MFD_COLOUR1);
	}
	else
	{
		draw_line (x1, y1, x1, y2, MFD_COLOUR1);
		draw_line (x1 + 2.0, y1, x1 + 2.0, y2, MFD_COLOUR1);
		draw_line (x1, y1, x1 + 2.0, y1, MFD_COLOUR1);
		draw_line (x1, y2, x1 + 2.0, y2, MFD_COLOUR1);

		draw_line (x1 + 1.0, y2, x1 + 1.0, y3, MFD_COLOUR1);

		draw_mono_sprite (small_engine_bar_marker, x1 - 4.0, y1 + 11.0, MFD_COLOUR1);
	}

	//
	// rotor rpm
	//

	set_2d_mono_font_position (0.25 - 0.0125, 0.85);

	if (draw_large_mfd)
	{
		set_mono_font_rel_position (-6.0, -16.0);

		print_mono_font_char ('N');

		set_mono_font_rel_position (0.0, 2.0);

		print_mono_font_char ('R');
	}
	else
	{
		set_mono_font_rel_position (-2.0, -7.0);

		print_mono_font_char ('N');

		set_mono_font_rel_position (0.0, 1.0);

		print_mono_font_char ('R');
	}

	digital_readout = bound (current_flight_dynamics->main_rotor_rpm.value, 0.0, 125.0);

	convert_float_to_int (digital_readout, &i);

	sprintf (buffer, "%03d", i);

	set_2d_mono_font_position (0.25 - 0.0125, -0.15);

	if (draw_large_mfd)
	{
		set_mono_font_rel_position (-8.0, 8.0);
	}
	else
	{
		set_mono_font_rel_position (-4.0, 3.0);
	}

	print_mono_font_string (buffer);

	bar_value = digital_readout * 0.008;

	get_2d_float_screen_coordinates (0.25 - 0.0125, 0.85, &x1, &y1);
	get_2d_float_screen_y_coordinate (-0.15, &y2);
	get_2d_float_screen_y_coordinate (-0.15 + bar_value, &y3);

	if (draw_large_mfd)
	{
		draw_line (x1, y1, x1, y2, MFD_COLOUR1);
		draw_line (x1 + 4.0, y1, x1 + 4.0, y2, MFD_COLOUR1);
		draw_line (x1, y1, x1 + 4.0, y1, MFD_COLOUR1);
		draw_line (x1, y2, x1 + 4.0, y2, MFD_COLOUR1);

		draw_line (x1 + 1.0, y2, x1 + 1.0, y3, MFD_COLOUR1);
		draw_line (x1 + 2.0, y2, x1 + 2.0, y3, MFD_COLOUR1);
		draw_line (x1 + 3.0, y2, x1 + 3.0, y3, MFD_COLOUR1);

		draw_mono_sprite (large_engine_bar_marker, x1 - 7.0, y1 + 30.0, MFD_COLOUR1);
	}
	else
	{
		draw_line (x1, y1, x1, y2, MFD_COLOUR1);
		draw_line (x1 + 2.0, y1, x1 + 2.0, y2, MFD_COLOUR1);
		draw_line (x1, y1, x1 + 2.0, y1, MFD_COLOUR1);
		draw_line (x1, y2, x1 + 2.0, y2, MFD_COLOUR1);

		draw_line (x1 + 1.0, y2, x1 + 1.0, y3, MFD_COLOUR1);

		draw_mono_sprite (small_engine_bar_marker, x1 - 4.0, y1 + 11.0, MFD_COLOUR1);
	}

	//
	// engine 2 rpm
	//

	set_2d_mono_font_position (0.4 - 0.025, 0.85);

	if (draw_large_mfd)
	{
		set_mono_font_rel_position (-6.0, -16.0);

		print_mono_font_char ('N');

		set_mono_font_rel_position (0.0, 2.0);

		print_mono_font_char ('P');
	}
	else
	{
		set_mono_font_rel_position (-2.0, -7.0);

		print_mono_font_char ('N');

		set_mono_font_rel_position (0.0, 1.0);

		print_mono_font_char ('P');
	}

	digital_readout = bound (current_flight_dynamics->right_engine_rpm.value, 0.0, 120.0);

	convert_float_to_int (digital_readout, &i);

	sprintf (buffer, "%03d", i);

	set_2d_mono_font_position (0.4 - 0.05, -0.35);

	if (draw_large_mfd)
	{
		set_mono_font_rel_position (-4.0, 8.0);
	}
	else
	{
		set_mono_font_rel_position (-2.0, 3.0);
	}

	print_mono_font_string (buffer);

	bar_value = digital_readout * 0.01;

	get_2d_float_screen_coordinates (0.4 - 0.025, 0.85, &x1, &y1);
	get_2d_float_screen_y_coordinate (-0.35, &y2);
	get_2d_float_screen_y_coordinate (-0.35 + bar_value, &y3);

	if (draw_large_mfd)
	{
		draw_line (x1, y1, x1, y2, MFD_COLOUR1);
		draw_line (x1 + 4.0, y1, x1 + 4.0, y2, MFD_COLOUR1);
		draw_line (x1, y1, x1 + 4.0, y1, MFD_COLOUR1);
		draw_line (x1, y2, x1 + 4.0, y2, MFD_COLOUR1);

		draw_line (x1 + 1.0, y2, x1 + 1.0, y3, MFD_COLOUR1);
		draw_line (x1 + 2.0, y2, x1 + 2.0, y3, MFD_COLOUR1);
		draw_line (x1 + 3.0, y2, x1 + 3.0, y3, MFD_COLOUR1);

		draw_mono_sprite (large_engine_bar_marker, x1 - 7.0, y1 + 30.0, MFD_COLOUR1);
	}
	else
	{
		draw_line (x1, y1, x1, y2, MFD_COLOUR1);
		draw_line (x1 + 2.0, y1, x1 + 2.0, y2, MFD_COLOUR1);
		draw_line (x1, y1, x1 + 2.0, y1, MFD_COLOUR1);
		draw_line (x1, y2, x1 + 2.0, y2, MFD_COLOUR1);

		draw_line (x1 + 1.0, y2, x1 + 1.0, y3, MFD_COLOUR1);

		draw_mono_sprite (small_engine_bar_marker, x1 - 4.0, y1 + 11.0, MFD_COLOUR1);
	}

	////////////////////////////////////////
	//
	// fuel
	//
	////////////////////////////////////////

	set_2d_mono_font_position (-0.8, -0.7);

	if (draw_large_mfd)
	{
		set_mono_font_rel_position (2.0, -16.0);
	}
	else
	{
		set_mono_font_rel_position (0.0, -7.0);
	}

	print_mono_font_string ("FUEL");

	digital_readout = bound (kilograms_to_pounds (current_flight_dynamics->fuel_weight.value), 0.0, 2500.0);
	convert_float_to_int (digital_readout, &i);
	sprintf (buffer, "%04dlbs", i);

	set_2d_mono_font_position (-0.8, -0.7);

	if (draw_large_mfd)
	{
		set_mono_font_rel_position (-12.0, 8.0);
	}
	else
	{
		set_mono_font_rel_position (-6.0, 3.0);
	}

	print_mono_font_string (buffer);

	////////////////////////////////////////
	//
	// NG RPM left engine
	//
	////////////////////////////////////////

	set_2d_mono_font_position (0.65, 0.85);

	if (draw_large_mfd)
	{
		set_mono_font_rel_position (-6.0, -16.0);

		print_mono_font_char ('N');

		set_mono_font_rel_position (0.0, 2.0);

		print_mono_font_char ('G');
	}
	else
	{
		set_mono_font_rel_position (-2.0, -7.0);

		print_mono_font_char ('N');

		set_mono_font_rel_position (0.0, 1.0);

		print_mono_font_char ('G');
	}

	digital_readout = bound (current_flight_dynamics->left_engine_n1_rpm.value, 0.0, 120.0);
	convert_float_to_int (digital_readout, &i);
	sprintf (buffer, "%03d", i);

	set_2d_mono_font_position (0.65 - 0.05, -0.35);

	if (draw_large_mfd)
		set_mono_font_rel_position (-4.0, 8.0);
	else
		set_mono_font_rel_position (-2.0, 3.0);

	print_mono_font_string (buffer);

	bar_value = current_flight_dynamics->left_engine_n1_rpm.value * 0.01;
	
	get_2d_float_screen_coordinates (0.65 - 0.0125, 0.85, &x1, &y1);
	get_2d_float_screen_y_coordinate (-0.35, &y2);
	get_2d_float_screen_y_coordinate (-0.35 + bar_value, &y3);

	if (draw_large_mfd)
	{
		draw_line (x1, y1, x1, y2, MFD_COLOUR1);
		draw_line (x1 + 4.0, y1, x1 + 4.0, y2, MFD_COLOUR1);
		draw_line (x1, y1, x1 + 4.0, y1, MFD_COLOUR1);
		draw_line (x1, y2, x1 + 4.0, y2, MFD_COLOUR1);

		draw_line (x1 + 1.0, y2, x1 + 1.0, y3, MFD_COLOUR1);
		draw_line (x1 + 2.0, y2, x1 + 2.0, y3, MFD_COLOUR1);
		draw_line (x1 + 3.0, y2, x1 + 3.0, y3, MFD_COLOUR1);
		
		draw_mono_sprite (large_engine_bar_marker, x1 - 7.0, y1 + 30.0, MFD_COLOUR1);
	}
	else
	{
		draw_line (x1, y1, x1, y2, MFD_COLOUR1);
		draw_line (x1 + 2.0, y1, x1 + 2.0, y2, MFD_COLOUR1);
		draw_line (x1, y1, x1 + 2.0, y1, MFD_COLOUR1);
		draw_line (x1, y2, x1 + 2.0, y2, MFD_COLOUR1);

		draw_line (x1 + 1.0, y2, x1 + 1.0, y3, MFD_COLOUR1);

		draw_mono_sprite (small_engine_bar_marker, x1 + 4.0, y1 + 11.0, MFD_COLOUR1);
		draw_mono_sprite (small_engine_bar_marker, x1 + 4.0, y1 + 33.0, MFD_COLOUR1);
	}

	////////////////////////////////////////
	//
	// NG RPM right engine
	//
	////////////////////////////////////////

	set_2d_mono_font_position (0.85, 0.85);

	if (draw_large_mfd)
	{
		set_mono_font_rel_position (-6.0, -16.0);

		print_mono_font_char ('N');

		set_mono_font_rel_position (0.0, 2.0);

		print_mono_font_char ('G');
	}
	else
	{
		set_mono_font_rel_position (-2.0, -7.0);

		print_mono_font_char ('N');

		set_mono_font_rel_position (0.0, 1.0);

		print_mono_font_char ('G');
	}

	digital_readout = bound (current_flight_dynamics->right_engine_n1_rpm.value, 0.0, 120.0);
	convert_float_to_int (digital_readout, &i);
	sprintf (buffer, "%03d", i);

	set_2d_mono_font_position (0.85, -0.35);

	if (draw_large_mfd)
		set_mono_font_rel_position (-4.0, 8.0);
	else
		set_mono_font_rel_position (-2.0, 3.0);

	print_mono_font_string (buffer);

	bar_value = current_flight_dynamics->right_engine_n1_rpm.value * 0.01;
	
	get_2d_float_screen_coordinates (0.85 - 0.0125, 0.85, &x1, &y1);
	get_2d_float_screen_y_coordinate (-0.35, &y2);
	get_2d_float_screen_y_coordinate (-0.35 + bar_value, &y3);

	if (draw_large_mfd)
	{
		draw_line (x1, y1, x1, y2, MFD_COLOUR1);
		draw_line (x1 + 4.0, y1, x1 + 4.0, y2, MFD_COLOUR1);
		draw_line (x1, y1, x1 + 4.0, y1, MFD_COLOUR1);
		draw_line (x1, y2, x1 + 4.0, y2, MFD_COLOUR1);

		draw_line (x1 + 1.0, y2, x1 + 1.0, y3, MFD_COLOUR1);
		draw_line (x1 + 2.0, y2, x1 + 2.0, y3, MFD_COLOUR1);
		draw_line (x1 + 3.0, y2, x1 + 3.0, y3, MFD_COLOUR1);
	}
	else
	{
		draw_line (x1, y1, x1, y2, MFD_COLOUR1);
		draw_line (x1 + 2.0, y1, x1 + 2.0, y2, MFD_COLOUR1);
		draw_line (x1, y1, x1 + 2.0, y1, MFD_COLOUR1);
		draw_line (x1, y2, x1 + 2.0, y2, MFD_COLOUR1);

		draw_line (x1 + 1.0, y2, x1 + 1.0, y3, MFD_COLOUR1);
		
		draw_mono_sprite (small_engine_bar_marker, x1 - 4.0, y1 + 33.0, MFD_COLOUR1);
		draw_mono_sprite (small_engine_bar_marker, x1 - 4.0, y1 + 11.0, MFD_COLOUR1);
	}
	
	////////////////////////////////////////
	//
	// Throttles
	//
	////////////////////////////////////////

	set_2d_mono_font_position (-0.25, -0.7);

	if (draw_large_mfd)
	{
		set_mono_font_rel_position (2.0, -16.0);
	}
	else
	{
		set_mono_font_rel_position (0.0, -7.0);
	}

	print_mono_font_string ("THROTTLE");

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

	set_2d_mono_font_position (0.0, -0.75);

	digital_readout = bound (current_flight_dynamics->right_engine_n1_rpm.max, 0.0, 110.0);
	convert_float_to_int (digital_readout, &i);

	if (i< 60)
		sprintf(buffer, " %s OFF ", buffer2);
	else if (i == 60)
		sprintf(buffer, " %s IDLE", buffer2);
	else if (i == 110.0)
		sprintf(buffer, " %s FLY ", buffer2);
	else
		sprintf(buffer, " %s %03d%%", buffer2, (i-60) * 2);

	x_adjust = get_mono_font_string_width (buffer) * -0.5;
	set_mono_font_rel_position (x_adjust, 0.0);
	print_mono_font_string (buffer);	

	////////////////////////////////////////

	set_2d_mono_font_position (0.5, -0.7);

	if (draw_large_mfd)
	{
		set_mono_font_rel_position (2.0, -16.0);
	}
	else
	{
		set_mono_font_rel_position (0.0, -7.0);
	}

	digital_readout = bound (current_flight_dynamics->apu_rpm.value + 0.5, 0.0, 100.0);
	convert_float_to_int (digital_readout, &i);

	sprintf(buffer, "APU %03d%%", i);

	print_mono_font_string (buffer);
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

void draw_apache_mfd_on_cockpit (float x_org, float y_org, int large_mfd, int draw_translucent_background, mfd_locations location)
{
	mfd_modes
		*mfd_mode;

	ASSERT ((location == MFD_LOCATION_LHS) || (location == MFD_LOCATION_RHS));

	if (location == MFD_LOCATION_LHS)
	{
		mfd_mode = &lhs_mfd_mode;
	}
	else
	{
		mfd_mode = &rhs_mfd_mode;
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
				(*mfd_mode == MFD_MODE_DAMAGED) ||
				(*mfd_mode == MFD_MODE_GROUND_RADAR) ||
				(*mfd_mode == MFD_MODE_AIR_RADAR) ||
				(*mfd_mode == MFD_MODE_TSD) ||
				(*mfd_mode == MFD_MODE_ASE) ||
				(*mfd_mode == MFD_MODE_WEAPON) ||
				(*mfd_mode == MFD_MODE_SYSTEM) ||
				(*mfd_mode == MFD_MODE_ENGINE)
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

					x_min = mfd_viewport_x_min;
					y_min = mfd_viewport_y_min;
					x_max = x_min + 128.0;
					y_max = y_min + 128.0;

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

	switch (*mfd_mode)
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
			draw_3d_flir_mfd (location);

			if (lock_screen (active_screen))
			{
				draw_layout_grid ();

				draw_2d_flir_mfd (TRUE, FALSE);

				unlock_screen (active_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_DTV:
		////////////////////////////////////////
		{
			draw_3d_dtv_mfd (location);

			if (lock_screen (active_screen))
			{
				draw_layout_grid ();

				draw_2d_dtv_mfd (TRUE, FALSE);

				unlock_screen (active_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_DVO:
		////////////////////////////////////////
		{
			draw_3d_dvo_mfd (location);

			if (lock_screen (active_screen))
			{
				draw_layout_grid ();

				draw_2d_dvo_mfd (TRUE, FALSE);

				unlock_screen (active_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_TSD:
		////////////////////////////////////////
		{
			if (lock_screen (active_screen))
			{
				draw_layout_grid ();

				draw_tactical_situation_display_mfd ();

				unlock_screen (active_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_ASE:
		////////////////////////////////////////
		{
			if (lock_screen (active_screen))
			{
				draw_layout_grid ();

				draw_aircraft_survivability_equipment_display_mfd ();

				unlock_screen (active_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_WEAPON:
		////////////////////////////////////////
		{
			if (lock_screen (active_screen))
			{
				draw_layout_grid ();

				draw_weapon_display_mfd (location, FALSE);

				unlock_screen (active_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_SYSTEM:
		////////////////////////////////////////
		{
			if (lock_screen (active_screen))
			{
				draw_layout_grid ();

				draw_system_display_mfd ();

				unlock_screen (active_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_ENGINE:
		////////////////////////////////////////
		{
			if (lock_screen (active_screen))
			{
				draw_layout_grid ();

				draw_engine_display_mfd ();

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

void draw_apache_mfd_on_texture (mfd_locations location)
{
	mfd_modes
		*mfd_mode;

	screen
		*mfd_texture_screen;

	ASSERT ((location == MFD_LOCATION_LHS) || (location == MFD_LOCATION_RHS));

	if (location == MFD_LOCATION_LHS)
	{
		mfd_mode = &lhs_mfd_mode;

		mfd_texture_screen = lhs_mfd_texture_screen;

		set_system_texture_screen (lhs_mfd_texture_screen, TEXTURE_INDEX_AVCKPT_DISPLAY_LHS_MFD);
	}
	else
	{
		mfd_mode = &rhs_mfd_mode;

		mfd_texture_screen = rhs_mfd_texture_screen;

		set_system_texture_screen (rhs_mfd_texture_screen, TEXTURE_INDEX_AVCKPT_DISPLAY_RHS_MFD);
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

	draw_large_mfd = FALSE;

	mfd_viewport_size = MFD_VIEWPORT_SMALL_SIZE;

	ASSERT (mfd_viewport_size <= MFD_TEXTURE_SIZE);

	mfd_viewport_x_org = MFD_VIEWPORT_TEXTURE_X_ORG;

	mfd_viewport_y_org = MFD_VIEWPORT_TEXTURE_Y_ORG;

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

	switch (*mfd_mode)
	{
		////////////////////////////////////////
		case MFD_MODE_OFF:
		////////////////////////////////////////
		{
			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, MFD_TEXTURE_SIZE - 1, MFD_TEXTURE_SIZE - 1, clear_mfd_colour);

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
				set_block (0, 0, MFD_TEXTURE_SIZE - 1, MFD_TEXTURE_SIZE - 1, clear_mfd_colour);

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
				set_block (0, 0, MFD_TEXTURE_SIZE - 1, MFD_TEXTURE_SIZE - 1, clear_mfd_colour);

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
				set_block (0, 0, MFD_TEXTURE_SIZE - 1, MFD_TEXTURE_SIZE - 1, clear_mfd_colour);

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
			if ((d3d_can_render_to_texture) && (!apache_damage.flir))
			{
				ASSERT (small_eo_3d_texture_screen);

				if (location == MFD_LOCATION_LHS)
				{
					set_system_texture_screen (small_eo_3d_texture_screen, TEXTURE_INDEX_AVCKPT_DISPLAY_LHS_MFD);
				}
				else
				{
					set_system_texture_screen (small_eo_3d_texture_screen, TEXTURE_INDEX_AVCKPT_DISPLAY_RHS_MFD);
				}

				draw_3d_eo_display_on_texture (&apache_flir, TARGET_ACQUISITION_SYSTEM_FLIR);

				set_active_screen (small_eo_3d_texture_screen);

				if (lock_screen (small_eo_3d_texture_screen))
				{
					draw_layout_grid ();

					draw_2d_flir_mfd (TRUE, FALSE);

					flush_screen_texture_graphics (small_eo_3d_texture_screen);

					unlock_screen (small_eo_3d_texture_screen);
				}

				set_pilots_full_screen_params (FALSE);
			}
			else
			{
				set_active_screen (mfd_texture_screen);

				if (lock_screen (mfd_texture_screen))
				{
					set_block (0, 0, MFD_TEXTURE_SIZE - 1, MFD_TEXTURE_SIZE - 1, clear_mfd_colour);

					draw_layout_grid ();

					draw_2d_flir_mfd (FALSE, FALSE);

					flush_screen_texture_graphics (mfd_texture_screen);

					unlock_screen (mfd_texture_screen);
				}
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_DTV:
		////////////////////////////////////////
		{
			if ((d3d_can_render_to_texture) && (!apache_damage.dtv))
			{
				ASSERT (small_eo_3d_texture_screen);

				if (location == MFD_LOCATION_LHS)
				{
					set_system_texture_screen (small_eo_3d_texture_screen, TEXTURE_INDEX_AVCKPT_DISPLAY_LHS_MFD);
				}
				else
				{
					set_system_texture_screen (small_eo_3d_texture_screen, TEXTURE_INDEX_AVCKPT_DISPLAY_RHS_MFD);
				}

				draw_3d_eo_display_on_texture (&apache_dtv, TARGET_ACQUISITION_SYSTEM_DTV);

				set_active_screen (small_eo_3d_texture_screen);

				if (lock_screen (small_eo_3d_texture_screen))
				{
					draw_layout_grid ();

					draw_2d_dtv_mfd (TRUE, FALSE);

					flush_screen_texture_graphics (small_eo_3d_texture_screen);

					unlock_screen (small_eo_3d_texture_screen);
				}

				set_pilots_full_screen_params (FALSE);
			}
			else
			{
				set_active_screen (mfd_texture_screen);

				if (lock_screen (mfd_texture_screen))
				{
					set_block (0, 0, MFD_TEXTURE_SIZE - 1, MFD_TEXTURE_SIZE - 1, clear_mfd_colour);

					draw_layout_grid ();

					draw_2d_dtv_mfd (FALSE, FALSE);

					flush_screen_texture_graphics (mfd_texture_screen);

					unlock_screen (mfd_texture_screen);
				}
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_DVO:
		////////////////////////////////////////
		{
			if ((d3d_can_render_to_texture) && (!apache_damage.dvo))
			{
				ASSERT (small_eo_3d_texture_screen);

				if (location == MFD_LOCATION_LHS)
				{
					set_system_texture_screen (small_eo_3d_texture_screen, TEXTURE_INDEX_AVCKPT_DISPLAY_LHS_MFD);
				}
				else
				{
					set_system_texture_screen (small_eo_3d_texture_screen, TEXTURE_INDEX_AVCKPT_DISPLAY_RHS_MFD);
				}

				draw_3d_eo_display_on_texture (&apache_dvo, TARGET_ACQUISITION_SYSTEM_DVO);

				set_active_screen (small_eo_3d_texture_screen);

				if (lock_screen (small_eo_3d_texture_screen))
				{
					draw_layout_grid ();

					draw_2d_dvo_mfd (TRUE, FALSE);

					flush_screen_texture_graphics (small_eo_3d_texture_screen);

					unlock_screen (small_eo_3d_texture_screen);
				}

				set_pilots_full_screen_params (FALSE);
			}
			else
			{
				set_active_screen (mfd_texture_screen);

				if (lock_screen (mfd_texture_screen))
				{
					set_block (0, 0, MFD_TEXTURE_SIZE - 1, MFD_TEXTURE_SIZE - 1, clear_mfd_colour);

					draw_layout_grid ();

					draw_2d_dvo_mfd (FALSE, FALSE);

					flush_screen_texture_graphics (mfd_texture_screen);

					unlock_screen (mfd_texture_screen);
				}
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_TSD:
		////////////////////////////////////////
		{
			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, MFD_TEXTURE_SIZE - 1, MFD_TEXTURE_SIZE - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_tactical_situation_display_mfd ();

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_ASE:
		////////////////////////////////////////
		{
			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, MFD_TEXTURE_SIZE - 1, MFD_TEXTURE_SIZE - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_aircraft_survivability_equipment_display_mfd ();

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_WEAPON:
		////////////////////////////////////////
		{
			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, MFD_TEXTURE_SIZE - 1, MFD_TEXTURE_SIZE - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_weapon_display_mfd (MFD_LOCATION_DONT_CARE, TRUE);

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_SYSTEM:
		////////////////////////////////////////
		{
			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, MFD_TEXTURE_SIZE - 1, MFD_TEXTURE_SIZE - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_system_display_mfd ();

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_ENGINE:
		////////////////////////////////////////
		{
			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, MFD_TEXTURE_SIZE - 1, MFD_TEXTURE_SIZE - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_engine_display_mfd ();

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			break;
		}
	}

	set_active_screen (video_screen);
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

void draw_overlaid_apache_mfd (float x_org, float y_org, float size, mfd_locations location)
{
	mfd_modes
		*mfd_mode;

	screen
		*mfd_texture_screen;

	texture_index_numbers
		texture_index;

	float
		mfd_screen_size,
		mfd_screen_half_size,
		mfd_screen_x_org,
		mfd_screen_y_org,
		mfd_screen_x_min,
		mfd_screen_y_min,
		mfd_screen_x_max,
		mfd_screen_y_max;

	ASSERT ((location == MFD_LOCATION_LHS) || (location == MFD_LOCATION_RHS));

	if (location == MFD_LOCATION_LHS)
	{
		mfd_mode = &lhs_mfd_mode;

		mfd_texture_screen = lhs_overlaid_mfd_texture_screen;

		texture_index = LHS_OVERLAID_MFD_TEXTURE_INDEX;
	}
	else
	{
		mfd_mode = &rhs_mfd_mode;

		mfd_texture_screen = rhs_overlaid_mfd_texture_screen;

		texture_index = RHS_OVERLAID_MFD_TEXTURE_INDEX;
	}

	if (*mfd_mode == MFD_MODE_OFF)
	{
		return;
	}

	////////////////////////////////////////
	//
	// scale position and size wrt screen resolution
	//
	////////////////////////////////////////

	if (get_global_unscaled_displays ())
	{
		float
			org_offset;

		mfd_screen_size = size;

		mfd_screen_half_size = mfd_screen_size * 0.5;

		mfd_screen_x_org = x_org * full_screen_width * (1.0 / 640.0);
		mfd_screen_y_org = y_org * full_screen_height * (1.0 / 480.0);

		org_offset = ((size * full_screen_width * (1.0 / 640.0)) - size) * 0.5;

		if (location == MFD_LOCATION_LHS)
		{
			mfd_screen_x_org -= org_offset;
		}
		else
		{
			mfd_screen_x_org += org_offset;
		}

		mfd_screen_y_org += org_offset;

		mfd_screen_x_min = mfd_screen_x_org - mfd_screen_half_size;
		mfd_screen_y_min = mfd_screen_y_org - mfd_screen_half_size;
		mfd_screen_x_max = mfd_screen_x_org + mfd_screen_half_size - 0.001;
		mfd_screen_y_max = mfd_screen_y_org + mfd_screen_half_size - 0.001;
	}
	else
	{
		mfd_screen_size = size * full_screen_width * (1.0 / 640.0);

		mfd_screen_half_size = mfd_screen_size * 0.5;

		mfd_screen_x_org = x_org * full_screen_width * (1.0 / 640.0);
		mfd_screen_y_org = y_org * full_screen_height * (1.0 / 480.0);

		mfd_screen_x_min = mfd_screen_x_org - mfd_screen_half_size;
		mfd_screen_y_min = mfd_screen_y_org - mfd_screen_half_size;
		mfd_screen_x_max = mfd_screen_x_org + mfd_screen_half_size - 0.001;
		mfd_screen_y_max = mfd_screen_y_org + mfd_screen_half_size - 0.001;
	}

	//
	// translate & scale values (EO 3D display does not match texture)
	//

	i_translate_3d = mfd_screen_x_min;
	j_translate_3d = mfd_screen_y_min;

	i_scale_3d = MFD_TEXTURE_SIZE / mfd_screen_size;
	j_scale_3d = MFD_TEXTURE_SIZE / mfd_screen_size;

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

	draw_large_mfd = FALSE;

	mfd_viewport_size = MFD_VIEWPORT_SMALL_SIZE;

	ASSERT (mfd_viewport_size <= MFD_TEXTURE_SIZE);

	mfd_viewport_x_org = MFD_VIEWPORT_TEXTURE_X_ORG;

	mfd_viewport_y_org = MFD_VIEWPORT_TEXTURE_Y_ORG;

	mfd_viewport_x_min = mfd_viewport_x_org - (mfd_viewport_size * 0.5);

	mfd_viewport_y_min = mfd_viewport_y_org - (mfd_viewport_size * 0.5);

	mfd_viewport_x_max = mfd_viewport_x_org + (mfd_viewport_size * 0.5) - 0.001;

	mfd_viewport_y_max = mfd_viewport_y_org + (mfd_viewport_size * 0.5) - 0.001;

	////////////////////////////////////////
	//
	// draw MFD display
	//
	////////////////////////////////////////

	switch (*mfd_mode)
	{
		////////////////////////////////////////
		case MFD_MODE_OFF:
		////////////////////////////////////////
		{
			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, MFD_TEXTURE_SIZE - 1, MFD_TEXTURE_SIZE - 1, clear_mfd_colour);

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
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, MFD_TEXTURE_SIZE - 1, MFD_TEXTURE_SIZE - 1, clear_mfd_colour);

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
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, MFD_TEXTURE_SIZE - 1, MFD_TEXTURE_SIZE - 1, clear_mfd_colour);

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
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, MFD_TEXTURE_SIZE - 1, MFD_TEXTURE_SIZE - 1, clear_mfd_colour);

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
			if (!apache_damage.flir)
			{
				draw_overlaid_3d_eo_display (&apache_flir, TARGET_ACQUISITION_SYSTEM_FLIR, mfd_screen_x_min, mfd_screen_y_min, mfd_screen_size);
			}
			else
			{
				draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);
			}

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, MFD_TEXTURE_SIZE - 1, MFD_TEXTURE_SIZE - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_2d_flir_mfd (TRUE, TRUE);

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			set_pilots_full_screen_params (FALSE);

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_DTV:
		////////////////////////////////////////
		{
			if (!apache_damage.dtv)
			{
				draw_overlaid_3d_eo_display (&apache_dtv, TARGET_ACQUISITION_SYSTEM_DTV, mfd_screen_x_min, mfd_screen_y_min, mfd_screen_size);
			}
			else
			{
				draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);
			}

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, MFD_TEXTURE_SIZE - 1, MFD_TEXTURE_SIZE - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_2d_dtv_mfd (TRUE, TRUE);

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			set_pilots_full_screen_params (FALSE);

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_DVO:
		////////////////////////////////////////
		{
			if (!apache_damage.dvo)
			{
				draw_overlaid_3d_eo_display (&apache_dvo, TARGET_ACQUISITION_SYSTEM_DVO, mfd_screen_x_min, mfd_screen_y_min, mfd_screen_size);
			}
			else
			{
				draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);
			}

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, MFD_TEXTURE_SIZE - 1, MFD_TEXTURE_SIZE - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_2d_dvo_mfd (TRUE, TRUE);

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			set_pilots_full_screen_params (FALSE);

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_TSD:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, MFD_TEXTURE_SIZE - 1, MFD_TEXTURE_SIZE - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_tactical_situation_display_mfd ();

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_ASE:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, MFD_TEXTURE_SIZE - 1, MFD_TEXTURE_SIZE - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_aircraft_survivability_equipment_display_mfd ();

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_WEAPON:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, MFD_TEXTURE_SIZE - 1, MFD_TEXTURE_SIZE - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_weapon_display_mfd (MFD_LOCATION_DONT_CARE, TRUE);

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_SYSTEM:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, MFD_TEXTURE_SIZE - 1, MFD_TEXTURE_SIZE - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_system_display_mfd ();

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_ENGINE:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, MFD_TEXTURE_SIZE - 1, MFD_TEXTURE_SIZE - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_engine_display_mfd ();

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

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

			set_d3d_flat_shaded_textured_renderstate (get_system_texture_ptr (texture_index));

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
//
// EVENTS & MFD SWITCHING
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static mfd_modes get_mfd_mode_for_eo_sensor (void)
{
	mfd_modes
		mfd_mode;

	if (eo_sensor == TARGET_ACQUISITION_SYSTEM_FLIR)
	{
		mfd_mode = MFD_MODE_FLIR;
	}
	else if (eo_sensor == TARGET_ACQUISITION_SYSTEM_DTV)
	{
		mfd_mode = MFD_MODE_DTV;
	}
	else if (eo_sensor == TARGET_ACQUISITION_SYSTEM_DVO)
	{
		mfd_mode = MFD_MODE_DVO;
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

void select_next_apache_tsd_ase_range (void)
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

void select_previous_apache_tsd_ase_range (void)
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

void select_next_apache_tsd_declutter_level (void)
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

void select_previous_apache_tsd_declutter_level (void)
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

static mfd_modes get_next_mfd_mode (mfd_modes mfd_mode)
{
	mfd_modes
		next_mfd_mode;

	switch (mfd_mode)
	{
		case MFD_MODE_OFF:
		{
			next_mfd_mode = MFD_MODE_TSD;

			break;
		}
		case MFD_MODE_DAMAGED:
		{
			next_mfd_mode = MFD_MODE_DAMAGED;

			break;
		}
		case MFD_MODE_GROUND_RADAR:
		{
			next_mfd_mode = MFD_MODE_AIR_RADAR;

			break;
		}
		case MFD_MODE_AIR_RADAR:
		{
			next_mfd_mode = get_mfd_mode_for_eo_sensor ();

			break;
		}
		case MFD_MODE_FLIR:
		{
			next_mfd_mode = MFD_MODE_TSD;

			break;
		}
		case MFD_MODE_DTV:
		{
			next_mfd_mode = MFD_MODE_TSD;

			break;
		}
		case MFD_MODE_DVO:
		{
			next_mfd_mode = MFD_MODE_TSD;

			break;
		}
		case MFD_MODE_TSD:
		{
			next_mfd_mode = MFD_MODE_ASE;

			break;
		}
		case MFD_MODE_ASE:
		{
			next_mfd_mode = MFD_MODE_WEAPON;

			break;
		}
		case MFD_MODE_WEAPON:
		{
			next_mfd_mode = MFD_MODE_SYSTEM;

			break;
		}
		case MFD_MODE_SYSTEM:
		{
			next_mfd_mode = MFD_MODE_ENGINE;

			break;
		}
		case MFD_MODE_ENGINE:
		{
			next_mfd_mode = MFD_MODE_GROUND_RADAR;

			break;
		}
		default:
		{
			debug_fatal ("Invalid mfd mode = %d", mfd_mode);

			break;
		}
	}

	return (next_mfd_mode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static mfd_modes get_previous_mfd_mode (mfd_modes mfd_mode)
{
	mfd_modes
		previous_mfd_mode;

	switch (mfd_mode)
	{
		case MFD_MODE_OFF:
		{
			previous_mfd_mode = MFD_MODE_TSD;

			break;
		}
		case MFD_MODE_DAMAGED:
		{
			previous_mfd_mode = MFD_MODE_DAMAGED;

			break;
		}
		case MFD_MODE_GROUND_RADAR:
		{
			previous_mfd_mode = MFD_MODE_ENGINE;

			break;
		}
		case MFD_MODE_AIR_RADAR:
		{
			previous_mfd_mode = MFD_MODE_GROUND_RADAR;

			break;
		}
		case MFD_MODE_FLIR:
		{
			previous_mfd_mode = MFD_MODE_AIR_RADAR;

			break;
		}
		case MFD_MODE_DTV:
		{
			previous_mfd_mode = MFD_MODE_AIR_RADAR;

			break;
		}
		case MFD_MODE_DVO:
		{
			previous_mfd_mode = MFD_MODE_AIR_RADAR;

			break;
		}
		case MFD_MODE_TSD:
		{
			previous_mfd_mode = get_mfd_mode_for_eo_sensor ();

			break;
		}
		case MFD_MODE_ASE:
		{
			previous_mfd_mode = MFD_MODE_TSD;

			break;
		}
		case MFD_MODE_WEAPON:
		{
			previous_mfd_mode = MFD_MODE_ASE;

			break;
		}
		case MFD_MODE_SYSTEM:
		{
			previous_mfd_mode = MFD_MODE_WEAPON;

			break;
		}
		case MFD_MODE_ENGINE:
		{
			previous_mfd_mode = MFD_MODE_SYSTEM;

			break;
		}
		default:
		{
			debug_fatal ("Invalid mfd mode = %d", mfd_mode);

			break;
		}
	}

	return (previous_mfd_mode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_next_apache_lhs_mfd (void)
{
	mfd_modes
		next_mfd_mode;

	next_mfd_mode = get_next_mfd_mode (lhs_mfd_mode);

	if (next_mfd_mode != MFD_MODE_DAMAGED)
	{
		if (next_mfd_mode == rhs_mfd_mode)
		{
			next_mfd_mode = get_next_mfd_mode (next_mfd_mode);
		}

		ASSERT (next_mfd_mode != rhs_mfd_mode);
	}

	select_apache_mfd_mode (next_mfd_mode, MFD_LOCATION_LHS);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_previous_apache_lhs_mfd (void)
{
	mfd_modes
		previous_mfd_mode;

	previous_mfd_mode = get_previous_mfd_mode (lhs_mfd_mode);

	if (previous_mfd_mode != MFD_MODE_DAMAGED)
	{
		if (previous_mfd_mode == rhs_mfd_mode)
		{
			previous_mfd_mode = get_previous_mfd_mode (previous_mfd_mode);
		}

		ASSERT (previous_mfd_mode != rhs_mfd_mode);
	}

	select_apache_mfd_mode (previous_mfd_mode, MFD_LOCATION_LHS);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_next_apache_rhs_mfd (void)
{
	mfd_modes
		next_mfd_mode;

	next_mfd_mode = get_next_mfd_mode (rhs_mfd_mode);

	if (next_mfd_mode != MFD_MODE_DAMAGED)
	{
		if (next_mfd_mode == lhs_mfd_mode)
		{
			next_mfd_mode = get_next_mfd_mode (next_mfd_mode);
		}

		ASSERT (next_mfd_mode != lhs_mfd_mode);
	}

	select_apache_mfd_mode (next_mfd_mode, MFD_LOCATION_RHS);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_previous_apache_rhs_mfd (void)
{
	mfd_modes
		previous_mfd_mode;

	previous_mfd_mode = get_previous_mfd_mode (rhs_mfd_mode);

	if (previous_mfd_mode != MFD_MODE_DAMAGED)
	{
		if (previous_mfd_mode == lhs_mfd_mode)
		{
			previous_mfd_mode = get_previous_mfd_mode (previous_mfd_mode);
		}

		ASSERT (previous_mfd_mode != lhs_mfd_mode);
	}

	select_apache_mfd_mode (previous_mfd_mode, MFD_LOCATION_RHS);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_apache_ground_radar_mfd (void)
{
	if (get_view_mode () == VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_LHS_MFD)
	{
		if (!apache_damage.lh_mfd)
		{
			select_apache_mfd_mode (MFD_MODE_GROUND_RADAR, MFD_LOCATION_LHS);

			return;
		}
	}

	if (get_view_mode () == VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_RHS_MFD)
	{
		if (!apache_damage.rh_mfd)
		{
			select_apache_mfd_mode (MFD_MODE_GROUND_RADAR, MFD_LOCATION_RHS);

			return;
		}
	}

	if (lhs_mfd_mode == MFD_MODE_GROUND_RADAR)
	{
		return;
	}

	if (rhs_mfd_mode == MFD_MODE_GROUND_RADAR)
	{
		return;
	}

	if (lhs_mfd_mode == MFD_MODE_AIR_RADAR)
	{
		select_apache_mfd_mode (MFD_MODE_GROUND_RADAR, MFD_LOCATION_LHS);

		return;
	}

	if (rhs_mfd_mode == MFD_MODE_AIR_RADAR)
	{
		select_apache_mfd_mode (MFD_MODE_GROUND_RADAR, MFD_LOCATION_RHS);

		return;
	}

	if ((lhs_mfd_mode == MFD_MODE_OFF) && (!apache_damage.lh_mfd))
	{
		select_apache_mfd_mode (MFD_MODE_GROUND_RADAR, MFD_LOCATION_LHS);

		return;
	}

	if ((rhs_mfd_mode == MFD_MODE_OFF) && (!apache_damage.rh_mfd))
	{
		select_apache_mfd_mode (MFD_MODE_GROUND_RADAR, MFD_LOCATION_RHS);

		return;
	}

	if (!apache_damage.lh_mfd)
	{
		select_apache_mfd_mode (MFD_MODE_GROUND_RADAR, MFD_LOCATION_LHS);

		return;
	}

	if (!apache_damage.rh_mfd)
	{
		select_apache_mfd_mode (MFD_MODE_GROUND_RADAR, MFD_LOCATION_RHS);

		return;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_apache_air_radar_mfd (void)
{
	if (get_view_mode () == VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_LHS_MFD)
	{
		if (!apache_damage.lh_mfd)
		{
			select_apache_mfd_mode (MFD_MODE_AIR_RADAR, MFD_LOCATION_LHS);

			return;
		}
	}

	if (get_view_mode () == VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_RHS_MFD)
	{
		if (!apache_damage.rh_mfd)
		{
			select_apache_mfd_mode (MFD_MODE_AIR_RADAR, MFD_LOCATION_RHS);

			return;
		}
	}

	if (lhs_mfd_mode == MFD_MODE_AIR_RADAR)
	{
		return;
	}

	if (rhs_mfd_mode == MFD_MODE_AIR_RADAR)
	{
		return;
	}

	if (lhs_mfd_mode == MFD_MODE_GROUND_RADAR)
	{
		select_apache_mfd_mode (MFD_MODE_AIR_RADAR, MFD_LOCATION_LHS);

		return;
	}

	if (rhs_mfd_mode == MFD_MODE_GROUND_RADAR)
	{
		select_apache_mfd_mode (MFD_MODE_AIR_RADAR, MFD_LOCATION_RHS);

		return;
	}

	if ((lhs_mfd_mode == MFD_MODE_OFF) && (!apache_damage.lh_mfd))
	{
		select_apache_mfd_mode (MFD_MODE_AIR_RADAR, MFD_LOCATION_LHS);

		return;
	}

	if ((rhs_mfd_mode == MFD_MODE_OFF) && (!apache_damage.rh_mfd))
	{
		select_apache_mfd_mode (MFD_MODE_AIR_RADAR, MFD_LOCATION_RHS);

		return;
	}

	if (!apache_damage.lh_mfd)
	{
		select_apache_mfd_mode (MFD_MODE_AIR_RADAR, MFD_LOCATION_LHS);

		return;
	}

	if (!apache_damage.rh_mfd)
	{
		select_apache_mfd_mode (MFD_MODE_AIR_RADAR, MFD_LOCATION_RHS);

		return;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_apache_tads_mfd (void)
{
	if (get_view_mode () == VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_LHS_MFD)
	{
		if (!apache_damage.lh_mfd)
		{
			select_apache_mfd_mode (get_mfd_mode_for_eo_sensor (), MFD_LOCATION_LHS);

			return;
		}
	}

	if (get_view_mode () == VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_RHS_MFD)
	{
		if (!apache_damage.rh_mfd)
		{
			select_apache_mfd_mode (get_mfd_mode_for_eo_sensor (), MFD_LOCATION_RHS);

			return;
		}
	}

	if ((lhs_mfd_mode == MFD_MODE_FLIR) || (lhs_mfd_mode == MFD_MODE_DTV) || (lhs_mfd_mode == MFD_MODE_DVO))
	{
		select_apache_mfd_mode (get_mfd_mode_for_eo_sensor (), MFD_LOCATION_LHS);

		return;
	}

	if ((rhs_mfd_mode == MFD_MODE_FLIR) || (rhs_mfd_mode == MFD_MODE_DTV) || (rhs_mfd_mode == MFD_MODE_DVO))
	{
		select_apache_mfd_mode (get_mfd_mode_for_eo_sensor (), MFD_LOCATION_RHS);

		return;
	}

	if ((lhs_mfd_mode == MFD_MODE_OFF) && (!apache_damage.lh_mfd))
	{
		select_apache_mfd_mode (get_mfd_mode_for_eo_sensor (), MFD_LOCATION_LHS);

		return;
	}

	if ((rhs_mfd_mode == MFD_MODE_OFF) && (!apache_damage.rh_mfd))
	{
		select_apache_mfd_mode (get_mfd_mode_for_eo_sensor (), MFD_LOCATION_RHS);

		return;
	}

	if (!apache_damage.lh_mfd)
	{
		select_apache_mfd_mode (get_mfd_mode_for_eo_sensor (), MFD_LOCATION_LHS);

		return;
	}

	if (!apache_damage.rh_mfd)
	{
		select_apache_mfd_mode (get_mfd_mode_for_eo_sensor (), MFD_LOCATION_RHS);

		return;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void toggle_apache_ase_auto_page (void)
{
	set_global_ase_auto_page (get_global_ase_auto_page () ^ 1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void auto_page_apache_ase_mfd (void)
{
	if (!get_global_ase_auto_page ())
	{
		return;
	}

	////////////////////////////////////////
	//
	// select viewed large MFD
	//
	////////////////////////////////////////

	if (get_view_mode () == VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_LHS_MFD)
	{
		if (!apache_damage.lh_mfd)
		{
			select_apache_mfd_mode (MFD_MODE_ASE, MFD_LOCATION_LHS);

			return;
		}
	}

	if (get_view_mode () == VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_RHS_MFD)
	{
		if (!apache_damage.rh_mfd)
		{
			select_apache_mfd_mode (MFD_MODE_ASE, MFD_LOCATION_RHS);

			return;
		}
	}

	////////////////////////////////////////
	//
	// check if already displayed
	//
	////////////////////////////////////////

	if (lhs_mfd_mode == MFD_MODE_ASE)
	{
		return;
	}

	if (rhs_mfd_mode == MFD_MODE_ASE)
	{
		return;
	}

	////////////////////////////////////////
	//
	// select undamaged off MFD
	//
	////////////////////////////////////////

	if ((lhs_mfd_mode == MFD_MODE_OFF) && (!apache_damage.lh_mfd))
	{
		select_apache_mfd_mode (MFD_MODE_ASE, MFD_LOCATION_LHS);

		return;
	}

	if ((rhs_mfd_mode == MFD_MODE_OFF) && (!apache_damage.rh_mfd))
	{
		select_apache_mfd_mode (MFD_MODE_ASE, MFD_LOCATION_RHS);

		return;
	}

	////////////////////////////////////////
	//
	// select unfocused MFD
	//
	////////////////////////////////////////

	if ((!get_apache_mfd_has_focus (MFD_LOCATION_LHS)) && (!apache_damage.lh_mfd))
	{
		select_apache_mfd_mode (MFD_MODE_ASE, MFD_LOCATION_LHS);

		return;
	}

	if ((!get_apache_mfd_has_focus (MFD_LOCATION_RHS)) && (!apache_damage.rh_mfd))
	{
		select_apache_mfd_mode (MFD_MODE_ASE, MFD_LOCATION_RHS);

		return;
	}

	////////////////////////////////////////
	//
	// select undamaged MFD
	//
	////////////////////////////////////////

	if (!apache_damage.lh_mfd)
	{
		select_apache_mfd_mode (MFD_MODE_ASE, MFD_LOCATION_LHS);

		return;
	}

	if (!apache_damage.rh_mfd)
	{
		select_apache_mfd_mode (MFD_MODE_ASE, MFD_LOCATION_RHS);

		return;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void toggle_apache_lhs_mfd_on_off (void)
{
	if (lhs_mfd_mode != MFD_MODE_OFF)
	{
		select_apache_mfd_mode (MFD_MODE_OFF, MFD_LOCATION_LHS);
	}
	else
	{
		select_next_apache_lhs_mfd ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void toggle_apache_rhs_mfd_on_off (void)
{
	if (rhs_mfd_mode != MFD_MODE_OFF)
	{
		select_apache_mfd_mode (MFD_MODE_OFF, MFD_LOCATION_RHS);
	}
	else
	{
		select_next_apache_rhs_mfd ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_apache_mfd_has_focus (mfd_locations mfd_location)
{
	int
		result;

	mfd_modes
		mfd_mode;

	if (mfd_location == MFD_LOCATION_LHS)
	{
		mfd_mode = lhs_mfd_mode;
	}
	else
	{
		mfd_mode = rhs_mfd_mode;
	}

	switch (target_acquisition_system)
	{
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_GROUND_RADAR:
		////////////////////////////////////////
		{
			result = (mfd_mode == MFD_MODE_GROUND_RADAR);

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_AIR_RADAR:
		////////////////////////////////////////
		{
			result = (mfd_mode == MFD_MODE_AIR_RADAR);

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_FLIR:
		////////////////////////////////////////
		{
			result = (mfd_mode == MFD_MODE_FLIR);

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_DTV:
		////////////////////////////////////////
		{
			result = (mfd_mode == MFD_MODE_DTV);

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_DVO:
		////////////////////////////////////////
		{
			result = (mfd_mode == MFD_MODE_DVO);

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

int get_apache_tads_display_visible (void)
{
	return
	(
		(lhs_mfd_mode == MFD_MODE_FLIR) ||
		(lhs_mfd_mode == MFD_MODE_DTV) ||
		(lhs_mfd_mode == MFD_MODE_DVO) ||
		(rhs_mfd_mode == MFD_MODE_FLIR) ||
		(rhs_mfd_mode == MFD_MODE_DTV) ||
		(rhs_mfd_mode == MFD_MODE_DVO)
	);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
