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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ui_object
	*controller_area,
	*controller_text_area;

ui_object
	*cyclic_area,
	*collective_area,
	*pedal_area,
	*device_area,
	*reverse_throttle_area,
	*keyboard_assist_area,
	*cyclic_option_button,
	*collective_option_button,
	*pedal_option_button,
	*device_option_button,
	*device_graphic_area,
	*reverse_throttle_button,
	*keyboard_assist_option_button;

static unsigned char
	*option_joystick_text[2],
	*option_throttle_text[2],
	*option_pedal_text[2],
	*option_boolean_text[2],
	*no_joystick_text;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_joystick_selection (void);

void notify_cyclic_option_button ( ui_object *obj, void *arg );

void notify_collective_option_button ( ui_object *obj, void *arg );

void notify_pedal_option_button ( ui_object *obj, void *arg );

void notify_device_option_button ( ui_object *obj, void *arg );

void notify_reverse_throttle_option_button ( ui_object *obj, void *arg );

void notify_keyboard_assist_option_button ( ui_object *obj, void *arg );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_joystick_selection (void)
{

	// adjust selected joystick
	if ( get_global_joystick_device_index () == -1 )
	{

		// We had no joysticks installed last time - adjust now if we do have

		if ( number_of_joystick_devices )
		{

			set_global_joystick_device_index ( 0 );
		}
		else
		{

			set_global_collective_input ( KEYBOARD_INPUT );

			set_global_cyclic_input (KEYBOARD_INPUT);

			set_global_pedal_input (KEYBOARD_INPUT);
		}
	}
	else if ( get_global_joystick_device_index() >= number_of_joystick_devices )
	{

		// Last joystick selection is now not available

		if ( number_of_joystick_devices == 0 )
		{

			set_global_joystick_device_index ( -1 );

			set_global_collective_input ( KEYBOARD_INPUT );

			set_global_cyclic_input ( KEYBOARD_INPUT );

			set_global_pedal_input ( KEYBOARD_INPUT );
		}
		else
		{
	
			set_global_joystick_device_index ( 0 );
		}
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_show_controller_page (void)
{

	// initialise button text

	if ( (get_global_cyclic_input () == JOYSTICK_INPUT) && (number_of_joystick_devices) )
	{
		set_ui_object_text (cyclic_option_button, option_joystick_text[1]);
	}
	else
	{
		set_ui_object_text (cyclic_option_button, option_joystick_text[0]);
	}

	if ( (get_global_collective_input () == THROTTLE_INPUT) && (number_of_joystick_devices) )
	{
		set_ui_object_text (collective_option_button, option_throttle_text[1]);
	}
	else
	{
		set_ui_object_text (collective_option_button, option_throttle_text[0]);
	}

	if ( (get_global_pedal_input () == RUDDER_INPUT) && (number_of_joystick_devices) )
	{
		set_ui_object_text (pedal_option_button, option_pedal_text[1]);
	}
	else
	{
		set_ui_object_text (pedal_option_button, option_pedal_text[0]);
	}

	if (get_global_joystick_device_index () == -1)
	{
		set_ui_object_font_type (device_option_button, UI_FONT_THICK_ITALIC_ARIAL_18);

		set_ui_object_text (device_option_button, no_joystick_text);

		preprocess_translation_object_size (device_graphic_area, device_option_button, &no_joystick_text, 1, RESIZE_OPTION_CYCLE_BUTTON);
	}
	else
	{
		unsigned char
			*name[1];

		set_ui_object_text (device_option_button, joystick_devices[get_global_joystick_device_index ()].device_name);
	
		name[0] = &joystick_devices[get_global_joystick_device_index ()].device_name;
		
		preprocess_translation_object_size (device_graphic_area, device_option_button, name, 1, RESIZE_OPTION_CYCLE_BUTTON);
	}
	
	set_ui_object_text (reverse_throttle_button, option_boolean_text [get_global_dynamics_options_reverse_throttle_input ()]);

	set_ui_object_text (keyboard_assist_option_button, option_boolean_text [get_global_dynamics_options_keyboard_assistance ()]);

	display_options_page(OPTIONS_PAGE_CONTROLLER);

	#if DEBUG_MODULE
		debug_filtered_log("Inside show_controller_page");
	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void define_options_screen_controller_page_objects (void)
{
	int
		i = 0;
		
	float
		x1,
		y1,
		x2,
		y2;

	ui_object
		*page;

	ui_object
		*title_change_array [6],
		*check_array [6],
		*change_array [6];

	/////////////////////////////////////////////////////////////////
	// Initialise Button Strings
	
	option_joystick_text [0] = get_trans ("UI_KEYBOARD");
	option_joystick_text [1] = get_trans ("UI_JOYSTICK");

	option_throttle_text [0] = get_trans ("UI_KEYBOARD");
	option_throttle_text [1] = get_trans ("Throttle");

	option_pedal_text [0] = get_trans ("UI_KEYBOARD");
	option_pedal_text [1] = get_trans ("Rudder Pedals");

	no_joystick_text = get_trans ("UI_NONE_AVAILABLE");
	
	option_boolean_text [0] = get_trans ("Off");
	option_boolean_text [1] = get_trans ("On");

	/////////////////////////////////////////////////////////////////
	// Controller Area

	x1 = 0.0;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 1.0;

	options_page [OPTIONS_PAGE_CONTROLLER] = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (options_screen),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2, y2),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_DRAWABLE (FALSE),
				UI_ATTR_FUNCTION (NOTIFY_TYPE_NONE),
				UI_ATTR_END
			);

	page = options_page [OPTIONS_PAGE_CONTROLLER];

	// areas and titles

	// cyclic

	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (OPTION_AREA_OFFSET_Y * i);

   cyclic_area = create_ui_object
									(
										UI_TYPE_AREA,
										UI_ATTR_PARENT (page),
										UI_ATTR_VIRTUAL_POSITION (x1, y1),
										UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, OPTION_AREA_HEIGHT),
										UI_ATTR_CLEAR (TRUE),
										UI_ATTR_END
									);

	x1 = OPTION_TITLE_OFFSET_X;
	y1 = 0.0; 

	title_change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (cyclic_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_END
	);

   check_array[i] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array [i]),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("UI_CYCLIC")),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [i], check_array [i], NULL, 0, RESIZE_OPTION_BOX_TITLE);

	// collective

	i++;
	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (OPTION_AREA_OFFSET_Y * i);

   collective_area = create_ui_object
								(
									UI_TYPE_AREA,
									UI_ATTR_PARENT ( page ),
									UI_ATTR_VIRTUAL_POSITION (x1, y1),
									UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, OPTION_AREA_HEIGHT),
									UI_ATTR_CLEAR (TRUE),
									UI_ATTR_END
								);

	x1 = OPTION_TITLE_OFFSET_X;
	y1 = 0.0; 

	title_change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (collective_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_END
	);

   check_array[i] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array [i]),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("UI_COLLECTIVE")),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [i], check_array [i], NULL, 0, RESIZE_OPTION_BOX_TITLE);

	// pedal area
	
	i++;
	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (OPTION_AREA_OFFSET_Y * i);

   pedal_area = create_ui_object
								(
									UI_TYPE_AREA,
									UI_ATTR_PARENT ( page ),
									UI_ATTR_VIRTUAL_POSITION (x1, y1),
									UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, OPTION_AREA_HEIGHT),
									UI_ATTR_CLEAR (TRUE),
									UI_ATTR_END
								);

	x1 = OPTION_TITLE_OFFSET_X;
	y1 = 0.0; 

	title_change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (pedal_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_END
	);

   check_array[i] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array [i]),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("UI_PEDAL")),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [i], check_array [i], NULL, 0, RESIZE_OPTION_BOX_TITLE);

	//device area

	i++;
	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (OPTION_AREA_OFFSET_Y * i);

   device_area = create_ui_object
										(
											UI_TYPE_AREA,
											UI_ATTR_PARENT (page),
											UI_ATTR_VIRTUAL_POSITION (x1, y1),
											UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, OPTION_AREA_HEIGHT),
											UI_ATTR_CLEAR (TRUE),
											UI_ATTR_END
										);

	x1 = OPTION_TITLE_OFFSET_X;
	y1 = 0.0; 

	title_change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (device_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_END
	);

   check_array[i] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array [i]),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("UI_DEVICE")),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [i], check_array [i], NULL, 0, RESIZE_OPTION_BOX_TITLE);

	//reverse throttle area

	i++;
	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (OPTION_AREA_OFFSET_Y * i);

   reverse_throttle_area = create_ui_object
										(
											UI_TYPE_AREA,
											UI_ATTR_PARENT (page),
											UI_ATTR_VIRTUAL_POSITION (x1, y1),
											UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, OPTION_AREA_HEIGHT),
											UI_ATTR_CLEAR (TRUE),
											UI_ATTR_END
										);

	x1 = OPTION_TITLE_OFFSET_X;
	y1 = 0.0; 

	title_change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (reverse_throttle_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_END
	);

   check_array[i] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array [i]),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("Reverse Throttle")),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [i], check_array [i], NULL, 0, RESIZE_OPTION_BOX_TITLE);

	//keyboard_assist area

	i++;
	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + OPTION_AREA_OFFSET_Y * i;

   keyboard_assist_area = create_ui_object
								(
									UI_TYPE_AREA,
									UI_ATTR_PARENT ( page ),
									UI_ATTR_VIRTUAL_POSITION (x1, y1),
									UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, OPTION_AREA_HEIGHT),
									UI_ATTR_CLEAR (TRUE),
									UI_ATTR_END
								);

	x1 = OPTION_TITLE_OFFSET_X;
	y1 = 0.0; 

	title_change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (keyboard_assist_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START ( 255, 255, 255, 0 ),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

   check_array[i] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array[i]),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("Keyboard Assist")),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [i], check_array [i], NULL, 0, RESIZE_OPTION_BOX_TITLE);


	/////////////////////////////////////////////////////////////////
	// buttons

	i = 0;

	// cyclic

	change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (cyclic_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [i]) + get_ui_object_x_size_end (title_change_array [i]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_MEDIUM_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_medium),
		UI_ATTR_END
	);

	cyclic_option_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (cyclic_area),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
		UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
		UI_ATTR_VIRTUAL_POSITION (get_ui_object_x_end (change_array [i]) + OPTION_BUTTON_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_STATE (UI_OBJECT_STATE_OFF),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_cyclic_option_button),
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], cyclic_option_button, option_joystick_text, 2, RESIZE_OPTION_CYCLE_BUTTON);

	// collective
	
	i++;

	change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (collective_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [i]) + get_ui_object_x_size_end (title_change_array [i]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_MEDIUM_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_medium),
		UI_ATTR_END
	);

   collective_option_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (collective_area),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
		UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
		UI_ATTR_VIRTUAL_POSITION (get_ui_object_x_end (change_array [i]) + OPTION_BUTTON_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_collective_option_button),
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], collective_option_button, option_throttle_text, 2, RESIZE_OPTION_CYCLE_BUTTON);

	// pedal button
	
	i++;

	change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (pedal_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [i]) + get_ui_object_x_size_end (title_change_array [i]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_LARGE_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

   pedal_option_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (pedal_area),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
		UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
		UI_ATTR_VIRTUAL_POSITION (get_ui_object_x_end (change_array [i]) + OPTION_BUTTON_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_pedal_option_button),
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], pedal_option_button, option_pedal_text, 2, RESIZE_OPTION_CYCLE_BUTTON);

	//device button
	
	i++;

	change_array[i] = device_graphic_area = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (device_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [i]) + get_ui_object_x_size_end (title_change_array [i]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_LARGE_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

   device_option_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (device_area),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
		UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
		UI_ATTR_VIRTUAL_POSITION (get_ui_object_x_end (change_array [i]) + OPTION_BUTTON_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_device_option_button),
		UI_ATTR_END
	);

	//reverse throttle button
	
	i++;

	change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (reverse_throttle_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [i]) + get_ui_object_x_size_end (title_change_array [i]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_SMALL_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_small),
		UI_ATTR_END
	);

   reverse_throttle_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (reverse_throttle_area),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
		UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
		UI_ATTR_VIRTUAL_POSITION (get_ui_object_x_end (change_array [i]) + OPTION_BUTTON_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_reverse_throttle_option_button),
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], reverse_throttle_button, option_boolean_text, 2, RESIZE_OPTION_CYCLE_BUTTON);

	// keyboard_assist
	
	i++;

	change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (keyboard_assist_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [i]) + get_ui_object_x_size_end (title_change_array [i]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_SMALL_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START ( 255, 255, 255, 0 ),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_small),
		UI_ATTR_END
	);

   keyboard_assist_option_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (keyboard_assist_area),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
		UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
		UI_ATTR_VIRTUAL_POSITION (get_ui_object_x_end (change_array [i]) + OPTION_BUTTON_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_keyboard_assist_option_button),
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], keyboard_assist_option_button, option_boolean_text, 2, RESIZE_OPTION_CYCLE_BUTTON);

	recursively_set_object_time (page, OPTIONS_BUTTON_AREA_FADE_TIME, OPTIONS_BUTTON_AREA_OFFSET_TIME);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_cyclic_option_button ( ui_object *obj, void *arg )
{

	if ( (number_of_joystick_devices) && (get_global_cyclic_input () == KEYBOARD_INPUT) )
	{
			set_global_cyclic_input (JOYSTICK_INPUT);
			
			set_ui_object_text (cyclic_option_button, option_joystick_text[1]);
	}
	else
	{
		set_global_cyclic_input (KEYBOARD_INPUT);

		set_ui_object_text (cyclic_option_button, option_joystick_text[0]);
	}

	// don't leave text selected

	set_toggle_button_off (obj);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_collective_option_button ( ui_object *obj, void *arg )
{

	if ( (number_of_joystick_devices) && (get_global_collective_input () == KEYBOARD_INPUT) )
	{
			set_global_collective_input (THROTTLE_INPUT);
			
			set_ui_object_text (collective_option_button, option_throttle_text[1]);
	}
	else
	{
		set_global_collective_input (KEYBOARD_INPUT);
		
		set_ui_object_text (collective_option_button, option_throttle_text[0]);
	}

	// don't leave text selected

	set_toggle_button_off (obj);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_pedal_option_button ( ui_object *obj, void *arg )
{

	if ( (number_of_joystick_devices) && (get_global_pedal_input () == KEYBOARD_INPUT) )
	{
			set_global_pedal_input (RUDDER_INPUT);
			
			set_ui_object_text (pedal_option_button, option_pedal_text[1]);
	}
	else
	{
		set_global_pedal_input (KEYBOARD_INPUT);
		
		set_ui_object_text (pedal_option_button, option_pedal_text[0]);
	}

	// don't leave text selected

	set_toggle_button_off (obj);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_device_option_button ( ui_object *obj, void *arg )
{
	unsigned char
		*name[1];

	if (number_of_joystick_devices > 1)
	{
		if ( get_global_joystick_device_index () < (number_of_joystick_devices - 1) )
		{
			set_global_joystick_device_index (get_global_joystick_device_index () + 1);
		}
		else
		{
			set_global_joystick_device_index (0);
		}

		set_ui_object_text (device_option_button, joystick_devices[get_global_joystick_device_index ()].device_name);

		name[0] = &joystick_devices[get_global_joystick_device_index ()].device_name;

		preprocess_translation_object_size (device_graphic_area, device_option_button, name, 1, RESIZE_OPTION_CYCLE_BUTTON);
	}

	// don't leave text selected

	set_toggle_button_off (obj);
	
	#if DEBUG_MODULE
		debug_filtered_log ("no. jd's:%d  jd index:%d", number_of_joystick_devices, get_global_joystick_device_index ());
	#endif
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_reverse_throttle_option_button ( ui_object *obj, void *arg )
{

	int
		selection;

	selection = !get_global_dynamics_options_reverse_throttle_input ();
	
	set_global_dynamics_options_reverse_throttle_input (selection);

	set_ui_object_text (reverse_throttle_button, option_boolean_text [selection]);

	set_current_dynamics_options (DYNAMICS_OPTIONS_REVERSE_THROTTLE_INPUT, get_global_dynamics_options_reverse_throttle_input());

	// don't leave text selected

	set_toggle_button_off (obj);

	#ifdef DEBUG_MODULE
		debug_filtered_log ("reverse throttle: %d", get_global_dynamics_options_reverse_throttle_input ());
	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_keyboard_assist_option_button ( ui_object *obj, void *arg )
{
	set_global_dynamics_options_keyboard_assistance (!get_global_dynamics_options_keyboard_assistance ());

	set_ui_object_text (keyboard_assist_option_button, option_boolean_text [get_global_dynamics_options_keyboard_assistance ()]);

	set_current_dynamics_options (DYNAMICS_OPTIONS_KEYBOARD_ASSISTANCE, get_global_dynamics_options_keyboard_assistance());

	// don't leave text selected

	set_toggle_button_off (obj);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


