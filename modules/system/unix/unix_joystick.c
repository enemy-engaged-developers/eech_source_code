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

#include "maths.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE	0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAXIMUM_JOYSTICK_DEVICES 16

#define NUMBER_OF_FORCE_FEEDBACK_AXES 2

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	number_of_joystick_devices;

joystick_device_info
	*joystick_devices = nullptr;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int setup_sdl_joysticks( void );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_joysticks (void)
{

	if ( !SDL_WasInit(SDL_INIT_JOYSTICK) )
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);

	//
	// Allocate joystick device array
	//

	joystick_devices = safe_malloc (sizeof (joystick_device_info) * MAXIMUM_JOYSTICK_DEVICES);

	//
	// First, enumerate all the joysticks that are available
	//

	number_of_joystick_devices = 0;

	if( setup_sdl_joysticks() != 0 ) {
		debug_log ("No joystick devices found");
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int setup_sdl_joysticks( void ) {

	int
		i, j, n;

	int
		number_of_joysticks_detected;

	number_of_joysticks_detected = SDL_NumJoysticks();

	if(number_of_joysticks_detected < 1)
		return -1;

	n = 0;

	for(i = 0; i < number_of_joysticks_detected; i++) {

		joystick_devices[ n ].input_device = SDL_JoystickOpen( i );

		if( joystick_devices[ n ].input_device ) {

			joystick_devices[ n ].number_of_buttons = SDL_JoystickNumButtons( joystick_devices[ n ].input_device );
			joystick_devices[ n ].number_of_axes = SDL_JoystickNumAxes( joystick_devices[ n ].input_device );
			joystick_devices[ n ].number_of_hats = SDL_JoystickNumHats( joystick_devices[ n ].input_device );
			
			for(j = 0; j < joystick_devices[ n ].number_of_buttons; j++) {
				joystick_devices[ n ].joystick_last_state.buttons[ j ] = SDL_JoystickGetButton( joystick_devices[ n ].input_device, j );
			}

			for(j = 0; j < joystick_devices[ n ].number_of_axes; j++) {
				joystick_devices[ n ].joystick_last_state.axes[ j ] = SDL_JoystickGetAxis( joystick_devices[ n ].input_device, j );
			}

			for(j = 0; j < joystick_devices[ n ].number_of_hats; j++) {
				joystick_devices[ n ].joystick_last_state.hats[ j ] = SDL_JoystickGetHat( joystick_devices[ n ].input_device, j );
			}
		
			strncpy( joystick_devices[ n ].device_name, SDL_JoystickName( i ), 1023 );
			
			strcpy( joystick_devices[ n ].device_product_name, "Unknown" );

#if DEBUG_MODULE

			debug_log ("Got joystick device %s (SDL device %d, Game device %d)", joystick_devices[ n ].device_name, i, n);

#endif

			n++;
		}
		else {
			debug_log("Unable to open joystick device %d, skipped.", i);
		}
	}

	number_of_joystick_devices = n;

	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void read_joystick_values (int joystick_device_index)
{

	int
		i;

	joystick_device_info
		*joystick = nullptr;

	int
		button_count;

	if ((joystick_device_index >= 0) && (joystick_device_index < number_of_joystick_devices))
	{
	
		joystick = &joystick_devices[joystick_device_index];
	
		//
		// Read the joystick values
		//
	
		if ((joystick) && (joystick->input_device))
		{
		
			//
			// Copy the current values to the last values
			//
		
			joystick->joystick_last_state = joystick->joystick_state;
		
			//
			// Now, poll the device
			//
		
		
			//
			// Read the state
			//
		
			for(i = 0; i < joystick->number_of_buttons; i++)
				joystick->joystick_state.buttons[ i ] = SDL_JoystickGetButton(joystick->input_device, i);

			for(i = 0; i < joystick->number_of_axes; i++)
				joystick->joystick_state.axes[ i ] = SDL_JoystickGetAxis(joystick->input_device, i);

			for(i = 0; i < joystick->number_of_buttons; i++)
				joystick->joystick_state.hats[ i ] = SDL_JoystickGetHat(joystick->input_device, i);

			//
			// Generate any button events
			//
		
			for (button_count = 0; button_count < joystick->number_of_buttons; button_count++)
			{
		
				if (joystick->joystick_last_state.buttons[button_count] != joystick->joystick_state.buttons[button_count])
				{
		
					if (joystick->joystick_state.buttons[button_count] == 1)
					{
		
						//
						// Generate a button pressed event
						//
		
						create_joystick_event (joystick_device_index, button_count, BUTTON_STATE_DOWN);
					}
					else
					{
		
						//
						// Generate a button released event
						//
		
						create_joystick_event (joystick_device_index, button_count, BUTTON_STATE_UP);
					}
				}
			}

		}


		//
		// Values are in here!
		//
	
#if DEBUG_MODULE
	
		if (joystick->joystick_xaxis_valid) debug_log ("Joystick Xaxis: %d", joystick->joystick_state.lX);
		if (joystick->joystick_yaxis_valid) debug_log ("Joystick Yaxis: %d", joystick->joystick_state.lY);
		if (joystick->joystick_zaxis_valid) debug_log ("Joystick Zaxis: %d", joystick->joystick_state.lZ);
		if (joystick->joystick_rxaxis_valid) debug_log ("Joystick RXaxis: %d", joystick->joystick_state.lRx);
		if (joystick->joystick_ryaxis_valid) debug_log ("Joystick RYaxis: %d", joystick->joystick_state.lRy);
		if (joystick->joystick_rzaxis_valid) debug_log ("Joystick RZaxis: %d", joystick->joystick_state.lRz);
	
#endif
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int set_joystick_force_feedback_forces (int joystick_device_index, int xforce, int yforce)
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// loke 030319
// this function returns the value of a joystick axis
// yem 030525 - changed axis to be indexed from 0 instead of 1. renamed to get_joystick_axis.
int get_joystick_axis (int joystick_index, int axis)
{
	read_joystick_values(joystick_index); // Jabberwock 031120 Some joystick values were not read at all!

	if( joystick_index >= 0 && joystick_index < number_of_joystick_devices
		  && axis >= 0 && axis < joystick_devices[joystick_index].number_of_axes ) {

		return joystick_devices[joystick_index].joystick_state.axes[ axis ];
	}
	
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Added 2003-05-25 (yem) Use this function instead of referencing DIJOYSTATE.rgdwPOV[] directly
joystick_hat_position get_joystick_hat(joystick_device_info *stick, int index) {
	// TODO: Add support for diagonal directions

	Uint8
		pos;

	if( index >= 0 && index < stick->number_of_hats ) {
		pos = stick->joystick_state.hats[ index ];

		switch( pos ) {
		case SDL_HAT_UP:
			return HAT_UP;
		case SDL_HAT_LEFT:
			return HAT_LEFT;
		case SDL_HAT_DOWN:
			return HAT_DOWN;
		case SDL_HAT_RIGHT:
			return HAT_RIGHT;
		default:
		case SDL_HAT_CENTERED:
			return HAT_CENTERED;
		}			
	}

	return HAT_CENTERED;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Added 2003-05-25 (yem) Use this function instead of referencing DIJOYSTATE.rgbButtons[] directly
int get_joystick_button(joystick_device_info *stick, int index) {

#ifdef WIN32

	if( index >= 0 && index < 32 )
		return stick->joystick_state.rgbButtons[ index ];

#else

	if( index >= 0 && index < stick->number_of_buttons )
		return stick->joystick_state.buttons[ index ];

#endif

	else
		return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
