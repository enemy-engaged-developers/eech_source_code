// 
//   Enemy Engaged RAH-66 Comanche Versus KA-52 Hokum
//   Copyright (C) 2000 Empire Interactive (Europe) Ltd,
//   677 High Road, North Finchley, London N12 0DA
// 
//   Please see the document LICENSE.TXT for the full licence agreement
// 
// 2. LICENCE
//  2.1     
//      Subject to the provisions of this Agreement we now grant to you the 
//      following rights in respect of the Source Code:
//   2.1.1 
//      the non-exclusive right to Exploit  the Source Code and Executable 
//      Code on any medium; and 
//   2.1.2 
//      the non-exclusive right to create and distribute Derivative Works.
//  2.2     
//      Subject to the provisions of this Agreement we now grant you the
//  following rights in respect of the Object Code:
//   2.2.1 
//  the non-exclusive right to Exploit the Object Code on the same
//  terms and conditions set out in clause 3, provided that any
//  distribution is done so on the terms of this Agreement and is
//  accompanied by the Source Code and Executable Code (as
//  applicable).
// 
// 3. GENERAL OBLIGATIONS
//  3.1 
//      In consideration of the licence granted in clause 2.1 you now agree:
//   3.1.1 
//  that when you distribute the Source Code or Executable Code or
//  any Derivative Works to Recipients you will also include the
//  terms of this Agreement;
//   3.1.2 
//  that when you make the Source Code, Executable Code or any
//  Derivative Works ("Materials") available to download, you will
//  ensure that Recipients must accept the terms of this Agreement
//  before being allowed to download such Materials;
//   3.1.3 
//  that by Exploiting the Source Code or Executable Code you may
//  not impose any further restrictions on a Recipient's subsequent
//  Exploitation of the Source Code or Executable Code other than
//  those contained in the terms and conditions of this Agreement;
//   3.1.4 
//  not (and not to allow any third party) to profit or make any
//  charge for the Source Code, or Executable Code, any
//  Exploitation of the Source Code or Executable Code, or for any
//  Derivative Works;
//   3.1.5 
//  not to place any restrictions on the operability of the Source 
//  Code;
//   3.1.6 
//  to attach prominent notices to any Derivative Works stating
//  that you have changed the Source Code or Executable Code and to
//  include the details anddate of such change; and
//   3.1.7 
//      not to Exploit the Source Code or Executable Code otherwise than
//  as expressly permitted by  this Agreement.
// 



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define INTERNAL_MODULES 1

#include "project.h"
//-- Werewolf
#include <winsock.h>
//-- Werewolf

// crh 030408 new single global version header
#include "version.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// DEBUG LEVELS
//
// 1 - minimal
// 2 - maximal

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char
    *tx_pack_buffer;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static char
    session_data,
    *data_record;

int
    data_record_size;

server_response_types
    server_response;

//-- Werewolf
SOCKADDR_IN Master;
SOCKADDR_IN Master2;
int mastersocket = -1;
int mastersocket2 = -1;
short MasterPort = 1375;
int num_multiplayer_refreshes = 0;
int last_heartbeat_time = 0;
char localplayer[256];
char ReceiveBuffer[65535];
char SendBuffer[65535];
int PACKET_SIZE = 4096; // This should be set from network.cpp
SOCKADDR from;
ServerData Servers[1000];
int numServers = 0;
//-- Werewolf


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void comms_record_data (char *data, int size);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_comms_manager (void)
{


    #if DEBUG_MODULE

    debug_log ("COMMS MAN: initialising comms manager: data size = %d", command_line_comms_data_record_size, direct_play_get_player_id ());

    #endif

    set_server_response (SERVER_RESPONSE_UNKNOWN);

    data_record = (char *) malloc_heap_mem (command_line_comms_data_record_size);

    add_update_function (send_comms_data, 1.0 / command_line_max_game_update_rate , 1.0);
    //add_update_function (data_exchange, 1.0 / command_line_max_game_update_rate , 1.0);

    if (command_line_comms_validate_connections)
    {

		//add_update_function (validate_connections, command_line_comms_timeout, 1.0);

		add_update_function (validate_connections, 3.0, 1.0); // Jabberwock - VC was called to rarely if cto was high
    }

    tx_pack_buffer = (char *) malloc_heap_mem (sizeof (char) * command_line_comms_pack_buffer_size);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_comms_manager (void)
{

    #if DEBUG_MODULE

    debug_log ("COMMS MAN: deinitialising comms manager");

    #endif

    free_mem (data_record);

    if (tx_pack_buffer)
    {

        free_mem (tx_pack_buffer);
    }

    //initialise_entity_list_validation ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void comms_clear_data_record (void)
{

    #if DEBUG_MODULE >= 2

    debug_log ("COMMS MAN: clearing data record");

    #endif

    #if COMMS_STATS

    packet_record_data_count = 0;

    #endif

    ASSERT (data_record);

    ASSERT (command_line_comms_data_record_size != 0);

    memset (data_record, 0, command_line_comms_data_record_size);

    data_record_size = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void comms_record_data (char *data, int size)
{

    char
        *new_data_record;

    //
    // Check data_record is big enough
    //

    while (data_record_size + size > command_line_comms_data_record_size)
    {

        new_data_record = (char *) malloc_heap_mem (command_line_comms_data_record_size * 2);

        ASSERT (data_record);

        memcpy (new_data_record, data_record, command_line_comms_data_record_size);

        command_line_comms_data_record_size *= 2;

        free_mem (data_record);

        data_record = new_data_record;

        #if DEBUG_MODULE

        debug_log ("COMMS MAN: MAX_DATA_RECORD_SIZE exceeded, mallocing %d (requested %d)", command_line_comms_data_record_size, data_record_size + size);

        #endif
    }

    //
    // Store size of data
    //

    memcpy (&data_record [data_record_size], &size, sizeof (int));

    data_record_size += sizeof (int);

    //
    // Store data
    //

    #if DEBUG_MODULE >= 2

    debug_log ("COMMS MAN: recording %d data", size);

    #endif

    #if COMMS_STATS

    packet_record_data_count ++;

    #endif

    memcpy (&data_record [data_record_size], data, size);

    data_record_size += size;

    //
    // latency test
    //
    {

        int
            packet_count;

        packet_count = data_record_size / command_line_comms_packet_data_size;

        if (packet_count > 1)
        {

            //debug_log ("COMM_MAN: possible packet latency problem. Holding %d packets", packet_count);
        }
    }
    //
    // end
    //
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_number_of_connected_players (void)
{
    connection_list_type
        *temp_connection;

    int
        player_count;

    temp_connection = get_connection_list_head ();

    player_count = 0;

    while (temp_connection)
    {
        player_count ++;

        temp_connection = temp_connection->next;
    }

    return player_count;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void data_exchange (void)
{

    int
        packet_data_size;

    connection_data_type
        *this_connection;

    this_connection = direct_play_get_connection_data ();

    if ((this_connection) && (this_connection->is_initialised))
    {

        #if DEBUG_MODULE >= 2

        debug_log ("COMMS MAN: Data exchange");

        #endif

        if (get_current_pack_buffer_bit_size () > 0)
        {

            transmit_entity_comms_message (ENTITY_COMMS_END, NULL);
        }

        ASSERT (!get_pack_buffer_overflow ());

        #if DEBUG_MODULE >= 2

        debug_log ("COMM_MAN: closing pack buffer line.216");

        #endif

        packet_data_size = close_pack_buffer ();

        if (packet_data_size > 0)
        {

            comms_record_data (tx_pack_buffer, packet_data_size);
        }

        #if DEBUG_MODULE >= 2

        debug_log ("COMM_MAN: opening pack buffer line.224");

        #endif

        open_pack_buffer (tx_pack_buffer, command_line_comms_pack_buffer_size);

        //
        // receive all packets waiting
        //

        receive_packets ();

        #if COMMS_STATS

        debug_comms_stats ();

        #endif

        //
        // process all data received this frame
        //

        comms_process_data ();

        //
        // send all data for this frame
        //

        comms_send_data ();

        //
        // reset the data record for next frame
        //

        comms_clear_data_record ();

        //
        // check resend list
        //

        update_resend_packet_list (command_line_comms_resend_list_size);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void receive_comms_data (void)
{

    connection_data_type
        *this_connection;

    this_connection = direct_play_get_connection_data ();

    if ( ( this_connection ) && ( this_connection->is_initialised ) )
    {

        //
        // receive all packets waiting
        //

        receive_packets ();

        #if COMMS_STATS

        //debug_comms_stats ();

        #endif

        //
        // process all data received this frame
        //

        comms_process_data ();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void send_comms_data (void)
{

    int
        packet_data_size;

    //
    //
    //

    direct_play_get_message_queue ();

    if (direct_play_get_send_queue_number_of_packets () > command_line_comms_packet_throttle_limit)
    {

        #if DEBUG_MODULE

        debug_log ("COMM_MAN: Throttling to %d, %d packets waiting", command_line_comms_packet_throttle_limit, direct_play_get_send_queue_number_of_packets ());

        #endif

        return;
    }

    //
    //
    //

    if (get_current_pack_buffer_bit_size () > 0)
    {

        transmit_entity_comms_message (ENTITY_COMMS_END, NULL);
    }

    ASSERT (!get_pack_buffer_overflow ());

    packet_data_size = close_pack_buffer ();

    if (packet_data_size > 0)
    {

        comms_record_data (tx_pack_buffer, packet_data_size);
    }

    open_pack_buffer (tx_pack_buffer, command_line_comms_pack_buffer_size);

    //
    // send all data for this frame
    //

    comms_send_data ();

    #if COMMS_STATS

    debug_comms_stats ();

    #endif

    //
    // reset the data record for next frame
    //

    comms_clear_data_record ();

    update_resend_packet_list (command_line_comms_resend_list_size);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void comms_send_data (void)
{

    if (data_record_size > 0)
    {

        send_packet (get_packet_destination (), PACKET_TYPE_AI_DATA, data_record, data_record_size, SEND_TYPE_GROUP);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 29AUG05 Casm Fix for wut transfer - don't overwrite pointers!
static void smart_memcpy ( void * dst, const void * src, int elemsize, int skipsize, int elems )
{
	for ( ; elems > 0; elems--)
	{
		memcpy ( ( char * ) dst + skipsize, ( const char * ) src + skipsize, elemsize - skipsize );
		src = ( const char * ) src + elemsize;
		dst = ( char * ) dst + elemsize;
	}
}

// 01OCT05 Casm yet another fix for wut transfer - special care for platoon_name field in group_database
static void group_database_cpy ( group_data * dst, const group_data * src )
{
	int
		elems;
	const char
		*tmp;

	for ( elems = NUM_ENTITY_SUB_TYPE_GROUPS; elems > 0; elems--)
	{
		tmp = dst->platoon_name;
		memcpy ( ( char * ) dst + 2 * sizeof ( const char * ), ( const char * ) src + 2 * sizeof ( const char * ), sizeof ( group_data ) - 2 * sizeof ( const char * ) );
		dst->platoon_name = tmp;
		src++;
		dst++;
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void comms_process_data (void)
{

    session_list_data_type
        *current_session;

    connection_list_type
        *this_connection,
        *connection;

    char
        *received_data;

    int
        planner_event,
        frame_id,
        packet_id,
        receive_flag,
        received_size;

    DPID
        received_id = 0;

    entity
        *member;

    send_types
        send_type;

    packet_types
        type;

    // receive all packets in queue

    current_session = get_current_game_session ();

    received_size = MAX_RECEIVE_SIZE;

    connection = get_connection_list_head ();

    while (connection)
    {

        this_connection = connection;

        connection = connection->next;

        send_type = SEND_TYPE_GROUP;

        while (send_type >= SEND_TYPE_PERSONAL)
        {

            receive_flag = TRUE;

            while (receive_flag)
            {

                type = process_packet_list (send_type, this_connection, &received_id, &received_data, &received_size);

                switch (type)
                {

                    ///////////////////////////////////////////////////////////////////////////////////////////////
                    //
                    // System packets, used internally
                    //
                    ///////////////////////////////////////////////////////////////////////////////////////////////

                    case PACKET_TYPE_INVALID:
                    {

                        receive_flag = FALSE;

                        if (get_comms_model () == COMMS_MODEL_SERVER)
                        {

                            if (this_connection->packet_rerequested > command_line_comms_packet_rerequest_limit)
                            {

                                debug_log ("COMM_MAN: REJECTING CONNECTION. CONNECTION TOO BAD (re-request limit %d reached)", command_line_comms_packet_rerequest_limit);

                                send_packet (this_connection->connection_id, PACKET_TYPE_SERVER_REJECTED, NULL, 0, SEND_TYPE_PERSONAL);
                            }
                        }

                        break;
                    }

                    case PACKET_TYPE_RESEND_PACKET:
                    {

                        send_types
                            resend_send_type;

                        frame_id = get_list_item (received_data, int);

                        packet_id = get_list_item (received_data, int);

                        resend_send_type = get_list_item (received_data, send_types);

                        #if DEBUG_MODULE

                        if (this_connection->pilot_entity)
                        {

                            debug_log ("COMMS MAN: received RESEND PACKET for frame %d packet %d from %s (dpid %d)",
                                            frame_id, packet_id,
                                            get_local_entity_string (this_connection->pilot_entity, STRING_TYPE_PILOTS_NAME),
                                            received_id);
                        }
                        else
                        {

                            debug_log ("COMMS MAN: received RESEND PACKET by unknown (pdid %d)",
                                            received_id);
                        }

                        #endif

                        resend_packet (received_id, frame_id, packet_id, resend_send_type);

                        break;
                    }

                    ///////////////////////////////////////////////////////////////////////////////////////////////
                    //
                    // Packets for initialisation and joining
                    //
                    ///////////////////////////////////////////////////////////////////////////////////////////////

                    case PACKET_TYPE_SESSION_QUERY:
                    {

                        char
                            *ptr;

                        int
                            server_version_number,
                            player_count,
                            size;

                        connection_list_type
                            *new_connection;

                        if (get_comms_model () == COMMS_MODEL_SERVER)
                        {

                            #if DEBUG_MODULE

                            if (this_connection->pilot_entity)
                            {

                                debug_log ("COMMS MAN: RECEIVED SESSION QUERY from %s (dpid %d)",
                                                get_local_entity_string (this_connection->pilot_entity, STRING_TYPE_PILOTS_NAME),
                                                received_id);
                            }
                            else
                            {

                                debug_log ("COMMS MAN: RECEIVED SESSION QUERY from %d", received_id);
                            }

                            #endif

                            new_connection = get_connection_list_item (received_id);

                            if (!new_connection->already_sent_query_data)
                            {

                                new_connection->already_sent_query_data = TRUE;

                                while (TRUE)
                                {

                                    ptr = new_connection->connection_receive_buffer;

                                    size = 0;

                                    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                    //
                                    // Check both client and server are running same campaign data
                                    //

                                    // Jabberwock 050301 Hardcoded version number

                                    // please put in the date of the version! check it is changed twice!
                                    server_version_number = 1621; // Jabberwock 050322

                                    quick_set_list_item (ptr, int, server_version_number);

                                    size += sizeof (int);
                                    //
                                    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                    // map details

                                    quick_set_list_item (ptr, int, NUM_MAP_X_SECTORS);

                                    quick_set_list_item (ptr, int, NUM_MAP_Z_SECTORS);

                                    quick_set_list_item (ptr, int, SECTOR_SIDE_LENGTH);

                                    size += sizeof (int) * 3;

                                    // data path

                                    strcpy (ptr, current_session->data_path);

                                    ptr += strlen (current_session->data_path) + 1;

                                    size += strlen (current_session->data_path) + 1;

                                    // population_placement filename

                                    if (population_placement_filename)
                                    {

                                        strcpy (ptr, population_placement_filename);

                                        ptr += strlen (population_placement_filename) + 1;

                                        size += strlen (population_placement_filename) + 1;
                                    }
                                    else
                                    {

                                        strcpy (ptr, "\0");

                                        ptr += strlen ("\0") + 1;

                                        size += strlen ("\0") + 1;
                                    }

                                    //

                                    // side_data filename

                                    if (side_data_filename)
                                    {

                                        strcpy (ptr, side_data_filename);

                                        ptr += strlen (side_data_filename) + 1;

                                        size += strlen (side_data_filename) + 1;
                                    }
                                    else
                                    {

                                        strcpy (ptr, "\0");

                                        ptr += strlen ("\0") + 1;

                                        size += strlen ("\0") + 1;
                                    }

                                    // campaign_population filename

                                    if (campaign_population_filename)
                                    {

                                        strcpy (ptr, campaign_population_filename);

                                        ptr += strlen (campaign_population_filename) + 1;

                                        size += strlen (campaign_population_filename) + 1;
                                    }
                                    else
                                    {

                                        strcpy (ptr, "\0");

                                        ptr += strlen ("\0") + 1;

                                        size += strlen ("\0") + 1;
                                    }

                                    //
                                    // planner position and zoom
                                    //

//                                  quick_set_list_item (ptr, float, planner_map_data.centre_map_x);

//                                  quick_set_list_item (ptr, float, planner_map_data.centre_map_z);

//                                  size += sizeof (float) * 2;

//                                  quick_set_list_item (ptr, int, planner_map_data.map_zoom);

//                                  size += sizeof (int);

                                    //
                                    // Pilots
                                    //

                                    player_count = get_number_of_connected_players ();

                                    quick_set_list_item (ptr, int, player_count);

                                    size += sizeof (int);

                                    //
                                    //
                                    //

                                    #if DEBUG_MODULE

                                    debug_log ("COMM_MAN: sending data path %s, population placement %s, side data %s, campaign_pop file %s",
                                                    current_session->data_path, population_placement_filename, side_data_filename, campaign_population_filename);

                                    #endif

                                    new_connection->connection_receive_buffer_size -= size;

                                    if (!pack_session (ptr, &new_connection->connection_receive_buffer_size, PACK_MODE_BROWSE_SESSION))
                                    {

                                        break;
                                    }

                                    new_connection->connection_receive_buffer_size *= 2;

                                    #if DEBUG_MODULE

                                    debug_log ("COMMS MAN: Browse: connection_receive_buffer too small, mallocing to %d", new_connection->connection_receive_buffer_size);

                                    #endif

                                    free_mem (new_connection->connection_receive_buffer);

                                    new_connection->connection_receive_buffer = malloc_heap_mem (new_connection->connection_receive_buffer_size);
                                }

                                //
                                //
                                //

                                send_packet (received_id, PACKET_TYPE_SESSION_INFO, new_connection->connection_receive_buffer, new_connection->connection_receive_buffer_size + size, SEND_TYPE_PERSONAL);

                                /*
                                {

                                    FILE
                                        *test_ptr;

                                    test_ptr = fopen ("out.txt", "wb");

                                    fwrite (new_connection->connection_receive_buffer, 1, new_connection->connection_receive_buffer_size + size, test_ptr);

                                    fclose (test_ptr);
                                }
                                */
                            }
                            else
                            {

                                debug_log ("COMM_MAN: not resending query data");
                            }
                        }

                        break;
                    }

// Jabberwock 031118 Server side settings

                    case PACKET_TYPE_SETTINGS_REQUEST:
					{
                        char
                        	buf [256],
                            *ptr;

                        int
                            size;

                        FILE
                     		*fp;

                        connection_list_type
                            *new_connection;

						if (get_comms_model () == COMMS_MODEL_SERVER)
						{
							send_comms_data ();

                            new_connection = get_connection_list_item (received_id);

         		       	    ptr = new_connection->connection_receive_buffer;

							size = 0;

							// MOTD

							strcpy (buf, "\0");

							if (file_exist ("motd.txt"))
							{
								if (file_size ("motd.txt") < 256)
								{

									fp = fopen ("motd.txt", "r" );

									if ( fp )
									{
										fscanf (fp, "%[^\n]\n", buf);

										fclose ( fp );
									}
								}
								else
								{
									server_log ("motd.txt too long!");
								}
							}

							strcpy (ptr, buf);

							ptr += strlen (buf) + 1;

							size += strlen (buf) + 1;
							// end of MOTD

							// WUT checking

							if (command_line_wut)
							{
								strcpy (ptr, WUT_filename);

								ptr += strlen (WUT_filename) + 1;

								size += strlen (WUT_filename) + 1;
							}
							else
							{
								strcpy (ptr, "NONE");

								ptr += strlen ("NONE") + 1;

								size += strlen ("NONE") + 1;
							}

							// Jabberwock 050129 WUT transfer - server side
							// with great help from Gotcha

							// Aircraft

							memcpy (ptr, aircraft_database, sizeof(aircraft_database));

							ptr += sizeof(aircraft_database);

							size += sizeof(aircraft_database);

							// Vehicle

							memcpy (ptr, vehicle_database, sizeof(vehicle_database));

							ptr += sizeof(vehicle_database);

							size += sizeof(vehicle_database);

							// Weapon

							memcpy (ptr, weapon_database, sizeof(weapon_database));

							ptr += sizeof(weapon_database);

							size += sizeof(weapon_database);

							// Keysite

							memcpy (ptr, keysite_database, sizeof(keysite_database));

							ptr += sizeof(keysite_database);

							size += sizeof(keysite_database);

							// Group

							memcpy (ptr, group_database, sizeof(group_database));

							ptr += sizeof(group_database);

							size += sizeof(group_database);

							// Task

							memcpy (ptr, task_database, sizeof(task_database));

							ptr += sizeof(task_database);

							size += sizeof(task_database);

							// Waypoint

							memcpy (ptr, waypoint_database, sizeof(waypoint_database));

							ptr += sizeof(waypoint_database);

							size += sizeof(waypoint_database);

							// Guide

							memcpy (ptr, guide_database, sizeof(guide_database));

							ptr += sizeof(guide_database);

							size += sizeof(guide_database);

							// Radar

							memcpy (ptr, radar_range_apache, sizeof(radar_range_apache));

							ptr += sizeof(radar_range_apache);

							size += sizeof(radar_range_apache);

							memcpy (ptr, radar_range_comanche, sizeof(radar_range_comanche));

							ptr += sizeof(radar_range_comanche);

							size += sizeof(radar_range_comanche);

							memcpy (ptr, radar_range_blackhawk, sizeof(radar_range_blackhawk));

							ptr += sizeof(radar_range_blackhawk);

							size += sizeof(radar_range_blackhawk);

							memcpy (ptr, radar_range_hokum, sizeof(radar_range_hokum));

							ptr += sizeof(radar_range_hokum);

							size += sizeof(radar_range_hokum);

							memcpy (ptr, radar_range_havoc, sizeof(radar_range_havoc));

							ptr += sizeof(radar_range_havoc);

							size += sizeof(radar_range_havoc);

							memcpy (ptr, radar_range_hind, sizeof(radar_range_hind));

							ptr += sizeof(radar_range_hind);

							size += sizeof(radar_range_hind);

							// Jabberwock 050129 ends

							quick_set_list_item (ptr, int, command_line_planner_goto_button);

							size += sizeof (int);

							quick_set_list_item (ptr, int, command_line_vector_flight_model);

							size += sizeof (int);

							quick_set_list_item (ptr, int, command_line_ground_radar_ignores_infantry);

							size += sizeof (int);

							quick_set_list_item (ptr, int, command_line_camcom);

							size += sizeof (int);

							// 03DEC05 Casm Added season info transer
							//VJ 051227 use set and get global season here
							quick_set_list_item (ptr, int, get_global_season() );

							size += sizeof (int);

							send_packet (received_id, PACKET_TYPE_SETTINGS_DATA, new_connection->connection_receive_buffer, new_connection->connection_receive_buffer_size + size, SEND_TYPE_PERSONAL);

						}

						break;
					}

					case PACKET_TYPE_SETTINGS_DATA:
                    {
                        int
                            size;

                        char
                            *ptr,
                            motd [256],
                            buffer [256],
                            temp_wut_filename[128];

						int
							season;

	                   	ptr = received_data;

                        size = 0;

						ui_object_destroy_list_items (session_info_list);

						// MOTD


						strncpy (motd, ptr, sizeof (motd));

						ptr += strlen (motd) + 1;

						size += strlen (motd) + 1;

						if (strlen (motd) > 0)
						{
							sprintf (buffer, "%s", motd);

							add_to_pop_up_list_with_word_wrap (buffer, session_info_list, NULL, 0, UI_FONT_ARIAL_10, sys_col_white);

							add_to_pop_up_list_with_word_wrap (" ", session_info_list, NULL, 0, UI_FONT_ARIAL_10, sys_col_white);
						}


                        // WUT

                        strncpy (temp_wut_filename, ptr, sizeof (temp_wut_filename));

                        ptr += strlen (temp_wut_filename) + 1;

                        size += strlen (temp_wut_filename) + 1;

                        strcpy(session_WUT_filename, temp_wut_filename);

                     // Jabberwock 050129 WUT transfer - client side
                     // with great help from Gotcha

					 /*	not needed anymore, hopefully!
                        if (stricmp (session_WUT_filename, "NONE") != 0)
                        {
                       		if (!file_exist(session_WUT_filename))
                       		{
                       			sprintf (buffer, "%s: %s", get_trans ("Missing local WUT file"), temp_wut_filename);

                       			add_to_pop_up_list_with_word_wrap (buffer, session_info_list, NULL, 0, UI_FONT_ARIAL_10, sys_col_white);

		               			set_ui_object_drawable (session_screen_continue_bdrop, FALSE);

										set_ui_object_drawable (session_screen_continue_button, FALSE);

	                       		break;
	                       	}
	                       	else
									{
	                       		parse_WUT_file(session_WUT_filename);
	                       	}
                        }
                        else
//VJ 050110 check for origwut.txt or gwut146x.csv
                        {
                        	if (file_exist("origwut.txt"))
                        		parse_WUT_file("origwut.txt");
                        	else
                        	if (file_exist("gwut146x.csv"))
                        		parse_WUT_file("gwut146x.csv");
                        }
						*/

                        sprintf (buffer, "%s: %s", get_trans ("Server WUT version"), session_WUT_filename);

						add_to_pop_up_list_with_word_wrap (buffer, session_info_list, NULL, 0, UI_FONT_ARIAL_10, sys_col_white);

						// 29AUG05 Casm Fix for wut transfer - don't overwrite pointers!

						// Aircraft

						smart_memcpy ( aircraft_database, ptr, sizeof ( *aircraft_database ), 4 * sizeof ( const char * ), sizeof ( aircraft_database ) / sizeof ( *aircraft_database ) );

						ptr += sizeof(aircraft_database);

						size += sizeof(aircraft_database);

						// Vehicle

						smart_memcpy ( vehicle_database, ptr, sizeof ( *vehicle_database ), 4 * sizeof ( const char * ), sizeof ( vehicle_database ) / sizeof ( *vehicle_database ) );

						ptr += sizeof(vehicle_database);

						size += sizeof(vehicle_database);

						// Weapon

						smart_memcpy ( weapon_database, ptr, sizeof ( *weapon_database ), 5 * sizeof ( const char * ), sizeof ( weapon_database ) / sizeof ( *weapon_database ) );

						ptr += sizeof(weapon_database);

						size += sizeof(weapon_database);

						// Keysite

						smart_memcpy ( keysite_database, ptr, sizeof ( *keysite_database ), 2 * sizeof ( const char * ), sizeof ( keysite_database ) / sizeof ( *keysite_database ) );

						ptr += sizeof(keysite_database);

						size += sizeof(keysite_database);

						// Group

						// 01OCT05 Casm yet another fix for wut transfer - special care for platoon_name field in group_database
						group_database_cpy ( group_database, ( const group_data * ) ptr );

						ptr += sizeof(group_database);

						size += sizeof(group_database);

						// Task

						smart_memcpy ( task_database, ptr, sizeof ( *task_database ), 3 * sizeof ( const char * ), sizeof ( task_database ) / sizeof ( *task_database ) );

						ptr += sizeof(task_database);

						size += sizeof(task_database);

						// Waypoint

						smart_memcpy ( waypoint_database, ptr, sizeof ( *waypoint_database ), 1 * sizeof ( const char * ), sizeof ( waypoint_database ) / sizeof ( *waypoint_database ) );

						ptr += sizeof(waypoint_database);

						size += sizeof(waypoint_database);

						// Guide

						memcpy (guide_database, ptr, sizeof(guide_database));

						ptr += sizeof(guide_database);

						size += sizeof(guide_database);

						// Radar

						memcpy (radar_range_apache, ptr, sizeof(radar_range_apache));

						ptr += sizeof(radar_range_apache);

						size += sizeof(radar_range_apache);

						memcpy (radar_range_comanche, ptr , sizeof(radar_range_comanche));

						ptr += sizeof(radar_range_comanche);

						size += sizeof(radar_range_comanche);

						memcpy (radar_range_blackhawk, ptr, sizeof(radar_range_blackhawk));

						ptr += sizeof(radar_range_blackhawk);

						size += sizeof(radar_range_blackhawk);

						memcpy (radar_range_hokum, ptr, sizeof(radar_range_hokum));

						ptr += sizeof(radar_range_hokum);

						size += sizeof(radar_range_hokum);

						memcpy (radar_range_havoc, ptr, sizeof(radar_range_havoc));

						ptr += sizeof(radar_range_havoc);

						size += sizeof(radar_range_havoc);

						memcpy (radar_range_hind, ptr, sizeof(radar_range_hind));

						ptr += sizeof(radar_range_hind);

						size += sizeof(radar_range_hind);

						// Jabberwock 050129 ends

                        session_planner_goto_button = get_list_item (ptr, int);

                        size += sizeof (int);

                        sprintf (buffer, "%s: %d", get_trans ("Map GOTO button"), session_planner_goto_button);

						add_to_pop_up_list_with_word_wrap (buffer, session_info_list, NULL, 0, UI_FONT_ARIAL_10, sys_col_white);

						session_vector_flight_model = get_list_item (ptr, int);

                        size += sizeof (int);

                        sprintf (buffer, "%s: %d", get_trans ("Vector flight model"), session_vector_flight_model);

						add_to_pop_up_list_with_word_wrap (buffer, session_info_list, NULL, 0, UI_FONT_ARIAL_10, sys_col_white);

						session_ground_radar_ignores_infantry = get_list_item (ptr, int);

                        size += sizeof (int);

                        sprintf (buffer, "%s: %d", get_trans ("Radar ignores infantry"), session_ground_radar_ignores_infantry);

						add_to_pop_up_list_with_word_wrap (buffer, session_info_list, NULL, 0, UI_FONT_ARIAL_10, sys_col_white);

						session_camcom = get_list_item (ptr, int);

                        size += sizeof (int);

                        sprintf (buffer, "%s: %d", get_trans ("Campaign Commander"), session_camcom);

						add_to_pop_up_list_with_word_wrap (buffer, session_info_list, NULL, 0, UI_FONT_ARIAL_10, sys_col_white);

						// 03DEC05 Casm Added season info transer
						season = get_list_item (ptr, int);

                        size += sizeof (int);

						if (season > 0 && season <= 3)
						{
							const char
								*seasons[4] = { NULL, "Summer", "Winter", "Desert" };

							//VJ 051227 use set and get global season here
							set_global_season ( season );

							add_to_pop_up_list_with_word_wrap (get_trans(seasons[season]), session_info_list, NULL, 0, UI_FONT_ARIAL_10, sys_col_white);
						}

               			set_ui_object_drawable (session_screen_continue_bdrop, FALSE);

						set_ui_object_drawable (session_screen_continue_button, FALSE);

               			set_ui_object_drawable (session_screen_next_bdrop, TRUE);

						set_ui_object_drawable (session_screen_next_button, TRUE);

						break;

                    }
// Jabberwock 031118 ends

                    case PACKET_TYPE_CONNECTION_VALIDATION:
                    {

                        debug_log ("COMM_MAN: received CONNECTION_VALIDATION, sending RESPONSE");

                        send_packet (received_id, PACKET_TYPE_CONNECTION_RESPONSE, NULL, 0, SEND_TYPE_PERSONAL);

                        break;
                    }

                    case PACKET_TYPE_CONNECTION_RESPONSE:
                    {

                        connection_list_type
                            *connection;

                        connection = get_connection_list_item (received_id);

                        connection->validation_count = 0;

                        connection->connection_validation_time = get_system_time (); // Jabberwock - Validation reset

                        debug_log ("COMM_MAN: received CONNECTION_RESPONSE, connection still alive");

                        break;
                    }

                    case PACKET_TYPE_SESSION_INFO:
                    {

                        entity
                            *force,
                            *pilot;

                        int
                            client_version_number,
                            server_version_number;

                        int
                            size,
                            x_size,
                            z_size,
                            sector_size,
                            player_count,
                            loop;

                        char
                            *ptr,
                            warzone_ffp_filename [256],
                            temp_campaign_population_filename [256],
                            temp_population_placement_filename [256],
                            temp_side_data_filename [256],
                            buffer [128];

                        session_data = FALSE;

                        reinitialise_entity_system ();

                        ptr = received_data;

                        size = 0;

                        set_ui_object_redraw (gunships_screen, TRUE);

                        ui_force_update ();

                        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //
                        // Check both client and server are running same campaign data
                        //

                        // Jabberwock 050301 Hardcoded version number

                        // please put in the date of the version! check it is changed twice!

                        client_version_number = 1621; // Jabberwock 050322

                        server_version_number = get_list_item (ptr, int);

                        size += sizeof (int);

                        if (client_version_number != server_version_number)
                        {
							//schorpp
                            debug_log ("COMM_MAN: Incorrect version. Server Version No. %d, Client Version No. %d", server_version_number, client_version_number);
							// Jabberwock 031118 Tell version is wrong
							ui_object_destroy_list_items (session_info_list);
							add_to_pop_up_list_with_word_wrap (get_trans ("Incompatible game version"), session_info_list, NULL, 0, UI_FONT_ARIAL_10, sys_col_white);
							//start_game_exit (GAME_EXIT_KICKOUT, FALSE);
							break;
                        }
                        //
                        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

						// Jabberwock 050320 Downwash MP check
						if (command_line_downwash)
						{
							ui_object_destroy_list_items (session_info_list);
							add_to_pop_up_list_with_word_wrap (get_trans ("Downwash has to be turned off for multiplayer. Change the setting in the ini file (dwash=0) and restart the game."), session_info_list, NULL, 0, UI_FONT_ARIAL_10, sys_col_white);
							//start_game_exit (GAME_EXIT_KICKOUT, FALSE);
							break;
                        }
                        // Jabberwock 050320 ends

                        // map details

                        x_size = get_list_item (ptr, int);

                        z_size = get_list_item (ptr, int);

                        sector_size = get_list_item (ptr, int);

                        size += (sizeof (int) * 3);

                        set_entity_world_map_size (x_size, z_size, sector_size);

                        // data path

                        strncpy (current_session->data_path, ptr, sizeof (current_session->data_path));

                        ptr += strlen (current_session->data_path) + 1;

                        size += strlen (current_session->data_path) + 1;

                        // population_placement_filename

                        strncpy (temp_population_placement_filename, ptr, sizeof (temp_population_placement_filename));

                        ptr += strlen (temp_population_placement_filename) + 1;

                        size += strlen (temp_population_placement_filename) + 1;

                        if (population_placement_filename)
                        {

                            free_mem (population_placement_filename);
                        }

                        if (strlen (temp_population_placement_filename) > 0)
                        {

                            population_placement_filename = (char *) malloc_heap_mem (strlen (temp_population_placement_filename) + 1);

                            sprintf (population_placement_filename, "%s", temp_population_placement_filename);
                        }
                        else
                        {

                            population_placement_filename = NULL;
                        }

                        // side_data filename

                        strncpy (temp_side_data_filename, ptr, sizeof (temp_side_data_filename));

                        ptr += strlen (temp_side_data_filename) + 1;

                        size += strlen (temp_side_data_filename) + 1;

                        if (side_data_filename)
                        {

                            free_mem (side_data_filename);
                        }

                        if (strlen (temp_side_data_filename) > 0)
                        {

                            side_data_filename = (char *) malloc_heap_mem (strlen (temp_side_data_filename) + 1);

                            sprintf (side_data_filename, "%s", temp_side_data_filename);
                        }
                        else
                        {

                            side_data_filename = NULL;
                        }

                        // campaign_population_filename

                        strncpy (temp_campaign_population_filename, ptr, sizeof (temp_campaign_population_filename));

                        ptr += strlen (temp_campaign_population_filename) + 1;

                        size += strlen (temp_campaign_population_filename) + 1;

                        if (campaign_population_filename)
                        {

                            free_mem (campaign_population_filename);
                        }

                        if (strlen (temp_campaign_population_filename) > 0)
                        {

                            campaign_population_filename = (char *) malloc_heap_mem (strlen (temp_campaign_population_filename) + 1);

                            sprintf (campaign_population_filename, "%s", temp_campaign_population_filename);
                        }
                        else
                        {

                            campaign_population_filename = NULL;
                        }

                        //
                        //
                        //

                        player_count = get_list_item (ptr, int);

                        size += sizeof (int);

                        //
                        //
                        //

                        received_size -= size;

                        #if DEBUG_MODULE

                        debug_log ("COMM_MAN: data path %s population placement filename %s, side data filename %s", current_session->data_path, population_placement_filename, side_data_filename);

                        debug_log ("COMM_MAN: campaign data path = %s", current_session->data_path);

                        #endif

                        //
                        // check we have the correct warzone locally
                        //

                        sprintf (warzone_ffp_filename, "%s\\terrain\\terrain.ffp", current_session->data_path);

                        if (!file_exist (warzone_ffp_filename))
                        {

                            add_to_pop_up_list_with_word_wrap (get_trans ("UNRECOGNISED_WARZONE"), session_info_list, NULL, 0, UI_FONT_ARIAL_10, sys_col_white);
                            //add_to_pop_up_list (get_trans ("Server using unrecognised warzone"), session_info_list, NULL, 0, UI_FONT_ARIAL_10, sys_col_white);

                            break;
                        }

                        //
                        //
                        //

                        create_local_only_entities (PACK_MODE_BROWSE_SESSION);

                        if (unpack_session (ptr, received_size, PACK_MODE_BROWSE_SESSION))
                        {

                            debug_log ("COMMS MAN: browse: received size overflow"); // schorpp
 							start_game_exit (GAME_EXIT_KICKOUT, FALSE);
							break;
                       }

                        #if DEBUG_MODULE

                        if (this_connection->pilot_entity)
                        {

                            debug_log ("COMMS MAN: received SESSION INFO from %s (dpid %d) (setting server id)",
                                            get_local_entity_string (this_connection->pilot_entity, STRING_TYPE_PILOTS_NAME),
                                            received_id);
                        }
                        else
                        {

                            debug_log ("COMMS MAN: RECEIVED SESSION INFO from %d", received_id);
                        }

                        debug_log ("COMMS MAN: session info: time of day = %f",
                                        get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_TIME_OF_DAY));

                        debug_log ("COMMS MAN: map dimensions %d, %d, sector size %d", x_size, z_size, sector_size);

                        #endif

                        // Jabberwock 031118 Server side settings

                        set_ui_object_drawable (session_screen_continue_bdrop, TRUE);

                        set_ui_object_drawable (session_screen_continue_button, TRUE);

                        // Jabberwock 031118 ends

                        //
                        // Display game info
                        //

                        ui_object_destroy_list_items (session_info_list);

                        if (get_local_entity_int_value (get_session_entity (), INT_TYPE_CAMPAIGN_REQUIRES_APACHE_HAVOC))
                        {

                            // campaign requires apache havoc to be installed
                            // check it is...

									// VJ 050118 aphavoc install hack
                            if (!get_global_apache_havoc_installed () && !global_aphavoc_maps)
                            {

                                add_to_pop_up_list_with_word_wrap (get_trans ("REQUIRES_APACHE_HAVOC"), session_info_list, NULL, 0, UI_FONT_ARIAL_10, sys_col_white);

                                set_ui_object_drawable (session_screen_continue_button, FALSE);

                                break;
                            }
                        }

                        loop = 3;

                        sprintf (buffer, "%s : %d", get_trans ("Players"), player_count);

                        add_to_pop_up_list_with_word_wrap (buffer, session_info_list, NULL, 0, UI_FONT_ARIAL_10, sys_col_white);

                        force = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

                        while (force)
                        {

                            pilot = get_local_entity_first_child (force, LIST_TYPE_PILOT);

                            while (pilot)
                            {
                                {
                                    rgb_colour
                                        col;

                                    sprintf (buffer, "%2d  ", loop - 2);

                                    strncat (buffer, get_local_entity_string (pilot, STRING_TYPE_PILOTS_NAME), 64);

                                    switch (get_local_entity_int_value (pilot, INT_TYPE_SIDE))
                                    {
                                        case ENTITY_SIDE_BLUE_FORCE:
                                        {
                                            col.r = 120;
                                            col.g = 158;
                                            col.b = 255;
                                            col.a = 255;

                                            break;
                                        }
                                        case ENTITY_SIDE_RED_FORCE:
                                        {
                                            col.r = 255;
                                            col.g = 120;
                                            col.b = 80;
                                            col.a = 255;

                                            break;
                                        }
                                        default:
                                        {
                                          col = ui_colour_white;

                                            break;
                                        }
                                    }

                                    add_to_pop_up_list_with_word_wrap (buffer, session_info_list, NULL, 0, UI_FONT_ARIAL_10, col);

                                    loop ++;
                                }

                                pilot = get_local_entity_child_succ (pilot, LIST_TYPE_PILOT);
                            }

                            force = get_local_entity_child_succ (force, LIST_TYPE_FORCE);
                        }

                        set_server_id (received_id);

                        //
                        // destroy all entities created by browse info
                        //

                        reinitialise_entity_system ();

                        break;
                    }

                    case PACKET_TYPE_CLIENT_PILOT_REQUEST:
                    {

                        connection_list_type
                            *new_connection;

                        client_pilot_request_data
                            pilot_data;

                        entity
                            *new_pilot;

                        int
                            index;

                        ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

//                      #if DEBUG_MODULE

                        debug_log ("COMMS MAN: RECEIVED PILOT REQUEST from %d", received_id);

//                      #endif

                        //
                        // unpack name
                        //

                        memcpy (&pilot_data, (client_pilot_request_data *) received_data, sizeof (client_pilot_request_data));

                        new_pilot = create_new_pilot_entity
                                        (
                                            pilot_data.name,
                                            pilot_data.side,
                                            pilot_data.rank,
                                            pilot_data.sub_type,
                                            pilot_data.unique_id,
                                            pilot_data.difficulty
                                        );

                        ASSERT (new_pilot);

                        index = get_local_entity_safe_index (new_pilot);

                        new_connection = get_connection_list_item (received_id);

                        transmit_entity_comms_message (ENTITY_COMMS_PILOT_REQUEST_ACCEPTED, NULL, received_id, index);

                        new_connection->pilot_entity = new_pilot;

                        break;
                    }

                    case PACKET_TYPE_CLIENT_GUNSHIP_REQUEST:
                    {

                        connection_list_type
                            *new_connection;

                        client_gunship_request_data
                            pilot_data;

                        int
                            index_number,
                            buffer [2];

                        if (get_comms_model () == COMMS_MODEL_SERVER)
                        {

//                          #if DEBUG_MODULE

                            if (this_connection->pilot_entity)
                            {

                                debug_log ("COMMS MAN: RECEIVED GUNSHIP REQUEST from %s (dpid %d)",
                                                get_local_entity_string (this_connection->pilot_entity, STRING_TYPE_PILOTS_NAME),
                                                received_id);
                            }
                            else
                            {

                                debug_log ("COMMS MAN: RECEIVED GUNSHIP REQUEST from %d", received_id);
                            }

//                          #endif

                            memcpy (&pilot_data, (client_gunship_request_data *) received_data, sizeof (client_gunship_request_data));

                            index_number = pilot_data.gunship_index;

                            ASSERT (index_number != ENTITY_INDEX_DONT_CARE);

                            member = get_local_entity_safe_ptr (index_number);

                            if (!member)
                            {
//                              #if DEBUG_MODULE

                                if (this_connection->pilot_entity)
                                {

                                    debug_log ("COMMS MAN: REFUSING GUNSHIP FOR PLAYER %s (dpid %d) for helicopter %d",
                                                    get_local_entity_string (this_connection->pilot_entity, STRING_TYPE_PILOTS_NAME),
                                                    received_id, pilot_data.gunship_index);
                                }
                                else
                                {

                                    debug_log ("COMMS MAN: Refusing gunship for player %d to helicopter %d", received_id, pilot_data.gunship_index);
                                }

//                              #endif

                                send_packet (received_id, PACKET_TYPE_GUNSHIP_REQUEST_REFUSED, NULL, 0, SEND_TYPE_PERSONAL);

                                break;
                            }

                            new_connection = get_connection_list_item (received_id);

                            //
                            // send acceptance
                            //

                            buffer [0] = index_number;

//                          #if DEBUG_MODULE

                            debug_log ("COMMS MAN: sending gunship request accepted for gunship %d pilot id %d", index_number, received_id);

//                          #endif

                            send_packet (received_id, PACKET_TYPE_GUNSHIP_REQUEST_ACCEPTED, (void *) &buffer, 4, SEND_TYPE_PERSONAL);

                            new_connection->gunship_number = pilot_data.gunship_index;

                            new_connection->gunship_entity = member;
                        }

                        break;
                    }

                    case PACKET_TYPE_CLIENT_CAMPAIGN_DATA_REQUEST:
                    {

                        connection_list_type
                            *new_connection;

                        int
                            index_number;

                        if (get_comms_model () == COMMS_MODEL_SERVER)
                        {

                            #if DEBUG_MODULE

                            if (this_connection->pilot_entity)
                            {

                                debug_log ("COMMS MAN: RECEIVED JOIN REQUEST by %s (dpid %d)",
                                                get_local_entity_string (this_connection->pilot_entity, STRING_TYPE_PILOTS_NAME),
                                                received_id);
                            }
                            else
                            {

                                debug_log ("COMMS MAN: received JOIN REQUEST by %d", received_id);
                            }

                            #endif


                            if (this_connection->pilot_entity)
                            {
                            	server_log ("%s is trying to join...", get_local_entity_string (this_connection->pilot_entity, STRING_TYPE_PILOTS_NAME));
                           	}
                           	else
                           	{
                           		server_log ("Received join request...", received_id);
                           	}
                           // Jabberwock 031118 ends

                            //
                            // flush group send buffer
                            //

                            send_comms_data ();

                            //
                            // pack mission data into packet
                            //

                            new_connection = get_connection_list_item (received_id);

                            //
                            // Store entity data
                            //

                            while (pack_session (new_connection->connection_receive_buffer, &new_connection->connection_receive_buffer_size, PACK_MODE_CLIENT_SESSION))
                            {

                                new_connection->connection_receive_buffer_size *= 2;

                                #if DEBUG_MODULE

                                debug_log ("COMMS MAN: Mission data: connection_receive_buffer too small, mallocing to %d", new_connection->connection_receive_buffer_size);

                                #endif

                                free_mem (new_connection->connection_receive_buffer);

                                new_connection->connection_receive_buffer = malloc_heap_mem (new_connection->connection_receive_buffer_size);

                                memset (new_connection->connection_receive_buffer, 0, new_connection->connection_receive_buffer_size);
                            }

                            // add frame id
                            index_number = get_group_frame_id ();
                            memcpy (&new_connection->connection_receive_buffer [new_connection->connection_receive_buffer_size], (void *) &index_number, sizeof (int));
                            new_connection->connection_receive_buffer_size += sizeof (int);

                            send_packet (received_id, PACKET_TYPE_MISSION_DATA, new_connection->connection_receive_buffer, new_connection->connection_receive_buffer_size, SEND_TYPE_PERSONAL);

                            memset (new_connection->connection_receive_buffer, 0, new_connection->connection_receive_buffer_size);

                            //
                            // send group frame id
                            //

                            Sleep (100);

                            index_number = get_group_frame_id ();

                            //send_packet (received_id, PACKET_TYPE_FRAME_ID, (void *) &index_number, 4, SEND_TYPE_PERSONAL);

                            zero_average_pack_size ();
                        }

                        break;
                    }

                    case PACKET_TYPE_CLIENT_FRAME_ID:
                    {

                        int
                            loop1,
                            loop2,
                            index_number;

                        stub_packet_type
                            *stub_packet;

                        connection_list_type
                            *new_connection;

                        index_number = get_list_item (received_data, int);

                        new_connection = get_connection_list_item (received_id);

                        //#if DEBUG_MODULE

                        if (new_connection)
                        {

                            debug_log ("COMMS MAN: received CLIENT FRAME ID (%d) by %d %s", index_number, received_id, direct_play_get_player_name (received_id));
                        }

                        //#endif

                        //
                        // send all packets between when the client started to join and when it actually joined.
                        //

                        for (loop1 = index_number; loop1 < get_group_frame_id () - 1; loop1 ++)
                        {

                            //#if DEBUG_MODULE

                            debug_log ("COMMS MAN: sending packet %d frame %d to recently joined client", loop1, 0);

                            //#endif

                            stub_packet = resend_packet (received_id, loop1, 1, SEND_TYPE_GROUP);

                            ASSERT (stub_packet);

                            for (loop2 = 2; loop2 <= stub_packet->packet->number_of_packets; loop2 ++)
                            {

                                //#if DEBUG_MODULE

                                debug_log ("COMMS MAN: sending packet %d frame %d to recently joined client", loop1, loop2);

                                //#endif

                                stub_packet = resend_packet (received_id, loop1, loop2, SEND_TYPE_GROUP);
                            }
                        }

                        break;
                    }

                    case PACKET_TYPE_GUNSHIP_REQUEST_REFUSED:
                    {

//                      #if DEBUG_MODULE

                        debug_log ("COMMS MAN: Gunship refused");

//                      #endif

                        set_server_response (SERVER_RESPONSE_REFUSE);

                        break;
                    }

                    case PACKET_TYPE_GUNSHIP_REQUEST_ACCEPTED:
                    {

                        entity
                            *gunship;

                        int
                            index_number;

//                      #if DEBUG_MODULE

                        debug_log ("COMMS MAN: received GUNSHIP ACCEPTED by %d", received_id);

//                      #endif

                        //
                        // set gunship
                        //

                        index_number = get_list_item (received_data, int);

                        ASSERT (get_pilot_entity ());

                        gunship = get_local_entity_safe_ptr (index_number);

                        debug_filtered_log ("COMM_MAN: setting gunship");

                        planner_event = FALSE;

                        if (get_event_stack_head_function() == ingame_screen_set_events)
                        {

                            pop_event (ingame_screen_set_events);

                            planner_event = TRUE;
                        }

                        assign_entity_to_user (gunship);

                        if (planner_event)
                        {

                            push_event (ingame_screen_set_events, "ingame screen events");
                        }

                        debug_filtered_log ("COMM_MAN: gunship set");

                        ////////////////////////////////////////////////////////////////////////

                        break;
                    }

                    case PACKET_TYPE_PILOT_REQUEST_ACCEPTED:
                    {

                        int
                            index_number;

                        ASSERT (get_comms_model () == COMMS_MODEL_CLIENT);

//                      #if DEBUG_MODULE

                        debug_log ("COMMS MAN: received PILOT ACCEPTED by %d", received_id);

//                      #endif

                        index_number = get_list_item (received_data, int);

                        set_pilot_entity (get_local_entity_safe_ptr (index_number));

                        break;
                    }

                    case PACKET_TYPE_MISSION_DATA:
                    {

                        #if DEBUG_MODULE

                        debug_log ("COMMS MAN: received MISSION DATA by %d", received_id);

                        #endif

                        set_mouse_graphic_off ();

                        //
                        // LOAD TERRAIN DATA
                        //

                        load_3d_terrain_game_data ();

                        initialise_population_name_database ();

                        load_route_data (); // might need to send what route filename to load...

                        //
                        // Initialise stuff
                        //

                        create_local_only_entities (PACK_MODE_CLIENT_SESSION);

                        /////////////////////////////////////////////////////////////////
                        if (strstr (strupr (side_data_filename), "SID"))
                        {

                            read_sector_side_file (side_data_filename);
                        }
                        else if (strstr (strupr (side_data_filename), "DAT"))
                        {

                            load_ai_sector_data (side_data_filename);
                        }
                        /////////////////////////////////////////////////////////////////

                        deinitialise_formation_database ();

                        initialise_formation_database ();

                        deinitialise_formation_component_database ();

                        initialise_formation_component_database ();

                        if (unpack_session (received_data, received_size - 4, PACK_MODE_CLIENT_SESSION))
                        {

                            debug_log ("COMMS MAN: received size overflow");
							start_game_exit (GAME_EXIT_KICKOUT, FALSE);
							break;
                        }
/*
                        force = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

                        while (force)
                        {

                            create_frontline (force);

                            force = get_local_entity_child_succ (force, LIST_TYPE_FORCE);
                        }

*/
                        {
                            int
                                index_number;

                            connection_list_type
                                *new_connection;

                            received_data += received_size - 4;
                            index_number = get_list_item (received_data, int);

                            new_connection = get_connection_list_item (received_id);

                            new_connection->receive_group_frame_id = index_number;

                            send_packet (get_server_id (), PACKET_TYPE_CLIENT_FRAME_ID, (void *) &index_number, 4, SEND_TYPE_PERSONAL);
                        }

                        session_data = TRUE;

                        //direct_play_join_group (); // Jabberwock 050303 Remove DP groups

                        set_gunship_waiting_for_connection ( FALSE );

                        zero_average_pack_size ();

                        set_mouse_graphic_on ();

                        break;
                    }

                    case PACKET_TYPE_FRAME_ID:
                    {

                        int
                            index_number;

                        connection_list_type
                            *new_connection;

                        index_number = get_list_item (received_data, int);

                        #if DEBUG_MODULE

                        debug_log ("COMMS MAN: received FRAME ID (%d) by %d", index_number, received_id);

                        #endif

                        new_connection = get_connection_list_item (received_id);

                        new_connection->receive_group_frame_id = index_number;

                        send_packet (get_server_id (), PACKET_TYPE_CLIENT_FRAME_ID, (void *) &index_number, 4, SEND_TYPE_PERSONAL);

                        break;
                    }

                    ///////////////////////////////////////////////////////////////////////////////////////////////
                    //
                    // In game packets
                    //
                    ///////////////////////////////////////////////////////////////////////////////////////////////

                    case PACKET_TYPE_AI_DATA:
                    {

                        int
                            //padding,
                            data_size;

                        #if DEBUG_MODULE >= 2

                        debug_log ("COMMS MAN: received AI DATA by %d", received_id);

                        #endif

                        if (get_comms_model () == COMMS_MODEL_CLIENT)
                        {

                            ASSERT (session_data);
                        }

                        data_size = get_list_item (received_data, int);

                        //debug
                        //padding = get_list_item (received_data, int);
                        //end

                        open_unpack_buffer (received_data, received_size);

                        process_received_entity_comms_messages ();

                        ASSERT (!get_unpack_buffer_overflow ());

                        close_unpack_buffer ();

                        //debug
                        //padding = get_list_item (received_data, int);
                        //end

                        memset (received_data, 0, this_connection->connection_receive_buffer_size);

                        break;
                    }

                    case PACKET_TYPE_END_GAME:
                    {

                        debug_log ("COMMS MAN: received END GAME from %d", received_id);

                        if (get_comms_model () == COMMS_MODEL_SERVER)
                        {
                            if (this_connection->gunship_entity)
                            {

                                set_client_server_entity_int_value (this_connection->gunship_entity, INT_TYPE_PLAYER, ENTITY_PLAYER_AI);
                            }

                            if (this_connection->pilot_entity)
                            {

                                debug_log ("    from %s ", get_local_entity_string (this_connection->pilot_entity, STRING_TYPE_PILOTS_NAME));
                            }

                            unregister_connection (received_id);
                        }
                        else
                        {

                            if (received_id == get_server_id ())
                            {

                                //setup_campaign_over_screen (get_local_force_entity (get_global_gunship_side ()), CAMPAIGN_RESULT_STALEMATE);

                                start_game_exit (GAME_EXIT_KICKOUT, FALSE);
                            }
                        }

                        receive_flag = FALSE;

                        break;
                    }

                    case PACKET_TYPE_SERVER_REJECTED:
                    {

                        debug_log ("COMMS MAN: received SERVER REJECTED (server id %d)", received_id);

                        //setup_campaign_over_screen (get_local_force_entity (get_global_gunship_side ()), CAMPAIGN_RESULT_SERVER_REJECTED);

                        start_game_exit (GAME_EXIT_KICKOUT, FALSE);

                        break;
                    }

                    default:
                    {

                        debug_log ("ERROR: Data Exchange, unknown packet type %d", type); //schorpp "trying ignore, kickout would open door for dos-attacks"

                        break;
                    }
                }
            }

            send_type --;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_ui_comms (void)
{

static int
        update_ticks = 0;

    if (update_ticks < get_system_time ())
    {

        data_exchange ();

        update_ticks = get_system_time () + (ONE_SECOND / command_line_max_game_update_rate);

        set_delta_time ();
    }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//-- Werewolf

// Resolve masterserver hostname
unsigned long LookUpIPAddress(CHAR * inet_address)
{

    unsigned long ulServerAddr = INADDR_NONE;
    LPHOSTENT hostentry = NULL;

    // Try parsing inet xxx.xxx.xxx.xxx format string
    ulServerAddr = inet_addr(inet_address);
    if (ulServerAddr == INADDR_NONE)
    {
        // If the IP address parse fails, try
        // resolving host name using hosts file
        hostentry = gethostbyname(inet_address);

        // At this point, the user didn't enter an IP address
        // or valid host name.  Display error message and return
        // exit.  Return FALSE to indicate failure.
        if (hostentry == NULL)
        {
            return INADDR_NONE;
        }
        // The hostname was valid.  Store the IP address
        else
        {
            ulServerAddr = *((unsigned long *)hostentry->h_addr_list[0]);
        }
    }

    return ulServerAddr;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Used by pilot.c to remember the hosting player's name
void net_set_hostname (const char *data)
{
    sprintf(localplayer, "%s", data);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int net_CheckForDataOnSocket (int p1, int p2)
{
	fd_set rread;
	struct timeval to;
	int sr = -1;
	int p;

	if (p1 > 0)
	{
	  p = p1;
	  FD_ZERO (&rread);
	  FD_SET (p, &rread);
	  memset (&to, 0, sizeof (to));
	  to.tv_sec = 0;
	  to.tv_usec = 10;
	  sr = select (1, &rread, NULL, NULL, &to);
	  if (sr > 0)
	    if (FD_ISSET (p,&rread))
	      return 1;
        }
        if (p2 > 0)
        {
	  p = p2;
	  FD_ZERO (&rread);
	  FD_SET (p, &rread);
	  memset (&to, 0, sizeof (to));
	  to.tv_sec = 0;
	  to.tv_usec = 10;
	  sr = select (1, &rread, NULL, NULL, &to);
	  if (sr > 0)
	    if (FD_ISSET (p,&rread))
	      return 2;
         }

	return sr;
}

// Send a UDP packet to the masterserver
void net_sendDataToMaster (char *data, int servernum)
{
    if (command_line_report_to_masterserver == FALSE)
    	return;


    if (servernum == 1)
    {
          debug_log ("HEARTBEAT: sending heartbeat to primary server");
          sendto (mastersocket, data, strlen (data), 0, (SOCKADDR *)&Master, sizeof (SOCKADDR));
        }
        else
        {
          debug_log ("HEARTBEAT: sending heartbeat to secondary server");
          sendto (mastersocket2, data, strlen (data), 0, (SOCKADDR *)&Master2, sizeof (SOCKADDR));
        }
}

//This is a special function because the received data is stored in ReceiveBuffer!!
void net_receiveData (int s)
{
	int socket;
	int len = sizeof (SOCKADDR);
	if (s == 1)
	  socket = mastersocket;
	if (s == 2)
	  socket = mastersocket2;

	memset (ReceiveBuffer, '\0', PACKET_SIZE);
	recvfrom (socket, ReceiveBuffer, PACKET_SIZE, 0, &from, &len);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Opens a socket to the masterserver. Returns -1 if unsuccessfull
int net_connectToMaster (char *serverName, short port, int servernum)
{
        int sock;
        u_long ulServerAddr;

        if (servernum==1)
        {
            debug_log ("HEARTBEAT: Connecting to primary master");
        }
        else
        {
            debug_log ("HEARTBEAT: Connecting to secondary master");
        }

        ulServerAddr = LookUpIPAddress(serverName);

        sock = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (sock == INVALID_SOCKET)
        {

            if (servernum==1)
            {
                debug_log ("HEARTBEAT: ERROR connecting to primary master!");
            }
            else
            {
                debug_log ("HEARTBEAT: ERROR connecting to secondary master!");
            }
            return -1;
        }
        if (servernum==1)
        {
            Master.sin_family = AF_INET;
            Master.sin_addr.s_addr = ulServerAddr;
//            Master.sin_addr.s_addr = inet_addr(serverName);
            Master.sin_port = htons (port);
        }
        else
        {
            Master2.sin_family = AF_INET;
            Master2.sin_addr.s_addr = ulServerAddr;
//            Master2.sin_addr.s_addr = inet_addr(serverName);
            Master2.sin_port = htons (port);
        }

        #if DEBUG_MODULE
        debug_log ("HEARTBEAT: connect successfull");
        #endif

        return sock;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Build a heartbeat packet and send it.
void net_heartbeat(void)
{
    char TempStuff[512];
    char versionBuffer[256];


#if DEBUG_MODULE
debug_log ("HEARTBEAT: net_heartbeat called");
#endif

    direct_play_session_capabilities ();
    sprintf(versionBuffer, "%d.%d.%d%s", MAJOR_VERSION, DATA_VERSION, MINOR_VERSION, BUILD_TYPE);
    sprintf(TempStuff, "%s %s %s %i %i %s", "Z", "127.0.0.1", //The transmitted ip is disregarded anyway...
                                                 localplayer,
                                                 direct_play_session_max_players(),
                                                 direct_play_get_number_of_players(),
                                                 versionBuffer);

debug_log ("HEARTBEAT: sending: %s", TempStuff);

    if (mastersocket > 0 )
      net_sendDataToMaster (TempStuff, 1);
    if (mastersocket2 > 0 )
      net_sendDataToMaster (TempStuff, 2);
}

//--------------------------------------------------------------------------------
// Retrieve a list of available internet game servers
//--------------------------------------------------------------------------------
void net_getServerList(void)
{
    char header[80];
    int index = 0;
    int respondingServer = 0;

    if (command_line_report_to_masterserver == FALSE)
    	return;

    debug_log ("GETSERVERLIST: Init");

    if ((mastersocket <=0) && (mastersocket2 <=0))
    {
    	numServers = 0;
	return;
    }


    if (num_multiplayer_refreshes == 1)
    {
      //Request a list of servers
      sprintf(SendBuffer, "Y");
      if (mastersocket > 0 )
        net_sendDataToMaster (SendBuffer, 1);
      if (mastersocket2 > 0 )
        net_sendDataToMaster (SendBuffer, 2);

      debug_log ("GETSERVERLIST: Request sent");
    }
    else if (num_multiplayer_refreshes > 2)
    {
          num_multiplayer_refreshes = 0;
    }

//		do {
//		timeout++;
//		} while ((net_CheckForDataOnSocket (mastersocket, mastersocket2)!=1) && (timeout < 6000000));
//		if (timeout<6000000)
//		{
		respondingServer = net_CheckForDataOnSocket (mastersocket, mastersocket2);
		if (respondingServer > 0)
		{
			do
			{
				net_receiveData (respondingServer); //The received data is in ReceiveBuffer!!
				debug_log ("GETSERVERLIST: Received: %s", ReceiveBuffer);

				if (ReceiveBuffer[0] == 'W')
				{
				    sscanf(ReceiveBuffer, "%s %s %s %i %i %s", header, Servers[index].Adress,
										Servers[index].Name,
										&Servers[index].MaxClients,
										&Servers[index].CurClients,
										Servers[index].Version);
					index++;
				}
			} while (strcmp(ReceiveBuffer, "X Done!") != 0);
			numServers = index;
			sprintf(Servers[index].Version, "");
		}
//		net_uninit_heartbeat();
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Called during mission load, this function opens a socket to the masterserver
// TODO: Replace hardcoded address with .ini-aware parameter.
void net_init_heartbeat(void)
{
    if (command_line_report_to_masterserver == FALSE)
    	return;

        mastersocket = net_connectToMaster (command_line_primary_server_setting, MasterPort, 1);
        if (mastersocket <= 0)
          mastersocket2 = net_connectToMaster (command_line_secondary_server_setting, MasterPort, 2);
    debug_log ("HEARTBEAT: after heartbeat initialisation");

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Called at every rendered frame, this function will send a heartbeat every 60 seconds.
void net_handle_heartbeat(void)
{
    connection_data_type
        *this_connection;

    if (command_line_report_to_masterserver == FALSE)
    	return;

        // Time for another heartbeat?
    if (last_heartbeat_time < get_system_time ())
    {
      debug_log ("HEARTBEAT: Time for another heartbeat!");
      //Check whether we're a server AND whether the mission is running
      if ((get_comms_model () == COMMS_MODEL_SERVER) && (get_game_status () == GAME_STATUS_INITIALISED))
      {
        this_connection = direct_play_get_connection_data ();
        // Check if network is enabled
        if ( ( this_connection ) && ( this_connection->service_provider.guid ) )
        {
          connection_data_type *this_connection;
          this_connection = direct_play_get_connection_data ();
          // Check whether the current networking method is TCP/IP
          if ( memncmp ( ( char * ) this_connection->service_provider.guid, ( char * ) &DPSPGUID_TCPIP, sizeof ( GUID ) ) == TRUE )
          {
            //Send heartbeat
            net_heartbeat();
          }
        }
      }
      //Set next scheduled heartbeat time. Strangely, ONE_SECOND does not equal one second, hence the multiplication factor "1000"
          last_heartbeat_time = get_system_time () + (ONE_SECOND * 60 * 1000);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Close masterserver socket.
void net_uninit_heartbeat(void)
{
    if (command_line_report_to_masterserver == FALSE)
    	return;

    if (mastersocket >= 0)
          closesocket (mastersocket);
        mastersocket = -1;
    if (mastersocket2 >= 0)
          closesocket (mastersocket2);
        mastersocket2 = -1;
}
//-- Werewolf

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

