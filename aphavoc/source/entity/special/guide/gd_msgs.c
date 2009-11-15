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

#if DEBUG_MODULE 

static int response_to_link_child (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	debug_log_entity_message (message, receiver, sender, pargs);

	return (TRUE);
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MODULE

static int response_to_unlink_child (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	debug_log_entity_message (message, receiver, sender, pargs);

	return (TRUE);
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MODULE

static int response_to_link_parent (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	debug_log_entity_message (message, receiver, sender, pargs);

	return (TRUE);
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MODULE

static int response_to_unlink_parent (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	debug_log_entity_message (message, receiver, sender, pargs);

	return (TRUE);
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_waypoint_action (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	entity
		*current_wp;

	#if DEBUG_MODULE

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ASSERT (get_local_entity_int_value (receiver, INT_TYPE_CHECK_WAYPOINT_ACTION));

	current_wp = get_local_entity_parent (receiver, LIST_TYPE_CURRENT_WAYPOINT);

	ASSERT (current_wp);

	ASSERT (get_local_entity_int_value (current_wp, INT_TYPE_CHECK_WAYPOINT_ACTION));

	notify_local_entity (ENTITY_MESSAGE_WAYPOINT_ACTION, current_wp, receiver);

	set_local_entity_int_value (receiver, INT_TYPE_CHECK_WAYPOINT_ACTION, FALSE);

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_waypoint_reached (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	#if DEBUG_MODULE

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	switch (get_local_entity_int_value (receiver, INT_TYPE_ENTITY_SUB_TYPE))
	{
		//
		// NAVIGATION GUIDES
		//
		
		case ENTITY_SUB_TYPE_GUIDE_NAVIGATION_DIRECT:
		case ENTITY_SUB_TYPE_GUIDE_NAVIGATION_VIRTUAL:
		case ENTITY_SUB_TYPE_GUIDE_NAVIGATION_ROUTED:
		case ENTITY_SUB_TYPE_GUIDE_NAVIGATION_ALTITUDE:
		case ENTITY_SUB_TYPE_GUIDE_LANDING_DIRECT:
		case ENTITY_SUB_TYPE_GUIDE_LANDED:
		{
			navigation_guide_waypoint_reached (receiver);

			break;
		}

		//
		// AIR-TO-AIR ATTACK GUIDES
		//

		case ENTITY_SUB_TYPE_GUIDE_ATTACK_AA_MOVE_SIX:
		{
			attack_guide_move_six_reached (receiver);

			break;
		}

		case ENTITY_SUB_TYPE_GUIDE_ATTACK_AA_MOVE_CIRCLE:
		{
			attack_guide_move_circle_reached (receiver);

			break;
		}

		case ENTITY_SUB_TYPE_GUIDE_ATTACK_AA_FIRE_INTERCEPT:
		{
			attack_guide_fire_intercept_reached (receiver);

			break;
		}

		//
		// AIR-TO-GROUND ATTACK GUIDES
		//

		case ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_APPROACH:
		{
			attack_guide_approach_reached (receiver);

			break;
		}

		case ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_SEEK_COVER:
		{
			attack_guide_seek_cover_reached (receiver);

			break;
		}

		case ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_FLY_TO_COVER:
		{
			attack_guide_fly_to_cover_reached (receiver);

			break;
		}

		case ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_TAKE_COVER:
		{
			attack_guide_take_cover_reached (receiver);

			break;
		}

		case ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_CLIMB:
		{
			attack_guide_climb_reached (receiver);

			break;
		}

		case ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_DIVE:
		{
			attack_guide_dive_reached (receiver);

			break;
		}

		case ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_FIRE:
		case ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_FIRE_VIRTUAL:
		{
			attack_guide_fire_reached (receiver);

			break;
		}

		case ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_DISENGAGE:
		case ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_DISENGAGE_VIRTUAL:
		{
			attack_guide_disengage_reached (receiver);

			break;
		}

		case ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_EGRESS:
		{
			attack_guide_egress_reached (receiver);

			break;
		}

		//
		// HASTY AIR-TO-GROUND ATTACK GUIDES (HELICOPTERS ONLY)
		//

		case ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_HASTY_FIRE:
		{
			attack_guide_hasty_fire_reached (receiver);

			break;
		}

		case ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_HASTY_TAKE_COVER:
		{
			attack_guide_hasty_take_cover_reached (receiver);

			break;
		}

		default:
		{
			debug_fatal ("GD_MSGS: Invalid guide type %d", get_local_entity_int_value (receiver, INT_TYPE_ENTITY_SUB_TYPE));
		}
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_task_completed (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	entity
		*group;

	task_terminated_types
		task_terminated;

	#if DEBUG_MODULE

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ASSERT (sender);

	ASSERT (get_local_entity_type (sender) == ENTITY_TYPE_TASK);

	task_terminated = (task_terminated_types) va_arg (pargs, int);

	group = get_local_entity_parent (receiver, LIST_TYPE_GUIDE_STACK);
		
	ASSERT (group);

	notify_local_entity (ENTITY_MESSAGE_TASK_COMPLETED, group, receiver, task_terminated);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_task_terminated (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	entity
		*group;

	task_terminated_types
		task_terminated;

	#if DEBUG_MODULE

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ASSERT (sender);

	ASSERT (get_local_entity_type (sender) == ENTITY_TYPE_TASK);

	task_terminated = va_arg (pargs, task_terminated_types);

	group = get_local_entity_parent (receiver, LIST_TYPE_GUIDE_STACK);
		
	ASSERT (group);

	//
	// Inform GROUP ENTITY task terminated 
	//

	notify_local_entity (ENTITY_MESSAGE_TASK_TERMINATED, group, receiver, task_terminated);

	//
	// Destroy GUIDE entity
	//

	//
	// NOTE:- The following two "if" statements are only necessary because notifying the group (above) can currently
	// kill the group (thus destroying the guides itself) if it cannot return to a base.
	// This should be resolved once return tasks are generated with the primary task.
	//

	if (get_local_entity_type (receiver) == ENTITY_TYPE_GUIDE)
	{
		if (get_local_entity_parent (receiver, LIST_TYPE_GUIDE) == sender)
		{
			destroy_client_server_entity (receiver);
		}
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_group_killed (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	entity
		*task;

	int
		task_type;

	#if DEBUG_MODULE

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ASSERT (sender);

	ASSERT (get_local_entity_type (sender) == ENTITY_TYPE_GROUP);

	//
	// Inform TASK ENTITY task terminated  (N.B. This will destroy this GUIDE)
	//

	task = get_local_entity_parent (receiver, LIST_TYPE_GUIDE);
		
	ASSERT (task);
	
	task_type = get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE);

	if (task_database [task_type].persistent_task)
	{
		destroy_client_server_entity (receiver);
	}
	else
	{
		notify_local_entity (ENTITY_MESSAGE_TASK_TERMINATED, task, receiver, TASK_TERMINATED_GROUP_DESTROYED);
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_guide_message_responses (void)
{
	#if DEBUG_MODULE 

	message_responses[ENTITY_TYPE_GUIDE][ENTITY_MESSAGE_LINK_CHILD]				= response_to_link_child;

	message_responses[ENTITY_TYPE_GUIDE][ENTITY_MESSAGE_UNLINK_CHILD]				= response_to_unlink_child;

	message_responses[ENTITY_TYPE_GUIDE][ENTITY_MESSAGE_LINK_PARENT] 				= response_to_link_parent;

	message_responses[ENTITY_TYPE_GUIDE][ENTITY_MESSAGE_UNLINK_PARENT]			= response_to_unlink_parent;

	#endif

	message_responses[ENTITY_TYPE_GUIDE][ENTITY_MESSAGE_WAYPOINT_ACTION]			= response_to_waypoint_action;

	message_responses[ENTITY_TYPE_GUIDE][ENTITY_MESSAGE_WAYPOINT_REACHED]		= response_to_waypoint_reached;

	message_responses[ENTITY_TYPE_GUIDE][ENTITY_MESSAGE_TASK_TERMINATED]			= response_to_task_terminated;

	message_responses[ENTITY_TYPE_GUIDE][ENTITY_MESSAGE_TASK_COMPLETED]			= response_to_task_completed;

	message_responses[ENTITY_TYPE_GUIDE][ENTITY_MESSAGE_GROUP_KILLED]				= response_to_group_killed;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
