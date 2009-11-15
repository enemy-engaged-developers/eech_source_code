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
	*game_type_selection_buttons,
   *game_type_screen,
	*campaign_button,
	*ghost_campaign_button,
	*skirmish_button,
	*ghost_skirmish_button;

texture_graphic
	*game_type_screen_graphic = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_game_type_screen (ui_object *obj, void *arg);

static void game_type_button_function (ui_object *obj, void *arg);

static void notify_game_type_back_button (ui_object *obj, void *arg);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_game_type_screen (void)
{
	int
		i;

   float
		x,
		y,
      x_size,
      y_size;

	ui_object
		*option_bdrop,
		*change_obj;

   game_type_screen = create_ui_object
            (
               UI_TYPE_SCREEN,
               UI_ATTR_VIRTUAL_POSITION (0, 0),
               UI_ATTR_VIRTUAL_SIZE (1.0, 1.0),
					UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_EITHER),
					UI_ATTR_FUNCTION (notify_game_type_screen),
					UI_ATTR_COLOUR_START (255,255,255,0),
					UI_ATTR_COLOUR_END (255,255,255,255),
					UI_ATTR_OFFSET_TIME (0),
					UI_ATTR_TIME_LENGTH (500),
               UI_ATTR_END
            );

   create_ui_object
            (
               UI_TYPE_TEXT,
               UI_ATTR_PARENT (game_type_screen),
					UI_ATTR_OFFSET_TIME (0),
					UI_ATTR_TIME_LENGTH (500),
               UI_ATTR_VIRTUAL_POSITION (TITLE_TEXT_POSITION_X, TITLE_TEXT_POSITION_Y),
					UI_ATTR_VIRTUAL_SIZE (TITLE_TEXT_WIDTH, TITLE_TEXT_HEIGHT),
					UI_ATTR_TEXT (get_trans ("UI_COMBAT")),
					UI_ATTR_FONT_TYPE (UI_FONT_IMPACT_22),
					UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_BOTTOM),
               UI_ATTR_FONT_COLOUR_START (ui_screen_title_text_colour.r, ui_screen_title_text_colour.g, ui_screen_title_text_colour.b, 0),
               UI_ATTR_FONT_COLOUR_END (ui_screen_title_text_colour.r, ui_screen_title_text_colour.g, ui_screen_title_text_colour.b, 255),
					UI_ATTR_HIGHLIGHTABLE (FALSE),
					UI_ATTR_CLEAR (TRUE),
               UI_ATTR_END
            );

	//////////////////////////////////////////////
	// gametype buttons
	//////////////////////////////////////////////

	x = 0.464;
	y = 0.304;

	x_size = 0.227;
	y_size = 0.036;

	i = 0;

	option_bdrop = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (game_type_screen),
		UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
		UI_ATTR_VIRTUAL_SIZE (TEXT_OPTION_BDROP_WIDTH, TEXT_OPTION_BDROP_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_OFFSET_TIME (0),
		UI_ATTR_TIME_LENGTH (500),
		UI_ATTR_TEXTURE_GRAPHIC (text_option_bdrop),
		UI_ATTR_END
	);

	change_obj = campaign_button = create_ui_object
			(
				UI_TYPE_BUTTON,
				UI_ATTR_PARENT (game_type_screen),
// set to same position as on main screen by GCsDriver  08-12-2007
//				UI_ATTR_VIRTUAL_POSITION (x, y),
					UI_ATTR_POSITION_START (0.0, 0.329),
					UI_ATTR_POSITION_END (0.663, 0.329),
				UI_ATTR_VIRTUAL_SIZE (x_size, y_size),
				UI_ATTR_ITEM_NUMBER (GAME_TYPE_CAMPAIGN),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
				UI_ATTR_TEXT (get_trans ("Campaign")),
				UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_22),
				#if !DEMO_VERSION
				UI_ATTR_FUNCTION (game_type_button_function),
				UI_ATTR_HIGHLIGHTABLE (TRUE),
				#else
//				UI_ATTR_FONT_COLOUR (sys_col_slate_grey.r, sys_col_slate_grey.g, sys_col_slate_grey.b, sys_col_slate_grey.a),
				#endif
				UI_ATTR_CLEAR (TRUE),
            UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
            UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
            UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
            UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
				UI_ATTR_HIGHLIGHTABLE (TRUE),
				UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_EITHER),
				UI_ATTR_OFFSET_TIME (0),
				UI_ATTR_TIME_LENGTH (500),
				UI_ATTR_END
			);

	preprocess_translation_object_size (change_obj, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	set_text_option_backdrop_object (option_bdrop, change_obj);

	// ghost campaign button

	x = get_ui_object_virtual_x (change_obj);
	x_size = get_ui_object_virtual_x_size (change_obj);

	ghost_campaign_button = create_ui_object
									(
										UI_TYPE_AREA,
										UI_ATTR_PARENT (game_type_screen),
										UI_ATTR_VIRTUAL_POSITION (x, y),
										UI_ATTR_VIRTUAL_SIZE (x_size, y_size),
										UI_ATTR_CLEAR (TRUE),
										UI_ATTR_DRAWABLE (FALSE),
										UI_ATTR_END
									);

	
	x = 0.606;
	y = 0.398;

	x_size = 0.202;
	y_size = 0.036;

	i++;

	option_bdrop = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (game_type_screen),
		UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
		UI_ATTR_VIRTUAL_SIZE (TEXT_OPTION_BDROP_WIDTH, TEXT_OPTION_BDROP_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_OFFSET_TIME (0),
		UI_ATTR_TIME_LENGTH (500),
		UI_ATTR_TEXTURE_GRAPHIC (text_option_bdrop),
		UI_ATTR_END
	);

	change_obj = skirmish_button = create_ui_object
			(
				UI_TYPE_BUTTON,
				UI_ATTR_PARENT (game_type_screen),
// set to same position as on main screen by GCsDriver  08-12-2007
//				UI_ATTR_VIRTUAL_POSITION (x, y),
					UI_ATTR_POSITION_START (0, 0.435),
					UI_ATTR_POSITION_END (0.785, 0.435),
				UI_ATTR_VIRTUAL_SIZE (x_size, y_size),
				UI_ATTR_ITEM_NUMBER (GAME_TYPE_SKIRMISH),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
				UI_ATTR_TEXT (get_trans ("Skirmish")),
				UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_22),
				#if !DEMO_VERSION
				UI_ATTR_FUNCTION (game_type_button_function),
				UI_ATTR_HIGHLIGHTABLE (TRUE),
				#else
//				UI_ATTR_FONT_COLOUR (sys_col_slate_grey.r, sys_col_slate_grey.g, sys_col_slate_grey.b, sys_col_slate_grey.a),
				#endif
            UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
            UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
            UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
            UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_OFFSET_TIME (0),
				UI_ATTR_TIME_LENGTH (500),
				UI_ATTR_END
			);

	preprocess_translation_object_size (change_obj, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	set_text_option_backdrop_object (option_bdrop, change_obj);

	// ghost skirmish button

	x = get_ui_object_virtual_x (change_obj);
	x_size = get_ui_object_virtual_x_size (change_obj);

	ghost_skirmish_button = create_ui_object
									(
										UI_TYPE_AREA,
										UI_ATTR_PARENT (game_type_screen),
										UI_ATTR_VIRTUAL_POSITION (x, y),
										UI_ATTR_VIRTUAL_SIZE (x_size, y_size),
										UI_ATTR_CLEAR (TRUE),
										UI_ATTR_DRAWABLE (FALSE),
										UI_ATTR_END
									);
	
	
	x = 0.441;
	y = 0.635;

	x_size = 0.245;
	y_size = 0.036;

	i++;

	option_bdrop = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (game_type_screen),
		UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
		UI_ATTR_VIRTUAL_SIZE (TEXT_OPTION_BDROP_WIDTH, TEXT_OPTION_BDROP_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_OFFSET_TIME (0),
		UI_ATTR_TIME_LENGTH (500),
		UI_ATTR_TEXTURE_GRAPHIC (text_option_bdrop),
		UI_ATTR_END
	);

	change_obj = create_ui_object
			(
				UI_TYPE_BUTTON,
				UI_ATTR_PARENT (game_type_screen),
// set to same position as on main screen by GCsDriver  08-12-2007
//				UI_ATTR_VIRTUAL_POSITION (x, y),
					UI_ATTR_POSITION_START (0, 0.595),
					UI_ATTR_POSITION_END (0.735, 0.595),
				UI_ATTR_VIRTUAL_SIZE (x_size, y_size),
				UI_ATTR_ITEM_NUMBER (GAME_TYPE_FREE_FLIGHT),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
				UI_ATTR_TEXT (get_trans ("Free Flight")),
				UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_22),
				UI_ATTR_FUNCTION (game_type_button_function),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_EITHER),
            UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
            UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
            UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
            UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
				UI_ATTR_HIGHLIGHTABLE (TRUE),
				UI_ATTR_OFFSET_TIME (0),
				UI_ATTR_TIME_LENGTH (500),
				UI_ATTR_END
			);

	preprocess_translation_object_size (change_obj, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	set_text_option_backdrop_object (option_bdrop, change_obj);

	
	x = 0.588;
	y = 0.738;

	x_size = 0.133;
	y_size = 0.036;

	i++;

	option_bdrop = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (game_type_screen),
		UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
		UI_ATTR_VIRTUAL_SIZE (TEXT_OPTION_BDROP_WIDTH, TEXT_OPTION_BDROP_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_OFFSET_TIME (0),
		UI_ATTR_TIME_LENGTH (500),
		UI_ATTR_TEXTURE_GRAPHIC (text_option_bdrop),
		UI_ATTR_END
	);

	change_obj = game_type_selection_buttons = create_ui_object
			(
				UI_TYPE_BUTTON,
				UI_ATTR_PARENT (game_type_screen),
// set to same position as on main screen by GCsDriver  08-12-2007
//				UI_ATTR_VIRTUAL_POSITION (x, y),
					UI_ATTR_POSITION_START (0, 0.704),
					UI_ATTR_POSITION_END (0.637, 0.704),
				UI_ATTR_VIRTUAL_SIZE (x_size, y_size),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
				UI_ATTR_ITEM_NUMBER (GAME_TYPE_DEMO),
				UI_ATTR_TEXT (get_trans ("Demo")),
				UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_22),
				UI_ATTR_FUNCTION (game_type_button_function),
            UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
            UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
            UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
            UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
				UI_ATTR_HIGHLIGHTABLE (TRUE),
				UI_ATTR_OFFSET_TIME (0),
				UI_ATTR_TIME_LENGTH (500),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_EITHER),
				UI_ATTR_END
			);

	preprocess_translation_object_size (change_obj, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	set_text_option_backdrop_object (option_bdrop, change_obj);


	/////////////////////////////////////////////////////////////////
	// Cancel Button

	option_bdrop = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (game_type_screen),
		UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
		UI_ATTR_VIRTUAL_SIZE (TEXT_OPTION_BDROP_WIDTH, TEXT_OPTION_BDROP_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_OFFSET_TIME (0),
		UI_ATTR_TIME_LENGTH (500),
		UI_ATTR_TEXTURE_GRAPHIC (text_option_bdrop),
		UI_ATTR_END
	);

	change_obj = create_ui_object
			(
				UI_TYPE_BUTTON,
				UI_ATTR_PARENT (game_type_screen),
				UI_ATTR_VIRTUAL_POSITION (OPTIONS_CANCEL_BUTTON_POS_X, OPTIONS_CANCEL_BUTTON_POS_Y),
				UI_ATTR_VIRTUAL_SIZE (OPTIONS_CANCEL_BUTTON_X, OPTIONS_CANCEL_BUTTON_Y),
				UI_ATTR_TEXT (get_trans("UI_CANCEL")),
				UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
				UI_ATTR_FUNCTION (notify_game_type_back_button),
				UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
				UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
            UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
            UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
            UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
            UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
				UI_ATTR_OFFSET_TIME (0),
				UI_ATTR_TIME_LENGTH (500),
				UI_ATTR_HIGHLIGHTABLE (TRUE),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);
			
	set_text_option_backdrop_object (option_bdrop, change_obj);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_game_type_screen (ui_object *obj, void *arg)
{

	if ( get_ui_object_drawable ( obj ) )
	{

		blit_front_buffer_to_render_buffer ();
	
		set_radio_buttons_off (game_type_selection_buttons);
	
		game_type_hilight_selection (NULL);
	
		process_game_initialisation_phases ();

		if ( game_type_screen_graphic )
		{
	
			destroy_texture_graphic ( game_type_screen_graphic );

			game_type_screen_graphic = NULL;
		}
	
		game_type_screen_graphic = create_texture_graphic ( "graphics\\ui\\cohokum\\combat.psd" );
	
		set_ui_object_texture_graphic ( game_type_screen, game_type_screen_graphic );

		reset_time_values ( game_type_screen );
	}
	else
	{

		if ( game_type_screen_graphic )
		{
	
			destroy_texture_graphic ( game_type_screen_graphic );

			game_type_screen_graphic = NULL;
		}
	}

	#if DEMO_VERSION
	
		set_ui_object_highlightable (campaign_button, FALSE);

		set_ui_object_font_colour_end (campaign_button, ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 127);

		set_ui_object_drawable (ghost_campaign_button, TRUE);

		set_ui_object_highlightable (skirmish_button, FALSE);

		set_ui_object_font_colour_end (skirmish_button, ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 127);

		set_ui_object_drawable (ghost_skirmish_button, TRUE);

	#endif

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void game_type_button_function (ui_object *obj, void *arg)
{

	set_game_type ((game_types) get_ui_object_item_number (obj));

	process_game_initialisation_phases ();

	#if DEBUG_MODULE

	debug_log ("GMTY_FN: game type %d", get_game_type ());

	#endif

//	game_type_hilight_selection (obj);

	if ((int) arg == BUTTON_STATE_UP)
	{
		
		switch (get_game_type ())
		{

			case GAME_TYPE_DEMO:
			{
	
				int
					filter,
					count,
					index,
					warzone;
	
				session_list_data_type
					*session;
	
				ui_object
					*item;
		
				//
				// If we're in demo mode, hack it in!
				//
	
				//session_filter = SESSION_LIST_TYPE_HOST;
				
				// 16DEC05 Casm Fix for Demo mode selection
				filter = command_line_session_filter;
				command_line_session_filter = 0;

				initialise_session_list ();

				session_list_rescan_function (NULL, NULL);
			
				session_update_session_list ();

				// 16DEC05 Casm Fix for Demo mode selection
				command_line_session_filter = filter;
		
				session = session_list_head;
		
				item = get_ui_object_child (session_list);
		
				set_global_gunship_side (ENTITY_SIDE_BLUE_FORCE);
	
				set_global_gunship_type (NUM_GUNSHIP_TYPES);
		
				if ((session) && (item))
				{
		
					//
					// Pick random host session
					//

					count = 0;

					while (session)
					{
						if (session->type == SESSION_LIST_TYPE_HOST)
						{
							count ++;
						}

				      session = session->next;
				   }

					if (count > 0)
					{		
						index = rand16 () % count;

						count = 0;

						warzone = 1;

						session = session_list_head;
		
						while (session)
						{
							if (session->type == SESSION_LIST_TYPE_HOST)
							{
								if (count == index)
								{
									break;
								}

								count ++;
							}

							warzone ++;
		
					      session = session->next;
					   }
		
						ASSERT (session);

						debug_log ("SESS_FN: demo mode selecting warzone %d", warzone);

						//
						// Load up the sound effects for all sides
						//
					
						load_side_dependant_application_sound_samples ( NUM_ENTITY_SIDES );
		
						push_ui_screen (loading_screen);
					
						session_list_function (item, ( void * ) warzone);
					}
				}

				break;
			}

			default:
			{
	
				push_ui_screen (session_screen);

				break;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_game_type_back_button (ui_object *obj, void *arg)
{

	if ((int) arg == BUTTON_STATE_DOWN)
	{

		set_ui_object_graphic (obj, (unsigned short int *) get_graphics_file_data (GRAPHICS_UI_APACHE_PLANNER_BACK_BUTTON_SELECTED));

		set_ui_object_redraw (game_type_screen, TRUE);
	}
	else if ((int) arg == BUTTON_STATE_UP)
	{
	
		set_ui_object_graphic (obj, (unsigned short int *) get_graphics_file_data (GRAPHICS_UI_APACHE_PLANNER_BACK_BUTTON_UNSELECTED));
	
		pop_ui_screen (SCREEN_POP_ACTUAL);
	}
	else
	{

		set_ui_object_graphic (obj, (unsigned short int *) get_graphics_file_data (GRAPHICS_UI_APACHE_PLANNER_BACK_BUTTON_UNSELECTED));
	
		set_ui_object_redraw (game_type_screen, TRUE);
	}

	//set_ui_object_graphic_type (obj, UI_OBJECT_ALPHA_GRAPHIC);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void game_type_hilight_selection (ui_object *choice)
{

	ui_object
		*next;

	next = get_ui_object_child (game_type_screen);

	while (next)
	{

		set_ui_object_highlighted (next, FALSE);

		if (next->type == UI_TYPE_RADIO)
		{

			set_ui_object_font_colour (next, default_unselected_text_colour.r, default_unselected_text_colour.g, default_unselected_text_colour.b, default_unselected_text_colour.a);
		}
	
		next = get_ui_object_next (next);
	}

	if (choice)
	{

		set_ui_object_font_colour (choice, default_selected_text_colour.r, default_selected_text_colour.g, default_selected_text_colour.b, default_selected_text_colour.a);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
