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



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_show_ingame_sound_page (void)
{
	display_options_page (OPTIONS_PAGE_INGAME_SOUND);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_channel_muted (ui_object *obj, void *arg)
{
	int
		mute,
		channel;

	channel = get_ui_object_item_number (obj);

	ASSERT ((channel >= 0) && (channel < NUM_SOUND_CHANNEL_TYPES));

	mute = get_sound_channel_muted (channel);

	if (mute)
	{
		set_ui_object_text (obj, get_trans ("Off"));
	}
	else
	{
		set_ui_object_text (obj, get_trans ("On"));
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_channel_volume (ui_object *obj, void *arg)
{
	char
		s [8];

	int
		vol,
		channel;

	channel = get_ui_object_item_number (obj);

	ASSERT ((channel >= 0) && (channel < NUM_SOUND_CHANNEL_TYPES));

	vol = get_sound_channel_volume (channel);

	sprintf (s, "%d", vol);

	set_ui_object_text (obj, s);

	if (get_sound_channel_muted (channel))
	{
		set_ui_object_font_colour (obj, ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, ui_option_text_default_colour.a);
	}
	else
	{
		set_ui_object_font_colour (obj, ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, ui_option_title_text_colour.a);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void decrease_channel_volume (ui_object *obj, void *arg)
{
	int
		vol,
		channel;

	channel = get_ui_object_item_number (obj);

	ASSERT ((channel >= 0) && (channel < NUM_SOUND_CHANNEL_TYPES));

	set_sound_channel_muted (channel, FALSE);

	vol = get_sound_channel_volume (channel);

	vol --;

	set_sound_channel_volume (channel, vol);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void increase_channel_volume (ui_object *obj, void *arg)
{
	int
		vol,
		channel;

	channel = get_ui_object_item_number (obj);

	ASSERT ((channel >= 0) && (channel < NUM_SOUND_CHANNEL_TYPES));

	set_sound_channel_muted (channel, FALSE);

	vol = get_sound_channel_volume (channel);

	vol ++;

	set_sound_channel_volume (channel, vol);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void toggle_channel_muted (ui_object *obj, void *arg)
{
	int
		mute,
		channel;

	channel = get_ui_object_item_number (obj);

	ASSERT ((channel >= 0) && (channel < NUM_SOUND_CHANNEL_TYPES));

	mute = get_sound_channel_muted (channel);

	set_sound_channel_muted (channel, !mute);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void define_options_screen_ingame_sound_page_objects (void)
{
	int
		loop;

	float
		x1,
		y1,
		x2,
		y2;

	ui_object
		*page,
		*text_area,
		*channel_area,
		*volume_area;

	/////////////////////////////////////////////////////////////////
	// sound Area

	x1 = 0.0;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 1.0;

	options_page [OPTIONS_PAGE_INGAME_SOUND] = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (options_screen),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2, y2),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_DRAWABLE (FALSE),
				UI_ATTR_FUNCTION (NOTIFY_TYPE_NONE),
				UI_ATTR_END
			);

	page = options_page [OPTIONS_PAGE_INGAME_SOUND];

	//
	// Channel Options
	//

	x1 = 0.0;
	y1 = 0.0;

	x2 = 1.0;
	y2 = 1.0;

   channel_area = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (page),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_COLOUR_START (0,0,0,0),
		UI_ATTR_COLOUR_END (255,255,255,255),
		UI_ATTR_END
	);

	for (loop = 0; loop < NUM_SOUND_CHANNEL_TYPES; loop ++)
	{
		y1 = OPTION_TITLE_OFFSET_Y	+ (loop * OPTION_AREA_OFFSET_Y);
		y2 = y1 + OPTION_AREA_HEIGHT;

		//
		// Description
		//
		
		x1 = OPTION_TITLE_OFFSET_X;
		x2 = x1 + 0.4f;

		text_area = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (channel_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
			UI_ATTR_COLOUR_START (255,255,255,0),
   	   UI_ATTR_COLOUR_END (255,255,255,255),
			UI_ATTR_END
		);

		create_ui_object
		(
			UI_TYPE_TEXT,
			UI_ATTR_PARENT (text_area),
			UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
			UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
			UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
			UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
			UI_ATTR_TEXT (get_trans (get_sound_channel_name (loop))),
			UI_ATTR_END
		);

		//
		// Volume Controls
		//
		
		x1 = x2 + OPTION_BOX_GAP_WIDTH;
		x2 = x1 + 0.12;

		volume_area = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (channel_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_COLOUR_START (255,255,255,0),
			UI_ATTR_COLOUR_END (255,255,255,255),
			UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
			UI_ATTR_END
		);

		create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (volume_area),
			UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
			UI_ATTR_VIRTUAL_SIZE (0.33f, 1.0),
			UI_ATTR_TEXT ("-"),
			UI_ATTR_ITEM_NUMBER (loop),
			UI_ATTR_FUNCTION (decrease_channel_volume),
			UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
	      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
   	   UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
	      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
   	   UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
			UI_ATTR_HIGHLIGHTABLE (TRUE),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

		create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (volume_area),
			UI_ATTR_VIRTUAL_POSITION (0.67f, 0.0),
			UI_ATTR_VIRTUAL_SIZE (0.33f, 1.0),
			UI_ATTR_TEXT ("+"),
			UI_ATTR_ITEM_NUMBER (loop),
			UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
	      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
   	   UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
	      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
   	   UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
			UI_ATTR_HIGHLIGHTABLE (TRUE),
			UI_ATTR_FUNCTION (increase_channel_volume),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

		create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (volume_area),
			UI_ATTR_VIRTUAL_POSITION (0.33f, 0.0),
			UI_ATTR_VIRTUAL_SIZE (0.34, 1.0),
			UI_ATTR_TEXT (""),
			UI_ATTR_ITEM_NUMBER (loop),
			UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
			UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
			UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
			UI_ATTR_DRAW_FUNCTION (draw_channel_volume),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

		//
		// "Mute" toggle
		//
		
		x1 = x2 + OPTION_BOX_GAP_WIDTH;
		x2 = x1 + 0.12;

		create_ui_object
		(
			UI_TYPE_BUTTON,
			UI_ATTR_PARENT (channel_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_COLOUR_START (255,255,255,0),
			UI_ATTR_COLOUR_END (255,255,255,255),
			UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
			UI_ATTR_TEXT (get_trans ("On")),
			UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
	      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
   	   UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
	      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
   	   UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
			UI_ATTR_HIGHLIGHTABLE (TRUE),
			UI_ATTR_ITEM_NUMBER (loop),
			UI_ATTR_FUNCTION (toggle_channel_muted),
			UI_ATTR_DRAW_FUNCTION (draw_channel_muted),
			UI_ATTR_END
		);
	}

	//
	//
	//

	recursively_set_object_time (page, OPTIONS_BUTTON_AREA_FADE_TIME, OPTIONS_BUTTON_AREA_OFFSET_TIME);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

