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

int set_infinite_smoke_list_generating_state (entity *parent, entity_sub_types type, float state)
{
	entity
		*en;

	smoke_list
		*raw;

	en = get_local_entity_first_child (parent, LIST_TYPE_SPECIAL_EFFECT);

	while (en)
	{
		if (en->type == ENTITY_TYPE_SMOKE_LIST)
		{
			raw = get_local_entity_data (en);

			if (raw->eff.sub_type == type)
			{
				if (raw->infinite_generator)
				{
					raw->generator_lifetime = state;

					//
					// if switching generator on, make sure it is on the update list
					//

					if (state == INFINITE_SMOKE_ON)
					{
						if (get_local_entity_parent (en, LIST_TYPE_UPDATE) == NULL)
						{
							insert_local_entity_into_parents_child_list (en, LIST_TYPE_UPDATE, get_update_entity(), raw->eff.update_link.child_pred);
						}
					}
				}
			}
      }

		en = get_local_entity_child_succ (en, LIST_TYPE_SPECIAL_EFFECT);
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int clear_smoke_list_generator_lifetime (entity *parent, entity_sub_types type)
{
	entity
		*en;

	smoke_list
		*raw;

	en = get_local_entity_first_child (parent, LIST_TYPE_SPECIAL_EFFECT);

	while (en)
	{
		if (en->type == ENTITY_TYPE_SMOKE_LIST)
		{
			raw = get_local_entity_data (en);

			if (raw->eff.sub_type == type)
			{
				raw->generator_lifetime = 0.0;
			}
      }

		en = get_local_entity_child_succ (en, LIST_TYPE_SPECIAL_EFFECT);
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int attach_client_server_meta_smoke_lists_to_object (entity *parent, meta_smoke_list_types meta_smoke_type, object_3d_sub_object_index_numbers sub_object_type)
{
	object_3d_instance
		*inst3d;

	int
		create_count;

	create_count = 0;

	inst3d = get_local_entity_ptr_value (parent, PTR_TYPE_INSTANCE_3D_OBJECT);

	if (inst3d)
	{
		int
			loop,
			depth;

		depth = count_sub_object_type_depth (inst3d, sub_object_type);

		for (loop = 0 ; loop < depth ; loop ++)
		{
			create_count += create_client_server_meta_smoke_list_sub_object_offset (meta_smoke_type, parent, sub_object_type, loop);
		}
	}

	return create_count;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int attach_local_meta_smoke_lists_to_object (entity *parent, meta_smoke_list_types meta_smoke_type, object_3d_sub_object_index_numbers sub_object_type, int *entity_index_list)
{
	object_3d_instance
		*inst3d;

	int
		create_count;

	inst3d = get_local_entity_ptr_value (parent, PTR_TYPE_INSTANCE_3D_OBJECT);

	create_count = 0;

	if (inst3d)
	{
		int
			loop,
			depth;

		depth = count_sub_object_type_depth (inst3d, sub_object_type);

		for (loop = 0 ; loop < depth ; loop ++)
		{
			if (entity_index_list)
			{
				create_count += create_meta_smoke_list_sub_object_offset (meta_smoke_type, parent, sub_object_type, loop, &entity_index_list [create_count]);
			}
			else
			{
				int
					i,
					count,
					*temp_index_list;

				//
				// create an array of entity index numbers and fill them all with ENTITY_INDEX_DONT_CARE
				//

				count = count_entities_in_meta_smoke_list (meta_smoke_type);

				ASSERT (count);

				temp_index_list = malloc_fast_mem (sizeof (int) * count);

				for ( i = 0 ; i < count ; i ++ )
				{
					temp_index_list [i] = ENTITY_INDEX_DONT_CARE;
				}

				create_count += create_meta_smoke_list_sub_object_offset (meta_smoke_type, parent, sub_object_type, loop, temp_index_list);

				free_mem (temp_index_list);
			}
		}
	}

	return create_count;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



