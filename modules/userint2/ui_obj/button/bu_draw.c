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

static void draw_button_ui_object (ui_object *obj)
{

	float
//		px1,
//		py1,
		x,
		//y,
		//vp_x1,
		//vp_y1,
		//vp_x2,
		//vp_y2,
		x_size,
		y_size,
		x_origin,
		y_origin,
		x1,
		y1,
		x2,
		y2;
		//nx1,
		//ny1,
		//nx2,
		//ny2;

	int
		redraw_flag = FALSE;
//		width,
//		height,
//		pitch;

	struct SCREEN
		*old_active_screen;
//		*memory_graphic;

//	unsigned short
//		*graphic;

//	unsigned char
//		*data;

//	ui_object
//		*parent;

	button_ui_object
		*button;

	button = obj->button;

	if (get_ui_object_redraw (obj))
	{

		if (get_ui_object_autosize (obj))
		{

			ui_object_autosize (obj);
		}

		//debug_log ("BU_DRAW: drawing button %f, %f  %f, %f", button->area.x, button->area.y, button->area.x_size, button->area.y_size);

		//x1 = get_ui_object_x (obj);
		//y1 = get_ui_object_y (obj);

		x_size = get_ui_object_x_size (obj);
		y_size = get_ui_object_y_size (obj);
	
		x_origin = get_ui_object_x_origin (obj);
		y_origin = get_ui_object_y_origin (obj);
	
		ui_set_origin (x_origin, y_origin);


		//x2 = x1 + x_size;// - 1;
		//y2 = y1 + y_size;// - 1;

		x1 = get_ui_object_x (obj);
		y1 = get_ui_object_y (obj);

		x1 += x_origin;
		y1 += y_origin;

		x2 = x1 + get_ui_object_x_size (obj);
		y2 = y1 + get_ui_object_y_size (obj);

		old_active_screen = get_active_screen ();

		if (get_ui_object_active_screen (obj))
		{
	
			set_active_screen (get_ui_object_active_screen (obj));
		}
		else
		{

			set_active_screen (video_screen);
		}

		// debug
		set_active_screen (video_screen);
		// debug

//		if (lock_screen (active_screen))
		{

//			memory_graphic = get_ui_object_memory_graphic (obj);
	
			if (!get_ui_object_clear (obj))
			{
	
				switch (get_ui_object_graphic_type (obj))
				{

					case UI_OBJECT_TEXTURE_GRAPHIC:
					{
			
						texture_graphic
							*graphic;
					
						if ((get_ui_object_state (obj) == UI_OBJECT_STATE_ON) && (get_ui_object_selected_texture_graphic (obj)))
						{
					
							graphic = get_ui_object_selected_texture_graphic (obj);
						}
						else if ((get_ui_object_highlighted (obj)) && (get_ui_object_highlighted_texture_graphic (obj)))
						{
					
							graphic = get_ui_object_highlighted_texture_graphic (obj);
						}
						else
						{
					
							graphic = get_ui_object_texture_graphic (obj);
						}
			
						if (graphic)
						{

							rgb_colour
								colour;

							real_colour
								text_colour;

							colour = get_ui_object_colour ( obj );

							text_colour.red = colour.r;
							text_colour.green = colour.g;
							text_colour.blue = colour.b;
							text_colour.alpha = colour.a;

							ui_draw_texture_graphic (x1, y1, x2, y2, graphic, text_colour);
						}
						else
						{
				
							ui_draw_area (0, 0, x2 - x1, y2 - y1, obj);
						}
				
						break;
					}
/*
					case UI_OBJECT_GRAPHIC:
					{
			
						if (get_ui_object_state (obj) == UI_OBJECT_STATE_ON)
						{
		
							graphic = get_ui_object_graphic (obj);
		
							ui_draw_graphic (x1, y1, x2, y2, graphic);
	
							redraw_flag = TRUE;
						}
						else
						{
	
							parent = get_ui_object_parent (obj);
	
							if (parent)
							{
	
								graphic = get_ui_object_graphic (parent);
	
								px1 = get_ui_object_x (parent);
	
								py1 = get_ui_object_y (parent);
	
								x1 -= px1;
								x2 -= px1;
	
								y1 -= py1;
								y2 -= py1;
		
								ui_draw_part_graphic (x1, y1, x2, y2, x1, y1, graphic);
	
								redraw_flag = TRUE;
							}
						}
	
						break;
					}
	
					case UI_OBJECT_MEMORY_GRAPHIC:
					{
		
						memory_graphic = get_ui_object_memory_graphic (obj);
	
						if (lock_screen (memory_graphic))
						{
		
							width = get_screen_width (memory_graphic);
		
							height = get_screen_height (memory_graphic);
		
							data = get_screen_data (memory_graphic);
		
							pitch = get_screen_pitch (memory_graphic);
			
							ui_draw_memory_graphic (obj, x1, y1, x2, y2, width, height, pitch, FALSE);
		
							unlock_screen (memory_graphic);
						}
	
						redraw_flag = TRUE;
	
						break;
					}
	
					case UI_OBJECT_ALPHA_GRAPHIC:
					{
			
						if (!get_ui_object_clear (obj))
						{
			
							graphic = get_ui_object_graphic (obj);
		
							ui_draw_alpha_graphic (x1, y1, x2, y2, graphic);
		
							redraw_flag = TRUE;
						}
						else
						{
		
							parent = get_ui_object_parent (obj);
		
							if (parent)
							{
		
								graphic = get_ui_object_graphic (parent);
		
								ui_draw_part_alpha_graphic (x1, y1, x2, y2, x1, y1, graphic);
		
								redraw_flag = TRUE;
							}
						}
		
						break;
					}
*/
					case UI_OBJECT_NO_GRAPHIC:
					default:
					{

						int
							state;

						state = get_ui_object_state (obj);

						if ((state == UI_OBJECT_STATE_OFF) && (get_ui_object_highlighted (obj)))
						{

							state = UI_OBJECT_STATE_HIGHLIGHTED;
						}

						ui_draw_button (x1, y1, x2, y2, state);
	
						redraw_flag = TRUE;
					}
				}
			}
		
			if (get_ui_object_text (obj))
			{

				char
					*text_ptr;

				int
					count;

				float
					y3;
	
				ui_save_current_font ();

				ui_set_object_font (obj);

				// count number of lines spanned

				text_ptr = get_ui_object_text (obj);

				count = 0;

				while (text_ptr)
				{

					count ++;

					text_ptr = strchr (text_ptr, '\n');

					// if found, step over it and display the next part of string
					if (text_ptr)
					{

						text_ptr ++;
					}
				}

				// now draw text

				text_ptr = get_ui_object_text (obj);
			
				get_text_y_position (&y3, y1, y2, text_ptr, get_ui_object_text_justify (obj), count);

				while (text_ptr)
				{
			
					get_text_x_position (&x, x1, x2, text_ptr, get_ui_object_text_justify (obj));
			
					ui_display_text (text_ptr, x, y3);

					y3 += ui_get_font_height ();

					// check for carriage return
					text_ptr = strchr (text_ptr, '\n');

					// if found, step over it and display the next part of string
					if (text_ptr)
					{

						text_ptr ++;
					}
				}

				ui_restore_current_font ();
	
				redraw_flag = TRUE;
			}
	
			if (redraw_flag)
			{
	
				set_ui_repaint_area (x1 - 1, y1 - 1, x2 + 1, y2 + 1);
			}
	
//			unlock_screen (active_screen);
		}

		set_active_screen (old_active_screen);

		button->area.redraw --;

		call_ui_object_draw_function (obj, NULL);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_button_ui_object_draw_functions (ui_object_types type)
{

	fn_draw_ui_object [type] = draw_button_ui_object;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
