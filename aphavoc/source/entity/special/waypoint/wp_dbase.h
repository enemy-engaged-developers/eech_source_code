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

struct WAYPOINT_DATA
{
	////////////////////////////////////////
	//
	// names
	//
	////////////////////////////////////////

	const char
		*full_name;

	int
		verbose_operational_state	: NUM_VERBOSE_OPERATIONAL_STATE_BITS;

	unsigned int
		mobile_follow_waypoint_offset		: 1,
		waypoint_action_message				: 9,
		waypoint_reached_message			: 9,
		waypoint_reached_return_value		: 4,
		planner_moveable						: 1,
		objective_waypoint					: 1,
		player_skip_waypoint					: 1,
		check_waypoint_action				: 1;

	entity_sub_types
		guide_sub_type;

	int
		map_icon;

	// FIXED WING

	float
		fw_minimum_previous_waypoint_distance,
		fw_action_radius,
		fw_reached_radius,
		fw_velocity;

	unsigned int
		fw_criteria_last_to_reach	: 1,
		fw_criteria_transmit_recon	: 1,
		fw_position_type				: NUM_POSITION_TYPE_BITS,
		fw_movement_type				: NUM_MOVEMENT_TYPE_BITS;

	// HELICOPTER

	float
		hc_minimum_previous_waypoint_distance,
		hc_action_radius,
		hc_reached_radius,
		hc_velocity;

	unsigned int
		hc_criteria_last_to_reach	: 1,
		hc_criteria_transmit_recon	: 1,
		hc_position_type				: NUM_POSITION_TYPE_BITS,
		hc_movement_type				: NUM_MOVEMENT_TYPE_BITS;

	// GROUND

	float
		rv_minimum_previous_waypoint_distance,
		rv_action_radius,
		rv_reached_radius,
		rv_velocity;

	unsigned int
		rv_criteria_last_to_reach	: 1,
		rv_criteria_transmit_recon	: 1,
		rv_position_type				: NUM_POSITION_TYPE_BITS,
		rv_movement_type				: NUM_MOVEMENT_TYPE_BITS;

	// SEA

	float
		sh_minimum_previous_waypoint_distance,
		sh_action_radius,
		sh_reached_radius,
		sh_velocity;

	unsigned int
		sh_criteria_last_to_reach	: 1,
		sh_criteria_transmit_recon	: 1,
		sh_position_type				: NUM_POSITION_TYPE_BITS,
		sh_movement_type				: NUM_MOVEMENT_TYPE_BITS;
};

typedef struct WAYPOINT_DATA waypoint_data;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ WUT mod bug, date: 26-mar-03
//remove "const" from definition
extern waypoint_data
	waypoint_database[NUM_ENTITY_SUB_TYPE_WAYPOINTS];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern float get_waypoint_database_action_radius_value (entity_sub_types waypoint_type, entity_types mobile_type);

extern float get_local_entity_waypoint_database_action_radius_value (entity *waypoint, entity *mobile);

extern float get_waypoint_database_reached_radius_value (entity_sub_types waypoint_type, entity_types mobile_type);

extern float get_local_entity_waypoint_database_reached_radius_value (entity *waypoint, entity *mobile);

extern float get_waypoint_database_velocity_value (entity_sub_types waypoint_type, entity_types mobile_type);

extern int get_waypoint_database_transmit_recon_flag (entity_sub_types waypoint_type, entity_types mobile_type);

extern int get_waypoint_database_last_to_reach_flag (entity_sub_types waypoint_type, entity_types mobile_type);

//extern int get_waypoint_database_waypoint_criteria_value (entity_sub_types waypoint_type, entity_types mobile_type);

extern int get_waypoint_database_position_type_value (entity_sub_types waypoint_type, entity_types mobile_type);

extern int get_waypoint_database_movement_type_value (entity_sub_types waypoint_type, entity_types mobile_type);

extern float get_waypoint_database_minimum_previous_waypoint_distance (entity_sub_types waypoint_type, entity_types mobile_type);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
