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
#include "project.h"

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

struct DIRECT_3D
	d3d_common;
struct DIRECT_3D_DATA
	d3d_data;
struct DIRECT_3D_EXPORT_MFD
	d3d_export_mfd[2];
struct DIRECT_3D_VECTORS
	d3d;

int
	d3d_initialised = FALSE,
	d3d_valid = FALSE,
	d3d_in_3d_scene = FALSE;

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
	// Texture dimension limits
	//

	d3d_maximum_texture_width,
	d3d_maximum_texture_height,

	//
	// Use the DX pipeline ( possibly hardware accelerated )
	//

	d3d_use_dx_pipeline = FALSE,

	//
	// Hardware TnL is available
	//

	d3d_using_hardware_tnl;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL initialise_direct_3d ( void )
{
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

	d3d_common.recreate_d3d = FALSE;

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

static int direct_3d_device_create ( void *params )
{
	HRESULT
		res;
	unsigned
		flags;
	flags = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
#ifdef DEBUG
	flags |= D3DCREATE_MULTITHREADED;
#endif
	if ( d3d_common.mfd == MFD_MULTIHEAD )
	{
		flags |= D3DCREATE_ADAPTERGROUP_DEVICE;
	}
	res = IDirect3D9_CreateDevice ( d3d_common.d3d, d3d_data.selected_adapter[D3D_MAIN], D3DDEVTYPE_HAL, application_window, flags, &d3d_data.d3dpp[D3D_MAIN], &d3d_data.device[D3D_MAIN] );
	if ( FAILED ( res ) )
		return res;
	if ( d3d_common.mfd == MFD_WINDOW || d3d_common.mfd == MFD_FULLSCREEN )
	{
		res = IDirect3D9_CreateDevice ( d3d_common.d3d, d3d_data.selected_adapter[D3D_MFD], D3DDEVTYPE_HAL, application_window, flags, &d3d_data.d3dpp[D3D_MFD], &d3d_data.device[D3D_MFD] );
	}
	return res;
}

static int direct_3d_device_release ( void *params )
{
	int
		count;

	if ( d3d_data.device[D3D_MFD] )
	{
		for ( count = 0; count < ARRAY_LENGTH ( d3d_export_mfd ); count++ )
		{
			if ( d3d_export_mfd[count].texture )
			{
				IDirect3DTexture9_Release ( d3d_export_mfd[count].texture );
			}
		}
		IDirect3DDevice9_Release ( d3d_data.device[D3D_MFD] );
	}
	return IDirect3DDevice9_Release ( d3d_data.device[D3D_MAIN] );
}

static int direct_3d_device_reset ( int d3d )
{
	HRESULT
		res;

	debug_log ( "Calling IDirect3DDevice9_TestCooperativeLevel" );
	res = IDirect3DDevice9_TestCooperativeLevel ( d3d_data.device[d3d] );
	debug_log ( "Cooperative level of d3d device: %s", get_d3d_error_message ( res ) );
	if ( res == D3DERR_DEVICELOST )
	{
		return FALSE;
	}
	if ( res == D3DERR_DEVICENOTRESET )
	{
		debug_log ( "Resetting d3d device" );
		res = IDirect3DDevice9_Reset ( d3d_data.device[d3d], &d3d_data.d3dpp[d3d] );
		if ( FAILED ( res ) )
		{
			return FALSE;
		}
	}
	return TRUE;

}
static int direct_3d_device_lost ( void *params )
{
	if ( d3d_data.device[D3D_MFD] )
		if ( !direct_3d_device_reset ( D3D_MFD ) )
			return FALSE;
	if ( !direct_3d_device_reset ( D3D_MAIN ) )
		return FALSE;
	return TRUE;
}

BOOL initialise_direct_3d_driver ( void )
{
	HRESULT
		ret;

	D3DCAPS9
		hardware_desc;

	d3d_using_hardware_tnl = d3d_use_dx_pipeline;

	memset ( d3d_data.d3dpp, 0, sizeof ( d3d_data.d3dpp ) );

	d3d_data.d3dpp[D3D_MAIN].BackBufferWidth = application_video_width;
	d3d_data.d3dpp[D3D_MAIN].BackBufferHeight = application_video_height;
	d3d_data.d3dpp[D3D_MAIN].BackBufferCount = 2;
	d3d_data.d3dpp[D3D_MAIN].BackBufferFormat = D3DFMT_X8R8G8B8;
	d3d_data.d3dpp[D3D_MAIN].SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3d_data.d3dpp[D3D_MAIN].hDeviceWindow = application_window;
	d3d_data.d3dpp[D3D_MAIN].Windowed = application_video_windowed;
	d3d_data.d3dpp[D3D_MAIN].EnableAutoDepthStencil = TRUE;
	d3d_data.d3dpp[D3D_MAIN].AutoDepthStencilFormat = D3DFMT_D24S8;

	if ( d3d_common.mfd != MFD_NONE )
	{
		d3d_data.d3dpp[D3D_MFD].BackBufferWidth = command_line_export_mfd_screen_width;
		d3d_data.d3dpp[D3D_MFD].BackBufferHeight = command_line_export_mfd_screen_height;
		d3d_data.d3dpp[D3D_MFD].BackBufferCount = 2;
		d3d_data.d3dpp[D3D_MFD].BackBufferFormat = D3DFMT_X8R8G8B8;
		d3d_data.d3dpp[D3D_MFD].SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3d_data.d3dpp[D3D_MFD].hDeviceWindow = export_window;
		d3d_data.d3dpp[D3D_MFD].Windowed = d3d_common.mfd == MFD_WINDOW;
		d3d_data.d3dpp[D3D_MFD].EnableAutoDepthStencil = d3d_common.mfd == MFD_MULTIHEAD;
		d3d_data.d3dpp[D3D_MFD].AutoDepthStencilFormat = D3DFMT_D24S8;
	}

	ret = system_thread_function ( direct_3d_device_create, NULL );

	if ( FAILED ( ret ) )
	{
		debug_fatal ( "Unable to create direct3d device object: %s", get_d3d_error_message ( ret ) );

		return FALSE;
	}

	ret = IDirect3DDevice9_GetDeviceCaps ( d3d_data.device[D3D_MAIN], &hardware_desc );

	if ( FAILED ( ret ) )
	{
		debug_fatal ( "Error getting d3d device capabilities: %s", get_d3d_error_message ( ret ) );
	}

	set_d3d_capabilities ( &hardware_desc );

	//
	// Set render target
	//

	{

		//
		// Create & set the viewport for the device2 interface.
		//

		D3DVIEWPORT9
			viewdata;

		//
		// Set up the viewport values for initial values
		//

		viewdata.X = 0;
		viewdata.Y = 0;

		viewdata.Width = application_video_width;
		viewdata.Height = application_video_height;

		viewdata.MinZ = 0;
		viewdata.MaxZ = 1;

		if ( !f3d_set_viewport ( &viewdata ) )
		{
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

	d3d_initialised = TRUE,

	initialise_d3d_state ();

	//
	// Set the device to valid
	//

	d3d_valid = TRUE;

	return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void destroy_d3d_vertex_buffers ( void )
{

	if ( d3d_common.d3d )
	{

		int
			count;

		for ( count = 0; count < MAXIMUM_TRIANGLE_BUFFERS; count++ )
		{

			if ( d3d.triangle_buffers[count].buffer )
			{

				f3d_vertex_release ( &d3d.triangle_buffers[count].buffer );
				f3d_index_release ( &d3d.triangle_buffers[count].ibuffer );

				d3d.triangle_buffers[count].vertices = NULL;
				d3d.triangle_buffers[count].indices = NULL;
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
				f3d_vertex_release ( &d3d.line_buffers[count].buffer );
				f3d_index_release ( &d3d.line_buffers[count].ibuffer );

				d3d.line_buffers[count].vertices = NULL;
				d3d.line_buffers[count].indices = NULL;
				d3d.line_buffers[count].texture.texture = 0;
				d3d.line_buffers[count].texture.texture_settings = 0;
				d3d.line_buffers[count].vertices_used = 0;
				d3d.line_buffers[count].indices_index = 0;
			}
		}

		if ( d3d.point_vertex_buffer )
		{
			f3d_vertex_release ( &d3d.point_vertex_buffer );
		}

		for ( count = 0; count < MAX_ALPHA_VERTEX_BUFFERS; count++ )
		{

			if ( d3d.alpha_vertex_buffer[count] )
			{
				f3d_vertex_release ( &d3d.alpha_vertex_buffer[count] );
			}
		}

		if ( d3d.alpha_index_buffer )
		{
			f3d_index_release ( &d3d.alpha_index_buffer );
		}

		if ( d3d.hardware_untransformed_buffer )
		{

			f3d_vertex_release ( &d3d.hardware_untransformed_buffer );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_d3d_vertex_buffers ( void )
{
	unsigned int
		size,
		fvf;

	int
		count;

	size = MAXIMUM_D3D_VERTICES_IN_VERTEX_BUFFER * sizeof ( TLVERTEX );
	fvf = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX1;

	for ( count = 0; count < MAXIMUM_TRIANGLE_BUFFERS; count++ )
	{
		f3d_vertex_create ( size, fvf, &d3d.triangle_buffers[count].buffer );
		f3d_index_create ( MAXIMUM_D3D_INDICES_IN_VERTEX_BUFFER, &d3d.triangle_buffers[count].ibuffer );

		d3d.triangle_buffers[count].vertices = NULL;
		d3d.triangle_buffers[count].indices = NULL;
		d3d.triangle_buffers[count].texture.texture = 0;
		d3d.triangle_buffers[count].vertices_used = 0;
		d3d.triangle_buffers[count].indices_index = 0;
	}

	for ( count = 0; count < MAXIMUM_LINE_BUFFERS; count++ )
	{
		f3d_vertex_create ( size, fvf, &d3d.line_buffers[count].buffer );
		f3d_index_create ( MAXIMUM_D3D_INDICES_IN_VERTEX_BUFFER, &d3d.line_buffers[count].ibuffer );

		d3d.line_buffers[count].vertices = NULL;
		d3d.line_buffers[count].indices = NULL;
		d3d.line_buffers[count].texture.texture = 0;
		d3d.line_buffers[count].vertices_used = 0;
		d3d.line_buffers[count].indices_index = 0;
	}

	f3d_vertex_create ( size, fvf, &d3d.point_vertex_buffer );

	for ( count = 0; count < MAX_ALPHA_VERTEX_BUFFERS; count++ )
	{
		f3d_vertex_create ( size, fvf, &d3d.alpha_vertex_buffer[count] );
	}

	f3d_index_create ( MAXIMUM_D3D_INDICES_IN_VERTEX_BUFFER, &d3d.alpha_index_buffer );

	size = MAXIMUM_D3D_VERTICES_IN_VERTEX_BUFFER * sizeof ( NTVERTEX );
	fvf = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

	f3d_vertex_create ( size, fvf, &d3d.hardware_untransformed_buffer );

	d3d.triangle_buffer = NULL;
	d3d.line_buffer = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_capabilities ( D3DCAPS9* capabilities )
{

	//
	// Check texture map size capabilities
	//

	d3d_maximum_texture_width = capabilities->MaxTextureWidth;
	d3d_maximum_texture_height = capabilities->MaxTextureHeight;
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

			d3d_common.recreate_d3d = TRUE;
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

	release_video_screens ();

	if ( !system_thread_function ( direct_3d_device_lost, NULL ) )
		return;

	d3d_valid = TRUE;

	d3d_common.recreate_d3d = FALSE;

	//
	// Set the FPU to zero rounding!
	//

	set_fpu_rounding_mode_zero ();

	initialise_d3d_state ();

	//
	// Recreate the render to texture screens
	//

	recreate_video_screens ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void d3d_release_objects ( void )
{

	HRESULT
		ret;

	destroy_d3d_vertex_buffers ();

	if ( d3d_data.device )
	{

		ret = system_thread_function ( direct_3d_device_release, NULL );

		if ( FAILED ( ret ) )
		{

			debug_log ( "Unable to release d3d device: %s", get_d3d_error_message ( ret ) );
		}

		d3d_data.device[D3D_MAIN] = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL d3d_begin_scene ( void )
{
	if ( d3d_common.recreate_d3d )
	{

		recreate_d3d ();
	}

	if ( d3d_valid )
	{

		if ( d3d_data.device )
		{

			reset_primitives ();

			if ( !f3d_scene_begin () )
			{
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
	if ( d3d_data.device )
	{

		flush_triangle_primitives ();

		flush_line_primitives ();

		finalise_primitives ();

		if ( !f3d_scene_end () )
		{
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

void d3d_color_fill(unsigned int colour, int x1, int y1, int x2, int y2)
{
	ASSERT ( d3d_in_3d_scene );

	{
		struct
		{
			float x, y, z, r;
			unsigned colour;
		} v[] =
		{
			{ 0, 0, 1, 1, 0 },
			{ 0, 0, 1, 1, 0 },
			{ 0, 0, 1, 1, 0 },
			{ 0, 0, 1, 1, 0 },
		};
		v[0].x = x1;
		v[0].y = y1;
		v[0].colour = colour;
		v[1].x = x2;
		v[1].y = y1;
		v[1].colour = colour;
		v[2].x = x2;
		v[2].y = y2;
		v[2].colour = colour;
		v[3].x = x1;
		v[3].y = y2;
		v[3].colour = colour;

		set_d3d_alpha_fog_zbuffer ( FALSE, FALSE, FALSE, FALSE );
		set_d3d_plain_renderstate ();
		IDirect3DDevice9_SetFVF ( d3d_data.device[D3D_MAIN], D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX0 );
		IDirect3DDevice9_DrawPrimitiveUP ( d3d_data.device[D3D_MAIN], D3DPT_TRIANGLEFAN, 2, v, sizeof ( *v ) );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void d3d_texture_draw ( screen *texture, int x, int y )
{
	if ( f3d_scene_begin () )
	{
		struct
		{
			float x, y, z, r;
			float u, v;
		} v[] =
		{
			{ 0, 0, 1, 1, 0, 0 },
			{ 0, 0, 1, 1, 1, 0 },
			{ 0, 0, 1, 1, 1, 1 },
			{ 0, 0, 1, 1, 0, 1 },
		};
		v[0].x = x;
		v[0].y = y;
		v[1].x = x + texture->width;
		v[1].y = y;
		v[2].x = x + texture->width;
		v[2].y = y + texture->height;
		v[3].x = x;
		v[3].y = y + texture->height;

		set_d3d_alpha_fog_zbuffer ( TRUE, FALSE, FALSE, FALSE );
		set_d3d_texture_wrapping ( 0, FALSE );
		set_d3d_texture_mip_filtering ( FALSE );
		set_d3d_texture_mag_filtering ( FALSE );
		set_d3d_texture_min_filtering ( FALSE );
		set_d3d_flat_shaded_textured_renderstate ( texture );
		IDirect3DDevice9_SetFVF ( d3d_data.device[D3D_MAIN], D3DFVF_XYZRHW | D3DFVF_TEX1 );
		IDirect3DDevice9_DrawPrimitiveUP ( d3d_data.device[D3D_MAIN], D3DPT_TRIANGLEFAN, 2, v, sizeof ( *v ) );
		f3d_scene_end ();
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
	{ D3DERR_CONFLICTINGTEXTUREPALETTE, "D3DERR_CONFLICTINGTEXTUREPALETTE" },
	{ D3DERR_DRIVERINTERNALERROR, "D3DERR_DRIVERINTERNALERROR" },
	{ D3DERR_NOTFOUND, "D3DERR_NOTFOUND" },
	{ D3DERR_MOREDATA, "D3DERR_MOREDATA" },
	{ D3DERR_DEVICELOST, "D3DERR_DEVICELOST" },
	{ D3DERR_DEVICENOTRESET, "D3DERR_DEVICENOTRESET" },
	{ D3DERR_NOTAVAILABLE, "D3DERR_NOTAVAILABLE" },
	{ D3DERR_OUTOFVIDEOMEMORY, "D3DERR_OUTOFVIDEOMEMORY" },
	{ D3DERR_INVALIDDEVICE, "D3DERR_INVALIDDEVICE" },
	{ D3DERR_INVALIDCALL, "D3DERR_INVALIDCALL" },
	{ D3DERR_DRIVERINVALIDCALL, "D3DERR_DRIVERINVALIDCALL" },
	{ D3DERR_WASSTILLDRAWING, "D3DERR_WASSTILLDRAWING" },
	{ D3DOK_NOAUTOGEN, "D3DOK_NOAUTOGEN" },
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
