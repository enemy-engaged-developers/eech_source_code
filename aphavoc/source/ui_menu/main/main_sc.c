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
	*main_area,
	*main_screen,
	*pilots_button,
	*credits_button,
	*modcredits_button,
	*ghost_pilots_button,
	*ghost_credits_button;

texture_graphic
	*options_box_small = NULL,
	*options_box_medium = NULL,
	*options_box_large = NULL,
	*options_box_extra_large = NULL,
	*options_axis_bar = NULL,
	*text_box_graphic = NULL,
	*text_option_bdrop = NULL,
	*list_box_graphic = NULL;

static texture_graphic
	*frontend_slider_bar_graphic = NULL,
	*frontend_slider_bdrop_graphic = NULL,
	*frontend_slider_bar_highlighted_graphic = NULL,
	*frontend_slider_bar_selected_graphic = NULL,
	*frontend_slider_up_graphic = NULL,
	*frontend_slider_up_highlighted_graphic = NULL,
	*frontend_slider_up_selected_graphic = NULL,
	*frontend_slider_down_graphic = NULL,
	*frontend_slider_down_highlighted_graphic = NULL,
	*frontend_slider_down_selected_graphic = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float
	main_screen_t_value = 0.0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_main_screen_exit_button (ui_object *obj, void *arg);

void draw_main_screen_background ( ui_object *obj, void *data );

static void animate_screen_scene ( float t, object_3d_instance *object );

static void recurse_animate_screen_scene ( float t, object_3d_database_entry *scene, object_3d_sub_instance *object );

static void notify_common_main_options_button (ui_object *obj, void *arg);

void set_frontend_slider_graphics (ui_object *parent);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_main_screen (void)
{
	ui_object
		*option_bdrop,
		*change_obj,
		*registered_to_message;

	float
		x1,
		y1,
		x2,
		y2;

	int
		i;

	deinitialise_main_screen ();

	/////////////////////////////////////////////////////////////////
	// option area & button texture objects

	options_box_small = create_texture_graphic ( "graphics\\ui\\cohokum\\boxsmall.psd", 1 );

	options_box_medium = create_texture_graphic ( "graphics\\ui\\cohokum\\boxmed.psd", 1 );

	options_box_large = create_texture_graphic ( "graphics\\ui\\cohokum\\boxlarge.psd", 1 );

	options_box_extra_large = create_texture_graphic ( "graphics\\ui\\cohokum\\boxexlrg.psd", 1 );

	options_axis_bar = create_texture_graphic ( "graphics\\ui\\cohokum\\Map\\RedBar.psd", 1 );

	text_box_graphic = create_texture_graphic ( "graphics\\ui\\cohokum\\Boxtext.psd", 1 );

	text_option_bdrop = create_texture_graphic ( "graphics\\ui\\cohokum\\bstripe.psd", 1 );

	/////////////////////////////////////////////////////////////////
	// List box graphics

	list_box_graphic = create_texture_graphic ( "graphics\\ui\\cohokum\\BoxList.psd", 1 );

	// initialise slider graphics
	frontend_slider_bdrop_graphic					= create_texture_graphic ( "graphics\\ui\\cohokum\\map\\sbcklist.psd", 1 );

	frontend_slider_bar_graphic 					= create_texture_graphic ( "graphics\\ui\\cohokum\\map\\scrolblu.psd", 1 );
	frontend_slider_bar_highlighted_graphic 	= create_texture_graphic ( "graphics\\ui\\cohokum\\map\\scrolwht.psd", 1 );
	frontend_slider_bar_selected_graphic 		= create_texture_graphic ( "graphics\\ui\\cohokum\\map\\scrolyel.psd", 1 );

	frontend_slider_up_graphic 					= create_texture_graphic ( "graphics\\ui\\cohokum\\map\\arrupblu.psd", 1 );
	frontend_slider_up_highlighted_graphic 	= create_texture_graphic ( "graphics\\ui\\cohokum\\map\\arrupwht.psd", 1 );
	frontend_slider_up_selected_graphic 		= create_texture_graphic ( "graphics\\ui\\cohokum\\map\\arrupyel.psd", 1 );

	frontend_slider_down_graphic 					= create_texture_graphic ( "graphics\\ui\\cohokum\\map\\arrdwblu.psd", 1 );
	frontend_slider_down_highlighted_graphic 	= create_texture_graphic ( "graphics\\ui\\cohokum\\map\\arrdwwht.psd", 1 );
	frontend_slider_down_selected_graphic 		= create_texture_graphic ( "graphics\\ui\\cohokum\\map\\arrdwyel.psd", 1 );


	/////////////////////////////////////////////////////////////////
	// Main Screen & title text

   main_screen = create_ui_object
            (
               UI_TYPE_SCREEN,
               UI_ATTR_VIRTUAL_POSITION (0, 0),
               UI_ATTR_VIRTUAL_SIZE (1.0, 1.0),
               UI_ATTR_COLOUR_START (255,255,255,64),
               UI_ATTR_COLOUR_END (255,255,255,255),
					UI_ATTR_OFFSET_TIME (0),
					UI_ATTR_TIME_LENGTH (500),
					UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_EITHER),
					UI_ATTR_FUNCTION (notify_main_screen),
               UI_ATTR_END
            );

   create_ui_object
            (
               UI_TYPE_TEXT,
               UI_ATTR_PARENT (main_screen),
					UI_ATTR_OFFSET_TIME (0),
					UI_ATTR_TIME_LENGTH (500),
               UI_ATTR_VIRTUAL_POSITION (TITLE_TEXT_POSITION_X, TITLE_TEXT_POSITION_Y),
					UI_ATTR_VIRTUAL_SIZE (TITLE_TEXT_WIDTH, TITLE_TEXT_HEIGHT),
					UI_ATTR_TEXT (get_trans ("Main Screen")),
					UI_ATTR_FONT_TYPE (UI_FONT_IMPACT_22),
					UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_BOTTOM),
               UI_ATTR_FONT_COLOUR_START (ui_screen_title_text_colour.r, ui_screen_title_text_colour.g, ui_screen_title_text_colour.b, 0),
               UI_ATTR_FONT_COLOUR_END (ui_screen_title_text_colour.r, ui_screen_title_text_colour.g, ui_screen_title_text_colour.b, 255),
					UI_ATTR_HIGHLIGHTABLE (FALSE),
					UI_ATTR_CLEAR (TRUE),
               UI_ATTR_END
            );


	/////////////////////////////////////////////////////////////////
	// Security Message - text to be inserted is ideally  <= 81 chars

	registered_to_message = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (main_screen),
			UI_ATTR_VIRTUAL_POSITION (0.05, 0.4),
			UI_ATTR_VIRTUAL_SIZE (0.9, 0.3),
			UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
         UI_ATTR_FONT_COLOUR_END (ui_screen_title_text_colour.r, ui_screen_title_text_colour.g, ui_screen_title_text_colour.b, 255),
			UI_ATTR_DRAWABLE (FALSE),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);


	/////////////////////////////////////////////////////////////////
	// Buttons

	// Combat

	i = 0;

	option_bdrop = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (main_screen),
		UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
		UI_ATTR_VIRTUAL_SIZE (TEXT_OPTION_BDROP_WIDTH, TEXT_OPTION_BDROP_HEIGHT),
		UI_ATTR_COLOUR_START (0, 0, 0, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_OFFSET_TIME (0),
		UI_ATTR_TIME_LENGTH (500),
		UI_ATTR_TEXTURE_GRAPHIC (text_option_bdrop),
		UI_ATTR_END
	);

   change_obj = create_ui_object
            (
               UI_TYPE_BUTTON,
               UI_ATTR_PARENT (main_screen),
					UI_ATTR_POSITION_START (0.0, 0.329),
					UI_ATTR_POSITION_END (0.663, 0.329),
					UI_ATTR_VIRTUAL_SIZE (0.196, 0.033),
					UI_ATTR_TEXT (get_trans ("UI_COMBAT")),
					UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_22),
					UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
					UI_ATTR_FUNCTION (notify_main_combat_missions_button),
            	UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
            	UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
            	UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
  		         UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
					UI_ATTR_HIGHLIGHTABLE (TRUE),
					UI_ATTR_CLEAR (TRUE),
					UI_ATTR_TIME_LENGTH (200),
					UI_ATTR_OFFSET_TIME (500),
               UI_ATTR_END
            );

	preprocess_translation_object_size (change_obj, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	set_text_option_backdrop_object (option_bdrop, change_obj);

	// Pilots

	i++;

	option_bdrop = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (main_screen),
		UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
		UI_ATTR_VIRTUAL_SIZE (TEXT_OPTION_BDROP_WIDTH, TEXT_OPTION_BDROP_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_OFFSET_TIME (0),
		UI_ATTR_TIME_LENGTH (500),
		UI_ATTR_TEXTURE_GRAPHIC (text_option_bdrop),
		UI_ATTR_END
	);

   pilots_button = create_ui_object
            (
               UI_TYPE_BUTTON,
               UI_ATTR_PARENT (main_screen),
					UI_ATTR_POSITION_START (0, 0.435),
					UI_ATTR_POSITION_END (0.785, 0.435),
					UI_ATTR_TIME_LENGTH (200),
					UI_ATTR_OFFSET_TIME (600),
					UI_ATTR_VIRTUAL_SIZE (0.155, 0.033),
               //UI_ATTR_GRAPHIC (get_graphics_file_data (GRAPHICS_UI_APACHE_MAIN_SCREEN_PLAYER_BUTTON)),
					UI_ATTR_TEXT (get_trans ("UI_PILOTS")),
					UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_22),
					UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
         	   UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
         	   UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
         	   UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
         	   UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
					UI_ATTR_FUNCTION (notify_main_select_player_button),
					UI_ATTR_HIGHLIGHTABLE (TRUE),
					UI_ATTR_CLEAR (TRUE),
               UI_ATTR_END
            );

	preprocess_translation_object_size (pilots_button, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	set_text_option_backdrop_object (option_bdrop, pilots_button);

	// ghost pilots button

	x1 = get_ui_object_virtual_x (pilots_button);
	x2 = get_ui_object_virtual_x_size (pilots_button);

	y1 = 0.435;
	y2 = 0.033;

	ghost_pilots_button = create_ui_object
									(
										UI_TYPE_AREA,
										UI_ATTR_PARENT (main_screen),
										UI_ATTR_VIRTUAL_POSITION (x1, y1),
										UI_ATTR_VIRTUAL_SIZE (x2, y2),
										UI_ATTR_CLEAR (TRUE),
										UI_ATTR_DRAWABLE (FALSE),
										UI_ATTR_END
									);


	// Options

	i++;

	option_bdrop = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (main_screen),
		UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
		UI_ATTR_VIRTUAL_SIZE (TEXT_OPTION_BDROP_WIDTH, TEXT_OPTION_BDROP_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (text_option_bdrop),
		UI_ATTR_OFFSET_TIME (0),
		UI_ATTR_TIME_LENGTH (500),
		UI_ATTR_END
	);

   change_obj = create_ui_object
            (
               UI_TYPE_BUTTON,
               UI_ATTR_PARENT (main_screen),
					UI_ATTR_POSITION_START (0, 0.595),
					UI_ATTR_POSITION_END (0.735, 0.595),
					UI_ATTR_TIME_LENGTH (200),
					UI_ATTR_OFFSET_TIME (700),
					UI_ATTR_VIRTUAL_SIZE (0.185, 0.042),
					UI_ATTR_TEXT (get_trans ("Options Screen")),
					UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_22),
					UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
					UI_ATTR_FUNCTION (notify_common_main_options_button),
      	      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
   	         UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
	            UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
	            UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
					UI_ATTR_HIGHLIGHTABLE (TRUE),
					UI_ATTR_CLEAR (TRUE),
               UI_ATTR_END
            );

	preprocess_translation_object_size (change_obj, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	set_text_option_backdrop_object (option_bdrop, change_obj);


	// Credits

	i++;

	option_bdrop = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (main_screen),
		UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
		UI_ATTR_VIRTUAL_SIZE (TEXT_OPTION_BDROP_WIDTH, TEXT_OPTION_BDROP_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_OFFSET_TIME (0),
		UI_ATTR_TIME_LENGTH (500),
		UI_ATTR_TEXTURE_GRAPHIC (text_option_bdrop),
		UI_ATTR_END
	);

   credits_button = create_ui_object
            (
               UI_TYPE_BUTTON,
               UI_ATTR_PARENT (main_screen),
					UI_ATTR_POSITION_START (0, 0.704),
					UI_ATTR_POSITION_END (0.637, 0.704),
					UI_ATTR_TIME_LENGTH (200),
					UI_ATTR_OFFSET_TIME (700),
					UI_ATTR_VIRTUAL_SIZE (0.185, 0.042),
					UI_ATTR_TEXT (get_trans ("Credits")),
					UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_22),
					UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
					UI_ATTR_FUNCTION (notify_main_credits_button),
      	      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
   	         UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
	            UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
	            UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
					UI_ATTR_HIGHLIGHTABLE (TRUE),
					UI_ATTR_CLEAR (TRUE),
               UI_ATTR_END
            );

	preprocess_translation_object_size (credits_button, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	set_text_option_backdrop_object (option_bdrop, credits_button);

	// ghost credits button

	x1 = get_ui_object_virtual_x (credits_button);
	x2 = get_ui_object_virtual_x_size (credits_button);

	y1 = 0.704;
	y2 = 0.042;

	ghost_credits_button = create_ui_object
									(
										UI_TYPE_AREA,
										UI_ATTR_PARENT (main_screen),
										UI_ATTR_VIRTUAL_POSITION (x1, y1),
										UI_ATTR_VIRTUAL_SIZE (x2, y2),
										UI_ATTR_CLEAR (TRUE),
										UI_ATTR_DRAWABLE (FALSE),
										UI_ATTR_END
									);


// Modder Credits by GCsDriver  08-12-2007

#if 0   // Disable until implemented properly
	i++;

	option_bdrop = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (main_screen),
		UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
		UI_ATTR_VIRTUAL_SIZE (TEXT_OPTION_BDROP_WIDTH, TEXT_OPTION_BDROP_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_OFFSET_TIME (0),
		UI_ATTR_TIME_LENGTH (500),
		UI_ATTR_TEXTURE_GRAPHIC (text_option_bdrop),
		UI_ATTR_END
	);

   modcredits_button = create_ui_object
            (
               UI_TYPE_BUTTON,
               UI_ATTR_PARENT (main_screen),
					UI_ATTR_POSITION_START (0, 0.883),
					UI_ATTR_POSITION_END (0.780, 0.883),
					UI_ATTR_TIME_LENGTH (200),
					UI_ATTR_OFFSET_TIME (700),
					UI_ATTR_VIRTUAL_SIZE (0.185, 0.042),
					UI_ATTR_TEXT (get_trans ("Mod-Team")),
					UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_22),
					UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
					UI_ATTR_FUNCTION (notify_main_modcredits_button),
      	      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
   	         UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
	            UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
	            UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
					UI_ATTR_HIGHLIGHTABLE (TRUE),
					UI_ATTR_CLEAR (TRUE),
               UI_ATTR_END
            );

	preprocess_translation_object_size (modcredits_button, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	set_text_option_backdrop_object (option_bdrop, modcredits_button);
#endif
// Modder Credits by GCsDriver end  08-12-2007

	/////////////////////////////////////////////////////////////////
	// Exit Button

	option_bdrop = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (main_screen),
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
				UI_ATTR_PARENT (main_screen),
				UI_ATTR_VIRTUAL_POSITION (OPTIONS_CANCEL_BUTTON_POS_X, OPTIONS_CANCEL_BUTTON_POS_Y),
				UI_ATTR_VIRTUAL_SIZE (OPTIONS_EXIT_BUTTON_X, OPTIONS_EXIT_BUTTON_Y),
				UI_ATTR_TEXT (get_trans("UI_EXIT")),
				UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
				UI_ATTR_FUNCTION (notify_main_screen_exit_button),
				UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
				UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
            UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
            UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
            UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
            UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
				UI_ATTR_HIGHLIGHTABLE (TRUE),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	set_text_option_backdrop_object (option_bdrop, change_obj);


#if 0
#ifndef COMMERCIAL

	if (check_cdrom_file_exists ("CONFIG.BIN"))
	{
		set_ui_object_text (registered_to_message, get_security_message ()),

		set_ui_object_drawable (registered_to_message, TRUE);
	}
	else
	{

		#ifdef INSTALL_FROM_CDROM

		debug_fatal ("Security Protection Failed");

		#endif
	}

#endif
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_main_screen (void)
{
	if (options_box_small)
	{
		destroy_texture_graphic (options_box_small);

		options_box_small = NULL;
	}

	if (options_box_medium)
	{
		destroy_texture_graphic (options_box_medium);

		options_box_medium = NULL;
	}

	if (options_box_large)
	{
		destroy_texture_graphic (options_box_large);

		options_box_large = NULL;
	}

	if (options_box_extra_large)
	{
		destroy_texture_graphic (options_box_extra_large);

		options_box_extra_large = NULL;
	}

	if (options_axis_bar)
	{
		destroy_texture_graphic (options_axis_bar);

		options_axis_bar = NULL;
	}
	
	if (text_box_graphic)
	{
		destroy_texture_graphic (text_box_graphic);

		text_box_graphic = NULL;
	}

	if (text_option_bdrop)
	{
		destroy_texture_graphic (text_option_bdrop);

		text_option_bdrop = NULL;
	}

	if (list_box_graphic)
	{
		destroy_texture_graphic (list_box_graphic);

		list_box_graphic = NULL;
	}

	if ( frontend_slider_bdrop_graphic )
	{
		destroy_texture_graphic ( frontend_slider_bdrop_graphic );

		frontend_slider_bdrop_graphic = NULL;
	}

	if ( frontend_slider_bar_graphic )
	{
		destroy_texture_graphic ( frontend_slider_bar_graphic );

		frontend_slider_bar_graphic = NULL;
	}

	if ( frontend_slider_bar_highlighted_graphic )
	{
		destroy_texture_graphic ( frontend_slider_bar_highlighted_graphic );

		frontend_slider_bar_highlighted_graphic = NULL;
	}

	if ( frontend_slider_bar_selected_graphic )
	{
		destroy_texture_graphic ( frontend_slider_bar_selected_graphic );

		frontend_slider_bar_selected_graphic = NULL;
	}

	if ( frontend_slider_up_graphic )
	{
		destroy_texture_graphic ( frontend_slider_up_graphic );

		frontend_slider_up_graphic = NULL;
	}

	if ( frontend_slider_up_highlighted_graphic )
	{
		destroy_texture_graphic ( frontend_slider_up_highlighted_graphic );

		frontend_slider_up_highlighted_graphic = NULL;
	}

	if ( frontend_slider_up_highlighted_graphic )
	{
		destroy_texture_graphic ( frontend_slider_up_highlighted_graphic );

		frontend_slider_up_highlighted_graphic = NULL;
	}

	if ( frontend_slider_down_graphic )
	{
		destroy_texture_graphic ( frontend_slider_down_graphic );

		frontend_slider_down_graphic = NULL;
	}

	if ( frontend_slider_down_highlighted_graphic )
	{
		destroy_texture_graphic ( frontend_slider_down_highlighted_graphic );

		frontend_slider_down_highlighted_graphic = NULL;
	}

	if ( frontend_slider_down_selected_graphic )
	{
		destroy_texture_graphic ( frontend_slider_down_selected_graphic );

		frontend_slider_down_selected_graphic = NULL;
	}

	if ( frontend_slider_up_selected_graphic )
	{
		destroy_texture_graphic ( frontend_slider_up_selected_graphic );

		frontend_slider_up_selected_graphic = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_frontend_slider_graphics (ui_object *parent)
{
	ui_object
		*temp,
		*slider;

	slider = get_ui_object_vslider (parent);

	ASSERT (slider);

	ASSERT (frontend_slider_bar_graphic);
	ASSERT (frontend_slider_bar_highlighted_graphic);
	ASSERT (frontend_slider_bar_selected_graphic);

	ASSERT (frontend_slider_up_graphic);
	ASSERT (frontend_slider_up_highlighted_graphic);
	ASSERT (frontend_slider_up_selected_graphic);

	ASSERT (frontend_slider_down_graphic);
	ASSERT (frontend_slider_down_highlighted_graphic);
	ASSERT (frontend_slider_down_selected_graphic);

	set_ui_object_texture_graphic (slider, frontend_slider_bdrop_graphic);

//	set_ui_object_clear (slider, TRUE);

	// get slider & set graphic
	temp = get_ui_object_child (slider);
	set_ui_object_texture_graphic (temp, frontend_slider_bar_graphic);
	set_ui_object_highlighted_texture_graphic (temp, frontend_slider_bar_highlighted_graphic);
	set_ui_object_selected_texture_graphic (temp, frontend_slider_bar_selected_graphic);
	set_ui_object_text (temp, "");

	// get up button & set graphic
	temp = get_ui_object_next (temp);
	set_ui_object_texture_graphic (temp, frontend_slider_up_graphic);
	set_ui_object_highlighted_texture_graphic (temp, frontend_slider_up_highlighted_graphic);
	set_ui_object_selected_texture_graphic (temp, frontend_slider_up_selected_graphic);
	set_ui_object_text (temp, "");

	// get down button & set graphic
	temp = get_ui_object_next (temp);
	set_ui_object_texture_graphic (temp, frontend_slider_down_graphic);
	set_ui_object_highlighted_texture_graphic (temp, frontend_slider_down_highlighted_graphic);
	set_ui_object_selected_texture_graphic (temp, frontend_slider_down_selected_graphic);
	set_ui_object_text (temp, "");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_common_main_options_button (ui_object *obj, void *arg)
{
	show_options_page ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_main_screen_exit_button (ui_object *obj, void *arg)
{

	if ((int) arg == BUTTON_STATE_DOWN)
	{

#if 0
		set_ui_object_graphic (obj, get_graphics_file_data (GRAPHICS_UI_APACHE_PLANNER_BACK_BUTTON_SELECTED));

		set_ui_object_redraw (main_screen, TRUE);
#endif
	}
	else if ((int) arg == BUTTON_STATE_UP)
	{

#if 0
		set_ui_object_graphic (obj, get_graphics_file_data (GRAPHICS_UI_APACHE_PLANNER_BACK_BUTTON_UNSELECTED));
#endif

		push_ui_screen ( exit_screen );
	}
	else
	{

#if 0
		set_ui_object_graphic (obj, get_graphics_file_data (GRAPHICS_UI_APACHE_PLANNER_BACK_BUTTON_UNSELECTED));

		set_ui_object_redraw (main_screen, TRUE);
#endif
	}

#if 0
	set_ui_object_graphic_type (obj, UI_OBJECT_ALPHA_GRAPHIC);
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_main_screen_background ( ui_object *obj, void *data )
{
/*
	object_3d_instance
		*apache;

	static float
		heading = 0,
		my_heading = 0;

	static int
		my_time = 3600*12;

	clear_zbuffer_screen ();

	set_3d_active_environment (main_3d_env);

	set_3d_infrared_mode ( main_3d_env, RENDER_CLEAR );

	set_3d_weathermode (main_3d_env, WEATHERMODE_DRY );

	set_3d_target_weathermode (main_3d_env, WEATHERMODE_DRY );

	set_3d_target_weathermode_transitional_status (main_3d_env, 0.0 );

	set_3d_time_of_day (main_3d_env, my_time );

	recalculate_3d_environment_settings (main_3d_env);

	visual_3d_vp->x = 0;
	visual_3d_vp->y = 0;
	visual_3d_vp->z = 0;
	visual_3d_vp->xv.x = 1;
	visual_3d_vp->xv.y = 0;
	visual_3d_vp->xv.z = 0;
	visual_3d_vp->yv.x = 0;
	visual_3d_vp->yv.y = 1;
	visual_3d_vp->yv.z = 0;
	visual_3d_vp->zv.x = 0;
	visual_3d_vp->zv.y = 0;
	visual_3d_vp->zv.z = 1;

	apache = construct_3d_object ( OBJECT_3D_MAIN_MENU );

	apache->vp.x = 0;
	apache->vp.y = 0;
	apache->vp.z = 20;

	get_3d_transformation_matrix ( visual_3d_vp->attitude, 0, rad ( 0 ) , my_heading );
	get_3d_transformation_matrix ( apache->vp.attitude, heading, rad ( 0 ) , rad ( 0 ) );

	my_time += 3600 / 100;

	if ( my_time >= 3600*24)
	{

		my_time -= 3600*24;
	}

	animate_screen_scene ( main_screen_t_value, apache );

	main_screen_t_value += 0.025;

	if ( main_screen_t_value > 1.0 )
	{

		main_screen_t_value = 1.0;
	}

	{

//		draw_3d_horizon ();

		insert_object_into_3d_scene ( OBJECT_3D_DRAW_TYPE_OBJECT, apache );

		draw_3d_sun ();

		draw_3d_scene ();
	}

	destruct_3d_object ( apache );
	*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
void animate_screen_scene ( float t, object_3d_instance *object )
{

	object_3d_scene_database_entry
		*scene;

	int
		count;

	ASSERT ( object );

	scene = &objects_3d_scene_database[object->object_number];

	for ( count = 0; count < scene->number_of_sub_objects; count++ )
	{

		recurse_animate_screen_scene ( t, &scene->sub_objects[count], &object->sub_objects[count] );
	}
}
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
void recurse_animate_screen_scene ( float t, object_3d_database_entry *scene, object_3d_sub_instance *object )
{

	int
		count;

	if ( scene->number_of_keyframes )
	{

		object_3d_sub_object_keyframe
			keyframe;

		calculate_keyframe ( scene->number_of_keyframes, scene->keyframes, &keyframe, t );

		object->relative_position.x = keyframe.x;
		object->relative_position.y = keyframe.y;
		object->relative_position.z = keyframe.z;

		object->relative_heading = keyframe.heading;
		object->relative_pitch = keyframe.pitch;
		object->relative_roll = keyframe.roll;

		object->relative_scale.x = keyframe.scale_x;
		object->relative_scale.y = keyframe.scale_y;
		object->relative_scale.z = keyframe.scale_z;
	}

	for ( count = 0; count < scene->number_of_sub_objects; count++ )
	{

		recurse_animate_screen_scene ( t, &scene->sub_objects[count], &object->sub_objects[count] );
	}
}
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_ui_list_spacing_proportional_to_font (ui_object *list, float scaling)
{
	int
		height;

	font_types
		old_font;

	float
		proportion,
		spacing;

	old_font = get_ui_font_type ();

	set_ui_font_type (get_ui_object_font_type (list));

	// get height

	height = ui_get_font_height ();

	// find proportion of ui_object used by font

	proportion = height / get_ui_object_y_size (list);

	// calc spacing value

	spacing = proportion * scaling;

	set_ui_object_list_box_y_space (list, spacing);

	set_ui_font_type (old_font);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


