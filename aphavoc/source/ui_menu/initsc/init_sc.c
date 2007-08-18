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

//VJ 030807 added wut file name display for startup screen
ui_object
	*WUT_text,
	*version_text,
	*copyright_text,
	*ah_installed_text,
	*initialising_text,
	*init_screen;

texture_graphic
	*init_screen_texture;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_init_screen (void)
{
	float
		x1,
		x2,
		y1,
		y2;

	char
		buf[128];

	x1 = 0.0;
	x2 = 1.0;
	y1 = 0.0;
	y2 = 1.0;
	

	init_screen = create_ui_object
		(
			UI_TYPE_SCREEN,
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2, y2),
			//UI_ATTR_GRAPHIC (get_graphics_file_data (GRAPHICS_UI_APACHE_INIT_SCREEN)),
			UI_ATTR_FUNCTION (init_function),
			UI_ATTR_END
		);

	x1 = 0.425;
	y1 = 0.951;
	x2 = 0.3;
	y2 = 0.0625;
	
	initialising_text = create_ui_object
		(
			UI_TYPE_TEXT,
			UI_ATTR_PARENT (init_screen),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2, y2),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
      	UI_ATTR_FONT_COLOUR (ui_init_screen_text_colour.r, ui_init_screen_text_colour.g, ui_init_screen_text_colour.b, 255),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_CENTRE),
			UI_ATTR_TEXT (""),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	x1 = 0.756;
	x1 = 0.98;
	y1 = 0.014;
	x2 = 0.0;
	y2 = 0.0625;
	
	ah_installed_text = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (init_screen),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2, y2),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
      	UI_ATTR_FONT_COLOUR (ui_init_screen_text_colour.r, ui_init_screen_text_colour.g, ui_init_screen_text_colour.b, 255),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
			UI_ATTR_TEXT (""),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	x1 = 0.80;
	y1 = 0.951;
	x2 = 0.3;
	y2 = 0.0625;
	
	version_text = create_ui_object
		(
			UI_TYPE_TEXT,
			UI_ATTR_PARENT (init_screen),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2, y2),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
      	UI_ATTR_FONT_COLOUR (ui_init_screen_text_colour.r, ui_init_screen_text_colour.g, ui_init_screen_text_colour.b, 255),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_CENTRE),
			UI_ATTR_TEXT (""),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

//VJ 030807 added wut file name display for startup screen
	x1 = 0.800;
	y1 = 0.88;
	x2 = 0.3;
	y2 = 0.0625;
	
	WUT_text = create_ui_object
		(
			UI_TYPE_TEXT,
			UI_ATTR_PARENT (init_screen),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2, y2),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
      	UI_ATTR_FONT_COLOUR (255,255,255,255),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_CENTRE),
			UI_ATTR_TEXT (""),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	x1 = 0.02;
	y1 = 0.951;
	x2 = 0.3;
	y2 = 0.0625;

	buf[0] = 255;
	buf[1] = '\0';
	strcat ( buf, " 2000 Razorworks Ltd." );

	copyright_text = create_ui_object
		(
			UI_TYPE_TEXT,
			UI_ATTR_PARENT (init_screen),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2, y2),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_14),
      	UI_ATTR_FONT_COLOUR (ui_init_screen_text_colour.r, ui_init_screen_text_colour.g, ui_init_screen_text_colour.b, 255),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_CENTRE),
			UI_ATTR_TEXT (buf),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void init_function (ui_object *obj, void *arg)
{

	set_mouse_off ();

	if ( get_ui_object_drawable ( obj ) )
	{

		if ( main_screen_texture )
		{
	
			destroy_texture_graphic (init_screen_texture);

			init_screen_texture = NULL;
		}
	
		init_screen_texture = create_texture_graphic ( "graphics\\ui\\cohokum\\title.psd" );
	
		set_ui_object_texture_graphic (init_screen, init_screen_texture);
	
		blit_front_buffer_to_render_buffer ();
	
		ui_set_user_function (NULL);
	}
	else
	{
		if (main_screen_texture)
		{
	
			destroy_texture_graphic (init_screen_texture);

			init_screen_texture = NULL;
		}
	}
	
	ui_force_update ();

	full_initialise_game ();

	set_mouse_on ();

	switch (command_line_run_mode)
	{
/*
		case RUN_MODE_AITOOL:
		{

			initialise_aitool ();

			push_ui_screen (aitool_select_map_screen);

			break;
		}
*/
		case RUN_MODE_NORMAL:
		default:
		{

			if (command_line_comms_dedicated_server)
			{

				process_game_initialisation_phases ();
			}
			else
			{
	
				play_cd_music ( CD_MUSIC_TYPE_INTRO );

				#if DEMO_VERSION
					push_ui_screen (advert_screen);
				#else
					push_ui_screen (main_screen);
				#endif
			}

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
