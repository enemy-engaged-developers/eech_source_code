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

#include "ai_sect.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*static*/ void initialise_ai_sector_exposure (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_ai_sectors (void)
{

//	initialise_ai_sector_exposure ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_ai_sector_exposure (void)
{

	entity
		*sector;

   int
		min_terrain_height,
		max_terrain_height,
		delta_value,
		value,
      x,
      z;

	//
	// find the min and max heights of the terrain to allow the exposure value to be scaled.
	//

   for (x = 0; x < (NUM_MAP_X_SECTORS * 2); x ++)
   {

      for (z = 0; z < (NUM_MAP_Z_SECTORS * 2); z ++)
      {

			if (terrain_sectors [z][x].maximum_height > max_terrain_height)
			{

				max_terrain_height = terrain_sectors [z][x].maximum_height;
			}

			if (terrain_sectors [z][x].minimum_height < min_terrain_height)
			{

				min_terrain_height = terrain_sectors [z][x].minimum_height;
			}
		}
	}

	#if DEBUG_MODULE

	debug_log ("AI_SECT: Terrain min height %d, max height %d", min_terrain_height, max_terrain_height);

	#endif

	//
	// exposure is the average delta height of the 4 sectors in an ai sector. Roughly scaled to 0 -> 255
	//

   for (x = 0; x < NUM_MAP_X_SECTORS; x ++)
   {

      for (z = 0; z < NUM_MAP_Z_SECTORS; z ++)
      {

         value =
            (((terrain_sectors [(z * 2) + 0][(x * 2) + 0].average_height - min_terrain_height) * 256) / (max_terrain_height - min_terrain_height) +
            ((terrain_sectors [(z * 2) + 1][(x * 2) + 0].average_height - min_terrain_height) * 256) / (max_terrain_height - min_terrain_height) +
            ((terrain_sectors [(z * 2) + 0][(x * 2) + 1].average_height - min_terrain_height) * 256) / (max_terrain_height - min_terrain_height) +
            ((terrain_sectors [(z * 2) + 1][(x * 2) + 1].average_height - min_terrain_height) * 256) / (max_terrain_height - min_terrain_height)) / 4;

			delta_value =
            (abs (value - ((terrain_sectors [(z * 2) + 0][(x * 2) + 0].average_height - min_terrain_height) * 256) / (max_terrain_height - min_terrain_height)) +
            abs (value - ((terrain_sectors [(z * 2) + 1][(x * 2) + 0].average_height - min_terrain_height) * 256) / (max_terrain_height - min_terrain_height)) +
            abs (value - ((terrain_sectors [(z * 2) + 0][(x * 2) + 1].average_height - min_terrain_height) * 256) / (max_terrain_height - min_terrain_height)) +
            abs (value - ((terrain_sectors [(z * 2) + 1][(x * 2) + 1].average_height - min_terrain_height) * 256) / (max_terrain_height - min_terrain_height))) * 2;

			// add some kind of forest check.

			delta_value = bound (delta_value, 0, 255);

			#if DEBUG_MODULE

			debug_log ("AI_SECT: sector %d, %d exposure level = %d, delta value = %d", x, z, value, delta_value);

			#endif

			sector = get_local_raw_sector_entity (x, z);

			set_local_entity_int_value (sector, INT_TYPE_EXPOSURE_LEVEL, delta_value);
      }
   }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


