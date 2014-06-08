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

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

#define ADVERT_TEXT_Y_OFFSET 0.065

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ui_object
	*advert_ok_button,
	*advert_screen;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_select_player_exit_button (ui_object *obj, void *arg);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_advert_screen (ui_object *obj, void *arg)
{
/*	time_t
		start_time,
		end_time;

	float
		elapsed_time;
*/

	if ( get_ui_object_drawable ( obj ) )
	{

		//
		// Setup screen graphics
		//

		set_ui_object_texture_graphic (advert_screen, create_texture_graphic ("graphics\\ui\\cohokum\\advert.psd", 0));

		reset_time_values (advert_screen);
	}

	set_mouse_off ();

	set_ui_object_redraw (advert_screen, TRUE);

	ui_force_update ();

	Sleep (5000);

	set_mouse_on ();

//	push_ui_screen (main_screen);

	set_ui_object_drawable (advert_ok_button, TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_advert_screen (void)
{
//	ui_object
//		*temp;

	float
		x1,
		y1,
		x2,
		y2;

//	unsigned char
//		string [256];

	x1 = 0.0;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 1.0;

	/////////////////////////////////////////////////////////////////

   advert_screen = create_ui_object
            (
               UI_TYPE_SCREEN,
					UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
					UI_ATTR_VIRTUAL_SIZE (x2, y2),
					UI_ATTR_COLOUR_START (255, 255, 255, 0),
					UI_ATTR_COLOUR_END (255, 255, 255, 255),
					UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_DISPLAYED),
					UI_ATTR_FUNCTION (notify_advert_screen),
               UI_ATTR_END
            );
/*
	// combat

	x1 = 0.030;
	y1 = 0.050;
	x2 = 0.180;
	y2 = 0.040;


	sprintf (string, "%s", get_trans ("advert combat title"));

   temp = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (advert_screen),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (x2, y2),
		UI_ATTR_FONT_TYPE (UI_FONT_IMPACT_22),
      UI_ATTR_FONT_COLOUR_START (ui_screen_title_text_colour.r, ui_screen_title_text_colour.g, ui_screen_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_screen_title_text_colour.r, ui_screen_title_text_colour.g, ui_screen_title_text_colour.b, 255),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (string),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_END
	);

	preprocess_translation_object_size (temp, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	x1 = 0.066;
	y1 += ADVERT_TEXT_Y_OFFSET;
	x2 = 0.180;
	y2 = 0.040;

	sprintf (string, "%s", get_trans ("advert combat text 1"));

   temp = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (advert_screen),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (x2, y2),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
      UI_ATTR_FONT_COLOUR_START (255, 255, 255, 0),
      UI_ATTR_FONT_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (string),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_END
	);

	preprocess_translation_object_size (temp, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	// missions

	x1 = 0.438;
	y1 = 0.268;
	x2 = 0.180;
	y2 = 0.040;


	sprintf (string, "%s", get_trans ("advert missions title"));

   temp = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (advert_screen),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (x2, y2),
		UI_ATTR_FONT_TYPE (UI_FONT_IMPACT_22),
      UI_ATTR_FONT_COLOUR_START (ui_screen_title_text_colour.r, ui_screen_title_text_colour.g, ui_screen_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_screen_title_text_colour.r, ui_screen_title_text_colour.g, ui_screen_title_text_colour.b, 255),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (string),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_END
	);

	preprocess_translation_object_size (temp, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	x1 = 0.474;
	y1 += ADVERT_TEXT_Y_OFFSET;
	x2 = 0.180;
	y2 = 0.040;

	sprintf (string, "%s", get_trans ("advert missions text 1"));

   temp = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (advert_screen),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (x2, y2),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
      UI_ATTR_FONT_COLOUR_START (255, 255, 255, 0),
      UI_ATTR_FONT_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (string),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_END
	);

	preprocess_translation_object_size (temp, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	// campaigns

	x1 = 0.084;
	y1 = 0.480;
	x2 = 0.180;
	y2 = 0.040;


	sprintf (string, "%s", get_trans ("advert campaigns title"));

   temp = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (advert_screen),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (x2, y2),
		UI_ATTR_FONT_TYPE (UI_FONT_IMPACT_22),
      UI_ATTR_FONT_COLOUR_START (ui_screen_title_text_colour.r, ui_screen_title_text_colour.g, ui_screen_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_screen_title_text_colour.r, ui_screen_title_text_colour.g, ui_screen_title_text_colour.b, 255),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (string),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_END
	);

	preprocess_translation_object_size (temp, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	x1 = 0.120;
	y1 += ADVERT_TEXT_Y_OFFSET;
	x2 = 0.180;
	y2 = 0.040;

	sprintf (string, "%s", get_trans ("advert campaigns text 1"));

   temp = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (advert_screen),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (x2, y2),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
      UI_ATTR_FONT_COLOUR_START (255, 255, 255, 0),
      UI_ATTR_FONT_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (string),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_END
	);

	preprocess_translation_object_size (temp, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	// multiplayer

	x1 = 0.541;
	y1 = 0.687;
	x2 = 0.180;
	y2 = 0.040;


	sprintf (string, "%s", get_trans ("advert multiplayer title"));

   temp = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (advert_screen),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (x2, y2),
		UI_ATTR_FONT_TYPE (UI_FONT_IMPACT_22),
      UI_ATTR_FONT_COLOUR_START (ui_screen_title_text_colour.r, ui_screen_title_text_colour.g, ui_screen_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_screen_title_text_colour.r, ui_screen_title_text_colour.g, ui_screen_title_text_colour.b, 255),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (string),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_END
	);

	preprocess_translation_object_size (temp, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	x1 = 0.577;
	y1 += ADVERT_TEXT_Y_OFFSET;
	x2 = 0.180;
	y2 = 0.040;

	sprintf (string, "%s", get_trans ("advert multiplayer text 1"));

   temp = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (advert_screen),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (x2, y2),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
      UI_ATTR_FONT_COLOUR_START (255, 255, 255, 0),
      UI_ATTR_FONT_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (string),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_END
	);

	preprocess_translation_object_size (temp, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);
*/
	/////////////////////////////////////////////////////////////////
	// Ok Button

	advert_ok_button = create_ui_object
			(
				UI_TYPE_BUTTON,
				UI_ATTR_PARENT (advert_screen),
				UI_ATTR_VIRTUAL_POSITION (0.021, 0.915),
				UI_ATTR_VIRTUAL_SIZE (OPTIONS_OK_BUTTON_X, OPTIONS_OK_BUTTON_Y),
				UI_ATTR_TEXT (get_trans("UI_OK")),
				UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
				UI_ATTR_FUNCTION (notify_select_player_exit_button),
				UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_22),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
           	UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
           	UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
           	UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
           	UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
				UI_ATTR_HIGHLIGHTABLE (TRUE),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_DRAWABLE (FALSE),
				UI_ATTR_END
			);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_select_player_exit_button (ui_object *obj, void *arg)
{
	if ((int) arg == BUTTON_STATE_UP)
	{
		set_ui_object_redraw (advert_screen, TRUE);

//		pop_ui_screen (SCREEN_POP_ACTUAL);
		push_ui_screen (main_screen);
	}
	else
	{
		set_ui_object_redraw (advert_screen, TRUE);
	}

#if 0
	set_ui_object_graphic_type (obj, UI_OBJECT_ALPHA_GRAPHIC);
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


