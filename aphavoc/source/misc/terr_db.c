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

static terrain_database_type
	terrain_database [TERRAIN_TYPE_LAST];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_terrain_database_element (terrain_types type, terrain_classes class, int draw_crater, int raised, int suitable_for_ground_vehicle)
{

	ASSERT (type >= TERRAIN_TYPE_INVALID);
	ASSERT (type < TERRAIN_TYPE_LAST);

	terrain_database [type].class = class;

	terrain_database [type].draw_crater = draw_crater;

	terrain_database [type].raised = raised;

	terrain_database [type].suitable_for_ground_vehicle = suitable_for_ground_vehicle;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

terrain_classes get_terrain_type_class ( terrain_types type )
{
	ASSERT (type >= TERRAIN_TYPE_INVALID);
	ASSERT (type < TERRAIN_TYPE_LAST);

	return terrain_database [type].class;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_terrain_type_draw_crater (terrain_types type)
{
	ASSERT (type >= TERRAIN_TYPE_INVALID);
	ASSERT (type < TERRAIN_TYPE_LAST);

	return terrain_database [type].draw_crater;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_terrain_type_raised (terrain_types type)
{
	ASSERT (type >= TERRAIN_TYPE_INVALID);
	ASSERT (type < TERRAIN_TYPE_LAST);

	return terrain_database [type].raised;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_terrain_type_suitable_for_ground_vehicle (terrain_types type)
{
	ASSERT (type >= TERRAIN_TYPE_INVALID);
	ASSERT (type < TERRAIN_TYPE_LAST);

	return terrain_database [type].suitable_for_ground_vehicle;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_terrain_database ()
{

	//
	// parameters : (type, class, draw_crater, raised, suitable_for_ground_vehicle)
	//

	set_terrain_database_element (TERRAIN_TYPE_INVALID, TERRAIN_CLASS_INVALID, FALSE, FALSE, FALSE);

	// Sunken features tops
	set_terrain_database_element (TERRAIN_TYPE_RIVER, TERRAIN_CLASS_WATER, FALSE, FALSE, FALSE);
	set_terrain_database_element (TERRAIN_TYPE_RESERVOIR, TERRAIN_CLASS_WATER, FALSE, FALSE, FALSE);
	set_terrain_database_element (TERRAIN_TYPE_TRENCH, TERRAIN_CLASS_LAND, FALSE, TRUE, FALSE);

	// Sunken features banks
	set_terrain_database_element (TERRAIN_TYPE_RIVER_BANK, TERRAIN_CLASS_LAND, TRUE, FALSE, FALSE);

	// Regular terrain types
	set_terrain_database_element (TERRAIN_TYPE_SEA, TERRAIN_CLASS_WATER, FALSE, FALSE, FALSE);

	set_terrain_database_element (TERRAIN_TYPE_BEACH, TERRAIN_CLASS_LAND, TRUE, FALSE, TRUE);

	set_terrain_database_element (TERRAIN_TYPE_LAND, TERRAIN_CLASS_LAND, TRUE, FALSE, TRUE);

	set_terrain_database_element (TERRAIN_TYPE_FIELD1, TERRAIN_CLASS_LAND, TRUE, FALSE, FALSE);
	set_terrain_database_element (TERRAIN_TYPE_FIELD2, TERRAIN_CLASS_LAND, TRUE, FALSE, FALSE);
	set_terrain_database_element (TERRAIN_TYPE_FIELD3, TERRAIN_CLASS_LAND, TRUE, FALSE, FALSE);
	set_terrain_database_element (TERRAIN_TYPE_FIELD4, TERRAIN_CLASS_LAND, TRUE, FALSE, FALSE);
	set_terrain_database_element (TERRAIN_TYPE_FIELD5, TERRAIN_CLASS_LAND, TRUE, FALSE, FALSE);
	set_terrain_database_element (TERRAIN_TYPE_FIELD6, TERRAIN_CLASS_LAND, TRUE, FALSE, FALSE);
	set_terrain_database_element (TERRAIN_TYPE_FIELD7, TERRAIN_CLASS_LAND, TRUE, FALSE, FALSE);
	set_terrain_database_element (TERRAIN_TYPE_FIELD8, TERRAIN_CLASS_LAND, TRUE, FALSE, FALSE);
	set_terrain_database_element (TERRAIN_TYPE_FIELD9, TERRAIN_CLASS_LAND, TRUE, FALSE, FALSE);
	set_terrain_database_element (TERRAIN_TYPE_FIELD10, TERRAIN_CLASS_LAND, TRUE, FALSE, FALSE);
	set_terrain_database_element (TERRAIN_TYPE_FIELD11, TERRAIN_CLASS_LAND, TRUE, FALSE, FALSE);

	set_terrain_database_element (TERRAIN_TYPE_ALTERED_LAND1, TERRAIN_CLASS_LAND, TRUE, FALSE, TRUE);
	set_terrain_database_element (TERRAIN_TYPE_ALTERED_LAND2, TERRAIN_CLASS_LAND, TRUE, FALSE, TRUE);
	set_terrain_database_element (TERRAIN_TYPE_ALTERED_LAND3, TERRAIN_CLASS_LAND, TRUE, FALSE, TRUE);

	set_terrain_database_element (TERRAIN_TYPE_FOREST_FLOOR, TERRAIN_CLASS_LAND, TRUE, FALSE, FALSE);

	// Raised features banks
	set_terrain_database_element (TERRAIN_TYPE_ROAD_BANK, TERRAIN_CLASS_LAND, TRUE, FALSE, TRUE);
	set_terrain_database_element (TERRAIN_TYPE_RAIL_BANK, TERRAIN_CLASS_LAND, TRUE, FALSE, TRUE);

	// Raised features sides
	set_terrain_database_element (TERRAIN_TYPE_HEDGE_SIDE_X, TERRAIN_CLASS_LAND, FALSE, TRUE, FALSE);
	set_terrain_database_element (TERRAIN_TYPE_HEDGE_SIDE_Z, TERRAIN_CLASS_LAND, FALSE, TRUE, FALSE);
	set_terrain_database_element (TERRAIN_TYPE_WALL_SIDE_X, TERRAIN_CLASS_LAND, FALSE, TRUE, FALSE);
	set_terrain_database_element (TERRAIN_TYPE_WALL_SIDE_Z, TERRAIN_CLASS_LAND, FALSE, TRUE, FALSE);
	set_terrain_database_element (TERRAIN_TYPE_TRENCH_SIDE_X, TERRAIN_CLASS_LAND, FALSE, TRUE, FALSE);
	set_terrain_database_element (TERRAIN_TYPE_TRENCH_SIDE_Z, TERRAIN_CLASS_LAND, FALSE, TRUE, FALSE);
	set_terrain_database_element (TERRAIN_TYPE_FOREST_SIDE_BOTTOM_X, TERRAIN_CLASS_FOREST, FALSE, TRUE, FALSE);
	set_terrain_database_element (TERRAIN_TYPE_FOREST_SIDE_BOTTOM_Z, TERRAIN_CLASS_FOREST, FALSE, TRUE, FALSE);
	set_terrain_database_element (TERRAIN_TYPE_FOREST_SIDE_MID_X, TERRAIN_CLASS_FOREST, FALSE, TRUE, FALSE);
	set_terrain_database_element (TERRAIN_TYPE_FOREST_SIDE_MID_Z, TERRAIN_CLASS_FOREST, FALSE, TRUE, FALSE);
	set_terrain_database_element (TERRAIN_TYPE_FOREST_SIDE_TOP_X, TERRAIN_CLASS_FOREST, FALSE, TRUE, FALSE);
	set_terrain_database_element (TERRAIN_TYPE_FOREST_SIDE_TOP_Z, TERRAIN_CLASS_FOREST, FALSE, TRUE, FALSE);

	// Raised features tops
	set_terrain_database_element (TERRAIN_TYPE_BUILT_UP_AREA1, TERRAIN_CLASS_LAND, TRUE, FALSE, TRUE);
	set_terrain_database_element (TERRAIN_TYPE_BUILT_UP_AREA2, TERRAIN_CLASS_LAND, TRUE, FALSE, TRUE);
	set_terrain_database_element (TERRAIN_TYPE_BUILT_UP_AREA3, TERRAIN_CLASS_LAND, TRUE, FALSE, TRUE);
	set_terrain_database_element (TERRAIN_TYPE_BUILT_UP_AREA4, TERRAIN_CLASS_LAND, TRUE, FALSE, TRUE);
	set_terrain_database_element (TERRAIN_TYPE_ROAD, TERRAIN_CLASS_LAND, TRUE, FALSE, TRUE);
	set_terrain_database_element (TERRAIN_TYPE_TRACK, TERRAIN_CLASS_LAND, TRUE, FALSE, TRUE);
	set_terrain_database_element (TERRAIN_TYPE_RAIL, TERRAIN_CLASS_LAND, TRUE, FALSE, TRUE);

	set_terrain_database_element (TERRAIN_TYPE_WALL_TOP, TERRAIN_CLASS_LAND, FALSE, TRUE, FALSE);
	set_terrain_database_element (TERRAIN_TYPE_HEDGE_TOP, TERRAIN_CLASS_LAND, FALSE, TRUE, FALSE);

	set_terrain_database_element (TERRAIN_TYPE_FOREST_TOP, TERRAIN_CLASS_FOREST, FALSE, TRUE, FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



