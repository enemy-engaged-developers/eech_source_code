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
#include "ai/highlevl/reaction.h" // Jabberwock 031007

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static ui_object
	*page_map_area,
	*page_back_button;

static map_dimension_type
	page_map_dimensions;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void show_map_page (void)
{
	display_campaign_page (CAMPAIGN_PAGE_MAP, ENTITY_INDEX_DONT_CARE, TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_campaign_screen_map_page_objects (void)
{
	float
		x1, z1,
		x2, z2;
		
	set_active_map_object (NULL);

	ASSERT (get_session_entity ());

	x1 = get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_POPULATION_X_MIN) - (5.0 * KILOMETRE);
	z1 = get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_POPULATION_Z_MIN) - (5.0 * KILOMETRE);

	x2 = get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_POPULATION_X_MAX) + (5.0 * KILOMETRE);
	z2 = get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_POPULATION_Z_MAX) + (5.0 * KILOMETRE);

	page_map_dimensions.x = (x1 + x2) * 0.5;
	page_map_dimensions.z = (z1 + z2) * 0.5;

	page_map_dimensions.size = max (x2 - x1, z2 - z1) * 1.5;

	page_map_dimensions.subject_entity = NULL;
	page_map_dimensions.selected_entity = NULL;

	clear_map_mouse_over_object (&page_map_dimensions);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_page_map (ui_object *obj, void *arg)
{
	draw_2d_map (obj, arg);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_map_page_objects (ui_object *obj, void *arg)
{
	set_ui_object_drawable (page_back_button, get_campaign_history_valid ());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void campaign_map_left_click_function (ui_object *obj, void *arg)
{
	entity
		*en,
		*group;

	map_dimension_type
		*map_dimensions;

	entity_sides
		side;

	ASSERT (obj);

	if ((int)arg != BUTTON_STATE_DOWN)
	{
		return;
	}

	map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (obj);

	ASSERT (map_dimensions);

	map_dimensions->selected_entity = NULL;

	side = get_local_entity_int_value (get_pilot_entity (), INT_TYPE_SIDE);
	
	//
	// Get current mouse-over entity
	//

	en = get_map_mouse_over_entity (map_dimensions);

	if (en)
	{
		switch (get_local_entity_type (en))
		{
			case ENTITY_TYPE_GROUP:
			{
				if (get_local_entity_int_value (en, INT_TYPE_SIDE) == side)
				{
					minimize_full_screen_map_object (obj, arg);

					show_group_page (en, FALSE);
				}
				else // Jabberwock 031007 Campaign Commander function
				{
					if (session_camcom)
					{
						if (get_comms_model () == COMMS_MODEL_SERVER)
						{
							process_radio_message (en, MESSAGE_LOCAL_BASE_CAMCOM_MESSAGE, 0);
						}
						else
						{
							transmit_entity_comms_message (ENTITY_COMMS_RADIO_MESSAGE, en, MESSAGE_LOCAL_BASE_CAMCOM_MESSAGE, 0);
						}
					}
				}
				break;
			}

			case ENTITY_TYPE_KEYSITE:
			{
				if (get_local_entity_int_value (en, INT_TYPE_SIDE) == side)
				{
					minimize_full_screen_map_object (obj, arg);

					show_base_page (en, FALSE);
				}
				else // Jabberwock 031007 Campaign Commander function
				{
					if (session_camcom)
					{
						if (get_comms_model () == COMMS_MODEL_SERVER)
						{
							process_radio_message (en, MESSAGE_LOCAL_BASE_CAMCOM_MESSAGE, 0);
						}
						else
						{
							transmit_entity_comms_message (ENTITY_COMMS_RADIO_MESSAGE, en, MESSAGE_LOCAL_BASE_CAMCOM_MESSAGE, 0);
						}

					}
				}
				break;
			}

			case ENTITY_TYPE_TASK:
			{
				ASSERT (get_local_entity_int_value (en, INT_TYPE_TASK_STATE) != TASK_STATE_COMPLETED);

				ASSERT (get_local_entity_int_value (en, INT_TYPE_SIDE) == side);

				minimize_full_screen_map_object (obj, arg);

				show_briefing_page (en, FALSE);

				break;
			}

			case ENTITY_TYPE_HELICOPTER:
			case ENTITY_TYPE_FIXED_WING:
			case ENTITY_TYPE_ROUTED_VEHICLE:
			case ENTITY_TYPE_SHIP_VEHICLE:
			case ENTITY_TYPE_ANTI_AIRCRAFT:
			{
				if (get_local_entity_int_value (en, INT_TYPE_SIDE) == side)
				{
					group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

					ASSERT (group);

					minimize_full_screen_map_object (obj, arg);

					show_group_page (group, FALSE);
				}

				break;
			}

			case ENTITY_TYPE_WAYPOINT:
			{
				if (get_local_entity_int_value (en, INT_TYPE_PLANNER_MOVEABLE))
				{
					set_active_map_object (obj);
	
					map_dimensions->selected_entity = en;
	
					push_event (map_move_waypoint_events, "move waypoint events");
				}
				
				break;
			}
		}
		
		return;
	}
		
	
	//
	// Check Insert Waypoint Icons
	//

	if (map_insert_waypoint_function (obj))
	{
		return;
	}

	//
	// Goto
	//

	map_goto_function (obj);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_campaign_map_origin (entity *en)
{
	vec3d
		*pos;

	float
		max_size;
	
	ASSERT (en);
	
	pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	ASSERT (pos);

	max_size = page_map_dimensions.size;

	max_size = min (max_size, (pos->x - MIN_MAP_X));
	max_size = min (max_size, (MAX_MAP_X - pos->x));

	max_size = min (max_size, (pos->z - MIN_MAP_Z));
	max_size = min (max_size, (MAX_MAP_Z - pos->z));

	page_map_dimensions.x = pos->x;
	page_map_dimensions.z = pos->z;

	page_map_dimensions.size = max_size;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void define_campaign_screen_map_page_objects (void)
{
	float
		x1,
		y1,
		x2,
		y2;

	ui_object
		*page;

	/////////////////////////////////////////////////////////////////
	// Main Page Area
	/////////////////////////////////////////////////////////////////

	x1 = CAMPAIGN_INSET_PAGE_X1;
	y1 = CAMPAIGN_INSET_PAGE_Y1;
	x2 = CAMPAIGN_INSET_PAGE_X2;
	y2 = CAMPAIGN_INSET_PAGE_Y2;

	campaign_page [CAMPAIGN_PAGE_MAP] = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (campaign_screen),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_DRAWABLE (FALSE),
			UI_ATTR_DRAW_FUNCTION (update_map_page_objects),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	page = campaign_page [CAMPAIGN_PAGE_MAP];

	/////////////////////////////////////////////////////////////////
	// Map Area

	x1 = 0.0;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 1.0;

	page_map_area = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (page),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_CLEAR (TRUE),
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

