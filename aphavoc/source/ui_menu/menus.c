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

void initialise_ui_menus (void)
{

	initialise_title_screen ();

	#if DEMO_VERSION
		initialise_advert_screen ();
	#endif

	initialise_main_screen ();

	#if !DEMO_VERSION
		initialise_select_player_screen ();
	#endif

	initialise_options_screen ();

	initialise_credits_screen ();

// GCsDriver  08-12-2007
	initialise_modcredits_screen ();

	initialise_game_type_screen ();

	initialise_session_screen ();

	initialise_exit_screen ();

	initialise_gunships_screen ();

	initialise_combat_zone_screen ();

	initialise_loading_screen ();

	initialise_ingame_screen ();

	initialise_campaign_screen ();

	initialise_free_flight_screen ();

	initialise_dedicated_server_screen ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_ui_frontend_list_object_highlightable (ui_object *obj)
{
	rgb_colour
		*col;

	ASSERT (obj);

	col = &ui_list_text_hilite_colour;

	set_ui_object_highlighted_font_colour (obj, col->r, col->g, col->b, col->a);

	set_ui_object_highlightable (obj, TRUE);

	set_ui_object_highlighted_notify_on (obj, NOTIFY_TYPE_CONTINUAL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void preprocess_translation_object_size (ui_object *change_obj, ui_object *check_obj, const char **translations, int num_trans, resize_ui_object_types flag)
{
	int
		i,
		justification;

	float
		x1,
		x2,
		x_origin,
		current_x_size;

	x1 = x2 = x_origin = 0.0;

	current_x_size = get_ui_object_x_size_end (change_obj);

	////////////////////////////////////////////////////////////////
	// get new size for object(s)

	// option box titles
	if (flag == RESIZE_OPTION_BOX_TITLE)
	{
#if 0	// Retro 17Jul2004 - FIXME
		if (get_global_current_language () != LANGUAGE_ENGLISH)
		{
			x2 = OPTION_BOX_EXTRA_LARGE_WIDTH;
		}
#endif
	}
	else
	{
		font_types
			old_font;

		float
			length,
			parent_size;

		length = 0.0;

		parent_size = get_ui_object_x_size (get_ui_object_parent (change_obj));
	
		// set font so we get correct size returned from ui_get_string_length()
		old_font = get_ui_font_type ();
	
		if (check_obj != NULL)
		{
			set_ui_font_type (get_ui_object_font_type (check_obj));
		}
		else
		{
			set_ui_font_type (get_ui_object_font_type (change_obj));
		}
			
		// option cycle buttons - uses translation array
		if ((flag == RESIZE_OPTION_CYCLE_BUTTON) || (flag == RESIZE_SESSPARM_CYCLE_BUTTON))
		{
			for (i =0; i < num_trans; i++)
			{
				length = max (length, ui_get_string_length (translations[i]));
			}
		}

		// single word/phrase buttons
		else
		{
			if (check_obj != NULL)
			{
				length = ui_get_string_length (get_ui_object_text (check_obj));
			}
			else
			{
				length = ui_get_string_length (get_ui_object_text (change_obj));
			}
		}

		length += 0.1 * length;

		// ui get string length should take care of this itself:

		if (parent_size)
		{
			length /= parent_size;
		}
		else
		{
			debug_fatal ("MENUS.C: parent has 0 x size!");
		}

		// reset font
		set_ui_font_type (old_font);	

		// if the object to be resized is an option button, bound it to a defined size
		x2 = max (length, OPTION_BOX_SMALL_WIDTH);

		if (flag == RESIZE_OPTION_CYCLE_BUTTON)
		{
			if (x2 > OPTION_BOX_LARGE_WIDTH)
			{
				x2 = OPTION_BOX_EXTRA_LARGE_WIDTH;
			}
			else if (x2 > OPTION_BOX_MEDIUM_WIDTH)
			{
				x2 = OPTION_BOX_LARGE_WIDTH;
			}
			else
			{
				x2 = OPTION_BOX_SMALL_WIDTH;
			}
		}
	}

	////////////////////////////////////////////////////////////////
	// resize objects if x2 has recieved a value - i.e. a change is required

	if (x2 > current_x_size)
	{
		// get x start of object, base on justification of text

		if (check_obj == NULL)
		{
			justification = get_ui_object_text_justify (change_obj);
		}
		else
		{
			justification = get_ui_object_text_justify (check_obj);
		}

		x_origin = get_ui_object_x_end (change_obj);

		// get new x position of object

		if ((justification == TEXT_JUSTIFY_RIGHT_CENTRE) || (justification == TEXT_JUSTIFY_RIGHT_TOP) || (justification == TEXT_JUSTIFY_RIGHT_BOTTOM))
		{
			x1 = max (0.0f, (x_origin + current_x_size - x2));
		}
//		else if ((justification == TEXT_JUSTIFY_CENTRE) || (justification == TEXT_JUSTIFY_CENTRE_TOP) || (justification == TEXT_JUSTIFY_CENTRE_BOTTOM))
//		{
//			x1 = max (0.0, x_origin - ((get_ui_object_virtual_x_size (change_obj) - x2) * 0.5));
//		}
		else
		{
			if (flag != RESIZE_SESSPARM_CYCLE_BUTTON)
			{
				x1 = x_origin;
			}
			else
			{
				x1 = max (0.0, (1.0 - x2));
			}
		}

		if (flag == RESIZE_OPTION_BOX_TITLE)
		{
			x1 += OPTION_TITLE_OFFSET_X * 0.5;
		}

		// set size & new position - beware of animated parameters...
		// this is really the responsibility of the ui draw code,
		// which if the object parameter isn't animated should set
		// start & end values to be the same,
		// but a certain someone :) hasn't done it yet!

		if (get_ui_object_x_size_start (change_obj) != get_ui_object_x_size_end (change_obj))
		{
			set_ui_object_x_size_end (change_obj, x2);
		}
		else
		{
			set_ui_object_x_size_start (change_obj, x2);

			set_ui_object_x_size_end (change_obj, x2);
		}

		if (get_ui_object_x_start (change_obj) != get_ui_object_x_end (change_obj))
		{
			set_ui_object_x_end (change_obj, x1);
		}
		else
		{
			set_ui_object_x_start (change_obj, x1);

			set_ui_object_x_end (change_obj, x1);
		}


		if (get_ui_object_texture_graphic (change_obj) != NULL)
		{
			float
				graphic_size;

			graphic_size = get_ui_object_x_size (change_obj) / get_global_3d_visual_screen_width();

		////////////////////////////////////////////////////////////////
		// change graphic

			if (graphic_size > OPTION_BOX_LARGE_WIDTH)
			{
				set_ui_object_texture_graphic (change_obj, options_box_extra_large);
			}
			else if (graphic_size > OPTION_BOX_MEDIUM_WIDTH)
			{
				set_ui_object_texture_graphic (change_obj, options_box_large);
			}
			else if (graphic_size > OPTION_BOX_SMALL_WIDTH)
			{
				set_ui_object_texture_graphic (change_obj, options_box_medium);
			}
			else
			{
				set_ui_object_texture_graphic (change_obj, options_box_small);
			}
		}
		
		/*
		////////////////////////////////////////////////////////////////
		// change graphic

		if (get_ui_object_texture_graphic (change_obj) != NULL)
		{
			if (x2 > OPTION_BOX_LARGE_WIDTH)
			{
				set_ui_object_texture_graphic (change_obj, options_box_extra_large);
			}
			else if (x2 > OPTION_BOX_MEDIUM_WIDTH)
			{
				set_ui_object_texture_graphic (change_obj, options_box_large);
			}
			else if (x2 > OPTION_BOX_SMALL_WIDTH)
			{
				set_ui_object_texture_graphic (change_obj, options_box_medium);
			}
			else
			{
				set_ui_object_texture_graphic (change_obj, options_box_small);
			}
		}
		*/
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void process_ingame_text_object_size (ui_object *change_obj, ui_object *check_obj, const char **translations, int num_trans, resize_ui_object_types flag)
{
	int
		i,
		justification;
	font_types
		current_font,
		old_font;

	float
		length,
		parent_size,
		x1,
		x2,
		x_origin,
		current_x_size;

	x1 = x2 = x_origin = 0.0;

	current_x_size = get_ui_object_x_size_end (change_obj);

	////////////////////////////////////////////////////////////////
	// get new size for object(s)

	length = 0.0;

	parent_size = get_ui_object_x_size (get_ui_object_parent (change_obj));

	// set font so we get correct size returned from ui_get_string_length()
	old_font = get_ui_font_type ();

	if (check_obj != NULL)
	{
		current_font = get_ui_object_font_type (check_obj);

		set_ui_font_type (current_font);
	}
	else
	{
		current_font = get_ui_object_font_type (change_obj);

		set_ui_font_type (current_font);
	}
		
	// use translation array if set
	if (translations)
	{
		for (i =0; i < num_trans; i++)
		{
			length = max (length, ui_get_string_length (translations[i]));
		}
	}
	// single word/phrase buttons
	else
	{
		if (check_obj != NULL)
		{
			length = ui_get_string_length (get_ui_object_text (check_obj));
		}
		else
		{
			length = ui_get_string_length (get_ui_object_text (change_obj));
		}
	}

	// ui get string length should take care of this itself:

//	length += 0.1 * length;

	if (parent_size)
	{
		length /= parent_size;
	}
	else
	{
		debug_fatal ("MENUS.C: parent has 0 x size!");
	}

	// reset font
	set_ui_font_type (old_font);	

	x2 = length;

	////////////////////////////////////////////////////////////////
	// resize objects if x2 has recieved a value - i.e. a change is required

	if (x2 != current_x_size)
	{
		// get x start of object, base on justification of text

		if (check_obj == NULL)
		{
			justification = get_ui_object_text_justify (change_obj);
		}
		else
		{
			justification = get_ui_object_text_justify (check_obj);
		}

		x_origin = get_ui_object_x_end (change_obj);

		// get new x position of object

		if ((justification == TEXT_JUSTIFY_RIGHT_CENTRE) || (justification == TEXT_JUSTIFY_RIGHT_TOP) || (justification == TEXT_JUSTIFY_RIGHT_BOTTOM))
		{
			x1 = max (0.0f, (x_origin + current_x_size - x2));
		}
		else
		{
			if (flag != RESIZE_SESSPARM_CYCLE_BUTTON)
			{
				x1 = x_origin;
			}
			else
			{
				x1 = max (0.0, (1.0 - x2));
			}
		}

		if (flag == RESIZE_OPTION_BOX_TITLE)
		{
			x1 += OPTION_TITLE_OFFSET_X * 0.5;
		}

		if (get_ui_object_x_size_start (change_obj) != get_ui_object_x_size_end (change_obj))
		{
			set_ui_object_x_size_end (change_obj, x2);
		}
		else
		{
			set_ui_object_x_size_start (change_obj, x2);

			set_ui_object_x_size_end (change_obj, x2);
		}

		if (get_ui_object_x_start (change_obj) != get_ui_object_x_end (change_obj))
		{
			set_ui_object_x_end (change_obj, x1);
		}
		else
		{
			set_ui_object_x_start (change_obj, x1);

			set_ui_object_x_end (change_obj, x1);
		}

		////////////////////////////////////////////////////////////////
		// change graphic

		if (get_ui_object_texture_graphic (change_obj) != NULL)
		{
			if (x2 > OPTION_BOX_LARGE_WIDTH)
			{
				set_ui_object_texture_graphic (change_obj, options_box_extra_large);
			}
			else if (x2 > OPTION_BOX_MEDIUM_WIDTH)
			{
				set_ui_object_texture_graphic (change_obj, options_box_large);
			}
			else if (x2 > OPTION_BOX_SMALL_WIDTH)
			{
				set_ui_object_texture_graphic (change_obj, options_box_medium);
			}
			else
			{
				set_ui_object_texture_graphic (change_obj, options_box_small);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_text_option_backdrop_object (ui_object *bdrop_obj, ui_object *check_obj)
{
	font_types
		new_font,
		old_font;

	float
		x1,
		y1,
		x2,
		y2,
		factor,
		parent_size,
		text_length;

	// get correct position & size
	parent_size = get_ui_object_x_size (get_ui_object_parent (bdrop_obj));
	
	old_font = get_ui_font_type ();

	new_font = get_ui_object_font_type (check_obj);

	set_ui_font_type (new_font);

	text_length = ui_get_string_length (get_ui_object_text (check_obj));

	set_ui_font_type (old_font);

	factor = ((int) UI_FONT_THICK_ARIAL_22) /  ((int) get_ui_object_font_type (check_obj));

	x2 = TEXT_OPTION_BDROP_WIDTH * factor;

	// ensure x2 > text length
	if (parent_size)
	{
		text_length /= parent_size;
	}
	else
	{
		debug_fatal ("MENUS.C: parent has 0 x size!");
	}

	if (x2 < text_length)
	{
		x2 = text_length * 1.5;
	}
	
	switch (new_font)
	{
		case UI_FONT_ARIAL_18:
		case UI_FONT_THICK_ARIAL_18:
		case UI_FONT_ITALIC_ARIAL_18:
		case UI_FONT_THICK_ITALIC_ARIAL_18:
		{
			y2 = 0.040;

			break;
		}
		case UI_FONT_STRETCH_ITALIC_ARIAL_18:
		{
			y2 = 0.045;

			break;
		}
		case UI_FONT_ARIAL_22:
		case UI_FONT_THICK_ARIAL_22:
		{
			y2 = TEXT_OPTION_BDROP_HEIGHT;

			break;
		}
		default:
		{
			y2 = TEXT_OPTION_BDROP_HEIGHT;
		}
	}

	x1 = (get_ui_object_x_end (check_obj) + get_ui_object_virtual_x_size (check_obj) * 0.5) - (x2 * 0.5);

	y1 = (get_ui_object_y_end (check_obj) + get_ui_object_virtual_y_size (check_obj) * 0.5) - (y2 * 0.5);


	// set correct position & size
	set_ui_object_virtual_x_size (bdrop_obj, x2);

	set_ui_object_virtual_y_size (bdrop_obj, y2);

	set_ui_object_x (bdrop_obj, x1);

	set_ui_object_y (bdrop_obj, y1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


