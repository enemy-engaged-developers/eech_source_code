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

#include "multi.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DIRECT_PLAY_DEBUG 0

#define DEBUG_DUMP_PACKET_DATA 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DEFINE_GUID(TEST_GUID, 0x33925241, 0x5f8, 0x11d0, 0x80, 0x63, 0x0, 0xa0, 0xc9, 0xa, 0xe8, 0x91);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int
	direct_play_initialised = FALSE;

static DWORD
	direct_play_send_queue_number_of_packets = 0,
	direct_play_send_queue_number_of_bytes = 0;

static int
	group_counter = 0,
	session_counter = 0;

static connection_data_type
	connection_data;

static service_provider_table_type
	*service_provider_table= NULL;

static session_table_type
	*session_table = NULL;

static group_table_type
	*group_table = NULL;

static DPCAPS
	interface_capabilities;

static LPVOID
	session_capabilities;

static LPDIRECTPLAY4A
	direct_playx = NULL;

static LPDIRECTPLAYLOBBY3A
	direct_play_lobby3 = NULL;

static DPLCONNECTION
	*direct_play_lobby3_connection_data;

static LPVOID
	*modem_address_data;

static DWORD
	modem_address_datasize;

int
	direct_play_use_guaranteed_packets = TRUE;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_direct_play_interface ( void );

void destroy_direct_play_interface ( void );

static void direct_play_initialise_lobbies ( void );

static BOOL FAR PASCAL direct_play_enum_address_callback ( REFGUID guid, DWORD datasize, LPCVOID data, LPVOID context );

static BOOL FAR PASCAL direct_play_enumerate_connections ( LPGUID lpguidSP, LPVOID lpConnection, DWORD dwConnectionSize, LPCDPNAME lpName, DWORD flags, LPVOID context );

static BOOL FAR PASCAL direct_play_enumerate_sessions_callback (LPDPSESSIONDESC2 lpThisSD, LPDWORD lpdwTimeOut, DWORD dwFlags, LPVOID lpContext);

static BOOL WINAPI direct_play_enumerate_groups_callback (DPID dpId, DWORD dwPlayerType, LPCDPNAME lpName, DWORD dwFlagsm, LPVOID lpContext);

/*static*/ char *get_dplay_error_message (HRESULT error);

void direct_play_system_message (LPDPMSG_GENERIC type);

void direct_play_sort_session_list (void);

#if DEBUG_DUMP_PACKET_DATA

static void write_comms_data (int flag, char *data, int size);

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

direct_play_comms_mode_types
	direct_play_comms_mode = DIRECT_PLAY_COMMS_MODE_NONE;

modem_names
	*modem_name_list = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Direct play initialise function
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int direct_play_initialise_system (void)
{

	if ( !direct_play_initialised )
	{

		//
		// Register the application
		//

		memset ( &connection_data, 0, sizeof ( connection_data_type ) );

		direct_play_set_group_name ( "Unnamed Group" );

		direct_play_set_session_name ( "Unnamed Session" );

		direct_play_set_player_name ( "Unnamed Player" );

		register_exit_function ( direct_play_deinitialise_system );

		direct_play_initialised = TRUE;

		//
		// Initialise the lobby first - if there is one we don't enumerate the service providers
		//

		direct_play_initialise_lobbies ();

		direct_play_enumerate_service_providers ();

		//
		// Reset FPU mode
		//

		set_fpu_rounding_mode_zero ();

		//
		// Watch the send queue
		//

		debug_watch ( "DP SEND QUEUE PACKETS: %d", MT_INT, &direct_play_send_queue_number_of_packets );

		debug_watch ( "DP SEND QUEUE BYTES: %d", MT_INT, &direct_play_send_queue_number_of_bytes );

		return TRUE;
	}
	else
	{

		debug_log ( "DIRECTP: Attempting to initialise DirectPlay twice!" );

		return FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_direct_play_interface ( void )
{

	HRESULT
		ret;

	destroy_direct_play_interface ();

	ret = CoCreateInstance ( &CLSID_DirectPlay, NULL, CLSCTX_INPROC_SERVER, &IID_IDirectPlay4A, ( LPVOID * ) &direct_playx );

	if ( ret != 0 )
	{

		debug_fatal ( "DIRECTP: Unable to create DirectPlay4A" );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void destroy_direct_play_interface ( void )
{

	if ( direct_playx )
	{
	
		HRESULT
			ret;
	
		ret = IDirectPlayX_Release ( direct_playx );
	
		if ( ret != 0 )
		{
	
			debug_log ( "DIRECTP: Unable to release the directplay object" );
		}

		direct_playx = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void direct_play_initialise_lobbies ( void )
{

	HRESULT
		ret;

	ret = CoCreateInstance ( &CLSID_DirectPlayLobby, NULL, CLSCTX_INPROC_SERVER, &IID_IDirectPlayLobby3A, ( LPVOID * ) &direct_play_lobby3 );

	if ( ret != DP_OK )
	{

		debug_log ( "DIRECTP: Unable to create DirectPlayLobby: %s", get_dplay_error_message ( ret ) );
	}
	else
	{

		DWORD
			datasize;

		//
		// Get the connection settings - this will also tell us if we were called by a lobby
		//

		ret = IDirectPlayLobby_GetConnectionSettings ( direct_play_lobby3, 0, NULL, &datasize );

		if ( ret == DPERR_NOTLOBBIED )
		{

			//
			// Not called by a lobby - bail out now.
			//

			debug_log ( "DIRECTP: Not called by a lobby - bailing out!" );

			IDirectPlayLobby_Release ( direct_play_lobby3 );

			direct_play_lobby3 = NULL;
		}
		else
		{

			//
			// We were created by a lobby - so get the details!
			//

			direct_play_lobby3_connection_data = safe_malloc ( datasize );

			ret = IDirectPlayLobby_GetConnectionSettings ( direct_play_lobby3, 0, direct_play_lobby3_connection_data, &datasize );

			if ( ret != DP_OK )
			{

				debug_log ( "DIRECTP: Unable to get lobby connection settings: %s", get_dplay_error_message ( ret ) );
			}
			else
			{

				//
				// Got the connection settings - parse them
				//

				if ( direct_play_lobby3_connection_data->dwFlags & DPLCONNECTION_CREATESESSION )
				{

					debug_log ( "DIRECTP: Lobby says to host a game" );
				}

				if ( direct_play_lobby3_connection_data->dwFlags & DPLCONNECTION_JOINSESSION )
				{

					debug_log ( "DIRECTP: Lobby says to join a game" );
				}

				direct_play_lobby3_connection_data->lpSessionDesc->dwFlags =  DPSESSION_KEEPALIVE;

				ret = IDirectPlayLobby_SetConnectionSettings( direct_play_lobby3, 0, 0, direct_play_lobby3_connection_data );

				if ( ret != DP_OK )
				{

					debug_log ( "DIRECTP: Unable to SetConectionSettings on lobby: %s", get_dplay_error_message ( ret ) );
				}

				//
				// Now connect to the lobby's game
				//

				ret = IDirectPlayLobby_ConnectEx ( direct_play_lobby3, 0, &IID_IDirectPlay4A, &direct_playx, NULL );

				if ( ret != DP_OK )
				{

					debug_log ( "DIRECTP: Unable to connect to lobby: %s", get_dplay_error_message ( ret ) );
				}
				else
				{

					debug_log ( "DIRECTP: Connected to lobby successfully" );
				}

				direct_play_set_comms_mode ( DIRECT_PLAY_COMMS_MODE_MULTI );

				debug_log ( "Session name: %s", direct_play_lobby3_connection_data->lpSessionDesc->lpszSessionNameA );

				debug_log ( "Player name: %s", direct_play_lobby3_connection_data->lpPlayerName->lpszShortNameA );
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int direct_play_get_lobbied ( void )
{

	if ( direct_play_lobby3 )
	{

		return ( TRUE );
	}
	else
	{

		return ( FALSE );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int direct_play_get_lobbied_join ( void )
{

	ASSERT ( direct_play_lobby3 );

	if ( direct_play_lobby3_connection_data->dwFlags & DPLCONNECTION_CREATESESSION )
	{

		return ( FALSE );
	}
	else
	{

		return ( TRUE );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void direct_play_register_application ( char *app_name, char *filename )
{

	HRESULT
		ret;

	LPDIRECTPLAYLOBBY3A
		dp_lobby3;

	DPAPPLICATIONDESC
		application_description;

	char
		path[1024];

	GetCurrentDirectory ( 1024, path );

	application_description.dwSize = sizeof ( DPAPPLICATIONDESC );
	application_description.dwFlags = 0;
	application_description.lpszApplicationNameA = app_name;

	memcpy ( &application_description.guidApplication, &TEST_GUID, sizeof ( GUID ) );
	application_description.lpszFilenameA= filename;
	application_description.lpszCommandLineA= NULL;
	application_description.lpszPathA = path;
	application_description.lpszCurrentDirectoryA= path;
	application_description.lpszDescriptionA= app_name;
	application_description.lpszDescriptionW= NULL;

	ret = CoCreateInstance ( &CLSID_DirectPlayLobby, NULL, CLSCTX_INPROC_SERVER, &IID_IDirectPlayLobby3A, ( LPVOID * ) &dp_lobby3 );

	if ( ret != DP_OK )
	{

		debug_fatal ( "Unable to register %s : %s", app_name, get_dplay_error_message ( ret ) );
	}
	else
	{

		ret = IDirectPlayLobby_RegisterApplication ( dp_lobby3, 0, &application_description );

		if ( ret != DP_OK )
		{

			debug_fatal ( "Unable to register %s : %s", app_name, get_dplay_error_message ( ret ) );
		}

		IDirectPlayLobby_Release ( dp_lobby3 );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void direct_play_deinitialise_system ( void )
{

	service_provider_table_type
		*destroy_service_provider;

	//
	// Free up memory
	//

	while ( service_provider_table )
	{

		destroy_service_provider = service_provider_table;

		service_provider_table = service_provider_table->next;

		if ( destroy_service_provider->name )
		{

			safe_free ( destroy_service_provider->name );
		}

		if ( destroy_service_provider->guid )
		{

			safe_free ( destroy_service_provider->guid );
		}

		if ( destroy_service_provider->connection )
		{

			safe_free ( destroy_service_provider->connection );
		}

		safe_free ( destroy_service_provider );
	}

	//
	// Need to do other mallocs
	//

	if ( direct_play_get_comms_mode () == DIRECT_PLAY_COMMS_MODE_MULTI )
	{

		//
		// check all of these...
		//

		direct_play_leave_group ();

		direct_play_destroy_player ();

		direct_play_destroy_group ();

		direct_play_close_session ();

		destroy_direct_play_interface ();
	}

	//
	// Now clean up the interface itself
	//

	if ( direct_playx )
	{

		IDirectPlayX_Release ( direct_playx );
	}

	direct_play_initialised = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int direct_play_enumerate_service_providers ( void )
{

	HRESULT
		hr;

	service_provider_table_type
		*destroy_provider,
		*current_service_provider;

#if DIRECT_PLAY_DEBUG

	debug_log ("DIRECTP: enumerate service providers");

#endif


	//
	// clear the current service provider table
	//

	current_service_provider = service_provider_table;

	while ( current_service_provider )
	{

		destroy_provider = current_service_provider;

		current_service_provider = current_service_provider->next;

		safe_free ( destroy_provider );
	}

	service_provider_table = NULL;

	modem_name_list = NULL;

	if ( !direct_play_get_lobbied () )
	{

		create_direct_play_interface ();
	
		//
		// Now enumerate the service providers
		//
	
	#if DIRECT_PLAY_DEBUG
	
		debug_log ( "DIRECTP: Services avaliable :" );
	
	#endif
	
		hr = IDirectPlayX_EnumConnections ( direct_playx, &TEST_GUID, ( LPVOID ) direct_play_enumerate_connections,
																NULL, DPCONNECTION_DIRECTPLAY | DPCONNECTION_DIRECTPLAYLOBBY );
	
	
		if ( hr != DP_OK )
		{
	
			destroy_direct_play_interface ();
	
			debug_log ( "DIRECTP: DirectPlay::EnumConnections : %s", get_dplay_error_message ( hr ) );
	
			return FALSE;
		}
	
		destroy_direct_play_interface ();
	
		//
		// Now validate the connections
		//
	
		{
	
			service_provider_table_type
				*new_sp_list,
				*this_sp,
				*next_sp;

			new_sp_list = NULL;
	
			this_sp = service_provider_table;
	
			while ( this_sp )
			{
		
				create_direct_play_interface ();
	
				hr = IDirectPlayX_InitializeConnection ( direct_playx, this_sp->connection, 0 );

				if ( hr == DP_OK )
				{

					//
					// Check if this is the modem Service Provider
					//

					if ( memcmp ( this_sp->guid, &DPSPGUID_MODEM, sizeof ( GUID ) ) == 0 )
					{

						//
						// We have to get a list of modems from this service provider!
						//

						modem_address_datasize = 0;

						hr = IDirectPlayX_GetPlayerAddress ( direct_playx, 0, NULL, &modem_address_datasize );

						if ( hr == DPERR_BUFFERTOOSMALL )
						{

							modem_address_data = safe_malloc ( modem_address_datasize );

							hr = IDirectPlayX_GetPlayerAddress ( direct_playx, 0, modem_address_data, &modem_address_datasize );

							if ( hr != DP_OK )
							{

								debug_log ( "Unable to get player address for modem: %s", get_dplay_error_message ( hr ) );
							}
						}
						else
						{

							debug_log ( "Unable to get player address for modem: %s", get_dplay_error_message ( hr ) );
						}

						//
						// Now, if we have a modem address list, parse that
						//
				
						if ( modem_address_data )
						{
				
							HRESULT
								hr;
				
							LPDIRECTPLAYLOBBY3A
								direct_play_lobby;
					
							hr = CoCreateInstance ( &CLSID_DirectPlayLobby, NULL, CLSCTX_INPROC_SERVER, &IID_IDirectPlayLobby3A, ( LPVOID * ) &direct_play_lobby );
					
							if ( hr != DP_OK )
							{
					
								debug_log ( "DIRECTP: UNABLE TO CREATE A DIRECTPLAYLOBBY3 interface to parse modem strings" );
							}
							else
							{
				
								hr = IDirectPlayLobby_EnumAddress ( direct_play_lobby, direct_play_enum_address_callback, modem_address_data, modem_address_datasize, NULL );
				
								IDirectPlayLobby_Release ( direct_play_lobby );
							}
						}
					}

					//
					// Add this one to the new list
					//
	
					next_sp = this_sp->next;
	
					this_sp->next = new_sp_list;
	
					new_sp_list = this_sp;
	
					this_sp = next_sp;
				}
				else
				{
	
					//
					// Free up the memory associated with this sp
					//
	
					next_sp = this_sp->next;
	
					safe_free ( this_sp->name );
	
					safe_free ( this_sp->connection );
	
					safe_free ( this_sp->guid );
	
					safe_free ( this_sp );
	
					this_sp = next_sp;
				}

				destroy_direct_play_interface ();
			}
	
			service_provider_table = new_sp_list;
		}
	}
	else
	{
	
		//
		// Create a fake "lobby" service provider for the UI
		//

		service_provider_table_type
			*new_service_provider;
	
		new_service_provider = ( service_provider_table_type * ) safe_malloc ( sizeof ( service_provider_table_type ) );
	
		new_service_provider->next = service_provider_table;
	
		service_provider_table = new_service_provider;
	
		new_service_provider->guid = safe_malloc ( sizeof ( GUID ) );
	
		memcpy ( new_service_provider->guid, &TEST_GUID, sizeof ( GUID ) );
	
		new_service_provider->connection_size = 0;
	
		new_service_provider->connection = NULL;
	
		new_service_provider->name = ( char * ) safe_malloc ( ( strlen ( "DirectPlay Lobby" ) + 1 ) );
	
		sprintf ( new_service_provider->name, "%s", "DirectPlay Lobby" );
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL FAR PASCAL direct_play_enum_address_callback ( REFGUID guid, DWORD datasize, LPCVOID data, LPVOID context )
{

	if ( memcmp ( guid, &DPAID_Modem, sizeof ( GUID ) ) == 0 )
	{

		char
			*string;

		string = ( char * ) data;
	
		while ( strlen ( string ) )
		{
	
			modem_names
				*modem_name;
	
			//
			// Add this modem to the list
			//
	
			modem_name = safe_malloc ( sizeof ( modem_names ) );
	
			modem_name->name = safe_malloc ( strlen ( string ) + 1 );
	
			strcpy ( modem_name->name, string );
	
			if ( !modem_name_list )
			{
	
				modem_name->succ = NULL;
	
				modem_name_list = modem_name;
			}
			else
			{
	
				modem_name->succ = modem_name_list;
	
				modem_name_list = modem_name;
			}

			string += ( strlen ( string ) + 1 );
		}
	}

	return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL FAR PASCAL direct_play_enumerate_connections ( LPGUID lpSPGuid, LPVOID lpConnection, DWORD dwConnectionSize, LPCDPNAME lpName, DWORD flags, LPVOID context )
{

	service_provider_table_type
		*new_service_provider;

	//
	// Create an entry in the linked list of service providers
	//

	new_service_provider = ( service_provider_table_type * ) safe_malloc ( sizeof ( service_provider_table_type ) );

	new_service_provider->next = service_provider_table;

	service_provider_table = new_service_provider;

	new_service_provider->guid = safe_malloc ( sizeof ( GUID ) );

	memcpy ( new_service_provider->guid, lpSPGuid, sizeof ( GUID ) );

	new_service_provider->connection_size = dwConnectionSize;

	new_service_provider->connection = safe_malloc ( dwConnectionSize );

	memcpy ( new_service_provider->connection, lpConnection, dwConnectionSize );

	new_service_provider->name = ( char * ) safe_malloc ( ( strlen ( lpName->lpszShortNameA ) + 1 ) );

	sprintf ( new_service_provider->name, "%s", lpName->lpszShortNameA );

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int direct_play_create_interface ( service_provider_table_type *this_service )
{

	if ( !direct_play_get_lobbied () )
	{
	
		HRESULT
			hr;
	
		//
		// Create the direct play interface itself
		//
	
		create_direct_play_interface ();
	
		connection_data.service_provider.guid = safe_malloc ( sizeof ( GUID ) );
	
		connection_data.service_provider.name = safe_malloc ( strlen ( this_service->name ) + 1 );
	
		connection_data.service_provider.connection = safe_malloc ( this_service->connection_size );

		connection_data.one_way_hosting_setup = FALSE;

		connection_data.is_initialised = FALSE;

		connection_data.is_hosting = FALSE;
	
		memcpy ( connection_data.service_provider.guid, this_service->guid, sizeof ( GUID ) );
	
		memcpy ( connection_data.service_provider.name, this_service->name, ( strlen ( this_service->name ) + 1 ) );
	
		memcpy ( connection_data.service_provider.connection, this_service->connection, this_service->connection_size );
	
		direct_play_set_comms_mode ( DIRECT_PLAY_COMMS_MODE_MULTI );
	
		//
		// Initialise the connection
		//
	
		hr = IDirectPlayX_InitializeConnection ( direct_playx, connection_data.service_provider.connection, 0 );
	
		if ( hr != DP_OK )
		{
	
			debug_log ( "DIRECTP: DirectPlay::InitializeConnection : %s", get_dplay_error_message ( hr ) );
	
			return ( FALSE );
		}
	
		return ( TRUE );
	}
	else
	{

		//
		// We're lobbied - all the interfaces are already there.
		//

		direct_play_set_comms_mode ( DIRECT_PLAY_COMMS_MODE_MULTI );
	
		return ( TRUE );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int direct_play_destroy_interface ()
{

	//
	// Destroy the direct play interface itself
	//

	if ( !direct_play_get_lobbied () )
	{

		destroy_direct_play_interface ();
	}

	if ( connection_data.service_provider.guid )
	{

		safe_free ( connection_data.service_provider.guid );

		connection_data.service_provider.guid = NULL;
	}

	if ( connection_data.service_provider.name )
	{

		safe_free ( connection_data.service_provider.name );

		connection_data.service_provider.name = NULL;
	}

	if ( connection_data.service_provider.connection )
	{

		safe_free ( connection_data.service_provider.connection );

		connection_data.service_provider.connection = NULL;
	}

	direct_play_set_comms_mode ( DIRECT_PLAY_COMMS_MODE_NONE );

	return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int direct_play_close_session (void)
{

	if ( direct_playx )
	{
	
		HRESULT
			hr;
	
		hr = IDirectPlayX_Close ( direct_playx );
	
		if ( hr != DP_OK )
		{

#if DIRECT_PLAY_DEBUG
	
			debug_log ( "DIRECTP: DirectPlay::Close : %s", get_dplay_error_message ( hr ) );

#endif
	
			return ( FALSE );
		}
	}

	return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Session Functions
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int direct_play_enumerate_sessions (void)
{

	HRESULT
		hr;

	DPSESSIONDESC2
		sessionDesc;

	session_table_type
		*current_session,
		*destroy_session;

	#if DIRECT_PLAY_DEBUG

	debug_log ( "DIRECTP: enumerate sessions" );

	#endif

	if ( direct_play_get_comms_mode () != DIRECT_PLAY_COMMS_MODE_MULTI )
	{

		debug_log ( "COMMS MODE != MULTI!!!" );

		return ( FALSE );
	}

	//
	// clear the current session table
	//

	current_session = session_table;

	while ( current_session )
	{

		destroy_session = current_session;

		current_session = current_session->next_session;

		if ( destroy_session->session )
		{

			if ( !destroy_session->lobby_session )
			{
	
				if ( destroy_session->session->lpszSessionNameA )
				{
	
					safe_free ( destroy_session->session->lpszSessionNameA );
				}
			}

			safe_free ( destroy_session->session );
		}

		safe_free ( destroy_session );
	}

	session_table = NULL;

	//
	// enumerate avaliable sessions
	//

	if ( !direct_play_get_lobbied () )
	{

		if ( direct_playx )
		{
	
			#if DIRECT_PLAY_DEBUG
		
			debug_log ( "DIRECTP: Enumerating sessions avaliable:" );
		
			#endif
		
			memset ( &sessionDesc, 0, sizeof ( DPSESSIONDESC2 ) );
		
			sessionDesc.dwSize = sizeof ( DPSESSIONDESC2 );
		
			sessionDesc.guidApplication = TEST_GUID;
		
			hr = IDirectPlayX_EnumSessions ( direct_playx, &sessionDesc, 0,
															( LPDPENUMSESSIONSCALLBACK2 ) direct_play_enumerate_sessions_callback,
															NULL,
															DPENUMSESSIONS_ASYNC );
	//														DPENUMSESSIONS_RETURNSTATUS | DPENUMSESSIONS_AVAILABLE | DPENUMSESSIONS_ASYNC );
		
			if ( hr != DP_OK )
			{
		
				debug_log ( "DIRECTP: DirectPlay::EnumSessions : %s", get_dplay_error_message ( hr ) );
			}
		}
	}
	else
	{

		if ( direct_play_get_lobbied_join () )
		{
	
			session_table_type
				*new_session;
	
			debug_log ( "Creating lobby session" );
	
			new_session = ( session_table_type * ) safe_malloc ( sizeof ( session_table_type ) );
	
			new_session->lobby_session = TRUE;
	
			new_session->next_session = session_table;
	
			session_table = new_session;
	
			new_session->session = ( LPDPSESSIONDESC2 ) safe_malloc ( sizeof ( DPSESSIONDESC2 ) );
	
			memcpy ( new_session->session, direct_play_lobby3_connection_data->lpSessionDesc, sizeof ( DPSESSIONDESC2 ) );
	
			session_counter ++;
	
			#if DIRECT_PLAY_DEBUG
	
			debug_log ("DIRECTP:      %s", new_session->session->lpszSessionNameA);
	
			#endif
	
			debug_log ( "Done" );
		}

		return TRUE;
	}

	direct_play_sort_session_list ();

	return  ( session_counter );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int direct_play_get_connection_baudrate ( void )
{

	if ( direct_playx )
	{

		DPCAPS
			caps;

		HRESULT
			hr;

		memset ( &caps, 0, sizeof ( DPCAPS ) );

		caps.dwSize = sizeof ( DPCAPS );

		hr = IDirectPlayX_GetCaps ( direct_playx, &caps, 0 );

		if ( hr == DP_OK )
		{

			return ( caps.dwHundredBaud );
		}
		else
		{

			return ( 0 );
		}
	}
	else
	{

		return ( 0 );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int direct_play_refresh_modem_session ( void )
{

	HRESULT
		hr;

	session_table_type
		*current_session,
		*destroy_session;

	//
	// clear the current session table
	//

	current_session = session_table;

	while ( current_session )
	{

		destroy_session = current_session;

		current_session = current_session->next_session;

		if ( destroy_session->session )
		{

			if ( !destroy_session->lobby_session )
			{
	
				if ( destroy_session->session->lpszSessionNameA )
				{
	
					safe_free ( destroy_session->session->lpszSessionNameA );
				}
			}

			safe_free ( destroy_session->session );
		}

		safe_free ( destroy_session );
	}

	session_table = NULL;

	//
	// enumerate avaliable sessions
	//

	if ( direct_playx )
	{

		session_table_type
			*new_session;

		int
			size;

		new_session = ( session_table_type * ) safe_malloc ( sizeof ( session_table_type ) );

		new_session->lobby_session = FALSE;

		new_session->next_session = session_table;

		session_table = new_session;

		hr = IDirectPlayX_GetSessionDesc ( direct_playx, NULL, ( LPDWORD ) &size );

		if ( hr == DPERR_BUFFERTOOSMALL )
		{
	
			new_session->session = ( LPDPSESSIONDESC2 ) safe_malloc ( size );
	
			memset ( new_session->session, 0, size );
	
			hr = IDirectPlayX_GetSessionDesc ( direct_playx, ( LPVOID ) new_session->session, ( LPDWORD ) &size );
	
			if ( hr == DP_OK )
			{
	
				session_counter ++;
			}
			else
			{
	
				debug_log ( "Directp: Refresh modem session: %s", get_dplay_error_message ( hr ) );
			}
		}
		else
		{

			debug_log ( "Unable to get session description size: %s", get_dplay_error_message ( hr ) );
		}
	}

	direct_play_sort_session_list ();

	return  ( session_counter );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// static void internal_direct_play_destroy_modem ( void *data );
static int internal_direct_play_destroy_modem ( void *data );

void direct_play_destroy_modem ( void )
{

	system_thread_function ( internal_direct_play_destroy_modem, NULL );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// void internal_direct_play_destroy_modem ( void *data )
int internal_direct_play_destroy_modem ( void *data )
{

	if ( direct_playx )
	{
	
		IDirectPlayX_Release ( direct_playx );
	
		direct_playx = NULL;
	}
	return(NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int internal_direct_play_dial_modem ( void *data );

int direct_play_dial_modem ( char *modem, char *phone_number )
{

	HRESULT
		ret;

	DPCOMPOUNDADDRESSELEMENT
		address_elements[4];

	LPVOID
		address;

	LPDIRECTPLAYLOBBY3A
		direct_play_lobby;

	DWORD
		address_size;

	int
		number_of_elements;

	session_table_type
		*current_session,
		*destroy_session;

	ASSERT ( modem );
	ASSERT ( phone_number );

	//
	// Destroy all sessions
	//

	current_session = session_table;

	while ( current_session )
	{

		destroy_session = current_session;

		current_session = current_session->next_session;

		if ( destroy_session->session )
		{

			if ( !destroy_session->lobby_session )
			{
	
				if ( destroy_session->session->lpszSessionNameA )
				{
	
					safe_free ( destroy_session->session->lpszSessionNameA );
				}
			}

			safe_free ( destroy_session->session );
		}

		safe_free ( destroy_session );
	}

	session_table = NULL;

	//
	// Create a lobby
	//

	ret = CoCreateInstance ( &CLSID_DirectPlayLobby, NULL, CLSCTX_INPROC_SERVER, &IID_IDirectPlayLobby3A, ( LPVOID * ) &direct_play_lobby );

	if ( ret != DP_OK )
	{

		debug_log ( "DIRECTP: UNABLE TO CREATE A DIRECTPLAYLOBBY3 interface" );

		return ( FALSE );
	}

	//
	// Modem needs a modem & phone number
	//

	number_of_elements = 0;

	address_elements[number_of_elements].guidDataType = DPAID_ServiceProvider;
	address_elements[number_of_elements].dwDataSize = sizeof ( GUID );
	address_elements[number_of_elements].lpData = ( LPVOID ) &DPSPGUID_MODEM;
	number_of_elements++;

	address_elements[number_of_elements].guidDataType = DPAID_Modem;
	address_elements[number_of_elements].dwDataSize = strlen ( modem ) + 1;
	address_elements[number_of_elements].lpData = modem;
	number_of_elements++;
	
	address_elements[number_of_elements].guidDataType = DPAID_Phone;
	address_elements[number_of_elements].dwDataSize = strlen ( phone_number ) + 1;
	address_elements[number_of_elements].lpData = phone_number;
	number_of_elements++;

	//
	// Find the size of memory to store the address
	//

	address_size = 0;

	ret = IDirectPlayLobby_CreateCompoundAddress ( direct_play_lobby, address_elements, number_of_elements, NULL, &address_size );

	if ( ret != DPERR_BUFFERTOOSMALL )
	{

		IDirectPlayLobby_Release ( direct_play_lobby );

		debug_log ( "DIRECTP: Unable to establish how big the compound address is" );

		return ( FALSE );
	}

	address = safe_malloc ( address_size );

	//
	// Now fill the memory with the address
	//

	ret = IDirectPlayLobby_CreateCompoundAddress ( direct_play_lobby, address_elements, number_of_elements, address, &address_size );

	if ( ret != DP_OK )
	{

		IDirectPlayLobby_Release ( direct_play_lobby );

		debug_log ( "DIRECTP: Unable to create a compound address" );

		return ( FALSE );
	}

	//
	// Release the lobby
	//

	IDirectPlayLobby_Release ( direct_play_lobby );

	//
	// Now usurp the original connection data
	//

	if ( connection_data.service_provider.connection )
	{

		safe_free ( connection_data.service_provider.connection );
	}

	connection_data.service_provider.connection = address;

	connection_data.service_provider.connection_size = address_size;

	//
	// Swap threads to the main system thread to dial the modem
	//

	return ( system_thread_function ( internal_direct_play_dial_modem, NULL ) );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int internal_direct_play_dial_modem ( void *data )
{

	HRESULT
		ret;

	DPSESSIONDESC2
		sessionDesc;

	//
	// Replace the directplay interface
	//

	create_direct_play_interface ();

	ret = IDirectPlayX_InitializeConnection ( direct_playx, connection_data.service_provider.connection, 0 );

	if ( ret != 0 )
	{

		debug_log ( "DIRECTP: Unable to initialize connection to dial modem" );

		return ( FALSE );
	}

	//
	// Now dial the phone.
	//

	memset ( &sessionDesc, 0, sizeof ( DPSESSIONDESC2 ) );

	sessionDesc.dwSize = sizeof ( DPSESSIONDESC2 );

	sessionDesc.guidApplication = TEST_GUID;

	ret = IDirectPlayX_EnumSessions ( direct_playx, &sessionDesc, 0,
													( LPDPENUMSESSIONSCALLBACK2 ) direct_play_enumerate_sessions_callback,
													NULL,
													DPENUMSESSIONS_AVAILABLE |
													DPENUMSESSIONS_ASYNC |
													DPENUMSESSIONS_RETURNSTATUS );

	if ( ret != DP_OK )
	{

		if ( ret == DPERR_CONNECTING )
		{

			return ( TRUE );
		}
		else
		{
	
			debug_log ( "DIRECTP: DirectPlay::EnumSessions : %s", get_dplay_error_message ( ret ) );
	
			return ( FALSE );
		}
	}
	else
	{
	
		return ( TRUE );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int internal_direct_play_dial_modem_status ( void *data );

HRESULT direct_play_dial_modem_status ( void )
{

	DPSESSIONDESC2
		sessionDesc;

	HRESULT
		ret;

	//
	// Now dial the phone.
	//

	memset ( &sessionDesc, 0, sizeof ( DPSESSIONDESC2 ) );

	sessionDesc.dwSize = sizeof ( DPSESSIONDESC2 );

	sessionDesc.guidApplication = TEST_GUID;

	ret = IDirectPlayX_EnumSessions ( direct_playx, &sessionDesc, 0, ( LPDPENUMSESSIONSCALLBACK2 ) direct_play_enumerate_sessions_callback,
													NULL,
													DPENUMSESSIONS_AVAILABLE |
													DPENUMSESSIONS_ASYNC |
													DPENUMSESSIONS_RETURNSTATUS );

	return ( ret );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int internal_direct_play_dial_modem_status ( void *data )
{

	DPSESSIONDESC2
		sessionDesc;

	HRESULT
		ret;

	//
	// Now dial the phone.
	//

	memset ( &sessionDesc, 0, sizeof ( DPSESSIONDESC2 ) );

	sessionDesc.dwSize = sizeof ( DPSESSIONDESC2 );
	sessionDesc.guidApplication = TEST_GUID;

	ret = IDirectPlayX_EnumSessions ( direct_playx, &sessionDesc, 0, ( LPDPENUMSESSIONSCALLBACK2 ) direct_play_enumerate_sessions_callback,
													NULL,
													DPENUMSESSIONS_AVAILABLE |
													DPENUMSESSIONS_ASYNC |
													DPENUMSESSIONS_RETURNSTATUS );

	return ( ret );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int internal_direct_play_answer_modem ( void *data );

int direct_play_answer_modem ( char *modem, int user_data )
{

	DPCOMPOUNDADDRESSELEMENT
		address_elements[4];

	LPDIRECTPLAYLOBBY3A
		direct_play_lobby;

	DWORD
		address_size;

	int
		number_of_elements;

	LPVOID
		address;

	HRESULT
		ret;

	//
	// Create a lobby
	//

	ret = CoCreateInstance ( &CLSID_DirectPlayLobby, NULL, CLSCTX_INPROC_SERVER, &IID_IDirectPlayLobby3A, ( LPVOID * ) &direct_play_lobby );

	if ( ret != DP_OK )
	{

		debug_log ( "DIRECTP: UNABLE TO CREATE A DIRECTPLAYLOBBY3 interface" );

		return ( FALSE );
	}

	//
	// Modem needs a modem & phone number
	//

	number_of_elements = 0;

	address_elements[number_of_elements].guidDataType = DPAID_ServiceProvider;
	address_elements[number_of_elements].dwDataSize = sizeof ( GUID );
	address_elements[number_of_elements].lpData = ( LPVOID ) &DPSPGUID_MODEM;
	number_of_elements++;

	if ( modem )
	{

		address_elements[number_of_elements].guidDataType = DPAID_Modem;
		address_elements[number_of_elements].dwDataSize = strlen ( modem ) + 1;
		address_elements[number_of_elements].lpData = modem;
		number_of_elements++;
	}

	//
	// Find the size of memory to store the address
	//

	ret = IDirectPlayLobby_CreateCompoundAddress ( direct_play_lobby, address_elements, number_of_elements, NULL, &address_size );

	if ( ret != DPERR_BUFFERTOOSMALL )
	{

		IDirectPlayLobby_Release ( direct_play_lobby );

		debug_log ( "DIRECTP: Unable to establish how big the compound address is" );

		return ( FALSE );
	}

	address = safe_malloc ( address_size );

	//
	// Now fill the memory with the address
	//

	ret = IDirectPlayLobby_CreateCompoundAddress ( direct_play_lobby, address_elements, number_of_elements, address, &address_size );

	if ( ret != DP_OK )
	{

		IDirectPlayLobby_Release ( direct_play_lobby );

		debug_log ( "DIRECTP: Unable to create a compound address" );

		return ( FALSE );
	}

	//
	// Release the lobby
	//

	IDirectPlayLobby_Release ( direct_play_lobby );

	//
	// Override the previous connection address
	//

	if ( connection_data.service_provider.connection )
	{

		safe_free ( connection_data.service_provider.connection );

		connection_data.service_provider.connection = address;

		connection_data.service_provider.connection_size = address_size;
	}

	//
	// Swap threads to the main system thread to open the modem
	//

	return ( system_thread_function ( internal_direct_play_answer_modem, &user_data ) );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int internal_direct_play_answer_modem ( void *data )
{

	static DPSESSIONDESC2
		sessionDesc;

	HRESULT
		ret;

	int
		*user_data;

	user_data = data;

	create_direct_play_interface ();

	ret = IDirectPlayX_InitializeConnection ( direct_playx, connection_data.service_provider.connection, 0 );

	if ( ret != 0 )
	{

		debug_log ( "DIRECTP: Unable to initialize connection for modem answering: %s", get_dplay_error_message ( ret ) );

		return ( FALSE );
	}

	if ( direct_playx )
	{

		//
		// To answer the phone - we need to open a session ( stupid, just stupid! )
		//

		memset ( &sessionDesc, 0, sizeof ( DPSESSIONDESC2 ) );
	
		sessionDesc.dwSize = sizeof ( DPSESSIONDESC2 );
		sessionDesc.dwFlags =  DPSESSION_KEEPALIVE;
		sessionDesc.dwMaxPlayers = 2;
		sessionDesc.guidApplication = TEST_GUID;
		sessionDesc.lpszSessionName = ( LPWSTR ) "Modem Session";
		sessionDesc.dwReserved1 = 0;
		sessionDesc.dwReserved2 = 0;
		sessionDesc.dwUser1 = *user_data;
		connection_data.this_session.session = &sessionDesc;
	
		if ( direct_play_use_guaranteed_packets )
		{

			sessionDesc.dwFlags |= DPSESSION_DIRECTPLAYPROTOCOL;
		}

		ret = IDirectPlayX_Open ( direct_playx, &sessionDesc, DPOPEN_CREATE | DPOPEN_RETURNSTATUS );
	
		if ( ret != DP_OK )
		{
	
			debug_log ( "DirectPlay::Open error: %s", get_dplay_error_message ( ret ) );
	
			return ( FALSE );
		}
		else
		{

			return ( TRUE );
		}
	}
	else
	{

		return ( FALSE );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int internal_direct_play_answer_modem_status ( void *data );

HRESULT direct_play_answer_modem_status ( void )
{

	//
	// Swap threads to the main system thread to open the modem
	//

	return ( system_thread_function ( internal_direct_play_answer_modem_status, NULL ) );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int internal_direct_play_answer_modem_status ( void *data )
{

	static DPSESSIONDESC2
		sessionDesc;

	HRESULT
		ret;

	//
	// To answer the phone - we need to open a session ( stupid, just stupid! )
	//

	memset ( &sessionDesc, 0, sizeof ( DPSESSIONDESC2 ) );

	sessionDesc.dwSize = sizeof ( DPSESSIONDESC2 );
	sessionDesc.dwFlags =  DPSESSION_KEEPALIVE;
	sessionDesc.guidApplication = TEST_GUID;
	sessionDesc.dwMaxPlayers = 2;
	sessionDesc.lpszSessionName = ( LPWSTR ) "Modem Session";
	connection_data.this_session.session = &sessionDesc;

	if ( direct_play_use_guaranteed_packets )
	{

		sessionDesc.dwFlags |= DPSESSION_DIRECTPLAYPROTOCOL;
	}

	ret = IDirectPlayX_Open ( direct_playx, &sessionDesc, DPOPEN_RETURNSTATUS );

	return ( ret );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL FAR PASCAL direct_play_enumerate_sessions_callback (LPDPSESSIONDESC2 lpThisSD, LPDWORD lpdwTimeOut, DWORD dwFlags, LPVOID lpContext)
{

	session_table_type
		*new_session;

	if ( dwFlags & DPESC_TIMEDOUT )
	{

		return ( FALSE );
	}

	if (lpThisSD)
	{

		new_session = (session_table_type *) safe_malloc (sizeof (session_table_type));

		new_session->lobby_session = FALSE;

		new_session->next_session = session_table;

		session_table = new_session;

		new_session->session = (LPDPSESSIONDESC2) safe_malloc (sizeof (DPSESSIONDESC2));

		memcpy (new_session->session, lpThisSD, sizeof (DPSESSIONDESC2));

		new_session->session->lpszSessionNameA = (LPSTR) safe_malloc (strlen (lpThisSD->lpszSessionNameA) + 1);

		sprintf (new_session->session->lpszSessionNameA, lpThisSD->lpszSessionNameA);

		session_counter ++;

		#if DIRECT_PLAY_DEBUG

		debug_log ("DIRECTP:      %s", new_session->session->lpszSessionNameA);

		#endif

		return TRUE;
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int direct_play_create_session ( int value )
{

	static DPSESSIONDESC2
		sessionDesc;

	HRESULT
		hr;

	if ( direct_playx )
	{
	
		//
		// Create a new session
		//
	
		memset ( &sessionDesc, 0, sizeof ( DPSESSIONDESC2 ) );
	
		sessionDesc.dwSize = sizeof ( DPSESSIONDESC2 );

		sessionDesc.dwFlags = DPSESSION_KEEPALIVE;

		if ( direct_play_use_guaranteed_packets )
		{

			sessionDesc.dwFlags |= DPSESSION_DIRECTPLAYPROTOCOL;
		}

		sessionDesc.guidApplication = TEST_GUID;
		sessionDesc.dwMaxPlayers = MAXPLAYERS;
		sessionDesc.lpszSessionName = ( LPWSTR ) connection_data.session_name;
		sessionDesc.dwReserved1 = 0;
		sessionDesc.dwReserved2 = 0;
		sessionDesc.dwUser1 = value;
		connection_data.this_session.session = &sessionDesc;
	
		hr = IDirectPlayX_Open ( direct_playx, &sessionDesc, DPOPEN_CREATE );
	
		if ( hr != DP_OK )
		{
	
			debug_log ( "DirectPlay::Open error: %s", get_dplay_error_message ( hr ) );
	
			return ( FALSE );
		}
	}

	return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void direct_play_set_session_type_and_name ( int value )
{

	if ( direct_playx )
	{
	
		HRESULT
			hr;
	
		int
			size;
	
		//
		// Get the current session description
		//
	
		hr = IDirectPlayX_GetSessionDesc ( direct_playx, NULL, ( LPDWORD ) &size );
	
		session_capabilities = ( LPVOID ) safe_malloc ( size );
	
		hr = IDirectPlayX_GetSessionDesc ( direct_playx, ( LPVOID ) session_capabilities, ( LPDWORD ) &size );
	
		if ( hr == DP_OK )
		{

			//
			// Now set the new session description
			//

			( ( LPDPSESSIONDESC2 ) session_capabilities )->dwUser1 = value;
			( ( LPDPSESSIONDESC2 ) session_capabilities )->lpszSessionName = ( LPWSTR ) connection_data.session_name;


			hr = IDirectPlayX_SetSessionDesc ( direct_playx, session_capabilities, 0 );

			if ( hr != DP_OK )
			{

				debug_log ( "Unable to set session description: %s", get_dplay_error_message ( hr ) );
			}
		}
		else
		{

			debug_log ( "Unable to set session description: %s", get_dplay_error_message ( hr ) );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int direct_play_join_session (void)
{

	HRESULT
		hr;

	DPSESSIONDESC2
		sessionDesc;

	if ( !direct_play_get_lobbied () )
	{
	
		//
		// After enumerating the avaliable sessions, join one
		//
	
		if ( connection_data.this_session.session )
		{
	
			memset ( &sessionDesc, 0, sizeof ( DPSESSIONDESC2 ) );
	
			sessionDesc.dwSize = sizeof ( DPSESSIONDESC2 );
	
			sessionDesc.guidInstance = connection_data.this_session.session->guidInstance;
	
			sessionDesc.guidApplication = connection_data.this_session.session->guidApplication;
	
			hr = IDirectPlayX_Open ( direct_playx, &sessionDesc, DPOPEN_JOIN );
	
			if ( hr != DP_OK )
			{
	
				debug_log ( "DIRECTP: DirectPlay::Open : %s", get_dplay_error_message ( hr ) );
	
				return ( FALSE );
			}
	
	
			direct_play_set_session_name ( ( char * ) connection_data.this_session.session->lpszSessionName );
	
	#if DIRECT_PLAY_DEBUG
	
			debug_log ( "DIRECTP: Joining Session %s", connection_data.this_session.session->lpszSessionName );
	
	#endif
	
			return TRUE;
		}
		else
		{

			debug_log ( "Attempting to join a direct play session, but session is not set" );
	
			return ( FALSE );
		}
	}
	else
	{

		debug_log ( "Joining lobbied game" );

		return ( TRUE );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int direct_play_interface_capabilities (void)
{

	HRESULT
		hr;

	if ( direct_play_get_comms_mode () != DIRECT_PLAY_COMMS_MODE_MULTI )
	{

		return ( FALSE );
	}

	interface_capabilities.dwSize = sizeof (DPCAPS);

	hr = IDirectPlayX_GetCaps ( direct_playx, &interface_capabilities, 0 );

	if ( hr != DP_OK )
	{

		debug_log ( "DIRECTP: DirectPlay::GetCaps : %s", get_dplay_error_message ( hr ) );

		return ( FALSE );
	}

	#if DIRECT_PLAY_DEBUG

	debug_log ( "DIRECTP: Session Capabilities:" );

	debug_log ( "DIRECTP:      Max Players : %d", interface_capabilities.dwMaxPlayers );

	debug_log ( "DIRECTP:      Max Buffer  : %d", interface_capabilities.dwMaxBufferSize );

	debug_log ( "DIRECTP:      Max QueueSz : %d", interface_capabilities.dwMaxQueueSize );

	debug_log ( "DIRECTP:      Baud Rate   : %d", interface_capabilities.dwHundredBaud );

	debug_log ( "DIRECTP:      Latency     : %d", interface_capabilities.dwLatency );

	debug_log ( "DIRECTP:      Local Plyrs : %d", interface_capabilities.dwMaxLocalPlayers );

	debug_log ( "DIRECTP:      TimeOut     : %d", interface_capabilities.dwTimeout );

	#endif

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DPCAPS *direct_play_get_interface_capabilities (void)
{

	return &interface_capabilities;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int direct_play_session_capabilities (void)
{

	HRESULT
		hr;

	int
		size;

	if ( direct_play_get_comms_mode () != DIRECT_PLAY_COMMS_MODE_MULTI )
	{

		return FALSE;
	}

	hr = IDirectPlayX_GetSessionDesc ( direct_playx, NULL, ( LPDWORD ) &size );

	session_capabilities = ( LPVOID ) safe_malloc ( size );

	hr = IDirectPlayX_GetSessionDesc ( direct_playx, ( LPVOID ) session_capabilities, ( LPDWORD ) &size );

	if ( hr != DP_OK )
	{

		debug_log ( "DIRECTP: DirectPlay::GetSessionDesc : %s", get_dplay_error_message ( hr ) );

		return ( FALSE );
	}

	#if DIRECT_PLAY_DEBUG

	debug_log ( "DIRECTP: Session Capabilities:");

	debug_log ( "DIRECTP:      Max Players : %d", ((LPDPSESSIONDESC2) session_capabilities)->dwMaxPlayers);

	debug_log ( "DIRECTP:      Num Players : %d", ((LPDPSESSIONDESC2) session_capabilities)->dwCurrentPlayers);

	#endif

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int direct_play_session_players (void)
{

	direct_play_session_capabilities ();

	return ( ( LPDPSESSIONDESC2 ) session_capabilities )->dwCurrentPlayers;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LPDPSESSIONDESC2 direct_play_get_session_capabilities (void)
{

	return session_capabilities;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Group functions
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int direct_play_enumerate_groups (void)
{

	HRESULT
		hr;

	#if DIRECT_PLAY_DEBUG

	debug_log ("DIRECTP: enumerate groups");

	#endif

	if ( direct_play_get_comms_mode () != DIRECT_PLAY_COMMS_MODE_MULTI )
	{

		return ( FALSE );
	}

	//
	// enumerate avaliable groups
	//

	if ( connection_data.this_session.session )
	{

		group_counter = 0;

		hr = IDirectPlayX_EnumGroups ( direct_playx, &connection_data.this_session.session->guidInstance, ( LPDPENUMPLAYERSCALLBACK2 ) direct_play_enumerate_groups_callback, NULL, 0 );

		if ( hr != DP_OK )
		{

			debug_log ( "DIRECTP: DirectPlay::EnumGroups : %s", get_dplay_error_message ( hr ) );

			return ( FALSE );
		}
	}

	return ( group_counter );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL WINAPI direct_play_enumerate_groups_callback (DPID dpId, DWORD dwPlayerType, LPCDPNAME lpName, DWORD dwFlagsm, LPVOID lpContext)
{

	group_table_type
		*new_group;

	if (dwPlayerType == DPPLAYERTYPE_GROUP)
	{

		group_counter ++;

		new_group = (group_table_type *) safe_malloc (sizeof (group_table_type));

		new_group->next_group = group_table;

		group_table = new_group;

		new_group->group = dpId;

		new_group->group_name = (char *) safe_malloc (strlen ( (char *) lpName->lpszShortName) + 1);

		sprintf (new_group->group_name, "%s", lpName->lpszShortName);

		#if DIRECT_PLAY_DEBUG

		debug_log ("DIRECTP:      %s (id:%d)", lpName->lpszShortName, dpId);

		#endif

		return TRUE;
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int direct_play_create_group (void)
{

	if ( direct_playx )
	{
	
		HRESULT
			hr;
	
		DPID
			id;
	
		DPNAME
			dpName;
	
		static group_table_type
			new_group;
	
#if DIRECT_PLAY_DEBUG

		debug_log ( "DIRECTP: DirectPlay::CreateGroup" );

#endif

		memset ( &dpName, 0, sizeof ( DPNAME ) );
	
		dpName.dwSize = sizeof ( DPNAME );
	
		dpName.lpszShortName = ( LPWSTR ) direct_play_get_group_name ();
	
		dpName.lpszLongName = ( LPWSTR ) direct_play_get_group_name ();
	
		hr = IDirectPlayX_CreateGroup ( direct_playx, &id, &dpName, NULL, 0, 0 );
	
		direct_play_set_group_id ( id );
	
		new_group.group = direct_play_get_group_id ();
	
		new_group.group_name = ( char * ) safe_malloc ( strlen ( direct_play_get_group_name () ) + 1 );
	
		sprintf ( new_group.group_name, "%s", direct_play_get_group_name () );
	
		connection_data.this_group = &new_group;
	
		if ( hr != DP_OK )
		{
	
			debug_log ( "DirectPlay::CreateGroup error: %s", get_dplay_error_message ( hr ) );
	
			return ( FALSE );
		}

		return ( TRUE );
	}

	return ( FALSE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int direct_play_join_group (void)
{

	HRESULT
		hr;


	if ( connection_data.this_group )
	{

		direct_play_set_group_id ( connection_data.this_group->group );

		hr = IDirectPlayX_AddPlayerToGroup ( direct_playx, direct_play_get_group_id (), direct_play_get_player_id () );

		if ( hr == DP_OK )
		{

			debug_log ( "DIRECTP: DirectPlay::AddPlayerToGroup: %s", get_dplay_error_message ( hr ) );

			return FALSE;
		}
		
		#if DIRECT_PLAY_DEBUG

		debug_log ("DIRECTP: Joining Group %s", connection_data.this_group->group_name);

		#endif

		direct_play_set_group_name (connection_data.this_group->group_name);

		return ( TRUE );
	}
	else
	{

		debug_log ( "DIRECTP: Direct Play: join group - no group set" );

		return ( FALSE );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int direct_play_leave_group (void)
{

	HRESULT
		hr;

	if ( direct_playx )
	{
	
		if ( connection_data.this_group )
		{
	
			if ( connection_data.this_group->group )
			{
		
				#if DIRECT_PLAY_DEBUG
		
				debug_log ("DIRECTP: DirectPlay:: Deleting Player from group" );
		
				#endif
		
				hr = IDirectPlayX_DeletePlayerFromGroup ( direct_playx, connection_data.this_group->group, direct_play_get_player_id () );
		
				if ( hr != DP_OK )
				{
		
					debug_log ( "DIRECTP: DirectPlay::DeletePlayerFromGroup: %s", get_dplay_error_message ( hr ) );
		
					return FALSE;
				}
		
				return ( TRUE );
			}
			else
			{
	
				return ( FALSE );
			}
		}
		else
		{
	
			debug_log ("DIRECTP: LEAVE GROUP : no group set");
	
			return ( FALSE );
		}
	}
	else
	{

		return ( FALSE );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int direct_play_remove_player_from_group (DPID id)
{

	HRESULT
		hr;

	if ( direct_playx )
	{
	
		if ( connection_data.this_group )
		{
	
			if ( connection_data.this_group->group )
			{
		
				#if DIRECT_PLAY_DEBUG
		
				debug_log ("DIRECTP: DirectPlay:: Deleting Player from group" );
		
				#endif
		
				hr = IDirectPlayX_DeletePlayerFromGroup ( direct_playx, connection_data.this_group->group, id );
		
				if ( hr != DP_OK )
				{
		
					debug_log ( "DIRECTP: DirectPlay::DeletePlayerFromGroup: %s", get_dplay_error_message ( hr ) );
		
					return FALSE;
				}
		
				return ( TRUE );
			}
			else
			{
	
				return ( FALSE );
			}
		}
		else
		{
	
			debug_log ("DIRECTP: LEAVE GROUP : no group set");
	
			return ( FALSE );
		}
	}
	else
	{

		return ( FALSE );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int direct_play_destroy_group (void)
{

	if ( direct_playx )
	{
	
		HRESULT
			hr;
	
		#if DIRECT_PLAY_DEBUG

		debug_log ("DIRECTP: DirectPlay:: Destroy group" );

		#endif

		hr = IDirectPlayX_DestroyGroup ( direct_playx, direct_play_get_group_id () );
	
		if ( hr != DP_OK )
		{
	
			debug_log ( "DIRECTP: DirectPlay::DestroyGroup: %s", get_dplay_error_message ( hr ) );
	
			return FALSE;
		}
	}

	return ( TRUE );
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Player functions
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int direct_play_create_player (void)
{

	if ( direct_playx )
	{
	
		DPNAME
			dpName;
	
		HRESULT
			hr;
	
		DPID
			id;
	
		//
		// create a new player.
		//
	
		#if DIRECT_PLAY_DEBUG

		debug_log ("DIRECTP: DirectPlay:: Create player" );

		#endif

		memset ( &dpName, 0, sizeof ( DPNAME ) );
	
		dpName.dwSize = sizeof ( DPNAME );
	
		dpName.lpszShortName = ( LPWSTR ) connection_data.player_name;
	
		dpName.lpszLongNameA = NULL;
	
		hr = IDirectPlayX_CreatePlayer ( direct_playx, &id, &dpName, NULL, NULL, 0, 0 );
	
		if ( hr != DP_OK )
		{
	
			debug_log ( "DIRECTP: DirectPlay::CreatePlayer: %s", get_dplay_error_message ( hr ) );
	
			return ( FALSE );
		}
	
		direct_play_set_player_id (id);
	
		return ( TRUE );
	}

	return ( FALSE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int direct_play_create_server_player (void)
{

	if ( direct_playx )
	{
	
		DPNAME
			dpName;
	
		HRESULT
			hr;
	
		DPID
			id;
	
		//
		// create a new player.
		//
	
		#if DIRECT_PLAY_DEBUG

		debug_log ("DIRECTP: DirectPlay:: Create player" );

		#endif

		memset ( &dpName, 0, sizeof ( DPNAME ) );
	
		dpName.dwSize = sizeof ( DPNAME );
	
		dpName.lpszShortName = ( LPWSTR ) connection_data.player_name;
	
		dpName.lpszLongNameA = NULL;
	
		hr = IDirectPlayX_CreatePlayer ( direct_playx, &id, &dpName, NULL, NULL, 0, DPPLAYER_SERVERPLAYER );
	
		if ( hr != DP_OK )
		{
	
			debug_log ( "DIRECTP: DirectPlay::CreatePlayer: %s", get_dplay_error_message ( hr ) );
	
			return ( FALSE );
		}
	
		direct_play_set_player_id (id);
	
		return ( TRUE );
	}

	return ( FALSE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int direct_play_destroy_player (void)
{

	if ( direct_playx )
	{
	
		HRESULT
			hr;
	
		#if DIRECT_PLAY_DEBUG

		debug_log ("DIRECTP: DirectPlay:: Destroy player" );

		#endif

		hr = IDirectPlayX_DestroyPlayer ( direct_playx, direct_play_get_player_id () );
	
		if ( hr != DP_OK )
		{
	
			debug_log ( "DIRECTP: DirectPlay::DestroyPlayer: %s", get_dplay_error_message ( hr ) );
	
			return ( FALSE );
		}
	
		return ( TRUE );
	}

	return ( FALSE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void direct_play_get_message_queue ( void )
{

	if ( direct_playx )
	{
	
		IDirectPlayX_GetMessageQueue ( direct_playx, 0, 0, DPMESSAGEQUEUE_SEND, &direct_play_send_queue_number_of_packets, &direct_play_send_queue_number_of_bytes );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Send and Receive functions
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int direct_play_send_data ( DPID to_id, LPVOID data, int size )
{

	HRESULT
		hr;

	if ( direct_play_get_comms_mode () != DIRECT_PLAY_COMMS_MODE_MULTI )
	{

		return ( 0 );
	}

#if DIRECT_PLAY_DEBUG

	debug_log ("DIRECTP: send data, id %d, size %d", to_id, size);

#endif

	if ( direct_play_use_guaranteed_packets )
	{

		hr = IDirectPlayX_SendEx ( direct_playx, direct_play_get_player_id (), to_id,
												DPSEND_GUARANTEED | DPSEND_ASYNC, data, size, 32767, 0, NULL, NULL );
	}
	else
	{
	
		hr = IDirectPlayX_Send ( direct_playx, direct_play_get_player_id (), to_id, 0, data, size );
	}

	if ( ( hr != DP_OK ) && ( hr != DPERR_PENDING ) )
	{

		debug_log ( "DIRECTP: DirectPlay::Send: %s", get_dplay_error_message ( hr ) );
		debug_log ( "Direct_playx = %08x, from id: %d, to id: %d, data: %08x, size: %d", direct_playx, direct_play_get_player_id (), to_id, data, size );

		return ( hr );
	}

#if DEBUG_DUMP_PACKET_DATA

	write_comms_data (FALSE, data, size);

#endif

	IDirectPlayX_GetMessageQueue ( direct_playx, 0, 0, DPMESSAGEQUEUE_SEND, &direct_play_send_queue_number_of_packets, &direct_play_send_queue_number_of_bytes );

	return ( 0 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int direct_play_receive_data (LPVOID data, int size)
{

	HRESULT
		hr;

	DPID
		sender_player_id,
		receiver_player_id;

	LPDPMSG_GENERIC
		type;

	int
		s1;

	if ( !direct_playx )
	{

		return ( FALSE );
	}

	if ( direct_play_get_comms_mode () != DIRECT_PLAY_COMMS_MODE_MULTI )
	{

		return ( FALSE );
	}

	//
	// Get message queue status
	//

	IDirectPlayX_GetMessageQueue ( direct_playx, 0, 0, DPMESSAGEQUEUE_SEND, &direct_play_send_queue_number_of_packets, &direct_play_send_queue_number_of_bytes );

	sender_player_id = DPID_SYSMSG;

	while ( sender_player_id == DPID_SYSMSG )
	{
	
		s1 = size;
	
		hr = IDirectPlayX_Receive ( direct_playx, &sender_player_id, &receiver_player_id, DPRECEIVE_ALL, ( LPVOID ) data, ( LPDWORD ) &s1 );
	
		//
		// If data was set to NULL, it was a request for the packet size so just return size
		//
	
		if ( data == NULL )
		{
	
			return ( s1 );
		}
	
		if ( hr != DP_OK )
		{
	
			if ( hr != DPERR_NOMESSAGES )
			{
	
				debug_log ( "DIRECTP: DirectPlay::Receive: %s", get_dplay_error_message ( hr ) );
			}
	
			return ( FALSE );
		}

		if ( sender_player_id == DPID_SYSMSG )
		{
	
			type = ( LPDPMSG_GENERIC ) data;
	
			direct_play_system_message ( type );
		}
	}

#if DIRECT_PLAY_DEBUG

	debug_log ("DIRECTP: receive, id %d, size %d", sender_player_id, s1);

#endif

#if DEBUG_DUMP_PACKET_DATA

	write_comms_data (TRUE, data, size);

#endif

	return ( s1 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Access functions etc...
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void direct_play_set_group_name (char *name)
{

	int
		length;

	if (name)
	{

		if (connection_data.group_name)
		{

			safe_free (connection_data.group_name);

			connection_data.group_name = NULL;
		}

		length = strlen (name) + 1;

		connection_data.group_name = (char *) safe_malloc (length);

		sprintf (connection_data.group_name ,"%s", name);
	}
	else
	{

		length = strlen ("No Name") + 1;

		connection_data.group_name = (char *) safe_malloc (length);

		sprintf (connection_data.group_name, "No Name");
	}

	#if DIRECT_PLAY_DEBUG

	debug_log ("DIRECTP: set group name %s", connection_data.group_name);

	#endif

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void direct_play_set_session_name (char *name)
{

	int
		length;

	if (name)
	{

		if (connection_data.session_name)
		{

			safe_free (connection_data.session_name);

			connection_data.session_name = NULL;
		}

		length = strlen (name) + 1;

		connection_data.session_name = (char *) safe_malloc (length);

		sprintf (connection_data.session_name ,"%s", name);
	}
	else
	{

		length = strlen ("No Name") + 1;

		connection_data.session_name = (char *) safe_malloc (length);

		sprintf (connection_data.session_name, "No Name");
	}

	#if DIRECT_PLAY_DEBUG

	debug_log ("DIRECTP: set session name %s", connection_data.session_name);

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void direct_play_set_player_name (char *name)
{

	int
		length;

	if (name)
	{

		if (connection_data.player_name)
		{

			safe_free (connection_data.player_name);

			connection_data.player_name = NULL;
		}

		length = strlen (name) + 1;

		connection_data.player_name = (char *) safe_malloc (length);

		sprintf (connection_data.player_name, "%s", name);
	}
	else
	{

		length = strlen ("No Name") + 1;

		connection_data.player_name = (char *) safe_malloc (length);

		sprintf (connection_data.player_name, "No Name");
	}

	#if DIRECT_PLAY_DEBUG

	debug_log ("DIRECTP: set player name %s", connection_data.player_name);

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char *direct_play_get_group_name (void)
{

	return connection_data.group_name;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char *direct_play_get_session_name (void)
{

	return connection_data.session_name;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char *direct_play_get_player_name (DPID player_id)
{

	int
		size,
		hr;

	void
		*data;

	char
		*name;

	LPDPNAME
		dp_name;

	size = 0;

	hr = IDirectPlayX_GetPlayerName (direct_playx, player_id, NULL, (LPDWORD) &size);

	if ( hr == DPERR_BUFFERTOOSMALL )
	{

		data = (void *) safe_malloc (size);

		hr = IDirectPlayX_GetPlayerName (direct_playx, player_id, data, (LPDWORD) &size);

		if ( hr != DP_OK )
		{

			debug_log ( "DPERR: Unable to get player name: %s", get_dplay_error_message ( hr ) );
		}
	}
	else
	{

		debug_log ( "DPERR: Unable to get player name size: %s", get_dplay_error_message ( hr ) );
	}

	dp_name = ( LPDPNAME ) data;

	name = safe_malloc ( strlen ( dp_name->lpszShortNameA ) + 1 );

	strcpy ( name, dp_name->lpszShortNameA );

	safe_free ( data );

	return name;

	//return connection_data.player_name;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int direct_play_get_number_of_players (void)
{

	HRESULT
		hr;

	LPVOID
		data;

	int
		size;

	if ( direct_play_get_comms_mode () != DIRECT_PLAY_COMMS_MODE_MULTI )
	{

		return FALSE;
	}

	IDirectPlayX_GetSessionDesc ( direct_playx, NULL, ( LPDWORD ) &size );

	data = ( LPVOID ) safe_malloc ( size );

	hr = IDirectPlayX_GetSessionDesc ( direct_playx, ( LPVOID ) data, ( LPDWORD ) &size );

	if ( hr != DP_OK )
	{

		return ( FALSE );
	}

	return ( ( ( LPDPSESSIONDESC2 ) data )->dwCurrentPlayers );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void direct_play_set_group_id (int id)
{

	#if DIRECT_PLAY_DEBUG

	debug_log ("DIRECTP: set group id %d", id);

	#endif

	connection_data.group_id = id;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void direct_play_set_player_id (int id)
{

	#if DIRECT_PLAY_DEBUG

	debug_log ("DIRECTP: set player id %d", id);

	#endif

	connection_data.player_id = id;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int direct_play_get_group_id (void)
{

	return connection_data.group_id;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int direct_play_get_player_id (void)
{

	return connection_data.player_id;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

session_table_type *direct_play_get_session_table (void)
{

	return session_table;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

service_provider_table_type *direct_play_get_service_provider_table (void)
{

	return service_provider_table;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

group_table_type *direct_play_get_group_table (void)
{

	return group_table;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

connection_data_type *direct_play_get_connection_data (void)
{

	return &connection_data;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void direct_play_set_service_provider (LPGUID this_service)
{

	connection_data.service_provider.guid = this_service;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DEBUGGING FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void direct_play_system_message (LPDPMSG_GENERIC type)
{

	#if DIRECT_PLAY_DEBUG

	char
		buffer [200];

	debug_log ( "Got Direct Play System Message" );

	switch ( type->dwType )
	{

		case DPSYS_CREATEPLAYERORGROUP:
		{

			debug_log ( "DP: DPSYS_CREATEPLAYERORGROUP" );
			break;
		}

		case DPSYS_DESTROYPLAYERORGROUP:
		{

			debug_log ( "DP: DPSYS_DESTROYPLAYERORGROUP" );
			break;
		}

		case DPSYS_ADDPLAYERTOGROUP:
		{

			debug_log ( "DP: DPSYS_ADDPLAYERTOGROUP" );
			break;
		}

		case DPSYS_DELETEPLAYERFROMGROUP:
		{

			debug_log ( "DP: DPSYS_DELETEPLAYERFROMGROUP" );
			break;
		}

		case DPSYS_SESSIONLOST:
		{

			debug_log ( "DP: DPSYS_SESSIONLOST" );
			break;
		}

		case DPSYS_HOST:
		{

			debug_log ( "DP: DPSYS_HOST" );
			break;
		}

		case DPSYS_SETPLAYERORGROUPDATA:
		{

			debug_log ( "DP: DPSYS_SETPLAYERORGROUPDATA" );
			break;
		}

		case DPSYS_SETPLAYERORGROUPNAME:
		{

			debug_log ( "DP: DPSYS_SETPLAYERORGROUPNAME" );
			break;
		}

		case DPSYS_SETSESSIONDESC:
		{

			debug_log ( "DP: DPSYS_SETSESSIONDESC" );
			break;
		}

		case DPSYS_ADDGROUPTOGROUP:
		{

			debug_log ( "DP: DPSYS_ADDGROUPTOGROUP" );
			break;
		}

		case DPSYS_DELETEGROUPFROMGROUP:
		{

			debug_log ( "DP: DPSYS_DELETEGROUPFROMGROUP" );
			break;
		}

		case DPSYS_SECUREMESSAGE:
		{

			debug_log ( "DP: DPSYS_SECUREMESSAGE" );
			break;
		}

		case DPSYS_STARTSESSION:
		{

			debug_log ( "DP: DPSYS_STARTSESSION" );
			break;
		}

		case DPSYS_CHAT:
		{

			debug_log ( "DP: DPSYS_CHAT" );
			break;
		}

		case DPSYS_SETGROUPOWNER:
		{

			debug_log ( "DP: DPSYS_SETGROUPOWNER" );
			break;
		}

		case DPSYS_SENDCOMPLETE:
		{

			debug_log ( "DP: DPSYS_SENDCOMPLETE" );
			break;
		}
	}


	switch (type->dwType)
	{

		case DPSYS_ADDPLAYERTOGROUP:
		{

			debug_log ("DIRECTP: SYSTEM MESSAGE : Add player %d to group %d",
							((LPDPMSG_ADDPLAYERTOGROUP) type)->dpIdPlayer,
							((LPDPMSG_ADDPLAYERTOGROUP) type)->dpIdGroup);

			break;
		}
		case DPSYS_CREATEPLAYERORGROUP:
		{

			if (((LPDPMSG_CREATEPLAYERORGROUP) type)->dwPlayerType == DPPLAYERTYPE_PLAYER)
			{

				debug_log ("DIRECTP: SYSTEM MESSAGE : Create player %d",
							((LPDPMSG_CREATEPLAYERORGROUP) type)->dpId);
			}
			else
			{

				debug_log ("DIRECTP: SYSTEM MESSAGE : Create group %d",
							((LPDPMSG_CREATEPLAYERORGROUP) type)->dpId);
			}

			break;
		}
		case DPSYS_DELETEPLAYERFROMGROUP:
		{

			debug_log ("DIRECTP: SYSTEM MESSAGE : Delete player %d from group %d",
							((LPDPMSG_DELETEPLAYERFROMGROUP) type)->dpIdPlayer,
							((LPDPMSG_DELETEPLAYERFROMGROUP) type)->dpIdGroup);

			break;
		}
		case DPSYS_DESTROYPLAYERORGROUP:
		{

			if (((LPDPMSG_DESTROYPLAYERORGROUP) type)->dwPlayerType == DPPLAYERTYPE_PLAYER)
			{

				debug_log ("DIRECTP: SYSTEM MESSAGE : Destroy player %d",
							((LPDPMSG_DESTROYPLAYERORGROUP) type)->dpId);
			}
			else
			{

				debug_log ("DIRECTP: SYSTEM MESSAGE : Destroy group %d",
							((LPDPMSG_DESTROYPLAYERORGROUP) type)->dpId);
			}

			break;
		}
		case DPSYS_HOST:
		{

			debug_log ("DIRECTP: SYSTEM MESSAGE : No host");

			break;
		}
		case DPSYS_SESSIONLOST:
		{

			debug_log ("DIRECTP: SYSTEM MESSAGE : session lost");

			break;
		}
		case DPSYS_SETPLAYERORGROUPDATA:
		{

			if (((LPDPMSG_SETPLAYERORGROUPDATA) type)->dwPlayerType == DPPLAYERTYPE_PLAYER)
			{

				debug_log ("DIRECTP: SYSTEM MESSAGE : Set player data");
			}
			else
			{

				debug_log ("DIRECTP: SYSTEM MESSAGE : Set group data");
			}

			break;
		}
		case DPSYS_SETPLAYERORGROUPNAME:
		{

			if (((LPDPMSG_SETPLAYERORGROUPNAME) type)->dwPlayerType == DPPLAYERTYPE_PLAYER)
			{

				debug_log ("DIRECTP: SYSTEM MESSAGE : Set player name");
			}
			else
			{

				debug_log ("DIRECTP: SYSTEM MESSAGE : Set group name");
			}

			break;
		}
		default:
		{

			sprintf (buffer, "DIRECTP: SYSTEM MESSAGE : unknown %d", type);

			debug_log (buffer);

			break;
		}
	}

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void direct_play_sort_session_list (void)
{

	session_table_type
		*prev_session,
		*next_session,
		*current_session;

	current_session = session_table;

	prev_session = NULL;

	while (current_session)
	{

		next_session = current_session->next_session;

		if (!next_session)
		{

			return;
		}

		//
		// compare names and swap if required
		//

		if (stricmp (current_session->session->lpszSessionNameA, next_session->session->lpszSessionNameA) < 0)
		{

			if (prev_session)
			{

				prev_session->next_session = next_session;
			}
			else
			{

				session_table = next_session;
			}

			current_session->next_session = next_session->next_session;

			next_session->next_session = current_session;

			current_session = session_table;

			prev_session = NULL;

			continue;
		}

		prev_session = current_session;

		current_session = next_session;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_direct_play_inet_address ( char *ip_address )
{

	if ( direct_playx )
	{

		HRESULT
			ret;
	
		DPCOMPOUNDADDRESSELEMENT
			address_elements[3];

		LPVOID
			address;

		LPDIRECTPLAYLOBBY3A
			direct_play_lobby;

		DWORD
			address_size;

		//
		// Create a lobby
		//

		ret = CoCreateInstance ( &CLSID_DirectPlayLobby, NULL, CLSCTX_INPROC_SERVER, &IID_IDirectPlayLobby3A, ( LPVOID * ) &direct_play_lobby );

		if ( ret != DP_OK )
		{

			debug_log ( "DIRECTP: UNABLE TO CREATE A DIRECTPLAYLOBBY3 interface" );

			return;
		}

		//
		// TCP/IP needs a service provider, an IP address, and optional port number
		//

		address_elements[0].guidDataType = DPAID_ServiceProvider;
		address_elements[0].dwDataSize = sizeof ( GUID );
		address_elements[0].lpData = ( LPVOID ) &DPSPGUID_TCPIP;

		address_elements[1].guidDataType = DPAID_INet;
		address_elements[1].dwDataSize = strlen ( ip_address ) + 1;
		address_elements[1].lpData = ip_address;

		//
		// Find the size of memory to store the address
		//

		ret = IDirectPlayLobby_CreateCompoundAddress ( direct_play_lobby, address_elements, 2, NULL, &address_size );

		if ( ret != DPERR_BUFFERTOOSMALL )
		{

			IDirectPlayLobby_Release ( direct_play_lobby );

			debug_log ( "DIRECTP: Unable to establish how big the compound address is" );

			return;
		}

		address = safe_malloc ( address_size );

		//
		// Now fill the memory with the address
		//

		ret = IDirectPlayLobby_CreateCompoundAddress ( direct_play_lobby, address_elements, 2, address, &address_size );

		if ( ret != DP_OK )
		{

			IDirectPlayLobby_Release ( direct_play_lobby );

			debug_log ( "DIRECTP: Unable to create a compound address" );

			return;
		}

		//
		// Now usurp the original connection data
		//

		if ( connection_data.service_provider.connection )
		{

			if ( connection_data.service_provider.connection )
			{

				safe_free ( connection_data.service_provider.connection );

				connection_data.service_provider.connection = address;

				connection_data.service_provider.connection_size = address_size;
			}

			//
			// Replace the directplay interface
			//

			create_direct_play_interface ();

			ret = IDirectPlayX_InitializeConnection ( direct_playx, connection_data.service_provider.connection, 0 );

			if ( ret != 0 )
			{

				debug_log ( "DIRECTP: Unable to initialize connection on the new IP address" );
			}
		}

		IDirectPlayLobby_Release ( direct_play_lobby );

		debug_log ( "DIRECTP: CREATED A COMPOUND ADDRESS FOR THE TCPIP SERVICE PROVIDER!" );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_direct_play_serial_address ( int com_port, int baud_rate, int stop_bits, int parity, int flow )
{

	if ( direct_playx )
	{

		HRESULT
			ret;
	
		DPCOMPOUNDADDRESSELEMENT
			address_elements[3];

		LPVOID
			address;

		LPDIRECTPLAYLOBBY3A
			direct_play_lobby;

		DWORD
			address_size;

		DPCOMPORTADDRESS
			com_port_address;

		//
		// Create a lobby
		//

		ret = CoCreateInstance ( &CLSID_DirectPlayLobby, NULL, CLSCTX_INPROC_SERVER, &IID_IDirectPlayLobby3A, ( LPVOID * ) &direct_play_lobby );

		if ( ret != DP_OK )
		{

			debug_log ( "DIRECTP: UNABLE TO CREATE A DIRECTPLAYLOBBY3 interface" );

			return;
		}

		//
		// Serial needs a service provider, and a com_port structure
		//

		address_elements[0].guidDataType = DPAID_ServiceProvider;
		address_elements[0].dwDataSize = sizeof ( GUID );
		address_elements[0].lpData = ( LPVOID ) &DPSPGUID_SERIAL;

		address_elements[1].guidDataType = DPAID_ComPort;
		address_elements[1].dwDataSize = sizeof ( DPCOMPORTADDRESS );
		address_elements[1].lpData = ( LPVOID ) &com_port_address;

		com_port_address.dwComPort = com_port;

		switch ( baud_rate )
		{

			case 1:	com_port_address.dwBaudRate = CBR_19200; break;
			case 2:	com_port_address.dwBaudRate = CBR_38400; break;
			case 3:	com_port_address.dwBaudRate = CBR_57600; break;
			case 4:	com_port_address.dwBaudRate = CBR_115200; break;
		}

		switch ( stop_bits )
		{

			case 1: com_port_address.dwStopBits = ONESTOPBIT; break;
			case 2: com_port_address.dwStopBits = ONE5STOPBITS; break;
			case 3: com_port_address.dwStopBits = TWOSTOPBITS; break;
		}

		switch ( parity )
		{

			case 1: com_port_address.dwParity = NOPARITY; break;
			case 2: com_port_address.dwParity = EVENPARITY; break;
			case 3: com_port_address.dwParity = ODDPARITY; break;
			case 4: com_port_address.dwParity = MARKPARITY; break;
		}

		switch ( flow )
		{

			case 1: com_port_address.dwFlowControl = DPCPA_NOFLOW; break;
			case 2: com_port_address.dwFlowControl = DPCPA_XONXOFFFLOW; break;
			case 3: com_port_address.dwFlowControl = DPCPA_RTSFLOW; break;
			case 4: com_port_address.dwFlowControl = DPCPA_DTRFLOW; break;
			case 5: com_port_address.dwFlowControl = DPCPA_RTSDTRFLOW; break;
		}

		//
		// Find the size of memory to store the address
		//

		ret = IDirectPlayLobby_CreateCompoundAddress ( direct_play_lobby, address_elements, 2, NULL, &address_size );

		if ( ret != DPERR_BUFFERTOOSMALL )
		{

			IDirectPlayLobby_Release ( direct_play_lobby );

			debug_log ( "DIRECTP: Unable to establish how big the compound address is" );

			return;
		}

		address = safe_malloc ( address_size );

		//
		// Now fill the memory with the address
		//

		ret = IDirectPlayLobby_CreateCompoundAddress ( direct_play_lobby, address_elements, 2, address, &address_size );

		if ( ret != DP_OK )
		{

			IDirectPlayLobby_Release ( direct_play_lobby );

			debug_log ( "DIRECTP: Unable to create a compound address" );

			return;
		}

		//
		// Now usurp the original connection data
		//

		if ( connection_data.service_provider.connection )
		{

			if ( connection_data.service_provider.connection )
			{

				safe_free ( connection_data.service_provider.connection );

				connection_data.service_provider.connection = address;

				connection_data.service_provider.connection_size = address_size;
			}

			//
			// Replace the directplay interface
			//

			create_direct_play_interface ();

			ret = IDirectPlayX_InitializeConnection ( direct_playx, connection_data.service_provider.connection, 0 );

			if ( ret != 0 )
			{

				debug_log ( "DIRECTP: Unable to initialize connection on the new serial address" );
			}
		}

		IDirectPlayLobby_Release ( direct_play_lobby );

		debug_log ( "DIRECTP: CREATED A COMPOUND ADDRESS FOR THE SERIAL SERVICE PROVIDER!" );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DPLAY_ERROR_MESSAGE
{

	HRESULT
		error;

	char
		*error_string;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static struct DPLAY_ERROR_MESSAGE dplay_error_table[] =
{

	{ DPERR_ALREADYINITIALIZED, "DPERR_ALREADYINITIALIZED" },
	{ DPERR_ACCESSDENIED, "DPERR_ACCESSDENIED" },
	{ DPERR_ACTIVEPLAYERS, "DPERR_ACTIVEPLAYERS" },
	{ DPERR_BUFFERTOOSMALL, "DPERR_BUFFERTOOSMALL" },
	{ DPERR_CANTADDPLAYER, "DPERR_CANTADDPLAYER" },
	{ DPERR_CANTCREATEGROUP, "DPERR_CANTCREATEGROUP" },
	{ DPERR_CANTCREATEPLAYER, "DPERR_CANTCREATEPLAYER" },
	{ DPERR_CANTCREATESESSION, "DPERR_CANTCREATESESSION" },
	{ DPERR_CAPSNOTAVAILABLEYET, "DPERR_CAPSNOTAVAILABLEYET" },
	{ DPERR_EXCEPTION, "DPERR_EXCEPTION" },
	{ DPERR_GENERIC, "DPERR_GENERIC" },
	{ DPERR_INVALIDFLAGS, "DPERR_INVALIDFLAGS" },
	{ DPERR_INVALIDOBJECT, "DPERR_INVALIDOBJECT" },
	{ DPERR_INVALIDPARAM, "DPERR_INVALIDPARAM" },
	{ DPERR_INVALIDPARAMS, "DPERR_INVALIDPARAMS" },
	{ DPERR_INVALIDPLAYER, "DPERR_INVALIDPLAYER" },
	{ DPERR_INVALIDGROUP, "DPERR_INVALIDGROUP" },
	{ DPERR_NOCAPS, "DPERR_NOCAPS" },
	{ DPERR_NOCONNECTION, "DPERR_NOCONNECTION" },
	{ DPERR_NOMEMORY, "DPERR_NOMEMORY" },
	{ DPERR_OUTOFMEMORY, "DPERR_OUTOFMEMORY" },
	{ DPERR_NOMESSAGES, "DPERR_NOMESSAGES" },
	{ DPERR_NONAMESERVERFOUND, "DPERR_NONAMESERVERFOUND" },
	{ DPERR_NOPLAYERS, "DPERR_NOPLAYERS" },
	{ DPERR_NOSESSIONS, "DPERR_NOSESSIONS" },
	{ DPERR_PENDING, "DPERR_PENDING" },
	{ DPERR_SENDTOOBIG, "DPERR_SENDTOOBIG" },
	{ DPERR_TIMEOUT, "DPERR_TIMEOUT" },
	{ DPERR_UNAVAILABLE, "DPERR_UNAVAILABLE" },
	{ DPERR_UNSUPPORTED, "DPERR_UNSUPPORTED" },
	{ DPERR_BUSY, "DPERR_BUSY" },
	{ DPERR_USERCANCEL, "DPERR_USERCANCEL" },
	{ DPERR_NOINTERFACE, "DPERR_NOINTERFACE" },
	{ DPERR_CANNOTCREATESERVER, "DPERR_CANNOTCREATESERVER" },
	{ DPERR_PLAYERLOST, "DPERR_PLAYERLOST" },
	{ DPERR_SESSIONLOST, "DPERR_SESSIONLOST" },
	{ DPERR_UNINITIALIZED, "DPERR_UNINITIALIZED" },
	{ DPERR_NONEWPLAYERS, "DPERR_NONEWPLAYERS" },
	{ DPERR_INVALIDPASSWORD, "DPERR_INVALIDPASSWORD" },
	{ DPERR_CONNECTING, "DPERR_CONNECTING" },
	{ DPERR_CONNECTIONLOST, "DPERR_CONNECTIONLOST" },
	{ DPERR_UNKNOWNMESSAGE, "DPERR_UNKNOWNMESSAGE" },
	{ DPERR_CANCELFAILED, "DPERR_CANCELFAILED" },
	{ DPERR_INVALIDPRIORITY, "DPERR_INVALIDPRIORITY" },
	{ DPERR_NOTHANDLED, "DPERR_NOTHANDLED" },
	{ DPERR_CANCELLED, "DPERR_CANCELLED" },
	{ DPERR_ABORTED, "DPERR_ABORTED" },
	{ DPERR_BUFFERTOOLARGE, "DPERR_BUFFERTOOLARGE" },
	{ DPERR_CANTCREATEPROCESS, "DPERR_CANTCREATEPROCESS" },
	{ DPERR_APPNOTSTARTED, "DPERR_APPNOTSTARTED" },
	{ DPERR_INVALIDINTERFACE, "DPERR_INVALIDINTERFACE" },
	{ DPERR_NOSERVICEPROVIDER, "DPERR_NOSERVICEPROVIDER" },
	{ DPERR_UNKNOWNAPPLICATION, "DPERR_UNKNOWNAPPLICATION" },
	{ DPERR_NOTLOBBIED, "DPERR_NOTLOBBIED" },
	{ DPERR_SERVICEPROVIDERLOADED, "DPERR_SERVICEPROVIDERLOADED" },
	{ DPERR_ALREADYREGISTERED, "DPERR_ALREADYREGISTERED" },
	{ DPERR_NOTREGISTERED, "DPERR_NOTREGISTERED" },
	{ DPERR_AUTHENTICATIONFAILED, "DPERR_AUTHENTICATIONFAILED" },
	{ DPERR_CANTLOADSSPI, "DPERR_CANTLOADSSPI" },
	{ DPERR_ENCRYPTIONFAILED, "DPERR_ENCRYPTIONFAILED" },
	{ DPERR_SIGNFAILED, "DPERR_SIGNFAILED" },
	{ DPERR_CANTLOADSECURITYPACKAGE, "DPERR_CANTLOADSECURITYPACKAGE" },
	{ DPERR_ENCRYPTIONNOTSUPPORTED, "DPERR_ENCRYPTIONNOTSUPPORTED" },
	{ DPERR_CANTLOADCAPI, "DPERR_CANTLOADCAPI" },
	{ DPERR_NOTLOGGEDIN, "DPERR_NOTLOGGEDIN" },
	{ DPERR_LOGONDENIED, "DPERR_LOGONDENIED" },
	{ DP_OK, "DP_OK" },
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static char
	no_dplay_error_message[] = "NO_DPLAY_ERROR_MESSAGE_FOUND";

char *get_dplay_error_message (HRESULT error)
{

	int
		count;

	count = 0;

	while ( ( dplay_error_table[count].error != 0 ) && ( dplay_error_table[count].error != error ) )
	{

		count ++;
	}

	if ( dplay_error_table [count].error != error )
	{

		return ( no_dplay_error_message );
	}
	else
	{

		return (dplay_error_table [count].error_string);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_DUMP_PACKET_DATA

void write_comms_data (int flag, char *data, int size)
{

	FILE
		*file_ptr;

	if (flag)
	{

		file_ptr = fopen ("out.dat", "ab");
	}
	else
	{

		file_ptr = fopen ("in.dat", "ab");
	}

	if (file_ptr)
	{

		fwrite (data, size, 1, file_ptr);

		fclose (file_ptr);
	}
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int direct_play_get_send_queue_number_of_packets (void)
{

	return direct_play_send_queue_number_of_packets;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int direct_play_get_send_queue_number_of_bytes (void)
{

	return direct_play_send_queue_number_of_bytes;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
