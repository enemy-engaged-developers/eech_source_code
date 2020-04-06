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

void pack_mobile_data (entity *en, mobile *raw, pack_modes mode)
{
	ASSERT ((mode >= 0) && (mode < NUM_PACK_MODES));

	switch (mode)
	{
		////////////////////////////////////////
		case PACK_MODE_SERVER_SESSION:
		case PACK_MODE_CLIENT_SESSION:
		////////////////////////////////////////
		{
			pack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, raw->sub_type);

			pack_vec3d (en, VEC3D_TYPE_POSITION, &raw->position);

			/////////////////////////////////////////////////////////////////

			if (get_local_entity_type (en) != ENTITY_TYPE_CARGO)
			{

				pack_attitude_matrix (en, raw->attitude);
			}

			/////////////////////////////////////////////////////////////////
			if (!check_zero_3d_vector (&raw->motion_vector))
			{

				pack_int_value (en, INT_TYPE_VALID, TRUE);

				pack_vec3d (en, VEC3D_TYPE_MOTION_VECTOR, &raw->motion_vector);
			}
			else
			{

				pack_int_value (en, INT_TYPE_VALID, FALSE);
			}
			/////////////////////////////////////////////////////////////////

			// velocity packed at lower levels (aircraft / vehicle)

			/////////////////////////////////////////////////////////////////
			// special case for special effect root
			// Pack first non-locally contructed entity as the list_root.
			if (get_local_entity_first_child (en, LIST_TYPE_SPECIAL_EFFECT))
			{
				list_root
					root;

				entity
					*spec = nullptr;

				pack_int_value (en, INT_TYPE_VALID, TRUE);

				spec = get_local_entity_first_child (en, LIST_TYPE_SPECIAL_EFFECT);

				while (TRUE)
				{
					if ((spec == NULL) ||
							(effect_database [get_local_entity_int_value (spec, INT_TYPE_ENTITY_SUB_TYPE)].constructed_locally == FALSE))
					{
						root.first_child = spec;

						pack_list_root (en, LIST_TYPE_SPECIAL_EFFECT, &root);

						break;
					}

					spec = get_local_entity_child_succ (spec, LIST_TYPE_SPECIAL_EFFECT);
				}
			}
			else
			{

				pack_int_value (en, INT_TYPE_VALID, FALSE);
			}
			/////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////
			if (raw->target_root.first_child)
			{

				pack_int_value (en, INT_TYPE_VALID, TRUE);

				pack_list_root (en, LIST_TYPE_TARGET, &raw->target_root);
			}
			else
			{

				pack_int_value (en, INT_TYPE_VALID, FALSE);
			}
			/////////////////////////////////////////////////////////////////

			// padlock_link

			// sector_link

			/////////////////////////////////////////////////////////////////
			if (raw->target_link.parent)
			{

				pack_int_value (en, INT_TYPE_VALID, TRUE);

				pack_list_link (en, LIST_TYPE_TARGET, &raw->target_link);
			}
			else
			{

				pack_int_value (en, INT_TYPE_VALID, FALSE);
			}
			/////////////////////////////////////////////////////////////////

			// update_link

			pack_int_value (en, INT_TYPE_ALIVE, raw->alive);

			pack_int_value (en, INT_TYPE_SIDE, raw->side);

			if (raw->alive)
			{

				pack_int_value (en, INT_TYPE_KILL_NEXT_UPDATE, raw->kill_next_update);
			}

			// updated

			// object_drawn_once_this_frame

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
			// cannot update entity at this level as the update may not apply to all entity types below
			//

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void unpack_mobile_data (entity *en, mobile *raw, pack_modes mode)
{
	ASSERT ((mode >= 0) && (mode < NUM_PACK_MODES));

	switch (mode)
	{
		////////////////////////////////////////
		case PACK_MODE_SERVER_SESSION:
		case PACK_MODE_CLIENT_SESSION:
		////////////////////////////////////////
		{
			raw->sub_type = unpack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);

			unpack_vec3d (en, VEC3D_TYPE_POSITION, &raw->position);

			/////////////////////////////////////////////////////////////////

			if (get_local_entity_type (en) == ENTITY_TYPE_CARGO)
			{

				get_identity_matrix3x3 (raw->attitude);
			}
			else
			{

				unpack_attitude_matrix (en, raw->attitude);
			}

			/////////////////////////////////////////////////////////////////
			if (unpack_int_value (en, INT_TYPE_VALID))
			{

				unpack_vec3d (en, VEC3D_TYPE_MOTION_VECTOR, &raw->motion_vector);
			}
			/////////////////////////////////////////////////////////////////

			// velocity unpacked at lower levels (aircraft / vehicle)

			/////////////////////////////////////////////////////////////////
			if (unpack_int_value (en, INT_TYPE_VALID))
			{

				unpack_list_root (en, LIST_TYPE_SPECIAL_EFFECT, &raw->special_effect_root);
			}
			/////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////
			if (unpack_int_value (en, INT_TYPE_VALID))
			{

				unpack_list_root (en, LIST_TYPE_TARGET, &raw->target_root);
			}
			/////////////////////////////////////////////////////////////////

			// padlock_link

			// sector_link

			/////////////////////////////////////////////////////////////////
			if (unpack_int_value (en, INT_TYPE_VALID))
			{

				unpack_list_link (en, LIST_TYPE_TARGET, &raw->target_link);
			}
			/////////////////////////////////////////////////////////////////

			// update_link

			raw->alive = unpack_int_value (en, INT_TYPE_ALIVE);

			raw->side = unpack_int_value (en, INT_TYPE_SIDE);

			if (raw->alive)
			{

				raw->kill_next_update = unpack_int_value (en, INT_TYPE_KILL_NEXT_UPDATE);
			}

			// updated

			// object_drawn_once_this_frame

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
			// cannot update entity at this level as the update may not apply to all entity types below
			//

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int pack_mobile_local_sound_effects (entity *mobile, pack_modes mode)
{
	int
		count;

	entity
		*en = nullptr;

	entity_sub_types
		sub_type;

	count = 0;

	//
	// count up local sound effect entities
	//

	en = get_local_entity_first_child (mobile, LIST_TYPE_SPECIAL_EFFECT);

	while (en)
	{
		if (get_local_entity_type (en) == ENTITY_TYPE_SOUND_EFFECT)
		{
			sub_type = get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);

			if (effect_database [sub_type].constructed_locally)
			{
				count ++;
			}
		}

		en = get_local_entity_child_succ (en, LIST_TYPE_SPECIAL_EFFECT);
	}

	//
	// pack up count
	//

	pack_int_value (en, INT_TYPE_LOCAL_EFFECT_COUNT, count);

	if (count == 0)
	{
		return 0;
	}

	//
	// pack sound data
	//

	en = get_local_entity_first_child (mobile, LIST_TYPE_SPECIAL_EFFECT);

	while (en)
	{
		if (get_local_entity_type (en) == ENTITY_TYPE_SOUND_EFFECT)
		{
			sub_type = get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);

			if (effect_database [sub_type].constructed_locally)
			{
				pack_local_only_sound_effect_data (en, mode);
			}
		}

		en = get_local_entity_child_succ (en, LIST_TYPE_SPECIAL_EFFECT);
	}

	return count;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int unpack_mobile_local_sound_effects (entity *mobile, pack_modes mode)
{
	int
		loop,
		count;

	count = 0;

	//
	// unpack count
	//

	count = unpack_int_value (mobile, INT_TYPE_LOCAL_EFFECT_COUNT);

	if (count == 0)
	{
		return 0;
	}

	//
	// unpack sound data
	//

	for (loop = 0; loop < count; loop ++)
	{
		unpack_local_only_sound_effect_data (mobile, mode);
	}

	return count;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
