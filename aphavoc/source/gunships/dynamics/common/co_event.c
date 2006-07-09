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

void debug_dynamics_damage_model (event *ev);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_flight_dynamics_events (void)
{

	if ( current_flight_dynamics )
	{

		// cyclic events

		switch (get_global_cyclic_input ())
		{

			case KEYBOARD_INPUT:
			{

				set_event (DIK_LEFT, MODIFIER_NONE, KEY_STATE_EITHER, cyclic_left);
				set_event (DIK_RIGHT, MODIFIER_NONE, KEY_STATE_EITHER, cyclic_right);
				set_event (DIK_UP, MODIFIER_NONE, KEY_STATE_EITHER, cyclic_forward);
				set_event (DIK_DOWN, MODIFIER_NONE, KEY_STATE_EITHER, cyclic_backward);

				break;
			}

			case MOUSE_INPUT:
			{

				set_event (MOUSE_MOVE, MODIFIER_NONE, BUTTON_STATE_INVALID, cyclic_mouse_input);

				break;
			}

			case JOYSTICK_INPUT:
			{
				// 030418 loke
				// implemented multiple joystick device selection
				if (command_line_cyclic_joystick_index == -1)
				{
					current_flight_dynamics->input_data.cyclic_joystick_device = joystick_devices [0];
				}
				else
				{
					current_flight_dynamics->input_data.cyclic_joystick_device = joystick_devices [command_line_cyclic_joystick_index];
				}

				break;
			}
		}

		// collective events

		switch (get_global_collective_input ())
		{

			case KEYBOARD_INPUT:
			{

				set_event (DIK_Q, MODIFIER_NONE, KEY_STATE_EITHER, collective_forward);
				set_event (DIK_A, MODIFIER_NONE, KEY_STATE_EITHER, collective_backward);
				set_event (DIK_EQUALS, MODIFIER_NONE, KEY_STATE_EITHER, collective_forward);
				set_event (DIK_MINUS, MODIFIER_NONE, KEY_STATE_EITHER, collective_backward);

				break;
			}

			case MOUSE_INPUT:
			{

				set_event (MOUSE_MOVE_UP, MODIFIER_MOUSE_RIGHT_BUTTON, BUTTON_STATE_EITHER, collective_mouse_input);
				set_event (MOUSE_MOVE_DOWN, MODIFIER_MOUSE_RIGHT_BUTTON, BUTTON_STATE_EITHER, collective_mouse_input);

				break;
			}

			case JOYSTICK_INPUT:
			{

				break;
			}
		}

		// pedal events

		switch (get_global_pedal_input ())
		{

			case KEYBOARD_INPUT:
			{

				set_event (DIK_Z, MODIFIER_NONE, KEY_STATE_EITHER, pedal_left);
				set_event (DIK_X, MODIFIER_NONE, KEY_STATE_EITHER, pedal_right);

				break;
			}

			case MOUSE_INPUT:
			{

				set_event (MOUSE_MOVE_LEFT, MODIFIER_MOUSE_RIGHT_BUTTON, BUTTON_STATE_EITHER, pedal_mouse_input);
				set_event (MOUSE_MOVE_RIGHT, MODIFIER_MOUSE_RIGHT_BUTTON, BUTTON_STATE_EITHER, pedal_mouse_input);

				break;
			}

			case JOYSTICK_INPUT:
			{

				break;
			}
		}

		// model keys

		set_event (DIK_T, MODIFIER_NONE, KEY_STATE_DOWN, set_trim_control);
		set_event (DIK_T, MODIFIER_LEFT_SHIFT, KEY_STATE_DOWN, clear_trim_control);
		set_event (DIK_R, MODIFIER_NONE, KEY_STATE_DOWN, flight_dynamics_toggle_rotor_brake);
		set_event (DIK_B, MODIFIER_NONE, KEY_STATE_DOWN, flight_dynamics_toggle_wheel_brake);
		set_event (DIK_H, MODIFIER_NONE, KEY_STATE_DOWN, flight_dynamics_toggle_auto_hover);
		set_event (DIK_H, MODIFIER_LEFT_SHIFT, KEY_STATE_DOWN, flight_dynamics_toggle_auto_hover);
		set_event (DIK_H, MODIFIER_LEFT_ALT, KEY_STATE_DOWN, flight_dynamics_toggle_altitude_lock);
		set_event (DIK_J, MODIFIER_LEFT_ALT, KEY_STATE_DOWN, flight_dynamics_decrease_altitude_lock);
		set_event (DIK_K, MODIFIER_LEFT_ALT, KEY_STATE_DOWN, flight_dynamics_increase_altitude_lock);
		set_event (DIK_G, MODIFIER_NONE, KEY_STATE_DOWN, flight_dynamics_toggle_auto_pilot);

		set_event (DIK_TAB, MODIFIER_LEFT_SHIFT, KEY_STATE_DOWN, load_dynamics_model);
		set_event (DIK_TAB, MODIFIER_LEFT_CONTROL, KEY_STATE_DOWN, save_dynamics_model);

		// arneh, july 2006 - engine keys
		set_event (DIK_COMMA,  MODIFIER_LEFT_CONTROL, KEY_STATE_DOWN, flight_dynamics_start_engine_ev);
		set_event (DIK_COMMA,  MODIFIER_NONE, 		  KEY_STATE_DOWN, flight_dynamics_throttle_engine_ev);
		set_event (DIK_COMMA,  MODIFIER_LEFT_SHIFT,   KEY_STATE_DOWN, flight_dynamics_throttle_engine_ev);
		set_event (DIK_PERIOD, MODIFIER_LEFT_CONTROL, KEY_STATE_DOWN, flight_dynamics_start_engine_ev);
		set_event (DIK_PERIOD, MODIFIER_NONE, 		  KEY_STATE_DOWN, flight_dynamics_throttle_engine_ev);
		set_event (DIK_PERIOD, MODIFIER_LEFT_SHIFT,   KEY_STATE_DOWN, flight_dynamics_throttle_engine_ev);
		set_event (DIK_SLASH,  MODIFIER_LEFT_CONTROL, KEY_STATE_DOWN, flight_dynamics_start_apu_ev);

		#ifdef DEBUG

		set_event (DIK_1, MODIFIER_RIGHT_SHIFT, KEY_STATE_DOWN, debug_dynamics_damage_model);
		set_event (DIK_2, MODIFIER_RIGHT_SHIFT, KEY_STATE_DOWN, debug_dynamics_damage_model);
		set_event (DIK_3, MODIFIER_RIGHT_SHIFT, KEY_STATE_DOWN, debug_dynamics_damage_model);
		set_event (DIK_4, MODIFIER_RIGHT_SHIFT, KEY_STATE_DOWN, debug_dynamics_damage_model);
		set_event (DIK_5, MODIFIER_RIGHT_SHIFT, KEY_STATE_DOWN, debug_dynamics_damage_model);
		set_event (DIK_6, MODIFIER_RIGHT_SHIFT, KEY_STATE_DOWN, debug_dynamics_damage_model);
		set_event (DIK_7, MODIFIER_RIGHT_SHIFT, KEY_STATE_DOWN, debug_dynamics_damage_model);
		set_event (DIK_8, MODIFIER_RIGHT_SHIFT, KEY_STATE_DOWN, debug_dynamics_damage_model);
		set_event (DIK_9, MODIFIER_RIGHT_SHIFT, KEY_STATE_DOWN, debug_dynamics_damage_model);
		set_event (DIK_0, MODIFIER_RIGHT_SHIFT, KEY_STATE_DOWN, debug_dynamics_damage_model);

		#endif
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void debug_dynamics_damage_model (event *ev)
{

	dynamics_damage_types
		damage;

	damage = 1 << ((ev->key)- (DIK_1));

	dynamics_damage_model (damage, FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
