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

#include "ai/taskgen/taskgen.h"
#include "ai/ai_misc/ai_route.h"
#include "ai/faction/faction.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////
//
// 2 levels of debug
//
//////////////////////////////////////////////////////

#define DEBUG_MODULE 0

#define INITIAL_SLEEP_TIME 				5
#define OFFSET_SLEEP_TIME 					2

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MODULE >= 2

static int response_to_link_child (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	debug_log_entity_message (message, receiver, sender, pargs);

	return (TRUE);
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MODULE >= 2

static int response_to_unlink_child (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	debug_log_entity_message (message, receiver, sender, pargs);

	return (TRUE);
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MODULE >= 2

static int response_to_link_parent (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	debug_log_entity_message (message, receiver, sender, pargs);

	return (TRUE);
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MODULE >= 2

static int response_to_unlink_parent (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	debug_log_entity_message (message, receiver, sender, pargs);

	return (TRUE);
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_task_assigned (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	entity
		*task,
		*group,
		*landing_en,
		*end_keysite,
		*end_landing;

	mobile
		*raw;

	int
		task_type;

	#if DEBUG_MODULE >= 2

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	ASSERT (sender);

	ASSERT (sender->type == ENTITY_TYPE_TASK);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	raw = (mobile *) get_local_entity_data (receiver);

	group = get_local_entity_parent (receiver, LIST_TYPE_MEMBER);

	task_type = get_local_entity_int_value (sender, INT_TYPE_ENTITY_SUB_TYPE); 

	/////////////////////////////////////////////////////////////////
	//
	// Assign task target to mobile (must be done before takeoff task assigned)
	//
	/////////////////////////////////////////////////////////////////

	if (task_type == ENTITY_SUB_TYPE_TASK_ENGAGE)
	{
		entity
			*guide,
			*target;

		target = get_local_entity_parent (sender, LIST_TYPE_TASK_DEPENDENT);

		ASSERT (target);

		set_client_server_entity_parent (receiver, LIST_TYPE_TARGET, target);

		guide = get_local_entity_parent (receiver, LIST_TYPE_FOLLOWER);

		ASSERT (guide);

		ASSERT (get_local_entity_parent (guide, LIST_TYPE_GUIDE) == sender);

		initialise_attack_guide (guide);
	}

	/////////////////////////////////////////////////////////////////
	//
	//
	//
	/////////////////////////////////////////////////////////////////

	switch (get_local_entity_int_value (receiver, INT_TYPE_OPERATIONAL_STATE))
	{

		case OPERATIONAL_STATE_LANDED:
		{

			if ((task_type == ENTITY_SUB_TYPE_TASK_ENGAGE) && (!get_local_entity_int_value (group, INT_TYPE_AIRCRAFT_GROUP)))
			{
				//
				// Ground based vehicles do not need to takeoff in order to do engage tasks
				//
			}
			else
			{
				//
				// Member landed so must takeoff first.
				//
	
				landing_en = get_local_group_member_landing_entity_from_keysite (receiver);
	
				ASSERT (landing_en);
	
				task = get_local_landing_entity_task (landing_en, ENTITY_SUB_TYPE_TASK_TAKEOFF);
	
				ASSERT (task);
	
				if (get_local_entity_int_value (receiver, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI)
				{
					//
					// Set weapon config, AI ONLY
					//
	
					if (get_local_entity_int_value (receiver, INT_TYPE_IDENTIFY_AIRCRAFT))
					{
						if (task_database [task_type].ai_stats.movement_stealth > 0)
						{
							set_client_server_entity_int_value (receiver, INT_TYPE_WEAPON_CONFIG_TYPE, get_local_entity_int_value (receiver, INT_TYPE_SCOUT_WEAPON_CONFIG_TYPE));
						}
						else
						{
							switch (get_local_entity_int_value (sender, INT_TYPE_TASK_TARGET_CLASS))
							{
								case TASK_TARGET_CLASS_AIR:
								{
									set_client_server_entity_int_value (receiver, INT_TYPE_WEAPON_CONFIG_TYPE, get_local_entity_int_value (receiver, INT_TYPE_AIR_TO_AIR_WEAPON_CONFIG_TYPE));
			
									break;
								}
								case TASK_TARGET_CLASS_GROUND:
								{
									set_client_server_entity_int_value (receiver, INT_TYPE_WEAPON_CONFIG_TYPE, get_local_entity_int_value (receiver, INT_TYPE_AIR_TO_SURFACE_WEAPON_CONFIG_TYPE));
		
									break;
								}
								default :
								{
									set_client_server_entity_int_value (receiver, INT_TYPE_WEAPON_CONFIG_TYPE, get_local_entity_int_value (receiver, INT_TYPE_DEFAULT_WEAPON_CONFIG_TYPE));
		
									break;
								}
							}
						}
					}
				}
	
				//
				// Check if entity can Lock takeoff route and Reserve landing site at destination keysite
				//
	
				if (notify_local_entity (ENTITY_MESSAGE_LOCK_TAKEOFF_ROUTE, landing_en, receiver))
				{
	
					insert_mobile_into_takeoff_route (receiver, landing_en);
				}
				else
				{
					#if DEBUG_MODULE
	
					debug_log ("MB_MSGS: Task %s : Mobile %s (%d) can't lock takeoff route",
									get_local_entity_string (sender, STRING_TYPE_FULL_NAME),
									get_local_entity_string (receiver, STRING_TYPE_FULL_NAME),
									get_local_entity_index (receiver));
	
					#endif
	
					//
					// insert mobile into takeoff queue
					//
	
					ASSERT (!get_local_entity_parent (receiver, LIST_TYPE_TAKEOFF_QUEUE));
	
					insert_local_entity_into_parents_child_list (receiver, LIST_TYPE_TAKEOFF_QUEUE, landing_en, NULL);
				}
	
				//
				// reserve landing site for mobile
				//
	
				if (get_local_entity_int_value (sender, INT_TYPE_ASSESS_LANDING))
				{
					end_keysite = (entity *) get_local_entity_ptr_value (sender, PTR_TYPE_RETURN_KEYSITE);
		
					ASSERT (end_keysite);
		
					end_landing = get_local_entity_landing_entity (end_keysite, group_database [get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE)].default_landing_type);
		
					notify_local_entity (ENTITY_MESSAGE_RESERVE_LANDING_SITE, end_landing, receiver, 1);
				}
	
				/////////////////////////////////////////////////////////////////
				//
				// SPECIAL_EFFECT_HOOK FOR TAKEOFF REQUEST
				//
				/////////////////////////////////////////////////////////////////
	
				/////////////////////////////////////////////////////////////////
				//
				//
				/////////////////////////////////////////////////////////////////
			}
		
			break;
		}

		case OPERATIONAL_STATE_TAXIING:
		case OPERATIONAL_STATE_TAKEOFF:
		case OPERATIONAL_STATE_TAKEOFF_HOLDING:
		case OPERATIONAL_STATE_LANDING:
		case OPERATIONAL_STATE_LANDING_HOLDING:
		{

			#if DEBUG_MODULE

			if (receiver == get_external_view_entity ())
			{
				
				debug_log ("MB_MSGS: not assigning landing/holding mobile %s (%d, group %d)",
							get_local_entity_string (receiver, STRING_TYPE_FULL_NAME),
							get_local_entity_safe_index (receiver),
							get_local_entity_index (get_local_entity_parent (receiver, LIST_TYPE_MEMBER)));
			}

			#endif

			break;
		}

		case OPERATIONAL_STATE_STOPPED:
		case OPERATIONAL_STATE_WAITING:
		{

			if (task_type != ENTITY_SUB_TYPE_TASK_ENGAGE)
			{
				set_client_server_entity_int_value (receiver, INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_NAVIGATING);
			}

			//
			// Intentional follow-through...
			//
		}

		default:
		{

			#if DEBUG_MODULE

			if (receiver == get_external_view_entity ())
			{
				
				debug_log ("MB_MSGS: assign non-landed mobile %s (%d, group %d)",
							get_local_entity_string (receiver, STRING_TYPE_FULL_NAME),
							get_local_entity_safe_index (receiver),
							get_local_entity_index (get_local_entity_parent (receiver, LIST_TYPE_MEMBER)));
			}

			#endif

			/////////////////////////////////////////////////////////////////
			//
			// SPECIAL_EFFECT_HOOK FOR ASSIGNING TASK TO IN-FLIGHT DRONES
			//
			/////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////
			//
			//
			/////////////////////////////////////////////////////////////////

			break;
		}
	}
	
	//
	// If not attacking, then "button-up"
	//
		
	if (task_type != ENTITY_SUB_TYPE_TASK_ENGAGE)
	{
		set_client_server_entity_int_value (receiver, INT_TYPE_SELECTED_WEAPON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON);
	}

	/////////////////////////////////////////////////////////////////
	//
	// SPECIAL_EFFECT_HOOK FOR TASK ASSIGNED 
	//
	/////////////////////////////////////////////////////////////////

	set_local_entity_float_value (receiver, FLOAT_TYPE_VIEW_INTEREST_LEVEL, DEFAULT_VIEW_INTEREST_LEVEL);

	/////////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////////

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_waypoint_approach_reached (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	ASSERT (sender);

	ASSERT (sender->type == ENTITY_TYPE_WAYPOINT);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	#if DEBUG_MODULE >= 2

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	open_client_server_entity_flaps (receiver);

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int
	num_waypoint_attack_cpg_comments [NUM_ENTITY_SIDES] = {0, 3, 3},
	last_waypoint_attack_cpg_comment [NUM_ENTITY_SIDES] = {0, 0, 0};

static speech_instance_type
	waypoint_attack_cpg_comments [] =
	{
		{ SPEECH_CPG_APPROACHING_ENGAGEMENT_AREA,				SPEECH_ARRAY_CPG_MESSAGES,			100, 	SPEECH_INTRODUCTION_NEVER },
		{ SPEECH_CPG_APPROACHING_BATTLE_POSITION,				SPEECH_ARRAY_CPG_MESSAGES,			100, 	SPEECH_INTRODUCTION_NEVER },
		{ SPEECH_CPG_APPROACHING_RP,								SPEECH_ARRAY_CPG_MESSAGES,			100, 	SPEECH_INTRODUCTION_NEVER },
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int
	num_waypoint_attack_wingman_comments [NUM_ENTITY_SIDES] = {0, 3, 3},
	last_waypoint_attack_wingman_comment [NUM_ENTITY_SIDES] = {0, 0, 0};

static speech_instance_type
	waypoint_attack_wingman_comments [] =
	{
		{ SPEECH_WINGMAN_APPROACHING_ENGAGEMENT_AREA,		SPEECH_ARRAY_WINGMAN_MESSAGES,	100, 	SPEECH_INTRODUCTION_ALWAYS },
		{ SPEECH_WINGMAN_APPROACHING_BATTLE_POSITION,		SPEECH_ARRAY_WINGMAN_MESSAGES,	100, 	SPEECH_INTRODUCTION_ALWAYS },
		{ SPEECH_WINGMAN_APPROACHING_RP,							SPEECH_ARRAY_WINGMAN_MESSAGES,	100, 	SPEECH_INTRODUCTION_ALWAYS },
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_waypoint_attack_action (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	entity
		*group,
		*objective,
		*task;

	entity_sides
		side;

	mobile
		*raw;

	vec3d
		*objective_pos;

	unsigned int
		task_target_type;

	int
		val,
		speech_index;

	ASSERT (sender);

	ASSERT (sender->type == ENTITY_TYPE_WAYPOINT);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	#if DEBUG_MODULE >= 2

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	raw = (mobile *) get_local_entity_data (receiver);

	//
	// if the groups current task has an objective - create engage tasks in the objectives sector,
	// else - create engage tasks in the current sector
	// 

	group = get_local_entity_parent (receiver, LIST_TYPE_MEMBER);

	ASSERT (group);

	// Group should not have been assigned this task if it is a passive group
	ASSERT (get_local_entity_int_value (group, INT_TYPE_ENGAGE_ENEMY));

	task = get_local_entity_parent (sender, LIST_TYPE_WAYPOINT);

	ASSERT (task);

	side = (entity_sides) get_local_entity_int_value (receiver, INT_TYPE_SIDE);

	//
	// Play Speech
	//
	
	if (get_local_entity_int_value (receiver, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI)
	{
		val = get_speech_random_value
				(
					waypoint_attack_wingman_comments,
					num_waypoint_attack_wingman_comments [side],
					last_waypoint_attack_wingman_comment [side]
				);

		speech_index = waypoint_attack_wingman_comments [val].speech_index;
	
		play_client_server_wingman_message
		(
			receiver,
			1.0,
			5.0,
			SPEECH_CATEGORY_MISSION_RELATED, -1.0,
			waypoint_attack_wingman_comments [val].introduction,
			SPEECH_ARRAY_WINGMAN_MESSAGES, speech_index
		);
	}
	else
	{
		val = get_speech_random_value
				(
					waypoint_attack_cpg_comments,
					num_waypoint_attack_cpg_comments [side],
					last_waypoint_attack_cpg_comment [side]
				);

		speech_index = waypoint_attack_cpg_comments [val].speech_index;
	
		play_client_server_cpg_message (receiver, 1.0, 5.0, SPEECH_CATEGORY_MISSION_RELATED, -1.0, speech_index);
	}

	//
	// Engage Targets
	//
	
	task_target_type = get_local_entity_int_value (task, INT_TYPE_TASK_TARGET_TYPE);

	objective = get_local_entity_parent (task, LIST_TYPE_TASK_DEPENDENT);

	if (objective)
	{
		switch (get_local_entity_type (objective))
		{
			case ENTITY_TYPE_GROUP:
			{
				engage_targets_in_group (group, objective, FALSE);

				break;
			}
			case ENTITY_TYPE_HELICOPTER:
			case ENTITY_TYPE_FIXED_WING:
			case ENTITY_TYPE_ROUTED_VEHICLE:
			case ENTITY_TYPE_SHIP_VEHICLE:
			case ENTITY_TYPE_ANTI_AIRCRAFT:
			{
				engage_specific_target (group, objective, TASK_ASSIGN_ALL_MEMBERS, FALSE);

				break;
			}
			case ENTITY_TYPE_SECTOR:
			{
				int
					sx,
					sz;
					
				sx = get_local_entity_int_value (objective, INT_TYPE_X_SECTOR);
				sz = get_local_entity_int_value (objective, INT_TYPE_Z_SECTOR);

				engage_targets_in_sector (group, sx, sz, task_target_type, FALSE);

				break;
			}
			default:
			{			
				objective_pos = get_local_entity_vec3d_ptr (objective, VEC3D_TYPE_POSITION);

				ASSERT (objective_pos);

				engage_targets_in_area (group, objective_pos, 2 * KILOMETRE, task_target_type, FALSE);

				break;
			}
		}
	}
	else
	{
		objective_pos = get_local_entity_vec3d_ptr (group, VEC3D_TYPE_POSITION);

		engage_targets_in_area (group, objective_pos, 2 * KILOMETRE, task_target_type, FALSE);
	}

	set_local_entity_float_value (receiver, FLOAT_TYPE_VIEW_INTEREST_LEVEL, DEFAULT_VIEW_INTEREST_LEVEL);

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_waypoint_convoy_reached (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	entity
		*mb,
		*group,
		*wp;

	vec3d
		*mb_pos,
		*wp_pos,
		vec;

	float
		distance,
		sleep;

	int
		group_count;

	mobile
		*raw;

	ASSERT (sender);

	ASSERT (sender->type == ENTITY_TYPE_WAYPOINT);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	#if DEBUG_MODULE >= 2

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	group_count = 0;
	
	raw = (mobile *) get_local_entity_data (receiver);

	set_local_entity_float_value (receiver, FLOAT_TYPE_VIEW_INTEREST_LEVEL, DEFAULT_VIEW_INTEREST_LEVEL);

	//
	// work out sleep timer
	//

	group = get_local_entity_parent (receiver, LIST_TYPE_MEMBER);

	mb = get_local_entity_first_child (group, LIST_TYPE_MEMBER);
	
	wp = sender;

	while (mb)
	{
	
		//get_formation_position (get_local_entity_int_value (wp, INT_TYPE_WAYPOINT_FORMATION), get_local_entity_int_value (mb, INT_TYPE_FORMATION_POSITION), &vec);
	
		//distance = sqrt ((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
		mb_pos = get_local_entity_vec3d_ptr (mb, VEC3D_TYPE_POSITION);
		wp_pos = get_local_entity_vec3d_ptr (wp, VEC3D_TYPE_POSITION);
		vec.x = wp_pos->x - mb_pos->x;
		vec.z = wp_pos->z - mb_pos->z;
		distance = normalise_any_3d_vector (&vec);
	
		if (group)
		{
	
			group_count = get_local_entity_int_value (group, INT_TYPE_MEMBER_COUNT);
		}

		// index number
		sleep = INITIAL_SLEEP_TIME + (OFFSET_SLEEP_TIME * get_local_entity_int_value (mb, INT_TYPE_FORMATION_POSITION));
	
  		// allow for distance from wp
		sleep -= distance / get_local_entity_float_value (mb, FLOAT_TYPE_CRUISE_VELOCITY);

		sleep = max (sleep, 0.0f);
	
		set_client_server_entity_float_value (mb, FLOAT_TYPE_SLEEP, sleep);

		mb = get_local_entity_child_succ (mb, LIST_TYPE_MEMBER);
	}

	#if DEBUG_MODULE
	
	if (receiver == get_external_view_entity ())
	{
			
		debug_log ("MB_MSGS: convoy waypoint reached mb %d (gp %d), formation pos %d setting sleep to %f, distance %f", get_local_entity_safe_index (receiver), get_local_entity_safe_index (group), get_local_entity_int_value (receiver, INT_TYPE_FORMATION_POSITION), sleep, distance);
	}

	#endif

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_waypoint_defend_reached (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	float
		sleep,
		fuel;

	entity
		*group,
		*member,
		*task;

	vec3d
		new_pos;

	mobile
		*raw;

	ASSERT (sender);

	ASSERT (sender->type == ENTITY_TYPE_WAYPOINT);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	#if DEBUG_MODULE >= 2

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	#if DEBUG_MODULE

	if (receiver == get_external_view_entity ())
	{
		debug_log ("MB_MSGS: defend waypoint reached mb %d", get_local_entity_safe_index (receiver));
	}

	#endif

	raw = (mobile *) get_local_entity_data (receiver);

	group = get_local_entity_parent (receiver, LIST_TYPE_MEMBER);

	task = get_local_entity_parent (sender, LIST_TYPE_WAYPOINT);

	//
	// Nofity task of task_complete
	//

	notify_local_entity (ENTITY_MESSAGE_TASK_TERMINATED, task, receiver, TASK_TERMINATED_WAYPOINT_ROUTE_COMPLETE);

	set_local_entity_int_value (group, INT_TYPE_ENGAGE_ENEMY, get_local_entity_int_value (group, INT_TYPE_DEFAULT_ENGAGE_ENEMY));

	//
	// for all group members
	//

	group = get_local_entity_parent (receiver, LIST_TYPE_MEMBER);

	member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

	while (member)
	{
		
		set_local_entity_int_value (member, INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_STOPPED);
	
		set_local_entity_float_value (member, FLOAT_TYPE_VIEW_INTEREST_LEVEL, DEFAULT_VIEW_INTEREST_LEVEL);
	
		set_infinite_smoke_list_generating_state (member, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_VEHICLE_WAKE, INFINITE_SMOKE_OFF);
	
		if (get_local_entity_int_value (member, INT_TYPE_LIGHTS_ON))
		{
	
			set_vehicle_headlight_state (member, OFF);
		}

		//
		// sort out supplies (ie. reduce group fuel only)
		//

		fuel = get_local_entity_float_value (group, FLOAT_TYPE_FUEL_SUPPLY_LEVEL);

		fuel -= get_local_entity_float_value (receiver, FLOAT_TYPE_FUEL_ECONOMY) * FUEL_USAGE_ACCELERATOR;

		fuel = bound (fuel, 0.0, 100.0);

		set_client_server_entity_float_value (group, FLOAT_TYPE_FUEL_SUPPLY_LEVEL, fuel);

		sleep = get_local_entity_refueling_sleep_time (group);
		set_local_entity_float_value (member, FLOAT_TYPE_SLEEP, sleep);

		//
		// Set Y to terrain altitude to make sure they are on the floor
		//

		get_local_entity_vec3d (member, VEC3D_TYPE_POSITION, &new_pos);

		new_pos.y = get_3d_terrain_elevation (new_pos.x, new_pos.z);

		set_client_server_entity_vec3d (member, VEC3D_TYPE_POSITION, &new_pos);

		#if DEBUG_MODULE || DEBUG_SUPPLY

		debug_log ("MB_MSGS: SUPPLY_INFO: Ground force defending: reducing group %s (%d) fuel level for %s (%d) to %f, sleeping for %f",
						get_local_entity_string (group, STRING_TYPE_FULL_NAME),
						get_local_entity_index (group),
						get_local_entity_string (member, STRING_TYPE_FULL_NAME),
						get_local_entity_index (member),
						fuel,
						sleep);

		#endif

		member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
	}

	assess_group_supplies (group);

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_waypoint_drop_off_reached (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	entity
		//*mb,
		//*group,
		*requester,
		*cargo;

	ASSERT (sender);

	ASSERT (sender->type == ENTITY_TYPE_WAYPOINT);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	#if DEBUG_MODULE >= 2

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	cargo = get_local_entity_first_child (receiver, LIST_TYPE_MOVEMENT_DEPENDENT);

	while (cargo)
	{

		if (get_local_entity_int_value (cargo, INT_TYPE_IDENTIFY_CARGO))
		{

			requester = get_local_entity_parent (sender, LIST_TYPE_TASK_DEPENDENT);

			if (requester)
			{

				if (get_local_entity_type (requester) == ENTITY_TYPE_KEYSITE)
				{
	
					delete_local_entity_from_parents_child_list (cargo, LIST_TYPE_MOVEMENT_DEPENDENT);
	
					#if DEBUG_MODULE
	
					debug_log ("MB_MSGS: SUPPLY_INFO: removing cargo %s from %s movement_dependent list", entity_sub_type_cargo_names [get_local_entity_int_value (cargo, INT_TYPE_ENTITY_SUB_TYPE)], entity_type_names [get_local_entity_type (receiver)]);
	
					#endif
		
					insert_local_entity_into_parents_child_list (cargo, LIST_TYPE_CARGO, requester, NULL);
		
					notify_local_entity (ENTITY_MESSAGE_WAYPOINT_DROP_OFF_REACHED, requester, receiver, cargo);
		
					transmit_entity_comms_message (ENTITY_COMMS_SWITCH_LIST, cargo, LIST_TYPE_MOVEMENT_DEPENDENT, requester, LIST_TYPE_CARGO);
	
					#if DEBUG_MODULE || DEBUG_SUPPLY
		
					debug_log ("MB_MSGS: SUPPLY_INFO: Drop_Off reached... inserting cargo %s into %s cargo list", entity_sub_type_cargo_names [get_local_entity_int_value (cargo, INT_TYPE_ENTITY_SUB_TYPE)], get_local_entity_string (requester, STRING_TYPE_KEYSITE_NAME));
		
					#endif
				}
				else
				{

					float
						level;

					//
					// its a group
					//

					ASSERT (get_local_entity_type (requester) == ENTITY_TYPE_GROUP);

					if (get_local_entity_int_value (cargo, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_CARGO_AMMO)
					{

						level = get_local_entity_float_value (requester, FLOAT_TYPE_AMMO_SUPPLY_LEVEL);

						level += (KEYSITE_MINIMUM_AMMO_SUPPLY_LEVEL * AMMO_RESTOCK_ACCELERATOR);

						level = bound (level, 0.0, 100.0);

						set_client_server_entity_float_value (requester, FLOAT_TYPE_AMMO_SUPPLY_LEVEL, level);
		
						#if DEBUG_MODULE || DEBUG_SUPPLY

						debug_log ("MB_MSGS: SUPPLY_INFO: Drop_Off reached... increasing group ammo to %f", level);

						#endif
					}
					else if (get_local_entity_int_value (cargo, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_CARGO_FUEL)
					{

						level = get_local_entity_float_value (requester, FLOAT_TYPE_FUEL_SUPPLY_LEVEL);

						level += (KEYSITE_MINIMUM_FUEL_SUPPLY_LEVEL * FUEL_RESTOCK_ACCELERATOR);

						level = bound (level, 0.0, 100.0);

						set_client_server_entity_float_value (requester, FLOAT_TYPE_FUEL_SUPPLY_LEVEL, level);
		
						#if DEBUG_MODULE || DEBUG_SUPPLY

						debug_log ("MB_MSGS: SUPPLY_INFO: Drop_Off reached... increasing group fuel to %f", level);

						#endif
					}
					else
					{
		
						#if DEBUG_MODULE || DEBUG_SUPPLY
			
						debug_log ("MB_MSGS: SUPPLY_INFO: invalid cargo type for group");
			
						#endif
					}
				}
			}
			else
			{

				#if DEBUG_MODULE || DEBUG_SUPPLY

				debug_log ("MB_MSGS: SUPPLY_INFO: Reached Dropoff but no keysite to deliever to.");

				#endif
			}
		}

		cargo = get_local_entity_child_succ (cargo, LIST_TYPE_MOVEMENT_DEPENDENT);
	}
/*
	//
	// try to fire off the cargo
	//

	group = get_local_entity_parent (receiver, LIST_TYPE_MEMBER);

	mb = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

	while (mb)
	{
	
		if (get_local_entity_int_value (mb, INT_TYPE_SELECTED_WEAPON) == ENTITY_SUB_TYPE_WEAPON_CRATE)
		{
	
			if (aircraft_fire_weapon (mb, AIRCRAFT_FIRE_WEAPON_SYSTEM_NOT_READY) == AIRCRAFT_FIRE_WEAPON_SYSTEM_NOT_READY)
			{
	
				//
				// go round again
				//

				#if DEBUG_MODULE

				debug_log ("MB_MSGS: SUPPLY_INFO: aircraft not ready to drop crates");

				#endif
			}
			else
			{

				#if DEBUG_MODULE

				debug_log ("MB_MSGS: SUPPLY_INFO: aircraft dropping crate");

				#endif
			}
		}

		close_client_server_entity_cargo_doors (mb);
	
		mb = get_local_entity_child_succ (mb, LIST_TYPE_MEMBER);
	}
*/
	//
	//
	//

	if (get_local_entity_int_value (receiver, INT_TYPE_OPERATIONAL_STATE) != OPERATIONAL_STATE_NAVIGATING)
	{

		set_client_server_entity_int_value (receiver, INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_NAVIGATING);
	}

	set_local_entity_float_value (receiver, FLOAT_TYPE_VIEW_INTEREST_LEVEL, DEFAULT_VIEW_INTEREST_LEVEL);

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_waypoint_finish_drop_off_reached (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	entity
		*task;

	#if DEBUG_MODULE

	debug_log ("MB_MSGS: FINSIH_DROP_OFF REACHED. closing cargo doors");

	#endif
		
	close_client_server_entity_cargo_doors (receiver);

	task = get_local_entity_parent (sender, LIST_TYPE_WAYPOINT);

	notify_local_entity (ENTITY_MESSAGE_TASK_COMPLETED, task, receiver, TASK_TERMINATED_OBJECTIVE_MESSAGE);

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_waypoint_land_reached (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	entity
		*mb,
		*task,
		*group,
		*keysite,
		*landing,
		*new_task,
		*new_keysite,
		*new_landing;

	mobile
		*raw;

	ASSERT (sender);

	ASSERT (get_local_entity_type (sender) == ENTITY_TYPE_WAYPOINT);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	#if DEBUG_MODULE >= 2

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	raw = (mobile *) get_local_entity_data (receiver);

	group = get_local_entity_parent (receiver, LIST_TYPE_MEMBER);

	task = get_local_entity_parent (sender, LIST_TYPE_WAYPOINT);

	ASSERT (task->type == ENTITY_TYPE_TASK);

	//
	// Clear position hold flags
	//

	mb = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

	while (mb)
	{
		if (get_local_entity_int_value (mb, INT_TYPE_POSITION_HOLD))
		{
			set_client_server_entity_int_value (mb, INT_TYPE_POSITION_HOLD, FALSE);
		}

		mb = get_local_entity_child_succ (mb, LIST_TYPE_MEMBER);
	}

	//

	keysite = (entity *) get_local_entity_parent (sender, LIST_TYPE_TASK_DEPENDENT);

	ASSERT (keysite);

	landing = get_local_entity_landing_entity (keysite, group_database [get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE)].default_landing_type);

	ASSERT (landing);

	if ((get_local_entity_int_value (keysite, INT_TYPE_IN_USE)) && (get_local_entity_int_value (keysite, INT_TYPE_SIDE) == get_local_entity_int_value (group, INT_TYPE_SIDE)))
	{

		//
		// terminate land task
		//

		notify_local_entity (ENTITY_MESSAGE_TASK_TERMINATED, task, receiver, TASK_TERMINATED_WAYPOINT_ROUTE_COMPLETE);

		//
		// request landing site
		//

		notify_local_entity (ENTITY_MESSAGE_LANDING_SITE_REQUEST, landing, receiver);

		//
		// Abort all engage tasks
		//

		terminate_all_engage_tasks (group);

		//
		// Stop group from engaging
		//

		set_local_entity_int_value (group, INT_TYPE_ENGAGE_ENEMY, FALSE);

		/////////////////////////////////////////////////////////////////
		//
		// SPECIAL_EFFECT_HOOK FOR REQUESTING TO LAND
		//
		/////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////
		//
		// 
		//
		/////////////////////////////////////////////////////////////////
	}
	else
	{

		/////////////////////////////////////////////////////////////////
		//
		// SPECIAL_EFFECT_HOOK FOR REACHING AIRBASE AND FINDING IT DESTROYED / CAPTURED
		//
		/////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////
		//
		// 
		//
		/////////////////////////////////////////////////////////////////

		debug_log ("MB_MSGS: %s (%d) reached land waypoint but keysite has been destroyed", get_local_entity_string (receiver, STRING_TYPE_FULL_NAME), get_local_entity_index (receiver));

		// destroy old task

		notify_local_entity (ENTITY_MESSAGE_TASK_TERMINATED, task, receiver, TASK_TERMINATED_WAYPOINT_ROUTE_COMPLETE);

		// create transfer task to new keysite

		if (create_group_emergency_transfer_task (group))
		{
			new_task = get_local_group_primary_task (group);
	
			new_keysite = (entity *) get_local_entity_ptr_value (new_task, PTR_TYPE_RETURN_KEYSITE);
	
			new_landing = get_local_entity_landing_entity (new_keysite, group_database [get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE)].default_landing_type);
	
			// unreserver landing site and reserver new ones
	
			mb = get_local_entity_first_child (group, LIST_TYPE_MEMBER);
	
			while (mb)
			{
	
				notify_local_entity (ENTITY_MESSAGE_UNRESERVE_LANDING_SITE, landing, mb, 1);
	
				notify_local_entity (ENTITY_MESSAGE_RESERVE_LANDING_SITE, new_landing, mb, 1);
	
				debug_log ("MB_MSGS:    %s (%d) unreserving landing place at keysite %s (%d) (landing %d) and reserving at keysite %s (%d) (landing %d)",
								get_local_entity_string (mb, STRING_TYPE_FULL_NAME),
								get_local_entity_index (mb),
								get_local_entity_string (keysite, STRING_TYPE_FULL_NAME),
								get_local_entity_index (keysite),
								get_local_entity_index (landing),
								get_local_entity_string (new_keysite, STRING_TYPE_FULL_NAME),
								get_local_entity_index (new_keysite),
								get_local_entity_index (new_landing));
	
				mb = get_local_entity_child_succ (mb, LIST_TYPE_MEMBER);
			}
		}
	}

	set_local_entity_float_value (receiver, FLOAT_TYPE_VIEW_INTEREST_LEVEL, DEFAULT_VIEW_INTEREST_LEVEL);

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_waypoint_landed_reached (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	float
		sleep;
		//fuel,
		//ammo;

	entity
		*task,
		*group,
		*guide,
		*keysite,
		*landing_en,
		*donar_group;

	mobile
		*raw;

	ASSERT (sender);

	ASSERT (get_local_entity_type (sender) == ENTITY_TYPE_WAYPOINT);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	#if DEBUG_MODULE >= 2

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	raw = (mobile *) get_local_entity_data (receiver);

	//
	// Notify end task
	//

	guide = get_local_entity_parent (receiver, LIST_TYPE_FOLLOWER);

	task = get_local_entity_parent (guide, LIST_TYPE_GUIDE);

	group = get_local_entity_parent (receiver, LIST_TYPE_MEMBER);

	landing_en = get_local_entity_parent (task, LIST_TYPE_ASSIGNED_TASK);

	/////////////////////////////////////////////////////////////////
	//
	// destroy guide entity (thus removing member from task)
	//
	/////////////////////////////////////////////////////////////////

	destroy_client_server_entity (guide);

	/////////////////////////////////////////////////////////////////
	//
	// Set mobile to landed
	//
	/////////////////////////////////////////////////////////////////
	
	if (!get_local_entity_int_value (receiver, INT_TYPE_LANDED))
	{

		set_client_server_entity_int_value (receiver, INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_LANDED);
	}

	notify_local_entity (ENTITY_MESSAGE_TASK_TERMINATED, landing_en, receiver, TASK_TERMINATED_WAYPOINT_ROUTE_COMPLETE);

	/////////////////////////////////////////////////////////////////
	//
	// Refuel / Re-arm / Repair
	//
	/////////////////////////////////////////////////////////////////

	ASSERT (landing_en->type == ENTITY_TYPE_LANDING);

	keysite = get_local_entity_parent (landing_en, LIST_TYPE_LANDING_SITE);

	ASSERT (keysite);

	if ((get_local_entity_int_value (receiver, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI) &&
		(get_local_entity_int_value (group, INT_TYPE_RESUPPLY_SOURCE) == RESUPPLY_SOURCE_KEYSITE))
	{

		float
			fuel,
			ammo;

		weapon_config_types
			config_type;

		//
		// fuel
		//
	
		fuel = get_local_entity_float_value (group, FLOAT_TYPE_FUEL_SUPPLY_LEVEL);

		fuel -= get_local_entity_float_value (receiver, FLOAT_TYPE_FUEL_ECONOMY) * FUEL_USAGE_ACCELERATOR;

		fuel = bound (fuel, 0.0, 100.0);

		set_client_server_entity_float_value (group, FLOAT_TYPE_FUEL_SUPPLY_LEVEL, fuel);

		set_client_server_entity_float_value (receiver, FLOAT_TYPE_FUEL_SUPPLY_LEVEL, get_local_entity_float_value (receiver, FLOAT_TYPE_FUEL_DEFAULT_WEIGHT));
	
		//
		// ammo
		//
	
		config_type = (weapon_config_types) get_local_entity_int_value (receiver, INT_TYPE_WEAPON_CONFIG_TYPE);
	
		if (config_type == WEAPON_CONFIG_TYPE_UNARMED)
		{
	
			config_type = (weapon_config_types) get_local_entity_int_value (receiver, INT_TYPE_DEFAULT_WEAPON_CONFIG_TYPE);
		}
	
		set_client_server_entity_int_value (receiver, INT_TYPE_WEAPON_CONFIG_TYPE, config_type);

		ammo = get_local_entity_float_value (group, FLOAT_TYPE_AMMO_SUPPLY_LEVEL);

		ammo -= get_local_entity_float_value (receiver, FLOAT_TYPE_AMMO_ECONOMY) * AMMO_USAGE_ACCELERATOR;

		ammo = bound (ammo, 0.0, 100.0);

		set_client_server_entity_float_value (group, FLOAT_TYPE_AMMO_SUPPLY_LEVEL, ammo);

		//
		// sleep
		//

		sleep = get_local_entity_rearming_sleep_time (group);
		sleep += get_local_entity_refueling_sleep_time (group);

		//sleep = ONE_MINUTE * ((-0.02 * (ammo + fuel)) + 5.0);
		set_client_server_entity_float_value (receiver, FLOAT_TYPE_SLEEP, sleep);

		#if DEBUG_MODULE || DEBUG_SUPPLY

		debug_log ("MB_MSGS: SUPPLY_INFO: member %s (%d) landed and refuelled/rearmed at %s (%d). Group supplies now ammo = %f, fuel = %f, sleeping for %f",
						get_local_entity_string (receiver, STRING_TYPE_FULL_NAME),
						get_local_entity_index (receiver),
						get_local_entity_string (keysite, STRING_TYPE_FULL_NAME),
						get_local_entity_index (keysite),
						get_local_entity_float_value (group, FLOAT_TYPE_AMMO_SUPPLY_LEVEL),
						get_local_entity_float_value (group, FLOAT_TYPE_FUEL_SUPPLY_LEVEL),
						sleep);

		#endif

		assess_group_supplies (group);
	}

	/////////////////////////////////////////////////////////////////
	//
	// repair
	//
	/////////////////////////////////////////////////////////////////

	set_client_server_entity_int_value (receiver, INT_TYPE_DAMAGE_LEVEL, get_local_entity_int_value (receiver, INT_TYPE_INITIAL_DAMAGE_LEVEL));

	/////////////////////////////////////////////////////////////////
	//
	// re-sync positions on clients machines
	//
	/////////////////////////////////////////////////////////////////

	set_client_server_entity_vec3d (receiver, VEC3D_TYPE_POSITION, get_local_entity_vec3d_ptr (receiver, VEC3D_TYPE_POSITION));

	/////////////////////////////////////////////////////////////////
	//
	// Link into MOVEMENT_DEPENDENT list (if on mobile_keysite)
	//
	/////////////////////////////////////////////////////////////////

	if ((receiver != get_local_entity_parent (keysite, LIST_TYPE_MOVEMENT_DEPENDENT)) && (get_local_entity_parent (keysite, LIST_TYPE_MOVEMENT_DEPENDENT)))
	{

		insert_local_entity_into_parents_child_list (receiver, LIST_TYPE_MOVEMENT_DEPENDENT, get_local_entity_parent (keysite, LIST_TYPE_MOVEMENT_DEPENDENT), NULL);
	}

	/////////////////////////////////////////////////////////////////
	//
	// Amalgamate groups
	//
	/////////////////////////////////////////////////////////////////

	group = get_local_entity_parent (receiver, LIST_TYPE_MEMBER);

	if (get_local_entity_int_value (group, INT_TYPE_GROUP_MODE) == GROUP_MODE_IDLE)
	{
		if (get_local_entity_int_value (group, INT_TYPE_GROUP_AMALGAMATE))
		{
			//
			// only amalgamate group if all members landed
			//

			donar_group = get_local_entity_first_child (keysite, LIST_TYPE_KEYSITE_GROUP);

			while (donar_group)
			{

				if (donar_group != group)
				{
		
					if (get_local_entity_int_value (donar_group, INT_TYPE_GROUP_MODE) == GROUP_MODE_IDLE)
					{

						if (get_local_entity_int_value (donar_group, INT_TYPE_GROUP_AMALGAMATE))
						{

							if (amalgamate_groups (group, donar_group))
							{
		
								donar_group = NULL;
	
								break;
							}
						}
					}
				}

				donar_group = get_local_entity_child_succ (donar_group, LIST_TYPE_KEYSITE_GROUP);
			}
		}
	}

	/////////////////////////////////////////////////////////////////
	//
	// SPECIAL_EFFECT_HOOK FOR LANDED
	//
	/////////////////////////////////////////////////////////////////

	set_infinite_smoke_list_generating_state (receiver, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_VEHICLE_WAKE, INFINITE_SMOKE_OFF);

	if (get_local_entity_int_value (receiver, INT_TYPE_IDENTIFY_VEHICLE))
	{
		if (get_local_entity_int_value (receiver, INT_TYPE_LIGHTS_ON))
		{
			set_vehicle_headlight_state (receiver, OFF);
		}
	}

	open_client_server_entity_loading_doors (receiver);

	open_client_server_entity_cargo_doors (receiver);

	/////////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////////

	set_local_entity_float_value (receiver, FLOAT_TYPE_VIEW_INTEREST_LEVEL, DEFAULT_VIEW_INTEREST_LEVEL);

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_waypoint_loop_reached (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	entity
		*wp,
		*task,
		*guide;

	ASSERT (sender);

	ASSERT (get_local_entity_type (sender) == ENTITY_TYPE_WAYPOINT);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	#if DEBUG_MODULE >= 2

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	//
	// delete mobile from current waypoint and insert on first wp
	//

	task = get_local_entity_parent (sender, LIST_TYPE_WAYPOINT);

	if (get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_TASK_TAKEOFF_HOLDING)
	{
		//
		// Needed in case a member was killed during takeoff, or other such problems which might occur 
		//
		
		mobile_check_all_members_taken_off (receiver);
	}
	else
	{
		wp = get_local_entity_first_child (task, LIST_TYPE_WAYPOINT);
	
		guide = get_local_entity_parent (receiver, LIST_TYPE_FOLLOWER);
	
		set_guide_new_waypoint (guide, wp);
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_waypoint_navigation_reached (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	ASSERT (sender);

	ASSERT (get_local_entity_type (sender) == ENTITY_TYPE_WAYPOINT);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	#if DEBUG_MODULE >= 2

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	set_local_entity_float_value (receiver, FLOAT_TYPE_VIEW_INTEREST_LEVEL, DEFAULT_VIEW_INTEREST_LEVEL);

	/////////////////////////////////////////////////////////////////
	//
	// SPECIAL_EFFECT_HOOK FOR WAYPOINT REACHED
	//
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////////

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_waypoint_sub_route_navigation_reached (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	int
		count,
		from_node,
		to_node;

	node_link_data
		*sub_route_node;

	entity
		*mb,
		*group,
		*succ_wp;

	ASSERT (sender);

	ASSERT (get_local_entity_type (sender) == ENTITY_TYPE_WAYPOINT);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	#if DEBUG_MODULE >= 2

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	if (get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE) == DAY_SEGMENT_TYPE_NIGHT)
	{
		if (!get_local_entity_int_value (receiver, INT_TYPE_LIGHTS_ON))
		{
			set_vehicle_headlight_state (receiver, ON);
		}
	}
	else
	{
		if (get_local_entity_int_value (receiver, INT_TYPE_LIGHTS_ON))
		{
			set_vehicle_headlight_state (receiver, OFF);
		}
	}

	//
	// Setup sub_route points. NB: ONLY the leader does this
	//

	#if DEBUG_MODULE

	debug_log ("MB_MSGS: sub_route navigation waypoint reached by %s (%d)",
					get_local_entity_string (receiver, STRING_TYPE_FULL_NAME),
					get_local_entity_index (receiver),
					get_local_entity_int_value (sender, INT_TYPE_ROUTE_NODE));

	#endif

	succ_wp = get_local_entity_child_succ (sender, LIST_TYPE_WAYPOINT);

	from_node = get_local_entity_int_value (sender, INT_TYPE_ROUTE_NODE);

	#if DEBUG_MODULE

	debug_log ("MB_MSGS: travelling from node %d", from_node);

	#endif

	if (succ_wp)
	{

		to_node = get_local_entity_int_value (succ_wp, INT_TYPE_ROUTE_NODE);

		#if DEBUG_MODULE

		debug_log ("MB_MSGS: travelling to node %d", to_node);

		#endif

		sub_route_node = get_road_sub_route (from_node, to_node, &count, NULL);

		if (sub_route_node)
		{
			group = get_local_entity_parent (receiver, LIST_TYPE_MEMBER);

			mb = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

			while (mb)
			{

				routed_vehicle
					*raw;

				raw = (routed_vehicle *) get_local_entity_data (mb);

				set_local_entity_int_value (mb, INT_TYPE_WAYPOINT_NEXT_INDEX, to_node);
				set_local_entity_int_value (mb, INT_TYPE_WAYPOINT_THIS_INDEX, from_node);
				set_local_entity_int_value (mb, INT_TYPE_SUB_WAYPOINT_COUNT, count);
				raw->sub_route = sub_route_node;

				#if DEBUG_MODULE

				debug_log ("MB_MSGS: SET-UP sub_route for leader entity %s, %d between %d and %d",
						get_local_entity_string (mb, STRING_TYPE_FULL_NAME),
						get_local_entity_index (mb),
						from_node,
						to_node);

				#endif

				mb = get_local_entity_child_succ (mb, LIST_TYPE_MEMBER);
			}

			mb = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

			transmit_entity_comms_message (ENTITY_COMMS_ROUTED_VEHICLE_ROUTE_DATA, mb, from_node, to_node);
		}
		else
		{

			debug_log ("MB_MSGS: ERROR, no route found betweek road nodes %d and %d.", from_node, to_node);
		}
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_waypoint_prepare_for_drop_off_reached (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	entity
		*mb,
		*group;

	ASSERT (sender);

	ASSERT (get_local_entity_type (sender) == ENTITY_TYPE_WAYPOINT);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	#if DEBUG_MODULE >= 2

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	/////////////////////////////////////////////////////////////////
	//
	// SPECIAL_EFFECT_HOOK FOR PREPARE_FOR_DROP_OFF WAYPOINT REACHED
	//
	/////////////////////////////////////////////////////////////////

	group = get_local_entity_parent (receiver, LIST_TYPE_MEMBER);

	mb = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

	while (mb)
	{
		open_client_server_entity_cargo_doors (mb);

		if (get_local_entity_weapon_available (mb, ENTITY_SUB_TYPE_WEAPON_CRATE))
		{
	
			set_client_server_entity_int_value (mb, INT_TYPE_SELECTED_WEAPON, ENTITY_SUB_TYPE_WEAPON_CRATE);

			#if DEBUG_MODULE
	
			debug_log ("MB_MSGS: %s (%d) reached prepare_for_drop_off, selecting crate_weapon", get_local_entity_string (mb, STRING_TYPE_FULL_NAME), get_local_entity_index (mb));

			#endif
		}
	
		mb = get_local_entity_child_succ (mb, LIST_TYPE_MEMBER);
	}

	/////////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////////

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_waypoint_pick_up_reached (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	entity
		*keysite,
		*cargo;

	ASSERT (sender);

	ASSERT (get_local_entity_type (sender) == ENTITY_TYPE_WAYPOINT);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	#if DEBUG_MODULE >= 2

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	keysite = get_local_entity_parent (sender, LIST_TYPE_TASK_DEPENDENT);

	cargo = get_local_entity_first_child (keysite, LIST_TYPE_CARGO);

	while ((cargo) && (get_local_entity_type (cargo) != ENTITY_TYPE_CARGO))
	{

		cargo = get_local_entity_child_succ (cargo, LIST_TYPE_CARGO);
	}

	if (!cargo)
	{

		return (TRUE);
	}

	notify_local_entity (ENTITY_MESSAGE_WAYPOINT_PICK_UP_REACHED, keysite, receiver, cargo);

	delete_local_entity_from_parents_child_list (cargo, LIST_TYPE_CARGO);

	insert_local_entity_into_parents_child_list (cargo, LIST_TYPE_MOVEMENT_DEPENDENT, receiver, NULL);

	transmit_entity_comms_message (ENTITY_COMMS_SWITCH_LIST, cargo, LIST_TYPE_CARGO, receiver, LIST_TYPE_MOVEMENT_DEPENDENT);

	//
	//
	//

	if (get_local_entity_int_value (receiver, INT_TYPE_OPERATIONAL_STATE) != OPERATIONAL_STATE_NAVIGATING)
	{

		set_client_server_entity_int_value (receiver, INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_NAVIGATING);
	}

	set_local_entity_float_value (receiver, FLOAT_TYPE_VIEW_INTEREST_LEVEL, DEFAULT_VIEW_INTEREST_LEVEL);

	#if DEBUG_MODULE

	debug_log ("MB_MSGS: inserting cargo %s into %s movement_dependent list", entity_sub_type_cargo_names [get_local_entity_int_value (cargo, INT_TYPE_ENTITY_SUB_TYPE)], entity_type_names [get_local_entity_type (receiver)]);

	#endif

	/////////////////////////////////////////////////////////////////
	//
	// SPECIAL_EFFECT_HOOK FOR PICKUP WAYPOINT REACHED
	//
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////////

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_waypoint_recon_action (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	ASSERT (sender);

	ASSERT (sender->type == ENTITY_TYPE_WAYPOINT);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	#if DEBUG_MODULE >= 2

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	if (get_local_entity_int_value (receiver, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI)
	{
		notify_local_entity (ENTITY_MESSAGE_WAYPOINT_RECON_REACHED, receiver, sender);
	}
	else
	{
		//
		// tell player to transmit recon
		//

		play_client_server_cpg_message (receiver, 1.0, 30.0, SPEECH_CATEGORY_MISSION_RELATED, -1.0, SPEECH_CPG_OBJECTIVE_IN_RANGE_RECON);

		if (receiver == get_gunship_entity ())
		{
			set_status_message (get_trans ("ADVISE_TRANSMIT_RECON"), STATUS_MESSAGE_TYPE_ALERT);
		}
		else
		{
			transmit_entity_comms_message (ENTITY_COMMS_ADVISE_TRANSMIT_RECON, receiver);
		}
	}

	/////////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////////

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_waypoint_recon_reached (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	int
		side;

	entity
		*task;

	ASSERT (sender);

	ASSERT (sender->type == ENTITY_TYPE_WAYPOINT);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	#if DEBUG_MODULE >= 2

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	side = get_local_entity_int_value (receiver, INT_TYPE_SIDE);

	//
	// Nofity task of task_complete
	//

	task = get_local_entity_parent (sender, LIST_TYPE_WAYPOINT);

	notify_local_entity (ENTITY_MESSAGE_TASK_COMPLETED, task, receiver, TASK_TERMINATED_OBJECTIVE_MESSAGE);

	set_local_entity_float_value (receiver, FLOAT_TYPE_VIEW_INTEREST_LEVEL, DEFAULT_VIEW_INTEREST_LEVEL);

	/////////////////////////////////////////////////////////////////
	//
	// SPECIAL_EFFECT_HOOK FOR RECON WAYPOINT REACHED
	//
	/////////////////////////////////////////////////////////////////

	if (get_local_entity_int_value (receiver, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI)
	{
		play_client_server_wingman_message
		(
			receiver,
			1.0,
			20.0,
			SPEECH_CATEGORY_MISSION_RELATED, -1.0,
			SPEECH_INTRODUCTION_ALWAYS,
			SPEECH_ARRAY_WINGMAN_MESSAGES, SPEECH_WINGMAN_TRANSMITTING_RECON_DATA
		);
	}
	else
	{
		play_client_server_cpg_message (receiver, 0.8, 30.0, SPEECH_CATEGORY_MISSION_RELATED, -1.0, SPEECH_CPG_TRANSMITTING_RECON);
	}

	/////////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////////

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_waypoint_repair_reached (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	entity
		*task,
		*objective;

	ASSERT (sender);

	ASSERT (sender->type == ENTITY_TYPE_WAYPOINT);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	debug_log ("MB_MSGS: repair waypoint reached by %s", get_local_entity_string (receiver, STRING_TYPE_FULL_NAME));

	task = get_local_entity_parent (sender, LIST_TYPE_WAYPOINT);

	ASSERT (task);

	objective = get_local_entity_parent (task, LIST_TYPE_TASK_DEPENDENT);

	switch (get_local_entity_type (objective))
	{
		case ENTITY_TYPE_BRIDGE:
		{
			repair_client_server_bridge_entity (objective);

			break;
		}
		case ENTITY_TYPE_KEYSITE:
		{
			set_client_server_entity_int_value (objective, INT_TYPE_KEYSITE_USABLE_STATE, KEYSITE_STATE_REPAIRING);

			break;
		}
	}

	//
	// Nofity task of task_complete
	//

	notify_local_entity (ENTITY_MESSAGE_TASK_COMPLETED, task, receiver, TASK_TERMINATED_OBJECTIVE_MESSAGE);

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_waypoint_taken_off_reached (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	entity
		*landing_en,
		*member,
		*group;

	mobile
		*raw;

	ASSERT (sender);

	ASSERT (sender->type == ENTITY_TYPE_WAYPOINT);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	#if DEBUG_MODULE >= 2

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	raw = (mobile *) get_local_entity_data (receiver);

	landing_en = get_local_group_member_landing_entity_from_task (receiver);

	group = get_local_entity_parent (receiver, LIST_TYPE_MEMBER);

	member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

	//
	// Unlock takeoff route
	//

	notify_local_entity (ENTITY_MESSAGE_WAYPOINT_TAKEN_OFF_REACHED, landing_en, receiver);

	//
	// Operational states
	//

	set_client_server_entity_int_value (receiver, INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_TAKEOFF_HOLDING);

	/////////////////////////////////////////////////////////////////
	//
	// SPECIAL_EFFECT_HOOK FOR ENTERING HOLDING PATTERN
	//
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////////

	//
	// Have all members taken off ?
	//

	mobile_check_all_members_taken_off (receiver);

	/////////////////////////////////////////////////////////////////
	//
	// SPECIAL_EFFECT_HOOK FOR COMPLETED TAKEOFF 
	//
	/////////////////////////////////////////////////////////////////

	set_local_entity_float_value (receiver, FLOAT_TYPE_VIEW_INTEREST_LEVEL, DEFAULT_VIEW_INTEREST_LEVEL);

	if (get_local_entity_type (receiver) == ENTITY_TYPE_FIXED_WING)
	{
		set_client_server_fixed_wing_afterburner_state (receiver, OFF);

		close_client_server_entity_flaps (receiver);
	}
	else if (get_local_entity_type (receiver) == ENTITY_TYPE_ROUTED_VEHICLE)
	{

		// set the formation numbers of the group to make the leader formation position 0
		// stopping RV's driving on top of each other

		set_client_server_entity_int_value (receiver, INT_TYPE_FORMATION_POSITION, get_local_entity_int_value (receiver, INT_TYPE_GROUP_MEMBER_NUMBER));
	}

	/////////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////////

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_waypoint_taxi_reached (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	ASSERT (sender);

	ASSERT (sender->type == ENTITY_TYPE_WAYPOINT);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	#if DEBUG_MODULE >= 2

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	close_client_server_entity_airbrakes (receiver);

	set_local_entity_float_value (receiver, FLOAT_TYPE_VIEW_INTEREST_LEVEL, DEFAULT_VIEW_INTEREST_LEVEL);

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_waypoint_troop_capture_reached (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	entity
		*task,
		*group,
		*troop_insertion_task,
		*destination_keysite;

	int
		side,
		keysite_type;

	float
		d,
		r,
		member_count,
		losses,
		efficiency,
		minimum;

	ASSERT (sender);

	ASSERT (get_local_entity_type (sender) == ENTITY_TYPE_WAYPOINT);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	group = get_local_entity_parent (receiver, LIST_TYPE_MEMBER);

	task = get_local_entity_parent (sender, LIST_TYPE_WAYPOINT);

	ASSERT (task);

	troop_insertion_task = get_local_entity_parent (task, LIST_TYPE_TASK_DEPENDENT);

	ASSERT (troop_insertion_task);

	if (!troop_insertion_task)
	{
		return FALSE;
	}

	ASSERT (get_local_entity_int_value (troop_insertion_task, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_TASK_TROOP_INSERTION);

	destination_keysite = get_local_entity_parent (troop_insertion_task, LIST_TYPE_TASK_DEPENDENT);

	ASSERT (destination_keysite);

	if (!destination_keysite)
	{
		return FALSE;
	}

	keysite_type = get_local_entity_int_value (destination_keysite, INT_TYPE_ENTITY_SUB_TYPE);

	side = get_local_entity_int_value (group, INT_TYPE_SIDE);

	if (side != get_local_entity_int_value (destination_keysite, INT_TYPE_SIDE))
	{
		if (keysite_database [keysite_type].ground_strike_target)
		{
			//
			// Chance of capturing keysite dependent upon efficiency
			//
	
			efficiency = get_local_entity_float_value (destination_keysite, FLOAT_TYPE_EFFICIENCY);
			
			minimum = get_local_entity_float_value (destination_keysite, FLOAT_TYPE_MINIMUM_EFFICIENCY);
	
			d = (efficiency - minimum) / (1.0 - minimum);
	
			//
			// And how many of the troops have been killed
			//
	
			member_count = (float)get_local_entity_int_value (group, INT_TYPE_MEMBER_COUNT);
	
			losses = (float)get_local_entity_int_value (group, INT_TYPE_LOSSES);
	
			d *= (member_count / (member_count + losses));
	
			r = frand1 ();
	
			debug_log ("MB_MSGS: Trying to capture %s", get_local_entity_string (destination_keysite, STRING_TYPE_KEYSITE_NAME));
			debug_log ("MB_MSGS: Efficiency %f - Minimum %f", efficiency, minimum);
			debug_log ("MB_MSGS: Probability %f : %f", d, r);
	
			if (d < r) 
			{
				capture_keysite (destination_keysite, (entity_sides) side);
			}
		}
		else
		{
			//
			// Efficiency not applicable
			//
			
			capture_keysite (destination_keysite, (entity_sides) side);
		}
	}

	notify_local_entity (ENTITY_MESSAGE_TASK_TERMINATED, task, receiver, TASK_TERMINATED_WAYPOINT_ROUTE_COMPLETE);

	group_destroy_all_members (group);

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_waypoint_troop_defend_reached (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	entity
		*task,
		*group;

	ASSERT (sender);

	ASSERT (get_local_entity_type (sender) == ENTITY_TYPE_WAYPOINT);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	group = get_local_entity_parent (receiver, LIST_TYPE_MEMBER);

	task = get_local_entity_parent (sender, LIST_TYPE_WAYPOINT);

	notify_local_entity (ENTITY_MESSAGE_TASK_TERMINATED, task, receiver, TASK_TERMINATED_WAYPOINT_ROUTE_COMPLETE);

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_waypoint_troop_insert_reached (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	vec3d
		start_pos;

	entity
		*group,
		*keysite,
		*new_task,
		*insert_task;

	entity_sides
		side;

	ASSERT (sender);

	ASSERT (get_local_entity_type (sender) == ENTITY_TYPE_WAYPOINT);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	#if DEBUG_MODULE >= 2

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	group = get_local_entity_parent (receiver, LIST_TYPE_MEMBER);

	insert_task = get_local_group_primary_task (group);

	keysite = get_local_entity_parent (insert_task, LIST_TYPE_TASK_DEPENDENT);

	side = (entity_sides) get_local_entity_int_value (receiver, INT_TYPE_SIDE);

	//
	// Open Leader's Doors
	//
	
	open_client_server_entity_loading_doors (receiver);
  
  //ataribaby 31/12/2008 fix for player heli
  if (receiver != get_gunship_entity ())
	 lower_client_server_entity_undercarriage (receiver);

	//
	// Create a troop group for leader only
	//

	// work out troop task positions

	get_local_entity_vec3d (receiver, VEC3D_TYPE_POSITION, &start_pos);

	start_pos.y -= get_local_entity_float_value (receiver, FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE);

	//
	// create person
	//

	group = create_faction_members (keysite,
												ENTITY_SUB_TYPE_GROUP_INFANTRY,
												FORMATION_COMPONENT_INFANTRY,
												8,
												side,
												&start_pos,
												TRUE,
												FALSE);

	if (group)
	{
		add_group_to_division (group, NULL);

		new_task = create_troop_movement_capture_task (side, &start_pos, insert_task, keysite, receiver);

		// assign task
	
		if (new_task)
		{
			if (!assign_task_to_group (group, new_task, TASK_ASSIGN_ALL_MEMBERS))
			{
				#ifdef DEBUG

				breakout (NULL);

				assign_task_to_group (group, new_task, TASK_ASSIGN_ALL_MEMBERS);

				debug_fatal ("MB_MSGS: can't assign person to its task");

				#endif
			}
			else
			{
				entity
					*mb;

				float
					sleep;

				mb = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

				sleep = 0.0;
		
				while (mb)
				{
					sleep += 0.5;
				
					// delay members to stagger their decend out of the helicopter
					set_client_server_entity_float_value (mb, FLOAT_TYPE_SLEEP, sleep);

					// get them inside the helicopter
					set_client_server_entity_vec3d (mb, VEC3D_TYPE_POSITION, &start_pos);
		
					mb = get_local_entity_child_succ (mb, LIST_TYPE_MEMBER);
				}
			}
		}
	
		/////////////////////////////////////////////////////////////////
		//
		// SPECIAL_EFFECT_HOOK FOR TROOP INSERT REACHED
		//
		/////////////////////////////////////////////////////////////////
	
		/////////////////////////////////////////////////////////////////
		//
		//
		/////////////////////////////////////////////////////////////////
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_waypoint_troop_putdown_point_reached (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	entity
		*group,
		*task,
		*insert_task;

	ASSERT (sender);

	ASSERT (get_local_entity_type (sender) == ENTITY_TYPE_WAYPOINT);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	//
	// tell insertion mission its complete
	//

	group = get_local_entity_parent (receiver, LIST_TYPE_MEMBER);

	task = get_local_entity_parent (sender, LIST_TYPE_WAYPOINT);

	insert_task = get_local_entity_parent (task, LIST_TYPE_TASK_DEPENDENT);

	ASSERT (insert_task);

	notify_local_entity (ENTITY_MESSAGE_TASK_COMPLETED, insert_task, group, TASK_TERMINATED_OBJECTIVE_MESSAGE);

	//
	// Close Flight Leader's Doors
	//
	{
		entity
			*guide,
			*leader;

		guide = get_local_entity_first_child (insert_task, LIST_TYPE_GUIDE);

		if (guide)
		{
			leader = (entity *) get_local_entity_ptr_value (guide, PTR_TYPE_TASK_LEADER);

			if (leader)
			{
				close_client_server_entity_loading_doors (leader);
        
        //ataribaby 31/12/2008 fix for player heli
        if (leader != get_gunship_entity ())
				  raise_client_server_entity_undercarriage (leader);
			}
		}
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_waypoint_troop_pickup_point_end_reached (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	int
		count;

	entity
		*mb,
		*task,
		*guide,
		*group,
		*destroy_mb,
		*extract_task;

	ASSERT (sender);

	ASSERT (get_local_entity_type (sender) == ENTITY_TYPE_WAYPOINT);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	//
	// tell extraction mission its complete if this is the last Troop_pickup_movement task.
	// i.e there may be more than one Troop_pickup_movement task attached to this flight group
	//

	group = get_local_entity_parent (receiver, LIST_TYPE_MEMBER);

	task = get_local_entity_parent (sender, LIST_TYPE_WAYPOINT);

	extract_task = get_local_entity_parent (task, LIST_TYPE_TASK_DEPENDENT);

	task = get_local_entity_first_child (extract_task, LIST_TYPE_TASK_DEPENDENT);

	count = 0;

	while (task)
	{

		count ++;

		task = get_local_entity_child_succ (task, LIST_TYPE_TASK_DEPENDENT);
	}

	if (count <= 1)
	{

		guide = get_local_entity_first_child (extract_task, LIST_TYPE_GUIDE);

		set_guide_next_waypoint (guide);

		//notify_local_entity (ENTITY_MESSAGE_TASK_COMPLETED, extract_task, group, TASK_TERMINATED_OBJECTIVE_MESSAGE);
	}

	//
	// now destroy troops
	//

	#if DEBUG_MODULE

	debug_log ("MB_MSGS: Troop pickup point reached destroying troops");

	#endif

	mb = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

	while (mb)
	{

		destroy_mb = mb;

		mb = get_local_entity_child_succ (mb, LIST_TYPE_MEMBER);

		destroy_client_server_entity (destroy_mb);
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_waypoint_troop_pickup_point_start_reached (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	entity
		*group,
		*mb;

	float
		sleep;

	ASSERT (sender);

	ASSERT (get_local_entity_type (sender) == ENTITY_TYPE_WAYPOINT);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	debug_log ("MB_MSGS: pickup point start reached");

	group = get_local_entity_parent (receiver, LIST_TYPE_MEMBER);

	mb = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

	sleep = 0.0;

	while (mb)
	{

		sleep += 2.0;
	
		// delay members to stagger their accent into the helicopter
		set_client_server_entity_float_value (mb, FLOAT_TYPE_SLEEP, sleep);

		mb = get_local_entity_child_succ (mb, LIST_TYPE_MEMBER);
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_mobile_message_responses (entity_types type)
{
	#if DEBUG_MODULE >= 2

	message_responses[type][ENTITY_MESSAGE_LINK_CHILD] 										= response_to_link_child;

	message_responses[type][ENTITY_MESSAGE_UNLINK_CHILD]										= response_to_unlink_child;

	message_responses[type][ENTITY_MESSAGE_LINK_PARENT]										= response_to_link_parent;

	message_responses[type][ENTITY_MESSAGE_UNLINK_PARENT]										= response_to_unlink_parent;

	#endif

	message_responses[type][ENTITY_MESSAGE_TASK_ASSIGNED]										= response_to_task_assigned;

	message_responses[type][ENTITY_MESSAGE_WAYPOINT_APPROACH_REACHED]						= response_to_waypoint_approach_reached;

	message_responses[type][ENTITY_MESSAGE_WAYPOINT_ATTACK_ACTION]							= response_to_waypoint_attack_action;

	message_responses[type][ENTITY_MESSAGE_WAYPOINT_CONVOY_REACHED]						= response_to_waypoint_convoy_reached;

	message_responses[type][ENTITY_MESSAGE_WAYPOINT_DEFEND_REACHED]						= response_to_waypoint_defend_reached;

	message_responses[type][ENTITY_MESSAGE_WAYPOINT_DROP_OFF_REACHED]						= response_to_waypoint_drop_off_reached;

	message_responses[type][ENTITY_MESSAGE_WAYPOINT_FINISH_DROP_OFF_REACHED]			= response_to_waypoint_finish_drop_off_reached;

	message_responses[type][ENTITY_MESSAGE_WAYPOINT_LAND_REACHED]							= response_to_waypoint_land_reached;

	message_responses[type][ENTITY_MESSAGE_WAYPOINT_LANDED_REACHED]						= response_to_waypoint_landed_reached;

	message_responses[type][ENTITY_MESSAGE_WAYPOINT_LOOP_REACHED]							= response_to_waypoint_loop_reached;

	message_responses[type][ENTITY_MESSAGE_WAYPOINT_NAVIGATION_REACHED]					= response_to_waypoint_navigation_reached;

	message_responses[type][ENTITY_MESSAGE_WAYPOINT_SUB_ROUTE_NAVIGATION_REACHED]		= response_to_waypoint_sub_route_navigation_reached;

	message_responses[type][ENTITY_MESSAGE_WAYPOINT_PREPARE_FOR_DROP_OFF_REACHED]		= response_to_waypoint_prepare_for_drop_off_reached;

	message_responses[type][ENTITY_MESSAGE_WAYPOINT_PICK_UP_REACHED]						= response_to_waypoint_pick_up_reached;

	message_responses[type][ENTITY_MESSAGE_WAYPOINT_RECON_ACTION]							= response_to_waypoint_recon_action;

	message_responses[type][ENTITY_MESSAGE_WAYPOINT_RECON_REACHED]							= response_to_waypoint_recon_reached;

	message_responses[type][ENTITY_MESSAGE_WAYPOINT_REPAIR_REACHED]						= response_to_waypoint_repair_reached;

	message_responses[type][ENTITY_MESSAGE_WAYPOINT_TAKEN_OFF_REACHED]					= response_to_waypoint_taken_off_reached;

	message_responses[type][ENTITY_MESSAGE_WAYPOINT_TAXI_REACHED]							= response_to_waypoint_taxi_reached;

	message_responses[type][ENTITY_MESSAGE_WAYPOINT_TROOP_CAPTURE_REACHED]				= response_to_waypoint_troop_capture_reached;

	message_responses[type][ENTITY_MESSAGE_WAYPOINT_TROOP_DEFEND_REACHED]				= response_to_waypoint_troop_defend_reached;

	message_responses[type][ENTITY_MESSAGE_WAYPOINT_TROOP_INSERT_REACHED]				= response_to_waypoint_troop_insert_reached;

	message_responses[type][ENTITY_MESSAGE_WAYPOINT_TROOP_PICKUP_POINT_END_REACHED]	= response_to_waypoint_troop_pickup_point_end_reached;

	message_responses[type][ENTITY_MESSAGE_WAYPOINT_TROOP_PICKUP_POINT_START_REACHED]= response_to_waypoint_troop_pickup_point_start_reached;

	message_responses[type][ENTITY_MESSAGE_WAYPOINT_TROOP_PUTDOWN_POINT_REACHED]		= response_to_waypoint_troop_putdown_point_reached;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



