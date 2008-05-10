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

#include "ai/highlevl/highlevl.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ui_object
	*campaign_screen,
	*campaign_page [NUM_CAMPAIGN_PAGES];

static ui_object
	*campaign_full_screen_mask_area,
	*campaign_dialog_area,
	*campaign_complete_area,
	*campaign_complete_side,
	*campaign_complete_reason,
	*campaign_quit_mission_area,
	*campaign_quit_campaign_area;

static texture_graphic
	*blue_campaign_complete_graphic = NULL,
	*red_campaign_complete_graphic = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_campaign_screen (void);

static void quit_mission_set_events (void);

static void quit_campaign_set_events (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_main_campaign_screen (void)
{
	#if !DEMO_VERSION

	initialise_map_data ();

	initialise_campaign_screen_sort_objects ();

	initialise_campaign_screen_menu_objects ();

	initialise_campaign_screen_list_objects ();

	initialise_campaign_screen_info_objects ();

	initialise_campaign_screen_selection_objects ();

	initialise_campaign_screen_base_page_objects ();

	initialise_campaign_screen_briefing_page_objects ();

	initialise_campaign_screen_debriefing_page_objects ();

	initialise_campaign_screen_group_page_objects ();

	initialise_campaign_screen_map_page_objects ();

	initialise_campaign_screen_stats_page_objects ();

	initialise_campaign_screen_log_page_objects ();

	initialise_campaign_screen_chat_page_objects ();

	initialise_campaign_screen_save_page_objects ();

	initialise_campaign_screen_weapon_loading_page_objects ();

	initialise_campaign_screen_full_screen_map_objects ();

	initialise_campaign_history ();

	set_ui_object_drawable (campaign_full_screen_mask_area, FALSE);

	set_ui_object_drawable (campaign_dialog_area, FALSE);

	set_ui_object_drawable (campaign_complete_area, FALSE);

	set_ui_object_drawable (campaign_quit_mission_area, FALSE);

	set_ui_object_drawable (campaign_quit_campaign_area, FALSE);

	show_map_page ();

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_campaign_screen (void)
{
	update_campaign_screen_list_objects ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_campaign_screen_entered (ui_object *obj, void *arg)
{
	if (get_ui_object_drawable (obj))
	{
		//
		// Screen has just been pushed
		//

		set_ui_mouse_over_entity (NULL);
	}

	update_campaign_screen ();

	set_mouse_graphic_on ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void campaign_screen_draw_function (ui_object *obj, void *arg)
{
	//
	// Initialise
	//

	set_last_drawn_map_object (NULL);

	//
	// General
	//
	
	ingame_screen_draw_function (obj, arg);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void display_campaign_page (campaign_pages page, int index, int add_to_history)
{
	#if !DEMO_VERSION

	int
		loop,
		current_page,
		current_index;

	//
	// Store history
	//
	
	if (add_to_history)
	{
		current_page = -1;
			
		for (loop = 0; loop < NUM_CAMPAIGN_PAGES; loop ++)
		{
			if (get_ui_object_drawable (campaign_page [loop]))
			{
				current_page = loop;
	
				break;
			}
		}
	
		if (current_page != -1)
		{
			current_index = get_ui_object_item_number (campaign_page [current_page]);
			
			if ((page != current_page) || (index != current_index))
			{
				push_campaign_history (current_page, current_index);
			}
		}
	}

	//
	// Display new page
	//

	for (loop = 0; loop < NUM_CAMPAIGN_PAGES; loop ++)
	{
		if (page == loop)
		{
			//TEMP - DEBUG
			#ifdef DEBUG
			if ((page == CAMPAIGN_PAGE_GROUP) && (index == ENTITY_INDEX_DONT_CARE))
			{
				//
				// IF THIS HAPPENS - TELL ME (DAVE L)
				//
				
				breakout (NULL);
			}				
			#endif
			//

			set_ui_object_drawable (campaign_page [loop], TRUE);

			set_ui_object_item_number (campaign_page [loop], index);
		}
		else
		{
			set_ui_object_drawable (campaign_page [loop], FALSE);
		}
	}

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

campaign_pages get_current_campaign_page (void)
{
	int
		loop,
		current_page;

	current_page = -1;
			
	for (loop = 0; loop < NUM_CAMPAIGN_PAGES; loop ++)
	{
		if (get_ui_object_drawable (campaign_page [loop]))
		{
			current_page = loop;
	
			break;
		}
	}

	return current_page;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_campaign_complete_button (ui_object *obj, void *arg)
{
	set_ui_object_drawable (campaign_full_screen_mask_area, FALSE);

	set_ui_object_drawable (campaign_dialog_area, FALSE);

	set_ui_object_drawable (campaign_complete_area, FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// QUIT MISSION
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void campaign_cancel_quit_mission (event *ev)
{
	set_ui_object_drawable (campaign_full_screen_mask_area, FALSE);

	set_ui_object_drawable (campaign_dialog_area, FALSE);

	set_ui_object_drawable (campaign_quit_mission_area, FALSE);

	pop_event (quit_mission_set_events);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_campaign_cancel_quit_mission_button (ui_object *obj, void *arg)
{
	campaign_cancel_quit_mission (NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void campaign_accept_quit_mission (event *ev)
{
	entity
		*task;

	campaign_cancel_quit_mission (ev);

	if (get_gunship_entity ())
	{
		pop_event (ingame_screen_set_events);
	
		set_gunship_entity (NULL);
	
		push_event (ingame_screen_set_events, "ingame screen events");

		//
		// Force Debrief Page
		//
		
		task = get_player_task (NULL);

		if (task)
		{
			if (get_local_entity_int_value (task, INT_TYPE_TASK_STATE) == TASK_STATE_COMPLETED)
			{
				show_debriefing_page (task, TRUE, FALSE);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_campaign_accept_quit_mission_button (ui_object *obj, void *arg)
{
	campaign_accept_quit_mission (NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void quit_mission_set_events (void)
{
	set_event (DIK_S, MODIFIER_NONE, KEY_STATE_DOWN, campaign_accept_quit_mission);
	set_event (DIK_Y, MODIFIER_NONE, KEY_STATE_DOWN, campaign_accept_quit_mission);
	set_event (DIK_J, MODIFIER_NONE, KEY_STATE_DOWN, campaign_accept_quit_mission);
	set_event (DIK_O, MODIFIER_NONE, KEY_STATE_DOWN, campaign_accept_quit_mission);
	set_event (DIK_T, MODIFIER_NONE, KEY_STATE_DOWN, campaign_accept_quit_mission);

	set_event (DIK_N, MODIFIER_NONE, KEY_STATE_DOWN, campaign_cancel_quit_mission);

	set_event (DIK_X, MODIFIER_LEFT_CONTROL, KEY_STATE_UP, exit_apache_havoc);

	set_event (MOUSE_LEFT_BUTTON, MODIFIER_NONE, BUTTON_STATE_EITHER, ui_left_mouse_button);
	set_event (MOUSE_LEFT_BUTTON, MODIFIER_LEFT_SHIFT, BUTTON_STATE_EITHER, ui_left_mouse_button);

	set_event (MOUSE_RIGHT_BUTTON, MODIFIER_NONE, BUTTON_STATE_EITHER, ui_right_mouse_button);
	set_event (MOUSE_RIGHT_BUTTON, MODIFIER_LEFT_SHIFT, BUTTON_STATE_EITHER, ui_right_mouse_button);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup_campaign_quit_mission_dialog (void)
{
	minimize_all_map_objects ();

	set_ui_object_drawable (campaign_full_screen_mask_area, TRUE);

	set_ui_object_drawable (campaign_dialog_area, TRUE);

	set_ui_object_drawable (campaign_quit_mission_area, TRUE);

	push_event (quit_mission_set_events, "quit mission events");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// QUIT CAMPAIGN
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void campaign_cancel_quit_campaign (event *ev)
{
	set_ui_object_drawable (campaign_full_screen_mask_area, FALSE);

	set_ui_object_drawable (campaign_dialog_area, FALSE);

	set_ui_object_drawable (campaign_quit_campaign_area, FALSE);

	pop_event (quit_campaign_set_events);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_campaign_cancel_quit_campaign_button (ui_object *obj, void *arg)
{
	campaign_cancel_quit_campaign (NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void campaign_accept_quit_campaign (event *ev)
{
	campaign_cancel_quit_campaign (ev);

	//
	// Make all pages not drawable, otherwise last page will be added to history next time a game is started.
	//
	
	display_campaign_page (-1, ENTITY_INDEX_DONT_CARE, FALSE);

	//
	// Quit
	//
	
	player_quit_session (NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_campaign_accept_quit_campaign_button (ui_object *obj, void *arg)
{
	campaign_accept_quit_campaign (NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void quit_campaign_set_events (void)
{
	set_event (DIK_S, MODIFIER_NONE, KEY_STATE_DOWN, campaign_accept_quit_campaign);
	set_event (DIK_Y, MODIFIER_NONE, KEY_STATE_DOWN, campaign_accept_quit_campaign);
	set_event (DIK_J, MODIFIER_NONE, KEY_STATE_DOWN, campaign_accept_quit_campaign);
	set_event (DIK_O, MODIFIER_NONE, KEY_STATE_DOWN, campaign_accept_quit_campaign);
	set_event (DIK_T, MODIFIER_NONE, KEY_STATE_DOWN, campaign_accept_quit_campaign);

	set_event (DIK_N, MODIFIER_NONE, KEY_STATE_DOWN, campaign_cancel_quit_campaign);

	set_event (DIK_X, MODIFIER_LEFT_CONTROL, KEY_STATE_UP, exit_apache_havoc);

	set_event (MOUSE_LEFT_BUTTON, MODIFIER_NONE, BUTTON_STATE_EITHER, ui_left_mouse_button);
	set_event (MOUSE_LEFT_BUTTON, MODIFIER_LEFT_SHIFT, BUTTON_STATE_EITHER, ui_left_mouse_button);

	set_event (MOUSE_RIGHT_BUTTON, MODIFIER_NONE, BUTTON_STATE_EITHER, ui_right_mouse_button);
	set_event (MOUSE_RIGHT_BUTTON, MODIFIER_LEFT_SHIFT, BUTTON_STATE_EITHER, ui_right_mouse_button);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup_campaign_quit_campaign_dialog (void)
{
	minimize_all_map_objects ();

	set_ui_object_drawable (campaign_full_screen_mask_area, TRUE);

	set_ui_object_drawable (campaign_dialog_area, TRUE);

	set_ui_object_drawable (campaign_quit_campaign_area, TRUE);

	push_event (quit_campaign_set_events, "quit campaign events");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_campaign_screen (void)
{
	ui_object
		*temp;

	float
		x1,
		y1,
		x2,
		y2,
		x_size,
		y_size;

	char
		string [256];

	blue_campaign_complete_graphic = create_texture_graphic ( "graphics\\ui\\cohokum\\map\\bvictory.psd" );
	red_campaign_complete_graphic = create_texture_graphic ( "graphics\\ui\\cohokum\\map\\rvictory.psd" );

	initialise_campaign_screen_message_responses ();

	x_size = 1.0;
	y_size = 1.0;

	/////////////////////////////////////////////////////////////////

   campaign_screen = create_ui_object
            (
               UI_TYPE_SCREEN,
               UI_ATTR_VIRTUAL_POSITION (0, 0),
               UI_ATTR_VIRTUAL_SIZE (x_size, y_size),
					UI_ATTR_FUNCTION (notify_campaign_screen_entered),
					UI_ATTR_DRAW_FUNCTION (campaign_screen_draw_function),
					UI_ATTR_CLEAR (TRUE),
               UI_ATTR_END
            );

	/////////////////////////////////////////////////////////////////
	// ORDER IS CRITICAL.....

	define_campaign_screen_briefing_page_objects ();

	define_campaign_screen_debriefing_page_objects ();

	/////////////////////////////////////////////////////////////////

	define_campaign_screen_group_page_objects ();

	/////////////////////////////////////////////////////////////////

	define_campaign_screen_base_page_objects ();

	/////////////////////////////////////////////////////////////////

	define_campaign_screen_list_objects ();

	/////////////////////////////////////////////////////////////////

	define_campaign_screen_map_page_objects ();

	/////////////////////////////////////////////////////////////////

	define_campaign_screen_stats_page_objects ();

	/////////////////////////////////////////////////////////////////

	define_campaign_screen_save_page_objects ();

	/////////////////////////////////////////////////////////////////

	define_campaign_screen_chat_page_objects ();

	/////////////////////////////////////////////////////////////////

	define_campaign_screen_log_page_objects ();

	/////////////////////////////////////////////////////////////////

	define_campaign_screen_weapon_loading_page_objects ();

	/////////////////////////////////////////////////////////////////

	define_campaign_screen_menu_objects ();

	define_campaign_screen_selection_objects ();

	define_campaign_screen_info_objects ();

	define_campaign_screen_full_screen_map_objects ();

	/////////////////////////////////////////////////////////////////

	x1 = 0.0;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 1.0;

	campaign_full_screen_mask_area = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (campaign_screen),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXTURE_GRAPHIC (common_grey_alpha_mask),
			UI_ATTR_END
		);

	x1 = CAMPAIGN_INSET_PAGE_X1;
	y1 = CAMPAIGN_INSET_PAGE_Y1;
	x2 = CAMPAIGN_INSET_PAGE_X2;
	y2 = CAMPAIGN_INSET_PAGE_Y2;

	campaign_dialog_area = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (campaign_full_screen_mask_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXTURE_GRAPHIC (common_black_alpha_mask),
			UI_ATTR_END
		);

	/////////////////////////////////////////////////////////////////
	//
	// Campaign Complete
	//
	/////////////////////////////////////////////////////////////////

	x1 = 0.0;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 1.0;

	campaign_complete_area = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (campaign_dialog_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_END
		);

	x1 = 0.0;
	y1 = 0.59;
	x2 = 1.0;
	y2 = 0.66;

	create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (campaign_complete_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT (get_trans ("Campaign Over")),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_22),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	x1 = 0.0;
	y1 = 0.665;
	x2 = 1.0;
	y2 = 0.726;

	campaign_complete_side = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (campaign_complete_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_22),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	x1 = 0.0;
	y1 = 0.760;
	x2 = 1.0;
	y2 = 0.820;

	campaign_complete_reason = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (campaign_complete_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	x1 = 0.323;
	y1 = 0.869;
	x2 = 0.674;
	y2 = 0.941;

	create_ui_object
		(
			UI_TYPE_BUTTON,
			UI_ATTR_PARENT (campaign_complete_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT (get_trans ("UI_OK")),
			UI_ATTR_FUNCTION (notify_campaign_complete_button),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_18),
			UI_ATTR_FONT_COLOUR (ui_ingame_live_text_colour.r, ui_ingame_live_text_colour.g, ui_ingame_live_text_colour.b, ui_ingame_live_text_colour.a),
			UI_ATTR_HIGHLIGHTED_FONT_COLOUR (ui_ingame_highlight_text_colour.r, ui_ingame_highlight_text_colour.g, ui_ingame_highlight_text_colour.b, ui_ingame_highlight_text_colour.a),
			UI_ATTR_SELECTED_FONT_COLOUR (ui_ingame_selected_text_colour.r, ui_ingame_selected_text_colour.g, ui_ingame_selected_text_colour.b, ui_ingame_selected_text_colour.a),
			UI_ATTR_HIGHLIGHTABLE (TRUE),
			UI_ATTR_TEXTURE_GRAPHIC (create_texture_graphic ("graphics\\ui\\cohokum\\map\\okaybtn.psd")),
			UI_ATTR_END
		);

	/////////////////////////////////////////////////////////////////
	//
	// Campaign Quit Mission
	//
	/////////////////////////////////////////////////////////////////

	x1 = 0.257;
	y1 = 0.427;
	x2 = 0.74;
	y2 = 0.498;

	campaign_quit_mission_area = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (campaign_dialog_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXTURE_GRAPHIC (create_texture_graphic ("graphics\\ui\\cohokum\\map\\quitmisn.psd")),
			UI_ATTR_END
		);

	x1 = 0.1;
	y1 = 0.0;
	x2 = 0.6;
	y2 = 1.0;

	sprintf (string, "%s?", get_trans ("QUIT MISSION"));
	
	create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (campaign_quit_mission_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT (string),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
			UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	x1 = 0.9;
	y1 = 0.0;
	x2 = 0.95;
	y2 = 1.0;

	temp = create_ui_object
		(
			UI_TYPE_BUTTON,
			UI_ATTR_PARENT (campaign_quit_mission_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT (get_trans ("No")),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
			UI_ATTR_FONT_COLOUR (ui_ingame_live_text_colour.r, ui_ingame_live_text_colour.g, ui_ingame_live_text_colour.b, ui_ingame_live_text_colour.a),
			UI_ATTR_HIGHLIGHTED_FONT_COLOUR (ui_ingame_highlight_text_colour.r, ui_ingame_highlight_text_colour.g, ui_ingame_highlight_text_colour.b, ui_ingame_highlight_text_colour.a),
			UI_ATTR_SELECTED_FONT_COLOUR (ui_ingame_selected_text_colour.r, ui_ingame_selected_text_colour.g, ui_ingame_selected_text_colour.b, ui_ingame_selected_text_colour.a),
			UI_ATTR_HIGHLIGHTABLE (TRUE),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_FUNCTION (notify_campaign_cancel_quit_mission_button),
			UI_ATTR_END
		);

	process_ingame_text_object_size (temp, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);


	x1 = get_ui_object_x_end (temp);

	x2 = get_ui_object_x_end (temp) - 0.05;

//	x1 = 0.6;
	y1 = 0.0;
//	x2 = 0.88;
	y2 = 1.0;

	temp = create_ui_object
		(
			UI_TYPE_BUTTON,
			UI_ATTR_PARENT (campaign_quit_mission_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT (get_trans ("Yes")),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
			UI_ATTR_FONT_COLOUR (ui_ingame_live_text_colour.r, ui_ingame_live_text_colour.g, ui_ingame_live_text_colour.b, ui_ingame_live_text_colour.a),
			UI_ATTR_HIGHLIGHTED_FONT_COLOUR (ui_ingame_highlight_text_colour.r, ui_ingame_highlight_text_colour.g, ui_ingame_highlight_text_colour.b, ui_ingame_highlight_text_colour.a),
			UI_ATTR_SELECTED_FONT_COLOUR (ui_ingame_selected_text_colour.r, ui_ingame_selected_text_colour.g, ui_ingame_selected_text_colour.b, ui_ingame_selected_text_colour.a),
			UI_ATTR_HIGHLIGHTABLE (TRUE),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_FUNCTION (notify_campaign_accept_quit_mission_button),
			UI_ATTR_END
		);

	process_ingame_text_object_size (temp, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	/////////////////////////////////////////////////////////////////
	//
	// Campaign Quit Campaign
	//
	/////////////////////////////////////////////////////////////////

	x1 = 0.257;
	y1 = 0.303;
	x2 = 0.74;
	y2 = 0.612;

	campaign_quit_campaign_area = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (campaign_dialog_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXTURE_GRAPHIC (create_texture_graphic ("graphics\\ui\\cohokum\\map\\quitcamp.psd")),
			UI_ATTR_END
		);

	x1 = 0.1;
	y1 = 0.65;
	x2 = 0.6;
	y2 = 1.0;

	sprintf (string, "%s?", get_trans ("Quit Campaign"));
	
	create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (campaign_quit_campaign_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT (string),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
			UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	x1 = 0.9;
	y1 = 0.65;
	x2 = 0.95;
	y2 = 1.0;

	temp = create_ui_object
		(
			UI_TYPE_BUTTON,
			UI_ATTR_PARENT (campaign_quit_campaign_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT (get_trans ("No")),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
			UI_ATTR_FONT_COLOUR (ui_ingame_live_text_colour.r, ui_ingame_live_text_colour.g, ui_ingame_live_text_colour.b, ui_ingame_live_text_colour.a),
			UI_ATTR_HIGHLIGHTED_FONT_COLOUR (ui_ingame_highlight_text_colour.r, ui_ingame_highlight_text_colour.g, ui_ingame_highlight_text_colour.b, ui_ingame_highlight_text_colour.a),
			UI_ATTR_SELECTED_FONT_COLOUR (ui_ingame_selected_text_colour.r, ui_ingame_selected_text_colour.g, ui_ingame_selected_text_colour.b, ui_ingame_selected_text_colour.a),
			UI_ATTR_HIGHLIGHTABLE (TRUE),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_FUNCTION (notify_campaign_cancel_quit_campaign_button),
			UI_ATTR_END
		);

	process_ingame_text_object_size (temp, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);


	x1 = get_ui_object_x_end (temp);

	x2 = get_ui_object_x_end (temp) - 0.05;

//	x1 = 0.6;
	y1 = 0.65;
//	x2 = 0.88;
	y2 = 1.0;

	temp = create_ui_object
		(
			UI_TYPE_BUTTON,
			UI_ATTR_PARENT (campaign_quit_campaign_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT (get_trans ("Yes")),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
			UI_ATTR_FONT_COLOUR (ui_ingame_live_text_colour.r, ui_ingame_live_text_colour.g, ui_ingame_live_text_colour.b, ui_ingame_live_text_colour.a),
			UI_ATTR_HIGHLIGHTED_FONT_COLOUR (ui_ingame_highlight_text_colour.r, ui_ingame_highlight_text_colour.g, ui_ingame_highlight_text_colour.b, ui_ingame_highlight_text_colour.a),
			UI_ATTR_SELECTED_FONT_COLOUR (ui_ingame_selected_text_colour.r, ui_ingame_selected_text_colour.g, ui_ingame_selected_text_colour.b, ui_ingame_selected_text_colour.a),
			UI_ATTR_HIGHLIGHTABLE (TRUE),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_FUNCTION (notify_campaign_accept_quit_campaign_button),
			UI_ATTR_END
		);

	process_ingame_text_object_size (temp, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup_campaign_completed_dialog (entity_sides side, campaign_completed_types complete)
{
	entity_sides
		this_side;

	//
	// Display campaign over message
	//

	set_ui_object_drawable (campaign_full_screen_mask_area, TRUE);

	set_ui_object_drawable (campaign_dialog_area, TRUE);

	switch (side)
	{
		case ENTITY_SIDE_BLUE_FORCE:
		{
			set_ui_object_texture_graphic (campaign_complete_area, blue_campaign_complete_graphic);

			break;
		}
		case ENTITY_SIDE_RED_FORCE:
		{
			set_ui_object_texture_graphic (campaign_complete_area, red_campaign_complete_graphic);

			break;
		}
		default:
		{
			debug_fatal ("CAMPAIGN: Invalid Side for campaign complete (%d)", side);
		}
	}

	this_side = get_local_entity_int_value (get_pilot_entity (), INT_TYPE_SIDE);

	if (side == this_side)
	{
		set_ui_object_text (campaign_complete_side, get_trans ("Allied Victory"));

		switch (complete)
		{
			case CAMPAIGN_COMPLETED_OBJECTIVES:
			{
				set_ui_object_text (campaign_complete_reason, get_trans ("Key Objectives Achieved"));

				break;
			}
			case CAMPAIGN_COMPLETED_VALID_GUNSHIPS:
			{
				set_ui_object_text (campaign_complete_reason, get_trans ("Enemy Air Forces Seriously Depleted"));

				break;
			}
			default:
			{
				set_ui_object_text (campaign_complete_reason, "");

				break;
			}
		}
	}
	else
	{
		set_ui_object_text (campaign_complete_side, get_trans ("Enemy Victory"));

		switch (complete)
		{
			case CAMPAIGN_COMPLETED_OBJECTIVES:
			{
				set_ui_object_text (campaign_complete_reason, get_trans ("Key Allied Installations Lost"));

				break;
			}
			case CAMPAIGN_COMPLETED_VALID_GUNSHIPS:
			{
				set_ui_object_text (campaign_complete_reason, get_trans ("Insufficient Resources Left For Conflict"));

				break;
			}
			default:
			{
				set_ui_object_text (campaign_complete_reason, "");

				break;
			}
		}
	}

	minimize_all_map_objects ();

	set_ui_object_drawable (campaign_complete_area, TRUE);

	ui_set_origin (0.0, 0.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void campaign_completed (entity_sides side, campaign_completed_types complete)
{

	player_log_type
		*log;

	if (get_comms_model () == COMMS_MODEL_SERVER)
	{
		ai_log ("###############################################");
		ai_log ("###############################################");
		ai_log ("CAMPAIGN WON BY %s SIDE", entity_side_short_names [side]);
		ai_log ("###############################################");
		ai_log ("###############################################");
	
		//
		// Transmit message to clients
		//

		transmit_entity_comms_message (ENTITY_COMMS_CAMPAIGN_COMPLETED, get_session_entity (), side, complete);

		//
		// AWARD CAMPAIGN COMPLETED MEDAL
		//

		log = get_current_player_log ();

		ASSERT (log);

		if (get_game_type () == GAME_TYPE_CAMPAIGN)
		{
			if (side == get_local_entity_int_value (get_pilot_entity (), INT_TYPE_SIDE))
			{
				award_campaign_medal (side, get_local_entity_int_value (get_session_entity (), INT_TYPE_CAMPAIGN_MEDAL));
	
				inc_player_log_successful_tours (side, log);
			}
			else
			{
				inc_player_log_failed_tours (side, log);
			}
		}
	}
	
	//
	// Set session state to complete
	//

	ASSERT (get_session_entity ());

	set_local_entity_int_value (get_session_entity (), INT_TYPE_SESSION_COMPLETE, complete);

	setup_campaign_completed_dialog (side, complete);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void campaign_screen_show_external_view_entity (event *ev)
{
	entity
		*en,
		*group;

	//
	// Switch back to campaign screen
	//
			
	if (get_in_flight_game_mode () == IN_FLIGHT_GAME_MODE_SIMULATOR)
	{
		set_in_flight_game_mode (IN_FLIGHT_GAME_MODE_PLANNER);
	}

	if (
			(get_game_type () != GAME_TYPE_CAMPAIGN) &&
			(get_game_type () != GAME_TYPE_SKIRMISH)
		)
	{
		return;
	}

	en = get_external_view_entity ();

	if (!en)
	{
		return;
	}

	group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

	if (!group)
	{
		return;
	}

	ASSERT (get_pilot_entity ());

	if (get_local_entity_int_value (en, INT_TYPE_SIDE) == get_local_entity_int_value (get_pilot_entity (), INT_TYPE_SIDE))
	{
		//
		// Show group page
		//

		show_group_page (group, FALSE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


