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

#include "ai/taskgen/croute.h"
#include "ai/taskgen/assign.h"
#include "ai/taskgen/taskgen.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ui_object
	*free_flight_screen;

static ui_object
	*free_flight_dialog_area,
	*free_flight_quit_campaign_area;

//gunship_types free_flight_gunship_type = GUNSHIP_TYPE_APACHE;
gunship_types free_flight_gunship_type = GUNSHIP_TYPE_HOKUM;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void quit_free_flight_set_events (void);

static int free_flight_gunship_type_matches(entity_sub_types entity_type);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_main_free_flight_screen (void)
{
	initialise_map_data ();

	initialise_free_flight_screen_map_page_objects ();

	initialise_free_flight_screen_info_objects ();

	set_ui_object_drawable (free_flight_dialog_area, FALSE);

	set_ui_object_drawable (free_flight_quit_campaign_area, FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_free_flight_screen_entered (ui_object *obj, void *arg)
{
 	if (command_line_ui_sounds_muted)
 		ui_sounds_muted = TRUE; //ataribaby 29/12/2008 for muted UI sounds
  
	set_mouse_graphic_on ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void free_flight_screen_draw_function (ui_object *obj, void *arg)
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
//
// QUIT FREE FLIGHT
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void free_flight_cancel_quit_campaign (event *ev)
{
	set_ui_object_drawable (free_flight_dialog_area, FALSE);

	set_ui_object_drawable (free_flight_quit_campaign_area, FALSE);

	pop_event (quit_free_flight_set_events);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_free_flight_cancel_quit_campaign_button (ui_object *obj, void *arg)
{
	free_flight_cancel_quit_campaign (NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void free_flight_accept_quit_campaign (event *ev)
{
	if (command_line_ui_sounds_muted)
		ui_sounds_muted = FALSE; //ataribaby 29/12/2008 for muted UI sounds 
  
	free_flight_cancel_quit_campaign (ev);

	player_quit_session (NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_free_flight_accept_quit_campaign_button (ui_object *obj, void *arg)
{
	free_flight_accept_quit_campaign (NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void quit_free_flight_set_events (void)
{
	set_event (DIK_S, MODIFIER_NONE, KEY_STATE_DOWN, free_flight_accept_quit_campaign);
	set_event (DIK_Y, MODIFIER_NONE, KEY_STATE_DOWN, free_flight_accept_quit_campaign);
	set_event (DIK_J, MODIFIER_NONE, KEY_STATE_DOWN, free_flight_accept_quit_campaign);
	set_event (DIK_O, MODIFIER_NONE, KEY_STATE_DOWN, free_flight_accept_quit_campaign);
	set_event (DIK_T, MODIFIER_NONE, KEY_STATE_DOWN, free_flight_accept_quit_campaign);

	set_event (DIK_N, MODIFIER_NONE, KEY_STATE_DOWN, free_flight_cancel_quit_campaign);

	set_event (DIK_X, MODIFIER_LEFT_CONTROL, KEY_STATE_UP, exit_apache_havoc);

	set_event (MOUSE_LEFT_BUTTON, MODIFIER_NONE, BUTTON_STATE_EITHER, ui_left_mouse_button);
	set_event (MOUSE_LEFT_BUTTON, MODIFIER_LEFT_SHIFT, BUTTON_STATE_EITHER, ui_left_mouse_button);

	set_event (MOUSE_RIGHT_BUTTON, MODIFIER_NONE, BUTTON_STATE_EITHER, ui_right_mouse_button);
	set_event (MOUSE_RIGHT_BUTTON, MODIFIER_LEFT_SHIFT, BUTTON_STATE_EITHER, ui_right_mouse_button);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup_free_flight_quit_campaign_dialog (void)
{
	set_ui_object_drawable (free_flight_dialog_area, TRUE);

	set_ui_object_drawable (free_flight_quit_campaign_area, TRUE);

	push_event (quit_free_flight_set_events, "quit free flight events");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_free_flight_screen (void)
{
	float
		x1, x2,
		y1, y2,
		x_size,
		y_size;

	char
		string [256];

	x_size = 1.0;
	y_size = 1.0;

	/////////////////////////////////////////////////////////////////

   free_flight_screen = create_ui_object
            (
               UI_TYPE_SCREEN,
               UI_ATTR_VIRTUAL_POSITION (0, 0),
               UI_ATTR_VIRTUAL_SIZE (x_size, y_size),
					UI_ATTR_FUNCTION (notify_free_flight_screen_entered),
					UI_ATTR_DRAW_FUNCTION (free_flight_screen_draw_function),
					UI_ATTR_CLEAR (TRUE),
               UI_ATTR_END
            );

	define_free_flight_screen_map_page_objects ();

	define_free_flight_screen_info_objects ();

	define_free_flight_screen_selection_objects ();

	/////////////////////////////////////////////////////////////////

	x1 = 0.0;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 1.0;

	free_flight_dialog_area = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (free_flight_screen),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXTURE_GRAPHIC (common_grey_alpha_mask),
			UI_ATTR_END
		);

	/////////////////////////////////////////////////////////////////
	//
	// Quit Free Flight
	//
	/////////////////////////////////////////////////////////////////

	x1 = 0.257;
	y1 = 0.303;
	x2 = 0.74;
	y2 = 0.612;

	free_flight_quit_campaign_area = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (free_flight_dialog_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXTURE_GRAPHIC (create_texture_graphic ("graphics\\ui\\cohokum\\map\\quitcamp.psd")),
			UI_ATTR_END
		);

	x1 = 0.1;
	y1 = 0.65;
	x2 = 0.6;
	y2 = 1.0;

	sprintf (string, "%s?", get_trans ("Quit Free Flight"));

	create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (free_flight_quit_campaign_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT (string),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
			UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	x1 = 0.6;
	y1 = 0.65;
	x2 = 0.8;
	y2 = 1.0;

	create_ui_object
		(
			UI_TYPE_BUTTON,
			UI_ATTR_PARENT (free_flight_quit_campaign_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT (get_trans ("Yes")),
			UI_ATTR_FUNCTION (notify_free_flight_accept_quit_campaign_button),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
			UI_ATTR_FONT_COLOUR (ui_ingame_live_text_colour.r, ui_ingame_live_text_colour.g, ui_ingame_live_text_colour.b, ui_ingame_live_text_colour.a),
			UI_ATTR_HIGHLIGHTED_FONT_COLOUR (ui_ingame_highlight_text_colour.r, ui_ingame_highlight_text_colour.g, ui_ingame_highlight_text_colour.b, ui_ingame_highlight_text_colour.a),
			UI_ATTR_SELECTED_FONT_COLOUR (ui_ingame_selected_text_colour.r, ui_ingame_selected_text_colour.g, ui_ingame_selected_text_colour.b, ui_ingame_selected_text_colour.a),
			UI_ATTR_HIGHLIGHTABLE (TRUE),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	x1 = 0.8;
	y1 = 0.65;
	x2 = 1.0;
	y2 = 1.0;

	create_ui_object
		(
			UI_TYPE_BUTTON,
			UI_ATTR_PARENT (free_flight_quit_campaign_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT (get_trans ("No")),
			UI_ATTR_FUNCTION (notify_free_flight_cancel_quit_campaign_button),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
			UI_ATTR_FONT_COLOUR (ui_ingame_live_text_colour.r, ui_ingame_live_text_colour.g, ui_ingame_live_text_colour.b, ui_ingame_live_text_colour.a),
			UI_ATTR_HIGHLIGHTED_FONT_COLOUR (ui_ingame_highlight_text_colour.r, ui_ingame_highlight_text_colour.g, ui_ingame_highlight_text_colour.b, ui_ingame_highlight_text_colour.a),
			UI_ATTR_SELECTED_FONT_COLOUR (ui_ingame_selected_text_colour.r, ui_ingame_selected_text_colour.g, ui_ingame_selected_text_colour.b, ui_ingame_selected_text_colour.a),
			UI_ATTR_HIGHLIGHTABLE (TRUE),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *free_flight_auto_assign_gunship (void)
{
	vec3d
		*pos;
	
	entity
		*force,
		*new_task,
		*group,
		*member,
		**gunship_list,
		*en;

	entity_sub_types
		sub_type;

	int
		c,
		index,
		count;

	//
	// Auto assign a helicopter for free flight
	//

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ASSERT (get_game_type () == GAME_TYPE_FREE_FLIGHT);

	ASSERT (get_pilot_entity ());

	if (get_gunship_entity ())
	{
		return NULL;
	}

	force = get_local_entity_parent (get_pilot_entity (), LIST_TYPE_PILOT);

	ASSERT (force);

	//
	// Count up candidates
	//

	count = 0;

	en = get_local_entity_first_child (force, LIST_TYPE_AIR_REGISTRY);
	
	while (en)
	{
		if (get_local_entity_int_value (en, INT_TYPE_GROUP_MODE) == GROUP_MODE_IDLE)
		{
			member = get_local_entity_first_child (en, LIST_TYPE_MEMBER);

			while (member)
			{
				sub_type = get_local_entity_int_value (member, INT_TYPE_ENTITY_SUB_TYPE);

				if (free_flight_gunship_type_matches(sub_type))
					if (get_local_entity_suitable_for_player (member, get_pilot_entity ()))
						count ++;

				member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
			}
		}

		en = get_local_entity_child_succ (en, LIST_TYPE_AIR_REGISTRY);
	}

	if (count == 0)
	{
		return NULL;
	}

	//
	// Create list of candidates
	//
	
	gunship_list = (entity **) safe_malloc (sizeof (entity *) * count);

	count = 0;

	en = get_local_entity_first_child (force, LIST_TYPE_AIR_REGISTRY);
	
	while (en)
	{
		if (get_local_entity_int_value (en, INT_TYPE_GROUP_MODE) == GROUP_MODE_IDLE)
		{
			member = get_local_entity_first_child (en, LIST_TYPE_MEMBER);

			while (member)
			{
				sub_type = get_local_entity_int_value (member, INT_TYPE_ENTITY_SUB_TYPE);

				if (free_flight_gunship_type_matches(sub_type))
					if (get_local_entity_suitable_for_player (member, get_pilot_entity ()))
					{
						gunship_list [count] = member;

						count ++;
					}

				member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
			}
		}

		en = get_local_entity_child_succ (en, LIST_TYPE_AIR_REGISTRY);
	}

	//
	// Pick one...
	//

	ASSERT (count > 0);

	index = rand16 () % count;

	for (c = 0; c < count; c ++)
	{
		en = gunship_list [index];

		group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

		pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

		new_task = create_user_task (en, ENTITY_SUB_TYPE_TASK_FREE_FLIGHT, pos, NULL, NULL);
					
		set_assign_create_waypoint_route (FALSE);
					
		if (assign_primary_task_to_group (group, new_task))
		{
			set_gunship_entity (en);

			set_view_mode (VIEW_MODE_COCKPIT_PANEL_LEVEL_AHEAD);

			safe_free (gunship_list);

			initialise_free_flight_screen_map_page_objects ();

			return en;
		}
		else
		{						
			debug_log ("FLIGHT: can't assign user to Created task");

			destroy_client_server_entity (new_task);
		}

		set_assign_create_waypoint_route (TRUE);

		index ++;

		if (index == count)
		{
			index = 0;
		}
	}

	safe_free (gunship_list);

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

gunship_types get_free_flight_gunship_type()
{
	return free_flight_gunship_type;
}

void set_free_flight_gunship_type(gunship_types type)
{
	free_flight_gunship_type = type;	
}

int free_flight_gunship_type_matches(entity_sub_types entity_type)
{
	switch (free_flight_gunship_type)
	{
		case GUNSHIP_TYPE_APACHE:
			return entity_type == ENTITY_SUB_TYPE_AIRCRAFT_AH64D_APACHE_LONGBOW;
		case GUNSHIP_TYPE_AH64A:
			return entity_type == ENTITY_SUB_TYPE_AIRCRAFT_AH64A_APACHE;
		case GUNSHIP_TYPE_COMANCHE:
			return entity_type == ENTITY_SUB_TYPE_AIRCRAFT_RAH66_COMANCHE;
		case GUNSHIP_TYPE_BLACKHAWK:
			return entity_type == ENTITY_SUB_TYPE_AIRCRAFT_UH60_BLACK_HAWK;
		case GUNSHIP_TYPE_HOKUM:
			return entity_type == ENTITY_SUB_TYPE_AIRCRAFT_KA52_HOKUM_B;
		case GUNSHIP_TYPE_HAVOC:
			return entity_type == ENTITY_SUB_TYPE_AIRCRAFT_MI28N_HAVOC_B;
		case GUNSHIP_TYPE_HIND:
			return entity_type == ENTITY_SUB_TYPE_AIRCRAFT_MI24D_HIND;
		case GUNSHIP_TYPE_KA50:
			return entity_type == ENTITY_SUB_TYPE_AIRCRAFT_KA50_HOKUM;
		case GUNSHIP_TYPE_VIPER:
			return entity_type == ENTITY_SUB_TYPE_AIRCRAFT_AH1Z_VIPER;
		case NUM_GUNSHIP_TYPES:			// if none other selected, default to comanche or hokum
			return entity_type == ENTITY_SUB_TYPE_AIRCRAFT_RAH66_COMANCHE || entity_type == ENTITY_SUB_TYPE_AIRCRAFT_KA52_HOKUM_B;
		default:
			ASSERT(!"unknown gunship type");
			break;
	}
	
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



