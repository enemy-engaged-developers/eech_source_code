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
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void unpack_local_data (entity *en, entity_types type, pack_modes mode)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_regen_pack_functions (void)
{
	fn_pack_local_entity_data[ENTITY_TYPE_REGEN]		= pack_local_data;

	fn_unpack_local_entity_data[ENTITY_TYPE_REGEN]	= unpack_local_data;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pack_local_regen_data (pack_modes mode)
{
   entity
      *en;

 	regen
      *raw;

	int
		i,
		j,
		k;
		
   ASSERT (mode != PACK_MODE_UPDATE_ENTITY);

   if (mode != PACK_MODE_SERVER_SESSION)
   {
      return;
   }

	en = get_local_entity_list ();

	while (en)
	{
		if (get_local_entity_type (en) == ENTITY_TYPE_REGEN)
		{
			//
			// pack regen data
			//

			pack_entity_safe_ptr (en);

			raw = get_local_entity_data (en);

			pack_float_value (en, FLOAT_TYPE_SLEEP, raw->sleep);

			pack_int_value (en, INT_TYPE_ALIVE, raw->alive);

			pack_int_value (en, INT_TYPE_SIDE, raw->side);
		}

		en = get_local_entity_succ (en);
	}

	for (i = 0; i < NUM_ENTITY_SIDES; i++)
	{
		for (j = 0; j < NUM_ENTITY_SUB_TYPE_REGENS; j++)
		{
			pack_int_value (en, INT_TYPE_VALUE, regen_manager[i][j].size);
			pack_int_value (en, INT_TYPE_VALUE, regen_manager[i][j].count);
			pack_int_value (en, INT_TYPE_VALUE, regen_manager[i][j].front);

			for (k = 0; k < regen_manager[i][j].size; k++)
			{
				pack_int_value (en, INT_TYPE_VALUE, regen_queue [i][j][k].type);
				pack_int_value (en, INT_TYPE_VALUE, regen_queue [i][j][k].sub_type);
				pack_int_value (en, INT_TYPE_VALUE, regen_queue [i][j][k].group);
			}
		}
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void unpack_local_regen_data (pack_modes mode)
{
   entity
      *en;

   regen
      *raw;

	int
		i,
		j,
		k,
		index;

   ASSERT (mode != PACK_MODE_UPDATE_ENTITY);

   if (mode != PACK_MODE_SERVER_SESSION)
   {
      return;
   }

	en = get_local_entity_list ();

	while (en)
	{
		if (get_local_entity_type (en) == ENTITY_TYPE_REGEN)
		{
			index = unpack_entity_safe_index ();

			raw = get_local_entity_data (en);

			raw->sleep = unpack_float_value (en, FLOAT_TYPE_SLEEP);

			raw->alive = unpack_int_value (en, INT_TYPE_ALIVE);

			raw->side = unpack_int_value (en, INT_TYPE_SIDE);
		}

		en = get_local_entity_succ (en);
	}

	for (i = 0; i < NUM_ENTITY_SIDES; i++)
	{
		for (j = 0; j < NUM_ENTITY_SUB_TYPE_REGENS; j++)
		{
			regen_manager [i][j].size = unpack_int_value (en, INT_TYPE_VALUE);
			regen_manager [i][j].count = unpack_int_value (en, INT_TYPE_VALUE);
			regen_manager [i][j].front = unpack_int_value (en, INT_TYPE_VALUE);

			regen_queue [i][j] = safe_malloc (sizeof (regen_list_element) * regen_manager [i][j].size);

			for (k = 0; k < regen_manager [i][j].size; k++)
			{
				regen_queue [i][j][k].type = unpack_int_value (en, INT_TYPE_VALUE);
				regen_queue [i][j][k].sub_type = unpack_int_value (en, INT_TYPE_VALUE);
				regen_queue [i][j][k].group = unpack_int_value (en, INT_TYPE_VALUE);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
