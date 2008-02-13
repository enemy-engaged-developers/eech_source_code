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

#include "servlog.h" // Jabberwock Server log

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

#define NUM_TABLE_ENTRIES 10

#define FLASH_RATE 1.0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity
	*pilot_entity = NULL;

static float
	flash_timer = 0.0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct PILOT_SCORE_TYPE
{
	int
		kills,
		valid;

	entity_sides
		side;
	
	char
		name [STRING_TYPE_PLAYERS_NAME_MAX_LENGTH + 1];
};

typedef struct PILOT_SCORE_TYPE pilot_score_type;

pilot_score_type pilot_high_score_table [NUM_TABLE_ENTRIES];

static void qs_table (pilot_score_type *list, int left, int right);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void send_pilot_joined_message (entity *en);

static int get_session_pilot_count (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_pilot_entity (entity *en)
{
	comms_data_flow_types
		store_data_flow;

	if (en)
	{
		debug_log ("PILOT: Setting pilot_entity to %s", get_local_entity_string (en, STRING_TYPE_PILOTS_NAME));

		ASSERT (pilot_entity == NULL);

		ASSERT (get_local_entity_type (en) == ENTITY_TYPE_PILOT);
	
		pilot_entity = en;

		// turn on NEXT button now Pilot entity has arrived
		if (get_comms_model () == COMMS_MODEL_CLIENT)
		{

			set_display_gunship_buttons (FALSE, "ENGAGE");

			// turn on only the gunship_next button
			set_ui_object_drawable (gunship_screen_next_button, TRUE);
		}
		//-- Werewolf
		else
		{
			// If we're the server, remember our player name. This will be sent out in the heartbeat packets.
			net_set_hostname( get_local_entity_string (en, STRING_TYPE_PILOTS_NAME) );
		}
		//-- Werewolf
	}
	else if (pilot_entity)
	{
		debug_log ("PILOT: Setting pilot_entity to NULL");

		ASSERT (pilot_entity);

		//
		// Program MUST be in TX mode otherwise clients pilot will not be destroyed on the server
		//
		
		store_data_flow = get_comms_data_flow ();

		set_comms_data_flow (COMMS_DATA_FLOW_TX);

		destroy_client_server_entity (pilot_entity);

		set_comms_data_flow (store_data_flow);

		pilot_entity = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void send_pilot_joined_message (entity *en)
{
	int
		player_count;

	char
		text [200];

	//
	// Client now joined in..... send system message to other players
	//

	player_count = get_session_pilot_count ();

	if (player_count == 1)
	{
		sprintf (text, "%s %s - 1 %s",
							get_local_entity_string (en, STRING_TYPE_PILOTS_NAME),
							get_trans ("joined"),
							get_trans ("player connected"));
	}
	else
	{
		sprintf (text, "%s %s - %d %s",
							get_local_entity_string (en, STRING_TYPE_PILOTS_NAME),
							get_trans ("joined"),
							player_count,
							get_trans ("players connected"));
	}

	send_text_message (en, NULL, MESSAGE_TEXT_SYSTEM_NEW_PILOT, text);
	
	server_log (text); // Jabberwock Server log
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void send_pilot_quit_message (entity *en)
{
	int
		player_count;

	char
		text [200];

	//
	// Client now joined in..... send system message to other players
	//

	player_count = get_session_pilot_count () - 1;

	if (player_count == 1)
	{
		sprintf (text, "%s %s - 1 %s",
							get_local_entity_string (en, STRING_TYPE_PILOTS_NAME),
							get_trans ("quit"),
							get_trans ("player connected"));
	}
	else
	{
		sprintf (text, "%s %s - %d %s",
							get_local_entity_string (en, STRING_TYPE_PILOTS_NAME),
							get_trans ("quit"),
							player_count,
							get_trans ("players connected"));
	}

	send_text_message (en, NULL, MESSAGE_TEXT_SYSTEM_NEW_PILOT, text);
	
	server_log (text); // Jabberwock Server log
	
	if ((command_line_pause_server) && (player_count <= 1)) // 040220 Jabberwock Pause server, changed to <=1 by Werewolf
	{
		force_pause_acceleration();
		server_log ("Server paused");
	}
}	
// 040220 Jabberwock ends

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_new_pilot_entity (const char *name, entity_sides side, int rank, entity_sub_types sub_type, int unique_id, int difficulty)
{
	entity
		*en,
		*force;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);
	
	ASSERT (name);

	force = get_local_force_entity (side);

	ASSERT (force);

	en = create_client_server_entity
				(
					ENTITY_TYPE_PILOT,
					ENTITY_INDEX_DONT_CARE,
					ENTITY_ATTR_PARENT (LIST_TYPE_PILOT, force),
					ENTITY_ATTR_STRING (STRING_TYPE_PILOTS_NAME, name),
					ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, sub_type),
					ENTITY_ATTR_INT_VALUE (INT_TYPE_UNIQUE_ID, unique_id),
					ENTITY_ATTR_INT_VALUE (INT_TYPE_SIDE, side),
					ENTITY_ATTR_INT_VALUE (INT_TYPE_PILOT_RANK, rank),
					ENTITY_ATTR_INT_VALUE (INT_TYPE_DIFFICULTY_LEVEL, difficulty),
					ENTITY_ATTR_END
				);

	send_pilot_joined_message (en);

	return en;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_server_pilot (void)
{
	entity
		*en;
		
	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	en = create_new_pilot_entity
				(
					get_player_log_name (get_current_player_log ()),
					get_global_gunship_side (),
					get_player_log_rank (get_global_gunship_side (), get_current_player_log ()),
					ENTITY_SUB_TYPE_PILOT_PILOT,
					direct_play_get_player_id (),
					get_global_difficulty_level ()
				);

	set_pilot_entity (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_client_pilot (void)
{
	client_pilot_request_data
		pilot_data;

	ASSERT (get_comms_model () == COMMS_MODEL_CLIENT);

	//
	// pack required gunship data
	//

	strcpy (pilot_data.name, get_player_log_name (get_current_player_log ()));
	pilot_data.side = get_global_gunship_side ();
	pilot_data.rank = get_player_log_rank (get_global_gunship_side (), get_current_player_log ());
	pilot_data.sub_type = ENTITY_SUB_TYPE_PILOT_PILOT;
	pilot_data.unique_id = direct_play_get_player_id ();
	pilot_data.difficulty = get_global_difficulty_level ();

	//
	// Send request
	//

	send_packet (get_server_id (), PACKET_TYPE_CLIENT_PILOT_REQUEST, (void *) &pilot_data, sizeof (client_pilot_request_data), SEND_TYPE_PERSONAL);

	// turn off NEXT button while Pilot entity is being created client_server
	if (get_comms_model () == COMMS_MODEL_CLIENT)
	{

		set_display_gunship_buttons (FALSE, "ENGAGE");
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_session_pilot_count (void)
{
	entity
		*force,
		*pilot;

	int
		count;
	
	ASSERT (get_session_entity ());

	count = 0;

	force = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

	while (force)
	{
		pilot = get_local_entity_first_child (force, LIST_TYPE_PILOT);

		while (pilot)
		{
			count ++;

			pilot = get_local_entity_child_succ (pilot, LIST_TYPE_PILOT);
		}

		force = get_local_entity_child_succ (force, LIST_TYPE_FORCE);
	}

	return count;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_pilot_high_score_table (void)
{
	memset (pilot_high_score_table, 0, sizeof (pilot_score_type) * NUM_TABLE_ENTRIES);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *get_player_task (entity *en)
{
	if (!en)
	{
		en = get_pilot_entity ();
	}

	ASSERT (en);

	ASSERT (get_local_entity_type (en) == ENTITY_TYPE_PILOT);

	return get_local_entity_parent (en, LIST_TYPE_PLAYER_TASK);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int update_pilot_high_score_table (void)
{
	int
		count,
		num_pilots;

	entity
		*force_en,
		*pilot_en;

	pilot_score_type
		*full_table;

	//
	// clear table
	//

	debug_log ("PILOT: Updating High Score Table");

	initialise_pilot_high_score_table ();

	num_pilots = 0;

	//
	// count up player pilots
	//

	ASSERT (get_session_entity ());

	force_en = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

	while (force_en)
	{
		pilot_en = get_local_entity_first_child (force_en, LIST_TYPE_PILOT);

		while (pilot_en)
		{
			num_pilots ++;

			pilot_en = get_local_entity_child_succ (pilot_en, LIST_TYPE_PILOT);
		}

		force_en = get_local_entity_child_succ (force_en, LIST_TYPE_FORCE);
	}

	if (num_pilots == 0)
	{
		return 0;
	}

	//
	// create arrays of player pilots and their scores
	//

	full_table = malloc_fast_mem (sizeof (pilot_score_type) * num_pilots);

	count = 0;

	force_en = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

	while (force_en)
	{
		pilot_en = get_local_entity_first_child (force_en, LIST_TYPE_PILOT);

		while (pilot_en)
		{
			full_table [count].kills = get_local_entity_int_value (pilot_en, INT_TYPE_KILLS);

			full_table [count].side = get_local_entity_int_value (pilot_en, INT_TYPE_SIDE);

			full_table [count].valid = TRUE;

			strcpy (full_table [count].name, get_local_entity_string (pilot_en, STRING_TYPE_PILOTS_NAME));

			debug_log ("PILOT: Adding %s (kills %d) to High Score Table", full_table [count].name, full_table [count].kills);

			count ++;

			pilot_en = get_local_entity_child_succ (pilot_en, LIST_TYPE_PILOT);
		}

		force_en = get_local_entity_child_succ (force_en, LIST_TYPE_FORCE);
	}

	ASSERT (count == num_pilots);

	//
	// quicksort the list
	//

   qs_table (full_table, 0, num_pilots - 1);

	//
	// add first n items to the high score table
	//

	count = min (num_pilots, NUM_TABLE_ENTRIES);

	memcpy (pilot_high_score_table, full_table, sizeof (pilot_score_type) * count);

	free_mem (full_table);

	return count;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void qs_table (pilot_score_type *list, int left, int right)
{
   int
      i, j, x;

   pilot_score_type
      temp;

   i = left;
   j = right;

   x = list [(left + right) / 2].kills;

   do
   {
      while (list [i].kills > x && i < right) i++;
      while (x > list [j].kills && j > left) j--;

      if (i <= j)
      {
         temp = list [i];
         list [i] = list [j];
         list [j] = temp;
         
         i++;
         j--;
      }

   } while (i <= j);

   if (left < j) qs_table (list, left, j);
   if (i < right) qs_table (list, i, right);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_high_score_table (void)
{

	char
		buffer [256];

	int
		loop,
		length;

	screen
		*old_active_screen;

	pilot_score_type
		*item;

	old_active_screen = get_active_screen ();

	set_active_screen ( video_screen );

	if ( lock_screen ( active_screen ) )
	{
		//
		// draw leaderboard
		//
		
		for (loop = 0; loop < NUM_TABLE_ENTRIES; loop ++)
		{
			item = &pilot_high_score_table [loop];
			
			if (item->valid)
			{
				set_ui_font_type (UI_FONT_ARIAL_14);

				if (item->side == ENTITY_SIDE_BLUE_FORCE)
				{
					set_ui_font_colour (ui_colour_blue);
				}
				else
				{
					set_ui_font_colour (ui_colour_orange);
				}

				length = ui_get_string_length (item->name);
	
				sprintf (buffer, "%s : %d", item->name, item->kills);

				// print text assuming game-exit overlay is 640x480 centred in the screen whatever res.
				ui_display_text (buffer, get_integer_screen_x_mid () - length, iy_640_480 + 180 + (loop * (ui_get_font_height () + 1)));
			}
		}

		//
		// update flash timer
		//

		flash_timer += (FLASH_RATE * get_delta_time ());

		flash_timer = frac (flash_timer);

		unlock_screen ( active_screen );
	}

	set_active_screen ( old_active_screen );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_high_score_table_to_ui_object_list (ui_object *blue_list_object, ui_object *red_list_object)
{

	char
		buffer [256];

	int
		loop;

	pilot_score_type
		*item;
		
	rgb_colour
		*col;

	ui_object
		*list;

	for (loop = 0; loop < NUM_TABLE_ENTRIES; loop ++)
	{
		item = &pilot_high_score_table [loop];
			
		if (item->valid)
		{
			if (item->side == ENTITY_SIDE_BLUE_FORCE)
			{
				col = &ui_colour_blue;
	
				list = blue_list_object;
			}
			else
			{
				col = &ui_colour_orange;

				list = red_list_object;
			}

			sprintf (buffer, "%s: %d", item->name, item->kills);
	
			add_to_pop_up_list (buffer, list, NULL, UI_LIST_NO_SELECTION, UI_FONT_ARIAL_14, *col);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char *get_high_score_table_entry (int index, int *side, int *kills)
{
	pilot_score_type
		*item;
		
	ASSERT (side);

	ASSERT (kills);

	ASSERT ((index >= 0) && (index < NUM_TABLE_ENTRIES));

	item = &pilot_high_score_table [index];
		
	if (item->valid)
	{
		*side = item->side;

		*kills = item->kills;

		return item->name;
	}
	else
	{
		return NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char *get_high_score_table_first_name (void)
{
	pilot_score_type
		*item;
		
	item = &pilot_high_score_table [0];
		
	if (item->valid)
	{
		return (item->name);
	}
	else
	{
		return NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_special_restart_text (void)
{
	char
		buffer [64];

	int
		string_length;
	
	float
		x;

	//
	// display game name
	//

	if (current_game_session)
	{
		sprintf (buffer, "%s", current_game_session->title);
		string_length = ui_get_string_length ( buffer );

		x = get_integer_screen_x_mid () - (string_length / 2);

		ui_display_text (buffer, x, 73 + iy_640_480);
	}

	//
	// display flashing message
	//

	if (flash_timer < 0.666)
	{
		set_ui_font_type (UI_FONT_ARIAL_14);

		set_ui_font_colour (ui_colour_yellow);

		sprintf ( buffer, get_trans ("PRESS SPACE") );

		string_length = ui_get_string_length (buffer);

		ui_display_text (buffer, get_integer_screen_x_mid () - (string_length / 2), 420 + iy_640_480);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

