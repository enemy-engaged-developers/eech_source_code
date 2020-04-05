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

static void pack_local_data (entity *en, pack_modes mode)
{
	ASSERT ((mode >= 0) && (mode < NUM_PACK_MODES));

	switch (mode)
	{
		////////////////////////////////////////
		case PACK_MODE_SERVER_SESSION:
		////////////////////////////////////////
		{

			unsigned int
				loop;

			task
				*raw = nullptr;

			raw = (task *) get_local_entity_data (en);

			switch (raw->sub_type)
			{

				case ENTITY_SUB_TYPE_TASK_LANDING:
				case ENTITY_SUB_TYPE_TASK_LANDING_HOLDING:
				case ENTITY_SUB_TYPE_TASK_TAKEOFF:
				case ENTITY_SUB_TYPE_TASK_TAKEOFF_HOLDING:
				{

					return;
				}

				default:
				{

					break;
				}
			}

			pack_entity_type (get_local_entity_type (en));

			pack_entity_safe_ptr (en);

			//
			// pack data (in exactly the same order as the data is unpacked)
			//

			pack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, raw->sub_type);

			// must be packed BEFORE task_link
			pack_int_value (en, INT_TYPE_TASK_STATE, raw->task_state);

			pack_vec3d (en, VEC3D_TYPE_POSITION, &raw->position);

			pack_int_value (en, INT_TYPE_ROUTE_LENGTH, raw->route_length);

			for (loop = 0; loop < raw->route_length; loop ++)
			{

				pack_vec3d (en, VEC3D_TYPE_POSITION, &raw->route_nodes [loop]);
			}

			pack_float_value (en, FLOAT_TYPE_TASK_USER_DATA, raw->task_user_data);

			pack_float_value (en, FLOAT_TYPE_TASK_PRIORITY, raw->task_priority);

			pack_float_value (en, FLOAT_TYPE_RATING, raw->rating);

			pack_float_value (en, FLOAT_TYPE_START_TIME, raw->start_time);

			pack_float_value (en, FLOAT_TYPE_STOP_TIMER, raw->stop_timer);

			pack_float_value (en, FLOAT_TYPE_EXPIRE_TIMER, raw->expire_timer);

			pack_entity_safe_ptr (raw->return_keysite);

			for (loop = 0; loop < raw->route_length; loop ++)
			{
				if (raw->route_dependents [loop])
				{
					pack_int_value (en, INT_TYPE_VALID, TRUE);

					pack_entity_safe_ptr (raw->route_dependents [loop]);
				}
				else
				{
					pack_int_value (en, INT_TYPE_VALID, FALSE);
				}
			}

			for (loop = 0; loop < raw->route_length; loop ++)
			{
				pack_int_value (en, INT_TYPE_WAYPOINT_FORMATION, raw->route_formation_types [loop]);
			}

			for (loop = 0; loop < raw->route_length; loop ++)
			{
				pack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, raw->route_waypoint_types [loop]);
			}

			/////////////////////////////////////////////////////////////////
			if (raw->guide_root.first_child)
			{
				pack_int_value (en, INT_TYPE_VALID, TRUE);

				pack_list_root (en, LIST_TYPE_GUIDE, &raw->guide_root);
			}
			else
			{
				pack_int_value (en, INT_TYPE_VALID, FALSE);
			}
			/////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////
			if (raw->task_dependent_root.first_child)
			{
				pack_int_value (en, INT_TYPE_VALID, TRUE);

				pack_list_root (en, LIST_TYPE_TASK_DEPENDENT, &raw->task_dependent_root);
			}
			else
			{
				pack_int_value (en, INT_TYPE_VALID, FALSE);
			}
			/////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////
			if (raw->waypoint_root.first_child)
			{
				pack_int_value (en, INT_TYPE_VALID, TRUE);

				pack_list_root (en, LIST_TYPE_WAYPOINT, &raw->waypoint_root);
			}
			else
			{
				pack_int_value (en, INT_TYPE_VALID, FALSE);
			}
			/////////////////////////////////////////////////////////////////

			// pilot_lock_link

			/////////////////////////////////////////////////////////////////
			if (raw->sector_task_link.parent)
			{
				pack_int_value (en, INT_TYPE_VALID, TRUE);

				pack_list_link (en, LIST_TYPE_SECTOR_TASK, &raw->sector_task_link);
			}
			else
			{
				pack_int_value (en, INT_TYPE_VALID, FALSE);
			}
			/////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////
			if (raw->task_dependent_link.parent)
			{
				pack_int_value (en, INT_TYPE_VALID, TRUE);

				pack_list_link (en, LIST_TYPE_TASK_DEPENDENT, &raw->task_dependent_link);
			}
			else
			{
				pack_int_value (en, INT_TYPE_VALID, FALSE);
			}
			/////////////////////////////////////////////////////////////////

			pack_list_link (en, get_local_task_list_type (en), &raw->task_link);

			// update link

			pack_int_value (en, INT_TYPE_TASK_TERMINATED, raw->task_terminated);

			/////////////////////////////////////////////////////////////////
			// kill data
			{

				task_kill_loss_data
					*kill = nullptr;

				// kills
					
				kill = raw->task_kills;

				while (kill)
				{

					pack_int_value (en, INT_TYPE_VALID, TRUE);
	
					pack_entity_type (kill->victim_type);
					pack_entity_type (kill->aggressor_type);
	
					pack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, kill->victim_sub_type);
					pack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, kill->aggressor_sub_type);
	
					pack_int_value (en, INT_TYPE_GROUP_MEMBER_NUMBER, kill->victim_id);
					pack_int_value (en, INT_TYPE_GROUP_MEMBER_NUMBER, kill->aggressor_id);
	
					pack_float_value (en, FLOAT_TYPE_TIME_OF_DAY, kill->time);
	
					pack_int_value (en, INT_TYPE_DAY, kill->day);
	
					kill = kill->next;
				}

				pack_int_value (en, INT_TYPE_VALID, FALSE);

				// losses
					
				kill = raw->task_losses;

				while (kill)
				{

					pack_int_value (en, INT_TYPE_VALID, TRUE);
	
					pack_entity_type (kill->victim_type);
					pack_entity_type (kill->aggressor_type);
	
					pack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, kill->victim_sub_type);
					pack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, kill->aggressor_sub_type);
	
					pack_int_value (en, INT_TYPE_GROUP_MEMBER_NUMBER, kill->victim_id);
					pack_int_value (en, INT_TYPE_GROUP_MEMBER_NUMBER, kill->aggressor_id);
	
					pack_float_value (en, FLOAT_TYPE_TIME_OF_DAY, kill->time);
	
					pack_int_value (en, INT_TYPE_DAY, kill->day);
	
					kill = kill->next;
				}

				pack_int_value (en, INT_TYPE_VALID, FALSE);
			}
			/////////////////////////////////////////////////////////////////

			pack_int_value (en, INT_TYPE_AWARDED_MEDALS, raw->awarded_medals);

			pack_int_value (en, INT_TYPE_AWARDED_PROMOTION, raw->awarded_promotion);

			pack_int_value (en, INT_TYPE_TASK_ID, raw->task_id);

			pack_int_value (en, INT_TYPE_TASK_COMPLETED, raw->task_completed);

			// route_check_sum

			pack_int_value (en, INT_TYPE_KILLS, raw->kills);

			pack_int_value (en, INT_TYPE_LOSSES, raw->losses);

			pack_int_value (en, INT_TYPE_PLAYER_TASK, raw->player_task);

			pack_int_value (en, INT_TYPE_MOVEMENT_TYPE, raw->movement_type);

			pack_int_value (en, INT_TYPE_TASK_DIFFICULTY, raw->difficulty);

			pack_int_value (en, INT_TYPE_CRITICAL_TASK, raw->critical_task);

			pack_int_value (en, INT_TYPE_TASK_SCORE, raw->task_score);

			// route length done above

			pack_int_value (en, INT_TYPE_SIDE, raw->side);

			/////////////////////////////////////////////////////////////////
			if (raw->update_link.parent)
			{
				pack_int_value (en, INT_TYPE_VALID, TRUE);
			}
			else
			{
				pack_int_value (en, INT_TYPE_VALID, FALSE);
			}
			/////////////////////////////////////////////////////////////////

			break;
		}
		////////////////////////////////////////
		case PACK_MODE_CLIENT_SESSION:
		////////////////////////////////////////
		{

			unsigned int
				loop;

			task
				*raw = nullptr;

			raw = (task *) get_local_entity_data (en);

			switch (raw->sub_type)
			{

				case ENTITY_SUB_TYPE_TASK_LANDING:
				case ENTITY_SUB_TYPE_TASK_LANDING_HOLDING:
				case ENTITY_SUB_TYPE_TASK_TAKEOFF:
				case ENTITY_SUB_TYPE_TASK_TAKEOFF_HOLDING:
				{

					return;
				}

				default:
				{

					break;
				}
			}

			pack_entity_type (get_local_entity_type (en));

			pack_entity_safe_ptr (en);

			//
			// pack data (in exactly the same order as the data is unpacked)
			//

			pack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, raw->sub_type);

			// must be packed BEFORE task_link
			pack_int_value (en, INT_TYPE_TASK_STATE, raw->task_state);

			pack_vec3d (en, VEC3D_TYPE_POSITION, &raw->position);

			pack_int_value (en, INT_TYPE_ROUTE_LENGTH, raw->route_length);

			for (loop = 0; loop < raw->route_length; loop ++)
			{
				pack_vec3d (en, VEC3D_TYPE_POSITION, &raw->route_nodes [loop]);
			}

			pack_float_value (en, FLOAT_TYPE_TASK_USER_DATA, raw->task_user_data);

			pack_float_value (en, FLOAT_TYPE_TASK_PRIORITY, raw->task_priority);

			pack_float_value (en, FLOAT_TYPE_RATING, raw->rating);

			pack_float_value (en, FLOAT_TYPE_START_TIME, raw->start_time);

			pack_float_value (en, FLOAT_TYPE_STOP_TIMER, raw->stop_timer);

			pack_float_value (en, FLOAT_TYPE_EXPIRE_TIMER, raw->expire_timer);

			pack_entity_safe_ptr (raw->return_keysite);

			for (loop = 0; loop < raw->route_length; loop ++)
			{
				if (raw->route_dependents [loop])
				{
					pack_int_value (en, INT_TYPE_VALID, TRUE);

					pack_entity_safe_ptr (raw->route_dependents [loop]);
				}
				else
				{
					pack_int_value (en, INT_TYPE_VALID, FALSE);
				}
			}

			for (loop = 0; loop < raw->route_length; loop ++)
			{
				pack_int_value (en, INT_TYPE_WAYPOINT_FORMATION, raw->route_formation_types [loop]);
			}

			for (loop = 0; loop < raw->route_length; loop ++)
			{
				pack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, raw->route_waypoint_types [loop]);
			}

			/////////////////////////////////////////////////////////////////
			if (raw->guide_root.first_child)
			{
				pack_int_value (en, INT_TYPE_VALID, TRUE);

				pack_list_root (en, LIST_TYPE_GUIDE, &raw->guide_root);
			}
			else
			{
				pack_int_value (en, INT_TYPE_VALID, FALSE);
			}
			/////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////
			if (raw->player_task_root.first_child)
			{
				pack_int_value (en, INT_TYPE_VALID, TRUE);

				pack_list_root (en, LIST_TYPE_PLAYER_TASK, &raw->player_task_root);
			}
			else
			{
				pack_int_value (en, INT_TYPE_VALID, FALSE);
			}
			/////////////////////////////////////////////////////////////////

			// task_dependent_root

			/////////////////////////////////////////////////////////////////
			if (raw->waypoint_root.first_child)
			{
				pack_int_value (en, INT_TYPE_VALID, TRUE);

				pack_list_root (en, LIST_TYPE_WAYPOINT, &raw->waypoint_root);
			}
			else
			{
				pack_int_value (en, INT_TYPE_VALID, FALSE);
			}
			/////////////////////////////////////////////////////////////////

			pack_list_link (en, LIST_TYPE_PILOT_LOCK, &raw->pilot_lock_link);

			// sector_task_link

			/////////////////////////////////////////////////////////////////
			if (raw->task_dependent_link.parent)
			{
				pack_int_value (en, INT_TYPE_VALID, TRUE);

				pack_list_link (en, LIST_TYPE_TASK_DEPENDENT, &raw->task_dependent_link);
			}
			else
			{
				pack_int_value (en, INT_TYPE_VALID, FALSE);
			}
			/////////////////////////////////////////////////////////////////

			pack_list_link (en, get_local_task_list_type (en), &raw->task_link);

			// update link

			// task_terminated

			/////////////////////////////////////////////////////////////////
			// kill data
			{

				task_kill_loss_data
					*kill = nullptr;
					
				kill = raw->task_kills;

				while (kill)
				{

					pack_int_value (en, INT_TYPE_VALID, TRUE);
	
					pack_entity_type (kill->victim_type);
					pack_entity_type (kill->aggressor_type);
	
					pack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, kill->victim_sub_type);
					pack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, kill->aggressor_sub_type);
	
					pack_int_value (en, INT_TYPE_GROUP_MEMBER_NUMBER, kill->victim_id);
					pack_int_value (en, INT_TYPE_GROUP_MEMBER_NUMBER, kill->aggressor_id);
	
					pack_float_value (en, FLOAT_TYPE_TIME_OF_DAY, kill->time);
	
					pack_int_value (en, INT_TYPE_DAY, kill->day);
	
					kill = kill->next;
				}

				pack_int_value (en, INT_TYPE_VALID, FALSE);
					
				kill = raw->task_losses;

				while (kill)
				{

					pack_int_value (en, INT_TYPE_VALID, TRUE);
	
					pack_entity_type (kill->victim_type);
					pack_entity_type (kill->aggressor_type);
	
					pack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, kill->victim_sub_type);
					pack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, kill->aggressor_sub_type);
	
					pack_int_value (en, INT_TYPE_GROUP_MEMBER_NUMBER, kill->victim_id);
					pack_int_value (en, INT_TYPE_GROUP_MEMBER_NUMBER, kill->aggressor_id);
	
					pack_float_value (en, FLOAT_TYPE_TIME_OF_DAY, kill->time);
	
					pack_int_value (en, INT_TYPE_DAY, kill->day);
	
					kill = kill->next;
				}

				pack_int_value (en, INT_TYPE_VALID, FALSE);
			}
			/////////////////////////////////////////////////////////////////

			// awarded medals

			// awarded promotion

			pack_int_value (en, INT_TYPE_TASK_ID, raw->task_id);

			pack_int_value (en, INT_TYPE_TASK_COMPLETED, raw->task_completed);

			// route_check_sum

			pack_int_value (en, INT_TYPE_KILLS, raw->kills);

			pack_int_value (en, INT_TYPE_LOSSES, raw->losses);

			// player_task

			pack_int_value (en, INT_TYPE_MOVEMENT_TYPE, raw->movement_type);

			pack_int_value (en, INT_TYPE_TASK_DIFFICULTY, raw->difficulty);

			// critical_task

			pack_int_value (en, INT_TYPE_TASK_SCORE, raw->task_score);

			// route_length

			pack_int_value (en, INT_TYPE_SIDE, raw->side);
	
			/////////////////////////////////////////////////////////////////
			if (raw->update_link.parent)
			{
				pack_int_value (en, INT_TYPE_VALID, TRUE);
			}
			else
			{
				pack_int_value (en, INT_TYPE_VALID, FALSE);
			}
			/////////////////////////////////////////////////////////////////

			break;
		}
		////////////////////////////////////////
		case PACK_MODE_BROWSE_SESSION:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case PACK_MODE_UPDATE_ENTITY:
		////////////////////////////////////////
		{
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void unpack_local_data (entity *en, entity_types type, pack_modes mode)
{
	ASSERT ((mode >= 0) && (mode < NUM_PACK_MODES));

	switch (mode)
	{
		////////////////////////////////////////
		case PACK_MODE_SERVER_SESSION:
		////////////////////////////////////////
		{
			unsigned int
				loop;

			int
				index;

			task
				*raw = nullptr;

			//
			// create entity
			//

			index = unpack_entity_safe_index ();

			en = get_free_entity (index);

			set_local_entity_type (en, type);

			raw = (task *) malloc_fast_mem (sizeof (task));

			set_local_entity_data (en, raw);

			memset (raw, 0, sizeof (task));

			//
			// unpack data (in exactly the same order as the data was packed)
			//

			raw->sub_type = unpack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);

			raw->task_state = (task_state_types) unpack_int_value (en, INT_TYPE_TASK_STATE);

			unpack_vec3d (en, VEC3D_TYPE_POSITION, &raw->position);

			raw->route_length = unpack_int_value (en, INT_TYPE_ROUTE_LENGTH);

			if (raw->route_length)
			{
	
				raw->route_nodes = (vec3d *) malloc_heap_mem (sizeof (vec3d) * (raw->route_length));
	
				for (loop = 0; loop < raw->route_length; loop ++)
				{

					unpack_vec3d (en, VEC3D_TYPE_POSITION, &raw->route_nodes [loop]);
				}
			}

			raw->task_user_data = unpack_float_value (en, FLOAT_TYPE_TASK_USER_DATA);

			raw->task_priority = unpack_float_value (en, FLOAT_TYPE_TASK_PRIORITY);

			raw->rating = unpack_float_value (en, FLOAT_TYPE_RATING);

			raw->start_time = unpack_float_value (en, FLOAT_TYPE_START_TIME);

			raw->stop_timer = unpack_float_value (en, FLOAT_TYPE_STOP_TIMER);

			raw->expire_timer = unpack_float_value (en, FLOAT_TYPE_EXPIRE_TIMER);

			raw->return_keysite = unpack_entity_safe_ptr ();

			if (raw->route_length)
			{

				raw->route_dependents = (entity **) malloc_heap_mem (sizeof (entity *) * raw->route_length);
	
				for (loop = 0; loop < raw->route_length; loop ++)
				{

					if (unpack_int_value (en, INT_TYPE_VALID))
					{
	
						raw->route_dependents [loop] = unpack_entity_safe_ptr ();
					}
					else
					{

						raw->route_dependents [loop] = NULL;
					}
				}

				raw->route_formation_types = (formation_types *) malloc_heap_mem (sizeof (formation_types) * raw->route_length);
	
				for (loop = 0; loop < raw->route_length; loop ++)
				{
	
					raw->route_formation_types [loop] = (formation_types) unpack_int_value (en, INT_TYPE_WAYPOINT_FORMATION);
				}
	
				raw->route_waypoint_types = (entity_sub_types *) malloc_heap_mem (sizeof (entity_sub_types) * raw->route_length);
	
				for (loop = 0; loop < raw->route_length; loop ++)
				{
	
					raw->route_waypoint_types [loop] = unpack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);
				}
			}

			/////////////////////////////////////////////////////////////////
			if (unpack_int_value (en, INT_TYPE_VALID))
			{

				unpack_list_root (en, LIST_TYPE_GUIDE, &raw->guide_root);
			}
			/////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////
			if (unpack_int_value (en, INT_TYPE_VALID))
			{

				unpack_list_root (en, LIST_TYPE_TASK_DEPENDENT, &raw->task_dependent_root);
			}
			/////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////
			if (unpack_int_value (en, INT_TYPE_VALID))
			{

				unpack_list_root (en, LIST_TYPE_WAYPOINT, &raw->waypoint_root);
			}
			/////////////////////////////////////////////////////////////////

			// pilot_lock_link

			/////////////////////////////////////////////////////////////////
			if (unpack_int_value (en, INT_TYPE_VALID))
			{

				unpack_list_link (en, LIST_TYPE_SECTOR_TASK, &raw->sector_task_link);
			}
			/////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////
			if (unpack_int_value (en, INT_TYPE_VALID))
			{

				unpack_list_link (en, LIST_TYPE_TASK_DEPENDENT, &raw->task_dependent_link);
			}
			/////////////////////////////////////////////////////////////////

			unpack_list_link (en, get_local_task_list_type (en), &raw->task_link);

			// update_link 

			raw->task_terminated = (task_terminated_types) unpack_int_value (en, INT_TYPE_TASK_TERMINATED);

			/////////////////////////////////////////////////////////////////
			// kill/loss data
			{

				task_kill_loss_data
					*last_kill = nullptr,
					*kill = nullptr;

				// kills

				ASSERT (!raw->task_kills);

				kill = NULL;

				last_kill = NULL;

				while (unpack_int_value (en, INT_TYPE_VALID))
				{

					kill = (task_kill_loss_data *) malloc_heap_mem (sizeof (task_kill_loss_data));

					memset (kill, 0, sizeof (task_kill_loss_data));
	
					kill->victim_type = unpack_entity_type ();
					kill->aggressor_type = unpack_entity_type ();
	
					kill->victim_sub_type = unpack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);
					kill->aggressor_sub_type = unpack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);
	
					kill->victim_id = unpack_int_value (en, INT_TYPE_GROUP_MEMBER_NUMBER);
					kill->aggressor_id = unpack_int_value (en, INT_TYPE_GROUP_MEMBER_NUMBER);
	
					kill->time = unpack_float_value (en, FLOAT_TYPE_TIME_OF_DAY);
	
					kill->day = unpack_int_value (en, INT_TYPE_DAY);
	
					kill->next = last_kill;
					last_kill = kill;
				}

				raw->task_kills = kill;

				// losses

				ASSERT (!raw->task_losses);

				kill = NULL;

				last_kill = NULL;
					
				while (unpack_int_value (en, INT_TYPE_VALID))
				{

					kill = (task_kill_loss_data *) malloc_heap_mem (sizeof (task_kill_loss_data));

					memset (kill, 0, sizeof (task_kill_loss_data));
	
					kill->victim_type = unpack_entity_type ();
					kill->aggressor_type = unpack_entity_type ();
	
					kill->victim_sub_type = unpack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);
					kill->aggressor_sub_type = unpack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);
	
					kill->victim_id = unpack_int_value (en, INT_TYPE_GROUP_MEMBER_NUMBER);
					kill->aggressor_id = unpack_int_value (en, INT_TYPE_GROUP_MEMBER_NUMBER);
	
					kill->time = unpack_float_value (en, FLOAT_TYPE_TIME_OF_DAY);
	
					kill->day = unpack_int_value (en, INT_TYPE_DAY);
	
					kill->next = last_kill;
					last_kill = kill;
				}

				raw->task_losses = kill;
			}
			/////////////////////////////////////////////////////////////////

			raw->awarded_medals = unpack_int_value (en, INT_TYPE_AWARDED_MEDALS);

			raw->awarded_promotion = unpack_int_value (en, INT_TYPE_AWARDED_PROMOTION);

			raw->task_id = unpack_int_value (en, INT_TYPE_TASK_ID);

			raw->task_completed = unpack_int_value (en, INT_TYPE_TASK_COMPLETED);

			// route_check_sum

			raw->kills = unpack_int_value (en, INT_TYPE_KILLS);

			raw->losses = unpack_int_value (en, INT_TYPE_LOSSES);

			raw->player_task = unpack_int_value (en, INT_TYPE_PLAYER_TASK);

			raw->movement_type = unpack_int_value (en, INT_TYPE_MOVEMENT_TYPE);

			raw->difficulty = unpack_int_value (en, INT_TYPE_TASK_DIFFICULTY);

			raw->critical_task = unpack_int_value (en, INT_TYPE_CRITICAL_TASK);

			raw->task_score = unpack_int_value (en, INT_TYPE_TASK_SCORE);

			// route_length done above

			raw->side = unpack_int_value (en, INT_TYPE_SIDE);

			//
			// link into system
			//

			if (unpack_int_value (en, INT_TYPE_VALID))
			{
				insert_local_entity_into_parents_child_list (en, LIST_TYPE_UPDATE, get_update_entity (), NULL);
			}
	
			break;
		}
		////////////////////////////////////////
		case PACK_MODE_CLIENT_SESSION:
		////////////////////////////////////////
		{
			unsigned int
				loop;

			int
				index;

			task
				*raw = nullptr;

			//
			// create entity
			//

			index = unpack_entity_safe_index ();

			en = get_free_entity (index);

			set_local_entity_type (en, type);

			raw = (task *) malloc_fast_mem (sizeof (task));

			set_local_entity_data (en, raw);

			memset (raw, 0, sizeof (task));

			//
			// unpack data (in exactly the same order as the data was packed)
			//

			raw->sub_type = unpack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);

			raw->task_state = (task_state_types) unpack_int_value (en, INT_TYPE_TASK_STATE);

			unpack_vec3d (en, VEC3D_TYPE_POSITION, &raw->position);

			raw->route_length = unpack_int_value (en, INT_TYPE_ROUTE_LENGTH);

			if (raw->route_length > 0)
			{
	
				raw->route_nodes = (vec3d *) malloc_heap_mem (sizeof (vec3d) * (raw->route_length));
	
				for (loop = 0; loop < raw->route_length; loop ++)
				{
	
					unpack_vec3d (en, VEC3D_TYPE_POSITION, &raw->route_nodes [loop]);
				}
			}

			raw->task_user_data = unpack_float_value (en, FLOAT_TYPE_TASK_USER_DATA);

			raw->task_priority = unpack_float_value (en, FLOAT_TYPE_TASK_PRIORITY);

			raw->rating = unpack_float_value (en, FLOAT_TYPE_RATING);

			raw->start_time = unpack_float_value (en, FLOAT_TYPE_START_TIME);

			raw->stop_timer = unpack_float_value (en, FLOAT_TYPE_STOP_TIMER);

			raw->expire_timer = unpack_float_value (en, FLOAT_TYPE_EXPIRE_TIMER);

			raw->return_keysite = unpack_entity_safe_ptr ();

			if (raw->route_length)
			{

				raw->route_dependents = (entity **) malloc_heap_mem (sizeof (entity *) * raw->route_length);
	
				for (loop = 0; loop < raw->route_length; loop ++)
				{

					if (unpack_int_value (en, INT_TYPE_VALID))
					{
	
						raw->route_dependents [loop] = unpack_entity_safe_ptr ();
					}
					else
					{

						raw->route_dependents [loop] = NULL;
					}
				}

				raw->route_formation_types = (formation_types *) malloc_heap_mem (sizeof (formation_types) * raw->route_length);
	
				for (loop = 0; loop < raw->route_length; loop ++)
				{
	
					raw->route_formation_types [loop] = (formation_types) unpack_int_value (en, INT_TYPE_WAYPOINT_FORMATION);
				}
	
				raw->route_waypoint_types = (entity_sub_types *) malloc_heap_mem (sizeof (entity_sub_types) * raw->route_length);
	
				for (loop = 0; loop < raw->route_length; loop ++)
				{
	
					raw->route_waypoint_types [loop] = unpack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);
				}
			}

			/////////////////////////////////////////////////////////////////
			if (unpack_int_value (en, INT_TYPE_VALID))
			{

				unpack_list_root (en, LIST_TYPE_GUIDE, &raw->guide_root);
			}
			/////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////
			if (unpack_int_value (en, INT_TYPE_VALID))
			{

				unpack_list_root (en, LIST_TYPE_PLAYER_TASK, &raw->player_task_root);
			}
			/////////////////////////////////////////////////////////////////

			// task_dependent_root

			/////////////////////////////////////////////////////////////////
			if (unpack_int_value (en, INT_TYPE_VALID))
			{

				unpack_list_root (en, LIST_TYPE_WAYPOINT, &raw->waypoint_root);
			}
			/////////////////////////////////////////////////////////////////

			unpack_list_link (en, LIST_TYPE_PILOT_LOCK, &raw->pilot_lock_link);

			// sector_task_link

			/////////////////////////////////////////////////////////////////
			if (unpack_int_value (en, INT_TYPE_VALID))
			{

				unpack_list_link (en, LIST_TYPE_TASK_DEPENDENT, &raw->task_dependent_link);
			}
			/////////////////////////////////////////////////////////////////

			unpack_list_link (en, get_local_task_list_type (en), &raw->task_link);

			// update_link

			// task_terminated

			/////////////////////////////////////////////////////////////////
			// kill/loss data
			{

				task_kill_loss_data
					*last_kill = nullptr,
					*kill = nullptr;

				// kills

				ASSERT (!raw->task_kills);

				kill = NULL;

				last_kill = NULL;

				while (unpack_int_value (en, INT_TYPE_VALID))
				{

					kill = (task_kill_loss_data *) malloc_heap_mem (sizeof (task_kill_loss_data));

					memset (kill, 0, sizeof (task_kill_loss_data));
	
					kill->victim_type = unpack_entity_type ();
					kill->aggressor_type = unpack_entity_type ();
	
					kill->victim_sub_type = unpack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);
					kill->aggressor_sub_type = unpack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);
	
					kill->victim_id = unpack_int_value (en, INT_TYPE_GROUP_MEMBER_NUMBER);
					kill->aggressor_id = unpack_int_value (en, INT_TYPE_GROUP_MEMBER_NUMBER);
	
					kill->time = unpack_float_value (en, FLOAT_TYPE_TIME_OF_DAY);
	
					kill->day = unpack_int_value (en, INT_TYPE_DAY);
	
					kill->next = last_kill;
					last_kill = kill;
				}

				raw->task_kills = kill;

				// losses

				ASSERT (!raw->task_losses);

				kill = NULL;

				last_kill = NULL;
					
				while (unpack_int_value (en, INT_TYPE_VALID))
				{

					kill = (task_kill_loss_data *) malloc_heap_mem (sizeof (task_kill_loss_data));

					memset (kill, 0, sizeof (task_kill_loss_data));
	
					kill->victim_type = unpack_entity_type ();
					kill->aggressor_type = unpack_entity_type ();
	
					kill->victim_sub_type = unpack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);
					kill->aggressor_sub_type = unpack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);
	
					kill->victim_id = unpack_int_value (en, INT_TYPE_GROUP_MEMBER_NUMBER);
					kill->aggressor_id = unpack_int_value (en, INT_TYPE_GROUP_MEMBER_NUMBER);
	
					kill->time = unpack_float_value (en, FLOAT_TYPE_TIME_OF_DAY);
	
					kill->day = unpack_int_value (en, INT_TYPE_DAY);
	
					kill->next = last_kill;
					last_kill = kill;
				}

				raw->task_losses = kill;
			}
			/////////////////////////////////////////////////////////////////

			// awarded medals

			// awarded promotion

			raw->task_id = unpack_int_value (en, INT_TYPE_TASK_ID);

			raw->task_completed = unpack_int_value (en, INT_TYPE_TASK_COMPLETED);

			// route_check_sum

			raw->kills = unpack_int_value (en, INT_TYPE_KILLS);

			raw->losses = unpack_int_value (en, INT_TYPE_LOSSES);

			// player_task

			raw->movement_type = unpack_int_value (en, INT_TYPE_MOVEMENT_TYPE);

			raw->difficulty = unpack_int_value (en, INT_TYPE_TASK_DIFFICULTY);

			// critical_task

			raw->task_score = unpack_int_value (en, INT_TYPE_TASK_SCORE);

			// route_length

			raw->side = unpack_int_value (en, INT_TYPE_SIDE);

			//
			// link into system
			//

			if (unpack_int_value (en, INT_TYPE_VALID))
			{
				insert_local_entity_into_parents_child_list (en, LIST_TYPE_UPDATE, get_update_entity (), NULL);
			}
	
			break;
		}
		////////////////////////////////////////
		case PACK_MODE_BROWSE_SESSION:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case PACK_MODE_UPDATE_ENTITY:
		////////////////////////////////////////
		{
			//
			// always use access functions to set the data
			//

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_task_pack_functions (void)
{
	fn_pack_local_entity_data[ENTITY_TYPE_TASK]		= pack_local_data;

	fn_unpack_local_entity_data[ENTITY_TYPE_TASK]	= unpack_local_data;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
