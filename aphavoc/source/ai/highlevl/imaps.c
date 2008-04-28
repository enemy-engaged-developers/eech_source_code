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

#include "imaps.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE   0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static unsigned char
	**imaps [NUM_IMAP_TYPES];

static float
	*imap_temp_array = NULL;

static int
	imaps_initialised = FALSE;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_imaps (void)
{
	int
		loop,
		side;
		
	ASSERT (get_session_entity ());

	for (loop = 0; loop < NUM_IMAP_TYPES; loop ++)
	{
		imaps [loop] = malloc_heap_mem (sizeof (unsigned char *) * NUM_ENTITY_SIDES);

		for (side = 0; side < NUM_ENTITY_SIDES; side ++)
		{
			imaps [loop][side] = malloc_heap_mem (sizeof (unsigned char) * NUM_MAP_Z_SECTORS * NUM_MAP_X_SECTORS);
		}
	}

	// temporary array

	imap_temp_array = malloc_heap_mem (sizeof (float) * NUM_MAP_X_SECTORS * NUM_MAP_Z_SECTORS);

	imaps_initialised = TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_imaps (void)
{
	int
		loop,
		side;
		
	for (loop = 0; loop < NUM_IMAP_TYPES; loop ++)
	{
		ASSERT (imaps [loop]);

		for (side = 0; side < NUM_ENTITY_SIDES; side ++)
		{
			free_mem (imaps [loop][side]);
		}

		free_mem (imaps [loop]);

		imaps [loop] = NULL;
	}	

	// temporary array

	free_mem (imap_temp_array);

	imap_temp_array = NULL;

	imaps_initialised = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_imap_value (imap_types type, entity_sides side, int x, int z)
{
	float
		f;

	unsigned char
		v;

	v = imaps [type][side][(z * NUM_MAP_X_SECTORS) + x];

	f = (float)v;

	return (f / 255.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned char get_imap_char_value (imap_types type, entity_sides side, int x, int z)
{
	unsigned char
		v;

	v = imaps [type][side][(z * NUM_MAP_X_SECTORS) + x];

	return v;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void normalise_inlfuence_map (float *original, unsigned char *output, int xsize, int zsize)
{
	float
		val,
		min_val,
		max_val;

	int
		x,
		z;

	ASSERT (original);

	ASSERT (output);

	//
	// Find largest value
	//

	min_val = FLT_MAX;

	max_val = 0.0;

	for (z = 0; z < zsize; z++)
	{
		for (x = 0; x < xsize; x++)
		{
			min_val = min (min_val, original [(z * xsize) + x]);

			max_val = max (max_val, original [(z * xsize) + x]);
		}
	}

	if (max_val == min_val)
	{
		return;
	}

	//
	// Normalise
	//

	for (z = 0; z < zsize; z++)
	{
		for (x = 0; x < xsize; x++)
		{
			val = 255.0 * ((original [(z * xsize) + x] - min_val) / (max_val - min_val));

			ASSERT ((val >= 0.0) && (val < 256.0));

			output [(z * xsize) + x] = (unsigned char)val;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef DEBUG
/*
static void invert_inlfuence_map (unsigned char *output, int xsize, int zsize)
{
	int
		z,
		z2;

	unsigned char
		*temp;

	ASSERT (output);

	temp = malloc_fast_mem (xsize);

	//
	// Invert
	//

	for (z = 0; z < zsize; z++)
	{
		z2 = (zsize - z) - 1;

		if (z != z2)
		{
			memcpy (temp, &output [z * xsize], xsize);
		
			memcpy (&output [z * xsize], &output [z2 * xsize], xsize);
		
			memcpy (&output [z2 * xsize], temp, xsize);
		}
	}
}
*/
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SECTOR SIDES
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float update_sector_side (int sx, int sz, entity_sides side, int in_use, float scale)
{
	entity
		*en;

	sector
		*raw;
		
	en = get_local_raw_sector_entity (sx, sz);

	ASSERT (en);

	raw = get_local_entity_data (en);

	if (scale > 0.0)
	{
		if (in_use)
		{
			raw->sector_side [side] += scale;
		}
		else
		{
			ASSERT (raw->sector_side [side] > 0.0);
	
			raw->sector_side [side] -= scale;
		}
	
		#if DEBUG_MODULE
	
		debug_log ("IMAPS: %d, %d (%s) setting side value to %f", sx, sz, entity_side_names [side], raw->sector_side [side]);
	
		#endif
	}

	return raw->sector_side [side];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_imap_sector_side (entity *en, int in_use)
{
	int
		x,
		z,
		sx,
		sz,
		side;

	vec3d
		*pos;

	float
		max_val,
		d2,
		dx,
		dz,
		scale,
		constant;

	ASSERT (en);

	max_val = get_local_entity_float_value (en, FLOAT_TYPE_SECTOR_SIDE_MAX_VALUE);

	if (max_val > 0.0)
	{
		constant = 0.3;

		side = get_local_entity_int_value (en, INT_TYPE_SIDE);

		pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);
	
		get_x_sector (sx, pos->x);
		get_z_sector (sz, pos->z);
	
		#if DEBUG_MODULE

		if (get_local_entity_type (en) == ENTITY_TYPE_KEYSITE)
		{
			debug_log ("IMAPS: Updating sector side for %s at %d, %d (IN USE : %d)", get_local_entity_string (en, STRING_TYPE_KEYSITE_NAME), sx, sz, in_use);
		}
		else
		{
			debug_log ("IMAPS: Updating sector side for %s at %d, %d (IN USE : %d)", get_local_entity_string (en, STRING_TYPE_FULL_NAME), sx, sz, in_use);
		}

		#endif

		for (z = MIN_MAP_Z_SECTOR; z <= MAX_MAP_Z_SECTOR ; z ++)
		{
			dz = (constant * fabs (z - sz)) + 1.0;

			for (x = MIN_MAP_X_SECTOR; x <= MAX_MAP_X_SECTOR ; x ++)
			{
				dx = (constant * fabs (x - sx)) + 1.0;

				d2 = ((dx * dx) + (dz * dz));

				scale = max_val / d2;

				update_sector_side (x, z, side, in_use, scale);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// KEYSITE IMPORTANCE
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float update_sector_importance_level (int sx, int sz, entity_sides side, int in_use, float scale)
{
	entity
		*en;

	sector
		*raw;
		
	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	en = get_local_raw_sector_entity (sx, sz);

	ASSERT (en);

	raw = get_local_entity_data (en);

	if (scale > 0.0)
	{
		if (in_use)
		{
			raw->importance_level [side] += scale;
		}
		else
		{
			ASSERT (raw->importance_level [side] > 0.0);
	
			raw->importance_level [side] -= scale;
		}
	
		#if DEBUG_MODULE
	
		debug_log ("IMAPS: %d, %d (%s) setting importance level to %f", sx, sz, entity_side_names [side], raw->importance_level [side]);
	
		#endif
	}

	return raw->importance_level [side];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_imap_importance_level (entity *en, int in_use)
{
	int
		x,
		z,
		sx,
		sz,
		side,
		sub_type,
		sector_radius,
		sr2;

	vec3d
		*pos;

	float
		scale,
		radius,
		importance;

	ASSERT (en);

	ASSERT (get_local_entity_type (en) == ENTITY_TYPE_KEYSITE);

	importance = get_local_entity_float_value (en, FLOAT_TYPE_KEYSITE_IMPORTANCE);

	if (importance > 0.0)
	{
		side = get_local_entity_int_value (en, INT_TYPE_SIDE);

		sub_type = get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);

		radius = keysite_database [sub_type].importance_radius / SECTOR_SIDE_LENGTH;

		convert_float_to_int (radius, &sector_radius);

		sector_radius = max (sector_radius, 1);

		sr2 = sector_radius * sector_radius;

		pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);
	
		get_x_sector (sx, pos->x);
		get_z_sector (sz, pos->z);
	
		#if DEBUG_MODULE

		debug_log ("IMAPS: Updating sector importance for %s at %d, %d (IN USE : %d)", get_local_entity_string (en, STRING_TYPE_KEYSITE_NAME), sx, sz, in_use);

		#endif

		for (z = -sector_radius; z <= sector_radius; z ++)
		{
			if (((sz + z) < MIN_MAP_Z_SECTOR) || ((sz + z) > MAX_MAP_Z_SECTOR))
			{
				continue;
			}

			for (x = -sector_radius; x <= sector_radius; x ++)
			{
				if (((sx + x) < MIN_MAP_X_SECTOR) || ((sx + x) > MAX_MAP_X_SECTOR))
				{
					continue;
				}

				scale = (float)((x * x) + (z * z)) / (float)sr2;

				if (scale < 1.0)
				{
					scale = 1.0 - scale;

					update_sector_importance_level (sx + x, sz + z, side, in_use, importance * scale);
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void normalise_importance_imaps (void)
{
	int
		sx,
		sz,
		side;

	entity
		*sec;

	sector
		*raw;

	float
		val;

	for (side = 0; side < NUM_ENTITY_SIDES; side ++)
	{
		for (sz = 0; sz < NUM_MAP_Z_SECTORS; sz++)
		{
			for (sx = 0; sx < NUM_MAP_X_SECTORS; sx++)
			{
				sec = get_local_raw_sector_entity (sx, sz);

				ASSERT (sec);

				raw = get_local_entity_data (sec);

				val = raw->importance_level [side];

				imap_temp_array [(sz * NUM_MAP_X_SECTORS) + sx] = val;
			}
		}

		normalise_inlfuence_map (imap_temp_array, imaps [IMAP_IMPORTANCE][side], NUM_MAP_X_SECTORS, NUM_MAP_Z_SECTORS);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DISTANCE TO FRIENDLY BASE 
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float update_sector_distance_to_friendly_base (int sx, int sz, entity_sides side, float scale)
{
	entity
		*en;

	sector
		*raw;
		
	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	en = get_local_raw_sector_entity (sx, sz);

	ASSERT (en);

	raw = get_local_entity_data (en);

	if (scale > 0.0)
	{
		raw->distance_to_friendly_base [side] = max (raw->distance_to_friendly_base [side], scale);
	
		#if DEBUG_MODULE
	
		debug_log ("IMAPS: %d, %d (%s) setting distance_to_friendly_base to %f", sx, sz, entity_side_names [side], raw->distance_to_friendly_base [side]);
	
		#endif
	}

	return raw->distance_to_friendly_base [side];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_keysite_distance_to_friendly_base (entity *en, entity_sides side)
{
	int
		x,
		z,
		sx,
		sz,
		sub_type,
		sector_radius,
		sr2;

	vec3d
		*pos;

	float
		scale,
		radius;

	ASSERT (en);

	ASSERT (get_local_entity_type (en) == ENTITY_TYPE_KEYSITE);

	sub_type = get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);

	radius = keysite_database [sub_type].air_coverage_radius / SECTOR_SIDE_LENGTH;

	if (radius > 0.0)
	{
		convert_float_to_int (radius, &sector_radius);

		sector_radius = max (sector_radius, 1);

		sr2 = sector_radius * sector_radius;

		pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);
	
		get_x_sector (sx, pos->x);
		get_z_sector (sz, pos->z);
	
		#if DEBUG_MODULE

		debug_log ("IMAPS: Updating sector base distance for %s at %d, %d (IN USE : %d)", get_local_entity_string (en, STRING_TYPE_KEYSITE_NAME), sx, sz, in_use);

		#endif

		for (z = -sector_radius; z <= sector_radius; z ++)
		{
			if (((sz + z) < MIN_MAP_Z_SECTOR) || ((sz + z) > MAX_MAP_Z_SECTOR))
			{
				continue;
			}

			for (x = -sector_radius; x <= sector_radius; x ++)
			{
				if (((sx + x) < MIN_MAP_X_SECTOR) || ((sx + x) > MAX_MAP_X_SECTOR))
				{
					continue;
				}

				scale = (float)((x * x) + (z * z)) / (float)sr2;

				if (scale < 1.0)
				{
					scale = 1.0 - scale;

					update_sector_distance_to_friendly_base (sx + x, sz + z, side, scale);
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_imap_distance_to_friendly_base (entity_sides side)
{
	entity
		*sec,
		*force,
		*keysite;

	int
		x,
		z;

	sector
		*raw;

	for (z = MIN_MAP_Z_SECTOR; z < MAX_MAP_Z_SECTOR; z ++)
	{
		for (x = MIN_MAP_X_SECTOR; x < MAX_MAP_X_SECTOR; x ++)
		{
			sec = get_local_raw_sector_entity (x, z);

			ASSERT (sec);

			raw = get_local_entity_data (sec);

			raw->distance_to_friendly_base [side] = 0.0;
		}
	}

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);
	
	force = get_local_force_entity (side);

	ASSERT (force);

	keysite = get_local_entity_first_child (force, LIST_TYPE_KEYSITE_FORCE);

	while (keysite)
	{
		if (get_local_entity_int_value (keysite, INT_TYPE_IN_USE))
		{
			if (get_local_entity_int_value (keysite, INT_TYPE_ALIVE))
			{
				update_keysite_distance_to_friendly_base (keysite, side);
			}
		}

		keysite = get_local_entity_child_succ (keysite, LIST_TYPE_KEYSITE_FORCE);
	}

	if (imaps_initialised)
	{
		normalise_base_distance_imaps ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void normalise_base_distance_imaps (void)
{
	int
		sx,
		sz,
		side;

	entity
		*sec;

	sector
		*raw;

	float
		val;

	for (side = 0; side < NUM_ENTITY_SIDES; side ++)
	{
		for (sz = 0; sz < NUM_MAP_Z_SECTORS; sz++)
		{
			for (sx = 0; sx < NUM_MAP_X_SECTORS; sx++)
			{
				sec = get_local_raw_sector_entity (sx, sz);

				ASSERT (sec);

				raw = get_local_entity_data (sec);

				val = raw->distance_to_friendly_base [side];

				imap_temp_array [(sz * NUM_MAP_X_SECTORS) + sx] = val;
			}
		}

		normalise_inlfuence_map (imap_temp_array, imaps [IMAP_BASE_DISTANCE][side], NUM_MAP_X_SECTORS, NUM_MAP_Z_SECTORS);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SURFACE TO AIR DEFENCE LEVELS
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float update_sector_surface_to_air_defence_level (int sx, int sz, entity_sides side, int in_use, float scale)
{
	entity
		*en;

	sector
		*raw;
		
	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	en = get_local_raw_sector_entity (sx, sz);

	ASSERT (en);

	raw = get_local_entity_data (en);

	if (scale > 0.0)
	{
		if (in_use)
		{
			raw->surface_to_air_defence_level [side] += scale;
		}
		else
		{
			ASSERT (raw->surface_to_air_defence_level [side] > 0.0);

			raw->surface_to_air_defence_level [side] -= scale;
		}
	
		#if DEBUG_MODULE
	
		debug_log ("IMAPS: %d, %d (%s) setting S-A level to %f", sx, sz, entity_side_names [side], raw->surface_to_air_defence_level [side]);
	
		#endif
	}

	return raw->surface_to_air_defence_level [side];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_imap_surface_to_air_defence_level (entity *en, entity *sector, int in_use)
{
	int
		x,
		z,
		sx,
		sz,
		side,
		sector_radius,
		sr2;

	float
		scale,
		radius,
		value;

	ASSERT (en);

	ASSERT (sector);

	value = get_local_entity_float_value (en, FLOAT_TYPE_POTENTIAL_SURFACE_TO_AIR_THREAT);

	if (value > 0.0)
	{
		side = get_local_entity_int_value (en, INT_TYPE_SIDE);

		radius = get_local_entity_float_value (en, FLOAT_TYPE_AIR_SCAN_RANGE) * 10.0 / SECTOR_SIDE_LENGTH;

		convert_float_to_int (radius, &sector_radius);

		sector_radius = max (sector_radius, 1);

		sr2 = sector_radius * sector_radius;

		sx = get_local_entity_int_value (sector, INT_TYPE_X_SECTOR);
		sz = get_local_entity_int_value (sector, INT_TYPE_Z_SECTOR);
	
		#if DEBUG_MODULE

		debug_log ("IMAPS: Updating sector S-A for %s at %d, %d (IN USE %d)", get_local_entity_string (en, STRING_TYPE_SHORT_DISPLAY_NAME), sx, sz, in_use);

		#endif

		for (z = -sector_radius; z <= sector_radius; z ++)
		{
			if (((sz + z) < MIN_MAP_Z_SECTOR) || ((sz + z) > MAX_MAP_Z_SECTOR))
			{
				continue;
			}

			for (x = -sector_radius; x <= sector_radius; x ++)
			{
				if (((sx + x) < MIN_MAP_X_SECTOR) || ((sx + x) > MAX_MAP_X_SECTOR))
				{
					continue;
				}

				scale = (float)((x * x) + (z * z)) / (float)sr2;

				if (scale < 1.0)
				{
					scale = 1.0 - scale;

					update_sector_surface_to_air_defence_level (sx + x, sz + z, side, in_use, value * scale);
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void normalise_air_defence_imaps (void)
{
	int
		sx,
		sz,
		side;

	entity
		*sec;

	sector
		*raw;

	float
		val;

	for (side = 0; side < NUM_ENTITY_SIDES; side ++)
	{
		for (sz = 0; sz < NUM_MAP_Z_SECTORS; sz++)
		{
			for (sx = 0; sx < NUM_MAP_X_SECTORS; sx++)
			{
				sec = get_local_raw_sector_entity (sx, sz);

				ASSERT (sec);

				raw = get_local_entity_data (sec);

				val = raw->surface_to_air_defence_level [side];

				imap_temp_array [(sz * NUM_MAP_X_SECTORS) + sx] = val;
			}
		}

		normalise_inlfuence_map (imap_temp_array, imaps [IMAP_AIR_DEFENCE][side], NUM_MAP_X_SECTORS, NUM_MAP_Z_SECTORS);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SURFACE TO SURFACE DEFENCE LEVELS
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float update_sector_surface_to_surface_defence_level (int sx, int sz, entity_sides side, int in_use, float scale)
{
	entity
		*en;

	sector
		*raw;
		
	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	en = get_local_raw_sector_entity (sx, sz);

	ASSERT (en);

	raw = get_local_entity_data (en);

	if (scale > 0.0)
	{
		if (in_use)
		{
			raw->surface_to_surface_defence_level [side] += scale;
		}
		else
		{
			ASSERT (raw->surface_to_surface_defence_level [side] > 0.0);

			raw->surface_to_surface_defence_level [side] -= scale;
		}
	
		#if DEBUG_MODULE
	
		debug_log ("IMAPS: %d, %d (%s) setting S-S level to %f", sx, sz, entity_side_names [side], raw->surface_to_surface_defence_level [side]);
	
		#endif
	}

	return raw->surface_to_surface_defence_level [side];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_imap_surface_to_surface_defence_level (entity *en, entity *sector, int in_use)
{
	int
		x,
		z,
		sx,
		sz,
		side,
		sector_radius,
		sr2;

	float
		scale,
		radius,
		value;

	ASSERT (en);

	ASSERT (sector);

	value = get_local_entity_float_value (en, FLOAT_TYPE_POTENTIAL_SURFACE_TO_SURFACE_THREAT);

	if (value > 0.0)
	{
		side = get_local_entity_int_value (en, INT_TYPE_SIDE);

		radius = get_local_entity_float_value (en, FLOAT_TYPE_SURFACE_SCAN_RANGE) * 10.0 / SECTOR_SIDE_LENGTH;

		convert_float_to_int (radius, &sector_radius);

		sector_radius = max (sector_radius, 1);

		sr2 = sector_radius * sector_radius;

		sx = get_local_entity_int_value (sector, INT_TYPE_X_SECTOR);
		sz = get_local_entity_int_value (sector, INT_TYPE_Z_SECTOR);
	
		#if DEBUG_MODULE

		debug_log ("IMAPS: Updating sector S-S for %s at %d, %d (IN USE %d)", get_local_entity_string (en, STRING_TYPE_SHORT_DISPLAY_NAME), sx, sz, in_use);

		#endif

		for (z = -sector_radius; z <= sector_radius; z ++)
		{
			if (((sz + z) < MIN_MAP_Z_SECTOR) || ((sz + z) > MAX_MAP_Z_SECTOR))
			{
				continue;
			}

			for (x = -sector_radius; x <= sector_radius; x ++)
			{
				if (((sx + x) < MIN_MAP_X_SECTOR) || ((sx + x) > MAX_MAP_X_SECTOR))
				{
					continue;
				}

				scale = (float)((x * x) + (z * z)) / (float)sr2;

				if (scale < 1.0)
				{
					scale = 1.0 - scale;

					update_sector_surface_to_surface_defence_level (sx + x, sz + z, side, in_use, value * scale);
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void normalise_surface_defence_imaps (void)
{
	int
		sx,
		sz,
		side;

	entity
		*sec;

	sector
		*raw;

	float
		val;

	for (side = 0; side < NUM_ENTITY_SIDES; side ++)
	{
		for (sz = 0; sz < NUM_MAP_Z_SECTORS; sz++)
		{
			for (sx = 0; sx < NUM_MAP_X_SECTORS; sx++)
			{
				sec = get_local_raw_sector_entity (sx, sz);

				ASSERT (sec);

				raw = get_local_entity_data (sec);

				val = raw->surface_to_surface_defence_level [side];

				imap_temp_array [(sz * NUM_MAP_X_SECTORS) + sx] = val;
			}
		}

		normalise_inlfuence_map (imap_temp_array, imaps [IMAP_SURFACE_DEFENCE][side], NUM_MAP_X_SECTORS, NUM_MAP_Z_SECTORS);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DEBUG OUTPUT FUNCTIONS
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void output_sector_side_influence_map (unsigned char *filename)
{
	#ifdef DEBUG

	int
		z,
		sx,
		sz,
		temp;

	entity
		*sec;

	sector
		*raw;

	unsigned char
		*output;

	rgb_colour
		col;

	float
		val,
		ratio,
		total;

	ASSERT (filename);

	output = safe_malloc (NUM_MAP_X_SECTORS * NUM_MAP_Z_SECTORS * 3);

	memset (output, 0, (NUM_MAP_X_SECTORS * NUM_MAP_Z_SECTORS * 3));
				
	for (sz = 0; sz < NUM_MAP_Z_SECTORS; sz++)
	{
		for (sx = 0; sx < NUM_MAP_X_SECTORS; sx++)
		{
			sec = get_local_raw_sector_entity (sx, sz);

			ASSERT (sec);

			raw = get_local_entity_data (sec);

			total = raw->sector_side [ENTITY_SIDE_BLUE_FORCE] + raw->sector_side [ENTITY_SIDE_RED_FORCE];

			ASSERT (total > 0.0);

			ratio = raw->sector_side [ENTITY_SIDE_BLUE_FORCE] / total;

			ratio = bound (ratio, 0.0, 1.0);

			// red
			val = 255.0 * (1.0 - ratio);
			convert_float_to_int (val, &temp);
			col.r = temp;

			// green
			col.g = 0;

			// blue
			val = 255.0 * ratio;
			convert_float_to_int (val, &temp);
			col.b = temp;

			z = (NUM_MAP_Z_SECTORS - sz) - 1;

			output [(z * NUM_MAP_X_SECTORS * 3) + (sx * 3)] = col.r;
			output [(z * NUM_MAP_X_SECTORS * 3) + (sx * 3) + 1] = col.g;
			output [(z * NUM_MAP_X_SECTORS * 3) + (sx * 3) + 2] = col.b;
		}
	}

	write_psd_rgb_file (filename, NUM_MAP_X_SECTORS, NUM_MAP_Z_SECTORS, NUM_MAP_X_SECTORS * 3, output);

	safe_free (output);

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void output_sector_side_normalised_influence_map (unsigned char *filename)
{
	#ifdef DEBUG

	int
		z,
		sx,
		sz;

	entity
		*sec;

	unsigned char
		*output;

	rgb_colour
		*col;

	ASSERT (filename);

	output = safe_malloc (NUM_MAP_X_SECTORS * NUM_MAP_Z_SECTORS * 3);

	memset (output, 0, (NUM_MAP_X_SECTORS * NUM_MAP_Z_SECTORS * 3));
				
	for (sz = 0; sz < NUM_MAP_Z_SECTORS; sz++)
	{
		for (sx = 0; sx < NUM_MAP_X_SECTORS; sx++)
		{
			sec = get_local_raw_sector_entity (sx, sz);

			ASSERT (sec);

			switch (get_local_entity_int_value (sec, INT_TYPE_SECTOR_SIDE))
			{
				case ENTITY_SIDE_BLUE_FORCE:
				{
					col = &sys_col_blue;

					break;
				}
				case ENTITY_SIDE_RED_FORCE:
				{
					col = &sys_col_red;

					break;
				}
				default:
				{
					col = &sys_col_black;

					break;
				}
			}

			z = (NUM_MAP_Z_SECTORS - sz) - 1;

			output [(z * NUM_MAP_X_SECTORS * 3) + (sx * 3)] = col->r;
			output [(z * NUM_MAP_X_SECTORS * 3) + (sx * 3) + 1] = col->g;
			output [(z * NUM_MAP_X_SECTORS * 3) + (sx * 3) + 2] = col->b;
		}
	}

	write_psd_rgb_file (filename, NUM_MAP_X_SECTORS, NUM_MAP_Z_SECTORS, NUM_MAP_X_SECTORS * 3, output);

	safe_free (output);

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void output_sector_fog_of_war_influence_map (entity_sides side, unsigned char *filename)
{
	#ifdef DEBUG

	int
		z,
		sx,
		sz,
		fog;

	entity
		*sec;

	unsigned char
		*output;

	float
		val,
		max_fog;

	ASSERT (filename);

	if (get_comms_model () != COMMS_MODEL_SERVER)
	{
		return;
	}

	max_fog = get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_FOG_OF_WAR_MAXIMUM_VALUE);

	output = safe_malloc (NUM_MAP_X_SECTORS * NUM_MAP_Z_SECTORS);

	memset (output, 0, (NUM_MAP_X_SECTORS * NUM_MAP_Z_SECTORS));
				
	for (sz = 0; sz < NUM_MAP_Z_SECTORS; sz++)
	{
		for (sx = 0; sx < NUM_MAP_X_SECTORS; sx++)
		{
			sec = get_local_raw_sector_entity (sx, sz);

			ASSERT (sec);

			val = (255.0 * get_sector_fog_of_war_value (sec, side)) / max_fog;

			convert_float_to_int (val, &fog);

			z = (NUM_MAP_Z_SECTORS - sz) - 1;

			output [(z * NUM_MAP_X_SECTORS) + sx] = fog;
		}
	}

	write_psd_greyscale (filename, NUM_MAP_X_SECTORS, NUM_MAP_Z_SECTORS, NUM_MAP_X_SECTORS, output);

	safe_free (output);

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void output_sector_surface_to_air_influence_map (entity_sides side, unsigned char *filename)
{
	#ifdef DEBUG

	ASSERT (filename);

	if (get_comms_model () != COMMS_MODEL_SERVER)
	{
		return;
	}

	ASSERT (imaps [IMAP_AIR_DEFENCE]);

	ASSERT (imaps [IMAP_AIR_DEFENCE][side]);

//	invert_inlfuence_map (imaps [IMAP_AIR_DEFENCE][side], NUM_MAP_X_SECTORS, NUM_MAP_Z_SECTORS);

	write_psd_greyscale (filename, NUM_MAP_X_SECTORS, NUM_MAP_Z_SECTORS, NUM_MAP_X_SECTORS, imaps [IMAP_AIR_DEFENCE][side]);

//	invert_inlfuence_map (imaps [IMAP_AIR_DEFENCE][side], NUM_MAP_X_SECTORS, NUM_MAP_Z_SECTORS);

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void output_sector_surface_to_surface_influence_map (entity_sides side, unsigned char *filename)
{
	#ifdef DEBUG

	ASSERT (filename);

	if (get_comms_model () != COMMS_MODEL_SERVER)
	{
		return;
	}

	ASSERT (imaps [IMAP_SURFACE_DEFENCE]);

	ASSERT (imaps [IMAP_SURFACE_DEFENCE][side]);

//	invert_inlfuence_map (imaps [IMAP_SURFACE_DEFENCE][side], NUM_MAP_X_SECTORS, NUM_MAP_Z_SECTORS);

	write_psd_greyscale (filename, NUM_MAP_X_SECTORS, NUM_MAP_Z_SECTORS, NUM_MAP_X_SECTORS, imaps [IMAP_SURFACE_DEFENCE][side]);

//	invert_inlfuence_map (imaps [IMAP_SURFACE_DEFENCE][side], NUM_MAP_X_SECTORS, NUM_MAP_Z_SECTORS);

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void output_sector_importance_influence_map (entity_sides side, unsigned char *filename)
{
	#ifdef DEBUG

	ASSERT (filename);

	if (get_comms_model () != COMMS_MODEL_SERVER)
	{
		return;
	}

	ASSERT (imaps [IMAP_IMPORTANCE]);

	ASSERT (imaps [IMAP_IMPORTANCE][side]);

//	invert_inlfuence_map (imaps [IMAP_IMPORTANCE][side], NUM_MAP_X_SECTORS, NUM_MAP_Z_SECTORS);

	write_psd_greyscale (filename, NUM_MAP_X_SECTORS, NUM_MAP_Z_SECTORS, NUM_MAP_X_SECTORS, imaps [IMAP_IMPORTANCE][side]);

//	invert_inlfuence_map (imaps [IMAP_IMPORTANCE][side], NUM_MAP_X_SECTORS, NUM_MAP_Z_SECTORS);

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void output_sector_distance_to_friendly_base_influence_map (entity_sides side, unsigned char *filename)
{
	#ifdef DEBUG

	ASSERT (filename);

	if (get_comms_model () != COMMS_MODEL_SERVER)
	{
		return;
	}

	ASSERT (imaps [IMAP_BASE_DISTANCE]);

	ASSERT (imaps [IMAP_BASE_DISTANCE][side]);

//	invert_inlfuence_map (imaps [IMAP_BASE_DISTANCE][side], NUM_MAP_X_SECTORS, NUM_MAP_Z_SECTORS);

	write_psd_greyscale (filename, NUM_MAP_X_SECTORS, NUM_MAP_Z_SECTORS, NUM_MAP_X_SECTORS, imaps [IMAP_BASE_DISTANCE][side]);

//	invert_inlfuence_map (imaps [IMAP_BASE_DISTANCE][side], NUM_MAP_X_SECTORS, NUM_MAP_Z_SECTORS);

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void output_all_influence_maps (void)
{
	debug_colour_log (DEBUG_COLOUR_RED, "OUTPUT INFLUENCE MAPS");

	output_sector_side_influence_map ("IM_SIDE.PSD");

	output_sector_side_normalised_influence_map ("IM_SIDE2.PSD");

	output_sector_fog_of_war_influence_map (ENTITY_SIDE_RED_FORCE, "IM_FOGR.PSD");
	output_sector_fog_of_war_influence_map (ENTITY_SIDE_BLUE_FORCE, "IM_FOGB.PSD");

	output_sector_surface_to_air_influence_map (ENTITY_SIDE_RED_FORCE, "IM_AIRR.PSD");
	output_sector_surface_to_air_influence_map (ENTITY_SIDE_BLUE_FORCE, "IM_AIRB.PSD");

	output_sector_surface_to_surface_influence_map (ENTITY_SIDE_RED_FORCE, "IM_SURFR.PSD");
	output_sector_surface_to_surface_influence_map (ENTITY_SIDE_BLUE_FORCE, "IM_SURFB.PSD");

	output_sector_importance_influence_map (ENTITY_SIDE_RED_FORCE, "IM_IMPR.PSD");
	output_sector_importance_influence_map (ENTITY_SIDE_BLUE_FORCE, "IM_IMPB.PSD");

	output_sector_distance_to_friendly_base_influence_map (ENTITY_SIDE_RED_FORCE, "IM_BASER.PSD");
	output_sector_distance_to_friendly_base_influence_map (ENTITY_SIDE_BLUE_FORCE, "IM_BASEB.PSD");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


