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
// NUMBERS ARRAY
// 

void initialise_speech_number_data (void)
{
	speech_array_types
		a = SPEECH_ARRAY_NUMBERS;

	speech_originator_types
		o;

	int
		max_items = NUM_SPEECH_NUMBERS;

	//
	// SYSTEM
	//
	{				
		o = SPEECH_ORIGINATOR_SYSTEM;
	
		initialise_sample_index_array (a, o, max_items);
	}

	//
	// CO PILOT
	//
	{	
		o = SPEECH_ORIGINATOR_CO_PILOT;
		
		initialise_sample_index_array (a, o, max_items);

		initialise_speech_data (a, o, SPEECH_NUMBER_ZERO, 			SOUND_SAMPLE_INDEX_SPEECH_US_CPG_0, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_0);
		initialise_speech_data (a, o, SPEECH_NUMBER_ONE,  			SOUND_SAMPLE_INDEX_SPEECH_US_CPG_01, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_01);
		initialise_speech_data (a, o, SPEECH_NUMBER_TWO, 			SOUND_SAMPLE_INDEX_SPEECH_US_CPG_02, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_02);
		initialise_speech_data (a, o, SPEECH_NUMBER_THREE, 		SOUND_SAMPLE_INDEX_SPEECH_US_CPG_03, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_03);
		initialise_speech_data (a, o, SPEECH_NUMBER_FOUR, 	 		SOUND_SAMPLE_INDEX_SPEECH_US_CPG_04, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_04);
		initialise_speech_data (a, o, SPEECH_NUMBER_FIVE, 			SOUND_SAMPLE_INDEX_SPEECH_US_CPG_05, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_05);
		initialise_speech_data (a, o, SPEECH_NUMBER_SIX, 		 	SOUND_SAMPLE_INDEX_SPEECH_US_CPG_06, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_06);
		initialise_speech_data (a, o, SPEECH_NUMBER_SEVEN, 		SOUND_SAMPLE_INDEX_SPEECH_US_CPG_07, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_07);
		initialise_speech_data (a, o, SPEECH_NUMBER_EIGHT, 	 	SOUND_SAMPLE_INDEX_SPEECH_US_CPG_08, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_08);
		initialise_speech_data (a, o, SPEECH_NUMBER_NINE, 	 		SOUND_SAMPLE_INDEX_SPEECH_US_CPG_09, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_09);
		initialise_speech_data (a, o, SPEECH_NUMBER_ONE_HUNDRED, SOUND_SAMPLE_INDEX_SPEECH_US_CPG_100, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_100);
	}

	//
	// WINGMAN 
	//
	{
		o = SPEECH_ORIGINATOR_WINGMAN1;
		
		initialise_sample_index_array (a, o, max_items);

		#if !DEMO_VERSION

		initialise_speech_data (a, o, SPEECH_NUMBER_ZERO, 			SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN1_0, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN1_0);
		initialise_speech_data (a, o, SPEECH_NUMBER_ONE,  			SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN1_01, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN1_01);
		initialise_speech_data (a, o, SPEECH_NUMBER_TWO, 			SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN1_02, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN1_02);
		initialise_speech_data (a, o, SPEECH_NUMBER_THREE, 		SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN1_03, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN1_03);
		initialise_speech_data (a, o, SPEECH_NUMBER_FOUR, 	 		SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN1_04, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN1_04);
		initialise_speech_data (a, o, SPEECH_NUMBER_FIVE, 			SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN1_05, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN1_05);
		initialise_speech_data (a, o, SPEECH_NUMBER_SIX, 		 	SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN1_06, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN1_06);
		initialise_speech_data (a, o, SPEECH_NUMBER_SEVEN, 		SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN1_07, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN1_07);
		initialise_speech_data (a, o, SPEECH_NUMBER_EIGHT, 	 	SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN1_08, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN1_08);
		initialise_speech_data (a, o, SPEECH_NUMBER_NINE, 	 		SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN1_09, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN1_09);
		initialise_speech_data (a, o, SPEECH_NUMBER_ONE_HUNDRED, SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN1_100, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN1_100);

		#endif
	}

	{
		o = SPEECH_ORIGINATOR_WINGMAN2;
		
		initialise_sample_index_array (a, o, max_items);

		#if !DEMO_VERSION

		initialise_speech_data (a, o, SPEECH_NUMBER_ZERO, 			SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN2_0, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN2_0);
		initialise_speech_data (a, o, SPEECH_NUMBER_ONE,  			SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN2_01, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN2_01);
		initialise_speech_data (a, o, SPEECH_NUMBER_TWO, 			SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN2_02, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN2_02);
		initialise_speech_data (a, o, SPEECH_NUMBER_THREE, 		SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN2_03, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN2_03);
		initialise_speech_data (a, o, SPEECH_NUMBER_FOUR, 	 		SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN2_04, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN2_04);
		initialise_speech_data (a, o, SPEECH_NUMBER_FIVE, 			SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN2_05, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN2_05);
		initialise_speech_data (a, o, SPEECH_NUMBER_SIX, 		 	SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN2_06, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN2_06);
		initialise_speech_data (a, o, SPEECH_NUMBER_SEVEN, 		SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN2_07, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN2_07);
		initialise_speech_data (a, o, SPEECH_NUMBER_EIGHT, 	 	SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN2_08, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN2_08);
		initialise_speech_data (a, o, SPEECH_NUMBER_NINE, 	 		SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN2_09, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN2_09);
		initialise_speech_data (a, o, SPEECH_NUMBER_ONE_HUNDRED, SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN2_100, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN2_100);

		#endif
	}

	//
	// AIR TRAFFIC CONTROLLER
	//
	{	
		o = SPEECH_ORIGINATOR_AIR_TRAFFIC_CONTROLLER;
		
		initialise_sample_index_array (a, o, max_items);

		#if !DEMO_VERSION

		initialise_speech_data (a, o, SPEECH_NUMBER_ZERO, 			SOUND_SAMPLE_INDEX_SPEECH_US_ATC_0, SOUND_SAMPLE_INDEX_SPEECH_CIS_ATC_0);
		initialise_speech_data (a, o, SPEECH_NUMBER_ONE,  			SOUND_SAMPLE_INDEX_SPEECH_US_ATC_01, SOUND_SAMPLE_INDEX_SPEECH_CIS_ATC_01);
		initialise_speech_data (a, o, SPEECH_NUMBER_TWO, 			SOUND_SAMPLE_INDEX_SPEECH_US_ATC_02, SOUND_SAMPLE_INDEX_SPEECH_CIS_ATC_02);
		initialise_speech_data (a, o, SPEECH_NUMBER_THREE, 		SOUND_SAMPLE_INDEX_SPEECH_US_ATC_03, SOUND_SAMPLE_INDEX_SPEECH_CIS_ATC_03);
		initialise_speech_data (a, o, SPEECH_NUMBER_FOUR, 	 		SOUND_SAMPLE_INDEX_SPEECH_US_ATC_04, SOUND_SAMPLE_INDEX_SPEECH_CIS_ATC_04);
		initialise_speech_data (a, o, SPEECH_NUMBER_FIVE, 			SOUND_SAMPLE_INDEX_SPEECH_US_ATC_05, SOUND_SAMPLE_INDEX_SPEECH_CIS_ATC_05);
		initialise_speech_data (a, o, SPEECH_NUMBER_SIX, 		 	SOUND_SAMPLE_INDEX_SPEECH_US_ATC_06, SOUND_SAMPLE_INDEX_SPEECH_CIS_ATC_06);
		initialise_speech_data (a, o, SPEECH_NUMBER_SEVEN, 		SOUND_SAMPLE_INDEX_SPEECH_US_ATC_07, SOUND_SAMPLE_INDEX_SPEECH_CIS_ATC_07);
		initialise_speech_data (a, o, SPEECH_NUMBER_EIGHT, 	 	SOUND_SAMPLE_INDEX_SPEECH_US_ATC_08, SOUND_SAMPLE_INDEX_SPEECH_CIS_ATC_08);
		initialise_speech_data (a, o, SPEECH_NUMBER_NINE, 	 		SOUND_SAMPLE_INDEX_SPEECH_US_ATC_09, SOUND_SAMPLE_INDEX_SPEECH_CIS_ATC_09);
		initialise_speech_data (a, o, SPEECH_NUMBER_ONE_HUNDRED, SOUND_SAMPLE_INDEX_SPEECH_US_ATC_100, SOUND_SAMPLE_INDEX_SPEECH_CIS_ATC_100);

		#endif
	}

	//
	// FORWARD AIR CONTROLLER 
	//
	{	
		o = SPEECH_ORIGINATOR_FORWARD_AIR_CONTROLLER;

		initialise_sample_index_array (a, o, max_items);

		#if !DEMO_VERSION

		initialise_speech_data (a, o, SPEECH_NUMBER_ZERO, 			SOUND_SAMPLE_INDEX_SPEECH_US_FAC_0, SOUND_SAMPLE_INDEX_SPEECH_CIS_FAC_0);
		initialise_speech_data (a, o, SPEECH_NUMBER_ONE,  			SOUND_SAMPLE_INDEX_SPEECH_US_FAC_01, SOUND_SAMPLE_INDEX_SPEECH_CIS_FAC_01);
		initialise_speech_data (a, o, SPEECH_NUMBER_TWO, 			SOUND_SAMPLE_INDEX_SPEECH_US_FAC_02, SOUND_SAMPLE_INDEX_SPEECH_CIS_FAC_02);
		initialise_speech_data (a, o, SPEECH_NUMBER_THREE, 		SOUND_SAMPLE_INDEX_SPEECH_US_FAC_03, SOUND_SAMPLE_INDEX_SPEECH_CIS_FAC_03);
		initialise_speech_data (a, o, SPEECH_NUMBER_FOUR, 	 		SOUND_SAMPLE_INDEX_SPEECH_US_FAC_04, SOUND_SAMPLE_INDEX_SPEECH_CIS_FAC_04);
		initialise_speech_data (a, o, SPEECH_NUMBER_FIVE, 			SOUND_SAMPLE_INDEX_SPEECH_US_FAC_05, SOUND_SAMPLE_INDEX_SPEECH_CIS_FAC_05);
		initialise_speech_data (a, o, SPEECH_NUMBER_SIX, 		 	SOUND_SAMPLE_INDEX_SPEECH_US_FAC_06, SOUND_SAMPLE_INDEX_SPEECH_CIS_FAC_06);
		initialise_speech_data (a, o, SPEECH_NUMBER_SEVEN, 		SOUND_SAMPLE_INDEX_SPEECH_US_FAC_07, SOUND_SAMPLE_INDEX_SPEECH_CIS_FAC_07);
		initialise_speech_data (a, o, SPEECH_NUMBER_EIGHT, 	 	SOUND_SAMPLE_INDEX_SPEECH_US_FAC_08, SOUND_SAMPLE_INDEX_SPEECH_CIS_FAC_08);
		initialise_speech_data (a, o, SPEECH_NUMBER_NINE, 	 		SOUND_SAMPLE_INDEX_SPEECH_US_FAC_09, SOUND_SAMPLE_INDEX_SPEECH_CIS_FAC_09);
		initialise_speech_data (a, o, SPEECH_NUMBER_ONE_HUNDRED, SOUND_SAMPLE_INDEX_SPEECH_US_FAC_100, SOUND_SAMPLE_INDEX_SPEECH_CIS_FAC_100);

		#endif
	}

	//
	// GROUND CONTROLLER
	//
	{	
		o = SPEECH_ORIGINATOR_GROUND_CONTROLLER;
		
		initialise_sample_index_array (a, o, max_items);

		#if !DEMO_VERSION

		initialise_speech_data (a, o, SPEECH_NUMBER_ZERO, 			SOUND_SAMPLE_INDEX_SPEECH_US_GC_0, SOUND_SAMPLE_INDEX_SPEECH_CIS_GC_0);
		initialise_speech_data (a, o, SPEECH_NUMBER_ONE,  			SOUND_SAMPLE_INDEX_SPEECH_US_GC_01, SOUND_SAMPLE_INDEX_SPEECH_CIS_GC_01);
		initialise_speech_data (a, o, SPEECH_NUMBER_TWO, 			SOUND_SAMPLE_INDEX_SPEECH_US_GC_02, SOUND_SAMPLE_INDEX_SPEECH_CIS_GC_02);
		initialise_speech_data (a, o, SPEECH_NUMBER_THREE, 		SOUND_SAMPLE_INDEX_SPEECH_US_GC_03, SOUND_SAMPLE_INDEX_SPEECH_CIS_GC_03);
		initialise_speech_data (a, o, SPEECH_NUMBER_FOUR, 	 		SOUND_SAMPLE_INDEX_SPEECH_US_GC_04, SOUND_SAMPLE_INDEX_SPEECH_CIS_GC_04);
		initialise_speech_data (a, o, SPEECH_NUMBER_FIVE, 			SOUND_SAMPLE_INDEX_SPEECH_US_GC_05, SOUND_SAMPLE_INDEX_SPEECH_CIS_GC_05);
		initialise_speech_data (a, o, SPEECH_NUMBER_SIX, 		 	SOUND_SAMPLE_INDEX_SPEECH_US_GC_06, SOUND_SAMPLE_INDEX_SPEECH_CIS_GC_06);
		initialise_speech_data (a, o, SPEECH_NUMBER_SEVEN, 		SOUND_SAMPLE_INDEX_SPEECH_US_GC_07, SOUND_SAMPLE_INDEX_SPEECH_CIS_GC_07);
		initialise_speech_data (a, o, SPEECH_NUMBER_EIGHT, 	 	SOUND_SAMPLE_INDEX_SPEECH_US_GC_08, SOUND_SAMPLE_INDEX_SPEECH_CIS_GC_08);
		initialise_speech_data (a, o, SPEECH_NUMBER_NINE, 	 		SOUND_SAMPLE_INDEX_SPEECH_US_GC_09, SOUND_SAMPLE_INDEX_SPEECH_CIS_GC_09);
		initialise_speech_data (a, o, SPEECH_NUMBER_ONE_HUNDRED, SOUND_SAMPLE_INDEX_SPEECH_US_GC_100, SOUND_SAMPLE_INDEX_SPEECH_CIS_GC_100);

		#endif
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

