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

ui_object
	*tool_tips = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_area_ui_object (ui_object *obj)
{

	float
		x_origin,
		y_origin,
		x,
		//y,
		x1,
		y1,
		x2,
		y2,
		y3;

	int
		redraw_flag = FALSE,
		masked,
		width,
		height,
		pitch;

	area_ui_object
		*area;

	struct SCREEN
		*old_active_screen,
		*memory_graphic;
/*
	unsigned short int
		*graphic;

*/
	unsigned char
		*data;

	ui_object
		*parent;

	if (get_ui_object_redraw (obj))
	{

		area = (area_ui_object *) obj->data;

		//debug_log ("AR_DRAW: drawing area %f, %f  %f, %f", area->x, area->y, area->x_size, area->y_size);

		x1 = get_ui_object_x (obj);
		y1 = get_ui_object_y (obj);

		x2 = x1 + get_ui_object_x_size (obj);
		y2 = y1 + get_ui_object_y_size (obj);
	
  		// test
		x_origin = get_ui_object_x_origin (obj);
		y_origin = get_ui_object_y_origin (obj);
	
		ui_set_origin (x_origin, y_origin);
		// test

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

		//if (lock_screen (active_screen))
		{
	
			switch (get_ui_object_graphic_type (obj))
			{
	
				case UI_OBJECT_GRAPHIC:
				{
		
					unsigned short int
						*graphic;
	
					if (!get_ui_object_clear (obj))
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
	
							ui_draw_part_graphic (x1, y1, x2, y2, x1, y1, graphic);
	
							redraw_flag = TRUE;
						}
					}
	
					break;
				}

				case UI_OBJECT_TEXTURE_GRAPHIC:
				{
		
					if (!get_ui_object_clear (obj))
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
					}
			
					break;
				}
/*				{

					if (!get_ui_object_clear (obj))
					{

						real_colour
							start,
							end,
							colour;

						int
							start_time,
							current_time,
							current_length,
							time_length;

						int
							dr,
							dg,
							db,
							da;

						float
							dx,
							dy,
							anim_x1,
							anim_y1,
							anim_x2,
							anim_y2;

						float
							t;

						texture_graphic
							*graphic;
		
						graphic = get_ui_object_texture_graphic (obj);

						start_time = get_ui_object_start_time (obj);

						start_time += get_ui_object_offset_time (obj);

						current_time = get_system_time ();

						current_length = current_time - start_time;

						time_length = get_ui_object_time_length (obj);

						t = ( float ) current_length / ( float ) time_length;

						t = bound ( t, 0, 1 );

						get_ui_object_start_real_colour ( obj, &start.red, &start.green, &start.blue, &start.alpha );

						get_ui_object_end_real_colour ( obj, &end.red, &end.green, &end.blue, &end.alpha );

						dr = ( int ) end.red - ( int ) start.red;
						dg = ( int ) end.green - ( int ) start.green;
						db = ( int ) end.blue - ( int ) start.blue;
						da = ( int ) end.alpha - ( int ) start.alpha;

						dr *= t;
						dg *= t;
						db *= t;
						da *= t;

						colour.red = ( ( int ) start.red + dr );
						colour.green = ( ( int ) start.green + dg );
						colour.blue = ( ( int ) start.blue + db );
						colour.alpha = ( ( int ) start.alpha + da );

						anim_x1 = get_ui_object_anim_start_x (obj);
						anim_y1 = get_ui_object_anim_start_y (obj);

						dx = get_ui_object_anim_end_x (obj) - anim_x1;
						dy = get_ui_object_anim_end_y (obj) - anim_y1;

						anim_x1 += dx * t;
						anim_y1 += dy * t;
						anim_x2 = anim_x1 + get_ui_object_x_size (obj);
						anim_y2 = anim_y1 + get_ui_object_y_size (obj);

						ui_draw_texture_graphic ( anim_x1, anim_y1, anim_x2, anim_y2, graphic, colour);
					}

					break;
				}
				*/
	
				case UI_OBJECT_MEMORY_GRAPHIC:
				{
	
					memory_graphic = get_ui_object_memory_graphic (obj);

					//if (lock_screen (memory_graphic))
					{
		
						width = get_screen_width (memory_graphic);
		
						height = get_screen_height (memory_graphic);
		
						data = get_screen_data (memory_graphic);
		
						pitch = get_screen_pitch (memory_graphic);
		
						masked = get_ui_object_clear (obj);
		
						ui_draw_memory_graphic (obj, x1, y1, x2, y2, width, height, pitch, masked);

						//unlock_screen (memory_graphic);
					}
	
					redraw_flag = TRUE;
	
					break;
				}
	
				case UI_OBJECT_ALPHA_GRAPHIC:
				{

					unsigned short int
						*graphic;

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
	
				case UI_OBJECT_ZOOMABLE_PALETTE_GRAPHIC:
				{
		
					struct ZOOMABLE_GRAPHIC
						*zoomable_graphic;

					if (!get_ui_object_clear (obj))
					{
	
						zoomable_graphic = get_ui_object_zoomable_palette_graphic (obj);
	
						draw_zoomable_graphic (zoomable_graphic, area->cx, area->cy, x1, y1, x2, y2, area->zoom);
	
						redraw_flag = TRUE;
					}
	
					break;
				}
	
				case UI_OBJECT_NO_GRAPHIC:
				default:
				{
	
					if (!get_ui_object_clear (obj))
					{

						int
							old_state;

						old_state = get_ui_object_state (obj);

						if ((old_state == UI_OBJECT_STATE_OFF) && (get_ui_object_highlighted (obj)))
						{

							set_ui_object_state (obj, UI_OBJECT_STATE_HIGHLIGHTED);
						}
	
						ui_draw_area (x1, y1, x2, y2, obj);

						set_ui_object_state (obj, old_state);
	
						redraw_flag = TRUE;
					}
				}
			}
	
			// text position
	
			if (get_ui_object_text (obj))
			{

				const char
					*text_ptr;

				int
					count;
	
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
		
				set_ui_repaint_area (x1 + ui_x_origin, y1 + ui_y_origin, x2 + ui_x_origin + 1, y2 + ui_y_origin + 1);
			}
	
			//unlock_screen (active_screen);
		}

		set_active_screen (old_active_screen);

		area->redraw --;

		call_ui_object_draw_function (obj, NULL);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void tool_tips_draw_area_ui_object (ui_object *obj)
{

	if (get_ui_object_tool_tips (obj))
	{

		font_types
			old_font;

		unsigned int
			timer;

		timer = get_ui_object_tool_tips_timer (obj);

		//debug_log ("AR_DRAW: %d tool_tips_timer = %f", obj, (float) (timer / TIME_1_SECOND));
	
		if (timer < get_system_time ())
		{

			const char
				*text;

			float
				x,
				y,
				x_size,
				y_size;

			//debug_log ("AR_DRAW: drawing tool tips for object %d = %s", obj, get_ui_object_tool_tips (obj));

			// font
			old_font = get_ui_font_type ();
			set_ui_font_type (UI_FONT_ARIAL_14);
			//

			text = get_ui_object_tool_tips (obj);

			x_size = ui_get_string_length (text) + 10;
			y_size = ui_get_font_height () + 10;

			x = bound (get_mouse_x (), 5.0, get_screen_width (video_screen) - (x_size + 5.0));
			y = bound (get_mouse_y (), 5.0, get_screen_height (video_screen) - (y_size + 5.0));

			if (!tool_tips)
			{
	
				tool_tips = create_ui_object
					(
						UI_TYPE_BUTTON,
						UI_ATTR_PARENT (current_screen),
						UI_ATTR_POSITION (x, y),
						UI_ATTR_SIZE (x_size, y_size),
						UI_ATTR_TEXT (text),
						UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_14),
						UI_ATTR_DRAWABLE (TRUE),
						UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_NONE),
						UI_ATTR_END
					);
			}
			else
			{

				set_ui_object_x (tool_tips, x);
				set_ui_object_y (tool_tips, y);

				set_ui_object_x_size (tool_tips, x_size);
				set_ui_object_y_size (tool_tips, y_size);

				set_ui_object_text (tool_tips, text);
				set_ui_object_drawable (tool_tips, TRUE);
			}

			// font
			set_ui_font_type (old_font);
			//
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_area_ui_object_draw_functions (ui_object_types type)
{

	fn_draw_ui_object [type] = draw_area_ui_object;

	fn_tool_tips_draw_ui_object [type] = tool_tips_draw_area_ui_object;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_tool_tips (void)
{

	if (tool_tips)
	{

		set_ui_object_drawable (tool_tips, FALSE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
