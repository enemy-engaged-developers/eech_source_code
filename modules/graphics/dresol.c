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



#include "graphics.h"
#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_GRAPHICS_RESOLUTION_MODES 256

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct RESOLUTION_INFO
{
	int
		width,
		height;
};
typedef struct RESOLUTION_INFO resolution_info;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	number_of_graphics_resolution_modes_available;

graphics_resolution_mode
	graphics_resolution_modes_available[MAX_GRAPHICS_RESOLUTION_MODES];


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*static*/ int create_test_d3d_device ( int width, int height );

/*static*/ void release_test_d3d_device ( void );

static int supported_resolution ( int width, int height );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_graphics_resolution_modes ( void )
{
	number_of_graphics_resolution_modes_available = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_graphics_resolution_index ( int width, int height )
{
	int
		count;

	for ( count = 0; count < number_of_graphics_resolution_modes_available; count++ )
	{
		if ( ( graphics_resolution_modes_available[count].width == width ) && ( graphics_resolution_modes_available[count].height == height ) )
		{
			return ( count );
		}
	}

	return ( -1 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int assess_graphic_device_resolutions ( void )
{
	int
		count;

	//
	// Go through all the physically available graphics modes, validating them
	//
	//	NB - this should only be used for FULLSCREEN running
	//

	number_of_graphics_resolution_modes_available = 0;

	if ( number_display_modes )
	{
		DWORD
			dwStyle;

		//
		// Setup the window style for a fullscreen application
		//
		dwStyle = GetWindowStyle ( application_window );
		dwStyle &= ~( WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX );
		dwStyle |= WS_POPUP;
		SetWindowLong ( application_window, GWL_STYLE, dwStyle );

		//
		// Go through all the graphics modes
		//
		for ( count = 0; count < number_display_modes; count++ )
		{
			{
				{
					int
						width,
						height;
					width = display_modes[count].ddsd.Width;
					height = display_modes[count].ddsd.Height;
					if ( supported_resolution ( width, height ) )
					{
						{
							debug_log ( "Graphics mode: %d x %d enabled", width, height );
							graphics_resolution_modes_available[number_of_graphics_resolution_modes_available].width = width;
							graphics_resolution_modes_available[number_of_graphics_resolution_modes_available].height = height;
							graphics_resolution_modes_available[number_of_graphics_resolution_modes_available].compressed_texture_mode = FALSE;

							number_of_graphics_resolution_modes_available++;
/*
							//
							// Create the d3d device & set its abilities
							//
							if ( create_test_d3d_device ( width, height ) )
							{
								//
								// Now check for available texture memory
								//
								initialise_system_texture_formats ();
								compress_system_textures = FALSE;
								{
									//
									// We can go into this mode
									//
									debug_log ( "Graphics mode: %d x %d enabled", width, height );
									graphics_resolution_modes_available[number_of_graphics_resolution_modes_available].width = width;
									graphics_resolution_modes_available[number_of_graphics_resolution_modes_available].height = height;
									graphics_resolution_modes_available[number_of_graphics_resolution_modes_available].compressed_texture_mode = FALSE;

									number_of_graphics_resolution_modes_available++;
								}
							}

							//
							// Release the d3d device
							//
							release_test_d3d_device ();
							*/
						}
					}
					else
						debug_log ( "%d x %d is below minimum resolution dimensions 640x480!", width, height );
				}
			}
		}
	}

	return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
int create_test_d3d_device ( int width, int height )
{
	D3DDEVICEDESC7
		hardware_desc;

	HRESULT
		d3drval;

	//
	// Get a d3d3 driver interface
	//

	d3drval = IDirectDraw7_QueryInterface ( ddraw.ddraw, &IID_IDirect3D7, ( LPVOID FAR * ) &d3d.d3d );
	if ( d3drval != DD_OK )
	{
		debug_log ( "Can't get a d3d device in this resolution" );
		return ( FALSE );
	}

	//
	// Query for a D3DDEVICE2 object
	//

	d3drval = IDirect3D7_CreateDevice ( d3d.d3d, &IID_IDirect3DHALDevice, ddraw.lpRenderBuffer, &d3d.device );
	if ( d3drval != DD_OK )
	{
		debug_log ( "Can't get a d3d device2 in this resolution" );
		return ( FALSE );
	}

	//
	// Get the capabilities of the device
	//

	d3drval = IDirect3DDevice7_GetCaps ( d3d.device, &hardware_desc );
	if ( d3drval != DD_OK )
	{
		debug_log ( "Unable to get the d3d device capabilities at this resolution" );
		return ( FALSE );
	}

	//
	// Set the capabilities of the 3dvisual according to the capabilities of the card.
	//
	set_d3d_capabilities ( &hardware_desc );

	//
	// Set render target
	//
	d3drval = IDirect3DDevice7_SetRenderTarget ( d3d.device, ddraw.lpRenderBuffer, 0 );
	if ( d3drval != DD_OK )
	{
		debug_log ( "Unable to set render target" );
		return ( FALSE );
	}

	{
		D3DVIEWPORT7
			viewdata;
		viewdata.dwX = 0;
		viewdata.dwY = 0;
		viewdata.dwWidth = application_video_width;
		viewdata.dwHeight = application_video_height;
		viewdata.dvMinZ = 0;
		viewdata.dvMaxZ = 1;
		if ( !f3d_set_viewport ( &viewdata ) )
		{
			debug_log ( "Unable to set viewport2: %d, %d, %s", application_video_width, application_video_height, get_d3d_error_message ( d3drval ) );
			return ( FALSE );
		}
	}

	//
	// Create the vertex buffers
	//
	create_d3d_vertex_buffers ();

	return ( TRUE );
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
void release_test_d3d_device ( void )
{
	HRESULT
		ddrval;

	destroy_d3d_vertex_buffers ();

	if ( d3d.d3d )
	{
		if ( d3d.device )
		{
			ddrval = IDirect3DDevice7_Release ( d3d.device );
			if ( ddrval < DD_OK )
			{
				debug_log ( "Unable to release d3d device: %s", get_d3d_error_message ( ddrval ) );
			}
			d3d.device = NULL;
		}

		if ( d3d.d3d )
		{
			ddrval = IDirect3D7_Release ( d3d.d3d );
			if ( ddrval < DD_OK )
			{
				debug_log ( "Unable to release d3d: %s", get_d3d_error_message ( ddrval ) );
			}
			d3d.d3d = NULL;
		}
	}
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int supported_resolution ( int width, int height )
{
	//Minimum supported screen resolution: 640x480
	//The maximum depends on your monitor and graphics card, and will be determined by DirectX.
	if ( ( width >= 800 ) && ( height >= 600 ) )
	{
		return ( TRUE );
	}
	return ( FALSE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
