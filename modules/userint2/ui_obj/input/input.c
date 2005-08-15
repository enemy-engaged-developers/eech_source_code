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
// Used to get input from the keyboard in the form of a string.
// 1.	create a INPUT object, in the desired place, etc.
// 2.	to start inputting text set_ui_object_state (obj, UI_OBJECT_STATE_ON)
// 3.	when text input is finished it will call its NOTIFY function,
//		passing itself as the parameter. Text can then be got using
//		get_ui_object_text (obj).
//	4.	the INPUT object will turn itself off when alls finished.
//
//	It uses the events ev_alpha functions.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "userint2.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ui_object
	*input_object;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void input_entry (int key_code)
{

	const char
		*input_text;
	char
		text [128],
		c [2];

	float
		overflow;

	int
		input_size,
		len;

	if (key_code == dinput_to_ascii (DIK_BACK))
	{

		if (get_ui_object_text (input_object))
		{

			input_text = get_ui_object_text (input_object);

			len = strlen (input_text);
		
			len = bound (len, 1, 127);
	
			sprintf (text, "%s", input_text);
	
			text [len - 1] = '\0';
	
			set_ui_object_text (input_object, text);

			//
			// Reposition text origin if deleting
			//

			if ((get_ui_object_x_size (input_object) != 0.0) && (!get_limit_input_length (input_object)))
			{

				input_size = get_ui_object_x_size (input_object);

				overflow = ui_get_string_length (input_text) - (input_size - ui_get_font_width ());

				overflow = max (0.0, overflow);

				set_ui_object_x_origin (input_object, -overflow);
			}
		}
	}
	else
	{

		ui_object
			*parent;

		parent = get_ui_object_parent ( input_object );

		if (get_ui_object_x_size (input_object) != 0.0)
		{
	
			if ((parent) && (get_limit_input_length (input_object)))
			{
	
				font_types
					font;
	
				font = get_ui_font_type ();

				set_ui_font_type ( get_ui_object_font_type ( parent ) );
	
				input_text = get_ui_object_text (input_object);
		
				input_size = get_ui_object_x_size (input_object);
	
				//
				// limit text input to size of input object
				//
	
				if ((input_size == 0) || (ui_get_string_length (input_text) < (input_size - 10)))
				{
		
					sprintf (c, "%c", key_code);
		
					set_ui_object_add_text (input_object, (char *) c);
				}

				set_ui_font_type ( font );
			}
			else
			{
	
				font_types
					font;
	
				//
				// slide origin to keep text_cursor in box
				//
	
				font = get_ui_font_type ();

				set_ui_font_type ( get_ui_object_font_type ( parent ) );
	
				input_text = get_ui_object_text (input_object);
		
				input_size = get_ui_object_x_size (input_object);
	
				overflow = ui_get_string_length (input_text) - (input_size - ui_get_font_width ());
	
				overflow = max (0.0, overflow);
	
				set_ui_object_x_origin (input_object, -overflow);
		
				sprintf (c, "%c", key_code);
		
				set_ui_object_add_text (input_object, (char *) c);

				set_ui_font_type ( font );
			}
		}
		else
		{

			sprintf (c, "%c", key_code);

			set_ui_object_add_text (input_object, (char *) c);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void input_end (int key_code)
{

	void
		((*function) (ui_object *obj, void *arg));

	function = get_ui_object_function (input_object);

	if (function)
	{

		function (input_object, NULL);
	}

	set_ui_object_state (input_object, UI_OBJECT_STATE_OFF);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void input_abort (int key_code)
{

	void
		((*function) (ui_object *obj, void *arg));

	set_ui_object_text (input_object, NULL);

	set_ui_object_state (input_object, UI_OBJECT_STATE_OFF);

	function = get_ui_object_function (input_object);

	if (function)
	{

		function (input_object, NULL);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_input_events (void)
{

	set_alpha_events ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
