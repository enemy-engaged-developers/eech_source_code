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



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "userint.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ui_object_vslider_function (ui_object *obj, void *arg)
{

	obj;

	if ((int) arg == BUTTON_STATE_DOWN)
	{

		set_event (MOUSE_MOVE_UP, MODIFIER_NONE, BUTTON_STATE_EITHER, vslider_move_function);

		set_event (MOUSE_MOVE_DOWN, MODIFIER_NONE, BUTTON_STATE_EITHER, vslider_move_function);
	}
	else if ((int) arg == BUTTON_STATE_UP)
	{

		set_event (MOUSE_MOVE_UP, MODIFIER_NONE, BUTTON_STATE_EITHER, NULL);

		set_event (MOUSE_MOVE_DOWN, MODIFIER_NONE, BUTTON_STATE_EITHER, NULL);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void vslider_move_function (void *ev)
{

	float
		min,
		max,
		inc;

	ui_object
		*slider_object = nullptr;

	if (*captured_object)
	{
		min = get_ui_object_slider_min (*captured_object);
	
		max = get_ui_object_slider_max (*captured_object);
	
		inc = get_ui_object_slider_inc (*captured_object);

		slider_object = get_ui_object_next (*captured_object);
	
		scroll_slider (slider_object, min, max, -((event *) ev)->dy);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ui_object_vslider_decrease_function (ui_object *obj, void *ev)
{

	float
		min,
		max,
		inc;

	ui_object
		*parent_object = nullptr,
		*slider_object = nullptr;

	obj;
	ev;

	parent_object = get_ui_object_parent (obj);

	min = get_ui_object_slider_min (parent_object);

	max = get_ui_object_slider_max (parent_object);

	inc = get_ui_object_slider_inc (parent_object);

	slider_object = get_ui_object_next (parent_object);

	scroll_slider (slider_object, min, max, inc);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ui_object_vslider_increase_function (ui_object *obj, void *ev)
{

	float
		min,
			max,
		inc;

	ui_object
		*parent_object = nullptr,
		*slider_object = nullptr;

	obj;
	ev;

	parent_object = get_ui_object_parent (obj);

	min = get_ui_object_slider_min (parent_object);

	max = get_ui_object_slider_max (parent_object);

	inc = get_ui_object_slider_inc (parent_object);

	slider_object = get_ui_object_next (parent_object);

	scroll_slider (slider_object, min, max, -inc);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void scroll_slider (ui_object *slider_object, float min, float max, float inc)
{

	float
		pos;

	if (slider_object)
	{

		pos = get_ui_object_y_origin (slider_object);
	
		pos += inc;
	
		pos = bound ((int) pos, -max, min);

		set_ui_object_y_origin (slider_object, pos);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void recalculate_slider_size (ui_object *slider_object)
{

	ui_object
		*current_list_item = nullptr;

	float
		slider_size,
		y,
		y_size,
		ny;
	
	current_list_item = get_ui_object_next (slider_object);

	if (!current_list_item)
	{

//		debug_log ("WARNING: Can't locate the item to slide! (1)");

		return;
	}

	current_list_item = get_ui_object_child (current_list_item);

	if (!current_list_item)
	{

//		debug_log ("WARNING: Can't locate the item to slide! (2)");

		set_ui_object_slider_max (slider_object, 0);

		return;
	}

	// find last object to be slid

	while (get_ui_object_next (current_list_item))
	{

		current_list_item = get_ui_object_next (current_list_item);
	}

	// work out how much to slide

	slider_size = LIST_ITEM_SPACING;

	// allow for the size of the window

	slider_size -= get_ui_object_y_size (slider_object);

	y = get_ui_object_y (current_list_item);

	y_size = get_ui_object_y_size (current_list_item);

	ny = get_ui_object_y (slider_object);

	slider_size += y_size + y - ny;

	// and a little for luck, allows the last one to be well on the screen

	slider_size += LIST_ITEM_SPACING * 2;

	slider_size = max (0, slider_size);

	set_ui_object_slider_max (slider_object, slider_size);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
