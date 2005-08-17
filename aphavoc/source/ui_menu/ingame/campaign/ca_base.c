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

#define BASE_3D_VIEW_MEDIUM_DISTANCE_INCREMENT	1.25

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static ui_object
	*base_page_title,
	*base_page_type_box,
	*base_page_sector_box,
	*base_page_status_box,
	*base_page_efficiency_box,
	*base_page_ammo_box,
	*base_page_fuel_box,
	*page_back_button;

static ui_object
	*page_3d_area, 
	*page_map_area, 
	*page_map_view_area,
	*page_map_view_mode_area,
	*page_map_toggle,
	*page_3d_toggle;

static map_dimension_type
	page_map_dimensions;

static float
	page_3d_heading,
	page_3d_pitch,
	page_3d_distance;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void show_base_page (entity *base, int force_update)
{
	entity
		*previous;

	vec3d
		*pos;

	int
		x, z;

	char
		s [128];

	ASSERT (base);

	ASSERT (get_local_entity_type (base) == ENTITY_TYPE_KEYSITE);

	if (force_update)
	{
		previous = NULL;
	}
	else
	{
		previous = get_local_entity_safe_ptr (get_ui_object_item_number (campaign_page [CAMPAIGN_PAGE_BASE]));
	}
	
	pos = get_local_entity_vec3d_ptr (base, VEC3D_TYPE_POSITION);

	ASSERT (pos);

	//
	// NAME
	//	

	set_ui_object_text (base_page_title, get_local_entity_string (base, STRING_TYPE_KEYSITE_NAME));

	//
	// TYPE
	//

	set_ui_object_text (base_page_type_box, get_trans (get_local_entity_string (base, STRING_TYPE_FULL_NAME)));

	//
	// LOCATION
	//

	get_x_sector (x, pos->x);
	get_z_sector (z, pos->z);

	sprintf (s, "[%03d, %03d]", x, z);

	set_ui_object_text (base_page_sector_box, s);

	//
	// 3D WINDOW
	//

	set_ui_object_item_number (page_3d_area, get_local_entity_index (base));

	if (base != previous)
	{
		page_3d_heading = 0.0;
		page_3d_pitch = (PI * 0.25);
		page_3d_distance = max (50.0, get_local_entity_float_value (base, FLOAT_TYPE_RECON_DISTANCE));
	}

	//
	// 2D MAP
	//

	set_ui_object_item_number (page_map_area, get_local_entity_index (base));

	if (base != previous)
	{
		page_map_dimensions.x = pos->x;
		page_map_dimensions.z = pos->z;

		page_map_dimensions.subject_entity = base;
	}

	//

	display_campaign_page (CAMPAIGN_PAGE_BASE, get_local_entity_index (base), TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_campaign_screen_base_page_objects (void)
{
	page_map_dimensions.x = MID_MAP_X;
	page_map_dimensions.z = MID_MAP_Z;
	page_map_dimensions.size = 8.0 * KILOMETRE;

	page_map_dimensions.subject_entity = NULL;
	page_map_dimensions.selected_entity = NULL;

	clear_map_mouse_over_object (&page_map_dimensions);

	set_ui_object_item_number (page_3d_area, ENTITY_INDEX_DONT_CARE);

	set_ui_object_item_number (page_map_area, ENTITY_INDEX_DONT_CARE);

	set_ui_object_drawable (page_3d_area, FALSE);

	set_ui_object_drawable (page_map_area, TRUE);

	set_ui_object_state (page_map_toggle, UI_OBJECT_STATE_ON);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_base_page_objects (ui_object *obj, void *arg)
{
	char
		s [128];

	entity
		*base;

	entity_sub_types
		sub_type;

	base = get_local_entity_safe_ptr (get_ui_object_item_number (campaign_page [CAMPAIGN_PAGE_BASE]));

	ASSERT (base);

	sub_type = get_local_entity_int_value (base, INT_TYPE_ENTITY_SUB_TYPE);

	//
	// STATUS 
	//

	{
		int
			status;

		status = get_local_entity_int_value (base, INT_TYPE_KEYSITE_USABLE_STATE);

		set_ui_object_text (base_page_status_box, get_trans (keysite_usable_state_names [status]));

		switch (status)
		{
			case KEYSITE_STATE_UNUSABLE:
			{
				set_ui_object_font_colour (base_page_status_box, ui_colour_red.r, ui_colour_red.g, ui_colour_red.b, ui_colour_red.a);

				break;
			}

			case KEYSITE_STATE_REPAIRING:
			{
				set_ui_object_font_colour (base_page_status_box, ui_colour_yellow.r, ui_colour_yellow.g, ui_colour_yellow.b, ui_colour_yellow.a);

				break;
			}

			default:
			{
				set_ui_object_font_colour (base_page_status_box, ui_colour_yellow.r, ui_colour_yellow.g, ui_colour_yellow.b, ui_colour_yellow.a);

				break;
			}
		}
	}

	//
	// Efficiency
	//

	{
		float
			efficiency;

		if (get_local_entity_float_value (base, FLOAT_TYPE_KEYSITE_MAXIMUM_STRENGTH) > 0.0)
		{
			efficiency = get_local_entity_float_value (base, FLOAT_TYPE_EFFICIENCY) * 100.0;

			sprintf (s, "%.0f%%", efficiency);
		}
		else
		{
			sprintf (s, "N/A", efficiency);
		}

		set_ui_object_text (base_page_efficiency_box, s);
	}

	//
	// Supplies
	//

	{
		float
			supplies;

		if (keysite_database [sub_type].report_ammo_level)
		{	
			supplies = get_local_entity_float_value (base, FLOAT_TYPE_AMMO_SUPPLY_LEVEL);

			sprintf (s, "%.0f%%", supplies);

			set_ui_object_text (base_page_ammo_box, s);
		}
		else
		{
			set_ui_object_text (base_page_ammo_box, "");
		}
		
		if (keysite_database [sub_type].report_fuel_level)
		{	
			supplies = get_local_entity_float_value (base, FLOAT_TYPE_FUEL_SUPPLY_LEVEL);

			sprintf (s, "%.0f%%", supplies);

			set_ui_object_text (base_page_fuel_box, s);
		}
		else
		{
			set_ui_object_text (base_page_fuel_box, "");
		}
	}

	//
	// Back Button
	//

	set_ui_object_drawable (page_back_button, get_campaign_history_valid ());
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_page_show_map (ui_object *obj, void *arg)
{
	set_ui_object_drawable (page_3d_area, FALSE);

	set_ui_object_drawable (page_map_area, TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_page_show_3d (ui_object *obj, void *arg)
{
	set_ui_object_drawable (page_3d_area, TRUE);

	set_ui_object_drawable (page_map_area, FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_page_map (ui_object *obj, void *arg)
{
	entity
		*en;

	en = get_local_entity_safe_ptr (get_ui_object_item_number (campaign_page [CAMPAIGN_PAGE_BASE]));

	ASSERT (en);
	
	draw_2d_map (obj, arg);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_page_3d_scene (ui_object *obj, void *arg)
{
	entity
		*en;

	viewpoint
		vp;

	vec3d
		*pos,
		vec;

	en = get_local_entity_safe_ptr (get_ui_object_item_number (obj));

	if (en)
	{
		pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

		ASSERT (pos);
		
		get_3d_unit_vector_from_heading_and_pitch (&vec, page_3d_heading, page_3d_pitch);

		vp.x = pos->x + (page_3d_distance * vec.x);
		vp.y = pos->y + (page_3d_distance * vec.y);
		vp.z = pos->z + (page_3d_distance * vec.z);
	
		invert_3d_vector (&vec);
	
		get_matrix3x3_from_unit_vec3d (vp.attitude, &vec);

		draw_campaign_screen_3d_scene (obj, &vp);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rotate_base_page_3d_scene_heading (float delta_heading)
{
	if (get_ui_object_drawable (campaign_page [CAMPAIGN_PAGE_BASE]))
	{
		page_3d_heading += rad (delta_heading);

		page_3d_heading = wrap_angle (page_3d_heading);
	}
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rotate_base_page_3d_scene_pitch (float delta_pitch)
{
	if (get_ui_object_drawable (campaign_page [CAMPAIGN_PAGE_BASE]))
	{
		page_3d_pitch += rad (delta_pitch);

		page_3d_pitch = bound (page_3d_pitch, PI * (1.0 / 12.0), PI * 0.5);
	}
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void zoom_base_page_3d_scene (int zoom)
{
	if (get_ui_object_drawable (campaign_page [CAMPAIGN_PAGE_BASE]))
	{
		if (zoom > 0)
		{
			page_3d_distance /= BASE_3D_VIEW_MEDIUM_DISTANCE_INCREMENT;
		}
		else if (zoom < 0)
		{
			page_3d_distance *= BASE_3D_VIEW_MEDIUM_DISTANCE_INCREMENT;
		}
	
		page_3d_distance = bound (page_3d_distance, 20.0, 4.0 * KILOMETRE);
	}
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef DEBUG

static void notify_base_destroy_button (ui_object *obj, void *arg)
{
	entity
		*en;

	entity_sides
		side,
		new_side;

	int
		sub_type;

	if (get_comms_model () != COMMS_MODEL_SERVER)
	{
		return;
	}
	
	en = get_local_entity_safe_ptr (get_ui_object_item_number (campaign_page [CAMPAIGN_PAGE_BASE]));

	ASSERT (en);

	sub_type = get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);

	if (keysite_database [sub_type].troop_insertion_target)
	{
		side = get_local_entity_int_value (en, INT_TYPE_SIDE);

		new_side = get_enemy_side (side);

//		create_troop_insertion_task (new_side, en, NULL, TRUE, 10.0, NULL, NULL);
		capture_keysite (en, new_side);
	}
	else
	{
		kill_client_server_entity (en);
	}
}

#endif
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void define_campaign_screen_base_page_objects (void)
{
	float
		x1,
		y1,
		x2,
		y2,
		ysize;

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

	campaign_page [CAMPAIGN_PAGE_BASE] = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (campaign_screen),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_CENTRE_TOP),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_DRAW_FUNCTION (update_base_page_objects),
			UI_ATTR_DRAWABLE (FALSE),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	page = campaign_page [CAMPAIGN_PAGE_BASE];

	/////////////////////////////////////////////////////////////////
	// Title
			
	x1 = 0.044;
	y1 = 0.089;

	base_page_title = create_ui_object
		(
			UI_TYPE_TEXT,
			UI_ATTR_PARENT (page),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_18),
			UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
			UI_ATTR_END
		);

	ysize = 0.06;

	y1 = 0.237;
	y2 = 0.31;

	/////////////////////////////////////////////////////////////////
	// Base Type Box

	x1 = 0.18;
	x2 = 0.2;

	sprintf (output, "%s :", get_trans ("Type"));
			
	create_ui_object	
			(
				UI_TYPE_TEXT,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (output),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_END
			);

	x1 = 0.2;
	x2 = 0.5;

	base_page_type_box = create_ui_object
			(
				UI_TYPE_TEXT,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (""),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_END
			);

	/////////////////////////////////////////////////////////////////
	// Base Sector Box

	y1 += ysize;
	y2 += ysize;

	x1 = 0.18;
	x2 = 0.2;

	sprintf (output, "%s :", get_trans ("Sector"));
			
	create_ui_object
			(
				UI_TYPE_TEXT,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (output),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_END
			);

	x1 = 0.2;
	x2 = 0.5;

	base_page_sector_box = create_ui_object
			(
				UI_TYPE_TEXT,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (""),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_END
			);

	/////////////////////////////////////////////////////////////////
	// Status Box

	y1 += ysize;
	y2 += ysize;

	x1 = 0.18;
	x2 = 0.2;

	sprintf (output, "%s :", get_trans ("Status"));
			
	create_ui_object
			(
				UI_TYPE_TEXT,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (output),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_END
			);

	x1 = 0.2;
	x2 = 0.5;

	base_page_status_box = create_ui_object
			(
				UI_TYPE_TEXT,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (""),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_END
			);

	/////////////////////////////////////////////////////////////////
	// Efficiency Box

	y1 += ysize;
	y2 += ysize;

	x1 = 0.18;
	x2 = 0.2;

	sprintf (output, "%s :", get_trans ("Efficiency"));
			
	create_ui_object
			(
				UI_TYPE_TEXT,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (output),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_END
			);

	x1 = 0.2;
	x2 = 0.5;

	base_page_efficiency_box = create_ui_object
			(
				UI_TYPE_TEXT,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (""),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_END
			);

	/////////////////////////////////////////////////////////////////
	// Ammo Box

	y1 += ysize;
	y2 += ysize;

	x1 = 0.18;
	x2 = 0.2;

	sprintf (output, "%s :", get_trans ("Ammo"));
			
	create_ui_object
			(
				UI_TYPE_TEXT,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (output),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_END
			);

	x1 = 0.2;
	x2 = 0.5;

	base_page_ammo_box = create_ui_object
			(
				UI_TYPE_TEXT,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (""),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_END
			);

	/////////////////////////////////////////////////////////////////
	// Fuel Box

	y1 += ysize;
	y2 += ysize;

	x1 = 0.18;
	x2 = 0.2;

	sprintf (output, "%s :", get_trans ("Fuel"));
			
	create_ui_object
			(
				UI_TYPE_TEXT,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (output),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_END
			);

	x1 = 0.2;
	x2 = 0.5;

	base_page_fuel_box = create_ui_object
			(
				UI_TYPE_TEXT,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (""),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_END
			);

	/////////////////////////////////////////////////////////////////
	// 2D MAP / 3D VIEW toggles

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

	/////////////////////////////////////////////////////////////////
	// 2D MAP / 3D VIEW toggles

	x1 = 0.5;
	y1 = 0.67;
	x2 = 1.0;
	y2 = 0.71;

	page_map_view_mode_area = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXTURE_GRAPHIC (create_texture_graphic ("graphics\\ui\\cohokum\\map\\maptabs.psd")),
				UI_ATTR_END
			);

	// 2d map toggle

	x1 = 0.0;
	y1 = 0.0;
	x2 = 0.33;
	y2 = 1.0;

	page_map_toggle = create_ui_object
			(
				UI_TYPE_RADIO,
				UI_ATTR_PARENT (page_map_view_mode_area),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (get_trans ("Map")),
				UI_ATTR_FUNCTION (notify_page_show_map),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_FONT_COLOUR (ui_ingame_live_text_colour.r, ui_ingame_live_text_colour.g, ui_ingame_live_text_colour.b, ui_ingame_live_text_colour.a),
				UI_ATTR_HIGHLIGHTED_FONT_COLOUR (ui_ingame_highlight_text_colour.r, ui_ingame_highlight_text_colour.g, ui_ingame_highlight_text_colour.b, ui_ingame_highlight_text_colour.a),
				UI_ATTR_SELECTED_FONT_COLOUR (ui_ingame_selected_text_colour.r, ui_ingame_selected_text_colour.g, ui_ingame_selected_text_colour.b, ui_ingame_selected_text_colour.a),
				UI_ATTR_HIGHLIGHTABLE (TRUE),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	// 3d view toggle

	x1 = 0.33;
	y1 = 0.0;
	x2 = 0.66;
	y2 = 1.0;

	page_3d_toggle = create_ui_object
			(
				UI_TYPE_RADIO,
				UI_ATTR_PARENT (page_map_view_mode_area),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (get_trans ("View")),
				UI_ATTR_FUNCTION (notify_page_show_3d),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_FONT_COLOUR (ui_ingame_live_text_colour.r, ui_ingame_live_text_colour.g, ui_ingame_live_text_colour.b, ui_ingame_live_text_colour.a),
				UI_ATTR_HIGHLIGHTED_FONT_COLOUR (ui_ingame_highlight_text_colour.r, ui_ingame_highlight_text_colour.g, ui_ingame_highlight_text_colour.b, ui_ingame_highlight_text_colour.a),
				UI_ATTR_SELECTED_FONT_COLOUR (ui_ingame_selected_text_colour.r, ui_ingame_selected_text_colour.g, ui_ingame_selected_text_colour.b, ui_ingame_selected_text_colour.a),
				UI_ATTR_HIGHLIGHTABLE (TRUE),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	/////////////////////////////////////////////////////////////////
	// 3d Preview Area
		
	x1 = 0.01;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 0.99;

	page_3d_area = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (page_map_view_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_DRAW_FUNCTION (draw_page_3d_scene),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	/////////////////////////////////////////////////////////////////
	// Map Area
		
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

	#ifdef DEBUG

	x1 = 0.1;
	y1 = 0.8;
	x2 = 0.4;
	y2 = 0.9;

	create_ui_object
			(
				UI_TYPE_BUTTON,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT ("Destroy\nCapture"),
				UI_ATTR_FUNCTION (notify_base_destroy_button),
				UI_ATTR_END
			);

	#endif

	/////////////////////////////////////////////////////////////////
	// "Divider" graphics

	x1 = 0.022;
	y1 = 0.206;
	x2 = 0.475;
	y2 = 0.229;

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
	x2 = 0.475;
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

	/////////////////////////////////////////////////////////////////
	// Map Objects

	define_map_objects (page_map_area, &page_map_dimensions, draw_page_map, campaign_map_left_click_function, map_centralise_function, &campaign_screen_full_screen_map);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_base_destroyed (campaign_screen_messages message, entity *sender)
{
	if (get_local_entity_safe_index (sender) == get_ui_object_item_number (campaign_page [CAMPAIGN_PAGE_BASE]))
	{
		if (get_ui_object_drawable (campaign_page [CAMPAIGN_PAGE_BASE]))
		{
			//
			// Not sure yet.... For now display the map page
			//

			show_map_page ();
		}

		set_ui_object_item_number (campaign_page [CAMPAIGN_PAGE_BASE], ENTITY_INDEX_DONT_CARE);
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_force_update (campaign_screen_messages message, entity *sender)
{
	if (get_ui_object_drawable (campaign_page [CAMPAIGN_PAGE_BASE]))
	{
		ASSERT (sender);

		show_base_page (sender, TRUE);
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_base_page_message_responses (void)
{
	campaign_screen_message_targets
		target;

	target = CAMPAIGN_SCREEN_TARGET_BASE_PAGE;

	campaign_screen_message_responses [target][CAMPAIGN_SCREEN_BASE_DESTROYED]		=	response_to_base_destroyed;

	campaign_screen_message_responses [target][CAMPAIGN_SCREEN_FORCE_UPDATE]		=	response_to_force_update;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


