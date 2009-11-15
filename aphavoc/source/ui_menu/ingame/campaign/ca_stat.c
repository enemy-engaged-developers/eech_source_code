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
#include "ai/faction/briefing.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

#define BPOWER_SIDE_AREA_YMIN				0.0
#define BPOWER_SIDE_AREA_YMAX				0.123

#define BPOWER_MAIN_AREA_YMIN				0.171
#define BPOWER_MAIN_AREA_YMAX				1.0
#define BPOWER_MAIN_AREA_XMIN				0.136
#define BPOWER_MAIN_AREA_XMAX				1.0
#define BPOWER_MAIN_AREA_TEXT_XMIN		0.16
#define BPOWER_MAIN_AREA_TEXT_XMAX		0.974
#define BPOWER_MAIN_AREA_ITEM_COUNT		7

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static ui_object
	*page_balance_area,
	*page_balance_overlay,
	*page_balance_sector_side_text_object [2],
	*page_balance_text_object [2][BPOWER_MAIN_AREA_ITEM_COUNT],

	*page_objective_area,
	*page_objective_name_list,
	*page_objective_status_list,

	*page_objective_description_area,
	*page_objective_description_list,

	*page_back_button;

static texture_graphic
	*solid_bar_graphic = NULL,
	*red_bar_graphic = NULL,
	*blue_bar_graphic = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_page_objective_highlight_function (ui_object *obj, void *arg);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void show_stats_objectives_page (void)
{
	entity
		*en,
		*objective;

	int
		side,
		sub_type;

	rgb_colour
		*col;

	ui_object
		*new_item;

	char
		s [128];

	side = get_global_gunship_side (); 

	en = get_local_force_entity ((entity_sides) side);

	ASSERT (en);

	//
	// OBJECTIVES
	//

	ui_object_destroy_list_items (page_objective_name_list);
	ui_object_destroy_list_items (page_objective_status_list);

	objective = get_local_entity_first_child (en, LIST_TYPE_CAMPAIGN_OBJECTIVE);

	while (objective)
	{
		ASSERT (get_local_entity_type (objective) == ENTITY_TYPE_KEYSITE);
		
		sub_type = get_local_entity_int_value (objective, INT_TYPE_ENTITY_SUB_TYPE);

		if (keysite_database [sub_type].troop_insertion_target)
		{
//			sprintf (s, "%s %s", get_trans ("Capture"), get_trans (get_local_entity_string (objective, STRING_TYPE_FULL_NAME)));

			sprintf (s, "%s", get_trans (get_local_entity_string (objective, STRING_TYPE_FULL_NAME)));

			new_item = add_to_pop_up_list (s, page_objective_name_list, NULL, get_local_entity_safe_index (objective), UI_FONT_ARIAL_14, ui_ingame_dead_text_colour);

			set_ui_object_text_justify (new_item, TEXT_JUSTIFY_LEFT_CENTRE);

			set_ingame_ui_object_mouse_over_properties (new_item);

			set_ui_object_highlighted_function (new_item, notify_page_objective_highlight_function);

			if (get_local_entity_int_value (objective, INT_TYPE_SIDE) != side)
			{
				sprintf (s, get_trans ("Incomplete"));

				col = &ui_ingame_dead_text_colour;
			}
			else
			{
				sprintf (s, get_trans ("Complete"));

				col = &ui_ingame_selected_text_colour;
			}

			new_item = add_to_pop_up_list (s, page_objective_status_list, NULL, get_local_entity_safe_index (objective), UI_FONT_ARIAL_14, *col);

			set_ui_object_text_justify (new_item, TEXT_JUSTIFY_LEFT_CENTRE);
		}
		else
		{
//			sprintf (s, "%s %s", get_trans ("Destroy"), get_trans (get_local_entity_string (objective, STRING_TYPE_FULL_NAME)));

			sprintf (s, "%s", get_trans (get_local_entity_string (objective, STRING_TYPE_FULL_NAME)));

			new_item = add_to_pop_up_list (s, page_objective_name_list, NULL, get_local_entity_safe_index (objective), UI_FONT_ARIAL_14, ui_ingame_dead_text_colour);

			set_ui_object_text_justify (new_item, TEXT_JUSTIFY_LEFT_CENTRE);

			set_ingame_ui_object_mouse_over_properties (new_item);

			set_ui_object_highlighted_function (new_item, notify_page_objective_highlight_function);

			if (get_local_entity_int_value (objective, INT_TYPE_ALIVE))
			{
				sprintf (s, "%s", get_trans ("Incomplete"));

				col = &ui_ingame_dead_text_colour;
			}
			else
			{
				sprintf (s, "%s", get_trans ("Complete"));

				col = &ui_ingame_selected_text_colour;
			}

			new_item = add_to_pop_up_list (s, page_objective_status_list, NULL, get_local_entity_safe_index (objective), UI_FONT_ARIAL_14, *col);

			set_ui_object_text_justify (new_item, TEXT_JUSTIFY_LEFT_CENTRE);
		}
		
		objective = get_local_entity_child_succ (objective, LIST_TYPE_CAMPAIGN_OBJECTIVE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void show_stats_page (void)
{
	show_stats_objectives_page ();

	display_campaign_page (CAMPAIGN_PAGE_STATS, ENTITY_INDEX_DONT_CARE, TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_campaign_screen_stats_page_objects (void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_stats_page_colour_bar (ui_object *obj, texture_graphic *graphic, float x1, float y1, float x2, float y2, float w)
{
	real_colour
		colour;

	float
		tx1, tx2,
		sx1, sx2,
		sy1, sy2,
		xmin, xmax,
		ymin, ymax;

	ASSERT (obj);

	ASSERT (graphic);

	xmin = get_ui_object_x (obj);
	ymin = get_ui_object_y (obj);

	xmax = xmin + get_ui_object_x_size (obj);
	ymax = ymin + get_ui_object_y_size (obj);

	//
	// Always have to render to the video screen
	//
		
	ASSERT ( active_screen == video_screen );
	
	if (w >= 0)
	{
		tx1 = x1;
		tx2 = x1 + (w * (x2 - x1));
	}
	else
	{
		tx2 = x2;
		tx1 = x2 + (w * (x2 - x1));
	}

	sx1 = (xmin + (tx1 * (xmax - xmin))) + 1;
	sx2 = (xmin + (tx2 * (xmax - xmin))) - 1;

	sy1 = (ymin + (y1 * (ymax - ymin))) + 1;
	sy2 = (ymin + (y2 * (ymax - ymin))) - 1;

	colour.red = 255;
	colour.green = 255;
	colour.blue = 255;
	colour.alpha = 255;
	
	ui_draw_texture_graphic (sx1, sy1, sx2, sy2, graphic, colour);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_stats_page_solid_bar (ui_object *obj, texture_graphic *graphic, float x1, float y1, float x2, float y2, float w)
{
	real_colour
		colour;

	float
		sx1, sx2,
		sy1, sy2,
		xmin, xmax,
		ymin, ymax;

	ASSERT (obj);

	ASSERT (graphic);

	xmin = get_ui_object_x (obj);
	ymin = get_ui_object_y (obj);

	xmax = xmin + get_ui_object_x_size (obj);
	ymax = ymin + get_ui_object_y_size (obj);

	//
	// Always have to render to the video screen
	//
		
	ASSERT ( active_screen == video_screen );
	
	colour.red = 255;
	colour.green = 255;
	colour.blue = 255;
	colour.alpha = 255;

	sx1 = xmin + 1;
	sx2 = xmax - 1;
	
	sy1 = (ymin + (y1 * (ymax - ymin))) + 1;
	sy2 = (ymin + (y2 * (ymax - ymin))) - 1;

	ui_draw_texture_graphic (sx1, sy1, sx2, sy2, graphic, colour);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_stats_page_unit_balance_of_power (ui_object *obj, int index, entity_sides side, int count, int total)
{
	entity_sides
		this_side;

	float
		dy,
		x1, y1,
		x2, y2,
		c, t, w;

	char
		s [16];

	texture_graphic
		*graphic;
		
	ASSERT (obj);
	
	x1 = BPOWER_MAIN_AREA_XMIN;
	x2 = BPOWER_MAIN_AREA_XMAX;

	dy = (BPOWER_MAIN_AREA_YMAX - BPOWER_MAIN_AREA_YMIN) / BPOWER_MAIN_AREA_ITEM_COUNT;

	y1 = BPOWER_MAIN_AREA_YMIN + ((float)index * dy);
	y2 = y1 + dy;

	this_side = (entity_sides) get_local_entity_int_value (get_pilot_entity (), INT_TYPE_SIDE);

	c = (float)count;
	t = (float)total;

	if (total > 0)
	{
		w = c / t;
	
		if (side != this_side)
		{
			w = -w;
		}
	
		switch (side)
		{
			case ENTITY_SIDE_BLUE_FORCE:
			{
				graphic = blue_bar_graphic;
	
				break;
			}
			case ENTITY_SIDE_RED_FORCE:
			{
				graphic = red_bar_graphic;
	
				break;
			}
			default:
			{
				debug_fatal ("CA_STAT: Invalid side %d for balance of power bar", side);
			}
		}
	
		draw_stats_page_colour_bar (obj, graphic, x1, y1, x2, y2, w);
	}
	else
	{
		if (side == this_side)
		{
			draw_stats_page_solid_bar (obj, solid_bar_graphic, x1, y1, x2, y2, 1.0);
		}
	}

	ASSERT (index >= 0);

	if (total > 0)
	{	
		sprintf (s, "%.0f%%", (100.0 * c / t));
	}
	else
	{
		sprintf (s, "");
	}

	if (side == this_side)
	{
		set_ui_object_text (page_balance_text_object [0][index], s);
	}
	else
	{
		set_ui_object_text (page_balance_text_object [1][index], s);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_stats_page_sector_side_balance_of_power (ui_object *obj, entity_sides side, int count, int total)
{
	entity_sides
		this_side;

	float
		x1, y1,
		x2, y2,
		c, t, w;

	char
		s [16];

	texture_graphic
		*graphic;
		
	ASSERT (obj);
	
	x1 = BPOWER_MAIN_AREA_XMIN;
	x2 = BPOWER_MAIN_AREA_XMAX;

	y1 = BPOWER_SIDE_AREA_YMIN;
	y2 = BPOWER_SIDE_AREA_YMAX;

	this_side = (entity_sides) get_local_entity_int_value (get_pilot_entity (), INT_TYPE_SIDE);

	c = (float)count;
	t = (float)total;

	if (total > 0)
	{
		w = c / t;
	
		if (side != this_side)
		{
			w = -w;
		}
	
		switch (side)
		{
			case ENTITY_SIDE_BLUE_FORCE:
			{
				graphic = blue_bar_graphic;
	
				break;
			}
			case ENTITY_SIDE_RED_FORCE:
			{
				graphic = red_bar_graphic;
	
				break;
			}
			default:
			{
				debug_fatal ("CA_STAT: Invalid side %d for balance of power bar", side);
			}
		}
	
		draw_stats_page_colour_bar (obj, graphic, x1, y1, x2, y2, w);
	}
	
	if (total > 0)
	{	
		sprintf (s, "%.0f%%", (100.0 * c / t));
	}
	else
	{
		sprintf (s, "");
	}

	if (side == this_side)
	{
		set_ui_object_text (page_balance_sector_side_text_object [0], s);
	}
	else
	{
		set_ui_object_text (page_balance_sector_side_text_object [1], s);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_stats_page_objects (ui_object *obj, void *arg)
{
	set_ui_object_drawable (page_back_button, get_campaign_history_valid ());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_stats_page_balance_of_power_objects (ui_object *obj, void *arg)
{
	entity
		*this_force,
		*enemy_force;

	entity_sides
		this_side,
		enemy_side;

	int
		total,
		this_count,
		enemy_count;

	float
		y1, y2, dy;
		
	this_side = (entity_sides) get_local_entity_int_value (get_pilot_entity (), INT_TYPE_SIDE);

	this_force = get_local_force_entity (this_side);

	ASSERT (this_force);

	enemy_side = get_enemy_side (this_side);

	enemy_force = get_local_force_entity (enemy_side);

	ASSERT (enemy_force);

	dy = (BPOWER_MAIN_AREA_YMAX - BPOWER_MAIN_AREA_YMIN) / BPOWER_MAIN_AREA_ITEM_COUNT;

	y1 = BPOWER_MAIN_AREA_YMIN;
	y2 = y1 + dy;

	//
	// Attack Helicopters
	//

	this_count = get_local_force_entity_group_count (this_force, ENTITY_SUB_TYPE_GROUP_ATTACK_HELICOPTER);
	this_count += get_local_force_entity_group_count (this_force, ENTITY_SUB_TYPE_GROUP_MARINE_ATTACK_HELICOPTER);
	this_count += get_local_force_entity_group_count (this_force, ENTITY_SUB_TYPE_GROUP_ASSAULT_HELICOPTER);
	this_count += get_local_force_entity_group_count (this_force, ENTITY_SUB_TYPE_GROUP_MARINE_ASSAULT_HELICOPTER);
	this_count += get_local_force_entity_group_count (this_force, ENTITY_SUB_TYPE_GROUP_RECON_HELICOPTER);
	this_count += get_local_force_entity_group_count (this_force, ENTITY_SUB_TYPE_GROUP_RECON_ATTACK_HELICOPTER);

	enemy_count = get_local_force_entity_group_count (enemy_force, ENTITY_SUB_TYPE_GROUP_ATTACK_HELICOPTER);
	enemy_count += get_local_force_entity_group_count (enemy_force, ENTITY_SUB_TYPE_GROUP_MARINE_ATTACK_HELICOPTER);
	enemy_count += get_local_force_entity_group_count (enemy_force, ENTITY_SUB_TYPE_GROUP_ASSAULT_HELICOPTER);
	enemy_count += get_local_force_entity_group_count (enemy_force, ENTITY_SUB_TYPE_GROUP_MARINE_ASSAULT_HELICOPTER);
	enemy_count += get_local_force_entity_group_count (enemy_force, ENTITY_SUB_TYPE_GROUP_RECON_HELICOPTER);
	enemy_count += get_local_force_entity_group_count (enemy_force, ENTITY_SUB_TYPE_GROUP_RECON_ATTACK_HELICOPTER);

	total = this_count + enemy_count;

	draw_stats_page_unit_balance_of_power (obj, 0, this_side, this_count, total);
	draw_stats_page_unit_balance_of_power (obj, 0, enemy_side, enemy_count, total);

	//
	// Transport Helicopters
	//

	y1 += dy;
	y2 += dy;

	this_count = get_local_force_entity_group_count (this_force, ENTITY_SUB_TYPE_GROUP_MEDIUM_LIFT_TRANSPORT_HELICOPTER);
	this_count += get_local_force_entity_group_count (this_force, ENTITY_SUB_TYPE_GROUP_HEAVY_LIFT_TRANSPORT_HELICOPTER);

	enemy_count = get_local_force_entity_group_count (enemy_force, ENTITY_SUB_TYPE_GROUP_MEDIUM_LIFT_TRANSPORT_HELICOPTER);
	enemy_count += get_local_force_entity_group_count (enemy_force, ENTITY_SUB_TYPE_GROUP_HEAVY_LIFT_TRANSPORT_HELICOPTER);

	total = this_count + enemy_count;

	draw_stats_page_unit_balance_of_power (obj, 1, this_side, this_count, total);
	draw_stats_page_unit_balance_of_power (obj, 1, enemy_side, enemy_count, total);

	//
	// Attack Aircraft
	//

	y1 += dy;
	y2 += dy;

	this_count = get_local_force_entity_group_count (this_force, ENTITY_SUB_TYPE_GROUP_MULTI_ROLE_FIGHTER);
	this_count += get_local_force_entity_group_count (this_force, ENTITY_SUB_TYPE_GROUP_CARRIER_BORNE_ATTACK_AIRCRAFT);
	this_count += get_local_force_entity_group_count (this_force, ENTITY_SUB_TYPE_GROUP_CARRIER_BORNE_INTERCEPTOR);
	this_count += get_local_force_entity_group_count (this_force, ENTITY_SUB_TYPE_GROUP_CLOSE_AIR_SUPPORT_AIRCRAFT);

	enemy_count = get_local_force_entity_group_count (enemy_force, ENTITY_SUB_TYPE_GROUP_MULTI_ROLE_FIGHTER);
	enemy_count += get_local_force_entity_group_count (enemy_force, ENTITY_SUB_TYPE_GROUP_CARRIER_BORNE_ATTACK_AIRCRAFT);
	enemy_count += get_local_force_entity_group_count (enemy_force, ENTITY_SUB_TYPE_GROUP_CARRIER_BORNE_INTERCEPTOR);
	enemy_count += get_local_force_entity_group_count (enemy_force, ENTITY_SUB_TYPE_GROUP_CLOSE_AIR_SUPPORT_AIRCRAFT);

	total = this_count + enemy_count;

	draw_stats_page_unit_balance_of_power (obj, 2, this_side, this_count, total);
	draw_stats_page_unit_balance_of_power (obj, 2, enemy_side, enemy_count, total);

	//
	// Transport Aircraft
	//

	y1 += dy;
	y2 += dy;

	this_count = get_local_force_entity_group_count (this_force, ENTITY_SUB_TYPE_GROUP_MEDIUM_LIFT_TRANSPORT_AIRCRAFT);
	this_count += get_local_force_entity_group_count (this_force, ENTITY_SUB_TYPE_GROUP_HEAVY_LIFT_TRANSPORT_AIRCRAFT);

	enemy_count = get_local_force_entity_group_count (enemy_force, ENTITY_SUB_TYPE_GROUP_MEDIUM_LIFT_TRANSPORT_AIRCRAFT);
	enemy_count += get_local_force_entity_group_count (enemy_force, ENTITY_SUB_TYPE_GROUP_HEAVY_LIFT_TRANSPORT_AIRCRAFT);

	total = this_count + enemy_count;

	draw_stats_page_unit_balance_of_power (obj, 3, this_side, this_count, total);
	draw_stats_page_unit_balance_of_power (obj, 3, enemy_side, enemy_count, total);

	//
	// Ships
	//

	y1 += dy;
	y2 += dy;

	this_count = get_local_force_entity_group_count (this_force, ENTITY_SUB_TYPE_GROUP_ASSAULT_SHIP);
	this_count += get_local_force_entity_group_count (this_force, ENTITY_SUB_TYPE_GROUP_FRIGATE);
	this_count += get_local_force_entity_group_count (this_force, ENTITY_SUB_TYPE_GROUP_LANDING_CRAFT);

	enemy_count = get_local_force_entity_group_count (enemy_force, ENTITY_SUB_TYPE_GROUP_ASSAULT_SHIP);
	enemy_count += get_local_force_entity_group_count (enemy_force, ENTITY_SUB_TYPE_GROUP_FRIGATE);
	enemy_count += get_local_force_entity_group_count (enemy_force, ENTITY_SUB_TYPE_GROUP_LANDING_CRAFT);

	total = this_count + enemy_count;

	draw_stats_page_unit_balance_of_power (obj, 4, this_side, this_count, total);
	draw_stats_page_unit_balance_of_power (obj, 4, enemy_side, enemy_count, total);

	//
	// Air Defences
	//

	y1 += dy;
	y2 += dy;

	this_count = get_local_force_entity_group_count (this_force, ENTITY_SUB_TYPE_GROUP_ANTI_AIRCRAFT);

	enemy_count = get_local_force_entity_group_count (enemy_force, ENTITY_SUB_TYPE_GROUP_ANTI_AIRCRAFT);

	total = this_count + enemy_count;

	draw_stats_page_unit_balance_of_power (obj, 5, this_side, this_count, total);
	draw_stats_page_unit_balance_of_power (obj, 5, enemy_side, enemy_count, total);

	//
	// Armour
	//

	y1 += dy;
	y2 += dy;

	this_count = get_local_force_entity_group_count (this_force, ENTITY_SUB_TYPE_GROUP_PRIMARY_FRONTLINE);
	this_count += get_local_force_entity_group_count (this_force, ENTITY_SUB_TYPE_GROUP_SECONDARY_FRONTLINE);
	this_count += get_local_force_entity_group_count (this_force, ENTITY_SUB_TYPE_GROUP_SELF_PROPELLED_ARTILLERY);
	this_count += get_local_force_entity_group_count (this_force, ENTITY_SUB_TYPE_GROUP_SELF_PROPELLED_MLRS);

	enemy_count = get_local_force_entity_group_count (enemy_force, ENTITY_SUB_TYPE_GROUP_PRIMARY_FRONTLINE);
	enemy_count += get_local_force_entity_group_count (enemy_force, ENTITY_SUB_TYPE_GROUP_SECONDARY_FRONTLINE);
	enemy_count += get_local_force_entity_group_count (enemy_force, ENTITY_SUB_TYPE_GROUP_SELF_PROPELLED_ARTILLERY);
	enemy_count += get_local_force_entity_group_count (enemy_force, ENTITY_SUB_TYPE_GROUP_SELF_PROPELLED_MLRS);

	total = this_count + enemy_count;

	draw_stats_page_unit_balance_of_power (obj, 6, this_side, this_count, total);
	draw_stats_page_unit_balance_of_power (obj, 6, enemy_side, enemy_count, total);

	//
	// Sector Sides
	//

	this_count = get_local_entity_int_value (this_force, INT_TYPE_FORCE_SECTOR_COUNT);

	enemy_count = get_local_entity_int_value (enemy_force, INT_TYPE_FORCE_SECTOR_COUNT);

	total = this_count + enemy_count;

	draw_stats_page_sector_side_balance_of_power (obj, this_side, this_count, total);
	draw_stats_page_sector_side_balance_of_power (obj, enemy_side, enemy_count, total);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_page_objective_highlight_function (ui_object *obj, void *arg)
{
	entity
		*objective;

	entity_sub_types
		keysite_type;

	static char
		text [2048];

	if ((int) arg == BUTTON_STATE_DOWN)
	{
	
		objective = get_local_entity_safe_ptr (get_ui_object_item_number (obj));
	
		if (objective)
		{
			ASSERT (get_local_entity_type (objective) == ENTITY_TYPE_KEYSITE);
		
			keysite_type = get_local_entity_int_value (objective, INT_TYPE_ENTITY_SUB_TYPE);
		
			if (get_objective_briefing_text (objective, keysite_type, text))
			{
				ui_object_destroy_list_items (page_objective_description_list);
		
				add_to_pop_up_list_with_word_wrap (text, page_objective_description_list, NULL, 0, UI_FONT_ARIAL_10, ui_ingame_dead_text_colour);
			}
			else
			{
				debug_log ("CA_STAT: WARNING: trying to show objective briefing for %s (%d)", get_local_entity_type_name (objective), get_local_entity_index (objective));
			}
		}
	}
	else
	{
		// used to remove the list when item not highlighted
		//ui_object_destroy_list_items (page_objective_description_list);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_page_objective_select_function (ui_object *obj, void *arg)
{
	entity
		*objective;

	entity_sub_types
		sub_type;

	objective = get_local_entity_safe_ptr (get_ui_object_item_number (obj));

	if (objective)
	{
		ASSERT (get_local_entity_type (objective) == ENTITY_TYPE_KEYSITE);

		sub_type = get_local_entity_int_value (objective, INT_TYPE_ENTITY_SUB_TYPE);
	
		force_map_layer_control_object ((map_layer_control_types) keysite_database [sub_type].map_layer_type, TRUE);

		set_campaign_map_origin (objective);

		show_map_page ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void define_campaign_screen_stats_page_objects (void)
{
	float
		x1,
		y1,
		x2,
		y2,
		dy;

	ui_object
		*page;

	char
		string [256];

	int
		loop;

	solid_bar_graphic = create_texture_graphic ("graphics\\ui\\cohokum\\map\\blockprp.psd");
	red_bar_graphic = create_texture_graphic ("graphics\\ui\\cohokum\\map\\redbar.psd");
	blue_bar_graphic = create_texture_graphic ("graphics\\ui\\cohokum\\map\\bluebar.psd");

	/////////////////////////////////////////////////////////////////
	// Main Page Area
	/////////////////////////////////////////////////////////////////

	x1 = CAMPAIGN_INSET_PAGE_X1;
	y1 = CAMPAIGN_INSET_PAGE_Y1;
	x2 = CAMPAIGN_INSET_PAGE_X2;
	y2 = CAMPAIGN_INSET_PAGE_Y2;

	campaign_page [CAMPAIGN_PAGE_STATS] = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (campaign_screen),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_DRAWABLE (FALSE),
			UI_ATTR_DRAW_FUNCTION (update_stats_page_objects),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	page = campaign_page [CAMPAIGN_PAGE_STATS];

	x1 = 0.044;
	y1 = 0.148;
	x2 = 0.449;
	y2 = 0.220;

	create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (page),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXTURE_GRAPHIC (create_texture_graphic ("graphics\\ui\\cohokum\\map\\baltitle.psd")),
			UI_ATTR_END
		);

	sprintf (string, " %s:", get_trans ("Balance of Power"));
	
	x1 = 0.000;
	y1 = 0.172;
	x2 = 0.442;
	y2 = 0.220;

	create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (page),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_22),
			UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_TEXT (string),
			UI_ATTR_END
		);

	/////////////////////////////////////////////////////////////////
	// Balance Of Power

	x1 = 0.5;
	y1 = 0.15;
	x2 = 0.99;
	y2 = 0.69;

	page_balance_area = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (page),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_DRAW_FUNCTION (update_stats_page_balance_of_power_objects),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	x1 = 0.0;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 1.0;

	page_balance_overlay = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (page_balance_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXTURE_GRAPHIC (create_texture_graphic ("graphics\\ui\\cohokum\\map\\bpower.psd")),
			UI_ATTR_END
		);

	//
	// Sector sides
	//
	
	y1 = BPOWER_SIDE_AREA_YMIN;
	y2 = BPOWER_SIDE_AREA_YMAX;

	x1 = BPOWER_MAIN_AREA_TEXT_XMIN;
	x2 = (BPOWER_MAIN_AREA_TEXT_XMIN + BPOWER_MAIN_AREA_TEXT_XMAX) * 0.5;

	page_balance_sector_side_text_object [0] = create_ui_object
	(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (page_balance_overlay),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
	);

	x1 = (BPOWER_MAIN_AREA_TEXT_XMIN + BPOWER_MAIN_AREA_TEXT_XMAX) * 0.5;
	x2 = BPOWER_MAIN_AREA_TEXT_XMAX;

	page_balance_sector_side_text_object [1] = create_ui_object
	(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (page_balance_overlay),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
	);

	//
	// Unit balance of power
	//

	dy = (BPOWER_MAIN_AREA_YMAX - BPOWER_MAIN_AREA_YMIN) / BPOWER_MAIN_AREA_ITEM_COUNT;

	y1 = BPOWER_MAIN_AREA_YMIN;

	for (loop = 0; loop < BPOWER_MAIN_AREA_ITEM_COUNT; loop ++)
	{
		y2 = y1 + dy;

		x1 = BPOWER_MAIN_AREA_TEXT_XMIN;
		x2 = (BPOWER_MAIN_AREA_TEXT_XMIN + BPOWER_MAIN_AREA_TEXT_XMAX) * 0.5;

		page_balance_text_object [0][loop] = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (page_balance_overlay),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

		x1 = (BPOWER_MAIN_AREA_TEXT_XMIN + BPOWER_MAIN_AREA_TEXT_XMAX) * 0.5;
		x2 = BPOWER_MAIN_AREA_TEXT_XMAX;

		page_balance_text_object [1][loop] = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (page_balance_overlay),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

		y1 += dy;
	}

	/////////////////////////////////////////////////////////////////
	// Objectives
	
	x1 = 0.040;
	y1 = 0.340;
	x2 = 0.49;
	y2 = 0.334;

	sprintf (string, "%s:", get_trans ("Objectives"));
	
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

	x1 = 0.059;
	y1 = 0.367;
	x2 = 0.444;
	y2 = 0.614;

	page_objective_area = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (page),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	x1 = 0.0;
	y1 = 0.0;
	x2 = 0.5;
	y2 = 1.0;

	page_objective_name_list = create_ui_object
		(
			UI_TYPE_LIST_BOX,
			UI_ATTR_PARENT (page_objective_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_ITEM_NUMBER (ENTITY_INDEX_DONT_CARE),
			UI_ATTR_HIGHLIGHTED_FUNCTION (notify_page_objective_highlight_function),
			UI_ATTR_HIGHLIGHTED_NOTIFY_ON (NOTIFY_TYPE_BUTTON_EITHER),
			UI_ATTR_HIGHLIGHTED_FONT_TYPE (UI_FONT_ARIAL_14),
			UI_ATTR_HIGHLIGHTED_FONT_COLOUR (ui_ingame_highlight_text_colour.r, ui_ingame_highlight_text_colour.g, ui_ingame_highlight_text_colour.b, ui_ingame_highlight_text_colour.a),
			UI_ATTR_FUNCTION (notify_page_objective_select_function), 
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	set_ui_list_spacing_proportional_to_font (page_objective_name_list, -0.2);

	x1 = 0.5;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 1.0;

	page_objective_status_list = create_ui_object
		(
			UI_TYPE_LIST_BOX,
			UI_ATTR_PARENT (page_objective_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_ITEM_NUMBER (ENTITY_INDEX_DONT_CARE),
			UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_NONE),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	set_ui_list_spacing_proportional_to_font (page_objective_status_list, -0.2);

	x1 = 0.062;
	y1 = 0.710;
	x2 = 0.900;
	y2 = 0.910;

	page_objective_description_area = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_VSLIDER (0.0, 0.0, 5),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	set_common_slider_graphics (page_objective_description_area);

	x1 = 0.0;
	x2 = 0.9;
	y1 = 0.0;
	y2 = 1.0;

	page_objective_description_list = create_ui_object
			(
				UI_TYPE_LIST_BOX,
				UI_ATTR_PARENT (page_objective_description_area),
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
	// "Divider" graphics

	x1 = 0.038;
	y1 = 0.282;
	x2 = 0.455;
	y2 = 0.306;

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

	x1 = 0.038;
	y1 = 0.612;
	x2 = 0.455;
	y2 = 0.634;

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

static int response_to_group_remove_member (campaign_screen_messages message, entity *sender)
{
	if (get_ui_object_drawable (campaign_page [CAMPAIGN_PAGE_STATS]))
	{
		show_stats_page ();
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_stats_page_message_responses (void)
{
	campaign_screen_message_targets
		target;

	target = CAMPAIGN_SCREEN_TARGET_STATS_PAGE;

	campaign_screen_message_responses [target][CAMPAIGN_SCREEN_GROUP_REMOVE_MEMBER]	=	response_to_group_remove_member;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
