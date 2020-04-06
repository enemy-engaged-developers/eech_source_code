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

ui_object
	*exit_back_button = nullptr,
	*exit_screen_text = nullptr,
	*exit_forward_button = nullptr,
	*exit_screen = nullptr;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_exit_no_button (ui_object *obj, void *arg);

static void notify_exit_screen (ui_object *obj, void *arg);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_exit_screen (void)
{
	float
		x1,
		y1,
		x2,
		y2;

	x1 = 0.0;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 1.0;

   exit_screen = create_ui_object
            (
               UI_TYPE_SCREEN,
               UI_ATTR_VIRTUAL_POSITION (x1, y1),
               UI_ATTR_VIRTUAL_SIZE (x2, y2),
//               UI_ATTR_GRAPHIC (get_graphics_file_data (GRAPHICS_UI_APACHE_EXIT_SCREEN)),
					UI_ATTR_FUNCTION (notify_exit_screen),
					UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_DISPLAYED),
               UI_ATTR_END
            );

	x1 = 0.470;
	y1 = 0.5;

	exit_screen_text = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (exit_screen),
      UI_ATTR_VIRTUAL_POSITION (x1, y1),
//		UI_ATTR_TEXT (get_trans ("Quitting...")),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_22),
		UI_ATTR_END
	);
/*

	/////////////////////////////////////////////////////////////////
	// Ok Button

	exit_back_button = create_ui_object
			(
				UI_TYPE_BUTTON,
				UI_ATTR_PARENT (exit_screen),
				UI_ATTR_VIRTUAL_POSITION (OPTIONS_OK_BUTTON_POS_X, OPTIONS_OK_BUTTON_POS_Y),
				UI_ATTR_VIRTUAL_SIZE (OPTIONS_OK_BUTTON_X, OPTIONS_OK_BUTTON_Y),
				UI_ATTR_TEXT (get_trans("UI_OK")),
				UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
				UI_ATTR_FUNCTION (notify_exit_yes_button),
				UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
				UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
            UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
            UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
            UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
            UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
				UI_ATTR_HIGHLIGHTABLE (TRUE),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	/////////////////////////////////////////////////////////////////
	// Cancel Button

	exit_forward_button = create_ui_object
			(
				UI_TYPE_BUTTON,
				UI_ATTR_PARENT (exit_screen),
				UI_ATTR_VIRTUAL_POSITION (OPTIONS_CANCEL_BUTTON_POS_X, OPTIONS_CANCEL_BUTTON_POS_Y),
				UI_ATTR_VIRTUAL_SIZE (OPTIONS_CANCEL_BUTTON_X, OPTIONS_CANCEL_BUTTON_Y),
				UI_ATTR_TEXT (get_trans("UI_CANCEL")),
				UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
				UI_ATTR_FUNCTION (notify_exit_no_button),
				UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
				UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
            UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
            UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
            UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
            UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
				UI_ATTR_HIGHLIGHTABLE (TRUE),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);
*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_exit_screen (ui_object *obj, void *arg)
{

	if ( get_ui_object_drawable ( obj ) )
	{

		//
		// Setup screen graphics
		//

		set_ui_object_texture_graphic (exit_screen, create_texture_graphic ("graphics\\ui\\cohokum\\exit.psd", 0));

		reset_time_values (exit_screen);

		set_exit_ui (TRUE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
void notify_exit_no_button (ui_object *obj, void *arg)
{

	if ( ( int ) arg == BUTTON_STATE_DOWN )
	{

		set_ui_object_graphic ( obj, get_graphics_file_data ( GRAPHICS_UI_APACHE_PLANNER_FORWARD_BUTTON_SELECTED ) );

		set_ui_object_redraw ( exit_screen, TRUE );
	}
	else if ( ( int ) arg == BUTTON_STATE_UP )
	{

		set_ui_object_graphic ( obj, get_graphics_file_data ( GRAPHICS_UI_APACHE_PLANNER_FORWARD_BUTTON_UNSELECTED ) );

		pop_ui_screen (SCREEN_POP_ACTUAL);
	}
	else
	{

		set_ui_object_graphic ( obj, get_graphics_file_data ( GRAPHICS_UI_APACHE_PLANNER_FORWARD_BUTTON_UNSELECTED ) );

		set_ui_object_redraw ( exit_screen, TRUE );
	}

	set_ui_object_graphic_type ( obj, UI_OBJECT_ALPHA_GRAPHIC );
}
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_exit_yes_button (ui_object *obj, void *arg)
{

	if ( ( int ) arg == BUTTON_STATE_DOWN )
	{

#if 0
		set_ui_object_graphic ( obj, get_graphics_file_data ( GRAPHICS_UI_APACHE_PLANNER_BACK_BUTTON_SELECTED ) );

		set_ui_object_redraw ( exit_screen, TRUE );
#endif
	}
	else if ( ( int ) arg == BUTTON_STATE_UP )
	{

#if 0
		set_ui_object_graphic ( obj, get_graphics_file_data ( GRAPHICS_UI_APACHE_PLANNER_BACK_BUTTON_UNSELECTED ) );
#endif

		set_exit_ui (TRUE);
	}
	else
	{

#if 0
		set_ui_object_graphic ( obj, get_graphics_file_data ( GRAPHICS_UI_APACHE_PLANNER_BACK_BUTTON_UNSELECTED ) );

		set_ui_object_redraw ( exit_screen, TRUE );
#endif
	}

#if 0
	set_ui_object_graphic_type ( obj, UI_OBJECT_ALPHA_GRAPHIC );
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
