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

#define JOYSTICK_AXIS_MINIMUM -10000

#define JOYSTICK_AXIS_MAXIMUM 10000

#define JOYSTICK_AXIS_DEADZONE 0.2

#define MAXIMUM_JOYSTICK_BUTTONS  128
#define MAXIMUM_JOYSTICK_AXES     32
#define MAXIMUM_JOYSTICK_HATS     32

#define JOYSTICK_DEFAULT_AXIS_ROLL 0
#define JOYSTICK_DEFAULT_AXIS_PITCH 1
#define JOYSTICK_DEFAULT_AXIS_YAW 5
#define JOYSTICK_DEFAULT_AXIS_THROTTLE 2

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// To read the joystick data structure, use the microsoft defined structure joystick_state ( structure DIJOYSTATE )
//
// It is:
//
// struct DIJOYSTATE
// {
//
//    LONG    lX;
//    LONG    lY;
//    LONG    lZ;
//    LONG    lRx;
//    LONG    lRy;
//    LONG    lRz;
//    LONG    rglSlider[2];
//    DWORD   rgdwPOV[4];
//    BYTE    rgbButtons[32];
// }
//

#ifndef WIN32
typedef struct {
	Uint8 buttons[ MAXIMUM_JOYSTICK_BUTTONS ];
	Sint16 axes[ MAXIMUM_JOYSTICK_AXES ];
	Uint8 hats [MAXIMUM_JOYSTICK_HATS ];
} SDLJOYSTATE;
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum JOYSTICK_HAT_POSITION
{
	HAT_CENTERED,
	HAT_UP,
	HAT_RIGHT,
	HAT_DOWN,
	HAT_LEFT,
	HAT_RIGHTUP,
	HAT_RIGHTDOWN,
	HAT_LEFTUP,
	HAT_LEFTDOWN
};

typedef enum JOYSTICK_HAT_POSITION joystick_hat_position;
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct JOYSTICK_DEVICE_INFO
{

#ifdef WIN32

	LPDIRECTINPUTDEVICE7
		input_device;

	LPDIRECTINPUTEFFECT
		input_effect;

	unsigned int
		joystick_xaxis_valid:1,
		joystick_yaxis_valid:1,
		joystick_zaxis_valid:1,
		joystick_rxaxis_valid:1,
		joystick_ryaxis_valid:1,
		joystick_rzaxis_valid:1,
		joystick_slider0axis_valid:1,
		joystick_slider1axis_valid:1,
		joystick_supports_force_feedback:1,
		joystick_has_pov:1;

	int
		number_of_buttons;

	DIJOYSTATE
		joystick_last_state,
		joystick_state;

#else

	SDL_Joystick
		*input_device;

	int
		number_of_buttons,
		number_of_axes,
		number_of_hats;

	SDLJOYSTATE
		joystick_last_state,
		joystick_state;

#endif

	char
		device_name[1024];

	char
		device_product_name[1024];
};

typedef struct JOYSTICK_DEVICE_INFO joystick_device_info;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void initialise_joysticks ( void );

extern void read_joystick_values ( int joystick_device_index );

extern int set_joystick_force_feedback_forces ( int joystick_device_index, int xforce, int yforce );

extern int get_joystick_axis (int joystick_index, int axis);

extern joystick_hat_position get_joystick_hat (joystick_device_info *stick, int index);

extern int get_joystick_button(joystick_device_info *stick, int index);

extern void GetGUIDString(const int iDevice, char* theString);	// Retro 28Aug2004

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern int
	number_of_joystick_devices;

extern joystick_device_info
	*joystick_devices;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Retro 10Jul2004 start
typedef struct {
	char* AxisName;
	int device;
	int axis;
	int inUse;
} AxisInfo_t;

extern AxisInfo_t AxisInfo[16*8];
extern int AxisCount;
// Retro 10Jul2004 end
