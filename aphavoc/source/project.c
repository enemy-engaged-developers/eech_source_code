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

#define INTERNAL_MODULES 1

#include "project.h"

// crh 030408 new single global version header
#include "version.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	cdrom_drive_letter = 0;

////////////////////////////////////////
//
// ALWAYS USE get_global_apache_havoc_installed () to test if Apache Havoc is installed (outside of this module)
//
////////////////////////////////////////

int
	apache_havoc_installation_path_valid;

char
	apache_havoc_installation_path[1024];

// JB 030311 Enable running out of separate directories
char
	comanche_hokum_installation_path[1024];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// JB 030311
static void set_comanche_hokum_installation_path ( void );
static void set_apache_havoc_installation_path ( void );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void application_main (int argc, char **argv)
{
	//
	// Initialise the global options data
	//

	debug_log ( "Initialising global options data" );

	initialise_global_options_data ();

	debug_log ( "Loading global options data" );

	load_global_options_data ();

	//
	// Initialise language
	//

	set_registry_language_settings ();

	//
	// process eech.ini file, call before commandline
	//
	//vj 030409, changed to generate eech.ini when it doesn't exist
    process_ini_file(argc, argv);

	//
	// process command line
	//

	process_environment_variable (ENV_NAME);

	process_command_line (argc, argv);


	//
	// setup the debug system
	//

	debug_fatal_warning_tone = FALSE;

	if (command_line_full_screen)
	{

		debug_set_window_creation (DEBUG_CREATE_NOWINDOW);

		debug_set_windows_update (DEBUG_UPDATE_MANUAL);

		initialise_debug_system (TRUE);
	}
	else
	{

		debug_set_window_creation (DEBUG_CREATE_WINDOW);

		debug_set_windows_update (DEBUG_UPDATE_AUTO);

		initialise_debug_system (TRUE);
	}

	//
	// version number
	//

	debug_colour_log (DEBUG_COLOUR_AMBER, "Version number = %02d.%02d", get_global_version_number () >> 8, get_global_version_number () & 0xff);

	// JB 030311
	set_comanche_hokum_installation_path();

	//
	// detect Apache Havoc
	//

	set_apache_havoc_installation_path ();

	if (apache_havoc_installation_path_valid)
	{
		set_global_apache_havoc_installed (TRUE);

		debug_colour_log (DEBUG_COLOUR_AMBER, "Apache Havoc installation path: %s", apache_havoc_installation_path);
	}
	else
	{
		set_global_apache_havoc_installed (FALSE);

		debug_colour_log (DEBUG_COLOUR_AMBER, "Apache Havoc is NOT installed");
	}

	//
	// CD-ROM drive letter
	//

	#ifdef INSTALL_FROM_CDROM

	if (command_line_comms_dedicated_server)
	{

		cdrom_drive_letter = 'Z';
	}
	else if (command_line_cdrom_drive_letter)
	{

		cdrom_drive_letter = command_line_cdrom_drive_letter;
	}
	else
	{
		cdrom_drive_letter = check_cdrom_file_exists ("COHOKUM\\COHOKUM.EXE");

		if (!cdrom_drive_letter)
		{
			if (get_global_current_language () == LANGUAGE_SPANISH)
			{
				debug_fatal ("No se pudo acceder al CD de Enemy Engaged RAH66 Comanche Vs KA-52 Hokum\n\nPor favor, introduce el CD...");
			}
			else
			{
				debug_fatal ("Unable to find the Enemy Engaged RAH66 Comanche Vs KA52 Hokum CD\n\nPlease insert the CD and try again ...");
			}
		}
	}

	#else

	cdrom_drive_letter = 'Z';

	#endif

	//
	// setup input system
	//

	if (command_line_debug_input)
	{
		initialise_input_system (INPUT_WINDOWS);
	}
	else
	{
		initialise_input_system (INPUT_DIRECTINPUT);
	}

	//
	// setup the graphics system
	//

	if ( command_line_no_hardware_tnl )
	{

		d3d_use_dx_pipeline = FALSE;
	}
	else
	{

		d3d_use_dx_pipeline = TRUE;
	}

	full_screen_colourdepth = command_line_display_bpp;

	debug_log ("Set colour depth to %d", full_screen_colourdepth );

	d3d_override_render_to_texture = command_line_no_render_to_texture;

	set_ddraw_use_double_buffering ( TRUE );
	set_ddraw_use_software_driver ( FALSE );
	set_ddraw_use_system_memory ( FALSE );
	set_ddraw_use_z_buffer ( TRUE );
	set_ddraw_use_full_screen ( command_line_full_screen );

	{

		int
			graphics_initialised;

		if ( !get_global_graphics_device_selection_automatic () )
		{

			if ( get_global_graphics_device_selection_primary () )
			{

				set_ddraw_use_software_driver ( TRUE );

				graphics_initialised = initialise_graphics_system ( NULL );
			}
			else
			{

				graphics_initialised = initialise_graphics_system ( &global_options.graphics_device_guid );
			}
		}
		else
		{

			graphics_initialised = initialise_graphics_system ( NULL );
		}

		if ( !graphics_initialised )
		{

			switch ( direct_draw_initialisation_error )
			{

				case DDRAW_INIT_UNABLE_TO_ENUMERATE:
				{

					debug_fatal ( "Unable to look for video card.\n\nPlease ensure you have the latest drivers\nfor your 3d card and have installed\nDirectX 6" );

					break;
				}

				case DDRAW_INIT_UNABLE_TO_CREATE_DDRAW:
				{

					debug_fatal ( "Unable to access video card.\n\nPlease ensure you have the latest drivers\nfor your 3d card and have installed\nDirectX 6" );

					break;
				}

				case DDRAW_INIT_UNABLE_TO_CREATE_DDRAW4:
				{

					debug_fatal ( "Unable to access DirectX6 drivers.\n\nPlease ensure you have the latest drivers\nfor your 3d card and have installed\nDirectX 6" );

					break;
				}

				case DDRAW_INIT_UNABLE_TO_ENUMERATE_DISPLAY_MODES:
				{

					debug_fatal ( "Unable to access DirectX6 drivers.\n\nPlease ensure you have the latest drivers\nfor your 3d card and have installed\nDirectX 6" );

					break;
				}

				case DDRAW_INIT_NO_3D_CARD:
				{

					debug_fatal ( "Unable to find a 3D graphics card.\n\nPlease ensure you have the latest drivers\nfor your 3d card and have installed\nDirectX 6" );

					break;
				}

				case DDRAW_INIT_OK:
				default:
				{

					debug_fatal ( "Unable to initialise a 3d video card.\n\nPlease ensure you have the latest drivers\nfor your 3d card and have installed\nDirectX 6" );

					break;
				}
			}
		}
	}

	//
	// Check the display resolutions
	//

	if ( command_line_full_screen )
	{

		GUID
			this_graphics_device;

		int
			index;

		//
		// If the last video card was different to the current one, re-assess the resolutions
		//

		get_ddraw_device_guid ( &this_graphics_device );

		if ( memcmp ( &this_graphics_device, &global_options.graphics_card_device_identifier, sizeof ( GUID ) ) != 0 )
		{

			if ( assess_graphic_device_resolutions () )
			{

				//
				// Save the GUID for next time
				//

				memcpy ( &global_options.graphics_card_device_identifier, &this_graphics_device, sizeof ( GUID ) );

				//
				// We've got at least one resolution to run at - store resolutions available in global_options
				//

				if ( number_of_graphics_resolution_modes_available > 32 )
				{

					number_of_graphics_resolution_modes_available = 32;
				}

				global_options.number_of_graphics_card_resolutions = number_of_graphics_resolution_modes_available;

				for ( index = 0; index < number_of_graphics_resolution_modes_available; index++ )
				{

					global_options.graphics_card_resolutions[index] = graphics_resolution_modes_available[index];
				}
			}
			else
			{

				//
				// We can't run at all. No memory even for 640x480 with compressed textures.
				//

				debug_fatal ( "Unable to allocate enough video memory.\n\nPlease ensure you have at least 4Mb of memory on your video card\nand you have the latest drivers installed\n" );
			}
		}
		else
		{

			//
			// Hardwire the available resolutions in
			//

			number_of_graphics_resolution_modes_available = global_options.number_of_graphics_card_resolutions;

			for ( index = 0; index < number_of_graphics_resolution_modes_available; index++ )
			{

				graphics_resolution_modes_available[index] = global_options.graphics_card_resolutions[index];

				debug_log ( "Enabling mode: %d x %d", graphics_resolution_modes_available[index].width, graphics_resolution_modes_available[index].height );
			}			
			
		}
	}
	else
	{

		//
		// These are the supported screen resolutions for windowed mode, where we can't query DirectX for supported screen dimensions
		//

		number_of_graphics_resolution_modes_available = 11;

		graphics_resolution_modes_available[0].width = 640;
		graphics_resolution_modes_available[0].height = 480;
		graphics_resolution_modes_available[0].compressed_texture_mode = FALSE;

		graphics_resolution_modes_available[1].width = 800;
		graphics_resolution_modes_available[1].height = 600;
		graphics_resolution_modes_available[1].compressed_texture_mode = FALSE;

		graphics_resolution_modes_available[2].width = 1024;
		graphics_resolution_modes_available[2].height = 768;
		graphics_resolution_modes_available[2].compressed_texture_mode = FALSE;

		graphics_resolution_modes_available[3].width = 1280; //Werewolf
		graphics_resolution_modes_available[3].height = 800;
		graphics_resolution_modes_available[3].compressed_texture_mode = FALSE;

		graphics_resolution_modes_available[4].width = 1280;
		graphics_resolution_modes_available[4].height = 960;
		graphics_resolution_modes_available[4].compressed_texture_mode = FALSE;

		graphics_resolution_modes_available[5].width = 1280; //Werewolf
		graphics_resolution_modes_available[5].height = 1024;
		graphics_resolution_modes_available[5].compressed_texture_mode = FALSE;

		graphics_resolution_modes_available[6].width = 1680; //Werewolf
		graphics_resolution_modes_available[6].height = 900;
		graphics_resolution_modes_available[6].compressed_texture_mode = FALSE;

		graphics_resolution_modes_available[7].width = 1680; //Werewolf
		graphics_resolution_modes_available[7].height = 1050;
		graphics_resolution_modes_available[7].compressed_texture_mode = FALSE;

		graphics_resolution_modes_available[8].width = 1600;
		graphics_resolution_modes_available[8].height = 1200;
		graphics_resolution_modes_available[8].compressed_texture_mode = FALSE;

		graphics_resolution_modes_available[9].width = 1920;
		graphics_resolution_modes_available[9].height = 1200;
		graphics_resolution_modes_available[9].compressed_texture_mode = FALSE;

		graphics_resolution_modes_available[10].width = 2048;
		graphics_resolution_modes_available[10].height = 1536;
		graphics_resolution_modes_available[10].compressed_texture_mode = FALSE;
	}

	//
	// setup the graphics display resolution
	//

	if (command_line_full_screen)
	{

		int
			index;

		index = get_graphics_resolution_index ( get_global_3d_visual_screen_width (), get_global_3d_visual_screen_height () );

		if ( index != -1 )
		{

			ddraw_set_display_resolution (get_global_3d_visual_screen_width (), get_global_3d_visual_screen_height (), full_screen_colourdepth, DISPLAY_FULLSCREEN );
		}
		else
		{

			set_global_3d_visual_screen_width ( 640 );

			set_global_3d_visual_screen_height ( 480 );

			ddraw_set_display_resolution ( get_global_3d_visual_screen_width (), get_global_3d_visual_screen_height (), full_screen_colourdepth, DISPLAY_FULLSCREEN );
		}
	}
	else
	{
		ddraw_set_display_resolution ( get_global_3d_visual_screen_width (), get_global_3d_visual_screen_height (), full_screen_colourdepth, DISPLAY_WINDOW );
	}

	//
	// initialise the graphics rendering routines for this resolution
	//

	initialise_graphics_rendering_system ();

	set_active_screen (video_screen);

	clear_screen ();

	ddraw_flip_surface ();

	//
	// Test the avis
	//

//	play_avi ( "downgattling.avi", 0 );

	//
	// begin application
	//

	game ();

	//VJ 030511 save automatically when leaving game to save all player choices in eech.ini
	dump_ini_file();

	//
	// end application
	//

	end_application ();
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// JB 030311
void set_comanche_hokum_installation_path(void)
{
	HKEY comanche_hokum_key;

	// JB 030311 Enable running out of separate directories
	if ( RegOpenKey ( HKEY_LOCAL_MACHINE, "Software\\Razorworks\\Comanche Hokum", &comanche_hokum_key ) == ERROR_SUCCESS )
	{
		DWORD type;
		long string_length;

		string_length = sizeof ( comanche_hokum_installation_path );

		type = REG_SZ;

		RegQueryValueEx ( comanche_hokum_key, "Installation Path", NULL, &type, ( LPBYTE ) comanche_hokum_installation_path, ( LPDWORD ) &string_length );
	}
	else if (!GetCurrentDirectory(sizeof(comanche_hokum_installation_path) - 1, comanche_hokum_installation_path))
		comanche_hokum_installation_path[0] = '\0';

	RegCloseKey ( comanche_hokum_key );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void set_apache_havoc_installation_path ( void )
{

	HKEY
		software_key,
		razorworks_key,
		apache_havoc_key;

	apache_havoc_installation_path_valid = FALSE;

	if ( RegOpenKey ( HKEY_LOCAL_MACHINE, "Software", &software_key ) == ERROR_SUCCESS )
	{

		if ( RegOpenKey ( software_key, "Razorworks", &razorworks_key ) == ERROR_SUCCESS )
		{

			if ( RegOpenKey ( razorworks_key, "Apache Havoc", &apache_havoc_key ) == ERROR_SUCCESS )
			{

				DWORD
					type;

				long
					string_length;

				string_length = sizeof ( apache_havoc_installation_path );

				type = REG_SZ;

				if ( RegQueryValueEx ( apache_havoc_key, "Installation Path", NULL, &type, ( LPBYTE ) apache_havoc_installation_path, ( LPDWORD ) &string_length ) == ERROR_SUCCESS )
				{

					apache_havoc_installation_path_valid = TRUE;
				}

				RegCloseKey ( apache_havoc_key );
			}

			RegCloseKey ( razorworks_key );
		}

		RegCloseKey ( software_key );
	}

	if (!apache_havoc_installation_path_valid)  // check if we have aphavoc directory anyway
	{
		char aphavoc_path[2048], aphavoc_file[2048];
		
		snprintf(aphavoc_path, sizeof(aphavoc_path)-1, "%s\\..", comanche_hokum_installation_path);
		snprintf(aphavoc_file, sizeof(aphavoc_file)-1, "%s\\aphavoc\\aphavoc.exe", aphavoc_path);

		if (file_exist(aphavoc_file))
		{
			strncpy(apache_havoc_installation_path, aphavoc_path, sizeof(apache_havoc_installation_path)-1);
			apache_havoc_installation_path_valid = TRUE;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_registry_language_settings ( void )
{

	HKEY
		software_key,
		razorworks_key,
		comanche_hokum_key;

	char
		language_string[512];

	set_global_current_language ( LANGUAGE_ENGLISH );

	if ( RegOpenKey ( HKEY_LOCAL_MACHINE, "Software", &software_key ) == ERROR_SUCCESS )
	{

		if ( RegOpenKey ( software_key, "Razorworks", &razorworks_key ) == ERROR_SUCCESS )
		{

			if ( RegOpenKey ( razorworks_key, "Comanche Hokum", &comanche_hokum_key ) == ERROR_SUCCESS )
			{

				DWORD
					type;

				long
					string_length;

				string_length = sizeof ( language_string );

				type = REG_SZ;

				if ( RegQueryValueEx ( comanche_hokum_key, "LANGUAGE", NULL, &type, ( LPBYTE ) &language_string, ( LPDWORD ) &string_length ) == ERROR_SUCCESS )
				{

					if ( stricmp ( language_string, "FRENCH" ) == 0 )			{ set_global_current_language ( LANGUAGE_FRENCH ); }
					else if ( stricmp ( language_string, "GERMAN" ) == 0 )	{ set_global_current_language ( LANGUAGE_GERMAN ); }
					else if ( stricmp ( language_string, "ITALIAN" ) == 0 )	{ set_global_current_language ( LANGUAGE_ITALIAN ); }
					else if ( stricmp ( language_string, "SPANISH" ) == 0 )	{ set_global_current_language ( LANGUAGE_SPANISH ); }
					else if ( stricmp ( language_string, "RUSSIAN" ) == 0 )	{ set_global_current_language ( LANGUAGE_RUSSIAN ); }
					else if ( stricmp ( language_string, "POLISH" ) == 0 )	{ set_global_current_language ( LANGUAGE_POLISH ); }
				}

				RegCloseKey ( comanche_hokum_key );
			}

			RegCloseKey ( razorworks_key );
		}

		RegCloseKey ( software_key );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
