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
//
// Problems :-
//
// if sending data with send_packet it will arrive before any entity data because entity data is buffered up per frame
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 1 - minimal
// 2 - medium
// 3 - the full monty
// 4 - show resend list as well

#define SOUND_DEBUG						0

#define DEBUG_MODULE						0

#define COMMS_DEBUG_BAD_CONNECTION	0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	comms_weapon_lag_timing;

float
	comms_weapon_lag_time,
   delta_time = 0.0,
   last_time = 0.0,
   network_frame_time = 0.0,
   network_frame_rate = 0.0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

comms_model_types
	system_comms_model;

comms_data_flow_types
	system_comms_data_flow;

DPID
	system_server_id;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	resend_packet_list_counter,
	group_packet_list_counter,
	personal_packet_list_counter;

int
	send_group_frame_id = 0;

stub_packet_type
	*rerequest_packet_list,
	*resend_packet_list,
	*received_group_packets,
	*received_personal_packets;

static packet_header_type
	*new_receive_packet = NULL;

static unsigned char
	*new_receive_packet_data = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int
	rerequest_packet_counter,
	resend_packet_counter;

#if COMMS_STATS

int
	packet_record_data_count;

static int
	total_data_size,
	total_connection_size,
	received_group_list_size,
	received_personal_list_size,
	resend_list_size,
	rerequest_list_size,
	num_packets_received,
	num_packets_sent;

float
	instant_packet_size_sent,
	instant_packet_size_received,
	av_packet_size_sent,
	av_packet_size_received,
	max_packet_size_sent,
	max_packet_size_received,
	max_processed_size;

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char
	*comms_model_string = NULL,
	*comms_model_names [] =
	{
	
		"COMMS_MODEL_SERVER",
		"COMMS_MODEL_CLIENT",
		"NUM_COMMS_MODEL_TYPES"
	},
	*send_type_names [] =
	{
	
		"SEND_TYPE_PERSONAL",
		"SEND_TYPE_GROUP",
		"NUM_SEND_TYPES"
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static stub_packet_type *get_stub_packet_for_frame (send_types send_type, DPID player_id, int frame_id, int packet_id);

static void request_resend_packet (connection_list_type *connection, int frame_id, int packet_id, int time_stamp, send_types send_type);

static void free_stub_packet (stub_packet_type *stub_packet);

static void add_stub_packet_to_list (stub_packet_type **list, stub_packet_type *packet);

static int count_packets_for_frame (stub_packet_type *packet_list, int player_id, int frame_id);

static int get_comms_checksum (char *data, int send_size);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_comms_data_flow (comms_data_flow_types data_flow)
{

	system_comms_data_flow = data_flow;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_comms_model (comms_model_types model)
{

	system_comms_model = model;

	comms_model_string = comms_model_names [model];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_comms (void)
{

	#if DEBUG_MODULE >= 1

	debug_log ("COMMS : Initialise comms");

	#endif

	direct_play_set_comms_mode (DIRECT_PLAY_COMMS_MODE_NONE);

	set_comms_data_flow (COMMS_DATA_FLOW_TX);

	set_comms_model (COMMS_MODEL_SERVER);

	reset_comms_data ();

	comms_clear_data_record ();

	if (command_line_comms_guaranteed_send)
	{

		// big number to stop my resend system kicking in
		command_line_comms_packet_resend_timer = 1000;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_comms_data (void)
{

	stub_packet_type
		*packet;

	#if DEBUG_MODULE >= 1

	debug_log ("COMMS : reset comms data");

	#endif

	comms_weapon_lag_timing = FALSE;

	comms_weapon_lag_time = 0.0;

	set_group_frame_id (0);

	//
	// Free all group packets
	//

	while (received_group_packets)
	{

		packet = received_group_packets;

		received_group_packets = received_group_packets->next;

		free_stub_packet (packet);

		packet = NULL;
	}

	//
	// Free all personal packets
	//

	while (received_personal_packets)
	{

		packet = received_personal_packets;

		received_personal_packets = received_personal_packets->next;

		free_stub_packet (packet);

		packet = NULL;
	}

	//
	// Free all resend packets
	//

	while (resend_packet_list)
	{

		packet = resend_packet_list;

		resend_packet_list = resend_packet_list->next;

		free_stub_packet (packet);

		packet = NULL;
	}

	received_group_packets = NULL;

	received_personal_packets = NULL;

	resend_packet_list = NULL;

	rerequest_packet_counter = 0;

	resend_packet_counter = 0;

	resend_packet_list_counter = 0;

	group_packet_list_counter = 0;

	personal_packet_list_counter = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_comms_debug (void)
{

	#if DEBUG_MODULE
	
	debug_log ("COMMS : initialise comms debug to level %d", DEBUG_MODULE);

	#endif
	
	#if COMMS_STATS
	
	debug_watch ("packets size								= %d", MT_INT, &command_line_comms_packet_data_size);
	debug_watch ("packets sent							= %d", MT_INT, &num_packets_sent);
	debug_watch ("packets send size (instant)			= %.02f", MT_FLOAT, &instant_packet_size_sent);
	debug_colour_watch (COLOUR_RED, "packets send size (av)				= %.02f", MT_FLOAT, &av_packet_size_sent);
	debug_watch ("packets send size (max)				= %.02f", MT_FLOAT, &max_packet_size_sent);
	
	debug_watch ("packets received						= %d", MT_INT, &num_packets_received);
	debug_watch ("packets received size (instant) 		= %.02f", MT_FLOAT, &instant_packet_size_received);
	debug_colour_watch (COLOUR_RED, "packets received size (av)			= %.02f", MT_FLOAT, &av_packet_size_received);
	debug_watch ("packets received size (max)			= %.02f", MT_FLOAT, &max_packet_size_received);

	debug_watch ("packets record count	 				= %d", MT_INT, &packet_record_data_count);
	
	#endif

	#if COMMS_STATS

	debug_colour_watch (COLOUR_RED, "processed size (max)					= %.02f", MT_FLOAT, &max_processed_size);
	
	debug_watch ("re-request counter						= %d", MT_INT, &rerequest_packet_counter);
	debug_watch ("resend packet counter				= %d", MT_INT, &resend_packet_counter);
	
	debug_watch ("group packet list counter				= %d", MT_INT, &group_packet_list_counter);
	debug_watch ("personal packet list counter			= %d", MT_INT, &personal_packet_list_counter);
	debug_watch ("resend packet list counter			= %d", MT_INT, &resend_packet_list_counter);
	
	debug_watch ("packet resend timer					= %.02f", MT_FLOAT, &command_line_comms_packet_resend_timer);
	debug_watch ("packet resend timer					= %.02f", MT_FLOAT, &command_line_comms_resend_timeout);
	
	debug_watch ("Max Network frame time				= %d", MT_INT, &command_line_max_game_update_rate);
	debug_watch ("Network frame time					= %.02f", MT_FLOAT, &network_frame_time);
	debug_watch ("Network frame rate					= %.02f", MT_FLOAT, &network_frame_rate);
	
	debug_watch ("Group packet list size					= %d", MT_INT, &received_group_list_size);
	debug_watch ("Personal packet list size				= %d", MT_INT, &received_personal_list_size);
	debug_watch ("Resend packet list size				= %d", MT_INT, &resend_list_size);
	debug_watch ("Rerequest packet list size			= %d", MT_INT, &rerequest_list_size);
	debug_watch ("Data Record size						= %d", MT_INT, &command_line_comms_data_record_size);
	debug_watch ("Connection size						= %d", MT_INT, &total_connection_size);
	debug_watch ("Total Data size							= %d", MT_INT, &total_data_size);

	#endif

	#if COMMS_STATS
	
	num_packets_received = 0;
	num_packets_sent = 0;
	av_packet_size_sent = 0;
	av_packet_size_received = 0;
	max_packet_size_sent = 0;
	max_packet_size_received = 0;
	max_processed_size = 0;

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_comms (void)
{
	
	#if COMMS_STATS
	
	debug_log ("********************************************************************");
	
	debug_log ("COMMS STATS:");
	
	debug_log ("packets size							= %d", command_line_comms_packet_data_size);
	debug_log ("packets sent							= %d", num_packets_sent);
	debug_log ("packets send size (av)				= %.02f", av_packet_size_sent);
	debug_log ("packets send size (max)				= %.02f", max_packet_size_sent);
	
	debug_log ("packets received						= %d", num_packets_received);
	debug_log ("packets received size (av)			= %.02f", av_packet_size_received);
	debug_log ("packets received size (max)		= %.02f", max_packet_size_received);
	
	debug_log ("processed size (max)					= %.02f", max_processed_size);
	
	debug_log ("re-request counter					= %d", rerequest_packet_counter);
	debug_log ("resend packet counter				= %d", resend_packet_counter);
	
	debug_log ("group packet list counter			= %d", group_packet_list_counter);
	debug_log ("personal packet list counter		= %d", personal_packet_list_counter);
	debug_log ("resend packet list counter			= %d", resend_packet_list_counter);
	
	debug_log ("packet resend timer					= %.02f", command_line_comms_packet_resend_timer);
	
	debug_log ("Network frame time					= %.02f", network_frame_time);
	debug_log ("Network frame rate					= %.02f", network_frame_rate);
	
	debug_log ("Group packet list size				= %d", received_group_list_size);
	debug_log ("Personal packet list size			= %d", received_personal_list_size);
	debug_log ("Resend packet list size				= %d", resend_list_size);
	debug_log ("Data Record size						= %d", command_line_comms_data_record_size);
	debug_log ("Connection size						= %d", total_connection_size);
	debug_log ("Total Data size						= %d", total_data_size);
	
	debug_log ("********************************************************************");
	
	#endif
	
	reset_comms_data ();
	
	if (new_receive_packet_data)
	{

		free_mem (new_receive_packet_data);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void send_packet (DPID player_id, packet_types type, char *data, int size, send_types send_type)
{

	HRESULT
		hr;

	float
		comms_timeout;
	
	int
		frame_id,
		send_size,
		packet_size,
		packet_counter,
		number_of_packets;
	
	stub_packet_type
		*stub_packet;
	
	connection_list_type
		*connection;
	
	static packet_header_type
		*new_packet = NULL;

	static unsigned char
		*new_packet_data = NULL;
		
	packet_counter = 1;
	
	connection = get_connection_list_item (player_id);
	
	if (send_type == SEND_TYPE_GROUP)
	{
		
		frame_id = send_group_frame_id;
		
		send_group_frame_id ++;
		
		#if DEBUG_MODULE >= 1
		
		debug_log ("COMMS: Sending group Data (type %d) (frame %d) size = %d, player id = %d", type, frame_id, size, player_id);
		
		#endif
	}
	else
	{
		
		if (connection)
		{
			
			frame_id = connection->send_personal_frame_id;
			
			connection->send_personal_frame_id ++;
			
			#if DEBUG_MODULE >= 1
			
			debug_log ("COMMS: Sending Personal Data (type %d) (frame %d) size = %d, player id = %d", type, frame_id, size, player_id);
			
			#endif
		}
		else
		{
			
			frame_id = 0;
			
			#if DEBUG_MODULE >= 1
			
			debug_log ("COMMS: Sending Personal Data (type %d) (frame %d no connection!) size = %d, player id = %d", type, frame_id, size, player_id);
	
			#endif
		}
	}
	
	#if COMMS_STATS
	
	av_packet_size_sent = (((av_packet_size_sent * num_packets_sent) + size) / ++ num_packets_sent);
	
	if (size > max_packet_size_sent)
	{
		
		max_packet_size_sent = size;
	}

	instant_packet_size_sent = size;
	
	#endif
	
	number_of_packets = max ((size - 1) / command_line_comms_packet_data_size, 0) + 1;
	
	do
	{
		
		send_size = min (size, command_line_comms_packet_data_size);

		//
		// For variable sized packets, just tell direct play the true size of the packet
		//
		packet_size = sizeof (packet_header_type) + (sizeof (unsigned char) * send_size);

		//
		// For old style fixed length packets, tell direct play the size of the whole packet ( not just the data )
		//
//		packet_size = sizeof (packet_header_type) + (sizeof (unsigned char) * command_line_comms_packet_data_size);

		new_packet_data = (unsigned char *) malloc_heap_mem (packet_size);

		memset (new_packet_data, 0, packet_size);
		
		debug_assert (new_packet_data);

		new_packet = (packet_header_type *) new_packet_data;
		
		new_packet->type = type;
		
		new_packet->number_of_packets = number_of_packets;
		
		new_packet->frame_id = frame_id;
		
		new_packet->player_id = direct_play_get_player_id ();
		
		new_packet->packet_id = packet_counter;
		
		new_packet->data_size = send_size;

		new_packet->check_sum = get_comms_checksum (data, send_size);
		
		memcpy (&new_packet_data [sizeof (packet_header_type)], data, send_size);
		
		#if COMMS_DEBUG_BAD_CONNECTION
		
		if (!(rand16 () % COMMS_DEBUG_BAD_CONNECTION))
		{
			
			debug_log ("COMMS BAD CONNECTION : NOT SENDING FRAME %d, PACKET %d", new_packet->frame_id, new_packet->packet_id);
		}
		else
		{
			
			#endif

			comms_timeout = command_line_comms_timeout;

			hr = direct_play_send_data (player_id, (LPVOID) new_packet_data, packet_size);

			while ((hr == DPERR_BUSY) || (hr == DPERR_GENERIC))
			{

				//
				//
				//

				comms_timeout -= get_delta_time ();

				if (comms_timeout <= 0.0)
				{

					break;
				}
				
				Sleep (10);

				hr = direct_play_send_data (player_id, (LPVOID) new_packet_data, packet_size);
			}

			if ( hr != DP_OK )
			{

				//
				// We got a different error - boot out of the game!!!!
				//

				if (get_comms_model () != COMMS_MODEL_SERVER)
				{
	
					//setup_campaign_over_screen (get_local_force_entity (get_global_gunship_side ()), CAMPAIGN_RESULT_SERVER_REJECTED);
	
					// Jabberwock 040518 Even more telling error message
					debug_fatal ( "DirectPlay error: %d",  hr );
					//start_game_exit (GAME_EXIT_KICKOUT, FALSE); 
				}
			}
			
			Sleep (0);
			
			#if COMMS_DEBUG_BAD_CONNECTION
		}
		
		#endif
		
		#if DEBUG_MODULE >= 2
		
		debug_log ("COMMS:      packet %d of %d, size %d", packet_counter, new_packet->number_of_packets, send_size);
		
		#endif
		
		size -= send_size;
		
		data += send_size;
		
		packet_counter ++;
		
		//
		// store packet ready for re-request
		//
		
		stub_packet = (stub_packet_type *) malloc_fast_mem (sizeof (stub_packet_type));

		memset (stub_packet, 0, sizeof (stub_packet_type));
		
		debug_assert (stub_packet);
		
		stub_packet->packet = new_packet;

		stub_packet->send_type = send_type;
		
		add_stub_packet_to_resend_list (stub_packet);
	}
	while (size);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void receive_packets (void)
{
	
  	int
		packet_size;

	send_types
		send_type;
	
	connection_list_type
		*connection;
	
	stub_packet_type
		*rerequest_packet,
		*stub_packet;
	
	//
	// Receive all packets present
	//

	send_type = SEND_TYPE_GROUP;

	connection = NULL;
	
	while (TRUE)
	{
		
		//
		// malloc_heap_mem new packet if required
		//

		packet_size = sizeof (packet_header_type) + (sizeof (unsigned char) * command_line_comms_packet_data_size);
		
		if (!new_receive_packet)
		{
			
			new_receive_packet_data = (unsigned char *) malloc_heap_mem (packet_size);

			new_receive_packet = (packet_header_type *) new_receive_packet_data;
		}

		memset (new_receive_packet_data, 0xFF, packet_size);
		
		//
		// Receive data into new packet
		//

		Sleep (0);
		
		if (!direct_play_receive_data ((LPVOID) new_receive_packet_data, packet_size))
		{
			
			return;
		}

		/////////////////////////////////////////////////////////////////
		// progress indicator
		if (get_gunship_screen_progress_message () == GUNSHIPS_SCREEN_CONNECTING_TEXT)
		{

			update_gunships_screen_progress_indicator ();
		}
		/////////////////////////////////////////////////////////////////
			
		Sleep (0);
		
		//
		// is it from a known connection
		//
		
		if (!(connection = get_connection_list_item (new_receive_packet->player_id)))
		{
			
			if (get_comms_model () == COMMS_MODEL_SERVER)
			{
				
				#if DEBUG_MODULE >= 1
				
				debug_log ("COMMS: received packet from unknown connection : registering");
				
				#endif
				
				connection = register_connection (new_receive_packet->player_id);
			}
			else
			{
				
				//
				// clients can only accept certain packets from unknown connections.
				//
				
				if (new_receive_packet->type == PACKET_TYPE_SESSION_INFO)
				{
					
					#if DEBUG_MODULE >= 1
					
					debug_log ("COMMS: received packet from unknown connection : registering server");
					
					#endif
					
					connection = register_connection (new_receive_packet->player_id);
				}
				else
				{
					
					#if DEBUG_MODULE >= 1
					
					debug_log ("COMMS: received packet from unknown connection : ignoring");
					
					#endif
					
					return;
				}
			}
		}

		send_type = get_packet_send_type (new_receive_packet);

		#if DEBUG_MODULE >= 1
		
		debug_log ("COMMS: received %s packet for frame %d, packet_id =%d, type = %d, size %d, player_id = %d", send_type_names [send_type], new_receive_packet->frame_id, new_receive_packet->packet_id, new_receive_packet->type, new_receive_packet->data_size, new_receive_packet->player_id);
		
		#endif

		//
		// do checksum check
		//

		{

			packet_header_type
				*temp_packet;

			temp_packet = (packet_header_type *) new_receive_packet_data;

			if (temp_packet)
			{
	
				if ((temp_packet->check_sum) != get_comms_checksum ((char *) &new_receive_packet_data [sizeof (packet_header_type)], (temp_packet->data_size)))
				{
/*
					char
						filename [32];

					int
						count;

					FILE
						*fp;

					count = 0;

					sprintf (filename, "bad%d.dat", count);

					while (file_exist (filename))
					{
						count ++;

						sprintf (filename, "bad%d.dat", count);
					}

					fp = fopen (filename, "wb");

					fwrite (temp_packet, temp_packet->data_size + sizeof (packet_header_type), 1, fp);

					fclose (fp);
*/
					debug_log ("COMMS:    data check_sum failed receiver %d, calculated %d, datasize %d",
									temp_packet->check_sum,
									get_comms_checksum ((char *) &new_receive_packet_data [sizeof (packet_header_type)], temp_packet->data_size),
									temp_packet->data_size);
		
					request_resend_packet (connection, temp_packet->frame_id, temp_packet->packet_id, get_system_time (), send_type);
	
					return;
				}
			}
		}
		
		//
		// malloc new stub packet
		//
		
		stub_packet = (stub_packet_type *) malloc_fast_mem (sizeof (stub_packet_type));

		memset (stub_packet, 0, sizeof (stub_packet_type));
		
		stub_packet->packet = (packet_header_type *) new_receive_packet_data;

		stub_packet->received_time = get_system_time ();
		
		stub_packet->send_type = send_type;

		//
		// add to appropriate list if not already received.
		//
		
		if (!get_stub_packet_for_frame (send_type, stub_packet->packet->player_id, stub_packet->packet->frame_id, stub_packet->packet->packet_id))
		{
			
			add_stub_packet_to_receive_list (send_type, stub_packet);
		}
		else
		{
			
			#if DEBUG_MODULE >= 2
			
			debug_log ("COMMS: already received %s packet for frame %d, packet_id =%d, type = %d, size %d, player_id = %d", send_type_names [send_type], new_receive_packet->frame_id, new_receive_packet->packet_id, new_receive_packet->type, new_receive_packet->data_size, new_receive_packet->player_id);
			
			#endif
		}

		//
		// check if packet is a rerequested one
		//

		rerequest_packet = rerequest_packet_list;

		while (rerequest_packet)
		{

			if ((rerequest_packet->send_type == send_type) &&
				(rerequest_packet->packet_id == new_receive_packet->packet_id) &&
				(rerequest_packet->frame_id == new_receive_packet->frame_id))
			{
/*
				FILE
					*fp;

				char
					filename [32];

				int
					count;

				count = 0;

				sprintf (filename, "good%d.dat", count);

				while (file_exist (filename))
				{
					count ++;

					sprintf (filename, "good%d.dat", count);
				}

				fp = fopen (filename, "wb");

				fwrite (new_receive_packet, new_receive_packet->data_size + sizeof (packet_header_type), 1, fp);

				fclose (fp);
*/
				#if DEBUG_MODULE >= 2

				debug_log ("COMMS: removing rerequest for %s packet frame %d, packet %d from list and setting time to %d",
								send_type_names [rerequest_packet->send_type],
								new_receive_packet->frame_id,
								new_receive_packet->packet_id,
								rerequest_packet->received_time);

				#endif

				stub_packet->received_time = rerequest_packet->received_time;

				remove_stub_packet_from_list (&rerequest_packet_list, rerequest_packet);

				free_mem (rerequest_packet);

				break;
			}

			rerequest_packet = rerequest_packet->next;
		}

		//
		//
		//
		
		connection->interpolation_time = get_system_time ();

		connection->connection_validation_time = get_system_time ();
		
		#if COMMS_STATS
		
		av_packet_size_received = (((av_packet_size_received * num_packets_received) + new_receive_packet->data_size) / ++ num_packets_received);
		
		if (new_receive_packet->data_size > max_packet_size_received)
		{
			
			max_packet_size_received = new_receive_packet->data_size;
		}

		instant_packet_size_received = new_receive_packet->data_size;
		
		#endif
		
		new_receive_packet_data = NULL;

		new_receive_packet = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int process_packet_list (send_types send_type, connection_list_type *connection, DPID *player_id, char **data, int *size)
{
	
	packet_types
		type;
	
	int
		loop,
		frame_id,
		*frame_ptr,
		closest_time,
		received_flag,
		predicted_size,
		data_ptr_offset;
	
	unsigned char
		*temp_char,
		*new_buffer;
	
	stub_packet_type
		*closest_packet = NULL,
		*packet,
		**packet_list,
		*this_packet;
	
	if (send_type == SEND_TYPE_GROUP)
	{
		
		frame_ptr = &connection->receive_group_frame_id;
		
		packet_list = &received_group_packets;

		if ((get_comms_model () == COMMS_MODEL_CLIENT) && (*frame_ptr == 0))
		{

			return PACKET_TYPE_INVALID;
		}
	}
	else
	{
		
		frame_ptr = &connection->receive_personal_frame_id;
		
		packet_list = &received_personal_packets;
	}
		
	#if DEBUG_MODULE >= 2
		
	debug_log ("COMMS: Checking for %s packets for id %d, frame %d", send_type_names [send_type], connection->connection_id, *frame_ptr);
		
	#endif
	
	this_packet = get_stub_packet_for_frame (send_type, connection->connection_id, *frame_ptr, 1);
	
	//
	// is it time to re-request the packet ? ie has then next packet arrived and N seconds gone by ?
	// NB. only capable of re-requesting one packet at a time...
	//

	if (!this_packet)
	{

		//
		// Find the closest next packet to the missing one
		//

		packet = *packet_list;
		
		while (packet)
		{

			if ((packet->send_type == send_type) &&
				(packet->packet->frame_id > *frame_ptr) &&
				(packet->packet->player_id == connection->connection_id))
			{

				if ((!closest_packet) || (packet->packet->frame_id < closest_packet->packet->frame_id))
				{

					closest_packet = packet;
				}
			}
			
			packet = packet->next;
		}

		//
		//
		//

		if (closest_packet)
		{
		
			if ((get_system_time () - closest_packet->received_time) > (command_line_comms_packet_resend_timer * TIME_1_SECOND))
			{
				
				#if DEBUG_MODULE >= 1
				
				debug_log ("COMMS: WAITING FOR %s FRAME %d, closest packet (%d %d) arrived %f seconds ago (None have arrived)",
								send_type_names [send_type],
								*frame_ptr,
								closest_packet->packet->frame_id,
								closest_packet->packet->packet_id,
								(float) (get_system_time () - closest_packet->received_time) / TIME_1_SECOND);
				
				#endif
				
				request_resend_packet (connection, *frame_ptr, 1, closest_packet->received_time, send_type);
			}
		}
	
		return PACKET_TYPE_INVALID;
	}
	
	#if DEBUG_MODULE >= 2
	
	if (send_type == SEND_TYPE_GROUP)
	{
		
		debug_log ("COMMS: Process GROUP packet list");
	}
	else
	{
		
		debug_log ("COMMS: Process PERSONAL packet list");
	}
	
	#endif
	
	*player_id = this_packet->packet->player_id;
	
	frame_id = this_packet->packet->frame_id;
	
	type = this_packet->packet->type;
	
	// do we have all packets for this frame
	
	received_flag = count_packets_for_frame (*packet_list, *player_id, frame_id);
	
	connection->number_of_packets = this_packet->packet->number_of_packets;

	if (received_flag == this_packet->packet->number_of_packets)
	{
		
		#if DEBUG_MODULE >= 2
		
		debug_log ("COMMS: received all %s packets for frame %d (total = %d)", send_type_names [send_type], frame_id, received_flag);
		
		#endif
		
		connection->packet_rerequested = 0;
		
		connection->size = 0;

		data_ptr_offset = 0;
		
		for (loop = 1; loop <= connection->number_of_packets; loop ++)
		{
			
			this_packet = get_stub_packet_for_frame (send_type, connection->connection_id, frame_id, loop);
			
			//
			// MUST have all packets by this point. Assert should NEVER fail
			//
			
			debug_assert (this_packet);
			
			connection->size += this_packet->packet->data_size;
			
			predicted_size = ((this_packet->packet->packet_id - 1) * command_line_comms_packet_data_size) + this_packet->packet->data_size;
			
			#if DEBUG_MODULE >= 3
			
			debug_log ("COMMS: predicted data size = %d, buffer = %d", predicted_size, connection->connection_receive_buffer_size);
			
			#endif
			
			#if COMMS_STATS
			
			if (predicted_size > max_processed_size)
			{
				
				max_processed_size = predicted_size;
			}
			
			#endif
			
			//
			// receive buffer not big enough so malloc some more.
			//
			
			if (predicted_size >= connection->connection_receive_buffer_size)
			{
				
				new_buffer = (char *) malloc_heap_mem (connection->connection_receive_buffer_size * 2);

				ASSERT (connection->connection_receive_buffer);
				
				memcpy (new_buffer, connection->connection_receive_buffer, connection->connection_receive_buffer_size);
				
				free_mem (connection->connection_receive_buffer);
				
				connection->connection_receive_buffer = new_buffer;
				
				connection->connection_receive_buffer_size *= 2;
				
				#if DEBUG_MODULE
				
				debug_log ("COMMS:     Connection receive buffer too small, mallocing %d", connection->connection_receive_buffer_size);
				
				#endif
			}
			
			temp_char = (unsigned char *) this_packet->packet;

			memcpy (&connection->connection_receive_buffer [data_ptr_offset], &temp_char [sizeof (packet_header_type)], this_packet->packet->data_size);

			data_ptr_offset += this_packet->packet->data_size;
			
			#if DEBUG_MODULE >= 3
			
			debug_log ("COMMS:     Processing %s packet frame_id = %d, packet_id %d, size %d, player %d", send_type_names [this_packet->send_type], this_packet->packet->frame_id, this_packet->packet->packet_id, this_packet->packet->data_size, this_packet->packet->player_id);
			
			#endif
			
			remove_stub_packet_from_receive_list (send_type, this_packet);
			
			free_stub_packet (this_packet);

			this_packet = NULL;
		}

		#if DEBUG_MODULE 

		debug_log ("COMMS:   Processing %s packets frame_id = %d, (total %d packets) size %d, player %d",
						send_type_names [send_type],
						frame_id,
						connection->number_of_packets,
						predicted_size,
						*player_id);

		#endif
		
		*data = connection->connection_receive_buffer;
		
		*size = connection->size;
		
		#if DEBUG_MODULE 
		
		connection->av_packet_size_received = (((connection->av_packet_size_received * connection->num_packets_received) + *size) / ++ connection->num_packets_received);
		
		if (*size > connection->max_packet_size_received)
		{
			
			connection->max_packet_size_received = *size;
		}
		
		#endif
		
		(*frame_ptr) ++;
		
		return type;
	}
	else
	{
		
		// some of the packets have arrived for this frame, is it time to re-request the others ?

		#if DEBUG_MODULE >= 2

		debug_log ("COMMS: only received %d %s packets for frame %d out of %d", received_flag, send_type_names [this_packet->send_type], this_packet->packet->frame_id, this_packet->packet->number_of_packets);

		#endif

		//
		// Find the closest packet in this frame
		//

		packet = *packet_list;

		closest_time = INT_MAX;
		
		while (packet)
		{

			if ((packet->send_type == send_type) &&
				(packet->packet->frame_id == *frame_ptr) &&
				(packet->packet->player_id == connection->connection_id))
			{

				if ((!closest_packet) || ((get_system_time () - closest_packet->received_time) < closest_time))
				{

					closest_packet = packet;

					closest_time = get_system_time () - closest_packet->received_time;
				}
			}
			
			packet = packet->next;
		}

		//
		//
		//

		if (closest_packet)
		{
		
			if ((get_system_time () - closest_packet->received_time) > (command_line_comms_packet_resend_timer * TIME_1_SECOND))
			{

				for (loop = 1; loop <= connection->number_of_packets; loop ++)
				{
					
					if (!(get_stub_packet_for_frame (send_type, connection->connection_id, *frame_ptr, loop)))
					{

						#if DEBUG_MODULE 
						
						debug_log ("COMMS: WAITING FOR %s FRAME %d packet %d, closest packet (%d %d) arrived %f seconds ago (Some have arrived)",
										send_type_names [send_type],
										*frame_ptr,
										loop,
										closest_packet->packet->frame_id,
										closest_packet->packet->packet_id,
										(float) (get_system_time () - closest_packet->received_time) / TIME_1_SECOND);
						
						#endif
						
						request_resend_packet (connection, *frame_ptr, loop, closest_packet->received_time, send_type);
					}
				}
			}
		}
	
		return PACKET_TYPE_INVALID;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DPID get_packet_destination (void)
{
	
	DPID
		id;
	
	switch (get_comms_model ())
	{
		
		case COMMS_MODEL_SERVER:
		{
			
			id = direct_play_get_group_id ();
			
			break;
		}
		case COMMS_MODEL_CLIENT:
		{
			
			id = get_server_id ();
			
			break;
		}
	}
	
	return (id);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

stub_packet_type *get_stub_packet_for_frame (send_types send_type, DPID player_id, int frame_id, int packet_id)
{

#if DEBUG_MODULE >= 4
	
	stub_packet_type
		*the_packet,
		*packet_list;
	
	if (send_type == SEND_TYPE_GROUP)
	{
		
		packet_list = received_group_packets;

		debug_log ("COMMS: GROUP PACKET LIST");
	}
	else
	{
		
		packet_list = received_personal_packets;

		debug_log ("COMMS: PERSONAL PACKET LIST");
	}

	the_packet = NULL;
	
	while (packet_list)
	{

		if (packet_list->packet->frame_id > 1)
		{

			debug_log ("COMMS:     %s packet frame %d, packet %d, player id %d",
						send_type_names [send_type],
						packet_list->packet->frame_id,
						packet_list->packet->packet_id,
						packet_list->packet->player_id);
		}
		
		if (packet_list->packet->frame_id == frame_id)
		{
			
			if (packet_list->packet->packet_id == packet_id)
			{
				
				if (packet_list->packet->player_id == player_id)
				{
					
					the_packet = packet_list;
				}
			}
		}
		
		packet_list = packet_list->next;
	}
	
	return the_packet;

#else
	
	stub_packet_type
		*packet_list;
	
	if (send_type == SEND_TYPE_GROUP)
	{
		
		packet_list = received_group_packets;
	}
	else
	{
		
		packet_list = received_personal_packets;
	}
	
	while (packet_list)
	{
		
		if (packet_list->packet->frame_id == frame_id)
		{
			
			if (packet_list->packet->packet_id == packet_id)
			{
				
				if (packet_list->packet->player_id == player_id)
				{
					
					return packet_list;
				}
			}
		}
		
		packet_list = packet_list->next;
	}
	
	return NULL;

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void request_resend_packet (connection_list_type *connection, int frame_id, int packet_id, int time_stamp, send_types send_type)
{

	stub_packet_type
		*new_stub_packet;

	int
		buffer [3];

	char
		*buffer_ptr;

	//
	// Add packet to rerequest list
	//

	new_stub_packet = rerequest_packet_list;

	while (new_stub_packet)
	{

		if ((new_stub_packet->send_type == send_type) &&
			(new_stub_packet->packet_id == packet_id) &&
			(new_stub_packet->frame_id == frame_id))
		{

			//
			// Rererequest after a certain time...
			//

			if ((get_system_time () - new_stub_packet->actual_time) > (command_line_comms_resend_timeout * TIME_1_SECOND))
			{

				debug_log ("COMMS: rerequest for frame %d packet %d must be lost, re-rerequesting", frame_id, packet_id);

				remove_stub_packet_from_list (&rerequest_packet_list, new_stub_packet);

				free_mem (new_stub_packet);

				break;
			}
			else
			{

				#if DEBUG_MODULE

				debug_log ("COMMS: rerequest for frame %d packet %d already exists, waiting... (waited %f so far)", frame_id, packet_id, (float) (get_system_time () - new_stub_packet->actual_time) / TIME_1_SECOND);

				#endif
			}

			return;
		}

		new_stub_packet = new_stub_packet->next;
	}
	
	buffer_ptr = (char *) &buffer;

	quick_set_list_item (buffer_ptr, int, frame_id);

	quick_set_list_item (buffer_ptr, int, packet_id);

	quick_set_list_item (buffer_ptr, send_types, send_type);
	
	send_packet (connection->connection_id, PACKET_TYPE_RESEND_PACKET, (char *) buffer, sizeof (buffer), SEND_TYPE_PERSONAL);
	
	rerequest_packet_counter ++;
						
	connection->packet_rerequested ++;
	
	#if COMMS_DEBUG_BAD_CONNECTION
	
	debug_log ("COMMS BAD CONNECTION: Re-requesting packet for frame %d, packet %d", frame_id, packet_id);
	
	#else
	
	debug_log ("WARNING: PACKET BEING RE-REQUESTED FROM PLAYER %d FOR %s FRAME %d PACKET %d",
					connection->connection_id,
					send_type_names [send_type],
					frame_id,
					packet_id);

	#endif

	new_stub_packet = (stub_packet_type *) malloc_fast_mem (sizeof (stub_packet_type));

	memset (new_stub_packet, 0, sizeof (stub_packet_type));

	new_stub_packet->send_type = send_type;

	new_stub_packet->received_time = time_stamp;

	new_stub_packet->actual_time = get_system_time ();

	new_stub_packet->frame_id = frame_id;

	new_stub_packet->packet_id = packet_id;

	new_stub_packet->packet = NULL;

	add_stub_packet_to_list (&rerequest_packet_list, new_stub_packet);

	#if DEBUG_MODULE

	debug_log ("COMMS:     rerequest %s frame %d, packet %d, time %d, added to rerequest list",
					send_type_names [send_type],
					frame_id,
					packet_id,
					get_system_time ());

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

stub_packet_type *resend_packet (DPID player_id, int frame_id, int packet_id, send_types send_type)
{
	
	int
		packet_size,
		index_number;
	
	stub_packet_type
		*stub_packet;
	
	#if COMMS_DEBUG_BAD_CONNECTION
	
	debug_log ("COMMS BAD CONNECTION: Sending packet requested for %s frame %d, packet %d", send_type_names [send_type], frame_id, packet_id);
	
	#else
	
	debug_log ("WARNING: PACKET BEING RESENT TO PLAYER %d FOR %s FRAME %d, PACKET %d",
					player_id,
					send_type_names [send_type],
					frame_id,
					packet_id);
	
	#endif
	
	resend_packet_counter ++;
	
	stub_packet = resend_packet_list;
	
	while (stub_packet)
	{
		
		if (
			//(packet->packet->player_id == player_id) && // not sure about this one yet.
			(stub_packet->send_type == send_type) &&
			(stub_packet->packet->frame_id == frame_id) &&
			(stub_packet->packet->packet_id == packet_id))
		{

			packet_size = sizeof (packet_header_type) + stub_packet->packet->data_size;

			direct_play_send_data (player_id, (LPVOID) stub_packet->packet, packet_size);
			
			return stub_packet;
		}
		
		stub_packet = stub_packet->next;
	}
	
	debug_log ("COMMS: No packet to resend, REJECTING player %d", player_id);
	
	if (get_comms_model () == COMMS_MODEL_SERVER)
	{

		// never received as client is waiting for other packets....
		
		send_packet (player_id, PACKET_TYPE_SERVER_REJECTED, NULL, 0, SEND_TYPE_PERSONAL);
	}
	else
	{

		if (get_gunship_entity ())
		{
			
			index_number = get_local_entity_index (get_gunship_entity ());
			
			send_packet (get_server_id (), PACKET_TYPE_END_GAME, (void *) &index_number, 4, SEND_TYPE_PERSONAL);

			// should this call start_game_exit () ?
		}
	}
	
	#if DEBUG_MODULE >= 2
	{
		
		char
			buffer [30],
			buffer2 [1024];
		
		strcpy (buffer2, "->");
		
		stub_packet = resend_packet_list;
		
		while (stub_packet)
		{
			
			sprintf (buffer, "(%d:%d:%d)", stub_packet->packet->player_id, stub_packet->packet->frame_id, stub_packet->packet->packet_id);
			
			if ((strlen (buffer2) + strlen (buffer)) > 1020)
			{
				
				strcat (buffer2, "...");
				
				break;
			}
			
			strcat (buffer2, buffer);
			
			stub_packet = stub_packet->next;
		}
		
		debug_log ("COMMS: RESEND LIST");
		
		debug_log (buffer2);
	}
	
	#endif

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void free_connection_packets (DPID connection_id)
{
	
	stub_packet_type
		*destroy_packet,
		*packet;
	
	#if DEBUG_MODULE >= 2
	
	debug_log ("COMMS: Removing connection %d packets from list", connection_id);
	
	#endif
	
	//
	// Free group packets for connection
	//
	
	packet = received_group_packets;
	
	while (packet)
	{

		destroy_packet = packet;
		
		packet = packet->next;
		
		if (destroy_packet->packet->player_id == connection_id)
		{
			
			remove_stub_packet_from_receive_list (SEND_TYPE_GROUP, destroy_packet);
			
			free_stub_packet (destroy_packet);
		}
	}
	
	//
	// Free personal packets for connection
	//
	
	packet = received_personal_packets;
	
	while (packet)
	{

		destroy_packet = packet;
		
		packet = packet->next;
		
		if (destroy_packet->packet->player_id == connection_id)
		{
			
			remove_stub_packet_from_receive_list (SEND_TYPE_PERSONAL, destroy_packet);
			
			free_stub_packet (destroy_packet);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void free_stub_packet (stub_packet_type *stub_packet)
{

	#if DEBUG_MODULE >= 3
	
	debug_log ("COMMS: Free packet");
	
	#endif

	if (stub_packet->packet)
	{

		free_mem (stub_packet->packet);

		stub_packet->packet = NULL;
	}
	
	free_mem (stub_packet);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_stub_packet_to_list (stub_packet_type **list, stub_packet_type *packet)
{
	
	ASSERT (packet);
	
	if (*list)
	{
		
		(*list)->prev = packet;
	}
	
	packet->next = *list;
	
	packet->prev = NULL;
	
	*list = packet;
	
	#if DEBUG_MODULE >= 3
	{
		
		stub_packet_type
			*current_packet;
		
		int
			count = 0;
		
		current_packet = *list;
		
		while (current_packet)
		{
			
			count ++;
			
			current_packet = current_packet->next;
		}
		
		debug_log ("COMMS: Add Stub Packet, count = %d", count);
		
	}
	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void remove_stub_packet_from_list (stub_packet_type **list, stub_packet_type *packet)
{
	
	stub_packet_type
		*next,
		*prev;
	
	next = packet->next;
	
	prev = packet->prev;
	
	if (next)
	{
		
		next->prev = prev;
	}
	
	if (prev)
	{
		
		prev->next = next;
	}
	else
	{
	
		*list = next;
	}
	
	packet->prev = NULL;
	
	packet->next = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DYNAMIC_CHECK_LIST 0

int count_packets_for_frame (stub_packet_type *packet_list, int player_id, int frame_id)
{

	//
	// get dynamics check list working at some point.
	//
	
 	#if DYNAMIC_CHECK_LIST

	static char
		*checklist = NULL;

	static int
		checklist_size = 0;

	int
		largest_frame = 0;

	#else

	static char
		checklist [8096];

	#endif

	stub_packet_type
		*stub_packet;

	int
		packet_count = 0;

 	#if DYNAMIC_CHECK_LIST

	// find largest frame

	stub_packet = packet_list;

	while (stub_packet)
	{

		if (stub_packet->packet->number_of_packets > largest_frame)
		{

			largest_frame = stub_packet->packet->number_of_packets;
		}

		stub_packet = stub_packet->next;
	}

	// malloc enough memory for largest frame

	if (largest_frame > checklist_size)
	{

		if (checklist)
		{

			free_mem (checklist);
		}

		checklist_size = largest_frame + 1;

		checklist = malloc_heap_mem (sizeof (char) * checklist_size);

		#if DEBUG_MODULE

		debug_log ("COMMS: resizing checklist array to %d", checklist_size);

		#endif
	}

	memset (checklist, 0, checklist_size);

	#else

	memset (checklist, 0, 8096);

	#endif
	
	stub_packet = packet_list;
	
	while (stub_packet)
	{

		#if DYNAMIC_CHECK_LIST

		ASSERT (stub_packet->packet->packet_id < checklist_size);

		#endif
		
		if (stub_packet->packet->frame_id == frame_id)
		{
			
			if (stub_packet->packet->player_id == player_id)
			{
				
				if (!(checklist [stub_packet->packet->packet_id]))
				{
					
					packet_count ++;
					
					checklist [stub_packet->packet->packet_id] = TRUE;
				}
				else
				{
					
					#if DEBUG_MODULE
					
					debug_log ("COMMS: not counting packet twice %d %d", frame_id, stub_packet->packet->packet_id);
					
					#endif
				}
			}
		}
		
		stub_packet = stub_packet->next;
	}
	
	#if DEBUG_MODULE
	
	debug_log ("COMMS: received %d packets for frame %d", packet_count, frame_id);
	
	#endif
	
	return packet_count;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_resend_packet_list (int packet_limit)
{
	
	int
		count;
	
	stub_packet_type
		*destroy_packet,
		*packet;
	
	if (resend_packet_list_counter >= packet_limit)
	{
		
		#if DEBUG_MODULE >= 2
		
		debug_log ("COMMS: resend packet list > %d", packet_limit);
		
		#endif
		
		packet = resend_packet_list;
		
		count = 0;
		
		while (packet)
		{
			
			count ++;
			
			destroy_packet = packet;
			
			packet = packet->next;
			
			if (count >= packet_limit)
			{
				
				remove_stub_packet_from_resend_list (destroy_packet);
				
				free_stub_packet (destroy_packet);
			}
		}
	}
	
	#if DEBUG_MODULE >= 4
	{
		
		char
			buffer [10],
			buffer2 [256];
		
		strcpy (buffer2, "->");
		
		packet = resend_packet_list;
		
		while (packet)
		{
			
			sprintf (buffer, "%d:", packet->packet->frame_id);
			
			if ((strlen (buffer2) + strlen (buffer)) > 253)
			{
				
				strcat (buffer2, "...");
				
				break;
			}
			
			strcat (buffer2, buffer);
			
			packet = packet->next;
		}
		
		debug_log ("COMMS: RESEND LIST %d", packet_limit);
		
		debug_log (buffer2);
	}
	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if COMMS_STATS

void debug_comms_stats (void)
{
	
	connection_list_type
		*connection;
	
	stub_packet_type
		*stub_packet;
	
	delta_time = get_system_time () - last_time;
	
	network_frame_time = (delta_time / TIME_1_SECOND);

	if (network_frame_time > 0)
	{
	
		network_frame_rate = 1.0 / network_frame_time;
	}
	else
	{

		network_frame_rate = 0.0;
	}
	
	last_time = get_system_time ();
	
	//
	// count up group packets
	//
	
	stub_packet = received_group_packets;
	
	received_group_list_size = 0;
	
	while (stub_packet)
	{
		
		received_group_list_size += sizeof (stub_packet_type);
		
		received_group_list_size += sizeof (packet_header_type);
		
		stub_packet = stub_packet->next;
	}
	
	//
	// count up personal packets
	//
	
	stub_packet = received_personal_packets;
	
	received_personal_list_size = 0;
	
	while (stub_packet)
	{
		
		received_personal_list_size += sizeof (stub_packet_type);
		
		received_personal_list_size += sizeof (packet_header_type);
		
		stub_packet = stub_packet->next;
	}
	
	//
	// count up resend packets
	//
	
	stub_packet = resend_packet_list;
	
	resend_list_size = 0;
	
	while (stub_packet)
	{
		
		resend_list_size += sizeof (stub_packet_type);
		
		resend_list_size += sizeof (packet_header_type);
		
		stub_packet = stub_packet->next;
	}
	
	//
	// count up rerequest stub packets
	//
	
	stub_packet = rerequest_packet_list;
	
	rerequest_list_size = 0;
	
	while (stub_packet)
	{
		
		rerequest_list_size += sizeof (stub_packet_type);
		
		stub_packet = stub_packet->next;
	}
	
	//
	// count up connections
	//
	
	connection = get_connection_list_head ();
	
	total_connection_size = 0;
	
	while (connection)
	{
		
		total_connection_size += sizeof (connection_list_type);
		
		total_connection_size += connection->connection_receive_buffer_size;
		
		connection = connection->next;
	}
	
	total_data_size = received_group_list_size +
							received_personal_list_size +
							resend_list_size +
							rerequest_list_size +
							command_line_comms_data_record_size +
							total_connection_size;
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_comms_checksum (char *data, int send_size)
{

	int
		loop,
		checksum;

	checksum = 0;

	if (data)
	{
	
		for (loop = 0; loop < send_size; loop ++)
		{
	
			checksum += data [loop];
		}
	}

	return checksum;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_comms_stats (void)
{

	packet_record_data_count = 0;

	total_data_size = 0;
	total_connection_size = 0;
	received_group_list_size = 0;
	received_personal_list_size = 0;
	resend_list_size = 0;
	rerequest_list_size = 0;
	num_packets_received = 0;
	num_packets_sent = 0;

	instant_packet_size_sent = 0.0;
	instant_packet_size_received = 0.0;
	av_packet_size_sent = 0.0;
	av_packet_size_received = 0.0;
	max_packet_size_sent = 0.0;
	max_packet_size_received = 0.0;
	max_processed_size = 0.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_receive_packet_list_time_stamps (void)
{

	stub_packet_type
		*packet;

	packet = received_group_packets;

	while (packet)
	{

		packet->actual_time = get_system_time () + TIME_1_SECOND;

		packet->received_time = get_system_time () + TIME_1_SECOND;

		packet = packet->next;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void display_comms_stats (void)
{

	char
		s[200];

	float
		y;

	if (!command_line_comms_show_stats)
	{

		return;
	}

	if (!begin_3d_scene ())
	{

		return;
	}

	set_full_screen_viewport ();

	y = 0.0;

	set_ui_font_type (UI_FONT_ARIAL_14);
	set_ui_font_colour (sys_col_amber);

	/////////////////////////////////////////////////////////////////

	sprintf (s, "Comms Info:");
	ui_display_text (s, 0, y);
	y += ui_get_font_height () + 1;

	/////////////////////////////////////////////////////////////////

	sprintf (s, "packets sent = %d", num_packets_sent);
	ui_display_text (s, 0, y);
	y += ui_get_font_height () + 1;

	sprintf (s, "packets send size (av) = %.02f", av_packet_size_sent);
	ui_display_text (s, 0, y);
	y += ui_get_font_height () + 1;

	sprintf (s, "packets send size (max) = %.02f", max_packet_size_sent);
	ui_display_text (s, 0, y);
	y += ui_get_font_height () + 1;
	
	sprintf (s, "packets received = %d", num_packets_received);
	ui_display_text (s, 0, y);
	y += ui_get_font_height () + 1;

	sprintf (s, "packets received size (av) = %.02f", av_packet_size_received);
	ui_display_text (s, 0, y);
	y += ui_get_font_height () + 1;

	sprintf (s, "packets received size (max) = %.02f", max_packet_size_received);
	ui_display_text (s, 0, y);
	y += ui_get_font_height () + 1;
	
	sprintf (s, "DirectPlay packet queue = %d", direct_play_get_send_queue_number_of_packets ());
	ui_display_text (s, 0, y);
	y += ui_get_font_height () + 1;

	sprintf (s, "Throttle limit = %d", command_line_comms_packet_throttle_limit);
	ui_display_text (s, 0, y);
	y += ui_get_font_height () + 1;

	if (get_gunship_entity ())
	{

		if (comms_weapon_lag_timing)
		{
		
			sprintf (s, "Weapon lag time = Timing...");
			ui_display_text (s, 0, y);
			y += ui_get_font_height () + 1;
		}
		else
		{
		
			sprintf (s, "Weapon lag time = %0.2f", comms_weapon_lag_time);
			ui_display_text (s, 0, y);
			y += ui_get_font_height () + 1;
		}
	}

	end_3d_scene ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
