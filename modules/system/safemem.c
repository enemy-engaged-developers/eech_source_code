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



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "system.h"

#ifndef WIN32
#include <errno.h>
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define SAFE_MEMORY_TRACKING 0

#define REPORT_SAFE_MEM_MALLOCS 0

#define MIN_SAFE_MEM_TRACK_SIZE 256

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct SAFE_MEMORY_TRACK
{

	void
		*memory;

	char
		*file;

	int
		size,
		line;

	struct SAFE_MEMORY_TRACK
		*succ,
		*pred;
};

typedef struct SAFE_MEMORY_TRACK safe_memory_track;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int
	safe_memory_counter = 0,
	report_safe_memory_warnings = TRUE,
	total_safe_memory_allocated = 0,
	maximum_safe_memory_allocated = 0;

static safe_memory_track
	*safe_memory_tracks = NULL;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_report_safe_memory_warnings (int flag)
{
	report_safe_memory_warnings = flag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_safe_memory_counter (void)
{
	if (report_safe_memory_warnings)
	{
		debug_colour_log (DEBUG_COLOUR_AMBER, "NOTE! Safe memory counter reset");
	}

	safe_memory_counter = 0;

	debug_watch ("Total safe memory allocated: %d", MT_INT, &total_safe_memory_allocated);
	debug_watch ("Maximum safe memory allocated: %d", MT_INT, &maximum_safe_memory_allocated);
	debug_watch ("Safe memory counter: %d", MT_INT, &safe_memory_counter );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void check_safe_memory_counter (void)
{
	if (report_safe_memory_warnings)
	{
		if (safe_memory_counter == 0)
		{
			debug_colour_log (DEBUG_COLOUR_AMBER, "NOTE! Safe memory counter == 0");
		}
		else
		{
			debug_colour_log (DEBUG_COLOUR_AMBER, "WARNING! Safe memory counter != 0 (counter = %d)", safe_memory_counter);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_SAFEMEM_MODULE

void *safe_malloc_memory (size_t size, char *file, int line)
{
	void
		*ptr;

	ASSERT (size > 0);

	ptr = malloc (size);

	ASSERT (ptr);

	safe_memory_counter++;

#if REPORT_SAFE_MEM_MALLOCS
	if ( size > 2048 )
	{
	
		debug_log ("SAFE_MALLOC: %s[%d] (size = %d)", file, line, size);
	}
#endif

	//
	// if debugging then report every so often if safe_memory_counter is getting large
	//

	#ifdef DEBUG
	{
		static int
			old_thousands = 0;

		int
			new_thousands;

		new_thousands = safe_memory_counter / 1000;

		if (report_safe_memory_warnings)
		{
			if (new_thousands > old_thousands)
			{
				old_thousands = new_thousands;

//				debug_colour_log (DEBUG_COLOUR_AMBER, "WARNING! Safe memory counter exceeded %d000", new_thousands);
			}
		}

		old_thousands = new_thousands;
	}
	#endif

	//
	// Add this to the total safe memory allocated
	//

	total_safe_memory_allocated += size;

	if (total_safe_memory_allocated > maximum_safe_memory_allocated)
	{
		maximum_safe_memory_allocated = total_safe_memory_allocated;
	}

#if SAFE_MEMORY_TRACKING
	if ( size > MIN_SAFE_MEM_TRACK_SIZE )
	{

		safe_memory_track
			*track;

		track = malloc ( sizeof ( safe_memory_track ) );

		track->memory = ptr;
		track->size = size;
		track->file = malloc ( strlen ( file ) + 1 );
		strcpy ( track->file, file );
		track->line = line;
		track->succ = safe_memory_tracks;
		track->pred = NULL;

		if ( safe_memory_tracks )
		{

			safe_memory_tracks->pred = track;
		}

		safe_memory_tracks = track;
	}
#endif

	return (ptr);
}

#else

void *safe_malloc_memory (size_t size)
{
	void
		*ptr;

	ASSERT (size > 0);

	ptr = malloc (size);

	if (!ptr)
	{

#ifdef WIN32
		MEMORYSTATUS
			status;
	
		int
			physical_memory_available,
			virtual_memory_available,
			total_memory_available;
	
		status.dwLength = sizeof ( status );
	
		GlobalMemoryStatus ( &status );
	
		physical_memory_available = status.dwTotalPhys - status.dwAvailPhys;
	
		virtual_memory_available = status.dwTotalPageFile - status.dwAvailPageFile;
	
		total_memory_available = physical_memory_available + virtual_memory_available;
	
		debug_fatal ( "Unable to allocate memory size %d - Windows reports there is only %d memory available", size, total_memory_available );
#else
		// TODO: print some more useful memory information here.
		debug_fatal ( "Unable to allocate memory size %d - %s", size, strerror(errno) );		
#endif
	}

	safe_memory_counter++;

	//
	// if debugging then report every so often if safe_memory_counter is getting large
	//

	#ifdef DEBUG
	{
		static int
			old_thousands = 0;

		int
			new_thousands;

		new_thousands = safe_memory_counter / 1000;

		if (report_safe_memory_warnings)
		{
			if (new_thousands > old_thousands)
			{
				old_thousands = new_thousands;

//				debug_colour_log (DEBUG_COLOUR_AMBER, "WARNING! Safe memory counter exceeded %d000", new_thousands);
			}
		}

		old_thousands = new_thousands;
	}
	#endif

	//
	// Add this to the total safe memory allocated
	//

	total_safe_memory_allocated += size;

	if (total_safe_memory_allocated > maximum_safe_memory_allocated)
	{
		maximum_safe_memory_allocated = total_safe_memory_allocated;
	}

	return (ptr);
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void safe_free (void *ptr)
{
	ASSERT (ptr);

	total_safe_memory_allocated -= (_msize (ptr));

	free (ptr);

	safe_memory_counter--;

#if SAFE_MEMORY_TRACKING
	{

		safe_memory_track
			*track;

		track = safe_memory_tracks;

		while ( track )
		{

			if ( track->memory == ptr )
			{

				free ( track->file );

				if ( track->succ )
				{

					track->succ->pred = track->pred;
				}

				if ( track->pred )
				{

					track->pred->succ = track->succ;
				}
				else
				{

					safe_memory_tracks = track->succ;
				}

				break;
			}

			track = track->succ;
		}
	}
#endif

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void report_tracked_safe_memory (void)
{

	safe_memory_track
		*track;

	debug_log ( "BEGIN TRACKED MEMORY STATUS ( total safemem allocated: %d )", total_safe_memory_allocated );

	track = safe_memory_tracks;

	while ( track )
	{

		debug_log ( "%s [%d]: %d", track->file, track->line, track->size );

		track = track->succ;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void report_total_safe_memory_allocated (void)
{
	debug_log ("Total safe memory allocated: %d", total_safe_memory_allocated);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
