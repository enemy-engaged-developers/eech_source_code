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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define TIME_10_MILLISECONDS	10

#define TIME_50_MILLISECONDS	50

#define TIME_100_MILLISECONDS	100

#define TIME_500_MILLISECONDS	500

#define TIME_1_SECOND	1000

#define TIME_2_SECOND	(TIME_1_SECOND * 2) 

#define TIME_3_SECOND	(TIME_1_SECOND * 3)

#define TIME_4_SECOND	(TIME_1_SECOND * 4)

#define TIME_5_SECOND	(TIME_1_SECOND * 5)

#define TIME_10_SECOND	(TIME_1_SECOND * 10)

#define TIME_20_SECOND	(TIME_1_SECOND * 20)

#define TIME_30_SECOND	(TIME_1_SECOND * 30)

#define TIME_1_MINUTE	(TIME_1_SECOND * 60)

#define TIME_2_MINUTE	(TIME_1_MINUTE * 2)

#define TIME_3_MINUTE	(TIME_1_MINUTE * 3)

#define TIME_4_MINUTE	(TIME_1_MINUTE * 4)

#define TIME_5_MINUTE	(TIME_1_MINUTE * 5)

#define TIME_10_MINUTE	(TIME_1_MINUTE * 10)

#define TIME_20_MINUTE	(TIME_1_MINUTE * 20)

#define TIME_30_MINUTE	(TIME_1_MINUTE * 30)

#define TIME_1_HOUR		(TIME_1_MINUTE * 60)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern volatile int
	system_ticks;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern int initialise_timers_system ( void );

extern SDL_TimerID create_timer_event ( unsigned int delay, unsigned int resolution, void ( *function ) ( void ) );

extern int destroy_timer_event ( int timer_id );

extern void system_sleep ( int milliseconds );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

