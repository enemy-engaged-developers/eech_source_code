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



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define INTERNAL_MODULES 1

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define SERVER_DEBUG 1 // schorpp

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static connection_list_type
	*connection_list_head = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

connection_list_type *register_connection (DPID connection_id)
{

	connection_list_type
		*new_connection;

	//
	// stop pause or time acceleration if game is not single player
	//

	set_min_time_acceleration (NULL);

	//
	//
	//

	if (new_connection = get_connection_list_item (connection_id))
	{

		#if SERVER_DEBUG

		debug_log ("SERVER: already registered connection %d", connection_id);

		#endif

		return new_connection;
	}
	else
	{

		new_connection = (connection_list_type *) malloc_heap_mem (sizeof (connection_list_type));

		memset (new_connection, 0, sizeof (connection_list_type));

		new_connection->connection_receive_buffer = (char *) malloc_heap_mem (command_line_comms_connection_receive_size);

		new_connection->connection_receive_buffer_size = command_line_comms_connection_receive_size;

		debug_log ("SERVER: connection receive buffer size = %d, commandline %d", new_connection->connection_receive_buffer_size, command_line_comms_connection_receive_size);

		new_connection->already_sent_query_data = FALSE;

		new_connection->group_resend_timer = 0.0;

		new_connection->personal_resend_timer = 0.0;

		new_connection->connection_id = connection_id;

		new_connection->next = connection_list_head;

		new_connection->receive_group_frame_id = 0;

		new_connection->receive_personal_frame_id = 0;

		new_connection->send_personal_frame_id = 0;

		connection_list_head = new_connection;

		debug_log ("SERVER: registering new connection %d", connection_id);

		#if SERVER_DEBUG

		debug_watch ("Connection id %d data", MT_INT, &new_connection->connection_id);
		debug_watch ("	number of packets				= %d", MT_INT, &new_connection->number_of_packets);
		debug_watch ("	size								= %d", MT_INT, &new_connection->size);
		//debug_watch ("	send group id					= %d", MT_INT, &new_connection->send_group_frame_id);
		debug_watch ("	send personal id				= %d", MT_INT, &new_connection->send_personal_frame_id);
		debug_watch ("	receive group id				= %d", MT_INT, &new_connection->receive_group_frame_id);
		debug_watch ("	receive personal id				= %d", MT_INT, &new_connection->receive_personal_frame_id);
		debug_watch ("	rerequest counter				= %d", MT_INT, &new_connection->packet_rerequested);
		debug_watch ("	gunship ptr						= %d", MT_INT, &new_connection->gunship_entity);
		debug_watch ("	player ptr							= %d", MT_INT, &new_connection->pilot_entity);
		debug_watch ("	gunship number				= %d", MT_INT, &new_connection->gunship_number);
		//debug_watch ("	last packet time				 	= %d", MT_INT, &new_connection->time);
		debug_watch ("	group resend time				 	= %f", MT_FLOAT, &new_connection->group_resend_timer);
		debug_watch ("	personal resend time			 	= %f", MT_FLOAT, &new_connection->personal_resend_timer);

		#endif

		return new_connection;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void unregister_connection (DPID connection_id)
{

	connection_list_type
		*prev_connection,
		*new_connection;

	new_connection = connection_list_head;

	prev_connection = NULL;

	while (new_connection)
	{

		if (new_connection->connection_id == connection_id)
		{

			if (prev_connection)
			{

				prev_connection->next = new_connection->next;
			}
			else
			{

				connection_list_head = new_connection->next;
			}

			free_mem (new_connection->connection_receive_buffer);

			free_mem (new_connection);

			#if SERVER_DEBUG

			debug_log ("SERVER: unregistering connection %d", connection_id);

			#endif

			//
			// remove any packets for connection_id in packet_list
			//

			free_connection_packets (connection_id);

			return;
		}

		prev_connection = new_connection;

		new_connection = new_connection->next;
	}

	debug_log ("SERVER: Error: unregister_connection, connection_id unknown"); //schorpp
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

connection_list_type *get_connection_list_head (void)
{

	return connection_list_head;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

connection_list_type *get_connection_list_item (DPID connection_id)
{

	connection_list_type
		*current_connection;

	current_connection = connection_list_head;

	// if dpid_all_players just return the first one.

	if ((connection_id == direct_play_get_group_id ()) || (connection_id == DPID_ALLPLAYERS))
	{

		return current_connection;
	}

	while (current_connection)
	{

		if (current_connection->connection_id == connection_id)
		{

			return current_connection;
		}

		current_connection = current_connection->next;
	}

	debug_log ("SERVER: new connection %d", connection_id);

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void validate_connections (void)
{

	connection_list_type
		*destroy_connection,
		*this_connection;
	int
		timeout_limit;

	this_connection = connection_list_head;

	while (this_connection)
	{

		destroy_connection = this_connection;

		this_connection = this_connection->next;

		if (destroy_connection->pilot_entity) // Jabberwock 031204 MP bug search - reinstated
		{
			// added count_limit for connecting players
			if (destroy_connection->pilot_entity)
			{
				timeout_limit = command_line_comms_timeout;
			}
			else
			{
				timeout_limit = command_line_comms_timeout + 15;
			}
		
			if ((get_system_time () - destroy_connection->connection_validation_time) > timeout_limit * TIME_1_SECOND)
			{
				if (destroy_connection->validation_count > 1) // Jabberwock 031203 Only two passes
				{
// Jabberwock 031107 MP bug search - this is where original crash occurs, but it's symptom, not the cause!
/*                                 	if (destroy_connection->pilot_entity)
					{
 					     entity
 						*gunship;
      						gunship = get_local_entity_parent (destroy_connection->pilot_entity, LIST_TYPE_AIRCREW);
	
						if (gunship)
						{
							set_client_server_entity_int_value (gunship, INT_TYPE_PLAYER, ENTITY_PLAYER_AI);
							debug_log ("SERVER: TIMEOUT: Resetting clients gunship to AI");
						}
*/
// below is the replacement code for the above: sets back the helo to AI - OK
					if (destroy_connection->gunship_entity)
					{
						set_client_server_entity_int_value (destroy_connection->gunship_entity, INT_TYPE_PLAYER, ENTITY_PLAYER_AI);
					}
// the original destroy pilot_entity - may cause invalid assignment? (random entity)
//					destroy_client_server_entity (destroy_connection->pilot_entity);
//					debug_log ("SERVER: TIMEOUT: destroying clients pilot entity");
//					}

					if (destroy_connection->pilot_entity)
					{
						server_log("%s removed by cvc", get_local_entity_string (destroy_connection->pilot_entity, STRING_TYPE_PILOTS_NAME));

						destroy_client_server_entity (destroy_connection->pilot_entity);

						destroy_connection->pilot_entity = NULL;
					}
					else
					{
						server_log("Unknown player removed");
					}

// Jabberwock 031108 - ends - seems to work!
					
					if (get_comms_model () == COMMS_MODEL_SERVER)
					{
						debug_log ("SERVER: TIMEOUT: Unregistering connection %d", destroy_connection->connection_id);
						//unregister_connection (destroy_connection->connection_id);
						// Jabberwock 0312073 MP bug search - Not working - DP timeout kills the player first....
                                                server_log("In cvc, DP-remove player from group");         //Moje040516 added for server_log info
						direct_play_remove_player_from_group (destroy_connection->connection_id);
					}
					else
					{
						debug_log ("SERVER: TIMEOUT: Quitting game", destroy_connection->connection_id);
						start_game_exit (GAME_EXIT_KICKOUT, FALSE);
					}

					unregister_connection (destroy_connection->connection_id);
				}
			}
			else
			{

				debug_log ("SERVER: sending %d CONNECTION_VALIDATION", destroy_connection->connection_id);

				send_packet (destroy_connection->connection_id, PACKET_TYPE_CONNECTION_VALIDATION, NULL, 0, SEND_TYPE_PERSONAL);

				//destroy_connection->connection_validation_time = get_system_time ();

				destroy_connection->validation_count ++;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int server_create_session (void)
{

	int
		connection_created;

   connection_data_type
      *comms_connection;

	comms_connection = direct_play_get_connection_data ();

	if ( ( comms_connection ) && ( comms_connection->is_initialised ) )
	{

		if ( !comms_connection->one_way_hosting_setup )
		{
		
			direct_play_close_session ();

			connection_created = FALSE;

			if ( direct_play_create_session (get_game_type ()) )
			{
			
				if ( direct_play_session_capabilities () )
				{
				
					if ( direct_play_create_group () )
					{
					
						if ( direct_play_create_player () )
						{
						
							set_server_id (direct_play_get_player_id ());

							connection_created = TRUE;
						}
					}
				}
			}

			if ( !connection_created )
			{

				comms_connection->is_initialised = FALSE;
			}
		}
		else
		{

			direct_play_set_session_type_and_name ( get_game_type () );
		}
	}

	return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

connection_list_type *get_gunships_connection_list_item (entity *en)
{

	connection_list_type
		*this_connection;

	this_connection = connection_list_head;

	while (this_connection)
	{

		if (this_connection->gunship_entity == en)
		{

			return this_connection;
		}

		this_connection = this_connection->next;
	}

	return NULL;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


