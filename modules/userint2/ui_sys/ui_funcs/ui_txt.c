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



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "userint2.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void (*fn_set_ui_object_text [NUM_UI_TYPES]) (ui_object *obj, const char *text);

const char *(*fn_get_ui_object_text [NUM_UI_TYPES]) (ui_object *obj);


void (*fn_set_ui_object_add_text [NUM_UI_TYPES]) (ui_object *obj, const char *text);


void (*fn_set_ui_object_text_justify [NUM_UI_TYPES]) (ui_object *obj, text_justify_types justify);

text_justify_types (*fn_get_ui_object_text_justify [NUM_UI_TYPES]) (ui_object *obj);


void (*fn_set_ui_object_font_type [NUM_UI_TYPES]) (ui_object *obj, int font_id);

int (*fn_get_ui_object_font_type [NUM_UI_TYPES]) (ui_object *obj);


void (*fn_set_ui_object_font_colour [NUM_UI_TYPES]) (ui_object *obj, char red, char green, char blue, char alpha);
void (*fn_set_ui_object_font_colour_end [NUM_UI_TYPES]) (ui_object *obj, char red, char green, char blue, char alpha);
void (*fn_set_ui_object_font_colour_start [NUM_UI_TYPES]) (ui_object *obj, char red, char green, char blue, char alpha);

rgb_colour (*fn_get_ui_object_font_colour [NUM_UI_TYPES]) (ui_object *obj);
rgb_colour (*fn_get_ui_object_font_colour_end [NUM_UI_TYPES]) (ui_object *obj);
rgb_colour (*fn_get_ui_object_font_colour_start [NUM_UI_TYPES]) (ui_object *obj);


void (*fn_set_ui_object_highlighted_font_type [NUM_UI_TYPES]) (ui_object *obj, int font_id);

int (*fn_get_ui_object_highlighted_font_type [NUM_UI_TYPES]) (ui_object *obj);


void (*fn_set_ui_object_highlighted_font_colour [NUM_UI_TYPES]) (ui_object *obj, char red, char green, char blue, char alpha);
void (*fn_set_ui_object_highlighted_font_colour_end [NUM_UI_TYPES]) (ui_object *obj, char red, char green, char blue, char alpha);
void (*fn_set_ui_object_highlighted_font_colour_start [NUM_UI_TYPES]) (ui_object *obj, char red, char green, char blue, char alpha);

rgb_colour (*fn_get_ui_object_highlighted_font_colour [NUM_UI_TYPES]) (ui_object *obj);
rgb_colour (*fn_get_ui_object_highlighted_font_colour_end [NUM_UI_TYPES]) (ui_object *obj);
rgb_colour (*fn_get_ui_object_highlighted_font_colour_start [NUM_UI_TYPES]) (ui_object *obj);


void (*fn_set_ui_object_selected_font_type [NUM_UI_TYPES]) (ui_object *obj, int font_id);

int (*fn_get_ui_object_selected_font_type [NUM_UI_TYPES]) (ui_object *obj);


void (*fn_set_ui_object_selected_font_colour [NUM_UI_TYPES]) (ui_object *obj, char red, char green, char blue, char alpha);
void (*fn_set_ui_object_selected_font_colour_end [NUM_UI_TYPES]) (ui_object *obj, char red, char green, char blue, char alpha);
void (*fn_set_ui_object_selected_font_colour_start [NUM_UI_TYPES]) (ui_object *obj, char red, char green, char blue, char alpha);

rgb_colour (*fn_get_ui_object_selected_font_colour [NUM_UI_TYPES]) (ui_object *obj);
rgb_colour (*fn_get_ui_object_selected_font_colour_end [NUM_UI_TYPES]) (ui_object *obj);
rgb_colour (*fn_get_ui_object_selected_font_colour_start [NUM_UI_TYPES]) (ui_object *obj);


void (*fn_set_ui_object_tool_tips [NUM_UI_TYPES]) (ui_object *obj, const char *tool_tips);

const char *(*fn_get_ui_object_tool_tips [NUM_UI_TYPES]) (ui_object *obj);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void default_set_ui_object_text (ui_object *obj, const char *text)
{

	obj;
	text;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char *default_get_ui_object_text (ui_object *obj)
{

	obj;

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void default_set_ui_object_add_text (ui_object *obj, const char *text)
{

	obj;
	text;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void default_set_ui_object_text_justify (ui_object *obj, text_justify_types justify)
{

	obj;
	justify;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

text_justify_types default_get_ui_object_text_justify (ui_object *obj)
{

	obj;

	return TEXT_JUSTIFY_CENTRE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void default_set_ui_object_font_type (ui_object *obj, int font_id)
{

	obj;
	font_id;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int default_get_ui_object_font_type (ui_object *obj)
{
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void default_set_ui_object_font_colour (ui_object *obj, char red, char green, char blue, char alpha)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

rgb_colour default_get_ui_object_font_colour (ui_object *obj)
{
	return ui_colour_white;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_ui_object_text_default_functions (void)
{

	int
		i;

	for (i = 0; i < NUM_UI_TYPES; i ++)
	{

		fn_set_ui_object_text [i]				= default_set_ui_object_text;

		fn_get_ui_object_text [i]				= default_get_ui_object_text;


		fn_set_ui_object_add_text [i]			= default_set_ui_object_add_text;


		fn_set_ui_object_text_justify [i]	= default_set_ui_object_text_justify;

		fn_get_ui_object_text_justify [i]	= default_get_ui_object_text_justify;


		fn_set_ui_object_font_type [i]		= default_set_ui_object_font_type;

		fn_get_ui_object_font_type [i]		= default_get_ui_object_font_type;


		fn_set_ui_object_font_colour [i]				= default_set_ui_object_font_colour;
		fn_set_ui_object_font_colour_end [i]		= default_set_ui_object_font_colour;
		fn_set_ui_object_font_colour_start [i]		= default_set_ui_object_font_colour;

		fn_get_ui_object_font_colour [i]				= default_get_ui_object_font_colour;
		fn_get_ui_object_font_colour_end [i]		= default_get_ui_object_font_colour;
		fn_get_ui_object_font_colour_start [i]		= default_get_ui_object_font_colour;


		fn_set_ui_object_highlighted_font_type [i]	= default_set_ui_object_font_type;

		fn_get_ui_object_highlighted_font_type [i]	= default_get_ui_object_font_type;


		fn_set_ui_object_highlighted_font_colour [i]			= default_set_ui_object_font_colour;
		fn_set_ui_object_highlighted_font_colour_end [i]	= default_set_ui_object_font_colour;
		fn_set_ui_object_highlighted_font_colour_start [i]	= default_set_ui_object_font_colour;

		fn_get_ui_object_highlighted_font_colour [i]			= default_get_ui_object_font_colour;
		fn_get_ui_object_highlighted_font_colour_end [i]	= default_get_ui_object_font_colour;
		fn_get_ui_object_highlighted_font_colour_start [i]	= default_get_ui_object_font_colour;


		fn_set_ui_object_selected_font_type [i]	= default_set_ui_object_font_type;

		fn_get_ui_object_selected_font_type [i]	= default_get_ui_object_font_type;


		fn_set_ui_object_selected_font_colour [i]			= default_set_ui_object_font_colour;
		fn_set_ui_object_selected_font_colour_end [i]	= default_set_ui_object_font_colour;
		fn_set_ui_object_selected_font_colour_start [i]	= default_set_ui_object_font_colour;

		fn_get_ui_object_selected_font_colour [i]			= default_get_ui_object_font_colour;
		fn_get_ui_object_selected_font_colour_end [i]	= default_get_ui_object_font_colour;
		fn_get_ui_object_selected_font_colour_start [i]	= default_get_ui_object_font_colour;


		fn_set_ui_object_tool_tips [i]				= default_set_ui_object_text;

		fn_get_ui_object_tool_tips [i]				= default_get_ui_object_text;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
