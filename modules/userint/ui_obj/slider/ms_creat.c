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

static void create_mslider_ui_object (ui_object *obj, ui_object_types type, va_list pargs)
{

	ui_object
		*parent;

   slider_ui_object
      *new_mslider;

	increase_ui_object_counter ();

   ////////////////////////////////////////
   //
   // MALLOC ENTITY DATA
   //
   ////////////////////////////////////////

   obj->type   = type;

   new_mslider	= safe_malloc (sizeof (slider_ui_object));

   obj->data   = new_mslider;

   ////////////////////////////////////////
   //
   // INITIALISE ALL ENTITY DATA TO 'WORKING' DEFAULT VALUES
   //
   // DO NOT USE ACCESS FUNCTIONS
   //
   // DO NOT USE RANDOM VALUES
   //
   ////////////////////////////////////////

   memset (new_mslider, 0, sizeof (slider_ui_object));

   new_mslider->area.x = 0.0;
   new_mslider->area.y = 0.0;
   new_mslider->area.x_size = 20.0;
   new_mslider->area.y_size = 20.0;
   new_mslider->area.x_origin = 0.0;
   new_mslider->area.y_origin = 0.0;
   new_mslider->area.drawable = 1;
   new_mslider->area.item_number = -1;
   new_mslider->area.redraw = 1;
   new_mslider->area.moveable = 0;
   new_mslider->area.resizeable = 0;
   new_mslider->area.notify_on = NOTIFY_TYPE_BUTTON_EITHER;
   new_mslider->area.parent = NULL;
   new_mslider->area.child = NULL;
   new_mslider->area.next = NULL;
   new_mslider->area.prev = NULL;
   new_mslider->area.state = 0;

   new_mslider->slider_min = 0;
   new_mslider->slider_max = 100;
   new_mslider->slider_inc = 10;

   ////////////////////////////////////////
   //
   // OVERWRITE DEFAULTS WITH GIVEN ATTRIBUTES
   //
   ////////////////////////////////////////

   set_ui_object_attributes (obj, pargs);

	parent = get_ui_object_parent (obj);

	if (!parent)
	{

		debug_fatal ("ERROR: mslider_box MUST have a parent");
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

void overload_mslider_ui_object_create_functions (ui_object_types type)
{

	fn_create_ui_object [type] = create_mslider_ui_object;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
