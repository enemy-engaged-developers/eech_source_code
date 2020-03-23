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

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ai/parser/parsgen.h"
#include "ai/faction/faction.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

session_list_types
	session_filter [NUM_GAME_TYPES];

session_list_data_type
	*session_child_head,
	*current_game_session,
	*session_list_head;

static int
	list_id = 0;

entity
	*players_group;

char // Jabberwock 031210 Session filter
	session_filter_value [256] = "root";

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

session_info_type
	session_info [MAX_NUMBER_OF_PLAYERS];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static session_list_data_type *add_session (const char *title, session_list_types type, int type_id, session_table_type *join_session, char *path, char *directory, char *filename, char *warzone_name, session_list_data_type **list, const char *address, int season);

static void recursive_check_campaign_files (const char *directory, session_list_data_type **list, const char *extension);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_session_list (void)
{

	session_filter [GAME_TYPE_INVALID] = SESSION_LIST_TYPE_INVALID;
	session_filter [GAME_TYPE_FREE_FLIGHT] = SESSION_LIST_TYPE_HOST;
	// Jabberwock 031210 Session filter
	session_filter [GAME_TYPE_CAMPAIGN] = (session_list_types) (SESSION_LIST_TYPE_HOST | SESSION_LIST_TYPE_JOIN | SESSION_LIST_TYPE_RESTORE | SESSION_LIST_TYPE_MASTER | SESSION_LIST_TYPE_FILTER);
	session_filter [GAME_TYPE_SKIRMISH] = (session_list_types) (SESSION_LIST_TYPE_HOST | SESSION_LIST_TYPE_JOIN | SESSION_LIST_TYPE_RESTORE | SESSION_LIST_TYPE_MASTER | SESSION_LIST_TYPE_FILTER);
	// Jabberwock 031210 ends
	session_filter [GAME_TYPE_DEMO] = SESSION_LIST_TYPE_HOST;

	sprintf (session_filter_value, "%s", "root"); // Jabberwock 040201 Session filter

	destroy_session_list (&session_list_head);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_session_list (void)
{

	leave_mission ();

	destroy_session_list (&session_list_head);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void destroy_session_list (session_list_data_type **list)
{

	session_list_data_type
		*child,
		*destroy_child,
		*destroy_session;

	while (*list)
	{

		destroy_session = *list;

		*list = (*list)->next;

		if (destroy_session->title)
		{

			free_mem (destroy_session->title);
		}

		if (destroy_session->displayed_title)
		{

			free_mem (destroy_session->displayed_title);
		}

		if (destroy_session->warzone_name)
		{

			free_mem (destroy_session->warzone_name);
		}

		//
		// destroy child sessions
		//

		child = destroy_session->child;

		while (child)
		{

			destroy_child = child;

			child = child->child;

			if (destroy_child->title)
			{

				free_mem (destroy_child->title);
			}

			if (destroy_child->warzone_name)
			{

				free_mem (destroy_child->warzone_name);
			}

			free_mem (destroy_child);
		}

		//
		//
		//

		if (destroy_session == current_game_session)
		{

			set_current_game_session_invalid ();
		}

		free_mem (destroy_session);
	}

	*list = NULL;

	list_id = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

session_list_data_type *add_session (const char *title, session_list_types type, int type_id, session_table_type *join_session, char *path, char *directory, char *filename, char *warzone_name, session_list_data_type **list, const char *address, int season)
{

	char
		*ptr,
		*filename_ptr;

	int
		unique_session;

	session_list_data_type
		*child,
		*session_item,
		*insert_position,
		*new_session;

	new_session = (session_list_data_type *) malloc_heap_mem (sizeof (session_list_data_type));

	memset (new_session, 0, sizeof (session_list_data_type));

	new_session->title = (char *) malloc_heap_mem (strlen (title) + 1);
	if (address)
		sprintf (new_session->ip_address, "%s", address);

	// 15JUN09 Casm retrieving season earlier
	new_session->season = season;

	// test
	if (type == SESSION_LIST_TYPE_RESTORE)
	{

		// strip off "campaign\" part of filename
		filename_ptr = strstr (filename, "\\");

		if (filename_ptr)
		{

			// advance ptr past '\'

			filename_ptr ++;

			//new_session->displayed_title = (char *) malloc_heap_mem (strlen (title) + strlen (filename_ptr) + 4);
			//sprintf (new_session->displayed_title, "%s (%s)", title, filename_ptr);

			new_session->displayed_title = (char *) malloc_heap_mem (strlen (filename_ptr) + 1);

			sprintf (new_session->displayed_title, "%s", filename_ptr);

			ptr = strrchr (new_session->displayed_title, '.');

			if (ptr)
			{

				*ptr = '\0';
			}
		}
		else
		{

			//new_session->displayed_title = (char *) malloc_heap_mem (strlen (title) + strlen (filename) + 4);
			//sprintf (new_session->displayed_title, "%s (%s)", title, filename);

			new_session->displayed_title = (char *) malloc_heap_mem (strlen (filename) + 1);

			sprintf (new_session->displayed_title, "%s", filename);

			ptr = strrchr (new_session->displayed_title, '.');

			if (ptr)
			{

				*ptr = '\0';
			}
		}
	}
	else
	{

		new_session->displayed_title = (char *) malloc_heap_mem (strlen (title) + 1);

		sprintf (new_session->displayed_title, "%s", title);
	}
	// test

	// work out where new item belongs in list (Alphabetically)

	session_item = *list;

	insert_position = NULL;

	unique_session = TRUE;

	while (session_item)
	{

		//
		// non-unique sessions
		//

		if ((strcmp (new_session->displayed_title, session_item->displayed_title) == 0) && (type == session_item->type))
		{

			unique_session = FALSE;

			insert_position = session_item;

			break;
		}

		//
		// unique sessions
		//

// Jabberwock 040201 Session filter
		if (session_item->type == SESSION_LIST_TYPE_FILTER)
		{
			if (type == SESSION_LIST_TYPE_FILTER)
			{
				if ((strcmp (new_session->displayed_title, session_item->displayed_title) < 0))
				{
					break;
				}
			}
		}
		else
		{
			if (type == SESSION_LIST_TYPE_FILTER)
			{
				break;
			}
			else
			{
				if ((strcmp (new_session->displayed_title, session_item->displayed_title) < 0))
				{
					break;
				}
			}
		}

// Jabberwock ends
		insert_position = session_item;

		session_item = session_item->next;
	}

	//
	// create new list item
	//

	list_id ++;

	sprintf (new_session->data_path, "%s", path);

	if (filename)
	{

			sprintf (new_session->campaign_directory, "%s", directory);

		sprintf (new_session->campaign_filename, "%s", filename);
	}

	if (warzone_name)
	{

	new_session->warzone_name = (char *) malloc_heap_mem (strlen (warzone_name) + 1);

	sprintf (new_session->warzone_name, "%s", warzone_name);
	}
	else
	{

		char
			*ptr,
			*last_ptr,
			path [512];

		strcpy (path, new_session->data_path);

		ptr = strstr (path, "\\maps\\");

		ptr += strlen ("\\maps\\");

		last_ptr = ptr;

		if (strstr (ptr, "\\"))
		{

			while (strstr (ptr, "\\"))
			{

				ptr = strstr (ptr, "\\");

				ptr += strlen ("\\");
			}

			ptr -= strlen ("\\");

			*ptr = '\0';
		}

		new_session->warzone_name = (char *) malloc_heap_mem (strlen (last_ptr) + 1);

		sprintf (new_session->warzone_name, "%s", last_ptr);
	}

	sprintf (new_session->title, "%s", title);

	new_session->type_id = type_id;

	new_session->list_id = list_id;

	new_session->type = type;

	new_session->join_session = join_session;

	//
	// add to session list
	//

	// Casm 18AUG05 Allow to show different saved games with the same name
	if (unique_session || type == SESSION_LIST_TYPE_RESTORE)
	{

		if (insert_position)
		{

			new_session->next = insert_position->next;

			insert_position->next = new_session;
		}
		else
		{

			// first session

			new_session->next = *list;

			*list = new_session;
		}
	}
	else
	{

		child = insert_position->child;

		insert_position->child = new_session;

		new_session->child = child;
	}

	return new_session;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void compile_single_session_list (session_list_data_type **list)
{

	connection_data_type
		*this_connection;

	this_connection = direct_play_get_connection_data ();

	if ( ( this_connection ) && ( this_connection->is_initialised ) )
	{

		if ( ( this_connection->one_way_hosting_setup ) && ( !this_connection->is_hosting ) )
		{

			return;
		}
	}

// Jabberwock 040201 Session filter
	if (!command_line_session_filter || (strcmp (session_filter_value, "root") == 0))
	{
		recursive_check_campaign_files ("..\\common\\maps", list, game_type_extensions [get_game_type ()]);
	}
	else
	{
		if ((strcmp (session_filter_value, "-Multiplayer-") != 0))
		{
			recursive_check_campaign_files (session_filter_value, list, game_type_extensions [get_game_type ()]);
		}
	}
}
// Jabberwock 040201 ends

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void compile_multi_session_list (session_list_data_type **list)
{
	#if !DEMO_VERSION

	int
		session_number = 0;

	session_table_type
		*this_session;

	connection_data_type
		*this_connection;

	char
		text [128];

	if (masterserver_rx_flag)
		set_ui_object_drawable (session_screen_connection_indicator, TRUE);

	this_connection = direct_play_get_connection_data ();

	if ( ( this_connection ) && ( this_connection->is_initialised ) )
	{

		int number_of_sessions;
		int currentServer;

		// Jabberwock 040201 Session filter
		if (command_line_session_filter)
		{
			if ((strcmp(session_filter_value, "root") == 0) || (strcmp(session_filter_value, "-Multiplayer-") == 0))
			{
				add_session ("-Multiplayer-", SESSION_LIST_TYPE_FILTER, 1, NULL, "-Multiplayer-", NULL, NULL, "-Multiplayer-", list, NULL, SESSION_SEASON_INVALID);
			}
		}

		if ( !this_connection->one_way_hosting_setup )
		{

			number_of_sessions =  direct_play_enumerate_sessions ();
		}
		else
		{

			validate_modem_connection ();

			if ( this_connection->is_initialised )
			{

				number_of_sessions = direct_play_refresh_modem_session ();
			}
		}

		if ( number_of_sessions )
		{

			this_session = direct_play_get_session_table ();

			while (this_session)
			{

				//if (this_session->session->dwUser1 == get_game_type ()) // Jabberwock 031118 MP - campaigns shows in skirmishes and vice versa
				{

					if ((!command_line_session_filter) || (strcmp ("-Multiplayer-", session_filter_value) == 0)) // Jabberwock 031210 Session filter
					{
						sprintf (text, "%s", this_session->session->lpszSessionNameA);

						session_number ++;

						add_session (text, SESSION_LIST_TYPE_JOIN, session_number, this_session, NULL, NULL, NULL, "-Multiplayer-", list, NULL, SESSION_SEASON_INVALID); // Jabberwock 031210 Session filter
					}
				}

				this_session = this_session->next_session;
			}
		}

		//Werewolf 14 May 2003
		//Fetch active servers from masterserver
		net_getServerList();
		for (currentServer=0; currentServer<numServers; currentServer++)
		{
			if ((!command_line_session_filter) || (strcmp ("-Multiplayer-", session_filter_value) == 0)) // Jabberwock 031210 Session filter
			{
				sprintf (text, "%s (%i/%i) %s", Servers[currentServer].Name, Servers[currentServer].CurClients, Servers[currentServer].MaxClients, Servers[currentServer].Version);

				session_number ++;

				add_session (text, SESSION_LIST_TYPE_MASTER, session_number, NULL, NULL, NULL, NULL, "-Multiplayer-", list, Servers[currentServer].Adress, SESSION_SEASON_INVALID); // Jabberwock 031210 Session filter
			}
		}
	}

	#endif
}

/*
void get_first_multi_session (session_list_data_type **list)
{
	#if !DEMO_VERSION

	int session_number = 0;

	session_table_type
		*this_session;

	connection_data_type
		*this_connection;

	session_list_data_type
		*this_session_list;

	char
		text [128];

	this_connection = direct_play_get_connection_data ();

	if ( ( this_connection ) && ( this_connection->is_initialised ) )
	{

		int
			number_of_sessions;

		if ( !this_connection->one_way_hosting_setup )
		{

			number_of_sessions =  direct_play_enumerate_sessions ();
		}
		else
		{

			validate_modem_connection ();

			if ( this_connection->is_initialised )
			{

				number_of_sessions = direct_play_refresh_modem_session ();
			}
		}

		debug_log ("GETFIRSTSESSION: Number of sessions: %i", number_of_sessions);

		if ( number_of_sessions )
		{

			this_session = direct_play_get_session_table ();

			if (!this_session)
				debug_log ("GETFIRSTSESSION: direct_play_get_session_table() returned ZERO :(");


			if (this_session)
			{

				sprintf (text, "%s", this_session->session->lpszSessionNameA);

				debug_log ("GETFIRSTSESSION: First session is: %s", text);

				session_number ++;

//				list = add_session (text, SESSION_LIST_TYPE_JOIN, session_number, this_session, NULL, NULL, NULL, "-Multiplayer-", &this_session_list, NULL, SESSION_SEASON_INVALID); // Jabberwock 031210 Session filter

				return;

//				this_session = this_session->next_session;
			}
		}
	}
	#endif
	return;
}*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void compile_restore_session_list (session_list_data_type **list)
{

	char
		extension [5];

	connection_data_type
		*this_connection;

	this_connection = direct_play_get_connection_data ();

	if ( ( this_connection ) && ( this_connection->is_initialised ) )
	{

		if ( ( this_connection->one_way_hosting_setup ) && ( !this_connection->is_hosting ) )
		{

			return;
		}
	}

	sprintf (extension, "%s", game_type_extensions [get_game_type ()]);

	extension [2] = extension [1];
	extension [1] = extension [0];
	extension [0] = 'S';

// Jabberwock 040201 Session filter
	if (!command_line_session_filter || (strcmp (session_filter_value, "root") == 0))
	{
		recursive_check_campaign_files ("..\\common\\maps", list, extension);
	}
	else
	{
		if ((strcmp (session_filter_value, "-Multiplayer-") != 0))
		{
			recursive_check_campaign_files (session_filter_value, list, extension);
		}
	}
}
// Jabberwock 040201 ends

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

session_list_data_type *get_session_list (void)
{

	return session_list_head;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int store_session (session_list_data_type *game_session, const char *filename)
{
	#if !DEMO_VERSION

	entity
		*force;

	int
		count;

	char
		limited_filename [32],
		title [128],
		extension [5],
		data_filename [256],
		script_filename [256],
		current_savefile [256],
		new_savefile [256],
		current_scriptfile [256],
		new_scriptfile [256],
		current_count[5];

	FILE
		*file_ptr;

	directory_file_list
		*saves_listing,
		*scripts_listing;

	count = -1;

	// STOP MUSIC FIRST
	stop_music(0.0);

	strncpy (limited_filename, filename, sizeof (limited_filename) - 2);
	limited_filename [31] = '\0';

	sprintf (data_filename, "%s\\%s\\%s", game_session->data_path, game_session->campaign_directory, limited_filename);
	sprintf (script_filename, "%s\\%s\\%s", game_session->data_path, game_session->campaign_directory, limited_filename);

	sprintf (extension, ".%s", game_type_extensions [get_game_type ()]);
	extension [3] = extension [2];
	extension [2] = extension [1];
	extension [1] = 'S';
	strncpy (current_savefile, data_filename, sizeof (data_filename));
	strncpy (current_scriptfile, script_filename, sizeof (script_filename));
	strcat (current_savefile, ".sav");
	strcat (current_scriptfile, extension);

	while (TRUE)
	{
		saves_listing = get_first_directory_file (current_savefile);
		scripts_listing = get_first_directory_file (current_scriptfile);

		if (!saves_listing || !scripts_listing)
			break;

		count++;

		sprintf (current_count, "_bak%i", count );

		strncpy (current_savefile, data_filename, sizeof (data_filename));
		strcat (current_savefile, current_count);
		strcat (current_savefile, ".sav");

		strncpy (current_scriptfile, script_filename, sizeof (script_filename));
		strcat (current_scriptfile, current_count);
		strcat (current_scriptfile, extension);
	}

	while (count >= 0)
	{
		count--;

		strncpy (current_savefile, data_filename, sizeof (data_filename));
		strncpy (current_scriptfile, script_filename, sizeof (script_filename));

		if (count >= 0)
		{
			sprintf (current_count, "_bak%i", count );
			strcat (current_savefile, current_count);
			strcat (current_scriptfile, current_count);
		}

		strcat (current_savefile, ".sav");
		strcat (current_scriptfile, extension);

		saves_listing = get_first_directory_file (current_savefile);
		scripts_listing = get_first_directory_file (current_scriptfile);

		if (count >= (command_line_saves_copies - 1))
		{
			if (unlink(current_savefile) || unlink(current_scriptfile))
			{
				debug_fatal("Failed to delete save file %s and/or script file %s", get_directory_file_filename(saves_listing), get_directory_file_filename(scripts_listing));
			}
		}
		else
		{
			strncpy (new_savefile, data_filename, sizeof (data_filename));
			strncpy (new_scriptfile, script_filename, sizeof (script_filename));
			sprintf (current_count, "_bak%i", count + 1 );
			strcat (new_savefile, current_count);
			strcat (new_scriptfile, current_count);
			strcat (new_savefile, ".sav");
			strcat (new_scriptfile, extension);

			if (rename(current_savefile, new_savefile))
			{
				debug_fatal("Failed to rename save file %s to %s", get_directory_file_filename ( saves_listing ), new_savefile);
			}
			
			if (rename(current_scriptfile, new_scriptfile))
			{
				debug_fatal("Failed to rename script file %s to %s", get_directory_file_filename ( scripts_listing ), new_scriptfile);
			}
		}
	}

	if (saves_listing)
		destroy_directory_file_list (saves_listing);
	if (scripts_listing)
		destroy_directory_file_list (scripts_listing);

	strcat (data_filename, ".sav");
	strcat(script_filename, extension);

	//
	// Create scripting file
	//

	file_ptr = fopen (script_filename, "w");

	if (!file_ptr)
	{

		debug_log ("SESSION: failed to open file %s", script_filename);

		return FALSE;
	}

	ASSERT (file_ptr);

	// Start

	set_file_comment (file_ptr, "/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////");
	set_file_tag (file_ptr, application_tag_strings, FILE_TAG_START);
	set_file_comment (file_ptr, "/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////");

	// Campaign title

	set_file_new_line (file_ptr, 1);

	sprintf (title, "%s", game_session->title);

	set_file_comment (file_ptr, "/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////");
	set_file_tag (file_ptr, application_tag_strings, FILE_TAG_TITLE);
	set_file_string (file_ptr, title);
	set_file_comment (file_ptr, "/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////");

	set_file_new_line (file_ptr, 1);

	set_file_comment (file_ptr, "/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////");
	set_file_tag (file_ptr, application_tag_strings, FILE_TAG_SHORT_TEXT_START);

	// campaign title

	set_file_string (file_ptr, game_session->title);

	set_file_new_line (file_ptr, 2);

	// elapsed campaign time
	{
		float
			elapsed_time;

		int
			hours,
			minutes,
			seconds,
			elapsed_days;

		elapsed_time = get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_ELAPSED_TIME);

		convert_float_to_int (elapsed_time / ONE_DAY, &elapsed_days);

		elapsed_time = fmod (elapsed_time, ONE_DAY);

		get_digital_clock_int_values (elapsed_time, &hours, &minutes, &seconds);

		sprintf (script_filename, "%s %d %s, %02d.%02d.%02d",
						get_trans ("Elapsed Time"),
						elapsed_days,
						get_trans ("days"),
						hours, minutes, seconds);



		set_file_string (file_ptr, script_filename);

		set_file_new_line (file_ptr, 1);
	}
	set_file_tag (file_ptr, application_tag_strings, FILE_TAG_TEXT_END);
	set_file_comment (file_ptr, "/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////");
	set_file_new_line (file_ptr, 1);

	set_file_tag (file_ptr, application_tag_strings, FILE_TAG_CAMPAIGN_DATA);

	if (side_data_filename)
	{

		// side data
		set_file_tag (file_ptr, application_tag_strings, FILE_TAG_FILENAME);
		set_file_string (file_ptr, side_data_filename);
	}

	if (population_placement_filename)
	{

		// population data
		set_file_tag (file_ptr, application_tag_strings, FILE_TAG_FILENAME);
		set_file_string (file_ptr, population_placement_filename);
	}

	set_file_tag (file_ptr, application_tag_strings, FILE_TAG_MAP_X_SIZE);
	set_file_int (file_ptr, world_map.num_map_x_sectors);
	set_file_tag (file_ptr, application_tag_strings, FILE_TAG_MAP_Z_SIZE);
	set_file_int (file_ptr, world_map.num_map_z_sectors);
	set_file_tag (file_ptr, application_tag_strings, FILE_TAG_MAP_SECTOR_SIZE);
	set_file_int (file_ptr, world_map.sector_side_length);

	if (campaign_population_filename)
	{

		// population data
		set_file_tag (file_ptr, application_tag_strings, FILE_TAG_FILENAME);
		set_file_string (file_ptr, campaign_population_filename);
	}

	//
	// save force in reverse order to list (so that they are read_in in the correct order)
	//

	force = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

	ASSERT (force);

	while (get_local_entity_child_succ (force, LIST_TYPE_FORCE))
	{

		force = get_local_entity_child_succ (force, LIST_TYPE_FORCE);
	}

	while (force)
	{

		set_file_tag (file_ptr, application_tag_strings, FILE_TAG_FACTION);
		set_file_tag (file_ptr, application_tag_strings, FILE_TAG_SIDE);
		set_file_enum (file_ptr, entity_side_names, get_local_entity_int_value (force, INT_TYPE_SIDE));

		set_file_tag (file_ptr, application_tag_strings, FILE_TAG_COLOUR);
		set_file_enum (file_ptr, sys_colour_names, get_local_entity_int_value (force, INT_TYPE_COLOUR));

		force = get_local_entity_child_pred (force, LIST_TYPE_FORCE);
	}

	set_file_tag (file_ptr, application_tag_strings, FILE_TAG_END);

	// Campaign saved filename

	set_file_new_line (file_ptr, 1);

	set_file_comment (file_ptr, "/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////");
	set_file_tag (file_ptr, application_tag_strings, FILE_TAG_SAVED_CAMPAIGN);

	set_file_tag (file_ptr, application_tag_strings, FILE_TAG_PATH);
	set_file_string (file_ptr, game_session->data_path);

	set_file_tag (file_ptr, application_tag_strings, FILE_TAG_PATH);
	set_file_string (file_ptr, game_session->campaign_directory);

	set_file_tag (file_ptr, application_tag_strings, FILE_TAG_FILENAME);
	set_file_string (file_ptr, game_session->campaign_filename);

	set_file_comment (file_ptr, "/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////");

	set_file_new_line (file_ptr, 1);

	//
	// Version number
	//

	{

		int
			value;
		set_file_comment (file_ptr, "/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////");

		set_file_tag (file_ptr, application_tag_strings, FILE_TAG_VERSION_NUMBER);
		value = get_local_entity_int_value ( get_session_entity (), INT_TYPE_VERSION_NUMBER );
		set_file_int (file_ptr, value);

		set_file_comment (file_ptr, "/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////");
	}

	// End

	//VJ 051202 add season (camo) info to file description
	//use set and get_global_season
	set_file_comment (file_ptr, "/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////");
	set_file_tag (file_ptr, application_tag_strings, FILE_TAG_SEASON);
	set_file_int (file_ptr, (int) get_global_season() );
	set_file_comment (file_ptr, "/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////");

	set_file_comment (file_ptr, "/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////");
	set_file_tag (file_ptr, application_tag_strings, FILE_TAG_END);
	set_file_comment (file_ptr, "/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////");

	fclose (file_ptr);

	//
	// Save entity data
	//

	file_ptr = fopen (data_filename, "wb");

	if (file_ptr)
	{

		unsigned char
			*save_ptr,
			*buffer;

		int
			extra_data,
			server_version_number,
			buffer_size;

		buffer_size = 1024 * 1024;

		buffer = (unsigned char *) malloc_heap_mem (buffer_size);

		save_ptr = buffer;

		extra_data = 0;

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// write out version number
		server_version_number = get_local_entity_int_value (get_session_entity (), INT_TYPE_VERSION_NUMBER);

		quick_set_list_item (save_ptr, int, server_version_number);

		buffer_size -= sizeof (int);
		extra_data += sizeof (int);
		//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// write out session
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		while (pack_session (save_ptr, &buffer_size, PACK_MODE_SERVER_SESSION))
		{

			debug_log ("SESSION: mallocing store pack buffer from %d to %d", buffer_size, buffer_size * 2);

			free_mem (buffer);

			buffer_size *= 2;

			buffer = (unsigned char *) malloc_heap_mem (buffer_size);

			save_ptr = buffer;

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// write out version number
			server_version_number = get_local_entity_int_value (get_session_entity (), INT_TYPE_VERSION_NUMBER);

			quick_set_list_item (save_ptr, int, server_version_number);

			buffer_size -= sizeof (int);
			//
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		}

		fwrite (buffer, buffer_size + extra_data, 1, file_ptr);

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		free_mem (buffer);
	}

	fclose (file_ptr);

	//
	//
	//

	// arneh feb 2009 - this call shouldn't be necessary, and it will double initialise things which confuses EECH
	//	set_current_game_session (game_session);

	// RESUME MUSIC LAST
	probably_change_cd_music();

	#endif

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void recursive_check_campaign_files (const char *directory, session_list_data_type **list, const char *extension)
{

	session_list_types
		session_type;

	directory_file_list
		*warzone_file,
		*directory_listing;

	unsigned int
		i,
		upper;

	int
		value,
		valid_file,
		season;

	static char
		operator_ [64],
		variable [64],
		temp_warzone_name [128],
		*warzone_name,
		warzone_path [1024],
		directory_search_path [1024];

	//
	// First, go through any files in this directory.
	//

	sprintf (directory_search_path, "%s\\*.%s", directory, extension);

	// Jabberwock 0400201 Session filter revised

	//VJ 050123 small bug fix: check for lowercase AND uppercase
	if ((strstr(directory, "CAMP01") || strstr(directory, "camp01")) && command_line_session_filter)
	{
		sprintf(warzone_path, "%s\\*.chc", directory);

		warzone_file = get_first_directory_file(warzone_path);

		sprintf(temp_warzone_name, "%s", get_directory_file_filename (warzone_file));

	//  Vadim 051120, if chc filename has spaces, capitalize every word

		for (upper=1, i = 0; i < (strlen (temp_warzone_name) - 4); i++)
		{
			if (upper)
			{
				temp_warzone_name[i] = toupper (temp_warzone_name[i]);
				upper=0;
			}
			else if (isspace(temp_warzone_name[i])) {
					upper=1;
			}
			else
			{
				temp_warzone_name[i] = tolower (temp_warzone_name[i]);
			}
		}

		temp_warzone_name[i] = '\0';

		for (i = 0; i < (strlen (directory) - 7); i++)
		{
			warzone_path[i] = directory[i];
		}

		warzone_path[i] = '\0';


		add_session (temp_warzone_name, SESSION_LIST_TYPE_FILTER, 1, NULL, warzone_path, NULL, NULL, temp_warzone_name, list, NULL, SESSION_SEASON_INVALID);
	}


	directory_listing = get_first_directory_file (directory_search_path);

	// JB 030313 Enable running out of separate directories
	if (!directory_listing)
	{
		char fn[1024];
		fn[0] = 0;
		strcpy(fn, comanche_hokum_installation_path);
		strcat(fn, "\\common\\");
		strcat(fn, directory_search_path);

		directory_listing = get_first_directory_file ( fn );
	}

	if (directory_listing)
	{

		valid_file = TRUE;

		while (valid_file)
		{

			session_type = SESSION_LIST_TYPE_HOST;

			if (get_directory_file_type (directory_listing) == DIRECTORY_FILE_TYPE_FILE)
			{

				FILE
					*file_ptr;

				file_tags
					tag;

				int
					end_flag;

				static char
					*ptr,
					*last_ptr,
					path [1024],
					full_filename [1024],
					campaign_title [1024],
					campaign_directory [32],
					campaign_filename [1024];

				//
				// Add campaign file to list
				//

				sprintf (full_filename, "%s\\%s", directory, get_directory_file_filename (directory_listing));

				file_ptr = safe_fopen (full_filename, "r");

				end_flag = FALSE;

				warzone_name = NULL;

				season = SESSION_SEASON_INVALID;

				while (!end_flag)
				{

					tag = (file_tags) get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

					switch (tag)
					{

						case FILE_TAG_WARZONE_NAME:
						{

							get_next_file_string (file_ptr, temp_warzone_name, sizeof (temp_warzone_name));

							warzone_name = temp_warzone_name;

							break;
						}

						case FILE_TAG_TITLE:
						{

							get_next_file_string (file_ptr, campaign_title, sizeof (campaign_title));

							//
							// Create data path, ie strip off the last directory name
							// N.B. valid data directories are in any directory below 'MAPS'.
							//

							strcpy (path, directory);

							ptr = strstr (path, "\\maps\\");

							ptr += strlen ("\\maps\\");

							while (ptr = strstr (ptr, "\\"))
							{

								ptr += strlen ("\\");

								last_ptr = ptr;
							}

							sprintf (campaign_directory, "%s", last_ptr);

							sprintf (campaign_filename, "%s", get_directory_file_filename (directory_listing));

							last_ptr -= strlen ("\\");

							*last_ptr = '\0';

							break;
						}

						case FILE_TAG_LANGUAGE_TEXT_START:
						{

							// skip script till correct language

							while (tag = (file_tags) get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG))
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

							while (tag = (file_tags) get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG))
							{

								if (tag == FILE_TAG_LANGUAGE_TEXT_STOP)
								{

									break;
								}
							}

							break;
						}

						case FILE_TAG_CAMPAIGN_DATA:
						{

							while (tag = (file_tags) get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG))
							{

								if (tag == FILE_TAG_END)
								{

									break;
								}
							}

							break;
						}

						case FILE_TAG_SAVED_CAMPAIGN:
						{

							session_type = SESSION_LIST_TYPE_RESTORE;

							break;
						}

						case FILE_TAG_IF:
						{

							ASSERT (get_current_player_log ());

							get_next_file_word (file_ptr, variable, sizeof (variable));

							get_next_file_word (file_ptr, operator_, sizeof (operator_));

							value = get_next_file_int (file_ptr);

							if (!if_file_tag_variable (variable, operator_, value))
							{

								// skip script till endif

								while (tag = (file_tags) get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG))
								{

									if ((tag == FILE_TAG_ENDIF) || (tag == FILE_TAG_END))
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

						case FILE_TAG_SEASON:
						{
							// 15JUN09 Casm retrieving season earlier
							season = get_next_file_int (file_ptr);

							break;
						}

						case FILE_TAG_CAMPAIGN_REQUIRES_APACHE_HAVOC:
						{
							debug_log("session filter: campaign_title %s", campaign_title);
							// VJ 050123 aphavoc install hack, do not close map if it exists but EEAH is not offcially installed
							if (!global_aphavoc_maps)
							{
								if (!get_global_apache_havoc_installed ())
								{

									end_flag = TRUE;

									debug_log ("SESSION: Campaign %s required Apache-Havoc to be installed", campaign_title);

									break;
								}
							}
						}

						case FILE_TAG_END:
						case FILE_TAG_UNKNOWN:
						{

							end_flag = TRUE;

							if ((!command_line_session_filter) || (strcmp(session_filter_value, "root") != 0))
							{
								// 15JUN09 Casm retrieving season earlier
								const char
									*title;
								// if host get the Translated campaign name
								// not hosted game so just use the name
								title = session_type == SESSION_LIST_TYPE_HOST ? get_trans (campaign_title) :  campaign_title;
								if (session_type == SESSION_LIST_TYPE_HOST || (session_type == SESSION_LIST_TYPE_MASTER) || (session_type == SESSION_LIST_TYPE_RESTORE))
								{
									add_session (title, session_type, 1, NULL, path, campaign_directory, campaign_filename, warzone_name, list, NULL, season);
								}
							}
							// Jabberwock 0400201 ends

							break;
						}
					}
				}

				fclose (file_ptr);
			}

			valid_file = get_next_directory_file (directory_listing);
		}

		destroy_directory_file_list (directory_listing);
	}

	//
	// Next, go through any directories, recursing into them.
	//

	sprintf (directory_search_path, "%s\\*", directory);

	directory_listing = get_first_directory_file (directory_search_path);

	// JB 030313 Enable running out of separate directories
	if (!directory_listing)
	{
		char fn[1024];
		fn[0] = 0;
		strcpy(fn, comanche_hokum_installation_path);
		strcat(fn, "\\common\\");
		strcat(fn, directory_search_path);

		directory_listing = get_first_directory_file ( fn );
	}

	if (directory_listing)
	{

		valid_file = TRUE;

		while (valid_file)
		{

			if (get_directory_file_type (directory_listing) == DIRECTORY_FILE_TYPE_DIRECTORY)
			{

				if ((strcmp (get_directory_file_filename (directory_listing), ".") != 0) &&
						(strcmp (get_directory_file_filename (directory_listing), "..") != 0))
				{

					char
						full_directory [1024];

					//
					// Create the full directory name
					//

					sprintf (full_directory, "%s\\%s", directory, get_directory_file_filename (directory_listing));

					//
					// Recurse into this directory
					//

					recursive_check_campaign_files (full_directory, list, extension);
				}
			}

			valid_file = get_next_directory_file (directory_listing);
		}

		destroy_directory_file_list (directory_listing);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_current_game_session (session_list_data_type *game_session)
{

	current_game_session = game_session;

	if (game_session)
	{

		if (get_comms_model () == COMMS_MODEL_SERVER)
		{

			//set_ui_object_drawable (session_screen_next_button_mask, FALSE);

			set_ui_object_drawable (session_screen_next_bdrop, TRUE);

			set_ui_object_drawable (session_screen_next_button, TRUE);

			// 15JUN09 Casm setting map information for saved games
			notify_session_parameters ();
			if (game_session->type == SESSION_LIST_TYPE_RESTORE)
			{
				set_ui_object_drawable (session_briefing_overlay, TRUE);
			}
		}
		else if (get_comms_model () == COMMS_MODEL_CLIENT)
		{
			set_ui_object_drawable (session_briefing_overlay, TRUE);
		}
	}
	else
	{

		//set_ui_object_drawable (session_screen_next_button_mask, TRUE);

		notify_clear_all_session_parameters ();

		set_ui_object_drawable (session_screen_next_bdrop, FALSE);

		set_ui_object_drawable (session_screen_next_button, FALSE);

		set_ui_object_drawable (session_screen_continue_button, FALSE); // Jabberwock 031118 Server side settings

		set_ui_object_drawable (session_screen_continue_bdrop, FALSE);

		set_ui_object_drawable (session_briefing_overlay, FALSE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void start_campaign (void)
{

	//
	// Check mission data has arrived...
	//

	ASSERT (current_game_session);

	switch (current_game_session->type)
	{

		case SESSION_LIST_TYPE_RESTORE:
		{

			create_campaign (get_current_game_session ());

			process_restore_session_setup_options ();

			break;
		}
		case SESSION_LIST_TYPE_HOST:
		{

			create_campaign (get_current_game_session ());

			process_host_session_setup_options ();

			break;
		}
		case SESSION_LIST_TYPE_JOIN:
		{

			if (!get_session_entity ())
			{

				return;
			}

			break;
		}
		case SESSION_LIST_TYPE_MASTER:
		{
			current_game_session->type = SESSION_LIST_TYPE_JOIN;

			//TODO: Setup dplay connection, then get first active session.

			if (!get_session_entity ())
			{

				return;
			}

			break;
		}
		// Jabberwock 031210 Session filter
		case SESSION_LIST_TYPE_FILTER:
		{
			if (!get_session_entity ())
			{

				return;
			}

			break;
		}
		// Jabberwock 031210 ends
		case SESSION_LIST_TYPE_INVALID:
		default:
		{

			debug_fatal ("GUNS_SC: unknown game type");
		}
	}

	ui_set_user_function (NULL);

	switch ( get_global_gunship_type () )
	{

		case GUNSHIP_TYPE_APACHE:
		case GUNSHIP_TYPE_COMANCHE:
		{

			//play_music ( MUSIC_TRACK_INGAME, FALSE );

			break;
		}
		case GUNSHIP_TYPE_HAVOC:
		case GUNSHIP_TYPE_HOKUM:
		{

			//play_music ( MUSIC_TRACK_INGAME, FALSE );

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
