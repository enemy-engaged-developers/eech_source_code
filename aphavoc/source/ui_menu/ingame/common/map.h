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

enum MAP_LAYER_CONTROL_TYPES
{
	MAP_LAYER_CONTROL_SECTOR_SIDES,
	MAP_LAYER_CONTROL_FOG_OF_WAR,
	MAP_LAYER_CONTROL_GRID,
	MAP_LAYER_CONTROL_KEYSITES,
	MAP_LAYER_CONTROL_MISSIONS,
	MAP_LAYER_CONTROL_AIRCRAFT,
	MAP_LAYER_CONTROL_ARMOUR,
	MAP_LAYER_CONTROL_SHIPS,
	MAP_LAYER_CONTROL_SAM_AAA,
	MAP_LAYER_CONTROL_THREAT_CIRCLES,
	MAP_LAYER_CONTROL_TRACK_PLAYER,

	NUM_MAP_LAYER_CONTROLS
};

typedef enum MAP_LAYER_CONTROL_TYPES map_layer_control_types;

#define MAP_LAYER_CONTROL_NONE -1

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum MAP_EVENT_TYPES
{
	MAP_EVENT_LOG_EVENT,
	MAP_EVENT_EXPLOSION,

	NUM_MAP_EVENT_TYPES
};

typedef enum MAP_EVENT_TYPES map_event_types;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum MAP_ICON_TYPE
{
	MAP_ICON_NONE,

	MAP_ICON_AAA,
	MAP_ICON_AIRBASE,
	MAP_ICON_APC,
	MAP_ICON_ARTILLERY,
	MAP_ICON_BUILDING,
	MAP_ICON_CAMPAIGN_OBJECTIVE,
	MAP_ICON_CARRIER,
	MAP_ICON_EVENT,
	MAP_ICON_EXPLOSION,
	MAP_ICON_FARP,
	MAP_ICON_HELICOPTER,
	MAP_ICON_HIGHLIGHT,
	MAP_ICON_JET,
	MAP_ICON_MISSION,
	MAP_ICON_OIL_REFINERY,
	MAP_ICON_PLAYER,
	MAP_ICON_PLAYER_OVERLAY,
	MAP_ICON_POWER_STATION,
	MAP_ICON_RADIO_TRANSMITTER,
	MAP_ICON_SELECTED,
	MAP_ICON_SHIP,
	MAP_ICON_TANK,
	MAP_ICON_TRANSPORT_AIRCRAFT,
	MAP_ICON_TRANSPORT_HELICOPTER,
	MAP_ICON_TRUCK,
	MAP_ICON_WAYPOINT_INSERT,
	MAP_ICON_WAYPOINT_INSERT_HIGHLIGHTED,
	MAP_ICON_WAYPOINT_INSERT_SELECTED,
	MAP_ICON_WAYPOINT_NAV,
	MAP_ICON_WAYPOINT_NAV_HIGHLIGHTED,
	MAP_ICON_WAYPOINT_NAV_SELECTED,
	MAP_ICON_WAYPOINT_TARGET,
	MAP_ICON_WAYPOINT_TARGET_HIGHLIGHTED,
	MAP_ICON_WAYPOINT_TARGET_SELECTED,
	MAP_ICON_WAYPOINT_TARGET_TEMPORARY,

	NUM_MAP_ICON_TYPES
};

typedef enum MAP_ICON_TYPE map_icon_type;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum MOUSE_OVER_OBJECT_TYPES
{
	MOUSE_OVER_OBJECT_NONE,
	MOUSE_OVER_OBJECT_ENTITY,
	MOUSE_OVER_OBJECT_WAYPOINT_ADD,
	
	NUM_MOUSE_OVER_OBJECT_TYPES
};

typedef enum MOUSE_OVER_OBJECT_TYPES mouse_over_object_types;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct MAP_MOUSE_OVER_OBJECT_TYPE
{
	mouse_over_object_types
		type;

	float
		distance;

	entity
		*en;

	vec3d
		pos;
};

typedef struct MAP_MOUSE_OVER_OBJECT_TYPE map_mouse_over_object_type;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct MAP_DIMENSION_TYPE
{
	float
		x,
		z,
		size;

	ui_object
		*parent,
		*map_area,
		**full_screen_parent,
		*layer_control_objects [NUM_MAP_LAYER_CONTROLS];

	entity
		*subject_entity,
		*selected_entity;

	map_mouse_over_object_type
		mouse_over_object;

	unsigned int
		full_screen			: 1,
		enable_goto			: 1;

	struct MAP_DIMENSION_TYPE
		*next;
};

typedef struct MAP_DIMENSION_TYPE map_dimension_type;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void draw_2d_map (ui_object *obj, void *arg);

extern void load_map_textures (void);

extern void initialise_map_data (void);

extern void set_active_map_object (ui_object *obj);

extern void set_last_drawn_map_object (ui_object *obj);

extern void clear_map_mouse_over_object (map_dimension_type *data);

extern entity *get_map_mouse_over_entity (map_dimension_type *data);

extern void define_map_objects (ui_object *parent, map_dimension_type *data, void *draw_function, void *left_mouse_function, void *right_mouse_function, ui_object **full_screen_parent);

extern void draw_waypoint_route_layer (ui_object *obj, entity_sides side);

extern void map_goto_function (ui_object *obj);

extern void map_centralise_function (ui_object *obj, void *arg);

extern void map_zoom_in_function (ui_object *obj, void *arg);

extern void map_zoom_out_function (ui_object *obj, void *arg);

extern void map_add_waypoint (entity *wp1, vec3d *pos);

extern int map_insert_waypoint_function (ui_object *obj);

extern void minimize_full_screen_map_object (ui_object *obj, void *arg);

extern void minimize_all_map_objects (void);

extern void add_map_event (int type, float x, float z, float lifetime);

extern void map_move_waypoint_events (void);

extern void update_map_events (void);

extern void update_map_overlays (void);

extern void update_map_animations (void);

extern void force_map_layer_control_object (map_layer_control_types index, int state);

extern void toggle_current_map_maximise_event (event *ev);

extern void shift_current_map_up_event (event *ev);
extern void shift_current_map_down_event (event *ev);
extern void shift_current_map_left_event (event *ev);
extern void shift_current_map_right_event (event *ev);

extern void zoom_in_current_map_event (event *ev);
extern void zoom_out_current_map_event (event *ev);

extern void centre_current_map_on_player (event *ev);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

