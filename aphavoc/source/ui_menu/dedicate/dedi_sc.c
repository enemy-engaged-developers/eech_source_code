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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ui_object
	*dedicated_server_screen;

static ui_object
	*player_list,
	*player_list_area,
	*dedicated_server_quit_button,
	*dedicated_server_title_text,
	*dedicated_server_map_text,
	*dedicated_server_game_text,
	*dedicated_server_time_text;

texture_graphic
	*dedicated_server_screen_texture;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_dedicated_server_quit_button (ui_object *obj, void *arg);

static void dedicated_screen_update_function (ui_object *obj, void *arg);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_dedicated_server_screen (void)
{
	float
		x, y;

	dedicated_server_screen = create_ui_object
		(
			UI_TYPE_SCREEN,
			UI_ATTR_POSITION (0, 0),
			UI_ATTR_VIRTUAL_SIZE (1.0, 1.0),
			UI_ATTR_FUNCTION (dedicated_server_function),
			UI_ATTR_DRAW_FUNCTION (dedicated_screen_update_function),
			UI_ATTR_END
		);

	create_ui_object
			(
				UI_TYPE_TEXT,
				UI_ATTR_PARENT (dedicated_server_screen),
				UI_ATTR_VIRTUAL_POSITION (0.66, 0.141666),
				UI_ATTR_TEXT ("Dedicated Server"),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_22),
				UI_ATTR_END
			);

	x = 0.125;
	y = 0.62;

	dedicated_server_title_text = create_ui_object
			(
				UI_TYPE_TEXT,
				UI_ATTR_PARENT (dedicated_server_screen),
				UI_ATTR_VIRTUAL_POSITION (x, y),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_22),
				UI_ATTR_END
			);

	x = 0.125;
	y += 0.0625;

	dedicated_server_map_text = create_ui_object
			(
				UI_TYPE_TEXT,
				UI_ATTR_PARENT (dedicated_server_screen),
				UI_ATTR_VIRTUAL_POSITION (x, y),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_22),
				UI_ATTR_END
			);

	x = 0.125;
	y += 0.0625;

	dedicated_server_game_text = create_ui_object
			(
				UI_TYPE_TEXT,
				UI_ATTR_PARENT (dedicated_server_screen),
				UI_ATTR_VIRTUAL_POSITION (x, y),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_22),
				UI_ATTR_END
			);

	x = 0.125;
	y += 0.0625;

	dedicated_server_time_text = create_ui_object
			(
				UI_TYPE_TEXT,
				UI_ATTR_PARENT (dedicated_server_screen),
				UI_ATTR_VIRTUAL_POSITION (x, y),
				UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_22),
				UI_ATTR_END
			);

	dedicated_server_quit_button = create_ui_object
								(
									UI_TYPE_BUTTON,
									UI_ATTR_PARENT (dedicated_server_screen),
									UI_ATTR_VIRTUAL_POSITION (0.0, 0.89583),
									UI_ATTR_VIRTUAL_SIZE (0.125, 0.0625),
									UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_22),
									UI_ATTR_TEXT (get_trans("UI_EXIT")),
									UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_EITHER),
									UI_ATTR_FUNCTION (notify_dedicated_server_quit_button),
									UI_ATTR_HIGHLIGHTABLE (TRUE),
									UI_ATTR_CLEAR (TRUE),
									UI_ATTR_END
								);

	/////////////////////////////////////////////////////////////////
	// List of players

	{
		float
			x1, y1,
			x2, y2;
			
		x1 = 0.125;
		y1 = 0.175;
		x2 = 0.6;
		y2 = 0.6;

		player_list_area = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (dedicated_server_screen),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
				UI_ATTR_VSLIDER (0, 300, 12),
				UI_ATTR_TEXTURE_GRAPHIC (list_box_graphic),
				UI_ATTR_END
			);

		set_frontend_slider_graphics (player_list_area);

		// List Box

		x1 = 0.05;
		y1 = 0.05;
		x2 = 0.95;
		y2 = 0.95;

		player_list = create_ui_object
				(
					UI_TYPE_LIST_BOX,
					UI_ATTR_PARENT (player_list_area),
					UI_ATTR_VIRTUAL_POSITION (x1, y1),
					UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
					UI_ATTR_CLEAR (TRUE),
					UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
					UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_NONE),
					UI_ATTR_END
				);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_dedicated_server_quit_button (ui_object *obj, void *arg)
{

	if ((int) arg == BUTTON_STATE_DOWN)
	{

		set_ui_object_graphic (obj, (unsigned short int *) get_graphics_file_data (GRAPHICS_UI_APACHE_PLANNER_BACK_BUTTON_SELECTED));

		set_ui_object_redraw (dedicated_server_screen, TRUE);
	}
	else if ((int) arg == BUTTON_STATE_UP)
	{

		set_ui_object_graphic (obj, (unsigned short int *) get_graphics_file_data (GRAPHICS_UI_APACHE_PLANNER_BACK_BUTTON_UNSELECTED));

		//deinitialise_base_system ();
	
		//setup_campaign_over_screen (get_local_force_entity (get_global_gunship_side ()), CAMPAIGN_CRITERIA_RESULT_SERVER_REJECTED);

		start_game_exit (GAME_EXIT_APACHE_HAVOC, FALSE);
	}
	else 
	{

		set_ui_object_graphic (obj, (unsigned short int *) get_graphics_file_data (GRAPHICS_UI_APACHE_PLANNER_BACK_BUTTON_UNSELECTED));

		set_ui_object_redraw (dedicated_server_screen, TRUE);
	}

	//set_ui_object_graphic_type (obj, UI_OBJECT_ALPHA_GRAPHIC);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void dedicated_server_function (ui_object *obj, void *arg)
{

	char
		buffer [256];

	set_mouse_on ();

	set_mouse_graphic_on ();

	ASSERT (current_game_session);

	//

	if ( get_ui_object_drawable ( obj ) )
	{

		if ( main_screen_texture )
		{
	
			destroy_texture_graphic (dedicated_server_screen_texture);

			dedicated_server_screen_texture = NULL;
		}
	
		dedicated_server_screen_texture = create_texture_graphic ( "graphics\\ui\\cohokum\\demoload.psd" );
	
		set_ui_object_texture_graphic (dedicated_server_screen, dedicated_server_screen_texture);
	
		blit_front_buffer_to_render_buffer ();
	
		ui_set_user_function (NULL);
	}
	else
	{
		if (main_screen_texture)
		{
	
			destroy_texture_graphic (dedicated_server_screen_texture);

			dedicated_server_screen_texture = NULL;
		}
	}
	//

	sprintf (buffer, "Title : %s", current_game_session->title);

	set_ui_object_text (dedicated_server_title_text, buffer);

	sprintf (buffer, "Map : %s", current_game_session->data_path);

	set_ui_object_text (dedicated_server_map_text, buffer);

	sprintf (buffer, "Game : %s", current_game_session->campaign_filename);

	set_ui_object_text (dedicated_server_game_text, buffer);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void dedicated_server_build_player_list (void)
{
	entity
		*force,
		*pilot;

	entity_sides
		side;

	rgb_colour
		col;

	ui_object_destroy_list_items (player_list);

	force = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

	while (force)
	{
		pilot = get_local_entity_first_child (force, LIST_TYPE_PILOT);

		while (pilot)
		{
			if (pilot != get_pilot_entity ())
			{
				side = (entity_sides) get_local_entity_int_value (pilot, INT_TYPE_SIDE);

				col.r = 255;
				col.g = 255;
				col.b = 255;
				col.a = 255;

				add_to_pop_up_list (get_local_entity_string (pilot, STRING_TYPE_PILOTS_NAME), player_list, NULL, 0, UI_FONT_ARIAL_16, col);
			}
			
			pilot = get_local_entity_child_succ (pilot, LIST_TYPE_PILOT);
		}

		force = get_local_entity_child_succ (force, LIST_TYPE_FORCE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void dedicated_screen_update_function (ui_object *obj, void *arg)
{

	float
		time;

	int
		hours,
		minutes,
		seconds;

	char
		s [64];

	ASSERT (command_line_comms_dedicated_server);

	if (get_session_entity ())
	{

		if (get_local_entity_int_value (get_session_entity (), INT_TYPE_SESSION_COMPLETE))
		{

			if (!get_connection_list_head ())
			{

				debug_log ("DEDI_SC: Exiting game as no clients left");

				exit_apache_havoc (NULL);
			}
		}

		time = get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_ELAPSED_TIME);

		get_digital_countdown_values (time, NULL, &hours, &minutes, &seconds);
	
		sprintf (s, "Day %d, %02d:%02d:%02d", get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY), hours, minutes, seconds);

		set_ui_object_text (dedicated_server_time_text, s);

		dedicated_server_build_player_list ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
