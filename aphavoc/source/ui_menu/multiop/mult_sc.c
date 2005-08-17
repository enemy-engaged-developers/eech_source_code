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

// screen objects
ui_object
   *multi_player_setup_area,
	*connection_type_bdrop,
	*connection_type_area,
	*connection_type_button;

// areas
ui_object
	*serial_parameters_area,
	*modem_parameters_area,
	*tcpip_parameters_area;

// ip objects
ui_object
	*ip_address_title,
	*ip_address_text_area,
	*ip_address_text_obj,
	*ip_address_text_input;

// serial objects
ui_object
	*com_port_area,
	*com_port_button,
	*baud_rate_area,
	*baud_rate_button,
	*stop_bits_area,
	*stop_bits_button,
	*parity_area,
	*parity_button,
	*flow_area,
	*flow_button,
	*serial_status_text;

// modem objects
ui_object
	*modem_type_area,
	*ghost_multiplayer_modem_area,
	*ghost_multiplayer_modem_area2,
	*modem_type_button,
	*phone_number_area,
	*phone_number_text_area,
	*phone_number_text_obj,
	*phone_number_text_input,
	*modem_call_buttons_area,
	*modem_answer_button,
	*modem_dial_button,
	*modem_cancel_button,
	*modem_status_text;

const char
	*baud_rate_text[4],
	*stop_bits_text[3],
	*parity_text[4],
	*flow_text[5];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_com_port_function ( ui_object *obj, void *arg );

static void notify_baud_rate_function ( ui_object *obj, void *arg );

static void notify_stop_bits_function ( ui_object *obj, void *arg );

static void notify_parity_function ( ui_object *obj, void *arg );

static void notify_flow_function ( ui_object *obj, void *arg );

static void multi_text_input_function ( ui_object *obj, void *arg );

static void get_text_input (ui_object *obj, void *arg);

static void notify_modem_type_function ( ui_object *obj, void *arg );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void define_multi_player_setup_objects (void)
{
	int
		i,
		j,
		last_modem_title_object_no;

	float
		x1,
		y1,
		x2,
		y2,
		mb_width;

	char
		text[128];
	const char
		*translations [3];

	ui_object
		*title_change_array [12],
		*check_array [12],
		*change_array [12];

	/////////////////////////////////////////////////////////////////
	// Initialise Button Strings

	baud_rate_text[0] = "19200";
	baud_rate_text[1] = "38400";
	baud_rate_text[2] = "57600";
	baud_rate_text[3] = "115200";
	
	stop_bits_text[0] = "1";
	stop_bits_text[1] = "1.5";
	stop_bits_text[2] = "2";
	
	parity_text[0] = get_trans ("None");
	parity_text[1] = "Even";
	parity_text[2] = "Odd";
	parity_text[3] = "Mark";
	
	flow_text[0] = get_trans ("None");
	flow_text[1] = "Xon/Xoff";
	flow_text[2] = "RTS";
	flow_text[3] = "DTR";
	flow_text[4] = "RTS/DTR";

	translations [0] = get_trans ("MP_DIAL");
	translations [1] = get_trans ("MP_CANCEL");
	translations [2] = get_trans ("MP_ANSWER");

	j = 0;
	i = 1;

	x2 = y2 = 1.0;

	/////////////////////////////////////////////////////////////////

	multi_player_setup_area = create_ui_object
											(
												UI_TYPE_AREA,
							               UI_ATTR_PARENT (options_screen),
												UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
												UI_ATTR_VIRTUAL_SIZE (1.0, 1.0),
												UI_ATTR_OFFSET_TIME (0),
												UI_ATTR_TIME_LENGTH (0),
												UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_EITHER),
												UI_ATTR_CLEAR (TRUE),
												UI_ATTR_END
											);

	/////////////////////////////////////////////////////////////////
	// Serial SP stuff
	//

	serial_parameters_area = create_ui_object
										(
											UI_TYPE_AREA,
											UI_ATTR_PARENT (multi_player_setup_area),
											UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
											UI_ATTR_VIRTUAL_SIZE (1.0, 1.0),
											UI_ATTR_CLEAR ( TRUE ),
											UI_ATTR_END
										);

	// com_port objects

//	y1 += OPTION_AREA_OFFSET_Y + 0.0375;

	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (OPTION_AREA_OFFSET_Y * i) + 0.0375;

   com_port_area = create_ui_object
									(
										UI_TYPE_AREA,
										UI_ATTR_PARENT (serial_parameters_area),
										UI_ATTR_VIRTUAL_POSITION (x1, y1),
										UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, OPTION_AREA_HEIGHT),
										UI_ATTR_CLEAR (TRUE),
					               UI_ATTR_COLOUR_START (0,0,0,0),
            					   UI_ATTR_COLOUR_END (255,255,255,255),
										UI_ATTR_END
									);

	x1 = OPTION_TITLE_OFFSET_X;
	y1 = 0.0; 

	title_change_array[j] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (com_port_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255,255,255,0),
      UI_ATTR_COLOUR_END (255,255,255,255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

   check_array[j] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array [j]),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("MP_COM_PORT") ),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [j], check_array [j], NULL, 0, RESIZE_OPTION_BOX_TITLE);

	// baud_rate objects

	i++;
	j++;

	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (OPTION_AREA_OFFSET_Y * i) + 0.0375;

   baud_rate_area = create_ui_object
									(
										UI_TYPE_AREA,
										UI_ATTR_PARENT (serial_parameters_area),
										UI_ATTR_VIRTUAL_POSITION (x1, y1),
										UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, OPTION_AREA_HEIGHT),
										UI_ATTR_CLEAR (TRUE),
					               UI_ATTR_COLOUR_START (0,0,0,0),
            					   UI_ATTR_COLOUR_END (255,255,255,255),
										UI_ATTR_END
									);

	x1 = OPTION_TITLE_OFFSET_X;
	y1 = 0.0; 

	title_change_array[j] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (baud_rate_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255,255,255,0),
      UI_ATTR_COLOUR_END (255,255,255,255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

   check_array[j] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array [j]),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("MP_BAUD_RATE") ),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [j], check_array [j], NULL, 0, RESIZE_OPTION_BOX_TITLE);

	// stop_bit objects

	i++;
	j++;

	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (OPTION_AREA_OFFSET_Y * i) + 0.0375;

   stop_bits_area = create_ui_object
									(
										UI_TYPE_AREA,
										UI_ATTR_PARENT (serial_parameters_area),
										UI_ATTR_VIRTUAL_POSITION (x1, y1),
										UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, OPTION_AREA_HEIGHT),
										UI_ATTR_CLEAR (TRUE),
					               UI_ATTR_COLOUR_START (0,0,0,0),
            					   UI_ATTR_COLOUR_END (255,255,255,255),
										UI_ATTR_END
									);

	x1 = OPTION_TITLE_OFFSET_X;
	y1 = 0.0; 

	title_change_array[j] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (stop_bits_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255,255,255,0),
      UI_ATTR_COLOUR_END (255,255,255,255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

   check_array[j] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array [j]),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("MP_STOP_BITS") ),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [j], check_array [j], NULL, 0, RESIZE_OPTION_BOX_TITLE);

	// parity objects

	i++;
	j++;

	x1 = 0.0;
	y1 = OPTION_TITLE_OFFSET_Y + (OPTION_AREA_OFFSET_Y * i) + 0.0375;

   parity_area = create_ui_object
									(
										UI_TYPE_AREA,
										UI_ATTR_PARENT (serial_parameters_area),
										UI_ATTR_VIRTUAL_POSITION (x1, y1),
										UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, OPTION_AREA_HEIGHT),
										UI_ATTR_CLEAR (TRUE),
					               UI_ATTR_COLOUR_START (0,0,0,0),
            					   UI_ATTR_COLOUR_END (255,255,255,255),
										UI_ATTR_END
									);

	x1 = OPTION_TITLE_OFFSET_X;
	y1 = 0.0; 

	title_change_array[j] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (parity_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255,255,255,0),
      UI_ATTR_COLOUR_END (255,255,255,255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

   check_array[j] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array [j]),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("MP_PARITY") ),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [j], check_array [j], NULL, 0, RESIZE_OPTION_BOX_TITLE);

	// flow objects

	i++;
	j++;

	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (OPTION_AREA_OFFSET_Y * i) + 0.0375;

   flow_area = create_ui_object
									(
										UI_TYPE_AREA,
										UI_ATTR_PARENT (serial_parameters_area),
										UI_ATTR_VIRTUAL_POSITION (x1, y1),
										UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, OPTION_AREA_HEIGHT),
										UI_ATTR_CLEAR (TRUE),
					               UI_ATTR_COLOUR_START (0,0,0,0),
            					   UI_ATTR_COLOUR_END (255,255,255,255),
										UI_ATTR_END
									);

	x1 = OPTION_TITLE_OFFSET_X;
	y1 = 0.0; 

	title_change_array[j] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (flow_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255,255,255,0),
      UI_ATTR_COLOUR_END (255,255,255,255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

   check_array[j] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array [j]),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("MP_HANDSHAKE") ),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [j], check_array [j], NULL, 0, RESIZE_OPTION_BOX_TITLE);

	/////////////////////////////////////////////////////////////////
	// Modem SP stuff
	//

	i = 1;
	j++;
	
	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (OPTION_AREA_OFFSET_Y * i) + 0.0375;

	modem_parameters_area = create_ui_object
									(
										UI_TYPE_AREA,
										UI_ATTR_PARENT (multi_player_setup_area),
										UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
										UI_ATTR_VIRTUAL_SIZE (x2, y2),
										UI_ATTR_CLEAR ( TRUE ),
										UI_ATTR_END
									);


	// modem type objects
	
	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (OPTION_AREA_OFFSET_Y * i) + 0.0375;

   modem_type_area = create_ui_object
									(
										UI_TYPE_AREA,
										UI_ATTR_PARENT (modem_parameters_area),
										UI_ATTR_VIRTUAL_POSITION (x1, y1),
										UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, OPTION_AREA_HEIGHT),
										UI_ATTR_CLEAR (TRUE),
					               UI_ATTR_COLOUR_START (0,0,0,0),
            					   UI_ATTR_COLOUR_END (255,255,255,255),
										UI_ATTR_END
									);

	x1 = OPTION_TITLE_OFFSET_X;
	y1 = 0.0; 

	title_change_array[j] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (modem_type_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255,255,255,0),
      UI_ATTR_COLOUR_END (255,255,255,255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

   check_array[j] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array [j]),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("MP_MODEM") ),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [j], check_array [j], NULL, 0, RESIZE_OPTION_BOX_TITLE);

	// phone number
	
	i++;
	j++;

	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (OPTION_AREA_OFFSET_Y * i) + 0.0375;

  	phone_number_area = create_ui_object
									(
										UI_TYPE_AREA,
										UI_ATTR_PARENT (modem_parameters_area),
										UI_ATTR_VIRTUAL_POSITION (x1, y1),
										UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, OPTION_AREA_HEIGHT),
										UI_ATTR_CLEAR (TRUE),
					               UI_ATTR_COLOUR_START (0,0,0,0),
            					   UI_ATTR_COLOUR_END (255,255,255,255),
										UI_ATTR_END
									);

	x1 = OPTION_TITLE_OFFSET_X;
	y1 = 0.0; 

	title_change_array[j] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (phone_number_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255,255,255,0),
      UI_ATTR_COLOUR_END (255,255,255,255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

   check_array[j] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array [j]),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("MP_PHONE_NUMBER") ),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [j], check_array [j], NULL, 0, RESIZE_OPTION_BOX_TITLE);

	// modem connection objects

	// connection type area - keep at bottom of function so it is on top of other areas

	i = 0;
	j++;

	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (OPTION_AREA_OFFSET_Y * i);

   connection_type_area = create_ui_object
									(
										UI_TYPE_AREA,
										UI_ATTR_PARENT (multi_player_setup_area),
										UI_ATTR_VIRTUAL_POSITION (x1, y1),
										UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, OPTION_AREA_HEIGHT),
										UI_ATTR_CLEAR (TRUE),
					               UI_ATTR_COLOUR_START (0,0,0,0),
            					   UI_ATTR_COLOUR_END (255,255,255,255),
										UI_ATTR_END
									);

	x1 = OPTION_TITLE_OFFSET_X;
	y1 = 0.0; 

	title_change_array[j] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (connection_type_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255,255,255,0),
      UI_ATTR_COLOUR_END (255,255,255,255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

   check_array[j] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array [j]),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("MP_CONNECTION") ),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [j], check_array [j], NULL, 0, RESIZE_OPTION_BOX_TITLE);

	// store index for button creation later
	last_modem_title_object_no = j;

	/////////////////////////////////////////////////////////////////
	// Objects for input of IP address
	//

	i = 1;
	j++;

	x1 = 0.0;
	y1 = OPTION_TITLE_OFFSET_Y + (OPTION_AREA_OFFSET_Y * i) + 0.0375;

   tcpip_parameters_area = create_ui_object
									(
										UI_TYPE_AREA,
										UI_ATTR_PARENT (multi_player_setup_area),
										UI_ATTR_VIRTUAL_POSITION (x1, y1),
										UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, OPTION_AREA_HEIGHT),
										UI_ATTR_CLEAR (TRUE),
					               UI_ATTR_COLOUR_START (0,0,0,0),
            					   UI_ATTR_COLOUR_END (255,255,255,255),
										UI_ATTR_END
									);

	x1 = OPTION_TITLE_OFFSET_X;
	y1 = 0.0; 

	title_change_array[j] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (tcpip_parameters_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255,255,255,0),
      UI_ATTR_COLOUR_END (255,255,255,255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

   check_array[j] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array [j]),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("MP_IP_ADDRESS") ),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [j], check_array [j], NULL, 0, RESIZE_OPTION_BOX_TITLE);



	/////////////////////////////////////////////////////////////////
	// Buttons
	/////////////////////////////////////////////////////////////////

	i = 1;
	j = 0;


	/////////////////////////////////////////////////////////////////
	// com_port objects

	change_array[j] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (com_port_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [0]) + get_ui_object_x_size_end (title_change_array [0]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_SMALL_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255,255,255,0),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_small),
		UI_ATTR_END
	);

   com_port_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (com_port_area),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
		UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
		UI_ATTR_VIRTUAL_POSITION (get_ui_object_x_end (change_array [j]) + OPTION_BUTTON_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_com_port_function),
		UI_ATTR_END
	);

	// baud_rate objects

	j++;

	change_array[j] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (baud_rate_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [0]) + get_ui_object_x_size_end (title_change_array [0]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_MEDIUM_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255,255,255,0),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_medium),
		UI_ATTR_END
	);

   baud_rate_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (baud_rate_area),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
		UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
		UI_ATTR_VIRTUAL_POSITION (get_ui_object_x_end (change_array [j]) + OPTION_BUTTON_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_baud_rate_function),
		UI_ATTR_END
	);

	// stop_bit objects

	j++;

	change_array[j] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (stop_bits_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [0]) + get_ui_object_x_size_end (title_change_array [0]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_SMALL_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255,255,255,0),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_small),
		UI_ATTR_END
	);

   stop_bits_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (stop_bits_area),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
		UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
		UI_ATTR_VIRTUAL_POSITION (get_ui_object_x_end (change_array [j]) + OPTION_BUTTON_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_stop_bits_function),
		UI_ATTR_END
	);

	// parity objects

	j++;

	change_array[j] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (parity_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [0]) + get_ui_object_x_size_end (title_change_array [0]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_SMALL_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255,255,255,0),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_small),
		UI_ATTR_END
	);

   parity_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (parity_area),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
		UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
		UI_ATTR_VIRTUAL_POSITION (get_ui_object_x_end (change_array [j]) + OPTION_BUTTON_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_parity_function),
		UI_ATTR_END
	);

	// total hack for the spanish

	if (get_global_current_language () == LANGUAGE_SPANISH)
	{
		set_ui_object_virtual_x_size (change_array [j], OPTION_BOX_MEDIUM_WIDTH);

		set_ui_object_texture_graphic (change_array [j], options_box_medium);
	}


	// flow objects

	j++;

	change_array[j] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (flow_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [0]) + get_ui_object_x_size_end (title_change_array [0]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_MEDIUM_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255,255,255,0),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_medium),
		UI_ATTR_END
	);

   flow_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (flow_area),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
		UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
		UI_ATTR_VIRTUAL_POSITION (get_ui_object_x_end (change_array [j]) + OPTION_BUTTON_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_flow_function),
		UI_ATTR_END
	);

	x1 = get_ui_object_x_end (title_change_array[0]);
	y1 = OPTION_TITLE_OFFSET_Y + (OPTION_AREA_OFFSET_Y * 6) + 0.0375;

	serial_status_text = create_ui_object
								(
									UI_TYPE_TEXT,
									UI_ATTR_PARENT (serial_parameters_area),
									UI_ATTR_VIRTUAL_POSITION (x1, y1),
									UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
									UI_ATTR_TEXT (""),
									UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
  							    	UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
							      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
									UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_NONE),
									UI_ATTR_END
								);

	/////////////////////////////////////////////////////////////////
	// Modem SP stuff
	//

	j++;

	change_array[j] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (modem_type_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [0]) + get_ui_object_x_size_end (title_change_array [0]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_EXTRA_LARGE_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255,255,255,0),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_extra_large),
		UI_ATTR_END
	);

   modem_type_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (modem_type_area),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
		UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
		UI_ATTR_VIRTUAL_POSITION (get_ui_object_x_end (change_array [j]) + OPTION_BUTTON_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_modem_type_function),
		UI_ATTR_END
	);


	// phone number
	
	j++;

	change_array[j] = phone_number_text_area = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (phone_number_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [0]) + get_ui_object_x_size_end (title_change_array [0]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_LARGE_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255,255,255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

	// Actual text

   phone_number_text_obj = create_ui_object
									(
										UI_TYPE_AREA,
										UI_ATTR_PARENT (phone_number_area),
										UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (change_array [j]) + OPTION_BUTTON_TEXT_OFFSET_X), 0.0),
										UI_ATTR_VIRTUAL_SIZE (1.0, 1.0),
										UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
      								UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      								UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      								UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      								UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
										UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
										UI_ATTR_TEXT (global_options.phone_number),
										UI_ATTR_HIGHLIGHTABLE (TRUE),
										UI_ATTR_CLEAR (TRUE),
										UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
										UI_ATTR_FUNCTION (get_text_input),
										UI_ATTR_END
									);

	// Text input

	phone_number_text_input = create_ui_object
									(
										UI_TYPE_INPUT,
										UI_ATTR_PARENT (phone_number_area),
										UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (change_array [j]) + OPTION_BUTTON_TEXT_OFFSET_X), OPTION_BOX_TEXT_OFFSET_Y),
										UI_ATTR_VIRTUAL_SIZE (1.0, 1.0),
										UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
										UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
      								UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      								UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
										UI_ATTR_STATE (UI_OBJECT_STATE_OFF),
										UI_ATTR_FUNCTION (multi_text_input_function),
										UI_ATTR_END
									);


	set_limit_input_length (phone_number_text_input, FALSE);

	set_ui_object_item_number (phone_number_text_input, (int) phone_number_text_obj);
	
	set_ui_object_item_number (phone_number_text_obj, (int) phone_number_text_input);

	//modem

	j++;


	x1 = 0.0;
	y1 = get_ui_object_y_end (phone_number_area);
	y1 += OPTION_AREA_OFFSET_Y + 0.0375;


	change_array[j] = modem_call_buttons_area = create_ui_object
									(
										UI_TYPE_AREA,
										UI_ATTR_PARENT (modem_parameters_area),
										UI_ATTR_VIRTUAL_POSITION (x1, y1),
										UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, OPTION_AREA_HEIGHT),
										UI_ATTR_CLEAR (TRUE),
					               UI_ATTR_COLOUR_START (0,0,0,0),
            					   UI_ATTR_COLOUR_END (255,255,255,255),
										UI_ATTR_END
									);

	x1 = get_ui_object_x_end (title_change_array[0]);
	y1 = 0.0;

	mb_width = 0.197;

	// dial button

   modem_dial_button = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (modem_call_buttons_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (mb_width, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255,255,255,0),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_medium),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_CENTRE),
		UI_ATTR_TEXT (get_trans ("MP_DIAL")),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_modem_dial_function),
		UI_ATTR_END
	);

	// get size for buttons

	preprocess_translation_object_size (modem_dial_button, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

//	if (global_options.current_language != LANGUAGE_ENGLISH)
//	{
//		preprocess_ui_option_button_size_free (modem_dial_button, NULL, translations, 3);
//	}

	mb_width = get_ui_object_x_size_end (modem_dial_button);

	x1 = get_ui_object_x_end (modem_dial_button) + OPTION_BOX_GAP_WIDTH + mb_width;

	// answer button
	
   modem_answer_button = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (modem_call_buttons_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (mb_width, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255,255,255,0),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_medium),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_CENTRE),
		UI_ATTR_TEXT (get_trans ("MP_ANSWER")),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_modem_answer_function),
		UI_ATTR_END
	);

	preprocess_translation_object_size (modem_answer_button, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	// cancel button

	mb_width = get_ui_object_x_size_end (modem_answer_button);

	x1 += mb_width + OPTION_BOX_GAP_WIDTH;

   modem_cancel_button = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (modem_call_buttons_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (mb_width, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255,255,255,0),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_medium),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_CENTRE),
		UI_ATTR_TEXT (get_trans ("MP_CANCEL")),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_modem_cancel_function),
		UI_ATTR_END
	);

	preprocess_translation_object_size (modem_cancel_button, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	// connection type area - keep at bottom of function so it is on top of other areas

	j++;

	change_array[j] = connection_type_bdrop = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (connection_type_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [j]) + get_ui_object_x_size_end (title_change_array [j]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_EXTRA_LARGE_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255,255,255,0),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_extra_large),
		UI_ATTR_END
	);

   connection_type_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (connection_type_area),
		UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
		UI_ATTR_VIRTUAL_POSITION (get_ui_object_x_end (change_array [j]) + OPTION_BUTTON_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_connection_type_button),
		UI_ATTR_END
	);

	// Modem status text

	x1 = get_ui_object_x_end (title_change_array[0]);
	y1 = get_ui_object_y_end (modem_call_buttons_area);
	y1 += OPTION_AREA_OFFSET_Y;

	j++;

	change_array[j] = modem_status_text = create_ui_object
								(
									UI_TYPE_TEXT,
									UI_ATTR_PARENT (modem_parameters_area),
									UI_ATTR_VIRTUAL_POSITION (x1, y1),
									UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
									UI_ATTR_TEXT (""),
									UI_ATTR_FONT_TYPE (UI_FONT_THICK_ARIAL_18),
      							UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      							UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
									UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_NONE),
									UI_ATTR_CLEAR (TRUE),
									UI_ATTR_END
								);

	/////////////////////////////////////////////////////////////////
	// Objects for input of IP address
	//

	j++;

	change_array[j] = ip_address_text_area = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (tcpip_parameters_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [j-2]) + get_ui_object_x_size_end (title_change_array [j-2]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_LARGE_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255,255,255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

	// Actual text

   ip_address_text_obj = create_ui_object
									(
										UI_TYPE_AREA,
										UI_ATTR_PARENT (tcpip_parameters_area),
										UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (change_array [j]) + OPTION_BUTTON_TEXT_OFFSET_X), 0.0),
										UI_ATTR_VIRTUAL_SIZE (1.0, 1.0),
										UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
      								UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      								UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      								UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      								UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
										UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
										UI_ATTR_TEXT (global_options.ip_address),
										UI_ATTR_HIGHLIGHTABLE (TRUE),
										UI_ATTR_CLEAR (TRUE),
										UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
										UI_ATTR_FUNCTION (get_text_input),
										UI_ATTR_END
									);

	// Text input

	ip_address_text_input = create_ui_object
									(
										UI_TYPE_INPUT,
										UI_ATTR_PARENT (tcpip_parameters_area),
										UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (change_array [j]) + OPTION_BUTTON_TEXT_OFFSET_X), OPTION_BOX_TEXT_OFFSET_Y),
										UI_ATTR_VIRTUAL_SIZE (1.0, 1.0),
										UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
										UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
      								UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
	    								UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
										UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
		  								UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
										UI_ATTR_STATE (UI_OBJECT_STATE_OFF),
										UI_ATTR_FUNCTION (multi_text_input_function),
										UI_ATTR_END
									);

	set_limit_input_length (ip_address_text_input, FALSE);

	set_ui_object_item_number ( ip_address_text_input, ( int ) ip_address_text_obj );

	set_ui_object_item_number ( ip_address_text_obj, ( int ) ip_address_text_input );

	// set object times

	recursively_set_object_time (multi_player_setup_area, OPTIONS_BUTTON_AREA_FADE_TIME, OPTIONS_BUTTON_AREA_OFFSET_TIME);

	// ghost multiplayer modem areas

	x1 = 0.000;
	y1 = 0.250;
	x2 = 1.000;
	y2 = 0.250;

	ghost_multiplayer_modem_area = create_ui_object
									(
										UI_TYPE_AREA,
										UI_ATTR_PARENT (options_screen),
										UI_ATTR_VIRTUAL_POSITION (x1, y1),
										UI_ATTR_VIRTUAL_SIZE (x2, y2),
										UI_ATTR_CLEAR (TRUE),
										UI_ATTR_DRAWABLE (FALSE),
										UI_ATTR_END
									);

	x1 = 0.000;
	y1 = get_ui_object_y_end (modem_dial_button);
	x2 = get_ui_object_x_end (modem_cancel_button);
	y2 = y1 + get_ui_object_virtual_y_size (modem_dial_button);

	ghost_multiplayer_modem_area2 = create_ui_object
									(
										UI_TYPE_AREA,
										UI_ATTR_PARENT (options_screen),
										UI_ATTR_VIRTUAL_POSITION (x1, y1),
										UI_ATTR_VIRTUAL_SIZE (x2, y2),
										UI_ATTR_CLEAR (TRUE),
										UI_ATTR_DRAWABLE (FALSE),
										UI_ATTR_END
									);

	// initialise strings

	sprintf (text, "%s: %s", get_trans ("MP_STATUS"), get_trans ("MP_INITIALISED"));

	set_ui_object_text (serial_status_text, text);

	sprintf (text, "%s: %s", get_trans ("MP_STATUS"), get_trans ("MP_UNCONNECTED"));

	set_ui_object_text (modem_status_text, text);

	// Now install the selected service provider

	install_global_options_service_provider ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_com_port_function ( ui_object *obj, void *arg )
{
	char
		text [2];

   int
      selection;

	selection = get_global_comms_port ();

	selection ++;

	if (selection > 4)
	{
		selection = 1;
	}

	sprintf (text, "%d", selection);

	set_ui_object_text (com_port_button, text);

	set_toggle_button_off (obj);
	
	set_global_comms_port (selection);

	set_serial_connection_status ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_baud_rate_function ( ui_object *obj, void *arg )
{

   int
      selection;

	selection = get_global_baud_rate ();

	selection ++;

	if (selection > 4)
	{
		selection = 1;
	}

	set_ui_object_text (obj, baud_rate_text [selection - 1]);

	set_toggle_button_off (obj);

	set_global_baud_rate ( selection );

	set_serial_connection_status ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_stop_bits_function ( ui_object *obj, void *arg )
{

   int
      selection;

	selection = get_global_stop_bits ();

	selection ++;

	if (selection > 3)
	{
		selection = 1;
	}

	set_ui_object_text (obj, stop_bits_text [selection - 1]);

	set_toggle_button_off (obj);
	
	set_global_stop_bits (selection);

	set_serial_connection_status ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_parity_function ( ui_object *obj, void *arg )
{

   int
      selection;

	selection = get_global_parity ();

	selection ++;

	if (selection > 4)
	{
		selection = 1;
	}

	set_ui_object_text (obj, parity_text [selection - 1]);

	set_toggle_button_off (obj);
	
	set_global_parity (selection);

	set_serial_connection_status ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_flow_function ( ui_object *obj, void *arg )
{

   int
      selection;

	selection = get_global_flow ();

	selection ++;

	if (selection > 5)
	{
		selection = 1;
	}

	set_ui_object_text (obj, flow_text [selection - 1]);

	set_toggle_button_off (obj);

	set_global_flow (selection);

	set_serial_connection_status ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void multi_text_input_function ( ui_object *obj, void *arg )
{

	const char
		*text;
		
	obj;
	arg;

	text = get_ui_object_text ( obj );

	if ( ( text ) && ( strlen ( text ) > 0 ) )
	{

		set_ui_object_text ( ( ui_object * ) get_ui_object_item_number ( obj ), text );
	}
	else
	{

		set_ui_object_text ( ( ui_object * ) get_ui_object_item_number ( obj ), "" );
	}

	set_ui_object_drawable ( ( ui_object * ) get_ui_object_item_number ( obj ), TRUE );

	ui_force_update ();

	// don't leave text selected

	set_toggle_button_off ((ui_object *) get_ui_object_item_number (obj));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_text_input (ui_object *obj, void *arg)
{

	set_ui_object_text (obj, "");

	set_ui_object_drawable ((ui_object *) get_ui_object_item_number (obj), TRUE);
	
	set_ui_object_state ((ui_object *) get_ui_object_item_number (obj), UI_OBJECT_STATE_ON);

	// don't leave text selected

	set_toggle_button_off (obj);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_modem_type_function ( ui_object *obj, void *arg )
{

	current_modem = current_modem->succ;

	if (!current_modem)
	{
		current_modem = modem_name_list;
	}

	set_ui_object_text (obj, current_modem->name);

	set_toggle_button_off (obj);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

