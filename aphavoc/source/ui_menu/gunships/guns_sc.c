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
	*gunships_screen,
	*gunships_area,
	*gunship_screen_back_button,
	*gunship_screen_next_button,
	*gunship_screen_button_title_area,
	*gunship_screen_button_area,
	*gunship_screen_gunship_type_button,
	*gunship_screen_gunship_text,
	*gunship_screen_gunship_text_area,
	*gunship_screen_gunship_type_area,
	*side_selected_area,
	*gunship_screen_waiting_area,
	*gunship_screen_waiting_area_text;

texture_graphic
	*gunships_screen_graphic = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	stop_gunship_model_rotating,
	gunships_screen_progress_indicator_counter,
	gunship_screen_progress_message,
	valid_helicopter,
	gunships_screen_side_selected = ENTITY_SIDE_NEUTRAL;

static int
	gunship_screen_progress_dot_count = 0,
	gunship_waiting_for_connection,
	gunship_just_entered_screen = FALSE;

void gunship_screen_render_gunship ( ui_object *obj, void *arg );

void notify_gunships_next_button (ui_object *obj, void *arg);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_gunships_screen (ui_object *obj, void *arg);

static void notify_briefing_button ( ui_object *obj, void *arg );

static void notify_gunships_back_button (ui_object *obj, void *arg);

static char* get_gunship_name(void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_gunships_screen (void)
{
	float
		x1,
		y1,
		x2,
		y2;

	ui_object
		*option_bdrop;


	// Casm 11JUN05 Preselect side if requested
	if ( gunships_screen_side_selected == ENTITY_SIDE_NEUTRAL )
	{
		switch ( command_line_game_initialisation_phase_gunship_type )
		{
			case GUNSHIP_TYPE_APACHE:
			case GUNSHIP_TYPE_COMANCHE:
			case GUNSHIP_TYPE_BLACKHAWK:
			case GUNSHIP_TYPE_AH64A:
			case GUNSHIP_TYPE_VIPER:
			{
				gunships_screen_side_selected = ENTITY_SIDE_BLUE_FORCE;
				set_free_flight_gunship_type ( ( gunship_types ) command_line_game_initialisation_phase_gunship_type );

				break;
			}

			case GUNSHIP_TYPE_HAVOC:
			case GUNSHIP_TYPE_HOKUM:
			case GUNSHIP_TYPE_HIND:
			case GUNSHIP_TYPE_KA50:
			{
				gunships_screen_side_selected = ENTITY_SIDE_RED_FORCE;
				set_free_flight_gunship_type ( ( gunship_types ) command_line_game_initialisation_phase_gunship_type );

				break;
			}
		}
	}
	// Casm 11JUN05 Preselect side if requested

	x1 = 0.0;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 1.0;

   gunships_screen = create_ui_object
            (
               UI_TYPE_SCREEN,
               UI_ATTR_VIRTUAL_POSITION (x1, y1),
               UI_ATTR_VIRTUAL_SIZE (x2, y2),
					UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_EITHER),
					UI_ATTR_FUNCTION (notify_gunships_screen),
               UI_ATTR_COLOUR_START (255,255,255,64),
               UI_ATTR_COLOUR_END (255,255,255,255),
					UI_ATTR_OFFSET_TIME (0),
					UI_ATTR_TIME_LENGTH (500),
               UI_ATTR_END
            );

	create_ui_object
            (
               UI_TYPE_TEXT,
               UI_ATTR_PARENT (gunships_screen),
					UI_ATTR_TIME_LENGTH (0),
					UI_ATTR_OFFSET_TIME (0),
               UI_ATTR_VIRTUAL_POSITION (TITLE_TEXT_POSITION_X, TITLE_TEXT_POSITION_Y),
					UI_ATTR_VIRTUAL_SIZE (TITLE_TEXT_WIDTH, TITLE_TEXT_HEIGHT),
					UI_ATTR_TEXT (get_trans ("Side")),
					UI_ATTR_FONT_TYPE (UI_FONT_IMPACT_22),
					UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_BOTTOM),
               UI_ATTR_FONT_COLOUR_START (ui_screen_title_text_colour.r, ui_screen_title_text_colour.g, ui_screen_title_text_colour.b, 0),
               UI_ATTR_FONT_COLOUR_END (ui_screen_title_text_colour.r, ui_screen_title_text_colour.g, ui_screen_title_text_colour.b, 255),
					UI_ATTR_HIGHLIGHTABLE (FALSE),
					UI_ATTR_CLEAR (TRUE),
               UI_ATTR_END
            );

	//////////////////////////////////////////////
	// gunship buttons

	x1 = 0.200;
	y1 = 0.734;
	x2 = 0.298;
	y2 = 0.059;

   gunship_screen_button_title_area = create_ui_object
									(
										UI_TYPE_AREA,
										UI_ATTR_PARENT (gunships_screen),
			            	   	UI_ATTR_VIRTUAL_POSITION (x1, y1),
      			        	 		UI_ATTR_VIRTUAL_SIZE (x2, y2),
										UI_ATTR_CLEAR (TRUE),
										UI_ATTR_END
									);

	x1 = 0.0;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 1.0;

	gunship_screen_gunship_text_area = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (gunship_screen_button_title_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (x2, y2),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

	gunship_screen_gunship_text = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (gunship_screen_button_title_area),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (0.910, 0.133),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("Side")),
		UI_ATTR_END
	);

	x1 = 0.503;
	y1 = 0.734;
	x2 = 0.298;
	y2 = 0.059;

   gunship_screen_button_area = create_ui_object
								(
									UI_TYPE_AREA,
									UI_ATTR_PARENT (gunships_screen),
			   	            UI_ATTR_VIRTUAL_POSITION (x1, y1),
     			        	 		UI_ATTR_VIRTUAL_SIZE (x2, y2),
									UI_ATTR_CLEAR (TRUE),
									UI_ATTR_END
								);

	x1 = 0.0;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 1.0;

	gunship_screen_gunship_type_area = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (gunship_screen_button_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (x2, y2),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

   gunship_screen_gunship_type_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (gunship_screen_button_area),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
		UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
		UI_ATTR_VIRTUAL_POSITION (0.058, 0.133),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (gunships_button_function),
		UI_ATTR_END
	);


	//////////////////////////////////////////////
	// side selected text

	x1 = 0.440;
	y1 = OPTIONS_OK_BUTTON_POS_Y;
	x2 = 0.25;
	y2 = 0.059;

	x1 = 0.0;
	y1 = OPTIONS_OK_BUTTON_POS_Y;
	x2 = 1.0;
	y2 = 0.059;

   side_selected_area = create_ui_object
								(
									UI_TYPE_AREA,
									UI_ATTR_PARENT (gunships_screen),
									UI_ATTR_VIRTUAL_POSITION (x1, y1),
     			        	 		UI_ATTR_VIRTUAL_SIZE (x2, y2),
									UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
									UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_CENTRE),
							      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
							      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
									UI_ATTR_TEXT (""),
									UI_ATTR_CLEAR (TRUE),
									UI_ATTR_END
								);

	//////////////////////////////////////////////
	// Gunship Render Area

	x1 = 0.087;
	y1 = 0.229;
	x2 = 0.828;
	y2 = 0.454;

	gunships_area = create_ui_object
							(
								UI_TYPE_AREA,
								UI_ATTR_PARENT (gunships_screen),
			               UI_ATTR_VIRTUAL_POSITION (x1, y1),
      			         UI_ATTR_VIRTUAL_SIZE (x2, y2),
								UI_ATTR_DRAW_FUNCTION (gunship_screen_render_gunship),
			               UI_ATTR_COLOUR_START (10, 5, 40, 0),
	    					   UI_ATTR_COLOUR_END (10, 5, 40, 255),
								UI_ATTR_CLEAR (TRUE),
								UI_ATTR_END
							);


	/////////////////////////////////////////////////////////////////
	// back and next
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	// Ok Button

	option_bdrop = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (gunships_screen),
		UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
		UI_ATTR_VIRTUAL_SIZE (TEXT_OPTION_BDROP_WIDTH, TEXT_OPTION_BDROP_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 255),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (text_option_bdrop),
		UI_ATTR_END
	);

	gunship_screen_next_button = create_ui_object
			(
				UI_TYPE_BUTTON,
				UI_ATTR_PARENT (gunships_screen),
				UI_ATTR_VIRTUAL_POSITION (OPTIONS_OK_BUTTON_POS_X, OPTIONS_OK_BUTTON_POS_Y),
				UI_ATTR_VIRTUAL_SIZE (OPTIONS_OK_BUTTON_X, OPTIONS_OK_BUTTON_Y),
				UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
  			   UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      		UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      		UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      		UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
				UI_ATTR_HIGHLIGHTABLE (TRUE),
				UI_ATTR_TEXT (get_trans("SELECT")),
				UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
				UI_ATTR_FUNCTION (notify_gunships_next_button),
				UI_ATTR_DRAWABLE (FALSE),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	set_text_option_backdrop_object (option_bdrop, gunship_screen_next_button);

	/////////////////////////////////////////////////////////////////
	// Cancel Button

	option_bdrop = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (gunships_screen),
		UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
		UI_ATTR_VIRTUAL_SIZE (TEXT_OPTION_BDROP_WIDTH, TEXT_OPTION_BDROP_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 255),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (text_option_bdrop),
		UI_ATTR_END
	);

	gunship_screen_back_button = create_ui_object
			(
				UI_TYPE_BUTTON,
				UI_ATTR_PARENT (gunships_screen),
				UI_ATTR_VIRTUAL_POSITION (OPTIONS_CANCEL_BUTTON_POS_X, OPTIONS_CANCEL_BUTTON_POS_Y),
				UI_ATTR_VIRTUAL_SIZE (OPTIONS_CANCEL_BUTTON_X, OPTIONS_CANCEL_BUTTON_Y),
				UI_ATTR_TEXT (get_trans("UI_CANCEL")),
				UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
				UI_ATTR_FUNCTION (notify_gunships_back_button),
				UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
      		UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      		UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      		UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      		UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
				UI_ATTR_HIGHLIGHTABLE (TRUE),
				UI_ATTR_DRAWABLE (FALSE),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	set_text_option_backdrop_object (option_bdrop, gunship_screen_back_button);

	x1 = 0.370;
	y1 = 0.758;
	x2 = 0.258;
	y2 = 0.102;

	gunship_screen_waiting_area = create_ui_object
											(
												UI_TYPE_AREA,
												UI_ATTR_PARENT (gunships_screen),
							               UI_ATTR_VIRTUAL_POSITION (x1, y1),
				      			         UI_ATTR_VIRTUAL_SIZE (x2, y2),
												UI_ATTR_CLEAR ( TRUE ),
												UI_ATTR_END
											);

	x1 = 0.328;
	y1 = OPTIONS_CANCEL_BUTTON_POS_Y;
	x2 = 0.4;
	y2 = 0.05;

	gunship_screen_waiting_area_text = create_ui_object
											(
												UI_TYPE_TEXT,
												UI_ATTR_PARENT (gunships_screen),
							               UI_ATTR_VIRTUAL_POSITION (x1, y1),
				      			         UI_ATTR_VIRTUAL_SIZE (x2, y2),
   							  	 			UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
  								    			UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
												UI_ATTR_HIGHLIGHTABLE (FALSE),
												UI_ATTR_TEXT (""),
												UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_22),
												UI_ATTR_END
											);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_gunships_screen (ui_object *obj, void *arg)
{

	if ( get_ui_object_drawable ( obj ) )
	{
		if (get_game_type () == GAME_TYPE_FREE_FLIGHT)
		{
			if (gunships_screen_side_selected == ENTITY_SIDE_NEUTRAL || get_free_flight_gunship_type() == NUM_GUNSHIP_TYPES)

				if ((gunships_screen_side_selected == ENTITY_SIDE_NEUTRAL) || (gunships_screen_side_selected == ENTITY_SIDE_BLUE_FORCE))
				{
					set_free_flight_gunship_type(GUNSHIP_TYPE_APACHE);
					gunships_screen_side_selected = ENTITY_SIDE_BLUE_FORCE;
				}
				else
				{
					set_free_flight_gunship_type(GUNSHIP_TYPE_HOKUM);
					gunships_screen_side_selected = ENTITY_SIDE_RED_FORCE;
				}

			set_ui_object_text (gunship_screen_gunship_type_button, get_gunship_name());
			set_ui_object_text (side_selected_area, get_trans (""));
			set_ui_object_text_justify (side_selected_area, TEXT_JUSTIFY_LEFT_CENTRE);
		}
		else
		{
			if ((gunships_screen_side_selected == ENTITY_SIDE_NEUTRAL) || (gunships_screen_side_selected == ENTITY_SIDE_BLUE_FORCE))
			{
				set_ui_object_text (gunship_screen_gunship_type_button, get_trans ("Blue Force"));

				set_ui_object_text (side_selected_area, get_trans (""));

				set_ui_object_text_justify (side_selected_area, TEXT_JUSTIFY_CENTRE);

				gunships_screen_side_selected = ENTITY_SIDE_BLUE_FORCE;
			}
			else
			{
				set_ui_object_text (gunship_screen_gunship_type_button, get_trans ("Red Force"));

				set_ui_object_text (side_selected_area, get_trans (""));

				set_ui_object_text_justify (side_selected_area, TEXT_JUSTIFY_CENTRE);

				gunships_screen_side_selected = ENTITY_SIDE_RED_FORCE;
			}
		}

		set_ui_object_drawable (gunship_screen_back_button, TRUE);

		//set_ui_object_drawable (gunship_screen_next_button, TRUE);
		//set_ui_object_text (gunship_screen_next_button, get_trans("SELECT"));
		set_display_gunship_buttons (TRUE, "SELECT");

		process_game_initialisation_phases ();

		blit_front_buffer_to_render_buffer ();

		if ( gunships_screen_graphic )
		{

			destroy_texture_graphic ( gunships_screen_graphic );

			gunships_screen_graphic = NULL;
		}

		free_all_hardware_textures ();

		gunships_screen_graphic = create_texture_graphic ( "graphics\\ui\\cohokum\\gunship.psd" );

		set_ui_object_texture_graphic ( gunships_screen, gunships_screen_graphic );

		reset_time_values ( gunships_screen );

		gunship_just_entered_screen = TRUE;

		// Casm 31MAR2009 Loading custom map textures before the first
		// 3d object is shown
		// VJ 050116 custom texture mod
		load_warzone_override_textures ();
	}
	else
	{

		if ( gunships_screen_graphic )
		{

			destroy_texture_graphic ( gunships_screen_graphic );

			gunships_screen_graphic = NULL;
		}
	}

	if (get_comms_model () == COMMS_MODEL_SERVER)
	{

		// set flag for helo rotation
		stop_gunship_model_rotating = FALSE;
	}
	else
	{

		// set flag for helo rotation
		stop_gunship_model_rotating = TRUE;
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void gunships_button_function (ui_object *obj, void *arg)
{
	if (get_game_type () == GAME_TYPE_FREE_FLIGHT)  // in free flight select helicopter instead of side
	{
		switch (get_free_flight_gunship_type())
		{
		case GUNSHIP_TYPE_HAVOC:
#ifdef DEBUG
			gunships_screen_side_selected = ENTITY_SIDE_BLUE_FORCE;
			set_free_flight_gunship_type(GUNSHIP_TYPE_AH64A);
			break;
#endif
		case GUNSHIP_TYPE_AH64A:
			gunships_screen_side_selected = ENTITY_SIDE_BLUE_FORCE;
			set_free_flight_gunship_type(GUNSHIP_TYPE_APACHE);
			break;
		case GUNSHIP_TYPE_APACHE:
			gunships_screen_side_selected = ENTITY_SIDE_BLUE_FORCE;
			set_free_flight_gunship_type(GUNSHIP_TYPE_COMANCHE);
			break;
		case GUNSHIP_TYPE_COMANCHE:
#ifdef DEBUG
			gunships_screen_side_selected = ENTITY_SIDE_BLUE_FORCE;
			set_free_flight_gunship_type(GUNSHIP_TYPE_BLACKHAWK);
			break;
#endif
		case GUNSHIP_TYPE_BLACKHAWK:
#ifdef DEBUG
			set_free_flight_gunship_type(GUNSHIP_TYPE_KA50);
			gunships_screen_side_selected = ENTITY_SIDE_RED_FORCE;
			break;
#endif
		case GUNSHIP_TYPE_KA50:
			set_free_flight_gunship_type(GUNSHIP_TYPE_HOKUM);
			gunships_screen_side_selected = ENTITY_SIDE_RED_FORCE;
			break;
		case GUNSHIP_TYPE_HOKUM:
			set_free_flight_gunship_type(GUNSHIP_TYPE_HIND);
			gunships_screen_side_selected = ENTITY_SIDE_RED_FORCE;
			break;
		case GUNSHIP_TYPE_HIND:
			set_free_flight_gunship_type(GUNSHIP_TYPE_VIPER);
			gunships_screen_side_selected = ENTITY_SIDE_BLUE_FORCE;
			break;
		case GUNSHIP_TYPE_VIPER:
			set_free_flight_gunship_type(GUNSHIP_TYPE_HAVOC);
			gunships_screen_side_selected = ENTITY_SIDE_RED_FORCE;
			break;
		}

		set_ui_object_text(gunship_screen_gunship_type_button, get_gunship_name());
		set_ui_object_text_justify (side_selected_area, TEXT_JUSTIFY_LEFT_CENTRE);
	}
	else
		if ((gunships_screen_side_selected == ENTITY_SIDE_BLUE_FORCE) || (gunships_screen_side_selected == ENTITY_SIDE_NEUTRAL))
		{
			set_ui_object_text (gunship_screen_gunship_type_button, get_trans ("Red Force"));

			set_ui_object_text (side_selected_area, get_trans (""));

			set_ui_object_text_justify (side_selected_area, TEXT_JUSTIFY_CENTRE);

			gunships_screen_side_selected = ENTITY_SIDE_RED_FORCE;
		}
		else
		{
			set_ui_object_text (gunship_screen_gunship_type_button, get_trans ("Blue Force"));

			set_ui_object_text (side_selected_area, get_trans (""));

			set_ui_object_text_justify (side_selected_area, TEXT_JUSTIFY_CENTRE);

			gunships_screen_side_selected = ENTITY_SIDE_BLUE_FORCE;
		}

	// don't leave text selected

	set_toggle_button_off (obj);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_gunships_back_button (ui_object *obj, void *arg)
{

	leave_mission ();

	set_global_gunship_side (ENTITY_SIDE_NEUTRAL);

	set_game_initialisation_phase (GAME_INITIALISATION_PHASE_SCENARIO);

	pop_ui_screen (SCREEN_POP_ACTUAL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_gunships_next_button (ui_object *obj, void *arg)
{

	if (get_comms_model () == COMMS_MODEL_SERVER)
	{

		// set flag for helo rotation
		stop_gunship_model_rotating = TRUE;
	}

	set_global_gunship_side (gunships_screen_side_selected);

	//
	// Load up the sound effects for this side
	//

	load_side_dependant_application_sound_samples ( ( entity_sides ) gunships_screen_side_selected );

	if ( !gunship_waiting_for_connection )
	{

		process_game_initialisation_phases ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_gunship_waiting_for_connection ( int flag )
{

	gunship_waiting_for_connection = flag;

	if ( flag )
	{

		set_ui_object_drawable ( gunship_screen_waiting_area, TRUE );
		set_ui_object_drawable ( gunship_screen_waiting_area_text, TRUE );

		if (current_game_session->type == SESSION_LIST_TYPE_JOIN)
		{

			set_display_gunship_buttons (FALSE, "SELECT");
		}
	}
	else
	{

		set_ui_object_drawable ( gunship_screen_waiting_area, FALSE );
		set_ui_object_drawable ( gunship_screen_waiting_area_text, FALSE );

		if (current_game_session->type == SESSION_LIST_TYPE_JOIN)
		{

			// set flag for helo rotation
			stop_gunship_model_rotating = FALSE;

			set_display_gunship_buttons (TRUE, "SELECT");
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_gunships_screen_progress_indicator (void)
{

	int
		loop;

	static int
		progress_timer = 0;

	char
		buffer [64];

	//////////////////////////////////////////////////////////////////////////////////

	if (progress_timer > get_system_time ())
	{

		return;
	}

	//////////////////////////////////////////////////////////////////////////////////

	progress_timer = get_system_time () + TIME_1_SECOND;

	gunship_screen_progress_dot_count ++;

	if (gunship_screen_progress_dot_count > 5)
	{

		gunship_screen_progress_dot_count = 0;
	}

	if (get_gunship_screen_progress_message () == GUNSHIPS_SCREEN_CONNECTING_TEXT)
	{

//		set_ui_object_x (gunship_screen_waiting_area_text, get_localisation_x_position (text_translation_list, GUNSHIPS_SCREEN_CONNECTING_TEXT));

		// debug to show number of packets
		//strcpy (buffer, get_localisation_text (text_translation_list, GUNSHIPS_SCREEN_CONNECTING_TEXT));
		sprintf (buffer, "%s (%d)", get_trans ("Connecting"), personal_packet_list_counter);
		// debug to show number of packets
	}
	else
	{

//		set_ui_object_x (gunship_screen_waiting_area_text, get_localisation_x_position (text_translation_list, GUNSHIPS_SCREEN_GENERATING_CAMPAIGN_TEXT));

		strcpy (buffer, get_trans ("Generating Campaign"));
	}

	for (loop = 0; loop < gunship_screen_progress_dot_count; loop ++)
	{

		strcat (buffer, " .");
	}

	strcat (buffer, "\0");

	set_ui_object_text (gunship_screen_waiting_area_text, buffer);

	ui_repaint ();

	#if DEBUG_MODULE

	debug_log ("GUNS_SC: setting progress text to %s", buffer);

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_gunship_screen_progress_message (int message)
{

	gunship_screen_progress_message = message;

	gunship_screen_progress_dot_count = 0;

	if (message == GUNSHIPS_SCREEN_CONNECTING_TEXT)
	{

//		set_ui_object_x (gunship_screen_waiting_area_text, get_localisation_x_position (text_translation_list, GUNSHIPS_SCREEN_CONNECTING_TEXT));

		set_ui_object_text (gunship_screen_waiting_area_text, get_trans ("Connecting"));
	}
	else
	{

		// set flag for helo rotation
		stop_gunship_model_rotating = TRUE;

//		set_ui_object_x (gunship_screen_waiting_area_text, get_localisation_x_position (text_translation_list, GUNSHIPS_SCREEN_GENERATING_CAMPAIGN_TEXT));

		set_ui_object_text (gunship_screen_waiting_area_text, get_trans ("Generating Campaign"));
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void gunship_screen_render_gunship ( ui_object *obj, void *arg )
{

	object_3d_instance
		*apache;

	static float
		heading = rad (180.0),
		my_heading = 0,
		pitch = rad (-14);

	static int
		my_time = 3600*16;

	set_3d_active_environment ( main_3d_env );

	set_3d_lightmode ( main_3d_env, LIGHTMODE_AUTOMATIC_LIGHT );

	set_3d_infrared_mode ( main_3d_env, INFRARED_OFF );

	set_3d_weathermode (main_3d_env, WEATHERMODE_DRY );

	set_3d_target_weathermode (main_3d_env, WEATHERMODE_DRY );

	set_3d_target_weathermode_transitional_status (main_3d_env, 0.0 );

	set_3d_time_of_day (main_3d_env, my_time );

	{
		float
			obj_x1,
			obj_y1,
			obj_x2,
			obj_y2,
			obj_size_x,
			obj_size_y;

		obj_x1 = get_ui_object_x (obj);
		obj_y1 = get_ui_object_y (obj);
		obj_size_x = get_ui_object_x_size (obj);
		obj_size_y = get_ui_object_y_size (obj);

		obj_x2 = obj_x1 + obj_size_x;
		obj_y2 = obj_y1 + obj_size_y;

//		set_3d_viewport ( main_3d_env, obj_x1, obj_y1, obj_x2, obj_y2 );

//		set_3d_origin ( main_3d_env, obj_x1 + (obj_size_x / 2.0), obj_y1 + (obj_size_y / 2.0) );

//		set_3d_viewcone ( main_3d_env, obj_size_x, obj_size_y, rad ( 59.99 ), rad ( 46.82 ) );

		set_3d_viewport ( main_3d_env, 0, 0, ( float ) application_video_width - 0.001, ( float ) application_video_height - 0.001 );

		set_3d_origin ( main_3d_env, application_video_width /2, application_video_height/2 );

		set_3d_viewcone ( main_3d_env, application_video_width, application_video_height, rad ( 59.99 ), rad (59.99) / full_screen_aspect_ratio );
#if RECOGNITION_GUIDE
		set_3d_view_distances ( main_3d_env, 10000.0, 100.0, 1.0, 0.0 );
#else
		set_3d_view_distances ( main_3d_env, 10000.0, 1.0, 1.0, 0.0 );
#endif
	}

	recalculate_3d_environment_settings (main_3d_env);

	clear_zbuffer_screen ();

	visual_3d_vp->x = 0;
	visual_3d_vp->y = 0;
	visual_3d_vp->z = 0;

	get_3d_transformation_matrix ( visual_3d_vp->attitude, 0, 0, 0 );

	if (get_game_type() == GAME_TYPE_FREE_FLIGHT)
	{
		pitch = rad(4);
		heading = rad(235);

		switch (get_free_flight_gunship_type())
		{
		case GUNSHIP_TYPE_AH64A:
			apache = construct_temporary_3d_object ( OBJECT_3D_AH_64A, FALSE );
			break;
		case GUNSHIP_TYPE_APACHE:
			apache = construct_temporary_3d_object ( OBJECT_3D_AH64D_APACHE_LONGBOW, FALSE );
			break;
		case GUNSHIP_TYPE_COMANCHE:
			apache = construct_temporary_3d_object ( OBJECT_3D_RAH66_UI, FALSE );
			break;
		case GUNSHIP_TYPE_BLACKHAWK:
			apache = construct_temporary_3d_object ( OBJECT_3D_UH60_BLACKHAWK, FALSE );
			pitch = rad(2);
			break;
		case GUNSHIP_TYPE_KA50:
			apache = construct_temporary_3d_object ( OBJECT_3D_KA_50, FALSE );
			pitch = 0;
			break;
		case GUNSHIP_TYPE_HOKUM:
			apache = construct_temporary_3d_object ( OBJECT_3D_KA_52_UI, FALSE );
			pitch = 0;
			break;
		case GUNSHIP_TYPE_HIND:
			apache = construct_temporary_3d_object ( OBJECT_3D_MI24_HIND, FALSE );
			pitch = rad(-3);
			break;
		case GUNSHIP_TYPE_HAVOC:
			apache = construct_temporary_3d_object ( OBJECT_3D_MI28N_HAVOC, FALSE );
			break;
		case GUNSHIP_TYPE_VIPER:
			apache = construct_temporary_3d_object ( OBJECT_3D_AH1_Z, FALSE );
			pitch = rad(2);
			break;
		}
	}
	else
		if ( gunships_screen_side_selected == ENTITY_SIDE_BLUE_FORCE )
		{

			apache = construct_temporary_3d_object ( OBJECT_3D_RAH66_UI, FALSE );

			set_texture_animation_frame_on_object ( apache, TEXTURE_ANIMATION_INDEX_USA_COPTER_DIGIT__000, 4 );
			set_texture_animation_frame_on_object ( apache, TEXTURE_ANIMATION_INDEX_USA_COPTER_DIGIT__001, 2 );
			set_texture_animation_frame_on_object ( apache, TEXTURE_ANIMATION_INDEX_USA_COPTER_DIGIT__002, 9 );
			set_texture_animation_frame_on_object ( apache, TEXTURE_ANIMATION_INDEX_USA_COPTER_DIGIT__003, 1 );
			set_texture_animation_frame_on_object ( apache, TEXTURE_ANIMATION_INDEX_USA_COPTER_DIGIT__004, 3 );
		}
		else
		{

			apache = construct_temporary_3d_object ( OBJECT_3D_KA_52_UI, FALSE );

			set_texture_animation_frame_on_object ( apache, TEXTURE_ANIMATION_INDEX_CIS_COPTER_DIGIT__000, 1 );
			set_texture_animation_frame_on_object ( apache, TEXTURE_ANIMATION_INDEX_CIS_COPTER_DIGIT__001, 5 );
			set_texture_animation_frame_on_object ( apache, TEXTURE_ANIMATION_INDEX_CIS_COPTER_DIGIT__002, 2 );
		}

	apache->vp.x = 0;

	if ( gunships_screen_side_selected == ENTITY_SIDE_BLUE_FORCE )
	{
		apache->vp.y = 1.5;
	}
	else
	{
		apache->vp.y = 2.2;
	}

	apache->vp.z = 18;//12

	get_3d_transformation_matrix ( visual_3d_vp->attitude, 0, rad ( 0 ) , my_heading );

	get_3d_transformation_matrix ( apache->vp.attitude, heading, pitch, 0.0);

	if (!stop_gunship_model_rotating)
	{

		if ( gunship_just_entered_screen )
		{

			gunship_just_entered_screen = FALSE;
		}
		else
		{

			heading += ( 0.75 * get_delta_time () );
		}
	}

	insert_object_into_3d_scene ( OBJECT_3D_DRAW_TYPE_OBJECT, apache );

	set_d3d_alpha_fog_zbuffer ( FALSE, TRUE, TRUE, TRUE );

	draw_3d_scene ();

	set_d3d_alpha_fog_zbuffer ( TRUE, FALSE, FALSE, FALSE );

	//
	// DO NOT DESTRUCT THE TEMPORARY INSTANCE - IT WILL CAUSE A PAGE FAULT
	//
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_display_gunship_buttons (int flag, char *text)
{

	set_ui_object_drawable (gunship_screen_next_button, flag);
	set_ui_object_drawable (side_selected_area, flag);
	set_ui_object_drawable (gunship_screen_gunship_type_button, flag);
	set_ui_object_drawable (gunship_screen_gunship_type_area, flag);
	set_ui_object_drawable (gunship_screen_gunship_text, flag);
	set_ui_object_drawable (gunship_screen_gunship_text_area, flag);

	set_ui_object_text (gunship_screen_next_button, get_trans (text));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char* get_gunship_name(void)
{
	switch (get_free_flight_gunship_type())
	{
		case GUNSHIP_TYPE_AH64A:
			return "AH-64A Apache";
		case GUNSHIP_TYPE_APACHE:
			return "AH-64D Longbow";
		case GUNSHIP_TYPE_COMANCHE:
			return "RAH-66 Comanche";
		case GUNSHIP_TYPE_BLACKHAWK:
			return "UH-60 Blackhawk";
		case GUNSHIP_TYPE_KA50:
			return "Ka-50 Black Shark";
		case GUNSHIP_TYPE_HOKUM:
			return "Ka-52 Alligator";
		case GUNSHIP_TYPE_HIND:
			return "Mi-24V \"Hind E\"";
		case GUNSHIP_TYPE_HAVOC:
			return "Mi-28N \"Havoc B\"";
		case GUNSHIP_TYPE_VIPER:
			return "AH-1Z Viper";
	}

	return "Invalid gunship";
}
