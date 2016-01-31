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

#include "userint2.h"

#include "graphics.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

rgb_colour
	ui_colour_white,
	ui_colour_light_grey,
	ui_colour_grey,
	ui_colour_dark_grey,
	ui_colour_black,

	ui_colour_light_red,
	ui_colour_red,
	ui_colour_dark_red,

	ui_colour_orange,
	ui_colour_yellow,

	ui_colour_light_green,
	ui_colour_green,
	ui_colour_dark_green,

	ui_colour_cyan,
	ui_colour_light_blue,
	ui_colour_blue,
	ui_colour_dark_blue,
	ui_colour_purple,

	ui_colour_ui_orange,

	default_unselected_text_colour,
	default_selected_text_colour,

	ui_button_up_background,
	ui_button_up_light_edge,
	ui_button_up_dark_edge,
	ui_button_highlighted_background,
	ui_button_highlighted_light_edge,
	ui_button_highlighted_dark_edge,
	ui_button_down_background,
	ui_button_down_dark_edge,
	ui_button_down_light_edge,
	ui_area_background,
	ui_area_light_edge,
	ui_area_dark_edge,
	ui_area_highlighted_background,
	ui_area_highlighted_light_edge,
	ui_area_highlighted_dark_edge,
	ui_hilight_colour,

	ui_ingame_title_text_colour,
	ui_ingame_live_text_colour,
	ui_ingame_dead_text_colour,
	ui_ingame_highlight_text_colour,
	ui_ingame_selected_text_colour,
	ui_ingame_cycle_text_colour,

	ui_init_screen_text_colour,
	ui_screen_title_text_colour,
	ui_option_title_text_colour,
	ui_list_text_default_colour,
	ui_list_text_hilite_colour,
	ui_list_text_selected_colour,
	ui_option_text_default_colour,
	ui_option_text_hilite_colour,
	ui_option_text_selected_colour;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_ui_colours ( void )
{

	ui_colour_white.r = 255;
	ui_colour_white.g = 255;
	ui_colour_white.b = 255;
	ui_colour_white.a = 255;
	ui_colour_light_grey.r = 200;
	ui_colour_light_grey.g = 200;
	ui_colour_light_grey.b = 200;
	ui_colour_light_grey.a = 255;
	ui_colour_grey.r = 150;
	ui_colour_grey.g = 150;
	ui_colour_grey.b = 150;
	ui_colour_grey.a = 255;
	ui_colour_dark_grey.r = 100;
	ui_colour_dark_grey.g = 100;
	ui_colour_dark_grey.b = 100;
	ui_colour_dark_grey.a = 255;
	ui_colour_black.r = 0;
	ui_colour_black.g = 0;
	ui_colour_black.b = 0;
	ui_colour_black.a = 255;

	ui_colour_light_red.r = 255;
	ui_colour_light_red.g = 100;
	ui_colour_light_red.b = 100;
	ui_colour_light_red.a = 255;
	ui_colour_red.r = 255;
	ui_colour_red.g = 0;
	ui_colour_red.b = 0;
	ui_colour_red.a = 255;
	ui_colour_dark_red.r = 150;
	ui_colour_dark_red.g = 0;
	ui_colour_dark_red.b = 0;
	ui_colour_dark_red.a = 255;

	ui_colour_orange.r = 255;
	ui_colour_orange.g = 150;
	ui_colour_orange.b = 0;
	ui_colour_orange.a = 255;
	ui_colour_yellow.r = 255;
	ui_colour_yellow.g = 255;
	ui_colour_yellow.b = 0;
	ui_colour_yellow.a = 255;

	ui_colour_light_green.r = 100;
	ui_colour_light_green.g = 255;
	ui_colour_light_green.b = 100;
	ui_colour_light_green.a = 255;
	ui_colour_green.r = 0;
	ui_colour_green.g = 255;
	ui_colour_green.b = 0;
	ui_colour_green.a = 255;
	ui_colour_dark_green.r = 0;
	ui_colour_dark_green.g = 150;
	ui_colour_dark_green.b = 0;
	ui_colour_dark_green.a = 255;

	ui_colour_cyan.r = 0;
	ui_colour_cyan.g = 255;
	ui_colour_cyan.b = 255;
	ui_colour_cyan.a = 255;
	ui_colour_light_blue.r = 100;
	ui_colour_light_blue.g = 100;
	ui_colour_light_blue.b = 255;
	ui_colour_light_blue.a = 255;
	ui_colour_blue.r = 0;
	ui_colour_blue.g = 0;
	ui_colour_blue.b = 255;
	ui_colour_blue.a = 255;
	ui_colour_dark_blue.r = 0;
	ui_colour_dark_blue.g = 0;
	ui_colour_dark_blue.b = 150;
	ui_colour_dark_blue.a = 255;
	ui_colour_purple.r = 255;
	ui_colour_purple.g = 0;
	ui_colour_purple.b = 255;
	ui_colour_purple.a = 255;

	ui_colour_ui_orange.r = 254;
	ui_colour_ui_orange.g = 124;
	ui_colour_ui_orange.b = 47;
	ui_colour_ui_orange.a = 255;

	default_unselected_text_colour.r = 255;
	default_unselected_text_colour.g = 255;
	default_unselected_text_colour.b = 255;
	default_unselected_text_colour.a = 255;
	default_selected_text_colour.r = 255;
	default_selected_text_colour.g = 255;
	default_selected_text_colour.b = 0;
	default_selected_text_colour.a = 255;

	ui_button_up_background.r = 33;
	ui_button_up_background.g = 49;
	ui_button_up_background.b = 115;
	ui_button_up_background.a = 255;

	ui_button_up_light_edge.r = 115;
	ui_button_up_light_edge.g = 148;
	ui_button_up_light_edge.b = 222;
	ui_button_up_light_edge.a = 255;

	ui_button_up_dark_edge.r = 16;
	ui_button_up_dark_edge.g = 24;
	ui_button_up_dark_edge.b = 66;
	ui_button_up_dark_edge.a = 255;

	ui_button_highlighted_background.r = 100;
	ui_button_highlighted_background.g = 49;
	ui_button_highlighted_background.b = 30;
	ui_button_highlighted_background.a = 255;

	ui_button_highlighted_light_edge.r = 115;
	ui_button_highlighted_light_edge.g = 148;
	ui_button_highlighted_light_edge.b = 222;
	ui_button_highlighted_light_edge.a = 255;

	ui_button_highlighted_dark_edge.r = 16;
	ui_button_highlighted_dark_edge.g = 24;
	ui_button_highlighted_dark_edge.b = 66;
	ui_button_highlighted_dark_edge.a = 255;

	ui_button_down_background.r = 148;
	ui_button_down_background.g = 57;
	ui_button_down_background.b = 0;
	ui_button_down_background.a = 255;

	ui_button_down_dark_edge.r = 82;
	ui_button_down_dark_edge.g = 33;
	ui_button_down_dark_edge.b = 0;
	ui_button_down_dark_edge.a = 255;

	ui_button_down_light_edge.r = 255;
	ui_button_down_light_edge.g = 156;
	ui_button_down_light_edge.b = 82;
	ui_button_down_light_edge.a = 255;

	ui_area_background.r = 35;
	ui_area_background.g = 0;
	ui_area_background.b = 0;
	ui_area_background.a = 255;

	ui_area_light_edge.r = 100;
	ui_area_light_edge.g = 100;
	ui_area_light_edge.b = 100;
	ui_area_light_edge.a = 255;

	ui_area_dark_edge.r = 75;
	ui_area_dark_edge.g = 75;
	ui_area_dark_edge.b = 75;
	ui_area_dark_edge.a = 255;

	ui_area_highlighted_background.r = 30;
	ui_area_highlighted_background.g = 49;
	ui_area_highlighted_background.b = 100;
	ui_area_highlighted_background.a = 255;

	ui_area_highlighted_light_edge.r = 222;
	ui_area_highlighted_light_edge.g = 148;
	ui_area_highlighted_light_edge.b = 115;
	ui_area_highlighted_light_edge.a = 255;

	ui_area_highlighted_dark_edge.r = 66;
	ui_area_highlighted_dark_edge.g = 24;
	ui_area_highlighted_dark_edge.b = 16;
	ui_area_highlighted_dark_edge.a = 255;

	ui_hilight_colour.r = 255;
	ui_hilight_colour.g = 255;
	ui_hilight_colour.b = 255;
	ui_hilight_colour.a = 255;

	//
	// Ingame UI colours
	//

	ui_ingame_title_text_colour.r = 40;
	ui_ingame_title_text_colour.g = 40;
	ui_ingame_title_text_colour.b = 128;
	ui_ingame_title_text_colour.a = 255;

	ui_ingame_live_text_colour.r = 96;
	ui_ingame_live_text_colour.g = 96;
	ui_ingame_live_text_colour.b = 222;
	ui_ingame_live_text_colour.a = 255;

	ui_ingame_dead_text_colour.r = 200;
	ui_ingame_dead_text_colour.g = 32;
	ui_ingame_dead_text_colour.b = 32;
	ui_ingame_dead_text_colour.a = 255;

	ui_ingame_highlight_text_colour.r = 255;
	ui_ingame_highlight_text_colour.g = 255;
	ui_ingame_highlight_text_colour.b = 255;
	ui_ingame_highlight_text_colour.a = 255;

	ui_ingame_selected_text_colour.r = 192;
	ui_ingame_selected_text_colour.g = 192;
	ui_ingame_selected_text_colour.b = 192;
	ui_ingame_selected_text_colour.a = 255;

	ui_ingame_cycle_text_colour.r = 120;
	ui_ingame_cycle_text_colour.g = 120;
	ui_ingame_cycle_text_colour.b = 255;
	ui_ingame_cycle_text_colour.a = 255;

	// following colours only used for main ui - not for "in session" screens yet, except ingame options screen

	// init screen colour
	ui_init_screen_text_colour.r = 2;
	ui_init_screen_text_colour.g = 159;
	ui_init_screen_text_colour.b = 85;
	ui_init_screen_text_colour.a = 255;

	// screen title text - yellow - dead
	ui_screen_title_text_colour.r = 255;
	ui_screen_title_text_colour.g = 255;
	ui_screen_title_text_colour.b = 255;
	ui_screen_title_text_colour.a = 255;

	// option title text - orange - dead
	ui_option_title_text_colour.r = 180;
	ui_option_title_text_colour.g = 180;
	ui_option_title_text_colour.b = 180;
	ui_option_title_text_colour.a =255;

	// list text colours - live
	ui_list_text_default_colour.r = 192;
	ui_list_text_default_colour.g = 192;
	ui_list_text_default_colour.b = 220;
	ui_list_text_default_colour.a =255;

	ui_list_text_hilite_colour.r = 255;
	ui_list_text_hilite_colour.g = 255;
	ui_list_text_hilite_colour.b = 255;
	ui_list_text_hilite_colour.a =255;

	ui_list_text_selected_colour.r = 255;
	ui_list_text_selected_colour.g = 255;
	ui_list_text_selected_colour.b = 0;
	ui_list_text_selected_colour.a =255;

	// all other text - live
	ui_option_text_default_colour.r = 220;
	ui_option_text_default_colour.g = 220;
	ui_option_text_default_colour.b = 220;
	ui_option_text_default_colour.a = 255;

	ui_option_text_hilite_colour.r = 255;
	ui_option_text_hilite_colour.g = 255;
	ui_option_text_hilite_colour.b = 255;
	ui_option_text_hilite_colour.a = 255;

	ui_option_text_selected_colour.r = 40;
	ui_option_text_selected_colour.g = 0;
	ui_option_text_selected_colour.b = 255;
	ui_option_text_selected_colour.a = 255;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


