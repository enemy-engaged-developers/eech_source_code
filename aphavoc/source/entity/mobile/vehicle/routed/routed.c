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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

#define MAX_META_SMOKE_LIST_ATTACHMENT_POINTS 2

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static struct ATTACHED_META_SMOKE_LIST_TABLE
{

	meta_smoke_list_types							type;
	object_3d_sub_object_index_numbers			attachment_point[MAX_META_SMOKE_LIST_ATTACHMENT_POINTS];

} attached_meta_smoke_list_table[] =
	{
		////////////////////////////////////////////////
		//
		// DUST TRAILS
		//
		////////////////////////////////////////////////
		{
			META_SMOKE_LIST_TYPE_VEHICLE_DUST_TRAIL,
			{
				OBJECT_3D_SUB_OBJECT_WHEEL_SMOKE_EFFECT,
				-1
			}
		},
		////////////////////////////////////////////////
		//
		// TERMINATOR
		//
		////////////////////////////////////////////////
		{
			-1,
			{
				-1,
				-1
			}
		}
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void attach_routed_vehicle_meta_smoke_lists (entity *en)
{
	int
		item,
		point;

	object_3d_sub_object_index_numbers
		attachment_point;

	meta_smoke_list_types
		type;

	item = 0;

	while (TRUE)
	{
		type = attached_meta_smoke_list_table [item].type;

		if (type == -1)
		{
			break;
		}
		else
		{
			for (point = 0; point < MAX_META_SMOKE_LIST_ATTACHMENT_POINTS; point ++)
			{
				attachment_point = attached_meta_smoke_list_table [item].attachment_point [point];

				if (attachment_point == -1)
				{
					break;
				}

				attach_local_meta_smoke_lists_to_object (en, type, attachment_point, NULL);
			}
		}

		item ++;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pack_routed_vehicle_meta_smoke_lists (entity *en, pack_modes mode)
{
	object_3d_instance
		*inst3d;

	int
		item,
		loop,
		count,
		point,
		packed_indices;

	entity
		*special_effect;

	object_3d_sub_object_index_numbers
		attachment_point;

	meta_smoke_list_types
		type;

	if (mode == PACK_MODE_SERVER_SESSION)
	{
		//
		// no need to pack indices as the server can use "ENTITY_INDEX_DONT_CARE"s when unpacking
		//

		return;
	}

	if (get_local_entity_int_value (en, INT_TYPE_ALIVE))
	{
		inst3d = get_local_entity_ptr_value (en, PTR_TYPE_INSTANCE_3D_OBJECT);

		if (inst3d)
		{
			#if DEBUG_MODULE

			debug_log ("ROUTED : Packing smoke for %s ( %d )", vehicle_database [get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)].full_name, en);

			#endif

			item = 0;

			special_effect = get_local_entity_first_child (en, LIST_TYPE_SPECIAL_EFFECT);

			while (TRUE)
			{
				type = attached_meta_smoke_list_table [item].type;

				if (type == -1)
				{
					break;
				}
				else
				{
					count = 0;

					for (point = 0; point < MAX_META_SMOKE_LIST_ATTACHMENT_POINTS; point ++)
					{
						attachment_point = attached_meta_smoke_list_table [item].attachment_point [point];

						if (attachment_point == -1)
						{
							break;
						}
						else
						{
							count += count_sub_object_type_depth (inst3d, attachment_point);
						}
					}

					count *= count_entities_in_meta_smoke_list (type);

					if (count > 0)
					{
						packed_indices = 0;

						for (loop = 0 ; loop < count ; loop ++)
						{
							while (TRUE)
							{
								ASSERT (special_effect);

								if (special_effect->type == ENTITY_TYPE_SMOKE_LIST)
								{
									if (effect_database [get_local_entity_int_value (special_effect, INT_TYPE_ENTITY_SUB_TYPE)].constructed_locally)
									{
										pack_entity_safe_index (get_local_entity_index (special_effect));

										#if DEBUG_MODULE

										debug_log ("ROUTED : Index %d = %d", packed_indices, get_local_entity_index (special_effect));

										#endif

										packed_indices ++;

										special_effect = get_local_entity_child_succ (special_effect, LIST_TYPE_SPECIAL_EFFECT);

										break;
									}
								}
	
								special_effect = get_local_entity_child_succ (special_effect, LIST_TYPE_SPECIAL_EFFECT);
							}
						}

						//
						// check to make sure that only vehicle wake smoke lists are being sent across ( and also the right amount of them )
						//

						ASSERT (packed_indices == count);
					}
				}

				item ++;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void unpack_routed_vehicle_meta_smoke_lists (entity *en, pack_modes mode)
{
	object_3d_instance
		*inst3d;

	int
		item,
		loop,
		count,
		point,
		*entity_index_list;

	meta_smoke_list_types
		type;

	object_3d_sub_object_index_numbers
		attachment_point;

	if (get_local_entity_int_value (en, INT_TYPE_ALIVE))
	{
		inst3d = get_local_entity_ptr_value (en, PTR_TYPE_INSTANCE_3D_OBJECT);

		if (inst3d)
		{
			#if DEBUG_MODULE

			debug_log ("ROUTED : Unpacking smoke for %s ( %d )", vehicle_database [get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)].full_name, en);

			#endif

			item = 0;

			while (TRUE)
			{
				type = attached_meta_smoke_list_table [item].type;

				if (type == -1)
				{
					break;
				}
				else
				{				
					for (point = 0; point < MAX_META_SMOKE_LIST_ATTACHMENT_POINTS; point ++)
					{
						attachment_point = attached_meta_smoke_list_table [item].attachment_point [point];

						if (attachment_point == -1)
						{
							break;
						}
						else
						{				
							count = count_sub_object_type_depth (inst3d, attachment_point);

							if (count >0)
							{
								count *= count_entities_in_meta_smoke_list (type);						

								entity_index_list = malloc_fast_mem (sizeof (int) * count);

								for (loop = 0; loop < count; loop ++)
								{
									if (mode == PACK_MODE_SERVER_SESSION)
									{
										entity_index_list [loop] = ENTITY_INDEX_DONT_CARE;
									}
									else
									{
										entity_index_list [loop] = unpack_entity_safe_index ();
									}

									#if DEBUG_MODULE

									debug_log ("ROUTED : Index %d = %d", loop, entity_index_list [loop]);

									#endif
								}

								register_attach_meta_smoke_list_to_object (en, type, attachment_point, entity_index_list, count);

								free_mem (entity_index_list);
							}
						}
					}
				}

				item ++;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stop_vehicles_on_route (int start_node, int end_node)
{
	entity
		*task,
		*force,
		*group,
		*member;

	int
		index1,
		index2;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	force = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

	while (force)
	{
		group = get_local_entity_first_child (force, LIST_TYPE_GROUND_REGISTRY);

		while (group)
		{
			task = get_local_group_primary_task (group);

			if (task)
			{
				member = get_local_entity_ptr_value (group, PTR_TYPE_GROUP_LEADER);
	
				ASSERT (member);
			
				index1 = get_local_entity_int_value (member, INT_TYPE_WAYPOINT_THIS_INDEX);
	
				index2 = get_local_entity_int_value (member, INT_TYPE_WAYPOINT_NEXT_INDEX);
	
				if (((index1 == start_node) && (index2 == end_node)) || ((index2 == start_node) && (index1 == end_node)))
				{
					//
					// destroy task
					//
	
					notify_local_entity (ENTITY_MESSAGE_TASK_TERMINATED, task, group, TASK_TERMINATED_GROUP_DESTROYED);

					//
					// set group to busy, and operational state to stopped
					//
	
					set_client_server_entity_int_value (group, INT_TYPE_GROUP_MODE, GROUP_MODE_BUSY);

					{
						entity
							*mb;

						mb = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

						while (mb)
						{
							set_client_server_entity_int_value (mb, INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_STOPPED);

							mb = get_local_entity_child_succ (mb, LIST_TYPE_MEMBER);
						}
					}

					/////////////////////////////////////////////////////////////////
					//
					// SPECIAL_EFFECT_HOOK FOR BRIDGE OUT
					//
					/////////////////////////////////////////////////////////////////
	
					/////////////////////////////////////////////////////////////////
					//
					//
					/////////////////////////////////////////////////////////////////
				}
			}
	
			group = get_local_entity_child_succ (group, LIST_TYPE_GROUND_REGISTRY);
		}

		force = get_local_entity_child_succ (force, LIST_TYPE_FORCE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


