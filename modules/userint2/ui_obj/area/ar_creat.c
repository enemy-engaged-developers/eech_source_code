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

static void create_area_ui_object (ui_object *obj, ui_object_types type, va_list pargs)
{

	area_ui_object
		*new_object;

	increase_ui_object_counter ();

	////////////////////////////////////////
	//
	// MALLOC ENTITY DATA
	//
	////////////////////////////////////////

	obj->type = type;

	new_object = (area_ui_object*) safe_malloc (sizeof (area_ui_object));

	obj->data = new_object;

	////////////////////////////////////////
	//
	// INITIALISE ALL ENTITY DATA TO 'WORKING' DEFAULT VALUES
	//
	// DO NOT USE ACCESS FUNCTIONS
	//
	// DO NOT USE RANDOM VALUES
	//
	////////////////////////////////////////

	memset (new_object, 0, sizeof (area_ui_object));

	//new_object->x = 0.0;
	//new_object->y = 0.0;
	//new_object->x_size = 0.0;
	//new_object->y_size = 0.0;
	new_object->x_origin = 0.0;
	new_object->y_origin = 0.0;
	new_object->drawable = 1;
	new_object->item_number = -1;
	new_object->item_number2 = -1;				// DL - Wasn't initialised (should it be?)
	new_object->redraw = 1;
	new_object->text_justify = TEXT_JUSTIFY_CENTRE;
	new_object->state = UI_OBJECT_STATE_OFF;
	new_object->notify_on = NOTIFY_TYPE_BUTTON_UP;
	new_object->highlighted_notify_on = NOTIFY_TYPE_BUTTON_EITHER;
	new_object->moveable = 0;
	new_object->resizeable = 0;
	new_object->parent = NULL;
	new_object->child = NULL;
	new_object->next = NULL;
	new_object->prev = NULL;
	new_object->colour_start.r = 255;
	new_object->colour_start.g = 255;
	new_object->colour_start.b = 255;
	new_object->colour_start.a = 255;
	new_object->colour_end.r = 255;
	new_object->colour_end.g = 255;
	new_object->colour_end.b = 255;
	new_object->colour_end.a = 255;
	new_object->font_type = UI_FONT_ARIAL_10;
	new_object->font_colour_end = default_unselected_text_colour;
	new_object->font_colour_start = default_unselected_text_colour;
	new_object->highlighted_font_type = -1;
	new_object->highlighted_font_colour_end = default_selected_text_colour;
	new_object->highlighted_font_colour_start = default_selected_text_colour;
	new_object->selected_font_type = -1;
	new_object->selected_font_colour_end = default_selected_text_colour;
	new_object->selected_font_colour_start = default_selected_text_colour;
	new_object->user_flag1 = 0;
	new_object->user_flag2 = 0;
	new_object->user_flag3 = 0;
	new_object->user_flag4 = 0;
	new_object->user_ptr = NULL;

	new_object->time_length = 1.0;

	////////////////////////////////////////
	//
	// OVERWRITE DEFAULTS WITH GIVEN ATTRIBUTES
	//
	////////////////////////////////////////

	set_ui_object_attributes (obj, pargs);

	////////////////////////////////////////
	//
	// Check the font default values & override them if not set
	//
	////////////////////////////////////////

	if ( new_object->font_type == -1 )
	{

		new_object->font_type = get_ui_font_type ();
	}

	if ( new_object->highlighted_font_type == -1 )
	{

		new_object->highlighted_font_type = new_object->font_type;
	}

	if ( new_object->selected_font_type == -1 )
	{

		new_object->selected_font_type = new_object->font_type;
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

static void destroy_area_ui_object (ui_object *obj)
{

	ui_object
		*parent,
		*next,
		*prev,
		*succ,
		*pred,
		*stack_next,
		*stack_prev;

	area_ui_object
		*parent_area,
		*area;

	////////////////////////////////////////
	//
	// REMOVE FROM SYSTEM
	//
	////////////////////////////////////////

	////////////////////////////////////////
	//
	// FREE UI_OBJECT DATA
	//
	////////////////////////////////////////

	area = (area_ui_object*) obj->data;

	// sort out parent

	parent = area->parent;

	if (parent)
	{

		parent_area = (area_ui_object *) parent->data;

		if (parent_area->child == obj)
		{

			if (area->next)
			{

				parent_area->child = area->next;
			}
			else
			{

				parent_area->child = NULL;
			}
		}
	}

	// do entity header

	stack_next = obj->stack_next;

	stack_prev = obj->stack_prev;

	succ = obj->succ;

	pred = obj->pred;

	if (succ)
	{

		if (pred)
		{

			succ->pred = pred;

			pred->succ = succ;
		}
		else
		{

			succ->pred = NULL;
		}
	}
	else
	{

		if (pred)
		{

			pred->succ = NULL;
		}
	}

	if (stack_next)
	{

		if (stack_prev)
		{

			stack_next->stack_prev = stack_prev;

			stack_prev->stack_next = stack_next;
		}
		else
		{

			stack_next->stack_prev = NULL;
		}
	}
	else
	{

		if (stack_prev)
		{

			pred->stack_next = NULL;
		}
	}

	// do area pointers

	next = area->next;
	prev = area->prev;

	if (next)
	{

		if (prev)
		{

			set_ui_object_prev (next, prev);

			set_ui_object_next (prev, next);
		}
		else
		{

			set_ui_object_prev (next, NULL);
		}
	}
	else
	{

		if (prev)
		{

			set_ui_object_next (prev, NULL);
		}
	}

	if (area->child)
	{

		destroy_ui_object (area->child);
	}

	// free text

	if (area->text)
	{

		safe_free (area->text);
	}

	if (area->tool_tips)
	{

		safe_free (area->tool_tips);
	}

	// free memory graphic

	if (area->texture_graphic)
		destroy_texture_graphic (area->texture_graphic);
	if (area->selected_texture_graphic)
		destroy_texture_graphic (area->selected_texture_graphic);
	if (area->highlighted_texture_graphic)
		destroy_texture_graphic (area->highlighted_texture_graphic);

	// free ui_object

	safe_free (obj->data);

	decrease_ui_object_counter ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_area_ui_object_create_functions (ui_object_types type)
{

	fn_create_ui_object [type] 	= create_area_ui_object;

	fn_destroy_ui_object [type] 	= destroy_area_ui_object;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
