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

static entity
	*mouse_over_entity = NULL;

static texture_graphic
	*common_slider_graphic = NULL,
	*common_slider_bar_graphic = NULL,
	*common_slider_bar_highlighted_graphic = NULL,
	*common_slider_bar_selected_graphic = NULL,
	*common_slider_up_graphic = NULL,
	*common_slider_up_highlighted_graphic = NULL,
	*common_slider_up_selected_graphic = NULL,
	*common_slider_down_graphic = NULL,
	*common_slider_down_highlighted_graphic = NULL,
	*common_slider_down_selected_graphic = NULL;

texture_graphic
	*common_divider_graphic = NULL,
	*common_purple_mask = NULL,
	*common_grey_alpha_mask = NULL,
	*common_black_alpha_mask = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void entity_mouse_over_function (ui_object *obj, void *arg);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_ingame_screen (void)
{
	common_slider_graphic 						= create_texture_graphic ( "graphics\\ui\\cohokum\\map\\sbckmap.psd" );

	common_slider_bar_graphic 					= create_texture_graphic ( "graphics\\ui\\cohokum\\map\\scrolprp.psd" );
	common_slider_bar_highlighted_graphic 	= create_texture_graphic ( "graphics\\ui\\cohokum\\map\\scrolwht.psd" );
	common_slider_bar_selected_graphic 		= create_texture_graphic ( "graphics\\ui\\cohokum\\map\\scrolyel.psd" );

	common_slider_up_graphic 					= create_texture_graphic ( "graphics\\ui\\cohokum\\map\\arrupprp.psd" );
	common_slider_up_highlighted_graphic 	= create_texture_graphic ( "graphics\\ui\\cohokum\\map\\arrupwht.psd" );
	common_slider_up_selected_graphic 		= create_texture_graphic ( "graphics\\ui\\cohokum\\map\\arrupyel.psd" );

	common_slider_down_graphic 				= create_texture_graphic ( "graphics\\ui\\cohokum\\map\\arrdwprp.psd" );
	common_slider_down_highlighted_graphic = create_texture_graphic ( "graphics\\ui\\cohokum\\map\\arrdwwht.psd" );
	common_slider_down_selected_graphic 	= create_texture_graphic ( "graphics\\ui\\cohokum\\map\\arrdwyel.psd" );

	common_divider_graphic = create_texture_graphic ( "graphics\\ui\\cohokum\\map\\divider.psd" );
	common_purple_mask = create_texture_graphic ( "graphics\\ui\\cohokum\\map\\blockprp.psd" );
	common_grey_alpha_mask = create_texture_graphic ( "graphics\\ui\\cohokum\\map\\greymask.psd" );
	common_black_alpha_mask = create_texture_graphic ( "graphics\\ui\\cohokum\\map\\blkmask.psd" );

	load_map_textures ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ingame_screen_draw_function (ui_object *obj, void *arg)
{
	ui_object
		*mouse_over_object;

	int
		index;

	entity
		*en;

	//
	// Clear Mouse Over Entity + initialise to highlighted ui object
	//

	set_ui_mouse_over_entity (NULL);

	mouse_over_object = get_current_highlighted_object ();

	if (mouse_over_object)
	{
		if (get_ui_object_highlighted_function (mouse_over_object) == entity_mouse_over_function)
		{
			index = get_ui_object_item_number (mouse_over_object);

			en = get_local_entity_safe_ptr (index);

			if (en)
			{
				set_ui_mouse_over_entity (en);
			}
		}
	}

	//
	// Update Timers etc.
	//

	update_infobar_timers ();

	update_map_animations ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_ui_mouse_over_entity (entity *en)
{
	mouse_over_entity = en;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *get_ui_mouse_over_entity (void)
{
	return mouse_over_entity;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void entity_mouse_over_function (ui_object *obj, void *arg)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_ingame_ui_object_mouse_over_properties (ui_object *obj)
{
	rgb_colour
		*col;

	ASSERT (obj);
	
	set_ui_object_highlightable (obj, TRUE);

	col = &ui_ingame_live_text_colour;
	set_ui_object_font_colour (obj, col->r, col->g, col->b, col->a);

	col = &ui_ingame_highlight_text_colour;
	set_ui_object_highlighted_font_colour (obj, col->r, col->g, col->b, col->a);

	col = &ui_ingame_selected_text_colour;
	set_ui_object_selected_font_colour (obj, col->r, col->g, col->b, col->a);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_ui_mouse_over_entity_function (ui_object *obj)
{
	ASSERT (obj);
	
	set_ui_object_highlighted_function (obj, entity_mouse_over_function);

	set_ui_object_highlighted_notify_on (obj, NOTIFY_TYPE_CONTINUAL);

	set_ingame_ui_object_mouse_over_properties (obj);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void start_ingame_ui_system (void)
{
	add_update_function (update_map_events, 0.0, 0.0);

	add_update_function (update_map_overlays, 15.0 * ONE_SECOND, 0.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stop_ingame_ui_system (void)
{
	remove_update_function (update_map_events);

	remove_update_function (update_map_overlays);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_mission_player_suitability_status (entity *mission)
{
	entity
		*guide,
		*group,
		*base;

	entity_sub_types
		group_type,
		mission_type;

	task_state_types
		state;

	mission_type = get_local_entity_int_value (mission, INT_TYPE_ENTITY_SUB_TYPE);

	if ((task_database [mission_type].primary_task) && (task_database [mission_type].visible_task))
	{
		state = get_local_entity_int_value (mission, INT_TYPE_TASK_STATE);
	
		switch (state)
		{
			case TASK_STATE_UNASSIGNED:
			{
				//
				// Take each group at the base, and test if it matches the mission type
				//
	
				base = get_local_entity_parent (mission, LIST_TYPE_UNASSIGNED_TASK);
	
				ASSERT (base);
	
				ASSERT (get_local_entity_type (base) == ENTITY_TYPE_KEYSITE);
	
				group = get_local_entity_first_child (base, LIST_TYPE_KEYSITE_GROUP);
	
				while (group)
				{
					if (get_local_entity_int_value (group, INT_TYPE_GROUP_MODE) == GROUP_MODE_IDLE)
					{
						group_type = get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE);
	
						if (get_group_suitable_for_player (group, get_pilot_entity ()))
						{
							if (get_group_to_task_suitability (group_type, mission_type) > 0.0)
							{
								return TRUE;
							}
						}
					}
	
					group = get_local_entity_child_succ (group, LIST_TYPE_KEYSITE_GROUP);
				}
	
				break;
			}
	
			case TASK_STATE_ASSIGNED:
			{
				//
				// Mission already assigned - see if group is suitable for player
				//
				
				guide = get_local_entity_first_child (mission, LIST_TYPE_GUIDE);
			
				ASSERT (guide);
	
				group = get_local_entity_parent (guide, LIST_TYPE_GUIDE_STACK);
	
				ASSERT (group);
	
				if (get_group_suitable_for_player (group, get_pilot_entity ()))
				{
					return TRUE;
				}
	
				break;
			}
	
			case TASK_STATE_COMPLETED:
			{
	
				break;
			}
		}
	}
	
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_group_player_suitability_status (entity *group)
{
	entity
		*base,
		*mission;

	entity_sub_types
		group_type,
		mission_type;

	ASSERT (group);

	if (!group)
	{
		return FALSE;
	}

	//
	// Check if group contains controllable entities
	//
	
	if (!get_group_suitable_for_player (group, get_pilot_entity ()))
	{
		return FALSE;
	}

	//
	// If group is already doing a mission, then it must have at least one suitable mission
	//

	if (get_local_group_primary_task (group))
	{
		return TRUE;
	}

	//
	// if group is NOT doing a mission, then it must be IDLE for it to be suitable (otherwise it could be landing / taxiing etc)
	//

	if (get_local_entity_int_value (group, INT_TYPE_GROUP_MODE) != GROUP_MODE_IDLE)
	{
		return FALSE;
	}

	//
	// Check if group is at a base with suitable missions
	//

	group_type = get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE);

	base = get_local_entity_parent (group, LIST_TYPE_KEYSITE_GROUP);

	ASSERT (base);

	ASSERT (get_local_entity_type (base) == ENTITY_TYPE_KEYSITE);

	mission = get_local_entity_first_child (base, LIST_TYPE_UNASSIGNED_TASK);

	while (mission)
	{	
		mission_type = get_local_entity_int_value (mission, INT_TYPE_ENTITY_SUB_TYPE);

		if (get_group_to_task_suitability (group_type, mission_type) > 0.0)
		{
			return TRUE;
		}

		mission = get_local_entity_child_succ (mission, LIST_TYPE_UNASSIGNED_TASK);
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_base_player_suitability_status (entity *base)
{
	entity
		*group,
		*guide,
		*mission;

	entity_sub_types
		group_type,
		mission_type;

	int
		loop,
		count,
		mission_types [NUM_ENTITY_SUB_TYPE_TASKS];

	ASSERT (base);

	//
	// First check assigned missions
	//

	mission = get_local_entity_first_child (base, LIST_TYPE_ASSIGNED_TASK);

	while (mission)
	{	
		mission_type = get_local_entity_int_value (mission, INT_TYPE_ENTITY_SUB_TYPE);

		if ((task_database [mission_type].primary_task) && (task_database [mission_type].visible_task))
		{
			guide = get_local_entity_first_child (mission, LIST_TYPE_GUIDE);

			ASSERT (guide);

			group = get_local_entity_parent (guide, LIST_TYPE_GUIDE_STACK);

			ASSERT (group);

			if (get_group_suitable_for_player (group, get_pilot_entity ()))
			{
				return TRUE;
			}
		}

		mission = get_local_entity_child_succ (mission, LIST_TYPE_ASSIGNED_TASK);
	}

	//
	// Construct a list of types of mission available at the base
	//

	memset (mission_types, 0, sizeof (int) * NUM_ENTITY_SUB_TYPE_TASKS);

	count = 0;

	mission = get_local_entity_first_child (base, LIST_TYPE_UNASSIGNED_TASK);

	while (mission)
	{	
		mission_type = get_local_entity_int_value (mission, INT_TYPE_ENTITY_SUB_TYPE);

		if ((task_database [mission_type].primary_task) && (task_database [mission_type].visible_task))
		{
			if (!mission_types [mission_type])
			{
				mission_types [mission_type] = TRUE;

				count ++;
			}
		}

		mission = get_local_entity_child_succ (mission, LIST_TYPE_ASSIGNED_TASK);
	}

	if (count == 0)
	{
		return FALSE;
	}

	//
	// Take each group at the base, and test if it matches an available mission type
	//

	group = get_local_entity_first_child (base, LIST_TYPE_KEYSITE_GROUP);

	while (group)
	{
		if (get_local_entity_int_value (group, INT_TYPE_GROUP_MODE) == GROUP_MODE_IDLE)
		{
			group_type = get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE);

			if (get_group_suitable_for_player (group, get_pilot_entity ()))
			{
				for (loop = 0; loop < NUM_ENTITY_SUB_TYPE_TASKS; loop ++)
				{
					if (mission_types [loop])
					{
						if (get_group_to_task_suitability (group_type, mission_type) > 0.0)
						{
							return TRUE;
						}
					}
				}
			}
		}

		group = get_local_entity_child_succ (group, LIST_TYPE_KEYSITE_GROUP);
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void player_assigned_new_task (entity *mobile, entity *task)
{
	#if DEMO_VERSION

	if (get_game_type () != GAME_TYPE_FREE_FLIGHT)
	{
		return;
	}

	#endif

	ASSERT (mobile);

	ASSERT (task);

	ASSERT (get_pilot_entity ());

	debug_log ("COMMON: Player %s assigned to task %s", get_local_entity_string (get_pilot_entity (), STRING_TYPE_PILOTS_NAME), get_local_entity_string (task, STRING_TYPE_FULL_NAME));

	set_gunship_entity (mobile);

	set_client_server_entity_parent (get_pilot_entity (), LIST_TYPE_PLAYER_TASK, task);

	//play ingame music track
	play_cd_music (CD_MUSIC_TYPE_COCKPIT);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void player_quit_current_task (void)
{
	ASSERT (!get_gunship_entity ());

	notify_campaign_screen (CAMPAIGN_SCREEN_PLAYER_LEAVE_MISSION, NULL);

	notify_clear_current_selections (NULL, NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void player_quit_session (event *ev)
{
	initialise_game_initialisation_phases ();

	set_exit_flight_loop (TRUE);

	push_ui_screen (game_type_screen);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void page_back_event (event *ev)
{
	minimize_all_map_objects ();

	pop_campaign_history (NULL, NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ingame_quit_function (event *ev)
{
	switch (get_game_type ())
	{
		case GAME_TYPE_CAMPAIGN:
		case GAME_TYPE_SKIRMISH:
		{
			if (get_in_flight_game_mode () == IN_FLIGHT_GAME_MODE_SIMULATOR)
			{
				set_in_flight_game_mode (IN_FLIGHT_GAME_MODE_PLANNER);
			}

			if (get_gunship_entity ())
			{
				setup_campaign_quit_mission_dialog ();
			}
			else
			{
				setup_campaign_quit_campaign_dialog ();
			}

			break;
		}
		case GAME_TYPE_FREE_FLIGHT:
		{
			if (get_in_flight_game_mode () == IN_FLIGHT_GAME_MODE_SIMULATOR)
			{
				set_in_flight_game_mode (IN_FLIGHT_GAME_MODE_PLANNER);
			}

			setup_free_flight_quit_campaign_dialog ();

			break;
		}
		default:
		{
			debug_fatal ("COMMON: Invalid Game Type %d", get_game_type ());
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void delete_waypoint_event (event *ev)
{
	entity
		*en,
		*task;

	entity_sub_types
		sub_type;

	en = get_ui_mouse_over_entity ();

	if (en)
	{
		if (get_local_entity_type (en) == ENTITY_TYPE_WAYPOINT)
		{
			if ((get_local_entity_child_succ (en, LIST_TYPE_WAYPOINT)) && (get_local_entity_child_pred (en, LIST_TYPE_WAYPOINT)))
			{
				sub_type = get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);

				if (waypoint_database [sub_type].planner_moveable)
				{
					//
					// Delete waypoint
					//

					if (!get_local_entity_first_child (en, LIST_TYPE_CURRENT_WAYPOINT))
					{
						task = get_local_entity_parent (en, LIST_TYPE_WAYPOINT);

						ASSERT (task);

						ASSERT (get_local_entity_int_value (task, INT_TYPE_PRIMARY_TASK));

						//
						// "Fast-track" unlinking of waypoint, Required to stop client "double-deleting"
						//
						
						unlink_local_entity_children (en, LIST_TYPE_CURRENT_WAYPOINT);
					
						delete_local_entity_from_parents_child_list (en, LIST_TYPE_TASK_DEPENDENT);
					
						delete_local_entity_from_parents_child_list (en, LIST_TYPE_WAYPOINT);

						//
						// Destroy Entity
						//
						
						destroy_client_server_entity (en);

						update_client_server_entity_waypoint_list_tags (task);

						set_ui_mouse_over_entity (NULL);
					}
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void adjust_3d_preview_heading_left_event (event *ev)
{
	rotate_base_page_3d_scene_heading (10.0);
	rotate_group_page_3d_scene_heading (10.0);
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void adjust_3d_preview_heading_right_event (event *ev)
{
	rotate_base_page_3d_scene_heading (-10.0);
	rotate_group_page_3d_scene_heading (-10.0);
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void adjust_3d_preview_pitch_up_event (event *ev)
{
	rotate_base_page_3d_scene_pitch (5.0);
	rotate_group_page_3d_scene_pitch (5.0);
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void adjust_3d_preview_pitch_down_event (event *ev)
{
	rotate_base_page_3d_scene_pitch (-5.0);
	rotate_group_page_3d_scene_pitch (-5.0);
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void adjust_3d_preview_zoom_in_event (event *ev)
{
	zoom_base_page_3d_scene (1);
	zoom_group_page_3d_scene (1);
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void adjust_3d_preview_zoom_out_event (event *ev)
{
	zoom_base_page_3d_scene (-1);
	zoom_group_page_3d_scene (-1);
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ingame_screen_set_events (void)
{

	#ifdef DEBUG

	set_event (DIK_SCROLL, MODIFIER_NONE, KEY_STATE_UP, breakout);

	#endif

	set_event (DIK_S, MODIFIER_RIGHT_SHIFT, KEY_STATE_DOWN, save_ui_screen);

	set_event (DIK_X, MODIFIER_LEFT_CONTROL, KEY_STATE_UP, exit_apache_havoc);

	set_event (DIK_Q, MODIFIER_LEFT_CONTROL, KEY_STATE_UP, ingame_quit_function);

   set_event (DIK_RETURN, MODIFIER_NONE, KEY_STATE_DOWN, toggle_in_flight_game_modes);

	//
	// time acceleration
	//

   set_event (DIK_P, MODIFIER_NONE, KEY_STATE_DOWN, toggle_pause_time_acceleration);

   set_event (DIK_ADD, MODIFIER_LEFT_CONTROL, KEY_STATE_DOWN, set_small_inc_time_acceleration);
   set_event (DIK_EQUALS, MODIFIER_LEFT_CONTROL, KEY_STATE_DOWN, set_small_inc_time_acceleration);

   set_event (DIK_SUBTRACT, MODIFIER_LEFT_CONTROL, KEY_STATE_DOWN, set_small_dec_time_acceleration);
   set_event (DIK_MINUS, MODIFIER_LEFT_CONTROL, KEY_STATE_DOWN, set_small_dec_time_acceleration);

	//
	// Map keyboard shortcuts
	//

	set_event (DIK_UP, MODIFIER_NONE, KEY_STATE_DOWN, shift_current_map_up_event);
	set_event (DIK_DOWN, MODIFIER_NONE, KEY_STATE_DOWN, shift_current_map_down_event);
	set_event (DIK_LEFT, MODIFIER_NONE, KEY_STATE_DOWN, shift_current_map_left_event);
	set_event (DIK_RIGHT, MODIFIER_NONE, KEY_STATE_DOWN, shift_current_map_right_event);

	set_event (DIK_NUMPAD8, MODIFIER_NONE, KEY_STATE_DOWN, shift_current_map_up_event);
	set_event (DIK_NUMPAD2, MODIFIER_NONE, KEY_STATE_DOWN, shift_current_map_down_event);
	set_event (DIK_NUMPAD4, MODIFIER_NONE, KEY_STATE_DOWN, shift_current_map_left_event);
	set_event (DIK_NUMPAD6, MODIFIER_NONE, KEY_STATE_DOWN, shift_current_map_right_event);

   set_event (DIK_EQUALS, MODIFIER_NONE, KEY_STATE_DOWN, zoom_in_current_map_event);
   set_event (DIK_MINUS, MODIFIER_NONE, KEY_STATE_DOWN, zoom_out_current_map_event);

   set_event (DIK_ADD, MODIFIER_NONE, KEY_STATE_DOWN, zoom_in_current_map_event);
   set_event (DIK_SUBTRACT, MODIFIER_NONE, KEY_STATE_DOWN, zoom_out_current_map_event);

	set_event (DIK_PERIOD, MODIFIER_NONE, KEY_STATE_DOWN, zoom_in_current_map_event);
	set_event (DIK_COMMA, MODIFIER_NONE, KEY_STATE_DOWN, zoom_out_current_map_event);

	set_event (DIK_DECIMAL, MODIFIER_NONE, KEY_STATE_DOWN, delete_waypoint_event);
	set_event (DIK_DELETE, MODIFIER_NONE, KEY_STATE_DOWN, delete_waypoint_event);

	set_event (DIK_BACK, MODIFIER_NONE, KEY_STATE_DOWN, page_back_event);

	set_event (DIK_C, MODIFIER_NONE, KEY_STATE_DOWN, centre_current_map_on_player);
	set_event (DIK_HOME, MODIFIER_NONE, KEY_STATE_DOWN, centre_current_map_on_player);

	//
	// 3D Preview keyboard shortcuts
	//

	set_event (DIK_LEFT, MODIFIER_LEFT_ALT, KEY_STATE_DOWN, adjust_3d_preview_heading_left_event);
	set_event (DIK_RIGHT, MODIFIER_LEFT_ALT, KEY_STATE_DOWN, adjust_3d_preview_heading_right_event);
	set_event (DIK_UP, MODIFIER_LEFT_ALT, KEY_STATE_DOWN, adjust_3d_preview_pitch_up_event);
	set_event (DIK_DOWN, MODIFIER_LEFT_ALT, KEY_STATE_DOWN, adjust_3d_preview_pitch_down_event);

	set_event (DIK_PERIOD, MODIFIER_LEFT_ALT, KEY_STATE_DOWN, adjust_3d_preview_zoom_in_event);
	set_event (DIK_COMMA, MODIFIER_LEFT_ALT, KEY_STATE_DOWN, adjust_3d_preview_zoom_out_event);

	set_event (DIK_EQUALS, MODIFIER_LEFT_ALT, KEY_STATE_DOWN, adjust_3d_preview_zoom_in_event);
	set_event (DIK_MINUS, MODIFIER_LEFT_ALT, KEY_STATE_DOWN, adjust_3d_preview_zoom_out_event);

	set_event (DIK_ADD, MODIFIER_LEFT_ALT, KEY_STATE_DOWN, adjust_3d_preview_zoom_in_event);
	set_event (DIK_SUBTRACT, MODIFIER_LEFT_ALT, KEY_STATE_DOWN, adjust_3d_preview_zoom_out_event);

	//
	// mouse buttons
	//

	set_event (MOUSE_LEFT_BUTTON, MODIFIER_NONE, BUTTON_STATE_EITHER, ui_left_mouse_button);

	set_event (MOUSE_RIGHT_BUTTON, MODIFIER_NONE, BUTTON_STATE_EITHER, ui_right_mouse_button);

	set_event (MOUSE_LEFT_BUTTON, MODIFIER_LEFT_SHIFT, BUTTON_STATE_EITHER, ui_left_mouse_button);

	set_event (MOUSE_RIGHT_BUTTON, MODIFIER_LEFT_SHIFT, BUTTON_STATE_EITHER, ui_right_mouse_button);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_common_slider_graphics (ui_object *parent)
{
	ui_object
		*temp,
		*slider;
		
	slider = get_ui_object_vslider (parent);

	ASSERT (slider);

	ASSERT (common_slider_graphic); 

	ASSERT (common_slider_bar_graphic); 
	ASSERT (common_slider_bar_highlighted_graphic);
	ASSERT (common_slider_bar_selected_graphic); 

	ASSERT (common_slider_up_graphic); 
	ASSERT (common_slider_up_highlighted_graphic); 
	ASSERT (common_slider_up_selected_graphic); 

	ASSERT (common_slider_down_graphic);
	ASSERT (common_slider_down_highlighted_graphic); 
	ASSERT (common_slider_down_selected_graphic); 

	set_ui_object_texture_graphic (slider, common_slider_graphic);

	// get slider & set graphic
	temp = get_ui_object_child (slider);
	set_ui_object_texture_graphic (temp, common_slider_bar_graphic);
	set_ui_object_highlighted_texture_graphic (temp, common_slider_bar_highlighted_graphic);
	set_ui_object_selected_texture_graphic (temp, common_slider_bar_selected_graphic);
	set_ui_object_text (temp, "");

	// get up button & set graphic
	temp = get_ui_object_next (temp);
	set_ui_object_texture_graphic (temp, common_slider_up_graphic);
	set_ui_object_highlighted_texture_graphic (temp, common_slider_up_highlighted_graphic);
	set_ui_object_selected_texture_graphic (temp, common_slider_up_selected_graphic);
	set_ui_object_text (temp, "");

	// get down button & set graphic
	temp = get_ui_object_next (temp);
	set_ui_object_texture_graphic (temp, common_slider_down_graphic);
	set_ui_object_highlighted_texture_graphic (temp, common_slider_down_highlighted_graphic);
	set_ui_object_selected_texture_graphic (temp, common_slider_down_selected_graphic);
	set_ui_object_text (temp, "");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
