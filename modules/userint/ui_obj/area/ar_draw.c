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

#include "userint.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_area_ui_object (ui_object *obj)
{

	float
		x,
		y,
		x1,
		y1,
		x2,
		y2;

	int
		redraw_flag = FALSE,
		masked,
		width,
		height,
		pitch;

	font_types
		font_id;

	area_ui_object
		*area;

	struct SCREEN
		*old_active_screen,
		*memory_graphic;

	unsigned short int
		*graphic;

	struct ZOOMABLE_GRAPHIC
		*zoomable_graphic;

	unsigned char
		*data;

	ui_object
		*parent;

	if (get_ui_object_redraw (obj))
	{

		area = (area_ui_object *) obj->data;

		//debug_log ("AR_DRAW: drawing area %f, %f  %f, %f", area->x, area->y, area->x_size, area->y_size);

		x1 = area->x;
		y1 = area->y;

		x2 = x1 + area->x_size;
		y2 = y1 + area->y_size;

		old_active_screen = get_active_screen ();

		if (get_ui_object_active_screen (obj))
		{
	
			set_active_screen (get_ui_object_active_screen (obj));
		}
		else
		{

			set_active_screen (video_screen);
		}

		if (lock_screen (active_screen))
		{
	
			switch (get_ui_object_graphic_type (obj))
			{
	
				case UI_OBJECT_GRAPHIC:
				{
		
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
	
				case UI_OBJECT_MEMORY_GRAPHIC:
				{
	
					memory_graphic = get_ui_object_memory_graphic (obj);

					if (lock_screen (memory_graphic))
					{
		
						width = get_screen_width (memory_graphic);
		
						height = get_screen_height (memory_graphic);
		
						data = get_screen_data (memory_graphic);
		
						pitch = get_screen_pitch (memory_graphic);
		
						masked = get_ui_object_clear (obj);
		
						ui_draw_memory_graphic (obj, x1, y1, x2, y2, width, height, pitch, masked);

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
	
				case UI_OBJECT_ZOOMABLE_PALETTE_GRAPHIC:
				{
		
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
	
						ui_draw_area (x1, y1, x2, y2);
	
						redraw_flag = TRUE;
					}
				}
			}
	
			// text position
	
			if (get_ui_object_text (obj))
			{
	
				font_id = get_ui_font ();
	
				set_ui_font (get_ui_object_font (obj));
	
				get_text_position (&x, &y, x1, y1, x2, y2, obj);
		
				ui_display_text (get_ui_object_text (obj), x, y);
	
				set_ui_font (font_id);
	
				redraw_flag = TRUE;
			}
	
			if (redraw_flag)
			{
		
				set_ui_repaint_area (x1 + ui_x_origin, y1 + ui_y_origin, x2 + ui_x_origin + 1, y2 + ui_y_origin + 1);
			}
	
			unlock_screen (active_screen);
		}

		set_active_screen (old_active_screen);

		area->redraw --;

		call_ui_object_draw_function (obj, NULL);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_area_ui_object_draw_functions (ui_object_types type)
{

	fn_draw_ui_object [type] = draw_area_ui_object;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
