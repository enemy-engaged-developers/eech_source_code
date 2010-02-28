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

#include "system.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_KEYS 256

#define MAX_DI_KEY_EVENTS 256

#define KEYBOARD_BUFFER_SIZE 256

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static unsigned char
	key_states[MAX_KEYS];

static LPDIRECTINPUTDEVICE7
	direct_input_keyboard = NULL;

static DIDEVICEOBJECTDATA
	direct_input_key_events[MAX_DI_KEY_EVENTS];

static int translate_windows_virtual_key_code_to_directinput ( int virtual_, int lparam );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HANDLE
	keyboard_handle = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void keyboard_activation_routine ( int activate );

static long windows_key_up_routine ( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

static long windows_key_down_routine ( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_keyboard ( void )
{

	HRESULT
		ret;

	DIPROPDWORD
		di_buffer_data;

	if ( input_system_type == INPUT_DIRECTINPUT )
	{

		ret = IDirectInput7_CreateDeviceEx ( direct_input, GUID_PREFIX GUID_SysKeyboard, GUID_PREFIX IID_IDirectInputDevice7, (LPVOID *) &direct_input_keyboard, NULL );

		if (ret != DI_OK )
		{

			return;
		}

		ret = IDirectInputDevice7_SetDataFormat ( direct_input_keyboard, &c_dfDIKeyboard );

		if ( ret != DI_OK )
		{

			return;
		}

		ret = IDirectInputDevice7_SetCooperativeLevel ( direct_input_keyboard, application_window, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );

		if ( ret != DI_OK )
		{

			return;
		}

		keyboard_handle = CreateEvent ( 0, 0, 0, 0 );

		if ( keyboard_handle == NULL )
		{

			debug_fatal ( "Unable to create a handle for the keyboard" );
		}

		ret = IDirectInputDevice7_SetEventNotification ( direct_input_keyboard, keyboard_handle );

		if ( ret != DI_OK )
		{

			debug_fatal ( "Unable to set event notification for the keyboard" );
		}

		//
		// Set the hardware buffering of the keyboard
		//

		di_buffer_data.diph.dwSize = sizeof ( DIPROPDWORD );
		di_buffer_data.diph.dwHeaderSize = sizeof ( DIPROPHEADER );
		di_buffer_data.diph.dwObj = 0;
		di_buffer_data.diph.dwHow = DIPH_DEVICE;
		di_buffer_data.dwData = KEYBOARD_BUFFER_SIZE;

		ret = IDirectInputDevice7_SetProperty ( direct_input_keyboard, DIPROP_BUFFERSIZE, &di_buffer_data.diph );

		if ( ret != DI_OK )
		{

			debug_fatal ( "Unable to set the keyboard buffer size" );
		}

		register_pre_activate_message_function ( keyboard_activation_routine );

		IDirectInputDevice7_Acquire ( direct_input_keyboard );

		IDirectInputDevice7_GetDeviceState ( direct_input_keyboard, 256, key_states );

	}
	else
	{

		//
		// Assumes the only other input system is windows
		//

		register_system_message_function ( WM_KEYUP, windows_key_up_routine );
		register_system_message_function ( WM_SYSKEYUP, windows_key_up_routine );
		register_system_message_function ( WM_KEYDOWN, windows_key_down_routine );
		register_system_message_function ( WM_SYSKEYDOWN, windows_key_down_routine );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_keyboard ( void )
{

	if ( direct_input_keyboard )
	{

		IDirectInputDevice7_Unacquire ( direct_input_keyboard );

		IDirectInputDevice7_Release ( direct_input_keyboard );

		CloseHandle ( keyboard_handle );

		keyboard_handle = NULL;

		direct_input_keyboard = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void keyboard_activation_routine ( int activate )
{

	HRESULT
		ret;

	if ( direct_input_keyboard )
	{

		if ( !activate )
		{

			//
			// About the LOSE focus
			//

			debug_log ( "Unacquiring keyboard" );

			IDirectInputDevice7_Unacquire ( direct_input_keyboard );
		}
		else
		{

			//
			// About to GAIN focus
			//

			debug_log ( "Acquiring keyboard" );

			ret = IDirectInputDevice7_Acquire ( direct_input_keyboard );

			if ( ret != DI_OK )
			{

				debug_log ( "Failed to acquire keyboard device" );
			}

			SetFocus ( application_window );

			//
			// Reset the events
			//

			reset_events ();

	//		SetEvent ( keyboard_handle );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void generate_keyboard_events ( void )
{

	HRESULT
		ret;

	DWORD
		items;

	unsigned int
		count;

	if ( direct_input_keyboard )
	{

		ret = IDirectInputDevice7_Acquire ( direct_input_keyboard );

		if ( ( ret == DI_OK ) || ( ret == S_FALSE ) )
		{

			ret = DI_BUFFEROVERFLOW;

			while ( ret == DI_BUFFEROVERFLOW )
			{

				//
				// Get the keyboard events.
				//

				items = MAX_DI_KEY_EVENTS;

				ret = IDirectInputDevice7_GetDeviceData ( direct_input_keyboard,
																			sizeof ( DIDEVICEOBJECTDATA ),
																			direct_input_key_events,
																			&items,
																			0 );

				for ( count = 0; count < items; count++ )
				{

					if ( direct_input_key_events[count].dwData & 0x80 )	// & DIDFT_BUTTON )
					{

						create_key_event ( direct_input_key_events[count].dwOfs, KEY_STATE_DOWN );
					}
					else
					{

						create_key_event ( direct_input_key_events[count].dwOfs, KEY_STATE_UP );
					}
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static long windows_key_up_routine ( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{

	int
		key;

	hWnd;
	message;
	wParam;

	key = translate_windows_virtual_key_code_to_directinput ( wParam, lParam );

	key_states[key] = FALSE;

	create_key_event ( key, KEY_STATE_UP );

	return ( 0 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static long windows_key_down_routine ( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{

	int
		key;

	hWnd;
	message;
	wParam;

	key = translate_windows_virtual_key_code_to_directinput ( wParam, lParam );

	key_states[key] = TRUE;

	create_key_event ( key, KEY_STATE_DOWN );

	return ( 0 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL check_key ( const SHORT key )
{

	HRESULT
		ret;

	if ( direct_input_keyboard )
	{

		IDirectInputDevice7_Acquire ( direct_input_keyboard );

		//
		// Ignore return code here
		//

		ret = IDirectInputDevice7_GetDeviceState ( direct_input_keyboard, 256, key_states );

		if ( ret != DI_OK )
		{

			return ( FALSE );
		}
	}
	else
	{


	}

	if ( key_states[key] )
	{

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

int wait_for_any_key ( void )
{

	event
		ev;

	while ( TRUE )
	{

		if ( get_event ( &ev ) )
		{

			if ( ev.type == EVENT_TYPE_KEY )
			{

				if ( ev.state == KEY_STATE_DOWN )
				{

					break;
				}
			}
		}
	}

	return ( ev.key );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int wait_for_key ( const int key )
{

	event
		ev;

	while ( TRUE )
	{

		if ( get_event ( &ev ) )
		{

			if ( ev.type == EVENT_TYPE_KEY )
			{

				if ( ( ev.key == key ) && ( ev.state == KEY_STATE_DOWN ) )
				{

					break;
				}
			}
		}
	}

	return ( ev.key );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int check_for_any_key ( void )
{

	event
		ev;

	if ( get_event ( &ev ) )
	{
		if ( ev.type == EVENT_TYPE_KEY )
		{
			if ( ev.state == KEY_STATE_DOWN )
			{

				return ( ev.key );
			}
		}
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define	VK_A		0x41
#define	VK_B		0x42
#define	VK_C		0x43
#define	VK_D		0x44
#define	VK_E		0x45
#define	VK_F		0x46
#define	VK_G		0x47
#define	VK_H		0x48
#define	VK_I		0x49
#define	VK_J		0x4a
#define	VK_K		0x4b
#define	VK_L		0x4c
#define	VK_M		0x4d
#define	VK_N		0x4e
#define	VK_O		0x4f
#define	VK_P		0x50
#define	VK_Q		0x51
#define	VK_R		0x52
#define	VK_S		0x53
#define	VK_T		0x54
#define	VK_U		0x55
#define	VK_V		0x56
#define	VK_W		0x57
#define	VK_X		0x58
#define	VK_Y		0x59
#define	VK_Z		0x5a

#define	VK_0		0x30
#define	VK_1		0x31
#define	VK_2		0x32
#define	VK_3		0x33
#define	VK_4		0x34
#define	VK_5		0x35
#define	VK_6		0x36
#define	VK_7		0x37
#define	VK_8		0x38
#define	VK_9		0x39

#define	VK_LSQBRACKET	0xdb
#define	VK_RSQBRACKET	0xdd

#define	VK_COMMA			0xbc
#define	VK_STOP			0xbe

#define	VK_MINUS		0xbd
#define	VK_EQUALS	0xbb

int translate_windows_virtual_key_code_to_directinput ( int virtual_, int lparam )
{

	int
		code,
		code2;

	code = ( ( lparam >> 16 ) & 0xff );
	code2 = ( ( lparam >> 16 ) & 0xfff );

	switch ( virtual_ )
	{

		case	VK_SHIFT:
		{

			if ( code == 0x2a )	return ( DIK_LSHIFT );
			else 						return ( DIK_RSHIFT );

			break;
		}

		case	VK_CONTROL:
		{

			if ( code2 == 0x1d ) return ( DIK_LCONTROL );
			else						return ( DIK_RCONTROL );

			break;
		}
		case	VK_MENU:
		{

			if ( code2 == 0x38 )	return ( DIK_LMENU );
			else						return ( DIK_RMENU );

			break;
		}

		case	VK_BACK:				return ( DIK_BACK );	break;
		case	VK_TAB:				return ( DIK_TAB );	break;
		case	VK_RETURN:			return ( DIK_RETURN );	break;
		case	VK_CAPITAL:			return ( DIK_CAPITAL );	break;
		case	VK_ESCAPE:			return ( DIK_ESCAPE );	break;
		case	VK_SPACE:			return ( DIK_SPACE );	break;
		case	VK_PRIOR:			return ( DIK_PRIOR );	break;
		case	VK_NEXT:				return ( DIK_NEXT );	break;
		case	VK_END:				return ( DIK_END );	break;
		case	VK_HOME:				return ( DIK_HOME );	break;
		case	VK_LEFT:				return ( DIK_LEFT );	break;
		case	VK_UP:				return ( DIK_UP );	break;
		case	VK_RIGHT:			return ( DIK_RIGHT );	break;
		case	VK_DOWN:				return ( DIK_DOWN );	break;
		case	VK_INSERT:			return ( DIK_INSERT );	break;
		case	VK_DELETE:			return ( DIK_DELETE );	break;

		case	VK_NUMPAD0:			return ( DIK_NUMPAD0 );	break;
		case	VK_NUMPAD1:			return ( DIK_NUMPAD1 );	break;
		case	VK_NUMPAD2:			return ( DIK_NUMPAD2 );	break;
		case	VK_NUMPAD3:			return ( DIK_NUMPAD3 );	break;
		case	VK_NUMPAD4:			return ( DIK_NUMPAD4 );	break;
		case	VK_NUMPAD5:			return ( DIK_NUMPAD5 );	break;
		case	VK_NUMPAD6:			return ( DIK_NUMPAD6 );	break;
		case	VK_NUMPAD7:			return ( DIK_NUMPAD7 );	break;
		case	VK_NUMPAD8:			return ( DIK_NUMPAD8 );	break;
		case	VK_NUMPAD9:			return ( DIK_NUMPAD9 );	break;

		case	VK_MULTIPLY:		return ( DIK_MULTIPLY );	break;
		case	VK_ADD:				return ( DIK_ADD );	break;
		case	VK_SUBTRACT:		return ( DIK_SUBTRACT );	break;
		case	VK_DECIMAL:			return ( DIK_DECIMAL );	break;
		case	VK_DIVIDE:			return ( DIK_DIVIDE );	break;

		case	VK_F1:				return ( DIK_F1 );	break;
		case	VK_F2:				return ( DIK_F2 );	break;
		case	VK_F3:				return ( DIK_F3 );	break;
		case	VK_F4:				return ( DIK_F4 );	break;
		case	VK_F5:				return ( DIK_F5 );	break;
		case	VK_F6:				return ( DIK_F6 );	break;
		case	VK_F7:				return ( DIK_F7 );	break;
		case	VK_F8:				return ( DIK_F8 );	break;
		case	VK_F9:				return ( DIK_F9 );	break;
		case	VK_F10:				return ( DIK_F10 );	break;
		case	VK_F11:				return ( DIK_F11 );	break;
		case	VK_F12:				return ( DIK_F12 );	break;
		case	VK_F13:				return ( DIK_F13 );	break;
		case	VK_F14:				return ( DIK_F14 );	break;
		case	VK_F15:				return ( DIK_F15 );	break;

		case	VK_A:					return ( DIK_A ); break;
		case	VK_B:					return ( DIK_B ); break;
		case	VK_C:					return ( DIK_C ); break;
		case	VK_D:					return ( DIK_D ); break;
		case	VK_E:					return ( DIK_E ); break;
		case	VK_F:					return ( DIK_F ); break;
		case	VK_G:					return ( DIK_G ); break;
		case	VK_H:					return ( DIK_H ); break;
		case	VK_I:					return ( DIK_I ); break;
		case	VK_J:					return ( DIK_J ); break;
		case	VK_K:					return ( DIK_K ); break;
		case	VK_L:					return ( DIK_L ); break;
		case	VK_M:					return ( DIK_M ); break;
		case	VK_N:					return ( DIK_N ); break;
		case	VK_O:					return ( DIK_O ); break;
		case	VK_P:					return ( DIK_P ); break;
		case	VK_Q:					return ( DIK_Q ); break;
		case	VK_R:					return ( DIK_R ); break;
		case	VK_S:					return ( DIK_S ); break;
		case	VK_T:					return ( DIK_T ); break;
		case	VK_U:					return ( DIK_U ); break;
		case	VK_V:					return ( DIK_V ); break;
		case	VK_W:					return ( DIK_W ); break;
		case	VK_X:					return ( DIK_X ); break;
		case	VK_Y:					return ( DIK_Y ); break;
		case	VK_Z:					return ( DIK_Z ); break;

		case	VK_0:					return ( DIK_0 ); break;
		case	VK_1:					return ( DIK_1 ); break;
		case	VK_2:					return ( DIK_2 ); break;
		case	VK_3:					return ( DIK_3 ); break;
		case	VK_4:					return ( DIK_4 ); break;
		case	VK_5:					return ( DIK_5 ); break;
		case	VK_6:					return ( DIK_6 ); break;
		case	VK_7:					return ( DIK_7 ); break;
		case	VK_8:					return ( DIK_8 ); break;
		case	VK_9:					return ( DIK_9 ); break;

		case	VK_NUMLOCK:			return ( DIK_NUMLOCK );	break;
		case	VK_SCROLL:			return ( DIK_SCROLL );	break;

		case	VK_LSHIFT:			return ( DIK_LSHIFT );	break;
		case	VK_RSHIFT:			return ( DIK_RSHIFT );	break;
		case	VK_LCONTROL:		return ( DIK_LCONTROL );	break;
		case	VK_RCONTROL:		return ( DIK_RCONTROL );	break;
		case	VK_LMENU:			return ( DIK_LMENU );	break;
		case	VK_RMENU:			return ( DIK_RMENU );	break;

		case	VK_LSQBRACKET:		return ( DIK_LBRACKET );	break;
		case	VK_RSQBRACKET:		return ( DIK_RBRACKET );	break;

		case	VK_COMMA:			return ( DIK_COMMA ); break;
		case	VK_STOP:				return ( DIK_PERIOD ); break;

		case	VK_MINUS:			return ( DIK_MINUS ); break;
		case	VK_EQUALS:			return ( DIK_EQUALS ); break;

		case	VK_SEPARATOR:		return ( 0x00 );	break;
		case	VK_PROCESSKEY:		return ( 0x00 );	break;
		case	VK_ATTN:				return ( 0x00 );	break;
		case	VK_CRSEL:			return ( 0x00 );	break;
		case	VK_EXSEL:			return ( 0x00 );	break;
		case	VK_EREOF:			return ( 0x00 );	break;
		case	VK_PLAY:				return ( 0x00 );	break;
		case	VK_ZOOM:				return ( 0x00 );	break;
		case	VK_NONAME:			return ( 0x00 );	break;
		case	VK_PA1:				return ( 0x00 );	break;
		case	VK_OEM_CLEAR:		return ( 0x00 );	break;
		case	VK_LBUTTON:			return ( 0x00 );	break;
		case	VK_RBUTTON:			return ( 0x00 );	break;
		case	VK_CANCEL:			return ( 0x00 );	break;
		case	VK_MBUTTON:			return ( 0x00 );	break;
		case	VK_CLEAR:			return ( 0x00 );	break;
		case	VK_SELECT:			return ( 0x00 );	break;
		case	VK_PRINT:			return ( 0x00 );	break;
		case	VK_EXECUTE:			return ( 0x00 );	break;
		case	VK_SNAPSHOT:		return ( 0x00 );	break;
		case	VK_HELP:				return ( 0x00 );	break;
		case	VK_LWIN:				return ( 0x00 );	break;
		case	VK_RWIN:				return ( 0x00 );	break;
		case	VK_APPS:				return ( 0x00 );	break;
		case	VK_PAUSE:			return ( 0x00 );	break;
	}

	return ( 0 );
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

