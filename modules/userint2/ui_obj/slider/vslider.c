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



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "userint2.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// NB: if vslider object is "clear" it will switch itself off when not needed (ie. list not long enough to slider)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ui_object
	*slider_area = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ui_object_vslider_function (ui_object *obj, void *arg)
{

	obj;

	if ((int) arg == BUTTON_STATE_DOWN)
	{

		slider_area = obj;

		set_event (MOUSE_MOVE_UP, MODIFIER_MOUSE_LEFT_BUTTON, BUTTON_STATE_EITHER, vslider_move_function); 

		set_event (MOUSE_MOVE_DOWN, MODIFIER_MOUSE_LEFT_BUTTON, BUTTON_STATE_EITHER, vslider_move_function);
	}
	else if ((int) arg == BUTTON_STATE_UP)
	{

		slider_area = NULL;

		set_event (MOUSE_MOVE_UP, MODIFIER_MOUSE_LEFT_BUTTON, BUTTON_STATE_EITHER, NULL);

		set_event (MOUSE_MOVE_DOWN, MODIFIER_MOUSE_LEFT_BUTTON, BUTTON_STATE_EITHER, NULL);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void vslider_move_function (event *ev)
{

	float
		pos,
		max,
		inc;

	ui_object
		*slider;

	if (*captured_object)
	{

		if (*captured_object == slider_area)
		{
	
			slider = get_ui_object_parent (*captured_object);
		
			if (slider)
			{
	
				inc = ev->dy;
	
				// make sure mouse is either on slider or next to (not above or below)
				if (highlighted_object != *captured_object)
				{
	
					if ((get_mouse_y () < get_ui_object_y (slider) + (UI_SLIDER_VIRTUAL_HEIGHT * get_screen_height (video_screen))) ||
						(get_mouse_y () > (get_ui_object_y (slider) + get_ui_object_y_size (slider) - (UI_SLIDER_VIRTUAL_HEIGHT * get_screen_height (video_screen)))))
					{
		
						return;
					}
				}
		
				pos = get_ui_object_y (*captured_object) - get_ui_object_y (slider);
			
				pos += inc;

				max = get_ui_object_y_size (slider);
			
				pos = bound (pos, UI_SLIDER_VIRTUAL_HEIGHT * get_screen_height (video_screen), (max - (UI_SLIDER_VIRTUAL_HEIGHT * get_screen_height (video_screen))) - get_ui_object_y_size (*captured_object));
		
				set_ui_object_virtual_y (*captured_object, pos / max);
		
				recalculate_slider_origin (slider);
			}
		}
		else
		{

			slider_area = NULL;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ui_object_vslider_decrease_function (ui_object *obj, void *ev)
{

	float
		pos,
		max,
		inc;

	ui_object
		*slider,
		*slider_object;

	slider = get_ui_object_association (obj);

	slider_object = get_ui_object_parent (obj);

	max = get_ui_object_y_size (slider_object);
	inc = get_ui_object_slider_inc (slider_object);

	pos = get_ui_object_y (slider) - get_ui_object_y (slider_object);
	
	pos -= inc;
	
	pos = bound (pos, UI_SLIDER_VIRTUAL_HEIGHT * get_screen_height (video_screen), (max - (UI_SLIDER_VIRTUAL_HEIGHT * get_screen_height (video_screen))) - get_ui_object_y_size (slider));
	
	set_ui_object_virtual_y (slider, pos / max);

	recalculate_slider_origin (slider_object);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ui_object_vslider_increase_function (ui_object *obj, void *ev)
{

	float
		pos,
		max,
		inc;

	ui_object
		*slider,
		*slider_object;

	slider = get_ui_object_association (obj);

	slider_object = get_ui_object_parent (obj);

	max = get_ui_object_y_size (slider_object);
	inc = get_ui_object_slider_inc (slider_object);

	pos = get_ui_object_y (slider) - get_ui_object_y (slider_object);
	
	pos += inc;
	
	pos = bound (pos, UI_SLIDER_VIRTUAL_HEIGHT * get_screen_height (video_screen), (max - (UI_SLIDER_VIRTUAL_HEIGHT * get_screen_height (video_screen))) - get_ui_object_y_size (slider));
	
	set_ui_object_virtual_y (slider, pos / max);

	recalculate_slider_origin (slider_object);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void scroll_slider (ui_object *slider_object, float min, float max, float inc)
{

	ui_object
		*parent;

	float
		pos;

	if (slider_object)
	{

		parent = get_ui_object_association (slider_object);

		// make sure mouse is either on slider or next to (not above or below)
		if (highlighted_object != slider_object)
		{

			if ((get_mouse_y () < get_ui_object_y (parent) + UI_SLIDER_VIRTUAL_HEIGHT) ||
				(get_mouse_y () > (get_ui_object_y (parent) + get_ui_object_y_size (parent) - UI_SLIDER_VIRTUAL_HEIGHT)))
			{

				return;
			}
		}

		pos = get_ui_object_y (slider_object) - get_ui_object_y (parent);
	
		pos += inc;
	
		pos = bound (pos, min + UI_SLIDER_VIRTUAL_HEIGHT, max - UI_SLIDER_VIRTUAL_HEIGHT - get_ui_object_y_size (slider_object));

		set_ui_object_y (slider_object, pos);

		recalculate_slider_origin (parent);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void recalculate_slider_size (ui_object *slider_object)
{

	ui_object
		*parent,
		*slider_area,
		*object_to_slide;

	float
		overhang,
		object_y,
		object_y_size,
		slider_y,
		slider_y_size,
		virtual_slider_y_size,
		new_slider_size,
		new_slider_virtual_size,
		total_slider_y_size;

	total_slider_y_size = 0.0;
	
	// get the slider area

	slider_area = get_ui_object_association (slider_object);

	// get the slider size

	slider_y = get_ui_object_y (slider_object);

	slider_y_size = get_ui_object_y_size (slider_object) - (2.0 * (UI_SLIDER_VIRTUAL_HEIGHT * get_screen_height (video_screen)));

	// get total "objects to slide" size

	parent = get_ui_object_parent (slider_object);

	virtual_slider_y_size = slider_y_size / get_ui_object_y_size (parent);

	object_to_slide = get_ui_object_child (parent);

	while (object_to_slide)
	{

		if (get_ui_object_type (object_to_slide) != UI_TYPE_VSLIDER)
		{

			object_y = get_ui_object_y (object_to_slide);
			object_y_size = get_ui_object_y_size (object_to_slide);

			if (get_ui_object_type (object_to_slide) == UI_TYPE_LIST_BOX)
			{

				object_y_size = get_next_list_position (object_to_slide);
			}
	
			if (total_slider_y_size < (object_y - slider_y + object_y_size))
			{
	
				total_slider_y_size = (object_y - slider_y + object_y_size);
			}
		}

		object_to_slide = get_ui_object_next (object_to_slide);
	}

	// switch slider on if needed

	if (total_slider_y_size > get_ui_object_y_size (slider_object))
	{

		set_ui_object_drawable (slider_object, TRUE);

		// find amount the object overhang by

		overhang = total_slider_y_size - get_ui_object_y_size (slider_object);

		// new slider size
	
		new_slider_size = (slider_y_size * get_ui_object_y_size (slider_object)) / total_slider_y_size;

		new_slider_size = bound (new_slider_size, UI_SLIDER_VIRTUAL_WIDTH * get_screen_width (video_screen), slider_y_size);

		new_slider_virtual_size = new_slider_size / get_ui_object_y_size (slider_object);
	
		set_ui_object_virtual_y_size (slider_area, new_slider_virtual_size);

		{

			float
				new_slider_y;

			new_slider_y = bound (get_ui_object_y (slider_area) - get_ui_object_y (slider_object),
													UI_SLIDER_VIRTUAL_HEIGHT * get_screen_height (video_screen),
													(get_ui_object_y_size (slider_object) - (UI_SLIDER_VIRTUAL_HEIGHT * get_screen_height (video_screen))) - new_slider_size);
		
			set_ui_object_virtual_y (slider_area, new_slider_y / get_ui_object_y_size (slider_object));
		}

		//debug_log ("VSLIDER: resizing to %f (%f pixels)", new_slider_virtual_size, new_slider_virtual_size * get_ui_object_y_size (slider_object));
	}
	else
	{

		//make slider disapear of area too small to slide
		set_ui_object_drawable (slider_object, FALSE);

		// can't slide as object_to_size is too small

		set_ui_object_virtual_y_size (slider_area, 1.0);

		set_ui_object_virtual_y (slider_area, UI_SLIDER_VIRTUAL_HEIGHT * get_screen_height (video_screen) / get_ui_object_y_size (slider_object));

		//debug_log ("VSLIDER: resizing to %f (%f pixels)", 1.0, get_ui_object_y_size (slider_object));
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void recalculate_slider_origin (ui_object *slider_object)
{

	ui_object
		*parent,
		*slider_area,
		*object_to_slide;

	float
		object_y,
		object_y_size,
		overhang,
		slider_y,
		y_origin,
		slider_y_size,
		total_slider_y_size;

	total_slider_y_size = 0.0;
	
	// get the slider area

	slider_area = get_ui_object_association (slider_object);

	if (!slider_area)
	{

		debug_log ("VSLIDER: can't find slider area");

		return;
	}

	// get the slider size

	slider_y = get_ui_object_y (slider_object);

	slider_y_size = get_ui_object_y_size (slider_object) - (2 * UI_SLIDER_VIRTUAL_HEIGHT * get_screen_height (video_screen));

	// get total "objects to slide" size

	parent = get_ui_object_parent (slider_object);

	object_to_slide = get_ui_object_child (parent);

	while (object_to_slide)
	{

		if (get_ui_object_type (object_to_slide) != UI_TYPE_VSLIDER)
		{
	
			object_y = get_ui_object_y (object_to_slide);
			object_y_size = get_ui_object_y_size (object_to_slide);

			if (get_ui_object_type (object_to_slide) == UI_TYPE_LIST_BOX)
			{

				object_y_size = get_next_list_position (object_to_slide);
			}
	
			if (total_slider_y_size < (object_y - slider_y + object_y_size))
			{
	
				total_slider_y_size = (object_y - slider_y + object_y_size);
			}
		}

		object_to_slide = get_ui_object_next (object_to_slide);
	}

	if (total_slider_y_size > get_ui_object_y_size (slider_object))
	{

		// find amount the object overhang by

		overhang = total_slider_y_size - get_ui_object_y_size (slider_object);

		// object_to_slide origin based on slider_area position

		y_origin = get_ui_object_y (slider_area);
		y_origin -= get_ui_object_y (slider_object);
		y_origin -= UI_SLIDER_VIRTUAL_HEIGHT * get_screen_height (video_screen);
		y_origin /= (slider_y_size - get_ui_object_y_size (slider_area));
		y_origin *= overhang;

		y_origin = max (y_origin, 0.0);

		// set 'object_to_slide' origins

		parent = get_ui_object_parent (slider_object);

		object_to_slide = get_ui_object_child (parent);
	}
	else
	{

		y_origin = 0.0;
	}

	object_to_slide = get_ui_object_child (parent);

	while (object_to_slide)
	{

		if (get_ui_object_type (object_to_slide) != UI_TYPE_VSLIDER)
		{

			set_ui_object_y_origin (object_to_slide, -y_origin);
		}

		object_to_slide = get_ui_object_next (object_to_slide);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ui_object *get_ui_object_vslider (ui_object *obj)
{

	ui_object
		*this_obj;

	this_obj = get_ui_object_child (obj);
	
  	while (this_obj)
	{

		if (get_ui_object_type (this_obj) == UI_TYPE_VSLIDER)
		{

			return this_obj;
		}

		this_obj = get_ui_object_next (this_obj);
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_ui_object_vslider_position (ui_object *obj, float pos)
{

	float
		min,
		max;

	ui_object
		*slider;

	slider = get_ui_object_association (obj);

	min = 0.0;
	max = get_ui_object_y_size (obj);
	
	pos = bound (pos, min + UI_SLIDER_VIRTUAL_HEIGHT, max - UI_SLIDER_VIRTUAL_HEIGHT - get_ui_object_y_size (slider));

	set_ui_object_y (slider, pos);

	recalculate_slider_origin (obj);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_ui_object_vslider_virtual_position (ui_object *obj, float pos)
{

	float
		py_size;

	ui_object
		*slider;

	slider = get_ui_object_association (obj);

	py_size = get_screen_height (video_screen) / get_ui_object_y_size (obj);

	pos = bound (pos, UI_SLIDER_VIRTUAL_HEIGHT * py_size, (1.0 - (UI_SLIDER_VIRTUAL_HEIGHT * py_size)) - get_ui_object_virtual_y_size (slider));

	set_ui_object_virtual_y (slider, pos);

	recalculate_slider_origin (obj);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
