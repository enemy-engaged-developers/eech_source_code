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
			smoke_list
				*raw;

			raw = get_local_entity_data (en);

			if (effect_database [raw->eff.sub_type].constructed_locally)
			{
				return;
			}

			pack_entity_type (get_local_entity_type (en));

			pack_entity_safe_ptr (en);

			//
			// pack effect data
			//

			pack_effect_data (en, &raw->eff, mode);

			//
			// pack smokelist data
			//

			pack_int_value (en, INT_TYPE_SMOKE_TYPE, raw->smoke_type);

			pack_float_value (en, FLOAT_TYPE_FREQUENCY, raw->frequency);

			pack_float_value (en, FLOAT_TYPE_GENERATOR_LIFETIME, raw->generator_lifetime);

			// Xhit: added scale and alpha_percentage for downwash effect. (030328)
			pack_float_value (en, FLOAT_TYPE_SCALE, raw->scale);
			pack_int_value (en, INT_TYPE_COLOUR_ALPHA, raw->alpha_percentage);

			// smoke_sleep

			pack_float_value (en, FLOAT_TYPE_SMOKE_LIFETIME, raw->smoke_lifetime);

			// texture_distance

			// width_adjustment

			// alive_count

			pack_int_value (en, INT_TYPE_INFINITE_GENERATOR, raw->infinite_generator);

			// head

			// tail

			pack_vec3d (en, VEC3D_TYPE_INITIAL_VELOCITY, &raw->initial_velocity);

			// motion vectors 

			// positions 

			// start_rotation 

			// current_frame

			// valid flags

			pack_vec3d (en, VEC3D_TYPE_RELATIVE_POSITION, &raw->relative_position);

			// sector_link 

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
				loop,
				index,
				number_of_slots;

			smoke_list
				*raw;

			//
			// create entity
			//

			index = unpack_entity_safe_index ();

			en = get_free_entity (index);

			set_local_entity_type (en, type);

			raw = malloc_heap_mem (sizeof (smoke_list));

			set_local_entity_data (en, raw);

			memset (raw, 0, sizeof (smoke_list));

			//
			// unpack effect data (in exactly the same order as the data was packed)
			//

			unpack_effect_data( en, &raw->eff, mode );

			//
			// unpack smokelist data
			//

			raw->smoke_type = unpack_int_value (en, INT_TYPE_SMOKE_TYPE);

			raw->frequency = unpack_float_value (en, FLOAT_TYPE_FREQUENCY);

			raw->generator_lifetime = unpack_float_value (en, FLOAT_TYPE_GENERATOR_LIFETIME);

			// Xhit: added scale and alpha_percentage for downwash effect. (030328)
			raw->scale = unpack_float_value (en, FLOAT_TYPE_SCALE);
			raw->alpha_percentage = unpack_int_value (en, INT_TYPE_COLOUR_ALPHA);

			// smoke_sleep

			raw->smoke_lifetime = unpack_float_value (en, FLOAT_TYPE_SMOKE_LIFETIME);

			// texture_distance 

			// width adjustment

			// alive_count

			raw->infinite_generator = unpack_int_value (en, INT_TYPE_INFINITE_GENERATOR);

			// head 

			// tail

			unpack_vec3d (en, VEC3D_TYPE_INITIAL_VELOCITY, &raw->initial_velocity);

			// motion_vector

			// position 

			// start_rotation 

			// current_rotation

			// valid flags

			unpack_vec3d (en, VEC3D_TYPE_RELATIVE_POSITION, &raw->relative_position);

			// sector_link

			////////////////////////////////////////
			//
			// BUILD COMPONENTS
			//
			////////////////////////////////////////
	
			number_of_slots = raw->smoke_lifetime / raw->frequency;
	
			//
			// Build array of smoke positions, and mark all as inactive ( -1, -1, -1 )
			// 
	
			raw->position = malloc_fast_mem (sizeof (vec3d) * number_of_slots);
	
			raw->valid = malloc_fast_mem (sizeof (unsigned char) * number_of_slots);
	
			for ( loop = number_of_slots - 1 ; loop >= 0 ; loop -- )
			{
				raw->valid[ loop ] = FALSE;

				raw->position[ loop ].x = -1.0;
				raw->position[ loop ].y = -1.0;
				raw->position[ loop ].z = -1.0;
			}
	
			raw->motion_vector = malloc_fast_mem (sizeof (vec3d) * number_of_slots);
	
			memset( raw->motion_vector, 0, sizeof( vec3d ) * number_of_slots );
	
			raw->start_rotation = malloc_fast_mem (sizeof (float) * number_of_slots);

			raw->head = 0;
	
			raw->tail = 0;
	
			//
			// link into system
			//

			insert_local_entity_into_parents_child_list (en, LIST_TYPE_SECTOR, get_local_sector_entity (&raw->eff.position), NULL);

			insert_local_entity_into_parents_child_list (en, LIST_TYPE_UPDATE, get_update_entity (), NULL);

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

void overload_smoke_list_pack_functions (void)
{
	fn_pack_local_entity_data[ENTITY_TYPE_SMOKE_LIST]		= pack_local_data;

	fn_unpack_local_entity_data[ENTITY_TYPE_SMOKE_LIST]	= unpack_local_data;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
