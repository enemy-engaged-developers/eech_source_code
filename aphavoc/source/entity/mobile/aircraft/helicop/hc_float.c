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

static void set_local_float_value (entity *en, float_types type, float value)
{
	helicopter
		*raw;

	#if DEBUG_MODULE

	debug_log_entity_args (ENTITY_DEBUG_LOCAL, ENTITY_DEBUG_FLOAT_VALUE, en, type, value);

	#endif

	raw = (helicopter *) get_local_entity_data (en);

	switch (type)
	{
		////////////////////////////////////////
		case FLOAT_TYPE_FUEL_SUPPLY_LEVEL:
		////////////////////////////////////////
		{

			raw->fuel_supply_level = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_INVULNERABLE_TIMER:
		////////////////////////////////////////
		{
			raw->invulnerable_timer = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_MAIN_ROTOR_BLADE_CONING_ANGLE:
		////////////////////////////////////////
		{
			raw->main_rotor_blade_coning_angle = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_MAIN_ROTOR_PITCH:
		////////////////////////////////////////
		{
			raw->main_rotor_pitch = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_MAIN_ROTOR_ROLL:
		////////////////////////////////////////
		{
			raw->main_rotor_roll = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_MAIN_ROTOR_RPM:
		////////////////////////////////////////
		{
			raw->main_rotor_rpm = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_MAIN_ROTOR_SPIN_UP_TIMER:
		////////////////////////////////////////
		{
			raw->main_rotor_spin_up_timer = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_TAIL_ROTOR_RPM:
		////////////////////////////////////////
		{
			raw->tail_rotor_rpm = value;

			break;
		}
		////////////////////////////////////////
		
		// Jabberwock 050310 MP Cannon bug
		case FLOAT_TYPE_PLAYER_WEAPON_HEADING:
		////////////////////////////////////////
		{
			raw->player_weapon_heading = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_PLAYER_WEAPON_PITCH:
		////////////////////////////////////////
		{
			raw->player_weapon_pitch = value;

			break;
		}
		// Jabberwock 050310 ends
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal_invalid_float_type (en, type);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_remote_float_value (entity *en, float_types type, float value)
{
	#if DEBUG_MODULE

	debug_log_entity_args (ENTITY_DEBUG_REMOTE, ENTITY_DEBUG_FLOAT_VALUE, en, type, value);

	#endif

	transmit_entity_comms_message (ENTITY_COMMS_FLOAT_VALUE, en, type, value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_server_float_value (entity *en, float_types type, float value)
{
	validate_client_server_local_fn ();

	set_local_float_value (en, type, value);

	validate_client_server_remote_fn ();

	set_remote_float_value (en, type, value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_client_float_value (entity *en, float_types type, float value)
{
	if (get_comms_data_flow () == COMMS_DATA_FLOW_TX)
	{
		validate_client_server_remote_fn ();

		set_remote_float_value (en, type, value);
	}
	else
	{
		validate_client_server_local_fn ();

		set_local_float_value (en, type, value);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float get_local_float_value (entity *en, float_types type)
{
	helicopter
		*raw;

	float
		value;

	raw = (helicopter *) get_local_entity_data (en);

	switch (type)
	{
		////////////////////////////////////////
		case FLOAT_TYPE_FUEL_SUPPLY_LEVEL:
		////////////////////////////////////////
		{
			value = raw->fuel_supply_level;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_INVULNERABLE_TIMER:
		////////////////////////////////////////
		{
			value = raw->invulnerable_timer;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_MAIN_ROTOR_BLADE_CONING_ANGLE:
		////////////////////////////////////////
		{
			value = raw->main_rotor_blade_coning_angle;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_MAIN_ROTOR_PITCH:
		////////////////////////////////////////
		{
			value = raw->main_rotor_pitch;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_MAIN_ROTOR_ROLL:
		////////////////////////////////////////
		{
			value = raw->main_rotor_roll;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_MAIN_ROTOR_RPM:
		////////////////////////////////////////
		{
			value = raw->main_rotor_rpm;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_MAIN_ROTOR_SPIN_UP_TIMER:
		////////////////////////////////////////
		{
			value = raw->main_rotor_spin_up_timer;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_RADAR_STEALTH_FACTOR:
		////////////////////////////////////////
		{
			value = NO_RADAR_STEALTH_FACTOR;

			if (raw->ac.mob.sub_type == ENTITY_SUB_TYPE_AIRCRAFT_RAH66_COMANCHE)
				if (get_local_entity_weapon_system_ready_state (en) == WEAPON_SYSTEM_READY_CLOSED)
					value -= NO_RADAR_STEALTH_FACTOR * 0.4;

			if (!get_comanche_stub_wings_attached (en))
				value -= NO_RADAR_STEALTH_FACTOR * 0.35;
				
			if (get_local_entity_undercarriage_state (en) == AIRCRAFT_UNDERCARRIAGE_UP)
				value -= NO_RADAR_STEALTH_FACTOR * 0.1;

			ASSERT (value > 0.0);

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_TAIL_ROTOR_RPM:
		////////////////////////////////////////
		{
			value = raw->tail_rotor_rpm;

			break;
		}
		////////////////////////////////////////
		
		// Jabberwock 050310 MP Cannon bug
		case FLOAT_TYPE_PLAYER_WEAPON_HEADING:
		////////////////////////////////////////
		{
			value = raw->player_weapon_heading;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_PLAYER_WEAPON_PITCH:
		////////////////////////////////////////
		{
			value = raw->player_weapon_pitch;

			break;
		}
		// Jabberwock 050310 ends
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal_invalid_float_type (en, type);

			break;
		}
	}

	return (value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_helicopter_float_value_functions (void)
{
	fn_set_local_entity_raw_float_value			[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_FUEL_SUPPLY_LEVEL]					 		= set_local_float_value;
	fn_set_local_entity_float_value				[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_FUEL_SUPPLY_LEVEL]							= set_local_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_FUEL_SUPPLY_LEVEL][COMMS_MODEL_SERVER]	= set_server_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_FUEL_SUPPLY_LEVEL][COMMS_MODEL_CLIENT]	= set_client_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_FUEL_SUPPLY_LEVEL]						  	= get_local_float_value;

	fn_set_local_entity_raw_float_value			[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_INVULNERABLE_TIMER]					 		= set_local_float_value;
	fn_set_local_entity_float_value				[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_INVULNERABLE_TIMER]							= set_local_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_INVULNERABLE_TIMER][COMMS_MODEL_SERVER]	= set_server_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_INVULNERABLE_TIMER][COMMS_MODEL_CLIENT]	= set_client_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_INVULNERABLE_TIMER]						  	= get_local_float_value;

	fn_set_local_entity_raw_float_value			[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_MAIN_ROTOR_BLADE_CONING_ANGLE]					 		= set_local_float_value;
	fn_set_local_entity_float_value				[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_MAIN_ROTOR_BLADE_CONING_ANGLE]							= set_local_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_MAIN_ROTOR_BLADE_CONING_ANGLE][COMMS_MODEL_SERVER]	= set_server_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_MAIN_ROTOR_BLADE_CONING_ANGLE][COMMS_MODEL_CLIENT]	= set_client_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_MAIN_ROTOR_BLADE_CONING_ANGLE]						  	= get_local_float_value;

	fn_set_local_entity_raw_float_value			[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_MAIN_ROTOR_PITCH]					 			= set_local_float_value;
	fn_set_local_entity_float_value				[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_MAIN_ROTOR_PITCH]								= set_local_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_MAIN_ROTOR_PITCH][COMMS_MODEL_SERVER]	= set_server_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_MAIN_ROTOR_PITCH][COMMS_MODEL_CLIENT]	= set_client_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_MAIN_ROTOR_PITCH]						  		= get_local_float_value;

	fn_set_local_entity_raw_float_value			[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_MAIN_ROTOR_ROLL]					 			= set_local_float_value;
	fn_set_local_entity_float_value				[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_MAIN_ROTOR_ROLL]								= set_local_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_MAIN_ROTOR_ROLL][COMMS_MODEL_SERVER]	= set_server_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_MAIN_ROTOR_ROLL][COMMS_MODEL_CLIENT]	= set_client_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_MAIN_ROTOR_ROLL]						  		= get_local_float_value;

	fn_set_local_entity_raw_float_value			[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_MAIN_ROTOR_RPM]				 				= set_local_float_value;
	fn_set_local_entity_float_value				[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_MAIN_ROTOR_RPM]								= set_local_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_MAIN_ROTOR_RPM][COMMS_MODEL_SERVER]		= set_server_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_MAIN_ROTOR_RPM][COMMS_MODEL_CLIENT]		= set_client_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_MAIN_ROTOR_RPM]					  			= get_local_float_value;

	fn_set_local_entity_raw_float_value			[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_MAIN_ROTOR_SPIN_UP_TIMER]				 				= set_local_float_value;
	fn_set_local_entity_float_value				[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_MAIN_ROTOR_SPIN_UP_TIMER]								= set_local_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_MAIN_ROTOR_SPIN_UP_TIMER][COMMS_MODEL_SERVER]	= set_server_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_MAIN_ROTOR_SPIN_UP_TIMER][COMMS_MODEL_CLIENT]	= set_client_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_MAIN_ROTOR_SPIN_UP_TIMER]					  			= get_local_float_value;

	fn_get_local_entity_float_value				[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_RADAR_STEALTH_FACTOR]  						= get_local_float_value;

	fn_set_local_entity_raw_float_value			[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_TAIL_ROTOR_RPM]					 			= set_local_float_value;
	fn_set_local_entity_float_value				[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_TAIL_ROTOR_RPM]								= set_local_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_TAIL_ROTOR_RPM][COMMS_MODEL_SERVER]		= set_server_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_TAIL_ROTOR_RPM][COMMS_MODEL_CLIENT]		= set_client_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_TAIL_ROTOR_RPM]					  			= get_local_float_value;
	
	// Jabberwock 050310 MP Cannon bug
	fn_set_local_entity_raw_float_value			[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_PLAYER_WEAPON_HEADING]					 			= set_local_float_value;
	fn_set_local_entity_float_value				[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_PLAYER_WEAPON_HEADING]								= set_local_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_PLAYER_WEAPON_HEADING][COMMS_MODEL_SERVER]		= set_server_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_PLAYER_WEAPON_HEADING][COMMS_MODEL_CLIENT]		= set_client_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_PLAYER_WEAPON_HEADING]					  			= get_local_float_value;

	fn_set_local_entity_raw_float_value			[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_PLAYER_WEAPON_PITCH]					 			= set_local_float_value;
	fn_set_local_entity_float_value				[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_PLAYER_WEAPON_PITCH]								= set_local_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_PLAYER_WEAPON_PITCH][COMMS_MODEL_SERVER]		= set_server_float_value;
	fn_set_client_server_entity_float_value	[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_PLAYER_WEAPON_PITCH][COMMS_MODEL_CLIENT]		= set_client_float_value;
	fn_get_local_entity_float_value				[ENTITY_TYPE_HELICOPTER][FLOAT_TYPE_PLAYER_WEAPON_PITCH]					  			= get_local_float_value;
	// Jabberwock 050310 ends
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
