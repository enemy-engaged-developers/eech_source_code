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

#include "system.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 1

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

event_stack
	*event_stack_head,
	*event_stack_tail;

static int
	event_id;
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MODULE

static void display_event_stack (void);

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
void initialise_event_stack (void)
{

	event_id = 0;

	event_stack_head = NULL;

	event_stack_tail = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
void deinitialise_event_stack (void)
{

	event_stack
		*this_event;

	this_event = event_stack_head;

	while (this_event)
	{

		this_event = event_stack_head->next;

		safe_free (event_stack_head);

		event_stack_head = this_event;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// push events, clearing event table first.

void push_event (void ((*this_function) (void)), char *name)
{

	event_stack
		*stack_search,
		*new_stack_item;

	// check if already on stack

	#if DEBUG_MODULE

	debug_log ("EV_STACK: -------------------------------------------------------------------------------");
	debug_log ("EV_STACK: push event");

	if (name)
	{

		debug_log ("EV_STACK: creating new event table for %s function %d", name, this_function);
	}
	else
	{

		debug_log ("EV_STACK: creating new event table for function %d", this_function);
	}

	#endif

	stack_search = event_stack_head;

	while (stack_search)
	{

		// event found on stack

		if (stack_search->function == this_function)
		{

			// pop all down to this function

			#if DEBUG_MODULE

			if (stack_search->name)
			{

				debug_log ("EV_STACK:     found event table for %s %d, id %d, function %d, overlay %d", stack_search->name, stack_search, stack_search->event_id, stack_search->function, stack_search->overlay);
			}
			else
			{

				debug_log ("EV_STACK:     found event table for %d, id %d, function %d, overlay %d", stack_search, stack_search->event_id, stack_search->function, stack_search->overlay);
			}

			#endif

			stack_search = event_stack_head;

			while (stack_search->function != this_function)
			{

				if (!stack_search->overlay)
				{

					#if DEBUG_MODULE

					debug_log ("EV_STACK:       popping down to it");

					#endif

					pop_event (NULL);
				}

				stack_search = stack_search->prev;
			}

			#if DEBUG_MODULE

			debug_log ("EV_STACK: -------------------------------------------------------------------------------");

			#endif

			return;
		}

		stack_search = stack_search->prev;
	}

	#if DEBUG_MODULE

	debug_log ("EV_STACK: -------------------------------------------------------------------------------");

	#endif

	// malloc new event

	new_stack_item = (event_stack *) safe_malloc (sizeof (event_stack));

	new_stack_item->overlay = FALSE;

	new_stack_item->function = this_function;

	new_stack_item->event_id = event_id ++;

	new_stack_item->name = NULL;

	if (name)
	{
	
		new_stack_item->name = (char *) safe_malloc (sizeof (char) * (strlen (name) + 1));
	
		sprintf (new_stack_item->name, "%s", name);
	}

	// overlay with this event table

	clear_events ();

	this_function ();

	// first event on stack

	if (!event_stack_head)
	{

		event_stack_head = new_stack_item;

		event_stack_tail = new_stack_item;

		new_stack_item->prev = NULL;

		new_stack_item->next = NULL;

		return;
	}

	// add event to head of stack

	new_stack_item->prev = event_stack_head;

	event_stack_head->next = new_stack_item;

	event_stack_head = new_stack_item;

	new_stack_item->next = NULL;

	#if DEBUG_MODULE

	display_event_stack ();

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// push events, without clearing event table first. Previous events will 'show through' the current event layer

void push_event_overlay (void ((*this_function) (void)), char *name)
{

	event_stack
		*stack_search,
		*new_stack_item;

	// check if already on stack

	stack_search = event_stack_head;

	#if DEBUG_MODULE

	debug_log ("EV_STACK: -------------------------------------------------------------------------------");
	debug_log ("EV_STACK: push event overlay");

	if (stack_search->name)
	{

		debug_log ("EV_STACK: creating new event table for %s function %d", name, this_function);
	}
	else
	{

		debug_log ("EV_STACK: creating new event table for function %d", this_function);
	}

	#endif

	while (stack_search)
	{

		// event found on stack

		if (stack_search->function == this_function)
		{

			#if DEBUG_MODULE

			debug_log ("EV_STACK:     found event table for %s %d, id %d, function %d, overlay %d", stack_search->name, stack_search, stack_search->event_id, stack_search->function, stack_search->overlay);

			#endif

			// pop all down to this function

			stack_search = event_stack_head;

			while (stack_search->function != this_function)
			{
			    if (!stack_search->overlay)
			    {

				#if DEBUG_MODULE

				debug_log ("EV_STACK:       popping down to it");

				#endif

				stack_search = stack_search->prev;	// needed because stack_search can be freed in pop_event()

				pop_event (NULL);

			    } else {

				stack_search = stack_search->prev;

			    }
			}

			#if DEBUG_MODULE

			debug_log ("EV_STACK: -------------------------------------------------------------------------------");

			#endif

			return;
		}

		stack_search = stack_search->prev;
	}

	#if DEBUG_MODULE

	debug_log ("EV_STACK: -------------------------------------------------------------------------------");

	#endif

	// malloc new event

	new_stack_item = (event_stack *) safe_malloc (sizeof (event_stack));

	new_stack_item->overlay = TRUE;

	new_stack_item->function = this_function;

	new_stack_item->event_id = event_id ++;

	new_stack_item->name = NULL;

	if (name)
	{
	
		new_stack_item->name = (char *) safe_malloc (sizeof (char) * (strlen (name) + 1));
	
		sprintf (new_stack_item->name, "%s", name);
	}

	// overlay with this event table

	this_function ();

	// first event on stack

	if (!event_stack_head)
	{

		event_stack_head = new_stack_item;

		event_stack_tail = new_stack_item;

		new_stack_item->prev = NULL;

		new_stack_item->next = NULL;

		return;
	}

	// add event to head of stack

	new_stack_item->prev = event_stack_head;

	event_stack_head->next = new_stack_item;

	event_stack_head = new_stack_item;

	new_stack_item->next = NULL;

	#if DEBUG_MODULE

	display_event_stack ();

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void push_event_stop (void)
{

	event_stack
		*new_stack_item;

	// malloc new event

	new_stack_item = (event_stack *) safe_malloc (sizeof (event_stack));

	#if DEBUG_MODULE

	debug_log ("EV_STACK: -------------------------------------------------------------------------------");

	debug_log ("EV_STACK: creating new event stop %d", new_stack_item);

	debug_log ("EV_STACK: -------------------------------------------------------------------------------");

	#endif

	new_stack_item->function = NULL;

	new_stack_item->event_id = event_id ++;

	new_stack_item->name = NULL;

	// overlay with this event table

	clear_events ();

	// first event on stack

	if (!event_stack_head)
	{

		event_stack_head = new_stack_item;

		event_stack_tail = new_stack_item;

		new_stack_item->prev = NULL;

		new_stack_item->next = NULL;

		return;
	}

	// add event to head of stack

	new_stack_item->prev = event_stack_head;

	event_stack_head->next = new_stack_item;

	event_stack_head = new_stack_item;

	new_stack_item->next = NULL;

	#if DEBUG_MODULE

	display_event_stack ();

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pop_event (void ((*function) (void)))
{

	event_stack
		*event,
		*popped_event;

	// store event to pop and unlink it and destroy it.

	#if DEBUG_MODULE

	debug_log ("EV_STACK: -------------------------------------------------------------------------------");
	debug_log ("EV_STACK: pop event");

	#endif

	if (event_stack_head)
	{
	
		popped_event = event_stack_head;

		//
		// Check if function is the correct one...
		//

		if (function)
		{

			if (function != popped_event->function)
			{

				#if DEBUG_MODULE

				if (popped_event->name)
				{

					debug_log ("EV_STACK: Not popping. Unmaintained event table %s id %d function %d is top of stack", popped_event->name, popped_event->event_id, popped_event->function);
				}
				else
				{

					debug_log ("EV_STACK: Not popping. Unmaintained event table id %d function %d is top of stack", popped_event->event_id, popped_event->function);
				}

				debug_log ("EV_STACK: -------------------------------------------------------------------------------");

				#endif

				return;
			}
		}

		//
		//
		//
	
		event_stack_head = event_stack_head->prev;
	
		if (event_stack_head)
		{

			event_stack_head->next = NULL;
	
  			// overlay with this event table

			clear_events ();

			// find the next non-overlay event

			event = event_stack_head;

			while ((event) && (event->overlay))
			{

				event = event->prev;
			}

			ASSERT (event);

			// execute all events from non-overlay up (so as to overlay properly)

			while (event)
			{

				if (event->function)
				{

					event->function ();
				}

				event = event->next;
			}
		}
		else
		{

			// empty stack

			event_stack_tail = NULL;
		}

		#if DEBUG_MODULE

		debug_log ("EV_STACK: popping event table %s %d, function %d, overlay %d", popped_event->name, popped_event, popped_event->function, popped_event->overlay);

		debug_log ("EV_STACK: -------------------------------------------------------------------------------");

		display_event_stack ();

		#endif

		if (popped_event->name)
		{

			safe_free (popped_event->name);
		}
	
		safe_free (popped_event);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pop_to_event_stop (void)
{

	event_stack
		*popped_event;

	// pop down to 'stop' and then one more

	if (event_stack_head)
	{

		#if DEBUG_MODULE

		debug_log ("EV_STACK: -------------------------------------------------------------------------------");

		debug_log ("EV_STACK: popping to event stop ");

		#endif
	
  		while ((event_stack_head) && (event_stack_head->function))
		{
	
			popped_event = event_stack_head;
	
			event_stack_head = event_stack_head->prev;

			#if DEBUG_MODULE

			if (popped_event->name)
			{

				debug_log ("EV_STACK:     popping %s %d, function %d, overlay %d, to event stop ", popped_event->name, popped_event, popped_event->function, popped_event->overlay);
			}
			else
			{

				debug_log ("EV_STACK:     popping %d, function %d, overlay %d, to event stop ", popped_event, popped_event->function, popped_event->overlay);
			}

			#endif

			if (popped_event->name)
			{
	
				safe_free (popped_event->name);
			}
		
			safe_free (popped_event);
		}

		pop_event (NULL);
	}

	#if DEBUG_MODULE

	debug_log ("EV_STACK: -------------------------------------------------------------------------------");

	display_event_stack ();

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MODULE

void display_event_stack (void)
{

	event_stack
		*ev;

	// pop down to 'stop' and then one more

	ev = event_stack_head;

	if (ev)
	{

		debug_log ("EV_STACK: -------------------------------------------------------------------------------");

		debug_log ("EV_STACK: current event stack ");
	
  		while (ev)
		{

			if (ev->name)
			{
	
				debug_log ("EV_STACK:     %s %d, function %d, overlay %d", ev->name, ev, ev->function, ev->overlay);
			}
			else
			{
	
				debug_log ("EV_STACK:     %d, function %d, overlay %d", ev, ev->function, ev->overlay);
			}

			ev = ev->prev;
		}
	}

	debug_log ("EV_STACK: -------------------------------------------------------------------------------");
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
