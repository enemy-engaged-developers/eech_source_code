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
//
// Sector entities are local only.
//
// They must be created before any client/server entities to ensure that the index numbers correspond on each machine.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_local_sector_entities (void)
{
	static int
		old_min_map_z_sector = -1,
		old_max_map_z_sector = -1,
		old_num_map_z_sectors = -1,
		old_min_map_x_sector = -1,
		old_max_map_x_sector = -1,
		old_num_map_x_sectors = -1;

	int
		x_sec,
		z_sec;

	//
	// First time setup
	//

	if (old_min_map_z_sector == -1)
	{
		old_min_map_z_sector = MIN_MAP_Z_SECTOR;

		old_max_map_z_sector = MAX_MAP_Z_SECTOR;

		old_num_map_z_sectors = NUM_MAP_Z_SECTORS;

		old_min_map_x_sector = MIN_MAP_X_SECTOR;

		old_max_map_x_sector = MAX_MAP_X_SECTOR;

		old_num_map_x_sectors = NUM_MAP_X_SECTORS;
	}

	//
	// Deinitialise sectors (must be the 'old' map size)
	//

	if (entity_sector_map)
	{
		for (z_sec = old_min_map_z_sector; z_sec <= old_max_map_z_sector; z_sec ++)
		{
			for (x_sec = old_min_map_x_sector; x_sec <= old_max_map_x_sector; x_sec ++)
			{
				if (entity_sector_map [x_sec + (z_sec * old_num_map_x_sectors)]->type != ENTITY_TYPE_UNKNOWN)
				{
					debug_fatal ("SC_CREAT: uninitialised sector entity");
				}
			}
		}

		free_mem (entity_sector_map);
	}

	//
	// Store new map size
	//

	old_min_map_z_sector = MIN_MAP_Z_SECTOR;

	old_max_map_z_sector = MAX_MAP_Z_SECTOR;

	old_num_map_z_sectors = NUM_MAP_Z_SECTORS;

	old_min_map_x_sector = MIN_MAP_X_SECTOR;

	old_max_map_x_sector = MAX_MAP_X_SECTOR;

	old_num_map_x_sectors = NUM_MAP_X_SECTORS;

	//
	// Malloc memory
	//

	entity_sector_map = (entity **) malloc_heap_mem (sizeof (entity) * NUM_MAP_X_SECTORS * NUM_MAP_Z_SECTORS);

	//
	// Create sector entities
	//

	for (z_sec = MIN_MAP_Z_SECTOR; z_sec <= MAX_MAP_Z_SECTOR; z_sec++)
	{
		for (x_sec = MIN_MAP_X_SECTOR; x_sec <= MAX_MAP_X_SECTOR; x_sec++)
		{
			entity_sector_map[x_sec + (z_sec * NUM_MAP_X_SECTORS)] = create_local_entity
			(
				ENTITY_TYPE_SECTOR,
				ENTITY_INDEX_DONT_CARE,
				ENTITY_ATTR_INT_VALUE (INT_TYPE_X_SECTOR, x_sec),
				ENTITY_ATTR_INT_VALUE (INT_TYPE_Z_SECTOR, z_sec),
				ENTITY_ATTR_END
			);
		}
	}

	debug_log ("SC_CREAT: creating sectors. Start entity %d", get_local_entity_index (entity_sector_map [0]));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *create_local (entity_types type, int index, char *pargs)
{
	entity
		*en;

	sector
		*raw;

	////////////////////////////////////////
  	//
  	// VALIDATE
  	//
	////////////////////////////////////////

	validate_local_create_entity_index (index);

	#if DEBUG_MODULE

	debug_log_entity_args (ENTITY_DEBUG_LOCAL, ENTITY_DEBUG_CREATE, NULL, type, index);

	#endif

	en = get_free_entity (index);

	if (en)
	{
		////////////////////////////////////////
   	//
   	// MALLOC ENTITY DATA
   	//
		////////////////////////////////////////

		set_local_entity_type (en, type);

		raw = (sector *) malloc_fast_mem (sizeof (sector));

		set_local_entity_data (en, raw);

		////////////////////////////////////////
   	//
   	// INITIALISE ALL ENTITY DATA TO 'WORKING' DEFAULT VALUES
		//
		// DO NOT USE ACCESS FUNCTIONS
		//
		// DO NOT USE RANDOM VALUES
		//
		////////////////////////////////////////

		memset (raw, 0, sizeof (sector));

		////////////////////////////////////////
		//
		// OVERWRITE DEFAULT VALUES WITH GIVEN ATTRIBUTES
		//
		////////////////////////////////////////

		set_local_entity_attributes (en, pargs);

		////////////////////////////////////////
		//
		// CHECK MANDATORY ATTRIBUTES HAVE BEEN GIVEN
		//
		////////////////////////////////////////

		////////////////////////////////////////
		//
		// RESOLVE DEFAULT VALUES
		//
		////////////////////////////////////////

		////////////////////////////////////////
		//
		// LINK INTO SYSTEM
		//
		////////////////////////////////////////
	}

	return (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_sector_create_functions (void)
{
	fn_create_local_entity[ENTITY_TYPE_SECTOR] = create_local;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
