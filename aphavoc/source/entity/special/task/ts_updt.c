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

#define DEBUG_MODULE 			0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_server (entity *en)
{
	task
		*raw;

	raw = get_local_entity_data (en);

	#ifdef DEBUG

	validate_task_entity (en);

	#endif

	//
	// Unassigned tasks terminated if expire time
	//	Assigned tasks terminated if stop time reached
	//

	switch (raw->task_state)
	{
		case TASK_STATE_UNASSIGNED:
		{
			//
			// Only decrement the expire timer if the task requires it (i.e. non-zero expire timer)
			//
			
			if (raw->expire_timer > 0.0)
			{
				raw->expire_timer -= get_delta_time ();
		
				if (raw->expire_timer <= 0.0)
				{
					raw->expire_timer = 0.0;
		
					#if DEBUG_MODULE

					debug_log ("TS_UPDT: UNASSIGNED task %d type %s expired", get_local_entity_index (en), entity_sub_type_task_names [raw->sub_type]);

					#endif

					notify_local_entity (ENTITY_MESSAGE_TASK_TERMINATED, en, en, TASK_TERMINATED_EXPIRE_TIME_REACHED);
				}
			}

			break;
		}

		case TASK_STATE_ASSIGNED:
		{
			//
			// Only decrement the stop timer if the task requires it (i.e. non-zero stop timer)
			//

			#ifdef DEBUG

			//
			//
			//

			if (task_database [raw->sub_type].primary_task)
			{
				ASSERT (raw->expire_timer == 0.0);
			}

			#endif
			
			if (raw->stop_timer > 0.0)
			{
				raw->stop_timer -= get_delta_time ();
		
				if (raw->stop_timer <= 0.0)
				{
					raw->stop_timer = 0.0;

					#if DEBUG_MODULE

					debug_log ("TS_UPDT: ASSIGNED task %d type %s reached stop time", get_local_entity_index (en), entity_sub_type_task_names [raw->sub_type]);

					#endif

					notify_local_entity (ENTITY_MESSAGE_TASK_COMPLETED, en, en, TASK_TERMINATED_STOP_TIME_REACHED);
				}
			}

			break;
		}

		case TASK_STATE_COMPLETED:
		{
			//
			// Expire Timer is used to destroy completed tasks after a certain time 
			//

			ASSERT (task_database [raw->sub_type].primary_task);
			
			if (raw->expire_timer > 0.0)
			{
				raw->expire_timer -= get_delta_time ();
		
				if (raw->expire_timer <= 0.0)
				{
					raw->expire_timer = 0.0;
		
					#if DEBUG_MODULE
	
					debug_log ("TS_UPDT: COMPLETED task %d type %s expired", get_local_entity_index (en), entity_sub_type_task_names [raw->sub_type]);
	
					#endif
	
					//
					// Destroy task
					//
				
					destroy_local_entity_family (en);
		
					transmit_entity_comms_message (ENTITY_COMMS_DESTROY_LOCAL_FAMILY, en);
				}
			}
			
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_client (entity *en)
{
	task
		*raw;

	raw = get_local_entity_data (en);

	switch (raw->task_state)
	{
		case TASK_STATE_UNASSIGNED:
		{
			//
			// Only decrement the expire timer if the task requires it (i.e. non-zero expire timer)
			//
			
			if (raw->expire_timer > 0.0)
			{
				raw->expire_timer -= get_delta_time ();
		
				raw->expire_timer = max (raw->expire_timer, 0.0);
			}

			break;
		}

		case TASK_STATE_ASSIGNED:
		{
			//
			// Only decrement the stop timer if the task requires it (i.e. non-zero stop timer)
			//
			
			if (raw->stop_timer > 0.0)
			{
				raw->stop_timer -= get_delta_time ();
		
				raw->stop_timer = max (raw->stop_timer, 0.0);
			}

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_task_update_functions (void)
{
	fn_update_client_server_entity[ENTITY_TYPE_TASK][COMMS_MODEL_SERVER]  	= update_server;

	fn_update_client_server_entity[ENTITY_TYPE_TASK][COMMS_MODEL_CLIENT]  	= update_client;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
