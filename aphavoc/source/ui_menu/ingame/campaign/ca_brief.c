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

#define RENDER_STILL_PREVIEW	(d3d_can_render_to_texture)

#define PREVIEW_TEXTURE_SIZE 256

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static ui_object
	*briefing_text_area,
	*briefing_text_list,
	*briefing_page_title,
	*briefing_page_type,
	*briefing_page_takeoff_base_box,
	*briefing_page_landing_base_box,
	*briefing_page_group_box,
	*briefing_page_objective_box,
	*briefing_page_status_box,
	*briefing_page_expire_elapsed_text_box,
	*briefing_page_expire_time_box,
	*briefing_page_duration_time_box,
	*briefing_page_weather_box,
	*briefing_page_wind_box,
	*briefing_page_pilot_lock_box,
	*page_map_area,
	*page_map_view_area,
	*page_map_view_mode_area,
	*page_map_toggle,
	*page_3d_area,
	*page_3d_toggle,
	*page_back_button;

ui_object
	*mission_accept_button;

static map_dimension_type
	page_map_dimensions;

static screen
	*preview_texture_screen = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void render_static_briefing_objective_preview (entity *en);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void show_briefing_page (entity *mission, int force_update)
{
	entity
		*base,
		*previous,
		*guide,
		*objective,
		*group;

	static unsigned char
		s [128],
		*objective_name,
		text [3072],
		text1 [1024],
		text2 [1024],
		text3 [1024];

	unsigned char
		*text_ptr,
		*dest_text_ptr;

	ASSERT (mission);

	ASSERT (get_local_entity_type (mission) == ENTITY_TYPE_TASK);

	//
	// Get Briefing_text
	//

	ui_object_destroy_list_items (briefing_text_list);

	set_ui_object_virtual_y_size (briefing_text_list, 1.0);

	if (get_briefing_text (mission, &text1, &text2, &text3))
	{

		memset (text, 0, sizeof (text));

		// manually copy the first string

		dest_text_ptr = text;

		text_ptr = text1;

		if ((*text_ptr != '\0') && (*text_ptr != '\n'))
		{
	
			while ((*text_ptr != '\0') && (*text_ptr != '\n'))
			{
	
				*dest_text_ptr = *text_ptr;
	
				dest_text_ptr ++;
				text_ptr ++;
			}
	
			*dest_text_ptr = ' ';
			dest_text_ptr ++;
		}

		// manually copy the first string

		text_ptr = text2;

		if ((*text_ptr != '\0') && (*text_ptr != '\n'))
		{
	
			while ((*text_ptr != '\0') && (*text_ptr != '\n'))
			{
	
				*dest_text_ptr = *text_ptr;
	
				dest_text_ptr ++;
				text_ptr ++;
			}
	
			*dest_text_ptr = ' ';
			dest_text_ptr ++;
		}

		// strcat the last to include the eof

		strcat (text, text3);

		add_to_pop_up_list_with_word_wrap (text, briefing_text_list, NULL, 0, UI_FONT_ARIAL_10, ui_ingame_dead_text_colour);
	}

	resize_briefing_list_size (briefing_text_list);

	//
	// 
	//

	if (force_update)
	{
		previous = NULL;
	}
	else
	{
		previous = get_local_entity_safe_ptr (get_ui_object_item_number (campaign_page [CAMPAIGN_PAGE_BRIEFING]));
	}

	sprintf (s, "%s:", get_trans ("Briefing"));

	set_ui_object_text (briefing_page_title, s);

	sprintf (s, "%s #%d", get_trans (get_local_entity_string (mission, STRING_TYPE_FULL_NAME)), get_local_entity_int_value (mission, INT_TYPE_TASK_ID));

	set_ui_object_text (briefing_page_type, s);

	//
	// TAKEOFF BASE
	//

	base = get_local_entity_parent (mission, get_local_task_list_type (mission));

	if ((base) && (get_local_entity_type (base) == ENTITY_TYPE_KEYSITE))
	{
		set_ui_object_text (briefing_page_takeoff_base_box, get_local_entity_string (base, STRING_TYPE_KEYSITE_NAME));

		set_ui_object_item_number (briefing_page_takeoff_base_box, get_local_entity_index (base));
	}
	else
	{
		set_ui_object_text (briefing_page_takeoff_base_box, "");

		set_ui_object_item_number (briefing_page_takeoff_base_box, ENTITY_INDEX_DONT_CARE);
	}

	//
	// LANDING BASE 
	//

	base = get_local_entity_ptr_value (mission, PTR_TYPE_RETURN_KEYSITE);

	if ((base) && (get_local_entity_type (base) == ENTITY_TYPE_KEYSITE))
	{
		set_ui_object_text (briefing_page_landing_base_box, get_local_entity_string (base, STRING_TYPE_KEYSITE_NAME));

		set_ui_object_item_number (briefing_page_landing_base_box, get_local_entity_index (base));
	}
	else
	{
		set_ui_object_text (briefing_page_landing_base_box, "");

		set_ui_object_item_number (briefing_page_landing_base_box, ENTITY_INDEX_DONT_CARE);
	}

	//
	// GROUP DOING MISSION
	//
	
	guide = get_local_entity_first_child (mission, LIST_TYPE_GUIDE);

	if (guide)
	{
		group = get_local_entity_parent (guide, LIST_TYPE_GUIDE_STACK);

		ASSERT (group);
		
		ASSERT (get_local_entity_type (group) == ENTITY_TYPE_GROUP);
		
		if (get_local_entity_int_value (group, INT_TYPE_AIRCRAFT_GROUP))
		{
			set_ui_object_text (briefing_page_group_box, get_local_entity_string (group, STRING_TYPE_DIVISION_NAME));
		}
		else
		{
			set_ui_object_text (briefing_page_group_box, get_trans (get_local_entity_string (group, STRING_TYPE_FULL_NAME)));
		}

		set_ui_object_item_number (briefing_page_group_box, get_local_entity_index (group));
	}
	else
	{
		set_ui_object_text (briefing_page_group_box, "");

		set_ui_object_item_number (briefing_page_group_box, ENTITY_INDEX_DONT_CARE);
	}

	//
	// MISSION OBJECTIVE
	//

	if (mission != previous)
	{	
		objective_name = get_task_objective_string (mission);

		if (objective_name)
		{
			objective = get_local_entity_parent (mission, LIST_TYPE_TASK_DEPENDENT);

			ASSERT (objective);

			set_ui_object_text (briefing_page_objective_box, objective_name);

			set_ui_object_item_number (page_3d_area, get_local_entity_index (objective));

			//
			// Set 3D preview box state
			//

			switch (get_local_entity_int_value (mission, INT_TYPE_TASK_OBJECTIVE_PREVIEW_TYPE))
			{
				case TASK_OBJECTIVE_PREVIEW_NONE:
				{
					//
					// No 3D preview available for this mission
					//
					
					set_ui_object_drawable (page_3d_toggle, FALSE);

					set_ui_object_drawable (page_3d_area, FALSE);
				
					set_ui_object_drawable (page_map_area, TRUE);
				
					set_ui_object_state (page_map_toggle, UI_OBJECT_STATE_ON);

					break;
				}
				case TASK_OBJECTIVE_PREVIEW_STILL:
				{
					//
					// Still 3D preview available for this mission
					//

					set_ui_object_drawable (page_3d_toggle, TRUE);

					//
					// Render scene
					//
					
					render_static_briefing_objective_preview (objective);

					break;
				}
				case TASK_OBJECTIVE_PREVIEW_LIVE:
				{
					//
					// Live 3D preview available for this mission
					//
					
					set_ui_object_drawable (page_3d_toggle, TRUE);

					break;
				}
			}
		}
		else
		{
			set_ui_object_text (briefing_page_objective_box, "");

			set_ui_object_item_number (page_3d_area, ENTITY_INDEX_DONT_CARE);
		}
	}

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
			*base_pos;

		base = get_local_entity_parent (mission, get_local_task_list_type (mission));
			
		base_pos = get_local_entity_vec3d_ptr (base, VEC3D_TYPE_POSITION);

		min_pos = *base_pos;
		max_pos = *base_pos;

		if (get_local_entity_int_value (mission, INT_TYPE_TASK_STATE) == TASK_STATE_ASSIGNED)
		{
			//
			// ASSIGNED TASK
			//

			entity
				*wp;

			wp = get_local_entity_first_child (mission, LIST_TYPE_WAYPOINT);

			while (wp)
			{
				pos = get_local_entity_vec3d_ptr (wp, VEC3D_TYPE_POSITION);

				min_pos.x = min (min_pos.x, pos->x);
				min_pos.z = min (min_pos.z, pos->z);

				max_pos.x = max (max_pos.x, pos->x);
				max_pos.z = max (max_pos.z, pos->z);

				wp = get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT);
			}
		}
		else
		{
			//
			// UNASSIGNED TASK
			//

			vec3d
				*route_nodes;

			int
				loop,
				route_length;

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
		}

		page_map_dimensions.x = (min_pos.x + max_pos.x) * 0.5;
		page_map_dimensions.z = (min_pos.z + max_pos.z) * 0.5;

		page_map_dimensions.size = max ((max_pos.x - min_pos.x), (max_pos.z - min_pos.z));

		page_map_dimensions.size *= 1.2;

		page_map_dimensions.size = max (page_map_dimensions.size, 4.0 * KILOMETRE);

		page_map_dimensions.subject_entity = mission;
	}
	
	//
	// Accept Button
	//

	if (get_local_entity_int_value (get_session_entity (), INT_TYPE_SESSION_COMPLETE))
	{
		set_ui_object_drawable (mission_accept_button, FALSE); 
	}
	else
	{
		set_ui_object_drawable (mission_accept_button, get_mission_player_suitability_status (mission));
	}

	display_campaign_page (CAMPAIGN_PAGE_BRIEFING, get_local_entity_index (mission), TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_campaign_screen_briefing_page_objects (void)
{
	page_map_dimensions.x = MID_MAP_X;
	page_map_dimensions.z = MID_MAP_Z;
	page_map_dimensions.size = 4.0 * KILOMETRE;

	page_map_dimensions.subject_entity = NULL;
	page_map_dimensions.selected_entity = NULL;

	clear_map_mouse_over_object (&page_map_dimensions);

	set_ui_object_drawable (page_3d_area, FALSE);
	set_ui_object_item_number (page_3d_area, ENTITY_INDEX_DONT_CARE);

	set_ui_object_drawable (page_map_area, TRUE);
	set_ui_object_item_number (page_map_area, ENTITY_INDEX_DONT_CARE);

	set_ui_object_drawable (page_map_area, TRUE);

	set_ui_object_state (page_map_toggle, UI_OBJECT_STATE_ON);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_briefing_page_objects (ui_object *obj, void *arg)
{
	unsigned char
		buffer [64],
		s [128];

	entity
		*mission;

	mission = get_local_entity_safe_ptr (get_ui_object_item_number (campaign_page [CAMPAIGN_PAGE_BRIEFING]));

	ASSERT (mission);

	ASSERT (get_local_entity_type (mission) == ENTITY_TYPE_TASK);

	//
	// STATUS 
	//

	if (get_local_task_list_type (mission) == LIST_TYPE_UNASSIGNED_TASK)
	{
		set_ui_object_text (briefing_page_status_box, get_trans ("Unassigned"));
	}
	else
	{
		int
			status;

		status = get_local_entity_int_value (mission, INT_TYPE_TASK_COMPLETED);

		set_ui_object_text (briefing_page_status_box, get_trans (task_status_names [status]));
	}

	//
	// EXPIRE TIME
	//

	{
		float
			expire_timer;

		int
			hours,
			minutes,
			seconds;

		unsigned char
			output [32];

		if (get_local_task_list_type (mission) == LIST_TYPE_UNASSIGNED_TASK)
		{
			sprintf (output, "%s :  ", get_trans ("Expires"));
			
			set_ui_object_text (briefing_page_expire_elapsed_text_box, output);

			expire_timer = get_local_entity_float_value (mission, FLOAT_TYPE_EXPIRE_TIMER);
		}
		else
		{
			sprintf (output, "%s :  ", get_trans ("Elapsed Time"));
			
			set_ui_object_text (briefing_page_expire_elapsed_text_box, output);

			expire_timer = get_local_entity_float_value (mission, FLOAT_TYPE_ELAPSED_MISSION_TIME);
		}

		expire_timer = min (expire_timer, ONE_DAY);

		get_digital_countdown_values (expire_timer, NULL, &hours, &minutes, &seconds);
	
		sprintf (s, "%02d:%02d:%02d", hours, minutes, seconds);

		set_ui_object_text (briefing_page_expire_time_box, s);
	}

	//
	// DURATION TIME
	//

	{
		float
			flight_time;

		int
			hours,
			minutes,
			seconds;

		flight_time = get_task_estimated_route_duration (mission);

		ASSERT (flight_time < ONE_DAY);

		get_digital_countdown_values (flight_time, NULL, &hours, &minutes, &seconds);

		seconds = 0;
	
		sprintf (s, "%02d:%02d:%02d", hours, minutes, seconds);

		set_ui_object_text (briefing_page_duration_time_box, s);
	}

	//
	// WEATHER
	//

	{

		int
			int_heading;

		float
			heading,
			speed;

		entity
			*keysite;

		weathermodes
			weather;

		vec3d
			*pos,
			wind_velocity;
	
		keysite = get_local_entity_parent (mission, get_local_task_list_type (mission));

		ASSERT (keysite);

		pos = get_local_entity_vec3d_ptr (keysite, VEC3D_TYPE_POSITION);

		// Weather mode

		weather = get_simple_session_weather_at_point (pos);

		ASSERT ((weather > WEATHERMODE_INVALID) && (weather < WEATHERMODE_LAST));

		switch (weather)
		{
			case WEATHERMODE_DRY:
			{
				sprintf (s, "%s", get_trans ("Clear and dry"));

				break;
			}
			case WEATHERMODE_LIGHT_RAIN:
			{
				sprintf (s, "%s", get_trans ("Light rain"));

				break;
			}
			case WEATHERMODE_HEAVY_RAIN:
			{
				sprintf (s, "%s", get_trans ("Stormy with heavy rain"));

				break;
			}
			case WEATHERMODE_SNOW:
			{
				sprintf (s, "%s", get_trans ("Snow"));

				break;
			}
			default:
			{
				sprintf (s, "");
			}
		}

		set_ui_object_text (briefing_page_weather_box, s);

		// Wind velocity

		get_session_wind_velocity_at_point (pos, &wind_velocity);

		speed = get_3d_vector_magnitude (&wind_velocity);

		heading = atan2 (wind_velocity.x, wind_velocity.z);

		heading += PI;

		heading *= (8 / PI2);

		heading += PI_OVER_FOUR;

		int_heading = (int) heading;

		// int heading = the 8 zones around N, NE, E, SE, S etc...

		switch (int_heading)
		{

			case 0:
			{

				sprintf (s, "%s", get_trans ("North"));

				break;
			}

			case 1:
			{

				sprintf (s, "%s", get_trans ("Northeast"));

				break;
			}

			case 2:
			{

				sprintf (s, "%s", get_trans ("East"));

				break;
			}

			case 3:
			{

				sprintf (s, "%s", get_trans ("Southeast"));

				break;
			}

			case 4:
			{

				sprintf (s, "%s", get_trans ("South"));

				break;
			}

			case 5:
			{

				sprintf (s, "%s", get_trans ("Southwest"));

				break;
			}

			case 6:
			{

				sprintf (s, "%s", get_trans ("West"));

				break;
			}

			default:
			{

				sprintf (s, "%s", get_trans ("Northwest"));

				break;
			}
		}

		sprintf (buffer, " %d %s", (int) speed, get_trans ("Knots"));

		strcat (s, buffer);

		set_ui_object_text (briefing_page_wind_box, s);
	}

	//
	// PLAYER LOCK
	//

	{
		entity
			*pilot;
			
		pilot = get_local_entity_parent (mission, LIST_TYPE_PILOT_LOCK);

		if (pilot)
		{
			set_ui_object_text (briefing_page_pilot_lock_box, get_local_entity_string (pilot, STRING_TYPE_PILOTS_NAME));
		}
		else
		{
			set_ui_object_text (briefing_page_pilot_lock_box, "");
		}
	}

	//
	// Accept Button
	//

	if ((!get_gunship_entity ()) && (mission != get_currently_selected_mission ()) && (!get_local_entity_int_value (get_session_entity (), INT_TYPE_SESSION_COMPLETE)))
	{
		set_ui_object_drawable (mission_accept_button, get_mission_player_suitability_status (mission));
	}
	else
	{
		set_ui_object_drawable (mission_accept_button, FALSE);
	}

	//
	// Back Button
	//

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

static void notify_group_selected (ui_object *obj, void *arg)
{
	int
		index;
		
	index = get_ui_object_item_number (obj);

	if (index != ENTITY_INDEX_DONT_CARE)
	{
		show_group_page (get_local_entity_ptr (index), FALSE);
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

	en = get_local_entity_safe_ptr (get_ui_object_item_number (campaign_page [CAMPAIGN_PAGE_BRIEFING]));

	ASSERT (en);
	
	draw_2d_map (obj, arg);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_mission_accept_button (ui_object *obj, void *arg)
{
	int
		index;

	entity
		*group,
		*guide,
		*mission;
		
	index = get_ui_object_item_number (campaign_page [CAMPAIGN_PAGE_BRIEFING]);

	ASSERT (index != ENTITY_INDEX_DONT_CARE);

	mission = get_local_entity_safe_ptr (index);

	if (get_mission_player_suitability_status (mission))
	{
		set_currently_selected_mission (index);

		if (!get_currently_selected_member ())
		{
			//
			// Automatically change list mode to group
			//
			
			show_group_list (NULL, NULL);
	
			if (get_local_entity_int_value (mission, INT_TYPE_TASK_STATE) == TASK_STATE_ASSIGNED)
			{
				//
				// Automatically Show group page
				//
			
				guide = get_local_entity_first_child (mission, LIST_TYPE_GUIDE);
	
				ASSERT (guide);
	
				group = get_local_entity_parent (guide, LIST_TYPE_GUIDE_STACK);
	
				ASSERT (group);
		
				show_group_page (group, FALSE);
			}
		}
	}
	else
	{
		set_ui_object_drawable (mission_accept_button, FALSE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_page_3d_scene (ui_object *obj, void *arg)
{
	entity
		*en,
		*mission;

	viewpoint
		vp;

	vec3d
		*pos;

	en = get_local_entity_safe_ptr (get_ui_object_item_number (obj));

	mission = get_local_entity_safe_ptr (get_ui_object_item_number (campaign_page [CAMPAIGN_PAGE_BRIEFING]));
	
	if (en && mission)
	{
		switch (get_local_entity_int_value (mission, INT_TYPE_TASK_OBJECTIVE_PREVIEW_TYPE))
		{
			case TASK_OBJECTIVE_PREVIEW_STILL:
			{
				if (RENDER_STILL_PREVIEW)
				{
					draw_campaign_screen_texture_to_object (preview_texture_screen, obj);

					break;
				}

				// DELIBERATE FALL-THROUGH
			}
			case TASK_OBJECTIVE_PREVIEW_LIVE:
			{
				vec3d
					vec;
			
				float
					heading,
					pitch,
					distance;
			
				pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);
		
				ASSERT (pos);
				
				distance = get_local_entity_float_value (en, FLOAT_TYPE_RECON_DISTANCE);

				if (distance > 0.0)
				{
					heading = PI;
	
					pitch = rad (60.0);
	
					get_3d_unit_vector_from_heading_and_pitch (&vec, heading, pitch);
	
					vp.x = pos->x + (distance * vec.x);
					vp.y = pos->y + (distance * vec.y);
					vp.z = pos->z + (distance * vec.z);
	
					invert_3d_vector (&vec);
	
					get_matrix3x3_from_unit_vec3d (vp.attitude, &vec);
	
					draw_campaign_screen_3d_scene (obj, &vp);
				}
				else
				{
					debug_log ("CA_MISS: INVALID RECON DISTANCE FOR %s", get_local_entity_type_name (en));
				}
							
				break;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_static_briefing_objective_preview (entity *en)
{
	viewpoint
		vp;

	vec3d
		*pos,
		vec;

	float
		heading,
		pitch,
		distance;

	if (!RENDER_STILL_PREVIEW)
	{
		return;
	}

	ASSERT (en);

	ASSERT (preview_texture_screen);

	pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	ASSERT (pos);

	distance = get_local_entity_float_value (en, FLOAT_TYPE_RECON_DISTANCE);

	if (distance == 0.0)
	{
		debug_log ("CA_MISS: INVALID RECON DISTANCE FOR %s", get_local_entity_type_name (en));

		return;
	}

	heading = PI;

	pitch = rad (65.0);

	get_3d_unit_vector_from_heading_and_pitch (&vec, heading, pitch);

	vp.x = pos->x + (distance * vec.x);
	vp.y = pos->y + (distance * vec.y);
	vp.z = pos->z + (distance * vec.z);

	invert_3d_vector (&vec);

	get_matrix3x3_from_unit_vec3d (vp.attitude, &vec);

	//
	// Hack time of day to mid-day (i.e. light scene from above)
	//
	
	set_3d_time_of_day (main_3d_env, 12.0 * ONE_HOUR);

	recalculate_3d_environment_settings (main_3d_env);

	//
	// Draw scene
	//
	
	draw_campaign_screen_3d_scene_to_texture (preview_texture_screen, &vp, PREVIEW_TEXTURE_SIZE);

	//
	// Add greyscale effect (test)
	//
	{
		int
			x,
			y,
			greyscale;

		rgb_colour
			col;

		screen
			*old_screen;

		old_screen = get_active_screen ();

		lock_screen (preview_texture_screen);

		set_active_screen (preview_texture_screen);
	
		for (y = 0; y < PREVIEW_TEXTURE_SIZE; y ++)
		{
			for (x = 0; x < PREVIEW_TEXTURE_SIZE; x ++)
			{
				get_pixel (x, y, &col);

				greyscale = (col.r + col.g + col.b) / 3;
	
				col.r = greyscale;
				col.g = greyscale;
				col.b = greyscale;

				set_pixel (x, y, col);
			}
		}

		unlock_screen (preview_texture_screen);

		set_active_screen (old_screen);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_campaign_screen_3d_textures (void)
{
	if (RENDER_STILL_PREVIEW)
	{
		preview_texture_screen = create_user_3dvisual_texture_screen (PREVIEW_TEXTURE_SIZE, PREVIEW_TEXTURE_SIZE, TEXTURE_TYPE_SCREEN);
	}
	else
	{
		preview_texture_screen = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_campaign_screen_3d_textures (void)
{
	if (RENDER_STILL_PREVIEW)
	{
		destroy_screen (preview_texture_screen);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void define_campaign_screen_briefing_page_objects (void)
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

	unsigned char
		output [64];

	/////////////////////////////////////////////////////////////////
	// Main Page Area
	/////////////////////////////////////////////////////////////////

	x1 = CAMPAIGN_INSET_PAGE_X1;
	y1 = CAMPAIGN_INSET_PAGE_Y1;
	x2 = CAMPAIGN_INSET_PAGE_X2;
	y2 = CAMPAIGN_INSET_PAGE_Y2;

	campaign_page [CAMPAIGN_PAGE_BRIEFING] = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (campaign_screen),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_CENTRE_TOP),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_DRAWABLE (FALSE),
			UI_ATTR_DRAW_FUNCTION (update_briefing_page_objects),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	page = campaign_page [CAMPAIGN_PAGE_BRIEFING];

	/////////////////////////////////////////////////////////////////
	// Title
			
	x1 = 0.045;
	y1 = 0.045;
	x2 = 0.45;
	y2 = 0.085;

	briefing_page_title = create_ui_object
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

	briefing_page_type = create_ui_object
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

	x_start = 0.024;

	x_mid = 0.224;

	x_end = 0.464;
	
	ysize = 0.04;

	yinc = 0.045;

	/////////////////////////////////////////////////////////////////
	// Task Status Box 

	x1 = x_start;
	y1 = 0.178;
	x2 = x_mid;
	y2 = y1 + ysize;

	sprintf (output, "%s :  ", get_trans ("Status"));
			
	create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (output),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	x1 = x_mid;
	x2 = x_end;

	briefing_page_status_box = create_ui_object
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

	/////////////////////////////////////////////////////////////////
	// Expire Time Box

	x1 = x_start;
	x2 = x_mid;

	y1 += yinc;
	y2 = y1 + ysize;

	sprintf (output, "%s :  ", get_trans ("Expires"));
			
	briefing_page_expire_elapsed_text_box = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (output),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	x1 = x_mid;
	x2 = x_end;

	briefing_page_expire_time_box = create_ui_object
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

	/////////////////////////////////////////////////////////////////
	// Duration Time 

	x1 = x_start;
	x2 = x_mid;

	y1 += yinc;
	y2 = y1 + ysize;

	sprintf (output, "%s :  ", get_trans ("Est. Duration"));
			
	create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (output),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	x1 = x_mid;
	x2 = x_end;

	briefing_page_duration_time_box = create_ui_object
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

	/////////////////////////////////////////////////////////////////
	// Priority

	#if 0

	x1 = x_start;
	x2 = x_mid;

	y1 += yinc;
	y2 = y1 + ysize;

	sprintf (output, "%s :  ", get_trans ("Priority"));
			
	create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (output),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	x1 = x_mid;
	x2 = x_end;

	briefing_page_priority_box = create_ui_object
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
	// Mission Takeoff Base Box

	x1 = x_start;
	x2 = x_mid;

	y1 += yinc;
	y2 = y1 + ysize;

	sprintf (output, "%s :  ", get_trans ("Start Base"));
			
	create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (output),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	x1 = x_mid;
	x2 = x_end;

	briefing_page_takeoff_base_box = create_ui_object
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

	set_ui_mouse_over_entity_function (briefing_page_takeoff_base_box);

	/////////////////////////////////////////////////////////////////
	// Mission Landing Base Box

	x1 = x_start;
	x2 = x_mid;

	y1 += yinc;
	y2 = y1 + ysize;

	sprintf (output, "%s :  ", get_trans ("Landing Base"));
			
	create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (output),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	x1 = x_mid;
	x2 = x_end;

	briefing_page_landing_base_box = create_ui_object
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

	set_ui_mouse_over_entity_function (briefing_page_landing_base_box);

	/////////////////////////////////////////////////////////////////
	// Mission Group Box

	x1 = x_start;
	x2 = x_mid;

	y1 += yinc;
	y2 = y1 + ysize;

	sprintf (output, "%s :  ", get_trans ("Group"));
			
	create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (output),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	x1 = x_mid;
	x2 = x_end;

	briefing_page_group_box = create_ui_object
			(
				UI_TYPE_BUTTON,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (""),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_FUNCTION (notify_group_selected),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	set_ui_mouse_over_entity_function (briefing_page_group_box);

	/////////////////////////////////////////////////////////////////
	// Mission Objective Box

	x1 = x_start;
	x2 = x_mid;

	y1 += yinc;
	y2 = y1 + ysize;

	sprintf (output, "%s :  ", get_trans ("Objective"));
			
	create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (output),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	x1 = x_mid;
	x2 = x_end;

	briefing_page_objective_box = create_ui_object
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

	/////////////////////////////////////////////////////////////////
	// Weather box

	x1 = x_start;
	x2 = x_mid;

	y1 += yinc;
	y2 = y1 + ysize;

	sprintf (output, "%s :  ", get_trans ("Weather"));
			
	create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (output),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	x1 = x_mid;
	x2 = x_end;

	briefing_page_weather_box = create_ui_object
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

	/////////////////////////////////////////////////////////////////
	// Wind box

	x1 = x_start;
	x2 = x_mid;

	y1 += yinc;
	y2 = y1 + ysize;

	sprintf (output, "%s :  ", get_trans ("Wind"));
			
	create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (output),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	x1 = x_mid;
	x2 = x_end;

	briefing_page_wind_box = create_ui_object
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

	/////////////////////////////////////////////////////////////////
	// Mission Pilot Lock Box

	x1 = x_start;
	x2 = x_mid;

	y1 += yinc;
	y2 = y1 + ysize;

	sprintf (output, "%s :  ", get_trans ("Locked By"));
			
	create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (output),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	x1 = x_mid;
	x2 = x_end;

	briefing_page_pilot_lock_box = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT (""),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
				UI_ATTR_FONT_COLOUR (ui_ingame_selected_text_colour.r, ui_ingame_selected_text_colour.g, ui_ingame_selected_text_colour.b, ui_ingame_selected_text_colour.a),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_CLEAR (TRUE),
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

	define_map_objects (page_map_area, &page_map_dimensions, draw_page_map, campaign_map_left_click_function, map_centralise_function, &campaign_screen_full_screen_map);

	/////////////////////////////////////////////////////////////////
	// briefing text

	x1 = 0.1;
	y1 = 0.746;
	x2 = 0.99;
	y2 = 0.94;

	briefing_text_area = create_ui_object
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

	set_common_slider_graphics (briefing_text_area);

	x1 = 0.0;
	x2 = 0.9;
	y1 = 0.0;
	y2 = 1.0;

	briefing_text_list = create_ui_object
			(
				UI_TYPE_LIST_BOX,
				UI_ATTR_PARENT (briefing_text_area),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
				UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
				UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_NONE),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	///////////////////////////////////////////////////
	// Accept Button
	///////////////////////////////////////////////////
		
	x1 = 0.283;
	y1 = 0.949;
	x2 = 0.699;
	y2 = 1.0;

	mission_accept_button = create_ui_object
		(
			UI_TYPE_BUTTON,
			UI_ATTR_PARENT (page),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT (get_trans ("Accept Mission")),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
			UI_ATTR_FONT_COLOUR (ui_ingame_live_text_colour.r, ui_ingame_live_text_colour.g, ui_ingame_live_text_colour.b, ui_ingame_live_text_colour.a),
			UI_ATTR_HIGHLIGHTED_FONT_COLOUR (ui_ingame_highlight_text_colour.r, ui_ingame_highlight_text_colour.g, ui_ingame_highlight_text_colour.b, ui_ingame_highlight_text_colour.a),
			UI_ATTR_SELECTED_FONT_COLOUR (ui_ingame_selected_text_colour.r, ui_ingame_selected_text_colour.g, ui_ingame_selected_text_colour.b, ui_ingame_selected_text_colour.a),
			UI_ATTR_HIGHLIGHTABLE (TRUE),
			UI_ATTR_FUNCTION (notify_mission_accept_button),
			UI_ATTR_TEXTURE_GRAPHIC (create_texture_graphic ("graphics\\ui\\cohokum\\map\\acptbtn.psd")),
			UI_ATTR_END
		);

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
	/////////////////////////////////////////////////////////////////

	define_campaign_page_back_button (page, &page_back_button);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_mission_assigned (campaign_screen_messages message, entity *sender)
{
	if (get_local_entity_safe_index (sender) == get_ui_object_item_number (campaign_page [CAMPAIGN_PAGE_BRIEFING]))
	{
		if (get_ui_object_drawable (campaign_page [CAMPAIGN_PAGE_BRIEFING]))
		{
			show_briefing_page (sender, TRUE);
		}
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_mission_completed (campaign_screen_messages message, entity *sender)
{
	if (get_local_entity_safe_index (sender) == get_ui_object_item_number (campaign_page [CAMPAIGN_PAGE_BRIEFING]))
	{
		if (get_ui_object_drawable (campaign_page [CAMPAIGN_PAGE_BRIEFING]))
		{
			show_debriefing_page (sender, TRUE, FALSE);
		}
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_mission_destroyed (campaign_screen_messages message, entity *sender)
{
	if (get_local_entity_safe_index (sender) == get_ui_object_item_number (campaign_page [CAMPAIGN_PAGE_BRIEFING]))
	{
		if (get_ui_object_drawable (campaign_page [CAMPAIGN_PAGE_BRIEFING]))
		{
			//
			// Not sure yet.... For now display the map page
			//

			show_map_page ();
		}

		set_ui_object_item_number (campaign_page [CAMPAIGN_PAGE_BRIEFING], ENTITY_INDEX_DONT_CARE);
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_force_update (campaign_screen_messages message, entity *sender)
{
	if (get_ui_object_drawable (campaign_page [CAMPAIGN_PAGE_BRIEFING]))
	{
		ASSERT (sender);

		show_briefing_page (sender, TRUE);
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_briefing_page_message_responses (void)
{
	campaign_screen_message_targets
		target;

	target = CAMPAIGN_SCREEN_TARGET_BRIEFING_PAGE;

	campaign_screen_message_responses [target][CAMPAIGN_SCREEN_MISSION_ASSIGNED]	=	response_to_mission_assigned;

	campaign_screen_message_responses [target][CAMPAIGN_SCREEN_MISSION_COMPLETED]	=	response_to_mission_completed;

	campaign_screen_message_responses [target][CAMPAIGN_SCREEN_MISSION_DESTROYED]	=	response_to_mission_destroyed;

	campaign_screen_message_responses [target][CAMPAIGN_SCREEN_FORCE_UPDATE]		=	response_to_force_update;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_briefing_text_to_list (ui_object *list, char *text1)
{

	rgb_colour
		col;

	char
		temp_text [256],
		word [128],
		*word_ptr,
		*text_ptr;

	int
		max_string_length;

	col = get_ui_object_font_colour (list);

	memset (temp_text, 0, sizeof (temp_text));
	memset (word, 0, sizeof (word));

	max_string_length = get_ui_object_x_size (list);

	text_ptr = text1;

	while ((*text_ptr != '\0'))
	{

		// get next word

		word_ptr = word;

		while (*text_ptr != '\0')
		{

			*word_ptr = *text_ptr;

			text_ptr ++;

			if (*word_ptr == ' ')
			{

				break;
			}

			word_ptr ++;
		}

		// check word isn't longer than allowed space (causes an error if so...)
		ASSERT (ui_get_string_length (word) < max_string_length);

		// check that current string + word fits on line
		if ((ui_get_string_length (temp_text) + ui_get_string_length (word)) > max_string_length)
		{

			// if not display string
			add_to_pop_up_list (temp_text, list, NULL, 0, -1, col);

			// clear string
			memset (temp_text, 0, sizeof (temp_text));
		}

		// add word to string
		strcat (temp_text, word);

		memset (word, 0, sizeof (word));
	}

	add_to_pop_up_list (temp_text, list, NULL, 0, -1, col);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void resize_briefing_list_size (ui_object *list)
{
	ui_object
		*parent,
		*slider;

	float
		y;

	parent = get_ui_object_parent (list);

	// re-size the list objects when items are added

	y = max (1.0, get_next_list_position (list) / get_ui_object_y_size (parent));

	//set_ui_object_virtual_y_size (list, y);
	set_ui_object_virtual_y_size (list, 1.0);

	// resize the slider on the player list

	slider = get_ui_object_vslider (parent);

	recalculate_slider_size (slider);

	set_ui_object_vslider_virtual_position (slider, 0.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
