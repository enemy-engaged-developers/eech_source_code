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

void overload_pylon_pack_functions (void)
{
   fn_pack_local_entity_data[ENTITY_TYPE_PYLON]    = pack_local_data;

   fn_unpack_local_entity_data[ENTITY_TYPE_PYLON]  = unpack_local_data;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pack_local_pylon_data (pack_modes mode)
{
   entity
      *en = nullptr;

   pylon
      *raw = nullptr;

	int
		total,
		pack_size,
		count,
		alive;

   ASSERT (mode != PACK_MODE_UPDATE_ENTITY);

   if (mode == PACK_MODE_BROWSE_SESSION)
   {
      return;
   }

	//
	// RLE encoded
	//

	debug_log ("RLE PYLON");

	pack_size = 0;

	count = 0;

	alive = TRUE;

	total = 0;

	en = get_local_entity_list ();

	while (en)
	{

		if (en->type == ENTITY_TYPE_PYLON)
		{

			total ++;

			raw = (pylon *) get_local_entity_data (en);

			if (alive == raw->fix.alive)
			{

				count ++;
			}
			else
			{

				pack_int_value (NULL, INT_TYPE_LENGTH, count);
				pack_size += NUM_LENGTH_BITS;

				pack_int_value (NULL, INT_TYPE_ALIVE, alive);
				pack_size += NUM_ALIVE_BITS;

				#if DEBUG_MODULE

				debug_log ("PY_PACK: packing count %d, alive %d", count, alive);

				#endif

				alive = raw->fix.alive;

				count = 1;
			}
		}

		en = get_local_entity_succ (en);
	}

	pack_int_value (NULL, INT_TYPE_LENGTH, count);
	pack_size += NUM_LENGTH_BITS;

	pack_int_value (NULL, INT_TYPE_ALIVE, alive);
	pack_size += NUM_ALIVE_BITS;

	#if DEBUG_MODULE

	debug_log ("PY_PACK: packing count %d, alive %d", count, alive);

	#endif

	//debug_log ("PY_PACK: packing %d pylons took %d bytes (%d bits)", total, pack_size / 8, pack_size);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void unpack_local_pylon_data (pack_modes mode)
{
   entity
		*destroy_en = nullptr,
      *en = nullptr;

   pylon
      *raw = nullptr;

	int
		alive,
		count;

   ASSERT (mode != PACK_MODE_UPDATE_ENTITY);

   if (mode == PACK_MODE_BROWSE_SESSION)
   {
      return;
   }

	//
	// RLE encoded
	//

	debug_log ("RLE PYLON");

	count = unpack_int_value (NULL, INT_TYPE_LENGTH);

	alive = unpack_int_value (NULL, INT_TYPE_ALIVE);

	#if DEBUG_MODULE

	debug_log ("PY_PACK: unpacking count %d, alive %d", count, alive);

	#endif

	en = get_local_entity_list ();

	ASSERT (en);

	while (en)
	{

		destroy_en = en;

		en = get_local_entity_succ (en);

		if (get_local_entity_type (destroy_en) == ENTITY_TYPE_PYLON)
		{

			if (count == 0)
			{

				count = unpack_int_value (NULL, INT_TYPE_LENGTH);

				alive = unpack_int_value (NULL, INT_TYPE_ALIVE);

				#if DEBUG_MODULE
			
				debug_log ("PY_PACK: unpacking count %d, alive %d", count, alive);
			
				#endif
			}

			count --;

			raw = (pylon *) get_local_entity_data (destroy_en);

			raw->fix.alive = alive;

			if (!alive)
			{
				raw->fix.object_3d_shape = get_3d_object_destroyed_object_index (raw->fix.object_3d_shape);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
