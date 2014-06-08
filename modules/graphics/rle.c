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


#if 0
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "graphics.h"

#include "misc.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Convert filename.TGA to filename.RLE
//
// The TGA file MUST include attribute data to act as a mask (32bpp).
//
//	RLE format:
//	{
//		for each occupied row:
//		{
//			unsigned short int x_offset (0xFFFF == end of file)
//			unsigned short int y_offset
//			{
//				for each run:
//				{
//					unsigned short int run_length (bytes)
//					unsigned short int packed_rgb * run_length
//					unsigned short int x_add (bytes) (0xFFFF == end of row)
//				}
//			}
//		}
//
//		0xFFFF (end of file)
//	}

void convert_tga_to_rle (const char *tga_filename, const char *rle_filename)
{
	FILE
		*rle_file_ptr;

	tga_rgba
		*tga_image,
		*tga_col,
		*run_start;

	rgb_colour
		rgb_col;

	rgb_packed
		packed_rgb_col;

	short int
		width,
		height;

	unsigned short int
		x,
		y,
		x_start,
		x_end,
		x_add,
		run_length,
		run_length_bytes,
		end_of_row = 0xFFFF,
		end_of_file = 0xFFFF;

	int
		first_run,
		mask,
		bits_per_pixel;

	unsigned char
		*rle_image,
		*destination_ptr;

	//
	// load TGA file
	//

	tga_image = ( tga_rgba * ) load_tga_file (tga_filename, &width, &height, &bits_per_pixel);

	if (bits_per_pixel != 32)
	{
		debug_fatal ( "%s must have 32 bits/pixel for convert_tga_to_rle", tga_filename);
	}

	//
	// Allocate a buffer memory area - must be big enough to hold the worst possible rle case
	//

	rle_image = ( unsigned char * ) safe_malloc ( width * height * sizeof ( rgb_packed ) * 2 );

	ASSERT ( rle_image );

	destination_ptr = rle_image;

	//
	// open RLE file
	//

	if ((rle_file_ptr = fopen (rle_filename, "wb")) == NULL)
	{
		debug_fatal ("Unable to open file %s during convert_tga_to_rle", rle_filename);
	}

	//
	// write RLE data
	//

	rgb_col.a = 255;

	for (y = 0; y < height; y++)
	{
		tga_col = tga_image + (width * (height - 1 - y));

		first_run = TRUE;

		run_start = NULL;

		x_start = 0;

		x_end = 0;

		for (x = 0; x <= width; x++)
		{
			if (x < width)
			{
				mask = tga_col->a;
			}
			else
			{
				// force end of run

				mask = TRUE;
			}

			if (!mask)
			{
				// check for start run

				if (!run_start)
				{
					run_start = tga_col;

					x_start = x;
				}
			}
			else
			{
				// check for end run

				if (run_start)
				{
					if (first_run)
					{

						quick_set_list_item ( destination_ptr, unsigned short int, x_start );
						quick_set_list_item ( destination_ptr, unsigned short int, y );

						first_run = FALSE;
					}
					else
					{
						x_add = (x_start - x_end - 1) * sizeof (packed_rgb_col);

						quick_set_list_item ( destination_ptr, unsigned short int, x_add );
					}

					x_end = x - 1;

					run_length = x - x_start;

					run_length_bytes = run_length * sizeof (packed_rgb_col);

					quick_set_list_item ( destination_ptr, unsigned short int, run_length_bytes );

					while (run_length--)
					{
						rgb_col.r = run_start->r;

						rgb_col.g = run_start->g;

						rgb_col.b = run_start->b;

						packed_rgb_col = get_packed_colour (rgb_col);

						quick_set_list_item ( destination_ptr, unsigned short int, packed_rgb_col );

						run_start++;
					}

					run_start = NULL;

					x_start = 0;
				}
			}

			tga_col++;
		}

		//
		// write end of row (if row occupied)
		//

		if (!first_run)
		{
			quick_set_list_item ( destination_ptr, unsigned short int, end_of_row );
		}
	}

	//
	// write end of file
	//

	quick_set_list_item ( destination_ptr, unsigned short int, end_of_file );

	//
	// Write the file out
	//

	fwrite ( rle_image, ( destination_ptr - rle_image ), 1, rle_file_ptr );

	//
	// clean up
	//


	fclose (rle_file_ptr);

	safe_free ( rle_image );

	safe_free (tga_image);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void convert_psd_to_rle ( const char *psd_filename, const char *rle_filename )
{

	FILE
		*rle_file_ptr;

	psd_rgba
		*psd_image,
		*psd_col,
		*run_start;

	rgb_colour
		rgb_col;

	rgb_packed
		packed_rgb_col;

	unsigned short int
		x,
		y,
		x_start,
		x_end,
		x_add,
		run_length,
		run_length_bytes,
		end_of_row = 0xFFFF,
		end_of_file = 0xFFFF;

	int
		width,
		height,
		first_run,
		mask,
		number_of_channels;

	unsigned char
		*rle_image,
		*destination_ptr;

	//
	// load PSD file
	//

	psd_image = ( psd_rgba * ) load_psd_file ( psd_filename, &width, &height, &number_of_channels );

	if ( number_of_channels != 4 )
	{

		debug_fatal ( "%s must have 4 channels/pixel for convert_psd_to_rle", psd_filename);
	}

	//
	// Allocate a buffer memory area - must be big enough to hold the worst possible rle case
	//

	rle_image = ( unsigned char * ) safe_malloc ( width * height * sizeof ( rgb_packed ) * 2 );

	destination_ptr = rle_image;

	//
	// open RLE file
	//

	if ( ( rle_file_ptr = fopen ( rle_filename, "wb" ) ) == NULL )
	{

		debug_fatal ( "Unable to open file %s during convert_psd_to_rle", rle_filename );
	}

	//
	// write RLE data
	//

	rgb_col.a = 255;

	for ( y = 0; y < height; y++ )
	{

		psd_col = psd_image + ( width * y );

		first_run = TRUE;

		run_start = NULL;

		x_start = 0;

		x_end = 0;

		for ( x = 0; x <= width; x++ )
		{
			if ( x < width )
			{

				mask = psd_col->a;
			}
			else
			{

				//
				// force end of run
				//

				mask = TRUE;
			}

			if ( !mask )
			{

				//
				// check for start run
				//

				if ( !run_start )
				{

					run_start = psd_col;

					x_start = x;
				}
			}
			else
			{

				//
				// check for end run
				//

				if ( run_start )
				{
					if ( first_run )
					{

						quick_set_list_item ( destination_ptr, unsigned short int, x_start );
						quick_set_list_item ( destination_ptr, unsigned short int, y );

						first_run = FALSE;
					}
					else
					{
						x_add = ( x_start - x_end - 1 ) * sizeof ( packed_rgb_col );

						quick_set_list_item ( destination_ptr, unsigned short int, x_add );
					}

					x_end = x - 1;

					run_length = x - x_start;

					run_length_bytes = run_length * sizeof ( packed_rgb_col );

					quick_set_list_item ( destination_ptr, unsigned short int, run_length_bytes );

					while ( run_length-- )
					{

						rgb_col.r = run_start->r;
						rgb_col.g = run_start->g;
						rgb_col.b = run_start->b;

						packed_rgb_col = get_general_packed_colour ( rgb_col );

						quick_set_list_item ( destination_ptr, unsigned short int, packed_rgb_col );

						run_start++;
					}

					run_start = NULL;

					x_start = 0;
				}
			}

			psd_col++;
		}

		//
		// write end of row (if row occupied)
		//

		if ( !first_run )
		{

			quick_set_list_item ( destination_ptr, unsigned short int, end_of_row );
		}
	}

	//
	// write end of file
	//

	quick_set_list_item ( destination_ptr, unsigned short int, end_of_file );

	//
	// Write the file out
	//

	fwrite ( rle_image, ( destination_ptr - rle_image ), 1, rle_file_ptr );

	//
	// clean up
	//

	fclose ( rle_file_ptr );

	safe_free ( rle_image );

	safe_free ( psd_image );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void convert_and_dither_psd_to_rle (const char *psd_filename, const char *rle_filename)
{

	FILE
		*rle_file_ptr;

	psd_rgba
		*psd_image,
		*psd_ptr;

	rgb_packed
		*dither_col,
		*run_start;

	rgb_colour
		rgb_col;

	rgb_packed
		*dither_image,
		packed_rgb_col;

	unsigned short int
		x,
		y,
		x_start,
		x_end,
		x_add,
		run_length,
		run_length_bytes,
		end_of_row = 0xFFFF,
		end_of_file = 0xFFFF;

	int
		width,
		height,
		first_run,
		mask,
		number_of_channels;

	unsigned char
		*rle_image,
		*destination_ptr;

	//
	// Load PSD file
	//

	psd_image = ( psd_rgba * ) load_psd_file ( psd_filename, &width, &height, &number_of_channels );

	if ( number_of_channels != 4 )
	{

		debug_fatal ( "%s must have 4 channels/pixel for convert_psd_to_rle", psd_filename );
	}

	//
	// Allocate a dither image
	//

	dither_image = ( rgb_packed * ) safe_malloc ( width * height * sizeof ( rgb_packed ) );

	//
	// Allocate a buffer memory area - must be big enough to hold the worst possible rle case
	//

	rle_image = ( unsigned char * ) safe_malloc ( width * height * sizeof ( rgb_packed ) * 2 );

	//
	// Dither the image
	//

	compute_dithered_rgba_image ( width, height, psd_image, ( rgb_packed * ) dither_image );

	//
	// Open RLE file
	//

	if ( ( rle_file_ptr = fopen ( rle_filename, "wb" ) ) == NULL )
	{

		debug_fatal ( "Unable to open file %s during convert_psd_to_rle", rle_filename );
	}

	//
	// Write RLE data
	//

	destination_ptr = rle_image;

	rgb_col.a = 255;

	for ( y = 0; y < height; y++ )
	{

		dither_col = dither_image + ( width * y );

		psd_ptr = psd_image + ( width * y );

		first_run = TRUE;

		run_start = NULL;

		x_start = 0;

		x_end = 0;

		for ( x = 0; x <= width; x++ )
		{
			if ( x < width )
			{

				mask = psd_ptr->a;
			}
			else
			{

				//
				// Force end of run
				//

				mask = TRUE;
			}

			if ( !mask )
			{

				//
				// Check for start run
				//

				if ( !run_start )
				{

					run_start = dither_col;

					x_start = x;
				}
			}
			else
			{

				//
				// check for end run
				//

				if ( run_start )
				{

					if ( first_run )
					{

						quick_set_list_item ( destination_ptr, unsigned short int, x_start );
						quick_set_list_item ( destination_ptr, unsigned short int, y );

						first_run = FALSE;
					}
					else
					{

						x_add = ( x_start - x_end - 1 ) * sizeof ( packed_rgb_col );

						quick_set_list_item ( destination_ptr, unsigned short int, x_add );
					}

					x_end = x - 1;

					run_length = x - x_start;

					run_length_bytes = run_length * sizeof ( packed_rgb_col );

					quick_set_list_item ( destination_ptr, unsigned short int, run_length_bytes );

					while ( run_length-- )
					{

						packed_rgb_col = *run_start;

						quick_set_list_item ( destination_ptr, unsigned short int, packed_rgb_col );

						run_start++;
					}

					run_start = NULL;

					x_start = 0;
				}
			}

			dither_col++;

			psd_ptr++;
		}

		//
		// write end of row (if row occupied)
		//

		if ( !first_run )
		{

			quick_set_list_item ( destination_ptr, unsigned short int, end_of_row );
		}
	}

	//
	// write end of file
	//

	quick_set_list_item ( destination_ptr, unsigned short int, end_of_file );

	//
	// Write the file out
	//

	fwrite ( rle_image, ( destination_ptr - rle_image ), 1, rle_file_ptr );

	//
	// clean up
	//

	fclose ( rle_file_ptr );

	safe_free ( rle_image );

	safe_free ( psd_image );

	safe_free ( dither_image );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void blit_rle_graphic (const unsigned char *rle_graphic, const int x, const int y)
{
	int
		screen_pitch,
		x_offset,
		y_offset,
		run_length,
		x_add;

	const unsigned char
		*rd;
	unsigned char
		*screen_data,
		*wt;

	ASSERT (rle_graphic);

	screen_pitch = get_screen_pitch (active_screen);

	screen_data = get_screen_data (active_screen);

	rd = rle_graphic;

	x_offset = get_list_item (rd, unsigned short int);

	while (x_offset != 0xFFFF)
	{
		y_offset = get_list_item (rd, unsigned short int);

		wt = screen_data + ((x + x_offset) * sizeof (rgb_packed)) + ((y + y_offset) * screen_pitch);

		x_add = 0;

		while (x_add != 0xFFFF)
		{
			wt += x_add;

			run_length = get_list_item (rd, unsigned short int);

			memcpy (wt, rd, run_length);

			rd += run_length;
			wt += run_length;

			x_add = get_list_item (rd, unsigned short int);
		}

		x_offset = get_list_item (rd, unsigned short int);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
