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
// DISTANCES ARRAY
// 

void initialise_speech_distances_data (void)
{
	speech_array_types
		a = SPEECH_ARRAY_DISTANCES;

	speech_originator_types
		o;

	int
		max_items = NUM_SPEECH_DISTANCES;

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

		initialise_speech_data (a, o, SPEECH_DISTANCE_HALF_KILOMETRE, 		SOUND_SAMPLE_INDEX_SPEECH_US_CPG_HALF_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_HALF_CL);
		initialise_speech_data (a, o, SPEECH_DISTANCE_ONE_KILOMETRE, 		SOUND_SAMPLE_INDEX_SPEECH_US_CPG_01_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_01_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_TWO_KILOMETRE, 		SOUND_SAMPLE_INDEX_SPEECH_US_CPG_02_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_02_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_THREE_KILOMETRE, 	SOUND_SAMPLE_INDEX_SPEECH_US_CPG_03_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_03_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_FOUR_KILOMETRE, 		SOUND_SAMPLE_INDEX_SPEECH_US_CPG_04_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_04_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_FIVE_KILOMETRE, 		SOUND_SAMPLE_INDEX_SPEECH_US_CPG_05_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_05_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_SIX_KILOMETRE, 		SOUND_SAMPLE_INDEX_SPEECH_US_CPG_06_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_06_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_SEVEN_KILOMETRE, 	SOUND_SAMPLE_INDEX_SPEECH_US_CPG_07_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_07_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_EIGHT_KILOMETRE, 	SOUND_SAMPLE_INDEX_SPEECH_US_CPG_08_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_08_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_NINE_KILOMETRE, 		SOUND_SAMPLE_INDEX_SPEECH_US_CPG_09_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_09_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_TEN_KILOMETRE, 		SOUND_SAMPLE_INDEX_SPEECH_US_CPG_10_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_10_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_ELEVEN_KILOMETRE, 	SOUND_SAMPLE_INDEX_SPEECH_US_CPG_11_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_11_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_TWELVE_KILOMETRE, 	SOUND_SAMPLE_INDEX_SPEECH_US_CPG_12_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_12_KM);
	}

	//
	// WINGMAN 
	//
	{	
		o = SPEECH_ORIGINATOR_WINGMAN1;
		
		initialise_sample_index_array (a, o, max_items);

		#if !DEMO_VERSION

		initialise_speech_data (a, o, SPEECH_DISTANCE_HALF_KILOMETRE, 		SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN1_HALF_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN1_HALF_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_ONE_KILOMETRE, 		SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN1_01_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN1_01_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_TWO_KILOMETRE, 		SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN1_02_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN1_02_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_THREE_KILOMETRE, 	SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN1_03_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN1_03_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_FOUR_KILOMETRE, 		SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN1_04_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN1_04_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_FIVE_KILOMETRE, 		SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN1_05_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN1_05_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_SIX_KILOMETRE, 		SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN1_06_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN1_06_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_SEVEN_KILOMETRE, 	SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN1_07_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN1_07_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_EIGHT_KILOMETRE, 	SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN1_08_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN1_08_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_NINE_KILOMETRE, 		SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN1_09_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN1_09_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_TEN_KILOMETRE, 		SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN1_10_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN1_10_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_ELEVEN_KILOMETRE, 	SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN1_11_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN1_11_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_TWELVE_KILOMETRE, 	SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN1_12_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN1_12_KM);

		#endif
	}
	
	{

		o = SPEECH_ORIGINATOR_WINGMAN2;
		
		initialise_sample_index_array (a, o, max_items);

		#if !DEMO_VERSION

		initialise_speech_data (a, o, SPEECH_DISTANCE_HALF_KILOMETRE, 		SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN2_HALF_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN2_HALF_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_ONE_KILOMETRE, 		SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN2_01_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN2_01_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_TWO_KILOMETRE, 		SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN2_02_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN2_02_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_THREE_KILOMETRE, 	SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN2_03_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN2_03_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_FOUR_KILOMETRE, 		SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN2_04_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN2_04_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_FIVE_KILOMETRE, 		SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN2_05_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN2_05_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_SIX_KILOMETRE, 		SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN2_06_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN2_06_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_SEVEN_KILOMETRE, 	SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN2_07_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN2_07_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_EIGHT_KILOMETRE, 	SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN2_08_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN2_08_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_NINE_KILOMETRE, 		SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN2_09_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN2_09_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_TEN_KILOMETRE, 		SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN2_10_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN2_10_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_ELEVEN_KILOMETRE, 	SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN2_11_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN2_11_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_TWELVE_KILOMETRE, 	SOUND_SAMPLE_INDEX_SPEECH_US_WINGMAN2_12_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_WINGMAN2_12_KM);

		#endif
	}

	//
	// AIR TRAFFIC CONTROLLER
	//
	{	
		o = SPEECH_ORIGINATOR_AIR_TRAFFIC_CONTROLLER;
		
		initialise_sample_index_array (a, o, max_items);
	}

	//
	// FORWARD AIR CONTROLLER 
	//
	{	
		o = SPEECH_ORIGINATOR_FORWARD_AIR_CONTROLLER;

		initialise_sample_index_array (a, o, max_items);
	}

	//
	// GROUND CONTROLLER
	//
	{	
		o = SPEECH_ORIGINATOR_GROUND_CONTROLLER;
		
		initialise_sample_index_array (a, o, max_items);

		#if !DEMO_VERSION

		initialise_speech_data (a, o, SPEECH_DISTANCE_HALF_KILOMETRE, 		SOUND_SAMPLE_INDEX_SPEECH_US_GC_HALF_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_GC_HALF_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_ONE_KILOMETRE, 		SOUND_SAMPLE_INDEX_SPEECH_US_GC_01_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_GC_01_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_TWO_KILOMETRE, 		SOUND_SAMPLE_INDEX_SPEECH_US_GC_02_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_GC_02_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_THREE_KILOMETRE, 	SOUND_SAMPLE_INDEX_SPEECH_US_GC_03_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_GC_03_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_FOUR_KILOMETRE, 		SOUND_SAMPLE_INDEX_SPEECH_US_GC_04_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_GC_04_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_FIVE_KILOMETRE, 		SOUND_SAMPLE_INDEX_SPEECH_US_GC_05_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_GC_05_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_SIX_KILOMETRE, 		SOUND_SAMPLE_INDEX_SPEECH_US_GC_06_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_GC_06_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_SEVEN_KILOMETRE, 	SOUND_SAMPLE_INDEX_SPEECH_US_GC_07_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_GC_07_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_EIGHT_KILOMETRE, 	SOUND_SAMPLE_INDEX_SPEECH_US_GC_08_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_GC_08_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_NINE_KILOMETRE, 		SOUND_SAMPLE_INDEX_SPEECH_US_GC_09_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_GC_09_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_TEN_KILOMETRE, 		SOUND_SAMPLE_INDEX_SPEECH_US_GC_10_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_GC_10_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_ELEVEN_KILOMETRE, 	SOUND_SAMPLE_INDEX_SPEECH_US_GC_11_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_GC_11_KM);
		initialise_speech_data (a, o, SPEECH_DISTANCE_TWELVE_KILOMETRE, 	SOUND_SAMPLE_INDEX_SPEECH_US_GC_12_CL, SOUND_SAMPLE_INDEX_SPEECH_CIS_GC_12_KM);

		#endif
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

