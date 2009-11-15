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

#include "graphics.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// mono-sprite data format:-
//
// char width
// char height
// char x_offset
// char y_offset
// char pixel * width * height (pixel either 0 or 1)

void draw_mono_sprite (const char *sprite_ptr, const float x, const float y, const rgb_colour colour)
{

	if ( active_screen->pixel_length <= 16 )
	{
		int
			width,
			height,
			x_offset,
			y_offset,
			x1,
			y1,
			x2,
			y2,
			x_count,
			y_count,
			x_adjust,
			y_adjust,
			screen_pitch,
			screen_ptr_add_on,
			sprite_ptr_add_on;
	
		unsigned char
			*screen_data,
			*screen_ptr;
	
		unsigned short int
			col;
	
		col = get_packed_colour (colour);
	
		width = *sprite_ptr++;
		height = *sprite_ptr++;
	
		x_offset = *(signed char *)sprite_ptr++;
		y_offset = *(signed char *)sprite_ptr++;
	
		convert_float_to_int (floor (x), &x1);
		convert_float_to_int (floor (y), &y1);
	
		x1 += x_offset;
		y1 += y_offset;
	
		x2 = x1 + width - 1;
		y2 = y1 + height - 1;
	
		if
		(
			(x1 >= active_int_viewport.x_min) && (y1 >= active_int_viewport.y_min) &&
			(x2 <= active_int_viewport.x_max) && (y2 <= active_int_viewport.y_max)
		)
		{
			//
			// draw unclipped sprite
			//
	
			screen_pitch = get_screen_pitch (active_screen);
	
			screen_data = get_screen_data (active_screen);
	
			screen_ptr = screen_data + (x1 * sizeof (rgb_packed)) + (y1 * screen_pitch);
	
			screen_ptr_add_on = screen_pitch - (width * sizeof (rgb_packed));
	
			for (y_count = height; y_count > 0 ; y_count--)
			{
				for (x_count = width; x_count > 0 ; x_count--)
				{
					if (*sprite_ptr++)
					{
						*(rgb_packed *)screen_ptr = col;
					}
	
					screen_ptr += sizeof (rgb_packed);
				}
	
				screen_ptr += screen_ptr_add_on;
			}
		}
		else
		{
			//
			// draw clipped sprite (if visible)
			//
	
			if
			(
				(x1 <= active_int_viewport.x_max) && (y1 <= active_int_viewport.y_max) &&
				(x2 >= active_int_viewport.x_min) && (y2 >= active_int_viewport.y_min)
			)
			{
				screen_pitch = get_screen_pitch (active_screen);
	
				screen_data = get_screen_data (active_screen);
	
				screen_ptr_add_on = screen_pitch - (width * sizeof (rgb_packed));
	
				sprite_ptr_add_on = 0;
	
				//
				// clip above
				//
	
				if (y1 < active_int_viewport.y_min)
				{
					y_adjust = active_int_viewport.y_min - y1;
	
					y1 += y_adjust;
	
					height -= y_adjust;
	
					sprite_ptr += (y_adjust * width);
				}
	
				//
				// clip below
				//
	
				if (y2 > active_int_viewport.y_max)
				{
					y_adjust = y2 - active_int_viewport.y_max;
	
					height -= y_adjust;
				}
	
				//
				// clip left
				//
	
				if (x1 < active_int_viewport.x_min)
				{
					x_adjust = active_int_viewport.x_min - x1;
	
					x1 += x_adjust;
	
					width -= x_adjust;
	
					sprite_ptr += x_adjust;
	
					sprite_ptr_add_on += x_adjust;
				}
	
				//
				// clip right
				//
	
				if (x2 > active_int_viewport.x_max)
				{
					x_adjust = x2 - active_int_viewport.x_max;
	
					width -= x_adjust;
	
					sprite_ptr_add_on += x_adjust;
				}
	
				screen_ptr = screen_data + (x1 * sizeof (rgb_packed)) + (y1 * screen_pitch);
	
				screen_ptr_add_on = screen_pitch - (width * sizeof (rgb_packed));
	
				for (y_count = height; y_count > 0 ; y_count--)
				{
					for (x_count = width; x_count > 0 ; x_count--)
					{
						if (*sprite_ptr++)
						{
							*(rgb_packed *)screen_ptr = col;
						}
	
						screen_ptr += sizeof (rgb_packed);
					}
	
					screen_ptr += screen_ptr_add_on;
	
					sprite_ptr += sprite_ptr_add_on;
				}
			}
		}
	}
	else
	{

		int
			width,
			height,
			x_offset,
			y_offset,
			x1,
			y1,
			x2,
			y2,
			x_count,
			y_count,
			x_adjust,
			y_adjust,
			screen_pitch,
			screen_ptr_add_on,
			sprite_ptr_add_on;
	
		unsigned char
			*screen_data,
			*screen_ptr;
	
		unsigned int
			col;
	
		col = colour.colour;
	
		width = *sprite_ptr++;
		height = *sprite_ptr++;
	
		x_offset = *(signed char *)sprite_ptr++;
		y_offset = *(signed char *)sprite_ptr++;
	
		convert_float_to_int (floor (x), &x1);
		convert_float_to_int (floor (y), &y1);
	
		x1 += x_offset;
		y1 += y_offset;
	
		x2 = x1 + width - 1;
		y2 = y1 + height - 1;
	
		if
		(
			(x1 >= active_int_viewport.x_min) && (y1 >= active_int_viewport.y_min) &&
			(x2 <= active_int_viewport.x_max) && (y2 <= active_int_viewport.y_max)
		)
		{
			//
			// draw unclipped sprite
			//
	
			screen_pitch = get_screen_pitch (active_screen);
	
			screen_data = get_screen_data (active_screen);
	
			screen_ptr = screen_data + (x1 * sizeof (unsigned int)) + (y1 * screen_pitch);
	
			screen_ptr_add_on = screen_pitch - (width * sizeof (unsigned int));
	
			for (y_count = height; y_count > 0 ; y_count--)
			{
				for (x_count = width; x_count > 0 ; x_count--)
				{
					if (*sprite_ptr++)
					{
						*(unsigned int *)screen_ptr = col;
					}
	
					screen_ptr += sizeof (unsigned int);
				}
	
				screen_ptr += screen_ptr_add_on;
			}
		}
		else
		{
			//
			// draw clipped sprite (if visible)
			//
	
			if
			(
				(x1 <= active_int_viewport.x_max) && (y1 <= active_int_viewport.y_max) &&
				(x2 >= active_int_viewport.x_min) && (y2 >= active_int_viewport.y_min)
			)
			{
				screen_pitch = get_screen_pitch (active_screen);
	
				screen_data = get_screen_data (active_screen);
	
				screen_ptr_add_on = screen_pitch - (width * sizeof (unsigned int));
	
				sprite_ptr_add_on = 0;
	
				//
				// clip above
				//
	
				if (y1 < active_int_viewport.y_min)
				{
					y_adjust = active_int_viewport.y_min - y1;
	
					y1 += y_adjust;
	
					height -= y_adjust;
	
					sprite_ptr += (y_adjust * width);
				}
	
				//
				// clip below
				//
	
				if (y2 > active_int_viewport.y_max)
				{
					y_adjust = y2 - active_int_viewport.y_max;
	
					height -= y_adjust;
				}
	
				//
				// clip left
				//
	
				if (x1 < active_int_viewport.x_min)
				{
					x_adjust = active_int_viewport.x_min - x1;
	
					x1 += x_adjust;
	
					width -= x_adjust;
	
					sprite_ptr += x_adjust;
	
					sprite_ptr_add_on += x_adjust;
				}
	
				//
				// clip right
				//
	
				if (x2 > active_int_viewport.x_max)
				{
					x_adjust = x2 - active_int_viewport.x_max;
	
					width -= x_adjust;
	
					sprite_ptr_add_on += x_adjust;
				}
	
				screen_ptr = screen_data + (x1 * sizeof (unsigned int)) + (y1 * screen_pitch);
	
				screen_ptr_add_on = screen_pitch - (width * sizeof (unsigned int));
	
				for (y_count = height; y_count > 0 ; y_count--)
				{
					for (x_count = width; x_count > 0 ; x_count--)
					{
						if (*sprite_ptr++)
						{
							*(unsigned int *)screen_ptr = col;
						}
	
						screen_ptr += sizeof (unsigned int);
					}
	
					screen_ptr += screen_ptr_add_on;
	
					sprite_ptr += sprite_ptr_add_on;
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
