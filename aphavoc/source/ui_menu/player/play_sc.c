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
#include "play_hours.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEFAULT_LOG_NAME	"Razorworks"

#define MAXIMUM_NUMBER_OF_PLAYERS 32

#define MAXIMUM_PLAYER_NAME 16

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static ui_object
	*player_list_bdrop,
	*player_list_area,
	*player_list,
	*player_name_entry_area,
	*player_name_input,

	*player_general_log_selection_button,
	*player_flight_hours_selection_button,
	*player_weapon_log_selection_button,
	*player_medals_selection_button,
	
	*player_blue_side_selection_button,
	*player_red_side_selection_button,
	
	*current_player_rank_text,
	*player_commision_date_text;

ui_object
	*select_player_screen,
	*log_page [NUM_LOG_PAGES];

entity_sides
	player_log_current_side;

int
	player_creating_player;

texture_graphic
	*player_screen_graphic = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_select_player_screen (ui_object *obj, void *arg);

static void notify_select_player_exit_button (ui_object *obj, void *arg);

static void notify_medals_button (ui_object *obj, void *arg);

static void player_list_function (ui_object *obj, void *arg);

static void player_add_function (ui_object *obj, void *arg);

static void player_name_input_function (ui_object *obj, void *arg);

static void player_callsign_entry_function (ui_object *obj, void *arg);

static void player_callsign_input_function (ui_object *obj, void *arg);

static void notify_player_entry_create_button (ui_object *obj, void *arg);

static void notify_select_player_restore_button(ui_object* obj, void* arg);

static void player_rename_function ( ui_object *obj, void *arg );

static void player_delete_function (ui_object *obj, void *arg);

static void player_select_side_function ( ui_object *obj, void *arg );

static player_log_type *create_empty_player_log ();

static player_log_type *create_player_log (const char *name);

static player_log_type *rename_player_log (int id, const char *name);

static void rebuild_player_log_list (void);

void test_player_scoring (player_log_type *log, int side);

void resize_player_list_size (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_select_player_screen (void)
{
	int
		i;
		
	float
		x1,
		y1,
		x2,
		y2,
		gap_width;

	ui_object
		*temp_obj,
		*option_bdrop,
		*change_array[3];

	x1 = 0.0;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 1.0;

	// initialise side switch for player info pages
	player_log_current_side = ENTITY_SIDE_BLUE_FORCE;

   select_player_screen = create_ui_object
									(
										UI_TYPE_SCREEN,
										UI_ATTR_VIRTUAL_POSITION (x1, y1),
										UI_ATTR_VIRTUAL_SIZE (x2, y2),
										UI_ATTR_COLOUR_START (255, 255, 255, 0),
										UI_ATTR_COLOUR_END (255, 255, 255, 255),
										UI_ATTR_OFFSET_TIME (0),
										UI_ATTR_TIME_LENGTH (500),
										UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_EITHER),
										UI_ATTR_FUNCTION (notify_select_player_screen),
										UI_ATTR_END
									);

   create_ui_object
            (
               UI_TYPE_TEXT,
               UI_ATTR_PARENT (select_player_screen),
					UI_ATTR_TIME_LENGTH (0),
					UI_ATTR_OFFSET_TIME (0),
               UI_ATTR_VIRTUAL_POSITION (TITLE_TEXT_POSITION_X, TITLE_TEXT_POSITION_Y),
					UI_ATTR_VIRTUAL_SIZE (TITLE_TEXT_WIDTH, TITLE_TEXT_HEIGHT),
					UI_ATTR_TEXT (get_trans ("UI_PILOTS")),
					UI_ATTR_FONT_TYPE (UI_FONT_IMPACT_22),
					UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_BOTTOM),
               UI_ATTR_FONT_COLOUR_START (ui_screen_title_text_colour.r, ui_screen_title_text_colour.g, ui_screen_title_text_colour.b, 0),
               UI_ATTR_FONT_COLOUR_END (ui_screen_title_text_colour.r, ui_screen_title_text_colour.g, ui_screen_title_text_colour.b, 255),
					UI_ATTR_OFFSET_TIME (0),
					UI_ATTR_TIME_LENGTH (500),
					UI_ATTR_HIGHLIGHTABLE (FALSE),
					UI_ATTR_CLEAR (TRUE),
               UI_ATTR_END
            );

	// setup other pages

	define_general_log_page_objects ();

	define_flight_hours_page_objects();

	define_weapon_log_page_objects ();
	
	y2 = 0.038;

	define_medals_page_objects ();

	////////////////////////////////////////////////
	//
	// player list
	//
	////////////////////////////////////////////////

	x1 = 0.030;
	y1 = 0.126;
	x2 = 0.466;
	y2 = 0.677;
	
   player_list_bdrop = create_ui_object
						(
							UI_TYPE_AREA,
							UI_ATTR_PARENT (select_player_screen),
							UI_ATTR_VIRTUAL_POSITION (x1, y1),
							UI_ATTR_VIRTUAL_SIZE (x2, y2),
							UI_ATTR_TEXTURE_GRAPHIC (list_box_graphic),
							UI_ATTR_OFFSET_TIME (0),
							UI_ATTR_TIME_LENGTH (500),
							UI_ATTR_END
						);

	x1 = 0.04;
	y1 = 0.1;
	x2 = 0.90;
	y2 = 0.86;
	
   player_list_area = create_ui_object
						(
							UI_TYPE_AREA,
							UI_ATTR_PARENT (player_list_bdrop),
							UI_ATTR_VIRTUAL_POSITION (x1, y1),
							UI_ATTR_VIRTUAL_SIZE (x2, y2),
							UI_ATTR_VSLIDER (0, 1000, ui_get_font_height ()),
							UI_ATTR_CLEAR (TRUE),
							UI_ATTR_END
						);

	////////////////////////////////////////////////
	//	Slider Graphics

	set_frontend_slider_graphics (player_list_area);

	x1 = 0.046;
	//y1 = 0.092;
	y1 = 0.0;
	x2 = 0.862;
	y2 = 0.840;
	
   player_list = create_ui_object
						(
							UI_TYPE_LIST_BOX,
							UI_ATTR_PARENT (player_list_area),
							UI_ATTR_VIRTUAL_POSITION (x1, y1),
							UI_ATTR_VIRTUAL_SIZE (x2, y2),
		            	UI_ATTR_FONT_COLOUR_START (ui_list_text_default_colour.r, ui_list_text_default_colour.g, ui_list_text_default_colour.b, 0),
   		         	UI_ATTR_FONT_COLOUR_END (ui_list_text_default_colour.r, ui_list_text_default_colour.g, ui_list_text_default_colour.b, 255),
      		      	UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_list_text_hilite_colour.r, ui_list_text_hilite_colour.g, ui_list_text_hilite_colour.b, 0),
         		   	UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_list_text_hilite_colour.r, ui_list_text_hilite_colour.g, ui_list_text_hilite_colour.b, 255),
							UI_ATTR_HIGHLIGHTABLE (TRUE),
							UI_ATTR_LIST_BOX_Y_SPACE (0),
							UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_18),
							UI_ATTR_CLEAR (TRUE),
							UI_ATTR_FUNCTION (player_list_function),
							UI_ATTR_END
						);

	////////////////////////////////////////////////
	// Delete Player Button

	gap_width = 0.04;
	
	x1 = 0.721;
	y1 = 0.029;
	x2 = 0.178;
	y2 = 0.038;

	i = 0;

   change_array[i] = create_ui_object
	(
		UI_TYPE_BUTTON,
		UI_ATTR_PARENT (player_list_bdrop),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (x2, y2),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
   	UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
    	UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
     	UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
    	UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_TEXT (get_trans ("DELETE")),
		UI_ATTR_CLEAR ( TRUE ),
		UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
		UI_ATTR_FUNCTION (player_delete_function),
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	///////////////////////////////////////////////
	// Rename Player Button
	
	x2 = 0.197;
	y2 = 0.038;

	x1 = get_ui_object_virtual_x (change_array[0]) - gap_width - x2 ;
	
	y1 = 0.029;

	i++;

   change_array[i] = create_ui_object
	(
		UI_TYPE_BUTTON,
		UI_ATTR_PARENT (player_list_bdrop),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (x2, y2),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
     	UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
    	UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
     	UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
    	UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_TEXT (get_trans ("RENAME")),
		UI_ATTR_FUNCTION ( player_rename_function ),
		UI_ATTR_CLEAR ( TRUE ),
		UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	////////////////////////////////////////////////
	// Add Player Button
	
	x2 = 0.106;
	y2 = 0.038;

	x1 = get_ui_object_virtual_x (change_array[1]) - gap_width - x2 ;
	
//	x1 = 0.379;
	y1 = 0.029;

	i++;
	
   change_array[i] = create_ui_object
	(
		UI_TYPE_BUTTON,
		UI_ATTR_PARENT (player_list_bdrop),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (x2, y2),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
     	UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
     	UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
     	UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
     	UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_TEXT (get_trans ("ADD")),
		UI_ATTR_CLEAR ( TRUE ),
		UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
		UI_ATTR_FUNCTION (player_add_function),
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);


	////////////////////////////////////////////////
	// Medals Selection Button
	
	x1 = 0.82;
	y1 = 0.112;
	x2 = 0.165;
	y2 = 0.039;

	option_bdrop = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (select_player_screen),
		UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
		UI_ATTR_VIRTUAL_SIZE (TEXT_OPTION_BDROP_WIDTH, TEXT_OPTION_BDROP_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 255),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (text_option_bdrop),
		UI_ATTR_OFFSET_TIME (0),
		UI_ATTR_TIME_LENGTH (500),
		UI_ATTR_END
	);

	player_medals_selection_button = create_ui_object
												(
													UI_TYPE_BUTTON,
													UI_ATTR_PARENT (select_player_screen),
													UI_ATTR_VIRTUAL_POSITION (x1, y1),
													UI_ATTR_VIRTUAL_SIZE (x2, y2),
													UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
													UI_ATTR_FONT_TYPE (UI_FONT_STRETCH_ITALIC_ARIAL_18),
													UI_ATTR_TEXT (get_trans ("Medals")),
													UI_ATTR_FUNCTION (notify_medals_button),
  									          	UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      								      	UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      								      	UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
            									UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
													UI_ATTR_HIGHLIGHTABLE (TRUE),
													UI_ATTR_CLEAR ( TRUE ),
													UI_ATTR_END
												);

	preprocess_translation_object_size (player_medals_selection_button, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	set_text_option_backdrop_object (option_bdrop, player_medals_selection_button);

	////////////////////////////////////////////////
	// Red Selection Button
	
	x1 = 0.628;
	y1 = 0.172;
	x2 = 0.238;
	y2 = 0.039;

	option_bdrop = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (select_player_screen),
		UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
		UI_ATTR_VIRTUAL_SIZE (TEXT_OPTION_BDROP_WIDTH, TEXT_OPTION_BDROP_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 255),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (text_option_bdrop),
		UI_ATTR_OFFSET_TIME (0),
		UI_ATTR_TIME_LENGTH (500),
		UI_ATTR_END
	);

	player_red_side_selection_button = create_ui_object
												(
													UI_TYPE_BUTTON,
													UI_ATTR_PARENT (select_player_screen),
													UI_ATTR_VIRTUAL_POSITION (x1, y1),
													UI_ATTR_VIRTUAL_SIZE (x2, y2),
													UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
													UI_ATTR_FONT_TYPE (UI_FONT_STRETCH_ITALIC_ARIAL_18),
													UI_ATTR_TEXT (get_trans ("Red Force")),
													UI_ATTR_FUNCTION (player_select_side_function),
													UI_ATTR_ITEM_NUMBER ( ENTITY_SIDE_RED_FORCE ),
  									          	UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      								      	UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      								      	UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
            									UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
													UI_ATTR_DRAWABLE (TRUE),
													UI_ATTR_HIGHLIGHTABLE (TRUE),
													UI_ATTR_CLEAR ( TRUE ),
													UI_ATTR_END
												);

	preprocess_translation_object_size (player_red_side_selection_button, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	set_text_option_backdrop_object (option_bdrop, player_red_side_selection_button);

	if (get_global_current_language () == LANGUAGE_GERMAN)
	{
		set_ui_object_x_end (option_bdrop, get_ui_object_x_end (option_bdrop) + 0.047);

		set_ui_object_x_end (player_red_side_selection_button, get_ui_object_x_end (player_red_side_selection_button) + 0.047);
	}

	////////////////////////////////////////////////
	// Blue Side Selection Button
	
	x1 = 0.739;
	y1 = 0.223;
	x2 = 0.247;
	y2 = 0.039;

	option_bdrop = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (select_player_screen),
		UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
		UI_ATTR_VIRTUAL_SIZE (TEXT_OPTION_BDROP_WIDTH, TEXT_OPTION_BDROP_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 255),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (text_option_bdrop),
		UI_ATTR_OFFSET_TIME (0),
		UI_ATTR_TIME_LENGTH (500),
		UI_ATTR_END
	);

	player_blue_side_selection_button = create_ui_object
												(
													UI_TYPE_BUTTON,
													UI_ATTR_PARENT (select_player_screen),
													UI_ATTR_VIRTUAL_POSITION (x1, y1),
													UI_ATTR_VIRTUAL_SIZE (x2, y2),
													UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
													UI_ATTR_FONT_TYPE (UI_FONT_STRETCH_ITALIC_ARIAL_18),
													UI_ATTR_TEXT (get_trans ("Blue Force")),
													UI_ATTR_FUNCTION (player_select_side_function),
													UI_ATTR_ITEM_NUMBER ( ENTITY_SIDE_BLUE_FORCE ),
          									  	UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
       									     	UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
    									        	UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
 									           	UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
													UI_ATTR_DRAWABLE (TRUE),
													UI_ATTR_HIGHLIGHTABLE (TRUE),
													UI_ATTR_CLEAR ( TRUE ),
													UI_ATTR_END
												);

	preprocess_translation_object_size (player_blue_side_selection_button, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	set_text_option_backdrop_object (option_bdrop, player_blue_side_selection_button);

	////////////////////////////////////////////////
	// General Log Selection Button

	x1 = 0.580;
	y1 = 0.750;
	x2 = 0.312;
	y2 = 0.042;

	option_bdrop = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (select_player_screen),
		UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
		UI_ATTR_VIRTUAL_SIZE (TEXT_OPTION_BDROP_WIDTH, TEXT_OPTION_BDROP_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 255),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (text_option_bdrop),
		UI_ATTR_OFFSET_TIME (0),
		UI_ATTR_TIME_LENGTH (500),
		UI_ATTR_END
	);

	player_general_log_selection_button = create_ui_object
												(
													UI_TYPE_BUTTON,
													UI_ATTR_PARENT (select_player_screen),
													UI_ATTR_VIRTUAL_POSITION (x1, y1),
													UI_ATTR_VIRTUAL_SIZE (x2, y2),
													UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
													UI_ATTR_FONT_TYPE (UI_FONT_STRETCH_ITALIC_ARIAL_18),
													UI_ATTR_TEXT (get_trans ("Flight Log")),
													UI_ATTR_FUNCTION (notify_show_general_log_page),
  									          	UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
  									         	UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      								      	UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
		  									   	UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
													UI_ATTR_HIGHLIGHTABLE (TRUE),
													UI_ATTR_CLEAR ( TRUE ),
													UI_ATTR_END
												);

	preprocess_translation_object_size (player_general_log_selection_button, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	set_text_option_backdrop_object (option_bdrop, player_general_log_selection_button);

	////////////////////////////////////////////////
	// Flight Hours Log Selection Button

	x1 = 0.620;
	y1 = 0.800;
	x2 = 0.312;
	y2 = 0.042;

	option_bdrop = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (select_player_screen),
		UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
		UI_ATTR_VIRTUAL_SIZE (TEXT_OPTION_BDROP_WIDTH, TEXT_OPTION_BDROP_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 255),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (text_option_bdrop),
		UI_ATTR_OFFSET_TIME (0),
		UI_ATTR_TIME_LENGTH (500),
		UI_ATTR_END
	);

	player_flight_hours_selection_button = create_ui_object
												(
													UI_TYPE_BUTTON,
													UI_ATTR_PARENT (select_player_screen),
													UI_ATTR_VIRTUAL_POSITION (x1, y1),
													UI_ATTR_VIRTUAL_SIZE (x2, y2),
													UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
													UI_ATTR_FONT_TYPE (UI_FONT_STRETCH_ITALIC_ARIAL_18),
													UI_ATTR_TEXT (get_trans ("Flight Hours")),
													UI_ATTR_FUNCTION (notify_show_flight_hours_page),
            									UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
         								   	UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      								      	UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
   								         	UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
													UI_ATTR_HIGHLIGHTABLE (TRUE),
													UI_ATTR_CLEAR ( TRUE ),
													UI_ATTR_END
												);

	preprocess_translation_object_size (player_flight_hours_selection_button, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	set_text_option_backdrop_object (option_bdrop, player_flight_hours_selection_button);


	////////////////////////////////////////////////
	// Weapon Log Selection Button

	x1 = 0.660;
	y1 = 0.850;
	x2 = 0.220;
	y2 = 0.042;
	
	option_bdrop = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (select_player_screen),
		UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
		UI_ATTR_VIRTUAL_SIZE (TEXT_OPTION_BDROP_WIDTH, TEXT_OPTION_BDROP_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 255),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (text_option_bdrop),
		UI_ATTR_OFFSET_TIME (0),
		UI_ATTR_TIME_LENGTH (500),
		UI_ATTR_END
	);

	player_weapon_log_selection_button = create_ui_object
												(
													UI_TYPE_BUTTON,
													UI_ATTR_PARENT (select_player_screen),
													UI_ATTR_VIRTUAL_POSITION (x1, y1),
													UI_ATTR_VIRTUAL_SIZE (x2, y2),
													UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
													UI_ATTR_FONT_TYPE (UI_FONT_STRETCH_ITALIC_ARIAL_18),
													UI_ATTR_TEXT (get_trans ("Weapons Log")),
													UI_ATTR_FUNCTION (notify_show_weapon_log_page),
            									UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
         								   	UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      								      	UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
   								         	UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
													UI_ATTR_HIGHLIGHTABLE (TRUE),
													UI_ATTR_CLEAR ( TRUE ),
													UI_ATTR_END
												);

	preprocess_translation_object_size (player_weapon_log_selection_button, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	set_text_option_backdrop_object (option_bdrop, player_weapon_log_selection_button);

	/////////////////////////////////////////////////////////////////
	// Ok Button

	option_bdrop = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (select_player_screen),
		UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
		UI_ATTR_VIRTUAL_SIZE (TEXT_OPTION_BDROP_WIDTH, TEXT_OPTION_BDROP_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 255),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (text_option_bdrop),
		UI_ATTR_OFFSET_TIME (0),
		UI_ATTR_TIME_LENGTH (500),
		UI_ATTR_END
	);

	temp_obj = create_ui_object
			(
				UI_TYPE_BUTTON,
				UI_ATTR_PARENT (select_player_screen),
				UI_ATTR_VIRTUAL_POSITION (OPTIONS_OK_BUTTON_POS_X, OPTIONS_OK_BUTTON_POS_Y),
				UI_ATTR_VIRTUAL_SIZE (OPTIONS_OK_BUTTON_X, OPTIONS_OK_BUTTON_Y),
				UI_ATTR_TEXT (get_trans("UI_OK")),
				UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
				UI_ATTR_FUNCTION (notify_select_player_exit_button),
				UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
           	UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
           	UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
           	UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
           	UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
				UI_ATTR_HIGHLIGHTABLE (TRUE),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);
			
	set_text_option_backdrop_object (option_bdrop, temp_obj);

	/////////////////////////////////////////////////////////////////
	// Undo Button

	x1 = OPTIONS_OK_BUTTON_POS_X + 0.020;
	y1 = OPTIONS_OK_BUTTON_POS_Y + 0.050;
	x2 = OPTIONS_OK_BUTTON_X;
	y2 = OPTIONS_OK_BUTTON_Y;

	option_bdrop = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (select_player_screen),
		UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
		UI_ATTR_VIRTUAL_SIZE (TEXT_OPTION_BDROP_WIDTH, TEXT_OPTION_BDROP_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 255),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (text_option_bdrop),
		UI_ATTR_OFFSET_TIME (0),
		UI_ATTR_TIME_LENGTH (500),
		UI_ATTR_END
	);

	temp_obj = create_ui_object
			(
				UI_TYPE_BUTTON,
				UI_ATTR_PARENT (select_player_screen),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2, y2),
				UI_ATTR_TEXT ("Undo Last Mission"),
				UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
				UI_ATTR_FUNCTION (notify_select_player_restore_button),
				UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
           	UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
           	UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
           	UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
           	UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
				UI_ATTR_HIGHLIGHTABLE (TRUE),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);
			
	set_text_option_backdrop_object (option_bdrop, temp_obj);

	
	///////////////////////////////////////////
	// Player name entry area

	x1 = get_ui_object_virtual_x (player_list);
	y1 = get_ui_object_virtual_y (player_list);
	x2 = get_ui_object_virtual_x_size (player_list);
	y2 = get_ui_object_virtual_y_size (player_list);
	
   player_name_entry_area = create_ui_object
            (
               UI_TYPE_AREA,
               UI_ATTR_PARENT (player_list_area),
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

   player_name_input = create_ui_object
            (
               UI_TYPE_INPUT,
               UI_ATTR_PARENT (player_name_entry_area),
					UI_ATTR_VIRTUAL_POSITION (x1, y1),
					UI_ATTR_VIRTUAL_SIZE (x2, y2),
					UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_18),
            	UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
            	UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
					UI_ATTR_FUNCTION (player_name_input_function),
					UI_ATTR_CLEAR (FALSE),
               UI_ATTR_END
            );

	/////////////////////////////////////////////////////////////////
	// Text Areas

	x1 = 0.584;
	y1 = 0.900;
	x2 = 0.195;
	y2 = 0.030;

   current_player_rank_text = create_ui_object
            (
               UI_TYPE_AREA,
               UI_ATTR_PARENT (select_player_screen),
					UI_ATTR_VIRTUAL_POSITION (x1, y1),
					UI_ATTR_VIRTUAL_SIZE (x2, y2),
					UI_ATTR_CLEAR ( TRUE ),
					UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
					UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_22),
  				   UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
   				UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
					UI_ATTR_TEXT (""),
               UI_ATTR_END
            );

	x1 = 0.462;
	y1 = 0.946;
	x2 = 0.317;
	y2 = 0.030;

   player_commision_date_text = create_ui_object
            (
               UI_TYPE_AREA,
               UI_ATTR_PARENT (select_player_screen),
					UI_ATTR_VIRTUAL_POSITION (x1, y1),
					UI_ATTR_VIRTUAL_SIZE (x2, y2),
					UI_ATTR_CLEAR ( TRUE ),
					UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
     	 			UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      			UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
					UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
					UI_ATTR_TEXT (""),
               UI_ATTR_END
            );
				
	rebuild_player_log_list ();

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void display_player_log_page (player_log_pages page)
{
	int
		loop;
		
	for (loop = 0; loop < NUM_LOG_PAGES; loop ++)
	{
		set_ui_object_drawable (log_page [loop], (page == loop));
	}

	if (page == LOG_PAGE_GENERAL)
	{
		set_ui_object_state (log_page [LOG_PAGE_GENERAL], UI_OBJECT_STATE_ON);
		set_ui_object_state (log_page [LOG_PAGE_FLIGHT_HOURS], UI_OBJECT_STATE_OFF);
		set_ui_object_state (log_page [LOG_PAGE_WEAPON], UI_OBJECT_STATE_OFF);

		set_ui_object_state (player_general_log_selection_button, UI_OBJECT_STATE_ON);
		set_ui_object_state (player_flight_hours_selection_button, UI_OBJECT_STATE_OFF);
		set_ui_object_state (player_weapon_log_selection_button, UI_OBJECT_STATE_OFF);
	}
	else if (page == LOG_PAGE_FLIGHT_HOURS)
	{
		set_ui_object_state (log_page [LOG_PAGE_GENERAL], UI_OBJECT_STATE_OFF);
		set_ui_object_state (log_page [LOG_PAGE_FLIGHT_HOURS], UI_OBJECT_STATE_ON);
		set_ui_object_state (log_page [LOG_PAGE_WEAPON], UI_OBJECT_STATE_OFF);

		set_ui_object_state (player_weapon_log_selection_button, UI_OBJECT_STATE_OFF);
		set_ui_object_state (player_flight_hours_selection_button, UI_OBJECT_STATE_ON);
		set_ui_object_state (player_general_log_selection_button, UI_OBJECT_STATE_OFF);
	}
	else
	{
		set_ui_object_state (log_page [LOG_PAGE_GENERAL], UI_OBJECT_STATE_OFF);
		set_ui_object_state (log_page [LOG_PAGE_FLIGHT_HOURS], UI_OBJECT_STATE_OFF);
		set_ui_object_state (log_page [LOG_PAGE_WEAPON], UI_OBJECT_STATE_ON);

		set_ui_object_state (player_weapon_log_selection_button, UI_OBJECT_STATE_ON);
		set_ui_object_state (player_flight_hours_selection_button, UI_OBJECT_STATE_OFF);
		set_ui_object_state (player_general_log_selection_button, UI_OBJECT_STATE_OFF);
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_select_player_screen (ui_object *obj, void *arg)
{
	if ( get_ui_object_drawable ( obj ) )
	{
	
		switch (player_log_current_side)
		{
	
			case ENTITY_SIDE_RED_FORCE:
			{
	
				set_ui_object_state ( player_red_side_selection_button, UI_OBJECT_STATE_ON );
	
				break;
			}
	
			case ENTITY_SIDE_BLUE_FORCE:
			{
	
				set_ui_object_state ( player_blue_side_selection_button, UI_OBJECT_STATE_ON );
	
				break;
			}
	
		}
	
		if ( player_screen_graphic )
		{
	
			destroy_texture_graphic ( player_screen_graphic );

			player_screen_graphic = NULL;
		}
	
		player_screen_graphic = create_texture_graphic ( "graphics\\ui\\cohokum\\pilots.psd" );

		set_ui_object_texture_graphic ( select_player_screen, player_screen_graphic );
	
		blit_front_buffer_to_render_buffer ();
	
		reset_time_values ( select_player_screen );

	}
	else
	{

		if ( player_screen_graphic )
		{
	
			destroy_texture_graphic ( player_screen_graphic );

			player_screen_graphic = NULL;
		}
	}

	rebuild_player_log_list ();

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_select_player_exit_button (ui_object *obj, void *arg)
{

	obj;
	arg;

	if ((int) arg == BUTTON_STATE_DOWN)
	{

		set_ui_object_graphic (obj, (unsigned short int *) get_graphics_file_data (GRAPHICS_UI_APACHE_PLANNER_BACK_BUTTON_SELECTED));
	}
	else if ((int) arg == BUTTON_STATE_UP)
	{

		set_ui_object_graphic (obj, (unsigned short int *) get_graphics_file_data (GRAPHICS_UI_APACHE_PLANNER_BACK_BUTTON_UNSELECTED));

		set_ui_object_redraw (select_player_screen, TRUE);

		pop_ui_screen (SCREEN_POP_ACTUAL);
	}
	else 
	{

		set_ui_object_graphic (obj, (unsigned short int *) get_graphics_file_data (GRAPHICS_UI_APACHE_PLANNER_BACK_BUTTON_UNSELECTED));

		set_ui_object_redraw (select_player_screen, TRUE);
	}

	set_ui_object_graphic_type (obj, UI_OBJECT_ALPHA_GRAPHIC);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_medals_button (ui_object *obj, void *arg)
{

	obj;
	arg;

	push_ui_screen (player_medals_screen);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_select_player_restore_button(ui_object* obj, void* arg)
{
	obj; arg;  // just to silence the compiler
	
	if (restore_log_from_backup())
		rebuild_player_log_list();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void player_list_function (ui_object *obj, void *arg)
{

	const char
		*player_name;

	player_log_type
		*player_log;

	int
		player_unique_id;

	if ( get_ui_object_item_number ( obj ) < 0 )
	{

		return;
	}

	player_name = get_ui_object_text ( obj );

	player_unique_id = get_ui_object_item_number2 ( obj );

	#if DEBUG_MODULE

	debug_log ( "Locating log %s, %d", player_name, player_unique_id );

	#endif
	
	if ( ( player_name ) && ( player_unique_id ) )
	{

		player_log = get_player_log_list ();

		while ( player_log )
		{

			if ( ( strcmp ( player_name, get_player_log_name ( player_log ) ) == 0 ) && ( player_unique_id == player_log->unique_id ) )
			{

				set_current_player_log ( player_log );

				rebuild_player_log_list ();

				return;
			}

			player_log = get_player_log_next ( player_log );
		}

		debug_fatal ( "PLAY_SC: Can't locate player log %s", player_name );
	}

	debug_fatal ( "PLAY_SC: Can't locate player log" );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void player_add_function (ui_object *obj, void *arg)
{

	ui_object
		*slider,
		*list_item;

	float
		x,
		y;

	int
		count;

	player_log_type
		*player;

	player = get_player_log_list ();

	count = 0;

	while ( player )
	{

		player = player->next;

		count++;
	}

	if ( count < MAXIMUM_NUMBER_OF_PLAYERS )
	{
	
		list_item = add_to_pop_up_list ( "", player_list, NULL, 0, UI_FONT_ARIAL_18, ui_list_text_default_colour );

		set_ui_frontend_list_object_highlightable (list_item);

		// re-size the list objects when items are added

		//resize_player_list_size ();

		// slide list to bottom
		
		slider = get_ui_object_vslider (player_list_area);
		set_ui_object_vslider_virtual_position (slider, 1.0);

		// move input object to correct position
		
		x = get_ui_object_virtual_x (list_item);

		y = get_ui_object_virtual_y (list_item);

		set_ui_object_virtual_x (player_name_input, x);
	
		set_ui_object_virtual_y (player_name_input, y);

		// switch input on
	
		set_ui_object_drawable (list_item, FALSE);
	
		set_ui_object_item_number (player_name_input, (int) list_item);
	
		set_ui_object_drawable (player_name_entry_area, TRUE);
	
		set_ui_object_state (player_name_input, UI_OBJECT_STATE_ON);
	
		player_creating_player = TRUE;
	}

	save_player_list ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void player_name_input_function ( ui_object *obj, void *arg )
{

  	const char
		*text;

	ui_object
		*object;

	player_log_type
		*player;

	text = get_ui_object_text ( obj );

	object = ( ui_object * ) get_ui_object_item_number ( obj );

	if ( ( text ) && ( strlen ( text ) > 0 ) )
	{

		//
		// Create the players log ( depending on whether we are in rename or create mode )
		//

		if ( player_creating_player )
		{

			player = create_player_log ( text );

			set_current_player_log ( player );

			rebuild_player_log_list ();
		}
		else
		{

			player = rename_player_log ( get_ui_object_item_number2 ( object ), text );

			set_ui_object_text ( object, player->name );
	
			set_ui_object_drawable ( object, TRUE);
		}
	}
	else
	{

		//
		// Destroy the list item - or set the players name back to what it was
		//

		if ( player_creating_player )
		{

			destroy_ui_object ( object );
		}
		else
		{

			int
				id;

			id = get_ui_object_item_number2 ( object );

			player = get_player_log_list ();

			while ( ( player ) && ( player->unique_id != id ) )
			{

				player = player->next;
			}

			ASSERT ( player );

			set_ui_object_text ( object, player->name );
		}
	}

	set_ui_object_drawable ( player_name_entry_area, FALSE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void player_rename_function ( ui_object *obj, void *arg )
{

	ui_object
		*list_item;

	float
		y,
		y_size;

	player_log_type
		*player;

	player = get_current_player_log ();

	list_item = get_ui_object_child ( player_list );

	while ( ( list_item ) && ( get_ui_object_item_number2 ( list_item ) != player->unique_id ) )
	{

		list_item = get_ui_object_next ( list_item );
	}

	ASSERT ( list_item );

	y = get_ui_object_virtual_y (list_item);
	
	y_size = get_ui_object_virtual_y_size (player_list);

	set_ui_object_virtual_y (player_name_input, y);

	set_ui_object_drawable (list_item, FALSE);

	set_ui_object_item_number (player_name_input, (int) list_item);

	set_ui_object_text ( player_name_input, get_ui_object_text ( list_item ) );

	set_ui_object_drawable (player_name_entry_area, TRUE);

	set_ui_object_state (player_name_input, UI_OBJECT_STATE_ON);

	player_creating_player = FALSE;

	save_player_list ();

	#if DEBUG_MODULE

	test_player_scoring (get_current_player_log ());

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void player_delete_function ( ui_object *obj, void *arg )
{

	player_log_type
		*log,
		*prev,
		*next,
		*delete_log;

	log = get_player_log_list ();

	if ( ( log ) && ( log->next ) )
	{
	
		delete_log = get_current_player_log ();
	
		if ( delete_log )
		{
	
			next = delete_log->next;
	
			prev = NULL;
	
			log = get_player_log_list ();

			// find log that is previous to delete_log if it exists
			while ( log )
			{
	
				if ( log->next == delete_log )
				{
	
					prev = log;
	
					break;
				}
	
				log = log->next;
			}

			// select previous log if it is valid	
			if ( prev )
			{
	
				set_current_player_log ( prev );
			
				prev->next = next;
	
				rebuild_player_log_list ();
			}
			// otherwise, if log has a next, select that
			else if ( next )
			{
	
				set_current_player_log ( next );
			
				set_player_log_list ( next );
			
				rebuild_player_log_list ();
			}
			// this case should never exist...
			else
			{
			
				direct_play_set_player_name ( "Unnamed Player" );
				
				set_current_player_log ( NULL );
			
				set_player_log_list ( NULL );
			
				rebuild_player_log_list ();
	
//				set_ui_object_text ( current_player_rank_text, "" );
			}
		
			save_player_list ();
		}

		resize_player_list_size ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void player_select_side_function ( ui_object *obj, void *arg )
{

	entity_sides
		side;

	side = (entity_sides) get_ui_object_item_number ( obj );

	player_log_current_side  = side;

	switch (player_log_current_side )
	{

		case ENTITY_SIDE_RED_FORCE:
		{

			set_ui_object_state ( player_red_side_selection_button, UI_OBJECT_STATE_ON );

			set_ui_object_state ( player_blue_side_selection_button, UI_OBJECT_STATE_OFF );

			break;
		}
		
		case ENTITY_SIDE_BLUE_FORCE:
		{

			set_ui_object_state ( player_blue_side_selection_button, UI_OBJECT_STATE_ON );

			set_ui_object_state ( player_red_side_selection_button, UI_OBJECT_STATE_OFF );

			break;
		}

		default:
		{
			set_ui_object_state ( player_red_side_selection_button, UI_OBJECT_STATE_OFF );

			set_ui_object_state ( player_blue_side_selection_button, UI_OBJECT_STATE_OFF );

			break;
		}
		
	}

	rebuild_player_log_list ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void load_player_list (void)
{

	int
		version = 0,
		level;

	player_log_type
		*new_player;

	FILE
		*file_ptr;

	#if DEBUG_MODULE

		//debug_log ("DEBUG - Initialising player list");

	#endif

	set_player_log_list ( NULL );

	ui_object_destroy_list_items ( player_list );

	if (file_exist ( "players2.bin" ))
	{
		version = 2;
		file_ptr = safe_fopen ( "players2.bin", "rb" );
	}
	else if (file_exist ( "players.bin" ))
	{
		version = 1;
		file_ptr = safe_fopen ( "players.bin", "rb" );
	}

	if (version)
	{
		int
			side,
			loop,
			num_entries,
			current_player_index,
			string_length;

		fread ( &num_entries, sizeof ( int ), 1, file_ptr );

		fread ( &current_player_index, sizeof ( int ), 1, file_ptr );

		for ( loop = 0; loop < num_entries; loop++ )
		{

			new_player = create_empty_player_log ();

			//
			// Name
			//
			
			fread ( &string_length, sizeof ( int ), 1, file_ptr );

			if ( string_length > 0 )
			{

				new_player->name = ( char * ) malloc_heap_mem ( sizeof ( char ) * (string_length  + 2));
	
				fread ( new_player->name, 1, string_length, file_ptr );
			}

			//
			// Unique ID
			//

			fread ( &new_player->unique_id, sizeof ( int ), 1, file_ptr );

			//
			// Date commissioned
			//

			fread ( &new_player->date_commissioned, sizeof ( player_commissioned_type ), 1, file_ptr );

			//
			// read individual gunship logs
			//

			for (side = 0; side <= NUM_ENTITY_SIDES; side ++ )
			{
				// size of original side log element was 756, it has changed now
				if (version == 1)
				{
					version1_player_side_log_type v1_log;
					
					fread ( &v1_log, sizeof(v1_log), 1, file_ptr );

					// the first values are in the same positoin so we'll just copy them
					memcpy(&new_player->side_log[side], &v1_log, sizeof(v1_log));
					
					// reset the kill values which didn't exist and now have been overwritten by later values
					new_player->side_log[side].helicopters_lost = new_player->side_log[side].kills.deaths;
					new_player->side_log[side].kills.fixed_wing = 0;
					new_player->side_log[side].kills.helicopter = new_player->side_log[side].kills.air;  // assume all airkills are helicopters... most probably are
					new_player->side_log[side].kills.air_defence = 0;
					new_player->side_log[side].kills.armour = 0;
					new_player->side_log[side].kills.artillery = 0;

					// recopy weapons usage data
					memcpy(&new_player->side_log[side].weapon_usage, &v1_log.weapon_usage, sizeof(v1_log.weapon_usage));
				}
				else
					fread ( &new_player->side_log[side], sizeof(player_side_log_type), 1, file_ptr );

				new_player->side_log[side].warzone_log = NULL;

				for ( level = 0; level < NUM_PLAYER_LEVELS; level ++ )
				{
	
					if ( new_player->side_log [side].level [level] < command_line_player_start_rank )
					{
	
						new_player->side_log [side].level [level] = command_line_player_start_rank;
					}
				}
			}

			// set player log list

			if (loop == 0)
			{
				set_player_log_list (new_player);

				rebuild_player_log_list ();
			}

			//
			// set current player
			//

			if ( ( loop == current_player_index ) || ( loop == 0 ) )
			{
				set_current_player_log ( new_player );

				rebuild_player_log_list ();
			}
		}

		fclose (file_ptr);
	}
	else
	{

		int
			side;

		new_player = create_empty_player_log ();

		// name
			
		new_player->name = (char *) malloc_heap_mem (sizeof (char) * (strlen (DEFAULT_LOG_NAME) + 2));
	
		sprintf ( new_player->name, "%s", DEFAULT_LOG_NAME );

		for (side = 0; side < NUM_ENTITY_SIDES; side++)
		{

			for (level = 0; level < NUM_PLAYER_LEVELS; level ++)
			{

				new_player->side_log [side].level [level] = command_line_player_start_rank;
			}
		}

		set_player_log_list (new_player);
		
		set_current_player_log (new_player);

		rebuild_player_log_list ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void save_player_list (void)
{

	#if 1
	//
	// save binary file
	//
	{
		FILE
			*file_ptr;
	
		player_log_type
			*current_player;

		int
			side,
			num_entries,
			string_length,
			current_player_index;
	
		file_ptr = safe_fopen ("players2.bin", "wb");
	
		num_entries = 0;

		current_player = get_player_log_list ();
	
		current_player_index = -1;

		fwrite (&num_entries, sizeof (int), 1, file_ptr);

		fwrite (&current_player_index, sizeof (int), 1, file_ptr);

		while (current_player)
		{
			//
			// store currently selected player
			//

			if (current_player == get_current_player_log ())
			{
				current_player_index = num_entries;
			}

			// name

			if (current_player->name)
			{
				string_length = strlen (current_player->name) + 1;			// add 1 to include null terminator

				fwrite (&string_length, sizeof (int), 1, file_ptr);

				fwrite (current_player->name, 1, string_length, file_ptr);
			}
			else
			{
				string_length = 0;

				fwrite (&string_length, sizeof (int), 1, file_ptr);
			}

			fwrite ( &current_player->unique_id, sizeof ( int ), 1, file_ptr );

			// date commissioned

			fwrite (&(current_player->date_commissioned), sizeof (player_commissioned_type), 1, file_ptr);

			// write individual side logs

			for (side = 0; side <= NUM_ENTITY_SIDES; side ++)
			{
				fwrite (&(current_player->side_log [side]), sizeof (player_side_log_type), 1, file_ptr);
			}

			num_entries ++;

			current_player = get_player_log_next (current_player);
		}

		fseek (file_ptr, 0, SEEK_SET);

		fwrite (&num_entries, sizeof (int), 1, file_ptr);

		fwrite (&current_player_index, sizeof (int), 1, file_ptr);

		fclose (file_ptr);
	}

	#else

	//
	// save text file
	//
	{
		FILE
			*file_ptr;
	
		player_log_type
			*current_player;
	
		file_ptr = safe_fopen ("players.log", "w");
	
		//
		// Start
		//
	
		set_file_comment (file_ptr, "/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////");
		set_file_tag (file_ptr, FILE_TAG_START);
		set_file_comment (file_ptr, "/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////");
	
		//
		// Players
		//
	
		//current_player = get_ui_object_child (player_list);
	
		current_player = get_player_log_list ();
	
		while (current_player)
		{
	
			//if (get_ui_object_text (current_player), file_ptr)
			{
	
				set_file_new_line (file_ptr, 1);
		
				set_file_comment (file_ptr, "/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////");
				set_file_tag (file_ptr, FILE_TAG_PLAYER);
	
				set_file_tag (file_ptr, FILE_TAG_NAME);
				set_file_string (file_ptr, get_player_log_name (current_player));
	
				set_file_tag (file_ptr, FILE_TAG_PILOT_EXPERIENCE);
				set_file_int (file_ptr, get_player_log_experience (get_global_gunship_side (), current_player));
	
				set_file_tag (file_ptr, FILE_TAG_PILOT_LEVEL);
				set_file_int (file_ptr, get_player_log_level (get_global_gunship_side (), current_player));
	
				//
				//
				//
	
				if (strcmp (direct_play_get_player_name (direct_play_get_player_id ()), get_player_log_name (current_player)) == 0)
				{
	
					set_file_tag (file_ptr, FILE_TAG_CURRENT_PLAYER);
				}
	
				set_file_comment (file_ptr, "/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////");
			}
	
			current_player = get_player_log_next (current_player);
		}
	
		set_file_new_line (file_ptr, 1);
	
		set_file_comment (file_ptr, "/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////");
		set_file_tag (file_ptr, FILE_TAG_END);
		set_file_comment (file_ptr, "/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////");
	
		fclose (file_ptr);
	}

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_player_log_unique_id ( void )
{

	int
		id,
		unique;

	player_log_type
		*player;

	id = 1;

	unique = FALSE;

	while ( !unique )
	{

		unique = TRUE;

		player = get_player_log_list ();

		while ( player )
		{

			if ( player->unique_id == id )
			{

				unique = FALSE;

				break;
			}

			player = player->next;
		}

		if ( !unique )
		{

			id++;
		}
	}

	return ( id );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

player_log_type *create_empty_player_log ( void )
{

	player_log_type
		*new_player_log,
		*list;

	int
		side,
		d,
		m,
		y;

	new_player_log = (player_log_type *) malloc_heap_mem (sizeof (player_log_type));

	memset (new_player_log, 0, sizeof (player_log_type));

	new_player_log->unique_id = get_player_log_unique_id ();

	get_system_date (&d, &m, &y);

	new_player_log->date_commissioned.day = d;
	new_player_log->date_commissioned.month = m;
	new_player_log->date_commissioned.year = y;

	for (side = 0; side < NUM_ENTITY_SIDES; side++)
	{
		memset (&new_player_log->side_log [side], 0, sizeof (player_side_log_type));

		new_player_log->side_log [side].rank = bound (command_line_player_start_rank, PILOT_RANK_LIEUTENANT, PILOT_RANK_COLONEL);

		new_player_log->side_log [side].experience = get_player_points_from_rank ( command_line_player_start_rank );
	}

	new_player_log->next = NULL;

	list = get_player_log_list ();

	if ( list )
	{

		while ( list->next )
		{

			list = list->next;
		}

		list->next = new_player_log;
	}
	else
	{
	
		set_player_log_list (new_player_log);
	}

	return new_player_log;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

player_log_type *create_player_log (const char *name)
{

	player_log_type
		*new_player_log;

	ASSERT (name);

	new_player_log = create_empty_player_log ();

	new_player_log->name = (char *) malloc_heap_mem (strlen (name) + 2);

	sprintf (new_player_log->name, "%s", name);

	if ( strlen ( name ) > MAXIMUM_PLAYER_NAME )
	{

		new_player_log->name[MAXIMUM_PLAYER_NAME-1] = '\0';
	}

	#if DEBUG_MODULE

	//debug_log ("PLAY_SC: Creating player log %s", name);

	#endif

	return new_player_log;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

player_log_type *rename_player_log (int id, const char *name)
{

	player_log_type
		*player;

	ASSERT (name);

	player = get_player_log_list ();

	while ( ( player ) && ( player->unique_id != id ) )
	{

		player = player->next;
	}

	ASSERT ( player );

	if ( player->name )
	{

		free_mem ( player->name );

		player->name = NULL;
	}

	player->name = (char *) malloc_heap_mem (strlen (name) + 2);

	sprintf (player->name, "%s", name);

	if ( strlen ( player->name ) > MAXIMUM_PLAYER_NAME-1 )
	{

		player->name[MAXIMUM_PLAYER_NAME-1] = '\0';
	}

	return player;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rebuild_player_log_list ( void )
{
	#if (!DEMO_VERSION)
	
	char
		buf[100];

	int
		count;

	ui_object
		*list_item,
		*selected_item;

	player_log_type
		*player_log,
		*current_log;

	ui_object_destroy_list_items (player_list);

	player_log = get_player_log_list ();

	selected_item = NULL;

	current_log = NULL;

	count = 0;

	while (player_log)
	{

		if (get_player_log_name (player_log))
		{

			#if DEBUG_MODULE

			//debug_log ( "Creating list for %s, %d", player_log->name, player_log->unique_id );

			#endif

			list_item = add_to_pop_up_list ( get_player_log_name ( player_log ), player_list, NULL, player_log->unique_id, UI_FONT_ARIAL_18, ui_list_text_default_colour);

			set_ui_frontend_list_object_highlightable (list_item);

			if (list_item)
			{

				set_ui_object_item_number2 ( list_item, player_log->unique_id );
		
				// set this log to unselected
	
				set_ui_object_state (list_item, UI_OBJECT_STATE_OFF);
	
				if (player_log == get_current_player_log ())
				{
					current_log = player_log;

					selected_item = list_item;
				}
			}
		}
		else
		{
			debug_log ("PLAY_SC: warning: Player log without name");
		}

		count ++;

		player_log = get_player_log_next (player_log);
	}

	// if a log is selected, get info from it

	if (current_log != NULL)
	{
		int
			d,
			m,
			y;

	char
		buf2[100];

		rebuild_general_log_list (current_log, player_log_current_side);
		rebuild_flight_hours_list (current_log, player_log_current_side);
		rebuild_weapon_log_list (current_log, player_log_current_side);		

		// set this log to selected
	
		set_ui_object_state (selected_item, UI_OBJECT_STATE_ON);
	
		// set text for commission date & rank
	
		set_ui_object_text ( current_player_rank_text, get_pilot_rank_name ( current_log->side_log[player_log_current_side].rank ));

		d = current_log->date_commissioned.day;
		m = current_log->date_commissioned.month;
		y = current_log->date_commissioned.year;

		sprintf (buf, "%s: ", get_trans ("Date Commissioned"));

		if (d < 10)
		{
			sprintf (buf2, "0");

			strcat (buf, buf2);
		}
		sprintf (buf2, "%d/", d);

		strcat (buf, buf2);

		if (m < 10)
		{
			sprintf (buf2, "0");

			strcat (buf, buf2);
		}
		sprintf (buf2, "%d/", m);

		strcat (buf, buf2);

		if (y < 10)
		{
			sprintf (buf2, "0");

			strcat (buf, buf2);
		}
		sprintf (buf2, "%d", y);

		strcat (buf, buf2);

		set_ui_object_text (player_commision_date_text, buf);
	}

	debug_log ("PLAY_SC: built player log list with %d items", count);

	resize_player_list_size ();

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void destroy_player_log (player_log_type *player_log)
{

	player_log_type
		*last_player_log,
		*this_player_log;

	this_player_log = get_player_log_list ();

	last_player_log = NULL;

	while ( this_player_log )
	{

		if ( player_log == this_player_log )
		{

			if (last_player_log)
			{

				last_player_log->next = this_player_log->next;
			}
			else
			{

				set_player_log_list (this_player_log->next);
			}

			free_mem (this_player_log);

			break;
		}

		last_player_log = this_player_log;

		this_player_log = get_player_log_next (this_player_log);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void test_player_scoring (player_log_type *log, int side)
{
	float
		seconds;

	int
		i,
		campaign_threshold,
		campaign,
		score,
		result;

	ASSERT ((side >= 0) && (side <= NUM_ENTITY_SIDES));

	// approx. time required to complete a campaign
	campaign_threshold = 32000;

	campaign = 0;

	for (i = 0; i < 5000; i++)
	{
		score = (int) (frand1() * 1000.0);

		seconds = (600 + (frand1() * 1200.0));

		inc_player_log_flying_seconds (side, log, seconds);

		inc_player_log_experience (side, log, score);

		if (get_player_log_rank (side, log) != get_player_rank_from_points (get_player_log_experience (side, log)) )
		{
			set_player_log_rank (side, log, get_player_rank_from_points (get_player_log_experience (side, log)) );
		}
		
		set_player_log_missions_flown (side, log, i);

		if (get_player_log_flying_seconds (side, log) > campaign_threshold)
		{
			campaign_threshold += campaign_threshold;

			award_campaign_medal (side, campaign);

			debug_filtered_log ("Campaign Medal Awarded %2d score:%8d time:%8f", result, get_player_log_experience (side, log), get_player_log_flying_seconds (side, log));

			campaign = (campaign + 1) % 3;
		}

		if (result = award_aviator_wings (side))
		{
			debug_filtered_log ("Awarded Aviator Wings  %2d score:%8d time:%8f", result, get_player_log_experience (side, log), get_player_log_flying_seconds (side, log));
		}
		
		if (award_valour_medal (side, score) != -1)
		{
			debug_filtered_log ("Awarded Valour Medal   %2d score:%8d time:%8f", result, get_player_log_experience (side, log), get_player_log_flying_seconds (side, log));
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void resize_player_list_size (void)
{
	ui_object
		*slider;

	//float
		//y;

	set_ui_object_virtual_y_size (player_list, 1.0);
	set_ui_object_virtual_y_size (player_name_entry_area, 1.0);
/*
	// re-size the list objects when items are added

	y = max (1.0, get_next_list_position (player_list) / get_ui_object_y_size (player_list_area));
	y = 1.0;

	set_ui_object_virtual_y_size (player_list, y);
	set_ui_object_virtual_y_size (player_name_entry_area, y);

	// resize the slider on the player list

	*/

	slider = get_ui_object_vslider (player_list_area);
	recalculate_slider_size (slider);

	recalculate_slider_origin (slider);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
