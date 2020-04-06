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

static void set_local_raw_int_value (entity *en, int_types type, int value)
{
	aircraft
		*raw = nullptr;

	#if DEBUG_MODULE

	debug_log_entity_args (ENTITY_DEBUG_LOCAL, ENTITY_DEBUG_INT_VALUE, en, type, value);

	#endif

	raw = (aircraft *) get_local_entity_data (en);

	switch (type)
	{
		////////////////////////////////////////
		case INT_TYPE_SELECTED_WEAPON:
		////////////////////////////////////////
		{
			raw->selected_weapon = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_WEAPON_CONFIG_TYPE:
		////////////////////////////////////////
		{
			raw->weapon_config_type = (weapon_config_types) value;

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

static void set_local_int_value (entity *en, int_types type, int value)
{
	aircraft
		*raw = nullptr;

	#if DEBUG_MODULE

	debug_log_entity_args (ENTITY_DEBUG_LOCAL, ENTITY_DEBUG_INT_VALUE, en, type, value);

	#endif

	raw = (aircraft *) get_local_entity_data (en);

	switch (type)
	{
		////////////////////////////////////////
		case INT_TYPE_CPG_IDENTIFIED:
		////////////////////////////////////////
		{
			raw->cpg_identified = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_DAMAGE_LEVEL:
		////////////////////////////////////////
		{
			float old_damage = raw->damage_level;

			raw->damage_level = value;

			assess_aircraft_damage_level (en, old_damage, value);

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_EJECTED:
		////////////////////////////////////////
		{
			raw->ejected = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_TROOPS_ONBOARD:
		////////////////////////////////////////
		{
			raw->troops_onboard = value;

			ASSERT (raw->inst3d);

			set_sub_object_type_visible_status(raw->inst3d, OBJECT_3D_SUB_OBJECT_TROOPS_ONBOARD, !!value);

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_FORMATION_POSITION:
		////////////////////////////////////////
		{
			raw->formation_position = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_GROUP_MEMBER_NUMBER:
		////////////////////////////////////////
		{
			ASSERT (value >= 0);

			ASSERT (value < (1 << NUM_GROUP_MEMBER_NUMBER_BITS));

			raw->group_member_number = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_GUNSHIP_RADAR_LOS_CLEAR:
		////////////////////////////////////////
		{
			raw->gunship_radar_los_clear = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_ID_NUMBER:
		////////////////////////////////////////
		{
			raw->id_number = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_ID_NUMBER_SIGNIFICANT_DIGITS:
		////////////////////////////////////////
		{
			raw->id_number_significant_digits = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_LIGHTS_ON:
		////////////////////////////////////////
		{
			raw->lights_on = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_OBJECT_3D_SHAPE:
		////////////////////////////////////////
		{
			raw->object_3d_shape = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_OPERATIONAL_STATE:
		////////////////////////////////////////
		{

			raw->operational_state = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_SELECTED_WEAPON:
		////////////////////////////////////////
		{
			//
			// stop continuous sound effect
			//

//			if (raw->selected_weapon != value)
			{
				pause_local_continuous_weapon_sound_effect (en, raw->selected_weapon);
			}

			//
			// play weapon selected speech
			//

			if (get_comms_model () == COMMS_MODEL_SERVER)
			{
				play_entity_weapon_selected_speech (en, value);
			}

			raw->selected_weapon = value;

			raw->weapon_burst_timer = 0.0;
			raw->weapon_salvo_timer = 0.0;

			//
			// special case for player's gunship
			//

			if (en == get_gunship_entity ())
			{
				rocket_salvo_count = 0;

				if (value == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
				{
					hud_mode = previous_hud_mode;
				}
				else
				{
					if (hud_mode != HUD_MODE_WEAPON)
						previous_hud_mode = hud_mode;
					hud_mode = HUD_MODE_WEAPON;
				}
			}

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_SELECTED_WEAPON_SYSTEM_READY:
		////////////////////////////////////////
		{
			raw->selected_weapon_system_ready = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_WEAPON_AND_TARGET_VECTORS_VALID:
		////////////////////////////////////////
		{
			raw->weapon_and_target_vectors_valid = value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_WEAPON_CONFIG_TYPE:
		////////////////////////////////////////
		{
			raw->weapon_config_type = (weapon_config_types) value;

			load_local_entity_weapon_config (en);

			if ((get_comms_model () == COMMS_MODEL_CLIENT) && (en == get_gunship_entity ()) && get_local_entity_int_value (en, INT_TYPE_GUNSHIP_TYPE) < NUM_GUNSHIP_TYPES)
			{
				//
				// needed because of the clients lag between selecting a new config, and it actually being changed
				//

				weapon_loading_update_currently_selected_weapons (en);
			}

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
	aircraft
		*raw = nullptr;

	int
		value;

	raw = (aircraft *) get_local_entity_data (en);

	switch (type)
	{
		////////////////////////////////////////
		case INT_TYPE_AIR_TO_AIR_WEAPON_CONFIG_TYPE:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].air_to_air_weapon_config_type;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_AIR_TO_SURFACE_WEAPON_CONFIG_TYPE:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].air_to_surface_weapon_config_type;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_AIRBORNE_AIRCRAFT:
		////////////////////////////////////////
		{

			switch (raw->operational_state)
			{

				case OPERATIONAL_STATE_ASLEEP:
				case OPERATIONAL_STATE_DEAD:
				case OPERATIONAL_STATE_LANDED:
				//case OPERATIONAL_STATE_REPAIRING:
				//case OPERATIONAL_STATE_REFUELING:
				//case OPERATIONAL_STATE_REARMING:
				case OPERATIONAL_STATE_STOPPED:
				case OPERATIONAL_STATE_TAXIING:
				case OPERATIONAL_STATE_UNKNOWN:
				case OPERATIONAL_STATE_WAITING:
				{

					value = FALSE;

					break;
				}

				case OPERATIONAL_STATE_DYING:
				case OPERATIONAL_STATE_LANDING:
				case OPERATIONAL_STATE_LANDING_HOLDING:
				case OPERATIONAL_STATE_NAVIGATING:
				case OPERATIONAL_STATE_TAKEOFF:
				case OPERATIONAL_STATE_TAKEOFF_HOLDING:
				{

					value = TRUE;

					break;
				}

				default:
				{

					debug_fatal ("AC_INT: unknown operational state");
				}
			}

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_COLLISION_TEST_MOBILE:
		////////////////////////////////////////
		{
			value = TRUE;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_CPG_IDENTIFIED:
		////////////////////////////////////////
		{
			value = raw->cpg_identified;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_DAMAGE_LEVEL:
		////////////////////////////////////////
		{
			value = raw->damage_level;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_DEFAULT_3D_SHAPE:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].default_3d_shape;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_DEFAULT_WEAPON_CONFIG_TYPE:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].default_weapon_config_type;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_DEFAULT_WEAPON_TYPE:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].default_weapon_type;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_DESTROYED_3D_SHAPE:
		////////////////////////////////////////
		{
			value = get_3d_object_destroyed_object_index (raw->object_3d_shape);

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_EJECTED:
		////////////////////////////////////////
		{
			value = raw->ejected;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_TROOPS_ONBOARD:
		////////////////////////////////////////
		{
			value = raw->troops_onboard;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_ENGAGE_ENEMY:
		////////////////////////////////////////
		{
			entity
				*group = nullptr;

			value = FALSE;

			switch (raw->operational_state)
			{
				case OPERATIONAL_STATE_NAVIGATING:
				{
					group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

					if (group)
					{
						value = get_local_entity_int_value (group, INT_TYPE_ENGAGE_ENEMY);
					}

					break;
				}
			}

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_EXPLOSIVE_POWER:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].explosive_power;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_EXPLOSIVE_QUALITY:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].explosive_quality;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_FORCE:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].force;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_FORCE_INFO_CATAGORY:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].force_info_catagory;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_FORMATION_POSITION:
		////////////////////////////////////////
		{
			value = raw->formation_position;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_GROUP_LEADER:
		////////////////////////////////////////
		{
			if ((get_local_entity_parent (en, LIST_TYPE_MEMBER)) && (get_local_entity_child_pred (en, LIST_TYPE_MEMBER) == NULL))
			{
				value = TRUE;
			}
			else
			{
				value = FALSE;
			}

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_GROUP_MEMBER_ID:
		////////////////////////////////////////
		{
			value = raw->group_member_number + 1;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_GROUP_MEMBER_NUMBER:
		////////////////////////////////////////
		{
			value = raw->group_member_number;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_GROUP_MEMBER_STATE:
		////////////////////////////////////////
		{
			entity
				*task = nullptr;

			//
			// First check for being on takeoff queue
			//

			if (get_local_entity_parent (en, LIST_TYPE_TAKEOFF_QUEUE))
			{
				value = GROUP_MEMBER_STATE_WAITING;

				break;
			}

			//
			// Check Task
			//

			task = get_local_entity_current_task (en);

			if (task)
			{
				if (task == get_local_entity_primary_task (en))
				{
					//
					// Member is on primary task
					//

					if (get_local_entity_int_value (task, INT_TYPE_TASK_STATE) == TASK_STATE_COMPLETED)
					{
						value = GROUP_MEMBER_STATE_RETURNING;
					}
					else
					{
						value = GROUP_MEMBER_STATE_NAVIGATING;
					}
				}
				else
				{
					//
					// Not A Primary Task
					//

					switch (get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE))
					{
						case ENTITY_SUB_TYPE_TASK_ENGAGE:
						{
							value = GROUP_MEMBER_STATE_ATTACKING;

							break;
						}
						case ENTITY_SUB_TYPE_TASK_LANDING:
						case ENTITY_SUB_TYPE_TASK_LANDING_HOLDING:
						{
							value = GROUP_MEMBER_STATE_LANDING;

							break;
						}
						case ENTITY_SUB_TYPE_TASK_TAKEOFF:
						case ENTITY_SUB_TYPE_TASK_TAKEOFF_HOLDING:
						{
							value = GROUP_MEMBER_STATE_TAKING_OFF;

							break;
						}
						default:
						{
							debug_fatal ("AC_INT: Invalid Task Type %d For Get Group Member State",
												get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE));
						}
					}
				}
			}
			else
			{
				value = GROUP_MEMBER_STATE_IDLE;
			}

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_GUNSHIP_RADAR_LOS_CLEAR:
		////////////////////////////////////////
		{
			value = raw->gunship_radar_los_clear;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_GUNSHIP_TYPE:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].gunship_type;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_IDENTIFY_AIRCRAFT:
		////////////////////////////////////////
		{
			value = TRUE;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_ID_NUMBER:
		////////////////////////////////////////
		{
			value = raw->id_number;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_ID_NUMBER_SIGNIFICANT_DIGITS:
		////////////////////////////////////////
		{
			value = raw->id_number_significant_digits;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_INITIAL_DAMAGE_LEVEL:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].initial_damage_level;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_LANDED:
		////////////////////////////////////////
		{

			switch (raw->operational_state)
			{

				case OPERATIONAL_STATE_LANDED:
				//case OPERATIONAL_STATE_REPAIRING:
				//case OPERATIONAL_STATE_REFUELING:
				//case OPERATIONAL_STATE_REARMING:
				{

					value = TRUE;

					break;
				}

				case OPERATIONAL_STATE_UNKNOWN:
				case OPERATIONAL_STATE_DEAD:
				case OPERATIONAL_STATE_DYING:
				case OPERATIONAL_STATE_LANDING:
				case OPERATIONAL_STATE_LANDING_HOLDING:
				case OPERATIONAL_STATE_NAVIGATING:
				case OPERATIONAL_STATE_STOPPED:
				case OPERATIONAL_STATE_TAKEOFF:
				case OPERATIONAL_STATE_TAKEOFF_HOLDING:
				case OPERATIONAL_STATE_TAXIING:
				case OPERATIONAL_STATE_WAITING:
				{

					value = FALSE;

					break;
				}

				default:
				{

					debug_fatal ("AC_INT: unknown operational state");
				}
			}

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_LIGHTS_ON:
		////////////////////////////////////////
		{
			value = raw->lights_on;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_MAP_ICON:
		////////////////////////////////////////
		{
			value = aircraft_database [raw->mob.sub_type].map_icon;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_MAX_WEAPON_CONFIG_TYPE:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].max_weapon_config_type;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_MIN_WEAPON_CONFIG_TYPE:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].min_weapon_config_type;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_MOBILE_MOVING:
		////////////////////////////////////////
		{

			switch (raw->operational_state)
			{

				case OPERATIONAL_STATE_LANDED:
				case OPERATIONAL_STATE_STOPPED:
				case OPERATIONAL_STATE_DEAD:
				//case OPERATIONAL_STATE_REPAIRING:
				//case OPERATIONAL_STATE_REFUELING:
				//case OPERATIONAL_STATE_REARMING:
				case OPERATIONAL_STATE_UNKNOWN:
				{

					value = FALSE;

					break;
				}

				case OPERATIONAL_STATE_DYING:
				case OPERATIONAL_STATE_LANDING:
				case OPERATIONAL_STATE_LANDING_HOLDING:
				case OPERATIONAL_STATE_NAVIGATING:
				case OPERATIONAL_STATE_TAKEOFF:
				case OPERATIONAL_STATE_TAKEOFF_HOLDING:
				case OPERATIONAL_STATE_TAXIING:
				case OPERATIONAL_STATE_WAITING:
				{

					value = TRUE;

					break;
				}

				default:
				{

					debug_fatal ("VH_INT: unknown operational state");
				}
			}

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_MOVEMENT_TYPE:
		////////////////////////////////////////
		{
			value = MOVEMENT_TYPE_AIR;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_OBJECT_3D_SHAPE:
		////////////////////////////////////////
		{
			value = raw->object_3d_shape;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_OFFENSIVE_CAPABILITY:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].offensive_capability;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_OPERATIONAL_STATE:
		////////////////////////////////////////
		{
			value = raw->operational_state;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_PLAYER_CONTROLLABLE:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].player_controllable;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_POINTS_VALUE:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].points_value;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_SCOUT_WEAPON_CONFIG_TYPE:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].scout_weapon_config_type;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_SELECTED_WEAPON:
		////////////////////////////////////////
		{
			value = raw->selected_weapon;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_SELECTED_WEAPON_SYSTEM_READY:
		////////////////////////////////////////
		{
			value = raw->selected_weapon_system_ready;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_TARGET_PRIORITY_TYPE:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].target_priority_type;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_TARGET_SYMBOL_TYPE:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].target_symbol_type;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_TARGET_TYPE:
		////////////////////////////////////////
		{
			value = TARGET_TYPE_AIR;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_TASK_LEADER:
		////////////////////////////////////////
		{
			entity
				*guide = nullptr;

			value = FALSE;

			guide = get_local_entity_parent (en, LIST_TYPE_FOLLOWER);

			if (guide)
			{
				if (get_local_entity_ptr_value (guide, PTR_TYPE_TASK_LEADER) == en)
				{
					value = TRUE;
				}
			}

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_TASK_TARGET_TYPE:
		////////////////////////////////////////
		{
			if (get_local_entity_int_value (en, INT_TYPE_LANDED))
			{
				value = (TASK_TARGET_TYPE_ANY | TASK_TARGET_TYPE_MOBILE | TASK_TARGET_TYPE_GROUNDED_AIRCRAFT);
			}
			else
			{
				value = (TASK_TARGET_TYPE_ANY | TASK_TARGET_TYPE_MOBILE | TASK_TARGET_TYPE_AIRBORNE_AIRCRAFT);
			}

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_THREAT_TYPE:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].threat_type;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_TRACK_ENTITY_ON_MAP:
		////////////////////////////////////////
		{
			value = TRUE;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_VIEW_CATEGORY:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].view_category;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_VIEW_TYPE:
		////////////////////////////////////////
		{
			value = aircraft_database[raw->mob.sub_type].view_type;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_VIEWABLE:
		////////////////////////////////////////
		{
			value = raw->view_link.parent != NULL;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_WEAPON_AND_TARGET_VECTORS_VALID:
		////////////////////////////////////////
		{
			value = raw->weapon_and_target_vectors_valid;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_WEAPON_CONFIG_TYPE:
		////////////////////////////////////////
		{
			value = raw->weapon_config_type;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_WEAPON_SYSTEM_READY:
		////////////////////////////////////////
		{
			////////////////////////////////////////
			//
			// WARNING! This only returns a valid value for aircraft that have weapon
			//          systems to be made ready in the current weapons configuration.
			//
			////////////////////////////////////////

			if (get_local_entity_float_value (en, FLOAT_TYPE_WEAPON_SYSTEM_READY_STATE) == AIRCRAFT_WEAPON_SYSTEM_READY_OPEN_FLOAT_VALUE)
			{
				value = TRUE;
			}
			else
			{
				value = FALSE;
			}

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

void overload_aircraft_int_value_functions (entity_types type)
{
	fn_get_local_entity_int_value				[type][INT_TYPE_AIR_TO_AIR_WEAPON_CONFIG_TYPE]				= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_AIR_TO_SURFACE_WEAPON_CONFIG_TYPE]			= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_AIRBORNE_AIRCRAFT]								= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_COLLISION_TEST_MOBILE]							= get_local_int_value;

	fn_set_local_entity_raw_int_value		[type][INT_TYPE_CPG_IDENTIFIED]									= set_local_int_value;
	fn_set_local_entity_int_value				[type][INT_TYPE_CPG_IDENTIFIED]									= set_local_int_value;
	fn_get_local_entity_int_value				[type][INT_TYPE_CPG_IDENTIFIED]									= get_local_int_value;

	fn_set_local_entity_raw_int_value		[type][INT_TYPE_DAMAGE_LEVEL]										= set_local_int_value;
	fn_set_local_entity_int_value				[type][INT_TYPE_DAMAGE_LEVEL]										= set_local_int_value;
	fn_set_client_server_entity_int_value	[type][INT_TYPE_DAMAGE_LEVEL][COMMS_MODEL_SERVER]			= set_server_int_value;
	fn_set_client_server_entity_int_value	[type][INT_TYPE_DAMAGE_LEVEL][COMMS_MODEL_CLIENT]			= set_client_int_value;
	fn_get_local_entity_int_value				[type][INT_TYPE_DAMAGE_LEVEL]										= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_DEFAULT_3D_SHAPE]								= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_DEFAULT_WEAPON_CONFIG_TYPE]					= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_DEFAULT_WEAPON_TYPE]							= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_DESTROYED_3D_SHAPE]								= get_local_int_value;

	fn_set_local_entity_raw_int_value		[type][INT_TYPE_EJECTED]											= set_local_int_value;
	fn_set_local_entity_int_value				[type][INT_TYPE_EJECTED]											= set_local_int_value;
	fn_set_client_server_entity_int_value	[type][INT_TYPE_EJECTED][COMMS_MODEL_SERVER]					= set_server_int_value;
	fn_set_client_server_entity_int_value	[type][INT_TYPE_EJECTED][COMMS_MODEL_CLIENT]					= set_client_int_value;
	fn_get_local_entity_int_value				[type][INT_TYPE_EJECTED]											= get_local_int_value;

	fn_set_local_entity_raw_int_value		[type][INT_TYPE_TROOPS_ONBOARD]											= set_local_int_value;
	fn_set_local_entity_int_value				[type][INT_TYPE_TROOPS_ONBOARD]											= set_local_int_value;
	fn_set_client_server_entity_int_value	[type][INT_TYPE_TROOPS_ONBOARD][COMMS_MODEL_SERVER]					= set_server_int_value;
	fn_set_client_server_entity_int_value	[type][INT_TYPE_TROOPS_ONBOARD][COMMS_MODEL_CLIENT]					= set_client_int_value;
	fn_get_local_entity_int_value				[type][INT_TYPE_TROOPS_ONBOARD]											= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_ENGAGE_ENEMY]										= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_EXPLOSIVE_POWER]									= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_EXPLOSIVE_QUALITY]								= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_FORCE]												= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_FORCE_INFO_CATAGORY]							= get_local_int_value;

	fn_set_local_entity_raw_int_value  		[type][INT_TYPE_FORMATION_POSITION]								= set_local_int_value;
	fn_set_local_entity_int_value				[type][INT_TYPE_FORMATION_POSITION]								= set_local_int_value;
	fn_set_client_server_entity_int_value	[type][INT_TYPE_FORMATION_POSITION][COMMS_MODEL_SERVER]	= set_server_int_value;
	fn_set_client_server_entity_int_value	[type][INT_TYPE_FORMATION_POSITION][COMMS_MODEL_CLIENT]	= set_client_int_value;
	fn_get_local_entity_int_value				[type][INT_TYPE_FORMATION_POSITION]								= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_GROUP_LEADER]										= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_GROUP_MEMBER_ID]									= get_local_int_value;

	fn_set_local_entity_raw_int_value		[type][INT_TYPE_GROUP_MEMBER_NUMBER]							= set_local_int_value;
	fn_set_local_entity_int_value				[type][INT_TYPE_GROUP_MEMBER_NUMBER]							= set_local_int_value;
	fn_set_client_server_entity_int_value	[type][INT_TYPE_GROUP_MEMBER_NUMBER][COMMS_MODEL_SERVER]	= set_server_int_value;
	fn_set_client_server_entity_int_value	[type][INT_TYPE_GROUP_MEMBER_NUMBER][COMMS_MODEL_CLIENT]	= set_client_int_value;
	fn_get_local_entity_int_value				[type][INT_TYPE_GROUP_MEMBER_NUMBER]							= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_GROUP_MEMBER_STATE]								= get_local_int_value;

	fn_set_local_entity_raw_int_value		[type][INT_TYPE_GUNSHIP_RADAR_LOS_CLEAR]						= set_local_int_value;
	fn_set_local_entity_int_value				[type][INT_TYPE_GUNSHIP_RADAR_LOS_CLEAR]						= set_local_int_value;
	fn_get_local_entity_int_value				[type][INT_TYPE_GUNSHIP_RADAR_LOS_CLEAR]						= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_GUNSHIP_TYPE]										= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_IDENTIFY_AIRCRAFT]								= get_local_int_value;

	fn_set_local_entity_raw_int_value		[type][INT_TYPE_ID_NUMBER]											= set_local_int_value;
	fn_set_local_entity_int_value				[type][INT_TYPE_ID_NUMBER]											= set_local_int_value;
	fn_get_local_entity_int_value				[type][INT_TYPE_ID_NUMBER]											= get_local_int_value;

	fn_set_local_entity_raw_int_value		[type][INT_TYPE_ID_NUMBER_SIGNIFICANT_DIGITS]				= set_local_int_value;
	fn_set_local_entity_int_value				[type][INT_TYPE_ID_NUMBER_SIGNIFICANT_DIGITS]				= set_local_int_value;
	fn_get_local_entity_int_value				[type][INT_TYPE_ID_NUMBER_SIGNIFICANT_DIGITS]				= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_INITIAL_DAMAGE_LEVEL]							= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_LANDED]												= get_local_int_value;

	fn_set_local_entity_raw_int_value		[type][INT_TYPE_LIGHTS_ON]											= set_local_raw_int_value;
	fn_set_local_entity_int_value				[type][INT_TYPE_LIGHTS_ON]											= set_local_int_value;
	fn_set_client_server_entity_int_value	[type][INT_TYPE_LIGHTS_ON][COMMS_MODEL_SERVER]				= set_server_int_value;
	fn_set_client_server_entity_int_value	[type][INT_TYPE_LIGHTS_ON][COMMS_MODEL_CLIENT]				= set_client_int_value;
	fn_get_local_entity_int_value				[type][INT_TYPE_LIGHTS_ON]											= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_MAP_ICON]											= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_MAX_WEAPON_CONFIG_TYPE]						= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_MIN_WEAPON_CONFIG_TYPE]						= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_MOBILE_MOVING]									= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_MOVEMENT_TYPE]									= get_local_int_value;

	fn_set_local_entity_raw_int_value		[type][INT_TYPE_OBJECT_3D_SHAPE]									= set_local_int_value;
	fn_set_local_entity_int_value				[type][INT_TYPE_OBJECT_3D_SHAPE]									= set_local_int_value;
	fn_get_local_entity_int_value				[type][INT_TYPE_OBJECT_3D_SHAPE]									= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_OFFENSIVE_CAPABILITY]							= get_local_int_value;

	fn_set_local_entity_raw_int_value		[type][INT_TYPE_OPERATIONAL_STATE]								= set_local_int_value;
	fn_set_local_entity_int_value				[type][INT_TYPE_OPERATIONAL_STATE]								= set_local_int_value;
	fn_set_client_server_entity_int_value	[type][INT_TYPE_OPERATIONAL_STATE][COMMS_MODEL_SERVER]	= set_server_int_value;
	fn_set_client_server_entity_int_value	[type][INT_TYPE_OPERATIONAL_STATE][COMMS_MODEL_CLIENT]	= set_client_int_value;
	fn_get_local_entity_int_value				[type][INT_TYPE_OPERATIONAL_STATE]								= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_PLAYER_CONTROLLABLE]	 						= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_POINTS_VALUE]										= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_SCOUT_WEAPON_CONFIG_TYPE]						= get_local_int_value;

	fn_set_local_entity_raw_int_value		[type][INT_TYPE_SELECTED_WEAPON]									= set_local_raw_int_value;
	fn_set_local_entity_int_value				[type][INT_TYPE_SELECTED_WEAPON]									= set_local_int_value;
	fn_set_client_server_entity_int_value	[type][INT_TYPE_SELECTED_WEAPON][COMMS_MODEL_SERVER]		= set_server_int_value;
	fn_set_client_server_entity_int_value	[type][INT_TYPE_SELECTED_WEAPON][COMMS_MODEL_CLIENT]		= set_client_int_value;
	fn_get_local_entity_int_value				[type][INT_TYPE_SELECTED_WEAPON]									= get_local_int_value;

	fn_set_local_entity_raw_int_value		[type][INT_TYPE_SELECTED_WEAPON_SYSTEM_READY]  				= set_local_int_value;
	fn_set_local_entity_int_value				[type][INT_TYPE_SELECTED_WEAPON_SYSTEM_READY]				= set_local_int_value;
	fn_get_local_entity_int_value				[type][INT_TYPE_SELECTED_WEAPON_SYSTEM_READY]				= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_TARGET_PRIORITY_TYPE]							= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_TARGET_SYMBOL_TYPE]								= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_TARGET_TYPE]										= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_TASK_LEADER]										= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_TASK_TARGET_TYPE]								= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_THREAT_TYPE]										= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_TRACK_ENTITY_ON_MAP]							= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_VIEW_CATEGORY]									= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_VIEW_TYPE]											= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_VIEWABLE]											= get_local_int_value;

	fn_set_local_entity_raw_int_value		[type][INT_TYPE_WEAPON_AND_TARGET_VECTORS_VALID]  			= set_local_int_value;
	fn_set_local_entity_int_value				[type][INT_TYPE_WEAPON_AND_TARGET_VECTORS_VALID]			= set_local_int_value;
	fn_get_local_entity_int_value				[type][INT_TYPE_WEAPON_AND_TARGET_VECTORS_VALID]			= get_local_int_value;

	fn_set_local_entity_raw_int_value		[type][INT_TYPE_WEAPON_CONFIG_TYPE]								= set_local_raw_int_value;
	fn_set_local_entity_int_value				[type][INT_TYPE_WEAPON_CONFIG_TYPE]								= set_local_int_value;
	fn_set_client_server_entity_int_value	[type][INT_TYPE_WEAPON_CONFIG_TYPE][COMMS_MODEL_SERVER]	= set_server_int_value;
	fn_set_client_server_entity_int_value	[type][INT_TYPE_WEAPON_CONFIG_TYPE][COMMS_MODEL_CLIENT]	= set_client_int_value;
	fn_get_local_entity_int_value				[type][INT_TYPE_WEAPON_CONFIG_TYPE]								= get_local_int_value;

	fn_get_local_entity_int_value				[type][INT_TYPE_WEAPON_SYSTEM_READY]							= get_local_int_value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
