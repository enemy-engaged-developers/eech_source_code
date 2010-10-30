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
#include "ai/highlevl/highlevl.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 2 levels of debug

#define DEBUG_MODULE 0

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

static int response_to_check_campaign_objectives (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	entity
		*en,
		*group,
		*enemy_force;

	int
		side,
		enemy_side,
		sub_type;

	campaign_completed_types
		complete;

	complete = CAMPAIGN_COMPLETED_FALSE;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	if (get_local_entity_int_value (get_session_entity (), INT_TYPE_SESSION_COMPLETE))
	{
		return TRUE;
	}

	side = get_local_entity_int_value (receiver, INT_TYPE_SIDE);

	enemy_side = get_enemy_side (side);

	enemy_force = get_local_force_entity ((entity_sides) enemy_side);

	ASSERT (enemy_force);

	//
	// Check Keysite Objectives
	//

	complete = CAMPAIGN_COMPLETED_OBJECTIVES;

	en = get_local_entity_first_child (receiver, LIST_TYPE_CAMPAIGN_OBJECTIVE);

	while (en)
	{
		if (get_local_entity_type (en) == ENTITY_TYPE_KEYSITE)
		{
			sub_type = get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);

			if (keysite_database [sub_type].troop_insertion_target)
			{
				if (get_local_entity_int_value (en, INT_TYPE_SIDE) != side)
				{
					complete = CAMPAIGN_COMPLETED_FALSE;

					break;
				}
			}
			else
			{
				if (get_local_entity_int_value (en, INT_TYPE_ALIVE))
				{
					complete = CAMPAIGN_COMPLETED_FALSE;

					break;
				}
			}
		}
		
		en = get_local_entity_child_succ (en, LIST_TYPE_CAMPAIGN_OBJECTIVE);
	}

	if (complete != CAMPAIGN_COMPLETED_FALSE)
	{
		ai_log ("(FORCE) Side %s Completed Keysite Objectives", entity_side_short_names [side]);
	}

	//
	// Check Opposing Forces for Minimum Keysite count
	//

	if (complete == CAMPAIGN_COMPLETED_FALSE)
	{
		complete = CAMPAIGN_COMPLETED_OBJECTIVES;

		en = get_local_entity_first_child (enemy_force, LIST_TYPE_KEYSITE_FORCE);

		while (en)
		{
			sub_type = get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);

			if (keysite_database [sub_type].air_force_capacity != KEYSITE_AIR_FORCE_CAPACITY_NONE)
			{
				if ((get_local_entity_int_value (en, INT_TYPE_ALIVE)) && (get_local_entity_int_value (en, INT_TYPE_IN_USE)))
				{
					complete = CAMPAIGN_COMPLETED_FALSE;

					break;
				}
			}

			en = get_local_entity_child_succ (en, LIST_TYPE_KEYSITE_FORCE);
		}

		if (complete != CAMPAIGN_COMPLETED_FALSE)
		{
			ai_log ("(FORCE) Side %s Has No Keysites Left", entity_side_short_names [enemy_side]);
		}
	}

	//
	// Check Opposing Forces for Player gunships
	//

	if (complete == CAMPAIGN_COMPLETED_FALSE)
	{
		complete = CAMPAIGN_COMPLETED_VALID_GUNSHIPS;

		group = get_local_entity_first_child (enemy_force, LIST_TYPE_AIR_REGISTRY);

		while (group)
		{
			sub_type = get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE);

			if (group_database [sub_type].default_entity_type == ENTITY_TYPE_HELICOPTER)
			{
				en = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

				while (en)
				{
					sub_type = get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);
		
					if (aircraft_database [sub_type].player_controllable)
					{
						switch (sub_type)
						{
							// Casm 16AUG05 Apache is always player-controllable
							case ENTITY_SUB_TYPE_AIRCRAFT_AH64D_APACHE_LONGBOW:
							case ENTITY_SUB_TYPE_AIRCRAFT_RAH66_COMANCHE:
							// Casm 16AUG05 Havoc is always player-controllable
							case ENTITY_SUB_TYPE_AIRCRAFT_MI28N_HAVOC_B:
							case ENTITY_SUB_TYPE_AIRCRAFT_KA52_HOKUM_B:
							{
								complete = CAMPAIGN_COMPLETED_FALSE;

								break;
							}
							// Casm 16AUG05 begin
							// All of the following helos can employ weapons
							// If they are player-controllable player may win
							case ENTITY_SUB_TYPE_AIRCRAFT_UH60_BLACK_HAWK:
							case ENTITY_SUB_TYPE_AIRCRAFT_MI24D_HIND:
							case ENTITY_SUB_TYPE_AIRCRAFT_CH46E_SEA_KNIGHT:
							case ENTITY_SUB_TYPE_AIRCRAFT_KA29_HELIX_B:
							{
								if (aircraft_database[sub_type].player_controllable)
									complete = CAMPAIGN_COMPLETED_FALSE;

								break;
							}
							// Casm 16AUG05 end Thanks to Craigmire!
						}
					}

					en = get_local_entity_child_succ (en, LIST_TYPE_MEMBER);
				}
			}

			if (complete == CAMPAIGN_COMPLETED_FALSE) break;

			group = get_local_entity_child_succ (group, LIST_TYPE_AIR_REGISTRY);
		}

		if (complete != CAMPAIGN_COMPLETED_FALSE)
		{
			ai_log ("(FORCE) Side %s Has No Player Controllable Gunships Left", entity_side_short_names [enemy_side]);
		}
	}

	//
	//
	//
	
	if (complete != CAMPAIGN_COMPLETED_FALSE)
	{
		//
		// THIS FORCE HAS MET ALL CAMPAIGN OBJECTIVES 
		//

		campaign_completed ((entity_sides) side, complete);
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_entity_fired_at (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	entity
		*victim,
		*group;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ASSERT (sender);

	victim = va_arg (pargs, entity *);

	ASSERT (victim);

	if (get_local_entity_int_value (sender, INT_TYPE_ALIVE))
	{
		//
		// Only respond to MOBILE Targets (Keysites are handled elsewhere)
		//
		
		if (get_local_entity_int_value (victim, INT_TYPE_IDENTIFY_MOBILE))
		{
			group = get_local_entity_parent (victim, LIST_TYPE_MEMBER);
	
			if (group)
			{
				notify_local_entity (ENTITY_MESSAGE_ENTITY_FIRED_AT, group, sender, victim);
			}
		}
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_force_armour_advancing (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	#if DEBUG_MODULE
	
	debug_log ("FC_MSGS: allied armour is advancing");

	#endif

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_force_armour_resisting (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	entity
		*enemy_entity;

	if ((get_game_status () != GAME_STATUS_INITIALISED) || (get_comms_model () == COMMS_MODEL_CLIENT))
	{

		return (FALSE);
	}

	enemy_entity = va_arg (pargs, entity *);

	#if DEBUG_MODULE
	
	debug_log ("FC_MSGS: allied armour is resisting");

	#endif

	//////////////////////////////////////////////////////////////////////////

	//
	// RETALIATION
	//

	if ((sender) && (enemy_entity))
	{
	
		entity
			*sector_en;

		entity_sides
			side;

		float
			threat_level;			//TEMP
	
		sector_en = get_local_sector_entity (get_local_entity_vec3d_ptr (enemy_entity, VEC3D_TYPE_POSITION));

		side = (entity_sides) get_local_entity_int_value (receiver, INT_TYPE_SIDE);

		threat_level = get_local_sector_entity_enemy_surface_to_surface_defence_level (sector_en, side);
		threat_level += get_local_sector_entity_enemy_surface_to_air_defence_level (sector_en, side);

		if (threat_level > 0.0)	//TEMP - should never really get here if no enemy threat
		{
			// PLAY_SPEECH (GC)
			//
			// [GC Introduction],
			// Requesting support 
	
			play_client_server_speech
			(
				get_session_entity (),
				receiver,
				side,
				ENTITY_SUB_TYPE_EFFECT_SOUND_RADIO_MESSAGE,
				SOUND_LOCALITY_RADIO,
				0.0,
				1.0,
				60.0,
				SPEECH_ORIGINATOR_GROUND_CONTROLLER,
				SPEECH_CATEGORY_MOVING,
				-1.0,
				SPEECH_ARRAY_GC_MESSAGES, SPEECH_GC_INTRODUCTION,
				SPEECH_ARRAY_GC_MESSAGES, SPEECH_GC_REQUEST_SUPPORT_AT,
				-1
			);
		}
	}

	//
	//
	//

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_force_armour_retreating (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	entity
		*enemy_entity;

	if ((get_game_status () != GAME_STATUS_INITIALISED) || (get_comms_model () == COMMS_MODEL_CLIENT))
	{

		return (FALSE);
	}

	enemy_entity = va_arg (pargs, entity *);

	#if DEBUG_MODULE

	debug_log ("FC_MSGS: allied armour is retreating");

	#endif

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_force_armour_stuck (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	#if DEBUG_MODULE
	
	debug_log ("FC_MSGS: allied armour is stuck at node");

	#endif

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_force_destroyed (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	force
		*force_raw;

	entity
		*enemy_entity;

	//campaign_criteria
		//criteria;

	//campaign_criteria_type
		//*campaign_criteria;

	int
		sub_type;

	if ((get_game_status () != GAME_STATUS_INITIALISED) || (get_comms_model () == COMMS_MODEL_CLIENT))
	{

		return FALSE;
		//debug_fatal ("FC_MSGS: client not allowed here");
	}

	force_raw = (force *) get_local_entity_data (receiver);

	#if DEBUG_MODULE
	
	debug_log ("FC_MSGS(%s): allied entity %s destroyed", entity_side_names [get_local_entity_int_value (receiver, INT_TYPE_SIDE)], entity_type_names [sender->type]);

	#endif

	enemy_entity = va_arg (pargs, entity *);

	sub_type = get_local_entity_int_value (sender, INT_TYPE_OBJECT_3D_SHAPE);

	//////////////////////////////////////////////////////////////////////////
/*
	if (get_local_entity_int_value (receiver, INT_TYPE_SIDE) != get_local_entity_int_value (sender, INT_TYPE_SIDE))
	{

		criteria = CAMPAIGN_CRITERIA_DESTROYED_ENEMY_OBJECTS;
	}
	else
	{

		criteria = CAMPAIGN_CRITERIA_DESTROYED_ALLIED_OBJECTS;
	}

	campaign_criteria = get_force_campaign_criteria (receiver, criteria, sub_type);

	if (!campaign_criteria)
	{

		campaign_criteria = get_force_campaign_criteria (receiver, criteria, OBJECT_3D_LAST);
	}

	if (campaign_criteria)
	{
	
		campaign_criteria->count ++;
	}
*/

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_force_entered_sector (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	entity
		*sector_en;

	int
		side;

	if ((get_game_status () != GAME_STATUS_INITIALISED) || (get_comms_model () == COMMS_MODEL_CLIENT))
	{

		return (FALSE);
	}

	sector_en = va_arg (pargs, entity *);

	side = get_local_entity_int_value (receiver, INT_TYPE_SIDE);

	#if DEBUG_MODULE
		
	debug_log ("FC_MSGS(%s): allied entity %s entered enemy sector", entity_side_names [side], get_local_entity_string (sender, STRING_TYPE_FULL_NAME));
	
	#endif
	
	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_force_inefficient_keysite (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	//campaign_criteria
		//criteria;

	//campaign_criteria_type
		//*campaign_criteria;

	if ((get_game_status () != GAME_STATUS_INITIALISED) || (get_comms_model () == COMMS_MODEL_CLIENT))
	{

		return (FALSE);
	}

	#if DEBUG_MODULE

	debug_log ("FC_MSGS: allied keysite %s inefficient", get_local_entity_string (sender, STRING_TYPE_KEYSITE_NAME));

	#endif
	
	//////////////////////////////////////////////////////////////////////////
/*
	if (get_local_entity_int_value (receiver, INT_TYPE_SIDE) == get_local_entity_int_value (sender, INT_TYPE_SIDE))
	{

		criteria = CAMPAIGN_CRITERIA_INEFFICIENT_ALLIED_KEYSITES;
	}
	else
	{

		criteria = CAMPAIGN_CRITERIA_INEFFICIENT_ENEMY_KEYSITES;
	}

	campaign_criteria = get_force_campaign_criteria (receiver, criteria, -1);

	if (campaign_criteria)
	{
	
		campaign_criteria->count ++;
	}
*/
	//////////////////////////////////////////////////////////////////////////

	//
	// RETALIATION
	//

	//
	//
	//

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_force_low_on_supplies (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	entity_sides
		side;

	movement_types
		movement_type;

	entity_sub_types
		sub_type;

	float
		factory_actual_range,
		airbase_actual_range;

	vec3d
		*pos;

	entity
		*task,
		*cargo,
		*airbase,
		*factory;

	if ((get_game_status () != GAME_STATUS_INITIALISED) || (get_comms_model () == COMMS_MODEL_CLIENT))
	{

		return (FALSE);
	}

	sub_type = va_arg (pargs, entity_sub_types);

	#if DEBUG_MODULE || DEBUG_SUPPLY

	debug_log ("FC_MSGS(%s): SUPPLY_INFO: allied keysite/group %s (%d) low on %s supplies (ammo = %f, fuel = %f)",
					entity_side_names [get_local_entity_int_value (receiver, INT_TYPE_SIDE)],
					get_local_entity_string (sender, STRING_TYPE_FULL_NAME),
					get_local_entity_index (sender),
					entity_sub_type_cargo_names [sub_type],
					get_local_entity_float_value (sender, FLOAT_TYPE_AMMO_SUPPLY_LEVEL),
					get_local_entity_float_value (sender, FLOAT_TYPE_FUEL_SUPPLY_LEVEL));

	#endif


	// ensure no other task is already taking care of this supply requirement

	// replace en with sender!

	if ((entity_is_object_of_task (sender, ENTITY_SUB_TYPE_TASK_SUPPLY, (entity_sides) get_local_entity_int_value (sender, INT_TYPE_SIDE))))
	{
		task = get_local_entity_first_child (sender, LIST_TYPE_TASK_DEPENDENT);

		while (task)
		{

			if (get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_TASK_SUPPLY)
			{

				if (get_local_entity_float_value (task, FLOAT_TYPE_TASK_USER_DATA) == sub_type)
				{

					// already got a supply task for this type.

					return (FALSE);
				}
			}

			task = get_local_entity_child_succ (task, LIST_TYPE_TASK_DEPENDENT);
		}
	}

	//
	// Locate correct supplier
	//

	side = (entity_sides) get_local_entity_int_value (sender, INT_TYPE_SIDE);

	pos = get_keysite_supply_position (sender);

	switch (sub_type)
	{

		case ENTITY_SUB_TYPE_CARGO_AMMO:
		{

			factory = get_closest_keysite (ENTITY_SUB_TYPE_KEYSITE_FACTORY, side, pos, 10 * KILOMETRE, &factory_actual_range, NULL);

			if (!factory)
			{

				factory = get_closest_keysite (ENTITY_SUB_TYPE_KEYSITE_OIL_REFINERY, side, pos, 10 * KILOMETRE, &factory_actual_range, NULL);
			}

			airbase = get_closest_keysite (ENTITY_SUB_TYPE_KEYSITE_AIRBASE, side, pos, 10 * KILOMETRE, &airbase_actual_range, NULL);

			if (airbase_actual_range < factory_actual_range)
			{

				factory = airbase;

				factory_actual_range = airbase_actual_range;
			}

			break;
		}

		case ENTITY_SUB_TYPE_CARGO_FUEL:
		{

			factory = get_closest_keysite (ENTITY_SUB_TYPE_KEYSITE_OIL_REFINERY, side, pos, 10 * KILOMETRE, &factory_actual_range, NULL);

			if (!factory)
			{

				factory = get_closest_keysite (ENTITY_SUB_TYPE_KEYSITE_FACTORY, side, pos, 10 * KILOMETRE, &factory_actual_range, NULL);
			}

			airbase = get_closest_keysite (ENTITY_SUB_TYPE_KEYSITE_AIRBASE, side, pos, 10 * KILOMETRE, &airbase_actual_range, NULL);

			if (airbase_actual_range < factory_actual_range)
			{

				factory = airbase;

				factory_actual_range = airbase_actual_range;
			}

			break;
		}
	}

	if (factory)
	{

		//
		// Get exact cargo to be picked up
		//

		cargo = get_local_entity_first_child (factory, LIST_TYPE_CARGO);

		while (cargo)
		{

			if (get_local_entity_int_value (cargo, INT_TYPE_ENTITY_SUB_TYPE) == sub_type)
			{

				break;
			}

			cargo = get_local_entity_child_succ (cargo, LIST_TYPE_CARGO);
		}

		if (cargo)
		{
	
			//
			// create task
			//
/*
			if (factory_actual_range > 75 * KILOMETRE)
			{

				#if DEBUG_MODULE || DEBUG_SUPPLY

				debug_log ("FC_MSGS: SUPPLY_INFO: keysite/group %s too far to re-supply %s.... ", get_local_entity_string (factory, STRING_TYPE_KEYSITE_NAME), get_local_entity_string (sender, STRING_TYPE_FULL_NAME));

				#endif
		
				return (FALSE);
			}
			else */

			movement_type = MOVEMENT_TYPE_AIR;

			task = create_supply_task (sender, factory, cargo, movement_type, task_database [ENTITY_SUB_TYPE_TASK_SUPPLY].task_priority, NULL, NULL);
	
			#if DEBUG_MODULE || DEBUG_SUPPLY

			if (task)
			{
		
				debug_log ("FC_MSGS(%s): SUPPLY_INFO: creating %s (%d) pick up and drop off task for keysite %s (%d), range %f",
								entity_side_names [get_local_entity_int_value (receiver, INT_TYPE_SIDE)],
								movement_names [movement_type],
								get_local_entity_index (task),
								get_local_entity_string (sender, STRING_TYPE_FULL_NAME),
								get_local_entity_index (sender),
								factory_actual_range);
			}
	
			#endif
		}
		else
		{
	
			#if DEBUG_MODULE || DEBUG_SUPPLY
	
			debug_log ("FC_MSGS(%s): SUPPLY_INFO: cannot locate cargo at factory to supply keysite %s",
							entity_side_names [get_local_entity_int_value (receiver, INT_TYPE_SIDE)],
							get_local_entity_string (sender, STRING_TYPE_FULL_NAME));
							//entity_sub_type_keysite_names [get_local_entity_int_value (sender, INT_TYPE_ENTITY_SUB_TYPE)]);
	
			#endif
		}
	}
	else
	{

		#if DEBUG_MODULE || DEBUG_SUPPLY

		debug_log ("FC_MSGS(%s): SUPPLY_INFO: cannot locate factory to supply keysite %s",
						entity_side_names [get_local_entity_int_value (receiver, INT_TYPE_SIDE)],
						get_local_entity_string (sender, STRING_TYPE_FULL_NAME));

		#endif
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_force_special_kill (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	force
		*force_raw;

	int
		kills;

	//campaign_criteria
		//criteria;

	//campaign_criteria_type
		//*campaign_criteria;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	force_raw = (force *) get_local_entity_data (receiver);

	kills = va_arg (pargs, int);

	#if DEBUG_MODULE
	
	debug_log ("FC_MSGS(%s): entity %s destroyed - aggressor kills = %d", entity_side_names [get_local_entity_int_value (receiver, INT_TYPE_SIDE)], get_local_entity_string (sender, STRING_TYPE_FULL_NAME), kills);

	#endif
/*
	criteria = CAMPAIGN_CRITERIA_SPECIAL_KILLS;

	campaign_criteria = get_force_campaign_criteria (receiver, criteria, -1);

	if (campaign_criteria)
	{
		campaign_criteria->count = max (campaign_criteria->count, kills);
	}
*/
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_force_vacant_farp (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	entity_sides
		this_side;

	if ((get_game_status () != GAME_STATUS_INITIALISED) || (get_comms_model () == COMMS_MODEL_CLIENT))
	{

		return (FALSE);
	}

	#if DEBUG_MODULE
	{

		vec3d
			*pos;

		pos = get_local_entity_vec3d_ptr (sender, VEC3D_TYPE_POSITION);

		debug_log ("FC_MSGS(%s): vacant keysite %s at %f, %f", entity_side_names [get_local_entity_int_value (receiver, INT_TYPE_SIDE)], get_local_entity_string (sender, STRING_TYPE_KEYSITE_NAME), pos->x, pos->z);
	}
	#endif

	this_side = (entity_sides) get_local_entity_int_value (receiver, INT_TYPE_SIDE);

	if (!entity_is_object_of_task (sender, ENTITY_SUB_TYPE_TASK_RECON, this_side))
	{
//		create_farp_recon_task (this_side, sender);
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_force_waypoint_reached (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	entity_sub_types
		sub_type;

	//campaign_criteria_type
		//*campaign_criteria;

	if ((get_game_status () != GAME_STATUS_INITIALISED) || (get_comms_model () == COMMS_MODEL_CLIENT))
	{

		return (FALSE);
	}

	sub_type = get_local_entity_int_value (sender, INT_TYPE_ENTITY_SUB_TYPE);

	//////////////////////////////////////////////////////////////////////////
/*
	campaign_criteria = get_force_campaign_criteria (receiver, CAMPAIGN_CRITERIA_REACHED_WAYPOINTS, sub_type);

	if (campaign_criteria)
	{
	
		campaign_criteria->count ++;
	}
*/
	//////////////////////////////////////////////////////////////////////////
	
	#if DEBUG_MODULE
		
	debug_log ("FC_MSGS(%s): force %s reached", entity_side_names [get_local_entity_int_value (receiver, INT_TYPE_SIDE)], entity_sub_type_waypoint_names [sub_type]);
	
	#endif

	return (TRUE);
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define REQUEST_ASSISTANCE_RANGE_MULTIPLIER		2000

static int response_to_request_assistance (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	entity
		*task,
		*group,
		*victim,
		*victim_group,
		*member,
		*aggressor,
		*target_group;

	vec3d
		*pos,
		*group_pos;

	int
		flag,
		group_type,
		response;

	float
		range,
		max_range;

	aggressor = va_arg (pargs, entity *);

	ASSERT (aggressor);

	ASSERT (sender);

	victim = sender;

	if (get_local_entity_type (victim) == ENTITY_TYPE_KEYSITE)
	{
		victim_group = victim;

		play_keysite_under_attack_speech (victim, aggressor);
	}
	else
	{
		victim_group = get_local_entity_parent (victim, LIST_TYPE_MEMBER);

		play_mobile_under_attack_speech (victim, aggressor);
	}
	
	ASSERT (victim_group);

	pos = get_local_entity_vec3d_ptr (victim, VEC3D_TYPE_POSITION);

	ASSERT (pos);

	target_group = get_local_entity_parent (aggressor, LIST_TYPE_MEMBER);

	ASSERT (target_group);

	response = FALSE;

	//
	// Send Text Message
	//

	send_text_message (target_group, victim_group, MESSAGE_TEXT_SYSTEM_ENTITY_UNDER_ATTACK, NULL);

	//
	// Play Speech
	// 

	

	//
	// find nearby suitable group
	//

	group = get_local_entity_first_child (receiver, LIST_TYPE_AIR_REGISTRY);

	while (group)
	{
		if (group != victim_group)			// if sender is a group, we don't want itself responding to its own request !
		{
			if (group != target_group)			// In certain FF incidents the aggressor may try to attack itself !
			{
				if (get_local_entity_int_value (group, INT_TYPE_ALIVE))
				{
					if (get_local_entity_int_value (group, INT_TYPE_ENGAGE_ENEMY))
					{
						group_type = get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE);
		
						// group must be aircraft
						if (group_database [group_type].movement_type == MOVEMENT_TYPE_AIR)
						{
							// group must be able to intercept with reasonable speed
							if (group_database [group_type].ai_stats.movement_speed >= 3)
							{
								//
								// group must already be airborne (i.e. navigating)
								//
	
								task = get_local_group_primary_task (group);
	
								if (task)
								{
									if (get_local_entity_int_value (task, INT_TYPE_DEFAULT_ENGAGE_ENEMY))
									{
										//
										// Check group is not already engaging
										//
		
										if (!check_group_task_type (group, ENTITY_SUB_TYPE_TASK_ENGAGE))
										{
											flag = TRUE;
				
											member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);
				
											while (member)
											{
												if (get_local_entity_int_value (member, INT_TYPE_OPERATIONAL_STATE) != OPERATIONAL_STATE_NAVIGATING)
												{
													flag = FALSE;
				
													break;
												}
				
												member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
											}
				
											if (flag)
											{
												//
												// calculate range
												//
				
												group_pos = get_local_entity_vec3d_ptr (group, VEC3D_TYPE_POSITION);
				
												range = get_sqr_2d_range (pos, group_pos);
				
												#if DEBUG_MODULE
				
												debug_log ("FC_MSGS: found possible group for persuer %s, group %s (range = %.2f)", get_local_entity_string (target, STRING_TYPE_FULL_NAME), get_local_entity_string (group, STRING_TYPE_FULL_NAME), sqrt (range));
				
												#endif
				
												max_range = group_database [group_type].ai_stats.movement_speed * REQUEST_ASSISTANCE_RANGE_MULTIPLIER;
				
												max_range *= max_range;
				
												if (range < max_range)
												{
													//
													// assign engage tasks
													//
			
													if (engage_targets_in_group (group, target_group, TRUE))
													{
														ai_log ("(ASSIST) %s assisting %s under attack by %s",
																	get_local_entity_string (group, STRING_TYPE_FULL_NAME),
																	get_local_entity_string (victim, STRING_TYPE_FULL_NAME),
																	get_local_entity_string (aggressor, STRING_TYPE_FULL_NAME));
			
														member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);
				
														play_client_server_radio_message_response (member, SPEECH_WINGMAN_ROGER_COMING_TO_ASSIST, 1.0, 10.0);
			
														response = TRUE;

														break;
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}

		group = get_local_entity_child_succ (group, LIST_TYPE_AIR_REGISTRY);
	}

	return response;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_task_created (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	entity
		*objective;

	ASSERT (sender);

	ASSERT (sender->type == ENTITY_TYPE_TASK);

	if ((get_game_status () != GAME_STATUS_INITIALISED) || (get_comms_model () == COMMS_MODEL_CLIENT))
	{

		return (FALSE);
	}

	objective = va_arg (pargs, entity *);

	if (objective)
	{
	
		#if DEBUG_MODULE
			
		debug_log ("FC_MSGS(%s): enemy created task %s objective %s",
						entity_side_names [get_local_entity_int_value (receiver, INT_TYPE_SIDE)],
						entity_sub_type_task_names [get_local_entity_int_value (sender, INT_TYPE_ENTITY_SUB_TYPE)],
						entity_type_names [objective->type]);
		
		#endif
	}
	else
	{
	
		#if DEBUG_MODULE
			
		debug_log ("FC_MSGS(%s): enemy created task %s",
						entity_side_names [get_local_entity_int_value (receiver, INT_TYPE_SIDE)],
						entity_sub_type_task_names [get_local_entity_int_value (sender, INT_TYPE_ENTITY_SUB_TYPE)]);
		
		#endif
	}

	return (TRUE);
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_task_assigned (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	ASSERT (sender);

	ASSERT (sender->type == ENTITY_TYPE_TASK);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	create_task_assigned_reactionary_tasks (sender);

	return (TRUE);
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_task_completed (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	entity_sub_types
		sub_type;

	force
		*force_raw;

	task_terminated_types
		task_terminated;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ASSERT (sender);

	ASSERT (get_local_entity_type (sender) == ENTITY_TYPE_TASK);

	task_terminated = (task_terminated_types) va_arg (pargs, int);

	sub_type = get_local_entity_int_value (sender, INT_TYPE_ENTITY_SUB_TYPE);

	ASSERT (task_database [sub_type].primary_task);

	#if DEBUG_MODULE
		
	debug_log ("FC_MSGS(%s): force %s complete", entity_side_names [get_local_entity_int_value (receiver, INT_TYPE_SIDE)], entity_sub_type_task_names [sub_type]);
	
	#endif

	//
	// Create reactionary tasks
	//

	create_task_completed_reactionary_tasks (sender);

	//
	// Update force statistics
	//
	
	force_raw = (force *) get_local_entity_data (receiver);

	ASSERT (get_local_entity_int_value (sender, INT_TYPE_TASK_COMPLETED) != TASK_INCOMPLETE);

	if (get_local_entity_int_value (sender, INT_TYPE_TASK_COMPLETED) == TASK_COMPLETED_FAILURE)
	{
		force_raw->task_generation [sub_type].failed ++;
	}
	else
	{
		force_raw->task_generation [sub_type].completed ++;
	}

	return (TRUE);
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_force_message_responses (void)
{
	#if DEBUG_MODULE >= 2

	message_responses[ENTITY_TYPE_FORCE][ENTITY_MESSAGE_LINK_CHILD] 										= response_to_link_child;

	message_responses[ENTITY_TYPE_FORCE][ENTITY_MESSAGE_UNLINK_CHILD]										= response_to_unlink_child;

	message_responses[ENTITY_TYPE_FORCE][ENTITY_MESSAGE_LINK_PARENT]										= response_to_link_parent;

	message_responses[ENTITY_TYPE_FORCE][ENTITY_MESSAGE_UNLINK_PARENT]									= response_to_unlink_parent;

	#endif

	message_responses[ENTITY_TYPE_FORCE][ENTITY_MESSAGE_CHECK_CAMPAIGN_OBJECTIVES]					= response_to_check_campaign_objectives;

	message_responses[ENTITY_TYPE_FORCE][ENTITY_MESSAGE_ENTITY_FIRED_AT]									= response_to_entity_fired_at;

	message_responses[ENTITY_TYPE_FORCE][ENTITY_MESSAGE_FORCE_ARMOUR_ADVANCING]						= response_to_force_armour_advancing;

	message_responses[ENTITY_TYPE_FORCE][ENTITY_MESSAGE_FORCE_ARMOUR_RESISTING]						= response_to_force_armour_resisting;

	message_responses[ENTITY_TYPE_FORCE][ENTITY_MESSAGE_FORCE_ARMOUR_RETREATING]						= response_to_force_armour_retreating;

	message_responses[ENTITY_TYPE_FORCE][ENTITY_MESSAGE_FORCE_ARMOUR_STUCK]								= response_to_force_armour_stuck;

	message_responses[ENTITY_TYPE_FORCE][ENTITY_MESSAGE_FORCE_DESTROYED]									= response_to_force_destroyed;

	message_responses[ENTITY_TYPE_FORCE][ENTITY_MESSAGE_FORCE_ENTERED_SECTOR]							= response_to_force_entered_sector;

	message_responses[ENTITY_TYPE_FORCE][ENTITY_MESSAGE_FORCE_INEFFICIENT_KEYSITE]					= response_to_force_inefficient_keysite;

	message_responses[ENTITY_TYPE_FORCE][ENTITY_MESSAGE_FORCE_LOW_ON_SUPPLIES]							= response_to_force_low_on_supplies;

	message_responses[ENTITY_TYPE_FORCE][ENTITY_MESSAGE_FORCE_SPECIAL_KILL]								= response_to_force_special_kill;

	message_responses[ENTITY_TYPE_FORCE][ENTITY_MESSAGE_FORCE_VACANT_FARP] 								= response_to_force_vacant_farp;

	message_responses[ENTITY_TYPE_FORCE][ENTITY_MESSAGE_FORCE_WAYPOINT_REACHED]						= response_to_force_waypoint_reached;

	message_responses[ENTITY_TYPE_FORCE][ENTITY_MESSAGE_REQUEST_ASSISTANCE]								= response_to_request_assistance;

	message_responses[ENTITY_TYPE_FORCE][ENTITY_MESSAGE_TASK_CREATED]										= response_to_task_created;

	message_responses[ENTITY_TYPE_FORCE][ENTITY_MESSAGE_TASK_ASSIGNED] 									= response_to_task_assigned;

	message_responses[ENTITY_TYPE_FORCE][ENTITY_MESSAGE_TASK_COMPLETED] 									= response_to_task_completed;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
