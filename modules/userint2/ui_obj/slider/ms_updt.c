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

static void update_mslider_ui_object (ui_object *obj)
{

	float
		parent_x1,
		parent_y1,
		parent_x2,
		parent_y2,
		parent_x_origin,
		parent_y_origin;

	float
		min,
		max,
		x1,
		y1,
		x2,
		y2;

	ui_object
		*object_to_slide,
		*parent;

   area_ui_object
      *area;

	float
		old_viewport_x1,
		old_viewport_y1,
		old_viewport_x2,
		old_viewport_y2;

   // store parents viewport data

	old_viewport_x1 = active_viewport.x_min;
	old_viewport_y1 = active_viewport.y_min;
	old_viewport_x2 = active_viewport.x_max;
	old_viewport_y2 = active_viewport.y_max;

   area = (area_ui_object *) obj->data;

	// Scroll if required

	if (scroll)
	{

		min = get_ui_object_slider_min (obj);
	
		max = get_ui_object_slider_max (obj);
	
		object_to_slide = get_ui_object_next (obj);
  
		scroll_slider (object_to_slide, min, max, scroll);
	}

	// store parents viewport data

	parent = get_ui_object_parent (obj);

	parent_x_origin = get_ui_object_x_origin (parent);

	parent_y_origin = get_ui_object_y_origin (parent);

	parent_x1 = get_ui_object_x (parent);

	parent_y1 = get_ui_object_y (parent);

	parent_x2 = parent_x1 + get_ui_object_x_size (parent);

	parent_y2 = parent_y1 + get_ui_object_y_size (parent);

   if (area->drawable)
   {

		ui_set_origin (0, 0);

      draw_ui_object (obj);

      if (area->child)
      {

			x1 = get_ui_object_x (obj);

			y1 = get_ui_object_y (obj);

			x2 = x1 + get_ui_object_x_size (obj);

			y2 = y1 + get_ui_object_y_size (obj);

			ui_clip_area (&x1, &y1, &x2, &y2);

			set_viewport (x1, y1, x2, y2);
	
			ui_set_origin (0, 0);
	
         update_ui_object (area->child);
      }
	}

	if (area->next)
	{

		parent = get_ui_object_parent (obj);

		if (parent)
		{
	
			set_viewport (parent_x1, parent_y1, parent_x2, parent_y2);
	
			ui_set_origin (parent_x_origin, parent_y_origin);
		}

		update_ui_object (area->next);
	}

	set_viewport (old_viewport_x1, old_viewport_y1, old_viewport_x2, old_viewport_y2);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_mslider_ui_object_update_functions (ui_object_types type)
{

	fn_update_ui_object [type] = update_mslider_ui_object;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
