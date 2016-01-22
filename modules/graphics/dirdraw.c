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



#ifndef OGRE_EE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "graphics.h"
#include "project.h"

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	application_video_width,
	application_video_height,
	application_video_windowed;

display_format
	display_modes[256];

int
	number_display_modes;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	number_of_display_devices;

display_device
	*display_devices;

static display_device
	*primary_display_device,
	*selected_display_device;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int
	graphics_initialised = FALSE;

HWND
	export_window;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void ddraw_restore_objects ( int activate );

static void ddraw_enum_modes ( D3DDISPLAYMODE* mode );

static void ddraw_enumerate_adapters ( unsigned adapter );

BOOL ddraw_initialise ( GUID *device_guid );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL initialise_graphics_system ( GUID *device_guid )
{

	ASSERT ( !graphics_initialised );

	initialise_graphics_colours ();

	register_exit_function ( ( void ( * ) ( void ) ) ddraw_release_objects );

	initialise_system_graphics_screens ();

	initialise_psd_layers ();

	if ( !ddraw_initialise ( device_guid ) )
	{

		return ( FALSE );
	}

	graphics_initialised = TRUE;

	register_post_activate_message_function ( ddraw_restore_objects );

	//
	// Reset the fpu rounding modes!
	//

	set_fpu_rounding_mode_zero ();

	return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_ddraw_use_full_screen ( int flag )
{

	application_video_windowed = !flag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_graphics_system_initialised ( void )
{

	return ( graphics_initialised );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void get_monitor_info ( int d3d )
{
	HMONITOR
		hmonitor;
	MONITORINFO
		monitorinfo;

	d3d_data.x[d3d] = 0;
	d3d_data.y[d3d] = 0;

	hmonitor = IDirect3D9_GetAdapterMonitor ( d3d_common.d3d, d3d_data.selected_adapter[d3d] );
	if ( hmonitor == NULL )
	{
		return;
	}
	memset ( &monitorinfo, 0, sizeof ( monitorinfo ) );
	monitorinfo.cbSize = sizeof ( monitorinfo );
	GetMonitorInfoW ( hmonitor, &monitorinfo );
	d3d_data.x[d3d] = monitorinfo.rcWork.left;
	d3d_data.y[d3d] = monitorinfo.rcWork.top;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int create_export_window ( void *arg )
{
	export_window = CreateWindowEx
	(

		0,
		"HELLO",	//NAME,
		"Export Window",	//TITLE,
		WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_VISIBLE,
		0,
		40,
		200,
		20,
		NULL,
		NULL,
		application_instance,
		NULL
	);

	if ( !export_window )
	{

		return ( FALSE );
	}

	ShowWindow ( export_window, SW_SHOWDEFAULT );

	UpdateWindow ( export_window );

	return ( TRUE );
}

BOOL ddraw_initialise ( GUID *device_guid )
{

	unsigned
		count,
		i,
		j,
		k;

	number_of_display_devices = 0;

	display_devices = NULL;

	selected_display_device = NULL;

	//
	// Always enumerate the drivers
	//

	d3d_common.d3d = Direct3DCreate9 ( D3D_SDK_VERSION );

	if ( !d3d_common.d3d )
	{
		debug_log ( "Failed to create Direct3D9 object" );
		return FALSE;
	}

	count = IDirect3D9_GetAdapterCount ( d3d_common.d3d );

	for ( i = 0; i < count; i++ )
	{
		ddraw_enumerate_adapters ( i );
	}

	if ( !primary_display_device )
	{
		debug_log ( "No video adapters found" );
		return FALSE;
	}

	d3d_data.selected_adapter[D3D_MAIN] = D3DADAPTER_DEFAULT;
	if ( device_guid )
	{
		for ( selected_display_device = display_devices; selected_display_device; selected_display_device = selected_display_device->succ )
		{
			if ( !memcmp ( &selected_display_device->guid, device_guid, sizeof ( GUID ) ) && selected_display_device->number_of_heads )
			{
				d3d_data.selected_adapter[D3D_MAIN] = selected_display_device->index;
				break;
			}
		}
	}
	if ( !selected_display_device )
	{
		selected_display_device = primary_display_device;
	}
	get_monitor_info ( D3D_MAIN );

	//
	// Enumerate the display modes this object is capable of
	//

	number_display_modes = 0;

	count = IDirect3D9_GetAdapterModeCount ( d3d_common.d3d, d3d_data.selected_adapter[D3D_MAIN], D3DFMT_X8R8G8B8 );
	for ( i = 0; i < count; i++ )
	{
		D3DDISPLAYMODE
			mode;

		IDirect3D9_EnumAdapterModes ( d3d_common.d3d, d3d_data.selected_adapter[D3D_MAIN], D3DFMT_X8R8G8B8, i, &mode );
		ddraw_enum_modes ( &mode );
	}

	if ( !number_display_modes )
	{

		debug_log ( "Unable to enumerate display modes" );

		return FALSE;
	}

	count = number_display_modes;
	for ( i = 0; i < count - 1; i++ )
	{
		k = i;
		for ( j = i + 1; j < count; j++ )
		{
			if ( display_modes[j].ddsd.Width > display_modes[k].ddsd.Width || display_modes[j].ddsd.Width == display_modes[k].ddsd.Width && display_modes[j].ddsd.Height < display_modes[k].ddsd.Height )
			{
				k = j;
			}
		}
		if ( k != i )
		{
			display_format
				tmp;

			tmp = display_modes[i];
			display_modes[i] = display_modes[k];
			display_modes[k] = tmp;
		}
	}

	//
	// Initialise the graphics modes availability
	//

	initialise_graphics_resolution_modes ();

	d3d_common.mfd = MFD_NONE;
	if ( command_line_export_mfd && command_line_export_mfd_adapter >= 0 )
	{
		display_device
			*export_display_device;
		int
			index;

		d3d_data.selected_adapter[D3D_MFD] = -1;
		export_display_device = display_devices;
		for ( index = 0; index < command_line_export_mfd_adapter; index++ )
		{
			export_display_device = export_display_device->succ;
			if  ( !export_display_device )
			{
				debug_log ( "wrong adapternumber (export_mfd):");
				return FALSE;
			}
		}
		d3d_data.selected_adapter[D3D_MFD] = export_display_device->index;
		d3d_common.mfd = MFD_WINDOW;
		if ( !application_video_windowed )
		{
			if ( !memcmp ( &export_display_device->guid, &selected_display_device->guid, sizeof ( GUID ) ) )
			{
				if ( selected_display_device->number_of_heads == 2 && application_video_width == command_line_export_mfd_screen_width && application_video_height == command_line_export_mfd_screen_height )
				{
					d3d_common.mfd = MFD_MULTIHEAD;
				}
			}
			else
			{
				d3d_common.mfd = MFD_FULLSCREEN;
			}
		}
		get_monitor_info ( D3D_MFD );
		system_thread_function ( create_export_window, NULL );
		if ( !export_window )
		{
			debug_log ( "Failed to create export window" );
			return FALSE;
		}
	}

	return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_ddraw_device_guid ( GUID *this_guid )
{

	D3DADAPTER_IDENTIFIER9
		did;

	HRESULT
		ret;

	if ( d3d_common.d3d )
	{

		ret = IDirect3D9_GetAdapterIdentifier ( d3d_common.d3d, d3d_data.selected_adapter[D3D_MAIN], 0, &did );

		*this_guid = did.DeviceIdentifier;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void ddraw_restore_objects ( int activate )
{

	if ( activate )
	{

		if ( !application_video_windowed )
		{

			if ( d3d_common.d3d )
			{

				d3d_common.recreate_d3d = TRUE;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL ddraw_release_objects ( void )
{

	int
		refs;

	if ( d3d_common.d3d )
	{
		refs = IDirect3D9_Release ( d3d_common.d3d );

		if ( refs != 0 )
		{
			debug_log ( "Unable to release d3d: %s", get_d3d_error_message ( refs ) );
		}

		d3d_common.d3d = NULL;
	}

	while ( display_devices )
	{
		display_device
			*device;

		device = display_devices;
		display_devices = display_devices->succ;
		if ( device->name )
			safe_free ( device->name );
		safe_free ( device );
	}

	return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_one_mfd ( LPDIRECT3DDEVICE9 device, struct DIRECT_3D_EXPORT_MFD *mfd, int left, int top, int right, int bottom )
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

	if ( !mfd->texture || !mfd->updated )
		return;

	v[0].x = left;
	v[0].y = top;
	v[1].x = right;
	v[1].y = top;
	v[2].x = right;
	v[2].y = bottom;
	v[3].x = left;
	v[3].y = bottom;
	IDirect3DDevice9_SetTexture ( device, 0, ( LPDIRECT3DBASETEXTURE9 ) mfd->texture );
	IDirect3DDevice9_SetTextureStageState ( device, 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
	IDirect3DDevice9_SetFVF ( device, D3DFVF_XYZRHW | D3DFVF_TEX1 );
	IDirect3DDevice9_DrawPrimitiveUP ( device, D3DPT_TRIANGLEFAN, 2, v, sizeof ( *v ) );
}

static void set_swap_chain ( int d3d )
{
	LPDIRECT3DSWAPCHAIN9
		sc;
	LPDIRECT3DSURFACE9
		bb;

	IDirect3DDevice9_GetSwapChain ( d3d_data.device[D3D_MAIN], d3d, &sc );
	IDirect3DSwapChain9_GetBackBuffer ( sc, 0, D3DBACKBUFFER_TYPE_MONO, &bb );
	IDirect3DDevice9_SetRenderTarget ( d3d_data.device[D3D_MAIN], 0, bb );
	IDirect3DSurface9_Release ( bb );
	IDirect3DSwapChain9_Release ( sc );
}

static void ddraw_flip_surface_export ( void )
{
	LPDIRECT3DDEVICE9
		device;

	if ( !d3d_data.device[D3D_MFD] )
	{
		device = d3d_data.device[D3D_MAIN];
		set_swap_chain ( D3D_MFD );
	}
	else
	{
		device = d3d_data.device[D3D_MFD];
	}
	IDirect3DDevice9_Clear ( device, 0, NULL, D3DCLEAR_TARGET, 0, 0.0f, 0 );
	if ( FAILED ( IDirect3DDevice9_BeginScene ( device ) ) )
		return;
	switch ( get_global_gunship_type () )
	{
		case GUNSHIP_TYPE_HAVOC:
		case GUNSHIP_TYPE_KA50:
		case GUNSHIP_TYPE_HIND:
			draw_one_mfd ( device, &d3d_export_mfd[0], command_line_export_mfd_single_pos[0], command_line_export_mfd_single_pos[1], command_line_export_mfd_single_pos[2], command_line_export_mfd_single_pos[3] );
			break;
		case GUNSHIP_TYPE_COMANCHE:
		case GUNSHIP_TYPE_HOKUM:
		case GUNSHIP_TYPE_APACHE:
		case GUNSHIP_TYPE_BLACKHAWK:
		case GUNSHIP_TYPE_VIPER:
		case GUNSHIP_TYPE_KIOWA:
		default:
			draw_one_mfd ( device, &d3d_export_mfd[0], command_line_export_mfd_left_pos[0], command_line_export_mfd_left_pos[1], command_line_export_mfd_left_pos[2], command_line_export_mfd_left_pos[3] );
			draw_one_mfd ( device, &d3d_export_mfd[1], command_line_export_mfd_right_pos[0], command_line_export_mfd_right_pos[1], command_line_export_mfd_right_pos[2], command_line_export_mfd_right_pos[3] );
			break;
	}
	IDirect3DDevice9_EndScene ( device );
	if ( !d3d_data.device[D3D_MFD] )
	{
		set_swap_chain ( D3D_MAIN );
	}
	else
	{
		IDirect3DDevice9_Present ( device, NULL, NULL, NULL, NULL );
	}
	d3d_export_mfd[0].updated = FALSE;
	d3d_export_mfd[1].updated = FALSE;
}

BOOL ddraw_flip_surface ( void )
{

	total_number_of_d3d_triangles = running_total_number_of_d3d_triangles;

	total_number_of_d3d_flushes = running_total_number_of_d3d_flushes;

	running_total_number_of_d3d_triangles = 0;

	running_total_number_of_d3d_flushes = 0;

	if ( d3d_common.mfd != MFD_NONE )
		ddraw_flip_surface_export ();
	IDirect3DDevice9_Present ( d3d_data.device[D3D_MAIN], NULL, NULL, NULL, NULL );
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_window_size ( HWND hwnd, int width, int height, int d3d )
{
	DWORD
		dwStyle;

	RECT
		rc;

	dwStyle = GetWindowStyle ( hwnd );

	dwStyle &= ~(WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX);

	dwStyle |= WS_POPUP;

	SetWindowLong ( hwnd, GWL_STYLE, dwStyle );

	//
	// Position the window properly
	//

	rc.left = 0;
	rc.top = 0;
	rc.right = width;
	rc.bottom = height;

	AdjustWindowRectEx ( &rc, GetWindowStyle ( hwnd ), GetMenu ( hwnd ) != NULL, GetWindowExStyle ( hwnd ) );

	rc.right += d3d_data.x[d3d] - rc.left;
	rc.bottom += d3d_data.x[d3d] - rc.top;
	rc.left = d3d_data.x[d3d];
	rc.top = d3d_data.y[d3d];

	SetWindowPos ( hwnd, NULL, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOACTIVATE );

	if ( hwnd == application_window )
		SetWindowPos ( hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL ddraw_set_display_resolution ( int width, int height )
{
	ASSERT ( get_graphics_system_initialised () );

	application_video_height = height;

	application_video_width = width;

	set_viewport ( 0, 0, width, height );

	if ( !application_video_windowed )
	{

		//
		// Create the screen associated with the render buffer ( video_screen )
		//

		create_video_screen ( width, height );
	}
	else
	{
		set_window_size ( application_window, width, height, D3D_MAIN );

		create_video_screen ( width, height );
	}

	if ( command_line_export_mfd && export_window )
	{
		set_window_size ( export_window, command_line_export_mfd_screen_width, command_line_export_mfd_screen_height, D3D_MFD );
	}

	return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL ddraw_change_display_resolution ( int width, int height )
{
	HRESULT
		ret;

	RECT
		rc,
		rcWork;

	BOOL
		windowed;

	ASSERT ( get_graphics_system_initialised () );

	application_video_height = height;
	application_video_width = width;

	set_basic_viewport ( 0, 0, application_video_width, application_video_height );

	windowed = application_video_windowed;

	if ( application_video_windowed )
	{

		//
		// Position the window properly
		//

		rc.top = 0;
		rc.left = 0;
		rc.bottom = height;
		rc.right = width;

		AdjustWindowRectEx ( &rc, GetWindowStyle ( application_window), GetMenu ( application_window) != NULL, GetWindowExStyle ( application_window ) );
		SetWindowPos ( application_window, NULL, 0, 0, rc.right-rc.left, rc.bottom-rc.top, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE );
		SetWindowPos ( application_window, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE );

		//
		// Make sure window does not hang off the screen
		//

		SystemParametersInfo ( SPI_GETWORKAREA, 0, &rcWork, 0 );

		GetWindowRect ( application_window, &rc );

		if ( rc.left < rcWork.left )
		{

			rc.left = rcWork.left;
		}

		if ( rc.top  < rcWork.top )
		{

			rc.top  = rcWork.top;
		}

		SetWindowPos ( application_window, NULL, rc.left, rc.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE );
		}

		release_video_screens ();

		//
		// Set the video mode
		//

		{
			int
				param[2];

			param[0] = width;
			param[1] = height;

			ret = system_thread_function ( ddraw_internal_set_display_mode, param );
		}

		if( FAILED ( ret ) )
		{

			debug_log ( "Unable to set display resolution: %s", get_d3d_error_message ( ret ) );

			return ( FALSE );
		}

		initialise_d3d_state ();

		recreate_video_screens ();

		//
		// Create the screen associated with the render buffer ( video_screen )
		//

		create_video_screen ( width, height );

		return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ddraw_internal_set_display_mode ( void *data )
{

	HRESULT
		ret;

	int
		*ptr;

	ptr = ( int * ) data;

	debug_log ( "Setting video mode %ix%i", ptr[0], ptr[1] );

	d3d_data.d3dpp[D3D_MAIN].BackBufferWidth = ptr[0];
	d3d_data.d3dpp[D3D_MAIN].BackBufferHeight = ptr[1];
	if ( d3d_common.mfd == MFD_MULTIHEAD )
	{
		d3d_data.d3dpp[D3D_MFD].BackBufferWidth = ptr[0];
		d3d_data.d3dpp[D3D_MFD].BackBufferHeight = ptr[1];
	}

	ret = IDirect3DDevice9_Reset ( d3d_data.device[D3D_MAIN], &d3d_data.d3dpp[D3D_MAIN] );

	return ( ret );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void ddraw_enum_modes ( D3DDISPLAYMODE* mode )
{
	int
		i;

	if ( number_display_modes == 255 )
	{
		return;
	}

	//
	// Set the surface description
	//

	memset ( &display_modes[number_display_modes], 0, sizeof ( display_format ) );

	display_modes[number_display_modes].ddsd = *mode;

	//
	// Assess the format
	//

	debug_log ( "Graphics adapter supports resolution %i x %i", mode->Width, mode->Height );

	if ( mode->Width >= 800 && mode->Height >= 600 )
	{
		for ( i = 0; i < number_display_modes; i++ )
		{
			if ( display_modes[i].ddsd.Width == mode->Width && display_modes[i].ddsd.Height == mode->Height )
			{
				return;
			}
		}

		debug_log ( "Resolution %i x %i accepted", mode->Width, mode->Height );
		number_display_modes++;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void ddraw_enumerate_adapters ( unsigned adapter )
{
	HRESULT
		ret;

	D3DADAPTER_IDENTIFIER9
		id;

	D3DCAPS9
		caps;

	ret = IDirect3D9_CheckDeviceType ( d3d_common.d3d, adapter, D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8, D3DFMT_X8R8G8B8, application_video_windowed );
	if ( FAILED ( ret ) )
	{
		return;
	}

	ret = IDirect3D9_GetAdapterIdentifier ( d3d_common.d3d, adapter, 0, &id );
	if ( FAILED ( ret ) )
	{
		debug_log ( "Unable to enumerate adapters: %s", get_d3d_error_message ( ret ) );
		return;
	}

	ret = IDirect3D9_GetDeviceCaps ( d3d_common.d3d, adapter, D3DDEVTYPE_HAL, &caps );
	if ( FAILED ( ret ) )
	{
		debug_log ( "Unable to enumerate adapters: %s", get_d3d_error_message ( ret ) );
		return;
	}

	{

		display_device
			*device;

		//
		// Add this driver to the list
		//

		device = ( display_device * ) safe_malloc ( sizeof ( display_device ) );

		device->succ = display_devices;

		device->name = ( char *) safe_malloc ( strlen ( id.Description ) + 1 );

		strcpy ( device->name, id.Description );

		device->index = adapter;
		if ( adapter == D3DADAPTER_DEFAULT )
		{
			device->is_primary = TRUE;
			primary_display_device = device;
		}
		else
		{
			device->is_primary = FALSE;
		}
		device->number_of_heads = caps.NumberOfAdaptersInGroup;
		device->guid = id.DeviceIdentifier;

		display_devices = device;

		number_of_display_devices++;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void copy_export_mfd_one ( struct DIRECT_3D_EXPORT_MFD *mfd, screen *src )
{
	HRESULT
		res;

	LPDIRECT3DSURFACE9
		ssurface,
		dsurface;

	D3DLOCKED_RECT
		srect,
		drect;

	if ( !src )
		return;

	if ( mfd->texture && ( mfd->width != src->width || mfd->height != src->height ) )
	{
		IDirect3DTexture9_Release ( mfd->texture );
		mfd->texture = NULL;
	}

	res = IDirect3DTexture9_GetSurfaceLevel ( src->texture, 0, &ssurface );
	if ( src->role == TEXTURE_ROLE_RENDER_TARGET )
	{
		if ( !FAILED ( res ) )
		{
			res = IDirect3DDevice9_CreateOffscreenPlainSurface ( d3d_data.device[D3D_MAIN], src->width, src->height, D3DFMT_X8R8G8B8, D3DPOOL_SYSTEMMEM, &dsurface, NULL );
		}
		if ( !FAILED ( res ) )
		{
			res = IDirect3DDevice9_GetRenderTargetData ( d3d_data.device[D3D_MAIN], ssurface, dsurface );
		}
		if ( ssurface )
			IDirect3DSurface9_Release ( ssurface );
	}
	else
	{
		dsurface = ssurface;
	}
	if ( !FAILED ( res ) && !mfd->texture )
	{
		res = IDirect3DDevice9_CreateTexture ( d3d_data.device[D3D_MFD] ? d3d_data.device[D3D_MFD] : d3d_data.device[D3D_MAIN], src->width, src->height, 1, 0, D3DFMT_X8R8G8B8, D3DPOOL_MANAGED, &mfd->texture, NULL );
		mfd->width = src->width;
		mfd->height = src->height;
	}
	if ( !FAILED ( res ) )
	{
		res = IDirect3DSurface9_LockRect ( dsurface, &srect, NULL, 0 );
	}
	if ( !FAILED ( res ) )
	{
		ASSERT ( !( srect.Pitch & 3 ) );
		res = IDirect3DTexture9_LockRect ( mfd->texture, 0, &drect, NULL, 0 );
		if ( !FAILED ( res ) )
		{
			ASSERT ( !( drect.Pitch & 3 ) );
			if ( srect.Pitch == drect.Pitch )
				memcpy ( drect.pBits, srect.pBits, drect.Pitch * src->height );
			IDirect3DTexture9_UnlockRect ( mfd->texture, 0 );
		}
		IDirect3DSurface9_UnlockRect ( dsurface );
	}
	if ( dsurface )
		IDirect3DSurface9_Release ( dsurface );
	if ( !FAILED ( res ) )
	{
		mfd->updated = TRUE;
	}
}

void copy_export_mfd ( screen *export_left, screen *export_right )
{
	if ( d3d_common.mfd != MFD_NONE )
	{
		copy_export_mfd_one ( &d3d_export_mfd[0], export_left );
		copy_export_mfd_one ( &d3d_export_mfd[1], export_right );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
