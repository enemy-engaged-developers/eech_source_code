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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static ui_object
	*screen_stack_head,
	*screen_stack_tail;
	
ui_object
	*current_screen;

static int
	screen_stack_size = 0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void push_ui_screen (ui_object *this_screen)
{

	void
		((*function) (ui_object *obj, void *arg));

	ui_object
		*stack_search;

	screen_ui_object
		*screen = NULL;

	// check if already on stack

	stack_search = screen_stack_head;

	current_screen = this_screen;
	
	while (stack_search)
	{

		// screen found on stack

		if (stack_search == this_screen)
		{

			// pop all down to this screen

			stack_search = screen_stack_head;

			while (stack_search != this_screen)
			{

				pop_ui_screen (SCREEN_POP_STACK_MAINTANANCE);

				stack_search = stack_search->stack_next;
			}
	
			function = get_ui_object_function (this_screen);
		
			if (function)
			{
		
				function (this_screen, &screen->screen_id);
			}

			return;
		}

		stack_search = stack_search->stack_next;
	}

	// add new screen

	this_screen->stack_next = screen_stack_head;

	// first screen on stack

	if (!screen_stack_head)
	{

		screen_stack_head = this_screen;

		screen_stack_tail = this_screen;

		this_screen->stack_prev = NULL;

		this_screen->stack_next = NULL;

		screen = (screen_ui_object *) this_screen->data;

		screen_stack_head->stack_id = screen_stack_size ++;

		function = get_ui_object_function (this_screen);

		if (function)
		{

			if ((get_ui_object_notify_on (this_screen) == NOTIFY_TYPE_DISPLAYED) || (get_ui_object_notify_on (this_screen) == NOTIFY_TYPE_BUTTON_EITHER))
			{

				function (this_screen, &screen->screen_id);
			}
		}
	}
	else
	{
	
		// add screen to head of stack
	
		screen = (screen_ui_object *) screen_stack_head->data;
	
		set_ui_object_drawable (screen_stack_head, FALSE);

		// call the previous screen's function if it has one

		function = get_ui_object_function (screen_stack_head);

		if (function)
		{

			if ((get_ui_object_notify_on (screen_stack_head) == NOTIFY_TYPE_REMOVED) || (get_ui_object_notify_on (screen_stack_head) == NOTIFY_TYPE_BUTTON_EITHER))
			{

				function (screen_stack_head, &screen->screen_id);
			}
		}

		//
	
		screen_stack_head->stack_prev = this_screen;
	
		screen_stack_head = this_screen;
	
		screen = (screen_ui_object *) screen_stack_head->data;
	
		screen_stack_head->stack_id = screen_stack_size ++;
	
		set_ui_object_drawable (screen_stack_head, TRUE);
	
		this_screen->stack_prev = NULL;
	
		function = get_ui_object_function (this_screen);
	
		if (function)
		{
	
			if ((get_ui_object_notify_on (this_screen) == NOTIFY_TYPE_DISPLAYED) || (get_ui_object_notify_on (this_screen) == NOTIFY_TYPE_BUTTON_EITHER))
			{

				function (this_screen, &screen->screen_id);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pop_ui_screen (screen_pop_types type)
{

	ui_object
		*popped_screen;

	screen_ui_object
		*screen;

	void
		((*function) (ui_object *obj, void *arg));

	// store screen to pop and unlink it and destroy it.

	if (screen_stack_head)
	{
	
		popped_screen = screen_stack_head;
	
		screen_stack_head = screen_stack_head->stack_next;

		// call popped screen function

		set_ui_object_drawable (popped_screen, FALSE);

		screen = (screen_ui_object *) popped_screen->data;

		function = get_ui_object_function (popped_screen);

		if (function)
		{
	
			if ((get_ui_object_notify_on (popped_screen) == NOTIFY_TYPE_REMOVED) || (get_ui_object_notify_on (popped_screen) == NOTIFY_TYPE_BUTTON_EITHER))
			{

				if (type == SCREEN_POP_ACTUAL)
				{
	
					function (popped_screen, &screen->screen_id);
				}
			}
		}

		// setup new screen
	
		if (screen_stack_head)
		{

			screen_stack_head->stack_prev = NULL;
	
			set_ui_object_drawable (screen_stack_head, TRUE);

			current_screen = screen_stack_head;

			function = get_ui_object_function (current_screen);

			if (function)
			{

				screen = (screen_ui_object *) current_screen->data;

				// call new screens function
	
				if ((get_ui_object_notify_on (current_screen) == NOTIFY_TYPE_DISPLAYED) || (get_ui_object_notify_on (current_screen) == NOTIFY_TYPE_BUTTON_EITHER))
				{

					if (type == SCREEN_POP_ACTUAL)
					{
		
						function (current_screen, &screen->screen_id);
					}
				}
			}
		}
		else
		{

			// empty stack

			screen_stack_tail = NULL;
		}

		screen_stack_size --;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ui_object *get_ui_screen_stack_head (void)
{

	return screen_stack_head;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
