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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Xhit: Introduced main_rotor_radius and number_of_main_rotors. (030328)
//		 IMPORTANT: number_of_main_rotors is 2 only if the helicopter got 2 main rotors
//		 on different axis (like the CHINOOK).
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ WUT mod bug, date: 26-mar-03
//remove "const" from definition
aircraft_data
   aircraft_database[NUM_ENTITY_SUB_TYPE_AIRCRAFT] =
   {
      ////////////////////////////////////////
      //
      // ENTITY_SUB_TYPE_AIRCRAFT_AH64D_APACHE_LONGBOW
      //
      ////////////////////////////////////////
      {
         "AH-64D Apache Longbow",											// full_name
         "AH-64D APACHE LONGBOW",											// long_display_name
         "AH-64D",																// short_display_name
			"HELICOPTER",															// easy_display_name

         OBJECT_3D_AH64D_APACHE_LONGBOW,									// default_3d_shape
			GUNSHIP_TYPE_APACHE,													// gunship_type
			ENTITY_FORCE_AIR,														// force
			WEAPON_CONFIG_TYPE_AH64D_APACHE_LONGBOW_47,					// default_weapon_config_type
			WEAPON_CONFIG_TYPE_AH64D_APACHE_LONGBOW_1,					// min_weapon_config_type
			WEAPON_CONFIG_TYPE_AH64D_APACHE_LONGBOW_50,					// max_weapon_config_type
			WEAPON_CONFIG_TYPE_AH64D_APACHE_LONGBOW_42,					// air_to_air_weapon_config_type
			WEAPON_CONFIG_TYPE_AH64D_APACHE_LONGBOW_47,					// air_to_surface_weapon_config_type
			WEAPON_CONFIG_TYPE_AH64D_APACHE_LONGBOW_47,					// scout_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_M230_30MM_ROUND,						// default_weapon_type
			TARGET_SYMBOL_HELICOPTER,											// target_symbol_type
			TARGET_PRIORITY_MEDIUM,												// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_HELICOPTER,							// force_info_catagory
			THREAT_TYPE_AIRBORNE_RADAR,										// threat_type
			VIEW_CATEGORY_COMBAT_HELICOPTERS,								// view_category
			VIEW_TYPE_AH64D_APACHE_LONGBOW,									// view_type
			MAP_ICON_HELICOPTER,													// map icon

         3.8313,																	// centre_of_gravity_to_ground_distance
         2.96,																		// centre_of_gravity_to_ground_distance_destroyed
         15.0,																		// chase_view_min_distance
         100.0,	  																// chase_view_max_distance
			0.5,																		// chase_view_min_distance_test
         2.0 * KILOMETRE,														// chase_view_max_distance_test
         knots_to_metres_per_second (110.0),								// cruise_velocity
         15.0,																		// cruise_altitude
         7.5,																		// attack_altitude
			rad (-21.3),															// destroyed_bank_offset
			rad (2.0),																// destroyed_pitch_offset
			rad (3.364),															// fuselage_angle
			0.0,																		// liftoff_velocity
			rad (3.5),																// main_rotor_shaft_angle
			-1.0,																		// main_rotor_direction
			rad (-4.0),																// main_rotor_blade_droop_angle
			0.0,																		// propellor_direction
			rad (90),																// max_turn_rate (deg / sec)
			rad (180.0),															// max_roll
			1.0,																		// max_vertical_turn_allowance
			15.0,																		// avoidance_radius
			6.0 * G,																	// g_max
			14.0,																		// power_output
			-1.0,																		// tail_rotor_direction
			5000.0,																	// recon_radius
			10.0,																		// target_scan_delay
			3000.0,																	// air_scan_range
			4000.0,																	// surface_scan_range
			1.0,																		// potential_air_to_air_threat
			1.0,																		// potential_air_to_surface_threat
			10.0,																		// Ammo_economy
			1136.0,																	// Fuel_default_weight
			10.0,																		// Fuel_economy
			1.0,																	// number_of_main_rotors
			7.315,																	// main_rotor_radius

			600,																		// initial_damage_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,										// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,												// explosive_power
			TRUE,																		// offensive_capability
			TRUE,																		// player_controllable
			200,																		// points value

			SOUND_SAMPLE_INDEX_EXTERIOR_APACHE_ROTOR,						// continuous_sound_effect_index
			SOUND_SAMPLE_INDEX_EXTERIOR_APACHE_ROTOR_WIND_UP,			// wind_up_sound_effect_index
			SOUND_SAMPLE_INDEX_EXTERIOR_APACHE_ROTOR_WIND_DOWN,		// wind_down_sound_effect_index
      },
      ////////////////////////////////////////
      //
      // ENTITY_SUB_TYPE_AIRCRAFT_MI28N_HAVOC_B
      //
      ////////////////////////////////////////
      {
         "Mi-28N Havoc B",														// full_name
         "Mi-28N HAVOC B",														// long_display_name
         "Mi-28N",																// short_display_name
			"HELICOPTER",															// easy_display_name

         OBJECT_3D_MI28N_HAVOC,												// default_3d_shape
			GUNSHIP_TYPE_HAVOC,													// gunship_type
			ENTITY_FORCE_AIR,														// force
			WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_8,								// default_weapon_config_type
			WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_1,								// min_weapon_config_type
			WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_30,							// max_weapon_config_type
			WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_12,							// air_to_air_weapon_config_type
			WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_8,								// air_to_surface_weapon_config_type
			WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_8,								// scout_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND,					// default_weapon_type
			TARGET_SYMBOL_HELICOPTER,											// target_symbol_type
			TARGET_PRIORITY_MEDIUM,												// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_HELICOPTER,							// force_info_catagory
			THREAT_TYPE_AIRBORNE_RADAR,										// threat_type
			VIEW_CATEGORY_COMBAT_HELICOPTERS,								// view_category
			VIEW_TYPE_MI28N_HAVOC_B,											// view_type
			MAP_ICON_HELICOPTER,													// map icon

         3.70,																		// centre_of_gravity_to_ground_distance
         2.71,																		// centre_of_gravity_to_ground_distance_destroyed
         15.0,																		// chase_view_min_distance
         100.0,	  																// chase_view_max_distance
			0.5,																		// chase_view_min_distance_test
         2.0 * KILOMETRE,														// chase_view_max_distance_test
         knots_to_metres_per_second (110.0),								// cruise_velocity
         15.0,																		// cruise_altitude
         7.5,																		// attack_altitude
			rad (24.0),																// destroyed_bank_offset
			rad (2.4),																// destroyed_pitch_offset
			rad (6.6),																// fuselage_angle
			0.0,																		// liftoff_velocity
			rad (6.5),																// main_rotor_shaft_angle
			1.0,																		// main_rotor_direction
			rad (-4.0),																// main_rotor_blade_droop_angle
			0.0,																		// propellor_direction
			rad (90),																// max_turn_rate (deg / sec)
			rad (180.0),															// max_roll
			1.0,																		// max_vertical_turn_allowance
			15.0,																		// avoidance_radius
			6.0 * G,																	// g_max
			15.1,																		// power_output
			-1.0,																		// tail_rotor_direction
			5000.0,																	// recon_radius
			10.0,																		// target_scan_delay
			3000.0, 																	// air_scan_range
			4000.0, 																	// surface_scan_range
			1.0,																		// potential_air_to_air_threat
			1.0,																		// potential_air_to_surface_threat
			10.0,																		// Ammo_economy
			1136.0,																	// Fuel_default_weight
			10.0,																		// Fuel_economy
			1.0,																	// number_of_main_rotors
			8.6,																	// main_rotor_radius

			600,																		// initial_damage_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,										// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,												// explosive_power
			TRUE,																		// offensive_capability
			TRUE,																		// player_controllable
			200,																		// points value

			SOUND_SAMPLE_INDEX_EXTERIOR_HAVOC_ROTOR,						// continuous_sound_effect_index
			SOUND_SAMPLE_INDEX_EXTERIOR_HAVOC_ROTOR_WIND_UP,			// wind_up_sound_effect_index
			SOUND_SAMPLE_INDEX_EXTERIOR_HAVOC_ROTOR_WIND_DOWN,			// wind_down_sound_effect_index
      },
      ////////////////////////////////////////
      //
      // ENTITY_SUB_TYPE_AIRCRAFT_RAH66_COMANCHE
      //
      ////////////////////////////////////////
      {
         "RAH-66 Comanche",													// full_name
         "RAH-66 COMANCHE",	  												// long_display_name
         "RAH-66",																// short_display_name
			"HELICOPTER",															// easy_display_name

         OBJECT_3D_RAH66,														// default_3d_shape
			GUNSHIP_TYPE_COMANCHE,												// gunship_type
			ENTITY_FORCE_AIR,														// force
			WEAPON_CONFIG_TYPE_RAH66_COMANCHE_150,							// default_weapon_config_type
			WEAPON_CONFIG_TYPE_RAH66_COMANCHE_1,							// min_weapon_config_type
			WEAPON_CONFIG_TYPE_RAH66_COMANCHE_384,							// max_weapon_config_type
			WEAPON_CONFIG_TYPE_RAH66_COMANCHE_86,							// air_to_air_weapon_config_type
			WEAPON_CONFIG_TYPE_RAH66_COMANCHE_155,							// air_to_surface_weapon_config_type
			WEAPON_CONFIG_TYPE_RAH66_COMANCHE_27,							// scout_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_M197_20MM_ROUND,						// default_weapon_type
			TARGET_SYMBOL_HELICOPTER,											// target_symbol_type
			TARGET_PRIORITY_MEDIUM,												// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_HELICOPTER,							// force_info_catagory
			THREAT_TYPE_AIRBORNE_RADAR,										// threat_type
			VIEW_CATEGORY_COMBAT_HELICOPTERS,								// view_category
			VIEW_TYPE_RAH66_COMANCHE,											// view_type
			MAP_ICON_HELICOPTER,													// map icon

         3.0,																		// centre_of_gravity_to_ground_distance
         3.0,																		// centre_of_gravity_to_ground_distance_destroyed
         15.0,																		// chase_view_min_distance
         100.0,	  																// chase_view_max_distance
			0.5,																		// chase_view_min_distance_test
         2.0 * KILOMETRE,														// chase_view_max_distance_test
         knots_to_metres_per_second (100.0),								// cruise_velocity
         15.0,																		// cruise_altitude
         7.5,																		// attack_altitude
			0.0,																		// destroyed_bank_offset
			rad (-1.0),																// destroyed_pitch_offset
			rad (2.4),																// fuselage_angle
			0.0,																		// liftoff_velocity
			rad (3.5),																// main_rotor_shaft_angle
			-1.0,																		// main_rotor_direction
			rad (0.0),																// main_rotor_blade_droop_angle
			0.0,																		// propellor_direction
			rad (100),																// max_turn_rate (deg / sec)
			rad (180.0),															// max_roll
			1.0,																		// max_vertical_turn_allowance
			15.0,																		// avoidance_radius
			6.0 * G,																	// g_max
			14.3,																		// power_output
			-1.0,																		// tail_rotor_direction
			5000.0,																	// recon_radius
			10.0,																		// target_scan_delay
			3000.0,																	// air_scan_range
			4000.0,																	// surface_scan_range
			1.0,																		// potential_air_to_air_threat
			1.0,																		// potential_air_to_surface_threat
			10.0,																		// Ammo_economy
			1136.0,																	// Fuel_default_weight
			10.0,																		// Fuel_economy
			1.0,																	// number_of_main_rotors
			5.95,																	// main_rotor_radius

			500,																		// initial_damage_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,										// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,												// explosive_power
			TRUE,																		// offensive_capability
			TRUE,																		// player_controllable
			200,																		// points value

			SOUND_SAMPLE_INDEX_EXTERIOR_APACHE_ROTOR,						// continuous_sound_effect_index
			SOUND_SAMPLE_INDEX_EXTERIOR_APACHE_ROTOR_WIND_UP,			// wind_up_sound_effect_index
			SOUND_SAMPLE_INDEX_EXTERIOR_APACHE_ROTOR_WIND_DOWN,		// wind_down_sound_effect_index
      },
      ////////////////////////////////////////
      //
      // ENTITY_SUB_TYPE_AIRCRAFT_KA52_HOKUM_B
      //
      ////////////////////////////////////////
      {
         "Ka-52 Alligator",														// full_name
         "Ka-52 ALLIGATOR",														// long_display_name
         "Ka-52",	  																// short_display_name
			"HELICOPTER",															// easy_display_name

			OBJECT_3D_KA_52,														// default_3d_shape
			GUNSHIP_TYPE_HOKUM,													// gunship_type
			ENTITY_FORCE_AIR,														// force
			WEAPON_CONFIG_TYPE_KA52_HOKUM_B_7,								// default_weapon_config_type
			WEAPON_CONFIG_TYPE_KA52_HOKUM_B_1,								// min_weapon_config_type
			WEAPON_CONFIG_TYPE_KA52_HOKUM_B_30,								// max_weapon_config_type
			WEAPON_CONFIG_TYPE_KA52_HOKUM_B_12,								// air_to_air_weapon_config_type
			WEAPON_CONFIG_TYPE_KA52_HOKUM_B_7,								// air_to_surface_weapon_config_type
			WEAPON_CONFIG_TYPE_KA52_HOKUM_B_7,								// scout_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND,					// default_weapon_type
			TARGET_SYMBOL_HELICOPTER,											// target_symbol_type
			TARGET_PRIORITY_MEDIUM,												// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_HELICOPTER,							// force_info_catagory
			THREAT_TYPE_AIRBORNE_RADAR,										// threat_type
			VIEW_CATEGORY_COMBAT_HELICOPTERS,								// view_category
			VIEW_TYPE_KA52_HOKUM_B,												// view_type
			MAP_ICON_HELICOPTER,													// map icon

         4.065,																	// centre_of_gravity_to_ground_distance
         3.25,																		// centre_of_gravity_to_ground_distance_destroyed
         15.0,																		// chase_view_min_distance
         100.0,	  																// chase_view_max_distance
			0.5,																		// chase_view_min_distance_test
         2.0 * KILOMETRE,														// chase_view_max_distance_test
         knots_to_metres_per_second (90.0),								// cruise_velocity
         15.0,																		// cruise_altitude
         7.5,																		// attack_altitude
			rad (16.0),																// destroyed_bank_offset
			0.0,																		// destroyed_pitch_offset
			rad (0.0),																// fuselage_angle
			0.0,																		// liftoff_velocity
			rad (3.5),																// main_rotor_shaft_angle
			-1.0,																		// main_rotor_direction
			rad (-4.0),																// main_rotor_blade_droop_angle
			0.0,																		// propellor_direction
			rad (160),																// max_turn_rate (deg / sec)
			rad (180.0),															// max_roll
			1.0,																		// max_vertical_turn_allowance
			15.0,																		// avoidance_radius
			6.0 * G,																	// g_max
			14.0,																		// power_output
			0.0,																		// tail_rotor_direction
			5000.0,																	// recon_radius
			10.0,																		// target_scan_delay
			3000.0,																	// air_scan_range
			4000.0,																	// surface_scan_range
			1.0,																		// potential_air_to_air_threat
			1.0,																		// potential_air_to_surface_threat
			10.0,																		// Ammo_economy
			1136.0,																	// Fuel_default_weight
			10.0,																		// Fuel_economy
			1.0,																	// number_of_main_rotors
			7.25,																	// main_rotor_radius

			650,																		// initial_damage_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,										// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,												// explosive_power
			TRUE,																		// offensive_capability
			TRUE,																		// player_controllable
			200,																		// points value

			SOUND_SAMPLE_INDEX_EXTERIOR_HAVOC_ROTOR,						// continuous_sound_effect_index
			SOUND_SAMPLE_INDEX_EXTERIOR_HAVOC_ROTOR_WIND_UP,			// wind_up_sound_effect_index
			SOUND_SAMPLE_INDEX_EXTERIOR_HAVOC_ROTOR_WIND_DOWN,			// wind_down_sound_effect_index
      },
      ////////////////////////////////////////
      //
      // ENTITY_SUB_TYPE_AIRCRAFT_UH60_BLACK_HAWK
      //
      ////////////////////////////////////////
      ////Moje 030524 1st line under "OBJECT_3D_UH60_BLACKHAWK" changed from "NUM_GUNSHIP_TYPES"
      ////Moje 040209 CHanged loadout schemes
      {
         "UH-60L Blackhawk",									// full_name
         "UH-60 BLACKHAWK",	 								// long_display_name
         "UH-60",	  									// short_display_name
			"HELICOPTER",								// easy_display_name

         OBJECT_3D_UH60_BLACKHAWK,							// default_3d_shape
			GUNSHIP_TYPE_BLACKHAWK,							// gunship_type
			ENTITY_FORCE_AIR,							// force
			WEAPON_CONFIG_TYPE_UH60_BLACK_HAWK_6,					// default_weapon_config_type
			WEAPON_CONFIG_TYPE_UH60_BLACK_HAWK_1,					// min_weapon_config_type
			WEAPON_CONFIG_TYPE_UH60_BLACK_HAWK_9,					// max_weapon_config_type
			WEAPON_CONFIG_TYPE_UH60_BLACK_HAWK_9,					// air_to_air_weapon_config_type
			WEAPON_CONFIG_TYPE_UH60_BLACK_HAWK_6,					// air_to_surface_weapon_config_type
			WEAPON_CONFIG_TYPE_UH60_BLACK_HAWK_5,					// scout_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_AGM114L_LONGBOW_HELLFIRE,			// default_weapon_type
			TARGET_SYMBOL_HELICOPTER,						// target_symbol_type
			TARGET_PRIORITY_MEDIUM,							// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_HELICOPTER,					// force_info_catagory
			THREAT_TYPE_AIRBORNE_RADAR,						// threat_type
			VIEW_CATEGORY_COMBAT_HELICOPTERS,					// view_category
			VIEW_TYPE_UH60_BLACK_HAWK,						// view_type
			MAP_ICON_HELICOPTER,							// map icon

         3.5154,										// centre_of_gravity_to_ground_distance
         3.35,											// centre_of_gravity_to_ground_distance_destroyed
         15.0,											// chase_view_min_distance
         100.0,	  										// chase_view_max_distance
			0.5,									// chase_view_min_distance_test
         2.0 * KILOMETRE,									// chase_view_max_distance_test
         knots_to_metres_per_second (85.0),							// cruise_velocity
         24.0,											// cruise_altitude
         12.0,											// attack_altitude
			0.0,									// destroyed_bank_offset
			rad (6.9),								// destroyed_pitch_offset
			rad (1.7),								// fuselage_angle
			0.0,									// liftoff_velocity
			rad (2.5),								// main_rotor_shaft_angle
			-1.0,									// main_rotor_direction
			rad (-4.0),								// main_rotor_blade_droop_angle
			0.0,									// propellor_direction
			rad (80),								// max_turn_rate (deg / sec)
			rad (180.0),								// max_roll
			1.0,									// max_vertical_turn_allowance
			15.0,									// avoidance_radius
			6.0 * G,								// g_max
			12.6,									// power_output
			-1.0,									// tail_rotor_direction
			5000.0,									// recon_radius
			10.0,									// target_scan_delay
			0.0,									// air_scan_range
			4000.0,		 							// surface_scan_range
			0.8,									// potential_air_to_air_threat
			1.0,									// potential_air_to_surface_threat
			10.0,									// Ammo_economy
			1136.0,									// Fuel_default_weight
			10.0,									// Fuel_economy
			1.0,									// number_of_main_rotors
			8.18,									// main_rotor_radius

			650,								// initial_damage_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,					// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,						// explosive_power
			TRUE,								// offensive_capability
			TRUE,								// player_controllable JB 030408 Fly any aircraft
			150,								// points value

			SOUND_SAMPLE_INDEX_MEDIUM_HELICOPTER_ROTOR,			// continuous_sound_effect_index
			SOUND_SAMPLE_INDEX_MEDIUM_HELICOPTER_ROTOR_WIND_UP,		// wind_up_sound_effect_index
			SOUND_SAMPLE_INDEX_MEDIUM_HELICOPTER_ROTOR_WIND_DOWN,		// wind_down_sound_effect_index
      },
      ////////////////////////////////////////
      //
      // ENTITY_SUB_TYPE_AIRCRAFT_MI24D_HIND
      //
      ////////////////////////////////////////
      ////Moje 030524 1st line under "OBJECT_3D_MI24_HIND" changed from "NUM_GUNSHIP_TYPES"
      ////Moje 040209 CHanged loadout schemes
      {
         "Mi-24V Hind",															// full_name
         "Mi-24V HIND",		 													// long_display_name
         "Mi-24V",																// short_display_name
			"HELICOPTER",															// easy_display_name

         OBJECT_3D_MI24_HIND,													// default_3d_shape
			GUNSHIP_TYPE_HIND,													// gunship_type
			ENTITY_FORCE_AIR,														// force
			WEAPON_CONFIG_TYPE_MI24D_HIND_47,									// default_weapon_config_type
			WEAPON_CONFIG_TYPE_MI24D_HIND_1,									// min_weapon_config_type
			WEAPON_CONFIG_TYPE_MI24D_HIND_60,									// max_weapon_config_type
			WEAPON_CONFIG_TYPE_MI24D_HIND_47,									// air_to_air_weapon_config_type
			WEAPON_CONFIG_TYPE_MI24D_HIND_47,									// air_to_surface_weapon_config_type
			WEAPON_CONFIG_TYPE_MI24D_HIND_47,									// scout_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_9A642_12P7MM_ROUND,					// default_weapon_type
			TARGET_SYMBOL_HELICOPTER,											// target_symbol_type
			TARGET_PRIORITY_MEDIUM,												// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_HELICOPTER,							// force_info_catagory
			THREAT_TYPE_INVALID,													// threat_type
			VIEW_CATEGORY_COMBAT_HELICOPTERS,								// view_category
			VIEW_TYPE_MI24V_HIND,												// view_type
			MAP_ICON_HELICOPTER,													// map icon

         3.94,		  																// centre_of_gravity_to_ground_distance
         3.25,																		// centre_of_gravity_to_ground_distance_destroyed
         15.0,																		// chase_view_min_distance
         100.0,	  																// chase_view_max_distance
			0.5,																		// chase_view_min_distance_test
         2.0 * KILOMETRE,														// chase_view_max_distance_test
         knots_to_metres_per_second (80.0),								// cruise_velocity
         24.0,																		// cruise_altitude
         12.0,																		// attack_altitude
			rad (14.4),																// destroyed_bank_offset
			rad (4.6),																// destroyed_pitch_offset
			rad (3.5),																// fuselage_angle
			0.0,																		// liftoff_velocity
			rad (4.5),																// main_rotor_shaft_angle
			1.0,																		// main_rotor_direction
			rad (-4.0),																// main_rotor_blade_droop_angle
			0.0,																		// propellor_direction
			rad (70),																// max_turn_rate (deg / sec)
			rad (180.0),															// max_roll
			1.0,																		// max_vertical_turn_allowance
			15.0,																		// avoidance_radius
			6.0 * G,																	// g_max
			13.0,																		// power_output
			-1.0,																		// tail_rotor_direction
			5000.0,																	// recon_radius
			10.0,																		// target_scan_delay
			2000.0,																	// air_scan_range
			4000.0,																	// surface_scan_range
			0.8,																		// potential_air_to_air_threat
			1.0,																		// potential_air_to_surface_threat
			10.0,																		// Ammo_economy
			1136.0,																	// Fuel_default_weight
			10.0,																		// Fuel_economy
			1.0,																	// number_of_main_rotors
			8.65,																	// main_rotor_radius

			650,																		// initial_damage_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,										// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,												// explosive_power
			TRUE,																		// offensive_capability
			TRUE,																	// player_controllable JB 030408 Fly any aircraft
			150,																		// points value

			SOUND_SAMPLE_INDEX_MEDIUM_HELICOPTER_ROTOR,					// continuous_sound_effect_index
			SOUND_SAMPLE_INDEX_MEDIUM_HELICOPTER_ROTOR_WIND_UP,		// wind_up_sound_effect_index
			SOUND_SAMPLE_INDEX_MEDIUM_HELICOPTER_ROTOR_WIND_DOWN,		// wind_down_sound_effect_index
      },
      ////////////////////////////////////////
      //
      // ENTITY_SUB_TYPE_AIRCRAFT_CH46E_SEA_KNIGHT
      //
      ////////////////////////////////////////
      {
         "CH-46E Sea Knight",													// full_name
         "CH-46E SEA KNIGHT",		 											// long_display_name
         "CH-46E",																// short_display_name
			"HELICOPTER",															// easy_display_name

         OBJECT_3D_CH_46,														// default_3d_shape
			NUM_GUNSHIP_TYPES,													// gunship_type
			ENTITY_FORCE_AIR,														// force
			WEAPON_CONFIG_TYPE_CH46E_SEA_KNIGHT_1,							// default_weapon_config_type
			WEAPON_CONFIG_TYPE_CH46E_SEA_KNIGHT_1,							// min_weapon_config_type
			WEAPON_CONFIG_TYPE_CH46E_SEA_KNIGHT_1,							// max_weapon_config_type
			WEAPON_CONFIG_TYPE_CH46E_SEA_KNIGHT_1,							// air_to_air_weapon_config_type
			WEAPON_CONFIG_TYPE_CH46E_SEA_KNIGHT_1,							// air_to_surface_weapon_config_type
			WEAPON_CONFIG_TYPE_CH46E_SEA_KNIGHT_1,							// scout_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_NO_WEAPON,	 							// default_weapon_type
			TARGET_SYMBOL_HELICOPTER,											// target_symbol_type
			TARGET_PRIORITY_MEDIUM,	  											// target_priority_type
			FORCE_INFO_CATAGORY_UNARMED_HELICOPTER,						// force_info_catagory
			THREAT_TYPE_INVALID,													// threat_type
			VIEW_CATEGORY_COMBAT_HELICOPTERS,								// view_category
			VIEW_TYPE_CH46E_SEA_KNIGHT,										// view_type
			MAP_ICON_TRANSPORT_HELICOPTER,									// map icon

         4.5958,																	// centre_of_gravity_to_ground_distance
         3.76,																		// centre_of_gravity_to_ground_distance_destroyed
         15.0,																		// chase_view_min_distance
         100.0,	  																// chase_view_max_distance
			0.5,																		// chase_view_min_distance_test
         2.0 * KILOMETRE,														// chase_view_max_distance_test
         knots_to_metres_per_second (70.0),								// cruise_velocity
         40.0,																		// cruise_altitude
         40.0,																		// attack_altitude
			0.0,																		// destroyed_bank_offset
			0.0,																		// destroyed_pitch_offset
			rad (3.0),																// fuselage_angle
			0.0,																		// liftoff_velocity
			rad (3.5),																// main_rotor_shaft_angle
			-1.0,																		// main_rotor_direction
			rad (-4.0),																// main_rotor_blade_droop_angle
			0.0,																		// propellor_direction
			rad (60),																// max_turn_rate (deg / sec)
			rad (180.0),															// max_roll
			1.0,																		// max_vertical_turn_allowance
			15.0,																		// avoidance_radius
			6.0 * G,																	// g_max
			11.0,																		// power_output
			0.0,																		// tail_rotor_direction
			3000.0,																	// recon_radius
			10.0,																		// target_scan_delay
			0.0,																		// air_scan_range
			0.0,																		// surface_scan_range
			0.0,																		// potential_air_to_air_threat
			0.0,																		// potential_air_to_surface_threat
			10.0,																		// Ammo_economy
			1136.0,																	// Fuel_default_weight
			10.0,																		// Fuel_economy
			1.0,																	// number_of_main_rotors
			9.145,																	// main_rotor_radius

			750,																		// initial_damage_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,										// explosive_quality
			EXPLOSIVE_POWER_HIGH,												// explosive_power
			FALSE,																	// offensive_capability
			TRUE,																	// player_controllable JB 030408 Fly any aircraft
			50,																		// points value

			SOUND_SAMPLE_INDEX_CH47,					            // continuous_sound_effect_index
			SOUND_SAMPLE_INDEX_MEDIUM_HELICOPTER_ROTOR_WIND_UP,		// wind_up_sound_effect_index
			SOUND_SAMPLE_INDEX_MEDIUM_HELICOPTER_ROTOR_WIND_DOWN,		// wind_down_sound_effect_index
      },
      ////////////////////////////////////////
      //
      // ENTITY_SUB_TYPE_AIRCRAFT_KA29_HELIX_B
      //
      ////////////////////////////////////////
      {
         "Ka-29 Helix B",														// full_name
         "Ka-29 HELIX B",			 											// long_display_name
         "Ka-29",																	// short_display_name
			"HELICOPTER",															// easy_display_name

			OBJECT_3D_KA29_HELIX_B,												// default_3d_shape
			NUM_GUNSHIP_TYPES,													// gunship_type
			ENTITY_FORCE_AIR,														// force
			WEAPON_CONFIG_TYPE_KA29_HELIX_B_1, 								// default_weapon_config_type
			WEAPON_CONFIG_TYPE_KA29_HELIX_B_1, 								// min_weapon_config_type
			WEAPON_CONFIG_TYPE_KA29_HELIX_B_1, 								// max_weapon_config_type
			WEAPON_CONFIG_TYPE_KA29_HELIX_B_1,								// air_to_air_weapon_config_type
			WEAPON_CONFIG_TYPE_KA29_HELIX_B_1,								// air_to_surface_weapon_config_type
			WEAPON_CONFIG_TYPE_KA29_HELIX_B_1,								// scout_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_S5,											// default_weapon_type
			TARGET_SYMBOL_HELICOPTER,											// target_symbol_type
			TARGET_PRIORITY_MEDIUM,	 											// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_HELICOPTER,							// force_info_catagory
			THREAT_TYPE_INVALID,													// threat_type
			VIEW_CATEGORY_COMBAT_HELICOPTERS,								// view_category
			VIEW_TYPE_KA29_HELIX_B,												// view_type
			MAP_ICON_HELICOPTER,													// map icon

         3.405,																	// centre_of_gravity_to_ground_distance
         3.02,																		// centre_of_gravity_to_ground_distance_destroyed
         15.0,																		// chase_view_min_distance
         100.0,	  																// chase_view_max_distance
			0.5,																		// chase_view_min_distance_test
         2.0 * KILOMETRE,														// chase_view_max_distance_test
         knots_to_metres_per_second (75.0),								// cruise_velocity
         25.0,																		// cruise_altitude
         20.0,																		// attack_altitude
			0.0,																		// destroyed_bank_offset
			0.0,																		// destroyed_pitch_offset
			rad (3.0828),															// fuselage_angle
			0.0,																		// liftoff_velocity
			rad (3.5),		  														// main_rotor_shaft_angle
			-1.0,																		// main_rotor_direction
			rad (-4.0),																// main_rotor_blade_droop_angle
			0.0,																		// propellor_direction
			rad (160),																// max_turn_rate (deg / sec)
			rad (180.0),															// max_roll
			1.0,																		// max_vertical_turn_allowance
			15.0,																		// avoidance_radius
			6.0 * G,																	// g_max
			11.0,																		// power_output
			0.0,																		// tail_rotor_direction
			5000.0,																	// recon_radius
			10.0,																		// target_scan_delay
			0.0,																		// air_scan_range
			2000.0,																	// surface_scan_range
			0.0,																		// potential_air_to_air_threat
			1.0,																		// potential_air_to_surface_threat
			10.0,																		// Ammo_economy
			1136.0,																	// Fuel_default_weight
			10.0,																		// Fuel_economy
			1.0,																	// number_of_main_rotors
			7.95,																	// main_rotor_radius

			750,																		// initial_damage_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,										// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,												// explosive_power
			TRUE,																		// offensive_capability
			TRUE,																	// player_controllable JB 030408 Fly any aircraft
			75,																		// points value

			SOUND_SAMPLE_INDEX_MEDIUM_HELICOPTER_ROTOR,					// continuous_sound_effect_index
			SOUND_SAMPLE_INDEX_MEDIUM_HELICOPTER_ROTOR_WIND_UP,		// wind_up_sound_effect_index
			SOUND_SAMPLE_INDEX_MEDIUM_HELICOPTER_ROTOR_WIND_DOWN,		// wind_down_sound_effect_index
      },
      ////////////////////////////////////////
      //
      // ENTITY_SUB_TYPE_AIRCRAFT_CH3_JOLLY_GREEN_GIANT
      //
      ////////////////////////////////////////
      {
         "CH-3 Jolly Green Giant",											// full_name
         "CH-3 JOLLY GREEN GIANT",	 										// long_display_name
         "CH-3",																	// short_display_name
			"HELICOPTER",															// easy_display_name

         OBJECT_3D_CH_3,		  												// default_3d_shape
			NUM_GUNSHIP_TYPES,													// gunship_type
			ENTITY_FORCE_AIR,														// force
			WEAPON_CONFIG_TYPE_CH3_JOLLY_GREEN_GIANT_1,					// default_weapon_config_type
			WEAPON_CONFIG_TYPE_CH3_JOLLY_GREEN_GIANT_1,					// min_weapon_config_type
			WEAPON_CONFIG_TYPE_CH3_JOLLY_GREEN_GIANT_1,					// max_weapon_config_type
			WEAPON_CONFIG_TYPE_CH3_JOLLY_GREEN_GIANT_1,					// air_to_air_weapon_config_type
			WEAPON_CONFIG_TYPE_CH3_JOLLY_GREEN_GIANT_1,					// air_to_surface_weapon_config_type
			WEAPON_CONFIG_TYPE_CH3_JOLLY_GREEN_GIANT_1,					// scout_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_NO_WEAPON,	 							// default_weapon_type
			TARGET_SYMBOL_HELICOPTER,											// target_symbol_type
			TARGET_PRIORITY_MEDIUM,												// target_priority_type
			FORCE_INFO_CATAGORY_UNARMED_HELICOPTER,						// force_info_catagory
			THREAT_TYPE_INVALID,													// threat_type
			VIEW_CATEGORY_TRANSPORT_HELICOPTERS,							// view_category
			VIEW_TYPE_CH3_JOLLY_GREEN_GIANT,									// view_type
			MAP_ICON_TRANSPORT_HELICOPTER,									// map icon

         4.54,																		// centre_of_gravity_to_ground_distance
         3.90,																		// centre_of_gravity_to_ground_distance_destroyed
         15.0,																		// chase_view_min_distance
         100.0,	  																// chase_view_max_distance
			0.5,																		// chase_view_min_distance_test
         2.0 * KILOMETRE,														// chase_view_max_distance_test
         knots_to_metres_per_second (70.0),								// cruise_velocity
         40.0,																		// cruise_altitude
         40.0,																		// attack_altitude
			rad (9.5),																// destroyed_bank_offset
			rad (-0.9),																// destroyed_pitch_offset
			rad (1.90),																// fuselage_angle
			0.0,																		// liftoff_velocity
			rad (3.0),																// main_rotor_shaft_angle
			-1.0,																		// main_rotor_direction
			rad (-4.0),																// main_rotor_blade_droop_angle
			0.0,																		// propellor_direction
			rad (40),																// max_turn_rate (deg / sec)
			rad (180.0),															// max_roll
			1.0,																		// max_vertical_turn_allowance
			15.0,																		// avoidance_radius
			6.0 * G,																	// g_max
			10.2,																		// power_output
			-1.0,																		// tail_rotor_direction
			3000.0,																	// recon_radius
			10.0,																		// target_scan_delay
			0.0,																		// air_scan_range
			0.0,																		// surface_scan_range
			0.0,																		// potential_air_to_air_threat
			0.0,																		// potential_air_to_surface_threat
			10.0,																		// Ammo_economy
			1136.0,																	// Fuel_default_weight
			10.0,																		// Fuel_economy
			1.0,																	// number_of_main_rotors
			9.5,																	// main_rotor_radius

			800,																		// initial_damage_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,										// explosive_quality
			EXPLOSIVE_POWER_HIGH,												// explosive_power
			FALSE,																	// offensive_capability
			TRUE,																	// player_controllable JB 030408 Fly any aircraft
			50,																		// points value

			SOUND_SAMPLE_INDEX_CH3,					                    // continuous_sound_effect_index
			SOUND_SAMPLE_INDEX_LARGE_HELICOPTER_ROTOR_WIND_UP,			// wind_up_sound_effect_index
			SOUND_SAMPLE_INDEX_LARGE_HELICOPTER_ROTOR_WIND_DOWN,		// wind_down_sound_effect_index
      },
      ////////////////////////////////////////
      //
      // ENTITY_SUB_TYPE_AIRCRAFT_MI17_HIP
      //
      ////////////////////////////////////////
      {
         "Mi-17 Hip",															// full_name
         "Mi-17 HIP",					 										// long_display_name
         "Mi-17",																	// short_display_name
			"HELICOPTER",															// easy_display_name

         OBJECT_3D_MI17_HIP,													// default_3d_shape
			NUM_GUNSHIP_TYPES,													// gunship_type
			ENTITY_FORCE_AIR,														// force
			WEAPON_CONFIG_TYPE_MI17_HIP_1,	  								// default_weapon_config_type
			WEAPON_CONFIG_TYPE_MI17_HIP_1,	  								// min_weapon_config_type
			WEAPON_CONFIG_TYPE_MI17_HIP_1,	  								// max_weapon_config_type
			WEAPON_CONFIG_TYPE_MI17_HIP_1,									// air_to_air_weapon_config_type
			WEAPON_CONFIG_TYPE_MI17_HIP_1,									// air_to_surface_weapon_config_type
			WEAPON_CONFIG_TYPE_MI17_HIP_1,									// scout_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_S5,											// default_weapon_type
			TARGET_SYMBOL_HELICOPTER,											// target_symbol_type
			TARGET_PRIORITY_MEDIUM,												// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_HELICOPTER,							// force_info_catagory
			THREAT_TYPE_INVALID,													// threat_type
			VIEW_CATEGORY_TRANSPORT_HELICOPTERS,							// view_category
			VIEW_TYPE_MI17_HIP,													// view_type
			MAP_ICON_TRANSPORT_HELICOPTER,									// map icon

         4.30,																		// centre_of_gravity_to_ground_distance
         4.00,																		// centre_of_gravity_to_ground_distance_destroyed
         15.0,																		// chase_view_min_distance
         100.0,	  																// chase_view_max_distance
			0.5,																		// chase_view_min_distance_test
         2.0 * KILOMETRE,														// chase_view_max_distance_test
         knots_to_metres_per_second (75.0),								// cruise_velocity
         40.0,																		// cruise_altitude
         40.0,																		// attack_altitude
			0.0,																		// destroyed_bank_offset
			rad (-7.2),																// destroyed_pitch_offset
			rad (4.5),																// fuselage_angle
			0.0,																		// liftoff_velocity
			rad (4.75),																// main_rotor_shaft_angle
			1.0,																		// main_rotor_direction
			rad (-4.0),																// main_rotor_blade_droop_angle
			0.0,																		// propellor_direction
			rad (50),																// max_turn_rate (deg / sec)
			rad (180.0),															// max_roll
			1.0,																		// max_vertical_turn_allowance
			15.0,																		// avoidance_radius
			6.0 * G,																	// g_max
			10.4,																		// power_output
			-1.0,																		// tail_rotor_direction
			5000.0,																	// recon_radius
			10.0,																		// target_scan_delay
			0.0,																		// air_scan_range
			0.0,																		// surface_scan_range
			0.0,																		// potential_air_to_air_threat
			1.0,																		// potential_air_to_surface_threat
			10.0,																		// Ammo_economy
			1136.0,																	// Fuel_default_weight
			10.0,																		// Fuel_economy
			1.0,																	// number_of_main_rotors
			10.645,																	// main_rotor_radius

			800,																		// initial_damage_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,										// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,												// explosive_power
			TRUE,																		// offensive_capability
			TRUE,																	// player_controllable JB 030408 Fly any aircraft
			50,																		// points value

			SOUND_SAMPLE_INDEX_MI16,					// continuous_sound_effect_index
			SOUND_SAMPLE_INDEX_LARGE_HELICOPTER_ROTOR_WIND_UP,			// wind_up_sound_effect_index
			SOUND_SAMPLE_INDEX_LARGE_HELICOPTER_ROTOR_WIND_DOWN,		// wind_down_sound_effect_index
      },
      ////////////////////////////////////////
      //
      // ENTITY_SUB_TYPE_AIRCRAFT_CH47D_CHINOOK
      //
      ////////////////////////////////////////
      {
         "CH-47D Chinook",														// full_name
         "CH-47D CHINOOK",		 		 										// long_display_name
         "CH-47D",	  															// short_display_name
			"HELICOPTER",															// easy_display_name

         OBJECT_3D_CH47D_CHINOOK,											// default_3d_shape
			NUM_GUNSHIP_TYPES,													// gunship_type
			ENTITY_FORCE_AIR,														// force
			WEAPON_CONFIG_TYPE_CH47D_CHINOOK_1,								// default_weapon_config_type
			WEAPON_CONFIG_TYPE_CH47D_CHINOOK_1,								// min_weapon_config_type
			WEAPON_CONFIG_TYPE_CH47D_CHINOOK_1,								// max_weapon_config_type
			WEAPON_CONFIG_TYPE_CH47D_CHINOOK_1,								// air_to_air_weapon_config_type
			WEAPON_CONFIG_TYPE_CH47D_CHINOOK_1,								// air_to_surface_weapon_config_type
			WEAPON_CONFIG_TYPE_CH47D_CHINOOK_1,								// scout_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_NO_WEAPON,								// default_weapon_type
			TARGET_SYMBOL_HELICOPTER,											// target_symbol_type
			TARGET_PRIORITY_MEDIUM,												// target_priority_type
			FORCE_INFO_CATAGORY_UNARMED_HELICOPTER,						// force_info_catagory
			THREAT_TYPE_INVALID,													// threat_type
			VIEW_CATEGORY_TRANSPORT_HELICOPTERS,							// view_category
			VIEW_TYPE_CH47D_CHINOOK,											// view_type
			MAP_ICON_TRANSPORT_HELICOPTER,									// map icon

         5.0,																		// centre_of_gravity_to_ground_distance
         4.22,																		// centre_of_gravity_to_ground_distance_destroyed
         15.0,																		// chase_view_min_distance
         100.0,	  																// chase_view_max_distance
			0.5,																		// chase_view_min_distance_test
         2.0 * KILOMETRE,														// chase_view_max_distance_test
         knots_to_metres_per_second (70.0),								// cruise_velocity
         40.0,																		// cruise_altitude
         40.0,																		// attack_altitude
			0.0,																		// destroyed_bank_offset
			0.0,																		// destroyed_pitch_offset
			rad (3.0),																// fuselage_angle
			0.0,																		// liftoff_velocity
			rad (3.5),																// main_rotor_shaft_angle
			1.0,																		// main_rotor_direction
			rad (-4.0),																// main_rotor_blade_droop_angle
			0.0,																		// propellor_direction
			rad (45),																// max_turn_rate (deg / sec)
			rad (180.0),															// max_roll
			1.0,																		// max_vertical_turn_allowance
			15.0,																		// avoidance_radius
			6.0 * G,																	// g_max
			10.2,																		// power_output
			0.0,																		// tail_rotor_direction
			3000.0,																	// recon_radius
			10.0,																		// target_scan_delay
			0.0,																		// air_scan_range
			0.0,																		// surface_scan_range
			0.0,																		// potential_air_to_air_threat
			0.0,																		// potential_air_to_surface_threat
			10.0,																		// Ammo_economy
			1136.0,																	// Fuel_default_weight
			10.0,																		// Fuel_economy
			2.0,																	// number_of_main_rotors
			9.145,																	// main_rotor_radius

			800,																		// initial_damage_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,										// explosive_quality
			EXPLOSIVE_POWER_HIGH,												// explosive_power
			FALSE,																	// offensive_capability
			TRUE,																	// player_controllable JB 030408 Fly any aircraft
			50,																		// points value

			SOUND_SAMPLE_INDEX_CH47,					                // continuous_sound_effect_index
			SOUND_SAMPLE_INDEX_LARGE_HELICOPTER_ROTOR_WIND_UP,			// wind_up_sound_effect_index
			SOUND_SAMPLE_INDEX_LARGE_HELICOPTER_ROTOR_WIND_DOWN,		// wind_down_sound_effect_index
      },
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_AIRCRAFT_MI6_HOOK
		//
		////////////////////////////////////////
		{
			"Mi-6 Hook",															// full_name
         "Mi-6 HOOK",			 		 										// long_display_name
         "Mi-6",	  	  															// short_display_name
			"HELICOPTER",															// easy_display_name

			OBJECT_3D_MI6_HOOK,													// default_3d_shape
			NUM_GUNSHIP_TYPES,													// gunship_type
			ENTITY_FORCE_AIR,														// force
			WEAPON_CONFIG_TYPE_MI6_HOOK_1, 									// default_weapon_config_type
			WEAPON_CONFIG_TYPE_MI6_HOOK_1, 									// min_weapon_config_type
			WEAPON_CONFIG_TYPE_MI6_HOOK_1, 									// max_weapon_config_type
			WEAPON_CONFIG_TYPE_MI6_HOOK_1,									// air_to_air_weapon_config_type
			WEAPON_CONFIG_TYPE_MI6_HOOK_1,									// air_to_surface_weapon_config_type
			WEAPON_CONFIG_TYPE_MI6_HOOK_1,									// scout_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_NO_WEAPON,		  						// default_weapon_type
			TARGET_SYMBOL_HELICOPTER,											// target_symbol_type
			TARGET_PRIORITY_MEDIUM,  											// target_priority_type
			FORCE_INFO_CATAGORY_UNARMED_HELICOPTER,						// force_info_catagory
			THREAT_TYPE_INVALID,													// threat_type
			VIEW_CATEGORY_TRANSPORT_HELICOPTERS,							// view_category
			VIEW_TYPE_MI6_HOOK,													// view_type
			MAP_ICON_TRANSPORT_HELICOPTER,									// map icon

			6.81,																		// centre_of_gravity_to_ground_distance
         6.00,																		// centre_of_gravity_to_ground_distance_destroyed
         25.0,																		// chase_view_min_distance
         125.0,	  																// chase_view_max_distance
			0.5,																		// chase_view_min_distance_test
         2.0 * KILOMETRE,														// chase_view_max_distance_test
			knots_to_metres_per_second (70.0),								// cruise_velocity
			40.0,																		// cruise_altitude
			40.0,																		// attack_altitude
			0.0,																		// destroyed_bank_offset
			rad (-2.5),																// destroyed_pitch_offset
			rad (1.5),																// fuselage_angle
			0.0,																		// liftoff_velocity
			rad (4.0),																// main_rotor_shaft_angle
			1.0,																		// main_rotor_direction
			rad (-4.0),																// main_rotor_blade_droop_angle
			0.0,																		// propellor_direction
			rad (45),																// max_turn_rate (deg / sec)
			rad (180.0),															// max_roll
			1.0,																		// max_vertical_turn_allowance
			15.0,																		// avoidance_radius
			6.0 * G,																	// g_max
			10.3,																		// power_output
			1.0,																		// tail_rotor_direction
			3000.0,																	// recon_radius
			10.0,																		// target_scan_delay
			0.0,																		// air_scan_range
			0.0,																		// surface_scan_range
			0.0,																		// potential_air_to_air_threat
			0.0,																		// potential_air_to_surface_threat
			10.0,																		// Ammo_economy
			1136.0,																	// Fuel_default_weight
			10.0,																		// Fuel_economy
			1.0,																	// number_of_main_rotors
			17.5,																	// main_rotor_radius

			1000,																		// initial_damage_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,										// explosive_quality
			EXPLOSIVE_POWER_HIGH,												// explosive_power
			FALSE,																	// offensive_capability
			TRUE,																	// player_controllable JB 030408 Fly any aircraft
			50,																		// points value

			SOUND_SAMPLE_INDEX_MI16,					                // continuous_sound_effect_index
			SOUND_SAMPLE_INDEX_LARGE_HELICOPTER_ROTOR_WIND_UP,			// wind_up_sound_effect_index
			SOUND_SAMPLE_INDEX_LARGE_HELICOPTER_ROTOR_WIND_DOWN,		// wind_down_sound_effect_index
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_AIRCRAFT_A10A_THUNDERBOLT
		//
		////////////////////////////////////////
		{
			"A-10A Thunderbolt",													// full_name
         "A-10A THUNDERBOLT",			 										// long_display_name
         "A-10A",	  	  															// short_display_name
			"AIRCRAFT",																// easy_display_name

			OBJECT_3D_A10A_THUNDERBOLT,										// default_3d_shape
			NUM_GUNSHIP_TYPES,													// gunship_type
			ENTITY_FORCE_AIR,														// force
			WEAPON_CONFIG_TYPE_A10A_THUNDERBOLT_1,							// default_weapon_config_type
			WEAPON_CONFIG_TYPE_A10A_THUNDERBOLT_1,							// min_weapon_config_type
			WEAPON_CONFIG_TYPE_A10A_THUNDERBOLT_1,							// max_weapon_config_type
			WEAPON_CONFIG_TYPE_A10A_THUNDERBOLT_1,							// air_to_air_weapon_config_type
			WEAPON_CONFIG_TYPE_A10A_THUNDERBOLT_1,							// air_to_surface_weapon_config_type
			WEAPON_CONFIG_TYPE_A10A_THUNDERBOLT_1,							// scout_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_GAU8A_30MM_ROUND,						// default_weapon_type
			TARGET_SYMBOL_AIRCRAFT,												// target_symbol_type
			TARGET_PRIORITY_MEDIUM,												// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_FIXED_WING,							// force_info_catagory
			THREAT_TYPE_AIRBORNE_RADAR,										// threat_type
			VIEW_CATEGORY_COMBAT_AIRCRAFT,									// view_category
			VIEW_TYPE_A10A_THUNDERBOLT,										// view_type
			MAP_ICON_JET,															// map icon

			2.05,																		// centre_of_gravity_to_ground_distance
         0.45,																		// centre_of_gravity_to_ground_distance_destroyed
         15.0,																		// chase_view_min_distance
         100.0,	  																// chase_view_max_distance
			0.5,																		// chase_view_min_distance_test
         2.0 * KILOMETRE,														// chase_view_max_distance_test
			knots_to_metres_per_second (300.0),								// cruise_velocity
			700.0,																	// cruise_altitude
			100.0,																	// attack_altitude
			0.0,																		// destroyed_bank_offset
			0.0,																		// destroyed_pitch_offset
			rad (0.0),																// fuselage_angle
			knots_to_metres_per_second (120),								// liftoff_velocity
			rad (0.0),																// main_rotor_shaft_angle
			0.0,																		// main_rotor_direction
			rad (0.0),																// main_rotor_blade_droop_angle
			0.0,																		// propellor_direction
			rad (180.0),															// max_turn_rate (deg / sec)
			rad (120.0),															// max_roll
			0.5,																		// max_vertical_turn_allowance
			15.0,																		// avoidance_radius
			7.0 * G,																	// g_max
			20.0,																		// power_output
			0.0,																		// tail_rotor_direction
			6000.0,																	// recon_radius
			10.0,																		// target_scan_delay
			3000.0,																	// air_scan_range
			5000.0,																	// surface_scan_range
			0.8,																		// potential_air_to_air_threat
			1.0,																		// potential_air_to_surface_threat
			10.0,																		// Ammo_economy
			1136.0,																	// Fuel_default_weight
			10.0,																		// Fuel_economy
			0.0,																	// number_of_main_rotors
			0.0,																	// main_rotor_radius

			850,																		// initial_damage_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,										// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,												// explosive_power
			TRUE,																		// offensive_capability
			FALSE,																	// player_controllable
			300,																		// points value

			SOUND_SAMPLE_INDEX_A10,										// continuous_sound_effect_index
			SOUND_SAMPLE_INDEX_NONE,											// wind_up_sound_effect_index
			SOUND_SAMPLE_INDEX_NONE,											// wind_down_sound_effect_index
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_AIRCRAFT_SU25_FROGFOOT
		//
		////////////////////////////////////////
		{
			"Su-25 Frogfoot",														// full_name
         "Su-25 FROGFOOT",		 		 										// long_display_name
         "Su-25",	  	  															// short_display_name
			"AIRCRAFT",																// easy_display_name

			OBJECT_3D_SU25,														// default_3d_shape
			NUM_GUNSHIP_TYPES,													// gunship_type
			ENTITY_FORCE_AIR,														// force
			WEAPON_CONFIG_TYPE_SU25_FROGFOOT_1,								// default_weapon_config_type
			WEAPON_CONFIG_TYPE_SU25_FROGFOOT_1,								// min_weapon_config_type
			WEAPON_CONFIG_TYPE_SU25_FROGFOOT_1,								// max_weapon_config_type
			WEAPON_CONFIG_TYPE_SU25_FROGFOOT_1,								// air_to_air_weapon_config_type
			WEAPON_CONFIG_TYPE_SU25_FROGFOOT_1,								// air_to_surface_weapon_config_type
			WEAPON_CONFIG_TYPE_SU25_FROGFOOT_1,								// scout_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_AO17A_30MM_ROUND,						// default_weapon_type
			TARGET_SYMBOL_AIRCRAFT,												// target_symbol_type
			TARGET_PRIORITY_MEDIUM,												// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_FIXED_WING,							// force_info_catagory
			THREAT_TYPE_AIRBORNE_RADAR,										// threat_type
			VIEW_CATEGORY_COMBAT_AIRCRAFT,									// view_category
			VIEW_TYPE_SU25_FROGFOOT,											// view_type
			MAP_ICON_JET,															// map icon

			1.55,																		// centre_of_gravity_to_ground_distance
         0.62,																		// centre_of_gravity_to_ground_distance_destroyed
         15.0,																		// chase_view_min_distance
         100.0,	  																// chase_view_max_distance
			0.5,																		// chase_view_min_distance_test
         2.0 * KILOMETRE,														// chase_view_max_distance_test
			knots_to_metres_per_second (300.0),								// cruise_velocity
			700.0,																	// cruise_altitude
			100.0,																	// attack_altitude
			rad (-5.8),																// destroyed_bank_offset
			0.0,																		// destroyed_pitch_offset
			rad (3.2),																// fuselage_angle
			knots_to_metres_per_second (120),								// liftoff_velocity
			rad (0.0),																// main_rotor_shaft_angle
			0.0,																		// main_rotor_direction
			rad (0.0),																// main_rotor_blade_droop_angle
			0.0,																		// propellor_direction
			rad(180),																// max_turn_rate (deg / sec)
			rad (120.0),															// max_roll
			0.5,																		// max_vertical_turn_allowance
			12.0,																		// avoidance_radius
			8.0 * G,																	// g_max
			20.0,																		// power_output
			0.0,																		// tail_rotor_direction
			6000.0,																	// recon_radius
			10.0,																		// target_scan_delay
			3000.0,																	// air_scan_range
			5000.0,																	// surface_scan_range
			0.8,																		// potential_air_to_air_threat
			1.0,																		// potential_air_to_surface_threat
			10.0,																		// Ammo_economy
			1136.0,																	// Fuel_default_weight
			10.0,																		// Fuel_economy
			0.0,																	// number_of_main_rotors
			0.0,																	// main_rotor_radius

			850,																		// initial_damage_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,										// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,												// explosive_power
			TRUE,																		// offensive_capability
			FALSE,																	// player_controllable
			300,																		// points value

			SOUND_SAMPLE_INDEX_JET_LOW,										// continuous_sound_effect_index
			SOUND_SAMPLE_INDEX_NONE,											// wind_up_sound_effect_index
			SOUND_SAMPLE_INDEX_NONE,											// wind_down_sound_effect_index
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_AIRCRAFT_F16_FIGHTING_FALCON
		//
		////////////////////////////////////////
		{
			"F-16C Fighting Falcon",												// full_name
         "F-16 FIGHTING FALCON",	  	 										// long_display_name
         "F-16",	  	  															// short_display_name
			"AIRCRAFT",																// easy_display_name

			OBJECT_3D_F16_FIGHTING_FALCON,									// default_3d_shape
			NUM_GUNSHIP_TYPES,													// gunship_type
			ENTITY_FORCE_AIR,														// force
			WEAPON_CONFIG_TYPE_F16_FIGHTING_FALCON_1,						// default_weapon_config_type
			WEAPON_CONFIG_TYPE_F16_FIGHTING_FALCON_1,						// min_weapon_config_type
			WEAPON_CONFIG_TYPE_F16_FIGHTING_FALCON_2,						// max_weapon_config_type
			WEAPON_CONFIG_TYPE_F16_FIGHTING_FALCON_1,						// air_to_air_weapon_config_type
			WEAPON_CONFIG_TYPE_F16_FIGHTING_FALCON_2,						// air_to_surface_weapon_config_type
			WEAPON_CONFIG_TYPE_F16_FIGHTING_FALCON_2,						// scout_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_M61A1_20MM_ROUND,						// default_weapon_type
			TARGET_SYMBOL_AIRCRAFT,						 						// target_symbol_type
			TARGET_PRIORITY_MEDIUM,												// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_FIXED_WING,							// force_info_catagory
			THREAT_TYPE_AIRBORNE_RADAR,										// threat_type
			VIEW_CATEGORY_COMBAT_AIRCRAFT,									// view_category
			VIEW_TYPE_F16_FIGHTING_FALCON,									// view_type
			MAP_ICON_JET,															// map icon

			1.675,																	// centre_of_gravity_to_ground_distance
         0.80,																		// centre_of_gravity_to_ground_distance_destroyed
         15.0,																		// chase_view_min_distance
         100.0,	  																// chase_view_max_distance
			0.5,																		// chase_view_min_distance_test
         2.0 * KILOMETRE,														// chase_view_max_distance_test
			knots_to_metres_per_second (450.0),								// cruise_velocity
			900.0,																	// cruise_altitude
			100.0,																	// attack_altitude
			rad (9.9),																// destroyed_bank_offset
			rad (1.4),																// destroyed_pitch_offset
			rad (2.0),																// fuselage_angle
			knots_to_metres_per_second (220),								// liftoff_velocity
			rad (0.0),																// main_rotor_shaft_angle
			0.0,																		// main_rotor_direction
			rad (0.0),																// main_rotor_blade_droop_angle
			0.0,																		// propellor_direction
			rad (180),																// max_turn_rate (deg / sec)
			rad (180.0),															// max_roll
			1.0,																		// max_vertical_turn_allowance
			10.0,																		// avoidance_radius
			10.0 * G,																// g_max
			20.0,																		// power_output
			0.0,																		// tail_rotor_direction
			10000.0,																	// recon_radius
			10.0,																		// target_scan_delay
			5000.0,																	// air_scan_range
			6000.0,																	// surface_scan_range
			1.0,																		// potential_air_to_air_threat
			1.0,																		// potential_air_to_surface_threat
			10.0,																		// Ammo_economy
			1136.0,																	// Fuel_default_weight
			10.0,																		// Fuel_economy
			0.0,																	// number_of_main_rotors
			0.0,																	// main_rotor_radius

			700,																		// initial_damage_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,										// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,												// explosive_power
			TRUE,																		// offensive_capability
			FALSE,																	// player_controllable
			400,																		// points value

			SOUND_SAMPLE_INDEX_JET_MEDIUM,									// continuous_sound_effect_index
			SOUND_SAMPLE_INDEX_NONE,											// wind_up_sound_effect_index
			SOUND_SAMPLE_INDEX_NONE,											// wind_down_sound_effect_index
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_AIRCRAFT_MIG29_FULCRUM
		//
		////////////////////////////////////////
		{
			"MiG-29 Fulcrum",														// full_name
         "MiG-29 FULCRUM",	  			 										// long_display_name
         "MiG-29",	  															// short_display_name
			"AIRCRAFT",																// easy_display_name

			OBJECT_3D_MIG29_FULCRUM,											// default_3d_shape
			NUM_GUNSHIP_TYPES,													// gunship_type
			ENTITY_FORCE_AIR,														// force
			WEAPON_CONFIG_TYPE_MIG29_FULCRUM_1,								// default_weapon_config_type
			WEAPON_CONFIG_TYPE_MIG29_FULCRUM_1,								// min_weapon_config_type
			WEAPON_CONFIG_TYPE_MIG29_FULCRUM_2,								// max_weapon_config_type
			WEAPON_CONFIG_TYPE_MIG29_FULCRUM_1,								// air_to_air_weapon_config_type
			WEAPON_CONFIG_TYPE_MIG29_FULCRUM_2,								// air_to_surface_weapon_config_type
			WEAPON_CONFIG_TYPE_MIG29_FULCRUM_2,								// scout_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_GSH301_30MM_ROUND,						// default_weapon_type
			TARGET_SYMBOL_AIRCRAFT,						 						// target_symbol_type
			TARGET_PRIORITY_MEDIUM,												// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_FIXED_WING,							// force_info_catagory
			THREAT_TYPE_AIRBORNE_RADAR,										// threat_type
			VIEW_CATEGORY_COMBAT_AIRCRAFT,									// view_category
			VIEW_TYPE_MIG29_FULCRUM,											// view_type
			MAP_ICON_JET,															// map icon

			1.5882,																	// centre_of_gravity_to_ground_distance
         0.42,																		// centre_of_gravity_to_ground_distance_destroyed
         15.0,																		// chase_view_min_distance
         100.0,	  																// chase_view_max_distance
			0.5,																		// chase_view_min_distance_test
         2.0 * KILOMETRE,														// chase_view_max_distance_test
			knots_to_metres_per_second (450.0),								// cruise_velocity
			900.0,																	// cruise_altitude
			100.0,																	// attack_altitude
			0.0,																		// destroyed_bank_offset
			rad (-3.0),																// destroyed_pitch_offset
			rad (0.0),																// fuselage_angle
			knots_to_metres_per_second (220),								// liftoff_velocity
			rad (0.0),																// main_rotor_shaft_angle
			0.0,																		// main_rotor_direction
			rad (0.0),																// main_rotor_blade_droop_angle
			0.0,																		// propellor_direction
			rad (180),																// max_turn_rate (deg / sec)
			rad (180.0),															// max_roll
			1.0,																		// max_vertical_turn_allowance
			12.0,																		// avoidance_radius
			10.0 * G,																// g_max
			20.0,																		// power_output
			0.0,																		// tail_rotor_direction
			10000.0,																	// recon_radius
			10.0,																		// target_scan_delay
			5000.0,																	// air_scan_range
			6000.0,																	// surface_scan_range
			1.0,																		// potential_air_to_air_threat
			1.0,																		// potential_air_to_surface_threat
			10.0,																		// Ammo_economy
			1136.0,																	// Fuel_default_weight
			10.0,																		// Fuel_economy
			0.0,																	// number_of_main_rotors
			0.0,																	// main_rotor_radius

			700,																		// initial_damage_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,										// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,												// explosive_power
			TRUE,																		// offensive_capability
			FALSE,																	// player_controllable
			400,																		// points value

			SOUND_SAMPLE_INDEX_JET_MEDIUM,									// continuous_sound_effect_index
			SOUND_SAMPLE_INDEX_NONE,											// wind_up_sound_effect_index
			SOUND_SAMPLE_INDEX_NONE,											// wind_down_sound_effect_index
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_AIRCRAFT_AV8B_HARRIER
		//
		////////////////////////////////////////
		{
			"AV-8B Harrier",														// full_name
         "AV-8B HARRIER",	  			 										// long_display_name
         "AV-8B",	  																// short_display_name
			"AIRCRAFT",																// easy_display_name

			OBJECT_3D_HARRIER,													// default_3d_shape
			NUM_GUNSHIP_TYPES,													// gunship_type
			ENTITY_FORCE_AIR,														// force
			WEAPON_CONFIG_TYPE_AV8B_HARRIER_1,	 							// default_weapon_config_type
			WEAPON_CONFIG_TYPE_AV8B_HARRIER_1,	 							// min_weapon_config_type
			WEAPON_CONFIG_TYPE_AV8B_HARRIER_1,	 							// max_weapon_config_type
			WEAPON_CONFIG_TYPE_AV8B_HARRIER_1,								// air_to_air_weapon_config_type
			WEAPON_CONFIG_TYPE_AV8B_HARRIER_1,								// air_to_surface_weapon_config_type
			WEAPON_CONFIG_TYPE_AV8B_HARRIER_1,								// scout_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_GAU12U_25MM_ROUND,						// default_weapon_type
			TARGET_SYMBOL_AIRCRAFT,												// target_symbol_type
			TARGET_PRIORITY_MEDIUM,												// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_FIXED_WING,							// force_info_catagory
			THREAT_TYPE_AIRBORNE_RADAR,										// threat_type
			VIEW_CATEGORY_COMBAT_AIRCRAFT,									// view_category
			VIEW_TYPE_AV8B_HARRIER,												// view_type
			MAP_ICON_JET,															// map icon

			1.925,																	// centre_of_gravity_to_ground_distance
         1.07,																		// centre_of_gravity_to_ground_distance_destroyed
         15.0,																		// chase_view_min_distance
         100.0,	  																// chase_view_max_distance
			0.5,																		// chase_view_min_distance_test
         2.0 * KILOMETRE,														// chase_view_max_distance_test
			knots_to_metres_per_second (350.0),								// cruise_velocity
			800.0,																	// cruise_altitude
			100.0,																	// attack_altitude
			rad (13.2),																// destroyed_bank_offset
			rad (2.0),																// destroyed_pitch_offset
			rad (0.6),																// fuselage_angle
			knots_to_metres_per_second (180),								// liftoff_velocity
			rad (0.0),																// main_rotor_shaft_angle
			0.0,																		// main_rotor_direction
			rad (0.0),																// main_rotor_blade_droop_angle
			0.0,																		// propellor_direction
			rad (180),																// max_turn_rate (deg / sec)
			rad (120.0),															// max_roll
			0.5,																		// max_vertical_turn_allowance
			9.5,																		// avoidance_radius
			6.0 * G,																	// g_max
			20.0,																		// power_output
			0.0,																		// tail_rotor_direction
			6000.0,																	// recon_radius
			10.0,																		// target_scan_delay
			3000.0,																	// air_scan_range
			5000.0,																	// surface_scan_range
			0.8,																		// potential_air_to_air_threat
			1.0,																		// potential_air_to_surface_threat
			10.0,																		// Ammo_economy
			1136.0,																	// Fuel_default_weight
			10.0,																		// Fuel_economy
			0.0,																	// number_of_main_rotors
			0.0,																	// main_rotor_radius

			700,																		// initial_damage_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,										// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,												// explosive_power
			TRUE,																		// offensive_capability
			FALSE,																	// player_controllable
			200,																		// points value

			SOUND_SAMPLE_INDEX_JET_MEDIUM,									// continuous_sound_effect_index
			SOUND_SAMPLE_INDEX_NONE,											// wind_up_sound_effect_index
			SOUND_SAMPLE_INDEX_NONE,											// wind_down_sound_effect_index
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_AIRCRAFT_YAK41_FREESTYLE
		//
		////////////////////////////////////////
		{
			"Yak-41 Freestyle",													// full_name
         "Yak-41 FREESTYLE",	 		 										// long_display_name
         "Yak-41",	  	 														// short_display_name
			"AIRCRAFT",																// easy_display_name

			OBJECT_3D_YAK_41,														// default_3d_shape
			NUM_GUNSHIP_TYPES,													// gunship_type
			ENTITY_FORCE_AIR,														// force
			WEAPON_CONFIG_TYPE_YAK141_FREESTYLE_1,							// default_weapon_config_type
			WEAPON_CONFIG_TYPE_YAK141_FREESTYLE_1,							// min_weapon_config_type
			WEAPON_CONFIG_TYPE_YAK141_FREESTYLE_1,							// max_weapon_config_type
			WEAPON_CONFIG_TYPE_YAK141_FREESTYLE_1,							// air_to_air_weapon_config_type
			WEAPON_CONFIG_TYPE_YAK141_FREESTYLE_1,							// air_to_surface_weapon_config_type
			WEAPON_CONFIG_TYPE_YAK141_FREESTYLE_1,							// scout_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_GSH301_30MM_ROUND,						// default_weapon_type
			TARGET_SYMBOL_AIRCRAFT,						 						// target_symbol_type
			TARGET_PRIORITY_MEDIUM,												// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_FIXED_WING,							// force_info_catagory
			THREAT_TYPE_AIRBORNE_RADAR,										// threat_type
			VIEW_CATEGORY_COMBAT_AIRCRAFT,									// view_category
			VIEW_TYPE_YAK41_FREESTYLE,											// view_type
			MAP_ICON_JET,															// map icon

			2.45,																		// centre_of_gravity_to_ground_distance
         1.25,																		// centre_of_gravity_to_ground_distance_destroyed
         15.0,																		// chase_view_min_distance
         100.0,	  																// chase_view_max_distance
			0.5,																		// chase_view_min_distance_test
         2.0 * KILOMETRE,														// chase_view_max_distance_test
			knots_to_metres_per_second (350.0),								// cruise_velocity
			800.0,																	// cruise_altitude
			100.0,																	// attack_altitude
			0.0,																		// destroyed_bank_offset
			rad (0.4),																// destroyed_pitch_offset
			rad (-0.3),																// fuselage_angle
			knots_to_metres_per_second (180),								// liftoff_velocity
			rad (0.0),																// main_rotor_shaft_angle
			0.0,																		// main_rotor_direction
			rad (0.0),																// main_rotor_blade_droop_angle
			0.0,																		// propellor_direction
			rad (180),																// max_turn_rate (deg / sec)
			rad (120.0),															// max_roll
			0.5,																		// max_vertical_turn_allowance
			15.0,																		// avoidance_radius
			8.0 * G,																	// g_max
			20.0,																		// power_output
			0.0,																		// tail_rotor_direction
			6000.0,																	// recon_radius
			10.0,																		// target_scan_delay
			3000.0,																	// air_scan_range
			5000.0,																	// surface_scan_range
			0.8,																		// potential_air_to_air_threat
			1.0,																		// potential_air_to_surface_threat
			10.0,																		// Ammo_economy
			1136.0,																	// Fuel_default_weight
			10.0,																		// Fuel_economy
			0.0,																	// number_of_main_rotors
			0.0,																	// main_rotor_radius

			700,																		// initial_damage_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,										// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,												// explosive_power
			TRUE,																		// offensive_capability
			FALSE,																	// player_controllable
			200,																		// points value

			SOUND_SAMPLE_INDEX_JET_MEDIUM,									// continuous_sound_effect_index
			SOUND_SAMPLE_INDEX_NONE,											// wind_up_sound_effect_index
			SOUND_SAMPLE_INDEX_NONE,											// wind_down_sound_effect_index
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_AIRCRAFT_FA18_HORNET
		//
		////////////////////////////////////////
		{
			"F/A-18C Hornet",														// full_name
         "F/A-18 HORNET",	 			 										// long_display_name
         "F/A-18",	  	 														// short_display_name
			"AIRCRAFT",																// easy_display_name

			OBJECT_3D_FA_18,														// default_3d_shape
			NUM_GUNSHIP_TYPES,													// gunship_type
			ENTITY_FORCE_AIR,														// force
			WEAPON_CONFIG_TYPE_FA18_HORNET_1,								// default_weapon_config_type
			WEAPON_CONFIG_TYPE_FA18_HORNET_1,								// min_weapon_config_type
			WEAPON_CONFIG_TYPE_FA18_HORNET_2,								// max_weapon_config_type
			WEAPON_CONFIG_TYPE_FA18_HORNET_1,								// air_to_air_weapon_config_type
			WEAPON_CONFIG_TYPE_FA18_HORNET_2,								// air_to_surface_weapon_config_type
			WEAPON_CONFIG_TYPE_FA18_HORNET_2,								// scout_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_M61A1_20MM_ROUND,						// default_weapon_type
			TARGET_SYMBOL_AIRCRAFT,						 						// target_symbol_type
			TARGET_PRIORITY_MEDIUM,												// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_FIXED_WING,							// force_info_catagory
			THREAT_TYPE_AIRBORNE_RADAR,										// threat_type
			VIEW_CATEGORY_COMBAT_AIRCRAFT,									// view_category
			VIEW_TYPE_FA18_HORNET,												// view_type
			MAP_ICON_JET,															// map icon

			1.975,																	// centre_of_gravity_to_ground_distance
         0.82,																		// centre_of_gravity_to_ground_distance_destroyed
         15.0,																		// chase_view_min_distance
         100.0,	  																// chase_view_max_distance
			0.5,																		// chase_view_min_distance_test
         2.0 * KILOMETRE,														// chase_view_max_distance_test
			knots_to_metres_per_second (450.0),								// cruise_velocity
			1000.0,																	// cruise_altitude
			100.0,																	// attack_altitude
			0.0,																		// destroyed_bank_offset
			rad (-0.9),																// destroyed_pitch_offset
			rad (0.6),																// fuselage_angle
			knots_to_metres_per_second (230),								// liftoff_velocity
			rad (0.0),																// main_rotor_shaft_angle
			0.0,																		// main_rotor_direction
			rad (0.0),																// main_rotor_blade_droop_angle
			0.0,																		// propellor_direction
			rad (180),																// max_turn_rate (deg / sec)
			rad (180.0),															// max_roll
			1.0,																		// max_vertical_turn_allowance
			12.0,																		// avoidance_radius
			10.0 * G,																// g_max
			20.0,																		// power_output
			0.0,																		// tail_rotor_direction
			10000.0,																	// recon_radius
			10.0,																		// target_scan_delay
			6000.0,																	// air_scan_range
			4000.0,																	// surface_scan_range
			1.0,																		// potential_air_to_air_threat
			1.0,																		// potential_air_to_surface_threat
			10.0,																		// Ammo_economy
			1136.0,																	// Fuel_default_weight
			10.0,																		// Fuel_economy
			0.0,																	// number_of_main_rotors
			0.0,																	// main_rotor_radius

			700,																		// initial_damage_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,										// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,												// explosive_power
			TRUE,																		// offensive_capability
			FALSE,																	// player_controllable
			350,																		// points value

			SOUND_SAMPLE_INDEX_JET_MEDIUM,									// continuous_sound_effect_index
			SOUND_SAMPLE_INDEX_NONE,											// wind_up_sound_effect_index
			SOUND_SAMPLE_INDEX_NONE,											// wind_down_sound_effect_index
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_AIRCRAFT_SU33_FLANKER
		//
		////////////////////////////////////////
		{
			"Su-33 Flanker",														// full_name
         "Su-33 FLANKER",	 			 										// long_display_name
         "Su-33",	 	 	 														// short_display_name
			"AIRCRAFT",																// easy_display_name

			OBJECT_3D_SU33,														// default_3d_shape
			NUM_GUNSHIP_TYPES,													// gunship_type
			ENTITY_FORCE_AIR,														// force
			WEAPON_CONFIG_TYPE_SU33_FLANKER_1,								// default_weapon_config_type
			WEAPON_CONFIG_TYPE_SU33_FLANKER_1,								// min_weapon_config_type
			WEAPON_CONFIG_TYPE_SU33_FLANKER_2,								// max_weapon_config_type
			WEAPON_CONFIG_TYPE_SU33_FLANKER_1,								// air_to_air_weapon_config_type
			WEAPON_CONFIG_TYPE_SU33_FLANKER_2,								// air_to_surface_weapon_config_type
			WEAPON_CONFIG_TYPE_SU33_FLANKER_2,								// scout_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_GSH301_30MM_ROUND,						// default_weapon_type
			TARGET_SYMBOL_AIRCRAFT,												// target_symbol_type
			TARGET_PRIORITY_MEDIUM,												// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_FIXED_WING,							// force_info_catagory
			THREAT_TYPE_AIRBORNE_RADAR,										// threat_type
			VIEW_CATEGORY_COMBAT_AIRCRAFT,									// view_category
			VIEW_TYPE_SU33_FLANKER,												// view_type
			MAP_ICON_JET,															// map icon

			2.8,																		// centre_of_gravity_to_ground_distance
         1.00,																		// centre_of_gravity_to_ground_distance_destroyed
         15.0,																		// chase_view_min_distance
         100.0,	  																// chase_view_max_distance
			0.5,																		// chase_view_min_distance_test
         2.0 * KILOMETRE,														// chase_view_max_distance_test
			knots_to_metres_per_second (450.0),								// cruise_velocity
			1000.0,																	// cruise_altitude
			100.0,																	// attack_altitude
			0.0,																		// destroyed_bank_offset
			rad (-1.7),																// destroyed_pitch_offset
			rad (-3.7),																// fuselage_angle
			knots_to_metres_per_second (230),								// liftoff_velocity
			rad (0.0),																// main_rotor_shaft_angle
			0.0,																		// main_rotor_direction
			rad (0.0),																// main_rotor_blade_droop_angle
			0.0,																		// propellor_direction
			rad (180),																// max_turn_rate (deg / sec)
			rad (180.0),															// max_roll
			1.0,																		// max_vertical_turn_allowance
			15.0,																		// avoidance_radius
			10.0 * G,																// g_max
			20.0,																		// power_output
			0.0,																		// tail_rotor_direction
			10000.0,																	// recon_radius
			10.0,																		// target_scan_delay
			6000.0,																	// air_scan_range
			4000.0,																	// surface_scan_range
			1.0,																		// potential_air_to_air_threat
			1.0,																		// potential_air_to_surface_threat
			10.0,																		// Ammo_economy
			1136.0,																	// Fuel_default_weight
			10.0,																		// Fuel_economy
			0.0,																	// number_of_main_rotors
			0.0,																	// main_rotor_radius

			700,																		// initial_damage_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,										// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,												// explosive_power
			TRUE,																		// offensive_capability
			FALSE,																	// player_controllable
			350,																		// points value

			SOUND_SAMPLE_INDEX_JET_MEDIUM,									// continuous_sound_effect_index
			SOUND_SAMPLE_INDEX_NONE,											// wind_up_sound_effect_index
			SOUND_SAMPLE_INDEX_NONE,											// wind_down_sound_effect_index
		},

		////////////////////////////////////////////////////////////////////////////////
		//
		// COMANCHE HOKUM
		//
		////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_AIRCRAFT_AH64A_APACHE
		//
		////////////////////////////////////////
      ////Moje 030816 1st line under "OBJECT_3D_AH_64A" changed from "NUM_GUNSHIP_TYPES"
      ////Moje 040209 CHanged loadout schemes
      {
         "AH-64A Apache",														// full_name
         "AH-64A APACHE",		  												// long_display_name
         "AH-64A",																// short_display_name
			"HELICOPTER",															// easy_display_name

         OBJECT_3D_AH_64A,														// default_3d_shape
			GUNSHIP_TYPE_AH64A,													// gunship_type
			ENTITY_FORCE_AIR,														// force
			WEAPON_CONFIG_TYPE_AH64A_APACHE_32,								// default_weapon_config_type
			WEAPON_CONFIG_TYPE_AH64A_APACHE_1,								// min_weapon_config_type
			WEAPON_CONFIG_TYPE_AH64A_APACHE_32,								// max_weapon_config_type
			WEAPON_CONFIG_TYPE_AH64A_APACHE_22,								// air_to_air_weapon_config_type
			WEAPON_CONFIG_TYPE_AH64A_APACHE_24,								// air_to_surface_weapon_config_type
			WEAPON_CONFIG_TYPE_AH64A_APACHE_23,								// scout_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_M230_30MM_ROUND,						// default_weapon_type
			TARGET_SYMBOL_HELICOPTER,											// target_symbol_type
			TARGET_PRIORITY_MEDIUM,												// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_HELICOPTER,							// force_info_catagory
			THREAT_TYPE_INVALID,			 										// threat_type
			VIEW_CATEGORY_COMBAT_HELICOPTERS,								// view_category
			VIEW_TYPE_AH64A_APACHE,												// view_type
			MAP_ICON_HELICOPTER,													// map icon

         3.8313,																	// centre_of_gravity_to_ground_distance
         3.1,																		// centre_of_gravity_to_ground_distance_destroyed
         15.0,																		// chase_view_min_distance
         100.0,	  																// chase_view_max_distance
			0.5,																		// chase_view_min_distance_test
         2.0 * KILOMETRE,														// chase_view_max_distance_test
         knots_to_metres_per_second (110.0),								// cruise_velocity
         15.0,																		// cruise_altitude
         10.0,																		// attack_altitude
			rad (26.0),																// destroyed_bank_offset
			rad (0.0),																// destroyed_pitch_offset
			rad (3.364),															// fuselage_angle
			0.0,																		// liftoff_velocity
			rad (3.5),																// main_rotor_shaft_angle
			-1.0,																		// main_rotor_direction
			rad (-4.0),																// main_rotor_blade_droop_angle
			0.0,																		// propellor_direction
			rad (200),																// max_turn_rate (deg / sec)
			rad (180.0),															// max_roll
			1.0,																		// max_vertical_turn_allowance
			15.0,																		// avoidance_radius
			6.0 * G,																	// g_max
			13.6,																		// power_output
			-1.0,																		// tail_rotor_direction
			5000.0,																	// recon_radius
			10.0,																		// target_scan_delay
			3000.0,																	// air_scan_range
			4000.0,																	// surface_scan_range
			1.0,																		// potential_air_to_air_threat
			1.0,																		// potential_air_to_surface_threat
			10.0,																		// Ammo_economy
			1136.0,																	// Fuel_default_weight
			10.0,																		// Fuel_economy
			1.0,																	// number_of_main_rotors
			7.315,																	// main_rotor_radius

			600,																		//DL initial_damage_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,										// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,												// explosive_power
			TRUE,																		// offensive_capability
			TRUE,																	// player_controllable JB 030408 Fly any aircraft
			120,																		// points value

			SOUND_SAMPLE_INDEX_SMALL_HELICOPTER_ROTOR,					// continuous_sound_effect_index
			SOUND_SAMPLE_INDEX_SMALL_HELICOPTER_ROTOR_WIND_UP,			// wind_up_sound_effect_index
			SOUND_SAMPLE_INDEX_SMALL_HELICOPTER_ROTOR_WIND_DOWN,		// wind_down_sound_effect_index
      },
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_AIRCRAFT_KA50_HOKUM
		//
		////////////////////////////////////////
      ////Moje 030816 1st line under "OBJECT_3D_KA_50" changed from "NUM_GUNSHIP_TYPES"
      {
         "Ka-50 Black Shark",															// full_name
         "Ka-50 Black Shark",		  													// long_display_name
         "Ka-50",													  				// short_display_name
			"HELICOPTER",															// easy_display_name

         OBJECT_3D_KA_50,														// default_3d_shape
			GUNSHIP_TYPE_KA50,													// gunship_type
			ENTITY_FORCE_AIR,														// force
			WEAPON_CONFIG_TYPE_KA50_HOKUM_7,									// default_weapon_config_type
			WEAPON_CONFIG_TYPE_KA50_HOKUM_1,									// min_weapon_config_type
			WEAPON_CONFIG_TYPE_KA50_HOKUM_30,									// max_weapon_config_type
			WEAPON_CONFIG_TYPE_KA50_HOKUM_12,									// air_to_air_weapon_config_type
			WEAPON_CONFIG_TYPE_KA50_HOKUM_7,									// air_to_surface_weapon_config_type
			WEAPON_CONFIG_TYPE_KA50_HOKUM_7,									// scout_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND,					// default_weapon_type
			TARGET_SYMBOL_HELICOPTER,											// target_symbol_type
			TARGET_PRIORITY_MEDIUM,												// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_HELICOPTER,							// force_info_catagory
			THREAT_TYPE_INVALID,			 										// threat_type
			VIEW_CATEGORY_COMBAT_HELICOPTERS,								// view_category
			VIEW_TYPE_KA50_HOKUM,												// view_type
			MAP_ICON_HELICOPTER,													// map icon

         4.065,																	// centre_of_gravity_to_ground_distance
         3.5,																		// centre_of_gravity_to_ground_distance_destroyed
         15.0,																		// chase_view_min_distance
         100.0,	  																// chase_view_max_distance
			0.5,																		// chase_view_min_distance_test
         2.0 * KILOMETRE,														// chase_view_max_distance_test
         knots_to_metres_per_second (115.0),								// cruise_velocity
         15.0,																		// cruise_altitude
         10.0,																		// attack_altitude
			rad (-16.0),		 													// destroyed_bank_offset
			rad (0.0),																// destroyed_pitch_offset
			rad (0.0),																// fuselage_angle
			0.0,																		// liftoff_velocity
			rad (3.5),																// main_rotor_shaft_angle
			1.0,																		// main_rotor_direction
			rad (-4.0),																// main_rotor_blade_droop_angle
			0.0,																		// propellor_direction
			rad (240),																// max_turn_rate (deg / sec)
			rad (180.0),															// max_roll
			1.0,																		// max_vertical_turn_allowance
			15.0,																		// avoidance_radius
			8.0 * G,																	// g_max
			14.5,																		// power_output
			-1.0,																		// tail_rotor_direction
			5000.0,																	// recon_radius
			10.0,																		// target_scan_delay
			3000.0,																	// air_scan_range
			4000.0,																	// surface_scan_range
			1.0,																		// potential_air_to_air_threat
			1.0,																		// potential_air_to_surface_threat
			10.0,																		// Ammo_economy
			1136.0,																	// Fuel_default_weight
			10.0,																		// Fuel_economy
			1.0,																	// number_of_main_rotors
			7.25,																	// main_rotor_radius

			600,																		// initial_damage_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,										// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,												// explosive_power
			TRUE,																		// offensive_capability
			TRUE,																	// player_controllable JB 030408 Fly any aircraft
			120,																		// points value

			SOUND_SAMPLE_INDEX_SMALL_HELICOPTER_ROTOR,					// continuous_sound_effect_index
			SOUND_SAMPLE_INDEX_SMALL_HELICOPTER_ROTOR_WIND_UP,			// wind_up_sound_effect_index
			SOUND_SAMPLE_INDEX_SMALL_HELICOPTER_ROTOR_WIND_DOWN,		// wind_down_sound_effect_index
      },
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_AIRCRAFT_OH58D_KIOWA_WARRIOR
		//
		////////////////////////////////////////
      {
         "OH-58D Kiowa Warrior",												//full_name
         "OH-58D KIOWA WARRIOR",												//long_display_name
         "OH-58D",		 										  				//short_display_name
			"HELICOPTER",															//easy_display_name

         OBJECT_3D_OH58D,														//default_3d_shape
			GUNSHIP_TYPE_KIOWA,													// gunship_type
			ENTITY_FORCE_AIR,														// force
			WEAPON_CONFIG_TYPE_OH58D_KIOWA_WARRIOR_8,						// default_weapon_config_type
			WEAPON_CONFIG_TYPE_OH58D_KIOWA_WARRIOR_1,						// min_weapon_config_type
			WEAPON_CONFIG_TYPE_OH58D_KIOWA_WARRIOR_20,						// max_weapon_config_type
			WEAPON_CONFIG_TYPE_OH58D_KIOWA_WARRIOR_13,						// air_to_air_weapon_config_type
			WEAPON_CONFIG_TYPE_OH58D_KIOWA_WARRIOR_7,						// air_to_surface_weapon_config_type
			WEAPON_CONFIG_TYPE_OH58D_KIOWA_WARRIOR_10,						// scout_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_NO_WEAPON,								// default_weapon_type
			TARGET_SYMBOL_HELICOPTER,											// target_symbol_type
			TARGET_PRIORITY_MEDIUM,												// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_HELICOPTER,							// force_info_catagory
			THREAT_TYPE_INVALID,			 										// threat_type
			VIEW_CATEGORY_COMBAT_HELICOPTERS,								// view_category
			VIEW_TYPE_OH58D_KIOWA_WARRIOR,									// view_type
			MAP_ICON_HELICOPTER,													// map icon

         2.9,																		// centre_of_gravity_to_ground_distance
         2.7,																		// centre_of_gravity_to_ground_distance_destroyed
         15.0,																		// chase_view_min_distance
         100.0,	  																// chase_view_max_distance
			0.5,																		// chase_view_min_distance_test
         2.0 * KILOMETRE,														// chase_view_max_distance_test
         knots_to_metres_per_second (120.0),								// cruise_velocity
         15.0,																		// cruise_altitude
         7.5,																		// attack_altitude
			rad (0.0),																// destroyed_bank_offset
			rad (0.0),																// destroyed_pitch_offset
			rad (0.0),																// fuselage_angle
			0.0,																		// liftoff_velocity
			rad (4.4),																// main_rotor_shaft_angle
			-1.0,																		// main_rotor_direction
			rad (-4.0),																// main_rotor_blade_droop_angle
			0.0,																		// propellor_direction
			rad (280),																// max_turn_rate (deg / sec)
			rad (180.0),															// max_roll
			1.0,																		// max_vertical_turn_allowance
			15.0,																		// avoidance_radius
			8.0 * G,																	// g_max
			14.0,																		// power_output
			-1.0,																		// tail_rotor_direction
			5000.0,																	// recon_radius
			10.0,																		// target_scan_delay
			3000.0,																	// air_scan_range
			4000.0,																	// surface_scan_range
			1.0,																		// potential_air_to_air_threat
			1.0,																		// potential_air_to_surface_threat
			10.0,																		// Ammo_economy
			1136.0,																	// Fuel_default_weight
			10.0,																		// Fuel_economy
			1.0,																	// number_of_main_rotors
			5.08,																	// main_rotor_radius

			600,																		// initial_damage_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,										// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,												// explosive_power
			TRUE,																		// offensive_capability
			TRUE,																	// player_controllable JB 030408 Fly any aircraft
			100,																		// points value

			SOUND_SAMPLE_INDEX_SMALL_HELICOPTER_ROTOR,					// continuous_sound_effect_index
			SOUND_SAMPLE_INDEX_SMALL_HELICOPTER_ROTOR_WIND_UP,			// wind_up_sound_effect_index
			SOUND_SAMPLE_INDEX_SMALL_HELICOPTER_ROTOR_WIND_DOWN,		// wind_down_sound_effect_index
      },
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_AIRCRAFT_MV22_OSPREY
		//
		////////////////////////////////////////
      {
         "MV-22 Osprey",														// full_name
         "MV-22 OSPREY",														// long_display_name
         "MV-22",																	// short_display_name
			"TILT-ROTOR",															// easy_display_name

         OBJECT_3D_MV_22,														// default_3d_shape
			NUM_GUNSHIP_TYPES,													// gunship_type
			ENTITY_FORCE_AIR,														// force
			WEAPON_CONFIG_TYPE_MV22_OSPREY_1,								// default_weapon_config_type
			WEAPON_CONFIG_TYPE_MV22_OSPREY_1,								// min_weapon_config_type
			WEAPON_CONFIG_TYPE_MV22_OSPREY_1,								// max_weapon_config_type
			WEAPON_CONFIG_TYPE_MV22_OSPREY_1,								// air_to_air_weapon_config_type
			WEAPON_CONFIG_TYPE_MV22_OSPREY_1,								// air_to_surface_weapon_config_type
			WEAPON_CONFIG_TYPE_MV22_OSPREY_1,								// scout_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_NO_WEAPON,								// default_weapon_type
			TARGET_SYMBOL_HELICOPTER,											// target_symbol_type
			TARGET_PRIORITY_MEDIUM,												// target_priority_type
			FORCE_INFO_CATAGORY_UNARMED_HELICOPTER,						// force_info_catagory
			THREAT_TYPE_INVALID,													// threat_type
			VIEW_CATEGORY_TRANSPORT_HELICOPTERS,							// view_category
			VIEW_TYPE_MV22_OSPREY,												// view_type
			MAP_ICON_TRANSPORT_HELICOPTER,									// map icon

         3.373,																	// centre_of_gravity_to_ground_distance
         2.5,																		// centre_of_gravity_to_ground_distance_destroyed
         18.0,																		// chase_view_min_distance
         100.0,	  																// chase_view_max_distance
			0.5,																		// chase_view_min_distance_test
         2.0 * KILOMETRE,														// chase_view_max_distance_test
         knots_to_metres_per_second (280.0),								// cruise_velocity
         100.0,																	// cruise_altitude
         100.0,																	// attack_altitude
			rad (-12.0),															// destroyed_bank_offset
			rad (0.0),																// destroyed_pitch_offset
			rad (0.0),																// fuselage_angle
			0.0,																		// liftoff_velocity
			rad (0.0),																// main_rotor_shaft_angle
			-1.0,																		// main_rotor_direction
			rad (-4.0),																// main_rotor_blade_droop_angle
			0.0,																		// propellor_direction
			rad (100),																// max_turn_rate (deg / sec)
			rad (180.0),															// max_roll
			1.0,																		// max_vertical_turn_allowance
			15.0,																		// avoidance_radius
			14.0 * G,																// g_max
			14.0,																		// power_output
			-1.0,																		// tail_rotor_direction
			3000.0,																	// recon_radius
			10.0,																		// target_scan_delay
			0.0,																		// air_scan_range
			0.0,																		// surface_scan_range
			0.0,																		// potential_air_to_air_threat
			0.0,																		// potential_air_to_surface_threat
			10.0,																		// Ammo_economy
			1136.0,																	// Fuel_default_weight
			10.0,																		// Fuel_economy
			2.0,																	// number_of_main_rotors
			12.885,																	// main_rotor_radius

			600,																		// initial_damage_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,										// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,												// explosive_power
			FALSE,			 														// offensive_capability
			TRUE,																	// player_controllable JB 030408 Fly any aircraft
			75,																		// points value

			SOUND_SAMPLE_INDEX_V22,					// continuous_sound_effect_index
			SOUND_SAMPLE_INDEX_MEDIUM_HELICOPTER_ROTOR_WIND_UP,		// wind_up_sound_effect_index
			SOUND_SAMPLE_INDEX_MEDIUM_HELICOPTER_ROTOR_WIND_DOWN,		// wind_down_sound_effect_index
      },
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_AIRCRAFT_AH1T_SEACOBRA
		//
		////////////////////////////////////////
      {
         "AH-1T Sea Cobra",														// full_name
         "AH-1T SEACOBRA",														// long_display_name
         "AH-1T",																	// short_display_name
			"HELICOPTER",															// easy_display_name

         OBJECT_3D_AH1_T,														// default_3d_shape
			NUM_GUNSHIP_TYPES,													// gunship_type
			ENTITY_FORCE_AIR,														// force
			WEAPON_CONFIG_TYPE_AH1T_SEACOBRA_1,								// default_weapon_config_type
			WEAPON_CONFIG_TYPE_AH1T_SEACOBRA_1,								// min_weapon_config_type
			WEAPON_CONFIG_TYPE_AH1T_SEACOBRA_1,								// max_weapon_config_type
			WEAPON_CONFIG_TYPE_AH1T_SEACOBRA_1,								// air_to_air_weapon_config_type
			WEAPON_CONFIG_TYPE_AH1T_SEACOBRA_1,								// air_to_surface_weapon_config_type
			WEAPON_CONFIG_TYPE_AH1T_SEACOBRA_1,								// scout_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_NO_WEAPON,								// default_weapon_type
			TARGET_SYMBOL_HELICOPTER,											// target_symbol_type
			TARGET_PRIORITY_MEDIUM,												// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_HELICOPTER,							// force_info_catagory
			THREAT_TYPE_INVALID,			 										// threat_type
			VIEW_CATEGORY_COMBAT_HELICOPTERS,								// view_category
			VIEW_TYPE_AH1T_SEACOBRA,											// view_type
			MAP_ICON_HELICOPTER,													// map icon

         3.75,																		// centre_of_gravity_to_ground_distance
         3.4,																		// centre_of_gravity_to_ground_distance_destroyed
         15.0,																		// chase_view_min_distance
         100.0,	  																// chase_view_max_distance
			0.5,																		// chase_view_min_distance_test
         2.0 * KILOMETRE,														// chase_view_max_distance_test
         knots_to_metres_per_second (110.0),								// cruise_velocity
         15.0,																		// cruise_altitude
         7.5,																		// attack_altitude
			rad (0.0),			 													// destroyed_bank_offset
			rad (0.0),																// destroyed_pitch_offset
			rad (0.0),																// fuselage_angle
			0.0,																		// liftoff_velocity
			rad (0.0),																// main_rotor_shaft_angle
			-1.0,																		// main_rotor_direction
			rad (-0.5),																// main_rotor_blade_droop_angle
			0.0,																		// propellor_direction
			rad (200),																// max_turn_rate (deg / sec)
			rad (180.0),															// max_roll
			1.0,																		// max_vertical_turn_allowance
			15.0,																		// avoidance_radius
			6.0 * G,																	// g_max
			14.0,																		// power_output
			-1.0,																		// tail_rotor_direction
			5000.0,																	// recon_radius
			10.0,																		// target_scan_delay
			3000.0,																	// air_scan_range
			4000.0,																	// surface_scan_range
			1.0,																		// potential_air_to_air_threat
			1.0,																		// potential_air_to_surface_threat
			10.0,																		// Ammo_economy
			1136.0,																	// Fuel_default_weight
			10.0,																		// Fuel_economy
			1.0,																	// number_of_main_rotors
			6.7,																	// main_rotor_radius

			600,																		// initial_damage_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,										// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,												// explosive_power
			TRUE,																		// offensive_capability
			TRUE,																	// player_controllable JB 030408 Fly any aircraft
			100,																		// points value

			SOUND_SAMPLE_INDEX_EXTERIOR_APACHE_ROTOR,						// continuous_sound_effect_index
			SOUND_SAMPLE_INDEX_EXTERIOR_APACHE_ROTOR_WIND_UP,			// wind_up_sound_effect_index
			SOUND_SAMPLE_INDEX_EXTERIOR_APACHE_ROTOR_WIND_DOWN,		// wind_down_sound_effect_index
      },
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_AIRCRAFT_AH1W_SUPERCOBRA
		//
		////////////////////////////////////////
      {
         "AH-1W Super Cobra",													// full_name
         "AH-1W SUPERCOBRA",													// long_display_name
         "AH-1W",																	// short_display_name
			"HELICOPTER",															// easy_display_name

         OBJECT_3D_AH1_W,														// default_3d_shape
			NUM_GUNSHIP_TYPES,													// gunship_type
			ENTITY_FORCE_AIR,														// force
			WEAPON_CONFIG_TYPE_AH1W_SUPERCOBRA_1,				 			// default_weapon_config_type
			WEAPON_CONFIG_TYPE_AH1W_SUPERCOBRA_1,				 			// min_weapon_config_type
			WEAPON_CONFIG_TYPE_AH1W_SUPERCOBRA_1,				 			// max_weapon_config_type
			WEAPON_CONFIG_TYPE_AH1W_SUPERCOBRA_1,				 			// air_to_air_weapon_config_type
			WEAPON_CONFIG_TYPE_AH1W_SUPERCOBRA_1,				 			// air_to_surface_weapon_config_type
			WEAPON_CONFIG_TYPE_AH1W_SUPERCOBRA_1,				 			// scout_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_NO_WEAPON,								// default_weapon_type
			TARGET_SYMBOL_HELICOPTER,											// target_symbol_type
			TARGET_PRIORITY_MEDIUM,												// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_HELICOPTER,							// force_info_catagory
			THREAT_TYPE_INVALID,			 										// threat_type
			VIEW_CATEGORY_COMBAT_HELICOPTERS,								// view_category
			VIEW_TYPE_AH1W_SUPERCOBRA,											// view_type
			MAP_ICON_HELICOPTER,													// map icon

         3.75,																		// centre_of_gravity_to_ground_distance
         3.4,																		// centre_of_gravity_to_ground_distance_destroyed
         15.0,																		// chase_view_min_distance
         100.0,	  																// chase_view_max_distance
			0.5,																		// chase_view_min_distance_test
         2.0 * KILOMETRE,														// chase_view_max_distance_test
         knots_to_metres_per_second (110.0),								// cruise_velocity
         15.0,																		// cruise_altitude
         7.5,																		// attack_altitude
			rad (0.0),			 													// destroyed_bank_offset
			rad (0.0),																// destroyed_pitch_offset
			rad (0.0),																// fuselage_angle
			0.0,																		// liftoff_velocity
			rad (0.0),																// main_rotor_shaft_angle
			-1.0,																		// main_rotor_direction
			rad (-0.5),																// main_rotor_blade_droop_angle
			0.0,																		// propellor_direction
			rad (200),																// max_turn_rate (deg / sec)
			rad (180.0),															// max_roll
			1.0,																		// max_vertical_turn_allowance
			15.0,																		// avoidance_radius
			6.0 * G,																	// g_max
			14.0,																		// power_output
			-1.0,																		// tail_rotor_direction
			5000.0,																	// recon_radius
			10.0,																		// target_scan_delay
			3000.0,																	// air_scan_range
			4000.0,																	// surface_scan_range
			1.0,																		// potential_air_to_air_threat
			1.0,																		// potential_air_to_surface_threat
			10.0,																		// Ammo_economy
			1136.0,																	// Fuel_default_weight
			10.0,																		// Fuel_economy
			1.0,																	// number_of_main_rotors
			7.315,																	// main_rotor_radius

			600,																		// initial_damage_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,										// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,												// explosive_power
			TRUE,																		// offensive_capability
			TRUE,																	// player_controllable JB 030408 Fly any aircraft
			100,																		// points value
            SOUND_SAMPLE_INDEX_EXTERIOR_APACHE_ROTOR,						// continuous_sound_effect_index
			SOUND_SAMPLE_INDEX_EXTERIOR_APACHE_ROTOR_WIND_UP,			// wind_up_sound_effect_index
			SOUND_SAMPLE_INDEX_EXTERIOR_APACHE_ROTOR_WIND_DOWN,		// wind_down_sound_effect_index
      },
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_AIRCRAFT_CH53E_SUPER_STALLION
		//
		////////////////////////////////////////
      {
         "CH-53E Super Stallion",											// full_name
         "CH-53E SUPER STALLION",											// long_display_name
         "CH-53E",																// short_display_name
			"HELICOPTER",															// easy_display_name

         OBJECT_3D_CH_53,														// default_3d_shape
			NUM_GUNSHIP_TYPES,													// gunship_type
			ENTITY_FORCE_AIR,														// force
			WEAPON_CONFIG_TYPE_CH53E_SUPER_STALLION_1,					// default_weapon_config_type
			WEAPON_CONFIG_TYPE_CH53E_SUPER_STALLION_1,					// min_weapon_config_type
			WEAPON_CONFIG_TYPE_CH53E_SUPER_STALLION_1,					// max_weapon_config_type
			WEAPON_CONFIG_TYPE_CH53E_SUPER_STALLION_1,					// air_to_air_weapon_config_type
			WEAPON_CONFIG_TYPE_CH53E_SUPER_STALLION_1,					// air_to_surface_weapon_config_type
			WEAPON_CONFIG_TYPE_CH53E_SUPER_STALLION_1,					// scout_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_NO_WEAPON,								// default_weapon_type
			TARGET_SYMBOL_HELICOPTER,											// target_symbol_type
			TARGET_PRIORITY_MEDIUM,												// target_priority_type
			FORCE_INFO_CATAGORY_UNARMED_HELICOPTER,						// force_info_catagory
			THREAT_TYPE_INVALID,			 										// threat_type
			VIEW_CATEGORY_TRANSPORT_HELICOPTERS,							// view_category
			VIEW_TYPE_CH53E_SUPER_STALLION,									// view_type
			MAP_ICON_TRANSPORT_HELICOPTER,									// map icon

         5.228,																	// centre_of_gravity_to_ground_distance
         4.25,																		// centre_of_gravity_to_ground_distance_destroyed
         22.0,																		// chase_view_min_distance
         100.0,	  																// chase_view_max_distance
			0.5,																		// chase_view_min_distance_test
         2.0 * KILOMETRE,														// chase_view_max_distance_test
         knots_to_metres_per_second (85.0),								// cruise_velocity
         50.0,																		// cruise_altitude
         50.0,																		// attack_altitude
			rad (-8.0),				  												// destroyed_bank_offset
			rad (0.0),																// destroyed_pitch_offset
			rad (0.0),																// fuselage_angle
			0.0,																		// liftoff_velocity
			rad (3.5),																// main_rotor_shaft_angle
			-1.0,																		// main_rotor_direction
			rad (-4.0),																// main_rotor_blade_droop_angle
			0.0,																		// propellor_direction
			rad (160),																// max_turn_rate (deg / sec)
			rad (180.0),															// max_roll
			1.0,																		// max_vertical_turn_allowance
			15.0,																		// avoidance_radius
			6.0 * G,																	// g_max
			12.0,																		// power_output
			-1.0,																		// tail_rotor_direction
			3000.0,																	// recon_radius
			10.0,																		// target_scan_delay
			0.0,																		// air_scan_range
			0.0,																		// surface_scan_range
			0.0,																		// potential_air_to_air_threat
			0.0,																		// potential_air_to_surface_threat
			10.0,																		// Ammo_economy
			1136.0,																	// Fuel_default_weight
			10.0,																		// Fuel_economy
			1.0,																	// number_of_main_rotors
			12.08,																	// main_rotor_radius

			600,																		// initial_damage_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,										// explosive_quality
			EXPLOSIVE_POWER_HIGH,												// explosive_power
			FALSE,																	// offensive_capability
			TRUE,																	// player_controllable JB 030408 Fly any aircraft
			75,																		// points value

			SOUND_SAMPLE_INDEX_CH53E,					                // continuous_sound_effect_index
			SOUND_SAMPLE_INDEX_LARGE_HELICOPTER_ROTOR_WIND_UP,			// wind_up_sound_effect_index
			SOUND_SAMPLE_INDEX_LARGE_HELICOPTER_ROTOR_WIND_DOWN,		// wind_down_sound_effect_index
      },
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_AIRCRAFT_C17_GLOBEMASTER_III
		//
		////////////////////////////////////////
		{
			"C-17 Globemaster III",												// full_name
         "C-17 GLOBEMASTER III",												// long_display_name
         "C-17",																	// short_display_name
			"AIRCRAFT",																// easy_display_name

			OBJECT_3D_C_17,														// default_3d_shape
			NUM_GUNSHIP_TYPES,													// gunship_type
			ENTITY_FORCE_AIR,														// force
			WEAPON_CONFIG_TYPE_C17_GLOBEMASTER_III_1,						// default_weapon_config_type
			WEAPON_CONFIG_TYPE_C17_GLOBEMASTER_III_1,						// min_weapon_config_type
			WEAPON_CONFIG_TYPE_C17_GLOBEMASTER_III_1,						// max_weapon_config_type
			WEAPON_CONFIG_TYPE_C17_GLOBEMASTER_III_1,						// air_to_air_weapon_config_type
			WEAPON_CONFIG_TYPE_C17_GLOBEMASTER_III_1,						// air_to_surface_weapon_config_type
			WEAPON_CONFIG_TYPE_C17_GLOBEMASTER_III_1,						// scout_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_NO_WEAPON,								// default_weapon_type
			TARGET_SYMBOL_AIRCRAFT,												// target_symbol_type
			TARGET_PRIORITY_MEDIUM,												// target_priority_type
			FORCE_INFO_CATAGORY_UNARMED_FIXED_WING,						// force_info_catagory
			THREAT_TYPE_INVALID,													// threat_type
			VIEW_CATEGORY_TRANSPORT_AIRCRAFT,								// view_category
			VIEW_TYPE_C17_GLOBEMASTER_III,									// view_type
			MAP_ICON_TRANSPORT_AIRCRAFT,										// map icon

			6.075,																	// centre_of_gravity_to_ground_distance
         5.0,																		// centre_of_gravity_to_ground_distance_destroyed
         55.0,																		// chase_view_min_distance
         150.0,																	// chase_view_max_distance
			0.5,																		// chase_view_min_distance_test
         2.0 * KILOMETRE,														// chase_view_max_distance_test
			knots_to_metres_per_second (240.0),								// cruise_velocity
			700.0,																	// cruise_altitude
			700.0,																	// attack_altitude
			rad (-7.0),																// destroyed_bank_offset
			0.0,																		// destroyed_pitch_offset
			rad (0.0),																// fuselage_angle
			knots_to_metres_per_second (100),								// liftoff_velocity
			rad (0.0),																// main_rotor_shaft_angle
			0.0,																		// main_rotor_direction
			rad (0.0),																// main_rotor_blade_droop_angle
			-1.0,																		// propellor_direction
			rad (40),																// max_turn_rate (deg / sec)
			rad (40.0),																// max_roll
			0.1,																		// max_vertical_turn_allowance
			30.0,																		// avoidance_radius
			3.0 * G,																	// g_max
			20.0,																		// power_output
			0.0,																		// tail_rotor_direction
			3000.0,																	// recon_radius
			10.0,																		// target_scan_delay
			0.0,																		// air_scan_range
			0.0,				  														// surface_scan_range
			0.0,																		// potential_air_to_air_threat
			0.0,																		// potential_air_to_surface_threat
			10.0,																		// Ammo_economy
			1136.0,																	// Fuel_default_weight
			10.0,																		// Fuel_economy
			0.0,																	// number_of_main_rotors
			0.0,																	// main_rotor_radius

			850,																		// initial_damage_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,										// explosive_quality
			EXPLOSIVE_POWER_HIGH,												// explosive_power
			FALSE,  																	// offensive_capability
			FALSE,																	// player_controllable
			150,																		// points value

			SOUND_SAMPLE_INDEX_C17,										// continuous_sound_effect_index
			SOUND_SAMPLE_INDEX_NONE,											// wind_up_sound_effect_index
			SOUND_SAMPLE_INDEX_NONE,											// wind_down_sound_effect_index
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_AIRCRAFT_IL76MD_CANDID_B
		//
		////////////////////////////////////////
		{
			"Il-76MD Candid-B",													// full_name
         "Il-76MD CANDID-B",													// long_display_name
         "Il-76MD",																// short_display_name
			"AIRCRAFT",																// easy_display_name

			OBJECT_3D_IL_76,														// default_3d_shape
			NUM_GUNSHIP_TYPES,													// gunship_type
			ENTITY_FORCE_AIR,														// force
			WEAPON_CONFIG_TYPE_IL76MD_CANDID_B_1,		  					// default_weapon_config_type
			WEAPON_CONFIG_TYPE_IL76MD_CANDID_B_1,							// min_weapon_config_type
			WEAPON_CONFIG_TYPE_IL76MD_CANDID_B_1,							// max_weapon_config_type
			WEAPON_CONFIG_TYPE_IL76MD_CANDID_B_1,							// air_to_air_weapon_config_type
			WEAPON_CONFIG_TYPE_IL76MD_CANDID_B_1,							// air_to_surface_weapon_config_type
			WEAPON_CONFIG_TYPE_IL76MD_CANDID_B_1,							// scout_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_NO_WEAPON,								// default_weapon_type
			TARGET_SYMBOL_AIRCRAFT,												// target_symbol_type
			TARGET_PRIORITY_MEDIUM,												// target_priority_type
			FORCE_INFO_CATAGORY_UNARMED_FIXED_WING,						// force_info_catagory
			THREAT_TYPE_INVALID,													// threat_type
			VIEW_CATEGORY_TRANSPORT_AIRCRAFT,								// view_category
			VIEW_TYPE_IL76MD_CANDID_B,											// view_type
			MAP_ICON_TRANSPORT_AIRCRAFT,										// map icon

			6.55,																		// centre_of_gravity_to_ground_distance
         5.0,																		// centre_of_gravity_to_ground_distance_destroyed
         55.0,																		// chase_view_min_distance
         150.0,																	// chase_view_max_distance
			0.5,																		// chase_view_min_distance_test
         2.0 * KILOMETRE,														// chase_view_max_distance_test
			knots_to_metres_per_second (240.0),								// cruise_velocity
			700.0,																	// cruise_altitude
			700.0,																	// attack_altitude
			rad (9.0),																// destroyed_bank_offset
			0.0,																		// destroyed_pitch_offset
			rad (0.0),																// fuselage_angle
			knots_to_metres_per_second (100),								// liftoff_velocity
			rad (0.0),																// main_rotor_shaft_angle
			0.0,																		// main_rotor_direction
			rad (0.0),																// main_rotor_blade_droop_angle
			1.0,																		// propellor_direction
			rad (40),																// max_turn_rate (deg / sec)
			rad (40.0),																// max_roll
			0.1,																		// max_vertical_turn_allowance
			30.0,																		// avoidance_radius
			3.0 * G,																	// g_max
			20.0,																		// power_output
			0.0,																		// tail_rotor_direction
			3000.0,																	// recon_radius
			10.0,																		// target_scan_delay
			0.0,																		// air_scan_range
			0.0,				  														// surface_scan_range
			0.0,																		// potential_air_to_air_threat
			0.0,																		// potential_air_to_surface_threat
			10.0,																		// Ammo_economy
			1136.0,																	// Fuel_default_weight
			10.0,																		// Fuel_economy
			0.0,																	// number_of_main_rotors
			0.0,																	// main_rotor_radius

			850,																		// initial_damage_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,										// explosive_quality
			EXPLOSIVE_POWER_HIGH,												// explosive_power
			FALSE,  																	// offensive_capability
			FALSE,																	// player_controllable
			150,																		// points value

			SOUND_SAMPLE_INDEX_IL76,										// continuous_sound_effect_index
			SOUND_SAMPLE_INDEX_NONE,											// wind_up_sound_effect_index
			SOUND_SAMPLE_INDEX_NONE,											// wind_down_sound_effect_index
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_AIRCRAFT_C130J_HERCULES_II
		//
		////////////////////////////////////////
		{
			"C-130J Hercules II",			  									// full_name
         "C-130J HERCULES II",			  									// long_display_name
         "C-130J",																// short_display_name
			"AIRCRAFT",																// easy_display_name

			OBJECT_3D_C130,														// default_3d_shape
			NUM_GUNSHIP_TYPES,													// gunship_type
			ENTITY_FORCE_AIR,														// force
			WEAPON_CONFIG_TYPE_C130J_HERCULES_II_1,						// default_weapon_config_type
			WEAPON_CONFIG_TYPE_C130J_HERCULES_II_1,		  				// min_weapon_config_type
			WEAPON_CONFIG_TYPE_C130J_HERCULES_II_1,		  				// max_weapon_config_type
			WEAPON_CONFIG_TYPE_C130J_HERCULES_II_1,		  				// air_to_air_weapon_config_type
			WEAPON_CONFIG_TYPE_C130J_HERCULES_II_1,		  				// air_to_surface_weapon_config_type
			WEAPON_CONFIG_TYPE_C130J_HERCULES_II_1,		  				// scout_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_NO_WEAPON,								// default_weapon_type
			TARGET_SYMBOL_AIRCRAFT,												// target_symbol_type
			TARGET_PRIORITY_MEDIUM,												// target_priority_type
			FORCE_INFO_CATAGORY_UNARMED_FIXED_WING,						// force_info_catagory
			THREAT_TYPE_INVALID,													// threat_type
			VIEW_CATEGORY_TRANSPORT_AIRCRAFT,								// view_category
			VIEW_TYPE_C130J_HERCULES_II,										// view_type
			MAP_ICON_TRANSPORT_AIRCRAFT,										// map icon

			3.9,			  															// centre_of_gravity_to_ground_distance
         2.8,																		// centre_of_gravity_to_ground_distance_destroyed
         45.0,																		// chase_view_min_distance
         150.0,																	// chase_view_max_distance
			0.5,																		// chase_view_min_distance_test
         2.0 * KILOMETRE,														// chase_view_max_distance_test
			knots_to_metres_per_second (260.0),								// cruise_velocity
			700.0,																	// cruise_altitude
			700.0,																	// attack_altitude
			0.0,																		// destroyed_bank_offset
			0.0,																		// destroyed_pitch_offset
			rad (0.0),																// fuselage_angle
			knots_to_metres_per_second (100),								// liftoff_velocity
			rad (0.0),																// main_rotor_shaft_angle
			0.0,																		// main_rotor_direction
			rad (0.0),																// main_rotor_blade_droop_angle
			-1.0,																		// propellor_direction
			rad (60),																// max_turn_rate (deg / sec)
			rad (60.0),																// max_roll
			0.2,																		// max_vertical_turn_allowance
			20.0,																		// avoidance_radius
			4.0 * G,																	// g_max
			20.0,																		// power_output
			0.0,																		// tail_rotor_direction
			3000.0,																	// recon_radius
			10.0,																		// target_scan_delay
			0.0,																		// air_scan_range
			0.0,				  														// surface_scan_range
			0.0,																		// potential_air_to_air_threat
			0.0,																		// potential_air_to_surface_threat
			10.0,																		// Ammo_economy
			1136.0,																	// Fuel_default_weight
			10.0,																		// Fuel_economy
			0.0,																	// number_of_main_rotors
			0.0,																	// main_rotor_radius

			850,																		// initial_damage_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,										// explosive_quality
			EXPLOSIVE_POWER_HIGH,												// explosive_power
			FALSE,  																	// offensive_capability
			FALSE,																	// player_controllable
			150,																		// points value

			SOUND_SAMPLE_INDEX_C130,										// continuous_sound_effect_index
			SOUND_SAMPLE_INDEX_NONE,											// wind_up_sound_effect_index
			SOUND_SAMPLE_INDEX_NONE,											// wind_down_sound_effect_index
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_AIRCRAFT_AN12B_CUB
		//
		////////////////////////////////////////
		{
			"An-12B Cub",															// full_name
         "An-12B Cub",															// long_display_name
         "An-12B",																// short_display_name
			"AIRCRAFT",																// easy_display_name

			OBJECT_3D_AN_12B,														// default_3d_shape
			NUM_GUNSHIP_TYPES,													// gunship_type
			ENTITY_FORCE_AIR,														// force
			WEAPON_CONFIG_TYPE_AN12B_CUB_1,									// default_weapon_config_type
			WEAPON_CONFIG_TYPE_AN12B_CUB_1,									// min_weapon_config_type
			WEAPON_CONFIG_TYPE_AN12B_CUB_1,									// max_weapon_config_type
			WEAPON_CONFIG_TYPE_AN12B_CUB_1,									// air_to_air_weapon_config_type
			WEAPON_CONFIG_TYPE_AN12B_CUB_1,									// air_to_surface_weapon_config_type
			WEAPON_CONFIG_TYPE_AN12B_CUB_1,									// scout_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_NO_WEAPON,								// default_weapon_type
			TARGET_SYMBOL_AIRCRAFT,												// target_symbol_type
			TARGET_PRIORITY_MEDIUM,												// target_priority_type
			FORCE_INFO_CATAGORY_UNARMED_FIXED_WING,						// force_info_catagory
			THREAT_TYPE_INVALID,													// threat_type
			VIEW_CATEGORY_TRANSPORT_AIRCRAFT,								// view_category
			VIEW_TYPE_AN12B_CUB,													// view_type
			MAP_ICON_TRANSPORT_AIRCRAFT,										// map icon

			6.5,			  															// centre_of_gravity_to_ground_distance
         5.0,																		// centre_of_gravity_to_ground_distance_destroyed
         40.0,																		// chase_view_min_distance
         150.0,																	// chase_view_max_distance
			0.5,																		// chase_view_min_distance_test
         2.0 * KILOMETRE,														// chase_view_max_distance_test
			knots_to_metres_per_second (260.0),								// cruise_velocity
			700.0,																	// cruise_altitude
			700.0,																	// attack_altitude
			0.0,																		// destroyed_bank_offset
			0.0,																		// destroyed_pitch_offset
			rad (0.0),																// fuselage_angle
			knots_to_metres_per_second (100),								// liftoff_velocity
			rad (0.0),																// main_rotor_shaft_angle
			0.0,																		// main_rotor_direction
			rad (0.0),																// main_rotor_blade_droop_angle
			1.0,																		// propellor_direction
			rad (50),																// max_turn_rate (deg / sec)
			rad (50.0),																// max_roll
			0.15,																		// max_vertical_turn_allowance
			20.0,																		// avoidance_radius
			4.0 * G,																	// g_max
			20.0,																		// power_output
			0.0,																		// tail_rotor_direction
			3000.0,																	// recon_radius
			10.0,																		// target_scan_delay
			0.0,																		// air_scan_range
			0.0,				  														// surface_scan_range
			0.0,																		// potential_air_to_air_threat
			0.0,																		// potential_air_to_surface_threat
			10.0,																		// Ammo_economy
			1136.0,																	// Fuel_default_weight
			10.0,																		// Fuel_economy
			0.0,																	// number_of_main_rotors
			0.0,																	// main_rotor_radius

			850,																		// initial_damage_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,										// explosive_quality
			EXPLOSIVE_POWER_HIGH,												// explosive_power
			FALSE,  																	// offensive_capability
			FALSE,																	// player_controllable
			150,																		// points value

			SOUND_SAMPLE_INDEX_AN12B,										// continuous_sound_effect_index
			SOUND_SAMPLE_INDEX_NONE,											// wind_up_sound_effect_index
			SOUND_SAMPLE_INDEX_NONE,											// wind_down_sound_effect_index
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_AIRCRAFT_AH1Z_VIPER
		//
		////////////////////////////////////////
      {
         "AH-1Z Viper",													// full_name
         "AH-1Z VIPER",													// long_display_name
         "AH-1Z",																	// short_display_name
			"HELICOPTER",															// easy_display_name

         OBJECT_3D_AH1Z,														// default_3d_shape
			GUNSHIP_TYPE_VIPER,													// gunship_type
			ENTITY_FORCE_AIR,														// force
			WEAPON_CONFIG_TYPE_AH1Z_VIPER_14,				 			// default_weapon_config_type
			WEAPON_CONFIG_TYPE_AH1Z_VIPER_1,				 			// min_weapon_config_type
			WEAPON_CONFIG_TYPE_AH1Z_VIPER_18,				 			// max_weapon_config_type
			WEAPON_CONFIG_TYPE_AH1Z_VIPER_10,				 			// air_to_air_weapon_config_type
			WEAPON_CONFIG_TYPE_AH1Z_VIPER_17,				 			// air_to_surface_weapon_config_type
			WEAPON_CONFIG_TYPE_AH1Z_VIPER_9,				 			// scout_weapon_config_type
			ENTITY_SUB_TYPE_WEAPON_NO_WEAPON,								// default_weapon_type
			TARGET_SYMBOL_HELICOPTER,											// target_symbol_type
			TARGET_PRIORITY_MEDIUM,												// target_priority_type
			FORCE_INFO_CATAGORY_ARMED_HELICOPTER,							// force_info_catagory
			THREAT_TYPE_INVALID,			 										// threat_type
			VIEW_CATEGORY_COMBAT_HELICOPTERS,								// view_category
			VIEW_TYPE_AH1Z_VIPER,											// view_type
			MAP_ICON_HELICOPTER,													// map icon

         3.75,																		// centre_of_gravity_to_ground_distance
         3.4,																		// centre_of_gravity_to_ground_distance_destroyed
         15.0,																		// chase_view_min_distance
         100.0,	  																// chase_view_max_distance
			0.5,																		// chase_view_min_distance_test
         2.0 * KILOMETRE,														// chase_view_max_distance_test
         knots_to_metres_per_second (110.0),								// cruise_velocity
         15.0,																		// cruise_altitude
         7.5,																		// attack_altitude
			rad (0.0),			 													// destroyed_bank_offset
			rad (0.0),																// destroyed_pitch_offset
			rad (0.0),																// fuselage_angle
			0.0,																		// liftoff_velocity
			rad (0.0),																// main_rotor_shaft_angle
			-1.0,																		// main_rotor_direction
			rad (-0.5),																// main_rotor_blade_droop_angle
			0.0,																		// propellor_direction
			rad (200),																// max_turn_rate (deg / sec)
			rad (180.0),															// max_roll
			1.0,																		// max_vertical_turn_allowance
			15.0,																		// avoidance_radius
			6.0 * G,																	// g_max
			14.0,																		// power_output
			-1.0,																		// tail_rotor_direction
			5000.0,																	// recon_radius
			10.0,																		// target_scan_delay
			3000.0,																	// air_scan_range
			4000.0,																	// surface_scan_range
			1.0,																		// potential_air_to_air_threat
			1.0,																		// potential_air_to_surface_threat
			10.0,																		// Ammo_economy
			1136.0,																	// Fuel_default_weight
			10.0,																		// Fuel_economy
			1.0,																	// number_of_main_rotors
			7.315,																	// main_rotor_radius

			600,																		// initial_damage_level

			EXPLOSIVE_QUALITY_EXPLOSIVE,										// explosive_quality
			EXPLOSIVE_POWER_MEDIUM,												// explosive_power
			TRUE,																		// offensive_capability
			TRUE,																	// player_controllable JB 030408 Fly any aircraft
			100,																		// points value
            SOUND_SAMPLE_INDEX_EXTERIOR_APACHE_ROTOR,						// continuous_sound_effect_index
			SOUND_SAMPLE_INDEX_EXTERIOR_APACHE_ROTOR_WIND_UP,			// wind_up_sound_effect_index
			SOUND_SAMPLE_INDEX_EXTERIOR_APACHE_ROTOR_WIND_DOWN,		// wind_down_sound_effect_index
      },
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
