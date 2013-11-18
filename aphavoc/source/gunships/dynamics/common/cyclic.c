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



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// somewhere between 1 and 15 minutes until total loss of control
#define MAX_HYDRAULICS_LOSS_RATE   (1.0 / 60.0)
#define MIN_HYDRAULICS_LOSS_RATE   (1.0 / 900.0)

float
	mouse_sensitivity = 25.0;

static float
	damaged_lock_x_pos,
	damaged_lock_y_pos,
	hydraulic_pressure,
	hydraulic_pressure_loss_rate;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void cyclic_left (event *ev)
{

	if (!current_flight_dynamics)
	{

		return;
	}

	if (ev->state == KEY_STATE_DOWN)
	{

		current_flight_dynamics->input_data.cyclic_input_pressure |= CYCLIC_PRESSURE_LEFT;
	}
	else
	{

		current_flight_dynamics->input_data.cyclic_input_pressure ^= CYCLIC_PRESSURE_LEFT;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void cyclic_right (event *ev)
{

	if (!current_flight_dynamics)
	{

		return;
	}

	if (ev->state == KEY_STATE_DOWN)
	{

		current_flight_dynamics->input_data.cyclic_input_pressure |= CYCLIC_PRESSURE_RIGHT;
	}
	else
	{

		current_flight_dynamics->input_data.cyclic_input_pressure ^= CYCLIC_PRESSURE_RIGHT;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void cyclic_forward (event *ev)
{

	if (!current_flight_dynamics)
	{

		return;
	}

	if (ev->state == KEY_STATE_DOWN)
	{

		current_flight_dynamics->input_data.cyclic_input_pressure |= CYCLIC_PRESSURE_FORWARD;
	}
	else
	{

		current_flight_dynamics->input_data.cyclic_input_pressure ^= CYCLIC_PRESSURE_FORWARD;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void cyclic_backward (event *ev)
{

	if (!current_flight_dynamics)
	{

		return;
	}

	if (ev->state == KEY_STATE_DOWN)
	{

		current_flight_dynamics->input_data.cyclic_input_pressure |= CYCLIC_PRESSURE_BACKWARD;
	}
	else
	{

		current_flight_dynamics->input_data.cyclic_input_pressure ^= CYCLIC_PRESSURE_BACKWARD;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void cyclic_mouse_input (event *ev)
{

#if 1

	// make mouse act on pressures

	if (ev->dx > 0.0)
	{

		current_flight_dynamics->input_data.cyclic_horizontal_pressure.value = max (0.0f, current_flight_dynamics->input_data.cyclic_horizontal_pressure.value);
	}
	else if (ev->dx < 0.0)
	{

		current_flight_dynamics->input_data.cyclic_horizontal_pressure.value = min (0.0f, current_flight_dynamics->input_data.cyclic_horizontal_pressure.value);
	}

	if (ev->dy > 0.0)
	{

		current_flight_dynamics->input_data.cyclic_vertical_pressure.value = max (0.0f, current_flight_dynamics->input_data.cyclic_vertical_pressure.value);
	}
	else if (ev->dy < 0.0)
	{

		current_flight_dynamics->input_data.cyclic_vertical_pressure.value = min (0.0f, current_flight_dynamics->input_data.cyclic_vertical_pressure.value);
	}

	current_flight_dynamics->input_data.cyclic_horizontal_pressure.value += (float) (ev->dx) * (mouse_sensitivity / 50.0);

	current_flight_dynamics->input_data.cyclic_vertical_pressure.value -= (float) (ev->dy) * (mouse_sensitivity / 50.0);

#else

	// make mouse act on cyclic values

	current_flight_dynamics->input_data.cyclic_x.value += (float) (ev->dx) * mouse_sensitivity / 50.0;

	current_flight_dynamics->input_data.cyclic_y.value -= (float) (ev->dy) * mouse_sensitivity / 50.0;

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_cyclic_pressure_inputs (void)
{

	float
		trim_x,
		trim_y;

	if (!current_flight_dynamics)
	{

		return;
	}

	if (hydraulic_pressure_loss_rate && hydraulic_pressure > 0.0)
	{
		hydraulic_pressure -= hydraulic_pressure_loss_rate * get_delta_time();

		if (hydraulic_pressure < 0.0)
			hydraulic_pressure = 0.0;
	}

	trim_x = current_flight_dynamics->input_data.cyclic_x_trim.value;
	trim_y = current_flight_dynamics->input_data.cyclic_y_trim.value;

	if (trim_button_held)
	{
		current_flight_dynamics->input_data.cyclic_x.value = current_flight_dynamics->input_data.cyclic_x_trim.value;
		current_flight_dynamics->input_data.cyclic_y.value = current_flight_dynamics->input_data.cyclic_y_trim.value;
	}
	else
		switch (get_global_cyclic_input ())
		{

			case KEYBOARD_INPUT:
			case MOUSE_INPUT:
			{

				if (current_flight_dynamics->input_data.cyclic_input_pressure & CYCLIC_PRESSURE_LEFT)
				{

					current_flight_dynamics->input_data.cyclic_horizontal_pressure.value = min (0.0f, current_flight_dynamics->input_data.cyclic_horizontal_pressure.value);

					current_flight_dynamics->input_data.cyclic_x.value = min ((current_flight_dynamics->input_data.cyclic_x.value) / 2.0f, current_flight_dynamics->input_data.cyclic_x.value);

					current_flight_dynamics->input_data.cyclic_horizontal_pressure.value -= MODEL_FRAME_RATE * get_model_delta_time ();

					if ((current_flight_dynamics->auto_hover == HOVER_HOLD_NORMAL) ||
						(current_flight_dynamics->auto_hover == HOVER_HOLD_STABLE))
					{

						set_current_flight_dynamics_auto_hover (HOVER_HOLD_NONE);
						set_current_flight_dynamics_auto_pilot (FALSE);
					}
				}
				else if (current_flight_dynamics->input_data.cyclic_input_pressure & CYCLIC_PRESSURE_RIGHT)
				{

					current_flight_dynamics->input_data.cyclic_horizontal_pressure.value = max (0.0f, current_flight_dynamics->input_data.cyclic_horizontal_pressure.value);

					current_flight_dynamics->input_data.cyclic_x.value = max ((current_flight_dynamics->input_data.cyclic_x.value) / 2.0f, current_flight_dynamics->input_data.cyclic_x.value);

					current_flight_dynamics->input_data.cyclic_horizontal_pressure.value += MODEL_FRAME_RATE * get_model_delta_time ();

					if ((current_flight_dynamics->auto_hover == HOVER_HOLD_NORMAL) ||
						(current_flight_dynamics->auto_hover == HOVER_HOLD_STABLE))
					{

						set_current_flight_dynamics_auto_hover (HOVER_HOLD_NONE);
						set_current_flight_dynamics_auto_pilot (FALSE);
					}
				}
				else
				{

					if (fabs (current_flight_dynamics->input_data.cyclic_horizontal_pressure.value) < 1.0)
					{

						current_flight_dynamics->input_data.cyclic_horizontal_pressure.value = 0.0;
					}
					else
					{

						current_flight_dynamics->input_data.cyclic_horizontal_pressure.value -= ((MODEL_FRAME_RATE * get_model_delta_time ()) / 2.0) * (current_flight_dynamics->input_data.cyclic_horizontal_pressure.value);
					}
				}



				if (current_flight_dynamics->input_data.cyclic_input_pressure & CYCLIC_PRESSURE_BACKWARD)
				{

					current_flight_dynamics->input_data.cyclic_vertical_pressure.value = min (0.0f, current_flight_dynamics->input_data.cyclic_vertical_pressure.value);

					current_flight_dynamics->input_data.cyclic_y.value = min (current_flight_dynamics->input_data.cyclic_y.value / 2.0f, current_flight_dynamics->input_data.cyclic_y.value);

					current_flight_dynamics->input_data.cyclic_vertical_pressure.value -= MODEL_FRAME_RATE * get_model_delta_time ();

					if ((current_flight_dynamics->auto_hover == HOVER_HOLD_NORMAL) ||
						(current_flight_dynamics->auto_hover == HOVER_HOLD_STABLE))
					{

						set_current_flight_dynamics_auto_hover (HOVER_HOLD_NONE);
						set_current_flight_dynamics_auto_pilot (FALSE);
					}
				}
				else if (current_flight_dynamics->input_data.cyclic_input_pressure & CYCLIC_PRESSURE_FORWARD)
				{

					current_flight_dynamics->input_data.cyclic_vertical_pressure.value = max (0.0f, current_flight_dynamics->input_data.cyclic_vertical_pressure.value);

					current_flight_dynamics->input_data.cyclic_y.value = max (current_flight_dynamics->input_data.cyclic_y.value / 2.0f, current_flight_dynamics->input_data.cyclic_y.value);

					current_flight_dynamics->input_data.cyclic_vertical_pressure.value += MODEL_FRAME_RATE * get_model_delta_time ();

					if ((current_flight_dynamics->auto_hover == HOVER_HOLD_NORMAL) ||
						(current_flight_dynamics->auto_hover == HOVER_HOLD_STABLE))
					{

						set_current_flight_dynamics_auto_hover (HOVER_HOLD_NONE);
						set_current_flight_dynamics_auto_pilot (FALSE);
					}
				}
				else
				{

					if (fabs (current_flight_dynamics->input_data.cyclic_vertical_pressure.value) < 1.0)
					{

						current_flight_dynamics->input_data.cyclic_vertical_pressure.value = 0.0;
					}
					else
					{

						current_flight_dynamics->input_data.cyclic_vertical_pressure.value -= ((MODEL_FRAME_RATE * get_model_delta_time ()) / 2.0) * (current_flight_dynamics->input_data.cyclic_vertical_pressure.value);
					}
				}

				// limit pressure inputs

				current_flight_dynamics->input_data.cyclic_horizontal_pressure.value = bound (
																					current_flight_dynamics->input_data.cyclic_horizontal_pressure.value,
																					current_flight_dynamics->input_data.cyclic_horizontal_pressure.min,
																					current_flight_dynamics->input_data.cyclic_horizontal_pressure.max
																					);

				current_flight_dynamics->input_data.cyclic_vertical_pressure.value = bound (current_flight_dynamics->input_data.cyclic_vertical_pressure.value,
																					current_flight_dynamics->input_data.cyclic_vertical_pressure.min,
																					current_flight_dynamics->input_data.cyclic_vertical_pressure.max
																					);

				// recalculate cyclic position

				if (current_flight_dynamics->input_data.cyclic_horizontal_pressure.value)
				{

					current_flight_dynamics->input_data.cyclic_x.value += (MODEL_FRAME_RATE * get_model_delta_time ()) * current_flight_dynamics->input_data.cyclic_horizontal_pressure.value;
					//current_flight_dynamics->input_data.cyclic_x.value += (MODEL_FRAME_RATE * get_model_delta_time ()) * (current_flight_dynamics->input_data.cyclic_horizontal_pressure.value);// + current_flight_dynamics->input_data.cyclic_x_trim.value);
				}
				else
				{

					// restore x
					//Werewolf: Removed old debug code, removed redundant multiplications

					if (get_global_cyclic_input () == KEYBOARD_INPUT)
					{
						if (get_current_dynamics_options (DYNAMICS_OPTIONS_KEYBOARD_ASSISTANCE))
						{
							current_flight_dynamics->input_data.cyclic_x.value += ((1.0 / 16.0) * MODEL_FRAME_RATE * get_model_delta_time ()) * (current_flight_dynamics->input_data.cyclic_x_trim.value - current_flight_dynamics->input_data.cyclic_x.value);
						}
						else
						{
							current_flight_dynamics->input_data.cyclic_x.value += ((3.0 / 4.0) * MODEL_FRAME_RATE * get_model_delta_time ()) * (current_flight_dynamics->input_data.cyclic_x_trim.value - current_flight_dynamics->input_data.cyclic_x.value);
						}
					}
					else if (get_global_cyclic_input () == MOUSE_INPUT)
					{
						if (fabs (current_flight_dynamics->input_data.cyclic_x.value) < 5.0)
						{
							current_flight_dynamics->input_data.cyclic_x.value *= 0.8;
						}
					}
				}

				if (current_flight_dynamics->input_data.cyclic_vertical_pressure.value)
				{
					//current_flight_dynamics->input_data.cyclic_y.value += (MODEL_FRAME_RATE * get_model_delta_time ()) * (current_flight_dynamics->input_data.cyclic_vertical_pressure.value + current_flight_dynamics->input_data.cyclic_y_trim.value);
					current_flight_dynamics->input_data.cyclic_y.value += (MODEL_FRAME_RATE * get_model_delta_time ()) * (current_flight_dynamics->input_data.cyclic_vertical_pressure.value);// + current_flight_dynamics->input_data.cyclic_y_trim.value);
				}
				else
				{

					// restore y

					if (get_global_cyclic_input () == KEYBOARD_INPUT)
					{
						if (get_current_dynamics_options (DYNAMICS_OPTIONS_KEYBOARD_ASSISTANCE))
						{
							current_flight_dynamics->input_data.cyclic_y.value += ((1.0 / 16.0) * MODEL_FRAME_RATE * get_model_delta_time ()) * (current_flight_dynamics->input_data.cyclic_y_trim.value - current_flight_dynamics->input_data.cyclic_y.value);
						}
						else
						{
							current_flight_dynamics->input_data.cyclic_y.value += ((3.0 / 4.0) * MODEL_FRAME_RATE * get_model_delta_time ()) * (current_flight_dynamics->input_data.cyclic_y_trim.value - current_flight_dynamics->input_data.cyclic_y.value);
						}
					}
					else if (get_global_cyclic_input () == MOUSE_INPUT)
					{
						if (fabs (current_flight_dynamics->input_data.cyclic_y.value) < 5.0)
						{
							debug_fatal ("CYCLIC: code with delta time");
							current_flight_dynamics->input_data.cyclic_y.value *= 0.8;
						}
					}
				}

				break;
			}

			case JOYSTICK_INPUT:
			{

				int
					joyval;

				float
					input;

				// 030418 loke
				// implemented multiple joystick device selection

				// x

				if (command_line_cyclic_joystick_index == -1)
				{
					joyval = get_joystick_axis (current_flight_dynamics->input_data.cyclic_joystick_device_index, JOYSTICK_DEFAULT_AXIS_ROLL);
				}
				else
				{
					joyval = get_joystick_axis (command_line_cyclic_joystick_index, command_line_cyclic_joystick_x_axis);
				}

				if (command_line_reverse_cyclic_x == 1)
					joyval *= -1;

				if (command_line_nonlinear_cyclic)
				{
					// in non-linear mode it uses a curve described by f(x) = x*x + x
					// gives a not so sensitive control around centre
					input = (2.0 * (float) joyval ) / ((float) JOYSTICK_AXIS_MAXIMUM - (float) JOYSTICK_AXIS_MINIMUM);
					if (input >= 0)
						input *= input;
					else
						input *= -input;
					input += input;
					input *= 50;
				}
				else
					input = (float) (200.0 * (float) joyval ) / ((float) JOYSTICK_AXIS_MAXIMUM - (float) JOYSTICK_AXIS_MINIMUM);

				if (fabs (input) < command_line_dynamics_cyclic_dead_zone)
				{

					input = 0.0;
				}

				current_flight_dynamics->input_data.cyclic_x.value = input;
        
        //ataribaby 1/1/2009 allow trim with ALT HOLD
				if (current_flight_dynamics->auto_hover == HOVER_HOLD_NONE || current_flight_dynamics->auto_hover == HOVER_HOLD_ALTITUDE_LOCK)
					current_flight_dynamics->input_data.cyclic_x.value += current_flight_dynamics->input_data.cyclic_x_trim.value;

				// y

				if (command_line_cyclic_joystick_index == -1)
				{
					joyval = get_joystick_axis (current_flight_dynamics->input_data.cyclic_joystick_device_index, JOYSTICK_DEFAULT_AXIS_PITCH);
				}
				else
				{
					joyval = get_joystick_axis (command_line_cyclic_joystick_index, command_line_cyclic_joystick_y_axis);
				}

				if (command_line_reverse_cyclic_y == 1)
					joyval *= -1;

				if (command_line_nonlinear_cyclic)
				{
					// in non-linear mode it uses a curve described by f(x) = x*x + x
					// gives a not so sensitive control around centre
					input = -2.0 * ((float) joyval ) / ((float) JOYSTICK_AXIS_MAXIMUM - (float) JOYSTICK_AXIS_MINIMUM);
					if (input >= 0)
						input *= input;
					else
						input *= -input;
					input += input;
					input *= 50.0;
				}
				else
					input = -(float) (200.0 * joyval) / (JOYSTICK_AXIS_MAXIMUM - JOYSTICK_AXIS_MINIMUM);

				if (fabs (input) < command_line_dynamics_cyclic_dead_zone)
				{

					input = 0.0;
				}

				current_flight_dynamics->input_data.cyclic_y.value = input;
        
        //ataribaby 1/1/2009 allow trim with ALT HOLD 
				if (current_flight_dynamics->auto_hover == HOVER_HOLD_NONE || current_flight_dynamics->auto_hover == HOVER_HOLD_ALTITUDE_LOCK)
					current_flight_dynamics->input_data.cyclic_y.value += current_flight_dynamics->input_data.cyclic_y_trim.value;

				/*
				debug_log ("CYCLIC: x %f, y %f", ((float) fabs (200.0 * get_joystick_axis(current_flight_dynamics->input_data.cyclic_joystick_device_index, JOYSTICK_DEFAULT_AXIS_ROLL) / (JOYSTICK_AXIS_MAXIMUM - JOYSTICK_AXIS_MINIMUM)),
					((float) fabs (200.0 * get_joystick_axis(current_flight_dynamics->input_data.cyclic_joystick_device_index, JOYSTICK_DEFAULT_AXIS_PITCH)) / (JOYSTICK_AXIS_MAXIMUM - JOYSTICK_AXIS_MINIMUM)));
				*/

				{
					// 030418 loke
					// implemented multiple joystick device selection

					int
						joystick_x_pos,
						joystick_y_pos;

					if (command_line_cyclic_joystick_index == -1)
					{
						joystick_x_pos = get_joystick_axis (current_flight_dynamics->input_data.cyclic_joystick_device_index, JOYSTICK_DEFAULT_AXIS_ROLL);
						joystick_y_pos = get_joystick_axis (current_flight_dynamics->input_data.cyclic_joystick_device_index, JOYSTICK_DEFAULT_AXIS_PITCH);
					}
					else
					{
						joystick_x_pos = get_joystick_axis (command_line_cyclic_joystick_index, command_line_cyclic_joystick_x_axis);
						joystick_y_pos = get_joystick_axis (command_line_cyclic_joystick_index, command_line_cyclic_joystick_y_axis);
					}

					if (((float) fabs (200.0 * joystick_x_pos) / (JOYSTICK_AXIS_MAXIMUM - JOYSTICK_AXIS_MINIMUM) > 10.0) ||
						((float) fabs (200.0 * joystick_y_pos) / (JOYSTICK_AXIS_MAXIMUM - JOYSTICK_AXIS_MINIMUM) > 10.0))
					{

						if ((current_flight_dynamics->auto_hover == HOVER_HOLD_NORMAL) ||
							(current_flight_dynamics->auto_hover == HOVER_HOLD_STABLE))
						{

							set_current_flight_dynamics_auto_hover (HOVER_HOLD_NONE);
							set_current_flight_dynamics_auto_pilot (FALSE);
						}
					}
				}

				break;
			}
		}

	//
	// DEBUG - to get the coolie hat working
	//
	#if 0
	{

		joystick_hat_position
			coolie_position;

		coolie_position = get_joystick_hat( &joystick_devices [current_flight_dynamics->input_data.cyclic_joystick_device_index], 0 );

		switch( coolie_position ) {
		case HAT_CENTERED:
			debug_log ("CYCLIC: coolie centered");
			break;
		case HAT_UP:
			debug_log ("CYCLIC: coolie up");
			break;
		case HAT_LEFT:
			debug_log ("CYCLIC: coolie left");
			break;
		case HAT_DOWN:
			debug_log ("CYCLIC: coolie down");
			break;
		case HAT_RIGHT:
			debug_log ("CYCLIC: coolie right");
			break;
		case HAT_LEFTUP:
			debug_log ("CYCLIC: coolie left+up");
			break;
		case HAT_LEFTDOWN:
			debug_log ("CYCLIC: coolie left+down");
			break;
		case HAT_RIGHTUP:
			debug_log ("CYCLIC: coolie right+up");
			break;
		case HAT_RIGHTDOWN:
			debug_log ("CYCLIC: coolie right+down");
			break;
		default:
			debug_log ("CYCLIC: coolie is on fire");
		}
	}
	#endif

	//
	// Damaged hydraulics
	//

	if (current_flight_dynamics->input_data.cyclic_x.damaged)
	{
		current_flight_dynamics->input_data.cyclic_x.value *= hydraulic_pressure;
		current_flight_dynamics->input_data.cyclic_x.value += damaged_lock_x_pos * (1.0 - hydraulic_pressure);
	}

	if (current_flight_dynamics->input_data.cyclic_y.damaged)
	{
		current_flight_dynamics->input_data.cyclic_y.value *= hydraulic_pressure;
		current_flight_dynamics->input_data.cyclic_y.value += damaged_lock_y_pos * (1.0 - hydraulic_pressure);
	}

	//
	// Damaged Stabaliser
	//

	if (current_flight_dynamics->input_data.cyclic_x_trim.damaged)
		current_flight_dynamics->input_data.cyclic_x_trim.value += (MODEL_FRAME_RATE * get_model_delta_time ()) * (0.5 * sfrand1 () * current_flight_dynamics->input_data.cyclic_x_trim.value);

	if (current_flight_dynamics->input_data.cyclic_y_trim.damaged)
		current_flight_dynamics->input_data.cyclic_y_trim.value += (MODEL_FRAME_RATE * get_model_delta_time ()) * (0.5 * sfrand1 () * current_flight_dynamics->input_data.cyclic_y_trim.value);

	// limit cyclic position

	current_flight_dynamics->input_data.cyclic_x.value = bound (
												//current_flight_dynamics->input_data.cyclic_x.value + current_flight_dynamics->input_data.cyclic_x_trim.value,
												current_flight_dynamics->input_data.cyclic_x.value,
												current_flight_dynamics->input_data.cyclic_x.min,
												current_flight_dynamics->input_data.cyclic_x.max
												);

	current_flight_dynamics->input_data.cyclic_y.value = bound (
												//current_flight_dynamics->input_data.cyclic_y.value + current_flight_dynamics->input_data.cyclic_y_trim.value,
												current_flight_dynamics->input_data.cyclic_y.value,
												current_flight_dynamics->input_data.cyclic_y.min,
												current_flight_dynamics->input_data.cyclic_y.max
												);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void damage_hydraulics(int damaging)
{
	if (damaging)
	{
		hydraulic_pressure = 0.65 + (sfrand1() * 0.1);  // lose some hydraulics pressure immediately
		// lock cyclic in a random position
		damaged_lock_x_pos = sfrand1() * 50.0;
		damaged_lock_y_pos = 25.0 + sfrand1() * 50.0;
		hydraulic_pressure_loss_rate = hydraulic_pressure * frand1() * (MAX_HYDRAULICS_LOSS_RATE - MIN_HYDRAULICS_LOSS_RATE) + MIN_HYDRAULICS_LOSS_RATE;
	}
	else
	{
		hydraulic_pressure = 1.0;
		hydraulic_pressure_loss_rate = 0.0;
	}
}

void damage_primary_hydralics_only(void)
{
	hydraulic_pressure *= 0.75 + (sfrand1() * 0.1);  // lose some hydraulics pressure
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_hydraulic_pressure(void)
{
	return hydraulic_pressure;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_cyclic(void)
{
	damage_hydraulics(FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
