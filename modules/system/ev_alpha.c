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

#include "system.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void
	((*alpha_entry_function) (int key)),
	((*end_alpha_entry_function) (int key)),
	((*abort_alpha_entry_function) (int key));

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void alpha_entry_lowercase (event *event);

static void alpha_entry_uppercase (event *event);

static void end_alpha_entry (event *event);

static void abort_alpha_entry (event *event);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_alpha_events (void)
{

	int
		loop;

	if (!alpha_entry_function)
	{

		debug_fatal ("ERROR: Alpha event function not setup");
	}

	//
	// Many special keys need to be uppercase so set all keys first to upper
	//

	for (loop = DIK_1; loop <= DIK_APPS; loop ++)
	{
			
		set_event (loop, MODIFIER_NONE, KEY_STATE_DOWN, alpha_entry_uppercase);

		if ((loop != DIK_LSHIFT) && (loop != DIK_RSHIFT))
		{
	
			set_event (loop, MODIFIER_LEFT_SHIFT, KEY_STATE_DOWN, alpha_entry_uppercase);
			set_event (loop, MODIFIER_RIGHT_SHIFT, KEY_STATE_DOWN, alpha_entry_uppercase);
		}
	}

	//
	// lowercase alpha keys
	// 	

	for (loop = DIK_Q; loop <= DIK_P; loop ++)
	{
			
		set_event (loop, MODIFIER_NONE, KEY_STATE_DOWN, alpha_entry_lowercase);
	}

	for (loop = DIK_A; loop <= DIK_L; loop ++)
	{
			
		set_event (loop, MODIFIER_NONE, KEY_STATE_DOWN, alpha_entry_lowercase);
	}

	for (loop = DIK_Z; loop <= DIK_M; loop ++)
	{
			
		set_event (loop, MODIFIER_NONE, KEY_STATE_DOWN, alpha_entry_lowercase);
	}

	for (loop = DIK_1; loop <= DIK_EQUALS; loop++)
	{

		set_event (loop, MODIFIER_NONE, KEY_STATE_DOWN, alpha_entry_lowercase);
	}

	set_event (DIK_COMMA, MODIFIER_NONE, KEY_STATE_DOWN, alpha_entry_lowercase);
	set_event (DIK_PERIOD, MODIFIER_NONE, KEY_STATE_DOWN, alpha_entry_lowercase);
	set_event (DIK_SLASH, MODIFIER_NONE, KEY_STATE_DOWN, alpha_entry_lowercase);
	set_event (DIK_MINUS, MODIFIER_NONE, KEY_STATE_DOWN, alpha_entry_lowercase);
	set_event (DIK_SUBTRACT, MODIFIER_NONE, KEY_STATE_DOWN, alpha_entry_lowercase);
	set_event (DIK_LBRACKET, MODIFIER_NONE, KEY_STATE_DOWN, alpha_entry_lowercase);
	set_event (DIK_RBRACKET, MODIFIER_NONE, KEY_STATE_DOWN, alpha_entry_lowercase);

	set_event (DIK_UNDERLINE, MODIFIER_LEFT_SHIFT, KEY_STATE_DOWN, alpha_entry_lowercase);
	set_event (DIK_UNDERLINE, MODIFIER_RIGHT_SHIFT, KEY_STATE_DOWN, alpha_entry_lowercase);

	//
	// special keys, clear shift keys
	//

	set_event (DIK_LSHIFT, MODIFIER_NONE, KEY_STATE_EITHER, NULL);
	set_event (DIK_RSHIFT, MODIFIER_NONE, KEY_STATE_EITHER, NULL);

	//
	// end and abort keys
	//

	set_event (DIK_RETURN, MODIFIER_NONE, KEY_STATE_DOWN, end_alpha_entry);
	set_event (DIK_ESCAPE, MODIFIER_NONE, KEY_STATE_DOWN, abort_alpha_entry);

	//
	// mouse buttons
	//

	set_event (MOUSE_LEFT_BUTTON, MODIFIER_NONE, BUTTON_STATE_DOWN, end_alpha_entry);
	set_event (MOUSE_RIGHT_BUTTON, MODIFIER_NONE, BUTTON_STATE_DOWN, end_alpha_entry);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void alpha_entry_lowercase (event *ev)
{

	int
		c;

	if (alpha_entry_function)
	{

		c = dinput_to_ascii (((event *) ev)->key);

		c = tolower (c);

		alpha_entry_function (c);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void alpha_entry_uppercase (event *ev)
{

	int
		c;

	if (alpha_entry_function)
	{

		c = dinput_to_upper_ascii (((event *) ev)->key);

		alpha_entry_function (c);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void end_alpha_entry (event *ev)
{

	void
		((*old_end_alpha_entry_function) (int key));

	old_end_alpha_entry_function = end_alpha_entry_function;

	pop_event (NULL);

	end_alpha_entry_function = NULL;

	abort_alpha_entry_function = NULL;

	alpha_entry_function = NULL;

	if (old_end_alpha_entry_function)
	{

		old_end_alpha_entry_function (((event *) ev)->key);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void abort_alpha_entry (event *ev)
{

	void
		((*old_abort_alpha_entry_function) (int key));

	old_abort_alpha_entry_function = abort_alpha_entry_function;

	pop_event (NULL);

	end_alpha_entry_function = NULL;

	abort_alpha_entry_function = NULL;

	alpha_entry_function = NULL;

	if (old_abort_alpha_entry_function)
	{

		old_abort_alpha_entry_function (((event *) ev)->key);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_alpha_event_functions (void ((*function) (int key)),
											void ((*end_function) (int key)),
											void ((*abort_function) (int key)))
{

	alpha_entry_function = function;

	end_alpha_entry_function = end_function;

	abort_alpha_entry_function = abort_function;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
