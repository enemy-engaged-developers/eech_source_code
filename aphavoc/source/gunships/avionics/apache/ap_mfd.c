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
#define MFD_COLOUR_RED			(mfd_colours[14])
#define MFD_COLOUR_CYAN			(mfd_colours[15])
#define MFD_COLOUR_DARK_BLUE	(mfd_colours[16])
#define MFD_COLOUR_DARK_RED		(mfd_colours[17])
#define MFD_CLEAR_COLOUR		(mfd_colours[18])

static rgb_colour
	text_display_colours[2];

#define TEXT_COLOUR1					(text_display_colours[0])
#define TEXT_BACKGROUND_COLOUR	(text_display_colours[1])

static void (*draw_line_func)(float, float, float, float, const rgb_colour) = NULL;

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
//#define MFD_VIEWPORT_LARGE_SIZE		(331)
#define MFD_VIEWPORT_LARGE_SIZE		(256)

#define MFD_TEXTURE_SMALL_SIZE			(128)
#define MFD_TEXTURE_LARGE_SIZE			(256)
//#define MFD_TEXTURE_SIZE			(128)

//#define MFD_VIEWPORT_TEXTURE_X_ORG	(MFD_TEXTURE_SIZE / 2)
//#define MFD_VIEWPORT_TEXTURE_Y_ORG	(MFD_TEXTURE_SIZE / 2)

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
	draw_large_mfd,
	mfd_texture_size,
	mfd_viewport_texture_x_org,
	mfd_viewport_texture_y_org;

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
	*rhs_overlaid_mfd_texture_screen,
	*eo_3d_texture_screen;

static rgb_colour
	clear_mfd_colour,
	clear_green_mfd_colour;

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

enum TSD_UNDERLAY_LEVELS
{
	TSD_UNDERLAY_NONE,
	TSD_UNDERLAY_MAP,
	TSD_UNDERLAY_TADS
};

typedef enum TSD_UNDERLAY_LEVELS tsd_underlay_levels;

static tsd_underlay_levels
	tsd_underlay;

static short
	tsd_tads_underlay_active = FALSE;

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

static char
	large_tsd_pointer_cross[] =
	{
		19,
		19,
		-9,
		-9,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
		0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,
		0,0,0,1,0,0,0,1,1,1,1,1,0,0,0,1,0,0,0,
		0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,
		0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,
		0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,
		0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
		0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,
		0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,
		0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,
		0,0,0,1,0,0,0,1,1,1,1,1,0,0,0,1,0,0,0,
		0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,
		0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	};

static char
	large_tsd_pointer_cross_mask[] =
	{
		19,
		19,
		-9,
		-9,
		0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
		1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
		0,1,0,1,0,0,0,1,1,1,1,1,0,0,0,1,0,1,0,
		0,0,1,0,1,1,1,0,0,0,0,0,1,1,1,0,1,0,0,
		0,0,0,1,0,0,0,1,1,1,1,1,0,0,0,1,0,0,0,
		0,0,0,1,0,1,1,0,0,0,0,0,1,1,0,1,0,0,0,
		0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,
		0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,0,
		0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,0,
		0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,0,
		0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,0,
		0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,0,
		0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,
		0,0,0,1,0,1,1,0,0,0,0,0,1,1,0,1,0,0,0,
		0,0,0,1,0,0,0,1,1,1,1,1,0,0,0,1,0,0,0,
		0,0,1,0,1,1,1,0,0,0,0,0,1,1,1,0,1,0,0,
		0,1,0,1,0,0,0,1,1,1,1,1,0,0,0,1,0,1,0,
		1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
		0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
	};

static vec3d get_relative_vec_from_tsd_coordinate (float x, float y, float scale)
{
	float x_origin, y_origin;
	float rel_x, rel_y;
	vec3d position;

	// match ground radar origin
	x_origin = 0.0;
	if (draw_large_mfd)
		y_origin = -0.65;
	else
		y_origin = -0.70;

	rel_x = x - x_origin;
	rel_y = y - y_origin;

	position.x = rel_x / scale;
	position.y = 0.0;
	position.z = rel_y / scale;  // yes, y coordinates in MFD translates to Z-coordinates in 3D

	return position;
}

static void get_tsd_coordinate_from_relative_vec (vec3d* vec, float* x, float* y, float scale)
{
	float x_origin, y_origin;

	// match ground radar origin
	x_origin = 0.0;
	if (draw_large_mfd)
		y_origin = -0.65;
	else
		y_origin = -0.70;

	*x = vec->x * scale;
	*y = vec->z * scale;

	*x += x_origin;
	*y += y_origin;
}

#define RADIUS	(ROOT2 - 0.05)
static void draw_pfz(int pfz_number, int is_nfz, matrix3x3 rotation_matrix, float scale)
{
	vec3d relative_coord;
	float x1, x2, x3, x4, y1, y2, y3, y4, centre_x, centre_y;
	char s[20];
	rgb_colour pfz_colour;
	pfz* current_zone;
	
	if (is_nfz)
	{
		current_zone = get_nfz(pfz_number);
		pfz_colour = MFD_COLOUR_BLUE;
	}
	else
	{
		current_zone = get_pfz(pfz_number);

		if (pfz_number == current_pfz)
			pfz_colour = MFD_COLOUR_RED;
		else
			pfz_colour = MFD_COLOUR_DARK_RED;
	}

	// get coordinates and draw box
	world_coordinate_to_relative_position(&current_zone->corner1, &relative_coord, rotation_matrix);
	get_tsd_coordinate_from_relative_vec (&relative_coord, &x1, &y1, scale);

	world_coordinate_to_relative_position(&current_zone->corner2, &relative_coord, rotation_matrix);
	get_tsd_coordinate_from_relative_vec (&relative_coord, &x2, &y2, scale);

	world_coordinate_to_relative_position(&current_zone->corner3, &relative_coord, rotation_matrix);
	get_tsd_coordinate_from_relative_vec (&relative_coord, &x3, &y3, scale);

	world_coordinate_to_relative_position(&current_zone->corner4, &relative_coord, rotation_matrix);
	get_tsd_coordinate_from_relative_vec (&relative_coord, &x4, &y4, scale);

	draw_2d_line(x1, y1, x2, y2, pfz_colour);
	draw_2d_line(x2, y2, x3, y3, pfz_colour);
	draw_2d_line(x3, y3, x4, y4, pfz_colour);
	draw_2d_line(x4, y4, x1, y1, pfz_colour);

	// PFZ laber
	set_mono_font_colour(pfz_colour);

	if (draw_large_mfd)
		set_mono_font_type (MONO_FONT_TYPE_6X10);
	else
		set_mono_font_type (MONO_FONT_TYPE_3X6);

	if (is_nfz)
		sprintf(s, "NF%d", pfz_number+1);
	else
		sprintf(s, "PF%d", pfz_number+1);

	centre_x = (x1 + x3) * 0.5;
	centre_y = (y1 + y3) * 0.5;
	
	set_2d_mono_font_position (centre_x, centre_y);
	set_mono_font_rel_position (-0.5 * get_mono_font_string_width(s), -4.0);
	
	print_mono_font_string (s);
}

static void draw_pfzs(void)
{
	int i;
	matrix3x3 rotation_matrix;
	float scale = RADIUS / tsd_ase_range;

	get_3d_transformation_matrix(rotation_matrix, -current_flight_dynamics->heading.value, 0.0, 0.0);

	for (i=0; i < next_free_nfz; i++)
		draw_pfz(i, TRUE, rotation_matrix, scale);

	for (i=0; i < next_free_pfz; i++)
		if (i != current_pfz)  // draw current PFZ last
			draw_pfz(i, FALSE, rotation_matrix, scale);
	
	if (current_pfz != NO_PFZ)
		draw_pfz(current_pfz, FALSE, rotation_matrix, scale);
}


void create_apache_pfz(int is_nfz)
{
	matrix3x3 rotation_matrix;
	vec3d relative_position;
	vec3d position1, position2, position3, position4;
	float scale = RADIUS / tsd_ase_range;

	// don't create too small pfzs
	if (fabs(pointer_position_x - clicked_position_x) < 0.05
		|| fabs(pointer_position_y - clicked_position_y) < 0.05)
		return;

	get_3d_transformation_matrix(rotation_matrix, current_flight_dynamics->heading.value, 0.0, 0.0);

	relative_position = get_relative_vec_from_tsd_coordinate(pointer_position_x, pointer_position_y, scale);
	relative_position_to_world_coordinate(&relative_position, &position1, rotation_matrix);

	relative_position = get_relative_vec_from_tsd_coordinate(pointer_position_x, clicked_position_y, scale);
	relative_position_to_world_coordinate(&relative_position, &position2, rotation_matrix);

	relative_position = get_relative_vec_from_tsd_coordinate(clicked_position_x, clicked_position_y, scale);
	relative_position_to_world_coordinate(&relative_position, &position3, rotation_matrix);

	relative_position = get_relative_vec_from_tsd_coordinate(clicked_position_x, pointer_position_y, scale);
	relative_position_to_world_coordinate(&relative_position, &position4, rotation_matrix);

	if (is_nfz)
		add_nfz(&position1, &position2, &position3, &position4);
	else
	{
		add_pfz(&position1, &position2, &position3, &position4);
		current_pfz = next_free_pfz - 1;
	}
}
#undef RADIUS


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

////////////////////////////////////////
//
// WEAPONS
//
////////////////////////////////////////

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
	stinger_missile_data[] =
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
	inverted_stinger_missile_data[] =
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
	
static void draw_box(float x1_c, float y1_c, float x2_c, float y2_c, int filled, rgb_colour colour);
static void draw_bordered_box(float x1_c, float y1_c, float x2_c, float y2_c, rgb_colour fill_colour, rgb_colour border_colour);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int pointer_active (void)
{
	if (lhs_mfd_mode != MFD_MODE_TSD && rhs_mfd_mode != MFD_MODE_TSD)
		return FALSE;

	if ((command_line_mouse_look == MOUSELOOK_ON
		 || command_line_mouse_look == MOUSELOOK_INTERNAL)
		&& !query_TIR_active())
	{
		return FALSE;
	}
	
	return TRUE;	
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_apache_mfd (void)
{
	select_apache_mfd_mode (MFD_MODE_ENGINE, MFD_LOCATION_LHS);

	select_apache_mfd_mode (MFD_MODE_TSD, MFD_LOCATION_RHS);

	tsd_ase_range = TSD_ASE_RANGE_5000;

	tsd_declutter_level = TSD_DECLUTTER_LEVEL_ALL;
	tsd_underlay = TSD_UNDERLAY_NONE;
	
	current_pfz = NO_PFZ;
	next_free_pfz = 0;
	next_free_nfz = 0;

	tsd_threat_line_flash_timer = TSD_THREAT_LINE_FLASH_RATE;
	tsd_draw_threat_line_status = 0;

	ase_threat_line_flash_timer = ASE_THREAT_LINE_FLASH_RATE;
	ase_draw_threat_line_status = 0;

	mfd_env = create_2d_environment ();


	if (!command_line_high_res_mfd)
	{
		switch (get_view_mode ())
		{
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY:
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY:
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY:
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY:
			draw_large_mfd = TRUE;
			break;
		default:
			draw_large_mfd = FALSE;
			break;
		}
	}
	else
		draw_large_mfd = TRUE;
		
	if (draw_large_mfd)
	{
		mfd_viewport_size = MFD_VIEWPORT_LARGE_SIZE;
		mfd_texture_size = MFD_TEXTURE_LARGE_SIZE;
		eo_3d_texture_screen = large_eo_3d_texture_screen;
		draw_line_func = draw_2d_half_thick_line;
	}
	else
	{
		mfd_viewport_size = MFD_VIEWPORT_SMALL_SIZE;
		mfd_texture_size = MFD_TEXTURE_SMALL_SIZE;
		eo_3d_texture_screen = small_eo_3d_texture_screen;
		draw_line_func = draw_2d_line;
	}
	mfd_viewport_texture_x_org = mfd_texture_size / 2;
	mfd_viewport_texture_y_org = mfd_texture_size / 2;

	lhs_mfd_texture_screen = create_system_texture_screen (mfd_texture_size, mfd_texture_size, TEXTURE_INDEX_AVCKPT_DISPLAY_LHS_MFD, TEXTURE_TYPE_SINGLEALPHA);
	rhs_mfd_texture_screen = create_system_texture_screen (mfd_texture_size, mfd_texture_size, TEXTURE_INDEX_AVCKPT_DISPLAY_RHS_MFD, TEXTURE_TYPE_SINGLEALPHA);

	lhs_overlaid_mfd_texture_screen = create_system_texture_screen (mfd_texture_size, mfd_texture_size, LHS_OVERLAID_MFD_TEXTURE_INDEX, TEXTURE_TYPE_SINGLEALPHA);
	rhs_overlaid_mfd_texture_screen = create_system_texture_screen (mfd_texture_size, mfd_texture_size, RHS_OVERLAID_MFD_TEXTURE_INDEX, TEXTURE_TYPE_SINGLEALPHA);

	set_rgb_colour (MFD_COLOUR1,   0, 255,   0, 255);
	set_rgb_colour (MFD_COLOUR2,   0, 200,   0, 255);
	set_rgb_colour (MFD_COLOUR3,   0, 176,   0, 255);
	set_rgb_colour (MFD_COLOUR4,   0, 151,   0, 255);
	set_rgb_colour (MFD_COLOUR5,   0, 149,   0, 255);
	set_rgb_colour (MFD_COLOUR6,  40,  68,  56, 255);

	set_rgb_colour (clear_mfd_colour, 0, 255, 0, 0);
	if (get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE) == DAY_SEGMENT_TYPE_NIGHT)
	{
		set_rgb_colour (clear_green_mfd_colour, 6, 6, 1, 255);
	}
	else
	{
		set_rgb_colour (clear_green_mfd_colour, 30, 58, 44, 255);
	}
	
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

	if (command_line_colour_mfd)
	{
		set_rgb_colour (MFD_COLOUR_BLUE,          60, 160, 255,   255);
		set_rgb_colour (MFD_COLOUR_DARK_BLUE,	0, 0,  96, 255);  //dark blue
		set_rgb_colour (MFD_COLOUR_YELLOW,       230, 230,  40,   255);
		set_rgb_colour (MFD_COLOUR_RED,          210, 90,  60,   255);	
		set_rgb_colour (MFD_COLOUR_DARK_RED,	148, 32,   0, 255);//dark red
		set_rgb_colour (MFD_COLOUR_CYAN,          60, 255, 230,   255);	
	}
	else
	{
		MFD_COLOUR_BLUE = MFD_COLOUR1;
		MFD_COLOUR_DARK_BLUE = MFD_COLOUR5;
		MFD_COLOUR_YELLOW = MFD_COLOUR1;
		MFD_COLOUR_RED = MFD_COLOUR1;
		MFD_COLOUR_DARK_RED = MFD_COLOUR5;
		MFD_COLOUR_CYAN = MFD_COLOUR1;
	}

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

	// don't let both a MFD show TADS, and have TADS as TSD underlay
	if ((mfd_mode == MFD_MODE_DVO
		 || mfd_mode == MFD_MODE_DTV
		 || mfd_mode == MFD_MODE_FLIR)
		&& tsd_underlay == TSD_UNDERLAY_TADS)
	{
		tsd_underlay = TSD_UNDERLAY_NONE;
	}

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
	heading_width_ratio = 0.5;
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
		draw_2d_line (-0.3000, -0.7750,  0.3000, -0.7750, MFD_COLOUR1);
		draw_2d_line (-0.3000, -1.0000,  0.3000, -1.0000, MFD_COLOUR1);
		draw_2d_line (-0.3000, -0.7750, -0.3000, -1.0000, MFD_COLOUR1);
		draw_2d_line ( 0.3000, -0.7750,  0.3000, -1.0000, MFD_COLOUR1);

		draw_2d_line ( 0.0000, -0.7750,  0.0000, -0.7950, MFD_COLOUR1);
		draw_2d_line (-0.2250, -0.7750, -0.2250, -0.7950, MFD_COLOUR1);
		draw_2d_line ( 0.2250, -0.7750,  0.2250, -0.7950, MFD_COLOUR1);

		draw_2d_line ( 0.0000, -0.9800,  0.0000, -1.0000, MFD_COLOUR1);
		draw_2d_line (-0.2250, -0.9800, -0.2250, -1.0000, MFD_COLOUR1);
		draw_2d_line ( 0.2250, -0.9800,  0.2250, -1.0000, MFD_COLOUR1);

		draw_2d_line (-0.3000, -0.8500, -0.2800, -0.8500, MFD_COLOUR1);
		draw_2d_line ( 0.3000, -0.8500,  0.2800, -0.8500, MFD_COLOUR1);

		x = eo_azimuth / eo_max_azimuth * 0.3;
		y = (eo_elevation / eo_min_elevation * -0.15) - 0.85;

		draw_2d_line (x - 0.0400, y - 0.0300, x + 0.0400, y - 0.0300, MFD_COLOUR1);
		draw_2d_line (x - 0.0400, y + 0.0300, x + 0.0400, y + 0.0300, MFD_COLOUR1);
		draw_2d_line (x - 0.0400, y - 0.0300, x - 0.0400, y + 0.0300, MFD_COLOUR1);
		draw_2d_line (x + 0.0400, y - 0.0300, x + 0.0400, y + 0.0300, MFD_COLOUR1);
	}
	else
	{
		draw_2d_line (-0.2000, -0.8250,  0.2000, -0.8250, MFD_COLOUR1);
		draw_2d_line (-0.2000, -0.9750,  0.2000, -0.9750, MFD_COLOUR1);
		draw_2d_line (-0.2000, -0.8250, -0.2000, -0.9750, MFD_COLOUR1);
		draw_2d_line ( 0.2000, -0.8250,  0.2000, -0.9750, MFD_COLOUR1);

		draw_2d_line ( 0.0000, -0.8250,  0.0000, -0.8475, MFD_COLOUR1);
		draw_2d_line (-0.1500, -0.8250, -0.1500, -0.8475, MFD_COLOUR1);
		draw_2d_line ( 0.1500, -0.8250,  0.1500, -0.8475, MFD_COLOUR1);

		draw_2d_line ( 0.0000, -0.9525,  0.0000, -0.9750, MFD_COLOUR1);
		draw_2d_line (-0.1500, -0.9525, -0.1500, -0.9750, MFD_COLOUR1);
		draw_2d_line ( 0.1500, -0.9525,  0.1500, -0.9750, MFD_COLOUR1);

		draw_2d_line (-0.2000, -0.8750, -0.1775, -0.8750, MFD_COLOUR1);
		draw_2d_line ( 0.2000, -0.8750,  0.1775, -0.8750, MFD_COLOUR1);

		x = eo_azimuth / eo_max_azimuth * 0.2;
		y = (eo_elevation / eo_min_elevation * -0.1) - 0.875;

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

	set_2d_mono_font_position (0.9, 1.0);

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

		set_2d_mono_font_position (-0.9, 1.0);

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
		target_symbol_colour,
		target_symbol_background_colour;
		
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

	// figure out correct colours to use
//VJ 030423 TSD render mod
	if (display_on_tsd)
	{
		//VJ 030511 TSD render mod, treat enemy colours as cheat
		if (command_line_tsd_enemy_colours)
		{
			if (source_side == get_local_entity_int_value (target, INT_TYPE_SIDE))
			{
				target_symbol_colour = MFD_COLOUR_BLUE;
				target_symbol_background_colour = MFD_COLOUR_DARK_BLUE;
			}
			else
			{
				target_symbol_colour = MFD_COLOUR_RED;
				target_symbol_background_colour = MFD_COLOUR_DARK_RED;
			}
		}
		else
		{
				target_symbol_colour = MFD_COLOUR_RED;
				target_symbol_background_colour = MFD_COLOUR_DARK_RED;
		}
	}		
	else
	{
		target_symbol_colour = MFD_COLOUR1;
		target_symbol_background_colour = MFD_COLOUR4;
	}

	// draw marker
	if (draw_large_mfd)
	{
		if (get_local_entity_int_value (target, INT_TYPE_GUNSHIP_RADAR_LOS_CLEAR))
		{
			draw_2d_mono_sprite (large_display_target_symbols_los_mask[target_symbol_type], dx, dy, target_symbol_background_colour);
			draw_2d_mono_sprite (large_display_target_symbols_los[target_symbol_type], dx, dy, target_symbol_colour);
		}
		else
		{
			draw_2d_mono_sprite (large_display_target_symbols_no_los_mask[target_symbol_type], dx, dy, target_symbol_background_colour);
			draw_2d_mono_sprite (large_display_target_symbols_no_los[target_symbol_type], dx, dy, target_symbol_colour);
		}

		if (selected_target)
		{
			draw_2d_mono_sprite (large_display_target_symbol_selected_target_mask, dx, dy, target_symbol_background_colour);
			draw_2d_mono_sprite (large_display_target_symbol_selected_target, dx, dy, target_symbol_colour);
		}
	}
	else
	{
		if (get_local_entity_int_value (target, INT_TYPE_GUNSHIP_RADAR_LOS_CLEAR))
		{
			draw_2d_mono_sprite (small_display_target_symbols_los_mask[target_symbol_type], dx, dy, target_symbol_background_colour);
			draw_2d_mono_sprite (small_display_target_symbols_los[target_symbol_type], dx, dy, target_symbol_colour);
		}
		else
		{
			draw_2d_mono_sprite (small_display_target_symbols_no_los_mask[target_symbol_type], dx, dy, target_symbol_background_colour);
			draw_2d_mono_sprite (small_display_target_symbols_no_los[target_symbol_type], dx, dy, target_symbol_colour);
		}

		if (selected_target)
		{
			draw_2d_mono_sprite (small_display_target_symbol_selected_target_mask, dx, dy, target_symbol_background_colour);
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
		scale;

	entity
		*source,
		*target;

	vec3d
		*source_position;

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

	set_2d_mono_font_position (-0.9, 1.0);

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

// Jabberwock 031107 Designated targets

	target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

	if (target && get_local_entity_parent (target, LIST_TYPE_DESIGNATED_TARGET))
	{
		int width = get_mono_font_string_width ("MARKED");
		set_2d_mono_font_position (1.0, -0.7);
		set_mono_font_rel_position (-width, 0);
		print_mono_font_string ("MARKED");		
	}
// Jabberwock 031107 ends
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

	draw_high_action_display(target, FALSE);

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
		fov = 18.0;

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
			if (system == TARGET_ACQUISITION_SYSTEM_FLIR)
				fov = 3.1;
			else  // DTV
				fov = 0.9;

			break;
		}
		case EO_FOV_MEDIUM:
		{
			if (system == TARGET_ACQUISITION_SYSTEM_FLIR)
				fov = 10.1;
			else  // DTV or DVO
				fov = 4.0;

			break;
		}
		case EO_FOV_WIDE:
		{
			if (system == TARGET_ACQUISITION_SYSTEM_FLIR)
				fov = 50.0;
			else  // DVO
				fov = 18.0;

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
			set_main_3d_params (tint, light_level, noise_level, mfd_viewport_x_min - 1.5, mfd_viewport_y_min - 1.5, MFD_VIEWPORT_LARGE_SIZE, MFD_VIEWPORT_LARGE_SIZE, rad(fov), rad(fov));
		}
		else
		{
			set_main_3d_params (tint, light_level, noise_level, mfd_viewport_x_min - 1.5, mfd_viewport_y_min - 1.5, MFD_VIEWPORT_LARGE_SIZE, MFD_VIEWPORT_LARGE_SIZE, rad(fov), rad(fov));
		}
	}
	else
	{
		if (location == MFD_LOCATION_LHS)
		{
			set_main_3d_params (tint, light_level, noise_level, mfd_viewport_x_min, mfd_viewport_y_min, 128.0, 128.0, rad(fov), rad(fov));
		}
		else
		{
			set_main_3d_params (tint, light_level, noise_level, mfd_viewport_x_min, mfd_viewport_y_min, 128.0, 128.0, rad(fov), rad(fov));
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
		fov;

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

	ASSERT (eo_3d_texture_screen);

	ASSERT (d3d_can_render_to_texture);

	switch (eo->field_of_view)
	{
		case EO_FOV_NARROW:
		{
			if (system == TARGET_ACQUISITION_SYSTEM_FLIR)
				fov = 1.6;
			else  // DTV
				fov = 0.9;

			break;
		}
		case EO_FOV_MEDIUM:
		{
			if (system == TARGET_ACQUISITION_SYSTEM_FLIR)
				fov = 3.6;
			else  // DTV or DVO
				fov = 4.0;

			break;
		}
		case EO_FOV_WIDE:
		{
			if (system == TARGET_ACQUISITION_SYSTEM_FLIR)
				fov = 10.1;
			else  // DVO
				fov = 18.0;

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

	set_3d_render_target (eo_3d_texture_screen);

	set_active_screen (eo_3d_texture_screen);

	if (command_line_green_mfd)
	{
		tint = DISPLAY_3D_TINT_GREEN;
	}
	else
	{
		tint = DISPLAY_3D_TINT_GREY;
	}

	set_main_3d_params (tint, light_level, noise_level, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_size, mfd_viewport_size, rad (fov), rad(fov));

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

static void draw_high_action_display (entity* target, int fill_boxes)
{
	const char* s;
	char buffer[200];

	float target_range;
	int x_adjust, width;

	entity_sub_types weapon_sub_type;

	if (target)
	{
		vec3d* target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);
		vec3d* source_position = get_local_entity_vec3d_ptr (get_gunship_entity(), VEC3D_TYPE_POSITION);
		
		target_range = get_3d_range (source_position, target_position);
	}
	else
		target_range = 0.0;


	if (draw_large_mfd)
		set_mono_font_type (MONO_FONT_TYPE_5X9);
	else
		set_mono_font_type (MONO_FONT_TYPE_3X6);

	if (fill_boxes)
	{
		rgb_colour bg_colour;

		set_rgb_colour (bg_colour, 0, 40, 0, 255);

		draw_bordered_box(-0.98, -1.0, -0.35, -0.8, bg_colour, MFD_COLOUR1);
		draw_bordered_box(0.98, -1.0, 0.35, -0.8, bg_colour, MFD_COLOUR1);
	}
	else
	{
		draw_box(-0.98, -1.0, -0.35, -0.8, FALSE, MFD_COLOUR1);
		draw_box(0.98, -1.0, 0.35, -0.8, FALSE, MFD_COLOUR1);
	}

// Jabberwock 031107 Designated targets
	target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);
	
	if (target && get_local_entity_parent (target, LIST_TYPE_DESIGNATED_TARGET))
	{
//		width = get_mono_font_string_width ("MARKED");
		
		set_2d_mono_font_position (-0.6, 0.0);
		set_mono_font_rel_position (0, 0);
		print_mono_font_string ("MARKED");		
	}
// Jabberwock 031107 ends

	//
	// target name
	//

	s = get_target_display_name (target, buffer, draw_large_mfd);

	if (s)
	{
		width = get_mono_font_string_width (s);
		set_2d_mono_font_position (0.0, -0.7);
		set_mono_font_rel_position (-width * 0.5, 0);
		print_mono_font_string (s);
	}

	// lower left box:
	// rang finder    range
	// targeting status

	// range finding system
	switch (target_acquisition_system)
	{
	case TARGET_ACQUISITION_SYSTEM_GROUND_RADAR:
	case TARGET_ACQUISITION_SYSTEM_AIR_RADAR:
		s = "FCR";
		sprintf(buffer, "R%.1f", target_range * 0.001);
		break;
	case TARGET_ACQUISITION_SYSTEM_FLIR:
	case TARGET_ACQUISITION_SYSTEM_DTV:
	case TARGET_ACQUISITION_SYSTEM_DVO:
		s = "TADS";
		sprintf(buffer, "L%04.0f", target_range);
		break;
	case TARGET_ACQUISITION_SYSTEM_IHADSS:
	case TARGET_ACQUISITION_SYSTEM_OFF:
	default:
		s = "NONE";
		sprintf(buffer, "A%.1", target_range * 0.001);
		break;
	}

	set_2d_mono_font_position (-0.95, -0.83);
	x_adjust = 0; //get_mono_font_string_width (s) * -0.5;
	set_mono_font_rel_position (x_adjust, 0);
	print_mono_font_string (s);

	set_2d_mono_font_position (-0.40, -0.83);
	x_adjust = -get_mono_font_string_width (buffer); // * 0.5;
	set_mono_font_rel_position (x_adjust, 0);
	print_mono_font_string (buffer);

	// targeting status
	
	switch (weapon_lock_type)
	{
		case WEAPON_LOCK_NO_ACQUIRE:
			s = "NO ACQUIRE";
			break;
		case WEAPON_LOCK_NO_WEAPON:
			s = "NO WEAPON";
			break;
		case WEAPON_LOCK_NO_TARGET:
			s = "NO TARGET";
			break;
		case WEAPON_LOCK_INVALID_TARGET:
			s = "INVALID TGT";
			break;
		case WEAPON_LOCK_SEEKER_LIMIT:
			s = "SKR LIMIT";
			break;
		case WEAPON_LOCK_NO_LOS:
			s = "NO LOS";
			break;
		case WEAPON_LOCK_MIN_RANGE:
			s = "MIN RNG";
			break;
		case WEAPON_LOCK_MAX_RANGE:
			s = "MAX RNG";
			break;
		case WEAPON_LOCK_NO_BORESIGHT:
		case WEAPON_LOCK_VALID:
			s = "VALID LOCK";
			break;
		default:
			debug_fatal ("Invalid weapon lock type = %d", weapon_lock_type);
			break;
	}

	set_2d_mono_font_position (-0.95, -0.83);
	x_adjust = 0; //get_mono_font_string_width (s) * -0.5;
	set_mono_font_rel_position (x_adjust, 10);
	print_mono_font_string (s);

	// lower right box:
	// weapon type
	// launch mode
	weapon_sub_type = get_local_entity_int_value (get_gunship_entity (), INT_TYPE_SELECTED_WEAPON);
	switch (weapon_sub_type)
	{
		case ENTITY_SUB_TYPE_WEAPON_M230_30MM_ROUND:
			s = "CANNON";
			break;
		case ENTITY_SUB_TYPE_WEAPON_AGM114L_LONGBOW_HELLFIRE:
		case ENTITY_SUB_TYPE_WEAPON_AGM114K_HELLFIRE_II:
			s = "MSL";
			break;
		case ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255:
		case ENTITY_SUB_TYPE_WEAPON_HYDRA70_M261:
			s = "RKT";
			break;
		case ENTITY_SUB_TYPE_WEAPON_AIM92_STINGER:
			s = "ATA";
			break;
		case ENTITY_SUB_TYPE_WEAPON_NO_WEAPON:
		default:
			s = "NONE";
			break;
	}

	set_2d_mono_font_position (0.37, -0.83);
	x_adjust = 0; //get_mono_font_string_width (s) * -0.5;
	set_mono_font_rel_position (x_adjust, 0);
	print_mono_font_string (s);

	// launch mode
	if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_LOCK_ON_AFTER_LAUNCH))
		s = "LOAL";
	else
		s = "LOBL";

	set_2d_mono_font_position (0.37, -0.83);
	x_adjust = 0; //get_mono_font_string_width (s) * -0.5;
	set_mono_font_rel_position (x_adjust, 9);
	print_mono_font_string (s);



	/*

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
	*/

	////////////////////////////////////////
	//
	// draw field of regard and view boxes
	//
	////////////////////////////////////////

	draw_field_of_regard_and_view_boxes ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_2d_eo_display (eo_params *eo, target_acquisition_systems system, int damaged, int valid_3d, int scaled_3d)
{
	const char
		*s;

	float
		width,
		y_adjust,
		i,
		j,
		x,
		y;

	entity
		*source,
		*target;

	vec3d
		target_point;

	viewpoint
		tmp;

	object_3d_visibility
		visibility;

	ASSERT (eo);


	source = get_gunship_entity ();
	target = get_local_entity_parent (source, LIST_TYPE_TARGET);

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

	set_2d_mono_font_position (-0.85, 1.0);

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
			s = "NAR";
			break;
		case EO_FOV_MEDIUM:
			s = "MED";
			break;
		case EO_FOV_WIDE:
			s = "WIDE";
			break;
		default:
			s = "XXX";
			break;
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

	set_2d_mono_font_position (0.85, 1.0);

	set_mono_font_rel_position (-width, y_adjust);

	print_mono_font_string (s);

	//
	// locked
	//

	if (eo_target_locked)
	{
		width = get_mono_font_string_width ("LOCKED");
		set_2d_mono_font_position (0.0, -0.6);
		set_mono_font_rel_position (-width * 0.5, 0);
		print_mono_font_string ("LOCKED");
	}


	draw_high_action_display (target, TRUE);

	////////////////////////////////////////
	//
	// draw heading scale
	//
	////////////////////////////////////////

	draw_heading_scale (get_heading_from_attitude_matrix (eo_vp.attitude));

	////////////////////////////////////////
	//
	// line graphics
	//
	////////////////////////////////////////

	//
	// datum
	//

//	if (draw_large_mfd)
	{
		draw_2d_line (-0.200, 0.0, -0.050, 0.0, MFD_COLOUR1);
		draw_2d_line (0.050, 0.0, 0.20, 0.0, MFD_COLOUR1);
		draw_2d_line (0.0, -0.200, 0.0, -0.050, MFD_COLOUR1);
		draw_2d_line (0.0, 0.050, 0.0, 0.20, MFD_COLOUR1);
	}
/*	else
	{
		draw_2d_line (-0.075, 0.0, -0.025, 0.0, MFD_COLOUR1);
		draw_2d_line (0.035, 0.0, 0.09, 0.0, MFD_COLOUR1);
		draw_2d_line (0.0, -0.075, 0.0, -0.025, MFD_COLOUR1);
		draw_2d_line (0.0, 0.035, 0.0, 0.09, MFD_COLOUR1);
	}*/

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


	rgb_colour tsd_basic_colour = MFD_COLOUR2;

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

	if (tsd_underlay == TSD_UNDERLAY_MAP)
	{
		if (tsd_render_mode != TSD_RENDER_CONTOUR_MODE)
		{
			tsd_basic_colour = MFD_COLOUR_DARK_BLUE;
			draw_tsd_terrain_map (mfd_env, -y_origin, tsd_ase_range, scale, source_position, source_heading);
		}

//VJ 030423 TSD render mod, added mfd_env
		draw_tsd_contour_map (mfd_env, -y_origin, tsd_ase_range, scale, source_position, source_heading, draw_large_mfd);
	}

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

			draw_radar_arc (ground_radar.scan_arc_size, radius, tsd_basic_colour);

			set_2d_window_rotation (mfd_env, -(ground_radar.scan_datum - (ground_radar.scan_arc_size * 0.5)));

			draw_2d_line (0.0, 0.0, 0.0, radius, tsd_basic_colour);

			set_2d_window_rotation (mfd_env, -(ground_radar.scan_datum + (ground_radar.scan_arc_size * 0.5)));

			draw_2d_line (0.0, 0.0, 0.0, radius, tsd_basic_colour);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_2d_window_rotation (mfd_env, 0.0);
		}
		else if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_AIR_RADAR)
		{
			set_2d_viewport_origin (mfd_env, u, v);

			radius = air_radar.scan_range * scale;

			if (air_radar.scan_arc_size == APACHE_RADAR_SCAN_ARC_SIZE_360)
			{
				draw_2d_circle (0.0, 0.0, radius, tsd_basic_colour);
			}
			else
			{
				set_2d_window_rotation (mfd_env, -air_radar.scan_datum);

				draw_radar_arc (air_radar.scan_arc_size, radius, tsd_basic_colour);

				draw_2d_line (0.0, 0.0, 0.0, radius, tsd_basic_colour);

				set_2d_window_rotation (mfd_env, -(air_radar.scan_datum - (air_radar.scan_arc_size * 0.5)));

				draw_2d_line (0.0, 0.0, 0.0, radius, tsd_basic_colour);

				set_2d_window_rotation (mfd_env, -(air_radar.scan_datum + (air_radar.scan_arc_size * 0.5)));

				draw_2d_line (0.0, 0.0, 0.0, radius, tsd_basic_colour);

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

		rgb_colour waypoint_colour = MFD_COLOUR_YELLOW;
		
		if (tsd_underlay == TSD_UNDERLAY_MAP)
			waypoint_colour = tsd_basic_colour;		

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
						draw_2d_half_thick_line (wp1_rel_position.x, wp1_rel_position.z, wp2_rel_position.x, wp2_rel_position.z, waypoint_colour);  // 2
					else
						draw_2d_half_thick_line (wp1_rel_position.x, wp1_rel_position.z, wp2_rel_position.x, wp2_rel_position.z, waypoint_colour);  // 5
				}
				else
				{
					if (tsd_render_mode == TSD_RENDER_CONTOUR_MODE)
						draw_2d_line (wp1_rel_position.x, wp1_rel_position.z, wp2_rel_position.x, wp2_rel_position.z, waypoint_colour);
					else
						draw_2d_line (wp1_rel_position.x, wp1_rel_position.z, wp2_rel_position.x, wp2_rel_position.z, waypoint_colour);
				}
				wp1 = wp2;

				wp1_rel_position = wp2_rel_position;

				wp2 = get_local_entity_child_succ (wp1, LIST_TYPE_WAYPOINT);
			}

			//
			// waypoint markers
			//

			if (tsd_underlay == TSD_UNDERLAY_MAP)
				set_mono_font_colour (MFD_COLOUR_BLUE);
			else
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
						draw_2d_mono_sprite (large_tsd_waypoint_marker, wp1_rel_position.x, wp1_rel_position.z, waypoint_colour); // 2
					else
						draw_2d_mono_sprite (large_tsd_waypoint_marker, wp1_rel_position.x, wp1_rel_position.z, waypoint_colour);  // 5
	
					set_2d_mono_font_position (wp1_rel_position.x, wp1_rel_position.z);

					set_mono_font_rel_position (-2.0, -4.0);
				}
				else
				{
//VJ 030423 TSD render mod
					if (tsd_render_mode == TSD_RENDER_CONTOUR_MODE)
						draw_2d_mono_sprite (small_tsd_waypoint_marker, wp1_rel_position.x, wp1_rel_position.z, waypoint_colour);
					else
						draw_2d_mono_sprite (small_tsd_waypoint_marker, wp1_rel_position.x, wp1_rel_position.z, waypoint_colour);

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
			draw_pfzs();
			
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
									draw_2d_circle (dx, dy, air_scan_range, MFD_COLOUR2);
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
		draw_2d_mono_sprite (large_tsd_ase_aircraft_datum_mask, x_origin, y_origin, MFD_COLOUR_DARK_BLUE);  // 6

		draw_2d_mono_sprite (large_tsd_ase_aircraft_datum, x_origin, y_origin, MFD_COLOUR_BLUE);  // 1
	}
	else
	{
		draw_2d_mono_sprite (small_tsd_ase_aircraft_datum_mask, x_origin, y_origin, MFD_COLOUR_DARK_BLUE);

		draw_2d_mono_sprite (small_tsd_ase_aircraft_datum, x_origin, y_origin, MFD_COLOUR_BLUE);
	}

	////////////////////////////////////////
	//
	// text
	//
	////////////////////////////////////////

	set_mono_font_colour (tsd_basic_colour);

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
				if (current_pfz != NO_PFZ)
				{
					sprintf(buffer, "FCR/PF%d", current_pfz+1);
					s = buffer;	
				}
				else
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
		if (tsd_underlay == TSD_UNDERLAY_MAP)
			display_waypoint_information (tsd_basic_colour);
		else
			display_waypoint_information (MFD_COLOUR4);
	}
	
	if (tsd_declutter_level != TSD_DECLUTTER_LEVEL_NAVIGATION)
	{
		// pointer
		draw_2d_mono_sprite (large_tsd_pointer_cross_mask, pointer_position_x, pointer_position_y, MFD_COLOUR4);
		draw_2d_mono_sprite (large_tsd_pointer_cross, pointer_position_x, pointer_position_y, MFD_COLOUR1);
		

		if (is_holding_left_button())   // is creating a pfz
			draw_box(clicked_position_x, clicked_position_y, pointer_position_x, pointer_position_y, FALSE, MFD_COLOUR_RED);
		if (is_holding_right_button())  // is creating a nfz
			draw_box(clicked_position_x, clicked_position_y, pointer_position_x, pointer_position_y, FALSE, MFD_COLOUR_BLUE);
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

	if (draw_large_mfd)
		return;

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

static void draw_bordered_box(float x1_c, float y1_c, float x2_c, float y2_c, rgb_colour fill_colour, rgb_colour border_colour)
{
	int x1, x2, y1, y2;
	int inner_x1, inner_x2, inner_y1, inner_y2;
	
	get_2d_int_screen_coordinates (min(x1_c, x2_c), max(y1_c, y2_c), &x1, &y1);
	get_2d_int_screen_coordinates (max(x1_c, x2_c), min(y1_c, y2_c), &x2, &y2);
	
	inner_x1 = x1+1;
	inner_x2 = x2-1;
	inner_y1 = y1+1;
	inner_y2 = y2-1;

	if (inner_x1 < inner_x2 && inner_y1 < inner_y2)
		set_block(inner_x1 * 2, inner_y1, inner_x2 * 2, inner_y2, fill_colour);

	draw_line(x1, y1, x2, y1, border_colour);
	draw_line(x1, y1, x1, y2, border_colour);
	draw_line(x1, y2, x2, y2, border_colour);
	draw_line(x2, y1, x2, y2, border_colour);
}

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_large_weapon_display_mfd (mfd_locations location)
{
	float x1, x2, x3, x4, y1, y2, y3;
	float forward_wing, rear_wing, wing_tip_left, wing_tip_right;
	char s[80], *s_ptr;
	float x_adjust;
	int number, damaged, selected_weapon, pylon;
	entity_sub_types weapon_sub_type;


	ASSERT(draw_large_mfd);

	selected_weapon = get_local_entity_int_value(get_gunship_entity (), INT_TYPE_SELECTED_WEAPON);

	set_mono_font_type (MONO_FONT_TYPE_7X12);

	// draw helicopter outline
	// nose
	
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


	// cannon
	if (get_local_entity_weapon_hardpoint_info (get_gunship_entity (),
		APACHE_CHAIN_GUN_TURRET, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, 
		&weapon_sub_type, &number, &damaged))
	{
		int selected = (weapon_sub_type == selected_weapon) && !damaged;

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

	s_ptr = "CHAFF";
		
	x_adjust = get_mono_font_string_width (s_ptr) * -0.5;
	set_mono_font_rel_position (x_adjust, 0.0);
	print_mono_font_string (s_ptr);

	set_2d_mono_font_position (0.0, -0.3);

	if (get_local_entity_weapon_hardpoint_info (get_gunship_entity (),
		APACHE_CHAFF_DISPENSER, ENTITY_SUB_TYPE_WEAPON_CHAFF,
		&weapon_sub_type, &number, &damaged))
	{
		if (!damaged)
			sprintf (s, "%2d", number);
		else
			sprintf (s, "XX");
	
		x_adjust = get_mono_font_string_width (s) * -0.5;
		set_mono_font_rel_position (x_adjust, 0.0);
		print_mono_font_string (s);
	}

	// Flares
	set_2d_mono_font_position (0.0, -0.45);

	s_ptr = "FLARE";
		
	x_adjust = get_mono_font_string_width (s_ptr) * -0.5;
	set_mono_font_rel_position (x_adjust, 0.0);
	print_mono_font_string (s_ptr);

	set_2d_mono_font_position (0.0, -0.55);
	
	if (get_local_entity_weapon_hardpoint_info (get_gunship_entity (),
		APACHE_FLARE_DISPENSER, ENTITY_SUB_TYPE_WEAPON_FLARE,
		&weapon_sub_type, &number, &damaged))
	{
		if (!damaged)
			sprintf (s, "%2d", number);
		else
			sprintf (s, "XX");
	
		x_adjust = get_mono_font_string_width (s) * -0.5;
		set_mono_font_rel_position (x_adjust, 0.0);
		print_mono_font_string (s);
	}

	// auto CM
	set_2d_mono_font_position (0.0, -0.7);

	if (get_global_auto_counter_measures ())
		s_ptr = "AUTO";
	else
		s_ptr = "MAN";
		
	x_adjust = get_mono_font_string_width (s_ptr) * -0.5;
	set_mono_font_rel_position (x_adjust, 0.0);
	print_mono_font_string (s_ptr);
	
	// master arm box

	set_2d_mono_font_position (0.0, 0.89);

	if (selected_weapon != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
	{
		draw_box(-0.25, 0.7, 0.25, 1.0, TRUE, MFD_COLOUR1);

		set_mono_font_colour (MFD_CLEAR_COLOUR);
		s_ptr = "ARM";
		
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
		s_ptr = "SAFE";
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
	case TARGET_ACQUISITION_SYSTEM_GROUND_RADAR:
	case TARGET_ACQUISITION_SYSTEM_AIR_RADAR:
		s_ptr = "FCR";
		break;
	case TARGET_ACQUISITION_SYSTEM_FLIR:
	case TARGET_ACQUISITION_SYSTEM_DTV:
	case TARGET_ACQUISITION_SYSTEM_DVO:
		s_ptr = "TADS";
		break;
	case TARGET_ACQUISITION_SYSTEM_IHADSS:
		s_ptr = "IHADSS";
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

	switch (target_acquisition_system)
	{
	case TARGET_ACQUISITION_SYSTEM_GROUND_RADAR:
	case TARGET_ACQUISITION_SYSTEM_AIR_RADAR:
		s_ptr = "FCR";
		break;
	case TARGET_ACQUISITION_SYSTEM_FLIR:
	case TARGET_ACQUISITION_SYSTEM_DTV:
	case TARGET_ACQUISITION_SYSTEM_DVO:
	case TARGET_ACQUISITION_SYSTEM_IHADSS:
		s_ptr = "LRF";
		break;
	case TARGET_ACQUISITION_SYSTEM_OFF:
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
	s_ptr = "SALVO";

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
	for (pylon = APACHE_LHS_INNER_PYLON; pylon <= APACHE_RHS_WING_TIP_MOUNT; pylon++)
	{
		float pylon_x, pylon_y;
		
		pylon_y = -0.35;
		switch (pylon)
		{
		case APACHE_LHS_INNER_PYLON:
			pylon_x = -0.42;
			break;
		case APACHE_RHS_INNER_PYLON:
			pylon_x = 0.42;
			break;
		case APACHE_LHS_OUTER_PYLON:
			pylon_x = -0.74;
			break;
		case APACHE_RHS_OUTER_PYLON:
			pylon_x = 0.74;
			break;
		case APACHE_LHS_WING_TIP_MOUNT:
			pylon_x = -0.97;
			break;
		case APACHE_RHS_WING_TIP_MOUNT:
			pylon_x = 0.97;
			break;
		}
		
		if (get_local_entity_weapon_hardpoint_info (get_gunship_entity (),
			pylon, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON,
			&weapon_sub_type, &number, &damaged))
		{
			if ((weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_AGM114L_LONGBOW_HELLFIRE) || (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_AGM114K_HELLFIRE_II))
			{
				int i;
				float last_offset;  // is last missile on the left or right side of pylon
				
				if (pylon == APACHE_LHS_INNER_PYLON || pylon == APACHE_LHS_OUTER_PYLON)
					last_offset = 0.07;
				else
					last_offset = -0.07;
				
				for (i = 1; i <= number; i++)
				{
					float missile_x, missile_y;
					
					switch(i)
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
							ASSERT(!"more than 4 hellfires on Apache pylon");
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
			}
			else if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255 ||
					 weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_HYDRA70_M261)
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
	
				if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255)
					sprintf(s, "MP");
				else
					sprintf(s, "RC");
					
				x_adjust = get_mono_font_string_width (s) * -0.4;
				set_mono_font_rel_position (x_adjust, 0.0);
				print_mono_font_string (s);
				
				set_2d_mono_font_position (pylon_x, pylon_y - 0.1);
				sprintf(s, "%2d", number);
				x_adjust = get_mono_font_string_width (s) * -0.4;
				set_mono_font_rel_position (x_adjust, 0.0);
				print_mono_font_string (s);
			}
			else if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_AIM92_STINGER)
			{
				int selected = (weapon_sub_type == selected_weapon) && !damaged;
				int left_tip = pylon == APACHE_LHS_WING_TIP_MOUNT;
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
						draw_2d_mono_sprite(inverted_stinger_missile_data, pylon_x, pylon_y + 0.25, MFD_COLOUR1);
					else
						draw_2d_mono_sprite(stinger_missile_data, pylon_x, pylon_y + 0.25, MFD_COLOUR1);
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
						draw_2d_mono_sprite(inverted_stinger_missile_data, pylon_x, pylon_y - 0.05, MFD_COLOUR1);
					else
						draw_2d_mono_sprite(stinger_missile_data, pylon_x, pylon_y - 0.05, MFD_COLOUR1);
				}
			}
			
			// if damaged, draw X across pylon
			if (damaged)
			{
				float width, height = 0.7, x1, y1, x2, y2, y_offset = 0.0;
				
				if (pylon == APACHE_LHS_WING_TIP_MOUNT || pylon == APACHE_RHS_WING_TIP_MOUNT)
				{
					// stingers are narrower and drawn more forward than other pylons
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

	if (draw_large_mfd)
	{
		draw_large_weapon_display_mfd (location);

		return;
	}

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
		set_mono_font_type (MONO_FONT_TYPE_6X10);

		y_adjust = 2.0;
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

		draw_mono_sprite (large_engine_bar_marker, x1 + 5.0, y1 + 20.0, MFD_COLOUR1);
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

		draw_mono_sprite (large_engine_bar_marker, x1 - 7.0, y1 + 20.0, MFD_COLOUR1);
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

		draw_mono_sprite (large_engine_bar_marker, x1 - 7.0, y1 + 23.0, MFD_COLOUR1);
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

		draw_mono_sprite (large_engine_bar_marker, x1 + 5.0, y1 + 23.0, MFD_COLOUR1);
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

		draw_mono_sprite (large_engine_bar_marker, x1 - 7.0, y1 + 20.0, MFD_COLOUR1);
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

		draw_mono_sprite (large_engine_bar_marker, x1 - 7.0, y1 + 20.0, MFD_COLOUR1);
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

		draw_mono_sprite (large_engine_bar_marker, x1 - 7.0, y1 + 20.0, MFD_COLOUR1);
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

	set_2d_mono_font_position (-0.8, -0.75);

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
	sprintf (buffer, "%04d lbs", i);

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

		draw_mono_sprite (large_engine_bar_marker, x1 + 5.0, y1 + 20.0, MFD_COLOUR1);
		draw_mono_sprite (large_engine_bar_marker, x1 + 5.0, y1 + 65.0, MFD_COLOUR1);
	}
	else
	{
		draw_line (x1, y1, x1, y2, MFD_COLOUR1);
		draw_line (x1 + 2.0, y1, x1 + 2.0, y2, MFD_COLOUR1);
		draw_line (x1, y1, x1 + 2.0, y1, MFD_COLOUR1);
		draw_line (x1, y2, x1 + 2.0, y2, MFD_COLOUR1);

		draw_line (x1 + 1.0, y2, x1 + 1.0, y3, MFD_COLOUR1);

		draw_mono_sprite (small_engine_bar_marker, x1 + 3.0, y1 + 11.0, MFD_COLOUR1);
		draw_mono_sprite (small_engine_bar_marker, x1 + 3.0, y1 + 33.0, MFD_COLOUR1);
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

		draw_mono_sprite (large_engine_bar_marker, x1 - 7.0, y1 + 20.0, MFD_COLOUR1);
		draw_mono_sprite (large_engine_bar_marker, x1 - 7.0, y1 + 65.0, MFD_COLOUR1);

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

	set_2d_mono_font_position (-0.25, -0.75);

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

	set_2d_mono_font_position (0.5, -0.75);

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
#define PITCH_DATUM_Y	((float) -0.1)

//									P9 O (+ve)
//
//
//    P1    P2    P3    P4    P5    P6    P7
//     O-----O     O-----O     O-----O-----O
//     |
//     |
//     |
// P8  O					 	   P10 O (-ve)

#define PITCH_BAR_X1		((float) (+0.100) * pitch_bar_scale)
#define PITCH_BAR_Y1		((float) (+0.000) * pitch_bar_scale)
#define PITCH_BAR_X2		((float) (+0.180) * pitch_bar_scale)
#define PITCH_BAR_Y2		((float) (+0.000) * pitch_bar_scale)
#define PITCH_BAR_X3		((float) (+0.220) * pitch_bar_scale)
#define PITCH_BAR_Y3		((float) (+0.000) * pitch_bar_scale)
#define PITCH_BAR_X4		((float) (+0.300) * pitch_bar_scale)
#define PITCH_BAR_Y4		((float) (+0.000) * pitch_bar_scale)
#define PITCH_BAR_X5		((float) (+0.340) * pitch_bar_scale)
#define PITCH_BAR_Y5		((float) (+0.000) * pitch_bar_scale)
#define PITCH_BAR_X6		((float) (+0.420) * pitch_bar_scale)
#define PITCH_BAR_Y6		((float) (+0.000) * pitch_bar_scale)
#define PITCH_BAR_X7		((float) (+0.900) * pitch_bar_scale)
#define PITCH_BAR_Y7		((float) (+0.000) * pitch_bar_scale)
#define PITCH_BAR_X8		PITCH_BAR_X6 //((float) (+0.125) * pitch_bar_scale)
#define PITCH_BAR_Y8		((float) (-0.050) * pitch_bar_scale)
#define PITCH_BAR_X9		((float) (+0.540) * pitch_bar_scale)
#define PITCH_BAR_Y9		((float) (+0.000) * pitch_bar_scale)
#define PITCH_BAR_X10	((float) (+0.540) * pitch_bar_scale)
#define PITCH_BAR_Y10	((float) (-0.000) * pitch_bar_scale)

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
		size,
		roll_size,
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
		set_mono_font_type (MONO_FONT_TYPE_6X10);

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
	size = 0.6;
	pitch_bar_scale = 0.6;

	get_2d_float_screen_coordinates (PITCH_DATUM_X, PITCH_DATUM_Y, &u, &v);

	//
	// roll
	//

	roll = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_ROLL);

	set_2d_instance_position (mfd_env, PITCH_DATUM_X, PITCH_DATUM_Y);
	roll_size = size + 0.2;

	set_2d_instance_rotation (mfd_env, rad (0.0));
	draw_2d_line (0.0, roll_size, 0.0, roll_size - 0.05, MFD_COLOUR_CYAN);

	set_2d_instance_rotation (mfd_env, rad (5.0));
	draw_2d_line (0.0, roll_size, 0.0, roll_size - 0.025, MFD_COLOUR_CYAN);
	set_2d_instance_rotation (mfd_env, rad (-5.0));
	draw_2d_line (0.0, roll_size, 0.0, roll_size - 0.025, MFD_COLOUR_CYAN);

	set_2d_instance_rotation (mfd_env, rad (10.0));
	draw_2d_line (0.0, roll_size, 0.0, roll_size - 0.05, MFD_COLOUR_CYAN);
	set_2d_instance_rotation (mfd_env, rad (-10.0));
	draw_2d_line (0.0, roll_size, 0.0, roll_size - 0.05, MFD_COLOUR_CYAN);

	set_2d_instance_rotation (mfd_env, rad (15.0));
	draw_2d_line (0.0, roll_size, 0.0, roll_size - 0.025, MFD_COLOUR_CYAN);
	set_2d_instance_rotation (mfd_env, rad (-15.0));
	draw_2d_line (0.0, roll_size, 0.0, roll_size - 0.025, MFD_COLOUR_CYAN);

	set_2d_instance_rotation (mfd_env, rad (20.0));
	draw_2d_line (0.0, roll_size, 0.0, roll_size - 0.05, MFD_COLOUR_CYAN);
	set_2d_instance_rotation (mfd_env, rad (-20.0));
	draw_2d_line (0.0, roll_size, 0.0, roll_size - 0.05, MFD_COLOUR_CYAN);

	set_2d_instance_rotation (mfd_env, rad (25.0));
	draw_2d_line (0.0, roll_size, 0.0, roll_size - 0.025, MFD_COLOUR_CYAN);
	set_2d_instance_rotation (mfd_env, rad (-25.0));
	draw_2d_line (0.0, roll_size, 0.0, roll_size - 0.025, MFD_COLOUR_CYAN);

	set_2d_instance_rotation (mfd_env, rad (30.0));
	draw_2d_line (0.0, roll_size, 0.0, roll_size - 0.05, MFD_COLOUR_CYAN);
	set_2d_instance_rotation (mfd_env, rad (-30.0));
	draw_2d_line (0.0, roll_size, 0.0, roll_size - 0.05, MFD_COLOUR_CYAN);

	set_2d_instance_rotation (mfd_env, bound (roll, rad (-30.0), rad (30.0)));
	draw_2d_line (0.0, roll_size - 0.075, 0.0, roll_size, MFD_COLOUR_CYAN);


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
				set_mono_font_colour (MFD_COLOUR_RED);
				draw_2d_line (+PITCH_BAR_X7, +PITCH_BAR_Y7, -PITCH_BAR_X7, +PITCH_BAR_Y7, MFD_COLOUR_RED);

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

				set_mono_font_colour (MFD_COLOUR_BLUE);

				if (step_direction == -1)
				{
					draw_2d_line (+PITCH_BAR_X1, +PITCH_BAR_Y1, +PITCH_BAR_X6, +PITCH_BAR_Y6, MFD_COLOUR_BLUE);
					draw_2d_line (-PITCH_BAR_X1, +PITCH_BAR_Y1, -PITCH_BAR_X6, +PITCH_BAR_Y6, MFD_COLOUR_BLUE);

					draw_2d_line (+PITCH_BAR_X6, +PITCH_BAR_Y6, +PITCH_BAR_X8, +PITCH_BAR_Y8, MFD_COLOUR_BLUE);
					draw_2d_line (-PITCH_BAR_X6, +PITCH_BAR_Y6, -PITCH_BAR_X8, +PITCH_BAR_Y8, MFD_COLOUR_BLUE);
					
					draw_2d_line (-0.03, -y_10_deg_step * 0.5, 0.03, -y_10_deg_step * 0.5, MFD_COLOUR_BLUE);
				}
				else
				{
					draw_2d_line (-PITCH_BAR_X1, -PITCH_BAR_Y1, -PITCH_BAR_X6, -PITCH_BAR_Y6, MFD_COLOUR_BLUE);
					draw_2d_line (+PITCH_BAR_X1, -PITCH_BAR_Y1, +PITCH_BAR_X6, -PITCH_BAR_Y6, MFD_COLOUR_BLUE);

					draw_2d_line (-PITCH_BAR_X6, -PITCH_BAR_Y6, -PITCH_BAR_X8, -PITCH_BAR_Y8, MFD_COLOUR_BLUE);
					draw_2d_line (+PITCH_BAR_X6, -PITCH_BAR_Y6, +PITCH_BAR_X8, -PITCH_BAR_Y8, MFD_COLOUR_BLUE);

					draw_2d_line (-0.03, y_10_deg_step * 0.5, 0.03, y_10_deg_step * 0.5, MFD_COLOUR_BLUE);
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
				draw_2d_line (+PITCH_BAR_X1, +PITCH_BAR_Y1, +PITCH_BAR_X6, +PITCH_BAR_Y6, MFD_COLOUR_BLUE);
				draw_2d_line (-PITCH_BAR_X1, +PITCH_BAR_Y1, -PITCH_BAR_X6, +PITCH_BAR_Y6, MFD_COLOUR_BLUE);

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
				set_mono_font_colour (MFD_COLOUR_RED);
				if (step_direction == -1)
				{
					draw_2d_line (+PITCH_BAR_X1, +PITCH_BAR_Y1, +PITCH_BAR_X2, +PITCH_BAR_Y2, MFD_COLOUR_RED);
					draw_2d_line (-PITCH_BAR_X1, +PITCH_BAR_Y1, -PITCH_BAR_X2, +PITCH_BAR_Y2, MFD_COLOUR_RED);

					draw_2d_line (+PITCH_BAR_X3, +PITCH_BAR_Y3, +PITCH_BAR_X4, +PITCH_BAR_Y4, MFD_COLOUR_RED);
					draw_2d_line (-PITCH_BAR_X3, +PITCH_BAR_Y3, -PITCH_BAR_X4, +PITCH_BAR_Y4, MFD_COLOUR_RED);

					draw_2d_line (+PITCH_BAR_X5, +PITCH_BAR_Y5, +PITCH_BAR_X6, +PITCH_BAR_Y6, MFD_COLOUR_RED);
					draw_2d_line (-PITCH_BAR_X5, +PITCH_BAR_Y5, -PITCH_BAR_X6, +PITCH_BAR_Y6, MFD_COLOUR_RED);

					draw_2d_line (+PITCH_BAR_X6, +PITCH_BAR_Y6, +PITCH_BAR_X8, -PITCH_BAR_Y8, MFD_COLOUR_RED);
					draw_2d_line (-PITCH_BAR_X6, +PITCH_BAR_Y6, -PITCH_BAR_X8, -PITCH_BAR_Y8, MFD_COLOUR_RED);
				}
				else
				{
					draw_2d_line (-PITCH_BAR_X1, -PITCH_BAR_Y1, -PITCH_BAR_X2, -PITCH_BAR_Y2, MFD_COLOUR_RED);
					draw_2d_line (+PITCH_BAR_X1, -PITCH_BAR_Y1, +PITCH_BAR_X2, -PITCH_BAR_Y2, MFD_COLOUR_RED);

					draw_2d_line (-PITCH_BAR_X3, -PITCH_BAR_Y3, -PITCH_BAR_X4, -PITCH_BAR_Y4, MFD_COLOUR_RED);
					draw_2d_line (+PITCH_BAR_X3, -PITCH_BAR_Y3, +PITCH_BAR_X4, -PITCH_BAR_Y4, MFD_COLOUR_RED);

					draw_2d_line (-PITCH_BAR_X5, -PITCH_BAR_Y5, -PITCH_BAR_X6, -PITCH_BAR_Y6, MFD_COLOUR_RED);
					draw_2d_line (+PITCH_BAR_X5, -PITCH_BAR_Y5, +PITCH_BAR_X6, -PITCH_BAR_Y6, MFD_COLOUR_RED);

					draw_2d_line (-PITCH_BAR_X6, -PITCH_BAR_Y6, -PITCH_BAR_X8, +PITCH_BAR_Y8, MFD_COLOUR_RED);
					draw_2d_line (+PITCH_BAR_X6, -PITCH_BAR_Y6, +PITCH_BAR_X8, +PITCH_BAR_Y8, MFD_COLOUR_RED);
				}

				sprintf (s, "%d0", abs(int_pitch));

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
				draw_2d_line (+PITCH_BAR_X1, +PITCH_BAR_Y1, +PITCH_BAR_X2, +PITCH_BAR_Y2, MFD_COLOUR_RED);
				draw_2d_line (-PITCH_BAR_X1, +PITCH_BAR_Y1, -PITCH_BAR_X2, +PITCH_BAR_Y2, MFD_COLOUR_RED);

				draw_2d_line (+PITCH_BAR_X3, +PITCH_BAR_Y3, +PITCH_BAR_X4, +PITCH_BAR_Y4, MFD_COLOUR_RED);
				draw_2d_line (-PITCH_BAR_X3, +PITCH_BAR_Y3, -PITCH_BAR_X4, +PITCH_BAR_Y4, MFD_COLOUR_RED);

				draw_2d_line (+PITCH_BAR_X5, +PITCH_BAR_Y5, +PITCH_BAR_X6, +PITCH_BAR_Y6, MFD_COLOUR_RED);
				draw_2d_line (-PITCH_BAR_X5, +PITCH_BAR_Y5, -PITCH_BAR_X6, +PITCH_BAR_Y6, MFD_COLOUR_RED);

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

	set_mono_font_colour (MFD_COLOUR1);

	reset_2d_instance (mfd_env);

	// centre datum
	
	draw_2d_line (-0.25, 0.0, -0.08, 0.0, MFD_COLOUR_CYAN);
	draw_2d_line ( 0.25, 0.0,  0.08, 0.0, MFD_COLOUR_CYAN);

	draw_2d_line (-0.08, 0.0, -0.04, -0.08, MFD_COLOUR_CYAN);
	draw_2d_line ( 0.08, 0.0,  0.04, -0.08, MFD_COLOUR_CYAN);

	draw_2d_line (0.0, 0.0, -0.04, -0.08, MFD_COLOUR_CYAN);
	draw_2d_line (0.0, 0.0,  0.04, -0.08, MFD_COLOUR_CYAN);

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

//	if (draw_main_display)
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
/*	else
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
	}*/

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

//	if (draw_main_display)
	{
		set_2d_mono_font_position (1.0, 0.85);

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
/*	else
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
	} */

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

//	if (draw_main_display)
	{
		x_adjust = -0.05;
	}
/*	else
	{
		x_adjust = -0.85;
	}*/

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

	set_2d_mono_font_position (-1.0, 0.85);

//	if (draw_main_display)
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
/*	else
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
	}*/

	print_mono_font_string (s);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_waypoint_information (rgb_colour box_colour)
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

	draw_box(-0.98, -0.75, -0.35, -1.0, FALSE, box_colour);

	if (wp)
	{
		if (draw_large_mfd)
		{
			set_mono_font_type (MONO_FONT_TYPE_7X12);
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

		set_2d_mono_font_position (-0.95, -0.8);

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

		set_2d_mono_font_position (-0.95, -0.9);

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

	draw_heading_scale (get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_HEADING));

	display_true_airspeed ();

	display_altitude ();

	draw_rate_of_climb_scale ();

	display_engine_torque ();

	display_waypoint_information (MFD_COLOUR4);
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

	update_pointer_position();

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

	if (tsd_underlay == TSD_UNDERLAY_TADS
		&& (d3d_can_render_to_texture)
		&& !apache_damage.flir
		&& (lhs_mfd_mode == MFD_MODE_TSD
			|| rhs_mfd_mode == MFD_MODE_TSD))
		tsd_tads_underlay_active = TRUE;
	else
		tsd_tads_underlay_active = FALSE;

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

	switch (*mfd_mode)
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
		case MFD_MODE_DTV:
		case MFD_MODE_DVO:
		////////////////////////////////////////
		{
			if ((d3d_can_render_to_texture) && (!apache_damage.flir))
			{
				ASSERT (eo_3d_texture_screen);

				if (location == MFD_LOCATION_LHS)
					set_system_texture_screen (eo_3d_texture_screen, TEXTURE_INDEX_AVCKPT_DISPLAY_LHS_MFD);
				else
					set_system_texture_screen (eo_3d_texture_screen, TEXTURE_INDEX_AVCKPT_DISPLAY_RHS_MFD);

				if (*mfd_mode == MFD_MODE_FLIR)
					draw_3d_eo_display_on_texture (&apache_flir, TARGET_ACQUISITION_SYSTEM_FLIR);
				else if (*mfd_mode == MFD_MODE_DTV)
					draw_3d_eo_display_on_texture (&apache_dtv, TARGET_ACQUISITION_SYSTEM_DTV);
				else
					draw_3d_eo_display_on_texture (&apache_dvo, TARGET_ACQUISITION_SYSTEM_DVO);

				set_active_screen (eo_3d_texture_screen);

				if (lock_screen (eo_3d_texture_screen))
				{
					draw_layout_grid ();

					if (*mfd_mode == MFD_MODE_FLIR)
						draw_2d_flir_mfd (TRUE, FALSE);
					else if (*mfd_mode == MFD_MODE_DTV)
						draw_2d_dtv_mfd (TRUE, FALSE);
					else
						draw_2d_dvo_mfd (TRUE, FALSE);

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

					if (*mfd_mode == MFD_MODE_FLIR)
						draw_2d_flir_mfd (FALSE, FALSE);
					else if (*mfd_mode == MFD_MODE_DTV)
						draw_2d_dtv_mfd (FALSE, FALSE);
					else
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
			if (tsd_tads_underlay_active)
			{
				if (location == MFD_LOCATION_LHS)
					set_system_texture_screen (eo_3d_texture_screen, TEXTURE_INDEX_AVCKPT_DISPLAY_LHS_MFD);
				else
					set_system_texture_screen (eo_3d_texture_screen, TEXTURE_INDEX_AVCKPT_DISPLAY_RHS_MFD);

				if (eo_sensor == TARGET_ACQUISITION_SYSTEM_FLIR)
					draw_3d_eo_display_on_texture (&apache_flir, TARGET_ACQUISITION_SYSTEM_FLIR);
				else
					draw_3d_eo_display_on_texture (&apache_dtv, TARGET_ACQUISITION_SYSTEM_DTV);
			
				mfd_texture_screen = eo_3d_texture_screen;
			}
			
			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				if (!tsd_tads_underlay_active)
					set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_green_mfd_colour);

				draw_tactical_situation_display_mfd ();

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			if (tsd_tads_underlay_active)
				set_pilots_full_screen_params (FALSE);

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_ASE:
		////////////////////////////////////////
		{
			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

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
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

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
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

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
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_engine_display_mfd ();

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_FLIGHT:
		////////////////////////////////////////
		{
			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_rgb_colour (clear_mfd_colour, 0, 0, 0, 0);
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_green_mfd_colour);
				set_rgb_colour (clear_mfd_colour, 0, 255, 0, 0);

				draw_layout_grid ();

				draw_flight_display_mfd();

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

	i_scale_3d = mfd_texture_size / mfd_screen_size;
	j_scale_3d = mfd_texture_size / mfd_screen_size;

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
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

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
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

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
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

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
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

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
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

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
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

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
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

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
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

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
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

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
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

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
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

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

static mfd_modes get_mfd_mode_for_radar (void)
{
	if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_AIR_RADAR)
		return MFD_MODE_AIR_RADAR;

	return MFD_MODE_GROUND_RADAR;
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

void select_next_tsd_underlay_level(void)
{
	int tads_active = (lhs_mfd_mode == MFD_MODE_DVO
		 || lhs_mfd_mode == MFD_MODE_DTV
		 || lhs_mfd_mode == MFD_MODE_FLIR
		 || rhs_mfd_mode == MFD_MODE_DVO
		 || rhs_mfd_mode == MFD_MODE_DTV
		 || rhs_mfd_mode == MFD_MODE_FLIR);
	
	if (tsd_underlay == TSD_UNDERLAY_NONE)
		tsd_underlay = TSD_UNDERLAY_MAP;
	else if (tsd_underlay == TSD_UNDERLAY_MAP && !tads_active)
		tsd_underlay = TSD_UNDERLAY_TADS;
	else
		tsd_underlay = TSD_UNDERLAY_NONE;
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
		case MFD_MODE_AIR_RADAR:
		{
			if (tsd_tads_underlay_active)
				next_mfd_mode = MFD_MODE_TSD;
			else
				next_mfd_mode = get_mfd_mode_for_eo_sensor ();

			break;
		}
		case MFD_MODE_FLIR:
		case MFD_MODE_DTV:
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
			next_mfd_mode = MFD_MODE_FLIGHT;

			break;
		}
		case MFD_MODE_FLIGHT:
		{
			next_mfd_mode = get_mfd_mode_for_radar();

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
		previous_mfd_mode = MFD_MODE_OFF;

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
		case MFD_MODE_AIR_RADAR:
		{
			previous_mfd_mode = MFD_MODE_FLIGHT;

			break;
		}
		case MFD_MODE_FLIR:
		case MFD_MODE_DTV:
		case MFD_MODE_DVO:
		{
			previous_mfd_mode = get_mfd_mode_for_radar();

			break;
		}
		case MFD_MODE_TSD:
		{
			if (tsd_tads_underlay_active)
				previous_mfd_mode = get_mfd_mode_for_radar();
			else
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
		case MFD_MODE_FLIGHT:
		{
			previous_mfd_mode = MFD_MODE_ENGINE;

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

	if (lhs_mfd_mode == MFD_MODE_GROUND_RADAR || rhs_mfd_mode == MFD_MODE_GROUND_RADAR)
		return;

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

	if (lhs_mfd_mode == MFD_MODE_TSD || rhs_mfd_mode == MFD_MODE_TSD)
		return;

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

	if (tsd_tads_underlay_active)
		return;

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
