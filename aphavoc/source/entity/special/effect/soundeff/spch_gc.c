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
//
// GC MESSAGES ARRAY
// 

void initialise_speech_gc_data (void)
{
	speech_array_types
		a = SPEECH_ARRAY_GC_MESSAGES;

	speech_originator_types
		o;

	int
		max_items = NUM_SPEECH_GC_MESSAGES;

	//
	// GROUND CONTROLLER
	//
	{	
		o = SPEECH_ORIGINATOR_GROUND_CONTROLLER;
		
		initialise_sample_index_array (a, o, max_items);

		#if !DEMO_VERSION

		initialise_speech_data (a, o, SPEECH_GC_INTRODUCTION, 							SOUND_SAMPLE_INDEX_SPEECH_US_GC_GC_01, SOUND_SAMPLE_INDEX_SPEECH_CIS_GC_GC_01);
		initialise_speech_data (a, o, SPEECH_GC_REQUEST_SUPPORT_AT, 					SOUND_SAMPLE_INDEX_SPEECH_US_GC_GC_02, SOUND_SAMPLE_INDEX_SPEECH_CIS_GC_GC_02);
		initialise_speech_data (a, o, SPEECH_GC_PINNED_DOWN_AT, 							SOUND_SAMPLE_INDEX_SPEECH_US_GC_GC_03, SOUND_SAMPLE_INDEX_SPEECH_CIS_GC_GC_03);
		initialise_speech_data (a, o, SPEECH_GC_NEED_AIR_SUPPORT_AT, 					SOUND_SAMPLE_INDEX_SPEECH_US_GC_GC_04, SOUND_SAMPLE_INDEX_SPEECH_CIS_GC_GC_04);
		initialise_speech_data (a, o, SPEECH_GC_UNDER_HEAVY_FIRE, 						SOUND_SAMPLE_INDEX_SPEECH_US_GC_GC_05, SOUND_SAMPLE_INDEX_SPEECH_CIS_GC_GC_05);
		initialise_speech_data (a, o, SPEECH_GC_INCOMING_ENEMY_AIRCRAFT_HEADING, 	SOUND_SAMPLE_INDEX_SPEECH_US_GC_GC_06, SOUND_SAMPLE_INDEX_SPEECH_CIS_GC_GC_06);
		initialise_speech_data (a, o, SPEECH_GC_INCOMING_ENEMY_GROUND_UNITS_AT, 	SOUND_SAMPLE_INDEX_SPEECH_US_GC_GC_07, SOUND_SAMPLE_INDEX_SPEECH_CIS_GC_GC_07);
		initialise_speech_data (a, o, SPEECH_GC_ADVANCING_TO, 							SOUND_SAMPLE_INDEX_SPEECH_US_GC_GC_08, SOUND_SAMPLE_INDEX_SPEECH_CIS_GC_GC_08);
		initialise_speech_data (a, o, SPEECH_GC_RETREATING_TO, 							SOUND_SAMPLE_INDEX_SPEECH_US_GC_GC_09, SOUND_SAMPLE_INDEX_SPEECH_CIS_GC_GC_09);
		initialise_speech_data (a, o, SPEECH_GC_FIRE_MISSION_RECEIVED, 				SOUND_SAMPLE_INDEX_SPEECH_US_GC_GC_10, SOUND_SAMPLE_INDEX_SPEECH_CIS_GC_GC_10);
		initialise_speech_data (a, o, SPEECH_GC_ARTILLERY_SHIFTING_POSITION, 		SOUND_SAMPLE_INDEX_SPEECH_US_GC_GC_11, SOUND_SAMPLE_INDEX_SPEECH_CIS_GC_GC_11);
		initialise_speech_data (a, o, SPEECH_GC_ARTILLERY_BUSY, 							SOUND_SAMPLE_INDEX_SPEECH_US_GC_GC_12, SOUND_SAMPLE_INDEX_SPEECH_CIS_GC_GC_12);

		#endif
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

