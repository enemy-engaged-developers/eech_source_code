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

#define GROUP_3D_VIEW_MEDIUM_DISTANCE_INCREMENT	1.25

#define GROUP_3D_VIEW_MEDIUM_ANGLE_INCREMENT		rad (45.0f)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static ui_object
	*group_page_title,
	*group_page_type_box,
	*group_page_kills_box,
	*group_page_losses_box,
	*group_page_base_box,
	*group_page_mission_box,
	*group_page_pilot_lock_box,
	*group_page_member_area,
	*group_page_member_list,
	*page_back_button;

static ui_object
	*view_button,
	*page_3d_area, 
	*page_map_area, 
	*page_map_view_area,
	*page_map_view_mode_area,
	*page_map_toggle,
	*page_3d_toggle;

ui_object
	*gunship_accept_button;

static map_dimension_type
	page_map_dimensions;

static float
	page_3d_heading = 0.0,
	page_3d_pitch = 0.0,
	page_3d_distance = 100.0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_member_list (ui_object *obj, void *arg);

static void update_member_list (ui_object *obj, void *arg);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int show_group_page (entity *group, int force_update)
{
	static char
		buffer [192];

	entity
		*member,
		*company,
		*division,
		*previous,
		*base,
		*pilot,
		*mission;

	ui_object
		*new_item,
		*first_item;

	int
		return_value;

	vec3d
		*pos;
				
	ASSERT (group);

	ASSERT (get_local_entity_type (group) == ENTITY_TYPE_GROUP);

	if (force_update)
	{
		previous = NULL;
	}
	else
	{
		previous = get_local_entity_safe_ptr (get_ui_object_item_number (campaign_page [CAMPAIGN_PAGE_GROUP]));
	}

	return_value = ENTITY_INDEX_DONT_CARE;

	ASSERT (get_local_entity_first_child (group, LIST_TYPE_MEMBER));

	if (group != previous)
	{
		set_ui_object_drawable (gunship_accept_button, FALSE);

		set_ui_object_item_number (gunship_accept_button, ENTITY_INDEX_DONT_CARE);
	}

	//
	// NAME
	//	

	company = get_local_entity_parent (group, LIST_TYPE_DIVISION);

	ASSERT (company);

	division = get_local_entity_parent (company, LIST_TYPE_DIVISION);

	ASSERT (division);

	sprintf (buffer, "%s,\n%s,\n%s",
				get_local_entity_string (group, STRING_TYPE_DIVISION_NAME),
				get_local_entity_string (company, STRING_TYPE_DIVISION_NAME),
				get_local_entity_string (division, STRING_TYPE_DIVISION_NAME));

	set_ui_object_text (group_page_title, buffer);

	//
	// TYPE
	//

	set_ui_object_text (group_page_type_box, get_trans (get_local_entity_string (group, STRING_TYPE_GROUP_SHORT_NAME)));

	//
	// KILLS
	//

	sprintf (buffer, "%d", get_local_entity_int_value (group, INT_TYPE_KILLS));

	set_ui_object_text (group_page_kills_box, buffer);

	//
	// LOSSES
	//

	sprintf (buffer, "%d", get_local_entity_int_value (group, INT_TYPE_LOSSES));

	set_ui_object_text (group_page_losses_box, buffer);

	//
	// BASE ATTACHED TO
	//

	base = get_local_entity_parent (group, LIST_TYPE_KEYSITE_GROUP);

	ASSERT (base);

	if (get_local_entity_type (base) == ENTITY_TYPE_KEYSITE)
	{
		set_ui_object_text (group_page_base_box, get_local_entity_string (base, STRING_TYPE_KEYSITE_NAME));

		set_ui_object_item_number (group_page_base_box, get_local_entity_index (base));
	}
	else
	{
		set_ui_object_text (group_page_base_box, "");

		set_ui_object_item_number (group_page_base_box, ENTITY_INDEX_DONT_CARE);
	}

	//
	// MISSION GROUP IS CURRENTLY DOING 
	//

	mission = get_local_group_primary_task (group);

	if ((mission) && (get_local_entity_int_value (mission, INT_TYPE_VISIBLE_TASK)))
	{
		set_ui_object_text (group_page_mission_box, get_trans (get_local_entity_string (mission, STRING_TYPE_SHORT_DISPLAY_NAME)));

		set_ui_object_item_number (group_page_mission_box, get_local_entity_index (mission));
	}
	else
	{
		set_ui_object_text (group_page_mission_box, "");

		set_ui_object_item_number (group_page_mission_box, ENTITY_INDEX_DONT_CARE);
	}

	//
	// GROUP MEMBER LIST
	//
	// (Automatically select first available member, or group leader if none)
	//

	// reset group list width
	set_ui_object_virtual_x_size (group_page_member_area, 0.368);
	set_ui_object_virtual_x_size (group_page_member_list, 0.9f);

	ui_object_destroy_list_items (group_page_member_list);

	set_ui_object_vslider_virtual_position (get_ui_object_vslider (group_page_member_area), 0.0);

	set_ui_object_item_number (group_page_member_list, ENTITY_INDEX_DONT_CARE);

	member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

	ASSERT (member);

	first_item = NULL;

	while (member)
	{
		sprintf (buffer, "1-%d %s", get_local_entity_int_value (member, INT_TYPE_GROUP_MEMBER_ID), get_local_entity_string (member, STRING_TYPE_FULL_NAME));

		if (get_local_entity_int_value (member, INT_TYPE_IDENTIFY_HELICOPTER))
		{
			pilot = get_local_entity_first_child (member, LIST_TYPE_AIRCREW);

			if (pilot)
			{
				sprintf (buffer, "1-%d %s (%s)",
								get_local_entity_int_value (member, INT_TYPE_GROUP_MEMBER_ID),
								get_local_entity_string (member, STRING_TYPE_FULL_NAME),
								get_local_entity_string (pilot, STRING_TYPE_PILOTS_NAME));

				// if player is in this group, resize group list width
				set_ui_object_virtual_x_size (group_page_member_area, 0.570);
				set_ui_object_virtual_x_size (group_page_member_list, 0.9f);
			}
		}
	
		if (get_local_entity_int_value (member, INT_TYPE_GROUP_LEADER))
		{
			first_item = add_to_pop_up_list (buffer, group_page_member_list, NULL, get_local_entity_index (member), UI_FONT_ARIAL_10, ui_colour_yellow);

			new_item = first_item;
		}
		else
		{
			new_item = add_to_pop_up_list (buffer, group_page_member_list, NULL, get_local_entity_index (member), UI_FONT_ARIAL_10, ui_ingame_live_text_colour);
		}

		set_ui_mouse_over_entity_function (new_item);

		if (get_ui_object_item_number (gunship_accept_button) == ENTITY_INDEX_DONT_CARE)
		{
			update_member_list (new_item, NULL);
		}

		member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
	}

	resize_pop_up_list (group_page_member_list);

	//
	// If no member selected - select group leader
	//

	if (get_ui_object_item_number (gunship_accept_button) == ENTITY_INDEX_DONT_CARE)
	{
		ASSERT (first_item);

		update_member_list (first_item, NULL);
	}

	//
	// 2D MAP
	//

	if (group != previous)
	{
		page_map_dimensions.subject_entity = NULL;

		member = get_group_page_member_list_current_entity ();

		if (member)
		{
			pos = get_local_entity_vec3d_ptr (member, VEC3D_TYPE_POSITION);

			ASSERT (pos);

			page_map_dimensions.x = pos->x;
			page_map_dimensions.z = pos->z;

			page_map_dimensions.subject_entity = member;
		}
	}

	ASSERT (group);

	display_campaign_page (CAMPAIGN_PAGE_GROUP, get_local_entity_safe_index (group), TRUE);

	return return_value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_campaign_screen_group_page_objects (void)
{
	page_map_dimensions.x = MID_MAP_X;
	page_map_dimensions.z = MID_MAP_Z;
	page_map_dimensions.size = 4.0 * KILOMETRE;

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

entity *get_group_page_member_list_current_entity (void)
{
	int
		index;

	index = get_ui_object_item_number (group_page_member_list);

	return get_local_entity_safe_ptr (index);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_group_page_objects (ui_object *obj, void *arg)
{
	entity
		*group;

	group = get_local_entity_safe_ptr (get_ui_object_item_number (campaign_page [CAMPAIGN_PAGE_GROUP]));

	if (!group)
	{
		display_campaign_page (CAMPAIGN_PAGE_MAP, ENTITY_INDEX_DONT_CARE, FALSE);

		return;
	}

	if (get_gunship_entity ())
	{
		set_ui_object_drawable (gunship_accept_button, FALSE);

		set_ui_object_item_number (gunship_accept_button, ENTITY_INDEX_DONT_CARE);
	}

	//
	// PLAYER LOCK
	//

	{
		entity
			*pilot;
			
		pilot = get_local_entity_parent (group, LIST_TYPE_PILOT_LOCK);

		if (pilot)
		{
			set_ui_object_text (group_page_pilot_lock_box, get_local_entity_string (pilot, STRING_TYPE_PILOTS_NAME));
		}
		else
		{
			set_ui_object_text (group_page_pilot_lock_box, "");
		}
	}

	set_ui_object_drawable (page_back_button, get_campaign_history_valid ());
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_base_selected (ui_object *obj, void *arg)
{
	int
		index;
		
	index = get_ui_object_item_number (obj);

	if (index != ENTITY_INDEX_DONT_CARE)
	{
		show_base_page (get_local_entity_ptr (index), FALSE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_mission_selected (ui_object *obj, void *arg)
{
	int
		index;
		
	index = get_ui_object_item_number (obj);

	if (index != ENTITY_INDEX_DONT_CARE)
	{
		show_briefing_page (get_local_entity_ptr (index), FALSE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_member_list (ui_object *obj, void *arg)
{
	int
		index;

	entity
		*en;

	index = get_ui_object_item_number (obj);

	en = get_local_entity_safe_ptr (index);

	set_ui_object_item_number (group_page_member_list, index);

	set_ui_object_state (obj, UI_OBJECT_STATE_ON);

	//
	// Clear Gunship Accept Button
	//
	
	set_ui_object_drawable (gunship_accept_button, FALSE);
	
	set_ui_object_item_number (gunship_accept_button, ENTITY_INDEX_DONT_CARE);

	set_ui_object_state (gunship_accept_button, UI_OBJECT_STATE_OFF);

	//
	// 3D VIEW
	//

	set_ui_object_item_number (page_3d_area, index);

	if (en)
	{
		page_3d_distance = get_local_entity_float_value (en, FLOAT_TYPE_CHASE_VIEW_MIN_DISTANCE);

		page_3d_heading = 0.0;
		page_3d_pitch = GROUP_3D_VIEW_MEDIUM_ANGLE_INCREMENT;
	}

	//
	// Set currently selected member
	//

	if ((en) && (!get_gunship_entity ()))
	{
		if (en != get_currently_selected_member ())
		{
			if (get_group_player_suitability_status (get_local_entity_parent (en, LIST_TYPE_MEMBER)))
			{
				if (get_local_entity_suitable_for_player (get_local_entity_ptr (index), get_pilot_entity ()))
				{
					if (!get_local_entity_int_value (get_session_entity (), INT_TYPE_SESSION_COMPLETE))
					{
						set_ui_object_drawable (gunship_accept_button, TRUE);
	
						set_ui_object_item_number (gunship_accept_button, index);
					}
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_member_list (ui_object *obj, void *arg)
{
	int
		index;

	entity
		*en;

	vec3d
		*pos;

	index = get_ui_object_item_number (obj);

	en = get_local_entity_safe_ptr (index);

	update_member_list (obj, arg);

	if (en)
	{
		//
		// 2D MAP
		//
	
		pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);
	
		ASSERT (pos);
	
		page_map_dimensions.x = pos->x;
		page_map_dimensions.z = pos->z;
	
		page_map_dimensions.subject_entity = en;
		
		set_ui_object_item_number (page_map_area, index);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_member_accept_button (ui_object *obj, void *arg)
{
	int
		index;

	entity
		*en,
		*mission;

	index = get_ui_object_item_number (obj);

	en = get_local_entity_safe_ptr (index);

	//
	// Set currently selected member
	//

	if ((en) && (!get_gunship_entity ()))
	{
		if (get_group_player_suitability_status (get_local_entity_parent (en, LIST_TYPE_MEMBER)))
		{
			if (get_local_entity_suitable_for_player (get_local_entity_ptr (index), get_pilot_entity ()))
			{
				set_currently_selected_member (index);

				update_member_list (obj, NULL);

				if (!get_currently_selected_mission ())
				{
					//
					// Automatically change list mode to Missions
					//
			
					show_mission_list (NULL, NULL);
	
					mission = get_local_entity_primary_task (en);

					if ((mission) && (get_local_entity_int_value (mission, INT_TYPE_TASK_STATE) == TASK_STATE_ASSIGNED))
					{
						//
						// Automatically Show Briefing page
						//

						show_briefing_page (mission, FALSE);
					}
				}

				return;
			}
		}
	}

	//
	// Button entity is invalid
	//

	set_ui_object_drawable (gunship_accept_button, FALSE);

	set_ui_object_item_number (gunship_accept_button, ENTITY_INDEX_DONT_CARE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_member_view_button (ui_object *obj, void *arg)
{
	int
		index;

	entity
		*en;

	index = get_ui_object_item_number (group_page_member_list);

	en = get_local_entity_safe_ptr (index);

	if (en)
	{
		ASSERT (get_local_entity_int_value (en, INT_TYPE_VIEWABLE));
		
		notify_local_entity (ENTITY_MESSAGE_SET_CAMERA_ACTION, get_camera_entity (), NULL, CAMERA_ACTION_CINEMATIC);

		set_external_view_entity (en);

		toggle_in_flight_game_modes (NULL);
	}
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

	en = get_local_entity_safe_ptr (get_ui_object_item_number (campaign_page [CAMPAIGN_PAGE_GROUP]));

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

void rotate_group_page_3d_scene_heading (float delta_heading)
{
	if (get_ui_object_drawable (campaign_page [CAMPAIGN_PAGE_GROUP]))
	{
		page_3d_heading += rad (delta_heading);

		page_3d_heading = wrap_angle (page_3d_heading);
	}
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rotate_group_page_3d_scene_pitch (float delta_pitch)
{
	if (get_ui_object_drawable (campaign_page [CAMPAIGN_PAGE_GROUP]))
	{
		page_3d_pitch += rad (delta_pitch);

		page_3d_pitch = bound (page_3d_pitch, PI * (1.0 / 8.0), PI * 0.5);
	}
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void zoom_group_page_3d_scene (int zoom)
{
	if (get_ui_object_drawable (campaign_page [CAMPAIGN_PAGE_GROUP]))
	{
		if (zoom > 0)
		{
			page_3d_distance /= GROUP_3D_VIEW_MEDIUM_DISTANCE_INCREMENT;
		}
		else if (zoom < 0)
		{
			page_3d_distance *= GROUP_3D_VIEW_MEDIUM_DISTANCE_INCREMENT;
		}
	
		page_3d_distance = bound (page_3d_distance, 12.0, 1.2 * KILOMETRE);
	}
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void define_campaign_screen_group_page_objects (void)
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

	campaign_page [CAMPAIGN_PAGE_GROUP] = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (campaign_screen),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_DRAWABLE (FALSE),
			UI_ATTR_DRAW_FUNCTION (update_group_page_objects),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	page = campaign_page [CAMPAIGN_PAGE_GROUP];

	/////////////////////////////////////////////////////////////////
	// Title
			
	x1 = 0.044;
	y1 = 0.044;
	x2 = 0.45;
	y2 = 0.20;

	group_page_title = create_ui_object
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

	/////////////////////////////////////////////////////////////////

	x_start = 0.23;

	x_mid = 0.24;

	x_end = 0.5;

	ysize = 0.04;

	yinc = 0.05f;

	/////////////////////////////////////////////////////////////////
	// Group Type Box

	x1 = x_start;
	y1 = 0.24;
	x2 = x_mid;
	y2 = y1 + ysize;

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

	x1 = x_mid;
	y1 = 0.24;
	x2 = x_end;
	y2 = y1 + ysize;

	group_page_type_box = create_ui_object
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
	// Group Kills Box

	x1 = x_start;
	x2 = x_mid;

	y1 += yinc;
	y2 = y1 + ysize;

	sprintf (output, "%s :", get_trans ("Kills"));

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

	x1 = x_mid;
	x2 = x_end;

	group_page_kills_box = create_ui_object
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
	// Group Losses Box

	x1 = x_start;
	x2 = x_mid;

	y1 += yinc;
	y2 = y1 + ysize;

	sprintf (output, "%s :", get_trans ("Losses"));

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

	x1 = x_mid;
	x2 = x_end;

	group_page_losses_box = create_ui_object
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
	// Group Base Box

	x1 = x_start;
	x2 = x_mid;

	y1 += yinc;
	y2 = y1 + ysize;

	sprintf (output, "%s :", get_trans ("Base"));
	
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

	x1 = x_mid;
	x2 = x_end;

	group_page_base_box = create_ui_object
			(
				UI_TYPE_BUTTON,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (""),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_FUNCTION (notify_base_selected),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	set_ui_mouse_over_entity_function (group_page_base_box);

	/////////////////////////////////////////////////////////////////
	// Group Mission Box

	x1 = x_start;
	x2 = x_mid;

	y1 += yinc;
	y2 = y1 + ysize;

	sprintf (output, "%s :", get_trans ("Mission"));
	
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

	x1 = x_mid;
	x2 = x_end;

	group_page_mission_box = create_ui_object
			(
				UI_TYPE_BUTTON,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (""),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_FUNCTION (notify_mission_selected),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	set_ui_mouse_over_entity_function (group_page_mission_box);

	/////////////////////////////////////////////////////////////////
	// Group Pilot Lock Box

	x1 = x_start;
	x2 = x_mid;

	y1 += yinc;
	y2 = y1 + ysize;

	sprintf (output, "%s :", get_trans ("Locked By"));

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

	x1 = x_mid;
	x2 = x_end;

	group_page_pilot_lock_box = create_ui_object
			(
				UI_TYPE_TEXT,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (""),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
				UI_ATTR_FONT_COLOUR (ui_ingame_selected_text_colour.r, ui_ingame_selected_text_colour.g, ui_ingame_selected_text_colour.b, ui_ingame_selected_text_colour.a),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_END
			);

	/////////////////////////////////////////////////////////////////
	// Member List Box

	x1 = 0.044;
	y1 = 0.680;
	x2 = 0.45;
	y2 = 0.730;

	sprintf (output, "%s:", get_trans ("Group"));

	create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (page),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
			UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
			UI_ATTR_TEXT (output),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	x1 = 0.1f;
	y1 = 0.730;
	x2 = 0.468;
	y2 = 0.955;

	group_page_member_area = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_VSLIDER (0, 300, 12),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	set_common_slider_graphics (group_page_member_area);

	x1 = 0.0;
	y1 = 0.0;
	x2 = 0.9f;
	y2 = 1.0;

	group_page_member_list = create_ui_object
			(
				UI_TYPE_LIST_BOX,
				UI_ATTR_PARENT (group_page_member_area),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_FUNCTION (notify_member_list),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_END
			);

	/////////////////////////////////////////////////////////////////
	// 2D MAP / 3D VIEW area

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

	// Full View Button
		
	x1 = 0.66;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 1.0;

	view_button = create_ui_object
			(
				UI_TYPE_BUTTON,
				UI_ATTR_PARENT (page_map_view_mode_area),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (get_trans ("Camera")),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_FUNCTION (notify_member_view_button),
				UI_ATTR_FONT_COLOUR (ui_ingame_live_text_colour.r, ui_ingame_live_text_colour.g, ui_ingame_live_text_colour.b, ui_ingame_live_text_colour.a),
				UI_ATTR_HIGHLIGHTED_FONT_COLOUR (ui_ingame_highlight_text_colour.r, ui_ingame_highlight_text_colour.g, ui_ingame_highlight_text_colour.b, ui_ingame_highlight_text_colour.a),
				UI_ATTR_SELECTED_FONT_COLOUR (ui_ingame_selected_text_colour.r, ui_ingame_selected_text_colour.g, ui_ingame_selected_text_colour.b, ui_ingame_selected_text_colour.a),
				UI_ATTR_HIGHLIGHTABLE (TRUE),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	/////////////////////////////////////////////////////////////////
	// 3d Preview Area
	
	x1 = 0.01f;
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
		
	x1 = 0.01f;
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

	///////////////////////////////////////////////////
	// Accept Button
		
	x1 = 0.283;
	y1 = 0.949;
	x2 = 0.699;
	y2 = 1.0;

	gunship_accept_button = create_ui_object
		(
			UI_TYPE_BUTTON,
			UI_ATTR_PARENT (page),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT (get_trans ("Accept Gunship")),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
			UI_ATTR_FONT_COLOUR (ui_ingame_live_text_colour.r, ui_ingame_live_text_colour.g, ui_ingame_live_text_colour.b, ui_ingame_live_text_colour.a),
			UI_ATTR_HIGHLIGHTED_FONT_COLOUR (ui_ingame_highlight_text_colour.r, ui_ingame_highlight_text_colour.g, ui_ingame_highlight_text_colour.b, ui_ingame_highlight_text_colour.a),
			UI_ATTR_SELECTED_FONT_COLOUR (ui_ingame_selected_text_colour.r, ui_ingame_selected_text_colour.g, ui_ingame_selected_text_colour.b, ui_ingame_selected_text_colour.a),
			UI_ATTR_HIGHLIGHTABLE (TRUE),
			UI_ATTR_FUNCTION (notify_member_accept_button),
			UI_ATTR_TEXTURE_GRAPHIC (create_texture_graphic ("graphics\\ui\\cohokum\\map\\acptbtn.psd")),
			UI_ATTR_END
		);

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
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_group_destroyed (campaign_screen_messages message, entity *sender)
{
	if (get_local_entity_safe_index (sender) == get_ui_object_item_number (campaign_page [CAMPAIGN_PAGE_GROUP]))
	{
		if (get_ui_object_drawable (campaign_page [CAMPAIGN_PAGE_GROUP]))
		{
			show_map_page ();
		}
		
		set_ui_object_item_number (campaign_page [CAMPAIGN_PAGE_GROUP], ENTITY_INDEX_DONT_CARE);
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_group_change_base (campaign_screen_messages message, entity *sender)
{
	if (get_ui_object_drawable (campaign_page [CAMPAIGN_PAGE_GROUP]))
	{
		if (get_local_entity_safe_index (sender) == get_ui_object_item_number (campaign_page [CAMPAIGN_PAGE_GROUP]))
		{
			show_group_page (sender, TRUE);
		}
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_group_add_member (campaign_screen_messages message, entity *sender)
{
	entity
		*group;
		
	if (get_ui_object_drawable (campaign_page [CAMPAIGN_PAGE_GROUP]))
	{
		group = get_local_entity_parent (sender, LIST_TYPE_MEMBER);

		ASSERT (group);
	
		if (get_local_entity_safe_index (group) == get_ui_object_item_number (campaign_page [CAMPAIGN_PAGE_GROUP]))
		{
			show_group_page (group, TRUE);
		}
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_group_remove_member (campaign_screen_messages message, entity *sender)
{
	entity
		*group;

	group = sender;
		
	ASSERT (group);

	ASSERT (get_local_entity_type (group) == ENTITY_TYPE_GROUP);
	
	if (get_local_entity_safe_index (group) == get_ui_object_item_number (campaign_page [CAMPAIGN_PAGE_GROUP]))
	{
		if (get_ui_object_drawable (campaign_page [CAMPAIGN_PAGE_GROUP]))
		{
			//
			// Force member list / map / 3d view update
			//

			if (get_local_entity_first_child (group, LIST_TYPE_MEMBER))
			{
				show_group_page (group, TRUE);
			}
			else
			{
				show_map_page ();
			}
		}
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_mission_assigned (campaign_screen_messages message, entity *sender)
{
	entity
		*group;
		
	if (get_ui_object_drawable (campaign_page [CAMPAIGN_PAGE_GROUP]))
	{
		group = get_local_entity_safe_ptr (get_ui_object_item_number (campaign_page [CAMPAIGN_PAGE_GROUP]));

		if (get_local_group_primary_task (group) == sender)
		{
			show_group_page (group, TRUE);
		}
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_mission_completed (campaign_screen_messages message, entity *sender)
{
	entity
		*group;
		
	if (get_ui_object_drawable (campaign_page [CAMPAIGN_PAGE_GROUP]))
	{
		group = get_local_entity_safe_ptr (get_ui_object_item_number (campaign_page [CAMPAIGN_PAGE_GROUP]));

		if (get_local_group_primary_task (group) == sender)
		{
			show_group_page (group, TRUE);
		}
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_force_update (campaign_screen_messages message, entity *sender)
{
	if (get_ui_object_drawable (campaign_page [CAMPAIGN_PAGE_GROUP]))
	{
		ASSERT (sender);

		show_group_page (sender, TRUE);
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_group_page_message_responses (void)
{
	campaign_screen_message_targets
		target;

	target = CAMPAIGN_SCREEN_TARGET_GROUP_PAGE;

	campaign_screen_message_responses [target][CAMPAIGN_SCREEN_GROUP_DESTROYED]		=	response_to_group_destroyed;

	campaign_screen_message_responses [target][CAMPAIGN_SCREEN_GROUP_CHANGE_BASE]		=	response_to_group_change_base;

	campaign_screen_message_responses [target][CAMPAIGN_SCREEN_GROUP_ADD_MEMBER]		=	response_to_group_add_member;

	campaign_screen_message_responses [target][CAMPAIGN_SCREEN_GROUP_REMOVE_MEMBER]	=	response_to_group_remove_member;

	campaign_screen_message_responses [target][CAMPAIGN_SCREEN_MISSION_ASSIGNED]		=	response_to_mission_assigned;

	campaign_screen_message_responses [target][CAMPAIGN_SCREEN_MISSION_COMPLETED]		=	response_to_mission_completed;

	campaign_screen_message_responses [target][CAMPAIGN_SCREEN_FORCE_UPDATE]			=	response_to_force_update;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



