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

enum GAME_STATUS_TYPES
{

	GAME_STATUS_UNINITIALISED,
	GAME_STATUS_UNINITIALISING,
	GAME_STATUS_INITIALISING,
	GAME_STATUS_INITIALISED,
	NUM_GAME_STATUS_TYPES
};

typedef enum GAME_STATUS_TYPES game_status_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern game_status_types
	game_status;

extern char
	*game_status_string;

extern void set_game_status (game_status_types status);

#define get_game_status() (game_status)

#define NUM_GLOBAL_OPTIONS_SOUND_CHANNEL_TYPES 7

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum GAME_TYPES
{
	GAME_TYPE_INVALID,
	GAME_TYPE_FREE_FLIGHT,
	GAME_TYPE_CAMPAIGN,
	GAME_TYPE_SKIRMISH,
	GAME_TYPE_DEMO,
	NUM_GAME_TYPES
};

typedef enum GAME_TYPES game_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum GUNSHIP_TYPES
{
	GUNSHIP_TYPE_APACHE,
	GUNSHIP_TYPE_HAVOC,
	GUNSHIP_TYPE_COMANCHE,
	GUNSHIP_TYPE_HOKUM,
	NUM_GUNSHIP_TYPES
};

typedef enum GUNSHIP_TYPES gunship_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern char
	*game_status_names [],
	*gunship_type_names [];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern int
	gunship_sub_types [],
	gunship_sides [];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum HUD_COLOURS
{
	HUD_COL_WHITE,
	HUD_COL_RED,
	HUD_COL_AMBER,
	HUD_COL_GOLD,
	HUD_COL_GREEN,
	HUD_COL_CYAN,
	HUD_COL_BLUE,
	HUD_COL_BLACK,
	NUM_HUD_COLOURS
};

typedef enum HUD_COLOURS hud_colours;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum CPG_ASSIST_TYPES
{
	CPG_ASSIST_TYPE_NONE,
	CPG_ASSIST_TYPE_EASY,
	CPG_ASSIST_TYPE_REAL,
	NUM_CPG_ASSISTANCE_TYPES
};

typedef enum CPG_ASSIST_TYPES cpg_assist_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum INPUT_DEVICE_TYPES
{

	NO_INPUT,
	KEYBOARD_INPUT,
	JOYSTICK_INPUT,
	MOUSE_INPUT,
	RUDDER_INPUT,
	THROTTLE_INPUT,
	NUM_INPUT_DEVICE_TYPES
};

typedef enum INPUT_DEVICE_TYPES input_device_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum DYNAMICS_MODEL_TYPES
{

	DYNAMICS_MODEL_NONE,
	DYNAMICS_MODEL_VECTOR,
	DYNAMICS_MODEL_BASIC,
	DYNAMICS_MODEL_NORMAL,
	DYNAMICS_MODEL_ADVANCED,
	NUM_DYNAMICS_MODEL_TYPES
};

typedef enum DYNAMICS_MODEL_TYPES dynamics_model_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum MAP_TYPES
{

	INVALID_MAP,
	MAP1,
	MAP2,
	MAP3,
	MAP4,
	NUM_MAP_TYPES
};

typedef enum MAP_TYPES map_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum SESSION_TIME_OF_DAY_SETTINGS
{

	SESSION_TIME_INVALID,
	SESSION_TIME_RANDOM,
	SESSION_TIME_DAWN,
	SESSION_TIME_MIDDAY,
	SESSION_TIME_AFTERNOON,
	SESSION_TIME_DUSK,
	SESSION_TIME_MIDNIGHT,
};

typedef enum SESSION_TIME_OF_DAY_SETTINGS session_time_of_day_settings;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum SESSION_WEATHER_SETTINGS
{

	SESSION_WEATHER_INVALID,
	SESSION_WEATHER_RANDOM,
	SESSION_WEATHER_GOOD,
	SESSION_WEATHER_FAIR,
	SESSION_WEATHER_POOR,
};

typedef enum SESSION_WEATHER_SETTINGS session_weather_settings;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum GAME_DIFFICULTY_SETTINGS
{

	GAME_DIFFICULTY_INVALID,
	GAME_DIFFICULTY_HARD,
	GAME_DIFFICULTY_MEDIUM,
	GAME_DIFFICULTY_EASY,
};

typedef enum GAME_DIFFICULTY_SETTINGS game_difficulty_settings;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum GAME_MUSIC_TYPES
{

	GAME_MUSIC_INVALID,

	GAME_MUSIC_OFF,
	GAME_MUSIC_ON,

	GAME_MUSIC_LAST,
};

typedef enum GAME_MUSIC_TYPES game_music_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct GAME_TEXT_LANGUAGE_TYPE
{

	int
		language;

	char
		*text;

	int
		xpos,
		ypos,
		xsize,
		ysize;
};

typedef struct GAME_TEXT_LANGUAGE_TYPE game_text_language_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
struct GAME_TEXT_TRANSLATION_TYPE
{
	int
		button_id;

	game_text_language_type
		language [NUM_LANGUAGES];
};

typedef struct GAME_TEXT_TRANSLATION_TYPE game_text_translation_type;
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum COCKPIT_DETAIL_LEVELS
{
	COCKPIT_DETAIL_LEVEL_LOW,
	COCKPIT_DETAIL_LEVEL_MEDIUM,
	COCKPIT_DETAIL_LEVEL_HIGH,
	NUM_COCKPIT_DETAIL_LEVELS
};

typedef enum COCKPIT_DETAIL_LEVELS cockpit_detail_levels;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct GLOBAL_OPTIONS_DATA
{
	////////////////////////////////////////
	//
	// ALWAYS KEEP THIS FIRST
	//

	int
		version_number;

	//
	////////////////////////////////////////

	////////////////////////////////////////
	//
	// VERSION 1.0
	//
	////////////////////////////////////////

	int
		current_language;

	int
		gunship_side;

	gunship_types
		gunship_type;

	hud_colours
		hud_colour;

	int
		map,
		hud_enlarge,
		blurred_main_rotors_visible_from_cockpit,
		display_external_view_name,
		graphics_files_installed;

	input_device_types
		cyclic_input,
		collective_input,
		pedal_input;

	int
		joystick_device_index;

	dynamics_model_types
		dynamics_model;

	GUID
		service_provider_guid;

	game_music_types
		sound_music_status;

	unsigned int
		sound_effects_enabled							:1,
		sound_speech_enabled								:1,
		graphics_rain_textures_enabled				:1;

	unsigned int
		dynamics_options_wind							:1,
		dynamics_options_transitional_lift			:1,
		dynamics_options_vortex_ring					:1,
		dynamics_options_retreating_blade_stall	:1,
		dynamics_options_reverse_throttle_input	:1,
		dynamics_options_keyboard_assistance		:1,
		dynamics_options_cross_coupling				:1,
		dynamics_options_ground_effect				:1,
		dynamics_options_object_collisions			:1,
		dynamics_options_ground_collisions			:1,
		dynamics_options_damage							:1,
		dynamics_options_over_torque					:1,
		dynamics_options_draw_flight_path			:1;

	unsigned int
		graphics_device_selection_automatic			:1,
		graphics_device_selection_primary			:1;

	GUID
		graphics_device_guid;

	int
		graphics_files_wrong_format;

	unsigned int
		graphics_files_red_mask,
		graphics_files_green_mask,
		graphics_files_blue_mask,
		graphics_files_alpha_mask;

	int
		comms_port,
		baud_rate,
		stop_bits,
		parity,
		flow;

	cpg_assist_types
		cpg_assist_type;

	int
		auto_counter_measures;

	char
		ip_address[128];

	char
		phone_number[128];

	int
		graphics_object_detail_level,
		graphics_terrain_detail_level;

	////////////////////////////////////////
	//
	// VERSION 1.1
	//
	////////////////////////////////////////

	enum SESSION_TIME_OF_DAY_SETTINGS
		session_free_flight_time_of_day,
		session_campaign_time_of_day;

	enum SESSION_WEATHER_SETTINGS
		session_free_flight_weather,
		session_campaign_weather;

	enum GAME_DIFFICULTY_SETTINGS
		difficulty_level;

	unsigned int
		session_free_flight_realism_infinite_weapons					:1,
		session_free_flight_realism_infinite_fuel						:1,
		session_free_flight_realism_invulnerable_from_weapons		:1,
		session_free_flight_realism_invulnerable_from_collisions	:1,
		session_free_flight_realism_suppress_ai_fire					:1,

		session_campaign_realism_infinite_weapons						:1,
		session_campaign_realism_infinite_fuel							:1,
		session_campaign_realism_invulnerable_from_weapons			:1,
		session_campaign_realism_invulnerable_from_collisions		:1,
		session_campaign_realism_suppress_ai_fire						:1;

	int
		display_hud_on_external_view,
		draw_cockpit_graphics,
		draw_overlaid_instruments;

	int
		sound_speech_copilot_enabled;

	float
		visual_screen_width,
		visual_screen_height;

	GUID
		graphics_card_device_identifier;

	int
		number_of_graphics_card_resolutions;

	graphics_resolution_mode
		graphics_card_resolutions[32];

	////////////////////////////////////////
	//
	// COMANCHE HOKUM
	//
	////////////////////////////////////////

	int
		apache_havoc_installed,
		ase_auto_page,
		glass_cockpit,
		simple_avionics,
		display_in_flight_intelligence_messages,
		unscaled_displays;

	cockpit_detail_levels
		cockpit_detail_level;

	int
		map_layer_options;

	int
		sound_channel_volume [NUM_GLOBAL_OPTIONS_SOUND_CHANNEL_TYPES],
		sound_channel_muted [NUM_GLOBAL_OPTIONS_SOUND_CHANNEL_TYPES];

	char
		spare[1000];
};

typedef struct GLOBAL_OPTIONS_DATA global_options_data;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern global_options_data
	global_options;

////////////////////////////////////////
//
// use set/get functions to access global_options
//
////////////////////////////////////////

#define get_global_version_number() (global_options.version_number)

#define set_global_version_number(VERSION_NUMBER) (global_options.version_number = (VERSION_NUMBER))

////////////////////////////////////////

#define get_global_gunship_side() (global_options.gunship_side)

#define set_global_gunship_side(SIDE) (global_options.gunship_side = (SIDE))

////////////////////////////////////////

#define get_global_gunship_type() (global_options.gunship_type)

////////////////////////////////////////

#define get_global_hud_colour() (global_options.hud_colour)

////////////////////////////////////////

#define set_global_hud_enlarge(FLAG) (global_options.hud_enlarge = (FLAG))

#define get_global_hud_enlarge() (global_options.hud_enlarge)

////////////////////////////////////////

#define set_global_display_hud_on_external_view(FLAG) (global_options.display_hud_on_external_view = (FLAG))

#define get_global_display_hud_on_external_view() (global_options.display_hud_on_external_view)

////////////////////////////////////////

#define set_global_draw_cockpit_graphics(FLAG) (global_options.draw_cockpit_graphics = (FLAG))

#define get_global_draw_cockpit_graphics() (global_options.draw_cockpit_graphics)

////////////////////////////////////////

#define set_global_draw_overlaid_instruments(FLAG) (global_options.draw_overlaid_instruments = (FLAG))

#define get_global_draw_overlaid_instruments() (global_options.draw_overlaid_instruments)

////////////////////////////////////////

#define set_global_3d_visual_screen_width(WIDTH) (global_options.visual_screen_width = (WIDTH))

#define get_global_3d_visual_screen_width() (global_options.visual_screen_width)

////////////////////////////////////////

#define set_global_3d_visual_screen_height(HEIGHT) (global_options.visual_screen_height = (HEIGHT))

#define get_global_3d_visual_screen_height() (global_options.visual_screen_height)

////////////////////////////////////////

#define set_global_blurred_main_rotors_visible_from_cockpit(FLAG) (global_options.blurred_main_rotors_visible_from_cockpit = (FLAG))

#define get_global_blurred_main_rotors_visible_from_cockpit() (global_options.blurred_main_rotors_visible_from_cockpit)

////////////////////////////////////////

#define set_global_display_external_view_name(FLAG) (global_options.display_external_view_name = (FLAG))

#define get_global_display_external_view_name() (global_options.display_external_view_name)

////////////////////////////////////////

#define get_global_graphics_files_installed() (global_options.graphics_files_installed)

#define set_global_graphics_files_installed(FLAG) (global_options.graphics_files_installed = (FLAG))

////////////////////////////////////////

#define set_global_dynamics_model(MODEL) (global_options.dynamics_model = (MODEL))

#define get_global_dynamics_model() (global_options.dynamics_model)

////////////////////////////////////////

#define set_global_cyclic_input(INPUT) (global_options.cyclic_input = (INPUT))

#define get_global_cyclic_input() (global_options.cyclic_input)

////////////////////////////////////////

#define set_global_collective_input(INPUT) (global_options.collective_input = (INPUT))

#define get_global_collective_input() (global_options.collective_input)

////////////////////////////////////////

#define set_global_pedal_input(INPUT) (global_options.pedal_input = (INPUT))

#define get_global_pedal_input() (global_options.pedal_input)

////////////////////////////////////////

#define set_global_joystick_device_index(INDEX) (global_options.joystick_device_index = (INDEX))

#define get_global_joystick_device_index() (global_options.joystick_device_index)

////////////////////////////////////////

#define set_global_map(MAP) (global_options.map = (MAP))

#define get_global_map() (global_options.map)

////////////////////////////////////////

#define set_global_sound_effects_enabled(FLAG) (global_options.sound_effects_enabled = (FLAG))
#define get_global_sound_effects_enabled() (global_options.sound_effects_enabled)

#define set_global_sound_music(FLAG) (global_options.sound_music_status = (FLAG))
#define get_global_sound_music() (global_options.sound_music_status)

#define set_global_speech_effects_enabled(FLAG) (global_options.sound_speech_enabled = (FLAG))
#define get_global_speech_effects_enabled() (global_options.sound_speech_enabled)

#define set_global_copilot_speech_effects_enabled(FLAG) (global_options.sound_speech_copilot_enabled = (FLAG))
#define get_global_copilot_speech_effects_enabled() (global_options.sound_speech_copilot_enabled)

////////////////////////////////////////

#define set_global_graphics_rain_textures_enabled(FLAG) (global_options.graphics_rain_textures_enabled = (FLAG))

#define get_global_graphics_rain_textures_enabled() (global_options.graphics_rain_textures_enabled)

////////////////////////////////////////

#define get_global_apache_havoc_installed() (global_options.apache_havoc_installed)

#define set_global_apache_havoc_installed(FLAG) (global_options.apache_havoc_installed = (FLAG))

////////////////////////////////////////

#define get_global_dynamics_options_wind() (global_options.dynamics_options_wind)

#define get_global_dynamics_options_transitional_lift() (global_options.dynamics_options_transitional_lift)

#define get_global_dynamics_options_vortex_ring() (global_options.dynamics_options_vortex_ring)

#define get_global_dynamics_options_reverse_throttle_input() (global_options.dynamics_options_reverse_throttle_input)

#define get_global_dynamics_options_keyboard_assistance() (global_options.dynamics_options_keyboard_assistance)

#define get_global_dynamics_options_retreating_blade_stall() (global_options.dynamics_options_retreating_blade_stall)

#define get_global_dynamics_options_cross_coupling() (global_options.dynamics_options_cross_coupling)

#define get_global_dynamics_options_ground_effect() (global_options.dynamics_options_ground_effect)

#define get_global_dynamics_options_object_collisions() (global_options.dynamics_options_object_collisions)

#define get_global_dynamics_options_ground_collisions() (global_options.dynamics_options_ground_collisions)

#define get_global_dynamics_options_damage() (global_options.dynamics_options_damage)

#define get_global_dynamics_options_over_torque() (global_options.dynamics_options_over_torque)

#define get_global_dynamics_options_draw_flight_path() (global_options.dynamics_options_draw_flight_path)

////////////////////////////////////////

#define set_global_dynamics_options_wind(FLAG) (global_options.dynamics_options_wind = (FLAG))

#define set_global_dynamics_options_transitional_lift(FLAG) (global_options.dynamics_options_transitional_lift = (FLAG))

#define set_global_dynamics_options_vortex_ring(FLAG) (global_options.dynamics_options_vortex_ring = (FLAG))

#define set_global_dynamics_options_retreating_blade_stall(FLAG) (global_options.dynamics_options_retreating_blade_stall = (FLAG))

#define set_global_dynamics_options_reverse_throttle_input(FLAG) (global_options.dynamics_options_reverse_throttle_input = (FLAG))

#define set_global_dynamics_options_keyboard_assistance(FLAG) (global_options.dynamics_options_keyboard_assistance = (FLAG))

#define set_global_dynamics_options_cross_coupling(FLAG) (global_options.dynamics_options_cross_coupling = (FLAG))

#define set_global_dynamics_options_ground_effect(FLAG) (global_options.dynamics_options_ground_effect = (FLAG))

#define set_global_dynamics_options_object_collisions(FLAG) (global_options.dynamics_options_object_collisions = (FLAG))

#define set_global_dynamics_options_ground_collisions(FLAG) (global_options.dynamics_options_ground_collisions = (FLAG))

#define set_global_dynamics_options_damage(FLAG) (global_options.dynamics_options_damage = (FLAG))

#define set_global_dynamics_options_over_torque(FLAG) (global_options.dynamics_options_over_torque = (FLAG))

#define set_global_dynamics_options_draw_flight_path(FLAG) (global_options.dynamics_options_draw_flight_path = (FLAG))

////////////////////////////////////////

#define set_global_graphics_device_selection_automatic(FLAG) (global_options.graphics_device_selection_automatic = (FLAG))

#define get_global_graphics_device_selection_automatic() (global_options.graphics_device_selection_automatic)

#define set_global_graphics_device_selection_primary(FLAG) (global_options.graphics_device_selection_primary = (FLAG))

#define get_global_graphics_device_selection_primary() (global_options.graphics_device_selection_primary)

////////////////////////////////////////

#define set_global_graphics_files_wrong_format(FLAG) (global_options.graphics_files_wrong_format = (FLAG))

#define get_global_graphics_files_wrong_format() (global_options.graphics_files_wrong_format)

#define set_global_graphics_files_red_mask(FLAG) (global_options.graphics_files_red_mask = (FLAG))

#define get_global_graphics_files_red_mask() (global_options.graphics_files_red_mask)

#define set_global_graphics_files_green_mask(FLAG) (global_options.graphics_files_green_mask = (FLAG))

#define get_global_graphics_files_green_mask() (global_options.graphics_files_green_mask)

#define set_global_graphics_files_blue_mask(FLAG) (global_options.graphics_files_blue_mask = (FLAG))

#define get_global_graphics_files_blue_mask() (global_options.graphics_files_blue_mask)

#define set_global_graphics_files_alpha_mask(FLAG) (global_options.graphics_files_alpha_mask = (FLAG))

#define get_global_graphics_files_alpha_mask() (global_options.graphics_files_alpha_mask)

////////////////////////////////////////

#define set_global_comms_port(VALUE) (global_options.comms_port = (VALUE))

#define get_global_comms_port() (global_options.comms_port)

#define set_global_baud_rate(VALUE) (global_options.baud_rate = (VALUE))

#define get_global_baud_rate() (global_options.baud_rate)

#define set_global_stop_bits(VALUE) (global_options.stop_bits = (VALUE))

#define get_global_stop_bits() (global_options.stop_bits)

#define set_global_parity(VALUE) (global_options.parity = (VALUE))

#define get_global_parity() (global_options.parity)

#define set_global_flow(VALUE) (global_options.flow = (VALUE))

#define get_global_flow() (global_options.flow)

////////////////////////////////////////

#define set_global_cpg_assist_type(TYPE) (global_options.cpg_assist_type = (TYPE))

#define get_global_cpg_assist_type() (global_options.cpg_assist_type)

#define set_global_auto_counter_measures(FLAG) (global_options.auto_counter_measures = (FLAG))

#define get_global_auto_counter_measures() (global_options.auto_counter_measures)

#define set_global_ase_auto_page(FLAG) (global_options.ase_auto_page = (FLAG))

#define get_global_ase_auto_page() (global_options.ase_auto_page)

#define set_global_glass_cockpit(FLAG) (global_options.glass_cockpit = (FLAG))

#define get_global_glass_cockpit() (global_options.glass_cockpit)

#define set_global_cockpit_detail_level(LEVEL) (global_options.cockpit_detail_level = (LEVEL))

#define get_global_cockpit_detail_level() (global_options.cockpit_detail_level)

#define set_global_simple_avionics(FLAG) (global_options.simple_avionics = (FLAG))

#define get_global_simple_avionics() (global_options.simple_avionics)

#define set_global_display_in_flight_intelligence_messages(FLAG) (global_options.display_in_flight_intelligence_messages = (FLAG))

#define get_global_display_in_flight_intelligence_messages() (global_options.display_in_flight_intelligence_messages)

#define set_global_unscaled_displays(FLAG) (global_options.unscaled_displays = (FLAG))

#define get_global_unscaled_displays() (global_options.unscaled_displays)

#define set_global_map_layer_options(VALUE) (global_options.map_layer_options = (VALUE))

#define get_global_map_layer_options() (global_options.map_layer_options)

#define set_global_sound_channel_volume(CHANNEL,VALUE) (global_options.sound_channel_volume [(CHANNEL)] = (VALUE))

#define get_global_sound_channel_volume(CHANNEL) (global_options.sound_channel_volume [(CHANNEL)])

#define set_global_sound_channel_muted(CHANNEL,VALUE) (global_options.sound_channel_muted [(CHANNEL)] = (VALUE))

#define get_global_sound_channel_muted(CHANNEL) (global_options.sound_channel_muted [(CHANNEL)])

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define set_global_graphics_object_detail_level(TYPE) (global_options.graphics_object_detail_level = (TYPE))

#define get_global_graphics_object_detail_level() (global_options.graphics_object_detail_level)

#define set_global_graphics_terrain_detail_level(TYPE) (global_options.graphics_terrain_detail_level = (TYPE))

#define get_global_graphics_terrain_detail_level() (global_options.graphics_terrain_detail_level)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define set_global_session_free_flight_time_of_day(VALUE) (global_options.session_free_flight_time_of_day = (VALUE))
#define get_global_session_free_flight_time_of_day() (global_options.session_free_flight_time_of_day)

#define set_global_session_campaign_time_of_day(VALUE) (global_options.session_campaign_time_of_day = (VALUE))
#define get_global_session_campaign_time_of_day() (global_options.session_campaign_time_of_day)


#define set_global_session_free_flight_weather(VALUE) (global_options.session_free_flight_weather = (VALUE))
#define get_global_session_free_flight_weather() (global_options.session_free_flight_weather)

#define set_global_session_campaign_weather(VALUE) (global_options.session_campaign_weather = (VALUE))
#define get_global_session_campaign_weather() (global_options.session_campaign_weather)


#define set_global_difficulty_level(VALUE) (global_options.difficulty_level = (VALUE))
#define get_global_difficulty_level() (global_options.difficulty_level)


#define set_global_session_free_flight_realism_infinite_weapons(VALUE) (global_options.session_free_flight_realism_infinite_weapons = (VALUE))
#define get_global_session_free_flight_realism_infinite_weapons() (global_options.session_free_flight_realism_infinite_weapons)

#define set_global_session_free_flight_realism_infinite_fuel(VALUE) (global_options.session_free_flight_realism_infinite_fuel = (VALUE))
#define get_global_session_free_flight_realism_infinite_fuel() (global_options.session_free_flight_realism_infinite_fuel)

#define set_global_session_free_flight_realism_invulnerable_from_weapons(VALUE) (global_options.session_free_flight_realism_invulnerable_from_weapons = (VALUE))
#define get_global_session_free_flight_realism_invulnerable_from_weapons() (global_options.session_free_flight_realism_invulnerable_from_weapons)

#define set_global_session_free_flight_realism_invulnerable_from_collisions(VALUE) (global_options.session_free_flight_realism_invulnerable_from_collisions = (VALUE))
#define get_global_session_free_flight_realism_invulnerable_from_collisions() (global_options.session_free_flight_realism_invulnerable_from_collisions)

#define set_global_session_free_flight_realism_suppress_ai_fire(VALUE) (global_options.session_free_flight_realism_suppress_ai_fire = (VALUE))
#define get_global_session_free_flight_realism_suppress_ai_fire() (global_options.session_free_flight_realism_suppress_ai_fire)


#define set_global_session_campaign_realism_infinite_weapons(VALUE) (global_options.session_campaign_realism_infinite_weapons = (VALUE))
#define get_global_session_campaign_realism_infinite_weapons() (global_options.session_campaign_realism_infinite_weapons)

#define set_global_session_campaign_realism_infinite_fuel(VALUE) (global_options.session_campaign_realism_infinite_fuel = (VALUE))
#define get_global_session_campaign_realism_infinite_fuel() (global_options.session_campaign_realism_infinite_fuel)

#define set_global_session_campaign_realism_invulnerable_from_weapons(VALUE) (global_options.session_campaign_realism_invulnerable_from_weapons = (VALUE))
#define get_global_session_campaign_realism_invulnerable_from_weapons() (global_options.session_campaign_realism_invulnerable_from_weapons)

#define set_global_session_campaign_realism_invulnerable_from_collisions(VALUE) (global_options.session_campaign_realism_invulnerable_from_collisions = (VALUE))
#define get_global_session_campaign_realism_invulnerable_from_collisions() (global_options.session_campaign_realism_invulnerable_from_collisions)

#define set_global_session_campaign_realism_suppress_ai_fire(VALUE) (global_options.session_campaign_realism_suppress_ai_fire = (VALUE))
#define get_global_session_campaign_realism_suppress_ai_fire() (global_options.session_campaign_realism_suppress_ai_fire)


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define set_global_current_language(VALUE) (global_options.current_language = (VALUE))
#define get_global_current_language() (global_options.current_language)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void initialise_global_options_data (void);

extern void set_global_gunship_type (gunship_types type);

extern void set_global_hud_colour (hud_colours colour);

extern void set_global_graphics_device_selection_guid ( GUID *guid );

extern void save_global_options_data (void);

extern void load_global_options_data (void);
/*
extern char *get_localisation_text (game_text_translation_type *list, int button_id);

extern int get_localisation_x_position (game_text_translation_type *list, int button_id);

extern int get_localisation_y_position (game_text_translation_type *list, int button_id);

extern int get_localisation_x_size (game_text_translation_type *list, int button_id);

extern int get_localisation_y_size (game_text_translation_type *list, int button_id);
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define UI_ATTR_LOCALISATION_TEXT(LIST, TYPE) UI_ATTR_TEXT (get_localisation_text ((LIST), (TYPE)))

#define UI_ATTR_LOCALISATION_POSITION(LIST, TYPE) UI_ATTR_POSITION (get_localisation_x_position ((LIST), (TYPE)), get_localisation_y_position ((LIST), (TYPE)))

#define UI_ATTR_LOCALISATION_SIZE(LIST, TYPE) UI_ATTR_SIZE (get_localisation_x_size ((LIST), (TYPE)), get_localisation_y_size ((LIST), (TYPE)))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define get_apache_havoc_gunship() ((get_global_gunship_type () == GUNSHIP_TYPE_APACHE) || (get_global_gunship_type () == GUNSHIP_TYPE_HAVOC))

#define get_comanche_hokum_gunship() ((get_global_gunship_type () == GUNSHIP_TYPE_COMANCHE) || (get_global_gunship_type () == GUNSHIP_TYPE_HOKUM))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
