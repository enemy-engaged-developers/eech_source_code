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

#include "graphics.h"

#include "3d.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int recurse_count_redraw_number (ui_object *obj);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_ui_screen_stack (void)
{

	float
		x1,
		y1,
		x2,
		y2,
		x_origin,
		y_origin;

	ui_object
		*screen_stack_head;

	screen_ui_object
		*screen;

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

	if ( begin_3d_scene () )
	{

		set_d3d_alpha_fog_zbuffer ( FALSE, FALSE, FALSE, FALSE );

		screen_stack_head = get_ui_screen_stack_head ();
	
		if (screen_stack_head)
		{
		
			screen = (screen_ui_object *) screen_stack_head->data;
		
			if (screen->area.drawable)
			{
	
				set_ui_object_redraw (screen_stack_head, TRUE);
	
				draw_ui_object (screen_stack_head);
	
				// set up the viewport for this screen
	
				if (screen->area.child)
				{
	
					x_origin = get_ui_object_x_origin (screen_stack_head);
	
					y_origin = get_ui_object_y_origin (screen_stack_head);
			
					x1 = get_ui_object_x (screen_stack_head);
	
					y1 = get_ui_object_y (screen_stack_head);
			
					x2 = x1 + get_ui_object_x_size (screen_stack_head);
	
					y2 = y1 + get_ui_object_y_size (screen_stack_head);
			
					set_viewport (x1, y1, x2, y2);
			
					ui_set_origin (x_origin, y_origin);
	
					update_ui_object (screen->area.child);
				}
		
				if (screen->area.next)
				{
		
					update_ui_object (screen->area.next);
				}
			}
		}

		end_3d_scene ();
	}

	set_viewport (old_viewport_x1, old_viewport_y1, old_viewport_x2, old_viewport_y2);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int update_ui_screen_stack_redraw_count (void)
{

	ui_object
		*obj;

	int
		ui_user_function_count,
		max_redraw_count;

	max_redraw_count = 0;

	ui_user_function_count = 0;

	obj = get_ui_screen_stack_head ();

	max_redraw_count = recurse_count_redraw_number (obj);

	if (ui_user_redraw_function)
	{

		ui_user_function_count = ui_user_redraw_function ();
	}

	max_redraw_count = max (max_redraw_count, ui_user_function_count);

	//debug_log ("SCREEN UPDT: max redraw count = %d", max_redraw_count);

	if (max_redraw_count)
	{

		max_redraw_count = MAX_UI_REDRAW_NUMBER;
	}

	return max_redraw_count;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int recurse_count_redraw_number (ui_object *obj)
{

	area_ui_object
		*raw;

	int
		new_count,
		count;

	raw = (area_ui_object *) obj->data;

	count = 0;

	new_count = 0;

	if (get_ui_object_drawable (obj))
	{

		count = raw->redraw;

		if (raw->child)
		{
	
			new_count = recurse_count_redraw_number (raw->child);

			count = max (( int ) raw->redraw, new_count);
		}
	}

	if (raw->next)
	{

		new_count = recurse_count_redraw_number (raw->next);

		new_count = max (count, new_count);

		count = max ( ( int ) raw->redraw, new_count);
	}

	return count;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
