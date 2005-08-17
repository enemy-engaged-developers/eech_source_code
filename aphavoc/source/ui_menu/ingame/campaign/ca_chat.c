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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static ui_object
	*chat_window_mode_area,
	*chat_window_area,
	*chat_window_destination_button,
	*chat_window_message_button,
	*chat_text_area,
	*chat_input,
	*chat_current_text,
	*chat_send_button,
	*chat_target_list_area,
	*chat_target_list,
	*chat_message_list_area,
	*chat_message_list,
	*page_back_button;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void build_chat_target_list (void);

static void build_chat_message_list (void);

static int add_message_to_campaign_log (int index);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void show_chat_page (ui_object *obj)
{
	//
	// Build Target List
	//
	
	build_chat_target_list ();

	//
	// Show Previous Messages
	//
	
	build_chat_message_list ();
	
	display_campaign_page (CAMPAIGN_PAGE_CHAT, ENTITY_INDEX_DONT_CARE, TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_campaign_screen_chat_page_objects (void)
{
	//
	// Set Window Mode
	//
	
	set_ui_object_drawable (chat_target_list_area, TRUE);

	set_ui_object_drawable (chat_message_list_area, FALSE);

	set_ui_object_state (chat_window_destination_button, UI_OBJECT_STATE_ON);

	//
	// Set Target to ALL
	//
	
	set_ui_object_item_number (chat_send_button, get_local_entity_safe_index (get_session_entity ()));

	//
	// Clear Text Input Area
	//
	
	set_ui_object_drawable (chat_input, FALSE);

	set_ui_object_text (chat_input, "");

	set_ui_object_state (chat_input, UI_OBJECT_STATE_OFF);

	//
	// Clear Current Text Area
	//
	
	set_ui_object_text (chat_current_text, "");

	set_ui_object_drawable (chat_current_text, TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void chat_enter_message_function (ui_object *obj, void *arg)
{
	set_ui_object_state (chat_input, UI_OBJECT_STATE_ON);

	set_ui_object_drawable (chat_current_text, FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void chat_input_function (ui_object *obj, void *arg)
{
	entity 	// Jabberwock 040213 Chat send after Enter
		*target;
		
	const char
		*text;
		
	text = get_ui_object_text (chat_input);

	if (text)
	{
		if (strlen (text) > 0)
		{
			set_ui_object_text (chat_current_text, get_ui_object_text (chat_input));

			// Jabberwock 040213 Chat send after Enter
			target = get_local_entity_safe_ptr (get_ui_object_item_number (chat_send_button));
		
			if (target)
			{
				send_text_message (get_pilot_entity (), target, MESSAGE_TEXT_PILOT_STRING, text);
			}
			// Jabberwock 040202 ends
		}
	}

	set_ui_object_drawable (chat_current_text, TRUE);

	set_ui_object_drawable (chat_input, FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_send_message (ui_object *obj, void *arg)
{
	entity
		*target;
		
	const char
		*text;
		
	target = get_local_entity_safe_ptr (get_ui_object_item_number (chat_send_button));

	if (target)
	{
		text = get_ui_object_text (chat_current_text);

		if (text)
		{
			if (strlen (text) > 0)
			{
				send_text_message (get_pilot_entity (), target, MESSAGE_TEXT_PILOT_STRING, text);

				return;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_target_list (ui_object *obj, void *arg)
{
	int
		index;
		
	index = get_ui_object_item_number (obj);

	if (index != ENTITY_INDEX_DONT_CARE)
	{
		set_ui_object_item_number (chat_send_button, index);

		build_chat_target_list ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_show_destinations (ui_object *obj, void *arg)
{
	build_chat_target_list ();

	set_ui_object_drawable (chat_target_list_area, TRUE);

	set_ui_object_drawable (chat_message_list_area, FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_show_messages (ui_object *obj, void *arg)
{
	build_chat_message_list ();
	
	set_ui_object_drawable (chat_target_list_area, FALSE);

	set_ui_object_drawable (chat_message_list_area, TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void build_chat_target_list (void)
{
	ui_object
		*new_item;

	entity
		*force,
		*pilot,
		*current_target;

	static char
		s [128];

	current_target = get_local_entity_safe_ptr (get_ui_object_item_number (chat_send_button));

	ui_object_destroy_list_items (chat_target_list);

	sprintf (s, "%s", get_trans ("Side"));

	new_item = add_to_pop_up_list (s, chat_target_list, NULL, ENTITY_INDEX_DONT_CARE, UI_FONT_ARIAL_16, ui_ingame_dead_text_colour);

	//
	// All 
	//

	ASSERT (get_session_entity ());

	sprintf (s, "%s", get_trans ("CHAT_TARGET_ALL"));

	new_item = add_to_pop_up_list (s, chat_target_list, NULL, get_local_entity_safe_index (get_session_entity ()), UI_FONT_ARIAL_16, ui_ingame_live_text_colour);

	set_ingame_ui_object_mouse_over_properties (new_item);

	if (get_session_entity () == current_target)
	{
		set_ui_object_state (new_item, UI_OBJECT_STATE_ON);
	}

	//
	// Sides
	//

	force = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

	while (force)
	{
		sprintf (s, "%s", get_local_entity_string (force, STRING_TYPE_FORCE_NAME));

		new_item = add_to_pop_up_list (s, chat_target_list, NULL, get_local_entity_safe_index (force), UI_FONT_ARIAL_16, ui_ingame_live_text_colour);

		set_ingame_ui_object_mouse_over_properties (new_item);

		if (force == current_target)
		{
			set_ui_object_state (new_item, UI_OBJECT_STATE_ON);
		}

		force = get_local_entity_child_succ (force, LIST_TYPE_FORCE);
	}

	//
	// Sides
	//

	sprintf (s, "%s", get_trans ("UI_PILOTS"));

	new_item = add_to_pop_up_list (s, chat_target_list, NULL, ENTITY_INDEX_DONT_CARE, UI_FONT_ARIAL_16, ui_ingame_dead_text_colour);

	force = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

	while (force)
	{
		pilot = get_local_entity_first_child (force, LIST_TYPE_PILOT);

		while (pilot)
		{
			if (pilot != get_pilot_entity ())
			{
				sprintf (s, "%s", get_local_entity_string (pilot, STRING_TYPE_PILOTS_NAME));
	
				new_item = add_to_pop_up_list (s, chat_target_list, NULL, get_local_entity_safe_index (pilot), UI_FONT_ARIAL_16, ui_ingame_live_text_colour);
	
				set_ingame_ui_object_mouse_over_properties (new_item);
	
				if (pilot == current_target)
				{
					set_ui_object_state (new_item, UI_OBJECT_STATE_ON);
				}
			}
			
			pilot = get_local_entity_child_succ (pilot, LIST_TYPE_PILOT);
		}

		force = get_local_entity_child_succ (force, LIST_TYPE_FORCE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void build_chat_message_list (void)
{
	int
		loop,
		start,
		count;

	//
	// Show Previous Messages
	//
	
	ui_object_destroy_list_items (chat_message_list);

	start = get_message_log_number_of_messages () - 1;

	count = 0;

	for (loop = start; loop >= 0; loop --)
	{
		if (add_message_to_campaign_log (loop))
		{
			count ++;

			if (count > 50)
			{
				break;
			}
		}
	}

	resize_pop_up_list (chat_message_list);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_chat_page_objects (ui_object *obj, void *arg)
{
	set_ui_object_drawable (page_back_button, get_campaign_history_valid ());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_chat_send_button (ui_object *obj, void *arg)
{
	entity
		*current_target;

	rgb_colour
		*col;
		
	static const char
		*text;
	static char
		s [256];

	sprintf (s, "%s: ", get_trans ("SEND TO"));

	current_target = get_local_entity_safe_ptr (get_ui_object_item_number (obj));

	if (current_target)
	{
		switch (get_local_entity_type (current_target))
		{
			case ENTITY_TYPE_SESSION:
			{
				strcat (s, get_trans ("CHAT_TARGET_ALL"));

				break;
			}
			case ENTITY_TYPE_FORCE:
			{
				strcat (s, get_local_entity_string (current_target, STRING_TYPE_FORCE_NAME));

				break;
			}
			case ENTITY_TYPE_PILOT:
			{
				strcat (s, get_local_entity_string (current_target, STRING_TYPE_PILOTS_NAME));

				break;
			}
			default:
			{
				current_target = NULL;
			
				build_chat_target_list ();

				break;
			}
		}
	}

	set_ui_object_text (obj, s);

	if (current_target)
	{
		text = get_ui_object_text (chat_current_text);

		if (text)
		{
			if (strlen (text) > 0)
			{
				set_ingame_ui_object_mouse_over_properties (obj);

				set_ui_object_notify_on (obj, NOTIFY_TYPE_BUTTON_DOWN);

				return;
			}
		}
	}

	set_ui_object_notify_on (obj, NOTIFY_TYPE_NONE);

	set_ui_object_highlightable (obj, FALSE);

	col = &ui_ingame_dead_text_colour;

	set_ui_object_font_colour (obj, col->r, col->g, col->b, col->a);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int add_message_to_campaign_log (int index)
{
	int
		hours,
		minutes,
		seconds;

	char
		*s;

	message_log_type
		*message;

	rgb_colour
		*col = NULL;

	message = get_message_log (index);

	ASSERT (message);

	if (message->type == MESSAGE_TEXT_PILOT_STRING)
	{
		get_digital_clock_int_values (message->time_of_day, &hours, &minutes, &seconds);
	
		s = malloc_fast_mem (strlen (message->string) + 20);
	
		sprintf (s, "[%02d:%02d] %s", hours, minutes, message->string);
	
		col = &(message->colour);
	
		ASSERT (col);
	
		add_to_pop_up_list (s, chat_message_list, NULL, index, -1, *col);
	
		free_mem (s);
	
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void campaign_screen_update_chat_page_pilot (entity *en)
{
	entity
		*current_target;
		
	current_target = get_local_entity_safe_ptr (get_ui_object_item_number (chat_send_button));
	
	if (current_target == en)
	{
		set_ui_object_item_number (chat_send_button, get_local_entity_safe_index (get_session_entity ()));
	}

	build_chat_target_list ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void define_campaign_screen_chat_page_objects (void)
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

	campaign_page [CAMPAIGN_PAGE_CHAT] = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (campaign_screen),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_CENTRE_TOP),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_14),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_DRAWABLE (FALSE),
			UI_ATTR_DRAW_FUNCTION (update_chat_page_objects),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	page = campaign_page [CAMPAIGN_PAGE_CHAT];

	/////////////////////////////////////////////////////////////////
	// Chat Target/Message Window

	x1 = 0.0;
	y1 = 0.068;
	x2 = 0.502;
	y2 = 0.109;

	chat_window_mode_area = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXTURE_GRAPHIC (create_texture_graphic ("graphics\\ui\\cohokum\\map\\chattabs.psd")),
				UI_ATTR_END
			);

	x1 = 0.0;
	y1 = 0.0;
	x2 = 0.5;
	y2 = 1.0;

	chat_window_destination_button = create_ui_object
			(
				UI_TYPE_RADIO,
				UI_ATTR_PARENT (chat_window_mode_area),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
				UI_ATTR_TEXT (get_trans ("Destination")),
				UI_ATTR_FUNCTION (notify_show_destinations),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	set_ingame_ui_object_mouse_over_properties (chat_window_destination_button);

	x1 = 0.5;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 1.0;

	chat_window_message_button = create_ui_object
			(
				UI_TYPE_RADIO,
				UI_ATTR_PARENT (chat_window_mode_area),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
				UI_ATTR_TEXT (get_trans ("Messages")),
				UI_ATTR_FUNCTION (notify_show_messages),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	set_ingame_ui_object_mouse_over_properties (chat_window_message_button);

	x1 = 0.057;
	y1 = 0.152;
	x2 = 0.931;
	y2 = 0.625;

	chat_window_area = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	/////////////////////////////////////////////////////////////////
	// Target List Area

	x1 = 0.0;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 1.0;

	chat_target_list_area = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (chat_window_area),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_VSLIDER (0, 300, 12),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	set_common_slider_graphics (chat_target_list_area);

	// List Box

	x1 = 0.0;
	y1 = 0.0;
	x2 = 0.95;
	y2 = 1.0;

	chat_target_list = create_ui_object
				(
					UI_TYPE_LIST_BOX,
					UI_ATTR_PARENT (chat_target_list_area),
					UI_ATTR_VIRTUAL_POSITION (x1, y1),
					UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
					UI_ATTR_CLEAR (TRUE),
					UI_ATTR_FUNCTION (notify_target_list),
					UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
					UI_ATTR_ITEM_NUMBER (ENTITY_INDEX_DONT_CARE),
					UI_ATTR_END
				);

	/////////////////////////////////////////////////////////////////
	// Message list

	x1 = 0.0;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 1.0;

	chat_message_list_area = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (chat_window_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_VSLIDER (0, 300, 12),
			UI_ATTR_END
		);

	set_common_slider_graphics (chat_message_list_area);

	x1 = 0.0;
	y1 = 0.0;
	x2 = 0.95;
	y2 = 1.0;

	chat_message_list = create_ui_object
			(
				UI_TYPE_LIST_BOX,
				UI_ATTR_PARENT (chat_message_list_area),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_NONE),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	/////////////////////////////////////////////////////////////////
	// Chat Text area

	x1 = 0.100;
	y1 = 0.720;
	x2 = 0.876;
	y2 = 0.756;

	sprintf (string, "%s:", get_trans ("Enter Message"));

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

	x1 = 0.123;
	y1 = 0.762;
	x2 = 0.876;
	y2 = 0.834;

	chat_text_area = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXTURE_GRAPHIC (create_texture_graphic ("graphics\\ui\\cohokum\\map\\msgbar.psd")),
				UI_ATTR_FUNCTION (chat_enter_message_function),
				UI_ATTR_END
			);

	// Chat Input

	x1 = 0.04;
	y1 = 0.25;
	x2 = 1.0;
	y2 = 1.0;

   chat_input = create_ui_object
            (
               UI_TYPE_INPUT,
               UI_ATTR_PARENT (chat_text_area),
					UI_ATTR_VIRTUAL_POSITION (x1, y1),
					UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
					UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
					UI_ATTR_FONT_COLOUR (ui_ingame_selected_text_colour.r, ui_ingame_selected_text_colour.g, ui_ingame_selected_text_colour.b, ui_ingame_selected_text_colour.a),
					UI_ATTR_FUNCTION (chat_input_function),
					UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
					UI_ATTR_TEXT (""),
					UI_ATTR_CLEAR (TRUE),
               UI_ATTR_END
            );

	// Chat Output

	x1 = 0.04;
	y1 = 0.16;
	x2 = 1.0;
	y2 = 1.0;

   chat_current_text = create_ui_object
            (
               UI_TYPE_AREA,
               UI_ATTR_PARENT (chat_text_area),
					UI_ATTR_VIRTUAL_POSITION (x1, y1),
					UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
					UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
					UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
					UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
					UI_ATTR_TEXT (""),
					UI_ATTR_FUNCTION (chat_enter_message_function),
					UI_ATTR_CLEAR (TRUE),
               UI_ATTR_END
            );

	/////////////////////////////////////////////////////////////////
	// Send Button

	x1 = 0.235;
	y1 = 0.834;
	x2 = 0.763;
	y2 = 0.884;

	chat_send_button = create_ui_object
			(
				UI_TYPE_BUTTON,
            UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
				UI_ATTR_TEXT (get_trans ("UI_SEND")),
				UI_ATTR_FUNCTION (notify_send_message),
				UI_ATTR_DRAW_FUNCTION (draw_chat_send_button),
				UI_ATTR_TEXTURE_GRAPHIC (create_texture_graphic ("graphics\\ui\\cohokum\\map\\sendbtn.psd")),
				UI_ATTR_END
			);

	set_ingame_ui_object_mouse_over_properties (chat_send_button);

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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_new_message (campaign_screen_messages message, entity *sender)
{
	build_chat_message_list ();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_chat_page_message_responses (void)
{
	campaign_screen_message_targets
		target;

	target = CAMPAIGN_SCREEN_TARGET_CHAT_PAGE;

	campaign_screen_message_responses [target][CAMPAIGN_SCREEN_NEW_MESSAGE]		=	response_to_new_message;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

