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

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ui_object
	*loading_screen,
	*loading_text;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void loading_function (ui_object *obj, void *arg);

static void initialise_demoload_graphic (ui_object *obj);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_loading_screen (void)
{
	float
		x1,
		y1,
		x2,
		y2;

	loading_screen = create_ui_object
		(
			UI_TYPE_SCREEN,
			UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
			UI_ATTR_VIRTUAL_SIZE (1.0, 1.0),
			//UI_ATTR_GRAPHIC (get_graphics_file_data (GRAPHICS_UI_APACHE_LOADING_SCREEN)),
			UI_ATTR_FUNCTION (loading_function),
			UI_ATTR_END
		);

	x1 = 0.620;
	y1 = 0.138;
	x2 = 0.2;
	y2 = 0.0625;

	loading_text = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (loading_screen),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2, y2),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_22),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_CENTRE),
	      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
	      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
			UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
			UI_ATTR_TEXT (get_trans ("Loading")),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_demoload_graphic (ui_object *obj)
{
	if ( get_ui_object_drawable ( obj ) )
	{

		//
		// Setup screen graphics
		//

		set_ui_object_texture_graphic (loading_screen, create_texture_graphic ("graphics\\ui\\cohokum\\demoload.psd", 0));

		reset_time_values (loading_screen);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loading_function (ui_object *obj, void *arg)
{

	switch (get_game_type ())
	{

		case GAME_TYPE_DEMO:
		{

			initialise_demoload_graphic (obj);

			set_ui_object_drawable (loading_text, TRUE);

			break;
		}

		case GAME_TYPE_CAMPAIGN:
		case GAME_TYPE_SKIRMISH:
		case GAME_TYPE_FREE_FLIGHT:
		default:
		{

			set_ui_object_drawable (loading_text, FALSE);

			switch (global_options.gunship_type)
			{

				case GUNSHIP_TYPE_APACHE:
				{

					//set_ui_object_graphic (loading_screen, get_graphics_file_data (GRAPHICS_UI_APACHE_LOADING_SCREEN));

					break;
				}

				case GUNSHIP_TYPE_HAVOC:
				{

					//set_ui_object_graphic (loading_screen, get_graphics_file_data (GRAPHICS_UI_HAVOC_LOADING_SCREEN));

					break;
				}
			}

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
