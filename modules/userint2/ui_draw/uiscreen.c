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

#include "system.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct UI_SCREEN_STACK
{

	int
		screen_id;

	void
		*screen; // should be entity_screen..

	struct UI_SCREEN_STACK
		*prev,
		*next;

	int
		displayable;
};

typedef struct UI_SCREEN_STACK ui_screen_stack;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static ui_screen_stack
	*screen_stack_head,
	*screen_stack_tail;

static int
	screen_id = 0;
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ui_pop_screen (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ui_push_screen (void *this_screen) // should be entity_screen..
{

	ui_screen_stack
		*stack_search,
		*new_stack_item;

	// check if already on stack

	stack_search = screen_stack_head;

	while (stack_search)
	{

		// screen found on stack

		if (stack_search->screen == this_screen)
		{

			// pop all down to this screen

			stack_search = screen_stack_head;

			while (stack_search->screen != this_screen)
			{

				ui_pop_screen ();

				stack_search = stack_search->prev;
			}

			return;
		}

		stack_search = stack_search->prev;
	}

	// malloc new screen

	new_stack_item = (ui_screen_stack *) safe_malloc (sizeof (ui_screen_stack));

	new_stack_item->screen = this_screen;

	new_stack_item->screen_id = screen_id ++;

	new_stack_item->displayable = TRUE;

	// first screen on stack

	if (!screen_stack_head)
	{

		screen_stack_head = new_stack_item;

		screen_stack_tail = new_stack_item;

		new_stack_item->prev = NULL;

		new_stack_item->next = NULL;

		return;
	}

	// add screen to head of stack

	screen_stack_head->displayable = FALSE;

	new_stack_item->prev = screen_stack_head;

	screen_stack_head->next = new_stack_item;

	screen_stack_head = new_stack_item;

	screen_stack_head->displayable = TRUE;

	new_stack_item->next = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ui_pop_screen (void)
{

	ui_screen_stack
		*popped_screen;

	// store screen to pop and unlink it and destroy it.

	if (screen_stack_head)
	{
	
		popped_screen = screen_stack_head;
	
		screen_stack_head = screen_stack_head->prev;
	
		if (screen_stack_head)
		{

			screen_stack_head->next = NULL;
	
			screen_stack_head->displayable = TRUE;
		}
		else
		{

			// empty stack

			screen_stack_tail = NULL;
		}
	
		free (popped_screen);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ui_list_screen_stack (void)
{

	ui_screen_stack
		*this_screen;

	int
		counter = 0,
		y = 50;

	char
		buffer [20];

	this_screen = screen_stack_head;

	while (this_screen)
	{

		sprintf (buffer, "Screen %d", this_screen->screen_id);

		ui_display_text (buffer, 10, y);

		y += ui_get_font_height ();

		counter ++;

		this_screen = this_screen->prev;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
