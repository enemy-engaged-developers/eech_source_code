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

view_modes
	view_mode;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	in_cockpit_flags[NUM_VIEW_MODES] =
	{
		TRUE,		// VIEW_MODE_COCKPIT_PANEL_UP40_LEFT90
		TRUE,		// VIEW_MODE_COCKPIT_PANEL_UP40_LEFT60
		TRUE,		// VIEW_MODE_COCKPIT_PANEL_UP40_LEFT30
		TRUE,		// VIEW_MODE_COCKPIT_PANEL_UP40_AHEAD
		TRUE,		// VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT30
		TRUE,		// VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT60
		TRUE,		// VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT90
		TRUE,		// VIEW_MODE_COCKPIT_PANEL_UP20_LEFT90
		TRUE,		// VIEW_MODE_COCKPIT_PANEL_UP20_LEFT60
		TRUE,		// VIEW_MODE_COCKPIT_PANEL_UP20_LEFT30
		TRUE,		// VIEW_MODE_COCKPIT_PANEL_UP20_AHEAD
		TRUE,		// VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT30
		TRUE,		// VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT60
		TRUE,		// VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT90
		TRUE,		// VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT90
		TRUE,		// VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT60
		TRUE,		// VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT30
		TRUE,		// VIEW_MODE_COCKPIT_PANEL_LEVEL_AHEAD
		TRUE,		// VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT30
		TRUE,		// VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT60
		TRUE,		// VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT90
		TRUE,		// VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT90
		TRUE,		// VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT60
		TRUE,		// VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT30
		TRUE,		// VIEW_MODE_COCKPIT_PANEL_DOWN20_AHEAD
		TRUE,		// VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT30
		TRUE,		// VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT60
		TRUE,		// VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT90
		TRUE,		// VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_LHS_MFD
		TRUE,		// VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_RHS_MFD
		TRUE,		// VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_TV
		TRUE,		// VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_HUD
		TRUE,		// VIEW_MODE_VIRTUAL_COCKPIT
		TRUE,		// VIEW_MODE_VIRTUAL_COCKPIT_PADLOCK
		TRUE,		// VIEW_MODE_VIRTUAL_COCKPIT_TRACK_TARGET
		TRUE,		// VIEW_MODE_VIRTUAL_COCKPIT_CREW
		TRUE,		// VIEW_MODE_VIRTUAL_COCKPIT_HUD
		TRUE,		// VIEW_MODE_VIRTUAL_COCKPIT_PERISCOPE
		TRUE,		// VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY
		TRUE,		// VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY
		TRUE,		// VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY
		TRUE,		// VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY
		FALSE,	// VIEW_MODE_EXTERNAL
		FALSE,	// VIEW_MODE_SAFE
	};

int
	in_cockpit;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	cockpit_panorama_row_values[NUM_VIEW_MODES] =
	{
		0,		// VIEW_MODE_COCKPIT_PANEL_UP40_LEFT90
		0,		// VIEW_MODE_COCKPIT_PANEL_UP40_LEFT60
		0,		// VIEW_MODE_COCKPIT_PANEL_UP40_LEFT30
		0,		// VIEW_MODE_COCKPIT_PANEL_UP40_AHEAD
		0,		// VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT30
		0,		// VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT60
		0,		// VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT90
		1,		// VIEW_MODE_COCKPIT_PANEL_UP20_LEFT90
		1,		// VIEW_MODE_COCKPIT_PANEL_UP20_LEFT60
		1,		// VIEW_MODE_COCKPIT_PANEL_UP20_LEFT30
		1,		// VIEW_MODE_COCKPIT_PANEL_UP20_AHEAD
		1,		// VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT30
		1,		// VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT60
		1,		// VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT90
		2,		// VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT90
		2,		// VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT60
		2,		// VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT30
		2,		// VIEW_MODE_COCKPIT_PANEL_LEVEL_AHEAD
		2,		// VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT30
		2,		// VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT60
		2,		// VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT90
		3,		// VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT90
		3,		// VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT60
		3,		// VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT30
		3,		// VIEW_MODE_COCKPIT_PANEL_DOWN20_AHEAD
		3,		// VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT30
		3,		// VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT60
		3,		// VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT90
		2,		// VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_LHS_MFD
		2,		// VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_RHS_MFD
		2,		// VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_TV
		2,		// VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_HUD
		2,		// VIEW_MODE_VIRTUAL_COCKPIT
		2,		// VIEW_MODE_VIRTUAL_COCKPIT_PADLOCK
		2,		// VIEW_MODE_VIRTUAL_COCKPIT_TRACK_TARGET
		2,		// VIEW_MODE_VIRTUAL_COCKPIT_CREW
		2,		// VIEW_MODE_VIRTUAL_COCKPIT_HUD
		2,		// VIEW_MODE_VIRTUAL_COCKPIT_PERISCOPE
		2,		// VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY
		2,		// VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY
		2,		// VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY
		2,		// VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY
		2,		// VIEW_MODE_EXTERNAL
		2,		// VIEW_MODE_SAFE
	};

int
	cockpit_panorama_row;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	cockpit_panorama_col_values[NUM_VIEW_MODES] =
	{
		0,		// VIEW_MODE_COCKPIT_PANEL_UP40_LEFT90
		1,		// VIEW_MODE_COCKPIT_PANEL_UP40_LEFT60
		2,		// VIEW_MODE_COCKPIT_PANEL_UP40_LEFT30
		3,		// VIEW_MODE_COCKPIT_PANEL_UP40_AHEAD
		4,		// VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT30
		5,		// VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT60
		6,		// VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT90
		0,		// VIEW_MODE_COCKPIT_PANEL_UP20_LEFT90
		1,		// VIEW_MODE_COCKPIT_PANEL_UP20_LEFT60
		2,		// VIEW_MODE_COCKPIT_PANEL_UP20_LEFT30
		3,		// VIEW_MODE_COCKPIT_PANEL_UP20_AHEAD
		4,		// VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT30
		5,		// VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT60
		6,		// VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT90
		0,		// VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT90
		1,		// VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT60
		2,		// VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT30
		3,		// VIEW_MODE_COCKPIT_PANEL_LEVEL_AHEAD
		4,		// VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT30
		5,		// VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT60
		6,		// VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT90
		0,		// VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT90
		1,		// VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT60
		2,		// VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT30
		3,		// VIEW_MODE_COCKPIT_PANEL_DOWN20_AHEAD
		4,		// VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT30
		5,		// VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT60
		6,		// VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT90
		3,		// VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_LHS_MFD
		3,		// VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_RHS_MFD
		3,		// VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_TV
		3,		// VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_HUD
		3,		// VIEW_MODE_VIRTUAL_COCKPIT
		3,		// VIEW_MODE_VIRTUAL_COCKPIT_PADLOCK
		3,		// VIEW_MODE_VIRTUAL_COCKPIT_TRACK_TARGET
		3,		// VIEW_MODE_VIRTUAL_COCKPIT_CREW
		3,		// VIEW_MODE_VIRTUAL_COCKPIT_HUD
		3,		// VIEW_MODE_VIRTUAL_COCKPIT_PERISCOPE
		3,		// VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY
		3,		// VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY
		3,		// VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY
		3,		// VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY
		3,		// VIEW_MODE_EXTERNAL
		3,		// VIEW_MODE_SAFE
	};

int
	cockpit_panorama_col;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

view_modes
	cockpit_panel_panorama[NUM_COCKPIT_PANORAMA_ROWS][NUM_COCKPIT_PANORAMA_COLS] =
	{
		{
			VIEW_MODE_COCKPIT_PANEL_UP40_LEFT90,
			VIEW_MODE_COCKPIT_PANEL_UP40_LEFT60,
			VIEW_MODE_COCKPIT_PANEL_UP40_LEFT30,
			VIEW_MODE_COCKPIT_PANEL_UP40_AHEAD,
			VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT30,
			VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT60,
			VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT90
		},
		{
			VIEW_MODE_COCKPIT_PANEL_UP20_LEFT90,
			VIEW_MODE_COCKPIT_PANEL_UP20_LEFT60,
			VIEW_MODE_COCKPIT_PANEL_UP20_LEFT30,
			VIEW_MODE_COCKPIT_PANEL_UP20_AHEAD,
			VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT30,
			VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT60,
			VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT90
		},
		{
			VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT90,
			VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT60,
			VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT30,
			VIEW_MODE_COCKPIT_PANEL_LEVEL_AHEAD,
			VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT30,
			VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT60,
			VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT90
		},
		{
			VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT90,
			VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT60,
			VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT30,
			VIEW_MODE_COCKPIT_PANEL_DOWN20_AHEAD,
			VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT30,
			VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT60,
			VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT90
		}
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float
	pilot_head_heading_values[NUM_VIEW_MODES] =
	{
		rad (90.0),		// VIEW_MODE_COCKPIT_PANEL_UP40_LEFT90
		rad (60.0),		// VIEW_MODE_COCKPIT_PANEL_UP40_LEFT60
		rad (30.0),		// VIEW_MODE_COCKPIT_PANEL_UP40_LEFT30
		rad (0.0),		// VIEW_MODE_COCKPIT_PANEL_UP40_AHEAD
		rad (-30.0),	// VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT30
		rad (-60.0),	// VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT60
		rad (-90.0),	// VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT90
		rad (90.0),		// VIEW_MODE_COCKPIT_PANEL_UP20_LEFT90
		rad (60.0),		// VIEW_MODE_COCKPIT_PANEL_UP20_LEFT60
		rad (30.0),		// VIEW_MODE_COCKPIT_PANEL_UP20_LEFT30
		rad (0.0),		// VIEW_MODE_COCKPIT_PANEL_UP20_AHEAD
		rad (-30.0),	// VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT30
		rad (-60.0),	// VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT60
		rad (-90.0),	// VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT90
		rad (90.0),		// VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT90
		rad (60.0),		// VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT60
		rad (30.0),		// VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT30
		rad (0.0),		// VIEW_MODE_COCKPIT_PANEL_LEVEL_AHEAD
		rad (-30.0),	// VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT30
		rad (-60.0),	// VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT60
		rad (-90.0),	// VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT90
		rad (90.0),		// VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT90
		rad (60.0),		// VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT60
		rad (30.0),		// VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT30
		rad (0.0),		// VIEW_MODE_COCKPIT_PANEL_DOWN20_AHEAD
		rad (-30.0),	// VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT30
		rad (-60.0),	// VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT60
		rad (-90.0),	// VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT90
		rad (0.0),		// VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_LHS_MFD
		rad (0.0),		// VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_RHS_MFD
		rad (0.0),		// VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_TV
		rad (0.0),		// VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_HUD
		rad (0.0),		// VIEW_MODE_VIRTUAL_COCKPIT
		rad (0.0),		// VIEW_MODE_VIRTUAL_COCKPIT_PADLOCK
		rad (0.0),		// VIEW_MODE_VIRTUAL_COCKPIT_TRACK_TARGET
		rad (0.0),		// VIEW_MODE_VIRTUAL_COCKPIT_CREW
		rad (0.0),		// VIEW_MODE_VIRTUAL_COCKPIT_HUD
		rad (0.0),		// VIEW_MODE_VIRTUAL_COCKPIT_PERISCOPE
		rad (0.0),		// VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY
		rad (0.0),		// VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY
		rad (0.0),		// VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY
		rad (0.0),		// VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY
		rad (0.0),		// VIEW_MODE_EXTERNAL
		rad (0.0),		// VIEW_MODE_SAFE
	};

float
	pilot_head_heading;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float
	pilot_head_pitch_values[NUM_VIEW_MODES] =
	{
		rad (40.0),		// VIEW_MODE_COCKPIT_PANEL_UP40_LEFT90
		rad (40.0),		// VIEW_MODE_COCKPIT_PANEL_UP40_LEFT60
		rad (40.0),		// VIEW_MODE_COCKPIT_PANEL_UP40_LEFT30
		rad (40.0),		// VIEW_MODE_COCKPIT_PANEL_UP40_AHEAD
		rad (40.0),		// VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT30
		rad (40.0),		// VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT60
		rad (40.0),		// VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT90
		rad (20.0),		// VIEW_MODE_COCKPIT_PANEL_UP20_LEFT90
		rad (20.0),		// VIEW_MODE_COCKPIT_PANEL_UP20_LEFT60
		rad (20.0),		// VIEW_MODE_COCKPIT_PANEL_UP20_LEFT30
		rad (20.0),		// VIEW_MODE_COCKPIT_PANEL_UP20_AHEAD
		rad (20.0),		// VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT30
		rad (20.0),		// VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT60
		rad (20.0),		// VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT90
		rad (0.0),		// VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT90
		rad (0.0),		// VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT60
		rad (0.0),		// VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT30
		rad (0.0),		// VIEW_MODE_COCKPIT_PANEL_LEVEL_AHEAD
		rad (0.0),		// VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT30
		rad (0.0),		// VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT60
		rad (0.0),		// VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT90
		rad (-20.0),	// VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT90
		rad (-20.0),	// VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT60
		rad (-20.0),	// VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT30
		rad (-20.0),	// VIEW_MODE_COCKPIT_PANEL_DOWN20_AHEAD
		rad (-20.0),	// VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT30
		rad (-20.0),	// VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT60
		rad (-20.0),	// VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT90
		rad (-20.0),	// VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_LHS_MFD
		rad (-20.0),	// VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_RHS_MFD
		rad (-20.0),	// VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_TV
		rad (0.0),		// VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_HUD
		rad (0.0),		// VIEW_MODE_VIRTUAL_COCKPIT
		rad (0.0),		// VIEW_MODE_VIRTUAL_COCKPIT_PADLOCK
		rad (0.0),		// VIEW_MODE_VIRTUAL_COCKPIT_TRACK_TARGET
		rad (0.0),		// VIEW_MODE_VIRTUAL_COCKPIT_CREW
		rad (0.0),		// VIEW_MODE_VIRTUAL_COCKPIT_HUD
		rad (0.0),		// VIEW_MODE_VIRTUAL_COCKPIT_PERISCOPE
		rad (0.0),		// VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY
		rad (0.0),		// VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY
		rad (0.0),		// VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY
		rad (0.0),		// VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY
		rad (0.0),		// VIEW_MODE_EXTERNAL
		rad (0.0),		// VIEW_MODE_SAFE
	};

float
	pilot_head_pitch;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float
	stored_pilot_head_heading,
	stored_pilot_head_pitch,
	stored_co_pilot_head_heading,
	stored_co_pilot_head_pitch;

view_modes
	stored_pilot_view_mode,
	stored_co_pilot_view_mode;

padlock_modes
	stored_pilot_padlock_mode,
	stored_co_pilot_padlock_mode;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

viewpoint
	pilot_head_vp;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	record_screen_sequence = FALSE;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//VJ 030318 wideview mod
int 
       wide_cockpit = FALSE;

int 
       edit_wide_cockpit = FALSE;
       
cockpit_position 
       wide_cockpit_position[6];  

int 
       wide_cockpit_nr;       

cockpit_position
		current_custom_cockpit_viewpoint;				// Retro 6Feb2005

//VJ 030324 framerate 
float
    framerate, framerate_avg;
int 
    doframerate;           

//VJ 030423 TSD render mod
tsd_render_modes 	
	tsd_render_mode;
	
//VJ 030429 TSD render mod
int tsd_render_palette;	