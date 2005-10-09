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

#define DEBUG_MODULE 0

#define REPORT_SCENE_BREAKS 0

#define USE_D3D_SOFTWARE_TNL 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// All the Direct3D objects and flags
//

struct DIRECT_3D_DATA
	d3d;

int
	d3d_override_render_to_texture = FALSE,
	d3d_use_rgb_device = FALSE,
	d3d_initialised = FALSE,
	d3d_valid = FALSE,
	d3d_in_3d_scene = FALSE;

int
	d3d_number_of_executions,
	d3d_number_of_texture_loads;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static BOOL initialise_direct_3d_driver ( void );

static void ( *restore_vb_friend_function ) ( void ) = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// Flags for the 3d visual to take note of
//

int

	//
	// We can only use square textures if this flag is TRUE
	//

	d3d_square_only_textures,

	//
	// We can't gouraud shade alpha component if this flag is TRUE
	//

	d3d_flat_only_alpha,

	//
	// We can't do table fog if this flag is TRUE
	//

	d3d_vertex_only_fog,

	//
	// We  can't do mipmapping
	//

	d3d_mipmap_textures,

	//
	// We can/can't do texturing from video memory
	//

	d3d_texture_video_memory,

	//
	// We can/can't do texturing from system memory
	//

	d3d_texture_system_memory,

	//
	// We can use vertices from video memory
	//

	d3d_vertex_buffer_in_video_memory,

	//
	// Can modulate colours on textures
	//

	d3d_modulate,

	//
	// Can modulate alpha on textures
	//

	d3d_modulate_alpha,

	//
	// Can render textured lines
	//

	d3d_textured_lines,

	//
	// Can do tri-linear texture filtering
	//

	d3d_trilinear_filtering,

	//
	// Texture dimension limits
	//

	d3d_minimum_texture_width,
	d3d_minimum_texture_height,
	d3d_maximum_texture_width,
	d3d_maximum_texture_height,

	//
	// Use the DX pipeline ( possibly hardware accelerated )
	//

	d3d_use_dx_pipeline = FALSE,

	//
	// Can render to a texture
	//

	d3d_can_render_to_texture = TRUE,

	//
	// Hardware TnL is available
	//

	d3d_using_hardware_tnl,

	//
	// Hardware video memory available
	//

	d3d_total_video_memory,

	d3d_total_video_texture_memory,

	//
	// Permedia2 detection
	//

	d3d_using_permedia2_chipset;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL initialise_direct_3d ( void )
{

	int
		count;


	for ( count = 0; count < 256; count++ )
	{

		application_colour_table[count].peFlags |= D3DPAL_READONLY;
	}

	ASSERT ( get_graphics_system_initialised () );

	register_exit_function ( d3d_release_objects );

	//
	// Create the 3d device
	//

	initialise_direct_3d_driver ();

	//
	// Create the vertex buffers
	//

	create_d3d_vertex_buffers ();

	//
	// Register the restore routine.
	//

	register_post_activate_message_function ( d3d_restore_objects );

	//
	//
	//

	d3d.recreate_d3d = FALSE;

	return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void register_restore_vb_routine ( void ( *function ) ( void ) )
{

	ASSERT ( !restore_vb_friend_function );

	restore_vb_friend_function = function;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL check_valid_direct_3d_device_exists ( void )
{
	/*

	D3DFINDDEVICESEARCH
		device_search_capabilities;

	D3DFINDDEVICERESULT
		device_search_result;

	HRESULT
		ret;

	//
	// We only match to hardware RGB drivers, with the following constraints:
	//
	//
	// Compulsory features necessary to run the game:
	//
	//		CULL NONE
	//
	//		ZCOMPARE ALWAYS & ZCOMPARE GREATEREQUAL
	//
	//		SRCBLEND SRCALPHA
	//		DESTBLEND INVSRCALPHA
	//
	//		ALPHA FLAT BLEND
	//		COLOUR FLAT RGB
	//		COLOUR GOURAUD RGB
	//
	//		TEXTURE ALPHA & TEXTURE PERSPECTIVE
	//
	//		TEXTURE BLEND MODULATE & TEXTURE BLEND MODULATE ALPHA
	//
	//
	// After finding the 3d device, we have to check for the following:
	//
	//		Fog is supported as either fog table, or fog vertex.
	//


	//
	// Set the size of the structures we are using.
	//

	device_search_capabilities.dwSize = sizeof ( D3DFINDDEVICESEARCH );

	device_search_result.dwSize = sizeof ( D3DFINDDEVICERESULT );

	device_search_capabilities.dwFlags = (
														D3DFDS_COLORMODEL | D3DFDS_DSTBLENDCAPS | D3DFDS_HARDWARE |
														D3DFDS_LINES | D3DFDS_MISCCAPS | D3DFDS_SHADECAPS |
														D3DFDS_SRCBLENDCAPS | D3DFDS_TEXTUREBLENDCAPS | D3DFDS_TEXTURECAPS |
														D3DFDS_TRIANGLES | D3DFDS_ZCMPCAPS
														);

	device_search_capabilities.bHardware = TRUE;

	device_search_capabilities.dcmColorModel = D3DCOLOR_RGB;

	device_search_capabilities.dpcPrimCaps.dwSize = sizeof ( D3DPRIMCAPS );

	device_search_capabilities.dpcPrimCaps.dwMiscCaps = D3DPMISCCAPS_CULLNONE;


	device_search_capabilities.dpcPrimCaps.dwZCmpCaps = D3DPCMPCAPS_ALWAYS | D3DPCMPCAPS_GREATEREQUAL;

	device_search_capabilities.dpcPrimCaps.dwSrcBlendCaps = D3DPBLENDCAPS_SRCALPHA;

	device_search_capabilities.dpcPrimCaps.dwDestBlendCaps = D3DPBLENDCAPS_INVSRCALPHA;

	device_search_capabilities.dpcPrimCaps.dwShadeCaps = D3DPSHADECAPS_ALPHAFLATBLEND |
																			D3DPSHADECAPS_COLORFLATRGB |
																			D3DPSHADECAPS_COLORGOURAUDRGB;

	device_search_capabilities.dpcPrimCaps.dwTextureCaps = D3DPTEXTURECAPS_ALPHA | D3DPTEXTURECAPS_PERSPECTIVE;

	device_search_capabilities.dpcPrimCaps.dwTextureBlendCaps = D3DPTBLENDCAPS_MODULATE | D3DPTBLENDCAPS_MODULATEALPHA;

//	ret = IDirect3D7_FindDevice ( d3d.d3d, &device_search_capabilities, &device_search_result );

	if ( ret != D3D_OK )
	{

		return ( FALSE );
	}

	//
	// Now check the fogging capabilities ( we *must* be able to do some sort of fog )
	//

	if ( device_search_result.ddHwDesc.dwFlags & D3DDD_TRICAPS )
	{

		if ( ( device_search_result.ddHwDesc.dpcTriCaps.dwRasterCaps & D3DPRASTERCAPS_FOGTABLE ) ||
				( device_search_result.ddHwDesc.dpcTriCaps.dwRasterCaps & D3DPRASTERCAPS_FOGVERTEX ) )
		{

			//
			// Matches the fog preconditions as well, so it is a valid rendering device
			//

			return ( TRUE );
		}
		else
		{

			return ( FALSE );
		}
	}
	else
	{

		return ( FALSE );
	}

	*/

	return ( FALSE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL initialise_direct_3d_driver ( void )
{

	HRESULT
		ret;


	static int
		render_target_set = FALSE;

	D3DDEVICEDESC7
		hardware_desc;

	//
	// Query for a D3DDEVICE2 object
	//

	if ( !d3d_use_rgb_device )
	{

		if ( d3d_use_dx_pipeline )
		{
	
#if USE_D3D_SOFTWARE_TNL
			ret = IDirect3D7_CreateDevice ( d3d.d3d, &IID_IDirect3DHALDevice, ddraw.lpRenderBuffer, &d3d.device );
#else
			ret = IDirect3D7_CreateDevice ( d3d.d3d, &IID_IDirect3DTnLHalDevice, ddraw.lpRenderBuffer, &d3d.device );
#endif
	
			if ( FAILED ( ret ) )
			{
	
				debug_log ( "Unable to create TnL: %s", get_ddraw_error_message ( ret ) );
	
				d3d_using_hardware_tnl = FALSE;
	
				ret = IDirect3D7_CreateDevice ( d3d.d3d, &IID_IDirect3DHALDevice, ddraw.lpRenderBuffer, &d3d.device );
			}
			else
			{

				debug_log ( "Setting d3d hardware" );
	
				d3d_using_hardware_tnl = TRUE;
			}
		}
		else
		{

			d3d_using_hardware_tnl = FALSE;

			ret = IDirect3D7_CreateDevice ( d3d.d3d, &IID_IDirect3DHALDevice, ddraw.lpRenderBuffer, &d3d.device );
		}
	}
	else
	{

		ret = IDirect3D7_CreateDevice ( d3d.d3d, &IID_IDirect3DRGBDevice, ddraw.lpRenderBuffer, &d3d.device );
	}

	if ( ret != DD_OK )
	{

		debug_fatal ( "Error creating d3d device2: %s", get_ddraw_error_message ( ret ) );
	}

	//
	// Get the capabilities of the device ( specifically looking for the square textures stuff at the moment )
	//

	memset ( &hardware_desc, 0, sizeof ( hardware_desc ) );

	ret = IDirect3DDevice7_GetCaps ( d3d.device, &hardware_desc );

	if ( ret != DD_OK )
	{

		debug_fatal ( "Error getting d3d device capabilities: %s", get_ddraw_error_message ( ret ) );
	}

	//
	// Set the capabilities of the 3dvisual according to the capabilities of the card.
	//

	set_d3d_capabilities ( &hardware_desc );

	//
	// Set render target
	//

//	if ( !render_target_set )
	{

		render_target_set = TRUE;

		ret = IDirect3DDevice7_SetRenderTarget ( d3d.device, ddraw.lpRenderBuffer, 0 );

		if ( ret != DD_OK )
		{

			debug_fatal ( "Error setting render target: %s", get_ddraw_error_message ( ret ) );
		}
	}

	{

		//
		// Create & set the viewport for the device2 interface.
		//

		D3DVIEWPORT7
			viewdata;

		//
		// Set up the viewport values for initial values
		//

		viewdata.dwX = 0;
		viewdata.dwY = 0;

		viewdata.dwWidth = application_video_width;
		viewdata.dwHeight = application_video_height;

		viewdata.dvMinZ = 0;
		viewdata.dvMaxZ = 1;

		ret = IDirect3DDevice7_SetViewport ( d3d.device, &viewdata );

		if ( ret != D3D_OK )
		{

			debug_log ( "Unable to set viewport2: %s", get_d3d_error_message ( ret ) );

			return ( FALSE );
		}
		else
		{

			debug_log ( "Set viewport success" );
		}
	}

	//
	// Initialise the d3d state system
	//

	initialise_d3d_state ();

	//
	// Set the device to valid
	//

	d3d_initialised = TRUE,

	d3d_valid = TRUE;

	return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void destroy_d3d_vertex_buffers ( void )
{

	if ( d3d.d3d )
	{

		HRESULT
			ddrval;

		int
			count;

		for ( count = 0; count < MAXIMUM_TRIANGLE_BUFFERS; count++ )
		{

			if ( d3d.triangle_buffers[count].buffer )
			{

				ddrval = IDirect3DVertexBuffer7_Release ( d3d.triangle_buffers[count].buffer );
	
				if ( ddrval > 0 )				{ debug_log ( "Unable to release triangle vertex buffer: %d instances left", ddrval ); }
				else if ( ddrval < DD_OK )	{ debug_log ( "Unable to release triangle vertex buffer: %s", get_d3d_error_message ( ddrval ) ); }
	
				d3d.triangle_buffers[count].buffer = NULL;
				d3d.triangle_buffers[count].vertices = NULL;
				d3d.triangle_buffers[count].texture.texture = 0;
				d3d.triangle_buffers[count].texture.texture_settings = 0;
				d3d.triangle_buffers[count].vertices_used = 0;
				d3d.triangle_buffers[count].indices_index = 0;
			}
		}

		for ( count = 0; count < MAXIMUM_LINE_BUFFERS; count++ )
		{

			if ( d3d.line_buffers[count].buffer )
			{

				ddrval = IDirect3DVertexBuffer7_Release ( d3d.line_buffers[count].buffer );
	
				if ( ddrval > 0 )				{ debug_log ( "Unable to release line vertex buffer: %d instances left", ddrval ); }
				else if ( ddrval < DD_OK )	{ debug_log ( "Unable to release line vertex buffer: %s", get_d3d_error_message ( ddrval ) ); }
	
				d3d.line_buffers[count].buffer = NULL;
				d3d.line_buffers[count].vertices = NULL;
				d3d.line_buffers[count].texture.texture = 0;
				d3d.line_buffers[count].texture.texture_settings = 0;
				d3d.line_buffers[count].vertices_used = 0;
				d3d.line_buffers[count].indices_index = 0;
			}
		}

		if ( d3d.point_vertex_buffer )
		{

			ddrval = IDirect3DVertexBuffer7_Release ( d3d.point_vertex_buffer );

			if ( ddrval > 0 )				{ debug_log ( "Unable to release point vertex buffer: %d instances left", ddrval ); }
			else if ( ddrval < DD_OK )	{ debug_log ( "Unable to release point vertex buffer: %s", get_d3d_error_message ( ddrval ) ); }

			d3d.point_vertex_buffer = NULL;
		}

		for ( count = 0; count < MAX_ALPHA_VERTEX_BUFFERS; count++ )
		{

			if ( d3d.alpha_vertex_buffer[count] )
			{

				ddrval = IDirect3DVertexBuffer7_Release ( d3d.alpha_vertex_buffer[count] );

				if ( ddrval > 0 )				{ debug_log ( "Unable to release %d alpha vertex buffer: %d instances left", count, ddrval ); }
				else if ( ddrval < DD_OK ) { debug_log ( "Unable to release %d alpha vertex buffer: %s", count, get_d3d_error_message ( ddrval ) ); }
			}

			d3d.alpha_vertex_buffer[count] = NULL;
		}

		if ( d3d.hardware_untransformed_buffer )
		{

			ddrval = IDirect3DVertexBuffer7_Release ( d3d.hardware_untransformed_buffer );

			if ( ddrval > 0 )				{ debug_log ( "Unable to release hardware untransformed buffer: %d instances left", ddrval ); }
			else if ( ddrval < DD_OK ) { debug_log ( "Unable to release hardware untransformed buffer: %s", get_d3d_error_message ( ddrval ) ); }

			d3d.hardware_untransformed_buffer = NULL;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_d3d_vertex_buffers ( void )
{

	D3DVERTEXBUFFERDESC
		desc;

	HRESULT
		ret;

	int
		count;

	memset ( &desc, 0, sizeof ( D3DVERTEXBUFFERDESC ) );

	desc.dwSize = sizeof ( D3DVERTEXBUFFERDESC );

	desc.dwCaps = D3DVBCAPS_WRITEONLY | D3DVBCAPS_DONOTCLIP;

	if ( !d3d_vertex_buffer_in_video_memory )
	{

//		desc.dwCaps |= D3DVBCAPS_SYSTEMMEMORY;
	}

	desc.dwCaps |= D3DVBCAPS_SYSTEMMEMORY;

	desc.dwFVF = D3DFVF_TLVERTEX;

	desc.dwNumVertices = MAXIMUM_D3D_VERTICES_IN_VERTEX_BUFFER;

	for ( count = 0; count < MAXIMUM_TRIANGLE_BUFFERS; count++ )
	{
	
		ret = IDirect3D7_CreateVertexBuffer ( d3d.d3d, &desc, &d3d.triangle_buffers[count].buffer, 0 );

		if ( ret != DD_OK )
		{
	
			debug_log ( "Unable to create vertex buffer: %s", get_d3d_error_message ( ret ) );
		}

		d3d.triangle_buffers[count].vertices = NULL;
		d3d.triangle_buffers[count].texture.texture = 0;
		d3d.triangle_buffers[count].vertices_used = 0;
		d3d.triangle_buffers[count].indices_index = 0;
	}

	for ( count = 0; count < MAXIMUM_LINE_BUFFERS; count++ )
	{
	
		ret = IDirect3D7_CreateVertexBuffer ( d3d.d3d, &desc, &d3d.line_buffers[count].buffer, 0 );

		if ( ret != DD_OK )
		{
	
			debug_log ( "Unable to create vertex buffer: %s", get_d3d_error_message ( ret ) );
		}

		d3d.line_buffers[count].vertices = NULL;
		d3d.line_buffers[count].texture.texture = 0;
		d3d.line_buffers[count].vertices_used = 0;
		d3d.line_buffers[count].indices_index = 0;
	}

	ret = IDirect3D7_CreateVertexBuffer ( d3d.d3d, &desc, &d3d.point_vertex_buffer, 0 );

	if ( ret != DD_OK )
	{

		debug_log ( "Unable to create vertex buffer: %s", get_d3d_error_message ( ret ) );
	}

	for ( count = 0; count < MAX_ALPHA_VERTEX_BUFFERS; count++ )
	{
	
		ret = IDirect3D7_CreateVertexBuffer ( d3d.d3d, &desc, &d3d.alpha_vertex_buffer[count], 0 );

		if ( ret != DD_OK )
		{
	
			debug_log ( "Unable to create vertex buffer: %s", get_d3d_error_message ( ret ) );
		}
	}

	memset ( &desc, 0, sizeof ( D3DVERTEXBUFFERDESC ) );

	desc.dwSize = sizeof ( D3DVERTEXBUFFERDESC );

#if USE_D3D_SOFTWARE_TNL
	desc.dwCaps = ( D3DVBCAPS_WRITEONLY | D3DVBCAPS_SYSTEMMEMORY );
#else
	desc.dwCaps = D3DVBCAPS_WRITEONLY;
#endif

	desc.dwNumVertices = 2048;
	desc.dwFVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

	ret = IDirect3D7_CreateVertexBuffer ( d3d.d3d, &desc, &d3d.hardware_untransformed_buffer, 0 );

	if ( FAILED ( ret ) )
	{

		debug_fatal ( "Unable to create vertex buffer: %s", get_d3d_error_message ( ret ) );
	}

	d3d.triangle_buffer = NULL;
	d3d.line_buffer = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_capabilities ( LPD3DDEVICEDESC7 capabilities )
{

	if ( capabilities->dwDevCaps & D3DDEVCAPS_TEXTURENONLOCALVIDMEM )	{ d3d_texture_system_memory = TRUE; }
	else																					{ d3d_texture_system_memory = FALSE; }

	if ( capabilities->dwDevCaps & D3DDEVCAPS_TEXTUREVIDEOMEMORY )	{ d3d_texture_video_memory = TRUE; }
	else																				{ d3d_texture_video_memory = FALSE; }

	if ( capabilities->dwDevCaps & D3DDEVCAPS_TLVERTEXVIDEOMEMORY )	{ d3d_vertex_buffer_in_video_memory = TRUE; }
	else																					{ d3d_vertex_buffer_in_video_memory = FALSE; }

	if ( capabilities->dwDevCaps & D3DDEVCAPS_SEPARATETEXTUREMEMORIES )	{ d3d_can_render_to_texture = FALSE; debug_log ( "SETTING NON RENDER" ); }
	else																						{ d3d_can_render_to_texture = TRUE; }

	if ( d3d_override_render_to_texture )
	{

		d3d_can_render_to_texture = FALSE;
	}

	if ( current_display_device )
	{

		if ( current_display_device->is_nondisplay )
		{

			d3d_can_render_to_texture = FALSE;
		}
	}

	if ( capabilities->dwDevCaps & D3DDD_TRICAPS )
	{

		//
		// Check the rasterisation capabilities of the device
		//

		if ( capabilities->dpcTriCaps.dwRasterCaps & D3DPRASTERCAPS_FOGTABLE  )
		{

#if ( DEBUG_MODULE )
			debug_log ( "Fog table supported" );
#endif
		}

		if ( capabilities->dpcTriCaps.dwRasterCaps & D3DPRASTERCAPS_FOGVERTEX  )
		{

#if ( DEBUG_MODULE )
			debug_log ( "Fog vertex supported" );
#endif
		}

		if ( capabilities->dpcTriCaps.dwRasterCaps & D3DPRASTERCAPS_MIPMAPLODBIAS )
		{

#if ( DEBUG_MODULE )
			debug_log ( "MipMapLOD supported" );
#endif
		}

		if ( capabilities->dpcTriCaps.dwRasterCaps & D3DPRASTERCAPS_ZBIAS )
		{

#if ( DEBUG_MODULE )
			debug_log ( "ZBias supported" );
#endif
		}

		if ( capabilities->dpcTriCaps.dwRasterCaps & D3DPRASTERCAPS_ZTEST  )
		{

#if ( DEBUG_MODULE )
			debug_log ( "Z Testing supported" );
#endif
		}

		//
		// Ensure we have the Z test we need
		//

		if ( capabilities->dpcTriCaps.dwZCmpCaps & D3DPCMPCAPS_GREATEREQUAL )
		{

#if ( DEBUG_MODULE )
			debug_log ( "Z compare greater equal supported" );
#endif
		}

		//
		// Check the source alpha blending capabilities
		//

		if ( capabilities->dpcTriCaps.dwSrcBlendCaps & D3DPBLENDCAPS_ONE  )
		{

#if ( DEBUG_MODULE )
			debug_log ( "Src blend one supported" );
#endif
		}

		if ( capabilities->dpcTriCaps.dwSrcBlendCaps & D3DPBLENDCAPS_BOTHSRCALPHA )
		{

#if ( DEBUG_MODULE )
			debug_log ( "BOTHSRCBLEND supported" );
#endif
		}

		if ( capabilities->dpcTriCaps.dwSrcBlendCaps & D3DPBLENDCAPS_SRCALPHA  )
		{

#if ( DEBUG_MODULE )
			debug_log ( "Src blend alpha supported" );
#endif
		}

		if ( capabilities->dpcTriCaps.dwSrcBlendCaps & D3DPBLENDCAPS_INVSRCALPHA  )
		{

#if ( DEBUG_MODULE )
			debug_log ( "Src blend inv alpha supported" );
#endif
		}

		if ( capabilities->dpcTriCaps.dwSrcBlendCaps & D3DPBLENDCAPS_ZERO  )
		{

#if ( DEBUG_MODULE )
			debug_log ( "Src blend zero supported" );
#endif
		}

		//
		// Check the destination alpha blending capabilities
		//

		if ( capabilities->dpcTriCaps.dwDestBlendCaps & D3DPBLENDCAPS_ONE  )
		{

#if ( DEBUG_MODULE )
			debug_log ( "Dest blend one supported" );
#endif
		}

		if ( capabilities->dpcTriCaps.dwDestBlendCaps & D3DPBLENDCAPS_SRCALPHA  )
		{

#if ( DEBUG_MODULE )
			debug_log ( "Dest blend alpha supported" );
#endif
		}

		if ( capabilities->dpcTriCaps.dwDestBlendCaps & D3DPBLENDCAPS_INVSRCALPHA  )
		{

#if ( DEBUG_MODULE )
			debug_log ( "Dest blend inv alpha supported" );
#endif
		}

		if ( capabilities->dpcTriCaps.dwDestBlendCaps & D3DPBLENDCAPS_ZERO  )
		{

#if ( DEBUG_MODULE )
			debug_log ( "Dest blend zero supported" );
#endif
		}

		//
		// Check the shading capabilities
		//

		if ( capabilities->dpcTriCaps.dwShadeCaps & D3DPSHADECAPS_ALPHAFLATBLEND  )
		{

#if ( DEBUG_MODULE )
			debug_log ( "Alpha flat blend supported" );
#endif
		}

		if ( capabilities->dpcTriCaps.dwShadeCaps & D3DPSHADECAPS_ALPHAFLATSTIPPLED  )
		{

#if ( DEBUG_MODULE )
			debug_log ( "Alpha flat stippled supported" );
#endif
		}

		if ( capabilities->dpcTriCaps.dwShadeCaps & D3DPSHADECAPS_ALPHAGOURAUDBLEND  )
		{

			d3d_flat_only_alpha = FALSE;

#if ( DEBUG_MODULE )
			debug_log ( "Alpha gouraud blend supported" );
#endif
		}
		else
		{

			d3d_flat_only_alpha = TRUE;
		}

		if ( capabilities->dpcTriCaps.dwShadeCaps & D3DPSHADECAPS_ALPHAGOURAUDSTIPPLED  )
		{

#if ( DEBUG_MODULE )
			debug_log ( "Alpha gouraud stippled supported" );
#endif
		}

		if ( capabilities->dpcTriCaps.dwShadeCaps & D3DPSHADECAPS_COLORFLATRGB  )
		{

#if ( DEBUG_MODULE )
			debug_log ( "Colour flat rgb supported" );
#endif
		}
		if ( capabilities->dpcTriCaps.dwShadeCaps & D3DPSHADECAPS_COLORGOURAUDRGB  )
		{

#if ( DEBUG_MODULE )
			debug_log ( "Colour gouraud rgb supported" );
#endif
		}
		if ( capabilities->dpcTriCaps.dwShadeCaps & D3DPSHADECAPS_FOGFLAT  )
		{

#if ( DEBUG_MODULE )
			debug_log ( "Fog flat supported" );
#endif
		}
		if ( capabilities->dpcTriCaps.dwShadeCaps & D3DPSHADECAPS_FOGGOURAUD  )
		{

#if ( DEBUG_MODULE )
			debug_log ( "Fog gouraud supported" );
#endif
		}
		if ( capabilities->dpcTriCaps.dwShadeCaps & D3DPSHADECAPS_SPECULARFLATRGB  )
		{

#if ( DEBUG_MODULE )
			debug_log ( "Specular flat supported" );
#endif
		}
		if ( capabilities->dpcTriCaps.dwShadeCaps & D3DPSHADECAPS_SPECULARGOURAUDRGB  )
		{

#if ( DEBUG_MODULE )
			debug_log ( "Specular gouraud supported" );
#endif
		}

		//
		// Make sure all the texture mapping modes we need are available
		//

		if ( capabilities->dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_ALPHA )
		{

#if ( DEBUG_MODULE )
			debug_log ( "Alpha textures allowed" );
#endif
		}

		if ( capabilities->dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_PERSPECTIVE )
		{

#if ( DEBUG_MODULE )
			debug_log ( "Perspective Correction allowed" );
#endif
		}

		if ( capabilities->dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_SQUAREONLY )
		{

			d3d_square_only_textures = TRUE;
		}
		else
		{

			d3d_square_only_textures = FALSE;
		}

		//
		// Check the texture filtering capabilities
		//

		if ( capabilities->dpcTriCaps.dwTextureFilterCaps & D3DPTFILTERCAPS_NEAREST  )
		{

#if ( DEBUG_MODULE )
			debug_log ( "Texture filter nearest supported" );
#endif
		}

		if ( capabilities->dpcTriCaps.dwTextureFilterCaps & D3DPTFILTERCAPS_LINEAR  )
		{

#if ( DEBUG_MODULE )
			debug_log ( "Texture filter linear supported" );
#endif
		}


		{

			int
				flag;

			flag = FALSE;

			if ( capabilities->dpcTriCaps.dwTextureFilterCaps & D3DPTFILTERCAPS_MIPNEAREST  )
			{
	
				flag = TRUE;
	
#if ( DEBUG_MODULE )
				debug_log ( "Texture filter mip-nearest supported" );
#endif
			}
	
			if ( capabilities->dpcTriCaps.dwTextureFilterCaps & D3DPTFILTERCAPS_MIPLINEAR  )
			{
	
				flag = TRUE;
	
#if ( DEBUG_MODULE )
				debug_log ( "Texture filter mip-linear supported" );
#endif
			}
	
			if ( capabilities->dpcTriCaps.dwTextureFilterCaps & D3DPTFILTERCAPS_LINEARMIPNEAREST  )
			{
	
				flag = TRUE;
	
#if ( DEBUG_MODULE )
				debug_log ( "Texture filter linear-mip-nearest supported" );
#endif
			}
	
			if ( capabilities->dpcTriCaps.dwTextureFilterCaps & D3DPTFILTERCAPS_LINEARMIPLINEAR  )
			{
	
#if ( DEBUG_MODULE )
				debug_log ( "Texture filter linear-mip-linear supported" );
#endif

				flag = TRUE;
	
				d3d_trilinear_filtering = TRUE;
			}
			else
			{

				d3d_trilinear_filtering = FALSE;
			}

			d3d_mipmap_textures = flag;
		}

		//
		// Check the texture blending capabilities
		//

		if ( capabilities->dpcTriCaps.dwTextureBlendCaps & D3DPTBLENDCAPS_MODULATE )
		{

			//
			// This capability *must* be supported
			//

			d3d_modulate = TRUE;
		}
		else
		{

			d3d_modulate = FALSE;
		}

		if ( capabilities->dpcTriCaps.dwTextureBlendCaps & D3DPTBLENDCAPS_MODULATEALPHA )
		{

			//
			// Rage Pro *doesn't* support modulate alpha - but we can still run anyway :)
			//

			d3d_modulate_alpha = TRUE;
		}
		else
		{

			d3d_modulate_alpha = FALSE;
		}

		//
		// Check the texture wrapping capabilities
		//

		if ( capabilities->dpcTriCaps.dwTextureAddressCaps & D3DPTADDRESSCAPS_WRAP  )
		{

#if ( DEBUG_MODULE )
			debug_log ( "Texture wrapping supported" );
#endif
		}
	}

	{

		if ( capabilities->dpcLineCaps.dwTextureCaps )
		{

			d3d_textured_lines = TRUE;
		}
		else
		{

			d3d_textured_lines = FALSE;
		}
	}

	//
	// Check texture map size capabilities
	//

	d3d_minimum_texture_width = capabilities->dwMinTextureWidth;
	d3d_minimum_texture_height = capabilities->dwMinTextureHeight;

	d3d_maximum_texture_width = capabilities->dwMaxTextureWidth;
	d3d_maximum_texture_height = capabilities->dwMaxTextureHeight;

	//
	// If the card doesn't have 8Megs of memory, limit texture size to 256x256
	//


	if ( d3d_total_video_texture_memory < 8192*1024 )
	{

		d3d_maximum_texture_width = min ( d3d_maximum_texture_width, 256 );
		d3d_maximum_texture_height = min ( d3d_maximum_texture_height, 256 );
	}

	d3d_using_permedia2_chipset = FALSE;

	//
	// Check for chipset specific stuff.
	//

	{

		DDDEVICEIDENTIFIER2
			did;

		IDirectDraw7_GetDeviceIdentifier ( ddraw.ddraw, &did, 0 );

		if ( did.dwVendorId ==0x12d2 )
		{

			if ( did.dwDeviceId == 0x18 || did.dwDeviceId == 0x19 )
			{

				//
				// Its a riva 128 - disable trilinear filtering!!!
				//

				d3d_trilinear_filtering = FALSE;
			}
		}

		if ( did.dwVendorId == 0x3d3d )
		{

			if ( ( did.dwDeviceId == 0x07 ) || ( did.dwDeviceId == 0x09 ) )
			{

				d3d_using_permedia2_chipset = TRUE;
			}
		}

		if ( did.dwVendorId == 0x104c)
		{

			if ( did.dwDeviceId == 0x3d07 )
			{

				d3d_using_permedia2_chipset = TRUE;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void d3d_restore_objects ( int activate )
{


	if ( !activate )
	{

		//
		// Losing focus
		//

		d3d_valid = FALSE;
	}
	else
	{
	
		//
		// Gaining focus
		//

		if ( d3d_initialised )
		{

			//
			// Flag the fact we need to recreate the d3d devices/textures
			//

			d3d.recreate_d3d = TRUE;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void recreate_d3d ( void )
{

	//
	// Free all hardware textures up
	//

	free_all_hardware_textures ();

	//
	// Release all the d3d interfaces
	//

	d3d_release_objects ();

	//
	// Re-create all the d3d interfaces
	//

	initialise_direct_3d_driver ();

	//
	// Create the vertex buffers
	//

	create_d3d_vertex_buffers ();

	if ( restore_vb_friend_function )
	{

		restore_vb_friend_function ();
	}

	d3d.recreate_d3d = FALSE;

	//
	// Set the FPU to zero rounding!
	//

	set_fpu_rounding_mode_zero ();

	//
	// Recreate the render to texture screens
	//

	restore_graphics_screens ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void d3d_release_objects ( void )
{

	HRESULT
		ddrval;

	destroy_d3d_vertex_buffers ();

	if ( d3d.device )
	{

		ddrval = IDirect3DDevice7_Release ( d3d.device );

		if ( ddrval < DD_OK )
		{

			debug_log ( "Unable to release d3d device7: %s", get_d3d_error_message ( ddrval ) );
		}

		d3d.device = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL d3d_begin_scene ( void )
{

	HRESULT
		ret;

	d3d_number_of_executions = 0;

	d3d_number_of_texture_loads = 0;

	if ( d3d.recreate_d3d )
	{

		recreate_d3d ();
	}

	if ( d3d_valid )
	{

		if ( d3d.device )
		{

			reset_primitives ();

			ret = IDirect3DDevice7_BeginScene ( d3d.device );
			
			if ( ret != D3D_OK )
			{


				debug_log ( "Unable to begin_scene - %s", get_d3d_error_message ( ret ) );
				//
				// End the scene
				//
	
				IDirect3DDevice7_EndScene ( d3d.device );
	
				return ( FALSE );
			}

			set_d3d_alpha_fog_zbuffer ( FALSE, TRUE, TRUE, TRUE );

//			set_d3d_transparency_off ();

//			set_d3d_texture_batching ( FALSE );

			d3d_in_3d_scene = TRUE;

#if ( REPORT_SCENE_BREAKS )
			debug_log ( "BEGIN 3D SCENE" );
#endif
	
			return ( TRUE );
		}
		else
		{
	
			return ( FALSE );
		}
	}
	else
	{

		return ( FALSE );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL d3d_end_scene ( void )
{

	HRESULT
		ret;

	if ( d3d.device )
	{

		flush_triangle_primitives ();

		flush_line_primitives ();

		finalise_primitives ();

		ret = IDirect3DDevice7_EndScene ( d3d.device );

		if ( ret != D3D_OK )
		{
	
			debug_log ( "Unable to end_scene: %s", get_d3d_error_message ( ret ) );
	
			return ( FALSE );
		}

		d3d_in_3d_scene = FALSE;

#if ( REPORT_SCENE_BREAKS )
		debug_log ( "END 3D SCENE" );
#endif
	
		return ( TRUE );
	}
	else
	{

		return ( FALSE );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void d3d_render_target_recreated ( void )
{

	HRESULT
		ret;

	ret = IDirect3DDevice7_SetRenderTarget ( d3d.device, ddraw.lpRenderBuffer, 0 );

	if ( ret != DD_OK )
	{

		debug_fatal ( "Error setting render target: %s", get_ddraw_error_message ( ret ) );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct direct_3d_errors
{
	HRESULT
		error;

	char
		*error_string;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct direct_3d_errors d3d_error_table[] =
{
	{ D3D_OK, "D3D_OK" },
	{ D3DERR_BADMAJORVERSION, "D3DERR_BADMAJORVERSION" },
	{ D3DERR_BADMINORVERSION, "D3DERR_BADMINORVERSION" },
	{ D3DERR_INVALID_DEVICE, "D3DERR_INVALID_DEVICE" },
	{ D3DERR_INITFAILED, "D3DERR_INITFAILED" },
	{ D3DERR_DEVICEAGGREGATED, "D3DERR_DEVICEAGGREGATED" },
	{ D3DERR_EXECUTE_CREATE_FAILED, "D3DERR_EXECUTE_CREATE_FAILED" },
	{ D3DERR_EXECUTE_DESTROY_FAILED, "D3DERR_EXECUTE_DESTROY_FAILED" },
	{ D3DERR_EXECUTE_LOCK_FAILED, "D3DERR_EXECUTE_LOCK_FAILED" },
	{ D3DERR_EXECUTE_UNLOCK_FAILED, "D3DERR_EXECUTE_UNLOCK_FAILED" },
	{ D3DERR_EXECUTE_LOCKED, "D3DERR_EXECUTE_LOCKED" },
	{ D3DERR_EXECUTE_NOT_LOCKED, "D3DERR_EXECUTE_NOT_LOCKED" },
	{ D3DERR_EXECUTE_FAILED, "D3DERR_EXECUTE_FAILED" },
	{ D3DERR_EXECUTE_CLIPPED_FAILED, "D3DERR_EXECUTE_CLIPPED_FAILED" },
	{ D3DERR_TEXTURE_NO_SUPPORT, "D3DERR_TEXTURE_NO_SUPPORT" },
	{ D3DERR_TEXTURE_CREATE_FAILED, "D3DERR_TEXTURE_CREATE_FAILED" },
	{ D3DERR_TEXTURE_DESTROY_FAILED, "D3DERR_TEXTURE_DESTROY_FAILED" },
	{ D3DERR_TEXTURE_LOCK_FAILED, "D3DERR_TEXTURE_LOCK_FAILED" },
	{ D3DERR_TEXTURE_UNLOCK_FAILED, "D3DERR_TEXTURE_UNLOCK_FAILED" },
	{ D3DERR_TEXTURE_LOAD_FAILED, "D3DERR_TEXTURE_LOAD_FAILED" },
	{ D3DERR_TEXTURE_SWAP_FAILED, "D3DERR_TEXTURE_SWAP_FAILED" },
	{ D3DERR_TEXTURE_LOCKED, "D3DERR_TEXTURE_LOCKED" },
	{ D3DERR_TEXTURE_NOT_LOCKED, "D3DERR_TEXTURE_NOT_LOCKED" },
	{ D3DERR_TEXTURE_GETSURF_FAILED, "D3DERR_TEXTURE_GETSURF_FAILED" },
	{ D3DERR_MATRIX_CREATE_FAILED, "D3DERR_MATRIX_CREATE_FAILED" },
	{ D3DERR_MATRIX_DESTROY_FAILED, "D3DERR_MATRIX_DESTROY_FAILED" },
	{ D3DERR_MATRIX_SETDATA_FAILED, "D3DERR_MATRIX_SETDATA_FAILED" },
	{ D3DERR_MATRIX_GETDATA_FAILED, "D3DERR_MATRIX_GETDATA_FAILED" },
	{ D3DERR_SETVIEWPORTDATA_FAILED, "D3DERR_SETVIEWPORTDATA_FAILED" },
	{ D3DERR_INVALIDCURRENTVIEWPORT, "D3DERR_INVALIDCURRENTVIEWPORT" },
	{ D3DERR_INVALIDPRIMITIVETYPE, "D3DERR_INVALIDPRIMITIVETYPE" },
	{ D3DERR_INVALIDVERTEXTYPE, "D3DERR_INVALIDVERTEXTYPE" },
	{ D3DERR_TEXTURE_BADSIZE, "D3DERR_TEXTURE_BADSIZE" },
	{ D3DERR_INVALIDRAMPTEXTURE, "D3DERR_INVALIDRAMPTEXTURE" },
	{ D3DERR_MATERIAL_CREATE_FAILED, "D3DERR_MATERIAL_CREATE_FAILED" },
	{ D3DERR_MATERIAL_DESTROY_FAILED, "D3DERR_MATERIAL_DESTROY_FAILED" },
	{ D3DERR_MATERIAL_SETDATA_FAILED, "D3DERR_MATERIAL_SETDATA_FAILED" },
	{ D3DERR_MATERIAL_GETDATA_FAILED, "D3DERR_MATERIAL_GETDATA_FAILED" },
	{ D3DERR_INVALIDPALETTE, "D3DERR_INVALIDPALETTE" },
	{ D3DERR_ZBUFF_NEEDS_SYSTEMMEMORY, "D3DERR_ZBUFF_NEEDS_SYSTEMMEMORY" },
	{ D3DERR_ZBUFF_NEEDS_VIDEOMEMORY, "D3DERR_ZBUFF_NEEDS_VIDEOMEMORY" },
	{ D3DERR_SURFACENOTINVIDMEM, "D3DERR_SURFACENOTINVIDMEM" },
	{ D3DERR_LIGHT_SET_FAILED, "D3DERR_LIGHT_SET_FAILED" },
	{ D3DERR_LIGHTHASVIEWPORT, "D3DERR_LIGHTHASVIEWPORT" },
	{ D3DERR_LIGHTNOTINTHISVIEWPORT, "D3DERR_LIGHTNOTINTHISVIEWPORT" },
	{ D3DERR_SCENE_IN_SCENE, "D3DERR_SCENE_IN_SCENE" },
	{ D3DERR_SCENE_NOT_IN_SCENE, "D3DERR_SCENE_NOT_IN_SCENE" },
	{ D3DERR_SCENE_BEGIN_FAILED, "D3DERR_SCENE_BEGIN_FAILED" },
	{ D3DERR_SCENE_END_FAILED, "D3DERR_SCENE_END_FAILED" },
	{ D3DERR_INBEGIN, "D3DERR_INBEGIN" },
	{ D3DERR_NOTINBEGIN, "D3DERR_NOTINBEGIN" },
	{ D3DERR_NOVIEWPORTS, "D3DERR_NOVIEWPORTS" },
	{ D3DERR_VIEWPORTDATANOTSET, "D3DERR_VIEWPORTDATANOTSET" },
	{ D3DERR_VIEWPORTHASNODEVICE, "D3DERR_VIEWPORTHASNODEVICE" },
	{ D3DERR_NOCURRENTVIEWPORT, "D3DERR_NOCURRENTVIEWPORT" },
	{ D3DERR_INVALIDVERTEXFORMAT, "D3DERR_INVALIDVERTEXFORMAT" },
	{ D3DERR_COLORKEYATTACHED, "D3DERR_COLORKEYATTACHED" },
	{ D3DERR_VERTEXBUFFEROPTIMIZED, "D3DERR_VERTEXBUFFEROPTIMIZED" },
	{ D3DERR_VBUF_CREATE_FAILED, "D3DERR_VBUF_CREATE_FAILED" },
	{ D3DERR_VERTEXBUFFERLOCKED, "D3DERR_VERTEXBUFFERLOCKED" },
	{ D3DERR_ZBUFFER_NOTPRESENT, "D3DERR_ZBUFFER_NOTPRESENT" },
	{ D3DERR_STENCILBUFFER_NOTPRESENT, "D3DERR_STENCILBUFFER_NOTPRESENT" },
	{ D3DERR_WRONGTEXTUREFORMAT, "D3DERR_WRONGTEXTUREFORMAT" },
	{ D3DERR_UNSUPPORTEDCOLOROPERATION, "D3DERR_UNSUPPORTEDCOLOROPERATION" },
	{ D3DERR_UNSUPPORTEDCOLORARG, "D3DERR_UNSUPPORTEDCOLORARG" },
	{ D3DERR_UNSUPPORTEDALPHAOPERATION, "D3DERR_UNSUPPORTEDALPHAOPERATION" },
	{ D3DERR_UNSUPPORTEDALPHAARG, "D3DERR_UNSUPPORTEDALPHAARG" },
	{ D3DERR_TOOMANYOPERATIONS, "D3DERR_TOOMANYOPERATIONS" },
	{ D3DERR_CONFLICTINGTEXTUREFILTER, "D3DERR_CONFLICTINGTEXTUREFILTER" },
	{ D3DERR_UNSUPPORTEDFACTORVALUE, "D3DERR_UNSUPPORTEDFACTORVALUE" },
	{ D3DERR_CONFLICTINGRENDERSTATE, "D3DERR_CONFLICTINGRENDERSTATE" },
	{ D3DERR_UNSUPPORTEDTEXTUREFILTER, "D3DERR_UNSUPPORTEDTEXTUREFILTER" },
	{ D3DERR_TOOMANYPRIMITIVES, "D3DERR_TOOMANYPRIMITIVES" },
	{ D3DERR_INVALIDMATRIX, "D3DERR_INVALIDMATRIX" },
	{ D3DERR_TOOMANYVERTICES, "D3DERR_TOOMANYVERTICES" },
	{ D3DERR_CONFLICTINGTEXTUREPALETTE, "D3DERR_CONFLICTINGTEXTUREPALETTE" },
	{ -1, "D3D_UNKNOWN ERROR" },
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char * get_d3d_error_message ( HRESULT error )
{

	int
		count;


	count = 0;

	while ( ( d3d_error_table[count].error != -1 ) && ( d3d_error_table[count].error != error ) )
	{

		count ++;
	}

	return ( d3d_error_table[count].error_string );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


