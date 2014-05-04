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

#include "misc.h"

#include "cmndline.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define SAVE_THUMBNAIL FALSE

struct TGA_IMAGE
{

	unsigned char
		id_field_length,
		colour_map_type,
		image_type_code,
		colour_map_entry_size,
		image_pixel_size,
		image_descriptor;

	unsigned short int
		colour_map_origin,
		colour_map_length,
		x_origin,
		y_origin,
		width,
		height;
};

typedef struct TGA_IMAGE tga_image;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PALETTEENTRY
	tga_image_palette [256];

unsigned char
	image [640 * 480 * 3];

int
	tga_image_origin_bottom_left;

void
	*tga_memory_mapped_image = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void *load_tga_file (const char *filename, short int *width, short int *height, int *bits_per_pixel)
{

	int
		size;

	FILE
		*file_ptr;

	void
		*image_data;

	tga_image
		image;

	file_ptr = safe_fopen (filename, "rb");

	// number of characters in identification field

	fread (&image.id_field_length, 1, 1, file_ptr);

	// colour map type

	fread (&image.colour_map_type, 1, 1, file_ptr);

	// image type code

	fread (&image.image_type_code, 1, 1, file_ptr);

	// colour map specification

	fread (&image.colour_map_origin, 2, 1, file_ptr);

	fread (&image.colour_map_length, 2, 1, file_ptr);

	fread (&image.colour_map_entry_size, 1, 1, file_ptr);

	// image specification

	fread (&image.x_origin, 2, 1, file_ptr);

	fread (&image.y_origin, 2, 1, file_ptr);

	fread (&image.width, 2, 1, file_ptr);

	fread (&image.height, 2, 1, file_ptr);

	*width = image.width;

	*height = image.height;

	fread (&image.image_pixel_size, 1, 1, file_ptr);

	*bits_per_pixel = image.image_pixel_size;

	fread (&image.image_descriptor, 1, 1, file_ptr);

	if (image.image_descriptor & 0x20)
	{

		tga_image_origin_bottom_left = FALSE;
	}
	else
	{

		tga_image_origin_bottom_left = TRUE;
	}

	// image identification field

	if (image.id_field_length)
	{

		fseek (file_ptr, image.id_field_length, SEEK_CUR);
	}

	// colour map data

	if (image.colour_map_type)
	{

		int
			count;

		for (count = 0; count < image.colour_map_length; count ++)
		{

			fread (&tga_image_palette [count].peBlue, 1, 1, file_ptr);
			fread (&tga_image_palette [count].peGreen, 1, 1, file_ptr);
			fread (&tga_image_palette [count].peRed, 1, 1, file_ptr);
		}
	}

	// image data field

	size = *width * *height * image.image_pixel_size / 8;

	image_data = safe_malloc (size);

	fread (image_data, 1, size, file_ptr);

	fclose (file_ptr);

	return image_data;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void *memory_map_tga_file (const char *filename, unsigned char **memory_mapped_file, short int *width, short int *height, int *bits_per_pixel)
{

	void
		*image_data;

	unsigned char
		*memory_ptr;

	tga_image
		image;

	unsigned char
		*ptr;

	memory_ptr = ( unsigned char * ) mopen ( filename );

	if ( !memory_ptr )
	{

		return ( NULL );
	}

	ptr = memory_ptr;

	// number of characters in identification field

	image.id_field_length = get_list_item ( ptr, unsigned char );

	// colour map type

	image.colour_map_type = get_list_item ( ptr, unsigned char );

	// image type code

	image.image_type_code = get_list_item ( ptr, unsigned char );

	// colour map specification

	image.colour_map_origin = get_list_item ( ptr, unsigned short int );

	image.colour_map_length = get_list_item ( ptr, unsigned short int );

	image.colour_map_entry_size = get_list_item ( ptr, unsigned char );

	// image specification

	image.x_origin = get_list_item ( ptr, unsigned short int );

	image.y_origin = get_list_item ( ptr, unsigned short int );

	image.width = get_list_item ( ptr, unsigned short int );

	image.height = get_list_item ( ptr, unsigned short int );

	image.image_pixel_size = get_list_item ( ptr, unsigned char );

	image.image_descriptor = get_list_item ( ptr, unsigned char );

	// image identification field

	if (image.id_field_length)
	{

		ptr += image.id_field_length;
	}

	// colour map data

	if (image.colour_map_type)
	{

		int
			count;

		for (count = 0; count < image.colour_map_length; count ++)
		{

			tga_image_palette[count].peBlue = get_list_item ( ptr, unsigned char );
			tga_image_palette[count].peGreen = get_list_item ( ptr, unsigned char );
			tga_image_palette[count].peRed = get_list_item ( ptr, unsigned char );
		}
	}

	*width = image.width;

	*height = image.height;

	*bits_per_pixel = image.image_pixel_size;

	if (image.image_descriptor & 0x20)
	{

		tga_image_origin_bottom_left = FALSE;
	}
	else
	{

		tga_image_origin_bottom_left = TRUE;
	}

	// image data field

	image_data = ptr;

	*memory_mapped_file = memory_ptr;

	return ( image_data );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void save_tga_screen (const char *filename)
{

	FILE
		*file_ptr;

	tga_image
		tga;

	rgb_colour
		colour;

	int
		width,
		height,
		loop_x,
		loop_y;

	unsigned char
		*image_ptr,
		*image;

	width = get_screen_width ( active_screen );

	height = get_screen_height ( active_screen );

	image = ( unsigned char * ) safe_malloc ( width * height * 3 );

	file_ptr = safe_fopen (filename, "wb");

	image_ptr = image;

	for (loop_y = height - 1; loop_y >= 0; loop_y --)
	{

		for (loop_x = 0; loop_x < width; loop_x ++)
		{

			get_pixel (loop_x, loop_y, &colour);

			*image_ptr ++ = colour.b;

			*image_ptr ++ = colour.g;

			*image_ptr ++ = colour.r;
		}
	}

	tga.id_field_length = 0;
	tga.colour_map_type = 0;
	tga.image_type_code = 2;

	tga.colour_map_origin = 0;
	tga.colour_map_length = 0;

	tga.colour_map_entry_size = 24;

	tga.x_origin = 0;
	tga.y_origin = 0;
	tga.width = width;
	tga.height = height;

	tga.image_pixel_size = 24;
	tga.image_descriptor = 0;

	// number of characters in identification field

	fwrite (&tga.id_field_length, 1, 1, file_ptr);

	// colour map type

	fwrite (&tga.colour_map_type, 1, 1, file_ptr);

	// image type code

	fwrite (&tga.image_type_code, 1, 1, file_ptr);

	// colour map specification

	fwrite (&tga.colour_map_origin, 2, 1, file_ptr);

	fwrite (&tga.colour_map_length, 2, 1, file_ptr);

	fwrite (&tga.colour_map_entry_size, 1, 1, file_ptr);

	// image specification

	fwrite (&tga.x_origin, 2, 1, file_ptr);

	fwrite (&tga.y_origin, 2, 1, file_ptr);

	fwrite (&tga.width, 2, 1, file_ptr);

	fwrite (&tga.height, 2, 1, file_ptr);

	fwrite (&tga.image_pixel_size, 1, 1, file_ptr);

	fwrite (&tga.image_descriptor, 1, 1, file_ptr);

	fwrite (image, width * 3, height, file_ptr);

	fclose (file_ptr);

	safe_free ( image );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void save_tga_screen_with_thumbnail ( const char *screen_filename, const char *thumbnail_filename )
{

	FILE
		*fp;

	tga_image
		tga;

	rgb_colour
		colour;

	int
		width,
		height,
		loop_x,
		loop_y,
		source_pitch;

	unsigned char
		*tga_image,
		*image_ptr;

	unsigned char
		*source_ptr,
		*source_line;

	source_ptr = get_screen_data ( video_screen );

	source_pitch = get_screen_pitch ( video_screen );

	width = get_screen_width ( video_screen );

	height = get_screen_height ( video_screen );

	tga_image = ( unsigned char * ) safe_malloc ( width * height * 3 );

	image_ptr = tga_image;

	source_line = source_ptr;

	for ( loop_y = 0; loop_y < height; loop_y++ )
	{
        // Casm 18JUN05 Fixed to allow both 16- and 32- bit screns to be saved
		unsigned char
			*source_line_data;
		int pixel_size;

		source_line_data = ( unsigned char * ) source_line;
		pixel_size = command_line_display_bpp == 16 ? 2 : 4;

		for ( loop_x = 0; loop_x < width; loop_x ++ )
		{
			colour = get_rgb_colour_value ( * ( unsigned long * ) source_line_data );

			source_line_data += pixel_size;

			*image_ptr ++ = colour.b;
			*image_ptr ++ = colour.g;
			*image_ptr ++ = colour.r;
		}

		source_line += source_pitch;
	}

	if ( ( fp = fopen ( screen_filename, "wb" ) ) == NULL )
	{

		debug_log ( "Unable to create file %s during save_tga_screen_with_thumbnail", screen_filename );
	}
	else
	{

		tga.id_field_length = 0;
		tga.colour_map_type = 0;
		tga.image_type_code = 2;
	
		tga.colour_map_origin = 0;
		tga.colour_map_length = 0;
	
		tga.colour_map_entry_size = 24;
	
		tga.x_origin = 0;
		tga.y_origin = 0;
		tga.width = width;
		tga.height = height;
	
		tga.image_pixel_size = 24;
		tga.image_descriptor = 0x20;
	
		// number of characters in identification field
	
		fwrite (&tga.id_field_length, 1, 1, fp);
	
		// colour map type
	
		fwrite (&tga.colour_map_type, 1, 1, fp);
	
		// image type code
	
		fwrite (&tga.image_type_code, 1, 1, fp);
	
		// colour map specification
	
		fwrite (&tga.colour_map_origin, 2, 1, fp);
	
		fwrite (&tga.colour_map_length, 2, 1, fp);
	
		fwrite (&tga.colour_map_entry_size, 1, 1, fp);
	
		// image specification
	
		fwrite (&tga.x_origin, 2, 1, fp);
	
		fwrite (&tga.y_origin, 2, 1, fp);
	
		fwrite (&width, 2, 1, fp);
	
		fwrite (&height, 2, 1, fp);
	
		fwrite (&tga.image_pixel_size, 1, 1, fp);
	
		fwrite (&tga.image_descriptor, 1, 1, fp);

		fwrite (tga_image, width * 3, height, fp);
	
		fclose (fp);
	}

	if ( ( width == 640 ) && ( height == 480 ) )
	{

		//
		// Now mess the data around to form a 160x120 image
		//
		
		source_ptr = tga_image;
	
		image_ptr = image;
	
		for ( loop_y = 0; loop_y < 120; loop_y ++ )
		{
	
			for ( loop_x = 0; loop_x < 160; loop_x ++ )
			{
	
				*image_ptr++ = *source_ptr++;
				*image_ptr++ = *source_ptr++;
				*image_ptr++ = *source_ptr++;
	
				source_ptr += ( 3 * 3 );
			}
	
			source_ptr += ( ( 640 * 3 ) * 3 );
		}
	
		//
		// Now, save the thumbnail as well.
		//
	
#if SAVE_THUMBNAIL
		
		if ( ( fp = fopen ( thumbnail_filename, "wb" ) ) == NULL )
		{
	
			debug_log ( "Unable to create thumbnail file %s during save_tga_screen_with_thumbnail", thumbnail_filename );
		}
		else
		{
		
			tga.id_field_length = 0;
			tga.colour_map_type = 0;
			tga.image_type_code = 2;
		
			tga.colour_map_origin = 0;
			tga.colour_map_length = 0;
		
			tga.colour_map_entry_size = 24;
		
			tga.x_origin = 0;
			tga.y_origin = 0;
			tga.width = 160;
			tga.height = 120;
		
			tga.image_pixel_size = 24;
			tga.image_descriptor = 0x20;
		
			// number of characters in identification field
		
			fwrite (&tga.id_field_length, 1, 1, fp);
		
			// colour map type
		
			fwrite (&tga.colour_map_type, 1, 1, fp);
		
			// image type code
		
			fwrite (&tga.image_type_code, 1, 1, fp);
		
			// colour map specification
		
			fwrite (&tga.colour_map_origin, 2, 1, fp);
		
			fwrite (&tga.colour_map_length, 2, 1, fp);
		
			fwrite (&tga.colour_map_entry_size, 1, 1, fp);
		
			// image specification
		
			fwrite (&tga.x_origin, 2, 1, fp);
		
			fwrite (&tga.y_origin, 2, 1, fp);
		
			fwrite (&tga.width, 2, 1, fp);
		
			fwrite (&tga.height, 2, 1, fp);
		
			fwrite (&tga.image_pixel_size, 1, 1, fp);
		
			fwrite (&tga.image_descriptor, 1, 1, fp);
		
			fwrite (&image, ( 160 * 120 * 3 ), 1, fp);
		
			fclose (fp);
		}
#endif
	}

	if ( tga_image )
	{

		safe_free ( tga_image );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void save_tga_image (const char *filename, int width, int height, const unsigned char *data)
{

	FILE
		*file_ptr;

	tga_image
		tga;

	int
		data_size;
/*
	rgb_colour
		colour;

	int
		loop_x,
		loop_y;
*/
//	unsigned char
//		*image_ptr;

	if ((file_ptr = fopen (filename, "wb")) == NULL)
	{
		debug_log ( "Unable to create file %s during save_tga_image:", filename );
	}

	data_size = ( width * height * 3 );

//	image_ptr = data;
/*
	for (loop_y = height; loop_y > 0; loop_y --)
	{

		for (loop_x = 0; loop_x < 640; loop_x ++)
		{

			get_pixel (loop_x, loop_y, &colour);

			*image_ptr ++ = colour.b;

			*image_ptr ++ = colour.g;

			*image_ptr ++ = colour.r;
		}
	}
*/
	tga.id_field_length = 0;
	tga.colour_map_type = 0;
	tga.image_type_code = 2;

	tga.colour_map_origin = 0;
	tga.colour_map_length = 0;

	tga.colour_map_entry_size = 24;

	tga.x_origin = 0;
	tga.y_origin = 0;
	tga.width = width;
	tga.height = height;

	tga.image_pixel_size = 24;
	tga.image_descriptor = 0;

	// number of characters in identification field

	fwrite (&tga.id_field_length, 1, 1, file_ptr);

	// colour map type

	fwrite (&tga.colour_map_type, 1, 1, file_ptr);

	// image type code

	fwrite (&tga.image_type_code, 1, 1, file_ptr);

	// colour map specification

	fwrite (&tga.colour_map_origin, 2, 1, file_ptr);

	fwrite (&tga.colour_map_length, 2, 1, file_ptr);

	fwrite (&tga.colour_map_entry_size, 1, 1, file_ptr);

	// image specification

	fwrite (&tga.x_origin, 2, 1, file_ptr);

	fwrite (&tga.y_origin, 2, 1, file_ptr);

	fwrite (&tga.width, 2, 1, file_ptr);

	fwrite (&tga.height, 2, 1, file_ptr);

	fwrite (&tga.image_pixel_size, 1, 1, file_ptr);

	fwrite (&tga.image_descriptor, 1, 1, file_ptr);

	fwrite (data, data_size, 1, file_ptr);

	fclose (file_ptr);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void save_tga_greyscale_image (const char *filename, int width, int height, const unsigned char *data)
{

	FILE
		*fp;

	tga_image
		tga;

	int
		count,
		y;

	if ((fp = fopen (filename, "wb")) == NULL)
	{

		debug_log ("Unable to create file %s during save_tga_greyscale_image", filename);
	}
	else
	{
	
		tga.id_field_length = 0;
		tga.colour_map_type = 1;
		tga.image_type_code = 1;
	
		tga.colour_map_origin = 0;
		tga.colour_map_length = 256;
	
		tga.colour_map_entry_size = 24;
	
		tga.x_origin = 0;
		tga.y_origin = 0;
		tga.width = width;
		tga.height = height;
	
		tga.image_pixel_size = 8;
		tga.image_descriptor = 0;
	
		// number of characters in identification field
	
		fwrite (&tga.id_field_length, 1, 1, fp);
	
		// colour map type
	
		fwrite (&tga.colour_map_type, 1, 1, fp);
	
		// image type code
	
		fwrite (&tga.image_type_code, 1, 1, fp);
	
		// colour map specification
	
		fwrite (&tga.colour_map_origin, 2, 1, fp);
	
		fwrite (&tga.colour_map_length, 2, 1, fp);
	
		fwrite (&tga.colour_map_entry_size, 1, 1, fp);
	
		// image specification
	
		fwrite (&tga.x_origin, 2, 1, fp);
	
		fwrite (&tga.y_origin, 2, 1, fp);
	
		fwrite (&tga.width, 2, 1, fp);
	
		fwrite (&tga.height, 2, 1, fp);
	
		fwrite (&tga.image_pixel_size, 1, 1, fp);
	
		fwrite (&tga.image_descriptor, 1, 1, fp);
	
		//
		// Palette
		//
	
		for (count = 0; count < 256; count ++)
		{
	
			unsigned char
				value;
	
			value = count;
	
			fwrite (&value, 1, 1, fp);
			fwrite (&value, 1, 1, fp);
			fwrite (&value, 1, 1, fp);
		}
	
		//
		// Image data
		//
	
		for (y = (height - 1); y >= 0; y --)
		{
	
			fwrite (&data [y * width], width, 1, fp);
		}
	
		fclose (fp);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
