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

enum mt_type
{

	MT_NONE,
	MT_INT,
	MT_FLOAT,
	MT_DOUBLE,
	MT_STRING,
	MT_STRING_PTR,
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum debug_window_creation
{

	DEBUG_CREATE_INVALID,
	DEBUG_CREATE_NOWINDOW,
	DEBUG_CREATE_WINDOW,
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum debug_update_state
{

	DEBUG_UPDATE_INVALID,
	DEBUG_UPDATE_MANUAL,
	DEBUG_UPDATE_AUTO,
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum DEBUG_COLOURS
{

	DEBUG_COLOUR_BLACK,
	DEBUG_COLOUR_BLUE,
	DEBUG_COLOUR_GREEN,
	DEBUG_COLOUR_CYAN,
	DEBUG_COLOUR_RED,
	DEBUG_COLOUR_MAGENTA,
	DEBUG_COLOUR_YELLOW,
	DEBUG_COLOUR_WHITE,
	DEBUG_COLOUR_SKY_BLUE,
	DEBUG_COLOUR_SLATE_GREY,
	DEBUG_COLOUR_FOREST_GREEN,
	DEBUG_COLOUR_ULTRAMARINE,
	DEBUG_COLOUR_SEABLUE,
	DEBUG_COLOUR_AQUAMARINE,
	DEBUG_COLOUR_GOLD,
	DEBUG_COLOUR_LIGHT_GREY,
	DEBUG_COLOUR_LIGHT_RED,
	DEBUG_COLOUR_DARK_RED,
	DEBUG_COLOUR_DARK_GREEN,
	DEBUG_COLOUR_DARK_BLUE,
	DEBUG_COLOUR_MEDIUM_BLUE,
	DEBUG_COLOUR_MEDIUM_RED,
	DEBUG_COLOUR_SANDY_BROWN,
	DEBUG_COLOUR_AMBER,

	DEBUG_COLOUR_LAST,
};

typedef enum DEBUG_COLOURS debug_colours;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern int
	debug_fatal_warning_tone;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void debug_set_window_creation ( enum debug_window_creation create );

extern void debug_set_windows_update ( enum debug_update_state update );

extern void debug_set_logging ( int logging );

extern void suppress_debug_log_timing_info ( int flag );

extern void initialise_debug_system ( int logging );

extern void debug_fatal ( const char *string, ... );

#ifdef DEBUG

extern void debug_log ( const char *string, ... );

extern void debug_colour_log ( enum DEBUG_COLOURS colour, const char *string, ... );

extern void debug_filtered_log (const char *msg, ...);

extern void debug_colour_filtered_log ( enum DEBUG_COLOURS colour, const char *msg, ...);

extern void debug_watch ( const char *string, enum mt_type type, void *data );

extern void debug_colour_watch ( enum DEBUG_COLOURS colour, const char *string, enum mt_type type, void *data );

extern void debug_watch2 ( const char *string, enum mt_type type, void *data1, void *data2 );

extern void debug_colour_watch2 ( enum DEBUG_COLOURS colour, const char *string, enum mt_type type, void *data1, void *data2 );

extern void debug_watch3 ( const char *string, enum mt_type type, void *data1, void *data2, void *data3 );

extern void debug_colour_watch3 ( enum DEBUG_COLOURS colour, const char *string, enum mt_type type, void *data1, void *data2, void *data3 );

extern void debug_watch4 ( const char *string, enum mt_type type, void *data1, void *data2, void *data3, void *data4 );

extern void debug_colour_watch4 ( enum DEBUG_COLOURS colour, const char *string, enum mt_type type, void *data1, void *data2, void *data3, void *data4 );

extern void update_debug_windows ( void );

#define BREAKOUT(X) DebugBreak(X);

#else

#ifdef WIN32
#define debug_log();
#define debug_colour_log();
#define debug_filtered_log();
#define debug_colour_filtered_log();
#define debug_watch();
#define debug_colour_watch();
#define debug_watch2();
#define debug_colour_watch2();
#define debug_watch3();
#define debug_colour_watch3();
#define debug_watch4();
#define debug_colour_watch4();
#define BREAKOUT();
#else
#define debug_log(a, x...) do { } while(0);
#define debug_colour_log(a, b, x...) do { } while(0);
#define debug_filtered_log(a, x...) do { } while(0);
#define debug_colour_filtered_log(a, b, x...) do { } while(0);
#define debug_watch(a, b, c) do { } while(0);
#define debug_colour_watch(a, b, c, d) do { } while(0);
#define debug_watch2(a, b, c, d) do { } while(0);
#define debug_colour_watch2(a, b, c, d, e) do { } while(0);
#define debug_watch3(a, b, c, d, e) do { } while(0);
#define debug_colour_watch3(a, b, c, d, e, f) do { } while(0);
#define debug_watch4(a, b, c, d, e, f) do { } while(0);
#define debug_colour_watch4(a, b, c, d, e, f, g) do { } while(0);
#define BREAKOUT(a) do { } while(0);
#endif

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* forward declarations for types used below */
struct EVENT;
/*********************************************/

extern void breakout ( struct EVENT *ev );

extern void rename_debug_log_file (const char *new_file_name);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

