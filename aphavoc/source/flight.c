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



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

in_flight_game_modes
	in_flight_game_mode;

int
	pages_clear,
	game_update_time;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_in_flight_menus (void);

static void update_in_flight_timers (void);

static void limit_frame_rate (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void flight (void)
{

	entity
		*keysite;

	int
		count;

	// Casm 17JUN05 Autosave option
	time_t
		last_autosaved, now;
	// Casm 17JUN05 Autosave option


	keysite = NULL;

	////////////////////////////////////////
	//
	// INITIALISE FLIGHT
	//
	////////////////////////////////////////

	set_game_exit_type (GAME_EXIT_INVALID);

	ASSERT (get_current_game_session ());

/////////////////////////////////////////
//VJ 050116 custom texture mod

	//VJ 051227 changed function parameter to void
	load_warzone_override_textures ();
	
	//repaint the screen to show the textures are loaded
	ui_repaint ();
/////////////////////////////////////////

	set_exit_flight_loop (FALSE);

	push_event_stop ();

	push_event (flight_events, "flight_events");

	initialise_views ();
	

	if (command_line_comms_dedicated_server)
	{

		set_raw_in_flight_game_mode (IN_FLIGHT_GAME_MODE_PLANNER);

		push_ui_screen (dedicated_server_screen);
	}
	else
	{
		if (get_game_type () == GAME_TYPE_FREE_FLIGHT)
		{
			free_flight_auto_assign_gunship ();
		}

		////////////////////////////////////////
		//
		// Start the ui on the situation screen
		//
		////////////////////////////////////////

		set_raw_in_flight_game_mode (IN_FLIGHT_GAME_MODE_PLANNER);

		switch (get_game_type ())
		{
			case GAME_TYPE_FREE_FLIGHT:
			{
				push_ui_screen (free_flight_screen);

				push_event (ingame_screen_set_events, "ingame screen events");

				break;
			}
			case GAME_TYPE_CAMPAIGN:
			case GAME_TYPE_SKIRMISH:
			{
				#if !DEMO_VERSION

				push_ui_screen (campaign_screen);

				push_event (ingame_screen_set_events, "ingame screen events");

				#endif

				break;
			}
			case GAME_TYPE_DEMO:
			{
				set_raw_in_flight_game_mode (IN_FLIGHT_GAME_MODE_SIMULATOR);

				set_local_entity_float_value (get_session_entity (), FLOAT_TYPE_TIME_OF_DAY_ACCELERATION, 60.0 * 2.0);

				set_local_entity_int_value (get_session_entity (), INT_TYPE_SKIP_NIGHT_TIME, TRUE);

				push_event (demo_events, "Demo events");

				break;
			}
			default:
			{
				debug_fatal ("FLIGHT: unknown gametype %d", get_game_type ());
			}
		}
	}

	start_ai_system ();

	start_ingame_ui_system ();

	////////////////////////////////////////
	//
	// FLIGHT
	//
	////////////////////////////////////////

	game_update_time = TIME_1_SECOND / command_line_max_game_update_rate;

	set_raw_time_acceleration (get_min_time_acceleration ());

	reset_delta_time ();

	debug_watch_delta_time ();

	set_display_exit_message (FALSE);

	if (get_comms_model () == COMMS_MODEL_SERVER)
	{
		server_create_session ();
	}

	////////////////////////////////////////
	set_game_status (GAME_STATUS_INITIALISED);
	////////////////////////////////////////

	if (get_game_type () == GAME_TYPE_DEMO)
	{

		//
		// demo mode
		//

		notify_local_entity (ENTITY_MESSAGE_SET_CAMERA_ACTION, get_camera_entity (), NULL, CAMERA_ACTION_AUTO_EDIT);
	}

	pages_clear = 0;

	////////////////////////////////////////

	reset_receive_packet_list_time_stamps ();

	////////////////////////////////////////
	//
	// leave pre_flight_test immediately BEFORE flight loop
	//

	pre_flight_test ();

	//
	////////////////////////////////////////

	////////////////////////////////////////
	//
	// Start gameloop
	//
	////////////////////////////////////////

	//
	// initialise joystick
	//
	read_joystick_values(0);	// Retro 10Jul2004
#if 0	// Retro 10Jul2004
	if (global_options.cyclic_input == JOYSTICK_INPUT)
	{
		read_joystick_values (get_global_joystick_device_index ());

		//-seeker 2003.04.20  multiple joystick hack
		if (command_line_rudder_joystick_index != -1)
		{
			read_joystick_values (command_line_rudder_joystick_index);
		}

		if (command_line_cyclic_joystick_index != -1)
		{
			read_joystick_values (command_line_cyclic_joystick_index);
		}

		if (command_line_collective_joystick_index != -1)
		{
			read_joystick_values (command_line_cyclic_joystick_index);
		}
	}
#endif	// Retro 10Jul2004

	// Casm 17JUN05 Autosave option
	last_autosaved = time ( NULL );
	// Casm 17JUN05 Autosave option

	while (!get_exit_flight_loop ())
	{

		//
		// tidy up screen for cards that dont draw to the screen extents.
		//

		if (pages_clear < 2)
		{

			pages_clear ++;

			clear_screen ();
		}

		//
		// Allow system thread some processor time (for events etc)
		//

		system_sleep (0);

		//
		// Time acceleration
		//

		count = get_time_acceleration ();

		if (count == 0)
		{
			set_active_screen (video_screen);

			update_client_server_entity (get_camera_entity ());
			
			if (command_line_pause_server) // 040220 Pause server - is it safe?
			{
                                receive_comms_data ();
                                update_update_functions (); // 040621 Jabberwock cvc active during pause to remove pilot entry
 
			}                              // 040621 Moje added -only expl. Pause server ends
		}
		else
		{
			while (count --)
			{
				set_active_screen (video_screen);

				receive_comms_data ();

				// received packet may have deinitialised the entity system
				if ((!get_session_entity ()) || (get_game_exit_type () == GAME_EXIT_KICKOUT))
				{

					set_exit_flight_loop (TRUE);

					break;
				}

				update_client_server_entities ();

				reset_interpolation_timer ();

				update_update_functions ();

				update_cpu_count ();

				update_view ();

				update_in_flight_timers ();
			}
		}

		if (get_exit_flight_loop ())
		{

			break;
		}

		in_flight_test ();

		reset_local_entity_drawn_flags ();

		switch (get_in_flight_game_mode ())
		{

			case IN_FLIGHT_GAME_MODE_SIMULATOR:
			{
				//
				// Check the resolution!
				//

				if (	( application_video_width != ( int ) full_screen_width ) ||
						( application_video_colourdepth != full_screen_colourdepth ) )
				{

					ddraw_change_display_resolution ( ( int ) full_screen_width, ( int ) full_screen_height, full_screen_colourdepth );
				}

				//
				// Draw view
				//

				draw_view ();

				//
				// play scene sound (after draw view)
				//

				play_application_main_scene_sound ();

				//
				//
				//

				if (record_screen_sequence)
				{
					save_screen_image_and_viewpoint_data ();
				}

				display_in_flight_debug_info ();

				display_comms_stats ();

				display_exit_message ();

				ddraw_flip_surface ();

				break;
			}

			case IN_FLIGHT_GAME_MODE_PLANNER:
			{
				//
				// Check the resolution!
				//

				if ( application_video_width != get_global_3d_visual_screen_width () )
				{

					ddraw_change_display_resolution ( get_global_3d_visual_screen_width (),
																	get_global_3d_visual_screen_height (), full_screen_colourdepth );
				}

				update_in_flight_menus ();

				play_application_ui_sound ();

				break;
			}
		}

		limit_frame_rate ();

		set_delta_time ();

		//-- Werewolf
		net_handle_heartbeat ();
		//-- Werewolf

		//
		// inputs
		//

		process_events ();
		read_joystick_values(0);	// Retro 10Jul2004
#if 0	// Retro 10Jul2004
		if (global_options.cyclic_input == JOYSTICK_INPUT)
		{

			read_joystick_values (get_global_joystick_device_index());

			//-seeker 2003.04.20  multiple joystick hack
			if (command_line_rudder_joystick_index != -1)
			{
				read_joystick_values (command_line_rudder_joystick_index);
			}

			if (command_line_cyclic_joystick_index != -1)
			{
				read_joystick_values (command_line_cyclic_joystick_index);
			}

			if (command_line_collective_joystick_index != -1)
			{
				read_joystick_values (command_line_cyclic_joystick_index);
			}
		}
#endif	// Retro 10Jul2004
		// Casm 17JUN05 Autosave option
		now = time ( NULL );
		if ( command_line_autosave > 0 && last_autosaved + command_line_autosave < now )
		{
			debug_log ( "Autosaving..." );
			store_session ( get_current_game_session (), "AUTOSAVE" );
			last_autosaved = now;
		}
		// Casm 17JUN05 Autosave option
	}

	ASSERT ((get_ui_screen_stack_head () != campaign_screen) && (get_ui_screen_stack_head () != options_screen));

	////////////////////////////////////////
	set_game_status (GAME_STATUS_UNINITIALISING);
	////////////////////////////////////////

	//
	// Check resolution we're in.
	//

	if ( application_video_width != get_global_3d_visual_screen_width () )
	{

		ddraw_change_display_resolution ( get_global_3d_visual_screen_width (),
														get_global_3d_visual_screen_height (), full_screen_colourdepth );
	}

	////////////////////////////////////////
	//
	// leave post_flight_test immediately AFTER flight loop
	//

	post_flight_test ();

	//
	////////////////////////////////////////

	pop_to_event_stop ();

	set_gunship_entity (NULL);

	set_pilot_entity (NULL);

	stop_local_entity_sounds ();

	if (get_game_type () == GAME_TYPE_DEMO)
	{
		set_local_entity_float_value (get_session_entity (), FLOAT_TYPE_TIME_OF_DAY_ACCELERATION, 1.0);

		set_local_entity_int_value (get_session_entity (), INT_TYPE_SKIP_NIGHT_TIME, FALSE);
	}

	////////////////////////////////////////
	// debug

	data_exchange ();

	leave_mission ();

	stop_ai_system ();

	stop_ingame_ui_system ();

	reset_comms_stats ();

	deinitialise_views ();

	////////////////////////////////////////////////////////////////////////////////////
	//VJ 050116 custom texture mod: destroy override textures and restore default ones
	restore_default_textures();
	////////////////////////////////////////////////////////////////////////////////////

	//
	// Everything is destroyed now so close pack buffer
	//

	close_pack_buffer ();

	// end
	////////////////////////////////////////

	////////////////////////////////////////
	//
	// DEINITIALISE FLIGHT
	//
	////////////////////////////////////////

	ui_object_unselect_list (session_list);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void toggle_in_flight_game_modes (event *ev)
{
	if (get_in_flight_game_mode () == IN_FLIGHT_GAME_MODE_SIMULATOR)
	{
		set_in_flight_game_mode (IN_FLIGHT_GAME_MODE_PLANNER);
	}
	else
	{
		pages_clear = 0;

		set_in_flight_game_mode (IN_FLIGHT_GAME_MODE_SIMULATOR);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_raw_in_flight_game_mode (int flag)
{

	in_flight_game_mode = (in_flight_game_modes)flag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_in_flight_game_mode (int flag)
{

	in_flight_game_mode = (in_flight_game_modes)flag;

	switch (flag)
	{

		case IN_FLIGHT_GAME_MODE_SIMULATOR:
		{

			//
			// going back to cockpit
			//

			if (get_event_stack_head_function () != flight_events)
			{

				push_event (flight_events, "flight events");
			}

			set_mouse_off ();

			////////////////////////////////////////
			//

			if (get_local_entity_int_value (get_camera_entity (), INT_TYPE_CAMERA_MODE) == CAMERA_MODE_END_OF_MISSION)
			{
				notify_local_entity (ENTITY_MESSAGE_SET_CAMERA_ACTION, get_camera_entity (), NULL, CAMERA_ACTION_CHASE);
			}

			//
			////////////////////////////////////////

			break;
		}

		case IN_FLIGHT_GAME_MODE_PLANNER:
		{
			stop_messaging_system (NULL);

			//
			// going back to UI
			// UI screen already on stack but we need to call its function
			//

			if (get_event_stack_head_function () != ingame_screen_set_events)
			{

				push_event (ingame_screen_set_events, "ingame screen events");
			}

			set_mouse_on ();

			push_ui_screen (get_ui_screen_stack_head ());

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_in_flight_menus (void)
{

	#if DEBUG_MODULE

	debug_log ("FLIGHT: Update in_flight_menus");

	#endif

	ui_force_update ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_in_flight_timers (void)
{
	update_speech_buffers ();

	update_mobile_sprite_light_timers ();

	update_aircraft_damage_timers ();

	update_message_log ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void limit_frame_rate (void)
{

	if (get_delta_time () < ((float) 1.0 / command_line_max_frame_rate))
	{

		#if DEBUG_MODULE

		debug_log ("LIMIT FRAME RATE: delta time = %f, max frame rate = %d, sleep %f", get_delta_time (), command_line_max_frame_rate, ((((float) 1.0 / command_line_max_frame_rate) - get_delta_time ()) * TIME_1_SECOND));

		#endif

		system_sleep ((((float) 1.0 / command_line_max_frame_rate) - get_delta_time ()) * TIME_1_SECOND);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


