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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int check_apache_havoc_ffp_files (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static memory_block_configuration
	memory_block_config[] =
	{
		////////////////////////////////////////
		//
		// GENERAL PURPOSE MEMORY BLOCKS
		//
		////////////////////////////////////////
		{
			4,											// block_size
			3500,										// number_of_blocks
		},
		{
			8,											// block_size
			500,										// number_of_blocks
		},
		{
			12,										// block_size
			1000,										// number_of_blocks
		},
		{
			16,										// block_size
			1000,										// number_of_blocks
		},
		{
			32,										// block_size
			100,										// number_of_blocks
		},
		{
			48,										// block_size
			500,										// number_of_blocks
		},
		{
			64,										// block_size
			100,										// number_of_blocks
		},
		{
			96,										// block_size
			100,										// number_of_blocks
		},
		{
			128,										// block_size
			100,										// number_of_blocks
		},
		{
			132,										// block_size
			1000,										// number_of_blocks
		},
		{
			192,										// block_size
			100,										// number_of_blocks
		},
		{
			256,										// block_size
			100,										// number_of_blocks
		},
		{
			384,										// block_size
			100,										// number_of_blocks
		},
		{
			512,										// block_size
			100,										// number_of_blocks
		},
		////////////////////////////////////////
		//
		// ENTITY SPECIFIC MEMORY BLOCKS
		//
		////////////////////////////////////////
		{
			sizeof (anti_aircraft),								// block_size
			1000,														// number_of_blocks
		},
		{
			sizeof (bridge),										// block_size
			1000,														// number_of_blocks
		},
		{
			sizeof (camera),										// block_size
			1,	 														// number_of_blocks
		},
		{
			sizeof (cargo),										// block_size
			5000,														// number_of_blocks
		},
		{
			sizeof (city),											// block_size
			14500,													// number_of_blocks
		},
		{
			sizeof (city_building),								// block_size
			55000,													// number_of_blocks
		},
		{
			sizeof (crater),										// block_size
			500,														// number_of_blocks
		},
		{
			sizeof (division),									// block_size
			300,														// number_of_blocks
		},
		{
			sizeof (explosion),									// block_size
			100,														// number_of_blocks
		},
		{
			sizeof (fixed_wing),									// block_size
			200,														// number_of_blocks
		},
		{
			sizeof (force),										// block_size
			2,	 														// number_of_blocks
		},
		{
			sizeof (group),										// block_size
			1000,														// number_of_blocks
		},
		{
			sizeof (guide),										// block_size
			400,														// number_of_blocks
		},
		{
			sizeof (helicopter),									// block_size
			400,														// number_of_blocks
		},
		{
			sizeof (keysite),										// block_size
			250,														// number_of_blocks
		},
		{
			sizeof (landing),										// block_size
			125,														// number_of_blocks
		},
		{
			sizeof (object),										// block_size
			100,														// number_of_blocks
		},
		{
			sizeof (particle),									// block_size
			100,														// number_of_blocks
		},
		{
			sizeof (person),										// block_size
			100,														// number_of_blocks
		},
		{
			sizeof (pilot),										// block_size
			16,														// number_of_blocks
		},
		{
			sizeof (pylon),										// block_size
			5500,														// number_of_blocks
		},
		{
			sizeof (regen),										// block_size
			100,														// number_of_blocks
		},
		{
			sizeof (routed_vehicle),							// block_size
			1000,														// number_of_blocks
		},
		{
			sizeof (scenic),										// block_size
			5500,														// number_of_blocks
		},
		{
			sizeof (sector),										// block_size
			9000,	  													// number_of_blocks
		},
		{
			sizeof (segment),										// block_size
			11500,													// number_of_blocks
		},
		{
			sizeof (session),										// block_size
			1,															// number_of_blocks
		},
		{
			sizeof (ship_vehicle),								// block_size
			100,		 												// number_of_blocks
		},
		{
			sizeof (site),		 									// block_size
			4250,		 												// number_of_blocks
		},
		{
			sizeof (site_updatable),							// block_size
			400,														// number_of_blocks
		},
		{
			sizeof (smoke_list),									// block_size
			2500,														// number_of_blocks
		},
		{
			sizeof (sound_effect),								// block_size
			4500,														// number_of_blocks
		},
		{
			sizeof (sprite),	 									// block_size
			100,														// number_of_blocks
		},
		{
			sizeof (task),											// block_size
			750,														// number_of_blocks
		},
		{
			sizeof (update),	 									// block_size
			1,		  													// number_of_blocks
		},
		{
			sizeof (waypoint),									// block_size
			3500,														// number_of_blocks
		},
		{
			sizeof (weapon),		 								// block_size
			250,														// number_of_blocks
		},
		//
		// for weapons systems
		//
		{
			SIZE_WEAPON_PACKAGE_STATUS_ARRAY,				// block_size
			2000,														// number_of_blocks
		},
		//
		// for smoke_lists
		//
		{
			8,															// block_size
			2500,														// number_of_blocks
		},
		{
			28,														// block_size
			2500,														// number_of_blocks
		},
		{
			84,														// block_size
			5000,														// number_of_blocks
		},
		{
			180,														// block_size
			2500,														// number_of_blocks
		},
		{
			396,														// block_size
			500,														// number_of_blocks
		},
		{
			492,														// block_size
			500,														// number_of_blocks
		},
		////////////////////////////////////////
		//
		// COMMS SPECIFIC MEMORY BLOCKS
		//
		////////////////////////////////////////
		{
			sizeof (stub_packet_type),							// block_size
			2000,														// number_of_blocks
		},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void brief_initialise_game (void)
{

	////////////////////////////////////////
	set_game_status (GAME_STATUS_UNINITIALISED);
	set_comms_model (COMMS_MODEL_SERVER);
	////////////////////////////////////////

	////////////////////////////////////////
	debug_watch ("Game status                                           =  %s", MT_STRING_PTR, &game_status_string);
	debug_watch ("Comms model                                           =  %s", MT_STRING_PTR, &comms_model_string);
	////////////////////////////////////////

	////////////////////////////////////////
	//
	// WARNING!     INITIALISATION ORDER IS CRITICAL
	//
	// NOTE :       MEMORY BLOCK SYSTEM CONSTRAINTS;
	//                      DO NOT USE REGISTER_EXIT_FUNCTION
	//                      FOR DEINITIALISATION.
	//
	////////////////////////////////////////

	////////////////////////////////////////
	//
	// INITIALISE GLOBAL OPTIONS
	//
	////////////////////////////////////////

	debug_log ( "Initialising memory system" );

	reset_safe_memory_counter ();

	reset_safe_memory_mapped_file_counter ();

	initialise_memory_block_system ();

	create_memory_block_configuration (memory_block_config, sizeof (memory_block_config) / sizeof (memory_block_configuration));

	////////////////////////////////////////
	//
	// INITIALISE GRAPHICS FILES
	//
	// NB. FIRST PASS CONVERSION ONLY
	//
	////////////////////////////////////////

	debug_log ( "Installing graphics files" );

	//
	// Check the graphics file format
	//

	{

		int
		red_mask,
		green_mask,
		blue_mask,
		alpha_mask;

		get_screen_pixel_format ( &red_mask, &green_mask, &blue_mask, &alpha_mask );

		if (	( red_mask != get_global_graphics_files_red_mask () ) ||
				( green_mask != get_global_graphics_files_green_mask () ) ||
				( blue_mask != get_global_graphics_files_blue_mask () ) ||
				( alpha_mask != get_global_graphics_files_alpha_mask () ) )
		{

			set_global_graphics_files_red_mask ( red_mask );

			set_global_graphics_files_green_mask ( green_mask );

			set_global_graphics_files_blue_mask ( blue_mask );

			set_global_graphics_files_alpha_mask ( alpha_mask );

			set_global_graphics_files_wrong_format ( TRUE );
		}
	}

	if ( (command_line_clean_graphics) || ( ( get_global_graphics_files_wrong_format () ) && ( !command_line_no_graphics_conversion ) ) )
	{

		uninstall_graphics_files ();
	}

	if ((!get_global_graphics_files_installed ()) || command_line_new_graphics)
	{
		while (!install_graphics_files (GRAPHICS_CONVERSION_FIRST_PASS));
	}

	debug_log ( "Opening graphics files" );

	mopen_all_graphics_files (GRAPHICS_CONVERSION_FIRST_PASS);

	//
	// Reset the graphics file format change flag now
	//

	set_global_graphics_files_wrong_format ( FALSE );

	debug_log ( "Installing event stack" );

	initialise_event_stack ();

	debug_log ( "Installing ui" );

	switch (command_line_run_mode)
	{
/*
		case RUN_MODE_AITOOL:
		{

			push_event (aitool_events, "aitool events");

			break;
		}
*/
		case RUN_MODE_NORMAL:
		default:
		{

			push_event (ui_events, "ui events");

			break;
		}
	}

	initialise_dinput_to_ascii_conversion_table ();

	debug_log ( "Initialising ui system" );

	initialise_ui_system (2000);

	debug_log ( "Initialising ui font" );

	//
	// Hack in to support all font resolutions
	//

	set_ui_font_resolution (get_global_3d_visual_screen_width (), get_global_3d_visual_screen_height ());
	initialise_ui_font ();

	set_ui_font_type (UI_FONT_ARIAL_18);

	debug_log ( "Initialising ui objects" );

	initialise_ui_objects ();

	debug_log ( "Initialising ui menus" );


	////////////////////////////////////////
	//
	// INITIALISE LANGUAGE DATABASE
	//
	////////////////////////////////////////

	initialise_language_database ();



	initialise_title_screen ();
	initialise_init_screen ();

	debug_log ( "Initialising ui mouseptr" );

	initialise_mouse_pointer ((rgb_packed *) get_graphics_file_data (GRAPHICS_UI_COMMON_MOUSE_POINTER));

	debug_log ( "Finished brief install" );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void full_initialise_game (void)
{

	unsigned char
		buffer [1024];

	////////////////////////////////////////
	//
	// WARNING!     INITIALISATION ORDER IS CRITICAL
	//
	// NOTE :       MEMORY BLOCK SYSTEM CONSTRAINTS;
	//                      DO NOT USE REGISTER_EXIT_FUNCTION
	//                      FOR DEINITIALISATION.
	//
	////////////////////////////////////////

	////////////////////////////////////////
	//
	// INITIALISE GRAPHICS FILES
	//
	////////////////////////////////////////

	{

		char
			buffer[256];

#if ( OEM_3DLABS_VERSION )
		sprintf ( buffer, "3DLabs Demonstration version" );
#else
		sprintf ( buffer, "%s: %d. %d. %d %s", get_trans ("Version"), MAJOR_VERSION, DATA_VERSION, MINOR_VERSION, BUILD_TYPE );
#endif

		set_ui_object_text (version_text, buffer);

//		add_to_pop_up_list ( buffer, init_screen_message_area, NULL, 0, UI_FONT_ARIAL_14, ui_colour_white );
	}

	if ( ( !get_global_graphics_files_installed () ) || command_line_new_graphics )
	{

		float
			file_count,
			percentage;

		int
			graphics_count_to_convert;

		char
			buffer [256];

		file_count = 0;

		graphics_count_to_convert = get_uninstalled_graphics_file_count ( GRAPHICS_CONVERSION_SECOND_PASS );

		if ( graphics_count_to_convert )
		{

			debug_log ( "First time graphics conversion" );

			sprintf (buffer, "%s...%s", get_trans ("Loading"), get_trans ("First Time Graphics Conversion"));

			set_ui_object_text (initialising_text, buffer);

			while (!install_graphics_files (GRAPHICS_CONVERSION_SECOND_PASS))
			{

				file_count ++;

				percentage = (file_count / graphics_count_to_convert) * 100.0;

				sprintf ( buffer, "%s...%s %.0f%%", get_trans ("Loading"), get_trans ("First Time Graphics Conversion"), percentage );

				set_ui_object_text (initialising_text, buffer);

				set_ui_object_redraw (init_screen, TRUE);

				ui_force_update ();
			}

			sprintf (buffer, "%s...%s", get_trans ("Loading"), get_trans ("First Time Graphics Conversion"));

			set_ui_object_text (initialising_text, buffer);
		}
	}

	save_global_options_data ();

	debug_log ( "Opening graphics files" );

	sprintf (buffer, "%s...%s", get_trans ("Loading"), get_trans ("Graphics"));

	set_ui_object_text (initialising_text, buffer);

	ui_force_update ();

	mopen_all_graphics_files (GRAPHICS_CONVERSION_SECOND_PASS);

	//
	// Check Apache Havoc FFP files exist
	//

	check_apache_havoc_ffp_files ();

	////////////////////////////////////////
	//
	// STATE IF APHAVOC INSTALLED
	//
	////////////////////////////////////////

	#if !DEMO_VERSION	
		if (get_global_apache_havoc_installed ())
		{
			char
				buffer [256];
	
			sprintf (buffer, "Apache Havoc: %s", get_trans ("MP_INSTALLED"));
	
			set_ui_object_text (ah_installed_text, buffer);
	
			process_ingame_text_object_size (ah_installed_text, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

			ui_force_update ();
		}
	#else
		set_global_apache_havoc_installed (FALSE);
	#endif

	////////////////////////////////////////
	//
	// INITIALISE MATHS LIBRARY
	//
	////////////////////////////////////////

	debug_log ( "Initialising maths library" );

	sprintf (buffer, "%s...%s", get_trans ("Loading"), get_trans ("Maths"));

	set_ui_object_text (initialising_text, buffer);

	ui_force_update ();

	initialise_maths_library ();

	////////////////////////////////////////
	//
	// INITIALISE CD PLAYER
	//
	////////////////////////////////////////

	debug_log ( "Initialising CD audio" );

	sprintf (buffer, "%s...%s", get_trans ("Loading"), get_trans ("CD Rom"));

	set_ui_object_text (initialising_text, buffer);

	ui_force_update ();

	capture_cd_audio_device ();

#ifdef COMMERCIAL
#if !DEMO_VERSION
#if ( LANGUAGE != LANGUAGE_SPANISH )
//	if ( !check_cd_for_80_minutes () )
//	{
//
//		debug_fatal ("Unable to find the Enemy Engaged RAH66 Comanche Vs KA52 Hokum CD\n\nPlease insert the CD and try again ...");
//	}
#endif
#endif
#endif

	////////////////////////////////////////
	//
	// INITIALISE JOYSTICK
	//
	////////////////////////////////////////

	debug_log ( "Initialising joysticks" );
	sprintf (buffer, "%s...%s", get_trans ("Loading"), get_trans ("Joystick"));

	set_ui_object_text (initialising_text, buffer);

	ui_force_update ();

	initialise_joysticks ();

	////////////////////////////////////////
	//
	// INITIALISE TRACKIR
	//	Retro 030317
	//	THIS IS NOT LOCALIZED YET !!
	//	(well.. doesn´t have to be)
	////////////////////////////////////////

	debug_log ( "Initialising trackIR" );
	sprintf (buffer, "%s...%s", get_trans ("Loading"), "TrackIR");

	set_ui_object_text (initialising_text, buffer);

	ui_force_update ();

	InitTrackIR ();

	////////////////////////////////////////
	//
	// INITIALISE UPDATE FUNCTIONS
	//
	////////////////////////////////////////

	debug_log ( "Initialising update function list" );

	sprintf (buffer, "%s...%s", get_trans ("Loading"), get_trans ("Update"));

	set_ui_object_text (initialising_text, buffer);

	ui_force_update ();

	initialise_update_function_list ();

	////////////////////////////////////////
	//
	// INITIALISE DIRECT PLAY
	//
	////////////////////////////////////////

	debug_log ( "Initialising direct play" );

	sprintf (buffer, "%s...%s", get_trans ("Loading"), get_trans ("Comms System"));

	set_ui_object_text (initialising_text, buffer);

	ui_force_update ();

	direct_play_initialise_system ();

	//
	// Register the application for any lobbies
	//

	direct_play_register_application ( "COMANCHE HOKUM", "cohokum.exe" );

	////////////////////////////////////////
	//
	// INITIALISE COMMS
	//
	////////////////////////////////////////

	//
	// DEPENDENCY: initialise_comms BEFORE initialise_entity_system
	//

	debug_log ( "Initialising comms manager" );

	sprintf (buffer, "%s...%s", get_trans ("Loading"), get_trans ("Comms System"));

	set_ui_object_text (initialising_text, buffer);

	ui_force_update ();

	initialise_comms_manager ();

	initialise_comms ();

	initialise_comms_debug ();

	////////////////////////////////////////
	//
	// INITIALISE 3D SYSTEM
	//
	////////////////////////////////////////

	debug_log ( "Initialising 3d system" );

	sprintf (buffer, "%s...%s", get_trans ("Loading"), get_trans ("3D System"));

	set_ui_object_text (initialising_text, buffer);

	ui_force_update ();

	initialise_application_3d_system ();

	initialise_terrain_database ();

	set_fpu_rounding_mode_zero ();

	////////////////////////////////////////
	//
	// INITIALISE FILE TAG SYSTEM
	//
	////////////////////////////////////////

	debug_log ( "Installing file tag system" );

	sprintf (buffer, "%s...%s", get_trans ("Loading"), get_trans ("Tag System"));

	set_ui_object_text (initialising_text, buffer);

	ui_force_update ();

	initialise_file_tag_system ();

	////////////////////////////////////////
	//
	// INITIALISE USER-INTERFACE
	//
	////////////////////////////////////////

	debug_log ( "Initialising ui menus" );

	sprintf (buffer, "%s...%s", get_trans ("Loading"), get_trans ("UI Manager"));

	set_ui_object_text (initialising_text, buffer);

	ui_force_update ();

	initialise_ui_menus ();

	////////////////////////////////////////
	//
	// INITIALISE ENTITY SYSTEM
	//
	////////////////////////////////////////

	debug_log ( "Initialising entity system" );

	sprintf (buffer, "%s...%s", get_trans ("Loading"), get_trans ("System Manager"));

	set_ui_object_text (initialising_text, buffer);

	ui_force_update ();

	initialise_entity_system (125000);

	////////////////////////////////////////
	//
	// INITIALISE AI SYSTEM
	//
	////////////////////////////////////////

	debug_log ( "Initialising ai system" );

	sprintf (buffer, "%s...%s", get_trans ("Loading"), get_trans ("AI System"));

	set_ui_object_text (initialising_text, buffer);

	ui_force_update ();

	initialise_ai_system ();

	////////////////////////////////////////
	//
	// INITIALISE USER DEFINED KEYS
	//
	////////////////////////////////////////

	debug_log ( "Initialising user defined events" );

	initialise_user_defined_events ();

	////////////////////////////////////////
	//
	// INITIALISE PLAYER LIST
	//
	////////////////////////////////////////

	debug_log ( "Initialising player list" );

	sprintf (buffer, "%s...%s", get_trans ("Loading"), get_trans ("Players"));

	set_ui_object_text (initialising_text, buffer);

	ui_force_update ();

	load_player_list ();

	////////////////////////////////////////
	//
	// INITIALISE MEDAL / PROMOTION NAME DATABASE
	//
	////////////////////////////////////////

	initialise_medal_and_promotion_names ();

	////////////////////////////////////////
	//
	// INITIALISE SOUND SYSTEM
	//
	////////////////////////////////////////

	debug_log ( "Initialising sound system" );

	sprintf (buffer, "%s...%s", get_trans ("Loading"), get_trans ("Sound System"));

	set_ui_object_text (initialising_text, buffer);

	ui_force_update ();

	initialise_application_sound_system ();

	initialise_game_initialisation_phases ();

	debug_log ( "Finished Full initialise" );
	set_ui_object_text ( initialising_text, get_trans ("Finished Initialisation") );

	ui_force_update ();

//VJ WUT mod 26-mar-03	

	////////////////////////////////////////
	//
	// Parse the WUT text file 
	//
	////////////////////////////////////////
    if (command_line_wut)
    {
	debug_log ( "reading WUT file %s",WUT_filename );

	sprintf (buffer, "%s...%s: %s", get_trans ("Loading"), get_trans ("WUT file"), WUT_filename);

	set_ui_object_text (initialising_text, buffer);

	ui_force_update ();

    	parse_WUT_file(WUT_filename);
    }

//	play_avi ( "wenesday.avi", 0 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int check_apache_havoc_ffp_files (void)
{

	int
		flag;

	if (get_global_apache_havoc_installed ())
	{
	
		flag = TRUE;
	
		if (!file_exist ("..\\common\\maps\\map1\\terrain\\terrain.ffp"))
		{
	
			flag = FALSE;
		}
	
		if (!file_exist ("..\\common\\maps\\map2\\terrain\\terrain.ffp"))
		{
	
			flag = FALSE;
		}
	
		if (!file_exist ("..\\common\\maps\\map3\\terrain\\terrain.ffp"))
		{
	
			flag = FALSE;
		}
	
		if (!flag)
		{
	
			set_global_apache_havoc_installed (FALSE);

			return FALSE;
		}
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

