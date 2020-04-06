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

////Moje 040411 This file is now obsolete due to a rearrangement of unix-files done by Svanberg
////Moje 040411 New Unix-files are found in a unix subfolder to the modules\system-folder

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "system.h"

// crh 030408 new single global version header
#include "version.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_SYSTEM_MESSAGE_FUNCTIONS 256

#define MAX_USER_MESSAGE_FUNCTIONS 256

#define MAX_EXIT_FUNCTIONS 256

#define INPUT_EVENT_BUFFER_SIZE 16

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void application_main ( int argc, char **argv );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct system_message_struct
{
    int
        parameter;

    long ( * function ) ( void * );
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct user_message_struct
{
    int
        parameter;

    long ( * function ) ( void * );
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct exit_struct
{
    int
        called;

    void ( * function ) ( void );
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SDL_Surface
	*application_window = nullptr;

int
	argc;
char
	**argv;

int
	nCmdShow;

BOOL
	application_active = TRUE,
	bFullScreen = FALSE,                    // Do you need exclusive mode ?
	bExiting = FALSE,
	application_debug_fatal;

Uint32
	application_thread_id = 0,
	system_thread_id = 0;

SDL_Thread
	*application_thread_handle = nullptr;

char
	application_current_directory[1024];

char
	application_debug_fatal_string[256];

SDL_Rect
	application_window_position;

int
	number_system_message_functions = 0,
	number_user_message_functions = 0,
	number_exit_functions = 0;

struct system_message_struct
	system_message_functions[MAX_SYSTEM_MESSAGE_FUNCTIONS];

struct user_message_struct
	user_message_functions[MAX_USER_MESSAGE_FUNCTIONS];

struct exit_struct
	exit_functions[MAX_EXIT_FUNCTIONS];

int
	exit_message_id;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int start_application ( void *data );

BOOL create_application_window ( int nCmdShow );

static void initialise_application_exception_handler ( void );

static void set_application_current_directory ( void );

BOOL register_user_message_function ( int parm, long ( * fn ) ( void * ) );

BOOL register_system_messsage_function ( int parm, long ( * fn ) ( void * ) );

static long call_user_function_routine ( void *data );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static long application_window_proc ( void *data );

static long windows_sizemove_routine ( void *data );

static long windows_keydown_routine ( void *data );

static long windows_cursor_routine ( void *data );

static long windows_close_request_routine ( void *data );

static long windows_paint_routine ( void *data );

static long windows_systemcommand_routine ( void *data );

static long windows_destroy_routine ( void *data );

static long windows_exit_routine ( void *data );

static void do_registered_exits ( void );

// static application_exception_handler ( LPEXCEPTION_POINTERS lpExceptionData );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int m_argc, char **m_argv)
{

	int
		terminated;

	SDL_Event
		*input_events = nullptr;

	argc = m_argc;
	argv = m_argv;

	//
	// Initialise SDL
	//

	atexit(SDL_Quit);

	if( SDL_Init(SDL_INIT_EVERYTHING) != 0 ) {
		debug_fatal("Unable to initialise SDL: %s", SDL_GetError());
		return 1;
	}

	input_events = safe_malloc( sizeof( SDL_Event ) * INPUT_EVENT_BUFFER_SIZE );

	//
	// Install our own exception handler!
	//

	initialise_application_exception_handler ();

	//
	// Set the current directory to where the executable is located
	//

	set_application_current_directory ();

	//
	// Unlink the debug.log file here.
	//

	unlink ( "debug.log" );

	system_thread_id = SDL_ThreadID ();

	application_debug_fatal = FALSE;

	application_active = TRUE;

	//
	// Initialise the memory statistics
	//

	initialise_memory_totals ();

	if ( !initialise_windows ( 1 ) )
	{

		deinitialise_windows ();

		return ( FALSE );
	}

	number_user_message_functions = 0;

	number_system_message_functions = 0;

	// register_system_message_function ( WM_USER, call_user_function_routine );

	// register_system_message_function ( WM_SETCURSOR, windows_cursor_routine );

	register_system_message_function ( SDL_VIDEOEXPOSE, windows_paint_routine  );

	register_system_message_function ( SDL_VIDEORESIZE, windows_sizemove_routine );

	register_system_message_function ( SDL_SYSWMEVENT, windows_systemcommand_routine );

	register_system_message_function ( SDL_QUIT, windows_close_request_routine );

	initialise_cdrom_system ();

	initialise_system_thread_calling_function ();

	exit_message_id = get_unique_message_id ();

	register_user_message_function ( exit_message_id, windows_exit_routine );

	//
	// The graphics / 3d / 2d systems need the maths fpu to round to zero
	//

	set_fpu_rounding_mode_zero ();

	set_fpu_exceptions ();

	initialise_event_system ();

	initialise_timers_system ();

	initialise_file_system ();

	terminated = FALSE;

	application_thread_handle = (SDL_Thread *) SDL_CreateThread ( start_application, NULL );
											  
	application_thread_id = SDL_GetThreadID ( application_thread_handle );

	// SetThreadPriority ( GetCurrentThread (), THREAD_PRIORITY_ABOVE_NORMAL );

	while ( !terminated )
	{

		generate_keyboard_events ();
		generate_mouse_events ();
	}

	free(input_events);

	return ( 0 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_application_current_directory ( void )
{

	char
		*ptr = nullptr;

	getcwd ( application_current_directory, sizeof ( application_current_directory ) );
/*
	ptr = application_current_directory;

	ptr += strlen ( application_current_directory );

	while ( ( *ptr != '\\' ) && ( ptr > application_current_directory ) )
	{

		ptr--;
	}

	if ( *ptr == '\\' )
	{

		*ptr = '\0';

		SetCurrentDirectory ( application_current_directory );
	}
*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
long application_window_proc ( void *data )
{

	int
		count;


	if ( !bExiting )
	{

		for ( count = 0; count < number_system_message_functions; count++ )
		{

			if ( system_message_functions[count].parameter == message )
			{

				if ( !bExiting )
				{

					return ( system_message_functions[count].function ( hWnd, message, wParam, lParam ) );
				}
				else
				{

					return ( FALSE );
				}
			}
		}
	}

	return 0;
}
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_windows ( void )
{

	if ( application_debug_fatal )
	{

		#ifdef COMMERCIAL

		// MessageBox ( application_window, application_debug_fatal_string, "ERROR", MB_OK );
		fprintf(stderr, "ERROR: %s\n", application_debug_fatal_string );

		#else

		// MessageBox ( application_window, application_debug_fatal_string, "DEBUG FATAL", MB_OK );
		fprintf(stderr, "DEBUG FATAL: %s\n", application_debug_fatal_string );

		#endif
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL initialise_windows ( int nCmdShow )
{

    if ( !create_application_window ( nCmdShow ) )
    {

        return ( FALSE );
    }

    return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void end_application ( void )
{

	// SendMessage ( application_window, WM_USER, exit_message_id, 0 );

	// Sleep ( INFINITE );

    exit(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL create_application_window ( int nCmdShow )
{

	char
		application_title[1024];

	//
	// set up and register window class
	//

/*
	wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;	// | CCS_NORESIZE;
	wc.lpfnWndProc = application_window_proc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon ( hInstance, IDI_APPLICATION );
	wc.hCursor = LoadCursor ( NULL, IDC_ARROW );
	wc.hbrBackground = ( HBRUSH ) GetStockObject ( BLACK_BRUSH );
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "HELLO";	//NAME;
*/

	//
	// create a window
	//

	sprintf ( application_title, "%s %s", TITLE, __DATE__ );

	application_window = (SDL_Surface *) SDL_SetVideo ( 640, 480, 32, SDL_OPENGL );

	SDL_WM_SetCaption( application_title, NULL );

	if ( !application_window )
	{

		return ( FALSE );
	}

	return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int start_application ( void *data )
{

	// SetThreadPriority ( GetCurrentThread (), THREAD_PRIORITY_NORMAL );

	//
	// The graphics / 3d / 2d systems need the maths fpu to round to zero
	//

	set_fpu_rounding_mode_zero ();

	set_fpu_exceptions ();

	application_main ( argc, argv );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL register_system_message_function ( int parm, long ( * fn ) ( void *data ) )
{

    int
        count;

    //
    // Check to see if we already have registered this message.
    //

    for ( count=0; count<number_system_message_functions; count++ )
    {

        if ( system_message_functions[count].parameter == parm )
        {

            return ( FALSE );
        }
    }

    //
    // Insert the function into the table
    //

    system_message_functions[number_system_message_functions].parameter = parm;

    system_message_functions[number_system_message_functions].function = fn;

    number_system_message_functions ++;

    return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL register_user_message_function ( int parm, long ( * fn ) ( void * ) )
{

    int
        count;

    //
    // Check to see if we already have registered this message.
    //

    for ( count=0; count<number_user_message_functions; count++ )
    {

        if ( user_message_functions[count].parameter == parm )
        {

            return ( FALSE );
        }
    }

    //
   // Insert the function into the table
    //

    user_message_functions[number_user_message_functions].parameter = parm;

    user_message_functions[number_user_message_functions].function = fn;

    number_user_message_functions ++;

    return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void register_exit_function ( void ( * fn ) ( void ) )
{

    int
        count;

    //
    // Check to see if we already have registered this message.
    //

    for ( count=0; count<number_exit_functions; count++ )
    {

        if ( exit_functions[count].function == fn )
        {

            return;
        }
    }

    //
    // Insert the function into the table
    //

    exit_functions[number_exit_functions].function = fn;

    exit_functions[number_exit_functions].called = FALSE;

    number_exit_functions ++;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

long call_user_function_routine ( void *data )
{

    int
        count;

	SDL_Event *event = (SDL_Event *) data;

    for ( count=0; count<number_user_message_functions; count++ )
    {

        if ( user_message_functions[count].parameter == event->type )
        {

            return ( user_message_functions[count].function ( event ) );
        }
    }



    return ( FALSE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

long windows_sizemove_routine ( void *data )
{
  /*
	GetClientRect ( application_window, &application_window_position );

	ClientToScreen ( application_window, (LPPOINT)&application_window_position );

	ClientToScreen ( application_window, (LPPOINT)&application_window_position+1 );
  */

	return ( FALSE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

long windows_cursor_routine ( void *data )
{
  /*
    SetCursor ( NULL );
  */

    return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

long windows_close_request_routine ( void *data )
{

	//
	// We do not want to let the user ALT-F4 out of the application - so return 0
	//

	return ( 0 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

long windows_paint_routine ( void *data )
{
  /*
	PAINTSTRUCT
		ps;

	BeginPaint ( hWnd, &ps );

	EndPaint ( hWnd, &ps );
  */

	return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

long windows_systemcommand_routine ( void *data )
{
  /*
	LRESULT
		lRc;

	switch ( GET_WM_COMMAND_ID ( wParam, lParam ) )
	{

		case SC_SCREENSAVE:
		{

			return ( 0 );

			break;
		}

		default:
		{

			lRc = DefWindowProc ( application_window, message, wParam, lParam );

			break;
		}
	}
  */

	return ( 0 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

long windows_exit_routine ( void *data )
{

	do_registered_exits ();

	//
	// If we debug_fatal'd we need to display a message box. Now is the time for that
	//

	if ( application_debug_fatal )
	{

		#ifdef COMMERCIAL

		// MessageBox ( application_window, application_debug_fatal_string, "ERROR", MB_OK );
		fprintf(stderr, "ERROR: %s\n", application_debug_fatal_string);

		#else

		// MessageBox ( application_window, application_debug_fatal_string, "DEBUG FATAL", MB_OK );
		fprintf(stderr, "DEBUG FATAL: %s\n", application_debug_fatal_string);

		#endif
	}

	// PostMessage ( application_window, WM_QUIT, 0, 0 );

	// PostQuitMessage ( 0 );

	return ( 0 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void do_registered_exits ( void )
{

	int
		count;

	bExiting = TRUE;

	//
	// In System thread - so disable the user thread.
	//

	// SetThreadPriority ( application_thread_handle, THREAD_PRIORITY_IDLE );

	//
	// Do the registered exit routines
	//

	for ( count = ( number_exit_functions - 1 ); count >= 0; count-- )
	{

		if ( ! exit_functions[count].called )
		{

			//
			// call the exit function
			//

			exit_functions[count].function ();

			exit_functions[count].called = TRUE;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_application_exception_handler ( void )
{
  /*
	SetUnhandledExceptionFilter ( application_exception_handler );
  */
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
struct EXCEPTION_DETAILS
{

	int
		code;

	char
		*reason = nullptr;
};

typedef struct EXCEPTION_DETAILS exception_details;
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
exception_details
	exception_codes[] =
	{

		{ EXCEPTION_ACCESS_VIOLATION,				"Access violation" },
		{ EXCEPTION_ARRAY_BOUNDS_EXCEEDED,		"Array bounds exceeded" },
		{ EXCEPTION_BREAKPOINT,						"Breakpoint" },
		{ EXCEPTION_DATATYPE_MISALIGNMENT,		"Datatype misalignment" },
		{ EXCEPTION_FLT_DENORMAL_OPERAND,		"Float: Denormal operand" },
		{ EXCEPTION_FLT_DIVIDE_BY_ZERO,			"Float: Divide by zero" },
		{ EXCEPTION_FLT_INEXACT_RESULT,			"Float: Inexact result" },
		{ EXCEPTION_FLT_INVALID_OPERATION,		"Float: Invalid operation" },
		{ EXCEPTION_FLT_OVERFLOW,					"Float: Overflow" },
		{ EXCEPTION_FLT_STACK_CHECK,				"Float: Stack check" },
		{ EXCEPTION_FLT_UNDERFLOW,					"Float: Underflow" },
		{ EXCEPTION_ILLEGAL_INSTRUCTION,			"Illegal instruction" },
		{ EXCEPTION_IN_PAGE_ERROR,					"In page error" },
		{ EXCEPTION_INT_DIVIDE_BY_ZERO,			"Integer: Divide by zero" },
		{ EXCEPTION_INT_OVERFLOW,					"Integer: Overflow" },
		{ EXCEPTION_INVALID_DISPOSITION,			"Invalid disposition" },
		{ EXCEPTION_NONCONTINUABLE_EXCEPTION,	"Non-continuable exception" },
		{ EXCEPTION_PRIV_INSTRUCTION,				"Privilaged instruction" },
		{ EXCEPTION_SINGLE_STEP,					"Single step" },
		{ EXCEPTION_STACK_OVERFLOW,				"Stack overflow" },
	};
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
long application_exception_handler ( LPEXCEPTION_POINTERS lpExceptionData )
{

	EXCEPTION_RECORD
		*exception_record = nullptr;

	CONTEXT
		*context_record = nullptr;

	FILE
		*fp = nullptr;

	int
		count;

	DWORD
		*memory = nullptr;

	fp = fopen ( "crash.log", "w" );

	if ( fp )
	{

		fprintf ( fp, "Executable build date: %s\n", __DATE__ );
		fprintf ( fp, "Executable build time: %s\n\n", __TIME__ );

		fprintf ( fp, "Crash details:\n\n" );

		exception_record = lpExceptionData->ExceptionRecord;

		context_record = lpExceptionData->ContextRecord;

		fprintf ( fp, "Location: %08x\n", exception_record->ExceptionAddress );

		for ( count = 0; count < ( sizeof ( exception_codes ) / sizeof ( exception_details ) ); count++ )
		{

			if ( exception_codes[count].code == exception_record->ExceptionCode )
			{

				fprintf ( fp, "Reason: %s\n", exception_codes[count].reason );
			}
		}

		switch ( exception_record->ExceptionCode )
		{

			case EXCEPTION_ACCESS_VIOLATION:
			{

				if ( exception_record->NumberParameters == 2 )
				{

					if ( exception_record->ExceptionInformation[0] == 0 )
					{

						fprintf ( fp, "Tried to read from memory location: 0x%08x", exception_record->ExceptionInformation[1] );
					}
					else
					{

						fprintf ( fp, "Tried to write to memory location: 0x%08x", exception_record->ExceptionInformation[1] );
					}
				}

				break;
			}

			default:
			{

				break;
			}
		}

		fprintf ( fp, "\n\n" );

		fprintf ( fp, "Register dump:\n" );
		fprintf ( fp, "EAX: 0x%08x\n", context_record->Eax );
		fprintf ( fp, "EBX: 0x%08x\n", context_record->Ebx );
		fprintf ( fp, "ECX: 0x%08x\n", context_record->Ecx );
		fprintf ( fp, "EDX: 0x%08x\n", context_record->Edx );
		fprintf ( fp, "EDI: 0x%08x\n", context_record->Edi );
		fprintf ( fp, "ESI: 0x%08x\n", context_record->Esi );
		fprintf ( fp, "EBP: 0x%08x\n", context_record->Ebp );
		fprintf ( fp, "ESP: 0x%08x\n", context_record->Esp );
		fprintf ( fp, "EIP: 0x%08x\n", context_record->Eip );

		fprintf ( fp, "\n\n" );

		fprintf ( fp, "Floating point details:\n" );
		fprintf ( fp, "Control word: 0x%08x\n", context_record->FloatSave.ControlWord );
		fprintf ( fp, "Status word: 0x%08x\n", context_record->FloatSave.StatusWord );

		for ( count = 0; count < 8; count++ )
		{

			fprintf ( fp, "ST(%d): %02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n", count,
											context_record->FloatSave.RegisterArea[count*10 + 0],
											context_record->FloatSave.RegisterArea[count*10 + 1],
											context_record->FloatSave.RegisterArea[count*10 + 2],
											context_record->FloatSave.RegisterArea[count*10 + 3],
											context_record->FloatSave.RegisterArea[count*10 + 4],
											context_record->FloatSave.RegisterArea[count*10 + 5],
											context_record->FloatSave.RegisterArea[count*10 + 6],
											context_record->FloatSave.RegisterArea[count*10 + 7],
											context_record->FloatSave.RegisterArea[count*10 + 8],
											context_record->FloatSave.RegisterArea[count*10 + 9] );
		}

		//
		// If we wanted, we could print out the stack a little but have to check the area first
		//

		fprintf ( fp, "\n\nStack dump:\n" );

		memory = ( DWORD * ) context_record->Esp;

		for ( count = 0; count < 16; count++ )
		{

			if ( !IsBadReadPtr ( memory, 4 ) )
			{

				fprintf ( fp, "%08x\n", *memory );
			}
			else
			{

				fprintf ( fp, "Invalid\n" );
			}

			memory++;
		}

		fflush ( fp );

		fclose ( fp );
	}

	//
	// Let the system clean itself up!
	//

	return ( EXCEPTION_CONTINUE_SEARCH );
}
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

