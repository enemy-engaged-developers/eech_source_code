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

//	#define's used for ui_object placement & sizing for options

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// screen title positions & sizes

#define TITLE_TEXT_POSITION_X					0.025

#define TITLE_TEXT_POSITION_Y					0.039

#define TITLE_TEXT_WIDTH						(0.95 - TITLE_TEXT_POSITION_X)

#define TITLE_TEXT_HEIGHT						0.039


// text option button backdrop graphics

#define TEXT_OPTION_BDROP_WIDTH				0.483

#define TEXT_OPTION_BDROP_HEIGHT				0.057


// main screen button dimensions

#define MAIN_BUTTON_WIDTH 						0.05

#define MAIN_BUTTON_HEIGHT 					0.06


// area for buttons & titles

#define OPTION_AREA_HEIGHT 					0.058

#define OPTION_AREA_WIDTH 						1.0


// title box sizes & offsets

#define OPTION_BOX_HEIGHT 						1.000 

#define OPTION_BOX_WIDTH 						0.298

#define OPTION_TITLE_OFFSET_X					0.117

#define OPTION_TITLE_OFFSET_Y					0.260


// button sizes

#define OPTION_BOX_SMALL_WIDTH 				0.108

#define OPTION_BOX_MEDIUM_WIDTH 				0.169

#define OPTION_BOX_LARGE_WIDTH 				0.298

#define OPTION_BOX_EXTRA_LARGE_WIDTH 		0.45


// gaps between buttons

#define OPTION_BOX_GAP_HEIGHT 				0.004

#define OPTION_BOX_GAP_WIDTH 					0.0026


// option box text is right justified

#define OPTION_BOX_TEXT_OFFSET_X 			0.95
	
#define OPTION_BOX_TEXT_OFFSET_Y 			0.143


// option button text is left justified

#define OPTION_BUTTON_TEXT_OFFSET_X 		0.008

#define OPTION_AREA_OFFSET_Y (OPTION_AREA_HEIGHT + OPTION_BOX_GAP_HEIGHT)



// area for buttons & titles

#define SETUP_AREA_HEIGHT 						0.058

#define SETUP_AREA_WIDTH 						0.466


// title box sizes

#define SETUP_BOX_HEIGHT 						1.000 

#define SETUP_BOX_WIDTH 						0.635


// button sizes

#define SETUP_BOX_SMALL_WIDTH 				0.142

#define SETUP_BOX_MEDIUM_WIDTH 				0.360 

#define SETUP_BOX_LARGE_WIDTH 				0.360


// gaps between buttons

#define SETUP_BOX_GAP_HEIGHT 					0.004

#define SETUP_BOX_GAP_WIDTH 					0.004

#define SETUP_DIVIDER_HEIGHT					0.075


// option box text is right justified

#define SETUP_BOX_TEXT_OFFSET_X 			0.597
	
#define SETUP_BOX_TEXT_OFFSET_Y 			0.143


// option button text is left justified

//#define SETUP_BUTTON_TEXT_OFFSET_X 		0.666

#define SETUP_BUTTON_TEXT_OFFSET_X 		0.05

#define SETUP_AREA_OFFSET_Y (OPTION_AREA_HEIGHT + OPTION_BOX_GAP_HEIGHT)


// fade in time for buttons & areas

#define OPTIONS_BUTTON_AREA_FADE_TIME 		400

#define OPTIONS_BUTTON_AREA_OFFSET_TIME 	0


// ok, cancel & exit button positions

#define OPTIONS_OK_BUTTON_POS_X 				0.038

#define OPTIONS_OK_BUTTON_POS_Y 				0.829

#define OPTIONS_CANCEL_BUTTON_POS_X 		0.038

#define OPTIONS_CANCEL_BUTTON_POS_Y 		0.877


// ok, cancel, exit button sizes

#define OPTIONS_OK_BUTTON_X 					0.150

#define OPTIONS_OK_BUTTON_Y 					0.050

#define OPTIONS_CANCEL_BUTTON_X 				0.150

#define OPTIONS_CANCEL_BUTTON_Y 				0.050

#define OPTIONS_EXIT_BUTTON_X 				0.100

#define OPTIONS_EXIT_BUTTON_Y 				0.050

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern ui_object
	*main_screen,
	*pilots_button,
	*credits_button,
	*ghost_pilots_button,
	*ghost_credits_button;

extern float
	main_screen_t_value;

extern texture_graphic
	*main_screen_texture,
	*main_screen2_texture,
	*main_screen_sprite_texture,
	*options_box_small,
	*options_box_medium,
	*options_box_large,
	*options_box_extra_large,
	*text_box_graphic,
	*text_option_bdrop,
	*list_box_graphic;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void initialise_main_screen (void);

extern void draw_main_screen_background ( ui_object *obj, void *data );

extern void set_frontend_slider_graphics (ui_object *parent);

extern void set_ui_list_spacing_proportional_to_font (ui_object *list, float scaling);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
