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

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_local_int_value (entity *en, int_types type, int value)
{
	group
		*raw;

	#if DEBUG_MODULE

	debug_log_entity_args (ENTITY_DEBUG_LOCAL, ENTITY_DEBUG_INT_VALUE, en, type, value);

	#endif

	raw = (group *) get_local_entity_data (en);

	switch (type)
	{
		////////////////////////////////////////
		case INT_TYPE_ALIVE:
		////////////////////////////////////////
		{
			raw->alive = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_ENGAGE_ENEMY:
		////////////////////////////////////////
		{
			raw->engage_enemy = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_ENTITY_SUB_TYPE:
		////////////////////////////////////////
		{
			raw->sub_type = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_GROUP_CALLSIGN:
		////////////////////////////////////////
		{
			raw->group_callsign = value;

			break;
		}		
		////////////////////////////////////////
		case INT_TYPE_GROUP_FORMATION:
		////////////////////////////////////////
		{
			ASSERT ((value >= FORMATION_NONE) && (value < FORMATION_INVALID));

			raw->group_formation = value;

			break;
		}		
		////////////////////////////////////////
		case INT_TYPE_GROUP_LIST_TYPE:
		////////////////////////////////////////
		{
			raw->group_list_type = (list_types) value;

			break;
		}		
		////////////////////////////////////////
		case INT_TYPE_KILLS:
		////////////////////////////////////////
		{
			raw->kills = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_LOSSES:
		////////////////////////////////////////
		{
			raw->losses = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_MEMBER_COUNT:
		////////////////////////////////////////
		{
			raw->member_count = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_MULTIPLAYER_GROUP:
		////////////////////////////////////////
		{
			raw->multiplayer_group = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_MINIMUM_IDLE_COUNT:
		////////////////////////////////////////
		{
			value = group_database[raw->sub_type].minimum_idle_count;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_ROUTE_NODE:
		////////////////////////////////////////
		{
			raw->route_node = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_SIDE:
		////////////////////////////////////////
		{
			// Casm 18AUG05 begin We need to place this group to another force if side is changed
			if ( raw->side != ENTITY_SIDE_UNINITIALISED && value != ENTITY_SIDE_UNINITIALISED && raw->side != value )
			{
				entity
					*old_force,
					*new_force;
				list_types
					list_type;

				list_type = (list_types) get_local_entity_int_value (en, INT_TYPE_REGISTRY_LIST_TYPE);
				if (list_type != LIST_TYPE_INVALID)
				{
					old_force = get_local_force_entity ((entity_sides) raw->side);
					new_force = get_local_force_entity ((entity_sides) value);

					delete_local_entity_from_parents_child_list (en, list_type);
					remove_group_type_from_force_info (old_force, raw->sub_type);
					insert_local_entity_into_parents_child_list (en, list_type, new_force, NULL);
					add_group_type_to_force_info (new_force, raw->sub_type);
				}
			}
			// Casm 18AUG05 end

			raw->side = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_UNIQUE_ID:
		////////////////////////////////////////
		{
			raw->unique_id = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_VERBOSE_OPERATIONAL_STATE:
		////////////////////////////////////////
		{
			raw->verbose_operational_state = value;

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal_invalid_int_type (en, type);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_remote_int_value (entity *en, int_types type, int value)
{
	#if DEBUG_MODULE

	debug_log_entity_args (ENTITY_DEBUG_REMOTE, ENTITY_DEBUG_INT_VALUE, en, type, value);

	#endif

	transmit_entity_comms_message (ENTITY_COMMS_INT_VALUE, en, type, value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_server_int_value (entity *en, int_types type, int value)
{
	validate_client_server_local_fn ();

	set_local_int_value (en, type, value);

	validate_client_server_remote_fn ();

	set_remote_int_value (en, type, value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_client_int_value (entity *en, int_types type, int value)
{
	if (get_comms_data_flow () == COMMS_DATA_FLOW_TX)
	{
		validate_client_server_remote_fn ();

		set_remote_int_value (en, type, value);
	}
	else
	{
		validate_client_server_local_fn ();

		set_local_int_value (en, type, value);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_local_int_value (entity *en, int_types type)
{
	group
		*raw;

	int
		value;

	raw = (group *) get_local_entity_data (en);

	switch (type)
	{
		////////////////////////////////////////
		case INT_TYPE_AIR_ATTACK_STRENGTH:
		////////////////////////////////////////
		{
			value = group_database [raw->sub_type].ai_stats.air_attack_strength;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_AIRCRAFT_GROUP:
		////////////////////////////////////////
		{
			value = (group_database [raw->sub_type].movement_type == MOVEMENT_TYPE_AIR);

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_ALIVE:
		////////////////////////////////////////
		{
			value = raw->alive;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_DEFAULT_ENGAGE_ENEMY:
		////////////////////////////////////////
		{
			value = group_database [raw->sub_type].default_engage_enemy;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_DEFAULT_GROUP_LIST_TYPE:
		////////////////////////////////////////
		{
			value = group_database [raw->sub_type].group_list_type;

			break;
		}		
		////////////////////////////////////////
		case INT_TYPE_DIVISION_ID:
		////////////////////////////////////////
		{
			// deliberate use of another variable...
			value = raw->group_callsign;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_ENGAGE_ENEMY:
		////////////////////////////////////////
		{
			if (group_database [raw->sub_type].movement_type == MOVEMENT_TYPE_AIR)
			{
				value = raw->engage_enemy;
			}
			else
			{
				value = group_database [raw->sub_type].default_engage_enemy;
			}

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_ENTITY_SUB_TYPE:
		////////////////////////////////////////
		{
			value = raw->sub_type;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_FRONTLINE:
		////////////////////////////////////////
		{
			value = group_database [raw->sub_type].frontline_flag;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_GROUP_AMALGAMATE:
		////////////////////////////////////////
		{
			value = group_database [raw->sub_type].amalgamate;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_GROUP_CALLSIGN:
		////////////////////////////////////////
		{
			value = raw->group_callsign;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_GROUP_CATEGORY:
		////////////////////////////////////////
		{
			value = group_database [raw->sub_type].group_category;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_GROUP_DEFAULT_FORMATION:
		////////////////////////////////////////
		{
			value = group_database [raw->sub_type].default_group_formation;

			break;
		}		
		////////////////////////////////////////
		case INT_TYPE_GROUP_FORMATION:
		////////////////////////////////////////
		{
			value = raw->group_formation;

			break;
		}		
		////////////////////////////////////////
		case INT_TYPE_GROUP_LIST_TYPE:
		////////////////////////////////////////
		{
			value = raw->group_list_type;

			break;
		}		
		////////////////////////////////////////
		case INT_TYPE_GROUP_MODE:
		////////////////////////////////////////
		{
			if (get_local_entity_first_child (en, LIST_TYPE_GUIDE_STACK))
			{
				value = GROUP_MODE_BUSY;
			}
			else
			{
				value = GROUP_MODE_IDLE;
			}

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_HIDDEN_BY_FOG_OF_WAR:
		////////////////////////////////////////
		{
			value = TRUE;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_KILLS:
		////////////////////////////////////////
		{
			value = raw->kills;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_LOCAL_ONLY_GROUP:
		////////////////////////////////////////
		{
			value = group_database [raw->sub_type].local_only_group;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_LOSSES:
		////////////////////////////////////////
		{
			value = raw->losses;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_MAP_ICON:
		////////////////////////////////////////
		{
			value = group_database [raw->sub_type].map_icon;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_MAXIMUM_MEMBER_COUNT:
		////////////////////////////////////////
		{
			value = group_database [raw->sub_type].maximum_member_count;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_MEMBER_COUNT:
		////////////////////////////////////////
		{
			value = raw->member_count;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_MOVEMENT_TYPE:
		////////////////////////////////////////
		{
			value = group_database [raw->sub_type].movement_type;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_MULTIPLAYER_GROUP:
		////////////////////////////////////////
		{
			value = raw->multiplayer_group;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_REGISTRY_LIST_TYPE:
		////////////////////////////////////////
		{
			value = group_database [raw->sub_type].registry_list_type;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_RESUPPLY_SOURCE:
		////////////////////////////////////////
		{
			value = group_database [raw->sub_type].resupply_source;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_ROUTE_NODE:
		////////////////////////////////////////
		{
			value = raw->route_node;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_SIDE:
		////////////////////////////////////////
		{
			value = raw->side;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_UNIQUE_ID:
		////////////////////////////////////////
		{
			value = raw->unique_id;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_VEHICLE_GROUP:
		////////////////////////////////////////
		{
			value = ((group_database [raw->sub_type].movement_type == MOVEMENT_TYPE_SEA) ||
						(group_database [raw->sub_type].movement_type == MOVEMENT_TYPE_GROUND));

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_VERBOSE_OPERATIONAL_STATE:
		////////////////////////////////////////
		{
			value = raw->verbose_operational_state;

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal_invalid_int_type (en, type);

			break;
		}
	}

	return (value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_group_int_value_functions (void)
{
	fn_get_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_AIR_ATTACK_STRENGTH]			= get_local_int_value;

	fn_get_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_AIRCRAFT_GROUP]					= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_GROUP][INT_TYPE_ALIVE]								= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_ALIVE]								= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_GROUP][INT_TYPE_ALIVE][COMMS_MODEL_SERVER]	= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_GROUP][INT_TYPE_ALIVE][COMMS_MODEL_CLIENT]	= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_ALIVE]								= get_local_int_value;

	fn_get_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_DEFAULT_ENGAGE_ENEMY]						= get_local_int_value;

	fn_get_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_DEFAULT_GROUP_LIST_TYPE]					= get_local_int_value;

	fn_get_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_DIVISION_ID]									= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_GROUP][INT_TYPE_ENGAGE_ENEMY]								= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_ENGAGE_ENEMY]								= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_GROUP][INT_TYPE_ENGAGE_ENEMY][COMMS_MODEL_SERVER]		= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_GROUP][INT_TYPE_ENGAGE_ENEMY][COMMS_MODEL_CLIENT]		= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_ENGAGE_ENEMY]								= get_local_int_value;
	
	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_GROUP][INT_TYPE_ENTITY_SUB_TYPE]							= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_ENTITY_SUB_TYPE]							= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_GROUP][INT_TYPE_ENTITY_SUB_TYPE][COMMS_MODEL_SERVER]	= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_GROUP][INT_TYPE_ENTITY_SUB_TYPE][COMMS_MODEL_CLIENT]	= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_ENTITY_SUB_TYPE]							= get_local_int_value;

	fn_get_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_FRONTLINE]									= get_local_int_value;

	fn_get_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_GROUP_AMALGAMATE]								= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_GROUP][INT_TYPE_GROUP_CALLSIGN]									= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_GROUP_CALLSIGN]									= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_GROUP][INT_TYPE_GROUP_CALLSIGN][COMMS_MODEL_SERVER]		= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_GROUP][INT_TYPE_GROUP_CALLSIGN][COMMS_MODEL_CLIENT]		= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_GROUP_CALLSIGN]									= get_local_int_value;

	fn_get_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_GROUP_CATEGORY]									= get_local_int_value;

	fn_get_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_GROUP_DEFAULT_FORMATION]						= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_GROUP][INT_TYPE_GROUP_FORMATION]								= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_GROUP_FORMATION]								= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_GROUP][INT_TYPE_GROUP_FORMATION][COMMS_MODEL_SERVER]		= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_GROUP][INT_TYPE_GROUP_FORMATION][COMMS_MODEL_CLIENT]		= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_GROUP_FORMATION]								= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_GROUP][INT_TYPE_GROUP_LIST_TYPE]								= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_GROUP_LIST_TYPE]								= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_GROUP][INT_TYPE_GROUP_LIST_TYPE][COMMS_MODEL_SERVER]		= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_GROUP][INT_TYPE_GROUP_LIST_TYPE][COMMS_MODEL_CLIENT]		= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_GROUP_LIST_TYPE]								= get_local_int_value;

	fn_get_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_GROUP_MODE]									= get_local_int_value;

	fn_get_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_HIDDEN_BY_FOG_OF_WAR]						= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_GROUP][INT_TYPE_KILLS]									= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_KILLS]									= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_GROUP][INT_TYPE_KILLS][COMMS_MODEL_SERVER]		= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_GROUP][INT_TYPE_KILLS][COMMS_MODEL_CLIENT]		= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_KILLS]									= get_local_int_value;

	fn_get_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_LOCAL_ONLY_GROUP]							= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_GROUP][INT_TYPE_LOSSES]								= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_LOSSES]								= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_GROUP][INT_TYPE_LOSSES][COMMS_MODEL_SERVER]		= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_GROUP][INT_TYPE_LOSSES][COMMS_MODEL_CLIENT]		= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_LOSSES]								= get_local_int_value;

	fn_get_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_MAP_ICON]								= get_local_int_value;

	fn_get_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_MAXIMUM_MEMBER_COUNT]				= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_GROUP][INT_TYPE_MEMBER_COUNT]								= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_MEMBER_COUNT]								= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_GROUP][INT_TYPE_MEMBER_COUNT][COMMS_MODEL_SERVER]		= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_GROUP][INT_TYPE_MEMBER_COUNT][COMMS_MODEL_CLIENT]		= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_MEMBER_COUNT]								= get_local_int_value;

	fn_get_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_MOVEMENT_TYPE]								= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_GROUP][INT_TYPE_MULTIPLAYER_GROUP]								= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_MULTIPLAYER_GROUP]								= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_GROUP][INT_TYPE_MULTIPLAYER_GROUP][COMMS_MODEL_SERVER]	= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_GROUP][INT_TYPE_MULTIPLAYER_GROUP][COMMS_MODEL_CLIENT]	= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_MULTIPLAYER_GROUP]								= get_local_int_value;

	fn_get_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_MINIMUM_IDLE_COUNT]	 						= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_GROUP][INT_TYPE_ROUTE_NODE]									= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_ROUTE_NODE]									= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_GROUP][INT_TYPE_ROUTE_NODE][COMMS_MODEL_SERVER]		= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_GROUP][INT_TYPE_ROUTE_NODE][COMMS_MODEL_CLIENT]		= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_ROUTE_NODE]									= get_local_int_value;

	fn_get_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_REGISTRY_LIST_TYPE]						= get_local_int_value;

	fn_get_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_RESUPPLY_SOURCE]							= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_GROUP][INT_TYPE_SIDE]											= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_SIDE]											= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_GROUP][INT_TYPE_SIDE][COMMS_MODEL_SERVER]				= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_GROUP][INT_TYPE_SIDE][COMMS_MODEL_CLIENT]				= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_SIDE]											= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_GROUP][INT_TYPE_UNIQUE_ID]									= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_UNIQUE_ID]									= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_GROUP][INT_TYPE_UNIQUE_ID][COMMS_MODEL_SERVER]			= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_GROUP][INT_TYPE_UNIQUE_ID][COMMS_MODEL_CLIENT]			= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_UNIQUE_ID]									= get_local_int_value;

	fn_get_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_VEHICLE_GROUP]								= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_GROUP][INT_TYPE_VERBOSE_OPERATIONAL_STATE]											= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_VERBOSE_OPERATIONAL_STATE]											= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_GROUP][INT_TYPE_VERBOSE_OPERATIONAL_STATE][COMMS_MODEL_SERVER]				= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_GROUP][INT_TYPE_VERBOSE_OPERATIONAL_STATE][COMMS_MODEL_CLIENT]				= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_GROUP][INT_TYPE_VERBOSE_OPERATIONAL_STATE]											= get_local_int_value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
