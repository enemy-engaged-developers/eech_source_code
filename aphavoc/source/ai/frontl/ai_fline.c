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



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

#include "ai_fline.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define FRONTLINE_DEBUG 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct FRONTLINE_ARRANGEMENTS
{

	int
		x,
		z;

	entity
		*sector = nullptr;

	unsigned char
		adjacent_count,
		inserted;
};

typedef struct FRONTLINE_ARRANGEMENTS frontline_arrangements;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	number_of_frontline_arrangement_slots_used;

entity
	*frontline_sectors_arrangements_force = nullptr;

frontline_arrangements
	frontline_sectors_arrangements[128*128];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int check_sector_frontline (entity_sides side, int x, int z);

static void recreate_side_frontline (entity *force, int x, int z);

static void parse_frontline_arrangements ( void );

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_frontline (entity *force)
{

	entity_sides
		side;

	entity
		*sector_en = nullptr;

	int
		loop_x,
		loop_z;

	#if FRONTLINE_DEBUG

	debug_log ("FRONTLINE: create front line for faction side %d", get_local_entity_int_value (force, INT_TYPE_SIDE));

	#endif

	unlink_local_entity_children ( force, LIST_TYPE_SECTOR_FRONTLINE );

	number_of_frontline_arrangement_slots_used = 0;

	frontline_sectors_arrangements_force = force;

	side = get_local_entity_int_value (force, INT_TYPE_SIDE);

	for (loop_x = 0; loop_x < NUM_MAP_X_SECTORS; loop_x ++)
	{

		for (loop_z = 0; loop_z < NUM_MAP_Z_SECTORS; loop_z ++)
		{

			if (check_sector_frontline (side, loop_x, loop_z))
			{

				sector_en = get_local_raw_sector_entity (loop_x, loop_z);

				set_local_entity_int_value (sector_en, INT_TYPE_FRONTLINE_FLAG, FRONTLINE_SECTOR_PRIMARY);

				add_sector_to_frontline (force, sector_en);
			}
		}
	}

	parse_frontline_arrangements ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

frontline_sector_types check_sector_frontline (entity_sides side, int x, int z)
{

	entity
		*sector = nullptr;

	int
		loop_x,
		loop_z,
		start_loop_x,
		start_loop_z;

	sector = get_local_raw_sector_entity (x, z);

	if (get_local_entity_int_value (sector, INT_TYPE_SIDE) != side)
	{

		return FRONTLINE_SECTOR_NONE;
	}

	start_loop_x = max (x - 1, 0);

	start_loop_z = max (z - 1, 0);

	for (loop_x = start_loop_x; ((loop_x <= x + 1) && (loop_x < NUM_MAP_X_SECTORS)); loop_x ++)
	{

		for (loop_z = start_loop_z; ((loop_z <= z + 1) && (loop_z < NUM_MAP_Z_SECTORS)); loop_z ++)
		{

			sector = get_local_raw_sector_entity (loop_x, loop_z);

			if (get_local_entity_int_value (sector, INT_TYPE_SIDE) != side)
			{

				return FRONTLINE_SECTOR_PRIMARY;
			}
		}
	}

	return FRONTLINE_SECTOR_NONE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int add_sector_to_frontline (entity *force, entity *sector_en)
{

	sector
		*sector_raw = nullptr;

	sector_raw = get_local_entity_data (sector_en);

	//sector_raw->side = get_local_entity_int_value (force, INT_TYPE_SIDE);
	set_client_server_entity_int_value (sector_en, INT_TYPE_SIDE, get_local_entity_int_value (force, INT_TYPE_SIDE));

	frontline_sectors_arrangements[number_of_frontline_arrangement_slots_used].x = sector_raw->x_sector;
	frontline_sectors_arrangements[number_of_frontline_arrangement_slots_used].z = sector_raw->z_sector;
	frontline_sectors_arrangements[number_of_frontline_arrangement_slots_used].sector = sector_en;
	frontline_sectors_arrangements[number_of_frontline_arrangement_slots_used].adjacent_count = 0;
	frontline_sectors_arrangements[number_of_frontline_arrangement_slots_used].inserted = FALSE;

	number_of_frontline_arrangement_slots_used++;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void parse_frontline_arrangements ( void )
{

	int
		sector_index,
		lowest_adjacent_count,
		lowest_adjacent_count_sector,
		count;

	//
	// Go through calculating all the adjacent_count values for the sectors
	//

	if ( number_of_frontline_arrangement_slots_used <- 0 )
	{

		return;
	}

	for ( count = 0; count < ( number_of_frontline_arrangement_slots_used - 1 ); count++ )
	{

		int
			temp;

		for ( temp = ( count + 1 ); temp < number_of_frontline_arrangement_slots_used; temp++ )
		{

			int
				dx,
				dz;

			dx = abs ( frontline_sectors_arrangements[count].x - frontline_sectors_arrangements[temp].x );
			dz = abs ( frontline_sectors_arrangements[count].z - frontline_sectors_arrangements[temp].z );

			if ( ( ( dx == 1 ) && ( dz == 0 ) ) || ( ( dx == 0 ) && ( dz == 1 ) ) )
			{

				frontline_sectors_arrangements[count].adjacent_count++;
				frontline_sectors_arrangements[temp].adjacent_count++;
			}
		}
	}

	//
	// Go through, finding the start sector ( one with least number of adjacent sectors )
	//

	lowest_adjacent_count = frontline_sectors_arrangements[0].adjacent_count;

	lowest_adjacent_count_sector = 0;

	for ( count = 1; count < ( number_of_frontline_arrangement_slots_used - 1 ); count++ )
	{

		if ( frontline_sectors_arrangements[count].adjacent_count < lowest_adjacent_count )
		{

			lowest_adjacent_count = frontline_sectors_arrangements[count].adjacent_count;
		
			lowest_adjacent_count_sector = count;
		}
	}

	//
	// Insert the first sector into the front line list
	//

	sector_index = lowest_adjacent_count_sector;

	delete_local_entity_from_parents_child_list ( frontline_sectors_arrangements[sector_index].sector, LIST_TYPE_SECTOR_FRONTLINE);

	insert_local_entity_into_parents_child_list ( frontline_sectors_arrangements[sector_index].sector,
																		LIST_TYPE_SECTOR_FRONTLINE,
																		frontline_sectors_arrangements_force, NULL );

	frontline_sectors_arrangements[sector_index].inserted = TRUE;

	//
	// Insert the remaining frontline sectors
	//

	count = number_of_frontline_arrangement_slots_used;

	while ( count )
	{

		int
			index;

		//
		// Get the sector adjacent to the last sector
		//

		for ( index = 0; index < number_of_frontline_arrangement_slots_used; index++ )
		{

			if ( !frontline_sectors_arrangements[index].inserted )
			{
	
				int
					dx,
					dz;
	
				dx = abs ( frontline_sectors_arrangements[index].x - frontline_sectors_arrangements[sector_index].x );
				dz = abs ( frontline_sectors_arrangements[index].z - frontline_sectors_arrangements[sector_index].z );
	
				if ( ( ( dx == 1 ) && ( dz == 0 ) ) || ( ( dx == 0 ) && ( dz == 1 ) ) )
				{

					sector_index = index;

					break;
				}
			}
		}

		delete_local_entity_from_parents_child_list ( frontline_sectors_arrangements[sector_index].sector, LIST_TYPE_SECTOR_FRONTLINE);

		insert_local_entity_into_parents_child_list ( frontline_sectors_arrangements[sector_index].sector,
																			LIST_TYPE_SECTOR_FRONTLINE,
																			frontline_sectors_arrangements_force, NULL );
	
		frontline_sectors_arrangements[sector_index].inserted = TRUE;
	
		count--;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void recreate_frontline (int x, int z)
{

	entity
		*force = nullptr;

	force = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

	while (force)
	{

		create_frontline ( force );

		force = get_local_entity_child_succ (force, LIST_TYPE_FORCE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
