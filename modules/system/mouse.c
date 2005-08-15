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



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "system.h"

#include "graphics.h"

#include "cmndline.h"	// Retro 030317, need this for mouse_look and mouse_look_speed

#include "flight.h"	// Retro 25Jul2004 for mouse in-game mode thingie

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_DI_MOUSE_EVENTS 256

#define MOUSE_BUFFER_SIZE 16

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MOUSE_DEBUG 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static LPDIRECTINPUTDEVICE7
	direct_input_mouse;

static DIDEVICEOBJECTDATA
	direct_input_mouse_events[MAX_DI_MOUSE_EVENTS];

static int
	mouse_position_x = 0,
	mouse_position_y = 0,
	abs_mouse_x = 0,		// Retro 030317
	abs_mouse_y = 0,		// Retro 030317
	mouse_on;

static POINT
	windows_cursor_position;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HANDLE
	mouse_handle = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void ( *remove_mouse_graphic_function ) ( const int x, const int y );

static void ( *draw_mouse_graphic_function ) ( const int x, const int y );

void draw_mouse_graphic ( const int x, const int y );

void mouse_activation_routine ( int activate );

static long windows_mouse_move_routine ( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

static long windows_left_button_up_routine ( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

static long windows_left_button_down_routine ( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

static long windows_right_button_up_routine ( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

static long windows_right_button_down_routine ( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

static long windows_middle_button_up_routine ( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam ); // Jabberwock 031016

static long windows_middle_button_down_routine ( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_mouse ( void )
{

	HRESULT
		ret;

	DIPROPDWORD
		di_buffer_data;

	mouse_position_x = 0;

	mouse_position_y = 0;

	mouse_on = FALSE;

	remove_mouse_graphic_function = NULL;

	draw_mouse_graphic_function = NULL;

	if ( input_system_type == INPUT_DIRECTINPUT )
	{
	
		ret = IDirectInput7_CreateDeviceEx ( direct_input, &GUID_SysMouse, &IID_IDirectInputDevice7, ( LPVOID * ) &direct_input_mouse, NULL );
	
		if (ret != DI_OK )
		{
	
			return;
		}
	
		ret = IDirectInputDevice7_SetDataFormat ( direct_input_mouse, &c_dfDIMouse );
	
		if ( ret != DI_OK )
		{
	
			return;
		}

		// JB 030311 from Andrew
		// Sometimes a double mouse is visible (when the resilution in EECH is different from the desktop)
		// VJ 030430 Double mouse problem, Changed last param to NONEXCLUSIVE
		ret = IDirectInputDevice7_SetCooperativeLevel ( direct_input_mouse, application_window, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );	
		
		if ( ret != DI_OK )
		{
	
			return;
		}

		mouse_handle = CreateEvent ( 0, 0, 0, 0 );

		if ( mouse_handle == NULL )
		{

			debug_fatal ( "Unable to create a handle for the mouse" );
		}

		IDirectInputDevice7_SetEventNotification ( direct_input_mouse, mouse_handle );

		//
		// Set the hardware buffering of the keyboard
		//
	
		di_buffer_data.diph.dwSize = sizeof ( DIPROPDWORD );
		di_buffer_data.diph.dwHeaderSize = sizeof ( DIPROPHEADER );
		di_buffer_data.diph.dwObj = 0;
		di_buffer_data.diph.dwHow = DIPH_DEVICE;
		di_buffer_data.dwData = MOUSE_BUFFER_SIZE;
	
		ret = IDirectInputDevice7_SetProperty ( direct_input_mouse, DIPROP_BUFFERSIZE, &di_buffer_data.diph );
	
		if ( ret != DI_OK )
		{
	
			return;
		}

		//
		// register the activation routine.
		//

		register_pre_activate_message_function ( mouse_activation_routine );

		ret = IDirectInputDevice7_Acquire ( direct_input_mouse );
	}
	else
	{

		//
		// Assumes the only other input system is windows
		//

		GetCursorPos ( &windows_cursor_position );

		register_system_message_function ( WM_MOUSEMOVE, windows_mouse_move_routine );
		register_system_message_function ( WM_LBUTTONDOWN, windows_left_button_down_routine );
		register_system_message_function ( WM_LBUTTONUP, windows_left_button_up_routine );
		register_system_message_function ( WM_RBUTTONDOWN, windows_right_button_down_routine );
		register_system_message_function ( WM_RBUTTONUP, windows_right_button_up_routine );
		register_system_message_function ( WM_MBUTTONDOWN, windows_middle_button_down_routine );
		register_system_message_function ( WM_MBUTTONUP, windows_middle_button_up_routine ); // Jabberwock 031016 Middle button

	}

	ret = IDirectInputDevice7_SetCooperativeLevel ( direct_input_mouse, application_window, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_mouse ( void )
{

	if ( direct_input_mouse )
	{

		IDirectInputDevice7_Unacquire ( direct_input_mouse );

		IDirectInputDevice7_Release ( direct_input_mouse );

		direct_input_mouse = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void mouse_activation_routine ( int activate )
{

	if ( direct_input_mouse )
	{

		if ( !activate )
		{

			//
			// We are about to LOSE focus
			//
	
			IDirectInputDevice7_Unacquire ( direct_input_mouse );
		}
		else
		{

			//
			// About to GAIN focus
			//

			IDirectInputDevice7_Acquire ( direct_input_mouse );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void generate_mouse_events ( void )
{

	HRESULT
		ret;

	DWORD
		items;

	int
		count;

	if ( direct_input_mouse )
	{

		ret = IDirectInputDevice7_Acquire ( direct_input_mouse );

		if ( ( ret == DI_OK ) || ( ret == S_FALSE ) )
		{
	
			int
				dx,
				dy,
				dz;
	
			dx = 0;
	
			dy = 0;
	
			dz = 0;
	
			ret = DI_BUFFEROVERFLOW;
	
			while ( ret == DI_BUFFEROVERFLOW )
			{
	
				//
				// Get the mouse events.
				//
	
				items = MAX_DI_MOUSE_EVENTS;
	
				ret = IDirectInputDevice_GetDeviceData ( direct_input_mouse,
																			sizeof ( DIDEVICEOBJECTDATA ),
																			direct_input_mouse_events,
																			&items,
																			0 );
	
	
	//			if ( ( ret == DIERR_NOTACQUIRED ) || ( ret == DIERR_INPUTLOST ) )
	//			{
	//
	//				IDirectInputDevice_Acquire ( direct_input_mouse );
	//
	//				ret = IDirectInputDevice_GetDeviceData ( direct_input_mouse,
	//																			sizeof ( DIDEVICEOBJECTDATA ),
	//																			direct_input_mouse_events,
	//																			&items,
	//																			0 );
	//			}
	
				for ( count = 0; count < items; count++ )
				{
	
					switch ( direct_input_mouse_events[count].dwOfs )
					{
	
						case DIMOFS_BUTTON0:
						{
	
							if ( direct_input_mouse_events[count].dwData & 0x80 )
							{
			
								create_mouse_button_event ( MOUSE_LEFT_BUTTON, BUTTON_STATE_DOWN );
							}
							else
							{
			
								create_mouse_button_event ( MOUSE_LEFT_BUTTON, BUTTON_STATE_UP );
							}
	
							break;
						}
	
						case DIMOFS_BUTTON1:
						{
	
							if ( direct_input_mouse_events[count].dwData & 0x80 )
							{
			
								create_mouse_button_event ( MOUSE_RIGHT_BUTTON, BUTTON_STATE_DOWN );
							}
							else
							{
			
								create_mouse_button_event ( MOUSE_RIGHT_BUTTON, BUTTON_STATE_UP );
							}
	
							break;
						}
						
						case DIMOFS_BUTTON2: // Jabberwock 031016 Middle button
						{
	
							if ( direct_input_mouse_events[count].dwData & 0x80 )
							{
			
								create_mouse_button_event ( MOUSE_MIDDLE_BUTTON, BUTTON_STATE_DOWN );
							}
							else
							{
			
								create_mouse_button_event ( MOUSE_MIDDLE_BUTTON, BUTTON_STATE_UP );
							}
	
							break;
						}
						
	
						case DIMOFS_X:
						{
	
							dx += direct_input_mouse_events[count].dwData;
	
							break;
						}
	
						case DIMOFS_Y:
						{
	
							dy += direct_input_mouse_events[count].dwData;
	
							break;
						}

						case DIMOFS_Z:
						{
	
							dz += direct_input_mouse_events[count].dwData;
	
							break;
						}
					}
				}
			}
	
			if ( ( dx != 0 ) || ( dy != 0 ) || ( dz != 0 ) )
			{

				if ( ( abs ( dx ) > 4 ) || ( abs ( dy ) > 4 ) )
				{

					dx *= 2;

					dy *= 2;
				}


				create_mouse_move_event ( dx, dy, dz );
			}
			
			move_mouse ( dx, dy );
	
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int process_mouse_event (event *ev)
{
	int
		loop,
		modifier,
		move_horizontal_ev = 0,
		move_vertical_ev = 0,
		move_wheel_ev = 0; // Jabberwock 030930 Mouse wheel events

	int
		function_flag = FALSE;

	// JB 030311 From Gotcha (Victor Jetten)
	// Solves the problem with lack of mouse click in 2D until a keyboard key is pressed
	if ((current_modifier_states & (1 << MODIFIER_LEFT_ALT)) ||
		(current_modifier_states & (1 << MODIFIER_RIGHT_ALT)))
	{
		current_modifier_states = MODIFIER_NONE;
	}

	for (loop = MODIFIER_NONE; loop < NUM_MODIFIER_TYPES; loop ++)
	{

		if ((current_modifier_states & (1 << loop)) || ((current_modifier_states | loop) == 0) || (ev->state == BUTTON_STATE_UP))
		{

			switch (ev->type)
			{
		
				case EVENT_TYPE_MOUSE_MOVE:
				{
			
					// assign desired move function
		
					if (ev->dx < 0)
					{
		
						move_horizontal_ev = MOUSE_MOVE_LEFT;
					}
					else if (ev->dx > 0)
					{
			
						move_horizontal_ev = MOUSE_MOVE_RIGHT;
					}
			
					if (ev->dy < 0)
					{
			
						move_vertical_ev = MOUSE_MOVE_UP;
					}
					else if (ev->dy > 0)
					{
			
						move_vertical_ev = MOUSE_MOVE_DOWN;
					}
					// Jabberwock 030930 - mouse wheel events
					if (ev->dz > 0)
					{
								
						move_wheel_ev = MOUSE_WHEEL_UP;
					}
					else if (ev->dz < 0)
					{
						move_wheel_ev = MOUSE_WHEEL_DOWN;
					}
					
					// Jabberwock 030930 ends
					
	
					// horizontal move function
		
					if (move_horizontal_ev)
					{
	
						if (registered_events [move_horizontal_ev][loop].in_use)
						{
	
							if (registered_events [move_horizontal_ev][loop].function)
							{
	
								registered_events [move_horizontal_ev][loop].function (ev);
	
								function_flag = TRUE;
							}
						}
					}
		
					// vertical move function
	
					if (move_vertical_ev)
					{
	
						if (registered_events [move_vertical_ev][loop].in_use)
						{
	
							if (registered_events [move_vertical_ev][loop].function)
							{
	
								registered_events [move_vertical_ev][loop].function (ev);
	
								function_flag = TRUE;
							}
						}
					}
	
					if (move_wheel_ev)
						{
		
							if (registered_events [move_wheel_ev][loop].in_use)
							{
		
								if (registered_events [move_wheel_ev][loop].function)
								{
		
									registered_events [move_wheel_ev][loop].function (ev);
		
									function_flag = TRUE;
								}
							}
						}
	
	
					// if we've already done a function quit
	
					if (!function_flag)
					{
	
						if (registered_events [MOUSE_MOVE][loop].in_use)
						{
	
							if (registered_events [MOUSE_MOVE][loop].function)
							{
	
								registered_events [MOUSE_MOVE][loop].function (ev);
	
								function_flag = TRUE;
							}
						}
					}
	
					return function_flag;
	
					break;
				}
				
				case EVENT_TYPE_MOUSE_BUTTON:
				default:
				{

					switch (ev->button)
					{
						case MOUSE_LEFT_BUTTON:
						{
							modifier = 1 << MODIFIER_MOUSE_LEFT_BUTTON;
							
							break;
						}
						case MOUSE_RIGHT_BUTTON:
						{
							modifier = 1 << MODIFIER_MOUSE_RIGHT_BUTTON;
							
							break;
						}
						default:
						{
							break;
						}
					}
		
					if (ev->state == BUTTON_STATE_UP)
					{
		
						current_modifier_states ^= modifier;
					}
					else
					{
		
						current_modifier_states |= modifier;
					}
		
					if (registered_events [ev->button][loop].in_use)
					{
		
						if ((registered_events [ev->button][loop].notify_state == ev->state) ||
							(registered_events [ev->button][loop].notify_state == BUTTON_STATE_EITHER))
						{
			
							if (registered_events [ev->button][loop].function)
							{
			
								registered_events [ev->button][loop].function (ev);
			
								return TRUE;
							}
						}
					}
		
					break;
				}
			}
		}
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void move_mouse ( int dx, int dy )
{

	if ( mouse_on )
	{

		mouse_position_x += dx;
		mouse_position_y += dy;

		mouse_position_x = bound ( mouse_position_x, 0, (application_video_width -1) );
		mouse_position_y = bound ( mouse_position_y, 0, (application_video_height -1) );
	
	}
	

	// Retro 030317 starts
	// OK what´s happening here... I need an absolute rather than a relative mouse, so I add/dec the mouse movements
	// to two variables that have a 'hard ceiling'
	// There are 2 access methods (below) through which I can get to this data
	// There´s also a reset function to recenter the view
	// This works regardless of mouse_on or mouse_off... we might change that though..
	// EVENTS assigned to mouse buttons work ONLY when mouse is ON !

	if (get_in_flight_game_mode () == IN_FLIGHT_GAME_MODE_SIMULATOR)	// Retro 25Jul2004 - only do this while in the 3d
	{
		abs_mouse_x += (command_line_mouse_look_speed * dx);  // minimum value of dx/dy is 8, with a '10' scaling is 80.. makes 1/400 of max movement
		abs_mouse_y += (command_line_mouse_look_speed * dy);

		if (abs_mouse_x >= 16383)
			abs_mouse_x = 16383;
		else if (abs_mouse_x <= -16383)
			abs_mouse_x = -16383;

		if (abs_mouse_y >= 16383)
			abs_mouse_y = 16383;
		else if (abs_mouse_y <= -16383)
			abs_mouse_y = -16383;
	}
	// Retro 030317 ends
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_mouse_on ( void )
{

	#if MOUSE_DEBUG

	debug_log ("MOUSE: ON");

	#endif

	mouse_on = TRUE;

	set_mouse_graphic_on ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_mouse_off ( void )
{

	if (command_line_mouse_look == FALSE)	// Clause by Retro 030317, to enable mouse_events in 3d
	{
		#if MOUSE_DEBUG

		debug_log ("MOUSE: OFF");

		#endif

		// mouse_on = FALSE; Commented out by Jabberwock 030930, to enable mouse FLIR control
	}

	set_mouse_graphic_off ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_mouse_on ( void )
{

	return ( mouse_on );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_mouse_x ( void )
{

	return ( mouse_position_x );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_mouse_x ( int x )
{

	mouse_position_x = x;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_mouse_y ( void )
{

	return ( mouse_position_y );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_mouse_y ( int y )
{

	mouse_position_y = y;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_absolute_mouse_x ( void )	// Retro 030317
{

	return ( abs_mouse_x );
}
int get_absolute_mouse_y ( void )	// Retro 030317
{

	return ( abs_mouse_y );
}
void reset_absolute_mouse ( void )	// Retro 030317
{
	abs_mouse_x = abs_mouse_y = 0;
}
// Retro 31Oct2004
// pos should be >= -16383 and <= 16383 but it doesn't really matter as it is clamped
void set_absolute_mouse_x ( const int pos )
{
	abs_mouse_x = pos;
}
// Retro 31Oct2004
// pos should be >= -16383 and <= 16383 but it doesn't really matter as it is clamped
void set_absolute_mouse_y ( const int pos )
{
	abs_mouse_y = pos;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static long windows_mouse_move_routine ( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{

	POINT
		pt;

	RECT
		my_rc;

	int
		x,
		y,
		dx,
		dy;

	hWnd;
	message;
	wParam;
	lParam;

	GetCursorPos ( &pt );

	GetClientRect ( application_window, &my_rc);

	ClientToScreen ( application_window, (LPPOINT)&my_rc);

	ClientToScreen ( application_window, (LPPOINT)&my_rc+1);

	x = pt.x - my_rc.left;

	y = pt.y - my_rc.top;

	dx = x - mouse_position_x;

	dy = y - mouse_position_y;

	create_mouse_move_event ( dx, dy, 0 );

	move_mouse ( dx, dy );

	return ( 0 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static long windows_left_button_up_routine ( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{

	hWnd;
	message;
	wParam;
	lParam;

	create_mouse_button_event ( MOUSE_LEFT_BUTTON, BUTTON_STATE_UP );

	return ( 0 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static long windows_left_button_down_routine ( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{

	hWnd;
	message;
	wParam;
	lParam;

	create_mouse_button_event ( MOUSE_LEFT_BUTTON, BUTTON_STATE_DOWN );

	return ( 0 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static long windows_right_button_up_routine ( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{

	hWnd;
	message;
	wParam;
	lParam;

	create_mouse_button_event ( MOUSE_RIGHT_BUTTON, BUTTON_STATE_UP );

	return ( 0 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static long windows_right_button_down_routine ( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{

	hWnd;
	message;
	wParam;
	lParam;

	create_mouse_button_event ( MOUSE_RIGHT_BUTTON, BUTTON_STATE_DOWN );

	return ( 0 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Jabberwock 031016

static long windows_middle_button_up_routine ( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{

	hWnd;
	message;
	wParam;
	lParam;

	create_mouse_button_event ( MOUSE_MIDDLE_BUTTON, BUTTON_STATE_UP );

	return ( 0 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static long windows_middle_button_down_routine ( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{

	hWnd;
	message;
	wParam;
	lParam;

	create_mouse_button_event ( MOUSE_MIDDLE_BUTTON, BUTTON_STATE_DOWN );

	return ( 0 );
}
