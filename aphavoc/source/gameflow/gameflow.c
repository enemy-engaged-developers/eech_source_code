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

static game_flow_types
	current_game_flow;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

game_initialisation_phases
	game_initialisation_phase;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_game_flow (game_flow_types flow)
{

	current_game_flow = flow;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

game_flow_types get_game_flow (void)
{

	return current_game_flow;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_game_initialisation_phases (void)
{

	set_game_type (GAME_TYPE_INVALID);

	set_global_gunship_type (NUM_GUNSHIP_TYPES);

	set_global_gunship_side (ENTITY_SIDE_NEUTRAL);

	if (command_line_game_initialisation_phase_game_type != GAME_TYPE_INVALID)
	{

		set_game_type (command_line_game_initialisation_phase_game_type);
	}

	if (command_line_game_initialisation_phase_gunship_type != NUM_GUNSHIP_TYPES)
	{

		set_global_gunship_type (command_line_game_initialisation_phase_gunship_type);
	}

	game_initialisation_phase = GAME_INITIALISATION_PHASE_NONE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void process_game_initialisation_phases (void)
{

	session_list_data_type
		*session;

   connection_data_type
      *this_connection;

   session_table_type
      *this_session;

	int
		flag,
		value;

	char
		operator [64],
		variable [64];

	switch (game_initialisation_phase)
	{

		case GAME_INITIALISATION_PHASE_NONE:
		{

			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//
			// NONE
			//
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			if (command_line_comms_dedicated_server)
			{

				set_comms_model (COMMS_MODEL_SERVER);

				//
				// set dedicated server defaults if none specifier on command_line.
				//

				if (command_line_game_initialisation_phase_game_type == GAME_TYPE_INVALID)
				{

					set_game_type (GAME_TYPE_CAMPAIGN);
				}

				if (command_line_game_initialisation_phase_gunship_type == NUM_GUNSHIP_TYPES)
				{

					set_global_gunship_type (GUNSHIP_TYPE_APACHE);
				}

				switch (get_global_gunship_type ())
				{

					case GUNSHIP_TYPE_APACHE:
					case GUNSHIP_TYPE_COMANCHE:
					{

						set_global_gunship_side (ENTITY_SIDE_BLUE_FORCE);

						break;
					}

					case GUNSHIP_TYPE_HAVOC:
					case GUNSHIP_TYPE_HOKUM:
					{

						set_global_gunship_side (ENTITY_SIDE_RED_FORCE);

						break;
					}
				}
					
				load_side_dependant_application_sound_samples (NUM_ENTITY_SIDES);

				if (get_game_type () != GAME_TYPE_INVALID)
				{
	
					if ((get_global_gunship_side () != ENTITY_SIDE_NEUTRAL) || (get_game_type () == GAME_TYPE_DEMO))
					{
	
						if (!get_current_game_session ())
						{
	
							session = (session_list_data_type *) malloc_heap_mem (sizeof (session_list_data_type));
							memset (session, 0, sizeof (session_list_data_type));

							session->title = (char *) malloc_heap_mem (sizeof (char) * (strlen ("Dedicated Server") + 2));
	
							sprintf (session->title, "Dedicated Server");
	
							session->type = SESSION_LIST_TYPE_HOST;
	
							session->list_id = 1;
	
							session->type_id = 1;
	
							session->join_session = NULL;
	
							session->warzone_name = "Cuba";
	
							if ((strcmp (command_line_game_initialisation_phase_path, "/0") == 0) ||
								(strcmp (command_line_game_initialisation_phase_path, "") == 0))
							{
	
								sprintf (session->data_path, "..\\common\\maps\\map6");
							}
							else
							{
	
								sprintf (session->data_path, command_line_game_initialisation_phase_path);
							}
	
							if ((strcmp (command_line_game_initialisation_phase_directory, "/0") == 0) ||
								(strcmp (command_line_game_initialisation_phase_directory, "") == 0))
							{
	
								sprintf (session->campaign_directory, "camp01");
							}
							else
							{
	
								sprintf (session->campaign_directory, command_line_game_initialisation_phase_directory);
							}

							if ((strcmp (command_line_game_initialisation_phase_filename, "/0") == 0) ||
								(strcmp (command_line_game_initialisation_phase_filename, "") == 0))
							{
	
								sprintf (session->campaign_filename, "yemen.chc");
							}
							else
							{
	
								sprintf (session->campaign_filename, command_line_game_initialisation_phase_filename);
							}
	
							session->child = NULL;
	
							session->next = NULL;
	
							set_current_game_session (session);

							if (get_game_type () == GAME_TYPE_DEMO)
							{

								push_ui_screen (loading_screen);
							}
						}
					}
				}
			}
		}
		case GAME_INITIALISATION_PHASE_GAME_TYPE:
		{

			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//
			// GAME_TYPE
			//
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			if (get_game_type () != GAME_TYPE_INVALID)
			{

				game_initialisation_phase = GAME_INITIALISATION_PHASE_SCENARIO;

				#if DEBUG_MODULE

				debug_log ("DEDICATE: set game_type to %d", command_line_game_initialisation_phase_game_type);

				#endif
			}
			else
			{

				#if DEBUG_MODULE

				debug_log ("DEDICATE: waiting for game_type");

				#endif

				break;
			}

			if (get_pack_buffer ())
			{

				close_pack_buffer ();
			}

			////////////////////////////////////////
			set_game_status (GAME_STATUS_UNINITIALISED);
			////////////////////////////////////////

			open_pack_buffer (tx_pack_buffer, command_line_comms_pack_buffer_size);

			reset_comms_data ();

			comms_clear_data_record ();
		}
		case GAME_INITIALISATION_PHASE_SCENARIO:
		{

			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//
			// SCENARIO
			//
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			if (get_comms_model () == COMMS_MODEL_CLIENT)
			{

				reinitialise_entity_system ();
			}

			session = get_current_game_session ();

			if (session)
			{

				if (get_comms_model () == COMMS_MODEL_SERVER)
				{

					int
						line_count;

					FILE
						*file_ptr;

					char
						line [1024],
						filename [1024];

					file_tags
						tag;

					if (get_game_type () == GAME_TYPE_FREE_FLIGHT)
					{

						//
						// Don't display briefing for free flight stuff
						//
					}
					else
					{

						int
							version_number;

						version_number = 0;

						line_count = 0;

						sprintf (filename, "%s\\%s\\%s", session->data_path, session->campaign_directory, session->campaign_filename);

						file_ptr = safe_fopen (filename, "r");

						flag = TRUE;

						while (flag)
						{

							tag = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

							switch (tag)
							{

								case FILE_TAG_TITLE:
								{

									get_next_file_string (file_ptr, line, sizeof (line));

									if (command_line_comms_dedicated_server)
									{

										if (session->title)
										{

											free_mem (session->title);
										}
			
										session->title = (char *) malloc_heap_mem (sizeof (char) * (strlen (line) + 2));

										sprintf (session->title, "%s", line);
									}

									break;
								}

								case FILE_TAG_SHORT_TEXT_START:
								{

									while (TRUE)
									{

										get_next_file_string (file_ptr, line, sizeof (line));

										if (strncmp ((line + 1), application_tag_strings [FILE_TAG_TEXT_END], 8) == 0)
										{
											break;
										}

										add_to_pop_up_list_with_word_wrap (get_trans (line), session_info_list, NULL, 0, UI_FONT_ARIAL_10, sys_col_white);

										line_count ++;
									}

									set_ui_object_vslider_virtual_position (get_ui_object_vslider (session_briefing_area), 0.0);
									
									break;
								}

								case FILE_TAG_IF:
								{

									ASSERT (get_current_player_log ());

									get_next_file_word (file_ptr, variable, sizeof (variable));

									get_next_file_word (file_ptr, operator, sizeof (operator));

									value = get_next_file_int (file_ptr);

									if (!if_file_tag_variable (variable, operator, value))
									{

										// skip script till endif

										while (tag = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG))
										{

											if (tag == FILE_TAG_ENDIF)
											{

												break;
											}
										}
									}

									break;
								}

								case FILE_TAG_ENDIF:
								{

									break;
								}

								case FILE_TAG_VERSION_NUMBER:
								{

									version_number = get_next_file_int (file_ptr);

									break;
								}

								case FILE_TAG_CAMPAIGN_DATA:
								{

									while (tag = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG))
									{

										if (tag == FILE_TAG_END)
										{

											break;
										}
									}

									break;
								}

								case FILE_TAG_END:
								{

									fclose (file_ptr);

									//
									// Check version numbers here if its a saved game.
									//

									if (session->type == SESSION_LIST_TYPE_RESTORE)
									{

										if ( version_number != get_global_version_number () )
										{

											//
											// Invalid version file
											//

											#if DEBUG_MODULE

											debug_log ( "GOT AN INVALID SAVED GAME" );

											#endif

											ui_object_destroy_list_items (session_info_list);

											add_to_pop_up_list_with_word_wrap (get_trans ("INVALID_SAVED_GAME"), session_info_list, NULL, 0, UI_FONT_ARIAL_10, sys_col_white);
											//add_to_pop_up_list (get_trans ("INVALID_SAVED_GAME"), session_info_list, NULL, 0, UI_FONT_ARIAL_10, sys_col_white);

											set_current_game_session_invalid();

											set_ui_object_drawable (session_briefing_overlay, TRUE);

											return;
										}
									}

									flag = FALSE;

									break;
								}

								case FILE_TAG_LANGUAGE_TEXT_START:
								{

									// skip script till correct language

									while (tag = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG))
									{

										#if (LANGUAGE == LANGUAGE_FRENCH)

										if (tag == FILE_TAG_LANGUAGE_FRENCH)
										{

											break;
										}
										#elif (LANGUAGE == LANGUAGE_GERMAN)

										if (tag == FILE_TAG_LANGUAGE_GERMAN)
										{

											break;
										}
										#elif (LANGUAGE == LANGUAGE_ITALIAN)

										if (tag == FILE_TAG_LANGUAGE_ITALIAN)
										{

											break;
										}
										#elif (LANGUAGE == LANGUAGE_SPANISH)

										if (tag == FILE_TAG_LANGUAGE_SPANISH)
										{

											break;
										}
										#else //LANGUAGE_ENGLISH

										if (tag == FILE_TAG_LANGUAGE_ENGLISH)
										{

											break;
										}
										#endif

										if (tag == FILE_TAG_LANGUAGE_TEXT_STOP)
										{

											break;
										}
									}

									break;
								}

								case FILE_TAG_LANGUAGE_TEXT_END:
								{

									// skip script till end of languages

									while (tag = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG))
									{

										if (tag == FILE_TAG_LANGUAGE_TEXT_STOP)
										{

											break;
										}
									}

									break;
								}
							}
						}
					}

					game_initialisation_phase = GAME_INITIALISATION_PHASE_SETUP;
				}
				else
				{

					//
					// join game
					//

					this_session = direct_play_get_session_table ();

					this_connection = direct_play_get_connection_data ();

					this_connection->this_session.session = session->join_session->session;

					if ( ( this_connection->is_initialised ) && ( !this_connection->one_way_hosting_setup ) )
					{

						direct_play_join_session ();

						direct_play_session_capabilities ();

						if (!direct_play_enumerate_groups ())
						{

							debug_fatal ("SESSION: Client can't enumerate any groups, restart machine");
						}

						this_connection->this_group = direct_play_get_group_table ();

						direct_play_create_player ();

						direct_play_join_group ();
					}

					Sleep (command_line_comms_initial_sleep_time);

					send_packet (DPID_ALLPLAYERS, PACKET_TYPE_SESSION_QUERY, NULL, 0, SEND_TYPE_GROUP);

					break;
				}

				#if DEBUG_MODULE

				debug_log ("DEDICATE: set current_session to %s %s", session->data_path, session->filename);

				#endif
			}
			else
			{

				#if DEBUG_MODULE

				debug_log ("DEDICATE: waiting for current_session");

				#endif

				break;
			}
		}
		case GAME_INITIALISATION_PHASE_SETUP:
		{

			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//
			// SETUP
			//
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//////////////////////////////////////////////////////////////////////
			set_gunship_screen_progress_message (GUNSHIPS_SCREEN_CONNECTING_TEXT);
			//////////////////////////////////////////////////////////////////////

			////////////////////////////////////////
			set_game_status (GAME_STATUS_INITIALISING);
			////////////////////////////////////////

			initialise_group_callsign_database ();

			initialise_message_log ();

			initialise_sound_channels ();

			initialise_valid_warzone_bridge_database ();

			session = get_current_game_session ();

			ASSERT (session);

			reset_delta_time ();

			if (get_comms_model () == COMMS_MODEL_SERVER)
			{

				char
					text [128],
					*name;

				name = get_player_log_name (get_current_player_log ());

				ASSERT (name);

				sprintf (text, "%s's %s", name, session->title);

				direct_play_set_session_name (text);

				sprintf (text, "%s's group", name);

				direct_play_set_group_name (text);

				ui_set_user_function (NULL);

				set_valid_combat_zone (TRUE);

				load_3d_terrain_game_data ();

				initialise_population_name_database ();

				reinitialise_entity_system ();
			}
			else
			{

				//
				// broadcast to all players JOIN_REQUEST
				//

				reinitialise_entity_system ();

				send_packet (get_server_id (), PACKET_TYPE_CLIENT_CAMPAIGN_DATA_REQUEST, NULL, 0, SEND_TYPE_PERSONAL);
			}

			switch (session->type)
			{

				case SESSION_LIST_TYPE_RESTORE:
				case SESSION_LIST_TYPE_HOST:
				{

					set_gunship_waiting_for_connection (FALSE);

					break;
				}
				case SESSION_LIST_TYPE_JOIN:
				{

					set_gunship_waiting_for_connection (TRUE);

					break;
				}
				case SESSION_LIST_TYPE_INVALID:
				default:
				{

					debug_fatal ("DEDICATE: unknown game type");
				}
			}

			#if DEBUG_MODULE

			debug_log ("DEDICATE: setup ...");

			#endif

			game_initialisation_phase = GAME_INITIALISATION_PHASE_GUNSHIP_TYPE;
		}
		case GAME_INITIALISATION_PHASE_GUNSHIP_TYPE:
		{

			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//
			// GUNSHIP_TYPE
			//
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			if (get_global_gunship_side () != ENTITY_SIDE_NEUTRAL)
			{

				switch (current_game_session->type)
				{

					case SESSION_LIST_TYPE_RESTORE:
					{

						set_mouse_graphic_off ();

						/////////////////////////////////////////////////////////////////
						set_gunship_screen_progress_message (GUNSHIPS_SCREEN_GENERATING_CAMPAIGN_TEXT);
						set_gunship_waiting_for_connection (TRUE);
						/////////////////////////////////////////////////////////////////

						create_campaign (get_current_game_session ());

						create_server_pilot ();

						process_restore_session_setup_options ();

						break;
					}
					case SESSION_LIST_TYPE_HOST:
					{

						set_mouse_graphic_off ();

						/////////////////////////////////////////////////////////////////
						set_gunship_screen_progress_message (GUNSHIPS_SCREEN_GENERATING_CAMPAIGN_TEXT);
						set_gunship_waiting_for_connection (TRUE);
						/////////////////////////////////////////////////////////////////

						create_campaign (get_current_game_session ());

						setup_campaign ();

						create_server_pilot ();

						process_host_session_setup_options ();

						break;
					}
					case SESSION_LIST_TYPE_JOIN:
					{

						create_client_pilot ();

						break;
					}
				}

				initialise_regen_queues ();

				#if !DEMO_VERSION
				
				initialise_main_campaign_screen ();

				#endif

				initialise_main_free_flight_screen ();

				game_initialisation_phase = GAME_INITIALISATION_PHASE_TRANSFERRING;

				#if DEBUG_MODULE

				debug_log ("DEDICATE: set side to %s", entity_side_names [get_global_gunship_side ()]);

				#endif
			}
			else
			{

				#if DEBUG_MODULE

				debug_log ("DEDICATE: waiting for side");

				#endif

				break;
			}
		}
		case GAME_INITIALISATION_PHASE_TRANSFERRING:
		{

			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//
			// TRANSFERRING
			//
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			if (get_comms_model () == COMMS_MODEL_CLIENT)
			{
				if (!get_pilot_entity ())
				{
					break;
				}
			}

			#if DEBUG_MODULE

			debug_log ("DEDICATE: Transferring");

			#endif

			ui_set_user_function (NULL);

			ui_repaint ();

			////////////////////////////////////////
			// entering game

			flight ();

			// exiting game
			////////////////////////////////////////

			set_mouse_on ();

			////////////////////////////////////////
			set_game_status (GAME_STATUS_UNINITIALISED);
			////////////////////////////////////////

			if (get_game_type () == GAME_TYPE_DEMO)
			{

				set_game_initialisation_phase (GAME_INITIALISATION_PHASE_NONE);

				pop_ui_screen (SCREEN_POP_ACTUAL);
			}

			deinitialise_message_log ();

			deinitialise_population_name_database ();

			minimize_all_map_objects ();

			initialise_game_initialisation_phases ();

			break;
		}
		case NUM_GAME_INITIALISATION_PHASES:
		{

			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//
			// END
			//
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

