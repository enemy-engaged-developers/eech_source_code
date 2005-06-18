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
	pixel_width;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_pixel ( const int x, const int y, const rgb_colour colour )
{

	unsigned int
		red,
		green,
		blue,
		alpha;

	ASSERT ( active_screen );

	if ( get_screen_locked ( active_screen ) )
	{

		if ( get_screen_pixel_width ( active_screen ) == 2 )
		{
	
			unsigned short int
				value;
		
			red = ( ( unsigned int ) colour.r ) << 24;
			green = ( ( unsigned int ) colour.g ) << 24;
			blue = ( ( unsigned int ) colour.b ) << 24;
			alpha = ( ( unsigned int ) colour.a ) << 24;
		
			red &= active_screen_red_mask;
			green &= active_screen_green_mask;
			blue &= active_screen_blue_mask;
			alpha &= active_screen_alpha_mask;
		
			red >>= active_screen_red_shift;
			green >>= active_screen_green_shift;
			blue >>= active_screen_blue_shift;
			alpha >>= active_screen_alpha_shift;
		
			value =  ( red | green | blue | alpha );
		
			* ( (USHORT *) ( get_screen_data ( active_screen ) + y * get_screen_pitch ( active_screen ) ) + x ) = value;
		}
		else
		{

			unsigned int
				value;
		
			//
			// Assume 4 bytes per pixel
			//

			red = ( ( unsigned int ) colour.r ) << 24;
			green = ( ( unsigned int ) colour.g ) << 24;
			blue = ( ( unsigned int ) colour.b ) << 24;
			alpha = ( ( unsigned int ) colour.a ) << 24;
		
			red &= active_screen_red_mask;
			green &= active_screen_green_mask;
			blue &= active_screen_blue_mask;
			alpha &= active_screen_alpha_mask;
		
			red >>= active_screen_red_shift;
			green >>= active_screen_green_shift;
			blue >>= active_screen_blue_shift;
			alpha >>= active_screen_alpha_shift;
		
			value =  ( red | green | blue | alpha );
		
			* ( (ULONG *) ( get_screen_data ( active_screen ) + y * get_screen_pitch ( active_screen ) ) + x ) = value;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_packed_pixel ( const int x, const int y, const rgb_packed colour )
{

	ASSERT ( active_screen );
	ASSERT ( active_screen->locked );

	* ( (USHORT *) ( get_screen_data ( active_screen ) + y * get_screen_pitch ( active_screen ) ) + x ) = ( USHORT ) colour;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_clipped_pixel ( const int x, const int y, const rgb_colour colour )
{

	ASSERT ( active_screen );

	if ( ( x >= active_int_viewport.x_min ) &&
			( x <= active_int_viewport.x_max ) &&
			( y >= active_int_viewport.y_min ) &&
			( y <= active_int_viewport.y_max ) )
	{

		set_pixel ( x, y, colour );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_pixel ( const int x, const int y, rgb_colour *colour )
{

	unsigned short int
		value;

	unsigned int
		red,
		green,
		blue,
		alpha;

	ASSERT ( active_screen );
	ASSERT ( colour );

	value = * ( ( short int *) ( get_screen_data ( active_screen ) + y * get_screen_pitch ( active_screen ) ) + x );

	red = value << active_screen_red_shift;
	green = value << active_screen_green_shift;
	blue = value << active_screen_blue_shift;
	alpha = value << active_screen_alpha_shift;

	red &= active_screen_red_mask;
	green &= active_screen_green_mask;
	blue &= active_screen_blue_mask;
	alpha &= active_screen_alpha_mask;

	colour->r = red >> 24;
	colour->g = green >> 24;
	colour->b = blue >> 24;
	colour->a = alpha >> 24;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

rgb_packed get_packed_pixel ( const int x, const int y )
{

	unsigned short int
		value;

	ASSERT ( active_screen );

	value = * ( ( short int *) ( get_screen_data ( active_screen ) + y * get_screen_pitch ( active_screen ) ) + x );

	return ( ( rgb_packed ) value );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

rgb_packed get_rgb_packed_value ( const rgb_colour colour )
{

	unsigned int
		red,
		green,
		blue,
		alpha;

//	ASSERT ( pixel_width == 16 );

	red = ( ( unsigned int ) colour.r ) << 24;
	green = ( ( unsigned int ) colour.g ) << 24;
	blue = ( ( unsigned int ) colour.b ) << 24;
	alpha = ( ( unsigned int ) colour.a ) << 24;

	red &= active_screen_red_mask;
	green &= active_screen_green_mask;
	blue &= active_screen_blue_mask;
	alpha &= active_screen_alpha_mask;

	red >>= active_screen_red_shift;
	green >>= active_screen_green_shift;
	blue >>= active_screen_blue_shift;
	alpha >>= active_screen_alpha_shift;

	return ( red | green | blue | alpha );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

rgb_colour get_rgb_colour_value ( const unsigned long colour )
{

	unsigned int
		red,
		green,
		blue,
		alpha;

	rgb_colour
		colour_value;

//	ASSERT ( pixel_width == 16 );

	red = colour << active_screen_red_shift;
	green = colour << active_screen_green_shift;
	blue = colour << active_screen_blue_shift;
	alpha = colour << active_screen_alpha_shift;

	red &= active_screen_red_mask;
	green &= active_screen_green_mask;
	blue &= active_screen_blue_mask;
	alpha &= active_screen_alpha_mask;

	colour_value.r = red >> 24;
	colour_value.g = green >> 24;
	colour_value.b = blue >> 24;
	colour_value.a = alpha >> 24;

	return ( colour_value );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

rgb_packed get_user_rgb_packed_value ( const rgb_colour colour )
{

	unsigned int
		red,
		green,
		blue,
		alpha;

//	ASSERT ( pixel_width == 16 );

	red = ( ( unsigned int ) colour.r ) << 24;
	green = ( ( unsigned int ) colour.g ) << 24;
	blue = ( ( unsigned int ) colour.b ) << 24;
	alpha = ( ( unsigned int ) colour.a ) << 24;

	red &= user_screen_red_mask;
	green &= user_screen_green_mask;
	blue &= user_screen_blue_mask;
	alpha &= user_screen_alpha_mask;

	red >>= user_screen_red_shift;
	green >>= user_screen_green_shift;
	blue >>= user_screen_blue_shift;
	alpha >>= user_screen_alpha_shift;

	return ( red | green | blue | alpha );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

rgb_colour get_user_rgb_colour_value ( const rgb_packed colour )
{

	unsigned int
		red,
		green,
		blue,
		alpha;

	rgb_colour
		colour_value;

//	ASSERT ( pixel_width == 16 );

	red = colour << user_screen_red_shift;
	green = colour << user_screen_green_shift;
	blue = colour << user_screen_blue_shift;
	alpha = colour << user_screen_alpha_shift;

	red &= user_screen_red_mask;
	green &= user_screen_green_mask;
	blue &= user_screen_blue_mask;
	alpha &= user_screen_alpha_mask;

	colour_value.r = red >> 24;
	colour_value.g = green >> 24;
	colour_value.b = blue >> 24;
	colour_value.a = alpha >> 24;

	return ( colour_value );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_pixel_format ( void )
{

	DDSURFACEDESC2
		ddsd;

	ASSERT ( ddraw.lpRenderBuffer );

	ddsd.dwSize = sizeof ( ddsd );

	IDirectDrawSurface7_GetSurfaceDesc ( ddraw.lpRenderBuffer, &ddsd );

	pixel_width = ddsd.ddpfPixelFormat.dwRGBBitCount;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_surface_shift_and_mask ( int source_mask, int *mask, int *shift )
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

