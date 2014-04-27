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

static void set_supply_heat_map_cargo_spot (entity *en, int x, int z, int value);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
unsigned char
	*supply_heat_bitmap = NULL;

unsigned char
	*supply_heat_map = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
float get_local_entity_rearming_sleep_time (entity *group, int weapon_type)
{

	float
		base_time,	
		sleep_time;

	if(!weapon_type)
		base_time = get_local_entity_float_value (group, FLOAT_TYPE_REARMING_TIME);
	else
		base_time = weapon_database[weapon_type].rearming_time;

	sleep_time = base_time * ( -(MAX_REARMING_TIME_SCALING_FACTOR - 1.0) / 100.0 * get_local_entity_float_value (group, FLOAT_TYPE_AMMO_SUPPLY_LEVEL) + MAX_REARMING_TIME_SCALING_FACTOR);

	#if DEBUG_MODULE || DEBUG_SUPPLY

	debug_log ("EN_SUPLY: SUPPLY_INFO: group %s rearming sleep time = %f (normal_time = %f, supply level = %f)",
					get_local_entity_string (group, STRING_TYPE_FULL_NAME),
					sleep_time,
					base_time,
					get_local_entity_float_value (group, FLOAT_TYPE_AMMO_SUPPLY_LEVEL));

	#endif

	return sleep_time;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_local_entity_refueling_sleep_time (entity *group)
{

	float
		sleep_time;

	// using rearming time for the moment...
	sleep_time = get_local_entity_float_value (group, FLOAT_TYPE_REARMING_TIME);

	sleep_time *= -(((MAX_REFUELING_TIME_SCALING_FACTOR - 1.0) / 100.0) * get_local_entity_float_value (group, FLOAT_TYPE_FUEL_SUPPLY_LEVEL)) + MAX_REARMING_TIME_SCALING_FACTOR;

	#if DEBUG_MODULE || DEBUG_SUPPLY

	debug_log ("EN_SUPLY: SUPPLY_INFO: group %s refueling sleep time = %f (normal_time = %f, supply level = %f)",
					get_local_entity_string (group, STRING_TYPE_FULL_NAME),
					sleep_time,
					get_local_entity_float_value (group, FLOAT_TYPE_REARMING_TIME),
					get_local_entity_float_value (group, FLOAT_TYPE_FUEL_SUPPLY_LEVEL));

	#endif

	return sleep_time;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void build_supply_heat_map (void)
{

	int
		x,
		z;

	entity
		*en,
		*group,
		*sector;

	float
		supplies;

	if (!supply_heat_map)
	{
		supply_heat_bitmap = (unsigned char *) malloc_heap_mem (sizeof (unsigned char) * (NUM_MAP_X_SECTORS * NUM_MAP_Z_SECTORS * 3));

		supply_heat_map = (unsigned char *) malloc_heap_mem (sizeof (unsigned char) * (NUM_MAP_X_SECTORS * NUM_MAP_Z_SECTORS));
	}

	#if DEBUG_MODULE

		debug_log ("EN_SUPLY: building supply heat map");

	#endif

	memset (supply_heat_map, 0, sizeof (unsigned char) * (NUM_MAP_X_SECTORS * NUM_MAP_Z_SECTORS));

	memset (supply_heat_bitmap, 0, sizeof (unsigned char) * (NUM_MAP_X_SECTORS * NUM_MAP_Z_SECTORS * 3));
	
	// draw cargo

   for (x = 0; x < NUM_MAP_X_SECTORS; x ++)
   {

      for (z = 0; z < NUM_MAP_Z_SECTORS; z ++)
      {

			sector = get_local_raw_sector_entity (x, z);

			en = get_local_entity_first_child (sector, LIST_TYPE_SECTOR);

			while (en)
			{

				if (get_local_entity_type (en) == ENTITY_TYPE_CARGO)
				{
					set_supply_heat_map_cargo_spot (en, x, z, 1);
				}

				else if (get_local_entity_int_value (en, INT_TYPE_ALIVE))
				{
					if (get_local_entity_int_value (en, INT_TYPE_IDENTIFY_VEHICLE))
					{
						if (get_local_entity_int_value (en, INT_TYPE_GROUP_LEADER))
						{
	
							group = get_local_entity_parent (en, LIST_TYPE_MEMBER);
	
							// get combined value of supplies - (each in range 0-100) into range 0-127

							supplies = (get_local_entity_float_value (group, FLOAT_TYPE_FUEL_SUPPLY_LEVEL) +
											get_local_entity_float_value (group, FLOAT_TYPE_AMMO_SUPPLY_LEVEL)) *
											0.05;
							
							set_supply_heat_map_cargo_spot (en, x, z, (int) supplies);
						}
					}
				}

				en = get_local_entity_child_succ (en, LIST_TYPE_SECTOR);
			}
		}
	}

	// draw frontline groups
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_supply_heat_map_cargo_spot (entity *en, int x, int z, int value)
{

	rgb_colour
		col;

	int
		x_loop,
		z_loop,
		x_a,
		z_a,
		offset,
		str;

	float
		scale;
	
	offset = supply_heat_map[x + (NUM_MAP_X_SECTORS * z)];

	if (offset > 128)
	{
		offset = 3;
	}
	else if (offset > 64)
	{
		offset = 2;
	}
	else if (offset > 32)
	{
		offset = 1;
	}
	else
	{
		offset = 0;
	}
	
	offset = min (offset, 3);

	if (offset)
	{
		scale = 255 / (offset * 2);
	}
	else
	{
		scale = 0;
		
		offset = 0;
	}
	
	for (z_loop = max (z - offset, 0); z_loop < min (z + offset + 1, NUM_MAP_Z_SECTORS); z_loop ++)
	{
		z_a = abs (z_loop - (z));

		for (x_loop = max (x - offset, 0); x_loop < min (x + offset + 1, NUM_MAP_X_SECTORS); x_loop ++)
		{

			col.r = supply_heat_bitmap [(z_loop * NUM_MAP_X_SECTORS * 3) + (x_loop * 3)];
			col.g = supply_heat_bitmap [(z_loop * NUM_MAP_X_SECTORS * 3) + (x_loop * 3) + 1];
			col.b = supply_heat_bitmap [(z_loop * NUM_MAP_X_SECTORS * 3) + (x_loop * 3) + 2];

			x_a = abs (x_loop - (x));

			str = 255 - (scale * (x_a + z_a));

			if (str > supply_heat_map[(z_loop * NUM_MAP_X_SECTORS) + x_loop])
			{
				supply_heat_map[(z_loop * NUM_MAP_X_SECTORS) + x_loop] = bound (str, 0.0, 255.0);
			}
			
			if (get_local_entity_int_value (en, INT_TYPE_SIDE) == ENTITY_SIDE_BLUE_FORCE)
			{
				if (str > col.b)
				{
					col.b = bound ((str), 0.0, 255.0);
				}
			}
			else if (get_local_entity_int_value (en, INT_TYPE_SIDE) == ENTITY_SIDE_RED_FORCE)
			{
				if (str > col.r)
				{
					col.r = bound ((str), 0.0, 255.0);
				}
			}
			else
			{
				if (str > col.g)
				{
					col.g = bound ((str), 0.0, 255.0);
				}
			}

			supply_heat_bitmap [(z_loop * NUM_MAP_X_SECTORS * 3) + (x_loop * 3)] = col.r;
			supply_heat_bitmap [(z_loop * NUM_MAP_X_SECTORS * 3) + (x_loop * 3) + 1] = col.g;
			supply_heat_bitmap [(z_loop * NUM_MAP_X_SECTORS * 3) + (x_loop * 3) + 2] = col.b;

		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void output_supply_heat_map (void)
{
	static int
		limit = 10,
		numzeros = 4,
		count = 0;

	char
		filename[13],
		temp_string[7];
	
	int
		z;

	// initialise filename & output map

	sprintf (filename, "sm");

	sprintf (temp_string, "%d.psd", count);
	
	if (count >= limit)
	{
		limit *= 10;
		
		numzeros--;
	}

	for (z = 0; z < numzeros; z++)
	{
		strcat (filename, "0");
	}

	strcat (filename, temp_string);


	if (supply_heat_bitmap == NULL)
	{
		build_supply_heat_map ();
	}
				
	write_psd_rgb_file (filename, NUM_MAP_X_SECTORS, NUM_MAP_Z_SECTORS, NUM_MAP_X_SECTORS * 3, supply_heat_bitmap);

	#if DEBUG_MODULE

		debug_log ("EN_SUPLY: generating supply heat map psd no. %d", count);

	#endif

	count++;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	
