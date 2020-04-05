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

static void internal_reset_time_values (ui_object *obj);

static void internal_recursively_set_object_time (ui_object *obj, int time, int offset);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ui_object_autosize (ui_object *obj)
{
/*
	ui_object
		*child = nullptr;

	area_ui_object
		*area = nullptr;

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
	*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_text_position (float *x, float *y, float x1, float y1, float x2, float y2, const char *text, text_justify_types justify_type)
{

	float
		mid_x,
		mid_y,
		max_x,
		max_y;

	float
		x_position,
		y_position;

	int
		ix_position,
		iy_position;

	mid_x = x1 + ((x2 - x1) / 2.0) - (ui_get_string_length (text) / 2.0);

	mid_y = y1 + ((y2 - y1) / 2.0) - (ui_get_font_height () / 2.0);

	max_x = x1 + (x2 - x1) - ui_get_string_length (text);

	max_y = y1 + (y2 - y1) - ui_get_font_height ();

	x_position = mid_x;

	y_position = mid_y;

	switch (justify_type)
	{

		case TEXT_JUSTIFY_CENTRE:
		{

			break;
		}
		case TEXT_JUSTIFY_LEFT_CENTRE:
		{

			x_position = x1;

			break;
		}
		case TEXT_JUSTIFY_RIGHT_CENTRE:
		{

			x_position = max_x;

			break;
		}
		case TEXT_JUSTIFY_CENTRE_TOP:
		{

			y_position = y1;

			break;
		}
		case TEXT_JUSTIFY_LEFT_TOP:
		{

			x_position = x1;
			y_position = y1;

			break;
		}
		case TEXT_JUSTIFY_RIGHT_TOP:
		{

			x_position = max_x;
			y_position = y1;

			break;
		}
		case TEXT_JUSTIFY_CENTRE_BOTTOM:
		{

			y_position = max_y;

			break;
		}
		case TEXT_JUSTIFY_LEFT_BOTTOM:
		{

			x_position = x1;
			y_position = max_y;

			break;
		}
		case TEXT_JUSTIFY_RIGHT_BOTTOM:
		{

			x_position = max_x;
			y_position = max_y;

			break;
		}
	}

	//
	// Now ensure we're not using 1/2 pixel boundaries :)
	//

	convert_float_to_int ( x_position, &ix_position );
	convert_float_to_int ( y_position, &iy_position );

	*x = ix_position;
	*y = iy_position;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_text_y_position (float *y, float y1, float y2, const char *text, text_justify_types justify_type, int line_count)
{

	float
		mid_y,
		max_y;

	float
		y_position;

	int
		iy_position;

	mid_y = y1 + ((y2 - y1) / 2.0);

	max_y = y1 + (y2 - y1);

	switch (justify_type)
	{

		case TEXT_JUSTIFY_CENTRE_TOP:
		case TEXT_JUSTIFY_LEFT_TOP:
		case TEXT_JUSTIFY_RIGHT_TOP:
		{

			y_position = y1;

			break;
		}
		case TEXT_JUSTIFY_CENTRE_BOTTOM:
		case TEXT_JUSTIFY_LEFT_BOTTOM:
		case TEXT_JUSTIFY_RIGHT_BOTTOM:
		{

			y_position = max_y - (line_count * ui_get_font_height ());

			break;
		}

		default:
		{

			y_position = mid_y - (0.5 * line_count * ui_get_font_height ());

			break;
		}
	}

	//
	// Now ensure we're not using 1/2 pixel boundaries :)
	//

	convert_float_to_int ( y_position, &iy_position );

	*y = iy_position;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_text_x_position (float *x, float x1, float x2, const char *text, text_justify_types justify_type)
{

	float
		mid_x,
		max_x;

	float
		x_position;

	int
		ix_position;

	mid_x = x1 + ((x2 - x1) / 2.0) - (ui_get_string_length (text) / 2.0);

	max_x = x1 + (x2 - x1) - ui_get_string_length (text);

	x_position = mid_x;

	switch (justify_type)
	{

		case TEXT_JUSTIFY_CENTRE:
		{

			break;
		}
		case TEXT_JUSTIFY_LEFT_TOP:
		case TEXT_JUSTIFY_LEFT_CENTRE:
		case TEXT_JUSTIFY_LEFT_BOTTOM:
		{

			x_position = x1;

			break;
		}
		case TEXT_JUSTIFY_RIGHT_TOP:
		case TEXT_JUSTIFY_RIGHT_CENTRE:
		case TEXT_JUSTIFY_RIGHT_BOTTOM:
		{

			x_position = max_x;

			break;
		}
	}

	//
	// Now ensure we're not using 1/2 pixel boundaries :)
	//

	convert_float_to_int ( x_position, &ix_position );

	*x = ix_position;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_ui_object_bounded_t_value (ui_object *obj)
{

	int
		start_time,
		current_time,
		current_length,
		time_length;

	float
		t;

	start_time = get_ui_object_start_time (obj);

	current_time = get_system_time ();

	current_length = current_time - start_time;

	time_length = get_ui_object_time_length (obj);

	if (time_length > 0)
	{

		t = (float) current_length / (float) time_length;
	}
	else
	{

		t = 1.0;
	}

	t = bound (t, 0.0, 1.0);

	return (t);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_time_values (ui_object *obj)
{

	ui_object
		*child = nullptr;

	int
		time_offset;

	time_offset = get_ui_object_offset_time (obj);

	set_ui_object_start_time (obj, get_system_time () + time_offset);

	set_ui_object_t_value (obj, 0.0);

	child = get_ui_object_child (obj);

	if (child)
	{

		internal_reset_time_values (child);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void internal_reset_time_values (ui_object *obj)
{

	ui_object
		*child = nullptr,
		*next = nullptr;

	int
		time_offset;

	time_offset = get_ui_object_offset_time (obj);

	set_ui_object_start_time (obj, get_system_time () + time_offset);

	set_ui_object_t_value (obj, 0.0);

	child = get_ui_object_child (obj);

	if (child)
	{

		internal_reset_time_values (child);
	}

	next = get_ui_object_next (obj);

	if (next)
	{

		internal_reset_time_values (next);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void recursively_set_object_time (ui_object *obj, int time, int offset)
{

	ui_object
		*child = nullptr;

	// set variables

	set_ui_object_time_length (obj, time);

	set_ui_object_offset_time (obj, offset);

	// do recursive stuff

	child = get_ui_object_child (obj);

	if (child)
	{

		internal_recursively_set_object_time (obj, time, offset);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void internal_recursively_set_object_time (ui_object *obj, int time, int offset)
{

	ui_object
		*child = nullptr,
		*next = nullptr;

	// set variables

	set_ui_object_time_length (obj, time);

	set_ui_object_offset_time (obj, offset);

	// do recursive stuff

	child = get_ui_object_child (obj);

	if (child)
	{

		internal_recursively_set_object_time (child, time, offset);
	}

	next = get_ui_object_next (obj);

	if (next)
	{

		internal_recursively_set_object_time (next, time, offset);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
