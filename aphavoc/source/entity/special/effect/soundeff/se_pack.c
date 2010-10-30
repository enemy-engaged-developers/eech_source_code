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
		case PACK_MODE_CLIENT_SESSION:
		////////////////////////////////////////
		{
			sound_effect
				*raw;

			unsigned int
				loop;

			raw = (sound_effect *) get_local_entity_data (en);

			if (effect_database [raw->eff.sub_type].constructed_locally)
			{
				return;
			}

			if (mode == PACK_MODE_SERVER_SESSION)
			{
	
				if (get_local_entity_type (raw->eff.special_effect_link.parent) == ENTITY_TYPE_SESSION)
				{
	
					return;
				}
			}

			pack_entity_type (get_local_entity_type (en));

			pack_entity_safe_ptr (en);

			//
			// pack effect data
			//

			pack_effect_data (en, &raw->eff, mode);

			//
			// pack sound effect data
			//

			pack_int_value (en, INT_TYPE_SOUND_EFFECT_SEQUENCE_COUNT, raw->sound_effect_sequence_count);

			for (loop = 0; loop < raw->sound_effect_sequence_count; loop ++)
			{
				pack_int_value (en, INT_TYPE_SOUND_EFFECT_INDEX, raw->effect_index [loop]);
			}

			pack_float_value (en, FLOAT_TYPE_AMPLIFICATION, raw->amplification);

			pack_float_value (en, FLOAT_TYPE_SOUNDPITCH, raw->pitch);

			pack_float_value (en, FLOAT_TYPE_EFFECT_LIFETIME, raw->effect_lifetime);

			pack_float_value (en, FLOAT_TYPE_VALID_EFFECT_LIFETIME, raw->valid_effect_lifetime);

			// sound_effect_data

			pack_int_value (en, INT_TYPE_SOUND_CHANNEL, raw->sound_channel);

			pack_int_value (en, INT_TYPE_SOUND_LOCALITY, raw->sound_locality);

			pack_int_value (en, INT_TYPE_VALID_SOUND_EFFECT, raw->valid_sound_effect);

			pack_int_value (en, INT_TYPE_SOUND_EFFECT_LOOPING, raw->looping);

			pack_int_value (en, INT_TYPE_SOUND_EFFECT_PANNING, raw->panning);

			if (get_local_entity_parent (en, LIST_TYPE_UPDATE))
			{
				pack_int_value (en, INT_TYPE_VALID, TRUE);
			}
			else
			{
				pack_int_value (en, INT_TYPE_VALID, FALSE);
			}

			#if DEBUG_MODULE

			debug_log ("SE_PACK: Packed %d - Sub-type %d", get_local_entity_safe_index (en), raw->eff.sub_type);

			#endif

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
		case PACK_MODE_CLIENT_SESSION:
		////////////////////////////////////////
		{
			unsigned int
				loop;

			int
				index;

			sound_effect
				*raw;

			//
			// create entity
			//

			index = unpack_entity_safe_index ();

			en = get_free_entity (index);

			set_local_entity_type (en, type);

			raw = (sound_effect *) malloc_heap_mem (sizeof (sound_effect));

			set_local_entity_data (en, raw);

			memset (raw, 0, sizeof (sound_effect));

			//
			// unpack effect data (in exactly the same order as the data was packed)
			//

			unpack_effect_data( en, &raw->eff, mode );

			//
			// unpack sound data
			//

			raw->sound_effect_sequence_count = unpack_int_value (en, INT_TYPE_SOUND_EFFECT_SEQUENCE_COUNT);

			ASSERT (raw->sound_effect_sequence_count > 0);

			raw->effect_index = (sound_sample_indices *) malloc_fast_mem (sizeof (sound_sample_indices) * raw->sound_effect_sequence_count);

			for (loop = 0; loop < raw->sound_effect_sequence_count; loop ++)
			{
				raw->effect_index [loop] = unpack_int_value (en, INT_TYPE_SOUND_EFFECT_INDEX);
			}

			raw->amplification = unpack_float_value (en, FLOAT_TYPE_AMPLIFICATION);

			raw->pitch = unpack_float_value (en, FLOAT_TYPE_SOUNDPITCH);

			raw->effect_lifetime = unpack_float_value (en, FLOAT_TYPE_EFFECT_LIFETIME);

			raw->valid_effect_lifetime = unpack_float_value (en, FLOAT_TYPE_VALID_EFFECT_LIFETIME);

			//sound_effect_data 

			raw->sound_channel = unpack_int_value (en, INT_TYPE_SOUND_CHANNEL);

			raw->sound_locality = unpack_int_value (en, INT_TYPE_SOUND_LOCALITY);

			raw->valid_sound_effect = unpack_int_value (en, INT_TYPE_VALID_SOUND_EFFECT);

			raw->looping = unpack_int_value (en, INT_TYPE_SOUND_EFFECT_LOOPING);

			raw->panning = unpack_int_value (en, INT_TYPE_SOUND_EFFECT_PANNING);

			//
			// link into system
			//

			// sound effect needs a parent
			//ASSERT (raw->eff.special_effect_link.parent);

			if (unpack_int_value (en, INT_TYPE_VALID))
			{
				insert_local_entity_into_parents_child_list (en, LIST_TYPE_UPDATE, get_update_entity (), NULL);
			}

			#if DEBUG_MODULE

			debug_log ("SE_PACK: Unpacked %d - Sub-type %d", get_local_entity_safe_index (en), raw->eff.sub_type);

			#endif

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

void overload_sound_effect_pack_functions (void)
{
	fn_pack_local_entity_data[ENTITY_TYPE_SOUND_EFFECT]		= pack_local_data;

	fn_unpack_local_entity_data[ENTITY_TYPE_SOUND_EFFECT]		= unpack_local_data;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pack_local_only_sound_effect_data (entity *en, pack_modes mode)
{
	sound_effect
		*raw;

	ASSERT (en);

	raw = (sound_effect *) get_local_entity_data (en);

	//
	// check properties
	//

	ASSERT (raw->looping); 

	ASSERT (raw->sound_effect_sequence_count == 1);

	//
	// pack data
	//

	if (mode == PACK_MODE_CLIENT_SESSION)
	{
		pack_entity_safe_ptr (en);
	}

	pack_int_value (en, INT_TYPE_SIDE, raw->side);

	pack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, raw->eff.sub_type);

	pack_int_value (en, INT_TYPE_VALID_SOUND_EFFECT, raw->valid_sound_effect);

	pack_int_value (en, INT_TYPE_SOUND_EFFECT_INDEX, raw->effect_index [0]);

	#if DEBUG_MODULE

	debug_log ("SE_PACK: Packed Local-Only %d - Sub-type %d", get_local_entity_safe_index (en), raw->eff.sub_type);

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void unpack_local_only_sound_effect_data (entity *parent, pack_modes mode)
{
	int
		side,
		entity_index,
		sample_index,
		valid;

	entity_sub_types
		sub_type;

	ASSERT (parent);

	//
	// unpack data
	//

	if (mode == PACK_MODE_CLIENT_SESSION)
	{
		entity_index = unpack_entity_safe_index ();
	}
	else
	{
		entity_index = ENTITY_INDEX_DONT_CARE;
	}

	side = unpack_int_value (NULL, INT_TYPE_SIDE);

	sub_type = unpack_int_value (NULL, INT_TYPE_ENTITY_SUB_TYPE);

	valid = unpack_int_value (NULL, INT_TYPE_VALID_SOUND_EFFECT);

	sample_index = unpack_int_value (NULL, INT_TYPE_SOUND_EFFECT_INDEX);

	register_attach_sound_effect_to_object (parent, entity_index, (entity_sides) side, sub_type, valid, sample_index);

	#if DEBUG_MODULE

	debug_log ("SE_PACK: Unpacked Local-Only %d - Sub-type %d", entity_index, sub_type);

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
