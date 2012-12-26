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
			sprite
				*raw;

			raw = (sprite *) get_local_entity_data (en);

			pack_entity_type (get_local_entity_type (en));

			pack_entity_safe_ptr (en);

			//
			// pack effect data
			//

			pack_effect_data (en, &raw->eff, mode);

			//
			// pack sprite data
			//

			pack_float_value (en, FLOAT_TYPE_ANIMATION_FREQUENCY, raw->animation_frequency);

			pack_float_value (en, FLOAT_TYPE_MAX_TURN_RATE, raw->rotation_rate);

			pack_float_value (en, FLOAT_TYPE_EFFECT_LIFETIME, raw->effect_lifetime);

			pack_float_value (en, FLOAT_TYPE_SPRITE_LIFETIME, raw->sprite_lifetime);

			pack_float_value (en, FLOAT_TYPE_START_SCALE, raw->start_scale);

			pack_float_value (en, FLOAT_TYPE_END_SCALE, raw->end_scale);

			pack_int_value (en, INT_TYPE_ANIMATED_TEXTURE, raw->animated_texture);

			pack_vec3d (en, VEC3D_TYPE_RELATIVE_POSITION, &raw->relative_position);

			pack_int_value (en, INT_TYPE_COLOUR_RED, raw->colour_red);
			pack_int_value (en, INT_TYPE_COLOUR_GREEN, raw->colour_green);
			pack_int_value (en, INT_TYPE_COLOUR_BLUE, raw->colour_blue);
			pack_int_value (en, INT_TYPE_COLOUR_ALPHA, raw->colour_alpha);

			pack_int_value (en, INT_TYPE_ADDITIVE, raw->additive);

			// sector_link linked later

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
			int
				index;

			sprite
				*raw;

			//
			// create entity
			//

			index = unpack_entity_safe_index ();

			en = get_free_entity (index);

			set_local_entity_type (en, type);

			raw = (sprite *) malloc_heap_mem (sizeof (sprite));

			set_local_entity_data (en, raw);

			memset (raw, 0, sizeof (sprite));

			//
			// unpack effect data (in exactly the same order as the data was packed)
			//

			unpack_effect_data( en, &raw->eff, mode );

			//
			// unpack sprite data
			//

			raw->animation_frequency = unpack_float_value (en, FLOAT_TYPE_ANIMATION_FREQUENCY);

			raw->rotation_rate = unpack_float_value (en, FLOAT_TYPE_MAX_TURN_RATE);

			raw->effect_lifetime = unpack_float_value (en, FLOAT_TYPE_EFFECT_LIFETIME);

			raw->sprite_lifetime = unpack_float_value (en, FLOAT_TYPE_SPRITE_LIFETIME);

			raw->start_scale = unpack_float_value (en, FLOAT_TYPE_START_SCALE);

			raw->end_scale = unpack_float_value (en, FLOAT_TYPE_END_SCALE);

			raw->animated_texture = (texture_animation_indices) unpack_int_value (en, INT_TYPE_ANIMATED_TEXTURE);

			unpack_vec3d (en, VEC3D_TYPE_RELATIVE_POSITION, &raw->relative_position);

			raw->colour_red = unpack_int_value (en, INT_TYPE_COLOUR_RED);
			raw->colour_green = unpack_int_value (en, INT_TYPE_COLOUR_GREEN);
			raw->colour_blue = unpack_int_value (en, INT_TYPE_COLOUR_BLUE);
			raw->colour_alpha = unpack_int_value (en, INT_TYPE_COLOUR_ALPHA);

			raw->additive = unpack_int_value (en, INT_TYPE_ADDITIVE);

			// sector_link

			////////////////////////////////////////
			//
			// BUILD COMPONENTS
			//
			////////////////////////////////////////
	
			////////////////////////////////////////
			//
			// LINK INTO SYSTEM
			//
			////////////////////////////////////////

			insert_local_entity_into_parents_child_list (en, LIST_TYPE_UPDATE, get_update_entity (), NULL);

			insert_local_entity_into_parents_child_list (en, LIST_TYPE_SECTOR, get_local_sector_entity (&raw->eff.position), NULL);

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

void overload_sprite_pack_functions (void)
{
	fn_pack_local_entity_data[ENTITY_TYPE_SPRITE]		= pack_local_data;

	fn_unpack_local_entity_data[ENTITY_TYPE_SPRITE]		= unpack_local_data;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
