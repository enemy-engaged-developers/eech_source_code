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

int
	mouse_graphic_needs_restoring = FALSE;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int
	mouse_graphic_position_x,
	mouse_graphic_position_y,
	mouse_graphic_on = FALSE,
	mouse_graphic_drawn = FALSE;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_mouse_pointer ( const int x, const int y );

void save_frontbuffer_screen_under_mouse_pointer ( int x, int y );

static void save_backbuffer_screen_under_mouse_pointer ( int x, int y );

void restore_screen_under_mouse_pointer ( void );

static void restore_backbuffer_screen_under_mouse_pointer ( void );

static void draw_backbuffer_mouse_pointer ( int x, int y );

static void swap_mouse_screen_buffers ( void );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct MOUSE_TRAIL_POSITION
{
	
	int
		x,
		y,
		used;
	
	struct MOUSE_TRAIL_POSITION
		*next;
};

typedef struct MOUSE_TRAIL_POSITION mouse_trail_position;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

mouse_trail_position
	mouse_trail_positions_array[256];

volatile struct MOUSE_TRAIL_POSITION
	*mouse_trails;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static screen
	*mouse_pointer_screen,
	*mouse_pointer_background,
	*mouse_backbuffer_pointer_background;

static int
	mouse_pointer_width = 10,
	mouse_pointer_height = 20;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_mouse_pointer ( rgb_packed *pointer )
{
	
	unsigned short int
		*ptr,
		*destptr;
	
	int
		x,
		y,
		count,
		destpitch;

	struct SCREEN
		*old_active_screen;
	
	mouse_trails = NULL;
	
	for ( count = 0; count < 256; count++ )
	{
		
		mouse_trail_positions_array[count].used = FALSE;
	}
	
	ptr = pointer + 2;
	
	mouse_pointer_screen = create_screen ( mouse_pointer_width, mouse_pointer_height, FALSE );

	mouse_pointer_background = create_screen ( mouse_pointer_width, mouse_pointer_height, FALSE );
	
	mouse_backbuffer_pointer_background = create_screen ( mouse_pointer_width, mouse_pointer_height, FALSE );

	old_active_screen = get_active_screen ();
	
	set_active_screen ( mouse_pointer_screen );
	
	while ( !lock_screen ( active_screen ) )
	{

		Sleep ( 100 );
	}

	destptr = ( unsigned short int * ) get_screen_data ( active_screen );

	destpitch = get_screen_pitch ( active_screen );

#if 0  // disabled as it doesn't work for all gfx-cards (gives cyan pointer)
	if (destpitch == mouse_pointer_width * 4) // 32bpp
	{
		rgb_colour* dest_rgba = (rgb_colour*)destptr;

		destpitch >>= 2; // bytes -> int's

		for ( y = 0; y < mouse_pointer_height; y++ )
		{
			for ( x = 0; x < mouse_pointer_width; x++ )
			{
				dest_rgba[x] = get_rgb_colour_value(*ptr++);
//				dest_rgba[x].a = 0;
			}
			
			dest_rgba += destpitch;
		}
	}
	else // (hopefully) 16bpp
#endif
	{
		destpitch >>= 1; // bytes -> shorts's

		for ( y = 0; y < mouse_pointer_height; y++ )
		{
			
			for ( x = 0; x < mouse_pointer_width; x++ )
			{
				
				destptr[x] = *ptr++;
			}
			
			destptr += destpitch;
		}
	}

	unlock_screen ( active_screen );

	set_active_screen (old_active_screen);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_mouse_pointer ( void )
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_mouse_graphic_on ( void )
{
	
	mouse_graphic_on = TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_mouse_graphic_off ( void )
{
	
	mouse_graphic_on = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_mouse_graphic_on ( void )
{
	
	return ( mouse_graphic_on );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_mouse_pointer ( void )
{
	
	if ( mouse_graphic_on )
	{
		
		if ( ( !mouse_graphic_drawn ) || ( mouse_graphic_position_x != get_mouse_x () ) || ( mouse_graphic_position_y != get_mouse_y () ) )
		{
			
			draw_mouse_pointer ( get_mouse_x (), get_mouse_y () );
			
			mouse_graphic_position_x = get_mouse_x ();
			
			mouse_graphic_position_y = get_mouse_y ();
			
			mouse_graphic_drawn = TRUE;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_mouse_pointer ( const int x, const int y )
{
	
	DDBLTFX
		ddbltfx;
	
	RECT
		my_rc,
		source_rc;
	
	HRESULT
		ret;
	
	ret = 0;

	if ( ( mouse_graphic_on ) && ( ddraw.ddraw ) && ( ddraw.lpFrontBuffer ) && ( ddraw.lpBackBuffer ) )
	{

		if ( mouse_graphic_needs_restoring )
		{
	
			//
			// Restore the previous background
			//
	
			restore_screen_under_mouse_pointer ();

			//
			// Save the current background
			//
	
			save_frontbuffer_screen_under_mouse_pointer ( x, y );
		}

		//
		// Draw the cursor
		//

		{
			
			my_rc.left = 0;
			
			my_rc.top = 0;
			
			source_rc.left = 0;
			
			source_rc.top = 0;
			
			source_rc.right = mouse_pointer_width;
			
			source_rc.bottom = mouse_pointer_height;
			
			if ( ddraw.application_windowed )
			{
				
				//
				// Adjust the top left part of the rectangle.
				//
				
				GetClientRect ( application_window, &my_rc );
				
				ClientToScreen ( application_window, ( LPPOINT ) &my_rc );
				
				ClientToScreen ( application_window, ( LPPOINT ) &my_rc + 1 );
			}
			
			
			my_rc.left += x;
			
			my_rc.top += y;
			
			my_rc.right = my_rc.left + mouse_pointer_width;
			
			my_rc.bottom = my_rc.top + mouse_pointer_height;
			
			if ( ( x + mouse_pointer_width ) > application_video_width )
			{
				
				source_rc.right -= ( ( x + mouse_pointer_width ) - application_video_width );
				
				my_rc.right -= ( ( x + mouse_pointer_width ) - application_video_width );
			}
			
			if ( ( y + mouse_pointer_height ) > application_video_height )
			{
				
				source_rc.bottom -= ( ( y + mouse_pointer_height ) - application_video_height );
				
				my_rc.bottom -= ( ( y + mouse_pointer_height ) - application_video_height );
			}
			
			memset ( &ddbltfx, 0, sizeof ( ddbltfx ) );
			
			ddbltfx.dwSize = sizeof ( ddbltfx );
			
			ddbltfx.dwROP = SRCCOPY;
			
			ddbltfx.ddckSrcColorkey.dwColorSpaceLowValue = 0;
			
			ddbltfx.ddckSrcColorkey.dwColorSpaceHighValue = 0;

			ret = IDirectDrawSurface7_Blt ( ddraw.lpFrontBuffer, &my_rc, mouse_pointer_screen->surface, &source_rc, DDBLT_KEYSRCOVERRIDE | DDBLT_WAIT, &ddbltfx );
			
			if ( ret != DD_OK )
			{
				
				debug_log ( "failed to blt: %s", get_ddraw_error_message ( ret ) );
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_raw_mouse_pointer ( const int x, const int y )
{
	
	DDBLTFX
		ddbltfx;
	
	RECT
		my_rc,
		source_rc;
	
	HRESULT
		ret;
	
	ret = 0;

	if ( ( mouse_graphic_on ) && ( ddraw.ddraw ) && ( ddraw.lpFrontBuffer ) && ( ddraw.lpBackBuffer ) )
	{

		//
		// Draw the cursor
		//

		{
			
			my_rc.left = 0;
			
			my_rc.top = 0;
			
			source_rc.left = 0;
			
			source_rc.top = 0;
			
			source_rc.right = mouse_pointer_width;
			
			source_rc.bottom = mouse_pointer_height;
			
			my_rc.left += x;
			
			my_rc.top += y;
			
			my_rc.right = my_rc.left + mouse_pointer_width;
			
			my_rc.bottom = my_rc.top + mouse_pointer_height;
			
			if ( ( x + mouse_pointer_width ) > application_video_width )
			{
				
				source_rc.right -= ( ( x + mouse_pointer_width ) - application_video_width );
				
				my_rc.right -= ( ( x + mouse_pointer_width ) - application_video_width );
			}
			
			if ( ( y + mouse_pointer_height ) > application_video_height )
			{
				
				source_rc.bottom -= ( ( y + mouse_pointer_height ) - application_video_height );
				
				my_rc.bottom -= ( ( y + mouse_pointer_height ) - application_video_height );
			}
			
			memset ( &ddbltfx, 0, sizeof ( ddbltfx ) );
			
			ddbltfx.dwSize = sizeof ( ddbltfx );
			
			ddbltfx.dwROP = SRCCOPY;
			
			ddbltfx.ddckSrcColorkey.dwColorSpaceLowValue = 0;
			
			ddbltfx.ddckSrcColorkey.dwColorSpaceHighValue = 0;

			ret = IDirectDrawSurface7_Blt ( ddraw.lpBackBuffer, &my_rc, mouse_pointer_screen->surface, &source_rc, DDBLT_KEYSRCOVERRIDE | DDBLT_WAIT, &ddbltfx );
			
			if ( ret != DD_OK )
			{
				
				debug_log ( "failed to blt: %s", get_ddraw_error_message ( ret ) );
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void flip_video_screen_with_mouse ( void )
{
	
	ASSERT ( video_screen );

	if ( ( ddraw.ddraw ) && ( ddraw.lpFrontBuffer ) && ( ddraw.lpBackBuffer ) )
	{

		//
		// Save the area underneath the mouse pointer
		//

		save_backbuffer_screen_under_mouse_pointer ( get_mouse_x (), get_mouse_y () );

		//
		// Draw the mouse cursor onto the back buffer
		//

		draw_backbuffer_mouse_pointer ( get_mouse_x (), get_mouse_y () );

		ddraw_flip_surface ();

		//
		// Screen has been flipped, but the backbuffer still has a mouse image on it - restore it
		//

		restore_backbuffer_screen_under_mouse_pointer ();

		//
		// Now the area under the mouse on the front buffer & rectangle is stored in the back buffer variables
		//

		swap_mouse_screen_buffers ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RECT
	saved_screen_mouse_rectangle,
	saved_screen_screen_rectangle,

	saved_back_screen_mouse_rectangle,
	saved_back_screen_screen_rectangle;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void save_frontbuffer_screen_under_mouse_pointer ( int x, int y )
{

	DDBLTFX
		ddbltfx;

	HRESULT
		ret;
	
	if ( ( mouse_graphic_on ) && ( ddraw.ddraw ) && ( ddraw.lpFrontBuffer ) && ( ddraw.lpBackBuffer ) )
	{

		RECT
			screen_rectangle;

		saved_screen_screen_rectangle.left = 0;
		
		saved_screen_screen_rectangle.top = 0;
		
		saved_screen_mouse_rectangle.left = 0;
		
		saved_screen_mouse_rectangle.top = 0;
		
		saved_screen_mouse_rectangle.right = mouse_pointer_width;
		
		saved_screen_mouse_rectangle.bottom = mouse_pointer_height;
		
		saved_screen_screen_rectangle.left += x;
		
		saved_screen_screen_rectangle.top += y;
		
		saved_screen_screen_rectangle.right = saved_screen_screen_rectangle.left + mouse_pointer_width;
		
		saved_screen_screen_rectangle.bottom = saved_screen_screen_rectangle.top + mouse_pointer_height;
		
		if ( ( x + mouse_pointer_width ) > application_video_width )
		{
			
			saved_screen_mouse_rectangle.right -= ( ( x + mouse_pointer_width ) - application_video_width );
			
			saved_screen_screen_rectangle.right -= ( ( x + mouse_pointer_width ) - application_video_width );
		}
		
		if ( ( y + mouse_pointer_height ) > application_video_height )
		{
			
			saved_screen_mouse_rectangle.bottom -= ( ( y + mouse_pointer_height ) - application_video_height );
			
			saved_screen_screen_rectangle.bottom -= ( ( y + mouse_pointer_height ) - application_video_height );
		}

		screen_rectangle = saved_screen_screen_rectangle;

		if ( ddraw.application_windowed )
		{

			RECT
				my_rc;
			
			//
			// Adjust the top left part of the rectangle.
			//
			
			GetClientRect ( application_window, &my_rc );
			ClientToScreen ( application_window, ( LPPOINT ) &my_rc );
			ClientToScreen ( application_window, ( LPPOINT ) &my_rc + 1 );

			screen_rectangle.left += my_rc.left;
			screen_rectangle.right += my_rc.left;
			screen_rectangle.top += my_rc.top;
			screen_rectangle.bottom += my_rc.top;
		}
		
		memset ( &ddbltfx, 0, sizeof ( ddbltfx ) );
		
		ddbltfx.dwSize = sizeof ( ddbltfx );
		
		ddbltfx.dwROP = SRCCOPY;
		
		ret = IDirectDrawSurface7_Blt ( mouse_pointer_background->surface,
															&saved_screen_mouse_rectangle,
															ddraw.lpFrontBuffer,
															&screen_rectangle,
															DDBLT_ROP | DDBLT_WAIT, &ddbltfx );
		
		if ( ret != DD_OK )
		{
			
			debug_log ( "save_frontbuffer_screen_under_mouse_pointer: %s", get_ddraw_error_message ( ret ) );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void save_backbuffer_screen_under_mouse_pointer ( int x, int y )
{

	DDBLTFX
		ddbltfx;

	HRESULT
		ret;
	
	if ( ( mouse_graphic_on ) && ( ddraw.ddraw ) && ( ddraw.lpFrontBuffer ) && ( ddraw.lpBackBuffer ) )
	{

		saved_back_screen_screen_rectangle.left = 0;
		
		saved_back_screen_screen_rectangle.top = 0;
		
		saved_back_screen_mouse_rectangle.left = 0;
		
		saved_back_screen_mouse_rectangle.top = 0;
		
		saved_back_screen_mouse_rectangle.right = mouse_pointer_width;
		
		saved_back_screen_mouse_rectangle.bottom = mouse_pointer_height;
		
		saved_back_screen_screen_rectangle.left += x;
		
		saved_back_screen_screen_rectangle.top += y;
		
		saved_back_screen_screen_rectangle.right = saved_back_screen_screen_rectangle.left + mouse_pointer_width;
		
		saved_back_screen_screen_rectangle.bottom = saved_back_screen_screen_rectangle.top + mouse_pointer_height;
		
		if ( ( x + mouse_pointer_width ) > application_video_width )
		{
			
			saved_back_screen_mouse_rectangle.right -= ( ( x + mouse_pointer_width ) - application_video_width );
			
			saved_back_screen_screen_rectangle.right -= ( ( x + mouse_pointer_width ) - application_video_width );
		}
		
		if ( ( y + mouse_pointer_height ) > application_video_height )
		{
			
			saved_back_screen_mouse_rectangle.bottom -= ( ( y + mouse_pointer_height ) - application_video_height );
			
			saved_back_screen_screen_rectangle.bottom -= ( ( y + mouse_pointer_height ) - application_video_height );
		}
		
		memset ( &ddbltfx, 0, sizeof ( ddbltfx ) );
		
		ddbltfx.dwSize = sizeof ( ddbltfx );
		
		ddbltfx.dwROP = SRCCOPY;
		
		ret = IDirectDrawSurface7_Blt ( mouse_backbuffer_pointer_background->surface,
															&saved_back_screen_mouse_rectangle,
															ddraw.lpBackBuffer,
															&saved_back_screen_screen_rectangle,
															DDBLT_ROP | DDBLT_WAIT, &ddbltfx );
		
		if ( ret != DD_OK )
		{
			
			debug_log ( "save_backbuffer_screen_under_mouse_pointer: %s", get_ddraw_error_message ( ret ) );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void restore_screen_under_mouse_pointer ( void )
{

	HRESULT
		ret;
	
	if ( ( mouse_graphic_on ) && ( ddraw.ddraw ) && ( ddraw.lpFrontBuffer ) && ( ddraw.lpBackBuffer ) )
	{

		DDBLTFX
			ddbltfx;

		RECT
			screen_rectangle;
		
		screen_rectangle = saved_screen_screen_rectangle;

		if ( ddraw.application_windowed )
		{

			RECT
				my_rc;
			
			//
			// Adjust the top left part of the rectangle.
			//
			
			GetClientRect ( application_window, &my_rc );
			ClientToScreen ( application_window, ( LPPOINT ) &my_rc );
			ClientToScreen ( application_window, ( LPPOINT ) &my_rc + 1 );

			screen_rectangle.left += my_rc.left;
			screen_rectangle.right += my_rc.left;
			screen_rectangle.top += my_rc.top;
			screen_rectangle.bottom += my_rc.top;
		}

		ddbltfx.dwSize = sizeof ( ddbltfx );
		
		ddbltfx.dwROP = SRCCOPY;
		
		ret = IDirectDrawSurface7_Blt ( ddraw.lpFrontBuffer,
															&screen_rectangle,
															mouse_pointer_background->surface,
															&saved_screen_mouse_rectangle,
															DDBLT_ROP | DDBLT_WAIT, &ddbltfx );
		
		if ( ret != DD_OK )
		{
			
			debug_log ( "restore_screen_under_mouse_pointer: %s", get_ddraw_error_message ( ret ) );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void restore_backbuffer_screen_under_mouse_pointer ( void )
{

	HRESULT
		ret;
	
	if ( ( mouse_graphic_on ) && ( ddraw.ddraw ) && ( ddraw.lpFrontBuffer ) && ( ddraw.lpBackBuffer ) )
	{

		DDBLTFX
			ddbltfx;
		
		ddbltfx.dwSize = sizeof ( ddbltfx );
		
		ddbltfx.dwROP = SRCCOPY;

		ret = IDirectDrawSurface7_Blt ( ddraw.lpBackBuffer,
															&saved_screen_screen_rectangle,
															mouse_pointer_background->surface,
															&saved_screen_mouse_rectangle,
															DDBLT_ROP | DDBLT_WAIT, &ddbltfx );

		if ( ret != DD_OK )
		{

			debug_log ( "restore_backbuffer_screen_under_mouse_pointer: %s", get_ddraw_error_message ( ret ) );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_backbuffer_mouse_pointer ( int x, int y )
{

	DDBLTFX
		ddbltfx;
	
	RECT
		my_rc,
		source_rc;
	
	HRESULT
		ret;
	
	if ( ( mouse_graphic_on ) && ( ddraw.ddraw ) && ( ddraw.lpFrontBuffer ) && ( ddraw.lpBackBuffer ) )
	{

		my_rc.left = 0;
		
		my_rc.top = 0;
		
		source_rc.left = 0;
		
		source_rc.top = 0;
		
		source_rc.right = mouse_pointer_width;
		
		source_rc.bottom = mouse_pointer_height;

		//
		// Do not adjust the back buffer mouse position under a window run
		//

		my_rc.left += x;
		
		my_rc.top += y;
		
		my_rc.right = my_rc.left + mouse_pointer_width;
		
		my_rc.bottom = my_rc.top + mouse_pointer_height;
		
		if ( ( x + mouse_pointer_width ) > application_video_width )
		{
			
			source_rc.right -= ( ( x + mouse_pointer_width ) - application_video_width );
			
			my_rc.right -= ( ( x + mouse_pointer_width ) - application_video_width );
		}
		
		if ( ( y + mouse_pointer_height ) > application_video_height )
		{
			
			source_rc.bottom -= ( ( y + mouse_pointer_height ) - application_video_height );
			
			my_rc.bottom -= ( ( y + mouse_pointer_height ) - application_video_height );
		}
		
		memset ( &ddbltfx, 0, sizeof ( ddbltfx ) );
		
		ddbltfx.dwSize = sizeof ( ddbltfx );
		
		ddbltfx.dwROP = SRCCOPY;
		
		ddbltfx.ddckSrcColorkey.dwColorSpaceLowValue = 0;
		
		ddbltfx.ddckSrcColorkey.dwColorSpaceHighValue = 0;
		
		ret = IDirectDrawSurface7_Blt ( ddraw.lpBackBuffer, &my_rc, mouse_pointer_screen->surface, &source_rc, DDBLT_ROP | DDBLT_KEYSRCOVERRIDE | DDBLT_WAIT, &ddbltfx );

		if ( ret != DD_OK )
		{

			debug_log ( "draw_backbuffer_mouse_pointer: %s", get_ddraw_error_message ( ret ) );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void swap_mouse_screen_buffers ( void )
{

	screen
		*temp;

	saved_screen_mouse_rectangle = saved_back_screen_mouse_rectangle;
	saved_screen_screen_rectangle = saved_back_screen_screen_rectangle;

	temp = mouse_pointer_background;

	mouse_pointer_background = mouse_backbuffer_pointer_background;

	mouse_backbuffer_pointer_background = temp;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

