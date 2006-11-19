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

#define DEBUG_MODULE 										0

#define DEBUG_MODULE_DISPLAY_TARGET_POINT_OFFSETS	0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_CRUISE_TIME	((float) (511.0))	// change this then update EN_FLOAT.C FLOAT_TYPE_WEAPON_LIFETIME pack size

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Weapon Dynamics
//
//		Powered Weapons
//			Given:	max_range
//						muzzle_velocity
//						cruise_velocity
//						g_max
//			Compute:	burn_time = (cruise_velocity - muzzle_velocity) / g_max
//						burn_dist = (muzzle_velocity * burn_time) + (g_max * burn_time * burn_time) / 2.0
//						cruise_dist = max_range - burn_dist
//						cruise_time = cruise_dist / cruise_velocity
//
//		Short Life Ballistic Weapons (cannon shells)
//			Given:	max_range
//						muzzle_velocity
//	  		Compute:	cruise_velocity = muzzle_velocity
//						g_max = 0.0
//	  					burn_time = 0.0
//						cruise_time = max_range / cruise_velocity
//
//		Long Life Ballistic Weapons (artillery shells)
//			Given:	max_range (horizontal)
//	  		Compute:	muzzle_velocity = sqrt (max_range * G)
//						cruise_velocity = muzzle_velocity
//						g_max = 0.0
//						burn_time = 0.0
//						cruise_time = 2.0 * muzzle_velocity * sin (45) / G
//
//			Notes: 	Maximum range when elevation is 45 degrees.
//
//						Assume range is horizontal.
//
//						range = ((u * u) / G) * sin (2.0 * theta)		// theta = 45 degrees, therefore, sin (2.0 * theta) = 1.0
//
//						u = sqrt (range * G)
//
//						t = (2.0 * u * sin (theta)) / G					// theta = 45 degrees
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ WUT mod bug, date: 26-mar-03
//remove "const" from definition

weapon_data
	weapon_database[NUM_ENTITY_SUB_TYPE_WEAPONS] =
	{
		////////////////////////////////////////
		//	 
		// ENTITY_SUB_TYPE_WEAPON_NO_WEAPON
		//
		////////////////////////////////////////
		{
			"No Weapon",														// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"None",																// weapon_loading_list_name
			"None",																// weapon_loading_name_text

			0,							  											// default_3d_shape
			0,		 																// guidance_type
			0,																		// aiming_type
			0,																		// decoy_type
			0,																		// warhead_type
			0,																		// threat_type
			0,																		// interior_launch_sound_effect
			0,																		// exterior_launch_sound_effect
			0,																		// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			-1,																	// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			0,																		// gun_shake
			0,																		// soft_damage_capability
			0,																		// hard_damage_capability
			0,																		// smoke_trail_type
			0,																		// acquire_parent_forward_velocity
			0,																		// ignore_gravity
			0,																		// survive_ground_impact
			0,																		// in_flight_collision_check
			0,																		// viewable_weapon
			0,																		// boresight_weapon
			0,																		// hellfire_flight_profile
			0,																		// weapon_class

			0.0,																	// weight
			0.0,																	// min_range
			0.0,																	// max_range
			0.0,																	// effective_range
			0.0,																	// min_range_loal
			0.0,																	// max_range_loal
			0.0,																	// max_range_error_ratio
			0.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			0.0,																	// cruise_velocity
			0.0,																	// g_max
			0.0,																	// burn_time
			0.0,																	// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,																	// inhibit_time
			0.0,																	// burst_duration
			0.0,																	// rate_of_fire
			0.0,																	// reload_time
			0.0,																	// max_launch_angle_error
		},

		////////////////////////////////////////////////////////////////////////////////
		//
		// BALLISTIC WEAPONS
		//
		////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////
		//	 
		// ENTITY_SUB_TYPE_WEAPON_M2_12P7MM_ROUND
		//
		////////////////////////////////////////
		{
			"12.7mm Round",		 											// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_CANNON_SHELL_ORANGE,								// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_BALL,										// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_CHAIN_GUN,					// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_LIGHT_MACHINE_GUN,						// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_LIGHT_MACHINE_GUN,						// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_NONE,										// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_CANNON,						// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			TRUE,																	// gun_shake
			4,																		// soft_damage_capability
			0,																		// hard_damage_capability
			META_SMOKE_LIST_TYPE_NONE,										// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			TRUE,		  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			FALSE,																// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_SURFACE_TO_AIR +									// weapon_class
			WEAPON_CLASS_SURFACE_TO_SURFACE,

			0.0,																	// weight
			0.0,		  															// min_range
			1800.0,																// max_range
			600.0,																// effective_range
			0.0,																	// min_range_loal
			1800.0,		 														// max_range_loal
			0.0,																	// max_range_error_ratio
			600.0,																// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			600.0,																// cruise_velocity
			0.0,																	// g_max
			0.0,																	// burn_time
			1800.0 / 600.0,													// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,																	// inhibit_time
			3.0,																	// burst_duration
			1000.0,																// rate_of_fire
			10.0,																	// reload_time
			rad (1.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//	 
		// ENTITY_SUB_TYPE_WEAPON_M61A1_20MM_ROUND
		//
		////////////////////////////////////////
		{
			"M61A1 20mm Round",												// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_CANNON_SHELL_RED,									// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_BALL,										// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_CHAIN_GUN,					// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_LIGHT_MACHINE_GUN,						// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_LIGHT_MACHINE_GUN,						// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_NONE,										// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_CANNON,						// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			TRUE,																	// gun_shake
			12,																	// soft_damage_capability
			0,																		// hard_damage_capability
			META_SMOKE_LIST_TYPE_NONE,										// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			TRUE,		  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			FALSE,																// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_AIR_TO_AIR +										// weapon_class
			WEAPON_CLASS_AIR_TO_SURFACE +
			WEAPON_CLASS_SURFACE_TO_AIR +
			WEAPON_CLASS_SURFACE_TO_SURFACE,

			0.0,																	// weight
			0.0,																	// min_range
			1600.0,																// max_range
			600.0,																// effective_range
			0.0,																	// min_range_loal
			1600.0,			 													// max_range_loal
			0.0,																	// max_range_error_ratio
			884.0,																// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			884.0,																// cruise_velocity
			0.0,																	// g_max
			0.0,																	// burn_time
			1600.0 / 884.0,													// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,																	// inhibit_time
			3.0,																	// burst_duration
			1000.0,																// rate_of_fire
			10.0,																	// reload_time
			rad (1.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//	 
		// ENTITY_SUB_TYPE_WEAPON_M197_20MM_ROUND
		//
		////////////////////////////////////////
		{
			"M197 20mm Round",												// full_name
			"GUN",																// hud_name
			"GUN",																// mfd_name
			"M197",																// weapon_loading_list_name
			"M197 20mm Cannon",												// weapon_loading_name_text

			OBJECT_3D_CANNON_SHELL_RED,									// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_BALL,										// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_CHAIN_GUN,					// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_LIGHT_MACHINE_GUN,						// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_LIGHT_MACHINE_GUN,						// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_NONE,										// continuous_sound_effect
			SPEECH_CPG_SWITCHING_TO_CHAINGUN,							// weapon_selected_cpg_speech
			SPEECH_CPG_CANNON_LOW,											// weapon_low_cpg_speech
			SPEECH_CPG_CANNON_OUT,											// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_CANNON,						// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			TRUE,																	// gun_shake
			12,																	// soft_damage_capability
			5,																		// hard_damage_capability
			META_SMOKE_LIST_TYPE_NONE,										// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			TRUE,		  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			FALSE,																// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_AIR_TO_AIR +										// weapon_class
			WEAPON_CLASS_AIR_TO_SURFACE,

			0.257, 		 														// weight
			0.0,			 														// min_range
			1600.0,																// max_range
			500.0,																// effective_range
			0.0,																	// min_range_loal
			1600.0,			 													// max_range_loal
			0.0,																	// max_range_error_ratio
			884.0,																// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			884.0,																// cruise_velocity
			0.0,																	// g_max
			0.0,																	// burn_time
			1600.0 / 884.0,	 												// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,																	// inhibit_time
			3.0,																	// burst_duration
			750.0,																// rate_of_fire
			0.0,																	// reload_time
			rad (1.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//	 
		// ENTITY_SUB_TYPE_WEAPON_GAU12U_25MM_ROUND
		//
		////////////////////////////////////////
		{
			"GAU-12/U 25mm Round", 			  								// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_CANNON_SHELL_ORANGE,								// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_BALL,										// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_CHAIN_GUN,					// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_LIGHT_MACHINE_GUN,						// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_LIGHT_MACHINE_GUN,						// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_NONE,										// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_CANNON,						// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			TRUE,																	// gun_shake
			15,																	// soft_damage_capability
			3,																		// hard_damage_capability
			META_SMOKE_LIST_TYPE_NONE,										// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			TRUE,		  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			FALSE,																// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_AIR_TO_AIR +										// weapon_class
			WEAPON_CLASS_AIR_TO_SURFACE,

			0.0,	  																// weight
			0.0,																	// min_range
			1600.0,																// max_range
			600.0,																// effective_range
			0.0,																	// min_range_loal
			1600.0,																// max_range_loal
			0.0,																	// max_range_error_ratio
			1051.0,																// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			1051.0,																// cruise_velocity
			0.0,																	// g_max
			0.0,																	// burn_time
			1600.0 / 1051.0,													// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,																	// inhibit_time
			3.0,																	// burst_duration
			1650.0,																// rate_of_fire
			0.0,																	// reload_time
			rad (1.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//	 
		// ENTITY_SUB_TYPE_WEAPON_M242_25MM_ROUND
		//
		////////////////////////////////////////
		{
			"M242 25mm Round", 				  								// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_CANNON_SHELL_WHITE,									// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_BALL,										// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_CHAIN_GUN,					// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_LIGHT_MACHINE_GUN,						// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_LIGHT_MACHINE_GUN,						// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_NONE,										// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_CANNON,						// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			TRUE,																	// gun_shake
			16,																	// soft_damage_capability
			6,																		// hard_damage_capability
			META_SMOKE_LIST_TYPE_NONE,										// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			TRUE,		  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			FALSE,																// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_SURFACE_TO_AIR +									// weapon_class
			WEAPON_CLASS_SURFACE_TO_SURFACE,

			0.0,																	// weight
			0.0,		  															// min_range
			3500.0,																// max_range
			2000.0,																// effective_range
			0.0,																	// min_range_loal
			3500.0,			 													// max_range_loal
			0.0,																	// max_range_error_ratio
			1000.0,																// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			1000.0,																// cruise_velocity
			0.0,																	// g_max
			0.0,																	// burn_time
			3500.0 / 1000.0,													// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,																	// inhibit_time
			3.0,																	// burst_duration
			1000.0,																// rate_of_fire
			9.0,																	// reload_time
			rad (1.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//	 
		// ENTITY_SUB_TYPE_WEAPON_GAU8A_30MM_ROUND
		//
		////////////////////////////////////////
		{
			"GAU-8/A 30mm Round",				  							// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_CANNON_SHELL_ORANGE,								// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_ARMOUR_PIERCING,						// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_CHAIN_GUN,					// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_HEAVY_MACHINE_GUN,						// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_HEAVY_MACHINE_GUN,						// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_NONE,										// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_CANNON,						// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			TRUE,																	// gun_shake
			100,																	// soft_damage_capability
			100,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_NONE,										// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			TRUE,		  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			FALSE,																// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_AIR_TO_AIR +										// weapon_class
			WEAPON_CLASS_AIR_TO_SURFACE,

			0.0, 		 															// weight
			0.0,																	// min_range
			1200.0,																// max_range
			600.0,																// effective_range
			0.0,																	// min_range_loal
			1200.0,			 													// max_range_loal
			0.0,																	// max_range_error_ratio
			1030.0,																// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			1030.0,																// cruise_velocity
			0.0,																	// g_max
			0.0,																	// burn_time
			1200.0 / 1030.0,													// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,																	// inhibit_time
			3.0,																	// burst_duration
			2100.0,																// rate_of_fire
			0.0,																	// reload_time
			rad (1.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//	 
		// ENTITY_SUB_TYPE_WEAPON_M230_30MM_ROUND
		//
		////////////////////////////////////////
		{
			"M230 30mm Round",				  								// full_name
			"GUN",																// hud_name
			"?",																	// mfd_name
			"M230",																// weapon_loading_list_name
			"M230 30mm Chain Gun",											// weapon_loading_name_text

			OBJECT_3D_CANNON_SHELL_RED,									// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE,							// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_CHAIN_GUN,					// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_INTERIOR_CHAINGUN,						// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_CHAINGUN,						// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_NONE,										// continuous_sound_effect
			SPEECH_CPG_SWITCHING_TO_CHAINGUN,							// weapon_selected_cpg_speech
			SPEECH_CPG_CANNON_LOW,											// weapon_low_cpg_speech
			SPEECH_CPG_CANNON_OUT,											// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_CANNON,						// weapon_launched_wingman_speech
			50,																	// report_weapon_low_count
			TRUE,																	// gun_shake
			30,																	// soft_damage_capability
			15,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_NONE,										// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			TRUE,		  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			FALSE,																// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_AIR_TO_AIR +										// weapon_class
			WEAPON_CLASS_AIR_TO_SURFACE,

			0.495,																// weight
			0.0,	 																// min_range
			1200.0,																// max_range
			800.0,																// effective_range
			0.0,																	// min_range_loal
			1200.0,	 															// max_range_loal
			0.0,																	// max_range_error_ratio
			792.0,																// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			792.0,																// cruise_velocity
			0.0,																	// g_max
			0.0,																	// burn_time
			1200.0 / 792.0,													// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,																	// inhibit_time
			3.0,																	// burst_duration
			625.0,																// rate_of_fire
			0.0,																	// reload_time
			rad (1.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//	 
		// ENTITY_SUB_TYPE_WEAPON_M75_76MM_ROUND
		//
		////////////////////////////////////////
		{
			//
			// customised for Oliver Hazard Perry Class (pitch limits 20.0 to 85.0 degrees)
			//

			"M75 76mm Round",													// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_ARTILLERY_SHELL,			  							// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_CALC_ANGLE_OF_PROJECTION,				// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE,							// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_HEAVY_ARTILLERY,							// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_HEAVY_ARTILLERY,							// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_NONE,										// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			-1,																	// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			450,																	// soft_damage_capability
			450,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_NONE,										// smoke_trail_type
			FALSE,																// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			FALSE,																// in_flight_collision_check
			TRUE,																	// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_SURFACE_TO_SURFACE,								// weapon_class

			0.0,																	// weight
			2571.4,																// min_range
			4000.0,																// max_range
			2000.0,																// effective_range
			2571.4,																// min_range_loal
			4000.0,			 													// max_range_loal
			50.0 / 4000.0,		 												// max_range_error_ratio
			198.1,																// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			198.1,																// cruise_velocity
			0.0,																	// g_max
			0.0,																	// burn_time
			28.6,																	// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,																	// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			20.0,																	// reload_time
			rad (1.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//	 
		// ENTITY_SUB_TYPE_WEAPON_M256_120MM_ROUND
		//
		////////////////////////////////////////
		{
			//
			// customised for M1A2 Abrams (pitch limits -9.0 to 20.0 degrees)
			//

			"M256 120mm Round",				  								// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_ARTILLERY_SHELL,			  							// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_CALC_ANGLE_OF_PROJECTION,				// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_TANK,			// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_HEAVY_ARTILLERY,							// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_HEAVY_ARTILLERY,							// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_NONE,										// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			-1,																	// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			634,																	// soft_damage_capability
			634,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_NONE,										// smoke_trail_type
			FALSE,																// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			FALSE,	 															// in_flight_collision_check
			TRUE,			  														// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_SURFACE_TO_SURFACE,								// weapon_class

			0.0,																	// weight
			0.0,																	// min_range
			4000.0,																// max_range
			2000.0,																// effective_range
			0.0,																	// min_range_loal
			4000.0,																// max_range_loal
			50.0 / 4000.0,														// max_range_error_ratio
			247.1,																// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			247.1,																// cruise_velocity
			0.0,																	// g_max
			0.0,																	// burn_time
			17.2,		  															// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,																	// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			15.0,																	// reload_time
			rad (1.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//	 
		// ENTITY_SUB_TYPE_WEAPON_M284_155MM_ROUND
		//
		////////////////////////////////////////
		{
			"M284 155mm Round",				  								// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_ARTILLERY_SHELL,			  							// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_CALC_ANGLE_OF_PROJECTION,				// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_TANK,			// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_HEAVY_ARTILLERY,							// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_HEAVY_ARTILLERY,							// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_NONE,										// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			-1,																	// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			1610,																	// soft_damage_capability
			1610,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_NONE,										// smoke_trail_type
			FALSE,																// acquire_parent_forward_velocity
			FALSE, 	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			FALSE, 																// in_flight_collision_check
			TRUE,																	// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_SURFACE_TO_SURFACE,								// weapon_class

			0.0,																	// weight
			0.0,		  															// min_range
			30000.0,																// max_range
			15000.0,																// effective_range
			0.0,																	// min_range_loal
			30000.0,																// max_range_loal
			150.0 / 30000.0, 													// max_range_error_ratio
			542.5,																// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			542.5,																// cruise_velocity
			0.0,																	// g_max
			0.0,																	// burn_time
			78.2,																	// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,																	// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			20.0,																	// reload_time
			rad (1.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//	 
		// ENTITY_SUB_TYPE_WEAPON_M270_227MM_ROCKET
		//
		////////////////////////////////////////
		{
			//
			// customised for M270 MLRS (pitch limits 15.0 to 50.0 degrees)
			//

			"M270 227mm Rocket",				  								// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_MLRS_MISSILE,											// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_CALC_ANGLE_OF_PROJECTION,				// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_TANK,			// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_EXTERIOR_ROCKET_LAUNCH,				// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_ROCKET_LAUNCH,				// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_HEAVY_MISSILE_FLIGHT,					// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			-1,																	// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			2500,																	// soft_damage_capability
			2500,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			FALSE,  																// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			FALSE, 																// in_flight_collision_check
			TRUE,				 													// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_SURFACE_TO_SURFACE,								// weapon_class

			0.0,																	// weight
			15801.5,																// min_range
			31600.0,																// max_range
			15000.0,																// effective_range
			15801.5,																// min_range_loal
			31600.0,			  													// max_range_loal
			150.0 / 31600.0,													// max_range_error_ratio
			556.8,																// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			556.8,																// cruise_velocity
			0.0,																	// g_max
			0.0,																	// burn_time
			80.3,																	// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,																	// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			25.0,																	// reload_time
			rad (1.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//	 
		// ENTITY_SUB_TYPE_WEAPON_NSV_12P7MM_ROUND
		//
		////////////////////////////////////////
		{
			"12.7mm Round",		 											// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_CANNON_SHELL_WHITE,									// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_BALL,										// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_CHAIN_GUN,					// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_LIGHT_MACHINE_GUN,						// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_LIGHT_MACHINE_GUN,						// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_NONE,										// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_CANNON,						// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			TRUE,																	// gun_shake
			4,																		// soft_damage_capability
			0,																		// hard_damage_capability
			META_SMOKE_LIST_TYPE_NONE,										// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			TRUE,		  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			FALSE,																// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_SURFACE_TO_AIR +									// weapon_class
			WEAPON_CLASS_SURFACE_TO_SURFACE,

			0.0,																	// weight
			0.0,		  															// min_range
			1800.0,																// max_range
			600.0,																// effective_range
			0.0,																	// min_range_loal
			1800.0,																// max_range_loal
			0.0,																	// max_range_error_ratio
			600.0,																// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			600.0,																// cruise_velocity
			0.0,																	// g_max
			0.0,																	// burn_time
			1800.0 / 600.0,													// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,																	// inhibit_time
			3.0,																	// burst_duration
			1000.0,																// rate_of_fire
			10.0,																	// reload_time
			rad (1.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//	 
		// ENTITY_SUB_TYPE_WEAPON_9A642_12P7MM_ROUND
		//
		////////////////////////////////////////
		{
			"9-A-624 12.7mm Round",				  							// full_name
			"9-A-624 12.7mm Round",																	// hud_name
			"9-A-624 12.7mm Round",																	// mfd_name
			"12.7mm Round",																	// weapon_loading_list_name
			"12.7mm Round",																	// weapon_loading_name_text

			OBJECT_3D_CANNON_SHELL_ORANGE,								// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_BALL,										// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_CHAIN_GUN,					// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_LIGHT_MACHINE_GUN,						// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_LIGHT_MACHINE_GUN,						// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_NONE,										// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_CANNON,						// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			TRUE,																	// gun_shake
			5,																		// soft_damage_capability
			0,																		// hard_damage_capability
			META_SMOKE_LIST_TYPE_NONE,										// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			TRUE,		  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			FALSE,																// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_AIR_TO_AIR +										// weapon_class
			WEAPON_CLASS_AIR_TO_SURFACE,

			0.0,																	// weight
			0.0,		  															// min_range
			1500.0,																// max_range
			800.0,																// effective_range
			0.0,																	// min_range_loal
			1500.0,		  														// max_range_loal
			0.0,																	// max_range_error_ratio
			600.0,																// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			600.0,																// cruise_velocity
			0.0,																	// g_max
			0.0,																	// burn_time
			1500.0 / 600.0,													// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,																	// inhibit_time
			3.0,																	// burst_duration
			4000.0,																// rate_of_fire
			0.0,																	// reload_time
			rad (1.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_KPV_14P5MM_ROUND
		//
		////////////////////////////////////////
		{
			"14.5mm Round",	  					  							// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_CANNON_SHELL_WHITE,									// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_BALL,										// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_CHAIN_GUN,					// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_LIGHT_MACHINE_GUN,						// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_LIGHT_MACHINE_GUN,						// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_NONE,										// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_CANNON,						// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			TRUE,																	// gun_shake
			6,																		// soft_damage_capability
			0,																		// hard_damage_capability
			META_SMOKE_LIST_TYPE_NONE,										// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			TRUE,		  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			FALSE,																// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_SURFACE_TO_AIR +									// weapon_class
			WEAPON_CLASS_SURFACE_TO_SURFACE,

			0.0,																	// weight
			0.0,		  															// min_range
			1600.0,																// max_range
			600.0,																// effective_range
			0.0,																	// min_range_loal
			1600.0,																// max_range_loal
			0.0,																	// max_range_error_ratio
			600.0,																// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			600.0,																// cruise_velocity
			0.0,																	// g_max
			0.0,																	// burn_time
			1600.0 / 600.0,  													// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,		 															// inhibit_time
			3.0,																	// burst_duration
			1000.0,																// rate_of_fire
			12.0,																	// reload_time
			rad (1.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND
		//
		////////////////////////////////////////
		{
			"GSh-23L 23mm Round",			  								// full_name
			"GSh-23L",															// hud_name
			"CANNON",		 													// mfd_name
			"GSh-23L", 															// weapon_loading_list_name
			"GSh-23L 23mm Cannon Pod",										// weapon_loading_name_text

			OBJECT_3D_CANNON_SHELL_ORANGE,								// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_BALL,										// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_CHAIN_GUN,					// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_HEAVY_MACHINE_GUN,						// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_HEAVY_MACHINE_GUN,						// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_NONE,										// continuous_sound_effect
			SPEECH_CPG_SWITCHING_TO_CANNON_PODS,						// weapon_selected_cpg_speech
			SPEECH_CPG_CANNON_LOW,											// weapon_low_cpg_speech
			SPEECH_CPG_CANNON_OUT,											// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_CANNON,						// weapon_launched_wingman_speech
			40,																	// report_weapon_low_count
			TRUE,			  														// gun_shake
			25,																	// soft_damage_capability
			8,																		// hard_damage_capability
			META_SMOKE_LIST_TYPE_NONE,										// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			TRUE,		  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			FALSE,																// viewable_weapon
			TRUE,																	// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_AIR_TO_AIR +										// weapon_class
			WEAPON_CLASS_AIR_TO_SURFACE,

			0.2,																	// weight
			0.0,		  															// min_range
			2000.0,																// max_range
			500.0,																// effective_range
			0.0,																	// min_range_loal
			2000.0,		  														// max_range_loal
			0.0,																	// max_range_error_ratio
			930.0,																// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			930.0,																// cruise_velocity
			0.0,																	// g_max
			0.0,																	// burn_time
			2000.0 / 930.0,	 												// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,		 															// inhibit_time
			3.0,																	// burst_duration
			1000.0,																// rate_of_fire
			0.0,																	// reload_time
			rad (1.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_GSH301_30MM_ROUND
		//
		////////////////////////////////////////
		{
			"GSh-301 30mm Round",				  							// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_CANNON_SHELL_RED,									// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE,							// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_CHAIN_GUN,					// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_HEAVY_MACHINE_GUN,						// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_HEAVY_MACHINE_GUN,						// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_NONE,										// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_CANNON,						// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			TRUE,		 															// gun_shake
			40,																	// soft_damage_capability
			25,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_NONE,										// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			TRUE,		  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			FALSE,																// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_AIR_TO_AIR +										// weapon_class
			WEAPON_CLASS_AIR_TO_SURFACE,

			0.0,																	// weight
			0.0,	  																// min_range
			1600.0,																// max_range
			800.0,																// effective_range
			0.0,																	// min_range_loal
			1600.0,			 													// max_range_loal
			0.0,																	// max_range_error_ratio
			800.0,																// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			800.0,																// cruise_velocity
			0.0,																	// g_max
			0.0,																	// burn_time
			1600.0 / 800.0,													// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,		 															// inhibit_time
			3.0,																	// burst_duration
			1000.0,																// rate_of_fire
			0.0,																	// reload_time
			rad (1.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_2A38M_30MM_ROUND
		//
		////////////////////////////////////////
		{
			"2A38M 30mm Round",												// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_CANNON_SHELL_RED,									// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE,							// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_CHAIN_GUN,					// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_HEAVY_MACHINE_GUN,						// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_HEAVY_MACHINE_GUN,						// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_NONE,										// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_CANNON,						// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			TRUE,																	// gun_shake
			25,																	// soft_damage_capability
			10,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_NONE,										// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			TRUE,		  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			FALSE,																// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_SURFACE_TO_AIR,									// weapon_class

			0.0,																	// weight
			0.0,																	// min_range
			2500.0,																// max_range
			1500.0,																// effective_range
			0.0,																	// min_range_loal
			2500.0,		  														// max_range_loal
			0.0,																	// max_range_error_ratio
			1200.0,																// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			1200.0,																// cruise_velocity
			0.0,																	// g_max
			0.0,																	// burn_time
			2500.0 / 1200.0, 													// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,		 															// inhibit_time
			3.0,																	// burst_duration
			1000.0,																// rate_of_fire
			15.0,																	// reload_time
			rad (1.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_2A42_30MM_ROUND
		//
		////////////////////////////////////////
		{
			"2A42 30mm Round",												// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_CANNON_SHELL_ORANGE,								// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE,							// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_CHAIN_GUN,					// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_HEAVY_MACHINE_GUN,						// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_HEAVY_MACHINE_GUN,						// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_NONE,										// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_CANNON,						// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			TRUE,		 															// gun_shake
			30,																	// soft_damage_capability
			15,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_NONE,										// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			TRUE,		  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			FALSE,																// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_SURFACE_TO_AIR +									// weapon_class
			WEAPON_CLASS_SURFACE_TO_SURFACE,

			0.0,																	// weight
			0.0,			 														// min_range
			4000.0,																// max_range
			800.0,																// effective_range
			0.0,																	// min_range_loal
			4000.0,																// max_range_loal
			0.0,																	// max_range_error_ratio
			1000.0,																// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			1000.0,																// cruise_velocity
			0.0,																	// g_max
			0.0,																	// burn_time
			4000.0 / 1000.0,													// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,		 															// inhibit_time
			3.0,																	// burst_duration
			350.0,																// rate_of_fire
			15.0,																	// reload_time
			rad (1.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND
		//
		////////////////////////////////////////
		{
			"2A42 30mm HE Round",	  		  								// full_name
			"Gun(HE)",															// hud_name
			"?",																	// mfd_name
			"2A42 (HE)",	  													// weapon_loading_list_name
			"2A42 30mm Cannon",												// weapon_loading_name_text

			OBJECT_3D_CANNON_SHELL_ORANGE,								// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE,							// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_CHAIN_GUN,					// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_INTERIOR_CHAINGUN,						// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_CHAINGUN,						// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_NONE,										// continuous_sound_effect
			SPEECH_CPG_SWITCHING_TO_CANNON,								// weapon_selected_cpg_speech
			SPEECH_CPG_CANNON_LOW,											// weapon_low_cpg_speech
			SPEECH_CPG_CANNON_OUT,											// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_CANNON,						// weapon_launched_wingman_speech
			20,																	// report_weapon_low_count
			TRUE,																	// gun_shake
			30,																	// soft_damage_capability
			15,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_NONE,										// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			TRUE,		  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			FALSE,																// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_AIR_TO_AIR +										// weapon_class
			WEAPON_CLASS_AIR_TO_SURFACE,

			1.0,																	// weight
			0.0,			 														// min_range
			2000.0,																// max_range
			600.0,																// effective_range
			0.0,																	// min_range_loal
			2000.0,																// max_range_loal
			0.0,																	// max_range_error_ratio
			1000.0,																// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			1000.0,																// cruise_velocity
			0.0,																	// g_max
			0.0,																	// burn_time
			2000.0 / 1000.0,													// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,		 															// inhibit_time
			3.0,																	// burst_duration
			350.0,																// rate_of_fire
			0.0,																	// reload_time
			rad (1.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND
		//
		////////////////////////////////////////
		{
			"2A42 30mm AP Round",	  		  								// full_name
			"Gun(AP)",															// hud_name
			"?",																	// mfd_name
			"2A42 (AP)",	  													// weapon_loading_list_name
			"2A42 30mm Cannon",												// weapon_loading_name_text

			OBJECT_3D_CANNON_SHELL_ORANGE,								// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_ARMOUR_PIERCING,						// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_CHAIN_GUN,					// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_INTERIOR_CHAINGUN,						// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_CHAINGUN,						// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_NONE,										// continuous_sound_effect
			SPEECH_CPG_SELECTING_CANNON,									// weapon_selected_cpg_speech
			SPEECH_CPG_CANNON_LOW,											// weapon_low_cpg_speech
			SPEECH_CPG_CANNON_OUT,											// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_CANNON,						// weapon_launched_wingman_speech
			20,																	// report_weapon_low_count
			TRUE,	 																// gun_shake
			25,																	// soft_damage_capability
			25,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_NONE,										// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			TRUE,		  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			FALSE,																// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_AIR_TO_AIR +										// weapon_class
			WEAPON_CLASS_AIR_TO_SURFACE,

			1.0,																	// weight
			0.0,			 														// min_range
			2000.0,																// max_range
			600.0,																// effective_range
			0.0,																	// min_range_loal
			2000.0,																// max_range_loal
			0.0,																	// max_range_error_ratio
			1000.0,																// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			1000.0,																// cruise_velocity
			0.0,																	// g_max
			0.0,																	// burn_time
			2000.0 / 1000.0,													// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,		 															// inhibit_time
			3.0,																	// burst_duration
			350.0,																// rate_of_fire
			0.0,																	// reload_time
			rad (1.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_2A72_30MM_ROUND
		//
		////////////////////////////////////////
		{
			"2A72 30mm Round",  		  		  								// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_CANNON_SHELL_RED,									// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE,							// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_CHAIN_GUN,					// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_HEAVY_MACHINE_GUN,						// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_HEAVY_MACHINE_GUN,						// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_NONE,										// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_CANNON,						// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			TRUE,		 															// gun_shake
			30,																	// soft_damage_capability
			15,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_NONE,										// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			TRUE,		  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			FALSE,																// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_SURFACE_TO_AIR +									// weapon_class
			WEAPON_CLASS_SURFACE_TO_SURFACE,

			0.0,																	// weight
			0.0,	 																// min_range
			2000.0,																// max_range
			1000.0,																// effective_range
			0.0,																	// min_range_loal
			2000.0,		  														// max_range_loal
			0.0,																	// max_range_error_ratio
			800.0,																// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			800.0,																// cruise_velocity
			0.0,																	// g_max
			0.0,																	// burn_time
			2000.0 / 800.0,		  											// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,																	// inhibit_time
			3.0,																	// burst_duration
			1000.0,																// rate_of_fire
			16.0,																	// reload_time
			rad (1.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_AO17A_30MM_ROUND
		//
		////////////////////////////////////////
		{
			"AO-17A 30mm Round",	  	  		  								// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_CANNON_SHELL_RED,									// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_ARMOUR_PIERCING,						// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_CHAIN_GUN,					// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_HEAVY_MACHINE_GUN,						// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_HEAVY_MACHINE_GUN,						// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_NONE,										// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_CANNON,						// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			TRUE,																	// gun_shake
			30,																	// soft_damage_capability
			15,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_NONE,										// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			TRUE,		  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			FALSE,																// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_AIR_TO_AIR +										// weapon_class
			WEAPON_CLASS_AIR_TO_SURFACE,

			0.0, 	  																// weight
			0.0,																	// min_range
			1500.0,																// max_range
			800.0,																// effective_range
			0.0,																	// min_range_loal
			1500.0,	 															// max_range_loal
			0.0,																	// max_range_error_ratio
			1000.0,																// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			1000.0,																// cruise_velocity
			0.0,																	// g_max
			0.0,																	// burn_time
			1500.0 / 1000.0,													// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,																	// inhibit_time
			3.0,																	// burst_duration
			100.0,																// rate_of_fire
			0.0,																	// reload_time
			rad (1.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_ADMG_630_30MM_ROUND
		//
		////////////////////////////////////////
		{
			"ADMG-630 30mm Round",											// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_CANNON_SHELL_WHITE,									// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE,							// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_CHAIN_GUN,					// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_HEAVY_MACHINE_GUN,						// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_HEAVY_MACHINE_GUN,						// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_NONE,										// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_CANNON,						// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			TRUE,																	// gun_shake
			30,																	// soft_damage_capability
			15,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_NONE,										// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			TRUE,		  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			FALSE,																// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_SURFACE_TO_AIR,									// weapon_class

			0.0,																	// weight
			0.0,																	// min_range
			1500.0,																// max_range
			1000.0,																// effective_range
			0.0,																	// min_range_loal
			1500.0,																// max_range_loal
			0.0,																	// max_range_error_ratio
			800.0,																// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			800.0,																// cruise_velocity
			0.0,																	// g_max
			0.0,																	// burn_time
			1500.0 / 800.0,													// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,																	// inhibit_time
			3.0,																	// burst_duration
			1000.0,																// rate_of_fire
			9.0,																	// reload_time
			rad (1.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_CIS_NAVAL_76MM_ROUND
		//
		////////////////////////////////////////
		{
			"76mm Round",														// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_ARTILLERY_SHELL,			  							// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_CALC_ANGLE_OF_PROJECTION,				// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_TANK,			// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_HEAVY_ARTILLERY,							// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_HEAVY_ARTILLERY,							// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_NONE,										// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			-1,																	// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			450,																	// soft_damage_capability
			450,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_NONE,										// smoke_trail_type
			FALSE,  																// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			FALSE,	 															// in_flight_collision_check
			TRUE,			  														// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_SURFACE_TO_SURFACE,								// weapon_class

			0.0,																	// weight
			0.0,		  															// min_range
			4000.0,																// max_range
			2000.0,																// effective_range
			0.0,																	// min_range_loal
			4000.0,																// max_range_loal
			50.0 / 4000.0,														// max_range_error_ratio
			198.1,																// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			198.1,																// cruise_velocity
			0.0,																	// g_max
			0.0,																	// burn_time
			28.6,																	// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,																	// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			20.0,																	// reload_time
			rad (1.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_CIS_NAVAL_100MM_ROUND
		//
		////////////////////////////////////////
		{
			"100mm Round",														// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_ARTILLERY_SHELL,			  							// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_CALC_ANGLE_OF_PROJECTION,				// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_TANK,			// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_HEAVY_ARTILLERY,							// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_HEAVY_ARTILLERY,							// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_NONE,										// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			-1,																	// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			650,																	// soft_damage_capability
			650,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_NONE,										// smoke_trail_type
			FALSE,																// acquire_parent_forward_velocity
			FALSE,		  														// ignore_gravity
			FALSE,																// survive_ground_impact
			FALSE,	 															// in_flight_collision_check
			TRUE,			  														// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_SURFACE_TO_SURFACE,								// weapon_class

			0.0,																	// weight
			0.0,																	// min_range
			4000.0,																// max_range
			2000.0,																// effective_range
			0.0,																	// min_range_loal
			4000.0,																// max_range_loal
			50.0 / 4000.0,		 												// max_range_error_ratio
			198.1,																// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			198.1,																// cruise_velocity
			0.0,																	// g_max
			0.0,																	// burn_time
			28.6,																	// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,																	// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			25.0,																	// reload_time
			rad (1.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_2K23_100MM_ROUND
		//
		////////////////////////////////////////
		{
			"2K23 100mm Round",	  	  		  								// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_ARTILLERY_SHELL,			  							// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_CALC_ANGLE_OF_PROJECTION,				// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_TANK,			// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_HEAVY_ARTILLERY,							// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_HEAVY_ARTILLERY,							// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_NONE,										// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			-1,																	// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			650,																	// soft_damage_capability
			650,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_NONE,										// smoke_trail_type
			FALSE,																// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			FALSE, 																// in_flight_collision_check
			TRUE,			  														// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_SURFACE_TO_SURFACE,								// weapon_class

			0.0,																	// weight
			0.0,																	// min_range
			4000.0,																// max_range
			2000.0,																// effective_range
			0.0,																	// min_range_loal
			4000.0,																// max_range_loal
			50.0 / 4000.0,		 												// max_range_error_ratio
			198.1,																// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			198.1,																// cruise_velocity
			0.0,																	// g_max
			0.0,																	// burn_time
			28.6,																	// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,																	// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			22.0,																	// reload_time
			rad (1.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_BM21_122MM_ROCKET
		//
		////////////////////////////////////////
		{
			//
			// customised for BM-21 (pitch limits 5.0 to 55.0 degrees)
			//

			"BM-21 122mm Rocket",	  	  		  							// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_BM21_MISSILE,											// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_CALC_ANGLE_OF_PROJECTION,				// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE,							// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_EXTERIOR_ROCKET_LAUNCH,				// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_ROCKET_LAUNCH,				// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_LIGHT_MISSILE_FLIGHT,					// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			-1,																	// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			1400,																	// soft_damage_capability
			1400,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			FALSE,																// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			FALSE, 																// in_flight_collision_check
			TRUE,			  														// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_SURFACE_TO_SURFACE,								// weapon_class

			0.0,																	// weight
			5209.4,	  															// min_range
			30000.0,																// max_range
			15000.0,																// effective_range
			5209.4,																// min_range_loal
			30000.0,		 														// max_range_loal
			150.0 / 30000.0,													// max_range_error_ratio
			542.5,																// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			542.5,																// cruise_velocity
			0.0,																	// g_max
			0.0,																	// burn_time
			78.2,																	// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,																	// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			20.0,																	// reload_time
			rad (1.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_2A46M1_125MM_ROUND
		//
		////////////////////////////////////////
		{
			//
			// customised for T80U (pitch limits -5.0 to 14.0 degrees)
			//

			"2A46M1 125mm Round",	  	  		  							// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_ARTILLERY_SHELL,			  							// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_CALC_ANGLE_OF_PROJECTION,				// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_TANK,			// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_HEAVY_ARTILLERY,							// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_HEAVY_ARTILLERY,							// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_NONE,										// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			-1,																	// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			688,																	// soft_damage_capability
			688,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_NONE,										// smoke_trail_type
			FALSE,																// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			FALSE, 																// in_flight_collision_check
			TRUE,				 													// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_SURFACE_TO_SURFACE,								// weapon_class

			0.0,																	// weight
			0.0,																	// min_range
			4000.0,																// max_range
			3000.0,																// effective_range
			0.0,																	// min_range_loal
			4000.0,			 													// max_range_loal
			50.0 / 4000.0,														// max_range_error_ratio
			289.1,																// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			289.1,																// cruise_velocity
			0.0,																	// g_max
			0.0,																	// burn_time
			14.3,																	// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,																	// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			15.0,																	// reload_time
			rad (1.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_2A65_152MM_ROUND
		//
		////////////////////////////////////////
		{
			"2A65 152mm Round",	 	 	  		  							// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_ARTILLERY_SHELL,			  							// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_CALC_ANGLE_OF_PROJECTION,				// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE,							// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_HEAVY_ARTILLERY,							// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_HEAVY_ARTILLERY,							// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_NONE,										// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			-1,																	// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			1548,																	// soft_damage_capability
			1548,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_NONE,										// smoke_trail_type
			FALSE,																// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			FALSE, 																// in_flight_collision_check
			TRUE,			  														// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_SURFACE_TO_SURFACE,								// weapon_class

			0.0,																	// weight
			0.0,	 																// min_range
			24000.0,																// max_range
			12000.0,																// effective_range
			0.0,																	// min_range_loal
			24000.0,				 												// max_range_loal
			150.0 / 24000.0,													// max_range_error_ratio
			485.2,																// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			485.2,																// cruise_velocity
			0.0,																	// g_max
			0.0,																	// burn_time
			69.9,																	// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,																	// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			25.0,																	// reload_time
			rad (1.0),															// max_launch_angle_error
		},

		////////////////////////////////////////////////////////////////////////////////
		//
		// UNGUIDED ROCKETS
		//
		////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255
		//
		////////////////////////////////////////
		{
			"Hydra 70 M255",					  								// full_name
			"RKT(HE)",	 		 												// hud_name
			"RKT(HE)",															// mfd_name
			"M255",																// weapon_loading_list_name
			"Hydra 70 M255",													// weapon_loading_name_text

			OBJECT_3D_AH64D_HYDRA_MISSILE,	  							// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE,							// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_INTERIOR_ROCKET_LAUNCH,				// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_ROCKET_LAUNCH,				// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_LIGHT_MISSILE_FLIGHT,					// continuous_sound_effect
			SPEECH_CPG_SWITCHING_TO_ROCKETS,								// weapon_selected_cpg_speech
			SPEECH_CPG_ROCKETS_LOW,											// weapon_low_cpg_speech
			SPEECH_CPG_ROCKETS_OUT,											// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_ROCKET,						// weapon_launched_wingman_speech
			5,																		// report_weapon_low_count
			FALSE,																// gun_shake
			500,																	// soft_damage_capability
			120,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			TRUE,	  	 															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			TRUE,				 													// viewable_weapon
			TRUE,			  														// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_AIR_TO_SURFACE,									// weapon_class

			6.0,																	// weight
			100.0,																// min_range
			5000.0,																// max_range
			800.0,																// effective_range
			100.0, 																// min_range_loal
			5000.0,		  														// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			850.0,																// cruise_velocity
			30.0 * G,															// g_max
			2.718,																// burn_time
			4.443,																// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,																	// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			0.0,																	// reload_time
			rad (0.1),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_HYDRA70_M261
		//
		////////////////////////////////////////
		{
			"Hydra 70 M261",			 		  								// full_name
			"RKT(MP)",															// hud_name
			"RKT(MP)",															// mfd_name
			"M261",	 		 													// weapon_loading_list_name
			"Hydra 70 M261",		 											// weapon_loading_name_text

			OBJECT_3D_AH64D_HYDRA_MISSILE,	  							// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_TANK,			// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_INTERIOR_ROCKET_LAUNCH,				// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_ROCKET_LAUNCH,				// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_LIGHT_MISSILE_FLIGHT,					// continuous_sound_effect
			SPEECH_CPG_SELECTING_ROCKETS,									// weapon_selected_cpg_speech
			SPEECH_CPG_ROCKETS_LOW,											// weapon_low_cpg_speech
			SPEECH_CPG_ROCKETS_OUT,											// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_ROCKET,						// weapon_launched_wingman_speech
			5,																		// report_weapon_low_count
			FALSE,																// gun_shake
			600,																	// soft_damage_capability
			400,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			TRUE,	  	 															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			TRUE,																	// viewable_weapon
			TRUE,				 													// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_AIR_TO_SURFACE,									// weapon_class

			6.0,																	// weight
			100.0,																// min_range
			5000.0,																// max_range
			800.0,																// effective_range
			100.0,	  															// min_range_loal
			5000.0,																// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			850.0,																// cruise_velocity
			30.0 * G,															// g_max
			2.718,																// burn_time
			4.443,																// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,																	// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			0.0,																	// reload_time
			rad (0.1),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_LAU69A
		//
		////////////////////////////////////////
		{
			"LAU-69/A",	  						  								// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_AH64D_HYDRA_MISSILE,	  							// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE,							// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_EXTERIOR_ROCKET_LAUNCH,				// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_ROCKET_LAUNCH,				// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_LIGHT_MISSILE_FLIGHT,					// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_ROCKET,						// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			500,																	// soft_damage_capability
			150,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			TRUE,																	// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			TRUE,			  														// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_AIR_TO_SURFACE,									// weapon_class

			0.0,																	// weight
			100.0,																// min_range
			5000.0,																// max_range
			750.0,																// effective_range
			100.0,																// min_range_loal
			5000.0,	 															// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			850.0,																// cruise_velocity
			30.0 * G,															// g_max
			2.718,																// burn_time
			4.443,																// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,																	// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			0.0,																	// reload_time
			rad (0.1),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_S5
		//
		////////////////////////////////////////
		{
			"S-5",	  							  								// full_name
			"S-5",																	// hud_name
			"S-5",																	// mfd_name
			"S-5",																	// weapon_loading_list_name
			"S-5",																	// weapon_loading_name_text

			OBJECT_3D_S5_MISSILE,		  									// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE,							// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_EXTERIOR_ROCKET_LAUNCH,				// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_ROCKET_LAUNCH,				// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_LIGHT_MISSILE_FLIGHT,					// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_ROCKET,						// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			500,																	// soft_damage_capability
			150,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			TRUE, 	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			TRUE,				  													// viewable_weapon
			FALSE,					// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_AIR_TO_SURFACE,									// weapon_class

			0.0,																	// weight
			100.0,																// min_range
			3000.0,																// max_range
			600.0,																// effective_range
			100.0,																// min_range_loal
			3000.0,																// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			700.0,																// cruise_velocity
			30.0 * G,															// g_max
			2.209,																// burn_time
			3.103,																// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,																	// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			0.0,																	// reload_time
			rad (0.1),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_S8
		//
		////////////////////////////////////////
		{
			"S-8",								  								// full_name
			"S-8",																// hud_name
			"S-8",  																// mfd_name
			"S-8",					  											// weapon_loading_list_name
			"S-8",					  											// weapon_loading_name_text

			OBJECT_3D_S8_MISSILE,	 						 				// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_TANK,			// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_EXTERIOR_ROCKET_LAUNCH,				// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_ROCKET_LAUNCH,				// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_LIGHT_MISSILE_FLIGHT,					// continuous_sound_effect
			SPEECH_CPG_SWITCHING_TO_ROCKETS,								// weapon_selected_cpg_speech
			SPEECH_CPG_ROCKETS_LOW,											// weapon_low_cpg_speech
			SPEECH_CPG_ROCKETS_OUT,											// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_ROCKET,						// weapon_launched_wingman_speech
			5,																		// report_weapon_low_count
			FALSE,																// gun_shake
			600,																	// soft_damage_capability
			400,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			TRUE,							// acquire_parent_forward_velocity
			TRUE,		  					// ignore_gravity
			FALSE,							// survive_ground_impact
			TRUE,	 						// in_flight_collision_check
			TRUE,			  				// viewable_weapon
			TRUE,							// boresight_weapon
			FALSE,							// hellfire_flight_profile
			WEAPON_CLASS_AIR_TO_SURFACE,				// weapon_class

			11.3,																	// weight
			100.0,																// min_range
			4000.0,																// max_range
			600.0,																// effective_range
			100.0,	  															// min_range_loal
			4000.0,																// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			750.0,																// cruise_velocity
			30.0 * G,															// g_max
			2.379,																// burn_time
			4.065,																// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,		 															// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			0.0,																	// reload_time
			rad (0.1),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_S13
		//
		////////////////////////////////////////
		{
			"S-13",	  							  								// full_name
			"S-13", 																// hud_name
			"S-13",			 													// mfd_name
			"S-13",					  											// weapon_loading_list_name
			"S-13",					  											// weapon_loading_name_text

			OBJECT_3D_S13_MISSILE,		  									// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_TANK,			// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_EXTERIOR_ROCKET_LAUNCH,				// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_ROCKET_LAUNCH,				// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_HEAVY_MISSILE_FLIGHT,					// continuous_sound_effect
			SPEECH_CPG_SELECTING_ROCKETS,									// weapon_selected_cpg_speech
			SPEECH_CPG_ROCKETS_LOW,											// weapon_low_cpg_speech
			SPEECH_CPG_ROCKETS_OUT,											// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_ROCKET,						// weapon_launched_wingman_speech
			3,																		// report_weapon_low_count
			FALSE,																// gun_shake
			800,																	// soft_damage_capability
			550,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			TRUE,		  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			TRUE,			  														// viewable_weapon
			TRUE,	  																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_AIR_TO_SURFACE,									// weapon_class

			68.0,																	// weight
			100.0,																// min_range
			6000.0,																// max_range
			600.0,																// effective_range
			100.0, 																// min_range_loal
			6000.0,		  														// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			800.0,																// cruise_velocity
			30.0 * G,															// g_max
			2.548,																// burn_time
			6.146,																// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,																	// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			0.0,																	// reload_time
			rad (0.1),															// max_launch_angle_error
		},

		////////////////////////////////////////////////////////////////////////////////
		//
		// AIR-TO-AIR GUIDED MISSILES
		//
		////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_AIM92_STINGER
		//
		////////////////////////////////////////
		{
			"AIM-92 Stinger",					  								// full_name
			"AAM",		 														// hud_name
			"AAM",																// mfd_name
			"AIM-92",	  														// weapon_loading_list_name
			"AIM-92 Stinger",	  												// weapon_loading_name_text

			OBJECT_3D_AH64D_STINGER_MISSILE,	 							// default_3d_shape
			WEAPON_GUIDANCE_TYPE_PASSIVE_INFRA_RED,					// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE,							// warhead_type
			THREAT_TYPE_IR_MISSILE,											// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_STINGER1,				// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_STINGER2,				// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_LIGHT_MISSILE_FLIGHT,					// continuous_sound_effect
			SPEECH_CPG_SWITCHING_TO_STINGERS,							// weapon_selected_cpg_speech
			SPEECH_CPG_STINGERS_LOW,										// weapon_low_cpg_speech
			SPEECH_CPG_STINGERS_OUT,										// weapon_out_cpg_speech
			SPEECH_CPG_FIRING_STINGER,										// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_MISSILE,						// weapon_launched_wingman_speech
			1,																		// report_weapon_low_count
			FALSE,																// gun_shake
			550,																	// soft_damage_capability
			0,																		// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			TRUE,																	// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_AIR_TO_AIR,										// weapon_class

			13.6,																	// weight
			500.0,																// min_range
			5000.0,																// max_range
			2500.0,																// effective_range
			500.0,		 														// min_range_loal
			5000.0,																// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			680.0,																// cruise_velocity
			15.0 * G,															// g_max
			4.281,																// burn_time
			5.055,																// cruise_time
			0.0,																	// cruise_time_max_error
			1.0,		 															// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			0.0,																	// reload_time
			rad (40.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_AIM9M_SIDEWINDER
		//
		////////////////////////////////////////
		{
			"AIM-9M Sidewinder",					  							// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_AIM_9M,	 		 										// default_3d_shape
			WEAPON_GUIDANCE_TYPE_PASSIVE_INFRA_RED,					// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE,							// warhead_type
			THREAT_TYPE_IR_MISSILE,	 										// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_LIGHT_MISSILE_FLIGHT,					// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_MISSILE,						// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			1000,																	// soft_damage_capability
			0,																		// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			TRUE,			  														// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_AIR_TO_AIR,										// weapon_class

			0.0,																	// weight
			500.0,																// min_range
			18000.0,																// max_range
			5000.0,																// effective_range
			500.0,		 														// min_range_loal
			18000.0,	  															// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			850.0,																// cruise_velocity
			15.0 * G,															// g_max
			5.437,																// burn_time
			18.298,																// cruise_time
			0.0,																	// cruise_time_max_error
			1.0,	  																// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			0.0,																	// reload_time
			rad (40.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_AIM120_AMRAAM
		//
		////////////////////////////////////////
		{
			"AIM-120 AMRAAM",		 				  							// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_AMRAAM,	 		 										// default_3d_shape
			WEAPON_GUIDANCE_TYPE_ACTIVE_RADAR, 							// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE,							// warhead_type
			THREAT_TYPE_RF_MISSILE,											// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_LIGHT_MISSILE_FLIGHT,					// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_MISSILE,						// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			1400,																	// soft_damage_capability
			50,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			TRUE,			  														// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_AIR_TO_AIR,										// weapon_class

			0.0,																	// weight
			500.0,																// min_range
			65000.0,																// max_range
			5000.0,																// effective_range
			500.0,	  															// min_range_loal
			65000.0,		 														// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			1300.0,																// cruise_velocity
			15.0 * G,															// g_max
			8.495,																// burn_time
			45.589,																// cruise_time
			0.0,																	// cruise_time_max_error
			1.0,		 															// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			0.0,																	// reload_time
			rad (45.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_IGLA_V
		//
		////////////////////////////////////////
		{
			"Igla-V",			  				  								// full_name
			"Igla-V",		 													// hud_name
			"IGLA-V",  															// mfd_name
			"Igla",											  					// weapon_loading_list_name
			"Igla-V",										  					// weapon_loading_name_text

			OBJECT_3D_IGLA_MISSILE,	 										// default_3d_shape
			WEAPON_GUIDANCE_TYPE_PASSIVE_INFRA_RED, 					// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE,							// warhead_type
			THREAT_TYPE_IR_MISSILE,	 										// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_INTERIOR_MISSILE_LAUNCH,				// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_LIGHT_MISSILE_FLIGHT,					// continuous_sound_effect
			SPEECH_CPG_SELECTING_IGLA,										// weapon_selected_cpg_speech
			SPEECH_CPG_IGLAS_LOW,											// weapon_low_cpg_speech
			SPEECH_CPG_IGLAS_OUT,											// weapon_out_cpg_speech
			SPEECH_CPG_FIRING_IGLA,											// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_MISSILE,						// weapon_launched_wingman_speech
			2,																		// report_weapon_low_count
			FALSE,																// gun_shake
			550,																	// soft_damage_capability
			0,																		// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			TRUE,				 													// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_AIR_TO_AIR,										// weapon_class

			18.2,																	// weight
			500.0,																// min_range
			5200.0,																// max_range
			3000.0,																// effective_range
			500.0,																// min_range_loal
			5200.0,																// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			850.0,																// cruise_velocity
			15.0 * G,															// g_max
			5.437,																// burn_time
			3.239,																// cruise_time
			0.0,																	// cruise_time_max_error
			1.0,	  																// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			0.0,																	// reload_time
			rad (30.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_AA8A_APHID
		//
		////////////////////////////////////////
		{
			"AA-8A Aphid",						  								// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_APHID_MISSILE,	  									// default_3d_shape
			WEAPON_GUIDANCE_TYPE_PASSIVE_INFRA_RED,	  				// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE,							// warhead_type
			THREAT_TYPE_IR_MISSILE,											// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_LIGHT_MISSILE_FLIGHT,					// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_MISSILE,						// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			1132,																	// soft_damage_capability
			40,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			TRUE,				 													// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_AIR_TO_AIR,										// weapon_class

			0.0,																	// weight
			500.0,																// min_range
			10000.0,																// max_range
			5000.0,																// effective_range
			500.0,		 														// min_range_loal
			10000.0,																// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			1000.0,																// cruise_velocity
			15.0 * G,															// g_max
			6.456,																// burn_time
			6.611,																// cruise_time
			0.0,																	// cruise_time_max_error
			1.0,																	// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			0.0,																	// reload_time
			rad (30.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_AA8B_APHID
		//
		////////////////////////////////////////
		{
			"AA-8B Aphid",						  								// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_APHID_MISSILE,	  									// default_3d_shape
			WEAPON_GUIDANCE_TYPE_SEMI_ACTIVE_RADAR,					// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE,							// warhead_type
			THREAT_TYPE_RF_MISSILE,											// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_LIGHT_MISSILE_FLIGHT,					// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_MISSILE,						// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			1132,																	// soft_damage_capability
			40,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			TRUE,				 													// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_AIR_TO_AIR,										// weapon_class

			0.0,																	// weight
			500.0,																// min_range
			15000.0,																// max_range
			5000.0,																// effective_range
			500.0,		 														// min_range_loal
			15000.0,	  															// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			1000.0,																// cruise_velocity
			15.0 * G,															// g_max
			6.456,																// burn_time
			11.611,																// cruise_time
			0.0,																	// cruise_time_max_error
			1.0,		 															// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			0.0,																	// reload_time
			rad (30.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_AA10A_ALAMO
		//
		////////////////////////////////////////
		{
			"AA-10A Alamo",						  							// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_AA_10,	  	  											// default_3d_shape
			WEAPON_GUIDANCE_TYPE_SEMI_ACTIVE_RADAR,					// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE,							// warhead_type
			THREAT_TYPE_RF_MISSILE,											// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_LIGHT_MISSILE_FLIGHT,					// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_MISSILE,						// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			1220,																	// soft_damage_capability
			40,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			TRUE,				 													// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_AIR_TO_AIR,										// weapon_class

			0.0,																	// weight
			500.0,																// min_range
			40000.0,																// max_range
			5000.0,																// effective_range
			500.0,	  															// min_range_loal
			40000.0,		 														// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			1500.0,																// cruise_velocity
			15.0 * G,															// g_max
			9.854,																// burn_time
			21.575,																// cruise_time
			0.0,																	// cruise_time_max_error
			1.0,																	// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			0.0,																	// reload_time
			rad (30.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_AA10B_ALAMO
		//
		////////////////////////////////////////
		{
			"AA-10B Alamo",						  							// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_AA_10,	  	  											// default_3d_shape
			WEAPON_GUIDANCE_TYPE_PASSIVE_INFRA_RED,					// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE,							// warhead_type
			THREAT_TYPE_IR_MISSILE,											// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_LIGHT_MISSILE_FLIGHT,					// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_MISSILE,						// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			1250,																	// soft_damage_capability
			40,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			TRUE,			  														// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_AIR_TO_AIR,										// weapon_class

			1.0,																	// weight
			500.0,																// min_range
			20000.0,																// max_range
			5000.0,																// effective_range
			500.0,	  															// min_range_loal
			20000.0,																// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			1500.0,																// cruise_velocity
			15.0 * G,															// g_max
			9.854,																// burn_time
			8.242,																// cruise_time
			0.0,																	// cruise_time_max_error
			1.0,		 															// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			0.0,																	// reload_time
			rad (30.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_AA11_ARCHER
		//
		////////////////////////////////////////
		{
			"AA-11 Archer",													// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_AA_11_ARCHER_MISSILE,								// default_3d_shape
			WEAPON_GUIDANCE_TYPE_PASSIVE_INFRA_RED,					// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE,							// warhead_type
			THREAT_TYPE_IR_MISSILE,											// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_LIGHT_MISSILE_FLIGHT,					// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_MISSILE,						// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			1300,																	// soft_damage_capability
			40,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			TRUE,																	// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_AIR_TO_AIR,										// weapon_class

			1.0,																	// weight
			500.0,																// min_range
			30000.0,																// max_range
			5000.0,																// effective_range
			500.0,	  															// min_range_loal
			30000.0,																// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			850.0,																// cruise_velocity
			15.0 * G,															// g_max
			5.437,																// burn_time
			32.416,																// cruise_time
			0.0,																	// cruise_time_max_error
			1.0,																	// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			0.0,																	// reload_time
			rad (30.0),															// max_launch_angle_error
		},

		////////////////////////////////////////////////////////////////////////////////
		//
		// AIR-TO-SURFACE GUIDED MISSILES
		//
		////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_AGM114L_LONGBOW_HELLFIRE
		//
		////////////////////////////////////////
		{
			"AGM-114L Longbow Hellfire", 									// full_name
			"AGM(R)",			 												// hud_name
			"AGM(R)",															// mfd_name
			"AGM-114L",								  							// weapon_loading_list_name
			"AGM-114L Longbow Hellfire",		  							// weapon_loading_name_text

			OBJECT_3D_AH64D_HELLFIRE_MISSILE,	 						// default_3d_shape
			WEAPON_GUIDANCE_TYPE_ACTIVE_RADAR,							// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_TANK,			// warhead_type
			THREAT_TYPE_RF_MISSILE,											// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_INTERIOR_MISSILE_LAUNCH,				// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_HEAVY_MISSILE_FLIGHT,					// continuous_sound_effect
			SPEECH_CPG_SWITCHING_TO_HELLFIRES,							// weapon_selected_cpg_speech
			SPEECH_CPG_HELLFIRES_LOW,										// weapon_low_cpg_speech
			SPEECH_CPG_HELLFIRES_OUT,										// weapon_out_cpg_speech
			SPEECH_CPG_FIRING_HELLFIRE,									// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_MISSILE,						// weapon_launched_wingman_speech
			2,																		// report_weapon_low_count
			FALSE,																// gun_shake
			2000,																	// soft_damage_capability
			2000,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			TRUE,			  														// viewable_weapon
			FALSE,																// boresight_weapon
			TRUE,																	// hellfire_flight_profile
			WEAPON_CLASS_AIR_TO_SURFACE,									// weapon_class

			45.0,																	// weight
			500.0,																// min_range
			8000.0,																// max_range
			3000.0,																// effective_range
			1500.0,	  															// min_range_loal
			8000.0,			//X-PATCH//5000.0,			 				// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			442.0,																// cruise_velocity
			10.0 * G,															// g_max
			3.996,																// burn_time
			23.5,				//X-PATCH//15.876,							// cruise_time
			0.0,																	// cruise_time_max_error
			1.0,	  																// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			0.0,																	// reload_time
			rad (30.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_AGM114K_HELLFIRE_II
		//
		////////////////////////////////////////
		{
			"AGM-114K Hellfire II",											// full_name
			"AGM(L)",	 				 										// hud_name
			"AGM(L)",															// mfd_name
			"AGM-114K",								  							// weapon_loading_list_name
			"AGM-114K Hellfire II",				  							// weapon_loading_name_text

			OBJECT_3D_AH64D_HELLFIRE_MISSILE,	 						// default_3d_shape
			WEAPON_GUIDANCE_TYPE_SEMI_ACTIVE_LASER,					// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_TANK,			// warhead_type
			THREAT_TYPE_LASER_MISSILE,										// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_INTERIOR_MISSILE_LAUNCH,				// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_HEAVY_MISSILE_FLIGHT,					// continuous_sound_effect
			SPEECH_CPG_SELECTING_HELLFIRES,								// weapon_selected_cpg_speech
			SPEECH_CPG_HELLFIRES_LOW,										// weapon_low_cpg_speech
			SPEECH_CPG_HELLFIRES_OUT,										// weapon_out_cpg_speech
			SPEECH_CPG_FIRING_HELLFIRE,									// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_MISSILE,						// weapon_launched_wingman_speech
			2,																		// report_weapon_low_count
			FALSE,																// gun_shake
			2000,																	// soft_damage_capability
			2000,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			TRUE,																	// viewable_weapon
			FALSE,																// boresight_weapon
			TRUE,																	// hellfire_flight_profile
			WEAPON_CLASS_AIR_TO_SURFACE,									// weapon_class

			45.0,																	// weight
			500.0,																// min_range
			8000.0,																// max_range
			3000.0,																// effective_range
			1500.0,																// min_range_loal
			8000.0,			//X-PATCH//5000.0,							// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			442.0,																// cruise_velocity
			10.0 * G,															// g_max
			3.996,																// burn_time
			23.5,				//X-PATCH//15.876,							// cruise_time
			0.0,																	// cruise_time_max_error
			1.0,			  														// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			0.0,																	// reload_time
			rad (30.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_AGM65D_MAVERICK
		//
		////////////////////////////////////////
		{
			"AGM-65D Maverick", 												// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_MAVERICK,	  											// default_3d_shape
			WEAPON_GUIDANCE_TYPE_PASSIVE_INFRA_RED,					// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_TANK,			// warhead_type
			THREAT_TYPE_IR_MISSILE,											// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_HEAVY_MISSILE_FLIGHT,					// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_MISSILE,						// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			3000,																	// soft_damage_capability
			3000,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			TRUE,				 													// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_AIR_TO_SURFACE,									// weapon_class

			0.0,																	// weight
			500.0,																// min_range
			24000.0,																// max_range
			6000.0,																// effective_range
			500.0,	  															// min_range_loal
			24000.0,		 														// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			340.0,																// cruise_velocity
			5.0 * G,																// g_max
			5.912,																// burn_time
			67.197,																// cruise_time
			0.0,																	// cruise_time_max_error
			1.0,		 															// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			0.0,																	// reload_time
			rad (10.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_AGM65F_MAVERICK
		//
		////////////////////////////////////////
		{
			"AGM-65F Maverick", 												// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_MAVERICK,	  											// default_3d_shape
			WEAPON_GUIDANCE_TYPE_PASSIVE_INFRA_RED,					// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_TANK,			// warhead_type
			THREAT_TYPE_IR_MISSILE,											// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_HEAVY_MISSILE_FLIGHT,					// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_MISSILE,						// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			3000,																	// soft_damage_capability
			3000,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			TRUE,			  														// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_AIR_TO_SURFACE,									// weapon_class

			0.0,																	// weight
			500.0,																// min_range
			24000.0,																// max_range
			6000.0,																// effective_range
			500.0,			  													// min_range_loal
			24000.0,																// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			340.0,																// cruise_velocity
			5.0 * G,																// g_max
			5.912,																// burn_time
			67.197,																// cruise_time
			0.0,																	// cruise_time_max_error
			1.0,		 															// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			0.0,																	// reload_time
			rad (10.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_ATAKA
		//
		////////////////////////////////////////
		{
			"Ataka",				 				 								// full_name
			"Ataka",	  															// hud_name
			"?",																	// mfd_name
			"Ataka",													 			// weapon_loading_list_name
			"Ataka",													 			// weapon_loading_name_text

			OBJECT_3D_ATAKA_MISSILE,	  									// default_3d_shape
			WEAPON_GUIDANCE_TYPE_RADIO_COMMAND,							// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_TANK,			// warhead_type
			THREAT_TYPE_RF_MISSILE,											// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_ATAKA1,				                    // interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_ATAKA2,				                    // exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_HEAVY_MISSILE_FLIGHT,					// continuous_sound_effect
			SPEECH_CPG_SELECTING_ATAKA,									// weapon_selected_cpg_speech
			SPEECH_CPG_ATAKAS_LOW,											// weapon_low_cpg_speech
			SPEECH_CPG_ATAKAS_OUT,											// weapon_out_cpg_speech
			SPEECH_CPG_FIRING_ATAKA,										// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_MISSILE,						// weapon_launched_wingman_speech
			2,																		// report_weapon_low_count
			FALSE,																// gun_shake
			2000,																	// soft_damage_capability
			2000,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			TRUE,				 													// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_AIR_TO_SURFACE,									// weapon_class

			42.5,																	// weight
			500.0,																// min_range
			6000.0,																// max_range
			3000.0,																// effective_range
			500.0,		 														// min_range_loal
			6000.0,			 													// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			400.0,																// cruise_velocity
			10.0 * G,															// g_max
			3.568,																// burn_time
			12.993,																// cruise_time
			0.0,																	// cruise_time_max_error
			1.0,	  																// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			0.0,																	// reload_time
			rad (25.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_VIKHR
		//
		////////////////////////////////////////
		{
			"Vikhr",				 				 								// full_name
			"Vikhr",				  												// hud_name
			"VIKHR",																// mfd_name
			"Vikhr",				  												// weapon_loading_list_name
			"Vikhr",				  												// weapon_loading_name_text

			OBJECT_3D_VIKHR_MISSILE,	  									// default_3d_shape
			WEAPON_GUIDANCE_TYPE_SEMI_ACTIVE_LASER,					// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_TANK,			// warhead_type
			THREAT_TYPE_LASER_MISSILE,										// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
		    SOUND_SAMPLE_INDEX_ATAKA1,				                    // interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_ATAKA2,				                    // exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_HEAVY_MISSILE_FLIGHT,					// continuous_sound_effect
			SPEECH_CPG_SWITCHING_TO_VIKHR,								// weapon_selected_cpg_speech
			SPEECH_CPG_VIKHRS_LOW,											// weapon_low_cpg_speech
			SPEECH_CPG_VIKHRS_OUT,											// weapon_out_cpg_speech
			SPEECH_CPG_FIRING_VIKHR,										// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_MISSILE,						// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			2000,																	// soft_damage_capability
			2000,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			TRUE,			  														// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_AIR_TO_SURFACE,									// weapon_class

			45.0,																	// weight
			500.0,																// min_range
			10000.0,																// max_range
			3000.0,																// effective_range
			500.0,			  													// min_range_loal
			10000.0,																// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			400.0,																// cruise_velocity
			10.0 * G,															// g_max
			3.568,																// burn_time
			22.993,																// cruise_time
			0.0,																	// cruise_time_max_error
			1.0,	  																// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			0.0,																	// reload_time
			rad (25.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_AT6_SPIRAL
		//
		////////////////////////////////////////
		{
			"AT-6 Spiral",				 				 						// full_name
			"AT-6 Spiral",																	// hud_name
			"AT-6 Spiral",																	// mfd_name
			"AT-6 Spiral",																	// weapon_loading_list_name
			"AT-6 Spiral",																	// weapon_loading_name_text

			OBJECT_3D_AT6_MISSILE,	  										// default_3d_shape
			WEAPON_GUIDANCE_TYPE_RADIO_COMMAND,							// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_TANK,			// warhead_type
			THREAT_TYPE_RF_MISSILE,											// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_HEAVY_MISSILE_FLIGHT,					// continuous_sound_effect
			-1,								// weapon_selected_cpg_speech
			-1,									// weapon_low_cpg_speech
			-1,								// weapon_out_cpg_speech
			-1,								// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_MISSILE,				// weapon_launched_wingman_speech
			0,								// report_weapon_low_count
			FALSE,								// gun_shake
			744,								// soft_damage_capability
			744,								// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			TRUE,								// acquire_parent_forward_velocity
			FALSE,	  							// ignore_gravity
			FALSE,								// survive_ground_impact
			TRUE,	 							// in_flight_collision_check
			TRUE,			  					// viewable_weapon
			FALSE,								// boresight_weapon
			FALSE,								// hellfire_flight_profile
			WEAPON_CLASS_AIR_TO_SURFACE,					// weapon_class

			0.0,								// weight
			500.0,								// min_range
			7000.0,								// max_range
			3000.0,								// effective_range
			500.0,		 						// min_range_loal
			7000.0,		  						// max_range_loal
			0.0,							// max_range_error_ratio
			50.0,								// muzzle_velocity
			0.0,							// muzzle_velocity_max_error
			340.0,							// cruise_velocity
			10.0 * G,							// g_max
			2.956,							// burn_time
			18.893,							// cruise_time
			0.0,							// cruise_time_max_error
			1.0,		 					// inhibit_time
			0.0,							// burst_duration
			FIRE_SINGLE_WEAPON,					// rate_of_fire
			0.0,							// reload_time
			rad (20.0),						// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_AS10_KAREN
		//
		////////////////////////////////////////
		{
			"AS-10 Karen",				 				 						// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_AS_10_KAREN_MISSILE,								// default_3d_shape
			WEAPON_GUIDANCE_TYPE_PASSIVE_INFRA_RED,					// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_TANK,			// warhead_type
			THREAT_TYPE_IR_MISSILE,											// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_HEAVY_MISSILE_FLIGHT,					// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_MISSILE,						// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			1000,																	// soft_damage_capability
			1000,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			TRUE,																	// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_AIR_TO_SURFACE,									// weapon_class

			0.0,																	// weight
			500.0,																// min_range
			10000.0,																// max_range
			4000.0,																// effective_range
			500.0,			  													// min_range_loal
			10000.0,		 														// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			340.0,																// cruise_velocity
			5.0 * G,			 													// g_max
			5.912,																// burn_time
			26.021,																// cruise_time
			0.0,																	// cruise_time_max_error
			1.0,		 															// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			0.0,																	// reload_time
			rad (10.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_AS14_KEDGE
		//
		////////////////////////////////////////
		{
			"AS-14 Kedge",				 				 						// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_AS_14,	  	  											// default_3d_shape
			WEAPON_GUIDANCE_TYPE_SEMI_ACTIVE_LASER,					// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_TANK,			// warhead_type
			THREAT_TYPE_LASER_MISSILE,										// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_HEAVY_MISSILE_FLIGHT,					// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			WEAPON_LAUNCH_WINGMAN_SPEECH_MISSILE,						// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			6354,																	// soft_damage_capability
			6354,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			TRUE,				 													// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_AIR_TO_SURFACE,									// weapon_class

			0.0,																	// weight
			500.0,																// min_range
			40000.0,																// max_range
			6000.0,																// effective_range
			500.0,	  															// min_range_loal
			40000.0,																// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			340.0,																// cruise_velocity
			5.0 * G,						 										// g_max
			5.912,																// burn_time
			114.256,																// cruise_time
			0.0,																	// cruise_time_max_error
			1.0,	  																// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			0.0,																	// reload_time
			rad (10.0),															// max_launch_angle_error
		},

		////////////////////////////////////////////////////////////////////////////////
		//
		// SURFACE-TO-AIR GUIDED MISSILES
		//
		////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_CHAPARRAL
		//
		////////////////////////////////////////
		{
			"Chaparral",						  								// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_CHAPARRAL,	 											// default_3d_shape
			WEAPON_GUIDANCE_TYPE_PASSIVE_INFRA_RED,					// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE,							// warhead_type
			THREAT_TYPE_IR_MISSILE,											// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_CHAPARRAL,				// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_CHAPARRAL,				// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_LIGHT_MISSILE_FLIGHT,					// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			-1,																	// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			300,																	// soft_damage_capability
			0,																		// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			TRUE,				 													// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_SURFACE_TO_AIR,									// weapon_class

			0.0,																	// weight
			500.0,																// min_range
			5000.0,																// max_range
			3500.0,																// effective_range
			500.0,		 														// min_range_loal
			5000.0,	 															// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			850.0,																// cruise_velocity
			15.0 * G,															// g_max
			5.437,																// burn_time
			3.004,																// cruise_time
			0.0,																	// cruise_time_max_error
			1.0,																	// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			25.0,																	// reload_time
			rad (60.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_FIM92A_STINGER
		//
		////////////////////////////////////////
		{
			"FIM-92A Stinger",				  								// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_AH64D_STINGER_MISSILE,	  							// default_3d_shape
			WEAPON_GUIDANCE_TYPE_PASSIVE_INFRA_RED,					// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE,							// warhead_type
			THREAT_TYPE_IR_MISSILE,											// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_LIGHT_MISSILE_FLIGHT,					// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			-1,																	// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			300,																	// soft_damage_capability
			0,																		// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			TRUE,																	// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_SURFACE_TO_AIR,									// weapon_class

			0.0,																	// weight
			500.0,																// min_range
			5000.0,																// max_range
			3500.0,																// effective_range
			500.0,	  															// min_range_loal
			5000.0,																// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			680.0,																// cruise_velocity
			15.0 * G,															// g_max
			4.281,																// burn_time
			5.055,																// cruise_time
			0.0,																	// cruise_time_max_error
			1.0,																	// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			25.0,																	// reload_time
			rad (40.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_SM1MR_STANDARD
		//
		////////////////////////////////////////
		{
			"SM-1MR Standard",												// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_STANDARD_MISSILE,	 	 							// default_3d_shape
			WEAPON_GUIDANCE_TYPE_SEMI_ACTIVE_RADAR,					// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE,							// warhead_type
			THREAT_TYPE_RF_MISSILE,											// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_LIGHT_MISSILE_FLIGHT,					// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			-1,																	// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			300,																	// soft_damage_capability
			0,																		// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			TRUE,			  														// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_SURFACE_TO_AIR,									// weapon_class

			0.0,																	// weight
			500.0,																// min_range
			30000.0,																// max_range
			15000.0,																// effective_range
			500.0,				 												// min_range_loal
			30000.0,																// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			850.0,																// cruise_velocity
			10.0 * G,															// g_max
			8.155,																// burn_time
			30.977,																// cruise_time
			0.0,																	// cruise_time_max_error
			1.0,																	// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			25.0,																	// reload_time
			rad (60.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_SEA_SPARROW
		//
		////////////////////////////////////////
		{
			"Sea Sparrow",														// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_SPARROW_MISSILE,	 		 							// default_3d_shape
			WEAPON_GUIDANCE_TYPE_SEMI_ACTIVE_RADAR,					// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE,							// warhead_type
			THREAT_TYPE_RF_MISSILE,											// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_LIGHT_MISSILE_FLIGHT,					// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			-1,																	// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			300,																	// soft_damage_capability
			0,																		// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			TRUE,																	// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_SURFACE_TO_AIR,									// weapon_class

			0.0,																	// weight
			500.0,																// min_range
			55000.0,																// max_range
			15000.0,																// effective_range
			500.0,	  															// min_range_loal
			55000.0,																// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			850.0,																// cruise_velocity
			10.0 * G,															// g_max
			8.155,																// burn_time
			60.389,																// cruise_time
			0.0,																	// cruise_time_max_error
			1.0,																	// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			25.0,																	// reload_time
			rad (60.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_SA7_GRAIL
		//
		////////////////////////////////////////
		{
			"SA-7 Grail",		  				  								// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_STRELA_MISSILE,	  	 								// default_3d_shape
			WEAPON_GUIDANCE_TYPE_PASSIVE_INFRA_RED,					// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE,							// warhead_type
			THREAT_TYPE_IR_MISSILE,											// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_LIGHT_MISSILE_FLIGHT,					// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			-1,																	// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			300,																	// soft_damage_capability
			0,																		// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			TRUE,			  														// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_SURFACE_TO_AIR,									// weapon_class

			0.0,																	// weight
			500.0,																// min_range
			3200.0,																// max_range
			2000.0,																// effective_range
			500.0,	  															// min_range_loal
			3200.0,																// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			510.0,																// cruise_velocity
			15.0 * G,															// g_max
			3.126,																// burn_time
			4.558,																// cruise_time
			0.0,																	// cruise_time_max_error
			1.0,																	// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			25.0,																	// reload_time
			rad (30.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_SA13_GOPHER
		//
		////////////////////////////////////////
		{
			"SA-13 Gopher",		 			  								// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_SA_13_MISSILE,										// default_3d_shape
			WEAPON_GUIDANCE_TYPE_PASSIVE_INFRA_RED,					// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE,							// warhead_type
			THREAT_TYPE_IR_MISSILE,											// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_CHAPARRAL,				                // interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_CHAPARRAL,				                // exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_LIGHT_MISSILE_FLIGHT,					// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			-1,																	// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			400,																	// soft_damage_capability
			0,																		// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			TRUE,			  														// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_SURFACE_TO_AIR,									// weapon_class

			0.0,																	// weight
			500.0,																// min_range
			5000.0,																// max_range
			3500.0,																// effective_range
			500.0,		 														// min_range_loal
			5000.0,	  															// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			510.0,																// cruise_velocity
			10.0 * G,															// g_max
			4.689,																// burn_time
			7.230,																// cruise_time
			0.0,																	// cruise_time_max_error
			1.0,																	// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			25.0,																	// reload_time
			rad (25.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_SA19_GRISON
		//
		////////////////////////////////////////
		{
			"SA-19 Grison SAM",	 			  								// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_SA19_MISSILE,											// default_3d_shape
			WEAPON_GUIDANCE_TYPE_RADIO_COMMAND,							// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE,							// warhead_type
			THREAT_TYPE_RF_MISSILE,											// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_LIGHT_MISSILE_FLIGHT,					// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			-1,																	// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			450,																	// soft_damage_capability
			0,																		// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			TRUE,			  														// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_SURFACE_TO_AIR,									// weapon_class

			0.0,																	// weight
			500.0,																// min_range
			8000.0,																// max_range
			5000.0,																// effective_range
			500.0,		 														// min_range_loal
			8000.0, 																// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			890.0,																// cruise_velocity
			15.0 * G,															// g_max
			5.708,																// burn_time
			5.974,																// cruise_time
			0.0,																	// cruise_time_max_error
			1.0,	  																// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			25.0,																	// reload_time
			rad (60.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_SAN3_GOBLET
		//
		////////////////////////////////////////
		{
			"SA-N-3 Goblet",													// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_SA_N_3_MISSILE,										// default_3d_shape
			WEAPON_GUIDANCE_TYPE_RADIO_COMMAND,							// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE,							// warhead_type
			THREAT_TYPE_RF_MISSILE,											// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_LIGHT_MISSILE_FLIGHT,					// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			-1,																	// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			350,																	// soft_damage_capability
			0,																		// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			TRUE,						 											// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_SURFACE_TO_AIR,									// weapon_class

			0.0,																	// weight
			500.0,																// min_range
			24000.0,																// max_range
			12000.0,																// effective_range
			500.0,																// min_range_loal
			24000.0,																// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			952.0,																// cruise_velocity
			10.0 * G,															// g_max
			9.195,																// burn_time
			20.371,																// cruise_time
			0.0,																	// cruise_time_max_error
			1.0,																	// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			25.0,																	// reload_time
			rad (45.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_SAN4_GECKO
		//
		////////////////////////////////////////
		{
			"SA-N-4 Gecko",													// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_SA_N_4_MISSILE,										// default_3d_shape
			WEAPON_GUIDANCE_TYPE_RADIO_COMMAND,							// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE,							// warhead_type
			THREAT_TYPE_RF_MISSILE,											// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_MISSILE_LAUNCH,				// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_LIGHT_MISSILE_FLIGHT,					// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			-1,																	// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			400,																	// soft_damage_capability
			0,																		// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			TRUE,			  														// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_SURFACE_TO_AIR,									// weapon_class

			0.0,																	// weight
			500.0,																// min_range
			12000.0,																// max_range
			8000.0,																// effective_range
			500.0,																// min_range_loal
			12000.0,		 														// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			850.0,																// cruise_velocity
			10.0 * G,															// g_max
			8.155,			 													// burn_time
			9.800,			 													// cruise_time
			0.0,																	// cruise_time_max_error
			1.0,	  																// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			24.0,																	// reload_time
			rad (45.0),															// max_launch_angle_error
		},

		////////////////////////////////////////////////////////////////////////////////
		//
		// SURFACE-TO-SURFACE GUIDED MISSILES
		//
		////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_M220_TOW2B
		//
		////////////////////////////////////////
		{
			"M220 TOW2B", 														// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_TOW_MISSILE,											// default_3d_shape
			WEAPON_GUIDANCE_TYPE_WIRE_GUIDED,							// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_TANK,			// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_EXTERIOR_ROCKET_LAUNCH,				// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_ROCKET_LAUNCH,				// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_HEAVY_MISSILE_FLIGHT,					// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			-1,																	// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			1017,																	// soft_damage_capability
			1017,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			TRUE,			  														// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_SURFACE_TO_SURFACE,								// weapon_class

			0.0,																	// weight
			100.0,																// min_range
			3750.0,																// max_range
			3000.0,																// effective_range
			100.0,		 														// min_range_loal
			3750.0, 																// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			300.0,																// cruise_velocity
			5.0 * G,																// g_max
			5.097,																// burn_time
			9.527,																// cruise_time
			0.0,																	// cruise_time_max_error
			1.0,	  																// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			30.0,																	// reload_time
			rad (30.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_AT5_SPANDREL
		//
		////////////////////////////////////////
		{
			"AT-5 Spandrel", 	 												// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_AT5_SPANDREL_MISSILE,				 				// default_3d_shape
			WEAPON_GUIDANCE_TYPE_SEMI_ACTIVE_RADAR,					// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_TANK,			// warhead_type
			THREAT_TYPE_RF_MISSILE,											// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_EXTERIOR_ROCKET_LAUNCH,				// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_ROCKET_LAUNCH,				// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_HEAVY_MISSILE_FLIGHT,					// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			-1,																	// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			802,																	// soft_damage_capability
			802,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			TRUE,			  														// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_SURFACE_TO_SURFACE,								// weapon_class

			0.0,																	// weight
			100.0,																// min_range
			4000.0,																// max_range
			3000.0,																// effective_range
			100.0,																// min_range_loal
			4000.0,																// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			300.0,																// cruise_velocity
			5.0 * G,																// g_max
			5.097,																// burn_time
			10.360,																// cruise_time
			0.0,																	// cruise_time_max_error
			1.0,		 															// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			30.0,																	// reload_time
			rad (15.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_AT10_STABBER
		//
		////////////////////////////////////////
		{
			"AT-10 Stabber",													// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_AT10_STABBER_MISSILE,								// default_3d_shape
			WEAPON_GUIDANCE_TYPE_SEMI_ACTIVE_LASER_BEAM_RIDING,	// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_TANK,			// warhead_type
			THREAT_TYPE_LASER_MISSILE,										// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_EXTERIOR_ROCKET_LAUNCH,				// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_ROCKET_LAUNCH,				// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_HEAVY_MISSILE_FLIGHT,					// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			-1,																	// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			440,																	// soft_damage_capability
			440,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			TRUE,			  														// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_SURFACE_TO_SURFACE,								// weapon_class

			0.0,																	// weight
			100.0,																// min_range
			5000.0,																// max_range
			3000.0,																// effective_range
			100.0,		 														// min_range_loal
			5000.0,																// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			300.0,																// cruise_velocity
			5.0 * G,																// g_max
			5.097,																// burn_time
			13.694,																// cruise_time
			0.0,																	// cruise_time_max_error
			1.0,	  																// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			30.0,																	// reload_time
			rad (20.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_AT11_SNIPER
		//
		////////////////////////////////////////
		{
			"AT-11 Sniper", 	 		 										// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_AT11_SNIPER_MISSILE,	  							// default_3d_shape
			WEAPON_GUIDANCE_TYPE_SEMI_ACTIVE_LASER_BEAM_RIDING,	// guidance_type
			WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT,					// aiming_type
			WEAPON_DECOY_TYPE_NONE,											// decoy_type
			WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_TANK,			// warhead_type
			THREAT_TYPE_LASER_MISSILE,										// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_EXTERIOR_ROCKET_LAUNCH,				// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_ROCKET_LAUNCH,				// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_HEAVY_MISSILE_FLIGHT,					// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			-1,																	// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			688,																	// soft_damage_capability
			688,																	// hard_damage_capability
			META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL,				// smoke_trail_type
			TRUE,																	// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			TRUE,		  															// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_SURFACE_TO_SURFACE,								// weapon_class

			0.0,																	// weight
			100.0,																// min_range
			4000.0,																// max_range
			3000.0,																// effective_range
			100.0,																// min_range_loal
			4000.0,			 													// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			300.0,																// cruise_velocity
			5.0 * G,		 														// g_max
			5.097,																// burn_time
			10.360,																// cruise_time
			0.0,																	// cruise_time_max_error
			1.0,																	// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			30.0,																	// reload_time
			rad (20.0),															// max_launch_angle_error
		},

		////////////////////////////////////////////////////////////////////////////////
		//
		// DECOYS
		//
		////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_CHAFF
		//
		////////////////////////////////////////
		{
			"CHAFF",	  							  								// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_EFFECT_CHAFF_1,										// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_NONE,										// aiming_type
			WEAPON_DECOY_TYPE_CHAFF,  										// decoy_type
			WEAPON_WARHEAD_TYPE_NONE,										// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_INTERIOR_CHAFF,							// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_CHAFF,							// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_NONE,										// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			SPEECH_CPG_CHAFF_LOW,											// weapon_low_cpg_speech
			SPEECH_CPG_CHAFF_OUT,											// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			-1,																	// weapon_launched_wingman_speech
			10,																	// report_weapon_low_count
			FALSE,																// gun_shake
			0,																		// soft_damage_capability
			0,																		// hard_damage_capability
			META_SMOKE_LIST_TYPE_NONE,										// smoke_trail_type
			FALSE,	 															// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			FALSE,	 															// in_flight_collision_check
			FALSE,																// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_DECOY,												// weapon_class

			0.0,																	// weight
			0.0,		 															// min_range
			0.0,																	// max_range
			0.0,																	// effective_range
			0.0,																	// min_range_loal
			0.0,																	// max_range_loal
			0.0,																	// max_range_error_ratio
			20.0,																	// muzzle_velocity
			5.0,																	// muzzle_velocity_max_error
			25.0,		 															// cruise_velocity
			0.0 * G,	  															// g_max
			0.0,																	// burn_time
			3.0,		  															// cruise_time
			2.0,																	// cruise_time_max_error
			0.0,																	// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			0.0,																	// reload_time
			rad (0.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_FLARE
		//
		////////////////////////////////////////
		{
			"FLARE",	  							  								// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_INVALID_OBJECT_INDEX,								// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_NONE,										// aiming_type
			WEAPON_DECOY_TYPE_FLARE,	 									// decoy_type
			WEAPON_WARHEAD_TYPE_NONE,										// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_INTERIOR_FLARE,							// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_EXTERIOR_FLARE,							// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_NONE,										// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			SPEECH_CPG_FLARES_LOW,											// weapon_low_cpg_speech
			SPEECH_CPG_FLARES_OUT,											// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			-1,																	// weapon_launched_wingman_speech
			10,																	// report_weapon_low_count
			FALSE,																// gun_shake
			0,																		// soft_damage_capability
			0,																		// hard_damage_capability
			META_SMOKE_LIST_TYPE_DECOY_FLARE_TRAIL,					// smoke_trail_type
			FALSE,	 															// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			FALSE, 																// in_flight_collision_check
			FALSE,																// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_DECOY,												// weapon_class

			0.0,																	// weight
			0.0,		 															// min_range
			0.0,																	// max_range
			0.0,																	// effective_range
			0.0,																	// min_range_loal
			0.0,																	// max_range_loal
			0.0,																	// max_range_error_ratio
			40.0,																	// muzzle_velocity
			10.0,																	// muzzle_velocity_max_error
			50.0,		 															// cruise_velocity
			0.0 * G,	  															// g_max
			0.0,																	// burn_time
			3.0,		  															// cruise_time
			2.0,																	// cruise_time_max_error
			0.0,																	// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			0.0,																	// reload_time
			rad (0.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_SMOKE_GRENADE
		//
		////////////////////////////////////////
		{
			"SMOKE GRENADE",					  								// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_INVALID_OBJECT_INDEX,								// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_NONE,										// aiming_type
			WEAPON_DECOY_TYPE_SMOKE_GRENADE,								// decoy_type
			WEAPON_WARHEAD_TYPE_SMOKE_GRENADE,							// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_SMOKEGRENADE,								// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_SMOKEGRENADE,								// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_NONE,										// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			-1,																	// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			0,																		// soft_damage_capability
			0,																		// hard_damage_capability
			META_SMOKE_LIST_TYPE_NONE,										// smoke_trail_type
			FALSE,	 															// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			TRUE,																	// survive_ground_impact
			FALSE,	 															// in_flight_collision_check
			FALSE,																// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_DECOY,												// weapon_class

			0.0,																	// weight
			0.0,		 															// min_range
			0.0,																	// max_range
			0.0,																	// effective_range
			0.0,																	// min_range_loal
			0.0,																	// max_range_loal
			0.0,																	// max_range_error_ratio
			6.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			6.0,		 															// cruise_velocity
			0.0 * G,	  															// g_max
			0.0,																	// burn_time
			45.0,		  															// cruise_time
			15.0,																	// cruise_time_max_error
			0.0,																	// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			0.0,																	// reload_time
			rad (0.0),															// max_launch_angle_error
		},

		////////////////////////////////////////////////////////////////////////////////
		//
		// CARGO
		//
		////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_CRATE
		//
		////////////////////////////////////////
		{
			"CRATE",																// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_C130_CRATE_WEAPON,									// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_NONE,										// aiming_type
			WEAPON_DECOY_TYPE_NONE,			 								// decoy_type
			WEAPON_WARHEAD_TYPE_NONE,										// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_NONE,										// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_NONE,										// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_NONE,										// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			-1,																	// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			0,																		// soft_damage_capability
			0,																		// hard_damage_capability
			META_SMOKE_LIST_TYPE_NONE,										// smoke_trail_type
			FALSE,																// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			TRUE,																	// survive_ground_impact
			FALSE,	 															// in_flight_collision_check
			FALSE,																// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_CARGO,												// weapon_class

			0.0,																	// weight
			0.0,		 															// min_range
			0.0,																	// max_range
			0.0,																	// effective_range
			0.0,																	// min_range_loal
			0.0,																	// max_range_loal
			0.0,																	// max_range_error_ratio
			0.0,																	// muzzle_velocity
			0.0,																	// muzzle_velocity_max_error
			0.0,		 															// cruise_velocity
			0.0 * G,	  															// g_max
			0.0,																	// burn_time
			MAX_CRUISE_TIME,													// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,																	// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			0.0,																	// reload_time
			rad (0.0),															// max_launch_angle_error
		},

		////////////////////////////////////////////////////////////////////////////////
		//
		// DEBRIS
		//
		////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_HOKUM_BLADE
		//
		////////////////////////////////////////
		{
			"Rotor Blade",														// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_KA52_ROTOR_WEAPON,									// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_NONE,										// aiming_type
			WEAPON_DECOY_TYPE_NONE,			 								// decoy_type
			WEAPON_WARHEAD_TYPE_BALL,										// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_NONE,										// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_NONE,										// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_NONE,										// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			-1,																	// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			550,																	// soft_damage_capability
			0,																		// hard_damage_capability
			META_SMOKE_LIST_TYPE_NONE,										// smoke_trail_type
			FALSE,																// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			FALSE,																// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_DEBRIS,												// weapon_class

			0.0,																	// weight
			0.0,		 															// min_range
			0.0,																	// max_range
			0.0,																	// effective_range
			0.0,																	// min_range_loal
			0.0,																	// max_range_loal
			0.0,																	// max_range_error_ratio
			15.0,																	// muzzle_velocity
			5.0,																	// muzzle_velocity_max_error
			20.0,		 															// cruise_velocity
			0.0 * G,	  															// g_max
			0.0,																	// burn_time
			10.0,		  															// cruise_time
			5.0,																	// cruise_time_max_error
			0.0,																	// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			0.0,																	// reload_time
			rad (0.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_HOKUM_PILOT
		//
		////////////////////////////////////////
		{
			"Ejected Pilot",													// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_KA52_PILOT_SEAT_WEAPON,							// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_NONE,										// aiming_type
			WEAPON_DECOY_TYPE_NONE,			 								// decoy_type
			WEAPON_WARHEAD_TYPE_BALL,										// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_INTERIOR_MISSILE_LAUNCH,					                    // interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_INTERIOR_MISSILE_LAUNCH,					                    // exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_LIGHT_MISSILE_FLIGHT,					// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			-1,																	// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			550,																	// soft_damage_capability
			0,																		// hard_damage_capability
			META_SMOKE_LIST_TYPE_SMALL_ROCKET_TRAIL,					// smoke_trail_type
			FALSE,																// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			FALSE,																// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_DEBRIS,												// weapon_class

			0.0,																	// weight
			0.0,		 															// min_range
			0.0,																	// max_range
			0.0,																	// effective_range
			0.0,																	// min_range_loal
			0.0,																	// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			10.0,																	// muzzle_velocity_max_error
			60.0,		 															// cruise_velocity
			0.0 * G,	  															// g_max
			0.0,																	// burn_time
			MAX_CRUISE_TIME,													// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,																	// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			0.0,																	// reload_time
			rad (0.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_HOKUM_CO_PILOT
		//
		////////////////////////////////////////
		{
			"Ejected Co-pilot",												// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_KA52_WSO_SEAT_WEAPON,								// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_NONE,										// aiming_type
			WEAPON_DECOY_TYPE_NONE,			 								// decoy_type
			WEAPON_WARHEAD_TYPE_BALL,										// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_INTERIOR_MISSILE_LAUNCH,					                    // interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_INTERIOR_MISSILE_LAUNCH,					                    // exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_LIGHT_MISSILE_FLIGHT,					// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			-1,																	// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			550,																	// soft_damage_capability
			0,																		// hard_damage_capability
			META_SMOKE_LIST_TYPE_SMALL_ROCKET_TRAIL,					// smoke_trail_type
			FALSE,																// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			FALSE,																// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_DEBRIS,												// weapon_class

			0.0,																	// weight
			0.0,		 															// min_range
			0.0,																	// max_range
			0.0,																	// effective_range
			0.0,																	// min_range_loal
			0.0,																	// max_range_loal
			0.0,																	// max_range_error_ratio
			50.0,																	// muzzle_velocity
			10.0,																	// muzzle_velocity_max_error
			60.0,		 															// cruise_velocity
			0.0 * G,	  															// g_max
			0.0,																	// burn_time
			MAX_CRUISE_TIME,													// cruise_time
			0.0,																	// cruise_time_max_error
			0.0,																	// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			0.0,																	// reload_time
			rad (0.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_HOKUM_LH_DOOR
		//
		////////////////////////////////////////
		{
			"Crew Door",														// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_KA52_DOOR_LHS_WEAPON,								// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_NONE,										// aiming_type
			WEAPON_DECOY_TYPE_NONE,			 								// decoy_type
			WEAPON_WARHEAD_TYPE_BALL,										// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_HEAVY_ARTILLERY,							// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_HEAVY_ARTILLERY,							// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_NONE,										// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			-1,																	// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			550,																	// soft_damage_capability
			0,																		// hard_damage_capability
			META_SMOKE_LIST_TYPE_NONE,										// smoke_trail_type
			FALSE,																// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			FALSE,																// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_DEBRIS,												// weapon_class

			0.0,																	// weight
			0.0,		 															// min_range
			0.0,																	// max_range
			0.0,																	// effective_range
			0.0,																	// min_range_loal
			0.0,																	// max_range_loal
			0.0,																	// max_range_error_ratio
			6.0,																	// muzzle_velocity
			2.0,																	// muzzle_velocity_max_error
			8.0,		 															// cruise_velocity
			0.0 * G,	  															// g_max
			0.0,																	// burn_time
			10.0,		  															// cruise_time
			5.0,																	// cruise_time_max_error
			0.0,																	// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			0.0,																	// reload_time
			rad (0.0),															// max_launch_angle_error
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_WEAPON_HOKUM_RH_DOOR
		//
		////////////////////////////////////////
		{
			"Crew Door",														// full_name
			"?",																	// hud_name
			"?",																	// mfd_name
			"?",																	// weapon_loading_list_name
			"?",																	// weapon_loading_name_text

			OBJECT_3D_KA52_DOOR_RHS_WEAPON,								// default_3d_shape
			WEAPON_GUIDANCE_TYPE_NONE,										// guidance_type
			WEAPON_AIMING_TYPE_NONE,										// aiming_type
			WEAPON_DECOY_TYPE_NONE,			 								// decoy_type
			WEAPON_WARHEAD_TYPE_BALL,										// warhead_type
			THREAT_TYPE_INVALID,												// threat_type
			ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,							// launch_sound_effect_sub_type
			SOUND_SAMPLE_INDEX_HEAVY_ARTILLERY,							// interior_launch_sound_effect
			SOUND_SAMPLE_INDEX_HEAVY_ARTILLERY,							// exterior_launch_sound_effect
			SOUND_SAMPLE_INDEX_NONE,										// continuous_sound_effect
			-1,																	// weapon_selected_cpg_speech
			-1,																	// weapon_low_cpg_speech
			-1,																	// weapon_out_cpg_speech
			-1,																	// weapon_launched_cpg_speech
			-1,																	// weapon_launched_wingman_speech
			0,																		// report_weapon_low_count
			FALSE,																// gun_shake
			550,																	// soft_damage_capability
			0,																		// hard_damage_capability
			META_SMOKE_LIST_TYPE_NONE,										// smoke_trail_type
			FALSE,																// acquire_parent_forward_velocity
			FALSE,	  															// ignore_gravity
			FALSE,																// survive_ground_impact
			TRUE,	 																// in_flight_collision_check
			FALSE,																// viewable_weapon
			FALSE,																// boresight_weapon
			FALSE,																// hellfire_flight_profile
			WEAPON_CLASS_DEBRIS,												// weapon_class

			0.0,																	// weight
			0.0,		 															// min_range
			0.0,																	// max_range
			0.0,																	// effective_range
			0.0,																	// min_range_loal
			0.0,																	// max_range_loal
			0.0,																	// max_range_error_ratio
			6.0,																	// muzzle_velocity
			2.0,																	// muzzle_velocity_max_error
			8.0,		 															// cruise_velocity
			0.0 * G,	  															// g_max
			0.0,																	// burn_time
			10.0,																	// cruise_time
			5.0,																	// cruise_time_max_error
			0.0,																	// inhibit_time
			0.0,																	// burst_duration
			FIRE_SINGLE_WEAPON,												// rate_of_fire
			0.0,																	// reload_time
			rad (0.0),															// max_launch_angle_error
		},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void validate_weapon_database (void)
{
	entity_sub_types
		sub_type;

	debug_log ("NUM_WEAPON_CONFIG_TYPES = %d", NUM_WEAPON_CONFIG_TYPES);

	for (sub_type = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON + 1; sub_type < NUM_ENTITY_SUB_TYPE_WEAPONS; sub_type++)
	{
		debug_assert (weapon_database[sub_type].full_name);

		debug_assert (weapon_database[sub_type].hud_name);

		debug_assert (weapon_database[sub_type].mfd_name);

		debug_assert (weapon_database[sub_type].weapon_loading_list_name);

		debug_assert (weapon_database[sub_type].weapon_loading_name_text);

		debug_assert (weapon_database[sub_type].default_3d_shape < OBJECT_3D_LAST);

		debug_assert (weapon_database[sub_type].guidance_type >= 0);

		debug_assert (weapon_database[sub_type].guidance_type < NUM_WEAPON_GUIDANCE_TYPES);

		debug_assert (weapon_database[sub_type].aiming_type >= 0);

		debug_assert (weapon_database[sub_type].aiming_type < NUM_WEAPON_AIMING_TYPES);

		debug_assert (weapon_database[sub_type].decoy_type >= 0);

		debug_assert (weapon_database[sub_type].decoy_type < NUM_WEAPON_DECOY_TYPES);

		debug_assert (weapon_database[sub_type].warhead_type >= 0);

		debug_assert (weapon_database[sub_type].warhead_type < NUM_WEAPON_WARHEAD_TYPES);

		debug_assert (weapon_database[sub_type].threat_type >= 0);

		debug_assert (weapon_database[sub_type].threat_type < NUM_THREAT_TYPES);

		debug_assert (weapon_database[sub_type].interior_launch_sound_effect >= 0);

		debug_assert (weapon_database[sub_type].exterior_launch_sound_effect >= 0);

		debug_assert ((weapon_database[sub_type].gun_shake == FALSE) || (weapon_database[sub_type].gun_shake == TRUE));

		debug_assert (weapon_database[sub_type].soft_damage_capability >= 0);

		debug_assert (weapon_database[sub_type].hard_damage_capability >= 0);

		debug_assert (weapon_database[sub_type].smoke_trail_type < NUM_META_SMOKE_LIST_TYPES);

		debug_assert ((weapon_database[sub_type].acquire_parent_forward_velocity == FALSE) || (weapon_database[sub_type].acquire_parent_forward_velocity == TRUE));

		debug_assert ((weapon_database[sub_type].ignore_gravity == FALSE) || (weapon_database[sub_type].ignore_gravity == TRUE));

		debug_assert ((weapon_database[sub_type].survive_ground_impact == FALSE) || (weapon_database[sub_type].survive_ground_impact == TRUE));

		debug_assert ((weapon_database[sub_type].in_flight_collision_check == FALSE) || (weapon_database[sub_type].in_flight_collision_check == TRUE));

		debug_assert ((weapon_database[sub_type].viewable_weapon == FALSE) || (weapon_database[sub_type].viewable_weapon == TRUE));

		debug_assert ((weapon_database[sub_type].boresight_weapon == FALSE) || (weapon_database[sub_type].boresight_weapon == TRUE));

		debug_assert ((weapon_database[sub_type].hellfire_flight_profile == FALSE) || (weapon_database[sub_type].hellfire_flight_profile == TRUE));

		debug_assert (weapon_database[sub_type].weapon_class != 0);

		debug_assert (weapon_database[sub_type].weight >= 0.0);

		debug_assert (weapon_database[sub_type].min_range >= 0.0);

		debug_assert (weapon_database[sub_type].max_range >= weapon_database[sub_type].min_range);

		debug_assert (weapon_database[sub_type].min_range_loal >= 0.0);

		debug_assert (weapon_database[sub_type].max_range_loal >= weapon_database[sub_type].min_range_loal);

		debug_assert (weapon_database[sub_type].max_range_error_ratio >= 0.0);

		debug_assert (weapon_database[sub_type].muzzle_velocity >= 0.0);

		debug_assert (weapon_database[sub_type].muzzle_velocity_max_error >= 0.0);

		debug_assert (weapon_database[sub_type].cruise_velocity >= 0.0);

		debug_assert ((weapon_database[sub_type].muzzle_velocity + weapon_database[sub_type].muzzle_velocity_max_error) <= weapon_database[sub_type].cruise_velocity);

		debug_assert (weapon_database[sub_type].g_max >= 0.0);

		debug_assert (weapon_database[sub_type].burn_time >= 0.0);

		debug_assert (weapon_database[sub_type].cruise_time >= 0.0);

		debug_assert (weapon_database[sub_type].cruise_time <= MAX_CRUISE_TIME);

		debug_assert (weapon_database[sub_type].cruise_time_max_error >= 0.0);

		debug_assert (weapon_database[sub_type].inhibit_time <= weapon_database[sub_type].burn_time);

		if (weapon_database[sub_type].rate_of_fire != FIRE_SINGLE_WEAPON)
		{
			debug_assert (weapon_database[sub_type].burst_duration > 0.0);

			debug_assert (weapon_database[sub_type].rate_of_fire > 0.0);
		}
		else
		{
			debug_assert (weapon_database[sub_type].burst_duration == 0.0);

			debug_assert (weapon_database[sub_type].launch_sound_effect_sub_type == ENTITY_SUB_TYPE_EFFECT_SOUND_MISC);
		}

		if ((weapon_database[sub_type].weapon_class & WEAPON_CLASS_SURFACE_TO_AIR) ||
		    (weapon_database[sub_type].weapon_class & WEAPON_CLASS_SURFACE_TO_SURFACE))
		{
			debug_assert (weapon_database[sub_type].reload_time > 0.0);
		}
		else
		{
			debug_assert (weapon_database[sub_type].reload_time == 0.0);
		}

		debug_assert (weapon_database[sub_type].max_launch_angle_error >= 0.0);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

weapon_package
	weapon_config_database[NUM_WEAPON_CONFIG_TYPES][NUM_WEAPON_PACKAGES] =
	{
		////////////////////////////////////////
		//
		// INCLUDE ORDER IS CRITICAL
		//
		////////////////////////////////////////

		#include "configs/unarmed.h"

		////////////////////////////////////////

		#include "configs/apache.h"			// ENTITY_SUB_TYPE_AIRCRAFT_AH64D_APACHE_LONGBOW
		#include "configs/havoc.h"		  		// ENTITY_SUB_TYPE_AIRCRAFT_MI28N_HAVOC_B
		#include "configs/comanche.h"	  		// ENTITY_SUB_TYPE_AIRCRAFT_RAH66_COMANCHE
		#include "configs/hokum.h"		  		// ENTITY_SUB_TYPE_AIRCRAFT_KA52_HOKUM_B
		#include "configs/blckhawk.h"	  		// ENTITY_SUB_TYPE_AIRCRAFT_UH60_BLACK_HAWK
		#include "configs/hind.h"				// ENTITY_SUB_TYPE_AIRCRAFT_MI24D_HIND
		#include "configs/seaknght.h"	  		// ENTITY_SUB_TYPE_AIRCRAFT_CH46E_SEA_KNIGHT
		#include "configs/helix.h"		  		// ENTITY_SUB_TYPE_AIRCRAFT_KA29_HELIX_B
		#include "configs/jolly.h"		 		// ENTITY_SUB_TYPE_AIRCRAFT_CH3_JOLLY_GREEN_GIANT
		#include "configs/hip.h"				// ENTITY_SUB_TYPE_AIRCRAFT_MI17_HIP
		#include "configs/chinook.h"			// ENTITY_SUB_TYPE_AIRCRAFT_CH47D_CHINOOK
		#include "configs/hook.h"				// ENTITY_SUB_TYPE_AIRCRAFT_MI6_HOOK
		#include "configs/thndrblt.h"			// ENTITY_SUB_TYPE_AIRCRAFT_A10A_THUNDERBOLT
		#include "configs/frogfoot.h"	  		// ENTITY_SUB_TYPE_AIRCRAFT_SU25_FROGFOOT
		#include "configs/falcon.h"			// ENTITY_SUB_TYPE_AIRCRAFT_F16_FIGHTING_FALCON
		#include "configs/fulcrum.h"			// ENTITY_SUB_TYPE_AIRCRAFT_MIG29_FULCRUM
		#include "configs/harrier.h"			// ENTITY_SUB_TYPE_AIRCRAFT_AV8B_HARRIER
		#include "configs/freestyl.h"			// ENTITY_SUB_TYPE_AIRCRAFT_YAK41_FREESTYLE
		#include "configs/hornet.h"			// ENTITY_SUB_TYPE_AIRCRAFT_FA18_HORNET
		#include "configs/flanker.h"			// ENTITY_SUB_TYPE_AIRCRAFT_SU33_FLANKER
		#include "configs/apache_a.h"			// ENTITY_SUB_TYPE_AIRCRAFT_AH64A_APACHE
		#include "configs/werewolf.h"			// ENTITY_SUB_TYPE_AIRCRAFT_KA50_HOKUM
		#include "configs/kiowa.h"				// ENTITY_SUB_TYPE_AIRCRAFT_OH58D_KIOWA_WARRIOR
		#include "configs/osprey.h"			// ENTITY_SUB_TYPE_AIRCRAFT_MV22_OSPREY
		#include "configs/seacobra.h"			// ENTITY_SUB_TYPE_AIRCRAFT_AH1T_SEACOBRA
		#include "configs/supcobra.h"			// ENTITY_SUB_TYPE_AIRCRAFT_AH1W_SUPERCOBRA
		#include "configs/stallion.h"			// ENTITY_SUB_TYPE_AIRCRAFT_CH53E_SUPER_STALLION
		#include "configs/globe.h"				// ENTITY_SUB_TYPE_AIRCRAFT_C17_GLOBEMASTER_III
		#include "configs/candid.h"			// ENTITY_SUB_TYPE_AIRCRAFT_IL76MD_CANDID_B
		#include "configs/hercules.h"			// ENTITY_SUB_TYPE_AIRCRAFT_C130J_HERCULES_II
		#include "configs/cub.h"	 			// ENTITY_SUB_TYPE_AIRCRAFT_AN12B_CUB

		////////////////////////////////////////

		#include "configs/abrams.h"			// ENTITY_SUB_TYPE_VEHICLE_M1A2_ABRAMS
		#include "configs/t80u.h"	  			// ENTITY_SUB_TYPE_VEHICLE_T80U
		#include "configs/bradley.h"			// ENTITY_SUB_TYPE_VEHICLE_M2A2_BRADLEY
		#include "configs/bmp2.h"	  			// ENTITY_SUB_TYPE_VEHICLE_BMP2
		#include "configs/bmp3.h"		 		// ENTITY_SUB_TYPE_VEHICLE_BMP3
		#include "configs/m113a2.h"			// ENTITY_SUB_TYPE_VEHICLE_M113A2
		#include "configs/btr80.h"	 			// ENTITY_SUB_TYPE_VEHICLE_BTR80
		// unarmed									// ENTITY_SUB_TYPE_VEHICLE_M1025_HUMVEE
		#include "configs/brdm2.h"				// ENTITY_SUB_TYPE_VEHICLE_BRDM2
		#include "configs/m109a2.h"			// ENTITY_SUB_TYPE_VEHICLE_M109A2
		#include "configs/2s19.h"				// ENTITY_SUB_TYPE_VEHICLE_2S19
		#include "configs/mlrs.h"	  			// ENTITY_SUB_TYPE_VEHICLE_M270_MLRS
		#include "configs/grad.h"		 		// ENTITY_SUB_TYPE_VEHICLE_BM21_GRAD
		#include "configs/vulcan.h"			// ENTITY_SUB_TYPE_VEHICLE_M163_VULCAN
		#include "configs/grison.h"			// ENTITY_SUB_TYPE_VEHICLE_SA19_GRISON
		#include "configs/avenger.h"			// ENTITY_SUB_TYPE_VEHICLE_M1037_AVENGER
		#include "configs/chaparrl.h"  		// ENTITY_SUB_TYPE_VEHICLE_M48A1_CHAPARRAL
		#include "configs/gopher.h"			// ENTITY_SUB_TYPE_VEHICLE_SA13_GOPHER
		// unarmed									// ENTITY_SUB_TYPE_VEHICLE_M998_HUMVEE
		// unarmed									// ENTITY_SUB_TYPE_VEHICLE_UAZ469B
		// unarmed									// ENTITY_SUB_TYPE_VEHICLE_M923A1_BIG_FOOT
		// unarmed									// ENTITY_SUB_TYPE_VEHICLE_M923A1_BIG_FOOT_COVERED
		// unarmed									// ENTITY_SUB_TYPE_VEHICLE_URAL_4320
		// unarmed									// ENTITY_SUB_TYPE_VEHICLE_M978_HEMTT
		// unarmed									// ENTITY_SUB_TYPE_VEHICLE_URAL_FUEL_TANKER
		#include "configs/tarawa.h"			// ENTITY_SUB_TYPE_VEHICLE_TARAWA_CLASS
		#include "configs/kiev.h"				// ENTITY_SUB_TYPE_VEHICLE_KIEV_CLASS
		#include "configs/ohp.h"				// ENTITY_SUB_TYPE_VEHICLE_OLIVER_HAZARD_PERRY_CLASS
		#include "configs/krivak.h"			// ENTITY_SUB_TYPE_VEHICLE_KRIVAK_II_CLASS
		// unarmed									// ENTITY_SUB_TYPE_VEHICLE_LCU
		// unarmed									// ENTITY_SUB_TYPE_VEHICLE_LCAC
		#include "configs/aist.h"				// ENTITY_SUB_TYPE_VEHICLE_AIST_CLASS
		#include "configs/us_inf_s.h"			// ENTITY_SUB_TYPE_VEHICLE_US_INFANTRY_SAM_STANDING
		#include "configs/us_inf_k.h"			// ENTITY_SUB_TYPE_VEHICLE_US_INFANTRY_SAM_KNEELING
		#include "configs/rs_inf_s.h"			// ENTITY_SUB_TYPE_VEHICLE_CIS_INFANTRY_SAM_STANDING
		#include "configs/rs_inf_k.h"			// ENTITY_SUB_TYPE_VEHICLE_CIS_INFANTRY_SAM_KNEELING
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

muzzle_flash_animation
	muzzle_flash_animation_database[NUM_MUZZLE_FLASH_TYPES] =
	{
		// MUZZLE_FLASH_INVALID
		{
			OBJECT_3D_INVALID_OBJECT_INDEX,						// object_3d_index_number
			TEXTURE_ANIMATION_INDEX_LAST,							// texture_animation_index1
			TEXTURE_ANIMATION_INDEX_LAST,							// texture_animation_index2
			0.0,															// muzzle_flash_duration
		},
		// MUZZLE_FLASH_SMALL_CALIBRE_STRAIGHT
		{
			OBJECT_3D_EFFECT_GUN_SMALL,							// object_3d_index_number
			TEXTURE_ANIMATION_INDEX_GUN,							// texture_animation_index1
			TEXTURE_ANIMATION_INDEX_GUN_FLARE,					// texture_animation_index2
			0.25,															// muzzle_flash_duration
		},
		// MUZZLE_FLASH_SMALL_CALIBRE_FLARED
		{
			OBJECT_3D_EFFECT_GUN_STAR_SMALL,						// object_3d_index_number
			TEXTURE_ANIMATION_INDEX_GUN,							// texture_animation_index1
			TEXTURE_ANIMATION_INDEX_GUN_FLARE,					// texture_animation_index2
			0.25,							 								// muzzle_flash_duration
		},
		// MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT
		{
			OBJECT_3D_EFFECT_GUN_MEDIUM, 							// object_3d_index_number
			TEXTURE_ANIMATION_INDEX_GUN,							// texture_animation_index1
			TEXTURE_ANIMATION_INDEX_GUN_FLARE,					// texture_animation_index2
			0.25,															// muzzle_flash_duration
		},
		// MUZZLE_FLASH_MEDIUM_CALIBRE_FLARED
		{
			OBJECT_3D_EFFECT_GUN_STAR_MEDIUM,					// object_3d_index_number
			TEXTURE_ANIMATION_INDEX_GUN,							// texture_animation_index1
			TEXTURE_ANIMATION_INDEX_GUN_FLARE,					// texture_animation_index2
			0.25,															// muzzle_flash_duration
		},
		// MUZZLE_FLASH_LARGE_CALIBRE_STRAIGHT
		{
			OBJECT_3D_EFFECT_GUN_LARGE,							// object_3d_index_number
			TEXTURE_ANIMATION_INDEX_GUN_SMOKE,					// texture_animation_index1
			TEXTURE_ANIMATION_INDEX_GUN_SMOKE_FRONT,			// texture_animation_index2
			0.25,															// muzzle_flash_duration
		},
		// MUZZLE_FLASH_LARGE_CALIBRE_FLARED
		{
			OBJECT_3D_EFFECT_GUN_STAR_LARGE,						// object_3d_index_number
			TEXTURE_ANIMATION_INDEX_GUN_SMOKE,					// texture_animation_index1
			TEXTURE_ANIMATION_INDEX_GUN_SMOKE_FRONT,			// texture_animation_index2
			0.25,															// muzzle_flash_duration
		},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vec3d
	target_point_offsets[OBJECT_3D_LAST];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_target_point_offsets (void)
{
	object_3d_index_numbers
		object_3d_index;

	object_3d_instance
		*inst3d;

	object_3d_sub_object_search_data
		search;

	viewpoint
		vp;

	object_3d_bounds
		*bounding_box;

	debug_assert (get_3d_objects_initialised ());

	target_point_offsets[OBJECT_3D_INVALID_OBJECT_INDEX].x = 0.0;
	target_point_offsets[OBJECT_3D_INVALID_OBJECT_INDEX].y = 0.0;
	target_point_offsets[OBJECT_3D_INVALID_OBJECT_INDEX].z = 0.0;

	for (object_3d_index = OBJECT_3D_INVALID_OBJECT_INDEX + 1; object_3d_index < OBJECT_3D_LAST; object_3d_index++)
	{
		inst3d = construct_3d_object (object_3d_index);

		debug_assert (inst3d);

		inst3d->vp.position.x = 0.0;
		inst3d->vp.position.y = 0.0;
		inst3d->vp.position.z = 0.0;

		get_identity_matrix3x3 (inst3d->vp.attitude);

		search.search_depth = 0;
		search.search_object = inst3d;
		search.sub_object_index = OBJECT_3D_SUB_OBJECT_TARGET_POINT;

		if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			get_3d_sub_object_world_viewpoint (search.result_sub_object, &vp);

			target_point_offsets[object_3d_index] = vp.position;
		}
		else
		{
			if (command_line_target_point_check)
			{
				debug_colour_log (DEBUG_COLOUR_FOREST_GREEN, "Target point missing from 3D object: %s", object_3d_enumeration_names[object_3d_index]);
			}

			bounding_box = get_object_3d_bounding_box (object_3d_index);

			target_point_offsets[object_3d_index].x = (bounding_box->xmin + bounding_box->xmax) * 0.5;
			target_point_offsets[object_3d_index].y = max ((bounding_box->ymin + bounding_box->ymax) * 0.5, 0.0);
			target_point_offsets[object_3d_index].z = (bounding_box->zmin + bounding_box->zmax) * 0.5;
		}

		#if DEBUG_MODULE_DISPLAY_TARGET_POINT_OFFSETS

		debug_log
		(
			"Target point offset for %s: x = %.2f, y = %.2f, z = %.2f",
			object_3d_enumeration_names[object_3d_index],
			target_point_offsets[object_3d_index].x,
			target_point_offsets[object_3d_index].y,
			target_point_offsets[object_3d_index].z
		);

		#endif

		destruct_3d_object (inst3d);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
