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

enum FILE_TAGS
{

	FILE_TAG_AIRBASE_SITE,
	FILE_TAG_AIR_NODE_ROUTE_DATA,
	FILE_TAG_AMMO_DUMP_SITE,
	FILE_TAG_AMMO_SUPPLIES,
	FILE_TAG_ANCHORAGE_SITE,
	FILE_TAG_ASSIGN_GROUP_TASK,
	FILE_TAG_ATTITUDE,
	FILE_TAG_AUTO_ASSIGN_GUNSHIP,
	FILE_TAG_BUILDING,
	FILE_TAG_BRIDGE,
	FILE_TAG_BRIEFING_ALLIED_CAUSE_TEXT,
	FILE_TAG_BRIEFING_ENEMY_CAUSE_TEXT,
	FILE_TAG_BRIEFING_EFFECT_TEXT,
	FILE_TAG_CAMPAIGN_DATA,
	FILE_TAG_CAMPAIGN_REQUIRES_APACHE_HAVOC,
	FILE_TAG_CAMPAIGN_TRIGGER,
	FILE_TAG_CAMPAIGN_TRIGGER_RESULT,
	FILE_TAG_COLOUR,
	FILE_TAG_COUNT,
	FILE_TAG_CREATE_GROUP,
	FILE_TAG_CREATE_MEMBERS,
	FILE_TAG_CREATE_MOBILE,
	FILE_TAG_CREATE_TASK,
	FILE_TAG_CREATE_WAYPOINT,
	FILE_TAG_CURRENT_PLAYER,
	FILE_TAG_DAYS,
	FILE_TAG_DEBRIEFING_TEXT,
	FILE_TAG_DELTA_TIME,
	FILE_TAG_DESTROY_ENTITY,
	FILE_TAG_DIVISION_ID_LIST,
	FILE_TAG_DURATION,
	FILE_TAG_END_CAMPAIGN,
	FILE_TAG_EXPERIENCE_POINTS,
	FILE_TAG_FACTION,
	FILE_TAG_FACTORY_SITE,
	FILE_TAG_FAILURE,
	FILE_TAG_FARP_SITE,
	FILE_TAG_FLAG_PYLONS,
	FILE_TAG_FLIGHT_DYNAMICS,
	FILE_TAG_FORCE_NAME,
	FILE_TAG_FORMATION,
	FILE_TAG_FORMATION_COMPONENT,
	FILE_TAG_FRONTLINE_FORCES,
	FILE_TAG_FUEL_SUPPLIES,
	FILE_TAG_GET_ALTITUDE,
	FILE_TAG_GET_ENTITY_GROUP,
	FILE_TAG_GET_ENTITY_PLAYER,
	FILE_TAG_GET_ENTITY_SIDE,
	FILE_TAG_GET_ENTITY_TARGET,
	FILE_TAG_GET_ENTITY_TASK,
	FILE_TAG_GET_ENTITY_TYPE,
	FILE_TAG_GET_ENTITY_X_POSITION,
	FILE_TAG_GET_ENTITY_Y_POSITION,
	FILE_TAG_GET_ENTITY_Z_POSITION,
	FILE_TAG_GET_INFINITE_AMMO,
	FILE_TAG_GET_INFINITE_FUEL,
	FILE_TAG_GET_INFINITE_WEAPONS,
	FILE_TAG_GET_INVULNERABLE,
	FILE_TAG_GET_NEAREST_SIDE_AIRCRAFT,
	FILE_TAG_GET_NEAREST_SIDE_KEYSITE,
	FILE_TAG_GET_NEAREST_SIDE_VEHICLE,
	FILE_TAG_GET_POSITION_TERRAIN_TYPE,
	FILE_TAG_GET_RANGE,
	FILE_TAG_GET_SIDE_BALANCE_OF_POWER,
	FILE_TAG_GET_SIDE_SECTOR_COUNT,
	FILE_TAG_GET_TIME,
	FILE_TAG_GET_TRIGGER_ENTITY,
	FILE_TAG_GET_USER_ENTITY,
	FILE_TAG_GET_VELOCITY,
	FILE_TAG_GET_WEATHER,
	FILE_TAG_GOAL,
	FILE_TAG_GROUP,
	FILE_TAG_HARDWARE_RESERVES,
	FILE_TAG_HEADING,
	FILE_TAG_HOURS,
	FILE_TAG_KEYSITE,
	FILE_TAG_KEYSITE_END,
	FILE_TAG_LANGUAGE_ENGLISH,
	FILE_TAG_LANGUAGE_FRENCH,
	FILE_TAG_LANGUAGE_GERMAN,
	FILE_TAG_LANGUAGE_ITALIAN,
	FILE_TAG_LANGUAGE_POLISH,
	FILE_TAG_LANGUAGE_SPANISH,
	FILE_TAG_LANGUAGE_TEXT_END,
	FILE_TAG_LANGUAGE_TEXT_START,
	FILE_TAG_LANGUAGE_TEXT_STOP,
	FILE_TAG_LENGTH,
	FILE_TAG_LIST,
	FILE_TAG_LONG_TEXT_START,
	FILE_TAG_MAP_SECTOR_SIZE,
	FILE_TAG_MAP_X_MAX,
	FILE_TAG_MAP_X_MIN,
	FILE_TAG_MAP_X_SIZE,
	FILE_TAG_MAP_Z_MAX,
	FILE_TAG_MAP_Z_MIN,
	FILE_TAG_MAP_Z_SIZE,
	FILE_TAG_MAX_PLAYERS,
	FILE_TAG_MEDAL,
	FILE_TAG_MEMBER,
	FILE_TAG_MILITARY_SITE,
	FILE_TAG_MINUTES,
	FILE_TAG_MOBILE_KEYSITE,
	FILE_TAG_MOVEMENT,
	FILE_TAG_NAME,
	FILE_TAG_OBJECTIVES,
	FILE_TAG_OBJECT_NUMBER,
	FILE_TAG_OBJECT_SCALING,
	FILE_TAG_OIL_RIG_SITE,
	FILE_TAG_OPTION_INFINITE_FUEL,
	FILE_TAG_OPTION_INFINITE_WEAPONS,
	FILE_TAG_OPTION_INVULNERABLE,
	FILE_TAG_OPTION_SUPPRESS_AI_FIRE,
	FILE_TAG_PARTIAL,
	FILE_TAG_PILOT,
	FILE_TAG_PILOT_EXPERIENCE,
	FILE_TAG_PILOT_LEVEL,
	FILE_TAG_PILOT_RANK,
	FILE_TAG_PLANNER_DATA,
	FILE_TAG_PLAY_SOUND_EFFECT,
	FILE_TAG_PLAYER,
	FILE_TAG_POPULATION_DATA,
	FILE_TAG_POPULATION_TYPE,
	FILE_TAG_POSITION,
	FILE_TAG_POWER_STATION_SITE,
	FILE_TAG_PROMOTION,
	FILE_TAG_RADIUS,
	FILE_TAG_RANK,
	FILE_TAG_RANK_POINTS,
	FILE_TAG_REGEN,
	FILE_TAG_REGEN_FREQUENCY,
	FILE_TAG_RESULT,
	FILE_TAG_ROAD_NODE_ROUTE_DATA,
	FILE_TAG_ROUTE,
	FILE_TAG_SAM_AAA_SITE,
	FILE_TAG_SAVED_CAMPAIGN,
	FILE_TAG_SCENIC_OBJECT,
	FILE_TAG_SEA_NODE_ROUTE_DATA,
	FILE_TAG_SECONDS,
	FILE_TAG_SET_DATE,
	FILE_TAG_SET_ENTITY_POSITION,
	FILE_TAG_SET_EVENT_TRIGGERED,
	FILE_TAG_SET_INFINITE_AMMO,
	FILE_TAG_SET_INFINITE_FUEL,
	FILE_TAG_SET_INFINITE_WEAPONS,
	FILE_TAG_SET_INVULNERABLE,
	FILE_TAG_SET_TIME,
	FILE_TAG_SET_WEATHER,
	FILE_TAG_SHORT_TEXT_START,
	FILE_TAG_SIDE,
	FILE_TAG_SIZE,
	FILE_TAG_START_BASE,
	FILE_TAG_SUCCESS,
	FILE_TAG_SUPPRESS_POPULATION_KEYSITES,
	FILE_TAG_TASK_GENERATION,
	FILE_TAG_TERRAIN_OBJECT,
	FILE_TAG_TEXT1,
	FILE_TAG_TEXT2,
	FILE_TAG_TEXT3,
	FILE_TAG_TEXT4,
	FILE_TAG_TEXT_END,
	FILE_TAG_TITLE,
	FILE_TAG_TOUR_OF_DUTY,
	FILE_TAG_TRAFFIC_ROUTE,
	FILE_TAG_TRANSLATION,
	FILE_TAG_TRANSLATION_PARAGRAPH,
	FILE_TAG_VELOCITY,
	FILE_TAG_VERSION_NUMBER,
	FILE_TAG_WARZONE_NAME,
	FILE_TAG_WARZONE_SIZE,
	FILE_TAG_WEATHER_RAIN,
	FILE_TAG_WEATHER_WIND,
	FILE_TAG_X_SECTOR,
	FILE_TAG_Z_SECTOR,
	FILE_TAG_ZOOM,
	FILE_TAG_APPLICATION_LAST_TAG
};

typedef enum FILE_TAGS file_tags;

extern const char
   *application_tag_strings [];

/*
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum FILE_TAG_OPERATORS
{

	FILE_TAG_EQUALS,
	FILE_TAG_LESS_THAN,
	FILE_TAG_GREATER_THAN,
	NUM_FILE_TAGS
};

typedef enum FILE_TAG_OPERATORS file_tag_operators;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct FILE_TAG_VARIABLE_TYPE
{

	char
		*name;

	int
		id,
		*variable;

	struct FILE_TAG_VARIABLE_TYPE
		*next;
};

typedef struct FILE_TAG_VARIABLE_TYPE file_tag_variable_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern const char *tag_strings [];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void initialise_file_tag_system (void);

extern void deinitialise_file_tag_system (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SET FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void set_file_tag (FILE *file_ptr, file_tags tag);

extern void set_file_int (FILE *file_ptr, int value);

extern void set_file_float (FILE *file_ptr, float value);

extern void set_file_string (FILE *file_ptr, const char *string);

extern void set_file_enum (FILE *file_ptr, const char *enum_strings [], int enum_value);

extern void set_file_new_line (FILE *file_ptr, int count);

extern void set_file_comment (FILE *file_ptr, const char *string);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GET FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern file_tags get_file_tag (char *line);

extern file_tags get_next_file_tag (FILE *file_ptr);

extern file_tags check_next_file_tag (FILE *file_ptr);

extern int get_next_file_int (FILE *file_ptr);

extern float get_next_file_float (FILE *file_ptr);

extern int get_next_file_string (FILE *file_ptr, char *buffer, int size);

extern int get_next_file_word (FILE *file_ptr, char *buffer, int size);

extern int get_next_file_enum (FILE *file_ptr, const char *enum_strings [], int last_enum);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void register_file_tag_variable (const char *variable_name, int *variable);

extern void unregister_file_tag_variable (const char *variable_name);

extern int *get_file_tag_variable (const char *variable_name);

extern int if_file_tag_variable (const char *variable_name, const char *operator, int value);

extern int if_file_tag_operator (int value1, const char *operator, int value2);

extern int set_file_tag_variable (const char *variable_name, int value);

extern int get_variable_id (const char *name);

extern int get_operator_id (const char *name);

extern const char *get_variable_name (int id);

extern char get_operator_name (int id);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
