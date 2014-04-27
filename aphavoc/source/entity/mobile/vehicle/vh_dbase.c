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

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//VJ WUT mod bug, date: 26-mar-03
//remove "const" from definition
vehicle_data
	vehicle_database[NUM_ENTITY_SUB_TYPE_VEHICLES] =
	{
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_M1A2_ABRAMS
		//
		////////////////////////////////////////
		{
			"M1A2 Abrams",													// full_name
			"M1A2 ABRAMS",	 												// long_display_name
			"M1A2",															// short_display_name
			"TANK",															// easy_display_name

			OBJECT_3D_M1A2_ABRAMS,										// default_3d_shape
			ENTITY_FORCE_GROUND,											// force
			WEAPON_CONFIG_TYPE_M1A2_ABRAMS_1,						// default_weapon_config_type
			WEAPON_CONFIG_TYPE_M1A2_ABRAMS_1,						// min_weapon_config_type
			WEAPON_CONFIG_TYPE_M1A2_ABRAMS_1,						// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_M2HB_12P7MM_ROUND,				// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_TRACKED_VEHICLE,							// target_symbol_type
			TARGET_PRIORITY_MEDIUM,		 								// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_ROUTED_VEHICLE,				// force_info_catagory
			THREAT_TYPE_INVALID,											// threat_type
			VIEW_CATEGORY_COMBAT_VEHICLES,							// view_category
			VIEW_TYPE_M1A2_ABRAMS,										// view_type
			MAP_ICON_TANK,													// map icon
			TRUE,	  															// carries_smoke_grenades

			8.0,																// chase_view_min_distance
			100.0,	  														// chase_view_max_distance
			0.5,	  	 														// chase_view_min_distance_test
			550.0,	  														// chase_view_max_distance_test
			knots_to_metres_per_second (20.0),              	// cruise_velocity
			(2.2902 + 2.3798),											// axle_length
			2.0,																// max_acceleration
			rad (5.0),														// max_turn_rate (rad / second)
			20.0 * G, 														// g_max
			20.0,																// power_output
			2000.0,															// recon_radius
			15.0,																// target_scan_delay
			10.0,																// air_scan_floor
			1000.0,															// air_scan_ceiling
			2000.0,															// air_scan_range
			4000.0,		  													// surface_scan_range
			0.333,															// potential_surface_to_air_threat
			1.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			1.0,																// armour_front
			0.75,																// armour_side
			0.5,																// armour_rear

			1500,																// initial_damage_level
			WARHEAD_EFFECTIVE_ARMOURED_VEHICLE,						// armor_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,								// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,										// explosive_power
			TRUE,																// offensive_capability
			100,																// points value

			SOUND_SAMPLE_INDEX_TANK_TICKING,							// idle_sound_effect
			SOUND_SAMPLE_INDEX_TANK_MOVING,							// moving_sound_effect
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_T80U
		//
		////////////////////////////////////////
		{
			"T-80U",															// full_name
			"T-80U",	 		 												// long_display_name
			"T-80U",															// short_display_name
			"TANK",															// easy_display_name

			OBJECT_3D_T_80,												// default_3d_shape
			ENTITY_FORCE_GROUND,											// force
			WEAPON_CONFIG_TYPE_T80U_1,									// default_weapon_config_type
			WEAPON_CONFIG_TYPE_T80U_1,									// min_weapon_config_type
			WEAPON_CONFIG_TYPE_T80U_1,									// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_NSVT_12P7MM_ROUND, 				// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_TRACKED_VEHICLE,							// target_symbol_type
			TARGET_PRIORITY_MEDIUM,		 								// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_ROUTED_VEHICLE,				// force_info_catagory
			THREAT_TYPE_INVALID,											// threat_type
			VIEW_CATEGORY_COMBAT_VEHICLES,							// view_category
			VIEW_TYPE_T80U,												// view_type
			MAP_ICON_TANK,													// map icon
			TRUE,		 														// carries_smoke_grenades

			8.0,																// chase_view_min_distance
			100.0,	  														// chase_view_max_distance
			0.5,																// chase_view_min_distance_test
			550.0,	  														// chase_view_max_distance_test
			knots_to_metres_per_second (20.0),              	// cruise_velocity
			(2.10 + 2.125),												// axle_length
			2.0,																// max_acceleration
			rad (5.0),														// max_turn_rate (rad / second)
			20.0 * G, 														// g_max
			20.0,																// power_output
			2000.0,															// recon_radius
			15.0,																// target_scan_delay
			10.0,																// air_scan_floor
			1000.0,															// air_scan_ceiling
			2000.0,															// air_scan_range
			4000.0,															// surface_scan_range
			0.333,  															// potential_surface_to_air_threat
			1.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			1.0,																// armour_front
			0.75,																// armour_side
			0.5,																// armour_rear

			1350,																// initial_damage_level
			WARHEAD_EFFECTIVE_ARMOURED_VEHICLE,						// armor_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,								// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,										// explosive_power
			TRUE,																// offensive_capability
			100,																// points value

			SOUND_SAMPLE_INDEX_TANK_TICKING,							// idle_sound_effect
			SOUND_SAMPLE_INDEX_TANK_MOVING,							// moving_sound_effect
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_M2A2_BRADLEY
		//
		////////////////////////////////////////
		{
			"M2A2 Bradley",                                 	// full_name
			"M2A2 BRADLEY", 												// long_display_name
			"M2A2",															// short_display_name
			"IFV",															// easy_display_name

			OBJECT_3D_M2A2_BRADLEY,                         	// default_3d_shape
			ENTITY_FORCE_GROUND,                            	// force
			WEAPON_CONFIG_TYPE_M2A2_BRADLEY_1,		 				// default_weapon_config_type
			WEAPON_CONFIG_TYPE_M2A2_BRADLEY_1,		 				// min_weapon_config_type
			WEAPON_CONFIG_TYPE_M2A2_BRADLEY_1,		 				// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_M242_25MM_ROUND,				// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_TRACKED_VEHICLE,  							// target_symbol_type
			TARGET_PRIORITY_HIGH,		 								// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_ROUTED_VEHICLE,				// force_info_catagory
			THREAT_TYPE_INVALID,											// threat_type
			VIEW_CATEGORY_COMBAT_VEHICLES,							// view_category
			VIEW_TYPE_M2A2_BRADLEY,										// view_type
			MAP_ICON_TANK,													// map icon
			TRUE,	  															// carries_smoke_grenades

			8.0,																// chase_view_min_distance
			100.0,	  														// chase_view_max_distance
			0.5,																// chase_view_min_distance_test
			550.0,	  														// chase_view_max_distance_test
			knots_to_metres_per_second (20.0),              	// cruise_velocity
			(1.995 + 1.855),												// axle_length
			2.0,																// max_acceleration
			rad (5.0),														// max_turn_rate (rad / second)
			7.0 * G, 														// g_max
			20.0,																// power_output
			3000.0,															// recon_radius
			15.0,																// target_scan_delay
			10.0,																// air_scan_floor
			2000.0,															// air_scan_ceiling
			4000.0,															// air_scan_range
			4000.0,															// surface_scan_range
			0.666,															// potential_surface_to_air_threat
			1.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			0.75,																// armour_front
			0.5,																// armour_side
			0.5,																// armour_rear

			1000,																// initial_damage_level
			WARHEAD_EFFECTIVE_ARMOURED_VEHICLE,						// armor_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,								// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,										// explosive_power
			TRUE,																// offensive_capability
			125,																// points value

			SOUND_SAMPLE_INDEX_TANK_TICKING,							// idle_sound_effect
			SOUND_SAMPLE_INDEX_TANK_MOVING,							// moving_sound_effect
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_BMP2
		//
		////////////////////////////////////////
		{
			"BMP-2",                                        	// full_name
			"BMP-2", 														// long_display_name
			"BMP-2",															// short_display_name
			"IFV",															// easy_display_name

			OBJECT_3D_BMP2,                                 	// default_3d_shape
			ENTITY_FORCE_GROUND,                            	// force
			WEAPON_CONFIG_TYPE_BMP2_1,									// default_weapon_config_type
			WEAPON_CONFIG_TYPE_BMP2_1,									// min_weapon_config_type
			WEAPON_CONFIG_TYPE_BMP2_1,	  								// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND,			// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_TRACKED_VEHICLE,							// target_symbol_type
			TARGET_PRIORITY_HIGH,		 								// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_ROUTED_VEHICLE,				// force_info_catagory
			THREAT_TYPE_INVALID,											// threat_type
			VIEW_CATEGORY_COMBAT_VEHICLES,							// view_category
			VIEW_TYPE_BMP2,												// view_type
			MAP_ICON_TANK,													// map icon
			TRUE,																// carries_smoke_grenades

			8.0,																// chase_view_min_distance
			100.0,	  														// chase_view_max_distance
			0.5,																// chase_view_min_distance_test
			550.0,	  														// chase_view_max_distance_test
			knots_to_metres_per_second (20.0),              	// cruise_velocity
			(1.38 + 2.156),												// axle_length
			2.0,																// max_acceleration
			rad (5.0),														// max_turn_rate (rad / second)
			7.0 * G, 														// g_max
			20.0,																// power_output
			3000.0,															// recon_radius
			15.0,																// target_scan_delay
			10.0,																// air_scan_floor
			2000.0,															// air_scan_ceiling
			4000.0,															// air_scan_range
			4000.0,															// surface_scan_range
			0.666, 															// potential_surface_to_air_threat
			1.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			0.5,																// armour_front
			0.25,																// armour_side
			0.25,																// armour_rear

			1000,																// initial_damage_level
			WARHEAD_EFFECTIVE_ARMOURED_VEHICLE,						// armor_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,								// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,										// explosive_power
			TRUE,																// offensive_capability
			125,																// points value

			SOUND_SAMPLE_INDEX_TANK_TICKING,							// idle_sound_effect
			SOUND_SAMPLE_INDEX_TANK_MOVING,							// moving_sound_effect
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_BMP3
		//
		////////////////////////////////////////
		{
			"BMP-3",                                        	// full_name
			"BMP-3", 														// long_display_name
			"BMP-3",															// short_display_name
			"IFV",															// easy_display_name

			OBJECT_3D_BMP3,                                 	// default_3d_shape
			ENTITY_FORCE_GROUND,                            	// force
			WEAPON_CONFIG_TYPE_BMP3_1,									// default_weapon_config_type
			WEAPON_CONFIG_TYPE_BMP3_1,									// min_weapon_config_type
			WEAPON_CONFIG_TYPE_BMP3_1,									// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_2A72_30MM_ROUND,				// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_TRACKED_VEHICLE,  							// target_symbol_type
			TARGET_PRIORITY_HIGH,		 								// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_ROUTED_VEHICLE,				// force_info_catagory
			THREAT_TYPE_INVALID,											// threat_type
			VIEW_CATEGORY_COMBAT_VEHICLES,							// view_category
			VIEW_TYPE_BMP3,												// view_type
			MAP_ICON_TANK,													// map icon
			TRUE,		 														// carries_smoke_grenades

			8.0,																// chase_view_min_distance
			100.0,	  														// chase_view_max_distance
			0.5,																// chase_view_min_distance_test
			550.0,	  														// chase_view_max_distance_test
			knots_to_metres_per_second (20.0),              	// cruise_velocity
			(1.78 + 2.52),													// axle_length
			2.0,																// max_acceleration
			rad (5.0),														// max_turn_rate (rad / second)
			7.0 * G, 														// g_max
			20.0,																// power_output
			2000.0,															// recon_radius
			15.0,																// target_scan_delay
			10.0,																// air_scan_floor
			1000.0,															// air_scan_ceiling
			2000.0,															// air_scan_range
			5000.0,	  														// surface_scan_range
			0.666,  															// potential_surface_to_air_threat
			1.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			0.5,																// armour_front
			0.25,																// armour_side
			0.25,																// armour_rear

			1000,																// initial_damage_level
			WARHEAD_EFFECTIVE_ARMOURED_VEHICLE,						// armor_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,								// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,										// explosive_power
			TRUE,																// offensive_capability
			125,																// points value

			SOUND_SAMPLE_INDEX_TANK_TICKING,							// idle_sound_effect
			SOUND_SAMPLE_INDEX_TANK_MOVING,							// moving_sound_effect
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_M113A2
		//
		////////////////////////////////////////
		{
			"M113A2",                                       	// full_name
			"M113A2", 														// long_display_name
			"M113A2",	  													// short_display_name
			"APC",															// easy_display_name

			OBJECT_3D_M_113_A1,        				         	// default_3d_shape
			ENTITY_FORCE_GROUND,                            	// force
			WEAPON_CONFIG_TYPE_M113A2_1,								// default_weapon_config_type
			WEAPON_CONFIG_TYPE_M113A2_1,								// min_weapon_config_type
			WEAPON_CONFIG_TYPE_M113A2_1,								// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_M2HB_12P7MM_ROUND,  				// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_TRACKED_VEHICLE,							// target_symbol_type
			TARGET_PRIORITY_MEDIUM,		 								// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_ROUTED_VEHICLE,				// force_info_catagory
			THREAT_TYPE_INVALID,											// threat_type
			VIEW_CATEGORY_COMBAT_VEHICLES,							// view_category
			VIEW_TYPE_M113A2,												// view_type
			MAP_ICON_APC,													// map icon
			FALSE,															// carries_smoke_grenades

			8.0,																// chase_view_min_distance
			100.0,	  														// chase_view_max_distance
			0.5,																// chase_view_min_distance_test
			550.0,	  														// chase_view_max_distance_test
			knots_to_metres_per_second (20.0),              	// cruise_velocity
			(1.40 + 1.30),													// axle_length
			2.0,																// max_acceleration
			rad (5.0),														// max_turn_rate (rad / second)
			7.0 * G, 														// g_max
			20.0,																// power_output
			2000.0,															// recon_radius
			15.0,																// target_scan_delay
			10.0,																// air_scan_floor
			1000.0,															// air_scan_ceiling
			2000.0,															// air_scan_range
			0.0,																// surface_scan_range
			0.333,															// potential_surface_to_air_threat
			0.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			0.5,																// armour_front
			0.5,																// armour_side
			0.5,																// armour_rear

			800,																// initial_damage_level
			WARHEAD_EFFECTIVE_ARMOURED_VEHICLE,						// armor_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,								// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,										// explosive_power
			TRUE,																// offensive_capability
			75,																// points value

			SOUND_SAMPLE_INDEX_TRUCK_TICKING,						// idle_sound_effect
			SOUND_SAMPLE_INDEX_TRUCK_MOVING,							// moving_sound_effect
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_BTR80
		//
		////////////////////////////////////////
		{
			"BTR-80",                                       	// full_name
			"BTR-80", 														// long_display_name
			"BTR-80",	  													// short_display_name
			"APC",															// easy_display_name

			OBJECT_3D_BTR_80,												// default_3d_shape
			ENTITY_FORCE_GROUND,                            	// force
			WEAPON_CONFIG_TYPE_BTR80_1,								// default_weapon_config_type
			WEAPON_CONFIG_TYPE_BTR80_1,								// min_weapon_config_type
			WEAPON_CONFIG_TYPE_BTR80_1,								// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_KPVT_14P5MM_ROUND,				// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_WHEELED_VEHICLE, 							// target_symbol_type
			TARGET_PRIORITY_MEDIUM,		 								// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_ROUTED_VEHICLE,				// force_info_catagory
			THREAT_TYPE_INVALID,											// threat_type
			VIEW_CATEGORY_COMBAT_VEHICLES,							// view_category
			VIEW_TYPE_BTR80,												// view_type
			MAP_ICON_APC,													// map icon
			TRUE,																// carries_smoke_grenades

			8.0,																// chase_view_min_distance
			100.0,	  														// chase_view_max_distance
			0.5,	  		  													// chase_view_min_distance_test
			550.0,	  														// chase_view_max_distance_test
			knots_to_metres_per_second (20.0),              	// cruise_velocity
			(2.25 + 2.21),													// axle_length
			2.0,																// max_acceleration
			rad (5.0),														// max_turn_rate (rad / second)
			7.0 * G, 														// g_max
			20.0,																// power_output
			2000.0,															// recon_radius
			15.0,																// target_scan_delay
			10.0,																// air_scan_floor
			1000.0,															// air_scan_ceiling
			2000.0,															// air_scan_range
			0.0,																// surface_scan_range
			0.333, 															// potential_surface_to_air_threat
			0.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			0.25,																// armour_front
			0.25,																// armour_side
			0.0,																// armour_rear

			800,																// initial_damage_level
			WARHEAD_EFFECTIVE_ARMOURED_VEHICLE,						// armor_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,								// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,										// explosive_power
			TRUE,																// offensive_capability
			75,																// points value

			SOUND_SAMPLE_INDEX_TRUCK_TICKING,						// idle_sound_effect
			SOUND_SAMPLE_INDEX_TRUCK_MOVING,							// moving_sound_effect
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_M1025_HUMVEE
		//
		////////////////////////////////////////
		{
			"M1025 HumVee",                                 	// full_name
			"M1025 HUMVEE", 	  											// long_display_name
			"M1025",	  	 													// short_display_name
			"SCOUT CAR",													// easy_display_name

			OBJECT_3D_HMMWV,                                	// default_3d_shape
			ENTITY_FORCE_GROUND,                            	// force
			WEAPON_CONFIG_TYPE_UNARMED,								// default_weapon_config_type
			WEAPON_CONFIG_TYPE_UNARMED,								// min_weapon_config_type
			WEAPON_CONFIG_TYPE_UNARMED,								// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, 	 					// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_WHEELED_VEHICLE, 							// target_symbol_type
			TARGET_PRIORITY_LOW,			 								// target_priority_type
			FORCE_INFO_CATAGORY_UNARMED_ROUTED_VEHICLE,			// force_info_catagory
			THREAT_TYPE_INVALID,											// threat_type
			VIEW_CATEGORY_COMBAT_VEHICLES,							// view_category
			VIEW_TYPE_M1025_HUMVEE,										// view_type
			MAP_ICON_APC,													// map icon
			FALSE,															// carries_smoke_grenades

			8.0,																// chase_view_min_distance
			100.0,	  														// chase_view_max_distance
			0.5,	  		  													// chase_view_min_distance_test
			550.0,	  														// chase_view_max_distance_test
			knots_to_metres_per_second (20.0),              	// cruise_velocity
			(1.6275 + 1.4375),											// axle_length
			2.0,																// max_acceleration
			rad (5.0),														// max_turn_rate (rad / second)
			7.0 * G, 														// g_max
			20.0,																// power_output
			1000.0,															// recon_radius
			0.0,																// target_scan_delay
			0.0,																// air_scan_floor
			0.0,																// air_scan_ceiling
			0.0,																// air_scan_range
			0.0,																// surface_scan_range
			0.0,																// potential_surface_to_air_threat
			0.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			0.0,																// armour_front
			0.0,																// armour_side
			0.0,																// armour_rear

			650,																// initial_damage_level
			WARHEAD_EFFECTIVE_ARMOURED_VEHICLE,						// armor_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,								// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,										// explosive_power
			FALSE,															// offensive_capability
			50,																// points value

			SOUND_SAMPLE_INDEX_JEEP_TICKING,							// idle_sound_effect
			SOUND_SAMPLE_INDEX_JEEP_MOVING,							// moving_sound_effect
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_BRDM2
		//
		////////////////////////////////////////
		{
			"BRDM-2",                                       	// full_name
			"BRDM-2", 			  											// long_display_name
			"BRDM-2",  	 													// short_display_name
			"SCOUT CAR",													// easy_display_name

			OBJECT_3D_BRDM_2,        					         	// default_3d_shape
			ENTITY_FORCE_GROUND,                            	// force
			WEAPON_CONFIG_TYPE_BRDM2_1,								// default_weapon_config_type
			WEAPON_CONFIG_TYPE_BRDM2_1,								// min_weapon_config_type
			WEAPON_CONFIG_TYPE_BRDM2_1,								// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_KPVT_14P5MM_ROUND,				// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_WHEELED_VEHICLE,  							// target_symbol_type
			TARGET_PRIORITY_MEDIUM,	 									// target_priority_type
			FORCE_INFO_CATAGORY_UNARMED_ROUTED_VEHICLE,			// force_info_catagory
			THREAT_TYPE_INVALID,											// threat_type
			VIEW_CATEGORY_COMBAT_VEHICLES,							// view_category
			VIEW_TYPE_BRDM2,												// view_type
			MAP_ICON_APC,													// map icon
			FALSE,															// carries_smoke_grenades

			8.0,																// chase_view_min_distance
			100.0,	  														// chase_view_max_distance
			0.5,	  			 												// chase_view_min_distance_test
			550.0,	  														// chase_view_max_distance_test
			knots_to_metres_per_second (20.0),              	// cruise_velocity
			(1.40 + 1.65),													// axle_length
			2.0,																// max_acceleration
			rad (5.0),														// max_turn_rate (rad / second)
			7.0 * G, 														// g_max
			20.0,																// power_output
			1000.0,															// recon_radius
			15.0,																// target_scan_delay
			10.0,																// air_scan_floor
			1000.0,															// air_scan_ceiling
			2000.0,															// air_scan_range
			0.0,																// surface_scan_range
			0.333,															// potential_surface_to_air_threat
			0.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			0.25,																// armour_front
			0.0,																// armour_side
			0.0,																// armour_rear

			650,																// initial_damage_level
			WARHEAD_EFFECTIVE_ARMOURED_VEHICLE,						// armor_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,								// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,										// explosive_power
			TRUE,																// offensive_capability
			50,																// points value

			SOUND_SAMPLE_INDEX_JEEP_TICKING,							// idle_sound_effect
			SOUND_SAMPLE_INDEX_JEEP_MOVING,							// moving_sound_effect
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_M109A2
		//
		////////////////////////////////////////
		{
			"M109A2",                                       	// full_name
			"M109A2", 			  											// long_display_name
			"M109A2",  	 													// short_display_name
			"ARTILLERY",													// easy_display_name

			OBJECT_3D_M109A2,                               	// default_3d_shape
			ENTITY_FORCE_GROUND,                            	// force
			WEAPON_CONFIG_TYPE_M109A2_1,								// default_weapon_config_type
			WEAPON_CONFIG_TYPE_M109A2_1,								// min_weapon_config_type
			WEAPON_CONFIG_TYPE_M109A2_1,								// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_M2HB_12P7MM_ROUND,  				// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_TRACKED_VEHICLE, 							// target_symbol_type
			TARGET_PRIORITY_MEDIUM,		 								// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_ROUTED_VEHICLE,				// force_info_catagory
			THREAT_TYPE_INVALID,											// threat_type
			VIEW_CATEGORY_ARTILLERY,									// view_category
			VIEW_TYPE_M109A2,												// view_type
			MAP_ICON_ARTILLERY,											// map icon
			FALSE,															// carries_smoke_grenades

			8.0,																// chase_view_min_distance
			100.0,	  														// chase_view_max_distance
			0.5,																// chase_view_min_distance_test
			550.0,	  														// chase_view_max_distance_test
			knots_to_metres_per_second (20.0),              	// cruise_velocity
			(2.0052 + 2.0148),											// axle_length
			2.0,																// max_acceleration
			rad (5.0),														// max_turn_rate (rad / second)
			7.0 * G, 														// g_max
			20.0,																// power_output
			2000.0,															// recon_radius
			15.0,																// target_scan_delay
			10.0,																// air_scan_floor
			1000.0,															// air_scan_ceiling
			2000.0,															// air_scan_range
			0.0,																// surface_scan_range
			0.333,		 													// potential_surface_to_air_threat
			0.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			0.75,																// armour_front
			0.5,																// armour_side
			0.25,																// armour_rear

			600,																// initial_damage_level
			WARHEAD_EFFECTIVE_ARMOURED_VEHICLE,						// armor_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,								// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,										// explosive_power
			TRUE,																// offensive_capability
			100,																// points value

			SOUND_SAMPLE_INDEX_TANK_TICKING,							// idle_sound_effect
			SOUND_SAMPLE_INDEX_TANK_MOVING,							// moving_sound_effect
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_2S19
		//
		////////////////////////////////////////
		{
			"2S19 Msta",                                         	// full_name
			"2S19", 				  											// long_display_name
			"2S19",  	 													// short_display_name
			"ARTILLERY",													// easy_display_name

			OBJECT_3D_2S19,												// default_3d_shape
			ENTITY_FORCE_GROUND,                            	// force
			WEAPON_CONFIG_TYPE_2S19_1,		 							// default_weapon_config_type
			WEAPON_CONFIG_TYPE_2S19_1,									// min_weapon_config_type
			WEAPON_CONFIG_TYPE_2S19_1,									// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_NSVT_12P7MM_ROUND,				// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_TRACKED_VEHICLE,  							// target_symbol_type
			TARGET_PRIORITY_MEDIUM,		 								// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_ROUTED_VEHICLE,				// force_info_catagory
			THREAT_TYPE_INVALID,											// threat_type
			VIEW_CATEGORY_ARTILLERY,									// view_category
			VIEW_TYPE_2S19,												// view_type
			MAP_ICON_ARTILLERY,											// map icon
			TRUE,		 														// carries_smoke_grenades

			8.0,																// chase_view_min_distance
			100.0,	  														// chase_view_max_distance
			0.5,																// chase_view_min_distance_test
			550.0,	  														// chase_view_max_distance_test
			knots_to_metres_per_second (20.0),              	// cruise_velocity
			(2.10 + 2.125),												// axle_length
			2.0,																// max_acceleration
			rad (5.0),														// max_turn_rate (rad / second)
			7.0 * G, 														// g_max
			20.0,																// power_output
			1000.0,															// recon_radius
			15.0,																// target_scan_delay
			10.0,																// air_scan_floor
			1000.0,															// air_scan_ceiling
			2000.0,															// air_scan_range
			0.0,																// surface_scan_range
			0.333,															// potential_surface_to_air_threat
			0.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			0.75,																// armour_front
			0.5,																// armour_side
			0.25,																// armour_rear

			600,																// initial_damage_level
			WARHEAD_EFFECTIVE_ARMOURED_VEHICLE,						// armor_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,								// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,										// explosive_power
			TRUE,																// offensive_capability
			100,																// points value

			SOUND_SAMPLE_INDEX_TANK_TICKING,							// idle_sound_effect
			SOUND_SAMPLE_INDEX_TANK_MOVING,							// moving_sound_effect
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_M270_MLRS
		//
		////////////////////////////////////////
		{
			"M270 MLRS",                                    	// full_name
			"M270 MLRS", 		  											// long_display_name
			"M270",  	 													// short_display_name
			"ARTILLERY",													// easy_display_name

			OBJECT_3D_MLRS,      					           		// default_3d_shape
			ENTITY_FORCE_GROUND,                            	// force
			WEAPON_CONFIG_TYPE_M270_MLRS_1,							// default_weapon_config_type
			WEAPON_CONFIG_TYPE_M270_MLRS_1,							// min_weapon_config_type
			WEAPON_CONFIG_TYPE_M270_MLRS_1,							// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_M26A1_227MM_ROCKET,				// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_TRACKED_VEHICLE,  							// target_symbol_type
			TARGET_PRIORITY_LOW,	 		 								// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_ROUTED_VEHICLE,				// force_info_catagory
			THREAT_TYPE_INVALID,											// threat_type
			VIEW_CATEGORY_ARTILLERY,									// view_category
			VIEW_TYPE_M270_MLRS,											// view_type
			MAP_ICON_ARTILLERY,											// map icon
			FALSE,															// carries_smoke_grenades

			8.0,																// chase_view_min_distance
			100.0,	  														// chase_view_max_distance
			0.5,																// chase_view_min_distance_test
			550.0,	  														// chase_view_max_distance_test
			knots_to_metres_per_second (20.0),              	// cruise_velocity
			(2.15 + 1.93),													// axle_length
			2.0,																// max_acceleration
			rad (5.0),														// max_turn_rate (rad / second)
			7.0 * G, 														// g_max
			20.0,																// power_output
			2000.0,															// recon_radius
			0.0,																// target_scan_delay
			0.0,																// air_scan_floor
			0.0,																// air_scan_ceiling
			0.0,	  															// air_scan_range
			0.0,																// surface_scan_range
			0.0,																// potential_surface_to_air_threat
			0.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			0.25,																// armour_front
			0.0,																// armour_side
			0.0,																// armour_rear

			700,																// initial_damage_level
			WARHEAD_EFFECTIVE_LIGHT_VEHICLE,							// armor_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,								// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,										// explosive_power
			TRUE,																// offensive_capability
			100,																// points value

			SOUND_SAMPLE_INDEX_TANK_TICKING,							// idle_sound_effect
			SOUND_SAMPLE_INDEX_TANK_MOVING,							// moving_sound_effect
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_BM21_GRAD
		//
		////////////////////////////////////////
		{
			"BM-21 Grad",													// full_name
			"BM-21 GRAD", 		  											// long_display_name
			"BM-21",  	 													// short_display_name
			"ARTILLERY",													// easy_display_name

			OBJECT_3D_BM_21,												// default_3d_shape
			ENTITY_FORCE_GROUND,                            	// force
			WEAPON_CONFIG_TYPE_BM21_GRAD_1,							// default_weapon_config_type
			WEAPON_CONFIG_TYPE_BM21_GRAD_1,							// min_weapon_config_type
			WEAPON_CONFIG_TYPE_BM21_GRAD_1,							// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_BM21_122MM_ROCKET, 			// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_WHEELED_VEHICLE,							// target_symbol_type
			TARGET_PRIORITY_LOW,			 								// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_ROUTED_VEHICLE,				// force_info_catagory
			THREAT_TYPE_INVALID,											// threat_type
			VIEW_CATEGORY_ARTILLERY,									// view_category
			VIEW_TYPE_BM21_GRAD,											// view_type
			MAP_ICON_ARTILLERY,											// map icon
			FALSE,															// carries_smoke_grenades

			8.0,																// chase_view_min_distance
			100.0,	  														// chase_view_max_distance
			0.5,																// chase_view_min_distance_test
			550.0,	  														// chase_view_max_distance_test
			knots_to_metres_per_second (20.0),              	// cruise_velocity
			(2.46 + 2.50),													// axle_length
			2.0,																// max_acceleration
			rad (5.0),														// max_turn_rate (rad / second)
			7.0 * G, 														// g_max
			20.0,																// power_output
			2000.0,															// recon_radius
			0.0,																// target_scan_delay
			0.0,																// air_scan_floor
			0.0,																// air_scan_ceiling
			0.0,																// air_scan_range
			0.0,																// surface_scan_range
			0.0,																// potential_surface_to_air_threat
			0.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			0.0,																// armour_front
			0.0,																// armour_side
			0.0,																// armour_rear

			700,																// initial_damage_level
			WARHEAD_EFFECTIVE_LIGHT_VEHICLE,							// armor_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,								// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,										// explosive_power
			TRUE,																// offensive_capability
			100,																// points value

			SOUND_SAMPLE_INDEX_TRUCK_TICKING,						// idle_sound_effect
			SOUND_SAMPLE_INDEX_TRUCK_MOVING,							// moving_sound_effect
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_M163_VULCAN
		//
		////////////////////////////////////////
		{
			"M163 Vulcan",                                  	// full_name
			"M163 VULCAN", 	  											// long_display_name
			"M163",  	 													// short_display_name
			"AAA",															// easy_display_name

			OBJECT_3D_M_163_A1,											// default_3d_shape
			ENTITY_FORCE_GROUND,                            	// force
			WEAPON_CONFIG_TYPE_M163_VULCAN_1,						// default_weapon_config_type
			WEAPON_CONFIG_TYPE_M163_VULCAN_1,						// min_weapon_config_type
			WEAPON_CONFIG_TYPE_M163_VULCAN_1,						// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_M61A1_20MM_ROUND, 				// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_AIR_DEFENCE_UNIT,							// target_symbol_type
			TARGET_PRIORITY_HIGH,		 								// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_ROUTED_VEHICLE,				// force_info_catagory
			THREAT_TYPE_AAA,												// threat_type
			VIEW_CATEGORY_AIR_DEFENCE_UNITS,							// view_category
			VIEW_TYPE_M163_VULCAN,										// view_type
			MAP_ICON_AAA,													// map icon
			FALSE,															// carries_smoke_grenades

			8.0,																// chase_view_min_distance
			100.0,	  														// chase_view_max_distance
			0.5,																// chase_view_min_distance_test
			550.0,	  														// chase_view_max_distance_test
			knots_to_metres_per_second (20.0),              	// cruise_velocity
			(1.40 + 1.30),													// axle_length
			2.0,																// max_acceleration
			rad (5.0),														// max_turn_rate (rad / second)
			7.0 * G, 														// g_max
			20.0,																// power_output
			2000.0,															// recon_radius
			15.0,																// target_scan_delay
			10.0,																// air_scan_floor
			1000.0,															// air_scan_ceiling
			2500.0,															// air_scan_range
			0.0,																// surface_scan_range
			0.666,															// potential_surface_to_air_threat
			0.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			0.25,																// armour_front
			0.25,																// armour_side
			0.25,																// armour_rear

			600,																// initial_damage_level
			WARHEAD_EFFECTIVE_ARMOURED_VEHICLE,						// armor_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,								// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,										// explosive_power
			TRUE,																// offensive_capability
			100,																// points value

			SOUND_SAMPLE_INDEX_TRUCK_TICKING,						// idle_sound_effect
			SOUND_SAMPLE_INDEX_TRUCK_MOVING,							// moving_sound_effect
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_SA19_GRISON
		//
		////////////////////////////////////////
		{
			"SA-19 Grison",                                 	// full_name
			"SA-19 GRISON", 	  											// long_display_name
			"SA-19",  	 													// short_display_name
			"SAM",															// easy_display_name

			OBJECT_3D_SA19_GRISON,                          	// default_3d_shape
			ENTITY_FORCE_GROUND,                            	// force
			WEAPON_CONFIG_TYPE_SA19_GRISON_1,						// default_weapon_config_type
			WEAPON_CONFIG_TYPE_SA19_GRISON_1,						// min_weapon_config_type
			WEAPON_CONFIG_TYPE_SA19_GRISON_1,						// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_2A38M_30MM_ROUND,				// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_AIR_DEFENCE_UNIT,							// target_symbol_type
			TARGET_PRIORITY_HIGH,		 								// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_ROUTED_VEHICLE,				// force_info_catagory
			THREAT_TYPE_SAM,	  											// threat_type
			VIEW_CATEGORY_AIR_DEFENCE_UNITS,							// view_category
			VIEW_TYPE_SA19_GRISON,										// view_type
			MAP_ICON_AAA,													// map icon
			FALSE,															// carries_smoke_grenades

			8.0,																// chase_view_min_distance
			100.0,	  														// chase_view_max_distance
			0.5,																// chase_view_min_distance_test
			550.0,	  														// chase_view_max_distance_test
			knots_to_metres_per_second (20.0),              	// cruise_velocity
			(2.2832 + 2.5476),											// axle_length
			2.0,																// max_acceleration
			rad (5.0),														// max_turn_rate (rad / second)
			7.0 * G, 														// g_max
			20.0,																// power_output
			6000.0,															// recon_radius
			15.0,																// target_scan_delay
			10.0,																// air_scan_floor
			4000.0,															// air_scan_ceiling
			7500.0,															// air_scan_range
			0.0,																// surface_scan_range
			1.0,																// potential_surface_to_air_threat
			0.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			0.5,																// armour_front
			0.25,																// armour_side
			0.0,																// armour_rear

			600,																// initial_damage_level
			WARHEAD_EFFECTIVE_ARMOURED_VEHICLE,						// armor_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,								// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,										// explosive_power
			TRUE,																// offensive_capability
			150,																// points value

			SOUND_SAMPLE_INDEX_TRUCK_TICKING,						// idle_sound_effect
			SOUND_SAMPLE_INDEX_TRUCK_MOVING,							// moving_sound_effect
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_M1037_AVENGER
		//
		////////////////////////////////////////
		{
			"M1097 Avenger",                                	// full_name
			"M1097 AVENGER", 	  											// long_display_name
			"M1097",  	 													// short_display_name
			"SAM",															// easy_display_name

			OBJECT_3D_BOEING_AVENGER,                       	// default_3d_shape
			ENTITY_FORCE_GROUND,                            	// force
			WEAPON_CONFIG_TYPE_M1037_AVENGER_1,						// default_weapon_config_type
			WEAPON_CONFIG_TYPE_M1037_AVENGER_1,						// min_weapon_config_type
			WEAPON_CONFIG_TYPE_M1037_AVENGER_1,						// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_FIM92A_STINGER,					// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_AIR_DEFENCE_UNIT,							// target_symbol_type
			TARGET_PRIORITY_HIGH,		 								// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_ROUTED_VEHICLE,				// force_info_catagory
			THREAT_TYPE_SAM,												// threat_type
			VIEW_CATEGORY_AIR_DEFENCE_UNITS,							// view_category
			VIEW_TYPE_M1037_AVENGER,									// view_type
			MAP_ICON_AAA,													// map icon
			FALSE,															// carries_smoke_grenades

			8.0,																// chase_view_min_distance
			100.0,	  														// chase_view_max_distance
			0.5,																// chase_view_min_distance_test
			550.0,	  														// chase_view_max_distance_test
			knots_to_metres_per_second (20.0),              	// cruise_velocity
			(1.63 + 1.44),													// axle_length
			2.0,																// max_acceleration
			rad (5.0),														// max_turn_rate (rad / second)
			7.0 * G, 														// g_max
			20.0,																// power_output
			4000.0,															// recon_radius
			15.0,																// target_scan_delay
			10.0,																// air_scan_floor
			3000.0,															// air_scan_ceiling
			4000.0,															// air_scan_range
			0.0,																// surface_scan_range
			1.0,																// potential_surface_to_air_threat
			0.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			0.0,																// armour_front
			0.0,																// armour_side
			0.0,																// armour_rear

			600,																// initial_damage_level
			WARHEAD_EFFECTIVE_LIGHT_VEHICLE,							// armor_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,								// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,										// explosive_power
			TRUE,																// offensive_capability
			125,																// points value

			SOUND_SAMPLE_INDEX_TRUCK_TICKING,						// idle_sound_effect
			SOUND_SAMPLE_INDEX_TRUCK_MOVING,							// moving_sound_effect
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_M48A1_CHAPARRAL
		//
		////////////////////////////////////////
		{
			"M48A1 Chaparral",                              	// full_name
			"M48A1 CHAPARRAL", 	  	 									// long_display_name
			"M48A1",  	 													// short_display_name
			"SAM",															// easy_display_name

			OBJECT_3D_M730A1,                 						// default_3d_shape
			ENTITY_FORCE_GROUND,                            	// force
			WEAPON_CONFIG_TYPE_M48A1_CHAPARRAL_1,	 				// default_weapon_config_type
			WEAPON_CONFIG_TYPE_M48A1_CHAPARRAL_1,	 				// min_weapon_config_type
			WEAPON_CONFIG_TYPE_M48A1_CHAPARRAL_1,	 				// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_MIM_72G_CHAPARRAL,						// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_AIR_DEFENCE_UNIT,							// target_symbol_type
			TARGET_PRIORITY_HIGH,		 								// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_ROUTED_VEHICLE,				// force_info_catagory
			THREAT_TYPE_SAM,												// threat_type
			VIEW_CATEGORY_AIR_DEFENCE_UNITS,							// view_category
			VIEW_TYPE_M48A1_CHAPARRAL,									// view_type
			MAP_ICON_AAA,													// map icon
			FALSE,															// carries_smoke_grenades

			8.0,																// chase_view_min_distance
			100.0,	  														// chase_view_max_distance
			0.5,																// chase_view_min_distance_test
			550.0,	  														// chase_view_max_distance_test
			knots_to_metres_per_second (20.0),              	// cruise_velocity
			(1.395 + 1.515),												// axle_length
			2.0,																// max_acceleration
			rad (5.0),														// max_turn_rate (rad / second)
			7.0 * G, 														// g_max
			20.0,																// power_output
			4000.0,															// recon_radius
			15.0,																// target_scan_delay
			10.0,																// air_scan_floor
			3000.0,															// air_scan_ceiling
			5000.0,															// air_scan_range
			0.0,																// surface_scan_range
			1.0,																// potential_surface_to_air_threat
			0.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			0.0,																// armour_front
			0.0,																// armour_side
			0.0,																// armour_rear

			600,																// initial_damage_level
			WARHEAD_EFFECTIVE_LIGHT_VEHICLE,							// armor_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,								// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,										// explosive_power
			TRUE,																// offensive_capability
			125,																// points value

			SOUND_SAMPLE_INDEX_TRUCK_TICKING,						// idle_sound_effect
			SOUND_SAMPLE_INDEX_TRUCK_MOVING,							// moving_sound_effect
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_SA13_GOPHER
		//
		////////////////////////////////////////
		{
			"SA-13 Gopher",                                 	// full_name
			"SA-13 GOPHER", 	  	 										// long_display_name
			"SA-13",  	 													// short_display_name
			"SAM",															// easy_display_name

			OBJECT_3D_SA13,												// default_3d_shape
			ENTITY_FORCE_GROUND,                            	// force
			WEAPON_CONFIG_TYPE_SA13_GOPHER_1,						// default_weapon_config_type
			WEAPON_CONFIG_TYPE_SA13_GOPHER_1,						// min_weapon_config_type
			WEAPON_CONFIG_TYPE_SA13_GOPHER_1,						// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_9M333,						// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_AIR_DEFENCE_UNIT,							// target_symbol_type
			TARGET_PRIORITY_HIGH,		 								// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_ROUTED_VEHICLE,				// force_info_catagory
			THREAT_TYPE_SAM,												// threat_type
			VIEW_CATEGORY_AIR_DEFENCE_UNITS,							// view_category
			VIEW_TYPE_SA13_GOPHER,										// view_type
			MAP_ICON_AAA,													// map icon
			FALSE,															// carries_smoke_grenades

			8.0,																// chase_view_min_distance
			100.0,	  														// chase_view_max_distance
			0.5,																// chase_view_min_distance_test
			550.0,	  														// chase_view_max_distance_test
			knots_to_metres_per_second (20.0),              	// cruise_velocity
			(1.7832 + 2.0776),											// axle_length
			2.0,																// max_acceleration
			rad (5.0),														// max_turn_rate (rad / second)
			7.0 * G, 														// g_max
			20.0,																// power_output
			3000.0,															// recon_radius
			15.0,																// target_scan_delay
			10.0,																// air_scan_floor
			3000.0,															// air_scan_ceiling
			5000.0,															// air_scan_range
			0.0,																// surface_scan_range
			1.0,																// potential_surface_to_air_threat
			0.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			0.5,																// armour_front
			0.25,																// armour_side
			0.0,																// armour_rear

			600,																// initial_damage_level
			WARHEAD_EFFECTIVE_LIGHT_VEHICLE,							// armor_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,								// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,										// explosive_power
			TRUE,																// offensive_capability
			100,																// points value

			SOUND_SAMPLE_INDEX_TRUCK_TICKING,						// idle_sound_effect
			SOUND_SAMPLE_INDEX_TRUCK_MOVING,							// moving_sound_effect
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_M998_HUMVEE
		//
		////////////////////////////////////////
		{
			"M998 HumVee",                                  	// full_name
			"M998 HUMVEE", 	  	 										// long_display_name
			"M998",  	 													// short_display_name
			"VEHICLE", 														// easy_display_name

			OBJECT_3D_M998,												// default_3d_shape
			ENTITY_FORCE_GROUND,                            	// force
			WEAPON_CONFIG_TYPE_UNARMED,								// default_weapon_config_type
			WEAPON_CONFIG_TYPE_UNARMED,								// min_weapon_config_type
			WEAPON_CONFIG_TYPE_UNARMED,								// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, 	 					// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_WHEELED_VEHICLE,							// target_symbol_type
			TARGET_PRIORITY_LOW,			 								// target_priority_type
			FORCE_INFO_CATAGORY_UNARMED_ROUTED_VEHICLE,			// force_info_catagory
			THREAT_TYPE_INVALID,											// threat_type
			VIEW_CATEGORY_TRANSPORT_VEHICLES,						// view_category
			VIEW_TYPE_M998_HUMVEE,										// view_type
			MAP_ICON_APC,													// map icon
			FALSE,															// carries_smoke_grenades

			8.0,																// chase_view_min_distance
			100.0,	  														// chase_view_max_distance
			0.5,																// chase_view_min_distance_test
			550.0,	  														// chase_view_max_distance_test
			knots_to_metres_per_second (20.0),              	// cruise_velocity
			(1.6275 + 1.4375),											// axle_length
			2.0,																// max_acceleration
			rad (5.0),														// max_turn_rate (rad / second)
			7.0 * G, 														// g_max
			20.0,																// power_output
			1000.0,															// recon_radius
			0.0,																// target_scan_delay
			0.0,																// air_scan_floor
			0.0,																// air_scan_ceiling
			0.0,																// air_scan_range
			0.0,																// surface_scan_range
			0.0,																// potential_surface_to_air_threat
			0.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			0.0,																// armour_front
			0.0,																// armour_side
			0.0,																// armour_rear

			350,																// initial_damage_level
			WARHEAD_EFFECTIVE_LIGHT_VEHICLE,							// armor_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,								// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,										// explosive_power
			FALSE,															// offensive_capability
			50,																	// points value

			SOUND_SAMPLE_INDEX_JEEP_TICKING,							// idle_sound_effect
			SOUND_SAMPLE_INDEX_JEEP_MOVING,							// moving_sound_effect
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_UAZ469B
		//
		////////////////////////////////////////
		{
			"UAZ-469B",                                     	// full_name
			"UAZ-469B", 	  		 										// long_display_name
			"UAZ-469B",  													// short_display_name
			"VEHICLE", 														// easy_display_name

			OBJECT_3D_UAZ,     						            	// default_3d_shape
			ENTITY_FORCE_GROUND,                            	// force
			WEAPON_CONFIG_TYPE_UNARMED,								// default_weapon_config_type
			WEAPON_CONFIG_TYPE_UNARMED,								// min_weapon_config_type
			WEAPON_CONFIG_TYPE_UNARMED,								// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, 	 					// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_WHEELED_VEHICLE,							// target_symbol_type
			TARGET_PRIORITY_LOW,			 								// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_ROUTED_VEHICLE,				// force_info_catagory
			THREAT_TYPE_INVALID,											// threat_type
			VIEW_CATEGORY_TRANSPORT_VEHICLES,						// view_category
			VIEW_TYPE_UAZ469B,											// view_type
			MAP_ICON_APC,													// map icon
			FALSE,															// carries_smoke_grenades

			8.0,																// chase_view_min_distance
			100.0,	  														// chase_view_max_distance
			0.5,																// chase_view_min_distance_test
			550.0,	  														// chase_view_max_distance_test
			knots_to_metres_per_second (20.0),              	// cruise_velocity
			(1.31 + 1.04),													// axle_length
			2.0,																// max_acceleration
			rad (5.0),														// max_turn_rate (rad / second)
			7.0 * G, 														// g_max
			20.0,																// power_output
			1000.0,															// recon_radius
			0.0,																// target_scan_delay
			0.0,																// air_scan_floor
			0.0,																// air_scan_ceiling
			0.0,																// air_scan_range
			0.0,																// surface_scan_range
			0.0,																// potential_surface_to_air_threat
			0.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			0.0,																// armour_front
			0.0,																// armour_side
			0.0,																// armour_rear

			350,																// initial_damage_level
			WARHEAD_EFFECTIVE_LIGHT_VEHICLE,							// armor_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,								// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,										// explosive_power
			FALSE,															// offensive_capability
			50,																// points value

			SOUND_SAMPLE_INDEX_JEEP_TICKING,							// idle_sound_effect
			SOUND_SAMPLE_INDEX_JEEP_MOVING,							// moving_sound_effect
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_M923A1_BIG_FOOT
		//
		////////////////////////////////////////
		{
			"M923A1 Big Foot",											// full_name
			"M923A1 BIG FOOT", 	  	 									// long_display_name
			"M923A1",  														// short_display_name
			"VEHICLE", 														// easy_display_name

			OBJECT_3D_M_923A1_OPEN,										// default_3d_shape
			ENTITY_FORCE_GROUND,                            	// force
			WEAPON_CONFIG_TYPE_UNARMED,								// default_weapon_config_type
			WEAPON_CONFIG_TYPE_UNARMED,								// min_weapon_config_type
			WEAPON_CONFIG_TYPE_UNARMED,								// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, 	 					// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_WHEELED_VEHICLE,							// target_symbol_type
			TARGET_PRIORITY_LOW,			 								// target_priority_type
			FORCE_INFO_CATAGORY_UNARMED_ROUTED_VEHICLE,			// force_info_catagory
			THREAT_TYPE_INVALID,											// threat_type
			VIEW_CATEGORY_TRANSPORT_VEHICLES,						// view_category
			VIEW_TYPE_M923A1_BIG_FOOT,									// view_type
			MAP_ICON_APC,													// map icon
			FALSE,															// carries_smoke_grenades

			8.0,																// chase_view_min_distance
			100.0,	  														// chase_view_max_distance
			0.5,																// chase_view_min_distance_test
			550.0,	  														// chase_view_max_distance_test
			knots_to_metres_per_second (20.0),              	// cruise_velocity
			(2.69 + 2.36),													// axle_length
			2.0,																// max_acceleration
			rad (5.0),														// max_turn_rate (rad / second)
			7.0 * G, 														// g_max
			20.0,																// power_output
			1000.0,															// recon_radius
			0.0,																// target_scan_delay
			0.0,																// air_scan_floor
			0.0,																// air_scan_ceiling
			0.0,																// air_scan_range
			0.0,																// surface_scan_range
			0.0,																// potential_surface_to_air_threat
			0.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			0.0,																// armour_front
			0.0,																// armour_side
			0.0,																// armour_rear

			350,																// initial_damage_level
			WARHEAD_EFFECTIVE_LIGHT_VEHICLE,							// armor_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,								// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,										// explosive_power
			FALSE,															// offensive_capability
			50,																// points value

			SOUND_SAMPLE_INDEX_TRUCK_TICKING,						// idle_sound_effect
			SOUND_SAMPLE_INDEX_TRUCK_MOVING,							// moving_sound_effect
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_M923A1_BIG_FOOT_COVERED
		//
		////////////////////////////////////////
		{
			"M923A1 Big Foot",											// full_name
			"M923A1 BIG FOOT", 	  	 									// long_display_name
			"M923A1",  														// short_display_name
			"VEHICLE", 														// easy_display_name

			OBJECT_3D_M_923A1_COVERED,									// default_3d_shape
			ENTITY_FORCE_GROUND,                            	// force
			WEAPON_CONFIG_TYPE_UNARMED,								// default_weapon_config_type
			WEAPON_CONFIG_TYPE_UNARMED,								// min_weapon_config_type
			WEAPON_CONFIG_TYPE_UNARMED,								// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, 	 					// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_WHEELED_VEHICLE,							// target_symbol_type
			TARGET_PRIORITY_LOW,			 								// target_priority_type
			FORCE_INFO_CATAGORY_UNARMED_ROUTED_VEHICLE,			// force_info_catagory
			THREAT_TYPE_INVALID,											// threat_type
			VIEW_CATEGORY_TRANSPORT_VEHICLES,						// view_category
			VIEW_TYPE_M923A1_BIG_FOOT,									// view_type
			MAP_ICON_APC,													// map icon
			FALSE,															// carries_smoke_grenades

			8.0,																// chase_view_min_distance
			100.0,	  														// chase_view_max_distance
			0.5,																// chase_view_min_distance_test
			550.0,	  														// chase_view_max_distance_test
			knots_to_metres_per_second (20.0),              	// cruise_velocity
			(2.69 + 2.36),													// axle_length
			2.0,																// max_acceleration
			rad (5.0),														// max_turn_rate (rad / second)
			7.0 * G, 														// g_max
			20.0,																// power_output
			1000.0,															// recon_radius
			0.0,																// target_scan_delay
			0.0,																// air_scan_floor
			0.0,																// air_scan_ceiling
			0.0,																// air_scan_range
			0.0,																// surface_scan_range
			0.0,																// potential_surface_to_air_threat
			0.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			0.0,																// armour_front
			0.0,																// armour_side
			0.0,																// armour_rear

			350,																// initial_damage_level
			WARHEAD_EFFECTIVE_LIGHT_VEHICLE,							// armor_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,								// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,										// explosive_power
			FALSE,															// offensive_capability
			50,																// points value

			SOUND_SAMPLE_INDEX_TRUCK_TICKING,						// idle_sound_effect
			SOUND_SAMPLE_INDEX_TRUCK_MOVING,							// moving_sound_effect
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_URAL_4320
		//
		////////////////////////////////////////
		{
			"Ural-4320",													// full_name
			"URAL-4320", 	 		 	 									// long_display_name
			"URAL-4320",  													// short_display_name
			"VEHICLE", 														// easy_display_name

			OBJECT_3D_URAL_4320,											// default_3d_shape
			ENTITY_FORCE_GROUND,                            	// force
			WEAPON_CONFIG_TYPE_UNARMED,								// default_weapon_config_type
			WEAPON_CONFIG_TYPE_UNARMED,								// min_weapon_config_type
			WEAPON_CONFIG_TYPE_UNARMED,								// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, 	 					// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_WHEELED_VEHICLE,							// target_symbol_type
			TARGET_PRIORITY_LOW,			 								// target_priority_type
			FORCE_INFO_CATAGORY_UNARMED_ROUTED_VEHICLE,			// force_info_catagory
			THREAT_TYPE_INVALID,											// threat_type
			VIEW_CATEGORY_TRANSPORT_VEHICLES,						// view_category
			VIEW_TYPE_URAL_4320,											// view_type
			MAP_ICON_APC,													// map icon
			FALSE,															// carries_smoke_grenades

			8.0,																// chase_view_min_distance
			100.0,	  														// chase_view_max_distance
			0.5,																// chase_view_min_distance_test
			550.0,	  														// chase_view_max_distance_test
			knots_to_metres_per_second (20.0),              	// cruise_velocity
			(2.46 + 2.50),													// axle_length
			2.0,																// max_acceleration
			rad (5.0),														// max_turn_rate (rad / second)
			7.0 * G, 														// g_max
			20.0,																// power_output
			1000.0,															// recon_radius
			0.0,																// target_scan_delay
			0.0,																// air_scan_floor
			0.0,																// air_scan_ceiling
			0.0,																// air_scan_range
			0.0,																// surface_scan_range
			0.0,																// potential_surface_to_air_threat
			0.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			0.0,																// armour_front
			0.0,																// armour_side
			0.0,																// armour_rear

			300,																// initial_damage_level
			WARHEAD_EFFECTIVE_LIGHT_VEHICLE,							// armor_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,								// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,										// explosive_power
			FALSE,															// offensive_capability
			50,																// points value

			SOUND_SAMPLE_INDEX_TRUCK_TICKING,						// idle_sound_effect
			SOUND_SAMPLE_INDEX_TRUCK_MOVING,							// moving_sound_effect
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_M978_HEMTT
		//
		////////////////////////////////////////
		{
			"M978 HEMTT",													// full_name
			"M978 HEMTT", 	 		 	 									// long_display_name
			"M978",		  													// short_display_name
			"VEHICLE", 														// easy_display_name

			OBJECT_3D_M_978,												// default_3d_shape
			ENTITY_FORCE_GROUND,                            	// force
			WEAPON_CONFIG_TYPE_UNARMED,								// default_weapon_config_type
			WEAPON_CONFIG_TYPE_UNARMED,								// min_weapon_config_type
			WEAPON_CONFIG_TYPE_UNARMED,								// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_NO_WEAPON,	 					// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_WHEELED_VEHICLE,  							// target_symbol_type
			TARGET_PRIORITY_LOW,			 								// target_priority_type
			FORCE_INFO_CATAGORY_UNARMED_ROUTED_VEHICLE,			// force_info_catagory
			THREAT_TYPE_INVALID,											// threat_type
			VIEW_CATEGORY_TRANSPORT_VEHICLES,						// view_category
			VIEW_TYPE_M978_HEMTT,										// view_type
			MAP_ICON_APC,													// map icon
			FALSE,															// carries_smoke_grenades

			8.0,																// chase_view_min_distance
			100.0,	  														// chase_view_max_distance
			0.5,																// chase_view_min_distance_test
			550.0,	  														// chase_view_max_distance_test
			knots_to_metres_per_second (20.0),              	// cruise_velocity
			(3.20 + 3.70),													// axle_length
			2.0,																// max_acceleration
			rad (5.0),														// max_turn_rate (rad / second)
			7.0 * G, 														// g_max
			20.0,																// power_output
			1000.0,															// recon_radius
			0.0,																// target_scan_delay
			0.0,																// air_scan_floor
			0.0,																// air_scan_ceiling
			0.0,																// air_scan_range
			0.0,																// surface_scan_range
			0.0,																// potential_surface_to_air_threat
			0.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			0.0,																// armour_front
			0.0,																// armour_side
			0.0,																// armour_rear

			300,																// initial_damage_level
			WARHEAD_EFFECTIVE_LIGHT_VEHICLE,							// armor_level

			EXPLOSIVE_QUALITY_EXPLOSIVE, 								// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,										// explosive_power
			FALSE,															// offensive_capability
			50,																// points value

			SOUND_SAMPLE_INDEX_TRUCK_TICKING,						// idle_sound_effect
			SOUND_SAMPLE_INDEX_TRUCK_MOVING,							// moving_sound_effect
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_URAL_FUEL_TANKER
		//
		////////////////////////////////////////
		{
			"Ural Fuel Tanker",		  									// full_name
			"URAL FUEL TANKER", 	 		 								// long_display_name
			"FUEL TANKER",  	 											// short_display_name
			"VEHICLE", 														// easy_display_name

			OBJECT_3D_URAL_FUEL,											// default_3d_shape
			ENTITY_FORCE_GROUND,                            	// force
			WEAPON_CONFIG_TYPE_UNARMED,								// default_weapon_config_type
			WEAPON_CONFIG_TYPE_UNARMED,								// min_weapon_config_type
			WEAPON_CONFIG_TYPE_UNARMED,								// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_NO_WEAPON,	 					// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_WHEELED_VEHICLE,  							// target_symbol_type
			TARGET_PRIORITY_LOW,			 								// target_priority_type
			FORCE_INFO_CATAGORY_UNARMED_ROUTED_VEHICLE,			// force_info_catagory
			THREAT_TYPE_INVALID,											// threat_type
			VIEW_CATEGORY_TRANSPORT_VEHICLES,						// view_category
			VIEW_TYPE_URAL_FUEL_TANKER,								// view_type
			MAP_ICON_APC,													// map icon
			FALSE,															// carries_smoke_grenades

			8.0,																// chase_view_min_distance
			100.0,	  														// chase_view_max_distance
			0.5,																// chase_view_min_distance_test
			550.0,	  														// chase_view_max_distance_test
			knots_to_metres_per_second (20.0),              	// cruise_velocity
			(2.46 + 2.50),													// axle_length
			2.0,																// max_acceleration
			rad (5.0),														// max_turn_rate (rad / second)
			7.0 * G, 														// g_max
			20.0,																// power_output
			1000.0,															// recon_radius
			0.0,																// target_scan_delay
			0.0,																// air_scan_floor
			0.0,																// air_scan_ceiling
			0.0,																// air_scan_range
			0.0,																// surface_scan_range
			0.0,																// potential_surface_to_air_threat
			0.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			0.0,																// armour_front
			0.0,																// armour_side
			0.0,																// armour_rear

			300,																// initial_damage_level
			WARHEAD_EFFECTIVE_LIGHT_VEHICLE,							// armor_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,								// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,										// explosive_power
			FALSE,															// offensive_capability
			50,																// points value

			SOUND_SAMPLE_INDEX_TRUCK_TICKING,						// idle_sound_effect
			SOUND_SAMPLE_INDEX_TRUCK_MOVING,							// moving_sound_effect
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_TARAWA_CLASS
		//
		////////////////////////////////////////
		{
			"Tarawa Class",                                 	// full_name
			"TARAWA CLASS", 	  			 								// long_display_name
			"TARAWA",  		  												// short_display_name
			"CARRIER", 														// easy_display_name

			OBJECT_3D_TARAWA,                               	// default_3d_shape
			ENTITY_FORCE_SEA,                               	// force
			WEAPON_CONFIG_TYPE_TARAWA_CLASS_1,						// default_weapon_config_type
			WEAPON_CONFIG_TYPE_TARAWA_CLASS_1,						// min_weapon_config_type
			WEAPON_CONFIG_TYPE_TARAWA_CLASS_1,						// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_M61A1_CIWS_20MM_ROUND,				// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_SHIP,											// target_symbol_type
			TARGET_PRIORITY_HIGH,		 								// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_SHIP_VEHICLE,				// force_info_catagory
			THREAT_TYPE_SAM, 												// threat_type
			VIEW_CATEGORY_WARSHIPS,										// view_category
			VIEW_TYPE_TARAWA_CLASS,										// view_type
			MAP_ICON_CARRIER,												// map icon
			FALSE,															// carries_smoke_grenades

			250.0,															// chase_view_min_distance
			1000.0,	  														// chase_view_max_distance
			0.5,			  													// chase_view_min_distance_test
			5100.0,	  														// chase_view_max_distance_test
			knots_to_metres_per_second (24.0),	            	// cruise_velocity
			(100),															// axle_length
			2.0,																// max_acceleration
			rad (5.0),														// max_turn_rate (rad / second)
			0.02 * G, 														// g_max
			20.0,																// power_output
			8000.0,															// recon_radius
			15.0,																// target_scan_delay
			10.0,																// air_scan_floor
			5000.0,															// air_scan_ceiling
			10000.0,															// air_scan_range
			0.0,																// surface_scan_range
			0.8,																// potential_surface_to_air_threat
			0.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			0.0,																// armour_front
			0.0,																// armour_side
			0.0,																// armour_rear

			12000,															// initial_damage_level
			WARHEAD_EFFECTIVE_CARRIER,									// armor_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,								// explosive_quality
			EXPLOSIVE_POWER_HIGH,										// explosive_power
			TRUE,																// offensive_capability
			3000,																// points value

			SOUND_SAMPLE_INDEX_NONE,									// idle_sound_effect
			SOUND_SAMPLE_INDEX_NONE,									// moving_sound_effect
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_KIEV_CLASS
		//
		////////////////////////////////////////
		{
			"Kiev Class",                                   	// full_name
			"KIEV CLASS", 	  				 								// long_display_name
			"KIEV",  		  												// short_display_name
			"CARRIER", 														// easy_display_name

			OBJECT_3D_KIEV_CLASS,                           	// default_3d_shape
			ENTITY_FORCE_SEA,                               	// force
			WEAPON_CONFIG_TYPE_KIEV_CLASS_1,		  					// default_weapon_config_type
			WEAPON_CONFIG_TYPE_KIEV_CLASS_1,		  					// min_weapon_config_type
			WEAPON_CONFIG_TYPE_KIEV_CLASS_1,		  					// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_AK_630_30MM_ROUND,			// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_SHIP,											// target_symbol_type
			TARGET_PRIORITY_HIGH,		 								// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_SHIP_VEHICLE,				// force_info_catagory
			THREAT_TYPE_SAM,												// threat_type
			VIEW_CATEGORY_WARSHIPS,										// view_category
			VIEW_TYPE_KIEV_CLASS,										// view_type
			MAP_ICON_CARRIER,												// map icon
			FALSE,															// carries_smoke_grenades

			250.0,															// chase_view_min_distance
			1000.0,	  														// chase_view_max_distance
			0.5,	  															// chase_view_min_distance_test
			5100.0,	  														// chase_view_max_distance_test
			knots_to_metres_per_second (32.0),               	// cruise_velocity
			(100),															// axle_length
			2.0,																// max_acceleration
			rad (5.0),														// max_turn_rate (rad / second)
			0.02 * G, 														// g_max
			20.0,																// power_output
			8000.0,															// recon_radius
			15.0,																// target_scan_delay
			10.0,																// air_scan_floor
			5000.0,															// air_scan_ceiling
			10000.0,															// air_scan_range
			0.0,																// surface_scan_range
			0.8,																// potential_surface_to_air_threat
			0.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			0.0,																// armour_front
			0.0,																// armour_side
			0.0,																// armour_rear

			15000,															// initial_damage_level
			WARHEAD_EFFECTIVE_CARRIER,									// armor_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,								// explosive_quality
			EXPLOSIVE_POWER_HIGH,										// explosive_power
			TRUE,																// offensive_capability
			3500,																// points value

			SOUND_SAMPLE_INDEX_NONE,									// idle_sound_effect
			SOUND_SAMPLE_INDEX_NONE,									// moving_sound_effect
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_OLIVER_HAZARD_PERRY_CLASS
		//
		////////////////////////////////////////
		{
			"Oliver Hazard Perry Class",								// full_name
			"OLIVER HAZARD PERRY CLASS", 	  							// long_display_name
			"OHP",  	  		  												// short_display_name
			"FRIGATE", 														// easy_display_name

			OBJECT_3D_OLIVER_HAZARD_PERRY,							// default_3d_shape
			ENTITY_FORCE_SEA,												// force
			WEAPON_CONFIG_TYPE_OLIVER_HAZARD_PERRY_CLASS_1,		// default_weapon_config_type
			WEAPON_CONFIG_TYPE_OLIVER_HAZARD_PERRY_CLASS_1,		// min_weapon_config_type
			WEAPON_CONFIG_TYPE_OLIVER_HAZARD_PERRY_CLASS_1,		// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_RIM_66B_STANDARD,					// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_SHIP,											// target_symbol_type
			TARGET_PRIORITY_HIGH,		 								// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_SHIP_VEHICLE,				// force_info_catagory
			THREAT_TYPE_SAM, 												// threat_type
			VIEW_CATEGORY_WARSHIPS,										// view_category
			VIEW_TYPE_OLIVER_HAZARD_PERRY_CLASS,					// view_type
			MAP_ICON_SHIP,													// map icon
			FALSE,															// carries_smoke_grenades

			125.0,															// chase_view_min_distance
			750.0,	  														// chase_view_max_distance
			0.5,																// chase_view_min_distance_test
			5100.0,	  														// chase_view_max_distance_test
			knots_to_metres_per_second (29.0),						// cruise_velocity
			(100),															// axle_length
			2.0,																// max_acceleration
			rad (5.0),														// max_turn_rate (rad / second)
			0.05 * G, 														// g_max
			20.0,																// power_output
			6000.0,															// recon_radius
			15.0,																// target_scan_delay
			10.0,																// air_scan_floor
			5000.0,															// air_scan_ceiling
			8000.0,															// air_scan_range
			0.0,																// surface_scan_range
			1.0,																// potential_surface_to_air_threat
			0.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			0.0,																// armour_front
			0.0,																// armour_side
			0.0,																// armour_rear

			8000,																// initial_damage_level
			WARHEAD_EFFECTIVE_FRIGATE,									// armor_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,								// explosive_quality
			EXPLOSIVE_POWER_HIGH,										// explosive_power
			TRUE,																// offensive_capability
			1500,																// points value

			SOUND_SAMPLE_INDEX_NONE,									// idle_sound_effect
			SOUND_SAMPLE_INDEX_SHIP_MOVING,							// moving_sound_effect
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_KRIVAK_II_CLASS
		//
		////////////////////////////////////////
		{
			"Krivak II Class",											// full_name
			"KRIVAK II CLASS", 	  										// long_display_name
			"KRIVAK",  		  												// short_display_name
			"FRIGATE", 														// easy_display_name

			OBJECT_3D_KRIVAK_2,											// default_3d_shape
			ENTITY_FORCE_SEA,												// force
			WEAPON_CONFIG_TYPE_KRIVAK_II_CLASS_1,					// default_weapon_config_type
			WEAPON_CONFIG_TYPE_KRIVAK_II_CLASS_1,					// min_weapon_config_type
			WEAPON_CONFIG_TYPE_KRIVAK_II_CLASS_1,					// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_9M33_OSA,						// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_SHIP,											// target_symbol_type
			TARGET_PRIORITY_HIGH,		 								// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_SHIP_VEHICLE,				// force_info_catagory
			THREAT_TYPE_SAM,												// threat_type
			VIEW_CATEGORY_WARSHIPS,										// view_category
			VIEW_TYPE_KRIVAK_II_CLASS,									// view_type
			MAP_ICON_SHIP,													// map icon
			FALSE,															// carries_smoke_grenades

			125.0,															// chase_view_min_distance
			750.0,	  														// chase_view_max_distance
			0.5,		 														// chase_view_min_distance_test
			5100.0,	  														// chase_view_max_distance_test
			knots_to_metres_per_second (32.0),						// cruise_velocity
			(100),															// axle_length
			2.0,																// max_acceleration
			rad (5.0),														// max_turn_rate (rad / second)
			0.05 * G, 														// g_max
			20.0,																// power_output
			6000.0,															// recon_radius
			15.0,																// target_scan_delay
			10.0,																// air_scan_floor
			5000.0,															// air_scan_ceiling
			8000.0,															// air_scan_range
			0.0,																// surface_scan_range
			1.0,																// potential_surface_to_air_threat
			0.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			0.0,																// armour_front
			0.0,																// armour_side
			0.0,																// armour_rear

			8000,																// initial_damage_level
			WARHEAD_EFFECTIVE_FRIGATE,									// armor_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,								// explosive_quality
			EXPLOSIVE_POWER_HIGH,										// explosive_power
			TRUE,																// offensive_capability
			1000,																// points value

			SOUND_SAMPLE_INDEX_NONE,									// idle_sound_effect
			SOUND_SAMPLE_INDEX_SHIP_MOVING,							// moving_sound_effect
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_LCU
		//
		////////////////////////////////////////
		{
			"Landing Craft Utility",	  								// full_name
			"LANDING CRAFT UTILITY", 									// long_display_name
			"LCU",  		 	 												// short_display_name
			"CRAFT", 														// easy_display_name

			OBJECT_3D_TARAWA_LANDING_CRAFT,                 	// default_3d_shape
			ENTITY_FORCE_SEA,                               	// force
			WEAPON_CONFIG_TYPE_UNARMED,								// default_weapon_config_type
			WEAPON_CONFIG_TYPE_UNARMED,								// min_weapon_config_type
			WEAPON_CONFIG_TYPE_UNARMED,								// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_NO_WEAPON,	 					// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_SHIP,											// target_symbol_type
			TARGET_PRIORITY_LOW,			 								// target_priority_type
			FORCE_INFO_CATAGORY_UNARMED_SHIP_VEHICLE,				// force_info_catagory
			THREAT_TYPE_INVALID,											// threat_type
			VIEW_CATEGORY_WARSHIPS,										// view_category
			VIEW_TYPE_LCU,													// view_type
			MAP_ICON_SHIP,													// map icon
			FALSE,															// carries_smoke_grenades

			25.0,																// chase_view_min_distance
			300.0,	  														// chase_view_max_distance
			0.5,			  													// chase_view_min_distance_test
			500.0,	  														// chase_view_max_distance_test
			knots_to_metres_per_second (7.5),	            	// cruise_velocity
			(100),															// axle_length
			2.0,																// max_acceleration
			rad (5.0),														// max_turn_rate (rad / second)
			0.1 * G, 														// g_max
			20.0,																// power_output
			1000.0,															// recon_radius
			0.0,																// target_scan_delay
			0.0,																// air_scan_floor
			0.0,																// air_scan_ceiling
			0.0,																// air_scan_range
			0.0,																// surface_scan_range
			0.0,																// potential_surface_to_air_threat
			0.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			0.0,																// armour_front
			0.0,																// armour_side
			0.0,																// armour_rear

			1000,																// initial_damage_level
			WARHEAD_EFFECTIVE_LIGHT_SHIP,								// armor_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,								// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,										// explosive_power
			FALSE,															// offensive_capability
			50,																// points value

			SOUND_SAMPLE_INDEX_NONE,									// idle_sound_effect
			SOUND_SAMPLE_INDEX_NONE,									// moving_sound_effect
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_LCAC
		//
		////////////////////////////////////////
		{
			"Landing Craft Air Cushioned",							// full_name
			"LANDING CRAFT (LCAC)",			 	  						// long_display_name
			"LCAC",  	 	 												// short_display_name
			"CRAFT", 														// easy_display_name

			OBJECT_3D_LCAC,												// default_3d_shape
			ENTITY_FORCE_SEA,                               	// force
			WEAPON_CONFIG_TYPE_UNARMED,								// default_weapon_config_type
			WEAPON_CONFIG_TYPE_UNARMED,								// min_weapon_config_type
			WEAPON_CONFIG_TYPE_UNARMED,								// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_NO_WEAPON,  						// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_SHIP,											// target_symbol_type
			TARGET_PRIORITY_LOW,			 								// target_priority_type
			FORCE_INFO_CATAGORY_UNARMED_SHIP_VEHICLE,				// force_info_catagory
			THREAT_TYPE_INVALID,											// threat_type
			VIEW_CATEGORY_WARSHIPS,										// view_category
			VIEW_TYPE_LCAC,												// view_type
			MAP_ICON_SHIP,													// map icon
			FALSE,															// carries_smoke_grenades

			25.0,																// chase_view_min_distance
			300.0,	  														// chase_view_max_distance
			0.5,			  													// chase_view_min_distance_test
			500.0,	  														// chase_view_max_distance_test
			knots_to_metres_per_second (7.5),	            	// cruise_velocity
			(100),															// axle_length
			2.0,																// max_acceleration
			rad (5.0),														// max_turn_rate (rad / second)
			0.1 * G, 														// g_max
			20.0,																// power_output
			1000.0,															// recon_radius
			0.0,																// target_scan_delay
			0.0,																// air_scan_floor
			0.0,																// air_scan_ceiling
			0.0,																// air_scan_range
			0.0,																// surface_scan_range
			0.0,																// potential_surface_to_air_threat
			0.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			0.0,																// armour_front
			0.0,																// armour_side
			0.0,																// armour_rear

			1000,																// initial_damage_level
			WARHEAD_EFFECTIVE_LIGHT_SHIP,								// armor_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,								// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,										// explosive_power
			FALSE,															// offensive_capability
			50,																// points value

			SOUND_SAMPLE_INDEX_HOVERCRAFT_TICKING,					// idle_sound_effect
			SOUND_SAMPLE_INDEX_HOVERCRAFT_MOVING,					// moving_sound_effect
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_AIST_CLASS
		//
		////////////////////////////////////////
		{
			"Aist Class",			 										// full_name
			"AIST CLASS", 	  												// long_display_name
			"AIST",  	 	 												// short_display_name
			"CRAFT", 														// easy_display_name

			OBJECT_3D_AIST_HOVERCRAFT,									// default_3d_shape
			ENTITY_FORCE_SEA,                               	// force
			WEAPON_CONFIG_TYPE_AIST_CLASS_1,							// default_weapon_config_type
			WEAPON_CONFIG_TYPE_AIST_CLASS_1,							// min_weapon_config_type
			WEAPON_CONFIG_TYPE_AIST_CLASS_1,							// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_AK_630_30MM_ROUND,			// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_SHIP,											// target_symbol_type
			TARGET_PRIORITY_HIGH, 		 								// target_priority_type
			FORCE_INFO_CATAGORY_UNARMED_SHIP_VEHICLE,				// force_info_catagory
			THREAT_TYPE_AAA,		 										// threat_type
			VIEW_CATEGORY_WARSHIPS,										// view_category
			VIEW_TYPE_AIST_CLASS,										// view_type
			MAP_ICON_SHIP,													// map icon
			FALSE,															// carries_smoke_grenades

			30.0,																// chase_view_min_distance
			350.0,	  														// chase_view_max_distance
			0.5,			  													// chase_view_min_distance_test
			500.0,	  														// chase_view_max_distance_test
			knots_to_metres_per_second (7.5),	            	// cruise_velocity
			(100),															// axle_length
			2.0,																// max_acceleration
			rad (5.0),														// max_turn_rate (rad / second)
			0.1 * G, 														// g_max
			20.0,																// power_output
			1000.0,															// recon_radius
			15.0,																// target_scan_delay
			10.0,																// air_scan_floor
			1000.0,															// air_scan_ceiling
			2000.0,															// air_scan_range
			0.0,																// surface_scan_range
			0.666,	 														// potential_surface_to_air_threat
			0.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			0.0,																// armour_front
			0.0,																// armour_side
			0.0,																// armour_rear

			1000,																// initial_damage_level
			WARHEAD_EFFECTIVE_LIGHT_SHIP,								// armor_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,								// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,										// explosive_power
			TRUE,																// offensive_capability
			50,																// points value

			SOUND_SAMPLE_INDEX_HOVERCRAFT_TICKING,					// idle_sound_effect
			SOUND_SAMPLE_INDEX_HOVERCRAFT_MOVING,					// moving_sound_effect
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_US_INFANTRY
		//
		////////////////////////////////////////
		{
			"Infantry",     		                            	// full_name
			"INFANTRY", 	  	  											// long_display_name
			"INFANTRY",  	 	  											// short_display_name
			"INFANTRY", 													// easy_display_name

			OBJECT_3D_US_MARINE_WALK,									// default_3d_shape
			ENTITY_FORCE_GROUND,                            	// force
			WEAPON_CONFIG_TYPE_US_INFANTRY_1,								// default_weapon_config_type
			WEAPON_CONFIG_TYPE_US_INFANTRY_1,								// min_weapon_config_type
			WEAPON_CONFIG_TYPE_US_INFANTRY_1,								// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_M16A2_5P56MM_ROUND,			 			// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_UNKNOWN,										// target_symbol_type
			TARGET_PRIORITY_LOW,			 								// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_ROUTED_VEHICLE,				// force_info_catagory
			THREAT_TYPE_INVALID,											// threat_type
			VIEW_CATEGORY_INFANTRY,										// view_category
			VIEW_TYPE_INFANTRY,											// view_type
			MAP_ICON_NONE,													// map icon
			FALSE,															// carries_smoke_grenades

			2.5,																// chase_view_min_distance
			10.0,	  		 													// chase_view_max_distance
			0.5,																// chase_view_min_distance_test
			100.0,	  														// chase_view_max_distance_test
			0.8,   										  	         	// cruise_velocity
			0.0,						 										// axle_length
			0.0,																// max_acceleration
			rad (0.0),														// max_turn_rate (rad / second)
			1.0 * G, 														// g_max
			0.0,																// power_output
			500.0,															// recon_radius
			0.0,																// target_scan_delay
			0.0,																// air_scan_floor
			0.0,																// air_scan_ceiling
			0.0,																// air_scan_range
			0.0,																// surface_scan_range
			0.0,																// potential_surface_to_air_threat
			0.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			0.0,																// armour_front
			0.0,																// armour_side
			0.0,																// armour_rear

			20,																// initial_damage_level
			WARHEAD_EFFECTIVE_LIGHT_VEHICLE,							// armor_level

			EXPLOSIVE_QUALITY_NONE,										// explosive_quality
			EXPLOSIVE_POWER_LOW,											// explosive_power
			FALSE,															// offensive_capability
			0,																	// points value

			SOUND_SAMPLE_INDEX_NONE,									// idle_sound_effect
			SOUND_SAMPLE_INDEX_NONE,									// moving_sound_effect
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_US_INFANTRY_SAM_STANDING
		//
		////////////////////////////////////////
		{
			"FIM-92A Stinger MANPAD",											// full_name
			"INFANTRY", 	  	  											// long_display_name
			"INFANTRY",  	 	  											// short_display_name
			"INFANTRY", 													// easy_display_name

			OBJECT_3D_US_MARINE_STANDING,								// default_3d_shape
			ENTITY_FORCE_GROUND,                            	// force
			WEAPON_CONFIG_TYPE_US_INFANTRY_SAM_STANDING_1,		// default_weapon_config_type
			WEAPON_CONFIG_TYPE_US_INFANTRY_SAM_STANDING_1,		// min_weapon_config_type
			WEAPON_CONFIG_TYPE_US_INFANTRY_SAM_STANDING_1,		// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_FIM92A_STINGER,		 			// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_AIR_DEFENCE_UNIT,							// target_symbol_type
			TARGET_PRIORITY_HIGH,		 								// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_ROUTED_VEHICLE,				// force_info_catagory
			THREAT_TYPE_INVALID,											// threat_type
			VIEW_CATEGORY_INFANTRY,										// view_category
			VIEW_TYPE_INFANTRY_WITH_SAM,								// view_type
			MAP_ICON_NONE,													// map icon
			FALSE,															// carries_smoke_grenades

			2.5,																// chase_view_min_distance
			10.0,	  		 													// chase_view_max_distance
			0.5,																// chase_view_min_distance_test
			100.0,	  														// chase_view_max_distance_test
			knots_to_metres_per_second (5.0),     	         	// cruise_velocity
			0.0,						 										// axle_length
			0.0,																// max_acceleration
			rad (0.0),														// max_turn_rate (rad / second)
			1.0 * G, 														// g_max
			0.0,																// power_output
			1000.0,															// recon_radius
			15.0,																// target_scan_delay
			5.0,																// air_scan_floor
			3000.0,															// air_scan_ceiling
			5000.0,															// air_scan_range
			0.0,																// surface_scan_range
			1.0,																// potential_surface_to_air_threat
			0.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			0.0,																// armour_front
			0.0,																// armour_side
			0.0,																// armour_rear

			20,																// initial_damage_level
			WARHEAD_EFFECTIVE_LIGHT_VEHICLE,							// armor_level

			EXPLOSIVE_QUALITY_FLAMMABLE,								// explosive_quality
			EXPLOSIVE_POWER_LOW,											// explosive_power
			TRUE,																// offensive_capability
			150,																// points value

			SOUND_SAMPLE_INDEX_NONE,									// idle_sound_effect
			SOUND_SAMPLE_INDEX_NONE,									// moving_sound_effect
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_US_INFANTRY_SAM_KNEELING
		//
		////////////////////////////////////////
		{
			"FIM-92A Stinger MANPAD",											// full_name
			"INFANTRY", 	  	  											// long_display_name
			"INFANTRY",  	 	  											// short_display_name
			"INFANTRY",														// easy_display_name

			OBJECT_3D_US_MARINE_KNEELING,								// default_3d_shape
			ENTITY_FORCE_GROUND,                            	// force
			WEAPON_CONFIG_TYPE_US_INFANTRY_SAM_KNEELING_1,		// default_weapon_config_type
			WEAPON_CONFIG_TYPE_US_INFANTRY_SAM_KNEELING_1,		// min_weapon_config_type
			WEAPON_CONFIG_TYPE_US_INFANTRY_SAM_KNEELING_1,		// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_FIM92A_STINGER,	  				// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_AIR_DEFENCE_UNIT,							// target_symbol_type
			TARGET_PRIORITY_HIGH,		 								// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_ROUTED_VEHICLE,				// force_info_catagory
			THREAT_TYPE_INVALID,											// threat_type
			VIEW_CATEGORY_INFANTRY,										// view_category
			VIEW_TYPE_INFANTRY_WITH_SAM,								// view_type
			MAP_ICON_NONE,													// map icon
			FALSE,															// carries_smoke_grenades

			2.5,																// chase_view_min_distance
			10.0,	  		 													// chase_view_max_distance
			0.5,																// chase_view_min_distance_test
			100.0,	  														// chase_view_max_distance_test
			knots_to_metres_per_second (0.0),       	       	// cruise_velocity
			0.0,						 										// axle_length
			0.0,																// max_acceleration
			rad (0.0),														// max_turn_rate (rad / second)
			1.0 * G, 														// g_max
			0.0,																// power_output
			1000.0,															// recon_radius
			15.0,																// target_scan_delay
			5.0,																// air_scan_floor
			3000.0,															// air_scan_ceiling
			5000.0,															// air_scan_range
			0.0,																// surface_scan_range
			1.0,																// potential_surface_to_air_threat
			0.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			0.0,																// armour_front
			0.0,																// armour_side
			0.0,																// armour_rear

			20,																// initial_damage_level
			WARHEAD_EFFECTIVE_LIGHT_VEHICLE,							// armor_level

			EXPLOSIVE_QUALITY_FLAMMABLE,								// explosive_quality
			EXPLOSIVE_POWER_LOW,											// explosive_power
			TRUE,																// offensive_capability
			150,																// points value

			SOUND_SAMPLE_INDEX_NONE,									// idle_sound_effect
			SOUND_SAMPLE_INDEX_NONE,									// moving_sound_effect
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_CIS_INFANTRY
		//
		////////////////////////////////////////
		{
			"Infantry",     		                            	// full_name
			"INFANTRY", 	  	  											// long_display_name
			"INFANTRY",  	 	  											// short_display_name
			"INFANTRY", 													// easy_display_name

			OBJECT_3D_CIS_MARINE_WALK,									// default_3d_shape
			ENTITY_FORCE_GROUND,                            	// force
			WEAPON_CONFIG_TYPE_CIS_INFANTRY_1,								// default_weapon_config_type
			WEAPON_CONFIG_TYPE_CIS_INFANTRY_1,								// min_weapon_config_type
			WEAPON_CONFIG_TYPE_CIS_INFANTRY_1,								// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_AK_47_7P62MM_ROUND,			 			// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_UNKNOWN,										// target_symbol_type
			TARGET_PRIORITY_LOW,			 								// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_ROUTED_VEHICLE,				// force_info_catagory
			THREAT_TYPE_INVALID,											// threat_type
			VIEW_CATEGORY_INFANTRY,										// view_category
			VIEW_TYPE_INFANTRY,											// view_type
			MAP_ICON_NONE,													// map icon
			FALSE,															// carries_smoke_grenades

			2.5,																// chase_view_min_distance
			10.0,	  		 													// chase_view_max_distance
			0.5,																// chase_view_min_distance_test
			100.0,	  														// chase_view_max_distance_test
			0.8,   										  	         	// cruise_velocity
			0.0,						 										// axle_length
			0.0,																// max_acceleration
			rad (0.0),														// max_turn_rate (rad / second)
			1.0 * G, 														// g_max
			0.0,																// power_output
			500.0,															// recon_radius
			0.0,																// target_scan_delay
			0.0,																// air_scan_floor
			0.0,																// air_scan_ceiling
			0.0,																// air_scan_range
			0.0,																// surface_scan_range
			0.0,																// potential_surface_to_air_threat
			0.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			0.0,																// armour_front
			0.0,																// armour_side
			0.0,																// armour_rear

			20,																// initial_damage_level
			WARHEAD_EFFECTIVE_LIGHT_VEHICLE,							// armor_level

			EXPLOSIVE_QUALITY_NONE,										// explosive_quality
			EXPLOSIVE_POWER_LOW,											// explosive_power
			FALSE,															// offensive_capability
			0,																	// points value

			SOUND_SAMPLE_INDEX_NONE,									// idle_sound_effect
			SOUND_SAMPLE_INDEX_NONE,									// moving_sound_effect
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_CIS_INFANTRY_SAM_STANDING
		//
		////////////////////////////////////////
		{
			"SA-7B MANPAD",										// full_name
			"INFANTRY", 	  	  											// long_display_name
			"INFANTRY",  	 	  											// short_display_name
			"INFANTRY",														// easy_display_name

			OBJECT_3D_RUSSIAN_MARINE_STANDING,						// default_3d_shape
			ENTITY_FORCE_GROUND,                            	// force
			WEAPON_CONFIG_TYPE_CIS_INFANTRY_SAM_STANDING_1,		// default_weapon_config_type
			WEAPON_CONFIG_TYPE_CIS_INFANTRY_SAM_STANDING_1,		// min_weapon_config_type
			WEAPON_CONFIG_TYPE_CIS_INFANTRY_SAM_STANDING_1,		// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_9K34_STRELA_3,			 			// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_AIR_DEFENCE_UNIT,							// target_symbol_type
			TARGET_PRIORITY_HIGH,		 								// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_ROUTED_VEHICLE,				// force_info_catagory
			THREAT_TYPE_INVALID,											// threat_type
			VIEW_CATEGORY_INFANTRY,										// view_category
			VIEW_TYPE_INFANTRY_WITH_SAM,								// view_type
			MAP_ICON_NONE,													// map icon
			FALSE,															// carries_smoke_grenades

			2.5,																// chase_view_min_distance
			10.0,	  		 													// chase_view_max_distance
			0.5,																// chase_view_min_distance_test
			100.0,	  														// chase_view_max_distance_test
			knots_to_metres_per_second (5.0),   	           	// cruise_velocity
			0.0,						 										// axle_length
			0.0,																// max_acceleration
			rad (0.0),														// max_turn_rate (rad / second)
			1.0 * G, 														// g_max
			0.0,																// power_output
			1000.0,															// recon_radius
			15.0,																// target_scan_delay
			5.0,																// air_scan_floor
			1500.0,															// air_scan_ceiling
			3000.0,															// air_scan_range
			0.0,																// surface_scan_range
			1.0,																// potential_surface_to_air_threat
			0.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			0.0,																// armour_front
			0.0,																// armour_side
			0.0,																// armour_rear

			20,																// initial_damage_level
			WARHEAD_EFFECTIVE_LIGHT_VEHICLE,							// armor_level

			EXPLOSIVE_QUALITY_FLAMMABLE,								// explosive_quality
			EXPLOSIVE_POWER_LOW,											// explosive_power
			TRUE,																// offensive_capability
			150,																// points value

			SOUND_SAMPLE_INDEX_NONE,									// idle_sound_effect
			SOUND_SAMPLE_INDEX_NONE,									// moving_sound_effect
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_CIS_INFANTRY_SAM_KNEELING
		//
		////////////////////////////////////////
		{
			"SA-7B MANPAD",										// full_name
			"INFANTRY", 	  	  											// long_display_name
			"INFANTRY",  	 	  											// short_display_name
			"INFANTRY",														// easy_display_name

			OBJECT_3D_RUSSIAN_MARINE_KNEELING,						// default_3d_shape
			ENTITY_FORCE_GROUND,                            	// force
			WEAPON_CONFIG_TYPE_CIS_INFANTRY_SAM_KNEELING_1,		// default_weapon_config_type
			WEAPON_CONFIG_TYPE_CIS_INFANTRY_SAM_KNEELING_1,		// min_weapon_config_type
			WEAPON_CONFIG_TYPE_CIS_INFANTRY_SAM_KNEELING_1,		// max_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_9K34_STRELA_3,						// default_weapon_type
			TARGET_TYPE_GROUND,											// target_type
			TARGET_SYMBOL_AIR_DEFENCE_UNIT,							// target_symbol_type
			TARGET_PRIORITY_HIGH,		 								// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_ROUTED_VEHICLE,				// force_info_catagory
			THREAT_TYPE_INVALID,											// threat_type
			VIEW_CATEGORY_INFANTRY,										// view_category
			VIEW_TYPE_INFANTRY_WITH_SAM,								// view_type
			MAP_ICON_NONE,													// map icon
			FALSE,															// carries_smoke_grenades

			2.5,																// chase_view_min_distance
			10.0,	  		 													// chase_view_max_distance
			0.5,																// chase_view_min_distance_test
			100.0,	  														// chase_view_max_distance_test
			knots_to_metres_per_second (0.0),     	         	// cruise_velocity
			0.0,						 										// axle_length
			0.0,																// max_acceleration
			rad (0.0),														// max_turn_rate (rad / second)
			1.0 * G, 														// g_max
			0.0,																// power_output
			1000.0,															// recon_radius
			15.0,																// target_scan_delay
			5.0,																// air_scan_floor
			1500.0,															// air_scan_ceiling
			3000.0,															// air_scan_range
			0.0,																// surface_scan_range
			1.0,																// potential_surface_to_air_threat
			0.0,																// potential_surface_to_surface_threat
			10.0,																// Ammo_economy
			10.0,																// Fuel_economy
			0.0,																// armour_front
			0.0,																// armour_side
			0.0,																// armour_rear

			20,																// initial_damage_level
			WARHEAD_EFFECTIVE_LIGHT_VEHICLE,							// armor_level

			EXPLOSIVE_QUALITY_FLAMMABLE,								// explosive_quality
			EXPLOSIVE_POWER_LOW,											// explosive_power
			TRUE,																// offensive_capability
			150,																// points value

			SOUND_SAMPLE_INDEX_NONE,									// idle_sound_effect
			SOUND_SAMPLE_INDEX_NONE,									// moving_sound_effect
		},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
