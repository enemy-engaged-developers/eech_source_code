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
// CPG MESSAGES ARRAY
// 

void initialise_speech_cpg_data (void)
{
	speech_array_types
		a = SPEECH_ARRAY_CPG_MESSAGES;

	speech_originator_types
		o;

	int
		max_items = NUM_SPEECH_CPG_MESSAGES;

	//
	// CO PILOT
	//
	{	
		o = SPEECH_ORIGINATOR_CO_PILOT;
		
		initialise_sample_index_array (a, o, max_items);

		initialise_speech_data (a, o, SPEECH_CPG_AFFIRMATIVE, 								SOUND_SAMPLE_INDEX_SPEECH_US_CPG_SYS_02,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_SYS_02);
		initialise_speech_data (a, o, SPEECH_CPG_NEGATIVE, 									SOUND_SAMPLE_INDEX_SPEECH_US_CPG_SYS_01,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_SYS_01);
		initialise_speech_data (a, o, SPEECH_CPG_GEAR_DOWN, 									SOUND_SAMPLE_INDEX_SPEECH_US_CPG_SYS_03,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_SYS_03);
		initialise_speech_data (a, o, SPEECH_CPG_GEAR_UP, 										SOUND_SAMPLE_INDEX_SPEECH_US_CPG_SYS_04,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_SYS_04);
		initialise_speech_data (a, o, SPEECH_CPG_AUTOPILOT_ON, 								SOUND_SAMPLE_INDEX_SPEECH_US_CPG_SYS_05,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_SYS_05);
		initialise_speech_data (a, o, SPEECH_CPG_AUTOPILOT_OFF, 								SOUND_SAMPLE_INDEX_SPEECH_US_CPG_SYS_06,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_SYS_06);
		initialise_speech_data (a, o, SPEECH_CPG_AUTOPILOT_TOO_LOW1, 						SOUND_SAMPLE_INDEX_SPEECH_US_CPG_SYS_07,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_SYS_07);
		initialise_speech_data (a, o, SPEECH_CPG_AUTOPILOT_TOO_LOW2, 						SOUND_SAMPLE_INDEX_SPEECH_US_CPG_SYS_08,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_SYS_08);
		initialise_speech_data (a, o, SPEECH_CPG_HOVER_HOLD_ON, 								SOUND_SAMPLE_INDEX_SPEECH_US_CPG_SYS_09,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_SYS_09);
		initialise_speech_data (a, o, SPEECH_CPG_HOVER_HOLD_OFF, 							SOUND_SAMPLE_INDEX_SPEECH_US_CPG_SYS_10,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_SYS_10);
		initialise_speech_data (a, o, SPEECH_CPG_HOVER_HOLD_TOO_FAST1, 					SOUND_SAMPLE_INDEX_SPEECH_US_CPG_SYS_11,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_SYS_11);
		initialise_speech_data (a, o, SPEECH_CPG_HOVER_HOLD_TOO_FAST2, 					SOUND_SAMPLE_INDEX_SPEECH_US_CPG_SYS_12,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_SYS_12);
		initialise_speech_data (a, o, SPEECH_CPG_ALTITUDE_HOLD_ON, 							SOUND_SAMPLE_INDEX_SPEECH_US_CPG_SYS_13,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_SYS_13);
		initialise_speech_data (a, o, SPEECH_CPG_ALTITUDE_HOLD_OFF, 						SOUND_SAMPLE_INDEX_SPEECH_US_CPG_SYS_14,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_SYS_14);
		initialise_speech_data (a, o, SPEECH_CPG_RADAR_ON, 									SOUND_SAMPLE_INDEX_SPEECH_US_CPG_SYS_15,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_SYS_15);
		initialise_speech_data (a, o, SPEECH_CPG_RADAR_OFF, 									SOUND_SAMPLE_INDEX_SPEECH_US_CPG_SYS_16,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_SYS_16);
		initialise_speech_data (a, o, SPEECH_CPG_IR_JAMMER_ON, 								SOUND_SAMPLE_INDEX_SPEECH_US_CPG_SYS_17,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_SYS_17);
		initialise_speech_data (a, o, SPEECH_CPG_IR_JAMMER_OFF, 								SOUND_SAMPLE_INDEX_SPEECH_US_CPG_SYS_18,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_SYS_18);
		initialise_speech_data (a, o, SPEECH_CPG_RADAR_JAMMER_ON, 							SOUND_SAMPLE_INDEX_SPEECH_US_CPG_SYS_19,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_SYS_19);
		initialise_speech_data (a, o, SPEECH_CPG_RADAR_JAMMER_OFF, 							SOUND_SAMPLE_INDEX_SPEECH_US_CPG_SYS_20,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_SYS_20);
		initialise_speech_data (a, o, SPEECH_CPG_RADAR_DAMAGED, 								SOUND_SAMPLE_INDEX_SPEECH_US_CPG_SYS_21,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_SYS_21);
		initialise_speech_data (a, o, SPEECH_CPG_FLIR_DAMAGED, 								SOUND_SAMPLE_INDEX_SPEECH_US_CPG_SYS_22,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_SYS_22);
		initialise_speech_data (a, o, SPEECH_CPG_DTV_DAMAGED, 								SOUND_SAMPLE_INDEX_SPEECH_US_CPG_SYS_23,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_SYS_23);
		initialise_speech_data (a, o, SPEECH_CPG_LLLTV_DAMAGED, 								SOUND_SAMPLE_INDEX_SPEECH_US_CPG_SYS_24,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_SYS_24);
		initialise_speech_data (a, o, SPEECH_CPG_DVO_DAMAGED, 								SOUND_SAMPLE_INDEX_SPEECH_US_CPG_SYS_25,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_SYS_25);
		initialise_speech_data (a, o, SPEECH_CPG_PERISCOPE_DAMAGED, 						SOUND_SAMPLE_INDEX_NONE, 						SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_SYS_26);
		initialise_speech_data (a, o, SPEECH_CPG_RADAR_JAMMER_DAMAGED, 					SOUND_SAMPLE_INDEX_SPEECH_US_CPG_SYS_27,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_SYS_27);
		initialise_speech_data (a, o, SPEECH_CPG_IR_JAMMER_DAMAGED, 						SOUND_SAMPLE_INDEX_SPEECH_US_CPG_SYS_28,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_SYS_28);
		initialise_speech_data (a, o, SPEECH_CPG_PNVS_DAMAGED, 								SOUND_SAMPLE_INDEX_SPEECH_US_CPG_SYS_29,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_SYS_29);
		initialise_speech_data (a, o, SPEECH_CPG_NIGHT_VISION_GOGGLES_DAMAGED, 			SOUND_SAMPLE_INDEX_SPEECH_US_CPG_SYS_30,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_SYS_30);
		initialise_speech_data (a, o, SPEECH_CPG_CONTROL_SYSTEMS_DAMAGED, 				SOUND_SAMPLE_INDEX_SPEECH_US_CPG_SYS_31,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_SYS_31);
		initialise_speech_data (a, o, SPEECH_CPG_SWITCHING_TO_CHAINGUN, 					SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_01,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_01);
		initialise_speech_data (a, o, SPEECH_CPG_SWITCHING_TO_CANNON, 						SOUND_SAMPLE_INDEX_NONE, 						SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_02);
		initialise_speech_data (a, o, SPEECH_CPG_SWITCHING_TO_CANNON_PODS, 				SOUND_SAMPLE_INDEX_NONE, 						SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_03);
		initialise_speech_data (a, o, SPEECH_CPG_SWITCHING_TO_STINGERS, 					SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_04,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_04);
		initialise_speech_data (a, o, SPEECH_CPG_SWITCHING_TO_IGLA, 						SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_05,	SOUND_SAMPLE_INDEX_NONE);
		initialise_speech_data (a, o, SPEECH_CPG_SWITCHING_TO_HELLFIRES, 					SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_06,	SOUND_SAMPLE_INDEX_NONE);
		initialise_speech_data (a, o, SPEECH_CPG_SWITCHING_TO_ATAKA, 						SOUND_SAMPLE_INDEX_NONE, 						SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_07);
		initialise_speech_data (a, o, SPEECH_CPG_SWITCHING_TO_VIKHR, 						SOUND_SAMPLE_INDEX_NONE, 						SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_08);
		initialise_speech_data (a, o, SPEECH_CPG_SWITCHING_TO_ROCKETS, 					SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_09,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_09);
		initialise_speech_data (a, o, SPEECH_CPG_SELECTING_CHAINGUN, 						SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_10,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_10);
		initialise_speech_data (a, o, SPEECH_CPG_SELECTING_CANNON, 							SOUND_SAMPLE_INDEX_NONE, 						SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_11);
		initialise_speech_data (a, o, SPEECH_CPG_SELECTING_CANNON_PODS, 					SOUND_SAMPLE_INDEX_NONE, 						SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_12);
		initialise_speech_data (a, o, SPEECH_CPG_SELECTING_STINGERS, 						SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_13,	SOUND_SAMPLE_INDEX_NONE);
		initialise_speech_data (a, o, SPEECH_CPG_SELECTING_IGLA, 							SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_14,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_14);
		initialise_speech_data (a, o, SPEECH_CPG_SELECTING_HELLFIRES, 						SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_15,	SOUND_SAMPLE_INDEX_NONE);
		initialise_speech_data (a, o, SPEECH_CPG_SELECTING_ATAKA, 							SOUND_SAMPLE_INDEX_NONE, 						SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_16);
		initialise_speech_data (a, o, SPEECH_CPG_SELECTING_VIKHR, 							SOUND_SAMPLE_INDEX_NONE, 						SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_17);
		initialise_speech_data (a, o, SPEECH_CPG_SELECTING_ROCKETS, 						SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_18,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_18);
		initialise_speech_data (a, o, SPEECH_CPG_FIRING_CHAINGUN, 							SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_20,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_20);
		initialise_speech_data (a, o, SPEECH_CPG_FIRING_CANNON, 								SOUND_SAMPLE_INDEX_NONE, 						SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_19);
		initialise_speech_data (a, o, SPEECH_CPG_FIRING_ROCKETS, 							SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_23,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_23);
		initialise_speech_data (a, o, SPEECH_CPG_FIRING_STINGER, 							SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_21,	SOUND_SAMPLE_INDEX_NONE);
		initialise_speech_data (a, o, SPEECH_CPG_FIRING_HELLFIRE, 							SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_22,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_22);
		initialise_speech_data (a, o, SPEECH_CPG_FIRING_IGLA, 								SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_26,	SOUND_SAMPLE_INDEX_NONE);
		initialise_speech_data (a, o, SPEECH_CPG_FIRING_ATAKA, 								SOUND_SAMPLE_INDEX_NONE, 						SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_27);
		initialise_speech_data (a, o, SPEECH_CPG_FIRING_VIKHR, 								SOUND_SAMPLE_INDEX_NONE, 						SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_28);
		initialise_speech_data (a, o, SPEECH_CPG_ENGAGING_WITH_CHAINGUN, 					SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_27,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_27);
		initialise_speech_data (a, o, SPEECH_CPG_ENGAGING_WITH_CANNON, 					SOUND_SAMPLE_INDEX_NONE, 						SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_24);
		initialise_speech_data (a, o, SPEECH_CPG_ENGAGING_WITH_ROCKETS, 					SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_29,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_29);
		initialise_speech_data (a, o, SPEECH_CPG_CANNON_LOW, 									SOUND_SAMPLE_INDEX_NONE, 						SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_30);
		initialise_speech_data (a, o, SPEECH_CPG_ROCKETS_LOW, 								SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_31,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_31);
		initialise_speech_data (a, o, SPEECH_CPG_HELLFIRES_LOW, 								SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_34,	SOUND_SAMPLE_INDEX_NONE);
		initialise_speech_data (a, o, SPEECH_CPG_STINGERS_LOW, 								SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_32,	SOUND_SAMPLE_INDEX_NONE);
		initialise_speech_data (a, o, SPEECH_CPG_IGLAS_LOW, 									SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_33,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_33);
		initialise_speech_data (a, o, SPEECH_CPG_VIKHRS_LOW, 									SOUND_SAMPLE_INDEX_NONE, 						SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_36);
		initialise_speech_data (a, o, SPEECH_CPG_ATAKAS_LOW, 									SOUND_SAMPLE_INDEX_NONE, 						SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_35);
		initialise_speech_data (a, o, SPEECH_CPG_CHAFF_LOW, 									SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_37,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_37);
		initialise_speech_data (a, o, SPEECH_CPG_FLARES_LOW, 									SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_38,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_38);
		initialise_speech_data (a, o, SPEECH_CPG_CANNON_OUT, 									SOUND_SAMPLE_INDEX_NONE, 						SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_39);
		initialise_speech_data (a, o, SPEECH_CPG_ROCKETS_OUT, 								SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_40,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_40);
		initialise_speech_data (a, o, SPEECH_CPG_HELLFIRES_OUT, 								SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_43,	SOUND_SAMPLE_INDEX_NONE);
		initialise_speech_data (a, o, SPEECH_CPG_STINGERS_OUT, 								SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_41,	SOUND_SAMPLE_INDEX_NONE);
		initialise_speech_data (a, o, SPEECH_CPG_IGLAS_OUT, 									SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_42,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_42);
		initialise_speech_data (a, o, SPEECH_CPG_VIKHRS_OUT, 									SOUND_SAMPLE_INDEX_NONE, 						SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_45);
		initialise_speech_data (a, o, SPEECH_CPG_ATAKAS_OUT, 									SOUND_SAMPLE_INDEX_NONE, 						SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_44);
		initialise_speech_data (a, o, SPEECH_CPG_CHAFF_OUT, 									SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_46,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_46);
		initialise_speech_data (a, o, SPEECH_CPG_FLARES_OUT, 									SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_47,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_47);
		initialise_speech_data (a, o, SPEECH_CPG_NO_TARGETING_SYSTEM, 						SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_48,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_48);
		initialise_speech_data (a, o, SPEECH_CPG_NO_TARGET, 									SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_50,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_50);
		initialise_speech_data (a, o, SPEECH_CPG_NO_WEAPON, 									SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_49,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_49);
		initialise_speech_data (a, o, SPEECH_CPG_INVALID_TARGET, 							SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_51,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_51);
		initialise_speech_data (a, o, SPEECH_CPG_TARGET_OUTSIDE_SEEKER_LIMIT, 			SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_52,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_52);
		initialise_speech_data (a, o, SPEECH_CPG_NO_LOS, 										SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_53,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_53);
		initialise_speech_data (a, o, SPEECH_CPG_TARGET_OUT_OF_RANGE, 						SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_54,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_54);
		initialise_speech_data (a, o, SPEECH_CPG_GOOD_TONE, 									SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_55,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_55);
		initialise_speech_data (a, o, SPEECH_CPG_TALLY_SPOT_ENGAGING, 						SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_56,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_56);
		initialise_speech_data (a, o, SPEECH_CPG_TARGET_LASED_WEAPONS_HOT, 				SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_57,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_57);
		initialise_speech_data (a, o, SPEECH_CPG_EXECUTE_SPOT, 								SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_58,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_58);
		initialise_speech_data (a, o, SPEECH_CPG_SPOT_ON, 										SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_59,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_59);
		initialise_speech_data (a, o, SPEECH_CPG_SWITCHING_TO_LOAL, 						SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_60,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_60);
		initialise_speech_data (a, o, SPEECH_CPG_SWITCHING_TO_LOBL, 						SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_61,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_61);
		initialise_speech_data (a, o, SPEECH_CPG_FRIENDLY_FIRE1, 							SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_62,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_62);
		initialise_speech_data (a, o, SPEECH_CPG_FRIENDLY_FIRE2, 							SOUND_SAMPLE_INDEX_SPEECH_US_CPG_WEP_63,	SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_WEP_63);


		initialise_speech_data (a, o, SPEECH_CPG_APPROACHING_ENGAGEMENT_AREA, 			SOUND_SAMPLE_INDEX_SPEECH_US_CPG_AWARE_01, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_AWARE_01);
		initialise_speech_data (a, o, SPEECH_CPG_APPROACHING_BATTLE_POSITION, 			SOUND_SAMPLE_INDEX_SPEECH_US_CPG_AWARE_02, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_AWARE_02);
		initialise_speech_data (a, o, SPEECH_CPG_APPROACHING_RP, 							SOUND_SAMPLE_INDEX_SPEECH_US_CPG_AWARE_03, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_AWARE_03);
		initialise_speech_data (a, o, SPEECH_CPG_OBJECTIVE_IN_RANGE_RECON, 				SOUND_SAMPLE_INDEX_SPEECH_US_CPG_AWARE_04, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_AWARE_04);
		initialise_speech_data (a, o, SPEECH_CPG_TRANSMITTING_RECON, 						SOUND_SAMPLE_INDEX_SPEECH_US_CPG_AWARE_05, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_AWARE_05);
		initialise_speech_data (a, o, SPEECH_CPG_MISSION_COMPLETED1, 						SOUND_SAMPLE_INDEX_SPEECH_US_CPG_AWARE_06, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_AWARE_06);
		initialise_speech_data (a, o, SPEECH_CPG_MISSION_COMPLETED2, 						SOUND_SAMPLE_INDEX_SPEECH_US_CPG_AWARE_07, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_AWARE_07);
		initialise_speech_data (a, o, SPEECH_CPG_ON_FINALS_CHECK_GEAR, 					SOUND_SAMPLE_INDEX_SPEECH_US_CPG_AWARE_08, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_AWARE_08);
		initialise_speech_data (a, o, SPEECH_CPG_PRIMARY_TARGET, 							SOUND_SAMPLE_INDEX_SPEECH_US_CPG_AWARE_09, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_AWARE_09);
		initialise_speech_data (a, o, SPEECH_CPG_MISSION_OBJECTIVE, 						SOUND_SAMPLE_INDEX_SPEECH_US_CPG_AWARE_10, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_AWARE_10);
		initialise_speech_data (a, o, SPEECH_CPG_INCOMING, 									SOUND_SAMPLE_INDEX_SPEECH_US_CPG_AWARE_11, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_AWARE_11);
		initialise_speech_data (a, o, SPEECH_CPG_INCOMING_MISSILE, 							SOUND_SAMPLE_INDEX_SPEECH_US_CPG_AWARE_12, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_AWARE_12);
		initialise_speech_data (a, o, SPEECH_CPG_RECEIVING_SMALL_ARMS_FIRE, 				SOUND_SAMPLE_INDEX_SPEECH_US_CPG_AWARE_13, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_AWARE_13);
		initialise_speech_data (a, o, SPEECH_CPG_TARGET_HIT, 									SOUND_SAMPLE_INDEX_SPEECH_US_CPG_AWARE_14, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_AWARE_14);
		initialise_speech_data (a, o, SPEECH_CPG_TARGET_MISSED, 								SOUND_SAMPLE_INDEX_SPEECH_US_CPG_AWARE_15, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_AWARE_15);
		initialise_speech_data (a, o, SPEECH_CPG_TARGET_DESTROYED, 							SOUND_SAMPLE_INDEX_SPEECH_US_CPG_AWARE_16, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_AWARE_16);
		initialise_speech_data (a, o, SPEECH_CPG_TARGET_IS_DOWN, 							SOUND_SAMPLE_INDEX_SPEECH_US_CPG_AWARE_17, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_AWARE_17);
		initialise_speech_data (a, o, SPEECH_CPG_KILL_CONFIRMED, 							SOUND_SAMPLE_INDEX_SPEECH_US_CPG_AWARE_18, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_AWARE_18);
		initialise_speech_data (a, o, SPEECH_CPG_GOOD_KILL, 									SOUND_SAMPLE_INDEX_SPEECH_US_CPG_AWARE_19, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_AWARE_19);
		initialise_speech_data (a, o, SPEECH_CPG_ENEMY, 										SOUND_SAMPLE_INDEX_SPEECH_US_CPG_AWARE_20, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_AWARE_20);
		initialise_speech_data (a, o, SPEECH_CPG_FRIENDLY, 									SOUND_SAMPLE_INDEX_SPEECH_US_CPG_AWARE_21, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_AWARE_21);
		initialise_speech_data (a, o, SPEECH_CPG_CHOPPERS, 									SOUND_SAMPLE_INDEX_SPEECH_US_CPG_AWARE_22, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_AWARE_22);
		initialise_speech_data (a, o, SPEECH_CPG_FAST_MOVERS, 								SOUND_SAMPLE_INDEX_SPEECH_US_CPG_AWARE_23, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_AWARE_23);
		initialise_speech_data (a, o, SPEECH_CPG_CARGO_BIRD, 									SOUND_SAMPLE_INDEX_SPEECH_US_CPG_AWARE_24, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_AWARE_24);
		initialise_speech_data (a, o, SPEECH_CPG_HEAVY_METAL, 								SOUND_SAMPLE_INDEX_SPEECH_US_CPG_AWARE_25, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_AWARE_25);
		initialise_speech_data (a, o, SPEECH_CPG_TANKS, 										SOUND_SAMPLE_INDEX_SPEECH_US_CPG_AWARE_26, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_AWARE_26);
		initialise_speech_data (a, o, SPEECH_CPG_ARMOUR, 										SOUND_SAMPLE_INDEX_SPEECH_US_CPG_AWARE_27, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_AWARE_27);
		initialise_speech_data (a, o, SPEECH_CPG_ARTILLERY, 									SOUND_SAMPLE_INDEX_SPEECH_US_CPG_AWARE_28, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_AWARE_28);
		initialise_speech_data (a, o, SPEECH_CPG_TRUCKS, 										SOUND_SAMPLE_INDEX_SPEECH_US_CPG_AWARE_29, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_AWARE_29);
		initialise_speech_data (a, o, SPEECH_CPG_SAM, 											SOUND_SAMPLE_INDEX_SPEECH_US_CPG_AWARE_30, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_AWARE_30);
		initialise_speech_data (a, o, SPEECH_CPG_TRIPLE_A, 									SOUND_SAMPLE_INDEX_SPEECH_US_CPG_AWARE_31, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_AWARE_31);
		initialise_speech_data (a, o, SPEECH_CPG_WARSHIPS, 									SOUND_SAMPLE_INDEX_SPEECH_US_CPG_AWARE_32, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_AWARE_32);
		initialise_speech_data (a, o, SPEECH_CPG_INFANTRY, 									SOUND_SAMPLE_INDEX_SPEECH_US_CPG_AWARE_33, SOUND_SAMPLE_INDEX_SPEECH_CIS_CPG_AWARE_33);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
