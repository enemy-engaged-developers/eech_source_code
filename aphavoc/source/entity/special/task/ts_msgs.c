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

/////////////////////////////////////////////////////
//
// 2 levels of debug
//
/////////////////////////////////////////////////////

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

static int response_to_link_parent (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	list_types
		list_type;

	entity_sub_types
		sub_type;

	#if DEBUG_MODULE >= 2

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	//
	// notify campaign screen
	//

	list_type = va_arg (pargs, list_types);

	sub_type = get_local_entity_int_value (receiver, INT_TYPE_ENTITY_SUB_TYPE);

	switch (list_type)
	{
		////////////////////////////////////////
		case LIST_TYPE_UNASSIGNED_TASK:
		////////////////////////////////////////
		{
			set_local_entity_int_value (receiver, INT_TYPE_TASK_STATE, TASK_STATE_UNASSIGNED);

			if (task_database [sub_type].primary_task)
			{
				notify_campaign_screen (CAMPAIGN_SCREEN_MISSION_CREATED, receiver);
			}

			break;
		}
		////////////////////////////////////////
		case LIST_TYPE_ASSIGNED_TASK:
		////////////////////////////////////////
		{
			set_local_entity_int_value (receiver, INT_TYPE_TASK_STATE, TASK_STATE_ASSIGNED);

			if (task_database [sub_type].primary_task)
			{
				notify_campaign_screen (CAMPAIGN_SCREEN_MISSION_ASSIGNED, receiver);
			}

			break;
		}
		////////////////////////////////////////
		case LIST_TYPE_COMPLETED_TASK:
		////////////////////////////////////////
		{
			set_local_entity_int_value (receiver, INT_TYPE_TASK_STATE, TASK_STATE_COMPLETED);

			if (task_database [sub_type].primary_task)
			{
				notify_campaign_screen (CAMPAIGN_SCREEN_MISSION_COMPLETED, receiver);
			}

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

static int response_to_set_entity_position (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	vec3d
		*position;

	float
		velocity,
		heading;

	entity
		*wp;

	task
		*raw;

	raw = (task *) get_local_entity_data (receiver);

	position = va_arg (pargs, vec3d *);

	heading = (float) va_arg (pargs, double);

	velocity = (float) va_arg (pargs, double);

	#if DEBUG_MODULE

	debug_log ("TS_MSGS: setting position %f, %f, %f, heading %f",
					position->x, position->y, position->z, heading);

	#endif

	wp = raw->waypoint_root.first_child;

	//
	// notify all waypoints of movement, before setting position so children can calculate delta movement.
	//

	while (wp)
	{

		notify_local_entity (ENTITY_MESSAGE_SET_ENTITY_POSITION, wp, receiver, position, (double) heading, (double) velocity);

		wp = get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT);
	}

	//
	// actually set position
	//

	set_local_entity_vec3d (receiver, VEC3D_TYPE_POSITION, position);

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_task_completed (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	task
		*raw;

	entity
		*force,
		*guide,
		*list_parent;

	task_terminated_types
		task_terminated;

	task_completed_types
		task_completed;

	#if DEBUG_MODULE >= 2

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	task_terminated = (task_terminated_types) va_arg (pargs, int);

	raw = (task *) get_local_entity_data (receiver);

	if (raw->task_completed == TASK_INCOMPLETE)
	{
		if (task_database [raw->sub_type].primary_task)
		{
			switch (raw->task_state)
			{
				case TASK_STATE_UNASSIGNED:
				{
					//
					// Terminate task
					//
	
					set_client_server_entity_int_value (receiver, INT_TYPE_TASK_COMPLETED, TASK_COMPLETED_FAILURE);

					notify_local_entity (ENTITY_MESSAGE_TASK_TERMINATED, receiver, sender, TASK_TERMINATED_OBJECTIVE_MESSAGE);

					break;
				}
				case TASK_STATE_ASSIGNED:
				{
					//
					// Assess task rating
					//
					
					task_completed = assess_task_completeness (receiver, task_terminated);

					if (task_completed != TASK_INCOMPLETE)
					{
						ASSERT (task_completed != raw->task_completed);
	
						set_client_server_entity_int_value (receiver, INT_TYPE_TASK_COMPLETED, task_completed);

//						#if DEBUG_MODULE
					
						debug_colour_log (DEBUG_COLOUR_GREEN, "TS_MSGS: %s Task %s (%d) completed - Rating %.1f (%s)",
													entity_side_names [get_local_entity_int_value (receiver, INT_TYPE_SIDE)],
													get_local_entity_string (receiver, STRING_TYPE_FULL_NAME),
													get_local_entity_index (receiver),
													(get_local_entity_float_value (receiver, FLOAT_TYPE_RATING) * 100.0),
													task_terminated_names [task_terminated]
												);

//						#endif

						//
						// Award Task Points
						//

						award_points_for_task_completion (receiver);

						//
						// Notify force 
						//		
			
						force = get_local_force_entity ((entity_sides) raw->side);
	
						notify_local_entity (ENTITY_MESSAGE_TASK_COMPLETED, force, receiver, task_terminated);

						//
						// move the task to the sessions completed task list
						//

						list_parent = get_local_entity_parent (receiver, LIST_TYPE_ASSIGNED_TASK);

						ASSERT (list_parent);

						set_client_server_entity_parent (receiver, LIST_TYPE_ASSIGNED_TASK, NULL);

						set_client_server_entity_parent (receiver, LIST_TYPE_COMPLETED_TASK, list_parent);

						//
						// Notify Guide which will inform group and return them to base
						//
					
						guide = get_local_entity_first_child (receiver, LIST_TYPE_GUIDE);
					
						while (guide)
						{
							notify_local_entity (ENTITY_MESSAGE_TASK_COMPLETED, guide, receiver, task_terminated);
					
							guide = get_local_entity_child_succ (guide, LIST_TYPE_GUIDE);
						}
					}

					break;
				}
			}
		}
		else
		{
			//
			// Terminate task
			//

			set_client_server_entity_int_value (receiver, INT_TYPE_TASK_COMPLETED, TASK_COMPLETED_FAILURE);

			notify_local_entity (ENTITY_MESSAGE_TASK_TERMINATED, receiver, sender, TASK_TERMINATED_OBJECTIVE_MESSAGE);
		}
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_task_terminated (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	task
		*raw;

	entity
		*guide,
		*next,
		*en;

	task_terminated_types
		task_terminated;

	#if DEBUG_MODULE >= 2

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	raw = (task *) get_local_entity_data (receiver);

	if (task_database [raw->sub_type].persistent_task)
	{
		//
		// Landing / Takeoff etc SHOULD NOT be terminated
		//

		debug_fatal ("TS_MSGS: Task %s incorrectly terminated", get_local_entity_string (receiver, STRING_TYPE_FULL_NAME));
	}

	//
	// Check for cyclic conditions
	//

	if (raw->task_terminated != TASK_TERMINATED_IN_PROGRESS)
	{
		return FALSE;
	}

	task_terminated = va_arg (pargs, task_terminated_types);

	#if DEBUG_MODULE

	debug_log ("TS_MSGS: task terminated %s (%d) %s",
					get_local_entity_string (receiver, STRING_TYPE_FULL_NAME),
					get_local_entity_index (receiver),
					task_terminated_names [task_terminated]);

	#endif

	raw->task_terminated = task_terminated;

	//
	// Call completed code also
	//

	if (raw->task_completed == TASK_INCOMPLETE)
	{
		notify_local_entity (ENTITY_MESSAGE_TASK_COMPLETED, receiver, sender, task_terminated);
	}

	//
	// Inform dependents task terminated
	//

	en = get_local_entity_first_child (receiver, LIST_TYPE_TASK_DEPENDENT);

	while (en)
	{
		next = get_local_entity_child_succ (en, LIST_TYPE_TASK_DEPENDENT);

		if (en != sender)
		{
			notify_local_entity (ENTITY_MESSAGE_TASK_COMPLETED, en, receiver, task_terminated);
		}

		en = next;
	}

	ASSERT (get_local_entity_type (receiver) == ENTITY_TYPE_TASK);		// Check task has not been prematurely destroyed by dependents

	//
	// Inform GUIDE ENTITY task terminated (This will sever all links between the task and it's guide / group / members etc.)
	//

	do
	{
		guide = get_local_entity_first_child (receiver, LIST_TYPE_GUIDE);

		if (guide)
		{
			notify_local_entity (ENTITY_MESSAGE_TASK_TERMINATED, guide, receiver, task_terminated);
		}
	}
	while (guide);

	if ((raw->task_state != TASK_STATE_UNASSIGNED) && (task_database [raw->sub_type].visible_task))
	{
		//
		// Destroy Links
		//
	
		ASSERT (task_database [raw->sub_type].primary_task);

		kill_client_server_entity (receiver);
	}
	else
	{
		//
		// Destroy task
		//
			
		destroy_local_entity_family (receiver);
	
		transmit_entity_comms_message (ENTITY_COMMS_DESTROY_LOCAL_FAMILY, receiver);
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_task_message_responses (void)
{

	#if DEBUG_MODULE >= 2

	message_responses[ENTITY_TYPE_TASK][ENTITY_MESSAGE_LINK_CHILD] 						= response_to_link_child;

	message_responses[ENTITY_TYPE_TASK][ENTITY_MESSAGE_UNLINK_CHILD]						= response_to_unlink_child;

	message_responses[ENTITY_TYPE_TASK][ENTITY_MESSAGE_UNLINK_PARENT]						= response_to_unlink_parent;

	#endif

	message_responses[ENTITY_TYPE_TASK][ENTITY_MESSAGE_LINK_PARENT]						= response_to_link_parent;

	message_responses[ENTITY_TYPE_TASK][ENTITY_MESSAGE_SET_ENTITY_POSITION]				= response_to_set_entity_position;

	message_responses[ENTITY_TYPE_TASK][ENTITY_MESSAGE_TASK_COMPLETED] 					= response_to_task_completed;

	message_responses[ENTITY_TYPE_TASK][ENTITY_MESSAGE_TASK_TERMINATED] 					= response_to_task_terminated;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////










