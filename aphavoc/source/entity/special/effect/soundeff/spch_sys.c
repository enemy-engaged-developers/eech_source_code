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
// SYSTEM MESSAGES ARRAY
// 

void initialise_speech_system_data (void)
{
	speech_array_types
		a = SPEECH_ARRAY_SYSTEM_MESSAGES;

	speech_originator_types
		o;

	int
		max_items = NUM_SPEECH_SYSTEM_MESSAGES;

	//
	// SYSTEM
	//
	{	
		o = SPEECH_ORIGINATOR_SYSTEM;
		
		initialise_sample_index_array (a, o, max_items);

		initialise_speech_data (a, o, SPEECH_SYSTEM_RADAR_FAILURE, 								SOUND_SAMPLE_INDEX_SPEECH_US_SYSTEM_WARN_01, SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_01);
		initialise_speech_data (a, o, SPEECH_SYSTEM_FLIR_FAILURE, 								SOUND_SAMPLE_INDEX_SPEECH_US_SYSTEM_WARN_02, SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_02);
		initialise_speech_data (a, o, SPEECH_SYSTEM_DTV_FAILURE, 								SOUND_SAMPLE_INDEX_SPEECH_US_SYSTEM_WARN_03, SOUND_SAMPLE_INDEX_NONE);
		initialise_speech_data (a, o, SPEECH_SYSTEM_LLLTV_FAILURE, 								SOUND_SAMPLE_INDEX_NONE, 							SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_04);
		initialise_speech_data (a, o, SPEECH_SYSTEM_DVO_FAILURE, 								SOUND_SAMPLE_INDEX_SPEECH_US_SYSTEM_WARN_05, SOUND_SAMPLE_INDEX_NONE);
		initialise_speech_data (a, o, SPEECH_SYSTEM_PERISCOPE_DAMAGED, 						SOUND_SAMPLE_INDEX_NONE, 							SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_06);
		initialise_speech_data (a, o, SPEECH_SYSTEM_LASER_DESIGNATOR_FAILURE, 				SOUND_SAMPLE_INDEX_SPEECH_US_SYSTEM_WARN_07, SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_07);
		initialise_speech_data (a, o, SPEECH_SYSTEM_LASER_RANGE_FINDER_FAILURE, 			SOUND_SAMPLE_INDEX_SPEECH_US_SYSTEM_WARN_08, SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_08);
		initialise_speech_data (a, o, SPEECH_SYSTEM_RADAR_JAMMER_FAILURE, 					SOUND_SAMPLE_INDEX_SPEECH_US_SYSTEM_WARN_09, SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_09);
		initialise_speech_data (a, o, SPEECH_SYSTEM_IR_JAMMER_FAILURE, 						SOUND_SAMPLE_INDEX_SPEECH_US_SYSTEM_WARN_10, SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_10);
		initialise_speech_data (a, o, SPEECH_SYSTEM_NAV_COMPUTER_FAILURE, 					SOUND_SAMPLE_INDEX_SPEECH_US_SYSTEM_WARN_11, SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_11);
		initialise_speech_data (a, o, SPEECH_SYSTEM_COMMS_FAILURE, 								SOUND_SAMPLE_INDEX_SPEECH_US_SYSTEM_WARN_12, SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_12);
		initialise_speech_data (a, o, SPEECH_SYSTEM_RADAR_WARNING_FAILURE, 					SOUND_SAMPLE_INDEX_SPEECH_US_SYSTEM_WARN_13, SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_13);
		initialise_speech_data (a, o, SPEECH_SYSTEM_IHADSS_FAILURE, 							SOUND_SAMPLE_INDEX_SPEECH_US_SYSTEM_WARN_14, SOUND_SAMPLE_INDEX_NONE);
		initialise_speech_data (a, o, SPEECH_SYSTEM_HIDSS_FAILURE, 								SOUND_SAMPLE_INDEX_SPEECH_US_SYSTEM_WARN_15, SOUND_SAMPLE_INDEX_NONE);
		initialise_speech_data (a, o, SPEECH_SYSTEM_HUD_FAILURE, 								SOUND_SAMPLE_INDEX_NONE, 							SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_16);
		initialise_speech_data (a, o, SPEECH_SYSTEM_HELMET_MOUNTED_SIGHT_FAILURE, 			SOUND_SAMPLE_INDEX_NONE, 							SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_17);
		initialise_speech_data (a, o, SPEECH_SYSTEM_MFD_FAILURE, 								SOUND_SAMPLE_INDEX_SPEECH_US_SYSTEM_WARN_18, SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_18);
//		initialise_speech_data (a, o, SPEECH_SYSTEM_DISPLAY_FAILURE, 							SOUND_SAMPLE_INDEX_SPEECH_US_SYSTEM_WARN_19, SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_19);
		initialise_speech_data (a, o, SPEECH_SYSTEM_TV_DISPLAY_FAILURE, 						SOUND_SAMPLE_INDEX_NONE, 							SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_20);
		initialise_speech_data (a, o, SPEECH_SYSTEM_THREAT_WARNING_DISPLAY_FAILURE, 		SOUND_SAMPLE_INDEX_NONE, 							SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_21);
		initialise_speech_data (a, o, SPEECH_SYSTEM_PNVS_FAILURE, 								SOUND_SAMPLE_INDEX_SPEECH_US_SYSTEM_WARN_22, SOUND_SAMPLE_INDEX_NONE);
		initialise_speech_data (a, o, SPEECH_SYSTEM_NIGHT_VISION_GOGGLES_FAILURE, 			SOUND_SAMPLE_INDEX_NONE, 							SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_23);
		initialise_speech_data (a, o, SPEECH_SYSTEM_GUN_JAMMED, 									SOUND_SAMPLE_INDEX_SPEECH_US_SYSTEM_WARN_24, SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_24);
		initialise_speech_data (a, o, SPEECH_SYSTEM_HARDPOINT_DAMAGED, 						SOUND_SAMPLE_INDEX_SPEECH_US_SYSTEM_WARN_25, SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_25);
		initialise_speech_data (a, o, SPEECH_SYSTEM_CHAFF_DISPENSER_DAMAGED, 				SOUND_SAMPLE_INDEX_SPEECH_US_SYSTEM_WARN_26, SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_26);
		initialise_speech_data (a, o, SPEECH_SYSTEM_FLARE_DISPENSER_DAMAGED, 				SOUND_SAMPLE_INDEX_SPEECH_US_SYSTEM_WARN_27, SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_27);
		initialise_speech_data (a, o, SPEECH_SYSTEM_MAIN_ROTOR_DAMAGED, 						SOUND_SAMPLE_INDEX_SPEECH_US_SYSTEM_WARN_28, SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_28);
		initialise_speech_data (a, o, SPEECH_SYSTEM_TAIL_ROTOR_DAMAGED, 						SOUND_SAMPLE_INDEX_SPEECH_US_SYSTEM_WARN_29, SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_29);
		initialise_speech_data (a, o, SPEECH_SYSTEM_LEFT_ENGINE_FAILURE, 						SOUND_SAMPLE_INDEX_SPEECH_US_SYSTEM_WARN_30, SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_30);
		initialise_speech_data (a, o, SPEECH_SYSTEM_RIGHT_ENGINE_FAILURE, 					SOUND_SAMPLE_INDEX_SPEECH_US_SYSTEM_WARN_31, SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_31);
		initialise_speech_data (a, o, SPEECH_SYSTEM_LEFT_ENGINE_FIRE, 							SOUND_SAMPLE_INDEX_SPEECH_US_SYSTEM_WARN_32, SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_32);
		initialise_speech_data (a, o, SPEECH_SYSTEM_RIGHT_ENGINE_FIRE, 						SOUND_SAMPLE_INDEX_SPEECH_US_SYSTEM_WARN_33, SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_33);
		initialise_speech_data (a, o, SPEECH_SYSTEM_HYDRAULIC_PRESSURE_FAILURE, 			SOUND_SAMPLE_INDEX_SPEECH_US_SYSTEM_WARN_34, SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_34);
		initialise_speech_data (a, o, SPEECH_SYSTEM_STABILISER_DAMAGED, 						SOUND_SAMPLE_INDEX_SPEECH_US_SYSTEM_WARN_35, SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_35);
		initialise_speech_data (a, o, SPEECH_SYSTEM_FUEL_LEAK, 									SOUND_SAMPLE_INDEX_SPEECH_US_SYSTEM_WARN_36, SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_36);
		initialise_speech_data (a, o, SPEECH_SYSTEM_LOW_ENGINE_OIL_PRESSURE, 				SOUND_SAMPLE_INDEX_SPEECH_US_SYSTEM_WARN_37, SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_37);
		initialise_speech_data (a, o, SPEECH_SYSTEM_HIGH_ENGINE_OIL_TEMPERATURE, 			SOUND_SAMPLE_INDEX_SPEECH_US_SYSTEM_WARN_38, SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_38);
		initialise_speech_data (a, o, SPEECH_SYSTEM_GEAR_DAMAGED, 								SOUND_SAMPLE_INDEX_SPEECH_US_SYSTEM_WARN_39, SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_39);
		initialise_speech_data (a, o, SPEECH_SYSTEM_FUEL_LOW, 									SOUND_SAMPLE_INDEX_SPEECH_US_SYSTEM_WARN_40, SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_40);
		initialise_speech_data (a, o, SPEECH_SYSTEM_ENGINE_OVERTORQUE, 						SOUND_SAMPLE_INDEX_SPEECH_US_SYSTEM_WARN_41, SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_41);
		initialise_speech_data (a, o, SPEECH_SYSTEM_LOW_ROTOR_RPM, 								SOUND_SAMPLE_INDEX_SPEECH_US_SYSTEM_WARN_42, SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_42);
		initialise_speech_data (a, o, SPEECH_SYSTEM_ROTOR_OVERSPEED, 							SOUND_SAMPLE_INDEX_SPEECH_US_SYSTEM_WARN_43, SOUND_SAMPLE_INDEX_SPEECH_CIS_SYSTEM_WARN_43);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

