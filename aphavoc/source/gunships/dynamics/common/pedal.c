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

void pedal_left (event *ev)
{

	if (ev->state == KEY_STATE_DOWN)
	{

		current_flight_dynamics->input_data.pedal_input_pressure |= PEDAL_PRESSURE_LEFT;
	}
	else
	{

		current_flight_dynamics->input_data.pedal_input_pressure ^= PEDAL_PRESSURE_LEFT;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pedal_right (event *ev)
{

	if (ev->state == KEY_STATE_DOWN)
	{

		current_flight_dynamics->input_data.pedal_input_pressure |= PEDAL_PRESSURE_RIGHT;
	}
	else
	{

		current_flight_dynamics->input_data.pedal_input_pressure ^= PEDAL_PRESSURE_RIGHT;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pedal_mouse_input (event *ev)
{

#if 0

	current_flight_dynamics->input_data.pedal_pressure.value += (ev->dx);

#else

	current_flight_dynamics->input_data.pedal.value += (ev->dx);

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_pedal_pressure_inputs (void)
{
	if (trim_button_held)
		current_flight_dynamics->input_data.pedal.delta = current_flight_dynamics->input_data.pedal_trim.value;
	else
		switch (get_global_pedal_input ())
		{

			case KEYBOARD_INPUT:
			case MOUSE_INPUT:
			{

				if (current_flight_dynamics->input_data.pedal_input_pressure & PEDAL_PRESSURE_LEFT)
				{

					if (current_flight_dynamics->input_data.pedal_pressure.value > 0.0)
					{

						// slowing down
						current_flight_dynamics->input_data.pedal_pressure.value -= (50 * get_delta_time ()) * current_flight_dynamics->input_data.pedal_pressure.value;
					}
					else
					{

						// speeding up
						current_flight_dynamics->input_data.pedal_pressure.value += 1 * get_delta_time ();
					}

					//

					if (current_flight_dynamics->input_data.pedal.value > 0.0)
					{

						// slowing down
						current_flight_dynamics->input_data.pedal.value -= (5.0f * get_delta_time ()) * current_flight_dynamics->input_data.pedal.value;
					}
					else
					{

						// speeding up
						current_flight_dynamics->input_data.pedal.value = current_flight_dynamics->input_data.pedal.value;
					}

					current_flight_dynamics->input_data.pedal_pressure.value -= 50 * get_delta_time ();
				}
				else if (current_flight_dynamics->input_data.pedal_input_pressure & PEDAL_PRESSURE_RIGHT)
				{

					if (current_flight_dynamics->input_data.pedal_pressure.value < 0.0)
					{

						// slowing down
						current_flight_dynamics->input_data.pedal_pressure.value -= (50 * get_delta_time ()) * current_flight_dynamics->input_data.pedal_pressure.value;
					}
					else
					{

						// speeding up
						current_flight_dynamics->input_data.pedal_pressure.value -= 1 * get_delta_time ();
					}

					//

					if (current_flight_dynamics->input_data.pedal.value < 0.0)
					{

						// slowing down
						current_flight_dynamics->input_data.pedal.value -= (5.0f * get_delta_time ()) * current_flight_dynamics->input_data.pedal.value;
					}
					else
					{

						// speeding up
						current_flight_dynamics->input_data.pedal.value = current_flight_dynamics->input_data.pedal.value;
					}

					current_flight_dynamics->input_data.pedal_pressure.value += 50 * get_delta_time ();
				}
				else
				{

					if (fabs (current_flight_dynamics->input_data.pedal_pressure.value) < 1.0)
					{

						current_flight_dynamics->input_data.pedal_pressure.value = 0.0;
					}
					else
					{

						current_flight_dynamics->input_data.pedal_pressure.value -= (5.0f * get_delta_time ()) * current_flight_dynamics->input_data.pedal_pressure.value;
					}

					current_flight_dynamics->input_data.pedal.value -= 1.0 * ((current_flight_dynamics->input_data.pedal.value - current_flight_dynamics->input_data.pedal_trim.value ) * get_delta_time ());
				}

				current_flight_dynamics->input_data.pedal_pressure.value = bound (current_flight_dynamics->input_data.pedal_pressure.value,
																					current_flight_dynamics->input_data.pedal_pressure.min,
																					current_flight_dynamics->input_data.pedal_pressure.max
																					);

				// recalculate pedal position

				if (current_flight_dynamics->input_data.pedal_pressure.value)
				{

					current_flight_dynamics->input_data.pedal.value += (1 * get_delta_time ()) * current_flight_dynamics->input_data.pedal_pressure.value;
				}
				else
				{

					// restore

					//if ((global_options.cyclic_input == KEYBOARD_INPUT) && (trim_control))
					{

						//current_flight_dynamics->input_data.pedal.value *= 0.5;
						current_flight_dynamics->input_data.pedal.value -= ((get_delta_time ()) / 2.0) * (current_flight_dynamics->input_data.pedal.value - current_flight_dynamics->input_data.pedal_trim.value);
					}
				}

				break;
			}

			case RUDDER_INPUT:
			{

				int
					joyval;

				float
					lag;

				// 030418 loke
				// implemented multiple joystick device selection
				if (command_line_rudder_joystick_index == -1)
				{
					joyval = get_joystick_axis (current_flight_dynamics->input_data.cyclic_joystick_device_index, JOYSTICK_DEFAULT_AXIS_YAW);
				}
				else
				{
					joyval = get_joystick_axis (command_line_rudder_joystick_index, command_line_rudder_joystick_axis);
				}

				// Retro 17Jul2004
				if (command_line_reverse_pedal)
				{
					joyval *= -1;
				}
				// Retro 17Jul2004 end

				if (command_line_nonlinear_cyclic)
				{
					// in non-linear mode it uses a curve described by f(x) = x*x + x
					// gives a not so sensitive control around centre
					float input = 2.0 * ((float) joyval ) / ((float) JOYSTICK_AXIS_MAXIMUM - (float) JOYSTICK_AXIS_MINIMUM);
					if (input >= 0)
						input *= input;
					else
						input *= -input;
					input += input;
					input *= 50.0;

					current_flight_dynamics->input_data.pedal.delta = input;
				}
				else
					current_flight_dynamics->input_data.pedal.delta = (float) (200.0 * (float) joyval ) / ((float) JOYSTICK_AXIS_MAXIMUM - (float) JOYSTICK_AXIS_MINIMUM);

				if (current_flight_dynamics->input_data.pedal.delta < -0.5)
				{

					current_flight_dynamics->input_data.pedal_input_pressure = PEDAL_PRESSURE_LEFT;
				}
				else if (current_flight_dynamics->input_data.pedal.delta > 0.5)
				{

					current_flight_dynamics->input_data.pedal_input_pressure = PEDAL_PRESSURE_RIGHT;
				}
				else
				{

					current_flight_dynamics->input_data.pedal_input_pressure = PEDAL_PRESSURE_NONE;
				}

				current_flight_dynamics->input_data.pedal.delta += current_flight_dynamics->input_data.pedal_trim.value;

				// vary lag depending if its demand or restore
				if (fabs (current_flight_dynamics->input_data.pedal.value) < fabs (current_flight_dynamics->input_data.pedal.delta))
				{

					lag = 2.0 * command_line_dynamics_rudder_acceleration;
				}
				else
				{

					lag = 3.0 * command_line_dynamics_rudder_value;
				}

				current_flight_dynamics->input_data.pedal.value += (lag * get_delta_time ()) * (current_flight_dynamics->input_data.pedal.delta - current_flight_dynamics->input_data.pedal.value);

				//debug_log ("pedal %f", current_flight_dynamics->input_data.pedal.value);

				break;
			}
		}

	current_flight_dynamics->input_data.pedal.value = bound (current_flight_dynamics->input_data.pedal.value,
												current_flight_dynamics->input_data.pedal.min,
												current_flight_dynamics->input_data.pedal.max);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
