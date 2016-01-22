#ifndef OGRE_EE
#include "graphics.h"
#include "system.h"


static LPDIRECT3DSURFACE9
	render_surface,
	video_surface;



void f3d_set_light(unsigned index, D3DLIGHT9 *light)
{
	HRESULT
		res;

	res = IDirect3DDevice9_SetLight ( d3d_data.device[D3D_MAIN], index, light );

	if ( FAILED ( res ) )
	{
		debug_log ( "Unable to set light: %s", get_d3d_error_message ( res ) );
	}
}

void f3d_light_enable(unsigned index, unsigned state)
{
	HRESULT
		res;

	res = IDirect3DDevice9_LightEnable ( d3d_data.device[D3D_MAIN], index, state );

	if ( FAILED ( res ) )
	{
		debug_log ( "Unable to %sable light: %s", state ? "en" : "dis",
			get_d3d_error_message ( res ) );
	}
}

void f3d_set_transform(unsigned type, D3DMATRIX *matrix)
{
	HRESULT
		res;

	res = IDirect3DDevice9_SetTransform ( d3d_data.device[D3D_MAIN], ( D3DTRANSFORMSTATETYPE ) type, matrix );

	if ( FAILED ( res ) )
	{
		debug_log ( "Unable to set %u transfom: %s", type, get_d3d_error_message ( res ) );
	}
}

int f3d_set_viewport(D3DVIEWPORT9 *viewport)
{
	HRESULT
		res;

	res = IDirect3DDevice9_SetViewport ( d3d_data.device[D3D_MAIN], viewport );

	if ( res != D3D_OK )
	{
		debug_log ( "Unable to set viewport9: %s", get_d3d_error_message ( res ) );
		return FALSE;
	}

	return TRUE;
}

void f3d_vertex_create(unsigned size, unsigned fvf, LPDIRECT3DVERTEXBUFFER9 *buffer)
{
	HRESULT
		res;

	res = IDirect3DDevice9_CreateVertexBuffer ( d3d_data.device[D3D_MAIN], size, 0, fvf, D3DPOOL_MANAGED, buffer, NULL );

	if ( FAILED ( res ) )
	{
		debug_fatal ( "Unable to create vertex buffer: %s", get_d3d_error_message ( res ) );
	}
}

void f3d_vertex_release(LPDIRECT3DVERTEXBUFFER9 *buffer)
{
	HRESULT
		res;

	ASSERT ( buffer );

	if ( *buffer )
	{
		res = IDirect3DVertexBuffer9_Release ( *buffer );

		if ( FAILED ( res ) )
		{
			debug_log ( "Unable to release primary vertex buffer: %s", get_d3d_error_message ( res ) );
		}
	}

	*buffer = NULL;
}


void f3d_vertex_lock(LPDIRECT3DVERTEXBUFFER9 buffer, unsigned flags, void **ptr)
{
	HRESULT
		res;

	ASSERT ( buffer );

	res = IDirect3DVertexBuffer9_Lock ( buffer, 0, 0, ptr, flags );

	if ( FAILED ( res ) )
	{
		debug_fatal ( "Unable to lock vertex buffer: %s", get_d3d_error_message ( res ) );
	}
}

void f3d_vertex_unlock(LPDIRECT3DVERTEXBUFFER9 buffer)
{
	HRESULT
		res;

	ASSERT ( buffer );

	res = IDirect3DVertexBuffer9_Unlock ( buffer );

	if ( FAILED ( res ) )
	{
		debug_log ( "Unable to unlock hardware vertices: %s", get_d3d_error_message ( res ) );
	}
}

void f3d_index_create(unsigned size, LPDIRECT3DINDEXBUFFER9 *ibuffer)
{
	HRESULT
		res;

	ASSERT ( ibuffer );

	res = IDirect3DDevice9_CreateIndexBuffer ( d3d_data.device[D3D_MAIN], size * sizeof ( unsigned short ), D3DUSAGE_SOFTWAREPROCESSING, D3DFMT_INDEX16, D3DPOOL_MANAGED, ibuffer, NULL );

	if ( FAILED ( res ) )
	{
		debug_fatal ( "Unable to create index buffer: %s", get_d3d_error_message ( res ) );
	}
}

void f3d_index_release(LPDIRECT3DINDEXBUFFER9 *ibuffer)
{
	HRESULT
		res;

	ASSERT ( ibuffer );

	if ( *ibuffer )
	{
		res = IDirect3DIndexBuffer9_Release ( *ibuffer );

		if ( FAILED ( res ) )
		{
			debug_log ( "Unable to release index buffer: %s", get_d3d_error_message ( res ) );
		}
	}

	*ibuffer = NULL;
}

void f3d_index_lock(LPDIRECT3DINDEXBUFFER9 ibuffer, unsigned flags, unsigned short **ptr)
{
	HRESULT
		res;

	ASSERT ( ibuffer );

	res = IDirect3DIndexBuffer9_Lock ( ibuffer, 0, 0, ( LPVOID * ) ptr, flags );

	if ( FAILED ( res ) )
	{
		debug_fatal ( "Unable to lock index buffer: %s", get_d3d_error_message ( res ) );
	}
}

void f3d_index_unlock(LPDIRECT3DINDEXBUFFER9 ibuffer)
{
	HRESULT
		res;

	ASSERT ( ibuffer );

	res = IDirect3DIndexBuffer9_Unlock ( ibuffer );

	if ( FAILED ( res ) )
	{
		debug_log ( "Unable to unlock index buffer: %s", get_d3d_error_message ( res ) );
	}
}

void f3d_dip(unsigned type, LPDIRECT3DVERTEXBUFFER9 buffer, unsigned vstart, unsigned vtotal, LPDIRECT3DINDEXBUFFER9 ibuffer, unsigned istart, unsigned primitives, unsigned fvf, unsigned stride)
{
	HRESULT
		res;

	ASSERT ( buffer );
	ASSERT ( ibuffer );
	ASSERT ( fvf && stride );

	if ( !vtotal || !primitives )
	{
		return;
	}

	res = IDirect3DDevice9_SetIndices ( d3d_data.device[D3D_MAIN], ibuffer );

	if ( FAILED ( res ) )
	{
		debug_log ( "Unable to set indices: %s", get_d3d_error_message ( res ) );
	}

	res = IDirect3DDevice9_SetStreamSource ( d3d_data.device[D3D_MAIN], 0, buffer, 0, stride );

	if ( FAILED ( res ) )
	{
		debug_log ( "Unable to set stream source: %s", get_d3d_error_message ( res ) );
	}

	res = IDirect3DDevice9_SetFVF ( d3d_data.device[D3D_MAIN], fvf );

	if ( FAILED ( res ) )
	{
		debug_log ( "Unable to set fvf: %s", get_d3d_error_message ( res ) );
	}

	res = IDirect3DDevice9_DrawIndexedPrimitive ( d3d_data.device[D3D_MAIN], ( D3DPRIMITIVETYPE ) type, vstart, 0, vtotal, istart, primitives );

	if ( FAILED ( res ) )
	{
		debug_log ( "Unable to draw indexed primitive: %s", get_d3d_error_message ( res ) );
	}

	res = IDirect3DDevice9_SetIndices ( d3d_data.device[D3D_MAIN], NULL );

	if ( FAILED ( res ) )
	{
		debug_log ( "Unable to set indices: %s", get_d3d_error_message ( res ) );
	}
}

void f3d_dp(unsigned type, LPDIRECT3DVERTEXBUFFER9 buffer, unsigned vstart, unsigned primitives, unsigned fvf, unsigned stride)
{
	HRESULT
		res;

	ASSERT ( buffer );
	ASSERT ( fvf && stride );

	if ( !primitives )
	{
		return;
	}

	res = IDirect3DDevice9_SetStreamSource ( d3d_data.device[D3D_MAIN], 0, buffer, 0, stride );

	if ( FAILED ( res ) )
	{
		debug_log ( "Unable to set stream source: %s", get_d3d_error_message ( res ) );
	}

	res = IDirect3DDevice9_SetFVF ( d3d_data.device[D3D_MAIN], fvf );

	if ( FAILED ( res ) )
	{
		debug_log ( "Unable to set fvf: %s", get_d3d_error_message ( res ) );
	}

	res = IDirect3DDevice9_DrawPrimitive ( d3d_data.device[D3D_MAIN], ( D3DPRIMITIVETYPE ) type, vstart, primitives );

	if ( FAILED ( res ) )
	{
		debug_log ( "Unable to draw primitive: %s", get_d3d_error_message ( res ) );
	}
}

void f3d_render_state(unsigned state, unsigned data)
{
	HRESULT
		res;

	res = IDirect3DDevice9_SetRenderState ( d3d_data.device[D3D_MAIN], ( D3DRENDERSTATETYPE ) state, data );

	if ( FAILED ( res ) )
	{
		debug_log ( "Unable to set renderstate: %s", get_d3d_error_message ( res ) );
	}

}

void f3d_set_texture(unsigned stage, screen *texture)
{
	HRESULT
		res;

	res = IDirect3DDevice9_SetTexture ( d3d_data.device[D3D_MAIN], stage, texture ? ( LPDIRECT3DBASETEXTURE9 ) texture->texture : NULL );
	if ( FAILED ( res ) )
	{
		debug_log ( "Unable to set texture: %s", get_d3d_error_message ( res ) );
	}
}

void f3d_set_texture_state(unsigned stage, unsigned state, unsigned data)
{
	HRESULT
		res;

	res = IDirect3DDevice9_SetTextureStageState ( d3d_data.device[D3D_MAIN], stage, ( D3DTEXTURESTAGESTATETYPE ) state, data );

	if ( FAILED ( res ) )
	{
		debug_log ( "Unable to set texture: %s", get_d3d_error_message ( res ) );
	}
}

void f3d_set_sampler_state(unsigned sampler, unsigned type, unsigned data)
{
	HRESULT
		res;

	res = IDirect3DDevice9_SetSamplerState ( d3d_data.device[D3D_MAIN], sampler, ( D3DSAMPLERSTATETYPE ) type, data );

	if ( FAILED ( res ) )
	{
		debug_log ( "Unable to set texture: %s", get_d3d_error_message ( res ) );
	}
}

void f3d_set_material(D3DMATERIAL9 *material)
{
	HRESULT
		res;

	res = IDirect3DDevice9_SetMaterial ( d3d_data.device[D3D_MAIN], material );

	if ( FAILED ( res ) )
	{
		debug_log ( "Unable to set material: %s", get_d3d_error_message ( res ) );
	}
}

int f3d_scene_begin(void)
{
	HRESULT
		res;

	res = IDirect3DDevice9_BeginScene ( d3d_data.device[D3D_MAIN] );

	if ( FAILED ( res ) )
	{
		debug_log ( "Unable to start 3d scene: %s", get_d3d_error_message ( res ) );
		return FALSE;
	}

	return TRUE;
}

int f3d_scene_end(void)
{
	HRESULT
		res;

	res = IDirect3DDevice9_EndScene ( d3d_data.device[D3D_MAIN] );

	if ( FAILED ( res ) )
	{
		debug_log ( "Unable to EndScene: %s", get_d3d_error_message ( res ) );
		return FALSE;
	}

	return TRUE;
}

void f3d_clear_zbuffer(void)
{
	HRESULT
		res;

	res = IDirect3DDevice9_Clear ( d3d_data.device[D3D_MAIN], 0, NULL, D3DCLEAR_ZBUFFER, 0, 1.0f, 0 );
	if ( FAILED ( res ) )
	{
		debug_log ( "Unable to clear zbuffer: %s", get_d3d_error_message ( res ) );
	}
}

void f3d_clear_screen(unsigned color)
{
	HRESULT
		res;

	res = IDirect3DDevice9_Clear ( d3d_data.device[D3D_MAIN], 0, NULL, D3DCLEAR_TARGET, color, 0.0f, 0 );
	if ( FAILED ( res ) )
	{
		debug_log ( "Unable to clear screen: %s", get_d3d_error_message ( res ) );
	}
}


int f3d_set_3d_render_target ( screen *this_screen )
{
	HRESULT
		res;

	ASSERT ( this_screen );
	ASSERT ( this_screen->role == TEXTURE_ROLE_RENDER_TARGET );

	if ( d3d_common.recreate_d3d )
	{
		recreate_d3d ();
	}
	if ( this_screen == video_screen )
	{
		if ( video_surface )
		{
			res = IDirect3DDevice9_SetRenderTarget ( d3d_data.device[D3D_MAIN], 0, video_surface );
			if ( FAILED ( res ) )
			{
				debug_fatal ( "Unable to set render target to video screen: %s", get_d3d_error_message ( res ) );
			}

			IDirect3DSurface9_Release ( video_surface );

			video_surface = NULL;
		}
	}
	else
	{
		ASSERT ( !video_surface );
		ASSERT ( !render_surface );

		res = IDirect3DDevice9_GetRenderTarget ( d3d_data.device[D3D_MAIN], 0, &video_surface );
		if ( FAILED ( res ) )
		{
			debug_log ( "Unable to get render target: %s", get_d3d_error_message ( res ) );
			return FALSE;
		}

		res = IDirect3DTexture9_GetSurfaceLevel ( this_screen->texture, 0, &render_surface );
		if ( FAILED ( res ) )
		{
			debug_log ( "Unable to get surface: %s", get_d3d_error_message ( res ) );

			IDirect3DSurface9_Release ( video_surface );

			video_surface = NULL;

			return FALSE;
		}

		res = IDirect3DDevice9_SetRenderTarget ( d3d_data.device[D3D_MAIN], 0, render_surface );
		if ( FAILED ( res ) )
		{
			debug_log ( "Unable to set render target to texture screen: %s", get_d3d_error_message ( res ) );

			IDirect3DSurface9_Release ( render_surface );

			render_surface = NULL;

			IDirect3DSurface9_Release ( video_surface );

			video_surface = NULL;

			return FALSE;
		}
	}
	return TRUE;
}

void f3d_stop_3d_render_target ( screen *this_screen )
{
	ASSERT ( this_screen );
	ASSERT ( this_screen != video_screen );
	ASSERT ( render_surface );
	ASSERT ( !this_screen->data );

	IDirect3DSurface9_Release ( render_surface );

	render_surface = NULL;
}

void f3d_texture_create(screen *texture, int width, int height, int number_of_mipmaps, enum TEXTURE_ROLE role)
{
	HRESULT
		res;

	ASSERT ( texture );
	ASSERT ( number_of_mipmaps || role != TEXTURE_ROLE_RENDER_TARGET);
	ASSERT ( role == TEXTURE_ROLE_STATIC_RGBX || role == TEXTURE_ROLE_STATIC_RGBA || number_of_mipmaps == 1 );

	texture->width = width;
	texture->height = height;
	texture->number_of_mipmaps = number_of_mipmaps;
	texture->role = role;
	texture->contains_alpha = role == TEXTURE_ROLE_STATIC_RGBA || role == TEXTURE_ROLE_DYNAMIC_RGBA;
	texture->texture = NULL;
	texture->data = NULL;

	res = IDirect3DDevice9_CreateTexture ( d3d_data.device[D3D_MAIN], width, height, number_of_mipmaps, role == TEXTURE_ROLE_RENDER_TARGET ? D3DUSAGE_RENDERTARGET : number_of_mipmaps ? 0 : D3DUSAGE_AUTOGENMIPMAP, texture->contains_alpha ? D3DFMT_A8R8G8B8 : D3DFMT_X8R8G8B8, role == TEXTURE_ROLE_RENDER_TARGET ? D3DPOOL_DEFAULT : D3DPOOL_MANAGED, &texture->texture, NULL );

	if ( FAILED ( res ) )
	{
		debug_fatal ( "Unable to create texture: %s ( %d, %d )", get_d3d_error_message ( res ), width, height );
	}
}

void f3d_texture_release(screen *texture)
{
	ASSERT ( texture );
	ASSERT ( !texture->data );

	if ( texture->texture )
	{
		IDirect3DTexture9_Release ( texture->texture );

		texture->texture = NULL;
	}
}

void f3d_texture_pre(screen *texture)
{
	if ( texture->texture && texture->role == TEXTURE_ROLE_RENDER_TARGET )
	{
		IDirect3DTexture9_Release ( texture->texture );

		texture->texture = NULL;
	}
}

void f3d_texture_post(screen *texture)
{
	HRESULT
		res;

	if ( texture->texture )
		return;

	ASSERT ( texture->role == TEXTURE_ROLE_RENDER_TARGET );

	res = IDirect3DDevice9_CreateTexture ( d3d_data.device[D3D_MAIN], texture->width, texture->height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &texture->texture, NULL );
	if ( FAILED ( res ) )
	{
		debug_fatal ( "Unable to create texture: %s ( %d, %d )", get_d3d_error_message ( res ), texture->width, texture->height );
	}
}

int f3d_texture_lock(screen *texture, int mipmap_level)
{
	HRESULT
		res;

	D3DLOCKED_RECT
		rect;

	ASSERT ( texture );

	if ( texture == video_screen )
	{
		LPDIRECT3DSURFACE9
			surface,
			backbuffer;

		ASSERT ( !texture->texture );
		ASSERT ( !mipmap_level );

#if 1
		res = IDirect3DDevice9_CreateOffscreenPlainSurface ( d3d_data.device[D3D_MAIN], d3d_data.d3dpp[D3D_MAIN].BackBufferWidth, d3d_data.d3dpp[D3D_MAIN].BackBufferHeight, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &surface, NULL );
#else
		res = IDirect3DDevice9_CreateOffscreenPlainSurface ( d3d_data.device[D3D_MAIN], d3d_data.d3dpp[D3D_MAIN].BackBufferWidth, d3d_data.d3dpp[D3D_MAIN].BackBufferHeight, D3DFMT_X8R8G8B8, D3DPOOL_SYSTEMMEM, &surface, NULL );
#endif
		if ( FAILED ( res ) )
		{
			debug_log ( "Failed to create offscreen surface: %s", get_d3d_error_message ( res ) );

			return FALSE;
		}

#if 1
		backbuffer = NULL;
		res = IDirect3DDevice9_GetFrontBufferData ( d3d_data.device[D3D_MAIN], 0, surface );

		if ( FAILED ( res ) )
		{
			debug_log ( "Failed to get frontbuffer data: %s", get_d3d_error_message ( res ) );

			IDirect3DSurface9_Release ( surface );

			return FALSE;
		}
#else
		res = IDirect3DDevice9_GetBackBuffer ( d3d_data.device[D3D_MAIN], 0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer );

		if ( FAILED ( res ) )
		{
			debug_log ( "Failed to get backbuffer: %s", get_d3d_error_message ( res ) );

			IDirect3DSurface9_Release ( surface );

			return FALSE;
		}

		res = IDirect3DDevice9_GetRenderTargetData ( d3d_data.device[D3D_MAIN], backbuffer, surface );

		IDirect3DSurface9_Release ( backbuffer );

		if ( FAILED ( res ) )
		{
			debug_log ( "Failed to get rendertardet data: %s", get_d3d_error_message ( res ) );

			IDirect3DSurface9_Release ( surface );

			return FALSE;
		}
#endif

		res = IDirect3DSurface9_LockRect ( surface, &rect, NULL, 0 );

		if ( FAILED ( res ) )
		{
			debug_log ( "Failed to lock surface: %s ( %d )", get_d3d_error_message ( res ) );

			IDirect3DSurface9_Release ( surface );

			return FALSE;
		}

		texture->texture = ( LPDIRECT3DTEXTURE9 ) surface;
	}
	else
	{
		ASSERT ( texture->texture );
		ASSERT ( texture->role != TEXTURE_ROLE_RENDER_TARGET );
		ASSERT ( !texture->data );

		res = IDirect3DTexture9_LockRect ( texture->texture, mipmap_level, &rect, NULL, 0 );

		if ( FAILED ( res ) )
		{
			debug_log ( "Failed to lock texture: %s ( %d )", get_d3d_error_message ( res ), mipmap_level );

			return FALSE;
		}
	}

	texture->mipmap = mipmap_level;

	texture->data = ( unsigned int * ) rect.pBits;

	ASSERT ( !( rect.Pitch & 3 ) );
	texture->pitch = rect.Pitch >> 2;

	return TRUE;
}

int f3d_texture_unlock(screen *texture)
{
	HRESULT
		res;

	ASSERT ( texture );
	ASSERT ( texture->texture );
	ASSERT ( texture->data );

	if ( texture == video_screen )
	{
		LPDIRECT3DSURFACE9
			surface;

		surface = ( LPDIRECT3DSURFACE9 ) texture->texture;

		res = IDirect3DSurface9_UnlockRect ( surface );

		if ( FAILED ( res ) )
		{
			debug_log ( "Unable to unlock surface: %s", get_d3d_error_message ( res ) );

			return FALSE;
		}

		IDirect3DSurface9_Release ( surface );

		texture->texture = NULL;
	}
	else
	{
		res = IDirect3DTexture9_UnlockRect ( texture->texture, texture->mipmap );

		if ( FAILED ( res ) )
		{
			debug_log ( "Unable to unlock texture: %s ( %d )", get_d3d_error_message ( res ), texture->mipmap );

			return FALSE;
		}
	}

	texture->data = NULL;

	return TRUE;
}
#endif
