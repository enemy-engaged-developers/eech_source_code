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

#ifndef OGRE_EE
static screen
	*mouse_pointer;
#else
unsigned
	mouse_pointer;
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define POINTER

#if defined(POINTER) && !defined(OGRE_EE)
struct
{
	unsigned width, height;
	unsigned char image[10 * 20];
} pointer[1] = { { 10, 20,
{
	0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x0D, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x0D, 0x0D, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x0D, 0xFB, 0x0D, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x0D, 0xFB, 0xF5, 0x0D, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x0D, 0xFB, 0xFD, 0xF6, 0x0D, 0x0D, 0x00, 0x00, 0x00, 0x00,
	0x0D, 0xFB, 0xFD, 0xFF, 0xF5, 0x0D, 0x0D, 0x00, 0x00, 0x00,
	0x0D, 0xFB, 0xFE, 0xFB, 0xF9, 0xEF, 0x0D, 0x0D, 0x00, 0x00,
	0x0D, 0xFB, 0xFF, 0xFF, 0xFF, 0xFE, 0xF2, 0x0D, 0x0D, 0x00,
	0x0D, 0xFB, 0xFF, 0xFF, 0xFF, 0xFA, 0xFB, 0xFB, 0x0D, 0x0D,
	0x0D, 0xFB, 0xFB, 0xFB, 0xFB, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D,
	0x0D, 0xFB, 0x0D, 0x0D, 0xFB, 0x0D, 0x00, 0x00, 0x00, 0x00,
	0x0D, 0x0D, 0x0D, 0x00, 0x0D, 0xFF, 0x0D, 0x00, 0x00, 0x00,
	0x0D, 0x00, 0x00, 0x00, 0x0D, 0xF0, 0x0D, 0x00, 0x00, 0x00,
	0x0D, 0x00, 0x00, 0x00, 0x00, 0x0D, 0xFF, 0x0D, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0xF2, 0x0D, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0xFF, 0x0D, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0xFB, 0x0D, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0xFF, 0x0D,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0x0D, 0x0D,
} } };
#endif

#ifndef POINTER
void initialise_mouse_pointer ( rgb_data *pointer )
#else
void initialise_mouse_pointer ( void )
#endif
{
#ifndef OGRE_EE
	int
		mouse_pointer_width,
		mouse_pointer_height;

	for ( mouse_pointer_width = 1; mouse_pointer_width < pointer->width; mouse_pointer_width <<= 1 );
	for ( mouse_pointer_height = 1; mouse_pointer_height < pointer->height; mouse_pointer_height <<= 1 );
	mouse_pointer = create_user_texture_screen ( mouse_pointer_width, mouse_pointer_height, TEXTURE_TYPE_MULTIPLEALPHA, 1 );
	while ( !lock_screen ( mouse_pointer ) )
	{
		Sleep ( 100 );
	}
	{
		unsigned int
			*ptr;
		int
			pitch,
			x,
			y;
		rgb_colour
#ifndef POINTER
			*image,
#endif
			colour;
#ifdef POINTER
		unsigned char
			*image;
#endif

		ptr = get_screen_data ( mouse_pointer );
		pitch = get_screen_pitch ( mouse_pointer );
		memset ( ptr, 0, pitch * mouse_pointer_height * 4 );
		image = pointer->image;
		for ( y = 0; y < pointer->height; y++ )
		{
			for ( x = 0; x < pointer->width; x++ )
			{
#ifdef POINTER
				colour.b = colour.g = colour.r = *image++;
				colour.alpha = colour.b ? 255 : 0;
#else
				colour = *image++;
				colour.alpha = colour.colour ? 255 : 0;
#endif
				*ptr++ = colour.colour;
			}
			ptr += pitch - pointer->width;
		}
	}
	unlock_screen ( mouse_pointer );
#else
	mouse_pointer = ogre_texture_load ( "graphics\\ui\\common\\pointer.PSD" );
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_mouse_pointer ( void )
{
#ifndef OGRE_EE
	destroy_screen ( mouse_pointer );
#else
	ogre_texture_clear ( mouse_pointer );
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_mouse_graphic_on ( void )
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_mouse_graphic_off ( void )
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_mouse_graphic_on ( void )
{
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_raw_mouse_pointer ( const int x, const int y )
{
#ifndef OGRE_EE
	set_viewport ( 0, 0, application_video_width, application_video_height );
	d3d_texture_draw ( mouse_pointer, x, y );
#else
	ogre_ui_draw ( mouse_pointer, x, y, x + 10, y + 20 );
#endif
}
