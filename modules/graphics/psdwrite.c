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



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "graphics.h"

#include "misc.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int run_length_encode_data ( const unsigned char *source_data, unsigned char *result, int length );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned short int
	*red_channel_line_lengths = nullptr,
	*green_channel_line_lengths = nullptr,
	*blue_channel_line_lengths = nullptr;

unsigned char
	*channel_compressed_data = nullptr,
	*channel_line_data = nullptr;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef OGRE_EE
void save_psd_screen ( const char *filename )
{

	write_psd_screen_file ( filename,
										get_screen_width ( video_screen ),
										get_screen_height ( video_screen ),
										get_screen_pitch ( video_screen ),
										get_screen_data ( video_screen ) );
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void write_psd_screen_file ( const char *filename, int width, int height, int pitch, const unsigned *data )
{

	FILE
		*fp = nullptr;

	char
		reserved_bytes[6];

	int
		count,
		length,
		compression_tables_offset,
		x,
		y;

	const unsigned int
		*graphic_data = nullptr,
		*source_line = nullptr;

	fp = safe_fopen ( filename, "wb" );

	//
	// Allocate the memory arrays.
	//

	red_channel_line_lengths = ( unsigned short * ) safe_malloc ( height * sizeof ( short int ) );

	green_channel_line_lengths = ( unsigned short * ) safe_malloc ( height * sizeof ( short int ) );

	blue_channel_line_lengths = ( unsigned short * ) safe_malloc ( height * sizeof ( short int ) );

	channel_compressed_data = ( unsigned char * ) safe_malloc ( width * 2 );

	channel_line_data = ( unsigned char * ) safe_malloc ( width );

	//
	// Write out the signature of the file
	//

	fwrite ( "8BPS", 4, 1, fp );

	//
	// Set the version of the format
	//

	iff_short_int_write ( 1, fp );

	//
	// Write the reserved bytes
	//

	memset ( reserved_bytes, 0, 6 );

	fwrite ( reserved_bytes, 6, 1, fp );

	//
	// Set the information about the image
	//

	//
	// Number of channels
	//

	iff_short_int_write ( 3, fp );

	//
	// Height, width
	//

	iff_int_write ( height, fp );

	iff_int_write ( width, fp );

	//
	// Bits per channel
	//

	iff_short_int_write ( 8, fp );

	//
	// Image mode
	//

	iff_short_int_write ( 3, fp );

	//
	// No colour mode data, so write length = 0
	//

	iff_int_write ( 0, fp );

	//
	// Write out no image resources, length = 0
	//

	iff_int_write ( 0, fp );

	//
	// Write out no layer/mask information, length = 0
	//

	iff_int_write ( 0, fp );

	//
	// Set the compression to RLE compressed ( 1 )
	//

	iff_short_int_write ( 1, fp );

	//
	// Skip over the compression tables for now - fill them in later
	//

	compression_tables_offset = ftell ( fp );

	fseek ( fp, ( height * 2 * 3 ), SEEK_CUR );

	//
	// Write out the red channel.
	//

	graphic_data = data;

	for ( y = 0; y < height; y++ )
	{

		source_line = graphic_data;

		for ( x = 0; x < width; x++ )
		{

			rgb_colour
				this_colour;

			this_colour.colour = source_line[x];

			channel_line_data[x] = this_colour.r;
		}

		length = run_length_encode_data ( channel_line_data, channel_compressed_data, width );

		red_channel_line_lengths[y] = length;

		fwrite ( channel_compressed_data, length, 1, fp );

		graphic_data += pitch;
	}

	//
	// Write out the green channel.
	//

	graphic_data = data;

	for ( y = 0; y < height; y++ )
	{

		source_line = graphic_data;

		for ( x = 0; x < width; x++ )
		{

			rgb_colour
				this_colour;

			this_colour.colour = source_line[x];

			channel_line_data[x] = this_colour.g;
		}

		length = run_length_encode_data ( channel_line_data, channel_compressed_data, width );

		green_channel_line_lengths[y] = length;

		fwrite ( channel_compressed_data, length, 1, fp );

		graphic_data += pitch;
	}

	//
	// Write out the blue channel.
	//

	graphic_data = data;

	for ( y = 0; y < height; y++ )
	{

		source_line = graphic_data;

		for ( x = 0; x < width; x++ )
		{

			rgb_colour
				this_colour;

			this_colour.colour = source_line[x];

			channel_line_data[x] = this_colour.b;
		}

		length = run_length_encode_data ( channel_line_data, channel_compressed_data, width );

		blue_channel_line_lengths[y] = length;

		fwrite ( channel_compressed_data, length, 1, fp );

		graphic_data += pitch;
	}

	//
	// Go back to the compression tables offset
	//

	fseek ( fp, compression_tables_offset, SEEK_SET );

	//
	// Write out the compression table for each channel
	//

	for ( count = 0; count < height; count++ )
	{

		iff_short_int_write ( red_channel_line_lengths[count], fp );
	}

	for ( count = 0; count < height; count++ )
	{

		iff_short_int_write ( green_channel_line_lengths[count], fp );
	}

	for ( count = 0; count < height; count++ )
	{

		iff_short_int_write ( blue_channel_line_lengths[count], fp );
	}

	//
	// Close the file
	//

	fclose ( fp );

	//
	// Free up the memory
	//

	safe_free ( red_channel_line_lengths );

	safe_free ( green_channel_line_lengths );

	safe_free ( blue_channel_line_lengths );

	safe_free ( channel_compressed_data );

	safe_free ( channel_line_data );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void write_psd_rgb_file ( const char *filename, int width, int height, int pitch, const unsigned char *data )
{

	FILE
		*fp = nullptr;

	char
		reserved_bytes[6];

	int
		count,
		length,
		compression_tables_offset,
		x,
		y;

	const unsigned char
		*graphic_data = nullptr,
		*source_line = nullptr;

	fp = safe_fopen ( filename, "wb" );

	//
	// Allocate the memory arrays.
	//

	red_channel_line_lengths = ( unsigned short * ) safe_malloc ( height * sizeof ( short int ) );

	green_channel_line_lengths = ( unsigned short * ) safe_malloc ( height * sizeof ( short int ) );

	blue_channel_line_lengths = ( unsigned short * ) safe_malloc ( height * sizeof ( short int ) );

	channel_compressed_data = ( unsigned char * ) safe_malloc ( width * 4 );

	channel_line_data = ( unsigned char * ) safe_malloc ( width );

	//
	// Write out the signature of the file
	//

	fwrite ( "8BPS", 4, 1, fp );

	//
	// Set the version of the format
	//

	iff_short_int_write ( 1, fp );

	//
	// Write the reserved bytes
	//

	memset ( reserved_bytes, 0, 6 );

	fwrite ( reserved_bytes, 6, 1, fp );

	//
	// Set the information about the image
	//

	//
	// Number of channels
	//

	iff_short_int_write ( 3, fp );

	//
	// Height, width
	//

	iff_int_write ( height, fp );

	iff_int_write ( width, fp );

	//
	// Bits per channel
	//

	iff_short_int_write ( 8, fp );

	//
	// Image mode
	//

	iff_short_int_write ( 3, fp );

	//
	// No colour mode data, so write length = 0
	//

	iff_int_write ( 0, fp );

	//
	// Write out no image resources, length = 0
	//

	iff_int_write ( 0, fp );

	//
	// Write out no layer/mask information, length = 0
	//

	iff_int_write ( 0, fp );

	//
	// Set the compression to RLE compressed ( 1 )
	//

	iff_short_int_write ( 1, fp );

	//
	// Skip over the compression tables for now - fill them in later
	//

	compression_tables_offset = ftell ( fp );

	fseek ( fp, ( height * 2 * 3 ), SEEK_CUR );

	//
	// Write out the red channel.
	//

	graphic_data = &data[0];

	for ( y = 0; y < height; y++ )
	{

		source_line = graphic_data;

		for ( x = 0; x < width; x++ )
		{

			channel_line_data[x] = *source_line;

			source_line += 3;
		}

		length = run_length_encode_data ( channel_line_data, channel_compressed_data, width );

		red_channel_line_lengths[y] = length;

		fwrite ( channel_compressed_data, length, 1, fp );

		graphic_data += pitch;
	}

	//
	// Write out the green channel.
	//

	graphic_data = &data[1];

	for ( y = 0; y < height; y++ )
	{

		source_line = graphic_data;

		for ( x = 0; x < width; x++ )
		{

			channel_line_data[x] = *source_line;

			source_line += 3;
		}

		length = run_length_encode_data ( channel_line_data, channel_compressed_data, width );

		green_channel_line_lengths[y] = length;

		fwrite ( channel_compressed_data, length, 1, fp );

		graphic_data += pitch;
	}

	//
	// Write out the blue channel.
	//

	graphic_data = &data[2];

	for ( y = 0; y < height; y++ )
	{

		source_line = graphic_data;

		for ( x = 0; x < width; x++ )
		{

			channel_line_data[x] = *source_line;

			source_line += 3;
		}

		length = run_length_encode_data ( channel_line_data, channel_compressed_data, width );

		blue_channel_line_lengths[y] = length;

		fwrite ( channel_compressed_data, length, 1, fp );

		graphic_data += pitch;
	}

	//
	// Go back to the compression tables offset
	//

	fseek ( fp, compression_tables_offset, SEEK_SET );

	//
	// Write out the compression table for each channel
	//

	for ( count = 0; count < height; count++ )
	{

		iff_short_int_write ( red_channel_line_lengths[count], fp );
	}

	for ( count = 0; count < height; count++ )
	{

		iff_short_int_write ( green_channel_line_lengths[count], fp );
	}

	for ( count = 0; count < height; count++ )
	{

		iff_short_int_write ( blue_channel_line_lengths[count], fp );
	}

	//
	// Close the file
	//

	fclose ( fp );

	//
	// Free up the memory
	//

	safe_free ( red_channel_line_lengths );

	safe_free ( green_channel_line_lengths );

	safe_free ( blue_channel_line_lengths );

	safe_free ( channel_compressed_data );

	safe_free ( channel_line_data );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void write_psd_greyscale ( const char *filename, int width, int height, int pitch, const unsigned char *data )
{

	FILE
		*fp = nullptr;

	char
		reserved_bytes[6];

	int
		count,
		length,
		compression_tables_offset,
		x,
		y;

	fp = safe_fopen ( filename, "wb" );

	//
	// Allocate the memory arrays.
	//

	red_channel_line_lengths = ( unsigned short * ) safe_malloc ( height * sizeof ( short int ) );

	channel_compressed_data = ( unsigned char * ) safe_malloc ( width * 8 );

	channel_line_data = ( unsigned char * ) safe_malloc ( width );

	//
	// Write out the signature of the file
	//

	fwrite ( "8BPS", 4, 1, fp );

	//
	// Set the version of the format
	//

	iff_short_int_write ( 1, fp );

	//
	// Write the reserved bytes
	//

	memset ( reserved_bytes, 0, 6 );

	fwrite ( reserved_bytes, 6, 1, fp );

	//
	// Set the information about the image
	//

	//
	// Number of channels
	//

	iff_short_int_write ( 1, fp );

	//
	// Height, width
	//

	iff_int_write ( height, fp );

	iff_int_write ( width, fp );

	//
	// Bits per channel
	//

	iff_short_int_write ( 8, fp );

	//
	// Image mode - greyscale
	//

	iff_short_int_write ( 1, fp );

	//
	// No colour mode data, so write length = 0
	//

	iff_int_write ( 0, fp );

	//
	// Write out no image resources, length = 0
	//

	iff_int_write ( 0, fp );

	//
	// Write out no layer/mask information, length = 0
	//

	iff_int_write ( 0, fp );

	//
	// Set the compression to RLE compressed ( 1 )
	//

	iff_short_int_write ( 1, fp );

	//
	// Skip over the compression table - seek back later & write it
	//

	compression_tables_offset = ftell ( fp );

	fseek ( fp, height * 2, SEEK_CUR );

	//
	// Now write out the grey channel.
	//

	for ( y = 0; y < height; y++ )
	{

		for ( x = 0; x < width; x++ )
		{

			channel_line_data[x] = data[x];
		}

		//
		// Now compress the line itself
		//

		length = run_length_encode_data ( channel_line_data, channel_compressed_data, width );

		red_channel_line_lengths[y] = length;

		fwrite ( channel_compressed_data, length, 1, fp );

		data += pitch;
	}

	//
	// Write out the compression table for each channel
	//

	fseek ( fp, compression_tables_offset, SEEK_SET );

	for ( count = 0; count < height; count++ )
	{

		iff_short_int_write ( red_channel_line_lengths[count], fp );
	}

	//
	// Close the file
	//

	fclose ( fp );

	//
	// Free up the memory
	//

	safe_free ( red_channel_line_lengths );

	safe_free ( channel_compressed_data );

	safe_free ( channel_line_data );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void write_psd_colourindex_and_alpha ( const char *filename, int width, int height, int pitch, const unsigned char *data )
{

	FILE
		*fp = nullptr;

	char
		reserved_bytes[6];

	int
		count,
		length,
		compression_tables_offset,
		x,
		y;

	const unsigned char
		*graphic_data = nullptr;

	fp = safe_fopen ( filename, "wb" );

	//
	// Allocate the memory arrays.
	//

	red_channel_line_lengths = ( unsigned short * ) safe_malloc ( height * sizeof ( short int ) );

	green_channel_line_lengths = ( unsigned short * ) safe_malloc ( height * sizeof ( short int ) );

	channel_compressed_data = ( unsigned char * ) safe_malloc ( width * 8 );

	channel_line_data = ( unsigned char * ) safe_malloc ( width );

	//
	// Write out the signature of the file
	//

	fwrite ( "8BPS", 4, 1, fp );

	//
	// Set the version of the format
	//

	iff_short_int_write ( 1, fp );

	//
	// Write the reserved bytes
	//

	memset ( reserved_bytes, 0, 6 );

	fwrite ( reserved_bytes, 6, 1, fp );

	//
	// Set the information about the image
	//

	//
	// Number of channels
	//

	iff_short_int_write ( 2, fp );

	//
	// Height, width
	//

	iff_int_write ( height, fp );

	iff_int_write ( width, fp );

	//
	// Bits per channel
	//

	iff_short_int_write ( 8, fp );

	//
	// Image mode - colourindex
	//

	iff_short_int_write ( 2, fp );

	//
	// Need to write colour palette
	//

	iff_int_write ( 768, fp );

	for ( count = 0; count < 256; count++ )
	{

		fwrite ( &psd_palette[count].r, 1, 1, fp );
	}

	for ( count = 0; count < 256; count++ )
	{

		fwrite ( &psd_palette[count].g, 1, 1, fp );
	}

	for ( count = 0; count < 256; count++ )
	{

		fwrite ( &psd_palette[count].b, 1, 1, fp );
	}

	//
	// Write out no image resources, length = 0
	//

	iff_int_write ( 0, fp );

	//
	// Write out no layer/mask information, length = 0
	//

	iff_int_write ( 0, fp );

	//
	// Set the compression to RLE compressed ( 1 )
	//

	iff_short_int_write ( 1, fp );

	//
	// Skip over the compression table - seek back later & write it
	//

	compression_tables_offset = ftell ( fp );

	fseek ( fp, ( height * 2 * 2 ), SEEK_CUR );

	//
	// Write out the paletted channel.
	//

	graphic_data = data;

	for ( y = 0; y < height; y++ )
	{

		const unsigned char
			*source_line = nullptr;

		source_line = graphic_data;

		for ( x = 0; x < width; x++ )
		{

			channel_line_data[x] = *source_line;

			source_line += 2;
		}

		//
		// Now compress the line itself
		//

		length = run_length_encode_data ( channel_line_data, channel_compressed_data, width );

		red_channel_line_lengths[y] = length;

		fwrite ( channel_compressed_data, length, 1, fp );

		graphic_data += pitch;
	}

	//
	// Write out the alpha channel.
	//

	graphic_data = &data[1];

	for ( y = 0; y < height; y++ )
	{

		const unsigned char
			*source_line = nullptr;

		source_line = graphic_data;

		for ( x = 0; x < width; x++ )
		{

			channel_line_data[x] = *source_line;

			source_line += 2;
		}

		//
		// Now compress the line itself
		//

		length = run_length_encode_data ( channel_line_data, channel_compressed_data, width );

		green_channel_line_lengths[y] = length;

		fwrite ( channel_compressed_data, length, 1, fp );

		graphic_data += pitch;
	}

	//
	// Write out the compression table for each channel
	//

	fseek ( fp, compression_tables_offset, SEEK_SET );

	for ( count = 0; count < height; count++ )
	{

		iff_short_int_write ( red_channel_line_lengths[count], fp );
	}

	for ( count = 0; count < height; count++ )
	{

		iff_short_int_write ( green_channel_line_lengths[count], fp );
	}

	//
	// Close the file
	//

	fclose ( fp );

	//
	// Free up the memory
	//

	safe_free ( red_channel_line_lengths );

	safe_free ( green_channel_line_lengths );

	safe_free ( channel_compressed_data );

	safe_free ( channel_line_data );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int run_length_encode_data ( const unsigned char *source_data, unsigned char *result, int length )
{

	int
		data_written;

	data_written = 0;

	while ( length )
	{

		if ( length == 1 )
		{

			//
			// Last pixel - just write it out.
			//

			*result++ = 0;
			*result++ = ( ( const char * ) source_data )[0];

			length = 0;
			data_written += 2;
		}
		else if ( length == 2 )
		{

			//
			// Last two pixels - test together
			//

			if ( source_data[0] == source_data[1] )
			{

				*result++ = -1;										// Duplicate next byte twice
				*result++ = ( ( const char * ) source_data )[0];

				length = 0;
				data_written += 2;
			}
			else
			{

				*result++ = 1;											// Copy the next 2 bytes literally
				*result++ = ( ( const char * ) source_data )[0];
				*result++ = ( ( const char * ) source_data )[1];

				length = 0;
				data_written += 3;
			}
		}
		else
		{

			//
			// There are 3 or more pixels left
			//

			if ( source_data[0] == source_data[1] )
			{

				int
					different,
					run_length;

				//
				// Write out a run of the same pixel value
				//

				different = FALSE;

				run_length = 2;

				while ( ( !different ) && ( run_length < length ) && ( run_length < 128 ) )
				{

					if ( source_data[run_length] == source_data[0] )
					{

						run_length++;
					}
					else
					{

						different = TRUE;
					}
				}

				*result++ = -( run_length - 1 );
				*result++ = ( ( const char * ) source_data )[0];

				source_data += run_length;
				data_written += 2;

				length -= run_length;
			}
			else
			{

				int
					count,
					different,
					run_length;

				//
				// Write out a run of different pixel values
				//

				different = TRUE;

				run_length = 2;

				while ( ( different ) && ( run_length < length ) && ( run_length < 128 ) )
				{

					if ( source_data[run_length] != source_data[run_length-1] )
					{

						run_length++;
					}
					else
					{

						//
						// If the next byte is different, don't do it!
						//

						if ( run_length < ( length - 1 ) )
						{

							if ( source_data[run_length+1] == source_data[run_length] )
							{

								different = FALSE;

								run_length -= 1;
							}
							else
							{

								run_length++;
							}
						}
						else
						{

							different = FALSE;

							run_length -= 1;
						}
					}
				}

				*result++ = run_length - 1;

				for ( count = 0; count < run_length; count++ )
				{

					*result++ = ( ( const char * ) source_data )[count];
				}

				source_data += run_length;
				data_written += run_length + 1;

				length -= run_length;
			}
		}
	}

	return ( data_written );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
