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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define CAMPAIGN_MENU_ITEM_FONT UI_FONT_ARIAL_16

#define MAX_MENU_BUTTONS 16

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static ui_object
	*top_menu_area,
	*campaign_chat_button,
	*campaign_save_button,
	*campaign_briefing_button,
	*campaign_weapon_loading_button,
	*button_list [MAX_MENU_BUTTONS];

static int
	menu_button_count = 0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_campaign_screen_menu_objects (void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_top_menu_area (ui_object *obj, void *arg)
{
	int
		loop,
		page;

	ui_object
		*this_object;

	entity
		*task;

	ASSERT (get_session_entity ());

	//
	// Set save button drawable state
	//
	
	set_ui_object_drawable
	(
		campaign_save_button,
		((get_comms_model () == COMMS_MODEL_SERVER) && (get_local_entity_int_value (get_session_entity (), INT_TYPE_SESSION_COMPLETE) == CAMPAIGN_COMPLETED_FALSE))
	);

	//
	// Set chat button drawable state
	//
	
	#ifdef DEBUG

	set_ui_object_drawable (campaign_chat_button, TRUE);

	#else

	set_ui_object_drawable (campaign_chat_button, (get_connection_list_head () != NULL));

	#endif

	//
	// Set briefing button drawable state
	//

	task = get_player_task (NULL);

	if (task)
	{
		set_ui_object_drawable (campaign_briefing_button, TRUE);

		if (get_local_entity_int_value (task, INT_TYPE_TASK_STATE) == TASK_STATE_COMPLETED)
		{
			set_ui_object_text (campaign_briefing_button, get_trans ("Debriefing"));
		}
		else
		{
			set_ui_object_text (campaign_briefing_button, get_trans ("Briefing"));
		}
	}
	else
	{
		set_ui_object_text (campaign_briefing_button, "");

		set_ui_object_drawable (campaign_briefing_button, FALSE);
	}

	//
	// Set weapon loading button drawable state
	//

	if (get_gunship_entity ())
	{	
		set_ui_object_drawable (campaign_weapon_loading_button, TRUE);
	}
	else
	{
		set_ui_object_drawable (campaign_weapon_loading_button, FALSE);
	}

	//
	// Set on/off states for all buttons
	//
	
	for (loop = 0; loop < menu_button_count; loop ++)
	{
		this_object = button_list [loop];

		ASSERT (this_object);
		
		page = get_ui_object_item_number (this_object);

		ASSERT ((page >= 0) && (page < NUM_CAMPAIGN_PAGES));

		if (get_ui_object_drawable (campaign_page [page]))
		{
			set_ui_object_state (this_object, UI_OBJECT_STATE_ON);
		}
		else
		{
			set_ui_object_state (this_object, UI_OBJECT_STATE_OFF);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_main_map_button (ui_object *obj, void *arg)
{
	show_map_page ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_stats_button (ui_object *obj, void *arg)
{
	show_stats_page ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_main_options_button (ui_object *obj, void *arg)
{
	set_pause_time_acceleration (NULL);

	show_options_page ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_save_button (ui_object *obj, void *arg)
{
	show_save_page (NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_chat_button (ui_object *obj, void *arg)
{
	show_chat_page (NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_log_button (ui_object *obj, void *arg)
{
	show_log_page ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_briefing_button (ui_object *obj, void *arg)
{
	entity
		*task;

	task = get_player_task (NULL);

	if (task)
	{
		if (get_local_entity_int_value (task, INT_TYPE_TASK_STATE) == TASK_STATE_COMPLETED)
		{
			show_debriefing_page (task, FALSE, FALSE);
		}
		else
		{
			show_briefing_page (task, FALSE);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_weapon_loading_button(ui_object *obj, void *arg)
{
	entity
		*group;
		
	ASSERT (get_gunship_entity ());

	group = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_MEMBER);

	ASSERT (group);

	show_weapon_loading_page (group, TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void define_campaign_screen_menu_objects (void)
{
	float
		x1,
		y1,
		x2,
		y2;

	menu_button_count = 0;

	/////////////////////////////////////////////////////////////////
	// Map / Stats / Options etc. 
	/////////////////////////////////////////////////////////////////

	x1 = CAMPAIGN_INSET_PAGE_X1;
	y1 = 0.0;
	x2 = 1.0;
	y2 = CAMPAIGN_INSET_PAGE_Y1;

	top_menu_area = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (campaign_screen),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXTURE_GRAPHIC (create_texture_graphic ("graphics\\ui\\cohokum\\map\\tabs.psd")),
			UI_ATTR_DRAW_FUNCTION (update_top_menu_area),
			UI_ATTR_END
		);

	/////////////////////////////////////////////////////////////////
	// Map Button

	x1 = 0.0;
	y1 = 0.0;
	x2 = 0.125;
	y2 = 1.0;

	button_list [menu_button_count++] = create_ui_object
			(
				UI_TYPE_RADIO,
				UI_ATTR_PARENT (top_menu_area),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (get_trans ("Map")),
				UI_ATTR_FONT_TYPE (CAMPAIGN_MENU_ITEM_FONT),
				UI_ATTR_FONT_COLOUR (ui_ingame_live_text_colour.r, ui_ingame_live_text_colour.g, ui_ingame_live_text_colour.b, ui_ingame_live_text_colour.a),
				UI_ATTR_HIGHLIGHTED_FONT_COLOUR (ui_ingame_highlight_text_colour.r, ui_ingame_highlight_text_colour.g, ui_ingame_highlight_text_colour.b, ui_ingame_highlight_text_colour.a),
				UI_ATTR_SELECTED_FONT_COLOUR (ui_ingame_selected_text_colour.r, ui_ingame_selected_text_colour.g, ui_ingame_selected_text_colour.b, ui_ingame_selected_text_colour.a),
				UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_DOWN),
				UI_ATTR_FUNCTION (notify_main_map_button),
				UI_ATTR_CLEAR ( TRUE ),
				UI_ATTR_HIGHLIGHTABLE (TRUE),
				UI_ATTR_ITEM_NUMBER (CAMPAIGN_PAGE_MAP),
				UI_ATTR_END
			);

	/////////////////////////////////////////////////////////////////
	// Stats Button

	x1 = 0.125;
	y1 = 0.0;
	x2 = 0.250;
	y2 = 1.0;

	button_list [menu_button_count++] = create_ui_object
			(
				UI_TYPE_RADIO,
				UI_ATTR_PARENT (top_menu_area),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (get_trans ("Sit. Rep.")),
				UI_ATTR_FONT_TYPE (CAMPAIGN_MENU_ITEM_FONT),
				UI_ATTR_FONT_COLOUR (ui_ingame_live_text_colour.r, ui_ingame_live_text_colour.g, ui_ingame_live_text_colour.b, ui_ingame_live_text_colour.a),
				UI_ATTR_HIGHLIGHTED_FONT_COLOUR (ui_ingame_highlight_text_colour.r, ui_ingame_highlight_text_colour.g, ui_ingame_highlight_text_colour.b, ui_ingame_highlight_text_colour.a),
				UI_ATTR_SELECTED_FONT_COLOUR (ui_ingame_selected_text_colour.r, ui_ingame_selected_text_colour.g, ui_ingame_selected_text_colour.b, ui_ingame_selected_text_colour.a),
				UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_DOWN),
				UI_ATTR_FUNCTION (notify_stats_button),
				UI_ATTR_CLEAR ( TRUE ),
				UI_ATTR_HIGHLIGHTABLE (TRUE),
				UI_ATTR_ITEM_NUMBER (CAMPAIGN_PAGE_STATS),
				UI_ATTR_END
			);

	/////////////////////////////////////////////////////////////////
	// Message Log Button

	x1 = 0.250;
	y1 = 0.0;
	x2 = 0.375;
	y2 = 1.0;

	button_list [menu_button_count++] = create_ui_object
			(
				UI_TYPE_RADIO,
				UI_ATTR_PARENT (top_menu_area),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (get_trans ("Log")),
				UI_ATTR_FONT_TYPE (CAMPAIGN_MENU_ITEM_FONT),
				UI_ATTR_FONT_COLOUR (ui_ingame_live_text_colour.r, ui_ingame_live_text_colour.g, ui_ingame_live_text_colour.b, ui_ingame_live_text_colour.a),
				UI_ATTR_HIGHLIGHTED_FONT_COLOUR (ui_ingame_highlight_text_colour.r, ui_ingame_highlight_text_colour.g, ui_ingame_highlight_text_colour.b, ui_ingame_highlight_text_colour.a),
				UI_ATTR_SELECTED_FONT_COLOUR (ui_ingame_selected_text_colour.r, ui_ingame_selected_text_colour.g, ui_ingame_selected_text_colour.b, ui_ingame_selected_text_colour.a),
				UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_DOWN),
				UI_ATTR_FUNCTION (notify_log_button),
				UI_ATTR_CLEAR ( TRUE ),
				UI_ATTR_HIGHLIGHTABLE (TRUE),
				UI_ATTR_ITEM_NUMBER (CAMPAIGN_PAGE_LOG),
				UI_ATTR_END
			);

	/////////////////////////////////////////////////////////////////
	// Weapon Loading Button

	x1 = 0.375;
	y1 = 0.0;
	x2 = 0.500;
	y2 = 1.0;

	campaign_weapon_loading_button = create_ui_object
			(
				UI_TYPE_RADIO,
				UI_ATTR_PARENT (top_menu_area),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (get_trans ("Payload")),
				UI_ATTR_FONT_TYPE (CAMPAIGN_MENU_ITEM_FONT),
				UI_ATTR_FONT_COLOUR (ui_ingame_live_text_colour.r, ui_ingame_live_text_colour.g, ui_ingame_live_text_colour.b, ui_ingame_live_text_colour.a),
				UI_ATTR_HIGHLIGHTED_FONT_COLOUR (ui_ingame_highlight_text_colour.r, ui_ingame_highlight_text_colour.g, ui_ingame_highlight_text_colour.b, ui_ingame_highlight_text_colour.a),
				UI_ATTR_SELECTED_FONT_COLOUR (ui_ingame_selected_text_colour.r, ui_ingame_selected_text_colour.g, ui_ingame_selected_text_colour.b, ui_ingame_selected_text_colour.a),
				UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_DOWN),
				UI_ATTR_FUNCTION (notify_weapon_loading_button),
				UI_ATTR_CLEAR ( TRUE ),
				UI_ATTR_HIGHLIGHTABLE (TRUE),
				UI_ATTR_ITEM_NUMBER (CAMPAIGN_PAGE_WEAPON_LOADING),
				UI_ATTR_END
			);

	button_list [menu_button_count++] = campaign_weapon_loading_button;

	/////////////////////////////////////////////////////////////////
	// Briefing Button

	x1 = 0.500;
	y1 = 0.0;
	x2 = 0.625;
	y2 = 1.0;

	campaign_briefing_button = create_ui_object
			(
				UI_TYPE_BUTTON,
				UI_ATTR_PARENT (top_menu_area),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_FONT_TYPE (CAMPAIGN_MENU_ITEM_FONT),
				UI_ATTR_FONT_COLOUR (ui_ingame_live_text_colour.r, ui_ingame_live_text_colour.g, ui_ingame_live_text_colour.b, ui_ingame_live_text_colour.a),
				UI_ATTR_HIGHLIGHTED_FONT_COLOUR (ui_ingame_highlight_text_colour.r, ui_ingame_highlight_text_colour.g, ui_ingame_highlight_text_colour.b, ui_ingame_highlight_text_colour.a),
				UI_ATTR_SELECTED_FONT_COLOUR (ui_ingame_selected_text_colour.r, ui_ingame_selected_text_colour.g, ui_ingame_selected_text_colour.b, ui_ingame_selected_text_colour.a),
				UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_DOWN),
				UI_ATTR_FUNCTION (notify_briefing_button),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_HIGHLIGHTABLE (TRUE),
				UI_ATTR_END
			);

	/////////////////////////////////////////////////////////////////
	// Chat Button

	x1 = 0.625;
	y1 = 0.0;
	x2 = 0.750;
	y2 = 1.0;

	campaign_chat_button = create_ui_object
			(
				UI_TYPE_RADIO,
				UI_ATTR_PARENT (top_menu_area),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (get_trans ("Chat")),
				UI_ATTR_FONT_TYPE (CAMPAIGN_MENU_ITEM_FONT),
				UI_ATTR_FONT_COLOUR (ui_ingame_live_text_colour.r, ui_ingame_live_text_colour.g, ui_ingame_live_text_colour.b, ui_ingame_live_text_colour.a),
				UI_ATTR_HIGHLIGHTED_FONT_COLOUR (ui_ingame_highlight_text_colour.r, ui_ingame_highlight_text_colour.g, ui_ingame_highlight_text_colour.b, ui_ingame_highlight_text_colour.a),
				UI_ATTR_SELECTED_FONT_COLOUR (ui_ingame_selected_text_colour.r, ui_ingame_selected_text_colour.g, ui_ingame_selected_text_colour.b, ui_ingame_selected_text_colour.a),
				UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_DOWN),
				UI_ATTR_FUNCTION (notify_chat_button),
				UI_ATTR_CLEAR ( TRUE ),
				UI_ATTR_HIGHLIGHTABLE (TRUE),
				UI_ATTR_ITEM_NUMBER (CAMPAIGN_PAGE_CHAT),
				UI_ATTR_END
			);

	button_list [menu_button_count++] = campaign_chat_button;

	/////////////////////////////////////////////////////////////////
	// Options Button

	x1 = 0.750;
	y1 = 0.0;
	x2 = 0.875;
	y2 = 1.0;

	create_ui_object
			(
				UI_TYPE_BUTTON,
				UI_ATTR_PARENT (top_menu_area),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (get_trans ("Options")),
				UI_ATTR_FONT_TYPE (CAMPAIGN_MENU_ITEM_FONT),
				UI_ATTR_FONT_COLOUR (ui_ingame_live_text_colour.r, ui_ingame_live_text_colour.g, ui_ingame_live_text_colour.b, ui_ingame_live_text_colour.a),
				UI_ATTR_HIGHLIGHTED_FONT_COLOUR (ui_ingame_highlight_text_colour.r, ui_ingame_highlight_text_colour.g, ui_ingame_highlight_text_colour.b, ui_ingame_highlight_text_colour.a),
				UI_ATTR_SELECTED_FONT_COLOUR (ui_ingame_selected_text_colour.r, ui_ingame_selected_text_colour.g, ui_ingame_selected_text_colour.b, ui_ingame_selected_text_colour.a),
				UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_DOWN),
				UI_ATTR_FUNCTION (notify_main_options_button),
				UI_ATTR_CLEAR ( TRUE ),
				UI_ATTR_HIGHLIGHTABLE (TRUE),
				UI_ATTR_END
			);

	/////////////////////////////////////////////////////////////////
	// Save Button

	x1 = 0.875;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 1.0;

	campaign_save_button = create_ui_object
			(
				UI_TYPE_RADIO,
				UI_ATTR_PARENT (top_menu_area),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (get_trans ("Save")),
				UI_ATTR_FONT_TYPE (CAMPAIGN_MENU_ITEM_FONT),
				UI_ATTR_FONT_COLOUR (ui_ingame_live_text_colour.r, ui_ingame_live_text_colour.g, ui_ingame_live_text_colour.b, ui_ingame_live_text_colour.a),
				UI_ATTR_HIGHLIGHTED_FONT_COLOUR (ui_ingame_highlight_text_colour.r, ui_ingame_highlight_text_colour.g, ui_ingame_highlight_text_colour.b, ui_ingame_highlight_text_colour.a),
				UI_ATTR_SELECTED_FONT_COLOUR (ui_ingame_selected_text_colour.r, ui_ingame_selected_text_colour.g, ui_ingame_selected_text_colour.b, ui_ingame_selected_text_colour.a),
				UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_DOWN),
				UI_ATTR_FUNCTION (notify_save_button),
				UI_ATTR_CLEAR ( TRUE ),
				UI_ATTR_HIGHLIGHTABLE (TRUE),
				UI_ATTR_ITEM_NUMBER (CAMPAIGN_PAGE_SAVE),
				UI_ATTR_END
			);

	button_list [menu_button_count++] = campaign_save_button; 

	/////////////////////////////////////////////////////////////////

	ASSERT (menu_button_count < MAX_MENU_BUTTONS);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

