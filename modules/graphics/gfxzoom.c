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

struct ZOOMABLE_GRAPHIC
{

	int
		width,
		height,
		inverted,
		total;

	unsigned char
		*memory_mapped_file,
		*data;

	unsigned int
		*palette;
};

typedef struct ZOOMABLE_GRAPHIC zoomable_graphic;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

zoomable_graphic * load_zoomable_graphic ( char *filename )
{

	unsigned char
		*memory_mapped_file,
		*data;

	short int
		width,
		height;

	int
		bits;

	zoomable_graphic
		*graphic;

	data = memory_map_tga_file ( filename, &memory_mapped_file, &width, &height, &bits );

	if ( bits != 8 )
	{

		debug_log ( "Only 8bit paletted zoomable graphics are supported: %s", filename );

		mclose ( memory_mapped_file );

		return ( NULL );
	}
	else
	{

		int
			total,
			count;

		graphic = malloc_fast_mem ( sizeof ( zoomable_graphic ) );

		graphic->width = width;

		graphic->height = height;

		graphic->data = data;

		graphic->memory_mapped_file = memory_mapped_file;

		graphic->inverted = tga_image_origin_bottom_left;

		graphic->palette = safe_malloc ( 256 * sizeof ( unsigned int ) );

		for ( count = 0; count < 256; count++ )
		{

			rgb_colour
				colour;

			unsigned int
				palette_colour;

			colour.r = tga_image_palette[count].peRed;
			colour.g = tga_image_palette[count].peGreen;
			colour.b = tga_image_palette[count].peBlue;
			colour.a = 0;

			palette_colour = get_rgb_packed_value ( colour );
			palette_colour <<= 16;
			palette_colour |= get_rgb_packed_value ( colour );
			graphic->palette[count] = palette_colour;
		}

		//
		// Spin through the graphic - DO NOT REMOVE THE TOTAL - otherwise on optimised make all this will disappear.
		//

		total = 0;

		for ( count = 0; count < ( width * height ); count += 2048 )
		{

			total += data[count];
		}

		graphic->total = total;

		return ( graphic );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_zoomable_graphic_width ( zoomable_graphic *graphic )
{

	ASSERT ( graphic );

	return ( graphic->width );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_zoomable_graphic_height ( zoomable_graphic *graphic )
{

	ASSERT ( graphic );

	return ( graphic->height );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_zoomable_graphic ( zoomable_graphic *graphic, int x, int y, int screen_x_min, int screen_y_min, int screen_x_max, int screen_y_max, int zoom )
{

	int
		screen_x,
		screen_y,
		graphic_x,
		graphic_y,
		screen_width,
		screen_height,
		screen_pitch,
		zoom_x_counter,
		zoom_y_counter,
		graphic_y_increment;

	unsigned char
		*screen_data,
		*graphic_data_line;

	unsigned short int
		*screen_line_ptr;

	screen_width = get_screen_width ( active_screen );
	screen_height = get_screen_height ( active_screen );
	screen_pitch = get_screen_pitch ( active_screen );
	screen_data = get_screen_data ( active_screen );

	//
	// Check all the parameters
	//

	ASSERT ( graphic );
	ASSERT ( x >= 0 );
	ASSERT ( x < graphic->width );
	ASSERT ( y >= 0 );
	ASSERT ( y < graphic->height );

	ASSERT ( screen_y_min < screen_y_max );
	ASSERT ( screen_x_min < screen_x_max );

	ASSERT ( screen_y_min >= 0 );
	ASSERT ( screen_y_min < screen_height );
	ASSERT ( screen_x_min >= 0 );
	ASSERT ( screen_x_min < screen_width );

	ASSERT ( screen_y_max >= 0 );
	ASSERT ( screen_y_max < screen_height );
	ASSERT ( screen_x_max >= 0 );
	ASSERT ( screen_x_max < screen_width );

	ASSERT ( zoom <= 64 );
	ASSERT ( zoom >= -64 );
	ASSERT ( zoom != 0 );

	if ( graphic->inverted )
	{

		y = graphic->height - y - 1;

		graphic_y_increment = -1;
	}
	else
	{

		graphic_y_increment = 1;
	}

	if ( zoom > 0 )
	{

		int
			count;
	
		zoom_y_counter = zoom;
	
		graphic_y = y;
	
		for ( screen_y = screen_y_min; screen_y <= screen_y_max; screen_y++ )
		{

			unsigned char
				graphic_pixel_value;

			screen_line_ptr = ( unsigned short int * ) ( screen_data + ( screen_y * screen_pitch ) );
	
			screen_line_ptr += screen_x_min;

			graphic_data_line = &graphic->data[ ( graphic_y * graphic->width ) + x ];
	
			zoom_x_counter = zoom;

			for ( count = ( screen_x_max - screen_x_min ); count >= 0; count-- )
			{
	
				unsigned short int
					pixel_value;
	
				graphic_pixel_value = *graphic_data_line;
	
				pixel_value = graphic->palette[graphic_pixel_value];
	
				zoom_x_counter--;
	
				if ( zoom_x_counter == 0 )
				{
	
					graphic_data_line++;

					zoom_x_counter = zoom;
				}
	
				*screen_line_ptr++ = pixel_value;
			}

			zoom_y_counter--;
	
			if ( zoom_y_counter == 0 )
			{
	
				graphic_y += graphic_y_increment;
	
				zoom_y_counter = zoom;
			}
		}
	}
	else
	{

		zoom = -zoom;

		graphic_y = y;
	
		for ( screen_y = screen_y_min; screen_y <= screen_y_max; screen_y++ )
		{
	
			screen_line_ptr = ( unsigned short int * ) ( screen_data + ( screen_y * screen_pitch ) );
	
			screen_line_ptr += screen_x_min;
	
			graphic_data_line = &graphic->data[ ( graphic_y * graphic->width ) ];
	
			graphic_x = x;
	
			for ( screen_x = screen_x_min; screen_x <= screen_x_max; screen_x++ )
			{
	
				unsigned char
					graphic_pixel_value;
	
				unsigned short int
					screen_pixel_value;
	
				//
				// Plot the pixel
				//
	
				graphic_pixel_value = graphic_data_line[graphic_x];	//graphic->data[ ( ( graphic_y * graphic->width ) + graphic_x ) ];
	
				screen_pixel_value = graphic->palette[graphic_pixel_value];
	
				*screen_line_ptr++ = screen_pixel_value;

				graphic_x += zoom;
			}
	
			graphic_y += zoom * graphic_y_increment;

			graphic_y = bound ( graphic_y, 0, ( graphic->height - 1 ) );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void unload_zoomable_graphic ( zoomable_graphic *graphic )
{

	ASSERT ( graphic );

	if ( graphic->palette )
	{

		safe_free ( graphic->palette );

		graphic->palette = NULL;
	}

	if ( graphic->memory_mapped_file )
	if ( graphic->data )
	{

		mclose ( graphic->memory_mapped_file );

		graphic->memory_mapped_file = NULL;

		graphic->data = NULL;
	}

	free_mem ( graphic );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

