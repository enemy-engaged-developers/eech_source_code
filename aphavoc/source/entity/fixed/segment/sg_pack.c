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

void overload_segment_pack_functions (void)
{
	fn_pack_local_entity_data[ENTITY_TYPE_SEGMENT]	= pack_local_data;

	fn_unpack_local_entity_data[ENTITY_TYPE_SEGMENT]	= unpack_local_data;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pack_local_segment_data (pack_modes mode)
{
   entity
      *en;

   segment
      *raw;

	#if DEBUG_MODULE

	static int
		count = 0;

	#endif

	int
		segment_alive,
		segment_count;

   ASSERT (mode != PACK_MODE_UPDATE_ENTITY);

   if (mode == PACK_MODE_BROWSE_SESSION)
   {
      return;
   }

	//
	// RLE segments, only alive ones.
	//

	segment_count = 0;

	segment_alive = TRUE;

	debug_log ("RLE SEGMENT");

	en = get_local_entity_list ();

	while (en)
	{

		if (get_local_entity_type (en) == ENTITY_TYPE_SEGMENT)
		{

			#if DEBUG_MODULE

			count ++;

			#endif

			raw = get_local_entity_data (en);

			if (segment_alive == raw->fix.alive)
			{

				segment_count ++;
			}
			else
			{

				pack_int_value (NULL, INT_TYPE_LENGTH, segment_count);

				pack_int_value (NULL, INT_TYPE_ALIVE, segment_alive);

				segment_alive = raw->fix.alive;

				segment_count = 1;
			}
		}
	
		en = get_local_entity_succ (en);
	}

	pack_int_value (NULL, INT_TYPE_LENGTH, segment_count);

	pack_int_value (NULL, INT_TYPE_ALIVE, segment_alive);

	#if DEBUG_MODULE

	debug_log ("SG_PACK: packing segment data (count = %d)", count);

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void unpack_local_segment_data (pack_modes mode)
{
   entity
      *en,
		*pred,
		*succ;

   segment
      *raw;

	#if DEBUG_MODULE

	static int
		count = 0;

	#endif

	int
		segment_alive,
		segment_count;

   ASSERT (mode != PACK_MODE_UPDATE_ENTITY);

   if (mode == PACK_MODE_BROWSE_SESSION)
   {
      return;
   }

	//
	// unpack alive status for each segment
	//

	debug_log ("RLE SEGMENT");

	segment_count = 0;

	segment_count = unpack_int_value (NULL, INT_TYPE_LENGTH);

	segment_alive = unpack_int_value (NULL, INT_TYPE_ALIVE);

	en = get_local_entity_list ();

	while (en)
	{

		if (en->type == ENTITY_TYPE_SEGMENT)
		{

			#if DEBUG_MODULE

			count ++;

			#endif

			if (segment_count == 0)
			{

				segment_count = unpack_int_value (NULL, INT_TYPE_LENGTH);

				segment_alive = unpack_int_value (NULL, INT_TYPE_ALIVE);
			}

			segment_count --;

			raw = get_local_entity_data (en);

			raw->fix.alive = segment_alive;

			if ((!raw->fix.alive) && (raw->fix.sub_type == ENTITY_SUB_TYPE_FIXED_BRIDGE_UNSUPPORTED_MID_SECTION))
			{
				//
				// position the segment on the ground
				//

				vec3d
					*pos;

				terrain_3d_point_data
					terrain_info;

				pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

				memset (&terrain_info, 0, sizeof (terrain_3d_point_data));

				pos->y = get_3d_terrain_point_data (pos->x, pos->z, &terrain_info);

				if (get_terrain_type_class (terrain_info.terrain_type) == TERRAIN_CLASS_WATER)
				{
					pos->y -= 1.0;
				}
			}
		}

		en = get_local_entity_succ (en);
	}

	#if DEBUG_MODULE

	debug_log ("SG_PACK: unpacking segment data (count = %d)", count);

	#endif

	//
	// determine 3d object for each segment ( some might be damaged / destroyed )
	//

	en = get_local_entity_list ();

	while (en)
	{

		if (en->type == ENTITY_TYPE_SEGMENT)
		{

			raw = get_local_entity_data (en);

			pred = get_local_entity_child_pred (en, LIST_TYPE_SEGMENT);

			succ = get_local_entity_child_succ (en, LIST_TYPE_SEGMENT);

			raw->fix.object_3d_shape = get_bridge_segment_damaged_object (en, pred, succ);
		}

		en = get_local_entity_succ (en);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
