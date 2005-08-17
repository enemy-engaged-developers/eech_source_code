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

static ui_object
	*debriefing_text_area,
	*debriefing_text_list,
	*debriefing_page_title,
	*debriefing_page_type,
	*debriefing_page_result_box,
	#ifdef DEBUG
	*debriefing_page_points_box,
	#endif
	*debriefing_page_kills_area,
	*debriefing_page_kills_box;

static ui_object
	*page_map_view_area,
	*page_map_area,
	*page_back_button;

static map_dimension_type
	page_map_dimensions;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void show_debriefing_page (entity *mission, int force_update, int force_final_debrief)
{

	medal_types
		medal;

	int
		awarded_medals,
		awarded_promotion;

	entity
		*base,
		*previous;

	static char
		s [128];

	char
		medal_text [1024],
		*debrief,
		*ff_debrief;

	ASSERT (mission);

	ASSERT (get_local_entity_type (mission) == ENTITY_TYPE_TASK);

	if (force_update)
	{
		previous = NULL;
	}
	else
	{
		previous = get_local_entity_safe_ptr (get_ui_object_item_number (campaign_page [CAMPAIGN_PAGE_DEBRIEFING]));
	}

	//
	// Get debriefing text
	//

	ui_object_destroy_list_items (debriefing_text_list);

	set_ui_object_virtual_y_size (debriefing_text_list, 1.0);

	if ((!force_final_debrief) && (get_gunship_entity ()) && (get_player_task (NULL) == mission) && (get_local_entity_int_value (mission, INT_TYPE_TASK_TERMINATED) == TASK_TERMINATED_IN_PROGRESS))
	{
		//
		// Awaiting Final Debrief
		//

		add_to_pop_up_list_with_word_wrap (get_trans ("NO_DEBRIEF_AVAILABLE"), debriefing_text_list, NULL, 0, UI_FONT_ARIAL_10, ui_ingame_dead_text_colour);
	}
	else
	{
		//
		// Final Debriefing
		//
		
		get_debriefing_text (mission, &debrief, &ff_debrief);
	
		if (debrief)
		{
		
			add_to_pop_up_list_with_word_wrap (debrief, debriefing_text_list, NULL, 0, UI_FONT_ARIAL_10, ui_ingame_dead_text_colour);
		}
		else
		{
	
			add_to_pop_up_list_with_word_wrap (get_trans ("NO_DEBRIEF_AVAILABLE"), debriefing_text_list, NULL, 0, UI_FONT_ARIAL_10, ui_ingame_dead_text_colour);
		}
	
		//
		// check for friendly fire
		//
	
		if (ff_debrief)
		{
	
			add_to_pop_up_list_with_word_wrap (ff_debrief, debriefing_text_list, NULL, 0, UI_FONT_ARIAL_10, ui_ingame_dead_text_colour);
		}
	
		//
		// check for medals
		//
	
		awarded_medals = get_local_entity_int_value (mission, INT_TYPE_AWARDED_MEDALS);
	
		for (medal = MEDAL_TYPE_NONE; medal < NUM_MEDAL_TYPES; medal ++)
		{
	
			if (awarded_medals & (1 << medal))
			{

				debug_log ("CA_DBF: Awarding Medal %s for task %s (%d)", medal_type_names [medal], get_local_entity_string (mission, STRING_TYPE_FULL_NAME), get_local_entity_index (mission));
			
				if (get_medal_briefing_text (mission, medal, medal_text))
				{
			
					add_briefing_text_to_list (debriefing_text_list, medal_text);
				}
				else
				{
	
					debug_log ("CA_DBF: no text for medal award : %s", medal_type_names [medal]);
				}
			}
		}
	
		//
		// check for promotion
		//
	
		awarded_promotion = get_local_entity_int_value (mission, INT_TYPE_AWARDED_PROMOTION);
	
		if (awarded_promotion != PILOT_RANK_NONE)
		{

			debug_log ("CA_DBF: Awarding Promotion %s for task %s (%d)", pilot_rank_names [awarded_promotion], get_local_entity_string (mission, STRING_TYPE_FULL_NAME), get_local_entity_index (mission));
		
			if (get_promotion_briefing_text (mission, awarded_promotion, medal_text))
			{
		
				add_briefing_text_to_list (debriefing_text_list, &medal_text);
			}
			else
			{

				debug_log ("CA_DBF: no text for promotion award : %s", pilot_rank_names [awarded_promotion]);
			}
		}
	}
		
	resize_briefing_list_size (debriefing_text_list);
	
	//
	// 
	//

	sprintf (s, "%s", get_trans ("Debriefing"));

	set_ui_object_text (debriefing_page_title, s);

	sprintf (s, "%s #%d", get_trans (get_local_entity_string (mission, STRING_TYPE_FULL_NAME)), get_local_entity_int_value (mission, INT_TYPE_TASK_ID));

	set_ui_object_text (debriefing_page_type, s);

	//
	// 2D MAP
	//

	set_ui_object_item_number (page_map_area, get_local_entity_index (mission));

	if (mission != previous)
	{
		//
		// Autofit map to mission route
		//

		vec3d
			min_pos,
			max_pos,
			*pos,
			*base_pos,
			*route_nodes;

		int
			loop,
			route_length;

		base = get_local_entity_parent (mission, get_local_task_list_type (mission));

		base_pos = get_local_entity_vec3d_ptr (base, VEC3D_TYPE_POSITION);

		min_pos = *base_pos;
		max_pos = *base_pos;

		route_nodes = get_local_entity_ptr_value (mission, PTR_TYPE_ROUTE_NODE);

		route_length = get_local_entity_int_value (mission, INT_TYPE_ROUTE_LENGTH);

		if (route_nodes)
		{
			for (loop = 0; loop < route_length; loop ++)
			{
				pos = &route_nodes [loop];

				min_pos.x = min (min_pos.x, pos->x);
				min_pos.z = min (min_pos.z, pos->z);

				max_pos.x = max (max_pos.x, pos->x);
				max_pos.z = max (max_pos.z, pos->z);
			}
		}

		page_map_dimensions.x = (min_pos.x + max_pos.x) * 0.5;
		page_map_dimensions.z = (min_pos.z + max_pos.z) * 0.5;

		page_map_dimensions.size = max ((max_pos.x - min_pos.x), (max_pos.z - min_pos.z));

		page_map_dimensions.size *= 1.2;

		page_map_dimensions.size = max (page_map_dimensions.size, 4.0 * KILOMETRE);

		page_map_dimensions.subject_entity = mission;
	}

	//

	display_campaign_page (CAMPAIGN_PAGE_DEBRIEFING, get_local_entity_index (mission), TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void autoselect_debriefing_page (entity *mission, int force_final_debrief)
{
	campaign_pages
		current_page;
		
	current_page = get_current_campaign_page ();

	if ((current_page != CAMPAIGN_PAGE_CHAT) && (current_page != CAMPAIGN_PAGE_SAVE))
	{
		show_debriefing_page (mission, TRUE, force_final_debrief);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_campaign_screen_debriefing_page_objects (void)
{
	page_map_dimensions.x = MID_MAP_X;
	page_map_dimensions.z = MID_MAP_Z;
	page_map_dimensions.size = 4.0 * KILOMETRE;

	page_map_dimensions.subject_entity = NULL;
	page_map_dimensions.selected_entity = NULL;

	clear_map_mouse_over_object (&page_map_dimensions);

	set_ui_object_item_number (page_map_area, ENTITY_INDEX_DONT_CARE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_debriefing_page_objects (ui_object *obj, void *arg)
{
	char
		s [128];

	entity
		*mission;
	
	//
	// N.B. Some of this stuff could be moved into "show_debriefing_page" as it doesn't need to be updated EVERY frame....
	//

	mission = get_local_entity_safe_ptr (get_ui_object_item_number (campaign_page [CAMPAIGN_PAGE_DEBRIEFING]));

	ASSERT (mission);

	//
	// RESULT
	//

	{
		int
			result;

		char
			output [256];

		result = get_local_entity_int_value (mission, INT_TYPE_TASK_COMPLETED);

		sprintf (output, "%s :  %s", get_trans ("Result"), get_trans (task_debrief_result_names [result]));

		set_ui_object_text (debriefing_page_result_box, output);
	}

	//
	// POINTS
	//

	#ifdef DEBUG

	{
		int
			points;

		points = get_local_entity_int_value (mission, INT_TYPE_TASK_SCORE);

		sprintf (s, "%d", points);

		set_ui_object_text (debriefing_page_points_box, s);
	}

	#endif

	//
	// KILLS / LOSSES
	//

	ui_object_destroy_list_items (debriefing_page_kills_box);
	
  	{

		task
			*task_raw;

		task_kill_loss_data
			*kill;

		int
			loop;

		static int
			aircraft_count [NUM_ENTITY_SUB_TYPE_AIRCRAFT],
			vehicle_count [NUM_ENTITY_SUB_TYPE_VEHICLES];

		task_raw = get_local_entity_data (mission);

		//
		// Kills
		//

		kill = task_raw->task_kills;

		if (kill)
		{
			memset (aircraft_count, 0, sizeof (int) * NUM_ENTITY_SUB_TYPE_AIRCRAFT);
			memset (vehicle_count, 0, sizeof (int) * NUM_ENTITY_SUB_TYPE_VEHICLES);

			add_to_pop_up_list (get_trans ("Kills"), debriefing_page_kills_box, NULL, 1.0, get_ui_object_font_type (debriefing_page_kills_box), get_ui_object_font_colour (debriefing_page_kills_box));

			// construct list

			while (kill)
			{
				if ((kill->victim_type == ENTITY_TYPE_FIXED_WING) || (kill->victim_type == ENTITY_TYPE_HELICOPTER))
				{
					aircraft_count [kill->victim_sub_type] ++;
				}
				else
				{
					vehicle_count [kill->victim_sub_type] ++;
				}
	
				kill = kill->next;
			}

			// Aircraft

			for (loop = 0; loop < NUM_ENTITY_SUB_TYPE_AIRCRAFT; loop ++)
			{
				if (aircraft_count [loop] > 0)
				{
					sprintf (s, "    %dx %s", aircraft_count [loop], aircraft_database [loop].full_name);
	
					add_to_pop_up_list (s, debriefing_page_kills_box, NULL, 1.0, get_ui_object_font_type (debriefing_page_kills_box), get_ui_object_font_colour (debriefing_page_kills_box));
				}
			}

			// Vehicles

			for (loop = 0; loop < NUM_ENTITY_SUB_TYPE_VEHICLES; loop ++)
			{
				if (vehicle_count [loop] > 0)
				{
					sprintf (s, "    %dx %s", vehicle_count [loop], vehicle_database [loop].full_name);
	
					add_to_pop_up_list (s, debriefing_page_kills_box, NULL, 1.0, get_ui_object_font_type (debriefing_page_kills_box), get_ui_object_font_colour (debriefing_page_kills_box));
				}
			}
		}

		//
		// Losses
		//

		kill = task_raw->task_losses;

		if (kill)
		{
			memset (aircraft_count, 0, sizeof (int) * NUM_ENTITY_SUB_TYPE_AIRCRAFT);
			memset (vehicle_count, 0, sizeof (int) * NUM_ENTITY_SUB_TYPE_VEHICLES);

			add_to_pop_up_list (get_trans ("Losses"), debriefing_page_kills_box, NULL, 1.0, get_ui_object_font_type (debriefing_page_kills_box), get_ui_object_font_colour (debriefing_page_kills_box));
	
			// construct list

			while (kill)
			{
				if ((kill->victim_type == ENTITY_TYPE_FIXED_WING) || (kill->victim_type == ENTITY_TYPE_HELICOPTER))
				{
					aircraft_count [kill->victim_sub_type] ++;
				}
				else
				{
					vehicle_count [kill->victim_sub_type] ++;
				}
	
				kill = kill->next;
			}

			// Aircraft

			for (loop = 0; loop < NUM_ENTITY_SUB_TYPE_AIRCRAFT; loop ++)
			{
				if (aircraft_count [loop] > 0)
				{
					sprintf (s, "    %dx %s", aircraft_count [loop], aircraft_database [loop].full_name);
	
					add_to_pop_up_list (s, debriefing_page_kills_box, NULL, 1.0, get_ui_object_font_type (debriefing_page_kills_box), get_ui_object_font_colour (debriefing_page_kills_box));
				}
			}

			// Vehicles

			for (loop = 0; loop < NUM_ENTITY_SUB_TYPE_VEHICLES; loop ++)
			{
				if (vehicle_count [loop] > 0)
				{
					sprintf (s, "    %dx %s", vehicle_count [loop], vehicle_database [loop].full_name);
	
					add_to_pop_up_list (s, debriefing_page_kills_box, NULL, 1.0, get_ui_object_font_type (debriefing_page_kills_box), get_ui_object_font_colour (debriefing_page_kills_box));
				}
			}
		}
	}

	set_ui_object_drawable (page_back_button, get_campaign_history_valid ());
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_page_map (ui_object *obj, void *arg)
{
	entity
		*en;

	en = get_local_entity_safe_ptr (get_ui_object_item_number (campaign_page [CAMPAIGN_PAGE_DEBRIEFING]));

	ASSERT (en);
	
	draw_2d_map (obj, arg);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void define_campaign_screen_debriefing_page_objects (void)
{
	float
		x1,
		y1,
		x2,
		y2,
		x_start,
		x_mid,
		x_end,
		ysize,
		yinc;

	ui_object
		*page;

	char
		output [128];
		
	/////////////////////////////////////////////////////////////////
	// Main Page Area
	/////////////////////////////////////////////////////////////////

	x1 = CAMPAIGN_INSET_PAGE_X1;
	y1 = CAMPAIGN_INSET_PAGE_Y1;
	x2 = CAMPAIGN_INSET_PAGE_X2;
	y2 = CAMPAIGN_INSET_PAGE_Y2;

	campaign_page [CAMPAIGN_PAGE_DEBRIEFING] = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (campaign_screen),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_CENTRE_TOP),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_14),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_DRAWABLE (FALSE),
			UI_ATTR_DRAW_FUNCTION (update_debriefing_page_objects),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	page = campaign_page [CAMPAIGN_PAGE_DEBRIEFING];

	/////////////////////////////////////////////////////////////////
	// Title
			
	x1 = 0.045;
	y1 = 0.053;

	x2 = 0.45;
	y2 = 0.085;

	debriefing_page_title = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (page),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_18),
			UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	x1 = 0.045;
	y1 = 0.092;
	x2 = 0.45;
	y2 = 0.136;

	debriefing_page_type = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (page),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
			UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	/////////////////////////////////////////////////////////////////

	x_start = 0.045;

	x_mid = 0.224;

	x_end = 0.464;
	
	ysize = 0.04;

	yinc = 0.05;

	/////////////////////////////////////////////////////////////////
	// Task Result Box

	x1 = x_start;
	y1 = 0.158;
	x2 = x_mid;
	y2 = y1 + ysize;

	sprintf (output, "%s :", get_trans ("Result"));
			
	debriefing_page_result_box = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (output),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_14),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	/////////////////////////////////////////////////////////////////
	// Task Points Awarded Box

	#ifdef DEBUG
	
	x1 = x_start;
	x2 = x_mid;

	y1 += yinc;
	y2 = y1 + ysize;

	sprintf (output, "%s :", get_trans ("Score"));
			
	create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (output),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_14),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	x1 = x_mid;
	x2 = x_end;

	debriefing_page_points_box = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (""),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	#endif

	/////////////////////////////////////////////////////////////////
	// Task Kills box

	x1 = 0.050;
	x2 = 0.474;

	y1 = 0.206;
	y2 = 0.620;

	debriefing_page_kills_area = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_14),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_VSLIDER (0, 0, 10),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	set_common_slider_graphics (debriefing_page_kills_area);

	x1 = 0.0;
	x2 = 0.9;

	y1 = 0.0;
	y2 = 1.0;

	debriefing_page_kills_box = create_ui_object
			(
				UI_TYPE_LIST_BOX,
				UI_ATTR_PARENT (debriefing_page_kills_area),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_14),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_NONE),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	/////////////////////////////////////////////////////////////////
	// debriefing text

	x1 = 0.1;
	y1 = 0.746;
	x2 = 0.99;
	y2 = 0.94;

	debriefing_text_area = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_VSLIDER (0.0, 0.0, 1.0),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	set_common_slider_graphics (debriefing_text_area);

	x1 = 0.0;
	x2 = 0.9;
	y1 = 0.0;
	y2 = 1.0;

	debriefing_text_list = create_ui_object
			(
				UI_TYPE_LIST_BOX,
				UI_ATTR_PARENT (debriefing_text_area),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_NONE),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	/////////////////////////////////////////////////////////////////
	// Map Area
			
	x1 = 0.5;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 0.67;

	page_map_view_area = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXTURE_GRAPHIC (create_texture_graphic ("graphics\\ui\\cohokum\\map\\blockprp.psd")),
				UI_ATTR_END
			);

	x1 = 0.01;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 0.99;

	page_map_area = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (page_map_view_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_END
		);

	/////////////////////////////////////////////////////////////////
	// Map Objects

	define_map_objects (page_map_area, &page_map_dimensions, draw_page_map, campaign_map_left_click_function, map_centralise_function, &campaign_screen_full_screen_map);


	/////////////////////////////////////////////////////////////////
	// "Divider" graphics

	x1 = 0.022;
	y1 = 0.138;
	x2 = 0.474;
	y2 = 0.161;

	create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXTURE_GRAPHIC (common_divider_graphic),
				UI_ATTR_END
			);

	////////////////////////////////////

	x1 = 0.022;
	y1 = 0.649;
	x2 = 0.474;
	y2 = 0.672;

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

static int response_to_mission_destroyed (campaign_screen_messages message, entity *sender)
{
	if (get_local_entity_safe_index (sender) == get_ui_object_item_number (campaign_page [CAMPAIGN_PAGE_DEBRIEFING]))
	{
		if (get_ui_object_drawable (campaign_page [CAMPAIGN_PAGE_DEBRIEFING]))
		{
			//
			// Not sure yet.... For now display the map page
			//

			show_map_page ();
		}

		set_ui_object_item_number (campaign_page [CAMPAIGN_PAGE_DEBRIEFING], ENTITY_INDEX_DONT_CARE);
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_force_update (campaign_screen_messages message, entity *sender)
{
	if (get_ui_object_drawable (campaign_page [CAMPAIGN_PAGE_DEBRIEFING]))
	{
		ASSERT (sender);

		show_debriefing_page (sender, TRUE, FALSE);
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_debriefing_page_message_responses (void)
{
	campaign_screen_message_targets
		target;

	target = CAMPAIGN_SCREEN_TARGET_DEBRIEFING_PAGE;

	campaign_screen_message_responses [target][CAMPAIGN_SCREEN_MISSION_DESTROYED]	=	response_to_mission_destroyed;

	campaign_screen_message_responses [target][CAMPAIGN_SCREEN_FORCE_UPDATE]		=	response_to_force_update;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



