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

extern void process_command_line (int argc, char *argv[]);

extern void process_environment_variable (const char *name);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define IGNORE_COMMAND_LINE_VERSION_NUMBER (0)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern int
	command_line_dynamics_advanced_engine_model, //Werewolf 5 Feb 06
	command_line_dynamics_flight_model,
	command_line_report_to_masterserver, //Werewolf 2 Jan 04
	command_line_dynamics_engine_startup, // arneh - july 06
	command_line_debug_input,
	command_line_debug_log_timing_info,
	command_line_dump_session,
	command_line_version_number,
	command_line_entity_update_frame_rate,
	command_line_full_screen,
	command_line_cdrom_drive_letter,
	command_line_hardware_render,
	command_line_no_sound,
	command_line_sound_hdwrbuf,
	command_line_clean_graphics,
	command_line_new_graphics,
	command_line_max_time_acceleration,
	command_line_ai_use_route_generator,
	command_line_no_graphics_conversion,
	command_line_comms_show_stats,
	command_line_comms_packet_throttle_limit,
	command_line_comms_resend_list_size,
	command_line_comms_packet_data_size,
	command_line_comms_packet_rerequest_limit,
	command_line_comms_connection_receive_size,
	command_line_comms_data_record_size,
	command_line_comms_timeout,
	command_line_comms_pack_buffer_size,
	command_line_comms_initial_sleep_time,
	command_line_comms_guaranteed_send,
	command_line_comms_dedicated_server,
	command_line_comms_interpolate_gunships,
	command_line_comms_validate_connections,
	command_line_game_initialisation_phase_game_type,
	command_line_game_initialisation_phase_gunship_type,
	command_line_max_frame_rate,
	command_line_max_game_update_rate,
	command_line_max_game_update_rate_set,
	command_line_run_mode,
	command_line_vector_flight_model,
	command_line_target_point_check,
	command_line_no_pilot_rejection,
	command_line_planner_goto_button,
	command_line_cheats_on,
	command_line_capture_aircraft,
	command_line_dynamics_sonic_buildup,
	command_line_player_start_rank,
	command_line_3d_visual_screen_width,
	command_line_3d_visual_screen_height,
	command_line_3d_visual_clear_edges,
	command_line_cpu_blit_textures,
	command_line_d3d_use_texture_management,
	command_line_no_hardware_tnl,
	command_line_no_render_to_texture,
	command_line_display_bpp,
	command_line_persistent_smoke,								// arneh 2007-07-10
	command_line_no_mission_complete_music,
	command_line_mouse_look,									// Retro 030317
	command_line_mouse_look_speed,							// Retro 030317
	command_line_min_fov,										// Retro 030318
	command_line_max_fov0,										// Retro 030318
	command_line_max_fov1,										// Casm 08OCT05
	command_line_max_fov2,										// Casm 08OCT05
	command_line_max_fov3,										// Casm 08OCT05
	command_line_eo_pan_joystick_index,						// loke 030319
	command_line_eo_pan_vertical_joystick_axis,			// loke 030319
	command_line_eo_pan_horizontal_joystick_axis,		// loke 030319
	command_line_eo_zoom_joystick_index,					// loke 030319
	command_line_eo_zoom_joystick_axis,						// loke 030319
	command_line_field_of_view_joystick_index,	
	command_line_field_of_view_joystick_axis,	
	command_line_ground_radar_ignores_infantry,			// loke 030322
	command_line_ground_stabilisation_available,			// loke 030322
	command_line_manual_laser_radar,						// arneh 2006-11-06
	command_line_targeting_system_auto_page,				// arneh 2007-01-06
	command_line_framerate,										// VJ 030324
//Retro27NovDEAD	command_line_key_mapping,									// Retro 030322
	command_line_downwash,										// Xhit 030328, VJ 030512 changed
	command_line_wut,												// VJ 030330
	command_line_dump_ini,										// VJ 030403
	command_line_cyclic_joystick_index,						// loke 030418
	command_line_cyclic_joystick_x_axis,					// loke 030418
	command_line_cyclic_joystick_y_axis,					// loke 030418
	command_line_nonlinear_cyclic,							// arneh 2007-01-14
	command_line_collective_joystick_index,					// loke 030418
	command_line_collective_joystick_axis,					// loke 030418
	command_line_rudder_joystick_index,						// loke 030418
	command_line_rudder_joystick_axis,						// loke 030418
	command_line_nonlinear_pedals,							// arneh 2007-01-14
	command_line_restricted_nvg_fov,						// arneh 2006-11-22
	command_line_russian_nvg_no_ir,						// GCsDriver 08-12-2007
	command_line_high_res_mfd,									// loke 030420
	command_line_high_res_hud,									// arneh 2006-07-18
	command_line_unpadlock_on_handover,									// GCsDriver  08-12-2007
	command_line_pilot_as_periscope_default,									// GCsDriver  08-12-2007
	command_line_autoreturn_to_pilot_after_periscope,									// GCsDriver  08-12-2007
	command_line_eo_full_range,						// GCsDriver  08-12-2007
	command_line_render_tree_shadows,						// GCsDriver  08-12-2007
	command_line_fly_any_airplane,							// VJ 030424
	command_line_tsd_enemy_colours,							// VJ 030511
	command_line_tsd_render_mode,								// VJ 030511
	command_line_tsd_palette,									// VJ 030511
	command_line_colour_mfd,									// arneh 2006-11-06
	command_line_maxplayers,									// Werewolf 030518
	command_line_camcom,										// Jabberwock 031007 Campaign Commander
	command_line_campaign_map,									// arneh 2007-07-01 campaign map mode
	command_line_campaign_map_palette,							// arneh 2007-07-01 pallette used for campaign map
	command_line_campaign_map_update_interval,					// arneh 2007-07-08 how often enemy units are updated on campaign map
	command_line_joylook_joystick_index,						// Jabberwock 031104 Joystick look
	command_line_joylookh_joystick_axis,						// Jabberwock 031104 Joystick look
	command_line_joylookv_joystick_axis,						// Jabberwock 031104 Joystick look
	command_line_joylook_step,									// Jabberwock 031104 Joystick look
	command_line_designated_targets,							// Jabberwock 031107 Designated targets
	command_line_session_filter,								// Jabberwock 031210 Session filter
	command_line_pause_server,									// Jabberwock 040220 Pause server
	command_line_reverse_pedal,									// Retro 17Jul2004
	command_line_external_trackir,								// Retro 31Oct2004
	command_line_external_trackir_direction,					// Retro 31Jan2005 (spooky, eh ?)
	command_line_wobbly_camera,									// arneh - makes external cameras wobbly in movement
	command_line_high_lod_hack,									// Retro 31Oct2004
	command_line_TIR_6DOF,										// Retro 6Feb2005
	command_line_mouse_tsd_target_select,                       // arneh, feb 2008
	command_line_3d_cockpit,								//VJ 050101 3d cpckpit mod
	command_line_shared_mem_export,								// Retro 14Aug2006
	global_aphavoc_maps,									// VJ 050123 aphavoc install hack, NOT A COMMAND LINE VARIABLE BUT GLOBAL BOOL
	global_hud_alpha, 									// VJ 050126 hud mod: background 
	command_line_texture_colour, 						//VJ 050303 texture mod using the colours of the terrain texture bitmaps directly
	global_mipmapping,  										//VJ 050530 mipmapping on/off
	global_anisotropic,										//VJ 050530 AF on/off	
	global_PNVS_level, 									 // VJ 050704 light setting for PNVS
	global_dynamic_water,  								//VJ 050817 dynamic water textures
	global_tsd_detail,                   //VJ 061213 toggle TSD colour grid detail level
	command_line_disable_message_text,					// arneh, - disables the output of text messages (at top of screen)
//VJ 051227 no longer needed, mapinfo structure	global_season,											//VJ 051011 add winter textures
//VJ 060120 OBSOLETE	global_zbuffer,										//VJ 051011 zbuffer correction
	command_line_autosave,								//Casm 17JUN05 Autosave option
	command_line_cannontrack,								// Jabberwock 050120 Cannon tracking
// Jabberwock 031118 Server side settings - temporary values so that ini is not overwritten with server data
	session_planner_goto_button,
	session_vector_flight_model,
	session_ground_radar_ignores_infantry,
	session_camcom,
// mue 070223 export_mfd
	command_line_export_mfd,
	command_line_export_mfd_adapter,
	command_line_export_mfd_screen_width,
	command_line_export_mfd_screen_height,
	command_line_export_mfd_right_pos[4],
	command_line_export_mfd_left_pos[4],
	command_line_export_mfd_single_pos[4];

 

extern float
	command_line_dynamics_retreating_blade_stall_effect,
	command_line_dynamics_rudder_value,
	command_line_dynamics_rudder_acceleration,
	command_line_collective_zone_1_limit,					// arneh 2007-01-14
	command_line_collective_zone_2_limit,					// arneh 2007-01-14
	command_line_collective_percentage_at_zone1,					// GCsDriver  08-12-2007
	command_line_dynamics_main_rotor_drag,
	command_line_dynamics_main_rotor_lift,
	command_line_dynamics_tail_rotor_drag,
	command_line_dynamics_cyclic_dead_zone,
	command_line_dynamics_yaw_altitude_loss,
	command_line_aitool_grid_pitch,
	command_line_comms_packet_resend_timer,
	command_line_comms_resend_timeout,
	command_line_city_block_approximation_range,
	command_line_user_invulnerable_time,
	command_line_object_lod_factor,
	command_line_fog_of_war_maximum_value,
	command_line_chaff_effectiveness,
	command_line_flare_effectiveness,
	command_line_smoke_effectiveness,
	command_line_g_force_head_movment_modifier,
	global_night_light_level, //VJ 060920 night light levels (0-1)
	global_hud_size2;// VJ 050126 hud mod: size 	

extern char
	command_line_themes[], //Casm 21DEC07
	command_line_game_initialisation_phase_path [],
	command_line_game_initialisation_phase_directory [],
	command_line_game_initialisation_phase_filename [],
	command_line_debug_log_name[],
	command_line_ip_address[],
	command_line_primary_server_setting[],	 //VJ for werewolf and eech.ini 030403
	command_line_secondary_server_setting[], //VJ for werewolf and eech.ini 030403
	command_line_server_log_filename[]; // Jabberwock 031119 Server log


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum RUN_MODES
{

	RUN_MODE_NORMAL,
	RUN_MODE_AITOOL,
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Retro 27Nov2004 - final resting place ?
enum MOUSELOOK_CONTROL_TYPE
{
	MOUSELOOK_OFF = 0,
	MOUSELOOK_INTERNAL,
	MOUSELOOK_EXTERNAL,
	MOUSELOOK_ON,			// internal+external
	MOUSELOOK_MAX
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
