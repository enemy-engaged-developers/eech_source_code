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

#include "uisession.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	campaign_selection;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void build_session_list (void);

static void rename_session (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_session_screen (ui_object *obj, void *arg)
{

	if ( get_ui_object_drawable ( obj ) )
	{

		//session_filter = SESSION_LIST_TYPE_HOST | SESSION_LIST_TYPE_JOIN | SESSION_LIST_TYPE_RESTORE;
	
		initialise_session_list ();
	
		//
		// destroy session info list
		//
	
		ui_object_destroy_list_items (session_list);

		ui_object_destroy_list_items (session_info_list);

		set_ui_list_spacing_proportional_to_font (session_info_list, -0.2);

		#if DEBUG_MODULE
	
		debug_log ("SESS_FN: opening pack buffer");
	
		#endif
		
		set_current_game_session_invalid ();
	
		//
		// We're not in demo mode - set the session list
		//
	
		process_game_initialisation_phases ();

		ui_set_user_function (session_update_session_list);
	
//		set_ui_object_drawable ( session_game_delete_button, FALSE );
	
//		set_ui_object_drawable ( session_screen_session_parameters_button, FALSE );

		//
		// Setup the screen
		//

		blit_front_buffer_to_render_buffer ();
	
		if ( session_screen_graphic )
		{
	
			destroy_texture_graphic ( session_screen_graphic );

			session_screen_graphic = NULL;
		}
	
		session_screen_graphic = create_texture_graphic ( "graphics\\ui\\cohokum\\combat.psd" );
	
		set_ui_object_texture_graphic ( session_screen, session_screen_graphic );
	
		reset_time_values ( session_screen );

		notify_clear_all_session_parameters ();
	}
	else
	{

		if ( session_screen_graphic )
		{
	
			destroy_texture_graphic ( session_screen_graphic );

			session_screen_graphic = NULL;
		}
	}

	set_ui_object_drawable (session_screen_delete_button, FALSE);

	set_ui_object_drawable (session_screen_rename_button, FALSE);
	
	{

		ui_object
			*slider;

		slider = get_ui_object_vslider (session_list_area);

		set_ui_object_vslider_virtual_position (slider, 0.0);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_session_back_button (ui_object *obj, void *arg)
{

	if ((int) arg == BUTTON_STATE_DOWN)
	{

		set_ui_object_graphic (obj, (unsigned short int *) get_graphics_file_data (GRAPHICS_UI_APACHE_PLANNER_BACK_BUTTON_SELECTED));

		set_ui_object_redraw (session_screen, TRUE);
	}
	else if ((int) arg == BUTTON_STATE_UP)
	{
	
		set_ui_object_graphic (obj, (unsigned short int *) get_graphics_file_data (GRAPHICS_UI_APACHE_PLANNER_BACK_BUTTON_UNSELECTED));

		leave_mission ();
	
		ui_set_user_function (NULL);
	
		#if DEBUG_MODULE
	
		debug_log ("SESS_FN: closing pack buffer");
		
		#endif
	
		set_game_initialisation_phase (GAME_INITIALISATION_PHASE_GAME_TYPE);
		
		game_type_hilight_selection (NULL);
	
		pop_ui_screen (SCREEN_POP_ACTUAL);
	}
	else
	{

		set_ui_object_graphic (obj, (unsigned short int *) get_graphics_file_data (GRAPHICS_UI_APACHE_PLANNER_BACK_BUTTON_UNSELECTED));
	
		set_ui_object_redraw (session_screen, TRUE);
	}
	
	set_ui_object_graphic_type (obj, UI_OBJECT_ALPHA_GRAPHIC);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_session_next_button (ui_object *obj, void *arg)
{

	if ((int) arg == BUTTON_STATE_DOWN)
	{

		set_ui_object_graphic (obj, (unsigned short int *) get_graphics_file_data (GRAPHICS_UI_APACHE_PLANNER_FORWARD_BUTTON_SELECTED));

		set_ui_object_redraw (session_screen, TRUE);
	}
	else if ((int) arg == BUTTON_STATE_UP)
	{

		set_ui_object_graphic (obj, (unsigned short int *) get_graphics_file_data (GRAPHICS_UI_APACHE_PLANNER_FORWARD_BUTTON_UNSELECTED));

		if (get_valid_current_game_session ())
		{
	
			//
			// reset delta time to keep mobile creation happy in faction.c (and everything else)
			//
	
			if (get_comms_model () == COMMS_MODEL_CLIENT)
			{

				game_initialisation_phase = GAME_INITIALISATION_PHASE_SETUP;
			}

			switch (get_game_type ())
			{
				case GAME_TYPE_SKIRMISH:
				case GAME_TYPE_CAMPAIGN:
				case GAME_TYPE_FREE_FLIGHT:
				{
				
					save_global_options_data ();
	
					push_ui_screen (gunships_screen);

					break;
				}
				case GAME_TYPE_DEMO:
				{

					// dont think demo gets here... check.

					push_ui_screen (loading_screen);

					break;
				}
			}
		}
	}
	else 
	{

		set_ui_object_graphic (obj, (unsigned short int *) get_graphics_file_data (GRAPHICS_UI_APACHE_PLANNER_FORWARD_BUTTON_UNSELECTED));

		set_ui_object_redraw (session_screen, TRUE);
	}

	set_ui_object_graphic_type (obj, UI_OBJECT_ALPHA_GRAPHIC);
}

// Jabberwock 031118 Server side settings
				

void notify_session_continue_button (ui_object *obj, void *arg)
{
	if ((int) arg == BUTTON_STATE_DOWN)
	{

		set_ui_object_graphic (obj, (unsigned short int *) get_graphics_file_data (GRAPHICS_UI_APACHE_PLANNER_FORWARD_BUTTON_SELECTED));

		set_ui_object_redraw (session_screen, TRUE);
	}
	else if ((int) arg == BUTTON_STATE_UP)
	{

		set_ui_object_graphic (obj, (unsigned short int *) get_graphics_file_data (GRAPHICS_UI_APACHE_PLANNER_FORWARD_BUTTON_UNSELECTED));

		//if (get_valid_current_game_session ())
		{
			if (get_comms_model () == COMMS_MODEL_CLIENT)
			{
				send_packet (get_server_id (), PACKET_TYPE_SETTINGS_REQUEST, NULL, 0, SEND_TYPE_PERSONAL);
				
			}
		}
	}
	else 
	{

		set_ui_object_graphic (obj, (unsigned short int *) get_graphics_file_data (GRAPHICS_UI_APACHE_PLANNER_FORWARD_BUTTON_UNSELECTED));

		set_ui_object_redraw (session_screen, TRUE);
	}

	set_ui_object_graphic_type (obj, UI_OBJECT_ALPHA_GRAPHIC);
}

// Jabberwock 031118 ends

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void session_list_function (ui_object *obj, void *arg)
{

   session_list_data_type
      *current_session_list;

	int selection;
	//int num_sessions; // Jabberwock 031210 Session filter

	if (obj->type == UI_TYPE_LIST_BOX)
	{

		return;
	}

	//
	// destroy session list ready for next time.
	// Otherwise one item will be selected if you pop to this screen
	//

	set_ui_object_redraw (session_screen, TRUE);

	//
   // release the current session
	//

   leave_mission ();

	//
   // find the session selected
	//

   campaign_selection = (int) arg;

   current_session_list = get_session_list ();

	if (!current_session_list)
	{

		return;
	}

   selection = campaign_selection;

   while (selection > 1)
   {

		if (!current_session_list)
		{

			return;
		}

		selection --;

      current_session_list = current_session_list->next;
   }

	session_child_head = current_session_list;

	set_random_number_seed (campaign_selection);

	//
   // process session selected
	//

	// set session restore function buttons to off

	set_ui_object_drawable (session_screen_delete_button, FALSE);

	set_ui_object_drawable (session_screen_rename_button, FALSE);

   switch (current_session_list->type)
   {

      case SESSION_LIST_TYPE_INVALID:
		{

			debug_fatal ("session invalid");

			break;
		}

      case SESSION_LIST_TYPE_RESTORE:
      {
			#if DEBUG_MODULE

			debug_log ("session restore");

			#endif

			// show delete & rename buttons, hide session parameters

			set_ui_object_drawable (session_screen_delete_button, TRUE);

			set_ui_object_drawable (session_screen_rename_button, TRUE);

			//
         // load session
         // intentional follow through..
			//
      }

      case SESSION_LIST_TYPE_HOST:
      {

			//
         // host a session
			//

			#if DEBUG_MODULE

			debug_log ("SESSION: hosting");

			#endif

            set_comms_model (COMMS_MODEL_SERVER);
				
			set_current_game_session (current_session_list);

			ui_object_destroy_list_items (session_info_list);

			set_game_initialisation_phase (GAME_INITIALISATION_PHASE_SCENARIO);

			process_game_initialisation_phases ();

			//set_game_initialisation_phase (GAME_INITIALISATION_PHASE_SETUP);

			//process_game_initialisation_phases ();
			
			break;
		}

      case SESSION_LIST_TYPE_JOIN:
      {

			#if DEBUG_MODULE

			debug_log ("SESSION: joining");

			#endif

			set_comms_model (COMMS_MODEL_CLIENT);

			set_current_game_session (current_session_list); // debug, should join actual session..

			ui_set_user_function (update_ui_comms);

			ui_object_destroy_list_items (session_info_list); // Jabberwock 031118 MP bug - reload list

			set_game_initialisation_phase (GAME_INITIALISATION_PHASE_SCENARIO); // Jabberwock 031118 MP bug - reload list

			process_game_initialisation_phases ();

         break;
      }

      case SESSION_LIST_TYPE_MASTER:
      {
			debug_log ("JOININET: Setting ip to %s ...", current_session_list->ip_address);
			//Set the IP, as if we would enter it in the options screen
			sprintf(global_options.ip_address, current_session_list->ip_address);

// Jabberwock 031126 - Empty box fix

			set_direct_play_inet_address (current_session_list->ip_address);
			
			set_comms_model (COMMS_MODEL_CLIENT);
			
			session_list_rescan_function (NULL, NULL); //Jabberwock
			
			ui_set_user_function (session_update_session_list);

			break;

/*

			global_options.ip_address[127] = '\0';

			debug_log ("JOININET: reinitializing dplay...");

			//Re-Activate DirectPlay
			if (!get_current_game_session ())
			{
				initialise_service_provider_connection ();
			}

			debug_log ("JOININET: flushing session list...");
//			initialise_session_list();
			current_session_list = NULL;
			
			//bail out if we don't find any sessions
			num_sessions = direct_play_enumerate_sessions();
			debug_log ("JOININET: Sessions found: %i", num_sessions);

			if (num_sessions <= 0)
			  break;
			
			debug_log ("JOININET: getting first session on server...");
			get_first_multi_session(&current_session_list);

			if (!current_session_list)
			{
			  debug_log ("JOININET: current_session_list is still NULL!");
			  break;
			}
			
//			debug_log ("JOININET: resetting current session type...");
//			current_session_list->type = SESSION_LIST_TYPE_JOIN;

//			debug_log ("JOININET: setting list = list->next ...");
//			current_session_list = current_session_list->next;

			debug_log ("JOININET: setting head = current ...");
			session_child_head = current_session_list;

			debug_log ("JOININET: setting comms model...");
			set_comms_model (COMMS_MODEL_CLIENT);

			debug_log ("JOININET: setting current session...");
			set_current_game_session (current_session_list); // debug, should join actual session..

			debug_log ("JOININET: update ui comms...");
			ui_set_user_function (update_ui_comms);

			debug_log ("JOININET: processing game initialisation phases...");
			process_game_initialisation_phases ();

			debug_log ("JOININET: Done!");
			
         break;*/
      }
      
      case SESSION_LIST_TYPE_FILTER:
	  {
	  		if (strcmp(session_filter_value, "root") == 0)
			{
				sprintf (session_filter_value, "%s", current_session_list->data_path);
			}
			else
			{
				sprintf (session_filter_value, "%s", "root");
			}
	  		
	  		ui_object_destroy_list_items (session_info_list);
	  		
	  		session_list_rescan_function (NULL, NULL); //Jabberwock

	  		break;
	  }

      default:
      {

         debug_fatal ("ERROR: session_list_function, unknown session_type %d", current_session_list->type);
      }
   }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void session_update_session_list (void)
{

	int
		game_update_time;

	static int
		update_ticks = 0;

	if (!get_pack_buffer ())
	{

		open_pack_buffer (tx_pack_buffer, command_line_comms_pack_buffer_size);
	}

	game_update_time = TIME_2_SECOND;

	if (update_ticks < get_system_time ())
	{

		#if DEBUG_MODULE

		debug_log ("SESSION: update session list");

		#endif

		data_exchange ();

		session_list_rescan_function (NULL, NULL);

		num_multiplayer_refreshes++;

		update_ticks = get_system_time () + game_update_time;

		set_delta_time ();

		set_ui_object_redraw (session_screen, TRUE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void session_list_rescan_function (ui_object *obj, void *arg)
{

	session_list_data_type
		*new_session,
		*new_session_list;

	ui_object
		*selected_obj;

	int
		re_highlight_flag;

	char
		text [64];

	//
	// store title of current selected session to allow us to re-highlight after build
	//

	re_highlight_flag = FALSE;

	selected_obj = get_ui_object_child (session_list);

	while (selected_obj)
	{

		if (get_ui_object_state (selected_obj) == UI_OBJECT_STATE_ON)
		{

			re_highlight_flag = TRUE;

			strncpy (text, get_ui_object_text (selected_obj), 63);

			break;
		}

		selected_obj = get_ui_object_next (selected_obj);
	}

	//
	// list all sessions
	// Generate new session list, find current_game_session, set current_game_session ptr up
	// destory old list.
	//

	new_session_list = NULL;

	if (session_filter [get_game_type ()] & SESSION_LIST_TYPE_HOST)
	{

		update_mouse_pointer ();

		compile_single_session_list (&new_session_list);
	}
	
	if (session_filter [get_game_type ()] & SESSION_LIST_TYPE_JOIN)
	{

		update_mouse_pointer ();

		set_mouse_graphic_off ();

		compile_multi_session_list (&new_session_list);

		set_mouse_graphic_on ();
	}

// Jabberwock 031118 MP bug - "No Games" bug
	
	if (session_filter [get_game_type ()] & SESSION_LIST_TYPE_MASTER)
	{

		update_mouse_pointer ();

		set_mouse_graphic_off ();

		compile_multi_session_list (&new_session_list);

		set_mouse_graphic_on ();
	}
	
// Jabberwock 031118 MP bug ends
/*
// Jabberwock 031210 Session filter 

	if (session_filter [get_game_type ()] & SESSION_LIST_TYPE_FILTER)
	{

		update_mouse_pointer ();

		set_mouse_graphic_off ();

		compile_single_session_list (&new_session_list);

		set_mouse_graphic_on ();
	}*/

// Jabberwock 031210 ends

	if (session_filter [get_game_type ()] & SESSION_LIST_TYPE_RESTORE)
	{

		update_mouse_pointer ();

		compile_restore_session_list (&new_session_list);
	}

	if (get_valid_current_game_session ())
	{

		// find new current_game_session
	
		new_session = new_session_list;
	
		while (new_session)
		{
	
			if (strcmp (new_session->title, current_game_session->title) == 0)
			{
	
				set_current_game_session (new_session);

				session_child_head = new_session;
	
				break;
			}
	
			new_session = new_session->next;
		}

		if (!get_current_game_session ())
		{
	
			debug_log ("SESS_FN: session on longer exists");
		}
	}

	// destroy old list

	destroy_session_list (&session_list_head);

	// reassign list

	session_list_head = new_session_list;

	//
	// Re-highlight selected object
	//

	build_session_list ();

	if (re_highlight_flag)
	{

		selected_obj = get_ui_object_child (session_list);

		while (selected_obj)
		{

			if (strncmp (text, get_ui_object_text (selected_obj), 63) == 0)
			{

				set_ui_object_state (selected_obj, UI_OBJECT_STATE_ON);

				break;
			}
			
			selected_obj = get_ui_object_next (selected_obj);
		}
	}

	// debug
	/*
	{

		static int
			count = 0;

		char
			buffer [32];

		sprintf (buffer, "test %d", count ++);

		add_to_pop_up_list (buffer, slider_test_list, NULL, 0, UI_FONT_ARIAL_18, &ui_colour_white);
	}
	*/
	// debug
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void build_session_list (void)
{
	rgb_colour
		col;

	ui_object
		*list_item;

	session_list_data_type
		*list;

	ui_object_destroy_list_items (session_list);

	list = get_session_list ();

	if (list)
	{
	
		while (list)
		{
	
			#if DEBUG_MODULE
	
			debug_log ("SESSION: list item %s", list->title);
	
			#endif

			if (list->type == SESSION_LIST_TYPE_HOST)
			{
				list_item = add_to_pop_up_list (list->displayed_title, session_list, NULL, list->list_id, UI_FONT_ARIAL_16, ui_list_text_default_colour);

				set_ui_frontend_list_object_highlightable (list_item);
			}
			else if (list->type == SESSION_LIST_TYPE_MASTER)
			{
				col.r = 240;
				col.g = 73;
				col.b = 89;
				col.a = 255;

				list_item = add_to_pop_up_list (list->displayed_title, session_list, NULL, list->list_id, UI_FONT_ARIAL_16, col);

				set_ui_frontend_list_object_highlightable (list_item);
			}
			else if (list->type == SESSION_LIST_TYPE_JOIN)
			{
				col.r = 73;
				col.g = 240;
				col.b = 89;
				col.a = 255;

				list_item = add_to_pop_up_list (list->displayed_title, session_list, NULL, list->list_id, UI_FONT_ARIAL_16, col);

				set_ui_frontend_list_object_highlightable (list_item);
			}
			else if (list->type == SESSION_LIST_TYPE_RESTORE)
			{
				col.r = 112;
				col.g = 210;
				col.b = 255;
				col.a = 255;

				list_item = add_to_pop_up_list (list->displayed_title, session_list, NULL, list->list_id, UI_FONT_ARIAL_16, col);

				set_ui_frontend_list_object_highlightable (list_item);
			}
			// Jabberwock 031210 Session filter
			else if (list->type == SESSION_LIST_TYPE_FILTER)
			{
				col.r = 220;
				col.g = 220;
				col.b = 220;
				col.a = 255;
					
				list_item = add_to_pop_up_list (list->displayed_title, session_list, NULL, list->list_id, UI_FONT_ARIAL_16, col);

				set_ui_frontend_list_object_highlightable (list_item);
			}			
			// Jabberwock 031210 ends


			list = list->next;
		}
	}
	else
	{
	
		add_to_pop_up_list ( get_trans ("No Games"), session_list, NULL, 0, UI_FONT_ARIAL_16, ui_colour_red );
	}
	/*
	{

		ui_object
			*slider;

		slider = get_ui_object_vslider (session_list_area);

		recalculate_slider_size (slider);
	}
	*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rename_session (void)
{
	unsigned char
		*ptr,
		old_name [1024],
		filename [1024],
		new_name [1024];

	ui_object
		*list_item;

	session_list_data_type
		*session;

	session = get_current_game_session ();

	list_item = get_ui_object_child (session_list);

	while ((list_item) && (get_ui_object_state (list_item) != UI_OBJECT_STATE_ON))
	{
		list_item = get_ui_object_next (list_item);
	}

	ASSERT (list_item);

	//
	// rename the 'sav' file
	//

	sprintf (filename, "%s\\%s\\%s", session->data_path, session->campaign_directory, session->campaign_filename);

	strcpy (old_name, filename);

	strcpy (new_name, get_ui_object_text (list_item));

	strcat (new_name, ".");

	strcat (new_name, game_type_extensions [get_game_type ()]);

	strcpy (session->campaign_filename, new_name);

	sprintf (new_name, "%s\\%s\\%s", session->data_path, session->campaign_directory, session->campaign_filename);

	#if DEBUG_MODULE

	debug_log ( "Renaming game %s to %s", filename, new_name);

	#endif

	rename (filename, new_name);

	// find last occurance of '.' in the old filename
	ptr = strrchr (old_name, '.');

	ASSERT (ptr);

	if (ptr)
	{
		*ptr++ = '.';
		*ptr++ = 'S';
		*ptr++ = 'A';
		*ptr++ = 'V';

		if (file_exist (old_name))
		{
			ptr = strrchr (new_name, '.');

			*ptr++ = '.';
			*ptr++ = 'S';
			*ptr++ = 'A';
			*ptr++ = 'V';

			#if DEBUG_MODULE

			debug_log ( "Renaming game2 %s to %s", old_name, new_name);

			#endif

			rename (old_name, new_name);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void session_name_input_function ( ui_object *obj, void *arg )
{
  	unsigned char
		limited_name [34],
		*text;

	ui_object
		*object;

	text = get_ui_object_text (obj);

	object = (ui_object *) get_ui_object_item_number (obj);

	if ((text) && (strlen (text) > 0))
	{
		parse_filename (text, 30);

		strcpy (limited_name, text);

		set_ui_object_text (object, limited_name);
	
		set_ui_object_drawable (object, TRUE);
	}

	set_ui_object_drawable (session_name_entry_area, FALSE);

	rename_session ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_session_rename_button ( ui_object *obj, void *arg )
{
	float
		x,
		y;

	ui_object
		*list_item;

	session_list_data_type
		*session;

	session = get_current_game_session ();

	if (session)
	{
		if (session->type == SESSION_LIST_TYPE_RESTORE)
		{
			// get correct session ui object in list

			list_item = get_ui_object_child (session_list);

			while ((list_item) && (get_ui_object_state (list_item) != UI_OBJECT_STATE_ON))
			{
				list_item = get_ui_object_next (list_item);
			}

			ASSERT (list_item);

			// move input object to correct position
		
			x = get_ui_object_virtual_x (list_item);

			y = get_ui_object_virtual_y (list_item);

			set_ui_object_virtual_x (session_name_input, x);
	
			set_ui_object_virtual_y (session_name_input, y);

			// switch input on
	
			set_ui_object_item_number (session_name_input, (int) list_item);
	
			set_ui_object_drawable (list_item, FALSE);
	
			set_ui_object_drawable (session_name_entry_area, TRUE);
	
			set_ui_object_state (session_name_input, UI_OBJECT_STATE_ON);
		}
	}	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_session_delete_button ( ui_object *obj, void *arg )
{

	session_list_data_type
		*session;

	char
		filename[1024];

	session = get_current_game_session ();

	if ( session )
	{

		if ( session->type == SESSION_LIST_TYPE_RESTORE )
		{

			char
				*ptr;

			sprintf ( filename, "%s\\%s\\%s", session->data_path, session->campaign_directory, session->campaign_filename );

			unlink ( filename );

			//
			// Delete the 'sav' file as well
			//

			debug_log ( "Deleting game %s", filename );

			// find last occurance of '.' in the filename
			ptr = strrchr (filename, '.');

			ASSERT (ptr);

			if (ptr)
			{
				*ptr++ = '.';
				*ptr++ = 'S';
				*ptr++ = 'A';
				*ptr++ = 'V';
	
				if ( file_exist ( filename ) )
				{
					debug_log ( "Deleting game2 %s", filename );
	
					unlink ( filename );
				}
			}
			
			ui_object_destroy_list_items (session_info_list);

			session_list_rescan_function ( NULL, NULL );
		}
	}
	// turn off delete and rename buttons as nothing is left selected

	set_ui_object_drawable (session_screen_delete_button, FALSE);

	set_ui_object_drawable (session_screen_rename_button, FALSE);

	set_current_game_session (NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_session_apache_briefing_button ( ui_object *obj, void *arg )
{

	set_briefing_side ( FALSE );

	push_ui_screen ( combat_zone_screen );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_session_havoc_briefing_button ( ui_object *obj, void *arg )
{

	set_briefing_side ( TRUE );

	push_ui_screen ( combat_zone_screen );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
