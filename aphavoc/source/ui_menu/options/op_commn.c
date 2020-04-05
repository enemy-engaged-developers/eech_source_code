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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ui_object
	*option_page_ok_button = nullptr,
	*ghost_sound_option_button = nullptr,
	*ghost_multiplayer_option_button = nullptr;

int
	option_page_ok_button_reasons;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_options_page_button (ui_object *obj, void *arg)
{
	options_pages
		page;

	page = (options_pages) get_ui_object_item_number (obj);

	notify_options_page (page);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void define_options_screen_common_objects (void)
{
	ui_object
		*option_bdrop = nullptr;

	float
		x1,
		y1,
		x2,
		y2;

	/////////////////////////////////////////////////////////////////
	// Graphics, Realism, Sound etc. 
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	// Realism Button

	x1 = 0.795;
	x2 = 0.194;
	y1 = 0.794;
	y2 = 0.052;

	option_bdrop = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (options_screen),
		UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
		UI_ATTR_VIRTUAL_SIZE (TEXT_OPTION_BDROP_WIDTH, TEXT_OPTION_BDROP_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_OFFSET_TIME (0),
		UI_ATTR_TIME_LENGTH (500),
		UI_ATTR_TEXTURE_GRAPHIC (text_option_bdrop),
		UI_ATTR_END
	);

	options_page_buttons [OPTIONS_PAGE_REALISM] = create_ui_object
	(
		UI_TYPE_BUTTON,
		UI_ATTR_PARENT (options_screen),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (x2, y2),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_options_page_button),
		UI_ATTR_ITEM_NUMBER (OPTIONS_PAGE_REALISM),
		UI_ATTR_TEXT (get_trans ("Realism Title")),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_FONT_TYPE (UI_FONT_STRETCH_ITALIC_ARIAL_18),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_OFFSET_TIME (0),
		UI_ATTR_TIME_LENGTH (500),
		UI_ATTR_END
	);

	preprocess_translation_object_size (options_page_buttons [OPTIONS_PAGE_REALISM], NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	set_text_option_backdrop_object (option_bdrop, options_page_buttons [OPTIONS_PAGE_REALISM]);

	/////////////////////////////////////////////////////////////////
	// Sound Button

	x1 = 0.550;
	x2 = 0.164;
	y1 = 0.902;
	y2 = 0.052;

	option_bdrop = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (options_screen),
		UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
		UI_ATTR_VIRTUAL_SIZE (TEXT_OPTION_BDROP_WIDTH, TEXT_OPTION_BDROP_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_OFFSET_TIME (0),
		UI_ATTR_TIME_LENGTH (500),
		UI_ATTR_TEXTURE_GRAPHIC (text_option_bdrop),
		UI_ATTR_END
	);

	options_page_buttons [OPTIONS_PAGE_SOUND] = create_ui_object
	(
		UI_TYPE_BUTTON,
		UI_ATTR_PARENT (options_screen),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (x2, y2),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_options_page_button),
		UI_ATTR_ITEM_NUMBER (OPTIONS_PAGE_SOUND),
		UI_ATTR_TEXT (get_trans ("SOUND MENU")),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_FONT_TYPE (UI_FONT_STRETCH_ITALIC_ARIAL_18),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_OFFSET_TIME (0),
		UI_ATTR_TIME_LENGTH (500),
		UI_ATTR_END
	);

	preprocess_translation_object_size (options_page_buttons [OPTIONS_PAGE_SOUND], NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	set_text_option_backdrop_object (option_bdrop, options_page_buttons [OPTIONS_PAGE_SOUND]);

	options_page_buttons [OPTIONS_PAGE_INGAME_SOUND] = create_ui_object
	(
		UI_TYPE_BUTTON,
		UI_ATTR_PARENT (options_screen),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (x2, y2),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_options_page_button),
		UI_ATTR_ITEM_NUMBER (OPTIONS_PAGE_INGAME_SOUND),
		UI_ATTR_TEXT (get_trans ("SOUND MENU")),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_FONT_TYPE (UI_FONT_STRETCH_ITALIC_ARIAL_18),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_OFFSET_TIME (0),
		UI_ATTR_TIME_LENGTH (500),
		UI_ATTR_END
	);

	preprocess_translation_object_size (options_page_buttons [OPTIONS_PAGE_INGAME_SOUND], NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	set_text_option_backdrop_object (option_bdrop, options_page_buttons [OPTIONS_PAGE_INGAME_SOUND]);

	x1 = get_ui_object_virtual_x (options_page_buttons [OPTIONS_PAGE_SOUND]);
	x2 = get_ui_object_virtual_x_size (options_page_buttons [OPTIONS_PAGE_SOUND]);

	ghost_sound_option_button = create_ui_object
									(
										UI_TYPE_AREA,
										UI_ATTR_PARENT (options_screen),
										UI_ATTR_VIRTUAL_POSITION (x1, y1),
										UI_ATTR_VIRTUAL_SIZE (x2, y2),
										UI_ATTR_CLEAR (TRUE),
										UI_ATTR_DRAWABLE (FALSE),
										UI_ATTR_END
									);

	/////////////////////////////////////////////////////////////////
	// Dynamics Button
	
	x1 = 0.648;
	x2 = 0.240;
	y1 = 0.743;
	y2 = 0.072;

	option_bdrop = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (options_screen),
		UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
		UI_ATTR_VIRTUAL_SIZE (TEXT_OPTION_BDROP_WIDTH, TEXT_OPTION_BDROP_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_OFFSET_TIME (0),
		UI_ATTR_TIME_LENGTH (500),
		UI_ATTR_TEXTURE_GRAPHIC (text_option_bdrop),
		UI_ATTR_END
	);

	options_page_buttons [OPTIONS_PAGE_DYNAMICS] = create_ui_object
	(
		UI_TYPE_BUTTON,
		UI_ATTR_PARENT (options_screen),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (x2, y2),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_options_page_button),
		UI_ATTR_ITEM_NUMBER (OPTIONS_PAGE_DYNAMICS),
		UI_ATTR_TEXT (get_trans("DYNAMICS MENU")),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_FONT_TYPE (UI_FONT_STRETCH_ITALIC_ARIAL_18),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_OFFSET_TIME (0),
		UI_ATTR_TIME_LENGTH (500),
		UI_ATTR_END
	);

	preprocess_translation_object_size (options_page_buttons [OPTIONS_PAGE_DYNAMICS], NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	set_text_option_backdrop_object (option_bdrop, options_page_buttons [OPTIONS_PAGE_DYNAMICS]);

	/////////////////////////////////////////////////////////////////
	// Graphics Button

	x1 = 0.422;
	x2 = 0.240;
	y1 = 0.849;
	y2 = 0.072;

	option_bdrop = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (options_screen),
		UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
		UI_ATTR_VIRTUAL_SIZE (TEXT_OPTION_BDROP_WIDTH, TEXT_OPTION_BDROP_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_OFFSET_TIME (0),
		UI_ATTR_TIME_LENGTH (500),
		UI_ATTR_TEXTURE_GRAPHIC (text_option_bdrop),
		UI_ATTR_END
	);

	options_page_buttons [OPTIONS_PAGE_GRAPHICS] = create_ui_object
	(
		UI_TYPE_BUTTON,
		UI_ATTR_PARENT (options_screen),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (x2, y2),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_options_page_button),
		UI_ATTR_ITEM_NUMBER (OPTIONS_PAGE_GRAPHICS),
		UI_ATTR_TEXT (get_trans("Graphics")),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_FONT_TYPE (UI_FONT_STRETCH_ITALIC_ARIAL_18),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_OFFSET_TIME (0),
		UI_ATTR_TIME_LENGTH (500),
		UI_ATTR_END
	);

	preprocess_translation_object_size (options_page_buttons [OPTIONS_PAGE_GRAPHICS], NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	set_text_option_backdrop_object (option_bdrop, options_page_buttons [OPTIONS_PAGE_GRAPHICS]);

	/////////////////////////////////////////////////////////////////
	// Controller Button

	x1 = 0.582;
	x2 = 0.211;
	y1 = 0.139;
	y2 = 0.052;

	option_bdrop = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (options_screen),
		UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
		UI_ATTR_VIRTUAL_SIZE (TEXT_OPTION_BDROP_WIDTH, TEXT_OPTION_BDROP_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_OFFSET_TIME (0),
		UI_ATTR_TIME_LENGTH (500),
		UI_ATTR_TEXTURE_GRAPHIC (text_option_bdrop),
		UI_ATTR_END
	);

	options_page_buttons [OPTIONS_PAGE_CONTROLLER] = create_ui_object
	(
		UI_TYPE_BUTTON,
		UI_ATTR_PARENT (options_screen),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (x2, y2),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_options_page_button),
		UI_ATTR_ITEM_NUMBER (OPTIONS_PAGE_CONTROLLER),
		UI_ATTR_TEXT (get_trans("CONTROLLER MENU")),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_FONT_TYPE (UI_FONT_STRETCH_ITALIC_ARIAL_18),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_OFFSET_TIME (0),
		UI_ATTR_TIME_LENGTH (500),
		UI_ATTR_END
	);

	preprocess_translation_object_size (options_page_buttons [OPTIONS_PAGE_CONTROLLER], NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	set_text_option_backdrop_object (option_bdrop, options_page_buttons [OPTIONS_PAGE_CONTROLLER]);

	/////////////////////////////////////////////////////////////////
	// Multiplayer Button

	x1 = 0.650;
	x2 = 0.311;
	y1 = 0.186;
	y2 = 0.052;

	option_bdrop = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (options_screen),
		UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
		UI_ATTR_VIRTUAL_SIZE (TEXT_OPTION_BDROP_WIDTH, TEXT_OPTION_BDROP_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_OFFSET_TIME (0),
		UI_ATTR_TIME_LENGTH (500),
		UI_ATTR_TEXTURE_GRAPHIC (text_option_bdrop),
		UI_ATTR_END
	);

	options_page_buttons [OPTIONS_PAGE_MULTIPLAYER] = create_ui_object
            (
               UI_TYPE_BUTTON,
               UI_ATTR_PARENT (options_screen),
					UI_ATTR_VIRTUAL_POSITION (x1, y1),
					UI_ATTR_VIRTUAL_SIZE (x2, y2),
					UI_ATTR_FUNCTION (notify_options_page_button),
					UI_ATTR_ITEM_NUMBER (OPTIONS_PAGE_MULTIPLAYER),
					UI_ATTR_TEXT (get_trans ("UI_MULTIPLAYER")),
					UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
					UI_ATTR_FONT_TYPE (UI_FONT_STRETCH_ITALIC_ARIAL_18),
			      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
			      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
			      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
				   UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
					UI_ATTR_HIGHLIGHTABLE (TRUE),
					UI_ATTR_CLEAR (TRUE),
					UI_ATTR_OFFSET_TIME (0),
					UI_ATTR_TIME_LENGTH (500),
               UI_ATTR_END
            );

	preprocess_translation_object_size (options_page_buttons [OPTIONS_PAGE_MULTIPLAYER], NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	set_text_option_backdrop_object (option_bdrop, options_page_buttons [OPTIONS_PAGE_MULTIPLAYER]);

	x1 = get_ui_object_virtual_x (options_page_buttons [OPTIONS_PAGE_MULTIPLAYER]);
	x2 = get_ui_object_virtual_x_size (options_page_buttons [OPTIONS_PAGE_MULTIPLAYER]);

	ghost_multiplayer_option_button = create_ui_object
									(
										UI_TYPE_AREA,
										UI_ATTR_PARENT (options_screen),
										UI_ATTR_VIRTUAL_POSITION (x1, y1),
										UI_ATTR_VIRTUAL_SIZE (x2, y2),
										UI_ATTR_CLEAR (TRUE),
										UI_ATTR_DRAWABLE (FALSE),
										UI_ATTR_END
									);

	/////////////////////////////////////////////////////////////////
	// Ok Button

	option_bdrop = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (options_screen),
		UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
		UI_ATTR_VIRTUAL_SIZE (TEXT_OPTION_BDROP_WIDTH, TEXT_OPTION_BDROP_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_OFFSET_TIME (0),
		UI_ATTR_TIME_LENGTH (500),
		UI_ATTR_TEXTURE_GRAPHIC (text_option_bdrop),
		UI_ATTR_END
	);

	option_page_ok_button = create_ui_object
			(
				UI_TYPE_BUTTON,
				UI_ATTR_PARENT (options_screen),
				UI_ATTR_VIRTUAL_POSITION (OPTIONS_OK_BUTTON_POS_X, OPTIONS_OK_BUTTON_POS_Y),
				UI_ATTR_VIRTUAL_SIZE (OPTIONS_OK_BUTTON_X, OPTIONS_OK_BUTTON_Y),
				UI_ATTR_TEXT (get_trans("UI_OK")),
				UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
				UI_ATTR_FUNCTION (notify_clear_options_screen),
				UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
				UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
      		UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      		UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      		UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      		UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
				UI_ATTR_HIGHLIGHTABLE (TRUE),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_COLOUR_START (255, 255, 255, 0),
				UI_ATTR_COLOUR_END (255, 255, 255, 255),
				UI_ATTR_OFFSET_TIME (0),
				UI_ATTR_TIME_LENGTH (500),
				UI_ATTR_END
			);
			
	set_text_option_backdrop_object (option_bdrop, option_page_ok_button);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void set_option_page_ok_button_reason (option_page_ok_button_reason reason, int set)
{
	if (set)
	{
		if (!option_page_ok_button_reasons)
		{
			set_ui_object_text (option_page_ok_button, get_trans ("Restart"));
		}
		option_page_ok_button_reasons |= 1 << reason;
	}
	else
	{
		option_page_ok_button_reasons &= ~(1 << reason);
		if (!option_page_ok_button_reasons)
		{
			set_ui_object_text (option_page_ok_button, get_trans ("UI_OK"));
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


