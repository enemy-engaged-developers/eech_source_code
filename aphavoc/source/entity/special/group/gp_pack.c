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
			group
				*raw;

			raw = (group *) get_local_entity_data (en);

			if (group_database [raw->sub_type].local_only_group)
			{
				return;
			}

			pack_entity_type (get_local_entity_type (en));

			pack_entity_safe_ptr (en);

			//
			// pack data (in exactly the same order as the data is unpacked)
			//

			pack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, raw->sub_type);

			pack_list_root (en, LIST_TYPE_MEMBER, &raw->member_root);

			/////////////////////////////////////////////////////////////////
			if (raw->guide_stack_root.first_child)
			{

				pack_int_value (en, INT_TYPE_VALID, TRUE);

				pack_list_root (en, LIST_TYPE_GUIDE_STACK, &raw->guide_stack_root);
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

			pack_int_value (en, INT_TYPE_GROUP_LIST_TYPE, raw->group_list_type);

			pack_entity_safe_ptr (raw->group_link.parent);
//			pack_list_link (en, raw->group_list_type, &raw->group_link);

			pack_list_link (en, LIST_TYPE_DIVISION, &raw->division_link);

			// update_link

			pack_float_value (en, FLOAT_TYPE_SLEEP, raw->sleep);

			pack_float_value (en, FLOAT_TYPE_LAST_SEEN_TIME, raw->last_seen_time);

			pack_float_value (en, FLOAT_TYPE_ASSIST_TIMER, raw->assist_timer);

			pack_float_value (en, FLOAT_TYPE_LAST_SEEN_TIME, raw->last_seen_time);

			pack_vec3d (en, VEC3D_TYPE_LAST_KNOWN_POSITION, &raw->last_known_position);

			// supplies
			
			pack_int_value (en, INT_TYPE_ALIVE, raw->alive);

			pack_int_value (en, INT_TYPE_ENGAGE_ENEMY, raw->engage_enemy);

			pack_int_value (en, INT_TYPE_GROUP_CALLSIGN, raw->group_callsign);
			
			pack_int_value (en, INT_TYPE_GROUP_FORMATION, raw->group_formation);
			
			pack_int_value (en, INT_TYPE_KILLS, raw->kills);

			pack_int_value (en, INT_TYPE_LOSSES, raw->losses);

			pack_int_value (en, INT_TYPE_MEMBER_COUNT, raw->member_count);

			pack_int_value (en, INT_TYPE_VERBOSE_OPERATIONAL_STATE, raw->verbose_operational_state);

			// unique_id
			
			pack_int_value (en, INT_TYPE_ROUTE_NODE, raw->route_node);
			
			pack_int_value (en, INT_TYPE_SIDE, raw->side);

			// pack whether the group should be on the update list
			if (raw->update_link.parent)
			{
				pack_int_value (en, INT_TYPE_VALID, TRUE);
			}
			else
			{
				pack_int_value (en, INT_TYPE_VALID, FALSE);
			}

			break;
		}
		////////////////////////////////////////
		case PACK_MODE_CLIENT_SESSION:
		////////////////////////////////////////
		{
			group
				*raw;

			raw = (group *) get_local_entity_data (en);

			if (group_database [raw->sub_type].local_only_group)
			{
				return;
			}

			pack_entity_type (get_local_entity_type (en));

			pack_entity_safe_ptr (en);

			//
			// pack data (in exactly the same order as the data is unpacked)
			//

			pack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, raw->sub_type);

			pack_list_root (en, LIST_TYPE_MEMBER, &raw->member_root);

			/////////////////////////////////////////////////////////////////
			if (raw->guide_stack_root.first_child)
			{

				pack_int_value (en, INT_TYPE_VALID, TRUE);

				pack_list_root (en, LIST_TYPE_GUIDE_STACK, &raw->guide_stack_root);
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

			// task_dependent_link

			pack_int_value (en, INT_TYPE_GROUP_LIST_TYPE, raw->group_list_type);

//			pack_list_link (en, raw->group_list_type, &raw->group_link);
			pack_entity_safe_ptr (raw->group_link.parent);

			pack_list_link (en, LIST_TYPE_DIVISION, &raw->division_link);

			pack_list_link (en, LIST_TYPE_PILOT_LOCK, &raw->pilot_lock_link);

			// update_link

			// sleep

			// assist timer

			pack_float_value (en, FLOAT_TYPE_LAST_SEEN_TIME, raw->last_seen_time);

			pack_vec3d (en, VEC3D_TYPE_LAST_KNOWN_POSITION, &raw->last_known_position);

			// supplies
			
			pack_int_value (en, INT_TYPE_ALIVE, raw->alive);

			// engage_enemy

			pack_int_value (en, INT_TYPE_GROUP_CALLSIGN, raw->group_callsign);

			pack_int_value (en, INT_TYPE_GROUP_FORMATION, raw->group_formation);
			
			pack_int_value (en, INT_TYPE_KILLS, raw->kills);

			pack_int_value (en, INT_TYPE_LOSSES, raw->losses);

			pack_int_value (en, INT_TYPE_MEMBER_COUNT, raw->member_count);

			pack_int_value (en, INT_TYPE_VERBOSE_OPERATIONAL_STATE, raw->verbose_operational_state);

			// unique_id

			// route_node

			pack_int_value (en, INT_TYPE_SIDE, raw->side);

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
			int
				index;

			group
				*raw;

			//
			// create entity
			//

			index = unpack_entity_safe_index ();

			en = get_free_entity (index);

			set_local_entity_type (en, type);

			raw = (group *) malloc_fast_mem (sizeof (group));

			set_local_entity_data (en, raw);

			memset (raw, 0, sizeof (group));

			//
			// unpack data (in exactly the same order as the data was packed)
			//

			raw->sub_type = unpack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);

			unpack_list_root (en, LIST_TYPE_MEMBER, &raw->member_root);

			/////////////////////////////////////////////////////////////////
			if (unpack_int_value (en, INT_TYPE_VALID))
			{

				unpack_list_root (en, LIST_TYPE_GUIDE_STACK, &raw->guide_stack_root);
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

				unpack_list_link (en, LIST_TYPE_TASK_DEPENDENT, &raw->task_dependent_link);
			}
			/////////////////////////////////////////////////////////////////

			raw->group_list_type = (list_types) unpack_int_value (en, INT_TYPE_GROUP_LIST_TYPE);

//			unpack_list_link (en, raw->group_list_type, &raw->group_link);
			raw->group_link.parent = unpack_entity_safe_ptr ();

			unpack_list_link (en, LIST_TYPE_DIVISION, &raw->division_link);

			// update_link

			raw->sleep = unpack_float_value (en, FLOAT_TYPE_SLEEP);

			raw->last_seen_time = unpack_float_value (en, FLOAT_TYPE_LAST_SEEN_TIME);

			raw->assist_timer = unpack_float_value (en, FLOAT_TYPE_ASSIST_TIMER);

			raw->last_seen_time = unpack_float_value (en, FLOAT_TYPE_LAST_SEEN_TIME);

			unpack_vec3d (en, VEC3D_TYPE_LAST_KNOWN_POSITION, &raw->last_known_position);

			// supplies

			raw->alive = unpack_int_value (en, INT_TYPE_ALIVE);

			raw->engage_enemy = unpack_int_value (en, INT_TYPE_ENGAGE_ENEMY);

			raw->group_callsign = unpack_int_value (en, INT_TYPE_GROUP_CALLSIGN);

			raw->group_formation = unpack_int_value (en, INT_TYPE_GROUP_FORMATION);

			raw->kills = unpack_int_value (en, INT_TYPE_KILLS);

			raw->losses = unpack_int_value (en, INT_TYPE_LOSSES);

			raw->member_count = unpack_int_value (en, INT_TYPE_MEMBER_COUNT);

			raw->verbose_operational_state = unpack_int_value (en, INT_TYPE_VERBOSE_OPERATIONAL_STATE);

			// unique_id

			raw->route_node = unpack_int_value (en, INT_TYPE_ROUTE_NODE);

			raw->side = unpack_int_value (en, INT_TYPE_SIDE);

			//
			// link into system
			//

			if (unpack_int_value (en, INT_TYPE_VALID))
			{
				insert_local_entity_into_parents_child_list (en, LIST_TYPE_UPDATE, get_update_entity (), NULL);
			}

			insert_local_entity_into_parents_child_list (en, raw->group_list_type, raw->group_link.parent, NULL);

			{
				list_types
					list_type;
	
				entity
					*force;
	
				list_type = (list_types) get_local_entity_int_value (en, INT_TYPE_REGISTRY_LIST_TYPE);
	
				if (list_type != LIST_TYPE_INVALID)
				{
					force = get_local_force_entity ((entity_sides) raw->side);
	
					ASSERT (force);
	
					insert_local_entity_into_parents_child_list (en, list_type, force, NULL);

					add_group_type_to_force_info (force, raw->sub_type);
				}
			}

			break;
		}
		////////////////////////////////////////
		case PACK_MODE_CLIENT_SESSION:
		////////////////////////////////////////
		{

			int
				index;

			group
				*raw;

			//
			// create entity
			//

			index = unpack_entity_safe_index ();

			en = get_free_entity (index);

			set_local_entity_type (en, type);

			raw = (group *) malloc_fast_mem (sizeof (group));

			set_local_entity_data (en, raw);

			memset (raw, 0, sizeof (group));

			//
			// unpack data (in exactly the same order as the data was packed)
			//

			raw->sub_type = unpack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);

			unpack_list_root (en, LIST_TYPE_MEMBER, &raw->member_root);

			/////////////////////////////////////////////////////////////////
			if (unpack_int_value (en, INT_TYPE_VALID))
			{
			
				unpack_list_root (en, LIST_TYPE_GUIDE_STACK, &raw->guide_stack_root);
			}
			/////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////
			if (unpack_int_value (en, INT_TYPE_VALID))
			{
			
				unpack_list_root (en, LIST_TYPE_TASK_DEPENDENT, &raw->task_dependent_root);
			}
			/////////////////////////////////////////////////////////////////

			// task_dependent_link

			raw->group_list_type = (list_types) unpack_int_value (en, INT_TYPE_GROUP_LIST_TYPE);

//			unpack_list_link (en, raw->group_list_type, &raw->group_link);
			raw->group_link.parent = unpack_entity_safe_ptr ();

			unpack_list_link (en, LIST_TYPE_DIVISION, &raw->division_link);

			unpack_list_link (en, LIST_TYPE_PILOT_LOCK, &raw->pilot_lock_link);

			// update_link 

			// sleep

			// assist timer

			raw->last_seen_time = unpack_float_value (en, FLOAT_TYPE_LAST_SEEN_TIME);

			unpack_vec3d (en, VEC3D_TYPE_LAST_KNOWN_POSITION, &raw->last_known_position);

			// supplies

			raw->alive = unpack_int_value (en, INT_TYPE_ALIVE);

			// engage_enemy

			raw->group_callsign = unpack_int_value (en, INT_TYPE_GROUP_CALLSIGN);

			raw->group_formation = unpack_int_value (en, INT_TYPE_GROUP_FORMATION);

			raw->kills = unpack_int_value (en, INT_TYPE_KILLS);

			raw->losses = unpack_int_value (en, INT_TYPE_LOSSES);

			raw->member_count = unpack_int_value (en, INT_TYPE_MEMBER_COUNT);

			raw->verbose_operational_state = unpack_int_value (en, INT_TYPE_VERBOSE_OPERATIONAL_STATE);

			// unique_id

			// route_node

			raw->side = unpack_int_value (en, INT_TYPE_SIDE);

			//
			// link into system
			//

			insert_local_entity_into_parents_child_list (en, raw->group_list_type, raw->group_link.parent, NULL);

			{
				list_types
					list_type;
	
				entity
					*force;
	
				list_type = (list_types) get_local_entity_int_value (en, INT_TYPE_REGISTRY_LIST_TYPE);
	
				if (list_type != LIST_TYPE_INVALID)
				{
					force = get_local_force_entity ((entity_sides) raw->side);
	
					ASSERT (force);
	
					insert_local_entity_into_parents_child_list (en, list_type, force, NULL);

					add_group_type_to_force_info (force, raw->sub_type);
				}
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

void overload_group_pack_functions (void)
{
	fn_pack_local_entity_data[ENTITY_TYPE_GROUP]		= pack_local_data;

	fn_unpack_local_entity_data[ENTITY_TYPE_GROUP]	= unpack_local_data;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pack_local_group_data (pack_modes mode)
{
	entity
		*en;

	group
		*raw;

	if ((mode != PACK_MODE_SERVER_SESSION) && (mode != PACK_MODE_CLIENT_SESSION))
	{
		return;
	}

	en = get_local_entity_list ();

	while (en)
	{
		if (get_local_entity_type (en) == ENTITY_TYPE_GROUP)
		{
			raw = (group *) get_local_entity_data (en);

			if (group_database [raw->sub_type].local_only_group)
			{
				//
				// DIVISION LINK
				//

				pack_list_link (en, LIST_TYPE_DIVISION, &raw->division_link);

				//
				// TASK DEPENDENT LINK
				//

				if (raw->task_dependent_link.parent)
				{
					pack_int_value (en, INT_TYPE_VALID, TRUE);

					pack_list_link (en, LIST_TYPE_TASK_DEPENDENT, &raw->task_dependent_link);
				}
				else
				{
					pack_int_value (en, INT_TYPE_VALID, FALSE);
				}
			}
		}

		en = get_local_entity_succ (en);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void unpack_local_group_data (pack_modes mode)
{

	group
		*raw;

	entity
		*en;

	if ((mode != PACK_MODE_SERVER_SESSION) && (mode != PACK_MODE_CLIENT_SESSION))
	{

		return;
	}

	en = get_local_entity_list ();

	while (en)
	{
		if (get_local_entity_type (en) == ENTITY_TYPE_GROUP)
		{
			raw = (group *) get_local_entity_data (en);

			if (group_database [raw->sub_type].local_only_group)
			{
				//
				// DIVISION LINK
				//

				unpack_list_link (en, LIST_TYPE_DIVISION, &raw->division_link);

				//
				// TASK DEPENDENT LINK
				//

				if (unpack_int_value (en, INT_TYPE_VALID))
				{
					unpack_list_link (en, LIST_TYPE_TASK_DEPENDENT, &raw->task_dependent_link);
				}
			}
		}
		
		en = get_local_entity_succ (en);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void validate_local_group_data (void)
{
	entity
		*force,
		*en;

	group
		*raw;

	//
	// re-calculate group division names (Cannot be done until all groups + divisions are unpacked)
	//

	ASSERT (get_session_entity ());

	force = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

	ASSERT (force);

	while (force)
	{
		//
		// GROUND REGISTRY
		//
		
		en = get_local_entity_first_child (force, LIST_TYPE_GROUND_REGISTRY);

		while (en)
		{
			ASSERT (get_local_entity_type (en) == ENTITY_TYPE_GROUP);

			raw = (group *) get_local_entity_data (en);

			set_local_division_name (en, raw->division_name);

			en = get_local_entity_child_succ (en, LIST_TYPE_GROUND_REGISTRY);
		}
		
		//
		// AIR REGISTRY
		//
		
		en = get_local_entity_first_child (force, LIST_TYPE_AIR_REGISTRY);

		while (en)
		{
			ASSERT (get_local_entity_type (en) == ENTITY_TYPE_GROUP);

			raw = (group *) get_local_entity_data (en);

			set_local_division_name (en, raw->division_name);

			en = get_local_entity_child_succ (en, LIST_TYPE_AIR_REGISTRY);
		}
		
		//
		// SEA REGISTRY
		//
		
		en = get_local_entity_first_child (force, LIST_TYPE_SEA_REGISTRY);

		while (en)
		{
			ASSERT (get_local_entity_type (en) == ENTITY_TYPE_GROUP);

			raw = (group *) get_local_entity_data (en);

			set_local_division_name (en, raw->division_name);

			en = get_local_entity_child_succ (en, LIST_TYPE_SEA_REGISTRY);
		}
		
		force = get_local_entity_child_succ (force, LIST_TYPE_FORCE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pack_group_callsign_database (pack_modes mode)
{

	int
		loop,
		loop2;

	if (mode == PACK_MODE_SERVER_SESSION)
	{
	
		for (loop = 0; loop < NUM_GROUP_CALLSIGNS; loop ++)
		{
	
			for (loop2 = 0; loop2 < NUM_ENTITY_SIDES; loop2 ++)
			{
	
				pack_int_value (NULL, INT_TYPE_VALUE, group_callsign_names [loop].side [loop2]);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void unpack_group_callsign_database (pack_modes mode)
{

	int
		loop,
		loop2;

	if (mode == PACK_MODE_SERVER_SESSION)
	{
	
		for (loop = 0; loop < NUM_GROUP_CALLSIGNS; loop ++)
		{
	
			for (loop2 = 0; loop2 < NUM_ENTITY_SIDES; loop2 ++)
			{
	
				group_callsign_names [loop].side [loop2] = unpack_int_value (NULL, INT_TYPE_VALUE);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
