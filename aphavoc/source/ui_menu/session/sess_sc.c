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



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

texture_graphic
	*session_screen_graphic = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ui_object
   *session_screen_next_bdrop,
   *session_screen_back_button,
   *session_screen_next_button,
   *session_screen_delete_button,
   *session_screen_rename_button,
   *session_info_list,
   *session_list_bdrop,
   *session_list_area,
   *session_list,
   *session_briefing_overlay,
   *session_briefing_area,
   *session_name_entry_area,
   *session_name_input,
   *session_screen;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_session_screen (void)
{

   ui_object
		*option_bdrop;

	float
		x1,
		x2,
		y1,
		y2;

	x1 = 0.0;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 1.0;

	session_screen = create_ui_object
							(
								UI_TYPE_SCREEN,
								UI_ATTR_VIRTUAL_POSITION (x1, y1),
								UI_ATTR_VIRTUAL_SIZE (x2, y2),
								UI_ATTR_COLOUR_START (255,255,255,64),
								UI_ATTR_COLOUR_END (255,255,255,255),
								UI_ATTR_TIME_LENGTH (500),
								UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_EITHER),
								UI_ATTR_FUNCTION (notify_session_screen),
								UI_ATTR_END
							);

	// Screen title text
   create_ui_object
            (
               UI_TYPE_TEXT,
               UI_ATTR_PARENT (session_screen),
					UI_ATTR_TIME_LENGTH (0),
					UI_ATTR_OFFSET_TIME (0),
               UI_ATTR_VIRTUAL_POSITION (TITLE_TEXT_POSITION_X, TITLE_TEXT_POSITION_Y),
					UI_ATTR_VIRTUAL_SIZE (TITLE_TEXT_WIDTH, TITLE_TEXT_HEIGHT),
					UI_ATTR_TEXT (get_trans ("Session")),
					UI_ATTR_FONT_TYPE (UI_FONT_IMPACT_22),
					UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_BOTTOM),
               UI_ATTR_FONT_COLOUR_START (ui_screen_title_text_colour.r, ui_screen_title_text_colour.g, ui_screen_title_text_colour.b, 0),
               UI_ATTR_FONT_COLOUR_END (ui_screen_title_text_colour.r, ui_screen_title_text_colour.g, ui_screen_title_text_colour.b, 255),
					UI_ATTR_HIGHLIGHTABLE (FALSE),
					UI_ATTR_CLEAR (TRUE),
               UI_ATTR_END
            );

   ////////////////////////////////////////////////////////
   // session info / briefing

	x1 = 0.506;
	y1 = 0.126;
	x2 = 0.466;
	y2 = 0.372;

	session_briefing_overlay = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (session_screen),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2, y2),
				UI_ATTR_TEXTURE_GRAPHIC (text_box_graphic),
				UI_ATTR_END
			);

	x1 = 0.02;
	y1 = 0.05;
	x2 = 0.96;
	y2 = 0.9;

	session_briefing_area = create_ui_object
										(
											UI_TYPE_AREA,
											UI_ATTR_PARENT (session_briefing_overlay),
											UI_ATTR_VIRTUAL_POSITION (x1, y1),
											UI_ATTR_VIRTUAL_SIZE (x2, y2),
											UI_ATTR_VSLIDER (0, 0, ui_get_font_height (UI_FONT_ARIAL_10)),
											UI_ATTR_CLEAR (TRUE),
											UI_ATTR_END
										);

	////////////////////////////////////////////////
	//	Slider Graphics

	set_frontend_slider_graphics (session_briefing_area);

   session_info_list = create_ui_object
            (
               UI_TYPE_LIST_BOX,
               UI_ATTR_PARENT (session_briefing_area),
					UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
					UI_ATTR_VIRTUAL_SIZE (0.92, 1.0),
					UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
					UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_NONE),
					UI_ATTR_CLEAR (TRUE),
               UI_ATTR_END
           );

	////////////////////////////////////////////////
	// session list
	////////////////////////////////////////////////

	x1 = 0.003;
	y1 = 0.126;
	x2 = 0.466;
	y2 = 0.677;
	

   session_list_bdrop = create_ui_object
						(
							UI_TYPE_AREA,
							UI_ATTR_PARENT (session_screen),
							UI_ATTR_VIRTUAL_POSITION (x1, y1),
							UI_ATTR_VIRTUAL_SIZE (x2, y2),
							UI_ATTR_TEXTURE_GRAPHIC (list_box_graphic),
							UI_ATTR_END
						);

	x1 = 0.02;
	y1 = 0.1;
	x2 = 0.96;
	y2 = 0.86;
	
   session_list_area = create_ui_object
						(
							UI_TYPE_AREA,
							UI_ATTR_PARENT (session_list_bdrop),
							UI_ATTR_VIRTUAL_POSITION (x1, y1),
							UI_ATTR_VIRTUAL_SIZE (x2, y2),
							UI_ATTR_VSLIDER (0, 1000, ui_get_font_height (UI_FONT_ARIAL_18)),
							UI_ATTR_CLEAR (TRUE),
							UI_ATTR_END
						);

	set_frontend_slider_graphics (session_list_area);

	x1 = 0.046;
	y1 = 0.0;
	x2 = 0.862;
	y2 = 1.0;
	
   session_list = create_ui_object
						(
							UI_TYPE_LIST_BOX,
							UI_ATTR_PARENT (session_list_area),
							UI_ATTR_VIRTUAL_POSITION (x1, y1),
							UI_ATTR_VIRTUAL_SIZE (x2, y2),
		            	UI_ATTR_FONT_COLOUR_START (ui_list_text_default_colour.r, ui_list_text_default_colour.g, ui_list_text_default_colour.b, 0),
   		         	UI_ATTR_FONT_COLOUR_END (ui_list_text_default_colour.r, ui_list_text_default_colour.g, ui_list_text_default_colour.b, 255),
      		      	UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_list_text_hilite_colour.r, ui_list_text_hilite_colour.g, ui_list_text_hilite_colour.b, 0),
         		   	UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_list_text_hilite_colour.r, ui_list_text_hilite_colour.g, ui_list_text_hilite_colour.b, 255),
							UI_ATTR_HIGHLIGHTABLE (TRUE),
							UI_ATTR_LIST_BOX_Y_SPACE (0),
							UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
							UI_ATTR_CLEAR (TRUE),
							UI_ATTR_FUNCTION (session_list_function),
							UI_ATTR_END
						);

	set_ui_list_spacing_proportional_to_font (session_list, -0.2);

	///////////////////////////////////////////////
	// Rename Button

	x1 = 0.05;
	y1 = 0.029;
	x2 = 0.45;
	y2 = 0.038;

   session_screen_rename_button = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (session_list_bdrop),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (x2, y2),
     	UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
    	UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
     	UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
    	UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_TEXT (get_trans ("RENAME")),
		UI_ATTR_FUNCTION (notify_session_rename_button),
		UI_ATTR_CLEAR ( TRUE ),
		UI_ATTR_DRAWABLE (FALSE),
		UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_END
	);

	////////////////////////////////////////////////
	//	Delete Button 

	x1 = 0.5;
	y1 = 0.029;
	x2 = 0.45;
	y2 = 0.038;

	session_screen_delete_button = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (session_list_bdrop),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (x2, y2),
		UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
   	UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
    	UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
     	UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
    	UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_TEXT (get_trans ("DELETE")),
		UI_ATTR_FUNCTION (notify_session_delete_button),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_DRAWABLE (FALSE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_END
	);

	x1 = get_ui_object_virtual_x (session_list);
	y1 = get_ui_object_virtual_y (session_list);
	x2 = get_ui_object_virtual_x_size (session_list);
	y2 = get_ui_object_virtual_y_size (session_list);
	
   session_name_entry_area = create_ui_object
            (
               UI_TYPE_AREA,
               UI_ATTR_PARENT (session_list_area),
					UI_ATTR_VIRTUAL_POSITION (x1, y1),
					UI_ATTR_VIRTUAL_SIZE (x2, y2),
					UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_18),
					UI_ATTR_CLEAR (TRUE),
					UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_NONE),
               UI_ATTR_END
            );

	x1 = 0.0;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 0.25;

   session_name_input = create_ui_object
            (
               UI_TYPE_INPUT,
               UI_ATTR_PARENT (session_name_entry_area),
					UI_ATTR_VIRTUAL_POSITION (x1, y1),
					UI_ATTR_VIRTUAL_SIZE (x2, y2),
					UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_18),
            	UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
            	UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
					UI_ATTR_FUNCTION (session_name_input_function),
					UI_ATTR_CLEAR (FALSE),
               UI_ATTR_END
            );



	/////////////////////////////////////////////////////////////////
	// Ok Button

	session_screen_next_bdrop = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (session_screen),
		UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
		UI_ATTR_VIRTUAL_SIZE (TEXT_OPTION_BDROP_WIDTH, TEXT_OPTION_BDROP_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 255),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (text_option_bdrop),
		UI_ATTR_OFFSET_TIME (0),
		UI_ATTR_TIME_LENGTH (500),
		UI_ATTR_END
	);

	session_screen_next_button = create_ui_object
			(
				UI_TYPE_BUTTON,
				UI_ATTR_PARENT (session_screen),
				UI_ATTR_VIRTUAL_POSITION (OPTIONS_OK_BUTTON_POS_X, OPTIONS_OK_BUTTON_POS_Y),
				UI_ATTR_VIRTUAL_SIZE (OPTIONS_OK_BUTTON_X, OPTIONS_OK_BUTTON_Y),
				UI_ATTR_TEXT (get_trans("UI_OK")),
				UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
				UI_ATTR_FUNCTION (notify_session_next_button),
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
			
	set_text_option_backdrop_object (session_screen_next_bdrop, session_screen_next_button);

	/////////////////////////////////////////////////////////////////
	// Cancel Button

	option_bdrop = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (session_screen),
		UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
		UI_ATTR_VIRTUAL_SIZE (TEXT_OPTION_BDROP_WIDTH, TEXT_OPTION_BDROP_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 255),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (text_option_bdrop),
		UI_ATTR_OFFSET_TIME (0),
		UI_ATTR_TIME_LENGTH (500),
		UI_ATTR_END
	);

	session_screen_back_button = create_ui_object
			(
				UI_TYPE_BUTTON,
				UI_ATTR_PARENT (session_screen),
				UI_ATTR_VIRTUAL_POSITION (OPTIONS_CANCEL_BUTTON_POS_X, OPTIONS_CANCEL_BUTTON_POS_Y),
				UI_ATTR_VIRTUAL_SIZE (OPTIONS_CANCEL_BUTTON_X, OPTIONS_CANCEL_BUTTON_Y),
				UI_ATTR_TEXT (get_trans("UI_CANCEL")),
				UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
				UI_ATTR_FUNCTION (notify_session_back_button),
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
			
	set_text_option_backdrop_object (option_bdrop, session_screen_back_button);

	//
	// Create the briefing
	//

   ////////////////////////////////////////////////////////
   // setup parameter objects

	define_session_parameter_objects ();

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
