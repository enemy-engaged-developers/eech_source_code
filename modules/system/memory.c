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



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "system.h"

#include "errno.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char
	mem_total_value;

static unsigned long
	initial_total_memory_available;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pretouch_memory ( char *memory, int size )
{

	int
		count;

	mem_total_value = 0;

	for ( count = 0; count < size; count += 2048 )
	{

		mem_total_value += *memory;

		memory += 2048;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_memory_totals ( void )
{

#ifdef WIN32
	MEMORYSTATUS
		status;

	int
		physical_memory_available,
		virtual_memory_available;

	status.dwLength = sizeof ( status );

	GlobalMemoryStatus ( &status );

	physical_memory_available = status.dwTotalPhys - status.dwAvailPhys;

	virtual_memory_available = status.dwTotalPageFile - status.dwAvailPageFile;

	initial_total_memory_available = physical_memory_available + virtual_memory_available;

#elif LINUX

	struct sysinfo sinfo;

	if( sysinfo( &sinfo ) == 0 ) {
		initial_total_memory_available = sinfo.freeram;
	}
	else {
		debug_log("sysinfo(2) call failed: %s\n", strerror(errno));
	}

#else
	// TODO: Implement for operating systems that aren't Linux or Windows
	debug_log ( "TODO: implement initialise_memory_totals() on this platform.") ;
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void report_memory_totals ( char *string )
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

	debug_log ( "MEMORY USED %s - %d", string, total_memory_available - initial_total_memory_available );
	debug_log ( "Total Physical memory: %d", status.dwTotalPhys );
	debug_log ( "Physical memory available: %d", status.dwAvailPhys );

	debug_log ( "Total Virtual memory: %d", status.dwTotalPageFile );
	debug_log ( "Virtual memory available: %d", status.dwAvailPageFile );

#elif LINUX

	// NOTE: This requires the new sysinfo structure only available in Linux 2.3.23 (i386), 2.3.48 (all architectures)

	struct sysinfo sinfo;

	if( sysinfo( &sinfo ) == 0 ) {
		debug_log ( "MEMORY USED %s - %d", string, sinfo.freeram - initial_total_memory_available );

		debug_log ( "Total Physical memory: %d", sinfo.totalhigh );
		debug_log ( "Physical memory available: %d", sinfo.freehigh );
		
		debug_log ( "Total Virtual memory: %d", sinfo.totalswap );
		debug_log ( "Virtual memory available: %d", sinfo.freeswap );
	}
	else {
		debug_log("sysinfo(2) call failed: %s\n", strerror(errno));
	}

#else
	// TODO: implement on non-win32
	debug_log ( "TODO: implement report_memory_totals(char *) on non-win32.") ;
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void walk_memory_heap ( void )
{

#ifdef WIN32
	struct _heapinfo
		heap;
#endif

	int
		heap_status;

	long
		memory_allocated;

	FILE
		*fp;

	fp = fopen ( "heap.log", "w" );

	memory_allocated = 0;;

	if ( fp )
	{
	
#ifdef WIN32
		heap._pentry = NULL;
	
		for(;;)
		{
	
			heap_status = _heapwalk( &heap );
	
			if ( heap_status != _HEAPOK )
				break;
	
			fprintf ( fp, "%s block at %Fp of size %d\n", ( heap._useflag == _USEDENTRY ? "USED" : "FREE" ), heap._pentry, heap._size );

			if ( heap._useflag == _USEDENTRY )
			{

				memory_allocated += heap._size;
			}
		}
		
		switch ( heap_status )
		{
	
			case _HEAPEND:
			{
		
				fprintf ( fp, "OK - end of heap\n" );
	
				break;
			}
			case _HEAPEMPTY:
			{
	
				fprintf ( fp, "OK - heap is empty\n" );
	
				break;
			}
			case _HEAPBADBEGIN:
			{
	
				fprintf ( fp, "ERROR - heap is damaged\n" );
	
				break;
			}
			case _HEAPBADPTR:
			{
	
				fprintf ( fp, "ERROR - bad pointer to heap\n" );
	
				break;
			}
			case _HEAPBADNODE:
			{
	
				fprintf ( fp, "ERROR - bad node in heap\n" );
	
				break;
			}
		}

		fprintf ( fp, "Total memory_allocated = %d", memory_allocated );
#else
		// TODO: implement on non-win32
		fprintf ( fp, "TODO: implement walk_memory_heap() on non-win32.\n" );
#endif

		fclose ( fp );
	}
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

