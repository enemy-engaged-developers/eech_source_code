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



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

void notify_terrain_detail_option_button ( ui_object *obj, void *arg );

void notify_object_detail_option_button ( ui_object *obj, void *arg );

void notify_cockpit_detail_option_button ( ui_object *obj, void *arg );

void notify_rain_textures_option_button ( ui_object *obj, void *arg );

void notify_incockpit_blurred_option_button ( ui_object *obj, void *arg );

void notify_card_selection_button ( ui_object *obj, void *arg );

void notify_screen_resolution_button (ui_object *obj, void *arg);

void notify_screen_accept_button (ui_object *obj, void *arg);

static void set_card_selection_device ( display_device *device );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ui_object
	*graphics_area,
	*terrain_detail_area1,
	*object_detail_area1,
	*cockpit_detail_area1,
	*rain_textures_area1,
	*incockpit_blurred_area1,
	*card_selection_area1,
	*card_selection_title_graphic_area,
	*card_selection_title_text,
	*ghost_card_selection_area1,
	*screen_resolution_area,
	*screen_accept_area,
	*terrain_detail_button,
	*object_detail_button,
	*cockpit_detail_button,
	*rain_textures_option_button,
	*incockpit_blurred_option_button,
	*card_selection_button_graphic,
	*card_selection_button,
	*screen_resolution_button,
	*screen_accept_button;

static const char
	*detail_text[3],
	*option_boolean_text[2],
	*option_gcard_text[2];

float
	new_width,
	new_height;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_show_graphics_page (void)
{
	display_device
		*device;

	int
		found = 0;

	unsigned char
		text [32];
				
	new_width = global_options.visual_screen_width;

	new_height = global_options.visual_screen_height;

	#if DEBUG_MODULE
		debug_filtered_log("Inside show_graphics_page");
	#endif

	// initialise button text
	
	set_ui_object_text (terrain_detail_button, detail_text[get_global_graphics_terrain_detail_level () - 1]);

	set_ui_object_text (object_detail_button, detail_text[get_global_graphics_object_detail_level () - 1]);

	set_ui_object_text (cockpit_detail_button, detail_text[get_global_cockpit_detail_level ()]);

	set_ui_object_text (rain_textures_option_button, option_boolean_text [get_global_graphics_rain_textures_enabled ()]);

	set_ui_object_text (incockpit_blurred_option_button, option_boolean_text [get_global_blurred_main_rotors_visible_from_cockpit ()]);

	// get current graphics card selected

	if ( get_global_graphics_device_selection_automatic () )
	{
		set_ui_object_text (card_selection_button, option_gcard_text [0]);

		set_ui_object_font_type (card_selection_button, UI_FONT_THICK_ITALIC_ARIAL_18);
	}
	else if ( get_global_graphics_device_selection_primary () )
	{
		set_ui_object_text (card_selection_button, option_gcard_text [1]);

		preprocess_translation_object_size (card_selection_button_graphic, card_selection_button, option_gcard_text, 2, RESIZE_OPTION_CYCLE_BUTTON);

		set_ui_object_font_type (card_selection_button, UI_FONT_THICK_ITALIC_ARIAL_18);
	}
	else
	{
		device = display_devices;

		while (device)
		{
			if (	( get_global_graphics_device_selection_primary () && device->is_primary ) ||
					( memcmp ( &device->guid, &global_options.graphics_device_guid, sizeof ( GUID ) ) == 0 ) )
			{
				set_ui_object_text (card_selection_button, device->name);

				preprocess_translation_object_size (card_selection_button_graphic, card_selection_button, ( const char * * ) &device->name, 1, RESIZE_OPTION_CYCLE_BUTTON);

				found = 1;

				break;
			}
			
			device = device->succ;
		}

		if (!found)
		{
			set_global_graphics_device_selection_automatic (TRUE);
			
			set_ui_object_text (card_selection_button, option_gcard_text [1]);

			preprocess_translation_object_size (card_selection_button_graphic, card_selection_button, option_gcard_text, 2, RESIZE_OPTION_CYCLE_BUTTON);

			debug_log ("OP_GRAFX.C: No display device found! Reverting to Auto");
		}
	}

	// set resolution button text

	sprintf (text, "%.0fx%.0f", new_width, new_height);

	set_ui_object_text (screen_resolution_button, text);

	// modify "accept" button

	if ( (new_width != global_options.visual_screen_width) || (new_height != global_options.visual_screen_height) )
	{
		set_ui_object_drawable (screen_accept_button, TRUE);
	}
	else
	{
		set_ui_object_drawable (screen_accept_button, FALSE);
	}
	

	// if called from within game - hide certain options
	if (get_current_game_session())
	{
		set_ui_object_highlightable (card_selection_button, FALSE);

		set_ui_object_colour_end (card_selection_title_graphic_area, 255, 255, 255, 127);

		set_ui_object_font_colour_end (card_selection_title_text, ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 127);

		set_ui_object_colour_end (card_selection_button_graphic, 255, 255, 255, 127);

		set_ui_object_font_colour_end (card_selection_button, ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 127);

		set_ui_object_drawable (ghost_card_selection_area1, TRUE);
	}
	else
	{
		set_ui_object_highlightable (card_selection_button, TRUE);
		
		set_ui_object_colour_end (card_selection_title_graphic_area, 255, 255, 255, 255);

		set_ui_object_font_colour_end (card_selection_title_text, ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255);

		set_ui_object_colour_end (card_selection_button_graphic, 255, 255, 255, 255);

		set_ui_object_font_colour_end (card_selection_button, ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255);

		set_ui_object_drawable (ghost_card_selection_area1, FALSE);
	}

	display_options_page (OPTIONS_PAGE_GRAPHICS);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void define_options_screen_graphics_page_objects (void)
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
		*title_change_array [7],
		*check_array [7],
		*change_array [8];

	/////////////////////////////////////////////////////////////////
	// Initialise Button Strings
	
	detail_text [0] = get_trans ("Low");
	detail_text [1] = get_trans ("Medium");
	detail_text [2] = get_trans ("High");

	option_boolean_text [0] = get_trans ("Off");
	option_boolean_text [1] = get_trans ("On");

	option_gcard_text [0] = get_trans ("Automatic");
	option_gcard_text [1] = get_trans ("Primary Display Driver");

	/////////////////////////////////////////////////////////////////
	// graphics Area

	x1 = 0.0;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 1.0;

	options_page [OPTIONS_PAGE_GRAPHICS] = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (options_screen),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2, y2),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_FUNCTION (NOTIFY_TYPE_NONE),
				UI_ATTR_END
			);

	page = options_page [OPTIONS_PAGE_GRAPHICS];

	// areas and titles

	// terrain detail

	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (OPTION_AREA_OFFSET_Y * i);

   terrain_detail_area1 = create_ui_object
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

	title_change_array [i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (terrain_detail_area1),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

   check_array [i] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array [i]),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("Terrain Detail")),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [i], check_array [i], NULL, 0, RESIZE_OPTION_BOX_TITLE);

	//object detail

	i++;
	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (OPTION_AREA_OFFSET_Y * i);

   object_detail_area1 = create_ui_object
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

	title_change_array [i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (object_detail_area1),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

   check_array [i] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array [i]),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("Object Detail")),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [i], check_array [i], NULL, 0, RESIZE_OPTION_BOX_TITLE);

	//cockpit detail

	i++;
	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (OPTION_AREA_OFFSET_Y * i);

   cockpit_detail_area1 = create_ui_object
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

	title_change_array [i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (cockpit_detail_area1),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

   check_array [i] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array [i]),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("Cockpit Detail")),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [i], check_array [i], NULL, 0, RESIZE_OPTION_BOX_TITLE);

	//rain textures
	
	i++;
	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (OPTION_AREA_OFFSET_Y * i);

   rain_textures_area1 = create_ui_object
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

	title_change_array [i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (rain_textures_area1),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

   check_array [i] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array [i]),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("Rain Textures")),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [i], check_array [i], NULL, 0, RESIZE_OPTION_BOX_TITLE);

	//incockpit blurred rotors

	i++;
	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (OPTION_AREA_OFFSET_Y * i);

   incockpit_blurred_area1 = create_ui_object
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

	title_change_array [i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (incockpit_blurred_area1),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

   check_array [i] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array [i]),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("Cockpit Rotors")),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [i], check_array [i], NULL, 0, RESIZE_OPTION_BOX_TITLE);

	//graphics card selection
	
	i++;
	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (OPTION_AREA_OFFSET_Y * i);

	card_selection_area1 = create_ui_object
									(
										UI_TYPE_AREA,
										UI_ATTR_PARENT (page),
										UI_ATTR_VIRTUAL_POSITION (x1, y1),
										UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, OPTION_AREA_HEIGHT),
										UI_ATTR_CLEAR (TRUE),
										UI_ATTR_END
									);

	ghost_card_selection_area1 = create_ui_object
									(
										UI_TYPE_AREA,
										UI_ATTR_PARENT (page),
										UI_ATTR_VIRTUAL_POSITION (x1, y1),
										UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, OPTION_AREA_HEIGHT),
										UI_ATTR_CLEAR (TRUE),
										UI_ATTR_DRAWABLE (FALSE),
										UI_ATTR_END
									);

	x1 = OPTION_TITLE_OFFSET_X;
	y1 = 0.0; 

	title_change_array [i] = card_selection_title_graphic_area = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (card_selection_area1),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

   check_array [i] = card_selection_title_text = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array [i]),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("Device Selection")),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [i], check_array [i], NULL, 0, RESIZE_OPTION_BOX_TITLE);

	// screen resolution selection
	
	i++;
	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (OPTION_AREA_OFFSET_Y * i);

	screen_resolution_area = create_ui_object
									(
										UI_TYPE_AREA,
										UI_ATTR_PARENT ( page ),
										UI_ATTR_VIRTUAL_POSITION (x1, y1),
										UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, OPTION_AREA_HEIGHT),
										UI_ATTR_CLEAR ( TRUE ),
										UI_ATTR_END
									);

	x1 = OPTION_TITLE_OFFSET_X;
	y1 = 0.0; 

	title_change_array [i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (screen_resolution_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

   check_array [i] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array [i]),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("Screen Resolution")),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [i], check_array [i], NULL, 0, RESIZE_OPTION_BOX_TITLE);

	

	/////////////////////////////////////////////////////////////////
	// buttons

	i = 0;

	//terrain detail
	
	change_array [i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (terrain_detail_area1),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [i]) + get_ui_object_x_size_end (title_change_array [i]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_MEDIUM_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_medium),
		UI_ATTR_END
	);

   terrain_detail_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (terrain_detail_area1),
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
		UI_ATTR_FUNCTION (notify_terrain_detail_option_button),
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], terrain_detail_button, detail_text, 3, RESIZE_OPTION_CYCLE_BUTTON);

	// object detail

	i++;

	change_array [i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (object_detail_area1),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [i]) + get_ui_object_x_size_end (title_change_array [i]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_MEDIUM_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_medium),
		UI_ATTR_END
	);

   object_detail_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (object_detail_area1),
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
		UI_ATTR_FUNCTION (notify_object_detail_option_button),
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], object_detail_button, detail_text, 3, RESIZE_OPTION_CYCLE_BUTTON);

	// cockpit detail
	
	i++;

	change_array [i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (cockpit_detail_area1),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [i]) + get_ui_object_x_size_end (title_change_array [i]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_MEDIUM_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_medium),
		UI_ATTR_END
	);

   cockpit_detail_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (cockpit_detail_area1),
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
		UI_ATTR_FUNCTION (notify_cockpit_detail_option_button),
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], cockpit_detail_button, detail_text, 3, RESIZE_OPTION_CYCLE_BUTTON);

	// rain textures option
	
	i++;

	change_array [i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (rain_textures_area1),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [i]) + get_ui_object_x_size_end (title_change_array [i]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_SMALL_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_small),
		UI_ATTR_END
	);

   rain_textures_option_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (rain_textures_area1),
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
		UI_ATTR_FUNCTION (notify_rain_textures_option_button),
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], rain_textures_option_button, option_boolean_text, 2, RESIZE_OPTION_CYCLE_BUTTON);

	// in cockpit blurred rotor option
	
	i++;

	change_array [i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (incockpit_blurred_area1),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [i]) + get_ui_object_x_size_end (title_change_array [i]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_SMALL_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_small),
		UI_ATTR_END
	);

   incockpit_blurred_option_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (incockpit_blurred_area1),
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
		UI_ATTR_FUNCTION (notify_incockpit_blurred_option_button),
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], incockpit_blurred_option_button, option_boolean_text, 2, RESIZE_OPTION_CYCLE_BUTTON);

	// graphics card selection
	
	i++;

	change_array [i] = card_selection_button_graphic = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (card_selection_area1),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [i]) + get_ui_object_x_size_end (title_change_array [i]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_LARGE_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

   card_selection_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (card_selection_area1),
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
		UI_ATTR_FUNCTION (notify_card_selection_button),
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], card_selection_button, option_gcard_text, 2, RESIZE_OPTION_CYCLE_BUTTON);

	// screen resolution selection
	
	i++;

	change_array [i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (screen_resolution_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [i]) + get_ui_object_x_size_end (title_change_array [i]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_MEDIUM_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_medium),
		UI_ATTR_END
	);

   screen_resolution_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (screen_resolution_area),
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
		UI_ATTR_FUNCTION (notify_screen_resolution_button),
		UI_ATTR_END
	);

	// screen resolution accept

	i++;
	
	change_array [i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (screen_resolution_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (change_array [i - 1]) + get_ui_object_x_size_start (change_array [i - 1]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_SMALL_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_medium),
		UI_ATTR_END
	);

   screen_accept_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (screen_resolution_area),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
		UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
		UI_ATTR_VIRTUAL_POSITION (get_ui_object_x_end (change_array [i]) + OPTION_BUTTON_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (get_trans ("Accept")),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_screen_accept_button),
		UI_ATTR_DRAWABLE (FALSE),
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], screen_accept_button, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	set_ui_object_virtual_x_size (change_array[i], (get_ui_object_virtual_x_size (change_array [i]) * 1.1));

	recursively_set_object_time (page, OPTIONS_BUTTON_AREA_FADE_TIME, OPTIONS_BUTTON_AREA_OFFSET_TIME);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_terrain_detail_option_button ( ui_object *obj, void *arg )
{
	int
		lod;

	lod = get_global_graphics_terrain_detail_level ();

	lod = (lod) % 3;

	set_ui_object_text (terrain_detail_button, detail_text [lod]);

	set_global_graphics_terrain_detail_level (lod+1);

	set_3d_detail_levels ();

	// don't leave text selected

	set_toggle_button_off (obj);

	#ifdef DEBUG_MODULE
		debug_filtered_log ("terrain detail level: %d", get_global_graphics_terrain_detail_level ());
	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_object_detail_option_button ( ui_object *obj, void *arg )
{
	int
		lod;

	lod = get_global_graphics_object_detail_level ();

	lod++;

	if (lod == 4)
	{
		lod = 1;
	}

	set_global_graphics_object_detail_level (lod);

	set_ui_object_text (object_detail_button, detail_text [lod-1]);

	set_3d_detail_levels ();

	// don't leave text selected

	set_toggle_button_off (obj);

	#ifdef DEBUG_MODULE
		debug_filtered_log ("object detail level: %d", get_global_graphics_object_detail_level ());
	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_cockpit_detail_option_button ( ui_object *obj, void *arg )
{
	cockpit_detail_levels
		lod;

	lod = get_global_cockpit_detail_level ();

	lod++;

	if (lod == NUM_COCKPIT_DETAIL_LEVELS)
	{
		lod = COCKPIT_DETAIL_LEVEL_LOW;
	}

	set_global_cockpit_detail_level (lod);

	set_ui_object_text (cockpit_detail_button, detail_text [lod]);

	set_3d_detail_levels ();

	// don't leave text selected

	set_toggle_button_off (obj);

	#if DEBUG_MODULE
		debug_filtered_log ("cockpit detail level: %d", get_global_cockpit_detail_level ());
	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_rain_textures_option_button ( ui_object *obj, void *arg )
{

	int
		selection;

	selection = !get_global_graphics_rain_textures_enabled ();
	
	set_global_graphics_rain_textures_enabled (selection);

	set_ui_object_text (rain_textures_option_button, option_boolean_text [selection]);

	// don't leave text selected

	set_toggle_button_off (obj);

	#ifdef DEBUG_MODULE
		debug_filtered_log ("rain textures: %d", get_global_graphics_rain_textures_enabled ());
	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_incockpit_blurred_option_button ( ui_object *obj, void *arg )
{

	int
		selection;

	selection = !get_global_blurred_main_rotors_visible_from_cockpit ();
	
	set_global_blurred_main_rotors_visible_from_cockpit (selection);

	set_ui_object_text (incockpit_blurred_option_button, option_boolean_text [selection]);

	// don't leave text selected

	set_toggle_button_off (obj);

	#ifdef DEBUG_MODULE
		debug_filtered_log ("blurred rotors: %d", get_global_blurred_main_rotors_visible_from_cockpit ());
	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_card_selection_button ( ui_object *obj, void *arg )
{

	display_device
		*device;

	//
	// Set next device identifiers
	//

	if ( get_global_graphics_device_selection_automatic () )
	{

		set_card_selection_device ( display_devices );
	}
	else
	{

		device = get_card_selection_device ();

		if ( device )
		{

			device = device->succ;
		}

		set_card_selection_device ( device );
	}

	//
	// Now reflect the new device in the text
	//

	if ( get_global_graphics_device_selection_automatic () )
	{

		set_ui_object_text ( card_selection_button, option_gcard_text[0] );

		set_ui_object_font_type ( card_selection_button, UI_FONT_THICK_ITALIC_ARIAL_18 );

		// set size of graphics card button

//		preprocess_translation_object_size (card_selection_button_graphic, NULL, option_gcard_text, 2, RESIZE_OPTION_CYCLE_BUTTON);
	}
	else
	{

		device = get_card_selection_device ();

		if ( device->is_primary )
		{

			set_ui_object_text ( card_selection_button, option_gcard_text[1] );
	
			set_ui_object_font_type ( card_selection_button, UI_FONT_THICK_ITALIC_ARIAL_18 );

			// set size of graphics card button

			preprocess_translation_object_size (card_selection_button_graphic, card_selection_button, option_gcard_text, 2, RESIZE_OPTION_CYCLE_BUTTON);
		}
		else
		{
	
			set_ui_object_text ( card_selection_button, device->name );

			// set size of graphics card button

//			preprocess_translation_object_size (card_selection_button_graphic, card_selection_button, &device->name, 1, RESIZE_OPTION_CYCLE_BUTTON);
		}
	}

	// modify ok button text

	if (old_graphics_card_automatic_selection != get_global_graphics_device_selection_automatic ())
	{
		set_ui_object_text (option_page_ok_button, get_trans ("Restart"));
	}
	else
	{
		set_ui_object_text (option_page_ok_button, get_trans ("UI_OK"));
	}

	if (!old_graphics_card_automatic_selection)
	{
		if (old_graphics_card_selection != get_card_selection_device ())
		{
			set_ui_object_text (option_page_ok_button, get_trans ("Restart"));
		}
		else
		{
			set_ui_object_text (option_page_ok_button, get_trans ("UI_OK"));
		}
	}

	// don't leave text selected

	set_toggle_button_off (obj);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_card_selection_device ( display_device *device )
{

	if ( device )
	{
		set_global_graphics_device_selection_automatic ( FALSE );
	
		if ( device->is_primary )
		{
			set_global_graphics_device_selection_primary ( TRUE );
		}
		else
		{
			set_global_graphics_device_selection_primary ( FALSE );

			set_global_graphics_device_selection_guid ( &device->guid );
		}
	}
	else
	{
		set_global_graphics_device_selection_automatic ( TRUE );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

display_device *get_card_selection_device ( void )
{

	display_device
		*device;

	device = display_devices;

	while ( device )
	{

		if ( get_global_graphics_device_selection_primary () )
		{

			if ( device->is_primary )
			{

				return ( device );
			}
		}
		else
		{

			if ( memcmp ( &device->guid, &global_options.graphics_device_guid, sizeof ( GUID ) ) == 0 )
			{
	
				return ( device );
			}
		}

		device = device->succ;
	}

	return ( NULL );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_screen_resolution_button (ui_object *obj, void *arg)
{
	unsigned char
		text [12];

	int
		i = 0;

	float
		height,
		width;
		
	height = new_height;

	width = new_width;

	while (i < global_options.number_of_graphics_card_resolutions)
	{
		if (	(width == global_options.graphics_card_resolutions[i].width) &&
				(height == global_options.graphics_card_resolutions[i].height) )
		{
			if (i < ( global_options.number_of_graphics_card_resolutions - 1 ) )
			{
				new_width = global_options.graphics_card_resolutions[i + 1].width;

				new_height = global_options.graphics_card_resolutions[i + 1].height;
			}
			else
			{
				new_width = global_options.graphics_card_resolutions[0].width;

				new_height = global_options.graphics_card_resolutions[0].height;
			}

			break;
		}

		i++;
	}

	sprintf (text, "%.0fx%.0f", new_width, new_height);

	set_ui_object_text (obj, text);

	// don't leave text selected

	set_toggle_button_off (obj);

	// modify "accept" button

	if ( (new_width != global_options.visual_screen_width) || (new_height != global_options.visual_screen_height) )
	{
		set_ui_object_drawable (screen_accept_button, TRUE);
	}
	else
	{
		set_ui_object_drawable (screen_accept_button, FALSE);
	}
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_screen_accept_button (ui_object *obj, void *arg)
{
	
	if ( (new_width != global_options.visual_screen_width) || (new_height != global_options.visual_screen_height) )
	{
		set_3d_resolutions (new_width, new_height);

		ddraw_change_display_resolution ( ( int ) new_width, ( int ) new_height, full_screen_colourdepth );

		// don't leave text selected

		set_toggle_button_off (obj);

		set_ui_object_drawable (screen_accept_button, FALSE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
