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

#define SET_LOCAL_REQUIRED				1
#define SET_CLIENT_SERVER_REQUIRED	1
#define GET_LOCAL_REQUIRED				1

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if SET_LOCAL_REQUIRED

static void set_local_float_value (entity *en, float_types type, float value)
{
	aircraft
		*raw = nullptr;

	#if DEBUG_MODULE

	debug_log_entity_args (ENTITY_DEBUG_LOCAL, ENTITY_DEBUG_FLOAT_VALUE, en, type, value);

	#endif

	raw = (aircraft *) get_local_entity_data (en);

	switch (type)
	{
		////////////////////////////////////////
		case FLOAT_TYPE_AIR_RADAR_CONTACT_TIMEOUT:
		////////////////////////////////////////
		{
			raw->air_radar_contact_timeout = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_CARGO_DOOR_STATE:
		////////////////////////////////////////
		{
			raw->cargo_door_state = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_DEATH_TIMER:
		////////////////////////////////////////
		{
			raw->death_timer = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_DISTANCE:
		////////////////////////////////////////
		{
			raw->distance = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_WEAPON_TO_INTERCEPT_POINT_RANGE:
		////////////////////////////////////////
		{
			raw->weapon_to_intercept_point_range = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_LOADING_DOOR_STATE:
		////////////////////////////////////////
		{
			raw->loading_door_state = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_RUDDER_STATE:
		////////////////////////////////////////
		{
			raw->rudder_state = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_UNDERCARRIAGE_STATE:
		////////////////////////////////////////
		{
			raw->undercarriage_state = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_VIEW_INTEREST_LEVEL:
		////////////////////////////////////////
		{
			raw->view_interest_level = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_WEAPON_BURST_TIMER:
		////////////////////////////////////////
		{
			raw->weapon_burst_timer = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_WEAPON_LAUNCH_DELAY:
		////////////////////////////////////////
		{
			raw->weapon_launch_delay = value;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_WEAPON_SYSTEM_READY_STATE:
		////////////////////////////////////////
		{
			raw->weapon_system_ready_state = value;

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal_invalid_float_type (en, type);

			break;
		}
	}
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if SET_CLIENT_SERVER_REQUIRED

static void set_remote_float_value (entity *en, float_types type, float value)
{
	#if DEBUG_MODULE

	debug_log_entity_args (ENTITY_DEBUG_REMOTE, ENTITY_DEBUG_FLOAT_VALUE, en, type, value);

	#endif

	transmit_entity_comms_message (ENTITY_COMMS_FLOAT_VALUE, en, type, value);
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if SET_CLIENT_SERVER_REQUIRED

static void set_server_float_value (entity *en, float_types type, float value)
{
	validate_client_server_local_fn ();

	set_local_float_value (en, type, value);

	validate_client_server_remote_fn ();

	set_remote_float_value (en, type, value);
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if SET_CLIENT_SERVER_REQUIRED

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

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if GET_LOCAL_REQUIRED

static float get_local_float_value (entity *en, float_types type)
{
	aircraft
		*raw = nullptr;

	float
		value;

	raw = (aircraft *) get_local_entity_data (en);

	switch (type)
	{
		////////////////////////////////////////
		case FLOAT_TYPE_AIR_RADAR_CONTACT_TIMEOUT:
		////////////////////////////////////////
		{
			value = raw->air_radar_contact_timeout;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_AIR_SCAN_RANGE:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].air_scan_range;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_AMMO_ECONOMY:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].ammo_economy;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_ATTACK_ALTITUDE:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].attack_altitude;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_AVOIDANCE_RADIUS:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].avoidance_radius;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_CARGO_DOOR_STATE:
		////////////////////////////////////////
		{
			value = raw->cargo_door_state;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE:
		////////////////////////////////////////
		{
			if (raw->mob.alive)
			{
				value = aircraft_database[raw->mob.sub_type].centre_of_gravity_to_ground_distance;
			}
			else
			{
				value = aircraft_database[raw->mob.sub_type].centre_of_gravity_to_ground_distance_destroyed;
			}

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_CHASE_VIEW_MAX_DISTANCE:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].chase_view_max_distance;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_CHASE_VIEW_MAX_DISTANCE_TEST:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].chase_view_max_distance_test;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_CHASE_VIEW_MIN_DISTANCE:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].chase_view_min_distance;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_CHASE_VIEW_MIN_DISTANCE_TEST:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].chase_view_min_distance_test;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_CRUISE_ALTITUDE:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].cruise_altitude;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_CRUISE_VELOCITY:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].cruise_velocity;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_DEATH_TIMER:
		////////////////////////////////////////
		{
			value = raw->death_timer;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_DISTANCE:
		////////////////////////////////////////
		{
			value = raw->distance;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_WEAPON_TO_INTERCEPT_POINT_RANGE:
		////////////////////////////////////////
		{
			value = raw->weapon_to_intercept_point_range;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_FUEL_DEFAULT_WEIGHT:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].fuel_default_weight;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_FUEL_ECONOMY:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].fuel_economy;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_FUSELAGE_ANGLE:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].fuselage_angle;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_LOADING_DOOR_STATE:
		////////////////////////////////////////
		{
			value = raw->loading_door_state;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_MAIN_ROTOR_DIRECTION:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].main_rotor_direction;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_MAIN_ROTOR_BLADE_DROOP_ANGLE:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].main_rotor_blade_droop_angle;

			break;
		}
		////////////////////////////////////////
		// Xhit: added FLOAT_TYPE_MAIN_ROTOR_RADIUS for downwash effect (030328)
		case FLOAT_TYPE_MAIN_ROTOR_RADIUS:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].main_rotor_radius;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_MAIN_ROTOR_SHAFT_ANGLE:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].main_rotor_shaft_angle;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_MAX_3D_OBJECT_VISUAL_RANGE:
		////////////////////////////////////////
		{
			value = object_3d_information_database[raw->object_3d_shape].maximum_distance;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_MAX_TURN_RATE:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].max_turn_rate;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_MAX_ROLL:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].max_roll;

			break;
		}
		// Xhit: added FLOAT_TYPE_NUMBER_OF_MAIN_ROTORS for downwash effect (030328)
		case FLOAT_TYPE_NUMBER_OF_MAIN_ROTORS:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].number_of_main_rotors;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_MAX_VERTICAL_TURN_ALLOWANCE:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].max_vertical_turn_allowance;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_POTENTIAL_AIR_THREAT:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].potential_air_to_air_threat;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_POTENTIAL_AIR_TO_AIR_THREAT:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].potential_air_to_air_threat;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_POTENTIAL_AIR_TO_SURFACE_THREAT:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].potential_air_to_surface_threat;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_POTENTIAL_SURFACE_THREAT:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].potential_air_to_surface_threat;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_PROPELLOR_DIRECTION:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].propellor_direction;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_RADAR_ALTITUDE:
		////////////////////////////////////////
		{
			value = max (raw->mob.position.y - get_3d_terrain_point_data_elevation (&raw->terrain_info), 0.0f);

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_RECON_RADIUS:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].recon_radius;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_RUDDER_STATE:
		////////////////////////////////////////
		{
			value = raw->rudder_state;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_SURFACE_SCAN_RANGE:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].surface_scan_range;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_TAIL_ROTOR_DIRECTION:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].tail_rotor_direction;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_TARGET_PRIORITY_AIR_ATTACK:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].potential_air_to_air_threat;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_TARGET_PRIORITY_GROUND_ATTACK:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].potential_air_to_surface_threat;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_TARGET_SCAN_DELAY:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].target_scan_delay;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_TARGET_SCAN_TIMER:
		////////////////////////////////////////
		{
			value = raw->target_scan_timer;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_TERRAIN_ELEVATION:
		////////////////////////////////////////
		{
			value = get_3d_terrain_point_data_elevation (&raw->terrain_info);

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_UNDERCARRIAGE_STATE:
		////////////////////////////////////////
		{
			value = raw->undercarriage_state;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_VIEW_INTEREST_LEVEL:
		////////////////////////////////////////
		{
			value = raw->view_interest_level;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_WEAPON_BURST_TIMER:
		////////////////////////////////////////
		{
			value = raw->weapon_burst_timer;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_WEAPON_LAUNCH_DELAY:
		////////////////////////////////////////
		{
			value = raw->weapon_launch_delay;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_WEAPON_SYSTEM_READY_STATE:
		////////////////////////////////////////
		{
			value = raw->weapon_system_ready_state;

			break;
		}
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

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_aircraft_float_value_functions (entity_types type)
{
	fn_set_local_entity_raw_float_value			[type][FLOAT_TYPE_AIR_RADAR_CONTACT_TIMEOUT]								= set_local_float_value;
	fn_set_local_entity_float_value				[type][FLOAT_TYPE_AIR_RADAR_CONTACT_TIMEOUT]								= set_local_float_value;
	fn_get_local_entity_float_value				[type][FLOAT_TYPE_AIR_RADAR_CONTACT_TIMEOUT]								= get_local_float_value;

	fn_get_local_entity_float_value				[type][FLOAT_TYPE_AIR_SCAN_RANGE] 											= get_local_float_value;

	fn_get_local_entity_float_value				[type][FLOAT_TYPE_AMMO_ECONOMY]												= get_local_float_value;

	fn_get_local_entity_float_value				[type][FLOAT_TYPE_ATTACK_ALTITUDE]											= get_local_float_value;

	fn_get_local_entity_float_value				[type][FLOAT_TYPE_AVOIDANCE_RADIUS]											= get_local_float_value;

	fn_set_local_entity_raw_float_value			[type][FLOAT_TYPE_CARGO_DOOR_STATE]											= set_local_float_value;
	fn_set_local_entity_float_value				[type][FLOAT_TYPE_CARGO_DOOR_STATE]											= set_local_float_value;
	fn_set_client_server_entity_float_value	[type][FLOAT_TYPE_CARGO_DOOR_STATE][COMMS_MODEL_SERVER]				= set_server_float_value;
	fn_set_client_server_entity_float_value	[type][FLOAT_TYPE_CARGO_DOOR_STATE][COMMS_MODEL_CLIENT]				= set_client_float_value;
	fn_get_local_entity_float_value				[type][FLOAT_TYPE_CARGO_DOOR_STATE]											= get_local_float_value;

	fn_get_local_entity_float_value				[type][FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE]				= get_local_float_value;

	fn_get_local_entity_float_value				[type][FLOAT_TYPE_CHASE_VIEW_MAX_DISTANCE]								= get_local_float_value;

	fn_get_local_entity_float_value				[type][FLOAT_TYPE_CHASE_VIEW_MAX_DISTANCE_TEST]							= get_local_float_value;

	fn_get_local_entity_float_value				[type][FLOAT_TYPE_CHASE_VIEW_MIN_DISTANCE]								= get_local_float_value;

	fn_get_local_entity_float_value				[type][FLOAT_TYPE_CHASE_VIEW_MIN_DISTANCE_TEST]							= get_local_float_value;

	fn_get_local_entity_float_value				[type][FLOAT_TYPE_CRUISE_ALTITUDE]											= get_local_float_value;

	fn_get_local_entity_float_value				[type][FLOAT_TYPE_CRUISE_VELOCITY]											= get_local_float_value;

	fn_set_local_entity_raw_float_value			[type][FLOAT_TYPE_DEATH_TIMER]												= set_local_float_value;
	fn_set_local_entity_float_value				[type][FLOAT_TYPE_DEATH_TIMER]												= set_local_float_value;
	fn_set_client_server_entity_float_value	[type][FLOAT_TYPE_DEATH_TIMER][COMMS_MODEL_SERVER]						= set_server_float_value;
	fn_set_client_server_entity_float_value	[type][FLOAT_TYPE_DEATH_TIMER][COMMS_MODEL_CLIENT]						= set_client_float_value;
	fn_get_local_entity_float_value				[type][FLOAT_TYPE_DEATH_TIMER]												= get_local_float_value;

	fn_set_local_entity_raw_float_value			[type][FLOAT_TYPE_DISTANCE]													= set_local_float_value;
	fn_set_local_entity_float_value				[type][FLOAT_TYPE_DISTANCE]													= set_local_float_value;
	fn_set_client_server_entity_float_value	[type][FLOAT_TYPE_DISTANCE][COMMS_MODEL_SERVER]							= set_server_float_value;
	fn_set_client_server_entity_float_value	[type][FLOAT_TYPE_DISTANCE][COMMS_MODEL_CLIENT]							= set_client_float_value;
	fn_get_local_entity_float_value				[type][FLOAT_TYPE_DISTANCE]													= get_local_float_value;

	fn_set_local_entity_raw_float_value			[type][FLOAT_TYPE_WEAPON_TO_INTERCEPT_POINT_RANGE]													= set_local_float_value;
	fn_set_local_entity_float_value				[type][FLOAT_TYPE_WEAPON_TO_INTERCEPT_POINT_RANGE]													= set_local_float_value;
	fn_set_client_server_entity_float_value	[type][FLOAT_TYPE_WEAPON_TO_INTERCEPT_POINT_RANGE][COMMS_MODEL_SERVER]							= set_server_float_value;
	fn_set_client_server_entity_float_value	[type][FLOAT_TYPE_WEAPON_TO_INTERCEPT_POINT_RANGE][COMMS_MODEL_CLIENT]							= set_client_float_value;
	fn_get_local_entity_float_value				[type][FLOAT_TYPE_WEAPON_TO_INTERCEPT_POINT_RANGE]													= get_local_float_value;

	fn_get_local_entity_float_value				[type][FLOAT_TYPE_FUEL_DEFAULT_WEIGHT]										= get_local_float_value;

	fn_get_local_entity_float_value				[type][FLOAT_TYPE_FUEL_ECONOMY]												= get_local_float_value;

	fn_get_local_entity_float_value				[type][FLOAT_TYPE_FUSELAGE_ANGLE]											= get_local_float_value;

	fn_set_local_entity_raw_float_value			[type][FLOAT_TYPE_LOADING_DOOR_STATE]										= set_local_float_value;
	fn_set_local_entity_float_value				[type][FLOAT_TYPE_LOADING_DOOR_STATE]										= set_local_float_value;
	fn_set_client_server_entity_float_value	[type][FLOAT_TYPE_LOADING_DOOR_STATE][COMMS_MODEL_SERVER]			= set_server_float_value;
	fn_set_client_server_entity_float_value	[type][FLOAT_TYPE_LOADING_DOOR_STATE][COMMS_MODEL_CLIENT]			= set_client_float_value;
	fn_get_local_entity_float_value				[type][FLOAT_TYPE_LOADING_DOOR_STATE]										= get_local_float_value;

	fn_get_local_entity_float_value				[type][FLOAT_TYPE_MAIN_ROTOR_DIRECTION]									= get_local_float_value;

	fn_get_local_entity_float_value				[type][FLOAT_TYPE_MAIN_ROTOR_BLADE_DROOP_ANGLE]							= get_local_float_value;

	// Xhit added following function for downwash effect 030328
	fn_get_local_entity_float_value				[type][FLOAT_TYPE_MAIN_ROTOR_RADIUS]									= get_local_float_value;

	fn_get_local_entity_float_value				[type][FLOAT_TYPE_MAIN_ROTOR_SHAFT_ANGLE]									= get_local_float_value;

	fn_get_local_entity_float_value				[type][FLOAT_TYPE_MAX_3D_OBJECT_VISUAL_RANGE]							= get_local_float_value;

	fn_get_local_entity_float_value				[type][FLOAT_TYPE_MAX_TURN_RATE]												= get_local_float_value;

	fn_get_local_entity_float_value				[type][FLOAT_TYPE_MAX_ROLL]													= get_local_float_value;

	fn_get_local_entity_float_value				[type][FLOAT_TYPE_MAX_VERTICAL_TURN_ALLOWANCE]							= get_local_float_value;

	// Xhit added following function for downwash effect 030328
	fn_get_local_entity_float_value				[type][FLOAT_TYPE_NUMBER_OF_MAIN_ROTORS]									= get_local_float_value;

	fn_get_local_entity_float_value				[type][FLOAT_TYPE_POTENTIAL_AIR_THREAT]									= get_local_float_value;

	fn_get_local_entity_float_value				[type][FLOAT_TYPE_POTENTIAL_AIR_TO_AIR_THREAT]							= get_local_float_value;

	fn_get_local_entity_float_value				[type][FLOAT_TYPE_POTENTIAL_AIR_TO_SURFACE_THREAT]	  					= get_local_float_value;

	fn_get_local_entity_float_value				[type][FLOAT_TYPE_POTENTIAL_SURFACE_THREAT]	  							= get_local_float_value;

	fn_get_local_entity_float_value				[type][FLOAT_TYPE_PROPELLOR_DIRECTION]										= get_local_float_value;

	fn_get_local_entity_float_value				[type][FLOAT_TYPE_RADAR_ALTITUDE]											= get_local_float_value;

	fn_get_local_entity_float_value				[type][FLOAT_TYPE_RECON_RADIUS]												= get_local_float_value;

	fn_set_local_entity_raw_float_value  		[type][FLOAT_TYPE_RUDDER_STATE]												= set_local_float_value;
	fn_set_local_entity_float_value				[type][FLOAT_TYPE_RUDDER_STATE]												= set_local_float_value;
	fn_set_client_server_entity_float_value	[type][FLOAT_TYPE_RUDDER_STATE][COMMS_MODEL_SERVER]					= set_server_float_value;
	fn_set_client_server_entity_float_value	[type][FLOAT_TYPE_RUDDER_STATE][COMMS_MODEL_CLIENT]					= set_client_float_value;
	fn_get_local_entity_float_value				[type][FLOAT_TYPE_RUDDER_STATE]												= get_local_float_value;

	fn_get_local_entity_float_value				[type][FLOAT_TYPE_SURFACE_SCAN_RANGE]		 								= get_local_float_value;

	fn_get_local_entity_float_value				[type][FLOAT_TYPE_TAIL_ROTOR_DIRECTION]									= get_local_float_value;

	fn_get_local_entity_float_value				[type][FLOAT_TYPE_TARGET_PRIORITY_AIR_ATTACK]	  						= get_local_float_value;

	fn_get_local_entity_float_value				[type][FLOAT_TYPE_TARGET_PRIORITY_GROUND_ATTACK]						= get_local_float_value;

	fn_get_local_entity_float_value				[type][FLOAT_TYPE_TARGET_SCAN_DELAY]	 		  	  						= get_local_float_value;

	fn_get_local_entity_float_value				[type][FLOAT_TYPE_TARGET_SCAN_TIMER]	 		  	  						= get_local_float_value;

	fn_get_local_entity_float_value				[type][FLOAT_TYPE_TERRAIN_ELEVATION]	 		  	  						= get_local_float_value;

	fn_set_local_entity_raw_float_value  		[type][FLOAT_TYPE_UNDERCARRIAGE_STATE]										= set_local_float_value;
	fn_set_local_entity_float_value				[type][FLOAT_TYPE_UNDERCARRIAGE_STATE]										= set_local_float_value;
	fn_set_client_server_entity_float_value	[type][FLOAT_TYPE_UNDERCARRIAGE_STATE][COMMS_MODEL_SERVER]			= set_server_float_value;
	fn_set_client_server_entity_float_value	[type][FLOAT_TYPE_UNDERCARRIAGE_STATE][COMMS_MODEL_CLIENT]			= set_client_float_value;
	fn_get_local_entity_float_value				[type][FLOAT_TYPE_UNDERCARRIAGE_STATE]										= get_local_float_value;

	fn_set_local_entity_raw_float_value			[type][FLOAT_TYPE_VIEW_INTEREST_LEVEL]										= set_local_float_value;
	fn_set_local_entity_float_value				[type][FLOAT_TYPE_VIEW_INTEREST_LEVEL]										= set_local_float_value;
	fn_get_local_entity_float_value				[type][FLOAT_TYPE_VIEW_INTEREST_LEVEL]										= get_local_float_value;

	fn_set_local_entity_raw_float_value			[type][FLOAT_TYPE_WEAPON_BURST_TIMER]										= set_local_float_value;
	fn_set_local_entity_float_value				[type][FLOAT_TYPE_WEAPON_BURST_TIMER]										= set_local_float_value;
	fn_get_local_entity_float_value				[type][FLOAT_TYPE_WEAPON_BURST_TIMER]										= get_local_float_value;

	fn_set_local_entity_raw_float_value  		[type][FLOAT_TYPE_WEAPON_LAUNCH_DELAY]												= set_local_float_value;
	fn_set_local_entity_float_value				[type][FLOAT_TYPE_WEAPON_LAUNCH_DELAY]												= set_local_float_value;
	fn_set_client_server_entity_float_value	[type][FLOAT_TYPE_WEAPON_LAUNCH_DELAY][COMMS_MODEL_SERVER]					= set_server_float_value;
	fn_set_client_server_entity_float_value	[type][FLOAT_TYPE_WEAPON_LAUNCH_DELAY][COMMS_MODEL_CLIENT]					= set_client_float_value;
	fn_get_local_entity_float_value				[type][FLOAT_TYPE_WEAPON_LAUNCH_DELAY]												= get_local_float_value;

	fn_set_local_entity_raw_float_value			[type][FLOAT_TYPE_WEAPON_SYSTEM_READY_STATE]								= set_local_float_value;
	fn_set_local_entity_float_value				[type][FLOAT_TYPE_WEAPON_SYSTEM_READY_STATE]								= set_local_float_value;
	fn_set_client_server_entity_float_value	[type][FLOAT_TYPE_WEAPON_SYSTEM_READY_STATE][COMMS_MODEL_SERVER]	= set_server_float_value;
	fn_set_client_server_entity_float_value	[type][FLOAT_TYPE_WEAPON_SYSTEM_READY_STATE][COMMS_MODEL_CLIENT]	= set_client_float_value;
	fn_get_local_entity_float_value				[type][FLOAT_TYPE_WEAPON_SYSTEM_READY_STATE]								= get_local_float_value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
