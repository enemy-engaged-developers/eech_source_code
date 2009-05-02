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

// crh 030408 new single global version header
#include "version.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static const char
	*global_options_filename = "game.cfg";

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

game_status_types
	game_status;

const char
	*game_status_string = NULL;

int
	global_co_pilot_scans_for_targets = TRUE;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char *game_status_names [] =
{

	"GAME_STATUS_UNINITIALISED",
	"GAME_STATUS_UNINITIALISING",
	"GAME_STATUS_INITIALISING",
	"GAME_STATUS_INITIALISED",
	"NUM_GAME_STATUS_TYPES"
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////Moje 030519 "Blackhawk Gunship", added below
////Moje 030612 "Hind Gunship", added below
////Moje 030816 "AH64A Gunship", and "KA50 Gunship", added below

const char
	*gunship_type_names [] =
	{
		"Apache Gunship",
		"Havoc Gunship",
		"Comanche Gunship",
		"Hokum Gunship",
		"Blackhawk Gunship",
		"Hind Gunship",
		"AH64A Gunship",
		"KA50 GUnship",
		"NUM_GUNSHIP_TYPES"
	};

const char*
	long_gunship_names[] =
	{
		"AH-64D Apache Longbow",
		"Mi-28N Havoc B",
		"RAH-66 Comanche",
		"Ka-52 Alligator",
		"UH-60 Blackhawk",
		"Mi-24V Hind",
		"AH-64A Apache",
		"Ka-50 Black Shark"
	};

gunship_types alphabetical_gunship_types[] = {
		GUNSHIP_TYPE_AH64A,     // AH
		GUNSHIP_TYPE_APACHE,    // AH
	 	GUNSHIP_TYPE_KA50,      // Ka
		GUNSHIP_TYPE_HOKUM,     // Ka
		GUNSHIP_TYPE_HIND,      // Mi
		GUNSHIP_TYPE_HAVOC,     // Mi
		GUNSHIP_TYPE_COMANCHE,  // RAH
		GUNSHIP_TYPE_BLACKHAWK, // UH
 	};


// Casm 21DEC07
char psd_theme[128];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

global_options_data
	global_options;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef MAJOR_VERSION

static unsigned short
	// Jabberwock 040915 Minor version included in the number so it is recognized by MP server
	// version number is saved with only 16 bits. Use 2 bits for major version, and 7 each for data and minor version
	// assumes major version will never be more than 3, data and minor never more than 127
//	application_version_number = ( MAJOR_VERSION << 14 ) | (DATA_VERSION << 7) | MINOR_VERSION;

////041009 Moje Gives us trouble with saved games :( Original resotred.
	application_version_number = ( MAJOR_VERSION << 8 ) | DATA_VERSION;

#else

static int
	application_version_number = 0;

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////Moje 030519 Added ENTITY_SUB_TYPE_AIRCRAFT_UH60_BLACK_HAWK, below
////Moje 030612 Added ENTITY_SUB_TYPE_AIRCRAFT_MI24D_HIND, below
////Moje 030816 Added ENTITY_SUB_TYPE_AIRCRAFT_AH64A_APACHE, ENTITY_SUB_TYPE_AIRCRAFT_KA50_HOKUM,and below

entity_sub_types
	gunship_sub_types [] =
	{
		ENTITY_SUB_TYPE_AIRCRAFT_AH64D_APACHE_LONGBOW,
		ENTITY_SUB_TYPE_AIRCRAFT_MI28N_HAVOC_B,
		ENTITY_SUB_TYPE_AIRCRAFT_RAH66_COMANCHE,
		ENTITY_SUB_TYPE_AIRCRAFT_KA52_HOKUM_B,
		ENTITY_SUB_TYPE_AIRCRAFT_UH60_BLACK_HAWK,
		ENTITY_SUB_TYPE_AIRCRAFT_MI24D_HIND,
		ENTITY_SUB_TYPE_AIRCRAFT_AH64A_APACHE,
		ENTITY_SUB_TYPE_AIRCRAFT_KA50_HOKUM,
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////Moje 030521 added ENTITY_SIDE_BLUE_FORCE,last line below
////Moje 030612 added ENTITY_SIDE_RED_FORCE,last line below
////Moje 030816 added ENTITY_SIDE_BLUE_FORCE, and ENTITY_SIDE_RED_FORCE at the end below

entity_sides
	gunship_sides [] =
	{
		ENTITY_SIDE_BLUE_FORCE,
		ENTITY_SIDE_RED_FORCE,
		ENTITY_SIDE_BLUE_FORCE,
		ENTITY_SIDE_RED_FORCE,
		ENTITY_SIDE_BLUE_FORCE,
		ENTITY_SIDE_RED_FORCE,
		ENTITY_SIDE_BLUE_FORCE,
		ENTITY_SIDE_RED_FORCE,
	};

installed_custom_3d_models custom_3d_models;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void initialise_global_options_data_version2 (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_game_status (game_status_types status)
{

	game_status = status;

	game_status_string = game_status_names [status];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_global_options_data (void)
{
	set_global_version_number (application_version_number);

	set_global_gunship_type (GUNSHIP_TYPE_COMANCHE);

	set_global_dynamics_model (DEFAULT_DYNAMICS_MODEL);

	set_global_dynamics_options_cross_coupling (TRUE);
	set_global_dynamics_options_damage (TRUE);
	set_global_dynamics_options_over_torque (FALSE);
	set_global_dynamics_options_draw_flight_path (FALSE);
	set_global_dynamics_options_ground_collisions (TRUE);
	set_global_dynamics_options_ground_effect (TRUE);
	set_global_dynamics_options_keyboard_assistance (TRUE);
	set_global_dynamics_options_object_collisions (TRUE);
	set_global_dynamics_options_retreating_blade_stall (FALSE);
	set_global_dynamics_options_reverse_throttle_input (FALSE);
	set_global_dynamics_options_transitional_lift (TRUE);
	set_global_dynamics_options_vortex_ring (FALSE);
	set_global_dynamics_options_wind (FALSE);

	set_global_cyclic_input (KEYBOARD_INPUT);

	set_global_collective_input (KEYBOARD_INPUT);

	set_global_pedal_input (KEYBOARD_INPUT);

	set_global_hud_colour (HUD_COL_GREEN);

	set_global_hud_enlarge (FALSE);

	set_global_blurred_main_rotors_visible_from_cockpit (TRUE);

	set_global_display_external_view_name (TRUE);

	set_global_graphics_files_installed (FALSE);

	set_global_map (MAP1);

	set_global_joystick_device_index (-1);

	set_global_sound_effects_enabled (TRUE);

	set_global_speech_effects_enabled (TRUE);

	set_global_sound_music ( GAME_MUSIC_ON );

	set_global_graphics_rain_textures_enabled (TRUE);

	set_global_graphics_device_selection_automatic (TRUE);

	set_global_graphics_files_wrong_format (FALSE);

	set_global_comms_port ( 1 );

	set_global_baud_rate ( 1 );

	set_global_stop_bits ( 1 );

	set_global_parity ( 1 );

	set_global_flow ( 1 );

	sprintf ( global_options.ip_address, "" );

	sprintf ( global_options.phone_number, "" );

	set_global_cpg_assist_type (CPG_ASSIST_TYPE_EASY);

	set_global_display_hud_on_external_view (TRUE);

	//
	// Spare stuff at the end of the file
	//

	memset (global_options.spare, 0, sizeof (global_options.spare));

	//
	// Initialise the next version's global data
	//

	initialise_global_options_data_version2 ();

	custom_3d_models.arneh_ah64d_cockpit = FALSE;
	custom_3d_models.arneh_mi24v_cockpit = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_global_options_data_version2 (void)
{
	set_global_apache_havoc_installed (FALSE);

	set_global_auto_counter_measures (TRUE);

	set_global_ase_auto_page (TRUE);

	set_global_graphics_object_detail_level ( 3 );

	set_global_graphics_terrain_detail_level ( 3 );

	set_global_session_free_flight_time_of_day ( SESSION_TIME_RANDOM );
	set_global_session_campaign_time_of_day ( SESSION_TIME_RANDOM );

	set_global_session_free_flight_weather ( SESSION_WEATHER_RANDOM );
	set_global_session_campaign_weather ( SESSION_WEATHER_RANDOM );

	set_global_difficulty_level ( GAME_DIFFICULTY_EASY );

	set_global_session_free_flight_realism_infinite_fuel ( TRUE );
	#if DEMO_VERSION
	set_global_session_free_flight_realism_infinite_weapons ( FALSE );
	set_global_session_free_flight_realism_invulnerable_from_collisions ( FALSE );
	set_global_session_free_flight_realism_invulnerable_from_weapons ( FALSE );
	set_global_session_free_flight_realism_suppress_ai_fire ( FALSE );
	#else
	set_global_session_free_flight_realism_infinite_weapons ( TRUE );
	set_global_session_free_flight_realism_invulnerable_from_collisions ( TRUE );
	set_global_session_free_flight_realism_invulnerable_from_weapons ( TRUE );
	set_global_session_free_flight_realism_suppress_ai_fire ( TRUE );
	#endif

	set_global_session_campaign_realism_infinite_weapons ( FALSE );
	set_global_session_campaign_realism_infinite_fuel ( FALSE );
	set_global_session_campaign_realism_invulnerable_from_collisions ( FALSE );
	set_global_session_campaign_realism_invulnerable_from_weapons ( FALSE );
	set_global_session_campaign_realism_suppress_ai_fire ( FALSE );

	set_global_copilot_speech_effects_enabled ( TRUE );

	set_global_draw_cockpit_graphics (TRUE);

	set_global_draw_overlaid_instruments (TRUE);

	set_global_glass_cockpit (FALSE);

	set_global_cockpit_detail_level (COCKPIT_DETAIL_LEVEL_HIGH);

	set_global_simple_avionics (FALSE);

	set_global_display_in_flight_intelligence_messages (TRUE);

	set_global_unscaled_displays (FALSE);

	set_global_3d_visual_screen_width (640.0);

	set_global_3d_visual_screen_height (480.0);

	set_global_map_layer_options
	(
		(1 << MAP_LAYER_CONTROL_FOG_OF_WAR) +
		(1 << MAP_LAYER_CONTROL_KEYSITES) +
		(1 << MAP_LAYER_CONTROL_AIRCRAFT) +
		(1 << MAP_LAYER_CONTROL_SHIPS) +
		(1 << MAP_LAYER_CONTROL_ARMOUR)
	);

	set_global_sound_channel_volume (SOUND_CHANNEL_SOUND_EFFECT, 				10);
	set_global_sound_channel_volume (SOUND_CHANNEL_SYSTEM, 						9);
	set_global_sound_channel_volume (SOUND_CHANNEL_CO_PILOT, 					10);
	set_global_sound_channel_volume (SOUND_CHANNEL_WINGMAN, 						9);
	set_global_sound_channel_volume (SOUND_CHANNEL_AIR_TRAFFIC_CONTROLLER, 	5);
	set_global_sound_channel_volume (SOUND_CHANNEL_FORWARD_AIR_CONTROLLER, 	6);
	set_global_sound_channel_volume (SOUND_CHANNEL_GROUND_CONTROLLER, 		5);

	set_global_sound_channel_muted (SOUND_CHANNEL_SOUND_EFFECT, 				FALSE);
	set_global_sound_channel_muted (SOUND_CHANNEL_SYSTEM, 						FALSE);
	set_global_sound_channel_muted (SOUND_CHANNEL_CO_PILOT, 						FALSE);
	set_global_sound_channel_muted (SOUND_CHANNEL_WINGMAN, 						FALSE);
	set_global_sound_channel_muted (SOUND_CHANNEL_AIR_TRAFFIC_CONTROLLER, 	FALSE);
	set_global_sound_channel_muted (SOUND_CHANNEL_FORWARD_AIR_CONTROLLER, 	FALSE);
	set_global_sound_channel_muted (SOUND_CHANNEL_GROUND_CONTROLLER, 			FALSE);

	//
	// Graphics card ID & resolution stuff
	//

	memset ( &global_options.graphics_card_device_identifier, 0, sizeof ( GUID ) );

	global_options.number_of_graphics_card_resolutions = 0;

	memset ( &global_options.graphics_card_resolutions, 0, sizeof ( graphics_resolution_mode ) * 32 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_global_gunship_type (gunship_types type)
{
	ASSERT ((type >= 0) && (type <= NUM_GUNSHIP_TYPES));

	global_options.gunship_type = type;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_global_hud_colour (hud_colours colour)
{
	ASSERT ((colour >= 0) && (colour < NUM_HUD_COLOURS));

	global_options.hud_colour = colour;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_global_graphics_device_selection_guid ( GUID *guid )
{

	ASSERT ( guid );

	memcpy ( &global_options.graphics_device_guid, guid, sizeof ( GUID ) );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void save_global_options_data (void)
{

	FILE
		*file_ptr;

	if (!(file_ptr = fopen (global_options_filename, "wb")))
	{

		debug_fatal ("Global: Error saving global options data");
	}

	fwrite (&global_options, sizeof (global_options), 1, file_ptr);

  	fclose (file_ptr);

	add_file_to_uninstall_log ( global_options_filename );

	debug_colour_log ( DEBUG_COLOUR_DARK_RED, "SAVED GLOBAL OPTIONS" );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void load_global_options_data (void)
{

	FILE
		*file_ptr;

	int
		size;

	if (!file_exist (global_options_filename))
	{

		return;
	}

	if (!(file_ptr = fopen (global_options_filename, "rb")))
	{

		debug_fatal ("Global: Error loading global options data (file : %s)", global_options_filename);
	}

	//
	// We have to be able to read in previous version of the global options file.
	//

	size = file_size (global_options_filename);

	#ifdef DEBUG

	if (size != sizeof (global_options))
	{
		debug_fatal ("Global: Global options file has changed size (file : %s) - Please delete it", global_options_filename);
	}

	#endif

	if (size > sizeof (global_options))
	{

		debug_fatal ("Global: Global options file is oversized (file : %s) - Please delete it", global_options_filename);
	}

	fread (&global_options, size, 1, file_ptr);

  	fclose (file_ptr);

	//
	// Need to upgrade the version number ( possibly )
	//

	if ( ( get_global_version_number () != application_version_number ) || ( size != sizeof ( global_options ) ) )
	{

		debug_log ( "Upgrading application version number" );

		initialise_global_options_data_version2 ();
	}

	set_global_version_number (application_version_number);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
