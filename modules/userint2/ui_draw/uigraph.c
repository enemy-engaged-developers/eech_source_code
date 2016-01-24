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

#include "3d.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
void ui_draw_graphic (float x1, float y1, float x2, float y2, rgb_data *graphic)
{

	unsigned int
		graphic_x,
		graphic_y,
		*screen_ptr;

	rgb_colour
		*image_ptr;

	int
		int_y_size,
		screen_pitch,
		clip_x_size,
		loop_y;

	float
		x_start,
		y_start,
		new_x1,
		new_y1,
		new_x2,
		new_y2;

	int
		x_start_int,
		y_start_int,
		int_x1,
		int_y1,
		int_x2,
		int_y2;

	new_x1 = x1;

	new_y1 = y1;

	new_x2 = x2;

	new_y2 = y2;

	//debug_log ("UIGRAPH: graphic %f, %f -> %f, %f", x1, y1, x2, y2);

	// clip area to ui viewport

	ui_clip_area (&new_x1, &new_y1, &new_x2, &new_y2);

	x_start = new_x1 - x1;

	y_start = new_y1 - y1;

	// button coords should be in viewport coords,
	// so add ui_origin to convert into screen coords

	x1 += ui_x_origin;

	y1 += ui_y_origin;

	x2 += ui_x_origin;

	y2 += ui_y_origin;

	new_x1 += ui_x_origin;

	new_y1 += ui_y_origin;

	new_x2 += ui_x_origin;

	new_y2 += ui_y_origin;

	// check if possible to draw

	if ((new_x2 - new_x1 < 2) || (new_y2 - new_y1 <= 2))
	{

		return;
	}

	// convert variabless to ints to save crap conversion

	convert_float_to_int (new_x1, &int_x1);
	convert_float_to_int (new_y1, &int_y1);
	convert_float_to_int (new_x2, &int_x2);
	convert_float_to_int (new_y2, &int_y2);
	convert_float_to_int (x_start, &x_start_int);
	convert_float_to_int (y_start, &y_start_int);

	// draw graphic

	graphic_x = graphic->width;

	graphic_y = graphic->height;

	image_ptr = graphic->image + y_start_int * graphic_x + x_start_int;

	clip_x_size = int_x2 - int_x1 + 1;

	screen_ptr = get_screen_data (active_screen);

	screen_pitch = get_screen_pitch (active_screen);

	screen_ptr += screen_pitch * int_y1;

	screen_ptr += int_x1;

	// which ever is smaller, area or graphic

	int_y_size = min (int_y2 - int_y1, (int) graphic_y);

	clip_x_size *= sizeof (int);

	for (loop_y = 0; loop_y <= int_y_size; loop_y ++)
	{

		memcpy (screen_ptr, image_ptr, clip_x_size);

		screen_ptr += screen_pitch;

		image_ptr += graphic_x;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ui_draw_part_graphic (float x1, float y1, float x2, float y2, int start_x, int start_y, rgb_data *graphic)
{

	unsigned int
		graphic_x,
		graphic_y,
		*screen_ptr;

	rgb_colour
		*image_ptr;

	int
		int_y_size,
		screen_pitch,
		clip_x_size,
		loop_y;

	float
		x_start,
		y_start,
		new_x1,
		new_y1,
		new_x2,
		new_y2;

	int
		x_start_int,
		y_start_int,
		int_x1,
		int_y1,
		int_x2,
		int_y2;

	new_x1 = x1;

	new_y1 = y1;

	new_x2 = x2;

	new_y2 = y2;

	//debug_log ("UIGRAPH: part graphic %f, %f -> %f, %f", x1, y1, x2, y2);

	// clip area to ui viewport

	ui_clip_area (&new_x1, &new_y1, &new_x2, &new_y2);

	x_start = new_x1 - x1;

	y_start = new_y1 - y1;

	// button coords should be in viewport coords,
	// so add ui_origin to convert into screen coords

	x1 += ui_x_origin;

	y1 += ui_y_origin;

	x2 += ui_x_origin;

	y2 += ui_y_origin;

	new_x1 += ui_x_origin;

	new_y1 += ui_y_origin;

	new_x2 += ui_x_origin;

	new_y2 += ui_y_origin;

	// check if possible to draw

	if ((new_x2 - new_x1 < 2) || (new_y2 - new_y1 <= 2))
	{

		return;
	}

	// convert variabless to ints to save crap conversion

	convert_float_to_int (new_x1, &int_x1);
	convert_float_to_int (new_y1, &int_y1);
	convert_float_to_int (new_x2, &int_x2);
	convert_float_to_int (new_y2, &int_y2);
	convert_float_to_int (x_start, &x_start_int);
	convert_float_to_int (y_start, &y_start_int);

	// draw graphic

	graphic_x = graphic->width;

	graphic_y = graphic->height;

	image_ptr = graphic->image + (start_y + y_start_int) * graphic_x + x_start_int + start_x;

	clip_x_size = int_x2 - int_x1 + 1;

	screen_ptr = get_screen_data (active_screen);

	screen_pitch = get_screen_pitch (active_screen);

	screen_ptr += screen_pitch * int_y1;

	screen_ptr += int_x1;

	// which ever is smaller, area or graphic

	int_y_size = min (int_y2 - int_y1, (int) graphic_y);

	clip_x_size *= sizeof (int);

	for (loop_y = 0; loop_y <= int_y_size; loop_y ++)
	{

		memcpy (screen_ptr, image_ptr, clip_x_size);

		screen_ptr += screen_pitch;

		image_ptr += graphic_x;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ui_draw_memory_graphic (ui_object *obj, float x1, float y1, float x2, float y2, int memory_graphic_width, int memory_graphic_height, int memory_graphic_pitch, int masked)
{

	struct SCREEN
		*memory_graphic;

	unsigned int
		*data_ptr,
		*screen_ptr;

	int
		data_pitch,
		screen_pitch;

	memory_graphic = get_ui_object_memory_graphic (obj);

	ui_clip_area (&x1, &y1, &x2, &y2);

	x1 += ui_x_origin;

	y1 += ui_y_origin;

	x2 += ui_x_origin;

	y2 += ui_y_origin;

	screen_ptr = get_screen_data (active_screen);

	screen_pitch = get_screen_pitch (active_screen);

	data_ptr = get_screen_data (memory_graphic);

	data_pitch = get_screen_pitch (memory_graphic);

	if (masked)
	{

			ui_draw_masked_graphic (x1, y1, x2, y2,
											screen_pitch, memory_graphic_pitch,
											data_ptr, screen_ptr);
	}
	else
	{

			ui_draw_unscaled_memory_graphic (x1, y1, x2, y2, memory_graphic);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ui_draw_unscaled_memory_graphic (float x1, float y1, float x2, float y2, struct SCREEN *memory_graphic)
{

	unsigned int
		*graphic,
		graphic_pitch,
		graphic_x,
		graphic_y,
		*screen_ptr;

	int
		int_y_size,
		screen_pitch,
		clip_x_size,
		loop_y;

	float
		x_start,
		y_start,
		new_x1,
		new_y1,
		new_x2,
		new_y2;

	int
		x_start_int,
		y_start_int,
		int_x1,
		int_y1,
		int_x2,
		int_y2;

	graphic = get_screen_data (memory_graphic);

	graphic_pitch = get_screen_pitch (memory_graphic);

	graphic_x = get_screen_width (memory_graphic);

	graphic_y = get_screen_height (memory_graphic);

	new_x1 = x1;

	new_y1 = y1;

	new_x2 = x2;

	new_y2 = y2;

	// clip area to ui viewport

	ui_clip_area (&new_x1, &new_y1, &new_x2, &new_y2);

	x_start = new_x1 - x1;

	y_start = new_y1 - y1;

	// button coords should be in viewport coords,
	// so add ui_origin to convert into screen coords

	x1 += ui_x_origin;

	y1 += ui_y_origin;

	x2 += ui_x_origin;

	y2 += ui_y_origin;

	new_x1 += ui_x_origin;

	new_y1 += ui_y_origin;

	new_x2 += ui_x_origin;

	new_y2 += ui_y_origin;

	// check if possible to draw

	if ((new_x2 - new_x1 < 2) || (new_y2 - new_y1 <= 2))
	{

		return;
	}

	// convert variabless to ints to save crap conversion

	convert_float_to_int (new_x1, &int_x1);
	convert_float_to_int (new_y1, &int_y1);
	convert_float_to_int (new_x2, &int_x2);
	convert_float_to_int (new_y2, &int_y2);
	convert_float_to_int (x_start, &x_start_int);
	convert_float_to_int (y_start, &y_start_int);

	// draw graphic

	graphic += y_start_int * graphic_x + x_start_int;

	clip_x_size = int_x2 - int_x1;

	screen_ptr = get_screen_data (active_screen);

	screen_pitch = get_screen_pitch (active_screen);

	screen_pitch = screen_pitch >> 1;

	screen_ptr += screen_pitch * int_y1;

	screen_ptr += int_x1;

	// which ever is smaller, area or graphic

	int_y_size = min (int_y2 - int_y1, (int) graphic_y);

	for (loop_y = 0; loop_y < int_y_size; loop_y ++)
	{

		memcpy (screen_ptr, graphic, clip_x_size);

		screen_ptr += screen_pitch;

		graphic += graphic_pitch;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
void ui_draw_alpha_graphic (float x1, float y1, float x2, float y2, unsigned short int *graphic)
{

	unsigned short int
		graphic_x,
		graphic_y,
		*screen_ptr;

	int
		int_y_size,
		screen_pitch,
		clip_x_size,
		loop_y;

	float
		x_start,
		y_start,
		new_x1,
		new_y1,
		new_x2,
		new_y2;

	int
		x_start_int,
		y_start_int,
		int_x1,
		int_y1,
		int_x2,
		int_y2;

	new_x1 = x1;

	new_y1 = y1;

	new_x2 = x2;

	new_y2 = y2;

	// clip area to ui viewport

	ui_clip_area (&new_x1, &new_y1, &new_x2, &new_y2);

	x_start = new_x1 - x1;

	y_start = new_y1 - y1;

	// button coords should be in viewport coords,
	// so add ui_origin to convert into screen coords

	x1 += ui_x_origin;

	y1 += ui_y_origin;

	x2 += ui_x_origin;

	y2 += ui_y_origin;

	new_x1 += ui_x_origin;

	new_y1 += ui_y_origin;

	new_x2 += ui_x_origin;

	new_y2 += ui_y_origin;

	// check if possible to draw

	if ((new_x2 - new_x1 < 2) || (new_y2 - new_y1 <= 2))
	{

		return;
	}

	// convert variabless to ints to save crap conversion

	convert_float_to_int (new_x1, &int_x1);
	convert_float_to_int (new_y1, &int_y1);
	convert_float_to_int (new_x2, &int_x2);
	convert_float_to_int (new_y2, &int_y2);
	convert_float_to_int (x_start, &x_start_int);
	convert_float_to_int (y_start, &y_start_int);

	// draw graphic

	graphic_x = *graphic ++;

	graphic_y = *graphic ++;

	graphic += y_start_int * graphic_x + x_start_int;

	clip_x_size = int_x2 - int_x1 + 1;

	screen_ptr = (unsigned int *) get_screen_data (active_screen);

	screen_pitch = get_screen_pitch (active_screen);

	screen_ptr += screen_pitch * int_y1;

	screen_ptr += int_x1;

	// which ever is smaller, area or graphic

	int_y_size = min (int_y2 - int_y1, graphic_y);

	clip_x_size *= sizeof (int);

	for (loop_y = 0; loop_y <= int_y_size; loop_y ++)
	{

		memcpy (screen_ptr, graphic, clip_x_size);

		screen_ptr += screen_pitch;

		graphic += graphic_x;
	}
}
*/
void ui_draw_alpha_graphic (float x1, float y1, float x2, float y2, rgb_data *graphic)
{

	int
		int_x,
		int_y,
		int_width,
		int_height;

	int
		pitch,
		image_pitch,
		loop_height;

	unsigned int
		*screen_ptr;

	rgb_colour
		*this_image_ptr;


	//
	// store some variables in alternative types for speed
	//

	//debug_log ("UIGRAPH: alpha graphic %f, %f -> %f, %f", x1, y1, x2, y2);

	int_width = graphic->width;

	int_height = graphic->height;

	image_pitch = int_width;

	this_image_ptr = graphic->image;

	//
	//
	//

	pitch = get_screen_pitch (active_screen);

	screen_ptr = get_screen_data (active_screen);

	convert_float_to_int (y1 * pitch, &int_y);

	screen_ptr += int_y;

	convert_float_to_int (x1, &int_x);

	for (loop_height = int_height; loop_height > 0; loop_height --)
	{

		int
			loop_width;

		unsigned int
			*line_ptr;

		line_ptr = screen_ptr + int_x;

		for (loop_width = 0; loop_width < int_width; loop_width ++)
		{

			//
			// plot pixel according to 8bit alpha mask
			//

			if (this_image_ptr->alpha < 248)
			{

				if (this_image_ptr->alpha > 8)
				{

					rgb_colour
						this_colour,
						pixel_colour,
						result_colour;

					float
						dr,
						dg,
						db,
						alpha_factor;

					int
						ir,
						ig,
						ib;

					this_colour.colour = *line_ptr;
					pixel_colour = *this_image_ptr;

					alpha_factor = ((float) (this_image_ptr->alpha)) / 255.0;

					dr = this_colour.r - pixel_colour.r;
					dg = this_colour.g - pixel_colour.g;
					db = this_colour.b - pixel_colour.b;

					dr = ( dr * alpha_factor ) + FLOAT_FLOAT_FACTOR;
					dg = ( dg * alpha_factor ) + FLOAT_FLOAT_FACTOR;
					db = ( db * alpha_factor ) + FLOAT_FLOAT_FACTOR;

					ir = ( *( ( int * ) &dr ) - INTEGER_FLOAT_FACTOR );
					ig = ( *( ( int * ) &dg ) - INTEGER_FLOAT_FACTOR );
					ib = ( *( ( int * ) &db ) - INTEGER_FLOAT_FACTOR );

					result_colour.r = pixel_colour.r + ir;	//(dr * alpha_factor);
					result_colour.g = pixel_colour.g + ig;	//(dg * alpha_factor);
					result_colour.b = pixel_colour.b + ib;	//(db * alpha_factor);
					result_colour.a = 0;

					*line_ptr = result_colour.colour;
				}
				else
				{

					*line_ptr = this_image_ptr->colour;
				}
			}

			line_ptr ++;

			this_image_ptr ++;
		}

		screen_ptr += pitch;

		this_image_ptr += (image_pitch - int_width);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ui_draw_part_alpha_graphic (float x1, float y1, float x2, float y2, int start_x, int start_y, rgb_data *graphic)
{

	unsigned int
		graphic_x,
		graphic_y,
		*screen_ptr;

	rgb_colour
		*image_ptr;

	int
		int_y_size,
		screen_pitch,
		clip_x_size,
		loop_y;

	float
		x_start,
		y_start,
		new_x1,
		new_y1,
		new_x2,
		new_y2;

	int
		x_start_int,
		y_start_int,
		int_x1,
		int_y1,
		int_x2,
		int_y2;

	new_x1 = x1;

	new_y1 = y1;

	new_x2 = x2;

	new_y2 = y2;

	//debug_log ("UIGRAPH: part alpha graphic %f, %f -> %f, %f", x1, y1, x2, y2);

	// clip area to ui viewport

	ui_clip_area (&new_x1, &new_y1, &new_x2, &new_y2);

	x_start = new_x1 - x1;

	y_start = new_y1 - y1;

	// button coords should be in viewport coords,
	// so add ui_origin to convert into screen coords

	x1 += ui_x_origin;

	y1 += ui_y_origin;

	x2 += ui_x_origin;

	y2 += ui_y_origin;

	new_x1 += ui_x_origin;

	new_y1 += ui_y_origin;

	new_x2 += ui_x_origin;

	new_y2 += ui_y_origin;

	// check if possible to draw

	if ((new_x2 - new_x1 < 2) || (new_y2 - new_y1 <= 2))
	{

		return;
	}

	// convert variabless to ints to save crap conversion

	convert_float_to_int (new_x1, &int_x1);
	convert_float_to_int (new_y1, &int_y1);
	convert_float_to_int (new_x2, &int_x2);
	convert_float_to_int (new_y2, &int_y2);
	convert_float_to_int (x_start, &x_start_int);
	convert_float_to_int (y_start, &y_start_int);

	// draw graphic

	graphic_x = graphic->width;

	graphic_y = graphic->height;

	image_ptr = graphic->image + (start_y + y_start_int) * graphic_x + x_start_int + start_x;

	clip_x_size = int_x2 - int_x1 + 1;

	screen_ptr = get_screen_data (active_screen);

	screen_pitch = get_screen_pitch (active_screen);

	screen_ptr += screen_pitch * int_y1;

	screen_ptr += int_x1;

	// which ever is smaller, area or graphic

	int_y_size = min (int_y2 - int_y1, (int) graphic_y);

	clip_x_size *= sizeof (int);

	for (loop_y = 0; loop_y <= int_y_size; loop_y ++)
	{

		memcpy (screen_ptr, graphic, clip_x_size);

		screen_ptr += screen_pitch;

		graphic += graphic_x;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ui_draw_scaled_graphic (
										const int source_x1, const int source_y1, const int source_x2, const int source_y2, int source_pitch,
										const int destination_x1, const int destination_y1, const int destination_x2, const int destination_y2, int destination_pitch,
										unsigned int *source_ptr,
										unsigned int *destination_ptr )
{

	int
		source_x_error,
		source_x_inc_frac,
		source_x_inc_whole,
		source_x_counter = 0,
		source_y_counter = 0,
		source_y_inc,
		source_x_delta,
		source_y_delta,
		destination_x_delta,
		destination_y_delta;

	int
		destination_x_loop,
		destination_y_loop;

	unsigned int
		*destination_line_ptr,
		*source_line_ptr;

	source_x_delta = source_x2 - source_x1;
	source_y_delta = source_y2 - source_y1;

	destination_x_delta = destination_x2 - destination_x1;
	destination_y_delta = destination_y2 - destination_y1;

	source_x_inc_frac = ((source_x_delta << 16) / destination_x_delta) & 0xFFFF;
	source_x_inc_whole = ((source_x_delta << 16) / destination_x_delta) >> 16;

	source_y_inc = (source_y_delta << 16) / destination_y_delta;

	destination_ptr += (destination_x1 + (destination_y1 * destination_pitch));

	source_ptr += (source_x1 + (source_y1 * source_pitch));

	destination_line_ptr = destination_ptr;

	source_x_error = 0;

	for (destination_y_loop = 0; destination_y_loop < destination_y_delta; destination_y_loop ++)
	{

		source_line_ptr = source_ptr + ((source_y_counter >> 16) * source_pitch);

		source_x_counter = 0;

		for (destination_x_loop = 0; destination_x_loop < destination_x_delta; destination_x_loop ++)
		{

			*destination_line_ptr ++ = *source_line_ptr;

			source_line_ptr += source_x_inc_whole;

			source_x_error += source_x_inc_frac;

			if (source_x_error >= 1 << 16)
			{

				source_x_error -= 1 << 16;

				source_line_ptr ++;
			}
		}

		destination_line_ptr += destination_pitch - destination_x_loop;

		source_y_counter += source_y_inc;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ui_draw_scaled_masked_graphic (
										const int source_x1, const int source_y1, const int source_x2, const int source_y2, int source_pitch,
										const int destination_x1, const int destination_y1, const int destination_x2, const int destination_y2, int destination_pitch,
										unsigned int *source_ptr,
										unsigned int *destination_ptr )
{

	int
		source_x_error,
		source_x_inc_frac,
		source_x_inc_whole,
		source_x_counter = 0,
		source_y_counter = 0,
		source_y_inc,
		source_x_delta,
		source_y_delta,
		destination_x_delta,
		destination_y_delta;

	int
		destination_x_loop,
		destination_y_loop;

	unsigned int
		*destination_line_ptr,
		*source_line_ptr;

	source_x_delta = source_x2 - source_x1;
	source_y_delta = source_y2 - source_y1;

	destination_x_delta = destination_x2 - destination_x1;
	destination_y_delta = destination_y2 - destination_y1;

	source_x_inc_frac = ((source_x_delta << 16) / destination_x_delta) & 0xFFFF;
	source_x_inc_whole = ((source_x_delta << 16) / destination_x_delta) >> 16;

	source_y_inc = (source_y_delta << 16) / destination_y_delta;

	destination_ptr += (destination_x1 + (destination_y1 * destination_pitch));

	source_ptr += (source_x1 + (source_y1 * source_pitch));

	destination_line_ptr = destination_ptr;

	source_x_error = 0;

	for (destination_y_loop = 0; destination_y_loop < destination_y_delta; destination_y_loop ++)
	{

		source_line_ptr = source_ptr + ((source_y_counter >> 16) * source_pitch);

		source_x_counter = 0;

		for (destination_x_loop = 0; destination_x_loop < destination_x_delta; destination_x_loop ++)
		{

			if (*source_line_ptr)
			{

				*destination_line_ptr = *source_line_ptr;
			}

			destination_line_ptr ++;

			source_line_ptr += source_x_inc_whole;

			source_x_error += source_x_inc_frac;

			if (source_x_error >= 1 << 16)
			{

				source_x_error -= 1 << 16;

				source_line_ptr ++;
			}
		}

		destination_line_ptr += destination_pitch - destination_x_loop;

		source_y_counter += source_y_inc;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ui_draw_masked_graphic (
										const int destination_x1, const int destination_y1, const int destination_x2, const int destination_y2,
										int destination_pitch, int source_pitch,
										unsigned int *source_ptr,
										unsigned int *destination_ptr )
{

	int
		destination_x_loop,
		destination_y_loop;

	destination_ptr += (destination_x1 + (destination_y1 * destination_pitch));

	destination_pitch -= (destination_x2 - destination_x1);
	source_pitch -= (destination_x2 - destination_x1);

	for (destination_y_loop = destination_y1; destination_y_loop < destination_y2; destination_y_loop ++)
	{

		destination_x_loop = destination_x1;

		for ( ; destination_x_loop < destination_x2; destination_x_loop ++)
		{

			if (*source_ptr)
			{

				*destination_ptr = *source_ptr;
			}

			destination_ptr ++;

			source_ptr ++;
		}

		destination_ptr += destination_pitch;

		source_ptr += source_pitch;
	}
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ui_draw_texture_graphic (float x1, float y1, float x2, float y2, texture_graphic *graphic, real_colour colour)
{
#ifndef OGRE_EE

	vertex
		quad[4];

	int
		texture_index,
		texture_x,
		texture_y,
		texture_width_left,
		texture_height_left,
		iwidth,
		iheight;

	float
		start_x,
		start_y,
		end_x,
		end_y,
		width,
		height,
		dx,
		dy,
		x,
		y;

	real_colour
		specular;

	x1 = floor ( x1 );
	x2 = ceil ( x2 );
	y1 = floor ( y1 );
	y2 = ceil ( y2 );

	start_x = x1;
	start_y = y1;

	end_x = x2;
	end_y = y2;

	width = end_x - start_x;
	height = end_y - start_y;

	iwidth = ( int ) width;
	iheight = ( int ) height;

	if ( width > iwidth )
	{

		iwidth++;
	}

	if ( height > iheight )
	{

		iheight++;
	}

	dx = ( width / graphic->graphic_width ) * graphic->texture_width;
	dy = ( height / graphic->graphic_height ) * graphic->texture_height;

	texture_width_left = graphic->graphic_width;
	texture_height_left = graphic->graphic_height;

	if ( ( graphic->transparent ) || ( colour.alpha != 255 ) )
	{

		set_d3d_alpha_fog_zbuffer ( TRUE, FALSE, FALSE, FALSE );
	}
	else
	{

		set_d3d_alpha_fog_zbuffer ( FALSE, FALSE, FALSE, FALSE );
	}

	set_d3d_texture_wrapping ( 0, FALSE );


	set_d3d_texture_mip_filtering ( FALSE );

	if ( ( iwidth == graphic->graphic_width ) && ( iheight == graphic->graphic_height ) )
	{

		set_d3d_texture_mag_filtering ( FALSE );
		set_d3d_texture_min_filtering ( FALSE );
	}
	else
	{

		set_d3d_texture_mag_filtering ( TRUE );
		set_d3d_texture_min_filtering ( TRUE );
	}

//	set_d3d_zbuffer_comparison ( FALSE );

//	set_d3d_zbuffer_writing ( FALSE );

	specular.red = 0;
	specular.green = 0;
	specular.blue = 0;
	specular.alpha = 255;

	y = start_y;

	texture_index = 0;

	for ( texture_y = 0; texture_y < graphic->number_of_textures_high; texture_y++ )
	{

		x = start_x;

		for ( texture_x = 0; texture_x < graphic->number_of_textures_wide; texture_x++ )
		{

			int
				outcode,
				outcode2;

			set_d3d_flat_shaded_textured_renderstate ( graphic->textures[texture_index].texture );

			memset ( quad, 0, sizeof ( quad ) );

			quad[0].i = x;
			quad[0].j = y;
			quad[0].u = 0;
			quad[0].v = 0;

			quad[1].i = x + dx * graphic->textures[texture_index].umax;
			quad[1].j = y;
			quad[1].u = graphic->textures[texture_index].umax;
			quad[1].v = 0;

			quad[2].i = x + dx * graphic->textures[texture_index].umax;
			quad[2].j = y + dy * graphic->textures[texture_index].vmax;
			quad[2].u = graphic->textures[texture_index].umax;
			quad[2].v = graphic->textures[texture_index].vmax;

			quad[3].i = x;
			quad[3].j = y + dy * graphic->textures[texture_index].vmax;
			quad[3].u = 0;
			quad[3].v = graphic->textures[texture_index].vmax;

			quad[0].z = 10;
			quad[0].q = 0.1;
			quad[0].next_vertex = &quad[1];

			quad[1].z = 10;
			quad[1].q = 0.1;
			quad[1].next_vertex = &quad[2];

			quad[2].z = 10;
			quad[2].q = 0.1;
			quad[2].next_vertex = &quad[3];

			quad[3].z = 10;
			quad[3].q = 0.1;
			quad[3].next_vertex = NULL;

			quad[0].outcode = generate_outcode ( quad[0].i, quad[0].j );
			quad[1].outcode = generate_outcode ( quad[1].i, quad[1].j );
			quad[2].outcode = generate_outcode ( quad[2].i, quad[2].j );
			quad[3].outcode = generate_outcode ( quad[3].i, quad[3].j );

			outcode = quad[0].outcode;
			outcode2 = quad[0].outcode;
			outcode |= quad[1].outcode;
			outcode2 &= quad[1].outcode;
			outcode |= quad[2].outcode;
			outcode2 &= quad[2].outcode;
			outcode |= quad[3].outcode;
			outcode2 &= quad[3].outcode;

			if ( outcode2 == 0 )
			{

				if ( outcode )
				{

					vertex
						*poly;

					clip_3d_coord = 0;

					poly = clip_3d_polygon ( &quad[0], outcode );

					if ( poly )
					{

						draw_wbuffered_flat_shaded_textured_polygon ( poly, colour, specular );
					}
				}
				else
				{

					draw_wbuffered_flat_shaded_textured_polygon ( quad, colour, specular );
				}
			}

			texture_index++;

			x += dx;
		}

		y += dy;
	}

//	flush_triangle_primitives ();
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
