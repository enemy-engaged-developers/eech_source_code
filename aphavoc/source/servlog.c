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

void get_clock_int_values (int time_of_day, int *hours, int *minutes, int *seconds);	// Retro 30Jan2004 fwd declaration
// Jabberwock 031119 Server log

void server_log (const char *msg, ...)
{

	FILE
		*fp = nullptr;
		
	int
		hours,
		minutes,
		seconds;
	

	static char
		buffer[1000];

	char
		buffer2[1000];

	va_list
		args;

	va_start (args, msg);

	vsprintf (buffer2, msg, args);
	
	if ( strcmp (buffer2, "separator") != 0 )
	{
		get_clock_int_values (get_system_time_of_day (), &hours, &minutes, &seconds);
	
		sprintf (buffer, "%02d:%02d:%02d : ", hours, minutes, seconds);
		
		strcat (buffer, buffer2);
	}
	else
	{
		sprintf (buffer, "%s", "----------------------------------------------------------");
	}

	va_end (args);

	if (!(strcmp (command_line_server_log_filename, "/0") == 0) &&
		!(strcmp (command_line_server_log_filename, "") == 0))
	{
		fp = fopen (command_line_server_log_filename, "a" );

		if ( fp )
		{

			fwrite ( buffer, 1, strlen ( buffer ), fp );

			fwrite ( "\n", 1, 1, fp );

			fclose ( fp );
		}
	}
}

void get_clock_int_values (int time_of_day, int *hours, int *minutes, int *seconds)
{
	int
		minutes_past_midnight,
		hours_past_midnight;

//	time_of_day = bound (time_of_day, 0.0, ONE_DAY - 1.0);

	hours_past_midnight = time_of_day / (60 * 60);

	minutes_past_midnight = time_of_day / 60;

	*hours = hours_past_midnight;

	*minutes = (minutes_past_midnight - (hours_past_midnight * 60));

	*seconds = (time_of_day - (minutes_past_midnight * 60));
}

// Jabberwock 031119 ends
