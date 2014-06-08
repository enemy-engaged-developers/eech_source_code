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
//
// The memory block system uses ready allocated arrays of fixed size memory
// blocks to provide fast memory allocation and to prevent memory fragmentation.
//
//
//
// Example of use:
//
//	// START OF APPLICATION
//
// initialise_memory_block_system ();
//
// // create memory blocks required (optimised for application)
//
// create_memory_blocks ( 64, 1000);
// create_memory_blocks (128, 2000);
// create_memory_blocks (256, 2000);
// create_memory_blocks (512, 1000);
//
// // DURING APPLICATION
//
// ptr1 = malloc_fast_mem (1000);	// speed optimised (uses memory block)
// ptr2 = malloc_heap_mem (500);		// space optimised (uses system heap)
//
// free_mem (ptr1);
// free_mem (ptr2);
//
//	// END OF APPLICATION
//
// #ifdef DEBUG
//
// // use statistics to optimise sysytem
//
// display_memory_block_system_statistics ();
//
// #endif
//
// deinitialise_memory_block_system ();
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "system.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum MEM_TYPES
{
	MEM_TYPE_UNKNOWN,
	MEM_TYPE_FAST,  	// speed optimised (uses memory block)
	MEM_TYPE_HEAP,	  	// space optimised (uses system heap)
	NUM_MEM_TYPES
};

typedef enum MEM_TYPES mem_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// forward declarations
//

typedef struct MEMBLOCK memblock;

typedef struct MEMARRAY memarray;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// memory block header
//

struct MEMBLOCK
{
	#if MEMBLOCK_INTEGRITY_TEST

	int
		integrity_test;

	#endif

	int
		size;

	memarray
		*array;

	memblock
		*succ,
		*pred;

	#if DEBUG_MEMBLOCK_MODULE

	char
		*create_location;

	#endif
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define INTEGRITY_TEST_VALUE	(1234567890)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// memory block array data
//

struct MEMARRAY
{
	//
	// MEMORY MANAGEMENT
	//

	mem_types
		type;

	int
		block_size,
		num_blocks;

	memarray
		*succ,
		*pred;

	memblock
		*base,
		*first_free_block,
		*first_used_block;

	//
	// STATISTICS
	//

	#if DEBUG_MEMBLOCK_MODULE

	int
		blocks_used_total,
		blocks_used_count,
		blocks_used_peak_count,
		total_requested_memory_size,
		total_allocated_memory_size;

	#endif
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static memblock *get_memory_block (memarray *array, int size);

#if DEBUG_MEMBLOCK_MODULE

static void initialise_array_statistics (memarray *array);

static void update_array_statistics_malloc (memarray *array, memblock *block);

static void update_array_statistics_free (memarray *array, memblock *block);

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// memory block system installed status
//

static int
	memory_block_system_installed = FALSE;

//
// memory block array linked list root
//

static memarray
	*memory_block_arrays = NULL;

//
// direct access to heap memory block array
//

static memarray
	*heap_array = NULL;

//
// statistics
//

#if DEBUG_MEMBLOCK_MODULE

static int
	total_block_memory_allocated = 0;

#define MAX_REQUESTED_MEMORY_SIZE (1000)

static int
	requested_memory_size_total[MAX_REQUESTED_MEMORY_SIZE],
	requested_memory_size_count[MAX_REQUESTED_MEMORY_SIZE],
	requested_memory_size_peak_count[MAX_REQUESTED_MEMORY_SIZE];

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_memory_block_system (void)
{
	memarray
		*array;

	//
	// initialise heap memory array
	//

	array = (memarray*) safe_malloc (sizeof (memarray));

	array->type = MEM_TYPE_HEAP;

	//
	// block_size = INT_MAX for search end stop
	//

	array->block_size = INT_MAX;
	array->num_blocks = 0;

	array->succ = NULL;
	array->pred = NULL;

	array->base = NULL;
	array->first_free_block = NULL;
	array->first_used_block = NULL;

	#if DEBUG_MEMBLOCK_MODULE

	initialise_array_statistics (array);

	#endif

	memory_block_arrays = array;

	heap_array = array;

	memory_block_system_installed = TRUE;

	#if DEBUG_MEMBLOCK_MODULE

	total_block_memory_allocated = 0;

	memset (requested_memory_size_total, 0, sizeof (requested_memory_size_total));

	memset (requested_memory_size_count, 0, sizeof (requested_memory_size_count));

	memset (requested_memory_size_peak_count, 0, sizeof (requested_memory_size_peak_count));

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_memory_block_system (void)
{
	memarray
		*array,
		*array_succ;

	memblock
		*block,
		*block_succ;

	array = memory_block_arrays;

	while (array)
	{
		array_succ = array->succ;

		if (array->first_used_block)
		{
			debug_log ("WARNING! Memory block array still in use (block_size = %d)", array->block_size);

			#if DEBUG_MEMBLOCK_MODULE
			{
				block = array->first_used_block;

				while (block)
				{
					debug_log ("->BLOCK: %s", block->create_location);

					block = block->succ;
				}
			}
			#endif
		}

		if (array->type == MEM_TYPE_FAST)
		{
			safe_free (array->base);
		}
		else
		{
			block = array->first_used_block;

			while (block)
			{
				block_succ = block->succ;

				safe_free (block);

				block = block_succ;
			}
		}

 		safe_free (array);

		array = array_succ;
	}

	memory_block_arrays = NULL;

	heap_array = NULL;

	memory_block_system_installed = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_memory_block_configuration (memory_block_configuration *memory_block_config, int num_entries)
{
	int
		i,
		j;

	ASSERT (memory_block_config);

	ASSERT (num_entries > 0);

	for (i = 0; i < num_entries; i++)
	{
		//
		// combine memory blocks of the same size
		//

		if (memory_block_config[i].block_size > 0)
		{
			if (i < (num_entries - 1))
			{
				for (j = i + 1; j < num_entries; j++)
				{
					if (memory_block_config[i].block_size == memory_block_config[j].block_size)
					{
						memory_block_config[i].number_of_blocks += memory_block_config[j].number_of_blocks;

						memory_block_config[j].block_size = 0;
						memory_block_config[j].number_of_blocks = 0;
					}
				}
			}

			create_memory_blocks (memory_block_config[i].block_size, memory_block_config[i].number_of_blocks);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_memory_blocks (int block_size, int num_blocks)
{
	int
		hdr_and_block_size,
		array_size,
		i;

	memblock
		*block;

	memarray
		*new_array,
		*array;

	ASSERT (block_size > 0);

	ASSERT (block_size < (1 << 20));

	ASSERT (num_blocks > 0);

	#if DEBUG_MEMBLOCK_MODULE

	total_block_memory_allocated += block_size * num_blocks;

	#endif

	//
	// initialise memory block array
	//

	new_array = (memarray*) safe_malloc (sizeof (memarray));

	new_array->type = MEM_TYPE_FAST;

	new_array->block_size = block_size;
	new_array->num_blocks = num_blocks;

	new_array->succ = NULL;
	new_array->pred = NULL;

	hdr_and_block_size = sizeof (memblock) + new_array->block_size;

	array_size = new_array->num_blocks * hdr_and_block_size;

	block = (memblock *) safe_malloc (array_size);

	new_array->base = block;
	new_array->first_free_block = block;
	new_array->first_used_block = NULL;

	#if DEBUG_MEMBLOCK_MODULE

	initialise_array_statistics (new_array);

	#endif

	//
	// initialise memory blocks
	//

	memset (block, 0, array_size);

	for (i = 0; i < new_array->num_blocks; i++)
	{
		#if MEMBLOCK_INTEGRITY_TEST

		block->integrity_test = INTEGRITY_TEST_VALUE;

		#endif

		block->array = new_array;

		if (i < new_array->num_blocks - 1)
		{
			block->succ = (memblock *) ((char *) block + hdr_and_block_size);
		}

		if (i > 0)
		{
			block->pred = (memblock *) ((char *) block - hdr_and_block_size);
		}

		#if DEBUG_MEMBLOCK_MODULE

		block->create_location = NULL;

		#endif

		block = block->succ;
	}

	// insert array into linked list in ascending order of block size
	//
	// linked list always terminated by heap memory array (block_size == INT_MAX)

	array = memory_block_arrays;

	while (new_array->block_size > array->block_size)
	{
		array = array->succ;
	}

	if (new_array->block_size == array->block_size)
	{
		debug_log ("WARNING! Duplicate memory block size used (block_size = %d)", new_array->block_size);
	}

	new_array->succ = array;

	if (array->pred)
	{
		array->pred->succ = new_array;

		new_array->pred = array->pred;
	}
	else
	{
		memory_block_arrays = new_array;
	}

	array->pred = new_array;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_memory_block_system_installed (void)
{
	return (memory_block_system_installed);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MEMBLOCK_MODULE

void *malloc_fast_memory (size_t size, char *file, int line)

#else

void *malloc_fast_memory (size_t size)

#endif
{
#if 0
	memblock
		*block;

	memarray
		*array;

	ASSERT (size > 0);

	#if DEBUG_MEMBLOCK_MODULE

	ASSERT (file);

	#endif

	#if DEBUG_MEMBLOCK_MODULE
	{
		int
			index;

		index = min (size, MAX_REQUESTED_MEMORY_SIZE - 1);

		requested_memory_size_total[index]++;

		requested_memory_size_count[index]++;

		requested_memory_size_peak_count[index] = max (requested_memory_size_peak_count[index], requested_memory_size_count[index]);
	}
	#endif

	ASSERT (memory_block_arrays);

	array = memory_block_arrays;

	while (!(block = get_memory_block (array, size)))
	{
		array = array->succ;
	}

	#if DEBUG_MEMBLOCK_MODULE
	{
		char
			s[200];

		int
			length;

		sprintf (s, "%s[%d]", file, line);

		length = strlen (s);

		block->create_location = (char *) safe_malloc (length + 1);

		strcpy (block->create_location, s);

		debug_log ("MALLOC FAST MEMORY: %s (size = %d)", s, size);
	}
	#endif

	//
	// return pointer to memory block (ignore header)
	//

	return ((void *) ((char *) block + sizeof (memblock)));
#else
	return malloc (size);
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MEMBLOCK_MODULE

void *malloc_heap_memory (size_t size, char *file, int line)

#else

void *malloc_heap_memory (size_t size)

#endif
{
#if 0
	memblock
		*block;

	ASSERT (size > 0);

	#if DEBUG_MEMBLOCK_MODULE

	ASSERT (file);

	#endif

	#if DEBUG_MEMBLOCK_MODULE
	{
		int
			index;

		index = min (size, MAX_REQUESTED_MEMORY_SIZE - 1);

		requested_memory_size_total[index]++;

		requested_memory_size_count[index]++;

		requested_memory_size_peak_count[index] = max (requested_memory_size_peak_count[index], requested_memory_size_count[index]);
	}
	#endif

	ASSERT (heap_array);

	block = get_memory_block (heap_array, size);

	#if DEBUG_MEMBLOCK_MODULE
	{
		char
			s[200];

		int
			length;

		sprintf (s, "%s[%d]", file, line);

		length = strlen (s);

		block->create_location = (char *) safe_malloc (length + 1);

		strcpy (block->create_location, s);

		debug_log ("MALLOC HEAP MEMORY: %s (size = %d)", s, size);
	}
	#endif

	//
	// return pointer to memory block (ignore header)
	//

	return ((void *) ((char *) block + sizeof (memblock)));
#else
	return malloc (size);
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void free_mem (void *ptr)
{
#if 0
	memblock
		*block;

	memarray
		*array;

	ASSERT (ptr);

	//
	// get pointer to block header
	//

	block = (memblock *) ((char *) ptr - sizeof (memblock));

	#if DEBUG_MEMBLOCK_MODULE

	debug_log ("FREE MEMORY: %s", block->create_location);

	//
	// this safe_free catches attempts to free the same memory twice
	//

	safe_free (block->create_location);

	block->create_location = NULL;

	#endif

	#if DEBUG_MEMBLOCK_MODULE
	{
		int
			index;

		index = min (block->size, MAX_REQUESTED_MEMORY_SIZE - 1);

		ASSERT (requested_memory_size_count[index] > 0);

		requested_memory_size_count[index]--;
	}
	#endif

	//
	// get pointer to array data
	//

	array = block->array;

	#if DEBUG_MEMBLOCK_MODULE

	update_array_statistics_free (array, block);

	#endif

	//
	// unlink block from used list
	//

	if (block->pred)
	{
		block->pred->succ = block->succ;
	}
	else
	{
		array->first_used_block = block->succ;
	}

	if (block->succ)
	{
		block->succ->pred = block->pred;
	}

	if (array->type == MEM_TYPE_FAST)
	{
		//
		// link block into start of free list
		//

		block->succ = array->first_free_block;

		if (block->succ)
		{
			block->succ->pred = block;
		}

		block->pred = NULL;

		array->first_free_block = block;

		//
		// clean up
		//

		block->size = 0;
	}
	else
	{
		safe_free (block);
	}
#else
	free (ptr);
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
memblock *get_memory_block (memarray *array, int size)
{
	memblock
		*block;

	if (array->type == MEM_TYPE_FAST)
	{
		if (size <= array->block_size)
		{
			block = array->first_free_block;

			if (block)
			{
				//
				// unlink block from start of free list
				//

				array->first_free_block = block->succ;

				if (block->succ)
				{
					block->succ->pred = NULL;
				}

				//
				// link block into start of used list
				//

				block->succ = array->first_used_block;

				if (block->succ)
				{
					block->succ->pred = block;
				}

				array->first_used_block = block;

				//
				// memory block details
				//

				block->size = size;

				//
				// update statistics
				//

				#if DEBUG_MEMBLOCK_MODULE

				update_array_statistics_malloc (array, block);

				#endif
			}
		}
		else
		{
			block = NULL;
		}
	}
	else
	{
		block = (memblock *) safe_malloc (sizeof (memblock) + size);

		//
		// link block into start of used list
		//

		block->succ = array->first_used_block;

		if (block->succ)
		{
			block->succ->pred = block;
		}

		block->pred = NULL;

		array->first_used_block = block;

		//
		// memory block details
		//

		#if MEMBLOCK_INTEGRITY_TEST

		block->integrity_test = INTEGRITY_TEST_VALUE;

		#endif

		block->size = size;

		block->array = array;

		//
		// update statistics
		//

		#if DEBUG_MEMBLOCK_MODULE

		update_array_statistics_malloc (array, block);

		#endif
	}

	return (block);
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if MEMBLOCK_INTEGRITY_TEST

void check_memory_block_system_integrity (void)
{
	memarray
		*array;

	memblock
		*block;

	array = memory_block_arrays;

	while (array)
	{
		block = array->first_used_block;

		while (block)
		{
			if (block->integrity_test != INTEGRITY_TEST_VALUE)
			{
				debug_fatal ("Memory block system integrity test failure");
			}

			block = block->succ;
		}

		array = array->succ;
	}
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MEMBLOCK_MODULE

void initialise_array_statistics (memarray *array)
{
	array->blocks_used_total				= 0;

	array->blocks_used_count				= 0;

	array->blocks_used_peak_count			= 0;

	array->total_requested_memory_size	= 0;

	array->total_allocated_memory_size	= 0;
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MEMBLOCK_MODULE

void update_array_statistics_malloc (memarray *array, memblock *block)
{
	int
		block_size;

	if (array->type == MEM_TYPE_FAST)
	{
		block_size = array->block_size;
	}
	else
	{
		array->num_blocks++;

		block_size = block->size;
	}

	array->blocks_used_total++;

	array->blocks_used_count++;

	array->blocks_used_peak_count = max (array->blocks_used_peak_count, array->blocks_used_count);

	array->total_requested_memory_size += block->size;

	array->total_allocated_memory_size += block_size;
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MEMBLOCK_MODULE

void update_array_statistics_free (memarray *array, memblock *block)
{
	int
		block_size;

	if (array->type == MEM_TYPE_FAST)
	{
		block_size = array->block_size;
	}
	else
	{
		array->num_blocks--;

		block_size = block->size;
	}

	ASSERT (array->blocks_used_count > 0);

	array->blocks_used_count--;
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MEMBLOCK_MODULE

void display_memory_block_system_statistics (void)
{
	memarray
		*array;

	float
		block_usage,
		storage_efficiency;

	int
		i;

	debug_log ("========================================");
	debug_log ("MEMORY BLOCK SYSTEM STATISTICS");
	debug_log ("========================================");

	debug_log ("total_block_memory_allocated = %d", total_block_memory_allocated);

	//
	// array statistics
	//

	array = memory_block_arrays;

	while (array)
	{
		debug_log ("========================================");

		if (array->type == MEM_TYPE_FAST)
		{
			debug_log ("Memory block array is MEM_TYPE_FAST");

			debug_log ("----------------------------------------");

			debug_log ("block_size                      = %d", array->block_size);

			debug_log ("num_blocks                      = %d", array->num_blocks);

			debug_log ("block_memory_allocated          = %d", array->block_size * array->num_blocks);
		}
		else
		{
			debug_log ("Memory block array is MEM_TYPE_HEAP");

			debug_log ("----------------------------------------");

			debug_log ("block_size                      = variable");

			debug_log ("num_blocks                      = %d", array->num_blocks);
		}

		debug_log ("blocks_used_total               = %d", array->blocks_used_total);

		debug_log ("blocks_used_count (should be 0) = %d", array->blocks_used_count);

		debug_log ("blocks_used_peak_count          = %d", array->blocks_used_peak_count);

		if (array->blocks_used_peak_count > 0)
		{
			block_usage = ((float) array->blocks_used_peak_count * 100.0) / (float) array->num_blocks;
		}
		else
		{
			block_usage = 0.0;
		}

		debug_log ("==>block_usage                  = %.2f%%", block_usage);

		debug_log ("total_requested_memory_size     = %d", array->total_requested_memory_size);

		debug_log ("total_allocated_memory_size     = %d", array->total_allocated_memory_size);

		if (array->total_allocated_memory_size > 0)
		{
			storage_efficiency = ((float) array->total_requested_memory_size * 100.0) / (float) array->total_allocated_memory_size;
		}
		else
		{
			storage_efficiency = 0.0;
		}

		debug_log ("==>storage_efficiency           = %.2f%%", storage_efficiency);

		array = array->succ;
	}

	//
	// requested memory size count
	//

	debug_log ("=====================================");

	debug_log ("REQUESTED MEMORY SIZE COUNT");

	debug_log ("----------------------------------------");

	for (i = 0; i < MAX_REQUESTED_MEMORY_SIZE; i++)
	{
		debug_log ("size = %4d, total = %5d, peak count = %5d", i, requested_memory_size_total[i], requested_memory_size_peak_count[i]);
	}

	debug_log ("=====================================");
}

#else

void display_memory_block_system_statistics (void)
{
	debug_log ("WARNING! Memory block system statistics are not enabled");
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
