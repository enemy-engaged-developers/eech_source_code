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

static int translate_windows_virtual_key_code_to_directinput ( int virtual, int modifiers );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void keyboard_activation_routine ( int activate );

static long windows_key_up_routine ( void *);

static long windows_key_down_routine ( void *);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_keyboard ( void )
{

	register_system_message_function ( SDL_KEYUP, windows_key_up_routine );
	register_system_message_function ( SDL_KEYDOWN, windows_key_down_routine );

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_keyboard ( void )
{

	//do nothing(?)

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void keyboard_activation_routine ( int activate )
{
/*
* Aquering focus and the like is handled by SDL
*/

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void generate_keyboard_events ( const SDL_KeyboardEvent *kb )
{
	unsigned int
		keyState;

	keyState = (SDL_KEYDOWN == kb->type) ? SDL_PRESSED : SDL_RELEASED ;

	create_key_event /* int key, enum KEY_STATES state */
		(
		translate_windows_virtual_key_code_to_directinput( kb->keysym.sym, kb->keysym.mod ),
		keyState
		);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static long windows_key_up_routine ( void *data)
{
	int
		key;
		
	const SDL_KeyboardEvent
		*kb = data;

	key = translate_windows_virtual_key_code_to_directinput ( kb->keysym.sym, kb->keysym.mod );

	key_states[key] = FALSE;

	create_key_event ( key, SDL_KEYUP );

	return ( 0 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static long windows_key_down_routine ( void *data)
{
	int
		key;

	const SDL_KeyboardEvent
		*kb = data;

	key = translate_windows_virtual_key_code_to_directinput ( kb->keysym.sym, kb->keysym.mod );

	key_states[key] = TRUE;

	create_key_event ( key, SDL_KEYDOWN );

	return ( 0 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL check_key ( const SHORT key )
{

	return ( key_states[key] );

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
	return 0;
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
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int translate_windows_virtual_key_code_to_directinput ( int virtual, int modifiers )
{

	int
		code,
		code2;

	code = ( ( modifiers >> 16 ) & 0xff );
	code2 = ( ( modifiers >> 16 ) & 0xfff );

	switch ( virtual )
	{

		case	SDLK_LSHIFT:	return ( DIK_LSHIFT );	break;
		case	SDLK_RSHIFT:	return ( DIK_RSHIFT );	break;
		case	SDLK_LCTRL:	return ( DIK_LCONTROL );	break;
		case	SDLK_RCTRL:	return ( DIK_RCONTROL );	break;
		/* According to system.h DIK_LMENU is left Alt */
		case	SDLK_LALT:	return ( DIK_LMENU );	break;
		case	SDLK_RALT:	return ( DIK_RMENU );	break;

		case	SDLK_BACKSPACE:				return ( DIK_BACK );	break;
		case	SDLK_TAB:				return ( DIK_TAB );	break;
		case	SDLK_RETURN:			return ( DIK_RETURN );	break;

	// I don't know the SDL eqvivalent
	//	case	SDLK_CAPITAL:			return ( DIK_CAPITAL );	break;

		case	SDLK_ESCAPE:			return ( DIK_ESCAPE );	break;
		case	SDLK_SPACE:			return ( DIK_SPACE );	break;
		case	SDLK_PAGEUP:			return ( DIK_PRIOR );	break;
		case	SDLK_PAGEDOWN:				return ( DIK_NEXT );	break;
		case	SDLK_END:				return ( DIK_END );	break;
		case	SDLK_HOME:				return ( DIK_HOME );	break;
		case	SDLK_LEFT:				return ( DIK_LEFT );	break;
		case	SDLK_UP:				return ( DIK_UP );	break;
		case	SDLK_RIGHT:			return ( DIK_RIGHT );	break;
		case	SDLK_DOWN:				return ( DIK_DOWN );	break;
		case	SDLK_INSERT:			return ( DIK_INSERT );	break;
		case	SDLK_DELETE:			return ( DIK_DELETE );	break;

		case	SDLK_KP0:			return ( DIK_NUMPAD0 );	break;
		case	SDLK_KP1:			return ( DIK_NUMPAD1 );	break;
		case	SDLK_KP2:			return ( DIK_NUMPAD2 );	break;
		case	SDLK_KP3:			return ( DIK_NUMPAD3 );	break;
		case	SDLK_KP4:			return ( DIK_NUMPAD4 );	break;
		case	SDLK_KP5:			return ( DIK_NUMPAD5 );	break;
		case	SDLK_KP6:			return ( DIK_NUMPAD6 );	break;
		case	SDLK_KP7:			return ( DIK_NUMPAD7 );	break;
		case	SDLK_KP8:			return ( DIK_NUMPAD8 );	break;
		case	SDLK_KP9:			return ( DIK_NUMPAD9 );	break;

		case	SDLK_KP_MULTIPLY:		return ( DIK_MULTIPLY );	break;
		case	SDLK_KP_PLUS:				return ( DIK_ADD );	break;
		case	SDLK_KP_MINUS:		return ( DIK_SUBTRACT );	break;
		case	SDLK_KP_PERIOD:			return ( DIK_DECIMAL );	break;
		case	SDLK_KP_DIVIDE:			return ( DIK_DIVIDE );	break;

		case	SDLK_F1:				return ( DIK_F1 );	break;
		case	SDLK_F2:				return ( DIK_F2 );	break;
		case	SDLK_F3:				return ( DIK_F3 );	break;
		case	SDLK_F4:				return ( DIK_F4 );	break;
		case	SDLK_F5:				return ( DIK_F5 );	break;
		case	SDLK_F6:				return ( DIK_F6 );	break;
		case	SDLK_F7:				return ( DIK_F7 );	break;
		case	SDLK_F8:				return ( DIK_F8 );	break;
		case	SDLK_F9:				return ( DIK_F9 );	break;
		case	SDLK_F10:				return ( DIK_F10 );	break;
		case	SDLK_F11:				return ( DIK_F11 );	break;
		case	SDLK_F12:				return ( DIK_F12 );	break;
		case	SDLK_F13:				return ( DIK_F13 );	break;
		case	SDLK_F14:				return ( DIK_F14 );	break;
		case	SDLK_F15:				return ( DIK_F15 );	break;

		case	SDLK_a:					return ( DIK_A ); break;
		case	SDLK_b:					return ( DIK_B ); break;
		case	SDLK_c:					return ( DIK_C ); break;
		case	SDLK_d:					return ( DIK_D ); break;
		case	SDLK_e:					return ( DIK_E ); break;
		case	SDLK_f:					return ( DIK_F ); break;
		case	SDLK_g:					return ( DIK_G ); break;
		case	SDLK_h:					return ( DIK_H ); break;
		case	SDLK_i:					return ( DIK_I ); break;
		case	SDLK_j:					return ( DIK_J ); break;
		case	SDLK_k:					return ( DIK_K ); break;
		case	SDLK_l:					return ( DIK_L ); break;
		case	SDLK_m:					return ( DIK_M ); break;
		case	SDLK_n:					return ( DIK_N ); break;
		case	SDLK_o:					return ( DIK_O ); break;
		case	SDLK_p:					return ( DIK_P ); break;
		case	SDLK_q:					return ( DIK_Q ); break;
		case	SDLK_r:					return ( DIK_R ); break;
		case	SDLK_s:					return ( DIK_S ); break;
		case	SDLK_t:					return ( DIK_T ); break;
		case	SDLK_u:					return ( DIK_U ); break;
		case	SDLK_v:					return ( DIK_V ); break;
		case	SDLK_w:					return ( DIK_W ); break;
		case	SDLK_x:					return ( DIK_X ); break;
		case	SDLK_y:					return ( DIK_Y ); break;
		case	SDLK_z:					return ( DIK_Z ); break;

		case	SDLK_0:					return ( DIK_0 ); break;
		case	SDLK_1:					return ( DIK_1 ); break;
		case	SDLK_2:					return ( DIK_2 ); break;
		case	SDLK_3:					return ( DIK_3 ); break;
		case	SDLK_4:					return ( DIK_4 ); break;
		case	SDLK_5:					return ( DIK_5 ); break;
		case	SDLK_6:					return ( DIK_6 ); break;
		case	SDLK_7:					return ( DIK_7 ); break;
		case	SDLK_8:					return ( DIK_8 ); break;
		case	SDLK_9:					return ( DIK_9 ); break;

		case	SDLK_NUMLOCK:			return ( DIK_NUMLOCK );	break;
		case	SDLK_SCROLLOCK:			return ( DIK_SCROLL );	break;

		case	SDLK_LEFTBRACKET:		return ( DIK_LBRACKET );	break;
		case	SDLK_RIGHTBRACKET:		return ( DIK_RBRACKET );	break;

		case	SDLK_COMMA:			return ( DIK_COMMA ); break;
		case	SDLK_PERIOD:				return ( DIK_PERIOD ); break;

		case	SDLK_MINUS:			return ( DIK_MINUS ); break;
		case	SDLK_EQUALS:			return ( DIK_EQUALS ); break;

		case	SDLK_SYSREQ:		return ( DIK_SYSRQ );	break;
		/* Left windows key */
		case	SDLK_LSUPER:		return ( DIK_LWIN );	break;
		case	SDLK_RSUPER:		return ( DIK_RWIN );	break;

		/* There are of cource more SDL buttons (and DIK buttons) defined */
		
		/* Alt Gr according to SDL */
		case	SDLK_MODE:		return ( 0x00 );	break;
		case	SDLK_PAUSE:			return ( DIK_PAUSE );	break;
	}

	return ( 0 );
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

