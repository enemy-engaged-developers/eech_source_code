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

#include "terrain.h"

#include "misc.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	maximum_number_of_terrain_objects,
	number_of_terrain_objects;

terrain_3d_object
	*terrain_object_slots = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_terrain_objects ( void )
{

	int
		x,
		z;

	ASSERT ( terrain_sectors );

	//
	// Go through all the terrain sectors setting the objects pointer to NULL
	//

	debug_log ( "RESETTING TERRAIN OBJECTS & POINTERS" );

	for ( z = 0; z < terrain_3d_sector_z_max; z++ )
	{

		for ( x = 0; x < terrain_3d_sector_x_max; x++ )
		{

			terrain_sectors[z][x].objects = NULL;
		}
	}

	maximum_number_of_terrain_objects = 0;

	number_of_terrain_objects = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_number_of_terrain_objects ( int number )
{

	maximum_number_of_terrain_objects = number;

	ASSERT ( maximum_number_of_terrain_objects );

	if ( terrain_object_slots )
	{

		safe_free ( terrain_object_slots );
	}

	terrain_object_slots = safe_malloc ( maximum_number_of_terrain_objects * sizeof ( struct TERRAIN_3D_OBJECT ) );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert_3d_object_into_terrain ( object_3d_instance *object )
{

	int
		x,
		z;

	ASSERT ( terrain_object_slots );

	ASSERT ( number_of_terrain_objects < maximum_number_of_terrain_objects );

	ASSERT ( position_on_3d_terrain ( object->vp.x, object->vp.z ) );

	get_terrain_3d_sector ( object->vp.position.x, object->vp.position.z, &x, &z );

	terrain_object_slots[number_of_terrain_objects].object = object;

	terrain_object_slots[number_of_terrain_objects].next_object = terrain_sectors[z][x].objects;

	terrain_sectors[z][x].objects = &terrain_object_slots[number_of_terrain_objects];

	number_of_terrain_objects++;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

