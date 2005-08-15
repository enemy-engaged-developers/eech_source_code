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

#include "userint2.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define LIST_DEBUG 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ui_object_list_item_function (ui_object *obj, void *arg)
{

	int
		list_position;

	ui_object
		*parent,
		*next_parent,
		*current_list_item;

	void
		((*pfunction) (ui_object *obj, void *arg));

	parent = get_ui_object_parent (obj);

	next_parent = parent;

	// set the next non-clear parent to redraw

	while ((next_parent) && (get_ui_object_clear (next_parent)))
	{

		next_parent = get_ui_object_parent (next_parent);

		if (next_parent)
		{

			set_ui_object_redraw (next_parent, TRUE);
		}
	}

	current_list_item = get_ui_object_child (parent);

	// find out what its list position is

	list_position = 0;

  	while (current_list_item)
	{
		
		list_position ++;

		if (obj == current_list_item)
		{

			break;
		}

		current_list_item = get_ui_object_next (current_list_item);
	}

	#if LIST_DEBUG

	debug_log ("UI LIST: item %d", list_position);

	#endif
		
	// notify parents function

	pfunction = get_ui_object_function (parent);

	if (pfunction)
	{

		pfunction (obj, (void *) list_position);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ui_object_list_item_right_function (ui_object *obj, void *arg)
{

	int
		list_position;

	ui_object
		*parent,
		*next_parent,
		*current_list_item;

	void
		((*pfunction) (ui_object *obj, void *arg));

	parent = get_ui_object_parent (obj);

	next_parent = parent;

	// set the next non-clear parent to redraw

	while ((next_parent) && (get_ui_object_clear (next_parent)))
	{

		next_parent = get_ui_object_parent (next_parent);

		if (next_parent)
		{

			set_ui_object_redraw (next_parent, TRUE);
		}
	}

	set_ui_object_redraw (parent, TRUE);

	current_list_item = get_ui_object_child (parent);

	// find out what its list position is

	list_position = 0;

  	while (current_list_item)
	{
		
		list_position ++;

		if (obj == current_list_item)
		{

			break;
		}

		current_list_item = get_ui_object_next (current_list_item);
	}
		
	// notify parents function

	pfunction = get_ui_object_right_function (parent);

	if (pfunction)
	{

		pfunction (obj, (void *) list_position);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_next_list_position (ui_object *list_object)
{

	float
		y,
		y_max;

	ui_object
		*y_max_object,
		*current_list_item;

	list_ui_object
		*list;

	list = list_object->data;

	current_list_item = get_ui_object_child (list_object);

	y_max_object = current_list_item;

	y_max = 0;

	if (current_list_item)
	{
	
		while (current_list_item)
		{

			if (get_ui_object_y (current_list_item) > y_max)
			{

				y_max_object = current_list_item;

				y_max = get_ui_object_y (current_list_item);
			}
	
			current_list_item = get_ui_object_next (current_list_item);
		}

		y = (get_ui_object_y (y_max_object) + get_ui_object_y_size (y_max_object) - get_ui_object_y (list_object) - 1 + list->y_space);

		return y;
	}

	//return LIST_ITEM_SPACING * 2;
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_next_list_virtual_position (ui_object *list_object)
{

	float
		y,
		y_max;

	ui_object
		*y_max_object,
		*current_list_item;

	list_ui_object
		*list;

	list = list_object->data;

	current_list_item = get_ui_object_child (list_object);

	y_max_object = current_list_item;

	y_max = 0;

	if (current_list_item)
	{
	
		while (current_list_item)
		{

			if (get_ui_object_y (current_list_item) > y_max)
			{

				y_max_object = current_list_item;

				y_max = get_ui_object_y (current_list_item);
			}
	
			current_list_item = get_ui_object_next (current_list_item);
		}

		y = get_ui_object_y (y_max_object);
		y += get_ui_object_y_size (y_max_object);
		y -= get_ui_object_y (list_object);

		y /= get_ui_object_y_size (list_object);
		y += list->y_space;

		return y;
	}

	//return LIST_ITEM_SPACING * 2;
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ui_object_destroy_list_items (ui_object *list)
{

	ui_object
		*destroy_item,
		*current_list_item;

	if (!list)
	{

		return;
	}

	current_list_item = get_ui_object_child (list);

	while (current_list_item)
	{

		destroy_item = current_list_item;

		current_list_item = get_ui_object_next (current_list_item);

		if (get_ui_object_type (destroy_item) != UI_TYPE_VSLIDER)
		{

			destroy_ui_object (destroy_item);
		}
	}

	set_ui_object_child (list, NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ui_object_destroy_list_item (ui_object *list, ui_object *item)
{

	ui_object
		*current_list_item;

	if ((!list) || (!item))
	{

		return FALSE;
	}

	current_list_item = get_ui_object_child (list);

	while (current_list_item)
	{

		if ((current_list_item == item) && (get_ui_object_type (current_list_item) != UI_TYPE_VSLIDER))
		{

			destroy_ui_object (current_list_item);

			return TRUE;
		}

		current_list_item = get_ui_object_next (current_list_item);
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ui_object *add_to_pop_up_list (const char *text, ui_object *obj, ui_object *next_item, int list_id, int font_type, rgb_colour font_colour)
{

	notify_types
		notify_on,
		highlighted_notify_on;

	ui_object
		*text_obj;

	int
		highlighted_font_type;

	float
		x_pos,
		list_x_size,
		list_y_size,
		new_position;

	rgb_colour
		highlighted_font_colour;

	//
	ASSERT (obj);
	//
/*
	if (!obj)
	{

		return NULL;
	}

*/
	//
	//
	//

	list_x_size = 1.0; //get_ui_object_x_size (obj) - 5;

	list_y_size = ui_get_font_height () / get_ui_object_y_size (obj);

	new_position = get_next_list_virtual_position (obj);

	//
	// If invalid font type specified, use the list box font type
	//
	
	if ((font_type < 0) || (font_type >= NUM_FONT_TYPES))
	{

		font_type = get_ui_object_font_type (obj);
	}

	highlighted_font_type = get_ui_object_highlighted_font_type (obj);

	//
	// If invalid font colour specified, use the list box font colour
	//

	notify_on = get_ui_object_notify_on (obj);
	highlighted_notify_on = get_ui_object_highlighted_notify_on (obj);

	highlighted_font_colour = get_ui_object_highlighted_font_colour (obj);

	x_pos = 5.0 / get_ui_object_x_size (obj);

	text_obj = create_ui_object
				(
					UI_TYPE_TEXT,
					UI_ATTR_NEXT (next_item),
					UI_ATTR_PARENT (obj),
					UI_ATTR_LIST_ITEM,
					UI_ATTR_VIRTUAL_SIZE (list_x_size, list_y_size),
					UI_ATTR_VIRTUAL_POSITION (x_pos, new_position),
					UI_ATTR_FONT_TYPE (font_type),
					UI_ATTR_FONT_COLOUR (font_colour.r, font_colour.g, font_colour.b, font_colour.a),
					UI_ATTR_HIGHLIGHTED_FONT_TYPE (highlighted_font_type),
					UI_ATTR_HIGHLIGHTED_FONT_COLOUR (highlighted_font_colour.r, highlighted_font_colour.g, highlighted_font_colour.b, highlighted_font_colour.a),
					UI_ATTR_TEXT (text),
					UI_ATTR_ITEM_NUMBER (list_id),
					UI_ATTR_ITEM_NUMBER2 (UI_LIST_NO_SELECTION),
					UI_ATTR_FUNCTION (ui_object_list_item_function),
					UI_ATTR_RIGHT_FUNCTION (ui_object_list_item_right_function),
					UI_ATTR_NOTIFY_ON (notify_on),
					UI_ATTR_HIGHLIGHTED_NOTIFY_ON (highlighted_notify_on),
					UI_ATTR_END
				);

	//
	// Set list box to redraw, and parents if its clear.
	//

	set_ui_object_redraw (obj, TRUE);

	while ((obj) && (get_ui_object_clear (obj)))
	{

		obj = get_ui_object_parent (obj);

		if (obj)
		{

			set_ui_object_redraw (obj, TRUE);
		}
	}

	return text_obj;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ui_object *add_to_pop_up_list_with_word_wrap (const char *text, ui_object *obj, ui_object *next_item, int list_id, int font_type, rgb_colour font_colour)
{

	font_types
		old_font,
		font;

	ui_object
		*item = NULL;

	char
		temp_text [256],
		word [128],
		*word_ptr;
	const char
		*text_ptr;

	int
		new_line_flag,
		max_string_length;

	old_font = get_ui_font_type ();

	font = get_ui_object_font_type (obj);

	set_ui_font_type (font);

	memset (temp_text, 0, sizeof (temp_text));
	memset (word, 0, sizeof (word));

	max_string_length = get_ui_object_x_size (obj);

	text_ptr = text;

	while ((*text_ptr != '\0'))
	{

		new_line_flag = FALSE;

		// get next word

		word_ptr = word;

		while (*text_ptr != '\0')
		{

			*word_ptr = *text_ptr;

			text_ptr ++;

			if (*word_ptr == ' ')
			{

				break;
			}

			word_ptr ++;

			if (*text_ptr == '\n')
			{

				text_ptr ++;

				new_line_flag = TRUE;

				break;
			}
		}

		// check word isn't longer than allowed space (causes an error if so...)
		debug_assert (ui_get_string_length (word) < max_string_length);

		// check that current string + word fits on line
		if ((ui_get_string_length (temp_text) + ui_get_string_length (word)) > max_string_length)
		{

			// if not display string
			add_to_pop_up_list (temp_text, obj, NULL, 0, -1, font_colour);

			// clear string
			memset (temp_text, 0, sizeof (temp_text));
		}

		// add word to string
		strcat (temp_text, word);

		memset (word, 0, sizeof (word));

		if (new_line_flag)
		{

			// if not display string
			add_to_pop_up_list (temp_text, obj, NULL, 0, -1, font_colour);

			// clear string
			memset (temp_text, 0, sizeof (temp_text));
		}
	}

	if (strlen (temp_text) > 0)
	{

		item = add_to_pop_up_list (temp_text, obj, NULL, 0, -1, font_colour);
	}

	set_ui_font_type (old_font);

	return item;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void resize_pop_up_list (ui_object *obj)
{
	float
		y;

	ui_object
		*parent;

	ASSERT (obj);

	ASSERT (obj->type == UI_TYPE_LIST_BOX);

	parent = get_ui_object_parent (obj);

	ASSERT (parent);

	ASSERT (parent->type == UI_TYPE_AREA);
	
	//
	// re-size the list objects when items are added
	//

	y = get_next_list_position (obj) / get_ui_object_y_size (parent);

	set_ui_object_virtual_y_size (obj, y);

	set_ui_object_virtual_y_size (obj, 1.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ui_object_unselect_list (ui_object *list)
{

	area_ui_object
		*area;

	ui_object
		*item;

	item = get_ui_object_child (list);

	while (item)
	{

		area = item->data;

		area->state = UI_OBJECT_STATE_OFF;

		item = get_ui_object_next (item);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
