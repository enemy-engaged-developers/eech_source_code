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

world_map_data
	world_map;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_entity_world_map_size (int num_map_x_sectors, int num_map_z_sectors, int sector_side_length)
{
	ASSERT (num_map_x_sectors > 0);

	ASSERT (num_map_z_sectors > 0);

	ASSERT (int_bit_count (sector_side_length) == 1);

	world_map.sector_side_length			= sector_side_length;

	world_map.sector_side_length_mask	= sector_side_length - 1;

	world_map.num_map_x_sectors			= num_map_x_sectors;
	world_map.num_map_z_sectors			= num_map_z_sectors;

	world_map.num_map_sectors				= num_map_x_sectors * num_map_z_sectors;

	world_map.min_map_x_sector	 			= 0;
	world_map.min_map_z_sector	  	 		= 0;

	world_map.max_map_x_sector		  		= num_map_x_sectors - 1;
	world_map.max_map_z_sector				= num_map_z_sectors - 1;

	world_map.min_map_x	 					= 0.0;
	world_map.min_map_y						= -8000.0;
	world_map.min_map_z						= 0.0;

	world_map.max_map_x						= (float) (num_map_x_sectors * sector_side_length) - 1.0;	// ***** DO NOT CHANGE 1.0 *****
	world_map.max_map_y						= 65535.0;				 										
	world_map.max_map_z		  				= (float) (num_map_z_sectors * sector_side_length) - 1.0;	// ***** DO NOT CHANGE 1.0 *****

	world_map.mid_map_x 						= world_map.min_map_x + ((world_map.max_map_x - world_map.min_map_x) * 0.5);
	world_map.mid_map_y						= world_map.min_map_y + ((world_map.max_map_y - world_map.min_map_y) * 0.5);
	world_map.mid_map_z						= world_map.min_map_z + ((world_map.max_map_z - world_map.min_map_z) * 0.5);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int bound_position_to_map_area (vec3d *position)
{
	int
		result;

	result = FALSE;

	if (position->x < MIN_MAP_X)
	{
		position->x = MIN_MAP_X;

		result = TRUE;
	}
	else if (position->x > MAX_MAP_X)
	{
		position->x = MAX_MAP_X;

		result = TRUE;
	}

	if (position->z < MIN_MAP_Z)
	{
		position->z = MIN_MAP_Z;

		result = TRUE;
	}
	else if (position->z > MAX_MAP_Z)
	{
		position->z = MAX_MAP_Z;

		result = TRUE;
	}

	return (result);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int bound_position_to_adjusted_map_area (vec3d *position)
{
	int
		result;

	result = FALSE;

	if (position->x < MIN_MAP_X + MAP_PERIMETER_SIZE)
	{
		position->x = MIN_MAP_X + MAP_PERIMETER_SIZE;

		result = TRUE;
	}
	else if (position->x > MAX_MAP_X - MAP_PERIMETER_SIZE)
	{
		position->x = MAX_MAP_X - MAP_PERIMETER_SIZE;

		result = TRUE;
	}

	if (position->z < MIN_MAP_Z + MAP_PERIMETER_SIZE)
	{
		position->z = MIN_MAP_Z + MAP_PERIMETER_SIZE;

		result = TRUE;
	}
	else if (position->z > MAX_MAP_Z - MAP_PERIMETER_SIZE)
	{
		position->z = MAX_MAP_Z - MAP_PERIMETER_SIZE;

		result = TRUE;
	}

	return (result);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int bound_position_to_map_volume (vec3d *position)
{
	int
		result;

	result = FALSE;

	if (position->x < MIN_MAP_X)
	{
		position->x = MIN_MAP_X;

		result = TRUE;
	}
	else if (position->x > MAX_MAP_X)
	{
		position->x = MAX_MAP_X;

		result = TRUE;
	}

	if (position->y < MIN_MAP_Y)
	{
		position->y = MIN_MAP_Y;

		result = TRUE;
	}
	else if (position->y > MAX_MAP_Y)
	{
		position->y = MAX_MAP_Y;

		result = TRUE;
	}

	if (position->z < MIN_MAP_Z)
	{
		position->z = MIN_MAP_Z;

		result = TRUE;
	}
	else if (position->z > MAX_MAP_Z)
	{
		position->z = MAX_MAP_Z;

		result = TRUE;
	}

	return (result);
}

int bound_double_position_to_map_volume (double_vec3d *position)
{
	int
		result;

	result = FALSE;

	if (position->x < MIN_MAP_X)
	{
		position->x = MIN_MAP_X;

		result = TRUE;
	}
	else if (position->x > MAX_MAP_X)
	{
		position->x = MAX_MAP_X;

		result = TRUE;
	}

	if (position->y < MIN_MAP_Y)
	{
		position->y = MIN_MAP_Y;

		result = TRUE;
	}
	else if (position->y > MAX_MAP_Y)
	{
		position->y = MAX_MAP_Y;

		result = TRUE;
	}

	if (position->z < MIN_MAP_Z)
	{
		position->z = MIN_MAP_Z;

		result = TRUE;
	}
	else if (position->z > MAX_MAP_Z)
	{
		position->z = MAX_MAP_Z;

		result = TRUE;
	}

	return (result);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int bound_position_to_adjusted_map_volume (vec3d *position)
{
	int
		result;

	result = FALSE;

	if (position->x < MIN_MAP_X + MAP_PERIMETER_SIZE)
	{
		position->x = MIN_MAP_X + MAP_PERIMETER_SIZE;

		result = TRUE;
	}
	else if (position->x > MAX_MAP_X - MAP_PERIMETER_SIZE)
	{
		position->x = MAX_MAP_X - MAP_PERIMETER_SIZE;

		result = TRUE;
	}

	if (position->y < MIN_MAP_Y)
	{
		position->y = MIN_MAP_Y;

		result = TRUE;
	}
	else if (position->y > MAX_MAP_Y)
	{
		position->y = MAX_MAP_Y;

		result = TRUE;
	}

	if (position->z < MIN_MAP_Z + MAP_PERIMETER_SIZE)
	{
		position->z = MIN_MAP_Z + MAP_PERIMETER_SIZE;

		result = TRUE;
	}
	else if (position->z > MAX_MAP_Z - MAP_PERIMETER_SIZE)
	{
		position->z = MAX_MAP_Z - MAP_PERIMETER_SIZE;

		result = TRUE;
	}

	return (result);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int bound_double_position_to_adjusted_map_volume (double_vec3d *position)
{
	int
		result;

	result = FALSE;

	if (position->x < MIN_MAP_X + MAP_PERIMETER_SIZE)
	{
		position->x = MIN_MAP_X + MAP_PERIMETER_SIZE;

		result = TRUE;
	}
	else if (position->x > MAX_MAP_X - MAP_PERIMETER_SIZE)
	{
		position->x = MAX_MAP_X - MAP_PERIMETER_SIZE;

		result = TRUE;
	}

	if (position->y < MIN_MAP_Y)
	{
		position->y = MIN_MAP_Y;

		result = TRUE;
	}
	else if (position->y > MAX_MAP_Y)
	{
		position->y = MAX_MAP_Y;

		result = TRUE;
	}

	if (position->z < MIN_MAP_Z + MAP_PERIMETER_SIZE)
	{
		position->z = MIN_MAP_Z + MAP_PERIMETER_SIZE;

		result = TRUE;
	}
	else if (position->z > MAX_MAP_Z - MAP_PERIMETER_SIZE)
	{
		position->z = MAX_MAP_Z - MAP_PERIMETER_SIZE;

		result = TRUE;
	}

	return (result);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
