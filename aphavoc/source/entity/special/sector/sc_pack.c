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

void overload_sector_pack_functions (void)
{
	fn_pack_local_entity_data[ENTITY_TYPE_SECTOR]		= pack_local_data;

	fn_unpack_local_entity_data[ENTITY_TYPE_SECTOR]	= unpack_local_data;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pack_local_sector_data (pack_modes mode)
{
	entity
		*en = nullptr;

	sector
		*raw = nullptr;

	entity_sides
		current_side;

	int
		sector_pack_size,
		side_count,
		x_sec,
		z_sec,
		total_side_count;

	ASSERT (mode != PACK_MODE_UPDATE_ENTITY);

	if (mode == PACK_MODE_BROWSE_SESSION)
	{
		return;
	}

	//
	// RLE encode the sector sides
	//

	debug_log ("RLE SECTOR");

	sector_pack_size = 0;

	en = get_local_raw_sector_entity (0, 0);

	raw = (sector *) get_local_entity_data (en);

	pack_int_value (NULL, INT_TYPE_SIDE, raw->side);

	sector_pack_size += NUM_SIDE_BITS;

	current_side = (entity_sides) raw->side;

	side_count = 0;

	total_side_count = 0;

	for (z_sec = MIN_MAP_Z_SECTOR; z_sec <= MAX_MAP_Z_SECTOR; z_sec++)
	{

		for (x_sec = MIN_MAP_X_SECTOR; x_sec <= MAX_MAP_X_SECTOR; x_sec++)
		{

			en = get_local_raw_sector_entity(x_sec, z_sec);

			raw = (sector *) get_local_entity_data (en);

			if (current_side != raw->side)
			{

				current_side = (entity_sides) raw->side;

				pack_int_value (NULL, INT_TYPE_LENGTH, side_count);

				#if DEBUG_MODULE

				debug_log ("SC_PACK : packed %d sectors for %s", side_count, entity_side_names [current_side]);

				#endif

				total_side_count += side_count;

				sector_pack_size += NUM_LENGTH_BITS;

				pack_int_value (NULL, INT_TYPE_SIDE, raw->side);

				sector_pack_size += NUM_SIDE_BITS;

				side_count = 1;
			}
			else
			{

				side_count ++;
			}
		}
	}

	pack_int_value (NULL, INT_TYPE_LENGTH, side_count);

	#if DEBUG_MODULE

	debug_log ("SC_PACK : packed %d sectors for %s", side_count, entity_side_names [current_side]);

	#endif

	total_side_count += side_count;

	sector_pack_size += NUM_LENGTH_BITS;

	//
	// Termination
	//

	pack_int_value (NULL, INT_TYPE_SIDE, ENTITY_SIDE_NEUTRAL);
	sector_pack_size += NUM_SIDE_BITS;

	pack_int_value (NULL, INT_TYPE_LENGTH, 0);
	sector_pack_size += NUM_LENGTH_BITS;

	debug_log ("SC_PACK : packed %d sectors", total_side_count);

	ASSERT (total_side_count == (NUM_MAP_Z_SECTORS * NUM_MAP_X_SECTORS));

	//
	// Pack FOG OF WAR
	//

	for (z_sec = MIN_MAP_Z_SECTOR; z_sec <= MAX_MAP_Z_SECTOR; z_sec++)
	{
		for (x_sec = MIN_MAP_X_SECTOR; x_sec <= MAX_MAP_X_SECTOR; x_sec++)
		{
			en = get_local_raw_sector_entity(x_sec, z_sec);

			raw = (sector *) get_local_entity_data (en);

			pack_float_value (en, FLOAT_TYPE_FOG_OF_WAR, raw->fog_of_war [ENTITY_SIDE_BLUE_FORCE]);
			pack_float_value (en, FLOAT_TYPE_FOG_OF_WAR, raw->fog_of_war [ENTITY_SIDE_RED_FORCE]);
		}
	}

	//
	// If saving game write out sector values (threat etc)
	//

	if (mode == PACK_MODE_SERVER_SESSION)
	{

		for (z_sec = MIN_MAP_Z_SECTOR; z_sec <= MAX_MAP_Z_SECTOR; z_sec++)
		{

			for (x_sec = MIN_MAP_X_SECTOR; x_sec <= MAX_MAP_X_SECTOR; x_sec++)
			{

				en = get_local_raw_sector_entity(x_sec, z_sec);

				raw = (sector *) get_local_entity_data (en);

				/////////////////////////////////////////////////////////////////
				if (raw->sector_task_root.first_child)
				{

					pack_int_value (en, INT_TYPE_VALID, TRUE);

					pack_list_root (en, LIST_TYPE_SECTOR_TASK, &raw->sector_task_root);
				}
				else
				{

					pack_int_value (en, INT_TYPE_VALID, FALSE);
				}
				/////////////////////////////////////////////////////////////////

				// TODO: should probably save the other elements of the list which doesn't have the construct_locally attribute
				if (raw->special_effect_root.first_child
					&& !effect_database [get_local_entity_int_value (raw->special_effect_root.first_child, INT_TYPE_ENTITY_SUB_TYPE)].constructed_locally)
				{
					pack_int_value (en, INT_TYPE_VALID, TRUE);

					pack_list_root (en, LIST_TYPE_SPECIAL_EFFECT, &raw->special_effect_root);
				}
				else
				{

					pack_int_value (en, INT_TYPE_VALID, FALSE);
				}

				//debug_log ("SC_PACK: packing sector %d, %d", raw->x_sector, raw->z_sector);

				pack_int_value (en, INT_TYPE_CAMPAIGN_CRITERIA_COUNT, raw->keysite_count);

				pack_float_value (en, FLOAT_TYPE_PROTOTYPE_1, raw->tallest_structure_height);
			}
		}
	}

	//debug_log ("SC_PACK: packing %d sectors took %d bytes (%d bits)", NUM_MAP_X_SECTORS * NUM_MAP_Z_SECTORS, sector_pack_size / 8, sector_pack_size);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void unpack_local_sector_data (pack_modes mode)
{

	entity
		*en = nullptr;

	sector
		*raw = nullptr;

	entity_sides
		side;

	int
		z_sec,
		x_sec,
		side_count;

	ASSERT (mode != PACK_MODE_UPDATE_ENTITY);

	if (mode == PACK_MODE_BROWSE_SESSION)
	{
		return;
	}

	//
	// RLE unencode the sector sides
	//

	debug_log ("RLE SECTOR");

	en = NULL;

	side = (entity_sides) unpack_int_value (NULL, INT_TYPE_SIDE);

	side_count = unpack_int_value (NULL, INT_TYPE_LENGTH);

	en = *entity_sector_map;

	while (side_count != 0)
	{

		while (side_count > 0)
		{

			raw = (sector *) get_local_entity_data (en);

			raw->side = side;

			side_count --;

			en ++;
		}

		side = (entity_sides) unpack_int_value (NULL, INT_TYPE_SIDE);

		side_count = unpack_int_value (NULL, INT_TYPE_LENGTH);
	}

	//
	// Unpack FOG OF WAR
	//

	for (z_sec = MIN_MAP_Z_SECTOR; z_sec <= MAX_MAP_Z_SECTOR; z_sec++)
	{
		for (x_sec = MIN_MAP_X_SECTOR; x_sec <= MAX_MAP_X_SECTOR; x_sec++)
		{
			en = get_local_raw_sector_entity(x_sec, z_sec);

			raw = (sector *) get_local_entity_data (en);

			raw->fog_of_war [ENTITY_SIDE_BLUE_FORCE] = unpack_float_value (en, FLOAT_TYPE_FOG_OF_WAR);
			raw->fog_of_war [ENTITY_SIDE_RED_FORCE] = unpack_float_value (en, FLOAT_TYPE_FOG_OF_WAR);
		}
	}

	//
	// If loading game read in sector values (threat etc)
	//

	if (mode == PACK_MODE_SERVER_SESSION)
	{

		for (z_sec = MIN_MAP_Z_SECTOR; z_sec <= MAX_MAP_Z_SECTOR; z_sec++)
		{

			for (x_sec = MIN_MAP_X_SECTOR; x_sec <= MAX_MAP_X_SECTOR; x_sec++)
			{

				en = get_local_raw_sector_entity(x_sec, z_sec);

				raw = (sector *) get_local_entity_data (en);

				if (unpack_int_value (en, INT_TYPE_VALID))
				{

					unpack_list_root (en, LIST_TYPE_SECTOR_TASK, &raw->sector_task_root);
				}

				if (unpack_int_value (en, INT_TYPE_VALID))
				{

					unpack_list_root (en, LIST_TYPE_SPECIAL_EFFECT, &raw->special_effect_root);
				}

				//debug_log ("SC_PACK: unpacking sector %d, %d", raw->x_sector, raw->z_sector);

				raw->keysite_count = unpack_int_value (en, INT_TYPE_CAMPAIGN_CRITERIA_COUNT);

				raw->tallest_structure_height = unpack_float_value (en, FLOAT_TYPE_PROTOTYPE_1);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
