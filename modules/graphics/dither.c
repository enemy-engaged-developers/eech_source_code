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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// Dithering pixel biasing values.
//

#define RIGHT_PIXEL_BIAS			6

#define BOTTOM_LEFT_PIXEL_BIAS	0

#define BOTTOM_PIXEL_BIAS			6

#define BOTTOM_RIGHT_PIXEL_BIAS	4

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DITHER_ERRORS
{

	int
		red,
		green,
		blue,
		padding;
};

typedef struct DITHER_ERRORS dither_errors;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void compute_dithered_rgb_image ( int width, int height, psd_rgb *image, rgb_packed *result_image )
{

	int
		x,
		y,
		memset_width;

	dither_errors
		*this_line_errors,
		*next_line_errors,
		*tmp_errors_ptr;

	ASSERT ( image );

	this_line_errors = safe_malloc ( width * sizeof ( dither_errors ) );

	next_line_errors = safe_malloc ( width * sizeof ( dither_errors ) );

	memset ( this_line_errors, 0, width * sizeof ( dither_errors ) );

	memset ( next_line_errors, 0, width * sizeof ( dither_errors ) );

	memset_width = min ( 3, width );

	for ( y = 0; y < height; y++ )
	{

		tmp_errors_ptr = next_line_errors;

		next_line_errors = this_line_errors;

		this_line_errors = tmp_errors_ptr;

		memset ( next_line_errors, 0, memset_width * sizeof ( dither_errors ) );

		for ( x = 0; x < width; x++ )
		{

			int
				r,
				g,
				b,
				error_red,
				error_green,
				error_blue;

			rgb_colour
				actual_colour;

			rgb_packed
				packed_colour;

			//
			// Get the rgb for this pixel
			//

			r = image->r;
			g = image->g;
			b = image->b;

			image++;

			//
			// Add in the propagated error from the line above
			//

			r += this_line_errors[x].red;
			g += this_line_errors[x].green;
			b += this_line_errors[x].blue;

			//
			// Bound the colours
			//

			r = bound ( r, 0, 255 );
			g = bound ( g, 0, 255 );
			b = bound ( b, 0, 255 );

			actual_colour.r = r;
			actual_colour.g = g;
			actual_colour.b = b;
			actual_colour.a = 255;

			packed_colour = get_rgb_packed_value ( actual_colour );

			actual_colour = get_rgb_colour_value ( packed_colour );

			*result_image++ = packed_colour;

			//
			// Figure the error at this pixel
			//

			error_red = r - ( int ) actual_colour.r;
			error_green = g - ( int ) actual_colour.g;
			error_blue = b - ( int ) actual_colour.b;

			//
			// Propagate the error
			//

			//
			// Next pixel gets 7/16
			//

			if ( x != ( width - 1 ) )
			{

				this_line_errors[x+1].red += ( ( error_red * RIGHT_PIXEL_BIAS ) / 16 );
				this_line_errors[x+1].green += ( ( error_green * RIGHT_PIXEL_BIAS ) / 16 );
				this_line_errors[x+1].blue += ( ( error_blue * RIGHT_PIXEL_BIAS ) / 16 );
			}

			if ( y != ( height - 1 ) )
			{

				if ( x != 0 )
				{

					//
					// Below left pixel gets 3/16 error
					//

					next_line_errors[x-1].red += ( ( error_red * BOTTOM_LEFT_PIXEL_BIAS ) / 16 );
					next_line_errors[x-1].green += ( ( error_green * BOTTOM_LEFT_PIXEL_BIAS ) / 16 );
					next_line_errors[x-1].blue += ( ( error_blue * BOTTOM_LEFT_PIXEL_BIAS ) / 16 );
				}

				//
				// Below pixel gets 5/16 error
				//

				next_line_errors[x].red += ( ( error_red * BOTTOM_PIXEL_BIAS ) / 16 );
				next_line_errors[x].green += ( ( error_green * BOTTOM_PIXEL_BIAS ) / 16 );
				next_line_errors[x].blue += ( ( error_blue * BOTTOM_PIXEL_BIAS ) / 16 );

				if ( x != ( width - 1 ) )
				{
	
					//
					// Below right pixel gets 1/16 error
					//
	
					next_line_errors[x+1].red = ( ( error_red * BOTTOM_RIGHT_PIXEL_BIAS ) / 16 );
					next_line_errors[x+1].green = ( ( error_green * BOTTOM_RIGHT_PIXEL_BIAS ) / 16 );
					next_line_errors[x+1].blue = ( ( error_blue * BOTTOM_RIGHT_PIXEL_BIAS ) / 16 );
				}
			}
		}
	}

	safe_free ( this_line_errors );

	safe_free ( next_line_errors );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void compute_dithered_rgba_image ( int width, int height, psd_rgba *image, rgb_packed *result_image )
{

	int
		x,
		y;

	dither_errors
		*this_line_errors,
		*next_line_errors,
		*tmp_errors_ptr;

	ASSERT ( image );

	this_line_errors = safe_malloc ( width * sizeof ( dither_errors ) );

	next_line_errors = safe_malloc ( width * sizeof ( dither_errors ) );

	memset ( this_line_errors, 0, width * sizeof ( dither_errors ) );

	memset ( next_line_errors, 0, width * sizeof ( dither_errors ) );

	for ( y = 0; y < height; y++ )
	{

		tmp_errors_ptr = next_line_errors;

		next_line_errors = this_line_errors;

		this_line_errors = tmp_errors_ptr;

		memset ( next_line_errors, 0, width * sizeof ( dither_errors ) );

		for ( x = 0; x < width; x++ )
		{

			int
				r,
				g,
				b,
				error_red,
				error_green,
				error_blue;

			rgb_colour
				actual_colour;

			rgb_packed
				packed_colour;

			//
			// Get the rgb for this pixel
			//

			r = image->r;
			g = image->g;
			b = image->b;

			image++;

			//
			// Add in the propagated error from the line above
			//

			r += this_line_errors[x].red;
			g += this_line_errors[x].green;
			b += this_line_errors[x].blue;

			//
			// Bound the colours
			//

			r = bound ( r, 0, 255 );
			g = bound ( g, 0, 255 );
			b = bound ( b, 0, 255 );

			actual_colour.r = r;
			actual_colour.g = g;
			actual_colour.b = b;
			actual_colour.a = 255;

			packed_colour = get_rgb_packed_value ( actual_colour );

			actual_colour = get_rgb_colour_value ( packed_colour );

			*result_image++ = packed_colour;

			//
			// Figure the error at this pixel
			//

			error_red = r - ( int ) actual_colour.r;
			error_green = g - ( int ) actual_colour.g;
			error_blue = b - ( int ) actual_colour.b;

			//
			// Propagate the error
			//

			//
			// Next pixel gets 7/16
			//

			if ( x != ( width - 1 ) )
			{

				this_line_errors[x+1].red = ( ( error_red * RIGHT_PIXEL_BIAS ) / 16 );
				this_line_errors[x+1].green = ( ( error_green * RIGHT_PIXEL_BIAS ) / 16 );
				this_line_errors[x+1].blue = ( ( error_blue * RIGHT_PIXEL_BIAS ) / 16 );
			}

			if ( y != ( height - 1 ) )
			{

				if ( x != 0 )
				{

					//
					// Below left pixel gets 3/16 error
					//

					next_line_errors[x-1].red += ( ( error_red * BOTTOM_LEFT_PIXEL_BIAS ) / 16 );
					next_line_errors[x-1].green += ( ( error_green * BOTTOM_LEFT_PIXEL_BIAS ) / 16 );
					next_line_errors[x-1].blue += ( ( error_blue * BOTTOM_LEFT_PIXEL_BIAS ) / 16 );
				}

				//
				// Below pixel gets 5/16 error
				//

				next_line_errors[x].red += ( ( error_red * BOTTOM_PIXEL_BIAS ) / 16 );
				next_line_errors[x].green += ( ( error_green * BOTTOM_PIXEL_BIAS ) / 16 );
				next_line_errors[x].blue += ( ( error_blue * BOTTOM_PIXEL_BIAS ) / 16 );

				if ( x != ( width - 1 ) )
				{
	
					//
					// Below right pixel gets 1/16 error
					//
	
					next_line_errors[x+1].red += ( ( error_red * BOTTOM_RIGHT_PIXEL_BIAS ) / 16 );
					next_line_errors[x+1].green += ( ( error_green * BOTTOM_RIGHT_PIXEL_BIAS ) / 16 );
					next_line_errors[x+1].blue += ( ( error_blue * BOTTOM_RIGHT_PIXEL_BIAS ) / 16 );
				}
			}
		}
	}

	safe_free ( this_line_errors );

	safe_free ( next_line_errors );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

