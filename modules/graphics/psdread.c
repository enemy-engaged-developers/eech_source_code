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

#include "global.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	number_of_psd_layers;

psd_layer_info
	psd_layers[MAX_PSD_LAYERS];

rgb_colour
	psd_palette[256];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_psd_layers ( void )
{

	int
		count;

	for ( count = 0; count < MAX_PSD_LAYERS; count++ )
	{

		psd_layers[count].data = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void * load_psd_file ( const char *filename, int *width_return, int *height_return, int *number_of_channels_return )
{

	FILE
		*fp;

	char
		id_buffer[256],
		*data,
		*ptr;

	int
		count,
		current_channel,
		width,
		height,
		number_of_channels,
		bits_per_channel,
		image_mode,
		compression,
		length,
		version;

	//
	// First, destroy any layers that may be allocated
	//

	for ( count = 0; count < MAX_PSD_LAYERS; count++ )
	{

		if ( psd_layers[count].data )
		{

			safe_free ( psd_layers[count].data );
			
			psd_layers[count].data = NULL;
		}
	}

	// Casm 21DEC07
	{
		char
			fn[1024];

		if (*psd_theme)
		{
			const char
				*ptr = strrchr(filename, '\\');

			if (ptr)
				sprintf(fn, "%.*s\\%s\\%s", ptr - filename, filename, psd_theme, ptr + 1);
			else
				sprintf(fn, "%s\\%s", psd_theme, filename);
			if (!file_exist(fn))
				strcpy(fn, filename);
		}
		else
			strcpy(fn, filename);
		fp = safe_fopen(fn, "rb");
	}

	//
	// Reset the number of layers
	//

	number_of_psd_layers = 0;

	//
	// Read in the signature of the file
	//

	id_buffer[4] = '\0';

	fread ( id_buffer, 4, 1, fp );

	if ( strcmp ( id_buffer, "8BPS" ) != 0 )
	{

		debug_fatal ( "File not a photoshop psd format: %s", filename );
	}

	//
	// Get the version of the format
	//

	version = iff_short_int_read ( fp );

	if ( version != 1 )
	{

		debug_fatal ( "File not correct photoshop version: %s", filename );
	}

	//
	// Skip the reserved bytes
	//

	fseek ( fp, 6, SEEK_CUR );

	//
	// Get the information about the image
	//

	number_of_channels = iff_short_int_read ( fp );

	height = iff_int_read ( fp );

	width = iff_int_read ( fp );

	bits_per_channel = iff_short_int_read ( fp );

	image_mode = iff_short_int_read ( fp );

	if ( bits_per_channel != 8 )
	{

		debug_fatal ( "Unsupported number of bits per channel: %s", filename );
	}

	switch ( image_mode )
	{

		case 1:
		case 2:
		case 3:
		{

			break;
		}

		default:
		{

			debug_fatal ( "Unsupported image mode: (%d) %s", image_mode, filename );
		}
	}

	length = iff_int_read ( fp );

	if ( image_mode == 2 )
	{

		//
		// Read in the palette
		//

		memset ( psd_palette, 0, sizeof ( psd_palette ) );

		for ( count = 0; count < 256; count++ )
		{

			fread ( &psd_palette[count].r, 1, 1, fp );
		}

		for ( count = 0; count < 256; count++ )
		{

			fread ( &psd_palette[count].g, 1, 1, fp );
		}

		for ( count = 0; count < 256; count++ )
		{

			fread ( &psd_palette[count].b, 1, 1, fp );
		}
	}
	else
	{
	
		//
		// Skip over the mode data
		//
	
		fseek ( fp, length, SEEK_CUR );
	}

	//
	// Skip over the image resources
	//

	length = iff_int_read ( fp );

	fseek ( fp, length, SEEK_CUR );

	//
	// Read in the layers
	//

	length = iff_int_read ( fp );

	if ( length )
	{

		int
			current_layer;

		//
		// Read in the layers information
		//

		length = iff_int_read ( fp );

		number_of_psd_layers = iff_short_int_read ( fp );

		if ( number_of_psd_layers < 0 )
		{

			number_of_psd_layers = -number_of_psd_layers;
		}

		for ( current_layer = 0; current_layer < number_of_psd_layers; current_layer++ )
		{

			int
				name_length,
				extra_data_length;

			psd_layers[current_layer].top = iff_int_read ( fp );

			psd_layers[current_layer].left = iff_int_read ( fp );

			psd_layers[current_layer].bottom = iff_int_read ( fp );

			psd_layers[current_layer].right = iff_int_read ( fp );

			psd_layers[current_layer].number_of_saved_channels = iff_short_int_read ( fp );

			for ( current_channel = 0; current_channel < psd_layers[current_layer].number_of_saved_channels; current_channel++ )
			{

				psd_layers[current_layer].channel_info[current_channel].id = iff_short_int_read ( fp );

				psd_layers[current_layer].channel_info[current_channel].length = iff_int_read ( fp );
			}

			//
			// Read in the id field or the layer
			//

			fread ( id_buffer, 4, 1, fp );
		
			if ( strcmp ( id_buffer, "8BIM" ) != 0 )
			{
		
				debug_fatal ( "File not a photoshop multi-layered psd format: %s", filename );
			}

			//
			// Read in the blend mode for the layer
			//

			fread ( id_buffer, 4, 1, fp );

			//
			// Skip over [ opacity, clipping, flags & filler bytes ]
			//

			fseek ( fp, 4, SEEK_CUR );

			//
			// Get length of extra data fields
			//

			extra_data_length = iff_int_read ( fp );

			//
			// Read in the layer mask data
			//

			length = iff_int_read ( fp );

			fseek ( fp, length, SEEK_CUR );

			extra_data_length -= ( 4 + length );

			//
			// Read in layer blending ranges
			//

			length = iff_int_read ( fp );

			fseek ( fp, length, SEEK_CUR );

			extra_data_length -= ( 4 + length );

			//
			// Read in the layer name ( pascal format: 1 byte = length of string, followed by string ) all formatted to multiple of 4 bytes
			//

			name_length = fgetc ( fp );

			if ( ( name_length + 1 ) % 4 )
			{

				length = name_length + ( 4 - ( name_length + 1 ) % 4 );
			}
			else
			{

				length = name_length;
			}

			fread ( psd_layers[current_layer].name, length, 1, fp );

			psd_layers[current_layer].name[length] = '\0';

			extra_data_length -= ( length + 1 );

			if ( extra_data_length )
			{

				fseek ( fp, extra_data_length, SEEK_CUR );
			}

			if (	( ( psd_layers[current_layer].bottom - psd_layers[current_layer].top ) != height ) ||
					( ( psd_layers[current_layer].right - psd_layers[current_layer].left ) != width ) )
/*
			if (	( psd_layers[current_layer].top != 0 ) ||
					( psd_layers[current_layer].left != 0 ) ||
					( psd_layers[current_layer].bottom != height ) ||
					( psd_layers[current_layer].right != width ) )
					*/
			{

				debug_fatal ( "Layer not same size as main image: ( %d, %d ) -> ( %d, %d ), ( %s ) - %s",
																					psd_layers[current_layer].top,
																					psd_layers[current_layer].left,
																					psd_layers[current_layer].bottom,
																					psd_layers[current_layer].right,
																					psd_layers[current_layer].name, filename );
			}

		}

		//
		// Read in each layers channel image data
		//

		for ( current_layer = 0; current_layer < number_of_psd_layers; current_layer++ )
		{

			int
				number_of_real_channels;

			//
			// Assess the number of "real" channels
			//

			number_of_real_channels = 0;

			for ( current_channel = 0; current_channel < psd_layers[current_layer].number_of_saved_channels; current_channel++ )
			{

				if ( psd_layers[current_layer].channel_info[current_channel].id >= 0 )
				{

					number_of_real_channels++;
				}
			}

			psd_layers[current_layer].number_of_channels = number_of_real_channels;

			//
			// Allocate enough memory for the whole image.
			//
		
			data = ( char * ) safe_malloc ( width * height * psd_layers[current_layer].number_of_channels );

			ASSERT ( data );
		
			//
			// Now read in the channels.
			//
		
			for ( current_channel = 0; current_channel < psd_layers[current_layer].number_of_saved_channels; current_channel++ )
			{
		
				int
					x,
					y,
					current_channel_data_length,
					current_channel_id;

				compression = iff_short_int_read ( fp );

				if ( compression )
				{

					//
					// Read in the number of bytes in this channel
					//

					current_channel_data_length = 0;

					for ( y = 0; y < height; y++ )
					{

						current_channel_data_length += iff_short_int_read ( fp );
					}
				}

				current_channel_id = psd_layers[current_layer].channel_info[current_channel].id;

				if ( current_channel_id < 0 )
				{

					//
					// Skip over the data for this channel
					//

					if ( compression )
					{
	
						fseek ( fp, current_channel_data_length, SEEK_CUR );
					}
					else
					{

						fseek ( fp, width * height, SEEK_CUR );
					}
				}
				else
				{
	
					//
					// There is no compression over rows.
					//
			
					for ( y = 0; y < height; y++ )
					{
			
						ptr = &data[ ( ( width * psd_layers[current_layer].number_of_channels * y ) + current_channel_id ) ];
			
						if ( compression )
						{
			
							signed char
								control;
			
							int
								number_of_pixels_in_run;
			
							int
								number_of_pixels_left;
			
							number_of_pixels_left = width;
			
							while ( number_of_pixels_left > 0 )
							{
			
								//
								// Read the source byte in
								//
			
								control = fgetc ( fp );
			
								number_of_pixels_in_run = control;
			
								if ( number_of_pixels_in_run >= 0 )
								{
			
									int
										count;
			
									//
									// Copy the next ( number_of_pixels_in_run + 1 ) bytes literally.
									//
			
									for ( count = 0; count <= number_of_pixels_in_run; count++ )
									{
			
										unsigned char
											pixel_data;
			
										pixel_data = fgetc ( fp );
			
										*ptr = pixel_data;
			
										ptr += psd_layers[current_layer].number_of_channels;
									}
			
									number_of_pixels_left -= ( number_of_pixels_in_run + 1 );
								}
								else if ( number_of_pixels_in_run != -128 )
								{
			
									int
										count;
			
									unsigned char
										pixel_data;
			
									//
									// Repeat the next byte ( ( -control ) + 1 ) times
									//
			
									number_of_pixels_in_run = -number_of_pixels_in_run;
			
									pixel_data = fgetc ( fp );
			
									for ( count = 0; count <= number_of_pixels_in_run; count++ )
									{
			
										*ptr = pixel_data;
			
										ptr += psd_layers[current_layer].number_of_channels;
									}
			
									number_of_pixels_left -= ( number_of_pixels_in_run + 1 );
								}
			
								if ( number_of_pixels_left < 0 )
								{
			
//									BREAKOUT ();
								}
							}
						}
						else
						{
			
							for ( x = 0; x < width; x++ )
							{
			
								unsigned char
									pixel_data;
			
								pixel_data = fgetc ( fp );
			
								*ptr = pixel_data;
			
								ptr += psd_layers[current_layer].number_of_channels;
							}
						}
					}
				}
			}

			psd_layers[current_layer].data = ( unsigned char * ) data;
		}

		{

			int
				file_position;


			file_position = ftell ( fp );

			if ( file_position & 1 )
			{

				fgetc ( fp );
			}
		}

		//
		// Skip over the global layers section
		//

		length = iff_int_read ( fp );

		fseek ( fp, length, SEEK_CUR );
	}

	compression = ftell ( fp );

	//
	// Read in the compression
	//

	compression = iff_short_int_read ( fp );

	//
	// Allocate enough memory for the whole image.
	//

	data = ( char * ) safe_malloc ( width * height * number_of_channels );

	ASSERT ( data );

	if ( compression )
	{
	
		//
		// Skip the table of byte counts
		//
	
		fseek ( fp, height * 2 * number_of_channels, SEEK_CUR );
	}

	//
	// Now read in the channels.
	//


	for ( current_channel = 0; current_channel < number_of_channels; current_channel++ )
	{

		int
			x,
			y;

		//
		// There is no compression over rows.
		//

		for ( y = 0; y < height; y++ )
		{

			ptr = &data[ ( ( width * number_of_channels * y ) + current_channel ) ];

			if ( compression )
			{

				signed char
					control;

				int
					number_of_pixels_in_run;

				int
					number_of_pixels_left;

				number_of_pixels_left = width;

				while ( number_of_pixels_left > 0 )
				{

					//
					// Read the source byte in
					//

					control = fgetc ( fp );

					number_of_pixels_in_run = control;

					if ( number_of_pixels_in_run >= 0 )
					{

						int
							count;

						//
						// Copy the next ( number_of_pixels_in_run + 1 ) bytes literally.
						//

						for ( count = 0; count <= number_of_pixels_in_run; count++ )
						{

							unsigned char
								pixel_data;

							pixel_data = fgetc ( fp );

							*ptr = pixel_data;

							ptr += number_of_channels;
						}

						number_of_pixels_left -= ( number_of_pixels_in_run + 1 );
					}
					else if ( number_of_pixels_in_run != -128 )
					{

						int
							count;

						unsigned char
							pixel_data;

						//
						// Repeat the next byte ( ( -control ) + 1 ) times
						//

						number_of_pixels_in_run = -number_of_pixels_in_run;

						pixel_data = fgetc ( fp );

						for ( count = 0; count <= number_of_pixels_in_run; count++ )
						{

							*ptr = pixel_data;

							ptr += number_of_channels;
						}

						number_of_pixels_left -= ( number_of_pixels_in_run + 1 );
					}

					if ( number_of_pixels_left < 0 )
					{

//						BREAKOUT ();
					}
				}
			}
			else
			{

				for ( x = 0; x < width; x++ )
				{

					unsigned char
						pixel_data;

					pixel_data = fgetc ( fp );

					*ptr = pixel_data;

					ptr += number_of_channels;
				}
			}
		}
	}

	//
	// Close the file
	//

	fclose ( fp );

	//
	// Set the return values.
	//

	*width_return = width;

	*height_return = height;

	*number_of_channels_return = number_of_channels;

	return ( data );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

