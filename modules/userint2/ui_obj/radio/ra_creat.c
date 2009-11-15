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

#include "userint2.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void create_radio_ui_object (ui_object *obj, ui_object_types type, va_list pargs)
{

   radio_ui_object
      *new_object;

	increase_ui_object_counter ();

   ////////////////////////////////////////
   //
   // MALLOC ENTITY DATA
   //
   ////////////////////////////////////////

   obj->type   = type;

   new_object    = (radio_ui_object *) safe_malloc (sizeof (radio_ui_object));

   obj->data   = new_object;

   ////////////////////////////////////////
   //
   // INITIALISE ALL ENTITY DATA TO 'WORKING' DEFAULT VALUES
   //
   // DO NOT USE ACCESS FUNCTIONS
   //
   // DO NOT USE RANDOM VALUES
   //
   ////////////////////////////////////////

   memset (new_object, 0, sizeof (radio_ui_object));

   //new_object->area.x = 0.0;
   //new_object->area.y = 0.0;
   //new_object->area.x_size = 0.0;
   //new_object->area.y_size = ui_get_font_height () + 4;
	new_object->area.colour_start.r = 255;
	new_object->area.colour_start.g = 255;
	new_object->area.colour_start.b = 255;
	new_object->area.colour_start.a = 255;
	new_object->area.colour_end.r = 255;
	new_object->area.colour_end.g = 255;
	new_object->area.colour_end.b = 255;
	new_object->area.colour_end.a = 255;
   new_object->area.x_origin = 0.0;
   new_object->area.y_origin = 0.0;
   new_object->area.drawable = 1;
   new_object->area.item_number = -1;
   new_object->area.redraw = 1;
   new_object->area.moveable = 0;
   new_object->area.resizeable = 0;
   new_object->area.text_justify = TEXT_JUSTIFY_CENTRE;
   new_object->area.notify_on = NOTIFY_TYPE_BUTTON_DOWN;
   new_object->area.parent = NULL;
   new_object->area.child = NULL;
   new_object->area.next = NULL;
   new_object->area.prev = NULL;
   new_object->area.font_type = UI_FONT_ARIAL_10;
   new_object->area.font_colour_end = default_unselected_text_colour;
   new_object->area.font_colour_start = default_unselected_text_colour;
   new_object->area.highlighted_font_type = -1;
   new_object->area.highlighted_font_colour_end = default_selected_text_colour;
   new_object->area.highlighted_font_colour_start = default_selected_text_colour;
   new_object->area.selected_font_type = -1;
   new_object->area.selected_font_colour_end = default_selected_text_colour;
   new_object->area.selected_font_colour_start = default_selected_text_colour;

   new_object->area.state = 0;

   ////////////////////////////////////////
   //
   // OVERWRITE DEFAULTS WITH GIVEN ATTRIBUTES
   //
   ////////////////////////////////////////

   set_ui_object_attributes (obj, pargs);

   ////////////////////////////////////////
	//
	// Check the font default values & override them if not set
	//
   ////////////////////////////////////////

	if ( new_object->area.font_type == -1 )
	{

		new_object->area.font_type = get_ui_font_type ();
	}

	if ( new_object->area.highlighted_font_type == -1 )
	{

		new_object->area.highlighted_font_type = new_object->area.font_type;
	}

	if ( new_object->area.selected_font_type == -1 )
	{

		new_object->area.selected_font_type = new_object->area.font_type;
	}

   ////////////////////////////////////////
   //
   // INTEGRATE INTO SYSTEM
   //
   ////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_radio_ui_object_create_functions (ui_object_types type)
{

	fn_create_ui_object [type] = create_radio_ui_object;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
