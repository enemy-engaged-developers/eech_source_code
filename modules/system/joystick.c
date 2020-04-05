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

#include "cmndline.h"	// Retro 18Jul2004

#include <stdio.h> 

#include <stdlib.h>

#include "multi.h"

#ifndef OGRE_EE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE	0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

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

// Retro 10Jul2004
int AxisCount = 0;
AxisInfo_t AxisInfo[MAXIMUM_JOYSTICK_DEVICES*8];	// 8 axis per device in DIJOYSTATE, I don�t know why razorworks choose 32 (!!!) (DIJOYSTATE2 I guess, but that�s been never implemented)

#ifndef OGRE_EE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static BOOL FAR PASCAL enumerate_joystick_devices (LPCDIDEVICEINSTANCE device, LPVOID user_data);
static BOOL FAR PASCAL DIEnumEffectsProc(LPCDIEFFECTINFO pei, LPVOID pv);
static BOOL FAR PASCAL EnumEffectsInFileProc(LPCDIFILEEFFECT lpdife, LPVOID pv);
LPDIRECTINPUTEFFECT
	g_lpeffect,
	pEff[999];
#endif
LPDIRECTINPUTDEVICE7
	feedback_device = NULL;
#ifndef OGRE_EE
char
	filename[64];
static int
	eff_count = 0,
	ffb = 0;

  // Making list of ffe files

struct external_effects{
	char* name;
	struct external_effects *Next;
}*Head;

void add_eff(char* name)
 {
	struct external_effects *temp1, *temp2;

	temp1=(struct external_effects *)safe_malloc(sizeof(struct external_effects));
	memset (temp1, 0, sizeof (struct external_effects));
	temp1->name = (char *) safe_malloc ((strlen (name) + 1));
	sprintf (temp1->name, "%s", name);
	
	debug_log("node %s", name);

	if(Head == NULL)
	{
		Head = temp1;
		Head->Next=NULL;
	}
	else
	{
	temp2 = Head;
		while(temp2->Next != NULL)
		temp2=temp2->Next;

		temp1->Next=NULL;
		temp2->Next=temp1;
	}
 }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Retro 12Dez2004 - however this solution is only a bandaid as it is only applied in the initialise routine
// ...the user has to restart the sim for the settings to take effect !!
static BOOL axis_has_deadzone ( const int deviceIndex, const int deviceAxis )
{
	BOOL retval;

	if ((deviceIndex == command_line_eo_zoom_joystick_index) && (deviceAxis == command_line_eo_zoom_joystick_axis))
	{
		retval = FALSE;
	}
	else if ((deviceIndex == command_line_collective_joystick_index) && (deviceAxis == command_line_collective_joystick_axis))
	{
		retval = FALSE;
	}
	else if ((deviceIndex == command_line_throttle_joystick_index) && (deviceAxis == command_line_throttle_joystick_axis))
	{
		retval = FALSE;
	}
	else if ((deviceIndex == command_line_field_of_view_joystick_index) && (deviceAxis == command_line_field_of_view_joystick_axis))
	{
		retval = FALSE;
	}
	else
	{
		retval = TRUE;
	}

	return retval;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_joysticks (void)
{
	HRESULT
		di_err;

	//
	// Allocate joystick device array
	//

	joystick_devices = (joystick_device_info *) safe_malloc (sizeof (joystick_device_info) * MAXIMUM_JOYSTICK_DEVICES);

	//
	// First, enumerate all the joysticks that are available
	//

	number_of_joystick_devices = 0;

	// Retro 10Jul2004
	AxisInfo[AxisCount].axis = -1;
	AxisInfo[AxisCount].device = -1;
	AxisInfo[AxisCount].AxisName = "Keyboard";
	AxisInfo[AxisCount].inUse = FALSE;	// keyboard is ALWAYS 'not in use' for our purposes
	AxisCount++;
	// Retro 10Jul2004 end

	if (direct_input)
	{

		di_err = IDirectInput7_EnumDevices (direct_input, DIDEVTYPE_JOYSTICK, enumerate_joystick_devices, NULL, DIEDFL_ATTACHEDONLY);

		if (di_err != DI_OK)
		{

//			debug_log ("Unable to enumerate any joystick devices");
		}
	}
}

void deinitialise_joysticks (void)
{
	struct external_effects *temp;

	temp = Head;

	while(temp)
	{
		temp = Head->Next;
		safe_free (Head);
		Head = temp;
	}
	
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static char* string_to_unicode(const char* str)
{
	WCHAR
		wstr[256];

	static CHAR
		ustr[256];

	MultiByteToWideChar(CP_ACP, 0, str, -1, wstr, ARRAYSIZE(wstr));
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, ustr, ARRAYSIZE(ustr), NULL, NULL);
	return ustr;
}

static unsigned process_axis(LPDIRECTINPUTDEVICE7 device, LPDIDEVICEOBJECTINSTANCE device_part, LPDIPROPRANGE device_range, LPDIPROPDWORD device_property, unsigned obj, unsigned index, const char* name)
{
	HRESULT
		di_err;

	di_err = IDirectInputDevice7_GetObjectInfo (device, device_part, obj, DIPH_BYOFFSET);

	if (di_err == DI_OK)
	{
#if 0	// Retro 12Dez2004
		device_property->dwData = (int) (JOYSTICK_AXIS_DEADZONE * 10000.0);
#else
		if ( TRUE == axis_has_deadzone (number_of_joystick_devices, index))
			device_property->dwData = (int) (JOYSTICK_AXIS_DEADZONE * 10000.0);
		else
			device_property->dwData = 0;
#endif

		device_range->diph.dwObj = obj;
		device_property->diph.dwObj = obj;
	
		IDirectInputDevice7_SetProperty (device, DIPROP_RANGE, &device_range->diph);
		IDirectInputDevice7_SetProperty (device, DIPROP_DEADZONE, &device_property->diph);

		strcpy (device_part->tszName, string_to_unicode (device_part->tszName));

		// Retro 10Jul2004 start
		AxisInfo[AxisCount].axis = index;
		AxisInfo[AxisCount].device = number_of_joystick_devices;
		AxisInfo[AxisCount].AxisName = (char*) malloc(strlen(joystick_devices[number_of_joystick_devices].device_product_name)+strlen(name)+strlen(device_part->tszName)+1);
		strcpy(AxisInfo[AxisCount].AxisName,joystick_devices[number_of_joystick_devices].device_product_name);
		strcat(AxisInfo[AxisCount].AxisName,name);
		strcat(AxisInfo[AxisCount].AxisName,device_part->tszName);
		AxisInfo[AxisCount].inUse = FALSE;
		AxisCount++;
		// Retro 10Jul2004 end

		return TRUE;
	}

	return FALSE;
}

BOOL FAR PASCAL enumerate_joystick_devices (LPCDIDEVICEINSTANCE device_instance, LPVOID user_data)
{

	HRESULT
		di_err;

	LPDIRECTINPUTDEVICE7
		device;

	DIPROPRANGE
		device_range;

	DIPROPDWORD
		device_property;

	DIDEVICEOBJECTINSTANCE
		device_part;

	DIDEVCAPS
		device_capabilities;
	
	DWORD
		joystick_force_axes[NUMBER_OF_FORCE_FEEDBACK_AXES];
	
	LONG
		joystick_force_directions[NUMBER_OF_FORCE_FEEDBACK_AXES];
	
	DIEFFECT
		effect;		// general parameters
	
	GUID
		guidEffect;
	
	DICONSTANTFORCE
		constant_force;

	directory_file_list
		*directory_listing = nullptr;
	
	int
		valid_file;
	
	//
	// Create the device
	//
	
	di_err = IDirectInput7_CreateDeviceEx (direct_input, GUID_PREFIX device_instance->guidInstance, GUID_PREFIX IID_IDirectInputDevice7, ( LPVOID * ) &device, NULL);

	if (di_err != DI_OK)
	{

		debug_log ("Unable to creat game device");
		
		return (DIENUM_CONTINUE);
	}

	//
	// Get the capabilities of the joystick
	//

	device_capabilities.dwSize = sizeof (device_capabilities);

	di_err = IDirectInputDevice7_GetCapabilities (device, &device_capabilities);

	if (di_err != DI_OK)
	{

		debug_log ("Unable to query a joystick for capabilities");

		IDirectInputDevice7_Release (device);

		return (DIENUM_CONTINUE);
	}

	//
	// First, the data format
	//

	di_err = IDirectInputDevice7_SetDataFormat (device, &c_dfDIJoystick);

	if (di_err != DI_OK)
	{

		debug_log ("Unable to set data format on a joystick");

		IDirectInputDevice7_Release (device);

		return (DIENUM_CONTINUE);
	}

	//
	// Next the cooperative level
	//
	
	
	if (device_capabilities.dwFlags & DIDC_FORCEFEEDBACK)
	{

		debug_log ("Got a force feedback joystick");
		
		feedback_device = device;
		
		ffb = 1;
		
		di_err = IDirectInputDevice7_SetCooperativeLevel (device, application_window, DISCL_EXCLUSIVE | DISCL_BACKGROUND);
	
		if (di_err != DI_OK)
		{
	
			debug_log ("Unable to set cooperative level on a force feedback joystick");
	
			IDirectInputDevice7_Release (device);
	
			return (DIENUM_CONTINUE);
		}

		//
		// Set the auto-centring mechanism off
		//

		device_property.diph.dwSize = sizeof (device_property);
		device_property.diph.dwHeaderSize = sizeof (DIPROPHEADER);
		device_property.diph.dwObj = 0;
		device_property.diph.dwHow = DIPH_DEVICE;
		device_property.dwData = 0;

		di_err = IDirectInputDevice7_SetProperty (device, DIPROP_AUTOCENTER, &device_property.diph);

		if (di_err != DI_OK)
		{
	
			debug_log ("Unable to set autocentring off on a force feedback joystick");
	
			IDirectInputDevice7_Release (device);
	
			return (DIENUM_CONTINUE);
		}

		//
		// Set the callback in motion to obtain the effect GUID
		//

		di_err = IDirectInputDevice7_EnumEffects(device, (LPDIENUMEFFECTSCALLBACK) DIEnumEffectsProc, &guidEffect, DIEFT_PERIODIC);

		if (di_err != DI_OK)
			{

				debug_log ("Unable to enumerate a force feedback joystick effect");
				
				IDirectInputDevice7_Release (device);
	
			}
		else
			{

				debug_log ("Standard force feedback joystick effect enumerated");
				
			}

		//
		// Create an effect for this joystick
		//

		joystick_force_axes[0] = DIJOFS_X;
		joystick_force_axes[1] = DIJOFS_Y;

		joystick_force_directions[0] = 0;
		joystick_force_directions[1] = 0;

		constant_force.lMagnitude = 0;

		effect.dwSize = sizeof (effect);
		effect.dwFlags = DIEFF_CARTESIAN | DIEFF_OBJECTOFFSETS;
		effect.dwDuration = INFINITE;
		effect.dwSamplePeriod = 0;
		effect.dwGain = DI_FFNOMINALMAX;
		effect.dwTriggerButton = DIEB_NOTRIGGER;
		effect.dwTriggerRepeatInterval = 0;
		effect.cAxes = NUMBER_OF_FORCE_FEEDBACK_AXES;
		effect.rgdwAxes = joystick_force_axes;
		effect.rglDirection = joystick_force_directions;
		effect.lpEnvelope = 0;
		effect.cbTypeSpecificParams = sizeof (constant_force);
		effect.lpvTypeSpecificParams = &constant_force;
		effect.dwStartDelay			= 0;

		
		di_err = IDirectInputDevice7_CreateEffect (device, GUID_PREFIX GUID_ConstantForce, &effect, &g_lpeffect, NULL);
		
		if (di_err != DI_OK)
		{
	
			debug_log ("Unable to create a force feedback joystick effect");
	
			IDirectInputDevice7_Release (device);
	
			return (DIENUM_CONTINUE);
		}

		
		//
		// Let's enumerate effects from "forcefeedback" folder
		//
		
		directory_listing = get_first_directory_file ("forcefeedback\\*.ffe");
		
		if (directory_listing)
		{
		valid_file = TRUE;
		while (valid_file)
		{
			if (get_directory_file_type (directory_listing) == DIRECTORY_FILE_TYPE_FILE)
			{
				
				char
					path[64];
				
				sprintf (filename, "%s", get_directory_file_filename (directory_listing));
				
				debug_log ("filename %s", filename);
				
				sprintf (path, "forcefeedback\\%s", filename);
				
				di_err = IDirectInputDevice7_EnumEffectsInFile(device, path, (LPDIENUMEFFECTSINFILECALLBACK) EnumEffectsInFileProc, NULL, DIFEF_INCLUDENONSTANDARD);

				if (di_err != DI_OK)
				{

					debug_log ("Unable to enumerate effects from %s: %s", filename, get_dinput_error_message (di_err));

					IDirectInputDevice7_Release (device);

					return (DIENUM_STOP);
					
				}
				else
				{
					debug_log ("Effects from %s file are enumerated", filename);
				}
			}

			valid_file = get_next_directory_file (directory_listing);
		}

		destroy_directory_file_list (directory_listing);
		}
	
	}
	
	else
	{
		di_err = IDirectInputDevice7_SetCooperativeLevel (device, application_window, DISCL_EXCLUSIVE | DISCL_BACKGROUND);
	
		if (di_err != DI_OK)
		{
	
			debug_log ("Unable to set cooperative level on a joystick");
	
			IDirectInputDevice7_Release (device);
	
			return (DIENUM_CONTINUE);
		}
	}

	//
	// Copy the name of the device
	//

	strcpy (joystick_devices[number_of_joystick_devices].device_name, string_to_unicode (device_instance->tszInstanceName));

	strcpy (joystick_devices[number_of_joystick_devices].device_product_name, string_to_unicode (device_instance->tszProductName));

	//
	// Initialise the device part for the next lot of queries
	//

	device_part.dwSize = sizeof (DIDEVICEOBJECTINSTANCE);

	//
	// Initialise the range structure
	//

	device_range.diph.dwSize = sizeof (device_range);
	device_range.diph.dwHeaderSize = sizeof (device_range.diph);
	device_range.diph.dwHow = DIPH_BYOFFSET;
	device_range.lMin = JOYSTICK_AXIS_MINIMUM;
	device_range.lMax = JOYSTICK_AXIS_MAXIMUM;

	//
	// Set the dead zones for all the axis to be the same (for now).
	// Note: when setting the deadzone, units are specified in the thousandths, so 20% = 2000/10000
	//

	device_property.diph.dwSize = sizeof (device_property);
	device_property.diph.dwHeaderSize = sizeof(device_property.diph);
	device_property.diph.dwHow = DIPH_BYOFFSET;
	device_property.dwData = (int) (JOYSTICK_AXIS_DEADZONE * 10000.0);

	//
	// Mark all axis to be invalid
	//

	joystick_devices[number_of_joystick_devices].joystick_xaxis_valid = FALSE;
	joystick_devices[number_of_joystick_devices].joystick_yaxis_valid = FALSE;
	joystick_devices[number_of_joystick_devices].joystick_zaxis_valid = FALSE;
	joystick_devices[number_of_joystick_devices].joystick_rxaxis_valid = FALSE;
	joystick_devices[number_of_joystick_devices].joystick_ryaxis_valid = FALSE;
	joystick_devices[number_of_joystick_devices].joystick_rzaxis_valid = FALSE;
	joystick_devices[number_of_joystick_devices].joystick_slider0axis_valid = FALSE;
	joystick_devices[number_of_joystick_devices].joystick_slider1axis_valid = FALSE;

	//
	// Initialise the X axis (if there is one)
	//

	joystick_devices[number_of_joystick_devices].joystick_xaxis_valid = process_axis (device, &device_part, &device_range, &device_property, DIJOFS_X, 0, " (X) : ");

	//
	// Initialise the Y axis (if there is one)
	//

	joystick_devices[number_of_joystick_devices].joystick_yaxis_valid = process_axis (device, &device_part, &device_range, &device_property, DIJOFS_Y, 1, " (Y) : ");

	//
	// Initialise the Z axis (if there is one)
	//

	joystick_devices[number_of_joystick_devices].joystick_zaxis_valid = process_axis (device, &device_part, &device_range, &device_property, DIJOFS_Z, 2, " (Z) : ");

	//
	// Initialise the Rx axis (if there is one)
	//

	joystick_devices[number_of_joystick_devices].joystick_rxaxis_valid = process_axis (device, &device_part, &device_range, &device_property, DIJOFS_RX, 3, " (RX) : ");

	//
	// Initialise the Ry axis (if there is one)
	//

	joystick_devices[number_of_joystick_devices].joystick_ryaxis_valid = process_axis (device, &device_part, &device_range, &device_property, DIJOFS_RY, 4, " (RY) : ");

	//
	// Initialise the Rz axis (if there is one)
	//

	joystick_devices[number_of_joystick_devices].joystick_rzaxis_valid = process_axis (device, &device_part, &device_range, &device_property, DIJOFS_RZ, 5, " (RZ) : ");

	//
	// Initialise the Slider0 axis (if there is one)
	//

	joystick_devices[number_of_joystick_devices].joystick_slider0axis_valid = process_axis (device, &device_part, &device_range, &device_property, DIJOFS_SLIDER(0), 6, " (SLIDER1) : ");

	//
	// Initialise the Slider1 axis (if there is one)
	//

	joystick_devices[number_of_joystick_devices].joystick_slider1axis_valid = process_axis (device, &device_part, &device_range, &device_property, DIJOFS_SLIDER(1), 7, " (SLIDER2) : ");

	//
	// Parse the capabilities
	//

	joystick_devices[number_of_joystick_devices].number_of_buttons = device_capabilities.dwButtons;

	//
	// Acquire the joystick
	//

	di_err = IDirectInputDevice7_Acquire (device);

	if (di_err != DI_OK)
	{

		//
		// Failed to acquire the device - release it.
		//

		debug_log ("Unable to acquire the device for a joystick");

		IDirectInputDevice7_Release (device);

		return (DIENUM_CONTINUE);
	}

	//
	// Store this device in the array
	//

	joystick_devices[number_of_joystick_devices].input_device = device;
//	joystick_devices[number_of_joystick_devices].input_effect = g_lpeffect;
	joystick_devices[number_of_joystick_devices].joystick_supports_force_feedback = FALSE;
	joystick_devices[number_of_joystick_devices].joystick_has_pov = FALSE;

	if (device_capabilities.dwFlags & DIDC_FORCEFEEDBACK)
	{

		joystick_devices[number_of_joystick_devices].joystick_supports_force_feedback = TRUE;
	}

	if (device_capabilities.dwPOVs > 0)
	{

		joystick_devices[number_of_joystick_devices].joystick_has_pov = TRUE;
	}

#if DEBUG_MODULE

	debug_log ("Got joystick device %s, %s", device_instance->tszInstanceName, device_instance->tszProductName);

#endif

	number_of_joystick_devices++;

	return (DIENUM_CONTINUE);
}
 
// Callback for effects

BOOL EffectFound = FALSE;

BOOL FAR PASCAL DIEnumEffectsProc(LPCDIEFFECTINFO pei, LPVOID pv)
{
	*((GUID *)pv) = pei->guid;
	EffectFound = TRUE;
	debug_log ("effect have GUID now");
	return (DIENUM_STOP);  // one is enough
}

BOOL FAR PASCAL EnumEffectsInFileProc(LPCDIFILEEFFECT lpdife, LPVOID pv)
{
	HRESULT	 di_err;
	char *p;
	DIEFFECT eff = *lpdife->lpDiEffect;

	eff.dwTriggerButton = DIEB_NOTRIGGER;

	di_err = IDirectInputDevice7_CreateEffect (feedback_device, GUID_PREFIX lpdife->GuidEffect, &eff, &pEff[eff_count], NULL);

	if (di_err != DI_OK)
	{
		debug_log ("Unable to creat a force feedback effect from file: %s", get_dinput_error_message (di_err));
	}
	else 
	{
		debug_log ("force feedback effect %i from file is created", eff_count);

		p = strchr (filename, '.');

		if (p)
		{
			*p = '\0';
		}


		add_eff((char*)filename);
		
	} 

	++eff_count;
	
	return (DIENUM_CONTINUE);
	
}

 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Retro 12Dez2004 - only applies deadzones according to axis use for now..
// this routine should be called when the user leaves the controller ui.. or (worst case) after EVERY change in that ui..
extern void change_joystick_properties ( void )
{
	int
		i, j, axisCount;

	HRESULT
		di_err;

	LPDIRECTINPUTDEVICE7
		device;

	DIDEVICEOBJECTINSTANCE
		device_part;

	DIPROPDWORD
		device_property;

	int offsets[] = { DIJOFS_X, DIJOFS_Y, DIJOFS_Z, DIJOFS_RX, DIJOFS_RY, DIJOFS_RZ, DIJOFS_SLIDER(0), DIJOFS_SLIDER(1) };
	const int numOffsets = sizeof(offsets)/sizeof(offsets[0]);

	//
	// Initialise the device part for the next lot of queries
	//

	device_part.dwSize = sizeof (DIDEVICEOBJECTINSTANCE);

	//
	// Set the dead zones for all the axis to be the same (for now).
	// Note: when setting the deadzone, units are specified in the thousandths, so 20% = 2000/10000
	//

	device_property.diph.dwSize = sizeof (device_property);
	device_property.diph.dwHeaderSize = sizeof(device_property.diph);
	device_property.diph.dwHow = DIPH_BYOFFSET;
	device_property.dwData = (int) (JOYSTICK_AXIS_DEADZONE * 10000.0);

	axisCount = 0;

	for (i = 0; i < number_of_joystick_devices; i++)
	{
		device = joystick_devices[i].input_device;

		for (j = 0; j < numOffsets; j++)
		{
			//
			// Check if there is an axis with the given offset, if yes then look if it should have a deadzone and apply
			//

			di_err = IDirectInputDevice7_GetObjectInfo (device, &device_part, offsets[j], DIPH_BYOFFSET);

			if (di_err == DI_OK)
			{
				if ( TRUE == axis_has_deadzone (i, j))
					device_property.dwData = (int) (JOYSTICK_AXIS_DEADZONE * 10000.0);
				else
					device_property.dwData = 0;

				device_property.diph.dwObj = offsets[j];
				IDirectInputDevice7_SetProperty (device, DIPROP_DEADZONE, &device_property.diph);

				axisCount++;
			}
		}
	}
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void read_joystick_values (int joystick_device_index)
{
	HRESULT
		di_err;

	joystick_device_info
		*joystick = nullptr;

	int
		button_count;

#if 0
	FILE* fp;
#endif

//	if ((joystick_device_index >= 0) && (joystick_device_index < number_of_joystick_devices))
	for (joystick_device_index = 0; joystick_device_index < number_of_joystick_devices; joystick_device_index++)
	{
	
		joystick = &joystick_devices[joystick_device_index];
	
		// Read the joystick values
	
		if ((joystick) && (joystick->input_device))
		{
			// Copy the current values to the last values
		
			joystick->joystick_last_state = joystick->joystick_state;
		
			// Now, poll the device

			di_err = IDirectInputDevice7_Poll (joystick->input_device);

			if (command_line_forcefeedback && feedback_device)
			{
				if (di_err == DI_NOTATTACHED)
					ffb = 1;
				else
				{
					IDirectInputDevice7_SendForceFeedbackCommand( feedback_device, DISFFC_STOPALL );
					ffb = 0;
				}
			}


			if ((di_err == DIERR_INPUTLOST) || (di_err == DIERR_NOTACQUIRED))
			{
				debug_log ("poll: %s", get_dinput_error_message (di_err));
				di_err = IDirectInputDevice7_Acquire (joystick->input_device);
				debug_log ("acquire joystick device: %s", get_dinput_error_message (di_err));
		
				if (di_err != DI_OK)
				{
					debug_log ("Unable to acquire joystick device: %s", get_dinput_error_message (di_err));
				}
				else
				{
					di_err = IDirectInputDevice7_Poll (joystick->input_device);
					
				}
			}
			if ((di_err != DI_OK) && (di_err != S_FALSE))
			{
				debug_log ("Unable to poll joystick device: %s (%d)", get_dinput_error_message (di_err), di_err);
				return;
			}
		
		
			//
			// Finally, read the state
			//
		
			di_err = IDirectInputDevice7_GetDeviceState (joystick->input_device, sizeof (DIJOYSTATE), &joystick->joystick_state);
		
			/* if ((di_err == DIERR_INPUTLOST) || (di_err == DIERR_NOTACQUIRED))
			{
		
				IDirectInputDevice7_Acquire (joystick->input_device);
				
				di_err = IDirectInputDevice7_GetDeviceState (joystick->input_device, sizeof (DIJOYSTATE), &joystick->joystick_state);
			} */
		
			if (di_err != DI_OK)
			{

				debug_log ("Unable to read joystick device state: %s (%d)", get_dinput_error_message (di_err), di_err);
		
				return;
			}

			//
			// Generate any button events
			//
			if (command_line_cyclic_joystick_index != -1)	// Retro 18Jul2004 FIXME
				if (joystick_device_index == command_line_cyclic_joystick_index)	// Retro 18Jul2004 FIXME
				for (button_count = 0; button_count < joystick->number_of_buttons; button_count++)
				{
					if (button_count > 31)	// Retro 8Jan2004 - X52 Kludge..
					{
						continue;
					}

					if (joystick->joystick_last_state.rgbButtons[button_count] != joystick->joystick_state.rgbButtons[button_count])
					{

						if (joystick->joystick_state.rgbButtons[button_count] & 0x80)
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
#if 0
		//
		// Hack for Win2k problems of putting the Z axis data into Slider0 member
		//

		if ((!joystick->joystick_zaxis_valid) && (joystick->joystick_slider0axis_valid))
		{

			joystick->joystick_state.lZ = joystick->joystick_state.rglSlider[0];
		}
#endif
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

#if 0
	fp = fopen("stickresult.txt","at");
	{
		int i = 0;

		for (i = 0; i < number_of_joystick_devices; i++)
		{
			fprintf(fp,"--> %i\n",i);

			fprintf(fp,"%i\n",joystick_devices[i].joystick_state.lX);
			fprintf(fp,"%i\n",joystick_devices[i].joystick_state.lY);
			fprintf(fp,"%i\n",joystick_devices[i].joystick_state.lZ);
			fprintf(fp,"%i\n",joystick_devices[i].joystick_state.lRx);
			fprintf(fp,"%i\n",joystick_devices[i].joystick_state.lRy);
			fprintf(fp,"%i\n",joystick_devices[i].joystick_state.lRz);
			fprintf(fp,"%i\n",joystick_devices[i].joystick_state.rglSlider[0]);
			fprintf(fp,"%i\n",joystick_devices[i].joystick_state.rglSlider[1]);
			
			fprintf(fp,"-----------------------\n");
		}
	}
	fclose(fp);
#endif
}
#endif
 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float 
	xforce = 0,
	yforce = 0,
	xtimer = 0,
	ytimer = 0,
	xfreq = 0,
	yfreq = 0,
	xampl = 0,
	yampl = 0,
	ff_xtrim = 0,
	ff_ytrim = 0,
	ff_xcorr = 0,
	ff_ycorr = 0;

#ifndef OGRE_EE
void play_ffb_weapon_effect (char* eff_name, float rate)
{
	if (feedback_device && ffb == 1 && command_line_forcefeedback == 1 && command_line_ffb_recoil > 0)	
	{
		HRESULT
			di_err;
		DWORD
			effect_flags;
		int
			i,
			found = 0;

		struct external_effects *curr = Head;

		ASSERT (feedback_device);

			for (i = 0; i < (eff_count) ; i++)
			{

				if (strcmp(curr->name, eff_name) == NULL)
				{
					found = 1;

					debug_log ("effect %s is playing from file", eff_name);

					di_err = IDirectInputEffect_GetEffectStatus (pEff[i], &effect_flags);

					if (di_err == DIERR_NOTDOWNLOADED)
					{
					IDirectInputEffect_Download (pEff[i]);

					di_err = IDirectInputEffect_GetEffectStatus (pEff[i], &effect_flags);
					}

					if (di_err == DI_OK)
					{
						if (!effect_flags & DIEGES_PLAYING)
						{

							//
							// Start the effect
							//

							di_err = IDirectInputEffect_Start (pEff[i], 1, DIES_NODOWNLOAD);


							if (di_err != DI_OK)
							{
								debug_log ("Unable to start a force feedback effect from file: %s", get_dinput_error_message (di_err));
								return;
							}
							else
							{
								debug_log ("force feedback effect %i is started", i);
							}
						}
					}
					else
					{
						debug_log ("Unable to acquire Force feedback effect from file: %s", get_dinput_error_message (di_err));
						return;
					} 
				}

				if(curr->Next != NULL)
					curr = curr->Next;			

			}

			if (!found && rate > 0)
			{
				debug_log ("file %s not found. playing standard effect", eff_name);
				yfreq += rate * PI * get_delta_time() / 30;
				yampl += command_line_ffb_recoil * 0.5;
			}
	}	
}
#endif

void set_joystick_force_feedback_forces ()
{
#ifndef OGRE_EE
	if (feedback_device && ffb == 1 && command_line_forcefeedback == 1)	
	{
		HRESULT
			di_err;

		LONG
			joystick_force_directions[NUMBER_OF_FORCE_FEEDBACK_AXES];

		DIEFFECT
			effect;		// general parameters

		DICONSTANTFORCE
			constant_force;

		DWORD
			effect_flags;

		ASSERT (feedback_device);

			//
			// Set the effect parameters
			//

			if (xfreq > (PI / 2))
				xfreq = (PI / 2);

			xtimer = xtimer + xfreq;

			if (xtimer > PI )
				xtimer = -PI2 + xtimer;

			if (xtimer < 0)
				xampl *= -1;

			xforce = (xforce + 10000 * xampl + ff_xcorr) + ff_xtrim;

			if (yfreq > (PI / 2))
				yfreq = (PI / 2);

			ytimer = ytimer + yfreq;

			if (ytimer > PI )
				ytimer = -PI2 + ytimer;

			if (ytimer < 0)
				yampl *= -1;

			yforce = (yforce + 10000 * yampl + ff_ycorr) + ff_ytrim;
			//debug_log ("xfrce %i, yfrce %i, xfreq %f, yfreq %f, xampl %f, yampl %f, xcorr %f, ycorr %f", xforce, yforce, xfreq, yfreq, xampl, yampl, ff_xcorr, ff_ycorr);

			bound (xforce, -10000, 10000);
			bound (yforce, -10000, 10000);

			joystick_force_directions[0] = xforce;
			joystick_force_directions[1] = yforce;

			constant_force.lMagnitude = (DWORD) sqrt ((double) (xforce) * (double) (xforce) + (double) (yforce) * (double) (yforce));

			effect.dwSize = sizeof (effect);
			effect.dwFlags = DIEFF_CARTESIAN | DIEFF_OBJECTOFFSETS;
			effect.cAxes = NUMBER_OF_FORCE_FEEDBACK_AXES;
			effect.rglDirection = joystick_force_directions;
			effect.lpEnvelope = 0;
			effect.cbTypeSpecificParams = sizeof (constant_force);
			effect.lpvTypeSpecificParams = &constant_force;

			di_err = IDirectInputEffect_GetEffectStatus (g_lpeffect, &effect_flags);

			if (di_err == DIERR_NOTDOWNLOADED)
			{
				IDirectInputEffect_Download (g_lpeffect);

				di_err = IDirectInputEffect_GetEffectStatus (g_lpeffect, &effect_flags);
			}

			if (di_err == DI_OK)
			{
				// If the effect isn't playing - play it

				if (!(effect_flags & DIEGES_PLAYING))
				{
					di_err = IDirectInputEffect_Start (g_lpeffect, 1, 0);

					if (di_err != DI_OK)
					{

						debug_log ("Unable to start a force feedback effect: %s", get_dinput_error_message (di_err));

						return;
					}
				}
				else
				{
					di_err = IDirectInputEffect_SetParameters (g_lpeffect, &effect, DIEP_DIRECTION | DIEP_TYPESPECIFICPARAMS );

					if (di_err != DI_OK)
					{
						debug_log ("Problems setting effect parameters: %s", get_dinput_error_message (di_err));
						return;
					}
				}
			}
			else
			{
				debug_log ("Unable to acquire Force feedback effect status: %s", get_dinput_error_message (di_err));
				return;
			} 
	}
#endif

 	xforce = yforce = xfreq = yfreq = xampl = yampl = ff_xcorr = ff_ycorr = ff_xtrim = ff_ytrim = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// loke 030319
// this function returns the value of a joystick axis
// yem 030525 - changed axis to be indexed from 0 instead of 1. renamed to get_joystick_axis.
int get_joystick_axis (int joystick_index, int axis)
{
//	read_joystick_values(joystick_index); // Jabberwock 031120 Some joystick values were not read at all!

	// Retro 10Jul2004
	if ((joystick_index < 0)||(joystick_index > number_of_joystick_devices))
		return 0;
	if ((axis < 0)||(axis > 7))
		return 0;
	// Retro 10Jul2004 end

	switch (axis) {
	case 0:
		if (joystick_devices[joystick_index].joystick_xaxis_valid)
		{
			return joystick_devices[joystick_index].joystick_state.lX;
		}
		break;
				
	case 1:
		if (joystick_devices[joystick_index].joystick_yaxis_valid)
		{
			return joystick_devices[joystick_index].joystick_state.lY;
		}
		break;
				
	case 2:
		if (joystick_devices[joystick_index].joystick_zaxis_valid)
		{
			return joystick_devices[joystick_index].joystick_state.lZ;
		}
		break;
				
	case 3:
		if (joystick_devices[joystick_index].joystick_rxaxis_valid)
		{
			return joystick_devices[joystick_index].joystick_state.lRx;
		}
		break;
				
	case 4:
		if (joystick_devices[joystick_index].joystick_ryaxis_valid)
		{
			return joystick_devices[joystick_index].joystick_state.lRy;
		}
		break;
				
	case 5:
		if (joystick_devices[joystick_index].joystick_rzaxis_valid)
		{
			return joystick_devices[joystick_index].joystick_state.lRz;
		}
		break;

	case 6:
		if (joystick_devices[joystick_index].joystick_slider0axis_valid)
		{
			return joystick_devices[joystick_index].joystick_state.rglSlider[0];
		}
		break;

	case 7:
		if (joystick_devices[joystick_index].joystick_slider1axis_valid)
		{
			return joystick_devices[joystick_index].joystick_state.rglSlider[1];
		}
		break;
	}

	return 0;
}

#ifndef OGRE_EE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

// Added 2003-05-25 (yem) Use this function instead of referencing DIJOYSTATE.rgdwPOV[] directly
joystick_hat_position get_joystick_hat(joystick_device_info *stick, int index) {
#ifndef OGRE_EE
	// TODO: Add support for diagonal directions

	DWORD
		pos;

	if( stick->joystick_has_pov && index >= 0 && index < 4 ) {
		pos = stick->joystick_state.rgdwPOV[ index ];

		if (LOWORD (pos) == 0xFFFF)
			return HAT_CENTERED;
		else if (pos < 45 * DI_DEGREES)
			return HAT_UP;
		else if (pos < 135 * DI_DEGREES)
			return HAT_RIGHT;
		else if (pos < 225 * DI_DEGREES)
			return HAT_DOWN;
		else if (pos < 315 * DI_DEGREES)
			return HAT_LEFT;
	}
#endif

	return HAT_CENTERED;
}

#ifndef OGRE_EE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Added 2003-05-25 (yem) Use this function instead of referencing DIJOYSTATE.rgbButtons[] directly
int get_joystick_button(joystick_device_info *stick, int index) {

	if( index >= 0 && index < 32 )
		return stick->joystick_state.rgbButtons[ index ];
	else
		return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Retro 28Aug2004 - theString has to be allocated !

void GetGUIDString(const int iDevice, char* theString)
{
	DIDEVICEINSTANCE devInst;
	char strTemp[MAX_PATH];
	char strTemp2[MAX_PATH];
	int i;

	if ((iDevice < 0)||(iDevice >= number_of_joystick_devices))
		return;

	if (!theString)
		return;

	devInst.dwSize = sizeof(DIDEVICEINSTANCE);
	IDirectInputDevice7_GetDeviceInfo(joystick_devices[iDevice].input_device, &devInst);

	sprintf(strTemp,"{%8.8X-%4.4X-%4.4X-",	devInst.guidProduct.Data1,
											devInst.guidProduct.Data2,
											devInst.guidProduct.Data3);

	for (i = 0; i < 2; i++)
	{
		sprintf(strTemp2,"%2.2X",devInst.guidProduct.Data4[i]);
		strcat(strTemp,strTemp2);
	}
	strcat(strTemp,"-");
	for (i = 2; i < 8; i++)
	{
		sprintf(strTemp2,"%2.2X",devInst.guidProduct.Data4[i]);
		strcat(strTemp,strTemp2);
	}
	strcat(strTemp,"}");

	strcpy(theString,strTemp);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ShutdownAxisInformation()
{
	int i = 0;

	for (i = 1; i < AxisCount; i++)	// '0' is keyboard and was not created on the heap
	{
		free(AxisInfo[i].AxisName);
		AxisInfo[i].AxisName = 0;
	}
}
#endif
