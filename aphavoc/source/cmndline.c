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

static char
	*environment_variable = "ENVIRONMENT VARIABLE";

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	command_line_debug_input									= FALSE,
	command_line_debug_log_timing_info						= TRUE,
	command_line_dump_session									= FALSE,
	command_line_version_number								= IGNORE_COMMAND_LINE_VERSION_NUMBER,

	#ifdef DEBUG

	#if ( OEM_3DLABS_VERSION )

	command_line_full_screen									= TRUE,

	#else

	command_line_full_screen									= FALSE,

	#endif

	#else

	command_line_full_screen									= TRUE,

	#endif

	command_line_cdrom_drive_letter							= FALSE,
	command_line_entity_update_frame_rate					= 2.0,
	command_line_hardware_render								= FALSE,
	command_line_no_sound										= FALSE,
	command_line_clean_graphics								= FALSE,

	#ifdef DEBUG
	command_line_new_graphics									= FALSE,
	#else
	command_line_new_graphics									= TRUE,
	#endif

	command_line_max_time_acceleration						= 4,
	command_line_ai_use_route_generator						= TRUE,
	command_line_no_graphics_conversion						= FALSE,
	command_line_comms_show_stats								= FALSE,
	command_line_comms_packet_throttle_limit				= 10,
	command_line_comms_resend_list_size						= 1000,
	command_line_comms_packet_data_size						= 450,
	command_line_comms_packet_rerequest_limit				= 100,
	command_line_comms_connection_receive_size			= (200 * 1024),
	command_line_comms_data_record_size						= (200 * 1024),
	command_line_comms_timeout									= (5.0),
	command_line_comms_pack_buffer_size						= (200 * 1024),
	command_line_comms_initial_sleep_time					= 500,
	command_line_comms_guaranteed_send						= TRUE,
	command_line_comms_dedicated_server						= FALSE,
	command_line_comms_interpolate_gunships				= TRUE,
	command_line_comms_validate_connections				= FALSE,
	command_line_game_initialisation_phase_game_type	= GAME_TYPE_INVALID,
	command_line_game_initialisation_phase_gunship_type= NUM_GUNSHIP_TYPES,
	command_line_max_frame_rate								= 30,
	command_line_max_game_update_rate						= 15,
	command_line_max_game_update_rate_set					= FALSE,
	command_line_run_mode										= RUN_MODE_NORMAL,
	command_line_vector_flight_model							= FALSE,
	command_line_target_point_check							= FALSE,
	command_line_no_pilot_rejection							= FALSE,
	command_line_planner_goto_button							= FALSE,
	command_line_cheats_on										= FALSE,
	command_line_capture_aircraft								= FALSE,
	command_line_dynamics_sonic_buildup 					= TRUE,
	command_line_player_start_rank							= PILOT_RANK_LIEUTENANT,
	command_line_3d_visual_screen_width						= 640,
	command_line_3d_visual_screen_height					= 480,
	command_line_3d_visual_clear_edges						= FALSE,
	command_line_cpu_blit_textures							= FALSE,
	command_line_d3d_use_texture_management				= TRUE,
	command_line_no_hardware_tnl								= FALSE,
	command_line_no_render_to_texture						= FALSE,
	command_line_display_bpp									= 16,
	command_line_no_mission_complete_music					= FALSE,
	command_line_mouse_look										= FALSE,	// Retro 030317
	command_line_mouse_look_speed								= 15,		// Retro 030317
	command_line_min_fov											= 20,		// Retro 030318
	command_line_max_fov											= 80,		// Retro 030318
	command_line_eo_pan_joystick_index						= -1,		// loke 030319
	command_line_eo_pan_vertical_joystick_axis			= 6,		// loke 030319
	command_line_eo_pan_horizontal_joystick_axis			= 8,		// loke 030319
	command_line_eo_zoom_joystick_index						= -1,		// loke 030319
	command_line_eo_zoom_joystick_axis						= 7,		// loke 030319
	command_line_ground_radar_ignores_infantry			= 1,		// loke 030322
	command_line_ground_stabilisation_available			= 1,		// loke 030322
//VJ framerate 24-mar-03
    command_line_framerate 									= FALSE;

float
	command_line_dynamics_retreating_blade_stall_effect= 1.0,
	command_line_dynamics_rudder_value						= 1.0,
	command_line_dynamics_rudder_acceleration				= 0.8,
	command_line_dynamics_main_rotor_drag					= 1.0,
	command_line_dynamics_main_rotor_lift					= 1.0,
	command_line_dynamics_tail_rotor_drag					= 1.0,
	command_line_dynamics_cyclic_dead_zone					= 0.0,
	command_line_dynamics_yaw_altitude_loss 				= 5.0,
	command_line_aitool_grid_pitch 							= 0.0,
	command_line_comms_resend_timeout						= 2.0,
	command_line_comms_packet_resend_timer 				= 5.0,
	command_line_city_block_approximation_range 			= 500.0,
	command_line_user_invulnerable_time						= 5.0,
	command_line_object_lod_factor							= 1.0,
	command_line_fog_of_war_maximum_value 					= DEFAULT_FOG_OF_WAR_MAXIMUM_VALUE,
	command_line_chaff_effectiveness							= 1.0,
	command_line_flare_effectiveness							= 1.0,
	command_line_smoke_effectiveness							= 1.0;

char
	command_line_game_initialisation_phase_path [128]	= "\0",
	command_line_game_initialisation_phase_directory [128]	= "\0",
	command_line_game_initialisation_phase_filename [128]	= "\0",
	command_line_debug_log_name[100]							= "DEBUG.LOG",
	command_line_ip_address[128]								= "\0";

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static char *strarg (char *s, char *arg);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void process_command_line (int argc, char *argv[])
{
	char
		*s1,
		*s2;

	debug_log ("%s command line (argc = %d)", *argv, argc);

	//
	// skip program name in command line
	//

	argc--;
	argv++;

	while (argc--)
	{
		s1 = *argv++;

		////////////////////////////////////////
		if ((s2 = strarg (s1, "command_line_game_initialisation_phase_path")) || (s2 = strarg (s1, "path")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%s", &command_line_game_initialisation_phase_path);
			}
			else
			{
				strcpy (command_line_game_initialisation_phase_path, "/0");
			}

			if (strlen (command_line_game_initialisation_phase_path) == 0)
			{
				strcpy (command_line_game_initialisation_phase_path, "/0");
			}

			debug_log ("ARG:%s, RESPONSE:command_line_game_initialisation_phase_path = %s", s1, command_line_game_initialisation_phase_path);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "command_line_game_initialisation_phase_directory")) || (s2 = strarg (s1, "directory")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%s", &command_line_game_initialisation_phase_directory);
			}
			else
			{
				strcpy (command_line_game_initialisation_phase_directory, "/0");
			}

			if (strlen (command_line_game_initialisation_phase_directory) == 0)
			{
				strcpy (command_line_game_initialisation_phase_directory, "/0");
			}

			debug_log ("ARG:%s, RESPONSE:command_line_game_initialisation_phase_directory = %s", s1, command_line_game_initialisation_phase_directory);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "command_line_game_initialisation_phase_filename")) || (s2 = strarg (s1, "filename")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%s", &command_line_game_initialisation_phase_filename);
			}
			else
			{
				strcpy (command_line_game_initialisation_phase_filename, "/0");
			}

			if (strlen (command_line_game_initialisation_phase_filename) == 0)
			{
				strcpy (command_line_game_initialisation_phase_filename, "/0");
			}

			debug_log ("ARG:%s, RESPONSE:command_line_game_initialisation_phase_filename = %s", s1, command_line_game_initialisation_phase_filename);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "entity_update_frame_rate")) || (s2 = strarg (s1, "eufr")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_entity_update_frame_rate);
			}
			else
			{
				command_line_entity_update_frame_rate = 2.0;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_entity_update_frame_rate = %d", s1, command_line_entity_update_frame_rate);
		}
		////////////////////////////////////////
		else if (s2 = strarg (s1, "3dw"))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_3d_visual_screen_width);
			}
			else
			{
				command_line_3d_visual_screen_width = 640;
			}

			set_global_3d_visual_screen_width (command_line_3d_visual_screen_width);

			debug_log ("ARG:%s, RESPONSE:command_line_3d_visual_screen_width = %d", s1, command_line_3d_visual_screen_width);
		}
		////////////////////////////////////////
		else if (s2 = strarg (s1, "3dh"))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_3d_visual_screen_height);
			}
			else
			{
				command_line_3d_visual_screen_height = 480;
			}

			set_global_3d_visual_screen_height (command_line_3d_visual_screen_height);

			debug_log ("ARG:%s, RESPONSE:command_line_3d_visual_screen_height = %d", s1, command_line_3d_visual_screen_height);
		}
		////////////////////////////////////////
		else if (s2 = strarg (s1, "3dce"))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_3d_visual_clear_edges);
			}
			else
			{
				command_line_3d_visual_clear_edges = TRUE;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_3d_visual_clear_edges = %d", s1, command_line_3d_visual_clear_edges);
		}
		////////////////////////////////////////
		else if (s2 = strarg (s1, "cbt"))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_cpu_blit_textures);
			}
			else
			{
				command_line_cpu_blit_textures = TRUE;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_cpu_blit_textures = %d", s1, command_line_cpu_blit_textures);
		}
		////////////////////////////////////////
		else if (s2 = strarg (s1, "3dreset"))
		////////////////////////////////////////
		{
			set_global_3d_visual_screen_width (640.0);

			set_global_3d_visual_screen_height (480.0);

			debug_log ("ARG:%s", s1);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "version_number")) || (s2 = strarg (s1, "vn")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_version_number);
			}

			if (command_line_version_number != IGNORE_COMMAND_LINE_VERSION_NUMBER)
			{
				set_global_version_number (command_line_version_number);
			}

			debug_log ("ARG:%s, RESPONSE:command_line_version_number = %d", s1, command_line_version_number);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "dynamics_cyclic_dead_zone")) || (s2 = strarg (s1, "dcdz")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%f", &command_line_dynamics_cyclic_dead_zone);
			}
			else
			{
				command_line_dynamics_cyclic_dead_zone = 0.0;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_dynamics_cyclic_dead_zone = %f", s1, command_line_dynamics_cyclic_dead_zone);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "dynamics_yaw_altitude_loss")) || (s2 = strarg (s1, "dyal")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%f", &command_line_dynamics_yaw_altitude_loss);
			}
			else
			{
				command_line_dynamics_yaw_altitude_loss = 5.0;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_dynamics_yaw_altitude_loss = %f", s1, command_line_dynamics_yaw_altitude_loss);
		}

		////////////////////////////////////////
		else if ((s2 = strarg (s1, "aitool_grid_pitch")) || (s2 = strarg (s1, "agp")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%f", &command_line_aitool_grid_pitch);
			}
			else
			{
				command_line_aitool_grid_pitch = 0.0;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_aitool_grid_pitch = %f", s1, command_line_aitool_grid_pitch);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "comms_packet_timer")) || (s2 = strarg (s1, "cpt")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%f", &command_line_comms_packet_resend_timer);
			}
			else
			{
				command_line_comms_packet_resend_timer = 5.0;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_comms_packet_resend_timer = %f", s1, command_line_comms_packet_resend_timer);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "city_block_approximation_range")) || (s2 = strarg (s1, "cbar")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%f", &command_line_city_block_approximation_range);
			}
			else
			{
				command_line_city_block_approximation_range = 500.0;
			}

			debug_log ("ARG:%s, RESPONSE:= %f", s1, command_line_city_block_approximation_range);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "user_invulnerable_time")) || (s2 = strarg (s1, "uit")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%f", &command_line_user_invulnerable_time);
			}
			else
			{
				command_line_user_invulnerable_time = 5.0;
			}

			debug_log ("ARG:%s, RESPONSE:= %f", s1, command_line_user_invulnerable_time);
		}
		////////////////////////////////////////
		else if (s2 = strarg (s1, "chaff"))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%f", &command_line_chaff_effectiveness);

				command_line_chaff_effectiveness = bound (command_line_chaff_effectiveness, 0.0, 1.0);
			}
			else
			{
				command_line_chaff_effectiveness = 1.0;
			}

			debug_log ("ARG:%s, RESPONSE:= %f", s1, command_line_chaff_effectiveness);
		}
		////////////////////////////////////////
		else if (s2 = strarg (s1, "flare"))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%f", &command_line_flare_effectiveness);

				command_line_flare_effectiveness = bound (command_line_flare_effectiveness, 0.0, 1.0);
			}
			else
			{
				command_line_flare_effectiveness = 1.0;
			}

			debug_log ("ARG:%s, RESPONSE:= %f", s1, command_line_flare_effectiveness);
		}
		////////////////////////////////////////
		else if (s2 = strarg (s1, "smoke"))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%f", &command_line_smoke_effectiveness);

				command_line_smoke_effectiveness = bound (command_line_smoke_effectiveness, 0.0, 1.0);
			}
			else
			{
				command_line_smoke_effectiveness = 1.0;
			}

			debug_log ("ARG:%s, RESPONSE:= %f", s1, command_line_smoke_effectiveness);
		}
		////////////////////////////////////////
		else if (s2 = strarg (s1, "fog"))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%f", &command_line_fog_of_war_maximum_value);
			}
			else
			{
				command_line_fog_of_war_maximum_value = DEFAULT_FOG_OF_WAR_MAXIMUM_VALUE;
			}

			debug_log ("ARG:%s, RESPONSE:= %f", s1, command_line_fog_of_war_maximum_value);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "comms_show_stats")) || (s2 = strarg (s1, "css")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_comms_show_stats);
			}
			else
			{
				command_line_comms_show_stats = TRUE;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_comms_show_stats= %d", s1, command_line_comms_show_stats);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "comms_packet_throttle_limit")) || (s2 = strarg (s1, "cptl")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_comms_packet_throttle_limit);
			}
			else
			{
				command_line_comms_packet_throttle_limit = 10;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_comms_packet_throttle_limit= %d", s1, command_line_comms_packet_throttle_limit);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "comms_resend_list_size")) || (s2 = strarg (s1, "crls")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_comms_resend_list_size);
			}
			else
			{
				command_line_comms_resend_list_size = 1000;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_comms_resend_list_size = %d", s1, command_line_comms_resend_list_size);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "comms_packet_data_size")) || (s2 = strarg (s1, "cpds")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_comms_packet_data_size);
			}
			else
			{
				command_line_comms_packet_data_size = 512;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_comms_packet_data_size = %d", s1, command_line_comms_packet_data_size);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "comms_rerequest_limit")) || (s2 = strarg (s1, "crl")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_comms_packet_rerequest_limit);
			}
			else
			{
				command_line_comms_packet_rerequest_limit = 10;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_comms_packet_rerequest_limit = %d", s1, command_line_comms_packet_rerequest_limit);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "comms_connection_receive_size")) || (s2 = strarg (s1, "ccrs")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_comms_connection_receive_size);
			}
			else
			{
				command_line_comms_connection_receive_size = (200 * 1024);
			}

			debug_log ("ARG:%s, RESPONSE:command_line_comms_connection_receive_size = %d", s1, command_line_comms_connection_receive_size);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "comms_data_record_size")) || (s2 = strarg (s1, "cdrs")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_comms_data_record_size);
			}
			else
			{
				command_line_comms_data_record_size = (200 * 1024);
			}

			debug_log ("ARG:%s, RESPONSE:command_line_comms_data_record_size = %d", s1, command_line_comms_data_record_size);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "comms_timeout")) || (s2 = strarg (s1, "cto")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_comms_timeout);
			}
			else
			{
				command_line_comms_timeout = 5.0;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_comms_timeout = %d", s1, command_line_comms_timeout);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "comms_resend_timeout")) || (s2 = strarg (s1, "crto")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%f", &command_line_comms_resend_timeout);
			}
			else
			{
				command_line_comms_resend_timeout = (2.0);
			}

			debug_log ("ARG:%s, RESPONSE:command_line_comms_resend_timeout = %f", s1, command_line_comms_resend_timeout);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "comms_pack_buffer_size")) || (s2 = strarg (s1, "cpbs")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_comms_pack_buffer_size);
			}
			else
			{
				command_line_comms_pack_buffer_size = (200 * 1024);
			}

			debug_log ("ARG:%s, RESPONSE:command_line_comms_pack_buffer_size = %d", s1, command_line_comms_pack_buffer_size);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "command_line_comms_initial_sleep_time")) || (s2 = strarg (s1, "cist")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_comms_initial_sleep_time);
			}
			else
			{
				command_line_comms_initial_sleep_time = 500;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_comms_initial_sleep_time = %d", s1, command_line_comms_initial_sleep_time);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "command_line_comms_guaranteed_send")) || (s2 = strarg (s1, "cgs")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_comms_guaranteed_send);
			}
			else
			{
				command_line_comms_guaranteed_send = FALSE;
			}

			/////////////////////////////////////////////////////////////////
			if (command_line_comms_guaranteed_send)
			{

				direct_play_use_guaranteed_packets = TRUE;
			}
			else
			{

				direct_play_use_guaranteed_packets = FALSE;
			}
			/////////////////////////////////////////////////////////////////

			debug_log ("ARG:%s, RESPONSE:command_line_comms_guaranteed_send = %d", s1, command_line_comms_guaranteed_send);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "command_line_comms_dedicated_server")) || (s2 = strarg (s1, "dedicated")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_comms_dedicated_server);
			}
			else
			{
				command_line_comms_dedicated_server = FALSE;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_comms_dedicated_server = %d", s1, command_line_comms_dedicated_server);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "command_line_comms_interpolate_gunships")) || (s2 = strarg (s1, "cig")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_comms_interpolate_gunships);
			}
			else
			{
				command_line_comms_interpolate_gunships = TRUE;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_comms_interpolate_gunships= %d", s1, command_line_comms_interpolate_gunships);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "command_line_comms_validate_connections")) || (s2 = strarg (s1, "cvc")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_comms_validate_connections);
			}
			else
			{
				command_line_comms_validate_connections = TRUE;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_comms_validate_connections= %d", s1, command_line_comms_validate_connections);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "command_line_game_initialisation_phase_game_type")) || (s2 = strarg (s1, "game_type")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_game_initialisation_phase_game_type);
			}
			else
			{
				command_line_game_initialisation_phase_game_type = GAME_TYPE_INVALID;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_game_initialisation_phase_game_type = %d", s1, command_line_game_initialisation_phase_game_type);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "command_line_game_initialisation_phase_gunship_type")) || (s2 = strarg (s1, "gunship_type")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_game_initialisation_phase_gunship_type);
			}
			else
			{
				command_line_game_initialisation_phase_gunship_type = NUM_GUNSHIP_TYPES;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_game_initialisation_phase_gunship_type = %d", s1, command_line_game_initialisation_phase_gunship_type);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "max_frame_rate")) || (s2 = strarg (s1, "mfr")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_max_frame_rate);
			}
			else
			{
				command_line_max_frame_rate = 30;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_max_frame_rate = %d", s1, command_line_max_frame_rate);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "max_update_rate")) || (s2 = strarg (s1, "mur")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_max_game_update_rate);

				command_line_max_game_update_rate_set = TRUE;
			}
			else
			{
				command_line_max_game_update_rate = 15;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_max_game_update_rate = %d", s1, command_line_max_game_update_rate);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "run_mode")) || (s2 = strarg (s1, "rm")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_run_mode);
			}
			else
			{
				command_line_run_mode = RUN_MODE_NORMAL;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_run_mode = %d", s1, command_line_run_mode);
		}
		////////////////////////////////////////
		else if (s2 = strarg (s1, "cdrom"))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%c", &command_line_cdrom_drive_letter);
			}
			else
			{
				command_line_cdrom_drive_letter = 'Z';
			}

			debug_log ("ARG:%s, RESPONSE:command_line_cdrom_drive_letter = %c", s1, command_line_cdrom_drive_letter);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "new_graphics")) || (s2 = strarg (s1, "ng")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_new_graphics);
			}
			else
			{
				command_line_new_graphics = TRUE;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_new_graphics = %d", s1, command_line_new_graphics);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "clean_graphics")) || (s2 = strarg (s1, "cg")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_clean_graphics);
			}
			else
			{
				command_line_clean_graphics = TRUE;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_clean_graphics = %d", s1, command_line_clean_graphics);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "max_time_acceleration")) || (s2 = strarg (s1, "mta")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_max_time_acceleration);
			}
			else
			{
				command_line_max_time_acceleration = 4;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_max_time_acceleration= %d", s1, command_line_max_time_acceleration);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "ai_use_route_generator")) || (s2 = strarg (s1, "aurg")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_ai_use_route_generator);
			}
			else
			{
				command_line_ai_use_route_generator = TRUE;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_ai_use_route_generator = %d", s1, command_line_ai_use_route_generator);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "no_convert_graphics")) || (s2 = strarg (s1, "ncg")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_no_graphics_conversion);
			}
			else
			{
				command_line_no_graphics_conversion = TRUE;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_no_graphics_conversion = %d", s1, command_line_no_graphics_conversion);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "vector_flight_model")) || (s2 = strarg (s1, "vfm")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_vector_flight_model);
			}
			else
			{
				command_line_vector_flight_model = FALSE;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_vector_flight_model = %d", s1, command_line_vector_flight_model);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "target_point")) || (s2 = strarg (s1, "tp")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_target_point_check);
			}
			else
			{
				command_line_target_point_check = TRUE;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_target_point_check = %d", s1, command_line_target_point_check);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "no_pilot_rejection")) || (s2 = strarg (s1, "npr")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_no_pilot_rejection);
			}
			else
			{
				command_line_no_pilot_rejection = FALSE;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_no_pilot_rejection = %d", s1, command_line_no_pilot_rejection);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "planner_goto_button")) || (s2 = strarg (s1, "goto")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_planner_goto_button);
			}
			else
			{
				command_line_planner_goto_button = FALSE;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_planner_goto_button = %d", s1, command_line_planner_goto_button);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "cheats_on")) || (s2 = strarg (s1, "cheats")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_cheats_on);
			}
			else
			{
				command_line_cheats_on = FALSE;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_cheats_on = %d", s1, command_line_cheats_on);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "capture_aircraft")) || (s2 = strarg (s1, "cpac")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_capture_aircraft);
			}
			else
			{
				command_line_capture_aircraft = FALSE;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_capture_aircraft = %d", s1, command_line_capture_aircraft);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "dynamics_sonic_buildup")) || (s2 = strarg (s1, "dsb")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_dynamics_sonic_buildup);
			}
			else
			{

				command_line_dynamics_sonic_buildup = TRUE;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_dynamics_sonic_buildup = %d", s1, command_line_dynamics_sonic_buildup);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "player_start_rank")) || (s2 = strarg (s1, "psr")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_player_start_rank);
			}
			else
			{

				command_line_player_start_rank = PILOT_RANK_LIEUTENANT;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_player_start_rank = %d", s1, command_line_player_start_rank);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "command_line_dynamics_retreating_blade_stall_effect")) || (s2 = strarg (s1, "drbs")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%f", &command_line_dynamics_retreating_blade_stall_effect);
			}
			else
			{
				command_line_dynamics_retreating_blade_stall_effect = 1.0;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_dynamics_retreating_blade_stall_effect = %f", s1, command_line_dynamics_retreating_blade_stall_effect);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "dynamics_rudder_value")) || (s2 = strarg (s1, "drv")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%f", &command_line_dynamics_rudder_value);
			}
			else
			{
				command_line_dynamics_rudder_value = 1.0;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_dynamics_rudder_value = %f", s1, command_line_dynamics_rudder_value);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "dynamics_rudder_acceleration")) || (s2 = strarg (s1, "dra")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%f", &command_line_dynamics_rudder_acceleration);
			}
			else
			{
				command_line_dynamics_rudder_acceleration = 0.8;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_dynamics_rudder_acceleration = %f", s1, command_line_dynamics_rudder_acceleration);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "dynamics_rotor_drag")) || (s2 = strarg (s1, "drd")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%f", &command_line_dynamics_main_rotor_drag);
			}
			else
			{
				command_line_dynamics_main_rotor_drag = 1.0;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_dynamics_main_rotor_drag = %f", s1, command_line_dynamics_main_rotor_drag);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "dynamics_main_rotor_lift")) || (s2 = strarg (s1, "dmrl")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%f", &command_line_dynamics_main_rotor_lift);
			}
			else
			{
				command_line_dynamics_main_rotor_lift = 1.0;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_dynamics_main_rotor_lift = %f", s1, command_line_dynamics_main_rotor_lift);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "dynamics_tail_rotor_drag")) || (s2 = strarg (s1, "dtrd")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%f", &command_line_dynamics_tail_rotor_drag);
			}
			else
			{
				command_line_dynamics_tail_rotor_drag = 1.0;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_dynamics_tail_rotor_drag = %f", s1, command_line_dynamics_tail_rotor_drag);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "object_level_of_detail")) || (s2 = strarg (s1, "olod")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%f", &command_line_object_lod_factor);
			}
			else
			{
				command_line_object_lod_factor = 1.0;
			}

			debug_log ("ARG:%s, RESPONSE:= %f", s1, command_line_object_lod_factor);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "directx_texture_management")) || (s2 = strarg (s1, "dxtm")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_d3d_use_texture_management );
			}
			else
			{
				command_line_d3d_use_texture_management = TRUE;
			}

			debug_log ("ARG:%s, RESPONSE:= %f", s1, command_line_d3d_use_texture_management);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "debug_input")) || (s2 = strarg (s1, "di")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_debug_input);
			}
			else
			{
				command_line_debug_input = TRUE;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_debug_input = %d", s1, command_line_debug_input);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "debug_log_timing_info")) || (s2 = strarg (s1, "dt")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_debug_log_timing_info);
			}
			else
			{
				command_line_debug_log_timing_info = TRUE;
			}

			suppress_debug_log_timing_info (!command_line_debug_log_timing_info);

			debug_log ("ARG:%s, RESPONSE:command_line_debug_log_timing_info = %d", s1, command_line_debug_log_timing_info);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "debug_log")) || (s2 = strarg (s1, "dl")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%s", &command_line_debug_log_name);
			}
			else
			{
				strcpy (command_line_debug_log_name, "DEBUG.LOG");
			}

			if (strlen (command_line_debug_log_name) == 0)
			{
				strcpy (command_line_debug_log_name, "DEBUG.LOG");
			}

			debug_log ("ARG:%s, RESPONSE:command_line_debug_log_name = %s", s1, command_line_debug_log_name);

			rename_debug_log_file (command_line_debug_log_name);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "ip_address")) || (s2 = strarg (s1, "ipa")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%s", &command_line_ip_address);
			}
			else
			{
				strcpy (command_line_ip_address, "\0");
			}

			if (strlen (command_line_ip_address) == 0)
			{
				strcpy (command_line_ip_address, "\0");
			}

			debug_log ("ARG:%s, RESPONSE:command_line_ip_address = %s", s1, command_line_ip_address);

			strcpy (global_options.ip_address, command_line_ip_address);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "dump_session")) || (s2 = strarg (s1, "ds")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_dump_session);
			}
			else
			{
				command_line_dump_session = TRUE;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_dump_session = %d", s1, command_line_dump_session);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "full_screen")) || (s2 = strarg (s1, "fs")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_full_screen);
			}
			else
			{
				command_line_full_screen = TRUE;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_full_screen = %d", s1, command_line_full_screen);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "hardware_render")) || (s2 = strarg (s1, "hw")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_hardware_render);
			}
			else
			{
				command_line_hardware_render = TRUE;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_hardware_render = %d", s1, command_line_hardware_render);
		}
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "no_sound")) || (s2 = strarg (s1, "ns")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_no_sound);
			}
			else
			{
				command_line_no_sound = TRUE;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_no_sound = %d", s1, command_line_no_sound);
		}
		////////////////////////////////////////
		else if (s2 = strarg (s1, "notnl"))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_no_hardware_tnl);
			}
			else
			{
				command_line_no_hardware_tnl = TRUE;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_no_hardware_tnl = %d", s1, command_line_no_hardware_tnl);
		}
		////////////////////////////////////////
		else if (s2 = strarg (s1, "nrt"))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_no_render_to_texture);
			}
			else
			{
				command_line_no_render_to_texture = TRUE;
			}

			debug_log ("ARG:%s, RESPONSE:command_line_render_to_texture = %d", s1, command_line_no_render_to_texture);
		}
		////////////////////////////////////////
		else if (s2 = strarg (s1, "32bit"))
		////////////////////////////////////////
		{

			command_line_display_bpp = 32;

			debug_log ("ARG:%s, RESPONSE:command_line_render_to_texture = %d", s1, command_line_no_render_to_texture);
		}
		////////////////////////////////////////
		else if (s2 = strarg (s1, "nomcm"))
		////////////////////////////////////////
		{
			command_line_no_mission_complete_music = TRUE;

			debug_log ("ARG:%s, RESPONSE:command_line_no_mission_complete_music = %d", s1, command_line_no_mission_complete_music);
		}
		////////////////////////////////////////
		else if (s2 = strarg(s1, "mouselook"))	// all by Retro 030317
		////////////////////////////////////////
		{

			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_mouse_look);
			}
		}
		////////////////////////////////////////
		else if (s2 = strarg(s1, "mousespeed"))	// all by Retro 030317
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_mouse_look_speed);
			}
		}
		////////////////////////////////////////
		else if (s2 = strarg(s1, "minfov"))		//all by Retro 030318
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_min_fov);
			}

			if ((command_line_min_fov <= 10)||(command_line_min_fov >= 120))
				command_line_min_fov = 20;
		}
		////////////////////////////////////////
		else if (s2 = strarg(s1, "maxfov"))		//all by Retro 030318
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_max_fov);
			}
			
			if ((command_line_max_fov <= 10)||(command_line_max_fov >= 120))
				command_line_max_fov = 80;
		}
		////////////////////////////////////////
		else if (s2 = strarg(s1, "pan_joystick_index"))	// loke 030319
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_eo_pan_joystick_index);
			}

			if (command_line_eo_pan_joystick_index < -1)
			{
				command_line_eo_pan_joystick_index = -1;
			}
		}
		////////////////////////////////////////
		else if (s2 = strarg(s1, "pan_joystick_vertical_axis"))	// loke 030319
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_eo_pan_vertical_joystick_axis);
			}
		}
		////////////////////////////////////////
		else if (s2 = strarg(s1, "pan_joystick_horizontal_axis"))	// loke 030319
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_eo_pan_horizontal_joystick_axis);
			}
		}
		////////////////////////////////////////
		else if (s2 = strarg(s1, "zoom_joystick_index"))	// loke 030319
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_eo_zoom_joystick_index);
			}

			if (command_line_eo_zoom_joystick_index < -1)
			{
				command_line_eo_zoom_joystick_index = -1;
			}
		}
		////////////////////////////////////////
		else if (s2 = strarg(s1, "zoom_joystick_axis"))	// loke 030319
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_eo_zoom_joystick_axis);
			}
		}
		////////////////////////////////////////
		else if (s2 = strarg(s1, "invisible_infantry"))	// loke 030322
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_ground_radar_ignores_infantry);
			}
		}
		////////////////////////////////////////
		else if (s2 = strarg(s1, "enable_ground_stabilisation"))	// loke 030322
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_ground_stabilisation_available);
			}
		}
//VJ framerate 24-mar-03
		////////////////////////////////////////
		else if ((s2 = strarg (s1, "framerate")))
		////////////////////////////////////////
		{
			if (*s2 == ':')
			{
				sscanf (s2 + 1, "%d", &command_line_framerate);
			}
			else
			{
				command_line_framerate = FALSE;
			}
		}
//VJ WUT mod 26-mar-03 
		//////////////////////////////////////// 
		else if (s2 = strarg (s1, "wut")) 
		//////////////////////////////////////// 
		{ 
			if (*s2 == ':') 
			{ 
				sscanf (s2 + 1, "%s", WUT_filename); 
			} 
			else 
			{ 
                WUT_filename[0] = '\0'; 
			} 
		}
		////////////////////////////////////////
		else
		////////////////////////////////////////
		{
			debug_log ("ARG:%s, RESPONSE:not recognized", s1);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void process_environment_variable (char *name)
{
	int
		argc;

	char
		*argv[128],
		*env,
		*buffer,
		*ptr;

	if (name)
	{
		env = getenv (name);

		if (env)
		{
			//
			// copy enviroment variable
			//

			buffer = safe_malloc (strlen (env) + 1);

			strcpy (buffer, env);

			ptr = buffer;

			//
			// create standard argc and argv parameters
			//

			argc = 0;

			argv[argc++] = environment_variable;
			argv[argc++] = ptr;

			while (*ptr)
			{
				//
				// skip white space
				//

				while (*ptr)
				{
					if (*ptr == ' ')
					{
						ptr++;
					}
					else
					{
						break;
					}
				}

				if (*ptr)
				{
					argv[argc++] = ptr;

					//
					// skip argument
					//

					while (*ptr)
					{
						if (!(*ptr == ' '))
						{
							ptr++;
						}
						else
						{
							break;
						}
					}

					if (*ptr)
					{
						*ptr++ = 0;
					}
				}
			}

			process_command_line (argc, argv);

			safe_free (buffer);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// search string s for argument arg, if found, skip over arg
//

char *strarg (char *s, char *arg)
{
	char
		*ptr;

	int
		length;

	ptr = NULL;

	if (arg)
	{
		if ((*s == '-') || (*s == '/'))
		{
			s++;
		}

		length = strlen (arg);

		if (length > 0)
		{
			if (strnicmp (s, arg, length) == 0)
			{
				ptr = s + length;
			}
		}
	}

	return (ptr);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
