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

#define DEBUG_MODULE	0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MASTER_CAUTION_FLASH_RATE	(0.5)

static int
	master_caution_alert,
	engine_damage_imminent_status,
	previous_engine_damage_imminent_status;

static float
	master_caution_flash_timer;

static float
	master_caution_sound_timer;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define GEAR_TRANSITION_FLASH_RATE	(0.25)

static int
	gear_transition_state;

static float
	gear_transition_timer;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void initialise_master_caution (void)
{
	master_caution_alert = FALSE;

	master_caution_flash_timer = 0.0;

	master_caution_sound_timer = 0.0;

	engine_damage_imminent_status = FALSE;

	previous_engine_damage_imminent_status = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void deinitialise_master_caution (void)
{
	if (get_gunship_entity ())
	{
		pause_local_entity_sound_type (get_gunship_entity (), ENTITY_SUB_TYPE_EFFECT_SOUND_MCA, 0.5);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void activate_hokum_master_caution (void)
{
	hokum_lamps.master_caution = 1;

	master_caution_alert = TRUE;

	master_caution_flash_timer = MASTER_CAUTION_FLASH_RATE;

	master_caution_sound_timer = 3.0;

	resume_local_entity_sound_type (get_gunship_entity (), ENTITY_SUB_TYPE_EFFECT_SOUND_MCA);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deactivate_hokum_master_caution (void)
{
	hokum_lamps.master_caution = 0;

	master_caution_alert = FALSE;

	master_caution_flash_timer = 0.0;

	master_caution_sound_timer = 0.0;

	pause_local_entity_sound_type (get_gunship_entity (), ENTITY_SUB_TYPE_EFFECT_SOUND_MCA, 0.5);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_master_caution (void)
{
	//
	// monitor engine damage
	//

	engine_damage_imminent_status = get_current_flight_dynamics_engine_damage_imminent ();

	if ((!previous_engine_damage_imminent_status) && engine_damage_imminent_status)
	{
		play_client_server_warning_message (get_gunship_entity (), SPEECH_SYSTEM_ENGINE_OVERTORQUE);

		activate_hokum_master_caution ();
	}

	previous_engine_damage_imminent_status = engine_damage_imminent_status;

	//
	// update master caution lamp
	//

	if (master_caution_alert)
	{
		master_caution_flash_timer -= get_delta_time ();

		if (master_caution_flash_timer <= 0.0)
		{
			master_caution_flash_timer = MASTER_CAUTION_FLASH_RATE;

			hokum_lamps.master_caution ^= 1;
		}

		master_caution_sound_timer -= get_delta_time ();

		if (master_caution_sound_timer <= 0.0)
		{
			master_caution_sound_timer = 0.0;

			pause_local_entity_sound_type (get_gunship_entity (), ENTITY_SUB_TYPE_EFFECT_SOUND_MCA, 0.5);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// Note that all lamps are extinguished in initialise_hokum_lamps ().
//

void initialise_hokum_lamp_avionics (void)
{
	initialise_master_caution ();

	gear_transition_state = 0;

	gear_transition_timer = 0.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_hokum_lamp_avionics (void)
{
	deinitialise_master_caution ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_hokum_lamp_avionics (void)
{
	entity
		*en;

	int
		gear_state;

	en = get_gunship_entity ();

	update_master_caution ();

	////////////////////////////////////////

	gear_state = get_local_entity_undercarriage_state (en);

	gear_transition_timer -= get_delta_time ();

	if (gear_transition_timer <= 0.0)
	{
		gear_transition_state ^= 1;

		gear_transition_timer = GEAR_TRANSITION_FLASH_RATE;
	}

	////////////////////////////////////////

	hokum_lamps.left_engine_fire = get_dynamics_damage_type (DYNAMICS_DAMAGE_LEFT_ENGINE_FIRE);

	hokum_lamps.apu_fire = 0;

	hokum_lamps.right_engine_fire = get_dynamics_damage_type (DYNAMICS_DAMAGE_RIGHT_ENGINE_FIRE);

	hokum_lamps.fire_extinguiser = fire_extinguisher_used;

	hokum_lamps.hydraulic_pressure = get_dynamics_damage_type (DYNAMICS_DAMAGE_LOW_HYDRAULICS);

	hokum_lamps.oil_pressure = get_dynamics_damage_type (DYNAMICS_DAMAGE_LOW_OIL_PRESSURE) || get_dynamics_damage_type (DYNAMICS_DAMAGE_HIGH_OIL_PRESSURE);

	hokum_lamps.oil_temperature = 0;

	hokum_lamps.overtorque = get_current_flight_dynamics_overtorque ();

	hokum_lamps.rotor_rpm = get_current_flight_dynamics_low_rotor_rpm ();

	hokum_lamps.fuel_low = current_flight_dynamics->fuel_weight.value < (current_flight_dynamics->fuel_weight.max * 0.25);

	hokum_lamps.rotor_brake = get_current_flight_dynamics_rotor_brake ();

	hokum_lamps.wheel_brake = get_current_flight_dynamics_wheel_brake ();

	hokum_lamps.navigation_lights = get_local_entity_int_value (en, INT_TYPE_LIGHTS_ON);

	hokum_lamps.hover_hold = get_current_flight_dynamics_auto_hover ();

	hokum_lamps.altitude_hold = get_current_flight_dynamics_altitude_lock ();

	hokum_lamps.auto_pilot = get_current_flight_dynamics_auto_pilot ();

	hokum_lamps.radar = get_local_entity_int_value (en, INT_TYPE_RADAR_ON);

	hokum_lamps.laser = get_local_entity_int_value (en, INT_TYPE_LASER_ON);

	hokum_lamps.radar_jammer = get_local_entity_int_value (en, INT_TYPE_RADAR_JAMMER_ON);

	hokum_lamps.ir_jammer = get_local_entity_int_value (en, INT_TYPE_INFRA_RED_JAMMER_ON);

	hokum_lamps.auto_counter_measures = get_global_auto_counter_measures ();

	hokum_lamps.ase_auto_page = get_global_ase_auto_page ();

	hokum_lamps.gear_damaged = get_dynamics_damage_type (DYNAMICS_DAMAGE_UNDERCARRIAGE);

	switch (gear_state)
	{
		////////////////////////////////////////
		case AIRCRAFT_UNDERCARRIAGE_UP:
		////////////////////////////////////////
		{
			hokum_lamps.gear_status = 1;

			hokum_lamps.gear_red = 1;

			break;
		}
		////////////////////////////////////////
		case AIRCRAFT_UNDERCARRIAGE_LOWERING:
		////////////////////////////////////////
		{
			hokum_lamps.gear_status = gear_transition_state;

			hokum_lamps.gear_red = 0;

			break;
		}
		////////////////////////////////////////
		case AIRCRAFT_UNDERCARRIAGE_DOWN:
		////////////////////////////////////////
		{
			hokum_lamps.gear_status = 1;

			hokum_lamps.gear_red = 0;

			break;
		}
		////////////////////////////////////////
		case AIRCRAFT_UNDERCARRIAGE_RAISING:
		////////////////////////////////////////
		{
			hokum_lamps.gear_status = gear_transition_state;

			hokum_lamps.gear_red = 1;

			break;
		}
	}

	hokum_lamps.pilot_lh_mfd_focus = get_hokum_mfd_has_focus (HOKUM_MFD_LOCATION_PILOT_LHS);

	hokum_lamps.pilot_rh_mfd_focus = get_hokum_mfd_has_focus (HOKUM_MFD_LOCATION_PILOT_RHS);

	hokum_lamps.co_pilot_lh_mfd_focus = get_hokum_mfd_has_focus (HOKUM_MFD_LOCATION_CO_PILOT_LHS);

	hokum_lamps.co_pilot_rh_mfd_focus = get_hokum_mfd_has_focus (HOKUM_MFD_LOCATION_CO_PILOT_RHS);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
