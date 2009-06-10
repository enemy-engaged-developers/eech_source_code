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

int
	texture_colour_red_mask,
	texture_colour_green_mask,
	texture_colour_blue_mask,
	texture_colour_red_shift,
	texture_colour_green_shift,
	texture_colour_blue_shift,

	texture_colour_nopalette_red_mask,
	texture_colour_nopalette_green_mask,
	texture_colour_nopalette_blue_mask,
	texture_colour_nopalette_red_shift,
	texture_colour_nopalette_green_shift,
	texture_colour_nopalette_blue_shift,

	texture_single_alpha_red_mask,
	texture_single_alpha_green_mask,
	texture_single_alpha_blue_mask,
	texture_single_alpha_alpha_mask,
	texture_single_alpha_red_shift,
	texture_single_alpha_green_shift,
	texture_single_alpha_blue_shift,
	texture_single_alpha_alpha_shift,

	texture_multiple_alpha_red_mask,
	texture_multiple_alpha_green_mask,
	texture_multiple_alpha_blue_mask,
	texture_multiple_alpha_alpha_mask,
	texture_multiple_alpha_red_shift,
	texture_multiple_alpha_green_shift,
	texture_multiple_alpha_blue_shift,
	texture_multiple_alpha_alpha_shift,

	colour_texture_pixel_width,
	colour_nopalette_texture_pixel_width,
	single_alpha_texture_pixel_width,
	multiple_alpha_texture_pixel_width;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static screen
	*set_texture_pixel_lookup_texture = NULL;

unsigned short int
	set_texture_pixel_lookup_table[256];

unsigned int
	set_texture_pixel_32bit_lookup_table[256];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_shift_and_mask ( int source_mask, int *mask, int *shift );

static rgb_packed get_colour_texture_packed_value ( const rgb_colour colour );

static unsigned int get_colour_texture_32bit_value ( const rgb_colour colour );

static rgb_packed get_single_alpha_texture_packed_value ( const rgb_colour colour );

static unsigned int get_single_alpha_texture_32bit_value ( const rgb_colour colour );

static rgb_packed get_multiple_alpha_texture_packed_value ( const rgb_colour colour );

static unsigned int get_multiple_alpha_texture_32bit_value ( const rgb_colour colour );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_texture_pixel ( screen *texture, const int x, const int y, const unsigned int texture_colour, unsigned int texture_alpha )
{

	ASSERT ( texture );

	if ( texture->palette )
	{

		unsigned char
			*ptr;

		ptr = get_screen_data ( texture );

		ptr += get_screen_pitch ( texture ) * y;

		ptr += x;

		*ptr = texture_colour;
	}
	else
	{

		unsigned char
			*ptr;

		switch ( texture->type )
		{

			case TEXTURE_TYPE_NOALPHA:
			{

				if ( colour_texture_pixel_width <= 16 )
				{

					initialise_set_texture_pixel_lookup_table ( texture );
			
					ptr = get_screen_data ( texture );
			
					ptr += get_screen_pitch ( texture ) * y;
			
					ptr += x * 2;

					*( ( unsigned short int * ) ptr ) = set_texture_pixel_lookup_table[texture_colour];
				}
				else
				{

					initialise_set_texture_pixel_lookup_table ( texture );
			
					ptr = get_screen_data ( texture );
			
					ptr += get_screen_pitch ( texture ) * y;
			
					ptr += x * 4;

					*( ( unsigned int * ) ptr ) = set_texture_pixel_32bit_lookup_table[texture_colour];
				}

				break;
			}

			case TEXTURE_TYPE_SINGLEALPHA:
			{

				if ( single_alpha_texture_pixel_width <= 16 )
				{

					unsigned short int
						value;
			
					initialise_set_texture_pixel_lookup_table ( texture );
			
					ptr = get_screen_data ( texture );
			
					ptr += get_screen_pitch ( texture ) * y;
			
					ptr += x * 2;

					value = set_texture_pixel_lookup_table[texture_colour];

					texture_alpha <<= 24;
	
					texture_alpha &= texture_single_alpha_alpha_mask;
	
					texture_alpha >>= texture_single_alpha_alpha_shift;
	
					value |= texture_alpha;

					*( ( unsigned short int * ) ptr ) = value;
				}
				else
				{

					unsigned int
						value;
			
					initialise_set_texture_pixel_lookup_table ( texture );
			
					ptr = get_screen_data ( texture );
			
					ptr += get_screen_pitch ( texture ) * y;
			
					ptr += x * 4;

					value = set_texture_pixel_32bit_lookup_table[texture_colour];

					texture_alpha <<= 24;
	
					texture_alpha &= texture_single_alpha_alpha_mask;
	
					texture_alpha >>= texture_single_alpha_alpha_shift;
	
					value |= texture_alpha;

					*( ( unsigned int * ) ptr ) = value;
				}

				break;
			}

			case TEXTURE_TYPE_MULTIPLEALPHA:
			{

				if ( multiple_alpha_texture_pixel_width <= 16 )
				{

					unsigned short int
						value;
			
					initialise_set_texture_pixel_lookup_table ( texture );
			
					ptr = get_screen_data ( texture );
			
					ptr += get_screen_pitch ( texture ) * y;
			
					ptr += x * 2;

					value = set_texture_pixel_lookup_table[texture_colour];

					texture_alpha <<= 24;
	
					texture_alpha &= texture_multiple_alpha_alpha_mask;
	
					texture_alpha >>= texture_multiple_alpha_alpha_shift;
	
					value |= texture_alpha;

					*( ( unsigned short int * ) ptr ) = value;
				}
				else
				{

					unsigned int
						value;
			
					initialise_set_texture_pixel_lookup_table ( texture );
			
					ptr = get_screen_data ( texture );
			
					ptr += get_screen_pitch ( texture ) * y;
			
					ptr += x * 4;

					value = set_texture_pixel_lookup_table[texture_colour];

					texture_alpha <<= 24;
	
					texture_alpha &= texture_multiple_alpha_alpha_mask;
	
					texture_alpha >>= texture_multiple_alpha_alpha_shift;
	
					value |= texture_alpha;

					*( ( unsigned int * ) ptr ) = value;
				}

				break;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_set_texture_pixel_lookup_table ( screen *texture )
{

	int
		count;

	if ( texture == set_texture_pixel_lookup_texture )
	{

		return;
	}

	switch ( texture->type )
	{

		case TEXTURE_TYPE_NOALPHA:
		{

			if ( colour_texture_pixel_width <= 16 )
			{
	
				for ( count = 0; count < 256; count++ )
				{
			
					rgb_colour
						colour;
				
					colour.r = texture->colour_table[count].peRed;
					colour.g = texture->colour_table[count].peGreen;
					colour.b = texture->colour_table[count].peBlue;
				
					set_texture_pixel_lookup_table[count] = get_colour_texture_packed_value ( colour );
				}
			}
			else
			{
	
				for ( count = 0; count < 256; count++ )
				{
			
					rgb_colour
						colour;
				
					colour.r = texture->colour_table[count].peRed;
					colour.g = texture->colour_table[count].peGreen;
					colour.b = texture->colour_table[count].peBlue;
				
					set_texture_pixel_32bit_lookup_table[count] = get_colour_texture_32bit_value ( colour );
				}
			}

			break;
		}

		case TEXTURE_TYPE_SINGLEALPHA:
		{

			if ( single_alpha_texture_pixel_width <= 16 )
			{
	
				for ( count = 0; count < 256; count++ )
				{
			
					rgb_colour
						colour;
				
					colour.r = texture->colour_table[count].peRed;
					colour.g = texture->colour_table[count].peGreen;
					colour.b = texture->colour_table[count].peBlue;
				
					set_texture_pixel_lookup_table[count] = get_single_alpha_texture_packed_value ( colour );
				}
			}
			else
			{
	
				for ( count = 0; count < 256; count++ )
				{
			
					rgb_colour
						colour;
				
					colour.r = texture->colour_table[count].peRed;
					colour.g = texture->colour_table[count].peGreen;
					colour.b = texture->colour_table[count].peBlue;
				
					set_texture_pixel_32bit_lookup_table[count] = get_single_alpha_texture_32bit_value ( colour );
				}
			}

			break;
		}

		case TEXTURE_TYPE_MULTIPLEALPHA:
		{

			if ( multiple_alpha_texture_pixel_width <= 16 )
			{
	
				for ( count = 0; count < 256; count++ )
				{
			
					rgb_colour
						colour;
				
					colour.r = texture->colour_table[count].peRed;
					colour.g = texture->colour_table[count].peGreen;
					colour.b = texture->colour_table[count].peBlue;
				
					set_texture_pixel_lookup_table[count] = get_multiple_alpha_texture_packed_value ( colour );
				}
			}
			else
			{
	
				for ( count = 0; count < 256; count++ )
				{
			
					rgb_colour
						colour;
				
					colour.r = texture->colour_table[count].peRed;
					colour.g = texture->colour_table[count].peGreen;
					colour.b = texture->colour_table[count].peBlue;
				
					set_texture_pixel_32bit_lookup_table[count] = get_multiple_alpha_texture_32bit_value ( colour );
				}
			}

			break;
		}
	}

	set_texture_pixel_lookup_texture = texture;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

rgb_packed get_colour_texture_packed_value ( const rgb_colour colour )
{

	unsigned int
		red,
		green,
		blue;

	ASSERT ( colour_texture_pixel_width == 16 );

	red = ( ( unsigned int ) colour.r ) << 24;
	green = ( ( unsigned int ) colour.g ) << 24;
	blue = ( ( unsigned int ) colour.b ) << 24;

	red &= texture_colour_red_mask;
	green &= texture_colour_green_mask;
	blue &= texture_colour_blue_mask;

	red >>= texture_colour_red_shift;
	green >>= texture_colour_green_shift;
	blue >>= texture_colour_blue_shift;

	return ( red | green | blue );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int get_colour_texture_32bit_value ( const rgb_colour colour )
{

	unsigned int
		red,
		green,
		blue;

	ASSERT ( colour_texture_pixel_width == 32 );

	red = ( ( unsigned int ) colour.r ) << 24;
	green = ( ( unsigned int ) colour.g ) << 24;
	blue = ( ( unsigned int ) colour.b ) << 24;

	red &= texture_colour_red_mask;
	green &= texture_colour_green_mask;
	blue &= texture_colour_blue_mask;

	red >>= texture_colour_red_shift;
	green >>= texture_colour_green_shift;
	blue >>= texture_colour_blue_shift;

	return ( red | green | blue );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

rgb_packed get_single_alpha_texture_packed_value ( const rgb_colour colour )
{

	unsigned int
		red,
		green,
		blue;

	ASSERT ( single_alpha_texture_pixel_width == 16 );

	red = ( ( unsigned int ) colour.r ) << 24;
	green = ( ( unsigned int ) colour.g ) << 24;
	blue = ( ( unsigned int ) colour.b ) << 24;

	red &= texture_single_alpha_red_mask;
	green &= texture_single_alpha_green_mask;
	blue &= texture_single_alpha_blue_mask;

	red >>= texture_single_alpha_red_shift;
	green >>= texture_single_alpha_green_shift;
	blue >>= texture_single_alpha_blue_shift;

	return ( red | green | blue );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int get_single_alpha_texture_32bit_value ( const rgb_colour colour )
{

	unsigned int
		red,
		green,
		blue;

	ASSERT ( single_alpha_texture_pixel_width == 32 );

	red = ( ( unsigned int ) colour.r ) << 24;
	green = ( ( unsigned int ) colour.g ) << 24;
	blue = ( ( unsigned int ) colour.b ) << 24;

	red &= texture_single_alpha_red_mask;
	green &= texture_single_alpha_green_mask;
	blue &= texture_single_alpha_blue_mask;

	red >>= texture_single_alpha_red_shift;
	green >>= texture_single_alpha_green_shift;
	blue >>= texture_single_alpha_blue_shift;

	return ( red | green | blue );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

rgb_packed get_multiple_alpha_texture_packed_value ( const rgb_colour colour )
{

	unsigned int
		red,
		green,
		blue;

	ASSERT ( multiple_alpha_texture_pixel_width == 16 );

	red = ( ( unsigned int ) colour.r ) << 24;
	green = ( ( unsigned int ) colour.g ) << 24;
	blue = ( ( unsigned int ) colour.b ) << 24;

	red &= texture_multiple_alpha_red_mask;
	green &= texture_multiple_alpha_green_mask;
	blue &= texture_multiple_alpha_blue_mask;

	red >>= texture_multiple_alpha_red_shift;
	green >>= texture_multiple_alpha_green_shift;
	blue >>= texture_multiple_alpha_blue_shift;

	return ( red | green | blue );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int get_multiple_alpha_texture_32bit_value ( const rgb_colour colour )
{

	unsigned int
		red,
		green,
		blue;

	ASSERT ( multiple_alpha_texture_pixel_width == 32 );

	red = ( ( unsigned int ) colour.r ) << 24;
	green = ( ( unsigned int ) colour.g ) << 24;
	blue = ( ( unsigned int ) colour.b ) << 24;

	red &= texture_multiple_alpha_red_mask;
	green &= texture_multiple_alpha_green_mask;
	blue &= texture_multiple_alpha_blue_mask;

	red >>= texture_multiple_alpha_red_shift;
	green >>= texture_multiple_alpha_green_shift;
	blue >>= texture_multiple_alpha_blue_shift;

	return ( red | green | blue );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_texture_pixel_formats ( void )
{

	if ( !texture_formats[TEXTURE_TYPE_NOALPHA].palette )
	{

		set_shift_and_mask ( texture_formats[TEXTURE_TYPE_NOALPHA].format.dwRBitMask, &texture_colour_red_mask, &texture_colour_red_shift );
		set_shift_and_mask ( texture_formats[TEXTURE_TYPE_NOALPHA].format.dwGBitMask, &texture_colour_green_mask, &texture_colour_green_shift );
		set_shift_and_mask ( texture_formats[TEXTURE_TYPE_NOALPHA].format.dwBBitMask, &texture_colour_blue_mask, &texture_colour_blue_shift );
	
		colour_texture_pixel_width = texture_formats[TEXTURE_TYPE_NOALPHA].format.dwRGBBitCount;
	}

	if ( !texture_formats[TEXTURE_TYPE_NOALPHA_NOPALETTE].palette )
	{

		set_shift_and_mask ( texture_formats[TEXTURE_TYPE_NOALPHA_NOPALETTE].format.dwRBitMask, &texture_colour_nopalette_red_mask, &texture_colour_nopalette_red_shift );
		set_shift_and_mask ( texture_formats[TEXTURE_TYPE_NOALPHA_NOPALETTE].format.dwGBitMask, &texture_colour_nopalette_green_mask, &texture_colour_nopalette_green_shift );
		set_shift_and_mask ( texture_formats[TEXTURE_TYPE_NOALPHA_NOPALETTE].format.dwBBitMask, &texture_colour_nopalette_blue_mask, &texture_colour_nopalette_blue_shift );

		colour_nopalette_texture_pixel_width = texture_formats[TEXTURE_TYPE_NOALPHA_NOPALETTE].format.dwRGBBitCount;
	}

	if ( !texture_formats[TEXTURE_TYPE_SINGLEALPHA].palette )
	{

		set_shift_and_mask ( texture_formats[TEXTURE_TYPE_SINGLEALPHA].format.dwRBitMask, &texture_single_alpha_red_mask, &texture_single_alpha_red_shift );
		set_shift_and_mask ( texture_formats[TEXTURE_TYPE_SINGLEALPHA].format.dwGBitMask, &texture_single_alpha_green_mask, &texture_single_alpha_green_shift );
		set_shift_and_mask ( texture_formats[TEXTURE_TYPE_SINGLEALPHA].format.dwBBitMask, &texture_single_alpha_blue_mask, &texture_single_alpha_blue_shift );
		set_shift_and_mask ( texture_formats[TEXTURE_TYPE_SINGLEALPHA].format.dwRGBAlphaBitMask, &texture_single_alpha_alpha_mask, &texture_single_alpha_alpha_shift );
	
		single_alpha_texture_pixel_width = texture_formats[TEXTURE_TYPE_SINGLEALPHA].format.dwRGBBitCount;
	}

	if ( !texture_formats[TEXTURE_TYPE_MULTIPLEALPHA].palette )
	{

		set_shift_and_mask ( texture_formats[TEXTURE_TYPE_MULTIPLEALPHA].format.dwRBitMask, &texture_multiple_alpha_red_mask, &texture_multiple_alpha_red_shift );
		set_shift_and_mask ( texture_formats[TEXTURE_TYPE_MULTIPLEALPHA].format.dwGBitMask, &texture_multiple_alpha_green_mask, &texture_multiple_alpha_green_shift );
		set_shift_and_mask ( texture_formats[TEXTURE_TYPE_MULTIPLEALPHA].format.dwBBitMask, &texture_multiple_alpha_blue_mask, &texture_multiple_alpha_blue_shift );
		set_shift_and_mask ( texture_formats[TEXTURE_TYPE_MULTIPLEALPHA].format.dwRGBAlphaBitMask, &texture_multiple_alpha_alpha_mask, &texture_multiple_alpha_alpha_shift );
	
		multiple_alpha_texture_pixel_width = texture_formats[TEXTURE_TYPE_MULTIPLEALPHA].format.dwRGBBitCount;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_shift_and_mask ( int source_mask, int *mask, int *shift )
{

	int
		shiftcount;

	shiftcount = 0;

	if ( source_mask )
	{

		for ( shiftcount = 0; !( source_mask & 0x80000000 ); shiftcount++ )
		{
	
			source_mask <<= 1;
		}
	}

	*shift = shiftcount;

	*mask = source_mask;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

