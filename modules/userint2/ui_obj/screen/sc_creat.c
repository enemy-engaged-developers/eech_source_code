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

static void create_screen_ui_object (ui_object *obj, ui_object_types type, va_list pargs)
{

   screen_ui_object
      *new_screen;

	increase_ui_object_counter ();

   ////////////////////////////////////////
   //
   // MALLOC ENTITY DATA
   //
   ////////////////////////////////////////

   obj->type = type;

   new_screen = (screen_ui_object *) safe_malloc (sizeof (screen_ui_object));

   obj->data = new_screen;

   ////////////////////////////////////////
   //
   // INITIALISE ALL ENTITY DATA TO 'WORKING' DEFAULT VALUES
   //
   // DO NOT USE ACCESS FUNCTIONS
   //
   // DO NOT USE RANDOM VALUES
   //
   ////////////////////////////////////////

   memset (new_screen, 0, sizeof (screen_ui_object));

   //new_screen->area.x = 0.0;
   //new_screen->area.y = 0.0;
   //new_screen->area.x_size = 0.0;
   //new_screen->area.y_size = 0.0;
	new_screen->area.colour_start.r = 255;
	new_screen->area.colour_start.g = 255;
	new_screen->area.colour_start.b = 255;
	new_screen->area.colour_start.a = 255;
	new_screen->area.colour_end.r = 255;
	new_screen->area.colour_end.g = 255;
	new_screen->area.colour_end.b = 255;
	new_screen->area.colour_end.a = 255;
   new_screen->area.x_origin = 0.0;
   new_screen->area.y_origin = 0.0;
   new_screen->area.drawable = 1;
   new_screen->area.item_number = -1;
   new_screen->area.redraw = 1;
   new_screen->area.moveable = 0;
   new_screen->area.resizeable = 0;
   new_screen->area.notify_on = NOTIFY_TYPE_DISPLAYED;
   new_screen->area.parent = NULL;
   new_screen->area.child = NULL;
   new_screen->area.next = NULL;
   new_screen->area.prev = NULL;
	new_screen->screen_id = ui_object_counter;

   ////////////////////////////////////////
   //
   // OVERWRITE DEFAULTS WITH GIVEN ATTRIBUTES
   //
   ////////////////////////////////////////

   set_ui_object_attributes (obj, pargs);

   ////////////////////////////////////////
   //
   // INTEGRATE INTO SYSTEM
   //
   ////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_screen_ui_object_create_functions (ui_object_types type)
{

	fn_create_ui_object [type] = create_screen_ui_object;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
