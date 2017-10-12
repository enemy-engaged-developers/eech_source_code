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

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ui_object
	*realism_area,
	*co_pilot_target_area,
	*co_pilot_ecm_area,
	*avionics_area,
	*difficulty_area,
	*cpg_report_targets_area,
	*co_pilot_target_option_button,
	*co_pilot_ecm_option_button,
	*avionics_option_button,
	*difficulty_option_button,
	*cpg_report_targets_button;

static const char
	*option_boolean_text[2],
	*option_cpg_text[3],
	*option_avionics_text[3],
	*option_difficulty_text[3],
	*option_cpg_report_targets_text[2];
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_co_pilot_target_option_button (ui_object *obj, void *arg);

void notify_co_pilot_ecm_option_button (ui_object *obj, void *arg);

void notify_avionics_option_button (ui_object *obj, void *arg);

void notify_difficulty_option_button (ui_object *obj, void *arg);

void notify_cpg_report_targets_option_button (ui_object *obj, void *arg);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_show_realism_page (void)
{
	set_ui_object_text (co_pilot_target_option_button, option_cpg_text [get_global_cpg_assist_type ()]);

	#if DEBUG_MODULE
	debug_filtered_log ("cpg_assist: %d text: %s",get_global_cpg_assist_type (), option_cpg_text [get_global_cpg_assist_type ()]);
	#endif

	set_ui_object_text (co_pilot_ecm_option_button, option_boolean_text [get_global_auto_counter_measures ()]);

	#if DEBUG_MODULE
	debug_filtered_log ("acm: %d text: %s", get_global_auto_counter_measures (), option_boolean_text [get_global_auto_counter_measures ()]);
	#endif

	set_ui_object_text (avionics_option_button, option_avionics_text [get_global_avionics_realism_level ()]);

	#if DEBUG_MODULE
	debug_filtered_log ("avionics: %d text: %s", get_global_avionics_realism_level (), option_avionics_text [get_global_avionics_realism_level ()]);
	#endif

	set_ui_object_text (difficulty_option_button, option_difficulty_text [get_global_difficulty_level () - 1]);

	#if DEBUG_MODULE
	debug_filtered_log ("diff: %d text: %s", get_global_difficulty_level (), option_difficulty_text [get_global_difficulty_level () - 1]);
	#endif

	set_ui_object_text (cpg_report_targets_button, option_cpg_report_targets_text[global_co_pilot_scans_for_targets]);

	display_options_page (OPTIONS_PAGE_REALISM);
	#if DEBUG_MODULE
		debug_filtered_log("Inside show_realism_page");
	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void define_options_screen_realism_page_objects (void)
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
		*title_change_array [5],
		*check_array [5],
		*change_array [5];

	/////////////////////////////////////////////////////////////////
	// Initialise Button Strings

	option_boolean_text [0] = get_trans ("Off");
	option_boolean_text [1] = get_trans ("On");

	option_cpg_text [0] = get_trans ("Off");
	option_cpg_text [1] = get_trans ("Novice");
	option_cpg_text [2] = get_trans ("Realistic");

	option_avionics_text [0] = get_trans ("Simple");
	option_avionics_text [1] = get_trans ("Advanced");
	option_avionics_text [2] = get_trans ("Realistic");

	option_difficulty_text [0] = get_trans ("Hard");
	option_difficulty_text [1] = get_trans ("Medium");
	option_difficulty_text [2] = get_trans ("Easy");

	option_cpg_report_targets_text[0] = get_trans ("Off");
	option_cpg_report_targets_text[1] = get_trans ("On");

	/////////////////////////////////////////////////////////////////
	// realism Area

	x1 = 0.0;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 1.0;

	options_page [OPTIONS_PAGE_REALISM] = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (options_screen),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_DRAWABLE (FALSE),
				UI_ATTR_FUNCTION (NOTIFY_TYPE_NONE),
				UI_ATTR_END
			);

	page = options_page [OPTIONS_PAGE_REALISM];

	// areas and titles

	// co_pilot_target_area

	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (OPTION_AREA_OFFSET_Y * i);

   co_pilot_target_area = create_ui_object
									(
										UI_TYPE_AREA,
										UI_ATTR_PARENT (page),
										UI_ATTR_VIRTUAL_POSITION (x1, y1),
										UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, OPTION_AREA_HEIGHT),
										UI_ATTR_CLEAR (TRUE),
										UI_ATTR_END
									);

	x1 = OPTION_TITLE_OFFSET_X;
	y1 = 0.0; 

	title_change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (co_pilot_target_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START ( 255, 255, 255, 0 ),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
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
		UI_ATTR_TEXT (get_trans ("Co-Pilot Target ID")),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [i], check_array [i], NULL, 0, RESIZE_OPTION_BOX_TITLE);

	//co_pilot_ecm area

	i++;
	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (OPTION_AREA_OFFSET_Y * i);

   co_pilot_ecm_area = create_ui_object
								(
									UI_TYPE_AREA,
									UI_ATTR_PARENT ( page ),
									UI_ATTR_VIRTUAL_POSITION (x1, y1),
									UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, OPTION_AREA_HEIGHT),
									UI_ATTR_CLEAR (TRUE),
									UI_ATTR_END
								);

	x1 = OPTION_TITLE_OFFSET_X;
	y1 = 0.0; 

	title_change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (co_pilot_ecm_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START ( 255, 255, 255, 0 ),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
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
		UI_ATTR_TEXT (get_trans ("Co-Pilot ECM")),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [i], check_array [i], NULL, 0, RESIZE_OPTION_BOX_TITLE);

	//avionics area

	i++;
	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (OPTION_AREA_OFFSET_Y * i);

   avionics_area = create_ui_object
								(
									UI_TYPE_AREA,
									UI_ATTR_PARENT (page),
									UI_ATTR_VIRTUAL_POSITION (x1, y1),
									UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, OPTION_AREA_HEIGHT),
									UI_ATTR_CLEAR (TRUE),
									UI_ATTR_END
								);

	x1 = OPTION_TITLE_OFFSET_X;
	y1 = 0.0; 

	title_change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (avionics_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START ( 255, 255, 255, 0 ),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
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
		UI_ATTR_TEXT (get_trans ("Avionics")),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [i], check_array [i], NULL, 0, RESIZE_OPTION_BOX_TITLE);

	//difficulty area

	i++;
	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (OPTION_AREA_OFFSET_Y * i);

   difficulty_area = create_ui_object
								(
									UI_TYPE_AREA,
									UI_ATTR_PARENT (page),
									UI_ATTR_VIRTUAL_POSITION (x1, y1),
									UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, OPTION_AREA_HEIGHT),
									UI_ATTR_CLEAR (TRUE),
									UI_ATTR_END
								);

	x1 = OPTION_TITLE_OFFSET_X;
	y1 = 0.0; 

	title_change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (difficulty_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START ( 255, 255, 255, 0 ),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
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
		UI_ATTR_TEXT (get_trans ("Difficulty")),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [i], check_array [i], NULL, 0, RESIZE_OPTION_BOX_TITLE);

	//cpg report targets area

	i++;
	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (OPTION_AREA_OFFSET_Y * i);

    cpg_report_targets_area = create_ui_object
								(
									UI_TYPE_AREA,
									UI_ATTR_PARENT (page),
									UI_ATTR_VIRTUAL_POSITION (x1, y1),
									UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, OPTION_AREA_HEIGHT),
									UI_ATTR_CLEAR (TRUE),
									UI_ATTR_END
								);

	x1 = OPTION_TITLE_OFFSET_X;
	y1 = 0.0; 

	title_change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (cpg_report_targets_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START ( 255, 255, 255, 0 ),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
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
		UI_ATTR_TEXT (get_trans ("Co-Pilot report targets")),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [i], check_array [i], NULL, 0, RESIZE_OPTION_BOX_TITLE);


	/////////////////////////////////////////////////////////////////
	// buttons

	i = 0;

	//Co-Pilot target ID
	
	change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (co_pilot_target_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [i]) + get_ui_object_x_size_end (title_change_array [i]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_MEDIUM_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START ( 255, 255, 255, 0 ),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_medium),
		UI_ATTR_END
	);

	// hack for russian
	if (get_global_current_language () == LANGUAGE_RUSSIAN)
	{
		set_ui_object_virtual_x_size (change_array [i], OPTION_BOX_LARGE_WIDTH);
		set_ui_object_texture_graphic (change_array [i], options_box_large);
	}
	
   co_pilot_target_option_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (co_pilot_target_area),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
		UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
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
		UI_ATTR_FUNCTION (notify_co_pilot_target_option_button),
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], co_pilot_target_option_button, option_cpg_text, 2, RESIZE_OPTION_CYCLE_BUTTON);

	// co_pilot_ecm
	
	i++;
		
	change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (co_pilot_ecm_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [i]) + get_ui_object_x_size_end (title_change_array [i]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_SMALL_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START ( 255, 255, 255, 0 ),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_small),
		UI_ATTR_END
	);

   co_pilot_ecm_option_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (co_pilot_ecm_area),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
		UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
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
		UI_ATTR_FUNCTION (notify_co_pilot_ecm_option_button),
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], co_pilot_ecm_option_button, option_boolean_text, 2, RESIZE_OPTION_CYCLE_BUTTON);

	// avionics
	
	i++;
		
	change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (avionics_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [i]) + get_ui_object_x_size_end (title_change_array [i]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_MEDIUM_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START ( 255, 255, 255, 0 ),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_medium),
		UI_ATTR_END
	);

   avionics_option_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (avionics_area),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
		UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
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
		UI_ATTR_FUNCTION (notify_avionics_option_button),
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], avionics_option_button, option_avionics_text, 2, RESIZE_OPTION_CYCLE_BUTTON);

	// difficulty setting
	
	i++;
		
	change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (difficulty_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [i]) + get_ui_object_x_size_end (title_change_array [i]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_MEDIUM_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START ( 255, 255, 255, 0 ),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_medium),
		UI_ATTR_END
	);

   difficulty_option_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (difficulty_area),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
		UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
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
		UI_ATTR_FUNCTION (notify_difficulty_option_button),
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], difficulty_option_button, option_difficulty_text, 3, RESIZE_OPTION_CYCLE_BUTTON);

	// cpg report target setting
	
	i++;
		
	change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (cpg_report_targets_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [i]) + get_ui_object_x_size_end (title_change_array [i]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_MEDIUM_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START ( 255, 255, 255, 0 ),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_medium),
		UI_ATTR_END
	);

    cpg_report_targets_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (cpg_report_targets_area),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
		UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
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
		UI_ATTR_FUNCTION (notify_cpg_report_targets_option_button),
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], cpg_report_targets_area, option_cpg_report_targets_text, 4, RESIZE_OPTION_CYCLE_BUTTON);

	recursively_set_object_time (page, OPTIONS_BUTTON_AREA_FADE_TIME, OPTIONS_BUTTON_AREA_OFFSET_TIME);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_co_pilot_target_option_button ( ui_object *obj, void *arg )
{
	int
		selection;
		
	selection = (get_global_cpg_assist_type () + 1) % NUM_CPG_ASSISTANCE_TYPES;

	set_global_cpg_assist_type ((cpg_assist_types) selection);

	set_ui_object_text (obj, option_cpg_text [selection]);

	// don't leave text selected

	set_toggle_button_off (obj);

	#if DEBUG_MODULE
		debug_filtered_log("selection:%d", selection);
	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_co_pilot_ecm_option_button ( ui_object *obj, void *arg )
{

	set_global_auto_counter_measures (!get_global_auto_counter_measures ());

	set_ui_object_text (obj, option_boolean_text [get_global_auto_counter_measures ()]);

	// don't leave text selected

	set_toggle_button_off (obj);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_avionics_option_button ( ui_object *obj, void *arg )
{

	if (get_global_avionics_realism_level () < AVIONICS_REALISM_LEVEL_REALISTIC)
		set_global_avionics_realism_level (get_global_avionics_realism_level () + 1);
	else
		set_global_avionics_realism_level (AVIONICS_REALISM_LEVEL_SIMPLE);

	set_ui_object_text (obj, option_avionics_text [get_global_avionics_realism_level ()]);

	#if DEBUG_MODULE
	debug_filtered_log ("avionics: %d text: %s", get_global_avionics_realism_level (), option_avionics_text [get_global_avionics_realism_level ()]);
	#endif

	// don't leave text selected

	set_toggle_button_off (obj);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_difficulty_option_button ( ui_object *obj, void *arg )
{
	int
		selection;

	selection = get_global_difficulty_level ();

	selection--;
	
	if (selection < GAME_DIFFICULTY_HARD)
	{
		selection = GAME_DIFFICULTY_EASY;
	}
	
	set_global_difficulty_level ((enum GAME_DIFFICULTY_SETTINGS) selection);

	set_ui_object_text (obj, option_difficulty_text [selection - 1]);

	// don't leave text selected

	set_toggle_button_off (obj);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_cpg_report_targets_option_button ( ui_object *obj, void *arg )
{
	global_co_pilot_scans_for_targets = !global_co_pilot_scans_for_targets;

	set_ui_object_text (obj, option_cpg_report_targets_text [global_co_pilot_scans_for_targets]);

	// don't leave text selected

	set_toggle_button_off (obj);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
