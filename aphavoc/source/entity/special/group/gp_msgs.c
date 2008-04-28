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

///////////////////////////////////////////////////
//
// 2 levels of debug
//
///////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

#include "ai/taskgen/taskgen.h"
#include "ai/ai_misc/ai_route.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_link_child (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	group
		*raw;

	list_types
		list_type;

	#if DEBUG_MODULE >= 2

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	raw = get_local_entity_data (receiver);

	list_type = va_arg (pargs, list_types);

	switch (list_type)
	{

		case LIST_TYPE_MEMBER:
		{

			raw->member_count ++;

			#if DEBUG_MODULE
			{
	
				int
					count;

				count = get_local_group_member_count (receiver);
	
				ASSERT (count == raw->member_count);
			}
			#endif

			if (get_local_entity_int_value (sender, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
			{

				raw->multiplayer_group = TRUE;
			}

			//
			// if group parent is a keysite, add members stats to keysite strength
			//

			if (get_local_entity_int_value (sender, INT_TYPE_IDENTIFY_FIXED))
			{
				entity
					*parent;

				parent = get_local_entity_parent (receiver, LIST_TYPE_BUILDING_GROUP);

				if (parent)
				{
					if (get_local_entity_type (parent) == ENTITY_TYPE_KEYSITE)
					{
						add_local_entity_importance_to_keysite (sender, parent);
					}
				}
			}

			//
			// if member is a mobile, notify the campaign screen of the change
			//

			if (get_local_entity_int_value (sender, INT_TYPE_IDENTIFY_MOBILE))
			{
				notify_campaign_screen (CAMPAIGN_SCREEN_GROUP_ADD_MEMBER, sender);
			}

			break;
		}
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_unlink_child (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	group
		*raw;

	list_types
		list_type;

	#if DEBUG_MODULE >= 2

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	raw = get_local_entity_data (receiver);

	list_type = va_arg (pargs, list_types);

	switch (list_type)
	{

		case LIST_TYPE_MEMBER:
		{

			entity
				*member;

			int
				multiplayer_group;

			raw->member_count --;

			member = raw->member_root.first_child;

			multiplayer_group = FALSE;

			while (member)
			{

				if (get_local_entity_int_value (member, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
				{

					multiplayer_group = TRUE;
				}

				member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
			}

			raw->multiplayer_group = multiplayer_group;

			//
			// if group parent is a keysite, remove members stats from keysite strength
			//

			if (get_local_entity_int_value (sender, INT_TYPE_IDENTIFY_FIXED))
			{
				subtract_local_entity_importance_from_keysite (sender);
			}

			break;
		}
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_link_parent (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	group
		*raw;

	list_types
		list_type;

	#if DEBUG_MODULE >= 2

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	raw = get_local_entity_data (receiver);

	list_type = va_arg (pargs, list_types);

	switch (list_type)
	{
		case LIST_TYPE_DIVISION:
		{
			set_local_division_name (receiver, raw->division_name);

			break;
		}
	}

	return (TRUE);
}

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

static int response_to_entity_fired_at (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	entity
		*victim,
		*force;

	int
		side,
		assist;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ASSERT (sender);

	//
	// Sender is the entity that fired at the receiving group
	//

	victim = va_arg (pargs, entity *);

	side = get_local_entity_int_value (receiver, INT_TYPE_SIDE);

	assist = FALSE;

	if (get_local_entity_int_value (sender, INT_TYPE_SIDE) != side)
	{
		//
		// Call for assistance
		//

		if (get_local_entity_float_value (receiver, FLOAT_TYPE_ASSIST_TIMER) == 0.0)
		{
			ai_log ("(RETALIATION) Group %s Requesting Assistance after being fired at by %s",
						get_local_entity_string (receiver, STRING_TYPE_FULL_NAME),
						get_local_entity_string (sender, STRING_TYPE_FULL_NAME));

			set_local_entity_float_value (receiver, FLOAT_TYPE_ASSIST_TIMER, DEFAULT_GROUP_ASSISTANCE_REQUEST_TIMER);

			force = get_local_force_entity (side);

			assist = notify_local_entity (ENTITY_MESSAGE_REQUEST_ASSISTANCE, force, victim, sender);
		}

		//
		// Retaliate - If not already engaging, and able to fight
		//

		if (get_local_entity_int_value (receiver, INT_TYPE_ENGAGE_ENEMY))
		{
			if (!check_group_task_type (receiver, ENTITY_SUB_TYPE_TASK_ENGAGE))
			{
				if (group_task_specific_retaliation_checks (receiver, sender, assist))
				{
					ai_log ("(RETALIATION) Group %s Responding to being fired at by %s",
								get_local_entity_string (receiver, STRING_TYPE_FULL_NAME),
								get_local_entity_string (sender, STRING_TYPE_FULL_NAME));

					engage_specific_target (receiver, sender, TASK_ASSIGN_ALL_MEMBERS, TRUE);
				}
			}
		}
	}
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_entity_targeted (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	entity
		*victim,
		*pilot;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	//
	// Sender is the aggressor
	//
	
	ASSERT (sender);

	victim = va_arg (pargs, entity *);

	//
	// Perform Retaliation
	//

	if (get_local_entity_int_value (sender, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
	{
		//
		// Same response as fired at.... (Hard difficulty only)
		//
		
		pilot = get_local_entity_first_child (sender, LIST_TYPE_AIRCREW);
	
		ASSERT (pilot);
	
		if (get_local_entity_int_value (pilot, INT_TYPE_DIFFICULTY_LEVEL) == GAME_DIFFICULTY_HARD)
		{	
			if (get_local_entity_int_value (sender, INT_TYPE_RADAR_ON))
			{	
				notify_local_entity (ENTITY_MESSAGE_ENTITY_FIRED_AT, receiver, sender, victim);
			}
		}
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_ground_force_advance (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	group
		*group_raw;

	int
		loop,
		current_node,
		advance_node,
		success_flag;

	entity
		*group,
		*allied_force,
		*group_occupying_node;

	vec3d
		*pos;

	success_flag = TRUE;

	advance_node = va_arg (pargs, int);

	group_raw = get_local_entity_data (receiver);

	if ((get_local_entity_int_value (receiver, INT_TYPE_GROUP_MODE) == GROUP_MODE_BUSY) || (!check_group_members_awake (receiver)))
	{

		#if DEBUG_MODULE

		debug_log ("GP_MSGS: group %d busy or sleeping", get_local_entity_index (receiver));

		#endif

		return FALSE;
	}

	current_node = group_raw->route_node;

	//////////////////////////////////////////////////////////////
	ASSERT (get_road_link_breaks (current_node, advance_node) == 0);
	//////////////////////////////////////////////////////////////

	allied_force = get_local_force_entity (group_raw->side);

	#if DEBUG_MODULE

	debug_log ("GP_MSGS: looking to advance from %d to %d group %d side %s", current_node, advance_node, receiver, entity_side_names [group_raw->side]);

	#endif

	//
	// Locate group at advance node (might not be one)
	//

	group_occupying_node = get_group_at_road_node (advance_node);

	//
	// Free and Reserve nodes ready for recursive calls
	//
	
	road_nodes [group_raw->route_node].side_occupying = ENTITY_SIDE_NEUTRAL;
	
	road_nodes [advance_node].side_occupying = group_raw->side;
	
	group_raw->route_node = advance_node;

	//
	// Tell group at node to retreat (if enemy, otherwise fail)
	//

	if (group_occupying_node)
	{

		if (get_local_entity_int_value (group_occupying_node, INT_TYPE_SIDE) == get_enemy_side (group_raw->side))
		{

			#if DEBUG_MODULE

			debug_log ("GP_MSGS: telling group %d side %s at node %d to retreat", group_occupying_node, entity_side_names [get_local_entity_int_value (group_occupying_node, INT_TYPE_SIDE)], advance_node);

			#endif

			success_flag = notify_local_entity (ENTITY_MESSAGE_GROUND_FORCE_RETREAT, group_occupying_node, receiver, current_node);
		}
		else
		{

			#if DEBUG_MODULE

			debug_log ("GP_MSGS: aborting group %d advance from %d because enemy (allied group?) can't retreat from %d", receiver, current_node, group_occupying_node);

			#endif

			success_flag = FALSE;
		}
	}

	//
	// Create advance task if retreat was successful
	//

	if (success_flag)
	{

		entity
			*new_task;

		#if DEBUG_MODULE

		if (get_local_entity_parent (receiver, LIST_TYPE_KEYSITE_GROUP))
		{

			if (get_local_entity_type (get_local_entity_parent (receiver, LIST_TYPE_KEYSITE_GROUP)) == ENTITY_TYPE_KEYSITE)
			{

				debug_log ("GP_MSGS: regen'd group taking off");
			}
		}

		#endif

		new_task = create_ground_force_task (ENTITY_SUB_TYPE_TASK_ADVANCE, receiver, current_node, advance_node, task_database [ENTITY_SUB_TYPE_TASK_ADVANCE].task_priority, NULL, NULL);

		if (new_task)
		{

			#if DEBUG_MODULE

			debug_log ("GP_MSGS: creating advance task for group %d, side %s to node %d", receiver, entity_side_names [group_raw->side], advance_node);

			#endif
		
			if (!assign_primary_task_to_group (receiver, new_task))
			{

				destroy_local_entity_family (new_task);

				transmit_entity_comms_message (ENTITY_COMMS_DESTROY_LOCAL_FAMILY, new_task);

				return FALSE;
			}

			/////////////////////////////////////////////////////////////////
			//
			// SPECIAL_EFFECT_HOOK FOR FRONTLINE ADVANCING
			//
			/////////////////////////////////////////////////////////////////

			{
				// PLAY_SPEECH (GC)
				//
				// [GC Introduction],
				// We are advancing

				pos = &road_node_positions [advance_node];

				ASSERT (pos);

				get_speech_sector_coordinates (pos);

				play_client_server_speech
				(
					get_session_entity (),
					receiver,
					group_raw->side,
					ENTITY_SUB_TYPE_EFFECT_SOUND_RADIO_MESSAGE,
					SOUND_LOCALITY_RADIO,
					0.0,
					0.3,
					20.0,
					SPEECH_ORIGINATOR_GROUND_CONTROLLER,
					SPEECH_CATEGORY_MOVING,
					180.0,
					SPEECH_ARRAY_GC_MESSAGES, SPEECH_GC_INTRODUCTION,
					SPEECH_ARRAY_GC_MESSAGES, SPEECH_GC_ADVANCING_TO,
					SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [0],
					SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [1],
					SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [2],
					SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [3],
					SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [4],
					SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [5],
					-1
				);
			}

			/////////////////////////////////////////////////////////////////
			//
			//
			/////////////////////////////////////////////////////////////////
	
			//
			// notify force that armour is advancing
			//

			notify_local_entity (ENTITY_MESSAGE_FORCE_ARMOUR_ADVANCING, allied_force, receiver, group_occupying_node);
	
			//
			// Check for supporting forces and bring them along
			//

			for (loop = 0; loop < road_nodes [current_node].number_of_links; loop ++)
			{

				#if DEBUG_MODULE

				debug_log ("GP_MSGS: looking for support group to node %d", current_node);

				#endif

				if (road_nodes [road_nodes [current_node].links [loop].node].side_occupying == group_raw->side)
				{

					if (get_road_link_breaks (road_nodes [current_node].links [loop].node, current_node) == 0)
					{
	
						entity
							*advancing_sector,
							*supporting_sector;
	
						sector
							*advancing_sector_raw,
							*supporting_sector_raw;
	
						int
							advancing_warmth,
							supporting_warmth;
				
						advancing_sector = get_local_sector_entity (&road_node_positions [current_node]);
						advancing_sector_raw = get_local_entity_data (advancing_sector);
//						advancing_warmth = advancing_sector_raw->side_ground_warmth [group_raw->side];
						advancing_warmth = 1.0;
				
						supporting_sector = get_local_sector_entity (&road_node_positions [road_nodes [current_node].links [loop].node]);
						supporting_sector_raw = get_local_entity_data (supporting_sector);
//						supporting_warmth = supporting_sector_raw->side_ground_warmth [group_raw->side];
						supporting_warmth = 0.0; 
	
						if (supporting_warmth <= advancing_warmth)
						{
		
							//
							// found node now find group
							//
		
							#if DEBUG_MODULE
		
							debug_log ("GP_MSGS: found support group at node %d (warmth advancing %d, supporting %d)", road_nodes [current_node].links [loop].node, advancing_warmth, supporting_warmth);
		
							#endif
	
							group = get_group_at_road_node (road_nodes [current_node].links [loop].node);
		
							if (group)
							{
		
								notify_local_entity (ENTITY_MESSAGE_GROUND_FORCE_ADVANCE, group, receiver, current_node);
		
								#if DEBUG_MODULE
		
								debug_log ("GP_MSGS: notifying support group %d to advance to node %d", group, current_node);
		
								#endif
		
								return TRUE;
							}
						}
					}
				}
			}
		}
	}
	else
	{

		//
		// Unreserve nodes since group isn't advancing
		//
	
		ASSERT (road_nodes [current_node].side_occupying == ENTITY_SIDE_NEUTRAL);
	
		road_nodes [current_node].side_occupying = group_raw->side;
		
		road_nodes [advance_node].side_occupying = ENTITY_SIDE_NEUTRAL;

		group_raw->route_node = current_node;

		#if DEBUG_MODULE

		debug_log ("GP_MSGS: aborting advance from %d to %d", current_node, advance_node);

		#endif

		if (group_occupying_node)
		{

			//
			// notify force that opposing forces can't retreat, let it 'soften them up'
			//

			notify_local_entity (ENTITY_MESSAGE_FORCE_ARMOUR_RESISTING, allied_force, receiver, group_occupying_node);
		}
	}

	return (success_flag);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_ground_force_retreat (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	int
		loop,
		success_flag,
		current_node,
		retreat_node,
		advancing_node;

	group
		*group_raw;

	entity
		*allied_force,
		*group_occupying_node;

	vec3d
		*pos;

	group_raw = get_local_entity_data (receiver);

	if ((get_local_entity_int_value (receiver, INT_TYPE_GROUP_MODE) == GROUP_MODE_BUSY) || (!check_group_members_awake (receiver)))
	{

		return FALSE;
	}

	success_flag = TRUE;

	advancing_node = va_arg (pargs, int);

	allied_force = get_local_force_entity (group_raw->side);

	//
	// Locate node to retreat to, must be aware of it and not occupied by the enemy
	// and not being exploring by allied (ie. exploring flag set while recursing to save infinite call)
	//

	current_node = group_raw->route_node;

	//////////////////////////////////////////////////////////////
	ASSERT (get_road_link_breaks (current_node, advancing_node) == 0);
	//////////////////////////////////////////////////////////////

	retreat_node = -1;

	for (loop = 0; loop < road_nodes [current_node].number_of_links; loop ++)
	{

		retreat_node = road_nodes [current_node].links [loop].node;

		if (
				(!(road_nodes [retreat_node].side_occupying & get_enemy_side (group_raw->side))) &&
				(!(road_nodes [retreat_node].side_exploring & group_raw->side)) &&
				(retreat_node != advancing_node))
		{
			pos = &road_node_positions [retreat_node];

			if (point_inside_adjusted_map_area (pos))
			{
				if (get_road_link_breaks (retreat_node, current_node) == 0)
				{
		
					#if DEBUG_MODULE
		
					debug_log ("GP_MSGS: Trying to retreat to node %d", retreat_node);
		
					#endif
		
					//
					// Locate group at retreat node (might not be one)
					//
		
					group_occupying_node = get_group_at_road_node (retreat_node);
				
					//
					// Free and Reserve nodes ready for recursive calls
					//
				
					road_nodes [current_node].side_occupying = ENTITY_SIDE_NEUTRAL;
				
					road_nodes [retreat_node].side_exploring = group_raw->side;
				
					group_raw->route_node = retreat_node;
				
					//
					// Tell group at node to retreat
					//
				
					if (group_occupying_node)
					{
				
						if (get_local_entity_int_value (group_occupying_node, INT_TYPE_SIDE) == group_raw->side)
						{
				
							#if DEBUG_MODULE
		
							debug_log ("GP_MSGS: telling group %d side %s to retreat from node %d", group_occupying_node, entity_side_names [get_local_entity_int_value (group_occupying_node, INT_TYPE_SIDE)], retreat_node);
		
							#endif
				
							success_flag = notify_local_entity (ENTITY_MESSAGE_GROUND_FORCE_RETREAT, group_occupying_node, receiver, current_node);
						}
						else
						{
		
							#if DEBUG_MODULE
		
							debug_log ("GP_MSGS: aborting retreat. Side %s, sleep %f", entity_side_names [group_raw->side], group_raw->sleep);
		
							#endif
				
							success_flag = FALSE;
						}
					}
				
					if (success_flag)
					{
		
						entity
							*new_task;
		
						new_task = create_ground_force_task (ENTITY_SUB_TYPE_TASK_RETREAT, receiver, current_node, retreat_node, task_database [ENTITY_SUB_TYPE_TASK_RETREAT].task_priority, NULL, NULL);
		
						if (new_task)
						{
				
							#if DEBUG_MODULE
		
							debug_log ("GP_MSGS: creating retreat task for group %d side %s from %d to %d", receiver, entity_side_names [group_raw->side], current_node, retreat_node);
		
							#endif
		
							if (assign_primary_task_to_group (receiver, new_task))
							{
			
								road_nodes [retreat_node].side_occupying = group_raw->side;
			
								road_nodes [retreat_node].side_exploring &= ~group_raw->side;
		
								/////////////////////////////////////////////////////////////////
								//
								// SPECIAL_EFFECT_HOOK FOR FRONTLINE RETREATING
								//
								/////////////////////////////////////////////////////////////////
		
								{
									// PLAY_SPEECH (GC)
									//
									// [GC Introduction],
									// We are retreating 
			
									ASSERT (pos);
					
									get_speech_sector_coordinates (pos);

									play_client_server_speech
									(
										get_session_entity (),
										receiver,
										group_raw->side,
										ENTITY_SUB_TYPE_EFFECT_SOUND_RADIO_MESSAGE,
										SOUND_LOCALITY_RADIO,
										0.0,
										0.3,
										20.0,
										SPEECH_ORIGINATOR_GROUND_CONTROLLER,
										SPEECH_CATEGORY_MOVING,
										180.0,
										SPEECH_ARRAY_GC_MESSAGES, SPEECH_GC_INTRODUCTION,
										SPEECH_ARRAY_GC_MESSAGES, SPEECH_GC_RETREATING_TO,
										SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [0],
										SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [1],
										SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [2],
										SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [3],
										SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [4],
										SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [5],
										-1
									);
								}
		
								/////////////////////////////////////////////////////////////////
								//
								//
								/////////////////////////////////////////////////////////////////
		
								//
								// notify force of retreat (hope for a CAS)
								//
		
								notify_local_entity (ENTITY_MESSAGE_FORCE_ARMOUR_RETREATING, allied_force, receiver, sender);
		
								return TRUE;
							}
							else
							{
		
								notify_local_entity (ENTITY_MESSAGE_FORCE_ARMOUR_STUCK, allied_force, receiver, NULL);
		
								destroy_local_entity_family (new_task);
			
								transmit_entity_comms_message (ENTITY_COMMS_DESTROY_LOCAL_FAMILY, new_task);
							}
						}
					}
					else
					{
				
						//
						// Unreserve nodes since group isn't retreating
						//
				
						ASSERT (road_nodes [current_node].side_occupying == ENTITY_SIDE_NEUTRAL);
				
						road_nodes [current_node].side_occupying = group_raw->side;
				
						road_nodes [retreat_node].side_occupying = ENTITY_SIDE_NEUTRAL;
				
						group_raw->route_node = current_node;
				
						#if DEBUG_MODULE
		
						debug_log ("GP_MSGS: aborting retreat from %d to %d", current_node, retreat_node);
		
						#endif
					}
				}
			}
		}
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_task_completed (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	entity
		*next,
		*task,
		*member;

	task_terminated_types
		task_terminated;

	int
		speech_index;

	#if DEBUG_MODULE

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ASSERT (sender);

	ASSERT (get_local_entity_type (sender) == ENTITY_TYPE_GUIDE);

	task_terminated = va_arg (pargs, task_terminated_types);

	//
	// Notify Escort tasks
	//

	task = get_local_entity_first_child (receiver, LIST_TYPE_TASK_DEPENDENT);

	while (task)
	{
		next = get_local_entity_child_succ (task, LIST_TYPE_TASK_DEPENDENT);

		if (get_local_entity_type (task) == ENTITY_TYPE_TASK)
		{
			if (get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_TASK_ESCORT)
			{
				debug_log ("GP_MSGS: Group %d Notifying Escort Task %d of completeness",
								get_local_entity_index (receiver),
								get_local_entity_index (task));

				notify_local_entity (ENTITY_MESSAGE_TASK_COMPLETED, task, receiver, TASK_TERMINATED_OBJECTIVE_MESSAGE);
			}
		}

		task = next;
	}

	task = get_local_entity_parent (sender, LIST_TYPE_GUIDE);

	ASSERT (task);

	if (get_local_entity_int_value (task, INT_TYPE_PRIMARY_TASK))
	{
		//
		// Notify Players of task completed
		//

		member = get_local_entity_first_child (receiver, LIST_TYPE_MEMBER);
	
		while (member)
		{
			if (get_local_entity_int_value (member, INT_TYPE_PLAYER) == ENTITY_PLAYER_LOCAL)
			{
				notify_gunship_entity_mission_completed (member, task);
			}
			else if (get_local_entity_int_value (member, INT_TYPE_PLAYER) == ENTITY_PLAYER_REMOTE)
			{
				transmit_entity_comms_message (ENTITY_COMMS_PLAYER_TASK_COMPLETED, member, task);
			}
		
			member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
		}

		//
		// Play Speech (Unless failed)
		//

		switch (get_local_entity_int_value (task, INT_TYPE_TASK_COMPLETED))
		{
			case TASK_INCOMPLETE:
			{
				debug_fatal ("GP_MSGS: Response to task completed - Task NOT complete");

				break;
			}
			case TASK_COMPLETED_FAILURE:
			{
				//
				// Play Speech
				//

				if (get_local_entity_int_value (task, INT_TYPE_TASK_TERMINATED) != TASK_TERMINATED_GROUP_DESTROYED)
				{
					if (get_local_entity_int_value (receiver, INT_TYPE_AIRCRAFT_GROUP))
					{
						play_client_server_speech
						(
							get_session_entity (),
							receiver,
							get_local_entity_int_value (receiver, INT_TYPE_SIDE),
							ENTITY_SUB_TYPE_EFFECT_SOUND_RADIO_MESSAGE,
							SOUND_LOCALITY_RADIO,
							0.0,
							1.0,
							20.0,
							SPEECH_ORIGINATOR_FORWARD_AIR_CONTROLLER,
							SPEECH_CATEGORY_MISSION_RELATED,
							-1.0,
							SPEECH_ARRAY_CALLSIGNS, get_local_entity_int_value (receiver, INT_TYPE_GROUP_CALLSIGN),
							SPEECH_ARRAY_FAC_MESSAGES, SPEECH_FAC_INTRODUCTION,
							SPEECH_ARRAY_FAC_MESSAGES, SPEECH_FAC_RETURN_TO_BASE,
							-1
						);
					}
				}
				
				break;
			}
			case TASK_COMPLETED_PARTIAL:
			case TASK_COMPLETED_SUCCESS:
			{
				//
				// Play Speech
				//

				if (get_local_entity_int_value (receiver, INT_TYPE_AIRCRAFT_GROUP))
				{
					member = get_local_entity_first_child (receiver, LIST_TYPE_MEMBER);

					if (member)
					{
						if (get_local_entity_int_value (member, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI)
						{
							if (rand16 () & 0x01)
							{
								speech_index = SPEECH_WINGMAN_MISSION_COMPLETE1;
							}
							else
							{
								speech_index = SPEECH_WINGMAN_MISSION_COMPLETE2;
							}

							play_client_server_wingman_message
							(
								member,
								0.7,
								20.0,
								SPEECH_CATEGORY_MISSION_RELATED, -1.0,
								SPEECH_INTRODUCTION_ALWAYS,
								SPEECH_ARRAY_WINGMAN_MESSAGES, speech_index
							);
						}
						else
						{
							if (rand16 () & 0x01)
							{
								speech_index = SPEECH_CPG_MISSION_COMPLETED1;
							}
							else
							{
								speech_index = SPEECH_CPG_MISSION_COMPLETED2;
							}
		
							play_client_server_cpg_message (receiver, 0.8, 30.0, SPEECH_CATEGORY_MISSION_RELATED, -1.0, speech_index);
						}
					}
				}
				
				break;
			}
		}
	}
	
	//
	// send system message
	//

	if (get_local_entity_int_value (task, INT_TYPE_VISIBLE_TASK))
	{
		send_text_message (receiver, task, MESSAGE_TEXT_SYSTEM_TASK_COMPLETED, NULL);

		ai_log ("(TASK) %s mission %s by %s",
					get_local_entity_string (task, STRING_TYPE_SHORT_DISPLAY_NAME),
					task_debrief_result_names [get_local_entity_int_value (task, INT_TYPE_TASK_COMPLETED)],
					get_local_entity_string (receiver, STRING_TYPE_FULL_NAME));
	}

	//
	// group return to base (but only if not already at end of wp route, or group dead)
	//

	switch (get_local_entity_int_value (task, INT_TYPE_TASK_TERMINATED))
	{
		case TASK_TERMINATED_GROUP_DESTROYED:
		case TASK_TERMINATED_WAYPOINT_ROUTE_COMPLETE:
		{
			break;
		}
		default:
		{
			group_return_to_base (receiver);

			break;
		}
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_task_terminated (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	unsigned int
		valid_members;

	task_terminated_types
		task_terminated;

	entity
		*guide,
		*member,
		*task;

	int
		task_type;

	group
		*raw;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ASSERT (sender);

	ASSERT (get_local_entity_type (sender) == ENTITY_TYPE_GUIDE);

	raw = get_local_entity_data (receiver);

	guide = sender;

	task = get_local_entity_parent (guide, LIST_TYPE_GUIDE);

	ASSERT (task);

	task_type = get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE);

	task_terminated = va_arg (pargs, task_terminated_types);

	valid_members = 0;

	member = get_local_entity_first_child (receiver, LIST_TYPE_MEMBER);

	while (member)
	{
		guide = get_local_entity_parent (member, LIST_TYPE_FOLLOWER);

		if (guide)
		{
			if (get_local_entity_parent (guide, LIST_TYPE_GUIDE) == task)
			{
				//
				// Store which members were actually currently doing the terminated task...
				//
				
				valid_members |= (1 << get_local_entity_int_value (member, INT_TYPE_GROUP_MEMBER_NUMBER));

				//
				// Inform members of task terminated, members should make themselves safe.
				//
			
				notify_local_entity (message, member, receiver);
			}
		}

		if (task_database [task_type].counts_towards_player_log)
		{
			ASSERT (task_database [task_type].primary_task);

			if (get_local_entity_int_value (member, INT_TYPE_PLAYER) == ENTITY_PLAYER_LOCAL)
			{
				notify_gunship_entity_mission_terminated (member, task);
			}
			else if (get_local_entity_int_value (member, INT_TYPE_PLAYER) == ENTITY_PLAYER_REMOTE)
			{
				transmit_entity_comms_message (ENTITY_COMMS_PLAYER_TASK_TERMINATED, member, task);
			}
		}
	
		member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
	}

	//
	// Reassign any members that were doing the terminated task
	//

	if (valid_members != 0)
	{
		reassign_group_members_to_valid_tasks (receiver, task, valid_members, TRUE);
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_mobile_killed (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	entity
		*guide,
		*task,
		*next;

	unsigned int
		valid_members,
		member_number;
			
	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ASSERT (sender);

	ASSERT (get_local_entity_int_value (sender, INT_TYPE_IDENTIFY_MOBILE));

	if (get_local_entity_int_value (receiver, INT_TYPE_MEMBER_COUNT) == 0)
	{
		//
		// group empty - so kill it (terminating ALL tasks)
		//

		kill_client_server_group_entity (receiver);

		return TRUE;
	}
	else
	{
		//
		// If the group is the objective of a task - check that task for completeness
		//

		task = get_local_entity_first_child (receiver, LIST_TYPE_TASK_DEPENDENT);

		while (task)
		{
			next = get_local_entity_child_succ (task, LIST_TYPE_TASK_DEPENDENT);

			if (get_local_entity_type (task) == ENTITY_TYPE_TASK)
			{
				if (!get_local_entity_int_value (task, INT_TYPE_TASK_COMPLETED))
				{
					if (assess_task_completeness (task, TASK_TERMINATED_IN_PROGRESS) == TASK_COMPLETED_SUCCESS)
					{
						notify_local_entity (ENTITY_MESSAGE_TASK_COMPLETED, task, receiver, TASK_TERMINATED_OBJECTIVE_MESSAGE);
					}
				}
			}

			task = next;
		}
		
		//
		// Remove dead mobile from GUIDE entities "valid_members" - any guides left with no valid members will be destroyed
		//

		//
		// Done in a seemingly inefficient way because "delete_group_member_from_guide_entity" can indirectly destroy
		// more than one guide in the group's guide stack 
		//
		
		member_number = (1 << get_local_entity_int_value (sender, INT_TYPE_GROUP_MEMBER_NUMBER));

		do
		{
			guide = get_local_entity_first_child (receiver, LIST_TYPE_GUIDE_STACK);

			while (guide)
			{
				valid_members = get_local_entity_int_value (guide, INT_TYPE_VALID_GUIDE_MEMBERS);

				if ((valid_members != TASK_ASSIGN_ALL_MEMBERS) && (valid_members & member_number))
				{
					task = get_local_entity_parent (guide, LIST_TYPE_GUIDE);

					ASSERT (task);

					if (get_local_entity_int_value (task, INT_TYPE_SOLO_TASK))
					{
						//
						// special case for ENGAGE / LANDING tasks etc...
						// DO NOT terminate the task, since other mobiles may still be doing it (or can do it in the future)
						// Instead, simply destroy the guide
						//

						ASSERT (valid_members == member_number);

						destroy_client_server_entity (guide);
					}
					else
					{	
						delete_group_member_from_guide_entity (sender, guide);
					}

					break;
				}
	
				guide = get_local_entity_child_succ (guide, LIST_TYPE_GUIDE_STACK);
			}
		}
		while (guide);
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_group_message_responses (void)
{

	message_responses[ENTITY_TYPE_GROUP][ENTITY_MESSAGE_LINK_CHILD] 					= response_to_link_child;

	message_responses[ENTITY_TYPE_GROUP][ENTITY_MESSAGE_UNLINK_CHILD]					= response_to_unlink_child;

	message_responses[ENTITY_TYPE_GROUP][ENTITY_MESSAGE_LINK_PARENT]					= response_to_link_parent;

	#if DEBUG_MODULE >= 2

	message_responses[ENTITY_TYPE_GROUP][ENTITY_MESSAGE_UNLINK_PARENT]				= response_to_unlink_parent;

	#endif

	message_responses[ENTITY_TYPE_GROUP][ENTITY_MESSAGE_ENTITY_FIRED_AT]				= response_to_entity_fired_at;

	message_responses[ENTITY_TYPE_GROUP][ENTITY_MESSAGE_ENTITY_TARGETED]				= response_to_entity_targeted;

	message_responses[ENTITY_TYPE_GROUP][ENTITY_MESSAGE_GROUND_FORCE_ADVANCE]		= response_to_ground_force_advance;

	message_responses[ENTITY_TYPE_GROUP][ENTITY_MESSAGE_GROUND_FORCE_RETREAT]		= response_to_ground_force_retreat;

	message_responses[ENTITY_TYPE_GROUP][ENTITY_MESSAGE_TASK_COMPLETED]				= response_to_task_completed;

	message_responses[ENTITY_TYPE_GROUP][ENTITY_MESSAGE_TASK_TERMINATED]				= response_to_task_terminated;

	message_responses[ENTITY_TYPE_GROUP][ENTITY_MESSAGE_MOBILE_KILLED]				= response_to_mobile_killed;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
