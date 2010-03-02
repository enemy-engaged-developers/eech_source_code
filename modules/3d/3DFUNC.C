#include "system.h"
#include <d3d.h>
#include <d3dtypes.h>
#include "graphics/colour.h"
#include "graphics/dirdraw.h"
#include "graphics/d3d.h"
#include "graphics/scrnstr.h"
#include "graphics/screens.h"
#include "graphics/textsys.h"
#include "3dfunc.h"



void f3d_set_light(unsigned index, D3DLIGHT7 *light)
{
	HRESULT
		ret;

	ret = IDirect3DDevice7_SetLight ( d3d_data.device, index, light );

	if ( FAILED ( ret ) )
	{
		debug_log ( "Unable to set light: %s", get_d3d_error_message ( ret ) );
	}
}

void f3d_light_enable(unsigned index, unsigned state)
{
	HRESULT
		ret;

	ret = IDirect3DDevice7_LightEnable ( d3d_data.device, index, state );

	if ( FAILED ( ret ) )
	{
		debug_log ( "Unable to %sable light: %s", state ? "en" : "dis",
			get_d3d_error_message ( ret ) );
	}
}

void f3d_set_transform(unsigned type, D3DMATRIX *matrix)
{
	HRESULT
		ret;

	ret = IDirect3DDevice7_SetTransform ( d3d_data.device, (D3DTRANSFORMSTATETYPE)type, matrix );

	if ( FAILED ( ret ) )
	{
		debug_log ( "Unable to set %u transfom: %s", type, get_d3d_error_message ( ret ) );
	}
}

int f3d_set_viewport(D3DVIEWPORT7 *viewport)
{
	HRESULT
		ret;

	ret = IDirect3DDevice7_SetViewport ( d3d_data.device, viewport );

	if ( ret != D3D_OK )
	{
		debug_log ( "Unable to set viewport7: %s", get_d3d_error_message ( ret ) );
		return FALSE;
	}

	return TRUE;
}

void f3d_vertex_create(D3DVERTEXBUFFERDESC* desc, LPDIRECT3DVERTEXBUFFER7 *buffer)
{
	HRESULT
		ret;

	ret = IDirect3D7_CreateVertexBuffer ( d3d_data.d3d, desc, buffer, 0 );

	if ( FAILED ( ret ) )
	{
		debug_fatal ( "Unable to create vertex buffer: %s", get_d3d_error_message ( ret ) );
	}
}

void f3d_vertex_release(LPDIRECT3DVERTEXBUFFER7 *buffer)
{
	HRESULT
		ret;

	ret = IDirect3DVertexBuffer_Release ( *buffer );

	if ( FAILED ( ret ) )
	{
		debug_log ( "Unable to release primary vertex buffer: %s", get_d3d_error_message ( ret ) );
	}

	*buffer = NULL;
}

void f3d_vertex_optimize(LPDIRECT3DVERTEXBUFFER7 buffer)
{
	HRESULT
		ret;

	ret = IDirect3DVertexBuffer7_Optimize ( buffer, d3d_data.device, 0 );

	if ( FAILED ( ret ) )
	{
		debug_fatal ( "Unable to optimize vertex buffer: %s", get_d3d_error_message ( ret ) );
	}
}


int f3d_vertex_lock(LPDIRECT3DVERTEXBUFFER7 buffer, unsigned flags, void **ptr)
{
	HRESULT
		ret;

	ret = IDirect3DVertexBuffer7_Lock ( buffer, flags, ptr, NULL );

	if ( FAILED ( ret ) )
	{
		debug_fatal ( "Unable to lock vertex buffer: %s", get_d3d_error_message ( ret ) );
		return FALSE;
	}

	return TRUE;
}

void f3d_vertex_unlock(LPDIRECT3DVERTEXBUFFER7 buffer)
{
	HRESULT
		ret;

	ret = IDirect3DVertexBuffer7_Unlock ( buffer );

	if ( FAILED ( ret ) )
	{
		debug_log ( "Unable to unlock hardware vertices: %s", get_d3d_error_message ( ret ) );
	}
}

void f3d_draw_vb(unsigned type, LPDIRECT3DVERTEXBUFFER7 buffer, unsigned start,
	unsigned total, unsigned short *indices, unsigned count)
{
	HRESULT
		ret;

	ret = IDirect3DDevice7_DrawIndexedPrimitiveVB ( d3d_data.device, (D3DPRIMITIVETYPE)type, buffer,
		start, total, indices, count, 0);

	if ( FAILED ( ret ) )
	{
		debug_log ( "Unable to draw indexed primitive: %s", get_d3d_error_message ( ret ) );
	}
}

void f3d_draw(unsigned type, LPDIRECT3DVERTEXBUFFER7 buffer, unsigned start,
	unsigned total)
{
	HRESULT
		ret;

	ret = IDirect3DDevice7_DrawPrimitiveVB ( d3d_data.device, (D3DPRIMITIVETYPE)type, buffer,
		start, total, 0);

	if ( FAILED ( ret ) )
	{
		debug_log ( "Unable to draw primitive: %s", get_d3d_error_message ( ret ) );
	}
}

void f3d_zbuffer_clear(float value)
{
	HRESULT
		ret;

	if ( d3d_data.device )
	{
		ret = IDirect3DDevice7_Clear ( d3d_data.device, 0, NULL, D3DCLEAR_ZBUFFER, 0, value, 0 );

		if ( ret != DD_OK )
		{
			debug_log ( "Unable to clear zbuffer: %s", get_d3d_error_message ( ret ) );
		}
	}
}

void f3d_render_state(unsigned state, unsigned data)
{
	HRESULT
		ret;

	ret = IDirect3DDevice7_SetRenderState ( d3d_data.device, (D3DRENDERSTATETYPE)state, data );

	if ( ret != DD_OK )
	{
		debug_log ( "Unable to set renderstate: %s", get_ddraw_error_message ( ret ) );
	}

}

void f3d_set_texture(unsigned stage, screen *texture)
{
	HRESULT
		ret;

	ret = IDirect3DDevice7_SetTexture ( d3d_data.device, stage,
		texture ? texture->surface : NULL );
	if ( ret != DD_OK )
	{
		debug_log ( "Unable to set texture: %s", get_ddraw_error_message ( ret ) );
	}
}

void f3d_set_texture_state(unsigned stage, unsigned state, unsigned data)
{
	HRESULT
		ret;

	ret = IDirect3DDevice7_SetTextureStageState ( d3d_data.device, (D3DTEXTURESTAGESTATETYPE)stage, (D3DTEXTURESTAGESTATETYPE)state, data );

	if ( ret != DD_OK )
	{
		debug_log ( "Unable to set texture: %s", get_ddraw_error_message ( ret ) );
	}
}

void f3d_set_material(D3DMATERIAL7 *material)
{
	HRESULT
		ret;

	ret = IDirect3DDevice7_SetMaterial ( d3d_data.device, material );

	if ( FAILED ( ret ) )
	{
		debug_log ( "Unable to set material: %s", get_ddraw_error_message ( ret ) );
	}
}

int f3d_scene_begin(void)
{
	HRESULT
		ret;

	ret = IDirect3DDevice7_BeginScene ( d3d_data.device );

	if ( FAILED ( ret ) )
	{
		debug_log ( "Unable to start 3d scene: %s", get_d3d_error_message ( ret ) );
		return FALSE;
	}

	return TRUE;
}

int f3d_scene_end(void)
{
	HRESULT
		ret;

	ret = IDirect3DDevice7_EndScene ( d3d_data.device );

	if ( FAILED ( ret ) )
	{
		debug_log ( "Unable to EndScene: %s", get_d3d_error_message ( ret ) );
		return FALSE;
	}

	return TRUE;
}

void f3d_palette_create(PALETTEENTRY *palette, LPDIRECTDRAWPALETTE *texture_palette)
{
	HRESULT
		ret;

	ret = IDirectDraw7_CreatePalette ( ddraw.ddraw, DDPCAPS_8BIT | DDPCAPS_ALLOW256,
		palette, texture_palette, NULL );
	if ( ret != DD_OK )
	{
		debug_log ( "Unable to create a texture palette: %s", get_ddraw_error_message ( ret ) );
	}
}

void f3d_palette_release(LPDIRECTDRAWPALETTE *texture_palette)
{
	HRESULT
		ret;

	ret = IDirectDrawPalette_Release ( *texture_palette );
	if ( ret != DD_OK )
	{
		debug_log ( "Unable to release palette: %s", get_ddraw_error_message ( ret ) );
	}
	*texture_palette = NULL;
}

int f3d_surface_create(LPDDSURFACEDESC2 ddsd, LPDIRECTDRAWSURFACE7 *surface)
{
	HRESULT
		ret;

	ret = IDirectDraw7_CreateSurface ( ddraw.ddraw, ddsd, surface, NULL );

	if ( ret != DD_OK )
	{
		debug_fatal ( "Unable to create texture surface: %s", get_ddraw_error_message ( ret ) );
		return FALSE;
	}
	return TRUE;
}

void f3d_surface_description(LPDIRECTDRAWSURFACE7 surface, LPDDSURFACEDESC2 ddsd)
{
	HRESULT
		ret;

	ddsd->dwSize = sizeof ( *ddsd );

	ret = IDirectDrawSurface7_GetSurfaceDesc ( surface, ddsd );

	if ( ret != DD_OK )
	{
		debug_fatal ( "Unable to get texture surface description: %s", get_ddraw_error_message ( ret ) );
	}
}

LPDIRECTDRAWSURFACE7 f3d_surface_front ( void )
{
	return ddraw.lpFrontBuffer;
}

LPDIRECTDRAWSURFACE7 f3d_surface_render ( void )
{
	return ddraw.lpRenderBuffer;
}

void f3d_surface_palette(LPDIRECTDRAWSURFACE7 surface, LPDIRECTDRAWPALETTE texture_palette)
{
	HRESULT
		ret;

	ret = IDirectDrawSurface7_SetPalette ( surface, texture_palette );
	if ( ret != DD_OK )
	{
		debug_fatal ( "Unable to set palette on texture: %s", get_ddraw_error_message ( ret ) );
	}
}

void f3d_surface_blt(LPDIRECTDRAWSURFACE7 primary, LPRECT rect1,
	LPDIRECTDRAWSURFACE7 secondary, LPRECT rect2, unsigned flags, LPDDBLTFX fx)
{
	HRESULT
		ret;

	ret = IDirectDrawSurface7_Blt ( primary, rect1, secondary, rect2, flags, fx );
	if ( ret != DD_OK )
	{
		debug_log ( "Unable to blt: %s", get_ddraw_error_message ( ret ) );
	}
}

void f3d_surface_release(LPDIRECTDRAWSURFACE7 *texture_surface)
{
	HRESULT
		ret;

	if ( *texture_surface )
	{
		ret = IDirectDrawSurface7_Release ( *texture_surface );
		if ( ret < DD_OK )
		{
			debug_log ( "Unable to release texture surface ( %d ): %s", ret, get_d3d_error_message ( ret ) );
		}
		else if ( ret > DD_OK )
		{
			debug_log ( "Unable to release texture surface, references: %d", ret );
		}
		*texture_surface = NULL;
	}
}

void f3d_clear_zbuffer(void)
{
	LPDIRECTDRAWSURFACEX
		zbuffer;

	if ( !active_screen )
	{
		return;
	}
	if ( active_screen == video_screen )
	{
		zbuffer = ddraw.lpZBuffer;
	}
	else
	{
		zbuffer = active_screen->zbuffer_surface;
	}
	if ( !zbuffer )
	{
		return;
	}
	{
		DDBLTFX
			fx;
		fx.dwSize = sizeof ( DDBLTFX );
		if ( application_video_colourdepth == 32 )
		{
			fx.dwFillDepth = 0xffffffff;
		}
		else
		{
			fx.dwFillDepth = 0xffff;
		}
		f3d_surface_blt ( ddraw.lpZBuffer, NULL, NULL, NULL, DDBLT_DEPTHFILL, &fx );
	}
}

void f3d_clear_screen(void)
{
	HRESULT
		ddrval;
	LPDIRECTDRAWSURFACEX
		surface;
	DDBLTFX
		fx;

	ASSERT ( active_screen );
	ASSERT ( active_screen->surface );

	if ( active_screen->render_texture_surface )
	{
		surface = active_screen->render_texture_surface;
	}
	else
	{
		surface = active_screen->surface;
	}
	fx.dwSize = sizeof ( fx );
	fx.dwFillColor = 0;
	ddrval = IDirectDrawSurface7_Blt ( surface, NULL, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &fx );
	if ( ddrval != DD_OK )
	{
		debug_log ( "Unable to blt during clear screen: %s", get_ddraw_error_message ( ddrval ) );
	}
}

int f3d_set_3d_render_target ( screen *this_screen )
{
	HRESULT
		ret;

	if ( d3d_data.recreate_d3d )
	{
		recreate_d3d ();
	}
	if ( this_screen == video_screen )
	{
		zbuffer_target_surface = f3d_surface_render ();
		ret = IDirect3DDevice7_SetRenderTarget ( d3d_data.device, this_screen->surface, 0 );
		if ( FAILED ( ret ) )
		{
			debug_log ( "Unable to set render target to video screen: %s", get_ddraw_error_message ( ret ) );
			return ( FALSE );
		}
		return ( TRUE );
	}
	else
	{
		zbuffer_target_surface = this_screen->render_texture_surface;
		ret = IDirect3DDevice7_SetRenderTarget ( d3d_data.device, this_screen->render_texture_surface, 0 );
		if ( FAILED ( ret ) )
		{
			debug_log ( "Unable to set render target to texture screen: %s", get_ddraw_error_message ( ret ) );
			return ( FALSE );
		}
		return ( TRUE );
	}
	return ( FALSE );
}

int f3d_enumerate_formats(HRESULT (CALLBACK *enumerate_texture_formats)(LPDDPIXELFORMAT, void*), void* context)
{
	HRESULT
		ret;

	ret = IDirect3DDevice7_EnumTextureFormats ( d3d_data.device, enumerate_texture_formats, context );

	if ( context != DD_OK )
	{
		debug_log ( "Error during texture format enumeration: %s", get_d3d_error_message ( ret ) );
		return ( FALSE );
	}

	return TRUE;
}

void f3d_evict_textures(void)
{
	HRESULT
		ret;

	ret = IDirect3D7_EvictManagedTextures ( d3d_data.d3d );

	if ( FAILED ( ret ) )
	{
		debug_log ( "Unable to evict managed textures: %s", get_ddraw_error_message ( ret ) );
	}
}

void f3d_texture_create(screen *texture, int width, int height, unsigned type, int number_of_mipmaps, int renderto)
{
	DDSURFACEDESC2
		ddsd;
	
	HRESULT
		ret;

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

	texture->type = (screen_format_types) type;
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

int f3d_texture_release(screen *texture)
{
	HRESULT
		ret;

	ASSERT ( texture );
	//ASSERT ( texture->surface );

	if ( texture->do_not_destroy )
	{
		return TRUE;
	}

	if ( !texture->clone_screen )
	{
		if ( texture->surface )
		{
			ddraw_destroy_surface ( texture->surface );
			texture->surface = NULL;
		}
		texture->palette = NULL;
	}

	if ( texture->usable_as_rendertarget )
	{
		ASSERT ( texture->zbuffer_surface );
		ASSERT ( texture->render_texture_surface );

		ret = IDirectDrawSurface7_DeleteAttachedSurface ( texture->render_texture_surface, 0, texture->zbuffer_surface );
		if ( FAILED ( ret ) )
		{
			debug_log ( "Unable to detach zbuffer: %s", get_ddraw_error_message ( ret ) );
		}

		ret = IDirectDrawSurface7_Release ( texture->render_texture_surface );
		if ( FAILED ( ret ) )
		{
			debug_log ( "Unable to release render surface: %s", get_ddraw_error_message ( ret ) );
		}

		ret = IDirectDrawSurface7_Release ( texture->zbuffer_surface );
		if ( FAILED ( ret ) )
		{
			debug_log ( "Unable to release zbuffer surface: %s", get_ddraw_error_message ( ret ) );
		}

		texture->zbuffer_surface = NULL;

		texture->render_texture_surface = NULL;
	}

	texture->used = FALSE;

	return ( TRUE );
}

void f3d_texture_restore(screen *texture)
{
	HRESULT
		ret;
	DDSURFACEDESC2
		ddsd;

	if ( ( texture->render_texture_surface ) && ( texture->zbuffer_surface ) )
	{
		//
		// Free up the surfaces
		//
		IDirectDrawSurface7_DeleteAttachedSurface ( texture->render_texture_surface, 0, NULL );
		IDirectDrawSurface7_Release ( texture->render_texture_surface );
		texture->render_texture_surface = NULL;
		IDirectDrawSurface7_Release ( texture->zbuffer_surface );
		texture->zbuffer_surface = NULL;
		//
		// Reallocate the surfaces
		//
		memset ( &ddsd, 0, sizeof ( ddsd ) );
		ddsd.dwSize = sizeof ( ddsd );
		memcpy ( &ddsd.ddpfPixelFormat, &texture_formats[ texture->type ].format, sizeof ( DDPIXELFORMAT ) );
		ddsd.dwSize = sizeof ( ddsd );
		ddsd.dwMipMapCount = 0;
		ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
		ddsd.ddsCaps.dwCaps = DDSCAPS_3DDEVICE;
		ddsd.dwHeight = texture->height;
		ddsd.dwWidth = texture->width;
		ddsd.ddsCaps.dwCaps3 = 0;
		ddsd.ddsCaps.dwCaps4 = 0;
		ddsd.ddsCaps.dwCaps2 = 0;
		ddsd.ddsCaps.dwCaps |= ( d3d_use_rgb_device ) ? ( DDSCAPS_SYSTEMMEMORY ) : ( DDSCAPS_VIDEOMEMORY | DDSCAPS_LOCALVIDMEM );
		ret = IDirectDraw7_CreateSurface ( ddraw.ddraw, &ddsd, &texture->render_texture_surface, NULL );
		if ( ret != DD_OK )
		{
			debug_fatal ( "Unable to create texture render surface: %s ( %d, %d )", get_ddraw_error_message ( ret ), texture->width, texture->height );
		}
		memset ( &ddsd, 0, sizeof ( ddsd ) );
		ddsd.dwSize = sizeof ( ddsd );
		f3d_surface_description ( ddraw.lpFrontBuffer, &ddsd );
		ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
		ddsd.ddsCaps.dwCaps = DDSCAPS_ZBUFFER;
		ddsd.ddsCaps.dwCaps |= ( d3d_use_rgb_device ) ? ( DDSCAPS_SYSTEMMEMORY ) : ( DDSCAPS_VIDEOMEMORY );
		ddsd.dwWidth = texture->width;
		ddsd.dwHeight = texture->height;
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

int f3d_texture_lock(screen *texture, int mipmap_level)
{

	int
		count;

	LPDIRECTDRAWSURFACEX
		texture_surface,
		next_level;

	HRESULT
		ddrval;

	DDSURFACEDESC2
		ddsd;

	ASSERT ( ddraw.ddraw );
	ASSERT ( texture );
	ASSERT ( texture->surface );
	ASSERT ( !texture->locked );

	texture_surface = texture->surface;

	for ( count = 0; count < mipmap_level; count++ )
	{

		DDSCAPS2
			ddscaps;

		memset ( &ddscaps, 0, sizeof ( ddscaps ) );

		ddscaps.dwCaps = DDSCAPS_TEXTURE | DDSCAPS_MIPMAP;

		ddrval = IDirectDrawSurface7_GetAttachedSurface ( texture_surface, &ddscaps, &next_level );

		if ( ddrval != DD_OK )
		{

			debug_log ( "Failed to get attached surface: %s", get_ddraw_error_message ( ddrval ) );

			memset ( &ddsd, 0, sizeof ( ddsd ) );

			ddsd.dwSize = sizeof ( ddsd );

			ddrval = IDirectDrawSurface7_GetSurfaceDesc ( texture_surface, &ddsd );

			if ( ddrval != DD_OK )
			{

				debug_log ( "Failed to get surface description: %s", get_ddraw_error_message ( ddrval ) );
			}
		
			debug_log ( "Failed to find mipmap %d, from %d levels: %s", count, ddsd.dwMipMapCount, get_ddraw_error_message ( ddrval ) );

			return ( FALSE );
		}

		if ( texture_surface != texture->surface )
		{

			IDirectDrawSurface7_Release ( texture_surface );
		}

		texture_surface = next_level;
	}


	ddsd.dwSize = sizeof ( ddsd );

	ddrval = IDirectDrawSurface7_GetSurfaceDesc ( texture_surface, &ddsd );

	if ( ddrval != DD_OK )
	{

		debug_log ( "Failed to get surface description of texture: %s", get_ddraw_error_message ( ddrval ) );

		return ( FALSE );
	}

	ddrval = IDirectDrawSurface7_Lock ( texture_surface, NULL, &ddsd, DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL );
		
	if ( ddrval != DD_OK )
	{

		debug_log ( "failed to lock texture: %s", get_ddraw_error_message ( ddrval ) );

		return ( FALSE );
	}

	texture->surface_locked = texture_surface;

	texture->locked = TRUE;

	texture->data = ddsd.lpSurface;

	texture->pitch = ddsd.lPitch;

	return ( TRUE );
}

int f3d_texture_unlock(screen *texture)
{

	HRESULT
		ddrval;

	ASSERT ( ddraw.ddraw );
	ASSERT ( texture );
	ASSERT ( texture->surface );
	ASSERT ( texture->surface_locked );
	ASSERT ( texture->locked );
	ASSERT ( texture->data );

	// Casm 16AUG05 Set the second argument to NULL - Thanks to Tamlin!
	ddrval = IDirectDrawSurface7_Unlock ( texture->surface_locked, NULL );

	if ( ddrval != DD_OK )
	{

		debug_log ( "Unable to unlock texture: %s", get_ddraw_error_message ( ddrval ) );

		return ( FALSE );
	}

	if ( texture->surface_locked != texture->surface )
	{

		IDirectDrawSurface7_Release ( texture->surface_locked );
	}

	texture->locked = FALSE;

	texture->surface_locked = NULL;

	texture->data = NULL;

	return ( TRUE );
}

void f3d_memory(unsigned long *total, unsigned long *free)
{
	DDSCAPS2
		caps;

	memset ( &caps, 0, sizeof ( caps ) );

	caps.dwCaps = DDSCAPS_TEXTURE | DDSCAPS_VIDEOMEMORY | DDSCAPS_LOCALVIDMEM;

	IDirectDraw7_GetAvailableVidMem ( ddraw.ddraw, &caps, total, free );
}

unsigned f3d_pixel_size(void)
{
	DDSURFACEDESC2
		ddsd;

	ASSERT ( ddraw.lpRenderBuffer );

	ddsd.dwSize = sizeof ( ddsd );

	IDirectDrawSurface7_GetSurfaceDesc ( ddraw.lpRenderBuffer, &ddsd );

	return ddsd.ddpfPixelFormat.dwRGBBitCount;
}

static int f3d_test_video_resolution_1(int width, int height, int depth)
{
	HRESULT
		ddrval;

	DDSURFACEDESC2
		ddsd;

	DDSCAPS2
		caps;

	//
	// Set the video mode
	//

	{
		int
			parms[3];
		parms[0] = width;
		parms[1] = height;
		parms[2] = depth;
		ddrval = system_thread_function ( ddraw_internal_set_display_mode, parms );
	}
	if ( ddrval != DD_OK )
	{
		debug_log ( "Unable to set display resolution: %d, %d, %d: %s", width, height, depth, get_ddraw_error_message ( ddrval ) );
		return ( FALSE );
	}

	//
	// Create the primary surface
	//
	memset ( &ddsd, 0, sizeof ( ddsd ) );
	ddsd.dwSize = sizeof (ddsd);
	ddsd.dwFlags = DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_3DDEVICE;
	//if ( ddraw.use_double_buffer )
	{
		ddsd.dwFlags |= DDSD_BACKBUFFERCOUNT;
		ddsd.dwBackBufferCount = 1;
		ddsd.ddsCaps.dwCaps |= DDSCAPS_FLIP | DDSCAPS_COMPLEX;
	}

	ddrval = IDirectDraw7_CreateSurface ( ddraw.ddraw, &ddsd, &ddraw.lpFrontBuffer, NULL);
	if ( ddrval != DD_OK )
	{
		debug_log ( "Unable to create primary surface: %s", get_ddraw_error_message ( ddrval ) );
		return ( FALSE );
	}

	//if ( ddraw.use_double_buffer )
	{
		//
		// Get the back screen from this surface.
		//
		memset ( &caps, 0, sizeof ( caps ) );
		caps.dwCaps = DDSCAPS_BACKBUFFER;
		ddrval = IDirectDrawSurface7_GetAttachedSurface ( ddraw.lpFrontBuffer, &caps, &ddraw.lpBackBuffer );
		if ( ddrval != DD_OK )
		{
			debug_log ( "Unable to get backbuffer: %s", get_ddraw_error_message ( ddrval ) );
			return ( FALSE );
		}
	}

	/*if ( ddraw.use_system_memory )
	{
		//
		// Create the system memory surface
		//
		memset ( &ddsd, 0, sizeof ( ddsd ) );
		ddsd.dwSize = sizeof( ddsd );
		ddrval = IDirectDrawSurface7_GetSurfaceDesc ( ddraw.lpFrontBuffer, &ddsd );
		ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE | DDSCAPS_SYSTEMMEMORY;
		ddsd.dwHeight = height;
		ddsd.dwWidth = width;
		ddrval = IDirectDraw7_CreateSurface ( ddraw.ddraw , &ddsd, &ddraw.lpRenderBuffer, NULL );
		if ( ddrval != DD_OK )
		{
			debug_log ( "Unable to create system memory surface: %s", get_ddraw_error_message ( ddrval ) );
			return ( FALSE );
		}
	}
	else*/
	{
		//
		// Set the render buffer
		//
		//if ( ddraw.use_double_buffer )
		{
			ddraw.lpRenderBuffer = ddraw.lpBackBuffer;
		}
		/*else
		{
			ddraw.lpRenderBuffer = ddraw.lpFrontBuffer;
		}*/
	}

	//if ( ddraw.use_z_buffer )
	{
		//
		// Create the zbuffer and attach it to the render buffer.
		//
		memset ( &ddsd, 0, sizeof ( ddsd ) );
		ddsd.dwSize = sizeof ( ddsd );
		ddrval = IDirectDrawSurface7_GetSurfaceDesc ( ddraw.lpFrontBuffer, &ddsd );
		ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
		ddsd.ddsCaps.dwCaps = DDSCAPS_ZBUFFER | DDSCAPS_VIDEOMEMORY;
		ddsd.dwHeight = height;
		ddsd.dwWidth = width;
		get_ddraw_zbuffer_pixel_format ( &ddsd.ddpfPixelFormat );
		ddrval = IDirectDraw7_CreateSurface ( ddraw.ddraw, &ddsd, &ddraw.lpZBuffer, NULL );
		if ( ddrval != DD_OK )
		{
			debug_log ( "Unable to create Zbuffer surface: %s", get_ddraw_error_message ( ddrval ) );
			return ( FALSE );
		}

		ddrval = IDirectDrawSurface7_AddAttachedSurface ( ddraw.lpRenderBuffer, ddraw.lpZBuffer );
		if ( ddrval != DD_OK )
		{
			debug_log ( "Unable to attach Zbuffer surface: %s", get_ddraw_error_message ( ddrval ) );
			return ( FALSE );
		}
	}

	application_video_width = width;
	application_video_height = height;

	return ( TRUE );
}

static void f3d_test_video_resolution_2(void)
{
	//
	// Free up the previous video mode's pointers
	//
	if ( ddraw.lpZBuffer )
	{
		if ( ddraw.lpRenderBuffer )
		{
			IDirectDrawSurface7_DeleteAttachedSurface ( ddraw.lpRenderBuffer, 0, ddraw.lpZBuffer );
		}
		IDirectDrawSurface7_Release ( ddraw.lpZBuffer );
		ddraw.lpZBuffer = NULL;
	}

	if ( ddraw.lpFrontBuffer )
	{
		//if ( ddraw.use_double_buffer )
		{
			if ( ddraw.lpBackBuffer )
			{
				IDirectDrawSurface7_Release ( ddraw.lpBackBuffer );
				ddraw.lpBackBuffer = NULL;
			}

			if ( ddraw.lpBackBuffer )
			{
				IDirectDrawSurface7_Release ( ddraw.lpBackBuffer );
				ddraw.lpBackBuffer = NULL;
			}
		}

		if ( ddraw.lpFrontBuffer )
		{
			IDirectDrawSurface7_Release ( ddraw.lpFrontBuffer );
			ddraw.lpFrontBuffer = NULL;
		}

		if ( ddraw.lpFrontBuffer )
		{
			IDirectDrawSurface7_Release ( ddraw.lpFrontBuffer );
			ddraw.lpFrontBuffer = NULL;
		}
	}

	/*if ( ddraw.use_system_memory )
	{
		if ( ddraw.lpRenderBuffer )
		{
			IDirectDrawSurface7_Release ( ddraw.lpRenderBuffer );
		}

		if ( ddraw.lpRenderBuffer )
		{
			IDirectDrawSurface7_Release ( ddraw.lpRenderBuffer );
		}
	}*/

	ddraw.lpRenderBuffer = NULL;
	ddraw.lpRenderBuffer = NULL;
}

int f3d_test_video_resolution(int width, int height, int depth)
{
	int
		result;

	f3d_test_video_resolution_2();
	result = f3d_test_video_resolution_1(width, height, depth);
	f3d_test_video_resolution_2();
	return result;
}

int f3d_enum_devices(LPDIRECTDRAWX ddraw, LPD3DENUMDEVICESCALLBACK7 enumerate_devices, LPVOID arg)
{
	HRESULT
		d3drval;
	LPDIRECT3DX
		lpD3D;

	d3drval = IDirectDraw7_QueryInterface ( ddraw, GUID_PREFIX IID_IDirect3D7, ( LPVOID FAR * ) &lpD3D );
	if ( d3drval != DD_OK )
	{
		return FALSE;
	}
	IDirect3D7_EnumDevices ( lpD3D, enumerate_devices, arg );
	IDirect3D7_Release ( lpD3D );
	return TRUE;
}

void f3d_context_set(void)
{
}

void f3d_context_leave(void)
{
}
