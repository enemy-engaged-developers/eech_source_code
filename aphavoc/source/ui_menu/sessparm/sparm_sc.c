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

#define CLEAR_BOXES 1

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum
{

	REALISM_INFINITE_WEAPONS,
	REALISM_INFINITE_FUEL,
	REALISM_COLLISIONS,
	REALISM_WEAPONS_DAMAGE,
	REALISM_SUPPRESS_AI_FIRE,
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ui_object
	*session_parameters_area = nullptr,
//VJ 051011 add season summer/winter/desert button
	*season_area = nullptr,
	*season_button = nullptr,
	*time_of_day_area = nullptr,
	*time_of_day_button = nullptr,
	*weather_area = nullptr,
	*weather_button = nullptr,

	*realism_inf_weapons_area = nullptr,
	*realism_inf_weapons_title = nullptr,
	*realism_inf_weapons_button = nullptr,
	*realism_inf_fuel_area = nullptr,
	*realism_inf_fuel_title = nullptr,
	*realism_inf_fuel_button = nullptr,
	*realism_collisions_area = nullptr,
	*realism_collisions_button = nullptr,
	*realism_weapons_damage_area = nullptr,
	*realism_weapons_damage_button = nullptr,
	*realism_suppress_ai_fire_area = nullptr,
	*realism_suppress_ai_fire_button = nullptr;

static const char
	*boolean_text[2],
	*suppress_ai_fire_text[2],
	*time_of_day_text[6],
	*weather_text[4],
//VJ 051011 add season default/summer/winter/desert button
	*season_text[4];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//static void notify_text_input_function ( ui_object *obj, void *arg );

static void session_parameters_text_input_function ( ui_object *obj, void *arg );

static void session_parameters_bounded_input_function ( ui_object *obj, void *arg, int minimum, int maximum );

static void process_session_setup_time_of_day_options (session_time_of_day_settings time_of_day);

static void process_session_setup_weather_options (session_weather_settings weather_setting);

static void process_sessparm_objects (ui_object *title_box_obj, ui_object *title_text_obj, ui_object *button_box_obj, ui_object *button_obj, const char *button_text[], int num_strings);

static void process_sessparm_boolean_objects (ui_object *title_box_obj, ui_object *title_text_obj, ui_object *button_box_obj, ui_object *button_obj, const char *button_text[], int num_strings);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_session_parameters (void)
{
	float
		y;

	notify_clear_all_session_parameters ();

	//VJ 051227 reading map inof data for automatic custom map
	// function declared in textuser.c
	debug_log("###CUSTOM TEXTURE STARTUP: sparm_sc: notify_session_parameters: read_map_info_data");

	//VJ 080215 add initialize to avoid being stuck on season first selected campaign
	initialise_custom_map_info();

	// 15JUN09 Casm setting season information for saved game
	set_global_season (get_current_game_session()->season);

	read_map_info_data();

	//
	// Set the button states
	//

	//VJ 051227 set season info with map_info structure
	set_global_season( current_map_info.season );

	if (get_current_game_session()->type == SESSION_LIST_TYPE_RESTORE)
	{
		return;
	}

	if (current_map_info.season != SESSION_SEASON_SUMMER && current_map_info.season != SESSION_SEASON_WINTER)
	{
		set_ui_object_highlightable (season_button, FALSE);

		set_ui_object_font_colour_end (season_button, ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 127);

		set_ui_object_notify_on (season_button, NOTIFY_TYPE_NONE);
	}
	else
	{
		set_ui_object_highlightable (season_button, TRUE);

		set_ui_object_font_colour_end (season_button, ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255);

		set_ui_object_notify_on (season_button, NOTIFY_TYPE_BUTTON_DOWN);
	}

	switch ( get_game_type () )
	{

		case GAME_TYPE_FREE_FLIGHT:
		{
//VJ 051011 add season summer/winter/desert button
			y = 0.333;
			set_ui_object_virtual_y (season_area, y);
			set_ui_object_text (season_button, season_text [get_global_season () - 1]);

			y += OPTION_AREA_OFFSET_Y;
			set_ui_object_virtual_y (time_of_day_area, y);
			set_ui_object_text (time_of_day_button, time_of_day_text [get_global_session_free_flight_time_of_day () - 1]);

			y += OPTION_AREA_OFFSET_Y;
			set_ui_object_virtual_y (weather_area, y);
			set_ui_object_text (weather_button, weather_text [get_global_session_free_flight_weather () - 1]);

			y += OPTION_AREA_OFFSET_Y;
			set_ui_object_virtual_y (realism_suppress_ai_fire_area, y);
			set_ui_object_text (realism_suppress_ai_fire_button, suppress_ai_fire_text [!get_global_session_free_flight_realism_suppress_ai_fire ()]);

			y += SETUP_DIVIDER_HEIGHT;
			set_ui_object_virtual_y (realism_inf_weapons_area, y);
			set_ui_object_text (realism_inf_weapons_button, boolean_text [get_global_session_free_flight_realism_infinite_weapons ()]);

			y += OPTION_AREA_OFFSET_Y;
			set_ui_object_virtual_y (realism_inf_fuel_area, y);
			set_ui_object_text (realism_inf_fuel_button, boolean_text [get_global_session_free_flight_realism_infinite_fuel ()]);

			y += OPTION_AREA_OFFSET_Y;
			set_ui_object_virtual_y (realism_collisions_area, y);
			set_ui_object_text (realism_collisions_button, boolean_text [!get_global_session_free_flight_realism_invulnerable_from_collisions ()]);

			y += OPTION_AREA_OFFSET_Y;
			set_ui_object_virtual_y (realism_weapons_damage_area, y);
			set_ui_object_text (realism_weapons_damage_button, boolean_text [!get_global_session_free_flight_realism_invulnerable_from_weapons ()]);

			set_ui_object_drawable (time_of_day_area, TRUE);
			set_ui_object_drawable (season_area, TRUE);
			set_ui_object_drawable (weather_area, TRUE);
			set_ui_object_drawable (realism_inf_weapons_area, TRUE);
			set_ui_object_drawable (realism_inf_fuel_area, TRUE);
			set_ui_object_drawable (realism_collisions_area, TRUE);
			set_ui_object_drawable (realism_weapons_damage_area, TRUE);
			set_ui_object_drawable (realism_suppress_ai_fire_area, TRUE);

			break;
		}

		case GAME_TYPE_CAMPAIGN:
		case GAME_TYPE_SKIRMISH:
		{
	//VJ 051011 add season summer/winter/desert button
			y = 0.533;
			set_ui_object_virtual_y (season_area, y);
			set_ui_object_text (season_button, season_text [get_global_season () - 1]);

			y += OPTION_AREA_OFFSET_Y;
			set_ui_object_virtual_y (time_of_day_area, y);
			set_ui_object_text (time_of_day_button, time_of_day_text [get_global_session_campaign_time_of_day () - 1]);

			y += OPTION_AREA_OFFSET_Y;
			set_ui_object_virtual_y (weather_area, y);
			set_ui_object_text (weather_button, weather_text [get_global_session_campaign_weather () - 1]);

			set_ui_object_drawable (session_briefing_overlay, TRUE);
			set_ui_object_drawable (time_of_day_area, TRUE);
			set_ui_object_drawable (season_area, TRUE);
			set_ui_object_drawable (weather_area, TRUE);

			break;
		}
	}

	#if DEMO_VERSION

		set_ui_object_font_colour_end (realism_inf_fuel_title, ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 127);

		set_ui_object_highlightable (realism_inf_fuel_button, FALSE);

		set_ui_object_font_colour_end (realism_inf_fuel_button, ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 127);

		set_ui_object_notify_on (realism_inf_fuel_button, NOTIFY_TYPE_NONE);


		set_ui_object_font_colour_end (realism_inf_weapons_title, ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 127);

		set_ui_object_highlightable (realism_inf_weapons_button, FALSE);

		set_ui_object_font_colour_end (realism_inf_weapons_button, ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 127);

		set_ui_object_notify_on (realism_inf_weapons_button, NOTIFY_TYPE_NONE);

	#endif

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_clear_all_session_parameters (void)
{
	set_ui_object_drawable (session_parameters_area, FALSE);
	set_ui_object_drawable (session_briefing_overlay, FALSE);
	set_ui_object_drawable (time_of_day_area, FALSE);
	set_ui_object_drawable (season_area, FALSE);
	set_ui_object_drawable (weather_area, FALSE);
	set_ui_object_drawable (realism_inf_weapons_area, FALSE);
	set_ui_object_drawable (realism_inf_fuel_area, FALSE);
	set_ui_object_drawable (realism_collisions_area, FALSE);
	set_ui_object_drawable (realism_weapons_damage_area, FALSE);
	set_ui_object_drawable (realism_suppress_ai_fire_area, FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void define_session_parameter_objects (void)
{
	ui_object
		*title_box_obj = nullptr,
		*title_text_obj = nullptr,
		*button_box_obj = nullptr;

	float
		x1,
		y1,
		x2,
		y2;

	boolean_text [0] = get_trans ("Off");
	boolean_text [1] = get_trans ("On");

	suppress_ai_fire_text [0] = get_trans ("Passive");
	suppress_ai_fire_text [1] = get_trans ("Hostile");

	season_text [0] = get_trans ("Default");
	season_text [1] = get_trans ("Summer");
	season_text [2] = get_trans ("Winter");
	season_text [3] = get_trans ("Desert");

	time_of_day_text [0] = get_trans ("Random");
	time_of_day_text [1] = get_trans ("Dawn");
	time_of_day_text [2] = get_trans ("Midday");
	time_of_day_text [3] = get_trans ("Afternoon");
	time_of_day_text [4] = get_trans ("Dusk");
	time_of_day_text [5] = get_trans ("Midnight");

	weather_text [0] = get_trans ("Variable");
	weather_text [1] = get_trans ("Good");
	weather_text [2] = get_trans ("Fair");
	weather_text [3] = get_trans ("Poor");

	/////////////////////////////////////////////////////////////////
	// Session Setup Area

	x1 = 0.0;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 1.0;

	session_parameters_area = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (session_screen),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2, y2),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_DRAWABLE (FALSE),
				UI_ATTR_FUNCTION (NOTIFY_TYPE_NONE),
				UI_ATTR_END
			);


	// areas and titles

//VJ 051011 add season summer/winter/desert button	==>
	/////////////////////////////////////////////////////////////////
	//Season

	x1 = 0.506;
	y1 = 0.5333;

	season_area = create_ui_object
								(
									UI_TYPE_AREA,
									UI_ATTR_PARENT (session_screen),
									UI_ATTR_VIRTUAL_POSITION (x1, y1),
									UI_ATTR_VIRTUAL_SIZE (SETUP_AREA_WIDTH, SETUP_AREA_HEIGHT),
									UI_ATTR_CLEAR (TRUE),
									UI_ATTR_END
								);

	title_box_obj = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (season_area),
		UI_ATTR_VIRTUAL_POSITION (0, 0),
		UI_ATTR_VIRTUAL_SIZE (SETUP_BOX_WIDTH, SETUP_BOX_HEIGHT),
		UI_ATTR_COLOUR_START ( 255, 255, 255, 0 ),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

	title_text_obj = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (season_area),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
		UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
		UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (SETUP_BOX_TEXT_OFFSET_X, SETUP_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("Season")),
		UI_ATTR_END
	);

	// Season Button

	button_box_obj = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (season_area),
		UI_ATTR_VIRTUAL_POSITION (SETUP_BOX_WIDTH + SETUP_BOX_GAP_WIDTH, 0),
		UI_ATTR_VIRTUAL_SIZE (SETUP_BOX_MEDIUM_WIDTH, SETUP_BOX_HEIGHT),
		UI_ATTR_COLOUR_START ( 255, 255, 255, 0 ),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_medium),
		UI_ATTR_END
	);

	season_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (button_box_obj),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
		UI_ATTR_VIRTUAL_POSITION (SETUP_BUTTON_TEXT_OFFSET_X, SETUP_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
		UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
		UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
		UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
		UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_season_function),
		UI_ATTR_END
	);

	process_sessparm_objects (title_box_obj, title_text_obj, button_box_obj, season_button, season_text, 4);

	/////////////////////////////////////////////////////////////////
	//Time of Day

	y1 += OPTION_AREA_OFFSET_Y;

	time_of_day_area = create_ui_object
								(
									UI_TYPE_AREA,
									UI_ATTR_PARENT (session_screen),
									UI_ATTR_VIRTUAL_POSITION (x1, y1),
									UI_ATTR_VIRTUAL_SIZE (SETUP_AREA_WIDTH, SETUP_AREA_HEIGHT),
									UI_ATTR_CLEAR (TRUE),
									UI_ATTR_END
								);

	title_box_obj = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (time_of_day_area),
		UI_ATTR_VIRTUAL_POSITION (0, 0),
		UI_ATTR_VIRTUAL_SIZE (SETUP_BOX_WIDTH, SETUP_BOX_HEIGHT),
		UI_ATTR_COLOUR_START ( 255, 255, 255, 0 ),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

	title_text_obj = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (time_of_day_area),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
		UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
		UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (SETUP_BOX_TEXT_OFFSET_X, SETUP_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("Time Of Day")),
		UI_ATTR_END
	);

	// Time Of Day Button

	button_box_obj = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (time_of_day_area),
		UI_ATTR_VIRTUAL_POSITION (SETUP_BOX_WIDTH + SETUP_BOX_GAP_WIDTH, 0),
		UI_ATTR_VIRTUAL_SIZE (SETUP_BOX_MEDIUM_WIDTH, SETUP_BOX_HEIGHT),
		UI_ATTR_COLOUR_START ( 255, 255, 255, 0 ),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_medium),
		UI_ATTR_END
	);

	time_of_day_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (button_box_obj),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
		UI_ATTR_VIRTUAL_POSITION (SETUP_BUTTON_TEXT_OFFSET_X, SETUP_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
		UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
		UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
		UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
		UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_time_of_day_function),
		UI_ATTR_END
	);

	process_sessparm_objects (title_box_obj, title_text_obj, button_box_obj, time_of_day_button, time_of_day_text, 5);

//VJ 051011 <== add season summer/winter/desert button

	/////////////////////////////////////////////////////////////////
	//	Weather

	y1 += OPTION_AREA_OFFSET_Y;

	weather_area = create_ui_object
								(
									UI_TYPE_AREA,
									UI_ATTR_PARENT (session_screen),
									UI_ATTR_VIRTUAL_POSITION (x1, y1),
									UI_ATTR_VIRTUAL_SIZE (SETUP_AREA_WIDTH, SETUP_AREA_HEIGHT),
									UI_ATTR_CLEAR (TRUE),
									UI_ATTR_END
								);

	title_box_obj = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (weather_area),
		UI_ATTR_VIRTUAL_POSITION (0, 0),
		UI_ATTR_VIRTUAL_SIZE (SETUP_BOX_WIDTH, SETUP_BOX_HEIGHT),
		UI_ATTR_COLOUR_START ( 255, 255, 255, 0 ),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

	title_text_obj = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (weather_area),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
		UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
		UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (SETUP_BOX_TEXT_OFFSET_X, SETUP_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("Weather")),
		UI_ATTR_END
	);


	// Weather Button

	button_box_obj = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (weather_area),
		UI_ATTR_VIRTUAL_POSITION (SETUP_BOX_WIDTH + SETUP_BOX_GAP_WIDTH, 0),
		UI_ATTR_VIRTUAL_SIZE (SETUP_BOX_MEDIUM_WIDTH, SETUP_BOX_HEIGHT),
		UI_ATTR_COLOUR_START ( 255, 255, 255, 0 ),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_medium),
		UI_ATTR_END
	);

	weather_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (button_box_obj),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
		UI_ATTR_VIRTUAL_POSITION (SETUP_BUTTON_TEXT_OFFSET_X, SETUP_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
		UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
		UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
		UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
		UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_weather_function),
		UI_ATTR_END
	);

	process_sessparm_objects (title_box_obj, title_text_obj, button_box_obj, weather_button, weather_text, 4);

	/////////////////////////////////////////////////////////////////
	//	Realism Suppress AI Fire

	y1 += OPTION_AREA_OFFSET_Y;

	realism_suppress_ai_fire_area = create_ui_object
								(
									UI_TYPE_AREA,
									UI_ATTR_PARENT (session_screen),
									UI_ATTR_VIRTUAL_POSITION (x1, y1),
									UI_ATTR_VIRTUAL_SIZE (SETUP_AREA_WIDTH, SETUP_AREA_HEIGHT),
									UI_ATTR_CLEAR (TRUE),
									UI_ATTR_END
								);

	title_box_obj = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (realism_suppress_ai_fire_area),
		UI_ATTR_VIRTUAL_POSITION (0, 0),
		UI_ATTR_VIRTUAL_SIZE (SETUP_BOX_WIDTH, SETUP_BOX_HEIGHT),
		UI_ATTR_COLOUR_START ( 255, 255, 255, 0 ),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

	title_text_obj = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (realism_suppress_ai_fire_area),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
		UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
		UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (SETUP_BOX_TEXT_OFFSET_X, SETUP_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("Environment")),
		UI_ATTR_END
	);


	// Suppress AI Fire Button

	button_box_obj = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (realism_suppress_ai_fire_area),
		UI_ATTR_VIRTUAL_POSITION (SETUP_BOX_WIDTH + SETUP_BOX_GAP_WIDTH, 0),
		UI_ATTR_VIRTUAL_SIZE (SETUP_BOX_MEDIUM_WIDTH, SETUP_BOX_HEIGHT),
		UI_ATTR_COLOUR_START ( 255, 255, 255, 0 ),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_small),
		UI_ATTR_END
	);

	realism_suppress_ai_fire_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (button_box_obj),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
		UI_ATTR_VIRTUAL_POSITION (SETUP_BUTTON_TEXT_OFFSET_X, SETUP_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
		UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
		UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
		UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
		UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_realism_suppress_ai_fire_function),
		UI_ATTR_END
	);

	process_sessparm_boolean_objects (title_box_obj, title_text_obj, button_box_obj, realism_suppress_ai_fire_button, suppress_ai_fire_text, 2);

	/////////////////////////////////////////////////////////////////
	//	Realism Infinite Weapons

	y1 += OPTION_AREA_OFFSET_Y;

	realism_inf_weapons_area = create_ui_object
								(
									UI_TYPE_AREA,
									UI_ATTR_PARENT (session_screen),
									UI_ATTR_VIRTUAL_POSITION (x1, y1),
									UI_ATTR_VIRTUAL_SIZE (SETUP_AREA_WIDTH, SETUP_AREA_HEIGHT),
									UI_ATTR_CLEAR (TRUE),
									UI_ATTR_END
								);


	title_box_obj = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (realism_inf_weapons_area),
		UI_ATTR_VIRTUAL_POSITION (0, 0),
		UI_ATTR_VIRTUAL_SIZE (SETUP_BOX_WIDTH, SETUP_BOX_HEIGHT),
		UI_ATTR_COLOUR_START ( 255, 255, 255, 0 ),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

	title_text_obj = realism_inf_weapons_title = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (realism_inf_weapons_area),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
		UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
		UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (SETUP_BOX_TEXT_OFFSET_X, SETUP_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("Infinite Weapons")),
		UI_ATTR_END
	);


	// Infinite Weapons Button

	button_box_obj = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (realism_inf_weapons_area),
		UI_ATTR_VIRTUAL_POSITION (SETUP_BOX_WIDTH + SETUP_BOX_GAP_WIDTH, 0),
		UI_ATTR_VIRTUAL_SIZE (SETUP_BOX_SMALL_WIDTH, SETUP_BOX_HEIGHT),
		UI_ATTR_COLOUR_START ( 255, 255, 255, 0 ),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_small),
		UI_ATTR_END
	);

	realism_inf_weapons_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (button_box_obj),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
		UI_ATTR_VIRTUAL_POSITION (SETUP_BUTTON_TEXT_OFFSET_X, SETUP_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
		UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
		UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
		UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
		UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_realism_inf_weapons_function),
		UI_ATTR_END
	);

	process_sessparm_boolean_objects (title_box_obj, title_text_obj, button_box_obj, realism_inf_weapons_button, boolean_text, 2);

	/////////////////////////////////////////////////////////////////
	//	Realism Infinite Fuel

	y1 += OPTION_AREA_OFFSET_Y;

	realism_inf_fuel_area = create_ui_object
								(
									UI_TYPE_AREA,
									UI_ATTR_PARENT (session_screen),
									UI_ATTR_VIRTUAL_POSITION (x1, y1),
									UI_ATTR_VIRTUAL_SIZE (SETUP_AREA_WIDTH, SETUP_AREA_HEIGHT),
									UI_ATTR_CLEAR (TRUE),
									UI_ATTR_END
								);

	title_box_obj = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (realism_inf_fuel_area),
		UI_ATTR_VIRTUAL_POSITION (0, 0),
		UI_ATTR_VIRTUAL_SIZE (SETUP_BOX_WIDTH, SETUP_BOX_HEIGHT),
		UI_ATTR_COLOUR_START ( 255, 255, 255, 0 ),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

	title_text_obj = realism_inf_fuel_title = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (realism_inf_fuel_area),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
		UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
		UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (SETUP_BOX_TEXT_OFFSET_X, SETUP_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("Infinite Fuel")),
		UI_ATTR_END
	);


	// Infinite Fuel Button

	button_box_obj = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (realism_inf_fuel_area),
		UI_ATTR_VIRTUAL_POSITION (SETUP_BOX_WIDTH + SETUP_BOX_GAP_WIDTH, 0),
		UI_ATTR_VIRTUAL_SIZE (SETUP_BOX_SMALL_WIDTH, SETUP_BOX_HEIGHT),
		UI_ATTR_COLOUR_START ( 255, 255, 255, 0 ),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_small),
		UI_ATTR_END
	);

	realism_inf_fuel_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (button_box_obj),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
		UI_ATTR_VIRTUAL_POSITION (SETUP_BUTTON_TEXT_OFFSET_X, SETUP_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
		UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
		UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
		UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
		UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_realism_inf_fuel_function),
		UI_ATTR_END
	);

	process_sessparm_boolean_objects (title_box_obj, title_text_obj, button_box_obj, realism_inf_fuel_button, boolean_text, 2);

	/////////////////////////////////////////////////////////////////
	//	Realism Collisions

	y1 += OPTION_AREA_OFFSET_Y;

	realism_collisions_area = create_ui_object
								(
									UI_TYPE_AREA,
									UI_ATTR_PARENT (session_screen),
									UI_ATTR_VIRTUAL_POSITION (x1, y1),
									UI_ATTR_VIRTUAL_SIZE (SETUP_AREA_WIDTH, SETUP_AREA_HEIGHT),
									UI_ATTR_CLEAR (TRUE),
									UI_ATTR_END
								);

	title_box_obj = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (realism_collisions_area),
		UI_ATTR_VIRTUAL_POSITION (0, 0),
		UI_ATTR_VIRTUAL_SIZE (SETUP_BOX_WIDTH, SETUP_BOX_HEIGHT),
		UI_ATTR_COLOUR_START ( 255, 255, 255, 0 ),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

	title_text_obj = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (realism_collisions_area),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
		UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
		UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (SETUP_BOX_TEXT_OFFSET_X, SETUP_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("Collisions")),
		UI_ATTR_END
	);


	// Collisions Button

	button_box_obj = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (realism_collisions_area),
		UI_ATTR_VIRTUAL_POSITION (SETUP_BOX_WIDTH + SETUP_BOX_GAP_WIDTH, 0),
		UI_ATTR_VIRTUAL_SIZE (SETUP_BOX_SMALL_WIDTH, SETUP_BOX_HEIGHT),
		UI_ATTR_COLOUR_START ( 255, 255, 255, 0 ),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_small),
		UI_ATTR_END
	);

	realism_collisions_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (button_box_obj),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
		UI_ATTR_VIRTUAL_POSITION (SETUP_BUTTON_TEXT_OFFSET_X, SETUP_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
		UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
		UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
		UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
		UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_realism_collisions_function),
		UI_ATTR_END
	);

	process_sessparm_boolean_objects (title_box_obj, title_text_obj, button_box_obj, realism_collisions_button, boolean_text, 2);

	/////////////////////////////////////////////////////////////////
	//	Realism Weapons Damage

	y1 += OPTION_AREA_OFFSET_Y;

	realism_weapons_damage_area = create_ui_object
								(
									UI_TYPE_AREA,
									UI_ATTR_PARENT (session_screen),
									UI_ATTR_VIRTUAL_POSITION (x1, y1),
									UI_ATTR_VIRTUAL_SIZE (SETUP_AREA_WIDTH, SETUP_AREA_HEIGHT),
									UI_ATTR_CLEAR (TRUE),
									UI_ATTR_END
								);

	title_box_obj = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (realism_weapons_damage_area),
		UI_ATTR_VIRTUAL_POSITION (0, 0),
		UI_ATTR_VIRTUAL_SIZE (SETUP_BOX_WIDTH, SETUP_BOX_HEIGHT),
		UI_ATTR_COLOUR_START ( 255, 255, 255, 0 ),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

	title_text_obj = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (realism_weapons_damage_area),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
		UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
		UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (SETUP_BOX_TEXT_OFFSET_X, SETUP_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("Weapons Damage")),
		UI_ATTR_END
	);


	// Weapons Damage Button

	button_box_obj = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (realism_weapons_damage_area),
		UI_ATTR_VIRTUAL_POSITION (SETUP_BOX_WIDTH + SETUP_BOX_GAP_WIDTH, 0),
		UI_ATTR_VIRTUAL_SIZE (SETUP_BOX_SMALL_WIDTH, SETUP_BOX_HEIGHT),
		UI_ATTR_COLOUR_START ( 255, 255, 255, 0 ),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_small),
		UI_ATTR_END
	);

	realism_weapons_damage_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (button_box_obj),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
		UI_ATTR_VIRTUAL_POSITION (SETUP_BUTTON_TEXT_OFFSET_X, SETUP_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
		UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
		UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
		UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
		UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_realism_weapons_damage_function),
		UI_ATTR_END
	);

	process_sessparm_boolean_objects (title_box_obj, title_text_obj, button_box_obj, realism_weapons_damage_button, boolean_text, 2);

	notify_clear_all_session_parameters ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//VJ 051011 add season summer/winter/desert button	==>
void notify_season_function ( ui_object *obj, void *arg )
{

	int
		tod;

	tod = get_global_season ();

	tod++;
	// skip deserts. they cannot be changed
	if (tod == SESSION_SEASON_DESERT)
		tod = SESSION_SEASON_SUMMER;
	if (tod == SESSION_SEASON_DEFAULT)
		tod = SESSION_SEASON_SUMMER;

	set_global_season (tod);

	set_ui_object_text (obj, season_text [get_global_season () - 1]);

	set_toggle_button_off (obj);

//VJ 060319 further bug fixes
	debug_log("###CUSTOM TEXTURE STARTUP: sparm_sc: notify_season_function");
}
//VJ 051011 <==add season summer/winter/desert button
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_time_of_day_function ( ui_object *obj, void *arg )
{
	int
		tod;

	switch ( get_game_type () )
	{
		case GAME_TYPE_FREE_FLIGHT:
		{
			tod = get_global_session_free_flight_time_of_day ();

			break;
		}

		case GAME_TYPE_CAMPAIGN:
		case GAME_TYPE_SKIRMISH:
		{
			tod = get_global_session_campaign_time_of_day ();

			break;
		}
	}

	tod++;

	if (tod > SESSION_TIME_MIDNIGHT)
	{
		tod = SESSION_TIME_RANDOM;
	}

	switch ( get_game_type () )
	{
		case GAME_TYPE_FREE_FLIGHT:
		{
			set_global_session_free_flight_time_of_day ((enum SESSION_TIME_OF_DAY_SETTINGS) tod);

			set_ui_object_text (obj, time_of_day_text [get_global_session_free_flight_time_of_day () - 1]);

			break;
		}

		case GAME_TYPE_CAMPAIGN:
		case GAME_TYPE_SKIRMISH:
		{
			set_global_session_campaign_time_of_day ((enum SESSION_TIME_OF_DAY_SETTINGS) tod);

			set_ui_object_text (obj, time_of_day_text [get_global_session_campaign_time_of_day () - 1]);

			break;
		}
	}

	// don't leave text selected

	set_toggle_button_off (obj);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_weather_function ( ui_object *obj, void *arg )
{
	int
		weather;

	switch ( get_game_type () )
	{
		case GAME_TYPE_FREE_FLIGHT:
		{
			weather = get_global_session_free_flight_weather ();

			break;
		}

		case GAME_TYPE_CAMPAIGN:
		case GAME_TYPE_SKIRMISH:
		{
			weather = get_global_session_campaign_weather ();

			break;
		}
	}

	weather++;

	if (weather > SESSION_WEATHER_POOR)
	{
		weather = SESSION_WEATHER_RANDOM;
	}

	switch ( get_game_type () )
	{
		case GAME_TYPE_FREE_FLIGHT:
		{
			set_global_session_free_flight_weather ((enum SESSION_WEATHER_SETTINGS) weather);

			set_ui_object_text (obj, weather_text [get_global_session_free_flight_weather () - 1]);

			break;
		}

		case GAME_TYPE_CAMPAIGN:
		case GAME_TYPE_SKIRMISH:
		{
			set_global_session_campaign_weather ((enum SESSION_WEATHER_SETTINGS) weather);

			set_ui_object_text (obj, weather_text [get_global_session_campaign_weather () - 1]);

			break;
		}
	}

	// don't leave text selected

	set_toggle_button_off (obj);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_realism_inf_weapons_function ( ui_object *obj, void *arg )
{

	switch ( get_game_type () )
	{
		case GAME_TYPE_FREE_FLIGHT:
		{
			set_global_session_free_flight_realism_infinite_weapons (!get_global_session_free_flight_realism_infinite_weapons ());

			set_ui_object_text (obj, boolean_text [get_global_session_free_flight_realism_infinite_weapons ()]);

			break;
		}

		case GAME_TYPE_CAMPAIGN:
		case GAME_TYPE_SKIRMISH:
		{
			set_global_session_campaign_realism_infinite_weapons (!get_global_session_campaign_realism_infinite_weapons ());

			set_ui_object_text (obj, boolean_text [get_global_session_campaign_realism_infinite_weapons ()]);

			break;
		}
	}

	// don't leave text selected

	set_toggle_button_off (obj);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_realism_inf_fuel_function ( ui_object *obj, void *arg )
{

	switch ( get_game_type () )
	{
		case GAME_TYPE_FREE_FLIGHT:
		{
			set_global_session_free_flight_realism_infinite_fuel (!get_global_session_free_flight_realism_infinite_fuel ());

			set_ui_object_text (obj, boolean_text [get_global_session_free_flight_realism_infinite_fuel ()]);

			break;
		}

		case GAME_TYPE_CAMPAIGN:
		case GAME_TYPE_SKIRMISH:
		{
			set_global_session_campaign_realism_infinite_fuel (!get_global_session_campaign_realism_infinite_fuel ());

			set_ui_object_text (obj, boolean_text [get_global_session_campaign_realism_infinite_fuel ()]);

			break;
		}
	}

	// don't leave text selected

	set_toggle_button_off (obj);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_realism_collisions_function ( ui_object *obj, void *arg )
{

	switch ( get_game_type () )
	{
		case GAME_TYPE_FREE_FLIGHT:
		{
			set_global_session_free_flight_realism_invulnerable_from_collisions (!get_global_session_free_flight_realism_invulnerable_from_collisions ());

			set_ui_object_text (obj, boolean_text [!get_global_session_free_flight_realism_invulnerable_from_collisions ()]);

			break;
		}

		case GAME_TYPE_CAMPAIGN:
		case GAME_TYPE_SKIRMISH:
		{
			set_global_session_campaign_realism_invulnerable_from_collisions (!get_global_session_campaign_realism_invulnerable_from_collisions ());

			set_ui_object_text (obj, boolean_text [!get_global_session_campaign_realism_invulnerable_from_collisions ()]);

			break;
		}
	}

	// don't leave text selected

	set_toggle_button_off (obj);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_realism_weapons_damage_function ( ui_object *obj, void *arg )
{

	switch ( get_game_type () )
	{
		case GAME_TYPE_FREE_FLIGHT:
		{
			set_global_session_free_flight_realism_invulnerable_from_weapons (!get_global_session_free_flight_realism_invulnerable_from_weapons ());

			set_ui_object_text (obj, boolean_text [!get_global_session_free_flight_realism_invulnerable_from_weapons ()]);

			break;
		}

		case GAME_TYPE_CAMPAIGN:
		case GAME_TYPE_SKIRMISH:
		{
			set_global_session_campaign_realism_invulnerable_from_weapons (!get_global_session_campaign_realism_invulnerable_from_weapons ());

			set_ui_object_text (obj, boolean_text [!get_global_session_campaign_realism_invulnerable_from_weapons ()]);

			break;
		}
	}

	// don't leave text selected

	set_toggle_button_off (obj);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_realism_suppress_ai_fire_function ( ui_object *obj, void *arg )
{

	switch ( get_game_type () )
	{
		case GAME_TYPE_FREE_FLIGHT:
		{
			set_global_session_free_flight_realism_suppress_ai_fire (!get_global_session_free_flight_realism_suppress_ai_fire ());

			set_ui_object_text (obj, suppress_ai_fire_text [!get_global_session_free_flight_realism_suppress_ai_fire ()]);

			break;
		}

		case GAME_TYPE_CAMPAIGN:
		case GAME_TYPE_SKIRMISH:
		{
			set_global_session_campaign_realism_suppress_ai_fire (!get_global_session_campaign_realism_suppress_ai_fire ());

			set_ui_object_text (obj, suppress_ai_fire_text [!get_global_session_campaign_realism_suppress_ai_fire ()]);

			break;
		}
	}

	// don't leave text selected

	set_toggle_button_off (obj);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void session_parameters_text_input_function ( ui_object *obj, void *arg )
{

	const char
		*text = nullptr;

	ui_object
		*text_object = nullptr;

	int
		value;

	obj;
	arg;

	text = get_ui_object_text ( obj );

	text_object = ( ui_object * ) get_ui_object_item_number ( obj );

	if ( ( text ) && ( strlen ( text ) > 0 ) )
	{

		set_ui_object_text ( text_object, text );
	}
	else
	{

		set_ui_object_text ( text_object, "" );
	}

	//
	// Now put the value into global options
	//

	value = -1;

	if ( strlen ( get_ui_object_text ( text_object ) ) > 0 )
	{

		sscanf ( get_ui_object_text ( text_object ), "%d", &value );
	}

#if 0
	switch ( get_ui_object_item_number ( text_object ) )
	{
/*
		case TEXT_INPUT_TIME_LIMIT:
		{

			if ( value >= 0 )
			{

				set_global_session_special_time_limit ( value );
			}
			else
			{

				set_global_session_special_time_limit ( 0 );
			}

			break;
		}

		case TEXT_INPUT_KILL_LIMIT:
		{


			sscanf ( get_ui_object_text ( text_object ), "%d", &value );

			if ( value >= 0 )
			{

				set_global_session_special_kill_limit ( value );
			}
			else
			{

				set_global_session_special_kill_limit ( 0 );
			}

			break;
		}
*/
	}
#endif

	set_ui_object_drawable ( ( ui_object * ) get_ui_object_item_number ( obj ), TRUE );

	ui_force_update ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void session_parameters_bounded_input_function ( ui_object *obj, void *arg, int minimum, int maximum )
{
	const char
		*text = nullptr;
	char
		buffer[ 8 ];

	int
		val;

	obj;
	arg;

// set input object on
// get text
// clear input object
// set input object to off
// process text
// set text area to on

	text = get_ui_object_text( obj );

	if ( ( text ) && ( strlen( text ) > 0 ) )
	{
		val = atoi ( text );

		val = bound ( val, minimum, maximum );

		itoa ( val, buffer, 10 );

		set_ui_object_text ( obj, buffer );
	}

	session_parameters_text_input_function ( obj, arg );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void session_parameters_time_limit_input_function ( ui_object *obj, void *arg )
{
	//
	// max time limit 60 minutes
	//

	session_parameters_bounded_input_function ( obj, arg, 0, 60 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void session_parameters_kill_limit_input_function ( ui_object *obj, void *arg )
{
	//
	// max kills limit dependent only on number of bits used to store kills !
	//

	session_parameters_bounded_input_function ( obj, arg, 0, (1 << (NUM_KILLS_BITS - 1)) - 1 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
void notify_text_input_function ( ui_object *obj, void *arg )
{
	set_ui_object_text (obj, "");

	set_ui_object_state ((ui_object *) get_ui_object_item_number2 (obj), UI_OBJECT_STATE_ON);

	// don't leave text selected

	set_toggle_button_off (obj);
}
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void process_session_setup_weather_options (session_weather_settings weather_setting)
{
	switch (weather_setting)
	{
		case SESSION_WEATHER_RANDOM:
		{
			if (get_local_entity_int_value (get_session_entity (), INT_TYPE_LOCAL_WEATHER_MODEL) == TRUE)
			{
				//
				// (If local_weather_model is set to FALSE, it means the weather for this warzone has been specified in the
				//		campaign file, and should not be changed)
				//

				set_session_random_weather_mode (get_session_entity ());
			}

			break;
		}
		case SESSION_WEATHER_GOOD:
		{
			set_session_fixed_weather_mode (get_session_entity (), WEATHERMODE_DRY);

			break;
		}
		case SESSION_WEATHER_FAIR:
		{
			set_session_fixed_weather_mode (get_session_entity (), WEATHERMODE_LIGHT_RAIN);

			break;
		}
		case SESSION_WEATHER_POOR:
		{
			//VJ 051014 link winter/summer to snow/rain
			if (get_global_season() == SESSION_SEASON_WINTER)
				set_session_fixed_weather_mode (get_session_entity (), WEATHERMODE_SNOW);
			else
				set_session_fixed_weather_mode (get_session_entity (), WEATHERMODE_HEAVY_RAIN);

			break;
		}
		default:
		{
			debug_fatal ("SPARM_SC: Invalid weather setting %d", weather_setting);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void process_session_setup_time_of_day_options (session_time_of_day_settings time_of_day)
{

	float
		session_time,
		setup_time;

	session_time = get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_TIME_OF_DAY);

	switch (time_of_day)
	{

		case SESSION_TIME_RANDOM:
		{
			setup_time = get_session_random_start_time_of_day ();

			break;
		}
		case SESSION_TIME_DAWN:
		case SESSION_TIME_MIDDAY:
		case SESSION_TIME_AFTERNOON:
		case SESSION_TIME_DUSK:
		case SESSION_TIME_MIDNIGHT:
		{
			setup_time = get_session_preset_time_of_day (time_of_day);

			break;
		}
		default:
		{
			debug_fatal ("SPARM_SC: Invalid time of day setting %d", time_of_day);

			break;
		}
	}

	//
	//
	//

	set_local_entity_float_value (get_session_entity (), FLOAT_TYPE_START_TIME, setup_time);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void process_host_session_setup_options (void)
{
	session_weather_settings
		weather_setting;

	session_time_of_day_settings
		time_of_day;

//VJ 051011 add season summer/winter/desert button
	//session_season_settings
		//season_setting;

	ASSERT (get_session_entity ());

	weather_setting = SESSION_WEATHER_RANDOM;

	time_of_day = SESSION_TIME_RANDOM;

//VJ 060304 changed to default season
	//season_setting = SESSION_SEASON_DEFAULT;

	switch (get_game_type ())
	{

		case GAME_TYPE_CAMPAIGN:
		case GAME_TYPE_SKIRMISH:
		{

			set_local_entity_int_value (get_session_entity (), INT_TYPE_INFINITE_FUEL, get_global_session_campaign_realism_infinite_fuel());
			set_local_entity_int_value (get_session_entity (), INT_TYPE_INFINITE_WEAPONS, get_global_session_campaign_realism_infinite_weapons());
			set_local_entity_int_value (get_session_entity (), INT_TYPE_INVULNERABLE_FROM_COLLISIONS, get_global_session_campaign_realism_invulnerable_from_collisions());
			set_local_entity_int_value (get_session_entity (), INT_TYPE_INVULNERABLE_FROM_WEAPONS, get_global_session_campaign_realism_invulnerable_from_weapons());
			set_local_entity_int_value (get_session_entity (), INT_TYPE_SUPPRESS_AI_FIRE, get_global_session_campaign_realism_suppress_ai_fire());

			weather_setting = get_global_session_campaign_weather();
			time_of_day = get_global_session_campaign_time_of_day();
//VJ 051011 add season summer/winter/desert button
			//season_setting = get_global_season();

			break;
		}

		case GAME_TYPE_FREE_FLIGHT:
		{

			set_local_entity_int_value (get_session_entity (), INT_TYPE_INFINITE_FUEL, get_global_session_free_flight_realism_infinite_fuel());
			set_local_entity_int_value (get_session_entity (), INT_TYPE_INFINITE_WEAPONS, get_global_session_free_flight_realism_infinite_weapons());
			set_local_entity_int_value (get_session_entity (), INT_TYPE_INVULNERABLE_FROM_COLLISIONS, get_global_session_free_flight_realism_invulnerable_from_collisions());
			set_local_entity_int_value (get_session_entity (), INT_TYPE_INVULNERABLE_FROM_WEAPONS, get_global_session_free_flight_realism_invulnerable_from_weapons());
			set_local_entity_int_value (get_session_entity (), INT_TYPE_SUPPRESS_AI_FIRE, get_global_session_free_flight_realism_suppress_ai_fire());

			weather_setting = get_global_session_free_flight_weather();
			time_of_day = get_global_session_free_flight_time_of_day();
//VJ 051011 add season summer/winter/desert button
			//season_setting = get_global_season();

			break;
		}
	}

	//
	// set weather
	//

	process_session_setup_weather_options (weather_setting);

	//
	// set time of day
	//

	process_session_setup_time_of_day_options (time_of_day);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void process_restore_session_setup_options (void)
{
	session_weather_settings
		weather_setting;

	session_time_of_day_settings
		time_of_day;

//VJ 051011 add season summer/winter/desert button
	//session_season_settings
		//season_setting;

	ASSERT (get_session_entity ());

	weather_setting = SESSION_WEATHER_RANDOM;

	time_of_day = SESSION_TIME_RANDOM;

	switch (get_game_type ())
	{

		case GAME_TYPE_FREE_FLIGHT:
		{

			set_local_entity_int_value (get_session_entity (), INT_TYPE_INFINITE_FUEL, get_global_session_free_flight_realism_infinite_fuel());
			set_local_entity_int_value (get_session_entity (), INT_TYPE_INFINITE_WEAPONS, get_global_session_free_flight_realism_infinite_weapons());
			set_local_entity_int_value (get_session_entity (), INT_TYPE_INVULNERABLE_FROM_COLLISIONS, get_global_session_free_flight_realism_invulnerable_from_collisions());
			set_local_entity_int_value (get_session_entity (), INT_TYPE_INVULNERABLE_FROM_WEAPONS, get_global_session_free_flight_realism_invulnerable_from_weapons());
			set_local_entity_int_value (get_session_entity (), INT_TYPE_SUPPRESS_AI_FIRE, get_global_session_free_flight_realism_suppress_ai_fire());

			weather_setting = get_global_session_free_flight_weather();
			time_of_day = get_global_session_free_flight_time_of_day();
//VJ 051011 add season summer/winter/desert button
//			season_setting = get_global_season();

			break;
		}

		default:
		{

			return;
		}
	}

	//
	// set weather
	//

	process_session_setup_weather_options (weather_setting);

	//
	// set time of day
	//

	process_session_setup_time_of_day_options (time_of_day);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void process_sessparm_objects (ui_object *title_box_obj, ui_object *title_text_obj, ui_object *button_box_obj, ui_object *button_obj, const char *button_text[], int num_strings)
{
	float
		old_size,
		new_size;

	// process button objects

	old_size = get_ui_object_virtual_x_size (button_box_obj);

	preprocess_translation_object_size (button_box_obj, button_obj, button_text, num_strings, RESIZE_SESSPARM_CYCLE_BUTTON);

	new_size = get_ui_object_virtual_x_size (button_box_obj);

	set_ui_object_virtual_x_size (button_obj, 1.0);

	set_ui_object_virtual_y_size (button_obj, 1.0);


	// process title objects

	set_ui_object_virtual_x_size (title_box_obj, (1.0 - new_size - SETUP_BOX_GAP_WIDTH));

	set_ui_object_x_end (title_text_obj, SETUP_BOX_TEXT_OFFSET_X - (new_size - old_size));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void process_sessparm_boolean_objects (ui_object *title_box_obj, ui_object *title_text_obj, ui_object *button_box_obj, ui_object *button_obj, const char *button_text[], int num_strings)
{
	float
		old_size,
		new_size;

	// process button objects

	if (get_global_current_language () != LANGUAGE_ENGLISH)
	{
		old_size = get_ui_object_virtual_x_size (button_box_obj);

		preprocess_translation_object_size (button_box_obj, button_obj, button_text, num_strings, RESIZE_SESSPARM_CYCLE_BUTTON);

		new_size = get_ui_object_virtual_x_size (button_box_obj);

		set_ui_object_x_end (button_box_obj, (1.0 - new_size));

		set_ui_object_virtual_x_size (button_obj, 1.0);

		set_ui_object_virtual_y_size (button_obj, 1.0);


		// process title objects

		set_ui_object_virtual_x_size (title_box_obj, (1.0 - new_size - SETUP_BOX_GAP_WIDTH));

		// not definite yet...
		set_ui_object_x_end (title_text_obj, (1.0 - new_size - SETUP_BOX_GAP_WIDTH - 0.05));
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
