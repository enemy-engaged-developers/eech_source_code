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

#include "terrain.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned char
	*terrain_3d_colour_data = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PALETTEENTRY
	terrain_3d_colour_palette[256];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_terrain_colours ( char *filename )
{

	int
		count,
		bits;

	short int
		width,
		height;

	terrain_3d_colour_data = ( unsigned char * ) load_tga_file ( filename, &width, &height, &bits );

	ASSERT ( terrain_3d_colour_data );

	if ( bits != 8 )
	{

		debug_fatal ( "Unable to load a true colour file for the terrain colours" );
	}

	for ( count = 0; count < 256; count++ )
	{

		terrain_3d_colour_palette[count].peRed = tga_image_palette[count].peRed;
		terrain_3d_colour_palette[count].peGreen = tga_image_palette[count].peGreen;
		terrain_3d_colour_palette[count].peBlue = tga_image_palette[count].peBlue;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define TERRAIN_COLOUR_SIZE 1024

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_terrain_colour_red ( float x, float z )
{

	int
		ix,
		ix2,
		iz,
		iz2;

	float
		fx,
		fz,
		colour_topleft,
		colour_topright,
		colour_bottomleft,
		colour_bottomright,
		colour_left,
		colour_right;

	unsigned char
		value;

	convert_float_to_int ( ( x / TERRAIN_COLOUR_SIZE ), &ix );

	convert_float_to_int ( ( z / TERRAIN_COLOUR_SIZE ), &iz );

	fx = ix * TERRAIN_COLOUR_SIZE;

	fz = iz * TERRAIN_COLOUR_SIZE;

	fx = ( ( x - fx ) / TERRAIN_COLOUR_SIZE );

	fz = ( ( z - fz ) / TERRAIN_COLOUR_SIZE );

	ix2 = ix + 1;

	iz2 = iz + 1;

	ix2 = bound ( ix2, 0, 1023 );

	iz2 = bound ( iz2, 0, 1023 );

	value = terrain_3d_colour_data[ ( ( iz * 1024 ) + ix ) ];

	colour_topleft = terrain_3d_colour_palette[value].peRed;

	value = terrain_3d_colour_data[ ( ( iz * 1024 ) + ix2 ) ];

	colour_topright = terrain_3d_colour_palette[value].peRed;

	value = terrain_3d_colour_data[ ( ( iz2 * 1024 ) + ix ) ];

	colour_bottomleft = terrain_3d_colour_palette[value].peRed;

	value = terrain_3d_colour_data[ ( ( iz2 * 1024 ) + ix2 ) ];

	colour_bottomright = terrain_3d_colour_palette[value].peRed;

	colour_left = ( colour_topleft * ( 1 - fz ) ) + ( colour_bottomleft * fz );

	colour_right = ( colour_topright * ( 1 - fz ) ) + ( colour_bottomright * fz );

	return ( ( colour_left * ( 1 - fx ) ) + ( colour_right * fx ) );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_terrain_colour_green ( float x, float z )
{

	int
		ix,
		ix2,
		iz,
		iz2;

	float
		fx,
		fz,
		colour_topleft,
		colour_topright,
		colour_bottomleft,
		colour_bottomright,
		colour_left,
		colour_right;

	unsigned char
		value;

	convert_float_to_int ( ( x / TERRAIN_COLOUR_SIZE ), &ix );

	convert_float_to_int ( ( z / TERRAIN_COLOUR_SIZE ), &iz );

	fx = ix * TERRAIN_COLOUR_SIZE;

	fz = iz * TERRAIN_COLOUR_SIZE;

	fx = ( ( x - fx ) / TERRAIN_COLOUR_SIZE );

	fz = ( ( z - fz ) / TERRAIN_COLOUR_SIZE );

	ix2 = ix + 1;

	iz2 = iz + 1;

	ix2 = bound ( ix2, 0, 1023 );

	iz2 = bound ( iz2, 0, 1023 );

	value = terrain_3d_colour_data[ ( ( iz * 1024 ) + ix ) ];

	colour_topleft = terrain_3d_colour_palette[value].peGreen;

	value = terrain_3d_colour_data[ ( ( iz * 1024 ) + ix2 ) ];

	colour_topright = terrain_3d_colour_palette[value].peGreen;

	value = terrain_3d_colour_data[ ( ( iz2 * 1024 ) + ix ) ];

	colour_bottomleft = terrain_3d_colour_palette[value].peGreen;

	value = terrain_3d_colour_data[ ( ( iz2 * 1024 ) + ix2 ) ];

	colour_bottomright = terrain_3d_colour_palette[value].peGreen;

	colour_left = ( colour_topleft * ( 1 - fz ) ) + ( colour_bottomleft * fz );

	colour_right = ( colour_topright * ( 1 - fz ) ) + ( colour_bottomright * fz );

	return ( ( colour_left * ( 1 - fx ) ) + ( colour_right * fx ) );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_terrain_colour_blue ( float x, float z )
{

	int
		ix,
		ix2,
		iz,
		iz2;

	float
		fx,
		fz,
		colour_topleft,
		colour_topright,
		colour_bottomleft,
		colour_bottomright,
		colour_left,
		colour_right;

	unsigned char
		value;

	convert_float_to_int ( ( x / TERRAIN_COLOUR_SIZE ), &ix );

	convert_float_to_int ( ( z / TERRAIN_COLOUR_SIZE ), &iz );

	fx = ix * TERRAIN_COLOUR_SIZE;

	fz = iz * TERRAIN_COLOUR_SIZE;

	fx = ( ( x - fx ) / TERRAIN_COLOUR_SIZE );

	fz = ( ( z - fz ) / TERRAIN_COLOUR_SIZE );

	ix2 = ix + 1;

	iz2 = iz + 1;

	ix2 = bound ( ix2, 0, 1023 );

	iz2 = bound ( iz2, 0, 1023 );

	value = terrain_3d_colour_data[ ( ( iz * 1024 ) + ix ) ];

	colour_topleft = terrain_3d_colour_palette[value].peBlue;

	value = terrain_3d_colour_data[ ( ( iz * 1024 ) + ix2 ) ];

	colour_topright = terrain_3d_colour_palette[value].peBlue;

	value = terrain_3d_colour_data[ ( ( iz2 * 1024 ) + ix ) ];

	colour_bottomleft = terrain_3d_colour_palette[value].peBlue;

	value = terrain_3d_colour_data[ ( ( iz2 * 1024 ) + ix2 ) ];

	colour_bottomright = terrain_3d_colour_palette[value].peBlue;

	colour_left = ( colour_topleft * ( 1 - fz ) ) + ( colour_bottomleft * fz );

	colour_right = ( colour_topright * ( 1 - fz ) ) + ( colour_bottomright * fz );

	return ( ( colour_left * ( 1 - fx ) ) + ( colour_right * fx ) );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
