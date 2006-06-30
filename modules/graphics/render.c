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

BOOL initialise_graphics_rendering_system ( void )
{

	initialise_direct_3d ();

	initialise_texture_system ();

	set_fpu_rounding_mode_zero ();

	return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define COBJMACROS 1

/*
#include "mmstream.h"
#include "amstream.h"
#include "ddstream.h"
*/

void play_avi ( const char *filename, int exit_key )
{
/*
	IAMMultiMediaStream
		*pAMStream;

	WCHAR
		wPath[512];

	IMediaStream
		*pPrimaryVidStream = NULL;

	IDirectDrawMediaStream
		*pDDStream = NULL;

	IDirectDrawSurface7
		*pSurface = NULL;

	IDirectDrawStreamSample
		*pSample = NULL;

	RECT
		rect;

	screen
		*texture_screen;

	HRESULT
		ret;

	ASSERT ( strlen ( filename ) < 512 );

	CoCreateInstance ( &CLSID_AMMultiMediaStream, NULL, CLSCTX_INPROC_SERVER, &IID_IAMMultiMediaStream, ( void ** ) &pAMStream );

	ret = IAMMultiMediaStream_Initialize ( pAMStream, STREAMTYPE_READ, 0, NULL );

	if ( FAILED ( ret ) )
	{

		debug_log ( "Unable to initialise multimedia stream" );

		IAMMultiMediaStream_Release ( pAMStream );

		return;
	}

	ret = IAMMultiMediaStream_AddMediaStream ( pAMStream, ( IUnknown __RPC_FAR *) ddraw.ddraw, &MSPID_PrimaryVideo, 0, NULL );

	if ( FAILED ( ret ) )
	{

		debug_log ( "Unable to add primary video media stream" );

		IAMMultiMediaStream_Release ( pAMStream );

		return;
	}

	ret = IAMMultiMediaStream_AddMediaStream ( pAMStream, NULL, &MSPID_PrimaryAudio, AMMSF_ADDDEFAULTRENDERER, NULL );

	if ( FAILED ( ret ) )
	{

		debug_log ( "Unable to add audio media stream" );

		IAMMultiMediaStream_Release ( pAMStream );

		return;
	}

	MultiByteToWideChar ( CP_ACP, 0, filename, -1, wPath, sizeof ( wPath ) / sizeof ( wPath[0] ) );

	ret = IAMMultiMediaStream_OpenFile ( pAMStream, wPath, 0 );

	if ( FAILED ( ret ) )
	{

		debug_log ( "Unable to open multimedia file" );

		IAMMultiMediaStream_Release ( pAMStream );

		return;
	}

   ret = IAMMultiMediaStream_GetMediaStream ( pAMStream, &MSPID_PrimaryVideo, &pPrimaryVidStream );

	if ( FAILED ( ret ) )
	{

		debug_log ( "Unable toget a media stream" );

		IAMMultiMediaStream_Release ( pAMStream );

		return;
	}

   ret = IMediaStream_QueryInterface ( pPrimaryVidStream, &IID_IDirectDrawMediaStream, (void **) &pDDStream );

	if ( FAILED ( ret ) )
	{

		debug_log ( "Unable to QI video stream to get audio stream" );

		IAMMultiMediaStream_Release ( pAMStream );

		IMediaStream_Release ( pPrimaryVidStream );

		return;
	}

   ret = IDirectDrawMediaStream_CreateSample ( pDDStream, NULL, NULL, 0, &pSample);

	if ( FAILED ( ret ) )
	{

		debug_log ( "Unable to create a surface" );

		IAMMultiMediaStream_Release ( pAMStream );

		IMediaStream_Release ( pPrimaryVidStream );

		return;
	}

   ret = IDirectDrawStreamSample_GetSurface ( pSample, ( LPDIRECTDRAWSURFACE * ) &pSurface, &rect );
    
	if ( FAILED ( ret ) )
	{

		debug_log ( "Unable to get a surface" );

		IDirectDrawStreamSample_Release ( pSample );

		IAMMultiMediaStream_Release ( pAMStream );

		IMediaStream_Release ( pPrimaryVidStream );

		return;
	}

	ret = IDirectDrawStreamSample_SetRect ( pSample, &rect );

	if ( FAILED ( ret ) )
	{

		debug_log ( "Unable to set a rect" );

		IDirectDrawStreamSample_Release ( pSample );

		IAMMultiMediaStream_Release ( pAMStream );

		IMediaStream_Release ( pPrimaryVidStream );

		return;
	}

   ret = IAMMultiMediaStream_SetState ( pAMStream, STREAMSTATE_RUN );

	if ( FAILED ( ret ) )
	{

		debug_log ( "Unable to start a multimedia file" );

		IDirectDrawStreamSample_Release ( pSample );

		IAMMultiMediaStream_Release ( pAMStream );

		IMediaStream_Release ( pPrimaryVidStream );

		return;
	}

	texture_screen = create_user_texture_screen ( 256, 256, SCREEN_FORMAT_TYPE_VIDEOSCREEN, 0 );

	while ( TRUE )
	{

		if ( IDirectDrawStreamSample_Update ( pSample, 0, NULL, NULL, 0 ) != S_OK )
		{

			break;
		}

		{

			IDirectDrawSurface7_Blt ( ddraw.lpRenderBuffer, NULL, pSurface, &rect, DDBLT_WAIT, NULL );
//			IDirectDrawSurface7_Blt ( texture_screen->surface, NULL, pSurface, &rect, DDBLT_WAIT, NULL );
			if ( begin_3d_scene () )
			{
		
				vertex
					quad[4];
		
				real_colour
					colour,
					specular;
		
				colour.red = 255;
				colour.green = 0;
				colour.blue = 255;
				colour.alpha = 255;
		
				specular.red = 0;
				specular.green = 0;
				specular.blue = 0;
				specular.alpha = 255;
		
				quad[0].i = 50;
				quad[0].j = 50;
				quad[0].z = 10;
				quad[0].q = 0.1;
				quad[0].u = 0;
				quad[0].v = 0;
				quad[0].next_vertex = &quad[1];
		
				quad[1].i = 306;
				quad[1].j = 50;
				quad[1].z = 10;
				quad[1].q = 0.1;
				quad[1].u = 1;
				quad[1].v = 0;
				quad[1].next_vertex = &quad[2];
		
				quad[2].i = 306;
				quad[2].j = 306;
				quad[2].z = 10;
				quad[2].q = 0.1;
				quad[2].u = 1;
				quad[2].v = 1;
				quad[2].next_vertex = &quad[3];
		
				quad[3].i = 50;
				quad[3].j = 306;
				quad[3].z = 10;
				quad[3].q = 0.1;
				quad[3].u = 0;
				quad[3].v = 1;
				quad[3].next_vertex = NULL;
		
				set_d3d_zbuffer_comparison ( FALSE );
				set_d3d_zbuffer_writing ( FALSE );

				set_d3d_flat_shaded_textured_renderstate ( texture_screen );
		
				set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP );
				set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP );
		
				set_d3d_texture_stage_state ( 0, D3DTSS_MAGFILTER, D3DTFG_POINT );
				set_d3d_texture_stage_state ( 0, D3DTSS_MINFILTER, D3DTFG_POINT );
				set_d3d_texture_stage_state ( 0, D3DTSS_MIPFILTER, D3DTFP_NONE );
		
				draw_wbuffered_flat_shaded_textured_polygon ( quad, colour, specular );
		
				end_3d_scene ();
			}
			

			ddraw_flip_surface ();
		}
	}

	destroy_screen ( texture_screen );

	IDirectDrawStreamSample_Release ( pSample );

	IAMMultiMediaStream_Release ( pAMStream );

	IMediaStream_Release ( pPrimaryVidStream );

	return; */
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
