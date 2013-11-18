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

#include "system.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct monitor_data
{

	struct monitor_data
		*pred,
		*succ;

	int
		offset,
		number;

	char
		*string;

	enum mt_type
		type;

	COLORREF
		colour;

	void
		*data,
		*data2,
		*data3,
		*data4;
};

typedef struct monitor_data MONITORDATA;

typedef struct monitor_data *LPMONITORDATA;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static HWND
	application_debug_log_window,
	application_debug_watch_window,
	application_debug_filtered_log_window;

int
	debug_fatal_warning_tone = TRUE;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HANDLE
	application_monitor_thread;

static LPMONITORDATA

#ifdef DEBUG

	first_log_monitor = NULL,

	last_log_monitor = NULL,

	first_filtered_log_monitor = NULL,

	last_filtered_log_monitor = NULL,

#endif

	first_watch_monitor = NULL,

	top_watch_monitor = NULL,

	last_watch_monitor = NULL,

	top_log_monitor = NULL,

	top_filtered_log_monitor = NULL;

static int
	debug_monitor_auto_update,

	debug_monitor = FALSE,								// Initially there is no debug monitor created

	debug_log_state = FALSE,							// Initially no logging is done.

	debug_timing_info_suppressed = FALSE,			 // Initially there is timing info

	number_of_watch_lines = 0,							// Number of debug monitor lines on display in the window

	number_of_watch_monitor_lines = 0,				// Total number of monitor lines

	//current_log_monitor_line = 0,						// Current monitor line at top of monitor window

	number_of_log_lines = 0,							// Number of debug monitor lines on display in the window

	//current_filtered_log_monitor_line = 0,			// Current monitor line at top of monitor window

	number_of_filtered_log_lines = 0;				// Number of debug monitor lines on display in the window

#ifdef DEBUG

static int
	number_of_log_monitor_lines = 0,					// Total number of monitor lines
	number_of_filtered_log_monitor_lines = 0;		// Total number of monitor lines

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static char
	debug_log_file_name[100],
	debug_filtered_log_file_name[100];

static COLORREF
	debug_colour_table[DEBUG_COLOUR_LAST];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void deinitialise_debug_system ( void );

static long initialise_internal_debug_system ( void * data );

static long WINAPI debug_window_notify ( HWND window_handle, UINT message, WPARAM wParam, LPARAM lParam );

static void application_monitor_process_thread ( void );

static int debug_initialise_message_id;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void debug_set_window_creation ( enum debug_window_creation create )
{

	if ( create == DEBUG_CREATE_WINDOW )
	{

		debug_monitor = TRUE;
	}
	else
	{

		debug_monitor = FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void debug_set_windows_update ( enum debug_update_state update )
{

	if ( update == DEBUG_UPDATE_AUTO )
	{

		debug_monitor_auto_update = TRUE;
	}
	else
	{

		debug_monitor_auto_update = FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void debug_set_logging ( int logging )
{

	debug_log_state = logging;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void suppress_debug_log_timing_info ( int flag )
{

	debug_timing_info_suppressed = flag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_debug_system ( int logging )
{

	strcpy (debug_log_file_name, "DEBUG.LOG");

	strcpy (debug_filtered_log_file_name, "DEBUG.FIL");

	unlink ( debug_filtered_log_file_name );

	debug_initialise_message_id = get_unique_message_id ();

	register_user_message_function ( debug_initialise_message_id, initialise_internal_debug_system );

	register_exit_function ( deinitialise_debug_system );

	debug_log_state = logging;

	debug_colour_table[DEBUG_COLOUR_BLACK] =			RGB ( 0, 0, 0 );
	debug_colour_table[DEBUG_COLOUR_BLUE] =			RGB ( 0, 0, 255 );
	debug_colour_table[DEBUG_COLOUR_GREEN] =			RGB ( 0, 255, 0 );
	debug_colour_table[DEBUG_COLOUR_CYAN] =			RGB ( 0, 255, 255 );
	debug_colour_table[DEBUG_COLOUR_RED] =				RGB ( 255, 0, 0 );
	debug_colour_table[DEBUG_COLOUR_MAGENTA] =		RGB ( 255, 0, 255 );
	debug_colour_table[DEBUG_COLOUR_YELLOW] =			RGB ( 255, 255, 0 );
	debug_colour_table[DEBUG_COLOUR_WHITE] =			RGB ( 255, 255, 255 );
	debug_colour_table[DEBUG_COLOUR_SKY_BLUE] =		RGB ( 135, 206, 235 );
	debug_colour_table[DEBUG_COLOUR_SLATE_GREY] =	RGB ( 112, 128, 144 );
	debug_colour_table[DEBUG_COLOUR_FOREST_GREEN] =	RGB ( 34, 139,  34 );
	debug_colour_table[DEBUG_COLOUR_ULTRAMARINE] =	RGB ( 18, 0, 143 );
	debug_colour_table[DEBUG_COLOUR_SEABLUE] =		RGB ( 90, 130, 190 );
	debug_colour_table[DEBUG_COLOUR_AQUAMARINE] =	RGB ( 127, 255, 212 );
	debug_colour_table[DEBUG_COLOUR_GOLD] =			RGB ( 255, 215, 0 );
	debug_colour_table[DEBUG_COLOUR_LIGHT_GREY] =	RGB ( 200, 200, 200 );
	debug_colour_table[DEBUG_COLOUR_LIGHT_RED] =		RGB ( 255, 150, 150 );
	debug_colour_table[DEBUG_COLOUR_DARK_RED] =		RGB ( 150, 0, 0 );
	debug_colour_table[DEBUG_COLOUR_DARK_GREEN] =	RGB ( 0, 150, 0 );
	debug_colour_table[DEBUG_COLOUR_DARK_BLUE] =		RGB ( 0, 0, 100 );
	debug_colour_table[DEBUG_COLOUR_MEDIUM_BLUE] =	RGB ( 50, 50, 150 );
	debug_colour_table[DEBUG_COLOUR_MEDIUM_RED] =	RGB ( 255, 50, 50 );
	debug_colour_table[DEBUG_COLOUR_SANDY_BROWN] =	RGB ( 244, 164,  96 );
	debug_colour_table[DEBUG_COLOUR_AMBER] =			RGB ( 255, 128, 0 );

#ifdef DEBUG

	// opengl
	SendMessage ( application_window, WM_USER, debug_initialise_message_id, 0 );

#endif

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void deinitialise_debug_system ( void )
{

	if ( debug_monitor_auto_update )
	{

		//
		// Disable the updating thread - but can't TerminateThread it in case its in kernel32 routines
		//

		SetThreadPriority ( application_monitor_thread, THREAD_PRIORITY_IDLE );
	}

/*
	if ( application_debug_log_window )
	{

		DestroyWindow ( application_debug_log_window );

		application_debug_log_window = 0;
	}

	if ( application_debug_watch_window )
	{

		DestroyWindow ( application_debug_watch_window );

		application_debug_watch_window = 0;
	}
	*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

long initialise_internal_debug_system ( void * data )
{

	WNDCLASS
		wc;

	DWORD
		monitor_thread_id;


	if ( debug_monitor )
	{

		memset ( &wc, 0, sizeof ( wc ) );

		wc.lpszClassName = "DebugLogClass";
		wc.hInstance = application_instance;
		wc.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_NOCLOSE;
		wc.lpfnWndProc = (WNDPROC) debug_window_notify;
		wc.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

		if ( !RegisterClass ( &wc ) )
		{

			return FALSE;
		}

		wc.lpszClassName = "DebugWatchClass";
		wc.hInstance = application_instance;
		wc.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_NOCLOSE;
		wc.lpfnWndProc = (WNDPROC) debug_window_notify;
		wc.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

		if ( !RegisterClass ( &wc ) )
		{

			return FALSE;
		}

		wc.lpszClassName = "DebugLogFilteredClass";
		wc.hInstance = application_instance;
		wc.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_NOCLOSE;
		wc.lpfnWndProc = (WNDPROC) debug_window_notify;
		wc.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

		if ( !RegisterClass ( &wc ) )
		{

			return FALSE;
		}

		application_debug_log_window = CreateWindow
		(
			"DebugLogClass",
			"Debug Log",
			WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_VISIBLE | LBS_DISABLENOSCROLL,
			1292,
			600,
			600,
			450,
			NULL,
			NULL,
			application_instance,
			NULL
		);

		SetScrollRange (application_debug_log_window, SB_VERT, 0, 0, TRUE);

		SetScrollPos (application_debug_log_window, SB_VERT, 0, TRUE);

		application_debug_watch_window = CreateWindow
		(
			"DebugWatchClass",
			"Debug Watch",
			WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_VISIBLE | LBS_DISABLENOSCROLL,
			1292,
			0,
			600,
			400,
			NULL,
			NULL,
			application_instance,
			NULL
		);

		SetScrollRange (application_debug_watch_window, SB_VERT, 0, 0, TRUE);

		SetScrollPos (application_debug_watch_window, SB_VERT, 0, TRUE);

		application_debug_filtered_log_window = CreateWindow
		(
			"DebugLogFilteredClass",
			"Debug Log Filter",
			WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_VISIBLE | LBS_DISABLENOSCROLL,
			1292,
			400,
			600,
			200,
			NULL,
			NULL,
			application_instance,
			NULL
		);

		SetScrollRange (application_debug_filtered_log_window, SB_VERT, 0, 0, TRUE);

		SetScrollPos (application_debug_filtered_log_window, SB_VERT, 0, TRUE);

		//
		// Create the thread to auto update the debug windows, if we want to
		//

		if ( ( application_debug_watch_window ) && ( application_debug_log_window ) )
		{

			if ( debug_monitor_auto_update )
			{

				application_monitor_thread = CreateThread
				(
					(LPSECURITY_ATTRIBUTES) NULL,
					0,
					(LPTHREAD_START_ROUTINE) application_monitor_process_thread,
					0,
					0,
					&monitor_thread_id
				);

//				SetThreadPriority ( application_monitor_thread, THREAD_PRIORITY_LOWEST );
			}
		}

		//
		// Set the focus back to the main application window
		//

		SetFocus ( application_window );
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef DEBUG

void debug_log (const char *msg, ...)
{
	static char
		buffer[4096];

	char
		time_info[100];

	va_list
		args;

	LPMONITORDATA
		md,
		temp;


	if ( debug_log_state )
	{

		va_start (args, msg);

		vsprintf (buffer, msg, args);

		if ( !debug_timing_info_suppressed )
		{

			sprintf (time_info, " @ %.2f", ( (float) system_ticks / 100.0 ) );

			strcat (buffer, time_info);
		}

		va_end (args);

//		OutputDebugString ( buffer );

		if ( debug_monitor )
		{

			md = ( LPMONITORDATA ) malloc ( sizeof ( MONITORDATA ) );

			memset ( md, 0, sizeof ( MONITORDATA ) );

			md->succ = NULL;

			md->pred = last_log_monitor;

			md->colour = debug_colour_table[DEBUG_COLOUR_BLACK];

			if ( last_log_monitor )
			{

				last_log_monitor->succ = md;
			}

			if ( first_log_monitor == NULL )
			{

				top_log_monitor = md;

				first_log_monitor = md;
			}

			last_log_monitor = md;

			number_of_log_monitor_lines ++;

			md->number = 0;
			md->offset = number_of_log_monitor_lines;
			md->string = strdup ( buffer );
			md->type = MT_NONE;
			md->data = NULL;

			SetScrollRange ( application_debug_log_window, SB_VERT, 0, number_of_log_monitor_lines, TRUE );

			if ( number_of_log_monitor_lines > number_of_log_lines )
			{

				int
					count;

				temp = md;

				for ( count=0; count<number_of_log_lines; count++ )
				{

					temp = temp->pred;
				}

				top_log_monitor = temp;

				SetScrollPos ( application_debug_log_window, SB_VERT, top_log_monitor->offset, TRUE);
			}
		}

#if 1
		{
			FILE
				*fp;

			fp = fopen ( debug_log_file_name, "a" );

			if ( fp )
			{
				fwrite ( buffer, 1, strlen ( buffer ), fp );

				fwrite ( "\n", 1, 1, fp );

				fclose ( fp );
			}
		}
#endif
	}
}

void debug_colour_log ( enum DEBUG_COLOURS colour, const char *msg, ...)
{
#if 1
	FILE
		*fp;
#endif
	static char
		buffer[1000];

	char
		time_info[100];

	va_list
		args;

	LPMONITORDATA
		md,
		temp;


	if ( debug_log_state )
	{

		va_start (args, msg);

		vsprintf (buffer, msg, args);

		if ( !debug_timing_info_suppressed )
		{

			sprintf (time_info, " @ %.2f", ( (float) system_ticks / 100.0 ) );

			strcat (buffer, time_info);
		}

		va_end (args);

		if ( debug_monitor )
		{

			md = ( LPMONITORDATA ) malloc ( sizeof ( MONITORDATA ) );

			memset ( md, 0, sizeof ( MONITORDATA ) );

			md->succ = NULL;

			md->pred = last_log_monitor;

			md->colour = debug_colour_table[colour];

			if ( last_log_monitor )
			{

				last_log_monitor->succ = md;
			}

			if ( first_log_monitor == NULL )
			{

				top_log_monitor = md;

				first_log_monitor = md;
			}

			last_log_monitor = md;

			number_of_log_monitor_lines ++;

			md->number = 0;
			md->offset = number_of_log_monitor_lines;
			md->string = strdup ( buffer );
			md->type = MT_NONE;
			md->data = NULL;

			SetScrollRange ( application_debug_log_window, SB_VERT, 0, number_of_log_monitor_lines, TRUE );

			if ( number_of_log_monitor_lines > number_of_log_lines )
			{

				int
					count;

				temp = md;

				for ( count=0; count<number_of_log_lines; count++ )
				{

					temp = temp->pred;
				}

				top_log_monitor = temp;

				SetScrollPos ( application_debug_log_window, SB_VERT, top_log_monitor->offset, TRUE);
			}
		}

#if 1
		fp = fopen ( debug_log_file_name, "a" );

		if ( fp )
		{

			fwrite ( buffer, 1, strlen ( buffer ), fp );

			fwrite ( "\n", 1, 1, fp );

			fclose ( fp );
		}
#endif
	}
}

void debug_filtered_log (const char *msg, ...)
{
#if 0
	FILE
		*fp;
#endif
	static char
		buffer[1000];

	char
		time_info[100];

	va_list
		args;

	LPMONITORDATA
		md,
		temp;


	if ( debug_log_state )
	{

		va_start (args, msg);

		vsprintf (buffer, msg, args);

		if ( !debug_timing_info_suppressed )
		{

			sprintf (time_info, " @ %.2f", ( (float) system_ticks / 100.0 ) );

			strcat (buffer, time_info);
		}

		va_end (args);

		if ( debug_monitor )
		{

			md = ( LPMONITORDATA ) malloc ( sizeof ( MONITORDATA ) );

			memset ( md, 0, sizeof ( MONITORDATA ) );

			md->succ = NULL;

			md->pred = last_filtered_log_monitor;

			md->colour = debug_colour_table[DEBUG_COLOUR_BLACK];

			if ( last_filtered_log_monitor )
			{

				last_filtered_log_monitor->succ = md;
			}

			if ( first_filtered_log_monitor == NULL )
			{

				top_filtered_log_monitor = md;

				first_filtered_log_monitor = md;
			}

			last_filtered_log_monitor = md;

			number_of_filtered_log_monitor_lines ++;

			md->number = 0;
			md->offset = number_of_filtered_log_monitor_lines;
			md->string = strdup ( buffer );
			md->type = MT_NONE;
			md->data = NULL;

			SetScrollRange ( application_debug_filtered_log_window, SB_VERT, 0, number_of_filtered_log_monitor_lines, TRUE );

			if ( number_of_filtered_log_monitor_lines > number_of_filtered_log_lines )
			{

				int
					count;

				temp = md;

				for ( count=0; count<number_of_filtered_log_lines; count++ )
				{

					temp = temp->pred;
				}

				top_filtered_log_monitor = temp;

				SetScrollPos ( application_debug_filtered_log_window, SB_VERT, top_filtered_log_monitor->offset, TRUE);
			}
		}

#if 0
		fp = fopen ( debug_filtered_log_file_name, "a" );

		if ( fp )
		{

			fwrite ( buffer, 1, strlen ( buffer ), fp );

			fwrite ( "\n", 1, 1, fp );

			fclose ( fp );
		}
#endif
	}
}

void debug_colour_filtered_log ( enum DEBUG_COLOURS colour, const char *msg, ...)
{
#if 0
	FILE
		*fp;
#endif
	static char
		buffer[1000];

	char
		time_info[100];

	va_list
		args;

	LPMONITORDATA
		md,
		temp;


	if ( debug_log_state )
	{

		va_start (args, msg);

		vsprintf (buffer, msg, args);

		if ( !debug_timing_info_suppressed )
		{

			sprintf (time_info, " @ %.2f", ( (float) system_ticks / 100.0 ) );

			strcat (buffer, time_info);
		}

		va_end (args);

		if ( debug_monitor )
		{

			md = ( LPMONITORDATA ) malloc ( sizeof ( MONITORDATA ) );

			memset ( md, 0, sizeof ( MONITORDATA ) );

			md->succ = NULL;

			md->pred = last_log_monitor;

			md->colour = debug_colour_table[colour];

			if ( last_filtered_log_monitor )
			{

				last_filtered_log_monitor->succ = md;
			}

			if ( first_filtered_log_monitor == NULL )
			{

				top_filtered_log_monitor = md;

				first_filtered_log_monitor = md;
			}

			last_filtered_log_monitor = md;

			number_of_filtered_log_monitor_lines ++;

			md->number = 0;
			md->offset = number_of_filtered_log_monitor_lines;
			md->string = strdup ( buffer );
			md->type = MT_NONE;
			md->data = NULL;

			SetScrollRange ( application_debug_filtered_log_window, SB_VERT, 0, number_of_filtered_log_monitor_lines, TRUE );

			if ( number_of_filtered_log_monitor_lines > number_of_filtered_log_lines )
			{

				int
					count;

				temp = md;

				for ( count=0; count<number_of_filtered_log_lines; count++ )
				{

					temp = temp->pred;
				}

				top_filtered_log_monitor = temp;

				SetScrollPos ( application_debug_filtered_log_window, SB_VERT, top_filtered_log_monitor->offset, TRUE);
			}
		}

#if 0
		fp = fopen ( debug_filtered_log_file_name, "a" );

		if ( fp )
		{

			fwrite ( buffer, 1, strlen ( buffer ), fp );

			fwrite ( "\n", 1, 1, fp );

			fclose ( fp );
		}
#endif
	}
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void debug_fatal ( const char *string, ... )
{

	va_list
		argument_list;

	FILE
		*fp;

	char
		buffer[4096];

	//
	// Work out what to output
	//

	va_start ( argument_list, string );

	vsprintf ( buffer, string, argument_list );

	va_end ( argument_list );

	if ( debug_log_state )
	{

		//
		// Open file for append.
		//

		fp = fopen ( debug_log_file_name, "a" );

		if ( fp )
		{

			//
			// Output the buffer to the file with ***FATAL*** so that it is easy to find.
			//

			fputs ( "************************************ FATAL ***********************************\n", fp );

			fputs ( buffer, fp );

			fputs ( "\n", fp );

			//
			// Close the file, just incase the system is unstable, so that the file is intact
			//

			fclose ( fp );
		}
	}

	//
	// Make sound to annoy everyone
	//

	#ifdef DEBUG

	if (debug_fatal_warning_tone)
	{

		int
			count;

		for ( count = 1000; count > 500; count -= 50 )
		{

			Beep ( count, 100 );
		}
	}

	#endif

	//
	// Exit the program
	//

	application_debug_fatal = TRUE;

	strcpy ( application_debug_fatal_string, buffer );

	end_application ();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_watch_item ( LPMONITORDATA md )
{

	md->succ = NULL;

	md->pred = last_watch_monitor;

	if ( last_watch_monitor )
	{

		last_watch_monitor->succ = md;
	}

	if ( first_watch_monitor == NULL )
	{

		top_watch_monitor = md;

		first_watch_monitor = md;
	}

	last_watch_monitor = md;

	number_of_watch_monitor_lines ++;

	SetScrollRange ( application_debug_watch_window, SB_VERT, 0, number_of_watch_monitor_lines, TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef DEBUG

void debug_watch ( const char *string, enum mt_type type, void *data )
{

	LPMONITORDATA
		md;

	if ( debug_log_state )
	{

		if ( debug_monitor )
		{

			md = ( LPMONITORDATA ) malloc ( sizeof ( MONITORDATA ) );

			memset ( md, 0, sizeof ( MONITORDATA ) );

			add_watch_item ( md );

			md->offset = number_of_watch_monitor_lines;
			md->number = 1;
			md->string = strdup ( string );
			md->type = type;
			md->data = data;
			md->colour = debug_colour_table[DEBUG_COLOUR_BLACK];
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void debug_watch2 ( const char *string, enum mt_type type, void *data1, void *data2 )
{

	LPMONITORDATA
		md;

	if ( debug_log_state )
	{

		if ( debug_monitor )
		{

			md = ( LPMONITORDATA ) malloc ( sizeof ( MONITORDATA ) );

			memset ( md, 0, sizeof ( MONITORDATA ) );

			add_watch_item ( md );

			md->number = 2;
			md->offset = number_of_watch_monitor_lines;
			md->string = strdup ( string );
			md->type = type;
			md->data = data1;
			md->data2 = data2;
			md->colour = debug_colour_table[DEBUG_COLOUR_BLACK];
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void debug_watch3 ( const char *string, enum mt_type type, void *data1, void *data2, void *data3 )
{

	LPMONITORDATA
		md;

	if ( debug_log_state )
	{

		if ( debug_monitor )
		{

			md = ( LPMONITORDATA ) malloc ( sizeof ( MONITORDATA ) );

			memset ( md, 0, sizeof ( MONITORDATA ) );

			add_watch_item ( md );

			md->number = 3;
			md->offset = number_of_watch_monitor_lines;
			md->string = strdup ( string );
			md->type = type;
			md->data = data1;
			md->data2 = data2;
			md->data3 = data3;
			md->colour = debug_colour_table[DEBUG_COLOUR_BLACK];
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void debug_watch4 ( const char *string, enum mt_type type, void *data1, void *data2, void *data3, void *data4 )
{

	LPMONITORDATA
		md;

	if ( debug_log_state )
	{

		if ( debug_monitor )
		{

			md = ( LPMONITORDATA ) malloc ( sizeof ( MONITORDATA ) );

			memset ( md, 0, sizeof ( MONITORDATA ) );

			add_watch_item ( md );

			md->number = 4;
			md->offset = number_of_watch_monitor_lines;
			md->string = strdup ( string );
			md->type = type;
			md->data = data1;
			md->data2 = data2;
			md->data3 = data3;
			md->data4 = data4;
			md->colour = debug_colour_table[DEBUG_COLOUR_BLACK];
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void debug_colour_watch ( enum DEBUG_COLOURS colour, const char *string, enum mt_type type, void *data )
{

	LPMONITORDATA
		md;

	if ( debug_log_state )
	{

		if ( debug_monitor )
		{

			md = ( LPMONITORDATA ) malloc ( sizeof ( MONITORDATA ) );

			memset ( md, 0, sizeof ( MONITORDATA ) );

			add_watch_item ( md );

			md->offset = number_of_watch_monitor_lines;
			md->number = 1;
			md->string = strdup ( string );
			md->type = type;
			md->data = data;
			md->colour = debug_colour_table[colour];
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void debug_colour_watch2 ( enum DEBUG_COLOURS colour, const char *string, enum mt_type type, void *data1, void *data2 )
{

	LPMONITORDATA
		md;

	if ( debug_log_state )
	{

		if ( debug_monitor )
		{

			md = ( LPMONITORDATA ) malloc ( sizeof ( MONITORDATA ) );

			memset ( md, 0, sizeof ( MONITORDATA ) );

			add_watch_item ( md );

			md->number = 2;
			md->offset = number_of_watch_monitor_lines;
			md->string = strdup ( string );
			md->type = type;
			md->data = data1;
			md->data2 = data2;
			md->colour = debug_colour_table[colour];
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void debug_colour_watch3 ( enum DEBUG_COLOURS colour, const char *string, enum mt_type type, void *data1, void *data2, void *data3 )
{

	LPMONITORDATA
		md;

	if ( debug_log_state )
	{

		if ( debug_monitor )
		{

			md = ( LPMONITORDATA ) malloc ( sizeof ( MONITORDATA ) );

			memset ( md, 0, sizeof ( MONITORDATA ) );

			add_watch_item ( md );

			md->number = 3;
			md->offset = number_of_watch_monitor_lines;
			md->string = strdup ( string );
			md->type = type;
			md->data = data1;
			md->data2 = data2;
			md->data3 = data3;
			md->colour = debug_colour_table[colour];
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void debug_colour_watch4 ( enum DEBUG_COLOURS colour, const char *string, enum mt_type type, void *data1, void *data2, void *data3, void *data4 )
{

	LPMONITORDATA
		md;

	if ( debug_log_state )
	{

		if ( debug_monitor )
		{

			md = ( LPMONITORDATA ) malloc ( sizeof ( MONITORDATA ) );

			memset ( md, 0, sizeof ( MONITORDATA ) );

			add_watch_item ( md );

			md->number = 4;
			md->offset = number_of_watch_monitor_lines;
			md->string = strdup ( string );
			md->type = type;
			md->data = data1;
			md->data2 = data2;
			md->data3 = data3;
			md->data4 = data4;
			md->colour = debug_colour_table[colour];
		}
	}
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void breakout ( event *ev )
{

	ev;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_window (HWND window_handle)
{

	int
		x,
		y,
		tab_size,
		tsize;

	LPMONITORDATA
		md;

	HDC
		hdc;

	RECT
		rest,
		rect;

	SIZE
		size;

	TEXTMETRIC
		text_metric;

	char
		buffer[1000];

	if ( debug_log_state )
	{

		x = 0;
		y = 0;

		hdc = GetDC (window_handle);

		GetClientRect (window_handle, &rect);

		SelectObject (hdc, GetStockObject (DEFAULT_GUI_FONT));

		SetTextCharacterExtra ( hdc, 0 );

		GetTextMetrics ( hdc, &text_metric );

		tab_size = 3 * ( text_metric.tmAveCharWidth );

		buffer[0] = 'O';

		GetTextExtentPoint32 (hdc, buffer, 1, &size);

		if ( window_handle == application_debug_log_window )
		{

			md = top_log_monitor;

			number_of_log_lines = (rect.bottom - rect.top) / size.cy;

			if (number_of_log_lines > 1)
			{

				number_of_log_lines --;
			}
			else
			{

				number_of_log_lines = 1;
			}
		}
		else if ( window_handle == application_debug_filtered_log_window )
		{

			md = top_filtered_log_monitor;

			number_of_filtered_log_lines = (rect.bottom - rect.top) / size.cy;

			if (number_of_filtered_log_lines > 1)
			{

				number_of_filtered_log_lines --;
			}
			else
			{

				number_of_filtered_log_lines = 1;
			}
		}
		else
		{

			md = top_watch_monitor;

			number_of_watch_lines = (rect.bottom - rect.top) / size.cy;

			if (number_of_watch_lines > 1)
			{

				number_of_watch_lines --;
			}
			else
			{

				number_of_watch_lines = 1;
			}
		}

		while ( md )
		{

			if ( md->string == NULL )
			{

				buffer[0] = '\0';
			}
			else
			{


				switch ( md->number )
				{

					case 0:
					{

						sprintf ( buffer, md->string );

						break;
					}

					case 1:
					{

						switch ( md->type )
						{

							case MT_INT:
							{

								sprintf ( buffer, md->string, * (int *) md->data );

								break;
							}
							case MT_FLOAT:
							{

								sprintf ( buffer, md->string, * (float *) md->data );

								break;
							}
							case MT_DOUBLE:
							{

								sprintf ( buffer, md->string, * (double *) md->data );

								break;
							}

							case MT_STRING:
							{

								sprintf ( buffer, md->string, (char *) md->data );

								break;
							}

							case MT_STRING_PTR:
							{

								sprintf ( buffer, md->string, *( (char * * ) md->data ) );

								break;
							}
						}

						break;
					}

					case 2:
					{

						switch ( md->type )
						{

							case MT_INT:
							{

								sprintf ( buffer, md->string, * (int *) md->data, * (int *) md->data2 );

								break;
							}

							case MT_FLOAT:
							{

								sprintf ( buffer, md->string, * (float *) md->data, * (float *) md->data2 );

								break;
							}

							case MT_DOUBLE:
							{

								sprintf ( buffer, md->string, * (double *) md->data, * (double *) md->data2 );

								break;
							}

							case MT_STRING:
							{

								sprintf ( buffer, md->string, (char *) md->data, (char *) md->data2 );

								break;
							}

							case MT_STRING_PTR:
							{

								sprintf ( buffer, md->string, *( (char ** ) md->data ), *( ( char ** ) md->data2 ) );

								break;
							}
						}

						break;
					}

					case 3:
					{

						switch ( md->type )
						{

							case MT_INT:
							{

								sprintf ( buffer, md->string, * (int *) md->data, * (int *) md->data2, * (int *) md->data3 );

								break;
							}

							case MT_FLOAT:
							{

								sprintf ( buffer, md->string, * (float *) md->data, * (float *) md->data2, * (float *) md->data3 );

								break;
							}

							case MT_DOUBLE:
							{

								sprintf ( buffer, md->string, * (double *) md->data, * (double *) md->data2, * (double *) md->data3 );

								break;
							}

							case MT_STRING:
							{

								sprintf ( buffer, md->string, (char *) md->data, (char *) md->data2, (char *) md->data3 );

								break;
							}

							case MT_STRING_PTR:
							{

								sprintf ( buffer, md->string, *( (char ** ) md->data ), *( ( char ** ) md->data2 ), *( ( char ** ) md->data3 ) );

								break;
							}
						}


						break;
					}

					case 4:
					{

						switch ( md->type )
						{

							case MT_INT:
							{

								sprintf ( buffer, md->string, * (int *) md->data, * (int *) md->data2, * (int *) md->data3, * (int *) md->data4 );

								break;
							}

							case MT_FLOAT:
							{

								sprintf ( buffer, md->string, * (float *) md->data, * (float *) md->data2, * (float *) md->data3, * (float *) md->data4 );

								break;
							}

							case MT_DOUBLE:
							{

								sprintf ( buffer, md->string, * (double *) md->data, * (double *) md->data2, * (double *) md->data3, * (double *) md->data4 );

								break;
							}

							case MT_STRING:
							{

								sprintf ( buffer, md->string, (char *) md->data, (char *) md->data2, (char *) md->data3, (char *) md->data4 );

								break;
							}

							case MT_STRING_PTR:
							{

								sprintf ( buffer, md->string, *( (char ** ) md->data ), *( ( char ** ) md->data2 ), *( ( char ** ) md->data3 ), *( ( char ** ) md->data4 ) );

								break;
							}
						}

						break;
					}

				}
			}

			SetTextColor ( hdc, md->colour );

			TabbedTextOut
			(
				hdc,
				x,
				y,
				buffer,
				strlen (buffer),
				1,
				&tab_size,
				0
			);

			tsize = GetTabbedTextExtent ( hdc, buffer, strlen (buffer), 1, &tab_size );

	//		GetTextExtentPoint32 ( hdc, buffer, strlen (buffer), &size );

			rest.top = y;
			rest.bottom = y + ( tsize >> 16 );	//size.cy;
			rest.left = x + ( tsize & 0xffff );	//size.cx;
			rest.right = rect.right - rect.left;

			FillRect ( hdc, &rest, (HBRUSH) GetStockObject (WHITE_BRUSH) );

			y += size.cy;

			md = md->succ;
		}

		rest.top = y;
		rest.bottom = rect.bottom - rect.top;
		rest.left = 0;
		rest.right = rect.right - rect.left;

		FillRect ( hdc, &rest, (HBRUSH) GetStockObject (WHITE_BRUSH) );

		ReleaseDC ( window_handle, hdc );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static long WINAPI debug_window_notify ( HWND window_handle, UINT message, WPARAM wParam, LPARAM lParam )
{

	PAINTSTRUCT
		ps;

	int
		diff,
		pos;

	switch (message)
	{

		case WM_ERASEBKGND:
		{

			return TRUE;
		}

		case WM_PAINT:
		{

			BeginPaint ( window_handle, &ps );

			update_window ( window_handle );

			EndPaint ( window_handle, &ps );

			break;
		}

		case WM_USER:
		{

			update_window ( window_handle );

			break;
		}

		case WM_VSCROLL:
		{

			pos = GetScrollPos (window_handle, SB_VERT);

			switch (LOWORD (wParam))
			{

				case SB_ENDSCROLL:
				{

					break;
				}

				case SB_LINEDOWN:
				{

					pos ++;

					if ( window_handle == application_debug_log_window )
					{

						if (top_log_monitor->succ)
						{

							top_log_monitor = top_log_monitor->succ;
						}
					}
					else if ( window_handle == application_debug_watch_window )
					{

						if (top_watch_monitor->succ)
						{

							top_watch_monitor = top_watch_monitor->succ;
						}
					}
					else
					{

						if (top_filtered_log_monitor->succ)
						{

							top_filtered_log_monitor = top_filtered_log_monitor->succ;
						}
					}

					break;
				}

				case SB_LINEUP:
				{

					pos --;

					if ( window_handle == application_debug_log_window )
					{

						if ( top_log_monitor->pred )
						{

							top_log_monitor = top_log_monitor->pred;
						}
					}
					else if ( window_handle == application_debug_watch_window )
					{

						if ( top_watch_monitor->pred )
						{

							top_watch_monitor = top_watch_monitor->pred;
						}
					}
					else
					{

						if ( top_filtered_log_monitor->pred )
						{

							top_filtered_log_monitor = top_filtered_log_monitor->pred;
						}
					}

					break;
				}

				case SB_PAGEDOWN:
				{

					if ( window_handle == application_debug_log_window )
					{

						diff = number_of_log_lines;

						while ( diff )
						{

							if ( top_log_monitor->succ )
							{

								top_log_monitor = top_log_monitor->succ;
							}

							diff --;
							pos ++;
						}
					}
					else if ( window_handle == application_debug_watch_window )
					{

						diff = number_of_watch_lines;

						while ( diff )
						{

							if ( top_watch_monitor->succ )
							{

								top_watch_monitor = top_watch_monitor->succ;
							}

							diff --;
							pos ++;
						}
					}
					else
					{

						diff = number_of_filtered_log_lines;

						while ( diff )
						{

							if ( top_filtered_log_monitor->succ )
							{

								top_filtered_log_monitor = top_filtered_log_monitor->succ;
							}

							diff --;
							pos ++;
						}
					}

					break;
				}

				case SB_PAGEUP:
				{

					if ( window_handle == application_debug_log_window )
					{

						diff = number_of_log_lines;

						while ( diff )
						{

							if ( top_log_monitor->pred )
							{

								top_log_monitor = top_log_monitor->pred;
							}

							diff --;
							pos --;
						}
					}
					else if ( window_handle == application_debug_watch_window )
					{

						diff = number_of_watch_lines;

						while ( diff )
						{

							if (top_watch_monitor->pred)
							{

								top_watch_monitor = top_watch_monitor->pred;
							}

							diff --;
							pos --;
						}
					}
					else
					{

						diff = number_of_filtered_log_lines;

						while ( diff )
						{

							if (top_filtered_log_monitor->pred)
							{

								top_filtered_log_monitor = top_filtered_log_monitor->pred;
							}

							diff --;
							pos --;
						}
					}

					break;
				}
			}

			SetScrollPos (window_handle, SB_VERT, pos, TRUE);

			update_window (window_handle);

			break;
		}


		case WM_DESTROY:
		{

			PostQuitMessage (0);

			break;
		}
	}

	return DefWindowProc (window_handle, message, wParam, lParam);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_debug_windows ( void )
{

#ifdef DEBUG

	if ( !debug_monitor_auto_update )
	{

		SendMessage ( application_debug_log_window, WM_USER, 0, 0 );

		SendMessage ( application_debug_watch_window, WM_USER, 0, 0 );
	}

#endif

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void application_monitor_process_thread ( void )
{

	while ( !bExiting )
	{

		update_window ( application_debug_log_window );

		update_window ( application_debug_watch_window );

		update_window ( application_debug_filtered_log_window );

		Sleep ( 200 );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rename_debug_log_file (const char *new_file_name)
{
	int
		error;

	FILE
		*fp;

	//
	// check everything is ok with new_file_name
	//

	ASSERT (new_file_name);

	ASSERT (strlen (new_file_name) > 0);

	ASSERT (strlen (new_file_name) < 100);

	debug_log ("Renaming debug log file from %s to %s", debug_log_file_name, new_file_name);

	//
	// if new_file_name file exists then delete it to prevent a rename error
	//

	if (file_exist (new_file_name))
	{
		error = unlink (new_file_name);

		if (error != 0)
		{
			debug_log ("Unlink debug log failed (error = %d)", error);
		}
	}

	// if the debug log file does not exist then create it
	//
	// (optimised compilation does not have debug_log only debug_fatal
	// so it's likely that the initial DEBUG.LOG file won't exist yet)

	if (!file_exist (debug_log_file_name))
	{
		fp = fopen (debug_log_file_name, "w");

		if (fp)
		{
			fclose (fp);
		}
		else
		{
			debug_log ("No debug log to rename");
		}
	}

	error = rename (debug_log_file_name, new_file_name);

	if (error != 0)
	{
		debug_log ("Rename debug log failed (error = %d)", error);
	}

	strcpy (debug_log_file_name, new_file_name);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
