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



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

dynamics_damage_type
	dynamics_damage_database [] =
	{

		{
			"None",
			DYNAMICS_DAMAGE_NONE,
			1.0,
			0.0,
			0.0 * ONE_SECOND,
			FALSE,
			FALSE,
		},
		{
			"Main rotor",
			DYNAMICS_DAMAGE_MAIN_ROTOR,
			0.2,
			0.8,
			60.0 * ONE_SECOND,
			TRUE,
			FALSE,
		},
		{
			"Tail rotor",
			DYNAMICS_DAMAGE_TAIL_ROTOR,
			0.3,
			0.5,
			50.0 * ONE_SECOND,
			TRUE,
			TRUE,
		},
		{
			"Left engine",
			DYNAMICS_DAMAGE_LEFT_ENGINE,
			0.4,
			0.1,
			30.0 * ONE_SECOND,
			TRUE,
			TRUE,
		},
		{
			"Right engine",
			DYNAMICS_DAMAGE_RIGHT_ENGINE,
			0.4,
			0.1,
			30.0 * ONE_SECOND,
			TRUE,
			TRUE,
		},
		{
			"Left engine fire",
			DYNAMICS_DAMAGE_LEFT_ENGINE_FIRE,
			0.6,
			0.3,
			10.0 * ONE_SECOND,
			FALSE,
			TRUE,
		},
		{
			"Right engine fire",
			DYNAMICS_DAMAGE_RIGHT_ENGINE_FIRE,
			0.6,
			0.3,
			10.0 * ONE_SECOND,
			FALSE,
			TRUE,
		},
		{
			"Low Hydraulics pressure",
			DYNAMICS_DAMAGE_LOW_HYDRAULICS,
			0.7,
			0.3,
			20.0 * ONE_SECOND,
			FALSE,
			TRUE,
		},
		{
			"Stabiliser",
			DYNAMICS_DAMAGE_STABILISER,
			0.75,
			0.3,
			20.0 * ONE_SECOND,
			FALSE,
			TRUE,
		},
		{
			"Fuel leak",
			DYNAMICS_DAMAGE_FUEL_LEAK,
			0.6,
			0.1,
			10.0 * ONE_SECOND,
			FALSE,
			TRUE,
		},
		{
			"Low oil pressure",
			DYNAMICS_DAMAGE_LOW_OIL_PRESSURE,
			0.8,
			0.1,
			10.0 * ONE_SECOND,
			FALSE,
			TRUE,
		},
		{
			"High oil pressure",
			DYNAMICS_DAMAGE_HIGH_OIL_PRESSURE,
			0.9,
			0.1,
			10.0 * ONE_SECOND,
			FALSE,
			TRUE,
		},
		{
			"Avionics",
			DYNAMICS_DAMAGE_AVIONICS,
			0.7,
			0.1,
			20.0 * ONE_SECOND,
			FALSE,
			TRUE,
		},
		{
			"Fire Extinguisher",
			DYNAMICS_DAMAGE_FIRE_EXTINGUISHER,
			0.0,
			0.0,
			5.0 * ONE_SECOND,
			FALSE,
			TRUE,
		},
		{
			"Undercarriage",
			DYNAMICS_DAMAGE_UNDERCARRIAGE,
			0.6,
			0.1,
			10.0 * ONE_SECOND,
			FALSE,
			TRUE,
		},
		{
			"APU",
			DYNAMICS_DAMAGE_APU,
			0.0,
			0.1,
			10.0 * ONE_SECOND,
			FALSE,
			TRUE,
		},
		{
			"Main rotor blade",
			DYNAMICS_DAMAGE_MAIN_ROTOR_BLADE,
			0.1,
			0.2,
			10.0 * ONE_SECOND,
			FALSE,
			TRUE,
		},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void dynamics_damage_model (unsigned int damage, int random)
{

	dynamics_damage_types
		damage_array [NUM_DYNAMIC_DAMAGES];

	int
		count;

	dynamics_damage_types
		this_damage;

	if (!get_session_entity ())
	{

		return;
	}

	if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_INVULNERABLE_FROM_COLLISIONS))
	{

		// if invulnerable only allow damage/use of fire extinguisher

		damage = damage & DYNAMICS_DAMAGE_FIRE_EXTINGUISHER;
	}

	if (random)
	{

		damage_array [0] = DYNAMICS_DAMAGE_NONE;

		this_damage = DYNAMICS_DAMAGE_NONE;

		count = 1;

		while (this_damage < NUM_DYNAMICS_DAMAGE_TYPES)
		{

			if (damage & this_damage)
			{

				damage_array [count] = this_damage;

				count ++;
			}

			this_damage = this_damage << 1;
		}

		damage = damage_array [rand16 () % count];

		#if DYNAMICS_DEBUG

		debug_log ("DYNAMICS: randomly selecting damage %d", damage);

		#endif
	}

	notify_avionics_of_dynamics_fault (damage);

	this_damage = DYNAMICS_DAMAGE_NONE;

	while (this_damage < NUM_DYNAMICS_DAMAGE_TYPES)
	{

		if ((damage & this_damage) && (!(current_flight_dynamics->dynamics_damage & this_damage)))
		{

			switch (this_damage)
			{

				case DYNAMICS_DAMAGE_NONE:
				{

					#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: no damage");

					#endif

					current_flight_dynamics->dynamics_damage = DYNAMICS_DAMAGE_NONE;

					current_flight_dynamics->main_blade_pitch.damaged = FALSE;

					current_flight_dynamics->main_rotor_roll_angle.damaged = FALSE;

					current_flight_dynamics->main_rotor_pitch_angle.damaged = FALSE;

					current_flight_dynamics->main_rotor_rpm.damaged = FALSE;

					current_flight_dynamics->tail_blade_pitch.damaged = FALSE;

					current_flight_dynamics->tail_rotor_rpm.damaged = FALSE;

					current_flight_dynamics->left_engine_torque.damaged = FALSE;

					current_flight_dynamics->left_engine_rpm.damaged = FALSE;

					current_flight_dynamics->right_engine_torque.damaged = FALSE;

					current_flight_dynamics->right_engine_rpm.damaged = FALSE;

					current_flight_dynamics->cross_coupling_effect.damaged = FALSE;

					current_flight_dynamics->input_data.cyclic_x.damaged = FALSE;

					current_flight_dynamics->input_data.cyclic_y.damaged = FALSE;

					current_flight_dynamics->input_data.cyclic_x_trim.damaged = FALSE;

					current_flight_dynamics->input_data.cyclic_y_trim.damaged = FALSE;

					break;
				}
				case DYNAMICS_DAMAGE_MAIN_ROTOR:
				{

					//#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: main rotor damage");

					//#endif

					current_flight_dynamics->dynamics_damage |= DYNAMICS_DAMAGE_MAIN_ROTOR;

					current_flight_dynamics->main_blade_pitch.damaged = TRUE;

					current_flight_dynamics->main_rotor_roll_angle.damaged = TRUE;

					current_flight_dynamics->main_rotor_pitch_angle.damaged = TRUE;

					current_flight_dynamics->main_rotor_rpm.damaged = TRUE;

					set_client_server_entity_int_value (get_gunship_entity (), INT_TYPE_MAIN_ROTOR_DAMAGED, TRUE);

					play_client_server_warning_message (get_gunship_entity (), SPEECH_SYSTEM_MAIN_ROTOR_DAMAGED);

					set_current_flight_dynamics_auto_hover (HOVER_HOLD_NONE);

					set_current_flight_dynamics_auto_pilot (FALSE);

					break;
				}
				case DYNAMICS_DAMAGE_TAIL_ROTOR:
				{

					//#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: tail rotor damage");

					//#endif

					current_flight_dynamics->dynamics_damage |= DYNAMICS_DAMAGE_TAIL_ROTOR;

					current_flight_dynamics->tail_blade_pitch.damaged = TRUE;

					current_flight_dynamics->tail_rotor_rpm.damaged = TRUE;

					current_flight_dynamics->cross_coupling_effect.damaged = TRUE;

					set_client_server_entity_int_value (get_gunship_entity (), INT_TYPE_TAIL_ROTOR_DAMAGED, TRUE);

					play_client_server_warning_message (get_gunship_entity (), SPEECH_SYSTEM_TAIL_ROTOR_DAMAGED);

					set_current_flight_dynamics_auto_hover (HOVER_HOLD_NONE);

					set_current_flight_dynamics_auto_pilot (FALSE);

					break;
				}
				case DYNAMICS_DAMAGE_LEFT_ENGINE:
				{

					//#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: left engine damage");

					//#endif

					current_flight_dynamics->dynamics_damage |= DYNAMICS_DAMAGE_LEFT_ENGINE;

					current_flight_dynamics->left_engine_torque.damaged = TRUE;

					current_flight_dynamics->left_engine_rpm.damaged = TRUE;

					play_client_server_warning_message (get_gunship_entity (), SPEECH_SYSTEM_LEFT_ENGINE_FAILURE);

					set_current_flight_dynamics_auto_hover (HOVER_HOLD_NONE);

					set_current_flight_dynamics_auto_pilot (FALSE);
					
					// if both engines damaged, disengage rotor
					if (damage & DYNAMICS_DAMAGE_RIGHT_ENGINE
						|| current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_RIGHT_ENGINE)
					{
						current_flight_dynamics->rotor_brake = TRUE;
						debug_log ("DYNAMICS: rotor disengage due to both engines failure");
					}
					break;
				}
				case DYNAMICS_DAMAGE_RIGHT_ENGINE:
				{

					//#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: right engine damage");

					//#endif

					current_flight_dynamics->dynamics_damage |= DYNAMICS_DAMAGE_RIGHT_ENGINE;

					current_flight_dynamics->right_engine_torque.damaged = TRUE;

					current_flight_dynamics->right_engine_rpm.damaged = TRUE;

					play_client_server_warning_message (get_gunship_entity (), SPEECH_SYSTEM_RIGHT_ENGINE_FAILURE);

					set_current_flight_dynamics_auto_hover (HOVER_HOLD_NONE);

					set_current_flight_dynamics_auto_pilot (FALSE);

					// if both engines damaged, disengage rotor
					if (damage & DYNAMICS_DAMAGE_LEFT_ENGINE
						|| current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_LEFT_ENGINE)
					{
						current_flight_dynamics->rotor_brake = TRUE;
						debug_log ("DYNAMICS: rotor disengage due to both engines failure");
					}
					
					break;
				}
				case DYNAMICS_DAMAGE_LEFT_ENGINE_FIRE:
				{

					//#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: left engine fire damage");

					//#endif

					current_flight_dynamics->dynamics_damage |= DYNAMICS_DAMAGE_LEFT_ENGINE_FIRE;

					play_client_server_warning_message (get_gunship_entity (), SPEECH_SYSTEM_LEFT_ENGINE_FIRE);

					set_current_flight_dynamics_auto_hover (HOVER_HOLD_NONE);

					set_current_flight_dynamics_auto_pilot (FALSE);

					break;
				}
				case DYNAMICS_DAMAGE_RIGHT_ENGINE_FIRE:
				{

					//#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: right engine fire damage");

					//#endif

					current_flight_dynamics->dynamics_damage |= DYNAMICS_DAMAGE_RIGHT_ENGINE_FIRE;

					play_client_server_warning_message (get_gunship_entity (), SPEECH_SYSTEM_RIGHT_ENGINE_FIRE);

					set_current_flight_dynamics_auto_hover (HOVER_HOLD_NONE);

					set_current_flight_dynamics_auto_pilot (FALSE);

					break;
				}
				case DYNAMICS_DAMAGE_LOW_HYDRAULICS:
				{

					//#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: LOW HYDRAULICS damage");

					//#endif

					current_flight_dynamics->dynamics_damage |= DYNAMICS_DAMAGE_LOW_HYDRAULICS;

					current_flight_dynamics->input_data.cyclic_x.damaged = TRUE;

					current_flight_dynamics->input_data.cyclic_y.damaged = TRUE;

					if (sfrand1 () < 0.0)
					{

						play_client_server_warning_message (get_gunship_entity (), SPEECH_SYSTEM_HYDRAULIC_PRESSURE_FAILURE);
					}
					else
					{

						play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_CONTROL_SYSTEMS_DAMAGED);
					}

					set_current_flight_dynamics_auto_hover (HOVER_HOLD_NONE);

					set_current_flight_dynamics_auto_pilot (FALSE);

					break;
				}
				case DYNAMICS_DAMAGE_STABILISER:
				{

					//#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: STABILISER damage");

					//#endif

					current_flight_dynamics->dynamics_damage |= DYNAMICS_DAMAGE_STABILISER;

					set_current_flight_dynamics_auto_hover (HOVER_HOLD_NONE);

					set_current_flight_dynamics_auto_pilot (FALSE);

					if (sfrand1 () < 0.0)
					{

						play_client_server_warning_message (get_gunship_entity (), SPEECH_SYSTEM_STABILISER_DAMAGED);
					}
					else
					{

						play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_CONTROL_SYSTEMS_DAMAGED);
					}

					break;
				}
				case DYNAMICS_DAMAGE_FUEL_LEAK:
				{

					//#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: FUEL_LEAK damage");

					//#endif

					current_flight_dynamics->dynamics_damage |= DYNAMICS_DAMAGE_FUEL_LEAK;

					play_client_server_warning_message (get_gunship_entity (), SPEECH_SYSTEM_FUEL_LEAK);

					break;
				}
				case DYNAMICS_DAMAGE_LOW_OIL_PRESSURE:
				{

					//#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: LOW_OIL_PRESSURE damage");

					//#endif

					current_flight_dynamics->dynamics_damage |= DYNAMICS_DAMAGE_LOW_OIL_PRESSURE;

					current_flight_dynamics->input_data.cyclic_y.damaged = TRUE;

					if (sfrand1 () < 0.0)
					{

						play_client_server_warning_message (get_gunship_entity (), SPEECH_SYSTEM_LOW_ENGINE_OIL_PRESSURE);
					}
					else
					{

						play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_CONTROL_SYSTEMS_DAMAGED);
					}

					set_current_flight_dynamics_auto_hover (HOVER_HOLD_NONE);

					set_current_flight_dynamics_auto_pilot (FALSE);

					break;
				}
				case DYNAMICS_DAMAGE_HIGH_OIL_PRESSURE:
				{

					//#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: HIGH_OIL_PRESSURE damage");

					//#endif

					current_flight_dynamics->dynamics_damage |= DYNAMICS_DAMAGE_HIGH_OIL_PRESSURE;

					current_flight_dynamics->input_data.collective.damaged = TRUE;

					if (sfrand1 () < 0.0)
					{

						play_client_server_warning_message (get_gunship_entity (), SPEECH_SYSTEM_HIGH_ENGINE_OIL_TEMPERATURE);
					}
					else
					{

						play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_CONTROL_SYSTEMS_DAMAGED);
					}

					set_current_flight_dynamics_auto_hover (HOVER_HOLD_NONE);

					set_current_flight_dynamics_auto_pilot (FALSE);

					break;
				}
				case DYNAMICS_DAMAGE_AVIONICS:
				{

					//#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: AVIONICS damage");

					//#endif

					current_flight_dynamics->dynamics_damage |= DYNAMICS_DAMAGE_AVIONICS;

					break;
				}
				case DYNAMICS_DAMAGE_FIRE_EXTINGUISHER:
				{

					//#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: FIRE_EXTINGUISHER damage");

					//#endif

					current_flight_dynamics->dynamics_damage |= DYNAMICS_DAMAGE_FIRE_EXTINGUISHER;

					break;
				}
				case DYNAMICS_DAMAGE_UNDERCARRIAGE:
				{

					//#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: UNDERCARRIAGE damage");

					//#endif

					current_flight_dynamics->dynamics_damage |= DYNAMICS_DAMAGE_UNDERCARRIAGE;

					current_flight_dynamics->undercarriage_state.damaged = TRUE;

					play_client_server_warning_message (get_gunship_entity (), SPEECH_SYSTEM_GEAR_DAMAGED);

					break;
				}
				case DYNAMICS_DAMAGE_APU:
				{
					debug_log ("DYNAMICS: APU damage");
					
					current_flight_dynamics->dynamics_damage |= DYNAMICS_DAMAGE_APU;

					current_flight_dynamics->apu_rpm.max = 0.0;
					current_flight_dynamics->apu_rpm.delta = -100.0;

					current_flight_dynamics->apu_rpm.damaged = TRUE;
					
					break;
				}
				case DYNAMICS_DAMAGE_MAIN_ROTOR_BLADE:
				{
					debug_log ("DYNAMICS: MAIN ROTOR BLADE damaged");
					
					current_flight_dynamics->dynamics_damage |= DYNAMICS_DAMAGE_MAIN_ROTOR_BLADE;
					
					break;	
				}
				default:
				{

					debug_fatal ("DYNAMICS: unknown damage %d", this_damage);
				}
			}
		}

		this_damage = this_damage << 1;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_current_dynamics_options (dynamics_options_types option, int flag)
{

	if (!current_flight_dynamics)
	{

		return;
	}

	switch (option)
	{

		case 	DYNAMICS_OPTIONS_CROSS_COUPLING:
		{

			current_flight_dynamics->dynamics_options.dynamics_options_cross_coupling = flag;

			break;
		}
		case 	DYNAMICS_OPTIONS_DAMAGE:
		{

			current_flight_dynamics->dynamics_options.dynamics_options_damage = flag;

			break;
		}
		case 	DYNAMICS_OPTIONS_DRAW_FLIGHT_PATH:
		{

			current_flight_dynamics->dynamics_options.dynamics_options_draw_flight_path = flag;

			break;
		}
		case 	DYNAMICS_OPTIONS_GROUND_COLLISIONS:
		{

			current_flight_dynamics->dynamics_options.dynamics_options_ground_collisions = flag;

			break;
		}
		case 	DYNAMICS_OPTIONS_GROUND_EFFECT:
		{

			current_flight_dynamics->dynamics_options.dynamics_options_ground_effect = flag;

			break;
		}
		case 	DYNAMICS_OPTIONS_KEYBOARD_ASSISTANCE:
		{

			current_flight_dynamics->dynamics_options.dynamics_options_keyboard_assistance = flag;

			break;
		}
		case 	DYNAMICS_OPTIONS_OBJECT_COLLISIONS:
		{

			current_flight_dynamics->dynamics_options.dynamics_options_object_collisions = flag;

			break;
		}
		case 	DYNAMICS_OPTIONS_OVER_TORQUE:
		{

			current_flight_dynamics->dynamics_options.dynamics_options_over_torque = flag;

			break;
		}
		case 	DYNAMICS_OPTIONS_RETREATING_BLADE_STALL:
		{

			current_flight_dynamics->dynamics_options.dynamics_options_retreating_blade_stall = flag;

			break;
		}
		case 	DYNAMICS_OPTIONS_REVERSE_THROTTLE_INPUT:
		{

			current_flight_dynamics->dynamics_options.dynamics_options_reverse_throttle_input = flag;

			break;
		}
		case DYNAMICS_OPTIONS_TRANSITIONAL_LIFT:
		{

			current_flight_dynamics->dynamics_options.dynamics_options_transitional_lift = flag;

			break;
		}
		case 	DYNAMICS_OPTIONS_VORTEX_RING:
		{

			current_flight_dynamics->dynamics_options.dynamics_options_vortex_ring = flag;

			break;
		}
		case DYNAMICS_OPTIONS_WIND:
		{

			current_flight_dynamics->dynamics_options.dynamics_options_wind = flag;

			break;
		}
		default:
		{

			debug_fatal ("DYNAMICS: unknown option");
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_current_dynamics_options (dynamics_options_types option)
{

	int
		flag;

	if (!current_flight_dynamics)
	{

		return FALSE;
	}

	switch (option)
	{

		case 	DYNAMICS_OPTIONS_CROSS_COUPLING:
		{

			flag = (current_flight_dynamics->dynamics_options.dynamics_options_cross_coupling);

			break;
		}
		case 	DYNAMICS_OPTIONS_DAMAGE:
		{

			flag = (current_flight_dynamics->dynamics_options.dynamics_options_damage);

			break;
		}
		case 	DYNAMICS_OPTIONS_DRAW_FLIGHT_PATH:
		{

			flag = (current_flight_dynamics->dynamics_options.dynamics_options_draw_flight_path);

			break;
		}
		case 	DYNAMICS_OPTIONS_GROUND_COLLISIONS:
		{

			flag = (current_flight_dynamics->dynamics_options.dynamics_options_ground_collisions);

			break;
		}
		case 	DYNAMICS_OPTIONS_GROUND_EFFECT:
		{

			flag = (current_flight_dynamics->dynamics_options.dynamics_options_ground_effect);

			break;
		}
		case 	DYNAMICS_OPTIONS_KEYBOARD_ASSISTANCE:
		{

			flag = current_flight_dynamics->dynamics_options.dynamics_options_keyboard_assistance;

			break;
		}
		case 	DYNAMICS_OPTIONS_OBJECT_COLLISIONS:
		{

			flag = (current_flight_dynamics->dynamics_options.dynamics_options_object_collisions);

			break;
		}
		case 	DYNAMICS_OPTIONS_OVER_TORQUE:
		{

			flag = (current_flight_dynamics->dynamics_options.dynamics_options_over_torque);

			break;
		}
		case 	DYNAMICS_OPTIONS_RETREATING_BLADE_STALL:
		{

			flag = (current_flight_dynamics->dynamics_options.dynamics_options_retreating_blade_stall);

			break;
		}
		case 	DYNAMICS_OPTIONS_REVERSE_THROTTLE_INPUT:
		{

			flag = current_flight_dynamics->dynamics_options.dynamics_options_reverse_throttle_input;

			break;
		}
		case DYNAMICS_OPTIONS_TRANSITIONAL_LIFT:
		{

			flag = (current_flight_dynamics->dynamics_options.dynamics_options_transitional_lift);

			break;
		}
		case 	DYNAMICS_OPTIONS_VORTEX_RING:
		{

			flag = (current_flight_dynamics->dynamics_options.dynamics_options_vortex_ring);

			break;
		}
		case DYNAMICS_OPTIONS_WIND:
		{

			flag = (current_flight_dynamics->dynamics_options.dynamics_options_wind);

			break;
		}
		default:
		{

			debug_fatal ("DYNAMICS: unknown option");
		}

	}

	return flag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_current_dynamics_fatal_damage (void)
{

	float
		fatal_damage_counter;

	int
		damage_count,
		this_damage,
		damage;

	fatal_damage_counter = 0.0;

	damage = current_flight_dynamics->dynamics_damage;

	this_damage = DYNAMICS_DAMAGE_NONE;

	damage_count = 0;

	#if DEBUG_MODULE

	debug_log ("CO_DMG: Assessing damage severity");

	#endif

	while (this_damage < NUM_DYNAMICS_DAMAGE_TYPES)
	{

		if (damage & this_damage)
		{

			fatal_damage_counter += dynamics_damage_database [damage_count].damage_severity;

			#if DEBUG_MODULE

			debug_log ("CO_DMG:    %s damaged %f total %f", dynamics_damage_database [damage_count].name, dynamics_damage_database [damage_count].damage_severity, fatal_damage_counter);

			#endif
		}

		damage_count ++;

		this_damage = this_damage << 1;
	}

	return (fatal_damage_counter >= 1.0) ? TRUE : FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_dynamics_at_keysite (void)
{

	unsigned int
		model_damage,
		damage_count,
		this_damage;

	if ((!get_keysite_currently_landed_at ()) || (!get_gunship_entity ()))
	{

		return;
	}

	//
	// Refuel, only set if inside keysite
	//

	#if !DEMO_VERSION

	if (current_flight_dynamics->refuelling)
	{
		entity
			*keysite;

		float
			max_fuel;

		if (!(current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_FUEL_LEAK))
		{

			//#if DYNAMICS_DEBUG

//			debug_log ("DYNAMICS: refuelling, fuel = %f (max = %f)", current_flight_dynamics->fuel_weight.value, current_flight_dynamics->fuel_weight.max);

			//#endif

			max_fuel = current_flight_dynamics->fuel_weight.max;

			keysite = get_keysite_currently_landed_at ();

			if (keysite)
			{

				if (get_local_entity_float_value (keysite, FLOAT_TYPE_FUEL_SUPPLY_LEVEL) <= 0.0)
				{

					if (!get_connection_list_head ())
					{

						max_fuel *= 0.25;
					}
				}
			}

			if (current_flight_dynamics->fuel_weight.value >= max_fuel)
			{

				current_flight_dynamics->refuelling = FALSE;
			}
			else
			{

				current_flight_dynamics->fuel_weight.value += REFUELLING_RATE * get_delta_time ();
			}

			current_flight_dynamics->fuel_weight.value = bound (current_flight_dynamics->fuel_weight.value,
																				current_flight_dynamics->fuel_weight.min,
																				current_flight_dynamics->fuel_weight.max);
		}
		else
		{

			debug_log ("DYNAMICS: can't refuel till leak is fixed");
		}
	}

	#endif

	//
	// Repair, only set if inside keysite
	//

	if (current_flight_dynamics->repairing)
	{

		if (current_flight_dynamics->dynamics_damage != DYNAMICS_DAMAGE_NONE)
		{

			current_flight_dynamics->damage_repair_time -= get_delta_time ();

			current_flight_dynamics->damage_repair_time = max (current_flight_dynamics->damage_repair_time, 0.0);

			#if DYNAMICS_DEBUG

			debug_log ("DYNAMICS: repairing %d, repair time %f seconds", current_flight_dynamics->damage_repair_time, current_flight_dynamics->damage_repair_time);

			#endif

			//
			// set repair timer to time to repair each part in turn
			//

			if (current_flight_dynamics->damage_repair_time <= 0.0)
			{

				// clear repaired damage
				if ((current_flight_dynamics->repairing_damage != DYNAMICS_DAMAGE_NONE) &&
					(current_flight_dynamics->dynamics_damage & current_flight_dynamics->repairing_damage))
				{

					repair_damage_model (current_flight_dynamics->repairing_damage);
				}

				current_flight_dynamics->repairing_damage = DYNAMICS_DAMAGE_NONE;

				// start repairing next
				this_damage = DYNAMICS_DAMAGE_NONE;

				damage_count = 0;

				model_damage = current_flight_dynamics->dynamics_damage;

				while (this_damage < NUM_DYNAMICS_DAMAGE_TYPES)
				{

					if ((model_damage & this_damage) && (dynamics_damage_database [damage_count].repairable))
					{

						current_flight_dynamics->damage_repair_time = dynamics_damage_database [damage_count].repair_time;

						current_flight_dynamics->repairing_damage = this_damage;

						#if DEBUG_MODULE

						debug_log ("DYNAMICS: repairing %s, repair time %f seconds", dynamics_damage_database [damage_count].name, current_flight_dynamics->damage_repair_time);

						#endif

						break;
					}

					damage_count ++;

					this_damage = this_damage << 1;
				}

				if (current_flight_dynamics->repairing_damage == DYNAMICS_DAMAGE_NONE)
				{

					#if DEBUG_MODULE

					debug_log ("DYNAMICS: model fully repaired");

					#endif

					restore_helicopter_entity (get_gunship_entity (), NULL, get_local_entity_int_value (get_gunship_entity (), INT_TYPE_OPERATIONAL_STATE));

					set_client_server_entity_int_value (get_gunship_entity (), INT_TYPE_DAMAGE_LEVEL, get_local_entity_int_value (get_gunship_entity (), INT_TYPE_INITIAL_DAMAGE_LEVEL));

					transmit_entity_comms_message (ENTITY_COMMS_RESTORE_ENTITY, get_gunship_entity (), get_local_entity_vec3d_ptr (get_gunship_entity (), VEC3D_TYPE_POSITION), get_local_entity_int_value (get_gunship_entity (), INT_TYPE_OPERATIONAL_STATE));
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_dynamics_damage (void)
{

	int
		damage;

	for (damage = 1; damage < NUM_DYNAMICS_DAMAGE_TYPES; damage = damage << 1)
	{

		if (current_flight_dynamics->dynamics_damage & damage)
		{

			switch (damage)
			{

				case DYNAMICS_DAMAGE_MAIN_ROTOR:
				case DYNAMICS_DAMAGE_TAIL_ROTOR:
				case DYNAMICS_DAMAGE_LEFT_ENGINE:
				case DYNAMICS_DAMAGE_RIGHT_ENGINE:
				case DYNAMICS_DAMAGE_LOW_HYDRAULICS:
				case DYNAMICS_DAMAGE_LOW_OIL_PRESSURE:
				case DYNAMICS_DAMAGE_HIGH_OIL_PRESSURE:
				case DYNAMICS_DAMAGE_AVIONICS:
				case DYNAMICS_DAMAGE_FIRE_EXTINGUISHER:
				case DYNAMICS_DAMAGE_UNDERCARRIAGE:
				case DYNAMICS_DAMAGE_APU:
				case DYNAMICS_DAMAGE_MAIN_ROTOR_BLADE:
				{

					break;
				}
				case DYNAMICS_DAMAGE_LEFT_ENGINE_FIRE:
				{

					if (current_flight_dynamics->dynamics_damage & ~DYNAMICS_DAMAGE_LEFT_ENGINE)
					{

						current_flight_dynamics->left_engine_temp.value += 10.0 * get_delta_time ();

						if (current_flight_dynamics->left_engine_temp.value > current_flight_dynamics->left_engine_temp.max)
						{

							dynamics_damage_model (DYNAMICS_DAMAGE_LEFT_ENGINE, FALSE);
						}

						#if DEBUG_MODULE

						debug_log ("DYNAMICS: left engine fire temp %f", current_flight_dynamics->left_engine_temp.value);

						#endif
					}

					break;
				}
				case DYNAMICS_DAMAGE_RIGHT_ENGINE_FIRE:
				{

					if (current_flight_dynamics->dynamics_damage & ~DYNAMICS_DAMAGE_RIGHT_ENGINE)
					{

						current_flight_dynamics->right_engine_temp.value += 10.0 * get_delta_time ();

						if (current_flight_dynamics->right_engine_temp.value > current_flight_dynamics->right_engine_temp.max)
						{

							dynamics_damage_model (DYNAMICS_DAMAGE_RIGHT_ENGINE, FALSE);
						}

						#if DEBUG_MODULE

						debug_log ("DYNAMICS: right engine fire temp %f", current_flight_dynamics->right_engine_temp.value);

						#endif
					}

					break;
				}
				case DYNAMICS_DAMAGE_STABILISER:
				{

					//
					// move cog about ramdomly
					//

					if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AIRBORNE_AIRCRAFT))
					{

						current_flight_dynamics->centre_of_gravity.x += current_flight_dynamics->roll.value * get_model_delta_time ();
						current_flight_dynamics->centre_of_gravity.z -= current_flight_dynamics->pitch.value * get_model_delta_time ();

						current_flight_dynamics->centre_of_gravity.x = bound (current_flight_dynamics->centre_of_gravity.x, -0.1, 0.1);
						current_flight_dynamics->centre_of_gravity.z = bound (current_flight_dynamics->centre_of_gravity.z, -0.1, 0.1);

						#if DEBUG_MODULE

						debug_log ("DYNAMICS: stabaliser damaged : cog %f, %f", current_flight_dynamics->centre_of_gravity.x, current_flight_dynamics->centre_of_gravity.z);

						#endif
					}

					break;
				}

				case DYNAMICS_DAMAGE_FUEL_LEAK:
				{

					current_flight_dynamics->fuel_weight.value -= FUEL_LEAK_RATE * get_delta_time ();

					current_flight_dynamics->fuel_weight.value = max (current_flight_dynamics->fuel_weight.value, 0.0);

					#if DEBUG_MODULE

					debug_log ("DYNAMICS: fuel leak, currently %f", current_flight_dynamics->fuel_weight.value);

					#endif

					break;
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void dynamics_restore_damage_values (void)
{

	switch (get_global_gunship_type ())
	{

		// JB 030313 Fly any aircraft
		default:
		case GUNSHIP_TYPE_APACHE:
		{

			apache_restore_damage_values ();

			break;
		}

		case GUNSHIP_TYPE_COMANCHE:
		{

			comanche_restore_damage_values ();

			break;
		}

		case GUNSHIP_TYPE_HAVOC:
		{

			havoc_restore_damage_values ();

			break;
		}
		case GUNSHIP_TYPE_HOKUM:
		{

			hokum_restore_damage_values ();

			break;
		}
		////Moje 030518 Start
		case GUNSHIP_TYPE_BLACKHAWK:
		{

			blackhawk_restore_damage_values ();

			break;
		}
		////Moje 030518 End
		////Moje 030612 start
		case GUNSHIP_TYPE_HIND:
		{

			hind_restore_damage_values ();

			break;
		}
		////Moje 030612 end
		////Moje 030816 Start
		case GUNSHIP_TYPE_AH64A:
		{

			ah64a_restore_damage_values ();

			break;
		}
		case GUNSHIP_TYPE_KA50:
		{
			ka50_restore_damage_values ();
			break;
		}
		////Moje 030816 end
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_dynamics_damage_currently_repairing_type (void)
{
	int
		val,
		type;

	type = 0;

	val = current_flight_dynamics->repairing_damage >> 1;

	while (val)
	{
		type ++;

		val = val >> 1;
	}

	return type;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void repair_damage_model (unsigned int damage)
{

	unsigned int
		this_damage;

	if (!get_gunship_entity ())
	{

		return;
	}

	this_damage = DYNAMICS_DAMAGE_NONE;

	while (this_damage < NUM_DYNAMICS_DAMAGE_TYPES)
	{

		if ((damage & this_damage) && ((current_flight_dynamics->dynamics_damage & this_damage)))
		{

			current_flight_dynamics->dynamics_damage -= this_damage;

			switch (this_damage)
			{

				case DYNAMICS_DAMAGE_NONE:
				{

					break;
				}
				case DYNAMICS_DAMAGE_MAIN_ROTOR:
				{

					#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: main rotor repaired");

					#endif

					current_flight_dynamics->main_blade_pitch.damaged = FALSE;

					current_flight_dynamics->main_rotor_roll_angle.damaged = FALSE;

					current_flight_dynamics->main_rotor_pitch_angle.damaged = FALSE;

					current_flight_dynamics->main_rotor_rpm.damaged = FALSE;

					restore_helicopter_main_rotors (get_gunship_entity ());
	
					transmit_entity_comms_message (ENTITY_COMMS_RESTORE_ENTITY, get_gunship_entity (), get_local_entity_vec3d_ptr (get_gunship_entity (), VEC3D_TYPE_POSITION), get_local_entity_int_value (get_gunship_entity (), INT_TYPE_OPERATIONAL_STATE));

					set_client_server_entity_int_value (get_gunship_entity (), INT_TYPE_MAIN_ROTOR_DAMAGED, FALSE);

					break;
				}
				case DYNAMICS_DAMAGE_TAIL_ROTOR:
				{

					#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: tail rotor repaired");

					#endif

					current_flight_dynamics->tail_blade_pitch.damaged = FALSE;

					current_flight_dynamics->tail_rotor_rpm.damaged = FALSE;

					current_flight_dynamics->cross_coupling_effect.damaged = FALSE;

					restore_helicopter_tail_rotors (get_gunship_entity ());

					break;
				}
				case DYNAMICS_DAMAGE_LEFT_ENGINE:
				{

					current_flight_dynamics->left_engine_torque.damaged = FALSE;

					current_flight_dynamics->left_engine_rpm.damaged = FALSE;

					#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: left engine repaired");

					#endif

					break;
				}
				case DYNAMICS_DAMAGE_RIGHT_ENGINE:
				{

					current_flight_dynamics->right_engine_torque.damaged = FALSE;

					current_flight_dynamics->right_engine_rpm.damaged = FALSE;

					#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: right engine repaired");

					#endif

					break;
				}
				case DYNAMICS_DAMAGE_LEFT_ENGINE_FIRE:
				{

					#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: left engine fire repaired");

					#endif

					break;
				}
				case DYNAMICS_DAMAGE_RIGHT_ENGINE_FIRE:
				{

					#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: right engine fire repaired");

					#endif

					break;
				}
				case DYNAMICS_DAMAGE_LOW_HYDRAULICS:
				{

					#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: LOW HYDRAULICS repaired");

					#endif

					current_flight_dynamics->input_data.cyclic_x.damaged = FALSE;

					current_flight_dynamics->input_data.cyclic_y.damaged = FALSE;

					break;
				}
				case DYNAMICS_DAMAGE_STABILISER:
				{

					switch (current_flight_dynamics->sub_type)
					{

						case ENTITY_SUB_TYPE_AIRCRAFT_AH64D_APACHE_LONGBOW:
						{

							apache_restore_damage_values ();

							break;
						}
						case ENTITY_SUB_TYPE_AIRCRAFT_MI28N_HAVOC_B:
						{

							havoc_restore_damage_values ();

							break;
						}
						case ENTITY_SUB_TYPE_AIRCRAFT_RAH66_COMANCHE:
						{

							comanche_restore_damage_values ();

							break;
						}
						case ENTITY_SUB_TYPE_AIRCRAFT_KA52_HOKUM_B:
						{

							hokum_restore_damage_values ();

							break;
						}
					////Moje 030527 Start

						case ENTITY_SUB_TYPE_AIRCRAFT_UH60_BLACK_HAWK:
						{

							blackhawk_restore_damage_values ();

							break;
						}
					////Moje 030527 End
					////moje 030612 start
						case ENTITY_SUB_TYPE_AIRCRAFT_MI24D_HIND:
						{

							hind_restore_damage_values ();

							break;
						}
					////Moje 030612 end
					////Moje 030816 Start

						case ENTITY_SUB_TYPE_AIRCRAFT_AH64A_APACHE:
						{

							ah64a_restore_damage_values ();

							break;
						}
						case ENTITY_SUB_TYPE_AIRCRAFT_KA50_HOKUM:
						{
							ka50_restore_damage_values ();
							break;
						}
					////Moje 030816 end
					}

					#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: STABILISER repaired");

					#endif

					break;
				}
				case DYNAMICS_DAMAGE_FUEL_LEAK:
				{

					#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: FUEL_LEAK repaired");

					#endif

					break;
				}
				case DYNAMICS_DAMAGE_LOW_OIL_PRESSURE:
				{

					current_flight_dynamics->input_data.cyclic_y.damaged = FALSE;

					#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: LOW_OIL_PRESSURE repaired");

					#endif

					break;
				}
				case DYNAMICS_DAMAGE_HIGH_OIL_PRESSURE:
				{

					current_flight_dynamics->input_data.collective.damaged = FALSE;

					#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: HIGH_OIL_PRESSURE repaired");

					#endif

					break;
				}
				case DYNAMICS_DAMAGE_AVIONICS:
				{

					#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: AVIONICS repaired");

					#endif

					if (get_keysite_currently_landed_at ())
					{
	
						// sort out what avionics to repair.
						switch (get_local_entity_int_value (get_keysite_currently_landed_at (), INT_TYPE_ENTITY_SUB_TYPE))
						{
	
							case ENTITY_SUB_TYPE_KEYSITE_FARP:
							{
	
								partially_repair_local_entity_avionics (get_gunship_entity ());
	
								break;
							}
							default:
							{
	
								fully_repair_local_entity_avionics (get_gunship_entity ());
	
								break;
							}
						}
					}
					else
					{
	
						fully_repair_local_entity_avionics (get_gunship_entity ());
					}

					break;
				}
				case DYNAMICS_DAMAGE_FIRE_EXTINGUISHER:
				{

					#if DEBUG_MODULE

					debug_log ("DYNAMICS: FIRE EXTINGUISHER repaired");

					#endif

					fire_extinguisher_used = FALSE;

					break;
				}
				case DYNAMICS_DAMAGE_UNDERCARRIAGE:
				{

					#if DEBUG_MODULE

					debug_log ("DYNAMICS: UNDERCARRIAGE repaired");

					#endif

					current_flight_dynamics->undercarriage_state.damaged = FALSE;

					break;
				}
				case DYNAMICS_DAMAGE_APU:
				{
					current_flight_dynamics->apu_rpm.damaged = FALSE;
					
					break;
				}
				case DYNAMICS_DAMAGE_MAIN_ROTOR_BLADE:
				{
					break;	
				}
				default:
				{

					debug_fatal ("DYNAMICS: unknown damage %d", this_damage);
				}
			}
		}

		this_damage = this_damage << 1;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void damage_entity_to_flight_model (entity *en)
{

	float
		damage_level;

	unsigned int
		this_damage;

	if (!current_flight_dynamics)
	{

		return;
	}

	this_damage = DYNAMICS_DAMAGE_NONE;

	damage_level = 0.0;

	while (this_damage < NUM_DYNAMICS_DAMAGE_TYPES)
	{

		if (current_flight_dynamics->dynamics_damage & this_damage)
		{

			switch (this_damage)
			{

				case DYNAMICS_DAMAGE_NONE:
				{

					break;
				}
				case DYNAMICS_DAMAGE_MAIN_ROTOR:
				{

					damage_level += 0.6;

					#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: main rotor damaged");

					#endif

					break;
				}
				case DYNAMICS_DAMAGE_TAIL_ROTOR:
				{

					damage_level += 0.8;

					#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: tail rotor damaged");

					#endif

					break;
				}
				case DYNAMICS_DAMAGE_LEFT_ENGINE:
				{

					damage_level += 0.4;

					#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: left engine damaged");

					#endif

					break;
				}
				case DYNAMICS_DAMAGE_RIGHT_ENGINE:
				{

					damage_level += 0.4;

					#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: right engine damaged");

					#endif

					break;
				}
				case DYNAMICS_DAMAGE_LEFT_ENGINE_FIRE:
				{

					damage_level += 0.2;

					#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: left engine fire damaged");

					#endif

					break;
				}
				case DYNAMICS_DAMAGE_RIGHT_ENGINE_FIRE:
				{

					damage_level += 0.2;

					#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: right engine fire damaged");

					#endif

					break;
				}
				case DYNAMICS_DAMAGE_LOW_HYDRAULICS:
				{

					damage_level += 0.2;

					#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: LOW HYDRAULICS damaged");

					#endif

					break;
				}
				case DYNAMICS_DAMAGE_STABILISER:
				{

					damage_level += 0.2;

					#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: STABILISER damaged");

					#endif

					break;
				}
				case DYNAMICS_DAMAGE_FUEL_LEAK:
				{

					damage_level += 0.1;

					#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: FUEL_LEAK damaged");

					#endif

					break;
				}
				case DYNAMICS_DAMAGE_LOW_OIL_PRESSURE:
				{

					damage_level += 0.1;

					#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: LOW_OIL_PRESSURE damaged");

					#endif

					break;
				}
				case DYNAMICS_DAMAGE_HIGH_OIL_PRESSURE:
				{

					damage_level += 0.1;

					#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: HIGH_OIL_PRESSURE damaged");

					#endif

					break;
				}
				case DYNAMICS_DAMAGE_AVIONICS:
				{

					damage_level += 0.1;

					#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: AVIONICS damaged");

					#endif

					break;
				}
				case DYNAMICS_DAMAGE_FIRE_EXTINGUISHER:
				{

					damage_level += 0.0;

					#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: FIRE_EXTINGUISHER damaged");

					#endif

					break;
				}
				case DYNAMICS_DAMAGE_UNDERCARRIAGE:
				{

					damage_level += 0.1;

					#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: UNDERCARRIAGE damaged");

					#endif

					break;
				}
				case DYNAMICS_DAMAGE_APU:
				{
					damage_level += 0.1;

					#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: APU damaged");

					#endif
					
					break;
				}
				case DYNAMICS_DAMAGE_MAIN_ROTOR_BLADE:
				{
					damage_level += 0.2;

					#if DYNAMICS_DEBUG

					debug_log ("DYNAMICS: MAIN ROTOR BLADE damaged");

					#endif

					break;	
				}
				default:
				{

					debug_fatal ("DYNAMICS: unknown damage %d", this_damage);
				}
			}
		}

		this_damage = this_damage << 1;
	}

	damage_level = bound (damage_level, 0.0, 0.9);

	damage_level = 1.0 - damage_level;

	damage_level *= get_local_entity_int_value (en, INT_TYPE_INITIAL_DAMAGE_LEVEL);

	set_client_server_entity_int_value (en, INT_TYPE_DAMAGE_LEVEL, damage_level);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void damage_helicopter_via_damage_level (entity *en, entity *aggressor)
{

	int
		damage;

	float
		en_damage_factor;

	ASSERT (get_local_entity_int_value (en, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI);

	en_damage_factor = (float) get_local_entity_int_value (en, INT_TYPE_DAMAGE_LEVEL) / get_local_entity_int_value (en, INT_TYPE_INITIAL_DAMAGE_LEVEL);

	for (damage = 0; damage < sizeof (dynamics_damage_database) / sizeof (dynamics_damage_type); damage ++)
	{

		if (dynamics_damage_database [damage].kickin_value >= en_damage_factor)
		{

			if (get_gunship_entity () == en)
			{

				dynamics_damage_model (1 << damage, TRUE);
			}
			else
			{

				transmit_entity_comms_message (ENTITY_COMMS_DAMAGE_PLAYER, en, 1 << damage, TRUE);
			}
/*
			if (aggressor)
			{

				if (dynamics_damage_database [damage].store_aggressor_in_debrief)
				{
	
					debug_log ("CO_DMG: storing in debrief that %s %s caused damage to user",
									entity_type_names [get_local_entity_type (aggressor)],
									get_local_entity_string (aggressor, STRING_TYPE_FULL_NAME));
	
//					set_debrief_aggressor_entity (aggressor);
				}
			}
*/
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
