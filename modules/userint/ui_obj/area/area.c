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

void ui_object_autosize (ui_object *obj)
{

	ui_object
		*child;

	area_ui_object
		*area;

	float
		x2 = 0.0,
		y2 = 0.0;

	debug_fatal ("UI_AUTOSIZE - NOT CODED YET!");

	child = get_ui_object_child (obj);

	while (child)
	{

		if (get_ui_object_autosize (child))
		{

			ui_object_autosize (child);
		}

		area = (area_ui_object *) child->data;

		if (area->x + area->x_size > x2)
		{

			x2 = area->x + area->x_size;
		}

		if (area->y + area->y_size > y2)
		{

			y2 = area->y + area->y_size;
		}

		child = get_ui_object_next (child);
	}

	set_ui_object_x_size (obj, x2);

	set_ui_object_y_size (obj, y2);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_text_position (float *x, float *y, float x1, float y1, float x2, float y2,ui_object *obj)
{

	float
		mid_x,
		mid_y,
		max_x,
		max_y;

	mid_x = x1 + (get_ui_object_x_size (obj) / 2) - (ui_get_string_length (get_ui_object_text (obj)) / 2);

	mid_y = y1 + (get_ui_object_y_size (obj) / 2) - (ui_get_font_height () / 2);

	max_x = x1 + get_ui_object_x_size (obj) - ui_get_string_length (get_ui_object_text (obj)) - 5;

	max_y = y1 + get_ui_object_y_size (obj) - ui_get_font_height () - 5;

	*x = mid_x;

	*y = mid_y;

	switch (get_ui_object_text_justify (obj))
	{

		case TEXT_JUSTIFY_CENTRE:
		{

			break;
		}
		case TEXT_JUSTIFY_LEFT_CENTRE:
		{

			*x = x1 + 5;

			break;
		}
		case TEXT_JUSTIFY_RIGHT_CENTRE:
		{

			*x = max_x;

			break;
		}
		case TEXT_JUSTIFY_CENTRE_TOP:
		{

			*y = y1 + 5;

			break;
		}
		case TEXT_JUSTIFY_LEFT_TOP:
		{

			*x = x1 + 5;
			*y = y1 + 5;

			break;
		}
		case TEXT_JUSTIFY_RIGHT_TOP:
		{

			*x = max_x;
			*y = y1 + 5;

			break;
		}
		case TEXT_JUSTIFY_CENTRE_BOTTOM:
		{

			*y = max_y;

			break;
		}
		case TEXT_JUSTIFY_LEFT_BOTTOM:
		{

			*x = x1 + 5;
			*y = max_y;

			break;
		}
		case TEXT_JUSTIFY_RIGHT_BOTTOM:
		{

			*x = max_x;
			*y = max_y;

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
