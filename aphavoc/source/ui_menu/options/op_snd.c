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

static ui_object
	*sound_effect_area,
	*music_area,
	*speech_area,
	*co_pilot_speech_area,
	*sound_effect_option_button,
	*music_option_button,
	*speech_option_button,
	*co_pilot_speech_option_button;

static const char
	*option_boolean_text[2];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_sound_effect_option_button ( ui_object *obj, void *arg );

void notify_music_option_button ( ui_object *obj, void *arg );

void notify_speech_option_button ( ui_object *obj, void *arg );

void notify_co_pilot_speech_option_button ( ui_object *obj, void *arg );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_show_sound_page (void)
{
	// initialise button text
	
	set_ui_object_text (sound_effect_option_button, option_boolean_text[get_global_sound_effects_enabled ()]);

	if (get_global_sound_music () == GAME_MUSIC_ON)
	{
		set_ui_object_text (music_option_button, option_boolean_text[1]);
	}
	else
	{
		set_ui_object_text (music_option_button, option_boolean_text[0]);
	}

	set_ui_object_text (speech_option_button, option_boolean_text[get_global_speech_effects_enabled ()]);

	set_ui_object_text (co_pilot_speech_option_button, option_boolean_text[get_global_copilot_speech_effects_enabled ()]);

	display_options_page (OPTIONS_PAGE_SOUND);

	#if DEBUG_MODULE

	debug_filtered_log("Inside show_sound_page");

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void define_options_screen_sound_page_objects (void)
{
	int
		i = 0;

	float
		x1,
		y1,
		x2,
		y2;

	ui_object
		*page;

	ui_object
		*title_change_array [4],
		*check_array [4],
		*change_array [4];

	/////////////////////////////////////////////////////////////////
	// Initialise Button Strings

	option_boolean_text [0] = get_trans ("Off");
	option_boolean_text [1] = get_trans ("On");

	/////////////////////////////////////////////////////////////////
	// sound Area

	x1 = 0.0;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 1.0;

	options_page [OPTIONS_PAGE_SOUND] = create_ui_object
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

	page = options_page [OPTIONS_PAGE_SOUND];

	// areas and titles

	// sound effect

	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (OPTION_AREA_OFFSET_Y * i);

   sound_effect_area = create_ui_object
									(
										UI_TYPE_AREA,
										UI_ATTR_PARENT (page),
										UI_ATTR_VIRTUAL_POSITION (x1, y1),
										UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, OPTION_AREA_HEIGHT),
										UI_ATTR_CLEAR (TRUE),
					               UI_ATTR_COLOUR_START (0,0,0,0),
            					   UI_ATTR_COLOUR_END (255,255,255,255),
										UI_ATTR_END
									);

	x1 = OPTION_TITLE_OFFSET_X;
	y1 = 0.0; 

	title_change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (sound_effect_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255,255,255,0),
      UI_ATTR_COLOUR_END (255,255,255,255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

   check_array[i] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array [i]),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("Sound Effects")),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [i], check_array [i], NULL, 0, RESIZE_OPTION_BOX_TITLE);

	//music area

	y1 += OPTION_AREA_OFFSET_Y;

	i++;
	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (OPTION_AREA_OFFSET_Y * i);

   music_area = create_ui_object
								(
									UI_TYPE_AREA,
									UI_ATTR_PARENT ( page ),
									UI_ATTR_VIRTUAL_POSITION (x1, y1),
									UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, OPTION_AREA_HEIGHT),
									UI_ATTR_CLEAR (TRUE),
									UI_ATTR_COLOUR_START (255,255,255,0),
           					   UI_ATTR_COLOUR_END (255,255,255,255),
									UI_ATTR_END
								);

	x1 = OPTION_TITLE_OFFSET_X;
	y1 = 0.0; 

	title_change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (music_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255,255,255,0),
	   UI_ATTR_COLOUR_END (255,255,255,255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

   check_array[i] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array [i]),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("Music")),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [i], check_array [i], NULL, 0, RESIZE_OPTION_BOX_TITLE);

	//speech area
	
	y1 += OPTION_AREA_OFFSET_Y;

	i++;
	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (OPTION_AREA_OFFSET_Y * i);

   speech_area = create_ui_object
								(
									UI_TYPE_AREA,
									UI_ATTR_PARENT ( page ),
									UI_ATTR_VIRTUAL_POSITION (x1, y1),
									UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, OPTION_AREA_HEIGHT),
									UI_ATTR_CLEAR (TRUE),
									UI_ATTR_COLOUR_START (255,255,255,0),
           					   UI_ATTR_COLOUR_END (255,255,255,255),
									UI_ATTR_END
								);

	x1 = OPTION_TITLE_OFFSET_X;
	y1 = 0.0; 

	title_change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (speech_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255,255,255,0),
		UI_ATTR_COLOUR_END (255,255,255,255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

   check_array[i] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array [i]),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("Speech")),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [i], check_array [i], NULL, 0, RESIZE_OPTION_BOX_TITLE);

	//co-pilot speech

	y1 += OPTION_AREA_OFFSET_Y;

	i++;
	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (OPTION_AREA_OFFSET_Y * i);

   co_pilot_speech_area = create_ui_object
										(
											UI_TYPE_AREA,
											UI_ATTR_PARENT (page),
											UI_ATTR_VIRTUAL_POSITION (x1, y1),
											UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, OPTION_AREA_HEIGHT),
											UI_ATTR_CLEAR (TRUE),
											UI_ATTR_COLOUR_START (255,255,255,0),
     		       					   UI_ATTR_COLOUR_END (255,255,255,255),
											UI_ATTR_END
										);

	x1 = OPTION_TITLE_OFFSET_X;
	y1 = 0.0; 

	title_change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (co_pilot_speech_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

   check_array[i] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array [i]),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("Co-Pilot Speech")),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [i], check_array [i], NULL, 0, RESIZE_OPTION_BOX_TITLE);


	/////////////////////////////////////////////////////////////////
	// buttons

	i = 0;

	//sound effects
	
	change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (sound_effect_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [i]) + get_ui_object_x_size_end (title_change_array [i]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_SMALL_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255,255,255,0),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_small),
		UI_ATTR_END
	);

   sound_effect_option_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (sound_effect_area),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
		UI_ATTR_VIRTUAL_POSITION (get_ui_object_x_end (change_array [i]) + OPTION_BUTTON_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_sound_effect_option_button),
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], sound_effect_option_button, option_boolean_text, 2, RESIZE_OPTION_CYCLE_BUTTON);

	// music

	i++;
		
	change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (music_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [i]) + get_ui_object_x_size_end (title_change_array [i]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_SMALL_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255,255,255,0),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_small),
		UI_ATTR_END
	);

   music_option_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (music_area),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
		UI_ATTR_VIRTUAL_POSITION (get_ui_object_x_end (change_array [i]) + OPTION_BUTTON_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_music_option_button),
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], music_option_button, option_boolean_text, 2, RESIZE_OPTION_CYCLE_BUTTON);

	//speech
	
	i++;
		
	change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (speech_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [i]) + get_ui_object_x_size_end (title_change_array [i]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_SMALL_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255,255,255,0),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_small),
		UI_ATTR_END
	);

   speech_option_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (speech_area),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
		UI_ATTR_VIRTUAL_POSITION (get_ui_object_x_end (change_array [i]) + OPTION_BUTTON_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_speech_option_button),
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], speech_option_button, option_boolean_text, 2, RESIZE_OPTION_CYCLE_BUTTON);

	//co-pilot speech
	
	i++;
		
	change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (co_pilot_speech_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [i]) + get_ui_object_x_size_end (title_change_array [i]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_SMALL_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255,255,255,0),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_small),
		UI_ATTR_END
	);

   co_pilot_speech_option_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (co_pilot_speech_area),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
		UI_ATTR_VIRTUAL_POSITION (get_ui_object_x_end (change_array [i]) + OPTION_BUTTON_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_co_pilot_speech_option_button),
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], co_pilot_speech_option_button, option_boolean_text, 2, RESIZE_OPTION_CYCLE_BUTTON);

	recursively_set_object_time (page, OPTIONS_BUTTON_AREA_FADE_TIME, OPTIONS_BUTTON_AREA_OFFSET_TIME);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_sound_effect_option_button ( ui_object *obj, void *arg )
{

	int
		selection;

	selection = !get_global_sound_effects_enabled ();
	
	set_ui_object_text (sound_effect_option_button, option_boolean_text [selection]);

	set_global_sound_effects_enabled (selection);

	if (selection)
	{
		set_global_sound_effects_enabled ( TRUE );

		if ( !get_application_sound_system_status () )
		{
			initialise_application_sound_system ();
		}
	}
	else
	{
		set_global_sound_effects_enabled ( FALSE );

		if ( get_application_sound_system_status () && (!get_global_speech_effects_enabled ()))
		{
			deinitialise_application_sound_system ();
		}
	}
		
	// don't leave text selected

	set_toggle_button_off (obj);

	#if DEBUG_MODULE

	debug_filtered_log ("sound effects: %d", get_global_sound_effects_enabled ());

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_music_option_button ( ui_object *obj, void *arg )
{

	int
		selection;

	selection =  ( get_global_sound_music () == GAME_MUSIC_ON ) ? GAME_MUSIC_OFF : GAME_MUSIC_ON;

	if (selection == GAME_MUSIC_ON)
	{
		set_ui_object_text (music_option_button, option_boolean_text [TRUE]);

		set_global_sound_music ( GAME_MUSIC_ON );

//		play_cd_music (CD_MUSIC_TYPE_INTRO);
	}
	else
	{
		set_ui_object_text (music_option_button, option_boolean_text [FALSE]);

		set_global_sound_music ( GAME_MUSIC_OFF );

		stop_cd_music ();
	}
	
	// don't leave text selected

	set_toggle_button_off (obj);

	#if DEBUG_MODULE

	debug_filtered_log ("music: %d", get_global_sound_music ());

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_speech_option_button ( ui_object *obj, void *arg )
{

	int
		selection;

	selection = !get_global_speech_effects_enabled ();

	set_ui_object_text (speech_option_button, option_boolean_text [selection]);

	if(selection)
	{
		set_global_speech_effects_enabled ( TRUE );

		if ( !get_application_sound_system_status () )
		{
			initialise_application_sound_system ();
		}
	}
	else
	{
		set_global_speech_effects_enabled ( FALSE );

		if ( get_application_sound_system_status () && (!get_global_sound_effects_enabled ()))
		{	
			deinitialise_application_sound_system ();
		}
	}

	// don't leave text selected

	set_toggle_button_off (obj);
	
	#if DEBUG_MODULE

	debug_filtered_log ("speech: %d", get_global_speech_effects_enabled ());

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_co_pilot_speech_option_button ( ui_object *obj, void *arg )
{

	int
		selection;

	selection = !get_global_copilot_speech_effects_enabled ();
	
	set_ui_object_text (co_pilot_speech_option_button, option_boolean_text [selection]);

	if(selection)
	{
		set_global_copilot_speech_effects_enabled ( TRUE );

		if ( !get_application_sound_system_status () )
		{	
			initialise_application_sound_system ();
		}
	}
	else
	{
		set_global_copilot_speech_effects_enabled ( FALSE );

		if ( get_application_sound_system_status () && (!get_global_sound_effects_enabled ()))
		{	
			deinitialise_application_sound_system ();
		}
	}

	// don't leave text selected

	set_toggle_button_off (obj);

	#if DEBUG_MODULE

	debug_filtered_log ("copilot speech: %d", get_global_copilot_speech_effects_enabled ());

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

