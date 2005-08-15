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

#include "graphics.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

rgb_colour
	sys_col_black,
	sys_col_blue,
	sys_col_green,
	sys_col_cyan,
	sys_col_red,
	sys_col_magenta,
	sys_col_yellow,
	sys_col_white,
	sys_col_sky_blue,
	sys_col_slate_grey,
	sys_col_forest_green,
	sys_col_ultramarine,
	sys_col_seablue,
	sys_col_aquamarine,
	sys_col_gold,
	sys_col_light_grey,
	sys_col_light_red,
	sys_col_dark_red,
	sys_col_dark_green,
	sys_col_dark_blue,
	sys_col_medium_blue,
	sys_col_medium_red,
	sys_col_sandy_brown,
	sys_col_amber,
	sys_col_waypoint_route,
	sys_col_red_force,
	sys_col_blue_force;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

rgb_colour
	*sys_colour_table [] =
	{

		&sys_col_black,
		&sys_col_blue,
		&sys_col_green,
		&sys_col_cyan,
		&sys_col_red,
		&sys_col_magenta,
		&sys_col_yellow,
		&sys_col_white,
		&sys_col_sky_blue,
		&sys_col_slate_grey,
		&sys_col_forest_green,
		&sys_col_ultramarine,
		&sys_col_seablue,
		&sys_col_aquamarine,
		&sys_col_gold,
		&sys_col_light_grey,
		&sys_col_light_red,
		&sys_col_dark_red,
		&sys_col_dark_green,
		&sys_col_dark_blue,
		&sys_col_medium_blue,
		&sys_col_medium_red,
		&sys_col_sandy_brown,
		&sys_col_amber,
		&sys_col_waypoint_route,
		&sys_col_red_force,
		&sys_col_blue_force,
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char
	*sys_colour_names [] =
	{

		"COL_BLACK",
		"COL_BLUE",
		"COL_GREEN",
		"COL_CYAN",
		"COL_RED",
		"COL_MAGENTA",
		"COL_YELLOW",
		"COL_WHITE",
		"COL_SKY_BLUE",
		"COL_SLATE_GREY",
		"COL_FOREST_GREEN",
		"COL_ULTRAMARINE",
		"COL_SEABLUE",
		"COL_AQUAMARINE",
		"COL_GOLD",
		"COL_LIGHT_GREY",
		"COL_LIGHT_RED",
		"COL_DARK_RED",
		"COL_DARK_GREEN",
		"COL_DARK_BLUE",
		"COL_MEDIUM_BLUE",
		"COL_MEDIUM_RED",
		"COL_SANDY_BROWN",
		"COL_AMBER",
		"COL_WAYPOINT_ROUTE",
		"COL_RED_FORCE",
		"COL_BLUE_FORCE",
		"NUM_SYS_COLOURS"
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_graphics_colours ( void )
{

	set_rgb_colour (sys_col_black, 0, 0, 0, 255);
	set_rgb_colour (sys_col_blue, 0, 0, 255, 255);
	set_rgb_colour (sys_col_green, 0, 255, 0, 255);
	set_rgb_colour (sys_col_cyan, 0, 255, 255, 255);
	set_rgb_colour (sys_col_red, 255, 0, 0, 255);
	set_rgb_colour (sys_col_magenta, 255, 0, 255, 255);
	set_rgb_colour (sys_col_yellow, 255, 255, 0, 255);
	set_rgb_colour (sys_col_white, 255, 255, 255, 255);
	set_rgb_colour (sys_col_sky_blue, 135, 206, 235, 255);
	set_rgb_colour (sys_col_slate_grey, 112, 128, 144, 255);
	set_rgb_colour (sys_col_forest_green, 34, 139, 34, 255);
	set_rgb_colour (sys_col_ultramarine, 18, 0, 143, 255);
	set_rgb_colour (sys_col_seablue, 90, 130, 190, 255);
	set_rgb_colour (sys_col_aquamarine, 127, 255, 212, 255);
	set_rgb_colour (sys_col_gold, 255, 215, 0, 255);
	set_rgb_colour (sys_col_light_grey, 200, 200, 200, 255);
	set_rgb_colour (sys_col_light_red, 255, 150, 150, 255);
	set_rgb_colour (sys_col_dark_red, 150, 0, 0, 255);
	set_rgb_colour (sys_col_dark_green, 0, 150, 0, 255);
	set_rgb_colour (sys_col_dark_blue, 0, 0, 100, 255);
	set_rgb_colour (sys_col_medium_blue, 50, 50, 150, 255);
	set_rgb_colour (sys_col_medium_red, 255, 50, 50, 255);
	set_rgb_colour (sys_col_sandy_brown, 244, 164, 96, 255);
	set_rgb_colour (sys_col_amber, 255, 128, 0, 255);
	set_rgb_colour (sys_col_waypoint_route, 31, 0, 136, 255);
	set_rgb_colour (sys_col_red_force, 224, 27, 0, 255);
	set_rgb_colour (sys_col_blue_force, 41, 86, 255, 255);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
