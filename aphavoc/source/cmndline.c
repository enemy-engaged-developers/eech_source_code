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
#include "ai/highlevl/highlevl.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static char
	environment_variable[] = "ENVIRONMENT VARIABLE";

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	command_line_dynamics_advanced_engine_model			= TRUE,  //Werewolf 5 Feb 06
	command_line_dynamics_flight_model					= 0,
	command_line_dynamics_engine_startup                = FALSE,  // arneh - july 06
	command_line_report_to_masterserver						= FALSE,  //Werewolf 2 Jan 04 (arneh changed default to off - jan 2007)
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
	command_line_sound_hdwrbuf									= 0,
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
	command_line_comms_packet_data_size						= 512,                  // Moje 040507 changed back to RW default
	command_line_comms_packet_rerequest_limit				= 10,
	command_line_comms_connection_receive_size			= (210 * 1024),
	command_line_comms_data_record_size						= (210 * 1024),
	command_line_comms_timeout									= (15.0),
	command_line_comms_pack_buffer_size						= (210 * 1024),
	command_line_comms_initial_sleep_time					= 500,
	command_line_comms_guaranteed_send						= TRUE,
	command_line_comms_dedicated_server						= FALSE,
	command_line_comms_interpolate_gunships				= TRUE,
	command_line_comms_validate_connections				= TRUE, // Jabberwock - We need validate_connections...
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
	command_line_capture_aircraft								= TRUE,  ////Moje 040304 customizing a bit..
	command_line_dynamics_sonic_buildup 					= TRUE,
	command_line_player_start_rank							= PILOT_RANK_LIEUTENANT,
	command_line_3d_visual_screen_width						= 640,
	command_line_3d_visual_screen_height					= 480,
	command_line_3d_reset									= FALSE,
	command_line_force_resolution							= FALSE,
	command_line_3d_visual_clear_edges						= FALSE,
	command_line_cpu_blit_textures							= FALSE,
	command_line_d3d_use_texture_management				= FALSE, //VJ 030511 changed to FALSE, was TRUE,
	command_line_no_hardware_tnl								= FALSE,
	command_line_no_dx9zbuffer_fix							= FALSE,
	command_line_no_render_to_texture						= FALSE,
	command_line_display_bpp									= 32, // Casm 03MAR10 32 bits by default
	command_line_persistent_smoke								= TRUE,
	command_line_cloud_puffs								= 1, // Casm 20MAY2012
	command_line_no_mission_complete_music					= FALSE,
	command_line_mouse_look										= MOUSELOOK_OFF,	// Retro 030317, 27Nov2004
	command_line_mouse_look_speed								= 15,		// Retro 030317
	command_line_min_fov											= 20,		// Retro 030318
	command_line_max_fov0											= 80,		// Retro 030318
	command_line_max_fov1											= 80,		// Casm 08OCT05
	command_line_max_fov2											= 80,		// Casm 08OCT05
	command_line_max_fov3											= 80,		// Casm 08OCT05
	command_line_max_fov4											= 80,		// Casm 09JUN09
	command_line_max_fov5											= 80,		// Casm 25JAN12
	command_line_max_fov6											= 80,		// Casm 14JUL10
	command_line_max_fov7											= 80,		// Casm 30MAY12
	command_line_eo_pan_joystick_index						= -1,		// loke 030319
	command_line_eo_pan_vertical_joystick_axis			= 6,		// loke 030319
	command_line_eo_pan_horizontal_joystick_axis			= 8,		// loke 030319
	command_line_eo_zoom_joystick_index						= -1,		// loke 030319
	command_line_eo_zoom_joystick_axis						= 7,		// loke 030319
	command_line_field_of_view_joystick_index               = -1,
	command_line_field_of_view_joystick_axis                = 4,
	command_line_ground_radar_ignores_infantry			= 1,		// loke 030322
	command_line_ground_stabilisation_available			= 1,		// loke 030322
	command_line_manual_laser_radar						= FALSE,	// arneh 2006-11-06
	command_line_targeting_system_auto_page				= TRUE,     // arneh 2007-01-06
	command_line_framerate										= FALSE,	// VJ 030326
//Retro27NovDEAD	command_line_key_mapping									= FALSE,	// Retro 030322
	command_line_downwash										= FALSE,	//VJ 050308 changed to false for MP, // Xhit 030328, VJ 030512 changed
	command_line_wut												= FALSE,	// VJ 030330
	command_line_dump_ini										= TRUE,	// VJ 030414 changed to true
	command_line_cyclic_joystick_index						= -1,		// loke 030418
	command_line_cyclic_joystick_x_axis						= 1,		// loke 030418
	command_line_cyclic_joystick_y_axis						= 2,		// loke 030418
	command_line_nonlinear_cyclic							= TRUE,		// arneh 2007-01-14
	command_line_collective_joystick_index					= -1,		// loke 030418
	command_line_collective_joystick_axis					= 3,		// loke 030418
	command_line_rudder_joystick_index						= -1,		// loke 030418
	command_line_rudder_joystick_axis						= 6,		// loke 030418
	command_line_nonlinear_pedals							= TRUE,		// arneh 2007-01-14
	command_line_restricted_nvg_fov							= TRUE,     // arneh 2006-11-22
	command_line_russian_nvg_no_ir							= 0,		// GCsDriver 08-12-2007
	command_line_high_res_mfd									= TRUE,		// loke 030420
	command_line_high_res_hud									= TRUE,     // arneh 20060808
	command_line_unpadlock_on_handover							= 0,     // GCsDriver  08-12-2007
	command_line_pilot_as_periscope_default							= 0,     // GCsDriver  08-12-2007
	command_line_autoreturn_to_pilot_after_periscope							= 0,     // GCsDriver  08-12-2007
	command_line_eo_full_range						= 0,		// GCsDriver  08-12-2007
	command_line_render_tree_shadows							= 1,     // GCsDriver  08-12-2007
	command_line_trees_fog										= 2,	// thealx 130430
	command_line_fly_any_airplane								= TRUE,     // VJ 030424
	command_line_tsd_enemy_colours							= 0,		// VJ 030511
	command_line_tsd_render_mode								= 0,		// VJ 030511
	command_line_tsd_palette									= 0,		// VJ 030511
	command_line_colour_mfd										= TRUE,		// arneh 2006-11-06
	command_line_maxplayers							= 4,	// Werewolf 030518
	command_line_camcom								= FALSE,	// Jabberwock 031007 Campaign Commander
	command_line_campaign_map						= 1,		// campaign map mode
	command_line_campaign_map_palette				= 1,		// palette used for campaign map
	command_line_campaign_map_update_interval       = 120,      // seconds
	command_line_tacview_logging					= 0,		// 0 = off, 1 = mission, fog of war, 2 = mission, all, 3 = campaign all
	command_line_tacview_generate_srtm_height_data  = 0,		// generate srtm height data for use with tacview
	command_line_joylook_joystick_index			= -1,	// Jabberwock 031104 Joystick look
	command_line_joylookh_joystick_axis				= 1,	// Jabberwock 031104 Joystick look
	command_line_joylookv_joystick_axis				= 2,	// Jabberwock 031104 Joystick look
	command_line_joylook_step						= 30,	// Jabberwock 031104 Joystick look
	command_line_designated_targets					= 0,  // Jabberwock 031107 Designated target
	command_line_session_filter						= 1,  //VJ 050308 changed to true!!! // Jabberwock 031210 Session filter
	command_line_pause_server						= 0,  // 040320 Jabberwock - Pause server
	command_line_reverse_pedal						= 0,	// Retro 17Jul2004
	command_line_reverse_cyclic_x					= 0,	// /thealx/
	command_line_reverse_cyclic_y					= 0,	// /thealx/
	command_line_external_trackir					= 0,	// Retro 31Oct2004
	command_line_external_trackir_direction	= 0,	// Retro 31Jan2005
	command_line_wobbly_camera				= TRUE,
	command_line_high_lod_hack						= 0,	// Retro 31Oct2004
	command_line_eo_quality							= 2,	// /thealx/
	command_line_TIR_6DOF							= 0,	// Retro 6Feb2005
	command_line_mouse_tsd_target_select            = TRUE,
	command_line_3d_cockpit							= 0,	// VJ 050101 3d cockpit mod
	command_line_shared_mem_export					= 0,	// Retro 14Aug2006
	global_aphavoc_maps								= 0,	// VJ 050123 aphavoc install hack, NOT A COMMAND LINE VARIABLE BUT GLOBAL BOOL
	global_hud_alpha									= 0,  // VJ 050126 hud mod: background
	global_mipmapping									= 1,  //VJ 050530 mipmapping on/off
	global_anisotropic								= 1,	//VJ 050530 AF on/off
	global_PNVS_level									= 0,  // VJ 050704 light setting for PNVS
	global_dynamic_water								= 1,  // VJ 050817 dynamic water textures
	global_tsd_detail                   = 0,  //VJ 061213 toggle TSD colour grid detail level
	command_line_disable_message_text  = FALSE,
//VJ 060120 OBSOLETE	global_zbuffer										= 0,	//VJ 051011 zbuffer correction //VJ 060120 OBSOLETE
//VJ 051227 no longer needed, mapinfo structure	global_season										= 1,	//VJ 051011 add winter textures
	command_line_texture_colour					= 2,  //VJ 050303 texture mod using the colours of the terrain texture bitmaps directly
	command_line_autosave							= 0,  //Casm 17JUN05 Autosave option
	command_line_saves_copies							= 1,  // make backup copies of save files /thealx/
	command_line_cannontrack						= 1, // Jabberwock 050120 Cannon tracking
// Jabberwock 031118 Server side settings
	session_planner_goto_button					= FALSE, // Jabberwock 040521 Variables HAVE to be intialised...
	session_vector_flight_model					= FALSE, // camcom bugs removed
	session_ground_radar_ignores_infantry		= 1,
	session_camcom										= 0,
// Jabberwock 031118 ends
// mue 070223 export_mfd
	command_line_export_mfd						=FALSE,
	command_line_export_mfd_adapter					=0,
	command_line_export_mfd_screen_width				=640,
	command_line_export_mfd_screen_height				=400,
	command_line_export_mfd_left_pos[4]				={0,0,256,256},
	command_line_export_mfd_right_pos[4]				={384,0,640,256},
	command_line_export_mfd_single_pos[4]				={0,0,256,256},
	command_line_ui_sounds_muted = TRUE; //ataribaby 29/12/2008 for muted UI sounds

float
	command_line_dynamics_retreating_blade_stall_effect= 1.0,
	command_line_dynamics_rudder_value						= 1.0,
	command_line_dynamics_rudder_acceleration				= 0.8,
	command_line_dynamics_main_rotor_drag					= 1.0,
	command_line_dynamics_main_rotor_lift					= 1.0,
	command_line_dynamics_tail_rotor_drag					= 1.0,
	command_line_dynamics_cyclic_dead_zone					= 0.0,
	command_line_dynamics_yaw_altitude_loss 				= 5.0,
	command_line_collective_zone_1_limit					= 0.3,		// arneh 2007-01-14
	command_line_collective_zone_2_limit					= 0.7,		// arneh 2007-01-14
	command_line_collective_percentage_at_zone1					= 60.0,		// GCsDriver  08-12-2007
	command_line_aitool_grid_pitch 							= 0.0,
	command_line_comms_resend_timeout						= 2.0,
	command_line_comms_packet_resend_timer 				= 5.0,
	command_line_city_block_approximation_range 			= 500.0,
	command_line_user_invulnerable_time						= 5.0,
	command_line_object_lod_factor							= 1.0,
	command_line_fog_of_war_maximum_value 					= DEFAULT_FOG_OF_WAR_MAXIMUM_VALUE,
	command_line_chaff_effectiveness							= 1.0,
	command_line_flare_effectiveness							= 1.0,
	command_line_smoke_effectiveness							= 1.0,
	command_line_g_force_head_movment_modifier					= 1.0,
	command_line_cockpit_vibrations								= 1.1,
	global_night_light_level					= 1.0,  // VJ 060916 light level setting at night
	global_hud_size2												= 1.0,	// VJ 050126 hud mod: size
	global_mfd_size								= 1.0;

char
	command_line_themes[128] = "", // Casm 21DEC07
	command_line_sound_device[128] = "", // Casm 07DEC09 OpenAL support
	command_line_sound_device_speech[128] = "", // Casm 22FEB11 Alternative sound device for speech
	command_line_game_initialisation_phase_path [128]			= "\0",
	command_line_game_initialisation_phase_directory [128]	= "\0",
	command_line_game_initialisation_phase_filename [128]		= "\0",
	command_line_debug_log_name[100]									= "DEBUG.LOG",
	command_line_ip_address[128]										= "\0",
	command_line_primary_server_setting[128]						= "hoxdna.org",  //VJ for werewolf 030403, default value changed 111103
	command_line_secondary_server_setting[128]					= "eech.dhs.org",  //VJ for werewolf 030403, default value changed 080403
	command_line_server_log_filename [128]			= "\0";	// Jabberwock 031119 Server log


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void process_command_line (int argc, char *argv[])
{
	const char
		*s1,
		*s2;
	char
		buf[128];

	debug_log ("%s command line (argc = %d)", *argv, argc);

	//
	// skip program name in command line
	//

	argc--;
	argv++;

	while (argc--)
	{
		s1 = *argv++;

		if ( *s1 == '-' || *s1 == '/' )
			s1++;

		s2 = strchr ( s1, ':' );

		if ( s2 )
		{
			memcpy ( buf, s1, s2 - s1 );
			buf[s2 - s1] = '\0';
			s1 = buf;
		}

		if ( !parse_option ( s1, s2 ? s2 + 1 : NULL ) )
		{
			debug_log ( "ARG:%s, RESPONSE:not recognized", s1 );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void process_environment_variable (const char *name)
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

			buffer = ( char * ) safe_malloc (strlen (env) + 1);

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
