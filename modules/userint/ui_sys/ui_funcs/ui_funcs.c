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

#include "userint.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_ui_global_functions (void)
{

	// set default functions

	set_ui_object_create_default_functions ();

	set_ui_object_draw_default_functions ();

	set_ui_object_position_default_functions ();

	set_ui_object_size_default_functions ();

	set_ui_object_origin_default_functions ();

	set_ui_object_flags_default_functions ();

	set_ui_object_colour_default_functions ();

	set_ui_object_links_default_functions ();

	set_ui_object_function_default_functions ();

	set_ui_object_notify_on_default_functions ();

	set_ui_object_update_default_functions ();

	set_ui_object_text_default_functions ();

	set_ui_object_graphic_default_functions ();

	// overload default functions

	initialise_area_ui_object_functions (UI_TYPE_AREA);
	
	initialise_button_ui_object_functions (UI_TYPE_BUTTON);
	
	initialise_radio_ui_object_functions (UI_TYPE_RADIO);
	
	initialise_toggle_ui_object_functions (UI_TYPE_TOGGLE);
	
	initialise_text_ui_object_functions (UI_TYPE_TEXT);
	
	initialise_screen_ui_object_functions (UI_TYPE_SCREEN);
	
	initialise_close_ui_object_functions (UI_TYPE_CLOSE_BOX);
	
	initialise_list_ui_object_functions (UI_TYPE_LIST_BOX);
	
	initialise_vslider_ui_object_functions (UI_TYPE_VSLIDER);
	
	initialise_mslider_ui_object_functions (UI_TYPE_MSLIDER);
	
	initialise_menu_ui_object_functions (UI_TYPE_MENU_STACK);
	
	initialise_input_ui_object_functions (UI_TYPE_INPUT);
	
	initialise_number_ui_object_functions (UI_TYPE_NUMBER);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
