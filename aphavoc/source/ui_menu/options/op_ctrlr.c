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

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ui_object
	*controller_area,
	*controller_text_area;

ui_object
	*cyclic_area,
	*cyclic_y_area,		// Retro 10Jul2004
	*collective_area,
	*pedal_area,
//Retro10Jul2004_dead	*device_area,
	*reverse_throttle_area,
	*keyboard_assist_area,
	*eo_pan_x_area,		// Retro 10Jul2004
	*eo_pan_y_area,		// Retro 10Jul2004
	*eo_zoom_area,		// Retro 10Jul2004
	*joylook_x_area,	// Retro 10Jul2004
	*joylook_y_area,	// Retro 10Jul2004
	*mouselook_area,	// Retro 10Jul2004
	*trackir_area,		// Retro 10Jul2004
	*reverse_pedal_area,// Retro 17Jul2004
	*mouselook_sensitivity_area,// Retro 17Jul2004 - this is for mouse if mouselook is enabled, POV else - check the eech.ini
	*joylook_sensitivity_area,	// Retro 17Jul2004
	*cyclic_option_button,
	*cyclic_y_option_button,	// Retro 10Jul2004
	*collective_option_button,
	*pedal_option_button,
//Retro10Jul2004_dead	*device_option_button,
//Retro10Jul2004_dead	*device_graphic_area,
	*reverse_throttle_button,
	*keyboard_assist_option_button,
	*eo_pan_x_option_button,	// Retro 10Jul2004
	*eo_pan_y_option_button,	// Retro 10Jul2004
	*eo_zoom_option_button,		// Retro 10Jul2004
	*joylook_x_option_button,	// Retro 10Jul2004
	*joylook_y_option_button,	// Retro 10Jul2004
	*mouselook_option_button,	// Retro 10Jul2004
	*trackir_option_button,		// Retro 10Jul2004
	*reverse_pedal_option_button,		// Retro 17Jul2004
	*mouselook_sensitivity_up_button,	// Retro 17Jul2004
	*mouselook_sensitivity_down_button,	// Retro 17Jul2004
	*joylook_sensitivity_up_button,		// Retro 17Jul2004
	*joylook_sensitivity_down_button,	// Retro 17Jul2004
	*autoconfigure_area,	// Retro 28Jul2004
	*autoconfigure_button;	// Retro 28Jul2004

static const char
	*option_joystick_text[2],
	*option_throttle_text[2],
	*option_pedal_text[2],
	*option_boolean_text[2],
	*option_mouselook_text[MOUSELOOK_MAX],	// Retro 27Nov2004
	*no_joystick_text;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_joystick_selection (void);

void notify_cyclic_option_button ( ui_object *obj, void *arg );
void notify_cyclic_option_button_right ( ui_object *obj, void *arg );	// Retro 28Aug2004

void notify_collective_option_button ( ui_object *obj, void *arg );
void notify_collective_option_button_right ( ui_object *obj, void *arg );	// Retro 28Aug2004

void notify_pedal_option_button ( ui_object *obj, void *arg );
void notify_pedal_option_button_right ( ui_object *obj, void *arg );	// Retro 28Aug2004

 //Retro10Jul2004_dead void notify_device_option_button ( ui_object *obj, void *arg );

void notify_reverse_throttle_option_button ( ui_object *obj, void *arg );

void notify_keyboard_assist_option_button ( ui_object *obj, void *arg );

// Retro 10Jul2004 start
void notify_cyclic_y_option_button ( ui_object *obj, void *arg );
void notify_cyclic_y_option_button_right ( ui_object *obj, void *arg );	// Retro 28Aug2004
void notify_eo_pan_x_option_button ( ui_object *obj, void *arg );
void notify_eo_pan_x_option_button_right ( ui_object *obj, void *arg );	// Retro 28Aug2004
void notify_eo_pan_y_option_button ( ui_object *obj, void *arg );
void notify_eo_pan_y_option_button_right ( ui_object *obj, void *arg );	// Retro 28Aug2004
void notify_eo_zoom_option_button ( ui_object *obj, void *arg );
void notify_eo_zoom_option_button_right ( ui_object *obj, void *arg );	// Retro 28Aug2004
void notify_joylook_x_option_button ( ui_object *obj, void *arg );
void notify_joylook_x_option_button_right ( ui_object *obj, void *arg );	// Retro 28Aug2004
void notify_joylook_y_option_button ( ui_object *obj, void *arg );
void notify_joylook_y_option_button_right ( ui_object *obj, void *arg );	// Retro 28Aug2004
void notify_mouselook_option_button ( ui_object *obj, void *arg );
void notify_mouselook_option_button_right ( ui_object *obj, void *arg );	// Retro 28Aug2004
void notify_trackir_option_button ( ui_object *obj, void *arg );
void notify_trackir_option_button_right ( ui_object *obj, void *arg );	// Retro 28Aug2004
// Retro 10Jul2004 end

// Retro 17Jul2004 start
void notify_reverse_pedal_option_button ( ui_object *obj, void *arg );
void notify_mouselook_sensitivity_up_button ( ui_object *obj, void *arg );
void notify_mouselook_sensitivity_down_button ( ui_object *obj, void *arg );
void notify_joylook_sensitivity_up_button ( ui_object *obj, void *arg );
void notify_joylook_sensitivity_down_button ( ui_object *obj, void *arg );
void draw_joylook_sensitivity ( ui_object *obj, void *arg );
void draw_mouselook_sensitivity ( ui_object *obj, void *arg );
// Retro 17Jul2004 end

void notify_autoconfigure_button( ui_object *obj, void *arg);		// Retro 28Jul2004
void setTrackIRButton ( int selection );	// Retro 31Jan2005

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Retro 28Aug2004

void resetJoystickMapping(void)
{
	int
		i;

	set_global_collective_input ( KEYBOARD_INPUT );

	set_global_cyclic_input ( KEYBOARD_INPUT );

	set_global_pedal_input ( KEYBOARD_INPUT );

	command_line_cyclic_joystick_index = -1;
	command_line_cyclic_joystick_x_axis = -1;
	command_line_cyclic_joystick_y_axis =- 1;

	command_line_collective_joystick_index = -1;
	command_line_collective_joystick_axis = -1;

	command_line_rudder_joystick_index = -1;
	command_line_rudder_joystick_axis = -1;

	command_line_eo_pan_joystick_index = -1;
	command_line_eo_pan_vertical_joystick_axis = -1;
	command_line_eo_pan_horizontal_joystick_axis = -1;

	command_line_eo_zoom_joystick_index = -1;
	command_line_eo_zoom_joystick_axis = -1;

	command_line_joylook_joystick_index = -1;
	command_line_joylookh_joystick_axis = -1;
	command_line_joylookv_joystick_axis = -1;

	for (i = 0; i < AxisCount; i++)
	{
		AxisInfo[i].inUse = FALSE;
	}
}

void initialise_joystick_selection (void)
{
#if 0	// Retro 10Jul2004
	// adjust selected joystick
	if ( get_global_joystick_device_index () == -1 ) 
	{

		// We had no joysticks installed last time - adjust now if we do have

		if ( number_of_joystick_devices )
		{

			set_global_joystick_device_index ( 0 );
		} 
		else
		{

			set_global_collective_input ( KEYBOARD_INPUT );

			set_global_cyclic_input (KEYBOARD_INPUT);

			set_global_pedal_input (KEYBOARD_INPUT);
		}
	}
	else if ( get_global_joystick_device_index() >= number_of_joystick_devices )
	{

		// Last joystick selection is now not available

		if ( number_of_joystick_devices == 0 )
		{

			set_global_joystick_device_index ( -1 );

			set_global_collective_input ( KEYBOARD_INPUT );

			set_global_cyclic_input ( KEYBOARD_INPUT );

			set_global_pedal_input ( KEYBOARD_INPUT );
		}
		else
		{
	
			set_global_joystick_device_index ( 0 );
		}
	}
#else	// Retro 17Jul2004
	// Check if the number of enumerated joysticks changed compared to last time
	// If it does, nuke everything
	if (( get_global_joystick_device_index () == -1 )||
		( number_of_joystick_devices != get_global_joystick_device_index ()))
	{
#if 0
		set_global_collective_input ( KEYBOARD_INPUT );

		set_global_cyclic_input ( KEYBOARD_INPUT );

		set_global_pedal_input ( KEYBOARD_INPUT );

		set_global_joystick_device_index (-1);

		command_line_cyclic_joystick_index = -1;
		command_line_cyclic_joystick_x_axis = -1;
		command_line_cyclic_joystick_y_axis =- 1;

		command_line_collective_joystick_index = -1;
		command_line_collective_joystick_axis = -1;

		command_line_rudder_joystick_index = -1;
		command_line_rudder_joystick_axis = -1;

		command_line_eo_pan_joystick_index = -1;
		command_line_eo_pan_vertical_joystick_axis = -1;
		command_line_eo_pan_horizontal_joystick_axis = -1;

		command_line_eo_zoom_joystick_index = -1;
		command_line_eo_zoom_joystick_axis = -1;

		command_line_joylook_joystick_index = -1;
		command_line_joylookh_joystick_axis = -1;
		command_line_joylookv_joystick_axis = -1;
#else
		set_global_joystick_device_index (-1);

		resetJoystickMapping();
#endif

#if DEBUG_MODULE
		debug_log ("Number of joysticks changed from %i to %i - resetting everything\n",get_global_joystick_device_index(),number_of_joystick_devices);
#endif

		// Now save the new number
		// For this I recycled an old function, in order to not touch the options-file layout - hence the strange name
		set_global_joystick_device_index ( number_of_joystick_devices );
	}
#endif	// Retro 10Jul2004
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Retro 10Jul2004 - on enumerating, each axis is entered into an array of axis
//	This function fins an axis described by its device and DX-type in this array
int findAxisInArray (int device, int axis)
{
	int
		i;

	for (i = 0; i < AxisCount; i++)
	{
		if ((AxisInfo[i].device == device)&&(AxisInfo[i].axis == axis))
		{
			return i;
		}
	}
	return -1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Retro 10Jul2004 - sets the 'used' flag of an axis described by its devices and DX-type to 'false'
void setAxisUnused(int device, int axis)
{
	int
		retAxisIndex;

	retAxisIndex = findAxisInArray(device,axis);
	if (retAxisIndex > 0)	// '0' is keyboard, '-1' is 'not found'
		AxisInfo[retAxisIndex].inUse = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Retro 20Aug2004
int checkIfAllAxisUsed()
{
	int
		i;

	// we start with 1 as 0 is the Keyboard, and, for our purposes, _never_ in use
	for (i = 1; i < AxisCount; i++)
	{
		if (AxisInfo[i].inUse == FALSE)
			return FALSE;
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Retro 10Jul2004 - on enumerating, each axis is entered into an array of axis
//	This function fins an UNUSED axis described by its device and DX-type in this array
int findNextUnusedAxis(int device, int axis)
{
	int
		retAxisIndex,
		i;

	retAxisIndex = findAxisInArray(device,axis);

	// set old deviceaxis to 'unused'
	// '-1' indicated 'device+axis combination not found'
	// either it was not mapped or an old configuration
	// file was loaded (new device added or such)
	if (retAxisIndex != -1)
		AxisInfo[retAxisIndex].inUse = FALSE;
	else
		retAxisIndex = 0;

	// Retro 20Aug2004 - if no axis is available, set mapping back to keyboard
	if (checkIfAllAxisUsed() == TRUE)
		return 0;

	// Retro 28Aug2004 - a safer variant, to avoid loops..
	for (i = retAxisIndex+1; i < (retAxisIndex + AxisCount + 1); i++)
	{
		if (AxisInfo[(i%AxisCount)].inUse == FALSE)
		{
			retAxisIndex = (i%AxisCount);
			break;
		}
	}

	// set new deviceaxis to 'used'
	// ..but keyboard is always 'not in use' for our purposes
	if (retAxisIndex != 0)
		AxisInfo[retAxisIndex].inUse = TRUE;

	return retAxisIndex;
}

int findPreviousUnusedAxis(int device, int axis)
{
	int
		retAxisIndex,
		i;

	retAxisIndex = findAxisInArray(device,axis);

	// set old deviceaxis to 'unused'
	// '-1' indicated 'device+axis combination not found'
	// either it was not mapped or an old configuration
	// file was loaded (new device added or such)
	if (retAxisIndex != -1)
		AxisInfo[retAxisIndex].inUse = FALSE;
	else
		retAxisIndex = 0;

	// Retro 20Aug2004 - if no axis is available, set mapping back to keyboard
	if (checkIfAllAxisUsed() == TRUE)
		return 0;

	// Retro 28Aug2004 - a safer variant, to avoid loops..
	for (i = (retAxisIndex + AxisCount-1); i > retAxisIndex-1; i--)
	{
		if (AxisInfo[(i%AxisCount)].inUse == FALSE)
		{
			retAxisIndex = (i%AxisCount);
			break;
		}
	}
	
	// set new deviceaxis to 'used'
	// ..but keyboard is always 'not in use' for our purposes
	if (retAxisIndex != 0)
		AxisInfo[retAxisIndex].inUse = TRUE;

	return retAxisIndex;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Retro 10Jul2004
// same as above, but with the additional restriction that the new axis has to be no the same device as the old one
// this means that keyboard is NEVER considered !
// This is used for cyclic pitch/bank, eo x/y and joystick look x/y axis
int findNextUnusedDeviceAxis(int device, int axis)
{
	int
		retAxisIndex,
		i;

	// user has to assign 'x' axis first
	if (device == -1)
		return 0;

	retAxisIndex = findAxisInArray(device,axis);

	// set old deviceaxis to 'unused'
	// '-1' indicated 'device+axis combination not found'
	// either it was not mapped or an old configuration
	// file was loaded (new device added or such)
	if (retAxisIndex != -1)
		AxisInfo[retAxisIndex].inUse = FALSE;
	else
		retAxisIndex = 0;

	// Retro 20Aug2004 - if no axis is available, set back to keyboard
	if (checkIfAllAxisUsed() == TRUE)
		return 0;

#if 0
	do {
		if ((retAxisIndex != -1)&&(retAxisIndex < AxisCount-1))
			retAxisIndex ++;
		else
			retAxisIndex = 1;	// no keyboard in this selection, thanks

	} while ((AxisInfo[retAxisIndex].device != device)||(AxisInfo[retAxisIndex].inUse == TRUE));
#else
	// Retro 28Aug2004 - a safer variant, to avoid loops..
	for (i = retAxisIndex+1; i < (retAxisIndex + AxisCount + 1); i++)
	{
		if ((AxisInfo[(i%AxisCount)].device == device)&&(AxisInfo[(i%AxisCount)].inUse == FALSE))
		{
			retAxisIndex = (i%AxisCount);
			break;
		}
	}
#endif

	if (retAxisIndex != 0)
		AxisInfo[retAxisIndex].inUse = TRUE; // set new deviceaxis to 'used'

	return retAxisIndex;
}

int findPreviousUnusedDeviceAxis(int device, int axis)
{
	int
		retAxisIndex,
		i;

	// user has to assign 'x' axis first
	if (device == -1)
		return 0;

	retAxisIndex = findAxisInArray(device,axis);

	// set old deviceaxis to 'unused'
	// '-1' indicated 'device+axis combination not found'
	// either it was not mapped or an old configuration
	// file was loaded (new device added or such)
	if (retAxisIndex != -1)
		AxisInfo[retAxisIndex].inUse = FALSE;
	else
		retAxisIndex = 0;

	// Retro 20Aug2004 - if no axis is available, set back to keyboard
	if (checkIfAllAxisUsed() == TRUE)
		return 0;

	// Retro 28Aug2004 - a safer variant, to avoid loops..
	for (i = (retAxisIndex + AxisCount-1); i > retAxisIndex-1; i--)
	{
		if ((AxisInfo[(i%AxisCount)].device == device)&&(AxisInfo[(i%AxisCount)].inUse == FALSE))
		{
			retAxisIndex = (i%AxisCount);
			break;
		}
	}

	if (retAxisIndex != 0)
		AxisInfo[retAxisIndex].inUse = TRUE; // set new deviceaxis to 'used'

	return retAxisIndex;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_show_controller_page (void)
{
#if 0	// Retro 10Jul2004
	// initialise button text

	if ( (get_global_cyclic_input () == JOYSTICK_INPUT) && (number_of_joystick_devices) )
	{
		set_ui_object_text (cyclic_option_button, option_joystick_text[1]);
	}
	else
	{
		set_ui_object_text (cyclic_option_button, option_joystick_text[0]);
	}

	if ( (get_global_collective_input () == THROTTLE_INPUT) && (number_of_joystick_devices) )
	{
		set_ui_object_text (collective_option_button, option_throttle_text[1]);
	}
	else
	{
		set_ui_object_text (collective_option_button, option_throttle_text[0]);
	}

	if ( (get_global_pedal_input () == RUDDER_INPUT) && (number_of_joystick_devices) )
	{
		set_ui_object_text (pedal_option_button, option_pedal_text[1]);
	}
	else
	{
		set_ui_object_text (pedal_option_button, option_pedal_text[0]);
	}

	if (get_global_joystick_device_index () == -1)
	{
		set_ui_object_font_type (device_option_button, UI_FONT_THICK_ITALIC_ARIAL_18);

		set_ui_object_text (device_option_button, no_joystick_text);

		preprocess_translation_object_size (device_graphic_area, device_option_button, &no_joystick_text, 1, RESIZE_OPTION_CYCLE_BUTTON);
	}
	else
	{
		const char
			*name[1];

		set_ui_object_text (device_option_button, joystick_devices[get_global_joystick_device_index ()].device_name);
	
		name[0] = &joystick_devices[get_global_joystick_device_index ()].device_name;
		
		preprocess_translation_object_size (device_graphic_area, device_option_button, name, 1, RESIZE_OPTION_CYCLE_BUTTON);
	}

#else	// Retro 10Jul2004

	// cyclic x/y

	if (command_line_cyclic_joystick_index != -1)
	{
		int AxisInfoIndex;
		
		AxisInfoIndex = findAxisInArray(command_line_cyclic_joystick_index,command_line_cyclic_joystick_x_axis);
		if (AxisInfoIndex != -1)
		{
			AxisInfo[AxisInfoIndex].inUse = TRUE;
			set_ui_object_text (cyclic_option_button, AxisInfo[AxisInfoIndex].AxisName);
			set_global_cyclic_input ( JOYSTICK_INPUT );
		}
		else
		{
			set_ui_object_text (cyclic_option_button, option_joystick_text[0]);
			set_global_cyclic_input ( KEYBOARD_INPUT );
		}

		AxisInfoIndex = findAxisInArray(command_line_cyclic_joystick_index,command_line_cyclic_joystick_y_axis);
		if (AxisInfoIndex != -1)
		{
			AxisInfo[AxisInfoIndex].inUse = TRUE;
			set_ui_object_text (cyclic_y_option_button, AxisInfo[AxisInfoIndex].AxisName);
			set_global_cyclic_input ( JOYSTICK_INPUT );
		}
		else
		{
			set_ui_object_text (cyclic_y_option_button, option_joystick_text[0]);
			set_global_cyclic_input ( KEYBOARD_INPUT );
		}
	}
	else
	{
		set_ui_object_text (cyclic_option_button, option_joystick_text[0]);
		set_ui_object_text (cyclic_y_option_button, option_joystick_text[0]);
		set_global_cyclic_input ( KEYBOARD_INPUT );
	}

	// collective

	if (command_line_collective_joystick_index != -1)
	{
		int AxisIndex;
		
		AxisIndex = findAxisInArray(command_line_collective_joystick_index,command_line_collective_joystick_axis);
		if (AxisIndex != -1)
		{
			AxisInfo[AxisIndex].inUse = TRUE;
			set_ui_object_text (collective_option_button, AxisInfo[AxisIndex].AxisName);
			set_global_collective_input ( THROTTLE_INPUT );
		}
		else
		{
			set_ui_object_text (collective_option_button, option_throttle_text[0]);
			set_global_collective_input ( KEYBOARD_INPUT );
		}
	}
	else
	{
		set_ui_object_text (collective_option_button, option_throttle_text[0]);
		set_global_collective_input ( KEYBOARD_INPUT );
	}

	// pedal (+ reverse button)

	if (command_line_rudder_joystick_index != -1)
	{
		int AxisIndex;
		
		AxisIndex = findAxisInArray(command_line_rudder_joystick_index,command_line_rudder_joystick_axis);
		if (AxisIndex != -1)
		{
			AxisInfo[AxisIndex].inUse = TRUE;
			set_ui_object_text (pedal_option_button, AxisInfo[AxisIndex].AxisName);
			set_global_pedal_input (RUDDER_INPUT);
			set_ui_object_text (reverse_pedal_option_button, option_boolean_text [command_line_reverse_pedal]);	// Retro 17Jul2004
		}
		else
		{
			set_ui_object_text (pedal_option_button, option_throttle_text[0]);
			set_global_pedal_input (KEYBOARD_INPUT);
			set_ui_object_text (reverse_pedal_option_button, option_boolean_text [FALSE]);	// Retro 17Jul2004
		}
	}
	else
	{
		set_ui_object_text (pedal_option_button, option_throttle_text[0]);
		set_global_pedal_input (KEYBOARD_INPUT);
		set_ui_object_text (reverse_pedal_option_button, option_boolean_text [FALSE]);	// Retro 17Jul2004
	}

	// EO x/y

	if (command_line_eo_pan_joystick_index != -1)
	{
		int AxisInfoIndex;
		
		AxisInfoIndex = findAxisInArray(command_line_eo_pan_joystick_index,command_line_eo_pan_horizontal_joystick_axis);
		if (AxisInfoIndex != -1)
		{
			AxisInfo[AxisInfoIndex].inUse = TRUE;
			set_ui_object_text (eo_pan_x_option_button, AxisInfo[AxisInfoIndex].AxisName);
		}
		else
		{
			set_ui_object_text (eo_pan_x_option_button, option_joystick_text[0]);
		}

		AxisInfoIndex = findAxisInArray(command_line_eo_pan_joystick_index,command_line_eo_pan_vertical_joystick_axis);
		if (AxisInfoIndex != -1)
		{
			AxisInfo[AxisInfoIndex].inUse = TRUE;
			set_ui_object_text (eo_pan_y_option_button, AxisInfo[AxisInfoIndex].AxisName);
		}
		else
		{
			set_ui_object_text (eo_pan_y_option_button, option_joystick_text[0]);
		}
	}
	else
	{
		set_ui_object_text (eo_pan_x_option_button, option_joystick_text[0]);
		set_ui_object_text (eo_pan_y_option_button, option_joystick_text[0]);
	}

	// EO Zoom

	if (command_line_eo_zoom_joystick_index != -1)
	{
		int AxisIndex;
		
		AxisIndex = findAxisInArray(command_line_eo_zoom_joystick_index,command_line_eo_zoom_joystick_axis);
		if (AxisIndex != -1)
		{
			AxisInfo[AxisIndex].inUse = TRUE;
			set_ui_object_text (eo_zoom_option_button, AxisInfo[AxisIndex].AxisName);
		}
		else
		{
			set_ui_object_text (eo_zoom_option_button, option_throttle_text[0]);
		}
	}
	else
	{
		set_ui_object_text (eo_zoom_option_button, option_throttle_text[0]);
	}

	// joystick look x/y

	if (command_line_joylook_joystick_index != -1)
	{
		int AxisInfoIndex;
		
		AxisInfoIndex = findAxisInArray(command_line_joylook_joystick_index,command_line_joylookh_joystick_axis);
		if (AxisInfoIndex != -1)
		{
			AxisInfo[AxisInfoIndex].inUse = TRUE;
			set_ui_object_text (joylook_x_option_button, AxisInfo[AxisInfoIndex].AxisName);
		}
		else
		{
			set_ui_object_text (joylook_x_option_button, option_joystick_text[0]);
		}

		AxisInfoIndex = findAxisInArray(command_line_joylook_joystick_index,command_line_joylookv_joystick_axis);
		if (AxisInfoIndex != -1)
		{
			AxisInfo[AxisInfoIndex].inUse = TRUE;
			set_ui_object_text (joylook_y_option_button, AxisInfo[AxisInfoIndex].AxisName);
		}
		else
		{
			set_ui_object_text (joylook_y_option_button, option_joystick_text[0]);
		}
	}
	else
	{
		set_ui_object_text (joylook_x_option_button, option_joystick_text[0]);
		set_ui_object_text (joylook_y_option_button, option_joystick_text[0]);
	}

	// mouselook
	// Retro 27Nov2004 - may be either OFF-INTERNAL-EXTERNAL-ON (both)
	set_ui_object_text (mouselook_option_button, option_mouselook_text [command_line_mouse_look]);

	// trackIR (depending on mouselook)

	TIR_Poll();	// Retro 6Feb2005

	if (query_TIR_active() == TRUE)
	{
		if (command_line_mouse_look != MOUSELOOK_OFF)
			set_ui_object_text (trackir_option_button, get_trans ("Running") );
		else
			set_ui_object_text (trackir_option_button, get_trans ("Enable Mouselook") );
	}
	else
		set_ui_object_text (trackir_option_button, option_boolean_text [0]);	// nailed to FALSE for now
#endif	// Retro 10Jul2004

	// reverse throttle

	set_ui_object_text (reverse_throttle_button, option_boolean_text [get_global_dynamics_options_reverse_throttle_input ()]);

	// keyboard assistant

	set_ui_object_text (keyboard_assist_option_button, option_boolean_text [get_global_dynamics_options_keyboard_assistance ()]);

	display_options_page(OPTIONS_PAGE_CONTROLLER);

	#if DEBUG_MODULE
		debug_filtered_log("Inside show_controller_page");
	#endif

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void define_options_screen_controller_page_objects (void)
{
	int
		i = 0;
		
	float
		x1,
		y1,
		x2,
		y2;

	ui_object
		*page;

	ui_object
#if 0
		*title_change_array [14],
		*check_array [14],
		*change_array [14];
#else
		*title_change_array[15],
		*check_array[15],
		*change_array[14];
#endif

	/////////////////////////////////////////////////////////////////
	// Initialise Button Strings
	
	option_joystick_text [0] = get_trans ("UI_KEYBOARD");
	option_joystick_text [1] = get_trans ("UI_JOYSTICK");

	option_throttle_text [0] = get_trans ("UI_KEYBOARD");
	option_throttle_text [1] = get_trans ("Throttle");

	option_pedal_text [0] = get_trans ("UI_KEYBOARD");
	option_pedal_text [1] = get_trans ("Rudder Pedals");

	no_joystick_text = get_trans ("UI_NONE_AVAILABLE");
	
	option_boolean_text [0] = get_trans ("Off");
	option_boolean_text [1] = get_trans ("On");

	// Retro 27Nov2004
	option_mouselook_text[MOUSELOOK_OFF] = get_trans("Off");
	option_mouselook_text[MOUSELOOK_INTERNAL] = get_trans("Internal");
	option_mouselook_text[MOUSELOOK_EXTERNAL] = get_trans("External");
	option_mouselook_text[MOUSELOOK_ON] = get_trans("On");
	// Retro 27Nov2004 end

	/////////////////////////////////////////////////////////////////
	// Controller Area

	x1 = 0.0;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 1.0;

	options_page [OPTIONS_PAGE_CONTROLLER] = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (options_screen),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2, y2),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_DRAWABLE (FALSE),
				UI_ATTR_FUNCTION (NOTIFY_TYPE_NONE),
				UI_ATTR_END
			);

	page = options_page [OPTIONS_PAGE_CONTROLLER];

	// areas and titles

	// cyclic

	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (/*OPTION_AREA_OFFSET_Y*/OPTION_SMALL_AREA_OFFSET_Y * i);

   cyclic_area = create_ui_object
									(
										UI_TYPE_AREA,
										UI_ATTR_PARENT (page),
										UI_ATTR_VIRTUAL_POSITION (x1, y1),
										UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, /*OPTION_AREA_HEIGHT*/OPTION_SMALL_AREA_HEIGHT),
										UI_ATTR_CLEAR (TRUE),
										UI_ATTR_END
									);

	x1 = CONTROLLER_OPTION_TITLE_OFFSET_X;	// Retro 10Jul2004
	y1 = 0.0; 

	title_change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (cyclic_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_END
	);

   check_array[i] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array [i]),
		UI_ATTR_FONT_TYPE (/*UI_FONT_THICK_ARIAL_18*/UI_FONT_ARIAL_14),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
//		UI_ATTR_TEXT (get_trans ("UI_CYCLIC")),
		UI_ATTR_TEXT (get_trans ("Cyclic Roll")),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [i], check_array [i], NULL, 0, RESIZE_OPTION_BOX_TITLE);

	// Retro 10Jul2004
	// cyclic y axis

	i++;
	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (/*OPTION_AREA_OFFSET_Y*/OPTION_SMALL_AREA_OFFSET_Y * i);

   cyclic_y_area = create_ui_object
									(
										UI_TYPE_AREA,
										UI_ATTR_PARENT (page),
										UI_ATTR_VIRTUAL_POSITION (x1, y1),
										UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, /*OPTION_AREA_HEIGHT*/OPTION_SMALL_AREA_HEIGHT),
										UI_ATTR_CLEAR (TRUE),
										UI_ATTR_END
									);

	x1 = CONTROLLER_OPTION_TITLE_OFFSET_X;	// Retro 10Jul2004
	y1 = 0.0; 

	title_change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (cyclic_y_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_END
	);

   check_array[i] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array [i]),
		UI_ATTR_FONT_TYPE (/*UI_FONT_THICK_ARIAL_18*/UI_FONT_ARIAL_14),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("Cyclic Pitch")),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [i], check_array [i], NULL, 0, RESIZE_OPTION_BOX_TITLE);
	// Retro 10Jul2004 end

	// collective

	i++;
	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (/*OPTION_AREA_OFFSET_Y*/OPTION_SMALL_AREA_OFFSET_Y * i);

   collective_area = create_ui_object
								(
									UI_TYPE_AREA,
									UI_ATTR_PARENT ( page ),
									UI_ATTR_VIRTUAL_POSITION (x1, y1),
									UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, /*OPTION_AREA_HEIGHT*/OPTION_SMALL_AREA_HEIGHT),
									UI_ATTR_CLEAR (TRUE),
									UI_ATTR_END
								);

	x1 = CONTROLLER_OPTION_TITLE_OFFSET_X;	// Retro 10Jul2004
	y1 = 0.0; 

	title_change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (collective_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_END
	);

   check_array[i] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array [i]),
		UI_ATTR_FONT_TYPE (/*UI_FONT_THICK_ARIAL_18*/UI_FONT_ARIAL_14),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("UI_COLLECTIVE")),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [i], check_array [i], NULL, 0, RESIZE_OPTION_BOX_TITLE);

	// pedal area
	
	i++;
	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (/*OPTION_AREA_OFFSET_Y*/OPTION_SMALL_AREA_OFFSET_Y * i);

   pedal_area = create_ui_object
								(
									UI_TYPE_AREA,
									UI_ATTR_PARENT ( page ),
									UI_ATTR_VIRTUAL_POSITION (x1, y1),
									UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, /*OPTION_AREA_HEIGHT*/OPTION_SMALL_AREA_HEIGHT),
									UI_ATTR_CLEAR (TRUE),
									UI_ATTR_END
								);

	x1 = CONTROLLER_OPTION_TITLE_OFFSET_X;	// Retro 10Jul2004
	y1 = 0.0; 

	title_change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (pedal_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_END
	);

   check_array[i] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array [i]),
		UI_ATTR_FONT_TYPE (/*UI_FONT_THICK_ARIAL_18*/UI_FONT_ARIAL_14),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("UI_PEDAL")),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [i], check_array [i], NULL, 0, RESIZE_OPTION_BOX_TITLE);

#if 0 //Retro10Jul2004_dead
	//device area

	i++;
	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (/*OPTION_AREA_OFFSET_Y*/OPTION_SMALL_AREA_OFFSET_Y * i);

   device_area = create_ui_object
										(
											UI_TYPE_AREA,
											UI_ATTR_PARENT (page),
											UI_ATTR_VIRTUAL_POSITION (x1, y1),
											UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, /*OPTION_AREA_HEIGHT*/OPTION_SMALL_AREA_HEIGHT),
											UI_ATTR_CLEAR (TRUE),
											UI_ATTR_END
										);

	x1 = CONTROLLER_OPTION_TITLE_OFFSET_X;	// Retro 10Jul2004
	y1 = 0.0; 

	title_change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (device_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_END
	);

   check_array[i] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array [i]),
		UI_ATTR_FONT_TYPE (/*UI_FONT_THICK_ARIAL_18*/UI_FONT_ARIAL_14),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("UI_DEVICE")),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [i], check_array [i], NULL, 0, RESIZE_OPTION_BOX_TITLE);
#endif //Retro10Jul2004_dead

	// Retro 10Jul2004
	// eo pan x area
	
	i++;
	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (/*OPTION_AREA_OFFSET_Y*/OPTION_SMALL_AREA_OFFSET_Y * i);

   eo_pan_x_area = create_ui_object
								(
									UI_TYPE_AREA,
									UI_ATTR_PARENT ( page ),
									UI_ATTR_VIRTUAL_POSITION (x1, y1),
									UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, /*OPTION_AREA_HEIGHT*/OPTION_SMALL_AREA_HEIGHT),
									UI_ATTR_CLEAR (TRUE),
									UI_ATTR_END
								);

	x1 = CONTROLLER_OPTION_TITLE_OFFSET_X;	// Retro 10Jul2004
	y1 = 0.0; 

	title_change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (eo_pan_x_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_END
	);

   check_array[i] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array [i]),
		UI_ATTR_FONT_TYPE (/*UI_FONT_THICK_ARIAL_18*/UI_FONT_ARIAL_14),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("EO Pan X")),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [i], check_array [i], NULL, 0, RESIZE_OPTION_BOX_TITLE);
	// Retro 10Jul2004 end

	// Retro 10Jul2004
	// eo panning y area
	
	i++;
	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (/*OPTION_AREA_OFFSET_Y*/OPTION_SMALL_AREA_OFFSET_Y * i);

   eo_pan_y_area = create_ui_object
								(
									UI_TYPE_AREA,
									UI_ATTR_PARENT ( page ),
									UI_ATTR_VIRTUAL_POSITION (x1, y1),
									UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, /*OPTION_AREA_HEIGHT*/OPTION_SMALL_AREA_HEIGHT),
									UI_ATTR_CLEAR (TRUE),
									UI_ATTR_END
								);

	x1 = CONTROLLER_OPTION_TITLE_OFFSET_X;	// Retro 10Jul2004
	y1 = 0.0; 

	title_change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (eo_pan_y_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_END
	);

   check_array[i] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array [i]),
		UI_ATTR_FONT_TYPE (/*UI_FONT_THICK_ARIAL_18*/UI_FONT_ARIAL_14),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("EO Pan Y")),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [i], check_array [i], NULL, 0, RESIZE_OPTION_BOX_TITLE);
	// Retro 10Jul2004 end

	// Retro 10Jul2004
	// eo zoom area
	
	i++;
	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (/*OPTION_AREA_OFFSET_Y*/OPTION_SMALL_AREA_OFFSET_Y * i);

   eo_zoom_area = create_ui_object
								(
									UI_TYPE_AREA,
									UI_ATTR_PARENT ( page ),
									UI_ATTR_VIRTUAL_POSITION (x1, y1),
									UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, /*OPTION_AREA_HEIGHT*/OPTION_SMALL_AREA_HEIGHT),
									UI_ATTR_CLEAR (TRUE),
									UI_ATTR_END
								);

	x1 = CONTROLLER_OPTION_TITLE_OFFSET_X;	// Retro 10Jul2004
	y1 = 0.0; 

	title_change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (eo_zoom_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_END
	);

   check_array[i] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array [i]),
		UI_ATTR_FONT_TYPE (/*UI_FONT_THICK_ARIAL_18*/UI_FONT_ARIAL_14),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("EO Zoom")),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [i], check_array [i], NULL, 0, RESIZE_OPTION_BOX_TITLE);
	// Retro 10Jul2004 end

	// Retro 10Jul2004
	// joylook x area
	
	i++;
	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (/*OPTION_AREA_OFFSET_Y*/OPTION_SMALL_AREA_OFFSET_Y * i);

   joylook_x_area = create_ui_object
								(
									UI_TYPE_AREA,
									UI_ATTR_PARENT ( page ),
									UI_ATTR_VIRTUAL_POSITION (x1, y1),
									UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, /*OPTION_AREA_HEIGHT*/OPTION_SMALL_AREA_HEIGHT),
									UI_ATTR_CLEAR (TRUE),
									UI_ATTR_END
								);

	x1 = CONTROLLER_OPTION_TITLE_OFFSET_X;	// Retro 10Jul2004
	y1 = 0.0; 

	title_change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (joylook_x_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_END
	);

   check_array[i] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array [i]),
		UI_ATTR_FONT_TYPE (/*UI_FONT_THICK_ARIAL_18*/UI_FONT_ARIAL_14),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("Joystick Look X")),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [i], check_array [i], NULL, 0, RESIZE_OPTION_BOX_TITLE);
	// Retro 10Jul2004 end

	// Retro 10Jul2004
	// joylook y area
	
	i++;
	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (/*OPTION_AREA_OFFSET_Y*/OPTION_SMALL_AREA_OFFSET_Y * i);

   joylook_y_area = create_ui_object
								(
									UI_TYPE_AREA,
									UI_ATTR_PARENT ( page ),
									UI_ATTR_VIRTUAL_POSITION (x1, y1),
									UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, /*OPTION_AREA_HEIGHT*/OPTION_SMALL_AREA_HEIGHT),
									UI_ATTR_CLEAR (TRUE),
									UI_ATTR_END
								);

	x1 = CONTROLLER_OPTION_TITLE_OFFSET_X;	// Retro 10Jul2004
	y1 = 0.0; 

	title_change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (joylook_y_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_END
	);

   check_array[i] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array [i]),
		UI_ATTR_FONT_TYPE (/*UI_FONT_THICK_ARIAL_18*/UI_FONT_ARIAL_14),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("Joystick Look Y")),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [i], check_array [i], NULL, 0, RESIZE_OPTION_BOX_TITLE);
	// Retro 10Jul2004 end

	//reverse throttle area

	i++;
	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (/*OPTION_AREA_OFFSET_Y*/OPTION_SMALL_AREA_OFFSET_Y * i);

   reverse_throttle_area = create_ui_object
										(
											UI_TYPE_AREA,
											UI_ATTR_PARENT (page),
											UI_ATTR_VIRTUAL_POSITION (x1, y1),
											UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, /*OPTION_AREA_HEIGHT*/OPTION_SMALL_AREA_HEIGHT),
											UI_ATTR_CLEAR (TRUE),
											UI_ATTR_END
										);

	x1 = CONTROLLER_OPTION_TITLE_OFFSET_X;	// Retro 10Jul2004
	y1 = 0.0; 

	title_change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (reverse_throttle_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_END
	);

   check_array[i] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array [i]),
		UI_ATTR_FONT_TYPE (/*UI_FONT_THICK_ARIAL_18*/UI_FONT_ARIAL_14),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("Reverse Throttle")),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [i], check_array [i], NULL, 0, RESIZE_OPTION_BOX_TITLE);

	// Retro 17Jul2004
	// Reverse Pedal Option area

	i++;
//	x1 = 0.0; 
//	x1 = 0.5; 
	x1 = SECOND_OPTION_START;
//	y1 = OPTION_TITLE_OFFSET_Y + /*OPTION_AREA_OFFSET_Y*/OPTION_SMALL_AREA_OFFSET_Y * i;
	y1 = OPTION_TITLE_OFFSET_Y + /*OPTION_AREA_OFFSET_Y*/OPTION_SMALL_AREA_OFFSET_Y * (i-1);

   reverse_pedal_area = create_ui_object
								(
									UI_TYPE_AREA,
									UI_ATTR_PARENT ( page ),
									UI_ATTR_VIRTUAL_POSITION (x1, y1),
									UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, /*OPTION_AREA_HEIGHT*/OPTION_SMALL_AREA_HEIGHT),
									UI_ATTR_CLEAR (TRUE),
									UI_ATTR_END
								);

	x1 = CONTROLLER_OPTION_TITLE_OFFSET_X;	// Retro 10Jul2004
	y1 = 0.0; 

	title_change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (reverse_pedal_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START ( 255, 255, 255, 0 ),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

   check_array[i] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array[i]),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_FONT_TYPE (/*UI_FONT_THICK_ARIAL_18*/UI_FONT_ARIAL_14),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("Reverse Pedal")),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [i], check_array [i], NULL, 0, RESIZE_OPTION_BOX_TITLE);
	// Retro 17Jul2004 end

	// Retro 10Jul2004
	//mouselook area

	i++;
	x1 = 0.0; 
	y1 = OPTION_TITLE_OFFSET_Y + (/*OPTION_AREA_OFFSET_Y*/OPTION_SMALL_AREA_OFFSET_Y * (i-1));

   mouselook_area = create_ui_object
										(
											UI_TYPE_AREA,
											UI_ATTR_PARENT (page),
											UI_ATTR_VIRTUAL_POSITION (x1, y1),
											UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, /*OPTION_AREA_HEIGHT*/OPTION_SMALL_AREA_HEIGHT),
											UI_ATTR_CLEAR (TRUE),
											UI_ATTR_END
										);

	x1 = CONTROLLER_OPTION_TITLE_OFFSET_X;	// Retro 10Jul2004
	y1 = 0.0; 

	title_change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (mouselook_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_END
	);

   check_array[i] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array [i]),
		UI_ATTR_FONT_TYPE (/*UI_FONT_THICK_ARIAL_18*/UI_FONT_ARIAL_14),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("Mouselook")),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [i], check_array [i], NULL, 0, RESIZE_OPTION_BOX_TITLE);
	// Retro 10Jul2004 end

	// Retro 10Jul2004
	//trackir area

	i++;
//	x1 = 0.0; 
//	x1 = 0.5; 
	x1 = SECOND_OPTION_START;
//	y1 = OPTION_TITLE_OFFSET_Y + /*OPTION_AREA_OFFSET_Y*/OPTION_SMALL_AREA_OFFSET_Y * i;
	y1 = OPTION_TITLE_OFFSET_Y + /*OPTION_AREA_OFFSET_Y*/OPTION_SMALL_AREA_OFFSET_Y * (i-2);

   trackir_area = create_ui_object
								(
									UI_TYPE_AREA,
									UI_ATTR_PARENT ( page ),
									UI_ATTR_VIRTUAL_POSITION (x1, y1),
									UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, /*OPTION_AREA_HEIGHT*/OPTION_SMALL_AREA_HEIGHT),
									UI_ATTR_CLEAR (TRUE),
									UI_ATTR_END
								);

	x1 = CONTROLLER_OPTION_TITLE_OFFSET_X;	// Retro 10Jul2004
	y1 = 0.0; 

	title_change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (trackir_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START ( 255, 255, 255, 0 ),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

   check_array[i] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array[i]),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_FONT_TYPE (/*UI_FONT_THICK_ARIAL_18*/UI_FONT_ARIAL_14),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("TrackIR")),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [i], check_array [i], NULL, 0, RESIZE_OPTION_BOX_TITLE);
	// Retro 10Jul2004 end

	// Retro 17Jul2004 - joylook sensitivity area

	joylook_sensitivity_area = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (joylook_x_area),
		UI_ATTR_VIRTUAL_POSITION (0.8f, 0),	// FIXME - no absolute coding !
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_SMALL_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START ( 255, 255, 255, 0 ),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

	// Retro 17Jul2004 end

	// Retro 28Aug2004 - autoconfigure area

	autoconfigure_area = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (page),
		UI_ATTR_VIRTUAL_POSITION (CONTROLLER_OPTION_TITLE_OFFSET_X, OPTION_TITLE_OFFSET_Y-OPTION_SMALL_AREA_OFFSET_Y),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_LARGE_WIDTH, OPTION_SMALL_AREA_HEIGHT),
		UI_ATTR_COLOUR_START ( 255, 255, 255, 0 ),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

	// Retro 28Aug2004 end

	// Retro 17Jul2004 - mouselook sensitivity area
	
	mouselook_sensitivity_area = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (mouselook_area),
		UI_ATTR_VIRTUAL_POSITION (0.42, 0),	// FIXME - no absolute coding!
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_SMALL_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START ( 255, 255, 255, 0 ),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

	// Retro 17Jul2004 end

	//keyboard_assist area

	i++;
	x1 = 0.0; 
//	y1 = OPTION_TITLE_OFFSET_Y + /*OPTION_AREA_OFFSET_Y*/OPTION_SMALL_AREA_OFFSET_Y * i;
	y1 = OPTION_TITLE_OFFSET_Y + /*OPTION_AREA_OFFSET_Y*/OPTION_SMALL_AREA_OFFSET_Y * (i-2);

   keyboard_assist_area = create_ui_object
								(
									UI_TYPE_AREA,
									UI_ATTR_PARENT ( page ),
									UI_ATTR_VIRTUAL_POSITION (x1, y1),
									UI_ATTR_VIRTUAL_SIZE (OPTION_AREA_WIDTH, /*OPTION_AREA_HEIGHT*/OPTION_SMALL_AREA_HEIGHT),
									UI_ATTR_CLEAR (TRUE),
									UI_ATTR_END
								);

	x1 = CONTROLLER_OPTION_TITLE_OFFSET_X;	// Retro 10Jul2004
	y1 = 0.0; 

	title_change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (keyboard_assist_area),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START ( 255, 255, 255, 0 ),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

   check_array[i] = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (title_change_array[i]),
		UI_ATTR_VIRTUAL_POSITION (OPTION_BOX_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_FONT_TYPE (/*UI_FONT_THICK_ARIAL_18*/UI_FONT_ARIAL_14),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
		UI_ATTR_TEXT (get_trans ("Keyboard Assist")),
		UI_ATTR_END
	);

	preprocess_translation_object_size (title_change_array [i], check_array [i], NULL, 0, RESIZE_OPTION_BOX_TITLE);

	/////////////////////////////////////////////////////////////////
	// buttons

	i = 0;

	// cyclic

	change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (cyclic_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [i]) + get_ui_object_x_size_end (title_change_array [i]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_EXTRA_LARGE_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_medium),
		UI_ATTR_END
	);

	cyclic_option_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (cyclic_area),
		UI_ATTR_FONT_TYPE (/*UI_FONT_THICK_ITALIC_ARIAL_18*/UI_FONT_ITALIC_ARIAL_14),
		UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
		UI_ATTR_VIRTUAL_POSITION (get_ui_object_x_end (change_array [i]) + OPTION_BUTTON_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_STATE (UI_OBJECT_STATE_OFF),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_cyclic_option_button),
		UI_ATTR_RIGHT_FUNCTION (notify_cyclic_option_button_right),	// Retro 28Aug2004
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], cyclic_option_button, option_joystick_text, 2, RESIZE_OPTION_CYCLE_BUTTON);

	// Retro 10Jul2004
	// cyclic y axis

	i++;

	change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (cyclic_y_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [i]) + get_ui_object_x_size_end (title_change_array [i]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_EXTRA_LARGE_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_medium),
		UI_ATTR_END
	);

	cyclic_y_option_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (cyclic_y_area),
		UI_ATTR_FONT_TYPE (/*UI_FONT_THICK_ITALIC_ARIAL_18*/UI_FONT_ITALIC_ARIAL_14),
		UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
		UI_ATTR_VIRTUAL_POSITION (get_ui_object_x_end (change_array [i]) + OPTION_BUTTON_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_STATE (UI_OBJECT_STATE_OFF),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_cyclic_y_option_button),
		UI_ATTR_RIGHT_FUNCTION (notify_cyclic_y_option_button_right),	// Retro 28Aug2004
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], cyclic_y_option_button, option_joystick_text, 2, RESIZE_OPTION_CYCLE_BUTTON);
	// Retro 10Jul2004 end

	// collective
	
	i++;

	change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (collective_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [i]) + get_ui_object_x_size_end (title_change_array [i]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_EXTRA_LARGE_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_medium),
		UI_ATTR_END
	);

   collective_option_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (collective_area),
		UI_ATTR_FONT_TYPE (/*UI_FONT_THICK_ITALIC_ARIAL_18*/UI_FONT_ITALIC_ARIAL_14),
		UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
		UI_ATTR_VIRTUAL_POSITION (get_ui_object_x_end (change_array [i]) + OPTION_BUTTON_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_collective_option_button),
		UI_ATTR_RIGHT_FUNCTION (notify_collective_option_button_right),	// Retro 28Aug2004
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], collective_option_button, option_throttle_text, 2, RESIZE_OPTION_CYCLE_BUTTON);

	// pedal button
	
	i++;

	change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (pedal_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [i]) + get_ui_object_x_size_end (title_change_array [i]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_EXTRA_LARGE_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

   pedal_option_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (pedal_area),
		UI_ATTR_FONT_TYPE (/*UI_FONT_THICK_ITALIC_ARIAL_18*/UI_FONT_ITALIC_ARIAL_14),
		UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
		UI_ATTR_VIRTUAL_POSITION (get_ui_object_x_end (change_array [i]) + OPTION_BUTTON_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_pedal_option_button),
		UI_ATTR_RIGHT_FUNCTION (notify_pedal_option_button_right),	// Retro 28Aug2004
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], pedal_option_button, option_pedal_text, 2, RESIZE_OPTION_CYCLE_BUTTON);

#if 0  //Retro10Jul2004_dead
	//device button
	
	i++;

	change_array[i] = device_graphic_area = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (device_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [i]) + get_ui_object_x_size_end (title_change_array [i]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_LARGE_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

   device_option_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (device_area),
		UI_ATTR_FONT_TYPE (/*UI_FONT_THICK_ITALIC_ARIAL_18*/UI_FONT_ITALIC_ARIAL_14),
		UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
		UI_ATTR_VIRTUAL_POSITION (get_ui_object_x_end (change_array [i]) + OPTION_BUTTON_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_device_option_button),
		UI_ATTR_END
	);
#endif  //Retro10Jul2004_dead

   // Retro 10Jul2004
   // eo pan x button
	
	i++;

	change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (eo_pan_x_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [i]) + get_ui_object_x_size_end (title_change_array [i]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_EXTRA_LARGE_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

   eo_pan_x_option_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (eo_pan_x_area),
		UI_ATTR_FONT_TYPE (/*UI_FONT_THICK_ITALIC_ARIAL_18*/UI_FONT_ITALIC_ARIAL_14),
		UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
		UI_ATTR_VIRTUAL_POSITION (get_ui_object_x_end (change_array [i]) + OPTION_BUTTON_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_eo_pan_x_option_button),
		UI_ATTR_RIGHT_FUNCTION (notify_eo_pan_x_option_button_right),	// Retro 28Aug2004
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], eo_pan_x_option_button, option_pedal_text, 2, RESIZE_OPTION_CYCLE_BUTTON);
	// Retro 10Jul2004 end

	// Retro 10Jul2004
	// eo pan y button
	
	i++;

	change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (eo_pan_y_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [i]) + get_ui_object_x_size_end (title_change_array [i]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_EXTRA_LARGE_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

   eo_pan_y_option_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (eo_pan_y_area),
		UI_ATTR_FONT_TYPE (/*UI_FONT_THICK_ITALIC_ARIAL_18*/UI_FONT_ITALIC_ARIAL_14),
		UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
		UI_ATTR_VIRTUAL_POSITION (get_ui_object_x_end (change_array [i]) + OPTION_BUTTON_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_eo_pan_y_option_button),
		UI_ATTR_RIGHT_FUNCTION (notify_eo_pan_y_option_button_right),	// Retro 28Aug2004
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], eo_pan_y_option_button, option_pedal_text, 2, RESIZE_OPTION_CYCLE_BUTTON);
	// Retro 10Jul2004 end

	// Retro 10Jul2004
	// eo zoom button
	
	i++;

	change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (eo_zoom_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [i]) + get_ui_object_x_size_end (title_change_array [i]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_EXTRA_LARGE_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

   eo_zoom_option_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (eo_zoom_area),
		UI_ATTR_FONT_TYPE (/*UI_FONT_THICK_ITALIC_ARIAL_18*/UI_FONT_ITALIC_ARIAL_14),
		UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
		UI_ATTR_VIRTUAL_POSITION (get_ui_object_x_end (change_array [i]) + OPTION_BUTTON_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_eo_zoom_option_button),
		UI_ATTR_RIGHT_FUNCTION (notify_eo_zoom_option_button_right),	// Retro 28Aug2004
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], eo_zoom_option_button, option_pedal_text, 2, RESIZE_OPTION_CYCLE_BUTTON);
	// Retro 10Jul2004 end

	// Retro 10Jul2004
	// joylook x button
	
	i++;

	change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (joylook_x_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [i]) + get_ui_object_x_size_end (title_change_array [i]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_EXTRA_LARGE_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

   joylook_x_option_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (joylook_x_area),
		UI_ATTR_FONT_TYPE (/*UI_FONT_THICK_ITALIC_ARIAL_18*/UI_FONT_ITALIC_ARIAL_14),
		UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
		UI_ATTR_VIRTUAL_POSITION (get_ui_object_x_end (change_array [i]) + OPTION_BUTTON_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_joylook_x_option_button),
		UI_ATTR_RIGHT_FUNCTION (notify_joylook_x_option_button_right),	// Retro 28Aug2004
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], joylook_x_option_button, option_pedal_text, 2, RESIZE_OPTION_CYCLE_BUTTON);
	// Retro 10Jul2004 end

	// Retro 10Jul2004
	// joylook y button
	
	i++;

	change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (joylook_y_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [i]) + get_ui_object_x_size_end (title_change_array [i]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_EXTRA_LARGE_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_large),
		UI_ATTR_END
	);

   joylook_y_option_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (joylook_y_area),
		UI_ATTR_FONT_TYPE (/*UI_FONT_THICK_ITALIC_ARIAL_18*/UI_FONT_ITALIC_ARIAL_14),
		UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
		UI_ATTR_VIRTUAL_POSITION (get_ui_object_x_end (change_array [i]) + OPTION_BUTTON_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_joylook_y_option_button),
		UI_ATTR_RIGHT_FUNCTION (notify_joylook_y_option_button_right),	// Retro 28Aug2004
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], joylook_y_option_button, option_pedal_text, 2, RESIZE_OPTION_CYCLE_BUTTON);
	// Retro 10Jul2004 end

	//reverse throttle button
	
	i++;

	change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (reverse_throttle_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [i]) + get_ui_object_x_size_end (title_change_array [i]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_SMALL_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_small),
		UI_ATTR_END
	);

   reverse_throttle_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (reverse_throttle_area),
		UI_ATTR_FONT_TYPE (/*UI_FONT_THICK_ITALIC_ARIAL_18*/UI_FONT_ITALIC_ARIAL_14),
		UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
		UI_ATTR_VIRTUAL_POSITION (get_ui_object_x_end (change_array [i]) + OPTION_BUTTON_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_reverse_throttle_option_button),
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], reverse_throttle_button, option_boolean_text, 2, RESIZE_OPTION_CYCLE_BUTTON);

	// Retro 17Jul2004
	// reverse pedal button
	
	i++;

	change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (reverse_pedal_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [i]) + get_ui_object_x_size_end (title_change_array [i]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_SMALL_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START ( 255, 255, 255, 0 ),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_small),
		UI_ATTR_END
	);

   reverse_pedal_option_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (reverse_pedal_area),
		UI_ATTR_FONT_TYPE (/*UI_FONT_THICK_ITALIC_ARIAL_18*/UI_FONT_ITALIC_ARIAL_14),
		UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
		UI_ATTR_VIRTUAL_POSITION (get_ui_object_x_end (change_array [i]) + OPTION_BUTTON_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_reverse_pedal_option_button),
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], keyboard_assist_option_button, option_boolean_text, 2, RESIZE_OPTION_CYCLE_BUTTON);
	// Retro 17Jul2004 end

	// Retro 10Jul2004
	//mouselook button
	
	i++;

	change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (mouselook_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [i]) + get_ui_object_x_size_end (title_change_array [i]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_SMALL_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_small),
		UI_ATTR_END
	);

   mouselook_option_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (mouselook_area),
		UI_ATTR_FONT_TYPE (/*UI_FONT_THICK_ITALIC_ARIAL_18*/UI_FONT_ITALIC_ARIAL_14),
		UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
		UI_ATTR_VIRTUAL_POSITION (get_ui_object_x_end (change_array [i]) + OPTION_BUTTON_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_mouselook_option_button),
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], mouselook_option_button, option_boolean_text, 2, RESIZE_OPTION_CYCLE_BUTTON);
	// Retro 10Jul2004 end

	// Retro 10Jul2004
	//trackir button
	
	i++;

	change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (trackir_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [i]) + get_ui_object_x_size_end (title_change_array [i]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_SMALL_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 0),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_small),
		UI_ATTR_END
	);

   trackir_option_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (trackir_area),
		UI_ATTR_FONT_TYPE (/*UI_FONT_THICK_ITALIC_ARIAL_18*/UI_FONT_ITALIC_ARIAL_14),
		UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
		UI_ATTR_VIRTUAL_POSITION (get_ui_object_x_end (change_array [i]) + OPTION_BUTTON_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_trackir_option_button),
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], trackir_option_button, option_boolean_text, 2, RESIZE_OPTION_CYCLE_BUTTON);
	// Retro 10Jul2004 end

	// Retro 17 Jul2004
	// Shamelessly copied from OP_INSND.C
	// Joystick Look Sensitivity Controls ( "+ 30 -" or such)
	//
	
	create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (joylook_sensitivity_area),
		UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
		UI_ATTR_VIRTUAL_SIZE (0.33f, 1.0),
		UI_ATTR_TEXT ("-"),
		UI_ATTR_FUNCTION (notify_joylook_sensitivity_down_button),
		UI_ATTR_FONT_TYPE (/*UI_FONT_THICK_ARIAL_18*/UI_FONT_ARIAL_14),
	    UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
   	UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
	    UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
   	UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_END
	);

	create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (joylook_sensitivity_area),
		UI_ATTR_VIRTUAL_POSITION (0.67f, 0.0),
		UI_ATTR_VIRTUAL_SIZE (0.33f, 1.0),
		UI_ATTR_TEXT ("+"),
		UI_ATTR_FONT_TYPE (/*UI_FONT_THICK_ARIAL_18*/UI_FONT_ARIAL_14),
	    UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
   	UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
	    UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
   	UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_FUNCTION (notify_joylook_sensitivity_up_button),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_END
	);

	create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (joylook_sensitivity_area),
		UI_ATTR_VIRTUAL_POSITION (0.33f, 0.0),
		UI_ATTR_VIRTUAL_SIZE (0.34, 1.0),
		UI_ATTR_TEXT (""),
		UI_ATTR_FONT_TYPE (/*UI_FONT_THICK_ARIAL_18*/UI_FONT_ARIAL_14),
		UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
		UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_DRAW_FUNCTION (draw_joylook_sensitivity),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_END
	);

	// Retro 17Jul2004 end

	// Retro 28Aug2004
	create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (autoconfigure_area),
		UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
		UI_ATTR_VIRTUAL_SIZE (1.0, 1.0),
		UI_ATTR_TEXT (get_trans ("Autoconfigure")),
		UI_ATTR_FUNCTION (notify_autoconfigure_button),
		UI_ATTR_FONT_TYPE (/*UI_FONT_THICK_ARIAL_18*/UI_FONT_ARIAL_14),
	    UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
   	UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
	    UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
   	UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_END
	);
	// Retro 28Aug2004 end

	// Retro 17 Jul2004
	// Shamelessly copied from OP_INSND.C
	// Mouselook Sensitivity Controls ( "+ 30 -" or such)
	//
	
	create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (mouselook_sensitivity_area),
		UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
		UI_ATTR_VIRTUAL_SIZE (0.33f, 1.0),
		UI_ATTR_TEXT ("-"),
		UI_ATTR_FUNCTION (notify_mouselook_sensitivity_down_button),
		UI_ATTR_FONT_TYPE (/*UI_FONT_THICK_ARIAL_18*/UI_FONT_ARIAL_14),
	    UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
   	UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
	    UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
   	UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_END
	);

	create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (mouselook_sensitivity_area),
		UI_ATTR_VIRTUAL_POSITION (0.67f, 0.0),
		UI_ATTR_VIRTUAL_SIZE (0.33f, 1.0),
		UI_ATTR_TEXT ("+"),
		UI_ATTR_FONT_TYPE (/*UI_FONT_THICK_ARIAL_18*/UI_FONT_ARIAL_14),
	    UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
   	UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
	    UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
   	UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_FUNCTION (notify_mouselook_sensitivity_up_button),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_END
	);

	create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (mouselook_sensitivity_area),
		UI_ATTR_VIRTUAL_POSITION (0.33f, 0.0),
		UI_ATTR_VIRTUAL_SIZE (0.34, 1.0),
		UI_ATTR_TEXT (""),
		UI_ATTR_FONT_TYPE (/*UI_FONT_THICK_ARIAL_18*/UI_FONT_ARIAL_14),
		UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
		UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_DRAW_FUNCTION (draw_mouselook_sensitivity),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_END
	);

	// Retro 17Jul2004 end

	// keyboard_assist button
	
	i++;

	change_array[i] = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (keyboard_assist_area),
		UI_ATTR_VIRTUAL_POSITION ((get_ui_object_x_end (title_change_array [i]) + get_ui_object_x_size_end (title_change_array [i]) + OPTION_BOX_GAP_WIDTH), 0.0),
		UI_ATTR_VIRTUAL_SIZE (OPTION_BOX_SMALL_WIDTH, OPTION_BOX_HEIGHT),
		UI_ATTR_COLOUR_START ( 255, 255, 255, 0 ),
		UI_ATTR_COLOUR_END ( 255, 255, 255, 255 ),
		UI_ATTR_TEXTURE_GRAPHIC (options_box_small),
		UI_ATTR_END
	);

   keyboard_assist_option_button = create_ui_object
	(
		UI_TYPE_TEXT,
		UI_ATTR_PARENT (keyboard_assist_area),
		UI_ATTR_FONT_TYPE (/*UI_FONT_THICK_ITALIC_ARIAL_18*/UI_FONT_ITALIC_ARIAL_14),
		UI_ATTR_FONT_COLOUR (254, 124, 47, 255),
		UI_ATTR_VIRTUAL_POSITION (get_ui_object_x_end (change_array [i]) + OPTION_BUTTON_TEXT_OFFSET_X, OPTION_BOX_TEXT_OFFSET_Y),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		UI_ATTR_TEXT (""),
      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
		UI_ATTR_HIGHLIGHTABLE (TRUE),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
		UI_ATTR_FUNCTION (notify_keyboard_assist_option_button),
		UI_ATTR_END
	);

	preprocess_translation_object_size (change_array [i], keyboard_assist_option_button, option_boolean_text, 2, RESIZE_OPTION_CYCLE_BUTTON);

	recursively_set_object_time (page, OPTIONS_BUTTON_AREA_FADE_TIME, OPTIONS_BUTTON_AREA_OFFSET_TIME);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_cyclic_option_button ( ui_object *obj, void *arg )
{
#if 0 // Retro 10Jul2004
	if ( (number_of_joystick_devices) && (get_global_cyclic_input () == KEYBOARD_INPUT) )
	{
			set_global_cyclic_input (JOYSTICK_INPUT);
			
			set_ui_object_text (cyclic_option_button, option_joystick_text[1]);
	}
	else
	{
		set_global_cyclic_input (KEYBOARD_INPUT);

		set_ui_object_text (cyclic_option_button, option_joystick_text[0]);
	}
#else
	int AxisInfoIndex;
	int oldCyclicDevice = command_line_cyclic_joystick_index;

	AxisInfoIndex = findNextUnusedAxis(command_line_cyclic_joystick_index,command_line_cyclic_joystick_x_axis);

	command_line_cyclic_joystick_index = AxisInfo[AxisInfoIndex].device;
	command_line_cyclic_joystick_x_axis = AxisInfo[AxisInfoIndex].axis;

	if (command_line_cyclic_joystick_index == -1)
	{
		set_global_cyclic_input (KEYBOARD_INPUT);
//R		set_global_joystick_device_index(-1);
	}
	else
	{
		set_global_cyclic_input (JOYSTICK_INPUT);
//R		set_global_joystick_device_index(command_line_cyclic_joystick_index);
	}

	set_ui_object_text (cyclic_option_button, AxisInfo[AxisInfoIndex].AxisName);

	if (command_line_cyclic_joystick_index != oldCyclicDevice)
	{
		set_ui_object_text (cyclic_y_option_button, option_joystick_text[0]);
		setAxisUnused(oldCyclicDevice,command_line_cyclic_joystick_y_axis);
		command_line_cyclic_joystick_y_axis = -1;
	}
#endif  // Retro 10Jul2004

	// don't leave text selected

	set_toggle_button_off (obj);
}

void notify_cyclic_option_button_right ( ui_object *obj, void *arg )	// Retro 28Aug2004
{
	int AxisInfoIndex;
	int oldCyclicDevice = command_line_cyclic_joystick_index;

	AxisInfoIndex = findPreviousUnusedAxis(command_line_cyclic_joystick_index,command_line_cyclic_joystick_x_axis);

	command_line_cyclic_joystick_index = AxisInfo[AxisInfoIndex].device;
	command_line_cyclic_joystick_x_axis = AxisInfo[AxisInfoIndex].axis;

	if (command_line_cyclic_joystick_index == -1)
	{
		set_global_cyclic_input (KEYBOARD_INPUT);
	}
	else
	{
		set_global_cyclic_input (JOYSTICK_INPUT);
	}
	if (command_line_cyclic_joystick_index != oldCyclicDevice)
	{
		set_ui_object_text (cyclic_y_option_button, option_joystick_text[0]);
		setAxisUnused(oldCyclicDevice,command_line_cyclic_joystick_y_axis);
		command_line_cyclic_joystick_y_axis = -1;
	}

	// ugh
	notify_show_controller_page ();

	// don't leave text selected
	set_toggle_button_off (obj);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_cyclic_y_option_button ( ui_object *obj, void *arg )
{
	int AxisInfoIndex;

	AxisInfoIndex = findNextUnusedDeviceAxis(command_line_cyclic_joystick_index,command_line_cyclic_joystick_y_axis);

	command_line_cyclic_joystick_y_axis = AxisInfo[AxisInfoIndex].axis;

/*	if (command_line_cyclic_joystick_index == -1)
		set_global_cyclic_input (KEYBOARD_INPUT);
	else
		set_global_cyclic_input (JOYSTICK_INPUT);*/

	set_ui_object_text (cyclic_y_option_button, AxisInfo[AxisInfoIndex].AxisName);

	// don't leave text selected

	set_toggle_button_off (obj);
}

void notify_cyclic_y_option_button_right ( ui_object *obj, void *arg )	// Retro 28Aug2004
{
	int AxisInfoIndex;

	AxisInfoIndex = findPreviousUnusedDeviceAxis(command_line_cyclic_joystick_index,command_line_cyclic_joystick_y_axis);

	command_line_cyclic_joystick_y_axis = AxisInfo[AxisInfoIndex].axis;

	set_ui_object_text (cyclic_y_option_button, AxisInfo[AxisInfoIndex].AxisName);

	// ugh
	notify_show_controller_page ();

	// don't leave text selected
	set_toggle_button_off (obj);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_collective_option_button ( ui_object *obj, void *arg )
{
#if 0 // Retro 10Jul2004
	if ( (number_of_joystick_devices) && (get_global_collective_input () == KEYBOARD_INPUT) )
	{
			set_global_collective_input (THROTTLE_INPUT);
			
			set_ui_object_text (collective_option_button, option_throttle_text[1]);
	}
	else
	{
		set_global_collective_input (KEYBOARD_INPUT);
		
		set_ui_object_text (collective_option_button, option_throttle_text[0]);
	}
#else // Retro 10Jul2004
	int
		AxisInfoIndex;

	AxisInfoIndex = findNextUnusedAxis(command_line_collective_joystick_index,command_line_collective_joystick_axis);

	command_line_collective_joystick_index = AxisInfo[AxisInfoIndex].device;
	command_line_collective_joystick_axis = AxisInfo[AxisInfoIndex].axis;

	if (command_line_collective_joystick_index == -1)
		set_global_collective_input (KEYBOARD_INPUT);
	else
		set_global_collective_input (THROTTLE_INPUT);

	set_ui_object_text (collective_option_button, AxisInfo[AxisInfoIndex].AxisName);
	
#endif // Retro 10Jul2004

	// don't leave text selected

	set_toggle_button_off (obj);
}

void notify_collective_option_button_right ( ui_object *obj, void *arg )	// Retro 28Aug2004
{
	int
		AxisInfoIndex;

	AxisInfoIndex = findPreviousUnusedAxis(command_line_collective_joystick_index,command_line_collective_joystick_axis);

	command_line_collective_joystick_index = AxisInfo[AxisInfoIndex].device;
	command_line_collective_joystick_axis = AxisInfo[AxisInfoIndex].axis;

	if (command_line_collective_joystick_index == -1)
		set_global_collective_input (KEYBOARD_INPUT);
	else
		set_global_collective_input (THROTTLE_INPUT);

	set_ui_object_text (collective_option_button, AxisInfo[AxisInfoIndex].AxisName);

	// ugh
	notify_show_controller_page ();

	// don't leave text selected
	set_toggle_button_off (obj);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_pedal_option_button ( ui_object *obj, void *arg )
{
#if 0 // Retro 10Jul2004
	if ( (number_of_joystick_devices) && (get_global_pedal_input () == KEYBOARD_INPUT) )
	{
			set_global_pedal_input (RUDDER_INPUT);
			
			set_ui_object_text (pedal_option_button, option_pedal_text[1]);
	}
	else
	{
		set_global_pedal_input (KEYBOARD_INPUT);
		
		set_ui_object_text (pedal_option_button, option_pedal_text[0]);
	}
#else // Retro 10Jul2004
	int
		AxisInfoIndex;

	AxisInfoIndex = findNextUnusedAxis(command_line_rudder_joystick_index,command_line_rudder_joystick_axis);

	command_line_rudder_joystick_index = AxisInfo[AxisInfoIndex].device;
	command_line_rudder_joystick_axis = AxisInfo[AxisInfoIndex].axis;

	if (command_line_rudder_joystick_index == -1)
	{
		set_global_pedal_input (KEYBOARD_INPUT);
		set_ui_object_text (reverse_pedal_option_button, option_boolean_text [FALSE]);
	}
	else
	{
		set_global_pedal_input (RUDDER_INPUT);
		set_ui_object_text (reverse_pedal_option_button, option_boolean_text [command_line_reverse_pedal]);
	}

	set_ui_object_text (pedal_option_button, AxisInfo[AxisInfoIndex].AxisName);
#endif // Retro 10Jul2004

	// don't leave text selected

	set_toggle_button_off (obj);
}

void notify_pedal_option_button_right ( ui_object *obj, void *arg )	// Retro 28Aug2004
{
	int
		AxisInfoIndex;

	AxisInfoIndex = findPreviousUnusedAxis(command_line_rudder_joystick_index,command_line_rudder_joystick_axis);

	command_line_rudder_joystick_index = AxisInfo[AxisInfoIndex].device;
	command_line_rudder_joystick_axis = AxisInfo[AxisInfoIndex].axis;

	if (command_line_rudder_joystick_index == -1)
	{
		set_global_pedal_input (KEYBOARD_INPUT);
		set_ui_object_text (reverse_pedal_option_button, option_boolean_text [FALSE]);
	}
	else
	{
		set_global_pedal_input (RUDDER_INPUT);
		set_ui_object_text (reverse_pedal_option_button, option_boolean_text [command_line_reverse_pedal]);
	}

	set_ui_object_text (pedal_option_button, AxisInfo[AxisInfoIndex].AxisName);

	// ugh
	notify_show_controller_page ();

	// don't leave text selected
	set_toggle_button_off (obj);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0  //Retro10Jul2004_dead
void notify_device_option_button ( ui_object *obj, void *arg )
{
	const char
		*name[1];

	if (number_of_joystick_devices > 1)
	{
		if ( get_global_joystick_device_index () < (number_of_joystick_devices - 1) )
		{
			set_global_joystick_device_index (get_global_joystick_device_index () + 1);
		}
		else
		{
			set_global_joystick_device_index (0);
		}

		set_ui_object_text (device_option_button, joystick_devices[get_global_joystick_device_index ()].device_name);

		name[0] = &joystick_devices[get_global_joystick_device_index ()].device_name;

		preprocess_translation_object_size (device_graphic_area, device_option_button, name, 1, RESIZE_OPTION_CYCLE_BUTTON);
	}

	// don't leave text selected

	set_toggle_button_off (obj);
	
	#if DEBUG_MODULE
		debug_filtered_log ("no. jd's:%d  jd index:%d", number_of_joystick_devices, get_global_joystick_device_index ());
	#endif
	
}
#endif  //Retro10Jul2004_dead

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_eo_pan_x_option_button ( ui_object *obj, void *arg )
{
	int
		AxisInfoIndex,
		oldEOPanDevice;

	oldEOPanDevice = command_line_eo_pan_joystick_index;

	AxisInfoIndex = findNextUnusedAxis(command_line_eo_pan_joystick_index,command_line_eo_pan_horizontal_joystick_axis);

	command_line_eo_pan_joystick_index = AxisInfo[AxisInfoIndex].device;
	command_line_eo_pan_horizontal_joystick_axis = AxisInfo[AxisInfoIndex].axis;

	set_ui_object_text (eo_pan_x_option_button, AxisInfo[AxisInfoIndex].AxisName);

	if (command_line_eo_pan_joystick_index != oldEOPanDevice)
	{
		set_ui_object_text (eo_pan_y_option_button, option_joystick_text[0]);
		setAxisUnused(oldEOPanDevice,command_line_eo_pan_vertical_joystick_axis);
		command_line_eo_pan_vertical_joystick_axis = -1;
	}

	// don't leave text selected

	set_toggle_button_off (obj);
}

void notify_eo_pan_x_option_button_right ( ui_object *obj, void *arg )	// Retro 28Aug2004
{
	int
		AxisInfoIndex,
		oldEOPanDevice;

	oldEOPanDevice = command_line_eo_pan_joystick_index;

	AxisInfoIndex = findPreviousUnusedAxis(command_line_eo_pan_joystick_index,command_line_eo_pan_horizontal_joystick_axis);

	command_line_eo_pan_joystick_index = AxisInfo[AxisInfoIndex].device;
	command_line_eo_pan_horizontal_joystick_axis = AxisInfo[AxisInfoIndex].axis;

	set_ui_object_text (eo_pan_x_option_button, AxisInfo[AxisInfoIndex].AxisName);

	if (command_line_eo_pan_joystick_index != oldEOPanDevice)
	{
		set_ui_object_text (eo_pan_y_option_button, option_joystick_text[0]);
		setAxisUnused(oldEOPanDevice,command_line_eo_pan_vertical_joystick_axis);
		command_line_eo_pan_vertical_joystick_axis = -1;
	}

	// ugh
	notify_show_controller_page ();

	// don't leave text selected
	set_toggle_button_off (obj);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_eo_pan_y_option_button ( ui_object *obj, void *arg )
{
	int
		AxisInfoIndex;

	AxisInfoIndex = findNextUnusedDeviceAxis(command_line_eo_pan_joystick_index,command_line_eo_pan_vertical_joystick_axis);

	command_line_eo_pan_vertical_joystick_axis = AxisInfo[AxisInfoIndex].axis;

	set_ui_object_text (eo_pan_y_option_button, AxisInfo[AxisInfoIndex].AxisName);

	// don't leave text selected

	set_toggle_button_off (obj);
}

void notify_eo_pan_y_option_button_right ( ui_object *obj, void *arg )	// Retro 28Aug2004
{
	int
		AxisInfoIndex;

	AxisInfoIndex = findPreviousUnusedDeviceAxis(command_line_eo_pan_joystick_index,command_line_eo_pan_vertical_joystick_axis);

	command_line_eo_pan_vertical_joystick_axis = AxisInfo[AxisInfoIndex].axis;

	set_ui_object_text (eo_pan_y_option_button, AxisInfo[AxisInfoIndex].AxisName);

	// ugh
	notify_show_controller_page ();

	// don't leave text selected
	set_toggle_button_off (obj);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_eo_zoom_option_button ( ui_object *obj, void *arg )
{
	int
		AxisInfoIndex;

	AxisInfoIndex = findNextUnusedAxis(command_line_eo_zoom_joystick_index,command_line_eo_zoom_joystick_axis);

	command_line_eo_zoom_joystick_index = AxisInfo[AxisInfoIndex].device;
	command_line_eo_zoom_joystick_axis = AxisInfo[AxisInfoIndex].axis;

	set_ui_object_text (eo_zoom_option_button, AxisInfo[AxisInfoIndex].AxisName);

	// don't leave text selected

	set_toggle_button_off (obj);
}

void notify_eo_zoom_option_button_right ( ui_object *obj, void *arg )	// Retro 28Aug2004
{
	int
		AxisInfoIndex;

	AxisInfoIndex = findPreviousUnusedAxis(command_line_eo_zoom_joystick_index,command_line_eo_zoom_joystick_axis);

	command_line_eo_zoom_joystick_index = AxisInfo[AxisInfoIndex].device;
	command_line_eo_zoom_joystick_axis = AxisInfo[AxisInfoIndex].axis;

	set_ui_object_text (eo_zoom_option_button, AxisInfo[AxisInfoIndex].AxisName);

	// ugh
	notify_show_controller_page ();

	// don't leave text selected
	set_toggle_button_off (obj);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_joylook_x_option_button ( ui_object *obj, void *arg )
{
	int
		AxisInfoIndex,
		oldJoyLookDevice;
	
	oldJoyLookDevice = command_line_joylook_joystick_index;

	AxisInfoIndex = findNextUnusedAxis(command_line_joylook_joystick_index,command_line_joylookh_joystick_axis);

	command_line_joylook_joystick_index = AxisInfo[AxisInfoIndex].device;
	command_line_joylookh_joystick_axis = AxisInfo[AxisInfoIndex].axis;

	set_ui_object_text (joylook_x_option_button, AxisInfo[AxisInfoIndex].AxisName);

	if (command_line_joylook_joystick_index != oldJoyLookDevice)
	{
		set_ui_object_text (joylook_y_option_button, option_joystick_text[0]);
		setAxisUnused(oldJoyLookDevice,command_line_joylookv_joystick_axis);
		command_line_joylookv_joystick_axis = -1;
	}

	// mouselook would override joystick look, so deactivate that
	if ((command_line_mouse_look != MOUSELOOK_OFF)&&(command_line_joylook_joystick_index != -1))
	{
		command_line_mouse_look = MOUSELOOK_OFF;
//		set_ui_object_text (mouselook_option_button, option_boolean_text [0]);
		set_ui_object_text (mouselook_option_button, option_mouselook_text [command_line_mouse_look]);
		setTrackIRButton (FALSE);
	}

	// don't leave text selected

	set_toggle_button_off (obj);
}

void notify_joylook_x_option_button_right ( ui_object *obj, void *arg )	// Retro 28Aug2004
{
	int
		AxisInfoIndex,
		oldJoyLookDevice;
	
	oldJoyLookDevice = command_line_joylook_joystick_index;

	AxisInfoIndex = findPreviousUnusedAxis(command_line_joylook_joystick_index,command_line_joylookh_joystick_axis);

	command_line_joylook_joystick_index = AxisInfo[AxisInfoIndex].device;
	command_line_joylookh_joystick_axis = AxisInfo[AxisInfoIndex].axis;

	set_ui_object_text (joylook_x_option_button, AxisInfo[AxisInfoIndex].AxisName);

	if (command_line_joylook_joystick_index != oldJoyLookDevice)
	{
		set_ui_object_text (joylook_y_option_button, option_joystick_text[0]);
		setAxisUnused(oldJoyLookDevice,command_line_joylookv_joystick_axis);
		command_line_joylookv_joystick_axis = -1;
	}

	// mouselook would override joystick look, so deactivate that
	if ((command_line_mouse_look != MOUSELOOK_OFF)&&(command_line_joylook_joystick_index != -1))
	{
		command_line_mouse_look = MOUSELOOK_OFF;
//		set_ui_object_text (mouselook_option_button, option_boolean_text [0]);
		set_ui_object_text (mouselook_option_button, option_mouselook_text [command_line_mouse_look]);
		setTrackIRButton (FALSE);
	}

	// ugh
	notify_show_controller_page ();

	// don't leave text selected
	set_toggle_button_off (obj);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_joylook_y_option_button ( ui_object *obj, void *arg )
{
	int
		AxisInfoIndex;

	AxisInfoIndex = findNextUnusedDeviceAxis(command_line_joylook_joystick_index,command_line_joylookv_joystick_axis);

	command_line_joylookv_joystick_axis = AxisInfo[AxisInfoIndex].axis;

	set_ui_object_text (joylook_y_option_button, AxisInfo[AxisInfoIndex].AxisName);

	// don't leave text selected

	set_toggle_button_off (obj);
}

void notify_joylook_y_option_button_right ( ui_object *obj, void *arg )	// Retro 28Aug2004
{
	int
		AxisInfoIndex;

	AxisInfoIndex = findPreviousUnusedDeviceAxis(command_line_joylook_joystick_index,command_line_joylookv_joystick_axis);

	command_line_joylookv_joystick_axis = AxisInfo[AxisInfoIndex].axis;

	set_ui_object_text (joylook_y_option_button, AxisInfo[AxisInfoIndex].AxisName);

	// ugh
	notify_show_controller_page ();

	// don't leave text selected
	set_toggle_button_off (obj);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setTrackIRButton ( int selection )
{
#if 0
	if (selection == TRUE)	// set to ON
	{
		if (query_TIR_active () == TRUE)
		{
			set_ui_object_text (trackir_option_button, get_trans ("Running") ) ;
		}
		else
			set_ui_object_text (trackir_option_button, option_boolean_text [0]);
	}
	else
	{
		if (query_TIR_active () == TRUE)
		{
			set_ui_object_text (trackir_option_button, get_trans ("Enable Mouselook") );
		}
		else
			set_ui_object_text (trackir_option_button, option_boolean_text [0]);
	}
#else
	TIR_Poll();	// Retro 6Feb2005

	if (query_TIR_active() == TRUE)
	{
		if (selection == TRUE)
			set_ui_object_text (trackir_option_button, get_trans ("Running") );
		else
			set_ui_object_text (trackir_option_button, get_trans ("Enable Mouselook") );
	}
	else
		set_ui_object_text (trackir_option_button, option_boolean_text [0]);
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_mouselook_option_button ( ui_object *obj, void *arg )
{
#if 0
	int
		selection;

	selection = !command_line_mouse_look;

	command_line_mouse_look = !command_line_mouse_look;

	// mouselook overrides joystick look, so deactivate this
	if (command_line_mouse_look == TRUE)
	{
		set_ui_object_text (joylook_x_option_button, option_joystick_text[0]);
		set_ui_object_text (joylook_y_option_button, option_joystick_text[0]);

		setAxisUnused(command_line_joylook_joystick_index,command_line_joylookh_joystick_axis);
		setAxisUnused(command_line_joylook_joystick_index,command_line_joylookv_joystick_axis);

		command_line_joylook_joystick_index = -1;
		command_line_joylookv_joystick_axis = -1;
		command_line_joylookh_joystick_axis = -1;

		setTrackIRButton (TRUE);
	}
	else
		setTrackIRButton (FALSE);

	set_ui_object_text (mouselook_option_button, option_boolean_text [selection]);
#else
	command_line_mouse_look++;
	command_line_mouse_look %= MOUSELOOK_MAX;

	if (command_line_mouse_look != MOUSELOOK_OFF)
	{
		set_ui_object_text (joylook_x_option_button, option_joystick_text[0]);
		set_ui_object_text (joylook_y_option_button, option_joystick_text[0]);

		setAxisUnused(command_line_joylook_joystick_index,command_line_joylookh_joystick_axis);
		setAxisUnused(command_line_joylook_joystick_index,command_line_joylookv_joystick_axis);

		command_line_joylook_joystick_index = -1;
		command_line_joylookv_joystick_axis = -1;
		command_line_joylookh_joystick_axis = -1;

		setTrackIRButton (TRUE);
	}
	else
		setTrackIRButton (FALSE);

	set_ui_object_text (mouselook_option_button, option_mouselook_text [command_line_mouse_look]);
#endif
	// don't leave text selected

	set_toggle_button_off (obj);

	#ifdef DEBUG_MODULE
		debug_filtered_log ("mouselook: %d", command_line_mouse_look);
	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_trackir_option_button ( ui_object *obj, void *arg )
{
#if 0	// Retro 11Jul2004 - debug stuff
	int i = 0;
	FILE* fp = fopen("stick.txt","wt");

	for (i = 0; i < AxisCount; i++)
	{
		fprintf(fp,"%i %i %i %s\n",AxisInfo[i].device, AxisInfo[i].axis, AxisInfo[i].inUse, AxisInfo[i].AxisName);
	}
	fprintf(fp,"\n");
	fprintf(fp,"%i\n",command_line_cyclic_joystick_index);
	fprintf(fp,"%i\n",command_line_cyclic_joystick_x_axis);
	fprintf(fp,"%i\n",command_line_cyclic_joystick_y_axis);
	fprintf(fp,"%i\n",command_line_collective_joystick_index);
	fprintf(fp,"%i\n",command_line_collective_joystick_axis);
	fprintf(fp,"%i\n",command_line_rudder_joystick_index);
	fprintf(fp,"%i\n",command_line_rudder_joystick_axis);
	fprintf(fp,"%i\n",command_line_joylook_joystick_index);
	fprintf(fp,"%i\n",command_line_joylookh_joystick_axis);
	fprintf(fp,"%i\n",command_line_joylookv_joystick_axis);
	fprintf(fp,"%i\n",command_line_eo_pan_joystick_index);
	fprintf(fp,"%i\n",command_line_eo_pan_vertical_joystick_axis);
	fprintf(fp,"%i\n",command_line_eo_pan_horizontal_joystick_axis);
	fprintf(fp,"%i\n",command_line_eo_zoom_joystick_index);
	fprintf(fp,"%i\n",command_line_eo_zoom_joystick_axis);
	fprintf(fp,"\n");
	fprintf(fp,"%i\n",get_global_joystick_device_index ());	// should be same as number_of_joystick_devices
	fprintf(fp,"%i\n",number_of_joystick_devices);
	fprintf(fp,"%i\n",global_options.cyclic_input);
	fprintf(fp,"%i\n",global_options.collective_input);
	fprintf(fp,"%i\n",global_options.pedal_input);
	fprintf(fp,"\n");

	for (i = 0; i < number_of_joystick_devices; i++)
	{
		fprintf(fp,"%i\n",joystick_devices[i].joystick_xaxis_valid);
		fprintf(fp,"%i\n",joystick_devices[i].joystick_yaxis_valid);
		fprintf(fp,"%i\n",joystick_devices[i].joystick_zaxis_valid);
		fprintf(fp,"%i\n",joystick_devices[i].joystick_rxaxis_valid);
		fprintf(fp,"%i\n",joystick_devices[i].joystick_ryaxis_valid);
		fprintf(fp,"%i\n",joystick_devices[i].joystick_rzaxis_valid);
		fprintf(fp,"%i\n",joystick_devices[i].joystick_slider0axis_valid);
		fprintf(fp,"%i\n",joystick_devices[i].joystick_slider1axis_valid);
		fprintf(fp,"--\n");
	}

	fclose(fp);
#endif	// Retro 11Jul2004

	// don't leave text selected

	set_toggle_button_off (obj);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_reverse_throttle_option_button ( ui_object *obj, void *arg )
{

	int
		selection;

	selection = !get_global_dynamics_options_reverse_throttle_input ();
	
	set_global_dynamics_options_reverse_throttle_input (selection);

	set_ui_object_text (reverse_throttle_button, option_boolean_text [selection]);

	set_current_dynamics_options (DYNAMICS_OPTIONS_REVERSE_THROTTLE_INPUT, get_global_dynamics_options_reverse_throttle_input());

	// don't leave text selected

	set_toggle_button_off (obj);

	#ifdef DEBUG_MODULE
		debug_filtered_log ("reverse throttle: %d", get_global_dynamics_options_reverse_throttle_input ());
	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_keyboard_assist_option_button ( ui_object *obj, void *arg )
{
	set_global_dynamics_options_keyboard_assistance (!get_global_dynamics_options_keyboard_assistance ());

	set_ui_object_text (keyboard_assist_option_button, option_boolean_text [get_global_dynamics_options_keyboard_assistance ()]);

	set_current_dynamics_options (DYNAMICS_OPTIONS_KEYBOARD_ASSISTANCE, get_global_dynamics_options_keyboard_assistance());

	// don't leave text selected

	set_toggle_button_off (obj);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_joylook_sensitivity_up_button ( ui_object *obj, void *arg )
{
	if (command_line_joylook_joystick_index == -1)
		return;

	if (command_line_joylook_step < 100)
		command_line_joylook_step++;
}
void notify_joylook_sensitivity_down_button ( ui_object *obj, void *arg )
{
	if (command_line_joylook_joystick_index == -1)
		return;

	if (command_line_joylook_step > 1)
		command_line_joylook_step--;
}

void draw_joylook_sensitivity ( ui_object *obj, void *arg )
{
	char
		s [8];

	ASSERT ((command_line_joylook_step > 0) && (command_line_joylook_step <= 100));

	sprintf (s, "%i", command_line_joylook_step);

	set_ui_object_text (obj, s);

	if (command_line_joylook_joystick_index == -1)
	{
		set_ui_object_font_colour (obj, ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, ui_option_text_default_colour.a);
	}
	else
	{
		set_ui_object_font_colour (obj, ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, ui_option_title_text_colour.a);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// These controls do not get grayed out when mouselook is disabled, as they then control POV sensitivity
void notify_mouselook_sensitivity_up_button ( ui_object *obj, void *arg )
{
	if (command_line_mouse_look_speed < 20)
		command_line_mouse_look_speed++;
}
void notify_mouselook_sensitivity_down_button ( ui_object *obj, void *arg )
{
	if (command_line_mouse_look_speed > 1)
		command_line_mouse_look_speed--;
}

void draw_mouselook_sensitivity ( ui_object *obj, void *arg )
{
	char
		s [8];

	ASSERT ((command_line_mouse_look_speed > 0) && (command_line_mouse_look_speed <= 20));

	sprintf (s, "%i", command_line_mouse_look_speed);

	set_ui_object_text (obj, s);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_reverse_pedal_option_button ( ui_object *obj, void *arg )
{
	if (command_line_rudder_joystick_index != -1)
	{
		command_line_reverse_pedal = !command_line_reverse_pedal;

		set_ui_object_text (reverse_pedal_option_button, option_boolean_text [command_line_reverse_pedal]);
	}

	// don't leave text selected

	set_toggle_button_off (obj);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MAX_PATH
#define MAX_PATH 260 // ugh
#endif

extern void GetGUIDString(const int iDevice, char* theString);	// Retro 28Aug2004

// in an ideal world those hardcoded mappings would be read from an .ini file
void notify_autoconfigure_button ( ui_object *obj, void *arg)
{
	char strGuid[MAX_PATH];

	// this variable lets the user cycle through all enumerated sticks.. at the end of the routine
	// it get´s increased by one.
static int iDevice = 0;

	// does nothing #ifndef WIN32
	GetGUIDString(iDevice,strGuid);
	
	if (!strGuid)
		return;

	//## Saitek X36 Flight Controller USB
	if (strcmp("{053F06A3-0000-0000-0000-504944564944}",strGuid) == 0)
	{
		resetJoystickMapping();

		set_global_collective_input ( THROTTLE_INPUT );
		set_global_cyclic_input ( JOYSTICK_INPUT );
		set_global_pedal_input ( RUDDER_INPUT );
		command_line_cyclic_joystick_index = iDevice;
		command_line_cyclic_joystick_x_axis = 0;
		command_line_cyclic_joystick_y_axis = 1;
		command_line_collective_joystick_index = iDevice;
		command_line_collective_joystick_axis = 6;
		command_line_rudder_joystick_index = iDevice;
		command_line_rudder_joystick_axis = 5;
	}
	// Logitech WingMan Force 3D USB
	else if (strcmp("{C283046D-0000-0000-0000-504944564944}",strGuid) == 0)
	{
		resetJoystickMapping();

		set_global_collective_input ( THROTTLE_INPUT );
		set_global_cyclic_input ( JOYSTICK_INPUT );
		set_global_pedal_input ( RUDDER_INPUT );
		command_line_cyclic_joystick_index = iDevice;
		command_line_cyclic_joystick_x_axis = 0;
		command_line_cyclic_joystick_y_axis = 1;
		command_line_collective_joystick_index = iDevice;
		command_line_collective_joystick_axis = 6;
		command_line_rudder_joystick_index = iDevice;
		command_line_rudder_joystick_axis = 5;
	}
	// Microsoft® SideWinder® Plug & Play Game Pad - although the sim is unflyable with this - imo
	else if (strcmp("{0027045E-0000-0000-0000-504944564944}",strGuid) == 0)
	{
		resetJoystickMapping();

		set_global_cyclic_input ( JOYSTICK_INPUT );
		command_line_cyclic_joystick_index = iDevice;
		command_line_cyclic_joystick_x_axis = 0;
		command_line_cyclic_joystick_y_axis = 1;
	}
	// Thrustmaster Top Gun® AfterBurner (USB)
	else if (strcmp("{B101044F-0000-0000-0000-504944564944}",strGuid) == 0)
	{
		resetJoystickMapping();

		set_global_collective_input ( THROTTLE_INPUT );
		set_global_cyclic_input ( JOYSTICK_INPUT );
		set_global_pedal_input ( RUDDER_INPUT );
		command_line_cyclic_joystick_index = iDevice;
		command_line_cyclic_joystick_x_axis = 0;
		command_line_cyclic_joystick_y_axis = 1;
		command_line_collective_joystick_index = iDevice;
		command_line_collective_joystick_axis = 6;
		command_line_rudder_joystick_index = iDevice;
		command_line_rudder_joystick_axis = 5;
	}
#if 0
	// Microsoft SideWinder Precision Racing Wheel
	else if (strcmp("{{001A045E-0000-0000-0000-504944564944}",strGuid) == 0)
	{
	}
#endif
	// Saitek X45 Flight Controller USB
	else if (strcmp("{053C06A3-0000-0000-0000-504944564944}",strGuid) == 0)
	{
		resetJoystickMapping();

		set_global_collective_input ( THROTTLE_INPUT );
		set_global_cyclic_input ( JOYSTICK_INPUT );
		set_global_pedal_input ( RUDDER_INPUT );
		command_line_cyclic_joystick_index = iDevice;
		command_line_cyclic_joystick_x_axis = 0;
		command_line_cyclic_joystick_y_axis = 1;
		command_line_collective_joystick_index = iDevice;
		command_line_collective_joystick_axis = 6;
		command_line_rudder_joystick_index = iDevice;
		command_line_rudder_joystick_axis = 5;
	}
	// Saitek Cyborg Evo
	else if (strcmp("{046406A3-0000-0000-0000-504944564944}",strGuid) == 0)
	{
		resetJoystickMapping();

		set_global_collective_input ( THROTTLE_INPUT );
		set_global_cyclic_input ( JOYSTICK_INPUT );
		set_global_pedal_input ( RUDDER_INPUT );
		command_line_cyclic_joystick_index = iDevice;
		command_line_cyclic_joystick_x_axis = 0;
		command_line_cyclic_joystick_y_axis = 1;
		command_line_collective_joystick_index = iDevice;
		command_line_collective_joystick_axis = 2;
		command_line_rudder_joystick_index = iDevice;
		command_line_rudder_joystick_axis = 5;
	}
	else	// no match, we do nothing and return
	{
		return;
	}

	// select next device next time this sub is executed
	// make sure we don´t get an out-of-bounds error
	iDevice++;
	iDevice = iDevice % number_of_joystick_devices;

	// redraw the whole screen with the new settings
	notify_show_controller_page ();
}
