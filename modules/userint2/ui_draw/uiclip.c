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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ui_clip_area (float *x_min, float *y_min, float *x_max, float *y_max)
{

	int
		clipped_flag = FALSE;

	float
		screen_min_x,
		screen_min_y,
		screen_max_x,
		screen_max_y;

	screen_min_x = 0 - ui_x_origin;
	screen_min_y = 0 - ui_y_origin;
	screen_max_x = get_screen_width (active_screen) - ui_x_origin;
	screen_max_y = get_screen_height (active_screen) - ui_y_origin;

	//
	// clip to left extent
	//

	if (*x_min < active_viewport.x_min - ui_x_origin)
	{

		*x_min = active_viewport.x_min - ui_x_origin;

		clipped_flag = TRUE;
	}

	// clip to screen

	if (*x_min < screen_min_x)
	{

		*x_min = screen_min_x;

		clipped_flag = TRUE;
	}

	// guarentee valid area

	if (*x_max < *x_min)
	{

		*x_max = *x_min;

		clipped_flag = TRUE;
	}

	//
	// clip right
	//

	if (*x_max > active_viewport.x_max - ui_x_origin)
	{

		*x_max = active_viewport.x_max - ui_x_origin;

		clipped_flag = TRUE;
	}

	// clip to screen

	if (*x_max > screen_max_x)
	{

		*x_max = screen_max_x;

		clipped_flag = TRUE;
	}

	// guarentee valid area

	if (*x_min > *x_max)
	{

		*x_min = *x_max;

		clipped_flag = TRUE;
	}

	//
	// clip top
	//

	if (*y_min < active_viewport.y_min - ui_y_origin)
	{

		*y_min = active_viewport.y_min - ui_y_origin;

		clipped_flag = TRUE;
	}

	// clip to screen

	if (*y_min < screen_min_y)
	{

		*y_min = screen_min_y;

		clipped_flag = TRUE;
	}

	// guarentee valid area

	if (*y_max < *y_min)
	{

		*y_max = *y_min;

		clipped_flag = TRUE;
	}

	//
	// clip bottom
	//

	if (*y_max > active_viewport.y_max - ui_y_origin)
	{

		*y_max = active_viewport.y_max - ui_y_origin;

		clipped_flag = TRUE;
	}

	// clip to screen

	if (*y_max > screen_max_y)
	{

		*y_max = screen_max_y;

		clipped_flag = TRUE;
	}

	// guarentee valid area

	if (*y_min > *y_max)
	{

		*y_min = *y_max;

		clipped_flag = TRUE;
	}

	return clipped_flag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ui_get_clip_area ( float *xmin, float *ymin, float *xmax, float *ymax )
{

	*xmin = active_viewport.x_min - ui_x_origin;
	*ymin = active_viewport.y_min - ui_y_origin;
	*xmax = active_viewport.x_max - ui_x_origin;
	*ymax = active_viewport.y_max - ui_y_origin;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int check_ui_object_clipped (ui_object *obj)
{

	int
		flag;

	ui_object
		*parent;

	float
		x1,
		x2,
		y1,
		y2,
		x_min,
		y_min,
		x_max,
		y_max,
		old_vp_x1,
		old_vp_y1,
		old_vp_x2,
		old_vp_y2;

	old_vp_x1 = active_viewport.x_min;
	old_vp_y1 = active_viewport.y_min;
	old_vp_x2 = active_viewport.x_max;
	old_vp_y2 = active_viewport.y_max;

	parent = get_ui_object_parent (obj);

	ASSERT (parent);

	x1 = get_ui_object_x (parent);
	y1 = get_ui_object_y (parent);
	x2 = x1 + get_ui_object_x_size (parent);
	y2 = y1 + get_ui_object_y_size (parent);

	x_min = get_ui_object_x (obj);
	y_min = get_ui_object_y (obj);
	x_max = x_min + get_ui_object_x_size (obj);
	y_max = y_min + get_ui_object_y_size (obj);
	
	set_viewport (x1, y1, x2, y2);

	flag = ui_clip_area (&x_min, &y_min, &x_max, &y_max);

	set_viewport (old_vp_x1, old_vp_y1, old_vp_x2, old_vp_y2);

	return flag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

