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

#define DEBUG_MODULE 0

#define INGAME_SOUND_OPTIONS	1

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ui_object
	*options_screen,
	*options_page [NUM_OPTIONS_PAGES],
	*options_page_buttons [NUM_OPTIONS_PAGES];

texture_graphic
	*options_screen_graphic = NULL;

static int
	current_options_page = OPTIONS_PAGE_GRAPHICS;

display_device
	*old_graphics_card_selection;

int
	old_graphics_card_automatic_selection;
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_options_screen (ui_object *obj, void *arg)
{

	if ( get_ui_object_drawable ( obj ) )
	{
		
		//
		// Setup screen graphics
		//
	
		blit_front_buffer_to_render_buffer ();
	
		if (options_screen_graphic)
		{
		
			destroy_texture_graphic (options_screen_graphic);
	
			options_screen_graphic = NULL;
		}
		
		options_screen_graphic = create_texture_graphic ("graphics\\ui\\cohokum\\setup.psd");
		
		set_ui_object_texture_graphic (options_screen, options_screen_graphic);
		
//		reset_time_values (options_screen);

		// if called from within game - hide certain options
		if (get_current_game_session())
		{
			set_ui_object_highlightable (options_page_buttons[OPTIONS_PAGE_MULTIPLAYER], FALSE);

			set_ui_object_font_colour_end (options_page_buttons[OPTIONS_PAGE_MULTIPLAYER], ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 127);

			set_ui_object_drawable (ghost_multiplayer_option_button, TRUE);

			if (current_options_page == OPTIONS_PAGE_MULTIPLAYER)
			{
				current_options_page = OPTIONS_PAGE_GRAPHICS;
			}

			#if INGAME_SOUND_OPTIONS
			
			set_ui_object_drawable (options_page_buttons[OPTIONS_PAGE_SOUND], FALSE);

			set_ui_object_drawable (options_page_buttons[OPTIONS_PAGE_INGAME_SOUND], TRUE);

			if (current_options_page == OPTIONS_PAGE_SOUND)
			{
				current_options_page = OPTIONS_PAGE_INGAME_SOUND;
			}

			#else

			set_ui_object_drawable (options_page_buttons[OPTIONS_PAGE_INGAME_SOUND], FALSE);

			set_ui_object_highlightable (options_page_buttons[OPTIONS_PAGE_SOUND], FALSE);

			set_ui_object_font_colour_end (options_page_buttons[OPTIONS_PAGE_SOUND], ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 127);

			set_ui_object_drawable (ghost_sound_option_button, TRUE);

			if (current_options_page == OPTIONS_PAGE_SOUND)
			{
				current_options_page = OPTIONS_PAGE_GRAPHICS;
			}

			#endif
		}
		else
		{
			set_ui_object_highlightable (options_page_buttons[OPTIONS_PAGE_MULTIPLAYER], TRUE);
			
			set_ui_object_font_colour_end (options_page_buttons[OPTIONS_PAGE_MULTIPLAYER], ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255);

			set_ui_object_drawable (ghost_multiplayer_option_button, FALSE);

			#if INGAME_SOUND_OPTIONS

			set_ui_object_drawable (options_page_buttons[OPTIONS_PAGE_SOUND], TRUE);

			set_ui_object_drawable (options_page_buttons[OPTIONS_PAGE_INGAME_SOUND], FALSE);

			if (current_options_page == OPTIONS_PAGE_INGAME_SOUND)
			{
				current_options_page = OPTIONS_PAGE_SOUND;
			}

			#else

			set_ui_object_drawable (options_page_buttons[OPTIONS_PAGE_INGAME_SOUND], FALSE);

			set_ui_object_highlightable (options_page_buttons[OPTIONS_PAGE_SOUND], TRUE);
			
			set_ui_object_font_colour_end (options_page_buttons[OPTIONS_PAGE_SOUND], ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255);

			set_ui_object_drawable (ghost_sound_option_button, FALSE);

			#endif
		}

		#if DEMO_VERSION

		set_ui_object_highlightable (options_page_buttons[OPTIONS_PAGE_MULTIPLAYER], FALSE);

		set_ui_object_font_colour_end (options_page_buttons[OPTIONS_PAGE_MULTIPLAYER], ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 127);

		set_ui_object_drawable (ghost_multiplayer_option_button, TRUE);

		#endif

		//initialise the joystick devices

		initialise_joystick_selection ();

		//call most recently entered options page
		
		notify_options_page (current_options_page);

		// get pointer to current graphics card

		old_graphics_card_selection = get_card_selection_device ();

		old_graphics_card_automatic_selection = get_global_graphics_device_selection_automatic ();
	}
	else
	{

		if (options_screen_graphic)
		{
	
			destroy_texture_graphic (options_screen_graphic);

			options_screen_graphic = NULL;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void display_options_page (options_pages page)
{
	int
		loop;
		
	//set drawable state of pages depending on chosen page & hilite appropriate button
	
	for (loop = 0; loop < NUM_OPTIONS_PAGES; loop ++)
	{
		set_ui_object_drawable (options_page [loop], FALSE);

		if (page == loop)
		{
			set_ui_object_state (options_page_buttons [loop], UI_OBJECT_STATE_ON);

			reset_time_values (options_page[loop]);

			current_options_page = loop;

			set_ui_object_drawable (options_page [loop], TRUE);

		}
		else
		{	
			set_ui_object_state (options_page_buttons [loop], UI_OBJECT_STATE_OFF);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_options_page (options_pages page)
{
	switch (page)
	{
		case OPTIONS_PAGE_CONTROLLER:
		{
			notify_show_controller_page ();

			break;
		}
		case OPTIONS_PAGE_DYNAMICS:
		{
			notify_show_dynamics_page ();

			break;
		}
		case OPTIONS_PAGE_GRAPHICS:
		{
			notify_show_graphics_page ();

			break;
		}
		case OPTIONS_PAGE_REALISM:
		{
			notify_show_realism_page ();

			break;
		}
		case OPTIONS_PAGE_SOUND:
		{
			notify_show_sound_page ();

			break;
		}
		case OPTIONS_PAGE_INGAME_SOUND:
		{
			notify_show_ingame_sound_page ();

			break;
		}
		case OPTIONS_PAGE_MULTIPLAYER:
		{
			notify_multi_player_setup ();

			break;
		}
		default:
		{
			debug_fatal ("OPTIONS.C: illegal options page called");
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_options_screen (void)
{
	float
		x_size,
		y_size;

	x_size = 1.0;
	y_size = 1.0;

	/////////////////////////////////////////////////////////////////

   options_screen = create_ui_object
            (
               UI_TYPE_SCREEN,
					UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
					UI_ATTR_VIRTUAL_SIZE (x_size, y_size),
					UI_ATTR_COLOUR_START (255, 255, 255, 0),
					UI_ATTR_COLOUR_END (255, 255, 255, 255),
					UI_ATTR_OFFSET_TIME (0),
					UI_ATTR_TIME_LENGTH (500),
					UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_DISPLAYED),
					UI_ATTR_FUNCTION (notify_options_screen),
               UI_ATTR_END
            );

   create_ui_object
            (
               UI_TYPE_TEXT,
               UI_ATTR_PARENT (options_screen),
					UI_ATTR_OFFSET_TIME (0),
					UI_ATTR_TIME_LENGTH (500),
               UI_ATTR_VIRTUAL_POSITION (TITLE_TEXT_POSITION_X, TITLE_TEXT_POSITION_Y),
					UI_ATTR_VIRTUAL_SIZE (TITLE_TEXT_WIDTH, TITLE_TEXT_HEIGHT),
					UI_ATTR_TEXT (get_trans ("Options Screen")),
					UI_ATTR_FONT_TYPE (UI_FONT_IMPACT_22),
					UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_BOTTOM),
               UI_ATTR_FONT_COLOUR_START (ui_screen_title_text_colour.r, ui_screen_title_text_colour.g, ui_screen_title_text_colour.b, 0),
               UI_ATTR_FONT_COLOUR_END (ui_screen_title_text_colour.r, ui_screen_title_text_colour.g, ui_screen_title_text_colour.b, 255),
					UI_ATTR_HIGHLIGHTABLE (FALSE),
					UI_ATTR_CLEAR (TRUE),
               UI_ATTR_END
            );

	/////////////////////////////////////////////////////////////////

	define_options_screen_controller_page_objects ();
	
	/////////////////////////////////////////////////////////////////

	define_options_screen_dynamics_page_objects ();
	
	/////////////////////////////////////////////////////////////////

	define_options_screen_graphics_page_objects ();
	
	/////////////////////////////////////////////////////////////////

	define_options_screen_realism_page_objects ();

	/////////////////////////////////////////////////////////////////

	define_options_screen_sound_page_objects ();

	define_options_screen_ingame_sound_page_objects ();

	/////////////////////////////////////////////////////////////////

	define_multi_player_setup_objects ();

	options_page [OPTIONS_PAGE_MULTIPLAYER] = multi_player_setup_area;
	
	/////////////////////////////////////////////////////////////////

	define_options_screen_common_objects ();

	/////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_clear_options_screen(void)
{

	store_multiplayer_options ();

	// Save the global options data

	save_global_options_data ();
	
	// if the graphics display adapter has changed, boot the player out
	{
	
		int
			flag;

		flag = FALSE;
	
		if (old_graphics_card_automatic_selection != get_global_graphics_device_selection_automatic ())
		{
			flag = TRUE;
		}
		else
		{
			flag = FALSE;
		}
	
		if (!old_graphics_card_automatic_selection)
		{
			if (old_graphics_card_selection != get_card_selection_device ())
			{
				flag = TRUE;
			}
			else
			{
				flag = FALSE;
			}
		}

		if (flag)
		{
			push_ui_screen (exit_screen);
		}
		else
		{
			pop_ui_screen (SCREEN_POP_ACTUAL);
		}
	}

	#if DEBUG_MODULE

	debug_filtered_log("Inside clear_options_screen");

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void show_options_page(void)
{

//	pop_event (campaign_options_events);

//	initialise_options_screen();
	
	push_ui_screen (options_screen);

	#if DEBUG_MODULE

	debug_filtered_log("Inside show_options_screen");

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


