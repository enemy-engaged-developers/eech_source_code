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
#include "cmndline.h"
#include "global.h"
//#include "external\pixel.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DirectDraw supports the following functions:
//
//		initialise_graphics				- creates the DirectDraw object.
//		ddraw_restore_objects			- restores all the direct_draw objects.
//		ddraw_release_objects			- destroys all the direct_draw objects.
//		ddraw_set_display_resolution	- sets the video resolution and window status ( either fullscreen, or window )
//		ddraw_lock_video_memory			- returns a pointer and pitch to the current secondary surface
//		ddraw_unlock_video_memory		- returns the surface to direct draw.
//		ddraw_lock_surface				- returns a pointer and pitch to the surface specified
//		ddraw_unlock_surface				- returns the surface to direct draw.
//
//		ddraw_flip_surface				- flips the secondary & primary surfaces around
//		ddraw_create_surface				- creates a surface, the same format as the display surface.
//		ddraw_destroy_surface			- destroys the surface.
//
//
// Additionally, some internal routines are also available. This is because all the actual creating and destroying
//  of objects, and also restoration of the objects have to be done in the parent thread. If you are actually running
//  as the parent thread, you MUST used these internal routines. Likewise, if you are NOT in the parent thread, you
//  must NOT use these internal routines. You are running in the parent thread if the routine has been called from a
//  message being sent to the main window.
//
//		ddraw_internal_release_objects
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	zbuffer_on_video = TRUE,
	application_video_width,
	application_video_height,
	application_video_colourdepth,
	best_assessment;

LPDIRECTDRAWSURFACEX
	zbuffer_target_surface;

PALETTEENTRY
	system_colour_table[256];

display_format
	display_modes[256];

int
	number_display_modes;

struct direct_draw_data
	ddraw =
	{
		NULL,							// LPDIRECTDRAW7 ddrawX

		TRUE,							// BOOL use_double_buffer
		TRUE,							// BOOL use_full_screen,
		FALSE,						// BOOL use_software_driver
		FALSE,						// BOOL use_system_memory
		FALSE,						// BOOL use_z_buffer,

		NULL,							//	LPDIRECTDRAWSURFACE lpFrontBuffer
		NULL,							//	LPDIRECTDRAWSURFACE lpBackBuffer
		NULL,							//	LPDIRECTDRAWSURFACE lpRenderBuffer
		NULL,							//	LPDIRECTDRAWSURFACE lpZBuffer

		NULL,							//	LPDIRECTDRAWCLIPPER lpClipper

		FALSE,						//	BOOL application_windowed

		0,								//	int windows_width,
		0,								//	int windows_height,
		0,								//	int windows_depth;

		16,							// int application_display_depth
	},

	ddraw_export =
	{
		NULL,							// LPDIRECTDRAW7 ddrawX

		TRUE,							// BOOL use_double_buffer
		TRUE,							// BOOL use_full_screen,
		FALSE,						// BOOL use_software_driver
		FALSE,						// BOOL use_system_memory
		FALSE,						// BOOL use_z_buffer,

		NULL,							//	LPDIRECTDRAWSURFACE lpFrontBuffer
		NULL,							//	LPDIRECTDRAWSURFACE lpBackBuffer
		NULL,							//	LPDIRECTDRAWSURFACE lpRenderBuffer
		NULL,							//	LPDIRECTDRAWSURFACE lpZBuffer

		NULL,							//	LPDIRECTDRAWCLIPPER lpClipper

		FALSE,						//	BOOL application_windowed

		0,								//	int windows_width,
		0,								//	int windows_height,
		0,								//	int windows_depth;

		16,							// int application_display_depth
	};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	number_of_display_devices;

display_device
	*display_devices,
	*best_display_device,
	*current_display_device;

ddraw_initialisation_errors
	direct_draw_initialisation_error;

DDPIXELFORMAT
	current_zbuffer_pixel_format;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int
	graphics_initialised = FALSE;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_ddraw_memory_config ( void );

static void ddraw_restore_objects ( int activate );

static int ddraw_validate_basic_3d_properties ( void );

static HRESULT FAR PASCAL ddraw_enum_modes 	( LPDDSURFACEDESC2 lpddsd, LPVOID Context );

static BOOL WINAPI ddraw_enumerate_drivers ( GUID FAR* lpGUID, LPSTR lpDriverDesc, LPSTR lpDriverName, LPVOID lpContext, HMONITOR hm );

static HRESULT WINAPI ddraw_enumerate_zbuffer_formats ( DDPIXELFORMAT *format, void *choice );

static void save_system_palette ( void );

BOOL ddraw_initialise ( GUID *device_guid );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL initialise_graphics_system ( GUID *device_guid )
{

	ASSERT ( !graphics_initialised );

	save_system_palette ();

	initialise_graphics_colours ();

	register_exit_function ((void *)ddraw_release_objects );

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

void set_ddraw_use_double_buffering ( int flag )
{

	ddraw.use_double_buffer = flag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_ddraw_use_software_driver ( int flag )
{

	ddraw.use_software_driver = flag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_ddraw_use_system_memory ( int flag )
{

	ddraw.use_system_memory = flag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_ddraw_use_z_buffer ( int flag )
{

	ddraw.use_z_buffer = flag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_ddraw_use_full_screen ( int flag )
{

	ddraw.use_full_screen = flag;
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

void set_ddraw_application_display_depth ( int depth )
{

	ASSERT ( ( depth == 16 ) || ( depth == 32 ) );

	ddraw.application_display_depth = depth;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL ddraw_initialise ( GUID *device_guid )
{
	
	HRESULT
		ret;

	int
		non_display_flag;

	display_device *export_display_device;

	ddraw.ddraw = NULL;
	ddraw_export.ddraw = NULL;

	ddraw.ddraw_valid = FALSE;
	ddraw_export.ddraw_valid = FALSE;

	number_of_display_devices = 0;

	display_devices = NULL;

	best_display_device = NULL;

	current_display_device = NULL;

	best_assessment = 0;

	//
	// Always enumerate the drivers
	//

	non_display_flag = FALSE;

	ret = DirectDrawEnumerateEx ( ddraw_enumerate_drivers, &non_display_flag, DDENUM_DETACHEDSECONDARYDEVICES|DDENUM_ATTACHEDSECONDARYDEVICES );// | DDENUM_NONDISPLAYDEVICES );

	if ( FAILED ( ret ) )
	{

		debug_log ( "Unable to enumerate direct draw objects: %s", get_ddraw_error_message ( ret ) );

		direct_draw_initialisation_error = DDRAW_INIT_UNABLE_TO_ENUMERATE;

		return ( FALSE );
	}

	//
	// Now enumerate any non-display devices
	//

	non_display_flag = TRUE;

	ret = DirectDrawEnumerateEx ( ddraw_enumerate_drivers, &non_display_flag, DDENUM_NONDISPLAYDEVICES );

	if ( FAILED ( ret ) )
	{

		debug_log ( "Unable to enumerate non display direct draw objects: %s", get_ddraw_error_message ( ret ) );
	}

	//
	//
	//

	if ( ( device_guid ) && ( ddraw.use_full_screen ) && ( !ddraw.use_software_driver ) )
	{

		display_device
			*device;

		device = display_devices;

		while ( device )
		{

			if ( !device->is_primary )
			{

				if ( memcmp ( device_guid, &device->guid, sizeof ( GUID ) ) == 0 )
				{

					ret = DirectDrawCreateEx ( &device->guid, ( LPVOID * ) &ddraw.ddraw, &IID_IDirectDraw7, NULL );
			
					if ( FAILED ( ret ) )
					{
			
						debug_log ( "Unable to create direct draw object: %s", get_ddraw_error_message ( ret ) );
					}
					else
					{
		
						//
						// Set the current display device
						//
		
						current_display_device = best_display_device;

						break;
					}
				}
			}

			device = device->succ;
		}
	}
	else if ( best_display_device )
	{

		//
		// If we're running fullscreen, or its the primary, we can use it.
		//
	
		if ( ( ( best_display_device->is_primary ) || ( ddraw.use_full_screen ) ) && ( !ddraw.use_software_driver ) )
		{

			if ( best_display_device->is_primary )
			{
	
				ret = DirectDrawCreateEx ( NULL, ( LPVOID * ) &ddraw.ddraw, &IID_IDirectDraw7, NULL );
			}
			else
			{

				ret = DirectDrawCreateEx ( &best_display_device->guid, ( LPVOID * ) &ddraw.ddraw, &IID_IDirectDraw7, NULL );
			}
	
			if ( FAILED ( ret ) )
			{

				debug_log ( "Unable to create direct draw object: %s", get_ddraw_error_message ( ret ) );
			}
			else
			{

				//
				// Set the current display device
				//

				current_display_device = best_display_device;
			}
		}
	}

	//
	// If we've not managed to create direct draw yet, default to the primary display
	//

	if ( !ddraw.ddraw )
	{

		ret = DirectDrawCreateEx ( NULL, ( LPVOID * ) &ddraw.ddraw, &IID_IDirectDraw7, NULL );

		if ( FAILED ( ret ) )
		{

			debug_log ( "Unable to create direct draw object: %s", get_ddraw_error_message ( ret ) );

			direct_draw_initialisation_error = DDRAW_INIT_UNABLE_TO_CREATE_DDRAW;

			return ( FALSE );
		}
	}

	//
	// Enumerate the display modes this object is capable of
	//

	number_display_modes = 0;
	
	ret = IDirectDraw7_EnumDisplayModes ( ddraw.ddraw, 0, NULL, NULL, ddraw_enum_modes );

	if ( FAILED ( ret ) )
	{

		debug_log ( "Unable to enumerate display modes: %s", get_ddraw_error_message ( ret ) );

		direct_draw_initialisation_error = DDRAW_INIT_UNABLE_TO_ENUMERATE_DISPLAY_MODES;

		return ( FALSE );
	}

	//
	// Check the device has the 3d capabilities needed
	//

	if ( !ddraw_validate_basic_3d_properties () )
	{

		direct_draw_initialisation_error = DDRAW_INIT_NO_3D_CARD;

		return ( FALSE );
	}

	//
	// Get a d3d driver interface
	//

	ret = IDirectDraw7_QueryInterface ( ddraw.ddraw, &IID_IDirect3D7, ( LPVOID FAR * ) &d3d.d3d );

	if ( ret != DD_OK )
	{

		debug_fatal ( "Unable to get a Direct3D driver from DirectX: %s", get_ddraw_error_message ( ret ) );

		return ( FALSE );
	}

	//
	// Initialise the graphics modes availability
	//

	initialise_graphics_resolution_modes ();

	//
	// Get the memory configuration of the device
	//

	set_ddraw_memory_config ();

	ddraw.ddraw_valid = TRUE;
	
	if(command_line_export_mfd)
	{
		int index;
		export_display_device=display_devices;
		for(index=0;index<command_line_export_mfd_adapter;index++)
		{
			export_display_device=export_display_device->succ;
			if(!export_display_device)
			{
				debug_log ( "wrong adapternumber (export_mfd):");
				return (FALSE);
			}
		}

		ret = DirectDrawCreateEx ( &export_display_device->guid, ( LPVOID * ) &ddraw_export.ddraw, &IID_IDirectDraw7, NULL );
		if ( FAILED ( ret ) )
		{
			debug_log ( "Unable to create direct draw object (export_mfd): %s", get_ddraw_error_message ( ret ) );
			direct_draw_initialisation_error = DDRAW_INIT_UNABLE_TO_CREATE_DDRAW;
			return (FALSE);
		}
		ddraw_export.ddraw_valid=TRUE;
		
	}	

	return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_ddraw_memory_config ( void )
{

	DWORD
		free;

	DDSCAPS2
		caps;

	memset ( &caps, 0, sizeof ( caps ) );

	caps.dwCaps = DDSCAPS_VIDEOMEMORY | DDSCAPS_LOCALVIDMEM;

	IDirectDraw7_GetAvailableVidMem ( ddraw.ddraw, &caps, ( DWORD * ) &d3d_total_video_memory, &free );

	memset ( &caps, 0, sizeof ( caps ) );

	caps.dwCaps = DDSCAPS_TEXTURE | DDSCAPS_VIDEOMEMORY | DDSCAPS_LOCALVIDMEM;

	IDirectDraw7_GetAvailableVidMem ( ddraw.ddraw, &caps, ( DWORD * ) &d3d_total_video_texture_memory, &free );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_ddraw_device_guid ( GUID *this_guid )
{

	DDDEVICEIDENTIFIER2
		did;

	HRESULT
		ret;

	if ( ddraw.ddraw )
	{

		ret = IDirectDraw7_GetDeviceIdentifier ( ddraw.ddraw, &did, 0 );

		memcpy ( this_guid, &did.guidDeviceIdentifier, sizeof ( GUID ) );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void ddraw_restore_objects ( int activate )
{

	if ( activate )
	{

		if ( !ddraw.application_windowed )
		{
	
			if ( ddraw.ddraw )
			{
	
				IDirectDraw7_RestoreAllSurfaces ( ddraw.ddraw );

				d3d.recreate_d3d = TRUE;
			}
		}
			if ( ddraw_export.ddraw )
			{
	
				IDirectDraw7_RestoreAllSurfaces ( ddraw_export.ddraw );
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

	if ( ddraw.ddraw )
	{

		if ( d3d.d3d )
		{
	
			refs = IDirect3D7_Release ( d3d.d3d );

			if ( refs < DD_OK )
			{
	
				debug_log ( "Unable to release d3d: %s", get_d3d_error_message ( refs ) );
			}
	
			d3d.d3d = NULL;
		}

		if ( ddraw.lpClipper )
		{

			//
			// Detach it from the primary screen
			//

			IDirectDrawSurface7_SetClipper ( ddraw.lpFrontBuffer, NULL );

			IDirectDrawClipper_Release ( ddraw.lpClipper );

			ddraw.lpClipper = NULL;
		}

		//
		// Remove the ZBuffer
		//

		if ( ddraw.lpZBuffer )
		{

			HRESULT
				ret;

			ret = IDirectDrawSurface7_DeleteAttachedSurface ( ddraw.lpRenderBuffer, 0, ddraw.lpZBuffer );

			if ( ret != DD_OK )
			{

				debug_log ( "Unable to delete the zbuffer from the render buffer: %s", get_ddraw_error_message ( ret ) );
			}

			refs = IDirectDrawSurface7_Release ( ddraw.lpZBuffer );

			ddraw.lpZBuffer = NULL;
		}

		if ( ddraw.application_windowed )
		{

			if ( ddraw.lpFrontBuffer )
			{

				IDirectDrawSurface7_Release ( ddraw.lpFrontBuffer );

				ddraw.lpFrontBuffer = NULL;
	
				if ( ddraw.lpBackBuffer )
				{
	
					IDirectDrawSurface7_Release ( ddraw.lpBackBuffer );
	
					ddraw.lpBackBuffer = NULL;
				}
			}
		}
		else
		{

			if ( ddraw.lpFrontBuffer )
			{

				if ( ddraw.use_double_buffer )
				{

					IDirectDrawSurface7_Release ( ddraw.lpBackBuffer );

					ddraw.lpBackBuffer = NULL;

					ddraw.lpRenderBuffer = NULL;
				}

				IDirectDrawSurface7_Release ( ddraw.lpFrontBuffer );

				ddraw.lpFrontBuffer = NULL;
			}

			if ( ddraw.use_system_memory )
			{

				if ( ddraw.lpRenderBuffer )
				{

					IDirectDrawSurface7_Release ( ddraw.lpRenderBuffer );

					ddraw.lpRenderBuffer = NULL;
				}
			}
		}

		ddraw_set_cooperative_level ( COOPERATIVE_LEVEL_NORMAL );

		refs = IDirectDraw7_Release ( ddraw.ddraw );

		ddraw.ddraw = NULL;

		debug_log ( "Released DirectDraw - references left: %d", refs );
	}

	return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL ddraw_lock_surface ( LPDIRECTDRAWSURFACEX surface, LPVOID *ptr, int *pitch )
{
	
	DDSURFACEDESC2
		ddsd;
	
	HRESULT
		ret;

	ASSERT ( surface );
	ASSERT ( ptr );
	ASSERT ( pitch );

	*ptr = NULL;
	
	*pitch = 0;
	
	ddsd.dwSize = sizeof ( DDSURFACEDESC2 );
	
	if ( ( ddraw.ddraw ) && ( surface ) )
	{
		
		ret = IDirectDrawSurface7_Lock ( surface, NULL, &ddsd, DDLOCK_NOSYSLOCK | DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL );
		
		if ( ret != DD_OK )
		{

			if ( ret == DDERR_SURFACELOST )
			{

				debug_log ( "Attempting restore" );

				ret = IDirectDrawSurface7_Restore ( surface );

				if ( FAILED ( ret ) )
				{

					debug_log ( "Unable to restore surface: %s", get_ddraw_error_message ( ret ) );
				}

				ret = IDirectDrawSurface7_Lock ( surface, NULL, &ddsd, DDLOCK_NOSYSLOCK | DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL );
			}

			if ( ret != DD_OK )
			{
	
				debug_log ( "failed to lock surface: %s", get_ddraw_error_message ( ret ) );
	
				return ( FALSE );
			}
		}

		if ( !ddsd.lpSurface )
		{

			debug_fatal ( "Locked surface, but got a NULL pointer..... odd...." );
		}

		*ptr = ddsd.lpSurface;
		
		*pitch = ddsd.lPitch;

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

BOOL ddraw_unlock_surface ( LPDIRECTDRAWSURFACE7 surface, unsigned char * memory )
{
	
	HRESULT
		ddrval;

	ASSERT ( surface );
	ASSERT ( memory );

	if ( ( ddraw.ddraw ) && ( surface ) )
	{
		
		ddrval = IDirectDrawSurface7_Unlock ( surface, NULL );
		
		if ( ddrval != DD_OK )
		{

			debug_log ( "Unable to unlock surface: %s", get_ddraw_error_message ( ddrval ) );

			return ( FALSE );
		}
		else
		{
			
			return ( TRUE );
		}
	}
	else
	{
		
		return ( TRUE );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL ddraw_flip_surface_export ( void )
{
	HRESULT	ddrval;
	DDBLTFX
		ddbltfx;
	RECT dst, src;
	int size;
	switch(get_global_gunship_type())
	{
		case GUNSHIP_TYPE_HAVOC:
		case GUNSHIP_TYPE_KA50:
		case GUNSHIP_TYPE_HIND:
			dst.left=command_line_export_mfd_single_pos[0];
			dst.top=command_line_export_mfd_single_pos[1];
			dst.right=command_line_export_mfd_single_pos[2];
			dst.bottom=command_line_export_mfd_single_pos[3];
		case GUNSHIP_TYPE_COMANCHE:
		case GUNSHIP_TYPE_HOKUM:
		case GUNSHIP_TYPE_APACHE:
		case GUNSHIP_TYPE_BLACKHAWK:
		default:
			dst.left=command_line_export_mfd_left_pos[0];
			dst.top=command_line_export_mfd_left_pos[1];
			dst.right=command_line_export_mfd_left_pos[2];
			dst.bottom=command_line_export_mfd_left_pos[3];
	}
	switch(get_global_gunship_type())
	{
		case GUNSHIP_TYPE_HAVOC:
		case GUNSHIP_TYPE_COMANCHE:
		case GUNSHIP_TYPE_HOKUM:
		case GUNSHIP_TYPE_APACHE:
			size=256;
			break;
		case GUNSHIP_TYPE_BLACKHAWK:
		case GUNSHIP_TYPE_HIND:
		case GUNSHIP_TYPE_KA50:
		case GUNSHIP_TYPE_AH64A:
		default:
			size=128;
			break;
	}
	src.left=0;
	src.top=0;
	src.right=size;
	src.bottom=size;

	ddbltfx.dwSize = sizeof ( ddbltfx );

	ddbltfx.dwROP = SRCCOPY;
       //	ddrval	= IDirectDrawSurface7_Flip ( ddraw2.lpFrontBuffer, NULL, DDFLIP_WAIT );
	ddrval = IDirectDrawSurface7_Blt ( ddraw_export.lpFrontBuffer, &dst, ddraw_export.lpBackBuffer, &src, 0, NULL);

	if(get_global_gunship_type()==GUNSHIP_TYPE_HAVOC)
		return TRUE;

	dst.left=command_line_export_mfd_right_pos[0];
	dst.top=command_line_export_mfd_right_pos[1];
	dst.right=command_line_export_mfd_right_pos[2];
	dst.bottom=command_line_export_mfd_right_pos[3];
	src.left=272;	
	src.top=0;
	src.right=272+size;
	src.bottom=size;
	ddrval = IDirectDrawSurface7_Blt ( ddraw_export.lpFrontBuffer, &dst, ddraw_export.lpBackBuffer, &src, 0, NULL);
	if ( ddrval != DD_OK )
	{
		debug_log ( "Unable to perform surface flip (export): %s", get_ddraw_error_message ( ddrval ) );
		return ( FALSE );
	}
	return TRUE;
}

BOOL ddraw_flip_surface ( void )
{
	
	HRESULT
		ddrval;

	DDBLTFX
		ddbltfx;

	RECT
		my_rc;

	if ( !ddraw.ddraw )
	{

		return ( FALSE );
	}
	if(ddraw_export.ddraw)
		ddraw_flip_surface_export();

	total_number_of_d3d_triangles = running_total_number_of_d3d_triangles;

	total_number_of_d3d_flushes = running_total_number_of_d3d_flushes;
	
	running_total_number_of_d3d_triangles = 0;

	running_total_number_of_d3d_flushes = 0;
	
	if ( ( ddraw.ddraw ) && ( ddraw.use_double_buffer ) && ( ddraw.lpFrontBuffer ) && ( ddraw.lpBackBuffer ) )
	{

		if ( !ddraw.application_windowed )
		{

			if ( ddraw.use_system_memory )
			{

				{

					DDSURFACEDESC2
						src_ddsd,
						dest_ddsd;
					

					//
					// Lock the surface memory
					//

					src_ddsd.dwSize = sizeof ( src_ddsd );

					dest_ddsd.dwSize = sizeof ( dest_ddsd );
	
					IDirectDrawSurface7_Lock ( ddraw.lpBackBuffer, NULL, &dest_ddsd, DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL );
		
					IDirectDrawSurface7_Lock ( ddraw.lpRenderBuffer, NULL, &src_ddsd, DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL );

					{

						unsigned char
							*source_screen,
							*dest_screen;

						int
							width,
							height;

						source_screen = src_ddsd.lpSurface;

						dest_screen = dest_ddsd.lpSurface;
				
						for ( height=0; height < application_video_height; height++ )
						{

							double
								*source,
								*dest;

							source = ( double * ) source_screen;

							dest = ( double * ) dest_screen;
				
							for ( width = application_video_width; width > 0; width -= 16 )
							{

								dest[0] = source[0];
								dest[1] = source[1];
								dest[2] = source[2];
								dest[3] = source[3];
								dest += 4;
								source += 4;
							}
				
							dest_screen += dest_ddsd.lPitch;
				
							source_screen += src_ddsd.lPitch;
						}
					}

					IDirectDrawSurface7_Unlock ( ddraw.lpBackBuffer, NULL );
					
					IDirectDrawSurface7_Unlock ( ddraw.lpRenderBuffer, NULL );
				}

//				ddbltfx.dwSize = sizeof ( ddbltfx );
	
//				ddbltfx.dwROP = SRCCOPY;
	
//				ddrval = IDirectDrawSurface7_Blt ( ddraw.lpBackBuffer, NULL, ddraw.lpRenderBuffer, NULL, 0, &ddbltfx );
			}
			else
			{
	
				ddrval = IDirectDrawSurface7_Flip ( ddraw.lpFrontBuffer, NULL, DDFLIP_WAIT );
				
				if ( ddrval != DD_OK )
				{
	
//					debug_log ( "Unable to perform surface flip: %s", get_ddraw_error_message ( ddrval ) );
	
					return ( FALSE );
				}
			}

			return ( TRUE );
		}
		else
		{

			ddbltfx.dwSize = sizeof ( ddbltfx );

			ddbltfx.dwROP = SRCCOPY;

			GetClientRect(application_window, &my_rc);
			ClientToScreen(application_window, (LPPOINT)&my_rc);
			ClientToScreen(application_window, (LPPOINT)&my_rc+1);


			my_rc.bottom = my_rc.top + application_video_height;
			my_rc.right = my_rc.left + application_video_width;

			ddrval = IDirectDrawSurface7_Blt ( ddraw.lpFrontBuffer, &my_rc, ddraw.lpBackBuffer, NULL, 0, NULL );

			if ( ddrval != DD_OK )
			{

				debug_log ( "Unable to perform a windowed flip operation: %s", get_ddraw_error_message ( ddrval ) );

				return ( FALSE );
			}
/*
			ddrval = -1;

			while ( ddrval != DD_OK )
			{
	
				ddrval = IDirectDrawSurface7_GetBltStatus ( ddraw.lpFrontBufferX, DDGBS_ISBLTDONE );
			}
*/
			return ( TRUE );
		}
	}
	else
	{
		
		return ( TRUE );
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL ddraw_set_display_resolution ( int width, int height, int depth, display_types display_type )
{

	DDSURFACEDESC2
		ddsd;
	
	DDSCAPS2
		caps;
	
	HRESULT
		ddrval;
	
	RECT
		rc,
		rcWork;
	
	DWORD
		dwStyle;

	BOOL
		windowed;
	
	ASSERT ( get_graphics_system_initialised () );

	switch ( display_type )
	{

		case DISPLAY_WINDOW:
		{

			windowed = TRUE;

			break;
		}

		case DISPLAY_FULLSCREEN:
		{

			windowed = FALSE;

			break;
		}

		default:
		{

			debug_fatal ( "Unknown window status passed to set_display_resolution" );

			break;
		}
	}
	
	application_video_height = height;

	application_video_width = width;

	application_video_colourdepth = depth;
	
	ddraw.application_windowed = windowed;

	set_viewport ( 0, 0, ( ( ( float ) width ) - 0.001 ), ( ( ( float ) height ) - 0.001 ) );
	
	if ( !windowed )
	{
		
		//
		// Set the cooperative mode settings.
		//
	
		//mue 070223 cooperative level must be set by the same thread that created the application window
		ddraw_cooperative_level coop_level=COOPERATIVE_LEVEL_EXCLUSIVE; 
		system_thread_function (ddraw_internal_set_cooperative_level,&coop_level  );

		//
		// Setup the window style for a fullscreen application
		//
		
		dwStyle = GetWindowStyle ( application_window );
		
		dwStyle &= ~( WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX );
		
		dwStyle |= WS_POPUP;
		
		SetWindowLong ( application_window, GWL_STYLE, dwStyle );
		
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
		
		if( ddrval != DD_OK )
		{
			
			debug_log ( "Unable to set display resolution: %s", get_ddraw_error_message ( ddrval ) );
			
			return ( FALSE );
		}

		//
		// Set the buffer pointers
		//

		ddraw.lpFrontBuffer = NULL;
		ddraw.lpBackBuffer = NULL;
		ddraw.lpRenderBuffer = NULL;
		
		//
		// Create the primary surface
		//

		memset ( &ddsd, 0, sizeof ( ddsd ) );

		ddsd.dwSize = sizeof ( ddsd );
		
		ddsd.dwFlags = DDSD_CAPS;

		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_3DDEVICE;
//		ddsd.ddsCaps.dwCaps2 = DDSCAPS2_HINTANTIALIASING;

		if ( ddraw.use_double_buffer )
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

		if ( ddraw.use_double_buffer )
		{
			
			//
			// Get the back screen from this surface.
			//

			memset ( &caps, 0, sizeof ( caps ) );

			caps.dwCaps = DDSCAPS_BACKBUFFER;
			
			ddrval = IDirectDrawSurface7_GetAttachedSurface ( ddraw.lpFrontBuffer, &caps, &ddraw.lpBackBuffer );
			
			if ( ddrval != DD_OK )
			{
				
				debug_fatal ( "Unable to get backbuffer: %s", get_ddraw_error_message ( ddrval ) );
				
				return ( FALSE );
			}
		}

		if ( ddraw.use_system_memory )
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
				
				debug_fatal ( "Unable to create system memory surface: %s", get_ddraw_error_message ( ddrval ) );
				
				return ( FALSE );
			}
		}
		else
		{

			//
			// Set the render buffer
			//

			if ( ddraw.use_double_buffer )
			{

				ddraw.lpRenderBuffer = ddraw.lpBackBuffer;
			}
			else
			{
	
				ddraw.lpRenderBuffer = ddraw.lpFrontBuffer;
			}
		}
		
		if ( ddraw.use_z_buffer )
		{

			//
			// Create the zbuffer and attach it to the render buffer.
			//

			memset ( &ddsd, 0, sizeof ( ddsd ) );
	
			ddsd.dwSize = sizeof ( ddsd );
	
			ddrval = IDirectDrawSurface7_GetSurfaceDesc ( ddraw.lpFrontBuffer, &ddsd );
			
			ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;

			ddsd.ddsCaps.dwCaps = DDSCAPS_ZBUFFER;

			if ( d3d_use_rgb_device )
			{

				ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
			}
			else
			{

				ddsd.ddsCaps.dwCaps |= DDSCAPS_VIDEOMEMORY;
			}
			
			ddsd.dwHeight = height;
			
			ddsd.dwWidth = width;

			//
			// Set zbuffer pixel format
			//

			get_ddraw_zbuffer_pixel_format ( &ddsd.ddpfPixelFormat );

//			ddsd.ddpfPixelFormat.dwSize = sizeof ( ddsd.ddpfPixelFormat );
//			ddsd.ddpfPixelFormat.dwFlags = DDPF_ZBUFFER;
//			ddsd.ddpfPixelFormat.dwZBufferBitDepth = depth;

			ddrval = IDirectDraw7_CreateSurface ( ddraw.ddraw, &ddsd, &ddraw.lpZBuffer, NULL );
			
			if ( ddrval != DD_OK )
			{
				
				debug_fatal ( "Unable to create Zbuffer surface: %s", get_ddraw_error_message ( ddrval ) );
				
				return ( FALSE );
			}

			ddrval = IDirectDrawSurface7_AddAttachedSurface ( ddraw.lpRenderBuffer, ddraw.lpZBuffer );

			if ( ddrval != DD_OK )
			{

				debug_fatal ( "Unable to attach Zbuffer surface: %s", get_ddraw_error_message ( ddrval ) );
				
				return ( FALSE );
			}

			zbuffer_target_surface = ddraw.lpRenderBuffer;
		}

		//
		// Create the screen associated with the render buffer ( video_screen )
		//

		create_video_screen ( width, height, ddraw.lpRenderBuffer );

//		return ( TRUE );
	}
	else
	{
		
		//
		// Set the cooperative mode settings.
		//

		ddraw_set_cooperative_level ( COOPERATIVE_LEVEL_NORMAL );

		//
		// Convert from a WS_POPUP window to a proper window.
		//
		
		dwStyle = GetWindowStyle ( application_window );
		
		dwStyle &= ~WS_POPUP;
		
		dwStyle |= WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX;
		
		SetWindowLong ( application_window, GWL_STYLE, dwStyle );
		
		//
		// Position the window properly
		//
		
		rc.top = 0;
		rc.left = 0;
		rc.bottom = height;
		rc.right = width;
		
		AdjustWindowRectEx ( &rc,
									GetWindowStyle ( application_window),
									GetMenu ( application_window) != NULL,
									GetWindowExStyle ( application_window ) );

		SetWindowPos ( application_window,
								NULL, 0, 0, rc.right-rc.left, rc.bottom-rc.top,
								SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
		
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
		
		//
		// Create the primary surface
		//
		
		memset ( &ddsd, 0, sizeof ( ddsd ) );

		ddsd.dwSize = sizeof (ddsd);
		
		ddsd.dwFlags = DDSD_CAPS;
		
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_3DDEVICE;
		
		ddrval = IDirectDraw7_CreateSurface ( ddraw.ddraw, &ddsd, &ddraw.lpFrontBuffer, NULL);
		
		if ( ddrval != DD_OK )
		{
			
			debug_log ( "Unable to create primary surface: %s", get_ddraw_error_message ( ddrval ) );
			
			return ( FALSE );
		}

		//
		// Create the secondary surface
		//

		memset ( &ddsd, 0, sizeof ( ddsd ) );

		ddsd.dwSize = sizeof( ddsd );

		ddrval = IDirectDrawSurface7_GetSurfaceDesc ( ddraw.lpFrontBuffer, &ddsd );
		
		ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;

		if ( ddraw.use_system_memory )
		{

			ddsd.ddsCaps.dwCaps = DDSCAPS_3DDEVICE | DDSCAPS_SYSTEMMEMORY;
		}
		else
		{

			ddsd.ddsCaps.dwCaps = DDSCAPS_3DDEVICE;
		}
		
		ddsd.dwHeight = height;
		
		ddsd.dwWidth = width;
		
		ddrval = IDirectDraw7_CreateSurface ( ddraw.ddraw , &ddsd, &ddraw.lpBackBuffer, NULL );
		
		if ( ddrval != DD_OK )
		{
			
			debug_fatal ( "Unable to create secondary surface: %s", get_ddraw_error_message ( ddrval ) );
			
			return ( FALSE );
		}

		//
		// Clear the surface
		//

		{
	
			DDBLTFX
				fx;
		
			RECT
				rect;
		
			//
			// Perform the blit using the blitter
			//
	
			fx.dwSize = sizeof ( fx );
			fx.dwFillColor = 0;
		
			rect.left = 0;
			rect.right = width;
		
			rect.top = 0;
			rect.bottom = height;
	
			ddrval = IDirectDrawSurface7_Blt ( ddraw.lpBackBuffer, &rect, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &fx );
		}

		//
		// Set render surface
		//

		ddraw.lpRenderBuffer = ddraw.lpBackBuffer;
		
		//
		// If needed, create the zbuffer and attach it to the render buffer.
		//

		if ( ddraw.use_z_buffer )
		{

			memset ( &ddsd, 0, sizeof ( ddsd ) );
	
			ddsd.dwSize = sizeof( ddsd );
	
			ddrval = IDirectDrawSurface7_GetSurfaceDesc ( ddraw.lpFrontBuffer, &ddsd );
			
			ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;

			if ( d3d_use_rgb_device )
			{
	
				ddsd.ddsCaps.dwCaps = DDSCAPS_ZBUFFER | DDSCAPS_SYSTEMMEMORY;
			}
			else
			{

				ddsd.ddsCaps.dwCaps = DDSCAPS_ZBUFFER | DDSCAPS_VIDEOMEMORY;
			}
			
			ddsd.dwHeight = height;
			
			ddsd.dwWidth = width;
			
			get_ddraw_zbuffer_pixel_format ( &ddsd.ddpfPixelFormat );

//			ddsd.ddpfPixelFormat.dwSize = sizeof ( ddsd.ddpfPixelFormat );
//			ddsd.ddpfPixelFormat.dwFlags = DDPF_ZBUFFER;
//			ddsd.ddpfPixelFormat.dwZBufferBitDepth = depth;

			ddrval = IDirectDraw7_CreateSurface ( ddraw.ddraw, &ddsd, &ddraw.lpZBuffer, NULL );
			
			if ( ddrval != DD_OK )
			{
				
				debug_fatal ( "Unable to create Zbuffer surface: %s", get_ddraw_error_message ( ddrval ) );
				
				return ( FALSE );
			}

			ddrval = IDirectDrawSurface7_AddAttachedSurface ( ddraw.lpRenderBuffer, ddraw.lpZBuffer );

			if ( ddrval != DD_OK )
			{

				debug_fatal ( "Unable to attach Zbuffer surface: %s", get_ddraw_error_message ( ddrval ) );
				
				return ( FALSE );
			}

			zbuffer_target_surface = ddraw.lpRenderBuffer;
		}

		//
		// now create a DirectDrawClipper object.
		//
		
		ddrval = IDirectDraw7_CreateClipper ( ddraw.ddraw, 0, &ddraw.lpClipper, NULL);
		
		if ( ddrval != DD_OK )
		{
			
			debug_log ( "Unable to create clipper: %s", get_ddraw_error_message ( ddrval ) );
			
			return ( FALSE );
		}

		ddrval = IDirectDrawClipper_SetHWnd ( ddraw.lpClipper, 0, application_window );
		
		if ( ddrval != DD_OK )
		{
			
			debug_log ( "Unable to set clipper to a window: %s", get_ddraw_error_message ( ddrval ) );
			
			return ( FALSE );
		}
		
		ddrval = IDirectDrawSurface7_SetClipper ( ddraw.lpFrontBuffer, ddraw.lpClipper);
		
		if ( ddrval != DD_OK )
		{
			
			debug_log ( "Unable to set clipper to the primary surface: %s", get_ddraw_error_message ( ddrval ) );
			
			return ( FALSE );
		}

		//
		// Create the screen associated with the render buffer ( video_screen )
		//

		create_video_screen ( width, height, ddraw.lpRenderBuffer );

//		return ( TRUE );
	}

	//mue 070223 init export_display
	if(ddraw_export.ddraw)
	{
		memset ( &ddsd, 0, sizeof ( ddsd ) );

		ddsd.dwSize = sizeof ( ddsd );
		
		ddsd.dwFlags = DDSD_CAPS;

		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
//		ddsd.ddsCaps.dwCaps2 = DDSCAPS2_HINTANTIALIASING;

		if ( ddraw_export.use_double_buffer )
		{
			
			ddsd.dwFlags |= DDSD_BACKBUFFERCOUNT;
			
			ddsd.dwBackBufferCount = 1;
			
			ddsd.ddsCaps.dwCaps |= DDSCAPS_FLIP | DDSCAPS_COMPLEX;
		}
		
		ddrval = IDirectDraw7_CreateSurface ( ddraw_export.ddraw, &ddsd, &ddraw_export.lpFrontBuffer, NULL);
		
		if ( ddrval != DD_OK )
		{
			
			debug_log ( "Unable to create primary surface: %s", get_ddraw_error_message ( ddrval ) );
			
			return ( FALSE );
		}

		if ( ddraw.use_double_buffer )
		{
			
			//
			// Get the back screen from this surface.
			//

			memset ( &caps, 0, sizeof ( caps ) );

			caps.dwCaps = DDSCAPS_BACKBUFFER;
			
			ddrval = IDirectDrawSurface7_GetAttachedSurface ( ddraw_export.lpFrontBuffer, &caps, &ddraw_export.lpBackBuffer );
			
			if ( ddrval != DD_OK )
			{
				
				debug_fatal ( "Unable to get backbuffer: %s", get_ddraw_error_message ( ddrval ) );
				
				return ( FALSE );
			}
			ddraw_export.lpRenderBuffer=ddraw_export.lpBackBuffer;
		}
	}
	return ( TRUE );
	// mue 070223 end init export_display
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL ddraw_change_display_resolution ( int width, int height, int depth )
{

	DDSURFACEDESC2
		ddsd;
	
	DDSCAPS2
		caps;
	
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
	application_video_colourdepth = depth;

	set_basic_viewport ( 0, 0, ( ( ( float ) application_video_width ) - 0.001 ), ( ( ( float ) application_video_height ) - 0.001 ) );
	
	windowed = ddraw.application_windowed;

	if ( !windowed )
	{

		//
	 	// Prevent d3d from being valid
		//

		d3d_valid = FALSE;

		//
		// Remove textures from pipeline
		//

		initialise_d3d_state ();

		//
		// Destroy the vertex buffers
		//

		destroy_d3d_vertex_buffers ();
	
		//
		// Free all hardware textures up
		//

		free_all_hardware_textures ();
	
		//
		// Release the 3d devices
		//
	
		d3d_release_objects ();
	
		//
		// Remove the Z buffer from the render surface
		//

		if ( ( ddraw.lpZBuffer ) && ( ddraw.lpRenderBuffer ) )
		{

			ret = IDirectDrawSurface7_DeleteAttachedSurface ( ddraw.lpRenderBuffer, 0, ddraw.lpZBuffer );

			if ( ret != DD_OK )
			{

				debug_log ( "Unable to delete the zbuffer from the render buffer: %s", get_ddraw_error_message ( ret ) );
			}

			ret = IDirectDrawSurface7_Release ( ddraw.lpZBuffer );

			if ( FAILED ( ret ) )
			{

				debug_log ( "Unable to delete the release the zbuffer: %s", get_ddraw_error_message ( ret ) );
			}

			ddraw.lpZBuffer = NULL;
		}

		//
		// Set the video mode
		//

		ret = IDirectDraw7_SetDisplayMode ( ddraw.ddraw, width, height, depth, 0, 0 );
		
		if( ret != DD_OK )
		{
			
			debug_log ( "Unable to set display resolution: %s", get_ddraw_error_message ( ret ) );
			
			return ( FALSE );
		}

		//
		// Free up the previous video mode's pointers
		//

		if ( ddraw.lpFrontBuffer )
		{

			ret = IDirectDrawSurface7_Release ( ddraw.lpFrontBuffer );

			if ( FAILED ( ret ) )
			{

				debug_log ( "Unable to release old front buffer: %s", get_ddraw_error_message ( ret ) );
			}
		}

		if ( ddraw.use_system_memory )
		{

			if ( ddraw.lpRenderBuffer )
			{

				ret = IDirectDrawSurface7_Release ( ddraw.lpRenderBuffer );

				if ( FAILED ( ret ) )
				{
	
					debug_log ( "Unable to release old front buffer: %s", get_ddraw_error_message ( ret ) );
				}
			}
		}

		//
		// Set the buffer pointers
		//

		ddraw.lpFrontBuffer = NULL;
		ddraw.lpBackBuffer = NULL;
		ddraw.lpRenderBuffer = NULL;
		
		//
		// Create the primary surface
		//

		memset ( &ddsd, 0, sizeof ( ddsd ) );

		ddsd.dwSize = sizeof ( ddsd );
		
		ddsd.dwFlags = DDSD_CAPS;

		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_3DDEVICE;

		if ( ddraw.use_double_buffer )
		{
			
			ddsd.dwFlags |= DDSD_BACKBUFFERCOUNT;
			
			ddsd.dwBackBufferCount = 1;
			
			ddsd.ddsCaps.dwCaps |= DDSCAPS_FLIP | DDSCAPS_COMPLEX;
		}
		
		ret = IDirectDraw7_CreateSurface ( ddraw.ddraw, &ddsd, &ddraw.lpFrontBuffer, NULL);
		
		if ( ret != DD_OK )
		{
			
			debug_log ( "Unable to create primary surface: %s", get_ddraw_error_message ( ret ) );
			
			return ( FALSE );
		}

		if ( ddraw.use_double_buffer )
		{
			
			//
			// Get the back screen from this surface.
			//

			memset ( &caps, 0, sizeof ( caps ) );

			caps.dwCaps = DDSCAPS_BACKBUFFER;
			
			ret = IDirectDrawSurface7_GetAttachedSurface ( ddraw.lpFrontBuffer, &caps, &ddraw.lpBackBuffer );
			
			if ( ret != DD_OK )
			{
				
				debug_fatal ( "Unable to get backbuffer: %s", get_ddraw_error_message ( ret ) );
				
				return ( FALSE );
			}
		}

		if ( ddraw.use_system_memory )
		{

			//
			// Create the system memory surface
			//
	
			memset ( &ddsd, 0, sizeof ( ddsd ) );
	
			ddsd.dwSize = sizeof( ddsd );
	
			ret = IDirectDrawSurface7_GetSurfaceDesc ( ddraw.lpFrontBuffer, &ddsd );

			if ( FAILED ( ret ) )
			{

				debug_log ( "Unable to GetSurfaceDesc: %s", get_ddraw_error_message ( ret ) );
			}

			ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
	
			ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE | DDSCAPS_SYSTEMMEMORY;
			
			ddsd.dwHeight = height;
			
			ddsd.dwWidth = width;
			
			ret = IDirectDraw7_CreateSurface ( ddraw.ddraw , &ddsd, &ddraw.lpRenderBuffer, NULL );
			
			if ( ret != DD_OK )
			{
				
				debug_fatal ( "Unable to create system memory surface: %s", get_ddraw_error_message ( ret ) );
				
				return ( FALSE );
			}
		}
		else
		{

			//
			// Set the render buffer
			//

			if ( ddraw.use_double_buffer )
			{

				ddraw.lpRenderBuffer = ddraw.lpBackBuffer;
			}
			else
			{
	
				ddraw.lpRenderBuffer = ddraw.lpFrontBuffer;
			}
		}
		
		if ( ddraw.use_z_buffer )
		{

			//
			// Create the zbuffer and attach it to the render buffer.
			//

			memset ( &ddsd, 0, sizeof ( ddsd ) );
	
			ddsd.dwSize = sizeof ( ddsd );
	
			ret = IDirectDrawSurface7_GetSurfaceDesc ( ddraw.lpFrontBuffer, &ddsd );

			if ( FAILED ( ret ) )
			{

				debug_log ( "Unable to GetSurfaceDesc: %s", get_ddraw_error_message ( ret ) );
			}
			
			ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
	
			ddsd.ddsCaps.dwCaps = DDSCAPS_ZBUFFER | DDSCAPS_VIDEOMEMORY;
			
			ddsd.dwHeight = height;
			
			ddsd.dwWidth = width;

			//
			// Set zbuffer pixel format
			//

			get_ddraw_zbuffer_pixel_format ( &ddsd.ddpfPixelFormat );

//			ddsd.ddpfPixelFormat.dwSize = sizeof ( ddsd.ddpfPixelFormat );
//			ddsd.ddpfPixelFormat.dwFlags = DDPF_ZBUFFER;
//			ddsd.ddpfPixelFormat.dwZBufferBitDepth = depth;

			ret = IDirectDraw7_CreateSurface ( ddraw.ddraw, &ddsd, &ddraw.lpZBuffer, NULL );
			
			if ( ret != DD_OK )
			{
				
				debug_fatal ( "Unable to create Zbuffer surface: %s", get_ddraw_error_message ( ret ) );
				
				return ( FALSE );
			}

			ret = IDirectDrawSurface7_AddAttachedSurface ( ddraw.lpRenderBuffer, ddraw.lpZBuffer );

			if ( ret != DD_OK )
			{

				debug_fatal ( "Unable to attach Zbuffer surface: %s", get_ddraw_error_message ( ret ) );
				
				return ( FALSE );
			}

			zbuffer_target_surface = ddraw.lpRenderBuffer;
		}

		//
		// Recreate d3d's managed surfaces
		//

		ret = IDirectDraw7_RestoreAllSurfaces ( ddraw.ddraw );

		if ( FAILED ( ret ) )
		{

			debug_log ( "Unable to RestoreAllSurface: %s", get_ddraw_error_message ( ret ) );
		}

		//
		// Create the screen associated with the render buffer ( video_screen )
		//

		create_video_screen ( width, height, ddraw.lpRenderBuffer );

		//
		// As we're in fullscreen mode, we have just wiped out all the d3d devices & hardware textures, recreate them
		//

		d3d.recreate_d3d = TRUE;

		return ( TRUE );
	}
	else
	{
		
		//
		// Position the window properly
		//
		
		rc.top = 0;
		rc.left = 0;
		rc.bottom = height;
		rc.right = width;
		
		AdjustWindowRectEx ( &rc, GetWindowStyle ( application_window), GetMenu ( application_window) != NULL, GetWindowExStyle ( application_window ) );
		SetWindowPos ( application_window, NULL, 0, 0, rc.right-rc.left, rc.bottom-rc.top, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
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
		
		//
		// No need to create the primary surface - the old one will suffice
		//

		//
		// Release the old secondary surface, clipper, zbuffer
		//

		if ( ddraw.lpClipper )
		{

			//
			// Detach it from the primary screen
			//

			IDirectDrawSurface7_SetClipper ( ddraw.lpFrontBuffer, NULL );

			IDirectDrawClipper_Release ( ddraw.lpClipper );

			ddraw.lpClipper = NULL;
		}

		//
		// Remove the ZBuffer
		//

		if ( ddraw.lpZBuffer )
		{

			HRESULT
				ret;

			ret = IDirectDrawSurface7_DeleteAttachedSurface ( ddraw.lpRenderBuffer, 0, ddraw.lpZBuffer );

			if ( ret != DD_OK )
			{

				debug_log ( "Unable to delete the zbuffer from the render buffer: %s", get_ddraw_error_message ( ret ) );
			}

			IDirectDrawSurface7_Release ( ddraw.lpZBuffer );

			ddraw.lpZBuffer = NULL;
		}

		//
		// Remove the back buffer/renderbuffer
		//

		if ( ddraw.lpBackBuffer )
		{

			IDirectDrawSurface7_Release ( ddraw.lpBackBuffer );

			ddraw.lpBackBuffer = NULL;

			ddraw.lpRenderBuffer = NULL;
		}
		
		//
		// Create the secondary surface
		//

		memset ( &ddsd, 0, sizeof ( ddsd ) );

		ddsd.dwSize = sizeof( ddsd );

		ret = IDirectDrawSurface7_GetSurfaceDesc ( ddraw.lpFrontBuffer, &ddsd );

		if ( FAILED ( ret ) )
		{

			debug_log ( "Unable to GetSurfaceDesc: %s", get_ddraw_error_message ( ret ) );
		}
		
		ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;

		if ( ddraw.use_system_memory )
		{

			ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE | DDSCAPS_SYSTEMMEMORY;
		}
		else
		{

			ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE;
		}
		
		ddsd.dwHeight = height;
		
		ddsd.dwWidth = width;
		
		ret = IDirectDraw7_CreateSurface ( ddraw.ddraw , &ddsd, &ddraw.lpBackBuffer, NULL );
		
		if ( ret != DD_OK )
		{
			
			debug_log ( "Unable to create secondary surface: %s", get_ddraw_error_message ( ret ) );
			
			return ( FALSE );
		}

		//
		// Set render surface
		//

		ddraw.lpRenderBuffer = ddraw.lpBackBuffer;
		
		//
		// If needed, create the zbuffer and attach it to the render buffer.
		//

		if ( ddraw.use_z_buffer )
		{

			memset ( &ddsd, 0, sizeof ( ddsd ) );
	
			ddsd.dwSize = sizeof( ddsd );
	
			ret = IDirectDrawSurface7_GetSurfaceDesc ( ddraw.lpFrontBuffer, &ddsd );
	
			if ( FAILED ( ret ) )
			{
	
				debug_log ( "Unable to GetSurfaceDesc: %s", get_ddraw_error_message ( ret ) );
			}
			
			ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
	
			ddsd.ddsCaps.dwCaps = DDSCAPS_ZBUFFER | DDSCAPS_VIDEOMEMORY;
			
			ddsd.dwHeight = height;
			
			ddsd.dwWidth = width;
			
			get_ddraw_zbuffer_pixel_format ( &ddsd.ddpfPixelFormat );

//			ddsd.ddpfPixelFormat.dwSize = sizeof ( ddsd.ddpfPixelFormat );
//			ddsd.ddpfPixelFormat.dwFlags = DDPF_ZBUFFER;
//			ddsd.ddpfPixelFormat.dwZBufferBitDepth = depth;

			ret = IDirectDraw7_CreateSurface ( ddraw.ddraw, &ddsd, &ddraw.lpZBuffer, NULL );
			
			if ( ret != DD_OK )
			{
				
				debug_fatal ( "Unable to create Zbuffer surface: %s", get_ddraw_error_message ( ret ) );
				
				return ( FALSE );
			}

			ret = IDirectDrawSurface7_AddAttachedSurface ( ddraw.lpRenderBuffer, ddraw.lpZBuffer );

			if ( ret != DD_OK )
			{

				debug_fatal ( "Unable to attach Zbuffer surface: %s", get_ddraw_error_message ( ret ) );
				
				return ( FALSE );
			}

			zbuffer_target_surface = ddraw.lpRenderBuffer;
		}

		//
		// now create a DirectDrawClipper object.
		//
		
		ret = IDirectDraw7_CreateClipper ( ddraw.ddraw, 0, &ddraw.lpClipper, NULL);
		
		if ( ret != DD_OK )
		{
			
			debug_log ( "Unable to create clipper: %s", get_ddraw_error_message ( ret ) );
			
			return ( FALSE );
		}

		ret = IDirectDrawClipper_SetHWnd ( ddraw.lpClipper, 0, application_window );
		
		if ( ret != DD_OK )
		{
			
			debug_log ( "Unable to set clipper to a window: %s", get_ddraw_error_message ( ret ) );
			
			return ( FALSE );
		}
		
		ret = IDirectDrawSurface7_SetClipper ( ddraw.lpFrontBuffer, ddraw.lpClipper);
		
		if ( ret != DD_OK )
		{
			
			debug_log ( "Unable to set clipper to the primary surface: %s", get_ddraw_error_message ( ret ) );
			
			return ( FALSE );
		}

		//
		// Create the screen associated with the render buffer ( video_screen )
		//

		create_video_screen ( width, height, ddraw.lpRenderBuffer );

		//
		// Now we need to alter the render target of the 3d system
		//

		d3d_render_target_recreated ();

		return ( TRUE );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_ddraw_zbuffer_pixel_format ( DDPIXELFORMAT *format )
{

	HRESULT
		ret;

	ASSERT ( d3d.d3d );

	ret = IDirect3D7_EnumZBufferFormats ( d3d.d3d, &IID_IDirect3DHALDevice, ddraw_enumerate_zbuffer_formats, ( void * ) format );

	if ( FAILED ( ret ) )
	{

		debug_fatal ( "Unable to enumerate zbuffer formats: %s", get_ddraw_error_message ( ret ) );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static HRESULT WINAPI ddraw_enumerate_zbuffer_formats ( DDPIXELFORMAT *format, void *choice )
{

	if ( format->dwFlags == DDPF_ZBUFFER )
	{

		memcpy ( choice, format, sizeof ( DDPIXELFORMAT ) );

		return ( D3DENUMRET_CANCEL );
	}

	return ( D3DENUMRET_OK );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ddraw_validate_display_devices ( void )
{

	if ( ddraw.ddraw )
	{
	
		HRESULT
			ret;
	
		ret = IDirectDraw7_TestCooperativeLevel ( ddraw.ddraw );

		if ( FAILED ( ret ) )
		{

			switch ( ret )
			{

				case DDERR_INVALIDOBJECT:
				{

					debug_log ( "Invalid object" );

					ddraw.ddraw_valid = FALSE;

					break;
				}

				case DDERR_EXCLUSIVEMODEALREADYSET:
				{

					debug_log ( "Exclusive mode already set" );

					ddraw.ddraw_valid = FALSE;

					break;
				}

				case DDERR_NOEXCLUSIVEMODE:
				{

					debug_log ( "No Exclusive mode" );

					ddraw.ddraw_valid = FALSE;

					break;
				}

				case DDERR_WRONGMODE:
				{

					debug_log ( "Wrong mode" );

					if ( ( !ddraw.ddraw_valid ) && ( !ddraw.application_windowed ) )
					{
		
						//
						// Need to change display mode, restore surfaces etc etc
						//
		
						ddraw_change_display_resolution ( application_video_width, application_video_height, application_video_colourdepth );
		
						ddraw.ddraw_valid = TRUE;
					}

					break;
				}
			}
		}
		else
		{

//			debug_log ( "PASSED" );
		}
	}
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

	ret = IDirectDraw7_SetDisplayMode ( ddraw.ddraw, ptr[0], ptr[1], ptr[2], 0, 0 );
	if(ddraw_export.ddraw)
		ret = IDirectDraw7_SetDisplayMode ( ddraw_export.ddraw, command_line_export_mfd_screen_width, command_line_export_mfd_screen_height, 16 , 0, 0 );

	return ( ret );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LPDIRECTDRAWSURFACEX ddraw_create_surface ( int width, int height, int video_memory )
{

	LPDIRECTDRAWSURFACEX
		lpSurface;

	DDSURFACEDESC2
		ddsd;

	HRESULT
		ddrval;

	//
	// Create the surface
	//

	memset ( &ddsd, 0, sizeof ( ddsd ) );

	ddsd.dwSize = sizeof ( ddsd );

	ddrval = IDirectDrawSurface7_GetSurfaceDesc ( ddraw.lpFrontBuffer, &ddsd );

	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;

	if ( !video_memory )
	{

		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
	}
	else
	{

		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	}
	
	ddsd.dwHeight = height;
	
	ddsd.dwWidth = width;
	
	ddrval = IDirectDraw7_CreateSurface ( ddraw.ddraw, &ddsd, &lpSurface, NULL );

	if ( ddrval != DD_OK )
	{

		debug_log ( "Unable to create a surface: %s", get_ddraw_error_message ( ddrval ) );

		return ( FALSE );
	}

	return ( lpSurface );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL ddraw_destroy_surface ( LPDIRECTDRAWSURFACEX surface )
{

	HRESULT
		ddrval;

	//
	// Create the surface
	//

	ddrval = IDirectDrawSurface7_Release ( surface );

	if ( FAILED ( ddrval ) )
	{

		debug_log ( "Unable to destroy a surface: %s", get_ddraw_error_message ( ddrval ) );

		return ( FALSE );
	}

	return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static HRESULT CALLBACK ddraw_enum_modes ( LPDDSURFACEDESC2 lpddsd, LPVOID Context )
{

	unsigned long
		m;

	int
		r,
		g,
		b;

	//
	// Stop if we've exceeded the number of display modes
	//

	if ( number_display_modes == 255 )
	{

		return ( DDENUMRET_CANCEL );
	}

	//
	// Set the surface description
	//

	memset ( &display_modes[number_display_modes], 0, sizeof ( display_format ) );
	
	memcpy ( &display_modes[number_display_modes].ddsd , lpddsd, sizeof ( DDSURFACEDESC ) );

	//
	// Assess the format
	//

	debug_log ( "Graphics adapter supports resolution %i x %i", lpddsd->dwWidth, lpddsd->dwHeight );


	if ( lpddsd->ddpfPixelFormat.dwFlags & DDPF_PALETTEINDEXED8 )
	{

		//
		// We no longer render to 8bit displays
		//
/*
		display_modes[number_display_modes].palette = TRUE;

		display_modes[number_display_modes].bpp_palette = 8;

		number_display_modes ++;
		*/
		debug_log ( "Resolution %i x %i skipped because it's 8 bit", lpddsd->dwWidth, lpddsd->dwHeight );

		return ( DDENUMRET_OK );
	}
	else if ( lpddsd->ddpfPixelFormat.dwFlags & DDPF_PALETTEINDEXED4)
	{

		//
		// We are NOT going to render to 4bit displays!
		//

		debug_log ( "Resolution %i x %i skipped because it's 4 bit", lpddsd->dwWidth, lpddsd->dwHeight );

		return ( DDENUMRET_OK );
	}
	else if ( lpddsd->ddpfPixelFormat.dwFlags & DDPF_ALPHAPIXELS)
	{

		//
		// Unknown display, ignore
		//
		debug_log ( "Resolution %i x %i skipped because alpha flag was set", lpddsd->dwWidth, lpddsd->dwHeight );

		return ( DDENUMRET_OK );
	}
	else
	{

		display_modes[number_display_modes].palette = FALSE;
		display_modes[number_display_modes].bpp_palette = 0;

		if ( lpddsd->ddpfPixelFormat.dwRBitMask )
		{

			for ( r=0, m=lpddsd->ddpfPixelFormat.dwRBitMask; !(m & 1); r++, m >>= 1)
					;

			for ( r=0; m & 1; r++, m >>= 1)
					;
		}

		if ( lpddsd->ddpfPixelFormat.dwGBitMask )
		{

			for ( g=0, m=lpddsd->ddpfPixelFormat.dwGBitMask; !(m & 1); g++, m >>= 1)
					;
			
			for ( g=0; m & 1; g++, m >>= 1)
					;
		}

		if ( lpddsd->ddpfPixelFormat.dwBBitMask )
		{

			for ( b=0, m=lpddsd->ddpfPixelFormat.dwBBitMask; !(m & 1); b++, m >>= 1)
					;
			
			for ( b=0; m & 1; b++, m >>= 1)
					;
		}
		
		display_modes[number_display_modes].bpp_red = r;
		display_modes[number_display_modes].bpp_green = g;
		display_modes[number_display_modes].bpp_blue = b;

		if ( ( r + g + b ) <= 32 )
		{

			if ( ( lpddsd->dwWidth >= 640 ) && ( lpddsd->dwHeight >= 480 ) )
			{
				debug_log ( "Resolution %i x %i accepted", lpddsd->dwWidth, lpddsd->dwHeight );
				number_display_modes++;
			}
		}

		return ( DDENUMRET_OK );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ddraw_validate_basic_3d_properties ( void )
{

	HRESULT
		ddrval;
	
	DDCAPS
		DriverCaps,
		HELCaps;


	//
	// Get the capabilities of the driver
	//

	memset( &DriverCaps, 0, sizeof ( DDCAPS ) );

	DriverCaps.dwSize = sizeof ( DDCAPS );

	memset( &HELCaps, 0, sizeof ( DDCAPS ) );

	HELCaps.dwSize = sizeof ( DDCAPS );

	ddrval = IDirectDraw7_GetCaps ( ddraw.ddraw, &DriverCaps, &HELCaps );

	if ( ddrval != DD_OK )
	{

		return ( FALSE );
	}

	if ( DriverCaps.dwCaps & DDCAPS_3D )
	{

		//
		// Assess the basic drivers 3D capabilities
		//

		if ( ddraw_internal_assess_3d_capabilities ( ddraw.ddraw ) > 0 )
		{

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

static BOOL WINAPI ddraw_enumerate_drivers ( GUID FAR* lpGUID, LPSTR lpDriverDesc, LPSTR lpDriverName, LPVOID lpContext, HMONITOR hm )
{

	LPDIRECTDRAWX
		lpDD;
	
	HRESULT
		ddrval;
	
	DDCAPS
		DriverCaps,
		HELCaps;

	int
		nondisplay;

	nondisplay = *( ( int * ) lpContext );

	if ( nondisplay )
	{

		if ( !lpGUID )
		{

			return ( DDENUMRET_OK );
		}
	}

	//
	// Create the driver
	//

	ddrval = DirectDrawCreateEx ( lpGUID, ( LPVOID * ) &lpDD, &IID_IDirectDraw7, NULL );

	if ( ddrval != DD_OK )
	{

		return ( DDENUMRET_OK );
	}

	//
	// Get the capabilities of the driver. If any call fails, just carry on to the next driver
	//

	memset( &DriverCaps, 0, sizeof ( DDCAPS ) );

	DriverCaps.dwSize = sizeof ( DDCAPS );

	memset( &HELCaps, 0, sizeof ( DDCAPS ) );

	HELCaps.dwSize = sizeof ( DDCAPS );

	ddrval = IDirectDraw7_GetCaps ( lpDD, &DriverCaps, &HELCaps );

	if ( ddrval != DD_OK )
	{

		IDirectDraw7_Release ( lpDD );

		return ( DDENUMRET_OK );
	}

// mue 070223 enumerate all  devices. 3D capabilities not necessary for mfd export?
	if ( DriverCaps.dwCaps & DDCAPS_3D || command_line_export_mfd)
	{

		display_device
			*device;
	
		int
			assessment;

		//
		// Add this driver to the list
		//
	
		device = safe_malloc ( sizeof ( display_device ) );
	
		device->succ = display_devices;
	
		device->name = safe_malloc ( strlen ( lpDriverDesc ) + 1 );
	
		strcpy ( device->name, lpDriverDesc );
	
		if ( lpGUID )
		{
	
			device->is_primary = FALSE;
	
			memcpy ( &device->guid, lpGUID, sizeof ( GUID ) );
		}
		else
		{
	
			device->is_primary = TRUE;
		}

		device->is_nondisplay = *( ( int * ) lpContext );

		display_devices = device;
	
		number_of_display_devices++;
	
		//
		// Assess the drivers 3D capabilities
		//

		assessment = ddraw_internal_assess_3d_capabilities ( lpDD );

		debug_log ( "Driver: %s, assessment: %d", device->name, assessment );

		if ( assessment >= 0 )
		{

/*			if ( device->is_primary )
			{

				if ( assessment > 10 )
				{

					assessment = 10;
				}
			}
*/	
			device->assessment = assessment;
	
			if ( assessment > best_assessment )
			{
	
				//
				// This driver has better 3D capabilities than the previous best
				//

				debug_log ( "Setting the best display device: %s assessment: %d",device->name, assessment );
	
				best_assessment = assessment;
	
				best_display_device = device;
			}
		}
	}

	//
	// Release the driver
	//

	IDirectDraw7_Release ( lpDD );

	return ( DDENUMRET_OK );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//mue 070223 wrapper function for calling as a thread function
int ddraw_internal_set_cooperative_level( void *data )
{
	return ddraw_set_cooperative_level(*(ddraw_cooperative_level*) data);
}


BOOL ddraw_set_cooperative_level ( ddraw_cooperative_level level )
{

	HRESULT
		ddrval;

	static int
		cooperative_level = UNSET_COOPERATIVE_LEVEL;
				
	if(ddraw_export.ddraw)
	{
		ddrval = IDirectDraw7_SetCooperativeLevel ( ddraw_export.ddraw, application_window,DDSCL_SETFOCUSWINDOW | DDSCL_CREATEDEVICEWINDOW | DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_FPUPRESERVE );	//DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN );
	}

	if ( ddraw.ddraw )
	{

		if ( level == COOPERATIVE_LEVEL_EXCLUSIVE )
		{
	
			if ( cooperative_level != COOPERATIVE_LEVEL_EXCLUSIVE )
			{
				if(ddraw_export.ddraw)
				{
				ddrval = IDirectDraw7_SetCooperativeLevel ( ddraw.ddraw, application_window,DDSCL_SETFOCUSWINDOW );	//DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN );
				ddrval = IDirectDraw7_SetCooperativeLevel ( ddraw.ddraw, application_window,DDSCL_SETDEVICEWINDOW| DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_FPUPRESERVE );	//DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN );
				}
				else
				{				
				ddrval = IDirectDraw7_SetCooperativeLevel ( ddraw.ddraw, application_window, DDSCL_EXCLUSIVE | DDSCL_FPUPRESERVE | DDSCL_FULLSCREEN );	//DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN );
//				ddrval = IDirectDraw7_SetCooperativeLevel ( ddraw.ddraw, application_window, DDSCL_EXCLUSIVE | DDSCL_MULTITHREADED | DDSCL_FULLSCREEN );	//DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN );
				}
				if ( ddrval != DD_OK )
				{
					
					debug_log ( "Unable to set cooperative level to exclusive: %s", get_ddraw_error_message ( ddrval ) );
					
					return ( FALSE );
				}
				
				cooperative_level = COOPERATIVE_LEVEL_EXCLUSIVE;
			}
	
			return ( TRUE );
		}
		else
		{
	
			if ( cooperative_level != COOPERATIVE_LEVEL_NORMAL )
			{
				
				if ( cooperative_level == COOPERATIVE_LEVEL_EXCLUSIVE )
				{
					
					//
					// Were in fullscreen mode last. Restore the displaymode before relinquishing exclusive level
					//
					
					ddrval = IDirectDraw7_RestoreDisplayMode ( ddraw.ddraw );
					
					if ( ddrval != DD_OK )
					{
						
						debug_log ( "Unable to restore display mode: %s", get_ddraw_error_message ( ddrval ) );
						
						return ( FALSE );
					}
				}
				
				ddrval = IDirectDraw7_SetCooperativeLevel ( ddraw.ddraw, application_window, DDSCL_NORMAL | DDSCL_FPUPRESERVE );
//				ddrval = IDirectDraw7_SetCooperativeLevel ( ddraw.ddraw, application_window, DDSCL_NORMAL | DDSCL_MULTITHREADED );
				
				if ( ddrval != DD_OK )
				{
					
					debug_log ( "Unable to set cooperative level to normal: %s", get_ddraw_error_message ( ddrval ) );
					
					return ( FALSE );
				}
				
				cooperative_level = COOPERATIVE_LEVEL_NORMAL;
			}
	
			return ( TRUE );
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

static void save_system_palette ( void )
{
	HDC
		my_dc;
	

	my_dc = GetDC ( application_window );
	
	GetSystemPaletteEntries ( my_dc, 0, (1 << 8), system_colour_table );

	GetSystemPaletteEntries ( my_dc, 0, (1 << 8), application_colour_table );
	
	ReleaseDC ( application_window, my_dc);
}
		
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void blit_front_buffer_to_render_buffer ( void )
{

	HRESULT
		ret;

	if ( !ddraw.application_windowed )
	{
		ret = IDirectDrawSurface7_Blt ( ddraw.lpBackBuffer, NULL, ddraw.lpFrontBuffer, NULL, DDBLT_WAIT, NULL );

		if ( FAILED ( ret ) )
		{
	
			debug_log ( "Unable to copy front buffer to back buffer, %s", get_ddraw_error_message ( ret ) );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DDRAW_ERROR_MESSAGE
{

	HRESULT
		error;

	char
		* error_string;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static struct DDRAW_ERROR_MESSAGE ddraw_error_table[] =
{

	{ DDERR_ALREADYINITIALIZED, "DDERR_ALREADYINITIALIZED" },
	{ DDERR_CANNOTATTACHSURFACE, "DDERR_CANNOTATTACHSURFACE" },
	{ DDERR_CANNOTDETACHSURFACE, "DDERR_CANNOTDETACHSURFACE" },
	{ DDERR_CURRENTLYNOTAVAIL, "DDERR_CURRENTLYNOTAVAIL" },
	{ DDERR_EXCEPTION, "DDERR_EXCEPTION" },
	{ DDERR_GENERIC, "DDERR_GENERIC" },
	{ DDERR_HEIGHTALIGN, "DDERR_HEIGHTALIGN" },
	{ DDERR_INCOMPATIBLEPRIMARY, "DDERR_INCOMPATIBLEPRIMARY" },
	{ DDERR_INVALIDCAPS, "DDERR_INVALIDCAPS" },
	{ DDERR_INVALIDCLIPLIST, "DDERR_INVALIDCLIPLIST" },
	{ DDERR_INVALIDMODE, "DDERR_INVALIDMODE" },
	{ DDERR_INVALIDOBJECT, "DDERR_INVALIDOBJECT" },
	{ DDERR_INVALIDPARAMS, "DDERR_INVALIDPARAMS" },
	{ DDERR_INVALIDPIXELFORMAT, "DDERR_INVALIDPIXELFORMAT" },
	{ DDERR_INVALIDRECT, "DDERR_INVALIDRECT" },
	{ DDERR_LOCKEDSURFACES, "DDERR_LOCKEDSURFACES" },
	{ DDERR_NO3D, "DDERR_NO3D" },
	{ DDERR_NOALPHAHW, "DDERR_NOALPHAHW" },
	{ DDERR_NOSTEREOHARDWARE, "DDERR_NOSTEREOHARDWARE" },
	{ DDERR_NOSURFACELEFT, "DDERR_NOSURFACELEFT" },
	{ DDERR_NOCLIPLIST, "DDERR_NOCLIPLIST" },
	{ DDERR_NOCOLORCONVHW, "DDERR_NOCOLORCONVHW" },
	{ DDERR_NOCOOPERATIVELEVELSET, "DDERR_NOCOOPERATIVELEVELSET" },
	{ DDERR_NOCOLORKEY, "DDERR_NOCOLORKEY" },
	{ DDERR_NOCOLORKEYHW, "DDERR_NOCOLORKEYHW" },
	{ DDERR_NODIRECTDRAWSUPPORT, "DDERR_NODIRECTDRAWSUPPORT" },
	{ DDERR_NOEXCLUSIVEMODE, "DDERR_NOEXCLUSIVEMODE" },
	{ DDERR_NOFLIPHW, "DDERR_NOFLIPHW" },
	{ DDERR_NOGDI, "DDERR_NOGDI" },
	{ DDERR_NOMIRRORHW, "DDERR_NOMIRRORHW" },
	{ DDERR_NOTFOUND, "DDERR_NOTFOUND" },
	{ DDERR_NOOVERLAYHW, "DDERR_NOOVERLAYHW" },
	{ DDERR_OVERLAPPINGRECTS, "DDERR_OVERLAPPINGRECTS" },
	{ DDERR_NORASTEROPHW, "DDERR_NORASTEROPHW" },
	{ DDERR_NOROTATIONHW, "DDERR_NOROTATIONHW" },
	{ DDERR_NOSTRETCHHW, "DDERR_NOSTRETCHHW" },
	{ DDERR_NOT4BITCOLOR, "DDERR_NOT4BITCOLOR" },
	{ DDERR_NOT4BITCOLORINDEX, "DDERR_NOT4BITCOLORINDEX" },
	{ DDERR_NOT8BITCOLOR, "DDERR_NOT8BITCOLOR" },
	{ DDERR_NOTEXTUREHW, "DDERR_NOTEXTUREHW" },
	{ DDERR_NOVSYNCHW, "DDERR_NOVSYNCHW" },
	{ DDERR_NOZBUFFERHW, "DDERR_NOZBUFFERHW" },
	{ DDERR_NOZOVERLAYHW, "DDERR_NOZOVERLAYHW" },
	{ DDERR_OUTOFCAPS, "DDERR_OUTOFCAPS" },
	{ DDERR_OUTOFMEMORY, "DDERR_OUTOFMEMORY" },
	{ DDERR_OUTOFVIDEOMEMORY, "DDERR_OUTOFVIDEOMEMORY" },
	{ DDERR_OVERLAYCANTCLIP, "DDERR_OVERLAYCANTCLIP" },
	{ DDERR_OVERLAYCOLORKEYONLYONEACTIVE, "DDERR_OVERLAYCOLORKEYONLYONEACTIVE" },
	{ DDERR_PALETTEBUSY, "DDERR_PALETTEBUSY" },
	{ DDERR_COLORKEYNOTSET, "DDERR_COLORKEYNOTSET" },
	{ DDERR_SURFACEALREADYATTACHED, "DDERR_SURFACEALREADYATTACHED" },
	{ DDERR_SURFACEALREADYDEPENDENT, "DDERR_SURFACEALREADYDEPENDENT" },
	{ DDERR_SURFACEBUSY, "DDERR_SURFACEBUSY" },
	{ DDERR_CANTLOCKSURFACE, "DDERR_CANTLOCKSURFACE" },
	{ DDERR_SURFACEISOBSCURED, "DDERR_SURFACEISOBSCURED" },
	{ DDERR_SURFACELOST, "DDERR_SURFACELOST" },
	{ DDERR_SURFACENOTATTACHED, "DDERR_SURFACENOTATTACHED" },
	{ DDERR_TOOBIGHEIGHT, "DDERR_TOOBIGHEIGHT" },
	{ DDERR_TOOBIGSIZE, "DDERR_TOOBIGSIZE" },
	{ DDERR_TOOBIGWIDTH, "DDERR_TOOBIGWIDTH" },
	{ DDERR_UNSUPPORTED, "DDERR_UNSUPPORTED" },
	{ DDERR_UNSUPPORTEDFORMAT, "DDERR_UNSUPPORTEDFORMAT" },
	{ DDERR_UNSUPPORTEDMASK, "DDERR_UNSUPPORTEDMASK" },
	{ DDERR_INVALIDSTREAM, "DDERR_INVALIDSTREAM" },
	{ DDERR_VERTICALBLANKINPROGRESS, "DDERR_VERTICALBLANKINPROGRESS" },
	{ DDERR_WASSTILLDRAWING, "DDERR_WASSTILLDRAWING" },
	{ DDERR_DDSCAPSCOMPLEXREQUIRED, "DDERR_DDSCAPSCOMPLEXREQUIRED" },
	{ DDERR_XALIGN, "DDERR_XALIGN" },
	{ DDERR_INVALIDDIRECTDRAWGUID, "DDERR_INVALIDDIRECTDRAWGUID" },
	{ DDERR_DIRECTDRAWALREADYCREATED, "DDERR_DIRECTDRAWALREADYCREATED" },
	{ DDERR_NODIRECTDRAWHW, "DDERR_NODIRECTDRAWHW" },
	{ DDERR_PRIMARYSURFACEALREADYEXISTS, "DDERR_PRIMARYSURFACEALREADYEXISTS" },
	{ DDERR_NOEMULATION, "DDERR_NOEMULATION" },
	{ DDERR_REGIONTOOSMALL, "DDERR_REGIONTOOSMALL" },
	{ DDERR_CLIPPERISUSINGHWND, "DDERR_CLIPPERISUSINGHWND" },
	{ DDERR_NOCLIPPERATTACHED, "DDERR_NOCLIPPERATTACHED" },
	{ DDERR_NOHWND, "DDERR_NOHWND" },
	{ DDERR_HWNDSUBCLASSED, "DDERR_HWNDSUBCLASSED" },
	{ DDERR_HWNDALREADYSET, "DDERR_HWNDALREADYSET" },
	{ DDERR_NOPALETTEATTACHED, "DDERR_NOPALETTEATTACHED" },
	{ DDERR_NOPALETTEHW, "DDERR_NOPALETTEHW" },
	{ DDERR_BLTFASTCANTCLIP, "DDERR_BLTFASTCANTCLIP" },
	{ DDERR_NOBLTHW, "DDERR_NOBLTHW" },
	{ DDERR_NODDROPSHW, "DDERR_NODDROPSHW" },
	{ DDERR_OVERLAYNOTVISIBLE, "DDERR_OVERLAYNOTVISIBLE" },
	{ DDERR_NOOVERLAYDEST, "DDERR_NOOVERLAYDEST" },
	{ DDERR_INVALIDPOSITION, "DDERR_INVALIDPOSITION" },
	{ DDERR_NOTAOVERLAYSURFACE, "DDERR_NOTAOVERLAYSURFACE" },
	{ DDERR_EXCLUSIVEMODEALREADYSET, "DDERR_EXCLUSIVEMODEALREADYSET" },
	{ DDERR_NOTFLIPPABLE, "DDERR_NOTFLIPPABLE" },
	{ DDERR_CANTDUPLICATE, "DDERR_CANTDUPLICATE" },
	{ DDERR_NOTLOCKED, "DDERR_NOTLOCKED" },
	{ DDERR_CANTCREATEDC, "DDERR_CANTCREATEDC" },
	{ DDERR_NODC, "DDERR_NODC" },
	{ DDERR_WRONGMODE, "DDERR_WRONGMODE" },
	{ DDERR_IMPLICITLYCREATED, "DDERR_IMPLICITLYCREATED" },
	{ DDERR_NOTPALETTIZED, "DDERR_NOTPALETTIZED" },
	{ DDERR_UNSUPPORTEDMODE, "DDERR_UNSUPPORTEDMODE" },
	{ DDERR_NOMIPMAPHW, "DDERR_NOMIPMAPHW" },
	{ DDERR_INVALIDSURFACETYPE, "DDERR_INVALIDSURFACETYPE" },
	{ DDERR_NOOPTIMIZEHW, "DDERR_NOOPTIMIZEHW" },
	{ DDERR_NOTLOADED, "DDERR_NOTLOADED" },
	{ DDERR_NOFOCUSWINDOW, "DDERR_NOFOCUSWINDOW" },
	{ DDERR_DCALREADYCREATED, "DDERR_DCALREADYCREATED" },
	{ DDERR_NONONLOCALVIDMEM, "DDERR_NONONLOCALVIDMEM" },
	{ DDERR_CANTPAGELOCK, "DDERR_CANTPAGELOCK" },
	{ DDERR_CANTPAGEUNLOCK, "DDERR_CANTPAGEUNLOCK" },
	{ DDERR_NOTPAGELOCKED, "DDERR_NOTPAGELOCKED" },
	{ DDERR_MOREDATA, "DDERR_MOREDATA" },
	{ DDERR_EXPIRED, "DDERR_EXPIRED" },
	{ DDERR_TESTFINISHED, "DDERR_TESTFINISHED" },
	{ DDERR_NEWMODE, "DDERR_NEWMODE" },
	{ DDERR_VIDEONOTACTIVE, "DDERR_VIDEONOTACTIVE" },
	{ DDERR_DEVICEDOESNTOWNSURFACE, "DDERR_DEVICEDOESNTOWNSURFACE" },
	{ DDERR_NOTINITIALIZED, "DDERR_NOTINITIALIZED" },
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
	{ D3DERR_VERTEXBUFFERUNLOCKFAILED, "D3DERR_VERTEXBUFFERUNLOCKFAILED" },
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
	{ D3DERR_INVALIDSTATEBLOCK, "D3DERR_INVALIDSTATEBLOCK" },
	{ D3DERR_INBEGINSTATEBLOCK, "D3DERR_INBEGINSTATEBLOCK" },
	{ D3DERR_NOTINBEGINSTATEBLOCK, "D3DERR_NOTINBEGINSTATEBLOCK" },
	{ 0, "NO ERROR" },
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char * get_ddraw_error_message ( HRESULT error )
{

	int
		count;


	count = 0;

	while ( ( ddraw_error_table[count].error != 0 ) && ( ddraw_error_table[count].error != error ) )
	{

		count ++;
	}

	return ( ddraw_error_table[count].error_string );
}

void copy_surface_to_surface(LPDIRECTDRAWSURFACEX src, RECT src_rect, LPDIRECTDRAWSURFACEX dst, RECT dst_rect )
{
	DDSURFACEDESC2
		src_ddsd,
		dest_ddsd;
	HRESULT ddrval;

	//
	// Lock the surface memory
	//
	src_ddsd.dwSize = sizeof ( src_ddsd );
	dest_ddsd.dwSize = sizeof ( dest_ddsd );
	ddrval=IDirectDrawSurface7_Lock ( dst, &dst_rect, &dest_ddsd, DDLOCK_NOSYSLOCK|DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL );
	if ( ddrval != DD_OK )
		debug_log ( "Unable to lock dst%s", get_ddraw_error_message ( ddrval ) );
	debug_log("size:dst %d %d",dest_ddsd.dwHeight,dest_ddsd.dwWidth);	
	ddrval=IDirectDrawSurface7_Lock ( src, &src_rect, &src_ddsd, DDLOCK_NOSYSLOCK|DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL );
	debug_log("size:src %d %d",src_ddsd.dwHeight,src_ddsd.dwWidth);	
	if ( ddrval != DD_OK )
		debug_log ( "Unable to lock src%s", get_ddraw_error_message ( ddrval ) );
	{

		unsigned char
			*source_screen,
			*dest_screen;

		int
			width,height, w, h;
/*		int 
		src_surface_red_mask,
		src_surface_green_mask,
		src_surface_blue_mask,
		src_surface_red_shift,
		src_surface_green_shift,
		src_surface_blue_shift,
		dst_surface_red_mask,
		dst_surface_green_mask,
		dst_surface_blue_mask,
		dst_surface_red_shift,
		dst_surface_green_shift,
		dst_surface_blue_shift;
		unsigned int
		red,
		green,
		blue;

		set_surface_shift_and_mask(src_ddsd.ddpfPixelFormat.dwRBitMask, &src_surface_red_mask, &src_surface_red_shift);
		set_surface_shift_and_mask(src_ddsd.ddpfPixelFormat.dwGBitMask, &src_surface_green_mask, &src_surface_green_shift);
		set_surface_shift_and_mask(src_ddsd.ddpfPixelFormat.dwBBitMask, &src_surface_blue_mask, &src_surface_blue_shift);

		set_surface_shift_and_mask(dest_ddsd.ddpfPixelFormat.dwRBitMask, &dst_surface_red_mask, &dst_surface_red_shift);
		set_surface_shift_and_mask(dest_ddsd.ddpfPixelFormat.dwGBitMask, &dst_surface_green_mask, &dst_surface_green_shift);
		set_surface_shift_and_mask(dest_ddsd.ddpfPixelFormat.dwBBitMask, &dst_surface_blue_mask, &dst_surface_blue_shift);
			
		dst_surface_red_mask&=src_surface_red_mask;
		dst_surface_green_mask&=src_surface_green_mask;
		dst_surface_blue_mask&=src_surface_blue_mask;
//		dst_surface_red_mask|=(dst_surface_red_mask>>16);
//		dst_surface_green_mask|=(dst_surface_green_mask>>16);
//		dst_surface_blue_mask|=(dst_surface_blue_mask>>16);
//		dst_surface_red_mask>>=src_surface_red_shift;
//		dst_surface_green_mask>>=src_surface_green_shift;
//		dst_surface_blue_mask>>=src_surface_blue_shift;
*/
		w=src_rect.right-src_rect.left;
		h=src_rect.bottom-src_rect.top;

		source_screen = src_ddsd.lpSurface;
		dest_screen = dest_ddsd.lpSurface;
				
		for ( height=0; height < h; height++ )
		{
			double
			*source,
			*dest;

			source = ( double * ) source_screen;
			dest = ( double * ) dest_screen;
				
	/*		unsigned short int
			*source,
			*dest;

			source = ( unsigned short int* ) source_screen;
			dest = ( unsigned short int* ) dest_screen;
	*/			
			for ( width = w; width > 0; width -= 16 )
			{
/*
				red=*source<<src_surface_red_shift;
				green=*source<<src_surface_green_shift;
				blue=*source<<src_surface_blue_shift;
				red&=dst_surface_red_mask;
				green&=dst_surface_green_mask;
				blue&=dst_surface_blue_mask;
				red>>=dst_surface_red_shift;
				green>>=dst_surface_green_shift;
				blue>>=dst_surface_blue_shift;
				
				*dest=(red|green|blue);
				dest++;
				source++;
*/
				dest[0] = source[0];
				dest[1] = source[1];
				dest[2] = source[2];
				dest[3] = source[3];
				dest += 4;
				source += 4;

			}
		
			dest_screen += dest_ddsd.lPitch;
			source_screen += src_ddsd.lPitch;
		}
	}

	ddrval=IDirectDrawSurface7_Unlock ( dst, NULL );
	if ( ddrval != DD_OK )
		debug_log ( "Unable to unlock dst%s", get_ddraw_error_message ( ddrval ) );
					
	ddrval=IDirectDrawSurface7_Unlock ( src, NULL );
	if ( ddrval != DD_OK )
		debug_log ( "Unable to unlock src%s", get_ddraw_error_message ( ddrval ) );
}

void clear_export_mfd_screen()
{
	DDBLTFX fx;

	memset(&fx, 0, sizeof(fx));
	fx.dwSize = sizeof(fx);
	fx.dwFillColor = 0;

	IDirectDrawSurface7_Blt ( ddraw_export.lpBackBuffer,NULL, NULL, NULL, DDBLT_COLORFILL|DDBLT_WAIT, &fx);
	IDirectDrawSurface7_Blt ( ddraw_export.lpFrontBuffer,NULL, NULL, NULL, DDBLT_COLORFILL|DDBLT_WAIT, &fx);
}

void copy_export_mfd(screen* export_left, screen* export_right)
{
	RECT src_rect, dst_rect;

	if(export_left)
	{
	src_rect.left=0;
	src_rect.top=0;
	src_rect.right=export_left->width;
	src_rect.bottom=export_left->height;
	copy_surface_to_surface(export_left->surface, src_rect, ddraw_export.lpBackBuffer,src_rect);	
	}

	if(export_right)
	{
	src_rect.left=0;
	src_rect.top=0;
	src_rect.right=export_right->width;
	src_rect.bottom=export_right->height;
	dst_rect.left=272;
	dst_rect.top=0;
	dst_rect.right=272+export_right->width;
	dst_rect.bottom=export_right->height;
	copy_surface_to_surface(export_right->surface, src_rect, ddraw_export.lpBackBuffer,dst_rect);	
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

