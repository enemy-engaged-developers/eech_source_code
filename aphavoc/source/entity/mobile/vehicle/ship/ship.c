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
		// SHIP WAKES ( REAR )
		//
		////////////////////////////////////////////////
		{
			META_SMOKE_LIST_TYPE_REAR_SHIP_WAKE,
			{
				OBJECT_3D_SUB_OBJECT_EFFECT_SHIP_WAKE_BACK,
				-1
			}
		},
		////////////////////////////////////////////////
		//
		// SHIP WAKES ( FRONT )
		//
		////////////////////////////////////////////////
		{
			META_SMOKE_LIST_TYPE_FRONT_SHIP_WAKE,
			{
				OBJECT_3D_SUB_OBJECT_EFFECT_SHIP_WAKE_FRONT,
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

void attach_ship_meta_smoke_lists (entity *en)
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

void pack_ship_meta_smoke_lists (entity *en, pack_modes mode)
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

			debug_log ("SHIP : Packing smoke for %s ( %d )", vehicle_database [get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)].full_name, en);

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
	
										debug_log ("SHIP : Index %d = %d", packed_indices, get_local_entity_index (special_effect));
	
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

void unpack_ship_meta_smoke_lists (entity *en, pack_modes mode)
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

			debug_log ("SHIP : Unpacking smoke for %s ( %d )", vehicle_database [get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)].full_name, en);

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

								//attach_local_meta_smoke_lists_to_object (en, type, attachment_point, entity_index_list);

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



