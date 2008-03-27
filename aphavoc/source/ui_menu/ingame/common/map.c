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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 						0

#define MAX_MAP_OBJECTS						8

#define MAP_OVERLAY_TEXTURE_SIZE			128

#define MAX_ICON_DRAW_LIST_ENTRIES		512

#define ANIMATE_MOUSE_OVER_ICON			FALSE

#define ICON_RESOLUTION_SCALE	(application_video_width / 640.0)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct MAP_EVENT_TYPE
{
	int
		type;

	float
		x,
		z,
		t,
		lifetime;

	struct MAP_EVENT_TYPE
		*next,
		*prev;
};

typedef struct MAP_EVENT_TYPE map_event_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static ui_object
	*last_drawn_map_object = NULL,
	*active_map_object = NULL;

static map_dimension_type
	*map_data_list = NULL;

static screen
	*map_overlay = NULL;

static map_event_type
	*map_events = NULL;

static texture_graphic
	*map_icons [NUM_ENTITY_SIDES][NUM_MAP_ICON_TYPES],
	*key_icons [NUM_MAP_LAYER_CONTROLS][3],
	*goto_icons [3],
	*zoom_in_icons [3],
	*zoom_out_icons [3],
	*minimise_icons [3],
	*maximise_icons [3],
	*map_key_backdrop_graphic = NULL;

static int
	map_icons_loaded = FALSE;

static float
	animation_timer = 0.0;

static int
	global_layer_controls;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct MAP_SIDE_BAND_TYPE
{
	float
		min,
		max,
		red_scale,
		blue_scale;
};

typedef struct MAP_SIDE_BAND_TYPE map_side_band_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const map_side_band_type
	map_side_band_data [] =
	{
		{0.0,		0.35,		1.0,	0.0},
		{0.35,	0.45,		0.8,	0.2},
		{0.45,	0.5,		0.6,	0.4},
		{0.5,		0.55,		0.4,	0.6},
		{0.55,	0.65,		0.2,	0.8},
		{0.65,	1.0,		0.0,	1.0},
		{-1,	-1,	-1,	-1}
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_layer_control_objects (int layer);

static void initialise_layer_control_objects (void);

static void map_draw_waypoint_routes (ui_object *obj, entity_sides side);

static void draw_task_waypoint_routes (ui_object *obj, entity *en);

static void draw_group_waypoint_routes (ui_object *obj, entity *en);

static void map_pop_move_waypoint_events (event *ev);

static void map_move_waypoint_position (event *ev);

static void map_layer_control_toggle_function (ui_object *obj, void *arg);

static void map_layer_control_radio_function (ui_object *obj, void *arg);

static void map_draw_threat_circles (ui_object *obj, entity_sides side);

static void map_draw_groups (ui_object *obj, entity_sides side);

static void map_draw_keysites (ui_object *obj, entity_sides side);

static void map_draw_towns (ui_object *obj);

static void map_draw_pilots (ui_object *obj, entity_sides side);

static void map_draw_missions (ui_object *obj, entity_sides side);

static void map_draw_string (ui_object *obj, vec3d *pos, const char *string, font_types font, rgb_colour *col, int centered);

static void map_draw_entity_icon (ui_object *obj, entity *en, vec3d *pos, int icon, int side, float scale);

static void map_draw_insert_waypoint_icon (ui_object *obj, entity *wp, vec3d *pos, int side);

static void map_draw_highlighted_insert_waypoint_icon (ui_object *obj, vec3d *pos);

static void map_draw_mouse_over_entity (ui_object *obj, entity *en);

static void map_draw_subject_entity (ui_object *obj);

static void map_get_screen_coords_from_world (ui_object *obj, vec3d *wpos, vec3d *spos);

static void map_get_world_coords_from_screen (ui_object *obj, vec3d *spos, vec3d *wpos);

static void bound_map_extents (ui_object *obj, float *w, float *h);

static void draw_2d_terrain_texture_overlays (ui_object *obj, float x, float z, float width, float height);

static void create_2d_terrain_texture_overlays (void);

static void map_draw_events (ui_object *obj);

static void map_draw_grid (ui_object *obj);

static void map_draw_track_entity (ui_object *obj, entity *en);

static void toggle_full_screen_function (ui_object *obj, void *arg);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct LAYER_CONTROL_BUTTON_TYPE
{
	int
		object_type;

	void
		*function;

	const char
		*graphic_filename;
};

typedef struct LAYER_CONTROL_BUTTON_TYPE layer_control_button_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const layer_control_button_type
	layer_control_button_data [NUM_MAP_LAYER_CONTROLS] =
	{
		UI_TYPE_RADIO,			map_layer_control_radio_function,	"SIDES",
		UI_TYPE_RADIO,			map_layer_control_radio_function,	"FOG",
		UI_TYPE_TOGGLE,		map_layer_control_toggle_function,	"GRID",
		UI_TYPE_TOGGLE,		map_layer_control_toggle_function,	"SITES",
		UI_TYPE_TOGGLE,		map_layer_control_toggle_function,	"MISN",
		UI_TYPE_TOGGLE,		map_layer_control_toggle_function,	"AIR",
		UI_TYPE_TOGGLE,		map_layer_control_toggle_function,	"GRND",
		UI_TYPE_TOGGLE,		map_layer_control_toggle_function,	"SEA",	
		UI_TYPE_TOGGLE,		map_layer_control_toggle_function,	"DEF",
		UI_TYPE_TOGGLE,		map_layer_control_toggle_function,	"THRT",
		UI_TYPE_TOGGLE,		map_layer_control_toggle_function,	"TRACK",
	};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static vec3d* get_last_known_position(entity* en)
{
	// arneh, 2007-07-08 - only update map position if update interval has passed

	int
		side,
		is_enemy;

	vec3d* pos;

	side = get_local_entity_int_value (en, INT_TYPE_SIDE);
	is_enemy = side != get_local_entity_int_value (get_pilot_entity (), INT_TYPE_SIDE);

	if (command_line_campaign_map_update_interval && is_enemy && en->type == ENTITY_TYPE_GROUP)
	{
		// arneh, 2007-07-08 - only update map position if update interval has passed

		int day = get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY);
		float current_time = current_time = (day * 24 *3600) + get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_TIME_OF_DAY);
		
		float last_update = get_local_entity_float_value (en, FLOAT_TYPE_LAST_SEEN_TIME);
		float time_since_last_update = current_time - last_update;

		if (time_since_last_update > command_line_campaign_map_update_interval)
		{
			pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

			set_local_entity_float_value (en, FLOAT_TYPE_LAST_SEEN_TIME, current_time);
			set_local_entity_vec3d (en, VEC3D_TYPE_LAST_KNOWN_POSITION, pos);
		}
		else
			pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_LAST_KNOWN_POSITION);
	}
	else
		pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	return pos;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_2d_map (ui_object *obj, void *arg)
{
	float
		x,
		z,
		x1, y1,
		x_size,
		y_size,
		width,
		height;

	int
		ix,
		iy,
		iwidth,
		iheight;

	entity_sides
		this_side,
		enemy_side;

	entity
		*en,
		*track_entity;

	vec3d
		*pos;

	map_dimension_type
		*map_dimensions,
		store_map_data;

	x1 = get_ui_object_x (obj);
	y1 = get_ui_object_y (obj);

	x_size = get_ui_object_x_size (obj);
	y_size = get_ui_object_y_size (obj);

	convert_float_to_int (x1, &ix);
	convert_float_to_int (y1, &iy);

	convert_float_to_int (x_size, &iwidth);
	convert_float_to_int (y_size, &iheight);

	x1 = ix;
	y1 = iy;

	x_size = iwidth;
	y_size = iheight;

	map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (obj);

	ASSERT (map_dimensions);
	
	this_side = get_local_entity_int_value (get_pilot_entity (), INT_TYPE_SIDE);

	enemy_side = get_enemy_side (this_side);

	map_dimensions->mouse_over_object.type = MOUSE_OVER_OBJECT_NONE;
	map_dimensions->mouse_over_object.distance = FLT_MAX;

	map_dimensions->mouse_over_object.en = NULL;

	//
	// Track Player / map subject
	//

	track_entity = NULL;

	if (global_layer_controls & (1 << MAP_LAYER_CONTROL_TRACK_PLAYER)) 
	{
		//
		// Track subject of map object.....
		//
		
		en = map_dimensions->subject_entity;

		if (en)
		{
			//
			// ...Unless it's not meant to be tracked
			//
			
			if (!get_local_entity_int_value (en, INT_TYPE_TRACK_ENTITY_ON_MAP))
			{
				en = NULL;
			}
		}

		//
		// Track the players helicopter by default
		//

		if (!en)
		{
			en = get_gunship_entity ();
		}

		if (en)
		{
			track_entity = en;

			store_map_data.x = map_dimensions->x;
			store_map_data.z = map_dimensions->z;

			store_map_data.size = map_dimensions->size;

			pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

			ASSERT (pos);
		
			map_dimensions->x = pos->x;
			map_dimensions->z = pos->z;
		}
	}

	//
	// Bound Map
	//

	bound_map_extents (obj, &width, &height);
	
	x = map_dimensions->x;
	z = map_dimensions->z;

	//
	// draw map
	//

	if (global_layer_controls & (1 << MAP_LAYER_CONTROL_SECTOR_SIDES)) 
	{
		set_2d_terrain_contour_colour (FALSE);
	}
	else
	{
		set_2d_terrain_contour_colour (TRUE);
	}
	
	set_2d_terrain_map_dimensions (
              x - width/2, z + height/2,
              x + width/2, z - height/2,
              x1, y1, (x1 + x_size) - 0.01, (y1 + y_size) - 0.01 );
 
	terrain_2d_map_contour_lines_drawn = TRUE;

	draw_2d_shaded_terrain_contour_map ();

	//
	// draw texture overlays
	//

   draw_2d_terrain_texture_overlays (obj, x, MAX_MAP_Z - z, width, height);

	//
	// draw town names
	//

	map_draw_towns (obj);

	//
	// draw grid
	//

	map_draw_grid (obj);

	//
	// draw layers etc...
	//

	map_draw_threat_circles (obj, this_side);
	map_draw_threat_circles (obj, enemy_side);

	map_draw_keysites (obj, enemy_side);
	map_draw_keysites (obj, this_side);

	map_draw_groups (obj, enemy_side);
	map_draw_groups (obj, this_side);

	map_draw_missions (obj, this_side);

	if (get_local_entity_int_value (get_session_entity (), INT_TYPE_CHEATS_ENABLED))
	{
		map_draw_pilots (obj, enemy_side);
	}

	map_draw_pilots (obj, this_side);

	if (track_entity)
	{
		map_draw_track_entity (obj, track_entity);
	}
	
	map_draw_subject_entity (obj);

	map_draw_waypoint_routes (obj, this_side);

//	this causes map flicker, so removed
//	map_draw_events (obj);

	en = get_ui_mouse_over_entity ();

	if (en)
	{
		map_draw_mouse_over_entity (obj, en);
	}
	else if (map_dimensions->mouse_over_object.type == MOUSE_OVER_OBJECT_ENTITY)
	{
		ASSERT (map_dimensions->mouse_over_object.en);

		map_draw_mouse_over_entity (obj, map_dimensions->mouse_over_object.en);

		set_ui_mouse_over_entity (map_dimensions->mouse_over_object.en);
	}
	else if (map_dimensions->mouse_over_object.type == MOUSE_OVER_OBJECT_WAYPOINT_ADD)
	{
		ASSERT (map_dimensions->mouse_over_object.en);

		map_draw_highlighted_insert_waypoint_icon (obj, &(map_dimensions->mouse_over_object.pos));
	}
	
	set_last_drawn_map_object (obj);

	if (track_entity)
	{
		map_dimensions->x = store_map_data.x;
		map_dimensions->z = store_map_data.z;

		map_dimensions->size = store_map_data.size;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void map_draw_waypoint_routes (ui_object *obj, entity_sides side)
{
	entity
		*en;

	map_dimension_type
		*map_dimensions;

	map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (obj);

	ASSERT (map_dimensions);
	
	//
	// Draw waypoint routes dependent of subject of the map
	//

	en = map_dimensions->subject_entity;

	if (en)
	{
		//
		// If a TASK - draw waypoint route for that task only
		//
	
		if (get_local_entity_type (en) == ENTITY_TYPE_TASK)
		{
			draw_task_waypoint_routes (obj, en);
	
			return;
		}
	
		//
		// If a MOBILE - draw waypoint route for that group only
		//
	
		if (get_local_entity_int_value (en, INT_TYPE_IDENTIFY_MOBILE))
		{
			draw_group_waypoint_routes (obj, get_local_entity_parent (en, LIST_TYPE_MEMBER));
	
			return;
		}
	}
	
	//
	// Default - Draw Player Waypoint Route
	//
	
	if (get_gunship_entity ())
	{
		draw_group_waypoint_routes (obj, get_local_entity_parent (get_gunship_entity (), LIST_TYPE_MEMBER));
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_task_waypoint_routes (ui_object *obj, entity *en)
{
	entity
		*wp1,
		*wp2;

	vec3d
		wpos1,
		wpos2,
		spos1,
		spos2,
		mid_pos;

	float
		font_width,
		font_height;

	char
		tag [5];

	int
		icon;

	entity_sides
		side;

	ASSERT (en);

	ASSERT (get_local_entity_type (en) == ENTITY_TYPE_TASK);

	if (!get_local_entity_int_value (en, INT_TYPE_VISIBLE_TASK))
	{
		return;
	}

	if (get_local_entity_int_value (en, INT_TYPE_MOVEMENT_TYPE) != MOVEMENT_TYPE_AIR)
	{
		return;
	}

	set_ui_font_type (UI_FONT_ARIAL_10);

	set_ui_font_colour (sys_col_white);

	font_height = ui_get_font_height ();

	side = get_local_entity_int_value (en, INT_TYPE_SIDE);

	wp1 = get_local_entity_first_child (en, LIST_TYPE_WAYPOINT);

	if (wp1)
	{
		//
		// Draw Connecting Lines .........
		//
		
		wp2 = get_local_entity_child_succ (wp1, LIST_TYPE_WAYPOINT);
	
		while (wp2)
		{
			get_local_entity_vec3d (wp1, VEC3D_TYPE_POSITION, &wpos1);

			get_local_entity_vec3d (wp2, VEC3D_TYPE_POSITION, &wpos2);

			// convert into screen coords

			map_get_screen_coords_from_world (obj, &wpos1, &spos1);
			map_get_screen_coords_from_world (obj, &wpos2, &spos2);

			//
			// Draw Line from WP1 -> WP2
			//

			draw_line (spos1.x, spos1.z, spos2.x, spos2.z, ui_ingame_dead_text_colour);

			wp1 = wp2;

			wp2 = get_local_entity_child_succ (wp2, LIST_TYPE_WAYPOINT);
		}

		//
		// Draw Icons ..............
		//
		
		wp1 = get_local_entity_first_child (en, LIST_TYPE_WAYPOINT);

		wp2 = get_local_entity_child_succ (wp1, LIST_TYPE_WAYPOINT);
	
		while (wp2)
		{
			get_local_entity_vec3d (wp1, VEC3D_TYPE_POSITION, &wpos1);

			get_local_entity_vec3d (wp2, VEC3D_TYPE_POSITION, &wpos2);

			// convert into screen coords

			map_get_screen_coords_from_world (obj, &wpos1, &spos1);
			map_get_screen_coords_from_world (obj, &wpos2, &spos2);

			//
			// Draw WP1 Icon
			//

			icon = get_local_entity_int_value (wp1, INT_TYPE_MAP_ICON);

			ASSERT (icon != MAP_ICON_NONE);

			map_draw_entity_icon (obj, wp1, &wpos1, icon, side, ICON_RESOLUTION_SCALE);

			//
			// Draw WP1 Letter
			//
			
			sprintf (tag, "%c", get_local_entity_char_value (wp1, CHAR_TYPE_TAG));

			font_width = ui_get_string_length (tag);

			ui_display_text (tag, spos1.x - (font_width * 0.5), spos1.z - (font_height * 0.5));
	
			//
			// Add Insert Waypoint Icon
			//

			mid_pos.x = (wpos1.x + wpos2.x) * 0.5;
			mid_pos.y = (wpos1.y + wpos2.y) * 0.5;
			mid_pos.z = (wpos1.z + wpos2.z) * 0.5;

			map_draw_insert_waypoint_icon (obj, wp1, &mid_pos, side);

			wp1 = wp2;

			wp2 = get_local_entity_child_succ (wp2, LIST_TYPE_WAYPOINT);
		}

		//
		// Draw Last Icon
		//

		icon = get_local_entity_int_value (wp1, INT_TYPE_MAP_ICON);

		ASSERT (icon != MAP_ICON_NONE);

		map_draw_entity_icon (obj, wp1, &wpos2, icon, side, ICON_RESOLUTION_SCALE);

		sprintf (tag, "%c", get_local_entity_char_value (wp1, CHAR_TYPE_TAG));

		font_width = ui_get_string_length (tag);

		ui_display_text (tag, spos2.x - (font_width * 0.5), spos2.z - (font_height * 0.5));

		//
		// if USER task show actual route flown (via current_flight_dynamics)
		//

		if (get_player_task (NULL) == en)
		{

			if (get_current_flight_dynamics ())
			{

				flight_path_data
					*flight_path;

				flight_path = get_current_flight_dynamics_flight_path ();

				if (flight_path)
				{

					wpos1.x = flight_path->x;
					wpos1.y = 0.0;
					wpos1.z = flight_path->z;

					map_get_screen_coords_from_world (obj, &wpos1, &spos1);

					flight_path = flight_path->next;

					while (flight_path)
					{

						wpos2.x = flight_path->x;
						wpos2.y = 0.0;
						wpos2.z = flight_path->z;

						map_get_screen_coords_from_world (obj, &wpos2, &spos2);

						switch (flight_path->action)
						{

							case FLIGHT_PATH_ACTION_USER_NAVIGATING:
							{
			
								draw_line (spos1.x, spos1.z, spos2.x, spos2.z, sys_col_red);

								break;
							}

							case FLIGHT_PATH_ACTION_AUTOPILOT_NAVIGATING:
							{
			
								draw_line (spos1.x, spos1.z, spos2.x, spos2.z, sys_col_green);

								break;
							}
						}

						wpos1 = wpos2;
						spos1 = spos2;

						flight_path = flight_path->next;
					}
				}
			}
		}
	}
	else
	{
		route_node
			*route,
			*temp_route;

		entity
			*target;

		vec3d
			*target_pos;

		//
		// Could be coded with a static ptr for "route" so the route is only generated with the task "en" changes...
		//

		route = temp_create_generic_waypoint_route (NULL, en, get_local_entity_ptr_value (en, PTR_TYPE_RETURN_KEYSITE), NULL, 0);

		temp_route = route;

		wpos1.x = temp_route->position.x;
		wpos1.y = temp_route->position.y;
		wpos1.z = temp_route->position.z;

		map_get_screen_coords_from_world (obj, &wpos1, &spos1);

		temp_route = temp_route->next;

		reset_waypoint_tags ();

		while (temp_route)
		{

			wpos2.x = temp_route->position.x;
			wpos2.y = temp_route->position.y;
			wpos2.z = temp_route->position.z;

			map_get_screen_coords_from_world (obj, &wpos2, &spos2);

			sprintf (tag, "%c", get_waypoint_sub_type_tag (temp_route->type));

			font_width = ui_get_string_length (tag);

			ui_display_text (tag, spos1.x - (font_width * 0.5), spos1.z - (font_height * 0.5));

			draw_line (spos1.x, spos1.z, spos2.x, spos2.z, ui_ingame_dead_text_colour);

			wpos1 = wpos2;
			spos1 = spos2;

			temp_route = temp_route->next;
		}

		destroy_fast_route (route);

		target = get_local_entity_parent (en, LIST_TYPE_TASK_DEPENDENT);

		if (target)
		{
			target_pos = get_last_known_position(target);

			if (target_pos)
			{
				map_get_screen_coords_from_world (obj, target_pos, &spos1);

				map_draw_entity_icon (obj, NULL, target_pos, MAP_ICON_WAYPOINT_TARGET_TEMPORARY, ENTITY_SIDE_NEUTRAL, ICON_RESOLUTION_SCALE);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_group_waypoint_routes (ui_object *obj, entity *en)
{
	entity
		*task;
		
	if (en)
	{
	
		ASSERT (get_local_entity_type (en) == ENTITY_TYPE_GROUP);
	
		task = get_local_group_primary_task (en);
	
		if (task)
		{
			draw_task_waypoint_routes (obj, task);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void load_map_icon (int icon, int side, const char *filename)
{
	ASSERT ((side >= 0) && (side < NUM_ENTITY_SIDES));

	ASSERT ((icon >= 0) && (icon < NUM_MAP_ICON_TYPES));

	ASSERT (filename);

	map_icons [side][icon] = create_texture_graphic (filename);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void load_key_icons (int layer)
{
	char
		filename [256];

	ASSERT ((layer >= 0) && (layer < NUM_MAP_LAYER_CONTROLS));

	sprintf (filename, "graphics\\ui\\cohokum\\key\\%sprp.psd", layer_control_button_data [layer].graphic_filename);

	key_icons [layer][0] = create_texture_graphic (filename);

	sprintf (filename, "graphics\\ui\\cohokum\\key\\%swht.psd", layer_control_button_data [layer].graphic_filename);

	key_icons [layer][1] = create_texture_graphic (filename);

	sprintf (filename, "graphics\\ui\\cohokum\\key\\%syel.psd", layer_control_button_data [layer].graphic_filename);

	key_icons [layer][2] = create_texture_graphic (filename);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void load_misc_3state_icons (const char *name, texture_graphic **icons)
{
	char
		filename [256];

	sprintf (filename, "graphics\\ui\\cohokum\\key\\%sprp.psd", name);

	icons [0] = create_texture_graphic (filename);

	sprintf (filename, "graphics\\ui\\cohokum\\key\\%swht.psd", name);

	icons [1] = create_texture_graphic (filename);

	sprintf (filename, "graphics\\ui\\cohokum\\key\\%syel.psd", name);

	icons [2] = create_texture_graphic (filename);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void load_map_textures (void)
{
	int
		side,
		icon,
		loop,
		layer;

	if (!map_overlay)
	{
		map_overlay = create_user_texture_screen (MAP_OVERLAY_TEXTURE_SIZE, MAP_OVERLAY_TEXTURE_SIZE, TEXTURE_TYPE_MULTIPLEALPHA, 0);
	}

	ASSERT (map_overlay);

	if (!map_icons_loaded)
	{
		for (side = 0; side < NUM_ENTITY_SIDES; side ++)
		{
			for (icon = 0; icon < NUM_MAP_ICON_TYPES; icon ++)
			{
				map_icons [side][icon] = NULL;
			}
		}
	
		load_map_icon (MAP_ICON_CAMPAIGN_OBJECTIVE,	ENTITY_SIDE_NEUTRAL, "graphics\\ui\\cohokum\\icons\\campobj.psd");
		load_map_icon (MAP_ICON_EVENT, 					ENTITY_SIDE_NEUTRAL, "graphics\\ui\\cohokum\\icons\\hotspot.psd");
		load_map_icon (MAP_ICON_EXPLOSION, 				ENTITY_SIDE_NEUTRAL, "graphics\\ui\\cohokum\\icons\\expl.psd");
		load_map_icon (MAP_ICON_HIGHLIGHT, 				ENTITY_SIDE_NEUTRAL, "graphics\\ui\\cohokum\\icons\\mover.psd");
		load_map_icon (MAP_ICON_PLAYER_OVERLAY, 		ENTITY_SIDE_NEUTRAL, "graphics\\ui\\cohokum\\icons\\player.psd");
		load_map_icon (MAP_ICON_SELECTED, 				ENTITY_SIDE_NEUTRAL, "graphics\\ui\\cohokum\\icons\\selected.psd");

		load_map_icon (MAP_ICON_WAYPOINT_INSERT_HIGHLIGHTED, 	ENTITY_SIDE_NEUTRAL, "graphics\\ui\\cohokum\\icons\\wpadwht.psd");
		load_map_icon (MAP_ICON_WAYPOINT_INSERT_SELECTED, 		ENTITY_SIDE_NEUTRAL, "graphics\\ui\\cohokum\\icons\\wpadyel.psd");
		load_map_icon (MAP_ICON_WAYPOINT_NAV_HIGHLIGHTED,		ENTITY_SIDE_NEUTRAL, "graphics\\ui\\cohokum\\icons\\navwht.psd");
		load_map_icon (MAP_ICON_WAYPOINT_NAV_SELECTED,			ENTITY_SIDE_NEUTRAL, "graphics\\ui\\cohokum\\icons\\navyel.psd");
		load_map_icon (MAP_ICON_WAYPOINT_TARGET_HIGHLIGHTED, 	ENTITY_SIDE_NEUTRAL, "graphics\\ui\\cohokum\\icons\\attkwht.psd");
		load_map_icon (MAP_ICON_WAYPOINT_TARGET_SELECTED, 		ENTITY_SIDE_NEUTRAL, "graphics\\ui\\cohokum\\icons\\attkyel.psd");
		load_map_icon (MAP_ICON_WAYPOINT_TARGET_TEMPORARY, 	ENTITY_SIDE_NEUTRAL, "graphics\\ui\\cohokum\\icons\\orngtarg.psd");

		load_map_icon (MAP_ICON_AAA, 						ENTITY_SIDE_RED_FORCE, "graphics\\ui\\cohokum\\icons\\cis_aaa.psd");
		load_map_icon (MAP_ICON_AIRBASE, 				ENTITY_SIDE_RED_FORCE, "graphics\\ui\\cohokum\\icons\\cis_rway.psd");
		load_map_icon (MAP_ICON_APC, 						ENTITY_SIDE_RED_FORCE, "graphics\\ui\\cohokum\\icons\\cis_apc.psd");
		load_map_icon (MAP_ICON_ARTILLERY,				ENTITY_SIDE_RED_FORCE, "graphics\\ui\\cohokum\\icons\\cis_artl.psd");
		load_map_icon (MAP_ICON_BUILDING, 				ENTITY_SIDE_RED_FORCE, "graphics\\ui\\cohokum\\icons\\cis_bld.psd");
		load_map_icon (MAP_ICON_CARRIER, 				ENTITY_SIDE_RED_FORCE, "graphics\\ui\\cohokum\\icons\\cis_ship.psd");
		load_map_icon (MAP_ICON_FARP, 					ENTITY_SIDE_RED_FORCE, "graphics\\ui\\cohokum\\icons\\cis_farp.psd");
		load_map_icon (MAP_ICON_HELICOPTER,				ENTITY_SIDE_RED_FORCE, "graphics\\ui\\cohokum\\icons\\cis_heli.psd");
		load_map_icon (MAP_ICON_JET, 						ENTITY_SIDE_RED_FORCE, "graphics\\ui\\cohokum\\icons\\cis_jet.psd");
		load_map_icon (MAP_ICON_MISSION, 				ENTITY_SIDE_RED_FORCE, "graphics\\ui\\cohokum\\icons\\cis_targ.psd");
		load_map_icon (MAP_ICON_OIL_REFINERY, 			ENTITY_SIDE_RED_FORCE, "graphics\\ui\\cohokum\\icons\\cis_oil.psd");
		load_map_icon (MAP_ICON_PLAYER, 					ENTITY_SIDE_RED_FORCE, "graphics\\ui\\cohokum\\icons\\cis_mult.psd");
		load_map_icon (MAP_ICON_POWER_STATION, 		ENTITY_SIDE_RED_FORCE, "graphics\\ui\\cohokum\\icons\\cis_powr.psd");
		load_map_icon (MAP_ICON_RADIO_TRANSMITTER,	ENTITY_SIDE_RED_FORCE, "graphics\\ui\\cohokum\\icons\\cis_mast.psd");
		load_map_icon (MAP_ICON_SHIP, 					ENTITY_SIDE_RED_FORCE, "graphics\\ui\\cohokum\\icons\\cis_frgt.psd");
		load_map_icon (MAP_ICON_TANK, 					ENTITY_SIDE_RED_FORCE, "graphics\\ui\\cohokum\\icons\\cis_tank.psd");
		load_map_icon (MAP_ICON_TRANSPORT_AIRCRAFT, 	ENTITY_SIDE_RED_FORCE, "graphics\\ui\\cohokum\\icons\\cis_trna.psd");
		load_map_icon (MAP_ICON_TRANSPORT_HELICOPTER, 	ENTITY_SIDE_RED_FORCE, "graphics\\ui\\cohokum\\icons\\cis_trnh.psd");
		load_map_icon (MAP_ICON_TRUCK, 					ENTITY_SIDE_RED_FORCE, "graphics\\ui\\cohokum\\icons\\cis_trck.psd");
		load_map_icon (MAP_ICON_WAYPOINT_INSERT, 		ENTITY_SIDE_RED_FORCE, "graphics\\ui\\cohokum\\icons\\cis_wpad.psd");
		load_map_icon (MAP_ICON_WAYPOINT_NAV, 			ENTITY_SIDE_RED_FORCE, "graphics\\ui\\cohokum\\icons\\cis_nav.psd");
		load_map_icon (MAP_ICON_WAYPOINT_TARGET, 		ENTITY_SIDE_RED_FORCE, "graphics\\ui\\cohokum\\icons\\cis_attk.psd");

		load_map_icon (MAP_ICON_AAA, 						ENTITY_SIDE_BLUE_FORCE, "graphics\\ui\\cohokum\\icons\\us_aaa.psd");
		load_map_icon (MAP_ICON_AIRBASE, 				ENTITY_SIDE_BLUE_FORCE, "graphics\\ui\\cohokum\\icons\\us_rway.psd");
		load_map_icon (MAP_ICON_APC, 						ENTITY_SIDE_BLUE_FORCE, "graphics\\ui\\cohokum\\icons\\us_apc.psd");
		load_map_icon (MAP_ICON_ARTILLERY, 				ENTITY_SIDE_BLUE_FORCE, "graphics\\ui\\cohokum\\icons\\us_artl.psd");
		load_map_icon (MAP_ICON_BUILDING, 				ENTITY_SIDE_BLUE_FORCE, "graphics\\ui\\cohokum\\icons\\us_bld.psd");
		load_map_icon (MAP_ICON_CARRIER, 				ENTITY_SIDE_BLUE_FORCE, "graphics\\ui\\cohokum\\icons\\us_ship.psd");
		load_map_icon (MAP_ICON_FARP, 					ENTITY_SIDE_BLUE_FORCE, "graphics\\ui\\cohokum\\icons\\us_farp.psd");
		load_map_icon (MAP_ICON_HELICOPTER, 			ENTITY_SIDE_BLUE_FORCE, "graphics\\ui\\cohokum\\icons\\us_heli.psd");
		load_map_icon (MAP_ICON_JET, 						ENTITY_SIDE_BLUE_FORCE, "graphics\\ui\\cohokum\\icons\\us_jet.psd");
		load_map_icon (MAP_ICON_MISSION, 				ENTITY_SIDE_BLUE_FORCE, "graphics\\ui\\cohokum\\icons\\us_targ.psd");
		load_map_icon (MAP_ICON_OIL_REFINERY, 			ENTITY_SIDE_BLUE_FORCE, "graphics\\ui\\cohokum\\icons\\us_oil.psd");
		load_map_icon (MAP_ICON_PLAYER, 					ENTITY_SIDE_BLUE_FORCE, "graphics\\ui\\cohokum\\icons\\us_mult.psd");
		load_map_icon (MAP_ICON_POWER_STATION, 		ENTITY_SIDE_BLUE_FORCE, "graphics\\ui\\cohokum\\icons\\us_powr.psd");
		load_map_icon (MAP_ICON_RADIO_TRANSMITTER,	ENTITY_SIDE_BLUE_FORCE, "graphics\\ui\\cohokum\\icons\\us_mast.psd");
		load_map_icon (MAP_ICON_SHIP, 					ENTITY_SIDE_BLUE_FORCE, "graphics\\ui\\cohokum\\icons\\us_frgt.psd");
		load_map_icon (MAP_ICON_TANK, 					ENTITY_SIDE_BLUE_FORCE, "graphics\\ui\\cohokum\\icons\\us_tank.psd");
		load_map_icon (MAP_ICON_TRANSPORT_AIRCRAFT, 	ENTITY_SIDE_BLUE_FORCE, "graphics\\ui\\cohokum\\icons\\us_trna.psd");
		load_map_icon (MAP_ICON_TRANSPORT_HELICOPTER, 	ENTITY_SIDE_BLUE_FORCE, "graphics\\ui\\cohokum\\icons\\us_trnh.psd");
		load_map_icon (MAP_ICON_TRUCK, 					ENTITY_SIDE_BLUE_FORCE, "graphics\\ui\\cohokum\\icons\\us_trck.psd");
		load_map_icon (MAP_ICON_WAYPOINT_INSERT, 		ENTITY_SIDE_BLUE_FORCE, "graphics\\ui\\cohokum\\icons\\us_wpad.psd");
		load_map_icon (MAP_ICON_WAYPOINT_NAV, 			ENTITY_SIDE_BLUE_FORCE, "graphics\\ui\\cohokum\\icons\\us_nav.psd");
		load_map_icon (MAP_ICON_WAYPOINT_TARGET, 		ENTITY_SIDE_BLUE_FORCE, "graphics\\ui\\cohokum\\icons\\us_attk.psd");

		for (layer = 0; layer < NUM_MAP_LAYER_CONTROLS; layer ++)
		{
			for (loop = 0; loop < 3; loop ++)
			{
				key_icons [layer][loop] = NULL;
			}
		}
	
		for (layer = 0; layer < NUM_MAP_LAYER_CONTROLS; layer ++)
		{
			load_key_icons (layer);
		}

		load_misc_3state_icons ("min", minimise_icons);
		load_misc_3state_icons ("max", maximise_icons);
		load_misc_3state_icons ("zmin", zoom_in_icons);
		load_misc_3state_icons ("zmout", zoom_out_icons);
		load_misc_3state_icons ("goto", goto_icons);

		map_key_backdrop_graphic = create_texture_graphic ("graphics\\ui\\cohokum\\key\\key.psd");

		map_icons_loaded = TRUE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_map_data (void)
{
	map_events = NULL;

	global_layer_controls = get_global_map_layer_options ();

	initialise_layer_control_objects ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_active_map_object (ui_object *obj)
{
	active_map_object = obj;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_last_drawn_map_object (ui_object *obj)
{
	last_drawn_map_object = obj;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void clear_map_mouse_over_object (map_dimension_type *data)
{
	ASSERT (data);

	data->mouse_over_object.type = MOUSE_OVER_OBJECT_NONE;
	data->mouse_over_object.distance = FLT_MAX;

	data->mouse_over_object.en = NULL;

	data->mouse_over_object.pos.x = 0;
	data->mouse_over_object.pos.y = 0;
	data->mouse_over_object.pos.z = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *get_map_mouse_over_entity (map_dimension_type *data)
{
	ASSERT (data);

	if (data->mouse_over_object.type == MOUSE_OVER_OBJECT_ENTITY)
	{
		return (data->mouse_over_object.en);
	}
	else
	{
		return NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_layer_control_objects (int layer)
{
	ui_object
		*obj;
		
	map_dimension_type
		*data;

	data = map_data_list;

	while (data)
	{
		obj = data->layer_control_objects [layer];
	
		ASSERT (obj);
	
		if (global_layer_controls & (1 << layer))
		{
			set_toggle_button_on (obj);
		}
		else
		{
			set_toggle_button_off (obj);
		}
	
		data = data->next;		
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_layer_control_objects (void)
{
	int
		loop;

	for (loop = 0; loop < NUM_MAP_LAYER_CONTROLS; loop ++)
	{
		update_layer_control_objects (loop);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int check_visible_entity (ui_object *obj, entity *en)
{
	entity
		*sector;

	vec3d
		*pos;

	int
		side;

	map_dimension_type
		*map_dimensions;

	ASSERT (en);

	map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (obj);

	ASSERT (map_dimensions);

	#ifdef DEBUG

	//
	// For developement purposes, if map fog option off - show everything...
	//
	
	if (!(global_layer_controls & (1 << MAP_LAYER_CONTROL_FOG_OF_WAR)))
	{
		return TRUE;
	}

	#endif

	side = get_local_entity_int_value (get_pilot_entity (), INT_TYPE_SIDE);

	if (get_local_entity_int_value (en, INT_TYPE_SIDE) == side)
	{
		return TRUE;
	}

	if (get_local_entity_type (en) == ENTITY_TYPE_KEYSITE)
	{
		if (get_local_entity_parent (en, LIST_TYPE_CAMPAIGN_OBJECTIVE))
		{
			return TRUE;
		}
	}

	if (!get_local_entity_int_value (en, INT_TYPE_HIDDEN_BY_FOG_OF_WAR))
	{
		return TRUE;
	}

	pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	sector = get_local_sector_entity (pos);

	if (get_sector_fog_of_war_value (sector, side) > 0.25)
	{
		return TRUE;
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void map_centralise_function (ui_object *obj, void *arg)
{
	//vec3d
	//	pos;

	map_dimension_type
		*map_dimensions;
		
	entity
		*en,
		*group;
	
	int
		side;

	if (((int) arg) == BUTTON_STATE_DOWN)
	{
		ASSERT (obj);
	
		map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (obj);

		ASSERT (map_dimensions);
		
		// Jabberwock 031007 Campaign Commander - cancel mission
		
		
		map_dimensions->selected_entity = NULL;

		side = get_local_entity_int_value (get_pilot_entity (), INT_TYPE_SIDE);
	
		en = get_map_mouse_over_entity (map_dimensions);
		
		if ((en) && (get_local_entity_type (en) == ENTITY_TYPE_TASK) && (session_camcom) && (get_in_flight_game_mode () == IN_FLIGHT_GAME_MODE_PLANNER))
		{
			if (get_local_entity_int_value (en, INT_TYPE_SIDE) == side) 
			{
				if (get_local_task_list_type (en) == LIST_TYPE_UNASSIGNED_TASK)
				{
					notify_local_entity (ENTITY_MESSAGE_TASK_TERMINATED, en, NULL, TASK_TERMINATED_ABORTED);
				}
				else
				{
					group = get_local_entity_parent (en, LIST_TYPE_TASK_DEPENDENT);
					
					notify_local_entity (ENTITY_MESSAGE_TASK_COMPLETED, en, en, TASK_TERMINATED_STOP_TIME_REACHED);
				}
			}
		}
		// Jabberwock 031007 ends
		//else  // Jabberwock 031020 Fine mouse panning - commented out, as centralising is not needed and quirky
		{
			//
			// Disable Tracking
			//

		//	force_map_layer_control_object (MAP_LAYER_CONTROL_TRACK_PLAYER, FALSE); 

			//
			// work out click position in world coords
			//

		//	pos.x = get_mouse_x ();
		//	pos.z = get_mouse_y ();

		//	map_get_world_coords_from_screen (obj, &pos, &pos);

		//	map_dimensions->x = pos.x;
		//	map_dimensions->z = pos.z;

		//	bound_map_extents (obj, NULL, NULL);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void map_zoom_in_function (ui_object *obj, void *arg)
{
	map_dimension_type
		*map_dimensions;

	map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (obj);

	ASSERT (map_dimensions);
	
	map_dimensions->size /= 2.0;

	map_dimensions->size = bound (map_dimensions->size, 100.0, max (MAX_MAP_X, MAX_MAP_Z));

	map_centralise_function (obj, NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void map_zoom_out_function (ui_object *obj, void *arg)
{
	map_dimension_type
		*map_dimensions;

	map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (obj);

	ASSERT (map_dimensions);

	map_dimensions->size *= 2.0;

	map_dimensions->size = bound (map_dimensions->size, 100.0, max (MAX_MAP_X, MAX_MAP_Z));

	map_centralise_function (obj, NULL);
}

// Jabberwock 031002 mouse-wheel map zoom procedures

void map_wheel_centralise (ui_object *obj)
{
	vec3d
		pos;

	map_dimension_type
		*map_dimensions;

		ASSERT (obj);
	
		map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (obj);

		ASSERT (map_dimensions);

		pos.x = get_mouse_x ();
		pos.z = get_mouse_y ();

		map_get_world_coords_from_screen (obj, &pos, &pos);
	
		map_dimensions->x = pos.x;
		map_dimensions->z = pos.z;
		
		bound_map_extents (obj, NULL, NULL);
		
}


void map_wheel_zoom_in_event (event *ev)
{
	
	map_dimension_type
		*map_dimensions;

	ui_object
			*obj;
			
	float
		x,
		y,
		width,
		height,
		wx_min,
		wz_min,
		wx_max,
		wz_max;
		
	vec3d
		pos1;

	obj = last_drawn_map_object;
	

	if (obj)
	{
		map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (obj);

		ASSERT (map_dimensions);
	
		map_dimensions->size /= 2.0;

		map_dimensions->size = bound (map_dimensions->size, 100.0, max (MAX_MAP_X, MAX_MAP_Z));

		pos1.x = get_mouse_x ();
		pos1.z = get_mouse_y ();

		x = get_ui_object_x (obj);
				
		y = get_ui_object_y (obj);

		map_wheel_centralise (obj);
		
		get_2d_terrain_map_world_dimensions (&wx_min, &wz_min, &wx_max, &wz_max);
		
		width = get_ui_object_x_size (obj)/2;
		height = get_ui_object_y_size (obj)/2;

		set_mouse_x (x+width);
		set_mouse_y (y+height);
	}

}

// Jabberwock 031002 ends

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void map_add_waypoint (entity *wp1, vec3d *pos)
{
	entity
		*task;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ASSERT (pos);

	ASSERT (wp1);
	ASSERT (get_local_entity_type (wp1) == ENTITY_TYPE_WAYPOINT);

	task = get_local_entity_parent (wp1, LIST_TYPE_WAYPOINT);

	ASSERT (task);
	ASSERT (get_local_entity_type (task) == ENTITY_TYPE_TASK);

	create_client_server_entity
	(
		ENTITY_TYPE_WAYPOINT,
		ENTITY_INDEX_DONT_CARE,
		ENTITY_ATTR_PARENT (LIST_TYPE_WAYPOINT, task),
		ENTITY_ATTR_CHILD_PRED (LIST_TYPE_WAYPOINT, wp1),
		ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_WAYPOINT_NAVIGATION),
		ENTITY_ATTR_INT_VALUE (INT_TYPE_POSITION_TYPE, POSITION_TYPE_ABSOLUTE),
		ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, pos->x, pos->y, pos->z),
		ENTITY_ATTR_END
	);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int map_insert_waypoint_function (ui_object *obj)
{
	map_dimension_type
		*data;

	entity
		*wp1,
		*wp2;

	vec3d
		pos,
		*wp1_pos,
		*wp2_pos;

	data = (map_dimension_type *)get_ui_object_user_ptr (obj);

	ASSERT (data);

	if (data->mouse_over_object.type == MOUSE_OVER_OBJECT_WAYPOINT_ADD)
	{
		wp1 = data->mouse_over_object.en;

		ASSERT (wp1);
		ASSERT (get_local_entity_type (wp1) == ENTITY_TYPE_WAYPOINT);

		wp2 = get_local_entity_child_succ (wp1, LIST_TYPE_WAYPOINT);

		ASSERT (wp2);
		ASSERT (get_local_entity_type (wp2) == ENTITY_TYPE_WAYPOINT);

		wp1_pos = get_local_entity_vec3d_ptr (wp1, VEC3D_TYPE_POSITION);

		wp2_pos = get_local_entity_vec3d_ptr (wp2, VEC3D_TYPE_POSITION);

		pos.x = (wp1_pos->x + wp2_pos->x) * 0.5;
		pos.y = (wp1_pos->y + wp2_pos->y) * 0.5;
		pos.z = (wp1_pos->z + wp2_pos->z) * 0.5;

		if (get_comms_model () == COMMS_MODEL_SERVER)
		{
			map_add_waypoint (wp1, &pos);
		}
		else
		{
			transmit_entity_comms_message (ENTITY_COMMS_ADD_PLANNER_WAYPOINT, wp1, &pos);
		}

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_full_screen_toggle_function (ui_object *obj, void *arg)
{
	map_dimension_type
		*map_dimensions;

	map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (obj);

	ASSERT (map_dimensions);

	ASSERT (map_dimensions->map_area);

	ASSERT (map_dimensions->full_screen_parent);
	
	set_ui_object_drawable (obj, TRUE);

	set_ui_object_highlightable (obj, TRUE);

	if (map_dimensions->full_screen)
	{
		set_ui_object_texture_graphic (obj, minimise_icons [0]);
		set_ui_object_highlighted_texture_graphic (obj, minimise_icons [1]);
		set_ui_object_selected_texture_graphic (obj, minimise_icons [2]);
	}
	else
	{
		set_ui_object_texture_graphic (obj, maximise_icons [0]);
		set_ui_object_highlighted_texture_graphic (obj, maximise_icons [1]);
		set_ui_object_selected_texture_graphic (obj, maximise_icons [2]);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void toggle_full_screen_function (ui_object *obj, void *arg)
{
	map_dimension_type
		*map_dimensions;

	ui_object
		*info_area;

	map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (obj);

	ASSERT (map_dimensions);

	ASSERT (map_dimensions->map_area);

	if (map_dimensions->full_screen_parent)
	{
		ASSERT (*(map_dimensions->full_screen_parent));

		info_area = get_ui_object_user_ptr (*(map_dimensions->full_screen_parent));
	
		if (map_dimensions->full_screen)
		{
			//
			// Minimize map
			//
	
			set_ui_object_drawable (*(map_dimensions->full_screen_parent), FALSE);
	
			set_ui_object_parent (map_dimensions->map_area, map_dimensions->parent);

			if (info_area)
			{
				set_ui_object_drawable (info_area, FALSE);
			}

			map_dimensions->full_screen = FALSE;
		}
		else
		{
			//
			// Maximize map
			//
	
			set_ui_object_drawable (*(map_dimensions->full_screen_parent), TRUE);
	
			set_ui_object_parent (map_dimensions->map_area, *(map_dimensions->full_screen_parent));
	
			if (info_area)
			{
				set_ui_object_drawable (info_area, TRUE);
			}

			map_dimensions->full_screen = TRUE;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_goto_toggle_function (ui_object *obj, void *arg)
{
	map_dimension_type
		*map_dimensions;

	map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (obj);

	ASSERT (map_dimensions);

	if (map_dimensions->enable_goto)
	{
		set_toggle_button_on (obj);
	}
	else
	{
		set_toggle_button_off (obj);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void toggle_map_goto_function (ui_object *obj, void *arg)
{
	map_dimension_type
		*map_dimensions;

	map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (obj);

	ASSERT (map_dimensions);

	map_dimensions->enable_goto = !(map_dimensions->enable_goto);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void minimize_full_screen_function (map_dimension_type *map_dimensions)
{
	ui_object
		*parent,
		*info_area;

	ASSERT (map_dimensions);

	ASSERT (map_dimensions->map_area);

	parent = get_ui_object_parent (map_dimensions->map_area);

	ASSERT (parent);

	if (map_dimensions->full_screen_parent)
	{
		ASSERT (*(map_dimensions->full_screen_parent));
	
		if (parent == *(map_dimensions->full_screen_parent))
		{
			//
			// Minimize map
			//
	
			info_area = get_ui_object_user_ptr (*(map_dimensions->full_screen_parent));
	
			set_ui_object_drawable (*(map_dimensions->full_screen_parent), FALSE);
	
			set_ui_object_parent (map_dimensions->map_area, map_dimensions->parent);
	
			if (info_area)
			{
				set_ui_object_drawable (info_area, FALSE);
			}

			map_dimensions->full_screen = FALSE;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void minimize_full_screen_map_object (ui_object *obj, void *arg)
{
	map_dimension_type
		*map_dimensions;

	map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (obj);

	ASSERT (map_dimensions);

	minimize_full_screen_function (map_dimensions);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void minimize_all_map_objects (void)
{
	map_dimension_type
		*data;

	data = map_data_list;

	while (data)
	{
		minimize_full_screen_function (data);
	
		data = data->next;		
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void map_goto_function (ui_object *obj)
{
	vec3d
		pos;

	float
		altitude;

	map_dimension_type
		*map_dimensions;

	ASSERT (get_session_entity ());

	if (get_local_entity_int_value (get_session_entity (), INT_TYPE_CHEATS_ENABLED))
	{
		map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (obj);
	
		ASSERT (map_dimensions);
	
		if (get_gunship_entity ())
		{
			if ((map_dimensions->enable_goto) || (session_planner_goto_button))
			{
				pos.x = get_mouse_x ();
				pos.z = get_mouse_y ();
		
				map_get_world_coords_from_screen (obj, &pos, &pos);
		
				bound_position_to_adjusted_map_volume (&pos);
		
				altitude = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_RADAR_ALTITUDE);
		
				altitude = min (altitude, 100.0);
		
				pos.y = get_3d_terrain_elevation (pos.x, pos.z) + altitude;
		
				set_client_server_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &pos);
			
				current_flight_dynamics->position.x = pos.x;
				current_flight_dynamics->position.y = pos.y;
				current_flight_dynamics->position.z = pos.z;
			
				current_flight_dynamics->model_motion_vector.x = 0.0;
				current_flight_dynamics->model_motion_vector.y = 0.0;
				current_flight_dynamics->model_motion_vector.z = 0.0;
			
				current_flight_dynamics->world_motion_vector.x = 0.0;
				current_flight_dynamics->world_motion_vector.y = 0.0;
				current_flight_dynamics->world_motion_vector.z = 0.0;
		
				set_current_flight_dynamics_valid_collision_points (FALSE);
	
				map_dimensions->enable_goto = FALSE;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void map_move_waypoint_events (void)
{

	set_event (MOUSE_MOVE, MODIFIER_MOUSE_LEFT_BUTTON, BUTTON_STATE_EITHER, map_move_waypoint_position);

	set_mouse_graphic_off ();

	//
	// mouse buttons
	//

	set_event (MOUSE_LEFT_BUTTON, MODIFIER_NONE, BUTTON_STATE_EITHER, map_pop_move_waypoint_events);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void map_pop_move_waypoint_events (event *ev)
{

	vec3d
		*pos;

	map_dimension_type
		*map_dimensions;

	ASSERT (active_map_object);

	map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (active_map_object);

	ASSERT (map_dimensions);

	set_mouse_graphic_on ();

	pop_event (map_move_waypoint_events);

	if (map_dimensions->selected_entity)
	{
		pos = get_local_entity_vec3d_ptr (map_dimensions->selected_entity, VEC3D_TYPE_POSITION);

		if (get_comms_model () == COMMS_MODEL_SERVER)
		{

			entity
				*member;

			set_client_server_entity_vec3d (map_dimensions->selected_entity, VEC3D_TYPE_POSITION, pos);

			member = get_local_entity_first_child (map_dimensions->selected_entity, LIST_TYPE_CURRENT_WAYPOINT);
		}
		else
		{

			transmit_entity_comms_message (ENTITY_COMMS_MOVE_PLANNER_WAYPOINT, map_dimensions->selected_entity, pos);
		}

		// update flight time

		{

			entity
				*task,
				*group,
				*guide,
				*member,
				*last_wp;

			float
				range,
				flight_time;

			vec3d
				*last_waypoint_position;

			last_wp = get_local_entity_child_pred (map_dimensions->selected_entity, LIST_TYPE_WAYPOINT);
	
			if (last_wp)
			{
	
				last_waypoint_position = get_local_entity_vec3d_ptr (last_wp, VEC3D_TYPE_POSITION);
	
				range = get_2d_range (pos, last_waypoint_position);
	
				task = get_local_entity_parent (map_dimensions->selected_entity, LIST_TYPE_WAYPOINT);
	
				ASSERT (task);
	
				guide = get_local_entity_first_child (task, LIST_TYPE_GUIDE);
	
				if (guide)
				{

					group = get_local_entity_parent (guide, LIST_TYPE_GUIDE_STACK);
		
					member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);
		
					if (member)
					{
			
						flight_time = range / get_local_entity_float_value (member, FLOAT_TYPE_CRUISE_VELOCITY);
			
						set_client_server_entity_float_value (map_dimensions->selected_entity, FLOAT_TYPE_FLIGHT_TIME, flight_time);
	
						debug_log ("CA_MAP: setting flight time for waypoint %s to %f", get_local_entity_string (map_dimensions->selected_entity, STRING_TYPE_FULL_NAME), flight_time);
					}
				}
			}
		}

		map_dimensions->selected_entity = NULL;
	}

	active_map_object = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void map_move_waypoint_position (event *ev)
{

	vec3d
		pos;

	map_dimension_type
		*map_dimensions;

	ASSERT (active_map_object);

	map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (active_map_object);

	ASSERT (map_dimensions);

	if (map_dimensions->selected_entity)
	{
		ASSERT (get_local_entity_type (map_dimensions->selected_entity) == ENTITY_TYPE_WAYPOINT);

		get_local_entity_vec3d (map_dimensions->selected_entity, VEC3D_TYPE_POSITION, &pos);

		map_get_screen_coords_from_world (active_map_object, &pos, &pos);

		#if DEBUG_MODULE

		debug_log ("CA_MAP: moving waypoint %s (%d) from %f, %f by %f, %f",
						get_local_entity_string (map_dimensions->selected_entity, STRING_TYPE_FULL_NAME),
						get_local_entity_index (map_dimensions->selected_entity),
						pos.x, pos.z,
						delta_pos.x,
						delta_pos.z);

		#endif

		pos.x += ev->dx;
		pos.z += ev->dy;

		map_get_world_coords_from_screen (active_map_object, &pos, &pos);

		bound_position_to_map_area (&pos);

		pos.y = max (pos.y, get_3d_terrain_elevation (pos.x, pos.z));

		set_local_entity_vec3d (map_dimensions->selected_entity, VEC3D_TYPE_POSITION, &pos);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void map_get_screen_coords_from_world (ui_object *obj, vec3d *wpos, vec3d *spos)
{

	float
		x1,
		y1,
		x_size,
		y_size,
		width,
		height,
		wx_min,
		wz_min,
		wx_max,
		wz_max;

	ASSERT (wpos);
	ASSERT (spos);

	spos->x = wpos->x;
	spos->y = wpos->y;
	spos->z = wpos->z;

	x1 = get_ui_object_x (obj);
	y1 = get_ui_object_y (obj);

	x_size = get_ui_object_x_size (obj);
	y_size = get_ui_object_y_size (obj);
	
	get_2d_terrain_map_world_dimensions (&wx_min, &wz_min, &wx_max, &wz_max);

	width = (wx_max - wx_min);

	height = (wz_min - wz_max);
	
	spos->x -= wx_min;
	spos->x /= width;
	spos->x *= x_size;
	spos->x += x1;

	spos->z -= wz_max;
	spos->z /= height;
	spos->z *= y_size;
	spos->z = y_size - spos->z;
	spos->z += y1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void map_get_world_coords_from_screen (ui_object *obj, vec3d *spos, vec3d *wpos)
{

	float
		x1,
		y1,
		x_size,
		y_size,
		width,
		height,
		wx_min,
		wz_min,
		wx_max,
		wz_max;

	ASSERT (wpos);
	ASSERT (spos);

	wpos->x = spos->x;
	wpos->y = spos->y;
	wpos->z = spos->z;

	x1 = get_ui_object_x (obj);
	y1 = get_ui_object_y (obj);

	x_size = get_ui_object_x_size (obj);
	y_size = get_ui_object_y_size (obj);
	
	get_2d_terrain_map_world_dimensions (&wx_min, &wz_min, &wx_max, &wz_max);

	width = (wx_max - wx_min);

	height = (wz_min - wz_max);
	
	wpos->x -= x1;
	wpos->x /= x_size;
	wpos->x *= width;
	wpos->x += wx_min;

	wpos->z -= y1;
	wpos->z = y_size - wpos->z;
	wpos->z /= y_size;
	wpos->z *= height;
	wpos->z += wz_max;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void map_layer_control_toggle_function (ui_object *obj, void *arg)
{
	int
		index;

	index = get_ui_object_item_number (obj);

	global_layer_controls ^= (1 << index);

	update_layer_control_objects (index);

	set_global_map_layer_options (global_layer_controls);

	create_2d_terrain_texture_overlays ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void map_layer_control_radio_function (ui_object *obj, void *arg)
{
	int
		loop,
		index;

	index = get_ui_object_item_number (obj);

	for (loop = 0; loop < NUM_MAP_LAYER_CONTROLS; loop ++)
	{
		if (loop == index)
		{
			global_layer_controls ^= (1 << loop);

			update_layer_control_objects (loop);
		}
		else
		{
			if (layer_control_button_data [loop].object_type == UI_TYPE_RADIO)
			{
				global_layer_controls &= ~(1 << loop);

				update_layer_control_objects (loop);
			}
		}
	}

	set_global_map_layer_options (global_layer_controls);

	create_2d_terrain_texture_overlays ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void force_map_layer_control_object (map_layer_control_types index, int state)
{
	if (state)
	{
		global_layer_controls |= (1 << index);
	}
	else
	{
		global_layer_controls &= ~(1 << index);
	}
	
	update_layer_control_objects (index);

	set_global_map_layer_options (global_layer_controls);

	create_2d_terrain_texture_overlays ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void map_draw_threat_circle (ui_object *obj, entity *group, int circle_side_count)
{
	vec3d
		*pos,
		pos2,
		spos1,
		spos2;

	entity
		*en;

	entity_sides
		side;

	float
		r,
		scan_radius,
		screen_radius;

	int
		active_radar;

	rgb_colour
		threat_circle_filled_colour,
		threat_circle_outline_colour;

	ASSERT (group);

	ASSERT (obj);

	if (!check_visible_entity (obj, group))
	{
		return;
	}

	pos = get_last_known_position(group);

	ASSERT (pos);

	scan_radius = 0.0;

	active_radar = FALSE;

	en = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

	while (en)
	{
		if (get_local_entity_int_value (en, INT_TYPE_OFFENSIVE_CAPABILITY))
		{
			if (get_local_entity_int_value (en, INT_TYPE_THREAT_TYPE) != THREAT_TYPE_INVALID)
			{
				active_radar = TRUE;
			}

			r = get_local_entity_float_value (en, FLOAT_TYPE_AIR_SCAN_RANGE);

			scan_radius = max (scan_radius, r);
		}

		en = get_local_entity_child_succ (en, LIST_TYPE_MEMBER);
	}

	if (scan_radius > 0.0)
	{
		pos2.x = pos->x + scan_radius;
		pos2.y = pos->y;
		pos2.z = pos->z;

		map_get_screen_coords_from_world (obj, pos, &spos1);

		map_get_screen_coords_from_world (obj, &pos2, &spos2);

		screen_radius = spos2.x - spos1.x;

		if (screen_radius > 0.0)
		{
			side = get_local_entity_int_value (group, INT_TYPE_SIDE);

			if (side == ENTITY_SIDE_BLUE_FORCE)
			{
				threat_circle_filled_colour.r = 20;
				threat_circle_filled_colour.g = 20;
				threat_circle_filled_colour.b = 200;
	
				threat_circle_outline_colour = ui_colour_dark_blue;
			}
			else
			{
				threat_circle_filled_colour.r = 200;
				threat_circle_filled_colour.g = 20;
				threat_circle_filled_colour.b = 20;
	
				threat_circle_outline_colour = ui_colour_dark_red;
			}

			if (active_radar)
			{
				threat_circle_filled_colour.a = 50;

				draw_filled_circle (spos1.x, spos1.z, screen_radius, circle_side_count, threat_circle_filled_colour);
			}
			else
			{
				threat_circle_outline_colour.a = 128;
			}
			
			draw_outline_circle (spos1.x, spos1.z, screen_radius, circle_side_count, threat_circle_outline_colour);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MIN_THREAT_CIRCLE_SIDES		16
#define MAX_THREAT_CIRCLE_SIDES		40

#define MIN_THREAT_CIRCLE_MAP_RADIUS	(100.0 * KILOMETRE)
#define MAX_THREAT_CIRCLE_MAP_RADIUS	(5.0 * KILOMETRE)

void map_draw_threat_circles (ui_object *obj, entity_sides side)
{
	entity
		*force,
		*group;

	entity_sub_types
		group_type;

	map_dimension_type
		*map_dimensions;

	float
		d,
		temp;

	int
		circle_side_count;

	if (global_layer_controls & (1 << MAP_LAYER_CONTROL_THREAT_CIRCLES))
	{				
		map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (obj);
	
		ASSERT (map_dimensions);
		
		force = get_local_force_entity (side);

		if (map_dimensions->size >= MIN_THREAT_CIRCLE_MAP_RADIUS)
		{
			circle_side_count = MIN_THREAT_CIRCLE_SIDES;
		}
		else if (map_dimensions->size <= MAX_THREAT_CIRCLE_MAP_RADIUS)
		{
			circle_side_count = MAX_THREAT_CIRCLE_SIDES;
		}
		else
		{
			d = (map_dimensions->size - MAX_THREAT_CIRCLE_MAP_RADIUS) / (MIN_THREAT_CIRCLE_MAP_RADIUS - MAX_THREAT_CIRCLE_MAP_RADIUS);

			temp = MAX_THREAT_CIRCLE_SIDES - (d * (MAX_THREAT_CIRCLE_SIDES - MIN_THREAT_CIRCLE_SIDES));

			convert_float_to_int (temp, &circle_side_count);
		}

		ASSERT ((circle_side_count >= MIN_THREAT_CIRCLE_SIDES) && (circle_side_count <= MAX_THREAT_CIRCLE_SIDES));
		
		//
		// SEA GROUPS
		//
	
		group = get_local_entity_first_child (force, LIST_TYPE_SEA_REGISTRY);
		
		while (group)
		{
			group_type = get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE);
	
			if (get_local_entity_int_value (group, INT_TYPE_AIR_ATTACK_STRENGTH) > 0)
			{
				map_draw_threat_circle (obj, group, circle_side_count);
			}
		
			group = get_local_entity_child_succ (group, LIST_TYPE_SEA_REGISTRY);
		}
	
		//
		// LAND GROUPS
		//
	
		group = get_local_entity_first_child (force, LIST_TYPE_GROUND_REGISTRY);
		
		while (group)
		{
			group_type = get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE);
	
			if (get_local_entity_int_value (group, INT_TYPE_AIR_ATTACK_STRENGTH) > 0)
			{
				map_draw_threat_circle (obj, group, circle_side_count);
			}
	
			group = get_local_entity_child_succ (group, LIST_TYPE_GROUND_REGISTRY);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define FORCE_DRAW_GROUP_MEMBERS_RADIUS	(16.0 * KILOMETRE)

static void map_draw_group (ui_object *obj, entity *en)
{
	vec3d
		*pos;

	entity_sub_types
		group_type;

	map_icon_type
		icon;

	const char
		*name;

	entity_sides
		side;

	entity
		*member,
		*player_group,
		*current_page_group;

	map_dimension_type
		*map_dimensions;

	int
		is_friendly;

	ASSERT (en);

	map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (obj);
	
	ASSERT (map_dimensions);
		
	side = get_local_entity_int_value (en, INT_TYPE_SIDE);
	is_friendly = side == get_local_entity_int_value (get_pilot_entity (), INT_TYPE_SIDE);

	if (get_gunship_entity ())
	{
		player_group = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_MEMBER);
	}
	else
	{
		player_group = NULL;
	}

	if (get_ui_object_drawable (campaign_page [CAMPAIGN_PAGE_GROUP]))
	{
		current_page_group = get_local_entity_safe_ptr (get_ui_object_item_number (campaign_page [CAMPAIGN_PAGE_GROUP]));
	}
	else
	{
		current_page_group = NULL;
	}

	if (is_friendly && ((en == player_group) || (en == current_page_group) || (map_dimensions->size < FORCE_DRAW_GROUP_MEMBERS_RADIUS)))
	{
		//
		// Draw individual members
		//

		member = get_local_entity_first_child (en, LIST_TYPE_MEMBER);

		while (member)
		{
			if (check_visible_entity (obj, member))
			{
				icon = get_local_entity_int_value (member, INT_TYPE_MAP_ICON);
		
				if (icon != MAP_ICON_NONE)
				{
					pos = get_local_entity_vec3d_ptr (member, VEC3D_TYPE_POSITION);
				
					map_draw_entity_icon (obj, member, pos, icon, side, 1.0);
				}
			}			

			member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
		}
	}
	else
	{
		//
		// draw group icon
		//
		
		if (check_visible_entity (obj, en))
		{
			icon = get_local_entity_int_value (en, INT_TYPE_MAP_ICON);
		
			if (icon != MAP_ICON_NONE)
			{
				group_type = get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);

//				if (!is_friendly && command_line_campaign_map_update_interval)
					pos = get_last_known_position(en);
/*				{
					// arneh, 2007-07-08 - only update map position if update interval has passed

					float last_update = get_local_entity_float_value (en, FLOAT_TYPE_LAST_SEEN_TIME);
					float time_since_last_update = current_time - last_update;

					if (time_since_last_update > command_line_campaign_map_update_interval)
					{
						pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

						set_local_entity_float_value (en, FLOAT_TYPE_LAST_SEEN_TIME, current_time);
						set_local_entity_vec3d (en, VEC3D_TYPE_LAST_KNOWN_POSITION, pos);
					}
					else
						pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_LAST_KNOWN_POSITION);
				}*/
//				else
//					pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);
				
				map_draw_entity_icon (obj, en, pos, icon, side, 1.0);
			
				if (get_current_list_mode () == COMMON_LIST_MODE_GROUP && is_friendly)
					if (group_database [group_type].default_entity_type == ENTITY_TYPE_HELICOPTER)
					{
						name = get_local_entity_string (en, STRING_TYPE_GROUP_CALLSIGN);
					
						map_draw_string (obj, pos, name, UI_FONT_ARIAL_14, &ui_colour_orange, FALSE);
					}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void map_draw_groups (ui_object *obj, entity_sides side)
{
	entity
		*force,
		*group,
		*current_page_group;

	entity_sub_types
		group_type;

	map_dimension_type
		*map_dimensions;

	map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (obj);

	ASSERT (map_dimensions);
	
	force = get_local_force_entity (side);

	if (get_ui_object_drawable (campaign_page [CAMPAIGN_PAGE_GROUP]))
	{
		current_page_group = get_local_entity_safe_ptr (get_ui_object_item_number (campaign_page [CAMPAIGN_PAGE_GROUP]));
	}
	else
	{
		current_page_group = NULL;
	}

	//
	// SEA GROUPS
	//

	group = get_local_entity_first_child (force, LIST_TYPE_SEA_REGISTRY);
	
	while (group)
	{
		group_type = get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE);

		if ((group == current_page_group) || (global_layer_controls & (1 << group_database [group_type].map_layer_type)))
		{				
			map_draw_group (obj, group);
		}
	
		group = get_local_entity_child_succ (group, LIST_TYPE_SEA_REGISTRY);
	}

	//
	// LAND GROUPS
	//

	group = get_local_entity_first_child (force, LIST_TYPE_GROUND_REGISTRY);
	
	while (group)
	{
		group_type = get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE);

		if ((group == current_page_group) || (global_layer_controls & (1 << group_database [group_type].map_layer_type)))
		{				
			map_draw_group (obj, group);
		}

		group = get_local_entity_child_succ (group, LIST_TYPE_GROUND_REGISTRY);
	}

	//
	// AIR GROUPS
	//

	group = get_local_entity_first_child (force, LIST_TYPE_AIR_REGISTRY);
	
	while (group)
	{
		group_type = get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE);

		if ((group == current_page_group) || (global_layer_controls & (1 << group_database [group_type].map_layer_type)))
		{
			if (get_local_entity_int_value (group, INT_TYPE_GROUP_MODE) != GROUP_MODE_IDLE)
			{
				map_draw_group (obj, group);
			}
		}
	
		group = get_local_entity_child_succ (group, LIST_TYPE_AIR_REGISTRY);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void map_draw_keysite (ui_object *obj, entity *en, map_icon_type overlay_icon)
{
	entity
		*pilot_force;

	vec3d
		*pos;

	entity_sub_types
		sub_type;

	entity_sides
		side,
		pilot_side;

	const char
		*name;
	char
		id [5];

	map_dimension_type
		*map_dimensions;

	map_icon_type
		icon;

	rgb_colour
		col;

	col = ui_colour_white;

	side = get_local_entity_int_value (en, INT_TYPE_SIDE);

	switch (side)
	{
		case ENTITY_SIDE_BLUE_FORCE:
		{
			col = ext_col_blue_force;

			break;
		}
		case ENTITY_SIDE_RED_FORCE:
		{
			col = ext_col_red_force;

			break;
		}
	}

	map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (obj);

	ASSERT (map_dimensions);
	
	pilot_side = get_local_entity_int_value (get_pilot_entity (), INT_TYPE_SIDE);

	pilot_force = get_local_force_entity (pilot_side);

	if (check_visible_entity (obj, en))
	{
		sub_type = get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);
			
		pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);
	
		//
		// Draw Icon
		//
									
		icon = get_local_entity_int_value (en, INT_TYPE_MAP_ICON);
	
		ASSERT (icon != MAP_ICON_NONE);
	
		map_draw_entity_icon (obj, en, pos, icon, side, 1.0);

		if (get_local_entity_parent (en, LIST_TYPE_CAMPAIGN_OBJECTIVE) == pilot_force)
		{
			//
			// Highlight as campaign objective
			//
										
			map_draw_entity_icon (obj, en, pos, MAP_ICON_CAMPAIGN_OBJECTIVE, ENTITY_SIDE_NEUTRAL, 1.0);
		}

		//
		// Draw Overlay Icon
		//
						
		if (overlay_icon != MAP_ICON_NONE)
		{
			map_draw_entity_icon (obj, NULL, pos, overlay_icon, ENTITY_SIDE_NEUTRAL, 1.0);
		}

		switch (sub_type)
		{
			case ENTITY_SUB_TYPE_KEYSITE_AIRBASE:
			case ENTITY_SUB_TYPE_KEYSITE_ANCHORAGE:
			{
				//
				// Print Name
				//

				name = get_local_entity_string (en, STRING_TYPE_KEYSITE_NAME);
		
				map_draw_string (obj, pos, name, UI_FONT_ARIAL_16, &col, FALSE);

				break;
			}
			case ENTITY_SUB_TYPE_KEYSITE_FARP:
			{
				sprintf (id, "%d", get_local_entity_int_value (en, INT_TYPE_KEYSITE_ID));

				map_draw_string (obj, pos, id, UI_FONT_UNSCALABLE_10, &ui_colour_white, TRUE);

				break;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void map_draw_keysites (ui_object *obj, entity_sides side)
{
	entity
		*force,
		*keysite;

	entity_sub_types
		sub_type;

	if ((global_layer_controls & (1 << MAP_LAYER_CONTROL_KEYSITES)) || (global_layer_controls & (1 << MAP_LAYER_CONTROL_SHIPS)))
	{
		force = get_local_force_entity (side);

		ASSERT (force);

		keysite = get_local_entity_first_child (force, LIST_TYPE_KEYSITE_FORCE);
		
		while (keysite)
		{
			if ((get_local_entity_int_value (keysite, INT_TYPE_IN_USE)) && (get_local_entity_int_value (keysite, INT_TYPE_ALIVE)))
			{
				sub_type = get_local_entity_int_value (keysite, INT_TYPE_ENTITY_SUB_TYPE);

				if (global_layer_controls & (1 << keysite_database [sub_type].map_layer_type))
				{
					map_draw_keysite (obj, keysite, MAP_ICON_NONE);
				}
			}
	
			keysite = get_local_entity_child_succ (keysite, LIST_TYPE_KEYSITE_FORCE);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void map_draw_towns (ui_object *obj)
{
	vec3d
		pos;

	population_name_database_type
		*item;

	map_dimension_type
		*map_dimensions;

	rgb_colour
		*col;

	col = &ui_colour_white;

	map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (obj);

	ASSERT (map_dimensions);
	
	item = population_name_database;
	
	while (item)
	{
		if (item->type == POPULATION_TYPE_TOWN)
		{
			if (map_dimensions->size <= (item->zoom * 2))
			{
				pos.x = item->x;
				pos.y = 0.0;
				pos.z = item->z;

				//
				// Print Name
				//

				ASSERT (item->name);

				map_draw_string (obj, &pos, item->name, UI_FONT_ARIAL_14, col, FALSE);
			}
		}

		item = item->next;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void map_draw_pilots (ui_object *obj, entity_sides side)
{
	entity
		*force,
		*pilot,
		*gunship;

	vec3d
		*pos;

	const char
		*name;

	map_dimension_type
		*map_dimensions;

	map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (obj);

	ASSERT (map_dimensions);
	
	force = get_local_force_entity (side);

	pilot = get_local_entity_first_child (force, LIST_TYPE_PILOT);
	
	while (pilot)
	{
		gunship = get_local_entity_parent (pilot, LIST_TYPE_AIRCREW);
		
		if (gunship)
		{
			if (get_local_entity_int_value (gunship, INT_TYPE_ALIVE))
			{
				if (check_visible_entity (obj, gunship))
				{
					pos = get_local_entity_vec3d_ptr (gunship, VEC3D_TYPE_POSITION);
			
					name = get_local_entity_string (pilot, STRING_TYPE_PILOTS_NAME);
				
					map_draw_entity_icon (obj, gunship, pos, MAP_ICON_PLAYER, side, 1.0);
	
					if (pilot == get_pilot_entity ())
					{
						map_draw_entity_icon (obj, gunship, pos, MAP_ICON_PLAYER_OVERLAY, ENTITY_SIDE_NEUTRAL, 1.0);
					}
	
					map_draw_string (obj, pos, name, UI_FONT_ARIAL_10, &ui_ingame_selected_text_colour, FALSE);
				}
			}
		}

		pilot = get_local_entity_child_succ (pilot, LIST_TYPE_PILOT);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void map_draw_missions (ui_object *obj, entity_sides side)
{
	entity
		*force,
		*keysite,
		*mission,
		*objective;

	vec3d
		*pos;

	map_dimension_type
		*map_dimensions;

	map_icon_type
		icon;

	char
		name [32];

	map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (obj);

	ASSERT (map_dimensions);
	
	icon = MAP_ICON_MISSION;

	if (global_layer_controls & (1 << MAP_LAYER_CONTROL_MISSIONS))
	{ 
		force = get_local_force_entity (side);
	
		keysite = get_local_entity_first_child (force, LIST_TYPE_KEYSITE_FORCE);
		
		while (keysite)
		{
			if (get_local_entity_int_value (keysite, INT_TYPE_IN_USE))
			{
				//
				// UNASSIGNED
				//
				
				mission = get_local_entity_first_child (keysite, LIST_TYPE_UNASSIGNED_TASK);

				while (mission)
				{
					if (get_local_entity_int_value (mission, INT_TYPE_VISIBLE_TASK))
					{
						objective = get_local_entity_parent (mission, LIST_TYPE_TASK_DEPENDENT);
	
						if (objective)
						{
							pos = get_last_known_position(objective);
	
							if (pos)
							{
								map_draw_entity_icon (obj, mission, pos, icon, side, 1.0);
		
								if (get_current_list_mode () == COMMON_LIST_MODE_MISSION)
								{
									sprintf (name, "%s #%d", get_trans (get_local_entity_string (mission, STRING_TYPE_SHORT_DISPLAY_NAME)), get_local_entity_int_value (mission, INT_TYPE_TASK_ID));
						
									map_draw_string (obj, pos, name, UI_FONT_ARIAL_14, &ui_colour_white, FALSE);
								}
							}
						}
					}
					
					mission = get_local_entity_child_succ (mission, LIST_TYPE_UNASSIGNED_TASK);
				}

				//
				// ASSIGNED
				//
				
				mission = get_local_entity_first_child (keysite, LIST_TYPE_ASSIGNED_TASK);

				while (mission)
				{
					if (get_local_entity_int_value (mission, INT_TYPE_VISIBLE_TASK))
					{
						objective = get_local_entity_parent (mission, LIST_TYPE_TASK_DEPENDENT);
	
						if (objective)
						{
							pos = get_last_known_position(objective);
	
							ASSERT (pos);
	
							map_draw_entity_icon (obj, mission, pos, icon, side, 1.0);
	
							if (get_current_list_mode () == COMMON_LIST_MODE_MISSION)
							{
								sprintf (name, "%s #%d", get_trans (get_local_entity_string (mission, STRING_TYPE_SHORT_DISPLAY_NAME)), get_local_entity_int_value (mission, INT_TYPE_TASK_ID));
					
								map_draw_string (obj, pos, name, UI_FONT_ARIAL_14, &ui_colour_orange, FALSE);
							}
						}
					}

					mission = get_local_entity_child_succ (mission, LIST_TYPE_ASSIGNED_TASK);
				}
			}
	
			keysite = get_local_entity_child_succ (keysite, LIST_TYPE_KEYSITE_FORCE);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void map_draw_symbol (ui_object *obj, vec3d *pos, unsigned char tag, font_types font, rgb_colour *col)
{

	vec3d
		screen_pos;

	char
		s [2];

	ASSERT (pos);

	map_get_screen_coords_from_world (obj, pos, &screen_pos);
		
	set_ui_font_type (font);

	set_ui_font_colour (*col);

	s [0] = tag;
	s [1] = 0;

	ui_display_text (s, screen_pos.x, screen_pos.z);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void map_draw_string (ui_object *obj, vec3d *pos, const char *string, font_types font, rgb_colour *col, int centered)
{
	vec3d
		screen_pos;

	float
		font_width,
		font_height;

	ASSERT (string);

	ASSERT (pos);

	map_get_screen_coords_from_world (obj, pos, &screen_pos);
		
	set_ui_font_type (font);

	set_ui_font_colour (*col);

	if (centered)
	{
		font_height = ui_get_font_height ();
	
		font_width = ui_get_string_length (string);
	
		ui_display_text (string, screen_pos.x - (font_width * 0.5), screen_pos.z - (font_height * 0.5));
	}
	else
	{
		ui_display_text (string, screen_pos.x, screen_pos.z);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void map_draw_icon (ui_object *obj, vec3d *pos, int icon, int side, float scale, float *distance)
{
	real_colour
		colour;

	vec3d
		screen_pos;

	texture_graphic
		*icon_graphic;

	int
		width,
		height;

	float
		x1, x2,
		y1, y2,
		wxmin, wxmax,
		wzmin, wzmax,
		sxmin, sxmax,
		symin, symax,
		mx, my,
		dx, dy;

	get_2d_terrain_map_world_dimensions (&wxmin, &wzmin, &wxmax, &wzmax);

	if (distance)
	{
		(*distance) = -1.0;
	}

	// N.B. wzmin is > wzmax !!
	if ((pos->x < wxmin) || (pos->x > wxmax) || (pos->z > wzmin) || (pos->z < wzmax))
	{
		return;
	}

	get_2d_terrain_map_screen_dimensions (&sxmin, &symin, &sxmax, &symax);

	map_get_screen_coords_from_world (obj, pos, &screen_pos);
		
	//
	// Always have to render to the video screen
	//
		
	ASSERT ( active_screen == video_screen );
	
	icon_graphic = map_icons [side][icon];

	ASSERT (icon_graphic);

	get_texture_graphic_source_dimensions (icon_graphic, &width, &height);

	ASSERT (scale > 0.0);

	scale *= 0.5;			// get radius from diametre

	x1 = screen_pos.x - ((float)width * scale);
	y1 = screen_pos.z - ((float)height * scale);

	x2 = screen_pos.x + ((float)width * scale);
	y2 = screen_pos.z + ((float)height * scale);

	colour.red = 255;
	colour.green = 255;
	colour.blue = 255;
	colour.alpha = 255;
	
	ui_draw_texture_graphic (x1, y1, x2, y2, icon_graphic, colour);

	if (distance)
	{
		if (obj == get_current_highlighted_object ())
		{
			mx = get_mouse_x ();
			my = get_mouse_y ();
			
			if ((mx > x1) && (mx < x2) && (my > y1) && (my < y2))
			{
				dx = mx - screen_pos.x;
				dy = my - screen_pos.z;
			
				(*distance) = ((dx * dx) + (dy * dy));
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void map_draw_entity_icon (ui_object *obj, entity *en, vec3d *pos, int icon, int side, float scale)
{
	map_dimension_type
		*map_dimensions;

	float
		distance;
	
	ASSERT (obj);

	ASSERT (pos);

	map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (obj);

	ASSERT (map_dimensions);

	map_draw_icon (obj, pos, icon, side, scale, &distance);

	//
	// Find closest icon to mouse
	//

	if (en)
	{
		if (obj == get_current_highlighted_object ())
		{
			if ((distance >= 0) && (distance <= map_dimensions->mouse_over_object.distance))
			{
				map_dimensions->mouse_over_object.type = MOUSE_OVER_OBJECT_ENTITY;

				map_dimensions->mouse_over_object.en = en;
		
				map_dimensions->mouse_over_object.distance = distance;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void map_draw_insert_waypoint_icon (ui_object *obj, entity *wp, vec3d *pos, int side)
{
	float
		scale,
		distance;

	int
		icon;

	map_dimension_type
		*map_dimensions;

	ASSERT (obj);

	ASSERT (pos);

	ASSERT (wp);

	map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (obj);

	ASSERT (map_dimensions);

	icon = MAP_ICON_WAYPOINT_INSERT;
	
	scale = ICON_RESOLUTION_SCALE;

	map_draw_icon (obj, pos, icon, side, scale, &distance);

	//
	// Find closest icon to mouse
	//

	if (obj == get_current_highlighted_object ())
	{
		if ((distance >= 0) && (distance <= map_dimensions->mouse_over_object.distance))
		{
			map_dimensions->mouse_over_object.type = MOUSE_OVER_OBJECT_WAYPOINT_ADD;

			map_dimensions->mouse_over_object.en = wp;

			map_dimensions->mouse_over_object.pos.x = pos->x;
			map_dimensions->mouse_over_object.pos.y = pos->y;
			map_dimensions->mouse_over_object.pos.z = pos->z;
	
			map_dimensions->mouse_over_object.distance = distance;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void map_draw_highlighted_insert_waypoint_icon (ui_object *obj, vec3d *pos)
{
	float
		scale;

	ASSERT (obj);

	ASSERT (pos);

	scale = ICON_RESOLUTION_SCALE;

	map_draw_icon (obj, pos, MAP_ICON_WAYPOINT_INSERT_HIGHLIGHTED, ENTITY_SIDE_NEUTRAL, scale, NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void map_draw_highlighted_group (ui_object *obj, entity *en, int overlay_icon, rgb_colour *col, float scale)
{
	int
		icon,
		side;

	vec3d
		*en_pos,
		*mission_pos,
		pos1,
		pos2;

	entity
		*mission,
		*objective;

	ASSERT (obj);

	ASSERT (en);

	ASSERT (col);

	//
	// Draw selected group member + mission it's doing
	//

	side = get_local_entity_int_value (en, INT_TYPE_SIDE);

	// get mission position
	mission_pos = NULL;

	if (side == get_local_entity_int_value (get_pilot_entity (), INT_TYPE_SIDE))
	{
		// get entity position
		en_pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);  // known to be friendly

		if (get_local_entity_type (en) == ENTITY_TYPE_GROUP)
		{
			mission = get_local_group_primary_task (en);
		}
		else
		{
			mission = get_local_entity_primary_task (en);
		}
	
		if (mission)
		{
			if (get_local_entity_int_value (mission, INT_TYPE_TASK_STATE) != TASK_STATE_COMPLETED)
			{
				objective = get_local_entity_parent (mission, LIST_TYPE_TASK_DEPENDENT);
	
				if (objective)
				{
					mission_pos = get_last_known_position (objective);

					if (mission_pos)
					{
						//
						// Draw connecting line
						//
				
						map_get_screen_coords_from_world (obj, en_pos, &pos1);
						map_get_screen_coords_from_world (obj, mission_pos, &pos2);
				
						draw_line (pos1.x, pos1.z, pos2.x, pos2.z, *col);
				
						//
						// Draw Mission Icon
						//
				
						icon = get_local_entity_int_value (mission, INT_TYPE_MAP_ICON);
				
						ASSERT (icon != MAP_ICON_NONE);
				
						map_draw_entity_icon (obj, mission, mission_pos, icon, side, 1.0);
					
						map_draw_entity_icon (obj, NULL, mission_pos, overlay_icon, ENTITY_SIDE_NEUTRAL, 1.0);
					}
				}
			}
		}
	}
	else
		en_pos = get_last_known_position(en);

	//
	// Draw Group / Member Icon
	//

	ASSERT (en_pos);

	icon = get_local_entity_int_value (en, INT_TYPE_MAP_ICON);

	if (get_local_entity_type (en) == ENTITY_TYPE_HELICOPTER)
	{
		if (get_local_entity_int_value (en, INT_TYPE_PLAYER))
		{
			icon = MAP_ICON_PLAYER;
		}
	}

	ASSERT (icon != MAP_ICON_NONE);

	map_draw_entity_icon (obj, en, en_pos, icon, side, 1.0);
	
	map_draw_entity_icon (obj, NULL, en_pos, overlay_icon, ENTITY_SIDE_NEUTRAL, scale);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void map_draw_highlighted_mission (ui_object *obj, entity *en, int overlay_icon, rgb_colour *col, float scale)
{
	int
		icon,
		side;

	vec3d
		*mission_pos,
		*group_pos,
		*base_pos,
		pos1,
		pos2;

	entity
		*base,
		*group,
		*guide,
		*objective;

	ASSERT (obj);

	ASSERT (en);

	ASSERT (col);

	//
	// Draw mission and group doing it (if assigned), and base attached to
	//

	side = get_local_entity_int_value (en, INT_TYPE_SIDE);

	// get entity position
	objective = get_local_entity_parent (en, LIST_TYPE_TASK_DEPENDENT);

	if (objective)
	{
		mission_pos = get_last_known_position(objective);

		ASSERT (mission_pos);
	}
	else
	{
		return;
	}

	if (side == get_local_entity_int_value (get_pilot_entity (), INT_TYPE_SIDE))
	{
		group = NULL;
	
		group_pos = NULL;
	
		base = NULL;
	
		base_pos = NULL;
	
		// get group position
		guide = get_local_entity_first_child (en, LIST_TYPE_GUIDE);
	
		if (guide)
		{
			group = get_local_entity_parent (guide, LIST_TYPE_GUIDE_STACK);
	
			ASSERT (group);
	
			group_pos = get_local_entity_vec3d_ptr (group, VEC3D_TYPE_POSITION);
		}
	
		// get base position
		if (get_local_entity_int_value (en, INT_TYPE_ASSESS_LANDING))
		{
			if (get_local_entity_int_value (en, INT_TYPE_TASK_STATE) == TASK_STATE_UNASSIGNED)
			{
				base = get_local_entity_parent (en, LIST_TYPE_UNASSIGNED_TASK);
			}
			else
			{
				base = get_local_entity_ptr_value (en, PTR_TYPE_RETURN_KEYSITE);
			}
	
			if (base)
			{
				base_pos = get_local_entity_vec3d_ptr (base, VEC3D_TYPE_POSITION);
	
				ASSERT (base_pos);
			}
		}
	
		//
		// Draw connecting lines
		//
	
		map_get_screen_coords_from_world (obj, mission_pos, &pos1);
	
		if (group)
		{
			ASSERT (group_pos);
			
			map_get_screen_coords_from_world (obj, group_pos, &pos2);
	
			draw_line (pos1.x, pos1.z, pos2.x, pos2.z, *col);

			//
			// Draw Group Icon
			//
	
			icon = get_local_entity_int_value (group, INT_TYPE_MAP_ICON);
	
			ASSERT (icon != MAP_ICON_NONE);
	
			map_draw_entity_icon (obj, group, group_pos, icon, side, 1.0);
		
			map_draw_entity_icon (obj, NULL, group_pos, overlay_icon, ENTITY_SIDE_NEUTRAL, 1.0);
		}
		else if (base)
		{
			ASSERT (base_pos);

			map_get_screen_coords_from_world (obj, base_pos, &pos2);
	
			draw_line (pos1.x, pos1.z, pos2.x, pos2.z, *col);
	
			//
			// Draw Base Icon
			//
	
			map_draw_keysite (obj, base, overlay_icon);
		}
	}
	
	//
	// Draw Mission Icon
	//

	icon = get_local_entity_int_value (en, INT_TYPE_MAP_ICON);

	ASSERT (icon != MAP_ICON_NONE);

	map_draw_entity_icon (obj, en, mission_pos, icon, side, 1.0);
	
	map_draw_entity_icon (obj, NULL, mission_pos, overlay_icon, ENTITY_SIDE_NEUTRAL, scale);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void map_draw_highlighted_base (ui_object *obj, entity *en, int overlay_icon)
{
	ASSERT (obj);

	ASSERT (en);

	//
	// Draw selected Base
	//

	map_draw_keysite (obj, en, overlay_icon);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void map_draw_highlighted_waypoint (ui_object *obj, entity *en, int overlay_icon, rgb_colour *col, float scale)
{
	vec3d
		*pos;

	int
		icon,
		waypoint_overlay_icon;

	entity
		*task;

	entity_sides
		side;

	map_dimension_type
		*map_dimensions;

	ASSERT (obj);

	ASSERT (en);

	ASSERT (col);

	map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (obj);

	ASSERT (map_dimensions);
	
	//
	// Draw selected waypoint
	//

	pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	ASSERT (pos);
	
	icon = get_local_entity_int_value (en, INT_TYPE_MAP_ICON);

	ASSERT (icon != MAP_ICON_NONE);

	task = get_local_entity_parent (en, LIST_TYPE_WAYPOINT);

	ASSERT (task);

	side = get_local_entity_int_value (task, INT_TYPE_SIDE);

	map_draw_entity_icon (obj, en, pos, icon, side, ICON_RESOLUTION_SCALE);

	waypoint_overlay_icon = MAP_ICON_NONE;

	if (en == map_dimensions->selected_entity)
	{
		//
		// Selected Icons
		//
		
		switch (icon)
		{
			case MAP_ICON_WAYPOINT_NAV:
			{
				waypoint_overlay_icon = MAP_ICON_WAYPOINT_NAV_SELECTED;

				break;
			}
			case MAP_ICON_WAYPOINT_TARGET:
			{
				waypoint_overlay_icon = MAP_ICON_WAYPOINT_TARGET_SELECTED;

				break;
			}
		}
	}
	else
	{
		//
		// Highlighted Icons
		//
		
		switch (icon)
		{
			case MAP_ICON_WAYPOINT_NAV:
			{
				waypoint_overlay_icon = MAP_ICON_WAYPOINT_NAV_HIGHLIGHTED;

				break;
			}
			case MAP_ICON_WAYPOINT_TARGET:
			{
				waypoint_overlay_icon = MAP_ICON_WAYPOINT_TARGET_HIGHLIGHTED;

				break;
			}
		}
	}

	map_draw_entity_icon (obj, NULL, pos, waypoint_overlay_icon, ENTITY_SIDE_NEUTRAL, ICON_RESOLUTION_SCALE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void map_draw_highlighted_entity (ui_object *obj, entity *en, int overlay_icon, rgb_colour *col, float scale)
{
	ASSERT (en);

	ASSERT (obj);

	ASSERT (col);

	switch (get_local_entity_type (en))
	{
		case ENTITY_TYPE_HELICOPTER:
		case ENTITY_TYPE_FIXED_WING:
		case ENTITY_TYPE_ROUTED_VEHICLE:
		case ENTITY_TYPE_SHIP_VEHICLE:
		case ENTITY_TYPE_ANTI_AIRCRAFT:
		case ENTITY_TYPE_GROUP:
		{
			//
			// Draw selected group member + mission it's doing
			//

			map_draw_highlighted_group (obj, en, overlay_icon, col, scale);

			break;
		}
		case ENTITY_TYPE_TASK:
		{
			map_draw_highlighted_mission (obj, en, overlay_icon, col, scale);

			break;
		}
		case ENTITY_TYPE_KEYSITE:
		{
			map_draw_highlighted_base (obj, en, overlay_icon);

			break;
		}
		case ENTITY_TYPE_WAYPOINT:
		{
			map_draw_highlighted_waypoint (obj, en, overlay_icon, col, scale);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void map_draw_mouse_over_entity (ui_object *obj, entity *en)
{
	ASSERT (en);

	ASSERT (obj);

	#if ANIMATE_MOUSE_OVER_ICON	
	{
		float
			x,
			scale;

		x = (2.0 * animation_timer) - 1.0;

		scale = 1.0 + (0.5 * (x * x));

		map_draw_highlighted_entity (obj, en, MAP_ICON_HIGHLIGHT, &sys_col_white, scale);
	}
	#else

	map_draw_highlighted_entity (obj, en, MAP_ICON_HIGHLIGHT, &sys_col_white, 1.0);

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void map_draw_subject_entity (ui_object *obj)
{
	entity
		*en;

	ASSERT (obj);

	en = NULL;

	if (get_ui_object_drawable (campaign_page [CAMPAIGN_PAGE_GROUP]))
	{
		//
		// Draw selected group member + mission it's doing
		//

		en = get_group_page_member_list_current_entity ();
	}
/*
	else if (get_ui_object_drawable (campaign_page [CAMPAIGN_PAGE_BRIEFING]))
	{
		//
		// Draw mission icon + group doing it
		//

		en = get_local_entity_safe_ptr (get_ui_object_item_number (campaign_page [CAMPAIGN_PAGE_BRIEFING]));

		ASSERT (en);
	}
*/
	else if (get_ui_object_drawable (campaign_page [CAMPAIGN_PAGE_BASE]))
	{
		//
		// Draw base icon
		// 

		en = get_local_entity_safe_ptr (get_ui_object_item_number (campaign_page [CAMPAIGN_PAGE_BASE]));

		ASSERT (en);
	}

	if (en)
	{
		map_draw_highlighted_entity (obj, en, MAP_ICON_SELECTED, &sys_col_yellow, 1.0);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void bound_map_extents (ui_object *obj, float *w, float *h)
{
	float
		width,
		height,
		x_size,
		y_size;

	map_dimension_type
		*map_dimensions;

	ASSERT (obj);

	map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (obj);

	ASSERT (map_dimensions);
	
	x_size = get_ui_object_x_size (obj);

	y_size = get_ui_object_y_size (obj);

	//
	// Correct Aspect Ratio + Bound Size
	//
	
	if (x_size < y_size)
	{
		height = map_dimensions->size;

		width = map_dimensions->size * (x_size / y_size);
	}
	else if (x_size > y_size)
	{
		width = map_dimensions->size;

		height = map_dimensions->size * (y_size / x_size);
	}
	else
	{
		width = map_dimensions->size;

		height = map_dimensions->size;
	}

	if (width > MAX_MAP_X)
	{
		height *= MAX_MAP_X / width;

		width = MAX_MAP_X;
	}

	if (height > MAX_MAP_Z)
	{
		width *= MAX_MAP_Z / height;

		height = MAX_MAP_Z;
	}

	//
	// Bound Map
	//

	map_dimensions->size = max (width, height);

	map_dimensions->x = bound (map_dimensions->x, width / 2.0, MAX_MAP_X - width / 2.0);
	map_dimensions->z = bound (map_dimensions->z, height / 2.0, MAX_MAP_Z - height / 2.0);

	if (w)
	{
		*w = width;
	}

	if (h)
	{
		*h = height;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_2d_terrain_texture_overlays (ui_object *obj, float x, float z, float width, float height)
{
	map_dimension_type
		*map_dimensions;

	real_colour
		colour,
		specular;
	
	float
		x_size,
		y_size,
		u_scale,
		v_scale,
		x1, y1,
		x2, y2,
		u1, v1,
		u2, v2;

	int
		ix,
		iy,
		iwidth,
		iheight;

	ASSERT (obj);

	ASSERT (map_overlay);

	map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (obj);

	ASSERT (map_dimensions);
	
	if (
			(global_layer_controls & (1 << MAP_LAYER_CONTROL_SECTOR_SIDES)) ||
			(global_layer_controls & (1 << MAP_LAYER_CONTROL_FOG_OF_WAR))
		)
	{
		if ( d3d_in_3d_scene )
		{
			u_scale = (float)NUM_MAP_X_SECTORS / (float)MAP_OVERLAY_TEXTURE_SIZE;
			v_scale = (float)NUM_MAP_Z_SECTORS / (float)MAP_OVERLAY_TEXTURE_SIZE;

			x_size = get_ui_object_x_size (obj);
			y_size = get_ui_object_y_size (obj);

			x1 = get_ui_object_x (obj);
			y1 = get_ui_object_y (obj);
		
			convert_float_to_int (x1, &ix);
			convert_float_to_int (y1, &iy);

			convert_float_to_int (x_size, &iwidth);
			convert_float_to_int (y_size, &iheight);

			x1 = ix;
			y1 = iy;

			x_size = iwidth;
			y_size = iheight;

			x2 = x1 + x_size;
			y2 = y1 + y_size;

			u1 = u_scale * (x - (width * 0.5)) / (MAX_MAP_X - MIN_MAP_X);
			v1 = v_scale * (z - (height * 0.5)) / (MAX_MAP_Z - MIN_MAP_Z);

			u2 = u_scale * (x + (width * 0.5)) / (MAX_MAP_X - MIN_MAP_X);
			v2 = v_scale * (z + (height * 0.5)) / (MAX_MAP_Z - MIN_MAP_Z);

			//
			// Always have to render to the video screen
			//
		
			ASSERT ( active_screen == video_screen );
	
			colour.red = 255;
			colour.green = 255;
			colour.blue = 255;
			colour.alpha = 255;
	
			specular.red = 0;
			specular.green = 0;
			specular.blue = 0;
			specular.alpha = 255;
		
			set_d3d_flat_shaded_textured_renderstate (map_overlay);
			set_d3d_transparency_on ();
			set_d3d_zbuffer_comparison ( FALSE );
			set_d3d_texture_wrapping ( 0, FALSE );
			set_d3d_texture_mag_filtering (TRUE);
			set_d3d_texture_min_filtering (TRUE);
			set_d3d_texture_mip_filtering (FALSE);
			
			{
				vertex
					quad[4];
		
				//
				// Set up quad vertices
				//

				quad[0].i = x1;
				quad[0].j = y1;
				quad[0].u = u1;
				quad[0].v = v1;
				quad[0].q = 0.1;
				quad[0].z = 100;
				quad[0].next_vertex = &quad[1];
		
				quad[1].i = x2;
				quad[1].j = y1;
				quad[1].u = u2;
				quad[1].v = v1;
				quad[1].q = 0.1;
				quad[1].z = 100;
				quad[1].next_vertex = &quad[2];
		
				quad[2].i = x2;
				quad[2].j = y2;
				quad[2].u = u2;
				quad[2].v = v2;
				quad[2].q = 0.1;
				quad[2].z = 100;
				quad[2].next_vertex = &quad[3];
		
				quad[3].i = x1;
				quad[3].j = y2;
				quad[3].u = u1;
				quad[3].v = v2;
				quad[3].q = 0.1;
				quad[3].z = 100;
				quad[3].next_vertex = NULL;
		
				draw_wbuffered_flat_shaded_textured_polygon ( quad, colour, specular );
			}
		
			flush_triangle_primitives ();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 1

static void create_fog_of_war_texture_overlay (void)
{
	int
		side,
		fog,
		x, z,
		tx, tz,
		sx, sz;

	float
		val,
		max_fog;

	rgb_colour
		col;

	entity
		*sec;

	ASSERT (map_overlay);
	ASSERT (get_pilot_entity());

	side = get_local_entity_int_value (get_pilot_entity (), INT_TYPE_SIDE);
	
	max_fog = get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_FOG_OF_WAR_MAXIMUM_VALUE);

	col.r = 0;
	col.g = 0;
	col.b = 0;

	for (z = -1; z < NUM_MAP_Z_SECTORS; z++)
	{
		sz = max (z, 0);

		tz = min (((NUM_MAP_Z_SECTORS - z) - 1), (MAP_OVERLAY_TEXTURE_SIZE - 1));

		for (x = 0; x <= NUM_MAP_X_SECTORS; x++)
		{
			sx = min (x, NUM_MAP_X_SECTORS - 1);

			tx = min (x, (MAP_OVERLAY_TEXTURE_SIZE - 1));

			sec = get_local_raw_sector_entity (sx, sz);

			ASSERT (sec);

			val = 140.0 * (1.0 - (get_sector_fog_of_war_value (sec, side) / max_fog));

			convert_float_to_int (val, &fog);

			// alpha
			col.a = fog;

			set_pixel (tx, tz, col);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#else

static void create_fog_of_war_texture_overlay (void)
{
	int
		side,
		fog,
		x, z,
		tx, tz,
		sx, sz;

	float
		val;

	rgb_colour
		col;

	ASSERT (map_overlay);

	side = get_local_entity_int_value (get_pilot_entity (), INT_TYPE_SIDE);
	
	col.a = 255;

	for (z = -1; z < NUM_MAP_Z_SECTORS; z++)
	{
		sz = max (z, 0);

		tz = min (((NUM_MAP_Z_SECTORS - z) - 1), (MAP_OVERLAY_TEXTURE_SIZE - 1));

		for (x = 0; x <= NUM_MAP_X_SECTORS; x++)
		{
			sx = min (x, NUM_MAP_X_SECTORS - 1);

			tx = min (x, (MAP_OVERLAY_TEXTURE_SIZE - 1));

			val = 255.0 * get_imap_value (IMAP_BASE_DISTANCE, side, sx, sz);

			convert_float_to_int (val, &fog);

			col.r = fog;
			col.g = fog;
			col.b = fog;

			set_pixel (tx, tz, col);
		}
	}
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void create_sector_side_texture_overlay (void)
{
	int
		side,
		band,
		temp,
		x, z,
		tx, tz,
		sx, sz;

	float
		val,
		ratio;

	rgb_colour
		col;

	const map_side_band_type
		*band_data; 

	ASSERT (map_overlay);

	side = get_local_entity_int_value (get_pilot_entity (), INT_TYPE_SIDE);
	
	for (z = -1; z < NUM_MAP_Z_SECTORS; z++)
	{
		sz = max (z, 0);

		tz = min (((NUM_MAP_Z_SECTORS - z) - 1), (MAP_OVERLAY_TEXTURE_SIZE - 1));

		for (x = 0; x <= NUM_MAP_X_SECTORS; x++)
		{
			sx = min (x, NUM_MAP_X_SECTORS - 1);

			tx = min (x, (MAP_OVERLAY_TEXTURE_SIZE - 1));

			ratio = get_local_sector_side_ratio (sx, sz, ENTITY_SIDE_BLUE_FORCE);

			band = 0;

			band_data = NULL;

			while (TRUE)
			{
				band_data = &map_side_band_data [band];

				ASSERT (band_data->min >= 0.0);
				ASSERT (band_data->max <= 1.0);

				if ((ratio >= band_data->min) && (ratio <= band_data->max))
				{
					break;
				}

				band ++;
			}

			ASSERT (band_data);

			// red
			val = 255.0 * (band_data->red_scale);
			convert_float_to_int (val, &temp);
			col.r = temp;

			// green
			col.g = 0;

			// blue
			val = 255.0 * (band_data->blue_scale);
			convert_float_to_int (val, &temp);
			col.b = temp;

			// alpha
			col.a = 192;

			set_pixel (tx, tz, col);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
static void create_supply_level_texture_overlay (void)
{
	int
		side,
		x, z,
		tx, tz,
		sx, sz;

	rgb_colour
		col;

	ASSERT (map_overlay);

	side = get_local_entity_int_value (get_pilot_entity (), INT_TYPE_SIDE);
	
	if (supply_heat_map == NULL)
	{
		build_supply_heat_map ();
	}

	for (z = -1; z < NUM_MAP_Z_SECTORS; z++)
	{
		sz = max (z, 0);

		tz = min (((NUM_MAP_Z_SECTORS - z) - 1), (MAP_OVERLAY_TEXTURE_SIZE - 1));

		for (x = 0; x <= NUM_MAP_X_SECTORS; x++)
		{
			sx = min (x, NUM_MAP_X_SECTORS - 1);

			tx = min (x, (MAP_OVERLAY_TEXTURE_SIZE - 1));


			col.r = supply_heat_bitmap [(sz * NUM_MAP_X_SECTORS * 3) + (sx * 3)];

			col.g = supply_heat_bitmap [(sz * NUM_MAP_X_SECTORS * 3) + (sx * 3) + 1];

			col.b = supply_heat_bitmap [(sz * NUM_MAP_X_SECTORS * 3) + (sx * 3) + 2];

			col.a = supply_heat_map [(NUM_MAP_X_SECTORS * sz) + sx];


			set_pixel (tx, tz, col);
		}
	}
}
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_2d_terrain_texture_overlays (void)
{
	screen
		*old_screen;

	ASSERT (map_overlay);

	debug_assert (NUM_MAP_X_SECTORS <= MAP_OVERLAY_TEXTURE_SIZE);
	debug_assert (NUM_MAP_Z_SECTORS <= MAP_OVERLAY_TEXTURE_SIZE);

	old_screen = get_active_screen ();

	lock_screen (map_overlay);

	set_active_screen (map_overlay);
	
	if (global_layer_controls & (1 << MAP_LAYER_CONTROL_SECTOR_SIDES))
	{
		//
		// SIDE DATA
		//

		create_sector_side_texture_overlay ();
	}
	else if (global_layer_controls & (1 << MAP_LAYER_CONTROL_FOG_OF_WAR))
	{
		//
		// FOG OF WAR
		//

		create_fog_of_war_texture_overlay ();
	}

	unlock_screen (map_overlay);

	set_active_screen (old_screen);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_map_overlays (void)
{
	create_2d_terrain_texture_overlays ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_map_event (int type, float x, float z, float lifetime)
{
	map_event_type
		*new_event;

	new_event = malloc_fast_mem (sizeof (map_event_type));

	new_event->type = type;
	new_event->x = x;
	new_event->z = z;
	new_event->t = lifetime;
	new_event->lifetime = lifetime;

	new_event->next = map_events;
	new_event->prev = NULL;

	if (map_events)
	{
		map_events->prev = new_event;
	}

	map_events = new_event;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void remove_map_event (map_event_type *event)
{
	map_event_type
		*prev,
		*next;

	ASSERT (event);

	prev = event->prev;

	next = event->next;

	if (prev)
	{
		prev->next = next;
	}

	if (next)
	{
		next->prev = prev;
	}

	if (event == map_events)
	{
		ASSERT (!prev);

		map_events = next;
	}

	free_mem (event);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_map_events (void)
{
	map_event_type
		*event,
		*next;

	event = map_events;

	while (event)
	{
		next = event->next;

		event->t -= get_delta_time ();

		if (event->t < 0.0)
		{
			remove_map_event (event);
		}

		event = next;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_map_animations (void)
{
	animation_timer += get_delta_time ();
	
	animation_timer = frac (animation_timer);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
void map_draw_events (ui_object *obj)
{
	map_event_type
		*event;

	vec3d
		pos;

	float
		scale;

	ASSERT (obj);

	pos.y = 0.0;

	event = map_events;

	while (event)
	{
		pos.x = event->x;
		pos.z = event->z;

		switch (event->type)
		{
			case MAP_EVENT_LOG_EVENT:
			{
				scale = 0.25 + (1.75 * (event->t / event->lifetime));

				map_draw_entity_icon (obj, NULL, &pos, MAP_ICON_EVENT, ENTITY_SIDE_NEUTRAL, scale);

				break;
			}

			case MAP_EVENT_EXPLOSION:
			{
				scale = 0.25 + (1.75 * (event->t / event->lifetime));

				map_draw_entity_icon (obj, NULL, &pos, MAP_ICON_EXPLOSION, ENTITY_SIDE_NEUTRAL, scale);

				break;
			}
		}

		event = event->next;
	}
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define OPTIMAL_NUMBER_OF_GRID_LINES				12.0 // this is the maximum number of grid lines (minimum will be half this value, average ... well you can work that out)
#define GRID_LINE_MINIMUM_SPACING					128.0
#define Y_BORDER											0.0
#define X_BORDER											5.0

// There are two kinds of Map Grid drawing functions, speed critical and space critical... this isn't the speed critical one ;)

void map_draw_grid (ui_object *obj)
{

	char
		scale_text [32],
		grid_number [10];

	float
		wxmin,
		wzmin,
		wxmax = 0,
		wzmax = 0,
		width,
		number_of_grid_lines,
		one_over_sector_side_length;

	int
		grid_spacing = 0,
		inew_wxmin,
		inew_wzmin,
		inew_wxmax,
		inew_wzmax,
		grid_loop;

	vec3d
		pos1,
		pos2;

	if (global_layer_controls & (1 << MAP_LAYER_CONTROL_GRID))
	{

		one_over_sector_side_length = 1.0 / SECTOR_SIDE_LENGTH;
	
		get_2d_terrain_map_world_dimensions (&wxmin, &wzmin, &wxmax, &wzmax);

		inew_wxmin = (((int) (wxmin * one_over_sector_side_length)) - 1.0) * SECTOR_SIDE_LENGTH;
		inew_wxmax = (((int) (wxmax * one_over_sector_side_length)) + 1.0) * SECTOR_SIDE_LENGTH;

		// Z max and min around wrong way !
		inew_wzmin = (((int) (wzmax * one_over_sector_side_length)) - 1.0) * SECTOR_SIDE_LENGTH;
		inew_wzmax = (((int) (wzmin * one_over_sector_side_length)) + 1.0) * SECTOR_SIDE_LENGTH;

		inew_wxmin = bound (inew_wxmin, 0.0, MAX_MAP_X);
		inew_wxmax = bound (inew_wxmax, 0.0, MAX_MAP_X);
		inew_wzmin = bound (inew_wzmin, 0.0, MAX_MAP_Z);
		inew_wzmax = bound (inew_wzmax, 0.0, MAX_MAP_Z);

		width = fabs (wxmax - wxmin);

		grid_spacing = GRID_LINE_MINIMUM_SPACING;

		number_of_grid_lines = width / grid_spacing;

		while (number_of_grid_lines > OPTIMAL_NUMBER_OF_GRID_LINES)
		{

			grid_spacing *= 2;

			number_of_grid_lines *= 0.5;
		}

		set_ui_font_type (UI_FONT_ARIAL_14);

		set_ui_font_colour (ui_colour_white);

		// along the X

		for (grid_loop = inew_wxmin; grid_loop <= inew_wxmax; grid_loop += grid_spacing)
		{

			pos1.x = grid_loop;
			pos1.z = wzmin;
			pos2.x = grid_loop;
			pos2.z = wzmax;

			if ((grid_loop >= wxmin) && (grid_loop <= wxmax))
			{

				map_get_screen_coords_from_world (obj, &pos1, &pos1);

				map_get_screen_coords_from_world (obj, &pos2, &pos2);

				if ((grid_loop % SECTOR_SIDE_LENGTH) == 0)
				{

					// sector boundary

					draw_line (pos1.x, pos1.z, pos2.x, pos2.z, sys_col_white);

					sprintf (grid_number, "%03d", (int) (grid_loop * one_over_sector_side_length));

					ui_display_text (grid_number, pos1.x, pos1.z - Y_BORDER);
				}
				else
				{

					// sub_sector division

					draw_line (pos1.x, pos1.z, pos2.x, pos2.z, sys_col_slate_grey);
				}
			}
		}

		// down the Z

		for (grid_loop = inew_wzmin; grid_loop <= inew_wzmax; grid_loop += grid_spacing)
		{

			pos1.x = wxmin;
			pos1.z = grid_loop;
			pos2.x = wxmax;
			pos2.z = grid_loop;

			if ((grid_loop >= wzmax) && (grid_loop <= wzmin))
			{

				map_get_screen_coords_from_world (obj, &pos1, &pos1);

				map_get_screen_coords_from_world (obj, &pos2, &pos2); 

				if ((grid_loop % SECTOR_SIDE_LENGTH) == 0)
				{
	
					// sector boundary

					draw_line (pos1.x, pos1.z, pos2.x, pos2.z, sys_col_white);

					sprintf (grid_number, "%03d", (int) (grid_loop * one_over_sector_side_length));

					ui_display_text (grid_number, pos1.x + X_BORDER, pos1.z - ui_get_font_height ());
				}
				else
				{

					// sub_sector division
			
					draw_line (pos1.x, pos1.z, pos2.x, pos2.z, sys_col_slate_grey);
				}
			}
		}

		//
		// Draw scale
		//

		{
			int value = (grid_spacing / 128) * 125; // binary -> decimal
			if (value >= 1000) {
				value /= 1000;	// m->km
			}

			sprintf(scale_text, "%s : %d %sm",
					get_trans("Grid"),
					value,
					(grid_spacing >= 1024) ? "k" : "");
		}

		pos1.x = wxmax;
		pos1.z = wzmax;

		map_get_screen_coords_from_world (obj, &pos1, &pos1);
		
// GCsDriver  08-12-2007
//		set_ui_font_colour (sys_col_slate_grey);
		set_ui_font_colour (ui_colour_white);
		
		ui_display_text (scale_text, pos1.x - (ui_get_string_length (scale_text) + 5), pos1.z - ui_get_font_height ());
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void map_draw_track_entity (ui_object *obj, entity *en)
{
	const char
		*name;
	char
		text [64];

	float
		wxmin,
		wzmin,
		wxmax,
		wzmax;

	static float
		flash_timer = 0.0;

	vec3d
		pos;

	entity
		*pilot,
		*group;

	ASSERT (en);

	if (flash_timer < 0.6)
	{
		get_2d_terrain_map_world_dimensions (&wxmin, &wzmin, &wxmax, &wzmax);
	
		sprintf (text, "");

		if (get_local_entity_int_value (en, INT_TYPE_IDENTIFY_AIRCRAFT))
		{
			pilot = get_local_entity_first_child (en, LIST_TYPE_AIRCREW);

			if (pilot)
			{
				sprintf (text, "%s: %s", get_trans ("Tracking"), get_local_entity_string (pilot, STRING_TYPE_PILOTS_NAME)); 
			}
			else
			{
				group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

				if (group)
				{
					sprintf (text, "%s: %s 1-%d",
								get_trans ("Tracking"), 
								get_local_entity_string (group, STRING_TYPE_GROUP_CALLSIGN),
								get_local_entity_int_value (en, INT_TYPE_GROUP_MEMBER_ID));
				}
			}
		}
		else
		{
			name = get_local_entity_string (en, STRING_TYPE_FULL_NAME); 

			if (name)
			{
				sprintf (text, "%s: %s", get_trans ("Tracking"), name); 
			}
		}
		
		pos.x = wxmin;
		pos.z = wzmax;
	
		map_get_screen_coords_from_world (obj, &pos, &pos);
		
		set_ui_font_type (UI_FONT_ARIAL_14);

		set_ui_font_colour (ui_ingame_selected_text_colour);
		
		ui_display_text (text, pos.x + 5, pos.z - ui_get_font_height ());
	}

	flash_timer = frac (flash_timer + get_delta_time ());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void toggle_current_map_maximise_event (event *ev)
{
	ui_object
		*obj;

	obj = last_drawn_map_object;

	if (obj)
	{
		toggle_full_screen_function (obj, NULL);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void shift_current_map_up_event (event *ev)
{
	ui_object
		*obj;

	map_dimension_type
		*map_dimensions;

	float
		d;

	obj = last_drawn_map_object;

	if (obj)
	{
		map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (obj);

		ASSERT (map_dimensions);

		d = map_dimensions->size * 0.2;
	
		map_dimensions->z += d;

		bound_map_extents (obj, NULL, NULL);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void shift_current_map_down_event (event *ev)
{
	ui_object
		*obj;

	map_dimension_type
		*map_dimensions;

	float
		d;

	obj = last_drawn_map_object;

	if (obj)
	{
		map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (obj);

		ASSERT (map_dimensions);

		d = map_dimensions->size * 0.2;
	
		map_dimensions->z -= d;

		bound_map_extents (obj, NULL, NULL);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void shift_current_map_left_event (event *ev)
{
	ui_object
		*obj;

	map_dimension_type
		*map_dimensions;

	float
		d;

	obj = last_drawn_map_object;

	if (obj)
	{
		map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (obj);

		ASSERT (map_dimensions);

		d = map_dimensions->size * 0.2;
	
		map_dimensions->x -= d;

		bound_map_extents (obj, NULL, NULL);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void shift_current_map_right_event (event *ev)
{
	ui_object
		*obj;

	map_dimension_type
		*map_dimensions;

	float
		d;

	obj = last_drawn_map_object;

	if (obj)
	{
		map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (obj);

		ASSERT (map_dimensions);

		d = map_dimensions->size * 0.2;
	
		map_dimensions->x += d;

		bound_map_extents (obj, NULL, NULL);
	}
}

// Jabberwock 031020 Fine mouse panning

void fine_current_map_up_event (event *ev)
{
	ui_object
		*obj;

	map_dimension_type
		*map_dimensions;

	float
		d;

	obj = last_drawn_map_object;

	if ((obj) && (get_in_flight_game_mode () == IN_FLIGHT_GAME_MODE_PLANNER))
	{
		map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (obj);

		ASSERT (map_dimensions);

		d = map_dimensions->size * 0.01;
	
		map_dimensions->z += d;

		bound_map_extents (obj, NULL, NULL);
	}
}

void fine_current_map_down_event (event *ev)
{
	ui_object
		*obj;

	map_dimension_type
		*map_dimensions;

	float
		d;

	obj = last_drawn_map_object;

	if ((obj) && (get_in_flight_game_mode () == IN_FLIGHT_GAME_MODE_PLANNER))
	{
		map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (obj);

		ASSERT (map_dimensions);

		d = map_dimensions->size * 0.01;
	
		map_dimensions->z -= d;

		bound_map_extents (obj, NULL, NULL);
	}
}

void fine_current_map_left_event (event *ev)
{
	ui_object
		*obj;

	map_dimension_type
		*map_dimensions;

	float
		d;

	obj = last_drawn_map_object;

	if ((obj) && (get_in_flight_game_mode () == IN_FLIGHT_GAME_MODE_PLANNER))
	{
		map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (obj);

		ASSERT (map_dimensions);

		d = map_dimensions->size * 0.01;
	
		map_dimensions->x -= d;

		bound_map_extents (obj, NULL, NULL);
	}
}

void fine_current_map_right_event (event *ev)
{
	ui_object
		*obj;

	map_dimension_type
		*map_dimensions;

	float
		d;

	obj = last_drawn_map_object;

	if ((obj) && (get_in_flight_game_mode () == IN_FLIGHT_GAME_MODE_PLANNER))
	{
		map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (obj);

		ASSERT (map_dimensions);

		d = map_dimensions->size * 0.01;
	
		map_dimensions->x += d;

		bound_map_extents (obj, NULL, NULL);
	}
}
// Jabberwock 031020 ends

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void zoom_in_current_map_event (event *ev)
{
	ui_object
		*obj;

	obj = last_drawn_map_object;

	if (obj)
	{
		map_zoom_in_function (obj, NULL);
	}
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void zoom_out_current_map_event (event *ev)
{
	ui_object
		*obj;

	obj = last_drawn_map_object;

	if (obj)
	{
		map_zoom_out_function (obj, NULL);
	}
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void centre_current_map_on_player (event *ev)
{
	ui_object
		*obj;

	entity
		*en;

	vec3d
		*pos;

	map_dimension_type
		*map_dimensions;

	obj = last_drawn_map_object;

	if (obj)
	{
		map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (obj);

		ASSERT (map_dimensions);

		en = get_gunship_entity ();

		if (en)
		{
			pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);	

			map_dimensions->x = pos->x;
			map_dimensions->z = pos->z;

			bound_map_extents (obj, NULL, NULL);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void define_map_objects (ui_object *parent, map_dimension_type *data, void *draw_function, void *left_mouse_function, void *right_mouse_function, ui_object **full_screen_parent)
{
	float
		x1,
		y1,
		x2,
		y2,
		y_inc;

	ui_object
		*map_area,
		*map_window,
		*map_controls_area;

	ASSERT (parent);

	ASSERT (data);

	memset (data, 0, sizeof (map_dimension_type));

	set_ui_object_user_ptr (parent, data);

	set_ui_object_clear (parent, TRUE);

	data->parent = parent;

	/////////////////////////////////////////////////////////////////

	x1 = 0.0;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 1.0;

	map_area = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (parent),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_USER_PTR ((void *)data),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);
	
	data->map_area = map_area;

	/////////////////////////////////////////////////////////////////
	// Map Window
	{
			
		x1 = 0.0;
		y1 = 0.0;
		x2 = 0.915;
		y2 = 1.0;

		map_window = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (map_area),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_DRAW_FUNCTION (draw_function),
				UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_DOWN),
				UI_ATTR_USER_PTR ((void *)data),
				UI_ATTR_FUNCTION (left_mouse_function),
				UI_ATTR_RIGHT_FUNCTION (right_mouse_function),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);
	}

	data->full_screen_parent = full_screen_parent;

	/////////////////////////////////////////////////////////////////
	// Map controls
	/////////////////////////////////////////////////////////////////
	{

		x1 = 0.915;
		x2 = 1.0;
		y1 = 0.0;
		y2 = 1.0;

		map_controls_area = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (map_area),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_TEXTURE_GRAPHIC (map_key_backdrop_graphic),
				UI_ATTR_END
			);

		x1 = 0.0;
		x2 = 1.0;

		y1 = 0.0;
		y_inc = 1.0 / 14.0;

		if (full_screen_parent)
		{
			/////////////////////////////////////////////////////////////////
			// Min/Max

			y1 = 0.0;
			y2 = y1 + y_inc;
			
			create_ui_object
			(
				UI_TYPE_BUTTON,
				UI_ATTR_PARENT (map_controls_area),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_DRAW_FUNCTION (draw_full_screen_toggle_function),
				UI_ATTR_FUNCTION (toggle_full_screen_function),
				UI_ATTR_USER_PTR ((void *)data),
				UI_ATTR_HIGHLIGHTABLE (TRUE),
				UI_ATTR_END
			);
		}
		else
		{
			/////////////////////////////////////////////////////////////////
			// Goto 

			y1 = 0.0;
			y2 = y1 + y_inc;
			
			create_ui_object
			(
				UI_TYPE_TOGGLE,
				UI_ATTR_PARENT (map_controls_area),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_DRAW_FUNCTION (draw_goto_toggle_function),
				UI_ATTR_FUNCTION (toggle_map_goto_function),
				UI_ATTR_USER_PTR ((void *)data),
				UI_ATTR_HIGHLIGHTABLE (TRUE),
				UI_ATTR_TEXTURE_GRAPHIC (goto_icons [0]),
				UI_ATTR_HIGHLIGHTED_TEXTURE_GRAPHIC (goto_icons [1]),
				UI_ATTR_SELECTED_TEXTURE_GRAPHIC (goto_icons [2]),
				UI_ATTR_END
			);
		}

		/////////////////////////////////////////////////////////////////
		// zoom

		y1 += y_inc;
		y2 = y1 + y_inc;
		
		create_ui_object
			(
				UI_TYPE_BUTTON,
				UI_ATTR_PARENT (map_controls_area),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_USER_PTR ((void *)data),
				UI_ATTR_FUNCTION (map_zoom_in_function),
				UI_ATTR_HIGHLIGHTABLE (TRUE),
				UI_ATTR_TEXTURE_GRAPHIC (zoom_in_icons [0]),
				UI_ATTR_HIGHLIGHTED_TEXTURE_GRAPHIC (zoom_in_icons [1]),
				UI_ATTR_SELECTED_TEXTURE_GRAPHIC (zoom_in_icons [2]),
				UI_ATTR_END
			);
		
		y1 += y_inc;
		y2 = y1 + y_inc;
		
		create_ui_object
			(
				UI_TYPE_BUTTON,
				UI_ATTR_PARENT (map_controls_area),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_USER_PTR ((void *)data),
				UI_ATTR_FUNCTION (map_zoom_out_function),
				UI_ATTR_HIGHLIGHTABLE (TRUE),
				UI_ATTR_TEXTURE_GRAPHIC (zoom_out_icons [0]),
				UI_ATTR_HIGHLIGHTED_TEXTURE_GRAPHIC (zoom_out_icons [1]),
				UI_ATTR_SELECTED_TEXTURE_GRAPHIC (zoom_out_icons [2]),
				UI_ATTR_END
			);

		/////////////////////////////////////////////////////////////////
		// layer controls
		{
			int
				loop;
	
			for (loop = 0; loop < NUM_MAP_LAYER_CONTROLS; loop ++)
			{
				y1 += y_inc;
				y2 = y1 + y_inc;
		
				data->layer_control_objects [loop] = create_ui_object
				(
					UI_TYPE_TOGGLE,
					UI_ATTR_PARENT (map_controls_area),
					UI_ATTR_VIRTUAL_POSITION (x1, y1),
					UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
					UI_ATTR_ITEM_NUMBER (loop),
					UI_ATTR_FUNCTION (layer_control_button_data [loop].function),
					UI_ATTR_USER_PTR ((void *)data),
					UI_ATTR_HIGHLIGHTABLE (TRUE),
					UI_ATTR_TEXTURE_GRAPHIC (key_icons [loop][0]),
					UI_ATTR_HIGHLIGHTED_TEXTURE_GRAPHIC (key_icons [loop][1]),
					UI_ATTR_SELECTED_TEXTURE_GRAPHIC (key_icons [loop][2]),
					UI_ATTR_END
				);
			}
		}
	}

	//
	// register map data
	//

	data->next = map_data_list;

	map_data_list = data;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Jabberwock 031009 Satellite view

void switch_to_satellite_event (event *ev)
{
	map_dimension_type
		*map_dimensions;
			
	entity
		*key,
		*en,
		*objective;

	ui_object
			*obj;
				
	obj = last_drawn_map_object;

	if (obj)	
	{
		map_dimensions = (map_dimension_type *)get_ui_object_user_ptr (obj);

		map_dimensions->selected_entity = NULL;
	
		en = get_map_mouse_over_entity (map_dimensions);
		
		key = NULL;
		
		if (en)
		{
			switch (get_local_entity_type (en))	
			{
				case ENTITY_TYPE_KEYSITE:
				case ENTITY_TYPE_WAYPOINT:
				{
					key = en;
					
					break;
				}
				case ENTITY_TYPE_TASK:
				{
					objective = get_local_entity_parent (en, LIST_TYPE_TASK_DEPENDENT);
				
					if (get_local_entity_type (objective) == ENTITY_TYPE_KEYSITE)
					{
						key = objective;
					}
					
					break;
				}
			}
		}
		if (key)
		{
			ASSERT (get_local_entity_int_value (key, INT_TYPE_VIEWABLE));
				
			notify_local_entity (ENTITY_MESSAGE_SET_CAMERA_ACTION, get_camera_entity (), NULL, CAMERA_ACTION_SATELLITE);
			
			set_external_view_entity (key);
			
			toggle_in_flight_game_modes (NULL);
		}
	}
}
// Jabberwock 031009 ends

