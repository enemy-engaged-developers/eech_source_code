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

static void draw_close_ui_object (ui_object *obj)
{

	float
		x_size,
		y_size,
		x1,
		y1,
		x2,
		y2;

	struct SCREEN
		*old_active_screen;

	unsigned short int
		*graphic;

	close_ui_object
		*close;

	close = (close_ui_object *) obj->data;

	if (get_ui_object_redraw (obj))
	{

		x1 = get_ui_object_x (obj);
		
		y1 = get_ui_object_y (obj);

		x_size = get_ui_object_x_size (obj);

		y_size = get_ui_object_y_size (obj);

		x2 = x1 + x_size;
	
		y2 = y1 + y_size;

		old_active_screen = get_active_screen ();

		if (get_ui_object_active_screen (obj))
		{
	
			set_active_screen (get_ui_object_active_screen (obj));
		}
		else
		{

			set_active_screen (video_screen);
		}

		//if (lock_screen (active_screen))
		{
		
			graphic = get_ui_object_graphic (obj);
	
			if (!get_ui_object_clear (obj))
			{
		
				if (graphic)
				{
		
					ui_draw_graphic (x1, y1, x2, y2, graphic);
				}
				else
				{

					int
						old_state;

					old_state = get_ui_object_state (obj);

					if (get_ui_object_highlighted (obj))
					{

						set_ui_object_state (obj, UI_OBJECT_STATE_HIGHLIGHTED);
					}

					ui_draw_area (x1, y1, x2, y2, obj);

					set_ui_object_state (obj, old_state);
				}
			}
		
			//unlock_screen (active_screen);
		}

		set_active_screen (old_active_screen);
	
		set_ui_redraw (TRUE);

		close->area.redraw --;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_close_ui_object_draw_functions (ui_object_types type)
{

	fn_draw_ui_object [type] = draw_close_ui_object;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
