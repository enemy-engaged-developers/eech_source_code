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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//static void initialise_service_provider_connection ( void );

static void set_multiplayer_options_display ( void );

static void multiplayer_modem_dial_update_function ( void );

static void multiplayer_modem_answer_update_function ( void );

static void multiplayer_modem_connection_update_function ( void );

static void break_modem_connection ( void );

static void ghost_ui_objects_for_modem (ui_object *obj, int flag);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum MODEM_INITIALISE_VALUES
{

	MODEM_NOT_CONNECTED,
	MODEM_DIALING,
	MODEM_ANSWERING,
	MODEM_DIALLED_CONNECTED,
	MODEM_ANSWERED_CONNECTED,
};

typedef enum MODEM_INITIALISE_VALUES modem_initialise_values;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

modem_initialise_values
	modem_state = MODEM_NOT_CONNECTED;

service_provider_table_type
	*current_active_service = NULL;

modem_names
	*current_modem;
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_serial_connection_status ( void )
{

	char
		text_buffer [256];

	connection_data_type
		*this_connection;

	this_connection = direct_play_get_connection_data ();

	if ( ( this_connection ) && ( this_connection->service_provider.guid ) )
	{

		if ( memncmp ( ( char * ) this_connection->service_provider.guid, ( char * ) &DPSPGUID_SERIAL, sizeof ( GUID ) ) == TRUE )
		{

			set_direct_play_serial_address ( get_global_comms_port (), get_global_baud_rate (), get_global_stop_bits (), get_global_parity (), get_global_flow () );

			if ( direct_play_create_session ( 0 ) )
			{

				sprintf (text_buffer, "%s: %s", get_trans ("MP_STATUS"), get_trans ("MP_CONNECTED"));

				set_ui_object_text (serial_status_text, text_buffer);

				direct_play_close_session ();

				this_connection->is_initialised = TRUE;
			}
			else
			{

				sprintf (text_buffer, "%s: %s", get_trans ("MP_STATUS"), get_trans ("MP_INVALID_PROPERTIES"));

				set_ui_object_text (serial_status_text, text_buffer);

				this_connection->is_initialised = FALSE;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_multi_player_setup (void)
{

	connection_data_type
		*this_connection;

	unsigned char
		text [10];

//	if ( get_ui_object_drawable ( obj ) )
//	{

		this_connection = direct_play_get_connection_data ();
	
		blit_front_buffer_to_render_buffer ();
	

		// Setup the service provider cycle button
	
		if ( this_connection->service_provider.name )
		{
			if ( memncmp ( ( char * ) this_connection->service_provider.guid, ( char * ) &DPSPGUID_TCPIP, sizeof ( GUID ) ) == TRUE )
			{
				set_ui_object_text (connection_type_button, get_trans("MP_INTERNET"));
			}
			else if ( memncmp ( ( char * ) this_connection->service_provider.guid, ( char * ) &DPSPGUID_SERIAL, sizeof ( GUID ) ) == TRUE )
			{
				set_ui_object_text (connection_type_button, get_trans("MP_SERIAL"));
			}
			else if ( memncmp ( ( char * ) this_connection->service_provider.guid, ( char * ) &DPSPGUID_MODEM, sizeof ( GUID ) ) == TRUE )
			{
				set_ui_object_text (connection_type_button, get_trans("MP_MODEM"));
			}
			else if ( memncmp ( ( char * ) this_connection->service_provider.guid, ( char * ) &DPSPGUID_IPX, sizeof ( GUID ) ) == TRUE )
			{
				set_ui_object_text (connection_type_button, get_trans("MP_IPX"));
			}
		}
		else
		{
			set_ui_object_text (connection_type_button, get_trans ("MP_NO_SERVICE_PROVIDER"));
		}

		preprocess_translation_object_size (connection_type_bdrop, connection_type_button, NULL, 0, RESIZE_OPTION_BOX_TITLE);
	
		// initialise modem to first in list (? Shouldn't we store the current modem elsewhere - ie globally ?)

		current_modem = modem_name_list;

		if (!current_modem)
		{
			set_ui_object_text (modem_type_button, "No Modem Installed");
		}
		else
		{
			set_ui_object_text (modem_type_button, current_modem->name);
		}

		// Com port button

		sprintf (text, "%d", get_global_comms_port ());

		set_ui_object_text (com_port_button, text);

		// Baud rate
	
		set_ui_object_text (baud_rate_button, baud_rate_text [get_global_baud_rate () - 1]);

		// Stop bits
	
		set_ui_object_text (stop_bits_button, stop_bits_text [get_global_stop_bits () - 1]);

		// Parity
	
		set_ui_object_text (parity_button, parity_text [get_global_parity () - 1]);

		// Flow
	
		set_ui_object_text (flow_button, flow_text [get_global_flow () - 1]);

		// Phone Number

		set_ui_object_text (phone_number_text_obj, global_options.phone_number);

		// IP Address

		set_ui_object_text (ip_address_text_obj, global_options.ip_address);


		// Now setup the connection type areas
	
		set_multiplayer_options_display ();
	

		// Lastly load in the stuff for the screen
/*	
		if ( multiplayer_screen_graphic )
		{
	
			destroy_texture_graphic ( multiplayer_screen_graphic );

			multiplayer_screen_graphic = NULL;
		}
	
		multiplayer_screen_graphic = create_texture_graphic ( "graphics\\ui\\cohokum\\multi.psd" );
	
		set_ui_object_texture_graphic ( multi_player_setup_area, multiplayer_screen_graphic );
	
		blit_front_buffer_to_render_buffer ();
	
		reset_time_values ( options_screen );
*/
//	}
//	else
//	{
/*
		if ( multiplayer_screen_graphic )
		{
	
			destroy_texture_graphic ( multiplayer_screen_graphic );

			multiplayer_screen_graphic = NULL;
		}
*/
//	}

	display_options_page (OPTIONS_PAGE_MULTIPLAYER);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void validate_modem_connection ( void )
{

	switch ( modem_state )
	{

		case MODEM_DIALLED_CONNECTED:
		case MODEM_ANSWERED_CONNECTED:
		{

			LPDPSESSIONDESC2 
				caps;
	
			direct_play_session_capabilities ();
	
			caps = direct_play_get_session_capabilities ();
	
			if ( caps )
			{
	
				if ( caps->dwCurrentPlayers != 2 )
				{

					break_modem_connection ();
				}
			}
			else
			{

				break_modem_connection ();
			}

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void break_modem_connection ( void )
{

	char
		text_buffer [256];

	connection_data_type
		*this_connection;

	ui_set_user_function ( NULL );

	switch ( modem_state )
	{

		case MODEM_DIALING:
		case MODEM_DIALLED_CONNECTED:
		{

			//
			// We can't destroy groups, or sessions.
			//

			direct_play_leave_group ();
	
			direct_play_destroy_player ();

			direct_play_close_session ();

			break;
		}

		case MODEM_ANSWERING:
		case MODEM_ANSWERED_CONNECTED:
		{

			direct_play_leave_group ();
	
			direct_play_destroy_player ();
	
			direct_play_destroy_group ();
	
			direct_play_close_session ();

			break;
		}
	}

	sprintf ( text_buffer, "%s: %s", get_trans ("MP_STATUS"), get_trans("MP_UNCONNECTED"));
	
	set_ui_object_text (modem_status_text, text_buffer);

//	set_ui_object_drawable ( multi_player_back_button, UI_OBJECT_STATE_ON );

	direct_play_destroy_modem ();

	this_connection = direct_play_get_connection_data ();

	if ( this_connection )
	{
	
		this_connection->one_way_hosting_setup = TRUE;
		this_connection->is_initialised = FALSE;
		this_connection->is_hosting = FALSE;
	}

	modem_state = MODEM_NOT_CONNECTED;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_modem_cancel_function ( ui_object *obj, void *arg )
{

	break_modem_connection ();

	ghost_ui_objects_for_modem (obj, FALSE);

	// don't leave text selected

	set_toggle_button_off (obj);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_modem_dial_function ( ui_object *obj, void *arg )
{
	ghost_ui_objects_for_modem (obj, TRUE);

	switch ( modem_state )
	{

		case MODEM_NOT_CONNECTED:
		{

			char
				*modem,
				*phone;
		
			modem = current_modem->name;
		
			phone = NULL;
				
			if ( modem )
			{
		
				if ( strlen ( get_ui_object_text ( phone_number_text_obj ) ) > 0 )
				{
		
					phone = get_ui_object_text ( phone_number_text_obj );

					modem_state = MODEM_DIALING;
		
					//
					// Have to call enum sessions to get the phone to dial out
					//
		
					if ( direct_play_dial_modem ( modem, phone ) )
					{
			
						//
						// Remove the back button while we connect
						//
						
//						set_ui_object_drawable ( multi_player_back_button, UI_OBJECT_STATE_OFF );
			
						ui_set_user_function ( multiplayer_modem_dial_update_function );
					}
					else
					{

						//
						// Report connection failed
						//
					}
				}
				else
				{
		
					//
					// Report no phone number typed in
					//
				}
			}

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_modem_answer_function ( ui_object *obj, void *arg )
{
	char
		text_buffer [256];

	ghost_ui_objects_for_modem (obj, TRUE);

	switch ( modem_state )
	{

		case MODEM_NOT_CONNECTED:
		{
		
			char
				*modem;
		
			modem = current_modem->name;
				
			if ( modem )
			{
		
				//
				// Have to call create session to get the phone to answer
				//
		
				if ( direct_play_answer_modem ( modem, GAME_TYPE_INVALID ) )
				{
			
					direct_play_session_capabilities ();
			
					direct_play_create_group ();
			
					direct_play_create_player ();
			
					set_server_id (direct_play_get_player_id ());
			
					//
					// Turn off the back button while we connect
					//
			
//					set_ui_object_drawable ( multi_player_back_button, UI_OBJECT_STATE_OFF );
			
					sprintf (text_buffer, "%s: %s", get_trans ("MP_STATUS"), get_trans ("MP_WAITING_FOR_CALL"));
				
					set_ui_object_text (modem_status_text, text_buffer);
	
					modem_state = MODEM_ANSWERING;
			
					ui_set_user_function ( multiplayer_modem_answer_update_function );
				}
			}

			break;
		}
	}

	// don't leave text selected

	set_toggle_button_off (obj);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
void notify_multi_player_setup_exit_button ( ui_object *obj, void *arg )
{

	if ( ( int ) arg == BUTTON_STATE_UP )
	{

		// Set the tcp/ip address to the one in the text area
	
		strncpy ( global_options.ip_address, get_ui_object_text ( ip_address_text_obj ), 127 );

		global_options.ip_address[127] = '\0';

		// Set the phone number to the one in the text area

		strncpy ( global_options.phone_number, get_ui_object_text ( phone_number_text_obj ), 127 );

		global_options.phone_number[127] = '\0';
	
		// Try to give the service provider all the information it needs
	
		initialise_service_provider_connection ();

		ui_set_user_function ( NULL );

		// Save the global options data

		save_global_options_data ();
	
		pop_ui_screen ();
	}

}
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void multiplayer_modem_dial_update_function ( void )
{

	char
		text_buffer [256];

	int
		game_update_time;

	static int
		update_ticks = 0;

	game_update_time = TIME_1_SECOND;

	if ( update_ticks < get_system_time () )
	{

		session_table_type
			*this_session;
	
		connection_data_type
			*this_connection;

		HRESULT
			connection_code;

		connection_code = direct_play_dial_modem_status ();

		if ( connection_code == DP_OK )
		{

			//
			// Need to do the final enumeration
			//

			sprintf (text_buffer, "%s: %s", get_trans ("MP_STATUS"), get_trans ("MP_FINDING_GAMES"));
				
			if ( direct_play_enumerate_sessions () )
			{
	
				set_comms_model ( COMMS_MODEL_CLIENT );
	
				this_session = direct_play_get_session_table ();
	
				if ( this_session )
				{

					int
						baudrate;

					this_connection = direct_play_get_connection_data ();
		
					this_connection->this_session.session = this_session->session;
		
					sprintf (text_buffer, "%s: %s", get_trans ("MP_STATUS"), get_trans ("MP_JOINING_GAMES"));
				

					if ( //schorpp "fatal" errhdl , maybe outdated, who uses modem to modem nowadays?

					direct_play_join_session () &&

					direct_play_session_capabilities () &&

					direct_play_enumerate_groups () )
					{

						this_connection->this_group = direct_play_get_group_table ();

						if (
			
						direct_play_create_player () &&

						direct_play_join_group () )
						{

						baudrate = direct_play_get_connection_baudrate ();
		
						sprintf (text_buffer, "%s: %s %d", get_trans ("MP_STATUS"), get_trans ("MP_CONNECTED_AT"), baudrate * 100);
					
						set_ui_object_text (modem_status_text, text_buffer);

	//					set_ui_object_drawable ( multi_player_back_button, UI_OBJECT_STATE_ON );

						ghost_ui_objects_for_modem (NULL, FALSE);

						modem_state = MODEM_DIALLED_CONNECTED;

						ui_set_user_function ( multiplayer_modem_connection_update_function );

						}

					}
					else
					{


					// schorpp mp errhd01 "fatal" 7/17/03
					debug_log ("SESSION: Server has got a problem, request campaing restart. ");
					sprintf (text_buffer, "Server has got a problem, request campaing restart.  %s", get_trans ("MP_UNCONNECTED"));
				
					set_ui_object_text ( modem_status_text, text_buffer );

					modem_state = MODEM_NOT_CONNECTED;

	//				set_ui_object_drawable ( multi_player_back_button, UI_OBJECT_STATE_ON );

					ghost_ui_objects_for_modem (NULL, FALSE);

					ui_set_user_function ( NULL );

		
					}
				}
			}
		}
		else
		{

			if ( connection_code == DPERR_CONNECTING )
			{
	

				sprintf (text_buffer, "%s: %s", get_trans ("MP_STATUS"), get_trans ("MP_CONNECTING"));
				
				set_ui_object_text ( modem_status_text, text_buffer );
			}
			else
			{

				sprintf (text_buffer, "%s: %s", get_trans ("MP_STATUS"), get_trans ("MP_UNCONNECTED"));
				
				set_ui_object_text ( modem_status_text, text_buffer );

				modem_state = MODEM_NOT_CONNECTED;

//				set_ui_object_drawable ( multi_player_back_button, UI_OBJECT_STATE_ON );

				ghost_ui_objects_for_modem (NULL, FALSE);

				ui_set_user_function ( NULL );
			}
		}

		update_ticks = get_system_time () + game_update_time;

		set_delta_time ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void multiplayer_modem_answer_update_function ( void )
{

	int
		game_update_time;

	static int
		update_ticks = 0;

	game_update_time = TIME_1_SECOND;

	if ( update_ticks < get_system_time () )
	{

		LPDPSESSIONDESC2 
			caps;

		direct_play_session_capabilities ();

		caps = direct_play_get_session_capabilities ();

		if ( caps )
		{

			if ( caps->dwCurrentPlayers == 2 )
			{

				int
					baudrate;

				char
					text_buffer[256];

				baudrate = direct_play_get_connection_baudrate ();


				sprintf (text_buffer, "%s: %s %d", get_trans ("MP_STATUS"), get_trans ("MP_CONNECTED_AT"), baudrate * 100);
				
				set_ui_object_text (modem_status_text, text_buffer);

//				set_ui_object_drawable ( multi_player_back_button, UI_OBJECT_STATE_ON );

				ghost_ui_objects_for_modem (NULL, FALSE);

				modem_state = MODEM_ANSWERED_CONNECTED;

				ui_set_user_function ( multiplayer_modem_connection_update_function );
			}
		}

		update_ticks = get_system_time () + game_update_time;

		set_delta_time ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void multiplayer_modem_connection_update_function ( void )
{

	int
		update_time;

	static int
		update_ticks = 0;

	update_time = TIME_1_SECOND;

	if ( update_ticks < get_system_time () )
	{

		validate_modem_connection ();

		update_ticks = get_system_time () + update_time;

		set_delta_time ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_service_provider_connection ( void )
{

	connection_data_type
		*this_connection;

	this_connection = direct_play_get_connection_data ();

	if ( ( this_connection ) && ( this_connection->service_provider.guid ) )
	{

		//
		// Set default values for session opening / enumeration
		//

		this_connection->one_way_hosting_setup = FALSE;
		this_connection->is_initialised = TRUE;
		this_connection->is_hosting = FALSE;

		//
		// Only initialise TCP/IP and serial connections.
		//  IPX doesn't need initialising at all, and
		//  modem should be initialised elsewhere ( when the user clicks dial/answer/canel ).
		//

		reset_comms_data ();

		deinitialise_comms_manager ();

		if ( memncmp ( ( char * ) this_connection->service_provider.guid, ( char * ) &DPSPGUID_TCPIP, sizeof ( GUID ) ) == TRUE )
		{

			// need good way to restore default values without overwritting commandline params
			//command_line_comms_resend_list_size						= 1000;
			//command_line_comms_packet_data_size						= 512;
			//command_line_comms_packet_rerequest_limit				= 100;
			//command_line_comms_connection_receive_size			= (32 * 1024);
			//command_line_comms_data_record_size						= (200 * 1024);
			//command_line_comms_timeout									= (2.0 * 60.0);
			//command_line_comms_pack_buffer_size						= (200 * 1024);
			//command_line_comms_initial_sleep_time					= 500;
			//command_line_max_frame_rate								= 30;

			if (!command_line_max_game_update_rate_set)
			{
			
				command_line_max_game_update_rate						= 5;
			}

			//command_line_comms_resend_timeout						= 10.0;
			//command_line_comms_packet_resend_timer 				= 2.0;

			set_direct_play_inet_address ( global_options.ip_address );
		}
		else if ( memncmp ( ( char * ) this_connection->service_provider.guid, ( char * ) &DPSPGUID_SERIAL, sizeof ( GUID ) ) == TRUE )
		{

			//command_line_comms_resend_list_size						= 1000;
			//command_line_comms_packet_data_size						= 512;
			//command_line_comms_packet_rerequest_limit				= 100;
			//command_line_comms_connection_receive_size			= (32 * 1024);
			//command_line_comms_data_record_size						= (200 * 1024);
			//command_line_comms_timeout									= (2.0 * 60.0);
			//command_line_comms_pack_buffer_size						= (200 * 1024);
			//command_line_comms_initial_sleep_time					= 500;
			//command_line_max_frame_rate								= 30;
			if (!command_line_max_game_update_rate_set)
			{

				command_line_max_game_update_rate						= 15;
			}
			//command_line_comms_resend_timeout						= 10.0;
			//command_line_comms_packet_resend_timer 				= 2.0;

			set_direct_play_serial_address ( get_global_comms_port (), get_global_baud_rate (), get_global_stop_bits (), get_global_parity (), get_global_flow () );

			set_serial_connection_status ();
		}
		else if ( memncmp ( ( char * ) this_connection->service_provider.guid, ( char * ) &DPSPGUID_MODEM, sizeof ( GUID ) ) == TRUE )
		{

			//command_line_comms_resend_list_size						= 1000;
			//command_line_comms_packet_data_size						= 512;
			//command_line_comms_packet_rerequest_limit				= 100;
			//command_line_comms_connection_receive_size			= (32 * 1024);
			//command_line_comms_data_record_size						= (200 * 1024);
			//command_line_comms_timeout									= (2.0 * 60.0);
			//command_line_comms_pack_buffer_size						= (200 * 1024);
			//command_line_comms_initial_sleep_time					= 500;
			//command_line_max_frame_rate								= 30;
			if (!command_line_max_game_update_rate_set)
			{

				command_line_max_game_update_rate						= 5;
			}
			//command_line_comms_resend_timeout						= 10.0;
			//command_line_comms_packet_resend_timer 				= 2.0;

			this_connection->one_way_hosting_setup = TRUE;

			switch ( modem_state )
			{

				case MODEM_NOT_CONNECTED:
				{

					this_connection->is_initialised = FALSE;

					break;
				}

				case MODEM_DIALING:
				case MODEM_ANSWERING:
				{

					debug_fatal ( "How can you exit this screen without a button to exit?" );

					break;
				}

				case MODEM_DIALLED_CONNECTED:
				{

					this_connection->is_initialised = TRUE;

					this_connection->is_hosting = FALSE;

					break;
				}

				case MODEM_ANSWERED_CONNECTED:
				{

					this_connection->is_initialised = TRUE;

					this_connection->is_hosting = TRUE;

					break;
				}
			}
		}
		else
		{

			//command_line_comms_resend_list_size						= 1000;
			//command_line_comms_packet_data_size						= 512;
			//command_line_comms_packet_rerequest_limit				= 10;
			//command_line_comms_connection_receive_size			= (32 * 1024);
			//command_line_comms_data_record_size						= (16 * 1024);
			//command_line_comms_timeout									= (2.0 * 60.0);
			//command_line_comms_pack_buffer_size						= (200 * 1024);
			//command_line_comms_initial_sleep_time					= 500;
			//command_line_max_frame_rate								= 30;
			if (!command_line_max_game_update_rate_set)
			{

				command_line_max_game_update_rate						= 15;
			}
			//command_line_comms_resend_timeout						= 1.0;
			//command_line_comms_packet_resend_timer 				= 5.0;
		}

		initialise_comms_manager ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_connection_type_button (ui_object *obj, void *arg)
{

   service_provider_table_type
      *this_service = NULL;

	this_service = direct_play_get_service_provider_table ();

	if (current_active_service)
	{
		while (this_service)
		{
			if (memcmp (&global_options.service_provider_guid, this_service->guid, sizeof (GUID)) == 0)
			{
				this_service = this_service->next;

				break;
			}

			this_service = this_service->next;
		}
	}

	start_service_provider ( this_service );

	if ( this_service )
	{

		// set the conection type text
		if ( memncmp ( ( char * ) this_service->guid, ( char * ) &DPSPGUID_TCPIP, sizeof ( GUID ) ) == TRUE )
		{
			set_ui_object_text (obj, get_trans("MP_INTERNET"));
		}
		else if ( memncmp ( ( char * ) this_service->guid, ( char * ) &DPSPGUID_SERIAL, sizeof ( GUID ) ) == TRUE )
		{
			set_ui_object_text (obj, get_trans("MP_SERIAL"));
		}
		else if ( memncmp ( ( char * ) this_service->guid, ( char * ) &DPSPGUID_MODEM, sizeof ( GUID ) ) == TRUE )
		{
			set_ui_object_text (obj, get_trans("MP_MODEM"));				
		}
		else if ( memncmp ( ( char * ) this_service->guid, ( char * ) &DPSPGUID_IPX, sizeof ( GUID ) ) == TRUE )
		{
			set_ui_object_text (obj, get_trans("MP_IPX"));
		}
		else
		{
			set_ui_object_text (obj, this_service->name);
		}

		preprocess_translation_object_size (connection_type_bdrop, obj, NULL, 0, RESIZE_OPTION_BOX_TITLE);

		memcpy ( &global_options.service_provider_guid, this_service->guid, sizeof ( GUID ) );
	}
	else
	{
		set_ui_object_text (obj, get_trans ("MP_NO_SERVICE_PROVIDER"));

		memset ( &global_options.service_provider_guid, 0, sizeof ( GUID ) );

		preprocess_translation_object_size (connection_type_bdrop, obj, NULL, 0, RESIZE_OPTION_BOX_TITLE);
	}

	set_toggle_button_off (obj);
	
	reset_time_values (options_page [OPTIONS_PAGE_MULTIPLAYER]);

	set_multiplayer_options_display ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void start_service_provider ( service_provider_table_type *this_service )
{

	if ( this_service != current_active_service )
	{

		if ( modem_state != MODEM_NOT_CONNECTED )
		{

			break_modem_connection ();
		}

		direct_play_close_session ();

		current_active_service = this_service;
	
		if ( this_service )
		{
		
			if ( direct_play_create_interface ( this_service ) )
			{
		
				direct_play_interface_capabilities ();

				//
				// Set the override values for the service provider here.
				//

				initialise_service_provider_connection ();
			}
		}
		else
		{
	
			direct_play_destroy_interface ();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void install_global_options_service_provider (void)
{

	//
	// Install service provider
	//

   service_provider_table_type
      *this_service;

   this_service = direct_play_get_service_provider_table ();

   while ( this_service )
   {

		if ( memncmp ( ( char * ) this_service->guid, ( char * ) &global_options.service_provider_guid, sizeof ( GUID ) ) == TRUE )
		{

			start_service_provider ( this_service );

//			add_service_provider_to_connection_message_list ( this_service->name );
		}

      this_service = this_service->next;
   }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_multiplayer_options_display ( void )
{

	connection_data_type
		*this_connection;

	// Set options areas themselves

	this_connection = direct_play_get_connection_data ();

	set_ui_object_drawable ( tcpip_parameters_area, UI_OBJECT_STATE_OFF );

	set_ui_object_drawable ( serial_parameters_area, UI_OBJECT_STATE_OFF );

	set_ui_object_drawable ( modem_parameters_area, UI_OBJECT_STATE_OFF );

	if ( ( this_connection ) && ( this_connection->service_provider.guid ) )
	{

		if ( memncmp ( ( char * ) this_connection->service_provider.guid, ( char * ) &DPSPGUID_TCPIP, sizeof ( GUID ) ) == TRUE )
		{
			set_ui_object_drawable ( tcpip_parameters_area, UI_OBJECT_STATE_ON );
		}
		else if ( memncmp ( ( char * ) this_connection->service_provider.guid, ( char * ) &DPSPGUID_SERIAL, sizeof ( GUID ) ) == TRUE )
		{
			set_ui_object_drawable ( serial_parameters_area, UI_OBJECT_STATE_ON );
		}
		else if ( memncmp ( ( char * ) this_connection->service_provider.guid, ( char * ) &DPSPGUID_MODEM, sizeof ( GUID ) ) == TRUE )
		{
			set_ui_object_drawable ( modem_parameters_area, UI_OBJECT_STATE_ON );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void store_multiplayer_options (void)
{

	// Set the tcp/ip address to the one in the text area

	strncpy ( global_options.ip_address, get_ui_object_text ( ip_address_text_obj ), 127 );

	global_options.ip_address[127] = '\0';

	// Set the phone number to the one in the text area

	strncpy ( global_options.phone_number, get_ui_object_text ( phone_number_text_obj ), 127 );

	global_options.phone_number[127] = '\0';

	// Try to give the service provider all the information it needs

	if (!get_current_game_session ())
	{

		initialise_service_provider_connection ();
	}

	ui_set_user_function ( NULL );

	// Save the global options data

	save_global_options_data ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ghost_ui_objects_for_modem (ui_object *obj, int flag)
{
	int
		i;
		
	// activate ghosting
	if (flag == TRUE)
	{
		// disable common object items
		for (i = 0; i < NUM_OPTIONS_PAGES; i++)
		{
			set_ui_object_drawable (options_page_buttons [i], FALSE);
		}	

		set_ui_object_drawable (option_page_ok_button, FALSE);
	
		// disable modem objects
		set_ui_object_highlightable (connection_type_button, FALSE);
	
		set_ui_object_font_colour_end (connection_type_button, ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 127);
	
		set_ui_object_highlightable (phone_number_text_obj, FALSE);
	
		set_ui_object_font_colour_end (phone_number_text_obj, ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 127);
	
		set_ui_object_highlightable (modem_type_button, FALSE);
	
		set_ui_object_font_colour_end (modem_type_button, ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 127);

		set_ui_object_highlightable (modem_answer_button, FALSE);
	
		set_ui_object_font_colour_end (modem_answer_button, ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 127);

		set_ui_object_highlightable (modem_dial_button, FALSE);
	
		set_ui_object_font_colour_end (modem_dial_button, ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 127);
	
		// enable ghosting overlay
		set_ui_object_drawable (ghost_multiplayer_modem_area, TRUE);

		set_ui_object_drawable (ghost_multiplayer_modem_area2, TRUE);
	}
	// deactivate ghosting
	else
	{
		// enable common object items
		for (i = 0; i < NUM_OPTIONS_PAGES; i++)
		{
			set_ui_object_drawable (options_page_buttons [i], TRUE);
		}	

		set_ui_object_drawable (option_page_ok_button, TRUE);
	
		// enable modem objects
		set_ui_object_highlightable (connection_type_button, TRUE);
	
		set_ui_object_font_colour_end (connection_type_button, ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255);
	
		set_ui_object_highlightable (phone_number_text_obj, TRUE);
	
		set_ui_object_font_colour_end (phone_number_text_obj, ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255);
	
		set_ui_object_highlightable (modem_type_button, TRUE);
	
		set_ui_object_font_colour_end (modem_type_button, ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255);
	
		set_ui_object_highlightable (modem_answer_button, TRUE);
	
		set_ui_object_font_colour_end (modem_answer_button, ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255);

		set_ui_object_highlightable (modem_dial_button, TRUE);
	
		set_ui_object_font_colour_end (modem_dial_button, ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255);
	
		// disable ghosting overlay
		set_ui_object_drawable (ghost_multiplayer_modem_area, FALSE);

		set_ui_object_drawable (ghost_multiplayer_modem_area2, FALSE);
	}

	// don't leave text selected
	if (obj)
	{
		set_toggle_button_off (obj);
	}
	
//	ui_force_update ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


