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

void initialise_free_flight_screen_selection_objects (void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_quit_free_flight (ui_object *obj, void *arg)
{
	setup_free_flight_quit_campaign_dialog ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_cockpit_button (ui_object *obj, void *arg)
{
	if (get_gunship_entity ())
	{
		set_view_mode (VIEW_MODE_COCKPIT_PANEL_LEVEL_AHEAD);
	}

	toggle_in_flight_game_modes (NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void define_free_flight_screen_selection_objects (void)
{
	float
		x1,
		y1,
		x2,
		y2;

	/////////////////////////////////////////////////////////////////
	// QUIT / COCKPIT BUTTONS
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	// Cockpit Button

	x1 = 0.831;
	y1 = 0.90;
	x2 = 1.0;
	y2 = 0.987;

	create_ui_object
		(
			UI_TYPE_BUTTON,
			UI_ATTR_PARENT (free_flight_screen),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT (get_trans ("Cockpit")),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
			UI_ATTR_FUNCTION (notify_cockpit_button),
			UI_ATTR_FONT_COLOUR (ui_ingame_live_text_colour.r, ui_ingame_live_text_colour.g, ui_ingame_live_text_colour.b, ui_ingame_live_text_colour.a),
			UI_ATTR_HIGHLIGHTED_FONT_COLOUR (ui_ingame_highlight_text_colour.r, ui_ingame_highlight_text_colour.g, ui_ingame_highlight_text_colour.b, ui_ingame_highlight_text_colour.a),
			UI_ATTR_SELECTED_FONT_COLOUR (ui_ingame_selected_text_colour.r, ui_ingame_selected_text_colour.g, ui_ingame_selected_text_colour.b, ui_ingame_selected_text_colour.a),
			UI_ATTR_HIGHLIGHTABLE (TRUE),
			UI_ATTR_TEXTURE_GRAPHIC (create_texture_graphic ("graphics\\ui\\cohokum\\map\\flybtn.psd")),
			UI_ATTR_END
		);

	/////////////////////////////////////////////////////////////////
	// Exit Free Flight

	x1 = 0.0;
	y1 = 0.90;
	x2 = 0.168;
	y2 = 0.987;

	create_ui_object
		(
			UI_TYPE_BUTTON,
			UI_ATTR_PARENT (free_flight_screen),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT (get_trans ("Exit")),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
			UI_ATTR_FONT_COLOUR (ui_ingame_live_text_colour.r, ui_ingame_live_text_colour.g, ui_ingame_live_text_colour.b, ui_ingame_live_text_colour.a),
			UI_ATTR_HIGHLIGHTED_FONT_COLOUR (ui_ingame_highlight_text_colour.r, ui_ingame_highlight_text_colour.g, ui_ingame_highlight_text_colour.b, ui_ingame_highlight_text_colour.a),
			UI_ATTR_SELECTED_FONT_COLOUR (ui_ingame_selected_text_colour.r, ui_ingame_selected_text_colour.g, ui_ingame_selected_text_colour.b, ui_ingame_selected_text_colour.a),
			UI_ATTR_HIGHLIGHTABLE (TRUE),
			UI_ATTR_TEXTURE_GRAPHIC (create_texture_graphic ("graphics\\ui\\cohokum\\map\\exitbtn.psd")),
			UI_ATTR_FUNCTION (notify_quit_free_flight),
			UI_ATTR_END
		);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


