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

struct CAMPAIGN_SCREEN_WEAPON_LOADING_BUTTON_TYPE
{
	int
		valid;

	ui_object
		*button_ptr;
};

typedef struct CAMPAIGN_SCREEN_WEAPON_LOADING_BUTTON_TYPE campaign_screen_weapon_loading_button_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static ui_object
	*page_back_button,
	*page_member_area,
	*page_member_list,
	*page_default_payload_list, 
	*page_auw_text,
	*page_fuel_text,
	*page_fuel_gauge,
	*page_repairing_text,
	*page_repairing_gauge,
	*weapon_loading_page [NUM_GUNSHIP_TYPES];

static campaign_screen_weapon_loading_button_type
	weapon_loading_button_list [NUM_GUNSHIP_TYPES][NUM_WEAPON_LOADING_HARDPOINT_TYPES];

static texture_graphic
	*bar_graphic;

static char
	buffer [192];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void rebuild_default_payload_list (entity *en);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void show_weapon_loading_page (entity *group, int force_update)
{
	gunship_types
		type;

	int
		loop;

	entity
		*en,
		*pilot,
		*member;

	ui_object
		*new_item;
		
	ASSERT (group);

	//
	// Reconstruct List
	//

	if (force_update)
	{
		ui_object_destroy_list_items (page_member_list);

		set_ui_object_vslider_virtual_position (get_ui_object_vslider (page_member_area), 0.0);

		set_ui_object_item_number (page_member_list, ENTITY_INDEX_DONT_CARE);

		member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

		ASSERT (member);

		while (member)
		{
			sprintf (buffer, "1-%d %s", get_local_entity_int_value (member, INT_TYPE_GROUP_MEMBER_ID), get_local_entity_string (member, STRING_TYPE_SHORT_DISPLAY_NAME));

			pilot = get_local_entity_first_child (member, LIST_TYPE_AIRCREW);

			if (pilot)
			{
				sprintf (buffer, "1-%d %s (%s)",
								get_local_entity_int_value (member, INT_TYPE_GROUP_MEMBER_ID),
								get_local_entity_string (member, STRING_TYPE_SHORT_DISPLAY_NAME),
								get_local_entity_string (pilot, STRING_TYPE_PILOTS_NAME));
			}
	
			if (get_local_entity_int_value (member, INT_TYPE_GUNSHIP_TYPE) < NUM_GUNSHIP_TYPES)
			{	
				new_item = add_to_pop_up_list (buffer, page_member_list, NULL, get_local_entity_safe_index (member), UI_FONT_ARIAL_14, ui_ingame_live_text_colour);
		
				set_ui_mouse_over_entity_function (new_item);

				set_ui_object_notify_on (new_item, NOTIFY_TYPE_BUTTON_DOWN);
			}
			else
			{
				new_item = add_to_pop_up_list (buffer, page_member_list, NULL, get_local_entity_safe_index (member), UI_FONT_ARIAL_14, ui_ingame_dead_text_colour);

				set_ui_object_notify_on (new_item, NOTIFY_TYPE_NONE);
			}
			
			if (member == get_gunship_entity ())
			{
				set_ui_object_state (new_item, UI_OBJECT_STATE_ON);

				set_ui_object_item_number (page_member_list, get_local_entity_safe_index (member));
			}

			member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
		}

		resize_pop_up_list (page_member_list);
	}

	//
	// Show weapon loading page
	//

	for (loop = 0; loop < NUM_GUNSHIP_TYPES; loop ++)
	{
		set_ui_object_drawable (weapon_loading_page [loop], FALSE);

		set_ui_object_item_number (weapon_loading_page [loop], ENTITY_INDEX_DONT_CARE);
	}

	en = get_local_entity_safe_ptr (get_ui_object_item_number (page_member_list));

	ASSERT (en);

	type = get_local_entity_int_value (en, INT_TYPE_GUNSHIP_TYPE);

	if (get_local_entity_int_value (en, INT_TYPE_GUNSHIP_TYPE) < NUM_GUNSHIP_TYPES)
	{
		weapon_loading_update_currently_selected_weapons (en);

		set_ui_object_drawable (weapon_loading_page [type], TRUE);

		set_ui_object_item_number (weapon_loading_page [type], get_local_entity_safe_index (en));
	}

	//
	// Default payload list
	//

	rebuild_default_payload_list (en);

	display_campaign_page (CAMPAIGN_PAGE_WEAPON_LOADING, get_local_entity_safe_index (group), TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_campaign_screen_weapon_loading_page_objects (void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_weapon_loading_page_objects (ui_object *obj, void *arg)
{
	set_ui_object_drawable (page_back_button, get_campaign_history_valid ());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_weapon_loading_gauge (ui_object *obj, float level)
{
	real_colour
		colour;

	float
		sx1, sx2,
		sy1, sy2,
		xmin, xmax,
		ymin, ymax;

	ASSERT (obj);

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
	
	sx1 = xmin;
	sx2 = xmax;

	sy1 = ymin;
	sy2 = ymax;

	sx2 = (xmin + (level * (xmax - xmin)));

	ui_draw_texture_graphic (sx1, sy1, sx2, sy2, bar_graphic, colour);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_member_list (ui_object *obj, void *arg)
{
	int
		index;

	entity
		*en,
		*group;

	index = get_ui_object_item_number (obj);

	en = get_local_entity_safe_ptr (index);

	ASSERT (en);
	
	set_ui_object_item_number (page_member_list, index);

	group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

	ASSERT (group);

	show_weapon_loading_page (group, FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_weapon_loading_page_change_weapon (ui_object *obj, void *arg)
{
	entity
		*en;

	ui_object
		*gunship_page;

	int
		hardpoint;

	ASSERT (obj);

	hardpoint = get_ui_object_item_number2 (obj);

	gunship_page = get_ui_object_parent (obj);

	ASSERT (gunship_page);

	en = get_local_entity_safe_ptr (get_ui_object_item_number (gunship_page));

	ASSERT (en);

	if (get_helicopter_allowed_to_rearm (en))
	{
		weapon_loading_select_next_weapon (en, hardpoint);
	}

	rebuild_default_payload_list (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_weapon_loading_gunship_page (ui_object *obj, void *arg)
{
	entity
		*en;

	gunship_types
		gunship;

	weapon_loading_hardpoint_types
		hardpoint;

	int
		count,
		fixed,
		auw,
		weapon_type;

	float
		mass;

	ui_object
		*button_object;

	rgb_colour
		*col;

	ASSERT (obj);

	en = get_local_entity_safe_ptr (get_ui_object_item_number (obj));

	ASSERT (en);

	gunship = get_local_entity_int_value (en, INT_TYPE_GUNSHIP_TYPE);

	ASSERT (gunship < NUM_GUNSHIP_TYPES);

	if (get_helicopter_allowed_to_rearm (en))
	{
		fixed = FALSE;
	}
	else
	{
		fixed = TRUE;
	}

	//
	// Set button text
	//	

	for (hardpoint = 0; hardpoint < NUM_WEAPON_LOADING_HARDPOINT_TYPES; hardpoint ++)
	{
		if (weapon_loading_button_list [gunship][hardpoint].valid)
		{
			button_object = weapon_loading_button_list [gunship][hardpoint].button_ptr;

			weapon_type = weapon_loading_get_current_hardpoint_weapon (gunship, hardpoint);

			//
			// Set Text
			//
			
			if (weapon_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
			{
				count = get_weapon_loading_hardpoint_weapon_count (en, hardpoint, weapon_type);

				sprintf (buffer, "%dx %s", count, weapon_database [weapon_type].weapon_loading_list_name);
			}
			else
			{
				sprintf (buffer, "%s", weapon_database [weapon_type].weapon_loading_list_name);
			}

			set_ui_object_text (button_object, buffer);

			//
			// Set Button Attributes
			//

			if ((fixed) || (weapon_loading_get_valid_weapon_count (en, hardpoint) < 2))
			{
				set_ui_object_notify_on (button_object, NOTIFY_TYPE_NONE);

				set_ui_object_highlightable (button_object, FALSE);

				col = &ui_ingame_dead_text_colour;

				set_ui_object_font_colour (button_object, col->r, col->g, col->b, col->a);
			}
			else
			{
				set_ui_object_notify_on (button_object, NOTIFY_TYPE_BUTTON_DOWN);

				set_ingame_ui_object_mouse_over_properties (button_object);
			}
		}
	}

	//
	// All-Up-Weight (player only)
	//

	if (en == get_gunship_entity ())
	{
		mass = set_flight_dynamics_mass ();

		convert_float_to_int (mass, &auw);

		sprintf (buffer, "%s: %dkg", get_trans ("All Up Weight"), auw);

		set_ui_object_text (page_auw_text, buffer);
	}
	else
	{
		set_ui_object_text (page_auw_text, "");
	}

	//
	// Fuel Page (player only)
	//
	
	if (en == get_gunship_entity ())
	{
		sprintf (buffer, " %.0fkg", get_current_flight_dynamics_fuel_weight ());

		set_ui_object_text (page_fuel_gauge, buffer);

		set_ui_object_drawable (page_fuel_text, TRUE);

		set_ui_object_drawable (page_fuel_gauge, TRUE);
		
		draw_weapon_loading_gauge (page_fuel_gauge, get_dynamics_normalised_fuel_value ());
	}
	else
	{
		set_ui_object_drawable (page_fuel_text, FALSE);

		set_ui_object_drawable (page_fuel_gauge, FALSE);
	}

	//
	// Damage Page (player only)
	//

	set_ui_object_drawable (page_repairing_text, FALSE);

	set_ui_object_drawable (page_repairing_gauge, FALSE);
		
	if (en == get_gunship_entity ())
	{
		int
			repair_index;

		float
			level,
			repair_time;

		if (current_flight_dynamics->repairing_damage != DYNAMICS_DAMAGE_NONE)
		{
			repair_index = get_dynamics_damage_currently_repairing_type ();

			repair_time = dynamics_damage_database [repair_index].repair_time;

			if (repair_time == 0.0)
			{		
				level = 1.0;
			}
			else
			{
				level = 1.0 - (current_flight_dynamics->damage_repair_time / repair_time);

				level = bound (level, 0.0, 1.0);
			}
		
			sprintf (buffer, " %s", get_trans (dynamics_damage_database [repair_index].name));

			set_ui_object_text (page_repairing_gauge, buffer);

			set_ui_object_drawable (page_repairing_text, TRUE);

			set_ui_object_drawable (page_repairing_gauge, TRUE);
		
			draw_weapon_loading_gauge (page_repairing_gauge, level);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rebuild_default_payload_list (entity *en)
{
	int
		fixed;

	ui_object
		*new_item;

	ASSERT (en);

	ui_object_destroy_list_items (page_default_payload_list);

	if (get_local_entity_int_value (en, INT_TYPE_GUNSHIP_TYPE) < NUM_GUNSHIP_TYPES)
	{	
		fixed = (!get_helicopter_allowed_to_rearm (en));
	}
	else
	{
		fixed = TRUE;
	}

	//

	sprintf (buffer, "%s", get_trans ("Air to Ground"));

	new_item = add_to_pop_up_list (buffer, page_default_payload_list, NULL, INT_TYPE_AIR_TO_SURFACE_WEAPON_CONFIG_TYPE, UI_FONT_ARIAL_14, ui_ingame_dead_text_colour);

	if (!fixed)
	{
		set_ingame_ui_object_mouse_over_properties (new_item);

		set_ui_object_notify_on (new_item, NOTIFY_TYPE_BUTTON_DOWN);
	}
	else
	{
		set_ui_object_notify_on (new_item, NOTIFY_TYPE_NONE);
	}

	//

	sprintf (buffer, "%s", get_trans ("Air to Air"));

	new_item = add_to_pop_up_list (buffer, page_default_payload_list, NULL, INT_TYPE_AIR_TO_AIR_WEAPON_CONFIG_TYPE, UI_FONT_ARIAL_14, ui_ingame_dead_text_colour);

	if (!fixed)
	{
		set_ingame_ui_object_mouse_over_properties (new_item);

		set_ui_object_notify_on (new_item, NOTIFY_TYPE_BUTTON_DOWN);
	}
	else
	{
		set_ui_object_notify_on (new_item, NOTIFY_TYPE_NONE);
	}

	//

	sprintf (buffer, "%s", get_trans ("Scout"));

	new_item = add_to_pop_up_list (buffer, page_default_payload_list, NULL, INT_TYPE_SCOUT_WEAPON_CONFIG_TYPE, UI_FONT_ARIAL_14, ui_ingame_dead_text_colour);

	if (!fixed)
	{
		set_ingame_ui_object_mouse_over_properties (new_item);

		set_ui_object_notify_on (new_item, NOTIFY_TYPE_BUTTON_DOWN);
	}
	else
	{
		set_ui_object_notify_on (new_item, NOTIFY_TYPE_NONE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_default_payload_list (ui_object *obj, void *arg)
{
	entity
		*en;

	int
		config_type;

	en = get_local_entity_safe_ptr (get_ui_object_item_number (page_member_list));
	
	if (en)
	{
		if (get_helicopter_allowed_to_rearm (en))
		{
			config_type = get_ui_object_item_number (obj);

			if (config_type != ENTITY_INDEX_DONT_CARE)
			{	
				ASSERT (
							(config_type == INT_TYPE_AIR_TO_SURFACE_WEAPON_CONFIG_TYPE) ||
							(config_type == INT_TYPE_AIR_TO_AIR_WEAPON_CONFIG_TYPE) ||
							(config_type == INT_TYPE_SCOUT_WEAPON_CONFIG_TYPE)
						);
		
				set_client_server_entity_int_value (en, INT_TYPE_WEAPON_CONFIG_TYPE, get_local_entity_int_value (en, config_type));
		
				weapon_loading_update_currently_selected_weapons (en);

				if (en == get_gunship_entity ())
				{
					set_flight_dynamics_mass ();
				}
			}
		}

		rebuild_default_payload_list (en);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void define_weapon_loading_button_object (ui_object *gunship_page, float x, float y, gunship_types gunship, weapon_loading_hardpoint_types hardpoint)
{
	float
		rx,
		ry;

	rx = 0.18;
	ry = 0.03;

	ASSERT (!weapon_loading_button_list [gunship][hardpoint].valid);

	weapon_loading_button_list [gunship][hardpoint].valid = TRUE;

	weapon_loading_button_list [gunship][hardpoint].button_ptr = create_ui_object
	(
		UI_TYPE_BUTTON,
		UI_ATTR_PARENT (gunship_page),
		UI_ATTR_VIRTUAL_POSITION (x - rx, y - ry),
		UI_ATTR_VIRTUAL_SIZE (rx + rx, ry + ry),
		UI_ATTR_ITEM_NUMBER (gunship),
		UI_ATTR_ITEM_NUMBER2 (hardpoint),
		UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
		UI_ATTR_FUNCTION (notify_weapon_loading_page_change_weapon),
		UI_ATTR_FONT_TYPE (UI_FONT_ITALIC_ARIAL_16),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_END
	);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void define_campaign_screen_weapon_loading_page_objects (void)
{
	float
		x1,
		y1,
		x2,
		y2;

	char
		string [256];

	int
		loop,
		gunship,
		hardpoint;

	ui_object
		*page,
		*gunship_page;

	bar_graphic = create_texture_graphic ("graphics\\ui\\cohokum\\map\\fuelrep.psd");

	/////////////////////////////////////////////////////////////////
	// Main Page Area
	/////////////////////////////////////////////////////////////////

	x1 = CAMPAIGN_INSET_PAGE_X1;
	y1 = CAMPAIGN_INSET_PAGE_Y1;
	x2 = CAMPAIGN_INSET_PAGE_X2;
	y2 = CAMPAIGN_INSET_PAGE_Y2;

	campaign_page [CAMPAIGN_PAGE_WEAPON_LOADING] = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (campaign_screen),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_DRAWABLE (FALSE),
			UI_ATTR_DRAW_FUNCTION (update_weapon_loading_page_objects),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	page = campaign_page [CAMPAIGN_PAGE_WEAPON_LOADING];

	//
	// Clear buttons
	//
	
	for (gunship = 0; gunship < NUM_GUNSHIP_TYPES; gunship ++)
	{
		for (hardpoint = 0; hardpoint < NUM_WEAPON_LOADING_HARDPOINT_TYPES; hardpoint ++)
		{
			weapon_loading_button_list [gunship][hardpoint].valid = FALSE;
			weapon_loading_button_list [gunship][hardpoint].button_ptr = NULL;
		}
	}

	/////////////////////////////////////////////////////////////////
	// Gunship Pages

	x1 = 0.4;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 1.0;

	for (loop = 0; loop < NUM_GUNSHIP_TYPES; loop ++)
	{
		weapon_loading_page [loop] = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (page),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_DRAWABLE (FALSE),
			UI_ATTR_DRAW_FUNCTION (update_weapon_loading_gunship_page),
			UI_ATTR_END
		);
	}

	/////////////////////////////////////////////////////////////////
	// APACHE PAGE 
	/////////////////////////////////////////////////////////////////

	gunship = GUNSHIP_TYPE_APACHE;

	gunship_page = weapon_loading_page [gunship];

	set_ui_object_texture_graphic (gunship_page, create_texture_graphic ("graphics\\ui\\cohokum\\map\\payapa.psd"));

	define_weapon_loading_button_object (gunship_page, 0.5, 0.705, gunship, WEAPON_LOADING_HARDPOINT_GUN1);

	define_weapon_loading_button_object (gunship_page, 0.5, 0.818, gunship, WEAPON_LOADING_HARDPOINT_INNER);

	define_weapon_loading_button_object (gunship_page, 0.5, 0.888, gunship, WEAPON_LOADING_HARDPOINT_OUTER);

	define_weapon_loading_button_object (gunship_page, 0.5, 0.959, gunship, WEAPON_LOADING_HARDPOINT_WINGTIP);

	/////////////////////////////////////////////////////////////////
	// HAVOC PAGE 
	/////////////////////////////////////////////////////////////////

	gunship = GUNSHIP_TYPE_HAVOC;

	gunship_page = weapon_loading_page [gunship];

	set_ui_object_texture_graphic (gunship_page, create_texture_graphic ("graphics\\ui\\cohokum\\map\\payhav.psd"));

	define_weapon_loading_button_object (gunship_page, 0.5, 0.664, gunship, WEAPON_LOADING_HARDPOINT_GUN1);

	define_weapon_loading_button_object (gunship_page, 0.5, 0.714, gunship, WEAPON_LOADING_HARDPOINT_GUN2);

	define_weapon_loading_button_object (gunship_page, 0.5, 0.816, gunship, WEAPON_LOADING_HARDPOINT_INNER);

	define_weapon_loading_button_object (gunship_page, 0.5, 0.887, gunship, WEAPON_LOADING_HARDPOINT_OUTER);

	/////////////////////////////////////////////////////////////////
	// COMANCHE PAGE 
	/////////////////////////////////////////////////////////////////

	gunship = GUNSHIP_TYPE_COMANCHE;

	gunship_page = weapon_loading_page [gunship];

	set_ui_object_texture_graphic (gunship_page, create_texture_graphic ("graphics\\ui\\cohokum\\map\\paycom.psd"));

	define_weapon_loading_button_object (gunship_page, 0.5, 0.599, gunship, WEAPON_LOADING_HARDPOINT_GUN1);

	define_weapon_loading_button_object (gunship_page, 0.5, 0.724, gunship, WEAPON_LOADING_HARDPOINT_INNER);

	define_weapon_loading_button_object (gunship_page, 0.5, 0.795, gunship, WEAPON_LOADING_HARDPOINT_MID);

	define_weapon_loading_button_object (gunship_page, 0.5, 0.866, gunship, WEAPON_LOADING_HARDPOINT_OUTER);

	define_weapon_loading_button_object (gunship_page, 0.5, 0.938, gunship, WEAPON_LOADING_HARDPOINT_WINGTIP);

	/////////////////////////////////////////////////////////////////
	// HOKUM PAGE
	/////////////////////////////////////////////////////////////////

	gunship = GUNSHIP_TYPE_HOKUM;

	gunship_page = weapon_loading_page [gunship];

	set_ui_object_texture_graphic (gunship_page, create_texture_graphic ("graphics\\ui\\cohokum\\map\\payhok.psd"));

	define_weapon_loading_button_object (gunship_page, 0.5, 0.650, gunship, WEAPON_LOADING_HARDPOINT_GUN1);

	define_weapon_loading_button_object (gunship_page, 0.5, 0.699, gunship, WEAPON_LOADING_HARDPOINT_GUN2);

	define_weapon_loading_button_object (gunship_page, 0.5, 0.814, gunship, WEAPON_LOADING_HARDPOINT_INNER);

	define_weapon_loading_button_object (gunship_page, 0.5, 0.888, gunship, WEAPON_LOADING_HARDPOINT_OUTER);

	////Moje 030519 Start
	/////////////////////////////////////////////////////////////////
	// BLACKHAWK PAGE 
	/////////////////////////////////////////////////////////////////

	gunship = GUNSHIP_TYPE_BLACKHAWK;

	gunship_page = weapon_loading_page [gunship];

	set_ui_object_texture_graphic (gunship_page, create_texture_graphic ("graphics\\ui\\cohokum\\map\\paybla.psd"));

	define_weapon_loading_button_object (gunship_page, 0.5, 0.818, gunship, WEAPON_LOADING_HARDPOINT_INNER);

	define_weapon_loading_button_object (gunship_page, 0.5, 0.888, gunship, WEAPON_LOADING_HARDPOINT_OUTER);
	////Moje 030519 End
	////Moje 030613 start
	/////////////////////////////////////////////////////////////////
	// HIND PAGE 
	/////////////////////////////////////////////////////////////////

	gunship = GUNSHIP_TYPE_HIND;

	gunship_page = weapon_loading_page [gunship];

	set_ui_object_texture_graphic (gunship_page, create_texture_graphic ("graphics\\ui\\cohokum\\map\\payhin.psd"));

	define_weapon_loading_button_object (gunship_page, 0.5, 0.705, gunship, WEAPON_LOADING_HARDPOINT_GUN1);

	define_weapon_loading_button_object (gunship_page, 0.5, 0.818, gunship, WEAPON_LOADING_HARDPOINT_INNER);

	define_weapon_loading_button_object (gunship_page, 0.5, 0.888, gunship, WEAPON_LOADING_HARDPOINT_OUTER);

	define_weapon_loading_button_object (gunship_page, 0.5, 0.959, gunship, WEAPON_LOADING_HARDPOINT_WINGTIP);
	////Moje 030613 end

	////Moje 030817 start
	/////////////////////////////////////////////////////////////////
	// AH64A PAGE 
	/////////////////////////////////////////////////////////////////

	gunship = GUNSHIP_TYPE_AH64A;

	gunship_page = weapon_loading_page [gunship];

	set_ui_object_texture_graphic (gunship_page, create_texture_graphic ("graphics\\ui\\cohokum\\map\\payah6.psd"));

	define_weapon_loading_button_object (gunship_page, 0.5, 0.705, gunship, WEAPON_LOADING_HARDPOINT_GUN1);

	define_weapon_loading_button_object (gunship_page, 0.5, 0.818, gunship, WEAPON_LOADING_HARDPOINT_INNER);

	define_weapon_loading_button_object (gunship_page, 0.5, 0.888, gunship, WEAPON_LOADING_HARDPOINT_OUTER);

	define_weapon_loading_button_object (gunship_page, 0.5, 0.959, gunship, WEAPON_LOADING_HARDPOINT_WINGTIP);

	/////////////////////////////////////////////////////////////////
	// KA50 PAGE
	/////////////////////////////////////////////////////////////////

	gunship = GUNSHIP_TYPE_KA50;

	gunship_page = weapon_loading_page [gunship];

	set_ui_object_texture_graphic (gunship_page, create_texture_graphic ("graphics\\ui\\cohokum\\map\\payka5.psd"));

	define_weapon_loading_button_object (gunship_page, 0.5, 0.650, gunship, WEAPON_LOADING_HARDPOINT_GUN1);

	define_weapon_loading_button_object (gunship_page, 0.5, 0.699, gunship, WEAPON_LOADING_HARDPOINT_GUN2);

	define_weapon_loading_button_object (gunship_page, 0.5, 0.814, gunship, WEAPON_LOADING_HARDPOINT_INNER);

	define_weapon_loading_button_object (gunship_page, 0.5, 0.888, gunship, WEAPON_LOADING_HARDPOINT_OUTER);

	////Moje 030816 end
	
	/////////////////////////////////////////////////////////////////
	// Member List Box

	x1 = 0.045;
	y1 = 0.026;
	x2 = 0.405;
	y2 = 0.176;

	sprintf (string, "%s:", get_trans ("Gunship"));

	create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (string),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	x1 = 0.048;
	y1 = 0.125;
	x2 = 0.500;
	y2 = 0.368;

	page_member_area = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_VSLIDER (0, 300, 12),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	set_common_slider_graphics (page_member_area);

	x1 = 0.0;
	y1 = 0.0;
	x2 = 0.9;
	y2 = 1.0;

	page_member_list = create_ui_object
			(
				UI_TYPE_LIST_BOX,
				UI_ATTR_PARENT (page_member_area),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_FUNCTION (notify_member_list),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_14),
				UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_DOWN),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	/////////////////////////////////////////////////////////////////
	// Default load-outs buttons

	x1 = 0.044;
	y1 = 0.347;
	x2 = 0.38;
	y2 = 0.404;

	sprintf (string, "%s:", get_trans ("Default Payload"));

	create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (string),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	x1 = 0.048;
	y1 = 0.417;
	x2 = 0.38;
	y2 = 0.576;

	page_default_payload_list = create_ui_object
			(
				UI_TYPE_LIST_BOX,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_FUNCTION (notify_default_payload_list),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_14),
				UI_ATTR_ITEM_NUMBER (ENTITY_INDEX_DONT_CARE),
				UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_DOWN),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	/////////////////////////////////////////////////////////////////
	// Current Gunship Mass

	x1 = 0.056;
	y1 = 0.897;
	x2 = 0.358;
	y2 = 0.928;

	page_auw_text = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_14),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	/////////////////////////////////////////////////////////////////
	// Fuel Gauge

	x1 = 0.044;
	y1 = 0.615;
	x2 = 0.348;
	y2 = 0.652;

	sprintf (string, "%s:", get_trans ("Fuel"));

	page_fuel_text = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
				UI_ATTR_TEXT (string),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	x1 = 0.054;
	y1 = 0.662;
	x2 = 0.358;
	y2 = 0.711;

	page_fuel_gauge = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXTURE_GRAPHIC (create_texture_graphic ("graphics\\ui\\cohokum\\map\\smallbar.psd")),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
				UI_ATTR_END
			);

	/////////////////////////////////////////////////////////////////
	// Repairing Gauge

	x1 = 0.044;
	y1 = 0.757;
	x2 = 0.348;
	y2 = 0.800;

	sprintf (string, "%s:", get_trans ("Repairing"));
	
	page_repairing_text = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
				UI_ATTR_TEXT (string),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	x1 = 0.054;
	y1 = 0.801;
	x2 = 0.358;
	y2 = 0.850;

	page_repairing_gauge = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXTURE_GRAPHIC (create_texture_graphic ("graphics\\ui\\cohokum\\map\\smallbar.psd")),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
				UI_ATTR_END
			);

	/////////////////////////////////////////////////////////////////
	// "Divider" graphics

	x1 = 0.021;
	y1 = 0.035;
	x2 = 0.389;
	y2 = 0.058;

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

	x1 = 0.021;
	y1 = 0.321;
	x2 = 0.389;
	y2 = 0.344;

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

	x1 = 0.021;
	y1 = 0.576;
	x2 = 0.389;
	y2 = 0.599;

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

static int response_to_player_leave_mission (campaign_screen_messages message, entity *sender)
{
	if (get_ui_object_drawable (campaign_page [CAMPAIGN_PAGE_WEAPON_LOADING]))
	{
		show_map_page ();
	}

	remove_campaign_page_from_history (CAMPAIGN_PAGE_WEAPON_LOADING);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_weapon_loading_page_message_responses (void)
{
	campaign_screen_message_targets
		target;

	target = CAMPAIGN_SCREEN_TARGET_WEAPON_LOADING_PAGE;

	campaign_screen_message_responses [target][CAMPAIGN_SCREEN_PLAYER_LEAVE_MISSION]		=	response_to_player_leave_mission;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




