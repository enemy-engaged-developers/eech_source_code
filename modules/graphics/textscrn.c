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

#define DEBUG_MODULE 1

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_texture_screen_data ( screen *texture, int width, int height, enum SCREEN_FORMAT_TYPES type, int number_of_mipmaps, int renderto )
{

	DDSURFACEDESC2
		ddsd;
	
	HRESULT
		ret;


	debug_log ( "Creating user texture screen: %d, %d ( %d mipmaps ) ( %d render to ) ", width, height, number_of_mipmaps, renderto );

	memset ( &ddsd, 0, sizeof ( ddsd ) );

	ddsd.dwSize = sizeof ( ddsd );

	//
	// Allocate a d3d managed texture
	//

	memcpy ( &ddsd.ddpfPixelFormat, &texture_formats[type].format, sizeof ( DDPIXELFORMAT ) );

	ddsd.dwMipMapCount = 0;
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
	ddsd.ddsCaps.dwCaps = DDSCAPS_TEXTURE;
	ddsd.dwHeight = height;
	ddsd.dwWidth = width;
	ddsd.ddsCaps.dwCaps3 = 0;
	ddsd.ddsCaps.dwCaps4 = 0;
	ddsd.ddsCaps.dwCaps2 = DDSCAPS2_HINTDYNAMIC | DDSCAPS2_TEXTUREMANAGE;

	if ( ( d3d_mipmap_textures ) && ( number_of_mipmaps > 1 ) )
	{
		
		ddsd.dwFlags |= DDSD_MIPMAPCOUNT;
		ddsd.ddsCaps.dwCaps |= DDSCAPS_COMPLEX | DDSCAPS_MIPMAP;
		ddsd.dwMipMapCount = number_of_mipmaps;
	}

	ret = IDirectDraw7_CreateSurface ( ddraw.ddraw, &ddsd, &texture->surface, NULL );

	if ( ret != DD_OK )
	{

		debug_fatal ( "Unable to create texture surface: %s ( %d, %d )", get_ddraw_error_message ( ret ), width, height );
	}

	//
	// Texture doesn't have a colour table
	//

	texture->type = type;
	texture->palette = NULL;
	texture->colour_table = NULL;
	texture->pixel_length = texture_formats[type].bpp_red + texture_formats[type].bpp_green + texture_formats[type].bpp_blue + texture_formats[type].bpp_alpha;
	texture->clone_screen = FALSE;
	texture->do_not_destroy = FALSE;

	//
	// Setup render surface
	//

	if ( renderto )
	{

		memset ( &ddsd, 0, sizeof ( ddsd ) );
	
		ddsd.dwSize = sizeof ( ddsd );
	
		memcpy ( &ddsd.ddpfPixelFormat, &texture_formats[type].format, sizeof ( DDPIXELFORMAT ) );
	
		ddsd.dwSize = sizeof ( ddsd );
		ddsd.dwMipMapCount = 0;
		ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
		ddsd.ddsCaps.dwCaps = DDSCAPS_3DDEVICE;
		ddsd.dwHeight = height;
		ddsd.dwWidth = width;
		ddsd.ddsCaps.dwCaps3 = 0;
		ddsd.ddsCaps.dwCaps4 = 0;
		ddsd.ddsCaps.dwCaps2 = 0;
		ddsd.ddsCaps.dwCaps |= ( d3d_use_rgb_device ) ? ( DDSCAPS_SYSTEMMEMORY ) : ( DDSCAPS_VIDEOMEMORY | DDSCAPS_LOCALVIDMEM );
		
		ret = IDirectDraw7_CreateSurface ( ddraw.ddraw, &ddsd, &texture->render_texture_surface, NULL );
	
		if ( ret != DD_OK )
		{
	
			debug_fatal ( "Unable to create texture render surface: %s ( %d, %d )", get_ddraw_error_message ( ret ), width, height );
		}

		memset ( &ddsd, 0, sizeof ( ddsd ) );

		ddsd.dwSize = sizeof ( ddsd );

		ret = IDirectDrawSurface7_GetSurfaceDesc ( ddraw.lpFrontBuffer, &ddsd );
		
		ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
		ddsd.ddsCaps.dwCaps = DDSCAPS_ZBUFFER;
		ddsd.ddsCaps.dwCaps |= ( d3d_use_rgb_device ) ? ( DDSCAPS_SYSTEMMEMORY ) : ( DDSCAPS_VIDEOMEMORY | DDSCAPS_LOCALVIDMEM );
		ddsd.dwWidth = width;
		ddsd.dwHeight = height;

		get_ddraw_zbuffer_pixel_format ( &ddsd.ddpfPixelFormat );
//		ddsd.ddpfPixelFormat.dwSize = sizeof ( ddsd.ddpfPixelFormat );
//		ddsd.ddpfPixelFormat.dwFlags = DDPF_ZBUFFER;
//		ddsd.ddpfPixelFormat.dwZBufferBitDepth = 16;

		ret = IDirectDraw7_CreateSurface ( ddraw.ddraw, &ddsd, &texture->zbuffer_surface, NULL );
		
		if ( ret != DD_OK )
		{
			
			debug_fatal ( "Unable to create Zbuffer surface: %s", get_ddraw_error_message ( ret ) );
		}

		ret = IDirectDrawSurface7_AddAttachedSurface ( texture->render_texture_surface, texture->zbuffer_surface );

		if ( ret != DD_OK )
		{

			debug_fatal ( "Unable to attach Zbuffer surface: %s", get_ddraw_error_message ( ret ) );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_system_texture_screen_mapping ( screen *this_screen, int texture_index )
{

	screen
		*texture;

	//
	// Usurp a system texture
	//

	if ( system_textures[texture_index]->used )
	{

		ASSERT ( system_textures[texture_index]->clone_screen );
	}

	texture = system_textures[texture_index];

	memcpy ( texture, this_screen, sizeof ( screen ) );

	texture->clone_screen = TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void flush_screen_texture_graphics ( screen *this_screen )
{

	ASSERT ( this_screen );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

screen *get_screen_texture ( screen *this_screen )
{

	ASSERT ( this_screen );

	return ( this_screen );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

