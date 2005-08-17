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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

#define FILENAME_MAX_LENGTH	30

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void build_save_file_list (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

session_list_data_type
	*current_session;

ui_object
	*save_file_list_area,
	*save_file_list,
	*save_text_area,
	*save_filename_input,
	*save_current_filename,
	*save_game_confirm_button;

static ui_object
	*page_back_button;

static char
	full_filename [512];
				
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void show_save_page (ui_object *obj)
{
	//
	// Build Existing Filenames List
	//
	
	build_save_file_list ();

	//
	// Set up text areas
	//
	
	current_session = get_current_game_session();
		
	display_campaign_page (CAMPAIGN_PAGE_SAVE, ENTITY_INDEX_DONT_CARE, TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_campaign_screen_save_page_objects (void)
{
	set_ui_object_drawable (save_filename_input, FALSE);

	set_ui_object_state (save_filename_input, UI_OBJECT_STATE_OFF);

	set_ui_object_text (save_filename_input, "");

	set_ui_object_text (save_current_filename, "");

	set_ui_object_drawable (save_current_filename, TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void save_session (ui_object *obj, void *arg)
{
	const char
		*filename;

	ASSERT (get_current_game_session ());

	ASSERT (get_session_entity ());

	filename = get_ui_object_text (save_current_filename);

	if (filename)
	{
		if (strlen (filename) > 0)
		{
			store_session (current_session, filename);
		}
	}

	pop_campaign_history (NULL, NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int valid_filename_symbol (char c)
{
	if (c >= 128)
	{
		return FALSE;
	}

	//
	// Letters or digits...
	//
	
	if (isalnum (c))
	{
		return TRUE;
	}
	
	//
	// Other valid special chars...
	//

	switch (c)
	{
		case ' ':
		case '-':
		case '_':
		case '!':
		case '(':
		case ')':
		{
			return TRUE;
		}
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void parse_filename (char *text, int max_length)
{
	char
		*kb,
		*pm,
		*parsed_text;

	int
		length;

	ASSERT (text);

	ASSERT (max_length > 0);

	parsed_text = malloc_fast_mem (strlen (text) + 1);

	pm = parsed_text;

	kb = text;

	length = 0;

	while ((*kb) && (length < max_length))
	{
		if (valid_filename_symbol (*kb))
		{
			*pm = *kb;

			pm ++;

			length ++;
		}

		kb ++;
	}

	//
	// terminate new string
	//

	*pm = '\0';	

	//
	// copy text back to original location
	//

	strcpy (text, parsed_text);

	// Casm 16AUG05 Fixed memory leak
	free_mem ( parsed_text );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void filename_input_function ( ui_object *obj, void *arg )
{
	const char
		*text;
	char *
		copy;
		
	text = get_ui_object_text (save_filename_input);

	if (text)
	{
		if (strlen (text) > 0)
		{
			copy = malloc_fast_memory ( strlen ( text ) + 1 );
			strcpy ( copy, text );

			parse_filename (copy, FILENAME_MAX_LENGTH);

			set_ui_object_text (save_current_filename, copy);

			free_mem ( copy );
		}
	}

	set_ui_object_drawable (save_current_filename, TRUE);

	set_ui_object_drawable (save_filename_input, FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void save_game_function (ui_object *obj, void *arg)
{
	const char
		*text;
				
	#if DEBUG_MODULE

	debug_filtered_log("Filename query");

	#endif

	text = get_ui_object_text (save_current_filename);

	if (text)
	{
		if (strlen (text) > 0)
		{
			strcpy (full_filename, current_session->data_path);
		
			strcat (full_filename, "\\Campaign\\");

			strcat (full_filename, text);
				
			strcat (full_filename, ".sav");

			if (file_exist (full_filename))
			{
				save_session (obj, arg);
			}
			else
			{
				save_session (obj, arg);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void save_enter_filename_function (ui_object *obj, void *arg)
{
	set_ui_object_text (save_filename_input, get_ui_object_text (save_current_filename));

	set_ui_object_state (save_filename_input, UI_OBJECT_STATE_ON);

	set_ui_object_drawable (save_current_filename, FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void build_save_file_list (void)
{
	session_list_data_type
		*game_session;

	directory_file_list
		*directory_listing;

	ui_object
		*new_item;

	int
		valid_file;

	char
		*p,
		filename [256],
		extension [8];

	ui_object_destroy_list_items (save_file_list);

	game_session = get_current_game_session ();

	ASSERT (game_session);

	sprintf (full_filename, "%s\\%s\\*.", game_session->data_path, game_session->campaign_directory);

	sprintf (extension, "%s", game_type_extensions [get_game_type ()]);

	extension [2] = extension [1];
	extension [1] = extension [0];
	extension [0] = 'S';

	strcat (full_filename, extension);

	directory_listing = get_first_directory_file (full_filename);

	if (directory_listing)
	{
		valid_file = TRUE;

		while (valid_file)
		{
			if (get_directory_file_type (directory_listing) == DIRECTORY_FILE_TYPE_FILE)
			{
				sprintf (filename, get_directory_file_filename (directory_listing));

				p = strchr (filename, '.');

				if (p)
				{
					*p = '\0';
				}

				new_item = add_to_pop_up_list (filename, save_file_list, NULL, ENTITY_INDEX_DONT_CARE, UI_FONT_ARIAL_16, ui_ingame_live_text_colour);

				set_ingame_ui_object_mouse_over_properties (new_item);
			}

			valid_file = get_next_directory_file (directory_listing);
		}

		destroy_directory_file_list (directory_listing);
	}

	resize_pop_up_list (save_file_list);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_save_file_list (ui_object *obj, void *arg)
{
	const char
		*text;
	char *
		copy;
		
	text = get_ui_object_text (obj);

	if (text)
	{
		if (strlen (text) > 0)
		{
			copy = malloc_fast_memory ( strlen ( text ) + 1 );
			strcpy ( copy, text );

			parse_filename (copy, FILENAME_MAX_LENGTH);

			set_ui_object_text (save_current_filename, copy);

			free_mem ( copy );
		}
	}

	set_ui_object_drawable (save_current_filename, TRUE);

	set_ui_object_drawable (save_filename_input, FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_save_page_objects (ui_object *obj, void *arg)
{
	const char
		*text;

	set_ui_object_drawable (page_back_button, get_campaign_history_valid ());

	//
	// Only display save button if valid filename
	//

	set_ui_object_drawable (save_game_confirm_button, FALSE);

	text = get_ui_object_text (save_current_filename);

	if (text)
	{
		if (strlen (text) > 0)
		{
			set_ui_object_drawable (save_game_confirm_button, TRUE);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void define_campaign_screen_save_page_objects (void)
{
	float
		x1,
		y1,
		x2,
		y2;

	ui_object
		*page;

	char
		string [256];

	/////////////////////////////////////////////////////////////////
	// Main Page Area
	/////////////////////////////////////////////////////////////////

	x1 = CAMPAIGN_INSET_PAGE_X1;
	y1 = CAMPAIGN_INSET_PAGE_Y1;
	x2 = CAMPAIGN_INSET_PAGE_X2;
	y2 = CAMPAIGN_INSET_PAGE_Y2;

	campaign_page [CAMPAIGN_PAGE_SAVE] = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (campaign_screen),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_CENTRE_TOP),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_14),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_DRAWABLE (FALSE),
			UI_ATTR_DRAW_FUNCTION (update_save_page_objects),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	page = campaign_page [CAMPAIGN_PAGE_SAVE];

	/////////////////////////////////////////////////////////////////
	// Target List Area

	x1 = 0.057;
	y1 = 0.152;
	x2 = 0.931;
	y2 = 0.625;

	save_file_list_area = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_VSLIDER (0, 300, 12),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	set_common_slider_graphics (save_file_list_area);

	// List Box

	x1 = 0.0;
	y1 = 0.0;
	x2 = 0.95;
	y2 = 1.0;

	save_file_list = create_ui_object
				(
					UI_TYPE_LIST_BOX,
					UI_ATTR_PARENT (save_file_list_area),
					UI_ATTR_VIRTUAL_POSITION (x1, y1),
					UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
					UI_ATTR_CLEAR (TRUE),
					UI_ATTR_FUNCTION (notify_save_file_list),
					UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
					UI_ATTR_ITEM_NUMBER (ENTITY_INDEX_DONT_CARE),
					UI_ATTR_END
				);

	/////////////////////////////////////////////////////////////////
	// Save Dialog Box

	x1 = 0.123;
	y1 = 0.762;
	x2 = 0.876;
	y2 = 0.834;

	save_text_area = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXTURE_GRAPHIC (create_texture_graphic ("graphics\\ui\\cohokum\\map\\msgbar.psd")),
				UI_ATTR_FUNCTION (save_enter_filename_function),
				UI_ATTR_END
			);

	/////////////////////////////////////////////////////////////////
	// Filename Input

	x1 = 0.04;
	y1 = 0.18;
	x2 = 1.0;
	y2 = 1.0;

   save_filename_input = create_ui_object
            (
               UI_TYPE_INPUT,
               UI_ATTR_PARENT (save_text_area),
					UI_ATTR_VIRTUAL_POSITION (x1, y1),
					UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
					UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
					UI_ATTR_FONT_COLOUR (ui_ingame_selected_text_colour.r, ui_ingame_selected_text_colour.g, ui_ingame_selected_text_colour.b, ui_ingame_selected_text_colour.a),
					UI_ATTR_FUNCTION (filename_input_function),
					UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
					UI_ATTR_CLEAR (TRUE),
               UI_ATTR_END
            );

	x1 = 0.04;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 1.0;

   save_current_filename = create_ui_object
            (
               UI_TYPE_AREA,
               UI_ATTR_PARENT (save_text_area),
					UI_ATTR_VIRTUAL_POSITION (x1, y1),
					UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
					UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
					UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
					UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
					UI_ATTR_TEXT (""),
					UI_ATTR_CLEAR (TRUE),
					UI_ATTR_FUNCTION (save_enter_filename_function),
               UI_ATTR_END
            );

	/////////////////////////////////////////////////////////////////
	// Enter Filename Text

	x1 = 0.100;
	y1 = 0.720;
	x2 = 0.876;
	y2 = 0.756;

	sprintf (string, "%s:", get_trans ("ENTER_SAVE_GAME_FILENAME"));

	create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
				UI_ATTR_TEXT (string),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	/////////////////////////////////////////////////////////////////
	// Confirm Button

	x1 = 0.320;
	y1 = 0.834;
	x2 = 0.672;
	y2 = 0.884;

	save_game_confirm_button = create_ui_object
			(
				UI_TYPE_BUTTON,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (get_trans ("Save")),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
				UI_ATTR_FUNCTION (save_game_function),
				UI_ATTR_TEXTURE_GRAPHIC (create_texture_graphic ("graphics\\ui\\cohokum\\map\\cbtn.psd")),
				UI_ATTR_END
			);

	set_ingame_ui_object_mouse_over_properties (save_game_confirm_button);

	/////////////////////////////////////////////////////////////////
	// "Divider" graphics

	x1 = 0.022;
	y1 = 0.109;
	x2 = 0.971;
	y2 = 0.133;

	create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXTURE_GRAPHIC (common_divider_graphic),
				UI_ATTR_END
			);

	x1 = 0.022;
	y1 = 0.644;
	x2 = 0.971;
	y2 = 0.667;

	create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXTURE_GRAPHIC (common_divider_graphic),
				UI_ATTR_END
			);

	/////////////////////////////////////////////////////////////////
	// BACK button

	define_campaign_page_back_button (page, &page_back_button);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

